// DAMDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// typedef for the data app
//
#ifndef __DAMDEF_H__
#define __DAMDEF_H__

#if !defined (__E32STD_H__)
#include <e32std.h>
#endif

#ifdef _UNICODE
#define KUidDataApp KUidDataApp16
#else
#define KUidDataApp KUidDataApp8
#endif

const TUid KUidDataApp8={268435590};
const TUid KUidDataApp16={0x10003A61};
const TUid KUidDataHeadStream={ 268435758};	

const TUint KErrDbsConnect=0;
const TUint KErrDbOpen=1;
const TUint KErrPrepare=3;
const TUint KErrEvaluate=4;
const TUint KErrInvalidView=5;
const TUint KErrYesNoArray=6;
const TUint KMaxFindString=250;
const TUint KAverageColumns=10;
const TUint KMaxSavedRecords=1;
const TUint KMaxSortColumns=3;
const TUint KMaxLinesDE=4;
const TInt KDaDefaultMinKeyLength = 10;

typedef TBuf<KMaxFindString> TFindString;
typedef TFileName TDatabaseName;

// defined at file scope because they are short
_LIT (KDaModelColAFormat,"ColA%d");
_LIT (KDaModelColBFormat,"ColB%d");

#endif
