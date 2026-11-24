// calalarm.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CALALARM_H__
#define __CALALARM_H__

#include <e32base.h>
#ifdef SYMBIAN_FLEXIBLE_ALARM 
#include "calcontent.h"
#endif //SYMBIAN_FLEXIBLE_ALARM 

NONSHARABLE_CLASS(CCalAlarm) : public CBase
/** Class representing an alarm. contains associated data extensions

This can be assigned to a calendar entry.

@publishedAll
@released
*/
	{
 public:

	IMPORT_C static CCalAlarm* NewL();
	IMPORT_C ~CCalAlarm();
	IMPORT_C void SetTimeOffset(TTimeIntervalMinutes aOffset);
	IMPORT_C TTimeIntervalMinutes TimeOffset() const;
	IMPORT_C void SetAlarmSoundNameL(const TDesC& aAlarmSoundName);
	IMPORT_C const TDesC& AlarmSoundNameL() const;
#ifdef SYMBIAN_FLEXIBLE_ALARM 
	IMPORT_C void SetAlarmAction(CCalContent* aAlarmAction);
	IMPORT_C CCalContent* AlarmAction() const;
#endif	// SYMBIAN_FLEXIBLE_ALARM 
private:
	CCalAlarm();

private:
	TTimeIntervalMinutes iOffset;
	HBufC* iAlarmName;
#ifdef SYMBIAN_FLEXIBLE_ALARM 
	// the associated data for rich alarm action
	CCalContent* iAlarmAction;
#endif	// SYMBIAN_FLEXIBLE_ALARM 
	};


#endif // __CALALARM_H__
 
