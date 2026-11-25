// EIKPWORD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__EIKPWORD_H__)
#define __EIKPWORD_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

class CSecurityBase;

class CEikSetPasswordDialog : public CEikDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(CSecurityBase& aSecurity,TPassword& aOldPassword);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	CEikSetPasswordDialog(CSecurityBase& aSecurity,TPassword& aOldPassword);
	// from CEikDialog
	TBool OkToExitL(TInt aButtonId);
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	CSecurityBase& iSecurity;
	TPassword& iOldPassword;
	};


class CEikVerifyPasswordDialog : public CEikDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(
									TBool& aPasswordCorrect,
									const CSecurityBase& aSecurity,
									TPassword& aPassword);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	CEikVerifyPasswordDialog(
									TBool& aPasswordCorrect,
									const CSecurityBase& aSecurity,
									TPassword& aPassword);
	// from CEikDialog
	TBool OkToExitL(TInt aButtonId);
	void PostLayoutDynInitL();
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	TBool& iPasswordCorrect;  // truth value is given back
	const CSecurityBase& iSecurity;
	TPassword& iPassword;
	};


#endif
