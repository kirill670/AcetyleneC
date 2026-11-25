/*
* ==============================================================================
*  Name        : cknitu9controls.h
*  Part of     : CKON
*  Interface   : ITU9 Editor API
*  Description : Keypad control
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


#ifndef CKNITU9CONTROLS_H
#define CKNITU9CONTROLS_H

// INCLUDES
#include <coecobs.h>
#include <eikchlst.h>
#include "cknbctrl.h"

// DATA TYPES

enum TCknItu9EditorMode
	{
	/** Hides input with a secret character */
	ESecretCharacters,
	/** Shows input */
	ENoSecretCharacters,
	/** Allows input of digits only */
	EDigitsOnly,
	/** Allows input of digits and special characters */
	ECharactersAll,
	/** Allows input of digits and special characters apart from '?' */
	ECharactersNoQuestionMark
	};

// FORWARD DECLARATIONS
class CEikGlobalTextEditor;
class CCknDialogButton;
class CCknSkinBase;

/**
*  The display for an Itu9 editor class. When 
*
*  @lib cknctl.lib
*  @since Series90 1.0
*  @internal
*/
class CCknItu9Editor : public CCknBorderedControl
	{
	public:
		CCknItu9Editor(CCoeControl* aParent, bool aIsSecret = false, bool aDigitsOnly = false, bool aQuestionMarkLegal = false);
		~CCknItu9Editor();
		void ConstructL(CCoeControl* aWindowContainer);
		void SetDefaultTextL(const TDesC* aText);
		void SetMaxLength(TInt aMaxLength);
		void SetModeL(TCknItu9EditorMode aMode);
		TPtrC Text();
		void Reset();
		TBool MaximumNumberOfCharactersEntered();

	public: // from CCoeControl

		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);
		CCoeControl* ComponentControl(TInt aIndex) const;
		TInt CountComponentControls() const;
		void Draw(const TRect& aRect) const;
		void SizeChanged();
		TSize MinimumSize();

	private:
		void DrawDeleteButton() const;
		void DrawDeleteButtonNow() const;
		bool IsSpecialCharacterL(TChar aCharacter);
		bool IsOptionalSpecialCharacterL(TChar aCharacter);
		bool IsValidKeyEventL(TChar aCharacter);
		void DisplayDefaultTextL();
		void ConvertToSecretL();
		void RemoveCharactersL(TBool aExtraCharactersOnly);

	private:
		CCoeControl* iParent;
		bool iIsSecret;
		bool iDigitsOnly;
		bool iQuestionMarkLegal;
		HBufC* iSpecialCharacters;
		HBufC* iOptionalCharacters;
		CEikGlobalTextEditor* iEditor;
		HBufC* iText;
		const TDesC* iDefaultText;
		TInt iMaxCharLength;
		TBool iDeletePressed;
		TUint iInternalFlags;
		TUint iRepeatDelay;
	};

/**
*  An observer for a button press event.
*  Classes that wish to register to recieve a button press event should
*  implement this interface.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class MCknItu9ButtonGroupObserver
	{
	public:

		/**
		* Called when a button pressed event is sent.
		* @param aPressedButtonCharacter The character of the button pressed.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void HandleButtonPressedEventL(TChar aPressedButtonCharacter) = 0;

		/**
		* Called to determine if there is space to enter more characters
		* <BR><B>Type of return value:</B> TBool
		*/
		virtual TBool MaximumNumberOfCharactersEntered(){return EFalse;}
	};

