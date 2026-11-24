/*
* ============================================================================
*  Name     : MmsConst.h
*  Part of  : MmsEngine
*
*  Description:
*     Miscellaneous constants needed by MmsEngine and its clients
*  Version:
*
*  Copyright (C) 2002-2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef MMSCONST_H
#define MMSCONST_H

//  INCLUDES
#include <msvuids.h>
#include <msvstd.hrh>
#include <e32std.h>

// ----- START OF DEPRECATED BLOCK
// These path names are deprecated.
// They are not used by any component anymore internally
// and should not be used externally
// To be removed in version 3.0
#define MTM_DATAFILE _L("c:\\system\\mtm\\MMSMTM.dat")
#define MTM_NAME _L("MMSMTM")
#define MTM_REGISTRY _L("c:\\system\\mtm\\MTM Registry")

// Temporary name, used only in test programs
#define MTM_READABLE_NAME _L("MmsClientSideComponent")
//-----END OF DEPRECATED BLOCK


// Periods for waiting information from WAP GW
// These default values are used if shared data client is not available
#define KMmsWapConnectTimer 300  //lint !e1923 keep macro   // 300 sec = 5 min
#define KMmsWapDisconnectTimer 300  //lint !e1923 keep macro   // 300 sec = 5 min
#define KMmsWapTransactionTimer 900 //lint !e1923 keep macro // 900 sec = 15 min
#define KMmsGprsSuspendTimer 900  //lint !e1923 keep macro // 900 sec = 15 min

// Default value for how much data we are able to receive
#define KMmsWapMaxReceiveSize (300*1024) //lint !e1923 keep macro // 300 kbytes

// Default value for how much data we are able to send
#define KMmsWapMaxSendSize (300*1024) //lint !e1923 keep macro // 300 kbytes


// CONSTANTS

// This defines the number of digits that will used for matching phone numbers to contacts
// in contact database. The number is counted from the right.
const TInt KMmsNumberOfDigitsToMatch = 7;

// This could be calculated and defined as a number
// NB. January = 0! 1st day of month = 0!
_LIT( KMmsYear1970String, "19700000:000000.000000" );

// This is the resource file that contains factory values
// for error actions (for scheduled sending and receiving)
// ----- START OF DEPRECATED BLOCK
// Because of data caging the definition must change.
// This definition must be deprecated.
// Path and filename must be separated
_LIT(KMmsResourceFile, "z:\\System\\Data\\MMSSERVER.RSC");
//-----END OF DEPRECATED BLOCK
// New definition that will use data caging path definition
_LIT(KMmsResourceDriveAndFile, "z:mmsserver.rsc");

#define KNOTIFICATIONFOLDER
// Invisible local folder that contains MMS notifications
_LIT(KMMSNotificationFolder, "MMSNotifications");

// Invisible local Mmbox folder
_LIT(KMmsMmboxFolder, "MmsMmbox");

// This is the extra amount of disk space that will be taken
// up by the index entry when creating new message entries.
// This is a crude estimate. It is defined here as a constant
// to allow it to be made more accurate by changing the value
// in only one place.
const TInt KMmsIndexEntryExtra = 80;

// This is the safety margin for fetching MMS messages.
// There should be at least this much extra disk space
// before a message can be fetched. A new message takes
// more disk space than the amount indicated in the 
// notification.
const TInt KMmsDiskSafetyMargin = 25000;

// dll uids
const TUid KUidMmsServerMtm={0x100058DB};
const TUid KUidMmsClientMtm={0x100058DC};
// uimtm and uidata mtm are in the same file
const TUid KUidMmsClientUIMtm={0x100058DD};
const TUid KUidMmsClientUIDataMtm={0x100058DD};
const TUid KUidMMsUtilityDll={0x100058E0};
const TUid KUidMMsTransportDll={0x101f4691};
// editor and viewer
const TInt KUidMsgMmsEditor={0x100058DE};
// Kidsgrove stuff uses viewer id
const TInt KUidMsgMmsViewer={0x100058DF};

// Documents folder
// In manual mode notifications can be moved to
// documents folder.
// This is defined in \mce\inc\mceids.h
// const TUid KMceDocumentsEntryId={0x00001008};

// message types
const TUid KUidMsgTypeMultimedia={0x100058E1};
const TUid KUidMsvTechnologyGroupMMS={0x100058E2};
const TUid KUidMsgMMSNotification={0x100059C8};

// message stream uids
const TUid KUidMmsHeaderStream={0x01000030};
const TUid KUidMmsMimeHeaderStream={0x01000031};
const TUid KUidMmsAttachmentInfoStream={0x01000032};
// recipient scheduling info
const TUid KUidMmsRecipientStream={0x01000033};
const TUid KUidBinaryNotificationStream={0x01000034};
// MMS encapsulation 1.2 extra headers streams
// element descriptor info, only in notification
const TUid KUidMMsElementDescriptorStream = {0x01000035};
// MMBox headers that can be present in several message PDUs
const TUid KUidMMsMMBoxMessageHeaderStream = {0x01000036};
// MMBox headers that are present in MMBox view request and confirmation only
const TUid KUidMMsMMBoxViewHeadersStream = {0x01000037};
// Conformance class information
const TUid KUidMMsConformanceClassStream = {0x01000038};
// Extra info (message text) present in extended notification.
const TUid KUidMMsExtendedNotificationStream = {0x01000039};

// Log entry event type uid
// Used unless Symbian allocates us an id
const TUid KLogMmsEventTypeUid = {0x1000595e};

// Currently only connection oriented unsecure port is supported
const TUint16 KSupportedWAPPort = 9201;

// maximum alias length
const TInt KMmsAliasLength = 128;

#ifdef __WINS__
// // Support for localmode polling in WINS emulator
// This ini-file is used only in local mode and in WINS
// There is no need for data caging in this case as the user
// may edit any file in WINS anyway.
// And this directory is for testing only
_LIT( KMmsLocalModeConfigFile,      "c:\\system\\data\\localmode.ini" );
_LIT( KMmsLocalmodeInDirectory,     "mmsin" );
_LIT( KMmsLocalmodeOutDirectory,    "mmsout" );
_LIT( KMmsLocalmodePollingInterval, "pollinginterval" );

#endif

//-----------------------------------------------
// Flag bits in iMtmData1
// The default value for all bits is 0
//-----------------------------------------------
// Message types stored in iMtmData1
const TUint32 KMmsMessageTypeMask = 0x0000000F;
const TUint32 KMmsMessageMSendReq = 0x00000001;
const TUint32 KMmsMessageMSendConf = 0x00000002;
const TUint32 KMmsMessageMNotificationInd = 0x00000003;
const TUint32 KMmsMessageMNotifyRespInd = 0x00000004;
const TUint32 KMmsMessageMRetrieveConf = 0x00000005;
const TUint32 KMmsMessageAcknowledgeInd = 0x00000006;
const TUint32 KMmsMessageDeliveryInd = 0x00000007;
// MMS encapsulation version 1.1 types
const TUint32 KMmsMessageReadRecInd = 0x00000008;
const TUint32 KMmsMessageReadOrigInd = 0x00000009;
const TUint32 KMmsMessageForwardReq = 0x0000000A;
const TUint32 KMmsMessageForwardConf = 0x0000000B;
// this must be the last one to allow some expansion for known types
const TUint32 KMmsMessageUnrecognized = 0x0000000F;

// Message state stored in iMtmData1 (see TMmsMsvEntry class)
const TUint32 KMmsMessageEncrypted =        0x00000010;
const TUint32 KMmsMessageSigned =           0x00000020;
const TUint32 KMmsMessageForwarded =        0x00000040;
const TUint32 KMmsMessageMobileTerminated = 0x00000080;
const TUint32 KMmsMessageEditorOriented =   0x00000100;

// Message type flags (not in TMmsMsvEntry)
// 1 byte reserved (0x0000F000)
// If no flag is set, message is personal (default)
const TUint32 KMmsMessageAdvertisement =   0x00001000;
const TUint32 KMmsMessageInformational =   0x00002000;

// DRM Types in iMtmData1
const TUint32 EDRMMmsMask =             0x0FFF0000;
const TUint32 EDRMForwardLock =			0x00010000; // Forward lock
const TUint32 EDRMCombinedDelivery =	0x00020000; // Combined delivery
const TUint32 EDRMSeparateDelivery =	0x00040000; // Separate delivery
const TUint32 EDRMRights =				0x00080000; // DRM Rights
const TUint32 EDRMMessage =				0x00100000; // DRM Message. This is used 
// only when it is not known for sure, if it is a FL or a CD.

// DRM Status in iMtmData1
const TUint32 EMmsUnsupportedDrmTypeRemoved =	0x01000000; // An DRM attachment, which is not allowed or capable 
															// to be used is received and removed.
const TUint32 EMmsDrmCorruptedAttachment =		0x02000000;	// A DRM attachment is corrupted and removed
const TUint32 EMmsDrmEngineError =				0x04000000; // A DRM engine caused an error.

// Bit that indicates if the message contains non-conformant content.
// Default value is 0.
// 0 = Message is conformant, or the content is unknown (created by legacy software)
// 1 = Message is known to contain non-conformant content.
const TUint32 KMmsNonConformantMessage =   0x10000000;

// Range of bits that indicates that the message has some special content
// that needs some non-standard handling
const TUint32 KMmsSpecialContentMask =  0xE0000000;
// Special content is "postcard"
const TUint32 KMmsPostcard =            0x20000000;
// Special content is "upload"
const TUint32 KMmsUpload =              0x40000000;


//-----------------------------------------------
// Flag bits in iMtmData2
// The default value for all bits is 0
//-----------------------------------------------

// Message notification stuff stored in iMtmData2
// response already sent to MMSC?
const TUint32 KMmsNotifyResponseSent = 0x00000001;
// undecoded (binary) notification
const TUint32 KMmsNotificationBinary = 0x00000002;

// The following flags are related to notifications that are stored in inbox
// to allow the messages to be fetched manually (not automatically)
// has the message corresponding to this notification expired

// Message corresponding to this notification has expired
// 0 = Message has not expired, 1 = Message has expired
const TUint32 KMmsMessageExpired =     0x00000004;

// Should this notification be deleted when the corresponding message expires
// 0 = Do not delete when expired, 1 = Delete when expired
const TUint32 KMmsDeleteAtExpiration = 0x00000008;

// Operation mask. The next bits tell which operation is currently in progress.
// When a message is being forwarded or fetched, another simulataneous operation
// is not allowed.
// 0 = no operation
const TUint32 KMmsOperationIdentifier = 0x00000070;

// fetch operation in progress
const TUint32 KMmsOperationFetch =      0x00000010;
// forward operation in progress or finished
const TUint32 KMmsOperationForward =    0x00000020;
// delete operation in progress or finished
const TUint32 KMmsOperationDelete =     0x00000030;
// 0x00000040 - 0x00000070 reserved for future operations

// Operation progress bits (4 bits)

// Is new operation allowed for this notification
// 0 = new operation allowed
// 1 = new operation forbidden
const TUint32 KMmsNewOperationForbidden = 0x00000080;
// Is operation currently ongoing
// 0 = no operation
// 1 = operation ongoing
const TUint32 KMmsOperationOngoing =      0x00000100;
// Has operation finished (and is result available)
// 0 = operation has not finished
// 1 = operation has finished
const TUint32 KMmsOperationFinished =     0x00000200;
// Operation result (if operation has finished)
// 0 = OK
// 1 = error
const TUint32 KMmsOperationResult =       0x00000400;

// Has message been stored to MMBox as result of some operation
// or was it in MMBox originally
// 0 = Message not in MMBox
// 1 = Message stored in MMBox
const TUint32 KMmsStoredInMMBox =         0x00000800;

// 0 = Not applicable
// 1 = Notification received in deferred mode, but response
//     sending was not allowed, and therefore notify-response
//     has not been sent to MMSC
// Another possibility, notification received in mmbox view list, 
// therefore no notify-response sent to MMSC,
const TUint32 KMmsDeferredButResponseNotSent = 0x00001000;

// The following flags are for all message types 

// bits reserved for future use
const TUint32 KMmsReservedMtmData2 =      0x00FFE000;


// bits reserved for UI usage
// MMS engine will not change these bits.
// The default value for these bits will be 0.
const TUint32 KMmsReservedForUI =         0xFF000000;

// End of MtmData bit definitions
// ------------------------------------------------------


// Unicode BOM
const TUint16 KMmsByteOrderMark = 0xFEFF;
const TUint16 KMmsReversedByteOrderMark = 0xFFFE;

// Maximum iDescription read from text/plain file in terms of characters. 
const TInt KMmsMaxDescription = 128;

// WSP assigned numbers
const TInt8 KUidMmsWSPMultiPartMixed = 0x23;
const TInt8 KUidMmsWSPMultiPartRelated = 0x33;

// MMS specific field assignments
// same values used for enum values in internal storage
const TUint8 KMmsMessageClassPersonal = 128;
const TUint8 KMmsMessageClassAdvertisement = 129;
const TUint8 KMmsMessageClassInformational = 130;
const TUint8 KMmsMessageClassAuto = 131;

// X-Mms-Message-Type field
// message types since encaps 1.0
const TUint8 KMmsMessageTypeMSendReq = 128;
const TUint8 KMmsMessageTypeMSendConf = 129;
const TUint8 KMmsMessageTypeMNotificationInd = 130;
const TUint8 KMmsMessageTypeMNotifyRespInd = 131;
const TUint8 KMmsMessageTypeMRetrieveConf = 132;
const TUint8 KMmsMessageTypeAcknowledgeInd = 133;
const TUint8 KMmsMessageTypeDeliveryInd = 134;
// message types since encaps 1.1
const TUint8 KMmsMessageTypeReadRecInd = 135;
const TUint8 KMmsMessageTypeReadOrigInd = 136;
const TUint8 KMmsMessageTypeForwardReq = 137;
const TUint8 KMmsMessageTypeForwardConf = 138;
// message types since encaps 1.2
const TUint8 KMmsMessageTypeMboxStoreReq = 139;
const TUint8 KMmsMessageTypeMboxStoreConf = 140;
const TUint8 KMmsMessageTypeMboxViewReq = 141;
const TUint8 KMmsMessageTypeMboxViewConf = 142;
const TUint8 KMmsMessageTypeMBoxUploadReq = 143;
const TUint8 KMmsMessageTypeMBoxUploadConf = 144;
const TUint8 KMmsMessageTypeMBoxDeleteReq = 145;
const TUint8 KMmsMessageTypeMBoxDeleteConf = 146;
const TUint8 KMmsMessageTypeMBoxDescr = 147;

// X-Mms-Priority field
const TUint8 KMmsPriorityLow = 128;
const TUint8 KMmsPriorityNormal = 129;
const TUint8 KMmsPriorityHigh = 130;

// All fields with Yes/No value
const TUint8 KMmsYes = 128;
const TUint8 KMmsNo = 129;

// X-Mms-Sender-Visibility field
const TUint8 KMmsSenderHide = 128;
const TUint8 KMmsSenderShow = 129;

// X-Mms-Status field
const TUint8 KMmsMessageStatusExpired = 128;
const TUint8 KMmsMessageStatusRetrieved = 129;
const TUint8 KMmsMessageStatusRejected = 130;
const TUint8 KMmsMessageStatusDeferred = 131;
const TUint8 KMmsMessageStatusUnrecognized = 132;
const TUint8 KMmsMessageStatusIndeterminate = 133;
const TUint8 KMmsMessageStatusForwarded = 134;
const TUint8 KMmsMessageStatusUnreachable = 135;

// X-Mms-Read-Status field
const TUint8 KMmsReadStatusRead = 128;
const TUint8 KMmsReadStatusDeletedWithoutBeingRead = 129;

// X-Mms-Reply-Charging field
const TUint8 KMmsReplyChargingRequested = 128;
const TUint8 KMmsReplyChargingRequestedTextOnly = 129;
const TUint8 KMmsReplyChargingAccepted = 130;
const TUint8 KMmsReplyChargingAcceptedTextOnly = 131;

// field assignments since MMS encapsulation 1.2

// X-Mms-Mbox-Quotas field & // X-Mms-MBox-Totals field
const TUint8 KMmsMessageCountToken = 128;
const TUint8 KMmsMessageSizeToken = 129;

// X-Mms-MM-Flags field
const TUint8 KMmsAddToken = 128;
const TUint8 KMmsRemoveToken = 129;
const TUint8 KMmsFilterToken = 130;

// X-Mms-MM-State field
const TUint8 KMmsDraft = 128;
const TUint8 KMmsSent = 129;
const TUint8 KMmsNew = 130;
const TUint8 KMmsRetrieved = 131;
const TUint8 KMmsForwarded = 132;

// end of field assignments

// All content type strings are in KContentTypeTable
// some are defined here to be used separately
_LIT8( KMmsAny, "*/*" );
_LIT8( KMmsTextPlain, "text/plain" );
_LIT8( KMmsApplicationSmil, "application/smil" );
_LIT8( KMmsUnknownType, "application/octet-stream" );
_LIT8( KMmsMultipartReport, "multipart/report" );

