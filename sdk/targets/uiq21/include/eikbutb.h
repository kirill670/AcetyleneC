// EIKBUTB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBUTB_H__)
#define __EIKBUTB_H__

#include <eikbctrl.h>
#include <uikon.hrh>
#include <lafpublc.h>

class TEikButtonCoordinator;

/**
 * Specifies button behaviour.
 *
 * <code>TButtonBehaviour</code> values may be bitwise-ORed.
 */
enum TButtonBehavior
	{
	EEikButtonStaysClear=EEikButStaysClear,						/** Button is always clear. */
	EEikButtonStaysSet=EEikButStaysSet,							/** Button is always set. */
	EEikButtonLatches=EEikButLatches,							/** Button latches. */

	/** Button reports a control event to its observer on just a pointer down
	rather than on a down followed by an up. */
	EEikButtonReportsOnPointerDown=EEikButReportOnPointerDown
	};

/**
 *
 * This is the base class from which concrete button controls (command
 * buttons, option buttons and checkboxes) are derived.
 *
 * The base class implements knowledge of the buttons logical state, and
 * can respond to user events. It cannot, however, draw itself.Derived
 * classes should provide an appropriate implementation of
 * <code>CCoeControl::Draw()</code>. It is usual to make the on-screen
 * appearance of the button dependent on its current state. Derived
 * classes may also implement <code>StateChanged()</code> to respond
 * appropriately to changes in the draw state.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikButtonBase : public CEikBorderedControl
	{
public:
	IMPORT_C CEikButtonBase();
	IMPORT_C ~CEikButtonBase();
public:
	/**
	 *
	 * Possible logical states for a button.
	 *
	 * <code>TState</code> values represent the logical state of a button.
	 * Derived button classes may draw themselves differently to indicate
	 * different states. See also <code>State()</code> and
	 * <code>SetState()</code>.The state of a non-latching button is, in
	 * general, of no interest to applications. What is of interest is the
	 * fact that it has been pressed.
	 */
	enum TState
		{
		EClear		  	=0,		/** The clear state; often drawn as button-up. */
		ESet			=1,		/** The set state; often drawn as button-down. */
		/** An indeterminate state; often used for an animation stage between the
		two other buttons, and may be used for derived tri-state buttons. */
		EIndeterminate  =2
		};
public: // new functions
	IMPORT_C TState State() const;
	IMPORT_C void SetState(TState aState);
	IMPORT_C virtual void Animate();
	IMPORT_C void SetCoordinator(TEikButtonCoordinator* aButCoord);
	IMPORT_C void SetBehavior(TButtonBehavior aBehavior);
	IMPORT_C void SetIgnoreNextPointerUp();
	IMPORT_C void SetBubbleHelpTextL(const TDesC& aText);
protected:
	/**
	 *
	 * Possible states for the draw stateThe <code>TDrawState</code> values
	 * affecting a button are stored in <code>iButFlags</code>.
	 *
	 * All draw state flag bits must be maskable by <code>0x001f</code>; the
	 * ones which describe a pressed button must be maskable by
	 * <code>0x0010</code>.
	 */
	enum TDrawState
		{
		EDrawClear					=SLafButtonBase::EDrawClear,				/** Button is clear. */
		EDrawSet					=SLafButtonBase::EDrawSet,					/** Button is set. */
		EDrawIndeterminate			=SLafButtonBase::EDrawIndeterminate,		/** Button is between set and clear. */
		EDrawClearPressed			=SLafButtonBase::EDrawClearPressed,			/** Button is clear, and the user is pressing it. */
		EDrawSetPressed				=SLafButtonBase::EDrawSetPressed,			/** Button is set, and the user is pressing it. */
		EDrawIndeterminatePressed	=SLafButtonBase::EDrawIndeterminatePressed	/** Button is between set and clear, and the user is pressing it. */
		};
protected: // new functions
	IMPORT_C void SetReportOnPointerDown();
	IMPORT_C TDrawState DrawState() const;
	IMPORT_C TBool IsPressed() const;
	IMPORT_C void SetAllowTristate();
	IMPORT_C void CopyDrawStateTo(CEikButtonBase* aTargetButton) const;
protected: // new functions
	TBool IsPointerEventDraggedOff();
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // new function
	IMPORT_C virtual void StateChanged();
	IMPORT_C virtual void Reserved_3();
public: // framework
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
private: // internal use only
	TBool ClickCompleted();
private:
	enum { EIgnoreNextPointerUp=0x1000 };
protected:
	TInt iButFlags;
private:
	TEikButtonCoordinator* iButCoord;
	HBufC* iBubbleHelpText;
	};

//
// Button coordinator class
//

/**
 *
 * Button coordinator.
 *
 * An instance of this class is used to coordinate groups of buttons on
 * the screen in which only one may be set at one time. All buttons which
 * should be coordinated in this way share the same button coordinator.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class TEikButtonCoordinator
	{
public:
	IMPORT_C TEikButtonCoordinator();
	IMPORT_C void SetChosenButton(CEikButtonBase* aChosenButton);		
private:
	CEikButtonBase* iChosenButton;
	};		 

#endif
