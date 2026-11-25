/*
* ==============================================================================
*  Name        : eiksrv.h
*  Part of     : UIKON
*  Interface   : Application Server API
*  Description : The application server and related classes.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef EIKSRV_H
#define EIKSRV_H

// INCLUDES
#include <eikappui.h>
#include <eikenv.h>
#include <apgtask.h>
#include <vwsappst.h>
#include <eikunder.h>

// FORWARD DECLARATIONS
class CEikServAppUiBase;
class CDictionaryFileStore;
class CEikServStatusPane;
class CVwsSessionWrapper;
class CEikServExtra;
class CEikServAppUiSession;
class CEikServNotifyServer;
class CNotifierServerExtended;
class CEikServBackupServer;
class CEikServAlarmAlertServer;
class CEikKeyWindow;
class CEikUndertaker;
class CEikPasswordControl;
class CEikTaskListDialog;
class MEikServAlarmFactory;
class CEikServDllClose;
class CEikServBlankWin;

const TInt KUidStatusPaneUpdateMessageValue = 0x101F8954; 
const TUid KUidStatusPaneUpdateMessage = {KUidStatusPaneUpdateMessageValue};

class TStatusPaneUpdate
	{
public:
	TInt iOrdPosOfForemostWgWithSp;
	};

typedef TPckgBuf<TStatusPaneUpdate> TStatusPaneUpdateBuf;
/** Creates an interface object to Eikon server.

@publishedPartner
@released
*/
typedef CEikServAppUiBase* (*CreateCEikServAppUiBase)();

// CONSTANTS
enum TEikAppUiServPanic
	{
	EEikSrvDefault,
	EEikSrvSvrCreateServer, // no longer used
	EEikSrvSvrStartServer,
	EEikSrvSrvNotFound,
	EEikSrvBadDescriptor,
	EEikSrvIllegalError,
	};

/**
*  Class used internally to start a server.
*
* @since Series90 1.0
* @internal
*  @lib eiksrv.lib
*/
class TServerStart
	{
	public:
		TServerStart(TRequestStatus& aStatus);
		TPtrC AsCommand() const;
		TServerStart();
		TInt GetCommand();
		void SignalL();

	private:
		TThreadId iId;
		TRequestStatus* iStatus;
	};


/**
*  The application UI server.
*
* @internal
* @since Series90 1.0
*  @lib eiksrv.lib
*/
class CEikServAppUiServer :public CServer2
	{
	friend class CEikServAppUiSession;
	public:
		enum {EPriority=EPriorityAbsoluteHigh};

	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CEikServAppUiServer* NewL();

		virtual CSession2* NewSessionL(const TVersion &aVersion,const RMessage2& aMessage) const;
		static TInt ThreadFunction(TAny* aStarted);
	CEikServAppUiBase& AppUi(); // non-inline (and non-exported) so that it cannot be accessed outside of the DLL
	private:
		CEikServAppUiServer(TInt aPriority=EPriority);
		void ConstructL();
	private:
		CEikServAppUiBase* iAppUi;
	};

/**
*  Session to the application UI server.
*
* @internal
* @since Series90 1.0
*  @lib eiksrv.lib
*/
class CEikServAppUiSession : public CSession2
	{
	public:

		/**
		* Two-phased constructors.
		*/
		static CEikServAppUiSession* NewL();
		static CEikServAppUiSession* NewL(RThread aClient, CEikServAppUiServer * aServer);

		/**
		* Destructor.
		*/
		~CEikServAppUiSession();

		virtual void ServiceL(const RMessage2 &aMessage);
		virtual void ServiceError(const RMessage2& aMessage,TInt aError);
	private:
		inline CEikServAppUiServer& Server() {return *STATIC_CAST(CEikServAppUiServer*,CONST_CAST(CServer2*,CSession2::Server()));}
		void PanicClient(TEikAppUiServPanic aCode);
	protected:
		CEikServAppUiServer* iAppUiServer;
		TBool iScreenBlanked;
	};


