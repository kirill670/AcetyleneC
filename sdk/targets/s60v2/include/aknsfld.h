/*
* ============================================================================
*  Name     : AknSfld.h
*  Part of  : Avkon
*
*  Description:
*  Search Field support. 
*
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __AKNSFLD_H__
#define __AKNSFLD_H__

#include <coecntrl.h>
#include <gulicon.h>
#include <eikgted.h>

class CEikEdwin;
class CGlobalText;
class CAknInputFrame;
class CAknSearchFieldIndicator;
class CAknsListBoxBackgroundControlContext;
class CAknsFrameBackgroundControlContext;
class CEikListBox;

/**
 * The CAknSearchField class implements a
 *
 * Search field control. There are four different styles for the search field
 * defined by a TSearchFieldStyle.
 *
 */
class CAknSearchField : public CCoeControl,
                        public MCoeControlObserver,
                        public MEikCommandObserver
{
public:
    enum TSearchFieldStyle 
        {
        ESearch, // Use only ESearch in Series 60
        EInput,     
        EUrl,           
        EPhone,
        EPlain,
        EPopup, // Use as popup search field
        EPinb,   // Use as pinb search field
        EClockApp, // for Clock application/list_single_heading_pane
        EFixed,    // same as ESearch, but using CreateWindowL().
        ESearchWithoutLine, // odd layout where no line is used
        EPopupWindow
        };
public:
    IMPORT_C ~CAknSearchField();
    IMPORT_C static CAknSearchField* NewL(const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit);
public:                 // for search string manipulation
    IMPORT_C TInt TextLength() const;
    IMPORT_C void GetSearchText(TDes& aSearchTxt) const;
    IMPORT_C void SetSearchTextL(const TDesC& aSearchTxt);
    IMPORT_C void SelectSearchTextL();
    IMPORT_C void ResetL();
    IMPORT_C void SetInfoTextL(const TDesC& aText);
    IMPORT_C void ClipboardL(CEikEdwin::TClipboardFunc aClipboardFunc);
public: // new methods for Avkon Skins support
    IMPORT_C void SetSkinEnabledL( const TBool aEnabled );
public: // from MCoeControlObserver
    void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public: // From CCoeControl
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    IMPORT_C TSize MinimumSize();
public:
    /** Sets position of the line on main pane
     *
     * @param aLinePos The position as defined in TAknSeparatorLinePos
     */
    IMPORT_C void SetLinePos(TInt aLinePos);

    /*
    * Access to the edwin owned by the search field.
    * @since 2.6
    * @return Reference to the edwin owned by the search field.
    */
    IMPORT_C CEikEdwin& Editor() const;

private: // from MObjectProvider
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    void SizeChanged();
    void FocusChanged(TDrawNow aDrawNow);
private:
    void ConstructL(const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit);
    CAknSearchField(); 
private:
    void ZoomEditorL();
private: // from MEikCommandObserver
    IMPORT_C void ProcessCommandL(TInt aCommandId);

private:
    void UpdatePopupCBAL();
    void RestorePopupCBA();
public:
    void SetListbox(CEikListBox* aListBox);
    void SetParentCtrl(CCoeControl* aParent);
    TBool IsPopup();

private:
    CEikEdwin* iEditor;
    CGlobalText* iGlobalText;
    CAknInputFrame* iInputFrame;
    CAknSearchFieldIndicator* iIndicator; 
    CAknsListBoxBackgroundControlContext* iSkinContext;
    TBool iUseSkinContext;
    TInt iLinePos;
    CAknsFrameBackgroundControlContext* iInputContext;
    TBool iIsPopup;
    TBool iCBAObserverUpdated;
    CEikListBox *iListBox; // not owned
    CCoeControl *iParent; // not owned
    };

#endif


