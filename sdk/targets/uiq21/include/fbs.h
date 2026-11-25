// FBS.H
//
// Copyright (C) 1995-2001 Symbian Ltd. All rights reserved.
//

#ifndef __FBS_H__
#define __FBS_H__

#include <e32std.h>
#include <gdi.h>
#include <fntstore.h>
#include <bitmap.h>

const TUid KCFbsFontUid = { 268435518 };
const TUid KMultiBitmapRomImageUid = { 268435521 };
const TUint32 KFontBitmapServerUidValue = 0x10003a16;
const TUid KFontBitmapServerUid = { KFontBitmapServerUidValue };

IMPORT_C TInt FbsStartup();

/**
 *
 * Character width and adjustments information.
 * @since 5.0
 * @lib "N/A"
 */
class SCharWidth
	{
public:
	TInt iLeftAdjust;
	TInt iRightAdjust;
	TInt iMove;
	TInt iWidth;
	};

class CFbsRalCache;

/**
 *
 * A session with the Font and Bitmap Server.
 * @since 5.0
 * @lib "fbscli.lib"
 */
class RFbsSession : protected RSessionBase
	{
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
	IMPORT_C TVersion Version();
	IMPORT_C TUint8* HeapBase() const;
	TInt SessionHandle() const { return Handle(); }
	TInt ScanLineBuffer(HBufC8*& aBuffer,TInt aSize);
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
 *
 * Font managed by the font and bitmap server.
 *
 * <code>CFbsFont</code> objects are used for screen and off-screen
 * bitmap fonts. They are usually obtained by calls to the
 * <code>CBitmapDevice::GetNearestFontInPixels()</code> and
 * <code>MGraphicsDeviceMap::GetNearestFontInTwips()</code> functions.The
 * class is derived from the abstract base class <code>CFont</code>, and
 * implements a number of functions defined in it.
 *
 * @since 5.0
 * @lib "fbscli.lib"
 */
class CFbsFont: public CFont
	{
	friend class CFbsTypefaceStore;
public:
	// From CFont
/**
 *
 * Gets the font's UID.
 *
 * All <code>CFbsFont</code> objects have the constant UID
 * <code>KCFbsFontUid</code>. It is safe to cast from <code>CFont*</code>
 * to <code>CFbsFont*</code> if <code>CFont::TypeUid()</code> returns
 * <code>KCFbsFontUid</code>.
 *
 * @returns   "TUid"
 *            The font's UID. This should be
 *            <code>KCFbsFontUid</code>.
 */
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
 *
 * A bitmap managed by the Font and Bitmap server.
 *
 * The class also defines some palette API functions. This functionality
 * is not currently supported.
 *
 * @since 5.0
 * @lib "fbscli.lib
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
	IMPORT_C TInt Create(const TSize& aSizeInPixels,TDisplayMode aDispMode);
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C TBool IsRomBitmap() const;
	IMPORT_C void SetRomBitmapL(CBitwiseBitmap* aRomBitmapPointer,TInt& aBitmapSizeInBytes);
	IMPORT_C TInt Load(const TDesC& aFileName,TInt32 aId=0,TBool aShareIfLoaded=ETrue);
	IMPORT_C TInt LoadAndCompress(const TDesC& aFileName,TInt32 aId=0,TBool aShareIfLoaded=ETrue);
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
protected:
    IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,const TPoint& aDitherOffset,TDisplayMode aDispMode) const;
	CBitwiseBitmap* Address() const;
	void DoSaveL(RFile& aFile);
	TInt DoCreate(const TSize& aSizeInPixels,TDisplayMode aDispMode,TUid aCreatorUid);
protected:
	RFbsSession* iFbs;
	CBitwiseBitmap* iAddressPointer;
	CBitwiseBitmap* iRomPointer;
	TInt iHandle;
	TInt iServerHandle;
	};

class CDirectFileStore;

/** Deprecated - do not use.
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
 *
 * Provides fast read/write access to the image data of a bitmap.
 *
 * Functionality includes the getting and setting of the individual
 * pixels of a bitmap. Common to this is the concept of the current pixel
 * position. Position is held as member data and is changed by using
 * various efficient functions. For example, incrementing the positions
 * x- or y co-ordinate is much quicker than setting a completely new
 * position. This efficiency issue is important as these functions are
 * used as part of the frequently used blitting DDA used for creating
 * stretched or compressed versions of bitmaps.Due to the defragmentation
 * process that is used to compress the FBSRV heap, bitmaps may be moved
 * in memory at any time including whilst the bitmaps contents are being
 * manipulated. Therefore, operations to lock and unlock the heap
 * preventing and allowing the heap to be compressed are provided. The
 * use of these functions, surrounding any calls to the other member
 * functions ensures that the simplicity, and efficiency, of these
 * functions is maximised.
 *
 * @since 5.0
 * @lib "fbscli.lib"
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
 *
 * Font and bitmap server typeface store.
 * @since 5.0
 * @lib "fbscli.lib"
 */
class CFbsTypefaceStore : public CTypefaceStore
	{
public:
	IMPORT_C static CFbsTypefaceStore* NewL(CGraphicsDevice* aDevice);
	IMPORT_C ~CFbsTypefaceStore();
	IMPORT_C TInt AddFile(const TDesC& aName,TInt& aId);
	IMPORT_C TInt InstallFile(const TDesC& aName,TInt& aId);
	IMPORT_C void RemoveFile(TInt aId=0);
	IMPORT_C virtual TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont*& aFont,const TFontSpec& aFontSpec);
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
private:
	RFbsSession* iFbs;
	CGraphicsDevice* iDevice;
	CFontCache* iTwipsCache;
	};

class CDitherColor256;

/**
 *
 * Performs operations with EColor256 bitmaps using a definable palette.
 *
 * @since 6.1
 * @lib "fbscli.lib"
 */
class CFbsColor256BitmapUtil : public CBase
	{
public:
/**
 *
 * Possible states for dithering.
 *
 * @since 6.1
 */
	enum TDither
		{
/** No dithering.
 */
		ENoDither,
/** Floyd-Steinberg dithering (for improved appearance).
 */
		EFloydSteinberg
		};
public:
/** 
 *
 * Static factory function.
 * 
 * @param     "const CPalette* aPalette"
 *            Optional colour palette to use for conversions
 *            (default is to use standard EColor256 palette).
 * @returns   "CFbsColor256BitmapUtil*"
 *            Fully constructed object.
 */
	IMPORT_C static CFbsColor256BitmapUtil* NewL(const CPalette* aPalette);
/** 
 *
 * Copy the contents of a bitmap to an EColor256 bitmap with optional dithering.
 * 
 * Bitmaps must be of the same size and the destination must have display mode
 * EColor256 or a panic will occur.
 *
 * @param     "CFbsBitmap* aColor256Destination"
 *            Destination EColor256 bitmap.
 * @param     "CFbsBitmap* aSource"
 *            Source bitmap - may be any mode.
 * @param     "TDither aDither=ENoDither"
 *            Dither mode to use - defaults to none.
 * @returns   "TInt"
 *            Error code.
 */
	IMPORT_C TInt CopyBitmap(CFbsBitmap* aColor256Destination,CFbsBitmap* aSource,TDither aDither=ENoDither);

/** Destructor.
 */
	~CFbsColor256BitmapUtil();
private:
	CFbsColor256BitmapUtil();
private:
	TColor256Util* iColor256Util;
	CDitherColor256* iDither;
	};

#endif