// DRM Content Types
_LIT8( KMmsDrmMessageCT, "application/vnd.oma.drm.message" ); // DRM Message
_LIT8( KMmsDrmContentCT, "application/vnd.oma.drm.content" ); // DRM Content
_LIT8( KMmsDrmRightsTFCT, "application/vnd.oma.drm.rights+xml" ); // DRM Rights in textual format
_LIT8( KMmsDrmRightsBFCT, "application/vnd.oma.drm.rights+wbxml" ); // DRM Rights in binary format

// Assigned numbers for content types
// If new assignments are needed, check numbers from KContentTypeTable
const TUint8 KMmsAssignedAny = 0x00;
const TUint8 KMmsAssignedText = 0x01;
const TUint8 KMmsAssignedTextPlain = 0x03;
const TUint8 KMmsAssignedApplicationVndWapMultipart = 0x22;
const TUint8 KMmsAssignedApplicationVndWapMultipartMixed = 0x23;
const TUint8 KMmsAssignedApplicationVndWapMultipartAlternative = 0x26;
const TUint8 KMmsAssignedApplicationXml = 0x27;
const TUint8 KMmsAssignedApplicationVndWapWbxml = 0x29;
const TUint8 KMmsAssignedApplicationVndWapMultipartRelated = 0x33;

