// COEMAIN.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
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

class CVwsSessionWrapper;
class MVwsSessionWrapperObserver;

class CCoeAppUiBase;
class CCoeEnv;
class TResourceReader;
class RGenericPointerArray;


/**
 * Active object priorities.
 * This is an alternative set to the <code>TPriority</code> in e32base.h
 */
enum TActivePriority
	{
	EActivePriorityClockTimer=300,		/** 300 */
	EActivePriorityIpcEventsHigh=200,	/** 200 */
	EActivePriorityFepLoader=150,		/** 150 */
	EActivePriorityWsEvents=100,		/** 100 */
	EActivePriorityRedrawEvents=50,		/** 50 */
	EActivePriorityDefault=0,			/** 0 */
	EActivePriorityLogonA=-10			/** 10 */
	};

class CCoeEnvExtra;
class CCoeStatic;

/**
 *
 * Interface providing notification when there is any change in the
 * currently loaded FEP.
 *
 * This happens either on application start-up, or as a result of a
 * different front-end processor having been installed.Writing derived
 * classes:Anyone requiring this notification should derive from this
 * class and override its pure virtual function. Derived classes also
 * need to call <code>CCoeEnv::AddObserverOfLoadedFepL()</code> during
 * construction, and <code>CCoeEnv::RemoveObserverOfLoadedFep()</code> in
 * their destructors.
 *
 * @since 6.0
 * @lib "N/A"
 */
class MCoeObserverOfLoadedFep
	{
public:
	/**
	 * Handles a changes in the loaded FEP.
	 *
	 * The function is called if a new FEP is loaded, or if the current one
	 * is unloaded.
	 */
	virtual void HandleChangeInLoadedFep()=0;
private:
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_1();
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_2();
	};

class TCoeInputCapabilities; // forward declaration of class defined in COEINPUT.H
/**
 *
 * Interface providing notification if any control gains or loses focus
 * or is destroyed.
 *
 * The FEP framework uses this classto observe when a target control
 * changes for reasons unrelated to the FEP.Writing derived
 * classes:Anything that needs such notification should derive from this
 * class and override its two pure virtual functions. In addition,
 * derived classes need to call <code>CCoeEnv::AddFocusObserverL()</code>
 * during construction, and <code>CCoeEnv::RemoveFocusObserver()</code>
 * in their destructors.
 *
 * @since 6.0
 * @lib "N/A"
 */
class MCoeFocusObserver
	{
public:
	/**
	 * Handles changes in focus.
	 * The function is called if any control gains or loses focus.
	 */
	virtual void HandleChangeInFocus()=0;

	/**
	 * Handles the destruction of any control.
	 * It is called by the framework if any control is destroyed.
	 */
	virtual void HandleDestructionOfFocusedItem()=0;
private:
	IMPORT_C virtual void MCoeFocusObserver_Reserved_1();
	IMPORT_C virtual void MCoeFocusObserver_Reserved_2();
	};

/**
 * The MCoeResourceChangeObserver specifies the interface which enables message
 * windows to observe resource changes.
 * 
 * @since App-Framework_6.2
 */
class MCoeResourceChangeObserver
	{
public:
	virtual void HandleResourceChange()=0;
private:
	IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_1();
	IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_2();
	};

/**
 *
 * Interface providing notification of foreground/background changes.
 *
 * The FEP framework class, <code>CCoeFep</code>, derives from
 * <code>MCoeForegroundObserver</code> which enables FEPs to receive
 * notification when the target application (which receives characters
 * produced by the FEP) goes into the foreground or background.Writing
 * derived classes:Anything that needs this notification should derive
 * from this class and override its two pure virtual functions.In
 * addition, derived classes also need to call
 * <code>CCoeEnv::AddForegroundObserverL()</code> during construction,
 * and <code>CCoeEnv::RemoveForegroundObserver()</code> in their
 * destructors.
 *
 * @since 6.0
 * @lib "N/A"
 */
class MCoeForegroundObserver
	{
public:
	/**
	 * Handles the application coming to the foreground.
	 */
	virtual void HandleGainingForeground()=0;

	/**
	 * Handles the application going into the background.
	 */
	virtual void HandleLosingForeground()=0;
private:
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_1();
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_2();
	};

/**
 *
 * Interface for handling incoming window server messages.
 *
 * This interface is used to enable FEPs to keep their settings
 * synchronised across all running instances.Writing derived
 * classes:Anything that needs to be notified of messages that get sent
 * by the window-server's message-sending service should derive from this
 * class and override its pure virtual function. In addition, derived
 * classes also need to call <code>CCoeEnv::AddMessageObserverL()</code>
 * during construction and <code>CCoeEnv::RemoveMessageObserver()</code>
 * in their destructors.
 *
 * @since 6.0
 * @lib ""
 */
