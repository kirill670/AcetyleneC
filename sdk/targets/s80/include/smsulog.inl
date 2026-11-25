// SMSULOG.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

/** @file SMSULOG.INL */


inline TBool CSmsEventLogger::ClientAvailable() const
/** Tests whether the Log Engine is installed.

@publishedAll
@released
@return True if there is a Log Engine, otherwise false */
	{
	return iLogWrapper->ClientAvailable();
	}


inline TInt CSmsEventLogger::GetString(TDes& aString, TInt aId) const
/** Gets a standard string from the specified resource.

@publishedAll
@released
@param aString On return, string read from resource
@param aId Resource ID
@return KErrNone, if successful; otherwise, one of the other system wide error 
codes */
	{
	return iLogWrapper->Log().GetString(aString,aId);
	}


inline CLogEvent& CSmsEventLogger::Event()
/** Gets the current log event.

@publishedAll
@released
@return Current log event */
	{
	return *iLogEvent;
	}


inline const CLogEvent& CSmsEventLogger::Event() const
/** Gets the current (const) log event.

@publishedAll
@released
@return Current log event */
	{
	return *iLogEvent;
	}



inline const TLogSmsPduData& CSmsEventLogger::SmsPDUData() const
/** Gets the current event's SMS PDU data.

@publishedAll
@released
@return Current event's SMS PDU data */
	{
	return iSmsPDUData;
	}



inline void CSmsEventLogger::GetStringL(TDes& aString, TInt aId) const
/**
@publishedAll
@released
*/
	{
	User::LeaveIfError(iLogWrapper->Log().GetString(aString,aId));
	}

