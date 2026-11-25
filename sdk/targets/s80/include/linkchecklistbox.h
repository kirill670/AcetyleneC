/*
* ==============================================================================
*  Name        : linkchecklistbox.h
*  Part of     : LinkModel
*  Interface   : Add to Desk API
*  Description : List box containing checkboxes and associated dialog.
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


#ifndef __LINKCHECKLISTBOX_H__
#define __LINKCHECKLISTBOX_H__

// INCLUDES
#include <eikdialg.h>
#include <bamdesca.h>

// FORWARD DECLARATIONS
class CEikColumnListBox;


/**
 * Observer class for using the check list box dialog.
 * 
 *  @since Series90 1.0
 */
class MCheckListBoxObserver
	{
	public:
		/**
		* Toggle the state of the given item. If the item cannot be toggled an
		* infoprint is displayed.
		* @param aItem The index of the item to be toggled.
		* @return ETrue if the toggles is successful. EFalse if it cannot be
		* toggled.
		* <BR><B>Type of return value:</B> TBool
		*/
		virtual TBool ToggleItemState(TInt aItem)=0;
	};

/**
 *  Base class for a dialog containing a scrolling list of checkboxes.
 *
 *  @lib linkmodel.h
 *  @since Series90 1.0
 */
class CScrollingCheckBoxListDialog : public CEikDialog, public MDesCArray, public MCheckListBoxObserver
	{
	friend class CAddToDeskDialog;
	public:
	enum
		{
		EItemClear=0,
		EItemSet=1,
		EItemClearDim=2,
		EItemSetDim=3
		};
	protected:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CScrollingCheckBoxListDialog();
		
	
		/**
		* Destructor.
		*/
		IMPORT_C ~CScrollingCheckBoxListDialog();

		/**
		* Call to set the text that is displayed when no items exist.
		* @param aResId The resource ID of the text.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetZeroItemTextL(TInt aResId);

		/**
		* This must be called after items have been added to the listbox.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void HandleItemsAddedL();

		/**
		* This must be called after items have been removed from the listbox.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void HandleItemsRemovedL();

		/**
		* Initialises up the list box columns during the dialog setup.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void PostLayoutDynInitL();

		/**
		* Initialises the list box model and scroll bars during dialog setup.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void PreLayoutDynInitL();

		/**
		* @return a pointer to the listbox of checkboxes.
		* <BR><B>Type of return value:</B> CEikColumnListBox*
		*/
		IMPORT_C CEikColumnListBox* ListBox() const;

		/**
		* Returns whether a particular item is ticked or dimmed .
		* @param aIndex The index of the item in question.
		* @return The state of the item. This will be one of:
		*		EItemClear		=0
		*		EItemSet		=1
		*		EItemClearDim	=2
		*		EItemSetDim		=3
		* <BR><B>Type of return value:</B> TInt
		*/
		virtual TInt ItemState(TInt aIndex) const=0;

		/**
		* Returns the text of a particular item.
		* @param aIndex The index of the item in question.
		* @return The item's text.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		virtual TPtrC ItemText(TInt aIndex) const=0;

		/**
		* @return the number of items in the list box. Call HandleItemsAddedL 
		* or RemovedL if the count changes.
		* <BR><B>Type of return value:</B> TInt
		*/
		virtual TInt ItemCount() const=0;
	private:
		void CheckFirstColumnWidthL();

// from MDesCarray
		IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
		IMPORT_C TInt MdcaCount() const;
// from CEikDialog
		IMPORT_C SEikControlInfo CreateCustomControlL(TInt aControlType);
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	private:
		mutable TBuf<256> iBuffer;
		HBufC* iNoItemsText;
	};

#endif // __LINKCHECKLISTBOX_H__

// End of File
