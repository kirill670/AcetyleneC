//	MsvSendErrorAction.h
//
//	Copyright (c) Symbian Software Ltd 1999-2004.  All rights reserved. 
//

#ifndef __MSVSENDERRORACTION_H__
#define __MSVSENDERRORACTION_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__
 
#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__


/////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
/////////////////////////////////////////////////////////////////////////////

#include "schsend.hrh"
#include <barsread.h>
#include <msvstore.h>

/////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __HIDE_MESSAGING_API_V1__
const TUid KUidMsvFileSendErrorActions		= {0x10005711};	//Used by CMsvSendErrorActions

const TInt16 KMsvSendErrorActionVersion		= 1;
const TInt16 KMsvSendErrorActionsVersion	= 1;
#endif

/////////////////////////////////////////////////////////////////////////////
//
//	TMsvSendErrorAction Declaration
//
/////////////////////////////////////////////////////////////////////////////

/**
Encapsulates the action to take for a particular error. 

An error may occur when the Server MTM is attempting to send a message or 
messages. If the Server MTM supports scheduling, then, depending on the error 
or conditions, the Server MTM may want to re-schedule the message on the Task 
Scheduler to send at a later time. CMsvScheduleSend::ReScheduleL() 
(in combination with CMsvSendErrorActions) uses the TMsvSendErrorAction 
to determine whether to re-schedule the message. 

@publishedAll
@released
*/

class TMsvSendErrorAction
	{
public:
	IMPORT_C TMsvSendErrorAction();

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void InternalizeL(RReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
#endif	// __HIDE_MESSAGING_API_V1__
	IMPORT_C void Reset();

	IMPORT_C void SetMaxRetries(const TInt16 aMaxRetries);
	IMPORT_C TInt16 MaxRetries() const;

	/** The error. */
	TInt					iError;

	/** The action to take if this error occurs. */
	TMsvSendAction			iAction;

	/** The number of attempts to make at sending a message if this error occurs. 
	
	If iRetries equals ESendRetriesInfinite, then sending will be attempted until 
	successful (or the user intervenes). This member is ignored if iAction equals 
	ESendActionFail. */
	TMsvSendRetries			iRetries;

	/** Retry behaviour.
	
	This member is used by CMsvSendErrorActions to determine when to resend the 
	message. This member is ignored if iAction equals ESendActionFail. */
	TMsvSendRetrySpacing	iRetrySpacing;

private:
	TInt16	iMaxRetries;
#ifndef __REMOVE_MESSAGING_API_V1__	
	TInt16	iVersion;
#endif	// __REMOVE_MESSAGING_API_V1__
	};


/////////////////////////////////////////////////////////////////////////////
//
// CMsvSendErrorActions
//
/////////////////////////////////////////////////////////////////////////////

/**
This class determines what action to take if an error occurs while the Server 
MTM is sending a message (or messages).

It encapsulates an array of TMsvSendErrorAction objects, which it uses to 
determine the action to take for a particular error. If the error is not 
found in the array, then CMsvSendErrorActions uses its default 
TMsvSendErrorAction object. 

@publishedAll
@released
*/

class CMsvSendErrorActions : public CBase
	{
public:
	IMPORT_C static CMsvSendErrorActions* NewL();
#ifdef __MESSAGING_API_V2__		
	IMPORT_C static CMsvSendErrorActions* NewLC();	
#endif	// __MESSAGING_API_V2__
	IMPORT_C ~CMsvSendErrorActions();

	IMPORT_C void AddSendErrorActionL(const TMsvSendErrorAction& aErrorAction);
	IMPORT_C TInt RemoveSendErrorAction(const TInt aError);
	IMPORT_C TInt GetSendErrorAction(const TInt aError, TMsvSendErrorAction& aErrorAction) const;

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);
#endif	// __HIDE_MESSAGING_API_V1__
	IMPORT_C void RestoreFromResourceL(TResourceReader& aReader);

	IMPORT_C void SetErrorsL(const CArrayFixFlat<TMsvSendErrorAction>& aErrors);
	IMPORT_C const CArrayFixFlat<TMsvSendErrorAction>& Errors() const;

	IMPORT_C const TMsvSendErrorAction& Default() const;
	IMPORT_C void SetDefault(const TMsvSendErrorAction& aAction);

private:
	CMsvSendErrorActions();
	void ConstructL();
	void RestoreErrorActionL(TResourceReader& aReader, TInt aActionCount, const TBool aDefault);

#ifndef __HIDE_MESSAGING_API_V1__		
	void InternalizeL(RReadStream& aReadStream);
	void ExternalizeL(RWriteStream& aWriteStream) const;
#endif	// __HIDE_MESSAGING_API_V1__

	TInt Find(const TInt aError, TInt& aIndex) const;

#ifndef __REMOVE_MESSAGING_API_V1__
	TInt16 iVersion;
#endif	// __REMOVE_MESSAGING_API_V1__
	
	CArrayFixFlat<TMsvSendErrorAction>* iErrors;
	TMsvSendErrorAction iDefault;
	};

#endif	// __MSVSENDERRORACTION_H__
