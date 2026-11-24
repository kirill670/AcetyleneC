// MCLIENT.H
//
// Copyright (c) 1998-2004 Symbian Software Ltd.  All rights reserved.
//

#if !defined(__MCLIENT_H__)
#define __MCLIENT_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__MSVSTD_H__)
#include "msvstd.h"
#endif

#if !defined(__MSVIPC_H__)
#include "msvipc.h"
#endif

#if !defined(__MSVREG_H__)
#include "msvreg.h"
#endif

#ifdef __MESSAGING_API_V2__
#include "mmsvstoremanager.h"
#endif // __MESSAGING_API_V2__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__
// Forward declarations
class CMsvClientEntry;
#ifdef __MESSAGING_API_V2__
class TCapabilitySet;
#endif // __MESSAGING_API_V2__

//**********************************
//RMsvSession
//**********************************
//
// NOTE most functions are exported for test purposes only
//
#ifdef __MESSAGING_API_V2__
/**
Low level client-side API to access the message server. 

It should not be used directly by client applications. They should use higher-level helper classes such as 
CMsvSession, CMsEntry, and CMsvStore. These helper classes access the message server through RMsvServerSession.

@internalTechnology
*/
class RMsvServerSession : public RSessionBase, public MRegisteredMtmDllObserver, public MMsvStoreManager
#else // __MESSAGING_API_V2__
class RMsvServerSession : public RSessionBase, public MRegisteredMtmDllObserver
/**
Low level client-side API to access the message server. 

It should not be used directly by client applications. They should use higher-level helper classes such as 
CMsvSession, CMsEntry, and CMsvStore. These helper classes access the message server through RMsvServerSession.
@internalComponent
@released
*/
#endif // __MESSAGING_API_V2__
	{
public:
	IMPORT_C RMsvServerSession();
	IMPORT_C virtual ~RMsvServerSession();
	IMPORT_C TInt Connect(RFs& aFs);
	IMPORT_C TVersion Version() const;
	// Synchronous message
	IMPORT_C TInt GetEntry(TMsvId aId, TMsvId& aService, TMsvEntry& aEntry);
	IMPORT_C TInt GetChildren(TMsvId aId, CArrayPtrFlat<CMsvClientEntry>& aEntries, const TMsvSelectionOrdering& aOrdering);
	IMPORT_C TInt LockEntry(TMsvId aId);
	IMPORT_C TInt ReleaseEntry(TMsvId aId);
	IMPORT_C TInt ReadStore(TMsvId aId);
	IMPORT_C TInt LockStore(TMsvId aId);
	IMPORT_C TInt ReleaseStore(TMsvId aId);
	TInt DecStoreReaderCount(TMsvId aId);
	IMPORT_C TInt OperationProgress(TMsvOp aId, TDes8& aProgress);
	IMPORT_C TInt OperationCompletion(TMsvOp aId, TDes8& aProgress);
	IMPORT_C TInt CancelOperation(TMsvOp aId, TDes8& aProgress);
	IMPORT_C TInt CancelSessionEventRequest();
	IMPORT_C TInt OperationMtmL(TMsvId aId1, TMsvId aId2, TUid& aMtm, TMsvId& aService);
#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C TInt LocalStoreDeleted(TMsvId aId);
#endif	// __HIDE_MESSAGING_API_V1__
	inline TInt OperationMtmL(TMsvId aId1, TUid& aMtm, TMsvId& aService);
#ifdef __MESSAGING_API_V2__
	IMPORT_C void CreateEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TSecureId aOwnerId);
	IMPORT_C void ChangeEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TSecureId aOwnerId);
#endif	// __MESSAGING_API_V2__
#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void CreateEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId);
	IMPORT_C void ChangeEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId);
#endif	// __HIDE_MESSAGING_API_V1__
	IMPORT_C void MoveEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId);
	IMPORT_C void CopyEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId);
	IMPORT_C void DeleteEntriesL(const CMsvEntrySelection& aSelection, TMsvOp aOperationId);
	IMPORT_C void ChangeAttributesL(const CMsvEntrySelection& aSelection, TUint aSetAttributes, TUint aClearAttributes);
	IMPORT_C void GetChildIdsL(TMsvId aId, const CMsvEntryFilter& aFilter, CMsvEntrySelection& aSelection);
	TInt OutstandingOperationsL();
	// Asynchronous messages
#ifdef __MESSAGING_API_V2__
	IMPORT_C void CreateEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TSecureId aOwnerId, TRequestStatus& aRequestStatus);
	IMPORT_C void ChangeEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TSecureId aOwnerId, TRequestStatus& aRequestStatus);
