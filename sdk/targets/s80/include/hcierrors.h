// Bluetooth HCIErrors.h
// The HCI Error codes
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.

#ifndef HCIERRORS_H__
#define HCIERRORS_H__

static const TInt KHCIErrorBase = -6000;

enum THCIErrorCode 
    {
     EOK								=0x00,                      
     EUnknownOpcode						=0x01,
     ENoConnection						=0x02,
     EHardwareFail						=0x03,
     EPageTimedOut						=0x04,
     EAuthenticationFailure				=0x05,
     EKeyMissing						=0x06,
     EKeyMemoryFull						=0x07,
     EConnectionTimeout					=0x08,
     EMaxConnections					=0x09,
     EMaxSCOConnections					=0x0a,
     EMaxACLConnections					=0x0b,
     ECommandDisallowed					=0x0c,
     EHostResourceRejection				=0x0d,
     EHostSecurityRejection				=0x0e,
     EHostPersonalDeviceRejection		=0x0f,
     ERemoteHostTimeout					=0x10,
     EUnsupportedParameter				=0x11,
     EInvalidHCIParameter				=0x12,
     ERemoteUserEndedConnection			=0x13,
     ERemoteLowResources				=0x14,
     ERemoteAboutToPowerOff				=0x15,
     ETerminatedByLocalHost				=0x16,
     ERepeatedAttempts					=0x17,
     EPairingNotAllowed					=0x18,
     EUnknownLMPpdu						=0x19,
     EUnsupportedRemoteLMPFeature		=0x1a,
     ESCOOffsetRejected					=0x1b,
     ESCOIntervalRejected				=0x1c,
     ESCOAirModeRejected				=0x1d,
     EInvalidLMPParameters				=0x1e,
     EUnspecifiedError					=0x1f,
	 EUnsupportedLMPParameterValue		=0x20,
	 ERoleChangeNotAllowed				=0x21,
	 ELMPResponseTimeout				=0x22,
	 ELMPErrorTransactionCollision		=0x23,
	 ELMPPDUNotAllowed					=0x24,
	 EEncryptionModeNotAcceptable		=0x25,
	 EUnitKeyUsed						=0x26,
	 EQOSIsNotSupported					=0x27,
	 EInstantPassed						=0x28,
	 EPairingWithUnitKeyNotSupported	=0x29,
     EPending
    };

#endif
