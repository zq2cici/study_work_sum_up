#ifndef _INVERTER_GPIO_H
#define _INVERTER_GPIO_H

#define ON 1
#define OFF 0

#define DAC_VOL_0p15V 150
#define DAC_VOL_0p44V 440


void TestBoardPowerOn(void);
void TestBoardPowerOff(void);
void MCU_Vbus_Output(void);
void MCU_Vinv_Output(uint8_t  state);
void TEMP_NTC_Output_Normal(void);
void TEMP_NTC_Output_Abnormal(void);
void LAOD_VOL_Output(uint16_t vol);
void i_LIMIT_Output(uint8_t  state);


#endif

