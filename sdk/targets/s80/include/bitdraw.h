// BITDRAW.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __BITDRAW_H__
#define __BITDRAW_H__

#include <gdi.h>

enum TScreenDriverPanic
	{
	EScreenDriverPanicNoDevicePresent=1,
	EScreenDriverPanicInvalidParameter,
	EScreenDriverPanicInvalidDisplayMode,
	EScreenDriverPanicInvalidWindowHandle,
	EScreenDriverPanicOutOfBounds,
	EScreenDriverPanicZeroLength,
	EScreenDriverPanicNullPointer,
	EScreenDriverPanicInvalidPointer,
	EScreenDriverPanicAlphaBlendInvariant,
	EScreenDriverPanicIvalidMethodCall
	};

GLREF_C void Panic(TScreenDriverPanic aPanicCode);

class CFbsDrawDevice : public CBase
	{
public:
	enum TShadowMode
		{
		ENoShadow	= 0x0,
		EShadow		= 0x1,
		EFade		= 0x2,
		EShadowFade	= 0x3
		};
	enum TOrientation
		{
		EOrientationNormal,
		EOrientationRotated90,
		EOrientationRotated180,
		EOrientationRotated270
		};
public:
	IMPORT_C static CFbsDrawDevice* NewScreenDeviceL(TScreenInfoV01 aInfo,TDisplayMode aDispMode);
	IMPORT_C static CFbsDrawDevice* NewBitmapDeviceL(TScreenInfoV01 aInfo,TDisplayMode aDispMode);
	IMPORT_C static TDisplayMode DisplayMode16M();
	virtual TDisplayMode DisplayMode() const = 0;
	virtual TInt LongWidth() const = 0;
	virtual void MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs,TBool aMapForwards) = 0;
	virtual void ReadLine(TInt aX,TInt aY,TInt aLength,TAny* aBuffer,TDisplayMode aDispMode) const = 0;
	virtual TRgb ReadPixel(TInt aX,TInt aY) const = 0;
	virtual TUint32* ScanLineBuffer() const = 0;
	virtual TInt ScanLineBytes() const = 0;
	virtual TDisplayMode ScanLineDisplayMode() const = 0;
	virtual TSize SizeInPixels() const = 0;
	virtual TInt HorzTwipsPerThousandPixels() const = 0;
	virtual TInt VertTwipsPerThousandPixels() const = 0;
	virtual void OrientationsAvailable(TBool aOrientation[4]) = 0;
	virtual TBool SetOrientation(TOrientation aOrientation) = 0;
	virtual void WriteBinary(TInt aX,TInt aY,TUint32* aBuffer,TInt aLength,TInt aHeight,TRgb aColor,CGraphicsContext::TDrawMode aDrawMode) = 0;
	virtual void WriteBinaryLine(TInt aX,TInt aY,TUint32* aBuffer,TInt aLength,TRgb aColor,CGraphicsContext::TDrawMode aDrawMode) = 0;
	virtual void WriteBinaryLineVertical(TInt aX,TInt aY,TUint32* aBuffer,TInt aHeight,TRgb aColor,CGraphicsContext::TDrawMode aDrawMode,TBool aUp) = 0;
	virtual void WriteRgb(TInt aX,TInt aY,TRgb aColor,CGraphicsContext::TDrawMode aDrawMode) = 0;
	virtual void WriteRgbMulti(TInt aX,TInt aY,TInt aLength,TInt aHeight,TRgb aColor,CGraphicsContext::TDrawMode aDrawMode) = 0;
	virtual void WriteRgbAlphaLine(TInt aX,TInt aY,TInt aLength,TUint8* aRgbBuffer,TUint8* aMaskBuffer) = 0;
	virtual void WriteLine(TInt aX,TInt aY,TInt aLength,TUint32* aBuffer,CGraphicsContext::TDrawMode aDrawMode) = 0;
public:
	virtual TInt InitScreen() {return(KErrNone);}
	virtual void SetAutoUpdate(TBool) {}
	virtual void SetBits(TAny*) {}
	virtual TInt SetCustomPalette(const CPalette*) { return KErrNotSupported; }
	virtual TInt GetCustomPalette(CPalette*&) { return KErrNotSupported; }
	virtual void SetDisplayMode(CFbsDrawDevice*) {}
	virtual void SetDitherOrigin(const TPoint&) {}
	virtual void SetUserDisplayMode(TDisplayMode) {}
	virtual void SetShadowMode(TShadowMode) {}
	virtual void SetFadingParameters(TUint8 /*aBlackMap*/,TUint8 /*aWhiteMap*/) {}
	virtual void ShadowArea(const TRect&) {} // Obeys shadow mode
	virtual void ShadowBuffer(TInt,TUint32*) {} // Obeys shadow mode
	virtual void Update() {}
	virtual void Update(const TRegion&) {}
	virtual void UpdateRegion(const TRect&) {}
public:
	virtual void WriteRgbAlphaMulti(TInt aX,TInt aY,TInt aLength,TRgb aColor,const TUint8* aMaskBuffer) = 0;
	virtual void WriteRgbAlphaLine(TInt aX,TInt aY,TInt aLength,
								const TUint8* aRgbBuffer1,
								const TUint8* aBuffer2,
								   const TUint8* aMaskBuffer,
								   CGraphicsContext::TDrawMode aDrawMode) = 0;
	virtual void Reserved_3() = 0;
	virtual void Reserved_4() = 0;
	virtual void Reserved_5() = 0;
	};

#endif

