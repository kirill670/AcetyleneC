// FBS.H
//
// Copyright (C) 1995-2004 Symbian Software Ltd. All rights reserved.
//

#ifndef __FBS_H__
#define __FBS_H__

#ifdef SYMBIAN_REMOVE_FONT_METRICS_V1
#undef SYMBIAN_HIDE_FONT_METRICS_V1
#define SYMBIAN_HIDE_FONT_METRICS_V1	// forcibly hide the API
#undef SYMBIAN_SUPPORT_FONT_METRICS_V1	// forcibly turn of support
#endif

#ifdef SYMBIAN_SUPPORT_FONT_METRICS_V1
#undef SYMBIAN_HIDE_FONT_METRICS_V1
#endif

#include <e32std.h>
#include <gdi.h>
#include <fntstore.h>
#include <bitmap.h>

/**
@internalTechnology
*/
const TUid KCFbsFontUid = { 268435518 };
/**
@internalComponent
*/
const TUid KMultiBitmapRomImageUid = { 268435521 };
const TUint32 KFontBitmapServerUidValue = 0x10003a16;
const TUid KFontBitmapServerUid = { KFontBitmapServerUidValue };
/**
@internalAll
*/
IMPORT_C TInt FbsStartup();

/** 
Required to ensure BC between NGage and 7.0S platforms.  
Function is exported at ordinal corresponding to where NGage platform
has extended this library and must not be moved.
@internalAll
*/
IMPORT_C void DummyReserved1();


/** 
Character width and adjustment information. 
@publishedAll
@released
*/
class SCharWidth
	{
public:
	/** The left adjust of the character. */
	TInt iLeftAdjust;
	/** The right adjust of the character. */
	TInt iRightAdjust;
	/** The total width of the character, defined as iLeftAdjust + iWidth + iRightAdjust. */
	TInt iMove;
	/** The width of the character. */
	TInt iWidth;
	};

class CFbsRalCache;

/** 
A session with the font and bitmap server. 
@publishedAll 
@released
*/
class RFbsSession : protected RSessionBase
	{
	// Allow access to internals for test
	friend class RClean;
	friend class TestFbs;
	friend class RTestBitmap;
	
	friend class CFbsBitmap;
	friend class CFbsBitmapAsyncStreamer;
public:
	IMPORT_C RFbsSession();
	IMPORT_C static TInt Connect();
	IMPORT_C static void Disconnect();
	IMPORT_C static RFbsSession* GetSession();
	IMPORT_C void CallBack();
	IMPORT_C void SetCallBack(TCallBack aCallBack);
	IMPORT_C void ResetCallBack();
	IMPORT_C TInt ResourceCount();
	IMPORT_C TInt SendCommand(TInt aMessage,TInt aInt0=0,TInt aInt1=0,TInt aInt2=0,TInt aInt3=0) const;
	TInt SendCommand(TInt aMessage, const TIpcArgs& aArgs) const;
	IMPORT_C TVersion Version();
	IMPORT_C TUint8* HeapBase() const;
	IMPORT_C TInt GetHeapSizes(TInt& aDefaultHeap, TInt& aSmallBmpHeap, TInt& aBigBmpChunk);
	TInt SessionHandle() const { return Handle(); }
	TInt AllocScanLineBuffer(TInt aSize);
	HBufC8* GetScanLineBuffer();
private:
	TBool LookupBitmapInROM(const TDesC& aFilename, TAny*& aAddr);
private:
	TInt iConnections;
	TCallBack iCallBack;
	RChunk iSharedChunk;
	RMutex iAddressMutex;
	RChunk iLargeBitmapChunk;
	RFs iFileServer;
	CFbsRalCache* iRomFileAddrCache;
	TAny* iUnused;
	HBufC8* iScanLineBuffer;
	TUint32* iSpare;
	};

