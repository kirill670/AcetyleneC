// APGAPLST.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#if !defined(__APGAPLST_H__)
#define __APGAPLST_H__

#if !defined(__APAID_H__)
#include <apaid.h>
#endif
#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif
#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#include <s32file.h>

// classes defined:
class CApaAppData;
class CApaAppList;
class CApaAppViewData;
//
// classes referenced:
class CApaMaskedBitmap;
class CApaAppInfoFileReader;
class TEntry;
class RFs;
//

/**
KApaMaxAppIcons

@publishedPartner
@released
*/
const TInt KApaMaxAppIcons=3;

/**
KApaIconIndexSmall

@publishedPartner
@released
*/
const TInt KApaIconIndexSmall=0;

/**
KApaIconIndexMedium

@publishedPartner
@released
*/
const TInt KApaIconIndexMedium=1;

/**
KApaIconIndexLarge

@publishedPartner
@released
*/
const TInt KApaIconIndexLarge=2;

/**
KIgnoreScreenMode

@internalTechnology
*/
const TInt KIgnoreScreenMode=-1;

/**
KVersionMajor

@internalComponent
*/
const TInt KVersionMajor = 2;

/**
KVersionMinor

@internalComponent
*/
const TInt KVersionMinor = 0;

/**
KVersionBuild

@internalComponent
*/
const TInt KVersionBuild = 1;


class CApaAppEntry : public CBase
/**
Utility class with smaller RAM footprint than TApaAppEntry

@internalComponent
*/
	{
public:
	static CApaAppEntry* NewL(const TApaAppEntry& aAppEntry);
	~CApaAppEntry();
	void Get(TApaAppEntry& aAppEntry) const;
private:
	CApaAppEntry(const TUidType& aUidType);
	void ConstructL(const TDesC& aFileName);
public:
	TUidType iUidType;
	HBufC* iFullName;
	};

class CApaAppDataExtra;
class CApaAppData : public CBase
/** Represents the data associated with a CApaApplication, such as its 
caption, capabilities and icons. This should be accessed through the Apparc Server.

@publishedAll
@deprecated
*/
	{
public:
	IMPORT_C TApaAppEntry AppEntry() const;
	inline TPtrC Caption() const;
	inline TPtrC ShortCaption() const;
	IMPORT_C CApaMaskedBitmap* Icon(TInt aIconIndex) const;
	IMPORT_C void Capability(TDes8& aCapabilityBuf)const;
	inline TBool IsPresent() const;
	// ER5
	IMPORT_C TDataTypePriority DataType(const TDataType& aDataType) const;
	// ER6
	IMPORT_C CApaMaskedBitmap* Icon(TSize aSize) const;
	IMPORT_C CArrayFixFlat<TSize>* IconSizesL() const;
	// ER6.1
	IMPORT_C CArrayPtrFlat<CApaAppViewData>* Views() const;
	IMPORT_C CDesCArray* OwnedFiles() const;
	IMPORT_C TBool CanUseScreenMode(TInt aScreenMode);
	// 7.0s
	IMPORT_C void GetIconInfo(TInt& aIconCount, TInt& aDefaultIconsUsed);
	//
	inline void Lock();
	inline void Unlock();
	void ExternalizeL(RWriteStream& aStream)const;

private:
	static CApaAppData* NewL(const TApaAppEntry& aAppEntry,const TDesC& aDefaultAppInfoFileName,RFs& aFs);
	CApaAppData(RFs& aFs);
	~CApaAppData();
	void ConstructL(const TApaAppEntry& aAppEntry,const TDesC& aDefaultAppInfoFileName,RFs& aFs);
	void InternalizeL(RReadStream& aStream);
	void GetCaptionsFromFile(RFs& aFs,HBufC *&aCaption, HBufC *&aShortCaption);
	TInt GetAifFileName (RFs& aFs, TFileName& aAifFileName, TEntry& aEntry);
	void GetIconsL(CApaAppInfoFileReader& aAppInfoFile);
	TBool UpdateAif(RFs& aFs,const TDesC& aDefaultAppInfoFileName);
	TInt GetAifData(RFs& aFs,const TDesC& aDefaultAppInfoFileName);
	TBool IsPending()const;
	void GetViewsL(CApaAppInfoFileReader& aAppInfoFile);
private:
	enum { ENotPresent, ENotPresentPendingUpdate, EPresentPendingUpdate, EIsPresent, ESuperseded };
private:
	CArrayPtrFlat<CApaMaskedBitmap>* iIcons;
	HBufC* iCaption;
	HBufC* iShortCaption;
	HBufC* iFullName;
	TInt iIsPresent; // uses enum
	TUidType iUidType;
	TInt iReferenceCount;
	CApaAppData* iNext;
	TApaAppCapabilityBuf iCapabilityBuf;
	CApaAppEntry* iSuccessor;
	TTime iAifTimeStamp;
	CArrayFixFlat<TDataTypeWithPriority> iDataTypeArray;
	CArrayPtrFlat<CApaAppViewData>* iViewDataArray;
	CApaAppDataExtra* iExtra;
 	RFs& iFs;
private:
	friend class CApaAppList;
	};



