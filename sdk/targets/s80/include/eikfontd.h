/*
* ==============================================================================
*  Name        : eikfontd.h
*  Part of     : CKon
*  Interface   : CEikFontDialog
*  Description : Classes that contribute to the Font Dialogs
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


#ifndef EIKFONTD_H
#define EIKFONTD_H

// INCLUDES
#include <eikdialg.h>
#include <txtfrmat.h>
#include <badesca.h>
#include <gdi.h>
#include <gulftflg.hrh>

// FORWARD DECLARATIONS
class CPreviewDlg;

// CONSTANTS
const TInt KEikFontDlgLenHotKeysArray=3;
/**
* Set font dialog.
*
* A multi page dialog for setting the font and other text attributes. 
* The first page contains two choice lists for selecting the typeface and 
* size and three check boxes for bold, italics and underlining. 
* The second page contains a colour selector, a checkbox for strikethrough and 
* a print position choicelist. Both pages have a font preview control.
*
*  @lib EIKCDLG.LIB
*  @since Series90 1.0
*/
class CEikFontDialog : public CEikDialog  
	{
	public:

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikFontDialog();

		/**
		* Initialises and launches the set font dialog.
		* @param aFormat - Contains the font and text attributes in effect at the cursor position. This is used to initialise the dialog's settings. On return, contains the new font and text attributes.
		* @param aAttribChangedMask - On return, indicates which attributes in aFormat were changed by the dialog.
		* @param aFonts - Specifies which font types should appear in the list.
		* @param aGraphicsDevice - The graphics device. This is used to get the list of available fonts. If NULL, the default screen device is used.
		* @param aFontControlFlags - A set of flags that specify which font controls should appear in the dialog, e.g. specifying EGulFontControlBold removes the bold checkbox control. The default shows all.
		* @param aBackGroundColor - The background colour for the font preview controls. White by default.
		* @return True if the user pressed OK (or equivalent), false if the dialog was cancelled.
		* <BR><B>Type of return value:</B> TBool
		*/

		IMPORT_C static TBool RunDlgLD(TCharFormat& aFormat,
							TCharFormatMask& aAttribChangedMask,
							TInt aFonts=EGulNoSymbolFonts,
							CGraphicsDevice* aGraphicsDevice=NULL, 
							TInt aFontControlFlags=EGulFontControlAll,
							const TRgb aBackGroundColor=KRgbWhite);

		/**
		* Initialises and launches the set font dialog.
		* @param aFormat - Contains the font and text attributes in effect at the cursor position. This is used to initialise the dialog's settings. On return, contains the new font and text attributes.
		* @param aAttribChangedMask - On return, indicates which attributes in aFormat were changed by the dialog.
		* @Param aUndeterminedMask - Indicates attributes that only apply to a part of the selection, so that the dialog's initial settings for those attributes are indeterminate.
		* @Param aTextSelection - The selected text. This is displayed in the font preview control.
		* @param aFonts - Specifies which font types should appear in the list.
		* @param aGraphicsDevice - The graphics device. This is used to get the list of available fonts. If NULL, the default screen device is used.
		* @param aFontControlFlags - A set of flags that specify which font controls should appear in the dialog, e.g. specifying EGulFontControlBold removes the bold checkbox control. The default shows all.
		* @param aBackGroundColor - The background colour for the font preview controls. White by default.
		* @return True if the user pressed OK (or equivalent), false if the dialog was cancelled.
		* <BR><B>Type of return value:</B> TBool
		*/

		IMPORT_C static TBool RunDlgLD(TCharFormat& aFormat,
							TCharFormatMask& aAttribChangedMask,
							TCharFormatMask& aUndeterminedMask,
							TDesC& aTextSelection,
							TInt aFonts=EGulNoSymbolFonts,
							CGraphicsDevice* aGraphicsDevice=NULL, 
							TInt aFontControlFlags=EGulFontControlAll,
							const TRgb aBackGroundColor=KRgbWhite);

		IMPORT_C static TBool RunDlgLD(TCharFormat& aFormat,
							TCharFormatMask& aAttribChangedMask,
							TCharFormatMask& aUndeterminedMask,
							TDesC& aTextSelection,
							TInt aFonts,
							CGraphicsDevice* aGraphicsDevice, 
							TInt aFontControlFlags,
							const TRgb aBackGroundColor,
							CEikFontDialog*& aDialog);

	//from CCoeControl

		/**
		* See CCoeControl
		*/
		void GetHelpContext(TCoeHelpContext& aContext) const;

	private: 
	CEikFontDialog(			TCharFormat& aFormat,
							TCharFormatMask& aAttribChangedMask,
							TInt aFonts=EGulNoSymbolFonts,
							CGraphicsDevice* aGraphicsDevice=NULL, 
							TInt aFontControlFlags=EGulFontControlAll,
							const TRgb aBackGroundColor=KRgbWhite);

	CEikFontDialog(			TCharFormat& aFormat,
							TCharFormatMask& aAttribChangedMask,
							TCharFormatMask& aUndeterminedMask,
							TDesC& aTextSelection,
							TInt aFonts=EGulNoSymbolFonts,
							CGraphicsDevice* aGraphicsDevice=NULL, 
							TInt aFontControlFlags=EGulFontControlAll,
							const TRgb aBackGroundColor=KRgbWhite);

	// framework
		TBool OkToExitL(TInt aButtonId);
		void PreLayoutDynInitL();
		void PostLayoutDynInitL();
		void HandleControlStateChangeL(TInt aControlId);
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	private: // personal
		void SetHotKeysFromResourceL();
		void GetAvailableFontsL(CGraphicsDevice& aDevice,CDesCArray& aFontNameList,TInt aFonts);
		void BuildFontNameListL();
		void UpdateHeightListL();
		void RemoveDuplicatePointHeights();
		void ConstructArraysL();
		void RunPreviewDialogL();
		void SetPreviewDimmed(TBool aDimmed);
		TBool IsPreviewDimmed() const;
		TBool FontAttributesUndetermined();
	private:
		class CPreviewDlg;
	private:
		TFixedArray<TInt,KEikFontDlgLenHotKeysArray> iHotKeyCodes;
		TInt iFontFlags;
		TInt iFontControlFlags;
		CGraphicsDevice* iGraphicsDevice;
		TCharFormat* iActiveFormat;
		TCharFormatMask* iAttribChangedMask; 
		TCharFormatMask iUndeterminedMask;	
		CDesCArray* iFontHeightList;
		CArrayFixFlat<TInt>* iTwipsList;
		TPtrC iTextSelection;
		TInt iHeightInTwips;
		TRgb iBackGroundColor;
		CDesCArray* iFontNameList;  
		TInt iCurrentSizeListWidth;
		CEikFontDialog** iSelfPointer;
	};

