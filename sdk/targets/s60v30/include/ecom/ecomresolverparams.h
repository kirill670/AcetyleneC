// EComResolverParams.h
// Copyright © 1997-2005 Symbian Ltd. All rights reserved.
//

/** 
Comments : Definition of the TEComResolverParams class.
 */ 
#ifndef __ECOMRESOLVERPARAMS_H__
#define __ECOMRESOLVERPARAMS_H__

#include <e32base.h>

/**
Used to pass values to a Resolver to aid in the filtering of Interface 
Implementation plugins.
These values are considered match characteristics used during resolution of
these Interface Implementation.
This structure DOES NOT own the instance pointer variables, 
and so WILL NOT delete them.

@publishedAll
@released
*/

class TEComResolverParams
	{
public:
	
	inline TEComResolverParams();
	
	
	inline const TDesC8& DataType() const;
	
	
	inline void SetDataType(const TDesC8& aDataType);
	
	inline TBool IsGenericMatch() const;
	inline void SetGenericMatch(TBool aGenericMatch);
	
	
	inline TBool IsWildcardMatch() const;
	
	
	inline void SetWildcardMatch(TBool aWildcardMatch);

private:
	/** The Interface Implementation plugin 'datatype' match descriptor.*/
	
	TPtrC8 iDataType;
	
	/** The flag to show if generic matching is enabled */
	TBool iGenericMatch;
	};


#include <Ecom/EComResolverParams.inl>

#endif	// __ECOMRESOLVERPARAMS_H__
