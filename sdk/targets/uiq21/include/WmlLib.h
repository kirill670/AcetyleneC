//	WmlLib.h
//
//	Copyright (c) 2001 Symbian Ltd.  All rights reserved. 
//

#ifndef __WMLLIB_H__
#define __WMLLIB_H__

// System includes
//
#include <E32Base.h>
//#include <WapEngStd.h>

// Local includes
//
#include "XmlLib.h"

//	Forward class declarations
//
class TWmlParser;
class CWmlValidator;
class CLocalContext;

//##ModelId=3B66652003BB
class CWmlLibrary : public CXmlLibrary
	{
public:	// Methods

	//##ModelId=3B666521000F
	IMPORT_C static CWmlLibrary* NewL(MWapPluginSP& aPluginSP, CLocalContext& aLocalContext, CXmlElement* aRootNode);
	//##ModelId=3B6665210005
	IMPORT_C static CWmlLibrary* NewLC(MWapPluginSP& aPluginSP, CLocalContext& aLocalContext, CXmlElement* aRootNode);

	//##ModelId=3B66652003E7
	IMPORT_C ~CWmlLibrary();

	// -----------------------------------------------------------------------
	// Method to "filter" and "convert" the variety of error codes from XmlLib and WmlLib
	// to general Wap error codes defined in WapEngStd.h.
	// Client should apply this method to all error codes received from the library
	// before passing them up to Wap Engine/Control
	//##ModelId=3B66652003E5
	IMPORT_C static TInt ResolveWapErrorCode(TInt aLibraryErrorCode);

private:	// Methods

	//##ModelId=3B66652003DB
	CWmlLibrary(MWapPluginSP& aPluginSP, CLocalContext& aLocalContext, CXmlElement* aRootNode);

private:	// Methods from CXmlLibrary

	//##ModelId=3B66652003D9
	virtual TInt ExecuteValidateL(CBNFNode* aDTDRootNode);

private:	// Attributes

	//##ModelId=3B66BA950357
	CLocalContext&		iLocalContext;
	
	};

#endif	// __WMLLIB_H__
