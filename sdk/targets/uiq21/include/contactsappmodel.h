// CCONTACTSAPPMODEL.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#ifndef __CONTACTSAPPMODEL_H__
#define __CONTACTSAPPMODEL_H__

#include "CmDefs.h"
#include <CntDb.h>
#include <BaDesCa.h>
#include <cmmobs.h>			// MContactsAppModelObserver
#include <cntviewbase.h>	// MContactViewObserver
#include <phbksync.h>		// RPhoneBookSession

enum TModelState
	{
	EModelNoDatabase=-1,
	EModelNormal,
	EModelQuickFinding,
	EModelFinding,
	EModelFound,
	EModelNotReady,
	EModelFiltered
	};

class CEikonEnv;
class CContactsAppCache;
class CContactTemplate;
class CContactItemFieldSet;
class MContactsAppModelObserver;
class CContactNamedRemoteView;
class CContactGroupView;
class CContactFilteredView;

class TContactAppModelGroup
	{
public:
	enum TType
		{
		EAllGroups,
		ENoGroup,	// Unfiled
		EInGroup,
		EInPhonebookGroup // SIM contacts belong to a special group
		};
public:
	IMPORT_C TContactAppModelGroup(TType aType, TContactItemId aGroupId = KNullContactId);
private:
	TContactAppModelGroup();
public:
	TType iType;
	TContactItemId iGroupId;
	};


class CContactsAppModel : public CBase, public MContactDbObserver, public MContactViewObserver
	{
public: // creation and destruction
	IMPORT_C static CContactsAppModel* NewL(MContactsAppModelObserver& aObserver);
	IMPORT_C TSortBy InitializeDatabaseL();
	IMPORT_C virtual ~CContactsAppModel();

public:
	IMPORT_C TSortBy SortOrder() const;
	IMPORT_C void SetSortOrderL(TSortBy aSortBy);
	IMPORT_C void CreateSortedByTextL(TDes& aBuffer, TSortBy aSortBy) const;
	IMPORT_C TBool GetSortByUids(TSortBy aSortBy, TUid& aFirstUid, TUid& aSecondUid) const; 
	IMPORT_C TBool GetSortByUids(TSortBy aSortBy, TUid& aFirstUid, TUid& aSecondUid, TUid& aFallbackUid) const;

public: // column state (show phone number or not)
	IMPORT_C void SetColumnState(TColumnState aColumnState);
	IMPORT_C TColumnState ColumnState() const;

public: // delete and undo delete
	IMPORT_C void DeleteCurrentContactWithUndoL();
	IMPORT_C void DeleteContactL(TContactItemId aContactId);
	IMPORT_C void DeleteAllContactsL();
	IMPORT_C TBool CanUndoDelete() const;
	IMPORT_C void UndoDeleteL();

public: // contact iteration and data retrieval
	IMPORT_C TInt Count() const;
	IMPORT_C TPtrC ContactNameL(TInt aIndex) const;
	IMPORT_C CContactItem* ContactItemLC(TInt aIndex) const;	// Caller takes ownership

public:	// current contact management and data retrieval
	IMPORT_C TBool SetCurrentContactByIndexL(TInt aIndex);
	IMPORT_C void SetCurrentContactByIdL(TContactItemId aId);
	IMPORT_C TInt CurrentContactIndex() const;
	IMPORT_C TContactItemId CurrentContactId() const;
	IMPORT_C CContactItem* CurrentContactItemL() const;	// Does NOT transfer object ownership to caller
	IMPORT_C void CurrentContactNameL(TDes& aBuffer) const;
	IMPORT_C TContactItemId ContactIdL(TInt aIndex) const;

public:	// new or change contact
	IMPORT_C CContactTemplate& DefaultTemplateL() const;
	IMPORT_C TBool CreateNewEntryL();
	IMPORT_C void UpdateCurrentContactL();

public:
	IMPORT_C MContactsAppModelObserver& ModelObserver() const;
	IMPORT_C void SetModelObserver(MContactsAppModelObserver& aObserver);
	IMPORT_C void SetCurrentContactAsOwnCardL();
	IMPORT_C TContactItemId OwnCardId() const;
	
public: // model category (group) support
	IMPORT_C void SetDefaultGroup(TContactItemId aDefaultGroup);	// default group of new contacts
	IMPORT_C CContactGroup* ContactGroupLC(TContactItemId aGroupId) const;	// Caller takes ownership

public: // group used for filtering	in list view
	IMPORT_C void SetCurrentGroupL(TContactAppModelGroup aGroup);
	IMPORT_C TContactAppModelGroup CurrentGroup() const;
	
public: // group of current contact	
	IMPORT_C void MoveCurrentContactToGroupL(TContactItemId aGroupId);
	IMPORT_C TContactItemId GroupOfCurrentContactL() const;
	
public: // find
	IMPORT_C void FindInAllTextL(const TFindString& aString, MContactsAppModelObserver& aFindObserver);
	IMPORT_C void QuickFindL(const TFindString& aString, MContactsAppModelObserver& aFindObserver);
	IMPORT_C void CancelFindL();
	IMPORT_C TFindString FindString() const;

public: // filter
	IMPORT_C void FilterL(CContactDatabase::TContactViewFilter aFilter, MContactsAppModelObserver& aFilterObserver);
	IMPORT_C void CancelFilterL();

public: // clipboard
	IMPORT_C TBool PasteFromStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary);
	IMPORT_C TBool PasteFromClipboardL();
	IMPORT_C void CopyCurrentContactToStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary,TInt aOptions);
	IMPORT_C void CopyCurrentContactToClipboardL();
	IMPORT_C void CutCurrentContactL();

