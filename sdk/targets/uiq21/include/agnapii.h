// AGNAPII.H	  
// (C) Copyright Psion Software PLC 1999
//
// Contains the codes that define which service is required of the remote
// agenda api


#if !defined(__AGNAPII_H__)
#define __AGNAPII_H__

// the build/version number of this release
const int KAgnApiMajVer	= 1;
const int KAgnApiMinVer	= 1;
const int KAgnApiBldVer	= 12; 
const int KAgnApiNullDate = 0xFFFF; // recorded in the year portion of dates to indcate a null date

_LIT(KAgnApiDefaultFilter, "DefaultFilter");
//#if defined(__GCC32__)
//const __wchar_t* const KAgnApiDefaultFilter = L"DefaultFilter";
//#elif defined(__VC32__)
//const unsigned short int* const KAgnApiDefaultFilter = L"DefaultFilter";
//#endif

enum TAgnApiFilterSetting 
	{ // when calling a function which uses a filter these enums define the bit settings for the filter
	EAgnApiFilterIncludeTimedAppts=0x01,			// include timed appointments
	EAgnApiFilterIncludeUnTimedAppts=0x02,			// include untimed appointments
	EAgnApiFilterIncludeEvents=0x04,				// include events
	EAgnApiFilterIncludeAnnivs=0x08,				// include anniversaries
	EAgnApiFilterIncludeTodos=0x10,					// include todos
	EAgnApiFilterIncludeRpts=0x20,					// include repeating entries
	EAgnApiFilterIncludeRptsNextInstanceOnly=0x40, 	// include only the next instance of a repeating entry
	EAgnApiFilterIncludeNonRpts=0x80, 				// include non repeating
	EAgnApiFilterIncludeCrossedOut=0x100,			// include crossed out entries
	EAgnApiFilterIncludeAlarmedOnly=0x1200,			// include alarmed entries
	EAgnApiFilterIncludeAll=EAgnApiFilterIncludeTimedAppts|EAgnApiFilterIncludeUnTimedAppts|EAgnApiFilterIncludeEvents|
				EAgnApiFilterIncludeAnnivs|EAgnApiFilterIncludeTodos|EAgnApiFilterIncludeRpts|
				EAgnApiFilterIncludeNonRpts| EAgnApiFilterIncludeCrossedOut // include them all
	};


enum TAgnApiWhichInstance
	{ // when updating or deleting an instance this is used to indicate to which instances the change applies
	EAgnApiCurrentInstance,				// Only the current instance
	EAgnApiAllInstances,				// All instances
	EAgnApiCurrentAndFutureInstances,	// The current and all future instances
	EAgnApiCurrentAndPastInstances		// The current and all past instances
	};


enum TAgnApiCmdCode
	{
	EAgnApiCmdNone,
	EAgnApiCmdQueryVersion,					// find out what version of the agnapi dll is being used
	EAgnApiCmdOpen,							// open an existing agenda file
	EAgnApiCmdCreate, 						// create a new agenda file
	EAgnApiCmdClose,						// close an opened agenda file - NOT IMPLEMENTED YET
	EAgnApiCmdGetUids,						// get a list of entry uids
	EAgnApiCmdAddEntries,					// add one or more entries
	EAgnApiCmdFetchEntries,					// fetch one or more entries
	EAgnApiCmdDeleteEntry,					// delete an entry
	EAgnApiCmdUpdateEntries,				// update one or more entries
	EAgnApiCmdPasteEntry,					// paste a previously cut entry
	EAgnApiCmdGetTodoListList,				// get a list of what todo lists their are
	EAgnApiCmdDeleteTodoList,				// delete a todo list
	EAgnApiCmdAddTodoList,					// add a new todo list
	EAgnApiCmdGetEntryCount,				// get the number of entries in the agenda
	EAgnApiCmdGetDefaultEventDisplayTime,
	EAgnApiCmdGetDefaultAnnivDisplayTime,
	EAgnApiCmdGetDefaultDayNoteDisplayTime,
	EAgnApiCmdSetDefaultEventDisplayTime,
	EAgnApiCmdSetDefaultAnnivDisplayTime,
	EAgnApiCmdSetDefaultDayNoteDisplayTime,

	EAgnApiCmdGetInstanceUids,				// get a list of instance uids											
	EAgnApiCmdFetchDayInstanceList,			// fetch a list of instance ids for a specified day
	EAgnApiCmdFetchTodoInstanceList,		// fetch a list of todo instances for a particular todo list	
	EAgnApiCmdFetchInstance,				// fetch an instance
	EAgnApiCmdDeleteInstance,				// delete one or more related instances 
	EAgnApiCmdUpdateInstance,				// update one or more related instances
	EAgnApiCmdCutInstance,					// cut one or more related instances
	EAgnApiCmdFindNextDayWithInstance,		// find the next day that contains an instance
	EAgnApiCmdFindPreviousDayWithInstance,	// find the previous day that contains an instance
	EAgnApiCmdCalculateInstances			// find the instance dates a repeat repeats on
	};

#endif