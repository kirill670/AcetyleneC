// CNTVIEWBASE.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTVIEWBASE_H__
#define __CNTVIEWBASE_H__

#include <e32std.h>
#include <s32mem.h>
#include <cntdb.h>

class CContactViewBase;
class CContactRemoteViewNotifier;
class CIdleContactSorter;

/** 
 * Specifies the view preferences.
 * The type of contact items to sort and the behaviour for items which don't have
 * field content for the view sort order fields can be specified.
 * 
 * The default item type includes contacts only. The default behaviour for 
 * contacts without content for the sort order fields is to sort them using the 
 * first field with text set. EUnSortedAtBeginning and EUnSortedAtEnd places the 
 * unsorted contacts at the end of the sorted list. EIgnoreUnSorted excludes 
 * contacts which don't have data for the fields specified in the sort order.
 * If ESingleWhiteSpaceIsEmptyField is specified fields containing a single 
 * white space are treated as empty fields.
 */
enum TContactViewPreferences
	{
	EContactsOnly					=0x00000000, //View contains sorted contacts only (default)
	EGroupsOnly						=0x00000001, //View contains sorted groups only 
	EContactAndGroups				=0x00000002, //View contains sorted contacts + groups
	EIgnoreUnSorted					=0x00000004, //Contacts that don't have sort fields are not put in view
	EUnSortedAtBeginning			=0x00000008, //Contacts that don't have sort fields are put at the beginning of a view
	EUnSortedAtEnd					=0x00000010, //Contacts that don't have sort fields are put at the end of a view
	ESingleWhiteSpaceIsEmptyField	=0x00000020,
	EICCEntriesOnly					=0x00000040, //View contains sorted ICC entries only
	EICCEntriesAndContacts			=0x00000080  //View contains sorted ICC entries and contacts
	};


/** 
 * Specifies events that may be raised by a contact view.
 */
class TContactViewEvent
	{
public:
	enum TEventType
		{
		EUnavailable,
		EReady,
		ESortOrderChanged,
		ESortError,
		EServerError,
		EIndexingError,
		EItemAdded,
		EItemRemoved,
		EGroupChanged
		};
public:
	inline TContactViewEvent();
	inline TContactViewEvent(TEventType aEventType,TInt aInt = KErrUnknown,TContactItemId aContactId = KErrUnknown); 
public:
	TEventType iEventType;
	TInt iInt; //returns error code or contact id
	TContactItemId iContactId;//ContactId that has been added / removed if relevant.
	};


/** A contact and a mapping */
struct TContactIdWithMapping
	{
	TContactItemId iId;
	TInt iMapping;
	};


/** 
 * Specifies the mixin protocol for the view observer. 
 * It should be inherited by classes which use contact views.
 */
class MContactViewObserver
	{
public:
	virtual void HandleContactViewEvent(const CContactViewBase& aView,const TContactViewEvent& aEvent)=0;
	};


/** Specifies a sort order for a contact view */
class RContactViewSortOrder
	{
public:
	IMPORT_C RContactViewSortOrder();
	IMPORT_C void Close();
	IMPORT_C void CopyL(const RContactViewSortOrder& aSortOrder);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TInt ExternalizedSize() const;
	IMPORT_C TBool operator==(const RContactViewSortOrder& aSortOrder) const;
	inline void AppendL(TFieldType aField);
	inline TFieldType operator[](TInt aIndex) const;
	inline TInt Count() const; 
private:
	RArray<TFieldType> iFields;
	TInt iSpare;
	};


/**
 * Minimal representation of a contact used by views.
 * Contains the fields that have been defined by the sort order.
 */
class CViewContact : public CBase
	{
public:
	enum TViewContactType{EContactItem,EGroup};
	IMPORT_C CViewContact(TContactItemId aId);
	IMPORT_C static CViewContact* NewL(const CViewContact& aContact);
	IMPORT_C ~CViewContact();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TInt ExternalizedSize() const;
	IMPORT_C TInt FieldCount() const;
	IMPORT_C TPtrC Field(TInt aPosition) const;
	IMPORT_C TBool ContactMatchesFilter(TInt aFilter) const;
	inline TInt ContactHint() const;
	inline TContactItemId Id() const;
	inline TViewContactType ContactType() const;
public:
	void AddFieldL(const TDesC& aField);
	inline void SetId(TContactItemId aId);
	inline void SetContactType(CViewContact::TViewContactType aContactType);
	inline void SetContactHint(TInt aHint);
	static TBool HintFieldMatchesFilter(TInt aHintField, TInt aFilter);
private:
	void ConstructL(const CViewContact &aContact);
	friend class CContactViewBase;
private:
	TContactItemId iId;
	TViewContactType iContactType;
    HBufC* iFieldTextBuf;
	RArray<TInt> iTextIndexes;
	TInt iHintBitField;
	};


