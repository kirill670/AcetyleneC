// MdaImageConverter.h
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAIMAGECONVERTER_H__
#define __MDAIMAGECONVERTER_H__

#include <fbs.h>
#include <bitdev.h>
#include <Mda\Client\Utility.h>
#include <Mda\Client\Resource.h>
#include <Mda\Client\Video.h>
#include <Mda\Common\Video.h>

/**
 *
 * An interface to a set of image conversion utility callback functions.
 *
 * The class is a mixin and is intended to be inherited by the client
 * classes which observe the image conversion operations. The functions
 * encapsulated by this class are called when the open, create and
 * conversion operations complete.The interface is also used by the
 * bitmap image rotator and the bitmap image re-scaler.A reference to
 * this object is passed as a parameter when constructing image
 * conversion utility, image rotator and image re-scaler objects.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class MMdaImageUtilObserver
	{
public:

/**
 *
 * Defines required client behaviour when a create operation has
 * completed.
 *
 * @param     "TInt aError"
 *            A value identifying the status of the create
 *            operation. <code>KErrNone</code> or one of the system
 *            wide error codes.
 */
	virtual void MiuoCreateComplete(TInt aError) = 0;

/**
 *
 * Defines required client behaviour when an open operation has
 * completed.
 *
 * @param     "TInt aError"
 *            A value identifying the status of the create
 *            operation. <code>KErrNone</code> or one of the system
 *            wide error codes.
 */
	virtual void MiuoOpenComplete(TInt aError) = 0;

/**
 *
 * Defines required client behaviour when a conversion, image rotation or
 * image re-scaling operation has completed.
 *
 * @param     "TInt aError"
 *            A value identifying the status of the operation.
 *            <code>KErrNone</code> or one of the system wide error
 *            codes.
 */
	virtual void MiuoConvertComplete(TInt aError) = 0;
	};

/**
 *
 * Image frame information.
 *
 * The class only consists of public member data; it has no member
 * functions.
 *
 * @since 5.0
 */
class TFrameInfo
	{
public:
	enum TFrameInfoFlags
		{
		EColor					= 0x00000001, // Grayscale if not set
		ETransparencyPossible	= 0x00000002, // Fully opaque if not set
		EFullyScaleable			= 0x00000004, // Will only scale to 1/2,1/4 & 1/8th if not set
		EConstantAspectRatio	= 0x00000008, // Scaling need not maintain aspect ratio if not set
		ECanDither				= 0x00000010, // Will not use error diffusion if not set
		EAlphaChannel			= 0x00000020, // Set if the image contains alpha-blending information
		ELeaveInPlace			= 0x00000040, // }
		ERestoreToBackground	= 0x00000080, // } Mutually exclusive image disposal methods
		ERestoreToPrevious		= 0x00000100  // }
		};
public:
	TRect iFrameCoordsInPixels;
	TSize iFrameSizeInTwips;
	TInt iBitsPerPixel;
	TTimeIntervalMicroSeconds iDelay;
	TUint32 iFlags;
	TSize iOverallSizeInPixels;
	};

/**
 *
 * Defines the public interface to image conversion.
 *
 * Clients of the concrete conversion classes call the functions provided
 * by this interface to perform the conversion. The implementation of
 * these functions is provided either by the concrete conversion classes
 * themselves or by private implementation classes.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageUtility : public CMdaResource, public MMdaObjectStateChangeObserver
	{
public:
	virtual ~CMdaImageUtility();
	IMPORT_C virtual void Close();

/**
 *
 * Begins the image conversion operation for the specified frame
 * overloaded function.
 *
 * The operation is asynchronous. When the conversion operation is
 * complete, successfully or otherwise, the callback function
 * <code>MMdaImageUtilObserver::MiuoConvertComplete()</code> is
 * called.When converting from a file or descriptor to a bitmap, the
 * operation can complete with <code>KErrUnderflow</code>, if there is
 * insufficient information in the file or descriptor. Typically, this
 * occurs when using the file or descriptor as a cache. In this
 * situation, the conversion operation should be performed repeatedly
 * until the file or descriptor has accumulated enough information for
 * the operation to complete with <code>KErrNone</code>. As much of the
 * image as is present is converted and written to the target bitmap at
 * each call to this function.
 *
 * @param     "CFbsBitmap& aBitmap"
 *            A reference to a bitmap. This may be a source or a
 *            target for the conversion process, depending on the
 *            concrete conversion class utility being used.
 * @param     "CFbsBitmap& aMaskBitmap"
 *            A source or target mask bitmap, if present.
 * @param     "TInt aFrameNumber = 0"
 *            The frame number. This value is relative to zero. For
 *            those concrete conversion classes which perform
 *            conversion from a bitmap, this value must always be
 *            zero. For those concrete conversion classes which
 *            perform conversion to a bitmap, this value must be
 *            less than the number of frames in the image.
 */
	virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0) = 0;
	virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0) = 0;

