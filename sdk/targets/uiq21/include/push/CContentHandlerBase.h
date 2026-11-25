// CContentHandlerBase.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
// 

/*
 * Comments: Defines the base class for all Push Content Handling plugins
 */ 

#ifndef __CCONTENTHANDLERBASE_H__
#define __CCONTENTHANDLERBASE_H__

// System includes
//
#include <e32base.h>
#include <msvstd.h>

// Local includes
//
#include "CPushHandlerBase.h"

// Forward declaration definitions here
class CPushMessage;
class CPluginKiller;
class MWapPushLog;

// Constants
//
const TUid KUidPushContentHandlerBase	= { 0x101F3E5E };

/**
 * CContentHandlerPluginBase forms an abstract base class for all the Content Handling plug-ins.
 * some generic functionality is provided to enable the construction of derived classes to be
 * simpler.
 */ 
//##ModelId=3B659DAC030D
class CContentHandlerBase : public CPushHandlerBase
	{
public:

/**
	@fn				NewL(const TDesC& aMatchData)
	Intended Usage	:	Static c'tor that uses ECom to instantiate a CContentHandlerBase
	derived class that matches the data in aMatchData.
	@since			6.0
	@param			aMatchData	A descriptor with the matching data
	@return			A pointer to the created CContentHandlerBase derived object that can
	matches the matching data.
 */
	inline static CContentHandlerBase* NewL(const TDesC& aMatchData);

/**
	@fn				~CContentHandlerBase()
	Intended Usage	:	D'tor. Uses ECom to ensure that the DLL containing the 
	used interface implementation is unloaded at the appropriate time.
	@since			6.0
 */
	inline virtual ~CContentHandlerBase();

	inline void SetParent(TMsvId aParentID);

protected:	// Methods

	inline CContentHandlerBase();

	inline void Complete(TInt aError);

	inline void IdleComplete();

protected:

	TMsvId				iParentID;

	TInt				iState; //state machine

	TBool				iAcknowledge;

	CPushMessage*		iMessage;

	};

#include "CContentHandlerBase.inl"

#endif    // __CCONTENTHANDLERBASE_H__
