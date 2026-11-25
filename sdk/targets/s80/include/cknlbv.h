/*
* ==============================================================================
*  Name        : cknlbv.h
*  Part of     : CKON / CKNCTL
*  Interface   : Snaking Listbox API
*  Description : Snaking Listbox with gaps and brush
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


#ifndef CKNLBV_H
#define CKNLBV_H

// INCLUDES
#include <eiklbv.h>


/**
* The CSnakingListBoxViewWithGapsAndBrush class implements a Snaking Listbox 
* with gaps between the columns and a background brush.
*
* @lib cknctl.lib
* 
*/

class CSnakingListBoxViewWithGapsAndBrush : public CSnakingListBoxView
	{
	public:

		/**
		* The two-phase object constructor.
        * 
        * @return the Snaking Listbox object
        * @remarks
        * @see
		*/
		IMPORT_C static CSnakingListBoxViewWithGapsAndBrush* NewL();

    public: // new functions

		/**
		* Sets the vertical gap between columns.
        *
		* @param aColumnGap The size of the vertical gap, in pixels 
		* @return 
        * @remarks
        * @see
		*/
		IMPORT_C void SetColumnGap(TInt aColumnGap);

		/**
		* Returns the vertical gap between columns.
        *
		* @return the vertical gap between columns, in pixels
        * @remarks
        * @see
		*/
		IMPORT_C TInt ColumnGap();

		/**
		* Sets the brush pattern to be used from a bitmap.
        *
		* @param aBitmap A pointer to the bitmap to use as the brush pattern
		* @return 
        * @remarks
        * @see
		*/
		IMPORT_C void UseBrushPattern(const CFbsBitmap* aBitmap);

    private: // from CSnakingListBox
		virtual void CalcBottomItemIndex();
		virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;
		virtual TInt VisibleWidth(const TRect& aRect) const;
		virtual void HScroll(TInt aHScrollAmount);
		virtual void DrawItem(TInt aItemIndex) const;
	private: 
		CSnakingListBoxViewWithGapsAndBrush();
		TBool ItemExists(TInt aIndex) const;
	private:
		TInt iColumnGap;
		const CFbsBitmap* iBrushPattern;
	};


#endif	// CKNLBV_H

// End of File
