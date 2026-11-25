// QikDrawUtils.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKDRAWUTILS_H__
#define __QIKDRAWUTILS_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <gulalign.h>
#include <coecntrl.h>
#include <gulutil.h>

class QikDrawUtils
	{
public:
	enum TArrowType
		{
		EQikLargeUp,
		EQikLargeDown,
		EQikLargeLeft,
		EQikLargeRight,
		EQikSmallUp,
		EQikSmallDown,
		EQikSmallLeft,
		EQikSmallRight
		};

	enum TOptionButtonType
		{
		EQikSet,
		EQikClear,
		EQikSetPressed,
		EQikClearPressed,
		EQikSetDimmed,
		EQikClearDimmed
		};

	IMPORT_C static void DrawArrow(CGraphicsContext& aGc, const TPoint& aPoint, QikDrawUtils::TArrowType aArrowType, TBool aDimmed = EFalse);
	IMPORT_C static void DrawArrow(CGraphicsContext& aGc, const TPoint& aPoint, QikDrawUtils::TArrowType aArrowType, TRgb aColor, TBool aDimmed = EFalse);
	IMPORT_C static TSize ArrowSize(QikDrawUtils::TArrowType aArrowType );

	IMPORT_C static void DrawOptionButton(CGraphicsContext& aGc, const TPoint& aPoint, QikDrawUtils::TOptionButtonType aType);
	IMPORT_C static void DrawOptionButton(CGraphicsContext& aGc, const TPoint& aPoint, QikDrawUtils::TOptionButtonType aType, TRgb aColor, TRgb aBackColor);
	IMPORT_C static TSize OptionButtonSize();

private:
	QikDrawUtils();
	~QikDrawUtils();

	static void DrawLargeUpArrow(CGraphicsContext& aGc, const TPoint& aPoint, TRgb aColor);
	static void DrawLargeDownArrow(CGraphicsContext& aGc, const TPoint& aPoint, TRgb aColor);
	static void DrawLargeLeftArrow(CGraphicsContext& aGc, const TPoint& aPoint, TRgb aColor);
	static void DrawLargeRightArrow(CGraphicsContext& aGc, const TPoint& aPoint, TRgb aColor);

	static void DrawSmallUpArrow(CGraphicsContext& aGc, const TPoint& aPoint, TBool aDimmed, TRgb aColor);
	static void DrawSmallDownArrow(CGraphicsContext& aGc, const TPoint& aPoint, TBool aDimmed, TRgb aColor);
	static void DrawSmallLeftArrow(CGraphicsContext& aGc, const TPoint& aPoint, TBool aDimmed, TRgb aColor);
	static void DrawSmallRightArrow(CGraphicsContext& aGc, const TPoint& aPoint, TBool aDimmed, TRgb aColor);

	static void DoDrawOptionButton(CGraphicsContext& aGc, const TPoint& aPoint, TBool aSet, TBool aPressed, TBool aDimmed, TRgb aColor, TRgb aBackColor);
	};


#endif
