//-------------------------------------------------------------------------------------------------
// ECCESvrCmd.h
//
// Describes the command set, error set and format of database object across the PC/EPOC link
//
//-------------------------------------------------------------------------------------------------

#ifndef _ECCE_CUSTOM_SERVER_DEFINITIONS_H_
#define _ECCE_CUSTOM_SERVER_DEFINITIONS_H_

#include <CntDef.hrh>


// Compilation conditional control of Profile tracing.

//#define __ECCESERVER_TRACE
#ifdef __ECCESERVER_TRACE
	#define __ECCESERVER_PROFILE_RESET(aFrom,aTo) RDebug::ProfileReset(aFrom,aTo)
//	#define __COARSE_TRACE
	#ifdef __COARSE_TRACE
		#define __COARSE_PROFILE_START(aNum) RDebug::ProfileStart(aNum)
		#define __COARSE_PROFILE_END(aNum) RDebug::ProfileEnd(aNum)
		#define __FINE_PROFILE_START(aNum)
		#define __FINE_PROFILE_END(aNum)
	#else // not coarse, so must be fine trace.
		#define __FINE_TRACE
		#define __COARSE_PROFILE_START(aNum)
		#define __COARSE_PROFILE_END(aNum)
		#define __FINE_PROFILE_START(aNum) RDebug::ProfileStart(aNum)
		#define __FINE_PROFILE_END(aNum) RDebug::ProfileEnd(aNum)
	#endif // __COARSE_TRACE
#else // Tracing not defined.
	#define __ECCESERVER_PROFILE_RESET(aFrom,aTo)
	#define __COARSE_PROFILE_START(aNum)
	#define __COARSE_PROFILE_END(aNum)
	#define __FINE_PROFILE_START(aNum)
	#define __FINE_PROFILE_END(aNum)
#endif // __ECCESERVER_TRACE


//-------------------------------------------------------------------------------------------------
// Custom server op codes...

