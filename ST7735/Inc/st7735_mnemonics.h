#ifdef __cplusplus
extern "C"{
#endif
#ifndef __ST7735_MNEMONICS_H__
#define __ST7735_MNEMONICS_H__

#define ST7735_TFT_WIDTH				128
#define ST7735_TFT_HEIGHT				160
#define ST7735_TFT_PIXEL_NUM 			(ST7735_TFT_WIDTH*ST7735_TFT_HEIGHT)
#define ST7735_TFT_DEFAULT_XMAX_ADDR	(ST7735_TFT_WIDTH-1)
#define ST7735_TFT_DEFAULT_YMAX_ADDR	(ST7735_TFT_HEIGHT-1)


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

/*GAMSET command argument*/
typedef enum{
	GammaCurveDefault = 1,
	GammaCurve1 = 1,
	GammaCurve2 = 2,
	GammaCurve3 = 4,
	GammaCurve4 = 8
}GAMSET_arg_t;

/*MADCTL commad arguments*/
typedef enum{
	MXorder_RightToLeft = 1,
	MXorder_LeftToRight = 0,
	MYorder_BottomToTop = 1,
	MYorder_TopTobottom = 0,
	MVorder_Exchange = 1,
	MVorder_Normal = 0,
	MLorder_BottomToTop = 1,
	MLorder_TopToBottom = 0,
	RGBorder_BGR = 1,
	RGBorder_RGB = 0,
	MHorder_LeftToRight = 0,
	MHorder_RightToLeft = 1
}MADCTL_arg_t;

/*COLMOD command arguments*/
typedef enum{
	BitPerPixel_12 = 3,
	BitPerPixel_16 = 5,
	BitPerPixel_18 = 6
}COLMOD_arg_t;

/*Colors for BitPerPixel_16 setting*/
typedef enum{
	BLACK = 0,
	WHITE = 65535,
	RED = 63488,
	GREEN = 2016,
	BLUE = 31,
	YELLOW = 65504,
	ORANGE = 64512,
	MAGENTA = 63519,
	PURPLE = 30735,
	PURPLE2 = 32784
}Colors_t;

/*Orientation*/
typedef enum{
	VERTICAL,
	TURN180_DEGREES,
	LANDSCAPE,
	TURN270_DEGREES,
}Orientation_t;

typedef enum{
	SLEEP_OUT = SLPOUT,
	SLEEP_IN = SLPIN
}DisplaySleepSetting_t;

typedef enum{
	DISPLAY_ON = DISPON,
	DISPLAY_OFF = DISPOFF
}DisplayOnOff_t;

typedef enum{
	INVERT = INVON,
	NON_INVERT = INVOFF
}DisplayInvertSetting_t;



#endif/*__ST7735_MNEMONICS_H__*/
#ifdef __cplusplus
}
#endif
