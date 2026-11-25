// APFDEF.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __APFDEF_H__
#define __APFDEF_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

// generic file extensions etc.

/**
@internalTechnology
*/
_LIT(KAppFileExtension,".app");

/**
@internalTechnology
*/
_LIT(KAppInfoFileExtension,".aif");

/**
@internalTechnology
*/
_LIT(KIniFileExtension,".ini");

/**
@internalComponent
*/
_LIT(KSystemControlFileExtension,".ctl");

/**
@internalComponent
*/
_LIT(KApaCaptionFileSuffix,"_Caption");

/**
@internalTechnology
*/
_LIT(KAppResourceFileExtension,".rsc");


/**
@internalComponent
*/
const TInt KApparcExtraLengthOfCaptionFileName=15;

//
// paths etc.

class Apfile
/**
@publishedAll
@deprecated
*/
	{
public:
	IMPORT_C static TPtrC TempPath();
	};


#endif