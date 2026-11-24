// AGMMODEL.H
//
// Copyright (c) Symbian Software Ltd 1997-2004.  All rights reserved.
//
#ifndef __AGMMODEL_H__
#define __AGMMODEL_H__

#include <e32base.h>
#include <vutil.h>
#include <e32def.h>
#include <badesca.h>
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
#include "agmobsrv.h"
#include "agmextrc.h"
#include "agmcfilt.h"
#include "agclient.h"


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
class CAgnGlobalIdIndex;
class CAgnObsController;
class CAgnTodoListIdIndex;
class CAgnCategoryIndex;
class CAgnServFile;
class CAgnProgressReporter;
class CAgnAsyncServerObserver;


class MAgnVersit
/** Provides an interface to decouple the static dependency of CAgnEntryModel on 
Versit.

This interface is implemented by the internal class TAgnVCalConverter, in a DLL 
called agnversit.dll. Rather than statically linking against versit.dll, the 
agenda engine dynamically loads agnversit.dll, to remove its dependency on Versit. 
All CAgnEntryModel's vCalendar-specific functions call the corresponding functions, 
below. 
@publishedPartner
@released
*/
	{
public:
	/** Imports a vCalendar consisting of one or more vCalendar entities.
	
	The vCalendar is read from the read stream specified and its entities are 
	converted into agenda entries and returned in the array aEntryArray.
	
	@param aFlags CAgnEntryModel::ELocalTime causes all date/times to be converted 
	to machine-local; CAgnEntryModel::EDefault leaves them unadjusted.
	@param aReadStream The read stream which contains the vCalendar.
	@param aEntryArray On return, a list of the agenda entries which were imported 
	from the vCalendar. The list contains the vEvents followed by the vTodos.
	@param aEntryModel Pointer to the agenda entry model instance that is calling 
	this function. */
	virtual void ImportVCalL(TInt aFlags, RReadStream& aReadStream, CArrayPtr<CAgnEntry>* aEntryArray, CAgnEntryModel* aEntryModel)=0;
	/** Exports one or more agenda entries as vCalendar entities to the write stream 
	specified. 
	
	The entries are exported either as vTodos, if they are to-dos, otherwise as 
	vEvents.
	
	@param aFlags CAgnEntryModel::ELocalTime causes all date/times to be left 
	as machine-local; CAgnEntryModel::EDefault causes them to be converted into 
	UTC.
	@param aWriteStream The stream to which the agenda entries should be externalised 
	as vCalendar entities.
	@param aEntryArray Pointer to the array of agenda entries to export.
	@param aCharSet The character encoding type.
	@param aEntryModel Pointer to the agenda entry model instance that is calling 
	this function. */
	virtual	void ExportVCalL(TInt aFlags, RWriteStream& aWriteStream, CArrayPtr<CAgnEntry>* aEntryArray, const Versit::TVersitCharSet aCharSet, CAgnEntryModel* aEntryModel)=0;
	/** Parses a vCalendar stream and updates the appropriate entries.
	
	Any vCalendar entities which do not contain a UID property, or entities with 
	a UID which doesn't exist in the agenda file will cause the aNumFailedToImport 
	count to increment.
	
	@param aReadStream The input vCalendar stream to be parsed.
	@param aNumFailedToImport On return, a count of the number of vCalendar entities 
	which do not contain a UID property, or entities with a UID which doesn't 
	exist in the agenda file.
	@param aEntryModel Pointer to the agenda entry model instance calling this 
	function. */
	virtual void UpdateVCalL(RReadStream& aReadStream, TInt& aNumFailedToImport, CAgnEntryModel* aEntryModel)=0;
	/** Destroys the MAgnVersit object.
	
	Called by CAgnEntryModel's destructor. */
	virtual void Release()=0;
private:
	IMPORT_C virtual void MAgnVersit_Reserved1();
	};

#ifdef SYMBIAN_COREAPPS_PLUGIN_API_V2
const TUid  KUidEComAgnVersitInterface = {0x102035F4};
class CAgnVersit: public CBase, public MAgnVersit
/** Provides an interface for ECom plugins
@publishedPartner
@released
*/
	{
public:
	static CAgnVersit* NewL();
	/** Releases Ecom resources
	*/
	IMPORT_C virtual ~CAgnVersit();
private:
	TUid iDtor_ID_Key;
	};

#endif
class CAgnEntryModelExData : public CBase
/**
Holds additional CAgnEntryModel data for BC proofing.
@internalComponent
@released
*/
	{
public:
	static CAgnEntryModelExData* NewL(CAgnServFile& aAgnServerFile);
	~CAgnEntryModelExData();

	CAgnServFile& AgnServerFile() const;
	CAgnAsyncServerObserver* AgnAsyncServerController();
	CAgnProgressReporter*    AgnProgressReporter();
	inline void SetBlockedState(TBool aState);
	inline TBool IsBlocked();
	TAgnEntryDateIterator* GetDateIterator();
	inline void SetFileredEntry(CArrayFixSeg<TAgnEntryId>* aEntries);
	inline void SetFileredEntryToNull();
	inline CArrayFixSeg<TAgnEntryId>* FilteredEntries() const;
	
private:
	inline CAgnEntryModelExData(CAgnServFile& aAgnServerFile);
	void ConstructL();
private:
	CAgnServFile* iAgnServerFile;	//not owned
	CAgnAsyncServerObserver* iAgnAsyncServerController;
	CAgnProgressReporter* iAgnProgressReporter;
	CArrayFixSeg<TAgnEntryId>* iFilteredEntries; // Not owned
	};
	
	

