// COEMAIN.H
//
// Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEMAIN_H__)
#define __COEMAIN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__BARSC_H__)
#include <barsc.h>
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__BASCHED_H__)
#include <basched.h>
#endif

#if !defined(__COEMOP_H__)
#include <coemop.h>
#endif

#if !defined(__COETEXTDRAWER_H__)
#include <coetextdrawer.h>
#endif

#if defined(USE_IH_RAISE_EVENT)
#include <SystemMonitor/RaiseEvent.h>
#include <test/testinstrumentation.h>
#endif

class CVwsSessionWrapper;
class MVwsSessionWrapperObserver;

class CCoeAppUi;
class CCoeEnv;
class TResourceReader;
class RGenericPointerArray;

/** UI Control framework active object priorities. 
These are in addition to the values contained in the TPriority enum in class CActive.

@publishedAll
@released */
enum TActivePriority
	{
	/** 300 */
	EActivePriorityClockTimer=300,
	/** 200 */
	EActivePriorityIpcEventsHigh=200,
	/** 150 */
	EActivePriorityFepLoader=150,
	/** 100 */
	EActivePriorityWsEvents=100,
	/** 50 */
	EActivePriorityRedrawEvents=50,
	/** 0 */
	EActivePriorityDefault=0,
	/** 10 */
	EActivePriorityLogonA=-10
	};

class CCoeEnvExtra;
class CCoeStatic;


class MCoeObserverOfLoadedFep
/** Interface providing notification when there is a change in the currently 
loaded FEP. 

This happens either on application start-up, or as a result of a different 
front end processor having been installed.

Anyone requiring this notification should derive from this class and implement 
its pure virtual function. Derived classes also need to call CCoeEnv::AddObserverOfLoadedFepL() 
during construction, and CCoeEnv::RemoveObserverOfLoadedFep() in their destructor. 

@publishedAll
@released */
	{
public:
	/** Handles a change in the loaded FEP. 
	
	The function is called if a new FEP is loaded, or if the current one is unloaded. */
	virtual void HandleChangeInLoadedFep()=0;
protected:
	IMPORT_C MCoeObserverOfLoadedFep();
	
private:
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_1();
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_2();
private:
 	TInt iMCoeObserverOfLoadedFep_Reserved1;
	};

class TCoeInputCapabilities; // forward declaration of class defined in COEINPUT.H


class MCoeFocusObserver
/** Interface providing notification if any control gains or loses focus or is 
destroyed. 

The FEP framework uses this class to observe when a target control changes 
for reasons unrelated to the FEP.

Anything that needs such notification should derive from this class and implement 
its two pure virtual functions. 

In addition, derived classes need to call CCoeEnv::AddFocusObserverL() during 
construction, and CCoeEnv::RemoveFocusObserver() in their destructors. 

@publishedAll
@released 
@see CCoeFep */
	{
public:
	/** Handles changes in focus. The function is called if any control gains or loses 
	focus. */
	virtual void HandleChangeInFocus()=0;
	/** Handles the destruction of any control. It is called by the framework if any 
	control is destroyed. */
	virtual void HandleDestructionOfFocusedItem()=0;

protected:
	IMPORT_C MCoeFocusObserver();

private:
	IMPORT_C virtual void MCoeFocusObserver_Reserved_1();
	IMPORT_C virtual void MCoeFocusObserver_Reserved_2();
private:
	TInt iMCoeFocusObserver_Reserved1;
	};

class MCoeResourceChangeObserver
/** An interface which enables message windows to observe resource changes.

Resource change observers should be added to the control environment using 
CCoeEnv::AddResourceChangeObserverL(). 

@publishedAll 
@released */
	{
public:
	/** Handles a change to the application's resources. */
	virtual void HandleResourceChange()=0;
protected:
	IMPORT_C MCoeResourceChangeObserver();
	
private:
	IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_1();
	IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_2();
private:
	TInt iMCoeResourceChangeObserver_Reserved1;
	};

