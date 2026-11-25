// A32SA1100.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

//
// Definitions for SA1100
// Derived from SA1100.I assembler file
//


#ifndef __A32SA1100_H__
#define __A32SA1100_H__
#include <e32std.h>
#include <k32std.h>

//
// SA1100 Interrupt names
//
_LIT8(KIrqGpioEdge0, "IrqGpioEdge0");
_LIT8(KIrqGpioEdge1, "IrqGpioEdge1");
_LIT8(KIrqGpioEdge2, "IrqGpioEdge2");
_LIT8(KIrqGpioEdge3, "IrqGpioEdge3");
_LIT8(KIrqGpioEdge4, "IrqGpioEdge4");
_LIT8(KIrqGpioEdge5, "IrqGpioEdge5");
_LIT8(KIrqGpioEdge6, "IrqGpioEdge6");
_LIT8(KIrqGpioEdge7, "IrqGpioEdge7");
_LIT8(KIrqGpioEdge8, "IrqGpioEdge8");
_LIT8(KIrqGpioEdge9, "IrqGpioEdge9");
_LIT8(KIrqGpioEdge10, "IrqGpioEdge10");
_LIT8(KIrqGpioEdge11_27, "IrqGpioEdge11_27");
_LIT8(KIrqLcd, "IrqLcd");
_LIT8(KIrqSerial0Udc, "IrqSerial0Udc");
_LIT8(KIrqSerial1Sdlc, "IrqSerial1Sdlc");
_LIT8(KIrqSerial1Uart, "IrqSerial1Uart");
_LIT8(KIrqSerial2Hssp, "IrqSerial2Hssp");
_LIT8(KIrqSerial3Uart, "IrqSerial3Uart");
_LIT8(KIrqSerial4Mcp, "IrqSerial4Mcp");
_LIT8(KIrqSerial4Ssp, "IrqSerial4Ssp");
_LIT8(KIrqDmaChannel0, "IrqDmaChannel0");
_LIT8(KIrqDmaChannel1, "IrqDmaChannel1");
_LIT8(KIrqDmaChannel2, "IrqDmaChannel2");
_LIT8(KIrqDmaChannel3, "IrqDmaChannel3");
_LIT8(KIrqDmaChannel4, "IrqDmaChannel4");
_LIT8(KIrqDmaChannel5, "IrqDmaChannel5");
_LIT8(KIrqOstMatch0, "IrqOstMatch0");		//Ost0=OS timer
_LIT8(KIrqOstMatch1, "IrqOstMatch1");		//Ost1=64Hz tick timer
_LIT8(KIrqOstMatch2, "IrqOstMatch2");		//Ost2=Ms timer.
_LIT8(KIrqOstMatch3, "IrqOstMatch3");		//OS timer match 3
_LIT8(KIrqRtcTick, "IrqRtcTick");
_LIT8(KIrqRtcAlarm, "IrqRtcAlarm");
_LIT8(KIrqGpioEdge11, "IrqGpioEdge11");		// conceptual interrupts
_LIT8(KIrqGpioEdge12, "IrqGpioEdge12");
_LIT8(KIrqGpioEdge13, "IrqGpioEdge13");
_LIT8(KIrqGpioEdge14, "IrqGpioEdge14");
_LIT8(KIrqGpioEdge15, "IrqGpioEdge15");
_LIT8(KIrqGpioEdge16, "IrqGpioEdge16");
_LIT8(KIrqGpioEdge17, "IrqGpioEdge17");
_LIT8(KIrqGpioEdge18, "IrqGpioEdge18");
_LIT8(KIrqGpioEdge19, "IrqGpioEdge19");
_LIT8(KIrqGpioEdge20, "IrqGpioEdge20");
_LIT8(KIrqGpioEdge21, "IrqGpioEdge21");
_LIT8(KIrqGpioEdge22, "IrqGpioEdge22");
_LIT8(KIrqGpioEdge23, "IrqGpioEdge23");
_LIT8(KIrqGpioEdge24, "IrqGpioEdge24");
_LIT8(KIrqGpioEdge25, "IrqGpioEdge25");
_LIT8(KIrqGpioEdge26, "IrqGpioEdge26");
_LIT8(KIrqGpioEdge27, "IrqGpioEdge27");
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


//----------------------------------------------------------------------------

// Page numbers from 8/5/97 data sheet (v2.1) unless otherwise stated

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
// Memory map (page 22): these are physical addresses
//----------------------------------------------------------------------------

const TUint KHwBaseStatic0		=	0x00000000;
const TUint KHwBaseStatic1		=	KHwBaseStatic0 + 128*KMega;
const TUint KHwBaseStatic2		=	KHwBaseStatic1 + 128*KMega;
const TUint KHwBaseStatic3		=	KHwBaseStatic2 + 128*KMega;

const TUint KHwBasePcmcia0		=	0x20000000;
const TUint KHwBasePcmcia1		=	KHwBasePcmcia0 + 256*KMega;

const TUint KHwBaseRegisters	=	0x80000000;
const TUint KHwBasePeripherals	=	KHwBaseRegisters;				// 8000.0000
const TUint KHwBaseSysControl	=	KHwBasePeripherals + 256*KMega;	// 9000.0000
const TUint KHwBaseMemAndExp	=	KHwBaseSysControl + 256*KMega;	// A000.0000
const TUint KHwBaseLcdAndDma	=	KHwBaseMemAndExp + 256*KMega;	// B000.0000

const TUint KHwBaseDram0		=	0xC0000000;
const TUint KHwBaseDram1		=	KHwBaseDram0 + 128*KMega;
const TUint KHwBaseDram2		=	KHwBaseDram1 + 128*KMega;
const TUint KHwBaseDram3		=	KHwBaseDram2 + 128*KMega;
const TUint KHwBaseZeros		=	KHwBaseDram3 + 128*KMega;

//----------------------------------------------------------------------------
// Memory map: linear addresses
//----------------------------------------------------------------------------

const TUint KHwLinBaseVideo		=	0x30000000;
const TUint KHwLinBaseRam		=	0x40000000;
const TUint KHwLinBaseRom		=	0x50000000;
const TUint KHwLinBaseRegisters	=	0x58000000;
const TUint KHwLinBaseRegSpacing=	0x1000;		// MMU small page size

// UDC		Physical base = 8000.0000
const TUint KHwBaseSerial0		=	KHwLinBaseRegisters + 0x00*KHwLinBaseRegSpacing;
// UART1	Physical base = 8001.0000
const TUint KHwBaseSerial1Uart	=	KHwLinBaseRegisters + 0x01*KHwLinBaseRegSpacing;
// SDLC		Physical base = 8002.0000
const TUint KHwBaseSerial1Sdlc	=	KHwLinBaseRegisters + 0x02*KHwLinBaseRegSpacing;
// UART2	Physical base = 8003.0000
const TUint KHwBaseSerial2Uart	=	KHwLinBaseRegisters + 0x03*KHwLinBaseRegSpacing;
// HSSP		Physical base = 8004.0000
const TUint KHwBaseSerial2Hssp	=	KHwLinBaseRegisters + 0x04*KHwLinBaseRegSpacing;
// UART3	Physical base = 8005.0000
const TUint KHwBaseSerial3		=	KHwLinBaseRegisters + 0x05*KHwLinBaseRegSpacing;
// MCP		Physical base = 8006.0000
const TUint KHwBaseSerial4Mcp	=	KHwLinBaseRegisters + 0x06*KHwLinBaseRegSpacing;
// SSP		Physical base = 8007.0000
const TUint KHwBaseSerial4Ssp	=	KHwLinBaseRegisters + 0x07*KHwLinBaseRegSpacing;
// OST		Physical base = 9000.0000
const TUint KHwBaseOst			=	KHwLinBaseRegisters + 0x08*KHwLinBaseRegSpacing;
// RTC		Physical base = 9001.0000
const TUint KHwBaseRtc			=	KHwLinBaseRegisters + 0x09*KHwLinBaseRegSpacing;
// PWR		Physical base = 9002.0000
const TUint KHwBasePwr			=	KHwLinBaseRegisters + 0x0a*KHwLinBaseRegSpacing;
// RSTC		Physical base = 9003.0000
const TUint KHwBaseReset		=	KHwLinBaseRegisters + 0x0b*KHwLinBaseRegSpacing;
// GPIO		Physical base = 9004.0000
const TUint KHwBaseGpio			=	KHwLinBaseRegisters + 0x0c*KHwLinBaseRegSpacing;
// INT		Physical base = 9005.0000
const TUint KHwBaseInts			=	KHwLinBaseRegisters + 0x0d*KHwLinBaseRegSpacing;
// PPC		Physical base = 9006.0000
const TUint KHwBasePpc			=	KHwLinBaseRegisters + 0x0e*KHwLinBaseRegSpacing;
// MEM		Physical base = A000.0000
const TUint KHwBaseMexp			=	KHwLinBaseRegisters + 0x0f*KHwLinBaseRegSpacing;
// DMA		Physical base = B000.0000
const TUint KHwBaseDma			=	KHwLinBaseRegisters + 0x10*KHwLinBaseRegSpacing;
// LCD		Physical base = B010.0000
//const TUint KHwBaseLcd			=	KHwLinBaseRegisters + 0x11*KHwLinBaseRegSpacing;
const TUint KHwBaseLcd			=	KHwLinBaseRegisters + 0x20000;

// Magic Gone into standby value.
const TUint KHwMagicEnterStandbyValue=0xBeADead1;

//dma addrs and channel layout
const TUint32 KBrutusDmaBaseAddr     = 0xb0000000;
const TUint8  KBrutusDmaChannelSize  = 0x20;
const TUint8  KBrutusDmaSetDscReg    = 0x04;
const TUint8  KBrutusDmaClearDscReg  = 0x08;
const TUint8  KBrutusDmaReadDscReg   = 0x0C;
const TUint8  KBrutusDmaBufAStartReg = 0x10;
const TUint8  KBrutusDmaBufACountReg = 0x14;
const TUint8  KBrutusDmaBufBStartReg = 0x18;
const TUint8  KBrutusDmaBufBCountReg = 0x1C;

//peripherals - compressed DMA 24bit addresses (as masks)
const TUint32 KDmaTxUDCCompAddr	  =0x80000A00;
const TUint32 KDmaTxSDLCCompAddr  =0x80801E00;
const TUint32 KDmaTxUART1CompAddr =0x80400500;
const TUint32 KDmaTxSIRCompAddr   =0x80C00500;		//?this is 28 bit
const TUint32 KDmaTxFIRCompAddr   =0x81001B00;
const TUint32 KDmaTxUART3CompAddr =0x81400500;

