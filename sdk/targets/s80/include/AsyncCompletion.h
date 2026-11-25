#if (!defined __ASYNC_COMPLETION_H__)
#define __ASYNC_COMPLETION_H__
#include <e32Base.h>

class COpTimer : public CTimer
	{
public:
	IMPORT_C static COpTimer* NewL(TCallBack aParent);
	virtual ~COpTimer();
	void RunL();
protected:
	COpTimer(TCallBack aParent);
public:
	TCallBack iParent;
	};

class CAsyncCompletion :  public CActive
	{
public:
	IMPORT_C static CAsyncCompletion* NewLC(TCallBack* aTimeoutOp = NULL);
	virtual ~CAsyncCompletion();
	IMPORT_C void Start(TTimeIntervalMicroSeconds32 = KMaxTUint);
protected:
	CAsyncCompletion(TCallBack* aTimeoutOp = NULL);
	void ConstructL();
	void DoCancel();
	void RunL();
	static TInt TimeoutCallBack(TAny* aThis);
public:
	TCallBack				iTimeoutOp;
	CActiveSchedulerWait	iScheduler;
	COpTimer*				iTimer;
	};
#endif