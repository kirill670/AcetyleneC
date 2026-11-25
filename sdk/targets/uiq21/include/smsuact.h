// SMSUACT.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __SMSUACT_H__
#define __SMSUACT_H__

#include <e32base.h>

class CSmsuTimeout;

class CSmsuActiveBase : public CActive
	{
	public:

		IMPORT_C ~CSmsuActiveBase();
		//
	protected:

		IMPORT_C CSmsuActiveBase(TInt aPriority);
		IMPORT_C virtual void Complete(TInt aStatus);
		IMPORT_C void CompleteMyself(TInt aStatus, TBool aSetActive = ETrue);
		IMPORT_C void TimedSetActive(const TTimeIntervalMicroSeconds32& aTimeIntervalMicroSeconds32);
		IMPORT_C void ConstructTimeoutL();
		IMPORT_C void Queue(TRequestStatus& aStatus);
		IMPORT_C TInt RunError(TInt aError); ///< Calls complete

        virtual void DoRunL()=0;
		inline virtual void DoComplete(TInt&) {};

        IMPORT_C void RunL();
    
    protected:

		CSmsuTimeout* iSmsuTimeout;
		TRequestStatus* iReport;
	};

#endif 
