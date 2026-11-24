// APGCLI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APGCLI_H__)
#define __APGCLI_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif
#if !defined(__APMREC_H__)
#include <apmrec.h>
#endif
#if !defined(__APAID_H__)
#include <apaid.h>
#endif
#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

// classes referenced
class CApaCommandLine;
class CApaMaskedBitmap;
class TApaAppInfo_7_0;
class MArrayFiller;
class RFile;
//

////////////////////////////////////
// RApaLsSession
////////////////////////////////////

class RApaLsSession : public RSessionBase
/** A session with the application architecture server.

The server provides access to a cached list of the applications on the device. 

To use this class, clients first need to connect to the server. 

Then, one of GetAllApps(), GetEmbeddableApps() or GetFilteredApps() needs to be called. 
These functions do some initialisation of server data in preparation for returning the 
application list (which is owned by the server).

Then, GetNextApp() is called in a loop. The first time around, it populates the session's 
application list and retrieves the first application in the list. Further calls to GetNextApp() 
retrieve the remaining applications in the list, until RApaLsSession::ENoMoreAppsInList is 
returned.

The session should be closed when it is no longer needed, before it goes out of scope.

Various functions in RApaLsSession need to access the application list, and may return 
RApaLsSession::EAppListInvalid to indicate that the function was called before the initial 
population of the list is complete. If this occurs, you could try again after a short delay.

This class provides many other functions, for instance launching applications, querying 
application-specific information, recognising data.

@publishedAll
@released */
	{
public:
	enum {
		/** A possible return value from GetNextApp(), to indicate that there are no more 
		applications in the list. */
		ENoMoreAppsInList=1,
		/** Indicates that an RApaLsSession member function was called before the session's 
		application list is fully populated. */
		EAppListInvalid
		};
	/** Defines the way an application is launched. */
	enum TLaunchType {
		/** Launches a new instance of the application. */
		ELaunchNewApp=1,
		/** Launches a new instance of the application if no existing instance of the application 
		is running. If an instance of the application is already running, then it 
		is brought to the foreground. */
		ESwitchFiles
		};
public:
	IMPORT_C RApaLsSession();
	//
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	//
	IMPORT_C TInt AppCount(TInt& aCount) const; // returns error
	IMPORT_C TInt EmbeddableAppCount(TInt& aCount) const; // returns error
	//
	IMPORT_C TInt GetAllApps() const; // Call to initialize
	IMPORT_C TInt GetAllApps(TInt aScreenMode) const; // Call to initialize
	IMPORT_C TInt GetEmbeddableApps() const; // Call to initialize
	IMPORT_C TInt GetEmbeddableApps(TInt aScreenMode) const; // Call to initialize
	// 7.0s
	IMPORT_C TInt GetFilteredApps(const TApaEmbeddabilityFilter& aFilter) const; // Call to initialize
	IMPORT_C TInt GetFilteredApps(const TApaEmbeddabilityFilter& aFilter, TInt aScreenMode) const; // Call to initialize
	// 8.1
	IMPORT_C TInt GetFilteredApps(TUint aCapabilityAttributeMask, TUint aCapabilityAttributeValue) const; // Call to initialize
	IMPORT_C TInt GetFilteredApps(TUint aCapabilityAttributeMask, TUint aCapabilityAttributeValue, TInt aScreenMode) const; // Call to initialize
	// 9.0
	IMPORT_C TInt GetServerApps(TUid aServiceUid) const; // Call to initialize
	IMPORT_C TInt GetServerApps(TUid aServiceUid, TInt aScreenMode) const; // Call to initialize
	//
	IMPORT_C TInt GetNextApp(TApaAppInfo& aInfo) const; // call repeatedly, returns err (inc ENoMoreAppsInList,EAppListInvalid)
	IMPORT_C TInt GetNextApp(TApaAppInfo& aInfo,TInt aScreenMode) const; // call repeatedly, returns err (inc ENoMoreAppsInList,EAppListInvalid)
	//
	IMPORT_C TInt GetAppInfo(TApaAppInfo& aInfo,TUid aAppUid) const;
private:
	//
	// 7.0 Binary compatible replacement functions
	IMPORT_C TInt GetNextApp_7_0(TApaAppInfo_7_0& aInfo) const; // call repeatedly, returns err (inc ENoMoreAppsInList,EAppListInvalid)
	IMPORT_C TInt GetNextApp_7_0(TApaAppInfo_7_0& aInfo,TInt aScreenMode) const; // call repeatedly, returns err (inc ENoMoreAppsInList,EAppListInvalid)
	IMPORT_C TInt GetAppInfo_7_0(TApaAppInfo_7_0& aInfo,TUid aAppUid) const;	
public:
	IMPORT_C TInt GetAppCapability(TDes8& aCapabilityBuf,TUid aAppUid) const;
	IMPORT_C TInt StartApp(const CApaCommandLine& aCommandLine); // This is only recommended for non document based apps
	IMPORT_C TInt StartApp(const CApaCommandLine& aCommandLine,TThreadId& aId);
	//
	// ER5 additions
	IMPORT_C TInt RecognizeData(const TDesC& aName, const TDesC8& aBuffer, TDataRecognitionResult& aDataType) const;
	IMPORT_C TInt RecognizeSpecificData(const TDesC& aName, const TDesC8& aBuffer, const TDataType& aDataType, TBool& aResult) const;
	//
	IMPORT_C TInt AppForDataType(const TDataType& aDataType, TUid& aAppUid) const;
	IMPORT_C TInt StartDocument(const TDesC& aFileName, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	IMPORT_C TInt StartDocument(const TDesC& aFileName, const TDataType& aDataType, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	IMPORT_C TInt StartDocument(const TDesC& aFileName, TUid aAppUid, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	IMPORT_C TInt CreateDocument(const TDesC& aFileName, TUid aAppUid, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	//
	IMPORT_C TInt GetAppIcon(TUid aAppUid, TInt aSize, CApaMaskedBitmap& aAppBitmap) const;
	//
	IMPORT_C TInt AppForDocument(const TDesC& aFileName, TUid& aUid, TDataType& aDataType) const;
	IMPORT_C TInt IsProgram(const TDesC& aFileName, TBool& aProgram) const;
	IMPORT_C TInt GetAcceptedConfidence(TInt& aConfidence) const;
	IMPORT_C TInt SetAcceptedConfidence(TInt aConfidence);
	IMPORT_C TInt GetMaxDataBufSize(TInt& aBufSize) const;
	IMPORT_C TInt SetMaxDataBufSize(TInt aBufSize);
	IMPORT_C TInt GetSupportedDataTypesL(CDataTypeArray& aDataTypes) const;
	//
	// ER6 Additions
	IMPORT_C TInt GetAppIconSizes(TUid aAppUid, CArrayFixFlat<TSize>& aArrayToFill) const;
	IMPORT_C TInt GetAppIcon(TUid aAppUid, TSize aSize, CApaMaskedBitmap& aAppBitmap) const;
	// ER6.1
	IMPORT_C TInt GetAppViews(CApaAppViewArray& aAppViews, TUid aAppUid) const;
	IMPORT_C TInt GetAppViewIcon(TUid aAppUid, TUid aViewUid, const TSize& aSize, CApaMaskedBitmap& aViewBitmap) const;
	IMPORT_C TInt GetAppOwnedFiles(CDesCArray& aAppOwnedFiles, TUid aAppUid) const;
	// 7.0s
	IMPORT_C TInt NumberOfOwnDefinedIcons(TUid aAppUid, TInt& aCount) const;
	// 8.1
	IMPORT_C TInt GetAppIcon(TUid aAppUid, HBufC*& aFullFileName) const;
	IMPORT_C TInt GetAppViewIcon(TUid aAppUid, TUid aViewUid, HBufC*& aFullFileName) const;
	IMPORT_C TInt InsertDataMapping(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid);
	IMPORT_C TInt InsertDataMappingIfHigher(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid, TBool& aInserted);
	IMPORT_C TInt DeleteDataMapping(const TDataType& aDataType);
	IMPORT_C TInt StartDocument(const TDesC& aFileName, RFs& aFSession, RFile& aFile, TThreadId& aThreadId);
	// 9.0
	IMPORT_C CApaAppServiceInfoArray* GetAppServicesLC(TUid aAppUid) const;
	IMPORT_C CApaAppServiceInfoArray* GetServiceImplementationsLC(TUid aServiceUid) const;
	IMPORT_C void GetAppServicesL(TUid aAppUid, CArrayFixFlat<TUid>& aServiceUids) const;
	IMPORT_C CApaAppServiceInfoArray* GetAppServiceOpaqueDataLC(TUid aAppUid, TUid aServiceUid) const;
	IMPORT_C TInt AppForDataTypeAndService(const TDataType& aDataType, TUid aServiceUid, TUid& aAppUid) const;
	IMPORT_C TInt AppForDocumentAndService(const TDesC& aFileName, TUid aServiceUid, TUid& aAppUid, TDataType& aDataType) const;
	IMPORT_C TInt AppForDocumentAndService(const TDesC& aFileName, RFs& aFSession, RFile& aFile, TUid aServiceUid, TUid& aAppUid, TDataType& aDataType) const;
	// 9.1
	IMPORT_C TInt ApplicationLanguage(TUid aAppUid, TLanguage& aLanguage) const;

public:
	// internal to the DLL
	void CancelNotify() const;
	void SetNotify(TRequestStatus& aStatus);
private:
	void DoGetAppOwnedFilesL(CDesCArray& aArrayToFill, TUid aAppUid) const;
	void DoGetAppViewsL(CApaAppViewArray& aArrayToFill, TUid aAppUid) const;
	void DoGetAppIconSizesL(TUid aAppUid, CArrayFixFlat<TSize>& aArrayToFill) const;
	TInt DoAppCount(TInt& aCount,TInt aCommand) const;
	void FetchArrayL(MArrayFiller& aArrayFiller,TUid aAppUid, TInt aOpcode, TInt aInitialBufSize) const;
	CBufBase* GetServiceBufferLC(TInt aOpcode, TUid aUid1, TUid aUid2=KNullUid) const;
	TInt StartAndCreate(TInt aRqst,const TDesC& aFileName, TUid aAppUid, TThreadId& aId, TLaunchType aLaunchType);
	TInt ReconnectToServer(TInt aErr,TBool& aTriedOnce) const;
	TInt SendReceiveWithReconnect(TInt aFunction,const TIpcArgs& aIpcArgs) const;
	TInt StartApplication(const CApaCommandLine& aCommandLine,TThreadId* aThreadId);
	};


#endif

