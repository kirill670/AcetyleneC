// AGMENTRY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMENTRY_H__
#define __AGMENTRY_H__

#include <e32base.h>
#include "agmrptd.h"
#include "agmbasic.h"
#include "agmids.h"
#include "agmpanic.h"
#include <txtmrtsr.h>
#include "agmrepli.h"
#include "agmxentr.h"


// ------------------------------- Local classes ---------------------------
class TAgnRichTextStoreResolver;
class CAgnEntry;
class CAgnAppt;
class CAgnEvent;
class CAgnAnniv;
class CAgnTodo;
class TAgnEntryStorer;
class CAgnEntryServerData;

// ------------------------- Referenced clases ------------------------------
class CStreamStore;
class CAgnEntryManager;
class CParaFormatLayer;
class CCharFormatLayer;
class CRichText;
class MPictureFactory;
class MRichTextStoreResolver;
class RAgendaServ;
class CAgnExtendedEntry;


// -------------------------------------------------------------------------
class TAgnRichTextStoreResolver : public MRichTextStoreResolver
//
// Supplied to a rich text object prior to a restoration of pictures so that it knows
// which store to load them from
//
	{
public:
	inline TAgnRichTextStoreResolver(const CStreamStore& aStore) : iStore(aStore){};
	virtual const CStreamStore& StreamStoreL(TInt) const;
private:
	const CStreamStore& iStore;
	};


/**
 * Abstract base class for the concrete agenda entry classes.
 *
 * It is derived from <code>CAgnBasicEntry</code> which provides alarm
 * and repeat information and entry attributes. <code>CAgnEntry</code>
 * adds other common entry information including entry IDs, persistence
 * and synchronisation information.Synchronisation information includes a
 * record of the date/time the entry was last modified the last changed
 * date/time. Most agenda entry functions which change an entrys details
 * or attributes call the <code>SetLastChangedDate()</code>
 * function.Agenda entries are identified by an entry ID. Instances are
 * identified by an instance ID, which consists of an entry ID and a
 * date. IDs are used so that lists of entries can be efficiently
 * processed and passed as function arguments and return values.This
 * class also provides casting functions. An entry or instance is
 * retrieved into a <code>CAgnEntry</code> because its type is not yet
 * known. To find the type of a retrieved entry or instance, use
 * <code>CAgnEntry::Type()</code>, which is implemented by each concrete
 * entry class. The return value is one of <code>EAnniv</code>,
 * <code>EAppt</code>, <code>EEvent</code> or <code>ETodo</code>. Then
 * use <code>CastToAnniv()</code>, <code>CastToAppt()</code>,
 * <code>CastToEvent()</code> or <code>CastToTodo()</code> respectively
 * to cast the entry or instance to a pointer to the appropriate class.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnEntry : public CAgnBasicEntry
	{
public:
	friend class CAgnEntryManager;
	friend class AgnEntryStorer;
	friend class TAgnInstanceEditor;
	friend class AgnModel;
	
	/**	Agenda entry type. */
	enum TType 
			{
			EAppt,	/** Appointment entry type.*/
			ETodo,	/** To-do entry type.*/
			EEvent,	/** Event entry type.*/
			EAnniv	/** Anniversary entry type.*/
			};

	// following enums for internal use only: (public so test code can use them)
	
	/** How entry's rich text object should be copied.*/
	enum TCopyHow 
			{
			EDeepCopy, /** When copying an agenda entry, indicates that the source entry's rich
						   text object is stored inline, so that the copy needs to create a new
						   stream and copy the rich text object into it.*/

			EShallowCopy /** When copying an agenda entry, indicates that the source entry's rich
							 text object is large, and so is stored out of line. In this case, the
							 copy only needs to copy the stream ID of the rich text object stored
							 in the source.*/
			};	
	enum TIncludeIdWhenComparing {ECompareId,EDontCompareId};
	enum TCreateHow {ECreateRichText,EDontCreateRichText};
	enum TMode {ENormal, EExtended, EClient, EClientAddEntry, EServer};

	IMPORT_C ~CAgnEntry();
	virtual TType Type() const=0;
	IMPORT_C const CAgnAppt* CastToAppt() const;
	IMPORT_C const CAgnTodo* CastToTodo() const;
	IMPORT_C const CAgnEvent* CastToEvent() const;
	IMPORT_C const CAgnAnniv* CastToAnniv() const;
	IMPORT_C CAgnAppt* CastToAppt();
	IMPORT_C CAgnTodo* CastToTodo();
	IMPORT_C CAgnEvent* CastToEvent();
	IMPORT_C CAgnAnniv* CastToAnniv();
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory)=0;  
	IMPORT_C TBool CompareL(CAgnEntry* aEntry,TIncludeIdWhenComparing aCompareId = ECompareId);

