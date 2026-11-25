/**
* ==============================================================================
*  Name        : cknvolumebar.h
*  Part of     : CKON
*  Interface   : Volume Bar API
*  Description : Volume bar widget class
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

#ifndef CKNVOLUMEBAR_H
#define CKNVOLUMEBAR_H

//  INCLUDES
#include <coecntrl.h>
#include <cknbctrl.h>

// FORWARD DECLARATIONS
/**
 * The <code>CCknSliderThumb</code> class implements thumb that
 * the user can drag to increase and decrease the volume level.
 *
 * @lib cknctl.lib
 * @since Series 90 1.0
 */
class CCknSliderThumb;

/**
 * The <code>CFocusChangeCbaUpdater</code> class implements to update 
 * the CBA when control gains or losses focus.
 *
 * @lib cknctl.lib
 * @since Series 90 1.0
 */
class CFocusChangeCbaUpdater;

// CLASS DECLARATION

/**
 * The <code>MCknSliderCustomDrawBase</code> class implements an interface
 * for containers of slider controls that require a custom draw. Classes that
 * contain a slider control may need to inherit this so that the slider
 * component controls can request a custom draw.
 *
 * @lib cknctl.lib
 * @since Series 90 1.0
 */
class MCknSliderCustomDrawBase
    {
    public:

       /**
        * Custom draw function. Called by a slider control when it requires 
        *its background area to be redrawn.
        *
        * @param aGc The graphics context
        * @param aRect The rectangle to draw in
        * @remarks
        * @see <code>CWindowGc</code> in win32std.h
        * @see <code>TRect</code> in e32std.h 
        */
        virtual void DrawBackground(CWindowGc& aGc, const TRect& aRect)=0;

        /**
        * Unused.
		* @internal
        */
        virtual void Reserved_1() {};

        /**
        * Unused.
		* @internal
		*/
        virtual void Reserved_2() {};
    };

/**
 * The <code>CCknVolumeBar</code> implements a Volume Bar control.
 * The Volume Bar allows volume to be increased or decreased within a 
 * pre-defined range. There are three versions of Volume Bar: horizontal, 
 * vertical and toolbar. Volume Bar provides a large thumb control that can be 
 * dragged within the control.
 *
 * @lib cknctl.lib
 * @since Series 90 1.0
 */
