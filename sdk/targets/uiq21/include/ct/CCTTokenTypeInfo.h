// Copyright (c) Symbian Ltd 2001

#ifndef __CCTTOKENTYPEINFO_H__
#define __CCTTOKENTYPEINFO_H__

#include <ct/TCTAllTokenTypes.h>
#include <ct/TCTTokenTypeAttribute.h>
#include <ct/RCPointerArray.h>
class CImplementationInformation;

/**@ingroup ct */
/**@{ */


/** Information about a token type. A list of CCTTokenTypeInfo objects
	can be obtained using the List function. Each CCTTokenTypeInfo has
	a list of interfaces it supports, a list of TCTTokenTypeAttributes
	associated with it, and a label. Based on this the client (or the
	user via a UI) can chose the required token type and load it via
	CCTTokenType::NewL */
class CCTTokenTypeInfo : public CBase
	{
 public:
	///@name Listing available Token Types
	///@{
	/** List all the CCTTokenTypeInfo objects that match the filter
		expression. This is the only way of creating CCTTokenTypeInfo
		objects.
		@param aTokenTypes An array to which the found token types will be
		appended. Ownership is transferred to the caller.
		@param aFilter An object that is used to filter tokens, by
		being offered each token in turn and declining the ones that aren't
		required */
	IMPORT_C static void ListL(RCPointerArray<CCTTokenTypeInfo>& aTokenTypes,
							  const MCTTokenTypeFilter& aFilter);
	/** List all the CCTTokenTypeInfo objects that match the filter
		expression. This version does not take a filter, but returns all
		token types.
		@param aTokenTypes An array to which the found token types will be
		appended. Ownership is transferred to the caller.
	*/
	IMPORT_C static void ListL(RCPointerArray<CCTTokenTypeInfo>& aTokenTypes);
	///@}

	/** Destructor */
	~CCTTokenTypeInfo();

	/** Returns a list of all interfaces supported by this token type */
	IMPORT_C const RArray<TUid>& Interfaces() const;

	/** Returns a list of all attributes of this token type */
	IMPORT_C const RArray<TCTTokenTypeAttribute>& Attributes() const;

	/** Returns a human-readable name for the token type */
	IMPORT_C const TDesC& Label() const;

	/** Returns the UID of this token type. */
	IMPORT_C TUid Type() const;
 private:
	/** Constructor */
	CCTTokenTypeInfo(CImplementationInformation* aEcomImplementationInfo);

 private:
	CImplementationInformation* iEcomImplementationInfo;
	RArray<TUid> iInterfaces;
	RArray<TCTTokenTypeAttribute> iAttributes;
	};

///@}
#endif // __CCTTOKENTYPEINFO_H__
