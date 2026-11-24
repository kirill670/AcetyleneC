// VCAL.INL
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

//
// CParserPropertyValueAlarm
//
inline CVersitAlarm* CParserPropertyValueAlarm::Value() const
/** Gets a pointer to the alarm property value.

@return Pointer to the alarm property value. */
	{return iValue;}

#ifdef SYMBIAN_FLEXIBLE_ALARM
//
// CParserPropertyValueExtendedAlarm
//
inline CVersitExtendedAlarm* CParserPropertyValueExtendedAlarm::Value() const
/** Gets a pointer to the extended alarm property value.

@return Pointer to the extended alarm property value. */
	{return iValue;}
#endif // SYMBIAN_FLEXIBLE_ALARM

