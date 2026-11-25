// AGMBASIC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMBASIC_H__
#define __AGMBASIC_H__

#include "agmutil.h"
#include "agmrptd.h"
#include "agmdate.h"
#include "agmids.h"
#include "agmpanic.h"
#include "agmexcpt.h"

// ------------------------------------- Local clases ------------------------------------
class CAgnBasicEntry;
class TAgnBasicAppt;
class TAgnBasicTodo;
class TAgnBasicEvent;
class TAgnBasicAnniv;


class TAgnAlarmPreTime
	{
public:
	void SetAlarm(TTimeIntervalDays aDaysWarning,TTimeIntervalMinutes aTime,const TAgnDateTime& aAlarmOrigin);
	TAgnTime AlarmTime(const TAgnDateTime& aAlarmOrigin) const;
	TAgnDateTime AlarmInstanceDateTime(const TAgnDateTime& aAlarmOrigin) const;
	TTimeIntervalDays AlarmDaysWarning(const TAgnDateTime& aAlarmOrigin) const;
	inline TBool operator==(const TAgnAlarmPreTime& aOther) const;
	inline TBool operator!=(const TAgnAlarmPreTime& aOther) const;
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDurationMinutes iAlarmPreTime;
	};


/**
 * Abstract base class for the entry classes <code>CAgnAppt</code>,
 * <code>CAgnTodo</code>, <code>CAgnEvent</code> and
 * <code>CAgnAnniv</code>.
 *
 * It provides an interface to alarm and repeat information (for
 * repeating entries) and to entry attributes e.g. whether the entry is
 * tentative and whether it is crossed out.Repeat exceptions are dates
 * which would normally be included in an entrys repeat dates, but are
 * excluded. For instance if an entry is to repeat on the 4th of every
 * month but not on the 4th January, then the 4th January is an
 * exception. A repeat can have more than one exception and all
 * exceptions are stored in an exception list, which is part of the
 * entrys repeat details.Entries have a last changed date/time, which is
 * used for synchronisation, and is updated each time the entry is
 * changed.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnBasicEntry : public CBase
//
// Contains the basic details for an entry
//
	{
public:
	enum TAgnStatus 
		{
		EAccepted, 
		ENeedsAction, 
		ESent, 
		ETentative, 
		EConfirmed, 
		EDeclined,
		ECompleted, 
		EDelegated
		};

public:
	friend class TAgnSortInstance;
	virtual ~CAgnBasicEntry();
 
//	enum TSynchronisationStatus {EOpen, EPrivate, ERestricted};

	inline TChar EntrySymbol() const;
	IMPORT_C void SetEntrySymbol(TChar aEntrySymbol);
	inline CAgnRptDef* RptDef();  
	inline const CAgnRptDef* RptDef() const;
	IMPORT_C void ClearRepeat();
	TBool operator==(const CAgnBasicEntry& aBasicEntry) const;
	void CopyBasicEntryL(const CAgnBasicEntry* aBasicEntry);

	// alarm date/time stuff
	IMPORT_C void SetAlarm(TTimeIntervalDays aDaysWarning,TTimeIntervalMinutes aTime); 
	IMPORT_C TTime AlarmInstanceDateTime() const;  
	IMPORT_C TTimeIntervalDays AlarmDaysWarning() const;
	IMPORT_C TTimeIntervalMinutes AlarmTime() const;

	// Synchronisation stuff
	IMPORT_C virtual void SetLastChangedDate();	

	// other attributes
	inline TBool IsCrossedOut() const;	
	inline TBool IsRepeating() const;  	  
	inline TBool HasExceptions() const;
	inline TBool IsStoredInline() const;
	IMPORT_C TBool HasAlarm() const;
	inline TBool DisplayInYearView() const;
	inline TBool HasEntrySymbol() const;
	inline TBool IsADayNote() const;
	inline TBool HasDefaultDisplayTime() const;
	inline TBool IsTentative() const;
	inline TBool IsSketch() const;
	inline TBool HasExtended() const;
	inline void ClearAllAttributes(); // not to be called by a view 
	IMPORT_C void SetIsCrossedOut(TBool aIsCrosedOut);// if a todo call CAgnTodo::CrossOut/UnCrossOut instead	
	IMPORT_C void SetIsRepeating(TBool aIsRepeating); // not to be called by a view 
	IMPORT_C void SetHasExceptions(TBool aHasExceptions); // not to be called by a view 
	void SetIsStoredInline(TBool aIsStoredInline);	// not to be called by a view
	IMPORT_C void SetHasAlarm(TBool aHasAlarm);	
	IMPORT_C void SetDisplayInYearView(TBool aDisplayInYearView);
	IMPORT_C void SetHasEntrySymbol(TBool aHasEntrySymbol);
	IMPORT_C void SetIsADayNote(TBool aIsADayNote);  // not to be called by a view
	IMPORT_C void SetHasDefaultDisplayTime(TBool aHasDefaultDisplayTime);
	IMPORT_C void SetIsTentative(TBool aIsTentative);
	IMPORT_C void SetIsSketch(TBool aIsSketch);
	IMPORT_C void SetHasExtended(TBool aHasExtended);

	IMPORT_C void SetRptStartDate(TAgnDate aRptStartDate); // not to be called by a view 
	IMPORT_C void SetRptEndDate(TAgnDate aRptEndDate);	// not to be called by a view 
	IMPORT_C void AddExceptionL(const TAgnException& aException); // not to be called by a view 
	IMPORT_C TBool RemoveException(const TAgnException& aException); // not to be called by a view 
	IMPORT_C TBool FindException(TAgnException& aException) const; // not to be called by a view 
	IMPORT_C const CAgnExceptionList* Exceptions() const;  // not to be called by a view 
	IMPORT_C void RemoveAllExceptions(); // not to be called by a view 
	IMPORT_C void PruneExceptions(); // not to be called by a view

	IMPORT_C void SetStatus(CAgnBasicEntry::TAgnStatus aStatus);
	IMPORT_C CAgnBasicEntry::TAgnStatus Status() const;

protected:
	inline CAgnBasicEntry();
	virtual TAgnDateTime AlarmOrigin() const;
	inline TAgnAlarmPreTime AlarmPreTime() const;
	void ResetStatusBits();
private:
	void CreateExceptionListL(const CAgnExceptionList* aExceptions=NULL);
protected:
	enum 
		{
		EIsCrossedOut			=EBit1,
		EIsRepeating			=EBit2,
		EHasExceptions			=EBit3,
		EIsStoredInline			=EBit4,
		EHasAlarm				=EBit5,
		EDisplayInYearView		=EBit6,	// needed ?
		EHasChanged				=EBit7,
		EHasEntrySymbol			=EBit8,
		EIsADayNote				=EBit9, // In here and not in TAgnBasicAppt to save space
		EHasDefaultDisplayTime	=EBit10,
		EIsTentative			=EBit11,
		EIsSketch				=EBit12,
		EHasExtended			=EBit13,	// Does the entry have extended attributes
		EIsNeedsAction			=EBit15,
		EIsAccepted				=EBit16,
		EIsSent					=0xC000,  // EBit15+EBit16,
		EIsConfirmed			=EBit14,
		EIsDeclined				=0xA000,  // EBit14+EBit16,
		EIsCompleted			=0x6000,  // EBit14+EBit15,
		EIsDelegated			=0xE000   // EBit14+EBit15+EBit16
		};

	CAgnRptDef* 		iRptDef; // contains the repeat definition plus exceptions
	TAgnAlarmPreTime	iAlarmPreTime;
	TUint16				iAttributes;
	TUint16				iEntrySymbol; 
	};



/**
 * Used by the <code>CAgnAppt</code> class to store appointment-specific
 * entry details.
 *
 * These details are the start and end date/time, or if the appointment
 * is a day note, the display date/time. Normally, these details should
 * be accessed using the <code>CAgnAppt</code> class.You can retrieve an
 * object of this class by calling <code>CAgnAppt::BasicAppt()</code>.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnBasicAppt
	{
public:
	inline TAgnDateTime StartDateTime() const;
	TAgnDateTime EndDateTime() const;
	void SetStartAndEndDateTime(TAgnDateTime aStartDateTime,TAgnDateTime aEndDateTime);

	TBool operator==(const TAgnBasicAppt& aBasicAppt) const;

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDateTime	iStartDateTime; 	
	TAgnDateTime	iEndDateTime;
	};


/**
 * Used by the <code>CAgnEvent</code> class to store event-specific entry
 * details.
 *
 * These details are the start and end dates and the display time.
 * Normally, these details should be accessed using the
 * <code>CAgnEvent</code> class.You can retrieve an object of this class
 * by calling <code>CAgnEvent::BasicEvent()</code>.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnBasicEvent
	{
public:
	inline TAgnDate StartDate() const;
	inline TAgnDate EndDate() const;
	void SetStartAndEndDate(TAgnDate aStartDate,TAgnDate aEndDate);
	inline TAgnTime DisplayTime() const;
	inline void SetDisplayTime(TAgnTime aDisplayTime);
	TBool operator==(const TAgnBasicEvent& aBasicEvent) const;

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDate 	iStartDate;
	TAgnDate 	iEndDate;
	TAgnTime	iDisplayTime; // the time an entry is displayed in dated
								  // views in minutes from midnight
	TUint16		iFiller;
	};


/**
 * Used by the <code>CAgnTodo</code> class to store to-do specific entry
 * details.
 *
 * These details include the ID of the to-do list to which the entry
 * belongs, the due and crossed out dates and the display time. Normally,
 * these details are accessed using member functions of the
 * <code>CAgnTodo</code> class. You can get a <code>TAgnBasicTodo</code>
 * instance by calling <code>CAgnTodo::BasicTodo()</code>.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnBasicTodo
	{
public:
	enum TStreamCrossedOutDate {EStreamCrossedOutDate,EDontStreamCrossedOutDate};

	inline TAgnDate DueDate() const;
	inline void SetDueDate(TAgnDate aDueDate);
	inline TAgnDate CrossedOutDate() const;
	void SetCrossedOutDate(TAgnDate aCrossedOutDate);
	inline TAgnTime DisplayTime() const;
	inline void SetDisplayTime(TAgnTime aDisplayTime);
	inline TAgnTodoListId TodoListId() const;
	inline void SetTodoListId(TAgnTodoListId aTodoListId);
	inline TAgnDurationDays Duration() const;
	inline void SetDuration(TAgnDurationDays aDuration);
	inline TUint Priority() const;
	inline void SetPriority(TUint aPriority);
	inline void SetAlarmFromDueDate();
	inline void SetAlarmFromStartDate();
	inline TBool IsAlarmSetFromDueDate() const;
	inline TBool IsAlarmSetFromStartDate() const;
	TBool IsDated() const;
	TBool operator==(const TAgnBasicTodo& aBasicTodo) const;

	void InternalizeL(RReadStream& aStream,
					TStreamCrossedOutDate aRestoreCrossedOutDate=EDontStreamCrossedOutDate);
	void ExternalizeL(RWriteStream& aStream,
					TStreamCrossedOutDate aStoreCrossedOutDate=EDontStreamCrossedOutDate) const;
private:
	enum TAlarmFrom {EDueDate=0,EStartDate};

	TAgnTodoListId 	iTodoListId; // The id of the todo list to which the todo belongs
	TAgnDurationDays iDuration;	
	TAgnDate 		iDueDate;
	TAgnDate		iCrossedOutDate;
	TAgnTime 		iDisplayTime;
	TUint8 			iPriority; 
	TInt8			iAlarmFrom; // the alarm has been set relative to the due date or start date
	TInt16			iFiller;
	};

#include "agmbasic.inl"

#endif