/**
 *
 * Cancels the conversion operation.
 *
 * The callback function
 * <code>MMdaImageUtilObserver::MiuoConvertComplete()</code> is not
 * called.
 *
 */
	virtual void CancelConvertL() = 0;
	IMPORT_C virtual void FrameInfo(TInt aFrame,TFrameInfo& aInfo) const;
	IMPORT_C virtual TInt FrameCount() const;
public:
	// Reserved functions - do not call
	virtual void ImageUtil_Reserved1();
	virtual void ImageUtil_Reserved2();
	virtual void ImageUtil_Reserved3();
	virtual void ImageUtil_Reserved4();
protected:
	CMdaImageUtility(MMdaImageUtilObserver& aObserver);
	void SetServerL(CMdaServer* aServer);
	void CancelControllerOperation();
	virtual void DoClose();
	// From MMdaObjectStateChangeObserver
	virtual void MoscoStateChangeEvent(CBase* aObject,TInt aPreviousState,TInt aCurrentState,TInt aErrorCode);
protected:
	MMdaImageUtilObserver& iObserver;
	CMdaServer* iServer;
	TBool iOwnsServer;
	CMdaController* iController;
	TInt iMoscoState;
	TMdaFbsBitmapDevice iBitmapDevice;
	TMdaFbsBitmapHandle iBitmapHandle;
	TMdaFbsBitmapMaskHandle iMaskBitmapHandle;
	RArray<TMdaVideoFrameSettings> iFrameSettings;
	TMdaVideoFrameSettings iCurrentFrameSettings;
	TMdaVideoDataSettings iOverallSettings;
	};

