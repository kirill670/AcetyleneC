// GRAPHICSACCELERATOR.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __GRAPHICSACCELERATOR_H__
#define __GRAPHICSACCELERATOR_H__

#include <e32std.h>
#include <gdi.h>

//
// Bitmaps
//

// Forward references
class CFbsBitmap;
class TAcceleratedBitmapSpec;

/**
 *
 * Information about an accelerated bitmap.
 *
 */
class TAcceleratedBitmapInfo
	{
public:
	TDisplayMode	iDisplayMode;
	TUint8*			iAddress;
	TSize			iSize;
	TInt			iLinePitch;
	TInt			iPixelShift;
	TUint8*			iPhysicalAddress;
	};

/**
 *
 * Bitmap class representing a hardware buffer
 * such as the display buffer.
 *
 */
class RHardwareBitmap
	{
	friend class CBitwiseBitmap;
	friend class CFbsScreenDevice;
public:

/** Default constructor.
 */
	inline RHardwareBitmap();

/**
 *
 * Constructor taking the handle of an existing
 * RHardwareBitmap to duplicate it.
 *
 */
	inline RHardwareBitmap(TInt aHandle);

/**
 *
 * Get information about the accelerated bitmap.
 *
 * @param     "TAcceleratedBitmapInfo& aInfo"
 *            Information structure to fill.
 * @returns   "TInt"
 *            <code>KErrNone</code>, if successful;
 *            <code>KErrUnknown</code>, if there is no bitmap
 *            to accelerate.
 */
	IMPORT_C TInt GetInfo(TAcceleratedBitmapInfo& aInfo) const;
private:
	IMPORT_C TInt SetAsScreenReference(TInt aScreen=-1);
	IMPORT_C TInt Create(TDisplayMode aDisplayMode, TSize aSize, TUid aCreatorUid);
	IMPORT_C void Destroy();
public:
	TInt iHandle;	// Must be only member data
	};

inline RHardwareBitmap::RHardwareBitmap()
	: iHandle(0)
	{}
inline RHardwareBitmap::RHardwareBitmap(TInt aHandle)
	: iHandle(aHandle)
	{}


class TBitmapLockCount
	{
	friend class TAcceleratedBitmapSpec;
public:
	inline TBitmapLockCount() : iCount(0) {}
private:
	inline TInt Inc() { return iCount++; }
	inline TInt Dec() { return --iCount; }
private:
	TInt iCount;
	};


class TAcceleratedBitmapSpec
	{
public:
	// Constructors
	inline TAcceleratedBitmapSpec();
	IMPORT_C TAcceleratedBitmapSpec(CFbsBitmap* aBitmap);
	IMPORT_C TAcceleratedBitmapSpec(RHardwareBitmap aBitmap);
	// Bitmap access (use with caution, see documentation)
	IMPORT_C TInt GetInfo(TAcceleratedBitmapInfo& aInfo) const;
	inline void Lock(TBitmapLockCount& aCount);
	inline void Lock(TBitmapLockCount& aCount,TAcceleratedBitmapInfo& aInfo);
	inline void	Unlock(TBitmapLockCount& aCount);
	// enums
	enum TAcceleratedBitmapType
		{
		ENoBitmap,
		EFbsBitmap,
		EHardwareBitmap,
		};
	enum TAcceleratedBitmapLock
		{
		EBitmapIsStatic,
		EBitmapNeedsLocking,
		};
	// Getters
	inline TAcceleratedBitmapType	Type() const;
	inline TInt						Handle() const;
private:
	IMPORT_C void DoLock(TBitmapLockCount& aCount);
	IMPORT_C void DoLock(TBitmapLockCount& aCount,TAcceleratedBitmapInfo& aInfo);
	IMPORT_C void DoUnlock(TBitmapLockCount& aCount);
private:
	TUint8	iType;			// TAcceleratedBitmapType
	TUint8	iLockStatus;	// TAcceleratedBitmapLock
	TUint8	iSpare1;
	TUint8	iSpare2;
	TInt	iHandle;
	};

inline TAcceleratedBitmapSpec::TAcceleratedBitmapSpec()
	: iType(ENoBitmap), iLockStatus(EBitmapIsStatic)
	{}

inline void TAcceleratedBitmapSpec::Lock(TBitmapLockCount& aCount)
	{ if(iLockStatus==EBitmapNeedsLocking) DoLock(aCount); }

inline void TAcceleratedBitmapSpec::Lock(TBitmapLockCount& aCount,TAcceleratedBitmapInfo& aInfo)
	{ if(iLockStatus==EBitmapNeedsLocking) DoLock(aCount,aInfo); }

