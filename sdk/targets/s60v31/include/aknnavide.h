/*
* ============================================================================
*  Name     : aknnavide.h
*  Part of  : AVKON
*
*  Description:
*     Decorator class for navigation pane controls. 
*     The class, for example, decorates navigation pane controls with 
*     navi arrows.
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

#ifndef AKNNAVIDE_H
#define AKNNAVIDE_H

#include <AknControl.h>
#include <coeccntx.h>
#include <e32std.h>
#include <coecntrl.h>

#include <aknnaviobserver.h>
#include <aknnavi.h>

class CEikScrollButton;
class CAknTabGroup;
class MAknNaviDecoratorObserver;
class CAknNavigationDecoratorExtension;

/**
 * Decorator class for navigation pane controls.
 * The class, for example, decorates navigation pane controls with navi arrows.
 */
class CAknNavigationDecorator :  public CAknControl, 
                                 public MCoeControlObserver,
                                 public MAknNavigationDecoratorInterface
	{
	
friend class CAknNavigationControlContainer;

public:

    /**
     * Defines scroll buttons.
     */
    enum TScrollButton 
        {
        /** Scroll left. */
        ELeftButton =  0x0001,

        /** Scroll right. */
        ERightButton = 0x0002
        };

    /**
     * Defines type of the decorated control. 
     */
    enum TControlType
        {
        /** Type not specified. */
        ENotSpecified,

        /** Tab group. */
        ETabGroup,
        
        /** Label. */
        ENaviLabel,
        
        /** Image. */
        ENaviImage,
        
        /** Text. */
        EHintText,
        
        /** Indicator. */
        EEditorIndicator,
        
        /** Volume. */
        ENaviVolume
        };

public:

    /** 
     * Creates a new navigation decorator. The object takes ownership of the 
     * decorated object at the beginning of the method before any leaving 
     * functions.
     *
     * @param aNavigationControlContainer Container control.
     * @param aDecoratedControl Control to be decorated.
     * @param aType = @c ENotSpecified Control type.
     * @return Navigation Decorator object that 
     *         contains decorated object.
     */
    IMPORT_C static CAknNavigationDecorator* NewL(
        CAknNavigationControlContainer* aNavigationControlContainer, 
        CCoeControl* aDecoratedControl, 
        TControlType aType = ENotSpecified);
    
    /**
    * Destructor.
    */
	IMPORT_C ~CAknNavigationDecorator();

    /**
     * Returns the control inside a navigation decorator object. Ownership of
     * the control is not changed.
     *
     * @return Control that is decorated with the decorator.
     */
    IMPORT_C CCoeControl* DecoratedControl();

    /** 
     * Shows or hides the navigation arrows at the both ends of the navigation
     * pane when current object is shown.
     *
     * @param aVisible Boolean value if navigation arrows are shown with the 
     *        decorated control. Visible if @c ETrue.
     */
	IMPORT_C void MakeScrollButtonVisible(TBool aVisible);
    
    /** 
     * Gets the State of the visibility of navigation arrows.
     *
     * @return @c ETrue if visible.    
     */
	IMPORT_C TBool ScrollButtonVisible() const;
    
    /** 
     * Sets the navigation arrow dimmed (and highlighted). Arrows have to be 
     * visible so that the dimmed arrow is shown on the screen.
     *
     * @param aButton Navigation arrow to be set (@c ELeftButton or 
     *        @c ERightButton).
     * @param aDimmed @c ETrue is the button is dimmed, @c EFalse if the button
     *        is set highlighted.
     */
    IMPORT_C void SetScrollButtonDimmed(TScrollButton aButton, TBool aDimmed);
    
    /**
    * Is button dimmed or highlighted.
    *
    * @param aButton Navigation arrow.
    * @return @c ETrue If the navigation arrow is dimmed, @c EFalse if 
    *         it is highlighted.
    */
    IMPORT_C TBool IsScrollButtonDimmed(TScrollButton aButton) const;
    
    /**
     * Sets the type of the decorated control.
     * 
     * @param aType Type of the control.
     */
    IMPORT_C void SetControlType(TControlType aType);
    
    /**
     * Returns the type of the decorated control.
     * 
     * @return Control type.
     */
    IMPORT_C TControlType ControlType() const;
 
    /**
     * Sets observer for navigation decorator events in the decorated control.
     * 
     * @param aObserver Pointer to observer.
     */
    IMPORT_C virtual void SetNaviDecoratorObserver(
                        MAknNaviDecoratorObserver* aObserver);

    /**
     * Sets the pointer to the default navigation pane control.
     *
     * @param aContainer Pointer to default control in navigation pane.
     */
    void SetNaviStack(CAknNavigationControlContainer* aContainer);

    /**
     * From @c CCoeControl.
     *
     * Handle pointer events.
     *
     * @param aPointerEvent Pointer event to be handled.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
     * Defines the navigation control layout style.
     */
    enum TAknNaviControlLayoutStyle
        {
        /** Normal layout style. */
        ENaviControlLayoutNormal = 0x1,

        /** Narrow layout style. */
        ENaviControlLayoutNarrow = 0x2        
        };

    /**
     * Defines the navigation control layout mode.
     */
    enum TAknNaviControlLayoutMode
        {
        /** 
         * This is the default layout mode. It lets UI framework to decide the
         * proper layout style which is applied to decorated controls in all 
         * situations.
         */
        ENaviControlLayoutModeAutomatic = 0x400,

        /** 
         * @c ENaviControlLayoutModeForced layout mode can be used to lock
         * the layout style to the current style.
         */
        ENaviControlLayoutModeForced = 0x800        
        };

        
    /**
     * Sets the layout style for this objects decorated control. The layout 
     * style can be normal or narrow style.
     *
     * The style is really applied if the decorated control supports it or if 
     * the layout mode has been set to forced mode 
     * (@c ENaviControlLayoutModeForced). Additionally narrow mode may not be 
     * supported at all in some statuspane configurations (even if forced). 
     * 
     * Whether decorated control supports or does not support given style at the
     * currently active statuspane layout can be queried using 
     * @c NaviControlLayoutStyleSupported() method.
     * 
     * @since S60 3.0     
     * @param aStyle Can be either normal (@c ENaviControlLayoutNormal)
     *        or narrow style (@c ENaviControlLayoutNarrow).
     *
     */
    IMPORT_C void SetNaviControlLayoutStyle(TAknNaviControlLayoutStyle aStyle);

    /**
    * Gets the current layout style of this objects decorated control
    * (ENaviControlLayoutNormal or ENaviControlLayoutNarrow).
    *
    * @since S60 3.0 
    * @return Current layout style of the navicontrol
    */
    IMPORT_C TAknNaviControlLayoutStyle NaviControlLayoutStyle();

    /**
     * Tells if decorated control supports given layout style at the current 
     * statuspane layout. For @c ENotSpecified type of controls this always 
     * returns @c EFalse (just for safety) because their implementation is 
     * not known.
     *
     * @since S60 3.0     
     * @param aStyle The layout style.
     * @return @c ETrue if the control supports given layout style 
     *         otherwise returns @c EFalse.
     */
    IMPORT_C TBool NaviControlLayoutStyleSupported(TAknNaviControlLayoutStyle 
                                                   aStyle);

    /**
     * Sets the layout mode @c ENaviControlLayoutModeAutomatic or 
     * @c ENaviControlLayoutModeForced. See @c TAknNaviControlLayoutMode
     * for more information.
     *
     * @since S60 3.0     
     * @param aMode New layout mode.
     *
     */
    IMPORT_C void SetNaviControlLayoutMode(TAknNaviControlLayoutMode aMode);
    
    /**
     * Gets the current layout mode of decorated control. Can be 
     * @c ENaviControlLayoutModeAutomatic (default) or 
     * @c ENaviControlLayoutModeForced (usually set by the application).
     *
     * @since S60 3.0     
     * @return Decorated control's current layout 
     *         mode.
     *
     */
    IMPORT_C TAknNaviControlLayoutMode NaviControlLayoutMode();
        

protected: // from CCoeControl

    /**
     * From @c CCoeControl. 
     *
     * Handles the size change events.
     */
    IMPORT_C virtual void SizeChanged();

    /**
     * From @c CCoeControl. 
     *
     * Returns the number of controls inside the context pane control.
     *
     * @return Number of controls.
     */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
     * From @c CCoeControl. 
     *
     * Returns a control determined by control id.
     *
     * @param aIndex Index of a control to be returned.
     * @return Pointer to the control.
     */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

public: // from CCoeControl
    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. color scheme change.
	 * @param aType Event type.
	 */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

protected: // from MCoeControlObserver

    /**
     * From @c MCoeControlObserver.
     *
     * Handles an event from an observed control.
     *
     * @param aControl Control that caused the event.
     * @param aEventType Type of the event.
     */
    IMPORT_C void HandleControlEventL(CCoeControl* aControl, 
                                      TCoeEvent aEventType);

private:

    /**
     * From CAknControl
     */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:

    /**
     * Private constructor.
     */
    IMPORT_C void ConstructL();

private:

    /**
     * From CAknControl
     */
    IMPORT_C virtual void Draw(const TRect& aRect) const;

    /**
     * Gets parent rect of this control. Used for layout calculation purposes.
     */
    TRect ParentRect();

public:

    /**
     * Gets the default rectangle of the given control type.
     *
     * @param aControlType The control type from which default rectangle is
     *        asked.
     * @return Rectangle which tells the default area for given 
     *         controltype. Coordinates are relative to navipane. 
     */
    static TRect DecoratedControlRect(TInt aControlType);

    /**
     * Gets the default rectangle of the navigation pane's default control.
     *
     * @param aControlType Not used.
     * @return Rectangle of the navigation pane's default control.
     */
    static TRect DecoratedControlNarrowRect(TInt aControlType);

private:

    /**
     * Gets the default rect of default controltype realtive to navipane in 
     * normal layoutstyle (ENaviControlLayoutNormal)
     *
     * @return Rectangle which is tells the default area for given controltype. 
     *         Coordinates are relative to navipane.
     *  
     */
    static TRect DecoratedDefaultControlRect();

    /**
     * Gets the default rect of tab controltype realtive to navipane in 
     * normal layoutstyle (ENaviControlLayoutNormal)
     *
     * @return Rectangle which is tells the default area for given controltype. 
     *         Coordinates are relative to navipane.
     * 
     */
    static TRect DecoratedTabControlRect();

    /**
     * Gets the default rect of volume controltype realtive to navipane in 
     * normal layoutstyle (ENaviControlLayoutNormal)
     *
     * @return Rectangle which is tells the default area for given controltype. 
     *         Coordinates are relative to navipane.
     * 
     */
    static TRect DecoratedVolumeControlRect();

    /**
     * This method handles sizechanges in normal layout style.
     */
    void SizeChangedInNormalLayout();

    /**
     * This method handles sizechanges in narrow layout style.
     */
    void SizeChangedInNarrowLayout();
    
    /**
     * This method initializes timer that is used for times layout style 
     * changes.
     */
    void InitLayoutStyleTimer();

    /**
     * This method cancels timer that is used for times layout style changes.
     */
    void CancelLayoutStyleTimer();    

    /**
     * This method is executed when timer that is used for times layout style 
     * changes expires.
     */
    static TInt LayoutStyleEvent(TAny * aPtr);

    /**
     * This method is executed when timer that is used for times layout style
     * changes expires.
     */
    void DoLayoutStyleEvent();
    
    void StartTimerL();
    
    void SmallDirectionIndicationL();
    
    static TInt IndicationDrawCallbackL( TAny* aThis );
    
    
protected:

    /**
     * Decorated control.
     * Own.
     */
    CCoeControl* iDecoratedControl;

    /**
     * Navigation pane default control.
     */
    CAknNavigationControlContainer* iContainer;

    /**
     * Observer for handling decorator events.
     */
    MAknNaviDecoratorObserver* iNaviDecoratorObserver;

private:
	TBool iNaviArrowsVisible;
	TBool iNaviArrowLeftDimmed;
	TBool iNaviArrowRightDimmed;
    TControlType iControlType;        
    TPoint iArrowLeftPos;
    TSize iArrowLeftSize;
    TPoint iArrowRightPos;
    TSize iArrowRightSize;
    
    TInt iLayoutFlags;
    CPeriodic* iLayoutStyleTimer;     

    CAknNavigationDecoratorExtension* iExtension;
    
    TInt iSpare;
	};

// AKNNAVIDE_H
#endif
