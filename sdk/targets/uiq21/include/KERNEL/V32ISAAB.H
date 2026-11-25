// V32ISAAB.H
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//

//
// Variant layer headers for Assabet+CC card
//

#ifndef __V32ISAAB_H__
#define __V32ISAAB_H__
#include <e32std.h>
#include <e32pccd.h>
#include <v32sa1100.h>
#include <m32std.h>
#include "v32s1111.h"
#include "v32s1110.h"
#include "v32scpld1111.h"

//#define __USE_LEDS_FOR_SYSTEM_DEBUG

//----------------------------------------------------------------------------
// Variant-specific constants: use #define if constant dependencies are not
// declared within this file (this breaks the dependency on other header files)
//----------------------------------------------------------------------------
// General-purpose I/O allocation

// SA-1110
#define KtVariantGpio32KHzClkOut		KHtGpioPort27
#define KtVariantGpioRClkOut			KHtGpioPort26
#define KtVariantGpioSa1111Irq			KHtGpioPort25 // Sorted
#define KtVariantGpioGfxIrq				KHtGpioPort24 // Sorted
#define KtVariantGpioUcb1300Irq			KHtGpioPort23 // Sorted
#define KtVariantGpioSa1111Mbreq		KHtGpioPort22
#define KtVariantGpioSa1111Mbgnt		KHtGpioPort21
#define KtVariantGpioUart3Clk			KHtGpioPort20
#define KtVariantGpioStereo64Fs			KHtGpioPort19
#define KtVariantGpioL3I2cScl			KHtGpioPort18
#define KtVariantGpioL3Mode				KHtGpioPort17
#define KtVariantGpioPsMode				KHtGpioPort16
#define KtVariantGpioL3I2cSda			KHtGpioPort15
#define KtVariantGpioRadioIrq			KHtGpioPort14
#define KtVariantSspSfrm				KHtGpioAltSspsfrm_o		// KHtGpioPort13 Sorted
#define KtVariantSspSclk				KHtGpioAltSspsclk_o		// KHtGpioPort12 Sorted
#define KtVariantSspRx					KHtGpioAltSsprxd_i		// KHtGpioPort11 Sorted
#define KtVariantSspTx					KHtGpioAltSsptxd_o		// KHtGpioPort10 Sorted
#define KtVariantGpioLcdD15				KHtGpioPort9
#define KtVariantGpioLcdD14				KHtGpioPort8
#define KtVariantGpioLcdD13				KHtGpioPort7
#define KtVariantGpioLcdD12				KHtGpioPort6
#define KtVariantGpioLcdD11				KHtGpioPort5
#define KtVariantGpioLcdD10				KHtGpioPort4
#define KtVariantGpioLcdD9				KHtGpioPort3
#define KtVariantGpioLcdD8				KHtGpioPort2
#define KtVariantGpioOnOffSw2			KHtGpioPort1
#define KtVariantGpioOnOffSw1			KHtGpioPort0

// Define initial GPIO data states (1=set, 0=clear)
#define KmVariantGpioInitData			(KtVariantGpioL3Mode)			// D13 LED

// Define initial GPIO directions (1=output, 0=input)
#define KmVariantGpioInitDdr			(KtVariantGpioLcdD8|KtVariantGpioLcdD9|KtVariantGpioLcdD10|KtVariantGpioLcdD11|\
										 KtVariantGpioLcdD12|KtVariantGpioLcdD13|KtVariantGpioLcdD14|KtVariantGpioLcdD15|\
										 KtVariantSspTx|KtVariantSspSfrm|KtVariantGpioL3I2cSda|KtVariantGpioPsMode|\
										 KtVariantGpioL3Mode|KtVariantGpioL3I2cScl|KtVariantGpioSa1111Mbgnt|\
										 KtVariantGpio32KHzClkOut)		// 0x0827A7FC

// Define GPIO sleep states
#define KmVariantGpioSleepData			0	//!!!

// Define GPIO alternative functions
#define KmVariantGpioAlt				(KtVariantGpioLcdD8|KtVariantGpioLcdD9|KtVariantGpioLcdD10|KtVariantGpioLcdD11|\
										 KtVariantGpioLcdD12|KtVariantGpioLcdD13|KtVariantGpioLcdD14|KtVariantGpioLcdD15|\
										 KtVariantGpioSa1111Mbgnt|KtVariantGpioSa1111Mbreq|KtVariantGpio32KHzClkOut)\
										 // 0x086003FC


//----------------------------------------------------------------------------
// Peripheral pin controller (data: pages 11-168 to 11-178)

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
#define KmVariantPwrWakeEnable			(KHtPwrPwerRtcAlarm)

//----------------------------------------------------------------------------
// Memory

