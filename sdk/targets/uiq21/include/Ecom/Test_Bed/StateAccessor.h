// StateAccessor.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file StateAccessor.h
	Comments : This file contains the definition of the class MStateAccessor
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __STATEACCESSOR_H__
#define __STATEACCESSOR_H__

#include <e32base.h>

/**
	@public
	@class MStateAccessor
	Dependencies : None
	Comments : Mixin which is used to define a class used for state checking of 
	a test object.
 */
//##ModelId=3AC9D06301C9
class MStateAccessor
	{
public:
/**
	@fn				InvariantTest(TAny* aTestObject) = 0
	Intended Usage	:	Override this in the derived class to implement 
						invariant testing
	@since			7.0
	@param			aTestObject The object to be tested
	@return			One of the EPOC standard error codes indicating the result of the test
	@pre 			A valid test object must be passed in
	@post			Returns an error code dependant on the result of the test
 */
	//##ModelId=3AC9D06301DF
	virtual TInt InvariantTest(TAny* aTestObject) = 0;
/**
	@fn				Internalize(TAny* aTestObject) = 0
	Intended Usage	:	Override this in the derived class to implement 
						object state loading.
	@since			7.0
	@param			aTestObject The object to be tested
	@return			One of the EPOC standard error codes indicating the outcome of the attempt
	to load the object state.
	@pre 			A valid test object must be passed in
	@post			Returns an error code dependant on the result of the test
 */
	//##ModelId=3AC9D06301DD
	virtual TInt Internalize(TAny* aTestObject) = 0;
/**
	@fn				Externalize(TAny* aTestObject) = 0
	Intended Usage	:	Override this in the derived class to implement 
						object state persistence.
	@since			7.0
	@param			aTestObject The object to be tested
	@return			One of the EPOC standard error codes indicating the outcome of attempt
	to externalize the object.
	@pre 			A valid test object must be passed in
	@post			Returns an error code dependant on the result of the test
 */
	//##ModelId=3AC9D06301D3
	virtual TInt Externalize(TAny* aTestObject) = 0;
	};

#endif
