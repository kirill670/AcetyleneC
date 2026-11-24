// BITMAP.H
//
// Copyright (c) 1995-2004 Symbian Ltd. All rights reserved.
//

#if !defined(__BITMAP_H__)
#define __BITMAP_H__
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
/**
@internalComponent
*/
const TUid KCBitwiseBitmapUid={268435520};
const TUid KCBitwiseBitmapHardwareUid={0x10009a3d};
const TUid KMultiBitmapFileImageUid={268435522};
const TInt KMaxLargeBitmapAlloc=0x1000;
const TInt KCompressionBookMarkThreshold=0x2000;

//Forward declarations
class CChunkPile;
class TCompressionBookMark;

/** 
Defines the types of file compression. 
@publishedAll
@released
*/
enum TBitmapfileCompression
	{
	/** Bitmap file is not compressed. */
	ENoBitmapCompression,
	/** File is compressed using run-length encoding compression. */
	EByteRLECompression,
	/** File is compressed using twelve bit run-length encoding compression. */
	ETwelveBitRLECompression,
	/** File is compressed using sixteen bit run-length encoding compression. */
	ESixteenBitRLECompression,
	/** File is compressed using twenty four bit run-length encoding compression. */
	ETwentyFourBitRLECompression,
	//Insert new enum items here!
	ERLECompressionLast
	};

class TRgb24bit
/**
@internalComponent
*/
	{
public:
	TUint8 iRed;
	TUint8 iGreen;
	TUint8 iBlue;
	};

/** 
Contains information about the bitmap when streaming bitmaps to stores. 
@publishedAll
@released
*/
class SEpocBitmapHeader
	{
public:
	/** The size of the bitmap data, in bytes. */
	TInt iBitmapSize;
	/** The size of the structure in which the bitmap data is stored. */
	TInt iStructSize;
	/** The size of the bitmap, in pixels. */
	TSize iSizeInPixels;
	/** The size of the bitmap, in twips. */
	TSize iSizeInTwips;
	/** The bitmap's number of bits per pixel */
	TInt iBitsPerPixel;
	/** Whether or not the bitmap is colour. A true value means that the bitmap is 
	colour. */
	TBool iColor;
	/** The number of entries in the bitmap's palette. */
	TInt iPaletteEntries;
	/** The type of compression used to store the bitmap. */
	TBitmapfileCompression iCompression;
	};

class TLineScanningPosition
/**
@internalTechnology
*/
	{
public:
	TLineScanningPosition(TUint32* aSrcDataPtr): iSrcDataPtr((TUint8*)aSrcDataPtr), iCursorPos(0), iScanLineBuffer(NULL) {}
public:
	TUint8* iSrcDataPtr;
	TInt iCursorPos;
	HBufC8* iScanLineBuffer;
	};

class CShiftedFileStore;
/**
BitGdi bitmap class (pseudo-CXxx class).
@publishedAll
@deprecated CFbsBitmap should be used instead.
*/
class CBitwiseBitmap
	{
	friend class CFbTop;
	friend class CFbClient;
	friend class CFbsBitmap;
	friend class CBitmapObject;
	friend class CFbsBitmapAsyncStreamer;
public:
	IMPORT_C TUid Uid() const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const CFbsBitmap& aHandleBitmap) const;
	IMPORT_C void ExternalizeRectangleL(RWriteStream& aStream,const TRect& aRect,const CFbsBitmap& aHandleBitmap) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C static void InternalizeHeaderL(RReadStream& aStream,SEpocBitmapHeader& aHeader);
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C void GetPixel(TRgb& aColor,const TPoint& aPos,TUint32* aBase) const;
	IMPORT_C TInt GetScanLinePtr(TUint32*& aSlptr, TPoint& aPixel,TInt aLength, TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	IMPORT_C TInt GetScanLinePtr(TUint32*& aSlptr, TInt& aLength, TPoint& aPixel,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	IMPORT_C void GetScanLine(TUint32*& aSlptr, TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode) const;
	IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase) const;
	IMPORT_C void GetVerticalScanLine(TDes8& aBuf,TInt aX,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase) const;
	IMPORT_C void StretchScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase) const;
	IMPORT_C void StretchScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	IMPORT_C TUint32* ScanLineAddress(TUint32* aBase,TUint aY) const;
	IMPORT_C TBool IsMonochrome(TUint32* aBase) const;
	IMPORT_C void Compress(TUint8* aNewData,TUint8* aOldData);
	IMPORT_C TBool IsLargeBitmap() const;
	IMPORT_C TInt CompressData();
	IMPORT_C void SetCompressionBookmark(TLineScanningPosition& aLineScanningPosition, TUint32* aBase, const CFbsBitmap* aFbsBitmap);
	IMPORT_C TInt HardwareBitmapHandle() const;
	IMPORT_C TBool IsCompressedInRAM() const;
