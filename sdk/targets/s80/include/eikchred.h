/*
* ==============================================================================
*  Name        : eikchred.h
*  Part of     : CKON
*  Interface   : Character Editor API
*  Description : Character editor.
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


#ifndef EIKCHRED_H
#define EIKCHRED_H

// INCLUDES
#include <coecntrl.h>
#include <eikbctrl.h>

/**
 * class CEikCharEditor
 *
 * This class defines a character editor which takes only
 * one character and it's always highlighted. You can
 * paste to the editor but no other clipboarding functions
 * are available.
 * @lib eikctl.lib
 * @since Series90 1.0
*/
class CEikCharEditor : public CEikBorderedControl
	{
	public: // class specific

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikCharEditor();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikCharEditor();

		/**
		* Sets the editor's character value.
		* @since Series90 1.0
		* @param aChar The character to which to set the editor's value.
		*/
		IMPORT_C void SetChar(TChar aChar);

		/**
		* Gets the editor's character value.
		* @since Series90 1.0
		* @return The character editor's value.
		*/
		IMPORT_C TChar GetChar() const;
	public: // from CCoeControl

		/**
		* Handles key events.
		* @since Series90 1.0
		* @param aKeyEvent A key event.
		* @param aType A event type.
		* @return A key response.
		*/
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

		/**
		* Gets the eitor's minimum size in pixels.
		* @since Series90 1.0
		* @return The size of charactor editor control.
		*/
		IMPORT_C TSize MinimumSize();

		/**
		* Gets the list of logical colours used to draw the control.
		* The list includes an explanation of how each colour is used.
		* @since Series90 1.0
		* @param aColorUseList The color list.
		*/
		IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* Handles a change to the editor's resources. The types of
		* resources handled are those which are shared across the environment, e.g. colours or fonts.
		* @since Series90 1.0
		* @param aType A message UID value.
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

		/**
		* Returns the input capabilities of the control.
		* @since Series90 1.0
		* @return The control's input capabilities.
		* <BR><B>Type of return value:</B> TCoeInputCapabilities
		*/
		IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	protected: // from CCoeControl

		/**
		* See CCoeControl
		*/
		IMPORT_C void Draw(const TRect& aRect) const;

		/**
		* See CCoeControl
		*/
		IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	private: // from CCoeControl
		IMPORT_C void Reserved_1();
		IMPORT_C void Reserved_2();
	private:
	enum TChredHotKeys // order of hotkeys defined in resource file.  Not all applicable to plain text editors
		{
		EHotKeyPaste,
		EHotKeyInsertChar=5
		};
		TChar iChar;
	};




#endif	// EIKCHRED_H

// End of File
