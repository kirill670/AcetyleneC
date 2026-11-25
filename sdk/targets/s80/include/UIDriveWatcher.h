/*
* ==============================================================================
*  Name        : UIDriveWatcher.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Drive Watcher
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef __UIDRIVEWATCHER_H__
#define __UIDRIVEWATCHER_H__

#include <e32base.h>
#include <w32std.h>

/**
*  Class for monitoring Insertion or Removal of a drive.
*	
*  This class is to be used when you need to check a particular file, to see whether it is a DRM-blocked file or not.
*  Certain MIME file types (i.e. those listed in miui.rss) are blocked. This class returns true if a file is of one of those types.
*
*  @lib UiUtil.lib
*  @since ?Series90_version
*/

const TInt KDriveLetterSize = 2;

class CDriveWatcher;

// call back function for when the disk is removed/inserted in CDriveWatcher
class MDriveWatcherObserver
	{
public:
	enum TDriveWatcherEvent
		{
		EDriveWatcherEventRemoved,
		EDriveWatcherEventInserted
		};
public:
	virtual void NotifyDriveEventL(const CDriveWatcher& aWatcher, TDriveWatcherEvent aEvent)=0;
	};

// generic drive watcher, which watches for a disk being inserted/removed on a set drive
class CDriveWatcher : public CActive
	{
public:
	//construct/destruct
	IMPORT_C static CDriveWatcher* NewL(RFs& aFs);
	~CDriveWatcher();
	IMPORT_C TInt AddObserver(MDriveWatcherObserver& aObserver);
	IMPORT_C void RemoveObserver(MDriveWatcherObserver& aObserver);
	IMPORT_C void StartWatchingDriveL(const TDesC& aName = KNullDesC); // start watching the specified drive
	IMPORT_C TBool DiskPresent() const;	// returns true if disk is present
private:
	void CheckDriveL(); // checks disk space and notifies observer if necessary

	void DoCancel();
	void RunL();
private:
	//construct/destruct
	CDriveWatcher(RFs& aFs);
	void ConstructL();

private:
	RFs&			iFsSession; // not owned
	TInt			iDriveNumber; // the number of the drive to watch
	TBool			iDrivePresent; // stores whether the drive is present
	TBuf<KDriveLetterSize>	iDefaultExternalDrive; //EPrimaryExternalDrive
	RPointerArray<MDriveWatcherObserver> iObserverArray;
	};

#endif // __UIDRIVEWATCHER_H__
