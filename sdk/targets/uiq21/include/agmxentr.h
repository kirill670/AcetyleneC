// AGMXENTR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __AGMXENTR_H__
#define __AGMXENTR_H__

#include <e32base.h>
#include <s32std.h>
#include <gdi.h>
#include "agmdate.h"

const TInt KMaxGlobalIDLength = 32;


typedef TBuf<KMaxGlobalIDLength> TAgnGlobalId;

/////////////////////////
//// CAgnAttendee


/**
 * Attendee to a group event.
 *
 * A group event might be, for example, a meeting. An agenda entry may
 * own multiple attendees. Attendees have a role (e.g. delegate,
 * organiser), a status (e.g. accepted, declined), an indicator of
 * whether a reply is requested from the attendee, an address and a
 * priority (indicates whether the attendee is required or requested to
 * attend).
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnAttendee : public CBase
	{
public:
	/** Attendee's role*/
	enum TAgnRole 
			{
			EAttendee, /** Attendee.*/
			EOrganizer, /** Organizer, but not owner.*/
			EOwner, /** Owner.*/
			EDelegate /** A delegate of another attendee.*/
			};	
	/** Attendee's status.*/
	enum TAgnStatus 
			{
			EAccepted, /** Attendee has accepted request.*/
			ENeedsAction, /** Action required by attendee.*/
			ESent, /** Request was sent to attendee.*/
			ETentative,	/** Attendee has tentatively accepted request.*/	 
			EConfirmed, /** Attendee's presence confirmed.*/
			EDeclined, /** Attendee has declined request.*/
			ECompleted, /** Required action has been completed by attendee.*/
			EDelegated, /** Attendee has delegated the request to another person.*/
			EReceived /** Attendee has received request.*/
			};
	/** Attendence priority .*/
	enum TAgnExpect 
			{
			EFyi, /** Request is informative only.*/
			ERequire, /** Attendee's presence is required.*/
			ERequest, /** Attendee's presence is requested.*/
			EImmediate /** Immediate reply requested.*/
			};

public:
	// construct / destruct functions
	CAgnAttendee();
	IMPORT_C static CAgnAttendee* NewL(const TDesC& aAddress);
	static CAgnAttendee* NewL(RReadStream& aStream);
	static CAgnAttendee* NewL();
	void ConstructL(const TDesC& aAddress);
	~CAgnAttendee();

	// Get functions
	inline TAgnRole Role() const;
	inline TAgnStatus Status() const;
	inline TBool ResponseRequested() const;
	inline TAgnExpect Expect() const;
	IMPORT_C TPtrC Address() const;

	// Set functions
	IMPORT_C void SetRole(TAgnRole aRole);
	IMPORT_C void SetStatus(TAgnStatus aStatus);
	IMPORT_C void SetResponseRequested(TBool aRsvp);	// default is no
	IMPORT_C void SetExpect(TAgnExpect aExpect);

	// Persistence
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	IMPORT_C void Copy(CAgnAttendee* aSource);
private:
	TAgnRole				iRole;
	TAgnStatus				iStatus;
	TAgnExpect				iExpect;
	TBool					iRsvp;
	HBufC*					iAddress;
	};


//
// CAgnCategory
//
/**
 * A category associated with an agenda entry.
 *
 * The category's type is held as a <code>TAgnCategoryType</code> value
 * (an enumerated type, see below). The set of possible categories is as
 * defined in the vCalendar 1.0 standard, with the addition of an
 * "Extended" category type. The Extended category type allows for
 * user-defined categories. An extended name is needed for an extended
 * category. The name can be assigned a descriptor of any size.Any number
 * of categories can be specified for an entry. <code>CAgnEntry</code>
 * provides member functions for adding, deleting and fetching
 * categories.
 *
 * @since 5.2
 * @lib "agnmodel.lib"
 */
class CAgnCategory: public CBase
	{
public:
	/** Agenda category type.*/
	enum TAgnCategoryType 
			{
			EAppointment,		/** Appointment*/ 
			EBusiness,			/** Business*/
			EEducation,			/** Education*/
			EHoliday,			/** Holiday*/
			EMeeting,			/** Meeting*/
			EMiscellaneous,		/** All other types*/ 
			EPersonal,			/** Personal*/
			EPhoneCall,			/** Phone call*/
			ESickDay,			/** Sick day*/
			ESpecialOccasion, 	/** Special occasion*/
			ETravel,			/** Travel*/
			EVacation,			/** Vacation*/
			EExtended			/** Extended*/
			};

public:
	// construct / destruct functions
	IMPORT_C static CAgnCategory* NewL(TAgnCategoryType aCategory);
	IMPORT_C static CAgnCategory* NewL(const TDesC& aExtendedName);
	static CAgnCategory* NewL(RReadStream& aStream);
	static CAgnCategory* NewL();
	~CAgnCategory();

	// Get functions
	inline TAgnCategoryType Category() const;
	IMPORT_C const TPtrC ExtendedCategoryName() const;

	// Persistence
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;

	IMPORT_C void Copy(CAgnCategory* aSource);
	TInt SizeOfCategory();
private:
	CAgnCategory();
	void ConstructL(TAgnCategoryType aCategory,const TDesC& aExtendedName);
	static CAgnCategory* CreateCategoryL(TAgnCategoryType aCategory,const TDesC& aExtendedName);
private:
	HBufC*				iExtendedCategoryName;
	TAgnCategoryType	iCategoryType;
	};




