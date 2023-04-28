#include "st7735.h"

static inline void resetHW(void);
static void send_command(uint8_t cmd);
static void send_byte(uint8_t byte);
static SPI_HandleTypeDef *spi_ptr;


void ST7735_TFT_init(SPI_HandleTypeDef *hspi_ptr){
	spi_ptr = hspi_ptr;
	SET_PIN(GPIOA,CS);
	SET_PIN(GPIOA,RST);
	SET_PIN(GPIOA,DC);
	resetHW();
	send_command(0x11);
	send_command(0x29);

	send_command(0x3A);
	send_byte(0x05);

	send_command(CASET);
	send_byte(127);
	send_command(RASET);
	send_byte(159);
	send_command(RAMWR);
	RST_PIN(GPIOA, CS);
	for(uint16_t i = 0; i < 40960; i++){
		uint8_t data = 4;
		HAL_SPI_Transmit(hspi_ptr, &data, 1, 1000);
		HAL_Delay(2);
	}
	SET_PIN(GPIOA, CS);

	send_command(CASET);
	send_byte(127);
	send_command(RASET);
	send_byte(159);
	send_command(RAMWR);
	RST_PIN(GPIOA, CS);
	for(uint16_t i = 0; i < 40960; i++){
		uint8_t data = 255;
		HAL_SPI_Transmit(hspi_ptr, &data, 1, 1000);
		HAL_Delay(1);
	}
}



__attribute__((always_inline)) static inline void resetHW(void){
	RST_PIN(GPIOA, RST);
	HAL_Delay(5);
	SET_PIN(GPIOA, RST);
	HAL_Delay(200); //after max 120ms resetting cancel occurs
}

static void send_command(uint8_t cmd){
	RST_PIN(GPIOA, CS);
	RST_PIN(GPIOA, DC);
	HAL_SPI_Transmit(spi_ptr, &cmd, 1, 1000);
	SET_PIN(GPIOA, DC);
	SET_PIN(GPIOA, CS);
}
static void send_byte(uint8_t byte){
	RST_PIN(GPIOA, CS);
	HAL_SPI_Transmit(spi_ptr, &byte, 1, 1000);
	SET_PIN(GPIOA, CS);
}