class MCoeForegroundObserver
/** Interface providing notification of foreground/background changes. 

The FEP framework class, CCoeFep, derives from MCoeForegroundObserver, which 
enables FEPs to receive notification when the target application (which receives 
the FEP's output) goes into the foreground or background.

Anything that needs this notification should derive from this class and override 
its two pure virtual functions.

In addition, derived classes also need to call CCoeEnv::AddForegroundObserverL() 
during construction, and CCoeEnv::RemoveForegroundObserver() in their destructors. 

@publishedAll
@released 
@see CCoeFep */
	{
public:
	/** Handles the application coming to the foreground. */
	virtual void HandleGainingForeground()=0;
	/** Handles the application going into the background. */
	virtual void HandleLosingForeground()=0;

protected:
	IMPORT_C MCoeForegroundObserver();
private:
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_1();
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_2();
private:
	TInt iMCoeForegroundObserver_Reserved1;
	};


class MCoeMessageObserver
/** Interface for handling incoming window server messages.

This interface is used to enable FEPs to keep their settings synchronised 
across all running instances.

Anything that needs to be notified of messages that get sent by the window server's 
message-sending service should derive from this class and override its pure 
virtual function. 

In addition, derived classes also need to call CCoeEnv::AddMessageObserverL() 
during construction and CCoeEnv::RemoveMessageObserver() in their destructors. 

@publishedAll 
@released */
	{
public:
	/** Message response flags. */
	enum TMessageResponse
		{
		/** Message not handled. */
		EMessageNotHandled,
		/** Message handled. */
		EMessageHandled
		};
public:
	/** Handles window server messages. 
	
	Implementations should return EMessageHandled if they are able to handle the 
	message, or EMessageNotHandled if the message is not appropriate to this observer.
	
	@param aClientHandleOfTargetWindowGroup The window group that the message 
	was sent to. Many implementations will not need this information.
	@param aMessageUid The message UID.
	@param aMessageParameters The message parameters.
	@return Indicates whether the message was handled or not handled 
	by the function. */
	virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters)=0;
protected:
	IMPORT_C MCoeMessageObserver();
	
private:
	IMPORT_C virtual void MCoeMessageObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageObserver_Reserved_2();
private:
	TInt iMCoeMessageObserver_Reserved1();
	};

class MCoeMessageMonitorObserver
	{
/** Mix-in interface for handling window visibility messages. 	

@publishedAll
@released */
public:
	/** Received windows messages for monitoring. 
	@param aEvent The windows server event data.*/
	virtual void MonitorWsMessage(const TWsEvent& aEvent)=0;
private:
	IMPORT_C virtual void MCoeMessageMonitorObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageMonitorObserver_Reserved_2();
	};

// classes defined in FEPBASE, declared here
class MCoeFepObserver;

/** 
@publishedAll
@released
*/
typedef void (*TCoeFepObserverFunction)(MCoeFepObserver& aFepObserver);

class CCoeFepParameters : public CBase
/**
@publishedAll 
@released 
*/
	{
public:
	static CCoeFepParameters* NewLC();
private:
	inline CCoeFepParameters() {}
	};


class CCoeFep; // must derive from CBase

class CCoeScheduler : public CBaActiveScheduler
/** Implements the active scheduler presupposed by the control environment.

@publishedPartner
@deprecated
*/
	{
public:
	IMPORT_C CCoeScheduler(CCoeEnv* aCoeEnv);
	IMPORT_C virtual void WaitForAnyRequest();
	IMPORT_C virtual void DisplayError(TInt aError) const;
	/** Gets the control environment.
	
	@return A pointer to the control environment. */
	inline CCoeEnv* CoeEnv() {return iCoeEnv;}
	TBool Flush() const; // not to be called from outside CONE
	void SetFlush(TBool aFlush); // not to be called from outside CONE
private:
	// from CBaActiveScheduler
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
private:
	CCoeEnv* iCoeEnv;
	TBool iFlush;
	};

class CCoeFontProvider;

class CCoeEnv : public CActive
							, public MObjectProvider
