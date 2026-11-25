// A32COTULLA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
// Copyright (c) 2001 Intel Corp. All rights reserved
//

//
// This file is part of the Cotulla Base port
//
// This declares the ASSP access class (TCotulla), which is
// used to protect the code from direct access to hardware addresses
//
// TCotulla provides various functions through which the hardware
// is accessed. This also allows the variant layer to link to the
// kernel and use TCotulla for hardware access.
//
// The class defined here is not intended to represent any real hardware,
// it is just a simple example of what an ASSP class might look like.
//

#ifndef __A32COTULLA_H__
#define __A32COTULLA_H__
#include <e32std.h>
#include <k32std.h>

extern TUint SABINAL;	// Initialized in ka_ini.cpp and used in ka_utl.cpp


/**
 * Each interrupt must have a name by which other code refers to it
 */

// Strings coresponding to the 32 first level interrupt sources.
_LIT8(KIrqReserved0,	"IrqReserved0");
_LIT8(KIrqReserved1,	"IrqReserved1");
_LIT8(KIrqReserved2,	"IrqReserved2");
_LIT8(KIrqReserved3,	"IrqReserved3");
_LIT8(KIrqReserved4,	"IrqReserved4");
_LIT8(KIrqReserved5,	"IrqReserved5");
_LIT8(KIrqReserved6,	"IrqReserved6");
_LIT8(KIrqReserved7,	"IrqReserved7");
_LIT8(KIrqGpioEdge0,	"IrqGpioEdge0");
_LIT8(KIrqGpioEdge1,	"IrqGpioEdge1");
_LIT8(KIrqGpioEdge2_80, "IrqGpioEdge2_80");
_LIT8(KIrqUsb,			"IrqUsb");
_LIT8(KIrqPmu,			"IrqPmu");
_LIT8(KIrqI2S,			"IrqI2S");
_LIT8(KIrqAC97,			"IrqAC97");
_LIT8(KIrqAdc,			"IrqAdc");
_LIT8(KIrqAdcTouch,		"IrqAdcTouch");
_LIT8(KIrqLcd,			"IrqLcd");
_LIT8(KIrqI2C,			"IrqI2C");
_LIT8(KIrqIcp,			"IrqIcp");
_LIT8(KIrqSTUart,		"IrqSTUart");
_LIT8(KIrqBTUart,		"IrqBTUart");
_LIT8(KIrqFFUart,		"IrqFFUart");
_LIT8(KIrqMmc,			"IrqMmc");
_LIT8(KIrqSsp,			"IrqSsp");
_LIT8(KIrqDmaChannel0_15,	"IrqDmaChannel0_15");
_LIT8(KIrqOstMatch0,	"IrqOstMatch0");
_LIT8(KIrqOstMatch1,	"IrqOstMatch1");
_LIT8(KIrqOstMatch2,	"IrqOstMatch2");
_LIT8(KIrqWatchdog,		"IrqWatchdog");
_LIT8(KIrqRtcTick,		"IrqRtcTick");
_LIT8(KIrqRtcAlarm,		"IrqRtcAlarm");
_LIT8(KIrqGpioEdge2,	"IrqGpioEdge2");
_LIT8(KIrqGpioEdge3,	"IrqGpioEdge3");
_LIT8(KIrqGpioEdge4,	"IrqGpioEdge4");
_LIT8(KIrqGpioEdge5,	"IrqGpioEdge5");
_LIT8(KIrqGpioEdge6,	"IrqGpioEdge6");
_LIT8(KIrqGpioEdge7,	"IrqGpioEdge7");
_LIT8(KIrqGpioEdge8,	"IrqGpioEdge8");
_LIT8(KIrqGpioEdge9,	"IrqGpioEdge9");
_LIT8(KIrqGpioEdge10,	"IrqGpioEdge10");
_LIT8(KIrqGpioEdge11,	"IrqGpioEdge11");		// conceptual interrupts
_LIT8(KIrqGpioEdge12,	"IrqGpioEdge12");
_LIT8(KIrqGpioEdge13,	"IrqGpioEdge13");
_LIT8(KIrqGpioEdge14,	"IrqGpioEdge14");
_LIT8(KIrqGpioEdge15,	"IrqGpioEdge15");
_LIT8(KIrqGpioEdge16,	"IrqGpioEdge16");
_LIT8(KIrqGpioEdge17,	"IrqGpioEdge17");
_LIT8(KIrqGpioEdge18,	"IrqGpioEdge18");
_LIT8(KIrqGpioEdge19,	"IrqGpioEdge19");
_LIT8(KIrqGpioEdge20,	"IrqGpioEdge20");
_LIT8(KIrqGpioEdge21,	"IrqGpioEdge21");
_LIT8(KIrqGpioEdge22,	"IrqGpioEdge22");
_LIT8(KIrqGpioEdge23,	"IrqGpioEdge23");
_LIT8(KIrqGpioEdge24,	"IrqGpioEdge24");
_LIT8(KIrqGpioEdge25,	"IrqGpioEdge25");
_LIT8(KIrqGpioEdge26,	"IrqGpioEdge26");
_LIT8(KIrqGpioEdge27,	"IrqGpioEdge27");
_LIT8(KIrqGpioEdge28,	"IrqGpioEdge28");
_LIT8(KIrqGpioEdge29,	"IrqGpioEdge29");
_LIT8(KIrqGpioEdge30,	"IrqGpioEdge30");
_LIT8(KIrqGpioEdge31,	"IrqGpioEdge31");
_LIT8(KIrqGpioEdge32,	"IrqGpioEdge32");
_LIT8(KIrqGpioEdge33,	"IrqGpioEdge33");
_LIT8(KIrqGpioEdge34,	"IrqGpioEdge34");
_LIT8(KIrqGpioEdge35,	"IrqGpioEdge35");
_LIT8(KIrqGpioEdge36,	"IrqGpioEdge36");
_LIT8(KIrqGpioEdge37,	"IrqGpioEdge37");
_LIT8(KIrqGpioEdge38,	"IrqGpioEdge38");
_LIT8(KIrqGpioEdge39,	"IrqGpioEdge39");
_LIT8(KIrqGpioEdge40,	"IrqGpioEdge40");
_LIT8(KIrqGpioEdge41,	"IrqGpioEdge41");
_LIT8(KIrqGpioEdge42,	"IrqGpioEdge42");
_LIT8(KIrqGpioEdge43,	"IrqGpioEdge43");
_LIT8(KIrqGpioEdge44,	"IrqGpioEdge44");
_LIT8(KIrqGpioEdge45,	"IrqGpioEdge45");
_LIT8(KIrqGpioEdge46,	"IrqGpioEdge46");
_LIT8(KIrqGpioEdge47,	"IrqGpioEdge47");
_LIT8(KIrqGpioEdge48,	"IrqGpioEdge48");
_LIT8(KIrqGpioEdge49,	"IrqGpioEdge49");
_LIT8(KIrqGpioEdge50,	"IrqGpioEdge50");
_LIT8(KIrqGpioEdge51,	"IrqGpioEdge51");
_LIT8(KIrqGpioEdge52,	"IrqGpioEdge52");
_LIT8(KIrqGpioEdge53,	"IrqGpioEdge53");
_LIT8(KIrqGpioEdge54,	"IrqGpioEdge54");
_LIT8(KIrqGpioEdge55,	"IrqGpioEdge55");
_LIT8(KIrqGpioEdge56,	"IrqGpioEdge56");
_LIT8(KIrqGpioEdge57,	"IrqGpioEdge57");
_LIT8(KIrqGpioEdge58,	"IrqGpioEdge58");
_LIT8(KIrqGpioEdge59,	"IrqGpioEdge59");
_LIT8(KIrqGpioEdge60,	"IrqGpioEdge60");
_LIT8(KIrqGpioEdge61,	"IrqGpioEdge61");
_LIT8(KIrqGpioEdge62,	"IrqGpioEdge62");
_LIT8(KIrqGpioEdge63,	"IrqGpioEdge63");
_LIT8(KIrqGpioEdge64,	"IrqGpioEdge64");
_LIT8(KIrqGpioEdge65,	"IrqGpioEdge65");
_LIT8(KIrqGpioEdge66,	"IrqGpioEdge66");
_LIT8(KIrqGpioEdge67,	"IrqGpioEdge67");
_LIT8(KIrqGpioEdge68,	"IrqGpioEdge68");
_LIT8(KIrqGpioEdge69,	"IrqGpioEdge69");
_LIT8(KIrqGpioEdge70,	"IrqGpioEdge70");
_LIT8(KIrqGpioEdge71,	"IrqGpioEdge71");
_LIT8(KIrqGpioEdge72,	"IrqGpioEdge72");
_LIT8(KIrqGpioEdge73,	"IrqGpioEdge73");
_LIT8(KIrqGpioEdge74,	"IrqGpioEdge74");
_LIT8(KIrqGpioEdge75,	"IrqGpioEdge75");
_LIT8(KIrqGpioEdge76,	"IrqGpioEdge76");
_LIT8(KIrqGpioEdge77,	"IrqGpioEdge77");
_LIT8(KIrqGpioEdge78,	"IrqGpioEdge78");
_LIT8(KIrqGpioEdge79,	"IrqGpioEdge79");
_LIT8(KIrqGpioEdge80,	"IrqGpioEdge80");

_LIT8(KIrqExt0, "IrqExt0");				// external interrupts
_LIT8(KIrqExt1, "IrqExt1");
_LIT8(KIrqExt2, "IrqExt2");
_LIT8(KIrqExt3, "IrqExt3");
_LIT8(KIrqExt4, "IrqExt4");
_LIT8(KIrqExt5, "IrqExt5");
_LIT8(KIrqExt6, "IrqExt6");
_LIT8(KIrqExt7, "IrqExt7");
_LIT8(KIrqExt8, "IrqExt8");
_LIT8(KIrqExt9, "IrqExt9");
_LIT8(KIrqExt10, "IrqExt10");
_LIT8(KIrqExt11, "IrqExt11");
_LIT8(KIrqExt12, "IrqExt12");
_LIT8(KIrqExt13, "IrqExt13");
_LIT8(KIrqExt14, "IrqExt14");
_LIT8(KIrqExt15, "IrqExt15");
_LIT8(KIrqExt16, "IrqExt16");
_LIT8(KIrqExt17, "IrqExt17");
_LIT8(KIrqExt18, "IrqExt18");
_LIT8(KIrqExt19, "IrqExt19");
_LIT8(KIrqExt20, "IrqExt20");
_LIT8(KIrqExt21, "IrqExt21");
_LIT8(KIrqExt22, "IrqExt22");
_LIT8(KIrqExt23, "IrqExt23");
_LIT8(KIrqExt24, "IrqExt24");
_LIT8(KIrqExt25, "IrqExt25");
_LIT8(KIrqExt26, "IrqExt26");
_LIT8(KIrqExt27, "IrqExt27");
_LIT8(KIrqExt28, "IrqExt28");
_LIT8(KIrqExt29, "IrqExt29");
_LIT8(KIrqExt30, "IrqExt30");
_LIT8(KIrqExt31, "IrqExt31");
_LIT8(KIrqExt32, "IrqExt32");
_LIT8(KIrqExt33, "IrqExt33");
_LIT8(KIrqExt34, "IrqExt34");
_LIT8(KIrqExt35, "IrqExt35");
_LIT8(KIrqExt36, "IrqExt36");
_LIT8(KIrqExt37, "IrqExt37");
_LIT8(KIrqExt38, "IrqExt38");
_LIT8(KIrqExt39, "IrqExt39");
_LIT8(KIrqExt40, "IrqExt40");
_LIT8(KIrqExt41, "IrqExt41");
_LIT8(KIrqExt42, "IrqExt42");
_LIT8(KIrqExt43, "IrqExt43");
_LIT8(KIrqExt44, "IrqExt44");
_LIT8(KIrqExt45, "IrqExt45");
_LIT8(KIrqExt46, "IrqExt46");
_LIT8(KIrqExt47, "IrqExt47");
_LIT8(KIrqExt48, "IrqExt48");
_LIT8(KIrqExt49, "IrqExt49");
_LIT8(KIrqExt50, "IrqExt50");
_LIT8(KIrqExt51, "IrqExt51");
_LIT8(KIrqExt52, "IrqExt52");
_LIT8(KIrqExt53, "IrqExt53");
_LIT8(KIrqExt54, "IrqExt54");
_LIT8(KIrqExt55, "IrqExt55");
_LIT8(KIrqExt56, "IrqExt56");
_LIT8(KIrqExt57, "IrqExt57");
_LIT8(KIrqExt58, "IrqExt58");
_LIT8(KIrqExt59, "IrqExt59");
_LIT8(KIrqExt60, "IrqExt60");
_LIT8(KIrqExt61, "IrqExt61");
_LIT8(KIrqExt62, "IrqExt62");
_LIT8(KIrqExt63, "IrqExt63");

_LIT8(KIrqDmaChannel0,	"IrqDmaChannel0");	// dma channels interrupt
_LIT8(KIrqDmaChannel1,	"IrqDmaChannel1");
_LIT8(KIrqDmaChannel2,	"IrqDmaChannel2");
_LIT8(KIrqDmaChannel3,	"IrqDmaChannel3");
_LIT8(KIrqDmaChannel4,	"IrqDmaChannel4");
_LIT8(KIrqDmaChannel5,	"IrqDmaChannel5");
_LIT8(KIrqDmaChannel6,	"IrqDmaChannel6");
_LIT8(KIrqDmaChannel7,	"IrqDmaChannel7");
_LIT8(KIrqDmaChannel8,	"IrqDmaChannel8");
_LIT8(KIrqDmaChannel9,	"IrqDmaChannel9");
_LIT8(KIrqDmaChannel10,	"IrqDmaChannel10");
_LIT8(KIrqDmaChannel11,	"IrqDmaChannel11");
_LIT8(KIrqDmaChannel12,	"IrqDmaChannel12");
_LIT8(KIrqDmaChannel13,	"IrqDmaChannel13");
_LIT8(KIrqDmaChannel14,	"IrqDmaChannel14");
_LIT8(KIrqDmaChannel15,	"IrqDmaChannel15");


/**
 * Constant conventions
 * KH		Hardware definition
 * KHw		4-byte word definition prefix
 * KHb		Byte definition prefix
 * KHt		Bit definition prefix
 * KHm		Mask definition prefix
 * KHs		Shift definition prefix
 * KHo		Offset definition prefix
 * KHwRo	Read-only register
 * KHwWo	Write-only register
 * KHwRw	Read/write register
 * KHwBase	Base address within memory map
 * _i		Input suffix
 * _o		Output suffix
 * _b		Input/output suffix
 */

/**
 * Memory map : these are physical addresses
 */

const TUint KHwBaseStatic0		=	0x00000000;						// static chip selects
const TUint KHwBaseStatic1		=	KHwBaseStatic0 + 64*KMega;
const TUint KHwBaseStatic2		=	KHwBaseStatic1 + 64*KMega;
const TUint KHwBaseStatic3		=	KHwBaseStatic2 + 64*KMega;
const TUint KHwBaseStatic4		=	KHwBaseStatic3 + 64*KMega;
const TUint KHwBaseStatic5		=	KHwBaseStatic4 + 64*KMega;

const TUint KHwBasePcmcia0		=	0x20000000;
const TUint KHwBasePcmcia1		=	KHwBasePcmcia0 + 256*KMega;

const TUint KHwBaseRegisters	=	0x40000000;
const TUint KHwBasePeripherals	=	KHwBaseRegisters;				// 4000.0000
const TUint KHwBaseLcdControl	=	KHwBaseRegisters + 64*KMega;	// 4400.0000
const TUint KHwBaseMemAndExp	=	KHwBaseLcdControl + 64*KMega;	// 4800.0000

const TUint KHwBaseDram0		=	0xA0000000;
const TUint KHwBaseDram1		=	KHwBaseDram0 + 64*KMega;
const TUint KHwBaseDram2		=	KHwBaseDram1 + 64*KMega;
const TUint KHwBaseDram3		=	KHwBaseDram2 + 64*KMega;

//const TUint KHwBaseFrameBuffer	=	KHwBaseDram0 + 15*KMega;
const TUint KHwBaseFrameBuffer	=	KHwBaseDram0 + 1*KMega;

/**
 * Memory map: linear addresses
 * All linear addresses must be consistent with the bootstrap BDB
 */

const TUint KHwLinBaseVideo			=	0x30000000;
const TUint KHwLinBaseRam			=	0x40000000;
const TUint KHwLinBaseRom			=	0x50000000;
const TUint KHwLinBaseRegisters		=	0x58000000;
const TUint KHwLinBaseRegSpacing	=	0x1000;		// MMU small page size

