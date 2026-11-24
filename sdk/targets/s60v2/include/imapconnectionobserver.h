// ImapConnectionObserver.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__IMAPCONNECTIONOBSERVER_H__)
#define __IMAPCONNECTIONOBSERVER_H__

/** IMAP4 connection observer events.

@see MMsvImapConnectionObserver 
@publishedAll
@released
*/
enum TImapConnectionEvent
	{
	/** Connecting to server. */
	EConnectingToServer,
	/** Synchronising folder list. */
	ESynchronisingFolderList,
	/** Synchronising inbox. */
	ESynchronisingInbox,
	/** Synchronising folders. */
	ESynchronisingFolders,
	/** Synchronisation complete. */
	ESynchronisationComplete,
	/** Disconnecting. */
	EDisconnecting,
	/** Connection completed. */
	EConnectionCompleted
	};

//	Mix-in class to allow observation of the stages of an IMAP operation
//
class MMsvImapConnectionObserver
/** Abstract base class used for IMAP4 connection observation. 

A derived class to handle IMAP4 connection events should override the HandleImapConnectionEvent() 
member function. 
@publishedAll
@released
*/
	{
public:
	/** Called when a connection event occurs.
	
	@param aConnectionState Connection event */
	virtual void HandleImapConnectionEvent(TImapConnectionEvent aConnectionState)=0;
	};

#endif
