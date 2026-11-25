/*
* ==============================================================================
*  Name        : eikdclbx.h
*  Part of     : CKON
*  Interface   : Contents Listbox API
*  Description : Directory contents list box.
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

#ifndef EIKDCLBX_H
#define EIKDCLBX_H

// INCLUDES
#include <eiklbx.h>
#include <eiklbed.h>
#include <badesca.h>

// FORWARD DECLARATIONS
class CDirContentsListBoxModel;
class CDirContentsListItemDrawer;
class CApaAppList;
class RApaLsSession;
class CGulIcon;

// CLASS DECLARATIONS

/**
*  Specific list box class for displaying the contents of a folder.
*
*  After construction, only the path needs to be set and the contents will be displayed.
*  This differs from the CEikDirectoryTreeListBox in that only one layer of files is shown, 
*  plus an optional root. This listbox handles all the file access internally.
*
*  @lib eikfile.lib
*  @since Series90 1.0
*/
class CEikDirContentsListBox : public CEikListBox
    {
	public:  // Declarations
	enum TDirContentsListBoxFlags
		{
		EShowNoItems 	= 0x10000	/** The dummy item will be used to show 'no items' text*/
									/** Only used in single selection mode,non-popout listboxes*/
		};

	public:
	// Constructors and destructor
		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikDirContentsListBox();

	// New methods
		/**
		* Second phase constructor for the list box.
		* @param aParent The parent control of the list box.
		* @param aListBoxFlags The list box flags.
		* @param aModelFlags The list box model flags.
		* @param aNumVisibleLines The height of the list box in lines.
		* @param aWidthInPixels The width of the list box in pixels.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aListBoxFlags=0,TUint aModelFlags=0,TInt aNumVisibleLines=0,TInt aWidthInPixels=0);

		/**
		* Get the directory list box model.
		* @return Pointer to the list box's CDirContentsListBoxModel class.
		* <BR><B>Type of return value:</B> CDirContentsListBoxModel*
		*/
		IMPORT_C CDirContentsListBoxModel* DclModel() const;

		/**
		* Get the directory list box item drawer.
		* @return Pointer to the list box's CDirContentsListItemDrawer class.
		* <BR><B>Type of return value:</B> CDirContentsListItemDrawer*
		*/
		IMPORT_C CDirContentsListItemDrawer* DclItemDrawer() const;

		/**
		* Sets the directory whose files are to be displayed in the list box.
		* This function calls HandleListUpdateL() after setting the new directory.
		* @param aPath The full path name.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetPathL(const TDesC& aPath);

		/**
		* Get the file name array of displayed items in the list box.
		* @param aItems Pointer to an array, which is to be filled with the file name array. 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void GetFullNamesOfSelectedItemsL(CDesCArray* aItems) const;

		/**
		* Updates the list box to see if any flags have been changed.  
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void HandleListUpdateL();

		/**
		* Refreshes the file array and changes the list of file names if required. 
		* This function calls HandleListUpdateL() after updating the file list.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void UpdateL();

		/**
		* Changes the displayed name of the currently selected item.
		* @param aName The new name for the item.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetCurrentItemName(const TDesC& aName);

		/**
		* Specifies whether or not text should be displayed when the file list is empty.
		* @param aShowNoItems Set to ETrue if 'no items' text should be displayed. EFalse if it shouldn't.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetShowNoItems(TBool aShowNoItems);

		/**
		* @return ETrue if text will be displayed when the file list is empty,
		*         EFalse if no text will be displayed.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool ShowNoItems();

		void GetIconListL(RApaLsSession& aLs);

		IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);

		/**
		* Constructs the control from the resources specified.
		* @param aReader The resource reader from which the control's resources will be read. 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Handles key presses in the list box control.
		* @param aKayEvent The type of keypress event.
		* @param aType The keypress event code.
		* @return Specifies whether or not the keypress was consumed by the control.
		* <BR><B>Type of return value:</B> TKeyResponse
		*/
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKayEvent,TEventCode aType);

		/**
		* Handles a pointer event in the list box control.
		* @param aPointerEvent The pointer event.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

		/**
		* Gets the minimum allowed size of the list box control.
		* @return The minimum size.
		* <BR><B>Type of return value:</B> TSize
		*/
		IMPORT_C TSize MinimumSize();

		/**
		 * Creates an item editor, if one does not already exist, and starts editing the current
		 * item up to a maximum length of aMaxLength characters.
		 *
		* @param aMaxLength The maximum text length allowed for the current item
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void EditItemL(TInt aMaxLength);

    private: //Methods
		IMPORT_C void Reserved_3(); // listbox use only
		void BaseConstructL(TInt aModelFlags);
		void HandleItemSelectionL(TInt aItemIndex);
		CGulIcon* CreateDRMIconL(const CGulIcon& aIcon);

	private:     // Data
		TInt iPressedIndex;
    };

/**
*  Editor class for the CEikDirContentsListBox.
*  This automatically renames files or folders after editing.
*
*  @lib eikfile.lib
*  @since Series90 1.0
*/
class CEikDirContentsListBoxEditor : public CEikListBoxTextEditor
    {
	public:
	// Constructors and destructor
		/**
		* Destructor.
		*/
		IMPORT_C ~CEikDirContentsListBoxEditor();

	// New methods
        
		/**
		* Constructor.
		* Creates a new list box editor.
		* @param aModel The list box model which needs editing.
		*/
		IMPORT_C CEikDirContentsListBoxEditor(MListBoxModel* aModel);

		/**
		* Gets the edited text.
		* @return Descriptor for the text displayed in the editor.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC ItemText();

		/**
		* Updates the edited text to match any possible changes to the list box model.
		* @return EFalse if the editor is not currently being used.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool UpdateModelL();
    };


#endif      // EIKDCLBX_H   
            
// End of File
