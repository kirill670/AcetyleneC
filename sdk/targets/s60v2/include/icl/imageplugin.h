
// ImagePlugin.h
//
// Copyright (c) Symbian Ltd 2001-3. All rights reserved.

#ifndef __ImageConversionPlugin_h
#define __ImageConversionPlugin_h

#include "ICL\ImageData.h"
#include "ICL\ImageCodec.h"

class CImageDecoderPriv;
class CImageEncoderPriv;
class CImageReadCodec;
class CImageWriteCodec;
class TBufPtr8;

/**
@publishedAll
@released

The PluginAPI for Image Converter Library decoder plugins. 

Intended for use by plugin writers only.
*/
class CImageDecoderPlugin : public CBase
	{
friend class CImageDecoderPriv;

public:
	IMPORT_C ~CImageDecoderPlugin();

	IMPORT_C virtual TInt NumberOfImageComments() const;
	IMPORT_C virtual HBufC* ImageCommentL(TInt aCommentNumber) const;
	IMPORT_C virtual TInt NumberOfFrameComments(TInt aFrameNumber) const;
	IMPORT_C virtual HBufC* FrameCommentL(TInt aFrameNumber, TInt aCommentNumber) const;

	/**
	Returns the image type and sub-type for a given frame of the image that
	has just been opened.

	This is a virtual funtion that each individual plugin must implement.

	@param  aFrameNumber
	        The frame index for type and sub-type information should be returned.
	@param  aImageType
	        On return contains the image type UID for the specified frame.
	@param  aImageSubType
	        On return contains the image sub-type UID for the specified frame. If the sub-type does
			not exist KNullUid is returned.
	*/
	virtual void ImageType(TInt aFrameNumber, TUid& aImageType, TUid& aImageSubType) const = 0;

protected:
	IMPORT_C CImageDecoderPlugin();
	IMPORT_C virtual void Cleanup();
	IMPORT_C virtual void ReadFrameHeadersL();

	/**
	Invokes the ReadFrameHeadersL() method of the supplied plugin.

	The plugin's version of ReadFrameHeadersL() should read the image header information, create
	the required codec and read the frame headers.

	This is a virtual funtion that each individual plugin must implement.
	*/
	virtual void ScanDataL() = 0;


	IMPORT_C virtual TInt FrameHeaderBlockSize(TInt aFrameNumber) const;
	IMPORT_C virtual TInt FrameBlockSize(TInt aFrameNumber) const;

	/**
	Returns the codec specific frame information stored in resource files.

	This is a virtual funtion that each individual plugin must implement.

	@param  aFs
	        A handle to a file server session.
	@param  aFrameNumber
	        The frame number to which the codec specific frame information
	        applies (optional, defaults to zero).

	@return A pointer to a newly allocated CFrameInfoStrings object.
	        Ownership is transferred to the caller.
	*/
	IMPORT_C virtual CFrameInfoStrings* FrameInfoStringsL(RFs& aFs, TInt aFrameNumber = 0) = 0;

	IMPORT_C void OpenExtraResourceFileLC(RFs& aFs, const TUid aUid, RResourceFile& aResourceFile) const;
	IMPORT_C void ReadDataL(TInt aPosition, TPtrC8& aReadBuffer, TInt aLength);
	IMPORT_C virtual void InitConvertL();

	IMPORT_C virtual void DoConvert();
	IMPORT_C void PrepareForProcessFrameL();
	IMPORT_C void HandleProcessFrameResult(TInt aErrCode, TFrameState aCodecState);
	IMPORT_C TBufPtr8& SourceData();

	IMPORT_C void RequestComplete(TInt aReason);
	IMPORT_C void SelfComplete(TInt aReason);
	IMPORT_C void SetSelfPending();

	IMPORT_C TBool IsImageHeaderProcessingComplete() const;

	IMPORT_C CImageReadCodec* ImageReadCodec() const;
	IMPORT_C void SetImageReadCodec(CImageReadCodec* aImageReadCodec);

	IMPORT_C const TFrameInfo& ImageInfo() const;
	IMPORT_C void SetImageInfo(const TFrameInfo& aImageInfo);

	IMPORT_C TInt NumberOfFrames() const;

	IMPORT_C const TImageDataBlock* ImageData(TInt aIndex) const;
	IMPORT_C TInt InsertImageData(const TImageDataBlock* aEntry, TInt aPos);
	IMPORT_C TInt AppendImageData(const TImageDataBlock* aEntry);
	IMPORT_C void RemoveImageData(TInt aPos);
	IMPORT_C TInt ImageDataCount() const;
	IMPORT_C TInt AppendImageDataBuffer(const HBufC8* aImageBuffer);

	IMPORT_C TInt DataLength() const;
	IMPORT_C void SetDataLength(TInt aDataLength);
	IMPORT_C TInt Position() const;
	IMPORT_C void SetPosition(const TInt aPosition);
	IMPORT_C TInt StartPosition() const;
	IMPORT_C void SetStartPosition(TInt aDataLength);

	IMPORT_C const CFbsBitmap& Destination() const;
	IMPORT_C TBool ValidDestination() const;
	IMPORT_C const CFbsBitmap& DestinationMask() const;
	IMPORT_C TBool ValidDestinationMask() const;

	IMPORT_C const TFrameInfo& FrameInfo(TInt aFrameNumber = 0) const;
	IMPORT_C const CFrameImageData& FrameData(TInt aFrameNumber = 0) const;

	IMPORT_C TInt SourceLength() const;

	IMPORT_C virtual void HandleCustomSyncL(TInt aParam);
	IMPORT_C virtual void InitCustomAsyncL(TInt aParam);
	IMPORT_C virtual void NotifyComplete();
	IMPORT_C TBool AmInThread() const;
	IMPORT_C TBool ShouldAbort() const;

private:
	TBool ValidProperties() const;

	// Future proofing
	IMPORT_C virtual void EnableMaskGeneration();
	IMPORT_C virtual void ReservedVirtual2();
	IMPORT_C virtual void ReservedVirtual3();
	IMPORT_C virtual void ReservedVirtual4();

private:
	CImageDecoderPriv* iProperties; // not owned

friend class RCImageDecoderPrivTestBase;
	};

