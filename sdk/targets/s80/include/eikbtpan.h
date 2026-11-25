/*
* ==============================================================================
*  Name        : eikbtpan.h
*  Part of     : CKON
*  Interface   : Button Group API
*  Description : Button panel capable of displaying rows of button groups.
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


#ifndef EIKBTPAN_H
#define EIKBTPAN_H

// INCLUDES
#include <eikbtgrp.h>
#include <coecntrl.h>
#include <coecobs.h>
#include <eiklbbut.h>
#include <eikctgrp.h>

// FORWARD DECLARATIONS
class MEikCommandObserver;

/**
 * @internal
 * Internal to Symbian
 *
 * @since Series90 1.0
 */
class CEikButtonPanel : public CCoeControl, public MCoeControlObserver, public MEikButtonGroup
	{
	public: // new functions

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikButtonPanel();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikButtonPanel();

		/**
		* Second phase constructor
		*/
		IMPORT_C void ConstructL();

		/**
		* Adds a button (of type CEikLabeledButton) to the button panel.
		* @param aButton Pointer to the button to add.
		* @param aId The command ID of the button to add.
		*/
		IMPORT_C void AddButtonL(CEikLabeledButton* aButton,TInt aId);

		/**
		* Adds a button (of type CEikLabeledButton) to the button panel.
		* @param aButton Pointer to the button to add.
		* @param aId The command ID of the button to add.
		* @param aRow The row to add the button to.
		*/
		IMPORT_C void AddButtonL(CEikLabeledButton* aButton,TInt aId, TInt aRow);

		/**
		* Sets the rows of the button panel to be laid horizontally.
		* @remarks This method also takes care of rounding the ends of
		* the first and last buttons in a row. 
		* After adding a button to an existing group, it is necessary
		* to call ResetMinimumSize and then SetHorizontal, otherwise
		* the added button will not be treated as the last button for purposes
		* of appearance.
		*/
		IMPORT_C void SetHorizontal();

		/**
		* Gets the command ID of a specified button.
		* @param aControl The button to get the command for.
		* @return The command ID of the button.
		*/
		IMPORT_C TInt ButtonId(CCoeControl* aControl) const;

		/**
		* Gets a button from its ID. Returns NULL if no button is found.
		* @param aButtonId The command ID to get a button for.
		* @return Pointer to the button.
		* @remarks CEikLabeledButton is a wrapper for a CEikCommandButtonBase.
		* The button returned by this method is the 'wrapped' button, whereas
		* LabeledButtonById() returns the 'wrapping' button.
		* @see LabeledButtonById
		*/
		IMPORT_C CEikCommandButtonBase* ButtonById(TInt aButtonId) const;

		/**
		* Gets a labelde button from its ID. Returns NULL if no button is found.
		* @param aButtonId The command ID to get a button for.
		* @return Pointer to the button.
		* @see ButtonById
		*/
		IMPORT_C CEikLabeledButton* LabeledButtonById(TInt aButtonId) const;

		/**
		* Sets a button's visibility.
		* @param aButtonId The command ID of the button.
		* @param aVisible ETrue if the button should be made visible. EFalse 
		*        otherwise.
		*/
		IMPORT_C void MakeButtonVisible(TInt aButtonId,TBool aVisible);

		/**
		* Gets the button which corresponds to a particular command key.
		* @param aChar The key to find.
		* @param aButtonId On return, contains the command ID of the button.
		* @return Pointer to the button. Returns NULL if no button is found.
		*/
		IMPORT_C CEikCommandButtonBase* ButtonForKey(TInt aChar,TInt& aButtonId) const;

		/**
		* Resets the minimum size of the button panel to 0.
		* @remarks Calling this method after any change ensures that the button 
		* is resized
		*/
		IMPORT_C void ResetMinimumSize();

		/**
		* Sets the minimum width of the buttons on the panel.
		* @param aWidth The width.
		*/
		IMPORT_C void SetMinButtonWidth(TInt aWidth);

		/**
		* Sets the command observer to which commands are passed when a button 
		* is pressed
		* @param aCommandObserver The command observer.
		*/
		IMPORT_C void SetCommandObserver(MEikCommandObserver* aCommandObserver);

		void UpdateHotKeyL(TInt aCommandId,CEikLabeledButton::TFlags aFlags,TInt aKeyCode);
	public:	// from CCoeControl

		/**
		* This allows a button panel to be generated from 
		* a resource of type EEikBgButtonPanel. 
		* @see <code>CCoeControl</code>.
		*/
		IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* @see <code>CCoeControl</code>.
		*/
		IMPORT_C TSize MinimumSize();

		/**
		* @see <code>CCoeControl</code>.
		*/
		IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* @see <code>CCoeControl</code>.
		*/
		IMPORT_C void HandleResourceChange(TInt aType);			

		/**
		* @see <code>CCoeControl</code>.
		*/
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	protected: // from CCoeControl

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
		IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	public: // from MCoeControlObserver

		/**
		* From <code>MCoeControlObserver</code>.
		* Used internally when one of the button's state is changed. This passes the command ID
		* on to the command observer.
		* @param aControl The command button which has received an event.
		* @param aEventType The type of event.
		*/
		IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	private: // from MEikButtonGroup
		void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
		void SetCommandL(TInt aPosition,TInt aResourceId);
		void SetCommandSetL(TInt aResourceId);
		void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
		void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
		void AddCommandToStackL(TInt aPosition,TInt aResourceId);
		void AddCommandSetToStackL(TInt aResourceId);
		void SetDefaultCommand(TInt aCommandId);
		TSize CalcMinimumSizeL(TInt aResourceId);
		void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
		TInt CommandPos(TInt aCommandId) const;
		void DimCommand(TInt aCommandId,TBool aDimmed);
		TBool IsCommandDimmed(TInt aCommandId) const;
		void MakeCommandVisible(TInt aCommandId,TBool aVisible);
		TBool IsCommandVisible(TInt aCommandId) const;
		CCoeControl* AsControl();
		const CCoeControl* AsControl() const;
		void SetBoundingRect(const TRect& aBoundingRect);
		void ReduceRect(TRect& aBoundingRect) const;
		CCoeControl* GroupControlById(TInt aCommandId) const;
		CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
		TInt CommandId(TInt aCommandPos) const;
		TInt ButtonCount() const;
		TUint ButtonGroupFlags() const;
	private: // from CCoeControl
		IMPORT_C void ActivateL();
		IMPORT_C TInt CountComponentControls() const;
		IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
		void Draw(const TRect& aRect) const;
		IMPORT_C void SizeChanged();
		IMPORT_C void Reserved_2();
	private: // new functions
		TInt RelativePosition(TInt aCommandPos, TInt& aGroupIndex) const;
		TBool ButtonsConsumedKeyL(const TKeyEvent& aKeyEvent,TInt aCode);
		void AppendNewLineL();
		CEikLabeledButton* LabeledButtonByPosition(TInt aPosition, TInt& aGroupIndex) const;
		CEikLabeledButton* LabeledButtonByPosition(TInt aPosition) const;
		void AdjustMarginsToFit(TInt8& aLeftBorder, TInt8& aRightBorder, TInt& aGapBetweenButtons);
		void SetButtonWidths();
	private:
		CArrayPtrFlat<CEikControlGroup>* iControlGroups;
		TSize iMinSize;
		TInt iButWidth;
		TInt iMinButWidth;
		TInt iCount; // for efficiency
		MEikCommandObserver* iCommandObserver;
	};


#endif	// EIKBTPAN_H

// End of File
