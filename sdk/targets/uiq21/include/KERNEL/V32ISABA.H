// V32ISABA.H
//
// Copyright (c) 1998 - 2001 Symbian Ltd.  All rights reserved.
//

//
// Variant layer headers for Brutus
//


#ifndef __V32ISABA_H__
#define __V32ISABA_H__
#include <e32std.h>
#include <e32pccd.h>
#include <v32sa1100.h>
#include <m32std.h>


//----------------------------------------------------------------------------
// Variant-specific constants: use #define if constant dependencies are not
// declared within this file (this breaks the dependency on other header files)
//----------------------------------------------------------------------------
// General-purpose I/O allocation

// SA-1100
#define KtVariantGpio32KHzClkOut		KHtGpioPort27
#define KtVariantGpioRClkOut			KHtGpioPort26
#define KtVariantGpioKeyCntrlAtn		KHtGpioPort25 // Sorted
#define KtVariantGpioKeyCntrlWkuOnly	KHtGpioPort24 // Sorted
#define KtVariantGpioKeyCntrlWakeup		KHtGpioPort23 // Sorted
#define KtVariantGpioCard_b_fault		KHtGpioPort22
// #define KtVariantGpioCard_a_fault		KHtGpioPort21
#define KtVariantGpioIrdaSd				KHtGpioPort21
#define KtVariantGpioDsr				KHtGpioPort20
#define KtVariantGpioDtr				KHtGpioPort19
#define KtVariantGpioDcd				KHtGpioPort18
#define KtVariantGpioRts				KHtGpioPort17
#define KtVariantGpioCts				KHtGpioPort16
#define KtVariantGpioKint				KHtGpioPort15
#define KtVariantGpioNmi_sleep			KHtGpioPort14
#define KtVariantSspSfrm				KHtGpioAltSspsfrm_o		// KHtGpioPort13 Sorted
#define KtVariantSspSclk				KHtGpioAltSspsclk_o		// KHtGpioPort12 Sorted
#define KtVariantSspRx					KHtGpioAltSsprxd_i		// KHtGpioPort11 Sorted
#define KtVariantSspTx					KHtGpioAltSsptxd_o		// KHtGpioPort10 Sorted
#define KtVariantGpioLedGrn1			KHtGpioPort9
#define KtVariantGpioLedGrn0			KHtGpioPort8
#define KtVariantGpioPcCard1Cd			KHtGpioPort7
#define KtVariantGpioPcCard1RdyIReq		KHtGpioPort6
#define KtVariantGpioPcCard1StsChg		KHtGpioPort5
#define KtVariantGpioPcCard0Cd			KHtGpioPort4
#define KtVariantGpioPcCard0RdyIReq		KHtGpioPort3
#define KtVariantGpioPcCard0StsChg		KHtGpioPort2
#define KtVariantGpioWakeupsa			KHtGpioPort1
#define KtVariantGpioBettyint			KHtGpioPort0

// Define initial GPIO data states (1=set, 0=clear)
#define KmVariantGpioInitData			(KtVariantGpioKeyCntrlWakeup|KtVariantGpioLedGrn1|KtVariantGpioLedGrn0)

// Define initial GPIO directions (1=output, 0=input)
#define KmVariantGpioInitDdr			(KtVariantGpioKeyCntrlWakeup|KtVariantSspSfrm|KtVariantSspSclk|\
										 KtVariantSspTx|KtVariantGpioLedGrn1|KtVariantGpioLedGrn0)
// Define GPIO sleep states
#define KmVariantGpioSleepData			0	//!!!

// Define GPIO alternative functions
#define KmVariantGpioAlt				(KHtGpioAltSspsfrm_o|\
										 KHtGpioAltSspsclk_o|\
										 KHtGpioAltSsprxd_i|\
										 KHtGpioAltSsptxd_o|)

//----------------------------------------------------------------------------
// Peripheral pin controller (data: pages 292-302)

