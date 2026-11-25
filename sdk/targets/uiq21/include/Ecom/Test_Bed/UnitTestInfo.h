// UnitTestInfo.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file UnitTestInfo.h
	Comments : This file contains the definition of the class CUnitTestInfo
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __UNITTESTINFO_H__
#define __UNITTESTINFO_H__

#include <e32base.h>

/**
	@public
	@class CUnitTestInfo
	Dependencies : CBase
	Comments : Storage for information about a group of transitions.  This group will normally
	correspond to the contents of a CUnitTest.
 */
//##ModelId=3A70658D0154
class CUnitTestInfo : public CBase
	{
public:

/**
	@fn				static CUnitTestInfo* NewLC(const TDesC& aSetId)
	Intended Usage	:	Two phase constructor which leaves a CTransition* on the cleanup stack
	Error Condition	: Leave with an error code.
	@exception		KErrNoMemory
	@since			7.0
	@param			aSetId An identifier for this CUnitTestInfo
	@return			CUnitTestInfo* A pointer to the newly created class
	@pre 			None
	@post			A CUnitTestInfo is on the CleanupStack
 */
	//##ModelId=3A70658D019B
	static CUnitTestInfo* NewLC(const TDesC& aSetId);

/**
	@fn				static CUnitTestInfo* NewL(const TDesC& aSetId)
	Intended Usage	:	Two phase constructor which leaves nothing on the cleanup stack
	Error Condition	:	
	@since			7.0
	@param			aSetId An identifier for this CUnitTestInfo
	@return			CUnitTestInfo* A pointer to the newly created class
	@pre 			None
	@post			Nothing is on the CleanupStack
 */
	//##ModelId=3A70658D0191
	static CUnitTestInfo* NewL(const TDesC& aSetId);

/**
	@fn				~CUnitTestInfo()
	Intended Usage	:	Standard destructor
	Error Condition	:	
	@since			7.0
 */
	//##ModelId=3A70658D0190
	~CUnitTestInfo();

/**
	@fn				inline const TDesC& UnitTestId() const
	Intended Usage	:	Returns the identifier of this CUnitTestInfo
	Error Condition	:	
	@since			7.0
	@return			const TDesC& The identifier of this UnitTest
	@pre 			None
 */
	//##ModelId=3A70658D0188
	inline const TDesC& UnitTestId() const;

private:
/**
	@fn				CUnitTestInfo()
	Intended Usage	:	Default constructor
	Error Condition	:	
	@since			7.0
 */
	//##ModelId=3A70658D0186
	CUnitTestInfo();

/**
	@fn				void ConstructL(const TDesC& aSetId)
	Intended Usage	:	Second phase of safe construction method
	Error Condition	:	
	@since			7.0
	@param			aSetId An identifier for this CUnitTestInfo
	@pre 			First phase of construction is complete
	@post			Object if fully constructed
 */
	//##ModelId=3A70658D017C
	void ConstructL(const TDesC& aUnitTestId);

private:
/** An identifier for this unit test */
	//##ModelId=3A71AF8401CB
	HBufC* iUnitTestId;
	};

#include "UnitTestInfo.inl"

#endif
