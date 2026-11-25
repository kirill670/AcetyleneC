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
TEComResolverParams::TEComResolverParams() :
iDataType(NULL,0),
iWildcardMatch(EFalse)
	{
	// Do nothing here
	}

//##ModelId=3A71B08F03AA
const TDesC8& TEComResolverParams::DataType() const
	{
	return iDataType;
	}

//##ModelId=3A71B08F03A0
void TEComResolverParams::SetDataType(const TDesC8& aDataType)
	{
	iDataType.Set(aDataType);
	}

//##ModelId=3A71B08F0370
TBool TEComResolverParams::IsWildcardMatch() const
	{
	return iWildcardMatch;
	}

//##ModelId=3A71B08F036E
void TEComResolverParams::SetWildcardMatch(TBool aWildcardMatch)
	{
	iWildcardMatch=aWildcardMatch;
	}

