/*
* =============================================================================
*  Name        : eikscrlb.h
*  Part of     : CKON
*  Interface   : Scrollbar API
*  Description : Scrollbar control and arrowhead Scrollbar control.
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

#ifndef EIKSCRLB_H
#define EIKSCRLB_H


// INCLUDES
#include <eikbctrl.h>
#include <eiksbobs.h>
#include <eikscbut.h>
#include <lafpublc.h>


// CONSTANTS
/** Scrollbar events for the vertical Scrollbar */
const TInt KEikScrollEventFromVBar=0;
/** Scrollbar events for the horizontal Scrollbar */
const TInt KEikScrollEventFromHBar=0x01;
/** Scrollbar event mask */
const TInt KEikScrollEventBarMask=0x01;

/** sets all bits in <code>EButtonsXxx</code> range */
const TInt KButtonPositionMask=KLafScrollBarButtonPositionMask; 

/** sets all bits in determining which components exist */
const TInt KDisplayComponentsMask=0x1f; 


// FORWARD DECLARATIONS
class CEikScrollButton;
class CEikScrollThumb;


// CLASS DECLARATIONS

/**
 * The <code>MEikScrollBarCustomDrawBase</code> class is a mixin interface 
 * class drawing a custom background for a Scrollbar. Controls that contain a 
 * Scrollbar need to inherit this to draw a custom background 
 * behind it. <b>Note</b>: There are no pure virtual methods in this class.
 *
 * @lib eikcoctl.lib
 * @since Series90 1.0
 */
class MEikScrollBarCustomDrawBase
    {

public:

    // New methods
        
    /**
    * The custom background draw method. Called by a Scrollbar when it 
    * requires its background to be drawn.
    *
    * @param aGc The graphics context to draw to
    * @param aRect The area to draw. The position is relative to the window
    * @remarks
    * @see
    */
    IMPORT_C virtual void DrawScrollBarBackground(CBitmapContext& aGc,
                                                  const TRect& aRect);

    /**
    * The custom background draw method. Called by a Scrollbar when it 
    * requires its background to be drawn.
    *
    * @param aGc The graphics context to draw to
    * @param aComponent The scroll component in which the background is to be 
    *                   drawn
    * @param aRect The area to draw. The position is relative to the window
    * @remarks
    * @see
    */
    IMPORT_C virtual void DrawScrollBarBackground(CBitmapContext& aGc, 
                                                  const CCoeControl* aComponent,
                                                  const TRect& aRect);
private:
    /**
    * @internal
    */
    IMPORT_C virtual void Reserved_1();

    /**
    * @internal
    */
    IMPORT_C virtual void Reserved_2();
    };

/**
 * The <code>TEikScrollBarModel</code> class provides the model for a 
 * <code>CEikScrollBar</code>. Scrollbar models encapsulate the range of 
 * integers that a Scrollbar can represent from zero to n, and the current 
 * position of the Scrollbar thumb within that range. This model also has 
 * publicly accessible data for the thumb position and span.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class TEikScrollBarModel
    {
public:

    // Constructors and destructor

    /**
    * The default object constructor.
    * Creates, allocates, and initializes a new <code>TEikScrollBarModel</code>.
    */
    inline TEikScrollBarModel();

    /**
    * The object constructor. It creates, allocates, and initializes a new 
    * <code>TEikScrollBarModel</code>.
    *
    * @param aScrollSpan The span of this model, numbered from zero
    * @param aThumbSpan The number of positions spanned by the thumb
    * @param aThumbPosition The position of the thumb within the model span
    * @remarks
    * @see
    */
    IMPORT_C TEikScrollBarModel(TInt aScrollSpan,
                                TInt aThumbSpan=0,
                                TInt aThumbPosition=0);

    // New methods
        
    /**
    * Tests two models for equality. The two models are the current 
    * model and the model specified by <code>aModel</code>.
    *
    * @param aModel The model against which the current model is tested
    * @return <code>ETrue</code> if the content of the models is the same;
    *         <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool operator==(const TEikScrollBarModel aModel) const;

    /**
    * Tests two models for inequality. The two models are the current model
    * and the model specified by <code>aModel</code>.
    *
    * @param aModel The model against which the current model is tested
    * @return <code>ETrue</code> if the content of the models is not the
    *         same; <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    inline TBool operator!=(const TEikScrollBarModel aModel) const; 

    /**
    * Tests whether the Scrollbar model is useful. Scrollbar models are 
    * only useful if their thumb span is smaller than their entire span.
    *
    * @return <code>ETrue</code> if this Scrollbar can be used; 
    *         <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool ScrollBarUseful() const;

    /**
    * Gets the maximum position possible for the low edge of the thumb within
    * the total span.
    *
    * @return the maximum value possible for <code>iThumbPosition</code>
    * @remarks
    * @see
    */
    IMPORT_C TInt MaxThumbPos() const;

    /**
    * Ensures that the thumb position remains within its valid range by 
    * altering it if necessary.
    *
    * @remarks
    * @see
    */
    IMPORT_C void CheckBounds();

