// GDI.INL
//
// Copyright (c) 1998-2001 Symbian Ltd.  All rights reserved.
//

//
// TRgb
//

/**
 *
 * Constructs a <code>TRgb</code> initialised to KRgbWhite.
 *
 */
inline TRgb::TRgb():
	iValue(0x00ffffff)
	{}

/**
 *
 * Constructs a <code>TRgb</code> directly from a single 32-bit integer.
 *
 * The integer is of the form <code>0x00bbggrr</code>, where bb is the
 * hex number of blue, gg is the hex number for green, and rr is the hex
 * number for red. For example, <code>TRgb(2,4,8)</code> using the 3
 * colour constructor is equal to <code>TRgb(0x00080402)</code> using
 * this constructor.
 *
 * @param     "TUint32 aValue"
 *            Integer representing colour value. Takes form
 *            <code>0x00bbggrr</code>.
 */
inline TRgb::TRgb(TUint32 aValue):
	iValue(aValue)
	{}

/**
 *
 * Constructs a <code>TRgb</code> from separate color components.
 *
 * The components values may be between 0 and 255 inclusive.
 * A value of 0 represents zero intensity of that colour and 255
 * represents full intensity.
 *
 * @param     "TInt aRed"
 *            Integer representing red component value.
 * @param     "TInt aGreen"
 *            Integer representing green component value.
 * @param     "TInt aBlue"
 *            Integer representing blue component value.
 */
inline TRgb::TRgb(TInt aRed,TInt aGreen,TInt aBlue):
	iValue(aRed|aGreen<<8|aBlue<<16)
	{}

/**
 *
 * Gets the red component.
 *
 * @returns   "TInt"
 *            The red component (0 - 255).
 */
inline TInt TRgb::Red() const
	{return(iValue&0xff);}

/**
 *
 * Gets the green component.
 *
 * @returns   "TInt"
 *            The green component (0 - 255).
 */
inline TInt TRgb::Green() const
	{return((iValue&0xff00)>>8);}

/**
 *
 * Gets the blue component.
 *
 * @returns   "TInt"
 *            The blue component (0 - 255).
 */
inline TInt TRgb::Blue() const
	{return((iValue&0xff0000)>>16);}

/**
 *
 * Compares this colour with the specified colour for equality.
 *
 * For two colours to be equal, their red, green and blue components must
 * all be equal.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be compared.
 * @returns   "TBool"
 *            <code>ETrue</code> if the colours are equal; <code>EFalse</code> otherwise.
 */
inline TBool TRgb::operator==(const TRgb& aColor) const
	{return(iValue==aColor.iValue);}

/**
 *
 * Compares this colour with the specified colour for inequality.
 *
 * For two colours to not be equal, at least one of their red,
 * green and blue components must be different.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be compared.
 * @returns   "TBool"
 *            <code>ETrue</code> if the colours are not equal; <code>EFalse</code> otherwise.
 */
inline TBool TRgb::operator!=(const TRgb& aColor) const
	{return(!(*this==aColor));}

/**
 *
 * Logical AND assignment operator.
 *
 * The operator ANDs the parameter with this value and assigns
 * the result back to this value. Note:This operates in the
 * <code>TRgb</code> domain. Graphics defines logical operations for
 * drawing primitives which operate in the device colour domain.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be other operand.
 * @returns   "TRgb&"
 *            Reference to this value containing the result.
 */
inline TRgb& TRgb::operator&=(const TRgb& aColor)
	{iValue&=aColor.iValue;return(*this);}

/**
 *
 * Logical OR assignment operator.
 *
 * The operator ORs the parameter with this value and assigns
 * the result back to this value. Note:This operates in the
 * <code>TRgb</code> domain. Graphics defines logical operations for
 * drawing primitives which operate in the device colour domain.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be other operand.
 * @returns   "TRgb&"
 *            Reference to this value containing the result.
 */
inline TRgb& TRgb::operator|=(const TRgb& aColor)
	{iValue|=aColor.iValue;return(*this);}

/**
 *
 * Logical XOR assignment operator.
 *
 * The operator XORs the parameter with this value and assigns
 * the result back to this value. Note:This operates in the
 * <code>TRgb</code> domain. Graphics defines logical operations for
 * drawing primitives which operate in the device colour domain.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be other operand.
 * @returns   "TRgb&"
 *            Reference to this value containing the result.
 */
inline TRgb& TRgb::operator^=(const TRgb& aColor)
	{iValue^=aColor.iValue;return(*this);}

/**
 *
 * Gets the 24-bit value of the <code>TRgb</code> as a 32-bit integer.
 *
 * @returns   "TUint32"
 *            The 32 bit value of the <code>TRgb</code>. The has the
 *            form <code>0x00bbggrr</code>.
 */
