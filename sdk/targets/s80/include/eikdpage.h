/*
* ==============================================================================
*  Name        : eikdpage.h
*  Part of     : CKON
*  Interface   : Dialog Base API
*  Description : Dialog page class.
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

#ifndef EIKDPAGE_H
#define EIKDPAGE_H


// INCLUDES
#include <coeccntx.h>
#include <eikscrlb.h>
#include <coecobs.h>
#include <eikedwob.h>


// FORWARD DECLARATIONS
class CEikCapCArray;
class CEikCaptionedControl;
class CEikDialogPageContainer;
class CEikEdwin;
class CEikLabel;
class TEikLabelColors;
class MEikDialogPageObserver;
struct SEikControlInfo;
class CCknSkinBase;

// CLASS DECLARATIONS

/**
* The CEikDialogPage class implements a scrollable dialog page control.
* @internal
*
* Link against EikDlg.lib
* @since Series90 1.0
*/
class CEikDialogPage : public CCoeControl, public MCoeControlObserver, public MEikScrollBarObserver, public MEikEdwinSizeObserver
    {

    public:  // Declarations

        enum TFocusNavigationMode
            {
            ECyclic,
            ENonCyclic
            };

    private:  // Declarations

        enum TFlag
            {
            EWindowsSizedForScrollBar=0x0001
            };

    public:

    // Constructors and destructor

        /**
        * Destructor.
        */
        ~CEikDialogPage();

        /**
        * Static constructor.
        */
        static CEikDialogPage* NewL(TInt aId,RWindow& aViewWin,CEikScrollBar& aScrollBar,const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);
        static CEikDialogPage* NewLC(TInt aId,RWindow& aViewWin,CEikScrollBar& aScrollBar,const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);
        static CEikDialogPage* NewL(TInt aId,RWindow& aViewWin,CEikScrollBar& aScrollBar,const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader);
        static CEikDialogPage* NewLC(TInt aId,RWindow& aViewWin,CEikScrollBar& aScrollBar,const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader);

    // New methods
        
        void SetDataPosition(TInt aPosition);
        TSize PreferredSize(TBool aForTallestControlOnly) const;
        void SetControlWidth(const TInt aWidth);
        void SetActiveL();
        void SetInactiveL();
        TInt PageId() const;
        TInt LineId(const CCoeControl& aControl) const;
        TBool SetInitialFocus();
        CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue);
        void SetControlCaptionL(TInt aLineId,const TDesC& aText);
        void SetControlCaptionL(TInt aLineId,TInt aResourceId);
        CCoeControl* Control(TInt aLineId) const;
        CCoeControl* ControlOrNull(TInt aLineId) const;
        TInt ControlHeight(TInt aLineIndex) const;
        CEikCaptionedControl* Line(TInt aLineId) const;
        CEikCaptionedControl* LineOrNull(TInt aLineId) const;
        CEikCaptionedControl* CurrentLine() const;
        void SetDensePacking(TBool aDensePacking);
        void InsertLineL(TInt aPosition,TInt aResourceId);
        void DeleteLine(TInt aLineId);
        void AdjustAllIds(TInt aControlIdDelta);
        TInt FocusLineL(TInt aLineId);
        TInt FocusedLineId() const;
        void GetAutoValues();
        TKeyResponse OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TFocusNavigationMode aFocusNavigationMode,TBool& aJustScrolled);
        TBool OwnsLine(TInt aLineId) const;
        void ResetLineMinimumSizes();
        TInt FindLineIndex(CCoeControl* aControl) const;
        TBool RotateFocusByL(TInt aDelta);
        TKeyResponse OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        TBool TakesEnterKey();
        TInt LineIndex(TInt aLineId);
        void ReportPageChangedL();
        void SetInternalMargins(TMargins8 aMargins);
        TBool NeedsClipboardSupport() const;
        TBool CurrentLineIsTopFocusableLine() const;

    // Methods from base classes

        TSize MinimumSize();
        virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
        virtual void HandleResourceChange(TInt aType);
        virtual void PrepareForFocusLossL();
        virtual void SetDimmed(TBool aDimmed);
        virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        virtual TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize);

    protected:  // Methods

    // Methods from base classes

        void SizeChanged();
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void FocusChanged(TDrawNow aDrawNow);
        virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);

    private: //Methods

    // Methods from base classes

        void Reserved_1();
        void Reserved_2();

    // New methods

        CEikDialogPage(TInt aId,RWindow& aViewWin,CEikScrollBar& aScrollBar,MEikDialogPageObserver* aPageObserver);
        void ConstructL();
        void ConstructFromResourceL(TResourceReader& aReader);
        void ConstructByTypeL(TInt aControlType,CEikCaptionedControl* aLine,CCoeControl* aContainer);
        void ShowFocus(TBool aFocus);
        SEikControlInfo CreateCustomControlL(TInt aControlType);
        void ChangeFocusTo(TInt aLineIndex);
        void PrepareForFocusTransitionL();
        TInt IdOfFocusControl() const;
        void CheckNonFocusingState(CCoeControl* aControl);
        void UpdateScrollBarL();
        void ChangeFocusToAndExposeL(TInt aLine);
        TInt TopFocusableLine() const;
        TInt BottomFocusableLine() const;
        TBool LineIsFocusable(TInt aLine) const;
        void ResizeEdwinToFitTextL(CEikEdwin* aEdwin, TDrawNow aDrawNow, TSize aDesirableEdwinSize);
        TSize SizeDeltaOfEdwinBorderPlusMargins(CEikEdwin* aEdwin) const;
        TInt YPosToLine(TInt& aYPos) const;
        TInt LineToYPos(TInt& aLine) const;
        void ExposeLine(TInt aLine);
        void SetDataWinSize();
        void PassOnEventL(CCoeControl* aControl,MCoeControlObserver::TCoeEvent aEvent);
        CEikCaptionedControl* ConstructLineL(TInt aResourceId,CCoeControl* aPrevious);
        CEikCaptionedControl* ConstructLineL(TResourceReader& aReader,CCoeControl* aPrevious);
        void ConstructLineL(TResourceReader& aReader,CEikCaptionedControl* aLine);
        TKeyResponse HandleCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent,TBool& aJustScrolled);
        TKeyResponse HandleNonCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent,TBool& aJustScrolled);
        void MakeEdwinScrollbarsVisibleL(TBool aVisible);
        TBool Flag(TFlag aFlag) const;
        void SetFlag(TFlag aFlag);
        void ClearFlag(TFlag aFlag);
        void LineChangedL(TInt aControlId);
        void AdjustLayoutForScrollBar();
        void ScrollUp(TBool aPageUp);
        TBool ScrollDown(TBool aPageDown);
        void ModifyControlL(TInt aType, CEikCaptionedControl* aLine);
		void AdjustDialogLabelsForScrollBar(TInt aScrollBarWidth);
			// To adjust the wrapping widths of the dialog labels for scroll bar

    private:     // Data

        RWindow& iViewWin;
        CEikScrollBar& iScrollBar;
        CEikCapCArray* iLines;
        MEikDialogPageObserver* iPageObserver;
        TInt iPageId;
        TInt iCurrentLine;
        TPoint iViewWinPos;
        TSize iViewWinSize;
        TPoint iDataWinPos;
        TSize iDataWinSize;
        TInt iFlags;
        TInt iSpaceFromTitle;
        TInt iSpaceFromBottom;
        CEikLabel::TEikLabelColors* iLabelColors;
        CCknSkinBase& iSkin;
    };