enum TECCESvrCmd
{
	// Standard operations --------------------------------
	ECmdQueryVersion		= 0x00,	// <in>]									<out> 0
	// Database operations --------------------------------					  
	ECmdFindDatabases		= 0x01, // <in> -                                   <out> [count:4][dbpath:s]*count
	ECmdCreateDatabase,				// 2<in>[dbpath:s][dbpswd:s]					<out> [handle:4]
	ECmdOpenDatabase,				// 3<in>[dbpath:s][dbpswd:s]					<out> [handle:4]
	ECmdCheckDatabase,				// 4<in>[dbpath:s]							<out> 0
	ECmdDeleteDatabase,				// 5<in>[dbpath:s]							<out> 0
	ECmdCloseDatabase,				// 6<in>[handle:4]							<out> 0
	ECmdGetDatabaseSize,			// 7<in>[handle:4]							<out> [sizeByte:4]
	ECmdSetDatabasePassword,		// 8<in>[handle:4][old:s][new:s]			    <out> 0
	ECmdGetSpecialItemIds,  		// 9<in>[dbpath:s][dppswd:s]					<out> [defTemplate:4][goldTemplate:4][ownCard:4]
	ECmdSetSpecialItemIds,			// 10<in>[dbpath:s][dppswd:s][defTemplate:4][ownCard:4]<out> -
	ECmdGetDatabaseUID,				// 11<in>[dbpath:s][dppswd:s]					<out> [uid:s]
	// Item operations ------------------------------------
	ECmdCreateContactItem,			// 12<in>[handle:4][dbpswd:s][ContactItem]	<out>[id:4]
	ECmdUpdateContactItem,			// 13<in>[handle:4][dbpswd:s][ContactItem]	<out>[id:4]
    ECmdFetchContactItem,			// 14<in>[handle:4][dbpswd:s][id:4]			<out>[ContactItem]
	ECmdDeleteContactItem,			// 15<in>[handle:4][dbpswd:s][id:4]			<out> 0
	ECmdIncItemRefCount,			// 16<in>[handle:4][dbpswd:s][id:4]			<out>[ref:4]
	ECmdDecItemRefCount,			// 17<in>[handle:4][dbpswd:s][id:4]		 	<out>[ref:4]
	ECmdGetItemRefCount,			// 18<in>[handle:4][dbpswd:s][id:4]   		<out>[ref:4]
	ECmdLockContactItem,			// 19<in>[handle:4][dbpswd:s][id:4]			<out> 0
	ECmdUnlockContactItem,			// 20<in>[handle:4][dbpswd:s][id:4]			<out> 0
	ECmdQueryIsItemDeleted,			// 21<in>[handle:4][dbpswd:s][id:4]			<out>[isDeleted:1]
	ECmdGetItemList,				// 22<in>[handle:4][dbpswd:s][itemType:4]			<out>[ids:IDList]
	ECmdGetChangedItemList,	 		// 23<in>[handle:4][dbpswd:s][itemType:4][date:8]	<out>[ids:IDList]
	// Family (group) operations --------------------------
	ECmdAddRelation,				// 24<in>[handle:4][dbpswd:s][group:4][item:4]<out> 0
	ECmdRemoveRelation,				// 25<in>[handle:4][dbpswd:s][group:4][item:4]<out> 0
	ECmdGetParents,					// 26<in>[handle:4][dbpswd:s][item:4]			<out>[ids:IDList]
	ECmdGetChildren,				// 27<in>[handle:4][dbpswd:s][group:4]		<out>[ids:IDList]
	ECmdUnlinkItem,					// 28<in>[handle:4][dbpswd:s][item:4]			<out> 0
	// Field operations -----------------------------------
    ECmdFetchField,					// 29<in>[handle:4][dbpswd:s][item:4][fieldid:4]			<out>[field:field]
	ECmdCreateField,				// 30<in>[handle:4][dbpswd:s][item:4][field:field]		<out>[id:4]
    ECmdUpdateField,				// 31<in>[handle:4][dbpswd:s][item:4][field:field]		<out>[id:4]
	ECmdDeleteField,				// 32<in>[handle:4][dbpswd:s][item:4][fieldid:4]			<out> 0
	ECmdGetContactFields,			// 33<in>[handle:4][dbpswd:s][item:4]						<out>[fields:fieldList]
	ECmdSetContactFields,			// 34<in>[handle:4][dbpswd:s][item:4][fields:fieldList]	<out>[idSet:IDList]
	ECmdUpdateContactFields,        // 35<in>[handle:4][dbpswd:s][item:4][added:fieldList]
									//								   [changed:fieldList]
									//								   [deleted:IDList]		<out>0
	ECmdCopyFields,					// 36<in>[handle:4][dbpswd:s][itemSrc:4][itemTgt:4]		<out>[count:4]
	ECmdDelContactFields,			// 37<in>[handle:4][dbpswd:s][item:4]						<out>[count:4]
	ECmdFetchFieldIds,				// 38<in>[handle:4][dbpswd:s][itemid:4]	 		 		<out>[idSet:IDList]
	// Sync operations ------------------------------------
	ECmdGenerateSyncId,	   			// 39<in>[handle:4][dbpswd:s][date:8]				 <out> [syncid:4]
	ECmdSetLastSyncDate,   			// 40<in>[handle:4][dbpswd:s][syncid:4][date:8]	 <out> 0
	ECmdGetLastSyncDate,   			// 41<in>[handle:4][dbpswd:s][syncid:4]			 <out> [date:8]
	ECmdRemoveSyncId,	   			// 42<in>[handle:4][dbpswd:s][syncid:4]			 <out> 0
	// Async find/notify change operations -----------------
	ECmdFindText,					//	43<in>[dbpath:s][dbpswd:s][findtext:s] <out>[findToken:4]
	ECmdGetFound,					//	44<in><out>[findResults:CFindResultList]
	ECmdCancelFind,					//	45<in>[findToken:4]
	ECmdNotifyChange,				//	46<in>[handle:4][dbpswd:s]
	ECmdGetChanged,					//	47<in><out>[dbUID:s][events:ChangeEventList]
	ECmdCancelNotify,				//	48<in><out>
	ECmdGetContactAndContactFields = 50,	//	
	ECmdUpdateContactItemAndWriteBack = 51,
#ifdef __COARSE_TRACE
	ECmdNotInDispatch = 100,				// Should be last cmd before the Multipart commands.
#endif
	// ----------------------------------------------------
	ECmdMultipartRequest	 = 0xFA,
    ECmdMultipartResponse	 = 0xFB,
	ECmdMultipartAbort		 = 0xFC,
	// Standard operation ---------------------------------
	ECmdQuit				 = 0xFF	// <in>[maj:1][min:1]						<out>[maj:1][min:1]
};


