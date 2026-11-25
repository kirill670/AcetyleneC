// MMFrameworkSP.h
//
// Copyright (C) 1997-2001 Symbian Ltd. All rights reserved.
//

#ifndef __MFRAMEWORKSP_H__
#define __MFRAMEWORKSP_H__

// System includes
//
#include <E32Def.h>

// Forward class declarations
//
class MWAPEngineObserver;
class CXmlTaskCoordinator;
class CLocalContext;
class CWapGCtxClient;
class CAttributeLookupTable;
class MWtaiPublicObserver;

//##ModelId=3B666FA40394
class MFrameworkSP
	{
public:

/**
	@fn				Observer() =0
	Intended Usage	:	Return a pointer to the engine observer (pointer 
	because it could be NULL).
	@since			6.0
	@return			A pointer to the MWAPEngineObsever object.
 */
	//##ModelId=3B666FA403C7
	virtual MWAPEngineObserver* Observer() =0;

/**
	@fn				TaskCoordinator() =0
	Intended Usage	:	Gets the Task Coordinator.
	@since			6.0
	@return			A reference to the Task Coordinater.
 */
	//##ModelId=3B666FA403C6
	virtual CXmlTaskCoordinator& TaskCoordinator() =0;
	
/**
	@fn				LocalContext() =0
	Intended Usage	:	Gets WAP Local Context.
	@since			6.0
	@return			A reference to the WAP Local Context. 
 */
	//##ModelId=3B666FA403BE
	virtual CLocalContext& LocalContext() =0;

/**
	@fn				GlobalContext() =0
	Intended Usage	:	Gets WAP Global Context.
	@since			6.0
	@return			A reference to the WAP Global Context. 
 */
	//##ModelId=3B666FA403BD
	virtual CWapGCtxClient& GlobalContext() =0;

/**
	@fn				AttributeLookup() =0
	Intended Usage	:	Gets the Attribute Look Up Table.
	@since			6.0
	@return			A reference to the Attribute Look Up Table.
 */
	//##ModelId=3B666FA403BC
	virtual CAttributeLookupTable& AttributeLookup() =0;

/**
	@fn				WtaiPublicObserver() =0
	Intended Usage	:	
	@since			6.0
	@return			A reference to the WtaiPublic observer 
 */
	//##ModelId=3B666FA403B2
	virtual MWtaiPublicObserver& WtaiPublicObserver() =0;

	};

#endif	// __MFRAMEWORKSP_H__
