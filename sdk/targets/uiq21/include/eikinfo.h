// EIKINFO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKINFO_H__)
#define __EIKINFO_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

class CEikInfoDialog : public CEikDialog, public MEikInfoDialog
	{
public:
	enum TExitKeys
		{
		EAllowEnter,
		EIgnoreEnter
		};
public:
	CEikInfoDialog(const TDesC& aTitle,const TDesC& aMsg,TExitKeys aExitKeys=EAllowEnter);
	CEikInfoDialog(TExitKeys aExitKeys=EAllowEnter);
	static TBool RunDlgLD(const TDesC& aTitle,const TDesC& aMsg,TExitKeys aExitKeys);
protected: //from CCoeControl
	void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from MEikInfoDialog
	TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg);
private:
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
private: // from CEikDialog
	void CreateButtonGroupContainerL(TInt aResourceId);
private:
	const TDesC* iTitle;
	const TDesC* iMessage;
	const TInt iFlags;
	};

#endif