public:     // Data

    /** the entire range of integers for this model */
    TInt iScrollSpan;
    /** the range spanned by the thumb */
    TInt iThumbSpan;
    /** the position of the low edge of the thumb within the scroll span */
    TInt iThumbPosition;            

    };

inline TEikScrollBarModel::TEikScrollBarModel()
    {}

inline TBool 
    TEikScrollBarModel::operator!=(const TEikScrollBarModel aModel) const 
            { return !(*this==aModel); }
  
/**
 * The <code>CEikScrollBar</code> class provides a Scrollbar.
 * Scrollbars are used when all the content of another control cannot be
 * seen at the same time. They can be oriented horizontally or
 * vertically, and can be displayed in several ways. Scrollbars represent
 * integers, and have a maximum, a minimum, and a current position
 * encapsulated within their model. The onscreen image of a Scrollbar
 * is calculated and displayed by the <code>CEikScrollBar</code> object,
 * and user changes to the Scrollbar (and hence its model) are reported
 * to an interested class through the <code>MEikScrollBarObserver</code>
 * interface.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikScrollBar : public CEikBorderedControl, public MCoeControlObserver
    {
public:  // Declarations

    /**
    * The enumeration <code>TOrientation</code> specifies the Scrollbar 
    * orientation.
    */
    enum TOrientation
        {
        /** the Scrollbar is oriented vertically */
        EVertical = SLafScrollBar::EVertical,
        /** the Scrollbar is oriented horizontally */
        EHorizontal = SLafScrollBar::EHorizontal    
        };

    /**
    * The enumeration <code>TEikScrollBarFlags</code> provides the Scrollbar 
    * initialization flags. The default is for the Scrollbar to have both a 
    * shaft and a thumb.
    */
    enum TEikScrollBarFlags
        {
        /** the default Scrollbar behavior */
        EEikScrollBarDefaultBehaviour = 
            SLafScrollBar::EEikScrollBarDefaultBehaviour,
        /** does not display nudge buttons */
        EEikScrollBarNoNudgeButtons =
            SLafScrollBar::EEikScrollBarNoNudgeButtons,
        // has buttons that move it a page at a time.
        /** not supported on S90 */
        EEikScrollBarHasPageButtons =
            SLafScrollBar::EEikScrollBarHasPageButtons,
        // has buttons that move it its entire extent.
        /** not supported on S90 */
        EEikScrollBarHasHomeEndButtons  =
            SLafScrollBar::EEikScrollBarHasHomeEndButtons,
        /** the central area is empty */
        EEikScrollBarNoShaftOrThumb = 
            SLafScrollBar::EEikScrollBarNoShaftOrThumb,
        /** the central area has no scroll thumb. The Scrollbar is scrollable 
            using the nudge buttons at either end of the Scrollbar */
        EEikScrollBarShaftButNoThumb =
            SLafScrollBar::EEikScrollBarShaftButNoThumb, 
        // the buttons are placed at the start of the Scrollbar. 
        /** not supported on S90 */
        EButtonsAtStartOfShaft =
            SLafScrollBar::EButtonsAtStartOfShaft, 
        // the buttons are placed at the end of the Scrollbar 
        /** not supported on S90 */
        EButtonsAtEndOfShaft =
            SLafScrollBar::EButtonsAtEndOfShaft, 
        // the buttons are placed at either end of the Scrollbar 
           // (<code>EButtonsAtStartOfShaft | EButtonsAtEndOfShaft</code>)
        /** not supported on S90 */
        EButtonsEitherSideOfShaft = SLafScrollBar::EButtonsEitherSideOfShaft,
        /** 
         * the nudge buttons do not automatically dim when the Scrollbar is at 
         * its maximum extent 
         */
        ENoAutoDimming = SLafScrollBar::ENoAutoDimming      
        };

