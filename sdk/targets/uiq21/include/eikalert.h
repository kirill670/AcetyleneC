// EIKALERT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKALERT_H__)
#define __EIKALERT_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

class CEikAlert : public CEikDialog, public MEikAlertWin
	{
protected: //from CCoeControl
	void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	// Defined by the Mix-in class:
	void ConstructL();
	void RunAlert(const TDesC& aMsg1,const TDesC& aMsg2);
	void Release();
	CEikDialog* AsEikDialog();
private:
	void PreLayoutDynInitL();
private: // from CEikDialog
	void CreateButtonGroupContainerL(TInt aResourceId);
protected:
	const TDesC* iMsg1;
	const TDesC* iMsg2;
private:
	TInt iSpare;
	};

IMPORT_C void Dummy1();
IMPORT_C void Dummy2();
IMPORT_C void Dummy3();
IMPORT_C void Dummy4();
IMPORT_C void Dummy5();
IMPORT_C void Dummy6();
IMPORT_C void Dummy7();
IMPORT_C void Dummy8();
IMPORT_C void Dummy9();
IMPORT_C void Dummy10();

#endif
