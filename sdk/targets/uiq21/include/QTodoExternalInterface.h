// QTodoExternalInterface.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef _QTODOEXTERNALINTERFACE_H_
#define _QTODOEXTERNALINTERFACE_H_

#include <AGMIDS.H>

// App. uid
const TUid KUidTodoApp = {0x100051FC};

// View uids.
const TUid KUidTodoListView = {0x10005206};
const TUid KUidTodoDetailsView = {0x10005207};

// Messages
const TUid KUidTodoAgendaEntry = {0x10005208};
const TUid KUidTodovCalEntry = {0x100066FC};

class TTodoDNLEntryId
{
public:
	TAgnUniqueId iId; // id of entry
};

typedef TPckgBuf<TTodoDNLEntryId> TTodoDNLAgendaEntryBuf;

#endif
