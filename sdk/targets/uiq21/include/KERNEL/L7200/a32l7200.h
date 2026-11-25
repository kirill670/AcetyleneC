// A32L7200.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __A32L7200_H__
#define __A32L7200_H__
#include <e32std.h>
#include <k32std.h>
#include <e32hal.h>

//
// L7200 Interrupts
//

_LIT8(KInterruptSTWDOG, "STWDOG");			// Watchdog Timer
_LIT8(KInterruptProgIRQ, "ProgIRQ");		// Programmable interrupt
_LIT8(KInterruptCommRx, "CommRx");			// Debug Port Tx
_LIT8(KInterruptCommTx, "CommTx");			// Debug Port Rx
_LIT8(KInterruptGCTC1IRQ, "GCTC1IRQ");		// Timer 1
_LIT8(KInterruptGCTC2IRQ, "GCTC2IRQ");		// Timer 2
_LIT8(KInterruptDMAC0IRQ, "DMAC0IRQ");		// DMA Controller Channel 0
_LIT8(KInterruptCLCDIRQ, "CLCDIRQ");		// Color LCD
_LIT8(KInterruptSMRXREADIRQ, "SMRXREADIRQ");// Smart Card
_LIT8(KInterruptSMTXTIDEIRQ, "SMTXTIDEIRQ");// Smart Card
_LIT8(KInterruptSMRESTIRQ, "SMRESTIRQ");	// Smart Card
_LIT8(KInterruptSIBIRQ, "SIBIRQ");			// Serial Interface Bus
_LIT8(KInterruptMMCIRQ, "MMCIRQ");			// Multimedia Card
_LIT8(KInterruptSSP1IRQ, "SSP1IRQ");		// Synchronous Serial Port1
_LIT8(KInterruptSSP2IRQ, "SSP2IRQ");		// Synchronous Serial Port2
_LIT8(KInterruptSPIIRQ, "SPIIRQ");			// SPI Slave
_LIT8(KInterruptU1IRQ, "U1IRQ");			// UART1
_LIT8(KInterruptU2IRQ, "U2IRQ");			// UART2
_LIT8(KInterruptIrDAIRQ, "IrDAIRQ");		// Medium/Fast IrDA Interface
_LIT8(KInterruptRTCTICKIRQ, "RTCTICKIRQ");	// Real-time TIC Event
_LIT8(KInterruptRTCALARMIRQ, "RTCALARMIRQ");// RTC Alarm
_LIT8(KInterruptGPIOIRQ, "GPIOIRQ");		// General-Purpose I/O
_LIT8(KInterruptGDMA, "GDMA_RQ");			// GPIO DMA
_LIT8(KInterruptM2MIRQ, "M2MIRQ");			// Memory to Memory DMA Controller
_LIT8(KInterruptReserved, "Reserved");		// reserved
_LIT8(KInterruptnINTF, "nINTF");			// External Active Low Interrupt Input 
_LIT8(KInterruptnINT0, "nINT0");			// External Active Low Interrupt Input 
_LIT8(KInterruptnINT1, "nINT1");			// External Active Low Interrupt Input 
_LIT8(KInterruptnINT2, "nINT2");			// External Active Low Interrupt Input 
_LIT8(KInterruptINT3, "INT3");				// External Active High Interrupt Input 
_LIT8(KInterruptBLINT, "BLINT");			// Low Battery or External Power
_LIT8(KInterruptMCINT, "MCINT");			// Set by rising edge on STMEDCHG
_LIT8(KInterruptDMAC1IRQ, "DMAC1IRQ");		// DMA Controller Channel 1 - piggy backed on DMAC0IRQ
_LIT8(KInterruptDMAC2IRQ, "DMAC2IRQ");		// DMA Controller Channel 2 
_LIT8(KInterruptDMAC3IRQ, "DMAC3IRQ");		// DMA Controller Channel 3 
_LIT8(KInterruptDMAC4IRQ, "DMAC4IRQ");		// DMA Controller Channel 4 
_LIT8(KInterruptDMAC5IRQ, "DMAC5IRQ");		// DMA Controller Channel 5 
_LIT8(KInterruptDMAC6IRQ, "DMAC6IRQ");		// DMA Controller Channel 6 
_LIT8(KInterruptDMAC7IRQ, "DMAC7IRQ");		// DMA Controller Channel 7 

