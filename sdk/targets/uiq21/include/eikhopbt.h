// EIKHOPBT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKHOPBT_H__)
#define __EIKHOPBT_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKBUTB_H__)
#include <eikbutb.h>
#endif

class CEikOptionButton;
class CEikLabel;

class CEikLabeledOptionButton : public CEikButtonBase 
	{
public:
	IMPORT_C CEikLabeledOptionButton();
	IMPORT_C CEikLabeledOptionButton(TInt aId,TBool aTextOnRight);
	IMPORT_C ~CEikLabeledOptionButton();
	IMPORT_C void ConstructL(const CCoeControl& aContainer,TEikButtonCoordinator& aCoordinator,const TDesC& aText);
	IMPORT_C const TInt Id();
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // framework
	IMPORT_C void SizeChanged();
	IMPORT_C TSize MinimumSize();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void StateChanged();
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TInt iId;
	CEikOptionButton* iButton;
	CEikLabel* iLabel;
	TBool iTextOnRight;
	};
			 
class CEikHorOptionButtonList : public CCoeControl ,public MCoeControlObserver
	{
public:
	IMPORT_C CEikHorOptionButtonList(TInt aInterButtonSpacing,TBool aTextOnRight);
	IMPORT_C CEikHorOptionButtonList();
	IMPORT_C ~CEikHorOptionButtonList();
	IMPORT_C void ConstructL(); 
	IMPORT_C void ConstructFromResourceL(TResourceReader &aReader);
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
public:// from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
public:// framework
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TSize MinimumSize();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void SizeChanged();
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
public: // new functions
	IMPORT_C void AddOptionButtonL( TInt aId,const TDesC& aDes);
	IMPORT_C void SetButtonById(TInt aId);
	IMPORT_C TInt LabeledButtonId();
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
	};

#endif
