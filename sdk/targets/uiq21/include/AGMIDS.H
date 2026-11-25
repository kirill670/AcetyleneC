// AGMIDS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMIDS_H__
#define __AGMIDS_H__

#include <s32stor.h>
#include "agmdate.h"

class TAgnTodoListId;


// !!! TAgnId should be a simple class without the partialid and stream id stuff (which
// should be moved to TAgnEntryId) - then TAgnUniqueId becomes redundant


/**
 *
 * The base class for agenda entry and to-do list ID types.
 *
 * Internally, stores the ID as a 32-bit unsigned integer. The interface
 * to agenda entry and to-do list IDs is provided by the derived classes,
 * including <code>TAgnEntryId</code> and <code>TAgnTodoListId</code>.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnId
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


/**
 * Uniquely identifies an agenda entry in an agenda file.
 *
 * It is assigned when the entry is added to the file, but can change if
 * the entry is updated. It therefore cannot be used to identify the
 * entry for synchronisation.Entry IDs are used whenever one or more
 * entries need to be processed and passed as function arguments and
 * return values in order to avoid transferring a large amount of data.
 * Instances are uniquely identified by instance IDs,
 * (<code>TAgnInstanceId</code>) which consist of an entry ID and a date.
 *
 * @since 5.1
 * @lib "agnmodel.lib"
 */
class TAgnEntryId : public TAgnId
	{
public:
	IMPORT_C TAgnEntryId();
	IMPORT_C TAgnEntryId(TAgnId aId);	
	};


class TAgnInstanceId : public TAgnEntryId
//
// Identifies an *instance* of an entry, i.e. a Id and a date
//
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


/**
 * An instance ID which additionally stores the instances start and end
 * dates / times.
 *
 * <code>CAgnDayDateTimeInstanceList</code> is a list of
 * <code>TAgnInstanceDateTimeId</code>s. It is populated using
 * <code>CAgnModel::PopulateDayDateTimeInstanceListL()</code>. The date
 * and time are stored using agenda model dates and times i.e. a number
 * of days since the agenda models minimum valid date and a number of
 * minutes since midnight, respectively.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnInstanceDateTimeId : public TAgnInstanceId
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


/**
 * Uniquely identifies a to-do list in an agenda file.
 *
 * The ID is assigned to the to-do list when the list is added to the
 * model, using <code>CAgnEntryModel::AddTodoListL()</code>, but it can
 * change if the list is updated. It therefore cannot be used to identify
 * the list for synchronisation.To fetch a to-do list, use
 * <code>CAgnEntryModel::FetchTodoListL()</code>, specifying the to-do
 * list ID.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnTodoListId : public TAgnId
	{
public:
	IMPORT_C TAgnTodoListId();
	IMPORT_C TAgnTodoListId(TAgnId aId);
	};

/**
 * Uniquely identifies an agenda entry or to-do list in an agenda file
 * using an unsigned integer.
 *
 * This value is assigned when the entry or to-do list is added to the
 * model, and is preserved during updates. Because of this, it can be
 * used to identify the entry or to-do list during synchronisation.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnUniqueId
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