/**
*  Symbian internal use.
*  This class implements the button group for the Itu9 control.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknItu9ButtonGroup : public CEikBorderedControl, public MCoeControlObserver
	{
	public:

		CCknItu9ButtonGroup(CCoeControl* aParent, MCknItu9ButtonGroupObserver* aObserver, bool aDigitsOnly = false, bool aQuestionMarkLegal = true, bool aSecret = false);
		~CCknItu9ButtonGroup();
		void ConstructL();
		void SetModeL(TCknItu9EditorMode aMode);
		void DestroyPopout();

	public: // from CCoeControl

		CCoeControl* ComponentControl(TInt aIndex) const;
		TInt CountComponentControls() const;
		void SizeChanged();
		TSize MinimumSize();
		void HandleResourceChange(TInt aType);

	public: // from MCoeControlObserver

		void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

	private:
		void CreateAndSetBitmapL(CCknDialogButton& aButton, const TDesC& aButtonText);
		static TInt ButtonTimerCallback(TAny* aSelf);
		void HandleButtonTimerEventL();
		const CFont* Font() const;
		void CreatePopoutL();
		void CreateListBoxL();
		void SetListBoxExtentL();
		void ActivateListBoxL();
		void CreateChoiceListPopupArrayL();
		void GetPointersToButtons();
		TInt CalculateTextWidth() const;
		void SetButtonTextL();
		void SetUpButtonsForCurrentModeL(TBool aRedraw=EFalse);

	private:
		enum TInternalFlags
			{
			ESpecialKeySingleClick = 0x01
			};

	private:
		CCoeControl* iParent;
		CCknDialogButton* iButton1;
		CCknDialogButton* iButton2;
		CCknDialogButton* iButton3;
		CCknDialogButton* iButton4;
		CCknDialogButton* iButton5;
		CCknDialogButton* iButton6;
		CCknDialogButton* iButton7;
		CCknDialogButton* iButton8;
		CCknDialogButton* iButton9;
		CCknDialogButton* iButton10;
		CCknDialogButton* iButton11;
		CCknDialogButton* iButton12;
		bool iDigitsOnly;
		bool iQuestionMarkLegal;
		bool iSecret;
		CDesC16Array* iChoiceListArray;
		RPointerArray<CCknDialogButton> iButtonArray;
		MCknItu9ButtonGroupObserver* iObserver;
		CEikChoiceListPopoutListBox* iPopoutListBox;
		CCknSkinBase& iSkin;
		TUint iInternalFlags;
		CPeriodic* iButtonTimer;
		TBool iMbmDuplicated;
	};

/**
*  A control that displays a grid of buttons in Itu9 format, i.e. a telephone keypad.
*  The control may be set to show asterisks instead of characters if the control is to
*  be used to input passwords. Also, it may be set to only accept numeric input.
*  The Dialog Buttons show numbers from 1 to 0, and '#' on the bottom right corner.
*  The bottom-left button opens a pop-out of other available characters, '*' '+' 'p' 'w' and '?'
*  The control may be set to either accept or disallow '?' as valid input.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknItu9Control : public CCknBorderedControl, public MCknItu9ButtonGroupObserver
	{
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CCknItu9Control* NewL();

		/**
		* Two-phased constructor.
		* @param aParent The parent control
		* @param aIsSecret If this is true, the control displays asterisks instead of the input characters.
		* @param aDigitsOnly If true the control only excepts numerical input.
		* @param aQuestionMarkLegal If true, a question mark '?' is leagal input.
		* @return A newly constructed CCknItu9Control
		* <BR><B>Type of return value:</B> CCknItu9Control
		* <BR><B>Range of return value:</B> The returned object will be newly allocated, or the method will leave.
		* <BR><B>Contents of return value:</B> A blank CCknItu9Control.
		*/
		IMPORT_C static CCknItu9Control* NewL(CCoeControl* aParent,
												bool aIsSecret = false,
												bool aDigitsOnly = false,
												bool aQuestionMarkLegal = true);

		/**
		* Destructor.
		*/
		IMPORT_C ~CCknItu9Control();

		/**
		* Set the default text to show in the control.
		* @param aText The default text to show
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetDefaultTextL(const TDesC* aText);

		/**
		* Sets the controls mode. The mode may be one of those specified in the TCknItu9EditorMode enum.
		* @param aMode One of the modes specified in TCknItu9EditorMode.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetModeL(TCknItu9EditorMode aMode);

		/**
		* Sets the maximum length of the input in characters.
		* @param aMaxLength The maximum input length in characters.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMaxLength(TInt aMaxLength);

		/**
		* Get the text displayed in the control.
		* @return The current text
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC Text();

		/**
		* Reset the control. This will display the default text.
		* 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void Reset();

		/**
		* Close the popout of other available characters.
		* 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void DestroyPopout();

	public: // from CCoeControl

		/**
		* See CCoeControl.
		* This allows the control to be constructed from resources with the ID ECknCtItu9Control
		* and the struct ITU9CONTROL.
		* 
		* @param aReader ?description
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
		CCoeControl* ComponentControl(TInt aIndex) const;
		TInt CountComponentControls() const;
		void SizeChanged();
		TSize MinimumSize();
		TBool MaximumNumberOfCharactersEntered();

	protected:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CCknItu9Control();

		/**
		* The symbian 2nd phase constructor.
		* @param aIsSecret If ETrue, the control displays asterisks instead of characters.
		* @param aDigitsOnly If ETrue, only digits are accepted as input.
		* @param aQuestionMarkLegal If ETrue, question marks are valid input.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(bool aIsSecret, bool aDigitsOnly, bool aQuestionMarkLegal);

		/**
		* The symbian 2nd phase constructor.
		* @param aParent the parent control.
		* @param aIsSecret If ETrue, the control displays asterisks instead of characters.
		* @param aDigitsOnly If ETrue, only digits are accepted as input.
		* @param aQuestionMarkLegal If ETrue, question marks are valid input.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(CCoeControl* aParent, bool aIsSecret, bool aDigitsOnly,
								bool aQuestionMarkLegal);

	public: // from MCknItu9ButtonGroupObserver

		/**
		* See MCknItu9ButtonGroupObserver.
		* 
		* @param aPressedButtonCharacter The character of the button pressed.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void HandleButtonPressedEventL(TChar aPressedButtonCharacter);

	private:
		CCknItu9Editor* iEditor;
		CCknItu9ButtonGroup* iKeyPad;
		TAny* iReserved;
	};


#endif	// CKNITU9CONTROLS_H

// End of File
