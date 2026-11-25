/*
* ==============================================================================
*  Name        : eikparad.h
*  Part of     : CKON
*  Interface   : Paragraph Dialog API
*  Description : Text dialogs
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


#ifndef EIKPARAD_H
#define EIKPARAD_H

// INCLUDES
#include <eikdialg.h>

// FORWARD DECLARATIONS
class CParaFormat;
class TParaFormatMask;
class TParaBorder;
class CEikBorderPreviewControl;


/**
 * The <code>CEikAlignDialog</code> class implements the Alignment dialog. This 
 * class launches a dialog that enables the user to edit the alignment of 
 * text,the format of which is passed in as a <code>TParaFormatMask</code>.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikAlignDialog : public CEikDialog
    {
    public:
        /**
        * Launches the Alignment dialog.
        *
        * @param aFormat The paragraph format
        * @param aAttribChangedMask On return, if the EAttAlignment flag is set, the horizontal 
		*                           alignment was changed.
        * @param aUndeterminedMask  If some text is selected in the underlying text editor, 
		*                           this mask indicates whether different alignment attributes 
		*                           apply to the selection, so that the dialog's initial setting 
		*                           is indeterminate. In this case, the setting is left blank.
        * @return <code>ETrue</code> if the dialog runs successfully; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see <code>CParaFormat</code> and <code>TParaFormatMask</code> in 
        *      txtfrmat.h 
        */
        IMPORT_C static TBool RunDlgLD(
                                    CParaFormat*        aFormat, 
                                    TParaFormatMask&    aAttribChangedMask, 
                                    TParaFormatMask&    aUndeterminedMask);

        /** @internal */
        void GetHelpContext(TCoeHelpContext& aContext) const;
    private: 
        CEikAlignDialog(CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, TParaFormatMask& aUndeterminedMask);
    // from CEikDialog  
        void PostLayoutDynInitL();
        TBool OkToExitL(TInt aKeyCode);
    private:
        TParaFormatMask* iAttribChangedMask;
        TParaFormatMask* iUndeterminedMask;
        CParaFormat::TAlignment* iAlignment;
    };

/**
 * The <code>CEikIndentDialog</code> class launches a dialog to enable the user 
 * to edit the paragraph indentation of some text, the format of which is passed 
 * in as a <code>TParaFormatMask</code>.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikIndentDialog : public CEikDialog
    {
    public:
        /**
        * Launches the Indents dialog.
        *
        * @param aFormat The paragraph format
        * @param aAttribChangedMask On return, indicates which of the attributes in aFormat were 
		*                           changed by the dialog. Any of the values EAttLeftMargin, EAttRightMargin 
		*                           and EAttIndent could be set.
        * @param aUndeterminedMask  If some text is selected in the underlying text editor, 
		*                           this mask indicates the attributes that only apply to a part 
		*                           of the selection, so that the dialog's initial settings for those 
		*                           attributes are indeterminate. In this case, they are 
		*                           initialised to zero.
        * @param aPageWidth The width of the printable page in twips. This is used as the maximum 
		*                   value for the three twips editors.
        * @return <code>ETrue</code> if the dialog runs successfully; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see <code>CParaFormat</code> and <code>TParaFormatMask</code> in 
        *      txtfrmat.h 
        */
        IMPORT_C static TBool RunDlgLD(
                                    CParaFormat*        aFormat, 
                                    TParaFormatMask&    aAttribChangedMask, 
                                    TParaFormatMask&    aUndeterminedMask,
                                    const TInt          aPageWidth);

        /** @internal */
        void GetHelpContext(TCoeHelpContext& aContext) const;
    private: 
        CEikIndentDialog(CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, TParaFormatMask& aUndeterminedMask,const TInt aPageWidth);
    // from CEikDialog
        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aKeyCode);
    private:
        void SetEditorStateL(TTextFormatAttribute aAtt,TInt aControlId,TInt32* aValue);
    private:
        TParaFormatMask* iAttribChangedMask;
        TParaFormatMask* iUndeterminedMask;
        TInt32* iLeftMargin;
        TInt32* iRightMargin;
        TInt32* iIndent;
        TInt iPageWidth;
    };

