/**
  ******************************************************************************
  * @file    inverter_test.c
  * @author  click
  * @version V0.0
  * @date    01-03-2018
  * @brief   This file is about inverter PCB basic testing
	*
	******************************************************************************
  */

#include "stm32f4xx_hal.h"
#include "inverter_test.h"
#include "inverter_middlewares.h"
#include "inverter_gpio.h"


void set_test_stop(u8 stop_status);

u8 TEST_STEP =TEST_INIT;

extern volatile u8  TIM2CH1_CAPTURE_STA;
extern volatile u32  TIM2CH1_CAPTURE_VAL;
extern volatile u8  TIM5CH1_CAPTURE_STA;
extern volatile u32  TIM5CH1_CAPTURE_VAL;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
//判断PWM频率
u8 IsInvPwmFreq60HZ(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_IC_Start_IT (&htim2, TIM_CHANNEL_1);
	
	TIM2CH1_CAPTURE_STA=0;
	TIM2CH1_CAPTURE_VAL=0;
	while(!(TIM2CH1_CAPTURE_STA&0Xa0));
	if((TIM2CH1_CAPTURE_VAL >(16666-100))&&(TIM2CH1_CAPTURE_VAL < (16666+100))){
		return 1;
	}else{
		return 0;
	}
}
u8 IsAuxPwmFreq16KHZ(void)
{
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_TIM_IC_Start_IT (&htim5, TIM_CHANNEL_2);
	
	TIM5CH1_CAPTURE_STA=0;
	TIM5CH1_CAPTURE_VAL=0;		
	while(!(TIM5CH1_CAPTURE_STA&0Xa0));
	if((TIM5CH1_CAPTURE_VAL >(62-10))&&(TIM5CH1_CAPTURE_VAL < (62+10))){
		return 1;
	}else{
		return 0;
	}
}
u8 IsCloseInvPwmFreq60HZ(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_IC_Start_IT (&htim2, TIM_CHANNEL_1);
	
	TIM2CH1_CAPTURE_STA=0;
	TIM2CH1_CAPTURE_VAL=0;
	while(!(TIM2CH1_CAPTURE_STA&0Xa0));
	if( TIM2CH1_CAPTURE_VAL == 0xffff){
		return 1;
	}else{
		return 0;
	}
}
u8 IsCloseAuxPwmFreq16KHZ(void)
{
	HAL_TIM_Base_Start_IT(&htim5);
	HAL_TIM_IC_Start_IT (&htim5, TIM_CHANNEL_2);
	TIM5CH1_CAPTURE_STA=0;
	TIM5CH1_CAPTURE_VAL=0;	
	while(!(TIM5CH1_CAPTURE_STA&0Xa0));
	if(TIM5CH1_CAPTURE_VAL == 0xffff){
		return 1;
	}else{
		return 0;
	}
}

u16 Uart1DataCRC16(u8 *pStr)
{
	//printf("Hello World!\n");
	int i = 0;
	int j = 0;
	int crc16 = 0xffff;
	for (i = 0;i < 13;i++)
	{
		crc16 = crc16 ^ *(pStr+i);
		for (j = 0;j < 8;j++)
		{
			if (crc16 & 0x01)
			crc16 = (crc16 >> 1) ^ 0xa001;
			else crc16 = crc16 >> 1;
		}
	}
	//printf("%X",crc16);
	return crc16;

}


//解析串口数据帧