private:
	IMPORT_C void operator delete(TAny*);
	IMPORT_C CBitwiseBitmap(RHeap* aHeap,CChunkPile* aPile);
	IMPORT_C ~CBitwiseBitmap();
	IMPORT_C void Reset();
	IMPORT_C TInt Construct(const TSize& aSize,TDisplayMode aDispMode,TUid aCreatorUid);
	IMPORT_C void ConstructL(RFs& aFs,const TDesC& aFilename,TInt32 aId,TUint aFileOffset);
	IMPORT_C void ConstructL(RFile& aFile,TInt32 aId,TUint aFileOffset);
	IMPORT_C void ConstructL(CShiftedFileStore* aFileStore,TStreamId aStreamId);
	IMPORT_C TInt Resize(const TSize& aSize);
private:
	void GenerateLineFromCompressedTwelveBitData(TUint8* aDestBuffer, const TPoint& aPixel,TInt aLength,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	void GenerateLineFromCompressedEightBitData(TUint8* aDestBuffer, const TPoint& aPixel,TInt aLength,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	TUint8 GetGrayPixelEx(TInt aX,TUint32* aScanLineAddress) const;
	TRgb GetRgbPixelEx(TInt aX,TUint32* aScanLineAddress) const;
	void GetRgbPixelExMany(TInt aX,TUint32* aScanlinePtr,TUint32* aDest,TInt aLength) const;
    void GetRgbPixelExMany16M(TInt aX,TUint32* aScanlinePtr,TUint8* aDest,TInt aLength) const;
	void GetScanLineGray2(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TUint32* aScanlinePtr) const;
	void GetScanLineGray4(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TUint32* aScanlinePtr) const;
	void GetScanLineGray16(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineGray256(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor16(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor256(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor4K(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor64K(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor16M(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor16MU(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColorRgb(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineExBits(TDes8& aBuf,TInt aX,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineExBytes(TDes8& aBuf,TInt aX,TInt aLength,TUint32* aScanlinePtr) const;
	void DoExternalizeDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeByteDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeTwelveBitDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeSixteenBitDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeTwentyFourBitDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfByteDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfTwelveBitDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfSixteenBitDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfTwentyFourBitDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TBool TrueColorPointerCompare(TUint8* aColorPointer,TUint8 aComponent1,TUint8 aComponent2,TUint8 aComponent3) const;
	void DoInternalizeL(RReadStream& aStream,TInt aSrceSize,TUint32* aBase);
	void DoInternalizeCompressedDataL(RReadStream& aStream,TInt aSrceSize,TUint32* aBase,TBitmapfileCompression aCompression);
	void DoDecompressByteData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);

	void DoDecompressByteDataAltL(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoDecompressTwelveBitData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);
	void DoDecompressTwelveBitDataAltL(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoDecompressSixteenBitData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);
	void DoDecompressSixteenBitDataAltL(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoDecompressTwentyFourBitData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);
	void DoDecompressTwentyFourBitDataAltL(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoStretchScanLine(TDes8& aBuf,TInt x,TInt y,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase,TLineScanningPosition& aLineScanningPosition) const;
	void DoCompressScanLine(TDes8& aBuf,TInt x,TInt y,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase,TLineScanningPosition& aLineScanningPosition) const;
	TUint32 HashTo1bpp(TUint32 aGray256,TBool aOddX,TBool aOddY) const;
	TUint32 HashTo2bpp(TUint32 aGray256,TInt aDitherIndex) const;
	TBool IsWordMonochrome(TUint32 aWord) const;
	TUint32* DataAddress() const;
	static void WhiteFill(TUint8* aData,TInt aDataSize,TDisplayMode aDispMode);
	static TInt ByteWidth(TInt aPixelWidth,TDisplayMode aDispMode);
	static TInt Bpp(TDisplayMode aDispMode);
	static TBool IsColor(TDisplayMode aDispMode);
	static TDisplayMode DisplayMode(TInt aBpp,TBool aColor);
	static TBitmapfileCompression CompressionType(TInt aBpp);
	TInt DoGetScanLinePtr(TUint32*& aSlptr, TPoint& aPixel,TInt aLength, TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	void GenerateLineFromCompressedSixteenBitData(TUint8* aDestBuffer, const TPoint& aPixel,TInt aLength, TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	TDisplayMode InitialDisplayMode() const;
	TInt SetDisplayMode(TDisplayMode aDisplayMode, TUint32* aDataAddress);
	TInt DisplayModeArgCheck(TDisplayMode aDisplayMode, TUint32* aDataAddress) const;
	void ChangeDisplayMode( TDisplayMode aNewDisplayMode,
							TInt aScanLineWidthNew,
							TUint8* aDataAddrNew,
							TUint32* aDataAddress,
							TInt aYStart,
							TInt aYInc,
							TInt aYEnd);
	void UpdateBitmapProperties(TDisplayMode aNewDisplayMode);
	TInt SwapWidthAndHeight(TUint32* aDataAddress);
	void CopyOldData(TUint8* aDest, const TUint8* aSrc, TInt aNewByteWidth, const TSize aNewSize);
	void DecompressOldData(TUint8* aDest, TInt aNewByteWidth, const TSize aNewSize, HBufC8* aScanLineBuf);
	TInt ResizeConditionsCheck(const TSize& aSize, TInt aNewByteWidth, TInt& aNewBitmapSize) const;
	TInt Alloc(TInt aNewBitmapSize, const TSize& aNewSize, TUint8*& aNewBuf, TInt& aNewDataOffset);
	void MoveData(TUint8* aDest, TUint8* aSrc, TInt aNewByteWidth, const TSize& aNewSize, HBufC8* aScanLineBuf);
	void ReinitializeHeader(const TSize& aNewSize, TInt aNewBitmapSize);
	void Free(TUint8* aSrc, TBool aLargeBmp, HBufC8* aScanLineBuf);
	void GenerateLineFromCompressed24BitData(TUint8* aDestBuffer, const TPoint& aPixel,TInt aLength, TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	void AdjustXCoord(TInt& aX) const;
	void GetLineScanPos(TLineScanningPosition& aLineScanPos, 
						const TCompressionBookMark*& aComprBookMark, 
						const TUint8* aBase) const;
	void UpdateBookMark(const TLineScanningPosition& aLineScanPos, 
						TCompressionBookMark* aComprBookMark, 
						const TUint8* aBase) const;
#ifdef SYMBIAN_GRAPHICS_ALPHA_SUPPORT_V1
	void GetScanLineColor16MA(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
#endif
private:
	TUid iUid;
	struct TSettings
		{
		TSettings(TDisplayMode aDisplayMode);
		void SetDisplayModes(TDisplayMode aDisplayMode);
		void SetCurrentDisplayMode(TDisplayMode aDisplayMode);
		TDisplayMode CurrentDisplayMode() const;
		TDisplayMode InitialDisplayMode() const;
		void SetInitialByteWidth(TInt aByteWidth);
		TInt InitialByteWidth() const;
		TUint32 iData;
		} iSettings;
	RHeap* iHeap;
	CChunkPile* iPile;
	TInt iByteWidth;
	SEpocBitmapHeader iHeader;
	RChunk iLargeChunk;
	TInt iDataOffset; // offset from "this" in bytes
	TBool iIsCompressedInRAM; //flag indicating whether CompressData has been called
	};

#endif
