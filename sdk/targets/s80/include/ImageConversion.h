// ImageConversion.h
//
// Copyright (c) 2001-2003 Symbian Ltd.  All rights reserved.
//
// This is the public client API for the Image Conversion Library

#ifndef __IMAGECONVERSION_H__
#define __IMAGECONVERSION_H__

#include <fbs.h>
#include <bitdev.h>
#include <badesca.h>
#include <ECom\ImplementationInformation.h>

#include "ICL\ImageCodecData.h"
#include "ICL\ImageData.h"

class MImageDecoderRelay;
class MImageEncoderRelay;
class CImageDecoderPlugin;
class CImageEncoderPlugin;
class CImageDecodeConstruct;
class CImageEncodeConstruct;
	

/**
 *
 * Class used to manage the mapping between an image's type, sub-type and description.
 *
 * @publishedAll
 * @released
 */
class CImageTypeDescription : public CBase
	{
public:
	static CImageTypeDescription* NewL(const TDesC& aDescription, const TUid aImageType, const TUid aSubType);
	static CImageTypeDescription* NewLC(const TDesC& aDescription, const TUid aImageType, const TUid aSubType);
	IMPORT_C ~CImageTypeDescription();
	IMPORT_C const TDesC& Description() const;
	IMPORT_C TUid ImageType() const;
	IMPORT_C TUid SubType() const;
private:
	CImageTypeDescription(const TUid aImageType, const TUid aSubType);
	void ConstructL(const TDesC& aDescription);
private:
	HBufC* iDescription;
	const TUid iImageType;
	const TUid iSubType;
	};

/**
 * @publishedAll
 *
 * Container type to manage lists of pointers to CImageTypeDescription objects.
 *
 */
typedef RPointerArray<CImageTypeDescription> RImageTypeDescriptionArray;

/**
 *
 * Class used to manage the mapping between an image's MIME type & file extension.
 *
 * @publishedAll
 * @released
 */
class CFileExtensionMIMEType : public CBase
	{
public:
	static CFileExtensionMIMEType* NewL(const TDesC8& aExtn, const TDesC8& aMIMEType, const TDesC& aDisplayName, TUid aImageType, TUid aImageSubType, TUid aImplementationUid);
	static CFileExtensionMIMEType* NewLC(const TDesC8& aExtn, const TDesC8& aMIMEType, const TDesC& aDisplayName, TUid aImageType, TUid aImageSubType, TUid aImplementationUid);
	IMPORT_C ~CFileExtensionMIMEType();

	IMPORT_C const TDesC& FileExtension() const;
	IMPORT_C const TDesC8& MIMEType() const;
	IMPORT_C const TDesC& DisplayName() const;
	IMPORT_C TUid ImageType() const;
	IMPORT_C TUid ImageSubType() const;
	IMPORT_C TUid ImplementationUid() const;
private:
	CFileExtensionMIMEType();
	void ConstructL(const TDesC8& aExtn, const TDesC8& aMIMEType, const TDesC& aDisplayName, TUid aImageType, TUid aImageSubType, TUid aImplementationUid);
private:
	HBufC* iFileExtension;
	HBufC8* iMIMEType;
	HBufC* iDisplayName;
	TUid iImageTypeUid;
	TUid iImageSubTypeUid;
	TUid iImplementationUid;
	};

/**
 * @publishedAll
 *
 * Container type to manage lists of pointers to CFileExtensionMIMEType objects.
 *
 */
typedef RPointerArray<CFileExtensionMIMEType> RFileExtensionMIMETypeArray;

/**
 * @publishedAll
 * @released
 *
 * @see CImplementationInformation
 *
 * Class used to manage various information about an implementation 
 * which is stored in resource files.
 *
 */
class CImplementationInformationType : public CBase
	{
public:
	static CImplementationInformationType* NewL();
	static CImplementationInformationType* NewLC();
	IMPORT_C ~CImplementationInformationType();

	void SetDataL(TUid aImplementationUid, TInt aVersion, const TDesC& aDisplayName, const TDesC8& aDataType, const TDesC8& aOpaqueData, TDriveUnit aDrive);

	IMPORT_C TUid ImplementationUid() const;
	IMPORT_C TInt Version() const;
	IMPORT_C const TDesC& DisplayName() const;
	IMPORT_C const TDesC8& DataType() const;
	IMPORT_C const TDesC8& OpaqueData() const;

	IMPORT_C TDriveUnit Drive();

private:
	CImplementationInformationType();

private:
	TUid iImplementationUid;
	TInt iVersion;
	HBufC* iDisplayName;
	HBufC8* iDataType;
	HBufC8* iOpaqueData;
	TDriveUnit iDrive;
	};

