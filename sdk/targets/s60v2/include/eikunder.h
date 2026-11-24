// EIKUNDER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKUNDER_H__)
#define __EIKUNDER_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class RThread;

//should not be available to 3rd parties but is being used by series 60 apps - should we deprecate to 3rd parties?
class MEikUndertakerObserver
/**
@publishedAll 
@released 
*/
	{
public:
	virtual void HandleThreadExitL(RThread& aThread)=0;
	};


//should not be available to 3rd parties but is being used by series 60 apps - should we deprecate to 3rd parties?
class CEikUndertaker : public CActive
/**
@publishedAll 
@released 
*/
	{
public:
	IMPORT_C static CEikUndertaker* NewL(MEikUndertakerObserver& aObserver);
	IMPORT_C ~CEikUndertaker();
private:
	CEikUndertaker(MEikUndertakerObserver& aObserver);
	void ConstructL();
	void Request();
private: // from CActive
	virtual void DoCancel();
	virtual void RunL();
private:
	MEikUndertakerObserver& iObserver;
	RUndertaker iUndertaker;
	TInt iThreadHandle;
	};

#endif
