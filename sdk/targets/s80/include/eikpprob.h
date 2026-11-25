// EIKPPROB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKPPROB_H__)
#define __EIKPPROB_H__

class CPrintSetup;

class MPrintPreviewDialogObserver
	{
public:
	virtual TBool PageSetupChangedL(CPrintSetup* aPrintSetup, TInt& aNumPagesInDoc)=0;	//return true if cancelled
	virtual TBool RunPrintRangeDialogL(CPrintSetup* aPrintSetup, TInt& aNumPagesInDoc)=0; //return true if cancelled
	};

#endif
