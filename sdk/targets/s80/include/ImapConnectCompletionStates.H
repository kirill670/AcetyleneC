//	ImapConnectCompletionStates.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

//	Enumerations used to communicate the point at which a client
//	requires an imap connection operation to complete.

#if !defined(__IMAPCONNECTCOMPLETIONSTATES_H__)
#define __IMAPCONNECTCOMPLETIONSTATES_H__

/**
@internalComponent
@released
*/
enum TImapConnectionCompletionState
	{
	EAfterConnect=1,
	EAfterFullSync,
	EAfterDisconnection
	};

#endif