inline void	TAcceleratedBitmapSpec::Unlock(TBitmapLockCount& aCount)
	{ if(iLockStatus==EBitmapNeedsLocking) DoUnlock(aCount); }

inline TAcceleratedBitmapSpec::TAcceleratedBitmapType TAcceleratedBitmapSpec::Type() const
	{ return (TAcceleratedBitmapSpec::TAcceleratedBitmapType)iType; }

inline TInt TAcceleratedBitmapSpec::Handle() const
	{ return iHandle; }


//
// Accelerator capabilities
//

enum TTransparencyType
	{
	ETransparentPixelZero,
	ETransparentPixel,
	ETransparentColor,
	ETransparent1555,
	};

class TGraphicsAcceleratorCaps
	{
public:
/*
A class to hold information about the capabilities of a graphics accelerator.
*/
	enum TClipCaps	// Bit flags
		{
		EClipToBitmap = 1,	// Will always clip all operations to the bitmap
		EClipping = 2		// Is able to clip operations to a region
		};

	enum TMaskBitmapCaps	// Enum
		{
		EMaskBitmapNone = 0,
		EMaskBitmapAnyDisplayMode,
		EMaskBitmapMatchingDisplayMode,
		EMaskBitmapGray2,
		};

	enum TAlphaChannelCaps	//Bit flags
    	{
		EAlpha4444 = 1,	// Bitmaps with 4 bits for Alpha value and Red, Green, Blue components
		EAlpha8888 = 2, // Bitmaps with 8 bits for Alpha value and Red, Green, Blue components
		EAlpha1555 = 4, // Bitmaps with 1 bit for Alpha value and 5 bits for Red, Green, and Blue
		};

	enum TAlphaBitmapCaps	//Bit flags
    	{
		EAlphaBitmapGray256 = 1,
		EAlphaBitmapColor16M = 2,
		EAlphaBitmapMatchingMode = 4,	// Alpha bitmap must be same mode as source
		};

	enum TPatternSizeCaps	//Bit flags
		{
		EPatternSizeAny = 0xFFFFFFFF,
		};

	enum TPatternCaps	//Bit flags
		{
		EPatternAnyDisplayMode = 1,			// Patterns can be in any supported display mode
		EPatternMatchingDisplayMode = 2,	// Pattern must be in same displ mode as target
		EPatternMustBeSquare = 4,			// The pattern must be square (width==height)
		};
		
	enum TPolygonCaps	// Bit flags for fill rules (see CGraphicsContext::TFillRule)
		{
		EPolygonFillAlternate = 1,
		EPolygonFillWinding = 2,
		};

	TInt			iStructureSize;	// The size of this class
	TInt			iVersion;		// == 1 to specify current API
	TUid			iVendorUid;		// Optional ID
	
	TUint			iDisplayModes;	// One bit for each TDisplayMode enumeration
	TUint			iClipping;		// TClipCaps bit flags
	TMaskBitmapCaps	iMaskType;		// Mask type used
	TUint			iTransparency;	// Bit flag for each TTransparencyType supported
	TUint			iAlphaChannel;	// TAlphaChannelCaps bit flags
	TUint			iAlphaBitmap;	// TAlphaBitmapCaps bit flags
	TUint			iPatternSizes;	// a mask bit for each power of 2, or EPatternSizeAny
	TUint			iPattern;		// TPatternCaps bit flags
	TUint			iPolygon;		// TPolygonCaps bit flags
	TUint			iReserved[4];	// Reserved (set to zero)
	};



//
// TGraphicsOperation
//