// alarm stuff
	IMPORT_C TPtrC AlarmSoundName() const;
	IMPORT_C void SetAlarmSoundNameL(const TDesC& aAlarmSoundName);
	IMPORT_C void ClearAlarm();

// Synchronisation stuff
	IMPORT_C virtual void SetLastChangedDate();	
	IMPORT_C TAgnUniqueId UniqueId() const;
	TAgnUniqueId UniqueIdFullBits() const;

	inline void SetUniqueId(TAgnUniqueId aUId);
	inline const TAgnReplicationData& ReplicationData() const;
	inline TAgnReplicationData& ReplicationData();
	inline void SetReplicationData(const TAgnReplicationData& aReplicationData);
	TInt LastChangedCounter() const;
	void IncLastChangedCounter();
	
// Other common stuff
	IMPORT_C void SetRptDefL(const CAgnRptDef* aRptDef);
	IMPORT_C void MakeInstanceNonRepeating();
	IMPORT_C CRichText* RichTextL();
	IMPORT_C virtual TTime InstanceStartDate() const = 0; // includes time for appts/day notes
	IMPORT_C virtual TTime InstanceEndDate() const = 0;	  // includes time for appts/daynotes
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const = 0;

// Persistence
	IMPORT_C TStreamId StoreComponentsL(CStreamStore& aStore);
	IMPORT_C void RestoreComponentsL(const CStreamStore& aStore);
	void RestoreComponentsL(RReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C CStreamStore* OpenRichTextStoreL();
	IMPORT_C CStreamStore* OpenEmbeddedStoreL();
	IMPORT_C void CloseEmbeddedStore();
	IMPORT_C CStreamStore* EmbeddedStore() const;
	IMPORT_C void LoadAllComponentsL(const MPictureFactory* aPictureFactory);
	void SetOriginatingStore(const CStreamStore& aStore);
	const CStreamStore& OriginatingStore() const;
	inline void SetRichTextStreamId(TStreamId aId);	
	inline TStreamId RichTextStreamId() const;

// Ids
	inline TAgnDate InstanceDate() const;
	inline TAgnEntryId EntryId() const;
	inline TAgnInstanceId InstanceId() const;
	inline void SetId(TAgnEntryId aId);	 
	inline void SetInstanceDate(TAgnDate aDate); 
	inline void SetIdAndInstanceDate(TAgnEntryId aId,TAgnDate aDate); 
	inline void SetIdAndInstanceDate(const TAgnInstanceId& aInstanceId); 
	inline void SetInstanceId(const TAgnInstanceId& aInstanceId); 

	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow) = 0;
	void SetRichText(CRichText* aRichText);
	void SetServer(RAgendaServ* aServer, TBool aAddEntry=EFalse);
	void SetServer();
	void SetExtended();
	void SetHowRichTextIsStored(); 
	void ExternalizeToBufferL(RWriteStream& aStream,RWriteStream& aTextStream) const;
	void InternalizeFromBufferL(RReadStream& aStream, CBufFlat* aTextBuffer);


	// Extended Entry functions
	IMPORT_C void SetGlobalIdL(const TDesC& aGlobalId);
	IMPORT_C TDesC& GlobalId();
	IMPORT_C TBool HasGlobalId();

	IMPORT_C void SetLocationL(const TDesC& aLocation);
	IMPORT_C TPtrC Location();


	IMPORT_C TBool HasAttendees();
	IMPORT_C TInt AttendeeCount();
	IMPORT_C CAgnAttendee* FetchAttendee(TInt aIndex);
	IMPORT_C void AddAttendeeL(CAgnAttendee* aAttendee);
	IMPORT_C void DeleteAttendee(TInt aIndex);

	IMPORT_C void SetCreationDateL(TAgnDate aCreationDate);
	IMPORT_C TAgnDate CreationDate();
	
	void ExternalizeBCL(RWriteStream& aStream) const;
	void ExternalizeExtendedL(RWriteStream& aStream) const;
	void InternalizeBCL(RReadStream& aStream);
	void InternalizeExtendedL(RReadStream& aStream);
	
	// Category list
	IMPORT_C TBool HasCategory();
	IMPORT_C TInt CategoryCount();
	IMPORT_C void AddCategoryL(CAgnCategory* aCategory);
	IMPORT_C CAgnCategory* FetchCategory(TInt aIndex);
	IMPORT_C void DeleteCategory(TInt aIndex);

	IMPORT_C void SetBackgroundColorL(const TRgb& aColor);
	IMPORT_C TRgb GetBackgroundColor() const;

	IMPORT_C void SetEventPriority(TUint aPriority); 
	IMPORT_C TUint EventPriority() const;
	IMPORT_C const TDesC& NotesTextL() const;  
	IMPORT_C void SetNotesTextL(HBufC* aNotes); // takes ownership
	void StoreNotesTextL(); 
	void UpdateNotesTextL();  
	void RestoreNotesTextL() const;  
	TStreamId NotesStreamId() const;
	void SetNotesStreamId(TStreamId aStreamId);
	void SetNotesClipboardStreamId(TStreamId aNotesStreamId);
	TStreamId NotesClipboardStreamId() const;

