// BACNTF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by BLB, October 1996
#if !defined(__BACNTF_H__)
#define __BACNTF_H__

#include <e32base.h>

/**
 *
 * Environment change notifier.
 *
 * This is an active object and can be used to handle environment change
 * events.
 *
 * @since 5.0
 * @lib " bafl.lib "
 */
class CEnvironmentChangeNotifier : public CActive
	{
public:
	IMPORT_C static CEnvironmentChangeNotifier* NewL(TInt aPriority,const TCallBack& aCallBack);
	IMPORT_C ~CEnvironmentChangeNotifier();
	IMPORT_C void Start();
	IMPORT_C TInt Set(const TCallBack& aCallBack);
	inline TInt Change() const;
private:
	inline CEnvironmentChangeNotifier(TInt aPriority);
	void RunL();
	void DoCancel();
private:
	TInt iChange;
	TCallBack iCallBack;
	RChangeNotifier iChangeNotifier;
	};


/**
 *
 * Returns the last set of change events.
 *
 * If the last outstanding request completed normally, the function
 * returns a bit pattern where each bit value corresponds to one of the
 * enumerators defined by <code>TChanges</code>. A set bit indicates that
 * the corresponding change event occurred.For example, if the bit value
 * <code>TChanges::EChangesMidnightCrossover</code> is set, then the
 * system time has passed midnight.
 *
 * @returns   " TInt "
 *            A set of bits consisting of one or more of the values
 *            defined by <code>TChanges</code>, or
 *            <code>KErrCancel</code> if the last outstanding
 *            request was cancelled.
 */
inline TInt CEnvironmentChangeNotifier::Change() const
	{return iChange;}

#endif


