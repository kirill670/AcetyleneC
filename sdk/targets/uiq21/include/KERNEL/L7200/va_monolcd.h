// VA_MONOLCD.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//


#ifndef __VA_MONOLCD_H__
#define __VA_MONOLCD_H__


/////////////////////Mono Lcd Stuff///////////////////////////////////
///////////////////////////Mono Lcd Stuff///////////////////////////////

#define MLCD_BASE     0x5800F000

#define MLCDCON       (MLCD_BASE + 0x000)
#define MPALLSW       (MLCD_BASE + 0x004)
#define MPALMSW       (MLCD_BASE + 0x008)
#define MLCDBASE      (MLCD_BASE + 0x00C)
#define MLCDCAR       (MLCD_BASE + 0x010)
#define MLCDID        (MLCD_BASE + 0x014)
#define MLCDTIMING0   (MLCD_BASE + 0x018)
#define MLCDTIMING1   (MLCD_BASE + 0x01C)

typedef enum {
    OFF = 0,
    ON  = 1
} EnableStatus;

typedef enum {
    SUCCESS = 0,
    FAIL = 1
} ReturnStatus;

typedef enum {
    MLCD_SDRAM_External = 0,
    MLCD_SRAM_Onchip = 1
} MLCD_SRAM_Type;

typedef enum {
    MLCD_1Bpp = 0,
    MLCD_2Bpp = 2,
    MLCD_4Bpp = 3
} MLCD_Bpp;

typedef enum {
    MLCD_Normal_Order  = 0,
    MLCD_Reverse_Order = 1
} MLCD_Alter_PixelOrder;

typedef struct
{
    unsigned long uWidth;       // line length, multiple of 16 pixels(16-1024)
    unsigned long uHeight;      // total number of lines per LCD panel(1-512)
    unsigned long uClock;       // LCD controller clock (BCLK) in Hz
    unsigned long uRefresh;     // LCD screen refresh rate in Hz (the closest match is chosen)
   
    MLCD_SRAM_Type tSRAMType;   // SRAM enable
    unsigned long  uACBias;     // number of line clock periods between each toggle of AC-bias pin
    MLCD_Bpp       tBpp ;		// bits per pixel

    MLCD_Alter_PixelOrder tAlterPixelOrder; // Mono LCD Alternative Pixel Order
    unsigned long uHSync;       // horizontal sync pulse width
    unsigned long uHFrontPorch; // horizontal front porch(1-256)
    unsigned long uHBackProch;  // horizontal back porch(1-256)

    unsigned long uClockPulse;  // number of clock pulses per line , generally should be (n_lines/4) - 1
    unsigned long uVSync;       // vertical sync pulse width
    unsigned long uVFrontPorch; // vertical front porch(0-255)
    unsigned long uVBackPorch;  // vertical back porch(0-255)
} MLCD_Parameter;


typedef struct {
    unsigned long ulBase;
    unsigned char ucOffset;
    unsigned char ucWidth;
} RegisterMono;


 
class TL7200MonoLCD

	{

public:
  
	IMPORT_C static void REG_SetBits(RegisterMono *pReg, unsigned long ulValue);

	IMPORT_C static unsigned long REG_GetBits(RegisterMono *pReg);

	IMPORT_C static void MLCD_EnableLCD(EnableStatus nEnable);
	IMPORT_C static void MLCD_EnableVEE(EnableStatus nEnable);

	IMPORT_C static int MLCD_InitVideo(void);

	IMPORT_C static void MLCD_SetContrast(int nContrast);

	IMPORT_C static void MLCD_SetParameter(MLCD_Parameter *pMLCDParam);
	IMPORT_C static void MLCD_GetParameter(MLCD_Parameter *pMLCDParam);
 
	IMPORT_C static int MLCD_GetPalette(unsigned char *pPalette, int nColors);
	IMPORT_C static int MLCD_SetPalette(unsigned char *pPalette, int nColors);

	IMPORT_C static void MLCD_SetFrameBufferLinearAddr(unsigned long uBaseAddr);
	IMPORT_C static unsigned long MLCD_GetFrameBufferLinearAddr(void);
 
	IMPORT_C static void MLCD_SetFrameBuffer(unsigned int dmaBase);

	IMPORT_C static void MLCD_SetFrameBufferAddress(unsigned int address);
	IMPORT_C static unsigned int MLCD_GetFrameBufferAddress(void);

protected:
 

private:


	};
 
#endif