/** 
Font managed by the font and bitmap server.
CFbsFont objects are used for screen and off-screen bitmap fonts. They are 
usually obtained by calls to the CBitmapDevice::GetNearestFontInPixels() and 
MGraphicsDeviceMap::GetNearestFontInTwips() functions.
The class implements a number of functions inherited from CFont.
@see CBitmapDevice::GetNearestFontInPixels()
@see MGraphicsDeviceMap::GetNearestFontInTwips() 
@publishedAll 
@released
*/
class CFbsFont: public CFont
	{
	friend class CFbsTypefaceStore;
public:
	// From CFont
	/** Gets the font's UID. 
	All CFbsFont objects have the constant UID KCFbsFontUid. It is safe to cast 
	from CFont* to CFbsFont* if CFont::TypeUid() returns KCFbsFontUid.
	@return The font's UID. This should be KCFbsFontUid. 
	@see CFont::TypeUid() */
	TUid TypeUid() const { return KCFbsFontUid; }
	IMPORT_C TInt HeightInPixels() const;
	IMPORT_C TInt AscentInPixels() const;
	IMPORT_C TInt CharWidthInPixels(TChar aChar) const;
	IMPORT_C TInt TextWidthInPixels(const TDesC& aText) const;
	IMPORT_C TInt BaselineOffsetInPixels() const;
	IMPORT_C TInt TextCount(const TDesC& aText,TInt aWidthInPixels) const;
	IMPORT_C TInt TextCount(const TDesC& aText,TInt aWidthInPixels,TInt& aExcessWidthInPixels) const;
	IMPORT_C TInt MaxCharWidthInPixels() const;
	IMPORT_C TInt MaxNormalCharWidthInPixels() const;
	IMPORT_C TFontSpec FontSpecInTwips() const;
	IMPORT_C CFont::TCharacterDataAvailability GetCharacterData(TUint aCode,TOpenFontCharMetrics& aMetrics,
	const TUint8*& aBitmap,TSize& aBitmapSize) const;
	IMPORT_C TBool GetFontMetrics(TOpenFontMetrics& aMetrics) const;
	IMPORT_C void TextWidthInPixels(const TDesC& aText,SCharWidth& aCharWidth) const;
	IMPORT_C TInt Handle() const;
	IMPORT_C TCharacterMetrics CharacterMetrics(TInt aCode,const TUint8*& aBytes) const;
	IMPORT_C TInt RawTextWidthInPixels(const TDesC& aText) const;
	IMPORT_C TBool GetFaceAttrib(TOpenFontFaceAttrib& aAttrib) const;
	IMPORT_C TBool IsOpenFont() const;
	IMPORT_C TBool HasCharacter(TInt aCode) const;
	IMPORT_C TInt ExtendedFunction(TUid aFunctionId, TAny* aParam = NULL);
protected:
	IMPORT_C CFbsFont();
	IMPORT_C ~CFbsFont();
	IMPORT_C CFbsFont(const CFbsFont& aFont);
	IMPORT_C CBitmapFont* Address() const;
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C void Reset();
protected:
	RFbsSession* iFbs;
	CBitmapFont* iAddressPointer;
	TInt iHandle;
	TInt iServerHandle;
	};