/**
 * The <code>CEikSpaceDialog</code> launches a dialog that enables the user to 
 * edit the paragraph and line spacing of some text, the format of which is passed 
 * in as a <code>TParaFormatMask</code>.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikSpaceDialog : public CEikDialog
    {
    public:
        /**
        * Launches the Line Spacing dialog.
        *
        * @param aFormat The paragraph format
        * @param aAttribChangedMask On return, indicates which attributes in aFormat were changed
		*                           by the dialog.
        * @param aUndeterminedMask  If some text is selected in the underlying text editor, 
		*                           this mask indicates attributes that only apply to a part of 
		*                           the selection, so that the dialog's initial settings for those 
		*                           attributes are indeterminate.
        * @return <code>ETrue</code> if the dialog runs successfully; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see <code>CParaFormat</code> and <code>TParaFormatMask</code> in <code>txtfrmat.h</code> 
        */
        IMPORT_C static TBool RunDlgLD(
                                    CParaFormat*        aFormat, 
                                    TParaFormatMask&    aAttribChangedMask, 
                                    TParaFormatMask&    aUndeterminedMask);
    private: 
        CEikSpaceDialog(CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, TParaFormatMask& aUndeterminedMask);
    // from CEikDialog
        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aKeyCode);
    protected:
        void HandleControlStateChangeL(TInt aControlId);
    private:
        TParaFormatMask* iAttribChangedMask;
        TParaFormatMask* iUndeterminedMask;
        CParaFormat::TLineSpacingControl* iLineSpacingControl;
        TInt32* iLineSpacing;
        TInt32* iSpaceBefore;
        TInt32* iSpaceAfter;
        TBool* iWidowOrphan;
        TBool* iKeepTogether;
        TBool* iKeepWithNext;
        TBool* iStartNewPage;
    };

