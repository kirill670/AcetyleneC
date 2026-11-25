// EXTERROR.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

/**
@file EXTERROR.H
@publishedAll
*/

#ifndef __EXTERROR_H__
#define __EXTERROR_H__


//Extended Error definitions
//@publishedAll
//@released

/** Base offset for the GSM errors */
const TInt KErrEtelGsmBase = -4000;

//Radio Resource Network Errors - defined by GSM 04.08
//@publishedAll
//@released

/** Base offset for the GSM radio resource errors. */
const TInt KErrGsmRadioResourceBase=KErrEtelGsmBase;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRUnspecifedAbnormalRelease=KErrGsmRadioResourceBase-1;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRChannelUnacceptable=KErrGsmRadioResourceBase-2;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRTimerExpired=KErrGsmRadioResourceBase-3;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRNoActivityOnRadioPath=KErrGsmRadioResourceBase-4;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRPreEmptiveRelease=KErrGsmRadioResourceBase-5;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRCallAlreadyCleared=KErrGsmRadioResourceBase-65;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRInvalidMessage=KErrGsmRadioResourceBase-95;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRNonExistentMessage=KErrGsmRadioResourceBase-97;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRIncompatibleMessageWithCallState=KErrGsmRadioResourceBase-98;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRInvalidInformationElement=KErrGsmRadioResourceBase-100;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmRRUnspecifiedProtocolError=KErrGsmRadioResourceBase-111;


//Mobility Management Network Errors - defined by GSM 04.08
//@publishedAll
//@released

/** Offset for the GSM mobility management errors. */
const TInt KErrGsmMobilityManagementBase=KErrGsmRadioResourceBase-128;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMUnallocatedTmsi=KErrGsmMobilityManagementBase-1;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMImsiUnknownInHlr=KErrGsmMobilityManagementBase-2;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMIllegalMs=KErrGsmMobilityManagementBase-3;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMImsiUnknownInVlr=KErrGsmMobilityManagementBase-4;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMImeiNotAccepted=KErrGsmMobilityManagementBase-5;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMIllegalMe=KErrGsmMobilityManagementBase-6;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMPlmnNotAllowed=KErrGsmMobilityManagementBase-11;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMLocationAreaNotAllowed=KErrGsmMobilityManagementBase-12;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMRoamingNotAllowedInThisLocationArea=KErrGsmMobilityManagementBase-13;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMNetworkFailure=KErrGsmMobilityManagementBase-17;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMCongestion=KErrGsmMobilityManagementBase-22;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMServiceOptionNotSupported=KErrGsmMobilityManagementBase-32;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMServiceOptionNotSubscribed=KErrGsmMobilityManagementBase-33;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMServiceOptionTemporaryOutOfOrder=KErrGsmMobilityManagementBase-34;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMCallCanNotBeIdentified=KErrGsmMobilityManagementBase-38;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMSemanticErrorInMessage=KErrGsmMobilityManagementBase-95;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMMandatoryInformationElementError=KErrGsmMobilityManagementBase-96;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMNonExistentMessageType=KErrGsmMobilityManagementBase-97;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMIncompatibleMessageWithProtocolState=KErrGsmMobilityManagementBase-98;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMNonExistentInformationElement=KErrGsmMobilityManagementBase-99;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMConditionalIEError=KErrGsmMobilityManagementBase-100;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmMMIncompatibleMessageWithCallState=KErrGsmMobilityManagementBase-101;
const TInt KErrGsmMMNoSuitableCellsInArea=KErrGsmMobilityManagementBase-15;
const TInt KErrGsmMMMacFailure=KErrGsmMobilityManagementBase-20;
const TInt KErrGsmMMSynchFailure=KErrGsmMobilityManagementBase-21;
const TInt KErrGsmMMGsmAuthenticationUnacceptable=KErrGsmMobilityManagementBase-23;
const TInt KErrGsmMMUnspecifiedProtocolError=KErrGsmMobilityManagementBase-111;

//Call Control Network Errors - defined by GSM 04.08
//@publishedAll
//@released

