/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduleSend.INL
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

inline CMsvOffPeakTimes& CMsvScheduleSend::OffPeakTimes() const
/** Gets off-peak times settings.

@return Off-peak times settings */
	{
	return *iOffPeakTimes;
	}

inline CMsvScheduleSettings& CMsvScheduleSend::ScheduleSettings() const
/** Gets scheduler settings.

@return Scheduler settings */
	{
	return *iSettings;
	}

inline CMsvSendErrorActions& CMsvScheduleSend::SendErrorActions() const
/** Gets action-on-sending-error settings.

@return Action-on-sending-error settings */
	{
	return *iErrorActions;
	}

inline CMsvSysAgentActions& CMsvScheduleSend::AgentActions() const
/** Gets System Agent conditions that must be satisfied before a sending attempt.

@return System Agent conditions */
	{
	return *iAgentActions;
	}
