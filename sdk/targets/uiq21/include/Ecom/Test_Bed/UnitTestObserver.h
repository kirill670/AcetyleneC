// UnitTestObserver.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file UnitTestObserver.h
	Comments : This file contains the definition of the class MUnitTestObserver
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __UNITTESTOBSERVER_H__
#define __UNITTESTOBSERVER_H__

class CUnitTest;

/**
	@public
	@class MUnitTestObserver
	@Depends : None
	Comments : Provides a callback method to the CComponentTester to 
	indicate that the unit test has completed
 */
//##ModelId=3AC9D0640120
class MUnitTestObserver
	{
public:
/**
	@fn				virtual Complete(CUnitTest* aUnitTest) = 0
	Intended Usage	:	Allows a 'callback' to indicate that the observed class has
					completed its task
	Error Condition	: None	
	@since			7.0
	@param			aUnitTest The unit test which has completed
	@pre 			Should be called to indicate that all transitions in the unit test have completed
	@post			The unit test should have completed all operation as it could now be unloaded
 */
	//##ModelId=3AC9D0640121
	virtual void Complete(CUnitTest* aUnitTest) = 0;
	};

#endif
