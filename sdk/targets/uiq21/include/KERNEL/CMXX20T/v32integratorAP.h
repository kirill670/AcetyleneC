// V32INTEGRATORAP.H
//
// Copyright (c) 2000 - 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __V32INTEGRATORAP_H__
#define __V32INTEGRATORAP_H__
#include <e32std.h>
#include <e32pccd.h>
#include <e32hal.h>
#include <m32std.h>
#include <kc_arm.h>
#include <v32spi.h>
#include <v32pl180.h>

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
    // Information
	virtual TBool XYInputPresent()=0;
    virtual TSize XYInputSize()=0;
    virtual TPoint OffsetToDisplayInPixels()=0;
    virtual TInt ProcessorClockInKHz()=0;
    virtual TInt SpeedFactor()=0;
    virtual TTimeIntervalMicroSeconds32 TickPeriod()=0;
    // Debug
    virtual void DebugInit()=0;
    virtual void DebugOutput(TUint aLetter)=0;
    // Power
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
    // Peripheral Bus general
    virtual void PeriphBusMachineInfo(TDes8* anInfo)=0;
	virtual TInt MediaChangeFromPeriphBus(TPBusNum aBus)=0;
	virtual TInt MediaChangeFromPrimaryPsu(TInt aPsuNum)=0;
    // philk - HAHAHAHACK - remove this 
	// virtual TAny* CreatePeriphBusControllerInterface()=0;
    // Drive Info
	virtual TInt TotalSupportedDrives()=0;
	virtual TLDriveAssignInfo DeviceInfoFromDrive(TInt aDriveNumber)=0;
	virtual TMediaDevice DeviceFromMedia(TInt aMediaNumber)=0;
	virtual TMediaDeviceAssignInfo MediaInfoFromDevice(TMediaDevice aDevice)=0;
	virtual TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice)=0;
	virtual TInt DriveSettings()=0;
    // Interrupts
	virtual TPtrC8 ExtInterruptSource()=0;
	virtual void EnableExtInterrupt(TExtInterruptID anId)=0;
	virtual void DisableExtInterrupt(TExtInterruptID anId)=0;
	virtual void ClearExtInterrupt(TExtInterruptID anId)=0;
	virtual TExtInterruptID ActiveExtInterrupt()=0;
    // Miscellaneous    
	virtual void StartupReason(TMachineStartupType &aReason)=0;
	// MMC variant class creation 
	virtual DPL180VariantMmc* CreateMmcVariantLayer()=0;
	};

#endif

