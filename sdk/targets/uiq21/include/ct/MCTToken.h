// Copyright (c) Symbian 2001

#ifndef __MCTTOKEN_H__
#define __MCTTOKEN_H__

#include <ct/tcttokenobjecthandle.h>
#include <ct/mcttokenobject.h>
#include <ct/tcttokenhandle.h>

class MCTTokenInterface;

/**@ingroup ct */
/**@{ */

/** The base class for a token. Token types must implement this class.
	It is created from a MCTTokenType using MCTTokenType::OpenToken.
	A token represents 1 instance of a particular kind of
	cryptographic module; for instance on a device with 2 WIMs, each
	WIM is a token. The token contains several interfaces,
	representing particular kinds of functions supported by the token
	(e.g. certificate management, key management etc)
*/
class MCTToken
	{
 public:
	///@name Functions for opening an interface. The base class implements the reference counting then calls the corresponding pure virtual Do... methods
	///@{
	/** Returns an interface, or NULL if it isn't supported by this
		token. Asynchronous.
		@param aRequiredInterface The UID of the interface that should be
		returned. 
		@param aReturnedInterface This will be set to a pointer to the
		returned interface on success. 
		@param aStatus Async. request status
	*/
	IMPORT_C void GetInterface(TUid aRequiredInterface,
							  MCTTokenInterface*& aReturnedInterface, 
							  TRequestStatus& aStatus);
	/** Cancel a GetInterface operation */
	IMPORT_C void CancelGetInterface();
	///@}

	/** Release. The token implements reference counting, with one count
		for itself and one for every opened interface. Once the count
		reaches 0, it releases its count with the token type.
	*/
	IMPORT_C void Release();

	/// @name Notification of token removal. The base class assumes the token is not removable, and so does nothing. Removable tokens must implement these functions.
	///@{
	/** Notifies the client when the token has been removed. 
		*/
	IMPORT_C virtual void NotifyOnRemoval(TRequestStatus& aStatus);
	/** Cancels NotifyOnRemoval */
	IMPORT_C virtual void CancelNotify();
	///@}

	/** Returns the associated token type.*/
	virtual MCTTokenType& TokenType() = 0;

	/** Returns a label for the token. This should be the same as the descriptor
		returned by CCTTokenType::List */
	virtual const TDesC& Label() = 0;

	/** Returns the token's handle. See the documentation of
		TCTTokenHandle for an explanation of the use of token handles
	 */
	virtual TCTTokenHandle Handle() = 0;

 protected:
 	 /** We need to make the destructor protected so that the users of the interface
	     will have to use the Release() function. */
	inline virtual ~MCTToken() = 0;

	///@name Helper functions for the reference counting
	///@{
	/** DoRelease is called when Release() has determined that the
		object is ready to be destroyed. It should destroy the
		token. It MUST NOT release the token type, as Release() will
		do that. The default implementation just does a 'delete this',
		but classes can override that if they want different
		behaviour.*/
	IMPORT_C virtual void DoRelease();
	/** Returns a reference to a variable to use as a reference count.
		The implementer should initialise this to 0. The value of the
		reference count should be treated as opaque by the
		implementer.
		*/
	virtual TInt& ReferenceCount() = 0;
	///@}

	///@name Implementation of GetInterface functionality */
	///@{
	/** @see GetInterface */
	virtual void DoGetInterface(TUid aRequiredInterface,
							  MCTTokenInterface*& aReturnedInterface, 
							  TRequestStatus& aStatus) = 0;
	/** @see CancelGetInterface */
	virtual TBool DoCancelGetInterface() = 0;
	///@}

 private:
	// Used by the token object to increment the reference count
	void ObjectCreated();
	// Needed to allow MCTTokenObject to increment the reference count
	// of the token
	friend class MCTTokenObject;
	};

inline MCTToken::~MCTToken()
	{
	}
///@}
#endif //__MCTTOKEN_H__
