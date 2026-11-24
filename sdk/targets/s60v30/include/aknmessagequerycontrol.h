/*
* ============================================================================
*  Name     : aknmessagequerycontrol.h
*  Part of  : AVKON
*
*  Description:
*  Interface to control to implement message queries, 
*  to be contained within CAknMessageQueryDialog
* 
*  Version:
*
*  Copyright © 2002, 2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*/

#ifndef AKNMESSAGEQUERYCONTROL_H
#define AKNMESSAGEQUERYCONTROL_H

// INCLUDES

#include <AknControl.h>
#include <aknutils.h>

// FORWARD DECLARATIONS

class CEikEdwin;
class CEikScrollBarFrame;
class CEikRichTextEditor;
class CRichText;

// CLASS DECLARATION

/**
*  Interface to control to implement message queries, 
*  to be contained within @c CAknMessageQueryDialog.
*
*  @since Series 60 0.9
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
    
    //@since 3.0
    /**
    * Sets the message text with link. 
    * @since Series 60 3.0
    * @param aMessage Message text.
    * @param aLinkText Link text. 
    * @param aLinkTextLocation location of links in the text.
    */
    void SetMessageTextWithLinksL( TDesC* aMessage, RArray<TDesC*>* aLinkTextArray, 
        RArray<TInt>* aLinkTextLocationArray );
        
    //@since 3.0
    /**
    * Fetches the current link chosen by the UI.
    * @since Series 60 3.0
    * @return The index of the link.
    */
    TInt CurrentLink() const;

    /**
    * Determines whether the link is highlighted.
    * @since Series 60 2.8
    * @return @c ETrue if the link is highlighted.
    */
    TBool LinkHighLighted();

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
    * @since Series 60 3.0
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    
private:
    void CalculateNumberOfScreens();
    void UpdateScrollIndicatorL();

    //@since 2.8
    void SetHighlightOnL( TBool aOn );   
    TBool IsLinkVisible( TInt aIndex ) const;    
    
    //@since 3.0
    
    /*
    *  Fetches the visible links from the links array
    */
    void CountCurrentVisible();

    /*
    *  Moves between visible links on the screen
    */
    TBool FirstVisible();    
    TBool LastVisible();
    TBool NextVisible();
    TBool PreviousVisible();
    
    
private:
    //@since 2.8
    //changed editor from CEikEdwin to CEikRichTextEditor
    //CEikEdwin* iEdwin;
    CEikRichTextEditor* iEdwin;
    TInt iNumberOfLines;
    TInt iCurrentScreen;
    TInt iNumberOfScreens;

    CEikScrollBarFrame* iSBFrame;
    TInt iSpare;   // Not in use.

    //@since 2.8
    // with link extension introduced 
    TBool iHighlightOn;
    TBool iHLBeforePrevScrollDown;
    TBool iHLBeforePrevScrollUp;
    TCharFormatMask iCharFormatMask;
    TCharFormat iCharFormat;
    
    //@since 3.0
    // with multiple link support 
    RArray<TInt>* iLinkTextLocationArray; // not owned
    RArray<TDesC*>* iLinkTextArray; // not owned
    RArray <TInt> iVisibleLinkArray;
    TInt iCurrentLink;
    TInt iLinkCount;
    
protected:
    /**
    * From @c CCoeControl. Draw a control.  
    * @since Series 60 2.0
    * @param aRect The region of the control to be redrawn. Not used.
    */
    IMPORT_C void Draw( const TRect& aRect ) const;


protected:
    /**
    * Get a layout rectangle (shift up and left by margins).
    * @since Series 60 2.6
    * @return The layout rectangle. 
    */
    TRect LayoutRect() const;
    };

inline TInt CAknMessageQueryControl::Lines() const
    {
    return iNumberOfLines;
    }

#endif // AKNMESSAGEQUERYCONTROL_H

// End of file
