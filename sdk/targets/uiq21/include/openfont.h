// OPENFONT.H
//
// Copyright (c) 1998-2001 Symbian Ltd. All rights reserved.
//

/*
A header for the open font system, which allows
EPOC32 to use fonts of arbitrary types, including TrueType
and other outline font formats.
*/

#ifndef __OPENFONT_H__
#define __OPENFONT_H__

#include <e32base.h>
#include <gdi.h>

class CFont;
class COpenFontFile;
class COpenFontGlyph;
class COpenFontGlyphCache;
class COpenFontGlyphTreeEntry;
class COpenFontPositioner;
class COpenFontSessionCache;
class COpenFontSessionCacheList;
class RFs;
class TCharacterMetrics;
class TFontSpec;
class TOpenFontFaceAttrib;

/*
The 2nd UID (the interface type) of DLLs implementing the OpenFont interface,
which is a single exported function at ordinal 1 that creates a
COpenFontRasterizer object.
*/
const TInt KUidOpenFontRasterizerValue = 0x10003B1F;

// One of these should be used as the 3rd UID of DLLs implementing the OpenFont interface.
const TInt KUidTrueTypeRasterizerValue = 0x100012A7;
const TInt KUidBitstreamTrueDocRasterizerValue = 0x100012A8;
const TInt KUidAdobeType1RasterizerValue = 0x100012A9;
const TInt KUidAgfaMicroTypeRasterizerValue = 0x10001827;

/*
KReplacementCharacter is a Private Use Area codepoint for a character to be displayed in place of
a character that is not present in a font. If KReplacementCharacter exists in a font, it will be used,
otherwise whatever the rasterizer does by default will be used. For example, TrueType fonts return
glyph index 0 for nonexistent characters, and that is usually, but not always, mapped to an
empty rectangle
*/
const TUint KReplacementCharacter = 0xF6DB;

/**
 *
 * Font metrics.
 * @since 5.0
 * @lib "fntstr.lib"
 */
class TOpenFontMetrics
	{
public:
	inline TOpenFontMetrics();
	IMPORT_C TOpenFontMetrics(const CFont* aFont);
	inline TInt Size() const;
	inline TInt Ascent() const;
	inline TInt Descent() const;
	inline TInt MaxHeight() const;
	inline TInt MaxDepth() const;
	inline TInt MaxWidth() const;
	inline void SetSize(TInt aSize);
	inline void SetAscent(TInt aAscent);
	inline void SetDescent(TInt aDescent);
	inline void SetMaxHeight(TInt aMaxHeight);
	inline void SetMaxDepth(TInt aMaxDepth);
	inline void SetMaxWidth(TInt aMaxWidth);
private:
	TInt16 iSize;			// size of the font ('pointsize' or 'design height' in pixels)
	TInt16 iAscent;			// typographic ascent
	TInt16 iDescent;		// typographic descent
	TInt16 iMaxHeight;		// maximum height of a character; may be greater than iAscent
	TInt16 iMaxDepth;		// maximum depth of a character; may be greater than iDescent
	TInt16 iMaxWidth;		// maximum width of a character
	TInt32 iReserved;
	};

/**
 *
 * Character metrics - includes more information than
 * <code>TCharacterMetrics</code>.
 *
 * Character metrics allow characters to be placed horizontally or
 * vertically. The character metrics encapsulated by this class are:
 * Height, Width, Horizontal Bearing X, Horizontal Bearing Y, Horizontal
 * Advance, Vertical Bearing X, Vertical Bearing Y, and Vertical Advance.
 * Their meanings are described in the associated setter and getter
 * functions.Note : Vertical drawing (in the sense of characters drawn
 * with horizontal baselines, but in a vertical line) is not yet
 * supported by the Symbian platform.
 *
 * @since 5.0
 * @lib "fntstr.lib"
 */
class TOpenFontCharMetrics
	{
public:
	enum TUninitialized { EUninitialized };
public:
	inline TOpenFontCharMetrics();
/**
 *
 * A constructor without initialisation.
 *
 */
	TOpenFontCharMetrics(TUninitialized) {}
	IMPORT_C TOpenFontCharMetrics(const TCharacterMetrics& aMetrics);
	IMPORT_C TBool GetTCharacterMetrics(TCharacterMetrics& aMetrics) const;
	inline TInt Width() const;
	inline TInt Height() const;
	inline TInt HorizBearingX() const;
	inline TInt HorizBearingY() const;
	inline TInt HorizAdvance() const;
	inline TInt VertBearingX() const;
	inline TInt VertBearingY() const;
	inline TInt VertAdvance() const;
	inline void GetHorizBounds(TRect& aBounds) const;
	inline void GetVertBounds(TRect& aBounds) const;
	inline void SetWidth(TInt aWidth);
	inline void SetHeight(TInt aHeight);
	inline void SetHorizBearingX(TInt aHorizBearingX);
	inline void SetHorizBearingY(TInt aHorizBearingY);
	inline void SetHorizAdvance(TInt aHorizAdvance);
	inline void SetVertBearingX(TInt aVertBearingX);
	inline void SetVertBearingY(TInt aVertBearingY);
	inline void SetVertAdvance(TInt aVertAdvance);
private:
	TInt16 iWidth;			// width of the glyph
	TInt16 iHeight;			// height of the glyph
	TInt16 iHorizBearingX;	// x component of horizontal bearing
	TInt16 iHorizBearingY;	// y component of horizontal bearing
	TInt16 iHorizAdvance;	// horizontal advance
	TInt16 iVertBearingX;	// x component of vertical bearing
	TInt16 iVertBearingY;	// y component of vertical bearing
	TInt16 iVertAdvance;	// vertical advance
	TInt32 iReserved;
	};

/**
 *
 * Font glyph data.
 *
 * Objects of this type are used by rasterizers to supply glyph data to
 * font and bitmap server clients. Unless you are writing a rasterizer
 * you will not need to use an object of this type.The object cannot be
 * constructed and destroyed by normal means - it resides on a
 * specified heap. It is created by <code>New()</code> and deleted by
 * <code>RHeap::Free()</code>.
 *
 * @since 5.0
 * @lib "fntstr.lib"
 */
class TOpenFontGlyphData
	{
public:
	IMPORT_C static TOpenFontGlyphData* New(RHeap* aHeap,TInt aBufferSize);
	inline TBool Overflow() const;
	inline TInt BytesNeeded() const;
	inline TPtrC8 Bitmap() const;
	inline const TUint8* BitmapPointer() const;
	inline const TOpenFontCharMetrics* Metrics() const;
	inline TInt GlyphIndex() const;
	inline TUint8* BufferStart();
	inline TUint8* BufferEnd();
	inline void SetBytesNeeded(TInt aBytes);
	inline void SetBitmapPointer(const TUint8* aBitmap);
	inline void SetMetricsPointer(const TOpenFontCharMetrics* aMetrics);
	inline void SetPointersToInternalBuffers();
	inline void SetMetrics(TOpenFontCharMetrics& aMetrics);
	inline void SetGlyphIndex(TInt aGlyphIndex);
private:
	/*
	Prevent construction and destruction by normal means; the object resides on a specified heap.
	and is created by New and deleted by RHeap::Free.
	*/
	TOpenFontGlyphData();
	~TOpenFontGlyphData();
private:
	TInt iBitmapBufferSize;					// size of the buffer in bytes
	TInt iBytesNeeded;						// bytes needed for the bitmap
	TOpenFontCharMetrics iMetricsBuffer;	// the metrics
	const TUint8* iBitmap;					// pointer to the bitmap; points either to iBitmapBuffer or to
											// the cache if the character was already rasterized
	const TOpenFontCharMetrics* iMetrics;	// pointer to the metrics; points either to iMetricsBuffer or to
											// the cache if the character was already rasterized
	TInt iGlyphIndex;						// the glyph index
	TAny* iReserved;						// unused; for future expansion
	TUint8 iBitmapBuffer[1];				// buffer used to write the bitmap when it is first rasterized; this
											// is actually of size iBitmapBufferSize.
	};

/**
 *
 * Open Font System font abstract base class.
 *
 * Derive a class from this class to represent an instance of a typeface
 * at a particular size, provide bitmaps of the glyphs, and determine
 * whether characters exist in the typeface. Writing derived classes
 * construction: You must call the constructor of this class when
 * creating your derived object, passing the arguments <code>aHeap</code>
 * and <code>aSessionCacheList</code> supplied to
 * <code>COpenFontFile::GetNearestFontInPixelsL()</code>, and the address
 * of the <code>COpenFontFile</code> object that creates the object as
 * <code>aFile</code>.The derived object must be created on the shared
 * heap <code>aHeap</code> because it is shared by several processes
 * the font and bitmap server and its clients. To do this, use
 * <code>aHeap->AllocL()</code> to obtain memory, then construct in place
 * using a placement argument to <code>new</code>.Writing derived classes
 * implement the pure virtual functions:Devived classes must
 * implement the pure virtual function <code>RasterizeL()</code>.
 * Information about this function is provided in the function definition
 * below. Information about deriving from this class is also provided in
 * the API guide.
 *
 * @since 5.0
 * @lib "fntstr.lib"
 */
