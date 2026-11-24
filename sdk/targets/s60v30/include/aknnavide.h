/*
* ============================================================================
*  Name     : aknnavide.h
*  Part of  : AVKON
*
*  Description:
*     Decorator class for navigation pane controls. 
*     The class, for example, decorates navigation pane controls with navi arrows.
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

	enum TScrollButton 
		{
		ELeftButton =  0x0001,
		ERightButton = 0x0002
		};

    enum TControlType
        {
        ENotSpecified,
        ETabGroup,
        ENaviLabel,
        ENaviImage,
        EHintText,
        EEditorIndicator,
        ENaviVolume
        };

public:

    /** 
    * Creates new navigation decorator. The object takes ownership of the decorated object
    * at the beginning of the method before any leaving functions.
    *
    * @param aNavigationControlContainer container control.
    * @param aDecoratedControl control to be decorated.
    * @return Navigation decorator object that contains decorated object.
    */
	IMPORT_C static CAknNavigationDecorator* NewL(
        CAknNavigationControlContainer* aNavigationControlContainer, 
        CCoeControl* aDecoratedControl, TControlType aType = ENotSpecified);
    
    /**
    * Destructor.
    */
	IMPORT_C ~CAknNavigationDecorator();

    /**
    * Returns control inside navigation decorator object. Ownedship of the control
    * is not changed.
    *
    * @return Control that is decorated with the decorator.
    */
	IMPORT_C CCoeControl* DecoratedControl();

    /** 
    * Shows or hides navigation arrows at the both ends of the navigation pane
    * when current object is shown.
    *
    * @param aVisible boolean value if navigation arrows are shown with the decorated control.
    */
	IMPORT_C void MakeScrollButtonVisible(TBool aVisible);
    
    /** 
    * State of the visibility of navigation arrows with the object.
    *
    * @return Boolean value if navigation arrows are visible or not.
    */
	IMPORT_C TBool ScrollButtonVisible() const;
    
    /** 
    * Sets navigation arrow dimmed (and highlighted). Arrows has to be visible that the dimmed arrow
    * is shown on the screen.
    *
    * @param aButton navigation arrow to be set (ELeftButton or ERightButton)
    * @param aDimmed ETrue is the button is dimmed, EFalse if the button is set highlighted.
    */
	IMPORT_C void SetScrollButtonDimmed(TScrollButton aButton, TBool aDimmed);
    
    /**
    * Is button dimmed or highlighted.
    *
    * @param aButton navigation arrow.
    * @return ETrue if the navigation arrow is dimmed, EFalse if it is highlighted.
    */
	IMPORT_C TBool IsScrollButtonDimmed(TScrollButton aButton) const;
    
    /**
     * Set type of the decorated control.
     * @param aType type of the control.
     */
    IMPORT_C void SetControlType(TControlType aType);
    
    /**
     * Returns type of the decorated control.
     * @return control type.
     */
    IMPORT_C TControlType ControlType() const;
 
    /**
    * Sets observer for navigation decorator events in the decorated control
    * @param aObserver pointer to observer
    */
    IMPORT_C virtual void SetNaviDecoratorObserver( MAknNaviDecoratorObserver* aObserver);

    void SetNaviStack(CAknNavigationControlContainer* aContainer);

    /**
    * From CCoeControl
    * handle pointer events
    *
    * @param aPointerEvent pointer event to be handled
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    
    enum TAknNaviControlLayoutStyle
        {
        ENaviControlLayoutNormal = 0x1,
        ENaviControlLayoutNarrow = 0x2        
        };

    enum TAknNaviControlLayoutMode
        {
        ENaviControlLayoutModeAutomatic = 0x400,
        ENaviControlLayoutModeForced = 0x800        
        };

        
    /**
    * Sets the layout style for this objects decorated control
    * Layout style can be normal or narrow style.
    *
    * Style is really applied if the decorated control supports it 
    * or if the layout mode has been set to forced mode 
    * (ENaviControlLayoutModeForced). Addtionally 
    * narrow mode may not be supported at all in some statuspane 
    * configurations (even if forced). 
    * 
    * Wheter decorated control supports or does not support given style
    * at the currently active statuspane layout can be queried using 
    * NaviControlLayoutStyleSupported() method.
    * 
    * @since 3.0     
    * @param aStyle Can be either normal (ENaviControlLayoutNormal)
    * or narrow style (ENaviControlLayoutNarrow)
    *
    */
    IMPORT_C void SetNaviControlLayoutStyle(TAknNaviControlLayoutStyle aStyle);

    /**
    * Gets the current layout style of this objects decorated control.
    * (ENaviControlLayoutNormal or ENaviControlLayoutNarrow)
    *
    * @since 3.0     
    * @return Current layout style of the navicontrol
    */
    IMPORT_C TAknNaviControlLayoutStyle NaviControlLayoutStyle();

    /**
    * Tells if decorated control supports given layout style at
    * the current statuspane layout. For ENotSpecified type of
    * controls this always returns EFalse (just for safety) because 
    * their impelemntation is not known.
    *
    * @since 3.0     
    * @return ETrue if the control supports given layout style. 
    *         Otherwise returns EFalse.
    */
    IMPORT_C TBool NaviControlLayoutStyleSupported(TAknNaviControlLayoutStyle aStyle);

    /**
    * Sets the layout mode ENaviControlLayoutModeAutomatic or 
    * ENaviControlLayoutModeForced.
    *
    * Layout mode ENaviControlLayoutModeAutomatic is the default
    * and it lets UI framework to decide the proper layout style
    * which is applied to decorated controls in all situations.
    *
    * Layout mode ENaviControlLayoutModeForced can be used to lock
    * the layout style to the current style if the application does
    * want to show only the other style.
    *
    * @since 3.0     
    * @param aMode New layout mode.
    *
    */
    IMPORT_C void SetNaviControlLayoutMode(TAknNaviControlLayoutMode aMode);
    
    /**
    * Gets the current layout mode of decorated control. Can be 
    * ENaviControlLayoutModeAutomatic (default) or 
    * ENaviControlLayoutModeForced (usually set by the application).
    *
    * @since 3.0     
    * @return Current layout mode of decorated control.
    *
    */
    IMPORT_C TAknNaviControlLayoutMode NaviControlLayoutMode();
        

