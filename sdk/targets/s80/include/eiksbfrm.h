/*
* =============================================================================
*  Name        : eiksbfrm.h
*  Part of     : CKON
*  Interface   : Scrollbar API
*  Description : Scrollbar frame
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

#ifndef EIKSBFRM_H
#define EIKSBFRM_H


// INCLUDES
#include <lafpublc.h>
#include <eikscrlb.h>

// FORWARD DECLARATIONS
class CEikCornerWindow;
class CEikScrollBarMargin;


// CLASS DECLARATIONS

/**
* The <code>TEikScrollBarFrameLayout</code> class sets the frame layout for a 
* Scrollbar. This contains public data for the margins, the client area 
* granularity and the tiling mode.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class TEikScrollBarFrameLayout
    {
public:  // Declarations
        
    /**
    * The enumeration <code>TTilingMode</code> determines whether the client 
    * rectangle or the inclusive rectangle remains constant.
    */
    enum TTilingMode
        {
        /** the client rectangle remains constant */
        EClientRectConstant,
        /** the inclusive rectangle remains constant */
        EInclusiveRectConstant
        };
public:
    // Constructors and destructor

    /**
    * The default object constructor.
    */
    IMPORT_C TEikScrollBarFrameLayout();
        
    /**
    * Sets all-inclusive margins.
    *
    * @param  aMargin The value to use for all-inclusive margins
    * @remarks
    * @see
    */
    IMPORT_C void SetInclusiveMargin(TInt aMargin);

    /**
    * Sets all client margins.
    * These surround the client rectangle, which is the client area viewport
    * onto the larger canvas to be scrolled.
    *
    * @param aMargin The value to use for all client margins
    * @remarks
    * @see
    */
    IMPORT_C void SetClientMargin(TInt aMargin);

    // Methods from base classes

