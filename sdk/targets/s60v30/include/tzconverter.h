// tzconverter.h
//
// Copyright (c) 1997-2005 Symbian Software Ltd. All rights reserved.
//
#ifndef __TZ_CONVERTER_H__
#define __TZ_CONVERTER_H__

#include <e32base.h>
#include <tzdefines.h>

class CTzChangeNotifier;
class CVTzActualisedRules;
class CTzRuleHolder;

/**
Converts between time expressed in UTC and local time. 

@publishedAll
@released

@see RTz
@since 9.1
*/
// @lib "timezoneclient.lib"
class CTzConverter : public CBase
	{
public:

	IMPORT_C static CTzConverter* NewL(RTz& aTzServer);
	IMPORT_C ~CTzConverter();
	IMPORT_C TInt ConvertToLocalTime(TTime& aTime);
	IMPORT_C TInt ConvertToLocalTime(TTime& aTime, const CTzId& aZone);
	IMPORT_C TInt ConvertToUniversalTime(TTime& aTime);
	IMPORT_C TInt ConvertToUniversalTime(TTime& aTime, const CTzId& aZone);
	IMPORT_C TUint16 CurrentTzId();

	void NotifyTimeZoneChangeL(RTz::TTzChanges aChange);
	const RTz& Server() const; 
private:
	CTzConverter(RTz& aTzServer);
	void ConstructL();
	void doConvertL(TTime& aTime, TTzTimeReference aTimerRef);

private:
	RTz& iTzServer;
	CTzRuleHolder* iRules;
	CTzChangeNotifier* iTzChangeNotifier;
	};

#endif