// Assigned numbers for WSP/HTTP status codes
// Informative 1xx
const TUint8 KMmsAssignedContinue = 0x10;
const TUint8 KMmsAssignedSwitchingProtocols = 0x11;
// Successful 2xx
const TUint8 KMmsAssignedOk = 0x20;
const TUint8 KMmsAssignedCreated = 0x21;
const TUint8 KMmsAssignedAccepted = 0x22;
const TUint8 KMmsAssignedNonAuthoritativeInformation = 0x23;
const TUint8 KMmsAssignedNoContent = 0x24;
const TUint8 KMmsAssignedResetContent = 0x25;
const TUint8 KMmsAssignedPartialContent = 0x26;
// MultipleChoices 3xx
const TUint8 KMmsAssignedMultipleChoices = 0x30;
const TUint8 KMmsAssignedMovedPermanently = 0x31;
const TUint8 KMmsAssignedMovedTemporarily = 0x32;
const TUint8 KMmsAssignedSeeOther = 0x33;
const TUint8 KMmsAssignedNotModified = 0x34;
const TUint8 KMmsAssignedUseProxy = 0x35;
// Client error 4xx
const TUint8 KMmsAssignedBadRequest = 0x40;
const TUint8 KMmsAssignedUnauthorized = 0x41;
const TUint8 KMmsAssignedPaymentRequired = 0x42;
const TUint8 KMmsAssignedForbidden = 0x43;
const TUint8 KMmsAssignedNotFound = 0x44;
const TUint8 KMmsAssignedMethodNotAllowed = 0x45;
const TUint8 KMmsAssignedNotAcceptable = 0x46;
const TUint8 KMmsAssignedProxyAuthenticationRequired = 0x47;
const TUint8 KMmsAssignedRequestTimeout = 0x48;
const TUint8 KMmsAssignedConflict = 0x49;
const TUint8 KMmsAssignedGone = 0x4A;
const TUint8 KMmsAssignedLengthRequired = 0x4B;
const TUint8 KMmsAssignedPreconditionFailed = 0x4C;
const TUint8 KMmsAssignedRequestEntityTooLarge = 0x4D;
const TUint8 KMmsAssignedRequestUriTooLarge = 0x4E;
const TUint8 KMmsAssignedUnsupportedMediaType = 0x4F;
// Server error 6xx
const TUint8 KMmsAssignedInternalServerError = 0x60;
const TUint8 KMmsAssignedNotImplemented = 0x61;
const TUint8 KMmsAssignedBadGateway = 0x62;
const TUint8 KMmsAssignedServiceUnavailable = 0x63;
const TUint8 KMmsAssignedGatewayTimeout = 0x64;
const TUint8 KMmsAssignedHttpVersionNotSupported = 0x65;

