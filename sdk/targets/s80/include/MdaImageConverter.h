// MdaImageConverter.h
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//

// BC Version that uses CImageDecode/Encode objects but is essentially source
// compatible with the old MdaImageConverter calls

#ifndef __MDAIMAGECONVERTER_H__
#define __MDAIMAGECONVERTER_H__

#include <fbs.h>

#include <MdaFrameInfo.h>
#include <Mda\Client\Resource.h>
#include <Mda\Client\Utility.h>
#include <Mda\Common\Video.h>

class CMdaServer;
class REComSession;

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
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - no direct equivalent"
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

// Note: TFrameInfo is now declared via ImageClientApi - was previously here


class CMdaImageUtilityPriv;
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
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - no direct equivalent"
 */
class CMdaImageUtility : public CDummyMdaResource, private MMdaObjectStateChangeObserver
	{
friend class CMdaImageUtilityPriv;

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
	IMPORT_C virtual void FrameInfo(TInt aFrame,TFrameInfoMCL& aInfo) const;
	IMPORT_C virtual TInt FrameCount() const;
public:
	// Reserved functions - do not call
	virtual void ImageUtil_Reserved1();
	virtual void ImageUtil_Reserved2();
	virtual void ImageUtil_Reserved3();
	virtual void ImageUtil_Reserved4();
protected:
	CMdaImageUtility();
	virtual void DoClose();
	// From MMdaObjectStateChangeObserver
	virtual void MoscoStateChangeEvent(CBase* aObject, TInt aPreviousState, TInt aCurrentState, TInt aErrorCode);

	void SelfComplete(TInt aError);
	void DoCancel();
protected:
	CMdaImageUtilityPriv* iProperties;
	};


class CImageDecoder;
class CMdaImageDataReadUtilityPriv;
/**
 *
 * Base class used in the derivation of
 * <code>CMdaImageDescToBitmapUtility</code> and
 * <code>CMdaImageFileToBitmapUtility</code>.
 *
 * It has no user accessible functions.
 *
 * @since 6.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - see CImageDecoder"
 */
class CMdaImageDataReadUtility : public CMdaImageUtility
	{
friend class CMdaImageDataReadUtilityPriv;

public:
	virtual ~CMdaImageDataReadUtility();
	// From CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
	// from CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
	IMPORT_C virtual const TDesC& FrameCommentL(TInt aFrameNumber); 
public:
	// Reserved functions - do not call
	virtual void ImageReadUtil_Reserved2();
	virtual void ImageReadUtil_Reserved3();
	virtual void ImageReadUtil_Reserved4();
protected:
	// Creates relevant iDecoder property - depending on subclass.
	// Called by "background" AO processing.
 	void DoOpenL();
	// From CMdaImageUtility
	virtual void DoClose();
private:
	inline CMdaImageDataReadUtilityPriv* Properties() const;
	};


class CImageEncoder;
class CMdaImageDataWriteUtilityPriv;
/**
 *
 * Base class used in the derivation of
 * <code>CMdaImageBitmapToDescUtility</code> and
 * <code>CMdaImageBitmapToFileUtility</code>.
 *
 * It has no user accessible functions.
 *
 * @since 6.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - see CImageEncoder"
 */
class CMdaImageDataWriteUtility : public CMdaImageUtility
	{
friend class CMdaImageDataWriteUtilityPriv;

public:
	virtual ~CMdaImageDataWriteUtility();
	// From CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,const TRect& aSourceRect,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
protected:
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
protected:
	virtual CImageEncoder* Encoder() const;
public:
	// Reserved functions - do not call
	virtual void ImageWriteUtil_Reserved1();
	virtual void ImageWriteUtil_Reserved2();
	virtual void ImageWriteUtil_Reserved3();
protected:
	// Creates relevant <code>iEncoder</code> property - depending on subclass.
	// Called by "background" AO processing.
	void DoCreateL(TBool aFullCreate=ETrue);
	// From CMdaImageUtility
	virtual void DoClose();
private:
	inline CMdaImageDataWriteUtilityPriv* Properties() const;
	};


