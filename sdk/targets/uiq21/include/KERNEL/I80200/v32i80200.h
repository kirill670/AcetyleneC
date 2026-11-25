// V32I80200.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __V32I80200_H__
#define __V32I80200_H__
#include <e32std.h>
#include <e32pccd.h>
#include <e32hal.h>
#include <m32std.h>
#include <kc_arm.h>
#include <a32i80200.h>

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
	virtual void WriteDebugUart(TUint aChar)=0;
	virtual TUint ReadDebugUart()=0;
	virtual TBool DebugUartTxRdy()=0;
	virtual TBool DebugUartRxRdy()=0;
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
	virtual void EnableExtInterrupt(TExtInterruptID anId)=0;
	virtual void DisableExtInterrupt(TExtInterruptID anId)=0;
	virtual void ClearExtInterrupt(TExtInterruptID anId)=0;
	virtual TExtInterruptID ActiveExtIRQ()=0;
	virtual TExtInterruptID ActiveExtFIQ()=0;
    // Miscellaneous    
	virtual void StartupReason(TMachineStartupType &aReason)=0;
	virtual TInt SetSoundDriverEnabled(TBool aState)=0;
	// Ms Timer
	virtual TInt MsTimerCountFromMs(TInt aMs)=0;
	virtual TInt MsTimerCount()=0;
	virtual void MsTimerStop()=0;
	virtual void MsTimerStart(TInt aCount)=0;
	virtual void MsTimerNext(TInt aCount)=0;
	};

#endif