protected:  // Declarations

    friend class CEikScrollBarFrame;

    /**
    * Flags to determine whether there are visible components and whether to
    * dim the increase, or decrease, buttons.
    */
    enum TPrivateScrollBarFlags
        {
        /** there are no visible components in the Scrollbar */
        ENoComponentsToDisplay = 0x10000,
        /** dim the increase nudge buttons */
        EIncreaseButtonsDimmed = 0x20000,
        /** dim the decrease nudge buttons */
        EDecreaseButtonsDimmed = 0x40000 
        };

    /**
    * Determines where on a Scrollbar a pointer down event occurred.
    */
    enum TPointerDownOn
        {
        /** No pointer down event occurred on the Scrollbar. */
        ENone, 
        /** A pointer down event occurred on the home button. */
        EHomeButton,
        /** A pointer down event occurred on the decrease page button. */
        EDecreasePageButton,
        /** A pointer down event occurred on the decrease nudge button. */
        EDecreaseNudgeButton,
        /** A pointer down event occurred on the decrease shaft button. */
        EDecreaseShaft,
        /** A pointer down event occurred on the Scrollbar thumb. */
        EThumb,
        /** A pointer down event occurred on the increase shaft button. */
        EIncreaseShaft,
        /** A pointer down event occurred on the increase nudge button. */
        EIncreaseNudgeButton,
        /** A pointer down event occurred on the increase page button. */
        EIncreasePageButton,
        /** A pointer down event occurred on the end button. */
        EEndButton
        };

    /**
    * Determines whether to redraw the Scrollbar shaft.
    */
    enum TShaftRedrawRequired
        {
        /** Do not redraw the Scrollbar shaft. */
        ENoRedrawRequired,
        /** Redraw the Scrollbar shaft. */
        ERedrawShaft
        };

    /**
    * Determines which buttons are displayed.
    */
    enum TWhichButtons
        {
        /** Display the increase nudge buttons only. */
        EIncreaseOnly,
        /** Display the decrease nudge buttons only. */
        EDecreaseOnly,
        /** Display all buttons. */
        EAll 
        };

    struct SEikScrollBarButtons
        {
        CEikScrollButton* iHome;
        CEikScrollButton* iDecreasePage;
        CEikScrollButton* iDecreaseNudge;
        CEikScrollButton* iIncreaseNudge;
        CEikScrollButton* iIncreasePage;
        CEikScrollButton* iEnd;
        };

