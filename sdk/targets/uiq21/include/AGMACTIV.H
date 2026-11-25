// AGMACTIV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMACTIV_H__
#define __AGMACTIV_H__

#include <e32base.h>


class MAgnProgressCallBack;

/**
 * Base class used in the derivation of <code>CAgnEntryModel</code>.
 *
 * It has no user accessible functions.
 *
 * @since 5.0
 * @lib ""
 */
class MAgnActiveStep
	{
public:
	virtual TInt DoStepL() = 0;
	virtual void StepCompleted(TInt aError = KErrNone) = 0;
	};

class CAgnFileActive : public CActive
	{
public:
	static CAgnFileActive* NewL();
	virtual ~CAgnFileActive();
	void Start(MAgnActiveStep* aStepCallBack,MAgnProgressCallBack* aProgressCallBack);
protected:
	inline CAgnFileActive(TInt aPriority = EPriorityIdle) : CActive(aPriority){};
	virtual void RunL();
	virtual void DoCancel();
	void SetActiveAndMakeRequest();
protected:
	MAgnActiveStep*			iStepCallBack;
	MAgnProgressCallBack*	iProgressCallBack;	
	};

#endif	
