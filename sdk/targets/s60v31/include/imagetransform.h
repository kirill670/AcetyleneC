// ImageTransform.h
//
// Copyright (c) 2004 Symbian Software Ltd. All rights reserved
//
// This is the public client API for the Image Transform Library

#ifndef __IMAGETRANSFORM_H__
#define __IMAGETRANSFORM_H__

#include <e32base.h>
#include <fbs.h>

// fwd refs
class CImageTransformFramework;	//fwd ref
class CImageTransformPluginExtension;

/**
The public API for clients to call the Image Transform (scaling) library.
This class provides functions to scale images held in files or descriptors.

@publishedAll
@released
*/
class CImageTransform : public CBase
	{
public:
	/**
	Flags to control how the image is transformed.
	These can be combined using an OR operation.
	*/
	enum TOptions
		{
		/** No flag set */
		EOptionNone = 0x00,
		EThumbnail	= 0x01,
		EEnumBoundary = 0x02
		};

public:
	IMPORT_C static CImageTransform* NewL(RFs& aFs);
	IMPORT_C ~CImageTransform();
	IMPORT_C void SetPluginUidL(TUid aPluginUid);
	IMPORT_C void SetSourceFilenameL(const TDesC& aFilename);
	IMPORT_C void SetSourceDataL(const TDesC8& aData);
	IMPORT_C void SetSourceMimeTypeL(const TDesC8& aMIMEType);
	IMPORT_C void SetSourceImageTypeL(TUid aImageType, TUid aImageSubType = KNullUid);
	IMPORT_C void SetSourceRect(const TRect& aRect);
	IMPORT_C void ClearSourceRect();

	IMPORT_C void SetDestFilenameL(const TDesC& aFilename);
	IMPORT_C void SetDestDataL(HBufC8*& aData);
	IMPORT_C void SetDestSizeInPixelsL(const TSize& aDestinationSize, TBool aMaintainAspectRatio = ETrue);

	IMPORT_C void SetOptionsL(TUint aOptions);
	IMPORT_C void SetPreserveImageData(TBool aPreserveImageData);

	IMPORT_C void SetupL();
	IMPORT_C void Transform(TRequestStatus& aStatus);
	IMPORT_C void CancelTransform();
	IMPORT_C void Reset();
	IMPORT_C CImageTransformPluginExtension* Extension() const;

private:
	CImageTransform();
	void ConstructL(RFs& aFs);

private:
	CImageTransformFramework* iBody;
	};

// __IMAGETRANSFORM_H__
#endif