public:

    // Constructors and destructor

    /**
    * The object destructor.
    */
    IMPORT_C ~CEikScrollBar();

    /**
    * The default object constructor.
    */
    IMPORT_C CEikScrollBar();


    // Methods from base classes
    // from CCoeControl

    /**
    * Handles a pointer event offered to the control by the control
    * environment.
    *
    * @param aPointerEvent The type of pointer event. See w32std.h for the 
    *                      event types
    * @remarks If this method is not implemented, then the 
    *          <code>CCoeControl</code>'s method is used to handle the event 
    *          for this control when a pointer event is forwarded to it
    * @see CCoeControl
    */
    IMPORT_C virtual void HandlePointerEventL(
                                    const TPointerEvent& aPointerEvent);

    /**
    * Draws the control on screen.
    *
    * @param aRect The region of the control to be redrawn
    * @remarks The method is called by the environment
    * @see CCoeControl
    */
    IMPORT_C virtual void Draw(const TRect& aRect) const;

    /**
    * Sets the control as ready to be drawn.
    *
    * @remarks There is no need to call this method if the control is 
    *          contained within another control, providing the 
    *          parent control calls its <code>ActivateL</code>. The 
    *          parent's method call results in any controls contained 
    *          within it to be drawn
    * @see CCoeControl
    */
    IMPORT_C virtual void ActivateL();

    /**
    * Used to set the control as dimmed (grayed out) and unable to receive events
    * or as undimmed. 
    *
    * @param aDimmed <code>ETrue</code> to dim the control; 
    *        <code>EFalse</code> to set the control as not dimmed
    * @remarks The method does not redraw the control. The application should 
    *          call <code>DrawNow()</code> to do so
    * @see CCoeControl
    */
    IMPORT_C virtual void SetDimmed(TBool aDimmed);

    /**
    * Gets the list of logical colors used for drawing the control. This 
    * method is no longer used. Skin functionality manages the colors for 
    * this control.
    * 
    * @param aColorUseList Not used
    * @remarks
    * @see CCoeControl
    */
    IMPORT_C virtual void GetColorUseListL(
        CArrayFix<TCoeColorUse>& aColorUseList) const; 

    /**
    * Handles a change to the resource of the application that is shared 
    * across the environment. The method is 
    * normally called by the CONE framework. It can also be called by 
    * the developer when used to change skins or other resource related 
    * items.
    * 
    * @param aType A <code>TInt</code> message UID value for the resource 
    *              that has changed
    * @remarks
    * @see CCoeControl
    */
    IMPORT_C virtual void HandleResourceChange(TInt aType); 

