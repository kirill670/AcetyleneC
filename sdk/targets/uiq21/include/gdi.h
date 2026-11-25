// GDI.H
//
// Copyright (c) 1998-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __GDI_H__
#define __GDI_H__

#include <e32base.h>
#include <f32file.h>
#include <s32std.h>

class TOpenFontCharMetrics;

const TInt KTwipsPerInch=1440;
const TInt KTwipsPerPoint=20;
const TInt KPointsPerInch=72;
const TInt KTwipsPerCm=567;
#if defined(__NO_CLASS_CONSTS__)
#define KA4PaperSizeInTwips TSize(11906,16838)
#define KLegalPaperSizeInTwips TSize(12240,20160)
#define KExecutivePaperSizeInTwips TSize(10440,15120)
#define KLetterPaperSizeInTwips TSize(12240,15840)
#define KCom_10PaperSizeInTwips TSize(5940,13680)
#define KMonarchPaperSizeInTwips TSize(5580,10800)
#define KDLPaperSizeInTwips TSize(6236,12472)
#define KC5PaperSizeInTwips TSize(9184,12983)
#else
const TSize KA4PaperSizeInTwips(11906,16838);
const TSize KLegalPaperSizeInTwips(12240,20160);
const TSize KExecutivePaperSizeInTwips(10440,15120);
const TSize KLetterPaperSizeInTwips(12240,15840);
const TSize KCom_10PaperSizeInTwips(5940,13680);
const TSize KMonarchPaperSizeInTwips(5580,10800);
const TSize KDLPaperSizeInTwips(6236,12472);
const TSize KC5PaperSizeInTwips(9184,12983);
#endif

/**
 *
 * 24-bit RGB colour value with 8 bits each for red, green and blue.
 *
 * All Graphics drawing functions are specified in terms of a 32-bit
 * <code>TRgb</code> colour containing the three colour values plus 8
 * unused bits. For hardware which does not support 24-bit colour, a
 * mapping from <code>TRgb</code> to display colours is performed. The
 * supported display modes are enumerated in the
 * <code>TDisplayMode</code> type. In each display mode a unique index
 * can represent each physical colours supported, and which can be mapped
 * onto a full RGB value. The mappings are as follows: 16-colour displays
 * use the EGA colour set: black, white, and then both light and dark
 * versions of grey, red, green, blue, cyan, magenta and yellow256-colour
 * displays support 216 colours made up of 6x6x6 RGB values, each
 * containing all possible multiples of 51 for R,G,B values.
 * Additionally, all remaining 10 shades of pure red, green, blue and
 * grey are represented, by adding all remaining multiples of 17. This
 * use of 256 colours is sometimes known as the Netscape colour
 * cube.4096-colour displays effectively support RGB values with 4 bits
 * per primary colour64k-colour displays effectively support RGB values
 * with 5 bits allocated to red, 6 to green and 5 to blue16
 * million-colour displays support true colour with 8 bits allocated to
 * each primary colour
 *
 * @since 5.0
 * @lib " gdi.lib "
 */
class TRgb
	{
public:
	inline TRgb();
	inline TRgb(TUint32 aValue);
	inline TRgb(TInt aRed,TInt aGreen,TInt aBlue);
	inline TInt Red() const;
	inline TInt Green() const;
	inline TInt Blue() const;
	IMPORT_C void SetRed(TInt aRed);
	IMPORT_C void SetGreen(TInt aGreen);
	IMPORT_C void SetBlue(TInt aBlue);
	IMPORT_C static TRgb Gray2(TInt aGray2);
	IMPORT_C static TRgb Gray4(TInt aGray4);
	IMPORT_C static TRgb Gray16(TInt aGray16);
	IMPORT_C static TRgb Gray256(TInt aGray256);
	IMPORT_C static TRgb Color16(TInt aColor16);
	IMPORT_C static TRgb Color256(TInt aColor256);
	IMPORT_C static TRgb Color4K(TInt aColor4K);
	IMPORT_C static TRgb Color64K(TInt aColor64K);
	IMPORT_C static TRgb Color16M(TInt aColor16M);
	IMPORT_C TInt Gray2() const;
	IMPORT_C TInt Gray4() const;
	IMPORT_C TInt Gray16() const;
	IMPORT_C TInt Gray256() const;
	IMPORT_C TInt Color16() const;
	IMPORT_C TInt Color256() const;
	IMPORT_C TInt Color4K() const;
	IMPORT_C TInt Color64K() const;
	IMPORT_C TInt Color16M() const;
	inline TBool operator==(const TRgb& aColor) const;
	inline TBool operator!=(const TRgb& aColor) const;
	inline TRgb operator~() const;
	inline TRgb operator&(const TRgb& aColor);
	inline TRgb operator|(const TRgb& aColor);
	inline TRgb operator^(const TRgb& aColor);
	inline TRgb& operator&=(const TRgb& aColor);
	inline TRgb& operator|=(const TRgb& aColor);
	inline TRgb& operator^=(const TRgb& aColor);
	inline TUint32 Value() const;
	IMPORT_C TInt Difference(const TRgb& aColor) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C static TRgb Color16MU(TInt a0RGB);
	IMPORT_C TInt Color16MU() const;
private:
	TUint32 iValue;
	};

#define KRgbBlack		TRgb(0x000000)
#define KRgbDarkGray	TRgb(0x555555)
#define KRgbDarkRed		TRgb(0x000080)
#define KRgbDarkGreen	TRgb(0x008000)
#define KRgbDarkYellow	TRgb(0x008080)
#define KRgbDarkBlue	TRgb(0x800000)
#define KRgbDarkMagenta	TRgb(0x800080)
#define KRgbDarkCyan	TRgb(0x808000)
#define KRgbRed			TRgb(0x0000ff)
#define KRgbGreen		TRgb(0x00ff00)
#define KRgbYellow		TRgb(0x00ffff)
#define KRgbBlue		TRgb(0xff0000)
#define KRgbMagenta		TRgb(0xff00ff)
#define KRgbCyan		TRgb(0xffff00)
#define KRgbGray		TRgb(0xaaaaaa)
#define KRgbWhite		TRgb(0xffffff)

/**
 *
 * Display modes.
 *
 */
enum TDisplayMode
	{
/** No display mode or display mode not set
 */
	ENone,
/** Monochrome display mode (1 bpp)
 */
	EGray2,
/** Four grayscales display mode (2 bpp)
 */
	EGray4,
/** 16 grayscales display mode (4 bpp)
 */
	EGray16,
/** 256 grayscales display mode (8 bpp)
 */
	EGray256,
/** Low colour EGA 16 colour display mode (4 bpp)
 */
	EColor16,
/** 256 colour display mode (8 bpp)
 */
	EColor256,
/** 64,000 colour display mode (16 bpp)
 */
	EColor64K,
/** True colour display mode (24 bpp)
 */
	EColor16M,
/** Not an actual display mode - used for moving buffers containing TRgbs
 */
	ERgb,
/** 4,000 colour display mode (12 bpp)
 */
	EColor4K,
/** True colour display mode (24 bpp) - unpacked - 32 bpp (file, memory, video)
 */
	EColor16MU
	};

/**
 *
 * A set of static utility functions to test if the display mode is
 * colour or greyscale, and how many colours/greyshades its supports.
 *
 * @since 5.0
 * @lib " gdi.lib"
 */
class TDisplayModeUtils
	{
public:
	IMPORT_C static TBool IsDisplayModeColor(TDisplayMode aDispMode);
	IMPORT_C static TInt NumDisplayModeColors(TDisplayMode aDispMode);
	IMPORT_C static TInt NumDisplayModeBitsPerPixel(TDisplayMode aDispMode);
	};

/**
 *
 * Provides user-definable palette support to the GDI.
 *
 * A palette is a user-defined set of colours, which is a subset of the
 * full range of 24-bit colours. This allows users the advantages of
 * having a low bpp colour mode whilst being able to specify the colours
 * available in that mode. To give an example, the EColor16 mode provides
 * a palette of 16 colours as it provides a mapping between an integer
 * index and a TRgb colour (see the table EGA Low-colour constants). Only
 * a palette of 16 colour enables you to change the palette. Palettes are
 * also used to allow 24-bit bitmaps to be stored in a more compressed
 * form by finding the actual number of different colours used in the
 * bitmap, creating a palette to allow the mapping of these colours to a
 * smaller index space, and encoding the bitmap's pixels using indexes
 * to this new index space. A palette has a size which is set at its
 * creation and cannot be altered - the number of entries in the
 * palette. Each entry in a palette is a mapping between that entry's
 * index and a TRgb value. Palette entries can be got and set at any time
 * between the palette's creation and destruction. The GDI's palette
 * support also provides functions to find the nearest palette colour to
 * a requested TRgb colour.
 *
 * @since 6.1
 * @lib "gdi.lib"
 */
class CPalette : public CBase
	{
public:
	IMPORT_C static CPalette* NewL(TInt aNumberOfEntries);
	IMPORT_C static CPalette* NewDefaultL(TDisplayMode aDispMode);
	IMPORT_C ~CPalette();
	IMPORT_C void Clear();
	inline TInt Entries() const;
	IMPORT_C TRgb GetEntry(TInt aPaletteIndex) const;
	IMPORT_C TRgb NearestEntry(const TRgb& aColor) const;
	IMPORT_C TInt NearestIndex(const TRgb& aColor) const;
	IMPORT_C void SetEntry(TInt aPaletteIndex,const TRgb& aPaletteEntry);
	IMPORT_C void GetDataPtr(TInt aFirstColor,TInt aNumColors,TPtr8& aPtr);
protected:
	IMPORT_C CPalette();
	void ConstructL(TInt aNumberOfEntries);
protected:
	TRgb* iArray;
	TInt iNumEntries;
	};

/**
 *
 * Enables conversion between a TRgb object and an index into an
 * arbitrary 256 colour palette.
 *
 * This encapsulates the lookup tables required for conversion.
 *
 * @since 6.1
 * @lib "gdi.lib"
 */
class TColor256Util
	{
public:
	IMPORT_C void Construct(const CPalette& aPalette);
	IMPORT_C TInt Color256(TRgb aRgb) const;
	IMPORT_C void Color256(TUint8* aDestination,const TRgb* aSource,TInt aNumPixels) const;
	inline TRgb Color256(TInt aColor256) const;
	IMPORT_C static const TColor256Util* Default();
public:
/**
 *
 * Palette table.
 *
 */
	TUint32	iColorTable[256];
/**
 *
 * Inverse palette table for fast rgb matching.
 * The top four bits of each component are concatenated
 * to form a 12 bit index into this table and that entry
 * is the index of the nearest palette entry.
 *
 */
	TUint8	iInverseColorTable[0x1000];
	};

/**
 *
 * Linear digital differential analyser.
 *
 * This is used to calculate the pixels which most closely approximate a
 * specified straight line, or when scaling a bitmap. Note that a line is
 * infinitely thin, and can only be approximated by pixels with real
 * width and height.Functions are provided for:pixel line
 * traversingjumping to a rectangle or co-ordinate
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TLinearDDA
	{
public:

/**
 *
 * LDDA Line mode.
 *
 */
	enum TLineMode
		{
/** Centres scan-lines in the pixel line
 */
		ECenter,
/** Starts at the beginning of a complete scan line.
 * Used for bitmap scaling.
 */
		ELeft
		};
public:
	IMPORT_C TLinearDDA();
	IMPORT_C TLinearDDA(const TLinearDDA& aLine);
	IMPORT_C void Construct(const TPoint& aStart,const TPoint& aFinish,TLineMode aMode=ECenter);
	IMPORT_C TBool SingleStep(TPoint& aPosition);
	IMPORT_C TBool SingleScanline(TPoint& aStartPosition,TPoint& aEndPosition);
	IMPORT_C TBool NextStep(TPoint& aPosition);
	IMPORT_C void JumpToRect(const TRect& aRect);
	IMPORT_C void JumpToXCoord(const TInt aXCoord,TInt& aYCoord);
	IMPORT_C void JumpToYCoord(TInt& aXCoord,const TInt aYCoord);
private:
	void UpdatePosition();
private:
	enum TLineStatus
		{
		EInitialised,
		ECurrent,
		EComplete
		};
private:
	TInt iCount;
	TSize iDifference;
	TPoint iFinish;
	TInt iGradient;
	TPoint iInc;
	TPoint iPos;
	TPoint iStart;
	TRect iBoundingRect;
	TBool iBoundingRectSet;
	TBool iInside;
	TLineStatus iStatus;
	};

/**
 *
 * Font posture flags.
 *
 * Fonts can be either upright or italic.
 *
 */
enum TFontPosture
	{
/** Font posture is normal (upright).
 */
	EPostureUpright,
/** Font posture is italic.
 */
	EPostureItalic
	};

/**
 *
 * Font stroke weight flags.
 *
 */
enum TFontStrokeWeight
	{
/** Font stroke weight is normal.
 */
	EStrokeWeightNormal,
/** Font stroke weight is bold.
 */
	EStrokeWeightBold
	};

/**
 *
 * Font print position flags.
 *
 * Fonts can be normal, superscript or subscript.
 *
 */
enum TFontPrintPosition
	{
/** Font is normal.
 */
	EPrintPosNormal,
/** Font is superscript.
 */
	EPrintPosSuperscript,
/** Font is subscript.
 */
	EPrintPosSubscript
	};

/**
 *
 * Font underline flags.
 *
 */
enum TFontUnderline
	{
/** Font is not underlined.
 */
	EUnderlineOff,
/** Font is underlined.
 */
	EUnderlineOn
	};

/**
 *
 * Font strike-through flags.
 *
 */
enum TFontStrikethrough
	{
/** Font is not struck-through.
 */
	EStrikethroughOff,
/** Font is struck-through.
 */
	EStrikethroughOn
	};

const TInt KMaxTypefaceNameLength=0x18;

