// AGCLIENT.H
//
// Copyright (c) Symbian Software Ltd 1997-2004.  All rights reserved.
//

#ifndef __AGCLIENT_H__
#define __AGCLIENT_H__

#include <e32base.h>
#include <s32std.h>
#include <s32mem.h>

#include "agmmodel.h"
#include "agmcomon.h"
#include "agmtodos.h"
#include "agmiedit.h"
#include "agmentry.h"
#include "agmsets.h"
#include "agmupact.h"
#include "agmstore.h"
#include "agmfilts.h"
#include "agmlists.h"
#include "agmcomon.h"
#include "agmxsort.h"
#include "agmactiv.h"
#include "agmxiter.h"
#include "agmver.h"
#include "agmextrc.h"
#include "agmxentr.h"
#include "agmsiter.h"
#include "agmcfilt.h"


class TAgnEntryDateIterator;
class CAgnEntryStore;
class TAgnTodoListStore;
class CAgnAnonStore;
class TAgnEntryGroupId;
class TAgnTodoListId;
class CAgnEntryGroup;
class CAgnTodoList;
class TAgnTidyFlags;
class CAgnTodoListIds;
class TAgnEntryIter;
class TAgnSortInstance;
class CAgnActive;
class CAgnAlarm;
class TAgnTodoListMapItem;
class CParaFormatLayer;
class CCharFormatLayer;
class MPictureFactory;
class MAgnModelStateCallBack;
class MAgnProgressCallBack;

class CAgnModel;
class CAgnSyncIter;

/**
@internalComponent
@released
*/
enum TAgnClientPanic
	{
	ELockError =	-1,
	EBufferError =	-2,
	EStreamIdError =-3,
	EUnknownType =	-4,
	ENullEntry   =  -5,
	EBadModel	 =  -6,
	EServerDeath =  -7
	};

// Frequency that the server is asked if the UI needs to update (approx 5 secs)
const TUint KNotifierUpdateFrequency = 5000000;

//#define LOGGING

#ifdef LOGGING
#define LOGC(text) { _LIT(KText,text); TPtrC textPtr(KText); Log(textPtr);}
#else
#define LOGC(x)
#endif

class TMaxAlarmsDays
/**
@internalComponent
@released
*/
	{
public:
	TInt	iMaxNumberOfAlarms;
	TInt	iMaxNumberOfDays;
	};

#define LINE {TBuf<20> _zout; _zout.AppendFormat(_L("Line: %d"),__LINE__); User::InfoPrint(_zout);}

class CAgnservNotifyActive : public CActive
/**
@internalComponent
@released
*/
	{
public:
	static CAgnservNotifyActive* NewL(RAgendaServ& aClient, TInt aFrequency);
	void ConstructL(RAgendaServ& aClient, TInt aFrequency);
	void BeginNotifier();
	void CancelRequest();
	~CAgnservNotifyActive();
private:
	inline CAgnservNotifyActive(TInt aPriority = EPriorityStandard) : CActive(aPriority){};
	void DoCancel();
	void RunL();
private:
	RAgendaServ* iClient;
	TInt iFrequency;
	TCallBack iUpdateCallback;	// callback to update the UI
	TBool iCancelled;
	CPeriodic*				iUpdateTimer;
	};