// Available peripheral pins (1=available, 0=in use by module)
// NB this can be read at run-time using ~TSa1100::PpcAllocated()
#define KmVariantPpcGpio				0	//!!!

// Sleep-mode DDR for peripheral pins (1=output, 0=input)
#define KmVariantPpcSleepDdr			0	//!!!

//----------------------------------------------------------------------------
// DC-DC pumps


//----------------------------------------------------------------------------
// Reset control
//----------------------------------------------------------------------------
// Power management

// Wake-up-enabled pins
#define KmVariantPwrWakeEnable			(KHtPwrPwerRtcAlarm|KtVariantGpioWakeupsa|KtVariantGpioBettyint)

//----------------------------------------------------------------------------
// Memory

// ROM (flash) wait states
#define     KwVariantRom0Type			TSa1100::ERomTypeNoBurstFlash
#define     KwVariantRom0Width			TSa1100::ERomWidth32
const TUint KwVariantRom0WaitNs			= 150;
const TUint KwVariantRom0PageNs			= 150;
const TUint KwVariantRom0RecoverNs		= 120;

#define     KwVariantRom1Type			TSa1100::ERomTypeNoBurstFlash
#define     KwVariantRom1Width			TSa1100::ERomWidth32
const TUint KwVariantRom1WaitNs			= 150;
const TUint KwVariantRom1PageNs			= 150;
const TUint KwVariantRom1RecoverNs		= 120;

//----------------------------------------------------------------------------
// O/S timers

//----------------------------------------------------------------------------
// Real-time clock

//----------------------------------------------------------------------------
// Keyboard

const TUint KwVariantKeyColLshift		= 7;
const TUint KwVariantKeyRowLshift		= 64;
const TUint KwVariantKeyColRshift		= 6;
const TUint KwVariantKeyRowRshift		= 64;

//----------------------------------------------------------------------------
// LCD

const TUint KwVariantLcdLogicWait		= 5;
const TUint KwVariantLcdSoftPump		= 4;
const TUint KwVariantLcdSoftPumpWait	= 5;
const TUint KwVariantLcdHardPump		= 11;
const TUint KwVariantLcdHardPumpWait	= 10;

// Settings for Passive Colour Single Panel 320x240 Display
#define     KwVariantLcdBpp				TSa1100::ELcd8BitsPerPixel
const TUint KwVariantLcdMaxColors		= 4096;
#define     KwVariantLcdMode			TSa1100::ELcdModePassiveColor
#define     KwVariantLcdPanel			TSa1100::ELcdSinglePanel
#define     KwVariantLcdGender			TSa1100::ELcdmemoryLittleEndian
const TUint KwVariantLcdWidth			= 320;
const TUint KwVariantLcdHeight			= 240;
const TUint KwVariantLcdPixelClkPeriodInNS=259;
const TUint KwVariantLcdDmaDelay		= 0;
const TUint KwVariantLcdDelayLeft		= 10200;	// 10.2uS
const TUint KwVariantLcdDelayRight		= 25700;	// 25.7uS
const TUint KwVariantLcdDelayTop		= 0;		// Disable in passive mode (BFW)
const TUint KwVariantLcdDelayBot		= 0;		// Disable in passive mode (EFW)
const TUint KwVariantLcdHsyncWidth		= 300;		// 300nS
const TUint KwVariantLcdVsyncWidth		= 0;		// 1 line clock (VSW)
const TUint KwVariantLcdAcBiasFreq		= 255;		// Generated by panel so max. to reduce pwr.
const TUint KwVariantLcdAcBiasTpi		= 0;		// Disable for now
#define     KwVariantLcdPolVsync		TSa1100::EPolarityActiveHigh
#define     KwVariantLcdPolHsync		TSa1100::EPolarityActiveHigh
#define     KwVariantLcdEdgePixClk		TSa1100::EEdgeRising
#define     KwVariantLcdPolOe			TSa1100::EPolarityActiveHigh

