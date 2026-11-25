// EMSYNCC.H	  
// Written by Martin H June 1998
// (C) Copyright Psion Software PLC 1998
//
// Contains the codes that define which service is required of CEmSyncInterface

#if !defined(__EMSYNCC_H__)
#define __EMSYNCC_H__

const int KUidEMailSyncInterfaceValue = 0x1000182C;

const int KEmSyncMajVer	= 1;
const int KEmSyncMinVer	= 1;
const int KEmSyncBldVer	= 29; // note for 30/31 I haven't incremented this as I don't know if the PC code will need recompiling

const int KUidMtmTypeSyncValue = 0x1000412A;
const int KUidMtmTechnologyGroupSyncValue = 0x10004129;

enum TEmSyncCmdCode
	{
	EEmSyncCmdNone,			// reserved for internal useage
	EEmSyncCmdFetchIndex,
	EEmSyncCmdAddEMail,
	EEmSyncCmdFetchEMail,
	EEmSyncCmdDeleteMessage,
	EEmSyncCmdUpdateEMailContent,
	EEmSyncCmdUpdateEMailBody,
	EEmSyncCmdFetchAttachment,
	EEmSyncCmdGetAttachmentName,
	EEmSyncCmdAddAttachment,
	EEmSyncCmdDeleteAttachment, 
	EEmSyncCmdIncRefCount,
	EEmSyncCmdDecRefCount,
	EEmSyncCmdMoveMessage,
	EEmSyncCmdQueryVersion,
	EEmSyncCmdUseOrCreateService,
	EEmSyncCmdGetServices,
	EEmSyncCmdIsMtmPresent,
	EEmSyncCmdIsMtmBelongingToTechnologyTypePresent,
	EEmSyncCmdDeleteEMailsBetweenDates
	};

enum TEmSyncMessageType
	{
	EMessageTypeUnknown,
	EMessageTypeRoot,
	EMessageTypeService,
	EMessageTypeFolder,
	EMessageTypeMessage,
	EMessageTypeAttachment
	};


enum TEmSyncMessageAttribute
	{
	EMessageStatusComplete			= 0x01,
	EMessageStatusNew				= 0x02,
	EMessagesStatusUnread			= 0x04,
	EMessageStatusFailed			= 0x08,
	EMessageIsVisible				= 0x10,
	EMessageIsReadOnly				= 0x20,
	EMessageHasMultipleRecipients	= 0x40,
	EMessageIsDeleted				= 0x80
	};

enum TEmSyncMessagePriority
	{
	EMessageHighPriority,
	EMessageMediumPriority,
	EMessageLowPriority
	};

#endif