/**
 *
 * Typeface name and attributes.
 *
 * This class identifies a typeface by name, and contains the combination
 * of attributes of the typeface. These attributes define whether it is a
 * symbol typeface, whether the typeface is proportional, and whether it
 * is serif or sans-serif. The combination of attributes for a typeface
 * are stored in a bitmask, with the various bits indicating different
 * attributes. The bitmask is calculated for any particular attribute
 * combination by ORing the enumerated value for each individual
 * attribute
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TTypeface
    {
public:

/**
 *
 * Typeface attribute flags.
 *
 */
	enum
		{
/** Typeface is a proportional typeface (e.g. Swiss)
 */
		EProportional=1,
/** Typeface is a serif typeface (e.g. Times)
 */
		ESerif=2,
/** Typeface is a symbol typeface (e.g. Symbol)
 */
		ESymbol=4
		};
public:
	IMPORT_C TTypeface();
	IMPORT_C TBool operator==(const TTypeface& aTypeface) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void SetAttributes(TInt aMask);
	IMPORT_C void SetIsProportional(TBool aIsProportional);
	IMPORT_C void SetIsSerif(TBool aIsSerif);
	IMPORT_C void SetIsSymbol(TBool aIsSymbol);
	IMPORT_C TInt Attributes() const;
	IMPORT_C TBool IsProportional() const;
	IMPORT_C TBool IsSerif() const;
	IMPORT_C TBool IsSymbol() const;
public:
/**
 *
 * The name of the typeface.
 *
 */
    TBufC<KMaxTypefaceNameLength> iName;
private:
    TUint32 iFlags;
    };

/**
An enumerated type for the format of a glyph bitmap.

Glyph bitmaps can differ in the number of bits per pixel, the compression method, and the meaning
of the information for each pixel. This type is used both to specify a desired rendering method, and
to pass information to the text rendering system enabling it to unpack and draw glyphs.

No values must be defined above 65535, because the bitmap type is stored in 16 bits inside TFontStyle.
*/
enum TGlyphBitmapType
	{
	EDefaultGlyphBitmap = 0,	// used to request that the current default method is used, whatever it is
	EMonochromeGlyphBitmap,		// the standard monochrome format: 1 bit per pixel, run-length encoded
	EAntiAliasedGlyphBitmap		// the standard anti-aliased format: 8 bits per pixel
	};

/**
 *
 * Encapsulates a font style.
 *
 * The font style information is comprised of:the posture of the font
 * upright or italicthe stroke weight of the font normal or boldthe
 * print position of the font normal, subscript or superscriptNote
 * that the underline and strike-through styles are not included in this
 * class, but are set in the graphics context.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TFontStyle
	{
public:
	IMPORT_C TFontStyle();
	IMPORT_C TFontStyle(TFontPosture aPost,TFontStrokeWeight aStrWgt,TFontPrintPosition aPrintPos);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TFontPosture Posture() const;
	IMPORT_C TFontStrokeWeight StrokeWeight() const;
	IMPORT_C TFontPrintPosition PrintPosition() const;
	IMPORT_C void SetPosture(TFontPosture aPosture);
	IMPORT_C void SetStrokeWeight(TFontStrokeWeight aStrokeWeight);
	IMPORT_C void SetPrintPosition(TFontPrintPosition aPrintPosition);
	inline TGlyphBitmapType BitmapType() const;
	inline void SetBitmapType(TGlyphBitmapType aBitmapType);
	inline TBool operator==(const TFontStyle& aFontStyle) const;
private:
	enum
		{
		EItalic=0x1,
		EBold=0x2,
		ESuper=0x4,
		ESub=0x8
		};
private:
	TUint32 iFlags; // flags in the low 16 bits, bitmap type in the high 16 bits
	};

/**
 *
 * Font specification.
 *
 * This class specifies the font in device independent terms.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TFontSpec
	{
public:
	IMPORT_C TFontSpec();
	IMPORT_C TFontSpec(const TDesC& aTypefaceName,TInt aHeight);
	IMPORT_C TBool operator==(const TFontSpec& aFontSpec) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TTypeface iTypeface;
	TInt iHeight;
	TFontStyle iFontStyle;
	};

/**
 *
 * Typeface family support information.
 *
 * This data-only class includes the name and attributes of a typeface,
 * how many font heights are available, its minimum and maximum heights,
 * and whether or not it is scaleable a typeface is scaleable if it
 * supports heights at fixed intervals between the minimum and maximum
 * heights.
 *
 * @since 5.0
 */
class TTypefaceSupport
    {
public:
    TTypeface iTypeface;
    TInt iNumHeights;
    TInt iMinHeightInTwips;
    TInt iMaxHeightInTwips;
    TBool iIsScalable; // supports heights from min to max at fixed interval
    };

const TInt KSuperSubScalingPercentage=67;
const TInt KSuperscriptOffsetPercentage=-28;
const TInt KSubscriptOffsetPercentage=14;

class CFont;

/**
 *
 * Typeface store abstract base interface.
 *
 * This class provides the interface of a store for typefaces.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CTypefaceStore : public CBase
	{
public:
	IMPORT_C ~CTypefaceStore();

/**
 *
 * Gets the bitmap font in the current graphics map which is nearest to
 * the specified font specification.
 *
 * @param     "CFont*& aFont"
 *            On return, contains a pointer to the nearest bitmap
 *            font.
 * @param     "const TFontSpec& aFontSpec"
 *            The device independent font specification of the font
 *            to be found.
 * @returns   "TInt"
 *            <code>KErrNone</code> if no nearest font can be found
 *            or if there was no error, <code>KErrNoMemory</code> if
 *            a nearest font can be found but no memory can be
 *            allocated to it in the font store, or another of the
 *            system-wide error codes.
 */
	virtual TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec)=0;

/**
 *
 * Gets the number of typefaces supported by the typeface store.
 *
 * @returns   "TInt"
 *            The number of supported typefaces.
 */
	virtual TInt NumTypefaces() const=0;

/**
 *
 * Gets typeface information for a specified typeface index.
 *
 * This information is returned in <code>aTypefaceSupport</code>, and
 * includes the typeface name and typeface attributes, the number of font
 * heights, the maximum and minimum font heights, and whether it is a
 * scaleable typeface.
 *
 * @param     "TTypefaceSupport& aTypefaceSupport"
 *            On return, if the function executed successfully, this
 *            object contains the typeface information.
 * @param     "TInt aTypefaceIndex"
 *            A typeface index number, in the range: zero to
 *            (<code>NumTypefaces() - 1</code>).
 */
	virtual void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const=0;

/**
 *
 * Gets the height of the font with specified height and typeface
 * indices, in twips.
 *
 * The value returned is rounded up or down to the nearest font height in
 * twips.
 *
 * @param     "TInt aTypefaceIndex"
 *            A typeface index number, in the range: 0 to
 *            (<code>NumTypefaces() - 1</code>).
 * @param     "TInt aHeightIndex"
 *            A font height index number, in the range: 0 to
 *            (<code>iNumHeights - 1</code>). Note:
 *            <code>TTypefaceSupport::iNumHeights</code> is returned
 *            by <code>TypefaceSupport()</code>.
 * @returns   "TInt"
 *            The height of the font, in twips.
 */
	virtual TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const=0;
	IMPORT_C void ReleaseFont(CFont* aFont);
	IMPORT_C static TInt BaselineOffset(TInt aHeight,TFontPrintPosition aPos);
	IMPORT_C static TInt SuperSubHeight(TInt aHeight,TFontPrintPosition aPos);
protected:
	IMPORT_C CTypefaceStore();
	IMPORT_C void ConstructL();
	IMPORT_C void AddFontL(CFont* aFont);
protected:
	class TFontAccess
		{
	public:
		CFont* iFont;
		TInt iAccessCount;
		};
protected:
	CArrayFixFlat<TFontAccess>* iFontAccess;
	};

const TInt KMaxFontCacheEntries=32;

/**
 *
 * Font cache.
 *
 * When a <code>CFont*</code> needs to be found for a particular
 * <code>TFontSpec</code>, the cache can be searched to see if the
 * <code>TFontSpec</code> is already in the cache. If the
 * <code>TFontSpec</code> is in the cache, its corresponding
 * <code>CFont*</code> can be returned. Otherwise
 * <code>GetNearestFontInTwips()</code> must be used to search all of the
 * available fonts for the nearest <code>CFont</code> a procedure which
 * takes much longer than a simple cache search.The current font cache
 * should be destroyed and a new cache created whenever the zoom factor
 * or device map changes, as these changes break the relation between
 * <code>CFont</code> and <code>TFontSpec</code>.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CFontCache : public CBase
	{
public:
	IMPORT_C CFontCache();
	IMPORT_C CFontCache(TInt aMaxEntries);
	IMPORT_C ~CFontCache();
	IMPORT_C CFont* Search(const TFontSpec& aFontSpec);
	IMPORT_C CFont* AddEntryL(CFont* aFont,const TFontSpec& aFontSpec);
	IMPORT_C CFont* RemoveFirstEntry();
public:
/**
 *
 * Count of the number of cache hits since creation.
 *
 */
	TInt iNumHits;
/**
 *
 * Count of the number of cache misses since creation.
 *
 */
	TInt iNumMisses;
private:
	class CFontCacheEntry : public CBase
		{
	public:
		CFontCacheEntry(CFont* aFont,const TFontSpec& aFontSpec,CFontCacheEntry* aNext);
	public:
		CFont* iFont;
		TFontSpec iSpec;
		CFontCacheEntry* iNext;
		};
private:
	TInt iNumEntries;
	TInt iMaxEntries;
	CFontCacheEntry* iFirst;
	};

/**
 *
 * Interface class for mapping between twips and device-specific units
 * (pixels).
 *
 * <code>CGraphicsContext</code> and <code>TZoomFactor</code> are derived
 * from <code>MGraphicsDeviceMap</code>.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class MGraphicsDeviceMap
    {
public:
	IMPORT_C MGraphicsDeviceMap();
	IMPORT_C virtual ~MGraphicsDeviceMap();
	IMPORT_C TPoint TwipsToPixels(const TPoint& aTwipPoint) const;
	IMPORT_C TRect TwipsToPixels(const TRect& aTwipRect) const;
	IMPORT_C TPoint PixelsToTwips(const TPoint& aPixelPoint) const;
	IMPORT_C TRect PixelsToTwips(const TRect& aPixelRect) const;

/**
 *
 * Converts a horizontal dimension from twips to pixels.
 *
 * An implementation is supplied by a derived class.
 *
 * @param     "TInt aTwips"
 *            A horizontal dimension of a device in twips.
 * @returns   "TInt"
 *            A horizontal dimension of a device in pixels.
 */
	virtual TInt HorizontalTwipsToPixels(TInt aTwips) const=0;

/**
 *
 * Converts a vertical dimension from twips to pixels.
 *
 * An implementation is supplied by a derived class.
 *
 * @param     "TInt aTwips"
 *            A vertical dimension of a device in twips.
 * @returns   "TInt"
 *            A vertical dimension of a device in pixels.
 */
	virtual TInt VerticalTwipsToPixels(TInt aTwips) const=0;

/**
 *
 * Converts a horizontal dimension from pixels to twips.
 *
 * An implementation is supplied by a derived class.
 *
 * @param     "TInt aPixels"
 *            A horizontal dimension of a device in pixels.
 * @returns   "TInt"
 *            A horizontal dimension of a device in twips.
 */
	virtual TInt HorizontalPixelsToTwips(TInt aPixels) const=0;

/**
 *
 * Converts a vertical dimension from pixels to twips.
 *
 * An implementation is supplied by a derived class.
 *
 * @param     "TInt aPixels"
 *            A vertical dimension of a device in pixels.
 * @returns   "TInt"
 *            A vertical dimension of a device in twips.
 */
	virtual TInt VerticalPixelsToTwips(TInt aPixels) const=0;

/**
 *
 * Gets the nearest font to that in the given font specification.
 *
 * The font and bitmap server returns a pointer to the nearest matching
 * font from those available.An implementation is supplied by a derived
 * class.
 *
 * @param     "CFont*& aFont"
 *            On return, this pointer is set to point to the device
 *            font which most closely approximates to the font
 *            specification.
 * @param     "const TFontSpec& aFontSpec"
 *            An absolute font specification.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
	virtual TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec)=0;

/**
 *
 * Releases the specified font.
 *
 * It is used to indicate that the specified font is no longer needed for
 * use by the device map. As fonts can be shared between applications,
 * this function does not delete the copy of the font from RAM unless the
 * font was only being used by this particular device map.An
 * implementation is supplied by a derived class.
 *
 * @param     "CFont* aFont"
 *            A pointer to the font to be released.
 */
	virtual void ReleaseFont(CFont* aFont)=0;
    };

class CGraphicsContext;

/**
 *
 * Specifies the interface for concrete device classes.
 *
 * It holds information on the capabilities and attributes of a graphics
 * device. The <code>CBitmapDevice</code> and <code>CPrinterDevice</code>
 * classes are derived from <code>CGraphicsDevice</code>.
 *
 * @since 5.0
 */
