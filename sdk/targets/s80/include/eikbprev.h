/*
* ==============================================================================
*  Name        : eikbprev.h
*  Part of     : CKON
*  Interface   : Border API
*  Description : Interface for the border around a preview of text
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


#ifndef EIKBPREV_H
#define EIKBPREV_H

// INCLUDES
#include <eikbctrl.h>
#include <txtfrmat.h>
#include <frmtlay.h>


// CLASS DECLARATIONS

/**
*  Border around a preview of text

*
*  @lib EikCDlg.lib
*  @since ?Series90_version
*/
class CEikBorderPreview : public CEikBorderedControl
	{

	public:

	// Constructors and destructor

		/**
		* C++ default constructor.
		*/
		CEikBorderPreview();

		/**
		* Destructor.
		*/
		~CEikBorderPreview();

	// New methods

		/**
		* Sets the paragraph borders and background colour for the preview
		* @since ?Series90_version
		* @param aBorders Paragraph borders to use
		* @param aBackgroundColor Background colour to use
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		void SetUp(const TParaBorderArray& aBorders,TRgb* aBackgroundColor);

		/**
		* Redraws the border and background
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		void HandleChange();

	// Methods from base classes

		/**
        * From CCoeControl Gets the list of logical colours used to draw the control
		* @param aColorUseList The colour list
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

		/**
        * From CCoeControl
		* @internal
		*/
		void HandleResourceChange(TInt aType);

	private: //Methods

		void Draw(const TRect& aRect) const;
		TSize MinimumSize();
		void ClearRect(const TRect& aRect) const;
		void DrawParaBorders() const;

	private:     // Data

		TPoint iOffset;
		TParaBorderArray iBorders;
		TRgb iBackgroundColor;

	};	


#endif	// EIKBPREV_H

// End of File
