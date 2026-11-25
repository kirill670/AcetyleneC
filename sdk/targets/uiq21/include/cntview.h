// CNTVIEW.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTVIEW_H__
#define __CNTVIEW_H__

#include <cntviewbase.h>

const TInt KMaxBoundaryMatchLength=8;

/**
 * This class gives a view representation of a group.
 * All contacts belonging to the group will be displayed. The view uses an 
 * underlying view to retrieve the contacts that belong to the group. TGroupType 
 * defines whether the view displays all contacts belonging to the group or all 
 * contacts that are not part of this group.
 */
class CContactGroupView: public CContactViewBase, public MContactViewObserver
	{
friend class CGroupViewTester;
public:
	enum TGroupType
		{
		EShowContactsInGroup,
		EShowContactsNotInGroup,
		EShowContactsNotInAnyGroup
		};
public:
	IMPORT_C static CContactGroupView* NewL(const CContactDatabase& aDb,CContactViewBase& aView,MContactViewObserver& aObserver,const TContactItemId aGroupId,const TGroupType aGroupType);
	IMPORT_C static CContactGroupView* NewL(const CContactDatabase& aDb,CContactViewBase& aView,MContactViewObserver& aObserver, const TDesC& aGroupName,const TGroupType aGroupType);
	~CContactGroupView();
public: // From CContactViewBase
	TContactItemId AtL(TInt aIndex) const;
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const CViewContact& ContactAtL(TInt aIndex) const;
	TContactViewPreferences ContactViewPreferences();
	const RContactViewSortOrder& SortOrderL() const;
protected:
	IMPORT_C virtual void UpdateGroupViewL();
private: // From MContactViewObserver.
	void HandleContactViewEvent(const CContactViewBase& aView,const TContactViewEvent& aEvent);
private: 
	void ConstructL(MContactViewObserver& aObserver,TContactItemId aGroupId);
	void UpdateForContactsInGroupL();
	void UpdateForContactsNotInThisGroupL();
	void UpdateForUnfiledContactsL();
	void UpdateForContactListL(const CContactIdArray* aArray);
	TContactItemId GetGroupIdbyNameL(const TDesC& aGroupName);
	TBool HandleRemoveEventL(const TContactViewEvent& aEvent);
	TBool HandleAddEventL(const TContactViewEvent& aEvent);
	TBool HandleAddEventForUnfiledContactsL(const TContactViewEvent& aEvent );
	static TInt CompareMappingsL(const TContactIdWithMapping& aFirst,const TContactIdWithMapping& aSecond);
	TInt static CompareIndexesAllowingDuplicates(const TContactIdWithMapping& aFirst, const TContactIdWithMapping& aSecond);
private:
	CContactGroupView(const CContactDatabase& aDb,CContactViewBase& aView,TGroupType aGroupType);
	void UpdateMappingsL();
private:
	RArray<TContactIdWithMapping> iGroupContacts;
	TContactItemId iGroupId;
	CContactViewBase& iView;
	TGroupType iGroupType;
	};


/** 
 * The CContactFindView class provides the functionality to create a view
 * based on a find criteria. The criteria is based on a MDesCArray - only 
 * contacts matching this criteria will be in this view. The only fields 
 * included in the search are only the fields that have been used in the 
 * underlying view's sort. (usually firstname, lastname & company name).
 */
class CContactFindView: public CContactViewBase, public MContactViewObserver
	{
public:
	IMPORT_C static CContactFindView* NewL(const CContactDatabase& aDb,CContactViewBase& aView,MContactViewObserver& aObserver,MDesCArray* aFindWords);
	IMPORT_C static CContactFindView* NewL(const CContactDatabase& aDb,CContactViewBase& aView,MContactViewObserver& aObserver,MDesCArray* aFindWords, TSearchType aSearchType);
	~CContactFindView();
public: // From CContactViewBase
	TContactItemId AtL(TInt aIndex) const;
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const CViewContact& ContactAtL(TInt aIndex) const;
	TContactViewPreferences ContactViewPreferences();
	const RContactViewSortOrder& SortOrderL() const;
protected:
	IMPORT_C virtual void UpdateFindViewL();
public:
	IMPORT_C void RefineFindViewL(MDesCArray* aFindWords);
private: // From MContactViewObserver.
	virtual void HandleContactViewEvent(const CContactViewBase& aView,const TContactViewEvent& aEvent);
private: 
	void ConstructL(MContactViewObserver& aObserver,MDesCArray* aFindWords);
	void DeleteFindContacts();
	void TightenFindViewCriteriaL();
	void HandleRemoveEventL(const TContactViewEvent& aEvent);
	void HandleAddEventL(const TContactViewEvent& aEvent);
	void CopyNewFindWordsL(MDesCArray* aFindWords);
	void DestroyFindWordsArray();
private:
	CContactFindView(const CContactDatabase& aDb,CContactViewBase& aView, TSearchType aSearchType);
private:
	RPointerArray<CViewContact> iFindContacts;
	CPtrCArray* iFindWords;
	CContactViewBase& iView;
	const TSearchType iSearchType;
	};