/////////////////////////
/// CAgnExtendedEntry

class CAgnExtendedEntry : public CBase
	{
public:
	CAgnExtendedEntry();
	~CAgnExtendedEntry();
	static CAgnExtendedEntry* NewL();

	// Attendee functions
	TBool HasAttendees();
	TInt AttendeeCount();
	void AddAttendeeL(CAgnAttendee* aAttendee);
	CAgnAttendee* FetchAttendee(TInt aIndex);
	void DeleteAttendee(TInt aIndex);

	// Global ID functions
	void SetGlobalId(const TDesC& aGlobalId);
	TDesC& GlobalId();
	TBool HasGlobalId();

	// Location functions
	void SetLocationL(const TDesC& aLocation);
	TPtrC Location();


	// Persistence
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	void CopyL(CAgnExtendedEntry* aSource);
	void SetCreationDate(TAgnDate aCreationDate);
	inline TAgnDate CreationDate() const;

	// Category list
	TBool HasCategory();
	TInt CategoryCount();
	void AddCategoryL(CAgnCategory* aCategory);
	CAgnCategory* FetchCategory(TInt aIndex);
	void DeleteCategory(TInt aIndex);

	// Entry symbol color
	void SetBackgroundColor(const TRgb& aColor);
	TRgb GetBackgroundColor() const;

	void SetEventPriority(TUint aPriority);
	TUint EventPriority() const;
	void SetNotesText(HBufC* aNotes);
	const TDesC& NotesText() const;
	TStreamId NotesStreamId() const;
	void SetNotesStreamId(TStreamId aStreamId);
	inline TBool NotesTextStreamExists() const;
	inline TBool NotesTextLoaded() const;
	inline TBool StreamMarkedAsDeleted() const;
	inline void MarkStreamAsDeleted(TBool aDeleteStream);
	TStreamId NotesClipboardStreamId() const;
	void SetNotesClipboardStreamId(TStreamId aStreamId);

private:
	CArrayPtrFlat<CAgnAttendee>*	iAttendeeList;
	TAgnGlobalId					iGlobalId;
	HBufC*							iLocation;
	TAgnDate						iCreationDate;
	CArrayPtrFlat<CAgnCategory>*	iCategoryList;
	TRgb							iBackgroundSymbolColor;
	
	TUint8							iEventPriority; 
	TStreamId						iNotesStreamId;
	HBufC*							iNotesText;
	TBool							iStreamMarkedAsDeleted;
	TStreamId						iNotesClipboardStreamId;
	};



// Inline functions

/**
 * Gets the role of the attendee.
 *
 * @returns   "TAgnRole"
 *            The attendees role.
 */
CAgnAttendee::TAgnRole CAgnAttendee::Role() const
	{
	return iRole;
	}

/**
 * Gets the status of the attendee.
 *
 * @returns   "TAgnStatus"
 *            The attendees status.
 */
CAgnAttendee::TAgnStatus CAgnAttendee::Status() const
	{
	return iStatus;
	}

/**
 * Returns whether a response has been requested from the attendee.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if a response is requested,
 *            <code>EFalse</code> if a response is not requested.
 */
TBool CAgnAttendee::ResponseRequested() const
	{
	return iRsvp;
	}

/**
 * Returns the priority indicated to the attendee.
 *
 * @returns   "TAgnExpect"
 *            Indicates whether the attendee is expected to attend.
 */
CAgnAttendee::TAgnExpect CAgnAttendee::Expect() const
	{
	return iExpect;
	}


TAgnDate CAgnExtendedEntry::CreationDate() const
	{
	return iCreationDate;
	}

/**
 * Gets the category type.
 *
 * @returns   "TAgnCategoryType"
 *            The category type.
 */
CAgnCategory::TAgnCategoryType CAgnCategory::Category() const
	{
	return iCategoryType;
	}



/** 
 * Does this entry have a notes stream
 */
inline TBool CAgnExtendedEntry::NotesTextStreamExists() const
	{
	return (iNotesStreamId != KNullStreamId);
	}

/**
 * Indicates if the Notes are loaded from stream. 
 */
inline TBool CAgnExtendedEntry::NotesTextLoaded() const
	{
	return (iNotesText && iNotesStreamId != KNullStreamId);
	}

inline TBool CAgnExtendedEntry::StreamMarkedAsDeleted() const
	{
    return iStreamMarkedAsDeleted;
	}

inline void CAgnExtendedEntry::MarkStreamAsDeleted(TBool aDeleteStream) 
	{
	iStreamMarkedAsDeleted = aDeleteStream;
	}


#endif