#ifndef SYMBIAN_REMOVE_COREAPPS_API_V1
class CAgnEntryModel : public CBase, public MAgnActiveStep
#else
class CAgnEntryModel : public CBase
#endif
/** The interface to the data stored in an agenda file.

In the entry model, the agenda data can be accessed as entries. There 
are the following types of entry: 

- appointments (CAgnAppt)

- to-dos (CAgnTodo)

- events (CAgnEvent)

- anniversaries (CAgnAnniv)

All requests to access agenda data are made by sending messages to the 
agenda server. This is invisible to the user of the class. This allows 
multiple applications to access the same data concurrently. 

Note that from v8.1 onwards, the agenda model can no longer be used in 'normal' 
(non-client) mode.

@see CAgnIndexedModel
@see CAgnModel 
@publishedAll
@released
*/
	{
public:
	friend class TAgnEntryIter;
	friend class CAgnUniqueView;
	/** Model state.
	@publishedAll
	@released
	*/
	enum TState	
			{
			/** The initial state of the model before a file has been created or opened. Also 
			the state of the model after an unsuccessful operation, e.g. after an attempt 
			to open a file has failed. Many agenda model functions raise a panic if the 
			model's state is ENoFile, for instance adding, deleting or updating entries 
			or to-do lists. */
			ENoFile,
			/** The model's state while it is carrying out a prolonged activity. Indicates 
			that the model is not available for use and any attempt to use it results 
			in a panic. */
			EBlocked, 
			/** A file is open, and the model is ready for use. */
			EOk
			};
	
	/** Specifies how frequently the caller of SaveAsL() 
	should be notified of its progress via MAgnProgressCallBack::Progress(). 
	It should not normally be necessary to change the value from the default 
	(ESaveAsCallBackMedium). 
	@publishedAll
	@released
	*/
	enum TSaveAsCallBackFrequency 
			{
			/** High frequency. */
			ESaveAsCallBackHigh=1,
			/** Medium frequency (the default). */
			ESaveAsCallBackMedium=3,
			/** Low frequency. */
			ESaveAsCallBackLow=4
			};
	enum 
		{
		/** Indicates the last position in the model's list of to-do lists. */
		EAddTodoListAtEnd=0xFFFF
		};
	/**
	@publishedAll
	@released
	*/
	enum TUseExistingUniqueId {EUseExistingUniqueId,EDontUseExistingUniqueId};

	/**
	@publishedAll
	@released
	*/
	enum TCommit {ECommit,EDontCommit}; 	
	/** The category step size. 
 
 	This is used when asynchronously filtering on a category, or deleting or renaming 
 	a category, using FilterCategoryL(), DeleteCategoryL() or RenameCategoryL(). These 
 	operations are done in steps. After each step, the progress of the task is reported 
 	to the caller via MAgnProgressCallBack::Progress().
 
 	The step size controls the frequency with which Progress() is called. The lower the 
 	step size, the more items are processed in each step, and the less frequently the 
 	caller will be notified. */
	enum TCategoryStepSize 
		{
		/** Low frequency. */
		ECategoryStepSizeLow = 5, 
		/** Medium frequency - this is used as the default. */
		ECategoryStepSizeMedium = 10, 
		/** High frequency. */
		ECategoryStepSizeHigh = 20
		};

	/** Indicates whether or not the model is a client of the server. 
	
	@publishedAll
	@released
	*/
	enum TModelMode 
			{
			/** The model is not using the server.  */
			ENormal,
			/** The model is a client of the server. */
			EClient,
			/** The model is in server mode. A client program should never set the model to 
			EServer. */
			EServer
			};
	/**
	@publishedAll
	@released
	*/
	enum TOpenFrequency {EOpenCallBackHigh=1,EOpenCallBackMedium=2,EOpenCallBackLow=4};

	/**
	@publishedAll
	@released
	*/
	enum TOptions {EDefault,ELocalTime};
	enum TActiveAction {ENone,ESaveAs,EFilterCategory,EDeleteCategory,ERenameCategory,ECompact}; //ECompact has to be the last one
		
	/**
	@publishedAll
	@released
	*/		
	enum TNotifyFrequency{ENoProgress = 0, ENotifyProgress};
	
	/**
	@publishedAll
	@released
	*/			
 
	IMPORT_C static CAgnEntryModel* NewL(MAgnModelStateCallBack* aStateCallBack=NULL); 
	IMPORT_C virtual ~CAgnEntryModel();



	IMPORT_C void OpenL(const TDesC& aFileName,
						TTimeIntervalMinutes aDefaultEventDisplayTime = 0,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime = 0,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime = 0);

	void OpenL(CStreamStore& aStore,	
 						TStreamId aId,
						TTimeIntervalMinutes aDefaultEventDisplayTime = 0,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime = 0,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime = 0);

#ifndef SYMBIAN_HIDE_COREAPPS_API_V1
	IMPORT_C TStreamId SaveAsL(CStreamStore& aStoreToSaveTo,MAgnProgressCallBack* aProgressCallBack,
						TSaveAsCallBackFrequency aSaveAsCallBackFrequency = ESaveAsCallBackMedium) const;

	IMPORT_C TStreamId SaveTodoListsL(CStreamStore& aStoreToSaveTo) const;
	IMPORT_C TStreamId SaveTodoListsL(TFileName aFileName) const;


	IMPORT_C TStreamId CreateL(CStreamStore& aStore,
								const TDesC& aDefaultTodoListName,
								const CParaFormatLayer* aParaFormatLayer,
								const CCharFormatLayer* aCharFormatLayer);  
	
	IMPORT_C TStreamId CreateL(CStreamStore& aStore,
								const TDesC& aDefaultTodoListName,
								const CParaFormatLayer* aParaFormatLayer,
								const CCharFormatLayer* aCharFormatLayer,
								TBool aCreateTodoList);

	IMPORT_C TInt IsValidL(CStreamStore& aStore,TStreamId aId) const;
	IMPORT_C void SetMode(TModelMode aMode);
#endif //SYMBIAN_HIDE_COREAPPS_API_V1

	TStreamId CreateL2(CStreamStore& aStore,
					const TDesC& aDefaultTodoListName,
					const CParaFormatLayer* aParaFormatLayer,
					const CCharFormatLayer* aCharFormatLayer,
					TBool aCreateTodoList);

	TStreamId SaveTodoListsL2(CStreamStore& aStoreToSaveTo) const;
	void SetMode2(TModelMode aMode);
	TInt IsValidL2(CStreamStore& aStore,TStreamId aId) const;


// Entry operations
	TAgnEntryId AddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit,TUseExistingUniqueId aUseExistingUniqueId = EDontUseExistingUniqueId);
	IMPORT_C TAgnEntryId AddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());
	IMPORT_C void DeleteEntryL(CAgnEntry* aEntry);
	IMPORT_C virtual void DeleteEntryL(TAgnEntryId aEntryId);
	virtual void DeleteEntryL(CAgnEntry* aEntry,TCommit aCommit);
 	IMPORT_C void UpdateEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());
	void UpdateEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit);
	IMPORT_C CAgnEntry* FetchEntryL(TAgnEntryId aId) const;
	IMPORT_C CAgnEntry* FetchEntryL(TAgnGlobalId aId) const;
	IMPORT_C CAgnEntry* FetchEntryL(TAgnUniqueId aId) const;
	IMPORT_C void ChangeTodoOrderL(TAgnTodoListId aTodoListId,TAgnEntryId aTodoId,TAgnEntryId aTodoPositionReferenceId= AgnModel::NullId());
	IMPORT_C void ChangeTodoOrderL(CAgnTodoList* aTodoList,TAgnEntryId aTodoId,TAgnEntryId aTodoPositionReferenceId= AgnModel::NullId());
	IMPORT_C void CutEntryL(TAgnEntryId aEntryId);
	IMPORT_C void CutEntryL(CAgnEntry* aEntry);
	IMPORT_C void PasteEntryL(CAgnEntry* aEntry, TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());

