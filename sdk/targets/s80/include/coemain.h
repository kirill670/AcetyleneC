// COEMAIN.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
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
 * The enumeration <code>TActivePriority</code> specifies the UI Control 
 * Framework active object priorities. These are in addition to the values 
 * contained in the <code>TPriority</code> enumeration in class 
 * <code>CActive</code>. 
 * 
 * @lib [what]
 * @publishedAll
 * @released 
 */
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

/** 
 * The <code>MCoeObserverOfLoadedFep</code> class is an interface class that 
 * provides notification 
 * when there is a change in the currently loaded FEP. This happens either on 
 * application start-up or as a result of a different front end processor 
 * having been installed. To use this notification, the developer should 
 * derive from this class and implement its pure virtual method. Derived 
 * classes also need to call <code>CCoeEnv::AddObserverOfLoadedFepL()</code>
 * during construction and <code>CCoeEnv::RemoveObserverOfLoadedFep()</code>
 * in their destructor. 
 *
 * @lib [what]
 * @publishedAll
 * @released 
 */
class MCoeObserverOfLoadedFep

    {
public:
   /** 
    * Handles a change in the loaded FEP. This method is called if a new FEP 
    * is loaded, or if the current one is unloaded. 
    *
    * @remarks
    * @see
    */
    virtual void HandleChangeInLoadedFep()=0;
private:
    IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_1();
    IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_2();
    };

class TCoeInputCapabilities; // forward declaration of class defined in COEINPUT.H

/** 
 * The <code>MCoeFocusObserver</code> class is an interface class that provides 
 * notification if any control gains or loses focus or is destroyed. The FEP 
 * framework uses this class to observe when a target control changes for 
 * reasons unrelated to the FEP. To use such a notification, the developer 
 * should derive from this class and implement its two pure virtual methods. 
 * In addition, derived classes need to call 
 * <code>CCoeEnv::AddFocusObserverL()</code> during construction and 
 * <code>CCoeEnv::RemoveFocusObserver()</code> in their destructors. See also 
 * <code>CCoeFep</code>.
 * 
 * @lib [what]
 * @publishedAll
 * @released 
 */
class MCoeFocusObserver

    {
public:
   /** 
    * Handles changes in focus. This method is called if any control gains or 
    * loses focus. 
    *
    * @remarks
    * @see
    */
    virtual void HandleChangeInFocus()=0;
   /** 
    * Handles the destruction of any control. It is called by the framework if 
    * any control is destroyed. 
    *
    * @remarks
    * @see
    */
    virtual void HandleDestructionOfFocusedItem()=0;
private:
    IMPORT_C virtual void MCoeFocusObserver_Reserved_1();
    IMPORT_C virtual void MCoeFocusObserver_Reserved_2();
    };

/** 
 * The <code>MCoeResourceChangeObserver</code> class is an interface class that 
 * enables message windows to observe resource changes. Resource change 
 * observers should be added to the control environment using 
 * <code>CCoeEnv::AddResourceChangeObserverL()</code>.  
 * 
 * @lib [what]
 * @released 
 * @publishedAll
 */
class MCoeResourceChangeObserver

    {
public:
   /** 
    * Handles a change to the application's resources. 
    *
    * @remarks
    * @see
    */
    virtual void HandleResourceChange()=0;
private:
    IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_1();
    IMPORT_C virtual void MCoeResourceChangeObserver_Reserved_2();
    };

/** 
 * The <code>MCoeForegroundObserver</code> class is an interface class that  
 * provides notification of foreground/background changes. The FEP framework 
 * class, <code>CCoeFep</code>, derives from <code>MCoeForegroundObserver</code>,
 * which enables FEPs to receive notification when the target application 
 * (which receives the FEP's output) goes into the foreground or background.
 * To use this notification, the developer should derive from this class and 
 * override its two pure virtual methods. In addition, derived classes also 
 * need to call <code>CCoeEnv::AddForegroundObserverL()</code> during 
 * construction and <code>CCoeEnv::RemoveForegroundObserver()</code> in their 
 * destructors. See also <code>CCoeFep</code>.
 * 
 * @lib [what]
 * @publishedAll
 * @released 
 */