/** Control environment.

CCoeEnv provides an active environment for creating controls. It implements 
active objects and an active scheduler, which provide access to the window 
server, simplifying the API for application programs. It also provides utility 
functions that are useful to many applications.

When a standard event occurs, the active scheduler calls CCoeEnv::RunL(). 
When a redraw event occurs, it calls CCoeRedrawer::RunL(). Priority key events 
must be accessed using the Window Server API directly.

Note: standard events are all events except redraw events and priority key events. 

@publishedAll
@released */
	{
public:
	IMPORT_C ~CCoeEnv();
	IMPORT_C CCoeEnv();
	IMPORT_C virtual void DestroyEnvironment();
	IMPORT_C CCoeAppUi* SetAppUi(CCoeAppUi* aAppUi);
	IMPORT_C void ExecuteD();
	IMPORT_C void RunL();
	IMPORT_C void DoCancel();
	IMPORT_C virtual void HandleError(TInt aError);
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(TBool aInitialFocusState);
	IMPORT_C void ConstructL( TBool aInitialFocusState, TInt aDefaultScreenNumber ) ; // Added May 04 support for Multiple Screens
	IMPORT_C void ConstructL(TBool aInitialFocusState, TInt aDefaultScreenNumber, TInt aWindowGroupID );
	inline const TWsEvent& LastEvent() const;
	inline CCoeAppUi* AppUi() const;
	inline RFs& FsSession() const;
	inline RWsSession& WsSession() const;
	inline RWindowGroup& RootWin() const;
	inline CWindowGc& SystemGc() const;
	inline const CFont* NormalFont() const;
	inline CWsScreenDevice* ScreenDevice() const;
	inline TBool IsSchedulerRunning() const;

	IMPORT_C CWindowGc* CreateGcL();
	IMPORT_C void Flush(TTimeIntervalMicroSeconds32 aDelay=0);
	IMPORT_C CFbsFont* CreateDeviceFontL(CGraphicsDevice* aDevice,const TFontSpec& aFontSpec);
	IMPORT_C CFbsFont* CreateScreenFontL(const TFontSpec& aFontSpec);
	IMPORT_C void ReleaseScreenFont(CFont* aFont) const;
	IMPORT_C void CreateResourceReaderLC(TResourceReader& aReader,TInt aResourceId) const;
	inline void ReadResource(TDes& aDes,TInt aResourceId) const; 
	inline void ReadResourceL(TDes& aDes,TInt aResourceId) const; 
	inline  HBufC* AllocReadResourceL(TInt aResourceId) const;
	inline HBufC* AllocReadResourceLC(TInt aResourceId) const;
	IMPORT_C TInt AddResourceFileL(const TDesC& aFileName);
	IMPORT_C void DeleteResourceFile(TInt aOffset);
	inline CDesCArrayFlat* ReadDesCArrayResourceL(TInt aResourceId);
	IMPORT_C void LeaveWithErrorText(const TDesC& aMsg,const TDesC* aContextText=NULL);
	IMPORT_C void Format128(TDes& aDes,TInt aResourceId,...);
	IMPORT_C void Format256(TDes& aDes,TInt aResourceId,...);
	IMPORT_C static TVersion Version();
	IMPORT_C static CCoeEnv* Static();
	IMPORT_C void SimulateKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C TBool IsWservEventPending() const;
	IMPORT_C TBool IsRedrawEventPending() const;
	IMPORT_C void PrepareToExit();
	IMPORT_C void BringOwnerToFront();
	IMPORT_C void ReadResourceAsDes8(TDes8& aDes,TInt aResourceId) const; /** @deprecated 7.0*/
	IMPORT_C void ReadResourceAsDes8L(TDes8& aDes,TInt aResourceId) const;
	IMPORT_C HBufC8* AllocReadResourceAsDes8L(TInt aResourceId) const;
	IMPORT_C HBufC8* AllocReadResourceAsDes8LC(TInt aResourceId) const;
	IMPORT_C CDesC8ArrayFlat* ReadDesC8ArrayResourceL(TInt aResourceId);
	IMPORT_C void SuppressNextFlush();
	IMPORT_C void ReadResourceAsDes16(TDes16& aDes,TInt aResourceId) const; /** @deprecated 7.0*/
	IMPORT_C void ReadResourceAsDes16L(TDes16& aDes,TInt aResourceId) const; 
	IMPORT_C HBufC16* AllocReadResourceAsDes16L(TInt aResourceId) const; // not available before Release 005
	IMPORT_C HBufC16* AllocReadResourceAsDes16LC(TInt aResourceId) const; // not available before Release 005
	IMPORT_C CDesC16ArrayFlat* ReadDesC16ArrayResourceL(TInt aResourceId); // not available before Release 005
	IMPORT_C void AddObserverOfLoadedFepL(MCoeObserverOfLoadedFep& aObserverOfLoadedFep); // not available before Release 005
	IMPORT_C void RemoveObserverOfLoadedFep(MCoeObserverOfLoadedFep& aObserverOfLoadedFep); // not available before Release 005
	IMPORT_C void AddFocusObserverL(MCoeFocusObserver& aFocusObserver); // not available before Release 005
	IMPORT_C void RemoveFocusObserver(MCoeFocusObserver& aFocusObserver); // not available before Release 005
	IMPORT_C void SyncNotifyFocusObserversOfChangeInFocus();
	void NotifyFocusObserversOfDestructionOfFocusedItem(); // not to be called from outside CONE
	IMPORT_C void AddForegroundObserverL(MCoeForegroundObserver& aForegroundObserver); // not available before Release 005
	IMPORT_C void RemoveForegroundObserver(MCoeForegroundObserver& aForegroundObserver); // not available before Release 005
	void NotifyForegroundObserversOfGainingForeground(); // not to be called from outside CONE
	void NotifyForegroundObserversOfLosingForeground(); // not to be called from outside CONE
	IMPORT_C void AddResourceChangeObserverL(MCoeResourceChangeObserver& aResourceChangeObserver); 
	IMPORT_C void RemoveResourceChangeObserver(MCoeResourceChangeObserver& aResourceChangeObserver); 
	void NotifyResourceObserversOfChangeInResource(); 
	IMPORT_C void AddMessageObserverL(MCoeMessageObserver& aMessageObserver); // not available before Release 005
	IMPORT_C void RemoveMessageObserver(MCoeMessageObserver& aMessageObserver); // not available before Release 005
	IMPORT_C void AddMessageMonitorObserverL(MCoeMessageMonitorObserver& aMessageMonitorObserver); 
	IMPORT_C void RemoveMessageMonitorObserver(MCoeMessageMonitorObserver& aMessageMonitorObserver); 
	void NotifyMessageMonitorObserversOfEvent(const TWsEvent& aEvent); 	
	IMPORT_C void AddFepObserverL(MCoeFepObserver& aFepObserver); // not available before Release 005
	IMPORT_C void RemoveFepObserver(MCoeFepObserver& aFepObserver); // not available before Release 005
	IMPORT_C void ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction); // not available before Release 005
	void EnsureCorrectFepIsLoadedL(); // not to be called from outside CONE
