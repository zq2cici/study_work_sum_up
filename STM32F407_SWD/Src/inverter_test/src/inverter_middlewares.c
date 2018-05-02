
#include "stm32f4xx_hal.h"

#include "inverter_test.h"
#include "inverter_middlewares.h"

extern ADC_HandleTypeDef hadc1;
u16 Get_Adc(u8 ch)   
{
	ch=10;
	HAL_ADC_Start(&hadc1);
	while(!(ADC_FLAG_EOC ==HAL_ADC_GetState(&hadc1)));//等待转换结束
	return HAL_ADC_GetValue(&hadc1);	//返回最近一次ADC1规则组的转换结果
}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		HAL_Delay(5);
	}
	return temp_val/times;
} 
	

#if EN_USART1_RX   //如果使能了接收
u8 RxData;
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART_RX_STA=0;       //接收状态标记	
UART1_BUF_INFO  UART1_Rev={0,0};
extern UART_HandleTypeDef huart1;
void Usart1_Iint(void)
{
	UART1_Rev.tail =0;
	UART1_Rev.head =0;
	USART_RX_STA =0;
	HAL_UART_Receive_IT(&huart1, &RxData, 1);
}
extern UART_HandleTypeDef huart1;
void Usart1_sendByte(u16 Data )
{
	u8 temp;
	temp =Data;
	HAL_UART_Transmit( &huart1, &temp,1, 1000);
}
//获取串口返回字节
//@*pdata : 获取数据缓冲地址
//@ rval: 1 获取成功，0: 获取失败
 u8 Usart1_readByte(u8 *pdata)
{
	if(UART1_Rev.tail != UART1_Rev.head){
		
		UART1_Rev.tail++;
		if(UART1_Rev.tail>= USART_REC_LEN){
			UART1_Rev.tail= 0;

		}
			
		if(USART_RX_STA) USART_RX_STA--;
		*pdata = USART_RX_BUF[UART1_Rev.tail] ;
		return 1;
	}
	return 0;
}

#endif	// #if EN_USART1_RX 

 




