#ifndef _INVERTER_TEST_H
#define _INVERTER_TEST_H

typedef  unsigned char  u8;
typedef  unsigned short  u16;
typedef  unsigned long  u32;


//���Բ���
enum{
   TEST_INIT,//  ���Գ�ʼ��
   TEST_OPEN_LOOP,   //��������
   TEST_OVERLOAD,//���ز���
   TEST_SHORT_CIRCUIT,//��·����
   TEST_OVER_TEMPRATURE,//���²���
   TEST_UART,//���ڲ���
   TEST_STOP,//
};


///����ֹͣ״̬
enum{
	TEST_STOP_SUCCESS,		// ���Գɹ�
	TEST_STOP_OPEN_LOOP,		//��������ʧ��
	TEST_STOP_OVER_LOAD,		//���ز���ʧ��	
	TEST_STOP_SHORT_CIRCUIT,//��·����ʧ��	
	TEST_STOP_OVER_TEMP,		//���²���ʧ��	
	TEST_STOP_UART, 			//���ڲ���ʧ��	

};



void TEST_Init(void);
void TEST_Proc(void);



#endif