/**
@publishedAll
@released

The plugin API for Image Converter Library encoder plugins.

Intended for use by plugin writers only.
*/
class CImageEncoderPlugin : public CBase
	{
friend class CImageEncoderPriv;

public:
	IMPORT_C ~CImageEncoderPlugin();

protected:
	IMPORT_C CImageEncoderPlugin();
	IMPORT_C virtual void Cleanup();
	IMPORT_C virtual void InitConvertL();
	IMPORT_C virtual void DoConvert();
	IMPORT_C void HandleProcessFrameResult(TInt aErrCode, TFrameState aCodecState);
	IMPORT_C TBufPtr8& DestinationData();
	IMPORT_C void FinishConvertL();
	IMPORT_C void WriteDataL(TInt aPosition,const TDesC8& aDes);
	IMPORT_C const CFbsBitmap& Source() const;
	IMPORT_C TBool ValidSource() const;

	IMPORT_C CImageWriteCodec* ImageWriteCodec() const;
	IMPORT_C void SetImageWriteCodec(CImageWriteCodec* aImageWriteCodec) const;
	IMPORT_C TInt& StartPosition() const;
	IMPORT_C TInt& Position() const;
	IMPORT_C const TSize& FrameInfoOverallSizeInPixels() const;

	/**
	Allocates the specific codec used for the encoding and passes
	ownership to the plugin.

	This is a pure virtual funtion that each individual plugin must implement.

	@param  aFrameImageData
	        The parameters which can be passed on to the encoding algorithm.
	        This data might be used to determine the exact codec created.

	@return An error code indicating if the function call was successful. KErrNone on success, otherwise
	        another of the system-wide error codes.
	*/
	virtual void PrepareEncoderL(const CFrameImageData* aFrameImageData) = 0;

	/**
	May be used to fill in additional fields at the end of the encoding
	process, which it may not have been possible to do earlier.

	This is a pure virtual funtion that each individual plugin must implement.
	*/
	virtual void UpdateHeaderL() = 0;

	IMPORT_C TInt CurrentImageSizeL() const;

	IMPORT_C void RequestComplete(TInt aReason);
	IMPORT_C void SelfComplete(TInt aReason);
	IMPORT_C void SetSelfPending();

	IMPORT_C virtual void HandleCustomSyncL(TInt aParam);
	IMPORT_C virtual void InitCustomAsyncL(TInt aParam);
	IMPORT_C virtual void NotifyComplete();
	IMPORT_C TBool AmInThread() const;
	IMPORT_C TBool ShouldAbort() const;

private:
	TBool ValidProperties() const;

	// Future proofing
	IMPORT_C virtual void ReservedVirtual1();
	IMPORT_C virtual void ReservedVirtual2();
	IMPORT_C virtual void ReservedVirtual3();
	IMPORT_C virtual void ReservedVirtual4();

private:
	CImageEncoderPriv* iProperties; // not owned
	};


#endif __ImageConversionPlugin_h

