// QMappExtInferface.h
//
// Copyright (c) 1999-2002 Symbian Ltd.  All rights reserved.
//

// QMappUids for use to DNL/Switch to the Quartz messaging application
#ifndef __QMAPPUIDS__
#define __QMAPPUIDS__
#include <msvstd.h>
// ViewArch switch commands here for now
#define  KQMappToBaseView 0x1000
#define  KQMappToEmailView 0x1001
#define  KQMappToSmsView 0x1002
#define	 KQMappToFaxView 0x1003
#define  KQMappCreateEmail 0x1004
#define  KQMappCreateSms 0x1005
#define	 KQMappCreateFax 0x1006
#define  KQMappToGenericView 0x1007
#define	 KQMappViewMessage 0x1008
#define	 KQMappToObexView 0x1009
#define  KQMappToMmsView 0x100A
#define  KQMappCreateMms 0x100B
/**
 * QMAPP View Arch views
 *
 */
const TUid KUidMsgAppUid		={0x100051E3};
const TUid KUidMsgBaseViewUid   ={0x1000520f};
const TUid KUidMsgListViewUid   ={0x10005210};

/** QMapp View switching commands*/
const TUid  KUidQMappSwitchToBaseView = {KQMappToBaseView};
const TUid  KUidQMappSwitchToEmailView = {KQMappToEmailView};
const TUid  KUidQMappSwitchToSmsView = {KQMappToSmsView};
const TUid  KUidQMappSwitchToFaxView = {KQMappToFaxView};
const TUid  KUidQMappSwitchToGenericView = {KQMappToGenericView};
const TUid  KUidQMappSwitchToObexView = {KQMappToObexView};
const TUid  KUidQMappSwitchToMmsView = {KQMappToMmsView};

/**
 * These are internal views only
 */
const TUid KUidMsgEmailListViewUid  ={0x10005211};
const TUid KUidMsgSmsListViewUid   ={0x10005212};
const TUid KUidMsgFaxListViewUid   ={0x10005213};
const TUid KUidMsgMmsListViewUid	={0x10005214};
const TUid KUidMsgOtherListViewUid	={0x10005215};
/************************************************/

// Create NewMessage Views
const TUid KUidMsgCreateSmsViewUid   ={0x101F6185};
const TUid KUidMsgCreateMmsViewUid	={0x101F6184};
const TUid KUidMsgCreateEmailViewUid ={0x101F6186};



/**
 * DNL Creation commands
 */
const TUid KUidQMappCreateEmail = {KQMappCreateEmail};
const TUid KUidQMappCreateFax = {KQMappCreateFax};
const TUid KUidQMappCreateSms = {KQMappCreateSms};
const TUid KUidQMappCreateMms = {KQMappCreateMms};

/**
 * DNL to create a new msg with messaging
 */
class TQMappDnlCreate
        {
public:
		/**  address of the receiver */
        TBuf<128> iAddress; 
		/**  name of the receiver */
		TBuf<128> iTo; 
        };

typedef TPckgBuf<TQMappDnlCreate> TQMappDnlCreateBuf;

/**
 * DNL view/edit existing message command, or to go to a specifc service list view specified in the parameter
 */
const TUid KUidQMappViewMessage = {KQMappViewMessage};
/**
 * DNL to switch to a listview and edit/view an existing message
 */
class TQMappDnlView
        {
public:
		/** 
		 * This can either be a service or a message entry id, if its a 
		 * service id, it will only switch to that service list view
		 */
        TMsvId iMessageId;
        };

typedef TPckgBuf<TQMappDnlView> TQMappDnlViewBuf;


#endif