// V32ARMLK.H
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __V32ARMLK_H__
#define __V32ARMLK_H__

#include <e32std.h>
#include <e32pccd.h>
#include <m32std.h>

#include <kc_arm.h>
#include <a32l7200.h>
#include <v32spi.h>

// Link-up Addresses and Constants
const TUint   KL7200PortAKeyRow=0x000000ff;

//                               
// Protea Rack D Hardware Addresses and constants
//

// The following will all need to change for Link-up - KAH

const TUint   KEigerPortBE2PromEnable=0x00000001;
const TUint   KEigerPortBE2PromClock=0x00000002;
const TUint   KEigerPortBDisplayContrast=0x0000003c;
const TUint   KEigerPortBCaseSwitchSense=0x00000040;
const TUint   KEigerPortBPcmciaVpcDisable=0x00000080;
const TUint   KEigerPortCRts=0x00000001;
const TUint   KEigerPortCDtr=0x00000002;
const TUint   KEigerPortCPowerLedDisable=0x00000004;
const TUint   KEigerPortCRs232Enable=0x00000008;
const TUint   KEigerPortCBacklightDetect=0x00000010;
const TUint   KEigerPortCBacklightOn=0x00000010;
const TUint   KEigerPortCIrRxEnable=0x00000020;
const TUint   KEigerPortCLoadBattery=0x00000040;
const TUint   KEigerPortCDictaphone=0x00000080;
const TUint   KEigerPortCE2PromSelectPRE=0x00000080;
const TUint   KEigerPortCCom2Enable=0x00000080;
const TUint   KEigerPortDCodecEnable=0x00000001;
const TUint   KEigerPortDAudioEnable=0x00000002;
const TUint   KEigerPortDLcdEnable=0x00000004;
const TUint   KEigerPortDCaseSwitchOnEnable=0x00000008;
const TUint   KEigerPortDAlarmLed=0x00000010;
const TUint   KEigerPortDFastChargeControl=0x00000020;
const TUint   KEigerPortDLcdLogicEnable=0x00000040;
const TUint   KEigerPortDPenDetectEnable=0x00000080;
const TUint   KEigerPortEDigitiser=0x0000000f;


const TInt KVariantPcCardAsicRevision=2;
//

//MAC220900
//
// These constants and the Custom class were previously taken from v32arm.h.

const TInt KMaxExtInterrupts=16;
const TUint8 KExtIntUnBound=0xFF;
const TInt KMemConfigByteAccess=1;

