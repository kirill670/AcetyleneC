// ImageProcessor.h
// Copyright (c) 1998-2002 Symbian Ltd
//

#ifndef ___IMAGEPROCESSOR_H__
#define ___IMAGEPROCESSOR_H__

#include <gdi.h>
#include <fbs.h>

/**
 * @publishedAll
 * @released
 */
enum TImageBitmapUtilPanic
	{
	ECorrupt
	};

/**
 * @publishedAll
 * @released
 *
 * Interface to colour conversion classes for various display modes.
 * Manages the mapping between RGB/Greyscale values and the index
 * into the color palette for the given display mode.
 *
 */
class TColorConvertor
	{
public:
	IMPORT_C static	TColorConvertor* NewL(TDisplayMode aDisplayMode);

	/**
	 *
	 * Ask for the colour index corresponding to the supplied RGB value.
	 * Operates in the context of the current display mode.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param   "aColor"
	 *          Colour in RGB format.
	 * @return  Colour index.
	 */
	virtual TInt ColorIndex(TRgb aColor) const = 0;

	/**
	 *
	 * Ask for the RGB value corresponding to the supplied colour index.
	 * Operates in the context of the current display mode.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param   "aColorIndex"
	 *          Colour in RGB format.
	 * @return  Rgb value.
	 */
	virtual TRgb Color(TInt aColorIndex) const = 0;

	/**
	 *
	 * Gets an array of colour indices from a corresponding array of RGB values.
	 * Operates in the context of the current display mode. 
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aIndexBuffer"
	 *          Pointer to the first element in destination array.
	 * @param	"aColorBuffer"
	 *          Pointer to the first element in the source array.
	 * @param	"aCount"
	 *          The number of elements to get.
	 */
	virtual void ColorToIndex(TInt* aIndexBuffer,TRgb* aColorBuffer,TInt aCount) const = 0;

	inline static TInt RgbToMonochrome(TRgb aRgb);
	};


/**
 * @publishedAll
 * @released
 *
 * Bitmap utility class.
 *
 */
class TImageBitmapUtil
	{
public:
	IMPORT_C TImageBitmapUtil();
	IMPORT_C void Begin();
	IMPORT_C TBool Begin(const TPoint& aPosition);
	IMPORT_C void End();
	IMPORT_C void SetBitmapL(CFbsBitmap* aBitmap);
	IMPORT_C void SetPixel(TUint32 aPixelIndex);
	IMPORT_C void SetPixels(TUint32* aPixelIndex,TInt aNumberOfPixels);
	IMPORT_C TBool SetPos(const TPoint& aPosition);
private:
	union TDataPointer
		{
		TUint32* iWordPos;
		TUint8* iBytePos;
		};
private:
	CFbsBitmap* iBitmap;
	TSize iSize;
	TPoint iPosition;
	TDataPointer iData;
	TDataPointer iBase;
	TInt iBpp;
	TInt iBppShift;
	TInt iPixelShift;
	TInt iPixelsPerWord;
	TInt iBitShift;
	TInt iScanlineWordLength;
	TUint32 iMask;
	TBool iWordAccess;
	};


class CImageProcessor;

/**
 * @publishedAll
 * @released
 *
 * Utility class providing static factory functions for creating instances of 
 * CImageProcessor derived classes.
 *
 */
class ImageProcessorUtility
	{
public:
	IMPORT_C static TInt ReductionFactor(const TSize& aOriginalSize,const TSize& aReducedSize);
	IMPORT_C static CImageProcessor* NewImageProcessorL(const CFbsBitmap& aBitmap,const TSize& aImageSize,TDisplayMode aImageDisplayMode, TBool aDisableErrorDiffusion);
	IMPORT_C static CImageProcessor* NewImageProcessorL(const CFbsBitmap& aBitmap,TInt aReductionFactor,TDisplayMode aImageDisplayMode, TBool aDisableErrorDiffusion);
	};



/**
 * @publishedAll
 * @released
 *
 * Interface to image processing classes.
 *
 */