#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
	void LoadFepL(const TDesC& aFileNameOfFepDll); // not to be called from outside CONE
	IMPORT_C MDesCArray* FileNamesOfAvailableFepsL(); // not available before Release 005
	IMPORT_C void InstallFepL(const TDesC& aFileNameOfFepDll); // not available before Release 005
	IMPORT_C void InstallFepL(const TDesC& aFileNameOfFepDll, const TBool aLeave);
	IMPORT_C HBufC* NameOfInstalledFepL(); // not available before Release 005
	IMPORT_C void ExecuteFepSettingsDialogL(const TDesC& aFileNameOfFepDll); // not available before Release 005
#endif
	void EnsureSpecifiedFepIsLoadedL(TUid aFepUid); // not to be called from outside CONE
	IMPORT_C void InstallFepL(TUid aFepUid);
	IMPORT_C void InstallFepL(TUid aFepUid, const TBool aLeave);
	IMPORT_C void AvailableFepsL(RArray<TUid>& aUids, CDesCArray* aDisplayNames);
	IMPORT_C void ExecuteFepSettingsDialogL(TUid aFepUid);
	IMPORT_C CCoeFep* Fep() const; // not available before Release 005
	IMPORT_C TUid FepUid() const; // not available before Release 006
	IMPORT_C CWindowGc* SwapSystemGc(CWindowGc* aGc); // not available before Release 005
	IMPORT_C static CCoeStatic* Static(TUid aUid);
	IMPORT_C CCoeStatic* FindStatic(TUid aUid);
	IMPORT_C void DisableExitChecks(TBool aDisable);
	IMPORT_C void InputCapabilitiesChanged(); // not available before Release 6.1

	IMPORT_C TBool IsResourceAvailableL(TInt aResourceId) const;
	IMPORT_C CCoeTextDrawerBase& DefaultTextDrawer() const;
	IMPORT_C const CCoeFontProvider& DefaultFontProvider() const; 
 
