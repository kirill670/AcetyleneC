//	SchSend_Panic.h
//
//	Copyright (c) 1999-2004 Symbian Software Ltd.  All rights reserved. 
//

#ifndef __SCHSEND_PANIC_H__
#define __SCHSEND_PANIC_H__

/**
@internalAll
@released
*/
enum TScheduleSendPanic
	{
	EMessageSelectionEmpty,
	EMessagesNotSameTime,
	EMessagesNotSameMtm,
	EMessagesNotSameOffPeak,
	EMessageNotScheduled,
	EScheduleNotCreated,
	ECannotScheduleInPast,
	EAttemptIntervalArrayEmpty,
	ETaskIdMsvIdMismatch,
	EInvalidAttemptInterval,
	EInvalidValidityPeriod,
	EInvalidMaxAttempts,
	EInvalidHour,
	EInvalidMinute,
	EInvalidSecond,
	EStartTimeTooEarly,
	EProgrammingBug,
	EVariableIntervalsNotFound,
	ELongIntervalOutOfRange,
	EShortIntervalOutOfRange,
	EVariableIntervalOutOfRange,
	EMaxRetriesMustBePositive,
	ERetryIntervalMustByPositive,
	EOffPeakTimesEmpty,
	EServerEntryNotSetToCorrectEntry,
	ELatencyOutOfRange,
	ESysAgentConditionOutOfSync,
	ESysAgentConditionTypeNotSupported,
	EReportNotNull,
	EMessagesNotSamePendingConditions,
	EPendingConditionsTimeoutOutOfRange
	};

GLREF_C void gPanic(TScheduleSendPanic aPanic);

#endif
