// CPushHandlerBase.inl
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
// 

// Local includes
//
#include "CPushHandlerBase.h"

// System includes
//
#include <ECom.h>

inline CPushHandlerBase::CPushHandlerBase()
: CActive(EPriorityStandard)
	{
	}

inline CPushHandlerBase::~CPushHandlerBase()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}

inline CPushHandlerBase* CPushHandlerBase::NewL(const TDesC& aMatchData)
	{
	return NewL(aMatchData, KUidPushHandlerBase);
	}

inline CPushHandlerBase* CPushHandlerBase::NewL(const TDesC& aMatchData, const TUid& aInterfaceUid)
	{
	// Convert match data to 8-bits
	HBufC8* buf = HBufC8::NewLC(aMatchData.Length());
	TPtr8 data = buf->Des();
	data.Copy(aMatchData);
	data.LowerCase();	// change to lower case

	// Set resolving parameters
	TEComResolverParams resolverParams;
	resolverParams.SetDataType(data);
	resolverParams.SetWildcardMatch(ETrue);

	// Get the instantiation
	CPushHandlerBase* pushHandler = REINTERPRET_CAST(CPushHandlerBase*,
									REComSession::CreateImplementationL(aInterfaceUid,
																		_FOFF(CPushHandlerBase, iDtor_ID_Key),
																		resolverParams));
	CleanupStack::PopAndDestroy(buf);
	return pushHandler;
	}

inline void CPushHandlerBase::SetLogger(MWapPushLog& aLog)
	{
	iLog = &aLog;
	}

inline void CPushHandlerBase::SetKiller(CPluginKiller& aPluginKiller)
	{
	iPluginKiller = &aPluginKiller;
	}

inline void CPushHandlerBase::SetManager(MConnManObserver& aManager)
	{
	iManager = &aManager;
	}

inline void CPushHandlerBase::SetConfirmationStatus(TRequestStatus& aStatus)
	{
	aStatus=KRequestPending;
	iConfirmStatus = &aStatus;
	}

inline void CPushHandlerBase::SignalConfirmationStatus(TInt aErr)
	{
	User::RequestComplete(iConfirmStatus, aErr);
	}