class CMdaImageFileToBitmapUtilityPriv;
/**
 *
 * Implements format conversion of a file based image to a bitmap.
 *
 * The class provides functions to create an instance of this conversion
 * utility and to open an existing image file.Conversion is performed
 * using the image conversion utility interface.
 *
 * @since 5.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - use CImageDecoder::FileNewL()"
 */
class CMdaImageFileToBitmapUtility : public CMdaImageDataReadUtility
	{
public:
	IMPORT_C static CMdaImageFileToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void OpenL(const TDesC& aFileName,TMdaClipFormat* aFormat = NULL,TMdaPackage* aCodec = NULL,TMdaPackage* aExtra = NULL);
private:
	inline CMdaImageFileToBitmapUtilityPriv* Properties() const;
	};


class CMdaImageDescToBitmapUtilityPriv;
/**
 *
 * Implements format conversion of a descriptor-based image to a bitmap.
 *
 * The class provides functions to create an instance of this conversion
 * utility and to open and prepare the image data.Conversion is performed
 * using the image conversion utility interface.
 *
 * @since 5.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - use CImageDecoder::DataNewL()"
 */
class CMdaImageDescToBitmapUtility : public CMdaImageDataReadUtility
	{
public:
	IMPORT_C static CMdaImageDescToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void OpenL(const TDesC8& aDescriptor,TMdaClipFormat* aFormat = NULL,TMdaPackage* aCodec = NULL,TMdaPackage* aExtra = NULL);
private:
	inline CMdaImageDescToBitmapUtilityPriv* Properties() const;
	};


class CMdaImageBitmapToFileUtilityPriv;
/**
 *
 * Implements format conversion of a bitmap to a file-based image.
 *
 * The class provides functions to create an instance of this conversion
 * utility and to create the file.Conversion is performed using the image
 * conversion utility interface.
 *
 * @since 5.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - use CImageEncoder::FileNewL()"
 */
class CMdaImageBitmapToFileUtility : public CMdaImageDataWriteUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToFileUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void CreateL(const TDesC& aFileName,TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
private:
	inline CMdaImageBitmapToFileUtilityPriv* Properties() const;
	};


class CMdaImageBitmapToDescUtilityPriv;
/**
 * @publishedAll
 * @deprecated 7.0s
 */
class CMdaImageBitmapToDescUtility : public CMdaImageDataWriteUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToDescUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void CreateL(TDes8& aDescriptor,TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
private:
	inline CMdaImageBitmapToDescUtilityPriv* Properties() const;
	};


class CMdaImageBitmapToBitmapUtilityPriv;
/**
 *
 * Implements bitmap to bitmap copying and colour depth conversion
 *
 * @since 5.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - use CImageEncoder::FileNewL()"
 */
class CMdaImageBitmapToBitmapUtility : public CMdaImageUtility
	{
friend class CMdaImageBitmapToBitmapUtilityPriv;

public:
	IMPORT_C static CMdaImageBitmapToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver, CMdaServer* aServer = NULL);
	IMPORT_C ~CMdaImageBitmapToBitmapUtility();
	IMPORT_C void OpenL(CFbsBitmap& aBitmap);
	// from CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap, TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap, CFbsBitmap& aMaskBitmap, TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
	// From CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
protected:
	// from CMdaImageUtility
	virtual void DoClose();
private:
	inline CMdaImageBitmapToBitmapUtilityPriv* Properties() const;
	};



class CMdaBitmapRotatorPriv;
/**
 *
 * Rotates a bitmap.
 *
 * The class offers a simple interface to perform bitmap rotations in
 * clockwise 90 degree increments. The target bitmap is resized as
 * necessary.
 *
 * @since 5.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - see CBitmapRotator"
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
	CMdaBitmapRotatorPriv* iProperties;
	};


class CMdaBitmapScalerPriv;
/**
 *
 * Re-scales a bitmap.
 *
 * The class offers a simple interface to perform arbitrary re-scaling of
 * a bitmap.
 *
 * @since 5.0
 * @publishedAll
 * @deprecated 7.0s "Replaced by Image Conversion library - see CBitmapScaler"
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
	CMdaBitmapScalerPriv* iProperties;
	};

#endif

