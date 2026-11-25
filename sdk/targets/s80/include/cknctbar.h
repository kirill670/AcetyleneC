/*
* ==============================================================================
*  Name        : cknctbar.h
*  Part of     : CKON
*  Interface   : Control Bar API
*  Description : The CCknControlBar class implements a visible controller for adjusting 
*                  for example volume control.
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


#ifndef CKNCTBAR_H
#define CKNCTBAR_H

// INCLUDES
#include <coecntrl.h>
#include <eikbctrl.h>
#include <gulicon.h>

#include <eikon.hrh>

// FORWARD DECLARATIONS
class CCknControlBarExt;

// CLASS DECLARATIONS
/**
 * The <code>CCknControlBar</code> class implements a visible controller for 
 * adjusting settings, for example, a volume control.The Control bar is constructed 
 * of multiple colored blocks, which appear when the Control Bar value is 
 * increased and disappear when the Control Bar value is decreased.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknControlBar : public CCoeControl
    {
    public:
    /** 
        * The <code>SControlBarData</code> structure defines the Control Bar
        * size and maximum value. 
        */
    struct SControlBarData
        {
        /** the Control Bar width in pixels */ 
        TInt iWidth;
        /** the Control Bar height in pixels */
        TInt iHeight;
        /** 
        * the upper limit, that is, the value at which the Control Bar is 
        * filled. The default value is one 
        */
        TInt iFinalValue;
        };

        /** 
        * The <code>SInfo</code> structure defines the appearance of the text
		* displayed on the control bar
        */
    struct SInfo
        {
        /** 
        * the minimum block size in pixels. The minimum block size is 
        * set to zero 
        */
        TInt iBlockMinimumSize;
        /** 
        * the text representation of progress as defined in 
        * <code>TEikProgressTextType</code> (eikon.hrh)
        */
        TEikProgressTextType iTextType;
        /** 
        * the color of the progress text that overwrites the filled part of 
        * the Control Bar 
        */
        TRgb iFillTextColor;
        /** 
        * the color of the progress text that overwrites the unfilled part of 
        * the Control Bar 
        */
        TRgb iEmptyTextColor;
        /** the font to use when drawing progress text */
        const CFont* iFont;
        };

        /**
        * Constructs a new control bar
        * 
        * @return a freshly allocated Control Bar. The framework calls
        *        <code>ConstructL()</code> on this object to complete the 
        *        second phase of construction
        * @remarks
        * @see
        */
        IMPORT_C static CCknControlBar* NewL();
        
        /**
        * Constructs a new control bar
        *
        * @param aData Defines a Control Bar size and maximum value
        * @param aHorizontalLayout Whether the Control Bar layout is horizontal
        * @return a freshly allocated Control Bar. The framework calls
        *        <code>ConstructL()</code> on this object to complete the 
        *        second phase of construction
        * @remarks SControlBarData structure will be initialised to zero,
		*		   SInfo structure will be set the texttype to EEikProgressTextNone,
		*		   sets the text color and font to control's environment font and color
		*		   and minimum block size to zero	
        * @see
        */
        IMPORT_C static CCknControlBar* NewL(const SControlBarData& aData, TBool aHorizontalLayout=ETrue);
        
        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C CCknControlBar();//this should be protected - use NewL for construction
        
        /**
        * The object constructor.
        *
        * @param aData Defines a Control Bar size and maximum value
        * @param aHorizontalLayout Whether the Control Bar layout is horizontal
        * @remarks
        * @return
        */
        IMPORT_C CCknControlBar(const SControlBarData& aData, TBool aHorizontalLayout=ETrue);//this should be protected - use NewL for construction

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknControlBar();    

        /**
        * Increments the slider bar value by <code>aInc</code> and draws the 
        * object.
        *
        * @param aInc The increment step
        * @remarks
        * @see
        */
        IMPORT_C void IncrementAndDraw(TInt aInc);

        /**
        * Sets a new value for the slider bar and draws the object.
        *
        * @param aValue The new value for the slider bar. It must be between 0 
        *               and <code>iData.iFinalValue</code>
        * @remarks The value passed outside the range will be rounded
		*          off to the minimum/maximum limits
        * @see
        */
        IMPORT_C void SetAndDraw(TInt aValue);

        /**
        * Constructs a Control Bar from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>CONTROLBAR</code>
        * @see <code>CCoeControl</code> (coecntrl.h)
		*      <code>TResourceReader</code> (barsread.h)
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Sets the  maximum value of the Control bar.
        *
        * @param aFinalValue The maximum value of the Control bar 
        * @remarks
        * @see 
        */
        IMPORT_C void SetFinalValue(TInt aFinalValue);

        /**
        * The Control Bar no longer uses an icon. Method is deprecated.
        * @deprecated
        * @param aIcon Bitmap.
        * @param aInternalOwnership If <code>ETrue</code>, delete <code>aIcon</code>.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetIcon(CGulIcon* aIcon, TBool aInternalOwnership=EFalse);//deprecated

        /**
        * Gets the current value of the Control bar.
        *
        * @return the current value of the Control bar 
        * @remarks 
        * @see
        */
        inline TInt CurrentValue() const { return(iCurrentValue); }

        /**
        * Sets the appearance of the control bar
        * 
        * @param aInfo contains information like minimum block size,  
		*			   progress texttype,text color and font
        * @remarks
        * @see
        */
	
        IMPORT_C void SetInfo(const SInfo& aInfo);

        /**
        * Sets the width, height, and maximum value of the Control Bar.
        * 
        * @param aData the Control Bar size and maximum value.
        * @remarks
        * @see
        */
        IMPORT_C void SetData(const SControlBarData& aData);

        /**
        * Gets the the appearance of the control bar
        *
        * @return a reference to the appearance of the control bar
        * @remarks
        * @see
        */
        IMPORT_C const SInfo& Info() const;

    public: 
        /**
        * Sets the Control Bar as ready for drawing.
        * 
        * @remarks
        * @see <code>CCoeControl</code> (coecntrl.h)
        */
        IMPORT_C void ActivateL();

        /**
        * Sets the size and position of the contents of the Control Bar after a 
        * resize.
        *
        * @remarks
        * @see <code>CCoeControl</code> (coecntrl.h)
        */
        IMPORT_C void SizeChanged();

        /**
        * Gets the minimum size for the Control Bar.
        * 
        * @return the minimum size of the Control Bar
        * @remarks
        * @see <code>CCoeControl</code> (coecntrl.h)
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code> (coecntrl.h)
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A <code>TInt</code> ID of the resource that has changed
        *              
        * @return
        * @remarks
        * @see <code>CCoeControl</code> (coecntrl.h)
        */
        IMPORT_C void HandleResourceChange(TInt aType);
    protected: 
        /**
        * From CCoeControl.
        * Handles pointer events.
        * @param aPointerEvent The pointer event
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        /**
        * From CCoeControl.
        * Draws the control on request.
        * @param aRect Optional. If supplied, the rectangle in which to draw the control.
        */
        IMPORT_C void Draw(const TRect& aRect) const;
    protected:
        /**
        * Second phase constructor.
        */
        void ConstructL();

    protected:
        /**
        * Evaluates and formats the text.
        * @param aTextBuf Text for evaluation.
        * @return Pointer to formatted text.
        */
        IMPORT_C virtual const TDesC* EvaluateText(TDes& aTextBuf) const;
        /**
        * Calculates Control bar blocks number.
        */
        void CalculateNumBlocks();

    private: // internal use
        void CheckSizeCalculated();
        void DrawBlock(CWindowGc& aGc,const TRect& aBlock,const TRgb aBlockColor,const TBool aDrawBlock=ETrue) const;
        CFbsBitmap* CreateBlockBitmapL(const TSize& aBlockSize) const;
        void DrawHorizSlider(CWindowGc& aGc,const TRect& aInvalidRect) const;
        void DrawVertSlider(CWindowGc& aGc,const TRect& aInvalidRect) const;
        TRect CalculateUpdatedRect(TInt aStartValue, TInt aEndValue);

        void GetColors();
        TBool CheckCreateExtension();
    private:
    struct SControlBarColors
        {
        TRgb iBlock;            // block color
        TRgb iBackground;       // background colour
        TRgb iOutlineShadow;    // bottom & right edge colour
        TRgb iOutlineHighlight; // top & left edge colour
        TRgb iSpare1;           // BC 
        TRgb iSpare2;           // BC 
        };
    enum TFlags { EVerticalLayout=1, EIconOwnedInternally=2 };
        SControlBarData iData;
        SControlBarColors iColors;

        TInt    iCurrentValue;
        TInt    iFlags;
        TPoint  iSliderPos;
        TPoint  iIconPos;
        TInt    iBlockGap;
    
        CCknControlBarExt* iExt;
    };


#endif  // CKNCTBAR_H

// End of File
