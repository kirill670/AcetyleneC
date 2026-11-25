// TransitionObserver.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file TransitionObserver.h
	Comments : This file contains the definition of the class MTransitionObserver
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __TRANSITIONOBSERVER_H__
#define __TRANSITIONOBSERVER_H__

class CTransition;

/**
	@public
	@class MTransitionObserver
	Dependencies : None
	Comments : Provides a callback method to the CUnitTest to indicate that the 
	specified transition has completed an asynchronous function.
 */
//##ModelId=3AC9D0610089
class MTransitionObserver
	{
public:
/**
	@fn				virtual void SetCurrentTransition(CTransition& aTransition) = 0
	Intended Usage	:	Passes the transition which is about to run.
					This allows transition information can be retrieved and 
					Repeat() can then be called on the transition.
	@since			7.0
	@param			aTransition The transition to set as current
	@return			void 
	@pre 			None
	@post			aTransition will be stored as a pointer to the currently executing transition
 */
	//##ModelId=3AC9D0610091
	virtual void SetCurrentTransition(CTransition& aTransition) = 0;

/**
	@fn				virtual void Complete(CTransition& aTransition, TInt aAsyncPostCheckError) = 0
	Intended Usage	:	Called to indicate that an asynchronous function on the specified
					transition has completed.
	@since			7.0
	@param			aTransition The transition which has completed
	@param			aAsyncPostCheckError An error code from the second phase of post-condition
					validation done after the transition's asynchronous request had completed.
					Used for asynchronous transitions only - for synchronous transitions, 2-phase
					post-condition checking does not apply, and a value of KErrNone is supplied.
	@pre 			None
	@post			Depends on observer implementation.  For example, aTransition has completed, 
					therefore if all transitions have completed the unit test is complete.
 */
	//##ModelId=3AC9D061008A
	virtual void Complete(CTransition& aTransition, TInt aAsyncPostCheckError) = 0;
	};

#endif