class COpenFont: public CBase
	{
public:
/**
 *
 * Creates a bitmap for the specified Unicode character.
 *
 * Implementations of this function should put the bitmap in
 * <code>aGlyphData->iBitmapBuffer</code>, and the character metrics are
 * placed in <code>aGlyphData->iMetricsBuffer</code>. The other parts of
 * <code>aGlyphData</code> should be left alone. There are a number of
 * strategies for achieving this, e.g. pass the rasterization task all
 * the way up to the rasterizer engine. These are discussed in the API
 * guide.At present you must write the bitmap in the Symbian platform's
 * run-length-encoded format. This is a packed binary format starting on
 * a byte boundary and made up of a number of sections. Each section
 * starts with a five-bit header. If the first bit of the header is 0 the
 * next four bits are a repeat count, starting with the least significant
 * bit, and a single row of bits (the number of bits in a row is
 * specified by <code>aGlyphData->iMetricsBuffer.Width()</code>) follows.
 * If the first bit of the header is 1 the next four bits are a count of
 * non-repeating rows, again starting with the least significant bit, and
 * that many rows of bits follow.
 *
 * @param     "TInt aCode"
 *            The character code of the Unicode character for which
 *            the bitmap is required.
 * @param     "TOpenFontGlyphData* aGlyphData"
 *            On return, contains a pointer to a TOpenFontGlyphData
 *            containing the character's bitmap and metrics.
 */
	virtual void RasterizeL(TInt aCode,TOpenFontGlyphData* aGlyphData) = 0;
	IMPORT_C virtual void Reserved(); // unused; for future expansion
	IMPORT_C COpenFont(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,COpenFontFile* aFile);
	IMPORT_C COpenFont(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,COpenFontFile* aFile,TInt aFaceIndex);
	IMPORT_C ~COpenFont();
	IMPORT_C void operator delete(TAny*);
	inline const TOpenFontMetrics& Metrics() const;
	inline const TOpenFontFaceAttrib* FaceAttrib() const;
	inline COpenFontFile* File() const;
	inline TInt FaceIndex() const;
	inline TBool CharacterNeedsToBeRasterized(TInt aSessionHandle,TInt aCode) const;
	TBool Rasterize(TInt aSessionHandle,TInt aCode,TOpenFontGlyphData* aGlyphData);
	TBool HasCharacterL(TInt aCode) const;
	TBool GetCharacterData(TInt aSessionHandle,TInt aCode,const TOpenFontCharMetrics*& aMetrics,const TUint8*& aBitmap) const;
	void OnFileDeleted();
protected:
	RHeap* iHeap;
	TOpenFontMetrics iMetrics;
	const COpenFontPositioner* iPositioner;					// the character positioning information; owned by the
															// file, but placed in shared memory and accessed
															// from the client side, so cannot be accessed via iFile
private:
	const COpenFontGlyph* Glyph(TInt aSessionHandle,TInt aCode) const;
	const COpenFontGlyph* FontCacheGlyph(TInt aCode,COpenFontGlyphTreeEntry**& aNode);
	const COpenFontGlyph* SessionCacheGlyph(RHeap* aHeap,TInt aSessionHandle,TInt aCode,
											COpenFontSessionCache*& aCache,TInt& aIndex,TBool aCreate) const;
	void RasterizeHelperL(TInt aCode,TOpenFontGlyphData* aGlyphData,TOpenFontGlyphData*& aTempGlyphData);
private:
	COpenFontFile* iFile;									// the file used by this font; null if it has been deleted
															// or cannot be used
	TInt iFaceIndex;										// index of the face in the font file
	COpenFontGlyphCache* iGlyphCache;						// the per-font glyph cache; owned by the font
	COpenFontSessionCacheList* iSessionCacheList;			// the list of per-session glyph caches; owned by CFontStore
	TAny* iReserved; // unused; for future expansion
	};

/**
 *
 * Font attribute base class.
 *
 * This class is not intended for user derivation.
 *
 * @since 5.0
 * @lib "N/A"
 */
class TOpenFontFaceAttribBase
	{
public:
	inline TOpenFontFaceAttribBase();
	inline TBool HasLatin() const;
	inline TBool HasGreek() const;
	inline TBool HasCyrillic() const;
	inline TBool HasKana() const;
	inline TBool HasHangul() const;
	inline TBool HasCJK() const;
	inline TBool IsSymbol() const;
	inline TBool IsBold() const;
	inline TBool IsItalic() const;
	inline TBool IsSerif() const;
	inline TBool IsMonoWidth() const;
	inline TPtrC Name() const;
	inline const TUint* Coverage() const;
	inline void SetName(const TDesC& aName);
	inline void SetCoverage(TUint aCoverage0,TUint aCoverage1 = 0,TUint aCoverage2 = 0,TUint aCoverage3 = 0);
	inline void SetBold(TBool aBold);
	inline void SetItalic(TBool aItalic);
	inline void SetSerif(TBool aSerif);
	inline void SetMonoWidth(TBool aMonoWidth);
	inline TBool operator==(const TOpenFontFaceAttribBase& aAttrib) const;

	// Unicode ranges for iCoverage[0] (incomplete; see the TrueType documentation for other values)
	enum
		{
		ELatinSet = 0x1,			// 0000-007F
		EGreekSet = 0x80,			// 0370-03FF
		ECyrillicSet = 0x200,		// 0400-04FF
		EArmenianSet = 0x400,		// 0530-058F
		EHebrewSet = 0x800,			// 0590-05FF
		EArabicSet = 0x2000,		// 0600-06FF
		EDevanagariSet = 0x8000,	// 0900-097F
		EBengaliSet = 0x10000,		// 0980-09FF
		EGurmukhiSet = 0x20000,		// 0A00-0A7F
		EGujuratiSet = 0x40000,		// 0A80-0AFF
		EOriyaSet = 0x80000,		// 0B00-0B7F
		ETamilSet = 0x100000,		// 0B80-0BFF
		ETeluguSet = 0x200000,		// 0C00-0C7F
		EKannadaSet = 0x400000,		// 0C80-0CFF
		EMalayalamSet = 0x800000,	// 0D00-0D7F
		EThaiSet = 0x1000000,		// 0E00-0E7F
		ELaoSet = 0x2000000,		// 0E80-0EFF
		EGeorgianSet = 0x8000000,	// 10A0-10FF
		EHangulJamoSet = 0x10000000,// 1100-11FF
		};

	// Unicode ranges for iCoverage[1]
	enum
		{
		ESymbolSets = 0xFFFE,
		EKanaSets = 0x60000,
		EHangulSet = 0x100000,
		ECJKSet = 0x8000000
		};

	// Attribute flags
	enum
		{
		EBold = 0x1,			// weight > 500 in Windows terms
		EItalic = 0x2,			// italic or oblique - any forward slant counts
		ESerif = 0x4,			// characters have serifs
		EMonoWidth = 0x8		// all characters are the same width
		};

	// Other constants
	enum
		{
		ENameLength = 32		// we allow 32 but names that are compatible with old-style fonts are limited to 24
		};
protected:
	TBufC<ENameLength> iName;				// the name of the typeface; whether this is the full name or family name
											// or is in English or another language depends on the context
	TUint iCoverage[4];						// bitmap of the character sets supported by the typeface;
											// these are the same as the fields ulUnicodeRange1 .. ulUnicodeRange4
											// in the OS/2 table in TrueType fonts
	TInt iStyle;							// bold, italic serif, and mono-width
	TInt32 iReserved;
	};

/**
 *
 * Typeface attributes.
 *
 * These attributes include the name, family name, and supported scripts.
 *
 * @since 5.0
 * @lib "N/A"
 */
class TOpenFontFaceAttrib: public TOpenFontFaceAttribBase
	{
public:
	inline TOpenFontFaceAttrib();
	inline TBool operator==(const TOpenFontFaceAttrib& aAttrib) const;
	inline TPtrC FullName() const;
	inline TPtrC FamilyName() const;
	inline TPtrC LocalFullName() const;
	inline TPtrC LocalFamilyName() const;
	inline TPtrC ShortFullName() const;
	inline TPtrC ShortFamilyName() const;
	inline TPtrC ShortLocalFullName() const;
	inline TPtrC ShortLocalFamilyName() const;
	inline void SetFullName(const TDesC& aName);
	inline void SetFamilyName(const TDesC& aName);
	inline void SetLocalFullName(const TDesC& aName);
	inline void SetLocalFamilyName(const TDesC& aName);
	inline TInt MinSizeInPixels() const;
	inline void SetMinSizeInPixels(TInt aSize);
private:
	TBufC<ENameLength> iFamilyName;			// the name without any style suffixes; usually a truncation of iFullName
	TBufC<ENameLength> iLocalFullName;		// the full name in the language of the current locale
	TBufC<ENameLength> iLocalFamilyName;	// the family name in the language of the current locale
	TInt iMinSizeInPixels;					// minimum supported size, (or readable size if scalable) in pixels
	TInt32 iReserved2;
	};

/**
 *
 * Font specification allowing more attributes to be specified than
 * <code>TFontSpec</code>.
 *
 * In addition to the attributes specified by <code>TFontSpec</code>,
 * this font specification allows stretching and slanting in the x
 * dimension, and other algorithmic effects. This is used to correct for
 * non-square pixels, and to allow algorithmic slanting and bold. The
 * width factor and slant factor transform any point (x,y) to (x *
 * <code>iWidthFactor</code> + y * <code>iSlantFactor</code>,y). The
 * width and slant factors are 16.16 fixed-point numbers.The font
 * specification also provides access to information about the scripts
 * which are supported by the font. This information is not always
 * reliable, because it may be incorrectly specified, or not specified at
 * all, by some font manufacturers.
 *
 * @since 5.0
 * @lib "fntstr.lib"
 */
