// EIKLBED.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
   
#if !defined(__EIKLBED_H__)
#define __EIKLBED_H__

#include <e32base.h>
#include <eiklbm.h>
#include <w32std.h>
#include <coedef.h>
#include <coecntrl.h>

class CCoeControl;
class CEikEdwin;
class CListBoxExt;
class CParaFormatLayer;
class CCharFormatLayer;

/**
 *
 * List box text editor interface.
 *
 * The class specifies an interface to a text editor which can be used
 * inside a list box.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class MEikListBoxEditor
	{
public:
	/**
	 * Gets a pointer to the current editable item text.
	 *
	 * @returns   "	TPtrC	"
	 *            Pointer to the editable item text.
	 */
	virtual TPtrC ItemText() = 0;

	/**
	 * Creates the editor inside the specified list box container.
	 *
	 * The editor occupies the rectangle <code>aRect</code> and is used to
	 * edit the contents of the item at index <code>aItemIndex</code> up to a
	 * maximum number of <code>aMaxLength</code> characters..
	 *
	 * @param     "	const CCoeControl& aContainer	"
	 *            List box within which the editor is created.
	 * @param     "	const TRect& aRect	"
	 *            Editors rectangle.
	 * @param     "	TInt aItemIndex	"
	 *            Index of the item to edit.
	 * @param     "	TInt aMaxLength	"
	 *            Maximum number of characters.
	 */
	virtual void StartEditingL(const CCoeControl& aContainer,const TRect& aRect,TInt aItemIndex,TInt aMaxLength) = 0;

	/**
	 * Stops editing and deletes the item editor.
	 */
	virtual void StopEditingL() = 0;

	/**
	 * Updates the list box model with the new item contents.
	 *
	 * @returns   "TBool"
	 *            <code>ETrue</code> if successful, <code>EFalse</code>
	 *            if editing is not currently on.
	 */
	virtual TBool UpdateModelL() = 0;

	/**
	 * Deletes the editor.
	 */
	virtual void Release() = 0;
private:
	IMPORT_C virtual void MEikListBoxEditor_Reserved_1();
	};

/**
 *
 * Handles a change in the position or size of the screen area occupied
 * by the status pane.
 *
 * This may be as a result of changes in layout or visibility and usually
 * requires other screen furniture and the top level control to be
 * redrawn.
 *
 */
class MListBoxEditorObserver
	{
public:
	/**
	 * Handles a list box editor event.
	 *
	 * @param     "	MEikListBoxEditor* aListBoxEditor	"
	 *            The list box editor for which the key event is
	 *            handled.
	 * @param     "	const TKeyEvent& aKeyEvent	"
	 *            The key event to handle.
	 * @returns   "	TKeyResponse	"
	 *            The response to the key event.
	 */
	virtual TKeyResponse HandleListBoxEditorEventL(MEikListBoxEditor* aListBoxEditor, const TKeyEvent& aKeyEvent)=0;
	};

/**
 *
 * Text list box item editor.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikListBoxTextEditor : public CCoeControl, public MEikListBoxEditor
	{
public:
	IMPORT_C CEikListBoxTextEditor(MListBoxModel* aModel);
	IMPORT_C ~CEikListBoxTextEditor();
	IMPORT_C void SetFont(const CFont* aFont);
	IMPORT_C CEikEdwin* Editor();
	IMPORT_C void SetListBoxEditorObserver(MListBoxEditorObserver* aObserver);
public: // from MEikListBoxEditor
	IMPORT_C TPtrC ItemText();
	IMPORT_C void StartEditingL(const CCoeControl& aContainer, const TRect& aRect, TInt aItemIndex, TInt aMaxLength );
	IMPORT_C void StopEditingL();
	IMPORT_C TBool UpdateModelL();
	IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
protected: // from MEikListBoxEditor
	IMPORT_C void Release();
protected:
	IMPORT_C MListBoxModel* ListBoxModel();
	IMPORT_C TInt ItemIndex() const;
protected: // from CCoeControl
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
private: // from MEikListBoxEditor
	IMPORT_C void MEikListBoxEditor_Reserved_1();
protected:
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	struct SExtra
		{
		CEikEdwin* iEditor;
		CListBoxExt* iListBoxExt; // this pointer does not own anything
		};
private:
	void UseFontL( CEikEdwin& editor, const CFont& aFont );
	TPtrC EditableItemText(TRect* aRect=NULL);
	void DoStopEditing();
private:
	MListBoxEditorObserver* iEditorObserver;
	MListBoxModel*  iModel;
	SExtra*			iExtra;
	TInt            iItemIndex;
	CFont*          iFont;
	TInt			iItemPos;
	TInt			iItemLen;
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	};

#endif
