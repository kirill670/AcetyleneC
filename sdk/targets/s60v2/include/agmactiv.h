// AGMACTIV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMACTIV_H__
#define __AGMACTIV_H__

#include <e32base.h>
#include "AGMIDS.H"


#ifndef SYMBIAN_REMOVE_COREAPPS_API_V1
class MAgnActiveStep
/**
@internalComponent
@released
*/
	{
public:
	virtual TInt DoStepL() = 0;
	virtual void StepCompleted(TInt aError = KErrNone) = 0;
	};
	
#endif //SYMBIAN_REMOVE_COREAPPS_API_V1


#ifndef SYMBIAN_HIDE_COREAPPS_API_V1

class MAgnProgressCallBack;


class CAgnCategory;

class CAgnFileActive : public CActive
/**
@internalComponent
@released
*/
	{
public:
	static CAgnFileActive* NewL();
	virtual ~CAgnFileActive();
	void Start(MAgnActiveStep* aStepCallBack,MAgnProgressCallBack* aProgressCallBack);
	void SetCategoryParametersL(const CAgnCategory& aCategory,TInt aStepSize,CArrayFixSeg<TAgnEntryId>* aEntries);
	void SetCategoryNewNameL(const TDesC& aNewName);
	const CAgnCategory& Category() const;
	CArrayFixSeg<TAgnEntryId>* FilteredEntries() const;
	TInt StepSize() const;
	void ResetFilteredEntries();
	const TDesC& CategoryNewName() const;

protected:
	inline CAgnFileActive(TInt aPriority = EPriorityIdle) : CActive(aPriority){};
	virtual void RunL();
	virtual void DoCancel();
	void SetActiveAndMakeRequest();
protected:
	MAgnActiveStep*			iStepCallBack;
	MAgnProgressCallBack*	iProgressCallBack;	
private:
	CAgnCategory* iCategory;
	TInt iStepSize;
	HBufC* iCategoryNewName;
	TBool iIsCategoryStep;
	CArrayFixSeg<TAgnEntryId>* iFilteredEntries; // Not owned
	};
#endif

#endif	