class TOpenFontSpec: public TOpenFontFaceAttribBase
	{
public:
	IMPORT_C TOpenFontSpec();
	IMPORT_C TOpenFontSpec(const TFontSpec& aFontSpec);
	IMPORT_C void operator=(const TFontSpec& aFontSpec);
	inline TBool operator==(const TOpenFontSpec& aFontSpec) const;
	IMPORT_C void SetAttrib(const TOpenFontFaceAttribBase& aAttrib);
	IMPORT_C void GetTFontSpec(TFontSpec& aFontSpec) const;
	IMPORT_C void CompensateForAspectRatio(TInt aKPixelWidth,TInt aKPixelHeight);
	IMPORT_C void CompensateForAspectRatio(const MGraphicsDeviceMap& aMap);
	inline TInt Height() const;
	inline TInt32 WidthFactor() const;
	inline TInt32 SlantFactor() const;
	inline TGlyphBitmapType BitmapType() const;
	inline TUint32 Effects() const;
	inline TFontPrintPosition PrintPosition() const;
	inline void SetHeight(TInt aHeight);
	inline void SetWidthFactor(TInt32 aWidthFactor);
	inline void SetSlantFactor(TInt32 aSlantFactor);
	inline void SetBitmapType(TGlyphBitmapType aBitmapType);
	inline void SetEffects(TUint32 aEffects);
/**
 *
 * Algorothmic effects flags.
 *
 * These can be combined using an OR operation.
 *
 */
	enum
		{
/** Font is algorithmic bold.
 */
		EAlgorithmicBold = 1,
/** Font has a drop shadow.
 */
		EDropShadow = 2,
/** Font is an outline font.
 */
		EOutline = 4
		};
private:
	TInt iHeight;						// em height
	TInt32 iWidthFactor;				// algorithmic width factor as a 16.16 fixed-point number
	TInt32 iSlantFactor;				// algorithmic slant factor as a 16.16 fixed-point number
	TInt iBitmapType;					// non-anti-aliased, standard anti-aliased, etc.; zero means 'default'
	TUint32 iEffects;					// bit flags for other effects like algorithmic bold and drop-shadow

	// The following data members exist only to allow round-trip conversion between TFontSpec and TOpenFontSpec
	TBool iSymbol;						// specifies a symbol font as understood by TFontSpec
	TFontPrintPosition iPrintPosition;	// normal, superscript or subscript

	TInt iReserved2;
	};

// Constants for attachment points for diacritics.
enum TOpenFontAttachment
	{
	EBaselineLeft,
	EBaselineRight,
	ETopLeft,
	ETopCenter,
	ETopRight,
	EBottomLeft,
	EBottomCenter,
	EBottomRight
	};

/**
 *
 * Font file abstract base class.
 *
 * Write a class derived from <code>COpenFontFile</code> to manage a file
 * with the font format supported by your DLL. The derived class must
 * implement the virtual <code>GetNearestFontInPixelsL()</code> function.
 * This function takes a font description and creates a
 * <code>COpenFont</code> derived object if the description matches a
 * typeface contained in the font file.Derived classes must also load
 * typeface attributes from the file into the protected typeface
 * attribute array during construction. This array is what is searched
 * when getting font attribute information - see
 * <code>AddArrayL()</code>, <code>GetNearestFontHelper()</code>.Writing
 * derived classes - construction:Call the <code>COpenFontFile</code>
 * constructor in the constructor for your derived object, passing it
 * <code>aUid</code> and <code>aFileName</code> arguments. These values
 * are the arguments passed when the constructor is called by
 * <code>COpenFontRasterizer::NewFontFileL()</code>.A file may contain
 * one or more typefaces. During construction the derived object should
 * extract the information for each typeface and add it to this object's
 * protected typeface attribute array - see <code>AddFaceL()</code>.
 * This process will probably leave under some conditions. It should
 * therefore be implemented in a second phase constructor.Writing derived
 * classes - implement the pure virtual functions:Derived classes must
 * also implement the two pure virtual functions
 * <code>GetNearestFontInPixelsL()</code> and
 * <code>HasUnicodeCharacterL()</code>. Information about these functions
 * is provided in the definitions below. Information about deriving from
 * this class is also provided in the API guide.
 *
 * @since 5.0
 * @lib "fntstr.lib"
 */
class COpenFontFile: public CBase
	{
public:
/**
 *
 * Gets the nearest font in pixels.
 *
 * Implementations of this pure virtual function should create the
 * <code>COpenFont</code> derived object that most closely matches
 * <code>aFontSpec</code>, and place a pointer to it in
 * <code>aFont</code>. If this cannot be done, e.g. if the font name
 * doesn't match, <code>aFont</code> should be set to <code>NULL</code>.
 * The other two arguments, <code>aHeap</code> and
 * <code>aSessionCacheList</code>, should be passed to the
 * <code>COpenFont</code> constructor.Note:Implementations may use the
 * utilitity function <code>GetNearestFontHelper()</code> to get the
 * attributes of the closest matching font.
 *
 * @param     "RHeap* aHeap"
 *            Shared heap. This value should be passed to the
 *            <code>COpenFont</code> derived classes' constructor.
 * @param     "COpenFontSessionCacheList* aSessionCacheList"
 *            The session cache list. This value should be passed to
 *            the <code>COpenFont</code> derived classes'
 *            constructor.
 * @param     "const TOpenFontSpec& aDesiredFontSpec"
 *            The desired font specification.
 * @param     "TInt aPixelWidth"
 *            The width of a pixel. Used with
 *            <code>aPixelHeight</code> for calculating the
 *            algorithmic slant of the typeface.
 * @param     "TInt aPixelHeight"
 *            The height of a pixel. Used with
 *            <code>aPixelWidth</code> for calculating the
 *            algorithmic slant of the typeface.
 * @param     "COpenFont*& aFont"
 *            On return, contains a pointer to the newly created
 *            <code>COpenFont</code> derived object, or NULL if no
 *            font matching <code>aDesiredFontSpec</code> exists.
 * @param     "TOpenFontSpec& aActualFontSpec"
 *            The actual font specification of the font retrieved
 *            into <code>aFont</code>.
 */
	virtual void GetNearestFontInPixelsL(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,
										 const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
										 COpenFont*& aFont,TOpenFontSpec& aActualFontSpec) = 0;
/**
 *
 * Tests whether a specified typeface contains a particular character.
 *
 * @param     "TInt aFaceIndex"
 *            The index of the typeface to be tested.
 * @param     "TInt aCode"
 *            The Unicode character code for the character to be
 *            tested.
 * @returns   "TBool"
 *            <code>ETrue</code> if the typeface contains
 *            <code>aCode</code>, otherwise <code>EFalse</code>.
 */
	virtual TBool HasUnicodeCharacterL(TInt aFaceIndex,TInt aCode) const = 0; 
	IMPORT_C virtual void Reserved(); // unused; for future expansion
	IMPORT_C COpenFontFile(TInt aUid,const TDesC& aFileName);
	IMPORT_C ~COpenFontFile();
	IMPORT_C TBool GetNearestFontHelper(const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
										TInt& aFaceIndex,TOpenFontSpec& aActualFontSpec) const;
	IMPORT_C void AddFaceL(const TOpenFontFaceAttrib& aAttrib);
	inline TUid Uid() const;
	inline const TDesC& FileName() const;
	inline const TOpenFontFaceAttrib& FaceAttrib(TInt aFaceIndex) const;
	inline TInt FaceCount() const;
	inline void IncRefCount();
	inline TBool DecRefCount();
	TInt GetNearestFontInPixels(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,
								const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
								COpenFont*& aFont,TOpenFontSpec& aActualFontSpec);
	void RemoveFontFromList(const COpenFont* aFont);
private:
	// A class to contain the public font attributes and private positioning information (for kerning, ligatures, etc.)
	class TAttrib: public TOpenFontFaceAttrib
		{
		public:
		COpenFontPositioner* iPositioner;	// if non-null, positioning information for the typeface
		};
private:
	CArrayFixFlat<TAttrib> iFaceAttrib;
	TUid iUid;
	TBuf<KMaxFileName> iFileName;
	TInt iRefCount;
	CArrayPtrFlat<COpenFont> iFontList;
	TAny* iReserved; // unused; for future expansion
	};

/**
 *
 * Font rasterizer abstract base class.
 *
 * An Open Font System rasterizer is a polymorphic DLL. It contains a
 * single exported factory function which creates rasterizer objects for
 * a specific font type - these objects are derived from
 * <code>COpenFontRasterizer</code>. This function is called just once,
 * when the Font and Bitmap Server loads the DLL.The rasterizer also
 * implements, but does not export, the single pure virtual function
 * declared in this class. The function reads font files, and creates a
 * <code>COpenFontFile</code> object if the font file is of the right
 * type.Writing derived classes:Open font rasterizers should derive from
 * this class and implement the <code>NewFontFileL()</code>
 * function.Derived classes should also define the factory function. It
 * is a static function which takes no arguments, and it is the only
 * function exported from the class. It creates a
 * <code>COpenFontRasterizer</code> derived object on the heap, and
 * returns it to the caller - the caller is responsible for deleting
 * the object. The name of the function does not matter because it is
 * loaded by ordinal, however it is good practice to name it
 * <code>NewL()</code>. As the name of the example function suggests, it
 * is allowed to leave.The rasterizer class may also need to store an
 * 'engine context'. This is an object derived from
 * <code>COpenFontRasterizerContext</code>, which provides functions that
 * make it easier to write the glyph bitmap during rasterization.More
 * information on deriving from this class is provided in the API guide.
 *
 * @since 5.0
 * @lib "fntstr.lib"
 */
