/*
* ==============================================================================
*  Name        : Eikgysel.h
*  Part of     : CKon
*  Interface   : Color Selector API	
*  Description : Classes relating to CKON popout color selection
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

#ifndef EIKGYSEL_H
#define EIKGYSEL_H

// INCLUDES
#include <eikbctrl.h>
#include <eikcmobs.h>
#include <eikchlst.h>
#include "EikUbgcb.h"

// DATA TYPES
// FORWARD DECLARATIONS
class CEikButtonGroupContainer;
class TResourceReader;

/**
 * Class CEikGrayPalette
 *
 * This class creates the popout window where the colors
 * are displayed.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikGrayPalette : public CEikBorderedControl, public MEikCommandObserver
	{
	public:
	enum TGrayPaletteDisplayMode
		{
		EDisplayMode4Gray,
		EDisplayMode16Gray,
		EDisplayMode16Color,
		EDisplayMode256Color,
		EDisplayMode2Gray,
		EDisplaySkinDefinedColors
		};
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikGrayPalette();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikGrayPalette();

		/**
		* ConstructL - Second phase constructor.
		* @param aMode Specifies Display mode (See enum TGrayPaletteDisplayMode above).
		* @return void
		*/
		IMPORT_C void ConstructL(TGrayPaletteDisplayMode aMode);

		/**
		* Gets the selected color.
		* @return an instance of a TRgb class containing associated rgb value
		* <BR><B>Type of return value:</B> TRgb
		* <BR><B>Range of return value:</B> See GDI.h for more information on the class TRbg
		*/
		IMPORT_C TRgb SelectedGray() const;

		/**
		* Sets the selected gray color.
		* @param aColor TRgb class containing the gray color to set (See GDI.h for more information on TRgb class)
		* @return void
		*/
		IMPORT_C void SetSelectedGray(const TRgb& aColor);
	public: // from CCoeControl

		/**
		* See SizeChanged() method in CCoeControl.
		*/
		IMPORT_C void SizeChanged();

		/**
		* See MinimumSize() method in CCoeControl.
		*/
		IMPORT_C TSize MinimumSize();

		/**
		* See OfferKeyEventL() method in CCoeControl.
		*/
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

		/**
		* See HandlePointerEventL() method in CCoeControl.
		*/
		IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

		/**
		* See Draw() method in CCoeControl.
		*/
		IMPORT_C void Draw(const TRect& aRect) const;

		/**
		* See GetColorUseListL() method in CCoeControl.
		*/
		IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* See HandleResourceChange() method in CCoeControl.
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

		/**
		* See InputCapabilities() method in CCoeControl.
		*/
		IMPORT_C TCoeInputCapabilities InputCapabilities() const;

	public: // from CCoeControl

		/**
		* See ActivateL() method in CCoeControl.
		*/
		IMPORT_C void ActivateL();

	protected:

		/**
		* Creates a button group container for the control, allowed for sub classes too.
		* This contains OK and cancel commands.
		* @return void
		*/
		IMPORT_C void CreateButtonGroupContainerL();

	protected: // from MEikCommandObserver

		/**
		* See ProcessCommandL() method in MEikCommandObserver.
		*/
		IMPORT_C void ProcessCommandL(TInt aCommandId);

	private:
		inline TInt MaxLevel() const;
		inline TInt Granularity() const; 
		void DrawGraySelections() const;
		void DrawHighlightToGray(TInt aGrayLevel, TBool aHighLighted) const;
		void DrawHighlightToGrayNow(TInt aGrayLevel, TBool aHighLighted) const;
	private:
		TInt iMaxGrayLevel; 
		TInt iSelectedGray;
		TPoint iTopLeft;
		TAny *iReserved1;	// iReserved1 & iReserved2 replace iSingleGrayDisplaySize from original version
		TAny *iReserved2;
		CEikButtonGroupContainer *iButtonGroupContainer;
	};


/**
 * class CEikGraySelector
 *
 * This class defines color selector which is used to select
 * colors. Colors are displayed in 4x4 or 1x4 matrix. 
 */

class CEikGraySelector : public CEikChoiceListBase, public MEikUpdatingBgContainerBase
    {
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikGraySelector();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikGraySelector();

		/**
		* ConstructL() - Second phase constructor.
		* @param aParent - Parent, used to set the container window (SetContainerWindowL(*aParent))
		* @param aFlags - Gray color selection such as EEikGraySelDisplay4Gray. See EIkon.hrh for more details
		* @return void
		*/
		IMPORT_C void ConstructL(CCoeControl* aParent, TInt aFlags);

		/**
		* See MinimumSize() method in CCoeControl.
		*/
		IMPORT_C virtual TSize MinimumSize();

		/**
		* See ConstructFromResourceL() method in CCoeControl.
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Gets the currently selected color.
		* @return an instance of a TRgb class containing associated rgb value
		* <BR><B>Type of return value:</B> TRgb
		* <BR><B>Range of return value:</B> See GDI.h for more information on the class TRbg
		*/
		IMPORT_C TRgb SelectedColor() const;

		/**
		* Sets the selcted color.
		* @param aColor TRgb class containing the color to set (See GDI.h for more information on TRgb class)
		* @return void
		*/
		IMPORT_C void SetSelectedColor(TRgb& aColor);

	public:	// from CCoeControl

		/**
		* See GetColorUseListL() method in CCoeControl.
		*/
		IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

		/**
		* See HandleResourceChange() method in CCoeControl.
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			

		/**
		* See PrepareForFocusGainL() method in CCoeControl.
		*/
		IMPORT_C void PrepareForFocusGainL();

		/**
		* See FocusChanged() method in CCoeControl.
		*/
		IMPORT_C void FocusChanged(TDrawNow /*aDrawNow*/);

	protected:

		/**
		* Creates the selector popout window.
		* @return void
		*/
		IMPORT_C virtual void CreatePopoutL();

		/**
		* Destroys the selector window. 
		* @return void
		*/
		IMPORT_C virtual void DestroyPopout();

		/**
		* Gets the current item number. 
		* @return Item Number
		*/
		IMPORT_C virtual TInt PopoutCurrentItem() const;
	protected: // from MEikUpdatingBgContainerBase

		/**
		 * This function does nothing.
		 *
		 * @since ER5U 
		 */
		IMPORT_C void HandleChangeButtonL();

		/**
		* Determins if popout is dipslayed
		* @return ETrue if on display, EFalse if not on display
		*/
		IMPORT_C TBool PopupDisplayed();

	private:
		IMPORT_C virtual void DrawContent() const;
		IMPORT_C void DoCreatePopoutL();
		void CreateGrayLevelArrayL();
		void BaseConstructL(TInt aFlags);
	private:
		CEikGrayPalette* iGrayPalette;
		TInt iGraySelectorFlags;
    };								


#endif	// EIKGYSEL_H

// End of File