class MCoeMessageObserver
	{
public:
	/**
	 * Message response flags.
	 */
	enum TMessageResponse
		{
		EMessageNotHandled,	/** Message handled. */
		EMessageHandled		/** Message not handled. */
		};
public:
	/**
	 *
	 * Handles window server messages.
	 *
	 * Implementations should return <code>EMessageHandled</code> if they are
	 * able to handle the message, or <code>EMessageNotHandled</code> if the
	 * message is not appropriate to this observer.
	 *
	 * @param     "TUint32 aClientHandleOfTargetWindowGroup"
	 *            The window group that the message was sent to. Many
	 *            implementations will not need this information.
	 * @param     "TUid aMessageUid"
	 *            The message UID.
	 * @param     "const TDesC8& aMessageParameters"
	 *            The message parameters.
	 * @returns   "TMessageResponse"
	 *            The message response — the message was either
	 *            handled or not handled by the function.
	 */
	virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters)=0;
private:
	IMPORT_C virtual void MCoeMessageObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageObserver_Reserved_2();
	};

// classes defined in FEPBASE, declared here
class MCoeFepObserver;
typedef void (*TCoeFepObserverFunction)(MCoeFepObserver& aFepObserver);
class CCoeFepParameters; // must derive from CBase
class CCoeFep; // must derive from CBase

/**
 * The CCoeScheduler class implements the active scheduler presupposed by the
 * control environment.
 */ 