// Todo list operations
	IMPORT_C CAgnTodoList* FetchTodoListL(TAgnTodoListId aTodoListId) const;
	IMPORT_C CAgnTodoList* FetchTodoListL(TAgnUniqueId aUniqueId) const;
	IMPORT_C virtual TAgnTodoListId AddTodoListL(CAgnTodoList* aTodoList,TInt aPosition=EAddTodoListAtEnd);
	IMPORT_C virtual void DeleteTodoListL(CAgnTodoList* aTodoList);  
	IMPORT_C virtual void DeleteTodoListL(TAgnTodoListId aTodoListId);
	IMPORT_C virtual void UpdateTodoListL(CAgnTodoList* aTodoList);
	IMPORT_C TInt TodoListCount() const;
	IMPORT_C void ChangeTodoListOrderL(TInt aOldPosition,TInt aNewPosition);
	IMPORT_C void PopulateTodoListNamesL(CAgnTodoListNames* aList) const;
	inline const CAgnTodoListList* PeekAtTodoListList() const;
	inline const CAgnDeletedTodoListList* PeekAtDeletedTodoListList() const; //  for synchronisation users
	IMPORT_C CArrayFixFlat<TAgnTodoListId>* TodoListIdsL() const; // for synchronisation users

// Misc 
	inline void SetDefaultEventDisplayTime(TTimeIntervalMinutes aDefaultEventDisplayTime);
	inline void SetDefaultAnnivDisplayTime(TTimeIntervalMinutes aDefaultAnnivDisplayTime);
	inline void SetDefaultDayNoteDisplayTime(TTimeIntervalMinutes aDefaultDayNoteDisplayTime);
	inline TTimeIntervalMinutes DefaultEventDisplayTime() const;
	inline TTimeIntervalMinutes DefaultAnnivDisplayTime() const;
	inline TTimeIntervalMinutes DefaultDayNoteDisplayTime() const;
	IMPORT_C TTimeIntervalMinutes DefaultDisplayTime(CAgnEntry::TType aType,TAgnTodoListId = AgnModel::NullId()) const;
	inline TState State() const;
	inline void RegisterAlarm(CAgnAlarm* aAlarm);
	inline CAgnAlarm* RegisteredAlarm() const;
	inline const CParaFormatLayer* ParaFormatLayer() const;
	inline const CCharFormatLayer* CharFormatLayer() const;
	IMPORT_C void SetParaAndCharFormatLayersL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer);
	inline void SetPictureFactory(MPictureFactory* aPictureFactory);
	inline MPictureFactory* PictureFactory() const;
	inline CAgnSortEntryTable* RegisteredIndex() const;
	inline CStreamStore& StreamStore() const;
	IMPORT_C TAgnVersion ModelVersion() const; // the version of the model object
	inline TAgnVersion FileVersion() const; // the version of the model that was used to create the currently loaded file
	inline CAgnGlobalIdIndex* GlobalIdIndex() const;
	inline CAgnUniqueIdIndex* UniqueIdIndex() const;
	inline CAgnTodoListIdIndex* TodoListIdIndex() const;
	inline CAgnDeletedIndex* DeletedIndex() const;
	IMPORT_C TTime LastSynchronizedDateL() const;
	IMPORT_C void SetLastSynchronizedDateL(const TTime& aTime) const;
	void SetDefaultDisplayTime(CAgnEntry* aEntry) const;
	IMPORT_C void Cancel(); // cancel an active object driven operation
	const TFileName& FileName() const;

// Observer stuff
#ifndef SYMBIAN_COREAPPS_PLUGIN_API_V2
	IMPORT_C void RegisterObserverL(const TFileName& aObserverName,const CAgnObserver* aObserver);	// Regiser a new observer
	IMPORT_C void UnregisterObserverL(const TFileName& aObserverName);
	IMPORT_C void UseObserverController(TBool aUse);
	IMPORT_C TBool IsInUseObserverController() const;
	IMPORT_C TInt NumberOfObserversRegistered() const;
	IMPORT_C TInt NumberOfObserversLoaded() const;
#else
 	IMPORT_C void RegisterObserverL(TUid aUid, const TDesC8& aPluginData=KNullDesC8);	// Register a new observer
 	IMPORT_C void UnregisterObserverL(TUid aUid);
	IMPORT_C void UseObserverControllerL(TBool aUse);
	IMPORT_C TBool IsInUseObserverControllerL() const;
#endif
	void UpdateObserverControllerL();
	inline CAgnObsController* ObserverController() const;

