#include "st7735.h"

static inline void resetHW(void);
static void send_command(uint8_t cmd);
static void send_byte(uint8_t byte);
static void send_data(uint8_t buff[], uint16_t size);
static SPI_HandleTypeDef *spi_ptr;

typedef union{
	struct{
		uint8_t :8;
		uint8_t start;
		uint8_t :8;
		uint8_t end;
	};
	uint8_t reg_val[4];
}Window_t;

static Window_t x={.start=0, .end=ST7735_TFT_DEFAULT_XMAX_ADDR}, y={.start=0, .end=ST7735_TFT_DEFAULT_YMAX_ADDR};


void ST7735_TFT_init(SPI_HandleTypeDef *hspi_ptr){
	spi_ptr = hspi_ptr;
	SET_PIN(CS_PORT,CS);
	SET_PIN(RST_PORT,RST);
	SET_PIN(DC_PORT,DC);
	resetHW();
	send_command(SLPOUT);
	send_command(DISPON);
	HAL_Delay(300);
	ST7735_TFT_setColorMod(BitPerPixel_16);
	ST7735_TFT_setWindow(x.start, x.end, y.start, y.end);
}

void ST7735_TFT_setXBoundary(uint8_t x_start, uint8_t x_end){
	x.start = x_start;
	x.end = x_end;
	send_command(CASET);
	RST_PIN(CS_PORT, CS);
	send_data(x.reg_val, 4);
	SET_PIN(CS_PORT, CS);
}

void ST7735_TFT_setYBoundary(uint8_t y_start, uint8_t y_end){
	y.start = y_start;
	y.end = y_end;
	send_command(RASET);
	RST_PIN(CS_PORT, CS);
	send_data(y.reg_val, 4);
	SET_PIN(CS_PORT, CS);
}

void ST7735_TFT_setWindow(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end){
	ST7735_TFT_setXBoundary(x_start, x_end);
	ST7735_TFT_setYBoundary(y_start, y_end);
}

void ST7735_TFT_setColorMod(COLMOD_arg_t colmod){
	send_command(COLMOD);
	send_byte(colmod);
}

void ST7735_TFT_fillScreen(Colors_t color){
	send_command(RAMWR);
	uint16_t pixel_num = ((x.end+1)-(x.start))*((y.end+1)-(y.start));
	uint8_t buff[2]={(color>>8), color&0xFF};
	RST_PIN(CS_PORT, CS);
	for(uint16_t i = 0; i < pixel_num; i++){
		send_data(buff, 2);
	}
	SET_PIN(CS_PORT, CS);
}

__attribute__((always_inline)) static inline void resetHW(void){
	RST_PIN(RST_PORT, RST);
	HAL_Delay(5);
	SET_PIN(RST_PORT, RST);
	HAL_Delay(200); //after max 120ms resetting cancel occurs
}

static void send_command(uint8_t cmd){
	RST_PIN(DC_PORT, DC);
	send_byte(cmd);
	SET_PIN(DC_PORT, DC);
}

static void send_byte(uint8_t byte){
	RST_PIN(CS_PORT, CS);
	HAL_SPI_Transmit(spi_ptr, &byte, 1, 1000);
	SET_PIN(CS_PORT, CS);
}

static void send_data(uint8_t buff[], uint16_t size){
	HAL_SPI_Transmit(spi_ptr, buff, size, 1000);
}





