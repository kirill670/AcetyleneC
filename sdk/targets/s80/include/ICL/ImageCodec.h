// ImageCodec.h
//
// Copyright (c) 2001-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __IMAGECODEC_H__
#define __IMAGECODEC_H__

#include <e32std.h>
#include <fbs.h>

// Pre-definitions needed to make sure everything always defined in the right order
class TFrameInfo;
class TImageDataBlock;
class CFrameImageData;

class CImageDecoder;
class CImageEncoder;
class CImageProcessor; 
class CImageProcessorReadCodecBody;
class CImageMaskProcessorReadCodecBody;

/**
 * @publishedAll
 * @released
 *
 * Indicates what processing has so far been completed on the frame.
 *
 */
enum TFrameState
	{
	EFrameIncomplete,

	EFrameComplete,

	EUnexpectedEndOfData,

	/** As 'EFrameIncomplete' but also requests a call to GetNewDataPosition */
	EFrameIncompleteRepositionRequest	
	};

/**
 * @publishedAll
 * @released
 *
 * Class used to shadow the descriptor supplying the image data.
 * It maintains a flag to determine whether the descriptor contains a 
 * filename or the image data itself.
 * This class is not for public use
 *
 */
class TImageParameterData
	{
public:

	/**
	 * Flag used to determine what the descriptor contains.
	 */
	enum TImageParameterDataFlag
		{
		 /** Field not set */
		ENull		= 0x00000000,

		/** Descriptor is a filename */
		EFilename	= 0x00000001,
		
		/** Descriptor contains data */
		EData		= 0x00000002
		};

	TImageParameterData();
	void SetFilenamePtr(const TDesC* aSourceFilenamePtr);
	void SetDataPtr(const TDesC8* aSourceDataPtr);
	IMPORT_C const TBool IsFilename() const;
	IMPORT_C const TDesC* SourceFilenamePtr() const;
	IMPORT_C const TDesC8* SourceDataPtr() const;

private:
	TImageParameterDataFlag iImageParameterDataFlag;
	union
		{
		const TDesC* iSourceFilenamePtr;
		const TDesC8* iSourceDataPtr;
		};
	};

/**
 * @publishedAll
 * @released
 *
 * @see TPtr8
 * @see TPtrC8
 * @see TDes8
 * @see TDesC8
 *
 * Utility class to allow forward iteration through the data contained in
 * an 8 bit descriptor.
 *
 */
class TBufPtr8 : public TPtr8
	{
public:
	/**
	 *
	 * Default constructor
	 */
	TBufPtr8()
		: TPtr8(0, 0, 0) {};
	inline void Set(const TDes8& aDes);
	inline void SetLengthOnly(const TDes8& aDes);
	inline void Set(const TPtrC8& aDes);
	inline void Shift(TInt aOffset);
	};

/**
 *
 * Produces a shallow copy of the argument descriptor.
 *
 * @param	"aDes"
 *          A reference to the descriptor containing the relevant data.
 */
inline void TBufPtr8::Set(const TDes8& aDes)
	{
	TPtr8::Set(CONST_CAST(TUint8*,aDes.Ptr()), aDes.Length(), aDes.MaxLength());
	}
/**
 *
 * Produces a shallow copy of the argument descriptor, but also restricts 
 * pointer access to the current actual size of the argument descriptor.
 *
 * @param	"aDes"
 *          A reference to the descriptor containing the relevant data.
 */
inline void TBufPtr8::SetLengthOnly(const TDes8& aDes)
	{
	TPtr8::Set(CONST_CAST(TUint8*,aDes.Ptr()), aDes.Length(), aDes.Length());
	}
/**
 *
 * Produces a shallow copy of the argument descriptor, but restricts 
 * pointer access to the size of the const argument descriptor.
 *
 * @param	"aDes"
 *          A reference to the descriptor containing the relevant data.
 */
inline void TBufPtr8::Set(const TPtrC8& aDes)
	{
	TPtr8::Set(CONST_CAST(TUint8*,aDes.Ptr()), aDes.Length(), aDes.Length());
	}
/**
 *
 * Seek the current data pointer aOffset bytes from the current position.
 *
 * @param	"aOffset"
 *          How many bytes by which to seek.
 */
inline void TBufPtr8::Shift(TInt aOffset)
	{
	SetLength(Length() - aOffset); iMaxLength -= aOffset; iPtr += aOffset;
	}

/**
 * @publishedAll
 * @released
 *
 * Note: For use by plugin writers only.
 *
 */
