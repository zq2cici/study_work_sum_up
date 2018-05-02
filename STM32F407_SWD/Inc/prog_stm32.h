/**
  ******************************************************************************
  * @file           : prog_stm32.h
  * @brief          : Header for prog_stm32.c file.
  *                   This file programs stm32 use fatfs .
  ******************************************************************************
  */
#ifndef __PROG_STM32_H__
#define __PROG_STM32_H__

#include "stm32f4xx_hal.h"

	uint8_t prog_stm32_use_fatfs(uint32_t onceProgSize);
	uint8_t gen_bin_file(void);
	
	#endif
	
	
	