/**
 * The <code>CEikBorderDialog</code> class sets the line style and color for 
 * paragraph border lines. This class launches a dialog that enables the user 
 * to edit the line style and color for the paragraph border lines of some text.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikBorderDialog : public CEikDialog
    {
    public:
    /**
    * The <code>TBorderProperties</code> class implements the border properties.
    * @internal
    */
    class TBorderProperties
        {
    public:
        /** @internal */
        TParaBorder iBottomBorder;
        /** @internal */
        TParaBorder iTopBorder;
        /** @internal */
        TParaBorder iLeftBorder;
        /** @internal */
        TParaBorder iRightBorder;
        /** @internal */
        TParaBorder iVCentreBorder;
        /** @internal */
        TParaBorder iHCentreBorder;
        };
    /** 
     * The enumeration <code>TBorderLineStyle</code> specifies the line style 
     * used for the border. 
     */
    enum TBorderLineStyle
        {
        /** no style used */
        ELineStyleNone,
        /** thick solid line style used */
        ELineStyleThickSolid,
        /** thin solid line style used  */
        ELineStyleThinSolid,
        /** dotted line style used */
        ELineStyleDots,
        /** dashes used for line style */
        ELineStyleDashes,
        /** dots and dashes used for line style */
        ELineStyleDotDash,
        /** two dots and one dash used for line style */
        ELineStyleDotDotDash,
        /** unused */
        ELineStyleUndefined
        };

    /** 
     * The enumeration <code>TBorderLinePlace</code> specifies the position in
     * which the border is placed. 
     */
    enum TBorderLinePlace
        {
        /** 
         * border placed on all sides - top, bottom, left, right, and horizontal
         * and vertical middle 
         */
        ELinePlaceAll,
        /** no borders placed */
        ELinePlaceNone,
        /** border placed at top */
        ELinePlaceTop,
        /** border placed on left */
        ELinePlaceLeft,
        /** border placed at bottom */
        ELinePlaceBottom,
        /** border placed at right */
        ELinePlaceRight,
        /** border placed at horizontal middle */
        ELinePlaceHorizontalMiddle,
        /** border placed at vertical middle */
        ELinePlaceVerticalMiddle
        };

    public:

        /**
        * The object destructor.
        */
        ~CEikBorderDialog();

        /**
        * Launches the Borders dialog.
        *
        * @param aBorderProperties Used to specify the current border properties of the paragraph
		*                          to the dialog and also on return, gets the new border properties
		*                          set by the user. It is used as a read/write variable. 
        * @param aCentreBorders Whether or not the center border is required
        * @return <code>ETrue</code> if the dialog completes successfully;
        *         <code>EFalse</code> otherwise
        */
        IMPORT_C static TBool RunDlgLD(TBorderProperties& aBorderProperties, bool aCentreBorders);
        
        /** @deprecated */
        IMPORT_C static TBool RunDlgLD(CParaFormat* aFormat, 
                                   TParaFormatMask& aAttribChangedMask, 
                                   TParaFormatMask& aUndeterminedMask);

    public: 
        /** @internal */
        void GetHelpContext(TCoeHelpContext& aContext) const;
        /** @internal */
        SEikControlInfo CreateCustomControlL(TInt aControlType);
        /** @internal */
        void HandleBorderPreviewSelection(TInt aPlace);

    private: 
        CEikBorderDialog(TBorderProperties& aBorderProperties, TBool aCentreBorders);
    // from CEikDialog
        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aKeyCode);
        void HandleControlStateChangeL(TInt aControlId);
    private:
    enum TBorderStyle {ENullLineStyle,EThin,EThick,EDouble,EDashed};
    private:
        TBorderLineStyle GetTBorderStyle(TParaBorder aBorder);
    TParaBorder::TLineStyle GetLineStyle(TBorderLineStyle aLineStyle);
        TInt GetLineThickness(TBorderLineStyle aLineStyle);
        void PlaceControlStateChanged();
        void StyleControlStateChanged();
        void ColorControlStateChanged();
        void InitialisePreviewControl();
        void InitialiseChoiceLists();
        void StoreBorder();


    private:
        CEikBorderPreviewControl*   iPreview;
        TBorderProperties&          iBorderProperties;
        TBool                       iCentreBorders;
    };

/**
 * The <code>CEikBorderPreviewControl</code> class implements the border 
 * preview control. This control is used in the border dialog control to 
 * preview the border being edited.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikBorderPreviewControl : public CCoeControl
    {
    public:
        /** @internal */
        CEikBorderPreviewControl(TBool aHorizontal, TBool aVertical, CCoeControl* aParent);
        /** 
        * The object destructor.
        */
		/** @internal */
        virtual ~CEikBorderPreviewControl();
        /** @internal */
        void ConstructL(TInt aWidth, TInt aHeight);
        /** @internal */
        void SetLineStyle(CEikBorderDialog::TBorderLinePlace aPlace, CEikBorderDialog::TBorderLineStyle aStyle);
        /** @internal */
        void SetLineColour(CEikBorderDialog::TBorderLinePlace aPlace, TRgb aColour);
        /** @internal */
        CEikBorderDialog::TBorderLineStyle LineStyle(CEikBorderDialog::TBorderLinePlace aPlace);
        /** @internal */
        TRgb LineColour(CEikBorderDialog::TBorderLinePlace aPlace);

    public: // from CCoeControl
        /** @internal */
        void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        /** @internal */
        void ConstructFromResourceL(TResourceReader& aReader);
        /** @internal */
        virtual void Draw(const TRect& aRect) const;
        /** @internal */
        TSize MinimumSize();

    private:
    void DrawLine(CWindowGc &aGc, TPoint aStart, TPoint aEnd, 
                  CEikBorderDialog::TBorderLineStyle aStyle, TRgb aColour) const;

    private:
        TBool           iHorizontal;
        TBool           iVertical;
        TSize           iSize;
        TInt            iMargin;
        const CFont*    iLabelFont;
    // Styles
        CEikBorderDialog::TBorderLineStyle  iLeftStyle;
        CEikBorderDialog::TBorderLineStyle  iRightStyle;
        CEikBorderDialog::TBorderLineStyle  iTopStyle;
        CEikBorderDialog::TBorderLineStyle  iBottomStyle;
        CEikBorderDialog::TBorderLineStyle  iHMiddleStyle;
        CEikBorderDialog::TBorderLineStyle  iVMiddleStyle;
    // Colours
        TRgb            iLeftColour;
        TRgb            iRightColour;
        TRgb            iTopColour;
        TRgb            iBottomColour;
        TRgb            iHMiddleColour;
        TRgb            iVMiddleColour;
        HBufC* iPreviewText;
        CCoeControl* iParent;
    };