/**
 * @publishedAll
 * @released
 *
 * The public API for clients to call the Image Conversion Library decoders
 *
 */
class CImageDecoder : public CBase
	{
public:

	/**
	 * Flags to control how the image is decoded.
	 * These can be combined using an OR operation.
	 */
	enum TOptions
		{
		/** No flag set */
		EOptionNone = 0x00,

		/** Do not dither the decoded image */
		EOptionNoDither	= 0x01,

		/** Perform the decoding in a separate thread */
		EOptionAlwaysThread = 0x02,

		/** 
		 * Allow Opens to complete with no error if there is less
		 * than one frame available. This should be set for streaming.
		 */
		EOptionAllowZeroFrameOpen = 0x04,

		/**
		 * Setting this flag requests that the plugin generate a mask during decoding.
		 *
		 * Note that this option is only relevant to image formats
		 * that do not already contain mask information.
		 *
		 * Note also that the client must check that TFrameInfo::ETransparencyPossible is set
		 * before attempting to obtain the mask, because not all plugins support mask generation.
		 */
		EAllowGeneratedMask = 0x08
		};

public:
	IMPORT_C static void GetImageTypesL(RImageTypeDescriptionArray& aImageTypeArray);
	IMPORT_C static void GetImageSubTypesL(const TUid aImageType, RImageTypeDescriptionArray& aSubTypeArray);
	IMPORT_C static void GetFileTypesL(RFileExtensionMIMETypeArray& aFileExtensionArray);
	IMPORT_C static void GetMimeTypeFileL(RFs& aFs, const TDesC& aFileName, TDes8& aMimeType);
	IMPORT_C static void GetMimeTypeDataL(const TDesC8& aImageData, TDes8& aMimeType);

	IMPORT_C static CImplementationInformationType* GetImplementationInformationL(TUid aImplementationUid);

	IMPORT_C static CImageDecoder* FileNewL(RFs& aFs, const TDesC& aSourceFilename, const TDesC8& aMIMEType, const TOptions aOptions = EOptionNone);
	IMPORT_C static CImageDecoder* FileNewL(RFs& aFs, const TDesC& aSourceFilename, const TOptions aOptions = EOptionNone, const TUid aImageType = KNullUid, const TUid aImageSubType = KNullUid, const TUid aDecoderUid = KNullUid);
	IMPORT_C static CImageDecoder* DataNewL(RFs& aFs, const TDesC8& aSourceData, const TDesC8& aMIMEType, const TOptions aOptions = EOptionNone);
	IMPORT_C static CImageDecoder* DataNewL(RFs& aFs, const TDesC8& aSourceData, const TOptions aOptions = EOptionNone, const TUid aImageType  = KNullUid, const TUid aImageSubType = KNullUid, const TUid aDecoderUid = KNullUid);
	IMPORT_C virtual ~CImageDecoder();

	IMPORT_C virtual void Convert(TRequestStatus* aRequestStatus, CFbsBitmap& aDestination, TInt aFrameNumber = 0);
	IMPORT_C virtual void Convert(TRequestStatus* aRequestStatus, CFbsBitmap& aDestination, CFbsBitmap& aDestinationMask, TInt aFrameNumber = 0);
	IMPORT_C virtual void ContinueConvert(TRequestStatus* aRequestStatus);
	IMPORT_C void Cancel();

	IMPORT_C TInt FrameCount() const;
	IMPORT_C TBool IsImageHeaderProcessingComplete() const;
	IMPORT_C void ContinueProcessingHeaderL();

	IMPORT_C const TFrameInfo& FrameInfo(TInt aFrameNumber = 0) const;
	IMPORT_C const CFrameImageData& FrameData(TInt aFrameNumber = 0) const;

	IMPORT_C TInt NumberOfImageComments() const;
	IMPORT_C HBufC* ImageCommentL(TInt aCommentNumber) const;
	IMPORT_C TInt NumberOfFrameComments(TInt aFrameNumber) const;
	IMPORT_C HBufC* FrameCommentL(TInt aFrameNumber, TInt aCommentNumber) const;

	IMPORT_C CFrameInfoStrings* FrameInfoStringsLC(TInt aFrameNumber = 0);
	IMPORT_C CFrameInfoStrings* FrameInfoStringsL(TInt aFrameNumber = 0);
	IMPORT_C TUid ImplementationUid() const;

	IMPORT_C void ImageType(TInt aFrameNumber, TUid& aImageType, TUid& aImageSubType) const;

protected:
	IMPORT_C CImageDecoder();

	// custom commands - for extended decoders
	IMPORT_C void CustomSyncL(TInt aParam);
	IMPORT_C void CustomAsync(TRequestStatus* aRequestStatus, TInt aParam);
	IMPORT_C CImageDecoderPlugin* Plugin() const;

private:
	static void MimeTypeGetDecoderListL(RImplInfoPtrArray& aDecoderList, const TDesC8& aMIMEType);
	static void ImageTypeGetDecoderListL(RImplInfoPtrArray& aDecoderList, const TDesC8& aImageHeader, const TUid aImageType, const TUid aImageSubType, const TUid aDecoderUid);
	static void SuffixTypeGetDecoderListL(RImplInfoPtrArray& aDecoderList, const TDesC& aFileName);

	static CImageDecoder* FileFindDecoderNewL(const RImplInfoPtrArray& aDecoderList, RFs& aFs, const TDesC& aSourceFilename, const TOptions aOptions);
	static CImageDecoder* FileDecoderNewL(const CImplementationInformation& aDecoderInfo, RFs& aFs, const TDesC& aSourceFilename, const TOptions aOptions);

	static CImageDecoder* DataFindDecoderNewL(const RImplInfoPtrArray& aDecoderList, RFs& aFs, const TDesC8& aSourceData, const TOptions aOptions);
	static CImageDecoder* DataDecoderNewL(const CImplementationInformation& aDecoderInfo, RFs& aFs, const TDesC8& aSourceData, const TOptions aOptions);

	static CImageDecodeConstruct* NewDecodeConstructL(const CImplementationInformation& aDecoderInfo);

	static void DoGetMimeTypeL(const TDesC& aFileName, const TDesC8& aMatchString, TDes8& aMimeType);

	static CImageDecoder* NewL(CImageDecodeConstruct* aConstruct, TOptions aOptions);
	static CImageDecoder* NewL();

	inline TBool ValidProperties() const;

	// Future proofing
	IMPORT_C virtual void ReservedVirtual1();
	IMPORT_C virtual void ReservedVirtual2();
	IMPORT_C virtual void ReservedVirtual3();
	IMPORT_C virtual void ReservedVirtual4();

private:
	MImageDecoderRelay* iRelay;

friend class CImageDecodeConstruct;	
	};

