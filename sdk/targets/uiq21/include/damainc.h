// DAMAINC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __DAMAINC_H__
#define __DAMAINC_H__

#include <e32base.h>
#include <s32stor.h>
#include <d32dbms.h>

class MDaIncrementalObserver;
class CDaActiveIncremental;

class MDaIncremental
	{
public:
	virtual ~MDaIncremental() {}
	virtual TInt Next(TInt& aRemainingSteps) = 0;
	virtual void CloseL() = 0;
	virtual void HandleLeave(TInt /*aError*/) = 0;
	virtual void HandleCancel() = 0;
	virtual void SetActiveIncremental(CDaActiveIncremental*) = 0;
	};

class MDaIncrementalObserver
	{
	public:
		virtual ~MDaIncrementalObserver() {}
		virtual void NotifyStepsExecuted(TInt aStepsExecuted)=0;
		virtual void Initialize(TInt aTotalSteps) = 0;
		virtual TBool DoExecuteLD() = 0;
		virtual void SetFinalValue(TInt aFinalValue) = 0;
		virtual TInt RemainingSteps() = 0;
		virtual void SetIncremental(MDaIncremental* aIncremental) = 0;
	};

class CDaActiveIncremental : public CActive
	{
	public:
		IMPORT_C static CDaActiveIncremental * NewL(TInt aPriority, MDaIncremental& aIncremental);
		IMPORT_C ~CDaActiveIncremental();
		IMPORT_C void Start();
	protected:
		CDaActiveIncremental(TInt aPriority, MDaIncremental& aIncremental);
		IMPORT_C virtual void RunL();
		IMPORT_C virtual void DoCancel();
	private:
		MDaIncremental& iIncremental;
	};

class CDaIncremental : public CBase, public MDaIncremental
	{
public:
	CDaIncremental()
		: iTerminationState(KErrNone)
		  {}
	IMPORT_C void SetObserver(MDaIncrementalObserver* aObserver);
	inline void SetActiveIncremental(CDaActiveIncremental* aActiveIncremental) 
		{iActiveIncremental = aActiveIncremental;}
	inline TInt TerminationState() const
		{return iTerminationState;}
	inline void Initialize(TInt aRemainingSteps)
		{iRemainingSteps = aRemainingSteps;}
	IMPORT_C virtual void HandleCancel();
	IMPORT_C virtual void HandleLeave(TInt aError);
protected:
	IMPORT_C void DoCancel();
protected:	
	MDaIncrementalObserver* iObserver;
	CDaActiveIncremental* iActiveIncremental;
	TInt iTerminationState;
	TInt iRemainingSteps;
	};

class CDaDbIncremental : public CDaIncremental
	{
public:
	CDaDbIncremental(RDbIncremental& aDbIncremental)
		:iDbIncremental(aDbIncremental) {}
	IMPORT_C virtual TInt Next(TInt& aRemainingSteps);
	IMPORT_C virtual void CloseL();
private:
	RDbIncremental& iDbIncremental;
	};

class CDaStoreReclaim : public CDaIncremental
	{
public:
	CDaStoreReclaim(RStoreReclaim& aDbIncremental)
		:iDbIncremental(aDbIncremental) {}
	IMPORT_C virtual TInt Next(TInt& aRemainingSteps);
	IMPORT_C virtual void CloseL();
private:
	RStoreReclaim& iDbIncremental;
	};
#endif