class CCknVolumeBar : public CCknBorderedControl
    {

    public: // Data types
       /**
        * The enumeration <code>TCknVolumeBarMode</code> specifies the mode in 
		* which the Volume Bar is displayed.
        */
        enum TCknVolumeBarMode
            {
            /** horizontal mode */
            EHorizontal,
            /** vertical mode */
            EVertical,
            /** toolbar mode */
            EToolbar
            };

    public:  // Methods

    // Constructors and destructor

       /**
        * Creates a volume bar control 
		*
		* Allocates and constructs a Volume Bar control.
        *
        * @param aContainer The container which is used for custom draw - must
        *                   not be null
        * @param aMinVolume The lower limit for the volume - negative values
        *                   are valid
        * @param aMaxVolume The upper limit for the volume - negative values
        *                   are valid. May be less than the lower limit if a
        *                   negative range is required, and must not be equal
        *                   to <code>aMinVolume</code>
        * @param aGranularity The smallest volume change size - must be
        *                     greater than 0 and smaller than the range
        * @param aHorizontal If this is <code>ETrue</code>, the Volume Bar
        *                    orientation will be horizontal. Otherwise, it will
        *                    be vertical
        * @param aShowMuteIcon Determines whether the mute icon is shown within
        *                      the control
        * @return pointer to the newly constructed object
        * @remarks
        * @see
        */
        IMPORT_C static CCknVolumeBar* NewL(MCknSliderCustomDrawBase* aContainer,TInt aMinVolume,TInt aMaxVolume,TInt aGranularity=1,TBool aHorizontal=ETrue,TBool aShowMuteIcon=ETrue);

       /**
	    * Creates a volume bar control 
		*
        * Allocates and constructs a Volume Bar control.
        *
        * @param aContainer The container which is used for custom draw - must
        *                   not be null
        * @param aMode The mode of Volume Bar to construct
        * @param aMinVolume The lower limit for the volume - negative values
        *                   are valid
        * @param aMaxVolume The upper limit for the volume - negative values
        *                   are valid. May be less than the lower limit if a
        *                   negative range is required, and must not be equal
        *                   to <code>aMinVolume</code>
        * @param aGranularity The smallest volume change size - must be
        *                     greater than 0 and smaller than the range
        * @param aShowMuteIcon Determines whether the mute icon is shown
        *                      within the control
        * @return pointer to the newly constructed object
        * @remarks
        * @see
        */
        IMPORT_C static CCknVolumeBar* NewL(MCknSliderCustomDrawBase* aContainer,TCknVolumeBarMode aMode,TInt aMinVolume,TInt aMaxVolume,TInt aGranularity=1,TBool aShowMuteIcon=ETrue);

       /**
        * Creates a volume bar control. 
		*
		* Default <code>NewL</code> method used to construct from resources.
        *
        * @return pointer to the newly constructed object
        * @remarks
        * @see
        */
        IMPORT_C static CCknVolumeBar* NewL();

       /**
        * The object destructor.
        */
        IMPORT_C ~CCknVolumeBar();


    // New methods

       /**
        * Sets the Volume Bar to a new position and redraws.
        *
        * @param aNewVolume The volume to set. If it is not divisible by the
        *                   granularity, the volume will be set to the nearest
        *                   value. If it is outside the volume range, the
        *                   volume will be set to the nearest limit
        * @remarks
        * @see
        */
        IMPORT_C void SetVolume(TInt aNewVolume);

       /**
        * Increases or decreases the volume by the specified amount and then
        * redraws.
        *
        * @param aVolumeAdjustment The amount to increase by. Negative values
        *                          decrease the volume. If not divisible by the
        *                          granularity, the volume will be set to the
        *                          nearest value. If the new volume lies
        *                          outside the volume range, it will be set to 
        *                          the nearest limit
        * @remarks
        * @see
        */
        IMPORT_C void IncreaseVolume(TInt aVolumeAdjustment);

       /**
        * Gets the current volume level setting.
        *
        * @return the current volume
        * @remarks
        * @see
        */
        IMPORT_C TInt Volume();

       /**
        * Mutes or un-mutes the Volume Bar. Muting puts mute icon to 
		* voice inactive state,but does not dim the thumb, Volume Bar
		* or increase/decrease button; these remain available for 
		* volume adjustment whilst muted
        * @param aMute <code>ETrue</code> to mute, <code>EFalse</code>
        *                    to un-mute
        *
        * @remarks Triggers a full redraw including background.
		*          Valid to call this function even if no Mute icon
		*          is displayed
        * @see
        */
        IMPORT_C void SetMute(TBool aMute);

       /**
        * Gets the current mute icon setting.
        *
        * @return whether the Volume Bar is muted
        * @remarks Valid to call this function even if no Mute icon
		*          is displayed
        * @see
        */
        IMPORT_C TBool IsMute();

       /**
        * Changes the lower volume limit. Current volume is not changed unless
        * it is caused to be outside the volume range, in which case it is set
        * to the new lower limit.
        *
        * @param aMinVolume The lower volume limit - negative values are 
        *                   permitted
        * @remarks
        * @see
        */
        IMPORT_C void SetMinVolume(TInt aMinVolume);

       /**
        * Gets the current minimum volume.
        *
        * @return the lower volume limit
        * @remarks
        * @see
        */
        IMPORT_C TInt MinVolume();

       /**
        * Changes the upper volume limit. Current volume is not changed unless
        * it is caused to be outside the volume range, in which case it is set
        * to the new upper limit.
        *
        * @param aMaxVolume The upper volume limit - negative values are 
        *                   permitted
        * @remarks
        * @see
        */
        IMPORT_C void SetMaxVolume(TInt aMaxVolume);

       /**
        * Gets the current maximum volume. 
        *
        * @return the upper volume limit
        * @remarks
        * @see
        */
        IMPORT_C TInt MaxVolume();


    // Methods from base classes

       /**
        * Set the control's container window. <code>CCknVolumeBar</code> is not 
        * a window-owning control. This method must therefore be called by the 
        * containing application.
        *
        * @param aContainer The container
        * @remarks
        * @see <code>CCoeControl</code> in coecntl.h 
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);

       /**
        * Constructs the control from resource.
        *
        * @param aReader A resource reader
        * @remarks
        * @see <code>CCoeControl</code> in coecntl.h
        * @see <code>TResourceReader</code> in barsread.h
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

       /**
        * Activates this control.
        * 
        * @remarks
        * @see <code>CCoeControl</code> in coecntl.h
        */
        IMPORT_C void ActivateL();

       /**
        * Gets the minimum size for the control.
        * 
        * @return the minimum size of the control
        * @remarks
        * @see <code>CCoeControl</code> in coecntl.h
        */
        IMPORT_C TSize MinimumSize();

       /**
        * Sets whether the control is dimmed or undimmed.
        *
        * @param aDimmed The dimmed value
        * @remarks
        * @see <code>CCoeControl</code> in coecntl.h
        */
        IMPORT_C void SetDimmed(TBool aDimmed);


    protected:  // Methods

    // New Methods

        /**
        * C++ constructor
        */
        IMPORT_C CCknVolumeBar();

        /**
        * C++ constructor
        *
        * @param aContainer the container
        * @param aMinVolume the minimum volume
        * @param aMaxVolume the maximum volume
        * @param aGranularity The granularity in the scale
        * @param aHorizontal ETrue if the control is drawn horizontally, EFalse otherwise
        * @param aShowMuteIcon ETrue if the mute icon is to be shown
        */
        IMPORT_C CCknVolumeBar(MCknSliderCustomDrawBase* aContainer,TInt aMinVolume,TInt aMaxVolume,TInt aGranularity,TBool aHorizontal,TBool aShowMuteIcon);

        /**
        * Symbian 2 phase constructor
        */
        void ConstructL();

        /**
        * Calculates size of the control
        */
        void CalculateSize();

        /**
        * Calculates the positions of control elements
        */
        void CalculatePositions();

        /**
        * Calculates the current volume from the thumb's pixel position
        * if (iMaxVolume-iMinVolume) is not perfectly divisible by granularity then
        * iVolume's range will be: iMinVolume <= iVolume < iMaxVolume
        */
        void SetCurrentVolumeFromThumb();

        /**
        * constucts the dimensions array should be called after bitmaps have been loaded
        * assumes the bitmaps in the horizontal Volume Bar mbm's are in identical order
        */
        void ConstructDimensions();

        /**
        * create bitmap and mask arrays.
        */
        void ConstructBitmapArraysL();

        /**
        * Draws the slider
        * @param aRect the rectangle in which to draw
        * @see <code>TRect</code> in e32std.h
        */
        void DrawSlider(const TRect& aRect) const;

        /**
        * Draws the mute icon
        */
        void DrawMuteIcon() const;

        /**
        * Draws the arrow element
        *
        * @param aArrowRect the rectangle in which to draw
        * @see <code>TRect</code> in e32std.h
        */
        void DrawArrow(const TRect& aArrowRect) const;

        /**
        * Sets up graphics context and draws arrow
        *
        * @see <code>TRect</code> in e32std.h
        */
        void DrawArrowNow(const TRect& aArrowRect) const;

        /**
        * Sets up and draws the thumb and background
        */
        void DrawThumbAndBackgroundNow();

    // Methods from base classes

        /**
        * From CCoeControl
        * Handles a pointer event
        *
        * @param aPointerEvent the pointer event to handle
        * @see <code>TPointerEvent</code> in w32std.h
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
         * From CCoeControl
         * Handles key events, allowed events: EKeyUpArrow, EKeyDownArrow if the Volume Bar is
         * displayed vertically; EKeyLeftArrow, EKeyRigthArrow if the Volume Bar is displayed
         * horizontally.
         *
         * @param aKeyEvent the occurred event
         * @param aType unused
         * @return A response
         * @see <code>TKeyEvent</code> in w32std.h
         * @see <code>TEventCode</code> in w32std.h
         **/
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * From CCoeControl
        * Draw the control
        *
        * @param aRect the rectangle in which to draw
        * @see <code>TRect</code> in e32std.h
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * From CCoeControl
        * Called when the control size is changed
        */
        IMPORT_C void SizeChanged();

        /**
        * From CCoeControl
        * Called when the control position is changed
        */
        IMPORT_C void PositionChanged();

        /**
        * From CCoeControl
        * Called when the focus of the control changes
        *
        * @param aDrawNow ETrue if the control should now be redrawn
        * @see <code>TDrawNow</code> in coedef.h
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * From CCoeControl
        * Called when a resource has changed
        *
        * @param aType the type of resource that has changed.
        */
        IMPORT_C void HandleResourceChange(TInt aType);

    private: //Methods

        /**
        * From CCoeControl
        * @return The number of components in this compound control.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl
        * Return a particular sub-component
        * @param aIndex the index of the sub-component
        * @return the sub-component
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * From CCoeControl
        * Process a command
        *
        * @param aObject The object that will actually process the command
        * @param aCommandId the command ID
        */
        static void ProcessCommandL(TAny* aObject, TInt aCommandId);

        /**
        * Actually process a command. Commands can be EEikIncreaseVolume, EEikDecreaseVolume or EEikMute.
        * @param aCommandId the command ID.
        */
        void ProcessCommand2L(TInt aCommandId);

    private:    // Data
        /** top or left depending on orientation */
        TRect iTlArrowRect;

        /** bottom or right depending on orientation */
        TRect iBrArrowRect;

        /** the rectangle for the mute icon */
        TRect iMuteIconRect;

        enum TButtonStatus
            {
            EUnpressed,
            EPressed,
            EDisabled
            };

        /** The status of this button */
        TButtonStatus iTlArrowStatus;

        /** The status of this button */
        TButtonStatus iBrArrowStatus;

        enum
            {
            ENone,
            ETlArrow,
            EBrArrow,
            EThumb
            } iPointerDownOn;

        /** the position of the pen down event */
        TPoint iPenDownPos;

        /** The container of this control */
        MCknSliderCustomDrawBase* iContainer;

        /** The volume at the left or top of the control */
        TInt iLeftTopVolume;

        /** The volume at the right or bottom of the control */
        TInt iRightBottomVolume;

        /** The size of the steps in the volume */
        TInt iGranularity;

        /** The current volume */
        TInt iVolume;

        /** Is the volume mute? */
        TBool iIsMute;

        /** Is the control to be drawn horizontally? */
        TBool iHorizontal;

        /** Is the mute icon to be shown? */
        TBool iShowMuteIcon;

        /** Is this to be a small bar? */
        TBool iSmallBar;

        /** The thumb component */
        CCknSliderThumb* iThumb;

        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iThumbHeight;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iThumbThickness;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iBackgroundHeight;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iArrowWidth;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iArrowHeight;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iMuteWidth;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iMuteHeight;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iSpaceLeftBorder;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iSpaceMuteToLArrow;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iSpaceRightBorder;
        /** the drawable length of the leftmost/topmost background bitmap */
        TInt iLengthOfFirstSliderBmp;
        /** the drawable length of the rightmost/bottommost background bitmap */
        TInt iLengthOfLastSliderBmp;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iLength;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iSliderLimitFromTl;
        /** dimensions - names assume horizontal slider but used for vertical slider as well */
        TInt iSliderLimitFromBr;

        /**
         * When the control gains or loses focus this member is responsible for updating
         * the CBA.
         */
        CFocusChangeCbaUpdater* iFocusChangeHandler;

        TUid iMbmUid;

        TBool iMbmDuplicated;

        /** unused */
        void *iReserved;
    };

#endif      // CKNVOLUMEBAR_H

// End of File