// DMA		Physical base = 4000.0000
const TUint KHwBaseDma		=	KHwLinBaseRegisters + 0x00*KHwLinBaseRegSpacing;
// FFUART	Physical base = 4010.0000
const TUint KHwBaseFfUart	=	KHwLinBaseRegisters + 0x01*KHwLinBaseRegSpacing;
// BTUART	Physical base = 4020.0000
const TUint KHwBaseBtUart	=	KHwLinBaseRegisters + 0x02*KHwLinBaseRegSpacing;
// I2C		Physical base = 4030.0000
const TUint KHwBaseI2C		=	KHwLinBaseRegisters + 0x03*KHwLinBaseRegSpacing;
// I2S		Physical base = 4040.0000
const TUint KHwBaseI2S		=	KHwLinBaseRegisters + 0x04*KHwLinBaseRegSpacing;
// AC97		Physical base = 4050.0000
const TUint KHwBaseAc97		=	KHwLinBaseRegisters + 0x05*KHwLinBaseRegSpacing;
// UDC		Physical base = 4060.0000
const TUint KHwBaseUdc		=	KHwLinBaseRegisters + 0x06*KHwLinBaseRegSpacing;
// STUART	Physical base = 4070.0000
const TUint KHwBaseStUart	=	KHwLinBaseRegisters + 0x07*KHwLinBaseRegSpacing;
// ICP		Physical base = 4080.0000
const TUint KHwBaseIcp		=	KHwLinBaseRegisters + 0x08*KHwLinBaseRegSpacing;
// RTC		Physical base = 4090.0000
const TUint KHwBaseRtc		=	KHwLinBaseRegisters + 0x09*KHwLinBaseRegSpacing;
// OST		Physical base = 40A0.0000
const TUint KHwBaseOst		=	KHwLinBaseRegisters + 0x0A*KHwLinBaseRegSpacing;
// PWM0		Physical base = 40B0.0000
const TUint KHwBasePwm0		=	KHwLinBaseRegisters + 0x0B*KHwLinBaseRegSpacing;
// PWM1		Physical base = 40C0.0000
const TUint KHwBasePwm1		=	KHwLinBaseRegisters + 0x0C*KHwLinBaseRegSpacing;
// INT		Physical base = 40D0.0000
const TUint KHwBaseInts		=	KHwLinBaseRegisters + 0x0D*KHwLinBaseRegSpacing;
// GPIO		Physical base = 40E0.0000
const TUint KHwBaseGpio		=	KHwLinBaseRegisters + 0x0E*KHwLinBaseRegSpacing;
// PWR		Physical base = 40F0.0000
const TUint KHwBasePwr		=	KHwLinBaseRegisters + 0x0F*KHwLinBaseRegSpacing;
// SSP		Physical base = 4100.0000
const TUint KHwBaseSsp		=	KHwLinBaseRegisters + 0x10*KHwLinBaseRegSpacing;
// MMC		Physical base = 4110.0000
const TUint KHwBaseMmc		=	KHwLinBaseRegisters + 0x11*KHwLinBaseRegSpacing;
// Clocks	Physical base = 4130.0000
const TUint KHwBaseClocks	=	KHwLinBaseRegisters + 0x12*KHwLinBaseRegSpacing;
// LCD		Physical base = 4400.0000
const TUint KHwBaseLcd		=	KHwLinBaseRegisters + 0x13*KHwLinBaseRegSpacing;
// MEM		Physical base = 4800.0000
const TUint KHwBaseMexp		=	KHwLinBaseRegisters + 0x14*KHwLinBaseRegSpacing;
// EXT      Physical base = Externally Determined in Variant 
const TUint KHwBaseExternal =   KHwLinBaseRegisters + 0x15*KHwLinBaseRegSpacing;

// Magic Gone into standby value.
const TUint KHwMagicEnterStandbyValue=0xBeADead1; //referenced in bootstrap code

// Hex LED - naughty doing this here but it is very useful to have this
// N.B value would not be appropriate for Sabinal
const TUint KHwRwExtLed       = KHwBaseExternal + 0x10;
const TUint KHwRwExtBlankLed       = KHwBaseExternal + 0x40;

/** 
 * Cotulla DMA Registers and Masks
 */

//DMA control registers - Phys Base Addr and Byte Offsets from base
const TUint KDmaBaseAddr          	= KHwBaseDma;
const TUint KDmaReqToChanMap      	= 0x0100;       //40 DRCMR regs  
const TUint KDmaRegisterSize		= 0x04;			//word-size register
const TUint KDmaChannelSize 	    = 0x10;  
const TUint KDmaInterruptReg		= 0xf0;			//1 DINT reg only
const TUint KDmaControlStatusReg	= 0x00;			//1 DCSR per channel
const TUint KDmaDescAddrReg			= 0x0200;		//1 per channel
const TUint KDmaSourceAddrReg    	= 0x0204;        //1 per channel
const TUint KDmaTargetAddrReg    	= 0x0208;		//1 per channel
const TUint KDmaCmdAddrReg    		= 0x020C;		//1 per channel

//DMA DCSR register masks
const TUint KDmaBusErrIntrMask     =KBit0;   //resettable status bit
const TUint KDmaStartIntrMask      =KBit1;
const TUint KDmaEndIntrMask        =KBit2;
const TUint KDmaStopIntrMask       =KBit3;		
const TUint KDmaReqPendMask        =KBit8;   //ro status bit
const TUint KDmaStopIrqEnMask      =KBit29;
const TUint KDmaNoDescFetchMask    =KBit30;  
const TUint KDmaRunMask            =KBit31;  //status only

//DMA DRCMRx register masks
const TUint  KDmaChnNum            =0xf;
const TUint  KDmaMapVld            =KBit7;

//DMA DINT register masks
const TUint KDmaChlIntr0Mask          =KBit0;
const TUint KDmaChlIntr1Mask          =KBit1;
const TUint KDmaChlIntr2Mask          =KBit2;
const TUint KDmaChlIntr3Mask          =KBit3;
const TUint KDmaChlIntr4Mask          =KBit4;
const TUint KDmaChlIntr5Mask          =KBit5;
const TUint KDmaChlIntr6Mask          =KBit6;
const TUint KDmaChlIntr7Mask          =KBit7;
const TUint KDmaChlIntr8Mask          =KBit8;
const TUint KDmaChlIntr9Mask          =KBit9;
const TUint KDmaChlIntr10Mask         =KBit10;
const TUint KDmaChlIntr11Mask         =KBit11;
const TUint KDmaChlIntr12Mask         =KBit12;
const TUint KDmaChlIntr13Mask         =KBit13;
const TUint KDmaChlIntr14Mask         =KBit14;
const TUint KDmaChlIntr15Mask         =KBit15;

//DMA Descriptor Address Register Masks
const TUint KDmaStopMask              =KBit0;
const TUint KDmaDescriptorAddress     =0xfffffff0;

//DMA Source Address Register Masks
const TUint KDmaSrcAddr     =0xfffffffc;

//DMA Target Address Register Masks
const TUint KDmaTrgAddr     =0xfffffffc;

//DMA Command Register Masks
const TUint KDmaLenMask         =0x00001fff;
const TUint KDmaWidthMask       =0x0000c000;
const TUint KDmaSizeMask        =0x00030000;
const TUint KDmaEndianMask      =0x00040000;
const TUint KDmaFlyByTMask      =0x00080000;
const TUint KDmaFlyBySMask      =0x00100000;
const TUint KDmaEndIrqEnMask    =0x00200000;
const TUint KDmaStartIrqEnMask  =0x00400000;
const TUint KDmaFlowTrgMask     =0x10000000;
const TUint KDmaFlowSrcMask     =0x20000000;
const TUint KDmaIncTrgAddrMask  =0x40000000;
const TUint KDmaIncSrcAddrMask  =0x80000000;

//DMA DRCMR values from Cotulla EAS table 6-4
const TUint32 KDmaTxI2SCompAddr       =0x010c;
const TUint32 KDmaTxBTUARTCompAddr    =0x0114;
const TUint32 KDmaTxFFUARTCompAddr    =0x011c;		
const TUint32 KDmaTxAC97ModemCompAddr =0x0128;
const TUint32 KDmaTxAC97AudioCompAddr =0x0130;
const TUint32 KDmaTxSSPCompAddr       =0x0138;
const TUint32 KDmaTxICPCompAddr       =0x0148;
const TUint32 KDmaTxSTUARTCompAddr    =0x0150;
const TUint32 KDmaTxMMCCompAddr       =0x0158;
const TUint32 KDmaTxUSB1CompAddr      =0x0164;
const TUint32 KDmaTxUSB3CompAddr      =0x016c;
const TUint32 KDmaTxUSB6CompAddr      =0x0178;
const TUint32 KDmaTxUSB8CompAddr      =0x0180;
const TUint32 KDmaTxUSB11CompAddr     =0x018c;
const TUint32 KDmaTxUSB13CompAddr     =0x0194;

const TUint32 KDmaRxI2SCompAddr       =0x0108;
const TUint32 KDmaRxBTUARTCompAddr    =0x0110;
const TUint32 KDmaRxFFUARTCompAddr    =0x0118;
const TUint32 KDmaRxAC97MicCompAddr   =0x0120;		
const TUint32 KDmaRxAC97ModemCompAddr =0x0124;
const TUint32 KDmaRxAC97AudioCompAddr =0x012c;
const TUint32 KDmaRxSSPCompAddr       =0x0134;
const TUint32 KDmaRxICPCompAddr       =0x0144;
const TUint32 KDmaRxSTUARTCompAddr    =0x014c;
const TUint32 KDmaRxMMCCompAddr       =0x0154;
const TUint32 KDmaRxUSB2CompAddr      =0x0168;
const TUint32 KDmaRxUSB4CompAddr      =0x0170;
const TUint32 KDmaRxUSB7CompAddr      =0x017c;
const TUint32 KDmaRxUSB9CompAddr      =0x0184;
const TUint32 KDmaRxUSB12CompAddr     =0x0190;
const TUint32 KDmaRxUSB14CompAddr     =0x0198;

const TUint KDmaClearStatusBits		  =0x20000007;

/**
 * Cotulla On-board modules
 */

/**
 * O/S timer
 */
const TUint KHwRwOstOsmr0		=	KHwBaseOst + 0x00;
const TUint KHwRwOstOsmr1		=	KHwBaseOst + 0x04;
const TUint KHwRwOstOsmr2		=	KHwBaseOst + 0x08;
const TUint KHwRwOstOsmr3		=	KHwBaseOst + 0x0c;
const TUint KHwRwOstOscr		=	KHwBaseOst + 0x10;
const TUint KHwRwOstOssr		=	KHwBaseOst + 0x14;
const TUint KHwRwOstOwer		=	KHwBaseOst + 0x18;
const TUint KHwRwOstOier		=	KHwBaseOst + 0x1c;

// Gap between OSMR registers
const TUint KHwRwOstOsmrGap		=	0x04;
// Number of match registers
const TUint KHwOstMaxMatch		=	3;	// Assume watchdog is to be used
const TUint	KHwRwOstOsmrWatchdog=	KHwRwOstOsmr3;

// Status for a given match
#define KHtOstOssrM(timer)			(KBit0<<(timer))

// Watchdog enable
const TUint KHtOstOwerWme		=	KBit0;

// Int enable for a given match
#define KHtOstOierE(timer)			(KBit0<<(timer))

// Match allocation
const TUint KHwOstMatchGeneral	=	0;		// Match 0 used as general-purpose timer
const TUint KHwOstMatch64HzTick	=	1;		// Match 1 used for 64Hz timer
const TUint KHwOstMatchMsTimer	=	2;		// Match 2 used for the ms timer.
const TUint KHwOstMatchWatchdog	=	3;		// Match 3 used as watchdog

// Match allocation in interrupt mask register
#define KHtIntsOstMatchGeneral	KHtIntsSrcOstMatch0
#define KHtIntsOstMatch64HzTick	KHtIntsSrcOstMatch1
#define KHtIntsOstMatchMsTimer	KHtIntsSrcOstMatch2
#define KHtIntsOstMatchWatchdog	KHtIntsSrcOstMatch3

/**
 * Real-time clock
 */
const TUint KHwRwRtcRcnr  		=	KHwBaseRtc + 0x00;
const TUint KHwRwRtcRtar		=	KHwBaseRtc + 0x04;
const TUint KHwRwRtcRtsr		=	KHwBaseRtc + 0x08;
const TUint KHwRwRtcRttr 		=	KHwBaseRtc + 0x0c;

// Trim
const TUint KHtRtcRttrLck 	=	KBit31;
const TUint KHsRtcRttrReserved =	26;
const TUint KHmRtcRttrReserved =    0x1f<<KHsRtcRttrReserved;
const TUint KHsRtcRttrTrimdel	=	16;
const TUint KHmRtcRttrTrimdel	=	0x000003ff<<KHsRtcRttrTrimdel;
const TUint KHsRtcRttrClkdiv	=	0;
const TUint KHmRtcRttrClkdiv	=	0x0000ffff<<KHsRtcRttrClkdiv;

// Status
const TUint KHtRtcRtsrHze		=	KBit3;
const TUint KHtRtcRtsrAle		=	KBit2;
const TUint KHtRtcRtsrHz		=	KBit1;
const TUint KHtRtcRtsrAl		=	KBit0;

/**
 * Power management and Reset Controller
 */
const TUint KHwRwPwrPmcr		=	KHwBasePwr + 0x00;
const TUint KHwRwPwrPssr		=	KHwBasePwr + 0x04;
const TUint KHwRwPwrPspr		=	KHwBasePwr + 0x08;
const TUint KHwRwPwrPwer		=	KHwBasePwr + 0x0c;
const TUint KHwRwPwrPrer		=	KHwBasePwr + 0x10;
const TUint KHwRwPwrPfer		=	KHwBasePwr + 0x14;
const TUint KHwRwPwrPedr		=	KHwBasePwr + 0x18;
const TUint KHwRwPwrPcfr		=	KHwBasePwr + 0x1c;
const TUint KHwRwPwrPgsr_x		=	KHwBasePwr + 0x20;
const TUint KHwRwPwrPgsr_y		=	KHwBasePwr + 0x24;
const TUint KHwRwPwrPgsr_z		=	KHwBasePwr + 0x28;
const TUint KHwRwPwrRcsr		=	KHwBasePwr + 0x30;

// Reset Status
const TUint KHtPwrRcsrGpr		=	KBit3;
const TUint KHtPwrRcsrSmr		=	KBit2;
const TUint KHtPwrRcsrWdr		=	KBit1;
const TUint KHtPwrRcsrHwr		=	KBit0;

// Control
const TUint KHtPwrPmcrIdae		=	KBit0; 

// Configuration
const TUint KHtPwrPcfrDs		=	KBit3; 
const TUint KHtPwrPcfrFs		=	KBit2;
const TUint KHtPwrPcfrFp		=	KBit1;
const TUint KHtPwrPcfrOpde		=	KBit0;

const TUint KHwOscFreqHz		=	3686400;	// 3.6864MHz

// Wakeup enable
const TUint KHtPwrPwerRtcAlarm	=	KBit31;

const TUint KHsPwrPwerValid		=	0;
const TUint KHmPwrPwerValid		=	0x8000ffff<<KHsPwrPwerValid; 

// Sleep status
const TUint KHtPwrPssrRdh       =   KBit5; 
const TUint KHtPwrPssrPh		=	KBit4;
//const TUint KHtPwrPssrDh		=	KBit3;  
const TUint KHtPwrPssrVfs		=	KBit2;
const TUint KHtPwrPssrBfs		=	KBit1;
const TUint KHtPwrPssrSs		=	KBit0;

const TUint KHmPwrPssrReason	=	KHtPwrPssrVfs|KHtPwrPssrBfs|KHtPwrPssrSs;

// GPIO sleep state
const TUint KHmPwrPgsr_xValid		=	0xffffffff; 
const TUint KHmPwrPgsr_yValid       =   0xffffffff; 
const TUint KHmPwrPgsr_zValid       =   0x0001ffff; 
const TUint KHmPwrPgsrReservedBits_z     =  	0xFFFE0000;

// Oscillator status
// const TUint KHtPwrPosrOok		=	KBit0; 


/**
 * General-purpose I/O 
 */
const TUint KHwRoGpioGplr_x		=	KHwBaseGpio + 0x00;
const TUint KHwRoGpioGplr_y		=	KHwBaseGpio + 0x04;
const TUint KHwRoGpioGplr_z		=	KHwBaseGpio + 0x08;
const TUint KHwRwGpioGpdr_x		=	KHwBaseGpio + 0x0c;
const TUint KHwRwGpioGpdr_y		=	KHwBaseGpio + 0x10;
const TUint KHwRwGpioGpdr_z		=	KHwBaseGpio + 0x14;
const TUint KHwWoGpioGpsr_x		=	KHwBaseGpio + 0x18;
const TUint KHwWoGpioGpsr_y		=	KHwBaseGpio + 0x1c;
const TUint KHwWoGpioGpsr_z		=	KHwBaseGpio + 0x20;
const TUint KHwWoGpioGpcr_x		=	KHwBaseGpio + 0x24;
const TUint KHwWoGpioGpcr_y		=	KHwBaseGpio + 0x28;
const TUint KHwWoGpioGpcr_z		=	KHwBaseGpio + 0x2c;
const TUint KHwRwGpioGrer_x		=	KHwBaseGpio + 0x30;
const TUint KHwRwGpioGrer_y		=	KHwBaseGpio + 0x34;
const TUint KHwRwGpioGrer_z		=	KHwBaseGpio + 0x38;
const TUint KHwRwGpioGfer_x		=	KHwBaseGpio + 0x3c;
const TUint KHwRwGpioGfer_y		=	KHwBaseGpio + 0x40;
const TUint KHwRwGpioGfer_z		=	KHwBaseGpio + 0x44;
const TUint KHwRwGpioGedr_x		=	KHwBaseGpio + 0x48;
const TUint KHwRwGpioGedr_y		=	KHwBaseGpio + 0x4c;
const TUint KHwRwGpioGedr_z		=	KHwBaseGpio + 0x50;
const TUint KHwRwGpioGafr0_x	=	KHwBaseGpio + 0x54;
const TUint KHwRwGpioGafr1_x	=	KHwBaseGpio + 0x58;
const TUint KHwRwGpioGafr0_y	=	KHwBaseGpio + 0x5c;
const TUint KHwRwGpioGafr1_y	=	KHwBaseGpio + 0x60;
const TUint KHwRwGpioGafr0_z	=	KHwBaseGpio + 0x64;
const TUint KHwRwGpioGafr1_z	=	KHwBaseGpio + 0x68;

