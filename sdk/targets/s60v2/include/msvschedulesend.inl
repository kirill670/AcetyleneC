/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduleSend.INL
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////


/**
Gets off-peak times settings.

@return Off-peak times settings
*/

inline CMsvOffPeakTimes& CMsvScheduleSend::OffPeakTimes() const
	{
	return *iOffPeakTimes;
	}


/**
Gets scheduler settings.

@return Scheduler settings
*/

inline CMsvScheduleSettings& CMsvScheduleSend::ScheduleSettings() const
	{
	return *iSettings;
	}


/**
Gets action-on-sending-error settings.

@return Action-on-sending-error settings
*/

inline CMsvSendErrorActions& CMsvScheduleSend::SendErrorActions() const
	{
	return *iErrorActions;
	}


/**
Gets System Agent conditions that must be satisfied before a sending attempt.

@return System Agent conditions
*/

inline CMsvSysAgentActions& CMsvScheduleSend::AgentActions() const
	{
	return *iAgentActions;
	}
