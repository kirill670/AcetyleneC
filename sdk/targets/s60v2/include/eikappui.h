// EIKAPPUI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKAPPUI_H__)
#define __EIKAPPUI_H__

#if !defined(__COEAUI_H__)
#include <coeaui.h>
#endif

#if !defined(__COEMAIN_H__)
#include <coemain.h>
#endif

#if !defined(__EIKMOBS_H__)
#include <eikmobs.h>
#endif

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

#if !defined(__VWSDEF_H__)
#include <vwsdef.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__BAERRHAN_H__)
#include <baerrhan.h>
#endif

#if !defined(__EIKAUFTY_H__)
#include <eikaufty.h>
#endif

#if !defined(__AKNWSEVENTOBSERVER_H__)
#include <AknWsEventObserver.h>
#endif

#include <coemop.h>
#include <akndef.h>

class MEikMenuBar;
class MEikMenuPane;
class CEikDocument;
class CEikApplication;
class MApaEmbeddedDocObserver;
struct SExtendedError;
class MEikAppUiFactory;
class CAknKeySoundSystem;
class CEikAppUiExtension;

const TUid KUidEikColorSchemeStore={0x1};
const TUid KUidEikColorSchemeStream={0x1};

class CEikAppUi : public CCoeAppUi, public MEikMenuObserver, public MCoeMessageObserver, public MObjectProvider
/** Handles application-wide aspects of the application's user interface such 
as the menu bar, toolbar pop-up menus, opening and closing files and exiting the 
application cleanly. 

Every GUI application should use its own class derived from CEikAppUi. 

An app UI's main role is to handle commands, in its HandleCommandL() function. 
These may be invoked using the menu bar, toolbar, or hotkeys; the commands 
that an app UI handles are specified in the application's resource file.

In addition, the app UI normally needs to respond to other kinds of events, by 
providing suitable implementations of the following virtual functions, all 
inherited from CCoeAppUi: 

- HandleKeyEventL(): Key events.

- HandleForegroundEventL(): Application switched to foreground.

- HandleSwitchOnEventL(): Machine switched on.

- HandleSystemEventL(): System events.

- HandleApplicationSpecificEventL(): Application-specific events.

@publishedAll
@released */
	{
private:
	friend class CAknAppUi;
	enum
		{
		EStandardAppFlag			= 0x00,
		ENoAppResourceFileFlag		= 0x01,
		ENonStandardResourceFileFlag= 0x02,
		ENoScreenFurnitureFlag		= 0x04,
		ELayoutAwareAppFlag			= 0x08,
		EAppOrientationSpecifiedFlag= 0x10,
		EAppOrientationLandscapeFlag= 0x20,
		EAppOrientationAutomaticFlag= 0x80,
		EAknEnableSkinFlag			= 0x1000,
		ELayoutAwareBuild			= ELayoutAwareAppFlag
		};

public:
	enum
		{
		EStandardApp				= ELayoutAwareBuild | EStandardAppFlag,
		ENoAppResourceFile			= ELayoutAwareBuild | ENoAppResourceFileFlag,
		ENonStandardResourceFile	= ELayoutAwareBuild | ENonStandardResourceFileFlag,
		ENoScreenFurniture			= ELayoutAwareBuild | ENoScreenFurnitureFlag,
		ELastReservedEikAppUiFlag	= 0x1000,
        /**
        * Flag indicating that default skin parameters should be provided by
        * UI controls created within the scope of this AppUi instance.
        * This value (or binary combination with some other values) should
        * be given as a parameter to <code>BaseConstructL</code> in case
        * the application wants to enable default skin parameters for all
        * the Avkon controls supporting them.
        *
        * Note: The value can be queried by using 
        * <code>AknsUtils::AvkonSkinEnabled()</code> from AknSkins.lib.
        *
        * @since 2.0
        */
        EAknEnableSkin				= ELayoutAwareBuild | EAknEnableSkinFlag,
		EAppOrientationPortrait     = ELayoutAwareBuild | EAppOrientationSpecifiedFlag,
		EAppOrientationLandscape    = ELayoutAwareBuild | EAppOrientationSpecifiedFlag | EAppOrientationLandscapeFlag,
		EAppOrientationAutomatic    = ELayoutAwareBuild | EAppOrientationSpecifiedFlag | EAppOrientationAutomaticFlag
		};

    enum TAppUiOrientation
        {
        /**
        * Use the default device screen rotation of the product for this application.
        * This is the default rotation setting for an application, and it should be used
        * by nearly all applications. 
        */
        EAppUiOrientationUnspecified,
        /**
        * Use a portrait screen rotation for this application.
        * This should only be used when an application specifically wants portrait
        * rotation. The device will select an appropriate portrait rotation, if one is
        * available.
        */
        EAppUiOrientationPortrait,
        /**
        * Use a landscape screen rotation for this application.
        * This should only be used when an application specifically wants landscape
        * rotation. The device will select an appropriate landscape rotation, if one is
        * available.
        */
        EAppUiOrientationLandscape,
        /**
        * Use the normal device screen rotation for this application.
        * Both portrait and landscape screen rotations are possible. The application
        * rotation follows device screen rotation.
        */
        EAppUiOrientationAutomatic
        };

public:
	IMPORT_C ~CEikAppUi();
	IMPORT_C CEikAppUi();
public: // new functions
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void HandleModelChangeL();
	IMPORT_C void LaunchPopupMenuL(TInt aResourceId,const TPoint& aTargetPos,TPopupTargetPosType aTargetType,const CEikHotKeyTable* aHotKeyTable=NULL);
	inline CEikAppUi* ContainerAppUi() const;
	IMPORT_C void SetDocument(CEikDocument* aDocument);
	IMPORT_C void SetEmbeddedDocInfo(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly);
	IMPORT_C virtual TBool ProcessCommandParametersL(TApaCommand aCommand,TFileName& aDocumentName,const TDesC8& aTail);
	IMPORT_C CEikDocument* Document() const;
	IMPORT_C CEikApplication* Application() const;
	IMPORT_C TRect ClientRect() const;
	IMPORT_C TRect ApplicationRect() const;
	IMPORT_C virtual void StopDisplayingMenuBar();
	IMPORT_C TBool FadeWhenInBackground();
	IMPORT_C void SetFaded(TBool aFade);
	IMPORT_C TBool IsFaded() const;
public: // new function
	IMPORT_C void ReportResourceChangedToAppL(TInt aType);
	IMPORT_C virtual void HandleCommandL(TInt aCommand);
	IMPORT_C virtual void ProcessMessageL(TUid aUid,const TDesC8& aParams);
	IMPORT_C virtual void OpenFileL(const TDesC& aFileName);
	IMPORT_C virtual void CreateFileL(const TDesC& aFileName);
	IMPORT_C virtual TErrorHandlerResponse HandleError(TInt aError,const SExtendedError& aExtErr,TDes& aErrorText,TDes& aContextText);
	IMPORT_C virtual void HandleResourceChangeL(TInt aType);
	IMPORT_C TBool IsForeground() const;
	IMPORT_C TBool IsPartialForeground() const;
	IMPORT_C TBool IsFullScreenApp() const;
	IMPORT_C TBool IsLayoutAwareApp() const;
	IMPORT_C void SetLayoutAwareApp(TBool aLayoutAwareApp);
	IMPORT_C TAppUiOrientation Orientation() const;
	IMPORT_C void SetOrientationL(TAppUiOrientation aOrientation);
	/** @since 3.0 */
	IMPORT_C TAknUiZoom LocalZoom() const;
	/** @since 3.0 */
	IMPORT_C void SetLocalUiZoomL(TAknUiZoom aZoom);
// Added for Avkon. Access method for the event monitor
	IMPORT_C CAknWsEventMonitor* EventMonitor() const;
	IMPORT_C CAknKeySoundSystem* KeySounds() const;
public: // from CCoeAppUiBase
	IMPORT_C void PrepareToExit();
protected: // new functions
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=EStandardApp);
	IMPORT_C void ReadAppInfoResourceL(TInt aResourceFileOffset=0);
	IMPORT_C void CreateHotKeyControlL(TInt aResourceId);
	IMPORT_C void SetDocChanged();
	IMPORT_C void SaveAnyChangesL();
	IMPORT_C void Exit();
	IMPORT_C void SaveL();
	IMPORT_C void ClosePopup();
	IMPORT_C TBool ProcessCommandParametersL(TApaCommand aCommand,TFileName& aDocumentName);
	IMPORT_C void SetFullScreenApp(TBool aIsFullScreen);
