// FNTSTORE.H
//
// Copyright (c) 1995-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __FNTSTORE_H__
#define __FNTSTORE_H__

#ifdef SYMBIAN_REMOVE_FONT_METRICS_V1
#undef SYMBIAN_HIDE_FONT_METRICS_V1
#define SYMBIAN_HIDE_FONT_METRICS_V1	// forcibly hide the API
#undef SYMBIAN_SUPPORT_FONT_METRICS_V1	// forcibly turn of support
#endif

#ifdef SYMBIAN_SUPPORT_FONT_METRICS_V1
#undef SYMBIAN_HIDE_FONT_METRICS_V1
#endif

#include <e32std.h>
#include <f32file.h>
#include <gdi.h>
#include <openfont.h>

class CFontStoreFile;
class CFontBitmap;
class RReadStream;
class TTypefaceFontBitmap;

class TCharacterMetrics
/**
@internalTechnology
*/
	{
	public:
	IMPORT_C TCharacterMetrics();

	TInt16 iAscentInPixels;
	TInt16 iHeightInPixels;
	TInt16 iLeftAdjustInPixels;
	TInt16 iMoveInPixels;
	TInt16 iRightAdjustInPixels;
	};

class TAlgStyle
/** 
An algorithmic style for a font.

Holds attributes such as whether the font is bold or italic, and the width 
and height factors.
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAlgStyle();
	IMPORT_C void SetIsBold(TBool aIsBold);
	IMPORT_C void SetIsItalic(TBool aIsItalic);
	IMPORT_C void SetIsMono(TBool aIsMono);
	IMPORT_C void SetWidthFactor(TInt aWidthFactor);
	IMPORT_C void SetHeightFactor(TInt aHeightFactor);
	IMPORT_C TBool IsBold() const;
	IMPORT_C TBool IsItalic() const;
	IMPORT_C TBool IsMono() const;
	IMPORT_C TInt WidthFactor() const;
	IMPORT_C TInt HeightFactor() const;
	IMPORT_C TBool operator==(const TAlgStyle& aAlgStyle) const;

public:
	/** Baseline offset in pixels. */
	TInt iBaselineOffsetInPixels;
private:
	enum
		{
		EBold=1,
		EItalic=2,
		EMono=4,
		};
	/** This member is private and not intended for use. */
    TInt8 iFlags;
	/** This member is private and not intended for use. */
	TInt8 iWidthFactor;
	/** This member is private and not intended for use. */
	TInt8 iHeightFactor;
	};

/** 
Bitmap font class.
An object of this class may either access and use a bitmap font (a CFontBitmap)
or an open font (a COpenFont).
Stored in a CFontStore.
@publishedAll
@released
*/
class CBitmapFont : public CFont
	{
	friend class CFontStore;
private:
	CBitmapFont(RHeap* aHeap,const TFontSpec& aFontSpecInTwips, const TAlgStyle& aAlgStyle, CFontBitmap* aFontBitmap);
	CBitmapFont(RHeap* aHeap,const TFontSpec& aFontSpecInTwips, const TAlgStyle& aAlgStyle, COpenFont* aOpenFont);
	void ConstructL();
	~CBitmapFont();
	static CBitmapFont* NewL(RHeap* aHeap, const TFontSpec& aFontSpecInTwips, const TAlgStyle& aAlgStyle, CFontBitmap* aFontBitmap);
	static CBitmapFont* NewL(RHeap* aHeap, const TFontSpec& aFontSpecInTwips, const TAlgStyle& aAlgStyle, COpenFont* aOpenFont);

private:
	// From CFont
	IMPORT_C virtual TUid DoTypeUid() const;
	IMPORT_C virtual TInt DoHeightInPixels() const;
	IMPORT_C virtual TInt DoAscentInPixels() const;
	IMPORT_C virtual TInt DoCharWidthInPixels(TChar aChar) const;
	IMPORT_C virtual TInt DoTextWidthInPixels(const TDesC &aText) const;
	IMPORT_C virtual TInt DoBaselineOffsetInPixels() const;
	IMPORT_C virtual TInt DoTextCount(const TDesC &aText, TInt aWidthInPixels) const;
	IMPORT_C virtual TInt DoTextCount(const TDesC &aText, TInt aWidthInPixels, TInt &aExcessWidthInPixels) const;
	IMPORT_C virtual TInt DoMaxCharWidthInPixels() const;
	IMPORT_C virtual TInt DoMaxNormalCharWidthInPixels() const;
	IMPORT_C virtual TFontSpec DoFontSpecInTwips() const;
	IMPORT_C virtual TInt DoExtendedFunction(TUid aFunctionId, TAny* aParam = NULL) const;

public:
	// New functions
	TUid Uid() const;
	IMPORT_C TCharacterMetrics CharacterMetrics(TInt aCode,const TUint8*& aBytes) const;
	IMPORT_C TBool GetCharacterData(TInt aSessionHandle, TInt aCode, TOpenFontCharMetrics& aMetrics, const TUint8*& aBitmap) const;
	IMPORT_C TBool Rasterize(TInt aSessionHandle,TInt aCode,TOpenFontGlyphData* aGlyphData) const;
	IMPORT_C void GetFontMetrics(TOpenFontMetrics& aMetrics) const;
	IMPORT_C TBool GetFaceAttrib(TOpenFontFaceAttrib& aAttrib) const;
	IMPORT_C TInt BitmapEncoding() const;
	IMPORT_C TBool HasCharacterL(TInt aCode) const;
	IMPORT_C TBool CharacterNeedsToBeRasterized(TInt aSessionHandle,TInt aCode) const;
	IMPORT_C void operator delete(TAny*);
	inline TBool IsOpenFont() const;
	inline COpenFont* OpenFont() const;
	inline TGlyphBitmapType GlyphBitmapType() const;

private:
	TInt Width(TInt aNum) const;
	TInt Height(TInt aNum) const;
	CFontBitmap* FontBitmap() const;

private:
	TFontSpec iFontSpecInTwips;

public:
	/** The algorithmic font style. */
	TAlgStyle iAlgStyle;	// must not move this member

private:
	RHeap* iHeap;
	TInt iFontBitmapOffset;
	COpenFont* iOpenFont;	// if iOpenFont is non-null this is an open font and many functions are forwarded to it
	};