protected: // from CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl. Returns number of controls inside the context pane control.
    * @return Number of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * From CCoeControl. Returns a control determined by control id.
    * @param anIndex Index of a control to be returned.
    * @return Pointer to control
    */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

protected: // from MCoeControlObserver

    /**
    * From MCoeControlObserver.
    * @param aControl Control that caused the event.
    * @param aEventType Type of the event.
    */
    IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

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
    * Gets the default rect of given controltype realtive to navipane in 
    * normal layoutstyle (ENaviControlLayoutNormal)
    *
    * @internal   
    * @param aControlType The navicontrol type which deafult rect is asked
    * @return Rectangle which is tells the default area for given controltype. 
    *         Coordinates are relative to navipane.
    * 
    */
    static TRect DecoratedControlRect(TInt aControlType);


    /**
    * Gets the default rect of given controltype realtive to navipane in 
    * narrow layoutstyle (ENaviControlLayoutNarrow)
    *
    * @internal   
    * @param aControlType The navicontrol type which deafult rect is asked.
    * @return Rectangle which is tells the default area for given controltype. 
    *         Coordinates are relative to navipane.
    * 
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
    * This method initializes timer that is used for times layout style changes.
    */
    void InitLayoutStyleTimer();

    /**
    * This method cancels timer that is used for times layout style changes.
    */
    void CancelLayoutStyleTimer();    

    /**
    * This method is executed when timer that is used for times layout style changes
    * expires.
    */
    static TInt LayoutStyleEvent(TAny * aPtr);

    /**
    * This method is executed when timer that is used for times layout style changes
    * expires.
    */
    void DoLayoutStyleEvent();
    
    
protected:
	CCoeControl* iDecoratedControl;
	CAknNavigationControlContainer* iContainer;
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

    TInt iSpare[2];
	};

#endif // AKNNAVIDE_H
