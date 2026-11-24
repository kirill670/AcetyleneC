// HAL_DATA.H
//
// Copyright (c) Symbian Software Ltd 1995-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/

#ifndef __HAL_DATA_H__
#define __HAL_DATA_H__

#define bitmask enum

/**
 * Attributes and values used by HAL::Get, HAL::Set etc.
 *
 * @public
 * @since 6.0
 */
class HALData
	{
public:
	enum TAttribute
		{
		EManufacturer,
		EManufacturerHardwareRev,
		EManufacturerSoftwareRev,
		EManufacturerSoftwareBuild,
		EModel,
		EMachineUid,
		EDeviceFamily,
		EDeviceFamilyRev,
		ECPU,
		ECPUArch,
		ECPUABI,
		ECPUSpeed,
		ESystemStartupReason,
		ESystemException,
		ESystemTickPeriod,
		EMemoryRAM,
		EMemoryRAMFree,
		EMemoryROM,
		EMemoryPageSize,
		EPowerGood,
		EPowerBatteryStatus,
		EPowerBackup,
		EPowerBackupStatus,
		EPowerExternal,
		EKeyboard,
		EKeyboardDeviceKeys,
		EKeyboardAppKeys,
		EKeyboardClick,
		EKeyboardClickState,
		EKeyboardClickVolume,
		EKeyboardClickVolumeMax,
		EDisplayXPixels,
		EDisplayYPixels,
		EDisplayXTwips,
		EDisplayYTwips,
		EDisplayColors,
		EDisplayState,
		EDisplayContrast,
		EDisplayContrastMax,
		EBacklight,
		EBacklightState,
		EPen,
		EPenX,
		EPenY,
		EPenDisplayOn,
		EPenClick,
		EPenClickState,
		EPenClickVolume,
		EPenClickVolumeMax,
		EMouse,
		EMouseX,
		EMouseY,
		EMouseState,
		EMouseSpeed,
		EMouseAcceleration,
		EMouseButtons,
		EMouseButtonState,
		ECaseState,
		ECaseSwitch,
		ECaseSwitchDisplayOn,
		ECaseSwitchDisplayOff,
		ELEDs,
		ELEDmask,
		EIntegratedPhone,
		EDisplayBrightness,
		EDisplayBrightnessMax,
		EKeyboardBacklightState,
		EAccessoryPower,
		ELanguageIndex,
		EKeyboardIndex,
		EMaxRAMDriveSize,
		EKeyboardState,
		ESystemDrive,
		EPenState,
		EDisplayIsMono,
		EDisplayIsPalettized,
		EDisplayBitsPerPixel,
		EDisplayNumModes,
		EDisplayMemoryAddress,
		EDisplayOffsetToFirstPixel,
		EDisplayOffsetBetweenLines,
		EDisplayPaletteEntry,
		EDisplayIsPixelOrderRGB,
		EDisplayIsPixelOrderLandscape,
		EDisplayMode,
		ESwitches,
		EDebugPort,
		ELocaleLoaded,
		EClipboardDrive,
		ECustomRestart,
		ECustomRestartReason,
		EDisplayNumberOfScreens,
		ENumHalAttributes
		};

	enum TAttributeProperty
		{
		EValid=0x1,
		ESettable=0x2,
		};

	enum TManufacturer // UID for manufacturer
		{
		EManufacturer_Ericsson=0x00000000,
		EManufacturer_Motorola=0x00000001,
		EManufacturer_Nokia=0x00000002,
		EManufacturer_Panasonic=0x00000003,
		EManufacturer_Psion=0x00000004,
		EManufacturer_Intel=0x00000005,
		EManufacturer_Cogent=0x00000006,
		EManufacturer_Cirrus=0x00000007,
		EManufacturer_Linkup=0x00000008,
		EManufacturer_TexasInstruments=0x00000009,
		// New manufacturers must obtain an official UID to identify themselves
		};

	enum TDeviceFamily
		{
		EDeviceFamily_Crystal,
		EDeviceFamily_Pearl,
		EDeviceFamily_Quartz,
		};

	enum TCPU
		{
		ECPU_ARM,
		ECPU_MCORE,
		ECPU_X86,
		};

	enum TCPUABI
		{
		ECPUABI_ARM4,
		ECPUABI_ARMI,
		ECPUABI_THUMB,
		ECPUABI_MCORE,
		ECPUABI_MSVC,
		ECPUABI_ARM5T,
		};

	enum TSystemStartupReason
		{
		ESystemStartupReason_Cold,
		ESystemStartupReason_Warm,
		ESystemStartupReason_Fault,
		};

	bitmask TKeyboard
		{
		EKeyboard_Keypad=0x1,
		EKeyboard_Full=0x2,
		};

	enum TMouseState
		{
		EMouseState_Invisible=0,
		EMouseState_Visible=1,
		};

	enum TMachineUid
		{
		EMachineUid_Series5mx=0x1000118a,
		EMachineUid_Brutus=0x10005f60,
		EMachineUid_Cogent=0x10005f61,
		EMachineUid_Win32Emulator=0x10005f62,
		EMachineUid_WinC=0x10005f63,
		EMachineUid_CL7211_Eval=0x1000604f,
		EMachineUid_LinkUp=0x00000000,
		EMachineUid_Assabet=0x100093f3,
		EMachineUid_IQ80310=0x1000a681,
		EMachineUid_Lubbock=0x1000a682,
		EMachineUid_Integrator=0x1000AAEA,
		EMachineUid_Helen=0x101F3EE3,
		};

	enum TPowerBatteryStatus
		{
		EPowerBatteryStatus_Zero,
		EPowerBatteryStatus_Replace,
		EPowerBatteryStatus_Low,
		EPowerBatteryStatus_Good,
		};

	enum TPowerBackupStatus
		{
		EPowerBackupStatus_Zero,
		EPowerBackupStatus_Replace,
		EPowerBackupStatus_Low,
		EPowerBackupStatus_Good,
		};
	};

#endif
