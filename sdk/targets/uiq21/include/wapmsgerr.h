// WAPMSGERR.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __WAPMSGERR_H__
#define __WAPMSGERR_H__

#include <e32base.h>

namespace Wap
	{
	_LIT(KWapMsgPanicDescriptor, "WAPMESSAGE");

enum 
	{
	ERetCodeBase      = -5500,
	EWSPCORetCodeBase = ERetCodeBase + 25,
	EWSPCLRetCodeBase = ERetCodeBase + 50,
	EWTPRetCodeBase   = ERetCodeBase + 75,
	EWDPRetCodeBase   = ERetCodeBase + 100,
	EWTLSRetCodeBase  = ERetCodeBase + 125,
	ERetCodeTop       = ERetCodeBase + 200
	};
enum TGeneralReturnCodes
	{  
	EMoreData           = ERetCodeBase + 0,
	EBearerError        = ERetCodeBase + 1,
	EPortAlreadyBound   = ERetCodeBase + 2,
	ECannotOpenPort     = ERetCodeBase + 3,
	ETooManyConnections = ERetCodeBase + 4,
	EBadConnection      = ERetCodeBase + 5,
	EBufferTooSmall     = ERetCodeBase + 6
	};

enum TWtlsReturnCodes
	{
	EWtlsOutOfMemory            = EWTLSRetCodeBase + 0,
	EWtlsSocketError            = EWTLSRetCodeBase + 1,
	EWtlsBadParameters          = EWTLSRetCodeBase + 2,
	EWtlsSocketError2           = EWTLSRetCodeBase + 3,
	EWtlsResumeIDNotFound       = EWTLSRetCodeBase + 4,
	EWtlsResumeError            = EWTLSRetCodeBase + 5,
	EWtlsRenegotiationRequest   = EWTLSRetCodeBase + 6,
	EWtlsIllegalCall            = EWTLSRetCodeBase + 7,
	EWtlsConnectionCloseNotify  = EWTLSRetCodeBase + 8,
	EWtlsSessionCloseNotify     = EWTLSRetCodeBase + 9,
	EWtlsNoConnection           = EWTLSRetCodeBase + 10,
	EWtlsUnexpectedMessage      = EWTLSRetCodeBase + 11,
	EWtlsBadRecordMac           = EWTLSRetCodeBase + 12,
	EWtlsDecryptionFailed       = EWTLSRetCodeBase + 13,
	EWtlsRecordOverflow         = EWTLSRetCodeBase + 14,
	EWtlsHandshakeFailure       = EWTLSRetCodeBase + 15,
	EWtlsDecompressionFailure   = EWTLSRetCodeBase + 16,
	EWtlsBadCertificate         = EWTLSRetCodeBase + 17,
	EWtlsUnsupportedCertificate = EWTLSRetCodeBase + 18,
	EWtlsCertificateRevoked     = EWTLSRetCodeBase + 19,
	EWtlsCertificateExpired     = EWTLSRetCodeBase + 20,
	EWtlsCertificateUnknown     = EWTLSRetCodeBase + 21,
	EWtlsIllegalParameter       = EWTLSRetCodeBase + 22,
	EWtlsUnknownCA              = EWTLSRetCodeBase + 23,
	EWtlsAccessDenied           = EWTLSRetCodeBase + 24,
	EWtlsDecodeError            = EWTLSRetCodeBase + 25,
	EWtlsDecryptError           = EWTLSRetCodeBase + 26,
	EWtlsUnknownKeyId           = EWTLSRetCodeBase + 27,
	EWtlsDisableKeyId           = EWTLSRetCodeBase + 28,
	EWtlsKeyExchangeDisabled    = EWTLSRetCodeBase + 29,
	EWtlsSessionNotReady        = EWTLSRetCodeBase + 30,
	EWtlsUnknownParameterIndex  = EWTLSRetCodeBase + 31,
	EWtlsDuplicateFinishedRecv  = EWTLSRetCodeBase + 32,
	EWtlsExportRestriction      = EWTLSRetCodeBase + 33,
	EWtlsProtocolVersion        = EWTLSRetCodeBase + 34,
	EWtlsInsufficientSecurity   = EWTLSRetCodeBase + 35,
	EWtlsInternalError          = EWTLSRetCodeBase + 36,
	EWtlsUserCanceled           = EWTLSRetCodeBase + 37,
	EWtlsNoRenegotiation        = EWTLSRetCodeBase + 38,

	EWtlsErrGeneral             = EWTLSRetCodeBase + 39,
	EWtlsErrBulk                = EWTLSRetCodeBase + 40,
	EWtlsErrMac                 = EWTLSRetCodeBase + 41,
	EWtlsErrSequenceNumberMode  = EWTLSRetCodeBase + 42,
	EWtlsErrKeyRefreshRate      = EWTLSRetCodeBase + 43,

	};

enum TWspCoReturnCodes
	{
	EWspCoBufferTooSmall      = EWSPCORetCodeBase + 0,
	EWspCoInvalidSession      = EWSPCORetCodeBase + 1,
	EWspCoInvalidTransaction  = EWSPCORetCodeBase + 2,
	EWspCoParameterError      = EWSPCORetCodeBase + 3,
	EWspCoSessionNotConnected = EWSPCORetCodeBase + 4,
	EWspCoNotSupported        = EWSPCORetCodeBase + 5,
	EWspCoInvalidState        = EWSPCORetCodeBase + 6,
	EWspCoSessionClosed       = EWSPCORetCodeBase + 7,
	EWspCoMRUExceeded         = EWSPCORetCodeBase + 8,
	EWspCoInvalidBufferSize   = EWSPCORetCodeBase + 9,
	EWspCoDataNotAvailable    = EWSPCORetCodeBase + 10,
	EWspCoErrorTimeout        = EWSPCORetCodeBase + 11
	};
	

enum TWspClReturnCodes
	{			
	EWspClBufferTooSmall      = EWSPCLRetCodeBase + 0,
	EWspClInvalidSession      = EWSPCLRetCodeBase + 1,
	EWspClParameterError      = EWSPCLRetCodeBase + 2,
	EWspClSessionNotConnected = EWSPCLRetCodeBase + 3,
	EWspClNotSupported        = EWSPCLRetCodeBase + 4,
	EWspClInvalidState        = EWSPCLRetCodeBase + 5,
	EWspClSessionClosed       = EWSPCLRetCodeBase + 6,
	EWspClMRUExceeded		 = EWSPCLRetCodeBase + 7,	
	EWspClInvalidBufferSize   = EWSPCLRetCodeBase + 8,
	EWspClDataNotAvailable    = EWSPCLRetCodeBase + 9,
	EWspClErrorTimeout        = EWSPCLRetCodeBase + 10
	};

enum TWtpReturnCodes
	{
	EWtpNoMemory                 = EWTPRetCodeBase + 0,
	EWtpBadArgument              = EWTPRetCodeBase + 1,
	EWtpProviderProtoErr         = EWTPRetCodeBase + 2,
	EWtpProviderAbortInvalidTID  = EWTPRetCodeBase + 3,
	EWtpProviderAbortNoClass2    = EWTPRetCodeBase + 4,
	EWtpProviderAbortNoSAR       = EWTPRetCodeBase + 5,
	EWtpProviderAbortNoUACK      = EWTPRetCodeBase + 6,
	EWtpProviderAbortVers1       = EWTPRetCodeBase + 7,
	EWtpProviderAbortNoResponse  = EWTPRetCodeBase + 8,
	EWtpProviderAbortMsgTooLarge = EWTPRetCodeBase + 9,
	EWtpProviderAbortGeneral     = EWTPRetCodeBase + 10,
	EWtpShutdownError            = EWTPRetCodeBase + 11
	};
}

#endif // __WAPMSGERR_H__
