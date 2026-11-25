// QikVertOptionButtonList.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0


#if !defined(__QIKVERTOPTIONBUTTONLIST_H__)
#define __QIKVERTOPTIONBUTTONLIST_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKBUTB_H__)
#include <eikbutb.h>
#endif

#if !defined(__EIKHOPBT_H__)
#include <eikhopbt.h>
#endif
/**
 * this class provides Vertical option buttons
 * that are a group of vertically arranged radio buttons
 * associated resource: QIK_VERTOPBUT
 *
 **/
class CEikOptionButton;
class CEikLabel;

class CQikVertOptionButtonList : public CCoeControl, public MCoeControlObserver
	{
public:
	IMPORT_C CQikVertOptionButtonList(TInt aInterButtonSpacing,TBool aTextOnRight);
	IMPORT_C CQikVertOptionButtonList();
	IMPORT_C ~CQikVertOptionButtonList();
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructFromResourceL(TResourceReader &aReader);
public: // new functions
	IMPORT_C void AddOptionButtonL( TInt aId,const TDesC& aDes);
	IMPORT_C void SetButtonById(TInt aId);
	IMPORT_C TInt LabeledButtonId();
public:	// from CCoeControl
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TSize MinimumSize();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void SizeChanged();
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
public:// from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TEikButtonCoordinator iCoordinator;
	TBool iTextOnRight;
	TInt iInterButtonSpacing;
	TInt iButtonId;
	CArrayFix<CEikLabeledOptionButton*> *iOptionButtonArray;
private:
	TInt iQikSpare1;
	};

#endif
