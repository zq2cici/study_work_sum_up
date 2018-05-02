

#include "stm32f4xx_hal.h"

#include "inverter_test.h"
#include "inverter_middlewares.h"


extern UART_HandleTypeDef huart1;
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance ==USART1){
		UART1_Rev.head++;
		if(UART1_Rev.head >= USART_REC_LEN){
			UART1_Rev.head = 0;
		}
		if(++USART_RX_STA >= USART_REC_LEN){
			USART_RX_STA = USART_REC_LEN;
		}
		USART_RX_BUF[UART1_Rev.head]=RxData;

		HAL_UART_Receive_IT(&huart1, &RxData, 1);
	}
}

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
volatile u8  TIM2CH1_CAPTURE_STA=0;	//输入捕获状态		    				
volatile u32	TIM2CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
volatile u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
volatile u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器溢出中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){
		if((TIM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
		{	 
			TIM2CH1_CAPTURE_STA|=0X20;		//标记成功捕获了一次
			TIM2CH1_CAPTURE_VAL=0xffff;
			HAL_TIM_Base_Stop_IT(&htim2);
			HAL_TIM_IC_Stop_IT (&htim2, TIM_CHANNEL_1);				
		}
	}
	if(htim->Instance == TIM5){
	 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
		{
			TIM5CH1_CAPTURE_STA|=0X20;		//标记成功捕获失败
			TIM5CH1_CAPTURE_VAL=0xffff;
			HAL_TIM_Base_Stop_IT(&htim5);
			HAL_TIM_IC_Stop_IT (&htim5, TIM_CHANNEL_2);
	 	}
	}
	
}
//定时器捕获中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){
			
		if(TIM2CH1_CAPTURE_STA&0X40)		//捕获到一个上降沿 		
		{	  			
			TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
		  	TIM2CH1_CAPTURE_VAL=htim->Instance->CNT;//获取当前的捕获值.
				HAL_TIM_Base_Stop_IT(&htim2);
				HAL_TIM_IC_Stop_IT (&htim2, TIM_CHANNEL_1);			
		}else  								//还未开始,第一次捕获上升沿
		{
			TIM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
			htim->Instance->CNT=0;
		}	
	}
	if(htim->Instance == TIM5){
		if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
		{	  			
			TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
		  	TIM5CH1_CAPTURE_VAL=htim->Instance->CNT;//获取当前的捕获值.
			HAL_TIM_Base_Stop_IT(&htim5);
			HAL_TIM_IC_Stop_IT (&htim5, TIM_CHANNEL_2);
		}else  								//还未开始,第一次捕获上升沿
		{
			TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
 			htim->Instance->CNT=0;
			
		}	
	}
}










