#ifndef _INVERTER_MIDDLEWARES_H
#define _INVERTER_MIDDLEWARES_H

//******************************************************
//					adc configure
//******************************************************
u16 Get_Adc_Average(u8 ch,u8 times);

//******************************************************
//					usart configure
//******************************************************
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
///串口接收缓冲索引
typedef struct {
	u8  head;
	u8  tail;
}UART1_BUF_INFO;  
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern u8 RxData;
extern UART1_BUF_INFO  UART1_Rev;

void Usart1_Iint(void);
void Usart1_sendByte(u16 Data );
 u8 Usart1_readByte(u8 *pdata);

#endif

