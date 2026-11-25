//
// EComResolverParams.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file EComResolverParams.h
	Comments : Definition of the TEComResolverParams class.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 
#ifndef __ECOMRESOLVERPARAMS_H__
#define __ECOMRESOLVERPARAMS_H__

#include <e32base.h>

// ____________________________________________________________________________________
/**
	@class TEComResolverParams

	A simple class to hold the Interface Implementation match characteristics, to be used
	during Interface Implementation resolution. 
	i.e. The data descriptor of the Interface Implementation and a flag indicating if 
	wildcard matching should be used.

	Wildcard characters are ‘*’ and ‘?’, where ‘*’ matches zero or more consecutive
	occurrences of any character and ‘?’ matches a single occurrence of any character.
	Wildcards are only applicable to the Interface Implementation's reported string.
	The match string is ALWAYS a literal.

	@since 7.0
	@dependencies TPtrC8, TDesC8, TBool

	@warning This structure DOES NOT own the instance pointer variables, 
	and so WILL NOT delete them.
 */
//##ModelId=3A71B08F031E
class TEComResolverParams
	{
public:
/**
	@fn				inline TEComResolverParams()
	Intended Usage	:	Default c'tor
	@since			7.0
 */
	//##ModelId=3B56A49802A3
	inline TEComResolverParams();

/**
	@fn				DataType() const
	Intended Usage	:	Provide access to the Interface Implementation 'data string' match descriptor.
	@since			7.0
	@return			The data type string match descriptor
	@pre 			The object is constructed
 */
	//##ModelId=3A71B08F03AA
	inline const TDesC8& DataType() const;

/**
	@fn				SetDataType(const TDesC8& aDataType)
	Intended Usage	:	Set the Interface Implementation 'data string' match descriptor.
	@since			7.0
	@param			aDataType The data type string to be stored
	@pre 			Object is constructed
	@post			iDataType equals aDataType.
 */
	//##ModelId=3A71B08F03A0
	inline void SetDataType(const TDesC8& aDataType);

/**
	@fn				IsWildcardMatch() const
	Intended Usage	:	Check if 'wildcard' matching is allowed.
	@since			7.0
	@return			ETrue if wildcard matching is allowed, EFalse otherwise
	@pre 			The object is constructed
 */
	//##ModelId=3A71B08F0370
	inline TBool IsWildcardMatch() const;

/**
	@fn				SetWildcardMatch(TBool aWildcardMatch)
	Intended Usage	:	Set/Clear the 'wildcard' match flag
	@since			7.0
	@param			aWildcardMatch The value to set the wildcard match flag to.
	@pre 			The object is constructed
	@post			iWildcardMatch equals aWildcardMatch.
 */
	//##ModelId=3A71B08F036E
	inline void SetWildcardMatch(TBool aWildcardMatch);

private:
/** The Interface Implementation 'data string' match descriptor. */
	//##ModelId=3A71BF5A00CA
	TPtrC8 iDataType;
/** The flag to show if 'wildcard' matching is enabled */
	//##ModelId=3A815C420177
	TBool iWildcardMatch;
	};

#include <Ecom/EComResolverParams.inl>

#endif	// __ECOMRESOLVERPARAMS_H__
