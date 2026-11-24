// VTZRULES.H
//
// Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
//
#ifndef __VTZRULES_H__
#define __VTZRULES_H__

#include <e32base.h>
#include <s32strm.h>
#include <tzdefines.h>
#include <tz.h>

class CVTzActualisedRules;
class TVTzActualisedRule; 

const TInt KVTzRulesGranularity = 4;


/**
Encapsulates one time zone rule.

@internalComponent
@since 9.1
@lib "timezoneclient.lib"
*/
class TTzRule
	{
public:
	IMPORT_C TTzRule(TInt16 aFromYear, TInt16 aToYear, TInt16 aOldOffset, TInt16 aNewOffset, TMonth aMonth, TTzRuleDay aDayRule, 
				TUint8 aDayOfMonth, TUint8 aDayOfWeek, TTzTimeReference aTimeReference, TUint16 aTimeOfChange);
	IMPORT_C TTzRule();
	IMPORT_C TTzRule(const TTzRule& aRule);
	IMPORT_C TTzRule(TTimeWithReference aFromYear, TTimeWithReference aToYear, TInt16 aOldOffset, TInt16 aNewOffset, TMonth aMonth, TTzRuleDay aDayRule, 
				TUint8 aDayOfMonth, TUint8 aDayOfWeek, TTzTimeReference aTimeReference, TUint16 aTimeOfChange);

	
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);		
	TBool RuleApplies(TInt aYear) const;	
	
	IMPORT_C TVTzActualisedRule Actualise(TInt aYear) const;
	
public:
	TTimeWithReference iFrom;		// first date the rule applies
	TTimeWithReference iTo;			// last date the rule applies
	TInt16		iOldLocalTimeOffset; // local time offset (in minutes) BEFORE the change (local time = UTC + DST)
	TInt16		iNewLocalTimeOffset; // local time offset (in minutes) AFTER the change
	TMonth		iMonth;
	TTzRuleDay	iDayRule;		// format in which the rule is expressed
	TUint8		iDayOfMonth;
	TUint8		iDayOfWeek;
	TTzTimeReference iTimeReference;
	TUint16		iTimeOfChange;	// number of minutes since midnight

	};

/**
Encapsulates a collection of time zone rules, and includes the period covered by the rules
and the standard time offset at the start of that period.

@internalComponent
@since 9.1
@lib "timezoneclient.lib"
*/
class CTzRules : public CBase
	{
public:
	IMPORT_C static CTzRules* NewL();
	IMPORT_C static CTzRules* NewL(TInt aStartYear, TInt aEndYear);
	IMPORT_C static CTzRules* NewL(RReadStream& aStream);
	IMPORT_C ~CTzRules();
	IMPORT_C TBool RulesApply(const TTime& aTime) const;
	IMPORT_C void AddRuleL(TTzRule aRule);
	IMPORT_C void RemoveRule(TInt aIndex);
	IMPORT_C TTzRule& operator[](TInt aIndex);
	IMPORT_C TInt Count() const;
	IMPORT_C TInt StartYear() const;
	IMPORT_C TInt EndYear() const;
	IMPORT_C void SetStartYear(TInt aYear);
	IMPORT_C void SetEndYear(TInt aYear);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C TInt InitialStdTimeOffset() const;
	IMPORT_C void SetInitialStdTimeOffset(TInt aOffset);
	IMPORT_C void ConvertToUtcL(TTime& aLocalTime) const;
	IMPORT_C void ConvertToLocalL(TTime& aUtcTime) const;
	IMPORT_C CTzRules* CloneL() const;
	IMPORT_C TBool IsEqualTo(const CTzRules& aRules) const;
	
	IMPORT_C void GetActualisedRulesL(CVTzActualisedRules& aActRules) const;
	IMPORT_C TInt ConvertTime(CVTzActualisedRules& aRules, TTime& aTime, TTzTimeReference aTimerRef) const;
	
private:
	CTzRules();
	CTzRules(TInt aStartYear, TInt aEndYear);
	TBool RulesApply(TInt aYear) const;
	void GetActualisedRulesL(CVTzActualisedRules& aActRules, TInt aYear) const;
	TInt GetOffsetL(const TTime& aTime, TTzTimeReference aTimeRef) const;
	TInt GetOffsetFromRuleL(const CVTzActualisedRules& aRules, const TTime& aTime, TTzTimeReference aTimeRef) const;
	TInt AddActualisedRulesL(CVTzActualisedRules& aActRules, TInt aYear) const;
	
private:
	TInt16 iStartYear;
	TInt16 iEndYear;
	RArray<TTzRule> iRules;
	TInt iInitialStdTimeOffset;
	};

//////////////////////////////////////////////////////////////////

/**
Encapsulates a local time change
@internalComponent
@since 9.1
@lib "timezoneclient.lib"
*/
class TVTzActualisedRule
	{
public:	
	TVTzActualisedRule(TTime aTimeOfChange, TInt aNewOffset, TTzTimeReference aTimeReference);
	IMPORT_C TVTzActualisedRule();
		
	IMPORT_C void operator=(TVTzActualisedRule aRule);
	static TInt Order(const TVTzActualisedRule& aLeft, const TVTzActualisedRule& aRight);	

public:
	TTime iTimeOfChange;
	TInt32  iNewOffset;
	TTzTimeReference iTimeReference;
	};
	
/**
Encapsulates a collection of the local time changes occurring during a range of years

@internalComponent
@since 9.1
@lib "timezoneclient.lib"
*/

class CVTzActualisedRules : public CBase
	{
public:
	static CVTzActualisedRules* NewL(TInt aStartYear, TInt aEndYear);
	~CVTzActualisedRules();
	void AddRuleL(const TVTzActualisedRule& aRule, TBool aSort=ETrue);
	TInt Count() const;
	TVTzActualisedRule& operator[](TInt aIndex) const;

	TInt StartYear() const;
	TInt EndYear() const;
	
private:
	CVTzActualisedRules(TInt aStartYear, TInt aEndYear);
	CVTzActualisedRules();
	
private:
	/** year covered by the actualised Rules */
	TInt32 iStartYear;						
	TInt32 iEndYear;						
	RArray<TVTzActualisedRule> iRules;	
	};

#endif