// ImageCodecData.h - data used by standard codecs
//
// Copyright (c) 2001-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __IMAGECODECDATA_H__
#define __IMAGECODECDATA_H__

#include <gdi.h>
#include <ezcompressor.h>
#include <ICL\ImageData.h>

class CFrameImageData;

/** 
 * Identification UIDs for TFrameDataBlock-derived classes 
 */

/** @publishedAll */
const TUid KGIFImageDescriptorUid = { 0x101F45E4 };
/** @publishedAll */
const TUid KGIFColorTableUid = { 0x101F7C0A };
/** @publishedAll */
const TUid KGIFLZWInfoUid = { 0x101F45E5 };
/** @publishedAll */
const TUid KGIFImageControlUid = { 0x101F45E6 };
/** @publishedAll */
const TUid KMBMDecodeDataUid = { 0x101F45E0 };
/** @publishedAll */
const TUid KMBMEncodeDataUid = { 0x101F45E9 };
/** @publishedAll */
const TUid KPNGEncodeDataUid = { 0x101F460A };
/** @publishedAll */
const TUid KTIFFImageDataUid = { 0x101F45E8 };


/**
 * Identification UIDs for TImageDataBlock-derived classes 
 */

/** @publishedAll */
const TUid KBMPImageDataUid = { 0x101F45BF };
/** @publishedAll */
const TUid KBMPCompressionUid = { 0x101F45E3 };
/** @publishedAll */
const TUid KJPGImageDataUid = { 0x101F45DA };
/** @publishedAll */
const TUid KJPGQTableUid = { 0x101F45E1 };
/** @publishedAll */
const TUid KJPGCommentUid = { 0x101F45E2 };
/** @publishedAll */
const TUid KGIFBackgroundColorUid = { 0x101F45DE };
/** @publishedAll */
const TUid KGIFCommentUid = { 0x101F45E7 };

/**
 * @publishedAll
 *
 * Max number of GIF palatte entries 
 */
const TInt KGifColorTableMaxEntries = 256;

/**
 * @publishedAll
 * @released
 *
 * BMP specific image data variant which holds bits per pixel info.
 * It is only used when configuring the BMP encoder.
 *
 */