class CGraphicsDevice : public CBase , public MGraphicsDeviceMap
    {
public:

/**
 *
 * Gets the display mode of the device.
 *
 * @returns   "TDisplayMode"
 *            The display mode of the device.
 */
	virtual TDisplayMode DisplayMode() const=0;

/**
 *
 * Gets the size of the device area in pixels.
 *
 * @returns   "TSize"
 *            The width and height of the device area, in pixels
 */
	virtual TSize SizeInPixels() const=0;

/**
 *
 * Gets the size of the device area in twips.
 *
 * @returns   "TSize"
 *            The width and height of the device area, in twips
 */
	virtual TSize SizeInTwips() const=0;

/**
 *
 * Creates a graphics context for the device.
 *
 * @param     "CGraphicsContext*& aGC"
 *            On return, contains a pointer to the created graphics
 *            context.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
    virtual TInt CreateContext(CGraphicsContext*& aGC)=0;

/**
 *
 * Gets the number of typefaces supported by the graphics device.
 *
 * @returns   "TInt"
 *            The number of typefaces supported.
 */
    virtual TInt NumTypefaces() const=0;

/**
 *
 * Gets typeface information for a specified typeface.
 *
 * This information is returned in <code>aTypefaceSupport</code>, and
 * includes:the typeface name and typeface attributesthe number of font
 * heightsthe maximum and minimum font heightswhether it is a scalable
 * typeface
 *
 * @param     "TTypefaceSupport& aTypefaceSupport"
 *            On return, contains the typeface information.
 * @param     "TInt aTypefaceIndex"
 *            A typeface index number, in the range: zero to
 *            (<code>NumTypefaces() - 1</code>).
 */
    virtual void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const=0;

/**
 *
 * Get the height of a font in twips.
 *
 * The font is identified by typeface and height.The value returned is
 * rounded up or down to the nearest font height in twips.
 *
 * @param     "TInt aTypefaceIndex"
 *            An index identifying the typeface, in the range:
 *            <code>0</code> to (<code>NumTypefaces() - 1</code>).
 * @param     "TInt aHeightIndex"
 *            An index identifying the font height, in the range:
 *            <code>0</code> to <code>(iNumHeights - 1)</code>. Note
 *            that <code>iNumHeights</code> is in the
 *            <code>TTypefaceSupport</code> object returned by
 *            <code>TypefaceSupport()</code>.
 * @returns   "TInt"
 *            The height of the font, in twips.
 */
	virtual TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const=0;

/**
 *
 * Gets the palette attributes of the device.
 *
 * @param     "TBool& aModifiable"
 *            On return, holds information on whether or not the
 *            devices palette is modifiable (true) or fixed (false).
 * @param     "TInt& aNumEntries"
 *            On return, holds the number of entries in the devices
 *            palette.
 */
	virtual void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const=0;

/**
 *
 * Sets the devices palette.
 *
 * @param     "CPalette* aPalette"
 *            The new palette for the device.
 */
	virtual void SetPalette(CPalette* aPalette)=0;

/**
 *
 * Gets the devices current palette.
 *
 * @param     "CPalette*& aPalette"
 *            On return, holds the devices current palette.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
	virtual TInt GetPalette(CPalette*& aPalette) const=0;
    };


/**
 *
 * Deprecated.
 *
 * This is not used anywhere in version 6.0.Code section range
 * information. A code section defines the bitmaps for characters in a
 * specified range the range is stored in objects of this type.
 *
 * @since 5.0
 */
class TCodeSection
	{
public:
	TInt iStart;
	TInt iEnd;
	};

/**
 *
 * Abstract font interface.
 *
 * The <code>CFont</code> class provides a device-independent interface
 * to a device-dependent font usually obtained from a call to
 * <code>GetNearestFont()</code> on a graphics device. It is used as a
 * handle in <code>CGraphicsContext::UseFont()</code> and to obtain
 * device-dependent information about the font notably the pixel
 * width of a text string.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CFont: public CBase
    {
	friend class CTypefaceStore;
public:

/**
 *
 * Text direction flags.
 
 *
 * This enum is used in <code>TMeasureTextInput</code> and determines
 * whether the text is drawn horizontally or vertically. Note: text is
 * drawn vertically in some styles of Japanese, etc.
 * * @since 
 */
	enum TTextDirection
		{
/** Text is drawn horizontally.
 */
		EHorizontal,
/** Text is drawn vertically.
 */
		EVertical
		};

/**
 *
 * Complicated parameter block used for contextual glyph selection,
 * ligature creation and diacritic placement when drawing text in complex
 * scriptsThis class declares a constructor, another scoped class, and
 * several other enums.
 *
 * However this class is not unlikely to be useful to third party
 * developers, and so these have not been fully documented.
 *
 * @lib "gdi.lib"
 */
	class TPositionParam
		{
	public:
		TPositionParam():
			iDirection(EHorizontal),
			iPosInText(0),
			iOutputGlyphs(0)
			{
			}

		enum
			{
			EMaxInputChars = 18,	// ligatures cannot be made from more than 18 components
			EMaxOutputGlyphs = 8	// output can consist of up to 8 characters (one base and 7 combining characters)
			};

		// inputs
		TTextDirection iDirection;	// direction to draw the text
		TPtrC iText;				// text containing the characters to be positioned

		// members used for both input and output
		TInt iPosInText;		// position in iText
		TPoint iPen;			// pen position

		// output
		class TOutput
			{
		public:
			TOutput() : iBitmapSize(TSize::EUninitialized),
				iBounds(TRect::EUninitialized) {}
			TUint iCode;			// character or glyph code
			const TUint8* iBitmap;	// bitmap data for the glyph, if available
			TSize iBitmapSize;		// size of the bitmap before algorithmic bolding, size multiplication, etc.
			TRect iBounds;			// bitmap bounds, relative to the original pen position
			};

		TOutput iOutput[EMaxOutputGlyphs];	// information about the glyphs that were output
		TInt iOutputGlyphs;					// number of glyphs actually output
		};	

/**
 *
 * Input parameter block.
 *
 * This is optionally used by <code>CFont::MeasureText()</code>, which is
 * the powerful text measurement function underlying all the other text
 * measurement functions.
 *
 * @lib "gdi.lib"
 */
	class TMeasureTextInput
		{
		public:
		TMeasureTextInput():
			iStartInputChar(0),
			iEndInputChar(KMaxTInt),
			iDirection(EHorizontal),
			iMaxAdvance(KMaxTInt),
			iMaxBounds(KMaxTInt),
			iCharJustNum(0),
			iCharJustExcess(0),
			iWordJustNum(0),
			iWordJustExcess(0)
			{
			}

		TInt iStartInputChar;	// starting index in iText; together with iMaxInputChars,
		TInt iEndInputChar;		// allows some context before and after the measured text to be supplied
								// so that shaping can work properly.
		TTextDirection iDirection;	// direction text is to be drawn in
		TInt iMaxAdvance;		// maximum advance
		TInt iMaxBounds;		// maximum width (or height if drawing vertically) of bounds
		TInt iCharJustNum;		// number of glyph groups to be letterspaced
		TInt iCharJustExcess;	// amount of space to be used for letterspacing
		TInt iWordJustNum;		// number of spaces to be used for wordspacing
		TInt iWordJustExcess;	// amount of space to be used for wordspacing
		};

/**
 *
 * Output parameter block.
 *
 * This is optionally used by <code>CFont::MeasureText()</code>, which is
 * the powerful text measurement function underlying all the other text
 * measurement functions.
 *
 * @lib "gdi.lib"
 */
	class TMeasureTextOutput
		{
		public:
		TInt iChars;			// number of input characters that would be drawn - this may be less than
								// the length of the text if a maximum advance or bounding box size is specified
		TInt iGlyphs;			// number of glyphs that would be drawn
		TInt iGroups;			// number of groups that would be drawn; a group is a base glyph plus one or more
								// combining characters
		TInt iSpaces;			// number of word spaces (U+0020) that would be drawn
		TRect iBounds;			// bounding box of all the glyphs that would be drawn
		TSize iMaxGlyphSize;	// maximum width and height of any glyph
		};


/**
 *
 * Data availability flags.
 
 *
 * Some fonts like printer fonts may only have width information and can
 * return <code>ECharacterWidthOnly</code> to show this: the text drawing
 * routines in <code>CFont</code> synthesize the rest of the data if
 * necessary.
 * * @since 
 */
	enum TCharacterDataAvailability
		{
/** No font information available.
 */
		ENoCharacterData,
/** Width information only is available.
 */
		ECharacterWidthOnly,
/** All character data is available.
 */
		EAllCharacterData
		};
public:

/**
 *
 * Gets run-time identity of the actual font type.
 *
 * This enables safe casting to a derived type.For example, if the
 * derived type is a <code>CFbsFont</code>, the return value is
 * <code>KCFbsFontUid</code>. You would need to cast to a
 * <code>CFbsFont</code> to get a character bounding box. Similarly, a
 * <code>CBitmapFont</code> returns <code>KCBitmapFontUidVal</code>.
 *
 * @returns   "TUid"
 *            The font-type identifier.
 */
	virtual TUid TypeUid() const=0;

/**
 *
 * Gets the height of the font in pixels.
 *
 * @returns   "TInt"
 *            The height of the font in pixels.
 */
	virtual TInt HeightInPixels() const=0;

/**
 *
 * Gets the ascent of the font in pixels.
 *
 * @returns   "TInt"
 *            The ascent of the font in pixels.
 */
	virtual TInt AscentInPixels() const=0;
	IMPORT_C virtual TInt DescentInPixels() const;

/**
 *
 * Gets the width in pixels in this font of the specified character.
 *
 * @param     "TChar aChar"
 *            The character whose width should be determined.
 * @returns   "TInt"
 *            The width in pixels of the specified character in this
 *            font.
 */
	virtual TInt CharWidthInPixels(TChar aChar) const=0;

/**
 *
 * Gets the width in pixels of the specified descriptor when displayed in
 * this font.
 *
 * @param     "const TDesC& aText"
 *            The descriptor whose width should be determined.
 * @returns   "TInt"
 *            The width of the specified descriptor when displayed
 *            in this font, in pixels.
 */
	virtual TInt TextWidthInPixels(const TDesC& aText) const=0;

/**
 *
 * Gets the baseline offset in pixels.
 *
 * The baseline offset is how far a font is raised or lowered from its
 * normal baseline.
 *
 * @returns   "TInt"
 *            Offset from normal baseline, in pixels.
 */
	virtual TInt BaselineOffsetInPixels() const=0;

/**
 *
 * Gets how much of the specified descriptor can be displayed in this
 * font without exceeding the specified width.
 *
 * @param     "const TDesC& aText"
 *            The descriptor.
 * @param     "TInt aWidthInPixels"
 *            The available width for character display.
 * @returns   "TInt"
 *            The number of characters which will be able to be
 *            displayed without exceeding the specified width. The
 *            count starts from the beginning of the descriptor.
 */
	virtual TInt TextCount(const TDesC& aText,TInt aWidthInPixels) const=0;

/**
 *
 * Gets how much of the specified descriptor can be displayed in this
 * font without exceeding the specified width.
 *
 * It also returns the excess width defined as the specified
 * available width minus the width of the portion of the descriptor which
 * can be displayed without exceeding the available width.
 *
 * @param     "const TDesC& aText"
 *            The descriptor.
 * @param     "TInt aWidthInPixels"
 *            The available width for character display.
 * @param     "TInt& aExcessWidthInPixels"
 *            The excess width after displaying the portion of the
 *            descriptor, in pixels.
 * @returns   "TInt"
 *            The number of characters which will be able to be
 *            displayed without exceeding the specified width. The
 *            count starts from the beginning of the descriptor.
 */
	virtual TInt TextCount(const TDesC& aText,TInt aWidthInPixels,TInt& aExcessWidthInPixels) const=0;

/**
 *
 * Gets the width in pixels of the widest character in this font.
 *
 * @returns   "TInt"
 *            The width of the maximum width character, in pixels.
 */
	virtual TInt MaxCharWidthInPixels() const=0;

/**
 *
 * Gets the width in pixels of the widest normal character in this font.
 *
 * Normal characters include all character in a character set except
 * non-alphabetic characters (e.g. the copyright symbol, or a block
 * graphics symbol, for example).
 *
 * @returns   "TInt"
 *            The width of the maximum width normal character, in
 *            pixels.
 */
	virtual TInt MaxNormalCharWidthInPixels() const=0;

/**
 *
 * Gets the font specification of this font in twips.
 *
 * @returns   "TFontSpec"
 *            The specification of this font in twips.
 */
	virtual TFontSpec FontSpecInTwips() const=0;
	IMPORT_C virtual TCharacterDataAvailability GetCharacterData(TUint aCode,
		TOpenFontCharMetrics& aMetrics,const TUint8*& aBitmap,TSize& aBitmapSize) const;
	IMPORT_C virtual TBool GetCharacterPosition(TPositionParam& aParam) const;
	IMPORT_C virtual void Reserved();
	// New functions
	IMPORT_C TInt WidthZeroInPixels() const;
	IMPORT_C TInt MeasureText(const TDesC& aText,const TMeasureTextInput* aInput = NULL,
		TMeasureTextOutput* aOutput = NULL) const;
protected:
	IMPORT_C virtual ~CFont();
    };

class CFbsBitmap;

/**
 *
 * Abstract, device independent, interface to graphics contexts.
 *
 * The class <code>CBitmapContext</code> is derived from this class.See
 * <code>CGraphicsContext::Reset()</code> for the default settings of a
 * graphics context immediately after construction.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CGraphicsContext : public CBase
	{
public:

/**
 *
 * Text alignment.
 *
 */
	enum TTextAlign
		{
/** Text is left-aligned.
 */
		ELeft,
/** Text is centred.
 */
		ECenter,
/** Text is right-aligned.
 */
		ERight
		};

/**
 *
 * Drawing mode components.
 *
 * This enum is not intended to be used directly, but provides components
 * for the easy specification of drawing modes in the
 * <code>TDrawMode</code> enum.
 *
 */
	enum TDrawModeComponents
		{
		EInvertScreen=1,
		EXor=2,
		EOr=4,
		EAnd=8,
		ELogicalOp=14,
		EInvertPen=16,
		EPenmode=32
		};