// Valid I/O mask
const TUint KHmGpioPort_xValid  =   0xffffffff;
const TUint KHmGpioPort_yValid  =   KHmGpioPort_xValid;
const TUint KHmGpioPort_zValid  =   0x0001ffff;
const TUint KHtGpioPort80		=	KBit16;
const TUint KHtGpioPort79		=	KBit15;
const TUint KHtGpioPort78		=	KBit14;
const TUint KHtGpioPort77		=	KBit13;
const TUint KHtGpioPort76		=	KBit12;
const TUint KHtGpioPort75		=	KBit11;
const TUint KHtGpioPort74		=	KBit10;
const TUint KHtGpioPort73		=	KBit9;
const TUint KHtGpioPort72		=	KBit8;
const TUint KHtGpioPort71		=	KBit7;
const TUint KHtGpioPort70		=	KBit6;
const TUint KHtGpioPort69		=	KBit5;
const TUint KHtGpioPort68		=	KBit4;
const TUint KHtGpioPort67		=	KBit3;
const TUint KHtGpioPort66		=	KBit2;
const TUint KHtGpioPort65		=	KBit1;
const TUint KHtGpioPort64		=	KBit0;
const TUint KHtGpioPort63		=	KBit31;
const TUint KHtGpioPort62		=	KBit30;
const TUint KHtGpioPort61		=	KBit29;
const TUint KHtGpioPort60		=	KBit28;
const TUint KHtGpioPort59		=	KBit27;
const TUint KHtGpioPort58		=	KBit26;
const TUint KHtGpioPort57		=	KBit25;
const TUint KHtGpioPort56		=	KBit24;
const TUint KHtGpioPort55		=	KBit23;
const TUint KHtGpioPort54		=	KBit22;
const TUint KHtGpioPort53		=	KBit21;
const TUint KHtGpioPort52		=	KBit20;
const TUint KHtGpioPort51		=	KBit19;
const TUint KHtGpioPort50		=	KBit18;
const TUint KHtGpioPort49		=	KBit17;
const TUint KHtGpioPort48		=	KBit16;
const TUint KHtGpioPort47		=	KBit15;
const TUint KHtGpioPort46		=	KBit14;
const TUint KHtGpioPort45		=	KBit13;
const TUint KHtGpioPort44		=	KBit12;
const TUint KHtGpioPort43		=	KBit11;
const TUint KHtGpioPort42		=	KBit10;
const TUint KHtGpioPort41		=	KBit9;
const TUint KHtGpioPort40		=	KBit8;
const TUint KHtGpioPort39		=	KBit7;
const TUint KHtGpioPort38		=	KBit6;
const TUint KHtGpioPort37		=	KBit5;
const TUint KHtGpioPort36		=	KBit4;
const TUint KHtGpioPort35		=	KBit3;
const TUint KHtGpioPort34		=	KBit2;
const TUint KHtGpioPort33		=	KBit1;
const TUint KHtGpioPort32		=	KBit0;
const TUint KHtGpioPort31		=	KBit31;
const TUint KHtGpioPort30		=	KBit30;
const TUint KHtGpioPort29		=	KBit29;
const TUint KHtGpioPort28		=	KBit28;
const TUint KHtGpioPort27		=	KBit27;
const TUint KHtGpioPort26		=	KBit26;
const TUint KHtGpioPort25		=	KBit25;
const TUint KHtGpioPort24		=	KBit24;
const TUint KHtGpioPort23		=	KBit23;
const TUint KHtGpioPort22		=	KBit22;
const TUint KHtGpioPort21		=	KBit21;
const TUint KHtGpioPort20		=	KBit20;
const TUint KHtGpioPort19		=	KBit19;
const TUint KHtGpioPort18		=	KBit18;
const TUint KHtGpioPort17		=	KBit17;
const TUint KHtGpioPort16		=	KBit16;
const TUint KHtGpioPort15		=	KBit15;
const TUint KHtGpioPort14		=	KBit14;
const TUint KHtGpioPort13		=	KBit13;
const TUint KHtGpioPort12		=	KBit12;
const TUint KHtGpioPort11		=	KBit11;
const TUint KHtGpioPort10		=	KBit10;
const TUint KHtGpioPort9		=	KBit9;
const TUint KHtGpioPort8		=	KBit8;
const TUint KHtGpioPort7		=	KBit7;
const TUint KHtGpioPort6		=	KBit6;
const TUint KHtGpioPort5		=	KBit5;
const TUint KHtGpioPort4		=	KBit4;
const TUint KHtGpioPort3		=	KBit3;
const TUint KHtGpioPort2		=	KBit2;
const TUint KHtGpioPort1		=	KBit1;
const TUint KHtGpioPort0		=	KBit0;

// Cotulla Alternate GPIO pin functions - Cotulla EAS table 4-12
const TUint KHtGpioAltActLowGpReset_i =   KHtGpioPort1;
const TUint KHtGpioAltAdc0_i          =   KHtGpioPort2;
const TUint KHtGpioAltAdc1_i          =   KHtGpioPort3;
const TUint KHtGpioAltAdc2_i          =   KHtGpioPort4;
const TUint KHtGpioAltAdc3_i          =   KHtGpioPort5;
const TUint KHtGpioAltMmcClk_a_o      =   KHtGpioPort6;
const TUint KHtGpioAlt48MhzClk_o      =   KHtGpioPort7;
const TUint KHtGpioAltMmcCs0_a_o      =   KHtGpioPort8;
const TUint KHtGpioAltMmcCs1_a_o      =   KHtGpioPort9;
const TUint KHtGpioAltRtc1Hz_a_o      =   KHtGpioPort10;
const TUint KHtGpioAltFastOsc_a_o     =   KHtGpioPort11; //3.6mhz osc out
const TUint KHtGpioAltSlowOsc_a_o     =   KHtGpioPort12; //32khz osc out
const TUint KHtGpioAltMbgnt_a_o       =   KHtGpioPort13; // mem cnt
const TUint KHtGpioAltMbreq_i         =   KHtGpioPort14; 
const TUint KHtGpioAltActLowCs1_o     =   KHtGpioPort15; 
const TUint KHtGpioAltPwm0_o          =   KHtGpioPort16; 
const TUint KHtGpioAltPwm1_o          =   KHtGpioPort17;
const TUint KHtGpioAltRdy_i           =   KHtGpioPort18; // ext bus rdy
const TUint KHtGpioAltDreq1_i         =   KHtGpioPort19; // Fly by req
const TUint KHtGpioAltDreq0_i         =   KHtGpioPort20;
const TUint KHtGpioAltDval0_o         =   KHtGpioPort21; //Fly By data valid
const TUint KHtGpioAltDval1_o         =   KHtGpioPort22; 
const TUint KHtGpioAltSclk_o          =   KHtGpioPort23; //SSP
const TUint KHtGpioAltSfrm_o          =   KHtGpioPort24; //SSP
const TUint KHtGpioAltTxd_o           =   KHtGpioPort25; //SSP
const TUint KHtGpioAltRxd_i           =   KHtGpioPort26; //SSP
const TUint KHtGpioAltExtClk_i        =   KHtGpioPort27; //SSP
const TUint KHtGpioAltAc97BitClk_i    =   KHtGpioPort28;
const TUint KHtGpioAltI2SBitClk_i     =   KHtGpioPort28;
const TUint KHtGpioAltI2SBitClk_o     =   KHtGpioPort28;
const TUint KHtGpioAltAc97BitClk_o    =   KHtGpioPort28;
const TUint KHtGpioAltAc97Sdata0_i    =   KHtGpioPort29;
const TUint KHtGpioAltI2SSdata_i      =   KHtGpioPort29;
const TUint KHtGpioAltI2SSdata0_o     =   KHtGpioPort30;
const TUint KHtGpioAltAc97Sdata0_o    =   KHtGpioPort30;
const TUint KHtGpioAltI2SSync_o       =   KHtGpioPort31;
const TUint KHtGpioAltAc97Sync_o      =   KHtGpioPort31;
const TUint KHtGpioAltI2SSysClk_o     =   KHtGpioPort32;
const TUint KHtGpioAltAc97Sdata1_i    =   KHtGpioPort32;
const TUint KHtGpioAltActLowCs5_o     =   KHtGpioPort33;
const TUint KHtGpioAltFFUartRxd_i     =   KHtGpioPort34;
const TUint KHtGpioAltAdc4_i          =   KHtGpioPort34;
const TUint KHtGpioAltMmcCs0_b_o      =   KHtGpioPort34;
const TUint KHtGpioAltFFUartCts_i     =   KHtGpioPort35;
const TUint KHtGpioAltFFUartDcd_i     =   KHtGpioPort36;
const TUint KHtGpioAltFFUartDsr_i     =   KHtGpioPort37;
const TUint KHtGpioAltFFUartRi_i      =   KHtGpioPort38;
const TUint KHtGpioAltAdc5_i          =   KHtGpioPort39;
const TUint KHtGpioAltMmcCs1_b_i      =   KHtGpioPort39;
const TUint KHtGpioAltFFUartTxd_o     =   KHtGpioPort39;
const TUint KHtGpioAltFFUartDtr_o     =   KHtGpioPort40;
const TUint KHtGpioAltFFUartRts_o     =   KHtGpioPort41;
const TUint KHtGpioAltBTUartRxd_i     =   KHtGpioPort42;
const TUint KHtGpioAltAdc6_i          =   KHtGpioPort43;
const TUint KHtGpioAltBTUartTxd_o     =   KHtGpioPort43;
const TUint KHtGpioAltBTUartCts_i     =   KHtGpioPort44;
const TUint KHtGpioAltBTUartRts_o     =   KHtGpioPort45;
const TUint KHtGpioAltIcpRxd_i        =   KHtGpioPort46;
const TUint KHtGpioAltSTUartTxd_o     =   KHtGpioPort47;
const TUint KHtGpioAltPoe_o           =   KHtGpioPort48; // Card Space
const TUint KHtGpioAltPwe_o           =   KHtGpioPort49; // Card Space
const TUint KHtGpioAltPior_o          =   KHtGpioPort50; // Card Space
const TUint KHtGpioAltPiow_o          =   KHtGpioPort51; // Card Space
const TUint KHtGpioAltPce1_o          =   KHtGpioPort52; // Card Space
const TUint KHtGpioAltPce2_o          =   KHtGpioPort53; // Card Space
const TUint KHtGpioAltMmcClk_b_o      =   KHtGpioPort53; 
const TUint KHtGpioAltMmcClk_c_o      =   KHtGpioPort54;
const TUint KHtGpioAltSktSel_o        =   KHtGpioPort54;
const TUint KHtGpioAltPreg_o          =   KHtGpioPort55; // Card Space
const TUint KHtGpioAltPwait_o         =   KHtGpioPort56;
const TUint KHtGpioAltIOIS16_o        =   KHtGpioPort57; // I/O Card Space Width

const TUint KHmGpioAltLdd_0_5_o	      =(KHtGpioPort58 | KHtGpioPort59 |  
										KHtGpioPort60 | KHtGpioPort61 | 
										KHtGpioPort62 | KHtGpioPort63);

const TUint KHmGpioAltLdd_6_16_o      =(KHtGpioPort64 | KHtGpioPort65 |
										KHtGpioPort66 | KHtGpioPort67 |
										KHtGpioPort68 | KHtGpioPort69 |
										KHtGpioPort70 | KHtGpioPort71 |
										KHtGpioPort72 | KHtGpioPort73);

const TUint KHmGpioZClksAcBias_o     =(KHtGpioPort74 | KHtGpioPort75 |
									   KHtGpioPort76 | KHtGpioPort77);

const TUint KHmGpioAltLddFclk_o       =   KHtGpioPort74;
const TUint KHmGpioAltLddLclk_o       =   KHtGpioPort75;
const TUint KHmGpioAltLddPclk_o       =   KHtGpioPort76;
const TUint KHmGpioAltLddAcBias_o     =   KHtGpioPort77;
const TUint KHmGpioAltActLowCs2_o     =   KHtGpioPort78;
const TUint KHmGpioAltActLowCs3_o     =   KHtGpioPort79;
const TUint KHmGpioAltActLowCs4_o     =   KHtGpioPort80;

const TUint KHmGpioReservedBits_z     =  	0xFFFE0000;

/**
 * Interrupt Controller
 */
const TUint KHwRoIntsIcip		=	KHwBaseInts + 0x00;
const TUint KHwRwIntsIcmr		=	KHwBaseInts + 0x04;
const TUint KHwRwIntsIclr		=	KHwBaseInts + 0x08;
const TUint KHwRoIntsIcfp		=	KHwBaseInts + 0x0c;
const TUint KHwRoIntsIcpr		=	KHwBaseInts + 0x10;
const TUint KHwRwIntsIccr		=	KHwBaseInts + 0x14;

const TUint KHtIntsIccrDim		=	KBit0;

// Interrupt sources
const TUint KHtIntsSrcRtcAlarm		=	KBit31;
const TUint KHtIntsSrcRtcTick		=	KBit30;
const TUint KHtIntsSrcOstMatch3		=	KBit29;
const TUint KHtIntsSrcOstMatch2		=	KBit28;
const TUint KHtIntsSrcOstMatch1		=	KBit27;
const TUint KHtIntsSrcOstMatch0		=	KBit26;
const TUint KHtIntsSrcDma			=	KBit25;
const TUint KHtIntsSrcSsp			=	KBit24;
const TUint KHtIntsSrcMmc			=	KBit23;
const TUint KHtIntsSrcFfuart		=	KBit22;
const TUint KHtIntsSrcBtuart		=	KBit21;
const TUint KHtIntsSrcStuart		=	KBit20;
const TUint KHtIntsSrcIcp			=	KBit19;
const TUint KHtIntsSrcI2c			=	KBit18;
const TUint KHtIntsSrcLcd			=	KBit17;
const TUint KHtIntsSrcAc97			=	KBit14;
const TUint KHtIntsSrcI2s			=	KBit13;
const TUint KHtIntsSrcPmu			=	KBit12;
const TUint KHtIntsSrcUsb			=	KBit11;
const TUint KHtIntsSrcGpioEdge2_80	=	KBit10;
const TUint KHtIntsSrcGpioEdge1		=	KBit9;
const TUint KHtIntsSrcGpioEdge0		=	KBit8;

/**
 * Memory Controller
 */

const TUint KHwRwMemMdcnfg		=	KHwBaseMexp + 0x00;
const TUint KHwRwMemMdrefr		=	KHwBaseMexp + 0x04;
const TUint KHwRwMemMsc0		=	KHwBaseMexp + 0x08;
const TUint KHwRwMemMsc1		=	KHwBaseMexp + 0x0C;
const TUint KHwRwMemMsc2		=	KHwBaseMexp + 0x10;
const TUint KHwRwMemMecr		=	KHwBaseMexp + 0x14;
const TUint KHwRwMemSxlcr		=	KHwBaseMexp + 0x18;
const TUint KHwRwMemSxcnfg		=	KHwBaseMexp + 0x1C;
const TUint KHwRwMemFlycnfg		=	KHwBaseMexp + 0x20;
const TUint KHwRwMemSxmrs		=	KHwBaseMexp + 0x24;
const TUint KHwRwMemMcmem0		=	KHwBaseMexp + 0x28;
const TUint KHwRwMemMcmem1		=	KHwBaseMexp + 0x2C;
const TUint KHwRwMemMcatt0		=	KHwBaseMexp + 0x30;
const TUint KHwRwMemMcatt1		=	KHwBaseMexp + 0x34;
const TUint KHwRwMemMcio0		=	KHwBaseMexp + 0x38;
const TUint KHwRwMemMcio1		=	KHwBaseMexp + 0x3C;
const TUint KHwRwMemMdmrs		=	KHwBaseMexp + 0x40;
const TUint KHwRoMemBootdef		=	KHwBaseMexp + 0x44;


// DRAM configuration
const TUint KHmMemMdcnfgDe0_1		=	(KBit0 | KBit1);
const TUint KHtMemMdcnfgDwid_0		=	KBit2;
const TUint KHsMemMdcnfgDcac_0		=	3;
const TUint KHmMemMdcnfgDcac_0		=	3<<KHsMemMdcnfgDcac_0;
const TUint KHsMemMdcnfgDrac_0		=	5;
const TUint KHmMemMdcnfgDrac_0		=	3<<KHsMemMdcnfgDrac_0;
const TUint KHtMemMdcnfgDnb_0		=	KBit7;
const TUint KHsMemMdcnfgDtc_0       =   8;
const TUint KHmMemMdcnfgDtc_0       =   3<<KHsMemMdcnfgDtc_0;
const TUint KHtMemMdcnfgDaddr_0		=	KBit10;
const TUint KHtMemMdcnfgDlatch_0	=	KBit11;
const TUint KHtMemMdcnfgDsa1111_0	=	KBit12;
const TUint KHtMemMdcnfgDe2		    =	KBit16;
const TUint KHtMemMdcnfgDe3		    =	KBit17;
const TUint KHtMemMdcnfgDwid_2		=	KBit18;
const TUint KHsMemMdcnfgDcac_2		=	19;
const TUint KHmMemMdcnfgDcac_2		=	3<<KHsMemMdcnfgDcac_2;
const TUint KHsMemMdcnfgDrac_2		=	21;
const TUint KHmMemMdcnfgDrac_2		=	3<<KHsMemMdcnfgDrac_2;
const TUint KHtMemMdcnfgDnb_2		=	KBit23;
const TUint KHsMemMdcnfgDtc_2		=	24;
const TUint KHmMemMdcnfgDtc_2		=	3<<KHsMemMdcnfgDtc_2;
const TUint KHtMemMdcnfgDaddr_2		=	KBit26;
const TUint KHtMemMdcnfgDlatch_1	=	KBit27;
const TUint KHtMemMdcnfgDsa1111_2	=	KBit28;

// SDRAM Mode Register Set
const TUint KHsMemMdmrsMdbl_0	=	0;  
const TUint KHmMemMdmrsMdbl_0	=	7<<KHsMemMdmrsMdbl_0;
const TUint KHsMemMdmrsMdadd_0  =   KBit3;
const TUint KHsMemMdmrsMdcl_0	=	4;  
const TUint KHmMemMdmrsMdcl_0	=	7<<KHsMemMdmrsMdcl_0;
const TUint KHsMemMdmrsMdmrs_0  =   7;
const TUint KHmMemMdmrsMdmrs_0  =   0xff<<KHsMemMdmrsMdmrs_0; 

