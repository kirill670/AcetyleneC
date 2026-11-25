// Copyright (c) 2002 Symbian Ltd.  All rights reserved.

/**
 * @file EMSPictureIE.h
 *
 * Defines  CEmsPictureIE  class
 */


#ifndef __EMSPictureIE_H__
#define __EMSPictureIE_H__

#include "EMSInformationElement.h"

/**
 * CEmsPictureIE wraps the creation & modification of the picture small/large and vriable
 * information element into a single class.
 *
 * Format of Small/Large
 * ----------------------------
 *
 * Position (Octet)		Bit		Description					
 *	1							Start Position
 *	2..n						Picture Data
 *
 * Format of variable
 * ----------------------------
 *
 * Position (Octet)		Bit		Description					
 *	1							Start Position
 *  2							Width
 *  3							Height
 *	4..n						Picture Data
 *
 * @see 3gpp Spec V5 section 9.2.3.24.10.1.7/8/9
 */

#define KSmallPicSize TSize(16,16)
#define KLargePicSize TSize(32,32)

class CGraphicsDevice;
class CFbsBitmap;
class CEmsPictureIE : public CEmsInformationElement
	{
friend class CEmsAnimationIE;
public:
	enum {ESmallBufSize=32, ELargeBufSize=128, EEnhancedMaxSize=128};
	enum TColors {EWhite = 0, EBlack=1};

	IMPORT_C static CEmsPictureIE* NewL(const CFbsBitmap& aBitmap); // resizes bitmap if needed
	static CEmsPictureIE* NewL();
	IMPORT_C CEmsInformationElement* DuplicateL() const;
	IMPORT_C ~CEmsPictureIE();	
	IMPORT_C void CopyL(const CEmsPictureIE& aSrc);
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C CFbsBitmap* GetBitmapL()const;

private:	
	virtual void EncodeBodyL(TPtr8 aPtr, TBool aIsForSerialisation) const;
	virtual void DecodeBodyL(const TPtrC8 aPtr, TBool aIsFromSerialisation);
	CEmsPictureIE();
	void ConstructL(const CFbsBitmap& aBitmap);
	inline HBufC8* PictureBuf() const ;
	static HBufC8* CreatePictureBufferL(const CFbsBitmap& aBitmap);
	TSize iSize;
	HBufC8* iPictureBuf;
	};
#include "emspictureie.inl"
#endif __EMSPictureIE_H__


//eof.
