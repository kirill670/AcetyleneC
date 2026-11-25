// A32TEMPLATEASSP.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

//
// This file is part of the Template Base port
//
// This declares the ASSP access class (TTemplateASSP), which is
// used to protect the code from direct access to hardware addresses
//
// TTemplateASSP provides various functions through which the hardware
// is accessed. This also allows the variant layer to link to the
// kernel and use TTemplateASSP for hardware access.
//
// The class defined here is not intended to represent any real hardware,
// it is just a simple example of what an ASSP class might look like.
//

#ifndef __A32TEMPLATEASSP_H__
#define __A32TEMPLATEASSP_H__
#include <e32std.h>
#include <k32std.h>

/**
 * TO DO: (mandatory)
 * Each interrupt must have a name by which other code refers to it
 */
_LIT8(KFiqBatteryLow, "FiqBatteryLow");
_LIT8(KFiqWatchdog, "FiqWatchdog");
_LIT8(KIrqTimer1, "IrqTimer1");
_LIT8(KIrqTimer2, "IrqTimer2");
_LIT8(KIrqSerial1, "IrqSerial1");
_LIT8(KIrqSerial2, "IrqSerial2");
_LIT8(KIrqKeypress, "IrqKeypress");
_LIT8(KIrqDma1, "IrqDma1");
_LIT8(KIrqDma2, "IrqDma2");
_LIT8(KIrqDigitiser, "IrqDigitiser");
_LIT8(KIrqGeneralEdge, "IrqGeneralEdge");
_LIT8(KIrqFir, "IrqFir");
_LIT8(KIrqExt0, "IrqExt0");
_LIT8(KIrqExt1, "IrqExt1");

/**
 * TTemplateASSP class
 */