class CCoeScheduler : public CBaActiveScheduler
	{
public:
	IMPORT_C CCoeScheduler(CCoeEnv* aCoeEnv);
	IMPORT_C virtual void WaitForAnyRequest();
	IMPORT_C virtual void DisplayError(TInt aError) const;
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

/**
 *
 * Control Environment.
 *
 * <code>CCoeEnv</code> provides an active environment for creating
 * controls. It implements active objects and an active scheduler, which
 * provide access to the window server, simplifying the API for
 * application programs. It also provides utility functions that are
 * useful to many applications.When a standard event occurs, the active
 * scheduler calls <code>CCoeEnv::RunL()</code>. When a redraw event
 * occurs, it calls <code>CCoeRedrawer::RunL()</code>. Priority key
 * events must be accessed using the window server client API
 * directly.Note:Standard events are all events except redraw events and
 * priority key events.
 *
 * @since 5.0
 * @lib "cone.lib"
 */
class CCoeEnv : public CActive
	{
public:
	IMPORT_C ~CCoeEnv();
	IMPORT_C CCoeEnv();
	IMPORT_C virtual void DestroyEnvironment();
	IMPORT_C CCoeAppUiBase* SetAppUi(CCoeAppUiBase* aAppUi);
	IMPORT_C void ExecuteD();
	IMPORT_C void RunL();
	IMPORT_C void DoCancel();
	IMPORT_C virtual void HandleError(TInt aError);
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(TBool aInitialFocusState);
	inline const TWsEvent& LastEvent() const;
	inline CCoeAppUiBase* AppUi() const;
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
	IMPORT_C void AddFepObserverL(MCoeFepObserver& aFepObserver); // not available before Release 005
	IMPORT_C void RemoveFepObserver(MCoeFepObserver& aFepObserver); // not available before Release 005
	IMPORT_C void ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction); // not available before Release 005
	void LoadFepL(); // not to be called from outside CONE
	void LoadFepL(const TDesC& aFileNameOfFepDll); // not to be called from outside CONE
	IMPORT_C void InstallFepL(const TDesC& aFileNameOfFepDll); // not available before Release 005
	IMPORT_C HBufC* NameOfInstalledFepL(); // not available before Release 005
	IMPORT_C MDesCArray* FileNamesOfAvailableFepsL(); // not available before Release 005
	IMPORT_C void ExecuteFepSettingsDialogL(const TDesC& aFileNameOfFepDll); // not available before Release 005
	IMPORT_C CCoeFep* Fep() const; // not available before Release 005
	IMPORT_C TUid FepUid() const; // not available before Release 006
	IMPORT_C CWindowGc* SwapSystemGc(CWindowGc* aGc); // not available before Release 005
	IMPORT_C static CCoeStatic* Static(TUid aUid);
	IMPORT_C void DisableExitChecks(TBool aDisable);
	IMPORT_C void InputCapabilitiesChanged(); // not available before Release 6.1
public: // *** Do not use! API liable to change ***
	IMPORT_C CCoeFepParameters* FepParameters();
public: // Internal to Symbian
	IMPORT_C void GetMessageNotifyingObserversLC(TUint32 aClientHandleOfTargetWindowGroup, TUid& aMessageUid, TPtr8& aMessageParameters, const TWsEvent& aMessageEvent);
protected: // Internal to Symbian
	IMPORT_C void SetUpFepL(CCoeFepParameters* aFepParameters, const TDesC& aFileNameOfDefaultFepDll);
private: // reserved virtual function space
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
public: // but not exported
	void ReadEvent();
	CVwsSessionWrapper* InitViewServerSessionL(MVwsSessionWrapperObserver& aObserver);
	void AddStatic(CCoeStatic* aStatic);
	CCoeStatic* RemoveStatic(TUid aUid);
	void QueueNotificationToFocusObserversOfChangeInFocus();
	TInt FocusObserverNotificationIdentifier() const;
	TBool FocusObserverNotificationIsStillPending(TInt aFocusObserverNotificationIdentifier) const;
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
	void InitScreenL();
	void InitRootWindowL(TBool aInitialFocusState);
	void InitSystemGcL();
	RResourceFile& ResourceFileForId(TInt aResourceId) const;
	void DestroyAllResourceFiles();
	void AddObserverL(TAny* aObserver, RGenericPointerArray& aArray);
	void RemoveObserver(TAny* aObserver, RGenericPointerArray& aArray);
	inline TBool DisableShutdownChecks() const;
	void UpdateStatic(CCoeAppUiBase* aNewAppUi);
	void SetInitialHandleCount();
	inline TUint InitialHandleCount() const;
protected:
	CCoeAppUiBase* iAppUi;
	RFs iFsSession;
	RWsSession iWsSession;
	RWindowGroup iRootWin;
	CWindowGc* iSystemGc;
	const CFont* iNormalFont;
	CWsScreenDevice* iScreen;
	TWsEvent iLastEvent;
	CArrayFix<RResourceFile>* iResourceFileArray;
	enum {KErrorTextLength = 80};

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


/**
 *
 * Base class for creating singleton objects that will be stored by
 * <code>CCoeEnv</code>.
 *
 * Each object must have a unique <code>TUid</code>.The Symbian Platform
 * does not provide writeable global static data. Singleton objects
 * provide its equivalent in thread local storage which is supported.This
 * behaviour is useful for objects in which only one copy is ever needed
 * in the thread or application, e.g. in alert windows.
 *
 * @since 6.0
 * @lib "cone.lib"
 */
class CCoeStatic : public CBase
	{
public:
	/**
	 * Scope of access to the singleton object.
	 * @since 6.0
	 */
	enum TScope
		{
		EThread,	/** Access from the entire thread.*/
		EApp,		/** Access from an appUi in that thread.*/
		};
public:
	IMPORT_C ~CCoeStatic();
protected:
	IMPORT_C CCoeStatic(TUid aUid,TScope=EThread);
private:
	TDblQueLink iCsLink;
	TUid iCsUid;
	CCoeAppUiBase* iCsAppUi;
	TScope iCsScope;
private:
	friend class CCoeEnv;
	friend class CCoeEnvExtra;
	};

/**
 *
 * Gets the most recent standard event that was received by the
 * application.
 *
 * Note:Standard events are all events except redraw events and priority
 * key events.
 *
 * @returns   "TWsEvent&"
 *            The last event.
 */
inline const TWsEvent& CCoeEnv::LastEvent() const
	{ return(iLastEvent); }
/**
 *
 * Gets the application UI owned by this application.
 *
 * @returns   "CCoeAppUiBase*"
 *            Pointer to the app UI owned by the application.
 */
inline CCoeAppUiBase* CCoeEnv::AppUi() const
	{ return(iAppUi); }
/**
 *
 * Gets the file server session owned by this <code>CCoeEnv</code>.
 *
 * This session is normally only used for accessing the application's
 * resource file.
 *
 * @returns   "RFs&"
 *            The file server session owned by this
 *            <code>CCoeEnv</code>.
 */
inline RFs& CCoeEnv::FsSession() const
	{ return((RFs&)iFsSession); }
/**
 *
 * Gets the window server session owned by the application.
 *
 * This provides access to window server functions not directly
 * accessible via the UI control framework.
 *
 * @returns   "RWsSession&"
 *            The window server session opened by the application.
 */
inline RWsSession& CCoeEnv::WsSession() const
	{ return((RWsSession&)iWsSession); }
/**
 *
 * Gets the application's window group.
 *
 * Note:A window group is an invisible window which acts as the parent
 * window for all other windows in an application. Typically, each
 * application has one window group. In the window server, window groups
 * are also the unit of keyboard focus.
 *
 * @returns   "RWindowGroup&"
 *            The application's window group.
 */
inline RWindowGroup& CCoeEnv::RootWin() const
	{ return((RWindowGroup&)iRootWin); }
/**
 *
 * Gets the system graphics context.
 *
 * This is the graphics contexts typically used for drawing controls, but
 * an alternative graphics context can be created if required using
 * <code>CreateGcL()</code>.
 *
 * @returns   "CWindowGc&"
 *            The system graphics context.
 */
inline CWindowGc& CCoeEnv::SystemGc() const
	{ return((CWindowGc&)*iSystemGc); }
/**
 *
 * Gets the normal environment font.
 *
 * This is the font created during construction of the control
 * environment.
 *
 * @returns   "CFont*"
 *            Pointer to the normal environment font.
 */
inline const CFont* CCoeEnv::NormalFont() const
	{ return(iNormalFont); }
/**
 *
 * Gets the default screen device owned by this <code>CCoeEnv</code>.
 *
 * This is typically used as the standard screen device for the
 * <code>CCoeEnv</code>'s application.
 *
 * @returns   "CWsScreenDevice*"
 *            The default screen device owned by this
 *            <code>CCoeEnv</code>.
 */
inline CWsScreenDevice* CCoeEnv::ScreenDevice() const
	{ return(iScreen); }
/**
 *
 * Gets the current error message text.
 *
 * @returns   "TDes&"
 *            The current error message text.
 */
inline TDes& CCoeEnv::ErrorText() 
	{ return *iErrorText; }
/**
 *
 * Gets the current error context text.
 *
 * @returns   "TDes&"
 *            The current error context text.
 */
inline TDes& CCoeEnv::ErrorContextText() 
	{ return *iErrorContextText; }

#if defined(_UNICODE)
/**
 *
 * @deprecated 7.0
 * Deprecated - Use .CCoeEnv::ReadResourceL instead
 *
 * Reads a resource into a descriptor.
 *
 * The descriptor must be long enough to contain the entire resource. No
 * memory is allocated by this function.If the read fails the function
 * sets an error condition and performs any cleanup required. The error
 * condition causes the GUI to launch an alert window.
 *
 * @param     "TDes& aDes"
 *            On return, contains the resource.
 * @param     "TInt aResourceId"
 *            The numeric ID of the resource to be read.
 */
inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes16(aDes,aResourceId); }
/**
 *
 * Reads a resource into a descriptor.
 *
 * The descriptor must be long enough to contain the entire resource. 
 * The method leaves if reading from the resource file generates an error.
 *
 * @param     "TDes& aDes"
 *            On return, contains the resource.
 * @param     "TInt aResourceId"
 *            The numeric ID of the resource to be read.
 */
