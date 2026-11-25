/*
* =============================================================================
*  Name        : eiklbed.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox editor classes.
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

#ifndef EIKLBED_H
#define EIKLBED_H


//** INCLUDES */
#include <e32base.h>
#include <eiklbm.h>
#include <w32std.h>
#include <coedef.h>
#include <coecntrl.h>
#include <gulutil.h>

//** FORWARD DECLARATIONS */
class CCoeControl;
class CEikEdwin;
class CListBoxExt;
class CParaFormatLayer;
class CCharFormatLayer;

//** CLASS DECLARATIONS */

/**
 * The <code>MEikListBoxEditor</code> class provides the Listbox text editor 
 * interface. The class specifies an interface to a text editor that can be 
 * used inside a Listbox to edit individual Listbox item text.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class MEikListBoxEditor
    {
    //** New methods */
public:
    /**
     * Gets a pointer to the current editable item text.
     *
     * @return a pointer to the editable item text
     * @remarks
     * @see
     */
    virtual TPtrC ItemText() = 0;

    /**
     * Creates the editor inside the specified Listbox container.
     *
     * @param aContainer The Listbox within which the editor is created
     * @param aRect The editor's rectangle
     * @param aItemIndex The index of the item to edit
     * @param aMaxLength The maximum number of characters
     * @remarks
     * @see
     */
    virtual void StartEditingL(const CCoeControl& aContainer,const TRect& aRect,TInt aItemIndex,TInt aMaxLength) = 0;

    /**
     * Stops editing and deletes the item editor.
     *
     * @remarks
     * @see
     */
    virtual void StopEditingL() = 0;

    /**
     * Updates the Listbox model with the new item contents.
     *
     * @return <code>ETrue</code> if successful; <code>EFalse</code> if editing 
     *         is not currently on
     * @remarks This method is usually called just before <code>StopEditingL()</code>
     *          is invoked
     * @see
     */
    virtual TBool UpdateModelL() = 0;

    /**
     * Deletes the editor.
     *
     * @remarks
     * @see
     */
    virtual void Release() = 0;

private: //** Methods */
    IMPORT_C virtual void MEikListBoxEditor_Reserved_1();
    };

/**
 * The <code>MListBoxEditorObserver</code> class is a Listbox editor observer 
 * mixin interface. The class specifies a mixin interface
 * to handle keyboard events that occur within a Listbox editor.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class MListBoxEditorObserver
    {
    //** New methods */
public:
    /**
    * Handles a Listbox editor event.
    *
    * @param aListBoxEditor The Listbox editor for which the key event is handled
    * @param aKeyEvent The key event to handle
    * @return the response to the key event
    * @remarks
    * @see
    */
    virtual TKeyResponse HandleListBoxEditorEventL(MEikListBoxEditor* aListBoxEditor, const TKeyEvent& aKeyEvent)=0;
    };