class Custom
	{
public:
    // Boot
    virtual void Init1()=0;
    virtual void Init2()=0;
    virtual void Init3()=0;
    virtual void Init4()=0;
    virtual void Init5()=0;
    virtual TBool TestBootSequence()=0;
	virtual TPtrC8 StartupBeep(TMachineStartupType aReason)=0;
    // Information
	virtual TPtrC MachineName()=0;
	virtual TPtrC DisplayName()=0;
	virtual TPtrC KeyboardName()=0;
	virtual TPtrC XYInputName()=0;
	virtual TPtrC PsuName()=0;
	virtual TBool XYInputPresent()=0;
	virtual TBool KeyboardPresent()=0;
	virtual TBool IsBacklightPresent()=0;
	virtual TSize DisplaySize()=0;
    virtual TSize XYInputSize()=0;
	virtual TSize PhysicalScreenSize()=0;
    virtual TPoint OffsetToDisplayInPixels()=0;
	virtual TInt KeyboardId()=0;
    virtual	TInt DisplayId()=0;
    virtual TInt UniqueId()=0;
    virtual TUint LedCapabilities()=0;
    virtual TPtrC ProcessorName()=0;
    virtual TInt ProcessorClockInKHz()=0;
    virtual TInt SpeedFactor()=0;
    virtual TInt MaximumDisplayColors()=0;
    virtual TTimeIntervalMicroSeconds32 TickPeriod()=0;
    virtual TInt LanguageIndex()=0;
    virtual TInt KeyboardIndex()=0;
    // Debug
    virtual void DebugInit()=0;
    virtual void DebugOutput(TUint aLetter)=0;
    // Power
    virtual void DisplayOn()=0;
    virtual void DisplayOff()=0;
    virtual void BacklightOn()=0;
    virtual void BacklightOff()=0;
    virtual void PowerReset()=0;
	virtual void WokeUp()=0;
    virtual void ApplyBackupBatteryLoad()=0;
    virtual void RemoveBackupBatteryLoad()=0;
    virtual void QuickEmergencyStandby()=0;
    virtual TBool EmergencyStandby()=0;
    virtual TInt MainBatteryInMilliVolts(TInt aReading,TInt aReference)=0;
    virtual TInt BackupBatteryInMilliVolts(TInt aReading,TInt aReference)=0;
    virtual TInt PcCardInMilliVolts(TInt aReading,TInt aReference)=0;
    virtual TInt DcJackInMilliVolts(TInt aReading,TInt aReference)=0;
    virtual TInt MainBatteryLowInMilliVolts()=0;
    virtual TInt MainBatteryReplaceInMilliVolts()=0;
    virtual TInt MainBatteryNotPresentInMilliVolts()=0;
    virtual TInt BackupBatteryGoodToLowInMilliVolts()=0;
    virtual TInt BackupBatteryLowToGoodInMilliVolts()=0;
    virtual TInt BackupBatteryLowToReplaceInMilliVolts()=0;
    virtual TInt BackupBatteryReplaceToLowInMilliVolts()=0;
    virtual TInt BackupBatteryNotPresentInMilliVolts()=0;
	virtual TInt IdleCurrentInMilliAmps()=0;
	virtual TInt RunningCurrentInMilliAmps()=0;
    virtual TInt MainBatteryMaxMilliVolts()=0;
    virtual TInt BackupBatteryMaxMilliVolts()=0;
	virtual TInt BacklightCurrentInMilliAmps()=0;
    // Display
    virtual TInt MaximumDisplayContrast()=0;
    virtual TInt InitialDisplayContrast()=0;
    virtual void SetDisplayContrast(TInt aValue)=0;
    // Peripheral Bus MediaChange
	virtual TPtrC8 MediaChangeIntSource(TInt aMediaChange)=0;
	virtual void ClearMediaChangeInt(TInt aMediaChange)=0;
	virtual TMediaState MediaState(TInt aMediaChange)=0;
    // Peripheral Bus general
    virtual void PeriphBusMachineInfo(TDes8* anInfo)=0;
	virtual TInt MediaChangeFromPeriphBus(TPBusNum aBus)=0;
	virtual TInt MediaChangeFromPrimaryPsu(TInt aPsuNum)=0;
    // Drive Info
	virtual TInt TotalSupportedDrives()=0;
	virtual TLDriveAssignInfo DeviceInfoFromDrive(TInt aDriveNumber)=0;
	virtual TMediaDevice DeviceFromMedia(TInt aMediaNumber)=0;
	virtual TMediaDeviceAssignInfo MediaInfoFromDevice(TMediaDevice aDevice)=0;
	virtual TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice)=0;
	virtual TInt DriveSettings()=0;
    // Machine control
    virtual void UpdateLeds(TUint aLedMask)=0;
    virtual TBool CaseClosed()=0;
    virtual void EnablePointerSwitchOn()=0;
    virtual void EnableCaseSwitchOn()=0;
    virtual void DisablePointerSwitchOn()=0;
    virtual void DisableCaseSwitchOn()=0;
    // Interrupts
	virtual TPtrC8 ExtInterruptSource()=0;
	virtual void EnableExtInterrupt(TExtInterruptID anId)=0;
	virtual void DisableExtInterrupt(TExtInterruptID anId)=0;
	virtual void ClearExtInterrupt(TExtInterruptID anId)=0;
	virtual TExtInterruptID ActiveExtInterrupt()=0;
    // Miscellaneous    
    virtual TInt BindSpiChannel(const TDesC8& aName)=0;
	virtual void StartupReason(TMachineStartupType &aReason)=0;
    virtual TBool EightChannelAdcFitted()=0;
	virtual TInt SetSoundDriverEnabled(TBool aState)=0;
	virtual TSpiController* CreateSpiController()=0;
	};

