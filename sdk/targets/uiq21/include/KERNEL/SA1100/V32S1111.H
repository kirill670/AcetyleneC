// V32S1111.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

//
// Definitions for SA1111
//

#ifndef __V32S1111_H__
#define __V32S1111_H__
#include <e32std.h>
#include <k32std.h>

//----------------------------------------------------------------------------
// Constant conventions:
//----------------------------------------------------------------------------

// KH		Hardware definition
// KHw		4-byte word definition prefix
// KHb		Byte definition prefix
// KHt		Bit definition prefix
// KHm		Mask definition prefix
// KHs		Shift definition prefix
// KHo		Offset definition prefix
// KHwRo	Read-only register
// KHwWo	Write-only register
// KHwRw	Read/write register
// KHwBase	Base address within memory map
// _i		Input suffix
// _o		Output suffix
// _b		Input/output suffix

//----------------------------------------------------------------------------
// SA1111 board memory map: physical addresses
//
//	Expansion Flash			0x08000000		32Mbyte
//  CPLD System registers	0x10000000		a few locations
//  Ethernet Controller		0x18000000		1KByte
//  PCMCIA					0x20000000		3x64MByte
//  CF						0x30000000		2x2MByte
//  SA1111 registers		0x40000000		8KByte
//  Expansion SDRAM			0xD0000000		16/32/64MByte
//
//----------------------------------------------------------------------------
// SA1111 device internal memory map (offsets from base 0x40000000) - CS4
//
//	Module name				Offset		End
//	System Bus Interface	0			0x000001FF (512bytes)		
//	System Controller		0x00000200	0x000003FF (512bytes)	
//	USB Host Controller		0x00000400	0x000005FF (512bytes)
//	Serial Audio Controller 0x00000600	0x000007FF (512bytes)
//	SSP Serial Port			0x00000800	0x000009FF (512bytes)
//	PS/2 Trackpad Interface	0x00000A00	0x00000BFF (512bytes)
//	PS/2 Mouse Interface	0x00000C00	0x00000DFF (512bytes)
//	Reserved				0x00000E00	0x00000FFF (512bytes)
//	GPIO Blocks A, B, C		0x00001000	0x000011FF (512bytes)
//	Reserved				0x00001200	0x000015FF (1024bytes)
//	Interrupt Controller	0x00001600	0x000017FF (512bytes)
//	PCMCIA Interface		0x00001800	0x000019FF (512bytes)
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// SA1111: registers (32-bit access)
//----------------------------------------------------------------------------
const TUint32 KHwSA1111BaseRegisters	=	0x40000000;
const TUint32 KHoSA1111RegSpacing		=	0x200;

// Offsets to KHwSA1111BaseRegisters
// SBI
const TUint32	KHoBaseSbi				=	0x00*KHoSA1111RegSpacing;
// System Controller
const TUint32	KHoBaseSc				=	0x01*KHoSA1111RegSpacing;
// USB Host Controller
const TUint32	KHoBaseUsb				=	0x02*KHoSA1111RegSpacing;
// Serial Audio Controller
const TUint32	KHoBaseSac				=	0x03*KHoSA1111RegSpacing;
// SSP Serial Port
const TUint32	KHoBaseSsp				=	0x04*KHoSA1111RegSpacing;
// PS/2 Trackpad Interface
const TUint32	KHoBaseKbd				=	0x05*KHoSA1111RegSpacing;
// PS/2 Mouse Interface
const TUint32	KHoBaseMouse			=	0x06*KHoSA1111RegSpacing;
// GPIO Block A, B, C
const TUint32	KHoBaseGpio				=	0x08*KHoSA1111RegSpacing;
// Interrupt Controller
const TUint32	KHoBaseIntCont			=	0x0B*KHoSA1111RegSpacing;
// PCMCIA Interface
const TUint32	KHoBasePcCard			=	0x0C*KHoSA1111RegSpacing;

//
//		From here downwards we have offsets to offsets as above
//
//----------------------------------------------------------------------------
//	SBI: pages 3-15 to 3-17

// Control Register
const TUint32 KHwRwSbiSkcr			=	KHoBaseSbi;

	const TUint32 KHtSkcrPllBypass		=	KBit0;
	const TUint32 KHtSkcrRclkEn			=	KBit1;
	const TUint32 KHtSkcrSleep			=	KBit2;
	const TUint32 KHtSkcrDoze				=	KBit3;
	const TUint32 KHtSkcrVcoOff			=	KBit4;
	const TUint32 KHtSkcrScanTestEn		=	KBit5;
	const TUint32 KHtSkcrClockTestEn		=	KBit6;
	const TUint32 KHtSkcrRdyEn			=	KBit7;
	const TUint32 KHtSkcrSelAc			=	KBit8;
	const TUint32 KHtSkcrOppc				=	KBit9;
	const TUint32 KHtSkcrPllTestEn		=	KBit10;
	const TUint32 KHtSkcrUsbIoTestEn		=	KBit11;
	const TUint32 KHtSkcrOeEn				=	KBit13;		// see specification update
	const TUint32 KHmSkcrTestMask			=	KHtSkcrScanTestEn|KHtSkcrClockTestEn|KHtSkcrOppc|\
											KHtSkcrPllTestEn|KHtSkcrUsbIoTestEn;
	const TUint32 KHmSkcrBits				=	0x00002FFF;

// Shared Memory Controller Register
const TUint32 KHwRwSbiSmcr			=	KHoBaseSbi + 0x00000004;

	const TUint32 KHtSmcrDtim				=	KBit0;
	const TUint32 KHtSmcrMbge				=	KBit1;
	const TUint32 KHmSmcrDrac				=	KBit2|KBit3|KBit4;
	const TUint32 KHsSmcrDrac				=	2;
	const TUint32 KHtSmcrClat				=	KBit5;
	const TUint32 KHmSmcrSdramBits		=	KHtSmcrDtim|KHmSmcrDrac|KHtSmcrClat;
	const TUint32 KHmSmcrBits				=	0x0000003F;

// ID Register
const TUint32 KHwRoSbiSkid			=	KHoBaseSbi + 0x00000008;

	const TUint32 KHmSkidCompRev			=	0x000000FF;		// the location of these bits changed
	const TUint32 KHsSkidCompRev			=	0;				// (see specification update)
	const TUint32 KHmSkidCompId			=	0xFFFFFF00;
	const TUint32 KHsSkidCompId			=	8;

#define Component_Id					0x00690CC2

//----------------------------------------------------------------------------
//	SC: pages 5-2 to 5-5

// Power Control Register
const TUint32 KHwRwScSkpcr				=	KHoBaseSc;

	const TUint32 KHtSkpcrUsbClkEn		=	KBit0;
	const TUint32 KHtSkpcrAcClkEn			=	KBit1;
	const TUint32 KHtSkpcrI2sClk			=	KBit2;
	const TUint32 KHtSkpcrL3ClkEn			=	KBit3;
	const TUint32 KHtSkpcrSspClkEn		=	KBit4;
	const TUint32 KHtSkpcrMouseClkEn		=	KBit5;
	const TUint32 KHtSkpcrKbdClkEn		=	KBit6;
	const TUint32 KHtSkpcrDmaClkEn		=	KBit7;
	const TUint32 KHtSkpcrPwmClkEn		=	KBit8;
	const TUint32 KHmSkpcrBits			=	0x000001FF;

// Clock Divider Register
const TUint32 KHwRwScSkcdr				=	KHoBaseSc + 0x00000004;

	const TUint32 KHmSkcdrFeedbackDiv		=	KBit0|KBit1|KBit2|KBit3|KBit4|KBit5|KBit6;
	const TUint32 KHmSkcdrInputDiv		=	KBit7|KBit8|KBit9|KBit10|KBit11;
	const TUint32 KHsSkcdrInputDiv		=	7;
	const TUint32 KHtSkcdrOutputDiv0		=	KBit12;
	const TUint32 KHtSkcdrOutputDiv1		=	KBit13;
	const TUint32 KHmSkcdrOutputDiv		=	KHtSkcdrOutputDiv0|KHtSkcdrOutputDiv1;
	const TUint32 KHtSkcdrOutputSel		=	KBit14;
	const TUint32 KHmSkcdrBits			=	0x00007FFF;

#define VCO_Input						3686400		// 3.6864MHz
#define VCO_Nominal_Output				VCO_Input*(0x4C+0x02)/0x02	// 143.7696 MHz
#define PLL_Nominal_Output				VCO_Nominal_Output/1		// 143.7696 MHz
#define _VCO_FREQ(mul,div)				(VCO_Input*(mul/div))	// max freq is 237MHz

// Audio Clock Divider Register
const TUint32 KHwRwScSkaud				=	KHoBaseSc + 0x00000008;

	const TUint32 KHmSkaudAudioClkDiv		=	KBit0|KBit1|KBit2|KBit3|KBit4|KBit5|KBit6;