/**
* The CEikDialogPageContainer class contains one or more dialog pages and
* provides an interface to the active page.
* @internal
*
* Link against EikDlg.lib
* @since Series90 1.0
*/
class CEikDialogPageContainer : public CCoeControl, public MCoeControlContext
    {
    public:

    // Constructors and destructor

        ~CEikDialogPageContainer();
        static CEikDialogPageContainer* NewL(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);
        static CEikDialogPageContainer* NewLC(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);

    // New methods
        
        TSize PreferredSize(const TSize& aMaxSize, TBool aForTallestControlOnly) const;
        void SetActivePageByIdL(TInt aPageId);
        void SetActivePageByIndexL(TInt aPageIndex);
        TInt ActivateFirstPageL();
        void AddPageL(TInt aPageId);
        void AddPageL(TInt aPageId,TResourceReader& aReader);
        TBool SetInitialFocus();
        CEikCaptionedControl* Line(TInt aLineId) const;
        CEikCaptionedControl* LineOrNull(TInt aLineId) const;
        CEikCaptionedControl* CurrentLine() const;
        void SetPageDensePacked(TInt aPageId,TBool aDensePacked);
        void SetAllPagesDensePacked(TBool aDensePacked);
        void SetPageDimmed(TInt aPageId,TBool aDimmed,TDrawNow aDrawNow);
        TBool IsActivePageDimmed() const;
        TInt LineId(const CCoeControl& aControl) const;
        void InsertLineL(TInt aPosition,TInt aPageId,TInt aResourceId);
        void DeleteLine(TInt aLineId);
        void AdjustAllIds(TInt aPageId,TInt aControlIdDelta);
        CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue);
        CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aLineId,TInt aControlType,TAny* aReturnValue);
        TInt FocusLineL(TInt aLineId);
        TInt FocusedLineId() const;
        void GetAutoValues();
        TKeyResponse OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,CEikDialogPage::TFocusNavigationMode aFocusNavigationMode,TBool& aJustScrolled);
        TInt ActivePageId() const;
        TInt ActivePageIndex() const;
        void ResetLineMinimumSizes();
        TInt FindLineIndex(const CCoeControl& aControl) const;
        TBool RotateFocusByL(TInt aDelta);
        TInt NumPages() const;
        TKeyResponse OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        TBool TakesEnterKey();
        TInt FindPageIndexForLineId(TInt aLineId);
        void SetInternalMargins(TMargins8 aMargins);
        TBool NeedsClipboardSupport() const;
        TBool CurrentLineIsTopFocusableLine() const;

    // Methods from base classes

        virtual void Draw(const TRect& aRect) const;
        virtual TSize MinimumSize();
        virtual void PrepareForFocusLossL();
        virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        void HandleResourceChange(TInt aType);
        virtual void PrepareContext(CWindowGc& aGc) const;

    protected:  // Methods

    // Methods from base classes
        
        virtual void SizeChanged();
        virtual TInt CountComponentControls() const;
        virtual CCoeControl* ComponentControl(TInt aIndex) const;
        virtual void ActivateL();
        virtual void FocusChanged(TDrawNow aDrawNow);
        virtual void Reserved_1();
        virtual void Reserved_2();

    private:

        CEikDialogPageContainer(MEikDialogPageObserver* aPageObserver);
        void SetPageL(TInt aPageId);
        void ConstructL(const CCoeControl& aParent);
        void ConstructFromResourceL(TResourceReader& aReader,const CCoeControl& aParent);
        void CommonConstructL(const CCoeControl& aParent);
        void CreatePageArrayL();
        void CreateScrollBarL(const CCoeControl& aParent);
        void CreateViewWinL(const CCoeControl& aParent);
        TInt PageIndex(TInt aPageId) const;
        TInt PageId(TInt aIndex) const;
        TInt PageIdFromLineId(TInt aLineId) const;

    private:     // Data

        RWindow* iViewWin;
        CEikScrollBar* iScrollBar;
        CArrayPtr<CEikDialogPage>* iPageArray;
        MEikDialogPageObserver* iPageObserver;
        TInt iActivePage;
        CCknSkinBase& iSkin;
    };

#endif      // EIKDPAGE_H   
            
// End of File