class Variant : public Custom
    {
public:
    Variant();
public:
    // Boot
    virtual void Init1();
    virtual void Init2();
    virtual void Init3();
    virtual void Init4();
    virtual void Init5();
    virtual TBool TestBootSequence();
	virtual TPtrC8 StartupBeep(TMachineStartupType aReason);
    // Information
	virtual TPtrC MachineName();
	virtual TPtrC DisplayName();
	virtual TPtrC KeyboardName();
	virtual TPtrC XYInputName();
	virtual TPtrC PsuName();
	virtual TBool XYInputPresent();
	virtual TBool KeyboardPresent();
	virtual TBool IsBacklightPresent();
	virtual TSize DisplaySize();
    virtual TSize XYInputSize();
	virtual TSize PhysicalScreenSize();
    virtual TPoint OffsetToDisplayInPixels();
	virtual TInt KeyboardId();
    virtual     TInt DisplayId();
    virtual TInt UniqueId();
    virtual TUint LedCapabilities();
    virtual TPtrC ProcessorName();
    virtual TInt ProcessorClockInKHz();
    virtual TInt SpeedFactor();
    virtual TInt MaximumDisplayColors();
    virtual TTimeIntervalMicroSeconds32 TickPeriod();
    virtual TInt LanguageIndex();
    virtual TInt KeyboardIndex();
    // Debug
    virtual void DebugInit();
    virtual void DebugOutput(TUint aLetter);
    // Power
    virtual void DisplayOn();
    virtual void DisplayOff();
    virtual void BacklightOn();
    virtual void BacklightOff();
    virtual void PowerReset();
	virtual void WokeUp();
    virtual void ApplyBackupBatteryLoad();
    virtual void RemoveBackupBatteryLoad();
    virtual void QuickEmergencyStandby();
    virtual TBool EmergencyStandby();
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
	virtual TInt IdleCurrentInMilliAmps();
	virtual TInt RunningCurrentInMilliAmps();
    virtual TInt MainBatteryMaxMilliVolts();
    virtual TInt BackupBatteryMaxMilliVolts();
	virtual TInt BacklightCurrentInMilliAmps();
    // Display
    virtual TInt MaximumDisplayContrast();
    virtual TInt InitialDisplayContrast();
    virtual void SetDisplayContrast(TInt aValue);
    // Peripheral Bus MediaChange
	virtual TPtrC8 MediaChangeIntSource(TInt aMediaChange);
	virtual void ClearMediaChangeInt(TInt aMediaChange);
	virtual TMediaState MediaState(TInt aMediaChange);
    // Peripheral Bus general
    virtual void PeriphBusMachineInfo(TDes8* anInfo);
	virtual TInt MediaChangeFromPeriphBus(TPBusNum aBus);
	virtual TInt MediaChangeFromPrimaryPsu(TInt aPsuNum);
    // Drive Info
	virtual TInt TotalSupportedDrives();
	virtual TLDriveAssignInfo DeviceInfoFromDrive(TInt aDriveNumber);
	virtual TMediaDevice DeviceFromMedia(TInt aMediaNumber);
	virtual TMediaDeviceAssignInfo MediaInfoFromDevice(TMediaDevice aDevice);
	virtual TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice);
	virtual TInt DriveSettings();				//MAC!
    // Machine control
    virtual void UpdateLeds(TUint aLedMask);
    virtual TBool CaseClosed();
    virtual void EnablePointerSwitchOn();
    virtual void EnableCaseSwitchOn();
    virtual void DisablePointerSwitchOn();
    virtual void DisableCaseSwitchOn();
    // Miscellaneous    
	virtual void StartupReason(TMachineStartupType &aReason);
	virtual TInt SetSoundDriverEnabled(TBool aState);

	// Following only required to satisfy the build process.
	// They are not implemented unless Link Up choose to do so.
	// KAH
	virtual TPtrC8 ExtInterruptSource();
	virtual void EnableExtInterrupt(TExtInterruptID anId);
	virtual void DisableExtInterrupt(TExtInterruptID anId);
	virtual void ClearExtInterrupt(TExtInterruptID anId);
	virtual TExtInterruptID ActiveExtInterrupt();
	virtual TInt BindSpiChannel(const TDesC8& aName);
	virtual TBool EightChannelAdcFitted();
	virtual TSpiController* Variant::CreateSpiController();

public:
	enum TVariantPanic
		{
	ELinkUpPanic0
	// define any platform specific panic numbers here. KAH
		};
    IMPORT_C static TInt MaximumVolume();
    IMPORT_C static void SetVolume(TInt aValue);
	static void Panic(TVariantPanic aPanic);
    };

// create a bitmask with a bitfield width and an amount to shift left
#define BIT_MASK(__bf) (((1U << (bw ## __bf)) - 1) << (bs ## __bf))

// clear bits in the width/shift specified/
#define CLEAR_BITS(__dst, __bf) ((__dst) = ((__dst) & ~(BIT_MASK(__bf))))

// get bits in the width/shift specified, but don't shift back down
#define GET_BOOL(__src, __bf) (((__src) & (BIT_MASK(__bf))))

// set bits in the width/shift specified; the value is cleaned of other bits by the macro
#define SET_BITS(__dst, __bf, __val) ((__dst) = ((__dst) & ~(BIT_MASK(__bf))) | (((__val) << (bs ## __bf)) & (BIT_MASK(__bf))))

// set bits without reading first - for sensitive interrupt type registers/
#define SET_BITS_ONLY(__dst, __bf, __val) ((__dst) = (((__val) << (bs ## __bf)) & (BIT_MASK(__bf))))

// get bits in the width/shift specified, and shift back down to the lowest bit
#define GET_BITS(__src, __bf) (((__src) & (BIT_MASK(__bf))) >> (bs ## __bf))


//    Additional bit operations for when the field width or shift are not constants
//    -----------------------------------------------------------------------------

// create a bitfield mask with a bitfield width and an amount to shift left
#define FIELD_MASK(__bw, __bs) (((1U << (__bw)) - 1) << (__bs))

// get bitfield in the width/shift specified, and shift back down to the lowest bit
#define GET_FIELD(__src, __bw, __bs) (((__src) & (FIELD_MASK(__bw,__bs))) >> (__bs))

// set bitfield in the width/shift specified; the value is cleaned of other bits by the macro
#define SET_FIELD(__dst, __bw, __bs, __val) ((__dst) = ((__dst) & ~(FIELD_MASK(__bw,__bs))) | (((__val) << (__bs)) & (FIELD_MASK(__bw,__bs))))

#endif

