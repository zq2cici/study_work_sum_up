
#include "stm32f4xx_hal.h"

#include "inverter_test.h"
#include "inverter_middlewares.h"

extern ADC_HandleTypeDef hadc1;
u16 Get_Adc(u8 ch)   
{
	ch=10;
	HAL_ADC_Start(&hadc1);
	while(!(ADC_FLAG_EOC ==HAL_ADC_GetState(&hadc1)));//�ȴ�ת������
	return HAL_ADC_GetValue(&hadc1);	//�������һ��ADC1�������ת�����
}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
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
	

#if EN_USART1_RX   //���ʹ���˽���
u8 RxData;
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA=0;       //����״̬���	
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
//��ȡ���ڷ����ֽ�
//@*pdata : ��ȡ���ݻ����ַ
//@ rval: 1 ��ȡ�ɹ���0: ��ȡʧ��
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

 




