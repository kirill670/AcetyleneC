// AGMIDS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMIDS_H__
#define __AGMIDS_H__

#ifdef SYMBIAN_REMOVE_COREAPPS_API_V1
#undef SYMBIAN_HIDE_COREAPPS_API_V1
#define SYMBIAN_HIDE_COREAPPS_API_V1    // forcibly hide the API 
#undef SYMBIAN_SUPPORT_COREAPPS_API_V1  // forcibly turn off support
#endif

#ifdef SYMBIAN_SUPPORT_COREAPPS_API_V1
#undef SYMBIAN_HIDE_COREAPPS_API_V1
#endif

#include <s32stor.h>
#include "agmdate.h"

class TAgnTodoListId;


// !!! TAgnId should be a simple class without the partialid and stream id stuff (which
// should be moved to TAgnEntryId) - then TAgnUniqueId becomes redundant


class TAgnId
/** The base class for agenda entry and to-do list ID types.

Internally, the ID is stored as a 32-bit unsigned integer. Derived classes 
include TAgnEntryId and TAgnTodoListId. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAgnId();
	IMPORT_C TAgnId(TStreamId aId); 
	IMPORT_C TAgnId(TStreamId aStreamId,TUint aPartialId);
	inline TAgnId(TUint aId);
	IMPORT_C TBool operator==(TAgnId aId) const;
	IMPORT_C TBool operator!=(TAgnId aId) const;
	inline TBool operator<(TAgnId aId) const;
	inline TBool operator>(TAgnId aId) const;
	inline TAgnId Id() const;
	inline TStreamId StreamId() const;
	void SetStreamId(TStreamId aId);
	void SetPartialId(TUint aId);
	TUint PartialId() const;
	inline TUint Value() const;
	inline void SetId(TAgnId aId);
	IMPORT_C TBool IsNullId() const;
	IMPORT_C void SetNullId();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TUint32 iId;
	};


class TAgnEntryId : public TAgnId
/** Uniquely identifies an agenda entry in an agenda file.

It is assigned when the entry is added to the file, but can change if the 
entry is updated. It therefore cannot be used to identify the entry for synchronisation. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAgnEntryId();
	IMPORT_C TAgnEntryId(TAgnId aId);	
	};


class TAgnInstanceId : public TAgnEntryId
/** Identifies an instance of an entry in the agenda instance model (CAgnModel), 
using an entry ID (TAgnEntryId) and an agenda date (TAgnDate). 
@publishedAll
@released
*/
	{
public:								
	IMPORT_C TAgnInstanceId();
	IMPORT_C TAgnInstanceId(TAgnEntryId aId,TAgnDate=AgnDateTime::NullDate());
	IMPORT_C TAgnInstanceId(TAgnEntryId aId,TTime aDate);
	IMPORT_C TBool operator==(TAgnInstanceId aId) const;
	IMPORT_C TBool operator!=(TAgnInstanceId aId) const;
	IMPORT_C void SetNullInstanceId();
	inline TAgnDate Date() const;
	inline void SetDate(TAgnDate aDate);
	inline void SetIdAndDate(TAgnEntryId aId,TAgnDate aDate);
	inline TBool IsNullInstanceId() const;
	
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TAgnDate 	iDate;
	TUint16		iFiller;
	};


class TAgnInstanceDateTimeId : public TAgnInstanceId
/** An instance ID which additionally stores the instance's start and end dates 
and times.

CAgnDayDateTimeInstanceList is a list of TAgnInstanceDateTimeIds. It is populated 
using CAgnModel::PopulateDayDateTimeInstanceListL(). 

The date and time are stored using agenda model dates and times i.e. a number of 
days since the agenda model's minimum valid date and a number of minutes since 
midnight, respectively. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C TTime StartDate() const;
	IMPORT_C TTime EndDate() const;
	IMPORT_C TTimeIntervalMinutes StartTime() const;
	IMPORT_C TTimeIntervalMinutes EndTime() const;
	IMPORT_C TBool HasNullStartTime() const;
	IMPORT_C TBool HasNullEndTime() const;
	inline void SetStartDate(TAgnDate aDate);
	inline void SetEndDate(TAgnDate aDate);
	inline void SetStartTime(TAgnTime aTime);
	inline void SetEndTime(TAgnTime aTime);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDateTime iStartDateTime;
	TAgnDateTime iEndDateTime;
	};


class TAgnTodoListId : public TAgnId
/** Unique identifier for a to-do list.

The ID is assigned to the to-do list when the list is added to the model, 
using CAgnEntryModel::AddTodoListL(), but it can change if the list is updated, 
so it cannot be used to identify the list for synchronisation.

To fetch a to-do list, use CAgnEntryModel::FetchTodoListL(), specifying the 
to-do list ID. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAgnTodoListId();
	IMPORT_C TAgnTodoListId(TAgnId aId);
	};

class TAgnUniqueId
/** Unique identifier for an agenda entry or to-do list.

This ID is assigned when the entry or to-do list is added to the model, 
and is preserved during updates. Because of this, it can be used to identify 
the entry or to-do list during synchronisation. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAgnUniqueId(); 
	IMPORT_C TAgnUniqueId(TUint aValue); 
	inline TBool operator==(TAgnUniqueId aUId) const;
	inline TBool operator!=(TAgnUniqueId aUId) const;
	inline TBool operator<(TAgnUniqueId aUId) const;
	inline TBool operator>(TAgnUniqueId aUId) const;
	inline TUint Id() const;
	inline void SetId(TUint aUId);
	inline void SetNullId();
	inline TBool IsNullId();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TUint32 iUId;
	};


class CAgnUniqueView;
template<class TypeId>
class TAgnMapId
/**
@internalComponent
@deprecated
*/
	{
public:
	friend class CAgnUniqueView;
	inline TypeId AgmId() const;
	inline TAgnUniqueId UniqueId() const;
	inline void SetAgmId(TypeId id);
	inline void SetUniqueId(TAgnUniqueId uid);
protected:
	TypeId			iAgmId;
	TAgnUniqueId	iUniqueId;
	};


#include "agmids.inl"

#endif
