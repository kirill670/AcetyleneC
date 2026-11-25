// UnitTest.inl
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

//##ModelId=3A70658A01AA
inline CUnitTest::CUnitTest(const TDesC&		 aName, 
							CDataLogger&		 aDataLogger, 
							MUnitTestObserver&	 aUnitTestObserver) :
CTimer(CActive::EPriorityStandard),
iUnitTestName(aName),
iDataLogger(aDataLogger),
iUnitTestObserver(aUnitTestObserver)
	{
	CActiveScheduler::Add(this);
	}

//##ModelId=3A70658A01E6
inline const TDesC& CUnitTest::UnitTestName() const
	{
	return iUnitTestName;
	}

inline void CUnitTest::PrepareUnitTestL()
	{
	// Do nothing in the default implementation
	}