/**
 *
 * Drawing modes.
 
 *
 * This enum builds on the drawing mode components in the
 * <code>TDrawModeComponents</code> enum.If the pen colour is
 * <code>p</code>, brush colour is <code>b</code> and screen colour is
 * <code>s</code>, the effect of <code>TDrawMode::EDrawModeAND</code> is
 * <code>P=p&s</code> and <code>B=b&s</code>. In other words, the
 * effective colour of the pen on the screen, <code>P</code>, is that
 * produced by the bitwise ANDing of the current screen colour and the
 * current pen colour. The effect is similar for the effective brush
 * colour, <code>B</code>.The effective pen and brush colour are given in
 * the table using the keyInputs: pen colour is p, brush colour is b and
 * screen colour is sOutputs: effective brush colour is B, effective pen
 * colour is P.
 *
 */
	enum TDrawMode
		{
/** Bitwise ANDs the pen and brush colours with the screen colour. P=p&s, B=b&s
 */
		EDrawModeAND=EAnd,
/** Inverts the pen and brush colours before ANDing. P=(~p)&s, B=(~b)&s
 */
		EDrawModeNOTAND=EInvertScreen|EAnd,
/** Uses both pen and brush colour as they are. P=p, B=b
 */
		EDrawModePEN=EPenmode,
/** Inverts the screen colour before ANDing. P=p&(~s), B=b&(~s)
 */
		EDrawModeANDNOT=EAnd|EInvertPen,
/** Bitwise XORs the pen and brush colours with the screen colour. P=p^s, B=b^s
 */
		EDrawModeXOR=EXor,
/** Bitwise ORs the pen and brush colours with the screen colour. P=p|s, B=b|s
 */
		EDrawModeOR=EOr,
/** Inverts the screen and pen and brush colours before ANDing. P=(~p)&(~s), B=(~b)&(~s)
 */
		EDrawModeNOTANDNOT=EInvertScreen|EAnd|EInvertPen,
/** Inverts the pen and brush colours before XORing. P=(~p)^s, B=(~b)^s
 */
		EDrawModeNOTXOR=EInvertScreen|EXor,
/** Inverts the colour of each pixel that is drawn over,
 * (pen and brush attributes are ignored). P=~s, B=~s
 */
		EDrawModeNOTSCREEN=EInvertScreen,
/** Inverts the pen and brush colours before ORing. P=(~p)|s, B=(~b)|s
 */
		EDrawModeNOTOR=EInvertScreen|EOr,
/** Inverts the pen and brush colours. P=~p, B=~b
 */
		EDrawModeNOTPEN=EInvertPen|EPenmode,
/** Inverts the screen, pen and brush colours before ORing. P=p|(~s), B=b|(~s)
 */
		EDrawModeORNOT=EOr|EInvertPen,
/** NOT OR NOT mode. P=(~p)|(~s), B=(~b)|(~s)
 */
		EDrawModeNOTORNOT=EInvertScreen|EOr|EInvertPen
		};

/**
 *
 * Pen styles.
 *
 * The screen pattern unit in each definition below describes the pattern
 * drawn by the line 1 represents a pixel drawn, 0 represents a pixel
 * that is not affected.
 *
 */
	enum TPenStyle
		{
/** The pen does not draw. Screen pattern unit = 00
 */
		ENullPen,
/** A solid line (default). Screen pattern unit = 11
 */
		ESolidPen,
/** A dotted line. Screen pattern unit = 1000
 */
		EDottedPen,
/** A dashed line. Screen pattern unit = 111000
 */
		EDashedPen,
/** A line of alternating dashes and dots. Screen pattern unit = 1111001100...
 */
		EDotDashPen,
/** A line of alternating single dashes and pairs of dots.
 * Screen pattern unit = 11110011001100...
 */
		EDotDotDashPen
		};

/**
 *
 * Brush styles.
 *
 */
	enum TBrushStyle
		{
/** The brush fill has no effect (default).
 */
		ENullBrush,
/** The brush fills with a solid single colour, determined
 * by <code>SetBrushColor()</code> and the drawing mode.
 */
		ESolidBrush,
/** The brush fills with a selected bitmap pattern,
 * set by <code>UseBrushPattern()</code>.
 */
		EPatternedBrush,
/** The brush fills with vertical hatching lines going from top to bottom.
 */
		EVerticalHatchBrush,
/** The brush fills with diagonal hatching lines going from bottom left to top right.
 */
		EForwardDiagonalHatchBrush,
/** The brush fills with horizontal hatching lines going from left to right.
 */
		EHorizontalHatchBrush,
/** The brush fills with rearward diagonal hatching lines going from top
 * left to bottom right.
 */
		ERearwardDiagonalHatchBrush,
/** The brush fills with horizontal and vertical hatching lines going from
 * left to right plus lines going from top to bottom giving the effect of
 * a grid of small squares
 */
		ESquareCrossHatchBrush,
/** The brush fills with forward diagonal and rearward diagonal hatching
 * lines going from bottom left to top right plus lines going from top
 * left to bottom right giving the effect of a grid of small diamonds.
 */
		EDiamondCrossHatchBrush
		};

/**
 *
 * Rules used to fill self crossing polygons.
 *
 * The filling of a polygon proceeds as follows: for a given point in the
 * polygon, thenif the rule is <code>TFillRule::EAlternate</code>
 * (default) and it has an odd winding number, then fill the surrounding
 * area.if the rule is <code>TFillRule::EWinding</code> and it has a
 * winding number greater than zero, then fill the surrounding area.
 *
 */
	enum TFillRule
		{
/** Only fill areas with odd winding numbers.
 */
		EAlternate,
/** Fill areas with winding numbers greater than zero.
 */
		EWinding
		};

/**
 *
 * Parameters to control the drawing of text.
 *
 */
	struct TDrawTextParam
		{
	public:
		TDrawTextParam():
			iDirection(CFont::EHorizontal),
			iCharJustNum(0),
			iCharJustExcess(0),
			iWordJustNum(0),
			iWordJustExcess(0)
			{}
	public:
		CFont::TTextDirection iDirection;	// the direction in which to draw the text
		TInt iCharJustNum;					// number of glyph groups to be letterspaced
		TInt iCharJustExcess;				// amount of space to be used for letterspacing
		TInt iWordJustNum;					// number of spaces to be used for wordspacing
		TInt iWordJustExcess;				// amount of space to be used for wordspacing
		};

/**
 *
 * Parameters for extended text drawing and measuring
 *
 */
	struct TDrawTextExtendedParam : public TDrawTextParam
		{
	public:
		TDrawTextExtendedParam():
			iParRightToLeft(EFalse)
			{}
	public:
		TBool iParRightToLeft;				// true if the paragraph direction is right to left
		};


public:

/**
 *
 * Gets a pointer to the graphics contexts graphics device.
 *
 * @returns   "CGraphicsDevice*"
 *            A pointer to the graphics device.
 */
	virtual CGraphicsDevice* Device() const=0;

/**
 *
 * Sets the position of the co-ordinate origin.
 *
 * All subsequent drawing operations are done relative to this origin.
 *
 * @param     "const TPoint& aPos"
 *            The origin. The default origin is
 *            <code>TPoint(0,0)</code> the top left corner of the
 *            screen.
 */
	virtual void SetOrigin(const TPoint& aPos=TPoint(0,0))=0;

/**
 *
 * Sets the drawing mode.
 *
 * The way that the pen and brush draw depends on the drawing mode. The
 * drawing mode affects the colour that is actually drawn, because it
 * defines the way that the current screen colour logically combines with
 * the current pen colour and brush colour. There are 13 drawing modes,
 * each giving different logical combinations of pen, brush and screen
 * colours. Each mode is produced by ORing together different
 * combinations of seven drawing mode components.The three most important
 * modes are <code>TDrawMode::EDrawModePEN</code>,
 * <code>TDrawMode::EDrawModeNOTSCREEN</code> and
 * <code>TDrawMode::EDrawModeXOR</code>. The default drawing mode is
 * <code>TDrawMode::EDrawModePEN</code>.The drawing mode is over-ridden
 * for line and shape drawing functions when a wide pen line has been
 * selected. It is forced to <code>TDrawMode::EDrawModePEN</code>. This
 * is to prevent undesired effects at line joins
 * (vertexes).Notes<code>TDrawMode::EDrawModeAND</code> gives a "colour
 * filter" effect. For example:ANDing with white gives the original
 * colourANDing with black gives black<code>TDrawMode::EDrawModeOR</code>
 * gives a "colour boost" effect. For example:ORing with black gives the
 * original colourORing with white gives
 * white<code>TDrawMode::EDrawModeXOR</code> gives an "Exclusive OR"
 * effect. For example:white XOR black gives whitewhite XOR white gives
 * blackblack XOR black gives black
 *
 * @param     "TDrawMode aDrawingMode"
 *
 */
	virtual void SetDrawMode(TDrawMode aDrawingMode)=0;

/**
 *
 * Sets the clipping rectangle.
 *
 * The area of visible drawing depends on the clipping region. The
 * default clipping rectangle is the full device area.
 *
 * @param     "const TRect& aRect"
 *            The clipping rectangle.
 */
	virtual void SetClippingRect(const TRect& aRect)=0;

/**
 *
 * Cancels any clipping rectangle.
 *
 * Clipping thus reverts to the full device area, the default.
 *
 */
	virtual void CancelClippingRect()=0;

/**
 *
 * Resets the graphics context to its default settings:the drawing mode
 * is <code>TDrawMode::EDrawModePen</code> (pen and brush colours used as
 * they are)there is no clipping rectangle the pen settings are: black,
 * solid, single pixel size the brush style is null no text font is
 * selected.
 *
 */
	virtual void Reset()=0;

/**
 *
 * Sets the device font to be used for text drawing.
 *
 * If the font is already in memory, then that copy is shared.Notes:The
 * <code>CFont*</code> argument must have been previously initialised by
 * calling <code>MGraphicsDeviceMap::GetNearestFontInTwips()</code> with
 * the required font-specification. If the <code>CFont*</code> has not
 * been initialised correctly, and therefore does not point to an
 * available font-bitmap, then a panic is raised.When the font is no
 * longer required, use <code>DiscardFont()</code> to free up the memory
 * used. If <code>UseFont()</code> is used again without using
 * <code>DiscardFont()</code> then the previous font is discarded
 * automatically.If no font has been selected, and an attempt is made to
 * draw text with <code>DrawText()</code>, then a panic is raised.
 *
 * @param     "const CFont* aFont"
 *            A device font
 */
	virtual void UseFont(const CFont* aFont)=0;

/**
 *
 * Discards a font.
 *
 * This frees up the memory used, if the font is not being shared.The
 * function can be called when no font is in use.
 *
 */
	virtual void DiscardFont()=0;

/**
 *
 * Sets the underline style.
 *
 * This is applied to all subsequently drawn text.
 *
 * @param     "TFontUnderline aUnderlineStyle"
 *            The underline style on or off.
 */
	virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle)=0;

/**
 *
 * Sets the strikethrough style.
 *
 * This is applied to all subsequently drawn text.
 *
 * @param     "TFontStrikethrough aStrikethroughStyle"
 *            The strikethrough style on or off.
 */
	virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle)=0;
	IMPORT_C static TInt JustificationInPixels(TInt aExcessPixels,TInt aTotalUnits,TInt aFirstUnit,TInt aNumUnits);
	IMPORT_C static TInt JustificationInPixels(TInt& aExcessPixels,TInt& aTotalUnits);

/**
 *
 * Adjusts the spaces between words to stretch or squeeze to a certain
 * width.
 *
 * The function is required by the Text Views API, and is not intended
 * for regular use by developers.The text line that is to be justified
 * has a certain number of gaps (spaces) between the words. It also has a
 * distance (in pixels) between the end of the last word and the actual
 * end of the line (right hand margin, usually). These excess width
 * pixels are distributed amongst the gaps between the words to achieve
 * full justification of the text line. Spaces become fat spaces to keep
 * underlining/strikethrough consistent. Pixels are distributed to the
 * inter-word gaps starting from the left end of the string. The spacing
 * between characters in each word remains unchanged.After a call to
 * <code>SetWordJustification()</code>, subsequent calls to either of the
 * two <code>DrawText()</code> functions are affected until the number of
 * spaces specified by <code>aNumSpaces</code> is used up.The easiest way
 * to find out the excess width and number of spaces is to call
 * <code>CFont::MeasureText()</code>. This function can also perform
 * counting, which is finding how much of some text will fit into a given
 * width.Use <code>CFont::TextCount()</code> to return the excess
 * width.For example, in the string "To be, or not to be", there are five
 * inter-word gaps. If there are six excess pixels they will be
 * distributed in the proportion 2, 1, 1, 1, 1 between the words. If
 * there are nine excess pixels they will be distributed in the
 * proportion 2, 2, 2, 2, 1 between the words.Notes:If the excess width
 * is zero, then calling <code>SetWordJustification()</code> has no
 * effect.At first sight it may appear that
 * <code>SetWordJustification()</code> is not required because you can
 * simply call <code>DrawText()</code> for each word. However, underlined
 * justified text does not work using this strategy you get a
 * non-underlined gap between the space and the beginning of the next
 * word.
 *
 * @param     "TInt aExcessWidth"
 *            The width (in pixels) to be distributed between the
 *            specified number of spaces. It may be positive, in
 *            which case the text is stretched, or negative, in
 *            which case it is shrunk.
 * @param     "TInt aNumGaps"
 *            The number of word spaces (characters with the code
 *            U+0020) over which the change in width is distributed.
 */
	virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps)=0;