/** Base offset for the GSM call control errors. */
const TInt KErrGsmCallControlBase=KErrGsmMobilityManagementBase-128;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCUnassignedNumber=KErrGsmCallControlBase-1;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNoRouteToTransitNetwork=KErrGsmCallControlBase-2;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNoRouteToDestination=KErrGsmCallControlBase-3;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCChannelUnacceptable=KErrGsmCallControlBase-6;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCOperatorDeterminedBarring=KErrGsmCallControlBase-8;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCUserBusy=KErrGsmCallControlBase-17;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCUserNotResponding=KErrGsmCallControlBase-18;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCUserAlertingNoAnswer=KErrGsmCallControlBase-19;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCCallRejected=KErrGsmCallControlBase-21;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNumberChanged=KErrGsmCallControlBase-22;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNonSelectedUserClearing=KErrGsmCallControlBase-26;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCDestinationOutOfOrder=KErrGsmCallControlBase-27;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCInvalidNumberFormat=KErrGsmCallControlBase-28;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCFacilityRejected=KErrGsmCallControlBase-29;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCResponseToStatusEnquiry=KErrGsmCallControlBase-30;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNormalUnspecified=KErrGsmCallControlBase-31;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNoChannelAvailable=KErrGsmCallControlBase-34;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNetworkOutOfOrder=KErrGsmCallControlBase-38;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCTemporaryFailure=KErrGsmCallControlBase-41;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCSwitchingEquipmentCongestion=KErrGsmCallControlBase-42;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCAccessInformationDiscarded=KErrGsmCallControlBase-43;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCRequestedChannelNotAvailable=KErrGsmCallControlBase-44;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCResourceNotAvailable=KErrGsmCallControlBase-47;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCQualityOfServiceNotAvailable=KErrGsmCallControlBase-49;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCRequestedFacilityNotSubscribed=KErrGsmCallControlBase-50;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCIncomingCallsBarredInCug=KErrGsmCallControlBase-55;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCBearerCapabilityNotAuthorised=KErrGsmCallControlBase-57;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCBearerCapabilityNotCurrentlyAvailable=KErrGsmCallControlBase-58;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCServiceNotAvailable=KErrGsmCallControlBase-63;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCBearerServiceNotImplemented=KErrGsmCallControlBase-65;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCChannelTypeNotImplemented=KErrGsmCallControlBase-66;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCAcmGreaterThanAcmMax=KErrGsmCallControlBase-68;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCRequestedFacilityNotImplemented=KErrGsmCallControlBase-69;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCOnlyRestrictedDigitalInformationBCAvailable=KErrGsmCallControlBase-70;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCServiceNotImplemented=KErrGsmCallControlBase-79;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCInvalidCallReferenceValue=KErrGsmCallControlBase-81;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCChannelDoesNotExist=KErrGsmCallControlBase-82;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCSuspendedCallExistsButCallIdentityDoesNotWork=KErrGsmCallControlBase-83;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCCallIdentityInUse=KErrGsmCallControlBase-84;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNoCallSuspended=KErrGsmCallControlBase-85;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCRequestedCallIdentityAlreadyCleared=KErrGsmCallControlBase-86;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCUserNotInCug=KErrGsmCallControlBase-87;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCIncompatibleDestination=KErrGsmCallControlBase-88;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCInvalidTransitNetworkSelection=KErrGsmCallControlBase-91;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCIncompatibleSegmentedMessage=KErrGsmCallControlBase-94;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCSemanticallyIncorrectMessage=KErrGsmCallControlBase-95;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCInvalidMandatoryInformation=KErrGsmCallControlBase-96;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNonExistentMessageType=KErrGsmCallControlBase-97;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCIncompatibleMessageInProtocolState=KErrGsmCallControlBase-98;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCNonExistentInformationElement=KErrGsmCallControlBase-99;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCConditionalIEError=KErrGsmCallControlBase-100;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCIncompatibleMessageInCallState=KErrGsmCallControlBase-101;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCRecoveryOnTimerExpiry=KErrGsmCallControlBase-102;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCUnspecifiedProtocolError=KErrGsmCallControlBase-111;
/** Please see the 3GPP GSM 04.08 document. */
const TInt KErrGsmCCUnspecifiedInterworkingError=KErrGsmCallControlBase-127;

/**
@internalComponent
*/
const TInt KErrGsmCCNormalCallClearing=KErrGsmCallControlBase-16; 
/**
@internalComponent
*/
const TInt KErrGsmCCPreemption=KErrGsmCallControlBase-25;

//Supplementary Services Network Errors - defined by GSM 04.80
//@publishedAll
//@released

