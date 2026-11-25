/*
* ==============================================================================
*  Name        : ckndlgbut.h
*  Part of     : CKON
*  Interface   : Dialog Button API
*  Description : Dialog button control
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


#ifndef CKNDLGBUT_H
#define CKNDLGBUT_H

// INCLUDES
#include <eikcmbut.h>

/**
*  Features of the CKON dialog button include:
*  1. drawn entirely from bitmaps; there are three bitmaps per button
*     left-end, tiled mid-section and right-end
*  2. can re-size in the horizontal direction only
*  3. capable of showing just one line of text
*
*  There are four button types for different situations; for a dialog
*  box with one button there is the solitary type; for a dialog box with
*  multiple buttons there are the first, middle and last types.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknDialogButton : public CEikCommandButton
	{
	public:
	enum TPosition
		{
		EDialogButtonFirst,
		EDialogButtonMiddle,
		EDialogButtonLast,
		EDialogButtonSolitary
		};
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CCknDialogButton* NewL();

		/**
		* The second phase constructor.
		*/
		IMPORT_C void ConstructL();

		/**
		* Destructor.
		*/
		IMPORT_C ~CCknDialogButton();

		/**
		* This function sets the position and margin of the dialog button. The left and
		* right margins of dialog buttons are different depending on the button position.
		* @param aPosition The position of the control.
		*/
		IMPORT_C void SetPosition(TPosition aPosition);

		/**
		* Handles a change to the control's resources that are shared across the environment. 
		* Examples include colors or fonts.
		* @param aType The type of the resource that has been changed.
		*/
		IMPORT_C void HandleResourceChange(TInt aType);
	protected:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CCknDialogButton();
	private: // from CCoeControl
		IMPORT_C void Draw(const TRect& aRect) const;
	private: // from MCoeControlContext
		IMPORT_C void PrepareContext(CWindowGc& aGc) const;
	private:
		void GetLeftEnd(TInt& aBitmapIndex) const;
		void GetMidSection(TInt& aBitmapIndex) const;
		void GetRightEnd(TInt& aBitmapIndex) const;
		void SetMargins();
	private:
		TPosition iPosition;
		void *iReserved;
	};


#endif	// CKNDLGBUT_H

// End of File
