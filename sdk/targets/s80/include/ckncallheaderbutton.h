/*
* ==============================================================================
*  Name        : ckncallheaderbutton.h
*  Part of     : CKON
*  Interface   : Callheader Button API
*  Description : Call header button control
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


#ifndef CKNCALLHEADERBUTTON_H
#define CKNCALLHEADERBUTTON_H

// INCLUDES
#include <cknbuttonbase.h>

class CCknSkinBase;

/**
* Features of the call header button include:
*
* 1. drawn entirely from bitmaps; there are three bitmaps per button
* left-end, tiled mid-section and right-end
*
* 2. can re-size in the horizontal direction only
*
* 3. capable of showing just one line of text
*
*		There are four button types for different situations; for a dialog
*		box with one button there is the solitary type; for a dialog box with
*		multiple buttons there are the first, middle and last types
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknCallHeaderButton : public CCknButtonBase
	{
	public:
	enum TPosition
		{
		ECallHeaderButtonFirst,
		ECallHeaderButtonMiddle,
		ECallHeaderButtonLast,
		ECallHeaderButtonSolitary
		};
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CCknCallHeaderButton* NewL();

		/**
		* The second phase constructor.
		*/
		IMPORT_C void ConstructL();

		/**
		* Destructor.
		*/
		IMPORT_C ~CCknCallHeaderButton();

		/**
		* Sets the position of the control.
		* @param aPosition The positon of the control.
		*/
		IMPORT_C void SetPosition(TPosition aPosition);

		/**
		* Handles a change to the control's resource.
		* @param aType A message UID value.
		*/
		IMPORT_C void HandleResourceChange(TInt aType);

		/**
		* Gets the minimumsize of this control.
		* @return The size of the control.
		* <BR><B>Type of return value:</B> TSize
		*/
		IMPORT_C TSize MinimumSize();
	protected:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CCknCallHeaderButton();
	private: // from CCoeControl
		IMPORT_C void Draw(const TRect& aRect) const;
	private: // from MCoeControlContext
		IMPORT_C void PrepareContext(CWindowGc& aGc) const;
	private:
		void GetLeftEnd(TInt& aBitmapIndex) const;
		void GetMidSection(TInt& aBitmapIndex) const;
		void GetRightEnd(TInt& aBitmapIndex) const;
	private:
		TPosition iPosition;
		CCknSkinBase& iSkin;
		TBool iMbmDuplicated;
		void *iReserved;
	};


#endif	// CKNCALLHEADERBUTTON_H

// End of File
