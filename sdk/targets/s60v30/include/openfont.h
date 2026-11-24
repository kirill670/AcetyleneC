// OPENFONT.H
//
// Copyright (c) 1998-2005 Symbian Software Ltd. All rights reserved.
//

/*
A header for the open font system, which allows
EPOC32 to use fonts of arbitrary types, including TrueType
and other outline font formats.
*/

#ifndef __OPENFONT_H__
#define __OPENFONT_H__

#ifdef SYMBIAN_REMOVE_FONT_METRICS_V1
#undef SYMBIAN_HIDE_FONT_METRICS_V1
#define SYMBIAN_HIDE_FONT_METRICS_V1	// forcibly hide the API
#undef SYMBIAN_SUPPORT_FONT_METRICS_V1	// forcibly turn of support
#endif

#ifdef SYMBIAN_SUPPORT_FONT_METRICS_V1
#undef SYMBIAN_HIDE_FONT_METRICS_V1
#endif

#include <e32base.h>
#include <gdi.h>
#include <Ecom/Ecom.h>

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
class CFontStore;
class TOpenFontFileData;

/**

The OpenFont ECOM Plug-in Interface Definition UID. 

@internalTechnology
*/
const TInt KUidOpenFontRasterizerPlunginInterface = 0x101F7F5D;

/** 
Replacement character code. 

This is a Unicode private use area codepoint, which is reserved in the Symbian 
OS to represent characters for which a glyph does not exist in a font (either 
a bitmap or scalable font). If a glyph exists in a font with this character 
code, it will be used for nonexistent characters, otherwise, the rasterizer's 
default replacement character glyph will be used. For example, TrueType fonts 
return glyph index 0 for nonexistent characters, and that is usually mapped 
to an empty rectangle.
@internalTechnology
*/
const TUint KReplacementCharacter = 0xF6DB;

/** 
KFillCharacterOffset is a significant offset that is set when a character within a code section is 
not in the font. This means that for these fill characters nothing is stored within the binary
data part of the code section.
@internalTechnology
*/
const TInt KFillCharacterOffset = 0x7FFF;

