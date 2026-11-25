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

const TInt KMaxGlobalIDLength = 256;		  //256 Series 80 (32 in N7710)
const TInt KOldGlobalIdMaxValue = 32;         //Only used in Series 80
const TInt KGlobalIdExtendePartMaxSize = 224; //Only used in Series 80

typedef TBuf<KMaxGlobalIDLength> TAgnGlobalId;

/////////////////////////
//// CAgnAttendee


class CAgnAttendee : public CBase
/** Attendee to a group event, for instance a meeting.

The event may have multiple attendees. Each attendee has a role (e.g. delegate, 
organiser), a status (e.g. accepted, declined), an indicator of whether a reply 
is requested from the attendee, an address and a priority (indicates whether the 
attendee is required or requested to attend). 
@publishedAll
@released
*/
	{
public:
	/** Attendee's role 
	@publishedAll
	@released
	*/
	enum TAgnRole 
			{
			/** Attendee. */
			EAttendee,
			/** Organizer, but not owner. */
			EOrganizer, 
			/** Owner. */
			EOwner, 
			/** A delegate of another attendee. */
			EDelegate 
			};	
	/** Attendee's status.
	@publishedAll
	@released
	*/
	enum TAgnStatus 
			{
			/** Attendee has accepted request. */
			EAccepted,
			/** Action is required by attendee. */
			ENeedsAction,
			/** Request was sent to attendee. */
			ESent, 
			/** Attendee has tentatively accepted the request. */
			ETentative,
			/** Attendee's presence is confirmed. */
			EConfirmed,
			/** Attendee has declined request. */
			EDeclined,
			/** The required action has been completed by attendee. */
			ECompleted,
			/** Attendee has delegated the request to another person. */
			EDelegated,
			/** Attendee has received request. */
			EReceived 
			};
	/** The priority of the attendence request.
	@publishedAll
	@released
	*/
	enum TAgnExpect 
			{
			/** Request is informative only. */
			EFyi, 
			/** Attendee's presence is required. */
			ERequire,
			/** Attendee's presence is requested. */
			ERequest, 
			/** Immediate reply requested. */
			EImmediate 
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
class CAgnCategory: public CBase
/** A category associated with an agenda entry. 

The category's type is held as a TAgnCategoryType value. The set 
of possible categories is as defined in the vCalendar 1.0 standard, 
with the addition of an 'Extended' category type. 

The Extended category type allows for user-defined categories. An extended 
name is needed for an extended category. The name can be assigned a descriptor 
of any length.

Any number of categories can be specified for an entry. CAgnEntry provides 
member functions for adding, deleting and fetching categories for an entry. 
CAgnEntryModel's category support functions enable you to find the categories 
used in a file and to get a list of entries filtered by their category. 
@publishedAll
@released
*/
	{
public:
	/** Agenda category type.
	@publishedAll
	@released
	*/
	enum TAgnCategoryType 
			{
			/** Appointment */
			EAppointment,
			/** Business */
			EBusiness,
			/** Education */
			EEducation,	
			/** Holiday */
			EHoliday,
			/** Meeting */
			EMeeting,
			/** All other types */
			EMiscellaneous, 
			/** Personal */
			EPersonal,
			/** Phone call */
			EPhoneCall,
			/** Sick day */
			ESickDay,
			/** Special occasion */
			ESpecialOccasion,
			/** Travel */
			ETravel,
			/** Vacation */
			EVacation,
			/** Extended */
			EExtended
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
	void SetExtendedCategoryName(const TDesC& aNewName);
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
/**
@internalComponent
@released
*/
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
	void ExternalizeL(RWriteStream& aStream) const ; 
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
	void InsertCategoryL(CAgnCategory& aCategory, TInt aCategoryIndex);

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
	TBool CategoryExist(CArrayPtrFlat<CAgnCategory>* aCategoryList, CAgnCategory& aSearchCategory);

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

CAgnAttendee::TAgnRole CAgnAttendee::Role() const
/** Gets the attendee's role.

@return The attendee's role. */
	{
	return iRole;
	}

CAgnAttendee::TAgnStatus CAgnAttendee::Status() const
/** Gets the attendee's status.

@return The attendee's status. */
	{
	return iStatus;
	}

TBool CAgnAttendee::ResponseRequested() const
/** Tests whether a response has been requested from the attendee.

@return ETrue if a response is requested, EFalse if a response is not requested. */
	{
	return iRsvp;
	}

CAgnAttendee::TAgnExpect CAgnAttendee::Expect() const
/** Gets the priority indicated to the attendee.

@return Indicates whether the attendee is expected to attend. */
	{
	return iExpect;
	}


TAgnDate CAgnExtendedEntry::CreationDate() const
	{
	return iCreationDate;
	}

CAgnCategory::TAgnCategoryType CAgnCategory::Category() const
/** Gets the category type.

@return The category type. */
	{
	return iCategoryType;
	}



/*
 * Does this entry have a notes stream
 */
inline TBool CAgnExtendedEntry::NotesTextStreamExists() const
	{
	return (iNotesStreamId != KNullStreamId);
	}

/*
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