// Don't call these unless you know what you're doing
	IMPORT_C TBool BufferedStoring() const;
	IMPORT_C void SetBufferedStoring(TBool aSetting);
	IMPORT_C TBool BufferedDeleting() const;
	IMPORT_C void SetBufferedDeleting(TBool aSetting);	
	IMPORT_C void CommitL();
	IMPORT_C void FlushAndCommitL();
	void FlushL();
	IMPORT_C void RollbackL();
	inline void SetState(TState aState); 

	IMPORT_C void CreateL(RFs& aFs, TFileName aFileName,
							const TDesC& aDefaultTodoListName,
							const CParaFormatLayer* aParaFormatLayer,
							const CCharFormatLayer* aCharFormatLayer);


	// Addition functions required for server interface
	IMPORT_C TStreamId StreamId(TUid aUid);
	IMPORT_C RReadStream& GetReadStreamL(TStreamId aStreamId);
	void ConstructIndexesL();
	TBool PrepareForIndexBuilderL();
	void CleanupIndexBuilder();			// deprecated -- do not use (does nothing)
	TInt DoIndexBuildStepL();
	CAgnSortEntryTable* ModelIndex();
	IMPORT_C TAgnInstanceExtractor* GetInstanceExtractorL(TAgnDate aToday, TAgnFilter& aFilter);
	IMPORT_C void GetDayListFromExtractorL(TAgnInstanceExtractor* aExtractor, TAgnDate aDay, CArrayFixFlat<TAgnSortInstance>* aDayInfoList, TAgnDate aToday);
	TAgnLiteEntry GetLiteEntryFromServerL(TAgnEntryId aId,CAgnSortEntryAllocator* aAllocator) const;
	CAgnSortEntry* GetLiteEntryForServer(TAgnEntryId aId);
	void CreateAlarmForServer();
	IMPORT_C void GetSymbolInstanceListL(CAgnSymbolList* aList,TTime& aToday, TAgnFilter& aFilter);
	void ExternalizeSymbolListL(CAgnSymbolList* aSymbolList, RWriteStream& aStream);
	void InternalizeSymbolListL(CAgnSymbolList* aSymbolList, RReadStream& aStream);
	IMPORT_C void SetServer(RAgendaServ* aServer);
	IMPORT_C RAgendaServ* Server() const;
	TAgnEntryId AddEntryForServerL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit,TUseExistingUniqueId aUseExistingUniqueId = EDontUseExistingUniqueId);
	IMPORT_C void ServerLog(TPtrC& aMessage);
	IMPORT_C TBool IsClient() const;
	IMPORT_C CStreamStore* GetEmbeddedStore(TStreamId aId);
	void ExternalizeTodoListListL(RWriteStream aWriteStream);
	void QueueNextAlarmL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds);
	void NextAlarmForServerL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds);
	void NextFewAlarmsForServerL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,const TInt aMaxNumberOfAlarms,const TInt aMaxNumberOfDays);
	void NextFewAlarmsForServerL(const TTime& aStartDateTime,const TTime& aEndDateTime,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,const TInt aMaxNumberOfAlarms);
	TTime NextDayWithInstanceFromServer(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	TTime PreviousDayWithInstanceFromServer(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	inline CAgnModelStreamIdSet* ModelStreamIdSet() const;
	IMPORT_C void SetEntryServer(CAgnEntry* aEntry);
	IMPORT_C TBool CheckNotifier();
	IMPORT_C CAgnSortEntryAllocator* SortEntryAllocator();
	IMPORT_C void DeleteLiteEntry(const CAgnSortEntry* aSortEntry);
	void CleanupLiteEntry(TAny* aPtr);
	IMPORT_C void UpdateDefaultEntryTimes();

	// new connectivity requirements
	void GetEntryUidsSinceDateL(CArrayFix<TAgnUniqueId>* aUniqueIdList, const TAgnConnectivityFilter& aFilter, const TFileName& aFilterLibraryName);
	IMPORT_C TInt GenerateSyncUidL();
	IMPORT_C void SetLastSyncDateL(TInt aSyncUid, const TTime& aSyncDate);
	IMPORT_C TTime GetLastSyncDateL(TInt aSyncUid) const;
	IMPORT_C void GetFileIdL(TInt64& aFileId) const;
	IMPORT_C void UpdateVCalL(RReadStream& aReadStream, TInt& aNumFailedToImport);

	IMPORT_C void ImportVCalL(TInt aFlags, RReadStream& aReadStream, CArrayPtr<CAgnEntry>* aEntryArray);
	IMPORT_C void ExportVCalL(TInt aFlags, RWriteStream& aWriteStream, CAgnEntry* aEntry, const Versit::TVersitCharSet aCharSet = Versit::EUTF8CharSet);
	IMPORT_C void ExportVCalL(TInt aFlags, RWriteStream& aWriteStream, CArrayFixFlat<TAgnEntryId>* aEntryIdList, const Versit::TVersitCharSet aCharSet = Versit::EUTF8CharSet);

public:	// deprecated
	IMPORT_C void ImportVCalL(RReadStream& aReadStream, CArrayPtr<CAgnEntry>* aEntryArray);
	IMPORT_C void ExportVCalL(RWriteStream& aWriteStream, CAgnEntry* aEntry, const Versit::TVersitCharSet aCharSet = Versit::EUTF8CharSet);
	IMPORT_C void ExportVCalL(RWriteStream& aWriteStream, CArrayFixFlat<TAgnEntryId>* aEntryIdList, const Versit::TVersitCharSet aCharSet = Versit::EUTF8CharSet);
public:
	HBufC* RestoreNotesTextL(TStreamId aStream);
	TStreamId StoreNotesTextL(const TDesC& aNotes);
	void UpdateNotesTextL(const TDesC& aNotes, TStreamId aStream);
	void DeleteNotesStreamL(TStreamId aStream);
	inline CAgnEntryModelExData& AgnEntryModelExData() const;
	static CAgnEntryModel* NewL(CAgnServFile& aAgnServerFile);

public:		// category access
	IMPORT_C TInt CategoryCountL() const;
	IMPORT_C CAgnCategory* CategoryL(TInt aIndex) const;
	IMPORT_C void AddCategoryToListL(const TDesC& aName);
	IMPORT_C void FilterCategoryL(const CAgnCategory& aCategory, CArrayFixSeg<TAgnEntryId>& aEntries, MAgnProgressCallBack* aCallBack, TCategoryStepSize aStepSize = ECategoryStepSizeMedium);

	IMPORT_C void DeleteCategoryL(const CAgnCategory& aCategory, MAgnProgressCallBack* aCallBack, TCategoryStepSize aStepSize = ECategoryStepSizeMedium);
	IMPORT_C void RenameCategoryL(const CAgnCategory& aCategory, const TDesC& aNewName, MAgnProgressCallBack* aCallBack, TCategoryStepSize aStepSize = ECategoryStepSizeMedium);
	
	void StartCategoryTaskL(TActiveAction aTask, const CAgnCategory& aCategory, CArrayFixSeg<TAgnEntryId>* aEntries, MAgnProgressCallBack* aCallBack, TCategoryStepSize aStepSize,const TDesC& aNewName = KNullDesC);
	void GetArrayFilterL();
	void RequestProgress(TRequestStatus& aStatus);

public:
	CAgnCategoryIndex* CategoryIndex() const;
	void DoUpdateEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TBool& aHadAlarm,TCommit aCommit);
    void AsyncMessageCompleted(TInt aResult, TBool aCallBack=ETrue);
	void ReportProgress(TInt aResult);
	void BuildIndexAsyncL( MAgnProgressCallBack* aAgnObserver, TNotifyFrequency aCallBackFrequency);
	
protected: 
	void virtual Reset();		
	inline CAgnEntryModel(MAgnModelStateCallBack* aStateCallBack);
	void ConstructL();
	void ConstructL(CAgnServFile* aAgnServerFile);
	void DoOpenL(CStreamStore& aStore, TStreamId aId);
	TAgnEntryId DoAddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit,TUseExistingUniqueId aUseExistingUniqueId = EDontUseExistingUniqueId);
	void DoDeleteEntryL(CAgnEntry* aEntry,TCommit aCommit);
	void DoChangeTodoOrderL(CAgnTodoList* aTodoList,TAgnEntryId aTodoId,TAgnEntryId aTodoPositionReferenceId);
