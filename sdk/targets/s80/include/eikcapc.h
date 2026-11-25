/*
* ==============================================================================
*  Name        : eikcapc.h
*  Part of     : CKON
*  Interface   : Label API
*  Description : Captioned controls used as lines in a dialog.
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

#ifndef EIKCAPC_H
#define EIKCAPC_H

// INCLUDES
#include <coecntrl.h>
#include <fepbase.h>
#include <eiklabel.h>
#include <gulicon.h>

// FORWARD DECLARATIONS
class CEikCapLabelExt;


/**
 * The CEikCapLabel is a class to display the text in a dialog line.
 * @internal
 * @lib eikdlg.lib
 * @since Series90 1.0
 */
class CEikCapLabel: public CEikLabel
    {
    public:

        /**
        * The default C++ object constructor
        */
        CEikCapLabel();

        /**
        * The object destructor.
        */
        ~CEikCapLabel();

        void SetIcon(CGulIcon* aIcon);
        CGulIcon* Icon();
        TBool Mandatory() const;
        void SetMandatory(TBool aMandatory);
    public: // from CCoeControl

        TSize MinimumSize();
    protected: // from CCoeControl

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C void Draw(const TRect& aRect) const;
        void DrawText(const TRect& aRect) const;
    protected:
        TBool iContainerDrawsBackground;
    private:
        void DrawMandatoryFieldIcon() const;
    private:
        TSize iMinSizeWithoutIcon;
		CGulIcon* iIcon;
		TBool iMandatory;
    };

/**
 * The CEikCaptionedControl is a class to contain a line on a dialog. 
 * It contains a label, a control and a trailer.
 * 
 * @internal
 * @lib eikdlg.lib
 * @since Series90 1.0
 */