public: // Methods

    // New methods
        
    /**
    * Completes the construction of the Scrollbar.
    *
    * @param aScrollBarObserver The Scrollbar observer that is to be informed
    *                           of scroll events by this Scrollbar
    * @param aParent The parent control for this new Scrollbar
    * @param aOrientation The orientation of the new Scrollbar
    * @param aLength The length of the Scrollbar
    * @param aScrollBarFlags An OR-ed combination of 
    *                        <code>TEikScrollbarFlags</code>
    * @remarks
    * @see
    */
    IMPORT_C virtual void ConstructL(MEikScrollBarObserver* aScrollBarObserver,
                          const CCoeControl* aParent,
                          TOrientation aOrientation,
                          TInt aLength,
                          TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);

    /**
    * Changes the length of the onscreen Scrollbar and redraws it.
    *
    * @param aLength The new length of the Scrollbar, in pixels
    * @remarks
    * @see
    */
    IMPORT_C void SetLengthL(TInt aLength);

    /**
    * Changes the model used by this Scrollbar. The thumb is updated.
    *
    * @param aModel The new model to use
    * @remarks
    * @see
    */
    IMPORT_C void SetModelL(const TEikScrollBarModel* aModel);

    /**
    * Changes the length and model at once to avoid a double update of the
    * Scrollbar.
    *
    * @param aLength The new length
    * @param aModel The new Scrollbar model
    * @remarks
    * @see
    */
    IMPORT_C void SetLengthAndModelL(TInt aLength,
                                     const TEikScrollBarModel* aModel);

    /**
    * Changes the position within the model, and updates the onscreen image
    * of the thumb within the Scrollbar.
    *
    * @param aThumbPos The new position for the thumb within the model
    * @remarks
    * @see
    */
    IMPORT_C void SetModelThumbPosition(TInt aThumbPos);

    /**
    * Calculates the minimum length in which the Scrollbar can be drawn. 
    * This does not mean that all Scrollbar components are drawn.
    *
    * @return the default breadth of the Scrollbar
    * @remarks The default breadth is either the height of the horizontal 
    *          Scrollbar or the width of a vertical Scrollbar
    * @see
    */
    IMPORT_C static TInt DefaultScrollBarBreadth();

    /**
    * Sets the Scrollbar observer.
    *
    * @param aScrollBarObserver The Scrollbar observer
    * @remarks
    * @see
    */
    // not available before Release 005u
    inline void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver);

    /**
    * Sets the Scrollbar background custom drawer.
    *
    * @param aCustomDrawer The Scrollbar background custom drawer
    * @remarks The custom drawer is the control containing the Scrollbar.
    *          For example, if the Scrollbar is contained in a view, the 
    *          view is set as the custom drawer
    * @see
    */
    IMPORT_C void SetCustomDrawer(MEikScrollBarCustomDrawBase* aCustomDrawer);

    /**
    * Gets the Scrollbar model used by this Scrollbar.
    *
    * @return the Scrollbar model
    */
    inline const TEikScrollBarModel* Model() const;

    /**
    * Gets the position within the Scrollbar model.
    * This method is normally called by an
    * <code>MEikScrollBarObserver</code> implementation in response to a
    * Scrollbar event.
    *
    * @return the current position within the Scrollbar model's range, in pixels
    * @remarks
    * @see
    */
    IMPORT_C TInt ThumbPosition() const;

    /**
    * Gets the height of a horizontal Scrollbar, or the width of a vertical
    * Scrollbar.
    *
    * @return the Scrollbar height or width
    * @remarks
    * @see
    */
    IMPORT_C TInt ScrollBarBreadth() const;

    /**
    * Calculates the minimum length in which the Scrollbar can be drawn.
    * This does not mean that all Scrollbar components are drawn.
    *
    * @param aScrollBarFlags Flags describing a Scrollbar
    * @return the minimum visible width of the described Scrollbar
    * @remarks
    * @see
    */
    IMPORT_C static TInt MinVisibleLength(const TInt aScrollBarFlags);

    /**
    * Sets the decrease nudge button's dim state.
    * A dimmed control indicates that user input is not accepted.
    *
    * @param aDimmed <code>ETrue</code> to dim the decrease nudge buttons;
    *                <code>EFalse</code> to undim the decrease nudge buttons
    * @remarks 
    * @see
    */
    IMPORT_C void SetDecreaseButtonsDimmed(TBool aDimmed);

    /**
    * Sets the increase nudge button's dim state.
    * A dimmed control indicates that user input is not accepted.
    *
    * @param aDimmed
    *        <code>ETrue</code> to dim the increase nudge buttons.
    *        <code>EFalse</code> to undim the increase nudge buttons
    * @remarks 
    * @see
    */
    IMPORT_C void SetIncreaseButtonsDimmed(TBool aDimmed);
    
    /**
    * Sets the dim state of all nudge buttons.
    * A dimmed control indicates that user input is not accepted.
    *
    * @param aDimmed
    *        <code>ETrue</code> to dim all nudge buttons;
    *        <code>EFalse</code> to undim all nudge buttons
    * @remarks 
    * @see
    */
    IMPORT_C void SetAllButtonsDimmed(TBool aDimmed);


    /**
    * Sets the control context for all the component controls of the
    * Scrollbar, that is, nudge buttons, shaft, and thumb. This method should 
    * be used in 
    * preference to <code>CCoeControl::SetControlContext</code>.
    *
    * @param aContext
    * @remarks This method allows all parts of the Scrollbar, that is, the 
    *          thumb, nudge buttons, shaft, to share the same look and feel. 
    *          This method is specific to Scrollbars, rather than the more 
    *          generalized implementation in <code>CCoeControl</code>
    * @see           
    */
    IMPORT_C void SetControlContextForAllComponents(
                                        MCoeControlContext* aContext);