/**
 * @publishedAll
 * @released
 *
 * The public API for clients to call the Buffered Image Conversion Library decoders
 *
 */
class CBufferedImageDecoder : public CBase
	{
private:
	enum TState
		{
		EStateCreated,
		EStateOpening,
		EStateOpen,
		EStateConverting
		};

public:
	IMPORT_C static CBufferedImageDecoder* NewL(RFs& aFs);
	IMPORT_C virtual ~CBufferedImageDecoder();

	IMPORT_C void OpenL(const TDesC8& aSourceData, const TDesC8& aMIMEType, const CImageDecoder::TOptions aOptions = CImageDecoder::EOptionNone);
	IMPORT_C void OpenL(const TDesC8& aSourceData, const CImageDecoder::TOptions aOptions = CImageDecoder::EOptionNone, const TUid aImageType  = KNullUid, const TUid aImageSubType = KNullUid, const TUid aDecoderUid = KNullUid);
	IMPORT_C void ContinueOpenL();
	IMPORT_C void ContinueProcessingHeaderL();
	IMPORT_C TBool IsImageHeaderProcessingComplete() const;

	IMPORT_C void Convert(TRequestStatus* aRequestStatus, CFbsBitmap& aDestination, TInt aFrameNumber = 0);
	IMPORT_C void Convert(TRequestStatus* aRequestStatus, CFbsBitmap& aDestination, CFbsBitmap& aDestinationMask, TInt aFrameNumber = 0);
	IMPORT_C void ContinueConvert(TRequestStatus* aRequestStatus);

	IMPORT_C void Cancel();
	IMPORT_C void Reset();

	IMPORT_C void AppendDataL(const TDesC8& aData);

	IMPORT_C TInt FrameCount() const;
	IMPORT_C const TFrameInfo& FrameInfo(TInt aFrameNumber = 0) const;
	IMPORT_C const CFrameImageData& FrameData(TInt aFrameNumber = 0) const;

	IMPORT_C TInt NumberOfImageComments() const;
	IMPORT_C HBufC* ImageCommentL(TInt aCommentNumber) const;
	IMPORT_C TInt NumberOfFrameComments(TInt aFrameNumber) const;
	IMPORT_C HBufC* FrameCommentL(TInt aFrameNumber, TInt aCommentNumber) const;

	IMPORT_C CFrameInfoStrings* FrameInfoStringsLC(TInt aFrameNumber = 0);
	IMPORT_C CFrameInfoStrings* FrameInfoStringsL(TInt aFrameNumber = 0);
	IMPORT_C TUid ImplementationUid() const;

	IMPORT_C TBool ValidDecoder () const;

private:
	CBufferedImageDecoder(RFs& aFs);

private:
	RFs iFileSession;
	CImageDecoder::TOptions iOptions;
	TUid iImageType;
	TUid iImageSubType;
	TUid iDecoderUid;
	TPtr8 iBuffer;
	TPtr8 iMimeType;	

	CImageDecoder* iDecoder;

	TBool iImageTypeOpen; // Object was opened using image type	
	TState iState;

friend class RBufferedDecoderTest;
	};

