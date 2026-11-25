/*
* =============================================================================
*  Name        : eikdtlbx.h
*  Part of     : CKON
*  Interface   : Tree Listbox API
*  Description : Directory tree listbox and item editor, plus tree listbox base
*                class.
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
* =============================================================================
*/

#ifndef EIKDTLBX_H
#define EIKDTLBX_H

// INCLUDES
#include <eikhlbx.h>
#include <eiklbed.h>
#include <eikdtlbm.h>

// FORWARD DECLARATIONS
class TResourceReader;

// CLASS DECLARATIONS
/**
*  Listbox control for displaying a hierarchical list of items.
*
*  This class is required for backward compatibility. Don't use it, use derived classes instead.
*
*  @deprecated
*  @lib eikfile.lib
*/
class CEikTreeListBoxBaseBC : public CEikHierarchicalListBox, public MHierarchicalListExpansionObserver
    {
    public:
    // Constructors and destructor
        /**
        * C++ default constructor.
        */
        IMPORT_C CEikTreeListBoxBaseBC();

        /**
        * Destructor.
        */
        IMPORT_C ~CEikTreeListBoxBaseBC();

    // New methods
        /**
        * Get the minimum size of the listbox control.
        * @return The minimum size.
        * <BR><B>Type of return value:</B> TSize
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Handles a pointer event on the listbox control.
        * @param aPointerEvent The pointer event.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Handle a keypress on the listbox control.
        * @param aKeyEvent The keypress event.
        * @param aType The type of keypress.
        * @return Specifies whether or not the control consumed the keypress.
        * <BR><B>Type of return value:</B> TKeyResponse
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Creates an item editor, if one does not already exist, and starts editing the current
        * item up to a maximum length of aMaxLength characters.
        * @param aMaxLength The maximum allowed length of the item text.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void EditItemL(TInt aMaxLength);

        /**
        * Updates the listbox to ensure a displayed item will be drawn correctly in the listbox.
        * @param aItemIndex The item to be checked.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void UpdateHierarchyL(TInt aItemIndex);

    protected:  // Methods
        void CheckForErrorFromFileServerL(TInt aErrorCode);
        CArrayPtrFlat<CGulIcon>* BaseConstructLC(const CFont* &aFont);

    protected:     // Data
        TBool* iDtlbxDestroyed;
    };

/**
*  Virtual base class for listboxes that can display a hierarchical list of 
*  items. 
*  This class provides the starting point for the definition of a customized 
*  directory listbox.
*
*  @lib eikfile.lib
*  @since Series90 1.0
*/
class CEikTreeListBoxBase : public CEikTreeListBoxBaseBC
    {
    public:
    // New methods
        
        /**
        * The second phase object constructor for the listbox.
        *
        * @param aParent The parent control
        * @param aFlags The flags to be set in the listbox
        * @param aModelFlags The flags to be set in the listbox model
        * @param aNumVisibleLines The height of the listbox control, in lines
        * @param aWidthInPixels The width of the listbox control, in pixels
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags,TInt aModelFlags,TInt aNumVisibleLines=0,TInt aWidthInPixels=0);

        /**
        * Constructs the listbox control from a resource file.
        *
        * @param aReader A reader positioned for reading from a 
		*                <code>DTLBOX</code> resource
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    protected:  // Methods

    // New Methods
        
        /**
        * Creates a listbox model for this listbox.
        * @param aModelFlags The flags for the listbox model.
        */
        virtual void CreateModelL(TInt aModelFlags)=0;

        /**
        * Constructs the listbox model.
        */
        virtual void ConstructModelL()=0;

        /**
        * Creates the listbox item drawer for this listbox.
        * @param aFont The font to be used in the listbox,
        * @param aIconArray The icons to be used in the listbox.
        */
        virtual void CreateItemDrawerL(const CFont* aFont, CArrayPtr<CGulIcon>* aIconArray)=0;

        void BaseConstructL(TInt aModelFlags);
    };

/**
*  Tree listbox class for displaying a directory structure in a listbox.
*  After construction, only the path needs to be set for the directory 
*  structure to be displayed.
*
*  @lib eikfile.lib
*  @since Series90 1.0
*/
class CEikDirectoryTreeListBox : public CEikTreeListBoxBaseBC
    {
    public:
    // New methods
        
        /**
        * The second phase object constructor.
        *
        * @param aParent The parent control for the listbox control
        * @param aFlags The flags to be set in this listbox
        * @param aModelFlags The flags to be set in this listbox's model
        * @param aNumVisibleLines The height of the listbox control in lines
        * @param aWidthInPixels The width of the listbox control in pixels
        * @return
		* @remarks
		* @see
        */
        IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags,TInt aModelFlags,TInt aNumVisibleLines=0,TInt aWidthInPixels=0);

        /**
        * Updates the listbox to display the file hierarchy for the specified 
		* drive.
		*
        * @param aDrive The number of the drive whose files are to be displayed
        * @return
		* @remarks
		* @see
        */
        IMPORT_C void CreateListL(TDriveNumber* aDrive);

        /**
        * Updates the listbox to display the file hierarchy for the specified 
		* path.
		*
        * @param aPath The path whose files are to be displayed
        * @return
		* @remarks
		* @see
        */
        IMPORT_C void CreateListL(const TDesC& aPath);

        /**
        * Refreshes the listbox to match the files in the specified directory.
		*
        * @return
		* @remarks
		* @see
        */
        IMPORT_C void UpdateL();

        /**
        * Sets the currently selected item to be the one in the specified path.
		*
        * @param aPath The path of the item to be selected
        * @return
		* @remarks
		* @see        
        */
        IMPORT_C void SetCurrentItemPathL(const TDesC& aPath);

        /**
        * Get the listbox model for this listbox. 
		*
        * @return pointer to the listbox model class
		* @remarks
		* @see
        */
        IMPORT_C CDirectoryTreeListBoxModel* DtlModel() const;

        /**
        * Construct the listbox from resources.
		*
        * @param aReader The reader from which the control's resources should 
		*                be read
        * @return
		* @remarks
		* @see
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    private: //Methods
        void BaseConstructL(TInt aModelFlags);
        TInt NewItemIndex(const TDesC& aItemPath) const;
        void SetCurrentItemName(const TDesC& aName,TInt aItemLevel,TInt& aSearchFromIndex);
    };

/**
* Editor class for the directory tree listbox.
* 
* This class allows the names of files and folders in the 
* <code>CEikDirectoryTreeListBox</code> directory structure to be edited. 
* It should be used with <code>CDirectoryTreeListboxModel</code>.
*
* @lib eikfile.lib
* @since Series90 1.0
*/
class CEikDirTreeListBoxEditor : public CEikListBoxTextEditor
    {
    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        * 
        * @param aModel The listbox model for the control to be edited
        * @return
        * @remarks The <code>MListBoxModel</code> is a mixin interface class 
		*          that is implemented by all listbox models. Listbox models 
		*          provide information needed to display the required data in a
		*          listbox. This class should be implemented by anything
        *          providing data for display in a <code>CEikListBox</code> 
		*          derived class. The very basic interface offered by 
		*          <code>MListBoxModel</code> is usually expanded upon to 
		*          provide more information for the specialized subclasses 
        *          of <code>CEikListBox</code>. It is usual when deriving 
		*          specialized listboxes to subclass the listbox class, its 
		*          view classes and its model together
        * @see
        */
        IMPORT_C CEikDirTreeListBoxEditor( MListBoxModel* aModel );

        /**
        * The object destructor.
        *
        * @return
        * @remarks
        * @see
        */
        IMPORT_C ~CEikDirTreeListBoxEditor();

    // New methods
        
        /**
        * Gets the edited text from the editor.
        *
        * @return the descriptor containing the edited text
        * @remarks
        * @see
        */
        IMPORT_C TPtrC ItemText();

        /**
        * Updates the text in the editor to match any relevant changes in the
		* listbox model.
        *
        * @return <code>EFalse</code> if the editor is not currently being 
        *         used;<code>ETrue</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool UpdateModelL();
    };

#endif      // EIKDTLBX_H   
            
// End of File
