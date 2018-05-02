#ifndef _INVERTER_MIDDLEWARES_H
#define _INVERTER_MIDDLEWARES_H

//******************************************************
//					adc configure
//******************************************************
u16 Get_Adc_Average(u8 ch,u8 times);

//******************************************************
//					usart configure
//******************************************************
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
///���ڽ��ջ�������
typedef struct {
	u8  head;
	u8  tail;
}UART1_BUF_INFO;  
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern u8 RxData;
extern UART1_BUF_INFO  UART1_Rev;

void Usart1_Iint(void);
void Usart1_sendByte(u16 Data );
 u8 Usart1_readByte(u8 *pdata);

#endif