/**
 * @publishedAll
 * @released
 *
 * The public API for clients to call the Image Conversion Library encoders
 *
 */
class CImageEncoder : public CBase
	{
public:

	/**
	 * Flags to control how the image is decoded.
	 * These can be combined using an OR operation.
	 */
	enum TOptions
		{
		/** No flag set */
		EOptionNone = 0x00,

		/** Perform the decoding in a separate thread */
		EOptionAlwaysThread = 0x01
		};
public:
	IMPORT_C static void GetImageTypesL(RImageTypeDescriptionArray& aImageTypeArray);
	IMPORT_C static void GetImageSubTypesL(const TUid aImageType, RImageTypeDescriptionArray& aSubTypeArray);
	IMPORT_C static void GetFileTypesL(RFileExtensionMIMETypeArray& aFileExtensionArray);
	IMPORT_C static CImageEncoder* FileNewL(RFs& aFs, const TDesC& aDestinationFilename, const TDesC8& aMIMEType, const TOptions aOptions = EOptionNone);
	IMPORT_C static CImageEncoder* FileNewL(RFs& aFs, const TDesC& aDestinationFilename, const TOptions aOptions = EOptionNone, const TUid aImageType = KNullUid, const TUid aImageSubType = KNullUid, const TUid aEncoderUid = KNullUid);
	IMPORT_C static CImageEncoder* DataNewL(HBufC8*& aDestinationData, const TDesC8& aMIMEType, const TOptions aOptions = EOptionNone);
	IMPORT_C static CImageEncoder* DataNewL(HBufC8*& aDestinationData, const TOptions aOptions = EOptionNone, const TUid aImageType = KNullUid, const TUid aImageSubType = KNullUid, const TUid aEncoderUid = KNullUid);

	IMPORT_C void Convert(TRequestStatus* aRequestStatus, const CFbsBitmap& aSource, const CFrameImageData* aFrameImageData = NULL);

	IMPORT_C virtual ~CImageEncoder();
	IMPORT_C void Cancel();

	IMPORT_C TUid ImplementationUid() const;

protected:
	IMPORT_C CImageEncoder();

	// custom commands - for extended encoders
	IMPORT_C void CustomSyncL(TInt aParam);
	IMPORT_C void CustomAsync(TRequestStatus* aRequestStatus, TInt aParam);
	IMPORT_C CImageEncoderPlugin* Plugin() const;

private:
	static void MimeTypeGetEncoderListL(RImplInfoPtrArray& aEncoderList, const TDesC8& aMIMEType);
	static void ImageTypeGetEncoderListL(RImplInfoPtrArray& aEncoderList, const TUid aImageType, const TUid aImageSubType, const TUid aEncoderUid);

   	static CImageEncodeConstruct* NewEncodeConstructL(const CImplementationInformation& aEncoderInfo);
	
	static CImageEncoder* NewL(CImageEncodeConstruct* aConstruct, TOptions aOptions);
	static CImageEncoder* NewL();

	inline TBool ValidProperties() const;

	// Future proofing
	IMPORT_C virtual void ReservedVirtual1();
	IMPORT_C virtual void ReservedVirtual2();
	IMPORT_C virtual void ReservedVirtual3();
	IMPORT_C virtual void ReservedVirtual4();

private:
	MImageEncoderRelay* iRelay;

friend class CImageEncodeConstruct;
	};

/**
 * @internalComponent
 *
 * ICL utility class used by ICL recognizer
 * Maintains an array of CImplementationInformation objects
 * so that data headers can be speedily matched against.
 * Updates the array when notified by ECOM of a change to the global
 * interface implementation registration data.
 * 
 */
class CIclRecognizerUtil : public CBase
	{
public:
	IMPORT_C static CIclRecognizerUtil* CIclRecognizerUtil::NewL();
	~CIclRecognizerUtil();
	IMPORT_C TBool GetMimeTypeL(const TDesC8& aImageData, const TDesC& aFileName, TDes8& aMimeType);

private:
	CIclRecognizerUtil();
	void ConstructL();

private:
	class CBody;
	CBody* iBody;	
	};

#endif // __IMAGECONVERSION_H__