const TUint8 KMmsUnAssigned = 0x37;

const TInt KNumberContentTypes = KMmsUnAssigned;
// The following is a gapless table where the corresponding
// assigned numbers must run from 0 to KMmsUnAssigned - 1.
// If new content types are added to the table, and the assigned
// numbers are not contiguous dummy entries must be inserted, but
// if these would become too numerous, a two-table system must be
// constructed.
// At the moment one table is enough, as all well-known content types
// have contiguous assigned numbers. 
static const TText8* const KContentTypeTable[] = 
    {
    _S8( "*/*" ),                                       //0x00
    _S8( "text/*" ),                                    //0x01
    _S8( "text/html" ),                                 //0x02
    _S8( "text/plain" ),                                //0x03
    _S8( "text/x-hdml" ),                               //0x04
    _S8( "text/x-ttml" ),                               //0x05
    _S8( "text/x-vCalendar" ),                          //0x06
    _S8( "text/x-vCard" ),                              //0x07
    _S8( "text/vnd.wap.wml" ),                          //0x08
    _S8( "text/vnd.wap.wmlscript" ),                    //0x09
    _S8( "text/vnd.wap.channel" ),                      //0x0A
    _S8( "Multipart/*" ),                               //0x0B
    _S8( "Multipart/mixed" ),                           //0x0C
    _S8( "Multipart/form-data" ),                       //0x0D
    _S8( "Multipart/byteranges" ),                      //0x0E
    _S8( "multipart/alternative" ),                     //0x0F
    _S8( "application/*" ),                             //0x10
    _S8( "application/java-vm" ),                       //0x11    
    _S8( "application/x-www-form-urlencoded" ),         //0x12
    _S8( "application/x-hdmlc" ),                       //0x13
    _S8( "application/vnd.wap.wmlc" ),                  //0x14
    _S8( "application/vnd.wap.vmlscriptc" ),            //0x15
    _S8( "application/vnd.wap.channelc" ),              //0x16
    _S8( "application/vnd.wap.uaprof" ),                //0x17
    _S8( "application/vnd.wap.wtls-ca-certificate" ),   //0x18
    _S8( "application/vnd.wap.wtls-user-certificate" ), //0x19
    _S8( "application/x-x509-ca-cert" ),                //0x1A
    _S8( "application/x-x509-user-cert" ),              //0x1B
    _S8( "image/*" ),                                   //0x1C
    _S8( "image/gif" ),                                 //0x1D
    _S8( "image/jpeg"),                                 //0x1E
    _S8( "image/tiff" ),                                //0x1F
    _S8( "image/png" ),                                 //0x20
    _S8( "image/vnd.wap.wbmp" ),                        //0x21
    _S8( "application/vnd.wap.multipart.*" ),           //0x22
    _S8( "application/vnd.wap.multipart.mixed" ),       //0x23
    _S8( "application/vnd.wap.multipart.form-data" ),   //0x24
    _S8( "application/vnd.wap.multipart.byteranges" ),  //0x25
    _S8( "application/vnd.wap.multipart.alternative" ), //0x26
    _S8( "application/xml" ),                           //0x27
    _S8( "text/xml" ),                                  //0x28
    _S8( "application/vnd.wap.wbxml" ),                 //0x29
    _S8( "application/x-x968-cross-cert" ),             //0x2A
    _S8( "application/x-x968-ca-cert" ),                //0x2B
    _S8( "application/x-x968-user-cert" ),              //0x2C
    _S8( "text/vnd.wap.si" ),                           //0x2D
    _S8( "application/vnd.wap.sic" ),                   //0x2E
    _S8( "text/vnd.wap.sl" ),                           //0x2F
    _S8( "text/vnd.wap.slc" ),                          //0x30
    _S8( "text/vnd.wap.co" ),                           //0x31
    _S8( "application/vnd.wap.coc" ),                   //0x32
    _S8( "application/vnd.wap.multipart.related" ),     //0x33
    _S8( "application/vnd.wap.sia" ),                   //0x34
    _S8( "text/vnd.wap.connectivity-xml" ),             //0x35
    _S8( "application/vnd.wap.connectivity-wbxml" ),    //0x36
    // This must always be the last one.
    // This is the type that all unassigned numbers get:
    // Even if we have an actual assigned number for
    // application/octet-stream some day, there must be
    // this duplicate entry at the end of the table to
    // handle mapping of unknown assigned numbers
    _S8( "application/octet-stream" )                   //KMmsUnAssigned
    };