class TGraphicsOperation
/*
Base class for all graphics operation argument specifications
*/
	{
public:
	enum TGopFunction
		{								// Require arguments commented below here

		EFilledRect,					// (TRect,TRgb)
		EFilledRectUsingDrawMode,		// (TRect,TRgb,CGraphicsContext:TDrawMode)
		EFilledRectWithPattern,			// (TRect,TGopFillPattern)
		EInvertRect,					// (TRect)
		EFadeRect,						// (TRect,TGopFadeParams)

		EBitBlt,						// (TPoint,TAcceleratedBitmapSpec,TRect&)
		EBitBltMasked,					// (TPoint,TAcceleratedBitmapSpec,TRect&,TAcceleratedBitmapSpec aMask)
		EBitBltTransparent,				// (TPoint,TAcceleratedBitmapSpec,TRect&,TGopTransparency)
		EBitBltAlphaChannel,			// (TPoint,TAcceleratedBitmapSpec,TRect&)
		EBitBltAlphaBitmap,				// (TPoint,TAcceleratedBitmapSpec,TRect&,TAcceleratedBitmapSpec aAlpha)

		EScaledBitBlt,					// (TRect,TAcceleratedBitmapSpec,TRect&)
		EScaledBitBltMasked,			// (TRect,TAcceleratedBitmapSpec,TRect&,TAcceleratedBitmapSpec aMask)
		EScaledBitBltTransparent,		// (TRect,TAcceleratedBitmapSpec,TRect&,TGopTransparency)
		EScaledBitBltAlphaChannel,		// (TRect,TAcceleratedBitmapSpec,TRect&)
		EScaledBitBltAlphaBitmap,		// (TRect,TAcceleratedBitmapSpec,TRect&,TAcceleratedBitmapSpec aAlpha)

		EFilledPolygon,					// (TRGb aColor,CGraphicsContext::TFillRule aFillRule,TInt aNumPoints,TPoint[])
		EFilledPolygonWithPattern,		// (TGopFillPattern,CGraphicsContext::TFillRule aFillRule,TInt aNumPoints,TPoint[])
		};
public:
	// Getters
	inline TGopFunction Function() const	{ return iFunction; }
	inline TInt Size() const				{ return iSize; }
	// Utility functions 
	inline TGraphicsOperation* Next() const;
	inline void Append(TInt aNumBytes,TAny* aData);
protected:
	inline TGraphicsOperation(TGopFunction aFunction, TInt aArgSize);
	inline TGraphicsOperation() {}
protected:
	TGopFunction iFunction;
	TInt iSize;  // Total size of derived class
	};

inline TGraphicsOperation::TGraphicsOperation(TGopFunction aFunction, TInt aSize)
	: iFunction(aFunction) , iSize(aSize) {}

inline TGraphicsOperation* TGraphicsOperation::Next() const
	{ return (TGraphicsOperation*)((TUint8*)this+iSize); }

inline void TGraphicsOperation::Append(TInt aNumBytes,TAny* aData)
	{
	Mem::Copy(Next(),aData,aNumBytes);
	iSize += aNumBytes;
	}



//
// Graphics accelerator
//

class CGraphicsAccelerator : public CBase
/*
Abstract base class for all graphics accelerators
*/
	{
public:
	// Return the capabilities of this accelerator
	virtual const TGraphicsAcceleratorCaps* Capabilities() = 0;

	// Perform a graphics operation
	virtual TInt Operation(const TGraphicsOperation& aOperation) = 0;
	virtual TInt Operation(const TGraphicsOperation& aOperation,TInt aNumClipRects,TRect* aClipRects) = 0;
	
	// Process a buffer of TGraphicsOperation. (Each operation immediately follows the
	// one preceding it in the buffer)
	virtual TInt Operation(TDes8& aBuffer) = 0;
	virtual TInt Operation(TDes8& aBuffer,TInt aNumClipRects,TRect* aClipRects) = 0;
public:
	// Reserved virtual functions for future use
	virtual void Reserved_1() = 0;
	virtual void Reserved_2() = 0;
	virtual void Reserved_3() = 0;
	virtual void Reserved_4() = 0;
	};



class CSoftwareGraphicsAccelerator : public CGraphicsAccelerator
	{
public:
	// Create a new CSoftwareGraphicsAccelerator for use with a given bitmap
	IMPORT_C static CSoftwareGraphicsAccelerator* NewL(CFbsBitmap* aBitmap);

	// Get the non-bitmap-specific capabilities of the hardware accelerator.
	IMPORT_C static const TGraphicsAcceleratorCaps* GenericCapabilities();
public:
	// From CGraphicsAccelerator
	virtual const TGraphicsAcceleratorCaps* Capabilities() = 0;
	virtual TInt Operation(const TGraphicsOperation& aOperation) = 0;
	virtual TInt Operation(const TGraphicsOperation& aOperation,TInt aNumClipRects,TRect* aClipRects) = 0;
	virtual TInt Operation(TDes8& aBuffer) = 0;
	virtual TInt Operation(TDes8& aBuffer,TInt aNumClipRects,TRect* aClipRects) = 0;
	// From CGraphicsAccelerator
	virtual void Reserved_1() = 0;
	virtual void Reserved_2() = 0;
	virtual void Reserved_3() = 0;
	virtual void Reserved_4() = 0;
	};



