// DAMOBSRV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __MOBSERV_H__
#define __MOBSERV_H__

class MDaObserver
 	{
public:
	enum TNotification 
		{
		EDefaultNotification=1,
		EIncrementalNotification=2,
		ENoRecordsInView,
		ENoRecordsInDatabase,
		ESearchComplete,
		EStartSearch,
		ENotFoundYet,
		ERecordAdded,
		ERecordDeleted,
		ERecordUpdated,
		};
	virtual void DeleteRowL(){}	
	virtual void NextL() {}
	virtual void PreviousL() {}
	virtual void ResetVisibleRange() {} // Does not seem the right place
	virtual void UpdateL(TInt aNotification)=0;
	virtual void AlertWin(const TDesC& /*aMessage*/){}
	};

#endif