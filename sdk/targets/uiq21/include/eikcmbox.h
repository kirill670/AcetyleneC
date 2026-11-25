// EIKCMBOX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCMBOX_H__)
#define __EIKCMBOX_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif

#include <eikbutb.h>
 
class CEikEdwin;
class CCharFormatLayer;
class TResourceReader;
class CEikTextListBox;

class CEikComboBoxButton : public CEikButtonBase
	{
	public:
		CEikComboBoxButton();
	public: // from CCoeControl
		TSize MinimumSize();
	protected: // from CEikButtonBase
	    void StateChanged();
	private: // from CCoeControl
		void Draw(const TRect& aRect) const;
	};

class CEikComboBox : public CEikBorderedControl, public MCoeControlObserver
	{						
public:
	enum TArrayOwnershipType
		{
		EArrayInternalOwner	=0x00,
		EArrayExternalOwner	=0x01
		};
public: // new functions
	IMPORT_C CEikComboBox();
	IMPORT_C ~CEikComboBox();
	IMPORT_C void ConstructL(const CCoeControl& aParent,TInt aWidthInChars,TInt aTextLimit,TInt aMaxArraySize);
	IMPORT_C MDesCArray* Array() const;
	IMPORT_C void SetArrayL(TInt aResourceId,TArrayOwnershipType aOwner=EArrayInternalOwner);
	IMPORT_C void SetArray(MDesCArray* aArray,TArrayOwnershipType aOwner=EArrayInternalOwner);
	IMPORT_C void GetText(TDes& aDes) const;
	IMPORT_C void SetTextL(const TDesC* aDes);
	IMPORT_C void InsertTextIntoArrayL();
	IMPORT_C CEikEdwin* Edwin()const;
	IMPORT_C TInt MaxArraySize() const;
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
protected: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
protected: // from CCoeControl
	IMPORT_C void SetContainerWindowL(const CCoeControl& aParent);
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	void ConstructTabButtonL();
	void HandleInteractionConfirmedL();
	void CreatePopoutL();
	void DestroyPopout();
	void DoCreatePopoutL();
private:
	CEikEdwin* iEdwin;
protected:
	CEikComboBoxButton* iTabButton;
	CEikTextListBox* iPopout;
private:
	MDesCArray* iArray;
	TInt iMaxArraySize;
	TInt iComboFlags;
	};

#endif
