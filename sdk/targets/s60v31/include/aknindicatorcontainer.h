/*
* ============================================================================
*  Name     : aknindicatorcontainer.h
*  Part of  : AVKON
*
*  Description:
*       A default control in the status pane's small indicator pane.
*       Editor indicators uses also same control in the navigation pane and
*       in queries.
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

#ifndef AKNINDICATORCONTAINER_H
#define AKNINDICATORCONTAINER_H

//  INCLUDES
#include <AknControl.h>
#include <eikspane.h>

class CIncallStatusBubble;
class CAknIndicator;
class CAknIndicatorContainerExtension;
class CAknPictographInterface;
class MAknIndicatorObserver;

/**
 * A default control in the status pane's small indicator pane.
 */
class CAknIndicatorContainer : public CAknControl, public MEikStatusPaneObserver
	{
public:
    
    enum TLayoutOrientation
        {
        EVertical,
        EHorizontal
        };

    enum TIndicatorAlignment
        {
        ELeft,
        ERight
        };
    
    enum TIndicatorContext
        {
        EUniversalIndicators = 0,
        ENaviPaneEditorIndicators,
        EQueryEditorIndicators,
        EFindIndicators
        };

    enum TIndicatorPosition
        {
        ELeftSide,
        ERightSide,
        EMiddle
        };
        
    enum TCustomIndicatorFlags
    	{
    	EMultiColorIndicator       = 0x1,	
    	EIndicatorPositionInverted = 0x2	
    	};    

    enum TLayoutMode
		{
		ELayoutModeUsual,
		ELayoutModeWide
		};


public:
    /**
    * Constructor. Creates EUniversalIndicators object.
    */
    IMPORT_C CAknIndicatorContainer();

    /**
    * Constructor. Creates EUniversalIndicators, ENaviPaneEditorIndicators or
    * EQueryEditorIndicators object.
    *
    * @param aIndicatorContext Indicator container context.
    */
    IMPORT_C CAknIndicatorContainer(TInt aIndicatorContext);

    /**
    * Destructor.
    */
    IMPORT_C ~CAknIndicatorContainer();

    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL();
    
    /**
    * Sets indicator state. The state can be one of the following: EAknIndicatorStateOff,
	* EAknIndicatorStateOn or EAknIndicatorStateAnimate. Editor indicators
    * do not support animation.
    *
    * @param aIndicatorId ID of the indicator to be modified.
    * @param aState A state to be set to the indicator.
    * @param aDrawNow A flag to indicate if the indicator is redrawn with this call.
    */
    IMPORT_C void SetIndicatorState(TUid aIndicatorId, TInt aState, TBool aDrawNow = ETrue);

    /** 
    * Return a current state of the indicator.
    *
    * @param aIndicatorId ID of the indicator.
    * @return Current state of the indicator.
    */
    IMPORT_C TInt IndicatorState(TUid aIndicatorId);
    
    /** 
    * Sets value to the message length indicator 
    * (EAknNaviPaneEditorIndicatorMessageLength).
    *
    * @param aIndicatorId ID of the indicator to be modified.
    * @param aString Value of the indicator.
    */
    IMPORT_C void SetIndicatorValueL(TUid aIndicatorId, const TDesC& aString);

    /** 
    * Sets value to the incall status bubble indicator on the top of the status pane.
    *
    * @param aFlags Mode of the bubble.
    */
    IMPORT_C void SetIncallBubbleFlags(const TInt& aFlags);
    
    /** 
    * Constructs the object from resource.
    *
    * @param aReader Resource reader.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /** 
    * Return the context of the indicator.
    *
    * @return context of the indicator.
    */
    IMPORT_C TInt IndicatorContext() const;


public: // From MEikStatusPaneObserver
    /**
    * From MEikStatusPaneObserver. The MEikStatusPaneObserver interface allows
    * a status pane observer to pick up changes in the size or position of 
    * the status pane. Such events will be as a result of layout changes which 
    * cause an actual change in the status pane rectangle.
    */
    IMPORT_C void HandleStatusPaneSizeChange();

public: // From CCoeControl
    /**
    * From CCoeControl.     
    * Handles pointer events
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
protected: // From CCoeControl

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. color scheme change.
     * Responds fade events and fades incall status bubble window group.
	 * @param aType Event type.
	 */
   	IMPORT_C virtual void HandleResourceChange(TInt aType);

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl. Handle the position change events.
    */
    IMPORT_C virtual void PositionChanged();

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
    
private: // From CCoeControl
    IMPORT_C virtual void Draw(const TRect& aRect) const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
    virtual void Reserved_1();  
    void PrioritizeIndicatorsL();
    
   	static TInt TickerCallback(TAny* aThis);
    TInt DoTick();

    void IncallBubbleSizeChanged(TBool aAllowIdleStateBubble);

    /**
    * Returns autolock state. 
    *
    * @return Return 1 if autolock application is in the front, 0 otherwise.
    */
    TInt AutolockState();

    void SizeChangedInSmallStatusPane();

    void SizeChangedInNormalStatusPane();

    void SizeChangedInStaconPane();

    void SizeChangedInFlatStatusPane();

    void SizeChangedInExtendedStatusPane();

    void SizeChangedInIdleExtendedStatusPane();

	void SizeChangedInIdleVertical();

    void SetContainerWindowNonFading(TBool aNonFading);    

    void SetupIndicatorLayoutModes();

public: 

   /** 
    * Sets value to the progress bar indicator 
    * (EAknNaviPaneEditorIndicatorProgressBar). 
    * Panics if this is not progress bar indicator.
    * 
    * @since 2.1
    * @param aIndicatorId ID of the indicator to be modified.
    * @param aValue current progress of the task that bar describes.
    * @param aMaxValue progress value when task is finished.
    *
    */
    IMPORT_C void SetIndicatorValue(TUid aIndicatorId, TInt aValue, TInt aMaxValue);

    /**
    * Redraws those indicators that are visible and contain pictographs.
    */
    void DrawPictographArea();

    /**
    * Returns the pictograph interface owned by the indicator container,
    * or NULL if pictographs are not supported.
    */
    CAknPictographInterface* PictographInterface() const;


    /** 
    * Sets wheter incall bubble is shown also on the top of the idle status pane.
    * Normally it is shown only in usual statuspane layouts, but with this
    * method it can be set to shown also in idle.
    *
    * NOTE: This method works only if indicatorcontainer is used as container for 
    *       universalindicators.
    *
    * @param aAllowed If true incall bubble is shown also in idle statuspane. Otherwise
    *                 bubble is shown only in usual statuspane layouts.
    */
    IMPORT_C void SetIncallBubbleAllowedInIdle(TBool aAllowed);

    /** 
    * Sets wheter incall bubble is shown on the top of the usual status pane.
    * Normally it is shown in usual statuspane layouts, but with this
    * method it can prevent it to be shown.
    *
    * NOTE: This method works only if indicatorcontainer is used as container for 
    *       universalindicators.
    *
    * @param aAllowed If true incall bubble is shown in usual statuspane. 
    *
    */
    IMPORT_C void SetIncallBubbleAllowedInUsual(TBool aAllowed);


   /**
    * Sets observer for given indicator.
    *
    * @param aIndicatorObserver observer of indicator
    * @param aIndicatorUid uid of indicator to be observed
    */
    IMPORT_C void SetIndicatorObserver(MAknIndicatorObserver* aIndicatorObserver, TUid aIndicatorUid);

   /**
    * Creates a custom indicator. Indicators created with this method can be used in addition
    * to default indicators.
    *
    * @since 3.1
    *
    * @param aIndicatorResourceId Resource id of INDICATOR struct to be used in costructing indicator. 
    *        	Uid in the resource is ignored, a dynamic uid is given to indicator and returned 
    *           to caller. 
    *
    * @param aCustomIndicatorFlags Flags that can be used to set additional indicator properties.
    *
    *        EMultiColorIndicator:  Indicator is shown as multicolor (default is 2-color).
    *
    *  	     EIndicatorPositionInverted: Indicator is aligned to the opposite side than default 
    *            (default is right side). Note that this flag does not quarantee exact location 
    *            for the indicator, indicators are shown in priority order and location may vary 
    *            and look different in different layouts.			
    *
    * @return Uid of the new indicator.
    *
    */
	IMPORT_C TUid CreateIndicatorFromResourceL(TInt aIndicatorResourceId, TInt aCustomIndicatorFlags);


   /**
    * Replaces the icon of the given indicator.
    *
    * @since 3.1
    * @param aIndicator   Uid of the indicator
    * @param aState       State which icon is replaced (EAknIndicatorStateOn or EAknIndicatorStateAnimate)
    * @param aLayoutMode  Layout mode of the icon to be replaced (ELayoutModeUsual or ELayoutModeWide)
    * @param aIconBitmap  Bitmap of the new icon. Ownership is transferred to CAknIndicatorContainer.
    * @param aIconMask    Mask of the new icon. Ownership is transferred to CAknIndicatorContainer.
    * @param aIconIndex   If parameter aState is EAknIndicatorStateAnimate, then this parameter must contain
    *                     the index of the icon to be replaced in the animation sequence. Old icon must exist 
    *                     for given index so that the number of animation frames does not change.
    */
	IMPORT_C void ReplaceIndicatorIconL(TUid aIndicator, TInt aState, TInt aLayoutMode, CFbsBitmap* aIconBitmap, CFbsBitmap* aIconMask, TInt aIconIndex = 0);

private:
    
   	typedef CArrayPtrFlat<CAknIndicator> CAknIndicatorQueue;
    CAknIndicatorQueue* iIndicators;
    TLayoutOrientation iLayoutOrientation;
    TLayoutOrientation iPreviousLayoutOrientation;
    
    TIndicatorAlignment iAlignment;
    
    TInt iIndicatorsShown;
    TInt iAnimatedIndicatorsShown;
    CAknIndicatorContainerExtension* iExtension; 
    TInt iIndicatorContext;
    
   	CPeriodic* iTicker;
    TBool iSpare2;  // Reserved for future use.
    TInt iSynchronizingValue;
    
    CIncallStatusBubble* iIncallBubble;
    };


// AKNINDICATORCONTAINER_H
#endif

// End of File