public: // *** Do not use! API liable to change ***
	TInt AppStartupInstrumentationEventIdBase();
public: // Internal to Symbian
	IMPORT_C void GetMessageNotifyingObserversLC(TUint32 aClientHandleOfTargetWindowGroup, TUid& aMessageUid, TPtr8& aMessageParameters, const TWsEvent& aMessageEvent);
protected: // Internal to Symbian
	IMPORT_C void SetAppStartupInstrumentationEventIdBaseL(TInt aAppStartupInstrumentationEventIdBase);
	IMPORT_C void DestroyEnvironmentStatic();
	IMPORT_C void DestroyEnvironmentEnd();	
private: // reserved virtual function space
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
private: // from CActive
	IMPORT_C TInt RunError(TInt aError);
public: // but not exported
	void ReadEvent();
	CVwsSessionWrapper* InitViewServerSessionL(MVwsSessionWrapperObserver& aObserver);
	void AddStatic(CCoeStatic* aStatic);
	void QueueNotificationToFocusObserversOfChangeInFocus();
	TInt FocusObserverNotificationIdentifier() const;
	TBool FocusObserverNotificationIsStillPending(TInt aFocusObserverNotificationIdentifier) const;
	void RefetchPixelMapping();

protected:	// from MObjectProvider
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId); 
public:
	IMPORT_C void SetZoomFactor(const TZoomFactor& aZoomFactor);
	IMPORT_C TZoomFactor ZoomFactor() const;

protected:
	IMPORT_C virtual void DestroyScreen();
	inline TDes& ErrorText();
	inline TDes& ErrorContextText();
private:
	IMPORT_C virtual void InitSystemFontsL();
	IMPORT_C virtual TInt ResourceFileVersionNumber() const;
	void CreateActiveSchedulerL();
	void ConnectToFileServerL();
	void ConnectToWindowServerL();
	void InitScreenL( TInt aDefaultScreenNumber ); // Modified May 04, support for Multiple Screens
	void InitRootWindowL(TBool aInitialFocusState, TInt aWindowGroupID=0);
	void InitSystemGcL();
	RResourceFile& ResourceFileForId(TInt aResourceId) const;
	void DestroyAllResourceFiles();
	void AddObserverL(TAny* aObserver, RGenericPointerArray& aArray);
	void RemoveObserver(TAny* aObserver, RGenericPointerArray& aArray);
	inline TBool DisableShutdownChecks() const;
	void UpdateStatic(CCoeAppUi* aNewAppUi);
	void SetInitialHandleCount();
	inline TUint InitialHandleCount() const;
protected:
	CCoeAppUi* iAppUi;
	RFs iFsSession;
	RWsSession iWsSession;
	RWindowGroup iRootWin;
	CWindowGc* iSystemGc;
	const CFont* iNormalFont;
	CWsScreenDevice* iScreen;
	TWsEvent iLastEvent;
	CArrayFix<RResourceFile>* iResourceFileArray;

