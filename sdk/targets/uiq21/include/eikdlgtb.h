// EIKDLGTB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDLGTB_H__)
#define __EIKDLGTB_H__

#if !defined(__EIKCTGRP_H__)
#include <eikctgrp.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

class CCoeBrushAndPenContext;

class CEikDialogToolBar : public CEikControlGroup, private MCoeControlObserver
	{
public:
	IMPORT_C ~CEikDialogToolBar();
	IMPORT_C CEikDialogToolBar();
	IMPORT_C void BaseConstructL();
	IMPORT_C CCoeControl* StateChangeControl() const;
	IMPORT_C TInt StateChangeControlId() const;
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
public: // from CEikControlGroup
	IMPORT_C void AddControlL(TEikGroupControl& aGroupControl);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from MCoeControlObserver
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	CCoeControl* iStateChangeControl;
	CCoeBrushAndPenContext* iBrushAndPenContext;
	};



#endif
