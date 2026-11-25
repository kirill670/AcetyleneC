/*
* ==============================================================================
*  Name        : eikcfdlg.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Screen capture dialog.
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

#ifndef EIKCFDLG_H
#define EIKCFDLG_H


// INCLUDES
#include <eikdialg.h>



// CLASS DECLARATIONS

/**
* @deprecated
* Link against eikfile.lib
*/
class CEikFileOpenDialog : public CEikDialog
	{

	public:

	// New methods
        
		IMPORT_C CEikFileOpenDialog(TDes* aFileName, TInt aTitleId=0);
		IMPORT_C void SetShowSystem(TBool aShowSystem);
		IMPORT_C void SetRequiredUid(const TUidType& aUidType);
		IMPORT_C void SetRequiredExtension(const TDesC* aExtension);
		IMPORT_C void RestrictToNativeDocumentFiles();
		IMPORT_C TInt ExecuteLD(TInt aResourceId);

	// Methods from base classes

    protected:  // Methods

	// Methods from base classes
        
		IMPORT_C void PreLayoutDynInitL();
		IMPORT_C TBool OkToExitL(TInt aButtonId);

	// New Methods
        
		IMPORT_C void HandleBrowseButtonL();

    private: //Methods

	// New Methods
        
	// Methods from base classes
        
	private:     // Data

		TDes* iFileName;
		TUidType iUidType;
		TDesC* iExtension;
		TBool iShowSystem;
		TInt iTitleId;
		RFs iFs;

	};

/**
* @deprecated
* Link against eikfile.lib
*/
class CEikFileSaveAsDialog : public CEikDialog
	{

	public:

	// New methods
        
		IMPORT_C CEikFileSaveAsDialog(TDes* aFileName,TBool* aUseNewFile=NULL,TInt aTitleId=0,TBool aAppendExtension=EFalse);
		IMPORT_C CEikFileSaveAsDialog(TDes* aFileName,const TDesC* aTitle,TBool* aUseNewFile=NULL,TBool aAppendExtension=EFalse);
		IMPORT_C static TBool RunDlgLD(	TDes* aFileName,
										TBool* aUseNewFile=NULL,
										TInt aTitleId=0,
										TBool aAppendExtension=EFalse);
		IMPORT_C TInt ExecuteLD(TInt aResourceId);

	protected:  // Methods

	// Methods from base classes

		IMPORT_C TBool OkToExitL(TInt aButtonId);
		IMPORT_C void PreLayoutDynInitL();

	protected:  // Methods

	// New Methods

		IMPORT_C void HandleBrowseButtonL();

	private: //Methods

	// New Methods

	// Methods from base classes

	private:     // Data

		TDes* iFileName;
		TBool* iUseNewFile;
		TInt iTitleId;
		const TDesC* iTitle;
		TBool iAppendExtension;
		RFs iFs;

	};

/**
* Dialog for saving screen capture.
*
* This opens a save as dialog and saves the screen capture to the file selected by the user.
*
* Link against eikfile.lib
* @since Series90 1.0
*/
class CEikScreenCaptureDialog : public CEikFileSaveAsDialog
	{

public:

	// New methods

		/**
		* Runs the screen capture dialog.
		* @param aFileName The initial path to save to, to be modified by the User. Updated with the User's choice if they OK the dialog
		* @param aSaveAsMonochromeImage Not used.
		* @param aTitleId Title resource for dialog. If 0, a default is used
		* @return ETrue if the User OKs the dialog. EFalse if they cancel it
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool RunDlgLD(TDes* aFileName, TBool& aSaveAsMonochromeImage, TInt aTitleId=0);

	private: //Methods

		CEikScreenCaptureDialog(TDes* aFileName, 
								TBool& aSaveAsMonochromeImage, 
								TInt aTitleId=0);
		TBool OkToExitL(TInt aButtonId);

	private:     // Data

		TBool& iSaveAsMonochrome;

	};

#endif      // EIKCFDLG_H   

// End of File
