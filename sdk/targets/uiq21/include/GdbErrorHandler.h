// GdbErrorHandler.h
//
// Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.
//
// Declarations used to deal with errors
//

#ifndef __GDBERRORHANDLER_H__
#define __GDBERRORHANDLER_H__

class MGdbErrorHandler
//
// Interface used to report an error occuring while handling an
// incoming request.  Some errors are fatal (i.e. user action
// requested) and other are just warnings.
// 
	{

public:
	enum TError
		{
		ENone,
		EByteReceptionError,
		EMsgReceptionError,
		EMsgReceptionGarbage,	
		EMsgReceptionBadChecksum,	
		EMsgEmissionBadAck,
		EUnmarshallingUnknownCmd,
		EUnmarshallingError,	
		EMarshallingReplyFailed,
		ECmdHandlingUnknownFileType,
		ECmdHandlingSpawnFailed,
		ECmdHandlingAttachFailed,
		ECmdHandlingInitBrkptFailed,
		ECmdHandlingAppLoadingFailed,
		ECmdHandlingReadMemFailed,
		ECmdHandlingWriteMemFailed,
		ECmdHandlingSetBreakPointFailed,
		ECmdHandlingClearBreakPointFailed,
		ECmdHandlingSetRegisterFailed,
		ECmdHandlingGetRegisterFailed,
		ECmdHandlingSingleStepFailed,
		ECmdHandlingContinueFailed,
		ECmdHandlingKillFailed,
		ECmdHandlingUnexpectedCmd,
		};

public:
	virtual void HandleError(TError aError, TInt aEpocError) = 0;
	};

#endif // __GDBERRORHANDLER_H__