//	inline CAgnModelStreamIdSet* ModelStreamIdSet() const;
	CAgnTodoList* CreateDefaultTodoListL(const TDesC& aTodoListName);
	inline CAgnTodoListList* TodoListList();
	inline const CAgnTodoListList* TodoListList() const;
	inline CAgnDeletedTodoListList* DeletedTodoListList();
	void UpdateTodoListListL();
	void UpdateDeletedTodoListListL();
	inline void RegisterIndex(CAgnSortEntryTable* aIndex);
public:
	inline CAgnEntryStore* EntryStore(); 
	//changed from protected to public to address def051980
	//where it is needed in CAgnIndexedModel::TidyByDateCompleted an CAgnIndexedModel::TidyByTodoListCompleted
	void UpdateNextUniqueEntryIdL();
protected:
	inline const CAgnEntryStore* EntryStore() const;
	inline const TAgnTodoListStore& TodoListStore() const;
	inline TAgnTodoListStore& TodoListStore();	
	TAgnTodoListId DoAddTodoListL(CAgnTodoList* aTodoList,TInt aPosition);
	void DoUpdateTodoListL(CAgnTodoList* aTodoList);
	void DoDeleteTodoListL(CAgnTodoList* aTodoList);
	void DoChangeTodoListOrderL(TInt aOldPosition,TInt aNewPosition);
	TStreamId DoSaveTodoListsL(CStreamStore& aStoreToSaveTo);
#ifndef SYMBIAN_REMOVE_COREAPPS_API_V1
	virtual TInt DoStepL(); // inherited from  MAgnActiveStep
	virtual void StepCompleted(TInt aError); // inherited from MAgnActiveStep
#else
	void StepCompleted(TInt aError);
#endif //SYMBIAN_REMOVE_COREAPPS_API_V1

#ifndef SYMBIAN_HIDE_COREAPPS_API_V1
	void SetUpSaveAsL(CStreamStore& aStoreToSaveTo,TStreamId& aStreamIdOfOtherModel/*,const TDesC& aDefaultTodoListName*/);
	TInt DoSaveAsStepL();
	void SaveAsCompleted(TInt aError);
#endif //SYMBIAN_HIDE_COREAPPS_API_V1


	void EnteringBlockedState(TInt aAction);
	void ExitingBlockedState(TState aState = EOk);
	void SetReplicatedEntryAsDeleted(CAgnEntry* aEntry);

	void ExternalizeEntryStoreL();
	CAgnEntry* FetchEntryFromServerL(TAgnEntryId aId) const;
	void PopulateMonthOfDayListsL(TAgnDate aStartDate,TAgnDate aEndDate,TAgnDate aToday,TAgnFilter& aFilter,CArrayFixFlat<TAgnSortInstance>** aDayList) const;
	void PopulateSymbolInstanceListFromDayListL(TAgnDate aToday,TAgnDate aStartDate,CAgnSymbolList* aList,CArrayFixFlat<TAgnSortInstance>** aDayList) const;
	void RefreshTodoListListL();
	void UpdateAlarmListL(CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,CArrayFixFlat<TAgnSortInstance>* aDayInfoList,
										TAgnDate aCurrentDate, const TAgnDateTime& aNow,TAgnDateTime& aNextAlarm);
	void AddToAlarmListL(CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,CArrayFixFlat<TAgnSortInstance>* aDayInfoList, const TAgnDateTime& startDateTime,
					const TAgnDateTime& endDateTime);
	void BuildTodoListsL();

	void SetupAsyncOperationL(MAgnProgressCallBack* aAgnObserver);
	TRequestStatus& GetAsyncOperationReqStatus();
	void StartAsyncOperationProgressNotificationL(TNotifyFrequency aCallBackFrequency);
	
private:
	void TaskCompleted(TInt aError);
	TBool AcceptAlarm(const CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,const TAgnSortInstance aSortInstance);
//data-caging related
public:
	IMPORT_C void GetDefaultFileNameL(TDes& aDes); 
	IMPORT_C void DeleteAgendaFileL(const TDesC& aFileName) const;
	IMPORT_C void SecureSaveTodoListsL(const TDesC& aFileName) const;
	IMPORT_C CDesCArray* ListAgendaFilesL() const;
	IMPORT_C TBool AgendaFileExistsL(const TDesC& aFileName) const;

protected:

	class TTodoListMapItem  
	/**
	@internalComponent
	@released
	*/
		{  
	public:	
		TAgnTodoListId	iOldId;
		TAgnTodoListId	iNewId;
		TBool			iTodoListCreated;
		};
 
	TInt									iActiveAction;
	MAgnModelStateCallBack*					iStateCallBack;
	MAgnProgressCallBack*					iProgressCallBack;
	CArrayFixFlat<TTodoListMapItem>*		iTodoListMap; 
	CAgnEntryModel*							iOtherModel;
#ifndef SYMBIAN_HIDE_COREAPPS_API_V1
	CAgnFileActive*							iActive;
#else
	TAny*									iReserved;
#endif

	TAgnEntryIter*							iEntryIter;	
	TBool									iThereAreEntriesToProcess;
	TInt									iNumStreamsProcessed; 
	TKeyArrayFix							iTodoListMapKey;
private:
	TState									iState;
	CAgnTodoListList*						iTodoListList;	
	CAgnDeletedTodoListList*				iDeletedTodoListList; 
	CAgnModelStreamIdSet*					iModelStreamIdSet;
	CAgnEntryStore* 						iEntryStore;  
	TAgnTodoListStore						iTodoListStore; 
	CStreamStore*							iStreamStore;
	CAgnSortEntryTable*						iRegisteredIndex;
	CAgnAlarm*								iRegisteredAlarm;
	TTimeIntervalMinutes					iDefaultEventDisplayTime;
	TTimeIntervalMinutes					iDefaultAnnivDisplayTime;
	TTimeIntervalMinutes					iDefaultDayNoteDisplayTime;
	CParaFormatLayer*						iParaFormatLayer;
	CCharFormatLayer*						iCharFormatLayer;
	MPictureFactory*						iPictureFactory;
	TUint									iNextUniqueIdValue;
	TSaveAsCallBackFrequency				iSaveAsCallBackFrequency;
	CAgnObsController*						iObserverController;
	TAgnUniqueId							iUniqueIdOfLastCutEntry;
	TAgnEntryId								iEntryIdOfLastCutEntry;

	// These are not used and only left in for BC: deprecated
	TAny*								iIndexBuildAppt;
	TAny*								iIndexBuildEvent;
	TAny*								iIndexBuildAnniv;
	TAny*								iIndexBuildTodo;

	CAgnSortEntryTable*						iModelIndex;
	CAgnGlobalIdIndex*						iGlobalIdIndex;
	CAgnUniqueIdIndex*						iUniqueIdIndex;
	CAgnTodoListIdIndex*					iTodoListIdIndex;
	CAgnDeletedIndex*						iDeletedIndex;
	RAgendaServ*							iAgnServer;
	TModelMode								iMode; // Client, Server, None
	CAgnCategoryIndex*						iCategoryIndex;