public:
	IMPORT_C TBool ExportContactsL(RWriteStream& aWriteStream, TInt aOptions, TBool aExportPrivateFields=ETrue) const; // only exports current contact
	IMPORT_C TBool ExportContactsInGroupL(RWriteStream& aWriteStream, TInt aOptions, TBool aExportPrivateFields=ETrue) const; 
	IMPORT_C TBool ImportContactsL(RReadStream& aReadStream, TInt aOptions); // can handle several contacts

public: // database state and access
	IMPORT_C CContactDatabase& Database() const;
	IMPORT_C TModelState ModelState() const;
	IMPORT_C TBool CompressDatabaseL();
	IMPORT_C void ChangeDatabaseDriveL(const TDriveUnit& aNewDrive,TBool aCopy);

public: // misc
	IMPORT_C static void GetFieldContentAsTPtr(const CContactItemField& aField, TPtrC& aPtr);

public:
	TContactItemId GetContactNameAtIndexL(TInt aIndex, TDes& aBuffer);

public:
	IMPORT_C TBool InitializePhonebookL();
	IMPORT_C TContactItemId PhonebookGroupIdL();
	IMPORT_C TInt ContactIndexFromPhonebookSlotNumberL(TInt aSlot) const;
	IMPORT_C TInt NumberOfEmptyPhonebookSlotsL();
	IMPORT_C void GetEmptyPhonebookSlotsL(RArray<TInt>& aFreeSlots) const;
	IMPORT_C TBool CreateNewICCEntryL();
	IMPORT_C TBool IsPhonebookSynchronised() const;
	IMPORT_C TBool IsPhonebookCurrentView() const;
	IMPORT_C TBool IsRingToneCurrentView() const;
	IMPORT_C TInt PhonebookNameFieldLength();
	IMPORT_C TInt PhonebookNumberFieldLength();
	//Send multiple contacts.
	IMPORT_C TBool ExportMultipleContactsL(RWriteStream& aWriteStream, const CContactIdArray& aContactIdArray, TInt aOptions, TBool aExportPrivateFields=ETrue) const; //exports multiple contacts
	IMPORT_C CContactItem* EntryFromClipboardL();
	IMPORT_C TInt CurrentFilter();
	
	IMPORT_C CContactIdArray* NamedRemoteDbViewIdArrayL();


private:
	CContactTemplate& ICCTemplateL();
	TInt NumberOfPhonebookSlotsL();