//                               
// L7200 Hardware Addresses and constants
//

#ifndef __SINGLE__
const TUint KL7200BaseAddress=0x58000000;
#define L7200_BASE_ADDRESS 0x58000000
#else
const TUint KL7200BaseAddress=0x80000000;
#define L7200_BASE_ADDRESS 0x80000000
#endif

#define KL7200MachineModeMono	0x0001
#define KL7200MachineModeColour	0x0002

#define KL7200XYIn_IntMask	0x20000000;
	const TUint	KL7200UART1_BASE	= 0x0B000;
	const TUint	KL7200UART2_BASE	= 0x0C000;
	const TUint KL7200UARTDR		= 0x00;
	const TUint KL7200RXSTAT		= 0x04;
	const TUint KL7200H_UBRLCR		= 0x08;
	const TUint KL7200M_UBRLCR		= 0x0C;
	const TUint KL7200L_UBRLCR		= 0x10;
	const TUint KL7200UARTCON		= 0x14;
	const TUint KL7200UARTFLG		= 0x18;
	//
	const TUint	KL7200UARTFLG_UBUSY	= KBit3;
	const TUint	KL7200UARTFLG_UTXFF	= KBit5;
	
	const TUint KL7200MMC_BASE		= 0x11000;

	const TUint KL7200INT_BASE		= 0x13000;
	const TUint KL7200IRQSTATUS		= 0x000;
	const TUint KL7200IRQRAWSTATUS	= 0x004;
	const TUint KL7200IRQENABLE		= 0x008;
	const TUint KL7200IRQENABLESET	= 0x008;
	const TUint KL7200IRQENABLECLEAR= 0x00C;
	const TUint KL7200IRQProgIrq	= 0x010;

	const TUint KL7200FIQSTATUS		= 0x100;
	const TUint KL7200FIQRAWSTATUS	= 0x104;
	const TUint KL7200FIQENABLE		= 0x108;
	const TUint KL7200FIQENABLESET	= 0x108;
	const TUint KL7200FIQENABLECLEAR= 0x10C;

	const TUint KL7200TIMER_BASE	= 0x15000;
	const TUint KL7200TIMER1LOAD	= 0x000;
	const TUint KL7200TIMER1VALUE	= 0x004;
	const TUint KL7200TIMER1CONTROL	= 0x008;
	const TUint KL7200TIMER1CLEAR	= 0x00C;

	const TUint KL7200TIMER2LOAD	= 0x020;
	const TUint KL7200TIMER2VALUE	= 0x024;
	const TUint KL7200TIMER2CONTROL	= 0x028;
	const TUint KL7200TIMER2CLEAR	= 0x02C;

	const TUint KL7200RTC_BASE		= 0x14000;
	const TUint KL7200RTCRTCDR		= 0x000;
	const TUint KL7200RTCRTCMR		= 0x004;
	const TUint KL7200RTCRTCS		= 0x008;
	const TUint KL7200RTCRTCC		= 0x008;
	const TUint KL7200RTCRTCDV		= 0x00C;
	const TUint KL7200RTCRTCCR		= 0x010;

	// Keyboard Memory base
	const TUint KL7200KEYBOARD_BASE	= 0x16000;
	const TUint	KL7200KBDR			= 0x00;
	const TUint	KL7200KBDMR			= 0x04;
	const TUint	KL7200KBSBSR		= 0x08;
	const TUint	KL7200KBKSR			= 0x10;

	const TUint KL7200GPIO_BASE		= 0x17000;
	const TUint KL7200PortA8		= 0x0;
	const TUint KL7200DdrA8			= 0x4;
	const TUint KL7200SbsrA8		= 0x8;
	const TUint KL7200EenrA8		= 0xc;
	const TUint KL7200EsnrA8		= 0x10;
	const TUint KL7200EstrA8		= 0x14;
	const TUint KL7200ImrA8			= 0x18;
	const TUint KL7200IntA8			= 0x1c;
	const TUint KL7200PortB8		= 0x20;
	const TUint KL7200DdrB8			= 0x24;
	const TUint KL7200SbsrB8		= 0x28;
	const TUint KL7200ImrB8			= 0x38;
	const TUint KL7200IntB8			= 0x3c;
	const TUint KL7200PortC8		= 0x40;
	const TUint KL7200DdrC8			= 0x44;
	const TUint KL7200SbsrC8		= 0x48;
	const TUint KL7200ImrC8			= 0x58;
	const TUint KL7200IntC8			= 0x5c;
	const TUint KL7200PortD8		= 0x60;
	const TUint KL7200DdrD8			= 0x64;
	const TUint KL7200SbsrD8		= 0x68;
	const TUint KL7200EenrD8		= 0x6c;
	const TUint KL7200EsnrD8		= 0x70;
	const TUint KL7200EstrD8		= 0x74;
	const TUint KL7200ImrD8			= 0x78;
	const TUint KL7200IntD8			= 0x7c;
	const TUint KL7200PortE8		= 0x80;
	const TUint KL7200DdrE8			= 0x84;
	const TUint KL7200SbsrE8		= 0x88;
	const TUint KL7200EenrE8		= 0x8c;
	const TUint KL7200EsnrE8		= 0x90;
	const TUint KL7200EstrE8		= 0x94;
	const TUint KL7200ImrE8			= 0x98;
	const TUint KL7200IntE8			= 0x9c;

	const TUint KL7200SIB_BASE		= 0x07000;
	const TUint KL7200SIBMCCR		= 0x000;
	const TUint KL7200SIBMCDR0		= 0x008;
	const TUint KL7200SIBMCDR1		= 0x00C;
	const TUint KL7200SIBMCDR2		= 0x010;
	const TUint KL7200SIBMCSR		= 0x018;


	const TUint KL7200PMU_BASE		= 0x12000;
	const TUint KL7200PMUSys_Config_Current = 0x000;
	const TUint KL7200PMUSys_Config_Next	= 0x004;
	const TUint KL7200PMUSys_Config_Run		= 0x00C;
	const TUint KL7200PMUSys_Config_Comm	= 0x010;
	const TUint KL7200PMUSys_Config_Sdram	= 0x014;
	const TUint KL7200PMUSys_Clock_Enable	= 0x030;
	const TUint KL7200PMUSys_Clock_Esync	= 0x034;
	const TUint KL7200PMUSys_Clock_Select	= 0x038;
	const TUint KL7200PMUSys_Status			= 0x040;
	const TUint KL7200PMUSys_Stat_Clr		= 0x044;
	const TUint KL7200PMUSys_Reset_Remap	= 0x048;
	const TUint KL7200PMUSys_Int_Ctlr		= 0x04C;
	const TUint KL7200PMUSys_ID				= 0x050;

	// peripheral dma controller base
	const TUint KL7200PeriphDmaController_Base		= 0xe000;
	//
	const TUint KL7200PeriphDmaController_EN		= 0x00;
	const TUint KL7200PeriphDmaController_TERM		= 0x04;
	const TUint KL7200PeriphDmaController_BZ		= 0x08;
	const TUint KL7200PeriphDmaController_UR		= 0x0c;
	const TUint KL7200PeriphDmaController_ISR		= 0x10;
	const TUint KL7200PeriphDmaController_ICR		= 0x14;
	const TUint KL7200PeriphDmaController_IER		= 0x18;
	const TUint KL7200PeriphDmaController_SBR		= 0x1c;
	const TUint KL7200PeriphDmaController_RCM1		= 0x20;
	const TUint KL7200PeriphDmaController_RCM2		= 0x24;
	//
	const TUint KL7200PeriphDmaController_C0Start	= 0x100;
	const TUint KL7200PeriphDmaController_C1Start	= 0x120;
	const TUint KL7200PeriphDmaController_C2Start	= 0x140;
	const TUint KL7200PeriphDmaController_C3Start	= 0x160;
	const TUint KL7200PeriphDmaController_C4Start	= 0x180;
	const TUint KL7200PeriphDmaController_C5Start	= 0x1a0;
	const TUint KL7200PeriphDmaController_C6Start	= 0x1c0;
	const TUint KL7200PeriphDmaController_C7Start	= 0x1e0;
	//
	const TUint KL7200PeriphDmaController_CNBAOffset= 0x00;
	const TUint KL7200PeriphDmaController_CNTCOffset= 0x04;
	const TUint KL7200PeriphDmaController_CSBAOffset= 0x08;
	const TUint KL7200PeriphDmaController_CSTCOffset= 0x0c;
	const TUint KL7200PeriphDmaController_CCBAOffset= 0x10;
	const TUint KL7200PeriphDmaController_CCTCOffset= 0x14;
	const TUint KL7200PeriphDmaController_CPAOffset	= 0x18;
	const TUint KL7200PeriphDmaController_CCTLOffset= 0x1c;
	//
	const TInt KL7200DmaChannelCount = 8;

