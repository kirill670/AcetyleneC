//
// SmlEngineDefines.h
// 
//


#ifndef __SMLENGINEDEFINES_H__
#define __SMLENGINEDEFINES_H__

// SyncML Authentication types
enum TSmlEncodingTypes
	{
		ESmlEncodingTypeUndefined = 0, 
		ESmlEncodingTypeWBXML, 
		ESmlEncodingTypeXML
	};


// SyncML Authentication types
enum TSmlAuthenticationTypes
	{
		ESmlNone,
		ESmlBasic,
		ESmlMd5,
	};

// SyncML Status Codes
enum TSmlSyncMLStatusCode
	{
		ESmlStatusInProgress = 101,
		ESmlStatusOK = 200,
		ESmlStatusItemAdded = 201,
		ESmlStatusAcceptedForProcessing = 202,
		ESmlStatusNonAuthoriveResponse = 203,
		ESmlStatusNoContent = 204,
		ESmlStatusResetContent = 205,
		ESmlStatusPartialContent = 206,
		ESmlStatusConflictResolvedWithMerge = 207,
		ESmlStatusConflictResolvedWithClientsCommand = 208,
		ESmlStatusConflictResolvedWithDuplicate = 209,
		ESmlStatusDeleteWithoutArchive = 210,
		ESmlStatusItemIsNotDeleted = 211,
		ESmlStatusAuthenticationAccepted = 212,
		ESmlStatusMultipleChoices = 300,
		ESmlStatusMovedPermanently = 301,
		ESmlStatusMovedTemporarily = 302,
		ESmlStatusSeeOtherURI = 303,
		ESmlStatusNotModified = 304,
		ESmlStatusUseProxy = 305,
		ESmlStatusBadRequest = 400,
		ESmlStatusUnauthorized = 401,
		ESmlStatusPaymentRequired = 402,
		ESmlStatusForbidden = 403,
		ESmlStatusNotFound = 404,
		ESmlStatusCommandNotAllowed = 405,
		ESmlStatusOptFeatureNotSupported = 406,
		ESmlStatusClientAuthenticationRequired = 407,
		ESmlStatusRequestTimeout = 408,
		ESmlStatusConflict = 409,
		ESmlStatusGone = 410,
		ESmlStatusSizeRequired = 411,
		ESmlStatusIncompleteCommand = 412,
		ESmlStatusEntityTooLarge = 413,
		ESmlStatusURITooLong = 414,
		ESmlStatusUnsupportedMediaTypeOrFormat = 415,
		ESmlStatusRequestedSizeTooBig = 416,
		ESmlStatusRetryLater = 417,
		ESmlStatusAlreadyExists = 418,
		ESmlStatusConflictResolvedWithServerData = 419,
		ESmlStatusDeviceFull = 420,
		ESmlStatusUnknownSearchGrammar = 421,
		ESmlStatusBadCGIScript = 422,
		ESmlStatusSoftDeleteUpdateConflict = 423,
		ESmlStatusCommandFailed = 500,
		ESmlStatusCommandNotImplemented = 501,
		ESmlStatusBadGateway = 502,
		ESmlStatusServiceUnavailable = 503,
		ESmlStatusGatewayTimeout = 504,
		ESmlStatusVersionNotSupported = 505,
		ESmlStatusProcessingError = 506,
		ESmlStatusAtomicFailed = 507,
		ESmlStatusRefreshRequired = 508,
		ESmlStatusServerAuthenticationRequired = 509,
		ESmlStatusDataStoreFailure = 510,
		ESmlStatusServerFailure = 511,
		ESmlStatusSynchronisationFailed = 512,
		ESmlStatusProtocolVersionNotSupported = 513
	};

enum TSmlAlertCodes 
	{
		ESmlAlertTwoWaySync				= 200,
		ESmlAlertSlowSync				= 201,
		ESmlAlertOneWaySyncFromClient	= 202,
		ESmlAlertRefreshFromClient		= 203,
		ESmlAlertOneWaySyncFromServer	= 204,
		ESmlAlertRefreshFromServer		= 205,
		// special alerts
		ESmlAlertResultAlert			= 221,
		ESmlAlertNextMessage			= 222,
	};


#endif //__SMLDEFINES_H__