/** Offset for the GSM supplementary services errors. */
const TInt KErrGsmSuppServiceBase=KErrGsmCallControlBase-128;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSUnknownSubscriber=KErrGsmSuppServiceBase-1;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSIllegalSubscriber=KErrGsmSuppServiceBase-9;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSBearerServiceNotProvisioned=KErrGsmSuppServiceBase-10;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSTeleserviceNotProvisioned=KErrGsmSuppServiceBase-11;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSIllegalEquipment=KErrGsmSuppServiceBase-12;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSCallBarred=KErrGsmSuppServiceBase-13;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSIllegalOperation=KErrGsmSuppServiceBase-16;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSErrorStatus=KErrGsmSuppServiceBase-17;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSNotAvailable=KErrGsmSuppServiceBase-18;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSSubscriptionViolation=KErrGsmSuppServiceBase-19;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSIncompatibility=KErrGsmSuppServiceBase-20;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSFacilityNotSupported=KErrGsmSuppServiceBase-21;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSAbsentSubscriber=KErrGsmSuppServiceBase-27;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSSystemFailure=KErrGsmSuppServiceBase-34;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSDataMissing=KErrGsmSuppServiceBase-35;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSUnexpectedDataValue=KErrGsmSuppServiceBase-36;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSPasswordRegistrationFailure=KErrGsmSuppServiceBase-37;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSNegativePasswordCheck=KErrGsmSuppServiceBase-38;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSPasswordAttemptsViolation=KErrGsmSuppServiceBase-43;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSUnknownAlphabet=KErrGsmSuppServiceBase-71;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSUssdBusy=KErrGsmSuppServiceBase-72;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSMaxNumMptyParticipants=KErrGsmSuppServiceBase-126;
/** Please see the 3GPP GSM 04.80 document. */
const TInt KErrGsmSSResourcesUnavailable=KErrGsmSuppServiceBase-127;


//SMS Errors - defined by GSM 04.11, 03.40 and 07.05
//@publishedAll
//@released

/** Base offset for the GSM SMS errors. */
const TInt KErrGsmSmsBase=KErrGsmSuppServiceBase-128;

// 04.11
//@publishedAll
//@released

/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSUnassignedNumber=KErrGsmSmsBase-1;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSOperatorDeterminedBarring=KErrGsmSmsBase-8;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSCallBarred=KErrGsmSmsBase-10;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSReserved=KErrGsmSmsBase-11;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSNetworkFailure=KErrGsmSmsBase-17;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSShortMessageTransferRejected=KErrGsmSmsBase-21;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSMemoryCapacityExceeded=KErrGsmSmsBase-22;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSDestinationOutOfOrder=KErrGsmSmsBase-27;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSUnidentifiedSubscriber=KErrGsmSmsBase-28;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSFacilityRejected=KErrGsmSmsBase-29;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSUnknownSubscriber=KErrGsmSmsBase-30;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSNetworkOutOfOrder=KErrGsmSmsBase-38;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSTemporaryFailure=KErrGsmSmsBase-41;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSCongestion=KErrGsmSmsBase-42;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSResourcesUnavailable=KErrGsmSmsBase-47;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSRequestedFacilityNotSubscribed=KErrGsmSmsBase-50;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSRequestedFacilityNotImplemented=KErrGsmSmsBase-69;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSInvalidShortMessageTransferReferenceValue=KErrGsmSmsBase-81;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSUnspecifiedInvalidMessage=KErrGsmSmsBase-95;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSInvalidMandatoryInformation=KErrGsmSmsBase-96;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSNonExistentMessageType=KErrGsmSmsBase-97;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSIncompatibleMessageWithSmsProtocolState=KErrGsmSmsBase-98;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSInformationElementNotImplemented=KErrGsmSmsBase-99;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSUnspecifiedProtocolError=KErrGsmSmsBase-111;
/** Please see the GSM 04.11 document. */
const TInt KErrGsmSMSUnspecifiedInterworkingError=KErrGsmSmsBase-127;

// 03.40
//@publishedAll
//@released