#ifndef SYMBIAN_COREAPPS_PLUGIN_API_V2
	MAgnVersit*                             iVCalConverter;
#else
	CAgnVersit*                             iVCalConverter;
#endif
	RFs                                     iFs;
	RLibrary                                iLibrary;
	TBool									iDllLoadFailed;
private:
	void LoadDllL();
	IMPORT_C virtual void CAgnEntryModel_Reserved1();
	IMPORT_C void Stub1();
	static CAgnEntryModel* NewL(CAgnServFile* aAgnServerFile, MAgnModelStateCallBack* aStateCallBack);

private:	
	CAgnEntryModelExData* iAgnEntryModelExData;
#ifndef SYMBIAN_COREAPPS_PLUGIN_API_V2
private:
	TInt LoadFromDriveL(TInt aDrive);
#endif
};


class CAgnIndexedModel : public CAgnEntryModel
/** Indexed agenda model. 

To access the data in an agenda file, the correct type of agenda model must 
be opened at run-time. The indexed model (CAgnIndexedModel) is opened as an 
intermediate stage in opening the instance model (CAgnModel). It can also 
be used in its own right for greater efficiency by applications which have 
no user interface and which need to access only a subset of the data in the 
file.

When an indexed model is opened, it builds indexes of the data in an agenda 
file, which allows the information to be filtered before entries are read.

An index is an array of sort entries (CAgnSortEntry). The main index class 
is CAgnSortEntryTable, which owns a number of specific entry type indexes. 
CAgnSortEntryTable filters entries when they are added to the model, to find out 
which other indexes they should go into.

The indexed model enables merging and tidying. Merging means 
adding the entries and to-do lists contained in one agenda file into another 
file. Tidying causes a subset of a file's entries or to-do lists to be deleted, 
moved or copied to another file. Tidying and merging can be prolonged operations, 
so an active object and callbacks are used. 
@publishedAll
@released
*/
	{
public:
	/** Callback frequency for OpenL() */
	enum TOpenCallBackFrequency
				{
				/** High callback frequency. */
				EOpenCallBackHigh=1,
				/** Medium callback frequency. */
				EOpenCallBackMedium=2,
				/** Low callback frequency. */
				EOpenCallBackLow=4
				};
	/** Callback frequency for MergeL() */
	enum TMergeCallBackFrequency
				{
				/** High callback frequency. */
				EMergeCallBackHigh=1,
				/** Medium callback frequency. */
				EMergeCallBackMedium=2,
				/** Low callback frequency. */
				EMergeCallBackLow=4
				};
	/** Callback frequency for TidyByDateL(). */
	enum TTidyByDateCallBackFrequency
				{
				/** High callback frequency. */
				ETidyByDateCallBackHigh=16,
				/** Medium callback frequency. */
				ETidyByDateCallBackMedium = 24,
				/** Low callback frequency. */
				ETidyByDateCallBackLow=48
				}; 
	/** Callback frequency for TidyByTodoListL(). */
	enum TTidyByTodoListCallBackFrequency
				{
				/** High callback frequency. */
				ETidyByTodoListCallBachHigh=1,
				/** Medium callback frequency. */
				ETidyByTodoListCallBackMedium=2,
				/** Low callback frequency. */
				ETidyByTodoListCallBackHow=3
				};
	/** Specifies whether to-do list settings should be replaced or retained 
	during merges. */
	enum TMergeTodoListSettings
				{
				/** Overwrites the settings for to-do lists in the target model with the settings 
				for to-do lists with the same name in the source model. */
				EMergeTodoListSettings,
				/** Retains the settings for to-do lists in the target model. */
				EDontMergeTodoListSettings
				};

	/** Defines the types of tidy operation. */
	enum TTidyDirective	
				{
				/** Deletes entries from the current model when tidying */
				EDelete,
				/** Copies entries to a file */
				ECopy,
				/** Copies entries to a file and deletes from the current file */
				ECopyAndDelete
				};

	/** Defines which to-do entries to tidy. */
	enum TTidyTodoListHow
				{
				/** Tidies all to-do entries. */
				EAll,
				/** Tidies only crossed-out to-do entries. */
				ECrossedOut,
				/** Tidies all to-do entries except crossed-out ones. */
				EExceptCrossedOut
				};
							
						
	IMPORT_C static CAgnIndexedModel* NewL(MAgnModelStateCallBack* aStateCallBack);
	static CAgnIndexedModel* NewL(CAgnServFile& aAgnServerFile,
								  MAgnModelStateCallBack* aStateCallBack);

	IMPORT_C virtual ~CAgnIndexedModel();

	IMPORT_C TBool OpenL(const TDesC& aFileName,
						TTimeIntervalMinutes aDefaultEventDisplayTime,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime,
						MAgnProgressCallBack* aProgressCallBack,
						TBool aOpenSynchronously = EFalse,
						TOpenCallBackFrequency aCallBackFrequency = EOpenCallBackMedium);

	IMPORT_C void OpenL(const TDesC& aFileName,
						TTimeIntervalMinutes aDefaultEventDisplayTime,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime);


	IMPORT_C TBool BuildIndexL(MAgnProgressCallBack* aProgressCallBack,
						TBool aOpenSynchronously = EFalse,
						TOpenCallBackFrequency aCallBackFrequency = EOpenCallBackMedium);

#ifndef SYMBIAN_HIDE_COREAPPS_API_V1

	IMPORT_C TBool MergeL(CStreamStore& aStoreToMergeFrom,
						TStreamId aSrcStreamId,
						MAgnProgressCallBack* aProgressCallBack,
						TMergeTodoListSettings aMergeSettings = EDontMergeTodoListSettings,
						TMergeCallBackFrequency aCallBackFrequency = EMergeCallBackHigh); 

	inline TBool TidyByDateL(const TAgnFilter& aFilter,
						const TTime& aTodaysDate,
						const TTime& aStartDate,
						const TTime& aEndDate,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						CStreamStore* aStoreToTidyTo);

	IMPORT_C TBool TidyByDateL(const TAgnFilter& aFilter,
						const TTime& aTodaysDate,
						const TTime& aStartDate,
						const TTime& aEndDate,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						CStreamStore* aStoreToTidyTo,
						TStreamId& aStoreStreamId,
						TTidyByDateCallBackFrequency aCallBackFrequency = ETidyByDateCallBackMedium);

	inline TBool TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,
						CStreamStore* aStoreToTidyTo);

	IMPORT_C TBool TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,
						CStreamStore* aStoreToTidyTo,
						TStreamId& aStoreStreamId,
						TTidyByTodoListCallBackFrequency aCallBackFrequency = ETidyByTodoListCallBackMedium);