protected:	
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const = 0; // includes time for appts/day notes
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const = 0;	  // includes time for appts/daynotes
	void ConstructL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow);
	virtual void StoreSpecificsL(RWriteStream& aStream) const=0;
	virtual void RestoreSpecificsL(RReadStream& aStream)=0;
	void StoreShallowL(RWriteStream& aStream) const;
	void RestoreShallowL(RReadStream& aStream);
	void CopyBasicDetailsFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopy);
	void AdjustStartDateAccordingToRepeatStartDate(const TTime& aRptStartDate);
	void StoreToBufferL(RWriteStream& aStream, RWriteStream& aTextStream) const;
	void RestoreFromBufferL(RReadStream& aStream, CBufFlat* aTextBuffer);
protected:
	enum {ETextArrayGranularity = 32, ERichTextInlineThreshold = 128};
	TAgnInstanceId 				iInstanceId; // the entry's instance Id
	HBufC* 						iAlarmSoundName; // the alarm pre-time is stored in CAgnBasicEntry
	const CStreamStore*			iOriginatingStore;	// The store from which the entry was fetched
	CRichText*					iRichText;
	TStreamId					iRichTextStreamId;
	const CParaFormatLayer*		iParaFormatLayer;
	const CCharFormatLayer*		iCharFormatLayer;
	TAgnUniqueId				iUniqueId;	 // the entry's unique Id
	TAgnReplicationData			iReplicationData;
	CAgnEntryServerData*		iServerData;
private:
	IMPORT_C virtual void CAgnEntry_Reserved1();
	TAny* CAgnEntry_Reserved;
	};


class CAgnEntryServerData : public CBase
	{
public:
	CStreamStore*				iEmbeddedStore;
	RAgendaServ*				iServer;
	CBufFlat*					iTextBuffer;
	CAgnEntry::TMode			iEntryMode;
	CAgnExtendedEntry*			iExtended;	// Extended attributes
	};


