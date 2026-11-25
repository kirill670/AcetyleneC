// v32UCB12.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

//
// Definitions for the Philips UCB1200 Advanced modem/audio 
// analog front-end
//

#ifndef __V32UCB12_H__
#define __V32UCB12_H__

//                               
// Hardware addresses and constants
//

// Address 0
// IO Port data register
#define UCB0_IO_DATA0		0x0001
#define UCB0_IO_DATA1		0x0002
#define UCB0_IO_DATA2		0x0004
#define UCB0_IO_DATA3		0x0008
#define UCB0_IO_DATA4		0x0010
#define UCB0_IO_DATA5		0x0020
#define UCB0_IO_DATA6		0x0040
#define UCB0_IO_DATA7		0x0080
#define UCB0_IO_DATA8		0x0100
#define UCB0_IO_DATA9		0x0200


// Address 1
// IO Port direction register
#define UCB1_IO_DIR0		0x0001
#define UCB1_IO_DIR1		0x0002
#define UCB1_IO_DIR2		0x0004
#define UCB1_IO_DIR3		0x0008
#define UCB1_IO_DIR4		0x0010
#define UCB1_IO_DIR5		0x0020
#define UCB1_IO_DIR6		0x0040
#define UCB1_IO_DIR7		0x0080
#define UCB1_IO_DIR8		0x0100
#define UCB1_IO_DIR9		0x0200
#define UCB1_SIB_ZERO		0x8000


// Address 2
// Rising Edge interrupt enable register
#define UCB2_IO_RIS_INT0		0x0001
#define UCB2_IO_RIS_INT1		0x0002
#define UCB2_IO_RIS_INT2		0x0004
#define UCB2_IO_RIS_INT3		0x0008
#define UCB2_IO_RIS_INT4		0x0010
#define UCB2_IO_RIS_INT5		0x0020
#define UCB2_IO_RIS_INT6		0x0040
#define UCB2_IO_RIS_INT7		0x0080
#define UCB2_IO_RIS_INT8		0x0100
#define UCB2_IO_RIS_INT9		0x0200
#define UCB2_ADC_RIS_INT		0x0800
#define UCB2_TSPX_RIS_INT		0x1000
#define UCB2_TSMX_RIS_INT		0x2000
#define UCB2_TCLIP_RIS_INT		0x4000
#define UCB2_ACLIP_RIS_INT		0x8000

// Address 3
// Falling Edge interrupt enable register
#define UCB3_IO_FAL_INT0		0x0001
#define UCB3_IO_FAL_INT1		0x0002
#define UCB3_IO_FAL_INT2		0x0004
#define UCB3_IO_FAL_INT3		0x0008
#define UCB3_IO_FAL_INT4		0x0010
#define UCB3_IO_FAL_INT5		0x0020
#define UCB3_IO_FAL_INT6		0x0040
#define UCB3_IO_FAL_INT7		0x0080
#define UCB3_IO_FAL_INT8		0x0100
#define UCB3_IO_FAL_INT9		0x0200
#define UCB3_ADC_FAL_INT		0x0800
#define UCB3_TSPX_FAL_INT		0x1000
#define UCB3_TSMX_FAL_INT		0x2000
#define UCB3_TCLIP_FAL_INT		0x4000
#define UCB3_ACLIP_FAL_INT		0x8000


// Address 4
// Interrupt clear/status register
#define UCB4_IO_INT_CLR0		0x0001
#define UCB4_IO_INT_CLR1		0x0002
#define UCB4_IO_INT_CLR2		0x0004
#define UCB4_IO_INT_CLR3		0x0008
#define UCB4_IO_INT_CLR4		0x0010
#define UCB4_IO_INT_CLR5		0x0020
#define UCB4_IO_INT_CLR6		0x0040
#define UCB4_IO_INT_CLR7		0x0080
#define UCB4_IO_INT_CLR8		0x0100
#define UCB4_IO_INT_CLR9		0x0200
#define UCB4_ADC_INT_CLR		0x0800
#define UCB4_TSPX_INT_CLR		0x1000
#define UCB4_TSMX_INT_CLR		0x2000
#define UCB4_TCLIP_INT_CLR		0x4000
#define UCB4_ACLIP_INT_CLR		0x8000