// IANA / WSP numbers for character sets
const TUint8 KMmsUtf8 = 0x6A;
const TUint8 KMmsUsAscii = 0x03;
const TUint KMmsIso10646Ucs2 = 0x03E8; // 1000
const TUint KMmsUTF16 = 0x03F7; // 1015
const TUint KMmsUTF16BE = 0x03F5; // 1013
const TUint KMmsUTF16LE = 0x03F6; // 1014
const TUint KMmsUtf7 = 0x03F4; // 1012

// CR/LF definitions for removal...
_LIT ( KLf16, "\x00A" ); // 16 bit line feed
_LIT ( KCr16, "\x00D" ); // 16 bit carriage return
_LIT ( KSpace16, " " ); // 16 bit space
_LIT ( KEqualsQuestion16, "=?" ); // MIME encoding starter
_LIT ( KQuote16, "\x022" ); // 16 bit quote
_LIT ( KMmsUnicodeLineSeparator, "\x2028");
_LIT ( KMmsUnicodeParagraphSeparator, "\x2029");
_LIT ( KMmsIdeographicSpace, "\x3000");
_LIT8 ( KLf8, "\x00A" ); // 8 bit line feed
_LIT8 ( KCr8, "\x00D" ); // 8 bit carriage return
_LIT8 ( KSpace8, " " ); // 8 bit space
_LIT8 ( KSemicolon8, ";" ); // 8 bit semicolon
_LIT8 ( KEquals8, "=" ); // 8 bit equal 

