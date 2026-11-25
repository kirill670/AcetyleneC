// httperr.h
//
// Copyright (C) 2001 Symbian Ltd
 
/** 
	@file httperr.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __HTTPERR_H__
#define __HTTPERR_H__

// System includes
#include <e32std.h>

/** 
	@public
	@class			HTTPStatus
	@since			7.0
	The complete set of HTTP Status codes, as defined in RFC2616.
 */

//##ModelId=3C4C18750141
class HTTPStatus
	{
public:
	enum
		{
		/** 'Informational' range of codes 1xx */
		EContinue						= 100,
		ESwitchingProtocols				= 101,
		/** 'Successful' range of codes 2xx */
		EOk								= 200,
		ECreated						= 201,
		EAccepted						= 202,
		ENonAuthoritativeInfo			= 203,
		ENoContent						= 204,
		EResetContent					= 205,
		EPartialContent					= 206,
		/** 'Redirection' range of codes 3xx */
		EMultipleChoices				= 300,
		EMovedPermanently				= 301,
		EFound							= 302, // Note, this is deprecated in HTTP/1.1 - 307 will be used instead
		ESeeOther						= 303,
		ENotModified					= 304,
		EUseProxy						= 305,
		EUnused							= 306,
		ETemporaryRedirect				= 307,
		/** 'Client Error' range of codes 4xx */
		EBadRequest						= 400,
		EUnauthorized					= 401,
		EPaymentRequired				= 402, // Note, this is reserved in HTTP/1.1
		EForbidden						= 403,
		ENotFound						= 404,
		EMethodNotAllowed				= 405,
		ENotAcceptable					= 406,
		EProxyAuthenticationRequired	= 407,
		ERequestTimeout					= 408,
		EConflict						= 409,
		EGone							= 410,
		ELengthRequired					= 411,
		EPreconditionFailed				= 412,
		ERequestEntityTooLarge			= 413,
		ERequestURITooLong				= 414,
		EUnsupportedMediaType			= 415,
		ERequestedRangeNotSatisfiable	= 416,
		EExpectationFailed				= 417,
		/** 'Server Error' range of codes 5xx */
		EInternalServerError			= 500,
		ENotImplemented					= 501,
		EBadGateway						= 502,
		EServiceUnavailable				= 503,
		EGatewayTimeout					= 504,
		EHTTPVersionNotSupported		= 505
		};

	/** Is the supplied status code in the 1xx Informational range? */
	//##ModelId=3C4C18750162
	inline static TBool IsInformational(TInt aStatus);
	/** Is the supplied status code in the 2xx Successful range? */
	//##ModelId=3C4C18750160
	inline static TBool IsSuccessful(TInt aStatus);
	/** Is the supplied status code in the 3xx Redirection range? */
	//##ModelId=3C4C18750159
	inline static TBool IsRedirection(TInt aStatus);
	/** Is the supplied status code in the 4xx Client Error range? */
	//##ModelId=3C4C18750157
	inline static TBool IsClientError(TInt aStatus);
	/** Is the supplied status code in the 5xx Server Error range? */
	//##ModelId=3C4C18750155
	inline static TBool IsServerError(TInt aStatus);
	};

//
// HTTP Panic codes
//

#include <e32base.h>

// HTTPPanic::Panic(HTTPPanic:: )

//##ModelId=3C4C18740352
class HTTPPanic
	{
public:
	enum THTTPPanic
		{
		ESessionAlreadyOpen,
		EHeaderFieldMissing,
		EHeaderParamMissing,
		EHeaderInvalidPart,
		EHeaderInvalidType,
		ETransactionEventOutstanding,
		ETransactionUnhandledError,
		EAddingFilterWithOutstandingTransactions,
		EFilterInvalidPosition,
		EHTTPFormDataUnreleased,
		EHTTPFormSupplyingData,
		EValidationFilterFailure,
		EInvalidTxData,
		EInvalidRxData,
		ENoTransportHandlerSet,
		EAuthenticationFilterBadState,
		EInvalidFilterHandle
		};

	//##ModelId=3C4C18740366
	static void Panic(THTTPPanic aPanic);
	};

// HTTP external errors/leave codes. Add new sub-ranges at the end; do not insert between the sub-ranges that
// are already here.  This is to allow a client to reasonably check for errors between two adjacent range
// base values rather than check for individual codes.

// Base value for the HTTP error code range (-7200 to -7399)
const TInt KHttpErrorBase = -7200;

//
// Text mode HTTP protocol handler
//

/// Codec encoding errors for HTTP headers
const TInt KHttpHeaderEncodeErrorBase = KHttpErrorBase;

