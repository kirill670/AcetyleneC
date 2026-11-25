// EIKRUBTL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKRUBTL_H__)
#define __EIKRUBTL_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

class CEikRubberBand : public CCoeControl
	{
public:
	enum TFlags
		{ // values share space with TEdges
		EAllowToFlip	=0x10,
		EMoveWholeBand	=0x20,
		EDrawAsCircle	=0x40,
		EMaintainAspect	=0x80
		};

public:
	IMPORT_C CEikRubberBand();
	IMPORT_C ~CEikRubberBand();
	IMPORT_C void Activate(const TPoint& aStartPos, const TRect& aRect, const TInt aFlags);
	IMPORT_C void NotifyDragPos(const TPoint& aPos);
	IMPORT_C void Deactivate();
	IMPORT_C void XorDraw() const;
	IMPORT_C void XorDrawNow() const;
	inline TRect BandRect() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void CheckDragPosIsValid(TPoint& aPointerPos);
	TRect EnclosedRect(const TPoint &aPointA,const TPoint &aPointB);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	enum
		{
		EMaintainAspectDragHoriz	=0x100,
		EMaintainAspectDragVert		=0x200
		};

private:
	TInt iRubberBandFlags;
	TPoint iAnchorPos;
	TRect iBandRect;
	};


inline TRect CEikRubberBand::BandRect() const
	{ return(iBandRect); }


class CEikRubberLine : public CCoeControl
	{
public:
	IMPORT_C CEikRubberLine();
	IMPORT_C ~CEikRubberLine();
	IMPORT_C void Activate(const TPoint& aStartPos);
	IMPORT_C void NotifyDragPos(const TPoint& aPos);
	IMPORT_C void Deactivate();
	IMPORT_C void XorDraw() const;
	IMPORT_C void XorDrawNow() const;
	inline TPoint AnchorPos() const;
	inline TPoint MovingPos() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TPoint iAnchorPos;
	TPoint iMovingPos;
	};


inline TPoint CEikRubberLine::AnchorPos() const
	{ return(iAnchorPos); }
inline TPoint CEikRubberLine::MovingPos() const
	{ return(iMovingPos); }
#endif