/**
 * An appointment entry or instance.
 *
 * Other entry types have a start and end date (or due/crossed out date
 * for to-dos), and a separate display time. Appointments on the other
 * hand have a start date/time and an end date/time specified using the
 * <code>TAgnDateTime</code> class. The display time is inherent in the
 * start date/time.An appointment whose end date/time is the same as its
 * start date/time is known as a day note. A day note has a date (the
 * date component of its date/time) and a display time (the time
 * component of the date/time). The display time can be used to tell the
 * user interface where to display the day note in a view that contains
 * times of day, such as in day or week views.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnAppt : public CAgnEntry
	{
public:
	IMPORT_C static CAgnAppt* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText); 
	IMPORT_C static CAgnAppt* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText); 
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TType Type() const;
	IMPORT_C TTime StartDateTime() const;
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const; 
	IMPORT_C TTime EndDateTime() const; 
	IMPORT_C void SetStartAndEndDateTime(const TTime& aStartDateTime,const TTime& aEndDateTime=Time::NullTTime());
	IMPORT_C void SetDisplayTime(TTimeIntervalMinutes aDisplayTime);
	IMPORT_C virtual TTime InstanceStartDate() const;
	IMPORT_C virtual TTime InstanceEndDate() const;
	inline const TAgnBasicAppt& BasicAppt() const;
	void SetDisplayTimeOnly(TTimeIntervalMinutes aDisplayTime);
protected:
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const;
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const;
	virtual TAgnDateTime AlarmOrigin() const;
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	CAgnAppt();
	CAgnAppt(const CAgnAppt&);
	CAgnAppt& operator=(const CAgnAppt&);
private:
	TAgnBasicAppt iBasicAppt;
	};


/**
 * An event entry or instance.
 *
 * An event has a start date, optionally an end date, and a display time.
 * Events differ from appointments in that events have a start and end
 * date, whereas appointments have a start and end date and time. Whereas
 * an appointment can have a duration of anything from zero to 23 hours
 * and 59 minutes, an event is always an all-day entry with no start or
 * end times.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnEvent	: public CAgnEntry
	{
public:
	IMPORT_C static CAgnEvent* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C static CAgnEvent* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const;
	IMPORT_C  void SetDisplayTime(TTimeIntervalMinutes aDisplayTime);
	IMPORT_C TTime StartDate() const;
	IMPORT_C TTime EndDate() const;
	IMPORT_C void SetStartAndEndDate(const TTime& aStartDate,const TTime& aEndDate=Time::NullTTime());
	IMPORT_C virtual TType Type() const;
	IMPORT_C virtual TTime InstanceStartDate() const;
	IMPORT_C virtual TTime InstanceEndDate() const;
	inline const TAgnBasicEvent& CAgnEvent::BasicEvent() const;
	void SetDisplayTimeOnly(TTimeIntervalMinutes aDisplayTime);
protected:
	CAgnEvent();
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const;
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const;
	virtual TAgnDateTime AlarmOrigin() const;
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:	
	CAgnEvent(const CAgnEvent&);
	CAgnEvent& operator=(const CAgnEvent&);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	TAgnBasicEvent iBasicEvent;
	};


/**
 *
 * An anniversary entry or instance.
 *
 * An anniversary is an event which occurs once a year. It may be
 * repeating, and if so, the repeat type must be yearly.
 * <code>CAgnAnniv</code> is derived from <code>CAgnEvent</code> its
 * additional details include an optional base year, so that an
 * anniversary can be displayed showing the number of years since the
 * base year (e.g. how old someone is on this birthday) and/or showing
 * the base year itself.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnAnniv	: public CAgnEvent
	{
public:
	/**Anniversary display modes.*/
	enum TDisplayAs 
			{
			ENone,			/** none of the following.*/
			EBaseYear,		/** Display base year.*/
			EElapsedYears,	/** Display elapsed years.*/
			EBaseAndElapsed	/** Display both base and elapsed years.*/
			};

	IMPORT_C static CAgnAnniv* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C static CAgnAnniv* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TType Type() const;
	inline TTimeIntervalYears BaseYear() const;
	inline TBool HasBaseYear() const;
	inline TDisplayAs DisplayAs() const;
	IMPORT_C void SetBaseYear(TTimeIntervalYears aBaseYear);
	IMPORT_C void SetDisplayAs(TDisplayAs aDisplayAs);
	inline void SetHasBaseYear(TBool aHasBaseYear);