#endif //SYMBIAN_HIDE_COREAPPS_API_V1

	IMPORT_C void TidyByTodoListL(
						const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,
						const TDesC& aNameOfFileToTidyTo,
						TNotifyFrequency aReporter=CAgnEntryModel::ENoProgress);
	IMPORT_C void TidyByDateL(
						const TAgnFilter& aFilter,
						const TTime& aTodaysDate,
						const TTime& aStartDate,
						const TTime& aEndDate,
						MAgnProgressCallBack* ProgressCallBack,
						TTidyDirective aDirective,
						const TDesC& aNameOfFileToTidyTo, 
						TNotifyFrequency aReporter=CAgnEntryModel::ENoProgress);
	IMPORT_C TBool TidyByDateL(
						const TAgnFilter& aFilter,
						const TTime& aTodaysDate,
						const TTime& aStartDate,
						const TTime& aEndDate,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective);
	IMPORT_C TBool TidyByTodoListL(
						const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective,
						TTidyTodoListHow aTidyHow);
	IMPORT_C TInt EntryCount() const;
	IMPORT_C TAgnLiteEntry GetLiteEntryL(TAgnEntryId aId) const;
	IMPORT_C TInt IndexCount(TInt aIndexNumber) const;
	// Don't use Indexes() - use RegisteredIndex() instead.
	inline CAgnSortEntryTable* Indexes() const;

	// Server interface.
	void ServerTidyByTodoListBeginL(const CArrayFixFlat<TAgnTodoListId>* aList,
									TTidyDirective aDirective,
									TTidyTodoListHow aTidyHow,
									CStreamStore* aStoreToTidyTo,
									TStreamId& aStoreStreamId,
									TTidyByTodoListCallBackFrequency aCallBackFrequency = ETidyByTodoListCallBackMedium);
	void ServerTidyByTodoListCompleted(TInt aErr);
	TBool ServerTidyByDateBeginL(const TAgnFilter& aFilter,
								 const TTime& aTodaysDate,
								 const TTime& aStartDate,
								 const TTime& aEndDate,
								 TTidyDirective aDirective,
								 CStreamStore* aStoreToTidyTo, 
								 TStreamId& aStoreStreamId,
								 TTidyByDateCallBackFrequency aTidyCallBackFrequency = ETidyByDateCallBackMedium);
	TInt DoTidyByDateStepL();
	void TidyByDateCompleted(TInt aError);
	void TidyByTodoListCompleted(TInt aError);

protected:
	enum TIndexedActiveAction {ELoad=ECompact+1,EMerge=ECompact+2,ETidyByDate=ECompact+3,ETidyByTodoList=ECompact+4, ECategoryDelete=ECompact+5,ECategoryRename=ECompact+6,ECategoryFilter=ECompact+7, ECategoryGetArrayFilter=ECompact+8};

	inline CAgnIndexedModel(MAgnModelStateCallBack* aStateCallBack);
	void ConstructL(CAgnServFile* aAgnServerFile = NULL);

#ifndef SYMBIAN_REMOVE_COREAPPS_API_V1
	virtual TInt DoStepL(); 
	virtual void StepCompleted(TInt aError);
#endif
	
	void virtual Reset();

#ifndef SYMBIAN_HIDE_COREAPPS_API_V1
private:
	TInt DoLoadStepL();
	void LoadCompleted(TInt aError);
	void SetUpMergeL(CStreamStore& aStoreToMergeFrom,TStreamId aSrcStreamId);
	TInt DoMergeStepL();
	void MergeEntriesStepL();
	void MergeTodoListsStepL();
	void MergeCompleted(TInt aError);
#endif

private:
	TBool SetUpTidyByDateL(const TAgnFilter& aFilter,const TTime& aTodaysDate,CStreamStore* aStoreToTidyTo,TStreamId& aStoreStreamId,TTidyDirective aDirective/*,const TDesC& aDefaultTodoListName*/);
	void DeleteTidiedEntriesL();
	TBool IsEntryValidToTidy(const CAgnSortEntry* aSortEntry);
	void SetUpTidyByTodoListL(CStreamStore* aStoreToTidyTo,TStreamId& aStoreStreamId,TTidyDirective aDirective/*,const TDesC& aDefaultTodoListName*/);
public:
	TInt DoTidyByTodoListStepL();
private:
	void TidyEntryL(CAgnSortEntry* aSortEntry,TAgnDate aStartDate,TAgnDate aEndDate);
	TBool CheckDateIteratorEnd(TAgnDate& aKey);
	IMPORT_C /*virtual*/ void CAgnEntryModel_Reserved1();
	IMPORT_C void Stub2();