/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSTelematicInterworkingNotSupported=KErrGsmSmsBase-128;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSShortMessageType0NotSupported=KErrGsmSmsBase-129;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSCannotReplaceShortMessage=KErrGsmSmsBase-130;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSUnspecifiedPIDError=KErrGsmSmsBase-143;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSDataCodingSchemeNotSupported=KErrGsmSmsBase-144;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSMessageClassNotSupported=KErrGsmSmsBase-145;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSUnspecifiedDCSError=KErrGsmSmsBase-159;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSCommandCannotBeActioned=KErrGsmSmsBase-160;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSCommandNotSupported=KErrGsmSmsBase-161;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSUnspecifiedCommandError=KErrGsmSmsBase-175;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSTpduNotSupported=KErrGsmSmsBase-176;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSServiceCentreBusy=KErrGsmSmsBase-192;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSNoSCSubscription=KErrGsmSmsBase-193;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSSCSystemFailure=KErrGsmSmsBase-194;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSInvalidSMEAddress=KErrGsmSmsBase-195;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSDestinationSMEBarred=KErrGsmSmsBase-196;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSDuplicateSM=KErrGsmSmsBase-197;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSTPVPFNotSupported=KErrGsmSmsBase-198;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSTPVPNotSupported=KErrGsmSmsBase-199;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSSimSMSStorageFull=KErrGsmSmsBase-208;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSNoSMSStorageCapabilityInSim=KErrGsmSmsBase-209;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSErrorInMS=KErrGsmSmsBase-210;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSMemCapacityExceeded=KErrGsmSmsBase-211;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSSimAppToolkitBusy=KErrGsmSmsBase-212;
/** Please see the GSM 03.40 document. */
const TInt KErrGsmSMSUnspecifiedErrorCause=KErrGsmSmsBase-255;

// 07.05
//@publishedAll
//@released

/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSFailureInME=KErrGsmSmsBase-300;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSServiceOfMSReserved=KErrGsmSmsBase-301;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSOperationNotAllowed=KErrGsmSmsBase-302;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSOperationNotSupported=KErrGsmSmsBase-303;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSInvalidPDUModeParameter=KErrGsmSmsBase-304;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSInvalidTextModeParameter=KErrGsmSmsBase-305;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSSimNotInserted=KErrGsmSmsBase-310;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSSimPin1Required=KErrGsmSmsBase-311;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSPhoneToSimLockRequired=KErrGsmSmsBase-312;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSSimFailure=KErrGsmSmsBase-313;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSSimBusy=KErrGsmSmsBase-314;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSSimWrong=KErrGsmSmsBase-315;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSSimPuk1Required=KErrGsmSmsBase-316;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSPin2Required=KErrGsmSmsBase-317;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSPuk2Required=KErrGsmSmsBase-318;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSMemoryFailure=KErrGsmSmsBase-320;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSInvalidMemoryIndex=KErrGsmSmsBase-321;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSMemoryFull=KErrGsmSmsBase-322;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSUnknownSCAddress=KErrGsmSmsBase-330;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSNoNetworkService=KErrGsmSmsBase-331;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSNetworkTimeout=KErrGsmSmsBase-332;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSCnmaAckNotExpected=KErrGsmSmsBase-340;
/** Please see the GSM 07.05 document. */
const TInt KErrGsmSMSUnknownError=KErrGsmSmsBase-500;


//General TE-TA Errors - defined by GSM 07.07
//@publishedAll
//@released

/** Base offset for the general TE-TA Errors - defined by GSM 07.07. */
const TInt KErrGsm0707Base=KErrGsmSmsBase-512;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707PhoneFailure=KErrGsm0707Base;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707NoConnectionToPhone=KErrGsm0707Base-1;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707PhoneLinkReserved=KErrGsm0707Base-2;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707OperationNotAllowed=KErrGsm0707Base-3;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707OperationNotSupported=KErrGsm0707Base-4;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707PhoneToSimLockRequired=KErrGsm0707Base-5;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SimNotInserted=KErrGsm0707Base-10;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SimPin1Required=KErrGsm0707Base-11;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SIMPuk1Required=KErrGsm0707Base-12;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SimFailure=KErrGsm0707Base-13;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SimBusy=KErrGsm0707Base-14;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SimWrong=KErrGsm0707Base-15;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707IncorrectPassword=KErrGsm0707Base-16;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SimPin2Required=KErrGsm0707Base-17;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707SIMPuk2Required=KErrGsm0707Base-18;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707MemoryFull=KErrGsm0707Base-20;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707InvalidIndex=KErrGsm0707Base-21;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707NotFound=KErrGsm0707Base-22;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707MemoryFailure=KErrGsm0707Base-23;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707TextStringTooLong=KErrGsm0707Base-24;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707InvalidCharsInTextString=KErrGsm0707Base-25;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707DialStringTooLong=KErrGsm0707Base-26;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707InvalidCharsInDialString=KErrGsm0707Base-27;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707NoNetworkService=KErrGsm0707Base-30;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707NetworkTimeout=KErrGsm0707Base-31;
/** Please see the GSM 07.07 document. */
const TInt KErrGsm0707UnknownError=KErrGsm0707Base-100;

#endif