#define Audio_Sample_Rate22_05K			0x00000018
#define Audio_Sample_Rate16K			0x00000022
#define Audio_Sample_Rate11_025K		0x00000032
#define Audio_Sample_Rate8K				0x00000045
#define _AUDIO_SAMP_RATE(Div)			(PLL_Nominal_Output/((Div+1)*256))
// PS/2 Mouse Clock Divider Register
const TUint32 KHwRwScSkpmc				=	KHoBaseSc + 0x0000000C;

	const TUint32 KHmSkpmcPmcDiv			=	KBit0|KBit1|KBit2|KBit3|KBit4|KBit5|KBit6|KBit7;

// PS/2 TrackPad Clock Divider Register
const TUint32 KHwRwScSkptc				=	KHoBaseSc + 0x00000010;

	const TUint32 KHmSkptcPtcDiv			=	KBit0|KBit1|KBit2|KBit3|KBit4|KBit5|KBit6|KBit7;

#define PS2_Clock_2MHz					0x00000047
#define PS2_Clock_4MHz					0x00000023
#define PS2_Clock_8MHz					0x00000011
#define _PS2_CLOCK_RATE(Div)			(PLL_Nominal_Output/(Div+1))

// PWM0 Enable Register
const TUint32 KHwRwScSkpen0				=	KHoBaseSc + 0x00000014;

	const TUint32 KHmSkpen0Pwm0En			=	KBit0;

// PWM0 Clock Register
const TUint32 KHwRwScSkpwm0				=	KHoBaseSc + 0x00000018;

	const TUint32 KHmSkpwm0DutyCycle		=	KBit0|KBit1|KBit2|KBit3|KBit4|KBit5|KBit6|KBit7;

// PWM1 Enable Register
const TUint32 KHwRwScSkpen1				=	KHoBaseSc + 0x0000001C;

	const TUint32 KHmSkpen1Pwm1En			=	KBit0;

// PWM1 Clock Register
const TUint32 KHwRwScSkpwm1				=	KHoBaseSc + 0x00000020;

	const TUint32 KHmSkpwm1DutyCycle		=	KBit0|KBit1|KBit2|KBit3|KBit4|KBit5|KBit6|KBit7;

//----------------------------------------------------------------------------
//	SAC: pages 7-9 to 7-22

// Serial Audio Common Control Register

const TUint32 KHwRwSacSacr0				=	KHoBaseSac;

	const TUint32 KHtSacr0EnSac			=	KBit0;
	const TUint32 KHtSacr0BitclkDir		=	KBit2;
	const TUint32 KHtSacr0RstSac			=	KBit3;
	const TUint32 KHmSacr0TxFifoTh		=	KBit8|KBit9|KBit10|KBit11;
	const TUint32 KHsSacr0TxFifoTh		=	8;
	const TUint32 KHmSacr0RxFifoTh		=	KBit12|KBit13|KBit14|KBit15;
	const TUint32 KHsSacr0RxFifoTh		=	12;
	const TUint32 KHmSacr0Bits			=	0x0000FFFF;

const TUint32 KHwRwSacSacr1				=	KHoBaseSac + 0x00000004;

	const TUint32 KHtSacr1AlterModeSel	=	KBit0;
	const TUint32 KHtSacr1EnL3			=	KBit1;
	const TUint32 KHtSacr1L3MultByte		=	KBit2;
	const TUint32 KHtSacr1DisableRec		=	KBit3;
	const TUint32 KHtSacr1DisablePlay		=	KBit4;
	const TUint32 KHtSacr1EnLpbTest		=	KBit5;
	const TUint32 KHmSacr1Bits			=	0x0000003F;

const TUint32 KHwRwSacSacr2				=	KHoBaseSac + 0x00000008;

	const TUint32 KHtSacr2TxSlot3Valid	=	KBit0;
	const TUint32 KHtSacr2TxSlot4Valid	=	KBit1;
	const TUint32 KHtSacr2WakeupAc97		=	KBit2;
	const TUint32 KHtSacr2DisableRec		=	KBit3;
	const TUint32 KHtSacr2DisablePlay		=	KBit4;
	const TUint32 KHtSacr2EnLpbTest		=	KBit5;
	const TUint32 KHtSacr2ResetAc97		=	KBit6;
	const TUint32 KHmSacr2Bits			=	0x0000007F;

const TUint32 KHwRoSacSasr0				=	KHoBaseSac + 0x0000000C;

	const TUint32 KHtSasr0TxFifoFull		=	KBit0;
	const TUint32 KHtSasr0RxFifoEmpty		=	KBit1;
	const TUint32 KHtSasr0SacBusy			=	KBit2;
	const TUint32 KHtSasr0TxFifoReq		=	KBit3;
	const TUint32 KHtSasr0RxFifoReq		=	KBit4;
	const TUint32 KHtSasr0TxFifoURun		=	KBit5;
	const TUint32 KHtSasr0RxFifoORun		=	KBit6;
	const TUint32 KHmSasr0TxFifoLevel		=	KBit8|KBit9|KBit10|KBit11;
	const TUint32 KHsSasr0TxFifoLevel		=	8;
	const TUint32 KHmSasr0RxFifoLevel		=	KBit12|KBit13|KBit14|KBit15;
	const TUint32 KHsSasr0RxFifoLevel		=	12;
	const TUint32 KHtSasr0L3WriteDone		=	KBit16;
	const TUint32 KHtSasr0L3ReadDone		=	KBit17;

const TUint32 KHwRoSacSasr1				=	KHoBaseSac + 0x00000010;

	const TUint32 KHtSasr1TxFifoFull		=	KBit0;
	const TUint32 KHtSasr1RxFifoEmpty		=	KBit1;
	const TUint32 KHtSasr1SacBusy			=	KBit2;
	const TUint32 KHtSasr1TxFifoReq		=	KBit3;
	const TUint32 KHtSasr1RxFifoReq		=	KBit4;
	const TUint32 KHtSasr1TxFifoURun		=	KBit5;
	const TUint32 KHtSasr1RxFifoORun		=	KBit6;
	const TUint32 KHmSasr1TxFifoLevel		=	KBit8|KBit9|KBit10|KBit11;
	const TUint32 KHsSasr1TxFifoLevel		=	8;
	const TUint32 KHmSasr1RxFifoLevel		=	KBit12|KBit13|KBit14|KBit15;
	const TUint32 KHsSasr1RxFifoLevel		=	12;
	const TUint32 KHtSasr1ComDataAddrDone	=	KBit16;
	const TUint32 KHtSasr1StatDataAddrDone=	KBit17;
	const TUint32 KHtSasr1ReadStatTout	=	KBit18;
	const TUint32 KHtSasr1LowPowerDetect	=	KBit19;
	const TUint32 KHtSasr1CodecReady		=	KBit20;
	const TUint32 KHtSasr1RxSlot3Valid	=	KBit21;
	const TUint32 KHtSasr1RxSlot4Valid	=	KBit22;

const TUint32 KHwRwSacSascr				=	KHoBaseSac + 0x00000018;

	const TUint32 KHtSascrTxFifoURunClear =	KBit5;
	const TUint32 KHtSascrRxFifoORunClear	=	KBit6;
	const TUint32 KHtSascrDataSentClear	=	KBit16;
	const TUint32 KHtSascrDataReadClear	=	KBit17;
	const TUint32 KHtSascrReadTimeoutClear=	KBit18;
	const TUint32 KHmSascrBits			=	0x00070060;

const TUint32 KHwRwSacL3_Car				=	KHoBaseSac + 0x0000001C;

	const TUint32 KHmL3_CarTransferType	=	KBit0|KBit1;
	const TUint32 KHmL3_CarRegAddress		=	KBit2|KBit3|KBit4|KBit5|KBit6|KBit7;
	const TUint32 KHsL3_CarRegAddress		=	2;

#define L3_READ_TRANSFER_SPECIFIER		0x00000002
#define L3_WRITE_TRANSFER_SPECIFIER		0x00000003

const TUint32 KHwRwSacL3_Cdr				=	KHoBaseSac + 0x00000020;

	const TUint32 KHmL3_CdrData			=	KBit0|KBit1|KBit2|KBit3|KBit4|KBit5|KBit6|KBit7;

const TUint32 KHwRwSacAccar				=	KHoBaseSac + 0x00000024;

	const TUint32 KHmAccarRegAddress		=	KBit12|KBit13|KBit14|KBit15|\
											KBit16|KBit17|KBit18|KBit19;
	const TUint32 KHsAccarRegAddress		=	12;

#define AC_READ_TRANSFER_SPECIFIER		0x00080000
#define AC_WRITE_TRANSFER_SPECIFIER		0xFFF7FFFF

const TUint32 KHwRwSacAccdr				=	KHoBaseSac + 0x00000028;

	const TUint32 KHmAccdrRegAddress		=	KBit4|KBit5|KBit6|KBit7|\
											KBit8|KBit9|KBit10|KBit11|\
											KBit12|KBit13|KBit14|KBit15|\
											KBit16|KBit17|KBit18|KBit19;
	const TUint32 KHsAccdrRegAddress		=	4;