class CHardwareGraphicsAccelerator : public CGraphicsAccelerator
	{
public:

/** Create a new CHardwareGraphicsAccelerator for use with a given hardware bitmap.
 */
	IMPORT_C static CHardwareGraphicsAccelerator* NewL(RHardwareBitmap aBitmap);

/** Get the non-bitmap-specific capabilities of the hardware accelerator.
 */
	IMPORT_C static const TGraphicsAcceleratorCaps* GenericCapabilities();
public:
	// From CGraphicsAccelerator
	virtual const TGraphicsAcceleratorCaps* Capabilities() = 0;
	virtual TInt Operation(const TGraphicsOperation& aOperation) = 0;
	virtual TInt Operation(const TGraphicsOperation& aOperation,TInt aNumClipRects,TRect* aClipRects) = 0;
	virtual TInt Operation(TDes8& aBuffer) = 0;
	virtual TInt Operation(TDes8& aBuffer,TInt aNumClipRects,TRect* aClipRects) = 0;
	// From CGraphicsAccelerator
	virtual void Reserved_1() = 0;
	virtual void Reserved_2() = 0;
	virtual void Reserved_3() = 0;
	virtual void Reserved_4() = 0;
	};



//
// Classes used as arguments to graphics operations
//

class TGopFillPattern
	{
public:
	TAcceleratedBitmapSpec	iBitmap;
	TPoint					iOrigin;
	};

class TGopFadeParams	// color component C = ( ( iScale * C ) >> 8 )+iOffset;
	{
public:
	TInt iScale;
	TInt iOffset;
	};

class TGopTransparency
	{
public:
	inline TGopTransparency(TTransparencyType aType)	: iType(aType), iParam(0) {}
	inline TGopTransparency(TInt aPixelValue)			: iType(ETransparentPixel), iParam(aPixelValue) {}
	inline TGopTransparency(TRgb aRgb)					: iType(ETransparentColor), iParam(aRgb.Value()) {}
	inline TRgb Color()	const							{ return TRgb(iParam); }
	inline TInt Pixel()	const							{ return iParam; }
public:
	TTransparencyType	iType;
	TUint32				iParam;
	};


//
// Wrapper classes for graphics operation arguments
//

#ifdef __WINS__
#pragma warning(disable : 4355) // Disable warning - 'this' : used in base member initializer list
#endif

class TGopFilledRect : public TGraphicsOperation
	{
public:
	inline TGopFilledRect(const TRect& aRect,TRgb aColor)
		: TGraphicsOperation(EFilledRect,sizeof(*this)), iRect(aRect) , iColor(aColor) {}
public:
	TRect	iRect;
	TRgb	iColor;
	};

class TGopFilledRectUsingDrawMode : public TGraphicsOperation
	{
public:
	inline TGopFilledRectUsingDrawMode(const TRect& aRect,TRgb aColor,CGraphicsContext::TDrawMode aDrawMode)
		: TGraphicsOperation(EFilledRectUsingDrawMode,sizeof(*this)), iRect(aRect) , iColor(aColor) , iDrawMode(aDrawMode) {}
public:
	TRect						iRect;
	TRgb						iColor;
	CGraphicsContext::TDrawMode	iDrawMode;
	};

class TGopFilledRectWithPattern : public TGraphicsOperation
	{
public:
	inline TGopFilledRectWithPattern(const TRect& aRect,TGopFillPattern aPattern)
		: TGraphicsOperation(EFilledRectWithPattern,sizeof(*this)), iRect(aRect) , iPattern(aPattern) {}
public:
	TRect			iRect;
	TGopFillPattern iPattern;
	};

class TGopInvertRect : public TGraphicsOperation
	{
public:
	inline TGopInvertRect(const TRect& aRect)
		: TGraphicsOperation(EInvertRect,sizeof(*this)), iRect(aRect) {}
public:
	TRect	iRect;
	};

class TGopFadeRect : public TGraphicsOperation
	{
public:
	inline TGopFadeRect(const TRect& aRect, const TGopFadeParams aFade)
		: TGraphicsOperation(EFadeRect,sizeof(*this)), iRect(aRect), iFade(aFade) {}
public:
	TRect			iRect;
	TGopFadeParams	iFade;
	};

class TGopBitBlt : public TGraphicsOperation
	{
public:
	inline TGopBitBlt(const TPoint& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect)
		: TGraphicsOperation(EBitBlt,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect) {}
public:
	TPoint					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	};

class TGopBitBltMasked : public TGraphicsOperation
	{
public:
	inline TGopBitBltMasked(const TPoint& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect, TAcceleratedBitmapSpec aMask)
		: TGraphicsOperation(EBitBltMasked,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect), iMask(aMask) {}
public:
	TPoint					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	TAcceleratedBitmapSpec	iMask;
	};