/**
 *
 * Sets character justification.
 *
 * This function is required by the Text Views API, and is not intended
 * for regular use by developers.It affects the strings of text used in
 * the calls to <code>DrawText()</code> that follow, until the number of
 * characters drawn equals <code>aNumChars</code>.The text line that is
 * to be justified has a certain number of characters this includes the
 * spaces between the words. It also has a distance (in pixels) between
 * the end of the last word and the actual end of the line (right hand
 * margin, usually). These excess width pixels are distributed amongst
 * all the characters, increasing the gaps between them, to achieve full
 * justification of the text line.Use <code>CFont::TextCount()</code> to
 * return the excess width.Notes:This function is provided to allow
 * simulation of printer fonts on screen. Due to the fact that
 * fully-scalable fonts are not used before ER5, large printer fonts can
 * be simulated by using the nearest smaller font and widening it
 * slightly.If the excess width is zero, then calling
 * <code>SetCharJustification()</code> has no
 * effect.<code>SetCharJustification()</code> is required for WYSIWYG
 * where the layout uses printer font metrics but screen fonts have to be
 * drawn on the screen. Because continuously scalable typefaces (c.f.
 * TrueType) are not used before ER5 and because screen fonts are coarser
 * and less numerous in their variety than the printer fonts, the best
 * matching smaller screen font must be used with character justification
 * to simulate the printer font on the screen.There is also a situation
 * where the gaps between characters on screen have to be reduced with
 * character clipping. The screen font that best matches the printer font
 * may have the required height, but has characters that are too wide. A
 * line of text that works on the printer will then be too long on the
 * screen, unless it is squashed horizontally. The number of pixels that
 * overlap the end of the screen line must now be removed from the gaps
 * between the characters, i.e. there is a negative excess width. This
 * situation is especially important where adding a TAB on screen gives
 * perfectly acceptable printout, but would push the last character of
 * the line off the right hand side of the screen.In practice what you do
 * in printer layout mode is:Calculate where the line breaks will come on
 * the printer. To do this you use a printer font (which in practice
 * means a table of character widths of the font that the printer will
 * use).Now change to use a screen font that is the closest font which is
 * no taller that the printer font. In practice it will often be fatter
 * maybe only for certain characters such as 'i'.You have to recalculate
 * the width of the characters using the screen fonts. You can do this
 * using <code>CFont::TextWidth</code>() as you have already determined
 * how many characters will fit on the line.If, in the screen font, the
 * characters are not as wide as the line then you can just use word
 * justification to expand the line. You would only do this if the text
 * is to be justified.If, however, the characters are wider than the line
 * then you would use character justification to clip each character. You
 * would need to do this even if the line is not justified.Thus, in
 * practice, character justification will only very rarely be used to
 * expand a line of characters.
 *
 * @param     "TInt aExcessWidth"
 *            The excess width (in pixels) to be distributed between
 *            the specified number of characters.
 * @param     "TInt aNumChars"
 *            The number of characters involved.
 */
	virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars)=0;

/**
 *
 * Sets the pen colour.
 *
 * The effective pen colour depends on the drawing mode. The default pen
 * colour is black.Note:The pen is used to draw lines, the outlines of
 * filled shapes, and text. The class provides member functions to set
 * the colour of the pen, the style of line and the line size drawn.
 *
 * @param     "const TRgb& aColor"
 *            An RGB colour for the pen.
 */
	virtual void SetPenColor(const TRgb& aColor)=0;

/**
 *
 * Sets the line drawing style for the pen.
 *
 * There are 6 pen styles. If no pen style is set, then the default is
 * <code>TPenStyle::ESolidPen</code>. To use a pen style, its full
 * context must be given, e.g. for a null pen:Notes:The pen is used to
 * draw lines, the outlines of filled shapes, and text.
 * <code>CGraphicsContext</code> member functions are provided to set the
 * colour of the pen, the style of line and the line size drawn.The
 * <code>TPenStyle::ENullPen</code> style should be used if a border is
 * not required around a filled shape.Dotted and dashed pen styles have a
 * device dependant implementation, always give single-pixel size lines
 * on the screen whatever the pen size set by <code>SetPenSize()</code>
 * and can only be used for straight lines, polylines, non-rounded
 * rectangles and polygons.The dotted/dashed pattern is continued,
 * without re-starting, for all consecutively drawn straight lines,
 * i.e.the outlines of rectangles the pattern starts in the top left
 * corner. It is reset at the end of the function call.the outlines of
 * polygons the pattern starts at the first point. It is reset at the end
 * of the function call.polylines and straight lines the pattern starts
 * at the first point initially. Consecutive calls to
 * <code>DrawLine()</code> and/or <code>DrawPolyLine()</code>, whether
 * the lines are concatenated or not, continue the pattern. It can be
 * reset by a further call to <code>SetPenStyle()</code> using the same
 * dotted/dashed style parameter.
 *
 * @param     "TPenStyle aPenStyle"
 *            A pen style.
 */
	virtual void SetPenStyle(TPenStyle aPenStyle)=0;

/**
 *
 * Sets the line drawing size for the pen.
 *
 * Lines of size greater than one pixel:are drawn with rounded ends that
 * extend beyond the end points, (as if the line is drawn using a
 * circular pen tip of the specified size).are always drawn in
 * <code>TDrawMode::EDrawModePEN</code> mode, overriding whatever mode
 * has been set using <code>SetDrawMode()</code>.Notes:The pen is used to
 * draw lines, the outlines of filled shapes, and text. The class
 * provides member functions to set the colour of the pen, the style of
 * line and the line size drawn.Wide straight lines and arcs have rounded
 * ends so that concatenated wide lines have smoothly rounded corners at
 * the vertexes.When lines are made wide, the extra strips of pixels are
 * added equally to both sides of the line. This works precisely for
 * lines of odd pixel size (3,5,7,etc.). Wide lines of even pixel size,
 * (2,4,6,etc.), have the extra strip of pixels added to the right and/or
 * below the line.Wide outlines of ellipses and wide line arcs are drawn
 * with the pixels distributed either side of a thin (single pixel wide)
 * true ellipse constructed in the normal manner. Wide ellipses and arcs
 * of even pixel size have the extra strip of pixels added to the right
 * and/or below the curved line. This gives a slight asymmetry to
 * ellipses.If the pen style is dotted or dashed, the size specification
 * is ignored: a single-pixel wide primitive is drawn, (this is device
 * dependant).A line size of zero is handled as if the pen style had been
 * set to <code>TPenStyle::ENullPen</code>.
 *
 * @param     "const TSize& aSize"
 *            A line size. The default is 1 pixel.
 */
	virtual void SetPenSize(const TSize& aSize)=0;

/**
 *
 * Sets the brush colour.
 *
 * The effective brush colour depends on the drawing mode.Notes:The brush
 * is used for filling shapes and the background of text boxes. The brush
 * has colour, style, pattern and pattern origin parameters.If no brush
 * colour has been set, it defaults to white. However the default brush
 * style is null, so when drawing to a window the default appears to be
 * the windows background colour.
 *
 * @param     "const TRgb& aColor"
 *            An RGB colour for the brush.
 */
	virtual void SetBrushColor(const TRgb& aColor)=0;

/**
 *
 * Sets the brush style.
 *
 * Ten brush styles are provided, including six built-in hatching
 * patterns (see <code>TBrushStyle</code>).Note:The brush is used for
 * filling shapes and the background of text boxes. The brush has colour,
 * style, pattern and pattern origin parameters.Use
 * <code>TBrushStyle::ENullBrush</code> to draw the outline of a fillable
 * shape on its own, without filling.If the
 * <code>TBrushStyle::EPatternedBrush</code> style is set, but no bitmap
 * pattern has been selected using <code>UseBrushPattern()</code>, then
 * the function panics.Hatching lines are done in the current brush
 * colour, set using <code>SetBrushColor()</code>. Hatching can be
 * overlaid on other graphics. The hatching pattern starts at the brush
 * origin, set using <code>SetBrushOrigin()</code>.
 *
 * @param     "TBrushStyle aBrushStyle"
 *            A brush style.
 */
	virtual void SetBrushStyle(TBrushStyle aBrushStyle)=0;

/**
 *
 * Sets the brush pattern origin.
 *
 * This specifies the position of the pixel in the top left corner of a
 * reference pattern tile, (in absolute device co-ordinates). Other
 * copies of the pattern file are then tiled around the reference one.
 * Thus the brush origin can be set as the top left corner of a shape.The
 * brush pattern may be a built-in style, or a bitmap. To use a bitmap,
 * the brush must have a pattern set and the brush style must be set to
 * <code>TBrushStyle::EPatternedBrush</code>.NotesThe brush is used for
 * filling shapes and the background of text boxes. The brush has colour,
 * style, pattern and pattern origin parameters.If
 * <code>SetBrushOrigin()</code> is not used, then the origin defaults to
 * (0,0).This brush origin remains in effect for all fillable shapes
 * drawn subsequently, until a new brush origin is set. Shapes can thus
 * be considered as windows onto a continuous pattern field (covering the
 * whole clipping region of a screen device, or the whole device area of
 * a printer).
 *
 * @param     "const TPoint& aOrigin"
 *            An origin point for the brush.
 */
	virtual void SetBrushOrigin(const TPoint& aOrigin)=0;

/**
 *
 * Sets the brush pattern to the specified bitmap.
 *
 * For the brush to actually use the bitmap,
 * <code>TBrushStyle::EPatternedBrush</code> must be used to set the
 * brush style.When the brush pattern is no longer required, use
 * <code>DiscardBrushPattern()</code> to free up the memory used, if the
 * bitmap is not being shared. If <code>UseBrushPattern()</code> is used
 * again without using <code>DiscardBrushPattern()</code> then the
 * previous pattern is discarded automatically.Notes:The brush is used
 * for filling shapes and the background of text boxes. The brush has
 * colour, style, pattern and pattern origin parameters.When loading a
 * bitmap, the bitmap is checked to see if it is already in memory. If
 * the bitmap is already there, then that copy is shared.The brush does
 * not need to have a pattern set at all. There are several built-in
 * hatching patterns which can be selected using
 * <code>SetBrushStyle()</code>.
 *
 * @param     "const CFbsBitmap* aBitmap"
 *            A bitmap pattern for the brush.
 */
	virtual void UseBrushPattern(const CFbsBitmap* aBitmap)=0;

/**
 *
 * Discards a non-built-in brush pattern.
 *
 * This frees up the memory used by the bitmap, if it is not being shared
 * by another process.Notes:The brush is used for filling shapes and the
 * background of text boxes. The brush has colour, style, pattern and
 * pattern origin parameters.If <code>DiscardBrushPattern()</code> is
 * used, with no brush pattern set, then there is no effect.
 *
 */
	virtual void DiscardBrushPattern()=0;

/**
 *
 * Sets the drawing point relative to the co-ordinate origin.
 *
 * A subsequent call to <code>DrawLineTo()</code> or
 * <code>DrawLineBy()</code> uses the new drawing point as the start
 * point for the line drawn.NotesThe operations <code>DrawLine()</code>,
 * <code>DrawLineTo()</code>, <code>DrawLineBy()</code> and
 * <code>DrawPolyline()</code> also change the internal drawing position
 * to the last point of the drawn line(s). The internal drawing position
 * is set to the co-ordinate origin if no drawing or moving operations
 * have yet taken place.
 *
 * @param     "const TPoint& aPoint"
 *            The new internal drawing position.
 */
	virtual void MoveTo(const TPoint& aPoint)=0;

/**
 *
 * Sets the drawing point relative to the current co-ordinates.
 *
 * A subsequent call to <code>DrawLineTo()</code> or
 * <code>DrawLineBy()</code> uses the new drawing point as the start
 * point for the line drawn.NotesThe operations <code>DrawLine()</code>,
 * <code>DrawLineTo()</code>, <code>DrawLineBy()</code> and
 * <code>DrawPolyline()</code> also change the internal drawing position
 * to the last point of the drawn line(s). The internal drawing position
 * is set to the co-ordinate origin if no drawing or moving operations
 * have yet taken place.
 *
 * @param     "const TPoint& aVector"
 *            The amount by which the internal drawing position is
 *            to move.
 */
	virtual void MoveBy(const TPoint& aVector)=0;

/**
 *
 * Draws a single point.
 *
 * The point is drawn with the current pen settings using the current
 * drawing mode.Note:If the pen size is greater than one pixel, a filled
 * circle of the current pen colour is drawn, with the pen size as the
 * diameter and the plotted point as the centre. If the pen size is an
 * even number of pixels, the extra pixels are drawn below and to the
 * right of the centre.
 *
 * @param     "const TPoint& aPoint"
 *            The point to be drawn.
 */
	virtual void Plot(const TPoint& aPoint)=0;

/**
 *
 * Draws an arc.
 *
 * The arc is considered a portion of an ellipse. The ellipse is defined
 * by the <code>TRect</code> argument.The pixels at both the start point
 * and the end point are drawn.The arc itself is the segment of the
 * ellipse drawn in an anti-clockwise direction from the start point to
 * the end point.Notes:A rectangle is used in the construction of the
 * ellipse of which the arc is a segment. This rectangle is passed as an
 * argument of type <code>TRect</code>.A wide line arc is drawn with the
 * pixels distributed either side of a true ellipse, in such a way that
 * the outer edge of the line would touch the edge of the construction
 * rectangle. In other words, the ellipse used to construct it is
 * slightly smaller than that for a single pixel line size.If the
 * specified start or end point is at the centre of the ellipse, then the
 * line that defines the start or end of the arc defaults to one
 * extending vertically above the centre point.If the start and end point
 * are the same point or are points on the same line through the ellipse
 * centre then a complete unfilled ellipse is drawn.
 *
 * @param     "const TRect& aRect"
 *            A rectangle in which to draw the ellipse, of which the
 *            arc is a segment.
 * @param     "const TPoint& aStart"
 *            The point defining the start of the arc. It defines
 *            one end of a line from the geometric centre of the
 *            ellipse. The point of intersection between this line
 *            and the ellipse defines the start point of the arc.
 * @param     "const TPoint& aEnd"
 *            The point defining the end of the arc. It defines one
 *            end of a second line from the geometric centre of the
 *            ellipse. The point of intersection between this line
 *            and the ellipse defines the end point of the arc.
 */
	virtual void DrawArc(const TRect& aRect,const TPoint& aStart,const TPoint& aEnd)=0;

