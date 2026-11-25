// phbksync.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** \file PHBKSYNC.H
 * Phonebook Synchroniser API header file.
 *
 * Describes the Phonebook Synchroniser API - classes, methods and types.
 */

#ifndef __PHBKSYNC_H__
#define __PHBKSYNC_H__

#include <e32std.h>
#include <cntdef.h>
#include <cntdb.h>
#include <cntitem.h>
#include <cntfldst.h>
#include <etelmm.h>

const TInt KSyncIndexNotSupplied=-1;

enum TPhonebookSyncRequestCancel
	{
	EDoSynchronisationCancelClient,
	ESyncDeleteCntFromICCCancelClient,
	ESyncWriteCntToICCCancelClient,
	ESyncNotifyCacheStateChangeCancelClient
	};

class TContactFieldFormat
	{
public:
	TContactFieldFormat(TInt aLength, TInt aCount, TBool aDisplayed);
public:
	TInt  iLength;
	TInt  iCount;
	TBool iDisplayed;
	};

/**
 * \class RPhoneBookSession PHBKSYNC.H "INC/PHBKSYNC.H"
 * \brief Provides client access to phonebook-synchroniser functionality provided by the Phonebook Synchroniser Server.
 */
class CPBSyncPtrHolder;
class RPhoneBookSession : public RSessionBase
	{
public:
	enum TPhonebookSyncMode
		{
		EAutoCurrentIcc,	// Automatic Synchronisation on start-up to any ICC
		EAutoSameIcc,		// Automatic Synchronisation only if current ICC is same as previously used
		EManual				// As selected by user
		};

	enum TSyncState
		{
		EUnsynchronised,
		ECacheValid,
		EErrorDuringSync
		};

	class TContactFieldsV1
		{
	public:
		enum TContactFieldsExtensionId
			{
			KPhBkSyncTContactFieldsV1
			};
	public:
		IMPORT_C TInt ExtensionId() const;
		IMPORT_C TContactFieldsV1();
	public:
		TContactFieldFormat iNameField;
		TContactFieldFormat iNumberField;
		TContactFieldFormat iIccSlotField;
	protected:
		TInt iExtensionId;
		};

	typedef TPckg<TContactFieldsV1> TContactFieldsV1Pckg;

	enum TSyncIdType
		{
		ESyncGroupId,
		ESyncTemplateId
		};

public:
	IMPORT_C RPhoneBookSession();
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C TVersion Version() const;
	IMPORT_C void DoSynchronisation(TRequestStatus& aReqStatus);
	IMPORT_C TInt ValidateContact(MContactSynchroniser::TValidateOperation aOperation, TContactItemId aId);
	IMPORT_C void WriteContact(TRequestStatus& aReqStatus, CContactICCEntry& aContactItem, TInt& aSlotNumber);
	IMPORT_C void DeleteContact(TRequestStatus& aReqStatus, TContactItemId aId);
	IMPORT_C TInt GetPhoneBookId(TContactItemId& aId, TSyncIdType aIdType);
	IMPORT_C TInt UpdateLookuptable(TContactItemId aNewUid, TInt aIccSlot);
	IMPORT_C TInt GetContactFormat(TDes8& aContactFields);
	IMPORT_C TInt GetSyncMode(TPhonebookSyncMode& aSyncMode);
	IMPORT_C TInt SetSyncMode(TPhonebookSyncMode aSyncMode);
	IMPORT_C TInt GetPhoneBookCacheState(TSyncState& aState);
	IMPORT_C void CancelRequest(TPhonebookSyncRequestCancel aReqToCancel);
	IMPORT_C void NotifyPhBkCacheStateChange(TRequestStatus& aStatus);
	IMPORT_C TInt GetLastSyncError(TInt& aError);
	IMPORT_C TInt GetNumSlots(TInt& aNumSlots) const;
	IMPORT_C void GetFreeSlotsL(RArray<TInt>& aFreeSlots) const;
	IMPORT_C TInt GetSlotId(TInt aSlot, TContactItemId& aId) const;

	// Debug calls - stubbed in release builds
	IMPORT_C TInt __DbgMarkHeap();
	IMPORT_C TInt __DbgCheckHeap(TInt aCount);
	IMPORT_C TInt __DbgMarkEnd(TInt aCount);
	IMPORT_C TInt __DbgFailNext(TInt aCount);
	
private:
	RPhoneBookSession(const RPhoneBookSession& aSession);
	TInt MapContactFormatToInternalL(const CContactICCEntry& aContactItem);
	void SetTypeOfNumber(const TDesC& aNumber);
private:
	CPBSyncPtrHolder* iSyncPtrHolder;
	};



#endif