/** 
A bitmap managed by the font and bitmap server.
The class also defines some palette functionality which is not yet 
implemented, since none of the modes currently supported by screen 
or bitmaps require variable palettes.
Note that the CFbsBitmap format is internal to Symbian, but the 
Image Converter API can be used to convert such bitmaps to standard formats. 
CFbsBitmap instances cannot be shared between different threads. They use some shared
thread local storage data. If you want to share a bitmap between threads, use Duplicate().
@publishedAll 
@released
@see CFbsBitmap::Duplicate()
*/
class CFbsBitmap : public CBase
	{
	friend class TBitmapUtil;
	friend class CBitwiseBitmap;
	friend class CFbsBitmapAsyncStreamer;
public:
	IMPORT_C CFbsBitmap();
	IMPORT_C ~CFbsBitmap();
	IMPORT_C void Reset();
	IMPORT_C static TInt ScanLineLength(TInt aLength,TDisplayMode aDispMode);
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TDisplayMode InitialDisplayMode() const;
	IMPORT_C TInt SetDisplayMode(TDisplayMode aDisplayMode);
	IMPORT_C TInt Create(const TSize& aSizeInPixels,TDisplayMode aDispMode);
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C TBool IsRomBitmap() const;
	IMPORT_C void SetRomBitmapL(CBitwiseBitmap* aRomBitmapPointer,TInt& aBitmapSizeInBytes);
	IMPORT_C TInt Load(const TDesC& aFileName,TInt32 aId=0,TBool aShareIfLoaded=ETrue);
	IMPORT_C TInt Load(const TDesC& aFileName,TInt32 aId,TBool aShareIfLoaded,TUint aFileOffset);
	IMPORT_C TInt LoadAndCompress(const TDesC& aFileName,TInt32 aId=0,TBool aShareIfLoaded=ETrue);
	IMPORT_C TInt LoadAndCompress(const TDesC& aFileName,TInt32 aId,TBool aShareIfLoaded,TUint aFileOffset);
	IMPORT_C TInt Save(const TDesC& aFilename);
	IMPORT_C static void StoreL(const TDesC& aFilename,TInt aNumSources,const TDesC* aSources[],TInt32 aSourceIds[]);
    IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TDisplayMode aDispMode) const;
    IMPORT_C void SetScanLine(TDes8& aBuf,TInt aY) const;
	IMPORT_C void GetVerticalScanLine(TDes8& aBuf,TInt aX,TDisplayMode aDispMode) const;
	IMPORT_C void GetVerticalScanLine(TDes8& aBuf,TInt aX,const TPoint& aDitherOffset,TDisplayMode aDispMode) const;
	IMPORT_C TInt Handle() const;
	IMPORT_C SEpocBitmapHeader Header() const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C void GetPixel(TRgb& aColor,const TPoint& aPixel) const;
	IMPORT_C TInt Resize(const TSize& aSizeInPixels);
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C void SetSizeInTwips(const MGraphicsDeviceMap* aMap);
	IMPORT_C void SetSizeInTwips(const TSize& aSizeInTwips);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void ExternalizeRectangleL(RWriteStream& aStream,const TRect& aRect) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C TInt Compress();
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C static TBool IsFileInRom(const TDesC& aFilename,TUint32*& aWord);
	IMPORT_C TBool IsMonochrome() const;
	IMPORT_C TBool IsLargeBitmap() const;
	IMPORT_C void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const;
	IMPORT_C void SetPalette(CPalette* aPalette);
	IMPORT_C TInt GetPalette(CPalette*& aPalette) const;
	IMPORT_C TUint32* DataAddress() const;
	IMPORT_C TInt CreateHardwareBitmap(const TSize& aSizeInPixels,TDisplayMode aDispMode,TUid aCreatorUid);
	IMPORT_C TInt HardwareBitmapHandle() const;
	IMPORT_C void LockHeap(TBool aAlways=EFalse) const;
	IMPORT_C void UnlockHeap(TBool aAlways=EFalse) const;
	IMPORT_C void LockHeapLC(TBool aAlways=EFalse) const;
	IMPORT_C static void UnlockHeap(TAny* aFbsBitmap);
	IMPORT_C TBool IsCompressedInRAM() const;
	IMPORT_C TInt SwapWidthAndHeight();
protected:
    IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,const TPoint& aDitherOffset,TDisplayMode aDispMode) const;
	CBitwiseBitmap* Address() const;
	void DoSaveL(RFile& aFile);
	TInt DoCreate(const TSize& aSizeInPixels,TDisplayMode aDispMode,TUid aCreatorUid);
private:
	TInt DoLoad(const TDesC& aFileName,TInt32 aId,TBool aShareIfLoaded,TUint aFileOffset);
	TInt DoLoadAndCompress(const TDesC& aFileName,TInt32 aId,TBool aShareIfLoaded,TUint aFileOffset);
	TBool LoadShiftedRomBmpL(const TDesC& aFileName,TInt32 aId,TUint aFileOffset);
