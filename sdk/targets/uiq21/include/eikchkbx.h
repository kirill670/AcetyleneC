// EIKCHKBX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCHKBX_H__)
#define __EIKCHKBX_H__

#if !defined(__EIKBUTB_H__)
#include <eikbutb.h>
#endif

class CEikCheckBox : public CEikButtonBase
	{
public:
	IMPORT_C ~CEikCheckBox();
	IMPORT_C CEikCheckBox();
public: // framework
	IMPORT_C TSize MinimumSize();
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	void DrawTick() const;
	TInt iSpare;
	};



#endif
