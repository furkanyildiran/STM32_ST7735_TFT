#ifdef __cplusplus
extern "C"{
#endif
#ifndef __ST7735_H__
#define __ST7735_H__
#include "stm32f1xx_hal.h"
#include "st7735_config.h"
#include "st7735_mnemonics.h"

#define SET_PIN(port, pin)	(port->ODR |= (1 << pin))
#define RST_PIN(port, pin)	(port->ODR &=~(1 << pin))

void ST7735_TFT_init(SPI_HandleTypeDef *hspi_ptr);

#endif/*__ST7735_H__*/
#ifdef __cplusplus
}
#endif
