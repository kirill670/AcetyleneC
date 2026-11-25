// WspError.h
//
// Copyright (C) 2001 Symbian Ltd
//  

#ifndef __WSPERROR_H__
#define __WSPERROR_H__

// System includes
#include <e32std.h>
#include <httperr.h>

// Constants used in this file
const TInt KWspErrorBase = KHttpErrorBase - 180;

/// @todo docing

enum TWspError
	{
	KWspErrServiceNumberNotDefined			= KWspErrorBase,
	KWspErrAccessPointNotSetUp				= KWspErrorBase - 1,
	KWspErrBadRedirectedAddressData			= KWspErrorBase - 2,
	KWspErrBearerNotSupported				= KWspErrorBase - 3,
	KWspErrRequestTooBig					= KWspErrorBase - 4,
	KWspErrStreamedRequestDataNotSupported	= KWspErrorBase - 5,	
	KWspErrUnsupportedSendPrimitive			= KWspErrorBase - 6,
	KWspErrSessionClosingOrSuspending		= KWspErrorBase - 7,
	KWspErrExpectingBodyData				= KWspErrorBase - 8,
	KWspErrTrailerHeadersNotExpected		= KWspErrorBase - 9,
	KWspErrMissingHeader					= KWspErrorBase - 10,
	KWspErrSMSBearerNotInCommsDB			= KWspErrorBase - 11,
	KWspErrCouldNotCreateTransportHandler	= KWspErrorBase - 12,
	KWspErrRequiredServicesNotSupported		= KWspErrorBase - 13,
	KWtlsErrConfigurationFailed				= KWspErrorBase - 14,
	KWtlsErrPhase1HandshakeFailed			= KWspErrorBase - 15,
	KWtlsErrPhase2HandshakeFailed			= KWspErrorBase - 16,
	KWtlsErrInvalidServerCert				= KWspErrorBase - 17,
	KWtlsErrUntrustedServerCert				= KWspErrorBase - 18,
	KWtlsErrNegotiatedConfigRejected		= KWspErrorBase - 19
	};

#endif //  __WSPERROR_H__
