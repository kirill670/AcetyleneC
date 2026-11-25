// Transition.inl
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

inline CUnitTestContext::CUnitTestContext(CDataLogger&			aDataLogger, 
										  MStateAccessor&		aAccessor,
										  MTransitionObserver&	aObserver)
: CBase(), iDataLogger(aDataLogger), iObserver(aObserver), iStateAccessor(aAccessor)
	{
	// Do nothing here
	}

inline CDataLogger& CUnitTestContext::DataLogger() const
	{
	return iDataLogger;
	}

inline MTransitionObserver& CUnitTestContext::TransitionObserver() const
	{
	return iObserver;
	}

inline MStateAccessor& CUnitTestContext::StateAccessor() const
	{
	return iStateAccessor;
	}

inline TTransitionValidator::TTransitionValidator(CUnitTestContext& aUTContext)
: iUTContext(aUTContext)
	{
	// Do nothing here
	}

inline TTransitionValidator::~TTransitionValidator()
	{
	// Do nothing here
	}

inline TBool TTransitionValidator::ValidatePreConditions()
	{
	return ETrue;
	}

inline TBool TTransitionValidator::ValidatePostConditions(TTestBedAsyncState /*aAsyncState*/)
	{
	return ETrue;
	}

inline TTransitionInfo::TTransitionInfo(const TDesC& aTransitionId, 
										CDataLogger& aDataLogger)
: iTransitionId(aTransitionId),	iIteration(0),	iDataLogger(aDataLogger)
	{
	// Do nothing here
	}

