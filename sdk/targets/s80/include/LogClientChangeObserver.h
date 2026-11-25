// LOGCLIENTCHANGEOBSERVER.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//
#ifndef __LOGCLIENTCHANGEOBSERVER_H__
#define __LOGCLIENTCHANGEOBSERVER_H__

// System includes
#include <logwrap.h>

/**
Constants
@internalComponent
*/
const TUid KLogClientChangeEventLogCleared = { 0x101F8C4F };

class MLogClientChangeObserver
/** This class allows a client of the log engine to observe specific change 
events within a given view.
@internalComponent
*/
	{
public:
	/** Handle a global change within the logs database
	
	This method is called when a generic event occurs within the log database. 
	Such events are	not specific to a view (see MLogViewChangeObserver for view 
	specific events).
	
	@param aChangeType The uid corresponding to the type of event which 
	occurred.
	@param aChangeParam1 A context-specific change paramater which can be 
	interpreted	based on the change type.
	@param aChangeParam2 A context-specific change paramater which can be 
	interpreted based on the change type.
	@param aChangeParam3 A context-specific change paramater which can be 
	interpreted	based on the change type.
	
	A list of change types and their associated parameters follows:
	
	KLogClientChangeEventLogCleared - no parameters. This event occurs when 
	the log database is cleared.	 */
	virtual void HandleLogClientChangeEventL(TUid aChangeType, TInt aChangeParam1, TInt aChangeParam2, TInt aChangeParam3) = 0;

private:
	IMPORT_C virtual void MLogClientChangeObserver_Reserved1();
	IMPORT_C virtual void MLogClientChangeObserver_Reserved2();
	};


#endif