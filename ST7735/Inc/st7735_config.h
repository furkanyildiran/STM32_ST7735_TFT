#ifdef __cplusplus
extern "C"{
#endif
#ifndef __ST7735_CONFIG_H__
#define __ST7735_CONFIG_H__
#include "stm32f1xx_hal.h"

#define CS_PORT		GPIOA
#define DC_PORT		GPIOA
#define RST_PORT	GPIOA
#define CS		 	2
#define DC		 	1
#define RST		 	3

#endif/*__ST7735_CONFIG_H__*/
#ifdef __cplusplus
}
#endif
