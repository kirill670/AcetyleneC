// GDI.INL
//
// Copyright (c) 1998-2003 Symbian Ltd.  All rights reserved.
//

//
// TRgb
//


inline TRgb::TRgb():
	iValue(0x00ffffff)
	/**  Constructs a @code TRgb @endcode initialised to KRgbWhite.*/
	{}

 
inline TRgb::TRgb(TUint32 aValue):
	iValue(aValue)
/** Constructs a TRgb directly from a single 32-bit integer.

The integer is of the form 0x00bbggrr, where bb is the hex number of blue, 
gg is the hex number for green, and rr is the hex number for red. For example, 
TRgb(2,4,8) using the 3 colour constructor is equal to TRgb(0x00080402) using 
this constructor.

@param aValue Integer representing colour value. Takes form 0x00bbggrr. */
	{}

 
inline TRgb::TRgb(TInt aRed,TInt aGreen,TInt aBlue):
	iValue(aRed|aGreen<<8|aBlue<<16)
/** Constructs a TRgb from its three component colours.

Each colour has a value between 0 and 255.

@param aRed Red component of the colour (0 - 255). 
@param aGreen Green component of the colour (0 -  255). 
@param aBlue Blue component of the colour (0 - 255). */
	{}


inline TInt TRgb::Red() const
/** Gets the red component.

@return The blue component (0 - 255). */
	{return(iValue&0xff);}


inline TInt TRgb::Green() const
/** Gets the green component.

@return The blue component (0 - 255). */
	{return((iValue&0xff00)>>8);}


inline TInt TRgb::Blue() const
/** Gets the blue component.

@return The blue component (0 - 255). */
	{return((iValue&0xff0000)>>16);}

 
inline TBool TRgb::operator==(const TRgb& aColor) const
/** Compares this colour with the specified colour for equality.

For two colours to be equal, their red, green and blue components must all 
be equal.

@param aColor Colour to be compared. 
@return ETrue. if the colours are equal; EFalse, otherwise. */
 
	{return(iValue==aColor.iValue);}

 
inline TBool TRgb::operator!=(const TRgb& aColor) const
/** Compares this colour with the specified colour for inequality.

Two colours are unequal if one at least one of their red, green and blue components 
are unequal.

@param aColor Colour to be compared. 
@return ETrue, if the colours are not equal; EFalse, otherwise.
 */
	{return(!(*this==aColor));}
 
inline TRgb& TRgb::operator&=(const TRgb& aColor)
/** Logical AND assignment operator.

The operator ANDs the first operand with the second and then assigns the result 
back to the first operand.

Note:

This operates in the TRgb domain. Graphics defines logical operations for 
drawing primitives which operate in the device colour domain.

@param aColor Colour to be compared. 
@return First operand-contains result of logical AND. */
	{iValue&=aColor.iValue;return(*this);}

inline TRgb& TRgb::operator|=(const TRgb& aColor)
/** Logical OR assignment operator.

The operator ORs the first operand with the second and then assigns the result 
back to the first operand.

Note:

This operates in the TRgb domain. Graphics defines logical operations for 
drawing primitives which operate in the device colour domain.

@param aColor Colour to be compared. 
@return First operand- contains result of logical OR. */
	{iValue|=aColor.iValue;return(*this);}

 
inline TRgb& TRgb::operator^=(const TRgb& aColor)
/** Logical EXCLUSIVE OR assignment operator.

The operator Exclusive ORs the first operand with the second and then assigns 
the result back to the first operand.

Note:

This operates in the TRgb domain. Graphics defines logical operations for 
drawing primitives which operate in the device colour domain.

@param aColor Colour to be compared. 
@return First operand  contains result of logical Exclusive OR. */
	{iValue^=aColor.iValue;return(*this);}

 
inline TUint32 TRgb::Value() const
/** Gets the 24-bit value of the TRgb as a 32-bit integer. 

@return The 32 bit value of the TRgb. The has the form 0x00bbggrr. */
	{return(iValue);}

 
inline TRgb TRgb::operator~() const
/** Bitwise logical inversion operator.

@return Contains results of logical inversion. */
	{return(TRgb(iValue^0x00ffffff));}

 
