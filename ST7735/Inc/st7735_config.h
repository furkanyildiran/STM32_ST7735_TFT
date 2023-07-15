#ifdef __cplusplus
extern "C"{
#endif
#ifndef __ST7735_CONFIG_H__
#define __ST7735_CONFIG_H__
#include "stm32f1xx_hal.h"

//if free rtos is used remove comment of below line
//#define FREE_RTOS_USED 	0

#define CS_PORT		GPIOC
#define DC_PORT		GPIOC
#define RST_PORT	GPIOC
#define CS		 	15
#define DC		 	13
#define RST		 	14

#endif/*__ST7735_CONFIG_H__*/
#ifdef __cplusplus
}
#endif