class COpenFontRasterizer: public CBase
	{
public:
/**
 *
 * Creates a <code>COpenFontFile</code> derived object for loading font
 * files in the new format.
 *
 * This function is called by the framework during font and bitmap server
 * startup. It creates a font file object for font files in the
 * \system\fonts directory on all drives, using the default search path.
 * The first font of a given name overrides subsequent ones. The
 * directory search path is soft to hard: Y:, X:, W:, ..., C:, B:, A:,
 * Z:. Files may also be added dynamically after startup using
 * <code>CWsScreenDevice::AddFile()</code>, which indirectly calls this
 * function.Implementations of this function should examine the file
 * <code>aFileName</code>, and if it is of the correct type attempt to
 * create a <code>COpenFontFile</code> derived object to load it. The
 * caller is responsible for deleting the object. The function must
 * return NULL if it cannot recognise the file, and it may also leave if
 * there is an error.
 *
 * @param     "TInt aUid"
 *            An ID to be used for the file. UIDs are required by
 *            the font framework, so the font store allocates them
 *            for non Symbian-platform-native font files. This ID
 *            persists until the font is unloaded, e.g. if the
 *            device is rebooted.
 * @param     "const TDesC& aFileName"
 *            The full path and filename of the file from which the
 *            <code>COpenFontFile</code> object is created, if the
 *            file is the correct type.
 * @param     "RFs& aFileSession"
 *            The file session owned by the Font and Bitmap server.
 *            This file session should be used for any file access.
 *            If <code>COpenFontFile</code> objects need to keep
 *            files open, <code>aFileSession</code> should be stored
 *            in a place that is accessible to them.
 * @returns   "COpenFontFile*"
 *            A pointer to a new <code>COpenFontFile</code> derived
 *            object, or NULL if the file type is not recognised.
 */
	virtual COpenFontFile* NewFontFileL(TInt aUid,const TDesC& aFileName,RFs& aFileSession) = 0;
	IMPORT_C virtual void Reserved(); // unused; for future expansion
private:
	TAny* iReserved; // unused; for future expansion
	};

/**
 *
 * Convenience class from which rasterizer contexts may be derived.
 *
 * A rasterizer context object may (optionally) be created to provide the
 * link between the rasterizer DLL code supported by the Open Font
 * System, and the rasterizer engine code. A rasterizer context object
 * class should get the requested bitmap from the associated rasterizer
 * engine. It should then convert this into Symbian run-length-encoded
 * format. This class contains convenience functions to make the
 * conversion easier.
 *
 * @since 5.0
 * @lib "fntstr.lib"
 */
class COpenFontRasterizerContext: public CBase
	{
public:
	inline COpenFontRasterizerContext();
	inline void StartGlyph(TOpenFontGlyphData* aGlyphData);
	inline void WriteGlyphBit(TInt aBit);
	inline void WriteGlyphByte(TInt aByte);
	inline void EndGlyph();
private:
	TOpenFontGlyphData* iGlyphData;
	TUint8* iGlyphDataStart;
	TUint8* iGlyphDataPtr;
	TUint8* iGlyphDataEnd;
	TInt iGlyphBit;
	TInt iBytesNeeded;
	TBool iOverflow;
	TAny* iReserved; // unused; for future expansion
	};


// Inline functions start here.

/**
 *
 * Default constructor.
 *
 */
inline TOpenFontMetrics::TOpenFontMetrics()
	{
	Mem::FillZ(this,sizeof(*this));
	}

/**
 *
 * Gets the font's size.
 *
 * @returns   "TInt"
 *            The font's size.
 */
inline TInt TOpenFontMetrics::Size() const
	{
	return iSize;
	}

/**
 *
 * Gets the font's ascent.
 *
 * Note:The ascent is usually the height of a Latin capital letter above
 * the baseline.
 *
 * @returns   "TInt"
 *            The font's ascent, in pixels.
 */
inline TInt TOpenFontMetrics::Ascent() const
	{
	return iAscent;
	}

/**
 *
 * Gets the font's descent.
 *
 * Note:The descent is usually the depth of a Latin lowercase 'p', 'q',
 * or 'y' below the baseline.
 *
 * @returns   "TInt"
 *            The font's descent, in pixels.
 */
inline TInt TOpenFontMetrics::Descent() const
	{
	return iDescent;
	}

/**
 *
 * Sets the font's maximum height.
 *
 * Note that if this object was initialised from the <code>CFont</code>
 * this will be the same as the ascent.Note: If this object was
 * initialised from the <code>CFont</code> this will be the same as the
 * ascent.This is the ascent for the character which is highest above the
 * baseline. In many fonts this will be the height of an accented
 * character like , including the accent.
 *
 * @returns   "TInt"
 *            The maximum height of the font, in pixels.
 */
inline TInt TOpenFontMetrics::MaxHeight() const
	{
	return iMaxHeight;
	}

/**
 *
 * Gets the font's maximum depth.
 *
 * Note: If this object was initialised from the <code>CFont</code> this
 * will be the same as the descent.This is the descent for the character
 * in the font which falls furthest below the baseline.
 *
 * @returns   "TInt"
 *            The font's maximum depth.
 */
inline TInt TOpenFontMetrics::MaxDepth() const
	{
	return iMaxDepth;
	}

/**
 *
 * Gets the maximum character width, in pixels.
 *
 * @returns   "TInt"
 *            The maximum character width, in pixels.
 */
inline TInt TOpenFontMetrics::MaxWidth() const
	{
	return iMaxWidth;
	}

/**
 *
 * Sets the font's size.
 *
 * @param     "TInt aSize"
 *            The font's size.
 */
inline void TOpenFontMetrics::SetSize(TInt aSize)
	{
	iSize = static_cast<TInt16>(aSize);
	}

/**
 *
 * Sets the ascent.
 *
 * @param     "TInt aAscent"
 *            The ascent, in pixels.
 */
inline void TOpenFontMetrics::SetAscent(TInt aAscent)
	{
	iAscent = static_cast<TInt16>(aAscent);
	}

/**
 *
 * Sets the descent.
 *
 * @param     "TInt aDescent"
 *            The descent, in pixels.
 */
inline void TOpenFontMetrics::SetDescent(TInt aDescent)
	{
	iDescent = static_cast<TInt16>(aDescent);
	}

/**
 *
 * Sets the font's maximum height.
 *
 * @param     "TInt aMaxHeight"
 *            The font's maximum height, in pixels.
 */
inline void TOpenFontMetrics::SetMaxHeight(TInt aMaxHeight)
	{
	iMaxHeight = static_cast<TInt16>(aMaxHeight);
	}

/**
 *
 * Sets the font's maximum depth.
 *
 * @param     "TInt aMaxDepth"
 *            The font's maximum depth, in pixels.
 */
inline void TOpenFontMetrics::SetMaxDepth(TInt aMaxDepth)
	{
	iMaxDepth = static_cast<TInt16>(aMaxDepth);
	}

/**
 *
 * Sets the maximum character width, in pixels.
 *
 * @param     "TInt aMaxWidth"
 *            The maximum character width, in pixels.
 */
inline void TOpenFontMetrics::SetMaxWidth(TInt aMaxWidth)
	{
	iMaxWidth = static_cast<TInt16>(aMaxWidth);
	}

/**
 *
 * Default constructor with initialisation.
 *
 */
inline TOpenFontCharMetrics::TOpenFontCharMetrics()
	{
	Mem::FillZ(this,sizeof(*this));
	}

/**
 *
 * Gets the width of the character's bitmap.
 *
 * @returns   "TInt"
 *            The width of the bitmap in pixels.
 */
inline TInt TOpenFontCharMetrics::Width() const
	{
	return iWidth;
	}

/**
 *
 * Gets the height of the character's bitmap.
 *
 * @returns   "TInt"
 *            The character's height in pixels.
 */
inline TInt TOpenFontCharMetrics::Height() const
	{
	return iHeight;
	}

/**
 *
 * Gets the horizontal bearing X.
 *
 * This is the distance in pixels from the pen point before the character
 * is drawn (the origin) to the left edge of the bitmap, when drawing
 * horizontally. A positive value means that the left edge of the bitmap
 * is right of the origin.
 *
 * @returns   "TInt"
 *            The horizontal bearing X in pixels
 */
inline TInt TOpenFontCharMetrics::HorizBearingX() const
	{
	return iHorizBearingX;
	}

/**
 *
 * Gets horizontal bearing Y.
 *
 * This is the vertical distance in pixels from the pen point before the
 * character is drawn (the origin) to the top edge of the bitmap, when
 * drawing horizontally. A positive value means that the top edge of the
 * bitmap is above the origin
 *
 * @returns   "TInt"
 *            The horizontal bearing Y in pixels.
 */
inline TInt TOpenFontCharMetrics::HorizBearingY() const
	{
	return iHorizBearingY;
	}

/**
 *
 * Gets the horizontal advance.
 *
 * This is the amount added to the x co-ordinate of the origin after the
 * character is drawn - what most people understand by the width or
 * escapement of a character. The origin here is the pen point before the
 * character is drawn.
 *
 * @returns   "TInt"
 *            The horizontal advance in pixels
 */
inline TInt TOpenFontCharMetrics::HorizAdvance() const
	{
	return iHorizAdvance;
	}

/**
 *
 * Gets the vertical bearing X.
 *
 * This is the distance in pixels from the pen point before the character
 * is drawn (the origin) to the left edge of the bitmap, when drawing
 * vertically. A positive value means that the left edge of the bitmap is
 * right of the origin.
 *
 * @returns   "TInt"
 *            The vertical bearing X in pixels.
 */
inline TInt TOpenFontCharMetrics::VertBearingX() const
	{
	return iVertBearingX;
	}

