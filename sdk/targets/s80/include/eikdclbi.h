/*
* ==============================================================================
*  Name        : eikdclbi.h
*  Part of     : CKON
*  Interface   : Contents Listbox API
*  Description : Directory contents list box item drawer.
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

#ifndef EIKDCLBI_H
#define EIKDCLBI_H


// INCLUDES
#include <eiklbi.h>
#include <eikclbd.h>

// FORWARD DECLARATIONS
class CDirContentsListBoxModel;
class CFont;
class CGulIcon;
class CColumnListBoxData;

// CLASS DECLARATIONS
/**
*  Drawer class for drawing a CDirContentsListBox.
*
* This can be accessed through the corresponding CDirContentsListBox.
*
* @since Series90 1.0
* @lib eikfile.lib
*/
class CDirContentsListItemDrawer : public CListItemDrawer
    {
	public:  // Declarations
	enum TShowFlags
		{
		EShowSize				=0x01,
		EShowDate				=0x02,
		EShowParentItemName		=0x04,
		EIndentContentItems		=0x08,
		EDisallowParentSelection=0x10,
		EDimReadOnlyFiles		=0x20,
		};

	class TColumnWidths
		{
	public:
		IMPORT_C TColumnWidths();
	public:
		TInt iBitmap;
		TInt iName;
		TInt iSize;
		TInt iDate;
		};

	public:
	// Constructors and destructor

		/**
		* Constructor.
		* @param aModel Pointer to the list box model to be drawn. 
		*/
		IMPORT_C CDirContentsListItemDrawer(const CDirContentsListBoxModel* aModel);

		/**
		* Destructor.
		*/
		IMPORT_C ~CDirContentsListItemDrawer();

	// New methods
        
		/**
		* Second phase constructor.
		* @param aFont Pointer to the font to be used to print the file names.
		* @param aDetailsFont Pointer to the font to be used to print the file details. 
		* @param aColumnData Pointer to the column data of the list box.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(const CFont* aFont,const CFont* aDetailsFont, CColumnListBoxData* aColumnData);

		/**
		* Sets the icons to be displayed beside the file names.
		* @param aIconArray Pointer to an icon array.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aIconArray);

		/**
		* Calculates the widths of the list box's columns. This function should be 
		* called after setting the icons and fonts.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void CalcColumnWidths();

		/**
		* Used to set the column widths specifically.
		* @param aWidths Data structure containing the widths of the columns
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetColumnWidths(TColumnWidths& aWidths);

		/**
		* Gets the list box model.
		* @return Pointer to the list box model which contains the data to be displayed.
		* <BR><B>Type of return value:</B> CDirContentsListBoxModel*
		*/
		IMPORT_C CDirContentsListBoxModel* DclModel() const;

		/**
		* Sets the flags for this item drawer. 
		* 
		* Flags specific to this class are:
		*     EShowSize  :  Includes the file size column
		*     EShowDate  :  Includes the file date modified column
		*     EShowParentItemName  :  Includes a parent directory item in the list box
		* @param aFlags The flags to be set.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetDclItemDrawerFlags(TInt aFlags);

		/**
		* Clears the specified flags for this item drawer.
		* @param aFlags The flags to be cleared.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ClearDclItemDrawerFlags(TInt aFlags);

		/**
		* Gets the list box's column widths.
		* @return Data structure containing the column widths.
		* <BR><B>Type of return value:</B> CDirContentsListItemDrawer::TColumnWidths
		*/
		IMPORT_C CDirContentsListItemDrawer::TColumnWidths ColumnWidths() const;
	
		/**
		* Second phase constructor.
		* @param aFont Pointer to the font to be used to print the file names.
		* @param aDetailsFont Pointer to the font to be used to print the file details. 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(const CFont* aFont,const CFont* aDetailsFont);

		/**
		* Sets the file uids to be drawn, and transfers ownership of the array to this class.
		* @param aUidArray Array of Uids.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetUidArray(CArrayFix<TUid>* aUidArray);

		/**
		* Gets the icon index for a specified item.
		* @param aItemIndex The index for the specified item.
		* @return The icon index.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt IconIndexFromItemIndex(TInt aItemIndex) const;

		/**
		* Gets the icon array for this item drawer.
		* @return Pointer to the array of icons.
		* <BR><B>Type of return value:</B> CArrayPtr<CGulIcon>*
		*/
		IMPORT_C CArrayPtr<CGulIcon>* IconArray() const; 

		/**
		* Gets the list box column data.
		* @return Pointer to the data.
		* <BR><B>Type of return value:</B> CColumnListBoxData*
		*/
		IMPORT_C CColumnListBoxData* ColumnData() const;

		/**
		* Draws a specified item.
		*
		* @param aItemIndex The index of the item to be drawn
		* @param aActualItemRect The area on which the drawing should be done.
		* @param aItemIsCurrent Set to ETrue if this item is the current item.
		* @param aViewIsEmphasized Set to ETrue if this item is emphasized.
		* @param aViewIsDimmed Set to ETrue if this item is dimmed.
		* @param aItemIsSelected Set to ETrue if this item is selected.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void DrawActualItem(TInt aItemIndex,const TRect& aActualItemRect,TBool aItemIsCurrent,TBool aViewIsEmphasized,TBool aViewIsDimmed,TBool aItemIsSelected) const;

		/**
		* Gets the width of a particular item.
		* @param aItemIndex The index of the item whose width is requested.
		* @return The width in pixels.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const;

		/**
		* Gets the minimum size of an item. This is calculated from the sizes of the fonts and icons.
		* @return The calculated minimum size.
		* <BR><B>Type of return value:</B> TSize
		*/
		IMPORT_C TSize MinimumCellSize() const;

		/**
		* Sets the area through which this object may be viewed.
		* @param aRect The view rectangle. Only that part of the list box which appears 
		* 		within this area will be drawn. 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetViewRect(const TRect& aRect);

		/**
		* Sets the width of the column containing the mark.
		* @param aWidthInPixels New width for the mark column.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMarkColumnWidth(TInt aWidthInPixels);

		/**
		* Sets the width of the gap between the column containing the lists item
 		* marks and the text column.
		* @param aGapInPixels New gap size.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMarkGutter(TInt aGapInPixels);

		/**
		* @return ETrue if the parent item can not be selected.
		* <BR><B>Type of return value:</B> TBool
		*/
		TBool ParentItemNotSelectable() const;

		/**
		* Modifies the rectangle to be positioned over the specified item.
		* @param aItem The index of the item to move the rectangle over.
		* @param aRect The rectangle to be modified.
		* <BR><B>Type of return value:</B> void
		*/
		void AdjustItemRect(TInt aItem,TRect& aRect) const;

    private: //Methods
		IMPORT_C TAny* Reserved_1();
		TBool GetItemText(TDes& aText,TInt aItemIndex) const;
		CGulIcon* ItemIcon(TInt aItemIndex) const;

	private:     // Data
		const CDirContentsListBoxModel* iModel;
		TUint iDcFlags;
		TBuf<2> iSeparators;
		CArrayFix<TUid>* iFileUidArray;
    };

#endif      // EIKDCLBI_H   
            
// End of File
