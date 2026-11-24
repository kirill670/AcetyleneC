// GULALIGN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULALIGN_H__)
#define __GULALIGN_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

/** Horizontal layout settings for graphic objects. 

@publishedAll
@released */
enum TGulHAlignment
	{
	/** Object is left-aligned. */
	EHLeft=CGraphicsContext::ELeft,
	/** Object is centred horizontally. */
	EHCenter=CGraphicsContext::ECenter,
	/** Object is right-aligned. */
	EHRight=CGraphicsContext::ERight
	};

/** Vertical layout settings for graphic objects. 

@publishedAll
@released */
enum TGulVAlignment
	{
	/** Object is aligned with the top. */
	EVTop=0x00,
	/** Object is centred vertically. */
	EVCenter=0x10,
	/** Object is aligned with the bottom. */
	EVBottom=0x20
	};

/** Alignment settings for the layout of graphic objects. 

@publishedAll
@released */
enum TGulAlignmentValue
	{
	/** Object is left and top aligned. */
	EHLeftVTop=EHLeft|EVTop,
	/** Object is left aligned and centred vertically. */
	EHLeftVCenter=EHLeft|EVCenter,
	/** Object is left aligned and at the bottom. */
	EHLeftVBottom=EHLeft|EVBottom,
	/** Object is centre aligned horizontally and at the top. */
	EHCenterVTop=EHCenter|EVTop,
	/** Object is centred horizontally and vertically. */
	EHCenterVCenter=EHCenter|EVCenter,
	/** Object is centred horizontally and at the bottom. */
	EHCenterVBottom=EHCenter|EVBottom,
	/** Object is right and top aligned. */
	EHRightVTop=EHRight|EVTop,
	/** Object is right aligned and centred vertically. */
	EHRightVCenter=EHRight|EVCenter,
	/** Object is right aligned and at the bottom. */
	EHRightVBottom=EHRight|EVBottom
	};


class TGulAlignment
/** Provides a convenient way to describe horizontal and vertical layouts of rectangular 
objects and to enquire how they occupy an area given their alignment. 

@publishedAll 
@released */
	{
private:
	enum {EHMask=0x03, EVMask=0x30};
public:
	inline TGulAlignment();
	inline TGulAlignment(TGulAlignmentValue aValue);
	inline operator TGulAlignmentValue() const;
	inline TGulVAlignment VAlignment() const;
	inline TGulHAlignment HAlignment() const;

	// Returns the horizontal text alignment. 
	inline CGraphicsContext::TTextAlign TextAlign() const;

	IMPORT_C void SetVAlignment(TGulVAlignment aVAlign);
	IMPORT_C void SetHAlignment(TGulHAlignment aHAlign);
	IMPORT_C TPoint InnerTopLeft(const TRect& aOuter,const TSize& aInnerSize) const;
	IMPORT_C TRect InnerRect(const TRect& aOuter,const TSize& aInnerSize) const;
private:
	TGulAlignmentValue iValue;
	};

inline TGulAlignment::TGulAlignment()
/** Default constructor. */
	{};
inline TGulAlignment::TGulAlignment(TGulAlignmentValue aValue)
/** Constructor initialising the object with an alignment value.
	
@param aValue The alignment value. */
	{iValue=aValue;}
inline TGulAlignment::operator TGulAlignmentValue() const
/** Gets the object's alignment value (TGulAlignmentValue). */
	{return(iValue);}
inline TGulVAlignment TGulAlignment::VAlignment() const
/** Gets the vertical alignment. 
	
@return Vertical alignment. */
	{return((TGulVAlignment)(iValue&EVMask));}
inline TGulHAlignment TGulAlignment::HAlignment() const
/** Gets the horizontal alignment. 
	
@return Horizontal alignment. */
	{return((TGulHAlignment)(iValue&EHMask));}
inline CGraphicsContext::TTextAlign TGulAlignment::TextAlign() const
/** Gets the horizontal text alignment.
	
@return The horizontal text alignment. */
	{return((CGraphicsContext::TTextAlign)(HAlignment()));}

#endif