class MCoeForegroundObserver

    {
public:
   /** 
    * Handles the application coming to the foreground. 
    *
    * @remarks
    * @see
    */
    virtual void HandleGainingForeground()=0;
   /** 
    * Handles the application going into the background. 
    *
    * @remarks
    * @see
    */
    virtual void HandleLosingForeground()=0;
private:
    IMPORT_C virtual void MCoeForegroundObserver_Reserved_1();
    IMPORT_C virtual void MCoeForegroundObserver_Reserved_2();
    };

/** 
 * The <code>MCoeForegroundObserver</code> class is an interface class that
 * handles incoming window server messages. This interface is used to enable 
 * FEPs to keep their settings synchronized across all running instances. 
 * Anything that needs to be notified of messages that are sent by the window 
 * server's message-sending service should derive from this class and override 
 * its pure virtual method. In addition, derived classes also need to call 
 * <code>CCoeEnv::AddMessageObserverL()</code> during construction and 
 * <code>CCoeEnv::RemoveMessageObserver()</code> in their destructors. 
 * 
 * @lib [what]
 * @publishedAll
 * @released 
 */
class MCoeMessageObserver

    {
public:
   /** 
    * The enumeration <code>TMessageResponse</code> specifies the message 
    * response flags. 
    */
    enum TMessageResponse
        {
        /** the message is not handled */
        EMessageNotHandled,
        /** the message is handled */
        EMessageHandled
        };
public:
   /** Handles window server messages. Implementations should return 
    * <code>EMessageHandled</code> if they are able to handle the message, or 
    * <code>EMessageNotHandled</code> if the message is not appropriate to this 
    * observer. 
    *
    * @param aClientHandleOfTargetWindowGroup The window group that the message 
    *                                         was sent to. Many implementations 
    *                                         will not need this information
    * @param aMessageUid The message UID
    * @param aMessageParameters The message parameters
    * @return indicates whether the message was handled or not handled by the 
    *         method 
    * @remarks
    * @see
    */
    virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters)=0;
private:
    IMPORT_C virtual void MCoeMessageObserver_Reserved_1();
    IMPORT_C virtual void MCoeMessageObserver_Reserved_2();
    };

// classes defined in FEPBASE, declared here
class MCoeFepObserver;

/** 
@publishedAll
@released
*/
typedef void (*TCoeFepObserverFunction)(MCoeFepObserver& aFepObserver);
class CCoeFepParameters; // must derive from CBase
class CCoeFep; // must derive from CBase

/** 
 * Implements the active scheduler presupposed by the control environment.
 * @publishedAll
 * @deprecated
 */
class CCoeScheduler : public CBaActiveScheduler

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

/** 
 * The <code>CCoeEnv</code> class is the control environment. <code>CCoeEnv</code> 
 * provides an active environment for creating controls. It implements active 
 * objects and an active scheduler, which provide access to the window server, 
 * simplifying the API for application programs. It also provides utility 
 * methods that are useful to many applications. When a standard event occurs,
 * the active scheduler calls <code>CCoeEnv::RunL()</code>. When a redraw event 
 * occurs, it calls <code>CCoeRedrawer::RunL()<code>. Priority key events must 
 * be accessed using the Window Server API directly. <b>Note</b>: Standard 
 * events are all events except redraw events and priority key events.
 *
 * @lib [what]
 * @publishedAll
 * @released 
 */
