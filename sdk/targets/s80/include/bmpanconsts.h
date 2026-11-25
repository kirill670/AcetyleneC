// BMPANCONSTS.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//


#if !defined(__BMPANCONSTS_H__)
#define __BMPANCONSTS_H__

/**
TBitmapAnimCommand

@internalComponent
*/
enum TBitmapAnimCommand
	{
	EBitmapAnimCommandSetBackgroundFrame,
	EBitmapAnimCommandSetDataFrame,
	EBitmapAnimCommandSetFlash,
	EBitmapAnimCommandSetFrameIndex,
	EBitmapAnimCommandSetFrameInterval,
	EBitmapAnimCommandSetNumberOfCycles,
	EBitmapAnimCommandSetPlayMode,
	EBitmapAnimCommandSetPosition,
	EBitmapAnimCommandStartAnimation,
	EBitmapAnimCommandStopAnimation,	
	EBitmapAnimCommandStartAnimationAndKeepLastFrame
	};

#endif