/**
 * The abstract base class of all contact view classes. The view classes provide 
 * users of the contact database with a simple means of presenting views on 
 * sorted contact data. 
 * 
 * All contact views are asynchronous in operation, and as such users of 
 * the view must 'observe' the view via a mixin interface. Immediately after 
 * construction views will not be in a usable state (the underlying data may be 
 * being sorted, for example). Only after the observer has received a 'ready' 
 * notification may the view be used. 
 * 
 * There are two main types of contact view - local views and remote views. The
 * data associated with local views are allocated within the client's memory space.
 * Remote view data is allocated within the memory space of the contacts server
 * 
 * A view can be named or un-named. An un-named view has a fixed sort order - the 
 * only way to change this is by closing the object and creating a new one with a 
 * different order. Named views may have their sort order changed. When this is 
 * done, first all observers will be informed that the view is 'unavailable'. This
 * notification will be followed by 'sort order changed' and 'ready'. Only once 
 * the 'ready' notification has been received may the view be used again.
 */
class CContactViewBase : public CBase
	{
public:
	enum TSearchType
		{
		EFullSearch,
		EPrefixSearch
		};

protected:
	enum TState
		{
		EInitializing,
		EReady,
		ENotReady
		};
public:
	IMPORT_C void OpenL(MContactViewObserver& aObserver);
	IMPORT_C TInt Open(MContactViewObserver& aObserver);
	IMPORT_C TBool Close(const MContactViewObserver& aObserver);
	virtual TContactItemId AtL(TInt aIndex) const=0;
	virtual const CViewContact& ContactAtL(TInt aIndex) const =0;
	virtual TInt CountL() const=0;
	virtual TInt FindL(TContactItemId aId) const=0;
	virtual HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const=0;
	IMPORT_C virtual void ContactsMatchingCriteriaL(const MDesCArray& aFindWords,RPointerArray<CViewContact>& aMatchedContacts);
	virtual TContactViewPreferences ContactViewPreferences()=0;
	virtual const RContactViewSortOrder& SortOrderL() const = 0;
	IMPORT_C virtual void ContactsMatchingPrefixL(const MDesCArray& aFindWords, RPointerArray<CViewContact>& aMatchedContacts);
	IMPORT_C virtual void GetContactIdsL(const CArrayFix<TInt>& aIndexes, CContactIdArray& aContactIds);
protected:
	IMPORT_C ~CContactViewBase();
	IMPORT_C void ConstructL();

	IMPORT_C CContactViewBase(const CContactDatabase& aDb);
	IMPORT_C void NotifyObservers(const TContactViewEvent& aEvent);
	IMPORT_C TInt NotifyObserverAsync(MContactViewObserver& aObserver,const TContactViewEvent& aEvent);
	IMPORT_C static TBool IdsMatch(const CViewContact& aFirst,const CViewContact& aSecond);
	IMPORT_C HBufC* FieldsWithSeparatorLC(const RPointerArray<CViewContact>& aContacts,TInt aIndex,const TDesC& aSeparator) const;
	//Find helper functions
	IMPORT_C virtual TBool MatchesCriteriaL(const CViewContact& aContact,const MDesCArray& aFindWords);
	IMPORT_C static TBool MatchesCriteriaL(const CViewContact& aContact,const MDesCArray& aFindWords, TSearchType aSearchType);
	IMPORT_C static TBool IdsEqual(const TContactIdWithMapping& aFirst,const TContactIdWithMapping& aSecond);
	IMPORT_C static TBool IndexesEqual(const TContactIdWithMapping& aFirst,const TContactIdWithMapping& aSecond);
	IMPORT_C static TInt CompareFieldsL(const CViewContact& aFirst, const CViewContact& aSecond);
private:
	static TInt AsyncNotifyCallBack(TAny* aSelf);
	static CDesCArrayFlat* CreateFindWordArrayLC(const MDesCArray& aFindWords, TSearchType aSearchType);
	static TBool ContactMatchesCriteriaL(const CViewContact& aContact,const MDesCArray& aFindWords);
	void MatchContactsL(const MDesCArray& aFindWords,RPointerArray<CViewContact>& aMatchedContacts, TSearchType aSearchType);
	static TInt CompareFieldsWithCollationLevel(const CViewContact& aFirst, const CViewContact& aSecond, TInt aCollationLevel);
	static TInt FindFirstPopulatedFieldL( const CViewContact& aContact, TInt aOffset, TInt aMax);
private:
	struct TObserverAndEvent
		{
		TContactViewEvent iAsyncEvent;
		MContactViewObserver* iObserverToNotify;
		};
protected:
	const CContactDatabase& iDb;
	TState iState;
private:
	RPointerArray<MContactViewObserver> iObserverArray;
	CIdle* iAsyncNotifier;
protected:
	TInt iError;
private:
	RArray<TObserverAndEvent> iOutstandingNotifications;
	};


