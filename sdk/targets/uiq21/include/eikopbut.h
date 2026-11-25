// EIKOPBUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKOPBUT_H__)
#define __EIKOPBUT_H__

#if !defined(__EIKBUTB_H__)
#include <eikbutb.h>
#endif

#if !defined(__GULBORDR_H__)
#include <gulbordr.h>
#endif

class CEikOptionButton : public CEikButtonBase
	{
public:
	IMPORT_C CEikOptionButton();
	IMPORT_C ~CEikOptionButton();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ConstructL();
public: // framework
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TInt iSpare;
	};



#endif