/** 
Font metrics.

@see CFbsFont::GetFontMetrics()
@publishedAll
@released
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
	TInt16 iDesignHeight;	// size of the font ('pointsize' in pixels)
	TInt16 iAscent;			// typographic ascent
	TInt16 iDescent;		// typographic descent
	TInt16 iMaxHeight;		// maximum height of a character; may be greater than iAscent
	TInt16 iMaxDepth;		// maximum depth of a character; may be greater than iDescent
	TInt16 iMaxWidth;		// maximum width of a character
	TInt32 iReserved;
	};

 
/** 
Character metrics  includes more information than TCharacterMetrics.

Character metrics allow characters to be placed horizontally or vertically. 
The character metrics encapsulated by this class are: Height, Width, Horizontal 
Bearing X, Horizontal Bearing Y, Horizontal Advance, Vertical Bearing X, 
Vertical Bearing Y, and Vertical Advance. Their meanings are described in the 
associated setter and getter functions.

Note : 

Vertical drawing (in the sense of characters drawn with horizontal baselines, 
but in a vertical line) is not yet supported by Symbian OS.

@see CFont::GetCharacterData()
@see CFbsFont::GetCharacterData() 
@publishedAll
@released
*/
class TOpenFontCharMetrics
	{
public:
	enum TUninitialized { EUninitialized };
public:
	inline TOpenFontCharMetrics();
 
	/** Default C++ constructor. 
	
	The constructor initialises all data members to zero. As for other T classes, 
	there is no need to explicitly cleanup TOpenFontCharMetrics objects. */
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
Font glyph data.

Objects of this type are used by rasterizers to supply glyph data to font 
and bitmap server clients. Unless you are writing a rasterizer you will not 
need to use an object of this type.

The object cannot be constructed and destroyed by normal means. It resides 
on a specified heap. It is created by New() and deleted by RHeap::Free().

@see COpenFont::RasterizeL()
@publishedAll
@released
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
	Prevent construction and destruction by normal means; the object resides 
	on a specified heap and is created by New and deleted by RHeap::Free.
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
Open Font System font abstract base class.

Derive a class from this class to represent an instance of a typeface at a 
particular size, provide bitmaps of the glyphs, and determine whether 
characters exist in the typeface.

Writing derived classes construction: 

You must call the constructor of this class when creating your derived object, 
passing the arguments aHeap and aSessionCacheList supplied to 
COpenFontFile::GetNearestFontInPixelsL(), and the address of the COpenFontFile 
object that creates the object as aFile.

The derived object must be created on the shared heap aHeap because it is 
shared by several processes: the font and bitmap server and its clients. 
To do this, use aHeap->AllocL() to obtain memory, then construct in place 
using a placement argument to new.

Devived classes must implement the pure virtual function RasterizeL(). 
Information about this function is provided in the function definition below. 

Information about deriving from this class is also provided in the API guide.

@see COpenFontFile::GetNearestFontInPixelsL()
@publishedAll
@released
*/
class COpenFont: public CBase
	{
public:
	/** Creates a bitmap for the specified Unicode character.
	
	Implementations of this function should put the bitmap in 
	aGlyphData->iBitmapBuffer, and the character metrics are placed in 
	aGlyphData->iMetricsBuffer. The other parts of aGlyphData should be left 
	alone. 
	
	There are a number of strategies for achieving this, e.g. pass the 
	rasterization task all the way up to the rasterizer engine. These are 
	discussed in the API quide.
	
	At present you must write the bitmap in the Symbian platform's 
	run-length-encoded format. This is a packed binary format starting on a 
	byte boundary and made up of a number of sections. Each section starts 
	with a five-bit header. If the first bit of the header is 0 the next four 
	bits are a repeat count, starting with the least significant bit, and a 
	single row of bits (the number of bits in a row is specified by 
	aGlyphData->iMetricsBuffer.Width()) follows. If the first bit of the header 
	is 1 the next four bits are a count of non-repeating rows, again starting 
	with the least significant bit, and that many rows of bits follow.
	
	@param aCode The character code of the Unicode character for which the 
	bitmap is required.
	@param aGlyphData On return, contains a pointer to a TOpenFontGlyphData 
	containing the character's bitmap and metrics. */
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
	inline TInt FontCapitalAscent() const;
	inline TInt FontMaxAscent() const;
	inline TInt FontStandardDescent() const;
	inline TInt FontMaxDescent() const;
	inline TInt FontLineGap() const;
	inline TInt FontMaxHeight() const;
protected:
	RHeap* iHeap;
	TOpenFontMetrics iMetrics;
	const COpenFontPositioner* iPositioner;					// The character positioning information; owned by the
															// file, but placed in shared memory and accessed
															// from the client side, so cannot be accessed via iFile
	/** The positive distance in pixels from the baseline to
		the top of an ANSI capital (whether or not there are
		ANSI capitals in the font) */
	TInt iFontCapitalAscent;								
	/** The positive distance in pixels from the baseline to
		the top of the highest pre-composed glyph in the font */
	TInt iFontMaxAscent;									
	/** The positive distance in pixels from the baseline to
		the bottom of the lowest ANSI descender (whether or
		not there are ANSI chars in the font)*/
	TInt iFontStandardDescent;								
	/** The positive distance in pixels from the baseline to
		the bottom of the lowest pre-composed glyph in the font */
	TInt iFontMaxDescent;									
	/** The recommended baseline to baseline gap for successive
		lines of text in the font */
	TInt iFontLineGap;										
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
Font attribute base class. 

This class is not intended for user derivation.

@see TOpenFontFaceAttrib
@see TOpenFontSpec
@publishedAll
@released
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
Typeface attributes.

These attributes include the name, family name, and supported scripts.

@see CFbsFont::GetFaceAttrib()
@publishedAll
@released
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
Font specification allowing more attributes to be specified than TFontSpec.

In addition to the attributes specified by TFontSpec, this font specification 
allows stretching and slanting in the x dimension, and other algorithmic effects. 
This is used to correct for non-square pixels, and to allow algorithmic slanting 
and bold. The width factor and slant factor transform any point (x,y) to (x 
* iWidthFactor + y * iSlantFactor,y). The width and slant factors are 16.16 
fixed-point numbers.

The font specification also provides access to information about the scripts 
which are supported by the font. This information is not always reliable, 
because it may be incorrectly specified, or not specified at all, by some 
font manufacturers. 
@publishedAll
@released
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
	IMPORT_C void CompensateForAspectRatio(TInt aPixelWidth,TInt aPixelHeight);
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
	IMPORT_C void SetEffects(FontEffect::TEffect aEffect, TBool aOn);
	IMPORT_C TBool IsEffectOn(FontEffect::TEffect aEffect) const;
	static TBool IsCompensationForAspectRatioNeeded(TInt aPixelWidth, TInt aPixelHeight, TReal& aRatio);

	/** Algorithmic effects flags.

 	These can be combined using an OR operation.
	@publishedPartner For use by system/UI software.
	@deprecated Use FontEffect::TEffect instead.
	*/
	enum
		{
		/** Font is algorithmic bold. */
		EAlgorithmicBold = 1,
		/** Font has a drop shadow. */
		EDropShadow = 2,
		/** Font is an outline font. */
		EOutline = 4
		};
private:
	TInt iHeight;						// em height
	TInt32 iWidthFactor;				// algorithmic width factor as a 16.16 fixed-point number
	TInt32 iSlantFactor;				// algorithmic slant factor as a 16.16 fixed-point number
	TInt iBitmapType;					// non-anti-aliased, standard anti-aliased, etc.; zero means 'default'
	TUint32 iEffects;					// bit flags for font effects

	// The following data members exist only to allow round-trip conversion between TFontSpec and TOpenFontSpec
	TBool iSymbol;						// specifies a symbol font as understood by TFontSpec
	TFontPrintPosition iPrintPosition;	// normal, superscript or subscript

	TInt iReserved2;
	};

/**
Constants for attachment points for diacritics.
@internalComponent
*/
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
Font file abstract base class.

Write a class derived from COpenFontFile to manage a file with the font format 
supported by your DLL. The derived class must implement the virtual 
GetNearestFontInPixelsL() function. This function takes a font description 
and creates a COpenFont derived object if the description matches a typeface 
contained in the font file.

Derived classes must also load typeface attributes from the file into the 
protected typeface attribute array during construction. This array is what 
is searched when getting font attribute information see AddFaceL(), 
GetNearestFontHelper().

Writing derived classes  construction:

Call the COpenFontFile constructor in the constructor for your derived object, 
passing it aUid and aFileName arguments. These values are the arguments passed 
when the constructor is called by COpenFontRasterizer::NewFontFileL().

A file may contain one or more typefaces. During construction the derived 
object should extract the information for each typeface and add it to this 
object's protected typeface attribute array see AddFaceL(). This process 
will probably leave under some conditions. It should therefore be implemented 
in a second phase constructor.

Writing derived classes  implement the pure virtual functions:

Derived classes must also implement the two pure virtual functions 
GetNearestFontInPixelsL() and HasUnicodeCharacterL(). Information about 
these functions is provided in the definitions below. Information about 
deriving from this class is also provided in the API guide. 

@see COpenFontRasterizer::NewFontFileL()
@see CWsScreenDevice::AddFile()
@publishedAll
@released
*/
class COpenFontFile: public CBase
	{
public:
#ifndef SYMBIAN_HIDE_FONT_METRICS_V1
	virtual void GetNearestFontInPixelsL(RHeap* aHeap, COpenFontSessionCacheList* aSessionCacheList,
										 const TOpenFontSpec& aDesiredFontSpec, TInt aPixelWidth, TInt aPixelHeight,
										 COpenFont*& aFont, TOpenFontSpec& aActualFontSpec) = 0;
#endif
	virtual void GetNearestFontToDesignHeightInPixelsL(RHeap* /*aHeap*/, COpenFontSessionCacheList* /*aSessionCacheList*/,
													   const TOpenFontSpec& /*aDesiredFontSpec*/, TInt /*aPixelWidth*/, TInt /*aPixelHeight*/,
													   COpenFont*& /*aFont*/, TOpenFontSpec& /*aActualFontSpec*/){}
	virtual void GetNearestFontToMaxHeightInPixelsL(RHeap* /*aHeap*/, COpenFontSessionCacheList* /*aSessionCacheList*/,
													const TOpenFontSpec& /*aDesiredFontSpec*/, TInt /*aPixelWidth*/, TInt /*aPixelHeight*/,
													 COpenFont*& /*aFont*/, TOpenFontSpec& /*aActualFontSpec*/, TInt /*aMaxHeight*/){}

	/** Tests whether a specified typeface contains a particular character.
	
	@param aFaceIndex The index of the typeface to be tested.
	@param aCode The Unicode character code for the character to be tested. 
	@return ETrue if the typeface contains aCode, otherwise EFalse. */
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
#ifndef SYMBIAN_HIDE_FONT_METRICS_V1
	TInt GetNearestFontInPixels(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,
								const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
								COpenFont*& aFont,TOpenFontSpec& aActualFontSpec);
#endif
	TInt GetNearestFontToDesignHeightInPixels(RHeap* aHeap, COpenFontSessionCacheList* aSessionCacheList,
											  const TOpenFontSpec& aDesiredFontSpec, TInt aPixelWidth, TInt aPixelHeight,
											  COpenFont*& aFont, TOpenFontSpec& aActualFontSpec);
	TInt GetNearestFontToMaxHeightInPixels(RHeap* aHeap, COpenFontSessionCacheList* aSessionCacheList,
										   const TOpenFontSpec& aDesiredFontSpec, TInt aPixelWidth, TInt aPixelHeight,
										   COpenFont*& aFont, TOpenFontSpec& aActualFontSpec, TInt aMaxHeight);
	void RemoveFontFromList(const COpenFont* aFont);
	void SetFontStoreL(CFontStore* aFontStore);
protected:
	IMPORT_C TBool GetNearestFontHelperOld(const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
										TInt& aFaceIndex,TOpenFontSpec& aActualFontSpec) const;
private:
	// A class to contain the public font attributes and private positioning information (for kerning, ligatures, etc.)
	class TAttrib: public TOpenFontFaceAttrib
		{
		public:
		COpenFontPositioner* iPositioner;	// if non-null, positioning information for the typeface
		};
	static TInt ScoreByName(const TOpenFontSpec& aDesiredFontSpec, const TAttrib& aAttrib);
	static TInt ScoreByStyle(const TOpenFontSpec& aDesiredFontSpec, const TAttrib& aAttrib, const TOpenFontFileData* aOpenFontFileData);
private:
	CArrayFixFlat<TAttrib> iFaceAttrib;
	TUid iUid;
	TBuf<KMaxFileName> iFileName;
	TInt iRefCount;
	CArrayPtrFlat<COpenFont> iFontList;
	TOpenFontFileData* iData;
	};

 
/** 
The Open Font rasterizer plug-in Interface Definition class. 

This interface allows the implementation of an Open Font rasterizer plug-in,
which can then be dynamically loaded at run time by the ECOM plug-in framework. 
The plug-in implementation is instantiated by calling NewL(), passing the implementation 
UID so that ECOM can instantiate the correct implementation. 

The rasterizer interface declares a single pure virtual functions, which the 
plug-in derived from this interface must implement. The function reads font files, and creates 
a COpenFontFile object if the font file is of the right type.

Writing derived classes:

Open font rasterizers should derive from this class and implement the 
NewFontFileL() function.

Derived classes should also define the factory function. It is a static function 
which takes no arguments. It creates a COpenFontRasterizer derived object on the heap, and returns it 
to the caller. This factory function, together with the implementation UID will form 
the TImplementationProxy used by the ECOM framework to instatiate the plug-in. 

The rasterizer class may also need to store an 'engine context'. This is an 
object derived from COpenFontRasterizerContext, which provides functions that 
make it easier to write the glyph bitmap during rasterization.


@publishedAll
@released
*/
class COpenFontRasterizer: public CBase
	{
public:
 	/** Creates a COpenFontFile derived object for loading font files in the 
 	new format. 
		
	This function is called by the framework during font and bitmap server 
	startup. It creates a font file object for font files in the \\resource\\fonts 
	directory on all drives, using the default search path. The first font of 
	a given name overrides subsequent ones. The directory search path is soft 
	to hard: Y:, X:, W:, ..., C:, B:, A:, Z:. Files may also be added 
	dynamically after startup using CWsScreenDevice::AddFile(), which 
	indirectly calls this function.
	
	Implementations of this function should examine the file aFileName, and if 
	it is of the correct type attempt to create a COpenFontFile derived object 
	to load it. The caller is responsible for deleting the object. The function 
	must return NULL if it cannot recognise the file, and it may also leave if 
	there is an error. 
	
	@param aUid An ID to be used for the file. UIDs are required by the font 
	framework, so the font store allocates them for non Symbian OS-native font 
	files. This ID persists until the font is unloaded, e.g. if the device is 
	rebooted.
	@param aFileName The full path and filename of the file from which the 
	COpenFontFile object is created, if the file is the correct type.
	@param aFileSession The file session owned by the Font and Bitmap server. 
	This file session should be used for any file access. If COpenFontFile 
	objects need to keep files open, aFileSession should be stored in a place 
	that is accessible to them. 
	@return A pointer to a new COpenFontFile derived object, or NULL if the 
	file type is not recognised.
	@see CWsScreenDevice::AddFile() */
	virtual COpenFontFile* NewFontFileL(TInt aUid,const TDesC& aFileName,RFs& aFileSession) = 0;
	inline static COpenFontRasterizer* NewL(TUid aInterfaceImplUid);
	inline virtual ~COpenFontRasterizer();
	IMPORT_C virtual void Reserved(); // unused; for future expansion
private:
	TUid iDtor_ID_Key;//ECOM identifier used during destruction
	};

 
/** 
Convenience class from which rasterizer contexts may be derived.

A rasterizer context object may (optionally) be created to provide the link 
between the rasterizer DLL code supported by the Open Font System, and the 
rasterizer engine code. A rasterizer context object class should get the 
requested bitmap from the associated rasterizer engine. It should then convert 
this into Symbian run-length-encoded format. This class contains convenience 
functions to make the conversion easier.

Deriving from this class is described in greater detail in the API guide.
@publishedAll
@released
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
/** Default C++ constructor.
	
This creates then zero fills the object. */
inline TOpenFontMetrics::TOpenFontMetrics()
	{
	Mem::FillZ(this,sizeof(*this));
	}

/** Gets the font's size.
	
@return The font's size. 
@see SetSize() */
inline TInt TOpenFontMetrics::Size() const
	{
	return iDesignHeight;
	}
 
/** Gets the font's ascent.
	
This is the ascent for the Latin character which is highest above the baseline.

@return The font's ascent, in pixels.
@see SetAscent() */
inline TInt TOpenFontMetrics::Ascent() const
	{
	return iAscent;
	}

/** Gets the font's descent.
	
This is the descent for the Latin character in the font which falls furthest below the baseline.
	
@return The font's descent, in pixels. 
@see SetDescent() */
inline TInt TOpenFontMetrics::Descent() const
	{
	return iDescent;
	}
 
/** Sets the font's maximum height.

Note that if this object was initialised from the CFont this will be the same 
as the ascent.

This is the ascent for the character which is highest above the baseline. 
In many fonts this will be the height of an accented character like Â, 
including the accent.
	
@return The maximum height of the font, in pixels.
@see SetMaxDepth() */
inline TInt TOpenFontMetrics::MaxHeight() const
	{
	return iMaxHeight;
	}
 
/** Gets the font's maximum depth.

Note: If this object was initialised from the CFont this will be the same as the 
descent.

This is the descent for the character in the font which falls furthest below 
the baseline.
	
@return The font's maximum depth.
@see SetMaxDepth() */
inline TInt TOpenFontMetrics::MaxDepth() const
	{
	return iMaxDepth;
	}
 
/** Gets the maximum character width, in pixels.
	
@return The maximum character width, in pixels.
@see SetMaxWidth() */
inline TInt TOpenFontMetrics::MaxWidth() const
	{
	return iMaxWidth;
	}
 
/** Sets the font's size.
	
@param aSize The font's size.
@see Size() */
inline void TOpenFontMetrics::SetSize(TInt aSize)
	{
	iDesignHeight = static_cast<TInt16>(aSize);
	}

/** Sets the ascent.
	
@param aAscent The ascent, in pixels.
@see Ascent() */
inline void TOpenFontMetrics::SetAscent(TInt aAscent)
	{
	iAscent = static_cast<TInt16>(aAscent);
	}

/** Sets the descent.
	
@param aDescent The descent, in pixels.
@see Descent() */
inline void TOpenFontMetrics::SetDescent(TInt aDescent)
	{
	iDescent = static_cast<TInt16>(aDescent);
	}
 
/** Sets the font's maximum height.
	
@param aMaxHeight The font's maximum height, in pixels. 
@see MaxHeight() */
inline void TOpenFontMetrics::SetMaxHeight(TInt aMaxHeight)
	{
	iMaxHeight = static_cast<TInt16>(aMaxHeight);
	}
 
/** Sets the font's maximum depth.
	
@param aMaxDepth The font's maximum depth, in pixels.
@see MaxDepth() */
inline void TOpenFontMetrics::SetMaxDepth(TInt aMaxDepth)
	{
	iMaxDepth = static_cast<TInt16>(aMaxDepth);
	}
 
/** Sets the maximum character width, in pixels.
	
@param aMaxWidth The maximum character width, in pixels.
@see MaxWidth() */
inline void TOpenFontMetrics::SetMaxWidth(TInt aMaxWidth)
	{
	iMaxWidth = static_cast<TInt16>(aMaxWidth);
	}
 
/** Default C++ constructor. 
	
The constructor initialises all data members to zero. As for other T classes, 
there is no need to explicitly cleanup TOpenFontCharMetrics objects. */
inline TOpenFontCharMetrics::TOpenFontCharMetrics()
	{
	Mem::FillZ(this,sizeof(*this));
	}
	
/** Gets the width of the character's bitmap.
	
@return The width of the bitmap in pixels. */
inline TInt TOpenFontCharMetrics::Width() const
	{
	return iWidth;
	}
 
/** Gets the height of the character's bitmap.
	
@return The character's height in pixels. */
inline TInt TOpenFontCharMetrics::Height() const
	{
	return iHeight;
	}
 
/** Gets the horizontal bearing X. 
	
This is the distance in pixels from the pen point before the character is 
drawn (the origin) to the left edge of the bitmap, when drawing horizontally. 
A positive value means that the left edge of the bitmap is right of the origin.
	
@return The horizontal bearing X in pixels */
inline TInt TOpenFontCharMetrics::HorizBearingX() const
	{
	return iHorizBearingX;
	}
 
/** Gets horizontal bearing Y.
	
This is the vertical distance in pixels from the pen point before the character 
is drawn (the origin) to the top edge of the bitmap, when drawing horizontally. 
A positive value means that the top edge of the bitmap is above the origin
	
@return The horizontal bearing Y in pixels. */
inline TInt TOpenFontCharMetrics::HorizBearingY() const
	{
	return iHorizBearingY;
	}
 
/** Gets the horizontal advance.
	
This is the amount added to the x co-ordinate of the origin after the character 
is drawn   what most people understand by the width or escapement of a character. 
The origin here is the pen point before the character is drawn. 
	
@return The horizontal advance in pixels */
inline TInt TOpenFontCharMetrics::HorizAdvance() const
	{
	return iHorizAdvance;
	}

/** Gets the vertical bearing X.
	
This is the distance in pixels from the pen point before the character is 
drawn (the origin) to the left edge of the bitmap, when drawing vertically. 
A positive value means that the left edge of the bitmap is right of the origin.
	
@return The vertical bearing X in pixels. */
inline TInt TOpenFontCharMetrics::VertBearingX() const
	{
	return iVertBearingX;
	}
 
/** Gets the vertical bearing Y.
	
This is the distance in pixels from the pen point before the character is 
drawn (the origin) to the top edge of the bitmap, when drawing vertically. 
A positive value means that the top edge of the bitmap is above the origin.
	
@return The vertical bearing Y in pixels. */
inline TInt TOpenFontCharMetrics::VertBearingY() const
	{
	return iVertBearingY;
	}
 
/** Gets the vertical advance.
	
When drawing vertically, this is the amount added to the y co-ordinate of 
the origin after the character is drawn what most people understand by 
the height of a character. The origin here is the pen point before the character 
is drawn.
	
Note: Vertical drawing is not supported in v5.
	
@return The vertical advance in pixels. */
inline TInt TOpenFontCharMetrics::VertAdvance() const
	{
	return iVertAdvance;
	}
 
/** Gets the bounds of the character relative to its origin when setting text 
horizontally.
	
The origin here is the pen point before the character is drawn. 

@param aBounds The character's bounds. */
inline void TOpenFontCharMetrics::GetHorizBounds(TRect& aBounds) const
	{
	aBounds.iTl.iX = iHorizBearingX;
	aBounds.iTl.iY = -iHorizBearingY;
	aBounds.iBr.iX = aBounds.iTl.iX + iWidth;
	aBounds.iBr.iY = aBounds.iTl.iY + iHeight;
	}
 
/** Gets the bounds of the character relative to its origin when setting text 
vertically. 
	
The origin here is the pen point before the character is drawn.
	
@param aBounds The character's bounds. */
inline void TOpenFontCharMetrics::GetVertBounds(TRect& aBounds) const
	{
	aBounds.iTl.iX = -iVertBearingX;
	aBounds.iTl.iY = iVertBearingY;
	aBounds.iBr.iX = aBounds.iTl.iX + iWidth;
	aBounds.iBr.iY = aBounds.iTl.iY + iHeight;
	}
 
/** Sets the width of the character's bitmap.
	
@param aWidth The width of the bitmap in pixels. */
inline void TOpenFontCharMetrics::SetWidth(TInt aWidth)
	{
	iWidth = (TInt16)aWidth;
	}
 
/** Sets the height of the character's bitmap.
	
@param aHeight The character height (in pixels). */
inline void TOpenFontCharMetrics::SetHeight(TInt aHeight)
	{
	iHeight = (TInt16)aHeight;
	}
 
/** Sets the horizontal bearing X.
	
This is the distance in pixels from the pen point before the character is 
drawn (the origin) to the left edge of the bitmap, when drawing horizontally. 
A positive value means that the left edge of the bitmap is right of the origin.
	
@param aHorizBearingX The horizontal bearing X (in pixels). */
inline void TOpenFontCharMetrics::SetHorizBearingX(TInt aHorizBearingX)
	{
	iHorizBearingX = (TInt16)aHorizBearingX;
	}
 
/** Sets the horizontal bearing Y.
	
This is the distance in pixels from the pen point before the character is 
drawn (the origin) to the top edge of the bitmap, when drawing horizontally. 
A positive value means that the top edge of the bitmap is above the origin.
	
@param aHorizBearingY The horizontal bearing Y (in pixels). */
inline void TOpenFontCharMetrics::SetHorizBearingY(TInt aHorizBearingY)
	{
	iHorizBearingY = (TInt16)aHorizBearingY;
	}
 
/** Sets the horizontal advance.
	
This is the amount added to the x co-ordinate of the origin after the character 
is drawn, what most people understand by the width or escapement of a character. 
The origin here is the pen point before the character is drawn.
	
@param aHorizAdvance The horizontal advance (in pixels). */
inline void TOpenFontCharMetrics::SetHorizAdvance(TInt aHorizAdvance)
	{
	iHorizAdvance = (TInt16)aHorizAdvance;
	}
 
/** Set vertical bearing X.
	
This is the distance in pixels from the pen point before the character is 
drawn (the origin) to the left edge of the bitmap, when drawing vertically. 
A positive value means that the left edge of the bitmap is right of the origin.
	
@param aVertBearingX The vertical bearing X (in pixels). */
inline void TOpenFontCharMetrics::SetVertBearingX(TInt aVertBearingX)
	{
	iVertBearingX = (TInt16)aVertBearingX;
	}
 
/** Sets the vertical bearing Y.
	
This is the distance in pixels from the pen point before the character is 
drawn (the origin) to the top edge of the bitmap, when drawing vertically. 
A positive value means that the top edge of the bitmap is above the origin.
	
@param aVertBearingY The vertical bearing Y (in pixels). */
inline void TOpenFontCharMetrics::SetVertBearingY(TInt aVertBearingY)
	{
	iVertBearingY = (TInt16)aVertBearingY;
	}
 
/** Sets the vertical advance.
	
When drawing vertically, this is the amount added to the y co-ordinate of 
the origin after the character is drawn  what most people understand by 
the height of a character. The origin here is the pen point before the character 
is drawn.
	
Note: Vertical drawing is not supported in v5.
	
@param aVertAdvance The vertical advance (in pixels). */
inline void TOpenFontCharMetrics::SetVertAdvance(TInt aVertAdvance)
	{
	iVertAdvance = (TInt16)aVertAdvance;
	}
 
/** Gets the character metrics for this font.
	
@return The character metrics for this font. */
inline const TOpenFontMetrics& COpenFont::Metrics() const
	{
	return iMetrics;
	}

/** Gets the glyph index.
	
This is the index of a particular glyph within the font file.
	
Note: This makes it possible to gain access to glyphs which are not referenced 
by the Unicode character set. However, this feature is not yet supported by 
Symbian OS.
	
@return The glyph index.
@see SetGlyphIndex() */
inline TInt TOpenFontGlyphData::GlyphIndex() const
	{
	return iGlyphIndex;
	}
 
/** Gets the typeface attributes.
	
These are the attributes of the font represented by this object.
	
@return The typeface attributes. */
inline const TOpenFontFaceAttrib* COpenFont::FaceAttrib() const
	{
	return iFile ? &iFile->FaceAttrib(iFaceIndex) : NULL;
	}
 
/** Gets a pointer to the COpenFontFile which created this object.
	
This is the COpenFontFile which owns the file that contains the definition 
of the typeface. It can be used to get information about the typeface, or 
to access the rasterizer context (engine).
	
@return The COpenFontFile which created this object. */
inline COpenFontFile* COpenFont::File() const
	{
	return iFile;
	}
 
/** Gets the index of this typeface within the font file.
	
@return The index of this typeface within the font file. */
inline TInt COpenFont::FaceIndex() const
	{
	return iFaceIndex;
	}
 
/** Tests whether or not a character needs to be rasterized.
	
Characters that have been rasterized are cached  there is no need to regenerate 
the character bitmap. This function should only be called by the Font and 
Bitmap server.
	
@param aSessionHandle A handle to the font and bitmap server session.
@param aCode The code for the Unicode character.
@return ETrue if the character needs to be rasterized, otherwise EFalse. */
inline TBool COpenFont::CharacterNeedsToBeRasterized(TInt aSessionHandle,TInt aCode) const
	{
	return Glyph(aSessionHandle,aCode) == NULL;
	}

/** Gets the ascent of an ANSI capital letter in the font whether or not
there are any ANSI capitals in the font.
@return The positive distance from the font baseline to the top of a
standard ANSI capital letter
@publishedAll
@released
@see AscentInPixels()
*/
inline TInt COpenFont::FontCapitalAscent() const
	{
	return iFontCapitalAscent;
	}

/** Gets the max ascent of any pre-composed glyph in the font. This will
include accents or diacritics that form part of pre-composed glyphs. It is
not guaranteed to cover the max ascent of composite glyphs that have to be
created by a layout engine. This is also the recommended distance between
the top of a text box and the baseline of the first line of text. 
@return The positive distance from the font baseline to the top of the
highest pre-composed glyph (including accents) above the baseline
@publishedAll
@released
@see AscentInPixels()
*/
inline TInt COpenFont::FontMaxAscent() const
	{
	return iFontMaxAscent;
	}

/** Gets the descent of an ANSI descending character in the font.
Whether or not there are any ANSI descenders in the font.
@return The positive distance from the font baseline to the bottom of the
lowest ANSI descender
@publishedAll
@released
@see DescentInPixels()
*/
inline TInt COpenFont::FontStandardDescent() const
	{
	return iFontStandardDescent;
	}

/** Gets the max descent of any pre-composed glyph in the font. This will
include accents or diacritics that form part of pre-composed glyphs. It is
not guaranteed to cover the max descent of composite glyphs that have to be
created by a layout engine.
@return The positive distance from the font baseline to the bottom of the
lowest pre-composed glyph (including accents) below the baseline
@publishedAll
@released
@see DescentInPixels()
*/
inline TInt COpenFont::FontMaxDescent() const
	{
	return iFontMaxDescent;
	}

/** Gets the suggested line gap for the font. This is the recommended
baseline to baseline distance between successive lines of text in the font.
@return The positive recommended gap between successive lines
@publishedAll
@released
*/
inline TInt COpenFont::FontLineGap() const
	{
	return iFontLineGap;
	}
	
/** Gets the maximum height for the font. This is the sum of the max ascent 
of the font and the max descent of the font.
@return The positive maximum height of the font
@publishedAll
@released
@see HeightInPixels()
*/
inline TInt COpenFont::FontMaxHeight() const
	{
	return iFontMaxAscent + iFontMaxDescent;
	}

/** Default C++ constructor.
	
This sets all attribute fields to zero. As for other T classes, there is no 
need to explicitly clean-up objects derived from this class. */
inline TOpenFontFaceAttribBase::TOpenFontFaceAttribBase()
	{
	Mem::FillZ(this,sizeof(*this));
	}
 
/** Default C++ constructor.
	
The function initialises the minimum typeface size to zero, the names to NULL, 
and the coverage and style flags to zero. */
inline TOpenFontFaceAttrib::TOpenFontFaceAttrib():
	iMinSizeInPixels(0),
	iReserved2(0)
	{
	}
 
/** Tests for support of Latin characters.
	
Note: A return value of ETrue implies that the font has a useable set of 
characters. It does not imply exhaustive coverage.
	
@return ETrue if Latin characters are supported */
inline TBool TOpenFontFaceAttribBase::HasLatin() const
	{
	return iCoverage[0] & ELatinSet;
	}
 
/** Tests for support of Greek characters.
	
Note: A return value of ETrue implies that the font has a useable set of 
characters. It does not imply exhaustive coverage.
	
@return ETrue if Greek characters are supported. */
inline TBool TOpenFontFaceAttribBase::HasGreek() const
	{
	return iCoverage[0] & EGreekSet;
	}
 
/** Tests for support of Cyrillic characters.
	
Note: A return value of ETrue implies that the font has a useable set of 
characters. It does not imply exhaustive coverage.
	
@return ETrue if Cyrillic characters are supported. */
inline TBool TOpenFontFaceAttribBase::HasCyrillic() const
	{
	return iCoverage[0] & ECyrillicSet;
	}
 
/** Tests for support of Japanese syllabic characters.
	
This function tests for the presence of Hiragana and Katakana syllabic 
characters in the font, collectively called kana. These characters are not 
sufficient for the Japanese language, which also makes use of Chinese characters.
	
Note: A return value of ETrue implies that the font has a useable set of 
characters. It does not imply exhaustive coverage.
	
@return ETrue if Japanese characters are supported 
@see HasCJK() */
inline TBool TOpenFontFaceAttribBase::HasKana() const
	{
	return iCoverage[1] & EKanaSets;
	}
 
/** Tests for support of Korean Hangul characters.
	
Korean may also make use of Chinese characters.
	
Note: A return value of ETrue implies that the font has a useable set of 
characters. It does not imply exhaustive coverage.
	
@return ETrue if Korean characters are supported 
@see HasCJK() */
inline TBool TOpenFontFaceAttribBase::HasHangul() const
	{
	return iCoverage[1] & EHangulSet;
	}
 
/** Tests for support of Chinese ideographic characters.
	
These are used in Chinese, Japanese and Korean.
	
Note: A return value of ETrue implies that the font has a useable set of 
characters. It does not imply exhaustive coverage.
	
@return ETrue if Chinese ideographs are supported. */
inline TBool TOpenFontFaceAttribBase::HasCJK() const
	{
	return iCoverage[1] & ECJKSet;
	}
 
/** Tests if the typeface contains symbols only.
	
@return ETrue if the typeface contains symbols only. */
inline TBool TOpenFontFaceAttribBase::IsSymbol() const
	{
	return iCoverage[0] == 0 && iCoverage[2] == 0 && iCoverage[3] == 0 &&
		   iCoverage[1] & ESymbolSets && !(iCoverage[1] & ~ESymbolSets);
	}
 
/** Tests if the typeface is inherently bold.
	
@return ETrue if the typeface is inherently bold. */
inline TBool TOpenFontFaceAttribBase::IsBold() const
	{
	return iStyle & EBold;
	}
 
/** Tests if the typeface is inherently italic.
	
@return ETrue if the typeface is inherently italic. */
inline TBool TOpenFontFaceAttribBase::IsItalic() const
	{
	return iStyle & EItalic;
	}
 
/** Tests if the typeface has serifs.
	
@return ETrue if the typeface has serifs. */
inline TBool TOpenFontFaceAttribBase::IsSerif() const
	{
	return iStyle & ESerif;
	}
 
/** Tests if all the characters have the same width.
	
@return ETrue if all the characters have the same width. */
inline TBool TOpenFontFaceAttribBase::IsMonoWidth() const
	{
	return iStyle & EMonoWidth;
	}
 
/** Gets the typeface's name.
	
@return Descriptor containing typeface name. */
inline TPtrC TOpenFontFaceAttribBase::Name() const
	{
	return iName;
	}
 
/** Gets the full name.
	
The full name of the typeface includes style attributes like Italic, Bold, 
and Cursive.
	
@return The full name of the typeface.
@see FamilyName() */
inline TPtrC TOpenFontFaceAttrib::FullName() const
	{
	return Name();
	}
 
/** Gets the family name.
	
Note: The family name of the typeface does not include style attributes like 
"Italic".
	
@return The family name of the typeface. 
@see FullName() */
inline TPtrC TOpenFontFaceAttrib::FamilyName() const
	{
	return iFamilyName;
	}
 
/** Gets the local full name.
	
The local full name of the typeface includes style attributes like Italic, 
Bold, and Cursive.
	
The local name of the typeface is the name in the language of the current 
locale, where this is provided by the font file. If the local name is not 
available then the local name will be the same as the ordinary name.
	
@return The local full name of the typeface. */
inline TPtrC TOpenFontFaceAttrib::LocalFullName() const
	{
	return iLocalFullName;
	}
 
/** Gets the local family name.
	
The local name of the typeface is the name in the language of the current 
locale, where this is provided by the font file. If the local name is not 
available then the local name will be the same as the ordinary name.
	
Note: The family name of the typeface does not include style attributes like 
'Italic'.
	
@return The local family name of the typeface. */
inline TPtrC TOpenFontFaceAttrib::LocalFamilyName() const
	{
	return iLocalFamilyName;
	}
 
/** Gets the short full name.
	
This is the full name of the typeface, truncated to KMaxTypefaceNameLength, 
if necessary.
	
Note: Short names are names truncated to KMaxTypefaceNameLength (24) characters 
where necessary so that they can be used in the TTypeFace class. The Open 
Font Framework allows 32 characters as a maximum name length.
	
@return The short full name of the typeface.
@see FullName() */
inline TPtrC TOpenFontFaceAttrib::ShortFullName() const
	{
	// Can't use TDesC::Left for this because it panics if the desired length is > the existing length!
	return TPtrC(iName.Ptr(),Min(iName.Length(),KMaxTypefaceNameLength));
	}
 
/** Gets the short family name.
	
This is the family name, truncated to KMaxTypefaceNameLength, if necessary.
	
Note: Short names are names truncated to KMaxTypefaceNameLength (24) characters 
where necessary so that they can be used in the TTypeFace class. The Open 
Font Framework allows 32 characters as a maximum name length.
	
@return The short family name of the typeface. 
@see FamilyName() */
inline TPtrC TOpenFontFaceAttrib::ShortFamilyName() const
	{
	return TPtrC(iFamilyName.Ptr(),Min(iFamilyName.Length(),KMaxTypefaceNameLength));
	}
 
/** Gets the short local full name.
	
This is the local full name of the typeface, truncated to KMaxTypefaceNameLength, 
if necessary.
	
Note: Short names are names truncated to KMaxTypefaceNameLength (24) characters 
where necessary so that they can be used in the TTypeFace class. The Open 
Font Framework allows 32 characters as a maximum name length.
	
@return The short local full name of the typeface. 
@see LocalFullName() */
inline TPtrC TOpenFontFaceAttrib::ShortLocalFullName() const
	{
	return TPtrC(iLocalFullName.Ptr(),Min(iLocalFullName.Length(),KMaxTypefaceNameLength));
	}
 
/** Gets the short local family name.
	
This is the local family name of the typeface, truncated to KMaxTypefaceNameLength, 
if necessary.
	
Note: Short names are names truncated to KMaxTypefaceNameLength (24) characters 
where necessary so that they can be used in the TTypeFace class. The Open 
Font Framework allows 32 characters as a maximum name length.
	
@return The short local family name of the typeface.
@see LocalFamilyName() */
inline TPtrC TOpenFontFaceAttrib::ShortLocalFamilyName() const
	{
	return TPtrC(iLocalFamilyName.Ptr(),Min(iLocalFamilyName.Length(),KMaxTypefaceNameLength));
	}
 
/** Gets a pointer to the sets of flags that indicate the font's Unicode coverage.
	
Each flag that is set represents a supported Unicode range. The mapping is 
defined in the TrueType documentation under the OS/2 table. 
	
Note: Some useful subsets are defined as anonymous enumerated constants at the end 
of this class, see ELatinSet etc.
	
@return A pointer to the flags that indicate the font's Unicode coverage. 
The flags are stored in an array of four 32-bit integers. When no information 
is available, all four integers are zero.
@see SetCoverage() */
inline const TUint* TOpenFontFaceAttribBase::Coverage() const
	{
	return iCoverage;
	}
 
/** Gets the minimum typeface size.
	
This is the smallest size that can be drawn legibly.
	
@return The minimum typeface size (in pixels). */
inline TInt TOpenFontFaceAttrib::MinSizeInPixels() const
	{
	return iMinSizeInPixels;
	}
 
/** Sets the name attribute.
	
@param aName Descriptor containing typeface name. */
inline void TOpenFontFaceAttribBase::SetName(const TDesC& aName)
	{
	iName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}
 
/** Sets the full name.
	
@param aName The full name of the typeface.
@see FullName() */
inline void TOpenFontFaceAttrib::SetFullName(const TDesC& aName)
	{
	SetName(aName);
	}
 
/** Sets the family name.
	
@param aName The family name of the typeface. 
@see FamilyName() */
inline void TOpenFontFaceAttrib::SetFamilyName(const TDesC& aName)
	{
	iFamilyName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}
 
/** Sets the local full name.
	
@param aName The local full name of the typeface. 
@see LocalFullName() */
inline void TOpenFontFaceAttrib::SetLocalFullName(const TDesC& aName)
	{
	iLocalFullName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}
 
/** Sets the local family name.
	
@param aName The local family name of the typeface. 
@see LocalFamilyName() */
inline void TOpenFontFaceAttrib::SetLocalFamilyName(const TDesC& aName)
	{
	iLocalFamilyName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}
 
/** Sets the coverage flags.
	
The flags are held in four 32 bit integers. Each flag that is set represents 
a range of Unicode characters that is supported by the typeface — Latin, 
Greek, Cyrillic etc. The mapping is defined in the TrueType documentation 
under the OS/2 table.
	
Note: Some useful subsets are defined as anonymous enumerated constants at 
the end of this class, see ELatinSet etc.
	
@param aCoverage0 The first set of coverage flags (bits 0-31).
@param aCoverage1 The second set of coverage flags (bits 32-63).
@param aCoverage2 The third set of coverage flags (bits 64-95). 
@param aCoverage3 The fourth set of coverage flags (bits 96-127). */
inline void TOpenFontFaceAttribBase::SetCoverage(TUint aCoverage0,TUint aCoverage1,TUint aCoverage2,TUint aCoverage3)
	{
	iCoverage[0] = aCoverage0;
	iCoverage[1] = aCoverage1;
	iCoverage[2] = aCoverage2;
	iCoverage[3] = aCoverage3;
	}
 
/** Set the minimum typeface size.
	
This is the smallest size that can be drawn legibly.
	
@param aSize Sets the minimum typeface size (in pixels). 
@see MinSizeInPixels() */
inline void TOpenFontFaceAttrib::SetMinSizeInPixels(TInt aSize)
	{
	iMinSizeInPixels = aSize;
	}
 
/** Equality operator.
	
Compares this and another set of font attributes, including the coverage, 
the family name, the local full name, the local family name, and the minimum 
size in pixels.
	
@param aAttrib Contains the font attributes and names to compare.
@return ETrue if all values are equal, EFalse if not. */
inline TBool TOpenFontFaceAttrib::operator==(const TOpenFontFaceAttrib& aAttrib) const
	{
	return TOpenFontFaceAttribBase::operator==(aAttrib) &&
		   iFamilyName == aAttrib.iFamilyName &&
		   iLocalFullName == aAttrib.iLocalFullName &&
		   iLocalFamilyName == aAttrib.iLocalFamilyName &&
		   iMinSizeInPixels == aAttrib.iMinSizeInPixels;
	}
 
/** Sets the bold attribute.
	
@param aBold The bold attribute takes this value — ETrue or EFalse. */
inline void TOpenFontFaceAttribBase::SetBold(TBool aBold)
	{
	if (aBold)
		iStyle |= EBold;
	else
		iStyle &= ~EBold;
	}
 
/** Sets the italic attribute.
	
@param aItalic The italic attribute takes this value   ETrue or EFalse. */
inline void TOpenFontFaceAttribBase::SetItalic(TBool aItalic)
	{
	if (aItalic)
		iStyle |= EItalic;
	else
		iStyle &= ~EItalic;
	}
 
/** Sets the serif attribute.
	
@param aSerif The serif attribute takes this value  ETrue or EFalse. */
inline void TOpenFontFaceAttribBase::SetSerif(TBool aSerif)
	{
	if (aSerif)
		iStyle |= ESerif;
	else
		iStyle &= ~ESerif;
	}
 
/** Sets the mono-width attribute.
	
@param aMonoWidth The mono-width attribute takes this value — ETrue or EFalse. */
inline void TOpenFontFaceAttribBase::SetMonoWidth(TBool aMonoWidth)
	{
	if (aMonoWidth)
		iStyle |= EMonoWidth;
	else
		iStyle &= ~EMonoWidth;
	}
 
/** Equality operator. 
	
Compares this and a specified set of font attributes, including the coverage 
and the typeface name.
	
In version 6.1, and earlier, the return value was TInt.
	
@param aAttrib The font attributes to compare. This is an object of TOpenFontFaceAttribBase 
or of a derived class. 
@return ETrue if the values are equal. */
inline TBool TOpenFontFaceAttribBase::operator==(const TOpenFontFaceAttribBase& aAttrib) const
	{
	return iStyle == aAttrib.iStyle &&
		   iCoverage[0] == aAttrib.iCoverage[0] &&
		   iCoverage[1] == aAttrib.iCoverage[1] &&
		   iCoverage[2] == aAttrib.iCoverage[2] &&
		   iCoverage[3] == aAttrib.iCoverage[3] &&
		   iName.CompareF(aAttrib.iName) == 0;
	}

/** Equality operator.
	
Compares this and another open font specification. Compares all the properties 
of the two fonts.
	
@param aFontSpec The open font specification to compare with this one.
@return ETrue if all values are equal, EFalse if not. */
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
 
/** Gets the height of the font.
	
@return The height of the font, in pixels or twips. 
@see SetHeight() */
inline TInt TOpenFontSpec::Height() const
	{
	return iHeight;
	}
 
/** Gets the algorithmic width factor.
	
@return The algorithmic width factor as a 16.16 fixed-point number.
@see SetWidthFactor() */
inline TInt32 TOpenFontSpec::WidthFactor() const
	{
	return iWidthFactor;
	}
 
/** Gets the algorithmic slant factor.
	
@return The algorithmic slant factor as a 16.16 fixed-point number.
@see SetSlantFactor() */
inline TInt32 TOpenFontSpec::SlantFactor() const
	{
	return iSlantFactor;
	}
 
/** Gets the anti-aliasing setting for the font, as set by SetBitmapType().
	
@return Indicates whether or not the font should be drawn using anti-aliasing. */
inline TGlyphBitmapType TOpenFontSpec::BitmapType() const
	{
	return (TGlyphBitmapType)iBitmapType;
	}

/** Gets the font effects flags.
@publishedPartner For use by system/UI software.
@released
@return The font effects flags.
@see TOpenFontSpec::SetEffects()
*/
inline TUint32 TOpenFontSpec::Effects() const
	{
	return iEffects;
	}

/** Gets the print position.
	
@return The print position. */
inline TFontPrintPosition TOpenFontSpec::PrintPosition() const
	{
	return iPrintPosition;
	}
 
/** Sets the font's height.
	
@param aHeight The font's height, in pixels or twips.
@see Height() */
inline void TOpenFontSpec::SetHeight(TInt aHeight)
	{
	iHeight = aHeight;
	}

/** Sets the algorithmic width factor.
	
The width factor is multiplied by the pixel's x position to get the new position, 
causing characters to become wider or narrower. A width factor of 1 (65536 
in 16.16 fixed-point number format) should be used if the character width 
is not to be changed.
	
@param aWidthFactor The algorithmic width factor as a 16.16 fixed-point number.
@see WidthFactor() */
inline void TOpenFontSpec::SetWidthFactor(TInt32 aWidthFactor)
	{
	iWidthFactor = aWidthFactor;
	}
 
/** Sets the algorithmic slant factor.
	
Note: The slant factor is used to create an italic effect for characters which 
do not have an italic glyph in the typeface. When slanting is active, pixel x 
co-ordinates are shifted by a factor relative to the y co-ordinate (i.e. x 
= x + y x slant factor).
	
The slant factor is a 32 bit, 16.16 fixed-point number. This means that the 
first 16 bits are treated as a whole number, and the second 16 as the fractional 
part. e.g. if aSlantFactor=0, there is no slant. If aSlantFactor=65536 this 
is equivalent to an integer slant value of 1, which causes a 45 degree slant 
on the character.
	
@param aSlantFactor The slant factor as a 16.16 fixed-point number.
@see SlantFactor() */
inline void TOpenFontSpec::SetSlantFactor(TInt32 aSlantFactor)
	{
	iSlantFactor = aSlantFactor;
	}
 
/** Sets whether the font should be drawn using anti-aliasing. If set, this value 
overrides the default setting (set by CFbsTypefaceStore::SetDefaultBitmapType()) 
for this font.
	
Anti-aliasing can only be used for scalable fonts. There is currently no anti-aliasing 
support for bitmapped fonts.
	
@param aBitmapType Indicates whether or not the font should be drawn using 
anti-aliasing. */
inline void TOpenFontSpec::SetBitmapType(TGlyphBitmapType aBitmapType)
	{
	iBitmapType = aBitmapType;
	}

/** Sets the font effects flags.
@publishedPartner For use by system/UI software.
@released
@param aEffect The font effects flags to be set.
@see TOpenFontSpec::Effects()
*/
inline void TOpenFontSpec::SetEffects(TUint32 aEffects)
	{
	iEffects = aEffects;
	}

/** Gets the font file's UID.
	
@return The uid of the file. */
inline TUid COpenFontFile::Uid() const
	{
	return iUid;
	}
 
/** Gets the full path and filename of the font file
	
This is the filename that was passed to the constructor when the object is 
created.
	
@return The filename of the font file. */
inline const TDesC& COpenFontFile::FileName() const
	{
	return iFileName;
	}
 
/** Gets the typeface at a specified index in the typeface attribute array.
	
@param aFaceIndex The index of the typeface for which the attributes are required.
@return The attributes of the typeface with the specified index.
@see AddFaceL()
@see FaceCount() */
inline const TOpenFontFaceAttrib& COpenFontFile::FaceAttrib(TInt aFaceIndex) const
	{
	return iFaceAttrib[aFaceIndex];
	}
 
/** Gets the number of typefaces in the typeface attributes array.
	
This is the number of typefaces in the font file — the attributes for each 
typeface should be loaded into the array when the derived object is constructed.
	
@return The number of typefaces in the font file.
@see AddFaceL()
@see FaceAttrib() */
inline TInt COpenFontFile::FaceCount() const
	{
	return iFaceAttrib.Count();
	}
 
/** Increments a reference count by one.
	
@see DecRefCount() */
inline void COpenFontFile::IncRefCount()
	{
	iRefCount++;
	}
 
/** Decrement a reference count by one.
	
@return ETrue if the reference count has reached zero (i.e. is less than or 
equal to zero); EFalse if the reference count has not yet reached zero (i.e. 
is positive).
@see IncRefCount() */
inline TBool COpenFontFile::DecRefCount()
	{
	iRefCount--;
	return iRefCount <= 0;
	}
 
/** Default C++ constructor. */
inline COpenFontRasterizerContext::COpenFontRasterizerContext():
	iGlyphData(NULL)
	{
	}
 
/** Start writing the glyph data.
	
Use this function to initialise the buffer to which the glyph bitmap is to 
be written. Call WriteGlyphBit() to add bits to the buffer.
	
@param aGlyphData A pointer to the glyph data. */
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
 
/** Writes a bit to the glyph buffer.
	
Before calling this function you should first call StartGlyph().
	
@param aBit The bit to be added to the buffer. */
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

/** Writes a byte to the glyph buffer.

Before calling this function you should first call StartGlyph().

@param aByte The byte to be added to the buffer. */	
inline void COpenFontRasterizerContext::WriteGlyphByte(TInt aByte)
 	{
	if (iGlyphDataPtr < iGlyphDataEnd)
		*iGlyphDataPtr++ = (TUint8)aByte;
	else
		iOverflow = TRUE;
	iBytesNeeded++;
	}
 
/** Completes writing glyph data.
	
Use this function to complete writing the glyph bitmap to the buffer. Call 
it after adding all necessary bits using WriteGlyphBit(). */
inline void COpenFontRasterizerContext::EndGlyph()
	{
	// Add 4 bytes to the data size; some BITGDI functions require this.
	iGlyphData->SetBytesNeeded(iBytesNeeded + 4);
	iGlyphData = NULL;
	}
    
/** Tests whether the bitmap buffer is large enough to hold the bitmap.
	
@return ETrue if the bitmap will overflow its buffer, otherwise EFalse. */
inline TBool TOpenFontGlyphData::Overflow() const
	{
	return iBytesNeeded > iBitmapBufferSize;
	}
 
/** Gets the number of bytes needed to store the glyph bitmap.
	
@return The number of bytes needed to store the glyph bitmap.
@see SetBytesNeeded() */
inline TInt TOpenFontGlyphData::BytesNeeded() const
	{
	return iBytesNeeded;
	}
 
/** Gets a constant pointer descriptor containing the bitmap this object 
represents. 
	
@return Pointer descriptor for the glyph. */
inline TPtrC8 TOpenFontGlyphData::Bitmap() const
	{
	return TPtrC8(iBitmap,iBytesNeeded);
	}
 
/** Gets a pointer to the bitmap.
	
This points either to the buffer used to write the bitmap when it is first 
rasterized, or to the cache if the character was already rasterized.
	
@return A pointer to the bitmap. */
inline const TUint8* TOpenFontGlyphData::BitmapPointer() const
	{
	return iBitmap;
	}
 
/** Gets the character's metrics.
	
@return The character's open font metrics. */
inline const TOpenFontCharMetrics* TOpenFontGlyphData::Metrics() const
	{
	return iMetrics;
	}
 
/** Gets a pointer to the start of the bitmap buffer.
	
@return A pointer to the start of the bitmap buffer. */
inline TUint8* TOpenFontGlyphData::BufferStart()
	{
	return iBitmapBuffer;
	}
 
/** Gets a pointer to the end of the bitmap buffer.
	
@return A pointer to the end of the bitmap buffer. */
inline TUint8* TOpenFontGlyphData::BufferEnd()
	{
	return iBitmapBuffer + iBitmapBufferSize;
	}
 
/** Sets the number of bytes needed to store the glyph bitmap.
	
@param aBytes The number of bytes needed to store the glyph bitmap.
@see BytesNeeded() */
inline void TOpenFontGlyphData::SetBytesNeeded(TInt aBytes)
	{
	iBytesNeeded = aBytes;
	}
 
/** Sets the pointer to the bitmap buffer.
	
@param aBitmap The pointer to the bitmap buffer. */
inline void TOpenFontGlyphData::SetBitmapPointer(const TUint8* aBitmap)
	{
	iBitmap = aBitmap;
	}
 
/** Sets the character's metrics, passing a pointer to a TOpenFontCharMetrics object.
	
@param aMetrics A pointer to the character's open font character metrics. */
inline void TOpenFontGlyphData::SetMetricsPointer(const TOpenFontCharMetrics* aMetrics)
	{
	iMetrics = aMetrics;
	}
 
/** Sets the bitmap and metrics pointers to point to the internal buffers.
	
The alternative is that the pointers point to the cache of metrics and bitmaps 
that have already been rasterized. */
inline void TOpenFontGlyphData::SetPointersToInternalBuffers()
	{
	iBitmap = iBitmapBuffer;
	iMetrics = &iMetricsBuffer;
	}
 
/** Sets the character's metrics, passing a reference to a TOpenFontCharMetrics 
object.
	
@param aMetrics The character's open font character metrics. */
inline void TOpenFontGlyphData::SetMetrics(TOpenFontCharMetrics& aMetrics)
	{
	iMetricsBuffer = aMetrics;
	iMetrics = &iMetricsBuffer;
	}
 
/** Sets the glyph index.
	
@param aGlyphIndex The glyph index. */
inline void TOpenFontGlyphData::SetGlyphIndex(TInt aGlyphIndex)
	{
	iGlyphIndex = aGlyphIndex;
	}
	
/** Uses ECOM plug-in framework to instantiate the Open Font rasteriser interface 
implementation given its implementation UID. 

@param     "TUid aInterfaceImplUid"
            The UID of the interface implementation required 

@returns   "COpenFontRasterizer*"
            A pointer to a COpenFontRasterizer object. */
inline COpenFontRasterizer* COpenFontRasterizer::NewL(TUid aInterfaceImplUid)
{
	return reinterpret_cast <COpenFontRasterizer*> (
		REComSession::CreateImplementationL(
			aInterfaceImplUid,
			_FOFF(COpenFontRasterizer, iDtor_ID_Key))); 
}

/** Default destructor */
inline COpenFontRasterizer::~COpenFontRasterizer()
{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
}

#endif // __OPENFONT_H__