inline void CCoeEnv::ReadResourceL(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes16L(aDes,aResourceId); }
/**
 *
 * Reads a specified resource into a heap descriptor, allocating memory
 * for the descriptor.
 *
 * Note:The calling program must destroy the heap descriptor when it is
 * no longer needed.
 *
 * @param     "TInt aResourceId"
 *            The numeric ID of the resource to be read.
 * @returns   "HBufC*"
 *            Pointer to a heap descriptor containing the resource.
 */
inline  HBufC* CCoeEnv::AllocReadResourceL(TInt aResourceId) const
	{ return AllocReadResourceAsDes16L(aResourceId); }

/**
 *
 * Reads a specified resource into a heap descriptor, allocating memory
 * for the descriptor, and pushing the descriptor onto the cleanup stack.
 *
 * The calling program should pop and destroy the heap descriptor when it
 * is no longer needed.
 *
 * @param     "TInt aResourceId"
 *            The numeric ID of the resource to be read.
 * @returns   "HBufC*"
 *            Pointer to a heap descriptor containing the resource.
 */
inline HBufC* CCoeEnv::AllocReadResourceLC(TInt aResourceId) const
	{ return AllocReadResourceAsDes16LC(aResourceId); }
/**
 *
 * Reads a resource into a build-independent descriptor array.
 *
 * Note:<code>CDesCArrayFlat</code> is a <code>CDesC8ArrayFlat</code> for
 * ER5, and <code>CDesC16ArrayFlat</code> for post ER5 builds.
 *
 * @param     "TInt aResourceId"
 *            The numeric ID of the resource to be read.
 * @returns   "CDesCArrayFlat*"
 *            A pointer to the descriptor array containing the
 *            resource data.
 */
inline CDesCArrayFlat* CCoeEnv::ReadDesCArrayResourceL(TInt aResourceId)
	{ return ReadDesC16ArrayResourceL(aResourceId); }
#else  // not UNICODE

/**
 * @deprecated 7.0
 * Deprecated - Use .CCoeEnv::ReadResourceL instead
 */
inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
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

/**
 *
 * Tests if the Active Scheduler is started in the CCoeEnv::ExecuteD
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if Active Scheduler is started in
 *								 CCoeEnv::ExecuteD()	
 *            <code>EFalse</code> if Active Scheduler is not started in
 *								  CCoeEnv::ExecuteD()	
 *            
 */
inline TBool CCoeEnv::IsSchedulerRunning() const
	{return iEnvFlags&ESchedulerIsRunning;}

#endif
