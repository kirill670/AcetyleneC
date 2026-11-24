// SCHTASK.H
//
// Copyright (c) 2004 Symbian Software Ltd.  All rights reserved.
//
// Representation of a task: 
// Includes both user-defined data (iInfo+iData) and data set by system
// construction from stream & accessors are exported for task executors

#if !defined(__SCHTASK_H__)
#define __SCHTASK_H__

#if !defined(__SCHINFO_H__)
#include "SCHINFO.H"
#endif 

#include <s32file.h>

/** 
The representation of a task that is being scheduled.

Instances of this class are not accessible to clients, but are passed to the 
registered program through the program's TFileName parameter.

When tasks are due, the Task Scheduler encapsulates task information within 
CScheduled objects, and externalises them to a direct file store. The filename 
is passed to the associated registered program through its TFileName parameter.

The root stream of the direct file store contains a 32 bit value, followed 
by the external representations of one or more CScheduledTask objects. The 
32 bit value is interpreted as a TInt32 and contains the number of CScheduledTask 
objects that follow in the stream.

The registered program can create successive CScheduledTask objects from this 
stream using the static NewLC() function.
 
@see TFileName
@see RStoreReadStream 
@publishedAll
@released
*/
class CScheduledTask : public CBase
	{
public:
	IMPORT_C static CScheduledTask* NewLC(RReadStream& aStream);
	~CScheduledTask();
	IMPORT_C const TTaskInfo& Info() const;
	IMPORT_C const HBufC& Data() const;
	IMPORT_C const TTime& ValidUntil() const;
	IMPORT_C TScheduleType ScheduleType() const;
	
	// These methods only used by task scheduler server
	CScheduledTask(TTaskInfo& aInfo, HBufC* aData, TScheduleType aScheduleType);
	TBool Due() const;
	void SetDue(TBool aDue);
	void OnDue(const TTime& aValidUntil);
	void DecRepeat();
	void Remove();
	void ExternalizeL(RWriteStream& aStream) const;
	//
	TInt ScheduleId() const;
	void SetScheduleId(TInt aScheduleId);
	//
	static TInt Offset();
	//
private:
	CScheduledTask();	
	void InternalizeL(RReadStream& aStream);
private:
	TPriQueLink iPLink;
	TTaskInfo iInfo;
	HBufC* iData;
	TTime iValidUntil;
	TBool iDue;
	TInt iScheduleId;
	TScheduleType iScheduleType;
	};

#endif