class TBmpImageData : public TImageDataBlock
	{
public:
	IMPORT_C TBmpImageData();

public:
	/** The number of bits pixel */
	TInt iBitsPerPixel;

private:
	TImageDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 * @released
 *
 * BMP specific image data variant which holds compression info.
 * It is only used when extracting info from the BMP decoder.
 *
 */
class TBmpCompression : public TImageDataBlock
	{
public:
	IMPORT_C TBmpCompression();

public:
	/**
	 * Flag reflecting the compression type.
	 */
	enum TCompression
	{
	/** No compression used */
	ENone,

	/** Eight bits per pixel run length encoding */
	EEightBppRLE,

	/** Four bits per pixel run length encoding */
	EFourBppRLE,

	/** Unused */
	EBitFields
	};

public:
	/**
	 * @see enum TCompression
	 *
	 * The type of compression used 
	 */
	TCompression iCompression;

private:
	TImageDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};


/**
 * @publishedAll
 * @released
 *
 * JPEG specific image data variant which holds color sampling and quality
 * factor info. It can be used with both the JPEG decoder and encoder.
 *
 */
class TJpegImageData : public TImageDataBlock
	{
public:
	/**
	 * Flag reflecting the color sampling type 
	 */
	enum TColorSampling
		{
		/** Monochrome */
		EMonochrome,

		/** Color420 */
		EColor420,

		/** Color422 */
		EColor422,

		/** Color444 */
		EColor444
		};
public:
	IMPORT_C TJpegImageData();

public:
	/**
	 * @see enum TColorSampling
	 *
	 * The color sampling scheme to use 
	 */
	TColorSampling iSampleScheme;

	/** The quality factor. Range is 0 to 100 inclusive */
	TInt iQualityFactor; 

private:
	TImageDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 *
 * @see class TJpegQTable
 *
 * The number of JPEG Q table entries 
 */
const TInt KJpgQTableEntries = 64;

/**
 * @publishedAll
 * @released
 *
 * JPEG specific image data variant which holds QTable info.
 * It can be used with both the JPEG decoder and encoder.
 *
 */
class TJpegQTable : public TImageDataBlock
	{
public:
	/**
	 * Flag reflecting the type of Q table
	 */
	enum TQTableIndex 
		{
		/** Luminence table */
		ELumaTable = 0,

		/** Chroma table */
		EChromaTable = 1 
		};
public:
	IMPORT_C TJpegQTable();

public:
	/** The type of queue table */
	TInt iTableIndex;

	/** The data in the Q table */
	TBuf8<KJpgQTableEntries> iEntries;

private:
	TImageDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 * @released
 *
 * JPEG specific image data variant which holds JPEG comment info.
 * It can be used with both the JPEG decoder and encoder.
 *
 */
class TJpegComment : public TImageDataBlock
	{
public:
	IMPORT_C TJpegComment();

public:
	/** The JPEG comment to set/query */
	HBufC8* iComment;

private:
	TImageDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};


/**
 * @publishedAll
 * @released
 *
 * GIF specific image data variant which holds background color info.
 * It can only be used with the GIF decoder (the encoder is not configurable).
 *
 */
class TGifBackgroundColor : public TImageDataBlock
	{
public:
	IMPORT_C TGifBackgroundColor();

public:
	/** The background colour as an index */
	TInt iBackgroundColorIndex;

	/** The background colour as an RGB value */
	TRgb iBackgroundColor;

private:
	TImageDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 * @released
 *
 * GIF specific frame data variant which holds image descriptor info.
 * It can only be used with the GIF decoder (the encoder is not configurable).
 *
 */
class TGifImageDescriptor : public TFrameDataBlock
	{
public:
	IMPORT_C TGifImageDescriptor();

public:
	/** Frame has its own local colour map */
	TBool iLocalColorMap;

	/** Frame's local colour map is sorted in priority order */
	TBool iSortedLocalMap;

	/** Flag indicating if the image is interlaced */
	TBool iInterlaced;

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 * @released
 *
 * GIF specific frame data for saving a frame local color map (palette).
 *
 */
class TGifColorTable : public TFrameDataBlock
	{
public:
	IMPORT_C TGifColorTable();

public:
	TRgb iPalette[KGifColorTableMaxEntries];

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};
	
/**
 * @publishedAll
 * @released
 *
 * GIF specific frame data variant which holds LZW compression info.
 * It can only be used with the GIF decoder (the encoder is not configurable).
 *
 */
class TGifLZWInfo : public TFrameDataBlock
	{
public:
	IMPORT_C TGifLZWInfo();

public:
	/** Initial number of bits used in LZW compression */
	TInt iInitialCodeLength;

	/** Size of compressed frame */
	TInt iCompressedBytes;

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 * @released
 *
 * GIF specific frame data variant which holds GIF image control info.
 * It can only be used with the GIF decoder (the encoder is not configurable).
 *
 */
class TGifImageControl : public TFrameDataBlock
	{
public:
	/**
	 * Flag reflecting how the previous frame is handled when
	 * the next frame is drawn.
	 */
	enum TDisposalMethod
		{
		/** No method set */
		ENone = 0,

		/** Leave the previous frame in place */
		ELeaveInPlace = 1,

		/** Restore to the backgound colour */
		ERestoreToBackground = 2,

		/** Restore the previous frame */
		ERestoreToPrevious = 3
		};

public:
	IMPORT_C TGifImageControl();

public:
	/** The interval between display of successive frames */
	TInt iDelayTimeInCentiseconds;

	/** The colour index to be used for transparency */
	TInt iTransparentColorIndex;

	/** Flag indicating if user input is required before display of next frame. */
	TBool iUserInputFlag;

	/** The frame disposal method for multiframe images */
	TDisposalMethod iDisposalMethod;

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 * @released
 *
 * GIF specific image data variant which holds GIF comment info.
 * It can only be used with the GIF decoder (the encoder is not configurable).
 *
 */
class TGifComment : public TImageDataBlock
	{
public:
	IMPORT_C TGifComment();

public:
	/** The GIF comment to set/query */
	HBufC8* iComment;

private:
	TImageDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};


// Mbm compression data. (Decoder only)
/**
 * @publishedAll
 * @released
 *
 * MBM specific frame data variant which holds frame data info.
 * It can only be used with the MBM decoder.
 *
 */
class TMbmDecodeData : public TFrameDataBlock
	{
public:
	IMPORT_C TMbmDecodeData();

public:
	/** Flag indicating if RLE compression is used */
	TBool iCompressed;

	/** The frame size in bytes */
	TInt iImageDataSizeInBytes;

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};


// Mbm display mode. (Encoder only)
/**
 * @publishedAll
 * @released
 *
 * MBM specific image data variant which holds frame data info.
 * It can only be used with the MBM encoder.
 *
 */
class TMbmEncodeData : public TFrameDataBlock
	{
public:
	IMPORT_C TMbmEncodeData();

public:
	/** The display mode */
	TDisplayMode iDisplayMode;

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};


/**
 * @publishedAll
 * @released
 *
 * PNG specific frame data variant which holds PNG encoding info.
 * It can only be used with the PNG encoder.
 *
 */
class TPngEncodeData : public TFrameDataBlock
	{
public:
	// Same values as CEZCompressor
	/**
	 * Flag reflecting the level of compression used
	 */
	enum TPngCompressLevel
		{
		/** Default compression used */
		EDefaultCompression = Z_DEFAULT_COMPRESSION,

		/** No compression used */
		ENoCompression = Z_NO_COMPRESSION,

		/** Optimise compression for speed */
		EBestSpeed = Z_BEST_SPEED,

		/** Optimise compression for size */
		EBestCompression = Z_BEST_COMPRESSION
		};
public:
	IMPORT_C TPngEncodeData();

public:
	/** Number of bits per pixel */
	TInt iBitsPerPixel;

	/** Flag indicating color or grayscale */
	TBool iColor;

	/** Flag indicating palette or RGB */ 
	TBool iPaletted;

	/** Level of compression */
	TPngCompressLevel iLevel; 

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/**
 * @publishedAll
 * @released
 *
 * TIFF specific frame data variant.
 * It can only be used with the TIFF decoder.
 *
 */
class TTiffImageData : public TFrameDataBlock
	{
public:
	IMPORT_C TTiffImageData();

public:
	/** New subfile type */
	TUint32				iNewSubfileType;

	/** Frame size in pixels */
	TSize				iSizeInPixels;

	/** Number of bits per sample */
	TInt				iBitsPerSample;

	/** Number of samples per pixel */
	TInt				iSamplesPerPixel;

	/** Compression */
	TInt				iCompression;

	/** T4 options */
	TInt				iT4Options;

	/** T6 options */
	TInt				iT6Options;

	/** Photometric Interpretation */
	TInt				iPhotometricInterpretation;

	/** Fill order */
	TInt				iFillOrder;

	/** Frame width in twips */
	TReal				iWidthInTwips;

	/** Frame height in twips */
	TReal				iHeightInTwips;

	/** Number of rows per strip */
	TInt				iRowsPerStrip;

	/** The number of TTiffImageStrip */
	TInt				iNumStrips;

	/** Array of TTiffImageStrip's */
	HBufC8*				iStripInfo; 

private:
	TFrameDataBlock* DuplicateL(CFrameImageData& aFrameImageData) const;
	};

/** 
 * Identification UIDs for image types. 
 */

/** @publishedAll */
const TUid KImageTypeBMPUid = {0x101F45B0};
/** @publishedAll */
const TUid KImageTypeGIFUid = {0x101F45B3};
/** @publishedAll */
const TUid KImageTypeWMFUid = {0x101F45BA};
/** @publishedAll */
const TUid KImageTypeWMFSubTypeStdUid = {0x101F45BB};
/** @publishedAll */
const TUid KImageTypeWMFSubTypeApmUid = {0x101F45BC};
/** @publishedAll */
const TUid KImageTypeWMFSubTypeClpUid = {0x101F45BD};
/** @publishedAll */
const TUid KImageTypeTIFFUid = {0x101F45C4};
/** @publishedAll */
const TUid KImageTypeTIFFSubTypeLittleEndianUid = {0x101F45C5};
/** @publishedAll */
const TUid KImageTypeTIFFSubTypeBigEndianUid = {0x101F45C6};
/** @publishedAll */
const TUid KImageTypePNGUid = {0x101F45C9};
/** @publishedAll */
const TUid KImageTypeMBMUid = {0x101F45CC};
/** @publishedAll */
const TUid KImageTypeWBMPUid = {0x101F45CF};
/** @publishedAll */
const TUid KImageTypeOTAUid = {0x101F45D2};
/** @publishedAll */
const TUid KImageTypeICOUid = {0x101F45D5};
/** @publishedAll */
const TUid KImageTypeJPGUid = {0x101F45D8};

#endif // __IMAGECODECDATA_H__