class CApaAppViewData : public CBase
/**
The CApaAppViewData class represents the data associated with an application view.

@internalComponent
*/
	{
public:
	IMPORT_C TUid Uid() const;
	inline TPtrC Caption() const;
	IMPORT_C CApaMaskedBitmap* Icon(const TSize& aSize) const;
	IMPORT_C CArrayFixFlat<TSize>* IconSizesL() const;
	IMPORT_C TInt ScreenMode() const;
public:
	~CApaAppViewData();
	static CApaAppViewData* NewLC();
	void SetUid(TUid aUid);
	void SetCaptionL(const TDesC& aCaption);
	void AddIconL(CApaMaskedBitmap* aIcon);
	void SetScreenMode(TInt aScreenMode);
private:
	CApaAppViewData();
	void ConstructL();
private:
	CArrayPtrFlat<CApaMaskedBitmap>* iIcons;
	HBufC* iCaption;
	TUid iUid;
	TInt iScreenMode;

	friend class CApaAppData;
	};


class MApaAppListObserver
/**
 The MApaAppListObserver interface allows a class to be informed when a CApaAppList is 
 updated.

 @internalComponent
*/
	{
public:
	virtual void NotifyUpdate(TInt aReason)=0;
	};


class CApaAppList : public CBase
/**
The CApaAppList class provides a list of all available applications present on a device.
Its functionality should be accessed through the Apparc Server.

@publishedAll
@deprecated 
*/
	{
public: 
	IMPORT_C static CApaAppList* NewL(RFs& aFs,CApaAppFinder* aAppFinder); // takes ownership of aAppFinder
public:
	IMPORT_C void UpdateL();
	IMPORT_C void PurgeL();
	inline void Purge();
	IMPORT_C TInt Count() const;
	IMPORT_C CApaAppData* FirstApp() const;
	IMPORT_C CApaAppData* FirstApp(TInt aScreenMode) const;
	IMPORT_C CApaAppData* NextApp(const CApaAppData* aApp) const;
	IMPORT_C CApaAppData* NextApp(const CApaAppData* aApp, TInt aScreenMode) const;
	IMPORT_C CApaAppData* AppDataByUid(TUid aAppUid) const;
	IMPORT_C TInt UpdateCounter() const;
	// ER5
	IMPORT_C TUid PreferredDataHandlerL(const TDataType& aDataType) const;
	IMPORT_C void StartIdleUpdateL();
	IMPORT_C void StartIdleUpdateL(MApaAppListObserver* aObserver);
	IMPORT_C void InitListL(MApaAppListObserver* aObserver);
	IMPORT_C TBool IsIdleUpdateComplete() const;
	//
	IMPORT_C TBool IsFirstScanComplete() const;
	IMPORT_C ~CApaAppList();

private:
	enum
		{
		EFirstScanComplete=0x01
		};

private:
	void ConstructL();
	void DeleteAppData ();
	CApaAppList(RFs& aFs,CApaAppFinder* aAppFinder);
	void UpdateNextAppL(TApaAppEntry& aAppEntry,TBool& aHasChanged);
	void AddToList( CApaAppData* aAppData );
	void SetPending(CApaAppData* aAppData);
	void SetNotFound(CApaAppData* aAppData, TBool& aHasChanged);
	static TInt IdleUpdateCallbackL(TAny* aObject);
	TInt IdleUpdateL();
	void StopIdlerL();
	void ScanComplete();

private: 
	// Persistence Layer
	void StoreL();
	void RestoreL();
	void StoreEntryL(RFileWriteStream& theWriteStream,CApaAppData* aApp);
	void DoStoreL(RFileWriteStream& aWriteStream);

private:
	RFs& iFs;
	CApaAppData* iAppData; // linked list of apps
	CApaAppFinder* iAppFinder;
	TInt iUpdateCounter;
	CPeriodic* iIdler;
	TApaAppEntry iCurrentApp;
	TInt iOldUpdateCounter;
	MApaAppListObserver* iObserver;
	TVersion iVersion;
	CApaAppData* iValidFirstAppData; //First valid app data in linked list!
	TInt iFlags;
	HBufC* iDefaultAppInfoFileName;
	};

//
// inlines
//

inline TPtrC CApaAppViewData::Caption() const
	{ return *iCaption; }

inline TPtrC CApaAppData::Caption() const
/** Gets the application's caption.

@return The application's caption. */
	{ return *iCaption; }

inline TPtrC CApaAppData::ShortCaption() const
/** Gets the application's short caption.

@return The application's short caption. */
	{ return *iShortCaption; }

inline TBool CApaAppData::IsPresent() const
/** Tests whether the application is present or not on the device.

@return True if application exists, else false. */
	{ return iIsPresent; }

inline void CApaAppData::Lock()
/** Locks the application.

This function increments a reference count that, if greater than zero, 
prevents the application from being removed from or replaced in the 
app list. This may be called any number of times, but each call to this 
function must be matched by a corresponding call to Unlock() to unlock 
the application. */
	{ ++iReferenceCount; }

inline void CApaAppData::Unlock()
/** Removes a lock from the application.

This decrements the reference count that was previously 
incremented by a call to Lock(). */
	{ --iReferenceCount; }

/**
 * Use PurgeL.
 *
 * @deprecated
 */
inline void CApaAppList::Purge()
	{	PurgeL();	}

#endif