/**
 *
 * Base class used in the derivation of
 * <code>CMdaImageDescToBitmapUtility</code> and
 * <code>CMdaImageFileToBitmapUtility</code>.
 *
 * It has no user accessible functions.
 *
 * @since 6.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageDataReadUtility : public CMdaImageUtility
	{
public:
	virtual ~CMdaImageDataReadUtility();
	// From CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
	// From CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
	IMPORT_C virtual const TDesC& FrameCommentL(TInt aFrameNumber);
	// New function
	IMPORT_C RMdaSourceClipPort& SourcePort();
public:
	// Reserved functions - do not call
	virtual void ImageReadUtil_Reserved2();
	virtual void ImageReadUtil_Reserved3();
	virtual void ImageReadUtil_Reserved4();
protected:
	enum TUtilState
		{
		EClosed,
		EOpenSrcOpen,
		EOpenSrcConfig,
		EOpenSrcConfigFormat,
		EOpenSrcConfigCodec,
		EOpenSrcConfigExtra,
		EOpenDstOpen,
		EOpenDstConfig,
		EOpenControllerCreate,
		EOpenControllerPrepare,
		EOpenSrcPortConfigOverall,
		EOpenSrcPortConfigFrame,
		EOpen,
		EConvertSrcPortConfig,
		EConvertSrcPortConfigMask,
		EConvertDstConfig,
		EConvertControllerPrime,
		EConvertSrcPortConfigFrame,
		EConvertControllerPrepare,
		EConvertNextFrameInfo
		};
protected:
	CMdaImageDataReadUtility(MMdaImageUtilObserver& aObserver);
	void DoOpenL(TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
	void GetCommentL();
	// From CMdaImageUtility
	virtual void DoClose();
protected:
	RMdaSourceClipPort iSrcPort;
	RMdaDestinationStreamPort iDstPort;
	TMdaClipLocation* iLocation;
	TMdaFileClipLocation iFile;
	TMdaDesClipLocation iDesc;
	TUtilState iState;
	TMdaClipFormat* iFormat;
	TMdaPackage* iCodec;
	TMdaPackage* iExtra;
	TMdaVideoCurrentFrame iFrame;
	RPointerArray<HBufC> iComment;
	};

/**
 *
 * Base class used in the derivation of
 * <code>CMdaImageBitmapToDescUtility</code> and
 * <code>CMdaImageBitmapToFileUtility</code>.
 *
 * It has no user accessible functions.
 *
 * @since 6.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageDataWriteUtility : public CMdaImageUtility
	{
public:
	virtual ~CMdaImageDataWriteUtility();
	// From CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,const TRect& aSourceRect,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
	// From CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
public:
	// Reserved functions - do not call
	virtual void ImageWriteUtil_Reserved1();
	virtual void ImageWriteUtil_Reserved2();
	virtual void ImageWriteUtil_Reserved3();
	virtual void ImageWriteUtil_Reserved4();
protected:
	enum TUtilState
		{
		EClosed,
		ECreateSrcOpen,
		ECreateSrcConfig,
		ECreateDstOpen,
		ECreateDstConfig,
		ECreateDstConfigFormat,
		ECreateDstConfigCodec,
		ECreateDstConfigExtra,
		ECreateControllerCreate,
		ECreated,
		EConvertSrcPortConfig,
		EConvertSrcPortConfigMask,
		EConvertDstPortConfigSourceRect,
		EConvertDstConfigCrop,
		EConvertControllerPrime
		};
protected:
	CMdaImageDataWriteUtility(MMdaImageUtilObserver& aObserver);
	void DoCreateL(TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
	// From CMdaImageUtility
	virtual void DoClose();
protected:
	RMdaSourceStreamPort iSrcPort;
	RMdaDestinationClipPort iDstPort;
	TMdaClipLocation* iLocation;
	TMdaFileClipLocation iFile;
	TMdaDesClipLocation iDesc;

	TMdaClipFormat* iFormat;
	TMdaPackage* iCodec;
	TMdaPackage* iExtra;
	TMdaDstPortSourceRect iSourceRectPackage;
	TMdaClipCrop iCrop;

	TUtilState iState;
	};

/**
 *
 * Implements format conversion of a file based image to a bitmap.
 *
 * The class provides functions to create an instance of this conversion
 * utility and to open an existing image file.Conversion is performed
 * using the image conversion utility interface.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageFileToBitmapUtility : public CMdaImageDataReadUtility
	{
public:
	IMPORT_C static CMdaImageFileToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void OpenL(const TDesC& aFileName,TMdaClipFormat* aFormat = NULL,TMdaPackage* aCodec = NULL,TMdaPackage* aExtra = NULL);
protected:
	CMdaImageFileToBitmapUtility(MMdaImageUtilObserver& aObserver);
	};

/**
 *
 * Implements format conversion of a descriptor-based image to a bitmap.
 *
 * The class provides functions to create an instance of this conversion
 * utility and to open and prepare the image data.Conversion is performed
 * using the image conversion utility interface.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageDescToBitmapUtility : public CMdaImageDataReadUtility
	{
public:
	IMPORT_C static CMdaImageDescToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void OpenL(const TDesC8& aDescriptor,TMdaClipFormat* aFormat = NULL,TMdaPackage* aCodec = NULL,TMdaPackage* aExtra = NULL);
protected:
	CMdaImageDescToBitmapUtility(MMdaImageUtilObserver& aObserver);
	};

/**
 *
 * Implements format conversion of a bitmap to a file-based image.
 *
 * The class provides functions to create an instance of this conversion
 * utility and to create the file.Conversion is performed using the image
 * conversion utility interface.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageBitmapToFileUtility : public CMdaImageDataWriteUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToFileUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void CreateL(const TDesC& aFileName,TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
protected:
	CMdaImageBitmapToFileUtility(MMdaImageUtilObserver& aObserver);
	};

/**
 *
 * Implements format conversion of a bitmap to a descriptor-based image.
 *
 * The class provides functions to create an instance of this conversion
 * utility and to initialise the descriptor.Conversion is performed using
 * the image conversion utility interface.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageBitmapToDescUtility : public CMdaImageDataWriteUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToDescUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void CreateL(TDes8& aDescriptor,TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
protected:
	CMdaImageBitmapToDescUtility(MMdaImageUtilObserver& aObserver);
	};

/**
 *
 * Implements format conversion from one bitmap to another bitmap.
 *
 * The class provides member functions to create an instance of this
 * conversion utility and to open the source bitmap.Conversion is
 * performed using the image conversion utility interface.The main use
 * for this class is for bitmap display mode conversion. Error diffusion
 * is used if information is lost in the conversion.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaImageBitmapToBitmapUtility : public CMdaImageUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C ~CMdaImageBitmapToBitmapUtility();
	IMPORT_C void OpenL(CFbsBitmap& aBitmap);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();

	// From CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
protected:
	enum TUtilState
		{
		EClosed,
		EReady,
		ESrcOpen,
		ESrcConfig,
		ESrcPortConfig,
		EDstOpen,
		EDstConfig,
		EDstPortConfig,
		EControllerCreate,
		EControllerPrime
		};
protected:
	CMdaImageBitmapToBitmapUtility(MMdaImageUtilObserver& aObserver);
	// From CMdaImageUtility
	virtual void DoClose();
protected:
	RMdaSourceStreamPort iSrcPort;
	RMdaDestinationStreamPort iDstPort;
	TMdaFbsBitmapHandle iDstBitmapHandle;
	TUtilState iState;
	};

/**
 *
 * Rotates a bitmap.
 *
 * The class offers a simple interface to perform bitmap rotations in
 * clockwise 90 degree increments. The target bitmap is resized as
 * necessary.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaBitmapRotator : public CBase
	{
public:
	enum TRotationAngle
		{
		ERotation90DegreesClockwise,
		ERotation180DegreesClockwise,
		ERotation270DegreesClockwise,
		EMirrorFlipHorizontal,
		EMirrorFlipVertical
		};
public:
	IMPORT_C static CMdaBitmapRotator* NewL();
	IMPORT_C virtual ~CMdaBitmapRotator();
	IMPORT_C void RotateL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aSrcBitmap,CFbsBitmap& aTgtBitmap,TRotationAngle aAngle);
	IMPORT_C void RotateL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aBitmap,TRotationAngle aAngle);
	IMPORT_C void CancelRotation();
protected:	
	static TInt Rotate(TAny* aParam);
	TBool DoRotate();
	void FlipScanLine(TDes8& aDes, TInt aWidth);
	CMdaBitmapRotator();
	void ConstructL();
protected:
	MMdaImageUtilObserver* iObserver;
	TInt iCurOffset;
	TInt iRows;
	CIdle* iRotator;
	TRotationAngle iAngle;
	TSize iBitmapSize;
	TDisplayMode iDisplayMode;
	CFbsBitmap* iTempBitmap;		// For the Rotate() with only one bitmap supplied
	CFbsBitmap* iSrcBitmap;
	CFbsBitmap* iTgtBitmap;
	HBufC8* iScanlineBuffer;
	TPtr8 iScanlineDes;
	TInt iLinesPerCall;				// Number of lines being rotated at once
  	CFbsBitmapDevice* iDevice;
	CFbsBitGc* iGc;	
	CFbsBitmap* iScanlineBitmap;	// Intermediate scanline bitmap
	};

/**
 *
 * Re-scales a bitmap.
 *
 * The class offers a simple interface to perform arbitrary re-scaling of
 * a bitmap.
 *
 * @since 5.0
 * @lib "MediaClientImage.lib"
 */
