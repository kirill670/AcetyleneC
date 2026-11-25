// CPushHandlerBase.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
// 

/** @file CPushHandlerBase.h
 * This file contains the declaration of the CPushHandlerBase which is the abstract class for all Push plugins.
 */

#ifndef __CPUSHHANDLERBASE_H__
#define __CPUSHHANDLERBASE_H__

// System includes
#include <e32base.h>

// Forward class declarations
class CPushMessage;
class CPluginKiller;
class MWapPushLog;
class MConnManObserver;

/**
 * Define the UID for a App Handling plugin which can be returned by a plugin manager
 */
const TUid KUidPushHandlerBase = { 0x101F3E5A };

/**
 * CPushHandlerBase forms an abstract base class for all Push plugins.
 */ 
//##ModelId=3B659E6D00F8
class CPushHandlerBase : public CActive
	{
public:	// Methods

/**
	@fn				NewL(const TDesC& aMatchData)
	Intended Usage	:	Static c'tor that uses ECom to instantiate a CPushHandlerBase
	derived class that matches the data in aMatchData.
	@since			6.0
	@param			aMatchData	A descriptor with the matching data
	@return			A pointer to the created CPushHandlerBase derived object that can
	matches the matching data.
 */
	inline static CPushHandlerBase* NewL(const TDesC& aMatchData);

/**
	@fn				NewL(const TDesC& aMatchData, const TUid& aInterfaceUid)
	Intended Usage	:	Static c'tor that uses ECom to instantiate a CPushHandlerBase
	derived class that matches the data in aMatchData. This should be called by derived
	interface classes,. The argument aInterfaceUid spedifies the  derived interface 
	required. But has been made public as fitting in with only system.
	@since			6.0
	@param			aMatchData		A descriptor with the matching data
	@param			aInterfaceUid	The UID of the desired interface
	@return			A pointer to the created CPushHandlerBase derived object that can 
	implements the specified interface, also derived from CPushHandlerBase, and that 
	matches the matching data.
 */
	inline static CPushHandlerBase* NewL(const TDesC& aMatchData, const TUid& aInterfaceUid);

/**
	@fn				~CPushHandlerBase()
	Intended Usage	:	D'tor. Uses ECom to ensure that the DLL containing the 
	used interface implementation is unloaded at the appropriate time.
	@since			6.0
 */
	inline virtual ~CPushHandlerBase();

	//Async. Functions
	virtual void HandleMessageL(CPushMessage* aPushMsg,TRequestStatus& aStatus) =0;

	virtual void CancelHandleMessage() =0;

	//Sync. Functions
	virtual void HandleMessageL(CPushMessage* aPushMsg) =0;

	inline void SetLogger(MWapPushLog& aLog);

	inline void SetKiller(CPluginKiller& aPluginKiller);

	inline void SetManager(MConnManObserver& aManager);

protected:	// Methods

	//##ModelId=3B659E6D0148
	CPushHandlerBase();

	void SetConfirmationStatus(TRequestStatus& aStatus);

	void SignalConfirmationStatus(TInt aErr);

protected:	// Attributes

	CPluginKiller*		iPluginKiller;

	MWapPushLog*		iLog;

	MConnManObserver*	iManager;

	TRequestStatus*		iConfirmStatus;

private:	// Attributes

	/** A unique UID used in interface destruction 
	 */
	TUid	iDtor_ID_Key;

private:	// BC-proofing

/**
	@fn				CPushHandlerBase_Reserved1() =0
	Intended Usage	:	Reserved for future expansion.
	@since			6.0
 */
	virtual void CPushHandlerBase_Reserved1() =0;		

/**
	@fn				CPushHandlerBase_Reserved2() =0
	Intended Usage	:	Reserved for future expansion.
	@since			6.0
 */
	virtual void CPushHandlerBase_Reserved2() =0;		

	/** Reserved for future expansion
	 */
	TAny*		iCPushHandlerBase_Reserved;

	};

#include "CPushHandlerBase.inl"

#endif    // __PUSHBASEHAND_H__