const TUint32 KDmaRxUDCCompAddr	  =0x80000A00;
const TUint32 KDmaRxSDLCCompAddr  =0x80801E00;
const TUint32 KDmaRxUART1CompAddr =0x80400500;
const TUint32 KDmaRxSIRCompAddr   =0x80C00500;		//?this is 28 bit
const TUint32 KDmaRxFIRCompAddr   =0x81001B00;
const TUint32 KDmaRxUART3CompAddr =0x81400500;

//peripherals - device DMA 4 bit selectors(as masks)
const TUint8 KDmaTxUDCSel   =0x00;
const TUint8 KDmaTxSDLCSel  =0x20;
const TUint8 KDmaTxUART1Sel =0x40;
const TUint8 KDmaTxSIRSel   =0x60;
const TUint8 KDmaTxFIRSel   =0x60;
const TUint8 KDmaTxUART3Sel =0x80;

const TUint8 KDmaRxUDCSel   =0x10;
const TUint8 KDmaRxSDLCSel  =0x30;
const TUint8 KDmaRxUART1Sel =0x50;
const TUint8 KDmaRxSIRSel   =0x70;
const TUint8 KDmaRxFIRSel   =0x70;
const TUint8 KDmaRxUART3Sel =0x90;

//DMA DAR Register masks
const TUint8 KReadMask          =0x1;
const TUint8 KBigEndianMask     =0x2;
const TUint8 KMaxBurstMask      =0x4;
const TUint8 KMaxDatumMask      =0x8;
const TUint8 KChannelSelectMask =0xF0;
const TUint32 KChannelAddrMask  =0xFFFFFF00;

//DCSR register masks
const TUint32 KDmaRunMask       =0x1;
const TUint32 KDmaIntEnableMask =0x2;
const TUint32 KDmaErrMask       =0x4;		//status only
const TUint32 KDmaDoneAMask     =0x8;		//status only
const TUint32 KDmaStartAMask    =0x10;
const TUint32 KDmaDoneBMask     =0x20;	//status only
const TUint32 KDmaStartBMask    =0x40;
const TUint32 KDmaBufInUseMask  =0x80;	//status only
//----------------------------------------------------------------------------
// On-board modules
//----------------------------------------------------------------------------
// O/S timer (pages 75-78)
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

//----------------------------------------------------------------------------
// Real-time clock (pages 70-74)
const TUint KHwRwRtcRtar		=	KHwBaseRtc + 0x00;
const TUint KHwRwRtcRcnr		=	KHwBaseRtc + 0x04;
const TUint KHwRwRtcRttr		=	KHwBaseRtc + 0x08;
const TUint KHwRwRtcRtsr		=	KHwBaseRtc + 0x10;

// Trim
const TUint KHsRtcRttrTrimdel	=	16;
const TUint KHmRtcRttrTrimdel	=	0x000003ff<<KHsRtcRttrTrimdel;
const TUint KHsRtcRttrClkdiv	=	0;
const TUint KHmRtcRttrClkdiv	=	0x0000ffff<<KHsRtcRttrClkdiv;

// Status
const TUint KHtRtcRtsrHze		=	KBit3;
const TUint KHtRtcRtsrAle		=	KBit2;
const TUint KHtRtcRtsrHz		=	KBit1;
const TUint KHtRtcRtsrAl		=	KBit0;

//----------------------------------------------------------------------------
// Power management (pages 79-92)
const TUint KHwRwPwrPmcr		=	KHwBasePwr + 0x00;
const TUint KHwRwPwrPssr		=	KHwBasePwr + 0x04;
const TUint KHwRwPwrPspr		=	KHwBasePwr + 0x08;
const TUint KHwRwPwrPwer		=	KHwBasePwr + 0x0c;
const TUint KHwRwPwrPcfr		=	KHwBasePwr + 0x10;
const TUint KHwRwPwrPpcr		=	KHwBasePwr + 0x14;
const TUint KHwRwPwrPgsr		=	KHwBasePwr + 0x18;
const TUint KHwRwPwrPosr		=	KHwBasePwr + 0x1c;

// Control
const TUint KHtPwrPmcrSf		=	KBit0;

// Configuration
const TUint KHtPwrPcfrFo		=	KBit3;
const TUint KHtPwrPcfrFs		=	KBit2;
const TUint KHtPwrPcfrFp		=	KBit1;
const TUint KHtPwrPcfrOpde		=	KBit0;

// PLL configuration
const TUint KHsPwrPpcrCcf		=	0;
const TUint KHmPwrPpcrCcf		=	0x0000001f<<KHsPwrPpcrCcf;

const TUint KHwOscFreqHz		=	3686400;	// 3.6864MHz

// Wakeup enable
const TUint KHtPwrPwerRtcAlarm	=	KBit31;
const TUint KHsPwrPwerValid		=	0;
const TUint KHmPwrPwerValid		=	0x8fffffff<<KHsPwrPwerValid;

// Sleep status
const TUint KHtPwrPssrPh		=	KBit4;
const TUint KHtPwrPssrDh		=	KBit3;
const TUint KHtPwrPssrVfs		=	KBit2;
const TUint KHtPwrPssrBfs		=	KBit1;
const TUint KHtPwrPssrSs		=	KBit0;

const TUint KHmPwrPssrReason	=	KHtPwrPssrVfs|KHtPwrPssrBfs|KHtPwrPssrSs;

// GPIO sleep state
const TUint KHmPwrPgsrValid		=	0x0fffffff;

// Oscillator status
const TUint KHtPwrPosrOok		=	KBit0;

//----------------------------------------------------------------------------
// Reset control (pages 93-95)
const TUint KHwWoResetRsrr		=	KHwBaseReset + 0x00;
const TUint KHwRwResetRcsr		=	KHwBaseReset + 0x04;

// Soft reset
const TUint KHtResetRsrrSwr		=	KBit0;

// Status
const TUint KHtResetRcsrSmr		=	KBit3;
const TUint KHtResetRcsrWdr		=	KBit2;
const TUint KHtResetRcsrSwr		=	KBit1;
const TUint KHtResetRcsrHwr		=	KBit0;

//----------------------------------------------------------------------------
// General-purpose I/O (pages 54-63)
const TUint KHwRoGpioGplr		=	KHwBaseGpio + 0x00;
const TUint KHwRwGpioGpdr		=	KHwBaseGpio + 0x04;
const TUint KHwWoGpioGpsr		=	KHwBaseGpio + 0x08;
const TUint KHwWoGpioGpcr		=	KHwBaseGpio + 0x0c;
const TUint KHwRwGpioGrer		=	KHwBaseGpio + 0x10;
const TUint KHwRwGpioGfer		=	KHwBaseGpio + 0x14;
const TUint KHwRwGpioGedr		=	KHwBaseGpio + 0x18;
const TUint KHwRwGpioGafr		=	KHwBaseGpio + 0x1c;

// Valid I/O mask
const TUint KHmGpioPortValid	=	0x0fffffff;

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

// Alternate GPIO pin functions
const TUint KHtGpioAlt32KHz_o		=	KHtGpioPort27;
const TUint KHtGpioAltRclk_o		=	KHtGpioPort26;
const TUint KHtGpioAltRtc_o			=	KHtGpioPort25;
const TUint KHtGpioAltTreqb_i		=	KHtGpioPort23;
const TUint KHtGpioAltTreqa_i		=	KHtGpioPort22;
const TUint KHtGpioAltMbreq_i		=	KHtGpioPort22;
const TUint KHtGpioAltTicack_o		=	KHtGpioPort21;
const TUint KHtGpioAltMbgnt_o		=	KHtGpioPort21;
const TUint KHtGpioAltMcpclk_i		=	KHtGpioPort21;
const TUint KHtGpioAltUartsclk3_i	=	KHtGpioPort20;
const TUint KHtGpioAltSspclk_i		=	KHtGpioPort19;
const TUint KHtGpioAltUartsclk1_i	=	KHtGpioPort18;
const TUint KHtGpioAltSdlcaaf_o		=	KHtGpioPort17;
const TUint KHtGpioAltSdlcsclk_b	=	KHtGpioPort16;
const TUint KHtGpioAltUartrxd_i		=	KHtGpioPort15;
const TUint KHtGpioAltUarttxd_o		=	KHtGpioPort14;
const TUint KHtGpioAltSspsfrm_o		=	KHtGpioPort13;
const TUint KHtGpioAltSspsclk_o		=	KHtGpioPort12;
const TUint KHtGpioAltSsprxd_i		=	KHtGpioPort11;
const TUint KHtGpioAltSsptxd_o		=	KHtGpioPort10;
const TUint KHtGpioAltSsp13_10		=	(KHtGpioPort13|KHtGpioPort12|KHtGpioPort11|KHtGpioPort10);
const TUint KHmGpioAltLdd9_2_o		=	KHtGpioPort9|KHtGpioPort8|KHtGpioPort7|
										KHtGpioPort6|KHtGpioPort5|KHtGpioPort4|
										KHtGpioPort3|KHtGpioPort2;

// Alternate function data direction masks
// nb1: test functions excluded
// nb2: bidirectional SDLC SCLK initialised as output
const TUint KHmGpioAltDdr			=	KHtGpioAlt32KHz_o|
										KHtGpioAltRclk_o|
										KHtGpioAltRtc_o|
										KHtGpioAltSdlcaaf_o|
										KHtGpioAltSdlcsclk_b|
										KHtGpioAltUarttxd_o|
										KHtGpioAltSspsfrm_o|
										KHtGpioAltSspsclk_o|
										KHtGpioAltSsptxd_o|
										KHmGpioAltLdd9_2_o;

//----------------------------------------------------------------------------
// Interrupts (pages 65-70)
const TUint KHwRoIntsIcip		=	KHwBaseInts + 0x00;
const TUint KHwRwIntsIcmr		=	KHwBaseInts + 0x04;
const TUint KHwRwIntsIclr		=	KHwBaseInts + 0x08;
const TUint KHwRwIntsIccr		=	KHwBaseInts + 0x0c;
const TUint KHwRoIntsIcfp		=	KHwBaseInts + 0x10;
const TUint KHwRoIntsIcpr		=	KHwBaseInts + 0x20;

const TUint KHtIntsIccrDim		=	KBit0;

