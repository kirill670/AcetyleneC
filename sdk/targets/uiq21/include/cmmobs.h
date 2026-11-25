// CMMOBS.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
#ifndef __CMMOBS_H__
#define __CMMOBS_H__

#include <E32Std.h>

/*
 * This mixin defines the methods all observers of the Contacts app model needs to implement
 *
 */
class MContactsAppModelObserver
	{
public:
	enum TFlags
		{
		ENone					= 0x00,
		EContactCountChanged	= 0x01, // item has been deleted or added
		ECurrentContactChanged	= 0x02, // index of current contact changed
		EFindComplete			= 0x04,
		EFindStarted			= 0x08,
		EFilterComplete			= 0x10,
		EMainViewComplete		= 0x20  // The iNamedRemoteDbView is ready
		};
public:
	/*
	 * Notifies the object that the model has changed
	 *
	 * @param aFlags the action that caused the event
	 */
	virtual void HandleContactsAppModelChangeL(TInt aFlags, TInt aItemHighlightIndex) = 0;

	/*
	 * Something we couldn't deal with has happened, clean up
	 * 
	 */
	virtual void UnrecoverableError(TInt aError)=0;
	};
#endif // __CMMOBS_H__