class CCoeEnv : public CActive

    {
public:
   /**
    * The object destructor.
    */
    IMPORT_C ~CCoeEnv();
   /** 
    * The default object constructor.
    */
    IMPORT_C CCoeEnv();
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C virtual void DestroyEnvironment();
    /**
    * [what]
    * 
    * @param aAppUi [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CCoeAppUiBase* SetAppUi(CCoeAppUiBase* aAppUi);
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void ExecuteD();
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void RunL();
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void DoCancel();
    /**
    * [what]
    * 
    * @param aError [what]
    * @remarks
    * @see
    */
    IMPORT_C virtual void HandleError(TInt aError);
    /**
    * Completes construction of a <code>CCoeEnv</code> object.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void ConstructL();
    /**
    * Completes construction of a <code>CCoeEnv</code> object.
    * 
    * @param aInitialFocusState [what]
    * @remarks
    * @see
    */
    IMPORT_C void ConstructL(TBool aInitialFocusState);

    /**
    * Gets the most recent standard event that was received by the application.
    * <b>Note</b>: Standard events are all events except redraw events and 
    * priority key events.
    * 
    * @return the last event
    * @remarks
    * @see
    */
    inline const TWsEvent& LastEvent() const;

    /**
    * Gets the application UI owned by this application.
    * 
    * @return a pointer to the AppUI owned by the application
    * @remarks
    * @see
    */
    inline CCoeAppUiBase* AppUi() const;

    /**
    * Gets the file server session owned by this <code>CCoeEnv</code>. This 
    * session is normally only used for accessing the application's resource 
    * file.
    * 
    * @return the file server session owned by this <code>CCoeEnv</code>
    * @remarks
    * @see
    */
    inline RFs& FsSession() const;

    /**
    * Gets the window server session owned by the application. This provides 
    * access to window server methods not directly accessible via the UI 
    * Control Framework.
    * 
    * @return the window server session opened by the application
    * @remarks
    * @see
    */
    inline RWsSession& WsSession() const;

    /**
    * Gets the application's window group. <b>Note</b>: A window group is an 
    * invisible window that acts as the parent window for all other windows in 
    * an application. Typically, each application has one window group. In the 
    * window server, window groups are also the unit of keyboard focus.
    * 
    * @return the application's window group
    * @remarks
    * @see
    */
    inline RWindowGroup& RootWin() const;

    /**
    * Gets the system graphics context. This is the graphics context typically 
    * used for drawing controls, but an alternative graphics context can be 
    * created using <code>CreateGcL()</code>, if required.
    * 
    * @return the system graphics context
    * @remarks
    * @see
    */
    inline CWindowGc& SystemGc() const;

    /**
    * Gets the normal environment font. This is the font created during 
    * construction of the control environment.
    * 
    * @return a pointer to the normal environment font
    * @remarks
    * @see InitSystemFontsL()
    */
    inline const CFont* NormalFont() const;

    /**
    * Gets the default screen device owned by this <code>CCoeEnv</code>. 
    * Typically, this is used as the standard screen device for the 
    * <code>CCoeEnv</code> object's application.
    * 
    * @return the default screen device owned by this <code>CCoeEnv</code>
    * @remarks
    * @see
    */
    inline CWsScreenDevice* ScreenDevice() const;

    /**
    * Tests if the Active Scheduler is started in the <code>CCoeEnv::ExecuteD</code>.
    * 
    * @return <code>ETrue</code> if Active Scheduler is started in
    *         <code>CCoeEnv::ExecuteD()</code>. <code>EFalse</code> if Active 
    *         Scheduler is not started in <code>CCoeEnv::ExecuteD()</code>
    * @remarks
    * @see
    */
    inline TBool IsSchedulerRunning() const;

    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CWindowGc* CreateGcL();

    /**
    * [what]
    * 
    * @param aDelay [what]
    * @remarks
    * @see
    */
    IMPORT_C void Flush(TTimeIntervalMicroSeconds32 aDelay=0);

    /**
    * [what]
    * 
    * @param aDevice [what]
    * @param aFontSpec [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CFbsFont* CreateDeviceFontL(CGraphicsDevice* aDevice,const TFontSpec& aFontSpec);

    /**
    * [what]
    * 
    * @param aFontSpec [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CFbsFont* CreateScreenFontL(const TFontSpec& aFontSpec);

    /**
    * [what]
    * 
    * @param aFont [what]
    * @remarks
    * @see
    */
    IMPORT_C void ReleaseScreenFont(CFont* aFont) const;

    /**
    * [what]
    * 
    * @param aReader [what]
    * @param aResourceId [what]
    * @remarks
    * @see
    */
    IMPORT_C void CreateResourceReaderLC(TResourceReader& aReader,TInt aResourceId) const;

    /** 
    * @deprecated
    * @see CCoeEnv::ReadResourceL
    */
    inline void ReadResource(TDes& aDes,TInt aResourceId) const; 

    /**
    * Reads a resource into a descriptor. The descriptor must be long enough 
    * to contain the entire resource. No memory is allocated by this method.
    * 
    * @param aDes On return, contains the resource data
    * @param aResourceId The numeric ID of the resource to be read
    * @see RResourceFile::ReadL()
    * @see KErrCoeFailedToReadFromProgDisk
    */
    inline void ReadResourceL(TDes& aDes,TInt aResourceId) const;

    /**
    * Reads a resource into a heap descriptor, allocating memory for it. 
    * <b>Note</b>: The calling program must destroy the heap descriptor when 
    * it is no longer needed.
    * 
    * @param aResourceId The numeric ID of the resource to be read
    * @return a pointer to a heap descriptor containing the resource data
    * @remarks
    * @see RResourceFile::AllocReadL()
    */
    inline  HBufC* AllocReadResourceL(TInt aResourceId) const;

    /**
    * Reads a specified resource into a heap descriptor, allocating memory for
    * it, and pushing the descriptor onto the cleanup stack. The calling 
    * program should pop and destroy the heap descriptor when it is no longer 
    * needed.
    * 
    * @param aResourceId The numeric ID of the resource to be read
    * @return a pointer to a heap descriptor containing the resource data
    * @remarks
    * @see RResourceFile::AllocReadLC()
    */
    inline HBufC* AllocReadResourceLC(TInt aResourceId) const;

    /**
    * [what]
    * 
    * @param aFileName [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C TInt AddResourceFileL(const TDesC& aFileName);
    /**
    * [what]
    * 
    * @param aOffset [what]
    * @remarks
    * @see
    */
    IMPORT_C void DeleteResourceFile(TInt aOffset);
    /**
    * Reads a resource into a Unicode descriptor array.
    * 
    * @param aResourceId The numeric ID of the resource to be read
    * @return a pointer to the descriptor array containing the resource data
    * @remarks
    * @see TResourceReader::ReadDesCArrayL()
    */
    inline CDesCArrayFlat* ReadDesCArrayResourceL(TInt aResourceId);

    /**
    * [what]
    * 
    * @param aMsg [what]
    * @param aContextText [what]
    * @remarks
    * @see
    */
    IMPORT_C void LeaveWithErrorText(const TDesC& aMsg,const TDesC* aContextText=NULL);
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @param ... [what]
    * @remarks
    * @see
    */
    IMPORT_C void Format128(TDes& aDes,TInt aResourceId,...);
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @param ... [what]
    * @remarks
    * @see
    */
    IMPORT_C void Format256(TDes& aDes,TInt aResourceId,...);
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C static TVersion Version();
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C static CCoeEnv* Static();
    /**
    * [what]
    * 
    * @param aKeyEvent [what]
    * @param aType [what]
    * @remarks
    * @see
    */
    IMPORT_C void SimulateKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C TBool IsWservEventPending() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C TBool IsRedrawEventPending() const;
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void PrepareToExit();
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void BringOwnerToFront();
    /**
    * @deprecated
    */
    IMPORT_C void ReadResourceAsDes8(TDes8& aDes,TInt aResourceId) const; /** @deprecated 7.0*/
    /**
    * [what]
    * 
    * @param aDes [what]
    * @param aResourceId [what]
    * @remarks
    * @see
    */
    IMPORT_C void ReadResourceAsDes8L(TDes8& aDes,TInt aResourceId) const;
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C HBufC8* AllocReadResourceAsDes8L(TInt aResourceId) const;
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C HBufC8* AllocReadResourceAsDes8LC(TInt aResourceId) const;
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CDesC8ArrayFlat* ReadDesC8ArrayResourceL(TInt aResourceId);
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void SuppressNextFlush();
    /** @deprecated */
    IMPORT_C void ReadResourceAsDes16(TDes16& aDes,TInt aResourceId) const; /** @deprecated 7.0*/
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @param aDes [what]
    * @remarks
    * @see
    */
    IMPORT_C void ReadResourceAsDes16L(TDes16& aDes,TInt aResourceId) const; 
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C HBufC16* AllocReadResourceAsDes16L(TInt aResourceId) const; // not available before Release 005
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C HBufC16* AllocReadResourceAsDes16LC(TInt aResourceId) const; // not available before Release 005
    /**
    * [what]
    * 
    * @param aResourceId [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CDesC16ArrayFlat* ReadDesC16ArrayResourceL(TInt aResourceId); // not available before Release 005
    /**
    * [what]
    * 
    * @param aObserverOfLoadedFep [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddObserverOfLoadedFepL(MCoeObserverOfLoadedFep& aObserverOfLoadedFep); // not available before Release 005
    /**
    * [what]
    * 
    * @param aObserverOfLoadedFep [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveObserverOfLoadedFep(MCoeObserverOfLoadedFep& aObserverOfLoadedFep); // not available before Release 005
    /**
    * [what]
    * 
    * @param aFocusObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddFocusObserverL(MCoeFocusObserver& aFocusObserver); // not available before Release 005
    /**
    * [what]
    * 
    * @param aFocusObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveFocusObserver(MCoeFocusObserver& aFocusObserver); // not available before Release 005
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void SyncNotifyFocusObserversOfChangeInFocus();
    /** @internal  */
    void NotifyFocusObserversOfDestructionOfFocusedItem(); // not to be called from outside CONE
    /**
    * [what]
    * 
    * @param aForegroundObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddForegroundObserverL(MCoeForegroundObserver& aForegroundObserver); // not available before Release 005
    /**
    * [what]
    * 
    * @param aForegroundObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveForegroundObserver(MCoeForegroundObserver& aForegroundObserver); // not available before Release 005
    /** @internal */
    void NotifyForegroundObserversOfGainingForeground(); // not to be called from outside CONE
    /** @internal */
    void NotifyForegroundObserversOfLosingForeground(); // not to be called from outside CONE
    /**
    * [what]
    * 
    * @param aResourceChangeObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddResourceChangeObserverL(MCoeResourceChangeObserver& aResourceChangeObserver); 
    /**
    * [what]
    * 
    * @param aResourceChangeObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveResourceChangeObserver(MCoeResourceChangeObserver& aResourceChangeObserver); 
    /** @internal */
    void NotifyResourceObserversOfChangeInResource(); 
    /**
    * [what]
    * 
    * @param aMessageObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddMessageObserverL(MCoeMessageObserver& aMessageObserver); // not available before Release 005
    /**
    * [what]
    * 
    * @param aMessageObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveMessageObserver(MCoeMessageObserver& aMessageObserver); // not available before Release 005
    /**
    * [what]
    * 
    * @param aFepObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void AddFepObserverL(MCoeFepObserver& aFepObserver); // not available before Release 005
    /**
    * [what]
    * 
    * @param aFepObserver [what]
    * @remarks
    * @see
    */
    IMPORT_C void RemoveFepObserver(MCoeFepObserver& aFepObserver); // not available before Release 005
    /**
    * [what]
    * 
    * @param aFepObserverFunction [what]
    * @remarks
    * @see
    */
    IMPORT_C void ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction); // not available before Release 005
    /** @internal */
    void LoadFepL(); // not to be called from outside CONE
    /** @internal */
    void LoadFepL(const TDesC& aFileNameOfFepDll); // not to be called from outside CONE
    /**
    * [what]
    * 
    * @param aFileNameOfFepDll [what]
    * @remarks
    * @see
    */
    IMPORT_C void InstallFepL(const TDesC& aFileNameOfFepDll); // not available before Release 005
    /**
    * [what]
    * 
    * @param aFileNameOfFepDll [what]
    * @param aLeave [what]
    * @remarks
    * @see
    */
    IMPORT_C void InstallFepL(const TDesC& aFileNameOfFepDll, const TBool aLeave);
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C HBufC* NameOfInstalledFepL(); // not available before Release 005
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C MDesCArray* FileNamesOfAvailableFepsL(); // not available before Release 005
    /**
    * [what]
    * 
    * @param aFileNameOfFepDll [what]
    * @remarks
    * @see
    */
    IMPORT_C void ExecuteFepSettingsDialogL(const TDesC& aFileNameOfFepDll); // not available before Release 005
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CCoeFep* Fep() const; // not available before Release 005
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C TUid FepUid() const; // not available before Release 006
    /**
    * [what]
    * 
    * @param aGc [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CWindowGc* SwapSystemGc(CWindowGc* aGc); // not available before Release 005
    /**
    * [what]
    * 
    * @param aUid [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C static CCoeStatic* Static(TUid aUid);
    /**
    * [what]
    * 
    * @param aUid [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C CCoeStatic* FindStatic(TUid aUid);
    /**
    * [what]
    * 
    * @param aDisable [what]
    * @remarks
    * @see
    */
    IMPORT_C void DisableExitChecks(TBool aDisable);
    /**
    * [what]
    * 
    * @remarks
    * @see
    */
    IMPORT_C void InputCapabilitiesChanged(); // not available before Release 6.1