const TUint KHsMemMdmrsMdbl_2	=	16;  
const TUint KHmMemMdmrsMdbl_2	=	7<<KHsMemMdmrsMdbl_2;
const TUint KHsMemMdmrsMdadd_2  =   KBit19;
const TUint KHsMemMdmrsMdcl_2	=	20;  
const TUint KHmMemMdmrsMdcl_2	=	7<<KHsMemMdmrsMdcl_2;
const TUint KHsMemMdmrsMdmrs_2  =   23;
const TUint KHmMemMdmrsMdmrs_2  =   0xff<<KHsMemMdmrsMdmrs_2; 

// Static memory control (2 per register) done
const TUint KHtMemMscRbuff      =   KBit15;
const TUint KHsMemMscRrr		=	12;
const TUint KHmMemMscRrr		=	0x7<<KHsMemMscRrr;
const TUint KHsMemMscRdn		=	8;
const TUint KHmMemMscRdn		=	0xf<<KHsMemMscRdn;
const TUint KHsMemMscRdf		=	4;
const TUint KHmMemMscRdf		=	0xf<<KHsMemMscRdf;
const TUint KHtMemMscRbw		=	KBit3;
const TUint KHsMemMscRt			=	0;
const TUint KHmMemMscRt			=	0x7<<KHsMemMscRt;

// Expansion memory configuration 
const TUint KHtMemMecrNos		=	KBit0;	
const TUint KHtMemMecrCit		=   KBit1;

// Memory Controller IO
const TUint KHsMemMcxxHold	=   14;
const TUint KHmMemMcxxHold  =   (0x3f<<KHsMemMcxxHold);
const TUint KHsMemMcxxAsst  =   7;
const TUint KHmMemMcxxAsst  =   (0x1f<<KHsMemMcxxAsst);
const TUint KHmMemMcxxReservedBits = 0xfff03000;
const TUint KHsMemMcxxSet	=   0;
const TUint HKmMemMcxxSet   =   (0x7f<<KHsMemMcxxSet);

// Number of static chip selects
const TUint KHwMemMscMaxCS		=	6;

// DRAM Refresh Control Register 
const TUint KHsMemMdrefrDri		=	0;
const TUint KHmMemMdrefrDri		=	0xfff<<KHsMemMdrefrDri;
const TUint KHtMemMdrefrE0pin		=	KBit12;
const TUint KHtMemMdrefrK0run		=	KBit13;
const TUint KHtMemMdrefrK0db2		=	KBit14;
const TUint KHtMemMdrefrE1pin		=	KBit15;
const TUint KHtMemMdrefrK1run		=	KBit16;
const TUint KHtMemMdrefrK1db2		=	KBit17;
const TUint KHtMemMdrefrK2run		=	KBit18;
const TUint KHtMemMdrefrK2db2		=	KBit19;
const TUint KHtMemMdrefrApd			=	KBit20;
const TUint KHtMemMdrefrSlfrsh		=	KBit22;
const TUint KHtMemMdrefrK0fref		=	KBit23;
const TUint KHtMemMdrefrK1fref		=	KBit24;
const TUint KHtMemMdrefrK2fref		=	KBit25;

/** 
 *  Clocks Manager Registers
 */
const TUint KHwRwClocksCccr		=	KHwBaseClocks + 0x00;
const TUint KHwRwClocksCken		=	KHwBaseClocks + 0x04;
const TUint KHwRwClocksOscc		=	KHwBaseClocks + 0x08;

// Core Clock Configuration Register
const TUint KHsClocksCccrL		=	0;
const TUint KHmClocksCccrL		=	0x1f<<KHsClocksCccrL;
const TUint KHsClocksCccrM		=	5;
const TUint KHmClocksCccrM		=	3<<KHsClocksCccrM;
const TUint KHsClocksCccrN		=	7;
const TUint KHmClocksCccrN		=	7<<KHsClocksCccrN;

// Clock Enable Register (bits 17+ should be written as zeroes)
const TUint KHtClocksCken0		=	KBit0;
const TUint KHtClocksCken1		=	KBit1;
const TUint KHtClocksCken2		=	KBit2;
const TUint KHtClocksCken3		=	KBit3;
const TUint KHtClocksCken4		=	KBit4;
const TUint KHtClocksCken5		=	KBit5;
const TUint KHtClocksCken6		=	KBit6;
const TUint KHtClocksCken7		=	KBit7;
const TUint KHtClocksCken8		=	KBit8;
const TUint KHtClocksCken9		=	KBit9;
const TUint KHtClocksCken10		=	KBit10;
const TUint KHtClocksCken11		=	KBit11;
const TUint KHtClocksCken12		=	KBit12;
const TUint KHtClocksCken13		=	KBit13;
const TUint KHtClocksCken14		=	KBit14;
const TUint KHtClocksCken15		=	KBit15;
const TUint KHtClocksCken16		=	KBit16;

// Oscillator Configuration Register 
const TUint KHtClocksOsccOok		=	KBit0;  
const TUint KHtClocksOsccOon		=	KBit1;

//CP14 PWRMODE reg fields
const TUint KHtCP14PwrmodeTurbo		=    KBit0;
const TUint KHtCP14PwrmodeFcs		=    KBit1;

//Return val indicating error in CClkCfg setting for L,M, or N
const TUint KErrCClkCfg				= 0;
/*  
 *  SSP's
 */
const TUint KHwRwSspSscr0     =   KHwBaseSsp+0x00;
const TUint KHwRwSspSscr1     =   KHwBaseSsp+0x04;
const TUint KHwRwSspSssr	  =   KHwBaseSsp+0x08;
const TUint KHwRwSspSsitr     =   KHwBaseSsp+0x0c;
const TUint KHwRwSspSsdr      =   KHwBaseSsp+0x10;

// SSCR0
const TUint KHsSspSscr0Scr		=	8;
const TUint KHmSspSscr0Scr		=	0x000000ff<<KHsSspSscr0Scr;
const TUint KHtSspSscr0Sse		=	KBit7;
const TUint KHtSspSscr0Ecs		=	KBit6;
const TUint KHsSspSscr0Frf		=	4;
const TUint KHmSspSscr0Frf		=	0x00000003<<KHsSspSscr0Frf;
const TUint KHsSspSscr0Dss		=	0;
const TUint KHmSspSscr0Dss		=	0x0000000f<<KHsSspSscr0Dss;

// SSCR1
const TUint KHsSspSscr1Strf		=	KBit15;
const TUint KHsSspSscr1Efwr		=	KBit14;
const TUint KHsSspSscr1Rft		=	10;
const TUint KHmSspSscr1Rft		=	0x0000000f<<KHsSspSscr1Rft;
const TUint KHsSspSscr1Tft		=	6;
const TUint KHmSspSscr1Tft		=	0x0000000f<<KHsSspSscr1Tft;
const TUint KHtSspSscr1Mwds		=	KBit5;
const TUint KHtSspSscr1Sph		=	KBit4;
const TUint KHtSspSscr1Spo		=	KBit3;
const TUint KHtSspSscr1Lbm		=	KBit2;
const TUint KHtSspSscr1Tie		=	KBit1;
const TUint KHtSspSscr1Rie		=	KBit0;

// SSSR
const TUint KHsSspSscr1Rfl		=	12;
const TUint KHmSspSscr1Rfl		=	0x0000000f<<KHsSspSscr1Rfl;
const TUint KHsSspSscr1Tfl		=	8;
const TUint KHmSspSscr1Tfl		=	0x0000000f<<KHsSspSscr1Tfl;
const TUint KHtSspSssrRor		=	KBit6;
const TUint KHtSspSssrRfs		=	KBit5;
const TUint KHtSspSssrTfs		=	KBit4;
const TUint KHtSspSssrBsy		=	KBit3;
const TUint KHtSspSssrRne		=	KBit2;
const TUint KHtSspSssrTnf		=	KBit1;

const TUint KHmSspSssrSticky	=	KHtSspSssrRor;

// SSITR (Test mode Only)
const TUint KHtSspSsitrTtfs		= KBit5; 
const TUint KHtSspSsitrTrfs		= KBit6;
const TUint KHtSspSsitrTror		= KBit7;

/**
 * UARTs
 */
// address of the all UART port registers BASE+offset
// BASE can be FFUART or STUART
const TUint KHoRwUartBuffer     =   0x00;
const TUint KHoRwUartIer        =   0x04;
const TUint KHoRoUartIir        =   0x08;
const TUint KHoWoUartFcr        =   0x08;
const TUint KHoRwUartLcr        =   0x0c;
const TUint KHoRwUartMcr        =   0x10;
const TUint KHoRoUartLsr        =   0x14;
const TUint KHoRoUartMsr        =   0x18;
const TUint KHoRwUartScr        =   0x1c;
const TUint KHoRwUartSir        =   0x20;

const TUint KHoRwUartDivLo      =   0x00;
const TUint KHoRwUartDivHi      =   0x04;

// Interrupt Enable Register (IER)
const TUint KHtUartIerDmae      =   KBit7;
const TUint KHtUartIerUue       =   KBit6;
const TUint KHtUartIerNrze      =   KBit5;
const TUint KHtUartIerRtoie     =   KBit4;
const TUint KHtUartIerMie       =   KBit3;
const TUint KHtUartIerRlse      =   KBit2;
const TUint KHtUartIerTie       =   KBit1;
const TUint KHtUartIerRavie     =   KBit0;

// FIFO Control Register (FCR)
const TUint KHtUartFcrITL		=   KBit7|KBit6;
const TUint KHtUartFcrResetTf   =   KBit2;
const TUint KHtUartFcrResetRf   =   KBit1;
const TUint KHtUartFcrFe        =   KBit0;

// Line Control Register (LCR)
const TUint KHtUartLcrDlab      =   KBit7;
const TUint KHtUartLcrSb        =   KBit6;
const TUint KHtUartLcrStkyp     =   KBit5;
const TUint KHtUartLcrEps       =   KBit4;
const TUint KHtUartLcrPen       =   KBit3;
const TUint KHtUartLcrStb       =   KBit2;
const TUint KHtUartLcrWls       =   KBit1|KBit0;
const TUint KHmUartDataFormat	=	KHtUartLcrEps|KHtUartLcrPen|KHtUartLcrStb|KHtUartLcrWls;

// Line Status Register (LSR)
const TUint KHtUartLsrFifoe     =   KBit7;
const TUint KHtUartLsrTemt      =   KBit6;
const TUint KHtUartLsrTdrq      =   KBit5;
const TUint KHtUartLsrBi        =   KBit4;
const TUint KHtUartLsrFe        =   KBit3;
const TUint KHtUartLsrPe        =   KBit2;
const TUint KHtUartLsrOe        =   KBit1;
const TUint KHtUartLsrDr        =   KBit0;

// Interrupt Identification Register (IIR)
const TUint KHtUartIirFifoes    =   KBit7|KBit6;
const TUint KHtUartIirTod       =   KBit3;
const TUint KHmUartIirRls       =   KBit2|KBit1;
const TUint KHtUartIirTfs		=	KBit1;
const TUint KHtUartIirRfs		=	KBit2;
const TUint KHmUartIirMs		=	KBit2|KBit1;
const TUint KHtUartIirIp        =   KBit0;

// Modem Control Register (MCR)
const TUint KHtUartMcrLoop      =   KBit4;
const TUint KHtUartMcrOut2      =   KBit3;
const TUint KHtUartMcrOut1      =   KBit2;
const TUint KHtUartMcrRts       =   KBit1;
const TUint KHtUartMcrDtr       =   KBit0;

// Modem Status Register (MSR)
const TUint KHtUartMsrDcd       =   KBit7;
const TUint KHtUartMsrRi        =   KBit6;
const TUint KHtUartMsrDsr       =   KBit5;
const TUint KHtUartMsrCts       =   KBit4;
const TUint KHtUartMsrDdcd      =   KBit3;
const TUint KHtUartMsrTeri      =   KBit2;
const TUint KHtUartMsrDdsr      =   KBit1;
const TUint KHtUartMsrDcts      =   KBit0;

// Slow Infrared Selection Register (ISR)
const TUint KHtUartIsrRxpl      =   KBit4;
const TUint KHtUartIsrTxpl      =   KBit3;
const TUint KHtUartIsrXmode     =   KBit2;
const TUint KHtUartIsrRcveir    =   KBit1;
const TUint KHtUartIsrXmitir    =   KBit0;
  
// address of the all ICP(FIR) port registers BASE+offset
const TUint KHoRwIcpCr0         =   KHwBaseIcp+0x00;
const TUint KHoRwIcpCr1         =   KHwBaseIcp+0x04;
const TUint KHoRwIcpCr2         =   KHwBaseIcp+0x08;
const TUint KHoRwIcpDr          =   KHwBaseIcp+0x0c;
const TUint KHoRwIcpSr0         =   KHwBaseIcp+0x14;
const TUint KHoRwIcpSr1         =   KHwBaseIcp+0x18;

// ICP Control Rgister 0
const TUint KHtIcpCr0Amr        =   KBit7;
const TUint KHtIcpCr0Tie        =   KBit6; 
const TUint KHtIcpCr0Rie        =   KBit5; 
const TUint KHtIcpCr0Rxe        =   KBit4; 
const TUint KHtIcpCr0Txe        =   KBit3;
const TUint KHtIcpCr0Tus        =   KBit2;
const TUint KHtIcpCr0Lbm        =   KBit1;
const TUint KHtIcpCr0Itr        =   KBit0; 

// ICP Control Register 1

// ICP Control Register 2
const TUint KHtIcpCr2Rxp        =   KBit3;
const TUint KHtIcpCr2Txp        =   KBit2;
const TUint KHtIcpCr2Trig       =   KBit1|KBit0;       

// ICP Status Register 0
const TUint KHtIcpSr0Fre        =   KBit5;
const TUint KHtIcpSr0Rfs        =   KBit4; 
const TUint KHtIcpSr0Tfs        =   KBit3; 
const TUint KHtIcpSr0Rab        =   KBit2; 
const TUint KHtIcpSr0Tur        =   KBit1;
const TUint KHtIcpSr0Eif        =   KBit0;

// ICP Status Register 1
const TUint KHtIcpSr1Ror        =   KBit6;
const TUint KHtIcpSr1Cre        =   KBit5; 
const TUint KHtIcpSr1Eof        =   KBit4; 
const TUint KHtIcpSr1Tnf        =   KBit3; 
const TUint KHtIcpSr1Rne        =   KBit2;
const TUint KHtIcpSr1Tby        =   KBit1;
const TUint KHtIcpSr1Rsy        =   KBit0;

// Generator for baud rate divisor
#define _UART_BRD(rate)	(14745600 / (16 * (rate)))

/**
 * LCD Controller
 */
// DMA granularity (bytes)
const TUint KHwLcdPixelDmaGranularity   =   16;

// Palette structure
const TUint KHsLcdPaletteMono   = 0;
const TUint KHmLcdPaletteMono   = 0x000f<<KHsLcdPaletteMono;
const TUint KHsLcdPaletteBlue   = 0;
const TUint KHmLcdPaletteBlue   = 0x000f<<KHsLcdPaletteBlue;
const TUint KHsLcdPaletteGreen  = 4;
const TUint KHmLcdPaletteGreen  = 0x000f<<KHsLcdPaletteGreen;
const TUint KHsLcdPaletteRed    = 8;
const TUint KHmLcdPaletteRed    = 0x000f<<KHsLcdPaletteRed;
const TUint KHsLcdPalettePbs    = 12;
const TUint KHmLcdPalettePbs    = 0x0003<<KHsLcdPalettePbs;

const TInt KHsMaxBytesPerPixel  = 1; //Maximum bpp is 16

// Palette entry spacing (bits)
const TUint KHsLcdPaletteSpacing    = 16;

// Palette masks
const TUint KHmLcdPalette4Bit       = 0x000f;
const TUint KHmLcdPalette8Bit       = 0x0fff;

// Palette entries
const TUint KHwLcdPaletteEntries4Bit    = 16;
const TUint KHwLcdPaletteEntries8Bit    = 256;

// Palette size given bits per pixel (bytes)
const TUint KHwLcdPaletteBytes4Bit  = 32;
const TUint KHwLcdPaletteBytes8Bit  = 512;

// Palette Entries; see wd_cot.cpp for more details
const TUint KPaletteEntBlack		= 0x0000;	
const TUint KPaletteEntMidBlue		= 0x0014;	
const TUint KPaletteEntMidGreen		= 0x0500;	
const TUint KPaletteEntMidCyan		= 0x0514;	
const TUint KPaletteEntMidRed		= 0xA000;
const TUint KPaletteEntMidMagenta	= 0xA014;
const TUint KPaletteEntMidYellow	= 0xA280;
const TUint KPaletteEntDimWhite		= 0xA514;
const TUint KPaletteEntGray			= 0x528A;
const TUint KPaletteEntBlue			= 0x515F;
const TUint KPaletteEntGreen		= 0x57EA;
const TUint KPaletteEntCyan			= 0x57FF;
const TUint KPaletteEntRed			= 0xFA8A;
const TUint KPaletteEntMagenta		= 0xFA9F;
const TUint KPaletteEntYellow		= 0xFFEA;
const TUint KPaletteEntWhite		= 0xFFFF;

const TUint KHsLcdPaletteUpperHalf	= 16;

