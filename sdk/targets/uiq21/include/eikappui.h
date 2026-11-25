// EIKAPPUI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKAPPUI_H__)
#define __EIKAPPUI_H__

#include <coeaui.h>
#include <coemain.h>
#include <eikmobs.h>
#include <apadef.h>
#include <vwsdef.h>
#include <eikdef.h>
#include <baerrhan.h>
#include <eikaufty.h>

class MEikMenuBar;
class MEikMenuPane;
class CEikDocument;
class CEikApplication;
class MApaEmbeddedDocObserver;
struct SExtendedError;

const TUid KUidEikColorSchemeStore={0x1};
const TUid KUidEikColorSchemeStream={0x1};

/**
 *
 * Handles application-wide aspects of the applications user interface
 * such as toolbar pop-up menus, opening and closing files and exiting
 * the application cleanly.
 *
 * App UIs handle commands, which are invoked using the menu bar,
 * toolbar, toolband and hotkeys; the commands that an app UI handles are
 * specified in its applications resource file.An applications UI is
 * responsible for opening and closing the application documents files in
 * response to user commands. It also owns and manages the core controls
 * of the user interface, for example the tool bar and menu bar, and
 * handles commands from these.Every Uikon application should use its own
 * class derived from <code>CEikAppUi</code> to handle application-wide
 * user interface details. Responses to various kinds of events can be
 * handled at the level of the app UI by providing suitable
 * implementations of the following virtual
 * functions:<code>CCoeAppUi::HandleKeyEventL()</code>: Key
 * events<code>CCoeAppUi::HandleForegroundEventL()</code>: Application
 * switched to foreground<code>CCoeAppUi::HandleSwitchOnEventL()</code>:
 * Machine switched on.<code>CCoeAppUi::HandleSystemEventL()</code>:
 * System events.<code>CCoeAppUi::HandleMessageReadyL()</code>: Message
 * ready.<code>CCoeAppUi::HandleApplicationSpecificEventL()</code>:
 * Application-specific events.<code>CEikAppUi::HandleCommandL()</code>:
 * Handles commands defined in resource files.
 *
 * @since 6.0
 * @lib " eikcore.lib "
 */
class CEikAppUi : public CCoeAppUi, public MEikMenuObserver, public MCoeMessageObserver
	{
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
	IMPORT_C void StopDisplayingMenuBar();
	IMPORT_C TBool FadeWhenInBackground();
	IMPORT_C void SetFaded(TBool aFaded);
public: // new function
	IMPORT_C void ReportResourceChangedToAppL(TInt aType);
	IMPORT_C virtual void HandleCommandL(TInt aCommand);
	IMPORT_C virtual void ProcessMessageL(TUid aUid,const TDesC8& aParams);
	IMPORT_C virtual void OpenFileL(const TDesC& aFileName);
	IMPORT_C virtual void CreateFileL(const TDesC& aFileName);
	IMPORT_C virtual TErrorHandlerResponse HandleError(TInt aError,const SExtendedError& aExtErr,TDes& aErrorText,TDes& aContextText);
	IMPORT_C virtual void HandleResourceChangeL(TInt aType);
public: // from CCoeAppUiBase
	IMPORT_C void PrepareToExit();
protected: // new functions
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=0);
	IMPORT_C void ReadAppInfoResourceL(TInt aResourceFileOffset=0);
	IMPORT_C void CreateHotKeyControlL(TInt aResourceId);
	IMPORT_C void SetDocChanged();
	IMPORT_C void SaveAnyChangesL();
	IMPORT_C void Exit();
	IMPORT_C void SaveL();
	IMPORT_C void ClosePopup();
	IMPORT_C TBool ProcessCommandParametersL(TApaCommand aCommand,TFileName& aDocumentName);
protected: // from MEikMenuObserver
	IMPORT_C void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
protected: // from CCoeAppUi
	IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent); // not available before ER5u
	IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination);
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
protected: // from MEikCommandObserver
	IMPORT_C void ProcessCommandL(TInt aCommand);
private: // from MEikMenuObserver
	IMPORT_C void SetEmphasis(CCoeControl* aMenuWindow,TBool aEmphasis);
protected: // from MCoeMessageObserver
	IMPORT_C MCoeMessageObserver::TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
private: // from CCoeAppUiBase
	IMPORT_C void HandleScreenDeviceChangedL(); // used to be Reserved_1()
	IMPORT_C void Reserved_2();
private: // new functions
	IMPORT_C virtual TBool ValidFileType(TUid aFileUid) const;
	IMPORT_C virtual void Reserved_3();
	IMPORT_C virtual void Reserved_4();
//	void DoLaunchPopupL(TInt aResourceId,const TPoint& aTargetPos, const CEikHotKeyTable* aHotKeyTable, TPopupTargetPosType aTargetType = EPopupTargetTopLeft);
public:
	/**
	 * The following enums relate to the use of an application resource file
	 * and screen furniture.
	 */
	enum
		{
		EStandardApp			= 0x00,		/** Application uses its standard application resource file. */
		ENoAppResourceFile		= 0x01,		/** Application has no application resource file. */
		ENonStandardResourceFile= 0x02,		/** Application uses a different application resource file from its standard. */
		ENoScreenFurniture		= 0x04,		/** Application uses no screen furniture. */
		ELastReservedEikAppUiFlag = 0x08
		};
private: // new functions
	void CreateResourceIndependentFurnitureL();
	TBool ValidFileExistsL(const TDesC& aFileName);
protected:
	CEikDocument* iDocument;
	CEikAppUi* iContainerAppUi;
	MApaEmbeddedDocObserver* iDoorObserver;
	TBool iEmbeddedAndReadOnly;
	TInt iFlags;
private:
	enum
		{
		EEmbedded = 0x01
		};
private:
	TInt iSpare;
	};

/**
 *
 * Returns the app UI inside which this app UI is embedded.
 *
 * Embedded app UIs are used for example, for editing embedded documents
 * and to stack a help application onto the context of a current
 * application.
 *
 * @returns   " CEikAppUi* "
 *            A pointer to this <code>CEikAppUi</code>s container
 *            app UI. <code>NULL</code> if this app UI is not
 *            embedded
 */
inline CEikAppUi* CEikAppUi::ContainerAppUi() const
	{ return iContainerAppUi; }

#endif