u8 Uart1DataFrameParse(u8 *pstate)
{
	u8 byte;
	u8 frame[15];
	u8 cnt;
	u16 crc16;	
	if(USART_RX_STA >=15) {
		if(Usart1_readByte( &byte)){
			frame[0]=byte;
			if(byte == 0xab){
				if(Usart1_readByte( &byte)){
					frame[1]=byte;
					if(byte == 0xba){
						if(Usart1_readByte( &byte)){
							frame[2]=byte;
							if(byte == 0x55){
								for(cnt=3;cnt<15;cnt++){
									Usart1_readByte( &byte);
									frame[cnt]=byte;
									HAL_Delay(2);
								}
								crc16=Uart1DataCRC16(frame);
								if(crc16==(frame[13]+(frame[14]*256))){
									*pstate =frame[12];
									return 1;
								}else{
									*pstate =0;
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}


//******************************open loop test start*******************************************

u8 sub_test_step =0;
void open_loop_test(void)
{
	u16 adcx;
	switch(sub_test_step){
	case 0:
		LAOD_VOL_Output(0);
		HAL_Delay(5);
		adcx=Get_Adc_Average(ADC_CHANNEL_10,10);
		if(adcx < 800){
			sub_test_step = 1;
		}else{
			set_test_stop(TEST_STOP_OPEN_LOOP);
		}
		
		break;
	case 1:
		LAOD_VOL_Output(DAC_VOL_0p15V);
		HAL_Delay(500);
		adcx=Get_Adc_Average(ADC_CHANNEL_10,10);
		if(adcx > 2730){
			sub_test_step = 2;
		}else{
			set_test_stop(TEST_STOP_OPEN_LOOP);
		}
		break;
	case 2:
		TEST_STEP = TEST_OVERLOAD;
		sub_test_step =0;
		break;
	default:
		break;

	}
}
//*******************************open loop test end **********************************
//*******************************overload test start *************************************


void overload_test(void)
{
	u8 buf;
	static u8 cnt=0;
	switch(sub_test_step ){
		case 0:
			LAOD_VOL_Output(DAC_VOL_0p44V);
			HAL_Delay(50);
			if(IsInvPwmFreq60HZ()){
				if(IsAuxPwmFreq16KHZ()){
					sub_test_step =1;
				}else{
					set_test_stop(TEST_STOP_OVER_LOAD);
				}
			}else{
				set_test_stop(TEST_STOP_OVER_LOAD);
			}
			break;
		case 1:
			LAOD_VOL_Output(700);
			HAL_Delay(1100);
			if(IsCloseInvPwmFreq60HZ()){
				if(IsCloseAuxPwmFreq16KHZ()){
					sub_test_step =2;
					Usart1_Iint();
					cnt =0;
				}else{
					set_test_stop(TEST_STOP_OVER_LOAD);
				}
			}else{
				set_test_stop(TEST_STOP_OVER_LOAD);
			}			
			
			break;
		case 2:
			if(Uart1DataFrameParse(&buf)){			
				if(buf==0x03){
					TEST_STEP = TEST_SHORT_CIRCUIT;
					sub_test_step =0;
				}

			}

			if(cnt++ >100){
				cnt =0;
				set_test_stop(TEST_STOP_OVER_LOAD);
			}			

			break;
		case 3:
			break;
			
		default:
			break;
	}
}
//******************************overlaod test end***************************************
//*******************************short circuit test start *************************************
void short_circuit_test(void)
{
	u8 buf;
	static u8 cnt=0;
	switch(sub_test_step ){
		case 0:
			TestBoardPowerOff();
			HAL_Delay(100);
			TestBoardPowerOn();
			
			LAOD_VOL_Output(DAC_VOL_0p44V);
			i_LIMIT_Output(ON);
			
			HAL_Delay(1000);
			if(IsInvPwmFreq60HZ()){
				if(IsAuxPwmFreq16KHZ()){
					sub_test_step =1;
				}else{
					set_test_stop(TEST_STOP_SHORT_CIRCUIT);
				}
			}else{
				set_test_stop(TEST_STOP_SHORT_CIRCUIT);
			}

			break;
		case 1:
			MCU_Vinv_Output(OFF);
			i_LIMIT_Output(OFF);
			HAL_Delay(350);
			if(IsCloseInvPwmFreq60HZ()){
				if(IsCloseAuxPwmFreq16KHZ()){
					sub_test_step =2;
					Usart1_Iint();
					cnt =0;
				}else{
					set_test_stop(TEST_STOP_SHORT_CIRCUIT);
				}
			}else{
				set_test_stop(TEST_STOP_SHORT_CIRCUIT);
			}			
			
			break;
		case 2:
			if(Uart1DataFrameParse(&buf)){			
				if(buf==0x05){
					sub_test_step =3;
				}

			}
			if(cnt++ >100){
				cnt =0;
				set_test_stop(TEST_STOP_SHORT_CIRCUIT);
			}			
			break;
		case 3:
			MCU_Vinv_Output(ON);
			i_LIMIT_Output(ON);
			TEST_STEP = TEST_OVER_TEMPRATURE;
			sub_test_step =0;	
			break;
			
		default:
			break;
	}
}
//******************************short circuit test end***************************************
//*******************************over  temprature test start *************************************
void over_temprature_test(void)
{
	u8 buf;
	static u8 cnt=0;
	switch(sub_test_step ){
		case 0:
			TestBoardPowerOff();
			HAL_Delay(100);
			TestBoardPowerOn();
			TEMP_NTC_Output_Normal();
			LAOD_VOL_Output(DAC_VOL_0p44V);
			HAL_Delay(1000);
			if(IsInvPwmFreq60HZ()){
				if(IsAuxPwmFreq16KHZ()){
					sub_test_step =1;
				}else{
					set_test_stop(TEST_STOP_OVER_TEMP);
					
				}
			}else{
				set_test_stop(TEST_STOP_OVER_TEMP);
				
			}
			break;
		case 1:
			TEMP_NTC_Output_Abnormal();
		
			HAL_Delay(1500);
			if(IsCloseInvPwmFreq60HZ()){
				if(IsCloseAuxPwmFreq16KHZ()){
					sub_test_step =2;
					Usart1_Iint();
					cnt =0;
				}else{
					set_test_stop(TEST_STOP_OVER_TEMP);
				}
			}else{
				set_test_stop(TEST_STOP_OVER_TEMP);
			}			
			break;
		case 2:
			if(Uart1DataFrameParse(&buf)){				
				if(buf==0x04){
					sub_test_step =3;
				}
			}
			if(cnt++ >100){
				cnt =0;
				set_test_stop(TEST_STOP_OVER_TEMP);
			}
			
			break;
		case 3:
			TEMP_NTC_Output_Normal();
			HAL_Delay(2500);
			if(IsInvPwmFreq60HZ()){
				if(IsAuxPwmFreq16KHZ()){
					sub_test_step =4;
				}else{
					set_test_stop(TEST_STOP_OVER_TEMP);
				}
			}else{
				set_test_stop(TEST_STOP_OVER_TEMP);
			}

			break;
		case 4:
			sub_test_step =0;
			set_test_stop(TEST_STOP_SUCCESS);
			break;
		default:
			break;
	}
}
//******************************over temprature test end***************************************
////*******************************uart test start *************************************
//void uart_test(void)
//{
//	switch(){
//		case:
//			break;
//		default:
//			break;
//	}
//}
////******************************uart test end***************************************





//****************************test stop  start*******************************************
u8 sub_tset_stop_step;
void set_test_stop(u8 stop_status)
{
	TEST_STEP =TEST_STOP;
	sub_tset_stop_step= stop_status;
}
void test_stop(void)
{
	switch(sub_tset_stop_step){
	case TEST_STOP_OPEN_LOOP:
		printf("开环闭环测试错误\n");
		break;
	case TEST_STOP_OVER_LOAD:
		printf("过载保护测试错误\n");
		break;
	case TEST_STOP_SHORT_CIRCUIT:
		printf("短路保护测试错误\n");
		break;
	case TEST_STOP_OVER_TEMP:
		printf("过温保护测试错误\n");
		break;
	case TEST_STOP_UART:
		break;
	case TEST_STOP_SUCCESS:
		printf("测试成功\n");	
		break;
	default:
		break;

	}

}
//***************************test stop end********************************************


void TEST_Init(void)
{
	TEMP_NTC_Output_Normal();
	
	TestBoardPowerOff();
	HAL_Delay(100);
	TestBoardPowerOn();	

	 HAL_TIM_Base_Start_IT(&htim2);
	
}
///逆变器测试进程

void TEST_Proc(void)
{

	switch(TEST_STEP){
		case TEST_INIT:
			MCU_Vbus_Output();
			MCU_Vinv_Output(ON);
			TEMP_NTC_Output_Normal();
			TEST_STEP =TEST_OPEN_LOOP;
			break;
		case TEST_OPEN_LOOP:
			open_loop_test();
			break;
		case TEST_OVERLOAD:
			overload_test();
			break;
		case TEST_SHORT_CIRCUIT:
			short_circuit_test();
			break;
		case TEST_OVER_TEMPRATURE:
			over_temprature_test();
			break;
		case TEST_UART:
			break;
		case TEST_STOP:
			test_stop();
			break;
		default:
			break;

}




}



















