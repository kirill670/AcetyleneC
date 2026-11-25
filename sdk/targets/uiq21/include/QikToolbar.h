// QIKTOOLBAR.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKTOOLBAR_H__
#define __QIKTOOLBAR_H__

#include <eikbctrl.h>
#include <coeccntx.h>
#include <eikbtgrp.h>

class MEikCommandObserver;
class TQikToolbarControl;

class CQikToolbar : public CEikBorderedControl, public MCoeControlObserver, public MEikButtonGroup, public MCoeControlContext
	{
public:
	IMPORT_C static CQikToolbar* NewL(TInt aResourceId, MEikCommandObserver* aCommandObserver);
	IMPORT_C ~CQikToolbar();
	IMPORT_C TInt Height() const;
protected:
	CQikToolbar();
	void ConstructL(TInt aResourceId, MEikCommandObserver* aCommandObserver);
	void ConstructFromResourceL(TResourceReader& aReader);
	void LayoutControls() const;
	void AddControlL(const TQikToolbarControl& aControl);
	TBool FindAdjacentControl(TInt aAlignment, TInt aCurrentIndex) const;
	TInt ControlId(CCoeControl* aControl) const;
	CCoeControl* ControlById(TInt aCommandId) const;
protected: // from CCoeControlContext	
	void PrepareContext(CWindowGc& aGc) const;
protected: // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void SizeChanged();
	void HandleResourceChange(TInt aType);
protected: // from MCoeControlObserver
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private: // from MEikButtonGroup
	void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void SetCommandL(TInt aPosition,TInt aResourceId);
	void SetCommandSetL(TInt aResourceId);
	void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void AddCommandToStackL(TInt aPosition,TInt aResourceId);
	void AddCommandSetToStackL(TInt aResourceId);
	void SetDefaultCommand(TInt aCommandId);
	TSize CalcMinimumSizeL(TInt aResourceId);
	void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
	TInt CommandPos(TInt aCommandId) const;
	void DimCommand(TInt aCommandId,TBool aDimmed);
	TBool IsCommandDimmed(TInt aCommandId) const;
	void MakeCommandVisible(TInt aCommandId,TBool aVisible);
	TBool IsCommandVisible(TInt aCommandId) const;
	CCoeControl* AsControl();
	const CCoeControl* AsControl() const;
	void SetBoundingRect(const TRect& aBoundingRect);
	void ReduceRect(TRect& aBoundingRect) const;
	CCoeControl* GroupControlById(TInt aCommandId) const;
	CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
	TInt CommandId(TInt aCommandPos) const;
	TInt ButtonCount() const;
	TUint ButtonGroupFlags() const;
private:
	CArrayFix<TQikToolbarControl>* iControlArray;
	MEikCommandObserver* iCommandObserver;
	TInt iHeight;
	TInt iHorizontalMargin;
	TInt iTopMargin;
	TInt iResourceId;
	TInt iFirstRightAlignedControl;
	};


class TQikToolbarControl
	{
public:
	TQikToolbarControl();
	TQikToolbarControl(CCoeControl* aControl);
	void ConstructFromResourceL(TResourceReader& aReader);
public:
	CCoeControl* iControl;
	TInt iId;
	TInt iWidth;
	TInt iAlignment;
	TInt iSpacing;
	TInt iYpos;
	};

#endif