class CImageReadCodec : public CBase
	{
public:
	IMPORT_C ~CImageReadCodec();

	/**
	 *
	 * Initial processing of the frame for the destination bitmap using data supplied in 
	 * aFrameInfo, aFrameImageData and using the flag aDisableErrorDiffusion. Not all codecs
	 * are expected to make use of all fields. 
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aFrameInfo"
	 *          A reference to a TFrameInfo object.
	 * @param	"aFrameImageData"
	 *          A reference to a CFrameImageData object.
	 * @param	"aDisableErrorDiffusion"
     *          Flag indicating whether error diffusion should be disabled.
	 * @param	"aDestination"
	 *          The destination bitmap.
	 * @param	"aDestinationMask"
	 *          The destination mask bitmap.
	 */
	virtual void InitFrameL(TFrameInfo& aFrameInfo, CFrameImageData& aFrameImageData, TBool aDisableErrorDiffusion, CFbsBitmap& aDestination, CFbsBitmap* aDestinationMask) = 0;

	IMPORT_C virtual void InitFrameHeader(TFrameInfo& aFrameInfo, CFrameImageData& aFrameData);
	IMPORT_C virtual TFrameState ProcessFrameHeaderL(TBufPtr8& aData);
	IMPORT_C virtual void Complete(); // Called on frame completion and on underflow
	IMPORT_C virtual void GetNewDataPosition(TInt& aPosition, TInt& aLength); // Returns a new position for the data stream, (also length of data required)

	/**
	 *
	 * Process the frame data contained in aSrc.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aSrc"
	 *          A reference to the buffer containing the frame data.
	 * @return	Current frame state after processing.
	 */
	virtual TFrameState ProcessFrameL(TBufPtr8& aSrc) = 0;
	void SetCurrentFrame(TInt aFrameNumber);

protected:
	IMPORT_C CImageReadCodec();
	IMPORT_C void ConstructL();

	IMPORT_C void ClearBitmapL(CFbsBitmap& aBitmap, TRgb aColor);
	IMPORT_C TInt CurrentFrame() const;

private:
	TInt iCurrentFrame; //make handle to body if additional properties are needed
	};

/**
 * @publishedAll
 * @released
 *
 * Note: For use by plugin writers only.
 *
 */
class CImageProcessorReadCodec : public CImageReadCodec
	{
public:
	IMPORT_C ~CImageProcessorReadCodec();
protected:
	IMPORT_C CImageProcessorReadCodec();
	IMPORT_C void ConstructL();

	IMPORT_C CImageProcessor* ImageProcessor() const;
	IMPORT_C void SetImageProcessor(CImageProcessor* aImageProc);

	IMPORT_C const TPoint& Pos() const;
	IMPORT_C TPoint& Pos();
	IMPORT_C void SetPos(const TPoint& aPos);
private:
	CImageProcessorReadCodecBody* iBody;
	};

/**
 * @publishedAll
 * @released
 *
 * Note: For use by plugin writers only.
 *
 */
class CImageMaskProcessorReadCodec : public CImageProcessorReadCodec
	{
public:
	IMPORT_C ~CImageMaskProcessorReadCodec();
protected:
	IMPORT_C CImageMaskProcessorReadCodec();
	IMPORT_C void ConstructL();

	IMPORT_C CImageProcessor* MaskProcessor() const;
	IMPORT_C void SetMaskProcessor(CImageProcessor* aMaskProc);

private:
	CImageMaskProcessorReadCodecBody* iBody;
	};

/**
 * @publishedAll
 * @released
 *
 * Note: For use by plugin writers only.
 *
 */
class CImageWriteCodec : public CBase
	{
public:
	IMPORT_C ~CImageWriteCodec();
	IMPORT_C virtual void InitFrameL(TBufPtr8& aDst, const CFbsBitmap& aSource);

	/**
	 *
	 * Process the frame data contained in aDst.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	aDst"
	 *          A reference to the buffer containing the frame data.
	 * @return	Current frame state after processing.
	 */
	virtual TFrameState ProcessFrameL(TBufPtr8& aDst) = 0;

	IMPORT_C const CFbsBitmap* Source() const;
	IMPORT_C void SetSource(const CFbsBitmap* aSource);
protected:
	IMPORT_C void ConstructL();
	IMPORT_C CImageWriteCodec();
private:
	const CFbsBitmap* iSource; // linked object
	};

/**
 * @internalComponent
 *
 * Max size of strings in extra resource files
 */
const TInt KCodecResourceStringMax=128;

#endif // __IMAGECODEC_H__