// Validity limits for values that are not enums.
// If different products need different validity
// limits, differences are controlled by conditional
// compilation

// max expiry: 168 hours (one week) expressed in seconds
const TInt KMmsMaxExpiry = 168 * 3600;

// Thses image size limits are deprecated.
// UI should define its own constants.
// MMS engine does not use these values.
//160*120 
const TInt KMmsImageMinWidth = 160;  // deprecated
const TInt KMmsImageMinHeight = 120; // deprecated
//640*480
const TInt KMmsImageMaxWidth = 640;  // deprecated
const TInt KMmsImageMaxHeight = 480; // deprecated

// MACROS

// DATA TYPES

// Possible address types
enum TMmsAddressType
    {
    EMmsAddressTypeUnknown = 0,
    EMmsAddressTypeMobile,
    EMmsAddressTypeEmail, 
    EMmsAddressTypeIpv4,
    EMmsAddressTypeIpv6
    };

// These panics should only be used in ASSERT_DEBUGs
// (The user should not see these)
enum TMmsPanic // MMS error codes
    {
    EMmsBadMtmTypeUid = KErrNone+1,
    EMmsNoCMsvEntrySet,
    EMmsEntryTypeNotSupported,
    EMmsHeadersNotFound,
    EMmsAlreadyBusy,
    EMmsUnknownState,
    EMmsActiveInFinalProgress,
    EMmsFinalProgressFailed 
    };
 