public:     // Data
    /** the inclusive margin, in twips or pixels. The area in which the Scrollbars are placed */
    TMargins iInclusiveMargin;
    /** the client margin, in twips or pixels. The area containing the scrollable data */
    TMargins iClientMargin;
    /** the amount of screen movement performed when the nudge button is pressed in the area containing the scrollable data */
    TSize iClientAreaGranularity;
    /** determines whether the client rectangle, or the inclusive rectangle, remains constant */
    TTilingMode iTilingMode;
    };

    /**
    * The Scrollbar frame is a manager that relates 
    * the horizontal and vertical Scrollbars with 
    * a corner window. A corner window is a view or dialog containing the 
    * scrollable data. This class manages the setup and behavior
    * of Scrollbars. A Scrollbar frame is not a
    * control, but it does implement the standard control composite pattern
    * to manage the relationship between the Scrollbars and the corner window.
    *
    * @lib eikcoctl.lib
    * @since 6.0
*/
class CEikScrollBarFrame : public CBase
    {
public:  // Declarations
        
    /**
    * The enumeration <code>TScrollBarVisibility</code> defines the visibility 
    * of a Scrollbar.
    */
    enum TScrollBarVisibility
        {
        /** the Scrollbar is not visible */
        EOff,
        /** the Scrollbar is visible */
        EOn,
        /** the Scrollbar is visible, if required */
        EAuto
        };
        
    /**
    * The enumeration <code>TScrollBarSide</code> defines the location of a 
    * Scrollbar.
    */
    enum TScrollBarSide
        {
        /** the Scrollbar is located at the bottom or to the right of the Scrollbar frame */
        EBottomOrRight              =SLafScrollBarFrame::EBottomOrRight,
        /** the Scrollbar is located at the top or to the left of the Scrollbar frame */
        ETopOrLeft                  =SLafScrollBarFrame::ETopOrLeft     
        };
        
    /**
    * The enumeration <code>TScrollBarManagement</code> determines how the Scrollbar frame manages Scrollbars.
    */
    enum TScrollBarManagement
        {
        /** 
        * the Scrollbar frame creates, destroys, and recreates Scrollbars
        * according to the visibility mode. The Scrollbar frame also acts as
        * an intermediary with its owning control so that the Scrollbars can
        * be treated as component controls
        */
        EComponent = SLafScrollBarFrame::EComponent,
                
        /** 
        * the Scrollbar frame creates, destroys, and recreates Scrollbars
        * according to the visibility mode. In this case, the Scrollbars are
        * not treated as component controls, instead, they are
        * geometrically managed in windows floating above the control window and
        * their position is determined in relation to the frame's position on
        * the screen
        */
        EFloating = SLafScrollBarFrame::EFloating,
            
        /** 
        * the Scrollbar frame uses the central application Scrollbar as held
        * in the environment. This Scrollbar is neither owned by the frame nor
        * treated as a component control of the frame's owner
        */
        EApplicationScrollBar = SLafScrollBarFrame::EApplicationScrollBar
        };
    /**
    * Defines the type of Scrollbar.
    * @deprecated
    */
    enum TScrollBarType
        {
        /** Scrollbar complete with shaft. */
        ENormalScrollBar = 0x0000,
        /** floating arrow head Scrollbar, without shaft. */
        EArrowHead = 0x1000 
        };
        
private:  // Declarations
        
    enum TMarginsAdjustmentMode
        {
        EGrow,
        EShrink
        };
        
    class TScrollBarAttributes
        {
    public:
        TScrollBarAttributes();
    public:
        TInt iControlType;
        TInt iBreadth; //excluding margin
        TScrollBarSide iSide;
        TScrollBarManagement iManagement;
        };
        
    class CExtraData : public CBase
        {
    public:
        ~CExtraData();
        CEikCornerWindow* iCornerWindow;
        CEikScrollBarMargin* iHSBarMargin;
        CEikScrollBarMargin* iVSBarMargin;
        };
        
public: // Methods

    // Constructors and destructor

    /**
    * The object constructor
    *
    * @param aParentWindow The Scrollbar frame's parent control. 
    *                      Usually a window control
    * @param aObserver Observer of Scrollbar activity
    * @param aPreAlloc Whether to  allocate Scrollbars immediately.
    *                  This is useful if the control being scrolled can 
    *                  change size while the Scrollbar is displayed
    * @remarks  If <code>aPreAlloc</code> is <code>ETrue</code>, any 
    *           Scrollbars that the Scrollbar frame may need are pre-allocated 
    *           according to the current Scrollbar visibility flags for 
    *           both the horizontal and vertical Scrollbars. A Scrollbar 
    *           that is pre-allocated, but which is not specifically displayed, 
    *           remains invisible. The default is for <code>aPreAlloc</code> to
    *           be <code>EFalse</code>, in which case, no pre-allocation is 
    *           performed. The default behavior is appropriate for 
    *           Scrollbar frames that do not alter dynamically throughout 
    *           their lifetime. For example, a pop-out listbox from a dialog 
    *           displays a set of items that, once the listbox is visible, 
    *           does not change. Pre-allocating a Scrollbar, in this case, 
    *           would be a waste of memory
    * @see
    */
    IMPORT_C CEikScrollBarFrame(CCoeControl* aParentWindow, 
                                MEikScrollBarObserver* aObserver, 
                                TBool aPreAlloc=EFalse);
                
    /**
    * The object destructor.
    */
    IMPORT_C ~CEikScrollBarFrame();
                
    // New methods
                
    /**
    * Forces any Scrollbars, and the corner window if it is visible, to be
    * redrawn.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void DrawScrollBarsNow() const;
                
    /**
    *
    * Sets the visibility state for both the horizontal and the vertical
    * Scrollbars. This is used when tiling.
    *
    * @param aHVisibility The horizontal Scrollbar visibility
    * @param aVVisibility The vertical Scrollbar visibility
    * @remarks
    * @see
    */
    IMPORT_C void SetScrollBarVisibilityL(TScrollBarVisibility aHVisibility, 
                                          TScrollBarVisibility aVVisibility);
                
    /**
    * Gets the horizontal Scrollbar's visibility.
    *
    * @return the visibility for the horizontal Scrollbar
    * @remarks
    * @see
    */
    inline TScrollBarVisibility HScrollBarVisibility() const;
                
    /**
    * Gets the vertical Scrollbar's visibility.
    *
    * @return the visibility for the vertical Scrollbar
    * @remarks
    * @see
    */
    inline TScrollBarVisibility VScrollBarVisibility() const;
                
    /**
    * Sets the dimmed property of both the Scrollbars
    *
    * @param aHDimmed Whether the horizontal Scrollbar should be dimmed
    * @param aVDimmed Whether the vertical Scrollbar should be dimmed
    * @remarks
    * @see
    */
    IMPORT_C void SetScrollBarsDimmed(TBool aHDimmed, TBool aVDimmed) const;
                
    /**
    * Tiles the client area and the Scrollbars managed by the frame.
    * The Scrollbars are set up according to the Scrollbar models, 
    * <code>aHModel</code> and <code>aVModel</code>. Ownership of the 
    * models is not
    * transferred as a result of passing these parameters as pointers. The
    * result of tiling geometry management is observable through the two
    * rectangles <code>aClientRect</code> and <code>aInclusiveRect</code>. 
    * <code>aClientRect</code> is the client area containing the data to be 
    * scrolled. <code>aInclusiveRect</code> is the area containing the 
    * Scrollbars. Parameter <code>aLayout</code> determines whether 
    * <code>aClientRect</code> or <code>aInclusiveRect</code> does not scroll.
    * If one is made constant, the other is scrollable.
    *
    * @param aHModel The horizontal Scrollbar model
    * @param aVModel The vertical Scrollbar model
    * @param aClientRect The client rectangle
    * @param aInclusiveRect A rectangle that includes the area to be scrolled 
    *                       and the Scrollbars themselves
    * @param aLayout The tiling layout
    * @return <code>ETrue</code> if the non-constant rectangle is adjusted;
    *         otherwise <code>EFalse</code>
    * @remarks 
    * @see
    */
    IMPORT_C TBool TileL(TEikScrollBarModel* aHModel, 
                         TEikScrollBarModel* aVModel,
                         TRect& aClientRect, 
                         TRect& aInclusiveRect, 
                         const TEikScrollBarFrameLayout& aLayout);
                
    /**
    * Adjusts both Scrollbar's positions relative to their current positions.
    *
    * @param aDeltaX Adjustment for the horizontal Scrollbar, in pixels
    * @param aDeltaY Adjustment for the vertical Scrollbar, in pixels
    * @remarks
    * @see
    */
    IMPORT_C void MoveThumbsBy(TInt aDeltaX, TInt aDeltaY) const;
                
    /**
    * Sets the specified Scrollbar position to an absolute position.
    *
    * @param aOrientation The Scrollbar to set the position of
    * @param aThumbPos The new position of the Scrollbar, in pixels
    * @remarks
    * @see
    */
    IMPORT_C void MoveThumbTo(CEikScrollBar::TOrientation aOrientation, 
                              TInt aThumbPos) const;
                
    /**
    * Returns the breadth of the Scrollbar identified by
    * <code>aOrientation</code>.
    *
    * @param aOrientation The orientation of the Scrollbar of which 
    *                     to obtain the breadth
    * @return the specified Scrollbar's breadth including any margin
    * @remarks
    * @see
    */
    IMPORT_C TInt ScrollBarBreadth(
                       CEikScrollBar::TOrientation aOrientation) const;
                
    /**
    * Sets the scrolling model for the Scrollbar identified by the
    * orientation <code>aOrientation</code> as being adjustable.
    *
    * @param aOrientation The orientation of the Scrollbar to change
    * @param aAdjusts <code>ETrue</code> to specify the scrolling model as
    *                 being adjustable for the specified Scrollbar;
    *                 <code>EFalse</code> otherwise
    * @remarks The default is to allow the Scrollbar's model to be modified.
    *          <b>Note</b>: if the model is adjustable and the content of the 
    *          model is changed using the public member variables of class 
    *          <code>TEikScrollBarModel</code>, method 
    *          <code>TileL()</code> should be called to update the Scrollbar
    *          with new values. If the model is not adjustable, the new values
    *          are ignored
    * @see
    */
    IMPORT_C void SetAdjustsModel(CEikScrollBar::TOrientation aOrientation,
                                  TBool aAdjusts);
                
    /**
    * Returns <code>ETrue</code> if the Scrollbar frame can adjust the
    * scrolling model for orientation <code>aOrientation</code>.
    *
    * @param aOrientation The orientation of the Scrollbar to check
    * @return <code>ETrue</code> if this Scrollbar frame can adjust the 
    *          scrolling model, <code>EFalse</code> otherwise
    * @remarks 
    * @see <code>SetAdjustsModel()</code> for setting the model's
    *      changeable status
    */
    IMPORT_C TBool AdjustsModel(
                          CEikScrollBar::TOrientation aOrientation) const;
                
    /**
    * Sets flags for the horizontal Scrollbar.
    *
    * @param aMask Horizontal Scrollbar flags to be set
    * @remarks Values for <code>aMask</code> are found in
    *          <code>TEikScrollBarFlags</code>
    * @see <code>eikscrlb.h</code> for <code>TEikScrollBarFlags</code>
    */
    inline void SetFlagsForHScrollBar(TInt aMask);
              
    /**
    * Sets flags for the vertical Scrollbar.
    * @param aMask Vertical Scrollbar flags to be set
    * @remarks Values for <code>aMask</code> are found in
    *          <code>TEikScrollBarFlags</code>
    * @see <code>eikscrlb.h</code> for <code>TEikScrollBarFlags</code>
    */
    inline void SetFlagsForVScrollBar(TInt aMask);
                
    /**
    * Clears horizontal Scrollbar flags.
    * @param aMask Horizontal Scrollbar flags to be cleared
    * @remarks Values for <code>aMask</code> are found in
    *          <code>TEikScrollBarFlags</code>
    * @see <code>eikscrlb.h</code> for <code>TEikScrollBarFlags</code>
    */
    inline void ClearFlagsForHScrollBar(TInt aMask);
                
    /**
    * Clears vertical Scrollbar flags.
    *
    * @param aMask Vertical Scrollbar flags to be cleared
    * @remarks Values for <code>aMask</code> are found in
    *          <code>TEikScrollBarFlags</code>
    * @see <code>eikscrlb.h</code> for <code>TEikScrollBarFlags</code>
    */
    inline void ClearFlagsForVScrollBar(TInt aMask);
                
    /**
    * Gets the horizontal Scrollbar flags.
    * @return horizontal Scrollbar flags
    * @remarks Flag values are found in
    *          <code>TEikScrollBarFlags</code>
    * @see <code>eikscrlb.h</code> for <code>TEikScrollBarFlags</code>
    */
    inline TInt FlagsForHScrollBar() const;
                
    /**
    * Gets the vertical Scrollbar flags.
    * @return vertical Scrollbar flags
    * @remarks
    * @see
    */
    inline TInt FlagsForVScrollBar() const;
                
    /**
    * Returns whether the specified Scrollbar exists
    *
    * @param aOrientation The Scrollbar to look for, specified by its 
    *                     orientation 
    * @return <code>ETrue</code> if the Scrollbar exists, <code>EFalse</code>
    *         if not
    * @remarks
    * @see
    */
    IMPORT_C TBool ScrollBarExists(
                            CEikScrollBar::TOrientation aOrientation) const;
                
    /**
    * @internal
    */
    IMPORT_C TInt CountComponentControls() const;
                
    /**
    * @internal
    */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
                
    /**
    * Gets a pointer to the corner window within this frame.
    *
    * @return a pointer to the corner window, or <code>NULL</code> if not 
    *         present
    * @remarks The corner window is a parent control, such as a view or dialog 
    *          containing the Scrollbars 
    * @see
    */
    IMPORT_C CCoeControl* CornerWindow() const;
                
    /**
    * Gets a pointer to the specified Scrollbar within this frame.
    *
    * @param aOrientation The Scrollbar to return, specified by its 
    *                     orientation
    * @return a pointer to the Scrollbar, or <code>NULL</code> if not present
    * @remarks
    * @see
                */
    IMPORT_C CEikScrollBar* GetScrollBarHandle(
                               CEikScrollBar::TOrientation aOrientation) const;
                
    /**
    * Returns the central application Scrollbar for orientation
    * <code>aOrientation</code>. This does not transfer ownership. The central
    * application Scrollbar is a scrolling indicator supplied in the user 
    * interface that can be used by any control to indicate scrolling. It 
    * removes the need for a control to create a Scrollbar of its own. 
    * The method returns <code>NULL</code> if no central application Scrollbar is 
    * available. This method can only be used in a thread with an active 
    * <code>CEikon</code> environment.
    *
    * @param aOrientation The orientation for which to obtain the
    *                     central application Scrollbar
    * @return the central application Scrollbar for the
    *         specified orientation
    * @remarks
    * @see
    */
    IMPORT_C static CEikScrollBar* ApplicationScrollBar(
                                  CEikScrollBar::TOrientation aOrientation);
                
    /**
    * Adds the Scrollbar <code>aScrollBar</code> to the stack of central
    * application Scrollbars for scrolling orientation
    * <code>aOrientation</code>. The central application Scrollbar is a 
    * scrolling indicator supplied in the user interface that can be used by 
    * any control to indicate scrolling. This removes the need for a control 
    * to create a Scrollbar of its own. This can only be used in a thread 
    * with an active <code>CEikon</code> environment. Scrollbar events are
    * only handled via the control, if the control inherits from class
    * <code>MEikScrollBarObserver</code>, and either the developer implements, 
    * or the control already implements, method <code>HandleScrollEventL</code>.
    *
    * @param aOrientation The orientation of the Scrollbar to add
    * @param aScrollBar The Scrollbar to add
    * @remarks
    * @see
    */
    IMPORT_C static void AddApplicationScrollBarL(
                                CEikScrollBar::TOrientation aOrientation, 
                                CEikScrollBar& aScrollBar);
                
    /**
    * Removes the Scrollbar <code>aScrollBar</code> from the stack of
    * central application Scrollbars for scrolling orientation
    * <code>aOrientation</code>. The central application Scrollbar is a 
    * scrolling indicator supplied in the UI that can be used by any control 
    * to indicate scrolling. It removes the need for a control to create a 
    * Scrollbar of its own. This can only be used in a thread with an active 
    * environment.
    *
    * @param aOrientation The orientation of the Scrollbar to remove
    * @param aScrollBar The Scrollbar to remove
    * @remarks
    * @see
    */
    IMPORT_C static void RemoveApplicationScrollBar(
                              CEikScrollBar::TOrientation aOrientation, 
                              CEikScrollBar& aScrollBar);
                
    /**
    * Sets management of the Scrollbar identified by the orientation
    * <code>aOrientation</code> to <code>aManagement</code>.
    * This determines how the Scrollbar frame manages Scrollbars.
    *
    * @param aOrientation The orientation of the Scrollbar for which 
    *                     to set management
    * @param aManagement The Scrollbar frames management type for the
    *                    specified Scrollbar
    * @remarks
    * @see
    */
    IMPORT_C void SetScrollBarManagement(
                              CEikScrollBar::TOrientation aOrientation, 
                              TScrollBarManagement aManagement);
                
    /**
    * Returns the management enum of the Scrollbar identified by the
    * orientation <code>aOrientation</code>.
    * This enum determines how the Scrollbar frame manages Scrollbars.
    *
    * @param aOrientation The orientation of the Scrollbar for which you wish
    *                     to get the management enum
    * @return the Scrollbar frames management type for the specified Scrollbar
    * @remarks
    * @see
    */
    IMPORT_C TScrollBarManagement ScrollBarManagement(
                          CEikScrollBar::TOrientation aOrientation) const;
                
    /**
    * Sets the control type of the Scrollbar identified by the orientation
    * <code>aOrientation</code> to <code>aControlType</code>.
    *
    * @param aOrientation The orientation of the Scrollbar for which
    *                     to specify the control type
    * @param aControlType The control type for the specified Scrollbar
    * @remarks
    * @see
    */
    IMPORT_C void SetScrollBarControlType(
                           CEikScrollBar::TOrientation aOrientation, 
                           TInt aControlType);
                
    /**
    * Returns the control type of the Scrollbar identified by the
    * orientation <code>aOrientation</code>.
    *
    * @param aOrientation The orientation of the Scrollbar you wish to check
    * @return the Scrollbar's control type
    * @remarks
    * @see
    */
    IMPORT_C TInt ScrollBarControlType(
                     CEikScrollBar::TOrientation aOrientation) const;
                
    /**
    * Specify the side of the Scrollbar frame on which to place the Scrollbar
    * identified by the orientation <code>aOrientation</code>.
    *
    * @param aOrientation The orientation of the Scrollbar to change
    * @param aSide The side of the Scrollbar frame on which the
    *              specified Scrollbar is to be placed
    * @remarks
    * @see
    */
    IMPORT_C void SetScrollBarSide(
                     CEikScrollBar::TOrientation aOrientation, 
                     TScrollBarSide aSide);
                
    /**
    * Returns the side of the Scrollbar frame on which the Scrollbar,
    * identified by the orientation <code>aOrientation</code>, is placed.
    *
    * @param aOrientation The orientation of the Scrollbar to check
    * @return the side of the frame on which the specified
    *         Scrollbar is to be placed
    * @remarks
    * @see
    */
    IMPORT_C TScrollBarSide ScrollBarSide(
                           CEikScrollBar::TOrientation aOrientation) const;
                
    /**
    * Sets the working breadth of the Scrollbar identified by orientation
    * <code>aOrientation</code>. This method sets the breadth to be used when 
    * performing Scrollbar frame component geometry management. The breadth 
    * does not include the Scrollbar margin that appears to the left of 
    * vertical Scrollbars or above horizontal Scrollbars (assuming the Scrollbar 
    * is positioned bottom or right).
    *
    * @param aOrientation The orientation of the Scrollbar for which 
    *                     to set the breadth
    * @param aBreadth The breadth of the specified Scrollbar
    * @remarks
    * @see
    */
    IMPORT_C void SetScrollBarBreadth(CEikScrollBar::TOrientation aOrientation, 
                                      TInt aBreadth);
                
    /**
    * Sets the Scrollbar frame observer to <code>aObserver</code>.
    *
    * @since Uikon1.2
    * @remarks
    * @see
    */
    IMPORT_C void SetObserver(MEikScrollBarObserver* aObserver);
                
    /**
    * Sets the custom background drawer for the components of the Scrollbar 
    * frame.
    *
    * @since Series 90 1.0.
    * @param aCustomDrawer The custom drawer
    * @remarks
    * @see
    */
    IMPORT_C void SetCustomDrawer(MEikScrollBarCustomDrawBase* aCustomDrawer);
                
    /**
    * Turns the Scrollbar margins on or off. The margins are off by default.
    *
    * @since Series 90 1.0
    * @param aMargins <code>ETrue</code> to turn the margins on; 
    *                 <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C void SetScrollBarMargins(TBool aMargins);

    /**
    * @internal
    */
    IMPORT_C void SetAdjustsHorizontalModel(TBool aAdjusts); 

    /**
    * @internal
    */
    IMPORT_C void SetAdjustsVerticalModel(TBool aAdjusts);

    /**
    * @internal
    */
    IMPORT_C TBool AdjustsHorizontalModel() const;

    /**
    * @internal
    */
    IMPORT_C TBool AdjustsVerticalModel() const;

    /**
    * @internal
    */
    IMPORT_C void MoveHorizThumbTo(TInt aHorizThumbPos) const;

    /**
    * @internal
    */
    IMPORT_C void MoveVertThumbTo(TInt aVertThumbPos) const;

    /**
    * @internal
    */
    IMPORT_C void SetTypeOfHScrollBar(TScrollBarType aType);

    /**
    * @internal
    */
    IMPORT_C void SetTypeOfVScrollBar(TScrollBarType aType);

    /**
    * @internal
    */
    IMPORT_C void SetSideOfHScrollBar(TScrollBarSide aSide);

    /**
    * @internal
    */
    IMPORT_C void SetSideOfVScrollBar(TScrollBarSide aSide);

    /**
    * @internal
    */
    IMPORT_C TScrollBarType TypeOfHScrollBar() const;
    
    /**
    * @internal
    */
    IMPORT_C TScrollBarType TypeOfVScrollBar() const;

    /**
    * @internal
    */
    IMPORT_C TBool RightSideForHScrollBar() const;

    /**
    * @internal
    */
    IMPORT_C TBool RightSideForVScrollBar() const;

    /**
    * @internal
    */

    IMPORT_C TBool IsArrowHeadScrollBar(TInt aFlag) const;
                
private: //Methods
        
    void CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aHModel,
                                            const TEikScrollBarModel* aVModel);

    void CheckPhysicalScrollBarVisibility(TEikScrollBarModel* aHModel, 
                                          TEikScrollBarModel* aVModel, 
                                          const TRect& aOutputRect, 
                                          const TEikScrollBarFrameLayout& aLayout);

    void AdjustRect(TRect& aOutputRect, 
                    TEikScrollBarFrameLayout::TTilingMode aTilingMode) const;

    void CreateOrRemoveRequiredScrollBarsL();

    void RemoveScrollBar(CEikScrollBar*& aScrollBar);

    void TileScrollBarsWithClientL(const TRect& aClientRect, 
                                   const TEikScrollBarModel* aHModel, 
                                   const TEikScrollBarModel* aVModel);

    TBool AdjustScrollBarModel(CEikScrollBar::TOrientation aOrientation, 
                               TEikScrollBarModel* aModel, 
                               TInt aNewPixelThumbSpan, 
                               const TEikScrollBarFrameLayout& aLayout) const;

    void AdjustRectByMargins(TMarginsAdjustmentMode aMode, 
                             TRect& aRect, 
                             const TMargins& aMargins) const;

    CEikScrollBar* CreateSBarLC(CEikScrollBar::TOrientation aOrientation,
                                TInt aFlags) const;

    CEikScrollBar* CreateHSBarLC() const;

    CEikScrollBar* CreateVSBarLC() const;

    CEikCornerWindow* CreateCornerWindowLC() const;

    static void CheckVisible(CCoeControl* aComponent);
        
