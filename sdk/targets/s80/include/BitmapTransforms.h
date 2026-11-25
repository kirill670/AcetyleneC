//
// BitmapTransforms.h
//
// Copyright (c) 2002-2003 Symbian Ltd.  All rights reserved.
//
// This is the public client API for the BitmapTransforms Library

#ifndef __BITMAPTRANSFORMS_H__
#define __BITMAPTRANSFORMS_H__

#include <e32base.h>
#include <fbs.h>
#include <bitdev.h>

class CBitmapRotatorBody;
class CBitmapScalerBody;
class CBitmapConverterBody;

const TUid KICLUidPostProcessCommand = { 0x101F7C18 };
/**
*
* The public API for clients to call the BitmapTransfroms Library bitmap rotation
* 
* @publishedAll
* @released
*            
*/
class CBitmapRotator : public CBase
{
public:
	
/**
 TRotationAngle is an enumeration within the namespace CBitmapRotator
 The enumeration provides a set of supported rotation and mirror angles:
 ERotation90DegreesClockwise is used to rotate a bitmap 90 degrees clockwise
 ERotation180DegreesClockwise is used to rotate a bitmap 180 degrees clockwise
 ERotation270DegreesClockwise is used to rotate a bitmap 270 degrees clcokwise
 EMirrorHorizontalAxis is used to mirror a bitmap about the horizontal axis
 EMirrorVerticalAxis is used to mirror a bitmap about the vertical axis
*/
	enum TRotationAngle
		{
		ERotation90DegreesClockwise,
		ERotation180DegreesClockwise,
		ERotation270DegreesClockwise,
		EMirrorHorizontalAxis,
		EMirrorVerticalAxis
		};

public:
	IMPORT_C static CBitmapRotator* NewL();
	IMPORT_C ~CBitmapRotator();
	IMPORT_C void Rotate(TRequestStatus* aRequestStatus, CFbsBitmap& aSrcBitmap, CFbsBitmap& aTgtBitmap, TRotationAngle aAngle);
	IMPORT_C void Rotate(TRequestStatus* aRequestStatus, CFbsBitmap& aBitmap, TRotationAngle aAngle);
	IMPORT_C TInt CustomCommand(TUid aUid, TAny* aParam);
	IMPORT_C void Cancel();

private:
	CBitmapRotator();
	void ConstructL();

private:
	CBitmapRotatorBody	*iBody;
};

/**
*
* The public API for clients to call 
* the BitmapTransforms library bitmap scaling
*
* @publishedAll
* @released
*
*/
class CBitmapScaler : public CBase
{
public:
	IMPORT_C static CBitmapScaler* NewL();
	IMPORT_C ~CBitmapScaler();
	IMPORT_C void Scale(TRequestStatus* aRequestStatus, CFbsBitmap& aSrcBitmap, CFbsBitmap& aTgtBitmap, TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void Scale(TRequestStatus* aRequestStatus, CFbsBitmap& aBitmap, const TSize& aDestinationSize, TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void Cancel();
	IMPORT_C TInt CustomCommand(TUid aUid, TAny* aParam);
    inline TInt DisablePostProcessing( TBool aState );
private:
	CBitmapScaler();
	void ConstructL();

private:
	CBitmapScalerBody* iBody;
	};

/**
*
* SetPostProcessing
* @param aState a boolean flag which if true will set post processing on
* Note by defualt the scaler has post processing on
* @internalTechnology
*
*/
inline TInt CBitmapScaler::DisablePostProcessing( TBool aState )
	{
	return CustomCommand( KICLUidPostProcessCommand,&aState);
	}

#endif __BITMAPTRANSFORMS_H__