// Interrupt sources
const TUint KHtIntsSrcRtcAlarm		=	KBit31;
const TUint KHtIntsSrcRtcTick		=	KBit30;
const TUint KHtIntsSrcOstMatch3		=	KBit29;
const TUint KHtIntsSrcOstMatch2		=	KBit28;
const TUint KHtIntsSrcOstMatch1		=	KBit27;
const TUint KHtIntsSrcOstMatch0		=	KBit26;
const TUint KHtIntsSrcDmaChannel5	=	KBit25;
const TUint KHtIntsSrcDmaChannel4	=	KBit24;
const TUint KHtIntsSrcDmaChannel3	=	KBit23;
const TUint KHtIntsSrcDmaChannel2	=	KBit22;
const TUint KHtIntsSrcDmaChannel1	=	KBit21;
const TUint KHtIntsSrcDmaChannel0	=	KBit20;
const TUint KHtIntsSrcSerial4Ssp	=	KBit19;
const TUint KHtIntsSrcSerial4Mcp	=	KBit18;
const TUint KHtIntsSrcSerial3Uart	=	KBit17;
const TUint KHtIntsSrcSerial2Hssp	=	KBit16;
const TUint KHtIntsSrcSerial1Uart	=	KBit15;
const TUint KHtIntsSrcSerial1Sdlc	=	KBit14;
const TUint KHtIntsSrcSerial0Udc	=	KBit13;
const TUint KHtIntsSrcLcd			=	KBit12;
const TUint KHtIntsSrcGpioEdge27_11	=	KBit11;
const TUint KHtIntsSrcGpioEdge10	=	KBit10;
const TUint KHtIntsSrcGpioEdge9		=	KBit9;
const TUint KHtIntsSrcGpioEdge8		=	KBit8;
const TUint KHtIntsSrcGpioEdge7		=	KBit7;
const TUint KHtIntsSrcGpioEdge6		=	KBit6;
const TUint KHtIntsSrcGpioEdge5		=	KBit5;
const TUint KHtIntsSrcGpioEdge4		=	KBit4;
const TUint KHtIntsSrcGpioEdge3		=	KBit3;
const TUint KHtIntsSrcGpioEdge2		=	KBit2;
const TUint KHtIntsSrcGpioEdge1		=	KBit1;
const TUint KHtIntsSrcGpioEdge0		=	KBit0;

//----------------------------------------------------------------------------
// Peripheral pin controller (pages 292-302)
const TUint KHwRwPpcPpdr		=	KHwBasePpc + 0x00;
const TUint KHwRwPpcPpsr		=	KHwBasePpc + 0x04;
const TUint KHwRwPpcPpar		=	KHwBasePpc + 0x08;
const TUint KHwRwPpcPsdr		=	KHwBasePpc + 0x0c;
const TUint KHwRoPpcPpfr		=	KHwBasePpc + 0x10;

// Peripheral pin mapping
const TUint KHtPpcPinSfrm		=	KBit21;
const TUint KHtPpcPinSclk		=	KBit20;
const TUint KHtPpcPinRxd4		=	KBit19;
const TUint KHtPpcPinTxd4		=	KBit18;
const TUint KHtPpcPinRxd3		=	KBit17;
const TUint KHtPpcPinTxd3		=	KBit16;
const TUint KHtPpcPinRxd2		=	KBit15;
const TUint KHtPpcPinTxd2		=	KBit14;
const TUint KHtPpcPinRxd1		=	KBit13;
const TUint KHtPpcPinTxd1		=	KBit12;
const TUint KHtPpcPinLbias		=	KBit11;
const TUint KHtPpcPinLfclk		=	KBit10;
const TUint KHtPpcPinLlclk		=	KBit9;
const TUint KHtPpcPinLpclk		=	KBit8;
const TUint KHsPpcPinLdd		=	0;
const TUint KHmPpcPinLdd		=	0x000000ff<<KHsPpcPinLdd;

// Assignment register
const TUint KHwPpcPparSpr		=	KBit18;
const TUint KHwPpcPparUpr		=	KBit12;

// Pin flag register
const TUint KHwPpcPpfrSp4		=	KBit18;
const TUint KHwPpcPpfrSp3rx		=	KBit17;
const TUint KHwPpcPpfrSp3tx		=	KBit16;
const TUint KHwPpcPpfrSp2rx		=	KBit15;
const TUint KHwPpcPpfrSp2tx		=	KBit14;
const TUint KHwPpcPpfrSp1rx		=	KBit13;
const TUint KHwPpcPpfrSp1tx		=	KBit12;
const TUint KHwPpcPpfrLcd		=	KBit0;

//----------------------------------------------------------------------------
// Memory/PCMCIA (pages 96-123)
const TUint KHwRwMemMdcnfg		=	KHwBaseMexp + 0x00;
const TUint KHwRwMemMdcas0		=	KHwBaseMexp + 0x04;
const TUint KHwRwMemMdcas1		=	KHwBaseMexp + 0x08;
const TUint KHwRwMemMdcas2		=	KHwBaseMexp + 0x0c;
const TUint KHwRwMemMsc0		=	KHwBaseMexp + 0x10;
const TUint KHwRwMemMsc1		=	KHwBaseMexp + 0x14;
const TUint KHwRwMemMecr		=	KHwBaseMexp + 0x18;

// DRAM configuration
const TUint KHsMemMdcnfgDri		=	17;
const TUint KHmMemMdcnfgDri		=	0x00007fff<<KHsMemMdcnfgDri;
const TUint KHsMemMdcnfgTdl		=	15;
const TUint KHmMemMdcnfgTdl		=	0x00000003<<KHsMemMdcnfgTdl;
const TUint KHsMemMdcnfgTrasr	=	11;
const TUint KHmMemMdcnfgTrasr	=	0x0000000f<<KHsMemMdcnfgTrasr;
const TUint KHsMemMdcnfgTrp		=	7;
const TUint KHmMemMdcnfgTrp		=	0x0000000f<<KHsMemMdcnfgTrp;
const TUint KHtMemMdcnfgCdb2	=	KBit6;
const TUint KHsMemMdcnfgDrac	=	4;
const TUint KHmMemMdcnfgDrac	=	0x00000003<<KHsMemMdcnfgDrac;
const TUint KHsMemMdcnfgDe		=	0;
const TUint KHmMemMdcnfgDe		=	0x0000000f<<KHsMemMdcnfgDe;

const TUint KHwRwMemMdcnfgMinRows	=	9;
const TUint KHwRwMemMdcnfgMaxRows	=	12;

// Static memory control (2 per register)
const TUint KHsMemMscRrr		=	13;
const TUint KHmMemMscRrr		=	0x00000007<<KHsMemMscRrr;
const TUint KHsMemMscRdn		=	8;
const TUint KHmMemMscRdn		=	0x0000001f<<KHsMemMscRdn;
const TUint KHsMemMscRdf		=	3;
const TUint KHmMemMscRdf		=	0x0000001f<<KHsMemMscRdf;
const TUint KHtMemMscRbw		=	4;//?
const TUint KHsMemMscRt			=	0;
const TUint KHmMemMscRt			=	0x00000003<<KHsMemMscRt;

// Number of static chip selects
const TUint KHwMemMscMaxCS		=	4;

// Expansion memory configuration (2 per register)
const TUint KHmMemMecrBs		=	0x0000001f;	// Field mask
const TUint KHsMemMecrBsm		=	10;			// Field shifts
const TUint KHsMemMecrBsa		=	5;
const TUint KHsMemMecrBsio		=	0;

const TUint KHsMemMecrOffsetSlot2	=	0x10;
const TUint KHsMemMecrBsmSlot2		=	KHsMemMecrBsm +  KHsMemMecrOffsetSlot2;		
const TUint KHsMemMecrBsaSlot2		=	KHsMemMecrBsa +  KHsMemMecrOffsetSlot2;
const TUint KHsMemMecrBsioSlot2		=	KHsMemMecrBsio+  KHsMemMecrOffsetSlot2;

//----------------------------------------------------------------------------
// Serial 0 (pages 176-188)
const TUint KHwRwUsbDcr			=	KHwBaseSerial0 + 0x00;
const TUint KHwRwUsbDdr			=	KHwBaseSerial0 + 0x08;
const TUint KHwRwUsbDsr			=	KHwBaseSerial0 + 0x10;

//----------------------------------------------------------------------------
// Serial 1 (pages 190-212)
const TUint KHwRwSdlcSdcr0		=	KHwBaseSerial1Sdlc + 0x60;
const TUint KHwRwSdlcSdcr1		=	KHwBaseSerial1Sdlc + 0x64;
const TUint KHwRwSdlcSdcr2		=	KHwBaseSerial1Sdlc + 0x68;
const TUint KHwRwSdlcSdcr3		=	KHwBaseSerial1Sdlc + 0x6c;
const TUint KHwRwSdlcSdcr4		=	KHwBaseSerial1Sdlc + 0x70;
const TUint KHwRwSdlcSddr		=	KHwBaseSerial1Sdlc + 0x78;
const TUint KHwRwSdlcSdsr0		=	KHwBaseSerial1Sdlc + 0x80;
const TUint KHwRwSdlcSdsr1		=	KHwBaseSerial1Sdlc + 0x84;

//----------------------------------------------------------------------------
// Serial 2 (pages 214-234)
const TUint KHoRwHpsirUtcr4		=	0x10;//SIR uart has 5 control regs
const TUint KHwRwHsspHscr0		=	KHwBaseSerial2Hssp + 0x60;
const TUint KHwRwHsspHscr1		=	KHwBaseSerial2Hssp + 0x64;
const TUint KHwRwHsspHsdr		=	KHwBaseSerial2Hssp + 0x6c;
const TUint KHwRwHsspHssr0		=	KHwBaseSerial2Hssp + 0x74;
const TUint KHwRoHsspHssr1		=	KHwBaseSerial2Hssp + 0x78;
const TUint KHwRwHsspHscr2		=	KHwBasePpc + 0x28;//Within same address as ppc

// Control reg 0
const TUint KHtHsspHscr0Itr     =   KBit0;
const TUint KHtHsspHscr0Lbm     =   KBit1;
const TUint KHtHsspHscr0Tus     =   KBit2;
const TUint KHtHsspHscr0Txe     =   KBit3;
const TUint KHtHsspHscr0Rxe     =   KBit4;
const TUint KHtHsspHscr0Rie     =   KBit5;
const TUint KHtHsspHscr0Tie     =   KBit6;
const TUint KHtHsspHscr0Ame     =   KBit7;

//Control reg 2
const TUint KHtHsspHscr2Txp     =   KBit18;
const TUint KHtHsspHscr2Rxp     =   KBit19;

//Status reg 0
const TUint KHtHsspHssr0Eif     =   KBit0;
const TUint KHtHsspHssr0Tur     =   KBit1;
const TUint KHtHsspHssr0Rab     =   KBit2;
const TUint KHtHsspHssr0Tfs     =   KBit3;
const TUint KHtHsspHssr0Rfs     =   KBit4;
const TUint KHtHsspHssr0Fre     =   KBit5;

//Status reg 1
const TUint KHtHsspHssr1Rsy     =   KBit0;
const TUint KHtHsspHssr1Tby     =   KBit1;
const TUint KHtHsspHssr1Rne     =   KBit2;
const TUint KHtHsspHssr1Tnf     =   KBit3;
const TUint KHtHsspHssr1Eof     =   KBit4;
const TUint KHtHsspHssr1Cre     =   KBit5;
const TUint KHtHsspHssr1Ror     =   KBit6;