private:     // Data
        
    TScrollBarVisibility iHVisibility;
    TScrollBarVisibility iVVisibility;
    MEikScrollBarObserver* iObserver;
    CCoeControl* iParentWindow;
    CExtraData *iExtra;
    CEikScrollBar* iHSbar;
    CEikScrollBar* iVSbar;
    TInt iScrollBarFrameFlags;
    TInt iHScrollBarFlags;
    TInt iVScrollBarFlags;
    TScrollBarAttributes iHAttributes;
    TScrollBarAttributes iVAttributes;
    };
    
inline CEikScrollBarFrame::TScrollBarVisibility 
                       CEikScrollBarFrame::HScrollBarVisibility() const
                       { return iHVisibility; }
    
inline CEikScrollBarFrame::TScrollBarVisibility 
                       CEikScrollBarFrame::VScrollBarVisibility() const
                       { return iVVisibility; }
    
inline void CEikScrollBarFrame::SetFlagsForHScrollBar(TInt aMask)
                       { iHScrollBarFlags|=aMask; }
    
inline void CEikScrollBarFrame::SetFlagsForVScrollBar(TInt aMask)
                       { iVScrollBarFlags|=aMask; }
    
inline void CEikScrollBarFrame::ClearFlagsForHScrollBar(TInt aMask)
                       { iHScrollBarFlags&=(~aMask); }
    
inline void CEikScrollBarFrame::ClearFlagsForVScrollBar(TInt aMask)
                       { iVScrollBarFlags&=(~aMask); }
    
inline TInt CEikScrollBarFrame::FlagsForHScrollBar() const
                       { return iHScrollBarFlags; }
    
inline TInt CEikScrollBarFrame::FlagsForVScrollBar() const
                       { return iVScrollBarFlags; }
    
#endif      // EIKSBFRM_H   
    
    // End of File
