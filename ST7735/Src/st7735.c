#include "st7735.h"

static inline void resetHW(void);
static void send_command(uint8_t cmd);
static void send_byte(uint8_t byte);
static void send_data(uint8_t buff[], uint16_t size);
static void send_pixelVal(Colors_t color);
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
static uint8_t arr[16][8]={
		{0x10,0x38,0x6C,0xC6,0xFE,0xFE,0x82,0x82},
		{0x7C,0x66,0x66,0x7C,0x7E,0x66,0x66,0x7C},
		{0x3C,0x66,0xE2,0xC0,0xC0,0xE2,0x66,0x3C},
		{0x7C,0x66,0x66,0x66,0x66,0x66,0x66,0x7C},
		{0x7E,0x60,0x60,0x7C,0x7C,0x60,0x60,0x7E},
		{0xFC,0xFC,0xC0,0xF8,0xF8,0xC0,0xC0,0xC0},
		{0x3C,0x66,0xE2,0xC0,0xCE,0xE6,0xE6,0x7E},
		{0xC6,0xC6,0xC6,0xFE,0xFE,0xC6,0xC6,0xC6},
		{0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18},
		{0x3E,0x3E,0x06,0x06,0x06,0x66,0x3E,0x1C},
		{0xC6,0xCC,0xD8,0xF0,0xF8,0xCC,0xC6,0xC2},
		{0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFE,0xFE},
		{0x82,0xC6,0xEE,0xFE,0xBA,0x92,0x82,0x82},
		{0xC2,0xE2,0xF2,0xBA,0x9E,0x8E,0x86,0x82},
		{0x38,0x7C,0xEE,0xC6,0xC6,0xEE,0x7C,0x38},
		{0x3C,0x66,0x66,0x66,0x7C,0x60,0x60,0x60}
};

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
	ST7735_TFT_setWindow(0, ST7735_TFT_DEFAULT_XMAX_ADDR, 0, ST7735_TFT_DEFAULT_YMAX_ADDR);
	send_command(RAMWR);
	uint8_t buff[2]={(color>>8), color&0xFF};
	RST_PIN(CS_PORT, CS);
	for(uint16_t i = 0; i < ST7735_TFT_PIXEL_NUM; i++){
		send_data(buff, 2);
	}
	SET_PIN(CS_PORT, CS);
}

void ST7735_TFT_writeA(uint8_t ch, uint8_t x, uint8_t y){
	ST7735_TFT_setWindow(x, x+7, y, y+7);
	send_command(RAMWR);
	RST_PIN(CS_PORT, CS);
	for(uint8_t i = 0; i < 8; i++){
		for(uint8_t j = 7; j > 0; j--){
			uint16_t val = arr[ch][i]>>j;
			if((val&1)==1)send_pixelVal(YELLOW);
			else send_pixelVal(BLUE);
		}
		if((arr[ch][i]&1) == 1)send_pixelVal(YELLOW);
		else send_pixelVal(BLUE);
	}
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

static void send_pixelVal(Colors_t color){
	uint8_t buff[2]={(color>>8), color&0xFF};
	RST_PIN(CS_PORT, CS);
	send_data(buff, 2);
	SET_PIN(CS_PORT, CS);
}