class RAgendaServ : public RSessionBase
/** The client interface to the agenda server. 

This class accesses agenda data by sending messages synchronously to the server.
This allows shared access to an agenda file by more than one client. 

Most functions in this class should not be used directly. If there is a 
corresponding version of the function in the model class, that should be used 
instead.

Note that a separate instance of the RAgendaServ class is required for each 
agenda file that is open. Only one file can be open at any one time in 
the same server session.

The API is used as follows:

@code
RAgendaServ* agnServer = RAgendaServ::NewL(); // allocate and construct server session
CleanupStack::PushL(agnServer); // ensure object is deleted
agnServer->Connect(); // connect to the server
CleanupClosePushL(*agnServer); // ensure that the session's Close() method gets called
CAgnEntryModel* model = CAgnEntryModel::NewL(); // allocate and construct model
CleanupStack::PushL(model);
model->SetServer(agnServer); // set model's server session pointer
model->OpenL(fileName) // open file using server
// ...Use agenda model API as normal - invokes corresponding server functions
CleanupStack::PopAndDestroy(3); // model, close session with server, agnServer
@endcode 
@publishedAll
@released
*/
	{
public:
    /**
    @internalComponent
    @released
    */
	enum  TLock{EUnlocked, ELocked, EExclusive, EWriteOnly};
	
	/**
	@internalComponent
	@released
	*/
	enum TNotifyType {ENone, EEntry, ETodoList};

	/**
	@internalComponent
	@released
	*/
	enum TIndexType {EModelIndex = 0x01, EUidIndex = 0x02};
public:
	// Server Connection functions
	IMPORT_C static RAgendaServ* NewL();
	IMPORT_C ~RAgendaServ();
	static void Destroy(TAny* aAgnServ);
	IMPORT_C TInt Connect();
	IMPORT_C void OpenAgendaL(TDesC& aFileName);
	IMPORT_C void CloseAgenda();
	static   void CloseAgenda(TAny* aAgnServ);
	IMPORT_C void BuildIndex(TInt aIndex);

	// Server Utility functions
	IMPORT_C void Log(TPtrC& aMessage) const;
	IMPORT_C TBool CompactFile();

	// Update Notification functions
	IMPORT_C void StartNotifierL(TInt aFrequency = KNotifierUpdateFrequency);
	IMPORT_C void StartNotifierL(TCallBack aCallback, TInt aFrequency = KNotifierUpdateFrequency);

	// File / Stream Access functions
	IMPORT_C TStreamId CreateNewStreamL(TUid aStreamUid);
	IMPORT_C RWriteStream& GetWriteStreamL(TStreamId aStreamId);
	IMPORT_C void CloseWriteStreamL();
	IMPORT_C TBool FileLoaded();
	IMPORT_C TBool FileIsReadOnly();

	IMPORT_C void GetDayDateTimeListFromExtractorL(TAgnDate aDay, CAgnDayDateTimeInstanceList* aDayInfoList) const;
	IMPORT_C void PopulateSymbolInstanceListL(CAgnSymbolList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate, CAgnEntryModel *aModel) const;

	IMPORT_C CAgnEntry::TType TypeByUniqueId(TAgnUniqueId aUniqueId);
	IMPORT_C TBool HasUniqueIdBeenDeleted(TAgnUniqueId aUniqueId);
	IMPORT_C TAgnDateTime UniqueIdLastChangedDate(TAgnUniqueId aUniqueId);
	IMPORT_C TAgnUniqueId GetUniqueId(TAgnEntryId aEntryId);
	IMPORT_C TAgnUniqueId GetUniqueId(TAgnTodoListId aTodoId);
	IMPORT_C TAgnEntryId GetEntryId(TAgnUniqueId aUniqueId);
	IMPORT_C TInt DeleteEntry(TAgnUniqueId aUid);
	IMPORT_C TInt DeleteTodoList(TAgnUniqueId aUid);
	// Entry / Date Iterator functions
	IMPORT_C TBool CreateEntryIterator();
	IMPORT_C TBool EntryIteratorNext();
	IMPORT_C TAgnEntryId EntryIteratorPosition();
	IMPORT_C TInt EntryIteratorStreamCount();
	IMPORT_C TInt EntryIteratorStreamCurrent();
	IMPORT_C void CreateDateIterator(TTime aToday, TAgnFilter* aFilter, TAgnDate aTidyStartDate);
	IMPORT_C void DateIteratorPrevious();
	IMPORT_C void DateIteratorNext();
	IMPORT_C TBool DateIteratorAtStart();
	IMPORT_C TBool DateIteratorAtEnd();
	IMPORT_C TAgnDate DateIteratorCurrentKey();
	IMPORT_C CAgnSortEntry* DateIteratorCurrentElement(CAgnSortEntryAllocator* aAllocator);
	IMPORT_C void DateIteratorGoto(TAgnDate aDate);
	IMPORT_C void DateIteratorGotoLessOrEqual(TAgnDate aDate);

	IMPORT_C void WaitUntilLoaded();

	// new connectivity sync functionality
	IMPORT_C void DecEntryRefCountL(const TAgnUniqueId aUniqueId);
	IMPORT_C void IncEntryRefCountL(const TAgnUniqueId aUniqueId);
	IMPORT_C void DecEntryRefCountsL(const CArrayFix<TAgnUniqueId>& aListOfUniqueIds);
	IMPORT_C void IncEntryRefCountsL(const CArrayFix<TAgnUniqueId>& aListOfUniqueIds);
	IMPORT_C void GetEntryUidsSinceDateL(CArrayFix<TAgnUniqueId>& aUids, const TAgnConnectivityFilter& aFilter, const TFileName& aFilterLibrary=KAgnDefaultFilter());
	IMPORT_C TInt FreeSpaceAvailable() const;
	IMPORT_C void StartCompactionL();
	IMPORT_C void StopCompactionL();
	IMPORT_C TInt _DebugRequestAllocatedCellsL();		
	IMPORT_C void _DebugSetHeapFail(TInt aHeapAllocationFailureFlag, TInt aCount);
 	
	
public:
	TVersion Version() const;
	void SetPictureFactory(MPictureFactory* aFactory);
	MPictureFactory* PictureFactory();
	TInt PercentageLoadedL(TBool aPause = EFalse);
	static TInt UpdateNotifier(TAny* aPtr);
	TInt DoUpdateNotifier();
	TNotifyType CheckNotifier();
	void SetNotifier(TRequestStatus& aStatus);
	TStreamId StreamId(TUid aUid);
	RReadStream& GetReadStreamL(TStreamId aStreamId);
	CEmbeddedStore* GetEmbeddedStoreL(TStreamId aStreamId);
	// Entry Fetch / Update functions
	CAgnEntry* FetchEntryL(TAgnEntryId aId,CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer) const;
	CAgnEntry* FetchEntryL(TAgnGlobalId aId,CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer) const;
	CAgnEntry* FetchEntryL(TAgnUniqueId aId,CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer) const;
	TAgnLiteEntry GetLiteEntryL(TAgnEntryId aId, CAgnSortEntryAllocator* aAllocator) const;
	void UpdateEntryL(CAgnEntry *aEntry, TAgnEntryId aTodoPosition);
	TAgnEntryId AddEntryL(CAgnEntry *aEntry, TAgnEntryId aTodoPosition, TInt aCommit, TBool aUseExistingId);
	void DeleteEntryL(CAgnEntry *aEntry);
	// Entry Filter / Extraction functions
	void GetInstanceExtractorL(TAgnDate aToday, const TAgnFilter& aFilter) const;
	void GetDayListFromExtractorL(TAgnDate aDay, CArrayFixFlat<TAgnInstanceId>* aDayInfoList) const;
	// ToDo List functions
	CAgnTodoList* FetchTodoListL(TAgnTodoListId aId);
	CAgnTodoList* FetchTodoListL(TAgnUniqueId aId);
	TStreamId SaveTodoListsL(TFileName aFileName);
	void RefreshTodoListListL(CAgnTodoListList* aTodoListList, CAgnDeletedTodoListList* aDeletedTodoListList);
	void UpdateTodoListL(CAgnTodoList* aTodoList);
	TAgnTodoListId AddTodoListL(CAgnTodoList* aTodoList, TInt aPosition);
	void DeleteTodoListL(CAgnTodoList* aTodoList);
	void ChangeTodoListOrderL(TInt aOldPosition, TInt aNewPosition);
	void CreateDateIteratorL(TTime aToday, TAgnFilter* aFilter, TAgnDate aTidyStartDate);
	// Model Utility functions
	void CommitL();
	void Rollback();
	void SetParaAndCharFormatLayersL(const CParaFormatLayer* aParaFormatLayer, const CCharFormatLayer* aCharFormatLayer);
	void GetModelTextFormattingL(CParaFormatLayer* aParaFormatLayer, CCharFormatLayer* aCharFormatLayer);
	void QueueNextAlarmL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,CAgnSortEntryAllocator* aAllocator);
	TTime PreviousDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	TTime NextDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	void SetLastSynchronizedDateL(const TTime& aTime) const;
	TTime LastSynchronizedDateL() const;
	TStreamId GetObserverControllerStreamId();
	TInt EntryCount();
	TInt IndexCount(TInt aIndex);
	void UpdateSyncIterL(CAgnSyncIter& aIter);
	void GetNumEntriesToTidyL(TAgnDate aStartDate, TAgnDate aEndDate, TInt& aNumEntries, TInt& aNumTodos);
	void SetDefaultDisplayTimes(TTimeIntervalMinutes aDefaultEventDisplayTime,TTimeIntervalMinutes aDefaultAnnivDisplayTime,TTimeIntervalMinutes aDefaultDayNoteDisplayTime);
	void SetBufferedStoring(TInt aSetting);
	TInt BufferedStoring();
	void SetBufferedDeleting(TInt aSetting);
	TInt BufferedDeleting();
	void FlushL();
	void CommitAndCompactL();
	TInt GenerateSyncUidL();
	void SetLastSyncDateL(TInt aSyncUid, const TTime& aSyncDate);
	TTime GetLastSyncDateL(TInt aSyncUid) const;
	void GetFileIdL(TInt64& aFileId) const;
	TStreamId StoreNotesTextL(const TDesC& aNotes);
	HBufC* RestoreNotesTextL(TStreamId aId);
	void UpdateNotesTextL(const TDesC& aNotes, TStreamId aId);
	void DeleteNotesTextL(TStreamId aId);
	const TFileName& FileName() const;
	void StartBuildIndex(TRequestStatus& aStatus);
	void StartTidyByToDoListL(TRequestStatus& aStatus,
							  const CArrayFixFlat<TAgnTodoListId>* aList,
							  TInt aDirective,
							  TInt aTidyHow,
							  const TDesC& aNameOfFileToTidyTo);
	void StartTidyByDateL(TRequestStatus& aStatus,
						  const TAgnFilter& aFilter,
						  const TTime& aTodaysDate,
						  const TTime& aStartDate,
						  const TTime& aEndDate,
						  TInt aDirective,
						  const TDesC& aNameOfFileToTidyTo);	
	void RequestProgress(TRequestStatus& aStatus);
	void CreateAgendaFileL(const TDesC& aFileName,const TDesC& aDefaultTodoListName,const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer);
	void DeleteAgendaFileL(const TDesC& aFileName);
	CDesCArray* ListAgendaFilesL() const;
	TBool AgendaFileExistsL(const TDesC& aFileName);