/**
 *
 * Gets the vertical bearing Y.
 *
 * This is the distance in pixels from the pen point before the character
 * is drawn (the origin) to the top edge of the bitmap, when drawing
 * vertically. A positive value means that the top edge of the bitmap is
 * above the origin.
 *
 * @returns   "TInt"
 *            The vertical bearing Y in pixels.
 */
inline TInt TOpenFontCharMetrics::VertBearingY() const
	{
	return iVertBearingY;
	}

/**
 *
 * Gets the vertical advance.
 *
 * When drawing vertically, this is the amount added to the y co-ordinate
 * of the origin after the character is drawn - what most people
 * understand by the height of a character. The origin here is the pen
 * point before the character is drawn.Note:Vertical drawing is not
 * supported in ER5.
 *
 * @returns   "TInt"
 *            The vertical advance in pixels.
 */
inline TInt TOpenFontCharMetrics::VertAdvance() const
	{
	return iVertAdvance;
	}

/**
 *
 * Gets the bounds of the character relative to its origin when setting
 * text horizontally.
 *
 * The origin here is the pen point before the character is drawn.
 *
 * @since     6.0
 * @param     "TRect& aBounds"
 *            The character's bounds.
 */
inline void TOpenFontCharMetrics::GetHorizBounds(TRect& aBounds) const
	{
	aBounds.iTl.iX = iHorizBearingX;
	aBounds.iTl.iY = -iHorizBearingY;
	aBounds.iBr.iX = aBounds.iTl.iX + iWidth;
	aBounds.iBr.iY = aBounds.iTl.iY + iHeight;
	}

/**
 *
 * Gets the bounds of the character relative to its origin when setting
 * text vertically.
 *
 * The origin here is the pen point before the character is drawn.
 *
 * @since     6.0
 * @param     "TRect& aBounds"
 *            The character's bounds.
 */
inline void TOpenFontCharMetrics::GetVertBounds(TRect& aBounds) const
	{
	aBounds.iTl.iX = -iVertBearingX;
	aBounds.iTl.iY = iVertBearingY;
	aBounds.iBr.iX = aBounds.iTl.iX + iWidth;
	aBounds.iBr.iY = aBounds.iTl.iY + iHeight;
	}

/**
 *
 * Sets the width of the character's bitmap.
 *
 * @param     "TInt aWidth"
 *            The width of the bitmap in pixels.
 */
inline void TOpenFontCharMetrics::SetWidth(TInt aWidth)
	{
	iWidth = (TInt16)aWidth;
	}

/**
 *
 * Sets the height of the character's bitmap.
 *
 * @param     "TInt aHeight"
 *            The character height (in pixels).
 */
inline void TOpenFontCharMetrics::SetHeight(TInt aHeight)
	{
	iHeight = (TInt16)aHeight;
	}

/**
 *
 * Sets the horizontal bearing X.
 *
 * This is the distance in pixels from the pen point before the character
 * is drawn (the origin) to the left edge of the bitmap, when drawing
 * horizontally. A positive value means that the left edge of the bitmap
 * is right of the origin.
 *
 * @param     "TInt aHorizBearingX"
 *            The horizontal bearing X (in pixels).
 */
inline void TOpenFontCharMetrics::SetHorizBearingX(TInt aHorizBearingX)
	{
	iHorizBearingX = (TInt16)aHorizBearingX;
	}

/**
 *
 * Sets the horizontal bearing Y.
 *
 * This is the distance in pixels from the pen point before the character
 * is drawn (the origin) to the top edge of the bitmap, when drawing
 * horizontally. A positive value means that the top edge of the bitmap
 * is above the origin.
 *
 * @param     "TInt aHorizBearingY"
 *            The horizontal bearing Y (in pixels).
 */
inline void TOpenFontCharMetrics::SetHorizBearingY(TInt aHorizBearingY)
	{
	iHorizBearingY = (TInt16)aHorizBearingY;
	}

/**
 *
 * Sets the horizontal advance.
 *
 * This is the amount added to the x co-ordinate of the origin after the
 * character is drawn - what most people understand by the width or
 * escapement of a character. The origin here is the pen point before the
 * character is drawn.
 *
 * @param     "TInt aHorizAdvance"
 *            The horizontal advance (in pixels).
 */
inline void TOpenFontCharMetrics::SetHorizAdvance(TInt aHorizAdvance)
	{
	iHorizAdvance = (TInt16)aHorizAdvance;
	}

/**
 *
 * Set vertical bearing X.
 *
 * This is the distance in pixels from the pen point before the character
 * is drawn (the origin) to the left edge of the bitmap, when drawing
 * vertically. A positive value means that the left edge of the bitmap is
 * right of the origin.
 *
 * @param     "TInt aVertBearingX"
 *            The vertical bearing X (in pixels).
 */
inline void TOpenFontCharMetrics::SetVertBearingX(TInt aVertBearingX)
	{
	iVertBearingX = (TInt16)aVertBearingX;
	}

/**
 *
 * Sets the vertical bearing Y.
 *
 * This is the distance in pixels from the pen point before the character
 * is drawn (the origin) to the top edge of the bitmap, when drawing
 * vertically. A positive value means that the top edge of the bitmap is
 * above the origin.
 *
 * @param     "TInt aVertBearingY"
 *            The vertical bearing Y (in pixels).
 */
inline void TOpenFontCharMetrics::SetVertBearingY(TInt aVertBearingY)
	{
	iVertBearingY = (TInt16)aVertBearingY;
	}

/**
 *
 * Sets the vertical advance.
 *
 * When drawing vertically, this is the amount added to the y co-ordinate
 * of the origin after the character is drawn - what most people
 * understand by the height of a character. The origin here is the pen
 * point before the character is drawn.Note:Vertical drawing is not
 * supported in ER5.
 *
 * @param     "TInt aVertAdvance"
 *            The vertical advance (in pixels).
 */
inline void TOpenFontCharMetrics::SetVertAdvance(TInt aVertAdvance)
	{
	iVertAdvance = (TInt16)aVertAdvance;
	}

/**
 *
 * Gets the character metrics for this font.
 *
 * @returns   "TOpenFontMetrics&"
 *            The character metrics for this font.
 */
inline const TOpenFontMetrics& COpenFont::Metrics() const
	{
	return iMetrics;
	}

/**
 *
 * Gets the glyph index.
 *
 * This is the index of a particular glyph within the font
 * file.Notes:This makes it possible to gain access to glyphs which are
 * not referenced by the Unicode character set. However, this feature is
 * not yet supported by the Symbian platform.
 *
 * @since     6.0
 * @returns   "TInt"
 *            The glyph index.
 */
inline TInt TOpenFontGlyphData::GlyphIndex() const
	{
	return iGlyphIndex;
	}

/**
 *
 * Gets the typeface attributes.
 *
 * These are the attributes of the font represented by this object.
 *
 * @returns   "TOpenFontFaceAttrib*"
 *            The typeface attributes.
 */
inline const TOpenFontFaceAttrib* COpenFont::FaceAttrib() const
	{
	return iFile ? &iFile->FaceAttrib(iFaceIndex) : NULL;
	}

/**
 *
 * Gets a pointer to the <code>COpenFontFile</code> which created this
 * object.
 *
 * This is the <code>COpenFontFile</code> which owns the file that
 * contains the definition of the typeface. It can be used to get
 * information about the typeface, or to access the rasterizer context
 * (engine).
 *
 * @returns   "COpenFontFile*"
 *            The <code>COpenFontFile</code> which created this
 *            object.
 */
inline COpenFontFile* COpenFont::File() const
	{
	return iFile;
	}

/**
 *
 * Gets the index of this typeface within the font file.
 *
 * @returns   "TInt"
 *            The index of this typeface within the font file.
 */
inline TInt COpenFont::FaceIndex() const
	{
	return iFaceIndex;
	}

/**
 *
 * Tests whether or not a character needs to be rasterized.
 *
 * Characters that have been rasterized are cached - there is no need
 * to regenerate the character bitmap. This function should only be
 * called by the Font and bitmap server.
 *
 * @since     6.0
 * @param     "TInt aSessionHandle"
 *            A handle to the font and bitmap server session.
 * @param     "TInt aCode"
 *            The code for the Unicode character.
 * @returns   "TBool"
 *            <code>ETrue</code> if the character needs to be
 *            rasterized, otherwise <code>EFalse</code>.
 */
inline TBool COpenFont::CharacterNeedsToBeRasterized(TInt aSessionHandle,TInt aCode) const
	{
	return Glyph(aSessionHandle,aCode) == NULL;
	}

/**
 *
 * Default C++ constructor.
 *
 * This sets all attribute fields to zero. As for other T classes, there
 * is no need to explicitly clean-up objects derived from this class.
 *
 */
inline TOpenFontFaceAttribBase::TOpenFontFaceAttribBase()
	{
	Mem::FillZ(this,sizeof(*this));
	}

/**
 *
 * Default C++ constructor.
 *
 * The function initialises the minimum typeface size to zero, the names
 * to NULL, and the coverage and style flags to zero.
 *
 */
inline TOpenFontFaceAttrib::TOpenFontFaceAttrib():
	iMinSizeInPixels(0),
	iReserved2(0)
	{
	}

/**
 *
 * Tests for support of Latin characters.
 *
 * Note:A return value of <code>ETrue</code> implies that the font has a
 * useable set of characters. It does not imply exhaustive coverage.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if Latin characters are supported
 */
inline TBool TOpenFontFaceAttribBase::HasLatin() const
	{
	return iCoverage[0] & ELatinSet;
	}