//----------------------------------------------------------------------------
// Serial 3 (pages 236-252)
// N.B. the following constants are offsets so that they can also be applied
// toother UARTs
const TUint KHoRwUartUtcr0		=	0x00;
const TUint KHoRwUartUtcr1		=	0x04;
const TUint KHoRwUartUtcr2		=	0x08;
const TUint KHoRwUartUtcr3		=	0x0c;
const TUint KHoRwUartUtdr		=	0x14;
const TUint KHoRwUartUtsr0		=	0x1c;
const TUint KHoRoUartUtsr1		=	0x20;

// General UART access: Serial 3 and Serial 1 when configured as UART
// Control reg 0
const TUint KHtUartUtcr0Tce		=	KBit6;
const TUint KHtUartUtcr0Rce		=	KBit5;
const TUint KHtUartUtcr0Sce		=	KBit4;
const TUint KHtUartUtcr0Dss		=	KBit3;
const TUint KHtUartUtcr0Sbs		=	KBit2;
const TUint KHtUartUtcr0Oes		=	KBit1;
const TUint KHtUartUtcr0Pe		=	KBit0;

const TUint KHmUartDataFormat	=	KHtUartUtcr0Pe|KHtUartUtcr0Oes|KHtUartUtcr0Sbs|KHtUartUtcr0Dss;
const TUint KHmUartExtClk		=	KHtUartUtcr0Sce|KHtUartUtcr0Tce|KHtUartUtcr0Rce;

// Control reg 1
const TUint KHsUartUtcr1Brdhi	=	0;
const TUint KHmUartUtcr1Brdhi	=	0x0000000f<<KHsUartUtcr1Brdhi;

// Control reg 2
const TUint KHsUartUtcr2Brdlo	=	0;
const TUint KHmUartUtcr2Brdlo	=	0x000000ff<<KHsUartUtcr2Brdlo;

// Control reg 3
const TUint KHtUartUtcr3Lbm		=	KBit5;
const TUint KHtUartUtcr3Tim		=	KBit4;
const TUint KHtUartUtcr3Rim		=	KBit3;
const TUint KHtUartUtcr3Brk		=	KBit2;
const TUint KHtUartUtcr3Txe		=	KBit1;
const TUint KHtUartUtcr3Rxe		=	KBit0;

// Data reg
const TUint KHtUartUtdrPre		=	KBit10;
const TUint KHtUartUtdrFre		=	KBit9;
const TUint KHtUartUtdrRor		=	KBit8;
const TUint KHsUartUtdrData		=	0;
const TUint KHmUartUtdrData		=	0x000000ff<<KHsUartUtdrData;

// Status 0
const TUint KHtUartUtsr0Eif		=	KBit5;
const TUint KHtUartUtsr0Reb		=	KBit4;
const TUint KHtUartUtsr0Rbb		=	KBit3;
const TUint KHtUartUtsr0Rid		=	KBit2;
const TUint KHtUartUtsr0Rfs		=	KBit1;
const TUint KHtUartUtsr0Tfs		=	KBit0;

const TUint KHmUartUtsr0Sticky	=	KHtUartUtsr0Rid+KHtUartUtsr0Rbb+KHtUartUtsr0Reb;

// Status 1
const TUint KHtUartUtsr1Ror		=	KBit5;
const TUint KHtUartUtsr1Fre		=	KBit4;
const TUint KHtUartUtsr1Pre		=	KBit3;
const TUint KHtUartUtsr1Tnf		=	KBit2;
const TUint KHtUartUtsr1Rne		=	KBit1;
const TUint KHtUartUtsr1Tby		=	KBit0;

// Generator for baud rate divisor
#define _UART_BRD(rate)	(3686400 / (16 * rate) - 1)

//----------------------------------------------------------------------------
// Serial 4 (pages 254-287)
const TUint KHwRwMcpMccr0		=	KHwBaseSerial4Mcp + 0x00;
const TUint KHwRwMcpMcdr0		=	KHwBaseSerial4Mcp + 0x08;
const TUint KHwRwMcpMcdr1		=	KHwBaseSerial4Mcp + 0x0c;
const TUint KHwRwMcpMcdr2		=	KHwBaseSerial4Mcp + 0x10;
const TUint KHwRwMcpMcsr		=	KHwBaseSerial4Mcp + 0x18;
const TUint KHwRwMcpMccr1		=	KHwBasePpc + 0x30;//Within same address as ppc

const TUint KHwRwSspSscr0		=	KHwBaseSerial4Ssp + 0x60;
const TUint KHwRwSspSscr1		=	KHwBaseSerial4Ssp + 0x64;
const TUint KHwRwSspSsdr		=	KHwBaseSerial4Ssp + 0x6c;
const TUint KHwRwSspSssr		=	KHwBaseSerial4Ssp + 0x74;

// MCCR0
const TUint KHsMcpMccr0Asd		=	0;
const TUint KHmMcpMccr0Asd		=	0x0000007f<<KHsMcpMccr0Asd;
const TUint KHsMcpMccr0Tsd		=	8;
const TUint KHmMcpMccr0Tsd		=	0x0000007f<<KHsMcpMccr0Tsd;
const TUint KHtMcpMccr0Mce		=	KBit16;
const TUint KHtMcpMccr0Ecs		=	KBit17;
const TUint KHtMcpMccr0Adm		=	KBit18;
const TUint KHtMcpMccr0Tte		=	KBit19;
const TUint KHtMcpMccr0Tre		=	KBit20;
const TUint KHtMcpMccr0Ate		=	KBit21;
const TUint KHtMcpMccr0Are		=	KBit22;
const TUint KHtMcpMccr0Lbm		=	KBit23;
const TUint KHsMcpMccr0Ecp		=	24;
const TUint KHmMcpMccr0Ecp		=	0x00000003<<KHsMcpMccr0Ecp;
const TUint KHtMcpMccr0Ecp0		=	KBit24;
const TUint KHtMcpMccr0Ecp1		=	KBit25;

const TUint KHmMcpMccr0Sticky	=	KHmMcpMccr0Asd|KHmMcpMccr0Tsd|KHtMcpMccr0Mce|
									KHtMcpMccr0Ecs|KHtMcpMccr0Adm|KHtMcpMccr0Tte|
									KHtMcpMccr0Tre|KHtMcpMccr0Ate|KHtMcpMccr0Are|
									KHtMcpMccr0Lbm|KHmMcpMccr0Ecp;


// MCCR1
const TUint KHtMcpMccr1Cfs		=	KBit20;

// MCDR2
const TUint KHsMcpMcdr2Data		=	0;
const TUint KHmMcpMcdr2Data		=	0x0000ffff<<KHsMcpMcdr2Data;
const TUint KHtMcpMcdr2Rw		=	KBit16;
const TUint KHsMcpMcdr2Addr		=	17;
const TUint KHmMcpMcdr2Addr		=	0x0000000f<<KHsMcpMcdr2Addr;

// MCSR
const TUint KHtMcpMcsrAts		=	KBit0;
const TUint KHtMcpMcsrArs		=	KBit1;
const TUint KHtMcpMcsrTts		=	KBit2;
const TUint KHtMcpMcsrTrs		=	KBit3;
const TUint KHtMcpMcsrAtu		=	KBit4;
const TUint KHtMcpMcsrAro		=	KBit5;
const TUint KHtMcpMcsrTtu		=	KBit6;
const TUint KHtMcpMcsrTro		=	KBit7;
const TUint KHtMcpMcsrAnf		=	KBit8;
const TUint KHtMcpMcsrAne		=	KBit9;
const TUint KHtMcpMcsrTnf		=	KBit10;
const TUint KHtMcpMcsrTne		=	KBit11;
const TUint KHtMcpMcsrCwc		=	KBit12;
const TUint KHtMcpMcsrCrc		=	KBit13;
const TUint KHtMcpMcsrAce		=	KBit14;
const TUint KHtMcpMcsrTce		=	KBit15;

const TUint KHmMcpMcsrSticky	=	KHtMcpMcsrAtu|KHtMcpMcsrAro|KHtMcpMcsrTtu|KHtMcpMcsrTro;

// SSCR0
const TUint KHsSspSscr0Scr		=	8;
const TUint KHmSspSscr0Scr		=	0x000000ff<<KHsSspSscr0Scr;
const TUint KHtSspSscr0Sse		=	KBit7;
const TUint KHsSspSscr0Frf		=	4;
const TUint KHmSspSscr0Frf		=	0x00000003<<KHsSspSscr0Frf;
const TUint KHsSspSscr0Dss		=	0;
const TUint KHmSspSscr0Dss		=	0x0000000f<<KHsSspSscr0Dss;

// SSCR1
const TUint KHtSspSscr1Ecs		=	KBit5;
const TUint KHtSspSscr1Sph		=	KBit4;
const TUint KHtSspSscr1Spo		=	KBit3;
const TUint KHtSspSscr1Lbm		=	KBit2;
const TUint KHtSspSscr1Tie		=	KBit1;
const TUint KHtSspSscr1Rie		=	KBit0;

// SSSR
const TUint KHtSspSssrRor		=	KBit6;
const TUint KHtSspSssrRfs		=	KBit5;
const TUint KHtSspSssrTfs		=	KBit4;
const TUint KHtSspSssrBsy		=	KBit3;
const TUint KHtSspSssrRne		=	KBit2;
const TUint KHtSspSssrTnf		=	KBit1;

const TUint KHmSspSssrSticky	=	KHtSspSssrRor;
//----------------------------------------------------------------------------
// LCD Data sheet (v2.2) (pages 144-183)
const TUint KHwRwLcdLccr0		=	KHwBaseLcd + 0x00;
const TUint KHwRwLcdLcsr		=	KHwBaseLcd + 0x04;
const TUint KHwRwLcdDbar1		=	KHwBaseLcd + 0x10;
const TUint KHwRwLcdDcar1		=	KHwBaseLcd + 0x14;
const TUint KHwRwLcdDbar2		=	KHwBaseLcd + 0x18;
const TUint KHwRwLcdDcar2		=	KHwBaseLcd + 0x1c;
const TUint KHwRwLcdLccr1		=	KHwBaseLcd + 0x20;
const TUint KHwRwLcdLccr2		=	KHwBaseLcd + 0x24;
const TUint KHwRwLcdLccr3		=	KHwBaseLcd + 0x28;

