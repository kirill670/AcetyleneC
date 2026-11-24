//  BIOUUIDS.H
//
//	Copyright (c) 1999-2004 Symbian Software Ltd.  All rights reserved.
//
//  Contains the TUid defines for the Bio Messaging 

#if !defined(__BIOUTILS_H__)
#define __BIOUTILS_H__

// forward declarations
class TUid;

/** UID of the Smart Message Parser DLL. */
const TUid KUidSmartMessageParserDll    = { 0x10001251};

/** BIO specific error/panic code base. */
const TInt KBIOMessageBaseError				= -505;
/** BIO message not found error. */
const TInt KBIOMessageNotFound				= KBIOMessageBaseError;
/** BIO server MTM already active error. */
const TInt KBIOMessageSvrMtmNotInactive		= KBIOMessageBaseError-1;
/** No BIO parser error. */
const TInt KBIOMessageNoParserCreated		= KBIOMessageBaseError-2;   
/** BIO parser in use error. */
const TInt KBIOMessageParserDllStillInUse	= KBIOMessageBaseError-3;      
/** BIO operation already active error. */
const TInt KBIOMessageOperationNotInactive	= KBIOMessageBaseError-4;
/** BIO server MTM operation not supported. */
const TInt KBIOMessageSvrNotSupported		= KBIOMessageBaseError-5;

/** Unused. */
const TUid KUidMsvNbsEditor={0x10001264};

//  New BIO Messaging TUids

/** Stream ID used for storing parsed BIO data. */
const TUid KUidMsvBIODataStream			= {0x10005268}; // stream used for storing parsed data

//  BIO Mtm components
/** BIO message type UID. */
const TUid KUidBIOMessageTypeMtm		= {0x10001262};
/** BIO client MTM UID. */
const TUid KUidBIOMessageClientMtmDll	= {0x1000125A}; //previously NBSC, now BIOC
/** BIO server MTM UID. */
const TUid KUidBIOMessageServerMtmDll	= {0x1000125C}; //previously NBSS, now BIOS
/** BIO UI MTM UID. */
const TUid KUidBIOMessageUiLayerMtmDll	= {0x10001265}; //previously NBUM, now BIUM

/** BIO message viewer UID. */
const TUid KUidBIOMessageViewerApp		= {0x10001264}; //previously NBED,now BIED

#endif //__BIOUTILS_H__