/**
 *
 * Tests for support of Greek characters.
 *
 * Note:A return value of <code>ETrue</code> implies that the font has a
 * useable set of characters. It does not imply exhaustive coverage.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if Greek characters are supported.
 */
inline TBool TOpenFontFaceAttribBase::HasGreek() const
	{
	return iCoverage[0] & EGreekSet;
	}

/**
 *
 * Tests for support of Cyrillic characters.
 *
 * Note:A return value of <code>ETrue</code> implies that the font has a
 * useable set of characters. It does not imply exhaustive coverage.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if Cyrillic characters are
 *            supported.
 */
inline TBool TOpenFontFaceAttribBase::HasCyrillic() const
	{
	return iCoverage[0] & ECyrillicSet;
	}

/**
 *
 * Tests for support of Japanese syllabic characters.
 *
 * This function tests for the presence of Hiragana and Katakana syllabic
 * characters in the font, collectively called kana. These characters are
 * not sufficient for the Japanese language, which also makes use of
 * Chinese characters.Note:A return value of <code>ETrue</code> implies
 * that the font has a useable set of characters. It does not imply
 * exhaustive coverage.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if Japanese characters are
 *            supported
 */
inline TBool TOpenFontFaceAttribBase::HasKana() const
	{
	return iCoverage[1] & EKanaSets;
	}

/**
 *
 * Tests for support of Korean Hangul characters.
 *
 * Korean may also make use of Chinese characters.Note:A return value of
 * <code>ETrue</code> implies that the font has a useable set of
 * characters. It does not imply exhaustive coverage.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if Korean characters are supported
 */
inline TBool TOpenFontFaceAttribBase::HasHangul() const
	{
	return iCoverage[1] & EHangulSet;
	}

/**
 *
 * Tests for support of Chinese ideographic characters.
 *
 * These are used in Chinese, Japanese and Korean.Note:A return value of
 * <code>ETrue</code> implies that the font has a useable set of
 * characters. It does not imply exhaustive coverage.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if Chinese ideographs are
 *            supported.
 */
inline TBool TOpenFontFaceAttribBase::HasCJK() const
	{
	return iCoverage[1] & ECJKSet;
	}

/**
 *
 * Tests if the typeface contains symbols only.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the typeface contains symbols
 *            only.
 */
inline TBool TOpenFontFaceAttribBase::IsSymbol() const
	{
	return iCoverage[0] == 0 && iCoverage[2] == 0 && iCoverage[3] == 0 &&
		   iCoverage[1] & ESymbolSets && !(iCoverage[1] & ~ESymbolSets);
	}

/**
 *
 * Tests if the typeface is inherently bold.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the typeface is inherently bold.
 */
inline TBool TOpenFontFaceAttribBase::IsBold() const
	{
	return iStyle & EBold;
	}

/**
 *
 * Tests if the typeface is inherently italic.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the typeface is inherently
 *            italic.
 */
inline TBool TOpenFontFaceAttribBase::IsItalic() const
	{
	return iStyle & EItalic;
	}

/**
 *
 * Tests if the typeface has serifs.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the typeface has serifs.
 */
inline TBool TOpenFontFaceAttribBase::IsSerif() const
	{
	return iStyle & ESerif;
	}

/**
 *
 * Tests if all the characters have the same width.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if all the characters have the same
 *            width.
 */
inline TBool TOpenFontFaceAttribBase::IsMonoWidth() const
	{
	return iStyle & EMonoWidth;
	}

/**
 *
 * Gets the typeface's name.
 *
 * @returns   "TPtrC"
 *            Descriptor containing typeface name.
 */
inline TPtrC TOpenFontFaceAttribBase::Name() const
	{
	return iName;
	}

/**
 *
 * Gets the full name.
 *
 * The full name of the typeface includes style attributes like Italic,
 * Bold, and Cursive.
 *
 * @returns   "TPtrC"
 *            The full name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::FullName() const
	{
	return Name();
	}

/**
 *
 * Gets the family name.
 *
 * Note:The family name of the typeface does not include style attributes
 * like "Italic".
 *
 * @returns   "TPtrC"
 *            The family name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::FamilyName() const
	{
	return iFamilyName;
	}

/**
 *
 * Gets the local full name.
 *
 * The local full name of the typeface includes style attributes like
 * Italic, Bold, and Cursive.The local name of the typeface is the name
 * in the language of the current locale, where this is provided by the
 * font file. If the local name is not available then the local name will
 * be the same as the ordinary name.
 *
 * @returns   "TPtrC"
 *            The local full name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::LocalFullName() const
	{
	return iLocalFullName;
	}

/**
 *
 * Gets the local family name.
 *
 * The local name of the typeface is the name in the language of the
 * current locale, where this is provided by the font file. If the local
 * name is not available then the local name will be the same as the
 * ordinary name.Note:The family name of the typeface does not include
 * style attributes like 'Italic'.
 *
 * @returns   "TPtrC"
 *            The local family name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::LocalFamilyName() const
	{
	return iLocalFamilyName;
	}

/**
 *
 * Gets the short full name.
 *
 * This is the full name of the typeface, truncated to
 * <code>KMaxTypefaceNameLength</code>, if necessary.Note:Short names are
 * names truncated to <code>KMaxTypefaceNameLength</code> (24) characters
 * where necessary so that they can be used in the <code>TTypeFace</code>
 * class. The Open Font Framework allows 32 characters as a maximum name
 * length.
 *
 * @returns   "TPtrC"
 *            The short full name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::ShortFullName() const
	{
	// Can't use TDesC::Left for this because it panics if the desired length is > the existing length!
	return TPtrC(iName.Ptr(),Min(iName.Length(),KMaxTypefaceNameLength));
	}

/**
 *
 * Gets the short family name.
 *
 * This is the family name, truncated to
 * <code>KMaxTypefaceNameLength</code>, if necessary.Note:Short names are
 * names truncated to <code>KMaxTypefaceNameLength</code> (24) characters
 * where necessary so that they can be used in the <code>TTypeFace</code>
 * class. The Open Font Framework allows 32 characters as a maximum name
 * length.
 *
 * @returns   "TPtrC"
 *            The short family name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::ShortFamilyName() const
	{
	return TPtrC(iFamilyName.Ptr(),Min(iFamilyName.Length(),KMaxTypefaceNameLength));
	}

/**
 *
 * Gets the short local full name.
 *
 * This is the local full name of the typeface, truncated to
 * <code>KMaxTypefaceNameLength</code>, if necessary.Note:Short names are
 * names truncated to <code>KMaxTypefaceNameLength</code> (24) characters
 * where necessary so that they can be used in the <code>TTypeFace</code>
 * class. The Open Font Framework allows 32 characters as a maximum name
 * length.
 *
 * @returns   "TPtrC"
 *            The short local full name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::ShortLocalFullName() const
	{
	return TPtrC(iLocalFullName.Ptr(),Min(iLocalFullName.Length(),KMaxTypefaceNameLength));
	}

/**
 *
 * Gets the short local family name.
 *
 * This is the local family name of the typeface, truncated to
 * <code>KMaxTypefaceNameLength</code>, if necessary.Note:Short names are
 * names truncated to <code>KMaxTypefaceNameLength</code> (24) characters
 * where necessary so that they can be used in the <code>TTypeFace</code>
 * class. The Open Font Framework allows 32 characters as a maximum name
 * length.
 *
 * @returns   "TPtrC"
 *            The short local family name of the typeface.
 */
inline TPtrC TOpenFontFaceAttrib::ShortLocalFamilyName() const
	{
	return TPtrC(iLocalFamilyName.Ptr(),Min(iLocalFamilyName.Length(),KMaxTypefaceNameLength));
	}

/**
 *
 * Gets a pointer to the 128-bit coverage bitmap.
 *
 * Each bit in the bitmap represents a subset of Unicode that is
 * supported. The mapping is defined in the TrueType documentation under
 * the OS/2 table. Note:Some useful subsets are defined as anonymous
 * enumerated constants at the end of this class, see
 * <code>ELatinSet</code> etc.
 *
 * @returns   "TUint*"
 *            A pointer to the 128-bit coverage bitmap. The coverage
 *            bitmap is an array of four 32-bit integers. When no
 *            information is available all four integers are zero.
 */
inline const TUint* TOpenFontFaceAttribBase::Coverage() const
	{
	return iCoverage;
	}

/**
 *
 * Gets the minimum typeface size.
 *
 * This is the smallest size that can be drawn legibly.
 *
 * @returns   "TInt"
 *            The minimum typeface size (in pixels).
 */
inline TInt TOpenFontFaceAttrib::MinSizeInPixels() const
	{
	return iMinSizeInPixels;
	}

/**
 *
 * Sets the name attribute.
 *
 * @param     "const TDesC& aName"
 *            Descriptor containing typeface name.
 */