protected:
	RFbsSession* iFbs;
	CBitwiseBitmap* iAddressPointer;
	CBitwiseBitmap* iRomPointer;
	TInt iHandle;
	TInt iServerHandle;
	};

class CDirectFileStore;

/**
@deprecated
@internalComponent
*/
class CFbsBitmapAsyncStreamer : public CBase
	{
public:
	enum TMode {ELoad, ESave};
public:
	IMPORT_C ~CFbsBitmapAsyncStreamer();
	IMPORT_C static CFbsBitmapAsyncStreamer* NewL(TMode aMode);
	IMPORT_C TInt Load(const TDesC& aFilename,TInt32 aId,TInt& aScanLines);
	IMPORT_C TBool LoadScanLinesL(TInt aNumberOfScanLines,CFbsBitmap*& aBitmap);
	IMPORT_C TInt Save(const TDesC& aFilename,CFbsBitmap* aBitmap,TInt32& aId,TInt& aScanLines);
	IMPORT_C TBool SaveScanLinesL(TInt aNumberOfScanLines);
private:
	CFbsBitmapAsyncStreamer(TMode aMode);
	void ConstructL();
	void DoLoadL(const TDesC& aFilename,TInt32 aId);
	void DoSaveL(RFile& aFile);
private:
	RFbsSession* iFbs;
	RStoreReadStream iReadStream;
	RStoreWriteStream iWriteStream;
	TStreamId iId;
	CDirectFileStore* iStore;
	TInt iCurrentScanLine;
	TUint32* iScanLineBase;
	CFbsBitmap* iBitmap;
	SEpocBitmapHeader iHeader;
	TDisplayMode iDispMode;
	TMode iMode;
	};


/** 
Provides fast read/write access to the image data of a bitmap. 

Functionality includes getting and setting the individual pixels of a bitmap. 
Common to this is the concept of the current pixel position. This is held 
as member data and is changed by using various efficient functions. For example, 
incrementing the position's x- or y co-ordinate is much quicker than setting 
a completely new position. This efficiency issue is important as these functions 
are used as part of the frequently used blitting DDA used for creating 
stretched or compressed versions of bitmaps.

Due to the defragmentation process that is used to compress the font and bitmap 
server heap, bitmaps may be moved in memory at any time including whilst 
the bitmap's contents are being manipulated. Therefore, operations to lock 
and unlock the heap are provided. These prevent and allow the heap to be compressed. 
The use of these functions, surrounding any calls to the 
other member functions maximises the simplicity and efficiency of these functions.

Note that you should always ensure each Begin() is matched by an End() call 
when using this class.

Note also that all display modes including EColor16M are supported, but the 
TDisplayMode values ERgb and ENone are not considered to be display modes. 
@publishedAll 
@released
*/
class TBitmapUtil
	{
public:
	IMPORT_C void Begin(const TPoint& aPosition);
	IMPORT_C void Begin(const TPoint& aPosition,const TBitmapUtil& aUtil);
	IMPORT_C void End();
	IMPORT_C TBitmapUtil(CFbsBitmap* aBitmap);
	IMPORT_C TUint32 GetPixel() const;
	IMPORT_C void SetPixel(TUint32 aValue);
	IMPORT_C void SetPixel(const TBitmapUtil& aSource);
	IMPORT_C void SetPos(const TPoint& aPosition);
	IMPORT_C void DecXPos();
	IMPORT_C void DecYPos();
	IMPORT_C void IncXPos();
	IMPORT_C void IncYPos();
private:
	void DoBegin(const TPoint& aPosition,const TBitmapUtil* aUtil);
private:
	CFbsBitmap* iFbsBitmap;
	TUint32* iWordPos;
	TUint32* iMinWordPos;
	TUint32* iMaxWordPos;
	TInt iBpp;
	TInt iPixelShift;
	TInt iBitShift;
	TUint32 iMask;
	TInt iScanlineWordLength;
	TBool iHeapLocked;
	};

class TFontInfo;

