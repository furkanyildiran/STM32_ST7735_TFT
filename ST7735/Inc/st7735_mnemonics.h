#ifdef __cplusplus
extern "C"{
#endif
#ifndef __ST7735_MNEMONICS_H__
#define __ST7735_MNEMONICS_H__
#include "stm32f1xx_hal.h"

/*COMMANDS BEGIN*/
#define	NOP 			0x00
#define SWRESET			0x01
#define RDDID			0x04
#define RDDRST			0x09
#define RDDPM			0x0A
#define RDD_MADCTL		0x0B
#define	RDD_COLMOD		0x0C
#define RDDIM			0x0D
#define RDDSM			0x0E
#define SLPIN			0x10
#define SLPOUT			0x11
#define PTLON			0x12
#define NORON			0x13
#define INVOFF			0x20
#define INVON			0x21
#define GAMSET			0x26
#define DISPOFF			0x28
#define DISPON			0x29
#define CASET			0x2A
#define RASET			0x2B
#define RAMWR			0x2C
#define RAMRD			0x2E
#define PTLAR			0x30
#define TEOFF			0x34
#define TEON			0x35
#define MADCTL			0x36
#define IDMOFF			0x38
#define IDMON			0x39
#define COLMOD			0x3A
#define RDID1			0xDA
#define RDID2			0xDB
#define RDID3			0xDC

#endif/*__ST7735_MNEMONICS_H__*/
#ifdef __cplusplus
}
#endif
