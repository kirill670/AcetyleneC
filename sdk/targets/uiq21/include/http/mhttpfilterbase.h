// MHTTPFilterBase.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file MHTTPFilterBase.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef	__MHTTPFILTERBASE_H__
#define	__MHTTPFILTERBASE_H__ 

// System includes
#include <e32std.h>

// Forward declarations
class RHTTPTransaction;
class THTTPEvent;
class THTTPSessionEvent;

/** 
	@public
	@class			MHTTPFilterBase
	@since			7.0
	A HTTP Filter. This is the base class for normal filters
	(MHTTPFilter) which adds an unload function, and
	MHTTPTransactionCallback, which doesn't add an unload function.  
 */

//##ModelId=3A914DF9034F
class MHTTPFilterBase
	{
public:
	/** Called when the filter's registration conditions are satisfied for events that
		occur on a transaction.
		Note that this function is not allowed to leave if called with
		certain events. @see THTTPEvent
		@param aTransaction The transaction that the event has occurred on.
		@param aEvent The event that has occurred.
		@exception Any Leaves must be handled by the appropriate MHFRunError.
	*/
	//##ModelId=3A914DF9035D
	IMPORT_C virtual void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent);

	/** Called when the filters registration conditions are satisfied for events that occur
		on the session.
		@ param aEvent The session event that has occured.
		@ exception Any leaves must be handled by the appropriate MHFRunError.
	*/
	//##ModelId=3C4C37D401C1
	IMPORT_C virtual void MHFSessionRunL(const THTTPSessionEvent& aEvent);

	/** Called when RunL leaves from a transaction event. This works in the same
		way as CActve::RunError; return KErrNone if you have handled the error.
		If you don't completely handle the error, a panic will occur.
		@param aError The leave code that RunL left with.
		@param aTransaction The transaction that was being processed.
		@param aEvent The Event that was being processed.
		@return KErrNone if the error has been cancelled or the code
		of the continuing error otherwise.
	*/
	//##ModelId=3A914DF90359
	IMPORT_C virtual TInt MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent& aEvent);

	/** Called when MHFRunL leaves from a session event. This works in the same
		way as CActve::RunError
		If you don't completely handle the error, a panic will occur.
		@param aError The leave code that RunL left with.
		@param aEvent The Event that was being processed.
		@return KErrNone if the error has been cancelled or the code
		of the continuing error otherwise.	
	*/
	//##ModelId=3C4C37D302C4
	IMPORT_C virtual TInt MHFSessionRunError(TInt aError, const THTTPSessionEvent& aEvent);
 	};


#endif //	 __MHTTPFILTERBASE_H__
