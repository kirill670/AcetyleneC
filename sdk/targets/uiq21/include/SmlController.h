//
// smlController.h
//

#ifndef __SMLCONTROLLER_H__
#define __SMLCONTROLLER_H__

#include <SmlEngineDefines.h>

// forward declarations
class MSmlReportingCallback;
class CSmlSettings;
class CSmlProfile;
class CSmlEngine;
class CSmlDataStore;

// sync methods
enum TSmlSyncMethods
{
	ESmlManual,
	ESmlScheduled
};

// typedef for Identifier arrays
typedef const RPointerArray<const CSmlIdentifier>& RSmlIdentifierArray;

// errors
const TInt KErrNoTasks = (-8000);
const TInt KErrSyncInProgress = (-8001);

/**

The TSyncInfo class holds information about a synchronisation

*/
class TSyncInfo
{
	friend class CSmlController;
public:
	TSyncInfo() : iMethod(ESmlManual), iTime(Time::NullTTime()), iStatus(KErrNone){};

	inline TInt Method() const { return iMethod; };
	inline const TTime& Time() const { return iTime; };
	inline TInt Status() const { return iStatus; };

	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);

private:
	TInt iMethod;
	TTime iTime;
	TInt iStatus;
};


/**

The CSmlController class is resposible for:
1. starting & stopping synchronisations, either manually or scheduled
2. creating and managing the data for tasks, including their synchronisation history information
3. Exposing server synchronisation settings, and manage them on a profile basis
4. Exposing Content Provider data filter settings on a task basis (not implemented for v1.0)
5. Allowing a client to register progress and error callbacks
6. Processing asynchronous message requests from client engine calls to the toolkit
7. Returning opaque data from ecom resource files fo the DBA
*/
class CSmlController : public CActive
{
public:
	IMPORT_C static CSmlController* NewL(MSmlReportingCallback* aCallback, TBool aOffline = EFalse);
	IMPORT_C static CSmlController* NewLC(MSmlReportingCallback* aCallback, TBool aOffline = EFalse);

	virtual ~CSmlController();

	IMPORT_C TInt SynchroniseL(TSmlAlertCodes aSyncType = ESmlAlertTwoWaySync);
	IMPORT_C TInt SynchroniseL(const CSmlIdentifier& aProfileId, TSmlAlertCodes aSyncType = ESmlAlertTwoWaySync);
	IMPORT_C void ServerAlertedSyncL(const TDesC& aMessage);
	IMPORT_C void StopSyncL();

	IMPORT_C void UpdateFilterSettingsL(const CSmlIdentifier& /*aId*/, CSmlSettings& /*aSettings*/);
	IMPORT_C void GetFilterSettingsL(const CSmlIdentifier& /*aId*/, CSmlSettings& /*aSettings*/) const;

	IMPORT_C RSmlIdentifierArray ListContentProvidersL();
	IMPORT_C RSmlIdentifierArray ListProtocolsL();

	IMPORT_C void LastSync(TSyncInfo& aLastSync) const;
	IMPORT_C void NextSyncL(TSyncInfo& aNextSync) const;

	IMPORT_C RSmlIdentifierArray ListProfiles() const;
	IMPORT_C void GetProfileL(const CSmlIdentifier& aId, CSmlProfile& aProfile);
	IMPORT_C void GetDefaultProfileL(CSmlProfile& aProfile);
	IMPORT_C void CreateProfileL(CSmlProfile& aProfile);
	IMPORT_C void UpdateProfileL(CSmlProfile& aProfile);
	IMPORT_C void DeleteProfileL(const CSmlIdentifier& aId);
	
	IMPORT_C void SetActiveProfileL(const CSmlIdentifier& aId);
	IMPORT_C const CSmlIdentifier& ActiveProfile();