protected:  // Methods

    // Methods from base classes
        
    /**
    * @internal
    */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

    /**
    * @internal
    */
    IMPORT_C TInt CountComponentControls() const;

    /**
    * @internal
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: //Methods

    // Methods from base classes
        
    // from MCoeControlObserver
    IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, 
                                              TCoeEvent aEventType);

    // to replace removed Reserved_2()
    IMPORT_C void Dummy1();

protected:

    void HandleButtonEventL(const TPointerEvent& aPointerEvent, 
                            CEikScrollButton* aButton);

private: //Methods

    // construction/destruction
    IMPORT_C virtual void CreateButtonL(CEikScrollButton*& aButton,
                                        CEikScrollButton::TType aType);

    // pointer event functions
    void HandleShaftEventL(const TPointerEvent& aPointerEvent, 
                           TPointerDownOn aLastPointerDownOn);

    // drawing functions
    void DrawButtons(TWhichButtons aWhich) const;
    IMPORT_C virtual void DrawButtonsNow(TWhichButtons aWhich) const;
    void DrawShaft(CWindowGc& aGc) const;
    void DrawShaftNow() const;
    void DrawThumbInShaft(CWindowGc& aGc) const;
    void DrawThumbInShaftNow() const;
    void RedrawShaft(const TRect& aRect) const;

    // set state functions
    void MoveResizeThumbL(
        TShaftRedrawRequired aShaftRedrawRequired=ENoRedrawRequired);
    void NewThumbAtPixelL();
    void MoveThumbToPixel(TInt aPos);
    void UpdateThumbL();
    void UpdateButtonsL();
    void DoSetModel(const TEikScrollBarModel* aModel);

    // calculation
    TInt CalcThumbPixelPos() const;
    TInt CalcThumbModelPos() const;
    TInt MinReqLengthToDisplay() const;
    IMPORT_C virtual void CalcDisplayFlags();
    void AddShaftIfPossible(TInt aExcessSpace);
    void CheckModelBounds();

    // misc
    void GetShaftRect(TRect& aRect) const; 
    void CheckAutoButtonDimming(TDrawNow aDrawNow=EDrawNow);
    TPointerDownOn ResolveButtonPress(TInt aPos);
    TPointerDownOn GeneralizeButtonType(CEikScrollButton::TType aType) const;
    void ReportScrollEventL(TEikScrollEvent aEvent);
    TBool DisplaysThumb() const;
    void UpdateLayoutL();
    
protected:
    
    void CreateRequiredComponentsL();
    void DestroyButton(CEikScrollButton*& aButton);
    void SetButtonAdjacency(CEikScrollButton* aButton);
    TInt NumberOfButtonPairs(TBool aUseDisplayFlags=EFalse) const;
    IMPORT_C virtual void DoSetLengthL(TInt aLength);
    IMPORT_C virtual void SetButtonPositionL(CEikScrollButton* aButton);
    IMPORT_C virtual void SetLayoutL();
    
public:     // Data
    
    /** 
    * the application Scrollbar stack. Each Scrollbar in the application 
    * is added and removed from this stack
    */
    TDblQueLink iSBLink;
    
protected:     // Data
    
    SEikScrollBarButtons iButtons;
    TOrientation iOrientation;
    TInt iScrollBarFlags;
    TInt iScrollBarDisplayFlags;
    TInt iLength;
    TInt iDecreaseButtonsStart;
    TInt iIncreaseButtonsStart;
    MEikScrollBarObserver* iScrollBarObserver;
    MEikScrollBarCustomDrawBase* iCustomDrawer;
    TInt iDecreaseButtonsEnd;
    TInt iIncreaseButtonsEnd;
    TPointerDownOn iPointerDownOn;
    