/**
*  Font preview dialog.
*
*  This dialog is launched from the set font dialog to preview a font.
*
*  @lib EIKCDLG.LIB
*  @since Series90 1.0
*/
class CEikFontDialog::CPreviewDlg : public CEikDialog
	{
	public:

		/**
		* Launch the preview dialog.
		* @param aFormat - Contains the font and text attributes in effect at the cursor position. This is used to initialise the dialog's settings. On return, contains the new font and text attributes.
		* @param aTextSelection - The selected text. This is displayed in the font preview control.
		* @param aBackGroundColor - The background colour for the font preview controls. White by default.
		* @return void
		*/
		static void RunDlgLD(const TCharFormat& aFormat, const TDesC& aText, const TRgb& aBackGround);
	//from CCoeControl

		/**
		* See CCoeControl
		*/
		void GetHelpContext(TCoeHelpContext& aContext) const;

	private:
		CPreviewDlg(const TCharFormat& aFormat, const TDesC& aText, const TRgb& aBackGround);
		~CPreviewDlg();
	private: //framework
		TBool OkToExitL(TInt aButtonId);
		void PostLayoutDynInitL();
		void PreLayoutDynInitL();
	private:
		CFbsFont* iPreviewFont;
		const TCharFormat* iActiveFormat;
		const TDesC& iTextSelection;
		const TRgb& iBackGroundColor;
	};


#endif	// EIKFONTD_H

// End of File
