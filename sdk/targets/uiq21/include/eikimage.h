// EIKIMAGE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKIMAGE_H__)
#define __EIKIMAGE_H__

#include <eikalign.h>

class CFbsBitmap;
class CBitmapContext;

/**
 *
 * This class provides functions that enable you to package bitmaps into
 * an image.
 *
 * Two bitmaps can be packaged, one for the image itself and, optionally,
 * another for the images mask.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikImage : public CEikAlignedControl
	{
public:
	IMPORT_C CEikImage();
	IMPORT_C ~CEikImage();
public: // framework
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
public: // new functions
	IMPORT_C void CreatePictureFromFileL(const TDesC& aFilename,TInt aMainId,TInt aMaskId=-1);
	IMPORT_C void SetPicture(const CFbsBitmap* aBitmap,const CFbsBitmap* aMaskBitmap=NULL);
	IMPORT_C void SetEmphasis(TBool aEmphasis);
	IMPORT_C void SetPictureOwnedExternally(TBool aOwnership);
	IMPORT_C const CFbsBitmap* Bitmap() const;
	IMPORT_C const CFbsBitmap* Mask() const;
	IMPORT_C void SetBitmap(const CFbsBitmap* aBitmap);
	IMPORT_C void SetMask(const CFbsBitmap* aMaskBitmap);
	IMPORT_C void SetNewBitmaps(const CFbsBitmap* aNewBitmap,const CFbsBitmap* aNewMask);
	IMPORT_C TBool IsPictureOwnedExternally();
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void Reserved_2();
private:
	enum TFlags
		{
		EFullEmphasis			= 0x01,
		EPictureOwnedExternally = 0x02,
		ESameBitmapAndMask		= 0x04
		};
private:
	const CFbsBitmap* iBitmap;
	const CFbsBitmap* iMaskBitmap;
	TInt iImFlags;
	TInt iSpare;
	};

#endif