const TUint32 KHwRoSacAcsar				=	KHoBaseSac + 0x0000002C;

	const TUint32 KHmAcsarSlotreqBits		=	KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7|\
											KBit8|KBit9|KBit10|KBit11;
	const TUint32 KHsAcsarSlotreqBits		=	2;

	const TUint32 KHmAcsarRegAddress		=	KBit12|KBit13|KBit14|KBit15|\
											KBit16|KBit17|KBit18|KBit19;
	const TUint32 KHsAcsarRegAddress		=	12;

const TUint32 KHwRoSacAcsdr				=	KHoBaseSac + 0x00000030;

	const TUint32 KHmAcsdrRegAddress		=	KBit4|KBit5|KBit6|KBit7|\
											KBit8|KBit9|KBit10|KBit11|\
											KBit12|KBit13|KBit14|KBit15|\
											KBit16|KBit17|KBit18|KBit19;
	const TUint32 KHsAcsdrRegAddress		=	4;

const TUint32 KHwRwSacSadtcs				=	KHoBaseSac + 0x00000034;

	const TUint32 KHtSadtcsDmaTxEnable	=	KBit0;
	const TUint32 KHtSadtcsDmaTxIrqEnable	=	KBit1;
	const TUint32 KHtSadtcsTxBufferADone	=	KBit3;
	const TUint32 KHtSadtcsTxBufferAStart	=	KBit4;
	const TUint32 KHtSadtcsTxBufferBDone	=	KBit5;
	const TUint32 KHtSadtcsTxBufferBStart	=	KBit6;
	const TUint32 KHtSadtcsTxBufferInUse	=	KBit7;

const TUint32 KHwRwSacSadtsa				=	KHoBaseSac + 0x00000038;

const TUint32 KHwRwSacSadtca				=	KHoBaseSac + 0x0000003C;

	const TUint32 KHmSadtcaXferCountA		=	KBit0|KBit1|KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7|\
											KBit8|KBit9|KBit10|KBit11|\
											KBit12;

const TUint32 KHwRwSacSadtsb				=	KHoBaseSac + 0x00000040;

const TUint32 KHwRwSacSadtcb				=	KHoBaseSac + 0x00000044;

	const TUint32 KHmSadtcbXferCountB		=	KBit0|KBit1|KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7|\
											KBit8|KBit9|KBit10|KBit11|\
											KBit12;

const TUint32 KHwRwSacSadrcs				=	KHoBaseSac + 0x00000048;

	const TUint32 KHtSadrcsDmaRxEnable	=	KBit0;
	const TUint32 KHtSadrcsDmaRxIrqEnable	=	KBit1;
	const TUint32 KHtSadrcsRxBufferADone	=	KBit3;
	const TUint32 KHtSadrcsRxBufferAStart	=	KBit4;
	const TUint32 KHtSadrcsRxBufferBDone	=	KBit5;
	const TUint32 KHtSadrcsRxBufferBStart	=	KBit6;
	const TUint32 KHtSadrcsRxBufferInUse	=	KBit7;

const TUint32 KHwRwSacSadrsa				=	KHoBaseSac + 0x0000004C;

const TUint32 KHwRwSacSadrca				=	KHoBaseSac + 0x00000050;

	const TUint32 KHmSadrcaXferCountA		=	KBit0|KBit1|KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7|\
											KBit8|KBit9|KBit10|KBit11|\
											KBit12;

const TUint32 KHwRwSacSadrsb				=	KHoBaseSac + 0x00000054;

const TUint32 KHwRwSacSadrcb				=	KHoBaseSac + 0x00000058;

	const TUint32 KHmSadrcbXferCountB		=	KBit0|KBit1|KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7|\
											KBit8|KBit9|KBit10|KBit11|\
											KBit12;

const TUint32 KHwRwScSaitr				=	KHoBaseSac + 0x0000005C;

	const TUint32 KHtSaitrTxFifoTestIrq	=	KBit0;
	const TUint32 KHtSaitrRxFifoTestIrq	=	KBit1;
	const TUint32 KHtSaitrTxURunTestIrq	=	KBit2;
	const TUint32 KHtSaitrRxORunTestIrq	=	KBit3;
	const TUint32 KHtSaitrCadtTestIrq		=	KBit4;
	const TUint32 KHtSaitrSadrTestIrq		=	KBit5;
	const TUint32 KHtSaitrRstToutTestIrq	=	KBit6;
	const TUint32 KHtSaitrTxBufADoneTestIrq =	KBit8;
	const TUint32 KHtSaitrTxBufBDoneTestIrq =	KBit9;
	const TUint32 KHtSaitrRxBufADoneTestIrq =	KBit10;
	const TUint32 KHtSaitrRxBufBDoneTestIrq =	KBit1;
	const TUint32 KHtSaitrBits			=	0x00000F7F;

const TUint32 KHwRwSacSadrBase			=	KHoBaseSac + 0x00000080;
const TUint32 KHwRwSacSadrLength			=	16;

//----------------------------------------------------------------------------
//	SSP: pages 8-7 to 8-16

const TUint32 KHwRwSspSspcr0				=	KHoBaseSsp;

	const TUint32 KHmSspcr0Dss			=	KBit0|KBit1|KBit2|KBit3;
	const TUint32 KHmSscpr0Frf			=	KBit4|KBit5;
	const TUint32 KHsSscpr0Frf			=	4;
	const TUint32 KHtSscpr0SspEn			=	KBit7;
	const TUint32 KHmSscpr0Scr			=	KBit8|KBit9|KBit10|KBit11|\
											KBit12|KBit13|KBit14|KBit15;
	const TUint32 KHsSscpr0Scr			=	8;
	const TUint32 KHmSscpr0Bits			=	0x0000FFBF;

const TUint32 KHwRwSspSspcr1				=	KHoBaseSsp + 0x00000004;

	const TUint32 KHtSspcr1RxIrqMask		=	KBit0;
	const TUint32 KHtSspcr1TxIrqMask		=	KBit1;
	const TUint32 KHtSspcr1Lbm			=	KBit2;
	const TUint32 KHtSspcr1Spo			=	KBit3;
	const TUint32 KHtSspcr1Sph			=	KBit4;
	const TUint32 KHmSspcr1Tft			=	KBit7|KBit8|KBit9|KBit10;
	const TUint32 KHsSspcr1Tft			=	7;
	const TUint32 KHmSspcr1Rft			=	KBit11|KBit12|KBit13|KBit14;
	const TUint32 KHsSspcr1Rft			=	11;
	const TUint32 KHmSspcr1Bits			=	0x00007F9F;

const TUint32 KHwRwSspSspsr				=	KHoBaseSsp + 0x00000010;

	const TUint32 KHtSspsrTnf				=	KBit2;
	const TUint32 KHtSspsrRne				=	KBit3;
	const TUint32 KHtSspsrBsy				=	KBit4;
	const TUint32 KHtSspsrTfs				=	KBit5;
	const TUint32 KHtSspsrRfs				=	KBit6;
	const TUint32 KHtSspsrRor				=	KBit7;
	const TUint32 KHmSspsrTfl				=	KBit8|KBit9|KBit10|KBit11;
	const TUint32 KHsSspsrTfl				=	8;
	const TUint32 KHmSspsrRfl				=	KBit12|KBit13|KBit14|KBit15;
	const TUint32 KHsSspsrRfl				=	12;

const TUint32 KHwRwSspSspitr				=	KHoBaseSsp + 0x00000014;

	const TUint32 KHtSspitrTfs			=	KBit5;
	const TUint32 KHtSspitrRfs			=	KBit6;
	const TUint32 KHtSspitrRor			=	KBit7;

const TUint32 KHwRwSspdwr					=	KHoBaseSsp + 0x00000040;
const TUint32 KHwRwSspdrr					=	KHwRwSspdwr;

	const TUint32 KHmDataBits				=	0x0000FFFF;

const TInt KSspClk1843200Bps = 0;
const TInt KSspClk460800Bps = 3;
const TInt KSspClk7200Bps = 255;
const TInt KSspFifoHalfLenght = 7;

//----------------------------------------------------------------------------
//	PS/2 Kbd and Mouse: pages 9-1 to 9-4

const TUint32 KHwRoKbdKbdcr				=	KHoBaseKbd;
const TUint32 KHwRoMouseKbdcr				=	KHoBaseMouse;

	const TUint32 KHtKbdcrFkc			=	KBit0;
	const TUint32 KHtKbdcrFkd			=	KBit1;
	const TUint32 KHtKbdcrEna			=	KBit3;
	const TUint32 KHtKbdcrBits			=	0x0000000B;