/**
 *
 * Draws a straight line between two points.
 *
 * @param     "const TPoint& aPoint1"
 *            The point at the start of the line.
 * @param     "const TPoint& aPoint2"
 *            The point at the end of the line.
 */
	virtual void DrawLine(const TPoint& aPoint1,const TPoint& aPoint2)=0;

/**
 *
 * Draws a straight line from the current drawing point to a specified
 * point.
 *
 * @param     "const TPoint& aPoint"
 *            The point at the end of the line.
 */
	virtual void DrawLineTo(const TPoint& aPoint)=0;

/**
 *
 * Draws a straight line relative to the current drawing point, using a
 * vector.
 *
 * The start point of the line is the current drawing point. The
 * specified vector is added to the drawing point to give the end point
 * of the line
 *
 * @param     "const TPoint& aVector"
 *            The vector to add to the current internal drawing
 *            position, giving the end point of the line.
 */
	virtual void DrawLineBy(const TPoint& aVector)=0;

/**
 *
 * Draws a polyline from a set of points in a list.
 *
 * A polyline is a series of concatenated straight lines joining a set of
 * points.
 *
 * @param     "const CArrayFix<TPoint>* aPointList"
 *            The list of points on the polyline.
 */
	virtual void DrawPolyLine(const CArrayFix<TPoint>* aPointList)=0;

/**
 *
 * Draws a polyline from a set of points in a list.
 *
 * A polyline is a series of concatenated straight lines joining a set of
 * points.
 *
 * @param     "const TPoint* aPointList"
 *            Pointer to a set of points on the polyline.
 * @param     "TInt aNumPoints"
 *            Number of points in the list.
 */
	virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints)=0;

/**
 *
 * Draws and fills a pie slice.
 *
 * The pie slice is an area bounded by:the arc of an ellipse drawn in an
 * anticlockwise direction from the start point to the end pointthe
 * straight line drawn to the start point from the geometric centre of
 * the ellipse.the straight line to the end point from the geometric
 * centre of the ellipse.Notes:A rectangle is used in the construction of
 * the pie slice. This rectangle is passed as an argument of type
 * <code>TRect</code>. The curved edge of the pie slice is an arc of an
 * ellipse constructed within the rectangle.The line drawn by the pen
 * goes inside the specified rectangle.The pixels at the end point of the
 * arc are not drawn.A wide line edged pie slice has the arc drawn with
 * the pixels distributed either side of a true ellipse. This is done in
 * such a way that the outer edge of the line touches the edge of the
 * construction rectangle. In other words, the ellipse used to construct
 * it is slightly smaller than that for a single pixel line size.If the
 * specified start or end point is at the centre of the ellipse, then the
 * line that defines the start or end of the arc defaults to one
 * extending vertically above the centre point.If the start and end point
 * are the same point or are points on the same line through the ellipse
 * centre then a complete filled ellipse is drawn. A line is also drawn
 * from the edge to the ellipse centre.
 *
 * @param     "const TRect& aRect"
 *            A rectangle in which to draw the ellipse bounding the
 *            pie slice.
 * @param     "const TPoint& aStart"
 *            A point defining the start of the arc bounding the pie
 *            slice. It defines one end of a line from the
 *            geometrical centre of the ellipse. The point of
 *            intersection between this line and the ellipse defines
 *            the start point of the arc.
 * @param     "const TPoint& aEnd"
 *            A point to define the end of the arc bounding the pie
 *            slice. It defines one end of a second line from the
 *            geometrical centre of the ellipse. The point of
 *            intersection between this line and the ellipse defines
 *            the end point of the arc.
 */
	virtual void DrawPie(const TRect& aRect,const TPoint& aStart,const TPoint& aEnd)=0;

/**
 *
 * Draws and fills an ellipse.
 *
 * The ellipse is drawn inside the rectangle defined by the
 * <code>TRect</code> argument. Any rectangle that has odd pixel
 * dimensions, has the bottom right corner trimmed to give even pixel
 * dimensions before the ellipse is constructed.Note:A wide outline
 * ellipse is drawn with the pixels distributed either side of a true
 * ellipse, in such a way that the outer edge of the line touches the
 * edge of the construction rectangle. In other words, the ellipse used
 * to construct it is smaller than that for a single pixel line size.
 *
 * @param     "const TRect& aRect"
 *            The rectangle in which the ellipse is drawn.
 */
	virtual void DrawEllipse(const TRect& aRect)=0;

/**
 *
 * Draws and fills a rectangle.
 *
 * @param     "const TRect& aRect"
 *            The rectangle to be drawn.
 */
	virtual void DrawRect(const TRect& aRect)=0;

/**
 *
 * Draws and fills a rectangle with rounded corners.
 *
 * The rounded corners are each constructed as an arc of an ellipse.The
 * line drawn by the pen, if any, goes inside the specified
 * rectangle.Notes:Dotted and dashed pen styles cannot be used for the
 * outline of a rounded rectangle.If either corner size dimension is
 * greater than half the corresponding rectangle length, the corner size
 * dimension is reduced to half the rectangle size.
 *
 * @param     "const TRect& aRect"
 *            The rectangle to be drawn.
 * @param     "const TSize& aCornerSize"
 *            The dimensions of each corner.
 */
	virtual void DrawRoundRect(const TRect& aRect,const TSize& aCornerSize)=0;

/**
 *
 * Draws and fills a polygon defined using a list of points.
 *
 * The first point in the list defines the start of the first side of the
 * polygon. The second point defines the second vertex (the end point of
 * the first side and the start point of the second side).The final side
 * of the polygon is drawn using the last point from the list, and the
 * line is drawn to the start point of the first side.Self-crossing
 * polygons are filled according to the specified fill rule.
 *
 * @param     "const CArrayFix<TPoint>* aPointList"
 *            Array containing list of points, specifying the vertices of
 *            the polygon.
 * @param     "TFillRule aFillRule=EAlternate"
 *            The fill rule. By default this is
 *            <code>TFillRule::EAlternate</code>.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
	virtual TInt DrawPolygon(const CArrayFix<TPoint>* aPointList,TFillRule aFillRule=EAlternate)=0;

/**
 *
 * Draws and fills a polygon defined using a list of points.
 *
 * The first point in the list defines the start of the first side of the
 * polygon. The second point defines the second vertex (the end point of
 * the first side and the start point of the second side).The final side
 * of the polygon is drawn using the last point from the list, and the
 * line is drawn to the start point of the first side.Self-crossing
 * polygons are filled according to the specified fill rule.
 *
 * @param     "const TPoint* aPointList"
 *            Pointer to list of points, specifying the vertices of
 *            the polygon.
 * @param     "TInt aNumPoints"
 *            The number of points in the list.
 * @param     "TFillRule aFillRule=EAlternate"
 *            The fill rule. By default this is
 *            <code>TFillRule::EAlternate</code>.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
	virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate)=0;

/**
 *
 * Draws a bitmap from a given point using the bitmaps size in twips.
 *
 * Notes:This member function converts the bitmap size in twips to pixels and does a
 * stretch/compress blit using a linearDDA. As this function scales the
 * bitmap, it is unavoidably slow. Therefore, where possible, use
 * <code>CBitmapContext::BitBlt()</code> instead. If the bitmap has to be
 * scaled, consider creating another bitmap along with an
 * <code>CFbsBitmapDevice</code> etc., doing <code>DrawBitmap()</code>
 * once and using <code>BitBlt()</code> subsequently.Note that all
 * bitmaps are clipped to the device boundaries.
 *
 * @param     "const TPoint& aTopLeft"
 *            Position within destination at which the top left
 *            hand corner of the source bitmap will be drawn.
 * @param     "const CFbsBitmap* aSource"
 *            A source bitmap.
 */
	virtual void DrawBitmap(const TPoint& aTopLeft,const CFbsBitmap* aSource)=0;

/**
 *
 * Draws a source bitmap to fit into a given destination rectangle.
 *
 * Notes:This member function uses rectangle sizes in pixels and does a
 * stretch/compress blit using a linearDDA.As this function scales the
 * bitmap, it is unavoidably slow. Therefore, where possible, use
 * <code>CBitmapContext::BitBlt()</code> instead. If the bitmap has to be
 * scaled, consider creating another bitmap along with an
 * <code>CFbsBitmapDevice</code> etc., doing <code>DrawBitmap()</code>
 * once and using <code>BitBlt()</code> subsequently.Note that all
 * bitmaps are clipped to the device boundaries.
 *
 * @param     "const TRect& aDestRect"
 *            The rectangle within which the bitmap is to be drawn.
 * @param     "const CFbsBitmap* aSource"
 *            A source bitmap.
 */
	virtual void DrawBitmap(const TRect& aDestRect,const CFbsBitmap* aSource)=0;

/**
 *
 * Draws a specified rectangle of a source bitmap to fit into a given
 * destination rectangle.
 *
 * Notes:This member function uses rectangle sizes in pixels and does a
 * stretch/compress blit using a linearDDA.As this function scales the
 * bitmap, it is unavoidably slow. Therefore, where possible, use
 * <code>CBitmapContext::BitBlt()</code> instead. If the bitmap has to be
 * scaled, consider creating another bitmap along with an
 * <code>CFbsBitmapDevice</code> etc., doing <code>DrawBitmap()</code>
 * once and using <code>BitBlt()</code> subsequently.Note that all
 * bitmaps are clipped to the device boundaries.
 *
 * @param     "const TRect& aDestRect"
 *            The rectangle within which the bitmap is to be drawn.
 * @param     "const CFbsBitmap* aSource"
 *            A source bitmap.
 * @param     "const TRect& aSourceRect"
 *            The rectangle in the source bitmap that is copied to
 *            the destination rectangle.
 */
	virtual void DrawBitmap(const TRect& aDestRect,const CFbsBitmap* aSource,const TRect& aSourceRect)=0;

/**
 *
 * Draws the specified text at the given position.
 *
 * @param     "const TDesC& aText"
 *            The text to be drawn.
 * @param     "const TPoint& aPosition"
 *            The position to draw the text at.
 */
	virtual void DrawText(const TDesC& aText,const TPoint& aPosition) = 0;

/**
 *
 * Draws the specified text within the given box using the baseline offset,
 * alignment and a margin.
 *
 * @param     "const TDesC& aText"
 *            The text to be drawn.
 * @param     "const TRect& aBox"
 *            The box to draw the text in.
 * @param     "TInt aBaselineOffset"
 *            The distance of the baseline of the text from the bottom of the box.
 * @param     TTextAlign aAlignment = ELeft"
 *            The horizontal alignment of the text within the box. Defaults to left.
 * @param     "TInt aLeftMargin = 0"
 *            The distance to offset the text after taking into account the alignment.
 *            Positive offsets to the right, negative to the left.
 */
	virtual void DrawText(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TTextAlign aAlignment = ELeft,
		TInt aLeftMargin = 0) = 0;
	IMPORT_C virtual void DrawText(const TDesC& aText,const TPoint& aPosition,const TDrawTextParam& aParam);
	IMPORT_C virtual void Reserved();
	IMPORT_C TInt DrawTextExtended(const TDesC& aText,const TPoint& aPosition,const TDrawTextExtendedParam& aParam);
	};

/**
 *
 * An abstract, device-independent, interface to bitmapped graphics
 * contexts.
 *
 * The default settings of a <code>CBitmapContext</code> object
 * immediately after construction are:drawing mode is
 * <code>EDrawModePen</code> (pen and brush colours used as they are)no
 * clipping rectanglepen settings are: black, solid, single pixel
 * widthbrush style is nullno text font selectedThe classes
 * <code>CFbsBitGc</code> and <code>CWindowGc</code> are derived from
 * this class.
 *
 * @since 5.0
 */
class CBitmapContext : public CGraphicsContext
	{
public:

/**
 *
 * Clears the whole bitmap.
 *
 * The cleared area is filled with the current brush colour.This pure
 * virtual function is implemented in derived classes.
 *
 */
	virtual void Clear()=0;

/**
 *
 * Clears a rectangular area of a bitmap.
 *
 * The cleared area is filled with the current brush colour.This pure
 * virtual function is implemented in derived classes.
 *
 */
	virtual void Clear(const TRect& aRect)=0;

/**
 *
 * Copies a rectangle.
 *
 * This pure virtual function is implemented in derived classes.
 *
 * @param     "const TPoint& aOffset"
 *            The offset from the top left corner of the rectangle
 *            to be copied to the top left corner of the copy.
 * @param     "const TRect& aRect"
 *            The rectangular area to be copied.
 */
	virtual void CopyRect(const TPoint& aOffset,const TRect& aRect)=0;

/**
 *
 * Performs a bitmap block transfer of a bitmap.
 *
 * @param     "const TPoint& aPoint"
 *            The position to draw the top left corner of the piece
 *            of bitmap
 * @param     "const CFbsBitmap* aBitmap"
 *            A memory-resident bitmap
 */
	virtual void BitBlt(const TPoint& aPoint,const CFbsBitmap* aBitmap)=0;

/**
 *
 * Performs a bitmap block transfer of a rectangular piece of a bitmap.
 *
 * If the specified rectangle is larger than the bitmap then the bitmap
 * is padded with white.This pure virtual function is implemented in
 * derived classes.
 *
 * @param     "const TPoint& aPoint"
 *            The position to draw the top left corner of the piece
 *            of bitmap
 * @param     "const CFbsBitmap* aBitmap"
 *            A memory-resident bitmap
 * @param     "const TRect& aRect"
 *            A rectangle defining the piece of the bitmap to be
 *            drawn, with co-ordinates relative to the top left
 *            corner of the bitmap
 */
	virtual void BitBlt(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aRect)=0;

/**
 *
 * Performs a masked bitmap block transfer.
 *
 * The mask bitmap can be used as either a positive or negative mask.
 * Masked pixels are not mapped to the destination rectangle.A black and
 * white (binary) mask bitmap is used. With
 * <code>aInvertMask=ETrue</code>, black pixels in the mask bitmap stop
 * corresponding pixels in the source bitmap from being transferred to
 * the destination rectangle. With <code>aInvertMask=EFalse</code>, white
 * pixels in the mask bitmap stop corresponding pixels in the source
 * bitmap from being transferred to the destination rectangle.Note that if
 * the mask bitmap is smaller than the source bitmap, then it is tiled
 * across the bitmap. Note that the mask is applied before the piece of
 * the bitmap is defined the mask is tiled relative to the top left of
 * the original source bitmap rather than the top left of the bitmap
 * piece.This pure virtual function is implemented in derived classes.
 *
 * @param     "const TPoint& aPoint"
 *            A position for the top left corner of the bitmap.
 * @param     "const CFbsBitmap* aBitmap"
 *            A memory-resident source bitmap.
 * @param     "const TRect& aSourceRect"
 *            A rectangle defining the piece of the bitmap to be
 *            drawn, with co-ordinates relative to the top left
 *            corner of the bitmap.
 * @param     "const CFbsBitmap* aMaskBitmap"
 *            A mask bitmap
 * @param     "TBool aInvertMask"
 *            If true, a source pixel that is masked by a black
 *            pixel is not transferred to the destination rectangle.
 *            If false, then a source pixel that is masked by a
 *            white pixel is not transferred to the destination
 *            rectangle.
 */
	virtual void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask)=0;

