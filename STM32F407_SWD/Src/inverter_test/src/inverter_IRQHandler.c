

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
volatile u8  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
volatile u32	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
volatile u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
volatile u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ������жϻص�����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){
		if((TIM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
		{	 
			TIM2CH1_CAPTURE_STA|=0X20;		//��ǳɹ�������һ��
			TIM2CH1_CAPTURE_VAL=0xffff;
			HAL_TIM_Base_Stop_IT(&htim2);
			HAL_TIM_IC_Stop_IT (&htim2, TIM_CHANNEL_1);				
		}
	}
	if(htim->Instance == TIM5){
	 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
		{
			TIM5CH1_CAPTURE_STA|=0X20;		//��ǳɹ�����ʧ��
			TIM5CH1_CAPTURE_VAL=0xffff;
			HAL_TIM_Base_Stop_IT(&htim5);
			HAL_TIM_IC_Stop_IT (&htim5, TIM_CHANNEL_2);
	 	}
	}
	
}
//��ʱ�������жϻص�����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){
			
		if(TIM2CH1_CAPTURE_STA&0X40)		//����һ���Ͻ��� 		
		{	  			
			TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
		  	TIM2CH1_CAPTURE_VAL=htim->Instance->CNT;//��ȡ��ǰ�Ĳ���ֵ.
				HAL_TIM_Base_Stop_IT(&htim2);
				HAL_TIM_IC_Stop_IT (&htim2, TIM_CHANNEL_1);			
		}else  								//��δ��ʼ,��һ�β���������
		{
			TIM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
			htim->Instance->CNT=0;
		}	
	}
	if(htim->Instance == TIM5){
		if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
		{	  			
			TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
		  	TIM5CH1_CAPTURE_VAL=htim->Instance->CNT;//��ȡ��ǰ�Ĳ���ֵ.
			HAL_TIM_Base_Stop_IT(&htim5);
			HAL_TIM_IC_Stop_IT (&htim5, TIM_CHANNEL_2);
		}else  								//��δ��ʼ,��һ�β���������
		{
			TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
 			htim->Instance->CNT=0;
			
		}	
	}
}