#ifdef __ECCESERVER_TRACE
enum TSyncFineProfile
	{
	EProfileCreateItemRead=0,
	EProfileCreateItemNew,
	EProfileCreateItemCreate,
	EProfileCreateItemWrite,
	EProfileCreateItemCompress,
	EProfileCreateItemCreatePassword,
	EProfileCreateItemCreateGetDatabase,
	EProfileCreateItemCreateNewContact,
	EProfileCreateItemCreateNewGroup,
	EProfileCreateItemCreateNewTemplate,

	EProfileCompressGetDatabase, /* 10*/
	EProfileCompressRequired,
	EProfileCompressCompact,

	EProfileUpdateItemRead,
	EProfileUpdateItemNew,
	EProfileUpdateItemUpdate,
	EProfileUpdateItemWrite,
	EProfileUpdateItemCompress,
	EProfileUpdateItemUpdateGetPassword,
	EProfileUpdateItemUpdateGetDatabase,
	EProfileUpdateItemOpen,

	EProfileUpdateItemMap, /* 21 */
	EProfileUpdateItemTemplate,
	EProfileUpdateItemGroup,
	EProfileUpdateItemSetTime,
	EProfileUpdateItemSetTemplateRefId,
	EProfileUpdateItemCommit,

	EProfileCreateItemNewContactTemplate,
	EProfileCreateItemNewContactCard,
	EProfileCreateItemNewContactAdd,

	EProfileUpdateFieldsRead,
	EProfileUpdateFieldsNew,
	EProfileUpdateFieldsModifiedNew,
	EProfileUpdateFieldsDeletedNew,

	EProfileUpdateFieldsUpdateOpenContact,
	EProfileUpdateFieldsUpdateAddedFields,
	EProfileUpdateFieldsUpdateModdedFields,
	EProfileUpdateFieldsUpdateDeletedFields,
	EProfileUpdateFieldsUpdateCommit,

	EProfileTransactionBegin,
	EProfileTransactionCommit,

	EProfileOpenDatabaseCloseApps,
	EProfileCloseDatabaseCommit,
	EProfileCloseDatabaseRestart,

	EProfileOutOfDispatchLoop

	}; // no more than 0..63 ...
#endif

//---------------------------------------------------------
// ContactItem - [id:4][itemType:4][name:s][modDate:8][modType:4][idTemplate:4][flags:4]

//---------------------------------------------------------
// itemType:
#define	KECCEItem_Type_Null      0xFFFF
#define	KECCEItem_Type_Template  0x0000
#define	KECCEItem_Type_Contact   0x0001
#define	KECCEItem_Type_Group	 0x0002
//---------------------------------------------------------
// modType

#define	KECCEMod_Type_Unchanged  0x0000		
#define	KECCEMod_Type_Inserted   0x0001
#define	KECCEMod_Type_Deleted    0x0002
#define	KECCEMod_Type_Changed    0x0004