/**
 *
 * Sets whether the graphics context is faded.
 *
 * @since     6.0
 * @param     "TBool aFaded"
 *            <code>ETrue</code> to fade the GC;
 *            <code>EFalse</code> to unfade it.
 */
	virtual void SetFaded(TBool aFaded)=0;

/**
 *
 * Sets fading parameters.
 *
 * This function allows you to override the map used when drawing with a
 * faded graphics context (GC). However if you draw to a faded window
 * with a faded GC, then fading on the GC is ignored and it will use the
 * fading of the window.Fading is used to change the colour of a window
 * to make other windows stand out. Fading can either make a faded window
 * closer to white or closer to black.Fading re-maps colours in the faded
 * GC to fall between the specified black and white map values. If
 * <code>aBlackMap</code>=0 and <code>aWhiteMap</code>=255 then the
 * colours are mapped unchanged. As the values converge the colours are
 * mapped to a smaller range so the differences between colours in
 * the faded GC decrease. If the values are reversed then the colours are
 * inverted (i.e. where the GC would be black, it is now white).
 *
 * @since     6.0
 * @param     "TUint8 aBlackMap"
 *            Black map fading parameter. Unfaded this is 0.
 * @param     "TUint8 aWhiteMap"
 *            White map fading parameter. Unfaded this is 255.
 */
	virtual void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap)=0;
	};

/**
 *
 * Defines an interface for the capabilities and attributes of a
 * bitmapped graphics device.
 * @since 5.0
 */
class CBitmapDevice : public CGraphicsDevice
	{
public:

/**
 *
 * Gets the RGB colour of an individual pixel on a bitmapped graphics
 * device.
 *
 * This pure virtual function is implemented in derived classes.
 *
 * @param     "TRgb& aColor"
 *            On return, should contain the RGB colour of the pixel.
 * @param     "const TPoint& aPixel"
 *            The (x,y) co-ordinates of the pixel. The top left
 *            pixel is (0,0).
 */
	virtual void GetPixel(TRgb& aColor,const TPoint& aPixel) const=0;

/**
 *
 * Copies a scanline into a buffer.
 *
 * The pixels are converted from the display mode format on the bitmapped
 * graphics device to the format of the specified device display mode.By
 * specifying the start pixel and the number of pixels, either the whole
 * or a portion of a bitmapped graphics device pixel row may be
 * copied.This pure virtual function is implemented in derived classes.
 *
 * @param     "TDes8& aBuf"
 *            An 8 bit modifiable descriptor buffer into which
 *            pixels are copied; it must be sufficiently large to
 *            store all the scanline pixels.
 * @param     "const TPoint& aStartPixel"
 *            The (x,y) co-ordinates of the first pixel of the
 *            bitmap scanline to be put into the buffer.
 * @param     "TInt aLength"
 *            The number of pixels to put into the buffer.
 * @param     "TDisplayMode aDispMode"
 *            The display mode into which to convert the pixels.
 */
	virtual void GetScanLine(TDes8& aBuf,const TPoint& aStartPixel,TInt aLength,TDisplayMode aDispMode) const=0;

/**
 *
 * Adds a font file to the devices font store.
 *
 * This pure virtual function is implemented in derived classes.
 *
 * @param     "const TDesC& aName"
 *            The name of the font file.
 * @param     "TInt& aId"
 *            On return, contains an ID for the font file.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
	virtual TInt AddFile(const TDesC& aName,TInt& aId)=0;

/**
 *
 * Removes a font file from the font store.
 *
 * This pure virtual function is implemented in derived classes.
 *
 * @param     "TInt aId=0"
 *            The ID of the font file to be removed. The default is
 *            0.
 */
	virtual void RemoveFile(TInt aId=0)=0;

/**
 *
 * Gets the nearest font to that specified for use by a bitmapped
 * graphics device.
 *
 * The font and bitmap server returns a pointer to the nearest matching
 * font from those available.This pure virtual function is implemented in
 * derived classes.
 *
 * @param     "CFont*& aFont"
 *            On return, the pointer is set to point to the device
 *            font which most closely approximates to the required
 *            font specification.
 * @param     "const TFontSpec& aFontSpec"
 *            An absolute font specification.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
	virtual TInt GetNearestFontInPixels(CFont*& aFont,const TFontSpec& aFontSpec)=0;

/**
 *
 * Gets the height, in pixels, of the specified typeface at one of its
 * defined heights.
 *
 * The typeface is identified by by an index. For a given typeface, there
 * are a discrete number of heights; the specific height is also
 * identified by an index. The value returned is rounded up or down to
 * the nearest font height in pixels.This pure virtual function is
 * implemented in derived classes.
 *
 * @param     "TInt aTypefaceIndex"
 *            A typeface index number, in the range: 0 to
 *            (<code>NumTypefaces()</code> - 1).
 * @param     "TInt aHeightIndex"
 *            A font height index number, in the range: 0 to
 *            (<code>iNumHeights</code> -<code> 1</code>) where
 *            <code>iNumHeights</code> is a public data member of
 *            the <code>TTypefaceSupport</code> object returned by
 *            <code>TypefaceSupport().</code>
 * @returns   "TInt"
 *            The height of the font, in pixels.
 */
	virtual TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const=0;
    inline TInt CreateBitmapContext(CBitmapContext*& aGC);
	};

class TMargins
    {
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool operator==(const TMargins& aMargins) const;
	IMPORT_C TBool operator!=(const TMargins& aMargins) const;
public:
	TInt iLeft;
	TInt iRight;
    TInt iTop;
	TInt iBottom;
	};

class TPictureCapability
	{
public:
	enum TScalingType
		{
		ENotScaleable,
		EFullyScaleable,
		EScaleableMaintainingAspectRatio
		};
public:
	inline TPictureCapability(TScalingType aScalingType,TBool aCroppable);
public:
	TScalingType iScalingType;
	TBool iIsCroppable;
	};

class CPicture : public CBase
    {
public:
	enum TDetach
		{
		EDetachFull,
		EDetachDraw
		};
public:
	IMPORT_C virtual ~CPicture();
	virtual void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,MGraphicsDeviceMap* aMap) const=0;
	IMPORT_C virtual TStreamId StoreL(CStreamStore& aStore) const; // assumes no sub streams
	virtual void DetachFromStoreL(TDetach /*aDegree*/=EDetachFull) {}
	virtual void ExternalizeL(RWriteStream& aStream) const =0;
	virtual void GetOriginalSizeInTwips(TSize& aSize) const =0;
	IMPORT_C virtual void SetScaleFactor(TInt aScaleFactorWidth,TInt aScaleFactorHeight); // does nothing
	IMPORT_C virtual void SetCropInTwips(const TMargins& aMargins); // does nothing
	IMPORT_C virtual TPictureCapability Capability() const; // no scale, no crop
	IMPORT_C virtual void GetCropInTwips(TMargins& aMargins) const; // returns no crop
	IMPORT_C virtual TInt ScaleFactorWidth() const; // returns no scaling
	IMPORT_C virtual TInt ScaleFactorHeight() const; // returns no scaling
	IMPORT_C virtual TBool LineBreakPossible(TUint aClass,TBool aBeforePicture,TBool aHaveSpaces) const;
	IMPORT_C virtual TBool NativePixelSize(TSize& aPixelSize);

	IMPORT_C void GetSizeInPixels(MGraphicsDeviceMap* aMap, TSize& aSize) const;
	IMPORT_C void SetSizeInPixels(MGraphicsDeviceMap* aMap, const TSize& aSize);
	IMPORT_C void AddCropInPixels(MGraphicsDeviceMap* aMap, const TMargins& aMargins);
	IMPORT_C void GetSizeInTwips(TSize& aSize) const;
	IMPORT_C void SetSizeInTwips(const TSize& aSize);
	IMPORT_C void ResetToOriginal();
protected:
	IMPORT_C CPicture();
	};

// Encodes a picture type and the stream ID of the picture body.
// The stream ID can be replaced by a pointer.

class TPictureHeader
	{
public:
	IMPORT_C TPictureHeader();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void DeletePicture();
public:
	TSwizzle<CPicture> iPicture;
	TUid iPictureType;
	TSize iSize;
	};

// An abstract interface for instantiating & restoring new CPicture objects.
// A concrete derived class will create picture of the specific type.

class MPictureFactory
	{
public:
	virtual void NewPictureL(TPictureHeader& aHeader,const CStreamStore& aDeferredPictureStore)const=0;
	};

// printing classes

const TInt KMaxPrinterModelNameLength=0x20;

/**
 *
 * Defines a modifiable buffer descriptor that can contain the name of a
 * printer model.
 *
 * The maximum length of the buffer is 32.
 *
 * @since 5.0
 */
typedef TBuf<KMaxPrinterModelNameLength> TPrinterModelName;

/**
 *
 * Page specification for a print operation.
 *
 * The page specification consists of the page orientation and the page
 * size in twips or pixels. By default, the page orientation is portrait.
 * When using landscape orientation, the left hand side of the page
 * becomes the top.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TPageSpec
	{
public:

/**
 *
 * The available page orientations.
 *
 */
	enum TPageOrientation
		{
		EPortrait,
		ELandscape
		};
public:
	IMPORT_C TPageSpec();
	IMPORT_C TPageSpec(TPageOrientation aOrientation,const TSize& aSize);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TSize OrientedPageSize() const;
	IMPORT_C TBool operator==(const TPageSpec& aPageSpec) const;
	IMPORT_C TBool operator!=(const TPageSpec& aPageSpec) const;
public:
	TSize iPortraitPageSize;
	TPageOrientation iOrientation;
	};

/**
 *
 * Controls the attributes of the band to be printed.
 *
 * An object of this type is passed as a parameter to functions
 * <code>MPageRegionPrinter::PrintBandL()</code> and
 * <code>CPrinterControl::QueueGetBand()</code>.
 *
 * @since 5.0
 */
class TBandAttributes
	{
public:
	TRect iRect;
	TBool iTextIsIgnored; // any text drawing to this band is ignored
	TBool iGraphicsIsIgnored; // any graphics drawing to this band is ignored
	TBool iFirstBandOnPage;
	};

/**
 *
 * Printer port interface.
 *
 * This interface is used as the base class for the various types of
 * printer port. New printer port classes should be derived from this
 * class.After allocation and construction, a pointer to a concrete
 * printer port should be passed to
 * <code>CPrintSetup::StartPrintL()</code>.
 *
 * @since 5.0
 */
class CPrinterPort : public CBase
	{
public:

/**
 *
 * Writes data asynchronously to the printer port.
 *
 * @param     "const TDesC8& aBuf"
 *            Data to be written to the port
 * @param     "TRequestStatus& aRequestStatus"
 *            A reference to the request status object. If the
 *            request is cancelled, this should be set to
 *            <code>KErrCancel</code>; if the request completes
 *            normally, this should be set to <code>KErrNone</code>.
 */
	virtual void WriteRequest(const TDesC8& aBuf,TRequestStatus& aRequestStatus)=0;

/**
 *
 * Cancels an outstanding <code>WriteRequest()</code> operation.
 *
 */
	virtual void Cancel()=0;
	};

/**
 *
 * Detailed information about a printer model.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TPrinterModelEntry
	{
public:
	TPrinterModelName iModelName;
	TBool iRequiresPrinterPort;
	TUid iUid;
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	};

/**
 *
 * Information about a printer model.
 *
 * An instance of this class consists of a
 * <code>TPrinterModelEntry</code> and a stream ID, and is passed to
 * <code>CPrinterDevice::SetModel()</code>, and is returned from
 * <code>CPrinterDevice::Model()</code>.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TPrinterModelHeader
	{
public:
	TPrinterModelEntry iEntry;
	TStreamId iModelDataStreamId;
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	};

/**
 *
 * Printer control interface.
 *
 * This abstract base class acts as the interface between a
 * <code>CPrinterDevice</code> object and the printer. It creates the
 * context for, and controls the progress and termination of the print
 * job.Only those who need to add new printer drivers should write
 * derived classes. After instantiation of such a class, using
 * <code>CPrinterDevice::CreateControlL()</code>, the object can be
 * accessed via the <code>iControl</code> member of
 * <code>CPrinterDevice</code>.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CPrinterControl : public CBase
	{
public:

/**
 *
 * More on page to print flags.
 * @since 
 */
	enum TMoreOnPage
		{
/** Indicates there is more to print on the current page.
 */
		EMoreOnPage,
/** Indicates there is no more to print on the current page.
 */
		ENoMoreOnPage
		};
public:
	IMPORT_C ~CPrinterControl();

