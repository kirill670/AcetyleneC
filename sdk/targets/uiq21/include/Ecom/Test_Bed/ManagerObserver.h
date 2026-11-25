//
// ManagerObserver.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file ManagerObserver.h
	Comments : This file contains the definition of the class MManagerObserver
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __MANAGEROBSERVER_H__
#define __MANAGEROBSERVER_H__

/**
	@public
	@class MManagerObserver
	Dependencies : None
	Comments : Observer to allow the CTestManager to indicate when all the
	tests are complete.
*/
class MManagerObserver
	{
public:
/**
	@fn				TestsComplete()
	Intended Usage	: 
	@since			7.0
	@pre 			Observer class is constructed
	@post			Depends on implementation
 */
	virtual void TestsComplete() = 0;
	};

#endif // __MANAGEROBSERVER_H__