/**
 * The <code>CEikListBoxTextEditor</code> class provides the Text Listbox item 
 * editor. The item editor is used to edit the text of actual Text Listbox items.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikListBoxTextEditor : public CCoeControl, public MEikListBoxEditor
    {
public:
    /**
     * The object destructor.
     */
    IMPORT_C ~CEikListBoxTextEditor();


    //** New methods */

    /**
     * The object constructor.
     *
     * @param aModel The model for the Text Listbox item editor
     * @remarks
     * @see
     */
    IMPORT_C CEikListBoxTextEditor(MListBoxModel* aModel);

    /**
     * Sets the editor's font.
     *
     * @param aFont The font to use for the Listbox's text editor
     * @remarks
     * @see
     */
    IMPORT_C void SetFont(const CFont* aFont);

    /**
     * Gets a pointer to the Listbox editor.
     *
     * @return a pointer to the Listbox editor
     * @remarks
     * @see
     */
    IMPORT_C CEikEdwin* Editor();

    /**
     * Sets the Listbox editor's observer.
     *
     * @param aObserver The Listbox editor's observer
     * @remarks
     * @see
     */
    IMPORT_C void SetListBoxEditorObserver(MListBoxEditorObserver* aObserver);

    /**
     * Gets a pointer to the current editable item text.
     *
     * @return a pointer to the editable item text
     * @remarks
     * @see
     */
    IMPORT_C TPtrC ItemText();

    /**
     * Creates the Listbox editor inside the specified container.
     * The editor occupies the rectangle <code>aRect</code> and is used to
     * edit the contents of the item at index <code>aItemIndex</code> up to
     * a maximum number of <code>aMaxLength</code> characters.
     *
     * @param aContainer The Listbox in which the editor is created
     * @param aRect The editor's rectangle
     * @param aItemIndex The index of the item to edit
     * @param aMaxLength The maximum number of characters
     * @remarks
     * @see
     */
    IMPORT_C void StartEditingL(const CCoeControl& aContainer, const TRect& aRect, TInt aItemIndex, TInt aMaxLength );

	/**
     * Creates the Listbox editor inside the specified container.
     * The editor occupies the rectangle <code>aRect</code> and is used to
     * edit the contents of the item at index <code>aItemIndex</code> up to
     * a maximum number of <code>aMaxLength</code> characters.
     *
     * @param aContainer The Listbox in which the editor is created
     * @param aRect The editor's rectangle
     * @param aItemIndex The index of the item to edit
     * @param aMaxLength The maximum number of characters
	 * @param aMargins The margins that will be used for the CEikEdwin instance
	 * created by this function.
     * @remarks
     * @see
     */
    IMPORT_C void StartEditingL(const CCoeControl& aContainer, const TRect& aRect, TInt aItemIndex, TInt aMaxLength, TMargins8 aMargins);

    /**
     * Stops editing and deletes the item editor.
     *
     * @remarks
     * @see
     */
    IMPORT_C void StopEditingL();

    /**
     * Updates the Listbox model with the new item contents.
     *
     * @return <code>ETrue</code> if successful; <code>EFalse</code> if 
     *         editing is not currently on
     * @remarks
     * @see
     */
    IMPORT_C TBool UpdateModelL();

    //** Methods from base classes */

    /**
     * Offers a key event.
     * If an observer exists, it is given the chance to intercept the key
     * events before they are given to the editor, or even prevent them
     * reaching the editor entirely.
     *
     * @param aKeyEvent The key event
     * @param aType The event type
     * @return indicates whether the key was consumed
     * @remarks
     * @see CCoeControl
     */
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

protected: //** Methods */

    //** New Methods */

    /**
     * Deletes this editor.
     */
    IMPORT_C void Release();

    /**
     * Gets the Listbox model.
     * 
     * @return the Listbox model
     */
    IMPORT_C MListBoxModel* ListBoxModel();

    /**
     * Gets the item index.
     * 
     * @return the item index
     */
    IMPORT_C TInt ItemIndex() const;

    /**
     * From CCoeControl
     * Overriding the equivalent function in CCoeControl
     * 
     * @return The number of component controls contained by this control.
     */
    IMPORT_C TInt CountComponentControls() const;

    /**
     * From CCoeControl
     * Overriding the equivalent function in CCoeControl
     * 
     * @param aIndex The index of the control to get.
     * @return The component control with an index of aIndex.
     */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

    /**
     * Writes the internal state of the control and its components to aStream.
     * Does nothing in release mode.
     * Designed to be overidden and base called by subclasses.
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:
    struct SExtra
        {
        CEikEdwin* iEditor;
        CListBoxExt* iListBoxExt; // this pointer does not own anything
        };

private: //** Methods */
    IMPORT_C void MEikListBoxEditor_Reserved_1();
    void UseFontL( CEikEdwin& editor, const CFont& aFont );
    TPtrC EditableItemText(TRect* aRect=NULL);
    void DoStopEditing();

private: //** Data */
    MListBoxEditorObserver* iEditorObserver;
    MListBoxModel*    iModel;
    SExtra*           iExtra;
    TInt              iItemIndex;
    CFont*            iFont;
    TInt              iItemPos;
    TInt              iItemLen;
    CParaFormatLayer* iParaFormatLayer;
    CCharFormatLayer* iCharFormatLayer;
    };


#endif //** EIKLBED_H */

//** End of File */