/**
 *
 * Gets the number of bands per page.
 *
 * @returns   "TInt"
 *            The number of bands on each page.
 */
	virtual TInt BandsPerPage()=0;

/**
 *
 * Prints the next band on the page.
 *
 * This is an asynchronous function.
 *
 * @param     "TRequestStatus& aStatus"
 *            Request status object. On successful completion
 *            contains <code>KErrNone</code>, otherwise another of
 *            the system-wide error codes.
 * @param     "TBandAttributes& aBand"
 *            On return, indicates the attributes of the band,
 *            including its height and width and whether or not the
 *            device will ignore one or other of graphics or text
 *            output. This information may be used by applications
 *            to draw more efficiently, or may be ignored
 * @returns   "TMoreOnPage"
 *            <code>EMoreOnPage</code>, if any unprinted bands
 *            remain on the current page.
 *            <code>ENoMoreOnPage</code>, if the current band is
 *            last on page.
 */
	virtual TMoreOnPage QueueGetBand(TRequestStatus& aStatus, TBandAttributes& aBand)=0; // returns affirmative if more to print on current page

/**
 *
 * Terminates the print process.
 *
 * This is an asynchronous function and is called when no more bands in
 * the document remain to be printed.Note that all bands have been
 * printed when no more pages or copies remain to be printed, and
 * <code>QueueGetBand()</code> returns <code>ENoMoreToPrint</code>.
 *
 * @param     "TRequestStatus& aStatus"
 *            Request status object. On successful completion
 *            contains <code>KErrNone</code>, otherwise another of
 *            the system-wide error codes.
 */
	virtual void QueueEndPrint(TRequestStatus& aStatus)=0; // Called at finish to flush buffer, tidy up printer etc.

/**
 *
 * Aborts the print process before it has completed.
 *
 * This function should be called if <code>QueueGetBand()</code> reports
 * an error.
 *
 */
	virtual void AbortPrint()=0; // tidy up synchronously in a short time, return success code
protected:
	IMPORT_C CPrinterControl(CPrinterPort* aPrinterPort);
protected:
	enum TState {ENotPrinting, EPrinting};
	TState iState;
	CPrinterPort* iPrinterPort;
	};

class CDictionaryStore;
class RFs;

/**
 *
 * Printer graphics device interface.
 *
 * This abstract class represents a physical graphics device that is used
 * for printing.This class is used to:set and get the page
 * specificationmap between the co-ordinates of the printed page (in
 * twips) and the co-ordinates of the image device (in pixels)get and set
 * the printer model entrycreate and delete a printer control.A printer
 * driver is defined in terms of a printer device and a printer control.
 * A printer device can own either a single or no printer control. The
 * control determines the progress and termination of the print job and
 * is responsible for producing output.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CPrinterDevice : public CGraphicsDevice
	{
public:
	IMPORT_C ~CPrinterDevice();
/**
 *
 * Gets the current page specification in twips.
 *
 * @returns   "TPageSpec"
 *            The current page specification, in twips.
 */
	inline TPageSpec CurrentPageSpecInTwips() const {return(iCurrentPageSpecInTwips);}
	IMPORT_C virtual void SelectPageSpecInTwips(const TPageSpec& aPageSpec);
	IMPORT_C virtual TRect PrintablePageInPixels() const;

/**
 *
 * Gets the printer model entry.
 *
 * @returns   "TPrinterModelEntry"
 *            The printer model entry.
 */
	virtual TPrinterModelEntry Model()const =0;

/**
 *
 * Sets the printer model header and the store.
 *
 * @param     "const TPrinterModelHeader& aModel"
 *            The printer model header.
 * @param     "CStreamStore& aStore"
 *            The store.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful; otherwise,
 *            another of the system-wide error codes.
 */
	virtual TInt SetModel(const TPrinterModelHeader& aModel,CStreamStore& aStore)=0;

/**
 *
 * Creates a printer control.
 *
 * The printer control is an instance of a <code>CPrinterControl</code>
 * derived class; it is assigned to this printer devices
 * <code>iControl</code> member.Note that this function is called by
 * <code>CPrintSetup::StartPrintL()</code>.
 *
 * @param     "CPrinterPort* aPrinterPort"
 *            Pointer to an instance of a printer port.
 */
	virtual void CreateControlL(CPrinterPort* aPrinterPort)=0;
	IMPORT_C virtual void DeleteControl();

/**
 *
 * Internalizes printer properties from the storeThe default
 * implementation is empty.
 *
 * @param     "RReadStream& aStream"
 *            The read stream.
 */
	virtual void InternalizePropertiesL(RReadStream& /*aStream*/) {}

/**
 *
 * Externalizes printer properties to the store.
 *
 * The default implementation is empty.
 *
 * @param     "RWriteStream& aStream"
 *            The write stream.
 */
	virtual void ExternalizePropertiesL(RWriteStream& /*aStream*/) const {}
	IMPORT_C void RestorePropertiesL();
	IMPORT_C void StorePropertiesL() const;
protected:
	IMPORT_C CPrinterDevice();
public:
	CPrinterControl* iControl;
protected:
	TPageSpec iCurrentPageSpecInTwips;
	};

/**
 *
 * Printer model list interface.
 *
 * Functions provided by this abstract base class can be used to extract
 * printer model information from the list of printer models. This class
 * would typically be used to implement printer selection in a dialog
 * box.
 *
 * @since 5.0
 */
class CPrinterModelList : public CBase
	{
public:

/**
 *
 * Gets the number of printer models in the printer model list.
 *
 * @returns   "TInt"
 *            The number of printer models.
 */
    virtual TInt ModelCount() const=0;

/**
 *
 * Gets printer model name.
 *
 * This is the name of the printer model at the specified index within
 * the list of printer models.
 *
 * @param     "TInt anIndex"
 *            The index of the printer model within the array of
 *            printer models. Note that this number must be between
 *            zero and <code>ModelCount()</code>.
 * @returns   "TPrinterModelEntry"
 *            Name of printer model, up to 32 characters long
 */
    virtual const TPrinterModelEntry operator[](TInt anIndex)=0;

/**
 *
 * Gets a printer models index within the model list from its UID.
 *
 * @param     "TUid aModelUid"
 *            The UID of the printer model.
 * @returns   "TInt"
 *            The index of the printer model within the array of
 *            printer models.
 */
	virtual TInt UidToNum(TUid aModelUid) const=0;
    };


/**
 *
 * Interface for printing in bands.
 *
 * This class provides a single <code>PrintBandL()</code> function that
 * prints the body of each page band by band. Classes derived from this
 * interface must provide an implementation of the
 * <code>PrintBandL()</code> function.
 *
 * @since 5.0
 */
class MPageRegionPrinter
	{
public:

/**
 *
 * Prints a band.
 *
 * Implementations should set up a graphics context to which all drawing
 * should take place using <code>CGraphicsDevice::CreateContext()</code>.
 * All co-ordinate calculations should be done in twips, and converted
 * into pixels before starting the print job.
 *
 * @param     "CGraphicsDevice* aDevice"
 *            Pointer to the graphics device representing the
 *            printer.
 * @param     "TInt aPageNo"
 *            The number of the page containing the band to be
 *            printed.
 * @param     "const TBandAttributes& aBandInPixels"
 *            Attributes of the band to be printed.
 */
	virtual void PrintBandL(CGraphicsDevice* aDevice,TInt aPageNo,const TBandAttributes& aBandInPixels)=0;
	};

const TInt KPdrStoreFileUidVal=268435514;

const TInt KPdlUidVal=268450588;
const TInt KUdlUidVal=268450589;

/**
 *
 * Printer specific user interface.
 *
 * The class is used to implement a printer specific setup dialog. A
 * concrete implementation of the class is supplied in a UDL (i.e. a UI
 * DLL).<code>CPrinterDriver::CreatePrinterDriverUIL()</code> is used to
 * construct a <code>CPrinterDriverUI</code> object for a specific
 * printer. (This function calls the ordinal 1 exported function of the
 * UDL that performs the construction of the
 * <code>CPrinterDriverUI</code> object).
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CPrinterDriverUI : public CBase
	{
protected:
	IMPORT_C CPrinterDriverUI();
public:
	IMPORT_C virtual TBool BeforePrintL();
	IMPORT_C virtual void AfterPrintL();
	IMPORT_C virtual void SetPropertiesL();
	IMPORT_C virtual TBool CanSetProperties();

/**
 *
 * Sets the printer device.
 *
 * @param     "CPrinterDevice* aPrinterDevice"
 *            The printer device.
 */
	virtual TInt SetPrinterDevice(CPrinterDevice* aPrinterDevice)=0;
	};
								   
class CFileStore;

/**
 *
 * Provides access to a store containing printer specification data.
 *
 * Printer specification data is held as a direct file store, and usually
 * has a .pdr file type.A printer driver is implemented as two files: a
 * PDR file containing the printer specification data and a PDL file
 * containing the code to link the printer with the graphics printing
 * system.The printer specification data is generated by compiling a text
 * file (a .pd file type) using the pdrtran tool. Printer specification
 * data defines:the name of the associated PDLa list of one or more
 * models supported by this driver, identified by name and UIDdevice
 * information such as the size of the device, typeface information for
 * each model, including which typefaces are supported, the heights
 * available in each typeface and the width of each character in a font.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class CPrinterDriver : public CBase
    {
public:
	IMPORT_C static CPrinterDriver* NewL();
	IMPORT_C ~CPrinterDriver();
	IMPORT_C void OpenPdrL(const TDesC &aName);
	IMPORT_C void Close();
	IMPORT_C TInt NumModels() const;
	IMPORT_C TPrinterModelEntry Model(TInt aNum) const;

/**
 *
 * Gets the associated graphics printer device.
 *
 * @returns   "CPrinterDevice*"
 *            The physical graphics device used for printing.
 */
	inline CPrinterDevice* PrinterDevice() {return iPrinterDevice;}
	IMPORT_C CPrinterDevice* CreatePrinterDeviceL(TUid aModelUid);
	IMPORT_C CPrinterDriverUI* CreatePrinterDriverUIL();
private:
	CPrinterDriver();
	void DeletePrinterDevice();
	void DoOpenPdrL(const TDesC &aName);
	void DoCreatePrinterDeviceL(TUid aModelUid);
	void LoadLibraryL(RLibrary& aLibrary,const TDesC& aExt,TUid aUid2);
private:
	RFs iFs;
	CFileStore *iPdrStore;
	TInt iNumModels;
	TPrinterModelHeader* iModelList;
	TFileName iPdlName;
	TUid iPdlUid;
	RLibrary iPdlLibrary;
	CPrinterDevice* iPrinterDevice;
	RLibrary iUdlLibrary;
	};

class RResourceFile;

/**
 *
 * Implements a printer model list interface for a collection of PDR
 * files.
 * @since 5.0
 * @lib "gdi.lib"
 */
class CPdrModelList : public CPrinterModelList
	{
public:
	IMPORT_C static CPdrModelList* NewL();
	IMPORT_C virtual ~CPdrModelList();
    IMPORT_C TInt ModelCount() const;
    IMPORT_C const TPrinterModelEntry operator [] (TInt anIndex);
	IMPORT_C TInt UidToNum(TUid aModelUid) const;  // returns KErrNotFound the model uid is not matched
	IMPORT_C void AddDirectoryL(const TDesC& aDir);
	IMPORT_C CPrinterModelList* ScanForModelsL();
	IMPORT_C CPrinterDriver* CreatePrinterDriverL(TInt anIndex);
private:
	CPdrModelList();
	void ConstructL();
private:
	class TFileEntry
		{
	public:
		TFileName iFileName;
		TDesC* iDirectory;
		};
	class TModelEntry
		{
	public:
		TPrinterModelEntry iEntry;
		TFileEntry* iFile; 
		};
private:
	void ScanDirectoryL(TInt aDirIndex);
	void ListModelsL(TInt aFileIndex, TParse& aParser, TFileName& aNameOfLoadedResourceFile, TFileName& aTempFileName, RResourceFile& aResourceFile, HBufC8*& aResource);
	HBufC* NewPathBufL(const TFileEntry& aFileEntry);
private:
	CArrayFixSeg<TModelEntry>* iModelArray;
	CArrayFixFlat<TFileEntry>* iFileArray;
	CArrayFixFlat<HBufC*>* iDirectoryArray;
	RFs iFileServer;
	};

/**
 *
 * The interface for mapping between twips and device-specific units
 * enriched with facilities to allow zooming.
 *
 * The class is recursive, because a <code>TZoomFactor</code> object can
 * have a <code>MGraphicsDeviceMap</code> (which could itself be a
 * <code>TZoomFactor</code>) in its member data. This allows a zoom
 * factor object to contain another zoom factor object, and is used to
 * allow objects with different zoom factors to be embedded in each other
 * to an arbitrary depth by the application architecture.
 *
 * @since 5.0
 * @lib "gdi.lib"
 */
class TZoomFactor : public MGraphicsDeviceMap
	{
public:
	IMPORT_C TZoomFactor();
	IMPORT_C ~TZoomFactor();
	inline TZoomFactor(const MGraphicsDeviceMap* aDevice);
	IMPORT_C TInt ZoomFactor() const;
	IMPORT_C void SetZoomFactor(TInt aZoomFactor);
	inline void SetGraphicsDeviceMap(const MGraphicsDeviceMap* aDevice);
	inline const MGraphicsDeviceMap* GraphicsDeviceMap() const;
	IMPORT_C void SetTwipToPixelMapping(const TSize& aSizeInPixels,const TSize& aSizeInTwips);
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwipWidth) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwipHeight) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixelWidth) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixelHeight) const;
	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C void ReleaseFont(CFont* aFont);
public:

/**
 *
 * One to one zoom factor.
 *
 */
	enum {EZoomOneToOne=1000};
private:
	TInt iZoomFactor;
	const MGraphicsDeviceMap* iDevice;
	};

#include <gdi.inl>
#endif // __GDI_H__