inline TRgb TRgb::operator&(const TRgb& aColor)
/** Bitwise logical AND operator.

@param aColor Colour to be compared. 
@return Contains results of logical AND. */
	{return(TRgb(iValue&aColor.iValue));}

 
inline TRgb TRgb::operator|(const TRgb& aColor)
/** Bitwise logical OR operator.

@param aColor Colour to be compared. 
@return Contains results of logical OR. */
	{return(TRgb(iValue|aColor.iValue));}

 
inline TRgb TRgb::operator^(const TRgb& aColor)
/** Bitwise EXCLUSIVE OR operator

@param aColor Colour to be compared. 
@return Contains results of logical EXCLUSIVE OR. */
	{return(TRgb(iValue^aColor.iValue));}

//
// CPalette
//

 
inline TInt CPalette::Entries() const
/** Gets the number of entries in the palette

@return The number of entries in the palette. */
	{return(iNumEntries);}

//
// TColor256Utils
//

 
inline TRgb TColor256Util::Color256(TInt aColor256) const
/** Gets the TRgb value of the entry at the specified index in the colour lookup 
table.

@param aColor256 The index into the colour lookup table.
@return The TRgb value of the entry at the specified index. */
	{ return TRgb(iColorTable[aColor256]); }

//
// TFontStyle
//

 
inline TBool TFontStyle::operator==(const TFontStyle& aFontStyle) const
/** Compares a font style for equality.

@param aFontStyle The font style to be compared with this font style.
@return ETrue, if this TFontStyle is equal to aFontStyle, EFalse, otherwise. */
	{return(iFlags==aFontStyle.iFlags);}

 
inline TGlyphBitmapType TFontStyle::BitmapType() const
/** Gets the anti-aliasing setting for the font, as set by SetBitmapType().

@return Indicates whether or not this font should be drawn using anti-aliasing. */
	{
	return (TGlyphBitmapType)(iFlags >> 16);
	}

 
inline void TFontStyle::SetBitmapType(TGlyphBitmapType aBitmapType)
/** Sets whether the font should be drawn using anti-aliasing. If set, this value 
overrides the default setting (set by CFbsTypefaceStore::SetDefaultBitmapType()) 
for this font.

Anti-aliasing can only be used for scalable fonts. There is currently no anti-aliasing 
support for bitmapped fonts.

@param aBitmapType Indicates whether or not this font should be drawn using 
anti-aliasing. */
	{
	iFlags &= 0xFFFF;
	iFlags |= (aBitmapType << 16);
	}

//
// CBitmapDevice
//

 
inline TInt CBitmapDevice::CreateBitmapContext(CBitmapContext*& aGC)
/** Creates a bitmap context for this bitmap device.

@param aGC On return, holds a pointer to the created bitmap context. 
@return KErrNone, if successful; otherwise, another of the system-wide error 
codes. */
	{return(CreateContext((CGraphicsContext*&)aGC));} // relies on CBitmapContext deriving _only_ from CGraphicsContext

//
// TPictureCapability
//

inline TPictureCapability::TPictureCapability(TScalingType aScalingType,TBool aCroppable):
	iScalingType(aScalingType),iIsCroppable(aCroppable)
/** Constructs the object setting the scaling-type and croppability properties.

@param aScalingType Whether or not the picture is scalable. 
@param aCroppable Whether or not the picture is croppable. */
	{}

//
// TZoomFactor
//

 
inline TZoomFactor::TZoomFactor(const MGraphicsDeviceMap* aDevice):
	iZoomFactor(TZoomFactor::EZoomOneToOne),
	iDevice(aDevice)
/** Constructs a zoom factor object for a specific graphics device map.

The graphics map is either directly associated with a particular graphics 
device itself, or is associated with a hierarchy of device maps whose root 
map is associated with a particular graphics device.

@param aDevice The graphics device map with which the zoom factor is associated. */
	{}

 
inline void TZoomFactor::SetGraphicsDeviceMap(const MGraphicsDeviceMap* aDevice)
/** Sets the graphics device map for this zoom factor object.

@param aDevice The graphics device map for this TZoomFactor. */
	{iDevice=aDevice;}

 
inline const MGraphicsDeviceMap* TZoomFactor::GraphicsDeviceMap() const
/** Gets the graphics device map of this zoom factor object.

@return The graphics device map of the TZoomFactor. */
	{return(iDevice);}