public: 
    /** Do not use! API liable to change */
    IMPORT_C CCoeFepParameters* FepParameters();
public: 
    /** @internal */
    IMPORT_C void GetMessageNotifyingObserversLC(TUint32 aClientHandleOfTargetWindowGroup, TUid& aMessageUid, TPtr8& aMessageParameters, const TWsEvent& aMessageEvent);
protected: // Internal to Symbian
    IMPORT_C void SetUpFepL(CCoeFepParameters* aFepParameters, const TDesC& aFileNameOfDefaultFepDll);
private: // reserved virtual function space
    IMPORT_C virtual void Reserved_1();
    IMPORT_C virtual void Reserved_2();
public: // but not exported
    /** @internal */
    void ReadEvent();
    /** @internal */
    CVwsSessionWrapper* InitViewServerSessionL(MVwsSessionWrapperObserver& aObserver);
    /** @internal */
    void AddStatic(CCoeStatic* aStatic);
    /** @internal */
    void QueueNotificationToFocusObserversOfChangeInFocus();
    /** @internal */
    TInt FocusObserverNotificationIdentifier() const;
    /** @internal */
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

private:
    enum TFlags // used in the bottom 16 bits only of iEnvFlags
        {
        ENoShutdownChecks           =0x0001,
        EExtraPointerIsErrorCode    =0x0002,
        ESchedulerIsRunning         =0x0004
        };