// Constants for UCB1200
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


enum TInterruptSource
		{
		EInterruptNone=-1,
		EInterruptSTWDOG=0,
		EInterruptProgIRQ,
		EInterruptCommRx,
		EInterruptCommTx,
		EInterruptGCTC1IRQ,
		EInterruptGCTC2IRQ,
		EInterruptDMAC0IRQ,
		EInterruptCLCDIRQ,
		EInterruptSMRXREADIRQ,
		EInterruptSMTXTIDEIRQ,
		EInterruptSMRESTIRQ,
		EInterruptSIBIRQ,
		EInterruptMMCIRQ,
		EInterruptSSP1IRQ,
		EInterruptSSP2IRQ,
		EInterruptSPIIRQ,
		EInterruptU1IRQ,
		EInterruptU2IRQ,
		EInterruptIrDAIRQ,
		EInterruptRTCTICKIRQ,
		EInterruptRTCALARMIRQ,
		EInterruptGPIOIRQ,
		EInterruptGDMA_IRQ,
		EInterruptM2MIRQ,
		EInterruptReserved,
		EInterruptnINTF,
		EInterruptnINT0,
		EInterruptnINT1, 
		EInterruptnINT2,
		EInterruptnINT3,
		EInterruptBLINT,
		EInterruptMCINT,
		EInterruptDMAC1IRQ,
		EInterruptDMAC2IRQ,
		EInterruptDMAC3IRQ,
		EInterruptDMAC4IRQ,
		EInterruptDMAC5IRQ,
		EInterruptDMAC6IRQ,
		EInterruptDMAC7IRQ
		};

