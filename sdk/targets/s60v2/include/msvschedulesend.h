//	MsvScheduleSend.h
//
//	Copyright (c) 1999-2004 Symbian Software Ltd.  All rights reserved. 
//

#ifndef __MSVSCHEDULESEND_H__
#define __MSVSCHEDULESEND_H__

#ifdef _DEBUG
#undef _MSG_NO_LOGGING
#endif

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__
 
#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__


#include <e32base.h>
#include <msvstd.h>
#include <csch_cli.h>
#include <msvschedulepackage.h>
#include <msvscheduledentry.h>

class CMsvEntrySelection;
class TMsvSchedulePackage;
class TMsvSendErrorAction;
class CMsvStore;
class TMsvEntry;
class CMsvOffPeakTimes;
class CMsvScheduleSettings;
class CMsvSendErrorActions;
class CMsvSysAgentActions;
class TMsvSchedulePackage;
class TMsvEntryScheduleData;
class CMsvServerEntry;
#ifdef __MESSAGING_API_V2__
class CRepository;
#endif

const TUid KUidMsvScheduledSendingDLL	= {0x100056A0};
const TInt KMsvSchsendArrayGrowth		= 10;

#ifdef _MSG_NO_LOGGING
#define SCHSENDLOG(a)
#else
_LIT(KSchSendLogDir, "schsend");
_LIT(KSchSendLogFile,"SchSend.txt");
#define SCHSENDLOG(a) a
#endif