// LCCR0
const TUint KHsLcdLccr0Fdd		=	12;
const TUint KHmLcdLccr0Fdd		=	0x000000ff<<KHsLcdLccr0Fdd;
const TUint KHtLcdLccr0Dpd		=	KBit9;
const TUint KHtLcdLccr0Ble		=	KBit8;
const TUint KHtLcdLccr0Pas		=	KBit7;
const TUint KHtLcdLccr0Erm		=	KBit5;
const TUint KHtLcdLccr0Bam		=	KBit4;
const TUint KHtLcdLccr0Ldm		=	KBit3;
const TUint KHtLcdLccr0Sds		=	KBit2;
const TUint KHtLcdLccr0Cms		=	KBit1;
const TUint KHtLcdLccr0Len		=	KBit0;

// LCCR1
const TUint KHsLcdLccr1Blw		=	24;
const TUint KHmLcdLccr1Blw		=	0x000000ff<<KHsLcdLccr1Blw;
const TUint KHsLcdLccr1Elw		=	16;
const TUint KHmLcdLccr1Elw		=	0x000000ff<<KHsLcdLccr1Elw;
const TUint KHsLcdLccr1Hsw		=	10;
const TUint KHmLcdLccr1Hsw		=	0x0000003f<<KHsLcdLccr1Hsw;
const TUint KHsLcdLccr1Ppl		=	0;
const TUint KHmLcdLccr1Ppl		=	0x000003ff<<KHsLcdLccr1Ppl;

// LCCR2
const TUint KHsLcdLccr2Bfw		=	24;
const TUint KHmLcdLccr2Bfw		=	0x000000ff<<KHsLcdLccr2Bfw;
const TUint KHsLcdLccr2Efw		=	16;
const TUint KHmLcdLccr2Efw		=	0x000000ff<<KHsLcdLccr2Efw;
const TUint KHsLcdLccr2Vsw		=	10;
const TUint KHmLcdLccr2Vsw		=	0x0000003f<<KHsLcdLccr2Vsw;
const TUint KHsLcdLccr2Lpp		=	0;
const TUint KHmLcdLccr2Lpp		=	0x000003ff<<KHsLcdLccr2Lpp;

// LCCR3
const TUint KHtLcdLccr3Oep		=	KBit23;
const TUint KHtLcdLccr3Pcp		=	KBit22;
const TUint KHtLcdLccr3Hsp		=	KBit21;
const TUint KHtLcdLccr3Vsp		=	KBit20;
const TUint KHsLcdLccr3Api		=	16;
const TUint KHmLcdLccr3Api		=	0x0000000f<<KHsLcdLccr3Api;
const TUint KHsLcdLccr3Acb		=	8;
const TUint KHmLcdLccr3Acb		=	0x000000ff<<KHsLcdLccr3Acb;
const TUint KHsLcdLccr3Pcd		=	0;
const TUint KHmLcdLccr3Pcd		=	0x000000ff<<KHsLcdLccr3Pcd;

// LCSR
const TUint KHtLcdLcsrOuu		=	KBit11;
const TUint KHtLcdLcsrOou		=	KBit10;
const TUint KHtLcdLcsrOul		=	KBit9;
const TUint KHtLcdLcsrOol		=	KBit8;
const TUint KHtLcdLcsrIuu		=	KBit7;
const TUint KHtLcdLcsrIou		=	KBit6;
const TUint KHtLcdLcsrIul		=	KBit5;
const TUint KHtLcdLcsrIol		=	KBit4;
const TUint KHtLcdLcsrAbc		=	KBit3;
const TUint KHtLcdLcsrBer		=	KBit2;
const TUint KHtLcdLcsrBau		=	KBit1;
const TUint KHtLcdLcsrLfd		=	KBit0;

const TUint KHmLcdLcsrSticky	=	KHtLcdLcsrBer+KHtLcdLcsrAbc+KHtLcdLcsrIol+KHtLcdLcsrIul+KHtLcdLcsrIou+
									KHtLcdLcsrIuu+KHtLcdLcsrOol+KHtLcdLcsrOul+KHtLcdLcsrOou+KHtLcdLcsrOuu;

// DMA granularity (bytes)
const TUint KHwLcdPixelDmaGranularity	=	16;

// Palette structure (page 144)
const TUint KHsLcdPaletteMono	= 0;
const TUint KHmLcdPaletteMono	= 0x000f<<KHsLcdPaletteMono;
const TUint KHsLcdPaletteBlue	= 0;
const TUint KHmLcdPaletteBlue	= 0x000f<<KHsLcdPaletteBlue;
const TUint KHsLcdPaletteGreen	= 4;
const TUint KHmLcdPaletteGreen	= 0x000f<<KHsLcdPaletteGreen;
const TUint KHsLcdPaletteRed	= 8;
const TUint KHmLcdPaletteRed	= 0x000f<<KHsLcdPaletteRed;
const TUint KHsLcdPalettePbs	= 12;
const TUint KHmLcdPalettePbs	= 0x0003<<KHsLcdPalettePbs;

const TInt KHsMaxBytesPerPixel	= 1; //Maximum bpp is 16

// Palette entry spacing (bits)
const TUint KHsLcdPaletteSpacing	= 16;

// Palette masks
const TUint KHmLcdPalette4Bit		= 0x000f;
const TUint KHmLcdPalette8Bit		= 0x0fff;
const TUint KHmLcdPalette12Bit		= 0x0000;
const TUint KHmLcdPalette16Bit		= 0x0000;

// Palette entries
const TUint KHwLcdPaletteEntries4Bit	= 16;
const TUint KHwLcdPaletteEntries8Bit	= 256;
const TUint KHwLcdPaletteEntries12Bit	= 16;
const TUint KHwLcdPaletteEntries16Bit	= 16;

// Palette size given bits per pixel (bytes)
const TUint	KHwLcdPaletteBytes4Bit	= 32;
const TUint	KHwLcdPaletteBytes8Bit	= 512;
const TUint	KHwLcdPaletteBytes12Bit	= 32;
const TUint	KHwLcdPaletteBytes16Bit	= 32;

const TUint	KHwLcdExtraBytes	= KHwLcdPaletteBytes8Bit+KHwLcdPixelDmaGranularity;

// Pixel structure (pages 145-147)
const TUint KHsLcdPixelSpacing4Bit	=	4;
const TUint KHsLcdPixelSpacing8Bit	=	8;
const TUint KHsLcdPixelSpacing12Bit	=	16;
const TUint KHsLcdPixelSpacing16Bit	=	16;

// Maximum number of lcd panels for the display
const TUint KHwLcdMaxPanels			=	2;

const TUint KHwBaseUdc		=	KHwLinBaseRegisters + 0x00*KHwLinBaseRegSpacing;
const TUint KHwRwUdcCr		=	KHwBaseUdc + 0x00;
const TUint KHwRwUdcAr		=	KHwBaseUdc + 0x04;
const TUint KHwRwUdcOmp		=	KHwBaseUdc + 0x08;
const TUint KHwRwUdcImp		=	KHwBaseUdc + 0x0c;
const TUint KHwRwUdcCs0		=	KHwBaseUdc + 0x10;
const TUint KHwRwUdcCs1		=	KHwBaseUdc + 0x14;
const TUint KHwRwUdcCs2		=	KHwBaseUdc + 0x18;
const TUint KHwRwUdcD0		=	KHwBaseUdc + 0x1c;
const TUint KHwRwUdcWc		=	KHwBaseUdc + 0x20;
const TUint KHwRwUdcDr		=	KHwBaseUdc + 0x28;
const TUint KHwRwUdcSr		=	KHwBaseUdc + 0x30;
//----------------------------------------------------------------------------
// UDC Control Register (UDCCR)
// Bit definitions
const TUint KHtUdcCrUdd			=   KBit0;
const TUint KHtUdcCrUda			=   KBit1;
const TUint KHtUdcCrDisableResim=   KBit2;
const TUint KHtUdcCrDisableEim	=   KBit3;
const TUint KHtUdcCrDisableRim	=   KBit4;
const TUint KHtUdcCrDisableTim	=   KBit5;
const TUint KHtUdcCrDisableSrm	=   KBit6;
const TUint KHtUdcCrDisableSusim=   KBit6;
const TUint KHtUdcCrDisableRem	=   KBit7;

//----------------------------------------------------------------------------
// UDC Endpoint 0 Control/Status Register (UDCCSO)
// Bit definitions
const TUint KHtUdcCs0Opr	=	KBit0;	// read only
const TUint KHtUdcCs0Ipr	=	KBit1;	// Cannot be cleared
const TUint KHtUdcCs0Sst	=	KBit2;  // Write 1 to clear
const TUint KHtUdcCs0Fst	=	KBit3;
const TUint KHtUdcCs0De		=	KBit4;
const TUint KHtUdcCs0Se		=	KBit5;	// read only
const TUint KHtUdcCs0So		=	KBit6;	// Write 1 to clear	
const TUint KHtUdcCs0Sse	=	KBit7;	// Write 1 to clear
// This mask is the "no change" clear mask,these bits will not be altered
const TUint KHtUdcCs0NoChange=	KHtUdcCs0Sst+KHtUdcCs0So+KHtUdcCs0Sse;
//----------------------------------------------------------------------------
// UDC Endpoint 1 Control/Status Register (UDCCS1)
// Bit definitions
const TUint KHtUdcCs1Rfs     =   KBit0;
const TUint KHtUdcCs1Rpc     =   KBit1;
const TUint KHtUdcCs1Rpe     =   KBit2;
const TUint KHtUdcCs1Sst     =   KBit3;
const TUint KHtUdcCs1Fst     =   KBit4;
const TUint KHtUdcCs1Rne     =   KBit5;
// This mask is the "no change" clear mask,these bits will not be altered
const TUint KHtUdcCs1NoChange=	KHtUdcCs1Rpc+KHtUdcCs1Sst;
//----------------------------------------------------------------------------
// UDC Endpoint 2 Control/Status Register (UDCCS2)
// Bit definitions
const TUint KHtUdcCs2Tfs     =   KBit0;
const TUint KHtUdcCs2Tpc     =   KBit1;
const TUint KHtUdcCs2Tpe     =   KBit2;
const TUint KHtUdcCs2Tur     =   KBit3;
const TUint KHtUdcCs2Sst     =   KBit4;
const TUint KHtUdcCs2Fst     =   KBit5;
// This mask is the "no change" clear mask,these bits will not be altered
const TUint KHtUdcCs2NoChange=   KHtUdcCs2Tpc+KHtUdcCs2Sst;

//----------------------------------------------------------------------------
// UDC Status/Interrupt Register (UDCSR)
// Bit definitions
const TUint KHtUdcSrEir		=   KBit0;
const TUint KHtUdcSrRir		=   KBit1;
const TUint KHtUdcSrTir		=   KBit2;
const TUint KHtUdcSrSusir	=   KBit3;
const TUint KHtUdcSrResir	=   KBit4;
const TUint KHtUdcSrRstir	=   KBit5;
const TUint KHtUdcSrNoChange=   KHtUdcSrEir+KHtUdcSrRir+KHtUdcSrTir+KHtUdcSrSusir+KHtUdcSrResir+KHtUdcSrRstir;
//----------------------------------------------------------------------------
// Size of Ep0 FIFO is fixed at 8 bytes
const TUint KEp0FIFOSz		=	8;
//----------------------------------------------------------------------------
//   missing...
// DMA

