// CContentHandlerBase.inl
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
// 

// Local includes
//
#include "CContentHandlerBase.h"
#include "PushLog.h"
#include "PushMessage.h"
#include "PluginKiller.h"

// System includes
//
#include <ECom.h>

inline CContentHandlerBase::CContentHandlerBase()
: CPushHandlerBase()
	{
	}

inline CContentHandlerBase::~CContentHandlerBase()
	{
	__LOG_PTR_DEBUG("CContentHandlerBase:: Destructor Called");
	Cancel();
	delete iMessage;
	}

inline CContentHandlerBase* CContentHandlerBase::NewL(const TDesC& aMatchData)
	{
	// Call base class interface CPushHandlerBase::NewL()
	return REINTERPRET_CAST(CContentHandlerBase*, 
							CPushHandlerBase::NewL(aMatchData, KUidPushContentHandlerBase));
	}

inline void CContentHandlerBase::SetParent(TMsvId aParentID)
	{
	iParentID = aParentID;
	}

/**
*	signal that finished and to kill off handler
*/
inline void CContentHandlerBase::Complete(TInt aError)
	{
	__LOG_PTR_DEBUG("CContentHandlerPluginBase:: Complete Called");
	if (iAcknowledge)
		SignalConfirmationStatus(aError);
	iPluginKiller->KillPushPlugin();
	}	

/**
 * Asynchronous request complete
 * Since we really didn't start an async event, make it look as though our
 * asynchronous request has been completed. 
 */	
inline void CContentHandlerBase::IdleComplete()
	{
	TRequestStatus* pS = &iStatus;
	User::RequestComplete(pS,KErrNone);
	SetActive();
	}