class CEikCaptionedControl : public CCoeControl, public MCoeCaptionRetrieverForFep
    {
    public:
    enum TSpaceSharingFlags
        {
        EIfTooSmallCtlGetsWidthLast         =0x0,
        EIfTooSmallCtlGetsWidthFirst        =0x1,
        EIfTooSmallCtlGetsEqualShareOfWidth =0x2,
        EIfTooBigCtlStaysMinHeight          =0x4,
        EIfTooBigCtlStaysMinWidth           =0x8,
        EIfTooBigCtlStaysMinSize            =EIfTooBigCtlStaysMinHeight|EIfTooBigCtlStaysMinWidth
        };

    enum TCapCFlags
        {// must carry on from TSpaceSharingFlags
        EUsesEars               =0x000010,
        ELeftEarDown            =0x000020,
        ERightEarDown           =0x000040,
        ELeftEarGrab            =0x000080,
        ERightEarGrab           =0x000100,
        ECurrent                =0x000200,
        ESeparatorAfter         =0x000400,
        EExtraAscent            =0x000800,
        ELatent                 =0x001000,
        ELglf                   =0x002000,
        ETakesEnterKey          =0x004000,
        EOfferAllHotKeys        =0x008000,
        ETrailerAfterEar        =0x010000,
        EMandatoryInput         =0x020000,
        EAlignToControls        =0x040000,
        // caption vertical position is center to the control
        ECaptionPositionCenter  =0x080000,
        EStretchToFitRight      =0x100000,
        // Series80 to disable the arrow between the caption and the value
        ESeparatorDisabled      =0x200000
        };

    public:

        /**
        * The default C++ constructor.
        * <b>Note</b>: NewL should be used instead of the default constructor.
        */
        IMPORT_C CEikCaptionedControl();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikCaptionedControl();
    public: // new functions

        /**
        * Specifies that this captioned control has 'ears' on either side.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetUsesEars();

        /**
        * Specifies whether or not this captioned control should have ears.
        * @param aUsesEars ETrue if the control has ears. EFalse if not.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetUsesEars(TBool aUsesEars);

        /**
        * Sets the flags that determine the way space is distributed if
        * the captioned control is given too much, or too little, space
        * relative to its minimum size.
        *
        * @param aFlags The flags (see <code>TSpaceSharingFlags</code>)
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetSpaceSharingFlags(TInt aFlags);

        /**
        * Specifies whether or not this control should be stretched to
        * the right to fill the dialog width.
        * @param aStretchRight ETrue if the control should be stretched, or
        * EFalse if it should not
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetStretchToFitRight(TBool aStretchRight);

        /**
        * Sets the EExtraAscent flag, which adds extra height to
        * the control's text.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetExtraAscent();

        /**
        * Sets the caption text that appears to the left of the control.
        * @param aText The text.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetCaptionL(const TDesC& aText);

        /**
        * Sets the caption icon that appears to the left of the caption text.
        * @param aIcon The icon. The captioned control does not own its icon
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetCaptionIconL(CGulIcon* aIcon);

        IMPORT_C void SetCaptionAndZoomL(const TDesC& aText, TInt aZoom);

        /**
        * Sets the trailer text which appears to the right of the control.
        * @param aText The text.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetTrailerL(const TDesC& aText);

        /**
        * Specifies whether or not this captioned control
        * is the currently selected one.
        * @param aSelected ETrue if this captioned control is currently
        *                  selected, or EFalse if it is not.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetCurrent(TBool aSelected);

        /**
        * Checks the dimmed state of the captioned control and redraws the
        * text (and ears) accordingly.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void CheckDimmedDisplayState();

        /**
        * Sets the text widths to 0.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void ResetMinimumSizes();

        /**
        * @return ETrue if the captioned control is latent (temporarily hidden)
        * <BR><B>Type of return value:</B> TBool
        */
        IMPORT_C TBool IsLatent() const;

        /**
        * Sets the captioned control to be latent.
        * If dialog lines are latent they are not visible and are not taken
        * into account when laying out the dialog
        * @param aLatent If aLatent is ETrue, this hides the captioned control.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetLatent(TBool aLatent);

        /**
        * @return ETrue if this control is not included when measuring a dialog.
        * <BR><B>Type of return value:</B> TBool
        */
        IMPORT_C TBool LatentGroupLineFollows() const;

        /**
        * Specifies whether this control is excluded when measuring a dialog.
        * @param aLglf ETrue to exclude this control when measuring a dialog
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetLatentGroupLineFollows(TBool aLglf);

        /**
        * @return ETrue if a divider appears below this captioned control.
        * <BR><B>Type of return value:</B> TBool
        */
        IMPORT_C TBool DividerAfter() const;

        /**
        * Specifies whether a divider appears below this captioned control.
        * @param aDividerAfter ETrue if a divider appears below this
        * captioned control.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetDividerAfter(TBool aDividerAfter);

        /**
        * @return ETrue if this captioned control can handle an Enter key.
        * <BR><B>Type of return value:</B> TBool
        */
        IMPORT_C TBool TakesEnterKey() const;

        /**
        * Specifies whether this captioned control can handle an Enter key.
        * @param aTakesEnter ETrue if this captioned control can handle
        * an Enter key
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetTakesEnterKey(TBool aTakesEnter);

        /**
        * @return ETrue if this captioned control should be offered key events
        * <BR><B>Type of return value:</B> TBool
        */
        IMPORT_C TBool OfferHotKeys() const;

        /**
        * Specifies whether or not this captioned control should be offered
        * key events.
        * @param aOffer ETrue if this captioned control should be offered
        * key events.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetOfferHotKeys(TBool aOffer);

        /**
        * Sets the size of the blank space on the left & right edges.
        * @param aHorizMargins The margin size.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetHorizontalMargins(TInt aHorizMargins);
        
    public: // from CCoeControl

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C TSize MinimumSize();

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C void PrepareForFocusLossL();

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C void PrepareForFocusGainL();

        /**
        * This allows the CEikCaptionedControl to be constructed from resources.
        * as part of the DIALOG and DLG_LINE structures
        * See <code>CCoeControl</code>.
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    private: // from CCoeControl
        IMPORT_C TInt CountComponentControls() const;
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
        IMPORT_C void SizeChanged();
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);
    protected: // from CCoeControl

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * See <code>CCoeControl</code>.
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private: // from CCoeControl
        IMPORT_C void Reserved_2();
    // from MCoeCaptionRetrieverForFep
        IMPORT_C virtual void GetCaptionForFep(TDes& aCaption) const;
        IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_1();
        IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_2();
    private:
    enum TWhichEars
        {
        ENoEar=0x00,
        ELeftEar=0x01,
        ERightEar=0x02,
        EBothEars=0x03
        };
    private: // new functions
        void SetCaptionAndIconL(const TDesC& aText, CGulIcon* aIcon, TInt aLineHeight, TInt aBaseline);
        TInt WidthForEars(TInt aWidthRemaining) const;
        void DrawEarsNow(TWhichEars aEar) const;
        void DrawEars(TWhichEars aEar) const;
        void DrawSingleEar(TWhichEars aEar,TBool aPressed) const;
        TRect EarRect(TWhichEars aEar) const;
        void FireEarL(TWhichEars aEar,TInt aEarRepeat);
        void StretchComponents();
        void SquashComponents();
        void DrawSeparator() const;
        TRect SeparatorRect(const TSize bitmapSize) const;
	protected: // new functions
		void SetControlWidth(const TInt aWidth);
    public:
        CCoeControl* iControl;
        CEikCapLabel* iCaption;
        CEikLabel* iTrailer;
        TInt iId;
        TInt iControlType;
        TAny* iReturnValue;
    private:
        TSize iMinSize;
        TInt iCapCFlags;
        TInt iCaptionWidth;
        TInt iFullWidth;
    /// margin at both left and right sides of the captioned control
        TInt iHorizMargins;
    friend class CEikCapCArray;
    };


#endif  // EIKCAPC_H

// End of File