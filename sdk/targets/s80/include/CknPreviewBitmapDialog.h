/*
* ==============================================================================
*  Name        : cknpreviewbitmapdialog.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : CBitmapPreviewControl is an internal class.
*				 CCknPreviewBitmapDialog class implements bitmap's preview dialog.
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


#ifndef CKNPREVIEWBITMAPDIALOG_H
#define CKNPREVIEWBITMAPDIALOG_H

// INCLUDES
#include <EIKBCTRL.H>
#include <eikdialg.h>

/**
*  Control used in the Bitmap Preview dialog
*  This is an internal class.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class CBitmapPreviewControl : public CEikBorderedControl
	{
	public:

		/**
		* C++ constructor.
		* @param aBitmap Bitmap
		*/
		CBitmapPreviewControl(const CFbsBitmap* aBitmap);
	private:
// from CCoeControl
		void Draw(const TRect& aRect) const;
		TSize MinimumSize();
	private:
		const CFbsBitmap* iBitmap;
	};

/**
*  CCknPreviewBitmapDialog class implements bitmap's preview dialog.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class CCknPreviewBitmapDialog : public CEikDialog
	{
	public:

		/**
		* Runs the preview dialog.
		* @param aBitmap Bitmap to be previewed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void RunLD(const CFbsBitmap* aBitmap);
	private:
		CCknPreviewBitmapDialog(const CFbsBitmap* aBitmap);
// from CEikDialog
		SEikControlInfo CreateCustomControlL(TInt aControlType);
	private:
		const CFbsBitmap* iBitmap;
	};


#endif	// CKNPREVIEWBITMAPDIALOG_H
// End of File
