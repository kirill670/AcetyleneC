/*
* ==============================================================================
*  Name        : eikmisdg.h
*  Part of     : CKON
*  Interface   : Character Map Dialog API
*  Description : Miscellaneous dialogs.
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



#ifndef EIKMISDG_H
#define EIKMISDG_H


// INCLUDES
#include <eikdialg.h>
#include <eikchmap.h>

//
// DATA TYPES


// FORWARD DECLARATIONS


// CLASS DECLARATIONS

/**
*  Number editor with minimum and maximum values
*
*  Link against EIKCDLG.LIB
*  @since Series90 1.0
*/
class CEikNumDialog : public CEikDialog
    {
	public:
	// Methods from base classes

        /**
        *  Static function to launch the dialog
        * @param aNumber The number display in the editor. Returns with the value provided by the user
		* @param aMin The minimum value
		* @param aMax The maximum value
		* @param aTitleId Resource ID of the dialog's title text string
		* @param aPromptId Resource ID of the text string displayed with the number
        */

	IMPORT_C static TBool RunDlgLD(	TInt&	aNumber, 
									TInt	aMin, 
									TInt	aMax, 
									TInt	aTitleId, 
									TInt	aPromptId);
    private: //Methods

		CEikNumDialog(TInt& aNumber, TInt aMin, TInt aMax, TInt aTitleId, TInt aPromptId);
		void PreLayoutDynInitL();
		TBool OkToExitL(TInt aButtonId);
	
	private:     // Data
		TInt* iNumber;
		TInt iTitleId;
		TInt iPromptId;
		TInt iMin;
		TInt iMax;

    };

/**
*  The cursor position in the char map.
*
*  Link against EIKCDLG.LIB
*  @since Series90 1.0
*/
class TChMapCursorPosition
    {

	public:

	// New methods
        
		/**
		* Internalize the focused control ID and selected character
		* @param aStream The stream to write to
		*/
		void InternalizeL(RReadStream& aStream);

		/**
		* Externalize the focused control ID and selected character
		* @param aStream The stream to read from
		*/
		void ExternalizeL(RWriteStream& aStream) const;

	public:     // Data
		/** The id of the control */
		TInt iFocusedControlId;
		/** The selected character in the Char map.		*/
		TInt iSelectedCharacter;

    };

/**
*  Dialog to insert special character into a control.
*  
*  Link against eikcdlg.lib
*  @since Series90 1.0
*/
class CEikCharMapDialog : public CEikDialog
    {

	public:

	// New methods
        
		/**
		* Static function to execute the dialog.
		* @param aControl The control into which the selected character is inserted
		* @return ETrue if OK pressed, EFalse if dialog cancelled 
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TBool
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C static TBool RunDlgLD(CCoeControl* aControl);

		//from CCoeControl
		/**
		* From CCoeControl Associated the control with a particular Help file and topic in a context sensitive application. Must set the public data members of TCoeHelpContext to the required Help file UID and context descriptor 
		* @param aContext The help context of the control
		*/
		void GetHelpContext(TCoeHelpContext& aContext) const;

        
    private: //Methods

		CEikCharMapDialog(CCoeControl* aControl);
		void HandleControlStateChangeL(TInt aResourceId);// from MCoeControlObserver
		void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
		TBool OkToExitL(TInt);
		void PreLayoutDynInitL();
		void PostLayoutDynInitL();
		void SetInitialCurrentLine();
		void LineChangedL(TInt aControlId);
		void PageChangedL(TInt aPageId);
		void DimOkButton(TBool aDim);
		void SetInitialCurrentLineL();

	private:     // Data
		CCoeControl* iControl;
		TInt iLastChar;
    };


#endif      // EIKMISDG_H   
            
// End of File