const TInt KErrHttpEncodeDefault			= KHttpHeaderEncodeErrorBase;	  ///< error making a default encoding of unrecognised headers
const TInt KErrHttpEncodeAccept				= KHttpHeaderEncodeErrorBase - 1; ///< error encoding the Accept field
const TInt KErrHttpEncodeAcceptCharset		= KHttpHeaderEncodeErrorBase - 2; ///< error encoding the Accept-Charset field
const TInt KErrHttpEncodeQValue				= KHttpHeaderEncodeErrorBase - 3; ///< error encoding a q-value parameter
const TInt KErrHttpEncodeAuthorization		= KHttpHeaderEncodeErrorBase - 4; ///< error encoding the Authorization field
const TInt KErrHttpEncodeBasicAuth			= KHttpHeaderEncodeErrorBase - 5; ///< error encoding Basic credentials
const TInt KErrHttpEncodeDigestAuth			= KHttpHeaderEncodeErrorBase - 6; ///< error encoding Digest credentials
const TInt KErrHttpEncodeConnection			= KHttpHeaderEncodeErrorBase - 7; ///< error encoding the Connection field
const TInt KErrHttpEncodeContentLength		= KHttpHeaderEncodeErrorBase - 8; ///< error encoding the Content-Length field
const TInt KErrHttpEncodeContentType		= KHttpHeaderEncodeErrorBase - 9; ///< error encoding the Content-Type field
const TInt KErrHttpEncodeHost				= KHttpHeaderEncodeErrorBase - 10;///< error encoding the Host field
const TInt KErrHttpEncodeHostPort			= KHttpHeaderEncodeErrorBase - 11;///< error encoding the Host field's port parameter
const TInt KErrHttpEncodeTransferEncoding	= KHttpHeaderEncodeErrorBase - 12;///< error encoding the Transfer-Encoding field
const TInt KErrHttpEncodeUserAgent			= KHttpHeaderEncodeErrorBase - 13;///< error encoding the User-Agent field
const TInt KErrHttpEncodeDate				= KHttpHeaderEncodeErrorBase - 14;///< error encoding the Date field
const TInt KErrHttpEncodeCookie				= KHttpHeaderEncodeErrorBase - 15;///< error encoding the Cookie field 
const TInt KErrHttpEncodeCacheControl		= KHttpHeaderEncodeErrorBase - 16;///< error encoding the Cache-Control field 
const TInt KErrHttpEncodePragma				= KHttpHeaderEncodeErrorBase - 17;///< error encoding the Pragma field 
const TInt KErrHttpEncodeIfMatch			= KHttpHeaderEncodeErrorBase - 18;///< error encoding the if match field 
const TInt KErrHttpEncodeIfNoneMatch		= KHttpHeaderEncodeErrorBase - 19;///< error encoding the if none match field 
const TInt KErrHttpEncodeIfModifiedSince	= KHttpHeaderEncodeErrorBase - 20;///< error encoding the if modified since field 
const TInt KErrHttpEncodeIfUnmodifiedSince	= KHttpHeaderEncodeErrorBase - 21;///< error encoding the if unmodified since field 
const TInt KErrHttpEncodeCookie2			= KHttpHeaderEncodeErrorBase - 22;///< error encoding the Cookie2 field 

// Codec decoding errors for values found in HTTP headers
const TInt KHttpValueDecodeErrorBase = KHttpErrorBase - 60;

const TInt KErrHttpDecodeMalformedDate		= KHttpValueDecodeErrorBase;	 ///< general formatting error for date values
const TInt KErrHttpDecodeMalformedYear 		= KHttpValueDecodeErrorBase - 1; ///< malformed year
const TInt KErrHttpDecodeMalformedMonth		= KHttpValueDecodeErrorBase - 2; ///< malformed short month name
const TInt KErrHttpDecodeMalformedDay		= KHttpValueDecodeErrorBase - 3; ///< malformed number of day in month
const TInt KErrHttpDecodeMalformedWkDay		= KHttpValueDecodeErrorBase - 4; ///< malformed short day name
const TInt KErrHttpDecodeMalformedWeekDay	= KHttpValueDecodeErrorBase - 5; ///< malformed long day name
const TInt KErrHttpDecodeMalformedInteger	= KHttpValueDecodeErrorBase - 6; ///< malformed integer value
const TInt KErrHttpDecodeMalformedQuotedStr	= KHttpValueDecodeErrorBase - 7; ///< malformed quoted string

// Codec decoding errors for HTTP headers
const TInt KHttpHeaderDecodeErrorBase = KHttpErrorBase - 70;

