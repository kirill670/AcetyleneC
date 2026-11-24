// FbsMessage.H
//
// Copyright (C) 2005-2006 Symbian Software Ltd. All rights reserved.
//

#ifndef __FBSMESSAGE_H__
#define __FBSMESSAGE_H__

/**
@internalComponent
*/
enum TFbsMessage
	{
	EFbsMessInit,
	EFbsMessShutdown,
	EFbsMessClose,
	EFbsMessResourceCount,
	EFbsMessNumTypefaces,
	EFbsMessTypefaceSupport,
	EFbsMessFontHeightInTwips,
	EFbsMessFontHeightInPixels,
	EFbsMessAddFontStoreFile,
	EFbsMessInstallFontStoreFile,
	EFbsMessRemoveFontStoreFile,
	EFbsMessSetPixelHeight,
	EFbsMessGetFontById,
	EFbsMessFontDuplicate,
	EFbsMessBitmapCreate,
	EFbsMessBitmapResize,
	EFbsMessBitmapDuplicate,
	EFbsMessBitmapLoad,
	EFbsMessDefaultAllocFail,
	EFbsMessDefaultMark,
	EFbsMessDefaultMarkEnd,
	EFbsMessUserAllocFail,
	EFbsMessUserMark,
	EFbsMessUserMarkEnd,
	EFbsMessHeapCheck,
	EFbsMessRasterize,
	EFbsMessFaceAttrib,
	EFbsMessHasCharacter,
	EFbsMessSetDefaultGlyphBitmapType,
	EFbsMessGetDefaultGlyphBitmapType,
	EFbsMessFontNameAlias,
	EFbsMessBitmapCompress,
	EFbsMessGetHeapSizes,
	EFbsMessGetNearestFontToDesignHeightInTwips,
	EFbsMessGetNearestFontToMaxHeightInTwips,
	EFbsMessGetNearestFontToDesignHeightInPixels,
	EFbsMessGetNearestFontToMaxHeightInPixels,
 	EFbsMessShapeText,
 	EFbsMessShapeDelete,
	EFbsMessDefaultLanguageForMetrics,
	EFbsMessSetTwipsHeight,
	EFbsMessGetTwipsHeight,
	EFbsCompress,
	EFbsMessBitmapBgCompress,
	EFbsFileStoreClose,
	EFbsSetSystemDefaultTypefaceName,
	};

// __FBSMESSAGE_H__
#endif