public:		// category access
	TInt CategoryCountL();
	CAgnCategory* CategoryL(TInt aIndex);
	void AddCategoryToListL(const TDesC& aName);
	void GetArrayFilterL(CArrayFixSeg<TAgnEntryId>& aEntries);
	void CancelTaskL();
	void StartCategoryTaskL(TRequestStatus& aStatus,const CAgnCategory& aCategory, TInt aStepSize, TInt aTask, const TDesC& aNewName = KNullDesC);
	void CancelReporting();
	// Observers
	void InstallObserverL(TUid aUid, const TDesC8& aPluginData);
	void UninstallObserverL(TUid aUid);
	void UseObserverControllerL(TBool aUse);
	TBool IsInUseObserverControllerL();

private:
	CBufFlat* PackageCategoryInfoLC(const CAgnCategory& aCategory,TInt aStepSize);

private:
	RAgendaServ();	// private constructor
	void Panic(TAgnClientPanic aPanic) const;
	TInt DoConnect();
	TInt ServerRequestL(TInt aCommand, TAny* aArg1 = NULL, TAny* aArg2 = NULL, TAny* aArg3 = NULL, TAny* aArg4 = NULL) const;
	CBufFlat* CreateTransmitBufferL(TInt aBufferSize) const;
	RReadStream& GetEmbeddedReadStreamL(TStreamId aStreamId);

	
	void ExternalizeFilterL(const TAgnFilter& aFilter, RWriteStream& aStream) const;
	CAgnSortEntry* InternalizeSortEntryL(RReadStream& aStream, CAgnSortEntryAllocator* aAllocator) const;
	void LogMemoryUsage();
	CEmbeddedStore* OpenEmbeddedStoreL(TStreamId aStreamId);
	CAgnTodoList* ReadTodoListL(TInt aBufferSize);
	CBufBase* WriteTodoListLC(const CAgnTodoList& aTodoList);
	CAgnEntry* ReadEntryFromServerSessionL(CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer, TInt aBufferSize) const;
	static CBufBase* WriteNotesTextToBufferLC(const TDesC& aNotes);
	void InternalizeAlarmInstancesL(CArrayFixFlat<TAgnSortInstance>& aAlarmedIds, CAgnSortEntryAllocator* aAllocator, TInt aBufferSize);
	static CBufBase* WriteUniqueIdArrayLC(const CArrayFix<TAgnUniqueId>& aListOfUniqueIds);
	
private:
	TFileName				iFileName;
	TBool					iIsReadOnly;
	TBool					iIsLoaded;
	CBufFlat*				iBuffer;
	MPictureFactory*		iPictureFactory;
	TNotifyType				iUpdateStatus;
	CAgnservNotifyActive*	iNotifier;
	TCallBack				iUiCallback;	// callback to notify the UI
	TBool					iUiCallbackInstalled;

	// The cached stream is used for caching read and write streams
	// to/from the server. 

	// The embedded stream is used to keep a copy of the data being
	// read from an embedded object, and may have a longer lifespan
	// than the last stream read.

	TStreamId				iCachedStreamId;	// id of the currently cached stream
	CBufFlat*				iCachedStream;
	RBufReadStream*			iCachedReadStream;
	RBufWriteStream*		iWriteStream;

	TStreamId				iEmbeddedStreamId;
	CBufFlat*				iEmbeddedStream;
	RBufReadStream*			iEmbeddedReadStream;
	CEmbeddedStore*			iEmbeddedStore;
	};





#endif