const TUint32 KHwRwKbdKbdstat			=	KHoBaseKbd + 0x00000004;
const TUint32 KHwRwMouseKbdstat			=	KHoBaseMouse + 0x00000004;

	const TUint32 KHtKbdstatKbc			=	KBit0;
	const TUint32 KHtKbdstatKbd			=	KBit1;
	const TUint32 KHtKbdstatRxParity	=	KBit2;
	const TUint32 KHsKbdstatRxParity	=	2;
	const TUint32 KHtKbdstatEna			=	KBit3;
	const TUint32 KHtKbdstatRxBusy		=	KBit4;
	const TUint32 KHtKbdstatRxFull		=	KBit5;
	const TUint32 KHtKbdstatTxBusy		=	KBit6;
	const TUint32 KHtKbdstatTxEmpty		=	KBit7;
	const TUint32 KHtKbdstatStopBitErr	=	KBit8;

const TUint32 KHwRwKbdKbddata			=	KHoBaseKbd + 0x00000008;
const TUint32 KHwRwMouseKbddata			=	KHoBaseMouse + 0x00000008;

	const TUint32 KHmKbddataBits		=	KBit0|KBit1|KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7;

const TUint32 KHwRwKbdKbdclkdiv			=	KHoBaseKbd + 0x0000000C;
const TUint32 KHwRwMouseKbdclkdiv		=	KHoBaseMouse + 0x0000000C;

	const TUint32 KHtKbdclkdivDivVal0	=	KBit0;
	const TUint32 KHtKbdclkdivDivVal1	=	KBit1;
	const TUint32 KHmKbdclkdivBits		=	KHtKbdclkdivDivVal0|KHtKbdclkdivDivVal1;

const TUint32 KHwRwKbdKbdprecnt			=	KHoBaseKbd + 0x00000010;
const TUint32 KHwRwMouseKbdprecnt		=	KHoBaseMouse + 0x00000010;

	const TUint32 KHmKbdprecntBits		=	KBit0|KBit1|KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7;

const TUint32 KHwRwKbdKbditr			=	KHoBaseKbd + 0x00000014;
const TUint32 KHwRwMouseKbditr			=	KHoBaseMouse + 0x00000014;

	const TUint32 KHtKbditrRxFull		=	KBit5;
	const TUint32 KHtKbditrTxEmpty		=	KBit7;
	const TUint32 KHtKbditrStopBitErr	=	KBit8;
	const TUint32 KHmKbditrBits			=	0x000001A0;

//----------------------------------------------------------------------------
//	GPIO: pages 10-2 to 10-5
// Port A
const TUint32	KHwRwGpioPa_ddr			=	KHoBaseGpio;

const TUint32	KHwRwGpioPa_drr			=	KHoBaseGpio + 0x00000004;
const TUint32	KHwRwGpioPa_dwr			=	KHoBaseGpio + 0x00000004;

const TUint32	KHwRwGpioPa_sdr			=	KHoBaseGpio + 0x00000008;

const TUint32	KHwRwGpioPa_ssr			=	KHoBaseGpio + 0x0000000C;

	const TUint32 KHmPortABits			=	KBit0|KBit1|KBit2|KBit3;  // applies to all PortA registers
// Port B
const TUint32	KHoGpioPortB			=	0x00000010;
const TUint32	KHwRwGpioPb_ddr			=	KHoBaseGpio + KHoGpioPortB;

const TUint32	KHwRwGpioPb_drr			=	KHoBaseGpio + KHoGpioPortB + 0x00000004;
const TUint32	KHwRwGpioPb_dwr			=	KHoBaseGpio + KHoGpioPortB + 0x00000004;

const TUint32	KHwRwGpioPb_sdr			=	KHoBaseGpio + KHoGpioPortB + 0x00000008;

const TUint32	KHwRwGpioPb_ssr			=	KHoBaseGpio + KHoGpioPortB + 0x0000000C;

	const TUint32 KHmPortBBits			=	KBit0|KBit1|KBit2|KBit3|\
											KBit4;			  // applies to all PortB registers
	const TUint32 KHsPortBBits			=	8;				  // applies to all PortB registers
// Port C
const TUint32	KHoGpioPortC			=	0x00000020;
const TUint32	KHwRwGpioPc_ddr			=	KHoBaseGpio + KHoGpioPortC;

const TUint32	KHwRwGpioPc_drr			=	KHoBaseGpio + KHoGpioPortC + 0x00000004;
const TUint32	KHwRwGpioPc_dwr			=	KHoBaseGpio + KHoGpioPortC + 0x00000004;

const TUint32	KHwRwGpioPc_sdr			=	KHoBaseGpio + KHoGpioPortC + 0x00000008;

const TUint32	KHwRwGpioPc_ssr			=	KHoBaseGpio + KHoGpioPortC + 0x0000000C;

	const TUint32 KHmPortCBits			=	KBit0|KBit1|KBit2|KBit3|\
											KBit4|KBit5|KBit6|KBit7;	// applies to all PortC registers
	const TUint32 KHsPortCBits			=	16;				  // applies to all PortC registers

//----------------------------------------------------------------------------
//	Interrupt Controller: pages 11-3 to 11-8
//
const TUint32	KHwRwIntContInttest0	=	KHoBaseIntCont;				  // for production test
const TUint32	KHwRwIntContInttest1	=	KHoBaseIntCont + 0x00000004;  // for production test

const TUint32	KHwRwIntContInten0		=	KHoBaseIntCont + 0x00000008;

	const TUint32 KHtIntContGpioA0Int	=	KBit0;		// these bit definitions apply to all 
	const TUint32 KHtIntContGpioA1Int	=	KBit1;		// registers indexed 0
	const TUint32 KHtIntContGpioA2Int	=	KBit2;
	const TUint32 KHtIntContGpioA3Int	=	KBit3;
	const TUint32 KHtIntContGpioB0Int	=	KBit4;
	const TUint32 KHtIntContGpioB1Int	=	KBit5;
	const TUint32 KHtIntContGpioB2Int	=	KBit6;
	const TUint32 KHtIntContGpioB3Int	=	KBit7;
	const TUint32 KHtIntContGpioB4Int	=	KBit8;
	const TUint32 KHtIntContGpioB5Int	=	KBit9;
	const TUint32 KHtIntContGpioC0Int	=	KBit10;
	const TUint32 KHtIntContGpioC1Int	=	KBit11;
	const TUint32 KHtIntContGpioC2Int	=	KBit12;
	const TUint32 KHtIntContGpioC3Int	=	KBit13;
	const TUint32 KHtIntContGpioC4Int	=	KBit14;
	const TUint32 KHtIntContGpioC5Int	=	KBit15;
	const TUint32 KHtIntContGpioC6Int	=	KBit16;
	const TUint32 KHtIntContGpioC7Int	=	KBit17;
	const TUint32 KHtIntContMsTxInt		=	KBit18;
	const TUint32 KHtIntContMsRxInt		=	KBit19;
	const TUint32 KHtIntContMsStoprrInt	=	KBit20;
	const TUint32 KHtIntContTpTxInt		=	KBit21;
	const TUint32 KHtIntContTpRxInt		=	KBit22;
	const TUint32 KHtIntContTpStoprrInt	=	KBit23;
	const TUint32 KHtIntContSspTxInt	=	KBit24;
	const TUint32 KHtIntContSspRxInt	=	KBit25;
	const TUint32 KHtIntContSspRorInt	=	KBit26;
	const TUint32 KHmIntContIndexMask0	=	0x07FFFFFF;

const TUint32	KHwRwIntContInten1			=	KHoBaseIntCont + 0x0000000C;

	const TUint32 KHtIntContAudTxDmaDoneA	=	KBit0;		// these bit definitions apply to all
	const TUint32 KHtIntContAudRxDmaDoneA	=	KBit1;		// registers indexed 1
	const TUint32 KHtIntContAudTxDmaDoneB	=	KBit2;
	const TUint32 KHtIntContAudRxDmaDoneB	=	KBit3;
	const TUint32 KHtIntContAudTfsr			=	KBit4;
	const TUint32 KHtIntContAudRfsr			=	KBit5;
	const TUint32 KHtIntContAudTur			=	KBit6;
	const TUint32 KHtIntContAudRor			=	KBit7;
	const TUint32 KHtIntContAudDts			=	KBit8;
	const TUint32 KHtIntContAudRdd			=	KBit9;
	const TUint32 KHtIntContAudSto			=	KBit10;
	const TUint32 KHtIntContUsbPwr			=	KBit11;
	const TUint32 KHtIntContnIrqHciM		=	KBit12;
	const TUint32 KHtIntContnIrqHciBuffAcc	=	KBit13;
	const TUint32 KHtIntContnIrqHciRmtWkp	=	KBit14;
	const TUint32 KHtIntContnIrqHciMfCir	=	KBit15;
	const TUint32 KHtIntContUsbPortResume	=	KBit16;
	const TUint32 KHtIntContS0ReadynInt		=	KBit17;
	const TUint32 KHtIntContS1ReadynInt		=	KBit18;
	const TUint32 KHtIntContS0CdValid		=	KBit19;
	const TUint32 KHtIntContS1CdValid		=	KBit20;
	const TUint32 KHtIntContS0_Bvd1Stschg	=	KBit21;
	const TUint32 KHtIntContS1_Bvd1Stschg	=	KBit22;
	const TUint32 KHmIntContIndexMask1		=	0x007FFFFF;