inline void TOpenFontFaceAttribBase::SetName(const TDesC& aName)
	{
	iName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

/**
 *
 * Sets the full name.
 *
 * @param     "const TDesC& aName"
 *            The full name of the typeface.
 */
inline void TOpenFontFaceAttrib::SetFullName(const TDesC& aName)
	{
	SetName(aName);
	}

/**
 *
 * Sets the family name.
 *
 * @param     "const TDesC& aName"
 *            The family name of the typeface.
 */
inline void TOpenFontFaceAttrib::SetFamilyName(const TDesC& aName)
	{
	iFamilyName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

/**
 *
 * Sets the local full name.
 *
 * @param     "const TDesC& aName"
 *            The local full name of the typeface.
 */
inline void TOpenFontFaceAttrib::SetLocalFullName(const TDesC& aName)
	{
	iLocalFullName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

/**
 *
 * Sets the local family name.
 *
 * @param     "const TDesC& aName"
 *            The local family name of the typeface.
 */
inline void TOpenFontFaceAttrib::SetLocalFamilyName(const TDesC& aName)
	{
	iLocalFamilyName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

/**
 *
 * Sets the coverage bitmap.
 *
 * This is a 128-bit bitmap in which each bit represents a subset of
 * Unicode that is supported by the typeface. The mapping is defined in
 * the TrueType documentation under the OS/2 table.Note: Some useful
 * subsets are defined as anonymous enumerated constants at the end of
 * this class, see <code>ELatinSet</code> etc.
 *
 * @param     "TUint aCoverage0"
 *            Bits 0-31 of the coverage bitmap.
 * @param     "TUint aCoverage1"
 *            Bits 32-63 of the coverage bitmap.
 * @param     "TUint aCoverage2"
 *            Bits 64-95 of the coverage bitmap.
 * @param     "TUint aCoverage3"
 *            Bits 96-127 of the coverage bitmap.
 */
inline void TOpenFontFaceAttribBase::SetCoverage(TUint aCoverage0,TUint aCoverage1,TUint aCoverage2,TUint aCoverage3)
	{
	iCoverage[0] = aCoverage0;
	iCoverage[1] = aCoverage1;
	iCoverage[2] = aCoverage2;
	iCoverage[3] = aCoverage3;
	}

/**
 *
 * Set the minimum typeface size.
 *
 * This is the smallest size that can be drawn legibly.
 *
 * @param     "TInt aSize"
 *            Sets the minimum typeface size (in pixels).
 */
inline void TOpenFontFaceAttrib::SetMinSizeInPixels(TInt aSize)
	{
	iMinSizeInPixels = aSize;
	}

/**
 *
 * Equality operator.
 *
 * Compares this and a specified set of font attributes for equality.
 *
 * @param     "const TOpenFontFaceAttrib& aAttrib"
 *            The font attributes to compare.
 * @returns   "TBool"
 *            <code>ETrue</code> if the values are equal.
 */
inline TBool TOpenFontFaceAttrib::operator==(const TOpenFontFaceAttrib& aAttrib) const
	{
	return TOpenFontFaceAttribBase::operator==(aAttrib) &&
		   iFamilyName == aAttrib.iFamilyName &&
		   iLocalFullName == aAttrib.iLocalFullName &&
		   iLocalFamilyName == aAttrib.iLocalFamilyName &&
		   iMinSizeInPixels == aAttrib.iMinSizeInPixels;
	}

/**
 *
 * Sets the bold attribute.
 *
 * @param     "TBool aBold"
 *            The bold attribute takes this value -
 *            <code>ETrue</code> or <code>EFalse</code>.
 */
inline void TOpenFontFaceAttribBase::SetBold(TBool aBold)
	{
	if (aBold)
		iStyle |= EBold;
	else
		iStyle &= ~EBold;
	}

/**
 *
 * Sets the italic attribute.
 *
 * @param     "TBool aItalic"
 *            The italic attribute takes this value -
 *            <code>ETrue</code> or <code>EFalse</code>.
 */
inline void TOpenFontFaceAttribBase::SetItalic(TBool aItalic)
	{
	if (aItalic)
		iStyle |= EItalic;
	else
		iStyle &= ~EItalic;
	}

/**
 *
 * Sets the serif attribute.
 *
 * @param     "TBool aSerif"
 *            The serif attribute takes this value -
 *            <code>ETrue</code> or <code>EFalse</code>.
 */
inline void TOpenFontFaceAttribBase::SetSerif(TBool aSerif)
	{
	if (aSerif)
		iStyle |= ESerif;
	else
		iStyle &= ~ESerif;
	}

/**
 *
 * Sets the mono-width attribute.
 *
 * @param     "TBool aMonoWidth"
 *            The mono-width attribute takes this value -
 *            <code>ETrue</code> or <code>EFalse</code>.
 */
inline void TOpenFontFaceAttribBase::SetMonoWidth(TBool aMonoWidth)
	{
	if (aMonoWidth)
		iStyle |= EMonoWidth;
	else
		iStyle &= ~EMonoWidth;
	}

/**
 *
 * Equality operator.
 *
 * Compares this and a specified set of font attributes for equality.
 *
 * @param     "const TOpenFontFaceAttribBase& aAttrib"
 *            The font attributes to compare. This is an object of
 *            <code>TOpenFontFaceAttribBase</code> or derived class.
 * @returns   "TBool"
 *            <code>ETrue</code> if the values are equal, <code>EFalse</code> otherwise.
 */
inline TBool TOpenFontFaceAttribBase::operator==(const TOpenFontFaceAttribBase& aAttrib) const
	{
	return iStyle == aAttrib.iStyle &&
		   iCoverage[0] == aAttrib.iCoverage[0] &&
		   iCoverage[1] == aAttrib.iCoverage[1] &&
		   iCoverage[2] == aAttrib.iCoverage[2] &&
		   iCoverage[3] == aAttrib.iCoverage[3] &&
		   iName.CompareF(aAttrib.iName) == 0;
	}

/**
 *
 * Equality operator.
 *
 * @param     "const TOpenFontSpec& aFontSpec"
 *            The font specification to compare against.
 * @returns   "TBool"
 *            <code>ETrue</code> if equal, <code>EFalse</code> otherwise.
 */
inline TBool TOpenFontSpec::operator==(const TOpenFontSpec& aFontSpec) const
	{
	return TOpenFontFaceAttribBase::operator==(aFontSpec) &&
		   iHeight == aFontSpec.iHeight &&
		   iWidthFactor == aFontSpec.iWidthFactor &&
		   iSlantFactor == aFontSpec.iSlantFactor &&
		   iBitmapType == aFontSpec.iBitmapType &&
		   iEffects == aFontSpec.iEffects &&
		   iSymbol == aFontSpec.iSymbol &&
		   iPrintPosition == aFontSpec.iPrintPosition;
	}

/**
 *
 * Gets the height of the font.
 *
 * @returns   "TInt"
 *            The height of the font, in pixels or twips.
 */
inline TInt TOpenFontSpec::Height() const
	{
	return iHeight;
	}

/**
 *
 * Gets the algorithmic width factor.
 *
 * @returns   "TInt32"
 *            The algorithmic width factor as a 16.16 fixed-point
 *            number.
 */
inline TInt32 TOpenFontSpec::WidthFactor() const
	{
	return iWidthFactor;
	}

/**
 *
 * Gets the algorithmic slant factor.
 *
 * @returns   "TInt32"
 *            The algorithmic slant factor as a 16.16 fixed-point
 *            number.
 */
inline TInt32 TOpenFontSpec::SlantFactor() const
	{
	return iSlantFactor;
	}

/**
 *
 * Gets the glyph bitmap type.
 *
 * @returns   "TGlyphBitmapType"
 *            The type of bitmap being used when rendering characters.
 */
inline TGlyphBitmapType TOpenFontSpec::BitmapType() const
	{
	return (TGlyphBitmapType)iBitmapType;
	}

/**
 *
 * Gets the algorithmic effects flags.
 *
 * This is the logical ORing of values in this class's anonymous enum -
 * e.g. <code>EAlgorithmicBold</code>.
 *
 * @returns   "TUint32"
 *            The effects flags.
 */
inline TUint32 TOpenFontSpec::Effects() const
	{
	return iEffects;
	}

/**
 *
 * Gets the print position.
 *
 * @returns   "TFontPrintPosition"
 *            The print position.
 */
inline TFontPrintPosition TOpenFontSpec::PrintPosition() const
	{
	return iPrintPosition;
	}

/**
 *
 * Sets the font's height.
 *
 * @param     "TInt aHeight"
 *            The font's height, in pixels or twips.
 */
inline void TOpenFontSpec::SetHeight(TInt aHeight)
	{
	iHeight = aHeight;
	}

/**
 *
 * Sets the algorithmic width factor.
 *
 * The width factor is multiplied by the pixel's x position to get the
 * new position, causing characters to become wider or narrower. A width
 * factor of 1 (65536 in 16.16 fixed-point number format) should be used
 * if the character width is not to be changed.
 *
 * @param     "TInt32 aWidthFactor"
 *            The algorithmic width factor as a 16.16 fixed-point
 *            number.
 */
inline void TOpenFontSpec::SetWidthFactor(TInt32 aWidthFactor)
	{
	iWidthFactor = aWidthFactor;
	}

/**
 *
 * Sets the algorithmic slant factor.
 *
 * Note:The slant factor is used to create an italic effect for
 * characters which do not have an italic glyph in the typeface. When
 * slanting is active, pixel x co-ordinates are shifted by a factor
 * relative to the y co-ordinate (i.e. x = x + y - slant factor).The
 * slant factor is a 32 bit, 16.16 fixed-point number. This means that
 * the first 16 bits are treated as a whole number, and the second 16 as
 * the fractional part. e.g. if <code>aSlantFactor</code>=0, there is no
 * slant. If <code>aSlantFactor</code>=65536 this is equivalent to an
 * integer slant value of 1, which causes a 45 degree slant on the
 * character.
 *
 * @param     "TInt32 aSlantFactor"
 *            The slant factor as a 16.16 fixed-point number.
 */
inline void TOpenFontSpec::SetSlantFactor(TInt32 aSlantFactor)
	{
	iSlantFactor = aSlantFactor;
	}

/**
 *
 * Sets the glyph bitmap type to use when rendering characters.
 *
 * @param     "TGlyphBitmapType aBitmapType"
 *            The bitmap type to use.
 */
inline void TOpenFontSpec::SetBitmapType(TGlyphBitmapType aBitmapType)
	{
	iBitmapType = aBitmapType;
	}

/**
 *
 * Sets the effects flags.
 *
 * The flags are the logical ORing of values in this class's anonymous
 * enum - e.g. <code>EAlgorithmicBold</code>.
 *
 * @param     "TUint32 aEffects"
 *            The effects flags.
 */
inline void TOpenFontSpec::SetEffects(TUint32 aEffects)
	{
	iEffects = aEffects;
	}

/**
 *
 * Gets the font file's UID.
 *
 * @returns   "TUid"
 *            The uid of the file.
 */
inline TUid COpenFontFile::Uid() const
	{
	return iUid;
	}

/**
 *
 * Gets the full path and filename of the font fileThis is the filename
 * that was passed to the constructor when the object is created.
 *
 * @returns   "TDesC&"
 *            The filename of the font file.
 */
inline const TDesC& COpenFontFile::FileName() const
	{
	return iFileName;
	}

/**
 *
 * Gets the typeface at a specified index in the typeface attribute
 * array.
 *
 * @param     "TInt aFaceIndex"
 *            The index of the typeface for which the attributes are
 *            required.
 * @returns   "TOpenFontFaceAttrib&"
 *            The attributes of the typeface with the specified
 *            index.
 */
inline const TOpenFontFaceAttrib& COpenFontFile::FaceAttrib(TInt aFaceIndex) const
	{
	return iFaceAttrib[aFaceIndex];
	}

/**
 *
 * Gets the number of typefaces in the typeface attributes array.
 *
 * This is the number of typefaces in the font file - the attributes
 * for each typeface should be loaded into the array when the derived
 * object is constructed.
 *
 * @returns   "TInt"
 *            The number of typefaces in the font file.
 */
inline TInt COpenFontFile::FaceCount() const
	{
	return iFaceAttrib.Count();
	}

/**
 *
 * Increments the reference count by one.
 *
 */
inline void COpenFontFile::IncRefCount()
	{
	iRefCount++;
	}

/**
 *
 * Decrement the reference count by one.
 *
 * The function will reduce the reference count below zero, but will
 * return <code>EFalse</code> for values below zero.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the decrement was successful,
 *            <code>EFalse</code> if the reference count decreased
 *            to zero.
 */
inline TBool COpenFontFile::DecRefCount()
	{
	iRefCount--;
	return iRefCount <= 0;
	}

/**
 *
 * Default constructor.
 *
 */
inline COpenFontRasterizerContext::COpenFontRasterizerContext():
	iGlyphData(NULL)
	{
	}

/**
 *
 * Start writing the glyph data.
 *
 * Use this function to initialise the buffer to which the glyph bitmap
 * is to be written. Call <code>WriteGlyphBit()</code> to add bits to the
 * buffer.
 *
 * @param     "TOpenFontGlyphData* aGlyphData"
 *            A pointer to the glyph data.
 */
inline void COpenFontRasterizerContext::StartGlyph(TOpenFontGlyphData* aGlyphData)
	{
	aGlyphData->SetPointersToInternalBuffers();
	iGlyphData = aGlyphData;
	iGlyphDataStart = iGlyphDataPtr = aGlyphData->BufferStart();
	// Allow 4 extra bytes; BITGDI requires this.
	iGlyphDataEnd = aGlyphData->BufferEnd() - 4;
	iGlyphBit = 1;
	*iGlyphDataPtr = 0;
	iBytesNeeded = 1;
	iOverflow = FALSE;
	}

/**
 *
 * Writes a bit to the glyph buffer.
 *
 * Before calling this function you should first call
 * <code>StartGlyph()</code>.
 *
 * @param     "TInt aBit"
 *            The bit to be added to the buffer.
 */
inline void COpenFontRasterizerContext::WriteGlyphBit(TInt aBit)
	{
	if (aBit && !iOverflow)
		*iGlyphDataPtr |= iGlyphBit;
	iGlyphBit <<= 1;
	if (iGlyphBit == 256)
		{
		iGlyphBit = 1;
		iBytesNeeded++;
		if (++iGlyphDataPtr < iGlyphDataEnd)
			*iGlyphDataPtr = 0;
		else
			iOverflow = TRUE;
		}
	}

/**
 *
 * Writes a byte to the glyph buffer.
 *
 * Before calling this function you should first call
 * <code>StartGlyph()</code>.
 *
 * @param     "TInt aByte"
 *            The byte to be added to the buffer.
 */
inline void COpenFontRasterizerContext::WriteGlyphByte(TInt aByte)
	{
	if (iGlyphDataPtr < iGlyphDataEnd)
		*iGlyphDataPtr++ = (TUint8)aByte;
	else
		iOverflow = TRUE;
	iBytesNeeded++;
	}

/**
 *
 * Completes writing glyph data.
 *
 * Use this function to complete writing the glyph bitmap to the buffer.
 * Call it after adding all necessary bits using
 * <code>WriteGlyphBit()</code>.
 *
 */
inline void COpenFontRasterizerContext::EndGlyph()
	{
	// Add 4 bytes to the data size; some BITGDI functions require this.
	iGlyphData->SetBytesNeeded(iBytesNeeded + 4);
	iGlyphData = NULL;
	}

/**
 *
 * Tests whether the bitmap buffer is large enough to hold the bitmap.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the bitmap will overflow its
 *            buffer, otherwise <code>EFalse</code>.
 */
inline TBool TOpenFontGlyphData::Overflow() const
	{
	return iBytesNeeded > iBitmapBufferSize;
	}

/**
 *
 * Gets the number of bytes needed to store the glyph bitmap.
 *
 * @returns   "TInt"
 *            The number of bytes needed to store the glyph bitmap.
 */
inline TInt TOpenFontGlyphData::BytesNeeded() const
	{
	return iBytesNeeded;
	}

/**
 *
 * Gets a constant pointer descriptor containing the bitmap this object
 * represents.
 *
 *
 *
 * @returns   "TPtrC8"
 *            Pointer descriptor for the glyph.
 */
inline TPtrC8 TOpenFontGlyphData::Bitmap() const
	{
	return TPtrC8(iBitmap,iBytesNeeded);
	}

/**
 *
 * Gets a pointer to the bitmap.
 *
 * This points either to the buffer used to write the bitmap when it is
 * first rasterized, or to the cache if the character was already
 * rasterized.
 *
 * @returns   "TUint8*"
 *            A pointer to the bitmap.
 */
inline const TUint8* TOpenFontGlyphData::BitmapPointer() const
	{
	return iBitmap;
	}

/**
 *
 * Gets the character's metrics.
 *
 * @returns   "TOpenFontCharMetrics*"
 *            The character's open font metrics.
 */
inline const TOpenFontCharMetrics* TOpenFontGlyphData::Metrics() const
	{
	return iMetrics;
	}

/**
 *
 * Gets a pointer to the start of the bitmap buffer.
 *
 * @returns   "TUint8*"
 *            A pointer to the start of the bitmap buffer.
 */
inline TUint8* TOpenFontGlyphData::BufferStart()
	{
	return iBitmapBuffer;
	}

/**
 *
 * Gets a pointer to the end of the bitmap buffer.
 *
 * @returns   "TUint8*"
 *            A pointer to the end of the bitmap buffer.
 */
inline TUint8* TOpenFontGlyphData::BufferEnd()
	{
	return iBitmapBuffer + iBitmapBufferSize;
	}

/**
 *
 * Sets the number of bytes needed to store the glyph bitmap.
 *
 * @param     "TInt aBytes"
 *            The number of bytes needed to store the glyph bitmap.
 */
inline void TOpenFontGlyphData::SetBytesNeeded(TInt aBytes)
	{
	iBytesNeeded = aBytes;
	}

/**
 *
 * Sets the pointer to the bitmap buffer.
 *
 * @param     "const TUint8* aBitmap"
 *            The pointer to the bitmap buffer.
 */
inline void TOpenFontGlyphData::SetBitmapPointer(const TUint8* aBitmap)
	{
	iBitmap = aBitmap;
	}

/**
 *
 * Sets the character's metrics, passing a pointer to a
 * <code>TOpenFontCharMetrics</code> object.
 *
 * @param     "const TOpenFontCharMetrics* aMetrics"
 *
 */
inline void TOpenFontGlyphData::SetMetricsPointer(const TOpenFontCharMetrics* aMetrics)
	{
	iMetrics = aMetrics;
	}

/**
 *
 * Sets the bitmap and metrics pointers to point to the internal buffers.
 *
 * The alternative is that the pointers point to the cache of metrics and
 * bitmaps that have already been rasterized.
 *
 */
inline void TOpenFontGlyphData::SetPointersToInternalBuffers()
	{
	iBitmap = iBitmapBuffer;
	iMetrics = &iMetricsBuffer;
	}

/**
 *
 * Sets the character's metrics, passing a reference to a
 * <code>TOpenFontCharMetrics</code> object.
 *
 * @param     "TOpenFontCharMetrics& aMetrics"
 *            The character's open font character metrics.
 */
inline void TOpenFontGlyphData::SetMetrics(TOpenFontCharMetrics& aMetrics)
	{
	iMetricsBuffer = aMetrics;
	iMetrics = &iMetricsBuffer;
	}

/**
 *
 * Sets the glyph index.
 *
 * @since     6.0
 * @param     "TInt aGlyphIndex"
 *            The glyph index.
 */
inline void TOpenFontGlyphData::SetGlyphIndex(TInt aGlyphIndex)
	{
	iGlyphIndex = aGlyphIndex;
	}

#endif // __OPENFONT_H__