private:     // Data
    CEikScrollThumb* iThumb;
    TEikScrollBarModel iModel;
    // following quantities all in pixels
    TInt iThumbLength;
    TInt iThumbPos;
    TInt iShaftStart;
    TInt iShaftEnd;
    TInt iPointerOffsetFromThumb;
    TInt iDummy;

    };

/**
 * An arrow head Scrollbar.
 *
 * This consists of two small nudge button arrows, it has no shaft and so
 * takes up very little space.Scrollbars are used when all the content
 * of another control cannot be seen at the same time. They may be
 * oriented horizontally or vertically, and may be displayed in several
 * ways.Scrollbars represent integers, and have a maximum, a minimum,
 * and a current position encapsulated within their model. The on-screen
 * image of a Scrollbar is calculated and displayed by the
 * <code>CEikArrowHeadScrollBar</code> object, and user changes to the
 * Scrollbar (and hence its model) are reported to an interested class
 * through the <code>MEikScrollBarObserver</code> interface.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 *
 * @internal
 * Internal to Symbian
 */
class CEikArrowHeadScrollBar : public CEikScrollBar
    {
    
public:
        
    // Constructors and destructor

    /**
    *
    * Constructs an Arrowhead Scrollbar object for the specified
    * window-owning control.
    *
    */
    IMPORT_C CEikArrowHeadScrollBar();
    
    /**
    * The object destructor.
    */
    IMPORT_C ~CEikArrowHeadScrollBar();

    // Methods from base classes

    /**
    *
    * Completes construction.
    *
    * @param     aScrollBarObserver The Scrollbar observer that is to be
    *            informed of scroll events by this Scrollbar.
    * @param     aParent The parent control for this new Scrollbar.
    * @param     aOrientation The orientation of the new Scrollbar.
    * @param     aLength The length of the Scrollbar.
    * @param     aScrollBarFlags An OR-ed combination of
    *            <code>TEikScrollbarFlags</code>.
    */
    IMPORT_C void ConstructL(MEikScrollBarObserver* aScrollBarObserver,
                    const CCoeControl* aParent,
                    TOrientation aOrientation,
                    TInt aLength,
                    TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);

    /**
    *
    * Called by the framework to handle pointer events on this
    * <code>CEikArrowHeadScrollBar</code>.
    *
    * @param     aPointerEvent
    *            The pointer event to handle.
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
    *
    * Draws this Scrollbar inside the specified rectangle.
    *
    * @param     aRect
    *            The area to redraw.
    */
    IMPORT_C void Draw(const TRect& aRect) const;
    
protected:  // Methods
    
    // New Methods
    
    void SetLayoutL();
    
    /**
    * Writes the internal state of the control and its components to aStream.
    * Does nothing in release mode.
    * Designed to be overidden and base called by subclasses.
    *
    * @internal
    * @since App-Framework_6.1
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: //Methods
    
    // Methods from base classes
    
    void CreateButtonL(CEikScrollButton*& aButton,
                       CEikScrollButton::TType aType);
    void DoSetLengthL(TInt aLength);
    void SetButtonPositionL(CEikScrollButton* aButton);
    void DrawButtonsNow(TWhichButtons aWhich) const;
    void CalcDisplayFlags();
    
    void PositionChanged();

private:     // Data
    
    CCoeControl* iParentControl;

    };

inline void 
    CEikScrollBar::SetScrollBarObserver(
                          MEikScrollBarObserver* aScrollBarObserver)
        { iScrollBarObserver=aScrollBarObserver; }

inline const TEikScrollBarModel* CEikScrollBar::Model() const
        { return &iModel; }


#endif      // EIKSCRLB_H   
            
// End of File