const TUint32	KHwRwIntContIntpol0			=	KHoBaseIntCont + 0x00000010;

const TUint32	KHwRwIntContIntpol1			=	KHoBaseIntCont + 0x00000014;

const TUint32	KHwRwIntContInttstsel		=	KHoBaseIntCont + 0x00000018;

	const TUint32 KHtInttstsel1IntInputSel	=	KBit0;
	const TUint32 KHtInttstsel1IntModeSel	=	KBit1;

const TUint32	KHwRwIntContInttstatclr0	=	KHoBaseIntCont + 0x0000001C;

const TUint32	KHwRwIntContInttstatclr1	=	KHoBaseIntCont + 0x00000020;

const TUint32	KHwRwIntContIntset0			=	KHoBaseIntCont + 0x00000024;

const TUint32	KHwRwIntContIntset1			=	KHoBaseIntCont + 0x00000028;

const TUint32	KHwRwIntContIntwake_en0		=	KHoBaseIntCont + 0x0000002C;

const TUint32	KHwRwIntContIntwake_en1		=	KHoBaseIntCont + 0x00000030;

const TUint32	KHwRwIntContIntwake_pol0	=	KHoBaseIntCont + 0x00000034;

const TUint32	KHwRwIntContIntwake_pol1	=	KHoBaseIntCont + 0x00000038;

//----------------------------------------------------------------------------
//	PCCard: pages 12-13 to 12-15
//
const TUint32	KHwRwPcCardPccr			=	KHoBasePcCard;

	const TUint32 KHtPcsrSocket0Ready	=	KBit0;
	const TUint32 KHtPcsrSocket1Ready	=	KBit1;
	const TUint32 KHtPcsrSocket0Detect	=	KBit2;
	const TUint32 KHtPcsrSocket1Detect	=	KBit3;
	const TUint32 KHtPcsrSocket0VS1		=	KBit4;
	const TUint32 KHtPcsrSocket0VS2		=	KBit5;
	const TUint32 KHtPcsrSocket1VS1		=	KBit6;
	const TUint32 KHtPcsrSocket1VS2		=	KBit7;
	const TUint32 KHtPcsrSocket0WP		=	KBit8;
	const TUint32 KHtPcsrSocket1WP		=	KBit9;
	const TUint32 KHtPcsrSock0Bvd1Stschg=	KBit10;
	const TUint32 KHtPcsrSock0Bvd2Spkr	=	KBit11;
	const TUint32 KHtPcsrSock1Bvd1Stschg=	KBit12;
	const TUint32 KHtPcsrSock1Bvd2Spkr	=	KBit13;

const TUint32	KHwRwPcCardPcssr			=	KHoBasePcCard + 0x00000004;

	const TUint32 KHtPccrSocket0Reset	=	KBit0;
	const TUint32 KHtPccrSocket1Reset	=	KBit1;
	const TUint32 KHtPccrSocket0Float	=	KBit2;
	const TUint32 KHtPccrSocket1Float	=	KBit3;
	const TUint32 KHtPccrSocket0PWaitEn	=	KBit4;
	const TUint32 KHtPccrSocket1PWaitEn	=	KBit5;
	const TUint32 KHtPccrSocket0Pse		=	KBit6;
	const TUint32 KHtPccrSocket1Pse		=	KBit7;
	const TUint32 KHmPccrBits			=	0x000000FF;

const TUint32	KHwRoPcCardPcsr		=	KHoBasePcCard + 0x00000008;

	const TUint32 KHtPccrSocket0Cont	=	KBit0;
	const TUint32 KHtPccrSocket1Cont	=	KBit1;
	const TUint32 KHmPcssrBits			=	0x00000003;