protected: // from MEikMenuObserver
	IMPORT_C void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
protected: // from CCoeAppUi
	IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent); // not available before ER5u
	IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination);
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
	IMPORT_C void HandleScreenDeviceChangedL();
private: // from MEikCommandObserver
	IMPORT_C void ProcessCommandL(TInt aCommand);
private: // from MEikMenuObserver
	IMPORT_C void SetEmphasis(CCoeControl* aMenuWindow,TBool aEmphasis);
protected: // from MCoeMessageObserver
	IMPORT_C MCoeMessageObserver::TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	IMPORT_C MObjectProvider* MopNext();
private: // from CCoeAppUiBase
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private: // new functions
	IMPORT_C virtual TBool ValidFileType(TUid aFileUid) const;
	IMPORT_C virtual void Reserved_3();
	IMPORT_C virtual void Reserved_4();
	void SimulateWsEventL(TInt aEvent);
	TInt FindAppWgIdBelowMeL();
	TInt EventForForegroundState(TBool aPartialFg, TBool aForeground);
	TBool ThreadIsForeground() const;
private: // new functions
	void CreateResourceIndependentFurnitureL();
	TBool ValidFileExists(const TDesC& aFileName);
    void UpdateSettingCacheAndForwardEventL( TInt aEventId );
	void ReportResourceChangedToAppStackL(CEikAppUi* aTopApp, TInt aEventId);
	void RestoreContainerAppsStateL();
protected:
	/** A pointer to the application's document. */
	CEikDocument* iDocument;
	/** A pointer to the containing app UI. This is NULL for non-embedded 
	apps. */
	CEikAppUi* iContainerAppUi;
	/** Embedded document observer. */
	MApaEmbeddedDocObserver* iDoorObserver;
	/** Indicates whether or not this is the app UI for an embedded, 
	read-only document. */
	TBool iEmbeddedAndReadOnly;
	TBitFlags iFlags;
	// Added for Avkon. Provides access to keysound server
	CAknKeySoundSystem* iKeySounds;	// Moved from CAknAppUi, because CEikSrvUi needs it as well
private:
	// Added for Avkon. Monitor events for emergency call support
	CAknWsEventMonitor* iEventMonitor;
	MEikAppUiFactory* iFactory;
	CEikAppUiExtension * iExtension;	
	TInt iSpare;
	};

inline CEikAppUi* CEikAppUi::ContainerAppUi() const
/** Returns the app UI inside which this app UI is embedded.

Embedded app UIs are used for editing embedded documents.

@return A pointer to this object's container app UI. NULL if this app 
UI is not embedded */
	{ return iContainerAppUi; }

#endif