//---------------------------------------------------------
// field flags
#define	KECCELinkFieldIsHidden				  0x00000001
#define	KECCELinkFieldIsReadOnly			  0x00000002
#define	KECCELinkFieldIsDisabled			  0x00000004
#define	KECCELinkFieldIsTemplate			  0x00000008
#define	KECCELinkFieldDoSynchronize			  0x00000010
#define	KECCELinkFieldOverRidesLabel		  0x00000020
#define	KECCELinkFieldHasExtraStream		  0x00000040
#define	KECCELinkFieldUsesTemplateTypes		  0x00000080
#define	KECCELinkFieldLabelUnspecified		  0x00000100
#define	KECCELinkFieldUserAddedField		  0x00000200
#define	KECCELinkFieldIsTemplateLabelField	  0x00000400

//-------------------------------------------------------------------------------------------------
// Error/return codes - from e32std.h
#ifdef _WINDOWS
const BYTE KErrNone					=    0;
const BYTE KErrNotFound				=  (-1);
const BYTE KErrGeneral				=  (-2);
const BYTE KErrCancel				=  (-3);
const BYTE KErrNoMemory				=  (-4);
const BYTE KErrNotSupported			=  (-5);
const BYTE KErrArgument				=  (-6);
const BYTE KErrTotalLossOfPrecision =  (-7);
const BYTE KErrBadHandle			=  (-8);
const BYTE KErrOverflow				=  (-9);
const BYTE KErrUnderflow			= (-10);
const BYTE KErrAlreadyExists		= (-11);
const BYTE KErrPathNotFound			= (-12);
const BYTE KErrDied					= (-13);
const BYTE KErrInUse				= (-14);
const BYTE KErrServerTerminated		= (-15);
const BYTE KErrServerBusy			= (-16);
const BYTE KErrCompletion			= (-17);
const BYTE KErrNotReady				= (-18);
const BYTE KErrUnknown				= (-19);
const BYTE KErrCorrupt				= (-20);
const BYTE KErrAccessDenied			= (-21);
const BYTE KErrLocked				= (-22);
const BYTE KErrWrite				= (-23);
const BYTE KErrDisMounted			= (-24);
const BYTE KErrEof					= (-25);
const BYTE KErrDiskFull				= (-26);
const BYTE KErrBadDriver			= (-27);
const BYTE KErrBadName				= (-28);
const BYTE KErrCommsLineFail		= (-29);
const BYTE KErrCommsFrame			= (-30);
const BYTE KErrCommsOverrun			= (-31);
const BYTE KErrCommsParity			= (-32);
const BYTE KErrTimedOut				= (-33);
const BYTE KErrCouldNotConnect		= (-34);
const BYTE KErrCouldNotDisconnect	= (-35);
const BYTE KErrDisconnected			= (-36);
const BYTE KErrBadLibraryEntryPoint = (-37);
const BYTE KErrBadDescriptor		= (-38);
const BYTE KErrAbort				= (-39);
const BYTE KErrTooBig				= (-40);
const BYTE KErrDivideByZero			= (-41);
const BYTE KErrBadPower				= (-42);
const BYTE KErrDirFull				= (-43);
const BYTE KErrHardwareNotAvailable	= (-44);
#endif // _WIN32

//-------------------------------------------------------------------------------------------------
// Misc constants
//const int KECCETransferBufferSize = 2048;
const int KECCETransferBufferSize = 20480;		// PETRAS 30.10.01
const int KECCECSvrVersionMaj	  = 1;
const int KECCECSvrVersionMin	  =	3;	//	JCS 17/01/2002
const int KECCECSvrVersionBld	  =	0;

const long KFoundBroadcastUID	= 0x0BADCAFE;
const long KChangedBroadcastUID	= 0x0ACECAFE;
const long KFindCompletedUID	= 0xC0DECAFE;

#endif // _ECCE_CUSTOM_SERVER_DEFINITIONS_H_

