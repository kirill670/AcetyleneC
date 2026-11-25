// ComponentInfo.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file ComponentInfo.h
	Comments : This file contains the definition of the class CComponentInfo

	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __COMPONENTINFO_H__
#define __COMPONENTINFO_H__

#include <e32base.h>
#include <f32file.h>

#include "UnitTestInfo.h"

/**
	@public
	@class CComponentInfo
	Dependencies : CBase
	Comments : Holds information about all the tests within a component.
 */
//##ModelId=3A70658B02D7
class CComponentInfo : public CBase
	{
public:

/**
	@fn				static CComponentInfo* NewLC(TEntry* aEntry, 
												 RPointerArray<CUnitTestInfo>* aUnitTestsInfo)
	Intended Usage	:	Standard two phase construction which leaves a CComponentInfo on the 
	cleanupstack.  This object takes ownership of both parameters.
	Error Condition	:	
	@since			7.0
	@param			aEntry Indicates the dll which contains this test component
	@param			aUnitTestsInfo The transition sets in this component test
	@return			CComponentInfo* A pointer to the newly created class
	@pre 			None
	@post			CComponentInfo is on the CleanupStack
 */
	//##ModelId=3A70658B031D
	static CComponentInfo* NewLC(TEntry* aEntry, RPointerArray<CUnitTestInfo>* aUnitTestsInfo);

/**
	@fn				static CComponentInfo* NewL(TEntry* aEntry, 
												RPointerArray<CUnitTestInfo>* aUnitTestsInfo)
	Intended Usage	:	Standard two-phase construction which leaves nothing on the 
	cleanup stack.  This object takes ownership of both parameters.
	Error Condition	:	
	@since			7.0
	@param			aEntry Indicates the dll which contains this test component
	@param			aUnitTestsInfo The transition sets in this component test
	@return			CComponentInfo* A pointer to the newly created class
	@pre 			None
	@post			Nothing is on the CleanupStack
 */
	//##ModelId=3A70658B0314
	IMPORT_C static CComponentInfo* NewL(TEntry* aEntry, RPointerArray<CUnitTestInfo>* aUnitTestsInfo);

/**
	@fn				~CComponentInfo()
	Intended Usage	:	Standard destructor
	Error Condition	:	
	@since			7.0
 */
	//##ModelId=3A70658B0313
	~CComponentInfo();


/**
	@fn				inline TEntry* Entry() const
	Intended Usage	:	Get the full path and name of this test component
	Error Condition	:	
	@since			7.0
	@return			TEntry* Information on the dll containing this components tests.
	@pre 			None
 */
	//##ModelId=3A70658B030B
	inline const TEntry& Entry() const;

/**
	@fn				inline RPointerArray<CUnitTestInfo>& UnitTestsInfo() const
	Intended Usage	:	Get a list of the transition sets in this component
	Error Condition	:	
	@since			7.0
	@return			RPointerArray<CUnitTestInfo>& Information on the unit tests contained in 
	this component.
	@pre 			None
 */
	//##ModelId=3A70658B030A
	inline const RPointerArray<CUnitTestInfo>& UnitTestsInfo() const;

private:
/**
	@fn				CComponentInfo(TEntry* aEntry, RPointerArray<CUnitTestInfo>* aUnitTestsInfo)
	Intended Usage	:	Standard constructor.  This object takes ownership of both parameters.
	Error Condition	:	
	@since			7.0
	@param			aEntry Indicates the dll which contains this test component
	@param			aUnitTestsInfo The transition sets in this component test
 */
	//##ModelId=3A70658B0300
	CComponentInfo(TEntry* aEntry, RPointerArray<CUnitTestInfo>* aUnitTestsInfo);

/**
	@fn				void ConstructL()
	Intended Usage	:	Standard second phase of construction
	Error Condition	:	
	@since			7.0
	@pre 			First phase of construction is complete
	@post			Object is fully constructed
 */
	//##ModelId=3A70658B02FF
	void ConstructL();

private:
/** The full path and name of this test component. This object takes ownership of iComponentEntry
	at construction.*/
	//##ModelId=3A71AF83020C
	TEntry* iComponentEntry;
/** Array of the subsets of transitions in this component. This object takes ownership of 
	iUnitTestsInfo at construction.*/
	//##ModelId=3A71AF830202
	RPointerArray<CUnitTestInfo>* iUnitTestsInfo;
	};

#include "ComponentInfo.inl"

#endif
