//
// EComResolverParams.inl
// Copyright © 1997-2004 Symbian Ltd. All rights reserved.
//

/** 
@file EComResolverParams.inl
Comments : Implementation of the TEComResolverParams class.

@warning This code contains Rose2000 generated ModelId comments
		 used in round trip engineering. Please do not remove.
*/ 


// ____________________________________________________________________________________
// Provide the inline implementation of TEComResolverParams 
// TEComResolverParams allows the user to define the characteristics
// of the Interface Implementation plugin to be found.
//

/**
Default c'tor

@since			7.0
*/
TEComResolverParams::TEComResolverParams()
:	iDataType(NULL,0),
	iGenericMatch(EFalse)
	{
	// do nothing;
	}


/**
Provides read access to the Interface Implementation plugin 'datatype' match pattern.

@since			7.0
@return			The read only 'datatype' match pattern.
@pre 			The object is constructed
*/
//##ModelId=3A71B08F03AA
const TDesC8& TEComResolverParams::DataType() const
	{
	return iDataType;
	}


/**
Set the Interface Implementation plugin 'datatype' match pattern.

@since			7.0
@param			aDataType The 'datatype' match pattern to be stored.
@pre 			The object is constructed
@post			iDataType equals aDataType.
*/
//##ModelId=3A71B08F03A0
void TEComResolverParams::SetDataType(const TDesC8& aDataType)
	{
	iDataType.Set(aDataType);
	}

/**
Check if 'generic' matching is allowed.

@since			8.0
@return			ETrue if generic matching is allowed, EFalse otherwise.
@pre 			The object is constructed
*/
TBool TEComResolverParams::IsGenericMatch() const
	{
	return iGenericMatch;
	}

/**
Indicates that a 'generic' match is required.

Either allow Interface Implementation plugins that are specific (use no wildcards
in their registry file) or generic (use wildcards in their registry file).

In any case the user of a should NOT use wildcards in the datatype string that
is passed into this object.

Rationale
The client that sets up the resolver is expected to know what type of data
it is handling.

Use Case:
"I have this gif to convert, but I'd prefer only gif-specific plugins" or 
"I have this gif to convert, but I'm happy with some generic image conversion
plugin".

NOT:
"I have this image I want some plugin to convert, but I don't know the type
of the image".

@since			8.0
@param			aGenericMatch ETrue if a generic match is required, EFalse if not.
@pre 			The object is constructed
@post			iGenericMatch equals aGenericMatch.
*/
void TEComResolverParams::SetGenericMatch(TBool aGenericMatch)
	{
	iGenericMatch=aGenericMatch;
	}
	

/**
Deprecated

@see			IsGenericMatch
@since			7.0
@pre 			The object is constructed
*/
//##ModelId=3A71B08F0370
TBool TEComResolverParams::IsWildcardMatch() const
	{
	return iGenericMatch;
	}


/**
Deprecated

@see			SetGenericMatch
@since			7.0
@pre 			The object is constructed
@post			iGenericMatch equals aWildcardMatch.
*/
//##ModelId=3A71B08F036E
void TEComResolverParams::SetWildcardMatch(TBool aWildcardMatch)
	{
	iGenericMatch=aWildcardMatch;
	}




