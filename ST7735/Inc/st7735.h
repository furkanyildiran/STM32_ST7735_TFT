#ifdef __cplusplus
extern "C"{
#endif
#ifndef __ST7735_H__
#define __ST7735_H__
#include "stm32f1xx_hal.h"
#include "st7735_config.h"
#include "st7735_mnemonics.h"

#define R_BIT_POS	11
#define G_BIT_POS	6
#define B_BIT_POS	0
#define SET_PIN(port, pin)		(port->ODR |= (1 << pin))
#define RST_PIN(port, pin)		(port->ODR &=~(1 << pin))
#define SET_RGB_COLOR565(R,G,B)	((R << R_BIT_POS) | (G << G_BIT_POS) | (B << B_BIT_POS))

void ST7735_TFT_init(SPI_HandleTypeDef *hspi_ptr);
void ST7735_TFT_setXBoundary(uint8_t x_start, uint8_t x_end);
void ST7735_TFT_setYBoundary(uint8_t y_start, uint8_t y_end);
void ST7735_TFT_setWindow(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);
void ST7735_TFT_setColorMod(COLMOD_arg_t colmod);
void ST7735_TFT_fillScreen(Colors_t color);
void ST7735_TFT_writeText(uint8_t x, uint8_t y, Colors_t text_color, Colors_t background);

#endif/*__ST7735_H__*/
#ifdef __cplusplus
}
#endif