const TInt KErrHttpDecodeAccept				= KHttpHeaderDecodeErrorBase;
const TInt KErrHttpDecodeConnection			= KHttpHeaderDecodeErrorBase - 1;///< error decoding the Connection field
const TInt KErrHttpDecodeContentLength		= KHttpHeaderDecodeErrorBase - 2;///< error decoding the Content-Length field
const TInt KErrHttpDecodeContentType		= KHttpHeaderDecodeErrorBase - 3;///< error decoding the Content-Type field
const TInt KErrHttpDecodeTransferEncoding	= KHttpHeaderDecodeErrorBase - 4;///< error decoding the Transfer-Encoding field
const TInt KErrHttpDecodeWWWAuthenticate	= KHttpHeaderDecodeErrorBase - 5;///< error decoding the WWWAuthenticate field
const TInt KErrHttpDecodeUnknownAuthScheme	= KHttpHeaderDecodeErrorBase - 6;///< the WWWAuthenticate field contained an unrecognised authentication scheme
const TInt KErrHttpDecodeBasicAuth			= KHttpHeaderDecodeErrorBase - 7;///< error decoding a Basic WWWAuthenticate challenge
const TInt KErrHttpDecodeDigestAuth			= KHttpHeaderDecodeErrorBase - 8;///< error decoding a Digest WWWAuthenticate challenge
const TInt KErrHttpDecodeCookie				= KHttpHeaderDecodeErrorBase - 9;///< error decoding a Set-Cookie field

// Response errors. These represent specific failure cases
const TInt KErrHttpResponseFailureBase = KHttpErrorBase - 100;

const TInt KErrHttpRedirectExceededLimit		= KErrHttpResponseFailureBase;	  ///< a uri redirected too many times, possibly indicating a circular redirection
const TInt KErrHttpRedirectUseProxy				= KErrHttpResponseFailureBase - 1;///< a server responded that the uri must be fetched via a proxy
const TInt KErrHttpRedirectNoLocationField		= KErrHttpResponseFailureBase - 2;///< a server sent a redirection response that did not include a Location header
const TInt KErrHttpUnknownParseState			= KErrHttpResponseFailureBase - 3;///< an error occured in parsing which left the parser in a unknown state

// Request building errors: cause the Validation Filter to make a transaction fail and terminate 
const TInt KErrHttpReqBuildErrorBase = KHttpErrorBase - 130;

const TInt KErrHttpRequestHasBody					= KErrHttpReqBuildErrorBase;	///< A body is provided with a method that doesn't allow bodys to be transmitted
const TInt KErrHttpRequestBodyMissing				= KErrHttpReqBuildErrorBase - 1;///< A body is missing from a method that requires it			
const TInt KErrHttpTraceReqWithoutMaxForwardHeader	= KErrHttpReqBuildErrorBase - 2;///< should contain The Max-Forward header
const TInt KErrHttpPostReqBodyWithoutSizeOnHTTP10	= KErrHttpReqBuildErrorBase - 3;///< body must NOT be sent chunked if using HTTP/1.0
const TInt KErrHttpInvalidHeaderInRequest	  		= KErrHttpReqBuildErrorBase - 4;///< request contained a response header or a entity header but no body

// Missing but required header errors
const TInt KErrHttpMissingHeaderBase = KHttpErrorBase - 160;

const TInt KErrHttpEntityHeaderMissingContentType		= KErrHttpMissingHeaderBase;	///< A body was provided in the request but no Content-Type header was set
const TInt KErrHttpGeneralHeaderMissingHost				= KErrHttpMissingHeaderBase - 1;///< The request URI was relative, but no Host header was set to indicate a server to connect to

// Protocol handler errors
const TInt KErrHttpProtocolHandlerBase = KHttpErrorBase - 170;
// The request body needed to be rewound but the client but it doesn't support 
const TInt KErrHttpCantResetRequestBody				= KErrHttpProtocolHandlerBase;
const TInt KErrHttpProtTransactionNotInitialised	= KErrHttpProtocolHandlerBase -1;

// end of error codes - maximum error value is -7399 - must not be exceeded!



// Inline methods from HTTPStatus
//
inline TBool HTTPStatus::IsInformational(TInt aStatus)
	{
	return ((aStatus >= HTTPStatus::EContinue) && (aStatus < HTTPStatus::EOk));
	}
inline TBool HTTPStatus::IsSuccessful(TInt aStatus)
	{
	return ((aStatus >= HTTPStatus::EOk) && (aStatus < HTTPStatus::EMultipleChoices));
	}
inline TBool HTTPStatus::IsRedirection(TInt aStatus)
	{
	return ((aStatus >= HTTPStatus::EMultipleChoices) && (aStatus < HTTPStatus::EBadRequest));
	}
inline TBool HTTPStatus::IsClientError(TInt aStatus)
	{
	return ((aStatus >= HTTPStatus::EBadRequest) && (aStatus < HTTPStatus::EInternalServerError));
	}
inline TBool HTTPStatus::IsServerError(TInt aStatus)
	{
	return (aStatus >= HTTPStatus::EInternalServerError);
	}



#endif // __HTTPERR_H__