class TTemplateASSP
	{
public:

	//
	// Various public enumerated values
	//
	// None of the values here represent any real hardware, they are just
	// to give an example of what you might need to provide
	//

	enum TTimerMode
		{
		ETimerModeIdle,
		ETimerModeFreeRunning
		};

	enum TInterruptSources
		{
		EIntTimer1 = 0x1,
		EIntTimer2 = 0x2,
		EIntUart1 = 0x4,
		EIntUart2 = 0x8,
		EIntRtcMatch = 0x40,
		EIntEdge = 0x80,
		EIntLowBattery = 0x40000000,
		EIntWatchdog = 0x80000000
		};
	
	enum TDmaChannel
		{
		EDmaChannel0,
		EDmaChannel1
		};

	enum { KNumDmaChannels = 2 };

	enum TDmaAction
		{
		EDmaIdle,
		EDmaRunning
		};

	enum TDmaInterruptMode
		{
		EDmaInterruptOff,
		EDmaInterruptOnComplete
		};

	enum TUartBase 
		{
		KHwUart0Base	= 0x58001800,
		KHwUart1Base	= 0x58001C00,
		};

	enum TUartBaud	
		{
		EBaud50     = 4596,
		EBaud75     = 3064,
		EBaud150    = 1532,
		EBaud300    = 768,
		EBaud600    = 384,
		EBaud1200   = 192,
		EBaud2400   = 96,
		EBaud4800   = 48,
		EBaud7200   = 32,
		EBaud9600   = 24,
		EBaud19200  = 12,
		EBaud38400  = 6,
		EBaud57600  = 4,
		EBaud115200 = 2,
		EBaud230400 = 1
		};

	enum TUartParity
		{
		EParityNone = 0x0,
		EParityOdd = 0x1,
		EParityEven = 0x3,
		EParityMark = 0x05,
		EParitySpace = 0x07
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
		EStopBits1=0x0, EStopBits2=0x1 //To get 1.5 stopbits you set #databits to 5 and #stopbits to 2
		};

	enum TUartOutLines
		{
		ERts = 0x1,
		EDtr = 0x2
		};

	enum TUartInLines
		{
		EDsr = 0x10,
		ECts = 0x20,
		EDcd = 0x40,
		ERi = 0x80
		};

	enum TUartIntFlags
		{
		EUartIntTx = 0x1,
		EUartIntRx = 0x2,
		EUartIntControlLines = 0x4
		};

	enum TUartErrorFlags
		{
		EUartErrNone = 0,
		EUartErrParity = 0x1,
		EUartErrFraming = 0x2,
		EUartErrOverrun = 0x4
		};

	enum TFirInterruptFlags
		{
		EFirIntFlagRx = 0x1,
		EFirIntFlagTx = 0x2
		};


public:
	//
	// Initialisation
	//
	static void Init3();

	//
	// Realtime Clock
	//
	IMPORT_C static TInt RtcData();
	IMPORT_C static void SetRtcMatch( TInt aCount );
	IMPORT_C static void SetRtc( const TTime& aTime );
	IMPORT_C static void GetRtc( TTime& aTime );
	IMPORT_C static TInt RtcTimeInMilliseconds();

	//
	// Timers
	//
	IMPORT_C static TUint32 Timer1Count();
	IMPORT_C static void SetTimer1Count( TUint32 aCount );
	IMPORT_C static void StartTimer1( TTimerMode aMode );
	IMPORT_C static void StopTimer1();

	IMPORT_C static TUint32 Timer2Count();
	IMPORT_C static void SetTimer2Count( TUint32 aCount );
	IMPORT_C static void StartTimer2( TTimerMode aMode );
	IMPORT_C static void StopTimer2();

	//
	// Interrupts
	//
	IMPORT_C static void EnableFiq( TInt aId );
	IMPORT_C static void DisableFiq( TInt aId );
	IMPORT_C static void EnableIrq( TInt aId );
	IMPORT_C static void DisableIrq( TInt aId );
	IMPORT_C static void EnableInterruptSource( TUint32 aEnableFlags );
	IMPORT_C static void DisableInterruptSource( TUint32 aDisableFlags );
	IMPORT_C static TBool IrqsPending();
	IMPORT_C static TBool FiqsPending();
	IMPORT_C static TBool IsIrqPending( TInt aId );
	IMPORT_C static TBool IsFiqPending( TInt aId );


	//
	// Our example DMA controller
	//
	IMPORT_C static void SetDmaAction( TInt aChannel, TDmaAction aAction );
	IMPORT_C static void SetDmaTransferSize( TInt aChannel, TUint32 aSize );
	IMPORT_C static void SetDmaSource( TInt aChannel, TUint32 aAddress );
	IMPORT_C static void SetDmaDest( TInt aChannel, TUint32 aAddress );
	IMPORT_C static void SetDmaSourceIncrement( TInt aChannel, TInt8 aIncrement );
	IMPORT_C static void SetDmaDestIncrement( TInt aChannel, TInt8 aIncrement );
	IMPORT_C static void SetDmaInterrupt( TInt aChannel, TDmaInterruptMode aMode );
	IMPORT_C static void SetDmaCount( TInt aChannel, TUint32 aCount );
	IMPORT_C static TUint32 DmaCount( TInt aChannel );
	IMPORT_C static TBool DmaFailed( TInt aChannel );

	//
	// Serial UARTs
	//

	IMPORT_C static void SetUartBaud( TUartBaud aBaud , TUint32 aPortBase );
	IMPORT_C static void SetUartParity( TUartParity aParity , TUint32 aPortBase );
	IMPORT_C static void SetUartDataBits( TUartDataBits aBits , TUint32 aPortBase );
	IMPORT_C static void SetUartStopBits( TUartStopBits aBits , TUint32 aPortBase );
	IMPORT_C static void SetUartOutputLines( TUint8 aClearFlags, TUint8 aSetFlags , TUint32 aPortBase );
	IMPORT_C static TUint8 UartInputLines( TUint32 aPortBase );
	IMPORT_C static TUint8 UartData( TUint32 aPortBase );
	IMPORT_C static void SetUartData( TUint8 aChar , TUint32 aPortBase );
	IMPORT_C static TBool UartRxFifoEmpty( TUint32 aPortBase );
	IMPORT_C static TBool UartTxFifoFull( TUint32 aPortBase );
	IMPORT_C static TBool UartTxInProgress( TUint32 aPortBase );
	IMPORT_C static void SetUartInterruptMask( TUint8 aClearFlags, TUint8 aSetFlags , TUint32 aPortBase );
	IMPORT_C static TUint8 UartInterruptFlags( TUint32 aPortBase );
	IMPORT_C static TUint8 UartErrorFlags( TUint32 aPortBase );
	IMPORT_C static void UartEnable( TUint32 aPortBase );
	IMPORT_C static void UartDisable( TUint32 aPortBase );

	static inline TUint32 DebugPortAddr();
	//
	// Fast IR
	//
	
	IMPORT_C static void FirEnable();
	IMPORT_C static void FirDisable();
	IMPORT_C static void FirRxEnable();
	IMPORT_C static void FirTxEnable();
	IMPORT_C static void FirRxDisable();
	IMPORT_C static void FirTxDisable();
	IMPORT_C static TUint8 FirData();
	IMPORT_C static void SetFirData( TUint8 aByte );
	IMPORT_C static TUint FirInterruptFlags();
	IMPORT_C static TBool FirRxFailed();
	IMPORT_C static TBool FirTxFailed();

	//
	// Battery
	//

	IMPORT_C static TBool BatteryChanged();
	IMPORT_C static TBool ExternalPowerPresent();
	IMPORT_C static TBool MainBatteryGood();
	IMPORT_C static TBool BackupBatteryGood();
	IMPORT_C static TInt MainBatteryVoltage();
	IMPORT_C static TInt BackupBatteryVoltage();

	//
	// Digitiser
	//
	
	IMPORT_C static TBool IsDigitiserPenDown();
	IMPORT_C static void StartDigitiserXConversion();
	IMPORT_C static void StartDigitiserYConversion();
	IMPORT_C static TBool DigitiserXConversionFinished();
	IMPORT_C static TBool DigitiserYConversionFinished();
	IMPORT_C static TInt DigitiserXData();
	IMPORT_C static TInt DigitiserYData();


	//
	// Miscellaneous stuff
	//
	IMPORT_C static void EnterIdle();
	IMPORT_C static void Sleep();
	IMPORT_C static void ResetWatchdog();
	IMPORT_C static TMachineStartupType StartupReason();

private:
	static TUint Register32(TUint aAddr);
	static void SetRegister32(TUint aValue,TUint aAddr);
	static void ModifyRegister32(TUint aClearMask,TUint aSetMask,TUint aAddr);
	static TUint8 Register8(TUint aAddr);
	static void SetRegister8(TUint8 aValue,TUint aAddr);
	static void ModifyRegister8(TUint8 aClearMask,TUint8 aSetMask,TUint aAddr);

private:
	//
	// addresses of I/O registers
	//
	enum THwAddresses
		{
		KHwRtcCount		= 0x58000000,
		KHwRtcMatch		= 0x58000004,
		KHwRtcYear		= 0x58000008,
		KHwRtcMonth		= 0x5800000C,
		KHwRtcDay		= 0x58000010,
		KHwRtcHour		= 0x58000014,
		KHwRtcMinute	= 0x58000018,
		KHwRtcSecond	= 0x5800001C,
		KHwRtcMillisecond = 0x58000020,

		KHwTimer1Count	= 0x58000400,
		KHwTimer1Match	= 0x58000404,
		KHwTimer1Mode	= 0x58000408,
		
		KHwTimer2Count	= 0x58000800,
		KHwTimer2Match	= 0x58000804,
		KHwTimer2Mode	= 0x58000808,

		KHwIntMask		= 0x58000C00,
		KHwIntFlags		= 0x58000C04,

		KHwDma0Base		= 0x58001000,
		KHwDma1Base		= 0x58001400,

		KHwFirControl = 0x58002000,
		KHwFirData = 0x58002004,
		KHwFirIntFlags = 0x58002008,

		KHwPowerFlags	= 0x58002400,
		KHwPowerMainVoltage	= 0x58002404,
		KHwPowerBackupVoltage = 0x58002408,

		KHwDigitiserControl	= 0x58002800,
		KHwDigitiserFlags	= 0x58002804,
		KHwDigitiserXData	= 0x58002808,
		KHwDigitiserYData	= 0x5800280C,

		KHwWatchdogCount = 0x58002C0C

		};

	enum TUartOffsets
		{
		KHwOffsetUartData	= 0x0,
		KHwOffsetUartMdmLines = 0x4,
		KHwOffsetUartBaud	= 0x8,
		KHwOffsetUartFlags	= 0xC,
		KHwOffsetUartIntMask = 0x10,
		KHwOffsetUartIntFlags = 0x14,
		KHwOffsetUartErrorFlags = 0x18,
		KHwOffsetUartDataBits = 0x1C,
		KHwOffsetUartStopBits = 0x20,
		KHwOffsetUartParity = 0x24,
		};

	enum TDmaOffsets
		{
		KHwOffsetDmaSource	= 0x00,
		KHwOffsetDmaDest	= 0x04,
		KHwOffsetDmaSrcInc	= 0x08,
		KHwOffsetDmaDestInc	= 0x0C,
		KHwOffsetDmaSize	= 0x10,
		KHwOffsetDmaCount	= 0x18,
		KHwOffsetDmaMode	= 0x1C
		};

	//
	// Some private constants
	//


	enum TDmaFlags
		{
		KDmaFlagRunning = 0x1,
		KDmaFlagInterrupt = 0x2,
		KDmaFlagError = 0x4
		};

	enum TUartFlags
		{
		KUartFlagRxFifoEmpty = 0x1,
		KUartFlagRxFifoFull = 0x2,
		KUartFlagTxFifoEmpty = 0x4,
		KUartFlagTxFifoFull = 0x8,
		KUartFlagTxActive = 0x10
		};

	enum FirControlFlags
		{
		KFirCtrlEnable = 0x1,
		KFirCtrlRxEnable = 0x2,
		KFirCtrlTxEnable = 0x3,
		KFirCtrlRxError = 0x40,
		KFirCtrlTxError = 0x80
		};
	
	enum TPowerFlags
		{
		KPowerFlagBatteryChanged,
		KPowerFlagExternalPresent,
		KPowerFlagMainGood,
		KPowerFlagBackupGood
		};

	enum TDigitiserFlags
		{
		KDigitiserFlagPenDown = 0x1,
		KDigitiserFlagXDone = 0x2,
		KDigitiserFlagYDone = 0x4
		};

	enum TDigitiserControl
		{
		KDigitiserControlStartX,
		KDigitiserControlStartY
		};


private:
	static const TUint32 dmaBase[KNumDmaChannels];
	};


/**
 Return base address of debug UART (as selected in obey file or with
 eshell debugport command).
 */

inline TUint32 TTemplateASSP::DebugPortAddr()
	{
	//
	// TO DO: (mandatory)
	//
	// Modify the code below to return the base address of the debug
	// UART.  
	//
	// The code below is just an example which assumes that the magic
	// cookie stored by rombuild in the ROM header and copied by the
	// bootstrap in the super page is the number of the port to use.
	// Each ASSP is free to choose a different semantic for that
	// field.
	// 

	// Default to UART 0 
	return (TheSuperPage().iDebugPort == 1) ? KHwUart1Base : KHwUart0Base;
	}

#endif

