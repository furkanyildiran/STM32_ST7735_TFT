#include "st7735.h"

static inline void resetHW(void);
static void delay(uint16_t d_time);
static void send_command(uint8_t cmd);
static void send_byte(uint8_t byte);
static void send_data(uint8_t buff[], uint16_t size);
static void send_pixelVal(Colors_t color);
static void setGammaCurve(GAMSET_arg_t gamma_curve);
static SPI_HandleTypeDef *spi_ptr;


static union{
	struct{
		uint8_t :8;
		uint8_t start;
		uint8_t :8;
		uint8_t end;
	};
	uint8_t reg_val[4];
}WindowX={.start=0, .end=ST7735_TFT_DEFAULT_XMAX_ADDR}, WindowY={.start=0, .end=ST7735_TFT_DEFAULT_YMAX_ADDR};

static struct{
	uint8_t height;
	uint8_t width;
	uint8_t orienation;
}Screen={.height = ST7735_TFT_HEIGHT, .width = ST7735_TFT_WIDTH, .orienation = VERTICAL};

static union{
	struct{
		uint8_t:1;
		uint8_t:1;
		uint8_t MH:1;
		uint8_t RGB:1;
		uint8_t ML:1;
		uint8_t MV:1;
		uint8_t MX:1;
		uint8_t MY:1;
	}bits;
	uint8_t reg_val;
}Madctl={.reg_val=0};

void ST7735_TFT_init(SPI_HandleTypeDef *hspi_ptr){
	spi_ptr = hspi_ptr;
	SET_PIN(CS_PORT,CS);
	SET_PIN(RST_PORT,RST);
	SET_PIN(DC_PORT,DC);
	resetHW();
	ST7735_TFT_Sleep(SLEEP_OUT);
	ST7735_TFT_OnOff(DISPLAY_ON);
	delay(300);
	ST7735_TFT_setColorMod(BitPerPixel_16);
	ST7735_TFT_setWindow(WindowX.start, WindowX.end, WindowY.start, WindowY.end);
}

void ST7735_TFT_setXBoundary(uint8_t x_start, uint8_t x_end){
	WindowX.start = x_start;
	WindowX.end = x_end;
	send_command(CASET);
	RST_PIN(CS_PORT, CS);
	send_data(WindowX.reg_val, 4);
	SET_PIN(CS_PORT, CS);
}

void ST7735_TFT_setYBoundary(uint8_t y_start, uint8_t y_end){
	WindowY.start = y_start;
	WindowY.end = y_end;
	send_command(RASET);
	RST_PIN(CS_PORT, CS);
	send_data(WindowY.reg_val, 4);
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

void ST7735_TFT_setOrientation(Orientation_t orientation){
	Madctl.reg_val=0;
	Screen.orienation = orientation;

	switch(orientation){
	case TURN180_DEGREES:
		Madctl.bits.MX = 1;
		Madctl.bits.MY = 1;
		Screen.height = ST7735_TFT_HEIGHT;
		Screen.width = ST7735_TFT_WIDTH;
		break;
	case VERTICAL:
		Screen.height = ST7735_TFT_HEIGHT;
		Screen.width = ST7735_TFT_WIDTH;
		break;
	case LANDSCAPE:
		Screen.height = ST7735_TFT_WIDTH;
		Screen.width = ST7735_TFT_HEIGHT;
		Madctl.bits.MV = 1;
		Madctl.bits.MX = 1;
		break;
	case TURN270_DEGREES:
		Screen.height = ST7735_TFT_WIDTH;
		Screen.width = ST7735_TFT_HEIGHT;
		Madctl.bits.MV = 1;
		Madctl.bits.MY = 1;
		break;
	}
	send_command(MADCTL);
	send_byte(Madctl.reg_val);
}

void ST7735_TFT_Paint(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end, Colors_t color){
	ST7735_TFT_setWindow(x_start, x_end, y_start, y_end);
	send_command(RAMWR);
	uint8_t buff[2]={(color>>8), color&0xFF};
	RST_PIN(CS_PORT, CS);
	for(uint16_t i = 0; i < ((x_end-x_start)+1)*((y_end-y_start)+1); i++){
		send_data(buff, 2);
	}
	SET_PIN(CS_PORT, CS);
}

void ST7735_TFT_Sleep(DisplaySleepSetting_t setting){
	send_command(setting);
}

void ST7735_TFT_Invert(DisplayInvertSetting_t setting){
	send_command(setting);
}

void ST7735_TFT_OnOff(DisplayOnOff_t status){
	send_command(status);
}

void ST7735_TFT_fillScreen(Colors_t color){
	ST7735_TFT_setWindow(0, Screen.width, 0, Screen.height);
	send_command(RAMWR);
	uint8_t buff[2]={(color>>8), color&0xFF};
	RST_PIN(CS_PORT, CS);
	for(uint16_t i = 0; i < ST7735_TFT_PIXEL_NUM; i++){
		send_data(buff, 2);
	}
	SET_PIN(CS_PORT, CS);
}

void ST7735_TFT_writeChar(char ch, uint8_t x_addr, uint8_t y_addr, Colors_t charColor, Colors_t backgroundColor){
	ST7735_TFT_setWindow(x_addr, x_addr+7, y_addr, y_addr+7);
	send_command(RAMWR);
	RST_PIN(CS_PORT, CS);
	for(uint8_t i = 0; i < 8; i++){
		for(int8_t j = 7; j >= 0; j--){
			uint16_t val = getChar((uint8_t)(ch-0x20), i)>>j;
			if((val&1)==1)send_pixelVal(charColor);
			else send_pixelVal(backgroundColor);
		}
	}
	SET_PIN(CS_PORT, CS);
}

void ST7735_TFT_writeString(char text[], uint8_t x_addr, uint8_t y_addr, Colors_t charColor, Colors_t backgroundColor){
	for(uint8_t i = 0; text[i] != '\0'; i++, x_addr+=8){
		if((x_addr + 8) > (Screen.width)){
			y_addr += 9;
			x_addr = 0;
		}
		ST7735_TFT_writeChar(text[i], x_addr, y_addr, charColor, backgroundColor);
	}
}

__attribute__((unused)) static void setGammaCurve(GAMSET_arg_t gamma_curve){
	send_command(GAMSET);
	send_byte(gamma_curve);
}

__attribute__((always_inline)) static inline void resetHW(void){
	RST_PIN(RST_PORT, RST);
	delay(5);
	SET_PIN(RST_PORT, RST);
	delay(200); //after max 120ms resetting cancel occurs
}

static void delay(uint16_t d_time){
#ifdef FREE_RTOS_USED
	osDelay(d_time);
#else
	HAL_Delay(d_time);
#endif
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




