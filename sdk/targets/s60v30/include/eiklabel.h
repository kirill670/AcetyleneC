// EIKLABEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLABEL_H__)
#define __EIKLABEL_H__


#if !defined(__EIKALIGN_H__)
#include <eikalign.h>
#endif

#if !defined(__COECCNTX_H__)
#include <coeccntx.h>
#endif

#include <bidi.h>

class CEikLabelExtension;
class CAknPictographInterface;

class CEikLabel : public CEikAlignedControl, public MCoeControlContext
	{
public:  // new functions
	IMPORT_C ~CEikLabel();
	IMPORT_C CEikLabel();
    /**
     * Sets the labels alignment, this overwrites alignment set
     * via CEikAlignedControl
     * 
     * @param aAlignment    should be one of { ELayoutAlignNone, ELayoutAlignCenter, ELayoutAlignLeft, ELayoutAlignRight, ELayoutAlignBidi } defined in Avkon.hrh
     */
	IMPORT_C void SetLabelAlignment(TInt aAlignment);

    /**
     * Sets the BrushStyle to be used from aBrushStyle, 
     * this overwrites the BrushStyle set via the Control Context
     * 
     * @param aBrushStyle
     */
    IMPORT_C void SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle);

    /**
     * Sets the BrushStyle to be used from the Control Context, 
     * this overwrites the BrushStyle set via the CEikLabel::SetBrushStyle() 
     * 
     */
    IMPORT_C void SetBrushStyleFromContext();


public:  // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;

public:  
	enum TTextEmphasis
		{
		ENoEmphasis		 =0x00,
		EPartialEmphasis =0x10,
		EFullEmphasis	 =0x20
		};
public:  // new functions
	IMPORT_C void SetTextL(const TDesC& aText);
	inline const TDesC* Text() const;
	IMPORT_C void CropText();
	IMPORT_C void SetBufferReserveLengthL(TInt aLength);
	IMPORT_C void SetFont(const CFont* aFont);
	inline const CFont* Font() const;
	IMPORT_C void SetEmphasis(TTextEmphasis aEmphasis);
    /**
    * Sets the gap between lines. Gap has a particular definition here.  It is defined to be:
    *    "baselines separation" - CFont::HeightInPixels()
    * 
    * @param    aGap    Pixels gap to set between lines.
    */
	IMPORT_C void SetPixelGapBetweenLines(TInt aGap);
	IMPORT_C TInt PixelGapBetweenLines() const;
	inline TBool IsUnderlined() const;
	IMPORT_C void SetUnderlining(TBool aUnderLining);
	inline TBool IsStrikethrough() const;
	IMPORT_C void SetStrikethrough(TBool aStrikethrough);
	IMPORT_C TSize CalcMinimumSize(TPtrC& aText) const;
	inline TUint8 NumberOfLines();
	IMPORT_C TInt BufferReserveLength() const;

    /**
    * Enables or disables logical to visual conversion when label text is drawn.
    * By default, it is enabled.
    * If you perform the conversion yourself and give visual text
    * (in scrictly left-to-right order) to label, you
    * should disable the conversion in label. Note that label does not perform
    * cropping if logical to visual conversion is disabled.
    *
    * @param aUseConversion Whether label should perform logical to visual
    *                       conversion or not.
    */
    IMPORT_C void UseLogicalToVisualConversion( TBool aUseConversion );

    /**
    * Returns information of whether label is performing logical to visual
    * conversion or not.
    *
    * @return ETrue if label does logical to visual conversion, EFalse if not.
    */
    IMPORT_C TBool LogicalToVisualConversionUsed() const;

    /**
    * Enables pictograph drawing in the label text.
    * Only effective in Japanese variant.
    * By default, it is disabled.
    *
    * @since 2.6
    * @param aInterface Used pictograph interface owned by the caller.
    */
    IMPORT_C void EnablePictographsL( CAknPictographInterface& aInterface );

    /**
    * Disables pictograph drawing in the label text.
    * Only effective in Japanese variant.
    * By default, it is disabled.
    *
    * @since 2.6
    */
    IMPORT_C void DisablePictographs();
public: // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	IMPORT_C void Reserved_2();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // new functions
	TInt HeightInPixels() const;
	TInt WidthInPixels(TPtrC& aText) const;
	void SetupGcForEmphasis(CGraphicsContext& aGc) const;
    TBool CheckAndCreateExtension();
protected:
	enum TLabelFlags
		{
		EUnderlining                  = 0x02,
		EStrikethrough                = 0x04,
        EUseLogicalToVisualConversion = 0x08
        // flags 0x10, 0x20, 0x40 are already used for text emphasis!
		};
	HBufC* iText;
	const CFont* iFont;
	TUint8 iNumberOfLines;
	TUint8 iLabFlags;
	TInt iGapBetweenLines; // See definition of this member in the "Setter" routine
private:
	TInt iReserveLength;
	CEikLabelExtension* iExtension;
    TInt iSpare[2];
	};


inline const TDesC* CEikLabel::Text() const
	{ return(iText); }
inline const CFont* CEikLabel::Font() const
	{ return(iFont); }
inline TBool CEikLabel::IsUnderlined() const
    {return iLabFlags&EUnderlining;}
inline TBool CEikLabel::IsStrikethrough() const
    {return iLabFlags&EStrikethrough;}
inline TUint8 CEikLabel::NumberOfLines()
	{return iNumberOfLines;}	

#endif
