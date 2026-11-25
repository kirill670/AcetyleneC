// V32ARMCA.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __V32ARMCA_H__
#define __V32ARMCA_H__
#include <e32std.h>
#include <e32pccd.h>
#include <v32eiger.h>
#include <m32std.h>

const TUint   KEigerPortAKeyRow=0x000000ff;

const TUint   KEigerPortBPcmcia1Rdy=0x00000001;
const TUint   KEigerPortBRts=0x00000002;
const TUint   KEigerPortBRi=0x00000004;
const TUint   KEigerPortBDiag=0x00000008;
const TUint   KEigerPortBPxEn=0x00000010;
const TUint   KEigerPortBMxEn=0x00000020;
const TUint   KEigerPortBPyEn=0x00000040;
const TUint   KEigerPortBMyEn=0x00000080;

const TUint   KEigerPortDDiagLEDEn=0x00000001;
const TUint   KEigerPortDLcdDcToDcEn=0x00000002;
const TUint   KEigerPortDLcdEn=0x00000004;
const TUint   KEigerPortDLcdBl=0x00000008;
const TUint   KEigerPortDLcdCon=0x000000f0;

const TUint   KEigerPortECodecEn=0x00000001;
const TUint   KEigerPortE5vDis=0x00000002;
const TUint   KEigerPortEAdcEn=0x00000004;

// Port and data direction defaults
// DDRA:
const TUint	KEigerDdrADefault=0x00;
// PORTA:
const TUint	KEigerPortADefault=0x00;
// DDRB:
const TUint	KEigerDdrBDefault=KEigerPortBRts|KEigerPortBPxEn|KEigerPortBMxEn|KEigerPortBPyEn|KEigerPortBMyEn;
// PORTB:
const TUint	KEigerPortBDefault=KEigerPortBPxEn|KEigerPortBPyEn|KEigerPortBMxEn|KEigerPortBMyEn;
// DDRD:
const TUint	KEigerDdrDDefault=0x00;
// PORTD:
const TUint	KEigerPortDDefault=0x00;
// DDRE:
const TUint	KEigerDdrEDefault=KEigerPortECodecEn|KEigerPortE5vDis|KEigerPortEAdcEn;
// PORTE:
const TUint	KEigerPortEDefault=KEigerPortEAdcEn;

#define KEigerCSRom0		TEiger::EChipSelect0
#define KEigerCSRom1		TEiger::EChipSelect1
#define KEigerCSExpansion0	TEiger::EChipSelect2
#define KEigerCSExpansion1	TEiger::EChipSelect3
#define KEigerCSPcmcia0		TEiger::EChipSelect4
#define KEigerCSPcmcia1		TEiger::EChipSelect5
#define KEigerCSInternal0	TEiger::EChipSelect6
#define KEigerCSInternal1	TEiger::EChipSelect7

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
    virtual	TInt DisplayId();
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
    // Drive Info
	virtual TInt TotalSupportedDrives();
	virtual TLDriveAssignInfo DeviceInfoFromDrive(TInt aDriveNumber);
	virtual TMediaDevice DeviceFromMedia(TInt aMediaNumber);
	virtual TMediaDeviceAssignInfo MediaInfoFromDevice(TMediaDevice aDevice);
	virtual TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice);
	virtual TInt DriveSettings();
    // Machine control
    virtual void UpdateLeds(TUint aLedMask);
    virtual TBool CaseClosed();
    virtual void EnablePointerSwitchOn();
    virtual void EnableCaseSwitchOn();
    virtual void DisablePointerSwitchOn();
    virtual void DisableCaseSwitchOn();
    // Interrupts
	virtual TPtrC8 ExtInterruptSource();
	virtual void EnableExtInterrupt(TExtInterruptID anId);
	virtual void DisableExtInterrupt(TExtInterruptID anId);
	virtual void ClearExtInterrupt(TExtInterruptID anId);
	virtual TExtInterruptID ActiveExtInterrupt();
    // Miscellaneous    
    virtual TInt BindSpiChannel(const TDesC8& aName);
	virtual void StartupReason(TMachineStartupType &aReason);
    virtual TBool EightChannelAdcFitted();
	virtual TInt SetSoundDriverEnabled(TBool aState);
	virtual TSpiController* CreateSpiController();
public:
    enum TPenMode
        {
        EPenModePenDetect,
        EPenModeDriveX,
        EPenModeDriveY
        };
	enum TVariantPanic
		{
		EC6700CardNoOutOfRange,
		EC6700WaitStatesOutOfRange,
		EC6700Init3OutOfMemory,
		EC6700Init3CreateChunk
		};
    IMPORT_C static void SetPenMode(TPenMode aPenMode);
    IMPORT_C static TInt MaximumVolume();
    IMPORT_C static void SetVolume(TInt aValue);
	static void Panic(TVariantPanic aPanic);
	static void Beep(TInt aFrequency);
    };

#endif

