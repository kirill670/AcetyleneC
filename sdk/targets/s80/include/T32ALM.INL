// T32ALM.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by BLB, June 1995
//

// Class TAlarmInfo
inline TInt TAlarmInfo::AlarmId() const
	{
	return(iAlarmId);
	}
inline TAlarmClockRepeat TAlarmInfo::Repeat() const
	{
	return(iRepeat);
	}
inline TAlarmType TAlarmInfo::Type() const
	{
	return(iType);
	}
inline TTime TAlarmInfo::DueTime() const
	{
	return(iDueTime);
	}
inline TTime TAlarmInfo::AlarmTime() const
	{
	return(iAlarmTime);
	}
inline TAlarmMessage TAlarmInfo::Message() const
	{
	return(iMessage);
	}
inline TAlarmSoundName TAlarmInfo::Sound() const
	{
	return(iSound);
	}

// 	class RAlarmServer
inline TVersion RAlarmServer::Version() const
/** Gets the version number of the DLL.

The version number may be incremented in future releases of the alarm server. 
If extra features are added in such releases, the version number may be used 
by application programs as a basis for assessing the capabilities of the alarm 
server. Version-specific functions will be marked as such in the API documentation.

@return The version number. */
	{
	return(TVersion(KAlarmServerMajVN,KAlarmServerMinVN,KAlarmServerBldVN));
	}