//const TUint KHwPcmciaIo			=	0x00000000;
//const TUint KHwPcmciaMemory		=	0x08000000;
//const TUint KHwPcmciaAttribute	=	0x0c000000;

//----------------------------------------------------------------------------

class TSa1100
	{
public:
// General
	enum TPolarity
		{
		EPolarityActiveLow,
		EPolarityActiveHigh
		};
	enum TEdge
		{
		EEdgeFalling,
		EEdgeRising
		};
// DRAM configuration enumerations
	enum TDramClockDiv
		{
		EDramClockCpu=KClear32,
		EDramClockMem=KHtMemMdcnfgCdb2
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
	enum TExpansionType
		{
		EExpansionIo=KHsMemMecrBsio,
		EExpansionAttribute=KHsMemMecrBsa,
		EExpansionCommon=KHsMemMecrBsm,
		EExpansionIoSlot2=KHsMemMecrBsioSlot2,
		EExpansionAttributeSlot2=KHsMemMecrBsaSlot2,
		EExpansionCommonSlot2=KHsMemMecrBsmSlot2
		};
// LCD enumerations
	enum TLcdEnable
		{
		ELcdDisable=KClear32,
		ELcdEnable=KHtLcdLccr0Len
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
	enum TLcdBaseAddrUpdateInt
		{
		ELcdBAUpdateIntEnable=KClear32,
		ELcdBAUpdateIntDisable=KHtLcdLccr0Bam
		};
	enum TLcdErrorInt
		{
		ELcdErrorIntEnable=KClear32,
		ELcdErrorIntDisable=KHtLcdLccr0Erm
		};
// UART enumerations
	enum TUartBaudRate
		{
		EUartBaudRate115200=_UART_BRD(115200),
		EUartBaudRate76800=_UART_BRD(76800),
		EUartBaudRate57600=_UART_BRD(57600),
		EUartBaudRate38400=_UART_BRD(38400),
		EUartBaudRate19200=_UART_BRD(19200),
		EUartBaudRate14400=_UART_BRD(14400),
		EUartBaudRate9600=_UART_BRD(9600),
		EUartBaudRate4800=_UART_BRD(4800),
		EUartBaudRate2400=_UART_BRD(2400),
		EUartBaudRate1200=_UART_BRD(1200),
		EUartBaudRate600=_UART_BRD(600),
		EUartBaudRate300=_UART_BRD(300),
		EUartBaudRate150=_UART_BRD(150),
		EUartBaudRate110=_UART_BRD(110)
		};
	enum TUartBreak
		{
		EUartBreakOff=KClear32,
		EUartBreakOn=KHtUartUtcr3Brk
		};
	enum TUartParity
		{
		EUartParityNone=KClear32,
		EUartParityOdd=KHtUartUtcr0Pe,
		EUartParityEven=KHtUartUtcr0Pe|KHtUartUtcr0Oes
		};
	enum TUartStopBit
		{
		EUartStopBitOne=KClear32,
		EUartStopBitTwo=KHtUartUtcr0Sbs
		};
	enum TUartDataLength
		{
		EUartDataLength7=KClear32,
		EUartDataLength8=KHtUartUtcr0Dss
		};
	enum TUartXmitEnable
		{
		EUartDisable=KClear32,
		EUartRxEnable=KHtUartUtcr3Rxe,
		EUartTxEnable=KHtUartUtcr3Txe,
		EUartRxTxEnable=KHtUartUtcr3Rxe|KHtUartUtcr3Txe
		};
	enum TUartFifoInt
		{
		EUartFifoNoInt=KClear32,
		EUartFifoRxInt=KHtUartUtcr3Rim,
		EUartFifoTxInt=KHtUartUtcr3Tim,
		EUartFifoRxTxInt=KHtUartUtcr3Rim|KHtUartUtcr3Tim
		};
	enum TUartLoopback
		{
		EUartLoopbackOff=KClear32,
		EUartLoopbackOn=KHtUartUtcr3Lbm
		};
	enum TUartExtClock
		{
		EUartExtClockNone=KClear32,
		EUartExtClockRxRiseTxRise=KHtUartUtcr0Sce,
		EUartExtClockRxFallTxRise=KHtUartUtcr0Sce|KHtUartUtcr0Rce,
		EUartExtClockRxRiseTxFall=KHtUartUtcr0Sce|KHtUartUtcr0Tce,
		EUartExtClockRxFallTxFall=KHtUartUtcr0Sce|KHtUartUtcr0Tce|KHtUartUtcr0Rce
		};

// Slow Infra-red enumeration
	enum TSirPowerMode
		{
		ESirLowPowerDisable = KClear32,
		ESirLowPowerEnable  = KBit1
		};
	enum TSirCommsMode
		{
		ESirNrzComms  = KClear32,
		ESirIrdaComms = KBit0
		};
// Fast Infra-red enumerations
	enum TIrDeviceSelect
		{
		EHpSirDevice =KClear32,
		E4ppmDevice  =KHtHsspHscr0Itr
		};
	enum THsspLoopback
		{
		EHsspLoopbackOff=KClear32,
		EHsspLoopbackOn =KHtHsspHscr0Lbm
		};
	enum THsspUnderrunBehaviour
		{
		EHsspEndOnUnderrun   =KClear32,
		EHsspAbortOnUnderrun =KHtHsspHscr0Tus 
		};
	enum THsspXmitEnable
		{
		EHsspDisable   =KClear32,
		EHsspRxEnable  =KHtHsspHscr0Rxe,
		EHsspTxEnable  =KHtHsspHscr0Txe,
		EHsspRxTxEnable=KHtHsspHscr0Rxe|KHtHsspHscr0Txe
		};
	enum THsspFifoInt
		{
		EHsspFifoNoInt  =KClear32,
		EHsspFifoRxInt  =KHtHsspHscr0Rie,
		EHsspFifoTxInt  =KHtHsspHscr0Tie,
		EHsspFifoRxTxInt=KHtHsspHscr0Rie|KHtHsspHscr0Tie
		};
	enum THsspAddressMatch
		{

		EHsspAddrMatchDisable = KClear32,
		EHsspAddrMatchEnable  =	KHtHsspHscr0Ame
		};
	enum THsspPinPolarity
		{
		EHsspTxTrueRxTrue = KHtHsspHscr2Txp|KHtHsspHscr2Rxp,
		EHsspTxTrueRxInv  = KHtHsspHscr2Txp,
		EHsspTxInvRxTrue  = KHtHsspHscr2Rxp,
		EHsppTxInvRxInv   = KClear32
		};

// Multimedia Communications Port (MCP)
	enum TMcpEnable
		{
		EMcpDisable=KClear32,
		EMcpEnable=KHtMcpMccr0Mce
		};
	enum TMcpExtClock
		{
		EMcpInternalClock=KClear32,
		EMcpExternalClock=KHtMcpMccr0Ecs
		};
	enum TMcpADMode
		{
		EMcpADDataValidMode=KClear32,
		EMcpADCounterMode=KHtMcpMccr0Adm
		};
	enum TMcpTteInt
		{
		EMcpTteIntDisable=KClear32,
		EMcpTteIntEnable=KHtMcpMccr0Tte
		};
	enum TMcpTreInt
		{
		EMcpTreIntDisable=KClear32,
		EMcpTreIntEnable=KHtMcpMccr0Tre
		};
	enum TMcpAteInt
		{
		EMcpAteIntDisable=KClear32,
		EMcpAteIntEnable=KHtMcpMccr0Ate
		};
	enum TMcpAreInt
		{
		EMcpAreIntDisable=KClear32,
		EMcpAreIntEnable=KHtMcpMccr0Are
		};
	enum TMcpLoopback
		{
		EMcpLoopbackDisable=KClear32,
		EMcpLoopbackEnable=KHtMcpMccr0Lbm
		};
	enum TMcpExtClockPrescale
		{
		EMcpExtClockDivByOne=KClear32,
		EMcpExtClockDivByTwo=KHtMcpMccr0Ecp0,
		EMcpExtClockDivByThree=KHtMcpMccr0Ecp1,
		EMcpExtClockDivByFour=KHtMcpMccr0Ecp0|KHtMcpMccr0Ecp1
		};

	enum TMcpClockFrequency
		{
		EMcpFreq12MHz=KClear32,
		EMcpFreq10MHz=KHtMcpMccr1Cfs
		};


// Synchronous Serial Port (SSP)
	enum TSspDataSize
		{
		ESspData4Bit=3,ESspData5Bit=4,ESspData6Bit=5,ESspData7Bit=6,ESspData8Bit=7,
		ESspData9Bit=8,ESspData10Bit=9,ESspData11Bit=10,ESspData12Bit=11,ESspData13Bit=12,
		ESspData14Bit=13,ESspData15Bit=14,ESspData16Bit=15
		};
	enum TSspFrameFormat
		{ESspFrameFormatSPI=0,ESspFrameFormatTISyncSer=1,ESspFrameFormatNatMicrowire=2};
static const TInt KSspClk1843200Bps = 0;
static const TInt KSspClk460800Bps = 3;
static const TInt KSspClk7200Bps = 255;
	enum TSspEnable
		{ESspDisable=KClear32,ESspEnable=KHtSspSscr0Sse};
	enum TSspRxFifoInt
		{ESspRxFifoIntDisable=KClear32,ESspRxFifoIntEnable=KHtSspSscr1Rie};
	enum TSspTxFifoInt
		{ESspTxFifoIntDisable=KClear32,ESspTxFifoIntEnable=KHtSspSscr1Tie};
	enum TSspLoopBack
		{ESspLoopBackDisable=KClear32,ESspLoopBackEnable=KHtSspSscr1Lbm};
	enum TSspSerClkPhase
		{ESspSclkPhaseMode1=KClear32,ESspSclkPhaseMode2=KHtSspSscr1Sph};
	enum TSspExtClockSel
		{ESspExtClkDisable=KClear32,ESspExtClkEnable=KHtSspSscr1Ecs};
// Peripheral pin controller
	enum TPpcAssignment
		{
		EPpcReassignNone=KClear32,
		EPpcReassignUpr=KHwPpcPparUpr,
		EPpcReassignSpr=KHwPpcPparSpr,
		EPpcReassignUprSpr=EPpcReassignUpr|EPpcReassignSpr
		};
	enum TDmaChannel
		{
		EDmaChannel0=0,
		EDmaChannel1=1,//KBrutusDmaChannelSize,
		EDmaChannel2=2,//KBrutusDmaChannelSize*2,
		EDmaChannel3=3,//KBrutusDmaChannelSize*3,
		EDmaChannel4=4,//KBrutusDmaChannelSize*4,
		EDmaChannel5=5 //KBrutusDmaChannelSize*5
		};

public:
// Initialisation
	static void Init3();

	static TUint32 DebugPortAddr();

	//DMA
	IMPORT_C static TUint32 GetDmaDevInfo(TUint8 aChannel);
	IMPORT_C static void    SetDmaDevInfo(TUint8 aChannel,TUint32 aVal);
	IMPORT_C static void    ClearDmaDscReg(TUint8 aChannel,TUint8 aClearMask);
	IMPORT_C static TUint32 GetDmaDscReg(TUint8 aChannel);
	IMPORT_C static void    SetDmaDscReg(TUint8 aChannel,TUint32 aVal);

	IMPORT_C static TUint32 GetDmaAddrBufA(TUint8 aChannel);
	IMPORT_C static TUint32 GetDmaCountBufA(TUint8 aChannel);
	IMPORT_C static TUint32 GetDmaAddrBufB(TUint8 aChannel);
	IMPORT_C static TUint32 GetDmaCountBufB(TUint8 aChannel);
	IMPORT_C static void SetDmaAddrBufA(TUint8 aChannel,TUint32 aVal);
	IMPORT_C static void SetDmaCountBufA(TUint8 aChannel,TUint32 aVal);
	IMPORT_C static void SetDmaAddrBufB(TUint8 aChannel,TUint32 aVal);
	IMPORT_C static void SetDmaCountBufB(TUint8 aChannel,TUint32 aVal);

	IMPORT_C static void StartBufA(TUint8 aChannel,TUint32 aVal);
	IMPORT_C static void StartBufB(TUint8 aChannel,TUint32 aVal);
	IMPORT_C static void CancelXfer(TUint8 aChannel);
	IMPORT_C static TInt NextBuffer(TUint8 aChannel);
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
	IMPORT_C static TUint PowerScratchpad();
	IMPORT_C static void SetPowerScratchpad(TUint aValue);
	IMPORT_C static void SetStandby();
	IMPORT_C static TUint ProcessorClockInKHz();
	IMPORT_C static TUint ProcessorPeriodInPs();
	IMPORT_C static TInt CpuVersionId();
// Memory (data: pages 96-123)
	IMPORT_C static void SetMemDramConfig(TUint aRows,TDramClockDiv aClockDiv,TUint aRasPrechg,
										  TUint aRasCbr,TUint aLatchTiming,TUint aRefresh);
	IMPORT_C static void SetMemStaticConfig(TRomType aType,TRomWidth aWidth,TUint aDelayFirst,
											TUint aDelayNext,TUint aRecover,TUint aChipSelect);
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
	IMPORT_C static void UpdateSystemTime(TBool aRtcChanged=EFalse);
	IMPORT_C static void SynchronizeSystemTime();
// LCD (data: pages 142-175)
	IMPORT_C static void SetLcdEnable(TLcdEnable anEnable);
	IMPORT_C static TLcdEnable LcdEnable();
	IMPORT_C static void SetLcdSize(TUint aPixelsPerLine,TUint aLinesPerPanel);
	IMPORT_C static void SetLcdConfig(TLcdMode aMode,TLcdPanelConfig aPanelConfig);
	IMPORT_C static void SetLcdVramBase(TUint aVramBase1,TUint aVramBase2=0);
	IMPORT_C static void SetLcdMemoryConfig(TLcdMemoryGender aMemGender,TUint aDmaReqDelay);
	IMPORT_C static void SetLcdHorizontalClocks(TUint aStartCount,TUint aHsyncPulseWidth,TUint anEndCount);
	IMPORT_C static void SetLcdVerticalClocks(TUint aStartCount,TUint aVsyncPulseWidth,TUint anEndCount);
	IMPORT_C static void SetLcdOtherClocks(TUint aPixClockDiv,TUint anAcBiasFreq,TUint anAcBiasTpi);
	IMPORT_C static void SetLcdSignalsPolarity(TPolarity aVsync,TPolarity anHsync,TEdge aPixClk,TPolarity anOe);
	IMPORT_C static void ModifyLcdIntMasks(TLcdDisableDoneInt anLDM,TLcdBaseAddrUpdateInt aBAM,TLcdErrorInt anERM);
	IMPORT_C static TUint LcdStatus();
	IMPORT_C static void LcdClearStatus(TUint aClearMask);
	IMPORT_C static TUint LcdVramCurrentAddress(TLcdDmaChannel aDmaChannel);
// UARTs (data: pages 236-252)
	IMPORT_C static void SetUartData(TUint aValue,TUint aPortBase);
	IMPORT_C static TUint UartData(TUint aPortBase);
	IMPORT_C static void SetUartConfig(TUartBaudRate aRate,TUartParity aParity,TUartStopBit aStopBit,
									   TUartDataLength aDataLength,TUint aPortBase);
	IMPORT_C static TUartBaudRate UartBaudRate(TUint aPortBase);
	IMPORT_C static TUartParity UartParity(TUint aPortBase);
	IMPORT_C static TUartStopBit UartStopBit(TUint aPortBase);
	IMPORT_C static TUartDataLength UartPortDataLength(TUint aPortBase);
	IMPORT_C static void SetUartPortBreak(TUartBreak aBreak,TUint aPortBase);
	IMPORT_C static TUartBreak UartPortBreak(TUint aPortBase);
	IMPORT_C static void SetUartEnable(TUartXmitEnable anEnable,TUartFifoInt aFifoInt,
									   TUartLoopback aLoopback,TUint aPortBase);
	IMPORT_C static TUartXmitEnable UartXmitEnable(TUint aPortBase);
	IMPORT_C static TUartFifoInt UartFifoInt(TUint aPortBase);
	IMPORT_C static TUartLoopback UartLoopback(TUint aPortBase);
	IMPORT_C static void SetUartExtClock(TUartExtClock aConfig,TUint aPortBase);
	IMPORT_C static TUartExtClock UartExtClock(TUint aPortBase);
	IMPORT_C static TUint UartStatus0(TUint aPortBase);
	IMPORT_C static void UartClearStatus0(TUint aClearMask,TUint aPortBase);
	IMPORT_C static TUint UartStatus1(TUint aPortBase);
	IMPORT_C static TBool UartRxFifoEmpty(TUint aPortBase);
	IMPORT_C static TBool UartTxBusy(TUint aPortBase);
	IMPORT_C static TBool UartTxFifoFull(TUint aPortBase);
// Slow Ir Port
	IMPORT_C static void SetIcpSirMode(TSirPowerMode aPowerMode,TSirCommsMode aCommMode);
	IMPORT_C static void SetSirEnable();
// Fast Ir Port (HSSP)
	IMPORT_C static void  SetHsspData(TUint aValue);
	IMPORT_C static TUint HsspData();
	IMPORT_C static void  SetHsspEnable(THsspXmitEnable anEnable,THsspFifoInt aFifoInt,
											 THsspLoopback aLoopback,THsspUnderrunBehaviour aBehaviour);
	IMPORT_C static void    SetHsspAddrMatch(TUint8 anIrdaPortNo);
	IMPORT_C static TUint8  GetHsspAddrMatch();
	IMPORT_C static void SetHsspPinPolarity(THsspPinPolarity aPolarity);
	IMPORT_C static THsspPinPolarity GetHsspPinPolarity();
	IMPORT_C static TUint HsspStatus0();
	IMPORT_C static void  HsspClearStatus0(TUint aClearMask);
	IMPORT_C static TUint HsspStatus1();
	IMPORT_C static TBool HsspRxFifoEmpty();
	IMPORT_C static TBool HsspTxFifoFull();	
//	IMPORT_C static void  SetHsspAbort(TUartBreak aBreak,TUint aPortBase);
// Multimedia Communications Port (MCP)
	// MCCR0
	IMPORT_C static void SetMcpMccr0(TUint aVal);
	IMPORT_C static TUint McpMccr0();
	IMPORT_C static void SetMcpAudioDivisor(TUint aDiv);
	IMPORT_C static TInt McpAudioDivisor();
	IMPORT_C static void SetMcpTelecomDivisor(TUint aDiv);
	IMPORT_C static TInt McpTelecomDivisor();
	IMPORT_C static void SetMcpEnable(TMcpEnable aEnable);
	IMPORT_C static void SetMcpExternalClockSelect(TMcpExtClock aSelect);
	IMPORT_C static void SetMcpADSampleMode(TMcpADMode aMode);
	IMPORT_C static void SetMcpTteInterrupt(TMcpTteInt aInt);
	IMPORT_C static void SetMcpTreInterrupt(TMcpTreInt aInt);
	IMPORT_C static void SetMcpAteInterrupt(TMcpAteInt aInt);
	IMPORT_C static void SetMcpAreInterrupt(TMcpAreInt aInt);
	IMPORT_C static void SetMcpLoopback(TMcpLoopback aLoop);
	IMPORT_C static void SetMcpExtClockDiv(TMcpExtClockPrescale aDiv);
	// MCCR1
	IMPORT_C static void SetMcpClockFrequency(TMcpClockFrequency aFreq);
	// MCDR2
	IMPORT_C static void McpDataRegisterWrite(TInt aReg, TInt aValue);
	IMPORT_C static TInt McpDataRegisterRead(TInt aReg);
	// MCSR
	IMPORT_C static TUint McpMcsr();
	IMPORT_C static void McpClearStatus(TUint aClearMask);

// Synchronous Serial Port (SSP)
	IMPORT_C static void SetSspConfig(TSspDataSize aSize,TSspFrameFormat aFormat,TInt aClockRate);
	IMPORT_C static void SetSspEnable(TSspEnable anEnable);
	IMPORT_C static void ModifySspIntMasks(TSspRxFifoInt anRFI,TSspTxFifoInt anTFI,TSspLoopBack anLbMode);
	IMPORT_C static void SetSspSerialClockConfig(TPolarity aPolarity,TSspSerClkPhase aPhase,TSspExtClockSel aSel);
	IMPORT_C static void SetSspData(TUint aValue);
	IMPORT_C static TUint SspData();
	IMPORT_C static TUint SspStatus();
	IMPORT_C static void SspClearStatus(TUint aClearMask);
// Interrupts (data: pages 64-69)
	IMPORT_C static TUint IntLevels();
	IMPORT_C static void SetIntLevels(TUint aValue);
	IMPORT_C static void ModifyIntLevels(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint IntMask();
	IMPORT_C static void SetIntMask(TUint aValue);
	IMPORT_C static void ModifyIntMask(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint IntsPending();
	IMPORT_C static TUint IrqsPending();
	IMPORT_C static TUint FiqsPending();
// General-purpose I/O (data: pages 54-63)
	IMPORT_C static TUint Port();
	IMPORT_C static void SetPort(TUint aSetMask);
	IMPORT_C static void ClearPort(TUint aClearMask);
	IMPORT_C static void ModifyPort(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint Ddr();
	IMPORT_C static void SetDdr(TUint aValue);
	IMPORT_C static void ModifyDdr(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortRisingEdgeDetect();
	IMPORT_C static void SetPortRisingEdgeDetect(TUint aValue);
	IMPORT_C static void ModifyPortRisingEdgeDetect(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortFallingEdgeDetect();
	IMPORT_C static void SetPortFallingEdgeDetect(TUint aValue);
	IMPORT_C static void ModifyPortFallingEdgeDetect(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortEdgeDetected();
	IMPORT_C static void ClearPortEdgeDetected(TUint aClearMask);
	IMPORT_C static TUint PortAlternatives();
	IMPORT_C static void SetPortAlternatives(TUint aValue);
	IMPORT_C static void ModifyPortAlternatives(TUint aClearMask,TUint aSetMask);
// Peripheral pin controller (data: pages 292-302)
	IMPORT_C static TUint PpcPort();
	IMPORT_C static void SetPpcPort(TUint aValue);
	IMPORT_C static void ModifyPpcPort(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PortSleepData();
	IMPORT_C static void SetPortSleepData(TUint aValue);
	IMPORT_C static void ModifyPortSleepData(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PpcDdr();
	IMPORT_C static void SetPpcDdr(TUint aValue);
	IMPORT_C static void ModifyPpcDdr(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PpcSleepDdr();
	IMPORT_C static void SetPpcSleepDdr(TUint aValue);
	IMPORT_C static void ModifyPpcSleepDdr(TUint aClearMask,TUint aSetMask);
	IMPORT_C static TUint PpcAllocated();
	IMPORT_C static TPpcAssignment PpcAssignment();
	IMPORT_C static void SetPpcAssignment(TPpcAssignment anAssignment);
	IMPORT_C static void ModifyPpcAssignment(TPpcAssignment aClearMask,TPpcAssignment aSetMask);
// UDC device
    // Write UDC Control
	IMPORT_C static void SetUdcControl(TUint aValue, TUint aPreserveMask, TUint aTestValue);
    IMPORT_C static void ModifyUdcControl(TUint aClearMask,TUint aSetMask, TUint aPreserveMask, TUint aTestValue);
    // Read UDC Control
    IMPORT_C static  TUint UdcControl();

    IMPORT_C static void SetUdcEnable();
    IMPORT_C static void SetUdcDisable();
    IMPORT_C static TBool UdcActive();
	IMPORT_C static void TSa1100::UdcWaitInactive();

    //----------------------------------------------------------------------------

    // UDC Address Register (UDCAR)
    // Write UDC Address
    IMPORT_C static void SetUdcAddress(TUint aValue);
    // Read UDC Address
    IMPORT_C static  TUint UdcAddress();

    //----------------------------------------------------------------------------
    // UDC OUT Max Packet Register (UDCOMP)
    // These will use the intended size rather than the size-1
    // Write UDC Rx Max Packet size
    IMPORT_C static void SetUdcOutMaxPktSize(TUint aValue);
    // Read UDC Rx Max Packet size
    IMPORT_C static  TUint UdcOutMaxPktSize();

    //----------------------------------------------------------------------------
    // UDC IN Max Packet Register (UDCIMP)
    // These will use the intended size rather than the size-1
    // Write UDC Tx Max Packet size
    IMPORT_C static void SetUdcInMaxPktSize(TUint aValue);
    // Read UDC Tx Max Packet size
    IMPORT_C static  TUint UdcInMaxPktSize();

    // Write UDC Endpoint 0 Control/Status 
    IMPORT_C static void SetUdcEp0Control(TUint aValue,TUint aPreserveMask,TUint aTestValue);
    IMPORT_C static void ModifyUdcEp0Control(TUint aClearMask,TUint aSetMask,TUint aPreserveMask,TUint aTestValue);
    // Read UDC Endpoint 0 Control/Status
    IMPORT_C static  TUint UdcEp0Control();


    // UDC Endpoint 0 Control/Status Register access functions
    // OUT Packet Ready, set when a valid OUT Packet is received
    // must be cleared by driver to permit entry to data phase of token processing
    IMPORT_C static void ClearUdcOPR();
    IMPORT_C static TBool UdcOPR();

    // IN Packet Ready, set when driver has written an OUT Packet to endpoint 0 FIFO
    IMPORT_C static void SetUdcIPR();
    IMPORT_C static TBool UdcIPR();

    // UDC Endpoint 0 Stall
    // This stall is for protocol violation.
    IMPORT_C static TBool UdcEp0Stalled();
    IMPORT_C static void ClearEp0UdcStall();
    // Driver forces stall with this
    IMPORT_C static void UdcEp0ForceStall();

    // Data End
    IMPORT_C static void SetUdcDataEnd();
    IMPORT_C static TBool UdcDataEnd();

    // Setup End
    IMPORT_C static void ClearUdcSetupEnd();
    IMPORT_C static TBool UdcSetupEnd();

    // Write UDC Endpoint 1 Control/Status
    IMPORT_C static void SetUdcEp1Control(TUint aValue,TUint aPreserveMask, TUint aTestValue);
    // Read UDC Endpoint 1 Control/Status
    IMPORT_C static  TUint UdcEp1Control();

    // UDC Endpoint 1 Control/Status Register access functions
    // Receive FIFO service (FIFO holds more that 8 bytes)
    IMPORT_C static TBool UdcRxFifoService();
    IMPORT_C static TBool UdcRxPktComplete();
    IMPORT_C static void ClearUdcRxPktComplete();
    IMPORT_C static TBool UdcRxPktErr();

    // UDC Endpoint 1 Stall
    // This stall is for protocol violation.
    IMPORT_C static TBool UdcRxStalled();
    IMPORT_C static void ClearUdcRxStall();
    // Driver forces stall with this
    IMPORT_C static void UdcRxForceStall();

    // State of Rx FIFO
    IMPORT_C static TBool UdcRxFifoEmpty();

    // Write UDC Endpoint 2 Control/Status
    IMPORT_C static void SetUdcEp2Control(TUint aValue,TUint aPreserveMask, TUint aTestValue);
    // Read UDC Endpoint 2 Control/Status
    IMPORT_C static  TUint UdcEp2Control();

    // UDC Endpoint 2 Control/Status Register access functions
    // Transmit FIFO service (FIFO holds less that 8 bytes)
    IMPORT_C static TBool UdcTxFifoService();
    IMPORT_C static void ClearTxPktComplete();
    IMPORT_C static TBool UdcTxPktComplete();
    IMPORT_C static TBool UdcTxPktErr();

    // UDC Endpoint 2 Stall
    // This stall is for protocol violation.
    IMPORT_C static TBool UdcTxStalled();
    IMPORT_C static void ClearUdcTxStall();
    // Driver forces stall with this
    IMPORT_C static void UdcTxForceStall();

    // State of Tx FIFO
    IMPORT_C static TBool UdcTxUnderrun();

    //----------------------------------------------------------------------------
    // UDC Endpoint 0 Data Register (UDCD0)
    // Write Endpoint 0 FIFO
    IMPORT_C static void SetUdcEp0Data(TUint aValue);
    // Read Endpoint 0 FIFO
    IMPORT_C static volatile TUint UdcEp0Data();

    //----------------------------------------------------------------------------
    // UDC Endpoint 0 Write Count Register (UDCWC)
    // Read Endpoint 0 Rx count
    IMPORT_C static TUint UdcEp0Count();

    //----------------------------------------------------------------------------
    // UDC Data Register (UDDR)
    // Write Data to UDC Tx FIFO
    IMPORT_C static void SetUdcData(TUint aValue);
    // Read Data from UDC Rx FIFO
    IMPORT_C static  TUint UdcData();

    // Write UDC Status/Interrupt
    IMPORT_C static void ClearUdcStatus(TUint aValue);
    // Read UDC Status/Interrupt
    IMPORT_C static  TUint UdcStatus();

    IMPORT_C static void ClearUdcEp0IntReq();
    IMPORT_C static TBool UdcEp0IntReq();

    IMPORT_C static void ClearUdcTxIntReq();
    IMPORT_C static TBool UdcTxIntReq();

    IMPORT_C static void ClearUdcRxIntReq();
    IMPORT_C static TBool UdcRxIntReq();

    IMPORT_C static void ClearUdcSusIntReq();
    IMPORT_C static TBool UdcSusIntReq();

    IMPORT_C static void ClearUdcRsmIntReq();
    IMPORT_C static TBool UdcRsmIntReq();

    IMPORT_C static void ClearUdcRstIntReq();
    IMPORT_C static TBool UdcRstIntReq();
private:
	static inline volatile TUint Register32(TUint anAddr);
	static inline void SetRegister32(TUint aValue,TUint anAddr);
	static inline void ModifyRegister32(TUint aClearMask,TUint aSetMask,TUint anAddr);
	static inline void SetRegisterVerify32(TUint aValue,TUint anAddr);
	static inline void SetRegisterVerify32(TUint aValue,TUint aPreserveMask,TUint aTestValue,TUint anAddr);
	static inline void ModifyRegisterVerify32(TUint aClearMask,TUint aSetMask,TUint aPreserveMask,TUint aTestValue,TUint anAddr);
	static inline volatile TUint8 Register8(TUint anAddr);
	static inline void SetRegister8(TUint8 aValue, TUint anAddr);
	static inline void ModifyRegister8(TUint8 aClearMask, TUint8 aSetMask, TUint anAddr);
	static inline void SetRegisterVerify8(TUint8 aValue, TUint anAddr);
	static inline void SetRegisterVerify8(TUint8 aValue, TUint8 aPreserveMask, TUint8 aTestValue, TUint anAddr);
	static inline void ModifyRegisterVerify8(TUint8 aClearMask, TUint8 aSetMask8, TUint8 aPreserveMask,
											 TUint8 aTestValue, TUint anAddr);
	static inline void UdcSmallDelay();
public:
	static volatile TUint LastRtcValue;
	static volatile TUint RtcFraction;
private:
	static TUint GPIOfollower;					//
	static TUint PPCfollower;					//				
	};


/**
 Return base address of debug UART (as selected in obey file or with
 eshell debugport command).
 */

inline TUint32 TSa1100::DebugPortAddr()
	{
	// Default to UART 3
	return (TheSuperPage().iDebugPort == 1) ? KHwBaseSerial1Uart : KHwBaseSerial3;
	}

#endif

