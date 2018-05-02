
#include "stm32f4xx_hal.h"


void TestBoardPowerOn(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,GPIO_PIN_RESET);
}
void TestBoardPowerOff(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,GPIO_PIN_SET);
	
}
//配置IO口输出电压

void MCU_Vbus_Output(void)
{
}

//PWM240HZ --%50DUTY
//PD12
extern TIM_HandleTypeDef htim4;
void MCU_Vinv_Output(uint8_t  state)
{
	if(state){

		HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
	}else{
		HAL_TIM_OC_Stop(&htim4,  TIM_CHANNEL_1);
	}
}

void TEMP_NTC_Output_Normal(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7|GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,GPIO_PIN_SET);	
}
void TEMP_NTC_Output_Abnormal(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7|GPIO_PIN_8,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,GPIO_PIN_SET);	
}

extern DAC_HandleTypeDef hdac;
//DAC
// 负载检测电压输出
// vol:0--3300
void LAOD_VOL_Output(uint16_t  vol)
{
	HAL_DAC_Start(&hdac,  DAC_CHANNEL_1);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, vol);
}

//限制电压输出
//state: ON 正常输出，OFF 关闭输出
void i_LIMIT_Output(uint8_t  state)
{
	if(state){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,GPIO_PIN_SET);	
	}else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,GPIO_PIN_RESET);
	}
}