// ROM (flash) wait states - with Intel's 2MByte FlashFile (28F1603S3)
/*#define     KwVariantRom0Type			TSa1110::ERomTypeNoBurstFlash
#define     KwVariantRom0Width			TSa1110::ERomWidth32
const TUint KwVariantRom0WaitNs			= 110;
const TUint KwVariantRom0PageNs			= 110;
const TUint KwVariantRom0RecoverNs		= 30;

#define     KwVariantRom1Type			TSa1110::ERomTypeNoBurstFlash
#define     KwVariantRom1Width			TSa1110::ERomWidth32
const TUint KwVariantRom1WaitNs			= 110;
const TUint KwVariantRom1PageNs			= 110;
const TUint KwVariantRom1RecoverNs		= 30;*/

// ROM (flash) wait states - with Intel's 16MByte StrataFlash (28F128J3A)
#define     KwVariantRom0Type			TSa1110::ERomTypeBurst4Rom
#define     KwVariantRom0Width			TSa1110::ERomWidth32
const TUint KwVariantRom0WaitNs			= 150;
const TUint KwVariantRom0PageNs			= 30;
const TUint KwVariantRom0RecoverNs		= 120;

#define     KwVariantRom1Type			TSa1110::ERomTypeBurst4Rom
#define     KwVariantRom1Width			TSa1110::ERomWidth32
const TUint KwVariantRom1WaitNs			= 150;
const TUint KwVariantRom1PageNs			= 30;
const TUint KwVariantRom1RecoverNs		= 120;


//----------------------------------------------------------------------------
// O/S timers

//----------------------------------------------------------------------------
// Real-time clock

//----------------------------------------------------------------------------
// Keyboard

//----------------------------------------------------------------------------
// LCD

//----------------------------------------------------------------------------
// CODEC
const TUint KwVariantCodecMaxVolume		= 0;

//----------------------------------------------------------------------------
// Breakpoints
#define __BREAKPOINT	__ASSERT_ALWAYS((0) ,Variant::Panic(Variant::ESoftwareBreakPoint));	//breakpoint


//----------------------------------------------------------------------------
// Interrupts

#define IrqKbdCont			"IrqExt0"
#define IrqEthntCont		"IrqExt1"
#define IrqSspXmt			"IrqExt2"
#define IrqSspRcv			"IrqExt3"
#define IrqSspRor			"IrqExt4"
#define IrqAudXmtDmaDoneA	"IrqExt5"
#define IrqAudRcvDmaDoneA	"IrqExt6"
#define IrqAudXmtDmaDoneB	"IrqExt7"
#define IrqAudRcvDmaDoneB	"IrqExt8"
#define IrqAudTfsr			"IrqExt9"
#define IrqAudRfsr			"IrqExt10"
#define IrqAudTur			"IrqExt11"
#define IrqAudRor			"IrqExt12"
#define IrqAudDts			"IrqExt13"
#define IrqAudRdd			"IrqExt14"
#define IrqAudSto			"IrqExt15"
#define IrqUsbPwr			"IrqExt16"
#define IrqUsbHciM			"IrqExt17"
#define IrqUsbHciBuffAcc	"IrqExt18"
#define IrqUsbHciRmtWkp		"IrqExt19"
#define IrqUsbHciMfCir		"IrqExt20"
#define IrqUsbPortResume	"IrqExt21"
#define IrqPcCardS0Ready	"IrqExt22"
#define IrqPcCardS1Ready	"IrqExt23"
#define	IrqPcCardS0CdVal	"IrqExt24"
#define	IrqPcCardS1CdVal	"IrqExt25"
#define	IrqPcCardS0StChg	"IrqExt26"
#define	IrqPcCardS1StChg	"IrqExt27"

//----------------------------------------------------------------------------

class Variant : public Custom
	{
public:
	// Pen modes
	enum TVisabaPanic
		{
		EKeyboardControllerTxFull,
		EAudioDmaCountNotAligned,
		EAudioDmaAddressNotAligned,
		ECpld1111Init3OutOfMemory,
		ECpld1111Init3CreateChunk,
		ECpld1110Init3CreateChunk,
		ESa1111Init3OutOfMemory,
		ESa1111Init3CreateChunk,
		ESa1111NotIdentified,
		EDramConfigBadWriteRecovery,
		EDramConfigBadRows,
		EDramConfigBadRasPrechg,
		EDramConfigBadLatchTiming,
		EDramConfigBadRasCbr,
		EDramConfigBadRefresh,
		EStaticConfigBadDelayFirst,
		EStaticConfigBadDelayNext,
		EStaticConfigBadRecover,
		EStaticConfigBadChipSelect,
		EVariantContrastOutOfRange,
		EVariantBrightnessOutOfRange,
		ESoftwareBreakPoint,					// software breakpoint
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
	virtual void UpdateLeds(TUint aLedMask);
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
	virtual TBool IsFullKeyboard();
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

	// Miscellaneous - interface to HAL driver
	virtual void UpdateDebugLeds(TInt aMask);
	virtual TInt GetDebugLedsStatus();
	virtual TInt GetSwitches();
private:
	TBool iPointerSwitchesOn;
	TBool iBacklightOn;
	};

#endif