// Values for recipient types 
enum TMmsRecipients
    {
    EMmsTo = 1, 
    EMmsCc,
    EMmsBcc
    };

// Values for message class 
enum TMmsMessageClass
    {
    EMmsMimimumMessageClass = KMmsMessageClassPersonal,
    EMmsClassPersonal = KMmsMessageClassPersonal, 
    EMmsClassAdvertisement = KMmsMessageClassAdvertisement,
    EMmsClassInformational = KMmsMessageClassInformational,
    EMmsClassAuto = KMmsMessageClassAuto,
    // change following if new message classes are added
    EMmsMaximumMessageClass = KMmsMessageClassAuto
    };

// Values for message priority
enum TMmsMessagePriority
    {
    EMmsMinimumPriority = KMmsPriorityLow,
    EMmsPriorityLow = KMmsPriorityLow, 
    EMmsPriorityNormal = KMmsPriorityNormal,
    EMmsPriorityHigh = KMmsPriorityHigh,
    // change following if new priorities added
    EMmsMaximumPriority = KMmsPriorityHigh
    };

// Values for message Sender-Visibility
enum TMmsMessageSenderVisibility
    {
    EMmsSenderVisibilityDefault = 0,
    EMmsMinimumSenderVisibility = KMmsSenderHide, // always minimum
    EMmsSenderVisibilityHide = KMmsSenderHide, 
    EMmsSenderVisibilityShow = KMmsSenderShow,
    EMmsMaximumSenderVisibility = KMmsSenderShow // change if new values added
    };

// Values for message Delivery-Report
enum TMmsMessageDeliveryReport
    {
    EMmsDeliveryReportYes = KMmsYes, 
    EMmsDeliveryReportNo = KMmsNo
    };

// Values for Delivery-Report allowed
enum TMmsSettingsDeliveryReportAllowed
    {
    EMmsDeliveryReportAllowedYes = KMmsYes, 
    EMmsDeliveryReportAllowedNo = KMmsNo
    };

// Values for message Read-Reply
enum TMmsMessageReadReply
    {
    EMmsReadReplyYes = KMmsYes, 
    EMmsReadreplyNo = KMmsNo
    };

// Values for Read-Reply sending allowed
enum TMmsSettingsReadReplyAllowed
    {
    EMmsReadReplyAllowedYes = KMmsYes, 
    EMmsReadReplyAllowedNo = KMmsNo
    };

// Values for MMS Creation mode
enum TMmsCreationMode
    {
    EMmsCreationModeRestricted = 0, 
    EMmsCreationModeWarning = 1,
    EMmsCreationModeFree = 2
    };
 
// Values for Message-Type field
// correspond to binary encoding!
enum TMmsMessageType
    {
    EMmsMSendReq = KMmsMessageTypeMSendReq,
    EMmsMSendConf = KMmsMessageTypeMSendConf,
    EMmsNotificationInd = KMmsMessageTypeMNotificationInd,
    EMmsNotifyRespInd = KMmsMessageTypeMNotifyRespInd,
    EMmsRetrieveConf = KMmsMessageTypeMRetrieveConf,
    EMmsAcknowledgeInd = KMmsMessageTypeAcknowledgeInd,
    EMmsDeliveryInd = KMmsMessageTypeDeliveryInd,
    EMmsReadRecInd = KMmsMessageTypeReadRecInd,
    EMmsReadOrigInd = KMmsMessageTypeReadOrigInd,
    EMmsForwardReq = KMmsMessageTypeForwardReq,
    EMmsForwardConf = KMmsMessageTypeForwardConf
    };

