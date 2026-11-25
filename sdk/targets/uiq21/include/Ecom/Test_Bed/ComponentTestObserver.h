// ComponentTestObserver.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file ComponentTestObserver.h
	Comments : This file contains the definition of the class MComponentTestObserver
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __COMPONENTTESTOBSERVER_H__
#define __COMPONENTTESTOBSERVER_H__

class CComponentTester;

/**
	@public
	@class MComponentTestObserver
	Dependencies : None
	Comments : Allows a 'callback' through the Complete() function to indicate that the 
	observed CComponentTester has completed its task
 */
//##ModelId=3AC9D0640329
class MComponentTestObserver
	{
public:
/**
	@fn				virtual void Complete(CComponentTester* aTester, TInt aStatus) = 0
	Intended Usage	:	Indicates that the CComponentTester has completed a unit test
	@since			7.0
	@param			aTester The observed component tester.
	@param			aUnitTestId The id of the unit test which has completed.
	@pre 			The specified unit test should have been launched
	@post			If all unit tests are complete then the specified CComponentTester and 
	associated library are marked for deletion/unloading, or the next unit test is run.
 */
	//##ModelId=3AC9D064033D
	virtual void Complete(CComponentTester* aTester, TInt aUnitTestId) = 0;
	};

#endif