protected:
	CAgnAnniv();
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:	
	CAgnAnniv(const CAgnAnniv&);
	CAgnAnniv& operator=(const CAgnAnniv&);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	TTimeIntervalYears 	iBaseYear;
	TDisplayAs 			iDisplayAs;
	TBool				iHasBaseYear;
	};


/**
 * A to-do entry or instance.
 *
 * A to-do entry represents a task or an action to be carried out. It has
 * no start or end date or time. It does have a display time, which
 * allows it to be displayed in views that contain times of day, such as
 * day or week views. Also, it may optionally have a start date (the
 * first date on which it is displayed in day or week views) and either a
 * due date (to indicate the date by which the action should be carried
 * out) or a crossed out date (the date the action was carried out). An
 * undated to-do entry does not have a due date, a crossed out date or a
 * start date. To-do details include the ID of the to-do list to which
 * the to-do belongs and a priority.All functions which set or change
 * to-do details also set the last changed date for synchronisation
 * purposes.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnTodo	: public CAgnEntry
	{
public:
	/** Due date display mode.*/
	enum TDisplayDueDateAs 
			{
			EAutomatic,		/**Display as a date until within one week of the due date, then shown as, for example, "Next Wed".*/
			EDate,			/** Always dsiplay as a date.*/
			EDays,			/** Display as the number of days until the due date.*/
			EDontDisplay	/** Never display the due date.*/
			};

	IMPORT_C static CAgnTodo* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C static CAgnTodo* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TType Type() const;
	inline TAgnTodoListId TodoListId() const;
	IMPORT_C void SetTodoListId(TAgnTodoListId aTodoListId);
	inline TDisplayDueDateAs DisplayDueDateAs() const;
	IMPORT_C void SetDisplayDueDateAs(TDisplayDueDateAs aDisplayAs);
	inline TUint Priority() const;
	IMPORT_C void SetPriority(TUint aPriority);
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const;
	IMPORT_C void SetDisplayTime(TTimeIntervalMinutes aDisplayTime);
	IMPORT_C TTime DueDate() const;
	IMPORT_C void SetDueDate(const TTime& aDate);
	IMPORT_C TTime CrossedOutDate() const;
	IMPORT_C void CrossOut(const TTime& aDate);
	IMPORT_C void UnCrossOut();
	inline TTimeIntervalDays Duration() const;
	IMPORT_C void SetDuration(TTimeIntervalDays aDuration);
	IMPORT_C void SetAlarmFromDueDate();
	IMPORT_C void SetAlarmFromStartDate();
	inline TBool IsAlarmSetFromDueDate() const;
	inline TBool IsAlarmSetFromStartDate() const;
	IMPORT_C TBool IsDated() const;
	IMPORT_C void MakeUndated();
	IMPORT_C virtual TTime InstanceStartDate() const;
	IMPORT_C virtual TTime InstanceEndDate() const;
	inline const TAgnBasicTodo& BasicTodo() const;
	void SetDisplayTimeOnly(TTimeIntervalMinutes aDisplayTime);
protected:
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const;
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const;
	virtual TAgnDateTime AlarmOrigin() const;
	CAgnTodo();
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:
	CAgnTodo(const CAgnTodo&);
	CAgnTodo& operator=(const CAgnTodo&);
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	TAgnBasicTodo 		iBasicTodo;
	TDisplayDueDateAs	iDisplayDueDateAs; // Indicates how the due date should be displayed
	};



class AgnEntryStorer
	{
public:
	IMPORT_C static TStreamId StoreEntryL(CStreamStore& aStore,CAgnEntry* aEntry);
	IMPORT_C static CAgnEntry* RestoreEntryL(const CStreamStore& aStore,TStreamId aStreamId,
							const CParaFormatLayer* aParaFormatLayer,
							const CCharFormatLayer* aCharFormatLayer);
	IMPORT_C static CAgnEntry* RestoreEntryL(RReadStream& aStream,
							const CParaFormatLayer* aParaFormatLayer,
							const CCharFormatLayer* aCharFormatLayer);
	};

#include "agmentry.inl"

#endif
