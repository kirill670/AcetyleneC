// MdaFrameInfo.h
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAFRAMEINFO_H__
#define __MDAFRAMEINFO_H__

// TFrameInfoMCL
/**
 * @publishedAll
 * @deprecated
 */
class TFrameInfoMCL
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

#if !defined(__WITHIN_MCI_LIBRARY)
// within the MediaClientImage library itself, TFrameInfo is the ICL version. Normally will be TFrameInfoMCL
typedef TFrameInfoMCL TFrameInfo;
#endif !defined(__WITHIN_MCI_LIBRARY)

#endif // __MDAFRAMEINFO_H__