private: // new functionality
	void HandleContactViewEvent(const CContactViewBase& aView,const TContactViewEvent& aEvent); // From MContactViewObserver
	void DoHandleContactViewEventL(const CContactViewBase& aView,const TContactViewEvent& aEvent);
private:
	void SaveContactL(RWriteStream& aWriteStream, TInt aOptions, TBool aExportPrivateFields=ETrue) const;	
	void SetNameOrPhoneNumberL(CContactItem& aItem,const TUid aType,const TDesC& aName);
private: 
	CContactsAppModel(MContactsAppModelObserver& aObserver); 
	void ConstructL();
	void HandleModelChangeL(TInt aFlags, TInt aLastActionedContactIndex); // notifies the modelobserver, if ignorechanged isn't true
	CContactTextDef* CreateTextDefLC(TSortBy aSortBy) const;
	TSortBy SortOrder(const RContactViewSortOrder& aViewSortOrder) const;
	void InitViewSortOrderL(TSortBy aSortOrder, RContactViewSortOrder& aViewSortOrder) const;
	void StoreCurrentContactAsTextL(CStreamStore& aStore,CStreamDictionary& aDictionary);
	void DoHandleDatabaseEventL(TContactDbObserverEvent aEvent);
	void WriteSortOrderToIniFileL(TSortBy aSortOrder) const;
	TSortBy ReadSortOrderFromIniFileL() const;
private: // from MContactDbObserver
	virtual void HandleDatabaseEventL(TContactDbObserverEvent aEvent);
private:
	enum TDbLockFlags
		{
		ETablesClosed	= 0x01,
		EInRollBack		= 0x02,
		ECompressingFile= 0x04,
		ERepairingFile	= 0x08,
		EChangingDrive	= 0x10,
		};

	enum TModelInternalState
		{
		EReady			 = 0x00,
		EUpdatingContact = 0x01
		};
//Used for storing status of phbksync
	enum TPhonebookSyncState
		{
		EPhonebookUnsynchronised= 0x00,
		EPhonebookSynchronised	= 0x01,
		EPhonebookNotAvailable	= 0x02
		};

private:
	CContactViewBase* iCurrentDbView;
	CContactNamedRemoteView* iNamedRemoteDbView;
	CContactGroupView* iGroupDbView;
	CContactViewBase* iFindDbView;
	CDesCArrayFlat* iFindWordsArray;
	MContactsAppModelObserver* iFindObserver;
	CContactFilteredView* iFilteredDbView;
	MContactsAppModelObserver* iFilterObserver;
	TModelInternalState iModelInternalState;
private:	
	MContactsAppModelObserver* iModelObserver;
	CContactChangeNotifier* iChangeNotifier; 
	CContactsAppCache* iContactsCache;
	CContactDatabase* iDatabase;
	mutable CContactTemplate* iDefaultTemplate;
	CContactTextDef* iNormalTextDef;
	CContactItem* iCurrentContactItem;
	CContactItem* iUndoBuffer;
	TContactItemId iUndoGroup;
	TContactAppModelGroup iCurrentGroup;
	TContactItemId iDefaultGroup;
	TBool iPasteGroup;
	TModelState iModelState;
	TFindString iFindString;
	TColumnState iColumns;
	TSortBy iSortBy;
	mutable TInt iCurrentContactIndex;
	TInt iResourceHandle;
	TInt iDatabaseCount;
	HBufC* iCloseText;
	CEikonEnv& iEnv;
	TBool iNewContactPending;
	TContactItemId iGroupIdOfPendingNewContact;
	TContactItemId iLastActionedContactId;
	CContactDatabase::TContactViewFilter iCurrentFilter;

	//data required for SIM phonebook support
	CContactLocalView* iPhonebookDbView;
	TContactItemId iPhonebookGroupId;
	CContactTemplate* iIccTemplate;	
	TPhonebookSyncState iPhonebookSyncState;
	TInt iTotalPhonebookSlots;
	TInt iPhonebookNameFieldLength;
	TInt iPhonebookNumberFieldLength;
	RPhoneBookSession iPhonebookSession;
	};

#endif // __CONTACTSAPPMODEL_H__

