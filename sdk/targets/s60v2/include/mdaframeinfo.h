// MdaFrameInfo.h
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAFRAMEINFO_H__
#define __MDAFRAMEINFO_H__

// TFrameInfoMCL
/**
@internalTechnology
@deprecated
*/
class TFrameInfoMCL
	{
public:
	/** Flags that define the attributes of a frame.
	These can be combined using an OR operation.
	*/
	enum TFrameInfoFlags
		{
		/** Grayscale if not set.
		*/
		EColor					= 0x00000001,
		/** Fully opaque if not set.
		*/
		ETransparencyPossible	= 0x00000002,
		/** Will only scale to 1/2,1/4 & 1/8th if not set.
		*/
		EFullyScaleable			= 0x00000004,
		/** Scaling need not maintain aspect ratio if not set.
		*/
		EConstantAspectRatio	= 0x00000008,
		/** Will not use error diffusion if not set.
		*/
		ECanDither				= 0x00000010,
		/** Set if the image contains alpha-blending information.
		*/
		EAlphaChannel			= 0x00000020,
		/** Mutually exclusive image disposal method 1.
		*/
		ELeaveInPlace			= 0x00000040,
		/** Mutually exclusive image disposal method 2.
		*/
		ERestoreToBackground	= 0x00000080,
		/** Mutually exclusive image disposal method 3.
		*/
		ERestoreToPrevious		= 0x00000100
		};

public:

	/**
	The coordinates of the frame within the screen in pixels.
	*/
	TRect iFrameCoordsInPixels;

	/**
	The size of the frame in twips.
	*/
	TSize iFrameSizeInTwips;

	/**
	The number of bits per pixel for the frame.
	*/
	TInt iBitsPerPixel;

	/**
	The delay in microseconds before displaying the next frame.
	*/
	TTimeIntervalMicroSeconds iDelay;

	/**
	Frame information flags. A combination of the values contained in the TFrameInfoFlags enum.
	*/
	TUint32 iFlags;

	/**
	The overall size of the image. A frame can occupy a rectangle within the overall image.
	In this case, the frame size is less than the overall image size, but iOverallSizeInPixels
	remains the same.
	*/
	TSize iOverallSizeInPixels;
	};

#if !defined(__WITHIN_MCI_LIBRARY)
// within the MediaClientImage library itself, TFrameInfo is the ICL version. Normally will be TFrameInfoMCL
typedef TFrameInfoMCL TFrameInfo;
#endif !defined(__WITHIN_MCI_LIBRARY)

#endif // __MDAFRAMEINFO_H__
