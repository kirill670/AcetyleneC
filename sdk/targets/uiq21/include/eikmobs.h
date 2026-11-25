// EIKMOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMOBS_H__)
#define __EIKMOBS_H__

#include <eikcmobs.h>
#include <w32std.h>
#include <coedef.h>

class CCoeControl;
class CEikMenuPane;
class CEikMenuBar;
class CEikHotKeyTable;
class TPoint;

/**
 *
 * Menu observer interface.
 *
 * Menu observers cooperate with menu bars and menu panes, initialising
 * them before display and responding to menu events appropriately.
 * <code>CEikAppUi</code> implements <code>MEikMenuObserver</code>, so
 * these functions may be implemented on an applications App UI.Writing
 * derived classesThe only pure virtual function in this interface is
 * <code>SetEmphasis()</code>. Other functions may be overridden to
 * provide additional behaviour.
 *
 * @since 6.0
 * @lib "eikcore.lib"
 */
class MEikMenuObserver : public MEikCommandObserver
	{
public:
	/**
	 * Menu types.
	 */
	enum TMenuType
		{
		EMenuPane,		/** Menu pane. */
		EMenuBar		/** Menu bar. */
		};
public:
	IMPORT_C virtual void HandleAttemptDimmedSelectionL(TInt aCommandId);
	IMPORT_C virtual TBool CheckHotKeyNotDimmedL(TInt aCommandId);
	IMPORT_C virtual void RestoreMenuL(CCoeControl* aMenuControl,TInt aResourceId,TMenuType aType);
	IMPORT_C virtual void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);
	IMPORT_C virtual void DynInitMenuBarL(TInt aResourceId,CEikMenuBar* aMenuBar);
	IMPORT_C virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
	IMPORT_C virtual void OfferKeyToAppL(const TKeyEvent& aKeyEvent,TEventCode aType);
	/**
	 * Called by the Uikon framework to handle the emphasising or
	 * de-emphasising of a menu window.
	 *
	 * <code>CEikMenuBar</code> objects call this on their observer to
	 * emphasise themselves when they are displayed, and de-emphasise
	 * themselves when they stop displaying.
	 *
	 * @param     "CCoeControl* aMenuControl"
	 *            The menu control.
	 * @param     " TBool aEmphasis"
	 *            <code>ETrue</code> to emphasize the menu,
	 *            <code>EFalse</code> otherwise.
	 */
	virtual void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis)=0;
private:
	IMPORT_C virtual void Reserved_1_MenuObserver();
	};

/**
 *
 * Provides additional functionality to an auto menu title, in the form
 * of an <code>OfferHotKeyL()</code> method, which is not required in the
 * normal <code>MEikMenuObserver</code>.
 *
 * Auto menu titles are used to ensure that some menu panes appear in
 * every menu constructed for an application.
 *
 * @since 6.0
 * @lib "eikcore.lib"
 */
class MEikAutoMenuObserver : public MEikMenuObserver
	{
public:
	/**
	 * Offers the specified hot key to the auto menu title.
	 *
	 * Implement this function if you expect to handle any events from an
	 * auto menu.
	 *
	 * @param     "const TKeyEvent& aKeyEvent"
	 *            The key event.
	 * @param     "TEventCode aType"
	 *            The type of key event.
	 * @returns   " TKeyResponse "
	 *            The auto menu title's response.
	 */
	virtual TKeyResponse OfferHotKeyL(const TKeyEvent& aKeyEvent,TEventCode aType)=0;
public: // from MEikMenuObserver
	IMPORT_C void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
private:
	IMPORT_C virtual void Reserved_1_MenuObserver();
	};


#endif
