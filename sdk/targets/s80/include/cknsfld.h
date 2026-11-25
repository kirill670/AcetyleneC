/*
* ==============================================================================
*  Name        : cknsfld.h
*  Part of     : CKON / CKNCTL
*  Interface   : Search Field API
*  Description : Search Field control.
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

#ifndef CKNSFLD_H
#define CKNSFLD_H


// INCLUDES
#include <coecntrl.h>
#include <gulicon.h>
#include <eikgted.h>
#include <ckon.hrh>


// DATA TYPES


// FORWARD DECLARATIONS
class CCknInputFrame;
class CEikEdwin;
class CGlobalText;
class CEikLabel;
class CCoeBrushAndPenContext;

// CLASS DECLARATIONS

/**
 * The <code>CCknSearchField</code> class implements a Search Field control. 
 * There are four different styles for the Search Field. These are defined by 
 * a <code>TSearchFieldStyle</code>. A Search Field is a specialized input 
 * frame targeting search functionality. Variants are provided for text string,
 * URL, phone number, or generic (plain) text input tasks. It contains a 
 * <code>CEikEdwin</code> editor, which forms the input frame, an 
 * optional icon, and an optional info text label.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknSearchField : public CCoeControl, public MCoeControlObserver
{
    public:  // Declarations
    /** 
     * The <code>TSearchFieldStyle</code> enumeration specifies the default 
     * icon assigned to the Search Field. */
    enum TSearchFieldStyle 
        {
        /** the associated spy glass icon */
        ESearch = ESearchFieldStyleSearch,
        /** the associated pencil and character 'A' icon */
        EInput = ESearchFieldStyleInput,
        /** the associated globe icon */
        EUrl = ESearchFieldStyleUrl,
        /** no associated icon */
        EPhone = ESearchFieldStylePhone,
        /** no associated icon */
        EPlain = ESearchFieldStylePlain
        };
    public:
        /**
        * The object destructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C ~CCknSearchField(); 
        /**
        * Starts the two-phase object construction. 
        *
        * @param aParent The reference to the parent control
        * @param aFieldStyle Defines the UI style
        * @param aIcon A pointer to the icon to be shown in the Search Field 
        *              frame. Takes ownership. Can be <code>NULL</code>
        * @param aTextLimit Defines the maximum text length
        * @return a pointer to the Search Field object
        * @remarks If <code>aIcon</code> is <code>NULL</code>, the 
        *          <code>SearchFieldStyle</code> is used to determine the icon.
        *          Otherwise, the developer-supplied icon is used
        * @see
        */
        IMPORT_C static CCknSearchField* NewL(const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit);
        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        CCknSearchField(); 
    // New methods
        
        /**
        * Constructs a Search Field from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>SEARCHFIELD</code>.
        *          The <code>type</code> does not change if the 
        *          <code>bitmap</code> is defined
        * @see CCoeControl
        */
        void ConstructFromResourceL(TResourceReader& aReader);
        /**
        * Returns the <code>CEikEdwin</code> editor object.
        *
        * @return a pointer to the Edwin object
        * @remarks The edit window of a Search Field is a 
        *          <code>CEikEdwin</code>
        * @see eikedwin.h
        */
        IMPORT_C CEikEdwin* Editor() const;
        /**
        * Returns the length of the search text.
        *
        * @return the search text length
        * @remarks
        * @see
        */
        IMPORT_C TInt TextLength() const;
        /**
        * Returns the text of Search Field by writing it into the buffer 
        * <code>aSearchText</code>.
        *
        * @param aSearchTxt A reference to the text buffer. The buffer size 
        *                   must be the same or greater than the maximum text 
        *                   length, which is given in the constructor, 
        *                   <code>NewL()</code>
        * @remarks If the buffer size is insufficient, the current thread panics
        *          and the application terminates 
        * @see
        */
        IMPORT_C void GetSearchText(TDes& aSearchTxt) const;    
        /**
        * Sets the text into the Search Field.
        *
        * @param aSearchTxt A reference to the text buffer
        * @remarks This method may leave if the reserved buffer space is 
        *          insufficient
        * @see
        */
        IMPORT_C void SetSearchTextL(const TDesC& aSearchTxt);  
        /**
        * Selects the whole search text.
        *
        * @remarks
        * @see
        */
        IMPORT_C void SelectSearchTextL();                      
        /**
        * Clears the text in the Search Field.
        *
        * @remarks
        * @see
        */
        IMPORT_C void ResetL();         
        /**
        * Sets info text in the Search Field. This is the text that,
        * when added, is displayed between the icon and the Search Field.
        *
        * @param aText The text to be set to the Search Field
        * @remarks
        * @see
        */
        IMPORT_C void SetInfoTextL(const TDesC& aText);
        /**
        * Calls the Edwin control's <code>ClipboardL()</code> method.
        *
        * @param aClipboardFunc The clipboard function, for example, cut, copy,
        *                       paste, or no clipboard
        * @remarks The editor is a <code>CEikEdwin</code> that supports 
        *          clipboard functionality. This method gives Search Field access 
        *          to the functionality
        * @see
        */
        IMPORT_C void ClipboardL(CEikEdwin::TClipboardFunc aClipboardFunc);
    // Methods from base classes

        /**
        * Handles an event from an observed control.
        *
        * @param aControl The control
        * @param aEventType The event type
        * @remarks
        * @see coecobs.h for both MCoeControlObserver and TCoeEvent 
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        /**
        * Gets the minimum size for the Search Field.
        * 
        * @return the minimum size of the Search Field
        * @see CCoeControl
        * @remarks The size of a Search Field can be set in several ways - 
        *          either via <code>widthinchars</code> in the .rss file or by 
        *          setting <code>SetRect()</code>. To determine the width in 
        *          characters using <code>MinimumSize()</code> the developer
        *          must determine the font size and perfom a calculation
        */
        IMPORT_C TSize MinimumSize();
    private: //Methods
        TInt MinHeight();
        TRect InnerRect() const;
        TMargins Borders() const;
        void Draw(const TRect& aRect) const;
        void DrawBorder(CWindowGc& aGc, TRect& aRect) const;
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void SizeChanged();
        void FocusChanged(TDrawNow aDrawNow); 
        void ConstructL(const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit);
        void ConstructL(TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit, TInt aWidthInChars);
    private:     // Data
        CEikEdwin* iEditor;
        CGlobalText* iGlobalText;
        CGulIcon* iIcon;
        CEikLabel* iInfoText;
        CCoeBrushAndPenContext* iBrushAndPenContext;
    };


#endif      // CKNSFLD_H   
            
// End of File