private:
    TDes* iErrorText;
    TDes* iErrorContextText;
    CCoeEnvExtra* iExtra;
    CTrapCleanup* iCleanup;
    TUint iEnvFlags;
    };

/** 
 * The <code>CCoeStatic</code> class is a base class for creating singleton 
 * objects that will be stored by <code>CCoeEnv</code>. Each object must have 
 * a unique <code>TUid</code>. Symbian OS does not provide writeable global 
 * static data. Singleton objects provide its equivalent in thread local 
 * storage, which is supported. This behavior is useful for objects in which 
 * only one copy is ever needed in the thread or application, for example, in 
 * alert windows. 
 * 
 * @lib [what]
 * @publishedAll 
 * @released 
 */
class CCoeStatic : public CBase

    {
public:
   /** 
    * The enumeration <code>TScope</code> specifies the scope of access to the 
    * singleton object. 
    */
    enum TScope
        {
        /** access from the entire thread */
        EThread,
        /** access from an AppUI in that thread */
        EApp,
        };
   /** 
    * The enumeration specifies the default destruction priority if none is 
    * specified in the constructor.
    */
    enum 
        {
        /** [what] */
        EDefaultDestructionPriority=100
        };
public:
    /** The object destructor. */
    IMPORT_C ~CCoeStatic();
protected:
    IMPORT_C CCoeStatic(TUid aUid,TScope=EThread);
    IMPORT_C CCoeStatic(TUid aUid,TInt aDestructionPriority,TScope aScope=EThread);
private:
    void DoConstruction(TUid aUid,TInt aDestructionPriority,TScope aScope);
    void SetCsAppUi(CCoeAppUiBase* aAppUi);
    CCoeAppUiBase* CsAppUi() const;
    TScope CsScope() const;
    inline TInt DestructionPriority() const {return iCsLink.iPriority;}
private:
    TPriQueLink iCsLink;
    TUid iCsUid;
    TUint iCsAppUiAndScope;
private:
    friend class CCoeEnv;
    friend class CCoeEnvExtra;
    };

inline const TWsEvent& CCoeEnv::LastEvent() const
/** Gets the most recent standard event that was received by the application.

Note: standard events are all events except redraw events and priority key events.

@return The last event. */
    { return(iLastEvent); }

inline CCoeAppUiBase* CCoeEnv::AppUi() const
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
/** Deprecated - Use .CCoeEnv::ReadResourceL() instead.

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
// @returns   "TBool"
//            <code>ETrue</code> if Active Scheduler is started in
//                               CCoeEnv::ExecuteD()    
//            <code>EFalse</code> if Active Scheduler is not started in
//                                CCoeEnv::ExecuteD()   
//            
inline TBool CCoeEnv::IsSchedulerRunning() const
    {return iEnvFlags&ESchedulerIsRunning;}

#endif