class CMdaBitmapScaler : public CBase
	{
public:
	IMPORT_C static CMdaBitmapScaler* NewL();
	IMPORT_C virtual ~CMdaBitmapScaler();
	IMPORT_C void ScaleL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aSrcBitmap,CFbsBitmap& aTgtBitmap,TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void ScaleL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aBitmap,TSize aDestSize,TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void CancelScaling();
protected:
	void CalcFilterTables(TInt aOrigWidth,TInt aDestWidth, TInt*& aFilterIndexTablePtr,
						  TInt*& aFilterCoeffsTablePtr );
	void ScaleLine(TDes8& aInDes,TDes8& aOutDes,TInt aStartIndex,TInt aInputWidth,
				   TInt aOutputWidth,TInt* aTableIndexPtr,TInt* aTableCoeffsPtr);
	static TInt Scale(TAny* aParam);
	TBool DoScale();
	CMdaBitmapScaler();
	void ConstructL();
protected:
	CFbsBitmap* iSrcBitmap;
	CFbsBitmap* iTgtBitmap;
	CFbsBitmap* iScaleBitmap;
	CFbsBitmap* iScanlineBitmap;
	CFbsBitmapDevice* iDevice;
	CFbsBitGc* iGc;
	TInt* iFilterIndexTable;
	TInt* iFilterIndexTablePtr;
	TInt iFilterIndexNum;
	TInt* iFilterCoeffsTable;
	TInt* iFilterCoeffsTablePtr;
	TInt iFilterCoeffsNum;
	TSize iOrigSize;
	TSize iDestSize;
	CFbsBitmap* iTempBitmap;
	HBufC8* iRBuffer;
	HBufC8* iBBuffer;
	HBufC8* iGBuffer;
	TPtr8 iRDes;
	TPtr8 iGDes;
	TPtr8 iBDes;
	HBufC8* iOrigBuffer;
	HBufC8* iDestBuffer;
	TPtr8 iOrigDes;
	TPtr8 iDestDes;
	CIdle* iScaler;
	MMdaImageUtilObserver* iObserver;
	TInt iLinesPerCall;
	TBool iVerticalScan;
	TInt iCurOffset;
	TInt iFinalOffset;
	TInt iCurLineSize;
	};

#endif