const TUint16 KPalette256_12bit[256] = {
	0x1000, 0x1300, 0x0600, 0x0900, 0x0C00, 0x0F00, 
	0x0030, 0x0330,	0x0630, 0x0930, 0x0C30, 0x0F30,
	0x0060, 0x0360, 0x0660, 0x0960,	0x0C60, 0x0F60,
	0x0090, 0x0390, 0x0690, 0x0990, 0x0C90, 0x0F90,
	0x00C0, 0x03C0, 0x06C0, 0x09C0, 0x0CC0, 0x0FC0,
	0x00F0, 0x03F0, 0x06F0, 0x09F0, 0x0CF0, 0x0FF0,
	0x0003, 0x0303, 0x0603, 0x0903, 0x0C03, 0x0F03, 
	0x0033, 0x0333, 0x0633, 0x0933, 0x0C33, 0x0F33,
	0x0063, 0x0363, 0x0663, 0x0963, 0x0C63, 0x0F63,
	0x0093, 0x0393, 0x0693, 0x0992, 0x0C93, 0x0F93,
	0x00C3, 0x03C3, 0x06C3, 0x09C3, 0x0CC3, 0x0FC3,
	0x00F3, 0x03F3, 0x06F3, 0x09F3, 0x0CF3, 0x0FF3,
	0x0006, 0x0306, 0x0606, 0x0906, 0x0C06, 0x0F06, 
	0x0036, 0x0336, 0x0636, 0x0936, 0x0C36, 0x0F36,
	0x0066, 0x0366, 0x0666, 0x0966, 0x0C66, 0x0F66,
	0x0096, 0x0396, 0x0696, 0x0996, 0x0C96, 0x0F96,
	0x00C6, 0x03C6, 0x06C6, 0x09C6, 0x0CC6, 0x0FC6,
	0x00F6, 0x03F6, 0x06F6, 0x09F6, 0x0CF6, 0x0FF6,
	0x0111, 0x0222, 0x0444, 0x0555, 0x0777,
	0x0100, 0x0200, 0x0400, 0x0500, 0x0700,
	0x0010, 0x0020,	0x0040, 0x0050, 0x0070,
	0x0001, 0x0002, 0x0004, 0x0005, 0x0007,
	0x0008, 0x000A, 0x000B, 0x000D, 0x000E, 
	0x0080, 0x00A0, 0x00B0, 0x00D0, 0x00E0,
	0x0800, 0x0A00, 0x0B00, 0x0D00, 0x0E00, 
	0x0888,	0x0AAA, 0x0BBB, 0x0DDD, 0x0EEE,
	0x0009, 0x0309, 0x0609, 0x0909, 0x0C09, 0x0F09, 
	0x0039, 0x0339,	0x0639, 0x0939, 0x0C39, 0x0F39,
	0x0069, 0x0369,	0x0669, 0x0969, 0x0C69, 0x0F69,
	0x0099, 0x0399, 0x0699, 0x0999, 0x0C99, 0x0F99,
	0x00C9, 0x03C9,	0x06C9, 0x09C9, 0x0CC9, 0x0FC9, 
	0x00F9, 0x03F9, 0x06F9, 0x09F9, 0x0CF9, 0x0FF9,
	0x000C, 0x030C,	0x060C, 0x090C, 0x0C0C, 0x0F0C,
	0x003C, 0x033C, 0x063C, 0x093C, 0x0C3C, 0x0F3C,
	0x006C, 0x036C,	0x066C, 0x096C, 0x0C6C, 0x0F6C,
	0x009C, 0x039C, 0x069C, 0x099C, 0x0C9C, 0x0F9C, 
	0x00CC, 0x03CC,	0x06CC, 0x09CC, 0x0CCC, 0x0FCC,
	0x00FC, 0x03FC, 0x06FC, 0x09FC, 0x0CFC, 0x0FFC,
	0x000F, 0x030F,	0x060F, 0x090F, 0x0C0F, 0x0F0F,
	0x003F, 0x033F, 0x063F, 0x093F, 0x0C3F, 0x0F3F,
	0x006F, 0x036F,	0x066F, 0x096F, 0x0C6F, 0x0F6F,
	0x009F, 0x039F, 0x069F, 0x099F, 0x0C9F, 0x0F9F, 
	0x00CF, 0x03CF,	0x06CF, 0x09CF, 0x0CCF, 0x0FCF, 
	0x00FF, 0x03FF, 0x06FF, 0x09FF, 0x0CFF, 0x0FFF
	};

const TUint KHwLcdFrameDescriptorBytes  = 16; //4 words

const TUint KHwLcdExtraBytes    = KHwLcdPaletteBytes8Bit+KHwLcdPixelDmaGranularity;

// Pixel structure
const TUint KHsLcdPixelSpacing4Bit  =   4;
const TUint KHsLcdPixelSpacing8Bit  =   8;

// Maximum number of lcd panels for the display
const TUint KHwLcdMaxPanels         =   2;

// Masks to set up the Port Alternatives for the LCD LDD signals, the neccessary clocks, and the AC bias
const TUint KHmClearPortAltLDD0thru5			= 0xFFF00000;
const TUint KHmSetPortAltLDD0thru5				= 0xAAA00000;
const TUint KHmClearPortAltLDD6thru15PlusClks	= 0x0FFFFFFF;
const TUint KHmSetPortAltLDD6thru15PlusClks		= 0x0AAAAAAA;

// LCD register set
const TUint KHwRwLcdLccr0       =   KHwBaseLcd + 0x000;
const TUint KHwRwLcdLccr1       =   KHwBaseLcd + 0x004;
const TUint KHwRwLcdLccr2       =   KHwBaseLcd + 0x008;
const TUint KHwRwLcdLccr3       =   KHwBaseLcd + 0x00c;

const TUint KHwRwLcdFbr0	=   KHwBaseLcd + 0x020;		// DMA channel 0 Frame Branch Register
const TUint KHwRwLcdFbr1 	=   KHwBaseLcd + 0x024;		// DMA channel 1 Frame Branch Register

const TUint KHwRwLcdLcsr	=   KHwBaseLcd + 0x038;
const TUint KHwRwLcdLiidr	=   KHwBaseLcd + 0x03c;
const TUint KHwRwLcdTrgbr	=   KHwBaseLcd + 0x040;
const TUint KHwRwLcdTcr		=   KHwBaseLcd + 0x044;

const TUint KHwRwLcdFdadr0 	=   KHwBaseLcd + 0x200;		// DMA channel 0
const TUint KHwRwLcdFsadr0	=   KHwBaseLcd + 0x204;
const TUint KHwRwLcdFidr0	=   KHwBaseLcd + 0x208;
const TUint KHwRwLcdLdcmd0	=   KHwBaseLcd + 0x20c;

const TUint KHwRwLcdFdadr1 	=   KHwBaseLcd + 0x210;		// DMA channel 1
const TUint KHwRwLcdFsadr1	=   KHwBaseLcd + 0x214;
const TUint KHwRwLcdFidr1	=   KHwBaseLcd + 0x218;
const TUint KHwRwLcdLdcmd1	=   KHwBaseLcd + 0x21c;



// LCCR0
const TUint KHtLcdLccr0Oum      =   KBit21;
const TUint KHtLcdLccr0Bm       =   KBit20;
const TUint KHsLcdLccr0Pdd      =   12;
const TUint KHmLcdLccr0Pdd      =   0x000000ff<<KHsLcdLccr0Pdd;
const TUint KHtLcdLccr0Qdm      =   KBit11;
const TUint KHtLcdLccr0Dis      =   KBit10;
const TUint KHtLcdLccr0Dpd      =   KBit9;
const TUint KHtLcdLccr0Ble      =   KBit8;
const TUint KHtLcdLccr0Pas      =   KBit7;
const TUint KHtLcdLccr0Efm      =   KBit6;
const TUint KHtLcdLccr0Ium      =   KBit5;
const TUint KHtLcdLccr0Sfm      =   KBit4;
const TUint KHtLcdLccr0Ldm      =   KBit3;
const TUint KHtLcdLccr0Sds      =   KBit2;
const TUint KHtLcdLccr0Cms      =   KBit1;
const TUint KHtLcdLccr0Enb      =   KBit0;

// LCCR1
const TUint KHsLcdLccr1Blw      =   24;
const TUint KHmLcdLccr1Blw      =   0x000000ff<<KHsLcdLccr1Blw;
const TUint KHsLcdLccr1Elw      =   16;
const TUint KHmLcdLccr1Elw      =   0x000000ff<<KHsLcdLccr1Elw;
const TUint KHsLcdLccr1Hsw      =   10;
const TUint KHmLcdLccr1Hsw      =   0x0000003f<<KHsLcdLccr1Hsw;
const TUint KHsLcdLccr1Ppl      =   0;
const TUint KHmLcdLccr1Ppl      =   0x000003ff<<KHsLcdLccr1Ppl;

// LCCR2
const TUint KHsLcdLccr2Bfw      =   24;
const TUint KHmLcdLccr2Bfw      =   0x000000ff<<KHsLcdLccr2Bfw;
const TUint KHsLcdLccr2Efw      =   16;
const TUint KHmLcdLccr2Efw      =   0x000000ff<<KHsLcdLccr2Efw;
const TUint KHsLcdLccr2Vsw      =   10;
const TUint KHmLcdLccr2Vsw      =   0x0000003f<<KHsLcdLccr2Vsw;
const TUint KHsLcdLccr2Lpp      =   0;
const TUint KHmLcdLccr2Lpp      =   0x000003ff<<KHsLcdLccr2Lpp;

// LCCR3
const TUint KHtLcdLccr3Dpc          =   KBit27;
const TUint KHmLcdLccr3DpcNotEnabled=   0x0;
const TUint KHsLcdLccr3Bpp          =   24;
const TUint KHmLcdLccr3Bpp          =   0x00000003<<KHsLcdLccr3Bpp;
const TUint KHtLcdLccr3Oep          =   KBit23;
const TUint KHtLcdLccr3Pcp          =   KBit22;
const TUint KHtLcdLccr3Hsp          =   KBit21;
const TUint KHtLcdLccr3Vsp          =   KBit20;
const TUint KHsLcdLccr3Api          =   16;
const TUint KHmLcdLccr3Api          =   0x0000000f<<KHsLcdLccr3Api;
const TUint KHsLcdLccr3Acb          =   8;
const TUint KHmLcdLccr3Acb          =   0x000000ff<<KHsLcdLccr3Acb;
const TUint KHsLcdLccr3Pcd          =   0;
const TUint KHmLcdLccr3Pcd          =   0x000000ff<<KHsLcdLccr3Pcd;

// LCSR
const TUint KHtLcdLcsrSint      =   KBit10;
const TUint KHtLcdLcsrBs        =   KBit9;
const TUint KHtLcdLcsrEof       =   KBit8;
const TUint KHtLcdLcsrQd        =   KBit7;
const TUint KHtLcdLcsrOu        =   KBit6;
const TUint KHtLcdLcsrIuu       =   KBit5;
const TUint KHtLcdLcsrIul       =   KBit4;
const TUint KHtLcdLcsrAbc       =   KBit3;
const TUint KHtLcdLcsrBer       =   KBit2;
const TUint KHtLcdLcsrSof       =   KBit1;
const TUint KHtLcdLcsrLdd       =   KBit0;

const TUint KHmLcdLcsrSticky    =   0x7ff;

// LDCMDx
const TUint KHtLcdLdcmdPal      =   KBit26;
const TUint KHtLcdLdcmdSofInt   =   KBit22;
const TUint KHtLcdLdcmdEofInt   =   KBit21;
const TUint KHsLcdLdcmdLen      =   0;
const TUint KHmLcdLdcmdLen      =   0x001fffff<<KHsLcdLdcmdLen;

// FBRx
const TUint KHsLcdFbrSrcAddr    =   4;
const TUint KHmLcdFbrSrcAddr    =   0x07ffffff<<KHsLcdFbrSrcAddr;
const TUint KHtLcdFbrBint       =   KBit1;
const TUint KHtLcdFbrBra        =   KBit0;

/**
 * USB Client Controller (UDC)
 */
// Some definitions
const TInt KHUdcTotalEndpoints  =   16;

// UDC registers
const TUint KHwRwUdcUdccr       =   KHwBaseUdc + 0x00;		// UDC Control Register
const TUint KHwRwUdcReserved0   =   KHwBaseUdc + 0x04;		// Reserved for Future Use 0
const TUint KHwRwUdcReserved1   =   KHwBaseUdc + 0x08;		// Reserved for Future Use 1
const TUint KHwRwUdcReserved2   =   KHwBaseUdc + 0x0C;		// Reserved for Future Use 2
const TUint KHwRwUdcUdccs0      =   KHwBaseUdc + 0x10;		// UDC Endpoint 0 Control/Status Register
const TUint KHwRwUdcUdccs1      =   KHwBaseUdc + 0x14;		// UDC Endpoint 1 (IN) Control/Status Register
const TUint KHwRwUdcUdccs2      =   KHwBaseUdc + 0x18;		// UDC Endpoint 2 (OUT) Control/Status Register
const TUint KHwRwUdcUdccs3      =   KHwBaseUdc + 0x1C;		// UDC Endpoint 3 (IN) Control/Status Register
const TUint KHwRwUdcUdccs4      =   KHwBaseUdc + 0x20;		// UDC Endpoint 4 (OUT) Control/Status Register
const TUint KHwRwUdcUdccs5      =   KHwBaseUdc + 0x24;		// UDC Endpoint 5 (Interrupt) Control/Status Register
const TUint KHwRwUdcUdccs6      =   KHwBaseUdc + 0x28;		// UDC Endpoint 6 (IN) Control/Status Register
const TUint KHwRwUdcUdccs7      =   KHwBaseUdc + 0x2C;		// UDC Endpoint 7 (OUT) Control/Status Register
const TUint KHwRwUdcUdccs8      =   KHwBaseUdc + 0x30;		// UDC Endpoint 8 (IN) Control/Status Register
const TUint KHwRwUdcUdccs9      =   KHwBaseUdc + 0x34;		// UDC Endpoint 9 (OUT) Control/Status Register
const TUint KHwRwUdcUdccs10     =   KHwBaseUdc + 0x38;		// UDC Endpoint 10 (Interrupt) Control/Status Register
const TUint KHwRwUdcUdccs11     =   KHwBaseUdc + 0x3C;		// UDC Endpoint 11 (IN) Control/Status Register
const TUint KHwRwUdcUdccs12     =   KHwBaseUdc + 0x40;		// UDC Endpoint 12 (OUT) Control/Status Register
const TUint KHwRwUdcUdccs13     =   KHwBaseUdc + 0x44;		// UDC Endpoint 13 (IN) Control/Status Register
const TUint KHwRwUdcUdccs14     =   KHwBaseUdc + 0x48;		// UDC Endpoint 14 (OUT) Control/Status Register
const TUint KHwRwUdcUdccs15     =   KHwBaseUdc + 0x4C;		// UDC Endpoint 15 (Interrupt) Control/Status Register
const TUint KHwRwUdcUicr0       =   KHwBaseUdc + 0x50;		// UDC Interrupt Control Register 0
const TUint KHwRwUdcUicr1       =   KHwBaseUdc + 0x54;		// UDC Interrupt Control Register 1
const TUint KHwRwUdcUsir0       =   KHwBaseUdc + 0x58;		// UDC Status Interrupt Register 0
const TUint KHwRwUdcUsir1       =   KHwBaseUdc + 0x5C;		// UDC Status Interrupt Register 1
const TUint KHwRwUdcUfnhr       =   KHwBaseUdc + 0x60;		// UDC Frame Number Register High
const TUint KHwRoUdcUfnlr       =   KHwBaseUdc + 0x64;		// UDC Frame Number Register Low
const TUint KHwRoUdcUbcr2       =   KHwBaseUdc + 0x68;		// UDC Byte Count Register 2
const TUint KHwRoUdcUbcr4       =   KHwBaseUdc + 0x6C;		// UDC Byte Count Register 4
const TUint KHwRoUdcUbcr7       =   KHwBaseUdc + 0x70;		// UDC Byte Count Register 7
const TUint KHwRoUdcUbcr9       =   KHwBaseUdc + 0x74;		// UDC Byte Count Register 9
const TUint KHwRoUdcUbcr12      =   KHwBaseUdc + 0x78;		// UDC Byte Count Register 12
const TUint KHwRoUdcUbcr14      =   KHwBaseUdc + 0x7C;		// UDC Byte Count Register 14
const TUint KHwRwUdcUddr0       =   KHwBaseUdc + 0x80;		// UDC Endpoint 0 Data Register
const TUint KHwWoUdcUddr1       =   KHwBaseUdc + 0x100;		// UDC Endpoint 1 Data Register
const TUint KHwRoUdcUddr2       =   KHwBaseUdc + 0x180;		// UDC Endpoint 2 Data Register
const TUint KHwWoUdcUddr3       =   KHwBaseUdc + 0x200;		// UDC Endpoint 3 Data Register
const TUint KHwRoUdcUddr4       =   KHwBaseUdc + 0x400;		// UDC Endpoint 4 Data Register
const TUint KHwWoUdcUddr5       =   KHwBaseUdc + 0xA0;		// UDC Endpoint 5 Data Register
const TUint KHwWoUdcUddr6       =   KHwBaseUdc + 0x600;		// UDC Endpoint 6 Data Register
const TUint KHwRoUdcUddr7       =   KHwBaseUdc + 0x680;		// UDC Endpoint 7 Data Register
const TUint KHwWoUdcUddr8       =   KHwBaseUdc + 0x700;		// UDC Endpoint 8 Data Register
const TUint KHwRoUdcUddr9       =   KHwBaseUdc + 0x900;		// UDC Endpoint 9 Data Register
const TUint KHwWoUdcUddr10      =   KHwBaseUdc + 0xC0;		// UDC Endpoint 10 Data Register
const TUint KHwWoUdcUddr11      =   KHwBaseUdc + 0xB00;		// UDC Endpoint 11 Data Register
const TUint KHwRoUdcUddr12      =   KHwBaseUdc + 0xB80;		// UDC Endpoint 12 Data Register
const TUint KHwWoUdcUddr13      =   KHwBaseUdc + 0xC00;		// UDC Endpoint 13 Data Register
const TUint KHwRoUdcUddr14      =   KHwBaseUdc + 0xE00;		// UDC Endpoint 14 Data Register
const TUint KHwWoUdcUddr15      =   KHwBaseUdc + 0xE0;		// UDC Endpoint 15 Data Register

// UDC register bit definitions
const TUint KHtUdcUdccrRem      =   KBit7;					// UDCCR
const TUint KHtUdcUdccrRstir    =   KBit6;
const TUint KHtUdcUdccrSrm      =   KBit5;
const TUint KHtUdcUdccrSusir    =   KBit4;
const TUint KHtUdcUdccrResir    =   KBit3;
const TUint KHtUdcUdccrRsm      =   KBit2;
const TUint KHtUdcUdccrUda      =   KBit1;
const TUint KHtUdcUdccrUde      =   KBit0;