private:
	enum TFlags // used in the bottom 16 bits only of iEnvFlags
		{
		ENoShutdownChecks			=0x0001,
		EExtraPointerIsErrorCode	=0x0002,
		ESchedulerIsRunning			=0x0004
		};
private:
	TDes* iErrorText;
	TDes* iErrorContextText;
	CCoeEnvExtra* iExtra;
	CTrapCleanup* iCleanup;
	TUint iEnvFlags;
	};

class CCoeStatic : public CBase
/** Base class for creating singleton objects that will be stored by CCoeEnv.

Each object must have a unique TUid.

Symbian OS does not provide writeable global static data. Singleton objects 
provide its equivalent in thread local storage, which is supported.

This behaviour is useful for objects in which only one copy is ever needed 
in the thread or application, e.g. in alert windows. 

@publishedAll 
@released */
	{
public:
	/** Scope of access to the singleton object. */
	enum TScope
		{
		/** Access from the entire thread. */
		EThread,
		/** Access from an appUi in that thread. */
		EApp,
		};
	/** The default destruction priority if none is specified in the constructor */
	enum {EDefaultDestructionPriority=100};
public:
	IMPORT_C ~CCoeStatic();
protected:
	IMPORT_C CCoeStatic();
	IMPORT_C CCoeStatic(TUid aUid,TScope=EThread);
	IMPORT_C CCoeStatic(TUid aUid,TInt aDestructionPriority,TScope aScope=EThread);
private:
	IMPORT_C virtual void CCoeStatic_Reserved1();
	IMPORT_C virtual void CCoeStatic_Reserved2();
private:
	void DoConstruction(TUid aUid,TInt aDestructionPriority,TScope aScope);
	void SetCsAppUi(CCoeAppUi* aAppUi);
	CCoeAppUi* CsAppUi() const;
	TScope CsScope() const;
	inline TInt DestructionPriority() const {return iCsLink.iPriority;}
private:
	TPriQueLink iCsLink;
	TUid iCsUid;
	TUint iCsAppUiAndScope;
	TInt iCCoeStatic_Reserved1;
private:
	friend class CCoeEnv;
	friend class CCoeEnvExtra;
	};

inline const TWsEvent& CCoeEnv::LastEvent() const
/** Gets the most recent standard event that was received by the application.

Note: standard events are all events except redraw events and priority key events.

@return The last event. */
	{ return(iLastEvent); }

inline CCoeAppUi* CCoeEnv::AppUi() const
/** Gets the application UI owned by this application.

@return Pointer to the app UI owned by the application. */
	{ return(iAppUi); }

inline RFs& CCoeEnv::FsSession() const
/** Gets the file server session owned by this CCoeEnv. 

This session is normally only used for accessing the application's resource 
file.

@return The file server session owned by this CCoeEnv. */
	{ return((RFs&)iFsSession); }

inline RWsSession& CCoeEnv::WsSession() const
/** Gets the window server session owned by the application. 

This provides access to window server functions not directly accessible via 
the UI control framework.

@return The window server session opened by the application. */
	{ return((RWsSession&)iWsSession); }

inline RWindowGroup& CCoeEnv::RootWin() const
/** Gets the application's window group.

Note: a window group is an invisible window which acts as the parent window for 
all other windows in an application. Typically, each application has one window 
group. In the window server, window groups are also the unit of keyboard focus.

@return The application's window group. */
	{ return((RWindowGroup&)iRootWin); }

inline CWindowGc& CCoeEnv::SystemGc() const
/** Gets the system graphics context. 

This is the graphics context typically used for drawing controls, but an 
alternative graphics context can be created if required using CreateGcL().

@return The system graphics context. */
	{ return((CWindowGc&)*iSystemGc); }

inline const CFont* CCoeEnv::NormalFont() const
/** Gets the normal environment font. 

This is the font created during construction of the control environment.

@return Pointer to the normal environment font.
@see InitSystemFontsL() */
	{ return(iNormalFont); }

