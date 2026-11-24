/*
* ============================================================================
*  Name        : AknMessageQueryControl.h
*  Part of     : UI Framework Core / AVKON
*  Description : Implementation of the interface to control message queries,
*                to be contained within CAknMessageQueryDialog
*  Version     : %version: e003sa01#25 %
*
*  Copyright  2002-2007 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef AKNMESSAGEQUERYCONTROL_H
#define AKNMESSAGEQUERYCONTROL_H

// INCLUDES

#include <akncontrol.h>
#include <aknutils.h>

// FORWARD DECLARATIONS

class CEikEdwin;
class CEikScrollBarFrame;
class CEikRichTextEditor;
class CRichText;

enum TMsgQueryTag
    {
    EMsgQueryLink = 0,
    EMsgQueryBold
    };


// CLASS DECLARATION

/**
*  Interface to control to implement message queries,
*  to be contained within @c CAknMessageQueryDialog.
*
*  
*/
NONSHARABLE_CLASS(CAknMessageQueryControl) : public CAknControl
    {
public:

    /**
    * C++ default constructor.
    */
    CAknMessageQueryControl();

    /**
    * Destructor.
    */
    ~CAknMessageQueryControl();

    /**
    * Constructs controls from a resource file.
    * @param aReader The resource reader with which to access
    * @c AVKON_MESSAGE_QUERY resource.
    */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

    /**
    * Sets the message text.
    * @param aMessage Message text.
    */
    IMPORT_C void SetMessageTextL( TDesC* aMessage );

    /**
    * Gets the number of lines.
    * @return Number of lines.
    */
    inline TInt Lines() const;

    /**
    * Handles key events.
    * @param aKeyEvent The key event.
    * @return Indicates whether or not the key event was used by this control.
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode );

    /**
    * Formats message text with links and bold text.
    * To be called from @c CAknMessageQueryDialog.
    *
    * @param  aFormatTextArray          Pointer to text to be formatted
    * @param  aFormatTextLocationArray  Start index of the text
    * @param  aFormatTypeArray          Format type
    *
    * 
    */
    void SetMessageTextWithFormattingL(
        TDesC* aMessage,
        RArray<TDesC*>* aFormatTextArray,
        RArray<TInt>* aFormatTextLocationArray,
        RArray<TMsgQueryTag>* aFormatTypeArray );

    /**
    * Fetches the current link chosen by the UI.
    * 
    * @return The index of the link or -1 if no link is chosen.
    */
    TInt CurrentLink() const;

    /**
    * Determines whether the link is highlighted.
    * 
    * @return @c ETrue if the link is highlighted.
    */
    IMPORT_C TBool LinkHighLighted() const;

    /**
    * When set, controls knows that it is in listquery dialog where
    * max. lines is 3 and background is not drawn
    */
    void SetListQLayout( TBool aListQLayout );

    /**
    * Determines if a link is tapped.
    * @param  aPos  Position of the character tapped.
    * @return @c ETrue if a link is tapped.
    * 
    */
    TBool LinkTappedL( TInt aPos );

public:  // from CCoeControl

    /**
    * From @c CCoeControl. Sets the control's minimum required size.
    * @return The minimum size required by the control.
    */
    TSize MinimumSize();

    /**
    * From @c CCoeControl. Gets the number of controls contained in
    * a compound control.
    * @return The number of component controls contained by this control.
    */
    TInt CountComponentControls() const;

    /**
    * From @c CCoeControl. Gets the specified component of a compound control.
    * It returns one of the control's component controls, identified by anIndex.
    * @param anIndex The index of the control to get.
    * @return The component control with an index of anIndex.
    */
    CCoeControl* ComponentControl( TInt anIndex ) const;

    /**
    * From @c CCoeControl. Responds to size changes to sets the size and
    * position of the contents of this control.
    */
    void SizeChanged();

    /**
    * From @c CCoeControl. Sets control as ready to be drawn.
    * This function calls @c CCoeControl::ActivateL().
    */
    virtual void ActivateL();

    /**
    * From @c CCoeControl. Handles pointer events
    * 
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private:
    void UpdateScrollIndicatorL();

    /**
    * Highlights or dehighlights the current link with proper font decoration.
    */
    void SetHighlightOnL( TBool aOn );

    /**
    * Returns if it is possible to scroll one page in the specified direction.
    * @arg aMoveDown The scroll direction is down, if ETrue.
    */
    TBool CanScrollPage( TBool aMoveDown );

    TBool IsLinkVisible( TInt aIndex ) const;  
        
    /**
    * Updates information about the current page:
    * - visible links
    * - cursor positions.
    * The visible links are fetched from the links array.
    * Number of cursor positions is calculated on the basis of visible links.
    * Sets variables: iVisibleLinksCount, iFirstVisibleLink, iPositionsCount
    */
    void UpdatePageInfo();

    /*
    *  Initialisation functions
    */
    void CreateEditorL();
    void LayoutEditorL();

private:
    /*
    * changed editor from CEikEdwin to CEikRichTextEditor
    * 
    */
    CEikRichTextEditor* iEdwin;
    TInt iNumberOfLines;    // Number of lines in the document
    TInt iTopLine;    // Index of the top visible line on the current page, zero-based
    TInt iLinesPerPage; // Number of lines in one page

    CEikScrollBarFrame* iSBFrame;
    TBool iListQLayout; // If ETrue, used by listqueryDialog

    //@since 2.8
    // with link extension introduced
    TBool iHighlightOn; // The current position is a link
    TCharFormatMask iCharFormatMask;
    TCharFormat iCharFormat;

    //@since 3.0
    // with multiple link support
    RArray<TInt> iLinkTextLocationArray;    // Link positions; sorted
    RArray<TDesC*> iLinkTextArray;  // Link texts; in sync with iLinkTextLocationArray w.r.t. item order
    TInt iLinksCount;   // Number of all links in the document
    TInt iVisibleLinksCount;    // Number of visibile links on the current page. Updated in UpdatePageInfo().
    TInt iFirstVisibleLink; // Index of the first visible link, zero-based. Updated in UpdatePageInfo().
    
    /** Cursor positions are places on the current page, where a virtual
    * cursor can stop.
    * The positions are considered visible links plus top and bottom of the page.
    * Position indexes are zero-based. If there are no visible links,
    * there is only one cursor position with index 0.
    */
    TInt iPositionsCount;   // Number of cursor positions on the current page. Updated in UpdatePageInfo().
    TInt iCurPos;   // Current cursor position on the current page, zero-based

protected:
    /**
    * From @c CCoeControl. Draw a control.
    * 
    * @param aRect The region of the control to be redrawn. Not used.
    */
    IMPORT_C void Draw( const TRect& aRect ) const;


protected:
    /**
    * Get a layout rectangle (shift up and left by margins).
    * 
    * @return The layout rectangle.
    */
    TRect LayoutRect() const;
    };

inline TInt CAknMessageQueryControl::Lines() const
    {
    return iNumberOfLines;
    }

// AKNMESSAGEQUERYCONTROL_H
#endif

// End of file
