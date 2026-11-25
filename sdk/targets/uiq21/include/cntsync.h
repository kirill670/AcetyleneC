// CNTSYNC.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTSYNC_H__
#define __CNTSYNC_H__


#include <e32base.h>
#include <cntdef.h>

class CContactICCEntry;

/** 
 * Abstract interface for Contacts Phonebook Synchroniser.
 * 
 * It should be inherited by classes which implement the phonebook
 * synchroniser API. The plug-in should have a second UID of 
 * 0x101F4A6E (KUidContactSynchroniserDll).
 * 
 * @since 7.0
 */
class MContactSynchroniser
	{
public:
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
	virtual void UpdatePostWrite(const CContactICCEntry& aContactItem) = 0;
	virtual TContactItemId ICCTemplateIdL() = 0;
	virtual TContactItemId GroupIdL() = 0;
	virtual void NotifySyncStateChange(TRequestStatus& aStatus) = 0;
	virtual void CancelNotifyRequest() = 0;
	virtual TBool IsSynchronisedL() = 0;
private:
	IMPORT_C virtual void MContactSynchroniser_Reserved_1();
	};

#endif