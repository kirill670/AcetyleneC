// EIKGRID.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKGRID_H__)
#define __EIKGRID_H__

#if !defined(__EIKBCTRL_H_)
#include <eikbctrl.h>
#endif
#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

class TCellRef;
class TRangeRef;
class CEikScrollBarFrame;
class CGridImg;
class CGridLay;

class CEikGrid : public CEikBorderedControl, public MEikScrollBarObserver
	{
public:
	IMPORT_C virtual ~CEikGrid();
	IMPORT_C static CEikGrid* NewL(CCoeControl* aControl,CGridLay *aGridLay,CGridImg *aGridImg);
	IMPORT_C CGridLay* GridLay() const;
	IMPORT_C CGridImg* GridImg() const;
	IMPORT_C CEikScrollBarFrame* SBFrame() const;

	IMPORT_C void DrawCellL(const TCellRef& aCell) const;
	IMPORT_C void DrawRangeL(const TRangeRef& aRange) const;
	IMPORT_C void DrawSelectedL() const;
	IMPORT_C TCellRef CursorPos() const;
	IMPORT_C void SetCursorPosL(const TCellRef& aCursorPos) const;
	IMPORT_C TCellRef AnchorPos() const;
	IMPORT_C void SetAnchorPosL(const TCellRef& aAnchorPos) const;
	IMPORT_C virtual void CheckScrollBarPosL() const;
	IMPORT_C virtual void UpdateGridAfterZoomL();
	IMPORT_C TPoint ExposeCellL(const TCellRef& aCell) const;
	IMPORT_C void ExposeCellAndScrollL(const TCellRef& aCell) const;
public:	// from CCoeControl
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
protected:
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual TInt CountComponentControls() const;
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
protected:	// from MEikScrollBarObserver
	IMPORT_C virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
protected:
	IMPORT_C void ConstructL(CCoeControl* aControl);
	IMPORT_C CEikGrid(CGridLay *aGridLay,CGridImg *aGridImg);
	IMPORT_C TCellRef CellToExpose() const;
protected:  // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:	// from CCoeControl
	IMPORT_C virtual void Reserved_2();
protected:
	CGridLay* iGridLay;
	CGridImg* iGridImg;
	CEikScrollBarFrame* iSBFrame;
private:
	TInt iSpare;
	};


#endif