class CEikPasswordModeCategory : public CBase
/**
@publishedPartner
@released
*/
	{
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CEikPasswordModeCategory* NewLC(RFs& aFs);

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikPasswordModeCategory();

		/**
		* Gets the password mode.
		* @param aMode On return, contains the mode, consisting of password mode flags from <code>TPasswordMode</code>.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void GetPasswordModeL(TPasswordMode& aMode) const;

		/**
		* Sets the password mode.
		* @param aMode The mode, consisting of password mode flags from <code>TPasswordMode</code>.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetPasswordModeL(TPasswordMode aMode);
	private:
		CEikPasswordModeCategory();
		void ConstructL(RFs& aFs);
	private:
		CDictionaryFileStore* iStore;
	};

/**
 * @deprecated
 * @internal
 * Internal to Symbian
 */
class TEikServCtrlFactories
	{
	};


//internal
class CEikServStatusPaneMonitor : public CBase
	{
public:
	enum TSPMonitorState
		{
		EStartingUp,
		EFgWgHasUpdatedStatusPane,
		EFgWgHasNotUpdatedStatusPane
		};
public:
	TThreadId iNewFgWgThreadId;
	TInt iNewFgWgId;
	TInt iForemostWgWithSpId;
	TInt iWgWithSpLastUpdated;
	TSPMonitorState iState;
	};
	
/**
 * @internal
 * Internal to Symbian
 */
class CEikServAppUiBase : public CEikAppUi, public MEikUndertakerObserver
    {
	/**
	*  Application starter class.
	*  Cannot change the size of this class there is an "inline" member object of it in CEikServAppUiBase
	*
	*/
	class TEikServAppStarter : public MVwsAppStarter
		{
		private: // From MVwsAppStarter.
			void StartAppL(TUid aAppUid,TThreadId& aThreadId);
		};

	public:
		enum TTaskCycleDirection { EBackwards, EForwards };
		enum TEikServServers { EAlwlSvr=0x01, EApaSvr=0x02, EBackupSvr=0x04 };

	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CEikServAppUiBase* NewL();

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CEikServAppUiBase* NewLC();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikServAppUiBase();

		/**
		* Wakes the alarm server up to let it know a key has been pressed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void NotifyAlarmServerOfTaskChangeL() const;
		/**
		* Not supported.
		*/
		IMPORT_C virtual void LaunchTaskListL() const;

		/**
		* Cycles through all current tasks, i.e. sets the next task to be the foreground task.
		* @param aDirection Either CEikServAppUiBase::EForwards or CEikServAppUiBase::EBackwards to cycle forwards or backwards through the tasks.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void CycleTasksL(TTaskCycleDirection aDirection) const;
		/**
		* Sets the flags of the status pane.
		* @param aFlags A bitwise OR of visual flags. See KEikStatusPaneBaseFadedBit KEikStatusPaneBaseVisibleBit and KEikStatusPaneBaseDimmedBit.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetStatusPaneFlags(TInt aFlags) const;

		/**
		* Sets the layout of the status pane.
		* @param aLayoutResId Resources to define the new status pane layout.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetStatusPaneLayoutL(TInt aLayoutResId) const;

		/**
		* Creates a blank screen window to cover the screen.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void BlankScreenL();

		/**
		* Deletes the blank screen window.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void UnblankScreen();

		/**
		* Not supported.
		*/
		IMPORT_C virtual void Extension(TUid aExtensionUid,const TDesC8& aBuffer,RMessagePtr2 aMessage); // shouldn't leave, but should handle error itself by doing aMessage.Complete
	public:

		/**
		* Get the application server's window group, used for alerts.
		* @return The window group by reference.
		* <BR><B>Type of return value:</B> RWindowGroup&

		*/
		inline RWindowGroup& AlertGroupWin() const;

		/**
		* Brings forward (or sends backwards) the application server's window group, used for alerts.
		* @param aForwards ETrue to bring the window group forwards. EFalse to send it backwards.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void BringAlertGroupWinForwards(TBool aForwards);

		//mjt internal
		CEikServStatusPaneMonitor* SpMonitor();
	protected:

		/**
		* Second phase constructor.
		*/
		IMPORT_C void ConstructL();

		/**
		* Initialise the application server. This includes system settings,
		* creating and starting notify, backup/restore and alarm/alert servers;
		* starting comms and the apparc server; creating an undertaker active object,
		* a restarter object and the status pane.
		* @param aCtrlFactories Not used.
		*/
		IMPORT_C void InitializeL(TEikServCtrlFactories& aCtrlFactories);

		/**
		* Starts the view server and sets it to the default view defined in eikpriv.rsg.
		*/
		IMPORT_C void InitializeViewServerIfNotAlreadyRunningL();

		/**
		* Constructor.
		*/
		IMPORT_C CEikServAppUiBase();
	protected: // from MEikUndertakerObserver

		/**
		* Called automatically by the undertaker. Should not need to be used.
		* This restarts the alarm/apparc servers if they exit.
		* @param aThread The thread that exits.
		*/
		IMPORT_C void HandleThreadExitL(RThread& aThread);
	private: // framework
		IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
		IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
		IMPORT_C TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		IMPORT_C void HandleSwitchOnEventL(CCoeControl* aDestination);
	protected:

		/**
		* This function does nothing.
		*/
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
	private:
		TAny* iNotifyServer; // Not used, but kept (privately) for BC
		TAny* iBackupRestoreServer; // no longer used, but kept here to keep sizeof(CEikServAppUiBase) from shrinking (which would break derived classes)
	protected:
		CEikServAlarmAlertServer* iAlarmAlertServer;
		CEikUndertaker* iUndertaker;
		RWindowGroup iBackdropWindowGroup;
		CEikServStatusPane* iStatusPane;
		CEikServBlankWin* iBlankWin;
		CEikServStatusPaneMonitor* iSpMonitor;
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
class CEikServEnv : public CEikonEnvSkinObs
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikServEnv();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikServEnv();

		/**
		* Deletes the application server when the environment is destroyed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void DestroyEnvironment();
	public:
		void SetEikServer(CEikServAppUiServer* aServer);
		void SetUiDll(RLibrary& aDll);
// from CCoeEnv, overriden to stop errors going via notifier server
		IMPORT_C void HandleError(TInt );
	private:
		RLibrary iUiDll;
		CEikServAppUiServer* iServer;
	};

inline RWindowGroup& CEikServAppUiBase::AlertGroupWin() const
	{ return((RWindowGroup&)iAlertGroupWin); }


#endif	// EIKSRV_H

// End of File