class TGopBitBltTransparent : public TGraphicsOperation
	{
public:
	inline TGopBitBltTransparent(const TPoint& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect, TGopTransparency aTransparency)
		: TGraphicsOperation(EBitBltTransparent,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect), iTransparency(aTransparency) {}
public:
	TPoint					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	TGopTransparency		iTransparency;
	};

class TGopBitBltAlphaChannel : public TGraphicsOperation
	{
public:
	inline TGopBitBltAlphaChannel(const TPoint& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect)
		: TGraphicsOperation(EBitBltAlphaChannel,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect) {}
public:
	TPoint					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	};

class TGopBitBltAlphaBitmap : public TGraphicsOperation
	{
public:
	inline TGopBitBltAlphaBitmap(const TPoint& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect, TAcceleratedBitmapSpec aAlphaBitmap)
		: TGraphicsOperation(EBitBltAlphaBitmap,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect), iAlphaBitmap(aAlphaBitmap) {}
public:
	TPoint					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	TAcceleratedBitmapSpec	iAlphaBitmap;
	};

class TGopScaledBitBlt : public TGraphicsOperation
	{
public:
	inline TGopScaledBitBlt(const TRect& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect)
		: TGraphicsOperation(EScaledBitBlt,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect) {}
public:
	TRect					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	};

class TGopScaledBitBltMasked : public TGraphicsOperation
	{
public:
	inline TGopScaledBitBltMasked(const TRect& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect, TAcceleratedBitmapSpec aMask)
		: TGraphicsOperation(EScaledBitBltMasked,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect), iMask(aMask) {}
public:
	TRect					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	TAcceleratedBitmapSpec	iMask;
	};

class TGopScaledBitBltTransparent : public TGraphicsOperation
	{
public:
	inline TGopScaledBitBltTransparent(const TRect& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect, TGopTransparency aTransparency)
		: TGraphicsOperation(EScaledBitBltTransparent,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect), iTransparency(aTransparency) {}
public:
	TRect					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	TGopTransparency		iTransparency;
	};

class TGopScaledBitBltAlphaChannel : public TGraphicsOperation
	{
public:
	inline TGopScaledBitBltAlphaChannel(const TRect& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect)
		: TGraphicsOperation(EScaledBitBltAlphaChannel,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect) {}
public:
	TRect					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	};

class TGopScaledBitBltAlphaBitmap : public TGraphicsOperation
	{
public:
	inline TGopScaledBitBltAlphaBitmap(const TRect& aDestination, TAcceleratedBitmapSpec aSourceBitmap, TRect& aSourceRect, TAcceleratedBitmapSpec aAlphaBitmap)
		: TGraphicsOperation(EScaledBitBltAlphaBitmap,sizeof(*this)), iDestination(aDestination), iSourceBitmap(aSourceBitmap), iSourceRect(aSourceRect), iAlphaBitmap(aAlphaBitmap) {}
public:
	TRect					iDestination;
	TAcceleratedBitmapSpec	iSourceBitmap;
	TRect					iSourceRect;
	TAcceleratedBitmapSpec	iAlphaBitmap;
	};

class TGopFilledPolygon : public TGraphicsOperation
	{
public:
	inline TGopFilledPolygon(TRgb aColor, CGraphicsContext::TFillRule aFillRule)
		: TGraphicsOperation(EFilledPolygon,sizeof(*this)), iColor(aColor), iFillRule(aFillRule), iNumPoints(0) {}
	inline void AddPoints(TInt aNumPoints, TPoint* aPoints);
public:
	TRgb						iColor;
	CGraphicsContext::TFillRule iFillRule;
	TInt						iNumPoints;
	};

inline void TGopFilledPolygon::AddPoints(TInt aNumPoints, TPoint* aPoints)
	{ Append(aNumPoints*sizeof(TPoint),aPoints); iNumPoints += aNumPoints; }

class TGopFilledPolygonWithPattern : public TGraphicsOperation
	{
public:
	inline TGopFilledPolygonWithPattern(TGopFillPattern aPattern, CGraphicsContext::TFillRule aFillRule)
		: TGraphicsOperation(EFilledPolygonWithPattern,sizeof(*this)), iPattern(aPattern), iFillRule(aFillRule), iNumPoints(0) {}
	inline void AddPoints(TInt aNumPoints, TPoint* aPoints);
public:
	TGopFillPattern				iPattern;
	CGraphicsContext::TFillRule iFillRule;
	TInt						iNumPoints;
	};

inline void TGopFilledPolygonWithPattern::AddPoints(TInt aNumPoints, TPoint* aPoints)
	{ Append(aNumPoints*sizeof(TPoint),aPoints); iNumPoints += aNumPoints; }





#endif