private:
	class TStreamIdKey : public TKeyArrayFix
		{
	public:
		inline TStreamIdKey(): TKeyArrayFix(0,ECmpTUint32){};
		virtual TInt Compare(TInt aLeft,TInt aRight) const;	
		};
	TOpenCallBackFrequency					iOpenCallBackFrequency;
	TMergeCallBackFrequency					iMergeCallBackFrequency;
	TInt									iTidyCallBackFrequency;
	// Don't use iIndexes - use RegisteredIndex() instead.
	CAgnSortEntryTable*						iIndexes;
	CAgnTodoListNames*						iTodoListNames;
	CArrayFixFlat<TAgnEntryId>*				iPossibleMergeMatches; 
	CArrayFixFlat<TAgnEntryId>*				iTidyDeleteArray; 
	CArrayFixFlat<TAgnEntryId>*				iAlreadyTidied;
	CArrayFixFlat<TAgnEntryId>*				iAlreadyTidiedForDay;
	TAgnEntryDateIterator*					iTidyIter;
	TAgnDate								iTidyStartDate;
	TAgnDate								iTidyEndDate;
	TAgnDate								iTidyDate;
	TAgnDate								iTodaysDate;
	TTidyDirective							iTidyDirective;
	TInt									iNumEntriesProcessed;
	TInt									iNumEntriesToProcess;
	TAgnEntryInfoFilter						iTidyInfoFilter;
	TInt									iTidyTodoListIndex;	
	TTidyTodoListHow						iTidyTodoListsHow;
	const CArrayFixFlat<TAgnTodoListId>*	iTidyTodoListIds;
	TMergeTodoListSettings					iMergeTodoListSettings;	
	CAgnAppt*								iAppt;
	CAgnEvent*								iEvent;
	CAgnAnniv*								iAnniv;
	CAgnTodo*								iTodo;
	};


class CAgnModel : public CAgnIndexedModel
/** The instance agenda model.

This should be used by applications which have a user interface. In 
the entry model, a repeating entry is represented as a single entry 
with a set of repeat details. However, for a user interface, a repeating 
entry needs to be presented to the user as multiple instances, one on 
each date on which a repeat occurs.

A view should generally deal with instances not entries. It should never call 
UpdateEntryL() or DeleteEntryL() and will very rarely (if at all) call FetchEntryL(). 
Instead, it should use the instance model and call UpdateInstanceL(), DeleteInstanceL() 
or FetchInstanceL(). An exception to this is when a new entry is added to 
the agenda model. Because it does not have an instance date at this point, 
the function is called AddEntryL(). 
@publishedAll
@released
*/
	{
public:
	IMPORT_C static CAgnModel* NewL(MAgnModelStateCallBack* aStateCallBack);

	IMPORT_C CAgnEntry* FetchInstanceL(const TAgnInstanceId& aInstanceId) const; // fetch an instance i.e. an entry with an instance date	
	IMPORT_C CAgnEntry* FetchInstanceLC(const TAgnInstanceId& aInstanceId) const;

	IMPORT_C TAgnEntryId AddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());
	IMPORT_C TAgnEntryId UpdateInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances=EAllInstances,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId()); 
	IMPORT_C TAgnEntryId DeleteInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances=EAllInstances);	
	IMPORT_C TAgnEntryId DeleteInstanceL(const TAgnInstanceId& aInstanceId,TAgnWhichInstances aWhichInstances=EAllInstances);
	IMPORT_C TAgnEntryId CutInstanceL(const TAgnInstanceId& aInstanceId,TAgnWhichInstances aWhichInstances=EAllInstances);
	IMPORT_C TAgnEntryId CutInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances=EAllInstances);


	IMPORT_C virtual TAgnTodoListId AddTodoListL(CAgnTodoList* aTodoList,TInt aPosition=EAddTodoListAtEnd);
	IMPORT_C virtual void DeleteTodoListL(CAgnTodoList* aTodoList);  
	IMPORT_C virtual void DeleteTodoListL(TAgnTodoListId aTodoListId);
	IMPORT_C virtual void UpdateTodoListL(CAgnTodoList* aTodoList);

	IMPORT_C void PopulateDayInstanceListL(CAgnDayList<TAgnInstanceId>* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateDayDateTimeInstanceListL(CAgnDayDateTimeInstanceList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateMonthInstanceListL(CAgnMonthInstanceList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateTodoInstanceListL(CAgnTodoInstanceList* aList,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateSymbolInstanceListL(CAgnSymbolList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;

	IMPORT_C TTime NextDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	IMPORT_C TTime PreviousDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;

	// Find methods
	IMPORT_C void FindNextInstanceL(CAgnDayList<TAgnInstanceId>* aMatchedInstanceList, const TDesC& aSearchText, const TTime& aStartDate, const TTime& aEndDate, const TAgnFilter& aFilter, const TTime& aToday) const;
	IMPORT_C void FindPreviousInstanceL(CAgnDayList<TAgnInstanceId>* aMatchedInstanceList, const TDesC& aSearchText, const TTime& aStartDate, const TTime& aEndDate, const TAgnFilter& aFilter, const TTime& aToday) const;
protected:
	void ConstructL();
	inline CAgnModel(MAgnModelStateCallBack* aStateCallBack);
	void NormaliseWhichInstances(const CAgnEntry* aInstance,TAgnWhichInstances& aWhichInstances) const;
	void PopulateSymbolInstanceListFromDayListL(TAgnDate aToday,TAgnDate aStartDate,CAgnSymbolList* aList,CArrayFixFlat<TAgnSortInstance>** aDayList) const;
	void PopulateMonthOfDayListsL(TAgnDate aStartDate,TAgnDate aEndDate,TAgnDate aToday,TAgnFilter& aFilter,CArrayFixFlat<TAgnSortInstance>** aDayList) const;

#ifndef SYMBIAN_REMOVE_COREAPPS_API_V1
	virtual TInt DoStepL(); 
	virtual void StepCompleted(TInt aError); 
#endif

protected:
	TAgnInstanceEditor 	iInstanceEditor;
private:
	IMPORT_C /*virtual*/ void CAgnEntryModel_Reserved1();
	};

class CAsyncWatcher : public CActive
/**
@internalComponent
@released 
*/
	{
public:
	CAsyncWatcher(TInt aPriority = EPriorityStandard) : CActive(aPriority){};
	~CAsyncWatcher(){};
	CAgnEntryModel* GetModel();
	void DoCancel(){};
	TRequestStatus& GetReqStatus();
protected:
	CAgnEntryModel* iModel;	
	};

NONSHARABLE_CLASS(CAgnAsyncServerObserver) : public CAsyncWatcher
/**
@internalComponent
@released 
*/
	{
public:
	static CAgnAsyncServerObserver* NewL();
	void StartObserverL(CAgnEntryModel& aModel);
	void SetActive();
	void CancelRequest();

private:
	void RunL();
	};

NONSHARABLE_CLASS(CAgnProgressReporter) : public CAsyncWatcher
/**
@internalComponent
@released 
*/
	{
public:
	inline void SetReport(TInt aValue);
	static CAgnProgressReporter* NewL();
	void StartReporterL(CAgnEntryModel& aModel);
//	void RequestComplete(TInt aErr);
private: 
	void RunL();
	TInt iValue;
	};

_LIT(KDefaultAgendaFileName,"Calendar");

#include "agmmodel.inl"

#endif