/** 
Provides a Server MTM's interface to the Task Scheduler for messaging 
scheduling.

Server MTM's must provide a derived class that implements GetMessageL() to 
provide a factory for MTM-specific scheduling CMsvScheduledEntry-based objects. 

@publishedAll
@released
*/
class CMsvScheduleSend : public CBase
	{
public:
	IMPORT_C ~CMsvScheduleSend();

	IMPORT_C void ScheduleL(const CMsvEntrySelection& aSelection, const TMsvSchedulePackage& aPackage);

	IMPORT_C void ReScheduleL(const CMsvEntrySelection& aSelection, const TMsvSchedulePackage& aPackage, const TMsvSendErrorAction* aErrorAction = NULL);

	IMPORT_C void CheckScheduleL(const CMsvEntrySelection& aSelection);
	IMPORT_C void DeleteScheduleL(const CMsvEntrySelection& aSelection);

	IMPORT_C void SendingCompleteL(TMsvEntry& aEntry, const TBool aChangeEntry = EFalse);
	IMPORT_C void SendingCompleteL(const CMsvEntrySelection& aSelection);

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C virtual void RestoreL(CMsvStore& aStore);
	//RestoreL restores iOffPeakTimes, iSettings and iErrorActions from streams in aStore.
	//The Server MTM may need to restore iOffPeakTimes, iSettings and/or iErrorActions
	//individually if either is specified in a resource file.
#endif	

	inline CMsvOffPeakTimes& OffPeakTimes() const;
	inline CMsvScheduleSettings& ScheduleSettings() const;
	inline CMsvSendErrorActions& SendErrorActions() const;
	inline CMsvSysAgentActions& AgentActions() const;

	IMPORT_C static void CreateScheduleL(RScheduler& aScheduler, const CMsvScheduleSettings& aSettings, const TTime& aStartTime, const TTimeIntervalMinutes& aValidityPeriod, TSchedulerItemRef& aRef);
#ifdef __CONDITIONS_SCHEDULES_VALID__
	IMPORT_C static void CreateScheduleL(RScheduler& aScheduler, const CArrayFixFlat<TTaskSchedulerCondition>& aConditions, const TTime& aTimeout, TSchedulerItemRef& aRef);
#endif
	IMPORT_C static void FindScheduleL(RScheduler& aScheduler, const TTime& aStartTime, TSchedulerItemRef& aRef);
#ifdef __CONDITIONS_SCHEDULES_VALID__
	IMPORT_C static void FindScheduleL(RScheduler& aScheduler, const CArrayFixFlat<TTaskSchedulerCondition>& aConditions, const TTime& aTimeout, TSchedulerItemRef& aRef);
#endif
	IMPORT_C static void RoundUpToMinute(TTime& aTime);
	IMPORT_C static void ScheduleEntryL(RScheduler& aScheduler, const TSchedulerItemRef& aRef, const TMsvSchedulePackage& aPackage, TTaskInfo& aInfo);
	IMPORT_C static void UpdateEntryAfterSchedule(const TSchedulerItemRef& aRef, const TTaskInfo& aInfo, const TTime& aTime, TInt aFinalState, TMsvEntry& aEntry, TMsvEntryScheduleData& aData);
	IMPORT_C static void ConnectAndRegisterL(RScheduler& aScheduler, const CMsvScheduleSettings& aSettings);

#ifdef __MESSAGING_API_V2__	
	IMPORT_C void LoadScheduleSettingsL(CRepository& aRepository);
#endif	

protected:

	IMPORT_C CMsvScheduleSend(CMsvServerEntry& aServerEntry);
	IMPORT_C virtual void ConstructL();

/**
Gets the schedule data and recipients of a message.

Recipient information is MTM-specific, so the server MTM must provide a 
derived class that implements CMsvScheduledEntry, and return objects of 
that type from this function.

@param	aId 
The message ID.

@return 
The message's schedule data.
*/
	virtual CMsvScheduledEntry* GetMessageL(const TMsvId aId) const = 0;

private:

	enum
		{
		EDefaultTaskPriority	= 1, //used when scheduling a task in the task scheduler
		EDefaultTaskRepeat		= 0	 //used when scheduling a task in the task scheduler
		};
	
	void SendingCompleteL(CMsvScheduledEntry& aScheduledEntry, const TBool aChangeEntry);

	TBool GetNextRetry(CMsvScheduledEntry& aMessage, const TMsvSendErrorAction& aErrorAction, TTimeIntervalSeconds& aInterval) const;

	void DoScheduleL(CMsvScheduledEntries& aSchEntries, const TInt aFinalState, const TTime& aTime, TBool aPendingConditions);
	void DoReScheduleL(CMsvScheduledEntries& aSchEntries);
	
	void GetMessagesL(const CMsvEntrySelection& aSelection);

	void ConnectAndRegisterL();

	void ScheduleEntryL(CMsvScheduledEntry& aMessage, const TInt aFinalState, const TTime& aStartTime, const TSchedulerItemRef& aRef, TBool aPendingConditions);

	void GetOffPeakL(TTime aFromTime, TTime& aStartTime, TTimeIntervalMinutes& aValidityPeriod) const;
	
	void DeleteScheduleForEntryL(CMsvScheduledEntry& aMessage);
	void ResetScheduleInfoForEntryL(CMsvScheduledEntry& aMessage, const TBool aChangeEntry);
#ifdef __CONDITIONS_SCHEDULES_VALID__
	void SortByDateAndPendingConditionsL(CMsvScheduledEntries& aScheduledEntries);
	void CreateScheduleL(const TTime& aStartTime, const TTimeIntervalMinutes& aValidityPeriod, const CArrayFixFlat<TTaskSchedulerCondition>& aSchConditions, TBool aPendingConditions, TSchedulerItemRef& aRef);
	void FindScheduleL(const TTime& aTime, const CArrayFixFlat<TTaskSchedulerCondition>& aSchConditions, TBool aPendingConditions, TSchedulerItemRef& aRef);

	void PopulateScheduleConditionsL(CArrayFixFlat<TTaskSchedulerCondition>& aSchConditions);
#else
	void SortByDateL(CMsvScheduledEntries& aScheduledEntries);
	void CreateScheduleL(const TTime& aStartTime, const TTimeIntervalMinutes& aValidityPeriod, TSchedulerItemRef& aRef);
	void FindScheduleL(const TTime& aTime, TSchedulerItemRef& aRef);
#endif
	TBool SetMessageStartTime(CMsvScheduledEntry& aMessage, const TTime& aFromTime, const TMsvSendErrorAction* aErrorAction = NULL);

	TBool TaskAndMessageMatchL(const CMsvScheduledEntry& aMessage);
	TMsvId GetMessageIdForTaskL(TInt aTaskId);
#ifndef _MSG_NO_LOGGING
	void FLog(TRefByValue<const TDesC> aFormat, ...);
	void FLog(TRefByValue<const TDesC8> aFormat, ...);
#endif

protected:

	/** The Server MTM specific scheduled message sending settings. */
	CMsvScheduleSettings*	iSettings;
	/** The Server MTM specific off peak time periods. */
	CMsvOffPeakTimes*		iOffPeakTimes;
	/** The Server MTM specific actions to take when particular errors occur during 
	message sending. */
	CMsvSendErrorActions*	iErrorActions;
	/** The System Agent conditions that must be satisfied before a sending attempt. */
	CMsvSysAgentActions*	iAgentActions;

	/** Indicates if this has been registered with the Task Scheduler. 
	
	Initially set to EFalse. */
	TBool					iRegistered;	
	/** Provides an interface to the Task Scheduler. */
	RScheduler				iScheduler;	
	/** The CMsvServerEntry of the server MTM. */
	CMsvServerEntry&		iServerEntry;
	/** Scheduling options. */
	TMsvSchedulePackage		iPackage;

	/** Array of message schedule data. */
	CMsvScheduledEntries*	iSchEntries;

	/** Array of schedule entry data. */
	CArrayFixFlat<TScheduleEntryInfo>* iSchEntryInfo;
	/** Array of schedule task data. */
	CArrayFixFlat<TTaskInfo>* iSchTaskInfo;
	};

#include <msvschedulesend.inl>

#endif