const TUint KHtUdcUicr0Im0      =   KBit0;					// UICR0
const TUint KHtUdcUicr0Im1      =   KBit1;
const TUint KHtUdcUicr0Im2      =   KBit2;
const TUint KHtUdcUicr0Im3      =   KBit3;
const TUint KHtUdcUicr0Im4      =   KBit4;
const TUint KHtUdcUicr0Im5      =   KBit5;
const TUint KHtUdcUicr0Im6      =   KBit6;
const TUint KHtUdcUicr0Im7      =   KBit7;

const TUint KHtUdcUicr1Im8      =   KBit0;					// UICR1
const TUint KHtUdcUicr1Im9      =   KBit1;
const TUint KHtUdcUicr1Im10     =   KBit2;
const TUint KHtUdcUicr1Im11     =   KBit3;
const TUint KHtUdcUicr1Im12     =   KBit4;
const TUint KHtUdcUicr1Im13     =   KBit5;
const TUint KHtUdcUicr1Im14     =   KBit6;
const TUint KHtUdcUicr1Im15     =   KBit7;

const TUint KHtUdcUsir0Ir0      =   KBit0;					// USIR0
const TUint KHtUdcUsir0Ir1      =   KBit1;
const TUint KHtUdcUsir0Ir2      =   KBit2;
const TUint KHtUdcUsir0Ir3      =   KBit3;
const TUint KHtUdcUsir0Ir4      =   KBit4;
const TUint KHtUdcUsir0Ir5      =   KBit5;
const TUint KHtUdcUsir0Ir6      =   KBit6;
const TUint KHtUdcUsir0Ir7      =   KBit7;

const TUint KHtUdcUsir1Ir8      =   KBit0;					// USIR1
const TUint KHtUdcUsir1Ir9      =   KBit1;
const TUint KHtUdcUsir1Ir10     =   KBit2;
const TUint KHtUdcUsir1Ir11     =   KBit3;
const TUint KHtUdcUsir1Ir12     =   KBit4;
const TUint KHtUdcUsir1Ir13     =   KBit5;
const TUint KHtUdcUsir1Ir14     =   KBit6;
const TUint KHtUdcUsir1Ir15     =   KBit7;

const TUint KHtUdcUdccs0Opr     =   KBit0;					// UDCCS0
const TUint KHtUdcUdccs0Ipr     =   KBit1;
const TUint KHtUdcUdccs0Ftf     =   KBit2;
const TUint KHtUdcUdccs0Drwf    =   KBit3;
const TUint KHtUdcUdccs0Sst     =   KBit4;
const TUint KHtUdcUdccs0Fst     =   KBit5;
const TUint KHtUdcUdccs0Rne     =   KBit6;
const TUint KHtUdcUdccs0Sa      =   KBit7;

const TUint KHtUdcUdccs1Tfs     =   KBit0;					// UDCCS1, UDCCS6, UDCCS11
const TUint KHtUdcUdccs1Tpc     =   KBit1;
const TUint KHtUdcUdccs1Tur     =   KBit3;
const TUint KHtUdcUdccs1Sst     =   KBit4;
const TUint KHtUdcUdccs1Tsp     =   KBit7;

const TUint KHtUdcUdccs2Rfs     =   KBit0;					// UDCCS2, UDCCS7, UDCCS12
const TUint KHtUdcUdccs2Rpc     =   KBit1;
const TUint KHtUdcUdccs2Sst     =   KBit4;
const TUint KHtUdcUdccs2Rne     =   KBit6;
const TUint KHtUdcUdccs2Rsp     =   KBit7;

const TUint KHtUdcUdccs3Tfs     =   KBit0;					// UDCCS3, UDCCS8, UDCCS13
const TUint KHtUdcUdccs3Tpc     =   KBit1;
const TUint KHtUdcUdccs3Tsp     =   KBit7;

const TUint KHtUdcUdccs4Rpc     =   KBit1;					// UDCCS4, UDCCS9, UDCCS14
const TUint KHtUdcUdccs4Rne     =   KBit6;
const TUint KHtUdcUdccs4Rsp     =   KBit7;

const TUint KHtUdcUdccs5Tfs     =   KBit0;					// UDCCS5, UDCCS10, UDCCS15
const TUint KHtUdcUdccs5Tpc     =   KBit1;
const TUint KHtUdcUdccs5Tur     =   KBit3;
const TUint KHtUdcUdccs5Sst     =   KBit4;
const TUint KHtUdcUdccs5Tsp     =   KBit7;

const TUint KHtUdcUfnhrIpe4     =   KBit3;					// UFNHR
const TUint KHtUdcUfnhrIpe9     =   KBit4;
const TUint KHtUdcUfnhrIpe14    =   KBit5;
const TUint KHtUdcUfnhrSim      =   KBit6;
const TUint KHtUdcUfnhrSir      =   KBit7;

// UDC register mask definitions
const TUint KHmUdcUfnhrFnmsb    =   KBit2 | KBit1 | KBit0;	// Most significant 3-bits of frame number


// AC'97 Controller
const TUint KHwRwAC97Pocr		=	KHwBaseAc97 + 0x00;
const TUint KHwRwAC97Picr		=	KHwBaseAc97 + 0x04;
const TUint KHwRwAC97Mccr		=	KHwBaseAc97 + 0x08;
const TUint KHwRwAC97Gcr		=	KHwBaseAc97 + 0x0C;
const TUint KHwRwAC97Posr		=	KHwBaseAc97 + 0x10;
const TUint KHwRwAC97Pisr		=	KHwBaseAc97 + 0x14;
const TUint KHwRwAC97Mcsr		=	KHwBaseAc97 + 0x18;
const TUint KHwRwAC97Gsr		=	KHwBaseAc97 + 0x1C;
const TUint KHwRwAC97Car		=	KHwBaseAc97 + 0x20;
const TUint KHwRwAC97Pcdr		=	KHwBaseAc97 + 0x40;
//const TUint KHwRwAC97PcdrAddr	=	0x40500040;
const TUint KHwRwAC97Mcdr		=	KHwBaseAc97 + 0x60;
const TUint KHwRwAC97Mocr		=	KHwBaseAc97 + 0x100;
const TUint KHwRwAC97Micr		=	KHwBaseAc97 + 0x108;
const TUint KHwRwAC97Mosr		=	KHwBaseAc97 + 0x110;
const TUint KHwRwAC97Misr		=	KHwBaseAc97 + 0x118;
const TUint KHwRwAC97Modr		=	KHwBaseAc97 + 0x140;
const TUint KHwRwAC97PrimaryCodec	=	KHwBaseAc97 + 0x200;
const TUint KHwRwAC97SecondaryCodec	=	KHwBaseAc97 + 0x300;
const TUint KHwRwAC97PrimaryModem	=	KHwBaseAc97 + 0x400;
const TUint KHwRwAC97SecondaryModem	=	KHwBaseAc97 + 0x500;

// AC'97 Global Status Register (GSR)
const TUint KHtAC97GsrGsci      =   KBit0;
const TUint KHtAC97GsrMiint     =   KBit1;
const TUint KHtAC97GsrMoint     =   KBit2;
const TUint KHtAC97GsrPiint     =   KBit5;
const TUint KHtAC97GsrPoint     =   KBit6;
const TUint KHtAC97GsrMint      =   KBit7;
const TUint KHtAC97GsrPcr       =   KBit8;  // Primary codec ready
const TUint KHtAC97GsrScr       =   KBit9;  // Secondary codec ready
const TUint KHtAC97GsrPri       =   KBit10; // Primary resume interrupt
const TUint KHtAC97GsrSri       =   KBit11; // Secondary resume interrupt
const TUint KHtAC97GsrRcs       =   KBit15; // Read completion status
const TUint KHtAC97GsrSdone     =   KBit18; // Status done
const TUint KHtAC97GsrCdone     =   KBit19; // Command done

// AC'97 Codec Access Register
const TUint KHtAC97CarCaip      =   KBit0;  // Codec Access in Progress

// AC'97 Global Control Register
const TUint KHtAC97GcrGie       =   KBit0;
const TUint KHtAC97GcrColdReset =   KBit1;
const TUint KHtAC97GcrWarmReset =   KBit2;
const TUint KHtAC97GcrShutOff   =   KBit3;
const TUint KHtAC97GcrPrie      =   KBit4;  // Primary resume interrupt enable
const TUint KHtAC97GcrSrie      =   KBit5;  // Secondary resume int. enable
const TUint KHtAC97GcrPrirdyIen =   KBit8;  // Primary ready int. enable
const TUint KHtAC97GcrSecrdyIen =   KBit9;  // Secondary ready int. enable
const TUint KHtAC97GcrSdoneIe   =   KBit18; // Status done int. enable
const TUint KHtAC97GcrCdoneIe   =   KBit19; // Command done int. enable

// AC'97 PCM-OUT Control Register
const TUint KHtAC97PocrFeie     =   KBit3;  // FIFO error interrupt enable, PCM-OUT

// AC'97 PCM-IN Control Register
const TUint KHtAC97PicrFeie     =   KBit3;  // FIFO error interrupt enable, PCM-IN

// AC'97 PCM-OUT Status Register
const TUint KHtAC97PosrFifoe	=	KBit4;  // FIFO error
// AC'97 PCM-IN Status Register
const TUint KHtAC97PisrFifoe	=	KBit4;  // FIFO error

// MMC register definitions
//  MMC bus clock
const TUint KHtMmcStrpcl			=	KHwBaseMmc+0x0;
const TUint KHtMmcStrpclStpClk	=	KBit0;	  // stop clock; writing 1 stops the MMC clock
													// bit automatically cleared to 0
const TUint KHtMmcStrpclStrtClk	=  	KBit1;	 // start clock; writing 1 starts the MMC clock
													// bit automatically cleared to 0

// MMC 	status register
const TUint KHtRoMmcStat				= 	KHwBaseMmc+0x4;
const TUint KHtRoMmcStatRdTmot		=	KBit0;  //  read timed out
const TUint KHtRoMmcStatTmotRspns	= 	KBit1;	//   card response timed out
const TUint KHtRoMmcStatCrcWrtErr	=	KBit2;  //  card observed erroneous transmission of data
const TUint KHtRoMmcStatCrcRdErr	=	KBit3;  //   crc error on recieved data				
const TUint KHtRoMmcStatSpiRdErrTkn =	KBit4;	//  spi data error token has been received
const TUint KHtRoMmcStatResCrcErr	=	KBit5;	// response crc error
const TUint KHtRoMmcStatXmitFifoEmpty	=	KBit6;	// transmitt fifo is empty
const TUint KHtRoMmcStatRecvFifoFull	= 	KBit7;	//  receive fifo is full
const TUint KHtRoMmcStatClkEn		=	KBit8;	//MMC clock is on	
const TUint KHtRoMmcStatDataTranDone	=	KBit11;	//  data transmission card has completed
const TUint KHtRoMmcStatPrgDone		= KBit12;  // card has finished programming and is not busy
const TUint KHtRoMmcStatEndCmdRes	= KBit13;	//  command and response sequence has completed

//  MMC Clock rate register
const TUint KHtRoMmcClkRt				= 	KHwBaseMmc+0x8;

//  MMC SPI register
const TUint KHtRwMmcSpi				= 	KHwBaseMmc+0xc;
const TUint KHtRwMmcSpiEn				= 	KBit0; 	//  enables spi mode
const TUint KHtRwMmcSpiCrcOn			=	KBit1;  //  enable crc generation and verification
const TUint KHtRwMmcSpiCsEn			= 	KBit2;  // enables spi chip select
const TUint KHtRwMmcSpiCsAddr		= 	KBit3;  // 1 enables CS1; 0 enable CS0

//  MMC command data register
const TUint KHtRwMmcCmdat				= 	KHwBaseMmc+0x10;
const TUint KHtRwMmcCmdatRspnFrmt	=	0x3;
const TUint KHtRwMmcCmdatDataEn		=  KBit2;  //  current command includes data
const TUint KHtRwMmcCmdatWrRd		=  KBit3;	// 0 specifies a read; 1 specifies a write
const TUint KHtRwMmcCmdatStrmBlk		=  KBit4;  //current command is in stream block mode
const TUint KHtRwMmcCmdatBusy			=  KBit5;  // specifies whether a busy signal is expected after
													//  after current command;  for no data trans. only
const TUint KHtRwMmcCmdatInit		=  KBit6;  // precede command sequence with 80 clocks
const TUint KHtRwMmcCmdatDmaEn		=  KBit7;	//  DMA mode

//  MMC Resto register
const TUint KHtRwMmcResto			= 	KHwBaseMmc+0x14;
const TUint KHtRwMmcRestoBits	=   0x7f;  //  number of MMC clocks before a response times out

//  MMC read time out register
const TUint KHtRwMmcRdTo		 = 	KHwBaseMmc+0x18;
const TUint KHtRwMmcRdtoBits	= 0xffff;

//  MMC block length register
const TUint KHtRwMmcBlklen	  = 	KHwBaseMmc+0x1c;
const TUint KHtRwMmcBlklenBits = 0x3ff;

//  MMC number of blocks register
const TUint KHtRwMmcNob		 = 	KHwBaseMmc+0x20;
const TUint KHtRwMmcNobBits		= 0xffffffff;

//  MMC partial full buffer register			
const TUint KHtRwMmcPtrBuf		 = 	KHwBaseMmc+0x24;
const TUint KHtRwMmcPtrBufBit	 = KBit0;  //  buffer is partially full and must be swapped to the other transmit buffer

//  MMC interrupt mask register
const TUint KHtRwMmcIMask		 = 	KHwBaseMmc+0x28;
const TUint KHtRwMmcIMaskDataTransDone	= KBit0;  // data transfer is done
const TUint KHtRwMmcIMaskPrgDone	= KBit1; // programming is done
const TUint KHtRwMmcIMaskEndCmdRes	= KBit2; //  end command response
const TUint KHtRwMmcIMaskStopCmd	= KBit3;  // ready for stop transaction command
const TUint KHtRwMmcIMaskClkIsOff	= KBit4; // clock is off
const TUint KHtRwMmcIMaskRxfifoRdReq	= KBit5;  //receive fifo read request
const TUint KHtRwMmcIMaskTxfifoWrReq	= KBit6;  //  transmit fifo write request

//  MMC current interrupt register
const TUint KHtRwMmcIReg		 = 	KHwBaseMmc+0x2c;
const TUint KHtRwMmcIRegDataTransDone	= KBit0;  // data transfer is done;  cleared by the mmc_stat[dataDone]
const TUint KHtRwMmcIRegPrgDone	= KBit1; // programming is done;  cleared by the mmc_stat[prgDone]
const TUint KHtRwMmcIRegEndCmdRes	= KBit2; //  end command response;  cleared by the mmc_stat[endCmdRes]
const TUint KHtRwMmcIRegStopCmd	= KBit3;  // ready for stop transaction command;  cleared when cmd12 is loaded
const TUint KHtRwMmcIRegClkIsOff	= KBit4; // clock is off;  cleared by the mmc_stat[clkEn]
const TUint KHtRwMmcIRegRxfifoRdReq	= KBit5;  //receive fifo read request; cleared after each read but immediately
												// set again unless the fifo is empty
const TUint KHtRwMmcIRegTxfifoWrReq	= KBit6;  //  transmit fifo write request; cleared after each write but immediately
												// set again unless the fifo is empty
//  MMC Command registers that specifies the commands
const TUint KHtRwMmcCmd		 	= KHwBaseMmc+0x30;
const TUint KHtRwMmcCmdBits		= 0x3f;

//  MMC upper 16 bits of the argument for the current command
const TUint KHtRwMmcArgh	    = KHwBaseMmc+0x34;
const TUint KHtRwMmcArghBits	= 0xffff;

//  MMC lower 16 bits of the argument for the current command
const TUint KHtRwMmcArgl	    = KHwBaseMmc+0x38;
const TUint KHtRwMmcArglBits	= 0xffff << 16;

//  MMC response fifo
const TUint KHtRoMmcResFifo	 	= KHwBaseMmc+0x3c;
const TUint KHtRoMmcResFifoBits	= 0xffff;

//  MMC  Receive fifo
const TUint KHtRoMmcRxFifo	 	= KHwBaseMmc+0x40;
const TUint KHtRoMmcRxFifoBits	= 0xff;

//  MMC transmit fifo
const TUint KHtWoMmcTxFifo	 	= KHwBaseMmc+0x44;
const TUint KHtWoMmcTxFifoBits	= 0xff;

/**
 * TDMAdesc class for DMA descriptor
 */
class TDMAdesc
{
	public:
	class TDMAdesc *DDADR;
	char *DSADR;
	char *DTADR;
	TUint DCMD;
};

/**
 * TCotulla class
 */
