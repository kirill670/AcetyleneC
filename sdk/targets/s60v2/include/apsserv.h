// APSSERV.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2004.  All rights reserved.
//

#if !defined(__APSSERV_H__)
#define __APSSERV_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__APMFNDR_H__)
#include <apmfndr.h>
#endif

#include "apgaplst.h"

// classes defined
class CApaAppListServer;
//
// classes referenced
class CApaAppList;
class CApaAppData;
class CApaFileRecognizer;
#ifndef SYMBIAN_REMOVE_UI_FRAMEWORKS_V1
class CApaScanningAppFinder;
#endif
class CApaAppRegFinder;
class CApaScanningFileRecognizer;
class CApaFsMonitor;
class CTypeStoreManager;
class MApaAppStarter;
class CApaEComMonitor;
class CBaBackupSessionWrapper;
//

// server name

/**
KAppListServerName 
@internalAll
*/
_LIT(KAppListServerName,"!AppListServer");

#ifdef __SECURE_API__
class CApaAppListServer : public CPolicyServer, public MApaAppListObserver, public MBackupOperationObserver
#else
class CApaAppListServer : public CServer2, public MApaAppListObserver, public MBackupOperationObserver
#endif
/**
CApaAppListServer 
@internalAll 
*/
	{
public:
	IMPORT_C static CApaAppListServer* NewL(CApaAppList* aAppList,CApaFileRecognizer* aRecognizer);
	inline static CApaAppListServer* NewL(MApaAppStarter& aAppStarter) {return NewL(&aAppStarter);}
	IMPORT_C static CApaAppListServer* NewL(MApaAppStarter* aAppStarter);
	IMPORT_C static CApaAppListServer* Self();
	inline CApaAppList* AppList();
	inline CApaFileRecognizer* FileRecognizer();
	inline CApaDataRecognizer* DataRecognizer();
	inline CTypeStoreManager*& TypeStoreManager();
	inline RFs& FsSession();
public: // from MApaAppListObserver
	void NotifyUpdate(TInt aReason);
	void InitialListPopulationComplete();
    // from MBackupOperationObserver
	void HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes);
	//
	IMPORT_C ~CApaAppListServer();
private:
	CApaAppListServer(TInt aPriority,CApaAppList* aAppList,CApaFileRecognizer* aRecognizer);
	void ConstructL(MApaAppStarter* aAppStarter);
	virtual CSession2* NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
	static TInt AppFsNotifyCallBack(TAny* aPtr);
	static TInt RecogFsNotifyCallBack(TAny* aPtr);
	static TInt TypeStoreNotifyCallback(TAny* aPtr);
	void UpdateApps();
	void UpdateRecogs();
	void UpdateTypeStore();
	void DoUpdateTypeStoreL();
private:
	enum {
		EOwnsFileRecognizer=0x01,
		EOwnsAppList=0x02
		};
private:
	RFs iFs;
	CApaFileRecognizer* iFileRecognizer;
	CApaAppList* iAppList;
	TInt iOwnsList;
	CApaScanningFileRecognizer* iScanningFileRecognizer;
#ifndef SYMBIAN_REMOVE_UI_FRAMEWORKS_V1
	CApaScanningAppFinder* iScanningAppFinder;
#endif
	CApaAppRegFinder* iAppRegFinder;
	CApaScanningDataRecognizer* iDataRecognizer;
	CApaFsMonitor* iAppFsMonitor;
	CApaFsMonitor* iRecogFsMonitor;
	CApaFsMonitor* iTypeStoreMonitor;
	CTypeStoreManager* iTypeStoreManager;
	TTime iTypeStoreModified;
	CBaBackupSessionWrapper* iBaBackupSessionWrapper;
	CApaEComMonitor* iRecEcomMonitor;
	};

class TApaAppViewIconSizeData
/**
The TApaAppViewIconSizeData class encapsulates the attributes that specify how to identify an icon for a particular
application and view in a certain size.

@internalComponent
*/
	{
public:
	inline TApaAppViewIconSizeData();
	inline TApaAppViewIconSizeData(TUid aAppUid,TUid aViewUid, const TSize& aSize);
public:
	TUid iAppUid;
	TUid iViewUid;
	TSize iSize;
	};

typedef TPckgBuf<TApaAppViewIconSizeData> TApaAppViewIconSizeDataBuf;

//
// inlines
//

inline TApaAppViewIconSizeData::TApaAppViewIconSizeData()
	: iAppUid(KNullUid), iViewUid(KNullUid), iSize(TSize(0,0))
	{}

inline TApaAppViewIconSizeData::TApaAppViewIconSizeData(TUid aAppUid,TUid aViewUid, const TSize& aSize)
	: iAppUid(aAppUid), iViewUid(aViewUid), iSize(aSize)
	{}

inline CApaAppList* CApaAppListServer::AppList()
	{ return iAppList; }

inline CApaFileRecognizer* CApaAppListServer::FileRecognizer()
	{ return iFileRecognizer; }

inline CApaDataRecognizer* CApaAppListServer::DataRecognizer()
	{ return iDataRecognizer; }

inline RFs& CApaAppListServer::FsSession()
	{ return iFs; }

inline CTypeStoreManager*& CApaAppListServer::TypeStoreManager()
	{ return iTypeStoreManager; }

#endif