	IMPORT_C void GetProviderFileTypeL(const CSmlIdentifier& aProvider, TUidType& aType);
	IMPORT_C HBufC8* ProviderProprietaryDataL(const CSmlIdentifier& aProvider);
	IMPORT_C void CreateProviderFileL(const CSmlIdentifier& aProvider, const TDesC& aFile);
	IMPORT_C TBool DoesDatabaseExistL(const CSmlIdentifier& aProvider, const TDesC& aDatabase);

	TBool IsValidContentProvider(const CSmlIdentifier& aId);
	TBool IsValidProtocol(const CSmlIdentifier& aId);
	TBool IsValidProfile(const CSmlIdentifier& aId);
	TBool IsValidProfileName(const TDesC& aName);

	CSmlTask* LoadTaskLC(TUint aTaskId, const CSmlProfile* aProfile);
	void GetTaskIdL(CSmlTask& aTask);
	RSmlIdentifierArray ListContentProviders();

private:
	CSmlController(MSmlReportingCallback* aCallback, TBool aOffline);
	void ConstructL();

	virtual void RunL();
	virtual void DoCancel();
	virtual TInt RunError(TInt aError);
	
	TBool FileExists(const TDesC& aFilename);
	void PopulateContentProvidersListL();
	void PopulateProtocolsListL();
	void PopulateProfilesListL();

	HBufC8* GetOpaqueDataLC(const CSmlIdentifier& aId);
	void UpdateProfileNameL(const CSmlIdentifier& aId);

	void GetIDStreamIDsL(TStreamId& aProfiles, TStreamId& aData) const;
	CSmlProfile* CreateDefaultProfileLC(const TStreamId& aId);
	
	void CreateControllerFileL(const TDesC& aFilename);
	void SaveProfileToStoreL(const CSmlProfile& aProfile);
	void DeleteProfileFromStoreL(const CSmlIdentifier& aId);
	void UpdateProfileIdsStreamL();
	void SaveTasksL(CSmlProfile& aProfile, RPointerArray<CSmlDataStore>& aTaskStores);
	void SaveTaskL(const CSmlTask* aTask, CSmlDataStore* aStore);	// creates/updates a task store 
	void DeleteTaskL(const CSmlTask* aTask);	// deletes the store, including the sync anchor information
	TUint CreateTaskId(TUint aSource, TUint aTarget) const;	// creates a task Id from 2 Ids
	void ResolveTaskId(TUint aId, TUint& aSource, TUint& aTarget) const;	// splits the Id into 2
	void GetNextIdsL(TUint& aSource, TUint& aTarget);
	void SaveDataL();
	void LoadDataL();

	TInt SendTaskInfoL();
	void CallEventHandler(TInt aErr = KErrNone);
	void CleanupFromSyncL(TInt aError, TBool aLog = ETrue);
	void ResetData();
	TInt EmulateSync(MSmlReportingCallback* aCallback);

	enum TSyncState 
	{
		EIdle,
		EReadyToStart,
		EConnected,
		ECompleteTask,
		EFinished,
		EDisconnecting,
		EDisconnected,		
	};

// data
	RFs iFs;												 // filestore session
	CPermanentFileStore* iStore;							 // the filestore
	RPointerArray<const CSmlIdentifier> iContentProviders;	 // list of all syncML synchronisable apps
	RPointerArray<const CSmlIdentifier> iProtocols;			 // list of all protocols that can be used with syncML
	RPointerArray<const CSmlIdentifier> iProfiles;			 // list of valid profiles
	TUint iNextSourceId;
	TUint iNextTargetId;
	TSyncInfo iLastSync;
	TUint iActiveProfile;									 // the active profile to use for a Sync
	CSmlEngine* iSmlEngine;
	TSyncState iSyncState;									 // the current syncState
	CSmlProfile* iSyncProfile;								 // holds the profile object during a sync
	TInt iCurrentTask;										 // holds the index of the current task during a sync
	MSmlReportingCallback* iCallback;						 // UI callback
	TBool iOffline;											 // run controller offline
	TSmlAlertCodes iSyncType;								 // type of sync
};

#endif // __SMLCONTROLLER_H__