const TUint KPaletteEntryWhite			= 0xFFF;

//----------------------------------------------------------------------------
// UARTs

#define     KwVariantUartBaseDebug		KHwBaseSerial3

//----------------------------------------------------------------------------
// CODEC
const TUint KwVariantCodecMaxVolume		= 0;

//----------------------------------------------------------------------------
// Interrupts

//----------------------------------------------------------------------------

class Variant : public Custom
	{
public:
	enum TVisabaPanic
		{
		EKeyboardControllerTxFull
		};
	static void Panic(TVisabaPanic aPanic);
	virtual void Init1();
	virtual void Init2();
	virtual void Init3();
    virtual void Init4();
    virtual void Init5();
	virtual TInt DebugInit();
	virtual void DebugOutput(TUint aLetter);
	virtual TPtrC8 ExtInterruptSource();
	virtual TInt EnableExtInterrupt(TExtInterruptID anId);
	virtual TInt DisableExtInterrupt(TExtInterruptID anId);
	virtual TInt ClearExtInterrupt(TExtInterruptID anId);
	virtual TExtInterruptID ActiveExtInterrupt();
	virtual void PowerReset();
	virtual TBool TestBootSequence();
	virtual TBool PointerSwitchesOn();
	virtual void EnablePointerSwitchOn();
	virtual void DisablePointerSwitchOn();
	virtual void StartupReason(TMachineStartupType &aReason);
	virtual void WokeUp();
	virtual void ApplyBackupBatteryLoad();
	virtual void RemoveBackupBatteryLoad();
	virtual void QuickEmergencyStandby();
	virtual TBool EmergencyStandby();
	virtual TInt ProcessorClockInKHz();
	virtual TInt SpeedFactor();
	virtual TInt MainBatteryMaxMilliVolts();
	virtual TInt BackupBatteryMaxMilliVolts();
	virtual TInt IdleCurrentInMilliAmps();
	virtual TInt RunningCurrentInMilliAmps();
	virtual TSize XYInputSize();
 	virtual TBool XYInputPresent();
	virtual TPoint OffsetToDisplayInPixels();
	virtual TTimeIntervalMicroSeconds32 TickPeriod();
	virtual TInt MainBatteryInMilliVolts(TInt aReading,TInt aReference);
	virtual TInt BackupBatteryInMilliVolts(TInt aReading,TInt aReference);
	virtual TInt PcCardInMilliVolts(TInt aReading,TInt aReference);
	virtual TInt DcJackInMilliVolts(TInt aReading,TInt aReference);
	virtual TInt MainBatteryLowInMilliVolts();
	virtual TInt MainBatteryReplaceInMilliVolts();
	virtual TInt MainBatteryNotPresentInMilliVolts();
	virtual TInt BackupBatteryGoodToLowInMilliVolts();
	virtual TInt BackupBatteryLowToGoodInMilliVolts();
	virtual TInt BackupBatteryLowToReplaceInMilliVolts();
	virtual TInt BackupBatteryReplaceToLowInMilliVolts();
	virtual TInt BackupBatteryNotPresentInMilliVolts();
	virtual TBool ExternalPowerPresent();
	virtual TSupplyStatus MainBatteryStatus();
	virtual TInt MainBatteryMilliVolts();
	virtual TSupplyStatus BackupBatteryStatus();
	virtual TInt BackupBatteryMilliVolts();
    // Drive Info
	virtual TInt TotalSupportedDrives();
	virtual TLDriveAssignInfo DeviceInfoFromDrive(TInt aDriveNumber);
	virtual TMediaDevice DeviceFromMedia(TInt aMediaNumber);
	virtual TMediaDeviceAssignInfo MediaInfoFromDevice(TMediaDevice aDevice);
	virtual TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice);
	virtual TInt DriveSettings();
private:
	TBool iPointerSwitchesOn;
	};

#endif

