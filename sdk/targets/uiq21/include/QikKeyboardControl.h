// QikKeyboardControl.h
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//
// defines the keyboard component
//////////////////////////////////////////////////////////////

#ifndef __QIKKEYBOARDCONTROL_H__
#define __QIKKEYBOARDCONTROL_H__

// global includes
#include <coecntrl.h>
#include <badesca.h>	// typedef CDesCArray

const TInt KMaxNumKeytops = 16;

// forward declarations
class CQikKeytopControl;
class CQvkKeytopObserver;

//
// MQikKeyboardObserver
//

/**
 * Mixin class. The Observer of the KeyboardControl should inherit from this class, and set itself as an observer into
 * CQikKeyboardControl by calling its SetObserver() function.
 *
 * @short The Observer of the KeyboardControl should inherit form this class
 * @see CQikKeyboardControl
 * @since Quartz 6.0
 */
class MQikKeyboardObserver
	{
public:
	/**
	 * This function will be called in the Keyboard Observer, as soon as a bottom on one of the Keytops is pressed.
	 * It has to be implemented by the Keyboard Observer.
	 *
	 * @param aKeyEvent The Keyevent, that gets created by the keyboard
	 */
	virtual void HandleKeyboardEventL(const TKeyEvent& aKeyEvent) = 0;

	/**
	 * As soon as the Keytop changes this function will get called, so that the Keyboard Observer can handle the change
	 * in size correctly. This function has to be implemented by the Keyboard Observer.
	 */
	virtual void HandleKeyboardSizeChanged() = 0;
	};

//
// MQikChangeKeyboardObserver
//

/**
 * Mixin class. The class, that inherits from this class can observe a KeyboarChanger. The Keyboard changer allows to
 * change between different Keytops. It is for example implemented in CQikKeyboardControl. The Keytop can be such a
 * Keyboard changer, but it can be any other control as well. Normally the control that holds several keytops should
 * inherit from this class.
 *
 * @short This mixin allows to observe a keyboard changer Control and by that change between different keytops.
 * @see CQikKeyboardControl
 * @internal
 * @since Quartz 6.0
 */
class MQikChangeKeytopObserver
	{
public:
	/**
	 * This function will be called to request a change from one Keytop to another
	 *
	 * @param aKeytopResourceId		The Keytop that should be changed to
	 */
	virtual void HandleKeytopChangeL(TInt aKeytopResourceId) = 0;
	};

	
//
// CQikKeyboardControl
//

/**
 *
 * @short Keyboard Control with different keyboards (called keytops)
 * @see CQikKeytopControl
 * @since Quartz 6.0
 */
class CQikKeyboardControl : public CCoeControl, public MQikChangeKeytopObserver
	{
public:	
	enum TKeytopType
		{
		EDefault,
		EAlphabetic,
		ENumerical
		};
public:
	IMPORT_C static CQikKeyboardControl* NewL(const CCoeControl& aContainer, TKeytopType aVisibleAtStart = EDefault, TBool aPreAllocMemory = EFalse);
	IMPORT_C void SetObserver(MQikKeyboardObserver* aObserver);
	IMPORT_C void ResetCapsAndShift();
	IMPORT_C TKeytopType CurrentKeytopType() const;
	IMPORT_C TBool SetCurrentKeytopTypeL(TKeytopType aType);
	IMPORT_C CDesCArray* SupportedLayoutsLC() const;
	IMPORT_C void SetLayoutL(TInt aIndex);

	~CQikKeyboardControl();
public: // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	TSize MinimumSize();
	void SizeChanged();
	void HandleResourceChange(TInt aType);
	void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
public: // from MQikChangeKeytopObserver
	void HandleKeytopChangeL(TInt aKeytopResourceId);
protected: //from CCoeControl
	void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	void Reserved_2();
private:
	CQikKeyboardControl(TBool aLowMemory);
	void ConstructL(TKeytopType aVisibleAtStart);
	void ConstructFromResourceL(TInt aKeybordLayoutResourceId, TKeytopType aVisibleAtStart);
	void Draw(const TRect& aRect) const;
private:
	HBufC* iLayoutName;
	CQvkKeytopObserver* iKeytopObserver;
	TFixedArray<TInt32, KMaxNumKeytops> iKeytopResources;
	TFixedArray<CQikKeytopControl*, KMaxNumKeytops> iKeytopArray;
	TInt iKeytopModificationsResourceId;
	TInt iKeytopLinksResourceId;
	CQikKeytopControl* iCurrentKeytop;
	TBool iPreAllocMemory;
	TInt iKeyboardResourceId;
	};

#endif	// __QIKKEYBOARDCONTROL_H__