/** 
 * The CContactLocalView class provides an instantiable base class for contact views.
 * Contains an array of sorted contact data which is kept up to date by reception
 * of database events from the underlying CContactDatabase object. May be derived 
 * from if the default sorting algorithm is not suitable
 */
class CContactLocalView : public CContactViewBase, public MContactDbObserver
	{
public:
	IMPORT_C static CContactLocalView* NewL(MContactViewObserver& aObserver,const CContactDatabase& aDb,const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes);
	IMPORT_C const RContactViewSortOrder& SortOrder() const;
public: // From CContactViewBase.
	TContactItemId AtL(TInt aIndex) const;
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const CViewContact&  ContactAtL(TInt aIndex) const;
	TContactViewPreferences ContactViewPreferences();
	const RContactViewSortOrder& SortOrderL() const;
	void NotifySortError(TInt aError);
protected:
	IMPORT_C ~CContactLocalView();
	IMPORT_C CContactLocalView(const CContactDatabase& aDb,TContactViewPreferences aContactTypes);
	IMPORT_C void ConstructL(MContactViewObserver& aObserver,const RContactViewSortOrder& aSortOrder);
	IMPORT_C virtual void SortL(const RContactViewSortOrder& aSortOrder);
	IMPORT_C virtual TInt InsertL(TContactItemId aId);
	IMPORT_C virtual TInt RemoveL(TContactItemId aId);
protected:
	void SetState(TState aState);
private: // From MContactDbObserver.
	virtual void HandleDatabaseEventL(TContactDbObserverEvent aEvent);
private:
	static TInt SortCallBack(TAny* aSelf);
	TInt DoReadIncrementL();
	void HandleOutstandingEvents();
	TBool UnSortableContactL(const CViewContact* aContact,TBool& aTakesOwnership);
protected:
	RContactViewSortOrder iSortOrder ;
private:
	IMPORT_C virtual void CContactLocalView_Reserved_1();
	IMPORT_C virtual void CContactLocalView_Reserved_2();
private:
	CContactTables* iContactDbTables;
	RPointerArray<CViewContact> iContacts;
	RPointerArray<CViewContact> iUnSortedContacts;
	RArray<TContactDbObserverEvent> iOutstandingEvents;
	CIdleContactSorter* iSortIdler;
	CContactDatabase::TSortDataSource iSortDataSource; 	// Used to find where the data for the sort comes from.
	CContactTextDef* iTextDef;
	TContactViewPreferences iViewPrefrences;
	TInt iSpare;
	};

/** 
 * Handle to a contact server local view object.
 * @private
 */
class RContactRemoteView : public RSubSessionBase
	{
public:
	void OpenL(const CContactDatabase& aDb,const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes);
	void OpenL(const CContactDatabase& aDb,const TDesC& aName,const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes);
	void Close();
public: // From CContactViewBase
	TContactItemId AtL(TInt aIndex) const;
	CViewContact*  ContactAtL(TInt aIndex);
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const RContactViewSortOrder& SortOrderL();
public:	
	void ContactsMatchingCriteriaL(const MDesCArray& aFindWords,RPointerArray<CViewContact>& aMatchedContacts, TBool aPrefixSearch);
	void ChangeSortOrderL(const RContactViewSortOrder& aSortOrder);
	void GetSortOrderL(RContactViewSortOrder& aSortOrder);
	TContactViewPreferences ContactViewPreferencesL();

	void RequestViewEvent(TPckgBuf<TContactViewEvent>& aEvent,TRequestStatus& aStatus);
	TInt CancelRequestViewEvent();
	void GetContactIdsL(const CArrayFix<TInt>& aIndexes, CContactIdArray& aContactIds);
private:
	HBufC8* PackageSortOrderLC(const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes) const;
private:
	CViewContact* iContact;
	RContactViewSortOrder iSortOrder ;
	};


