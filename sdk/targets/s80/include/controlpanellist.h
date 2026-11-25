//
// ControlPanelList.h
// Copyright Psion Computers plc
//
#ifndef __CONTROLPANELLIST_H__
#define __CONTROLPANELLIST_H__

#include <e32base.h>
#include <coeaui.h>
#include <uidrivewatcher.h>

//FORWARD DECLARATIONS
class RFs;
class CGulIcon;
class RReadStream;
class RWriteStream;
class CApaSystemControlList;
class CApaScanningControlFinder;
class CApaSystemControl;
class CApaMaskedBitmap;
class CControlPanelAppUi;

const TInt KSmallIconSize=32;
const TInt KLargeIconSize=64;

const TInt KRevertAllOrdinal=2;
const TInt KRevertFactorySettingOrdinal=3;

class MControlPanelListObserver
	{
public:
	enum TControlPanelListEvent
		{
		EControlPanelListUpdated = 0
		};
	virtual void NotifyControlPanelListEventL(TControlPanelListEvent aEvent)=0;
	};
	
//! class CControlPanelList
/*!
handles creating and updating a list of control panel items
*/
class CControlPanelList : public CBase, public MDriveWatcherObserver
	{
public:
//! struct SIndexItem
	struct SIndexItem
		{
		//! TPtrC				iName
		TPtrC					iName;
		//! TInt                iRealIndex
		TInt                    iRealIndex;
		//! CApaMaskedBitmap*   iSmallIcon
		CApaMaskedBitmap*       iSmallIcon;
		//! CApaMaskedBitmap*   iLargeIcon
		CApaMaskedBitmap*       iLargeIcon;
		};
public:  // Exported
	IMPORT_C static CControlPanelList* NewL(RFs& aFs);
	IMPORT_C CGulIcon* Icon(TInt aIndex, TInt aIconSize) const;
	IMPORT_C void RunItemL(TInt aIndex);
	IMPORT_C void RevertAllL();
	IMPORT_C void RevertFactorySettingL();
	IMPORT_C void SaveItemInfoL(RWriteStream& aWriteStream,TInt aItem) const;
    IMPORT_C TInt ItemL(RReadStream& aReadStream);
    IMPORT_C TPtrC Name(TInt aIndex);
    IMPORT_C TInt Count();
	IMPORT_C TInt Lookup(TUid aUid);
	IMPORT_C CApaSystemControl* Control(TInt aIndex);
	
	IMPORT_C TInt AddObserver(MControlPanelListObserver& aObserver);
	IMPORT_C void RemoveObserver(MControlPanelListObserver& aObserver);
public:
    void RevertItemL(TInt aIndex, TInt aOrdinal);
	void NotifyDriveEventL(const CDriveWatcher& aWatcher, TDriveWatcherEvent aEvent);
    ~CControlPanelList();
private:
	CControlPanelList(RFs& aFs);
	void ConstructL();
	TInt AddControl(const TDesC& aDefaultFile, const TInt aIndex);
	void GetControlBitmapL(const TFileName& aAifFile, SIndexItem& aControlStruct, TUid aUid=KNullUid) const;
	TInt GetControlBitmap(const TFileName& aAifFile, SIndexItem& aControlStruct, TUid aUid=KNullUid) const;
	void UpdateListL();
private:
    //! RFs&                        iFs
	RFs&                            iFs;
    //! CApaScanningControlFinder*  iFinder
	CApaScanningControlFinder*      iFinder;
    //!CApaSystemControlList*       iExtraControlsList
	CApaSystemControlList*          iExtraControlsList;
	//! RArray<SIndexItem>          iIndex
    RArray<SIndexItem>              iIndex;
    //! CGulIcon*                   iIcon
	CGulIcon*                       iIcon;
    //! CDriveWatcher*              iDiskWatcher	
	CDriveWatcher*					iDiskWatcher;
    //! RPointerArray<MControlPanelListObserver> iObserverArray
	RPointerArray<MControlPanelListObserver> iObserverArray;
	};

#endif // __CONTROLPANELLIST_H__
