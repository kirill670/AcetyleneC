// QCONTACTSEXTERNALINTERFACE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __QCONTACTSEXTERNALINTERFACE_H__
#define __QCONTACTSEXTERNALINTERFACE_H__

#include <E32Std.h>
#include <cntdef.h>
#include <w32std.h> // TKeyEvent

const TUid KUidContactsManagerApp={0x10003a74};
const TUid KUidContactsAppListView={0x100038f5};
const TUid KUidContactsAppDetailedView={0x100038f4};
const TUid KUidContactsAppDefaultTemplate={0x10003E7E};
const TUid KUidContactsAppPreferences={0x10003E7F};
const TUid KUidContactsAppPrintSetup={0x10003a75};
const TUid KUidContactsAppSimDetailView={0x101F591D}; 

enum TViewTab
	{
	EContactsAppInfoTab=0,
	EContactsAppNotesTab,
	EContactsAppPictureTab
	};

/**
 * Contacts DNL:s
 */

//
//
//

/**
 * DNL to detailed view in Contacts
 */
const TUid KUidCntDnlDetailed={0x100051ee};

class TCntDnlDetailed
	{
public:
	TContactItemId id; // id of contact to view
	TInt tab; // default tab to show in view (see enum above)
	};

typedef TPckgBuf<TCntDnlDetailed> TCntDnlDetailedBuf;

//
//
//

/**
 * DNL to edit view in Contacts, with id to view
 */
const TUid KUidCntDnlEdit={0x100051ef};

class TCntDnlEdit
	{
public:
	TContactItemId id; // id of contact to view
	TInt tab; // default tab to show in view (see enum above)
	};

typedef TPckgBuf<TCntDnlEdit> TCntDnlEditBuf;

//
//
//

/**
 * DNL to edit view in Contacts, creating a new contact with no data.
 */
const TUid KUidCntDnlNew={0x100051f0};

/**
 * DNL to edit view in Contacts, creating a new contact with a phone number filled in.
 */
const TUid KUidCntDnlNewPhone={0x101f6cea};

/**
 * DNL to edit view in Contacts, creating a new contact with an enail adress filled in.
 */
const TUid KUidCntDnlNewEmail={0x101f6ceb};

class TCntDnlNew
	{
public:
	TBuf<128> iData; // Data to be inserted in field.
	};

typedef TPckgBuf<TCntDnlNew> TCntDnlNewBuf;

#endif //__QCONTACTSEXTERNALINTERFACE_H__