/** 
 * The base class of all remote contact view classes. Provides an implementation
 * of the CContactViewBase virtual abstraction for all sub-classes. Also adds
 * handling of remote view notifications to the functionality provided
 * by CContactViewBase.
 * 
 * The data associated with remote views are allocated within the memory space of the
 * contacts server. Within the server a local view object will be associated with
 * each client side remote view object. The advatange of this configuration is that multiple
 * clients can share the same server side view objects, thereby reducing the overhead
 * associated with initial sorting of the view data and keeping the it in sync with
 * the underlying data. Remote views should therefore be used when the same view is
 * likely to be needed by more than one client.
 */
class CContactRemoteViewBase : public CContactViewBase

	{
public: // From CContactViewBase.
	TContactItemId AtL(TInt aIndex) const;
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const CViewContact&  ContactAtL(TInt aIndex) const;
	TContactViewPreferences ContactViewPreferences();
	void ContactsMatchingCriteriaL(const MDesCArray& aFindWords,RPointerArray<CViewContact>& aMatchedContacts);
	void ContactsMatchingPrefixL(const MDesCArray& aFindWords, RPointerArray<CViewContact>& aMatchedContacts);
	const RContactViewSortOrder& SortOrderL() const;
	void GetContactIdsL(const CArrayFix<TInt>& aIndexes, CContactIdArray& aContactIds);
protected:
	~CContactRemoteViewBase();
	CContactRemoteViewBase(const CContactDatabase& aDb);
	void ConstructL(MContactViewObserver& aObserver);
private:
	static TInt NotifierCallBack(TAny* aSelf);
	void HandleContactViewEvent(const TContactViewEvent& aEvent);
protected:
	RContactRemoteView iView;
private:
	CContactRemoteViewNotifier* iNotifier;
	};


/** 
 * The main remote contact view class associated with a corresponding CContactLocalView
 * object within the contact server. Provides a efficient means for multiple clients
 * to share the same underlying view data.
 */
class CContactRemoteView : public CContactRemoteViewBase
	{
public:
	IMPORT_C static CContactRemoteView* NewL(MContactViewObserver& aObserver,const CContactDatabase& aDb,const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes);
	IMPORT_C void GetSortOrderL(RContactViewSortOrder& aSortOrder);
protected:
	~CContactRemoteView();
	CContactRemoteView(const CContactDatabase& aDb);
private:
	void ConstructL(MContactViewObserver& aObserver,const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes);
	};


/** 
 * This class allows clients to create CContactNamedLocalView objects inside the 
 * contact server. Once one client has done this, other clients can share it by name. 
 * It extends CContactRemoteView by providing a method for changing the sort order. 
 * All users of the named view will be notified when the sort order is changed.
 * 
 * If a client opens a named view that already exists but requests a different 
 * sort order, the client will be returned the existing view with the existing sort 
 * order. Depending on the needs of the client it may wish to resort the shared remote 
 * view
 */
class CContactNamedRemoteView : public CContactRemoteView
	{
public:
	IMPORT_C static CContactNamedRemoteView* NewL(MContactViewObserver& aObserver,const TDesC& aName,const CContactDatabase& aDb,const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes);
	IMPORT_C void ChangeSortOrderL(const RContactViewSortOrder& aSortOrder);
private:
	~CContactNamedRemoteView();
	CContactNamedRemoteView(const CContactDatabase& aDb);
	void ConstructL(MContactViewObserver& aObserver,const TDesC& aName,const RContactViewSortOrder& aSortOrder,TContactViewPreferences aContactTypes);
	};


inline TContactViewEvent::TContactViewEvent() {};
inline TContactViewEvent::TContactViewEvent(TEventType aEventType,TInt aInt,TContactItemId aContactId) : iEventType(aEventType),iInt(aInt),iContactId(aContactId) {};

inline void RContactViewSortOrder::AppendL(TFieldType aField) { User::LeaveIfError(iFields.Append(aField)); }
inline TFieldType RContactViewSortOrder::operator[](TInt aIndex) const { return iFields[aIndex]; }
inline TInt RContactViewSortOrder::Count() const { return iFields.Count(); }

inline TContactItemId CViewContact::Id() const {return iId;}
inline CViewContact::TViewContactType CViewContact::ContactType() const {return iContactType;}
inline TInt CViewContact::ContactHint() const {return iHintBitField;}
inline void CViewContact::SetId(TContactItemId aId) {iId=aId;}
inline void CViewContact::SetContactType(CViewContact::TViewContactType aContactType) {iContactType=aContactType;}
inline void CViewContact::SetContactHint(TInt aHint) {iHintBitField = aHint;}
#endif
