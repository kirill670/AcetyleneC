/*
* ==============================================================================
*  Name        : eikprogi.h
*  Part of     : ckon
*  Interface   : Progress Bar API
*  Description : Progress Bar
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


#ifndef EIKPROGI_H
#define EIKPROGI_H

// INCLUDES
#include <eikbctrl.h>
#include <eikon.hrh>

// FORWARD DECLARATIONS
class TGulBorder;

/**
 * The <code>CEikProgressInfo</code> class provides a control that indicates 
 * the progress of an operation.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikProgressInfo : public CEikBorderedControl
    {
    public:

        /** 
        * The <code>SInfo</code> structure defines the parameters of the 
        * Progress Bar. 
        */
    struct SInfo
        {
        /** 
        * text representation of progress as defined in 
        * <code>TEikProgressTextType</code> in <code>eikon.hrh</code> 
        */
        TEikProgressTextType iTextType;
        /** the number of blocks into which the Progress Bar is divided */
        TInt iSplitsInBlock;
        /** 
        * the upper limit, that is, the value at which the Progress Bar is 
        * filled. Must be greater than zero 
        */
        TInt iFinalValue;
        /** the Progress Bar width in pixels */
        TInt iWidth;
        /** 
        * the Progress Bar height in pixels. If not specified, it is set to 
        * the current font height 
        */
        TInt iHeight;
        };

    /** The <code>SLayout</code> structure defines the appearance of the Progress Bar. */
    struct SLayout
        {
        /** the color of the filled part of the Progress Bar */
        TRgb iFillColor;
        /** the color of the unfilled part of the Progress Bar */
        TRgb iEmptyColor;
        /** 
        * the color of the progress text that overwrites the filled part of 
        * the Progress Bar 
        */
        TRgb iFillTextColor;
        /** 
        * the color of the progress text that overwrites the unfilled part of 
        * the Progress Bar */
        TRgb iEmptyTextColor;
        /** the font to use when drawing caption and progress text */
        const CFont* iFont;
        /** 
        * the separation between blocks. This is only used when 
        * <code>SInfo.iSplitsInBlock</code> is greater than zero 
        */
        TInt iGapBetweenBlocks;
        };

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikProgressInfo();

        /**
        * The default object constructor.
        *
        * @remarks If this constructor is used, the <code>iHeight</code> 
        *          field of the <code>SInfo</code> field must be set using 
        *          <code>SetInfo</code> before the Progress Bar is drawn,
        *          otherwise an unhandled divide-by-zero error occurs
        * @see
        */
        IMPORT_C CEikProgressInfo();

        /**
        * The object constructor.
        *
        * @param aProgInfo The information required for the Progress Bar
        * @remarks
        * @see
        */
        IMPORT_C CEikProgressInfo(const SInfo& aProgInfo);


        /**
        * Adds the specified increment to the current progress value and 
        * redraws the control. Calls <code>SetAndDraw()</code> to redraw the 
        * control, passing in the result of adding the specified increment to 
        * the current progress value as <code>aValue</code>.
        *
        * @param aInc The increment to add to the current progress value
        * @remarks This method, along with <code>SetAndDraw()</code>, is the 
        *          means by which the application updates the Progress Bar
        * @see
        */
        IMPORT_C void IncrementAndDraw(TInt aInc);

        /**
        * Redraws the control with the specified value as the new progress 
        * value. Called either directly from the application or by
        * <code>IncrementAndDraw()</code> 
        *
        * @param aValue The new progress value
        * @remarks This method, along with <code>IncrementAndDraw</code>, is 
        *          the means by which the application updates the Progress Bar.
        *          If <code>aValue</code> is bigger than 
        *          <code>SInfo.iFinalValue</code>, <code>aValue</code> is
        *          set to <code>SInfo.iFinalValue</code>
        * @see
        */
        IMPORT_C void SetAndDraw(TInt aValue);

        /**
        * Constructs a Progress Bar from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>PROGRESSINFO</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Sets the layout for the control.
        *
        * @param aLayout The layout for the control
        * @remarks
        * @see SLayout struct
        */
        IMPORT_C void SetLayout(const SLayout& aLayout);

        /**
        * Sets the control's border.
        *
        * @param aBorder The control's border. Values are defined in gulbordr.h
        * @remarks
        */
        IMPORT_C void SetBorder(const TGulBorder& aBorder);

        /**
        * Sets the final value, that is the upper limit, for the Progress Bar 
        * control. When the current value reaches this, following a call to
        * <code>SetAndDraw()</code> or <code>IncrementAndDraw()</code>, the 
        * Progress Bar is completely filled.
        *
        * @param aFinalValue The upper range limit for the Progress Bar
        * @remarks The value must be greater than 0 otherwise the application
        *          crashes with an unhandled divide-by-zero error
        * @see
        */
        IMPORT_C void SetFinalValue(TInt aFinalValue);

        /**
        * Sets the information required for a Progress Bar.
        *
        * @param aInfo The information required for the Progress Bar
        * @remarks
        * @see
        */
        IMPORT_C void SetInfo(const SInfo& aInfo);
    

        /**
        * Gets a reference to the <code>SInfo</code> struct used to define the 
        * Progress Bar.
        *
        * @return a reference to the <code>SInfo</code> data for the Progress 
        *         Bar
        * @remarks Returns a reference to the object's <code>SInfo</code> 
        *          struct, which can be updated and written back using 
        *          <code>SetInfo()</code>
        * @see
        */
        inline const SInfo& Info() const { return(iInfo); }

        /**
        * Gets a reference to the <code>SLayout</code> struct used to define 
        * the colors and layout of the Progress Bar.
        *
        * @return reference to the <code>SLayout</code> data for the Progress 
        *         Bar
        * @remarks Returns a reference to the object's <code>SLayout</code> 
        *          struct, which can be updated and written back using 
        *          <code>SetLayout()</code>
        * @see
        */
        inline const SLayout& Layout() const { return(iLayout); }

        /**
        * Gets the current value for how far the operation has progressed.
        *
        * @return The value for how far the operation has progressed with 
        *         respect to the final value. For example, a 
        *         <code>CurrentValue()</code> of <code>5</code> with 
        *         <code>SInfo.iFinalValue</code> of <code>10</code> means that
        *         the Progress Bar is half filled
        * @remarks
        * @see
        */
        inline TInt CurrentValue() const { return(iCurrentValue); }
    protected:

        /**
        * Gets the current value of the progress text.
        * 
        * @param aTextBuf The buffer from which the text is obtained
        * @return the control's text or  <code>NULL</code> if no text is used 
        * in the control
        * @remarks
        * @see
        */
        IMPORT_C virtual const TDesC* EvaluateText(TDes& aTextBuf) const;
    public: // from CCoeControl

        /**
        * Activates this control.
        * 
        * @remarks Informs the framework that the control is ready to be drawn
        * @see CCoeControl
        */
        IMPORT_C void ActivateL();

        /**
        * Gets the minimum size for the Progress Bar.
        * 
        * @return the minimum size needed to display the Progress Bar. Used,
        *         for example, to determine the size of a display rectangle 
        *         for it
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Called from the framework when the Progress Bar size changes.
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void SizeChanged();

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * Handles a change to the control's resources that are shared across 
        * the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource that 
        *              has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
    private: // from CCoeControl
        IMPORT_C void Draw(const TRect& aRect) const;
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2(); 
    private: // internal use
        void Construct();
        void CheckSizeCalculated();
    private:
        SInfo iInfo;
        SLayout iLayout;
        TInt iCurrentValue;
        TBool iHeightWasSupplied;
        CFbsBitmap* iBrushBitmap;
    };




#endif  // EIKPROGI_H

// End of File
