#ifndef _INVERTER_TEST_H
#define _INVERTER_TEST_H

typedef  unsigned char  u8;
typedef  unsigned short  u16;
typedef  unsigned long  u32;


//测试步骤
enum{
   TEST_INIT,//  测试初始化
   TEST_OPEN_LOOP,   //开环测试
   TEST_OVERLOAD,//过载测试
   TEST_SHORT_CIRCUIT,//短路测试
   TEST_OVER_TEMPRATURE,//过温测试
   TEST_UART,//串口测试
   TEST_STOP,//
};


///测试停止状态
enum{
	TEST_STOP_SUCCESS,		// 测试成功
	TEST_STOP_OPEN_LOOP,		//开环测试失败
	TEST_STOP_OVER_LOAD,		//过载测试失败	
	TEST_STOP_SHORT_CIRCUIT,//短路测试失败	
	TEST_STOP_OVER_TEMP,		//过温测试失败	
	TEST_STOP_UART, 			//串口测试失败	

};



void TEST_Init(void);
void TEST_Proc(void);



#endif