#endif	// __MESSAGING_API_V2__
#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void CreateEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void ChangeEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
#endif	// __HIDE_MESSAGING_API_V1__
	IMPORT_C void DeleteEntriesL(const CMsvEntrySelection& aSelection, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void MoveEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void CopyEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void TransferCommandL(const CMsvEntrySelection& aSelection, TInt aCommandId, const TDesC8& aParameter, TMsvOp aOperationId, TRequestStatus& aStatus);
	IMPORT_C TInt TransferCommandL(const CMsvEntrySelection& aSelection, TInt aCommandId, const TDesC8& aParameter, TMsvOp aOperationId);
	IMPORT_C void QueueSessionEventRequest(TDes8& aChange, TDes8& aSequence, TRequestStatus& aRequestStatus);
	void ChangeDriveL(TInt aDrive, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
#ifdef __MESSAGING_API_V2__
	void CopyStoreL(const TDriveUnit& aDrive, TMsvOp aOperationId, TRequestStatus& aStatus);
	void DeleteStoreL(const TDriveUnit& aDrive, TMsvOp aOperationId, TRequestStatus& aStatus);
#endif // __MESSAGING_API_V2__
	// MTM 
	IMPORT_C TInt FillRegisteredMtmDllArray(TUid aMtmDllTypeUid,CRegisteredMtmDllArray& aRegisteredMtmDllArray,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32);  // Fill array with Dlls whose second uid is aMtmDllTypeUid
	IMPORT_C TInt InstallMtmGroup(const TDesC& aFullName);
	IMPORT_C TInt DeInstallMtmGroup(const TDesC& aFullName); 
	IMPORT_C TInt UseMtmGroup(TUid aMtmTypeUid);
	IMPORT_C TInt ReleaseMtmGroup(TUid aMtmTypeUid);  
	IMPORT_C CMtmGroupData* GetMtmGroupDataL(TUid aMtmTypeUid);  
#ifdef __MESSAGING_API_V2__
	void GetMtmRequiredCapabilitiesL(TUid aMtmTypeUid, TCapabilitySet& aCapSet) const;
	TBool GetAndClearIndexCorruptFlagL();
	TBool DriveContainsStoreL(TDriveUnit aDrive);
#endif // __MESSAGING_API_V2__
	// Server
	IMPORT_C void CloseMessageServer();
	IMPORT_C void RemoveEntry(TMsvId aId);
	IMPORT_C TInt GetMessageDirectory(TDes& aDirectory);
	TInt SetSessionAsObserver();
	TUint32 NotifySequenceL();
#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C TInt GetMtmPath(const TUidType& aType, TDes& aName) const;
	IMPORT_C TInt SetMtmPath(const TUidType& aType, const TDesC& aName);
	IMPORT_C TInt DelMtmPath(const TUidType& aType);
#endif	// __HIDE_MESSAGING_API_V1__
	IMPORT_C TInt SetReceiveEntryEvents(TBool aReceive);
	// Services
	IMPORT_C TInt StopService(TMsvId aServiceId);
	IMPORT_C TBool ServiceActive(TMsvId aServiceId);
	IMPORT_C TInt ServiceProgress(TMsvId aServiceId, TDes8& aProgress);
	//
	IMPORT_C void SetFailure(TInt aType, TInt aArg1 = 0, TInt aArg2 = 0, TInt aArg3 = 0);
	TInt GetMessageDrive();

#ifdef __MESSAGING_API_V2__
	// from MMsvStoreManager
	IMPORT_C TBool CreateAttachmentForWriteL(TMsvId aEntryId, TDes& aFilename, RFile& aFile);
	IMPORT_C void OpenAttachmentL(TMsvId aEntryId, const TDesC& aFilePath, RFile& aFile);
	IMPORT_C void OpenAttachmentForWriteL(TMsvId aEntryId, const TDesC& aFilePath, RFile& aFile);
	IMPORT_C TInt DeleteAttachment(TMsvId aEntryId, const TDesC& aFilePath);
	IMPORT_C TInt OpenFileStoreForRead(TMsvId aEntryId, RFile& aFile);
	IMPORT_C void OpenTempStoreFileL(TMsvId aEntryId, RFile& aFile);
	IMPORT_C void ReplaceFileStoreL(TMsvId aEntryId);
	IMPORT_C void DeleteFileStoreL(TMsvId aEntryId);
	IMPORT_C TBool FileStoreExistsL(TMsvId aEntryId) const;
#endif //__MESSAGING_API_V2__

private:
	void DoGetChildrenL(TMsvId aId, CArrayPtrFlat<CMsvClientEntry>& aEntries, const TMsvSelectionOrdering& aOrdering);
	void DoGetRemainingChildrenL(TPckgBuf<TMsvChildrenDetails>& aDetails, CArrayPtrFlat<CMsvClientEntry>& aEntries);
	void PackEntryIntoBufferL(const TMsvEntry& aEntry);
	void SendEntryDataL(TMsvOp aOperationId, const TMsvEntry& aEntry);
	void SendOperationDataL(TMsvOp aOperationId, const CMsvEntrySelection& aSelection, TInt aParameter1=0, TInt aParameter2=0);
	void SendCommandDataL(TMsvOp aOperationId, const CMsvEntrySelection& aSelection, TInt aCommand, const TDesC8& aParameter);
	void TestSlotAvailableL();
	void PackOperationDataL(const CMsvEntrySelection& aSelection, TInt aParameter1, TInt aParameter2);
	void DoGetEntryL(TMsvId aId, TMsvId& aService, TMsvEntry& aEntry);
	
private:
	HBufC8* iBuffer;
	};

/**
Gets the MTM that would perform an operation on a specified entry.

@param aId1 ID of the entry
@param aMtm On return, the UID of the MTM that would be used 
@param aService On return, the ID of the service that would be used 
@return System wide error code

@capability None
*/
inline TInt RMsvServerSession::OperationMtmL(TMsvId aId1, TUid& aMtm, TMsvId& aService)
	{
	return OperationMtmL(aId1, aId1, aMtm, aService);
	}

#endif // __MCLIENT_H__

