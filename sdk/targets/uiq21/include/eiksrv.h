// EIKSRV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSRV_H__)
#define __EIKSRV_H__

#include <eikappui.h>
#include <eikenv.h>
#include <apgtask.h>
#include <vwsappst.h>
#include <eikunder.h>

class CEikServAppUiBase;
class CDictionaryFileStore;
class CEikServStatusPane;
class CVwsSessionWrapper;
class CEikServExtra;

enum TEikAppUiServPanic
	{
	EEikSrvDefault,
	EEikSrvSvrCreateServer, // no longer used
	EEikSrvSvrStartServer,
	EEikSrvSrvNotFound,
	EEikSrvBadDescriptor,
	EEikSrvIllegalError,
	};

class TServerStart
	{
public:
	TServerStart(TRequestStatus& aStatus);
	TPtrC AsCommand() const;
//
	TServerStart();
	TInt GetCommand();
	void SignalL();
private:
	TThreadId iId;
	TRequestStatus* iStatus;
	};

class CEikServAppUiSession;

class CEikServAppUiServer :public CServer
	{
	friend class CEikServAppUiSession;
public:
	enum {EPriority=EPriorityAbsoluteHigh};
	IMPORT_C static CEikServAppUiServer* NewL();
	virtual CSharableSession* NewSessionL(const TVersion &aVersion) const;
	static TInt ThreadFunction(TAny* aStarted);
private:
	CEikServAppUiServer(TInt aPriority=EPriority);
	void ConstructL();
private:
	CEikServAppUiBase* iAppUi;
	};

class CEikServAppUiSession : public CSession
	{
public:
	 CEikServAppUiSession(RThread aClient, CEikServAppUiServer * aServer);
	 static CEikServAppUiSession* NewL(RThread aClient, CEikServAppUiServer * aServer);
	~CEikServAppUiSession();
	virtual void ServiceL(const RMessage &aMessage);
	void Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset=0);
private:
	void PanicClient(TEikAppUiServPanic aCode);
protected:
	CEikServAppUiServer* iAppUiServer;
	TBool iScreenBlanked;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CEikPasswordModeCategory : public CBase
	{
public:
	IMPORT_C static CEikPasswordModeCategory* NewLC(RFs& aFs);
	IMPORT_C ~CEikPasswordModeCategory();
	IMPORT_C void GetPasswordModeL(TPasswordMode& aMode) const; 
	IMPORT_C void SetPasswordModeL(TPasswordMode aMode);
private:
	CEikPasswordModeCategory();
	void ConstructL(RFs& aFs);
private:
	CDictionaryFileStore* iStore;
	};

//
// CEikServAppUiBase
//

class CEikServNotifyServer;
class CNotifierServerExtended;
class CEikServBackupServer;
class CEikServAlarmAlertServer;
class CEikKeyWindow;
class CEikUndertaker;
class CEikPasswordControl;
class CEikTaskListDialog;
class MEikServNotifyAlert;
class MEikServAlarmFactory;
class CEikServDllClose;
class CEikServBlankWin;

/**
 * @internal
 * Internal to Symbian
 */
class TEikServCtrlFactories
	{
public:
	inline TEikServCtrlFactories();
	inline TEikServCtrlFactories(MEikServNotifyAlert* aAlert,MEikServAlarmFactory* aAlarmAlert);
public:
	MEikServNotifyAlert* iAlert;
	MEikServAlarmFactory* iAlarmAlert; // does not own anything
	};

/**
 * @internal
 * Internal to Symbian
 */
class CEikServAppUiBase : public CEikAppUi, public MEikUndertakerObserver
    {
	class TEikServAppStarter : public MVwsAppStarter // cannot change the size of this class there is an "inline" member object of it in CEikServAppUiBase
		{
	private: // From MVwsAppStarter.
		void StartAppL(TUid aAppUid,TThreadId& aThreadId);
		};
public:
	enum TTaskCycleDirection { EBackwards, EForwards };
	enum TEikServServers { EAlwlSvr=0x01, EApaSvr=0x02, EBackupSvr=0x04 };
private:
public:
	IMPORT_C static CEikServAppUiBase* NewL();
	IMPORT_C static CEikServAppUiBase* NewLC();
	IMPORT_C ~CEikServAppUiBase();
	IMPORT_C void NotifyAlarmServerOfTaskChange() const;
	IMPORT_C virtual void LaunchTaskListL() const;
	IMPORT_C void CycleTasks(TTaskCycleDirection aDirection) const;
	IMPORT_C void SetStatusPaneFlags(TInt aFlags) const;
	IMPORT_C void SetStatusPaneLayoutL(TInt aLayoutResId) const;
	IMPORT_C virtual void BlankScreenL();
	IMPORT_C virtual void UnblankScreen();
	IMPORT_C virtual void Extension(TUid aExtensionUid,const TDesC8& aBuffer,RMessagePtr aMessage); // shouldn't leave, but should handle error itself by doing aMessage.Complete
public:
	inline RWindowGroup& AlertGroupWin() const;
	IMPORT_C void BringAlertGroupWinForwards(TBool aForwards);
protected:
	IMPORT_C void ConstructL();
	IMPORT_C void InitializeL(TEikServCtrlFactories& aCtrlFactories);
	IMPORT_C void InitializeViewServerIfNotAlreadyRunningL();
	IMPORT_C CEikServAppUiBase();
protected: // from MEikUndertakerObserver
	IMPORT_C void HandleThreadExitL(RThread& aThread);
private: // framework
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
	IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
    IMPORT_C TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandleSwitchOnEventL(CCoeControl* aDestination);
protected:
	IMPORT_C void HandleScreenDeviceChangedL();
private: // specific
	void SetSystemTime() const;
	static TInt RestartServerCallback(TAny* aObj);
	static TInt StartNotifierServerCallBackL(TAny* aPtr);
	void RestartServer();
protected:
	RWindowGroup iAlertGroupWin;
	TInt iAlertGroupForwardsCount;
	TInt iResourceFileOffset;
	CEikServNotifyServer* iNotifyServer;
private:
	TAny* iBackupRestoreServer; // no longer used, but kept here to keep sizeof(CEikServAppUiBase) from shrinking (which would break derived classes)
protected:
	CEikServAlarmAlertServer* iAlarmAlertServer;
	CEikUndertaker* iUndertaker;
	RWindowGroup iBackdropWindowGroup;
	CEikServStatusPane* iStatusPane;
	CEikServBlankWin* iBlankWin;
	TInt iBlankWinRefCount;
private:
	CEikServExtra* iEikServExtra;
	TInt iServerToRestart;
	TEikServAppStarter iAppStarter;
	TAny* iSpare;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CEikServEnv : public CEikonEnv
	{
public:
	IMPORT_C CEikServEnv();
	IMPORT_C ~CEikServEnv();
	IMPORT_C void DestroyEnvironment();
public:
	void SetEikServer(CEikServAppUiServer* aServer);
	void SetUiDll(RLibrary& aDll);
private:
	RLibrary iUiDll;
	CEikServAppUiServer* iServer;
	};

inline TEikServCtrlFactories::TEikServCtrlFactories()
	: iAlert(NULL), iAlarmAlert(NULL)
	{}
inline TEikServCtrlFactories::TEikServCtrlFactories(MEikServNotifyAlert* aAlert,MEikServAlarmFactory* aAlarmAlert)
	: iAlert(aAlert), iAlarmAlert(aAlarmAlert)
	{}

inline RWindowGroup& CEikServAppUiBase::AlertGroupWin() const
	{ return((RWindowGroup&)iAlertGroupWin); }
      
#endif