/**
 *  This was formerly the CEikBorderDialog but the functionality in that has 
 *  changed so we provide the old one is this (internal) class.
 *  @internal
 *  @lib eikcdlg.lib
 *  @since Series90 1.0
 *
 */
class CEikBorderDialogDeprecated : public CEikDialog
    {
public:
    /** @internal */
    static TBool RunDlgLD(
                                    CParaFormat*        aFormat, 
                                    TParaFormatMask&    aAttribChangedMask, 
                                    TParaFormatMask&    aUndeterminedMask);
    //from CCoeControl
    void GetHelpContext(TCoeHelpContext& aContext) const;
private: 
    CEikBorderDialogDeprecated(CParaFormat* aFormat, TParaFormatMask& aAttribChangedMask, TParaFormatMask& aUndeterminedMask);
    // from CEikDialog
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aKeyCode);
    void HandleControlStateChangeL(TInt aControlId);
private:
    enum TBorderStyle {ENullLineStyle,EThin,EThick,EDouble,EDashed};
private:
    void SetBorderLineStyleAndColor(const TParaBorder& aBorder, TTextFormatAttribute aAttribute,TInt aControlId, TInt aColorControlId);
    void DoPreviewL();
    TBorderStyle GetTBorderStyle(TParaBorder aBorder);
    TParaBorder::TLineStyle GetLineStyle(TBorderStyle aLineStyle);
    TInt GetLineThickness(TBorderStyle aLineStyle);
    //color
    TRgb ConvertGrayToTRgb(TUint aGray);
    TInt ConvertTRgbToGray(TRgb aTRgb);
private:
    class CPreviewDlg;
private:
    CParaFormat* iFormat;
    TParaFormatMask* iAttribChangedMask;
    TParaFormatMask* iUndeterminedMask;
    TParaBorder iRightBorder;
    TParaBorder iLeftBorder;
    TParaBorder iTopBorder;
    TParaBorder iBottomBorder;
    TInt32* iBorderMargin;
    const TParaBorder iOldLeftBorder;
    const TParaBorder iOldRightBorder;
    const TParaBorder iOldTopBorder;
    const TParaBorder iOldBottomBorder;
    //color
    TRgb iFillColor;
    const TRgb iOldFillColor;
//  TInt iLineStyleCount;
//  TInt iColorCount;
    };

/** @deprecated */
class CEikBorderDialogDeprecated::CPreviewDlg : public CEikDialog
    {
public:
    static TBool RunDlgLD(const TParaBorderArray& iBorderArray, TRgb& iFillColor);
private:
    CPreviewDlg(const TParaBorderArray& iBorderArray, TRgb& iFillColor);
private: //framework
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aKeyCode);
private:
    const TParaBorderArray& iBorderArray;
    TRgb& iFillColor;
    };

#endif  // EIKPARAD_H

// End of File
