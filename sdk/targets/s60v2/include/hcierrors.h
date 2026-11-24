// Bluetooth HCIErrors.h
// The HCI Error codes
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.

/**
@file hcierrors.h
@publishedAll
@released
*/

#ifndef HCIERRORS_H__
#define HCIERRORS_H__

static const TInt KHCIErrorBase = -6000;	/*!< Base error value for HCI error codes */

enum THCIErrorCode
/** HCI error codes taken from the Bluetooth code specification.
@see Bluetooth specification
*/
    {
     EOK								=0x00,	/*!< HCI OK error code - Used to indicate the absence of any error condition */
     EUnknownOpcode						=0x01,	/*!< HCI unknown opcode error code */
     ENoConnection						=0x02,	/*!< HCI no connection error code */
     EHardwareFail						=0x03,	/*!< HCI hardware failure error code */
     EPageTimedOut						=0x04,	/*!< HCI page timeout error code */
     EAuthenticationFailure				=0x05,	/*!< HCI authentification failure error code */
     EKeyMissing						=0x06,	/*!< HCI key missing error code */
     EKeyMemoryFull						=0x07,	/*!< HCI key memory full error code */
     EConnectionTimeout					=0x08,	/*!< HCI connection timeout error code */
     EMaxConnections					=0x09,	/*!< HCI maximum number of connections exceeded error code */
     EMaxSCOConnections					=0x0a,	/*!< HCI maximum number of SCO connections exceeded error code */
     EMaxACLConnections					=0x0b,	/*!< HCI maximum number of ACL connections exceeded error code */
     ECommandDisallowed					=0x0c,	/*!< HCI command disallowed error code */
     EHostResourceRejection				=0x0d,	/*!< HCI host resource rejection error code */	
     EHostSecurityRejection				=0x0e,	/*!< HCI host security rejection error code */
     EHostPersonalDeviceRejection		=0x0f,	/*!< HCI host personal device rejection error code */
     ERemoteHostTimeout					=0x10,	/*!< HCI remote host timeout error code */
     EUnsupportedParameter				=0x11,	/*!< HCI unsupported parameter error code */
     EInvalidHCIParameter				=0x12,	/*!< HCI invalid HCI parameter error code */
     ERemoteUserEndedConnection			=0x13,	/*!< HCI remote device user ended connection error code */
     ERemoteLowResources				=0x14,	/*!< HCI remote device low resources error code */
     ERemoteAboutToPowerOff				=0x15,	/*!< HCI remote device about to power off error code */
     ETerminatedByLocalHost				=0x16,	/*!< HCI treminated by local host error code */
     ERepeatedAttempts					=0x17,	/*!< HCI repeated attempts error code */
     EPairingNotAllowed					=0x18,	/*!< HCI pairing not allowed error code */
     EUnknownLMPpdu						=0x19,	/*!< HCI unknown LMP PDU error code */
     EUnsupportedRemoteLMPFeature		=0x1a,	/*!< HCI unsupported remote LMP feature error code */
     ESCOOffsetRejected					=0x1b,	/*!< HCI SCO offset rejected error code */
     ESCOIntervalRejected				=0x1c,	/*!< HCI SCO interval rejected error code */
     ESCOAirModeRejected				=0x1d,	/*!< HCI SCO air mode rejected error code */
     EInvalidLMPParameters				=0x1e,	/*!< HCI invalid LMP parameters error code */
     EUnspecifiedError					=0x1f,	/*!< HCI unspecified error code */
	 EUnsupportedLMPParameterValue		=0x20,	/*!< HCI unsupported LMP parameter value error code */
	 ERoleChangeNotAllowed				=0x21,	/*!< HCI role change not allowed error code */
	 ELMPResponseTimeout				=0x22,	/*!< HCI LMP response timeout error code */
	 ELMPErrorTransactionCollision		=0x23,	/*!< HCI LMP error transaction collision error code */
	 ELMPPDUNotAllowed					=0x24,	/*!< HCI LMP PDU not allowed error code */
	 EEncryptionModeNotAcceptable		=0x25,	/*!< HCI encryption mode not acceptable error code */
	 EUnitKeyUsed						=0x26,	/*!< HCI unit key not used error code */
	 EQOSIsNotSupported					=0x27,	/*!< HCI QOS not supported error code */
	 EInstantPassed						=0x28,	/*!< HCI instant passed error code */
	 EPairingWithUnitKeyNotSupported	=0x29,	/*!< HCI pairing with unit key not supported error code */
/** This value will be removed
@internalTechnology
*/
	 EDifferentTransactionCollision		=0x2a,
	 //Reserved by Bluetooth Spec ...	=0x2b,
	 EQoSUnacceptableParameter			=0x2c,	/*!< HCI bad parameter error code */
	 EQoSRejected						=0x2d,	/*!<  HCI quality of service not accepted error code */
	 EChannelClassificationNotSupported	=0x2e,	/*!< HCI adaptive frequency hopping channel classification not supported error code */
	 EInsufficientSecurity				=0x2f,	/*!< HCI insufficient security error code */
	 EParameterOutOfMandatoryRange		=0x30,	/*!< HCI parameter value outside required range error code */
	 //Reserved by Bluetooth Spec ...	=0x31,
	 ERoleSwitchPending					=0x32,	/*!< HCI failure because a master/slave role switch is about to take place error code */
	 //Reserved by Bluetooth Spec ...	=0x33,
	 EReservedSlotViolation				=0x34,	/*!< HCI use of reserved baseband packet slot error code */
	 ERoleSwitchFailed					=0x35,	/*!< HCI master/slave role switch failed error code */
    };

#endif