class TSa1111
	{
public:
// General
	enum TState
		{
		EEnable,
		EDisable
		};
	enum TDirection
		{
		EOutput,
		EInput
		};
	enum TPolarity
		{
		EPolarityActiveLow,
		EPolarityActiveHigh
		};
	enum TActiveEdge
		{
		EFallingEdge,
		ERisingEdge
		};
// SBI
	enum TOpMode
		{
		ENormalMode=KClear32,
		ESleepMode=KHtSkcrSleep,	// should never be reported
		EDozeMode=KHtSkcrDoze,
		EInvalidMode=KSet32			// should never be reported
		};
	enum TTestMode
		{
		EScanTest=KHtSkcrScanTestEn,
		EClockTest=KHtSkcrClockTestEn,
		EOppcTest=KHtSkcrOppc,
		EPllTest=KHtSkcrPllTestEn,
		EUsbIoTest=KHtSkcrUsbIoTestEn,
		};
	enum TAudioSel
		{
		EAcLink,
		EI2s_Msb
		};
	enum TDramType
		{
		ESdram=KHtSmcrDtim,
		EOther=KClear32
		};
	enum TCasLatency
		{
		MinLatency=KClear32,
		MaxLatency=KHtSmcrClat
		};
// SC
	enum TPllDividerRates
		{
		ESameAsVco=KClear32,
		EVcoDivBy2=KHtSkcdrOutputDiv1,
		EVcoDivBy4=KHtSkcdrOutputDiv0,
		EVcoDivBy8=KHtSkcdrOutputDiv0|KHtSkcdrOutputDiv1
		};
	enum TClockPolarity
		{
		EDirect,
		EInverted
		};
	enum TAudioClockRates
		{
		E22KHz=Audio_Sample_Rate22_05K,
		E16KHz=Audio_Sample_Rate16K,
		E11KHz=Audio_Sample_Rate11_025K,
		E8KHz=Audio_Sample_Rate8K
		};
	enum TPs2ClockRates
		{
		E2MHz=PS2_Clock_2MHz,
		E4MHz=PS2_Clock_4MHz,
		E8MHz=PS2_Clock_8MHz
		};
// SAC
	enum TAudioAltMode
		{
		EI2s,
		EMsb_First
		};
	enum TSerialAudioTest
		{
		ESacTxFifoIrqTest=KHtSaitrTxFifoTestIrq,
		ESacRxFifoIrqTest=KHtSaitrRxFifoTestIrq,
		ESacTxFifoUnderrunIrqTest=KHtSaitrTxURunTestIrq,
		ESacRxFifoOverrunIrqTest=KHtSaitrRxORunTestIrq,
		EAc97CommandDataAddressDoneIrqTest=KHtSaitrCadtTestIrq,
		EAc97StatusDataAddressDoneIrqTest=KHtSaitrSadrTestIrq,
		EAc97ReadStatusTimeoutIrqTest=KHtSaitrRstToutTestIrq,
		ESacTxBufferADoneIrqTest=KHtSaitrTxBufADoneTestIrq,
		ESacTxBufferBDoneIrqTest=KHtSaitrTxBufBDoneTestIrq,
		ESacRxBufferADoneIrqTest=KHtSaitrRxBufADoneTestIrq,
		ESacRxBufferBDoneIrqTest=KHtSaitrRxBufBDoneTestIrq
		};
//SSP
	enum TSspDataSize
		{
		ESspData4Bit=3,ESspData5Bit=4,ESspData6Bit=5,ESspData7Bit=6,ESspData8Bit=7,
		ESspData9Bit=8,ESspData10Bit=9,ESspData11Bit=10,ESspData12Bit=11,ESspData13Bit=12,
		ESspData14Bit=13,ESspData15Bit=14,ESspData16Bit=15
		};
	enum TSspFrameFormat
		{
		ESspFrameFormatSPI=0,
		ESspFrameFormatTISyncSer=1,
		ESspFrameFormatNatMicrowire=2
		};
	enum TSspSerClkPhase
		{
		ESspSclkPhaseMode1=KClear32,
		ESspSclkPhaseMode2=KHtSspcr1Sph
		};
	enum TSspTest
		{
		ESspTxFifoIrqTest=KHtSspitrTfs,
		ESspRxFifoIrqTest=KHtSspitrRfs,
		ESspRxFifoOverrunIrqTest=KHtSspitrRor
		};
// PS/2 KBD AND MOUSE
	enum TPs2Sel
		{
		EKeyboard,
		EMouse
		};
	enum TPs2DividerRates
		{
		EKbdClkDivBy8=KClear32,
		EKbdClkDivBy4=KHtKbdclkdivDivVal0,
		EKbdClkDivBy2=KHtKbdclkdivDivVal1
		};
	enum TPs2Test
		{
		EPs2RxFullIrqTest=KHtKbditrRxFull,
		EPs2TxEmptyIrqTest=KHtKbditrTxEmpty,
		EPs2StopBitErrIrqTest=KHtKbditrStopBitErr
		};
	enum TGpioPort
		{
		EPortA=KClear32,
		EPortB=KHoGpioPortB,
		EPortC=KHoGpioPortC
		};
// Interrupt Controller
	enum TIntSource
		{
		EGpioA0Int=0, EGpioA1Int=1, EGpioA2Int=2, EGpioA3Int=3, EGpioB0Int=4, EGpioB1Int=5,
		EGpioB2Int=6, EGpioB3Int=7, EGpioB4Int=8, EGpioB5Int=9, EGpioC0Int=10, EGpioC1Int=11,
		EGpioC2Int=12, EGpioC3Int=13, EGpioC4Int=14, EGpioC5Int=15, EGpioC6Int=16, EGpioC7Int=17,
		EMsTxInt=18, EMsRxInt=19, EMsStopErrInt=20, ETpTxInt=21, ETpRxInt=22, ETpStopErrInt=23,
		ESspTxInt=24, ESspRxInt=25, ESspRorInt=26, EAudTxDmaDoneA=32, EAudRxDmaDoneA=33,
		EAudTxDmaDoneB=34, EAudRxDmaDoneB=35, EAudTfsr=36, EAudRfsr=37, EAudTur=38,
		EAudRor=39, EAudDts=40, EAudRdd=41, EAudSto=42, EUsbPwr=43, EnIrqHciM=44,
		EnIrqHciBuffAcc=45, EnIrqHciRmtWkp=46, EnIrqHciMfCir=47, EUsbPortResume=48,
		ES0ReadynInt=49, ES1ReadynInt=50, ES0CdValid=51, ES1CdValid=52, ES0_Bvd1Stschg=53,
		ES1_Bvd1Stschg=54,
		};
	enum TIntSet
		{
		EIntRegSet0,
		EIntRegSet1
		};
	enum TIntContMode
		{
		EInterruptMode=KClear32,
		EWakeUpMode=KHtInttstsel1IntModeSel
		};
// PCMCIA
	enum TPcCardSocket
		{
		ESocket0,
		ESocket1
		};
	enum TPcCardVoltage
		{
		E3Volt,
		E5Volt
		};
	enum TPcCardSleepState
		{
		ETristated,
		ESateDefined
		};

public:
	TSa1111();									// Constructor
	// Initialisation
	static void Init3();

	// SBI
	IMPORT_C static void EnablePll(TState aState);
	IMPORT_C static void EnableRclk(TState aState);
	IMPORT_C static TBool IsRclkEnabled();		// NB: RCLK needs to be enabled before accessing
												// any registers other than SBI's
	IMPORT_C static void EnableVco(TState aState);
	IMPORT_C static void EnableReadySignal(TState aState);
	IMPORT_C static void EnableOeSignal(TState aState);	// needs nOE signal (see specification update)
	IMPORT_C static void GoToSleep();
	IMPORT_C static void GoToDoze();
	IMPORT_C static void ReturnFromDoze();
	IMPORT_C static TOpMode GetOperationalMode();
	IMPORT_C static void SelectAudio(TAudioSel aSelection);
	IMPORT_C static TAudioSel GetAudioSelection();
	IMPORT_C static void EnterTestMode(TTestMode aTest);	// does not reset other test bits
	IMPORT_C static void LeaveTestMode(TTestMode aTest);	// must specifically clear a test bit
	IMPORT_C static void ModifySkcr(TUint32 aClearMask, TUint32 aSetMask);
	IMPORT_C static TUint32 ReadSkcr();						// return all bits from this register

	IMPORT_C static void SetDramConfig(TDramType aType, TCasLatency aLatency, TUint32 aRows);
	IMPORT_C static void EnableMemGrantSignal(TState aState);
	IMPORT_C static TUint32 ReadSmcr();						// return all bits from this register

	IMPORT_C static TBool CheckId(TUint32* aPtr);

	// SC
	IMPORT_C static void EnableUsbClock(TState aState);
	IMPORT_C static void EnableAcLinkClock(TState aState);
	IMPORT_C static void EnableI2sClock(TState aState);
	IMPORT_C static void EnableL3Clock(TState aState);
	IMPORT_C static void EnableSspClock(TState aState);
	IMPORT_C static void EnableMouseClock(TState aState);
	IMPORT_C static void EnableKbdClock(TState aState);
	IMPORT_C static void EnableDmaClock(TState aState);
	IMPORT_C static void EnablePwmClock(TState aState);
	IMPORT_C static TUint32 ReadSkpcr();				// return all bits from this register

	IMPORT_C static TUint32 SetVcoFrequency(TUint32 aFeedbackDivider, TUint32 anInputDivider); // both LSB aligned
	IMPORT_C static void SetPllDivider(TPllDividerRates aRate);
	IMPORT_C static TPllDividerRates GetPllDividerRate();
	IMPORT_C static void SwitchClockPolarity(TClockPolarity aPolarity);
	IMPORT_C static void ModifySkcdr(TUint32 aClearMask,TUint32 aSetMask); // to access undocumented bits...
	IMPORT_C static TUint32 ReadSkcdr();				// return all bits from this register

	IMPORT_C static void SetAudioSampleRate(TAudioClockRates aSampleRate);
	IMPORT_C static TUint32 GetAudioSampleRate();

	IMPORT_C static void SetPs2MouseClockRate(TPs2ClockRates aClockRate);
	IMPORT_C static TUint32 GetPs2MouseClockRate();

	IMPORT_C static void SetPs2KbdClockRate(TPs2ClockRates aClockRate);
	IMPORT_C static TUint32 GetPs2KbdClockRate();

	IMPORT_C static void EnablePwm0(TState aState);
	IMPORT_C static void SetPwm0DutyCycle(TUint32 aDutyCycle);
	IMPORT_C static TUint32 GetPwm0DutyCycle();

	IMPORT_C static void EnablePwm1(TState aState);
	IMPORT_C static void SetPwm1DutyCycle(TUint32 aDutyCycle);
	IMPORT_C static TUint32 GetPwm1DutyCycle();

	//SAC
	IMPORT_C static void EnableSac(TState aState);
	IMPORT_C static TBool IsSacEnabled();		// NB: Sac needs to be enabled before accessing
												// any other bits of SACR0 and other SAC registers
	IMPORT_C static void SetBitClkDirection(TDirection aDirection);
	IMPORT_C static TDirection WhatsBitClkDir();
	IMPORT_C static void ResetSac();					// reset pulse for SAC (internal)
	IMPORT_C static void SetSacTxFifoThreshold(TUint32 aThreshold);
	IMPORT_C static TUint32 GetSacTxFifoThreshold();
	IMPORT_C static void SetSacRxFifoThreshold(TUint32 aThreshold);
	IMPORT_C static TUint32 GetSacRxFifoThreshold();
	IMPORT_C static TUint32 ReadSacr0();				// return all bits from this register

	IMPORT_C static void EnableAudioAltMode(TAudioAltMode aMode);
	IMPORT_C static void EnableL3Control(TState aState);
	IMPORT_C static void EnableL3MultipleByteMode(TState aState);
	IMPORT_C static void EnableAltRecFunction(TState aState);
	IMPORT_C static void EnableAltPlayFunction(TState aState);
	IMPORT_C static void EnableAltLoopbackTest(TState aState);
	IMPORT_C static TUint32 ReadSacr1();				// return all bits from this register

	IMPORT_C static void ValidateAc97TxLefttChannel(TState aState);
	IMPORT_C static void ValidateAc97TxRightChannel(TState aState);
	IMPORT_C static void ActivateAc97WakeUp();		// use these 2 and a timer to create a wake-up
	IMPORT_C static void DeactivateAc97WakeUp();	// pulse of a suitable duration
	IMPORT_C static void EnableAc97RecFunction(TState aState);
	IMPORT_C static void EnableAc97PlayFunction(TState aState);
	IMPORT_C static void EnableAc97LoopbackTest(TState aState);
	IMPORT_C static void ActivateAc97Reset();		// use these 2 and a timer to create a reset
	IMPORT_C static void DeactivateAc97Reset();		// pulse of a suitable duration
	IMPORT_C static TUint32 ReadSacr2();				// return all bits from this register

	IMPORT_C static TBool IsSacTxFifoFull(TAudioSel aSelection);
	IMPORT_C static TBool IsSacRxFifoEmpty(TAudioSel aSelection);
	IMPORT_C static TBool IsSacBusy(TAudioSel aSelection);
	IMPORT_C static TBool IsSacTxFifoRequesting(TAudioSel aSelection);
	IMPORT_C static TBool IsSacRxFifoRequesting(TAudioSel aSelection);
	IMPORT_C static TBool HasSacTxFifoUnderrun(TAudioSel aSelection);
	IMPORT_C static TBool HasSacRxFifoOverrun(TAudioSel aSelection);
	IMPORT_C static TUint32 GetSacTxFifoLevel(TAudioSel aSelection);
	IMPORT_C static TUint32 GetSacRxFifoLevel(TAudioSel aSelection);
	IMPORT_C static TBool IsL3DataWriteDone();
	IMPORT_C static TBool IsL3DataReadDone();
	IMPORT_C static TBool IsAc97CommandDataAddressDone();
	IMPORT_C static TBool IsAc97StatusDataAddressDone();
	IMPORT_C static TBool IsAc97ReadStatusTimeout();
	IMPORT_C static TBool IsAc97LowPowerModeDetect();
	IMPORT_C static TBool IsAc97CodecReady();
	IMPORT_C static TBool IsAc97RxLeftChannelValid();
	IMPORT_C static TBool IsAc97RxRightChannelValid();

	IMPORT_C static void ClearSacTxFifoUnderrun();
	IMPORT_C static void ClearSacRxFifoOverrun();
	IMPORT_C static void ClearL3DataWrite_Ac97CommandBit();
	IMPORT_C static void ClearL3DataRead_Ac97StatusBit();
	IMPORT_C static void ClearAc97ReadStatusTimeout();

	IMPORT_C static void WriteL3Address_WriteXfer(TUint32 anAddress);	// anAddress is LSB aligned
	IMPORT_C static void WriteL3Address_ReadXfer(TUint32 anAddress);	// (starting from 0) 
	IMPORT_C static void WriteDataToL3Register(TUint32 aData);
	IMPORT_C static TUint32 ReadDataFromL3Register();

	IMPORT_C static void WriteAc97Address_WriteXfer(TUint32 anAddress);// anAddress is LSB aligned
	IMPORT_C static void WriteAc97Address_ReadXfer(TUint32 anAddress); // (starting from 0) 
	IMPORT_C static void WriteAc97CommandData(TUint32 aData);			 // aData is LSB aligned
	IMPORT_C static TUint32 ReadAc97StatusAddress();					 // returns an LSB aligned value
	IMPORT_C static TUint32 ReadAc97SlotreqBits();					 // returns an LSB aligned value
	IMPORT_C static TUint32 ReadAc97StatusData();						 // returns an LSB aligned value

	IMPORT_C static void EnableAudioDmaTx(TState aState);
	IMPORT_C static void EnableAudioDmaTxDoneIrq(TState aState);
	IMPORT_C static TBool IsDmaTxBufferADone();
	IMPORT_C static void StartDmaTxBuferA();
	IMPORT_C static void StopDmaTxBuferA();
	IMPORT_C static TBool IsDmaTxBufferBDone();
	IMPORT_C static void StartDmaTxBuferB();
	IMPORT_C static void StopDmaTxBuferB();
	IMPORT_C static TBool IsDmaTxBufferInUse();

	IMPORT_C static void SetTxBufferAStartAddress(TUint32 anAddress);	// needs to be on a 32-bit boundary
	IMPORT_C static TUint32 GetTxBufferAStartAddress();

	IMPORT_C static void SetTxBufferAXferCount(TUint32 aCount);		// aCount is a multiple of 4
	IMPORT_C static TUint32 GetTxBufferAXferCount();

	IMPORT_C static void SetTxBufferBStartAddress(TUint32 anAddress);	// needs to be on a 32-bit boundary
	IMPORT_C static TUint32 GetTxBufferBStartAddress();

	IMPORT_C static void SetTxBufferBXferCount(TUint32 aCount);		// aCount is a multiple of 4
	IMPORT_C static TUint32 GetTxBufferBXferCount();

	IMPORT_C static void EnableAudioDmaRx(TState aState);
	IMPORT_C static void EnableAudioDmaRxDoneIrq(TState aState);
	IMPORT_C static TBool IsDmaRxBufferADone();
	IMPORT_C static void StartDmaRxBuferA();
	IMPORT_C static void StopDmaRxBuferA();
	IMPORT_C static TBool IsDmaRxBufferBDone();
	IMPORT_C static void StartDmaRxBuferB();
	IMPORT_C static void StopDmaRxBuferB();
	IMPORT_C static TBool IsDmaRxBufferInUse();

	IMPORT_C static void SetRxBufferAStartAddress(TUint32 anAddress);	// needs to be on a 32-bit boundary
	IMPORT_C static TUint32 GetRxBufferAStartAddress();

	IMPORT_C static void SetRxBufferAXferCount(TUint32 aCount);		// aCount is a multiple of 4
	IMPORT_C static TUint32 GetRxBufferAXferCount();

	IMPORT_C static void SetRxBufferBStartAddress(TUint32 anAddress);	// needs to be on a 32-bit boundary
	IMPORT_C static TUint32 GetRxBufferBStartAddress();

	IMPORT_C static void SetRxBufferBXferCount(TUint32 aCount);		// aCount is a multiple of 4
	IMPORT_C static TUint32 GetRxBufferBXferCount();

	IMPORT_C static void SacTxFifoIrqTest();
	IMPORT_C static void SacRxFifoIrqTest();
	IMPORT_C static void SacTxFifoUnderrunIrqTest();
	IMPORT_C static void SacRxFifoOverrunIrqTest();
	IMPORT_C static void Ac97CommandDataAddressDoneIrqTest();
	IMPORT_C static void Ac97StatusDataAddressDoneIrqTest();
	IMPORT_C static void Ac97ReadStatusTimeoutIrqTest();
	IMPORT_C static void TxBufferADoneIrqTest();
	IMPORT_C static void TxBufferBDoneIrqTest();
	IMPORT_C static void RxBufferADoneIrqTest();
	IMPORT_C static void RxBufferBDoneIrqTest();
	IMPORT_C static void ClearSacTestBit(TSerialAudioTest aTest);
	IMPORT_C static TUint32 ReadSaitr();				// return all bits from this register

	IMPORT_C static void ReadAudioDataFromFifo(TUint32 aDestAddressOffset); // 1) must allow burst transfer
	IMPORT_C static void WriteAudioDataToFifo(TUint32 aSrcAddressOffset);	  // 2) Address need to be on a 32-bit boundary

// SSP
	IMPORT_C static void EnableSsp(TState aState);
	IMPORT_C static void SetSspConfig(TSspDataSize aSize,TSspFrameFormat aFormat,TInt aClockRate);
	IMPORT_C static TUint32 ReadSspcr0();				// return all bits from this register

	IMPORT_C static void EnableSspRxFifoIrq(TState aState);
	IMPORT_C static void EnableSspTxFifoIrq(TState aState);
	IMPORT_C static void EnableSspLoopbackTest(TState aState);
	IMPORT_C static void SetSspSerialClockConfig(TPolarity aPolarity,TSspSerClkPhase aPhase);
	IMPORT_C static void SetSspTxFifoThreshold(TUint32 aThreshold);
	IMPORT_C static void SetSspRxFifoThreshold(TUint32 aThreshold);
	IMPORT_C static TUint32 ReadSspcr1();				// return all bits from this register

	IMPORT_C static TBool IsSspTxFifoFull();
	IMPORT_C static TBool IsSspRxFifoEmpty();
	IMPORT_C static TBool IsSspBusy();
	IMPORT_C static TBool IsSspTxFifoRequesting();
	IMPORT_C static TBool IsSspRxFifoRequesting();
	IMPORT_C static TBool HasSspRxFifoOverrun();
	IMPORT_C static void ClearSspRorBit();
	IMPORT_C static TUint32 GetSspTxFifoLevel();
	IMPORT_C static TUint32 GetSspRxFifoLevel();
	
	IMPORT_C static void SspTxFifoIrqTest();
	IMPORT_C static void SspRxFifoIrqTest();
	IMPORT_C static void SspRxFifoOverrunIrqTest();
	IMPORT_C static void ClearSspTestBit(TSspTest aTest);
	IMPORT_C static TUint32 ReadSspitr();				// return all bits from this register

	IMPORT_C static TUint32 ReadSspDataFromFifo();
	IMPORT_C static void WriteSspDataToFifo(TUint32 aValue);

// PS/2 KBD AND MOUSE
	IMPORT_C static void ForceKbdClkSignalLow(TPs2Sel aDevice);	// use these 2 and a timer to create
	IMPORT_C static void ReleaseKbdClkSignal(TPs2Sel aDevice);	// a 1uS request-to-send pulse
	IMPORT_C static void ForceKbdDataSignalLow(TPs2Sel aDevice); // use these 2 and a timer to create
	IMPORT_C static void ReleaseKbdDataSignal(TPs2Sel aDevice);	 // a 1uS request-to-send pulse
	IMPORT_C static void EnablePs2Device(TPs2Sel aDevice, TState aState);
	IMPORT_C static TUint32 ReadKbdcr(TPs2Sel aDevice);		// return all bits from this register

	IMPORT_C static TUint32 ReadKbdIfSignals(TPs2Sel aDevice); // returns state of KbdClk and KbdData
	IMPORT_C static TUint32 ReadParityBit(TPs2Sel aDevice);	// returns 1 or 0 (LSB aligned)
	IMPORT_C static TBool IsPs2DeviceEnabled(TPs2Sel aDevice);
	IMPORT_C static TBool IsPs2RxBusy(TPs2Sel aDevice);
	IMPORT_C static TBool IsPs2RxFull(TPs2Sel aDevice);
	IMPORT_C static TBool IsPs2TxBusy(TPs2Sel aDevice);
	IMPORT_C static TBool IsPs2TxEmpty(TPs2Sel aDevice);
	IMPORT_C static TBool IsPs2StopBitError(TPs2Sel aDevice);
	IMPORT_C static void ClearPs2StopBitError(TPs2Sel aDevice);

	IMPORT_C static void WriteDataToPs2Device(TPs2Sel aDevice, TUint32 aValue);
	IMPORT_C static TUint32 ReadDataFromPs2Device(TPs2Sel aDevice);

	IMPORT_C static void SetPs2DeviceClockConfig(TPs2Sel aDevice, TPs2DividerRates aDivider, TUint32 aCount);

	IMPORT_C static void Ps2TxEmptyIrqTest(TPs2Sel aDevice);
	IMPORT_C static void Ps2RxFullIrqTest(TPs2Sel aDevice);
	IMPORT_C static void Ps2StopBitErrIrqTest(TPs2Sel aDevice);
	IMPORT_C static void ClearPs2TestBit(TPs2Sel aDevice, TPs2Test aTest);
	IMPORT_C static TUint32 ReadKbditr(TPs2Sel aDevice);		// return all bits from this register

// GPIO
//
// GPIO has 3 channels: A (4 bit), B (6 bit) and C (8 bit). For each channel there are:
//		- a Data-Read and a Data-Write regiters
//		- a Direction register
//		- a Sleep Set register
//		- a Sleep Direction register
//	The following routines assume the user may want to read/write/modify bits from
//	different ports simultaneously. Therefore the accessor routines should access all 3 
//	ports at once and use a 32-bit value constructed from the individual port values.
//	Two helper function are provided:
//	1) to pack the individual values for the 3 ports into a 32-bit word to be passed to
//	   SetPort,ClearPort and ModifyPort.
//	2) to unpack from a 32-bit word read to the indiviual port values (use after ReadPort)
//	SetPortSleepData, ModifyPortSleepData act on the sleep state of the ports before
//	transiting to that state. Therefore they:
//		- do not need to be atomic-like operations
//		- can be done on a per port basis.
//	ReadPortSleepStateReg only returns the value written to Sleep State Register of each port 
//	(not the values on the pins).
//	All other operations (on port DDRs) are done on a per port basis.
//
	IMPORT_C static TUint32 ReadPort();						// all ports at once (A,B and C)
	IMPORT_C static void SetPort(TUint32 aSetMask); 									// ibid.
	IMPORT_C static void ClearPort(TUint32 aClearMask);								// ibid.
	IMPORT_C static void ModifyPort(TUint32 aClearMask,TUint32 aSetMask);				// ibid.
	IMPORT_C static TUint32 ReadPortDdr(TGpioPort aPort);		// on a per port basis (A,B or C)
	IMPORT_C static void WritePortDdr(TGpioPort aPort, TUint32 aValue);					// ibid.
	IMPORT_C static void ModifyPortDdr(TGpioPort aPort, TUint32 aClearMask,TUint32 aSetMask);// ibid.
	IMPORT_C static TUint32 ReadPortSleepDdr(TGpioPort aPort);						// ibid
	IMPORT_C static void WritePortSleepDdr(TGpioPort aPort, TUint32 aValue);			// ibid
	IMPORT_C static void ModifyPortSleepDdr(TGpioPort aPort,TUint32 aClearMask,TUint32 aSetMask);// ibid
	IMPORT_C static void WritePortSleepData(TGpioPort aPort,TUint32 aValue);			// ibid.
	IMPORT_C static void ModifyPortSleepData(TGpioPort aPort,TUint32 aClearMask,TUint32 aSetMask);// ibid.
	IMPORT_C static TUint32 ReadPortSleepStateReg(TGpioPort aPort);					// ibid.
	IMPORT_C static void UnpackPorts(TUint32 &aReadVal, TUint32* aPortAValPtr, TUint32* aPortBValPtr, TUint32* aPortCValPtr);
	IMPORT_C static TUint32 PackPorts(TUint32 aPortAVal, TUint32 aPortBVal, TUint32 aPortCVal);

// Interrupt Controller
//
//	The Interrupt controller allows 50 independently programmable Interrupt or Wake-up sources.
//	It has got 2 sets of registers: set 0 for Int sources 0-32, and 1 for Int sources 33-54
//	It includes registers for masking and selecting polarity of both Interrupts and Wake-up
//	sources, reading the state of the Ints/wake-up signals and clearing them and also testing
//	the controller by setting individual sources.
//	The routines below allow:
//		- enabling/disabling interrupt/wake-up on a per source basis (identified)
//		- reading interrupt/wake-up enable registers (2) and modifying the enable masks - per set basis 
//		- selecting polarity on a per source basis (identified)
//		- reading the polarity registers (2) and modifying them - per set basis
//		- clearing a source on a per source basis (identified)
//		- enquiry if a particular source has interrupted or woken-up - per source basis
//		- reading the interrupt/wake-ip state of all sources at once - per set basis
//		- selecting between Int or Wake-up mode and between Test and normal mode
//		- setting the sources for test purposes - on a per set basis
//	The register pair INTTEST0-1 has not been contenplated as it is only used for production 
//	tests.
//
	IMPORT_C static void DisableAllInterrupts();						// all at once
	IMPORT_C static void EnableInt(TIntSource aSource, TState aState);	// on a per source basis
	IMPORT_C static void EnableWkUp(TIntSource aSource, TState aState);				// ibid.
	IMPORT_C static void SetIntPolarity(TIntSource aSource, TActiveEdge anEdge);	// ibid.
	IMPORT_C static void SetWkUpPolarity(TIntSource aSource, TActiveEdge anEdge);	// ibid.
	IMPORT_C static void ClearIntSource(TIntSource aSource);						// ibid.
	IMPORT_C static TBool IsIntSet(TIntSource aSource);								// ibid.
	IMPORT_C static TUint32 ReadIntMask(TIntSet aSet);					// on a per set basis
	IMPORT_C static void ModifyIntMask(TUint32 aClearMask,TUint32 aSetMask,TIntSet aSet);// ibid.
	IMPORT_C static TUint32 ReadWkUpMask(TIntSet aSet);								// ibid.
	IMPORT_C static void ModifyWkUpMask(TUint32 aClearMask,TUint32 aSetMask,TIntSet aSet);// ibid.
	IMPORT_C static TUint32 ReadIntPolarity(TIntSet aSet);							//  ibid.
	IMPORT_C static void ModifyIntPolarity(TUint32 aClearMask,TUint32 aSetMask,TIntSet aSet);// ibid.
	IMPORT_C static TUint32 ReadWkUpPolarity(TIntSet aSet);							//  ibid.
	IMPORT_C static void ModifyWkUpPolarity(TUint32 aClearMask,TUint32 aSetMask,TIntSet aSet);// ibid.
	IMPORT_C static TUint32 ReadIntSource(TIntSet aSet);								//  ibid.
	IMPORT_C static void ModifyIntStateTestReg(TUint32 aClearMask,TUint32 aSetMask,TIntSet aSet);// ibid.
	IMPORT_C static void SelectIntContMode(TIntContMode aMode);
	IMPORT_C static void EnableIntContTest(TState aState);

// PCMCIA
	IMPORT_C static TBool IsSocketReady(TPcCardSocket aSocket);
	IMPORT_C static TBool IsSocketDetect(TPcCardSocket aSocket);
	IMPORT_C static TBool IsSocketVoltageSense1(TPcCardSocket aSocket);
	IMPORT_C static TBool IsSocketVoltageSense2(TPcCardSocket aSocket);
	IMPORT_C static TBool IsSocketIo16(TPcCardSocket aSocket);
	IMPORT_C static TBool IsSocketBvd1_CardStatusChange(TPcCardSocket aSocket);
	IMPORT_C static TBool IsSocketBvd2_SpeakerChange(TPcCardSocket aSocket);

	IMPORT_C static void ActivateSocketReset(TPcCardSocket aSocket);
	IMPORT_C static void DeactivateSocketReset(TPcCardSocket aSocket);
	IMPORT_C static void EnableSocketFloat(TPcCardSocket aSocket, TState aState);
	IMPORT_C static void EnableSocketPWait(TPcCardSocket aSocket, TState aState);
	IMPORT_C static void EnableSocketVoltageSel(TPcCardSocket aSocket, TPcCardVoltage aVoltage);
	IMPORT_C static void ResetPccr();
	IMPORT_C static TUint32 ReadPcCardPccr();				// return all bits from this register

	IMPORT_C static void SetSocketSleepState(TPcCardSocket aSocket, TPcCardSleepState aState);
	IMPORT_C static TUint32 ReadPcCardPcssr();			// return all bits from this register

private:
	static inline TUint32 Register32(TUint32 anAddr);
	static inline void SetRegister32(TUint32 aValue,TUint32 anAddr);
	static inline void ModifyRegister32(TUint32 aClearMask,TUint32 aSetMask,TUint32 anAddr);

private:
	static const TUint32 IntSourceArray0[27];
	static const TUint32 IntSourceArray1[23];

private:
	TUint32 GPIOfollower;
    TUint32 iHwChunkLinAddr;
};

#endif