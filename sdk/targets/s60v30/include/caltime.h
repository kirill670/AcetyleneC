// caltime.h
//
// Copyright (c) Symbian Software Ltd 2005. All rights reserved.
//

#ifndef __CALTIME_H__
#define __CALTIME_H__

#include <e32base.h>

/** Represents a date/time, as used in the Calendar API.

This stores a single TTime, which may be set or retrieved in either UTC or system local time.

There are references to null time throughout the Interim API - this means Time::NullTTime().

@publishedAll
@released
*/
NONSHARABLE_CLASS(TCalTime)
	{
public:
	IMPORT_C TCalTime();
	
	IMPORT_C void SetTimeUtcL(const TTime& aUtcTime);
	IMPORT_C void SetTimeLocalL(const TTime& aLocalTime);
	IMPORT_C TTime TimeUtcL() const;
	IMPORT_C TTime TimeLocalL() const;
	
	IMPORT_C static TTime MaxTime();
	IMPORT_C static TTime MinTime();
	
private:
	TTime	iTimeUtc;
	TInt32  iReserved;
	};
	
#endif // __CALTIME_H__