/** 
 * The CContactFilteredView class provides a filtered view over an existing
 * CContactViewBase derived object. For example, a view containing only those
 * contacts that have an email address. For efficiency reasons there are a finite
 * set of filters available (defined in CContactDatabase::TContactViewFilter)
 */
class CContactFilteredView : public CContactViewBase, public MContactViewObserver
	{
public:
	IMPORT_C static CContactFilteredView* NewL(MContactViewObserver& aObserver,const CContactDatabase& aDb,CContactViewBase& aView,TInt aFilter);
public: // From CContactViewBase.
	TContactItemId AtL(TInt aIndex) const;
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const CViewContact& ContactAtL(TInt aIndex) const;
	TContactViewPreferences ContactViewPreferences();
	const RContactViewSortOrder& SortOrderL() const;
	virtual void ContactsMatchingCriteriaL(const MDesCArray& aFindWords,RPointerArray<CViewContact>& aMatchedContacts);
	virtual void ContactsMatchingPrefixL(const MDesCArray& aFindWords, RPointerArray<CViewContact>& aMatchedContacts);
private: // From MContactViewObserver.
	virtual void HandleContactViewEvent(const CContactViewBase& aView,const TContactViewEvent& aEvent);
private:
//ChrisD: why private d'tor
	~CContactFilteredView();
	CContactFilteredView(const CContactDatabase& aDb,TInt aFilter,CContactViewBase& aView);
	void ConstructL(MContactViewObserver& aObserver);
	void CreateFilteredIdArrayL();
	void UpdateFilteredIdArrayL(TContactViewEvent& aEvent, TBool& aViewModified);
	void HandleAddEventL(TContactViewEvent& aEvent, TBool& aViewModified);
	void HandleRemoveEventL(TContactViewEvent& aEvent, TBool& aViewModified);
	TInt BinaryInsertL(TContactIdWithMapping aId);
	static TInt FilterCallBack(TAny* aSelf);
	static TBool CompareMappings(const TContactIdWithMapping& aFirst,const TContactIdWithMapping& aSecond);
	void FilterResultsArray(RPointerArray<CViewContact>& aMatchedContacts);
	TInt DoFilterIncrementL();
	void UpdateMappingsL();
private:
	const TInt iFilter;
	CContactViewBase& iView;
	RArray<TContactIdWithMapping> iFilteredIdArray;
	CIdle* iIdleFilterer;
	TInt iCurrentPositionInIdArray;
	};


/** 
 * The abstract base class of all sub-view range classes
 */
class CContactViewRangeBase : public CBase
	{
public:
	enum TCriteria
		{
		ELessThan,
		ELessThanOrEqualTo,
		EGreaterThan,
		EGreaterThanOrEqualTo
		};
public:
	~CContactViewRangeBase();
	inline TInt LowIndex() const;
	inline TInt HighIndex() const;
	virtual void SetL()=0;
	IMPORT_C TBool IndicesValid() const;
protected:
	CContactViewRangeBase(const CContactViewBase& aView);
	void ConstructL();
	TInt FindIndexL(const TDesC& aMatch,TCriteria aCriteria) const;
	TBool MatchesCriteriaL(TCriteria aCriteria,const TDesC& aMatch,TInt aIndex) const;
	void ValidateIndices();
protected:
	const CContactViewBase& iView;
	TInt iLow;
	TInt iHigh;
	//ChrisD: contain by value not ptr
	TCollationMethod* iCollateMethod;
	};


/** 
 * The CContactLocalView class provides an instantiable sub-view range
 */
class CContactViewRange : public CContactViewRangeBase
	{
public:
	~CContactViewRange();
	IMPORT_C static CContactViewRange* NewL(const CContactViewBase& aView,const TDesC& aLowMatch,TCriteria aLowCriteria,const TDesC& aHighMatch,TCriteria aHighCriteria);
private: // From CContactViewRangeBase.
	void SetL();
private:
	CContactViewRange(const CContactViewBase& aView,const TDesC& aLowMatch,TCriteria aLowCriteria,const TDesC& aHighMatch,TCriteria aHighCriteria);
	void ConstructL();
private:
	TBuf<KMaxBoundaryMatchLength> iLowMatch;
	TCriteria iLowCriteria;
	TBuf<KMaxBoundaryMatchLength> iHighMatch;
	TCriteria iHighCriteria;
	};


/** 
 * Specifies a lower limit for the sub-view range
 */
class CContactViewLowRange : public CContactViewRangeBase
	{
public:
	IMPORT_C static CContactViewLowRange* NewL(const CContactViewBase& aView,const TDesC& aMatch,TCriteria aCriteria);
private: // From CContactViewRangeBase.
	void SetL();
private:
	CContactViewLowRange(const CContactViewBase& aView,const TDesC& aMatch,TCriteria aCriteria);
//ChrisD: why private d'tor
	~CContactViewLowRange();
private:
	TBuf<KMaxBoundaryMatchLength> iMatch;
	TCriteria iCriteria;
	};


/** 
 * Specifies an upper limit for the sub-view range
 */
