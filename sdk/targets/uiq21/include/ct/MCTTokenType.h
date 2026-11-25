// Copyright (c) Symbian 2001


#ifndef __MCTTOKENTYPE_H__
#define __MCTTOKENTYPE_H__

#include <f32file.h>
#include <ct/RCPointerArray.h>

class CCTTokenTypeInfo;
class MCTToken;
class TCTTokenHandle;

/**@ingroup ct */
/**@{ */

/** A token type. This abstract class is instantiated via ECom for a
	particular token type. It allows a list of available tokens of
	that type to be obtained, and particular tokens to be opened. All
	implementation classes are in fact a subclass of CCTTokenType;
	refer to its documentation for implementation details. Client
	access is entireley through this M class. The difference betweeen
	a token type and a token is best explained with an example; if a
	device has 2 identical WIM slots, the code to handle WIMs is 1
	token type, which will have 2 tokens, for the 2 WIMs. */
class MCTTokenType
	{
 public:
	/// @name Static constructor functions that use ECom to load the actual implementation.
	///@{
	/** Creates a MCTTokenType given it's CCTTokenTypeInfo */
	inline static MCTTokenType* NewL(const CCTTokenTypeInfo& aInfo, RFs aFs);
	/** Creates a MCTTokenType given the UID of the token type. */
	inline static MCTTokenType* NewL(TUid aUID, RFs aFs);
	///@}

	///@{
	/** List all the tokens of this type. This function is asynchronous.
		Tokens are totaly defined by name, so instead of a CCTTokenInfo class,
		this just returns a list of HBufCs.
		@param aTokens The returned tokens
		@param aStatus Asyncronous return status.
	 */
	virtual void List(RCPointerArray<HBufC>& aTokens, 
					  TRequestStatus& aStatus) = 0;
	/** Cancel a list operation */
	virtual void CancelList() = 0;
	///@}

	///@{
	/** Opens a specified token.
		@param aTokenInfo The info of the required token
		@param aToken The returned token
		@param aStatus Asynchronous return status.
	 */
	virtual void OpenToken(const TDesC& aTokenInfo, MCTToken*& aToken, 
						   TRequestStatus& aStatus) = 0;
	/** Opens a specified token.
		@param aTokenHandle The handle of the required token
		@param aToken The returned token
		@param aStatus Asynchronous return status.
	 */
	virtual void OpenToken(TCTTokenHandle aHandle, MCTToken*& aToken, 
						   TRequestStatus& aStatus) = 0;
	/** Cancel an OpenToken operation */
	virtual void CancelOpenToken() = 0;
	///@}

	/** Release. Call when you've finished with the object The API
        doesn't allow the destructor to be directly called as this
        object could remain in existence for longer to hold onto the
        ECom handle on the DLL; for instance it may not be deleted
        until all tokens and interfaces have also been
        released. */
	virtual void Release() = 0;

	/** Returns the UID of the token type. This function is implemented by
		CCTTokenType, so token type implementers need not implement it. */
	virtual TUid Type() const = 0;
	/** Returns the label of the token type. This function is implemented by
		CCTTokenType, so token type implementers need not implement it. */
	virtual const TDesC& Label() const = 0;
	};


// Inline functions are defined at the end of CCTTokenType.h
///@}
#endif //__MCTTOKENTYPE_H__
