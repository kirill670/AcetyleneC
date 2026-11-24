// AGMCALLB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMCALLB_H__
#define __AGMCALLB_H__

#include "agmmodel.h"

class  MAgnModelStateCallBack
/** Agenda model state callback.

An object of this class may be specified when the agenda model is constructed. 
The model's state can be one of CAgnEntryModel::ENoFile, CAgnEntryModel::EOk or 
CAgnEntryModel::EBlocked. The state can be found by calling the model's 
State() method. If a state callback was specified, the model informs 
the user when it is about to change state via the state callback.

When the user calls a model function whose execution could take some time 
they recieve a state callback with aState set to EBlocked. An exception to 
this is when an empty file is opened (i.e. which contains no entries). In this 
case, the OpenL() function returns synchronously.

While the model is carrying out the operation, it notifies the user of its 
progress with a progress callback (see MAgnProgressCallBack) and 
when finished, notifies the user via StateCallBack() with aState set to EOk 
to indicate it has left the blocked state. 
@publishedAll
@released
*/
	{
public: 
	/** Agenda model state callback.
	
	This is called with a value of EBlocked when the model is about to enter a blocked 
	state, for instance when opening, merging or tidying, and with EOk when it is about 
	to leave the blocked state.
	
	@param aState The current state of the model. */
	virtual void StateCallBack(CAgnEntryModel::TState aState) = 0;
	};


class MAgnProgressCallBack
/** Agenda model progress callback.

This provides information about the progress of prolonged agenda model operations, 
and about how the operation terminated.

An MAgnProgressCallBack object is usually specified when the client requests 
an activity such as merging, tidying or save as, which might take some time 
to complete, so that the client needs to be updated on its progress and completion state. 
See for example CAgnIndexedModel::MergeL().

As the model is carrying out the operation, it calls Progress() with aPercentageCompleted 
set to the amount of the operation that has been carried out so far. Note 
that when the operation is complete, Progress() is not called with aPercentageCompleted 
set to 100. Instead the Completed() method is called. Note also that if the 
operation completes quickly, for instance when opening a small file, then 
Progress() will probably not be called. If on return, aError is anything other 
than KErrNone then something went wrong during the operation. 
@publishedAll
@released
*/
	{
public:
	/** Called by the agenda model during prolonged operations such as merging and 
	tidying, to indicate how much of the operation has been completed. 
	
	Note that this function is not called when the operation is complete, with aPercentageCompleted 
	set to 100; instead the Completed() method is called. The frequency with which 
	this function is called is indicated by a callback frequency parameter, 
	see for instance CAgnIndexedModel::MergeL().
	
	@param aPercentageCompleted The percentage of the task that has been completed. */
	virtual void Progress(TInt aPercentageCompleted) = 0;
	/** Called when the function completes.

	@param aError Indicates how the function completed. KErrNone if successful, 
	otherwise one of the system error codes. */
	virtual void Completed(TInt aError = KErrNone) = 0;
	};

#endif