class CContactViewHighRange : public CContactViewRangeBase
	{
public:
	IMPORT_C static CContactViewHighRange* NewL(const CContactViewBase& aView,const TDesC& aMatch,TCriteria aCriteria);
private: // From CContactViewRangeBase.
	void SetL();
private:
	CContactViewHighRange(const CContactViewBase& aView,const TDesC& aMatch,TCriteria aCriteria);
//ChrisD: why private d'tor
	~CContactViewHighRange();
private:
	TBuf<KMaxBoundaryMatchLength> iMatch;
	TCriteria iCriteria;
	};


/** 
 * Objects of this class present a 'window' of data over a (potentially) larger 
 * data set contained in an underlying CContactViewBase object. For example, 
 * a view containing only those contacts whose name is greater than or equal 
 * to 'a' and less than 'd'). As the underlying data is modified, objects of
 * this class will keep themselves up to date.
 */
class CContactSubView : public CContactViewBase, public MContactViewObserver
	{
public:
	IMPORT_C static CContactSubView* NewL(MContactViewObserver& aObserver,const CContactDatabase& aDb,CContactViewBase& aView,const TDesC& aBoundary);//>= > is infinity <= < =0;
	IMPORT_C static CContactSubView* NewL(MContactViewObserver& aObserver,const CContactDatabase& aDb,CContactViewBase& aView,const TDesC& aLowBoundary,const TDesC& aHighBoundary);
public: // From CContactViewBase.
	TContactItemId AtL(TInt aIndex) const;
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const CViewContact& ContactAtL(TInt aIndex) const;
	TContactViewPreferences ContactViewPreferences();
	const RContactViewSortOrder& SortOrderL() const;
private: // From MContactViewObserver.
	virtual void HandleContactViewEvent(const CContactViewBase& aView,const TContactViewEvent& aEvent);
private:
//ChrisD: why private d'tor
	~CContactSubView();
	CContactSubView(const CContactDatabase& aDb,CContactViewBase& aView);
	CContactSubView(const CContactDatabase& aDb,const CContactSubView& aView);
	void CommonConstructL(MContactViewObserver& aObserver);
	void ConstructL(MContactViewObserver& aObserver,const TDesC& aBoundary);
	void ConstructL(MContactViewObserver& aObserver,const CContactSubView& aView);
	void ConstructL(MContactViewObserver& aObserver,const CContactSubView& aView,const TDesC& aBoundary);
	void ConstructL(MContactViewObserver& aObserver,const TDesC& aLowBoundary,const TDesC& aHighBoundary);
	CContactViewRangeBase::TCriteria DecodeBoundary(TDes& aBoundary) const;
	TInt MapToUnderlyingViewIndex(TInt aSubViewIndex) const;
	TInt MapToSubViewIndex(TInt aUnderlyingViewIndex) const;
private:
	CContactViewBase& iView;
	CContactViewRangeBase* iRange;
	};


/** 
 * Objects of this class may be used to concatenate multiple CContactViewBase objects
 * into a single contiguous view. The component views will be ordered according to the
 * order of the array passed into the constructor.
 */
class CContactConcatenatedView : public CContactViewBase, public MContactViewObserver
	{
public:
	IMPORT_C static CContactConcatenatedView* NewL(MContactViewObserver& aObserver,const CContactDatabase& aDb,RPointerArray<CContactViewBase>& aComponentViews);
public: // From CContactViewBase.
	TContactItemId AtL(TInt aIndex) const;
	TInt CountL() const;
	TInt FindL(TContactItemId aId) const;
	HBufC* AllFieldsLC(TInt aIndex,const TDesC& aSeparator) const;
	const CViewContact& ContactAtL(TInt aIndex) const;
	TContactViewPreferences ContactViewPreferences();
	const RContactViewSortOrder& SortOrderL() const;
private: // From MContactViewObserver.
	virtual void HandleContactViewEvent(const CContactViewBase& aView,const TContactViewEvent& aEvent);
private:
	struct TComponentView
		{
		TComponentView(CContactViewBase& aView,TState aState);
		CContactViewBase& iView;
		TState iState;
		};
private:
	~CContactConcatenatedView();
	CContactConcatenatedView(const CContactDatabase& aDb);
	void ConstructL(MContactViewObserver& aObserver,RPointerArray<CContactViewBase>& aComponentViews);
	void CopyComponentViewsL(RPointerArray<CContactViewBase>& aComponentViews);
	void OpenComponentViewsL();
	void CloseComponentViews();
	TBool ComponentViewsReady();
	void SetComponentViewReady(const CContactViewBase& aView);
	TInt OffsetL(const CContactViewBase& aView);
	static TBool ComponentViewsEqual(const TComponentView& aFirst,const TComponentView& aSecond);
	TInt FindComponentView(const CContactViewBase& aView);
private:
	RArray<TComponentView> iComponentView;
	};


inline TInt CContactViewRangeBase::LowIndex() const { return iLow; }
inline TInt CContactViewRangeBase::HighIndex() const { return iHigh; }

#endif
