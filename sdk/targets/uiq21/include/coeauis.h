// COEAUIS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEAUIS_H__)
#define __COEAUIS_H__

#if !defined(__COEAUIB_H__)
#include <coeauib.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

/**
 *
 * Simple application UI.
 *
 * Applications which use this class designate one control to be the root
 * control which receives all key events for the application. The root
 * control must handle key events itself or channel them to other
 * controls within the application, by calling
 * <code>CCoeControl::OfferKeyEventL()</code>.In practise, most realistic
 * applications use the standard app UI <code>CCoeAppUi</code>. The main
 * difference is that this class provides a control stack rather than a
 * root control.
 *
 * @deprecated Deprecated in 6.1
 * @since 5.0
 * @lib "cone.lib"
 */
class CCoeAppUiSimple : public CCoeAppUiBase
	{
public:
	IMPORT_C CCoeAppUiSimple();
	IMPORT_C ~CCoeAppUiSimple();
public: // new functions
	IMPORT_C void SetRootControl(CCoeControl* aControl);
protected: // from CCoeAppUiBase
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
private: // new functions
	IMPORT_C virtual void HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void HandleForegroundEventL(TBool aForeground);
private:
	CCoeControl* iRootControl;
	};

#endif
