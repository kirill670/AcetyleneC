// JotterExternalInterface.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QJOTTEREXTERNALINTERFACE_H__
#define __QJOTTEREXTERNALINTERFACE_H__



const TUid KUidJotterApp={0x10003a70};
const TUid KUidJotterDetailView={0x10009a2d}; 
const TUid KUidJotterListView={0x10009a2e}; 

//Uid's for reading jotter files
const TUid KUidJotterJottingStore = {0x1000a48d};  
const TUid KUidJotterSketchStream = {0x10009a2f}; 
const TUid KUidJotterTextStream = {0x1000a48e};  


/**
 * DNL to detailed view in Jotter, will become obsolete if we are allowed to break BC by removing this class
 */
const TUid KUidJotterDnlDetailed={0x1000a48f};

class TJotterDnlDetailed
	{
public:
	TFileName filename; // name of jotter file to display
	};

typedef TPckgBuf<TJotterDnlDetailed> TJotterDnlDetailedBuf;

/**
* DNL to detailed view in Jotter
*/
class TJotterDnlDetailedDeletion
	{
public:
	TFileName iFilename;	// name of jotter file to display
	TInt iDeleteBehaviour;	// enum that states if we should delete the file after save or not.
	};

typedef TPckgBuf<TJotterDnlDetailedDeletion> TJotterDnlDetailedDeletionBuf;

enum TDeleteBehavior
	{
	EDontDelete,
	EDeleteOnSave,	//is represented by KDeleteOnSave ("DeleteOnSave") received by the viewer
	EAlwaysDelete,	//is represented by KAlwaysDelete ("AlwaysDelete") received by the viewer
	EOldDelete		//This is used to keep old behaviour in case TJotterDnlDetailed is used
	};

#endif
