//
// EComResolverParams.inl
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
@file EComResolverParams.inl
Comments : Implementation of the TEComResolverParams class.
	
@warning This code contains Rose2000 generated ModelId comments
		 used in round trip engineering. Please do not remove.
 */ 

// ____________________________________________________________________________________
// Provide the inline implementation of TEComResolverParams 
// TEComResolverParams allows the user to define the characteristics of the plugin to be found
//
/**
Intended Usage	:	Default c'tor
@since			7.0
*/
TEComResolverParams::TEComResolverParams() :
iDataType(NULL,0),
iWildcardMatch(EFalse)
	{
	// Do nothing here
	}


/**
Intended Usage	:	Provide access to the Interface Implementation 'data string' match descriptor.
@since			7.0
@return			The data type string match descriptor
@pre 			The object is constructed
*/
//##ModelId=3A71B08F03AA
const TDesC8& TEComResolverParams::DataType() const
	{
	return iDataType;
	}


/**
Intended Usage	:	Set the Interface Implementation 'data string' match descriptor.
@since			7.0
@param			aDataType The data type string to be stored
@pre 			Object is constructed
@post			iDataType equals aDataType.
*/
//##ModelId=3A71B08F03A0
void TEComResolverParams::SetDataType(const TDesC8& aDataType)
	{
	iDataType.Set(aDataType);
	}


/**
Intended Usage	:	Check if 'wildcard' matching is allowed.
@since			7.0
@return			ETrue if wildcard matching is allowed, EFalse otherwise
@pre 			The object is constructed
*/
//##ModelId=3A71B08F0370
TBool TEComResolverParams::IsWildcardMatch() const
	{
	return iWildcardMatch;
	}


/**
Intended Usage	:	Set/Clear the 'wildcard' match flag
@since			7.0
@param			aWildcardMatch The value to set the wildcard match flag to.
@pre 			The object is constructed
@post			iWildcardMatch equals aWildcardMatch.
*/
//##ModelId=3A71B08F036E
void TEComResolverParams::SetWildcardMatch(TBool aWildcardMatch)
	{
	iWildcardMatch=aWildcardMatch;
	}

