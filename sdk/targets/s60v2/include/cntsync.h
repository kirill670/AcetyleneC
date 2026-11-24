// CNTSYNC.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTSYNC_H__
#define __CNTSYNC_H__


#include <e32base.h>
#include <cntdef.h>

class CContactICCEntry;
class MContactSynchroniser
/** 
Abstract interface for a contacts phonebook synchroniser.

It should be inherited by classes which implement the phonebook 
synchroniser API. The plug-in should have a second UID of 
0x101F4A6E (KUidContactSynchroniserDll).
@publishedPartner
@released
*/
	{
public:
	/**
	@publishedPartner
	@released
	*/
	enum TValidateOperation
		{
		ERead,		/** Check a cached ICC contact can be read */
		ESearch,	/** Check a cached ICC contact can be searched */
		EEdit		/** Check a cached ICC contact can be edited */
		};
public:
	virtual TInt ValidateContact(TValidateOperation aOp, TContactItemId aId) = 0;
	virtual TInt ValidateWriteContact(CContactICCEntry& aContactItem) = 0;
	virtual TInt DeleteContact(TContactItemId aId) = 0;
	virtual void Release() = 0;
	virtual void UpdatePostWriteL(const CContactICCEntry& aContactItem) = 0;
	virtual TContactItemId ICCTemplateIdL() = 0;
	virtual TContactItemId ICCTemplateIdL(TUid aPhonebookUid) = 0;
	virtual TContactItemId GroupIdL() = 0;
	virtual TContactItemId GroupIdL(TUid aPhonebookUid) = 0;
	virtual void NotifySyncStateChange(TRequestStatus& aStatus) = 0;
	virtual void CancelNotifyRequest() = 0;
	virtual TBool IsSynchronisedL() = 0;
private:
	IMPORT_C virtual void MContactSynchroniser_Reserved_1();
	};
	
#ifdef SYMBIAN_COREAPPS_PLUGIN_API_V2

/** The UID for the default phone book synchroniser ECom plugin interface
*/
const TUid KUidEcomCntPhBkSyncInterface = {0x102035FD};
	
class CContactSynchroniser : public CBase, public MContactSynchroniser
/** 
Abstract interface for a ECom contacts phonebook synchroniser plugin

It should be inherited by classes which implement the phonebook 
synchroniser API in a platform secured environment. The ECom plug-in interface uid is 
KUidEcomCntPhBkSyncInterface
@publishedPartner
@released
*/
	{
public:
	// From MContactSynchroniser
	virtual TInt ValidateContact(TValidateOperation aOp, TContactItemId aId) = 0;
	virtual TInt ValidateWriteContact(CContactICCEntry& aContactItem) = 0;
	virtual TInt DeleteContact(TContactItemId aId) = 0;
	virtual void Release() = 0;
	virtual void UpdatePostWriteL(const CContactICCEntry& aContactItem) = 0;
	virtual TContactItemId ICCTemplateIdL() = 0;
	virtual TContactItemId ICCTemplateIdL(TUid aPhonebookUid) = 0;
	virtual TContactItemId GroupIdL() = 0;
	virtual TContactItemId GroupIdL(TUid aPhonebookUid) = 0;
	virtual void NotifySyncStateChange(TRequestStatus& aStatus) = 0;
	virtual void CancelNotifyRequest() = 0;
	virtual TBool IsSynchronisedL() = 0;
public:
	static CContactSynchroniser* NewL();
	IMPORT_C virtual ~CContactSynchroniser();
private:
	TUid iDtor_ID_Key;
	};
#endif

#endif