enum TDmaChannel
		{
		EDmaChannel0=0x00,
		EDmaChannel1,
		EDmaChannel2,
		EDmaChannel3,
		EDmaChannel4,
		EDmaChannel5,
		EDmaChannel6,
		EDmaChannel7
		};

enum TDmaRequest
		{
		EChannelOff		=0x00,
		EAudioCodecRx	=0x01,
		EAudioCodecTx	=0x02,
		ETelCodecRx		=0x03,
		ETelCodecTx		=0x04,
		ESSPMaster1Rx	=0x05,
		ESSPMaster1Tx	=0x06,
		ESSPMaster2Rx	=0x07,
		ESSPMaster2Tx	=0x08,
		ESPISlaveRx		=0x09,
		ESPISlaveTx		=0x0a,
		EUart1Rx		=0x0b,
		EUart1Tx		=0x0c,
		EUart2Rx		=0x0d,
		EUart2Tx		=0x0e,
		EIrdaRx			=0x0f,
		EIrdaTx			=0x10,
		EM2MWrite		=0x11,
		EM2MRead		=0x12,
		EGPIODmaRx		=0x13,
		EGPIODmaTx		=0x14,
		EMmcRx			=0x15,
		EMmcTx			=0x16
		};


class TL7200
    {
public:
    enum TKeyDriveMode
        {
        EKeyDriveModeAllHigh,
        EKeyDriveModeAllLow,
        EKeyDriveModeAllTri,
        EKeyDriveModeSingleColumn
        };
    enum TSpiFrequency
        {
        ESpiFrequency8KHz=0x00000000,
        ESpiFrequency32KHz=0x00010000,
        ESpiFrequency128KHz=0x00020000,
        ESpiFrequency256KHz=0x00030000
        };
    enum TLcdId
        {
        ELcdIdNormal
        };
    enum TChipSelect
        {
        EChipSelect0=0,
        EChipSelect1=8,
        EChipSelect2=16,
        EChipSelect3=24,
        EChipSelect4=32,
        EChipSelect5=40,
        EChipSelect6=48,
        EChipSelect7=56
        };
    enum TBusWidth
        {
        EBusWidth32=0x00,
        EBusWidth16=0x01,
        EBusWidth8=0x02,
        EBusWidthPCMCIA=0x03
        };
    enum TRanWaitState
        {
        ERanWaitState4=0x00,
        ERanWaitState3=0x04,
        ERanWaitState2=0x08,
        ERanWaitState1=0x0C
        };
    enum TSeqWaitState
        {
        ESeqWaitState3=0x00,
        ESeqWaitState2=0x10,
        ESeqWaitState1=0x20,
        ESeqWaitState0=0x30
        };
    enum TSeqMode
        {
        ESequentialModeOff=0x00,
        ESequentialModeOn=0x40
        };
    enum TExpClock
        {
        EExpClockOff=0x00,
        EExpClockOn=0x80
        };
	enum TLcdType					// (Values for LCDCON, actually 2bpp)
        {
        ELcd640x240	=0x5814e95f,
        ELcd640x200	=0x581ce7cf,
		ELcd320x240	=0x5a2a64af,
		ELcd320x200	=0x5a3a63E7
        };
    enum TBitsPerPixel
        {
        EBitsPerPixel1=0,
        EBitsPerPixel2=1,
        EBitsPerPixel4=3
        };
    enum TPumpType
        {
        EPumpType0Battery=0,
        EPumpType0Mains=4,
        EPumpType1=8
        };
    enum TBaudRate
        {
        EBaudRate115200=0x001,
        EBaudRate76800=0x002,
        EBaudRate57600=0x003,
        EBaudRate38400=0x005,
        EBaudRate19200=0x00B,
        EBaudRate14400=0x00F,
        EBaudRate9600=0x017,
        EBaudRate4800=0x02F,
        EBaudRate2400=0x05F,
        EBaudRate1200=0x0BF,
        EBaudRate600=0x17F,
        EBaudRate300=0x2FF,
        EBaudRate150=0x5FF,
        EBaudRate110=0x82E
        };
    enum TBreak
        {
        EBreakOff=0x00000000,
        EBreakOn=0x00001000
        };
    enum TParity
        {
        EParityNone=0x00000000,
        EParityOdd=0x00002000,
        EParityEven=0x00006000
        };
    enum TStopBit
        {
        EStopBitOne=0x00000000,
        EStopBitTwo=0x00008000
        };
    enum TFifo
        {
        EFifoOff=0x00000000,
        EFifoOn=0x00010000
        };
    enum TDataLength
        {
        EDataLength5=0x00000000,
        EDataLength6=0x00020000,
        EDataLength7=0x00040000,
        EDataLength8=0x00060000
        };
    enum TGreyScale
        {
        EGreyScale0=0,
        EGreyScale1=4,
        EGreyScale2=8,
        EGreyScale3=12,
        EGreyScale4=16,
        EGreyScale5=20,
        EGreyScale6=24,
        EGreyScale7=28,
        EGreyScale8=32,
        EGreyScale9=36,
        EGreyScale10=40,
        EGreyScale11=44,
        EGreyScale12=48,
        EGreyScale13=52,
        EGreyScale14=56,
        EGreyScale15=60
        };
    enum TSpiClock
        {
        ESpiClockOff=0x0000,
        ESpiClockOn=0x2000
        };
public:

	static TInt aRTCOffset; // Offset for Current time from RTC.
    
	IMPORT_C static void SetKeyDriveMode(TKeyDriveMode aKeyDriveMode,TInt aColumn=0);
	IMPORT_C static void SetExtendedPort(TUint8 aValue);
//    IMPORT_C static void SetSpiFrequency(TSpiFrequency aFrequency);
//    IMPORT_C static TLcdId LcdId();
    IMPORT_C static TInt RtcTickCount();
//    IMPORT_C static TInt CpuVersionId();
//    IMPORT_C static void SetChipSelectConfig(TChipSelect aChipSelect,TBusWidth aWidth,TRanWaitState aRan,TSeqWaitState aSeq,TSeqMode aMode,TExpClock aClock);
//    IMPORT_C static void SetDramRefresh(TInt aValue);
//    IMPORT_C static void SetLcdType(TLcdType anLcdType);
//    IMPORT_C static void SetGreyScale(TBitsPerPixel aNumber);
//    IMPORT_C static void SetPump(TPumpType aPump,TInt aValue);
    IMPORT_C static void SetTimer1Data(TUint aValue);
    IMPORT_C static TUint Timer1Data();
    IMPORT_C static void SetTimer2Data(TUint aValue);
    IMPORT_C static TUint Timer2Data();
    IMPORT_C static void SetRtcData(TUint aValue);
    IMPORT_C static TUint RtcData();
    IMPORT_C static void SetRtcMatch(TUint aValue);
    IMPORT_C static TUint RtcMatch();
//    IMPORT_C static void SetCodecData(TUint aValue);
//    IMPORT_C static TUint CodecData();
    IMPORT_C static void SetUartData(TUint aValue);
    IMPORT_C static TUint UartData();
    IMPORT_C static void SetUartConfig(TBaudRate aRate,TParity aParity,TStopBit aStopBit,TDataLength aDataLength);
    IMPORT_C static TBaudRate UartBaudRate();
    IMPORT_C static TParity UartParity();
    IMPORT_C static TStopBit UartStopBit();
    IMPORT_C static TDataLength UartDataLength();
    IMPORT_C static void SetUartBreak(TBreak aBreak);
    IMPORT_C static TBreak UartBreak();
    IMPORT_C static void SetUartFifo(TFifo aFifo);
    IMPORT_C static TFifo UartFifo();
//    IMPORT_C static void SetSpiClock(TSpiClock anSpiClock);
//    IMPORT_C static void RequestSpiSample(TInt aFrameLength,TInt aConfig);
//    IMPORT_C static TUint SpiSample();
//    IMPORT_C static void SetPalette(TGreyScale aGreyScale, TInt aValue);
	IMPORT_C static void BootWaitMilliSeconds(TInt aDuration);
//
	IMPORT_C static TInt TestReg8(TUint aDevice, TUint aRegister, TUint aMask);
	IMPORT_C static TInt SetReg8(TUint aDevice, TUint aRegister, TUint aValue);
	IMPORT_C static TInt GetReg8(TUint aDevice, TUint aRegister);
	IMPORT_C static void SendStringL(TUint aLength, const char *s);
	IMPORT_C static void SendString(const char *s);
	IMPORT_C static void SendCharacter(TUint aChar);

// KAH - NOTE - all E4 references changed to E8	
    IMPORT_C static TUint PortA8();
    IMPORT_C static TUint PortB8();
    IMPORT_C static TUint PortC8();
    IMPORT_C static TUint PortD8();
    IMPORT_C static TUint PortE8();
    IMPORT_C static void SetPortA8(TUint aValue);
    IMPORT_C static void SetPortB8(TUint aValue);
    IMPORT_C static void SetPortC8(TUint aValue);
    IMPORT_C static void SetPortD8(TUint aValue);
    IMPORT_C static void SetPortE8(TUint aValue);
    IMPORT_C static void ModifyPortA8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortB8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortC8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortD8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyPortE8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrA8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrB8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrC8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrD8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void ModifyDdrE8(TUint aClearMask,TUint aSetMask);
    IMPORT_C static void SetDdrA8(TUint aValue);
    IMPORT_C static void SetDdrB8(TUint aValue);
    IMPORT_C static void SetDdrC8(TUint aValue);
    IMPORT_C static void SetDdrD8(TUint aValue);
    IMPORT_C static void SetDdrE8(TUint aValue);
    IMPORT_C static TUint IntStatusFIQ32();
    IMPORT_C static TUint IntStatusIRQ32();
    IMPORT_C static TUint IntRawStatusFIQ32();
    IMPORT_C static TUint IntRawStatusIRQ32();
    IMPORT_C static void ModifyIntMaskIRQ32E(TUint aMask);
    IMPORT_C static void ModifyIntMaskIRQ32D(TUint aMask);
    IMPORT_C static void ModifyIntMaskFIQ32E(TUint aMask);
    IMPORT_C static void ModifyIntMaskFIQ32D(TUint aMask);
	IMPORT_C static TMachineStartupType StartupReason();
    IMPORT_C static void SetStartFlagClear();
    IMPORT_C static void SetBatteryLowEOI();
    IMPORT_C static void SetMediaChangedEOI();
    IMPORT_C static void SetTickSOI();
    IMPORT_C static void SetTickEOI();
    IMPORT_C static void SetTimer1SOI();
    IMPORT_C static void SetTimer1EOI();
    IMPORT_C static void SetTimer2SOI();
    IMPORT_C static void SetTimer2EOI();
    IMPORT_C static void StopTimer1();
    IMPORT_C static void StopTimer2();
    IMPORT_C static void SetRtcMatchEOI();
    IMPORT_C static void SetUartEOI();
    IMPORT_C static void SetCodecEOI();
    IMPORT_C static void SetHalt();
    IMPORT_C static void SetStandby();

	// dma controller
	IMPORT_C static void DmaEnable(TDmaChannel aChannel);
	IMPORT_C static void DmaTerminate(TDmaChannel aChannel);
	IMPORT_C static TBool IsDmaBusy(TDmaChannel aChannel);
	IMPORT_C static TBool IsDmaUnderrun(TDmaChannel aChannel);
	IMPORT_C static void DmaSetSyncBypass(TDmaChannel aChannel);
	IMPORT_C static void DmaClearSyncBypass(TDmaChannel aChannel);
	IMPORT_C static TBool IsDmaSyncBypass(TDmaChannel aChannel);
	IMPORT_C static void DmaIntEnable(TDmaChannel aChannel);
	IMPORT_C static TBool DmaIntDisable(TDmaChannel aChannel);
	IMPORT_C static TUint8 DmaIntMask();
	IMPORT_C static void DmaIntClear(TDmaChannel aChannel);
	IMPORT_C static TUint8 DmaIntStatus();
	IMPORT_C static TInt DmaIrqRequest();
	IMPORT_C static TUint32 DmaMapping1(); 
	IMPORT_C static TUint32 DmaMapping2();
	IMPORT_C static void DmaSetMapping(TDmaChannel aChannel,TDmaRequest aReq);
	IMPORT_C static void DmaSetNextBuffAddr(TDmaChannel aChannel,TPhysAddr aAddr);
	IMPORT_C static void DmaSetNextTransferCount(TDmaChannel aChannel,TInt aCount);
	IMPORT_C static void DmaSetPeriphAddr(TDmaChannel aChannel, TPhysAddr aAddr);
	IMPORT_C static TUint32 DmaPeriphAddress(TDmaChannel aChannel);
	IMPORT_C static void DmaSetControl(TDmaChannel aChannel,TUint aVal);
	IMPORT_C static TUint32 DmaControl(TDmaChannel aChannel);
	IMPORT_C static TUint32 DmaCurrentBufferAddress(TDmaChannel aChannel);
	IMPORT_C static TUint32 DmaCurrentTransferCount(TDmaChannel aChannel);

    static void Init3();
    };

#endif