// Values for Status field
// correspond to binary encoding!
enum TMmsMessageStatus
    {
    EMmsStatusExpired = KMmsMessageStatusExpired,
    EMmsStatusRetrieved = KMmsMessageStatusRetrieved,
    EMmsStatusRejected = KMmsMessageStatusRejected,
    EMmsStatusDeferred = KMmsMessageStatusDeferred,
    EMmsStatusUnrecognized = KMmsMessageStatusUnrecognized,
    EMmsStatusIndeterminate = KMmsMessageStatusIndeterminate,
    EMmsStatusForwarded = KMmsMessageStatusForwarded
    };

// Values for read status
// correspond to binary encoding!
enum TMmsReadStatus
    {
    EMmsReadStatusRead = KMmsReadStatusRead,
    EMmsReadStatusDeletedWithoutBeingRead = KMmsReadStatusDeletedWithoutBeingRead
    };

enum TMmsReplyCharging
    {
    EMmsReplyChargingRequested = KMmsReplyChargingRequested,
    EMmsReplyChargingRequestedTextOnly = KMmsReplyChargingRequestedTextOnly,
    EMmsReplyChargingAccepted = KMmsReplyChargingAccepted,
    EMmsReplyChargingAcceptedTextOnly = KMmsReplyChargingAcceptedTextOnly
    };

// mms receiving mode
enum TMmsReceivingMode
    {
    // first mode is default, must be set to 0:
    // If mode is not specified, it must default to "always enabled"

    // These modes control if acknowledgements or fetch requests
    // are sent to MMSC when notifications about new messages arrive.

    EMmsMinimumReceivingMode = 0,
    EMmsReceivingAlwaysEnabled = EMmsMinimumReceivingMode,
    EMmsReceivingEnabledInHomeNetwork,
    EMmsReceivingDisabled,
    EMmsReceivingManual,
    // change following if new modes added
    EMmsMaximumReceivingMode = EMmsReceivingManual
    };

// new mms receiving mode used in 2.6
enum TMmsNewReceivingMode
    {
    // These modes control if acknowledgements or fetch requests
    // are sent to MMSC when notifications about new messages arrive.
    // These modes control into which folder the notifications 
    // are finally stored.

    EMmsNewNotApplicable = 0,
    EMmsNewReceivingFetch = 1,
    EMmsNewReceivingManual = 2,
    EMmsNewReceivingPostpone = 3,
    EMmsNewReceivingReject = 4,
    // change following if new modes added
    EMmsNewMaximumReceivingMode = EMmsNewReceivingReject
    };


// message fetching state
enum TMmsSettingsFetchMode
    {
    // Modes that send acknowledgements to MMSC

    // Fetch everything that fits criteria, discard rest
    // (too big messages, advertisements etc.)
    // Fetching is tried until message expires.
    // Retry interval may be lengthened in some cases.
    EMmsMinimumFetchingMode = 1,
    EMmsFetchingOn = EMmsMinimumFetchingMode,

    // Send a reject response to everything
    EMmsFetchingOff,

    // Send a deferred response to everything until the
    // user switches fetching mode on again.
    // At that point fetch everything that has not expired
    EMmsFetchingDeferred,

    // change this is modes added
    EMmsMaximumFetchingMode = EMmsFetchingDeferred
    };

// Default speaker
enum TMmsSettingsDefaultSpeaker
    {
    EMmsMinimumDefaultSpeaker = 1,
    EMmsAudioSpeakerHandsfree = EMmsMinimumDefaultSpeaker,
    EMmsAudioSpeakerHandset = 2,
    // change following if new speakers added
    EMmsMaximumDefaultSpeaker = EMmsAudioSpeakerHandset
    };

// Factory settings
enum TMmsFactorySettingsLevel
    {
    EMmsFactorySettingsLevelNormal = 0x0,
    EMmsFactorySettingsLevelDeep 
    };

// Type of the Delete operation
enum TMmsDeleteOperationType
    {
    EMmsDeleteNotificationOnly, 
    EMmsDeleteMMBoxOnly,
    EMmsDeleteBoth
    };

class TCommandParameters
    {
    public:
        inline TCommandParameters();
        // The delay to wait before operation is started.
        // if 0, delay is determined by hard-coded default value
        // (a small delay, for example 10 seconds, exact value must
        // be determined when hardware timing is better known)
        // This parameter is intended to be used to initiate
        // retry operation after a delay (for example 10 minutes)
        TTimeIntervalSeconds iInitialDelay;
        // only schedule entries that have failed because of following error
        // if iError == KErrNone, everything is rescheduled
        TInt iError; 
    };

typedef TPckgBuf<TCommandParameters> TCommandParametersBuf;

TCommandParameters::TCommandParameters():
iInitialDelay( 0 ),
iError( 0 )
    {
    }

#endif      // MMSCONST_H
            
// End of File