inline CWsScreenDevice* CCoeEnv::ScreenDevice() const
/** Gets the default screen device owned by this CCoeEnv. 

This is typically used as the standard screen device for the CCoeEnv's application.

@return The default screen device owned by this CCoeEnv. */
	{ return(iScreen); }

inline TDes& CCoeEnv::ErrorText() 
/** Gets the current error message text.

@return The current error message text. */
	{ return *iErrorText; }

inline TDes& CCoeEnv::ErrorContextText() 
/** Gets the current error context text.

@return The current error context text. */
	{ return *iErrorContextText; }

#if defined(_UNICODE)
inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
/** Reads a resource into a descriptor. 

The descriptor must be long enough to contain the entire resource. No memory 
is allocated by this function. If the read fails, the function sets an error 
condition and performs any cleanup required. The error condition causes the 
GUI to launch an alert window.

Deprecated - Use CCoeEnv::ReadResourceL() instead.

@deprecated 
@param aDes On return, contains the resource data.
@param aResourceId The numeric ID of the resource to be read.
@see RResourceFile::ReadL()
@see KErrCoeFailedToReadFromProgDisk */
	{ ReadResourceAsDes16(aDes,aResourceId); }

inline void CCoeEnv::ReadResourceL(TDes& aDes,TInt aResourceId) const
/** Reads a resource into a descriptor.

The descriptor must be long enough to contain the entire resource. 
No memory is allocated by this function.

@param aDes On return, contains the resource data.
@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource. */
	{ ReadResourceAsDes16L(aDes,aResourceId); }

inline  HBufC* CCoeEnv::AllocReadResourceL(TInt aResourceId) const
/** Reads a resource into a heap descriptor, allocating memory for it. 

Note: the calling program must destroy the heap descriptor when it is no longer 
needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data.
@see RResourceFile::AllocReadL() */
	{ return AllocReadResourceAsDes16L(aResourceId); }

inline HBufC* CCoeEnv::AllocReadResourceLC(TInt aResourceId) const
/** Reads a specified resource into a heap descriptor, allocating memory for it, 
and pushing the descriptor onto the cleanup stack. 

The calling program should pop and destroy the heap descriptor when it is 
no longer needed.

@param aResourceId The numeric ID of the resource to be read.
@return Pointer to a heap descriptor containing the resource data.
@see RResourceFile::AllocReadLC() */
	{ return AllocReadResourceAsDes16LC(aResourceId); }

inline CDesCArrayFlat* CCoeEnv::ReadDesCArrayResourceL(TInt aResourceId)
/** Reads a resource into a Unicode descriptor array.

@param aResourceId The numeric ID of the resource to be read.
@return A pointer to the descriptor array containing the resource data.
@see TResourceReader::ReadDesCArrayL() */
	{ return ReadDesC16ArrayResourceL(aResourceId); }
#else  // not UNICODE

inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
/** Deprecated - use CCoeEnv::ReadResourceL() instead.

@deprecated */
	{ ReadResourceAsDes8(aDes,aResourceId); }

inline void CCoeEnv::ReadResourceL(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes8L(aDes,aResourceId); }
inline  HBufC* CCoeEnv::AllocReadResourceL(TInt aResourceId) const
	{ return AllocReadResourceAsDes8L(aResourceId); }
inline HBufC* CCoeEnv::AllocReadResourceLC(TInt aResourceId) const
	{ return AllocReadResourceAsDes8LC(aResourceId); }
inline CDesCArrayFlat* CCoeEnv::ReadDesCArrayResourceL(TInt aResourceId)
	{ return ReadDesC8ArrayResourceL(aResourceId); }
#endif // UNICODE

//
// Tests if the Active Scheduler is started in the CCoeEnv::ExecuteD
//
// @return   "TBool"
//            <code>ETrue</code> if Active Scheduler is started in
//								 CCoeEnv::ExecuteD()	
//            <code>EFalse</code> if Active Scheduler is not started in
//								  CCoeEnv::ExecuteD()	
//            
inline TBool CCoeEnv::IsSchedulerRunning() const
	{return iEnvFlags&ESchedulerIsRunning;}

#endif