class TCotulla
	{
public:

	//
	// Various public enumerated values
	//
	// 
	// 

	enum TPolarity
		{
		EPolarityActiveLow,
		EPolarityActiveHigh
		};
	enum TEdge
		{
		EEdgeRising,		// RWZ: CHECK ORDERING!
		EEdgeFalling
		};
    // DRAM configuration enumerations
	enum TDramClockDiv
		{
		EDramClockCpu=KClear32,
//		EDramClockMem=KHtMemMdcnfgCdb2  <<==  NMD  what should this be???
		};
    // ROM/SRAM configuration enumerations
	enum TRomType
		{
		ERomTypeNoBurstFlash=0<<KHsMemMscRt,
		ERomTypeNoBurstSram=1<<KHsMemMscRt,
		ERomTypeBurst4Rom=2<<KHsMemMscRt,
		ERomTypeBurst8Rom=3<<KHsMemMscRt
		};
	enum TRomWidth
		{
		ERomWidth32=KClear32,
		ERomWidth16=KHtMemMscRbw
		};
    // Expansion memory configuration enumerations

   // LCD enumerations
	enum TLcdEnable
		{
		ELcdDisable=KClear32,
		ELcdEnable=KHtLcdLccr0Enb
		};
	enum TLcdBitsPerPixel
		{
		ELcd4BitsPerPixel,
		ELcd8BitsPerPixel,
		ELcd12BitsPerPixel,
		ELcd16BitsPerPixel
		};
	enum TLcdMode
		{
		ELcdModePassiveMono=KHtLcdLccr0Cms,
		ELcdModePassiveColor=KClear32,
		ELcdModeActiveColor=KHtLcdLccr0Pas
		};
	enum TLcdPanelConfig
		{
		ELcdSinglePanel=KClear32,
		ELcdSinglePanelDoublePix=KHtLcdLccr0Dpd,
		ELcdDualPanel=KHtLcdLccr0Sds
		};
	enum TLcdMemoryGender
		{
		ELcdmemoryLittleEndian=KClear32,
		ELcdmemoryBigEndian=KHtLcdLccr0Ble
		};
	enum TLcdDmaChannel
		{
		ELcdDmaChannel1,
		ELcdDmaChannel2
		};
	enum TLcdDisableDoneInt
		{
		ELcdDisDoneIntEnable=KClear32,
		ELcdDisDoneIntDisable=KHtLcdLccr0Ldm
		};

	enum TLcdBaseStartOfFrameInt						// RamiZ: New to Cotulla
		{
		ELcdBaseStartOfFrameEnable=KClear32,
		ELcdStartOfFrameIntDisable=KHtLcdLccr0Sfm
		};

	enum TLcdInputFifoUnderrunInt						// RamiZ: New to Cotulla
		{
		ELcdInputFifoUnderrunEnable=KClear32,
		ELcdInputFifoUnderrunIntDisable=KHtLcdLccr0Ium	
		};

	enum TLcdEndOfFrameInt								// RamiZ: New to Cotulla
		{
		ELcdEndOfFrameEnable=KClear32,
		ELcdEndOfFrameIntDisable=KHtLcdLccr0Efm			
		};


	enum TLcdQuickDisableInt							// RamiZ: New to Cotulla
		{
		ELcdQuickDisableIntEnable=KClear32,
		ELcdQuickDisableIntDisable=KHtLcdLccr0Qdm
		};


	enum TLcdBranchInt									// RamiZ: New to Cotulla
		{
		ELcdBranchIntEnable=KClear32,
		ELcdBranchIntDisable=KHtLcdLccr0Bm
		};


	enum TLcdOutputFifoUnderrunInt						// RamiZ: New to Cotulla
		{
		ELcdOutputFifoUnderrunEnable=KClear32,
		ELcdOutputFifoUnderrunDisable=KHtLcdLccr0Oum
		};


// UART ENUMS
	enum TUartBaud	
		{
		EBaud50     = _UART_BRD(50),
		EBaud75     = _UART_BRD(75),
		EBaud150    = _UART_BRD(150),
		EBaud300    = _UART_BRD(300),
		EBaud600    = _UART_BRD(600),
		EBaud1200   = _UART_BRD(1200),
		EBaud2400   = _UART_BRD(2400),
		EBaud4800   = _UART_BRD(4800),
		EBaud7200   = _UART_BRD(7200),
		EBaud9600   = _UART_BRD(9600),
		EBaud19200  = _UART_BRD(19200),
		EBaud38400  = _UART_BRD(38400),
		EBaud57600  = _UART_BRD(57600),
		EBaud115200 = _UART_BRD(115200),
		EBaud230400 = _UART_BRD(230400)
		};

	enum TUartParity
		{
		EUartParityNone=KClear32,
		EUartParityOdd=KHtUartLcrPen,
		EUartParityEven=KHtUartLcrPen|KHtUartLcrEps
		};

	enum TUartDataBits
		{
		EDataBits5,
		EDataBits6,
		EDataBits7,
		EDataBits8
		};

	enum TUartStopBits
		{
		EStopBits1=KClear32, 
		EStopBits2=KHtUartLcrStb 
		//To get 1.5 stopbits you set #databits to 5 and #stopbits to 2
		};

	enum TUartOutLines
		{
		ERts = KHtUartMcrRts,
		EDtr = KHtUartMcrDtr
		};

	enum TUartInLines
		{
		EDsr = KHtUartMsrDsr,
		ECts = KHtUartMsrCts,
		EDcd = KHtUartMsrDcd,
		ERi = KHtUartMsrRi
		};

	enum TUartFifoIntFlags
		{
		EUartNoFifo = KClear32,
		EUartFifoRxInt = KHtUartIerRavie,
		EUartFifoTxInt = KHtUartIerTie,
		EUartFifoRxTxInt = KHtUartIerRavie|KHtUartIerTie,
		};

	enum TUartIntFlags
	{
        EUartNoInt = KClear32,
        EUartLineStatusInt = KHtUartIerRlse, 
		EUartModemStatusInt = KHtUartIerMie,
		EUartRevTimeOutInt = KHtUartIerRtoie,
		EUartLineModemStatus = KHtUartIerRlse|KHtUartIerMie,
		EUartLineRevTimeOut = KHtUartIerRlse|KHtUartIerRtoie,
		EUartModemRevTimeOut = KHtUartIerMie|KHtUartIerRtoie,
		EUartLineModemTimeOut =KHtUartIerRlse|KHtUartIerMie|KHtUartIerRtoie 
	};

    enum TUartXmitEnable
	{
		EUartDisable=KClear32,
		EUartEnable= KHtUartIerUue
	};

	enum TUartDmaEnable
	{
		EUartDmaDisable = KClear32,
		EUartDmaEnable = KHtUartIerDmae
	};

	enum TUartNrzEnable
	{
		EUartNrzDisable = KClear32,
		EUartNrzEnable = KHtUartIerNrze
	};

	enum TUartErrorFlags
		{
		EUartErrParity = KHtUartLsrPe,
		EUartErrFraming = KHtUartLsrFe,
		EUartErrOverrun = KHtUartLsrOe
		};

	enum TUartLoopback
		{
		EUartLoopbackOff=KClear32,
		EUartLoopbackOn=KHtUartMcrLoop
		};

	enum TUartOut2
	{
		EUartOut2Off = KClear32,
		EUartOut2On = KHtUartMcrOut2
	};

	enum TUartFifoFlags
	{
		EUartFifoDisable = KClear32,
		EUartFifoEnable = KHtUartFcrFe
	};
	
	enum TUartFifoReset
	{
		EUartResetRxFifo	= KHtUartFcrResetRf,
		EUartResetTxFifo 	= KHtUartFcrResetTf,
		EUartResetRxTxFifo 	= KHtUartFcrResetRf | KHtUartFcrResetTf 
	};

	enum TUartRxFifoTriLevel
	{
		EUartRxFifo1 = 0x00,
		EUartRxFifo8 = 0x40,
		EUartRxFifo16 = 0x80,
		EUartRxFifo32 = 0xc0
	};

	enum TUartBreak
		{
		EUartBreakOff=KClear32,
		EUartBreakOn=KHtUartLcrSb
		};

	enum TUartDlab
	{
		EUartDlab0 = KClear32,
		EUartDlab1 = KHtUartLcrDlab
	};

    // Slow IR specific enumeration
	enum TSirXmitEnable
	{
		ESirDisable = KClear32,
        ESirTxEnable = KHtUartIsrXmitir,
		ESirRxEnable = KHtUartIsrRcveir,
		ESirTxRxEnable = KHtUartIsrXmitir|KHtUartIsrRcveir 
	};

	enum TSirPowerMode
		{
		ESirLowPowerDisable = KClear32,
		ESirLowPowerEnable  = KHtUartIsrXmode
		};

	enum TSirXmitPolarity
	{
		ESirPolarityPos0 = KClear32,
		ESirTxPolarityNeg0 = KHtUartIsrTxpl,
		ESirRxPolarityNeg0 = KHtUartIsrRxpl,
		ESirTxRxPolarityNeg0 = KHtUartIsrTxpl|KHtUartIsrRxpl
	};

	// Fast Infra-red enumerations
	enum TIcpEnable
		{
		EIcpEnableOff =KClear32,
		EIcpEnableOn  =KHtIcpCr0Itr
		};

	enum TIcpLoopback
		{
		EIcpLoopbackOff=KClear32,
		EIcpLoopbackOn =KHtIcpCr0Lbm
		};
	enum TIcpUnderrunBehaviour
		{
		EIcpEndOnUnderrun   =KClear32,
		EIcpAbortOnUnderrun =KHtIcpCr0Tus 
		};
	enum TIcpXmitEnable
		{
		EIcpDisable   =KClear32,
		EIcpRxEnable  =KHtIcpCr0Rxe,
		EIcpTxEnable  =KHtIcpCr0Txe,
		EIcpRxTxEnable=KHtIcpCr0Rxe|KHtIcpCr0Txe
		};
	enum TIcpFifoInt
		{
		EIcpFifoNoInt  =KClear32,
		EIcpFifoRxInt  =KHtIcpCr0Rie,
		EIcpFifoTxInt  =KHtIcpCr0Tie,
		EIcpFifoRxTxInt=KHtIcpCr0Rie|KHtIcpCr0Tie
		};
	enum TIcpAddressMatch
		{

		EIcpAddrMatchDisable = KClear32,
		EIcpAddrMatchEnable  = KHtIcpCr0Amr
		};

	enum TIcpPinPolarity
		{
		EIcpTxTrueRxTrue = KHtIcpCr2Rxp|KHtIcpCr2Txp,
		EIcpTxTrueRxInv  = KHtIcpCr2Txp,
		EIcpTxInvRxTrue  = KHtIcpCr2Rxp,
		EIcpTxInvRxInv   = KClear32
		};

	enum TIcpRxFifoTriLevel
	{
		EIcpRxFifo8 = 0x00,
        EIcpRxFifo16 = 0x01,
		EIcpRxFifo32 = 0x02
	};
	// MMC CLOCK RATE
	enum TMmcClkRate
	{
	  EMmc20MHz = 0x0,
	  EMmc10MHz = 0x1,
	  EMmc5MHz	= 0x2,
	  EMmc2_5MHz = 0x3,
	  EMmc1_25MHz = 0x4,
	  EMmc_625MHz = 0x5,
	  EMmc_3125MHz = 0x6
	};

	//  MMC response format
	enum TMmcRspnFrmt
	{
	  EMmcNoResponse = 0x0,
	  EMmcMmcSpiR1	= 0x1,
	  EMmcMmcSpiR2	= 0x2,
	  EMmcMmcR3		= 0x3
	};

	//  MMC Command Index values
	enum TMmcCmdIndex
	{
	  EMmcSpiCmd0		= 0x0,	// go idle state
	  EMmcSpiCmd1		= 0x1,	// send op command
	  EMmcCmd2			= 0x2,	// all send cid
	  EMmcCmd3			= 0x3,	// set relative addr
	  EMmcCmd4			= 0x4,	// set dsr
	  EMmcCmd7			= 0x7,	 // select/deselect card
	  EMmcSpiCmd9		= 0x9,	// send csd
	  EMmcSpiCmd10		= 0xa,	// send cid
	  EMmcCmd11			= 0xb,	//  read data until stop
	  EMmcCmd12			= 0xc,	 // stop transmission
	  EMmcSpiCmd13		= 0xd,	 // send status
	  EMmcCmd15			= 0xf,	// go inactive state
	  EMmcSpiCmd16		= 0x10,	//  set block length
	  EMmcSpiCmd17		= 0x11,	// read single block
	  EMmcCmd18			= 0x12,	//  read multiple block
	  EMmcCmd20			= 0x14,	 // write data until stop
	  EMmcSpiCmd24		= 0x18,	 // write block
	  EMmcCmd25			= 0x19,	 // write multiple block
	  EMmcCmd26			= 0x1a,	// program CID
	  EMmcSpiCmd27		= 0x1b,	// program CSD
	  EMmcSpiCmd28		= 0x1c,	// set write prot
	  EMmcSpiCmd29		= 0x1d,  // clr write prot
	  EMmcSpiCmd30		= 0x1e,	// send write prot
	  EMmcSpiCmd32		= 0x200,	 // tag sector start
	  EMmcSpiCmd33		= 0x201,	// tag sector end
	  EMmcSpiCmd34		= 0x202,	// untag sector
	  EMmcSpiCmd35		= 0x203,	// tag erase group start
	  EMmcSpiCmd36		= 0x204,	//  tag erase group end
	  EMmcSpiCmd37		= 0x205,	 // untag erase group
	  EMmcSpiCmd38		= 0x206,	 // erase
	  EMmcCmd39			= 0x207,	//fast IO
	  EMmcCmd40			= 0x208,	// go irq state
	  EMmcSpiCmd42		= 0x2a,	// lock-unlock
	  EMmcSpiCmd55		= 0x37,	// app cmd
	  EMmcSpiCmd56		= 0x38,	//  gen cmd
	  ESpiCmd58			= 0x3a,	 // read ocr
	  ESpiCmd59			= 0x3b,	 // crc on-off
	  EMmcCmd60			= 0x3c,	// reserved for manufacturer
	  EMmcCmd61			= 0x3d,	 // reserved for manufacturer
	  EMmcCmd62			= 0x3e,	// reserved for manufacturer
	  EMmcCmd63			= 0x3f	 // reserved for manufacturer
	};


    // Synchronous Serial Port (SSP)
	enum TSspDataSize
		{
		ESspData4Bit=3,
		ESspData5Bit=4,
		ESspData6Bit=5,
		ESspData7Bit=6,
		ESspData8Bit=7,
		ESspData9Bit=8,
		ESspData10Bit=9,
		ESspData11Bit=10,
		ESspData12Bit=11,
		ESspData13Bit=12,
		ESspData14Bit=13,
		ESspData15Bit=14,
		ESspData16Bit=15
		};
	enum TSspFrameFormat
		{
		ESspFrameFormatSPI=0,
		ESspFrameFormatTISyncSer=1,
		ESspFrameFormatNatMicrowire=2
		};
static const TInt KSspClk1843200Bps = 0;
static const TInt KSspClk460800Bps = 3;
static const TInt KSspClk7200Bps = 255;
	enum TSspEnable
		{
		ESspDisable=KClear32,
		ESspEnable=KHtSspSscr0Sse
		};
	enum TSspRxFifoInt
		{
		ESspRxFifoIntDisable=KClear32,
		ESspRxFifoIntEnable=KHtSspSscr1Rie
		};
	enum TSspTxFifoInt
		{
		ESspTxFifoIntDisable=KClear32,
		ESspTxFifoIntEnable=KHtSspSscr1Tie};
	enum TSspLoopBack
		{
		ESspLoopBackDisable=KClear32,
		ESspLoopBackEnable=KHtSspSscr1Lbm};
	enum TSspSerClkPhase
		{
		ESspSclkPhaseMode1=KClear32,
		ESspSclkPhaseMode2=KHtSspSscr1Sph
		};
	enum TSspExtClockSel
		{
		ESspExtClkDisable=KClear32,
		ESspExtClkEnable=KHtSspSscr0Ecs
		};
	enum TDmaChannel
		{
		EDmaChannel0=0,
		EDmaChannel1=1,
		EDmaChannel2=2,
		EDmaChannel3=3,
		EDmaChannel4=4,
		EDmaChannel5=5,
		EDmaChannel6=6,	
		EDmaChannel7=7,	
		EDmaChannel8=8,
		EDmaChannel9=9,
		EDmaChannel10=10,
		EDmaChannel11=11,
		EDmaChannel12=12,
		EDmaChannel13=13,
		EDmaChannel14=14,
		EDmaChannel15=15
		};
    // Expansion memory configuration enumerations
	enum TExpansionType
		{
		EExpansionIo = KHwRwMemMcio0,
		EExpansionAttribute = KHwRwMemMcatt0,
		EExpansionCommon = KHwRwMemMcmem0,
		EExpansionIoSlot2 = KHwRwMemMcmem1,
		EExpansionAttributeSlot2 = KHwRwMemMcatt1,
		EExpansionCommonSlot2 = KHwRwMemMcio1
		};
    // Gpio alternate function register field settings
    enum TGpioFunction
	{
		SelectGpioNormal = 0,
		SelectGpioAlternate1 = 1,
		SelectGpioAlternate2 = 2,
		SelectGpioAlternate3 = 3
	};

	//Constants to tell functions which GPIO register is to be addressed
	enum TGpioBank{
		EGpio_X,	
		EGpio_Y,	
		EGpio_Z
	};

	enum TGpioHalfBank{
		EGpio_X0,
		EGpio_X1,
		EGpio_Y0,
		EGpio_Y1,
		EGpio_Z0,
		EGpio_Z1
	};

	enum TClockRegisterXtal2Mem{
        ECccrL_0 = 0xF, // Sabinal, 1111, Multiplier = 9
        ECccrL_1 = 0x1, // 00001 - Multiplier = 27
        ECccrL_2 = 0x2, // 00010 - Multiplier = 32
        ECccrL_3 = 0x3, // 00011 - Multiplier = 36
        ECccrL_4 = 0x4, // 00100 - Multiplier = 40
        ECccrL_5 = 0x5  // 00101 - Multiplier = 45
	};

	enum TMemFreqInKHz{
		EMemFreq_0 = 33200,		// Sabinal
		EMemFreq_1 = 99500,
		EMemFreq_2 = 118000,
		EMemFreq_3 = 132700,
		EMemFreq_4 = 147500,
		EMemFreq_5 = 165900
	};

	enum TClockRegisterMem2Run{
		ECccrM_0 = 0x01,
		ECccrM_1 = 0x02,
		ECccrM_2 = 0x03
	};

	enum TFreqMultiplierMem2Run{
		EMultM_X1 = 1,
		EMultM_X2 = 2,
		EMultM_X4 = 4
	};

	enum TClockRegisterRun2Turbo{
		ECccrN_0 = 0x02,
		ECccrN_1 = 0x03,
		ECccrN_2 = 0x04,
		ECccrN_3 = 0x05,
		ECccrN_4 = 0x06
	};

	enum TFreqMultiplierRun2Turbo{
		EMultN_X1 = 2,           
		EMultN_X2 = 3,
		EMultN_X3 = 4,
		EMultN_X4 = 5,
		EMultN_X5 = 6
	};

	enum TAcLinkStatus{
		EAcLinkStatErr = 0,
		EAcLinkStatOk = 1
    };
    
	// RTC enumerations
	enum TRtcIntSource
	{
		EDisableAll = 0,
		ERtcAlarm = KHtRtcRtsrAle,  
		E1Hz = KHtRtcRtsrHze,
		EEnableAll = KHtRtcRtsrHze|KHtRtcRtsrAle
	};


public:

	// Initialisation
	static void Init3();

	// Tuneable debug port
	static TUint32 DebugPortAddr();

	//DMA	
	IMPORT_C static TUint32 GetDmaDint();
	IMPORT_C static TUint32 GetDmaDcsr(TUint8 aChannel);
	IMPORT_C static void SetDmaDcsr(TUint8 aChannel, TUint32 aVal);
	IMPORT_C static void ClearDmaDcsr(TUint8 aChannel, TUint8 aClearMask);
	IMPORT_C static TUint32 GetDmaDrcmr(TUint32 aDevice);
	IMPORT_C static void SetDmaDrcmr(TUint32 aDevice, TUint32 aVal);
	IMPORT_C static TUint32 GetDmaDdadr(TUint8 aChannel);
	IMPORT_C static void SetDmaDdadr(TUint8 aChannel, TUint32 aVal);
	IMPORT_C static TUint32 GetDmaDsadr(TUint8 aChannel);
	IMPORT_C static void SetDmaDsadr(TUint8 aChannel, TUint32 aVal);
	IMPORT_C static TUint32 GetDmaDtadr(TUint8 aChannel);
	IMPORT_C static void SetDmaDtadr(TUint8 aChannel, TUint32 aVal);
	IMPORT_C static TUint32 GetDmaDcmd(TUint8 aChannel);
	IMPORT_C static void SetDmaDcmd(TUint8 aChannel, TUint32 aVal);

	
// Reset control (data: pages 93-95)
	IMPORT_C static void SetResetSoftware();
	IMPORT_C static TMachineStartupType StartupReason();
	IMPORT_C static void SetStartFlagClear();
// Power management (data: pages 79-92)
	IMPORT_C static void SetPowerSleepForce();
	IMPORT_C static TUint PowerSleepStatus();
	IMPORT_C static void ClearPowerSleepStatus(TUint aClearMask);
	IMPORT_C static TUint PowerConfig();
	IMPORT_C static void ModifyPowerConfig(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PowerWakeupEnable();
	IMPORT_C static void ModifyPowerWakeupEnable(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TBool Power32KHzOk();
	IMPORT_C static void Enable32KHz();
	IMPORT_C static TUint PowerScratchpad();
	IMPORT_C static void SetPowerScratchpad(TUint aValue);
	IMPORT_C static void SetStandby();
	IMPORT_C static TUint ProcessorClockInKHz();
	IMPORT_C static TUint ProcessorPeriodInPs();
	IMPORT_C static TInt CpuVersionId();
	IMPORT_C static void SetPowerRiseEdgeDetect();
	IMPORT_C static void SetPowerFallEdgeDetect();
// Memory (data: pages 96-123)
	IMPORT_C static void SetMemDramConfig(TUint aRows,TDramClockDiv aClockDiv,TUint aRasPrechg,
										  TUint aRasCbr,TUint aLatchTiming,TUint aRefresh);
	IMPORT_C static void SetMemStaticConfig(TRomType aType,TRomWidth aWidth,TUint aDelayFirst,
											TUint aDelayNext,TUint aRecover,TUint aChipSelect);
	IMPORT_C static void SetMecrRegister(TUint aClearMask,TUint aSetMask);
	IMPORT_C static void SetMemExpansionConfig(TExpansionType aType,TUint aTimeInPicoseconds);
// O/S timer (data: pages 75-78)
	IMPORT_C static TUint OstData();
	IMPORT_C static void SetOstData(TUint aValue);
	IMPORT_C static TUint OstMatch(TUint aTimer);
	IMPORT_C static void SetOstMatch(TUint aValue,TUint aTimer);
	IMPORT_C static void SetOstWatchdogEnable();
	IMPORT_C static TUint OstWatchdogMatch();
	IMPORT_C static void SetOstWatchdogMatch(TUint aValue);
	IMPORT_C static void SetOstMatchEOI(TUint aTimer);
	IMPORT_C static void EnableOstInterrupt(TUint aTimer);
	IMPORT_C static void DisableOstInterrupt(TUint aTimer);
	IMPORT_C static void BootWaitMilliSeconds(TInt aDuration);
// Real-time clock (data: pages 70-74)
	IMPORT_C static TUint RtcData();
	IMPORT_C static void SetRtcData(TUint aValue);
	IMPORT_C static void SetRtcMatch(TUint aValue);
	IMPORT_C static TUint RtcMatch();
	IMPORT_C static void SetRtcMatchEOI();
	IMPORT_C static void SetRtcTickEOI();
	IMPORT_C static TUint RtcTrim();
	IMPORT_C static void SetRtcTrim(TUint anXtalFreq);
	IMPORT_C static void EnableRtcInt(TRtcIntSource aSource);
// LCD (data: pages 142-175)
	IMPORT_C static void SetLcdEnable(TLcdEnable anEnable);
	IMPORT_C static TLcdEnable LcdEnable();
	IMPORT_C static void SetLcdSize(TUint aPixelsPerLine,TUint aLinesPerPanel);
	IMPORT_C static void SetLcdConfig(TLcdMode aMode,TLcdPanelConfig aPanelConfig);
	IMPORT_C static void SetLcdVramBases(TUint aVramBase1,TUint PanelSize=153600, TUint PaletteSize=0);
	IMPORT_C static void SetLcdMemoryConfig(TLcdMemoryGender aMemGender,TUint aDmaReqDelay);
	IMPORT_C static void SetLcdHorizontalClocks(TUint aStartCount,TUint aHsyncPulseWidth,TUint anEndCount);
	IMPORT_C static void SetLcdVerticalClocks(TUint aStartCount,TUint aVsyncPulseWidth,TUint anEndCount);
	IMPORT_C static void SetLcdOtherClocks(TUint aPixClockDiv,TUint anAcBiasFreq,TUint anAcBiasTpi);
	IMPORT_C static void SetLcdSignalsPolarity(TPolarity aVsync,TPolarity anHsync,TEdge aPixClk,TPolarity anOe);
	IMPORT_C static void ModifyLcdIntMasks( TLcdDisableDoneInt		  anLDM, TLcdBaseStartOfFrameInt anSFM, 
											TLcdInputFifoUnderrunInt  anIUM, TLcdEndOfFrameInt		 anEFM, 
											TLcdQuickDisableInt		  aQDM , TLcdBranchInt			 aBM, 
											TLcdOutputFifoUnderrunInt anOUM);
	IMPORT_C static TUint LcdStatus();
	IMPORT_C static void LcdClearStatus(TUint aClearMask);
	IMPORT_C static TUint LcdVramCurrentAddress(TLcdDmaChannel aDmaChannel);
	IMPORT_C static void SetPixelInfo(TUint aBitsPerPixel, TUint aDoublePixelClockMode);
	IMPORT_C static void InitializePalette();
	IMPORT_C static void SetLcdPaletteEntry(TUint anEntryIndex,TUint aValue);


	// UARTs 
	IMPORT_C static void SetUartData(TUint aValue,TUint aPortBase);
	IMPORT_C static TUint UartData(TUint aPortBase);
	IMPORT_C static void SetUartConfig(TUartBaud aRate,TUartParity aParity,TUartStopBits aStopBit,
									   TUartDataBits aDataLength,TUint aPortBase);
	IMPORT_C static TUartBaud UartBaudRate(TUint aPortBase);
	IMPORT_C static TUartParity UartParity(TUint aPortBase);
	IMPORT_C static TUartStopBits UartStopBits(TUint aPortBase);
	IMPORT_C static TUartDataBits UartDataBits(TUint aPortBase);
	IMPORT_C static void SetUartBreak(TUartBreak aBreak,TUint aPortBase);
	IMPORT_C static TUartBreak UartBreak(TUint aPortBase);
	IMPORT_C static void SetUartEnable(TUartXmitEnable anEnable,TUartDmaEnable dmaEnable, TUartNrzEnable nrzEnable, TUint aPortBase);
	IMPORT_C static TUartXmitEnable UartXmitEnable(TUint aPortBase);
	IMPORT_C static void SetUartFifoIntEnable(TUartFifoIntFlags fifoIntEnable, TUint aPortBase);
	IMPORT_C static TUartFifoIntFlags UartFifoIntEnable(TUint aPortBase);
	IMPORT_C static void SetUartIntEnable(TUartIntFlags intEnable, TUint aPortBase);
    IMPORT_C static TUartIntFlags UartIntEnable(TUint aPortBase);
    IMPORT_C static void SetUartLoopbackEnable(TUartLoopback loopEnable, TUint aPortBase); 
	IMPORT_C static TUartLoopback UartLoopbackEnable(TUint aPortBase);
	IMPORT_C static void SetUartFCR(TUartFifoFlags aFifoFlags, TUartFifoReset aResetRxTxFifo, TUartRxFifoTriLevel aTriLevel, TUint aPortBase);
	IMPORT_C static void SetUartModemOutLines(TUint8 aClear, TUint8 aSet,TUint aPortBase);
	IMPORT_C static TUint UartIIR(TUint aPortBase);
    IMPORT_C static TUint UartLSR(TUint aPortBase);
    IMPORT_C static TUint UartMSR(TUint aPortBase);
	IMPORT_C static TBool UartTxFifoEmpty(TUint aPortBase);
	IMPORT_C static TBool UartRxFifoEmpty(TUint aPortBase);
	IMPORT_C static void SetUartInterruptOut(TUartOut2 aOut2, TUint aPortBase);

// Slow Ir Port
	IMPORT_C static void SetSirEnable(TSirXmitPolarity aPolarity, TSirPowerMode aPower, TUint aPortBase);
	IMPORT_C static void SetSirXmitEnable(TSirXmitEnable aXmit, TUint aPortBase);
// Fast Ir Port (Icp)
	IMPORT_C static void  SetIcpData(TUint aValue);
	IMPORT_C static TUint IcpData();
	IMPORT_C static void  SetIcpEnable(TIcpEnable aIcp, TIcpXmitEnable anEnable,TIcpFifoInt aFifoInt,
											 TIcpLoopback aLoopback,TIcpUnderrunBehaviour aBehaviour);
	IMPORT_C static void    SetIcpAddrMatch(TUint8 anIrdaPortNo);
	IMPORT_C static TUint8  IcpAddrMatch();
	IMPORT_C static void SetIcpPinPolarity(TIcpPinPolarity aPolarity);
	IMPORT_C static TIcpPinPolarity IcpPinPolarity();
	IMPORT_C static void SetIcpTrigLevel(TIcpRxFifoTriLevel aTrigLevel);
	IMPORT_C static TIcpRxFifoTriLevel IcpTrigLevel();
	IMPORT_C static TUint IcpStatus0();
	IMPORT_C static void  IcpClearStatus0(TUint aClearMask);
	IMPORT_C static TUint IcpStatus1();
	IMPORT_C static TBool IcpRxFifoEmpty();
	IMPORT_C static TBool IcpTxFifoFull();	
//	IMPORT_C static void  SetHsspAbort(TUartBreak aBreak,TUint aPortBase);

// Synchronous Serial Port (SSP)
	IMPORT_C static void SetSspConfig(TSspDataSize aSize,TSspFrameFormat aFormat,TInt aClockRate);
	IMPORT_C static void SetSspEnable(TSspEnable anEnable);
	IMPORT_C static void ModifySspIntMasks(TSspRxFifoInt anRFI,TSspTxFifoInt anTFI,TSspLoopBack anLbMode);
	IMPORT_C static void SetSspSerialClockConfig(TPolarity aPolarity,TSspSerClkPhase aPhase,TSspExtClockSel aSel);
	IMPORT_C static void SetSspData(TUint aValue);
	IMPORT_C static TUint SspData();
	IMPORT_C static TUint SspStatus();
	IMPORT_C static void SspClearStatus(TUint aClearMask);
// Interrupts 
	IMPORT_C static TUint IntLevels();
	IMPORT_C static void SetIntLevels(TUint aValue);
	IMPORT_C static void ModifyIntLevels(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint IntMask();
	IMPORT_C static void SetIntMask(TUint aValue);
	IMPORT_C static void ModifyIntMask(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint IntsPending();
	IMPORT_C static TUint IrqsPending();
	IMPORT_C static TUint FiqsPending();
// General-purpose I/O 
	IMPORT_C static TUint Port(TGpioBank aSet);
	IMPORT_C static void SetPort(TGpioBank aSet, TUint aSetMask);
	IMPORT_C static void ClearPort(TGpioBank aSet, TUint aClearMask);
	IMPORT_C static void ModifyPort(TGpioBank aSet, TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint Ddr(TGpioBank aSet);
	IMPORT_C static void SetDdr(TGpioBank aSet,TUint aValue);
	IMPORT_C static void ModifyDdr(TGpioBank aSet,TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortRisingEdgeDetect(TGpioBank aSet);
	IMPORT_C static void SetPortRisingEdgeDetect(TGpioBank aSet,TUint aValue);
	IMPORT_C static void ModifyPortRisingEdgeDetect(TGpioBank aSet,TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortFallingEdgeDetect(TGpioBank aSet);
	IMPORT_C static void SetPortFallingEdgeDetect(TGpioBank aSet, TUint aValue);
	IMPORT_C static void ModifyPortFallingEdgeDetect(TGpioBank aSet,TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortEdgeDetected(TGpioBank aSet);
	IMPORT_C static void ClearPortEdgeDetected(TGpioBank aSet,TUint aClearMask);
	IMPORT_C static TUint PortAlternatives(TGpioHalfBank aSet);
	IMPORT_C static void SetPortAlternatives(TGpioHalfBank aSet, TUint aValue);
	IMPORT_C static void ModifyPortAlternatives(TGpioHalfBank aSet, TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortSleepData(TGpioBank aSet);
	IMPORT_C static void SetPortSleepData(TGpioBank aSet,TUint aValue);
	IMPORT_C static void ModifyPortSleepData(TGpioBank aSet,TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint TCotulla::CClkCfg();
	IMPORT_C void TCotulla::SetCClkCfg(TUint);
	IMPORT_C static TUint TCotulla::MemoryClockInKHz();
	IMPORT_C static TUint TCotulla::MemoryPeriodInPs();

// USB Client Controller (UDC)
	IMPORT_C static void Udc(TInt aEndpoint);

// AC'97 Controller
	IMPORT_C static TUint InitACLink(void);
	IMPORT_C static void  ReInitACLink(void);
	IMPORT_C static TUint ReadACLink(volatile TUint aAddr, volatile TUint *aData);
	IMPORT_C static TUint WriteACLink(volatile TUint aAddr, volatile TUint aData);
	IMPORT_C static void  SetIsTxDmaStarted(void);
	IMPORT_C static TBool GetIsTxDmaStarted(void);
	IMPORT_C static void  ClearIsTxDmaStarted(void);
	IMPORT_C static void  SetIsRxDmaStarted(void);
	IMPORT_C static TBool GetIsRxDmaStarted(void);
	IMPORT_C static void  ClearIsRxDmaStarted(void);
	IMPORT_C static TInt  GetNumOfDmaPageQueries(void);
	IMPORT_C static void  SetNumOfDmaPageQueries(void);
	IMPORT_C static void  LockACLink(void);
	IMPORT_C static void  UnLockACLink(void);
	IMPORT_C static TUint ActualACLinkRead(volatile TUint aAddr, volatile TUint *aData);
	IMPORT_C static TUint ActualACLinkWrite(volatile TUint aAddr, volatile TUint aData);


// MMC Controller
    IMPORT_C static void EnableMMCClock(void);
	IMPORT_C static void DisableMMCClock(void);

	//
	// Miscellaneous stuff
	//
	IMPORT_C static void EnterIdle();
	IMPORT_C static void Sleep();
	IMPORT_C static void ResetWatchdog();
	IMPORT_C static TUint AsspStepping();

	static inline TUint32 Register32(TUint32 aAddr)
		{return *reinterpret_cast<const volatile TUint32*>(aAddr);}
	static inline void SetRegister32(TUint aValue, TUint32 aAddr)
		{*reinterpret_cast<volatile TUint32*>(aAddr) = aValue;}
	IMPORT_C static void ModifyRegister32(TUint32 aClearMask, TUint32 aSetMask, TUint32 aAddr);
	static inline TUint8 Register8(TUint32 aAddr)
		{return *reinterpret_cast<const volatile TUint8*>(aAddr);}
	static inline void SetRegister8(TUint8 aValue, TUint32 aAddr)
		{*reinterpret_cast<volatile TUint8*>(aAddr) = aValue;}
	IMPORT_C static void ModifyRegister8(TUint8 aClearMask, TUint8 aSetMask, TUint32 aAddr);

    /**
	 * Public variables
	 */
public:
	static volatile TUint LastRtcValue;
	static volatile TUint RtcFraction;

	/**
	 * Some private constants
	 */

private:
	static TUint GPIOfollower_x;
	static TUint GPIOfollower_y;
	static TUint GPIOfollower_z;
//	static TUint PPCfollower;	//No PPC in Cotulla		

	};

/*
 * Return base address of debug UART (as selected in obey file or with
 * eshell debugport command).
 */
inline TUint32 TCotulla::DebugPortAddr()
	{
	// Default to BTUART
	return (TheSuperPage().iDebugPort == 1) ? KHwBaseFfUart : KHwBaseBtUart ;
	}

#endif

// r8-r14 saved in FIQ and IRQ	modes
// need to find the Linear to Physical mapping of the stack pointer
