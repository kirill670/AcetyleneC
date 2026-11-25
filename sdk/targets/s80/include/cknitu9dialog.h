/*
* ==============================================================================
*  Name        : cknitu9dialog.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : MCknItu9DialogObserver class is an interface class.
*	 			 CCknItu9Dialog is used for entering PINs and numeric passwords.
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


#ifndef CKNITU9DIALOG_H
#define CKNITU9DIALOG_H

// INCLUDES
#include "eikdialg.h"

// FORWARD DECLARATIONS
class CCknItu9Control;

// CONSTANTS
const TInt KOptionalButtonCommandId	= 0x1001;


/**
*  MCknItu9DialogObserver class is an interface used by
*  CCknItu9Dialog class to handle optional button events.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class MCknItu9DialogObserver
	{
public:
		/**
		* Handles optional button events.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void HandleOptionalButtonEvent() = 0;
	};

/**
*  CCknItu9Dialog is used for entering PINs and numeric passwords.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class CCknItu9Dialog : public CEikDialog
	{
	public:

		/**
		* Runs Itu9 dialog.
		* @param aEditorText Editor text.
		* @param aButtonText Text on the buttons. Can be NULL.
		* @param aIsSecret Whether to hide the input with a secret character.
		* @param aDigitsOnly Whether the input is digits only.
		* @param aQuestionMarkLegal Whether '?' input is allowed.
		* @param aObserver Itu9 Dialog observer. Can be NULL.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool RunDlgLD(TDesC& aEditorText, const TDesC* aButtonText = NULL, bool aIsSecret = false, bool aDigitsOnly = false, bool aQuestionMarkLegal = true, MCknItu9DialogObserver* aObserver = NULL);

		/**
		* Destructor.
		*/
		~CCknItu9Dialog();

	public: // from CEikDialog
		void PreLayoutDynInitL();
		TBool OkToExitL(TInt aButtonId);

	protected:

		/**
		* C++ constructor.
		* @param aEditorText Editor text.
		* @param aButtonText Text on the buttons. Can be NULL.
		* @param aIsSecret Whether to hide the input with a secret character.
		* @param aDigitsOnly Whether the input is digits only.
		* @param aQuestionMarkLegal Whether '?' input is allowed.
		* @param aObserver Itu9 Dialog observer. Can be NULL.
		*/
		CCknItu9Dialog(TDesC& aEditorText, const TDesC* aButtonText = NULL, bool aIsSecret = false, bool aDigitsOnly = false, bool aQuestionMarkLegal = true, MCknItu9DialogObserver* aObserver = NULL);

	private:
		CCknItu9Control* iItu9Control;
		TDesC& iEditorText;
		const TDesC* iButtonText;
		bool iIsSecret;
		bool iDigitsOnly;
		bool iQuestionMarkLegal;
		MCknItu9DialogObserver* iObserver;
	};


#endif	// CKNITU9DIALOG_H

// End of File