/** 
Font and bitmap server typeface store. 
@publishedAll 
@released
*/
class CFbsTypefaceStore : public CTypefaceStore
	{
public:
	IMPORT_C static CFbsTypefaceStore* NewL(CGraphicsDevice* aDevice);
	IMPORT_C ~CFbsTypefaceStore();
	IMPORT_C TInt AddFile(const TDesC& aName,TInt& aId);
	IMPORT_C TInt InstallFile(const TDesC& aName,TInt& aId);
	IMPORT_C void RemoveFile(TInt aId=0);
#ifndef SYMBIAN_HIDE_FONT_METRICS_V1
	IMPORT_C virtual TInt GetNearestFontInTwips(CFont*& aFont, const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont*& aFont, const TFontSpec& aFontSpec);
#endif
#ifdef SYMBIAN_FONT_METRICS_V2
	IMPORT_C virtual TInt GetNearestFontToDesignHeightInTwips(CFont*& aFont, const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontToDesignHeightInPixels(CFont*& aFont, const TFontSpec& aFontSpec);
	IMPORT_C virtual TInt GetNearestFontToMaxHeightInTwips(CFont*& aFont, const TFontSpec& aFontSpec, TInt aMaxHeight);
	IMPORT_C TInt GetNearestFontToMaxHeightInPixels(CFont*& aFont, const TFontSpec& aFontSpec, TInt aMaxHeight);
#endif
	IMPORT_C TInt GetFontById(CFont *&aFont,TUid aUid,const TAlgStyle& aAlgStyle);
	IMPORT_C virtual TInt NumTypefaces() const;
	IMPORT_C virtual void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const;
	IMPORT_C virtual TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C TGlyphBitmapType DefaultBitmapType() const;
	IMPORT_C void SetDefaultBitmapType(TGlyphBitmapType aType) const;
	IMPORT_C void SetFontNameAliasL(const TDesC& aFontAlias,const TDesC& aFontName) const;
	IMPORT_C static void RemoveFontFileLocksL(); // Deprecated - Unload all fonts loaded from RAM or removable media
	IMPORT_C static void RemoveFontFileLocksL(const TDesC& aDrive, TBool aAllFonts); // Unload all fonts (of specified type) loaded from named drive
	IMPORT_C static void RemoveFontFileLocksL(const TDesC& aFileName); // Unload the named font file
private:
	CFbsTypefaceStore(CGraphicsDevice* aDevice);
	TInt CreateFont(CFont*& aFont,const TFontInfo& aFontInfo);
	TInt FontHeight(TInt aTypefaceIndex,TInt aHeightIndex,TInt aMessage) const;
	void SetSize() const;
	TInt GetNearestFontInTwipsL(CFont*& aFont,const TFontSpec& aFontSpec);
#ifdef SYMBIAN_FONT_METRICS_V2
	TInt GetNearestFontToDesignHeightInTwipsL(CFont*& aFont,const TFontSpec& aFontSpec);
#endif
private:
	RFbsSession* iFbs;
	CGraphicsDevice* iDevice;
	CFontCache* iTwipsCache;
	};

class CDitherColor256;

/** 
Copies a bitmap in any display mode of at least 256 colours into a 256 
colour bitmap, optionally using a user-defined palette. 
@publishedAll 
@released
*/
class CFbsColor256BitmapUtil : public CBase
	{
public:
	/** Indicates whether or not to use dithering. */
	enum TDither
		{
		/** No dithering. */
		ENoDither,
		/** Use the Floyd-Steinberg dithering algorithm. */
		EFloydSteinberg
		};
public:

	IMPORT_C static CFbsColor256BitmapUtil* NewL(const CPalette* aPalette);

	IMPORT_C TInt CopyBitmap(CFbsBitmap* aColor256Destination,CFbsBitmap* aSource,TDither aDither=ENoDither);

	~CFbsColor256BitmapUtil();
private:
	CFbsColor256BitmapUtil();
private:
	TColor256Util* iColor256Util;
	CDitherColor256* iDither;
	};

#endif
