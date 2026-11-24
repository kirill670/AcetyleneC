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
TEComResolverParams

Used to pass values to a Resolver to aid in the filtering of Interface 
Implementation plugins.

These values are considered match characteristics used during resolution of
these Interface Implementation.

@since 7.0

@warning This structure DOES NOT own the instance pointer variables, 
and so WILL NOT delete them.

@internalComponent
*/
//##ModelId=3A71B08F031E
class TEComResolverParams
	{
public:
	//##ModelId=3B56A49802A3
	inline TEComResolverParams();
	
	//##ModelId=3A71B08F03AA
	inline const TDesC8& DataType() const;
	//##ModelId=3A71B08F03A0
	inline void SetDataType(const TDesC8& aDataType);
	
	inline TBool IsGenericMatch() const;
	inline void SetGenericMatch(TBool aGenericMatch);

	// Deprecated
	//##ModelId=3A71B08F0370
	inline TBool IsWildcardMatch() const;
	//##ModelId=3A71B08F036E
	inline void SetWildcardMatch(TBool aWildcardMatch);

private:
	/** The Interface Implementation plugin 'datatype' match descriptor. */
	//##ModelId=3A71BF5A00CA
	TPtrC8 iDataType;
	/** The flag to show if generic matching is enabled */
	TBool iGenericMatch;
	};


#include <Ecom/EComResolverParams.inl>

#endif	// __ECOMRESOLVERPARAMS_H__