inline TUint32 TRgb::Value() const
	{return(iValue);}

/**
 *
 * Bitwise logical inversion operator.
 *
 * @returns   "TRgb"
 *            Contains results of logical inversion of each colour component.
 */
inline TRgb TRgb::operator~() const
	{return(TRgb(iValue^0x00ffffff));}

/**
 *
 * Bitwise logical AND operator.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be other operand.
 * @returns   "TRgb"
 *            Contains results of logical AND.
 */
inline TRgb TRgb::operator&(const TRgb& aColor)
	{return(TRgb(iValue&aColor.iValue));}

/**
 *
 * Bitwise logical OR operator.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be other operand.
 * @returns   "TRgb"
 *            Contains results of logical OR.
 */
inline TRgb TRgb::operator|(const TRgb& aColor)
	{return(TRgb(iValue|aColor.iValue));}

/**
 *
 * Bitwise logical XOR operator.
 *
 * @param     "const TRgb& aColor"
 *            Colour to be other operand.
 * @returns   "TRgb"
 *            Contains results of logical XOR.
 */
inline TRgb TRgb::operator^(const TRgb& aColor)
	{return(TRgb(iValue^aColor.iValue));}

//
// CPalette
//

/**
 *
 * Gets the number of entries in the palette.
 *
 * @returns   "TInt"
 *            The number of entries in the palette.
 */
inline TInt CPalette::Entries() const
	{return(iNumEntries);}

//
// TColor256Utils
//

/**
 *
 * Converts a palette index into a TRgb object.
 *
 * @param     "TInt aColor256"
 *            Palette index to convert.
 * @returns   "TRgb"
 *            Corresponding palette entry.
 */
inline TRgb TColor256Util::Color256(TInt aColor256) const
	{ return TRgb(iColorTable[aColor256]); }

//
// TFontStyle
//

/**
 *
 * Compares a font style for equality.
 *
 * @param     "const TFontStyle& aFontStyle"
 *            The font style to be compared with this font style.
 * @returns   "TBool"
 *            <code>ETrue</code> if this <code>TFontStyle</code> is
 *            equal to <code>aFontStyle</code>, <code>EFalse</code>,
 *            otherwise.
 */
inline TBool TFontStyle::operator==(const TFontStyle& aFontStyle) const
	{return(iFlags==aFontStyle.iFlags);}

/**
 *
 * Gets the glyph bitmap type of the font style.
 *
 * @returns   "TGlyphBitmapType"
 *            The font style's glyph bitmap type.
 */
inline TGlyphBitmapType TFontStyle::BitmapType() const
	{
	return (TGlyphBitmapType)(iFlags >> 16);
	}

/**
 *
 * Sets the glyph bitmap type of the font style.
 *
 * @param     "TGlyphBitmapType aBitmapType"
 *            The glyph bitmap type to be set.
 */
inline void TFontStyle::SetBitmapType(TGlyphBitmapType aBitmapType)
	{
	iFlags &= 0xFFFF;
	iFlags |= (aBitmapType << 16);
	}

//
// CBitmapDevice
//

/**
 *
 * Creates a bitmap context for this bitmap device.
 *
 * @param     "CBitmapContext*& aGC"
 *            On return, holds a pointer to the created bitmap
 *            context.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
inline TInt CBitmapDevice::CreateBitmapContext(CBitmapContext*& aGC)
	{return(CreateContext((CGraphicsContext*&)aGC));} // relies on CBitmapContext deriving _only_ from CGraphicsContext

//
// TPictureCapability
//

inline TPictureCapability::TPictureCapability(TScalingType aScalingType,TBool aCroppable):
	iScalingType(aScalingType),iIsCroppable(aCroppable)
	{}

//
// TZoomFactor
//

/**
 *
 * Constructs a zoom factor object, based on the <code>MGraphicsDeviceMap</code>
 * object, ready for use.
 *
 */
inline TZoomFactor::TZoomFactor(const MGraphicsDeviceMap* aDevice):
	iZoomFactor(TZoomFactor::EZoomOneToOne),
	iDevice(aDevice)
	{}

/**
 *
 * Sets the graphics device map for this zoom factor object.
 *
 * @param     "const MGraphicsDeviceMap* aDevice"
 *            The graphics device map for this
 *            <code>TZoomFactor</code>.
 */
inline void TZoomFactor::SetGraphicsDeviceMap(const MGraphicsDeviceMap* aDevice)
	{iDevice=aDevice;}

/**
 *
 * Gets the graphics device map of this zoom factor object.
 *
 * @returns   "MGraphicsDeviceMap*"
 *            The graphics device map of the
 *            <code>TZoomFactor</code>.
 */
inline const MGraphicsDeviceMap* TZoomFactor::GraphicsDeviceMap() const
	{return(iDevice);}