#define UCB4_IO_INT_STAT0		0x0001
#define UCB4_IO_INT_STAT1		0x0002
#define UCB4_IO_INT_STAT2		0x0004
#define UCB4_IO_INT_STAT3		0x0008
#define UCB4_IO_INT_STAT4		0x0010
#define UCB4_IO_INT_STAT5		0x0020
#define UCB4_IO_INT_STAT6		0x0040
#define UCB4_IO_INT_STAT7		0x0080
#define UCB4_IO_INT_STAT8		0x0100
#define UCB4_IO_INT_STAT9		0x0200
#define UCB4_ADC_INT_STAT		0x0800
#define UCB4_TSPX_INT_STAT		0x1000
#define UCB4_TSMX_INT_STAT		0x2000
#define UCB4_TCLIP_INT_STAT		0x4000
#define UCB4_ACLIP_INT_STAT		0x8000


// Address 5
// Telecom control register A
#define UCB5_TEL_DIV_DATA		0x007F
#define UCB5_TEL_DIV_SHIFT		0
#define UCB5_TEL_LOOP			0x0080


// Address 6
// Telecom control register B
#define UCB6_TEL_VOICE_ENA		0x0008
#define UCB6_TEL_CLIP_STAT		0x0010
#define UCB6_TEL_CLIP_CLR		0x0010
#define UCB6_TEL_ATT			0x0040
#define UCB6_TEL_SIDE_ENA		0x0800
#define UCB6_TEL_MUTE			0x2000
#define UCB6_TEL_IN_ENA			0x4000
#define UCB6_TEL_OUT_ENA		0x8000


// Address 7
// Audio control register A
#define UCB7_AUD_DIV_MASK		0x007F
#define UCB7_AUD_DIV_SHIFT		0
#define UCB7_AUD_GAIN_MASK		0x0F80
#define UCB7_AUD_GAIN_SHIFT		7


// Address 8
// Audio control register B
#define UCB8_AUD_ATT_MASK		0x001F
#define UCB8_AUD_ATT_SHIFT		0
#define UCB8_AUD_CLIP_STAT		0x0040
#define UCB8_AUD_CLIP_CLR		0x0040
#define UCB8_AUD_LOOP			0x0100
#define UCB8_AUD_MUTE			0x2000
#define UCB8_AUD_IN_ENA			0x4000
#define UCB8_AUD_OUT_ENA		0x8000


// Address 9
// Touchscreen control register
#define UCB9_TSMX_POW			0x0001
#define UCB9_TSPX_POW			0x0002
#define UCB9_TSMY_POW			0x0004
#define UCB9_TSPY_POW			0x0008
#define UCB9_TSMX_GND			0x0010
#define UCB9_TSPX_GND			0x0020
#define UCB9_TSMY_GND			0x0040
#define UCB9_TSPY_GND			0x0080

#define UCB9_MODE_INT			0x0000
#define UCB9_MODE_PRES			0x0100
#define UCB9_MODE_POS			0x0200
#define UCB9_TCS_BIAS_ENA		0x0800

#define UCB9_TSPX_LOW			0x1000
#define UCB9_TSMX_LOW			0x2000


// Address 10
// ADC control register
#define UCB10_ADC_SYNC_ENA		0x0001
#define UCB10_VREFBYP_CON		0x0002

#define UCB10_ADC_INPUT_TSPX	0x0000
#define UCB10_ADC_INPUT_TSMX	0x0004
#define UCB10_ADC_INPUT_TSPY	0x0008
#define UCB10_ADC_INPUT_TSMY	0x000C
#define UCB10_ADC_INPUT_AD0		0x0010
#define UCB10_ADC_INPUT_AD1		0x0014
#define UCB10_ADC_INPUT_AD2		0x0018
#define UCB10_ADC_INPUT_AD3		0x001C

#define UCB10_EXT_REF_ENA		0x0020
#define UCB10_ADC_START			0x0080
#define UCB10_ADC_ENA			0x8000


// Address 11
// ADC data register
#define UCB11_ADC_DATA_MASK		0x7FE0
#define UCB11_ADC_DATA_SHIFT	5
#define UCB11_ADC_DAT_VAL		0x8000


// Address 12
// ID register
#define UCB12_VERSION_MASK		0x003F
#define UCB12_VERSION_SHIFT		0
#define UCB12_DEVICE_MASK		0x0FC0
#define UCB12_DEVICE_SHIFT		6
#define UCB12_SUPPLIER_MASK		0xF000
#define UCB12_SUPPLIER_SHIFT	12


// Address 13
// MODE register
#define UCB13_AUD_TEST				0x0001
#define UCB13_TEL_TEST				0x0002
#define UCB13_PROD_TEST_MODE_MASK	0x003C
#define UCB13_DYN_VFLAG_ENA			0x1000
#define UCB13_AUD_OFF_CAN			0x2000


// Address 14
// Reserved


// Address 15
// NULL register
// Returns 0xFFFF at all times

#endif