class CFontStore : public CTypefaceStore
/** 
A store for fonts.

Stores and handles both open and fixed-size fonts. Open fonts are made from 
open (scalable) typefaces by Open Font plug-in rasterizers. Fonts of other 
typefaces are stored in a limited number of fixed sizes. However, which is 
being used is transparent to the user of this class. For example the GetNearestFont...() 
functions get a bitmap font which may be retrieved from memory or generated 
via a rasterizer.
@publishedAll
@released
*/
    {
private:
	CFontStore();
	void ConstructL();
public:
	IMPORT_C static CFontStore* NewL(RHeap* aHeap);
	IMPORT_C ~CFontStore();
	IMPORT_C TUid AddFileL(const TDesC& aName);
	IMPORT_C void RemoveFile(TUid aFileUid);
#ifndef SYMBIAN_HIDE_FONT_METRICS_V1
	IMPORT_C TInt GetNearestFontInTwips(CFont *&aFont, const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont *&aFont, const TFontSpec &aFontSpec);
#endif
	IMPORT_C TInt GetNearestFontToDesignHeightInTwips(CFont *&aFont, const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontToDesignHeightInPixels(CFont *&aFont, const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontToMaxHeightInTwips(CFont*& aFont, const TFontSpec& aFontSpec, TInt aMaxHeight);
	IMPORT_C TInt GetNearestFontToMaxHeightInPixels(CFont*& aFont, const TFontSpec& aFontSpec, TInt aMaxHeight);
#ifndef SYMBIAN_HIDE_FONT_METRICS_V1
	IMPORT_C TInt GetNearestFontInTwips(CFont *&aFont, const TOpenFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont *&aFont, const TOpenFontSpec &aFontSpec);
#endif
	IMPORT_C TInt GetNearestFontToDesignHeightInTwips(CFont *&aFont, const TOpenFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontToDesignHeightInPixels(CFont *&aFont, const TOpenFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontToMaxHeightInTwips(CFont*& aFont, const TOpenFontSpec& aFontSpec, TInt aMaxHeight);
	IMPORT_C TInt GetNearestFontToMaxHeightInPixels(CFont*& aFont, const TOpenFontSpec& aFontSpec, TInt aMaxHeight);
	IMPORT_C TInt GetFontById(CFont *&aFont,TUid aUid,const TAlgStyle& aAlgStyle);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport &aTypefaceSupport,TInt aTypefaceIndex) const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C void InstallRasterizerL(COpenFontRasterizer* aRasterizer);
	IMPORT_C void DeleteSessionCache(TInt aSessionHandle);
	inline TGlyphBitmapType DefaultBitmapType() const;
	inline void SetDefaultBitmapType(TGlyphBitmapType aType);
	TInt BitmapFontFilesCount() const;
private:
	void InternalizeFontStoreFileL(CFontStoreFile* aFontStoreFile, TInt aFontVersion);
	TTypeface* GetNearestTypeface(const TTypeface& aTypeface) const;
	TTypefaceFontBitmap GetNearestTypefaceFontBitmap(const TFontSpec& aFontSpecInPixels, TInt aMaxHeight = 0);
	CFontBitmap* GetFontBitmapById(TUid aUid);
	CBitmapFont* FindFont(const TFontSpec& aFontSpecInPixels,const TAlgStyle& aAlgStyle,TUid aUid) const;
	CBitmapFont* FindFont(const TOpenFontSpec& aFontSpecInPixels,const TAlgStyle& aAlgStyle) const;
	CBitmapFont* NewFontL(const TFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,CFontBitmap* aFontBitmap);
	CBitmapFont* NewFontL(const TOpenFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,COpenFont* aOpenFont);
	TInt VerticalPixelsToTwips(TInt aPixelHeight) const;
	TInt VerticalTwipsToPixels(TInt aTwipsHeight) const;
	TInt GetNearestBitmapFontInPixels(CBitmapFont *&aFont, TFontSpec &aFontSpec, TInt aMaxHeight = 0);
	TInt GetNearestOpenFontInPixels(CBitmapFont *&aFont, TOpenFontSpec &aFontSpec, const TOpenFontSpec& aIdealFontSpecInPixels, TInt aMaxHeight = 0);
	TInt GetNearestFontInPixels(CFont *&aFont, const TOpenFontSpec &aFontSpec, TInt aMaxHeight);
	void UpdateTypefaceSupportListL();

public:
	/** The width of 1000 pixels in twips.
	
	This is set in the constructor. If the appropriate HALData attributes are 
	set (EDisplayXPixels and EDisplayXTwips) then the value is calculated using 
	these; otherwise the value is set to 11860. */
	TInt iKPixelWidthInTwips;
	
	/** The height of 1000 pixels in twips.
	
	This is set in the constructor. If the appropriate HALData attributes are 
	set (EDisplayYPixels and EDisplayYTwips) then the value is calculated using 
	these; otherwise the value is set to 11860. */
	TInt iKPixelHeightInTwips;
private:
	RFs iFs;
	RHeap* iHeap;
	CArrayPtrFlat<CFontStoreFile> iFontStoreFileList;
	CArrayPtrFlat<TTypeface> iTypefaceList;
	CArrayPtrFlat<CFontBitmap> iFontBitmapList;
	CArrayFixFlat<TTypefaceFontBitmap> iTypefaceFontBitmapList;
	CArrayPtrFlat<COpenFontFile> iOpenFontFileList;
	CArrayFixFlat<TTypefaceSupport> iOpenFontTypefaceSupportList;
	CArrayPtrFlat<COpenFontRasterizer> iOpenFontRasterizerList;
	COpenFontSessionCacheList* iOpenFontSessionCacheList;
	TInt iOpenFontUid;
	TGlyphBitmapType iDefaultBitmapType;
	};

// inline functions start here
inline TBool CBitmapFont::IsOpenFont() const
/** Returns whether the bitmap font object is an open font (a COpenFont) rather 
than a bitmap font (a CFontBitmap).
	
@return ETrue if the bitmap font object is using an open font (a COpenFont); 
EFalse if it is using a bitmap font (a CFontBitmap). */
	{
	return iOpenFont != NULL;
	}

inline COpenFont* CBitmapFont::OpenFont() const
/** Returns a pointer to the open font being used by the bitmap font object.
	
@return A pointer to an open font. */
	{ 
	return iOpenFont;
	}

inline TGlyphBitmapType CBitmapFont::GlyphBitmapType() const
/** Gets the anti-aliasing setting for the font.
	
This is only applicable to open fonts (COpenFonts) not bitmap fonts (CBitmapFonts).
	
Note that this setting is stored in the device-independent font specification 
which is set when the bitmap font object is constructed.
	
@return The anti-aliasing setting for the font. */
	{
	return iFontSpecInTwips.iFontStyle.BitmapType();
	}

inline TGlyphBitmapType CFontStore::DefaultBitmapType() const
/** Returns a default bimap type.
	
@return A default bimap type. */
	{
	return iDefaultBitmapType;
	}

inline void CFontStore::SetDefaultBitmapType(TGlyphBitmapType aType)
/** Sets a default bimap type.
	
@param aType A default bimap type. */
	{
	iDefaultBitmapType = aType;
	}

#endif