class CImageProcessor : public CBase
	{
public:
	// Setup

	/**
	 *
	 * Initialises internal data structures prior to conversion.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param   "aBitmap"
	 *          Reference to a fully constucted bitmap with the required
	 *          display mode and size.
	 * @param   "aImageRect"
	 *          The region of the image to convert.
	 */
	virtual void PrepareL(CFbsBitmap& aBitmap,const TRect& aImageRect) = 0;

	/**
	 *
	 * Overloaded version of the above allowing specification of a block size
	 * for those formats which support blocked pixel data eg. JPEG
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param   "aBitmap"
	 *          Reference to a fully constucted bitmap with the required
	 *          display mode and size.
	 * @param   "aImageRect"
	 *          The region of the image to convert.
	 * @param   "aRgbBlockSize"
	 *          The size of the block to use.
	 */
	virtual void PrepareL(CFbsBitmap& aBitmap,const TRect& aImageRect,const TSize& aRgbBlockSize) = 0;

	/**
	 *
	 * Set the number of pixels by which to increment the current position in 
	 * the Y-axis. This is used when rendering images supporting interlacing.
	 * eg GIF
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aYInc"
	 *          The number of pixels.
	 */
	virtual void SetYPosIncrement(TInt aYInc) = 0;

	/**
	 *
	 * Set the number times the current line should be repeated. The lines
	 * are repeated in the same direction as set by SetYPosIncrement(). This
	 * is used to fill blank lines when rendering interlaced images. eg GIF
	 */
	virtual void SetLineRepeat(TInt aLineRepeat) = 0;

	/**
	 *
	 * Set the pixel padding to aNumberOfPixels.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aNumberOfPixels"
	 *          The value to set pixel padding to.
	 */
	virtual void SetPixelPadding(TInt aNumberOfPixels) = 0;

	// Color pixel writing

	/**
	 *
	 * Set the pixel at the current position to aColor.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aColor"
	 *          The RGB value to set the current pixel to.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 * @post    The current position is updated.
	 */
	virtual TBool SetPixel(TRgb aColor) = 0;

	/**
	 *
	 * Set aCount number of pixels to the value given by aColor, starting at 
	 * the current position.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aColor"
	 *          The RGB value to set the pixels to.
	 * @param	"aCount"
	 *          The number of pixels to set.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 * @post    The current position is updated.
	 */
	virtual TBool SetPixelRun(TRgb aColor,TInt aCount) = 0;

	/**
	 *
	 * Uses the array of colour values supplied by aColorBuffer, whose length
	 * is specified in aBufferLength, to write to the bitmap, starting at the current
	 * position.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aColorBuffer"
	 *          Pointer to the first element in the array.
	 * @param	"aBufferLength"
	 *          The number of elements in the array.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 * @post    The current position is updated.
	 */
	virtual TBool SetPixels(TRgb* aColorBuffer,TInt aBufferLength) = 0;

    /**
	 *
	 * For image types which support blocking of pixels eg JPEG, sets the current
	 * pixel block using the data supplied in aColorBuffer.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aColorBuffer"
	 *          Pointer to a buffer representing a block of pixel color values.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 */
	virtual TBool SetPixelBlock(TRgb* aColorBuffer) = 0;

	// Monochrome pixel writing

	/**
	 *
	 * Set the pixel at the current position to aGray256.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aGray256"
	 *          The greyscale value to set the current pixel to.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 * @post    The current position is updated.
	 */
	virtual TBool SetMonoPixel(TInt aGray256) = 0;

	/**
	 *
	 * Set aCount number of pixels to the value given by aGray256, starting at 
	 * the current position.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aGray256"
	 *          The greyscale value to set the pixels to.
	 * @param	"aCount"
	 *          The number of pixels to set.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 * @post    The current position is updated.
	 */
	virtual TBool SetMonoPixelRun(TInt aGray256,TInt aCount) = 0;

	/**
	 *
	 * Uses the array of colour values supplied by aGray256Buffer, whose length
	 * is specified in aBufferLength, to write to the bitmap, starting at the current
	 * position.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aGray256Buffer"
	 *          Pointer to the first element in the array.
	 * @param	"aBufferLength"
	 *          The number of elements in the array.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 * @post    The current position is updated.
	 */
	virtual TBool SetMonoPixels(TUint32* aGray256Buffer,TInt aBufferLength) = 0;

    /**
	 *
	 * For image types which support blocking of pixels eg JPEG, sets the current
	 * pixel block using the data supplied in aGray256Buffer.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aGray256Buffer"
	 *          Pointer to a buffer representing a block of pixel color values.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 */
	virtual TBool SetMonoPixelBlock(TUint32* aGray256Buffer) = 0;

	// Processor flow control

	/**
	 *
	 * Set the current position in the bitmap to aPosition.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aPosition"
	 *          Reference to TPoint object defining the position to move to.
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 */
	virtual TBool SetPos(const TPoint& aPosition) = 0;

	/**
	 *
	 * Commits the changes made to the current bitmap by flushing the buffer.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @return	ETrue if the operation succeeded, otherwise EFalse.
	 * @post    The current position is updated.
	 */
	virtual TBool FlushPixels() = 0;
	};

inline TInt TColorConvertor::RgbToMonochrome(TRgb aRgb)
	{
	TInt value = aRgb.Value();
	TInt r = value&0xFF;
	TInt g = value&0xFF00;
	value &= 0x00FF0000;	// blue<<16
	value += r<<(16+1);		// + (red<<16)*2
	value += g<<(16+2-8);	// + (green<<16)*4
	value += g<<(16+0-8);	// + (green<<16)
	return value>>(16+3);	// total/8
	}

#endif ___IMAGEPROCESSOR_H__

