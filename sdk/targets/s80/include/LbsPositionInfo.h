/*
* ==============================================================================
*  Name        : LbsPositionInfo.h
*  Part of     : Mobile Location Framework/Core
*  Interface   : --
*  Description :
*   ?description_line
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/
// LbsPositionInfo.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSPOSITIONINFO_H__
#define __LBSPOSITIONINFO_H__

#include <LbsPosition.h>
#include <LbsCommon.h>
#include <LbsFields.h>


const TInt KPositionGenericInfoDefaultBufferSize = 1024;
const TInt KPositionGenericInfoDefaultMaxFields = 32;
/**
 * Position update types
 *
 * @publishedAll
 */
enum _TPositionUpdateType
	{
	EPositionUpdateUnknown = 0,
	EPositionUpdateGeneral = 0x01
	};

typedef TUint32 TPositionUpdateType;


class TPositionInfoBase : public TPositionClassTypeBase
/**
 * This class provides the interface used by RPositioner to get a location fix,
 * and as such all classes used to get location info from the location server should
 * derive from this class.
 *
 * Class contains info about the update type and the ID of the module that gave the 
 * location fix
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TPositionModuleId ModuleId() const;
	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);

	IMPORT_C TPositionUpdateType UpdateType() const;
	IMPORT_C void SetUpdateType(TPositionUpdateType aUpdateType);

protected:
	IMPORT_C TPositionInfoBase();

protected:
	/** The Id of the module that gave the location fix. */
	TPositionModuleId iModuleId;
	/** The type of update that this location fix represents. */
	TUint32 iUpdateType;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


class TPositionInfo : public TPositionInfoBase
/**
 * Standard class for getting a TPosition location fix from the location server.
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TPositionInfo();

	IMPORT_C void GetPosition(TPosition& aPosition) const;
	IMPORT_C void SetPosition(const TPosition& aPosition);

protected:
	/** The TPosition. */
	TPosition iPosition;
	};


class TPositionCourseInfo : public TPositionInfo
/**
 * Class for getting a TCourse from the location server.
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TPositionCourseInfo();

	IMPORT_C void GetCourse(TCourse& aCourse) const;
	IMPORT_C void SetCourse(const TCourse& aCourse);

protected:
	/** The TCourse. */
	TCourse iCourse;
	};


class HPositionGenericInfo : public TPositionInfo
/**
 * Class for getting arbitrary information back from the location server. The client should
 * set up to KPositionMaxRequestedFields as being requested. The definitions of the fields
 * are given in the enum _TPositionFieldId. The client must know what data type will be
 * returned for each of the fields. The server will make a best attempt to fill in
 * the requested fields.
 *
 * The client needs to allocate a big enough buffer to store the information it is requesting.
 * In order to be sure of getting back all the information the client must know how big
 * any strings to be returned are.
 *
 * @publishedAll
 */
	{
public:

	IMPORT_C static HPositionGenericInfo* New(TInt aBufferSize = KPositionGenericInfoDefaultBufferSize,
											  TInt aMaxFields = KPositionGenericInfoDefaultMaxFields);

	IMPORT_C static HPositionGenericInfo* NewL(TInt aBufferSize = KPositionGenericInfoDefaultBufferSize,
											   TInt aMaxFields = KPositionGenericInfoDefaultMaxFields);

	IMPORT_C static HPositionGenericInfo* NewLC(TInt aBufferSize = KPositionGenericInfoDefaultBufferSize,
												TInt aMaxFields = KPositionGenericInfoDefaultMaxFields);

	IMPORT_C void ClearRequestedFields();

	IMPORT_C TInt SetRequestedField(TPositionFieldId aFieldId);
	
	IMPORT_C TInt SetRequestedFields(const TPositionFieldIdList aFieldIdList);

	IMPORT_C TInt IsRequestedField(TPositionFieldId aFieldId) const;

	IMPORT_C TPositionFieldId FirstRequestedFieldId() const;

	IMPORT_C TPositionFieldId NextRequestedFieldId(TPositionFieldId aFieldId) const;

	IMPORT_C TBool IsFieldAvailable(TPositionFieldId aFieldId) const;

	IMPORT_C void ClearPositionData();	//Required on server side

	IMPORT_C TInt BufferSize() const;

	IMPORT_C TInt MaxFields() const;

	template <class TType>
		inline TInt SetValue(TPositionFieldId aFieldId, const TType& aValue) 
			{return PositionFieldManager::SetValue(aFieldId, aValue, *this);}

	template <class TType>
		inline TInt GetValue(TPositionFieldId aFieldId, TType& aValue) const 
			{return PositionFieldManager::GetValue(aFieldId, aValue, *this);}

private:
	HPositionGenericInfo(TInt aDataBufferSize, TInt aMaxFields, 
		TUint aFieldIndexStartPoint, TUint aDataStartPoint, TBool aResetRequestedFields);

	HPositionGenericInfo& operator=(const HPositionGenericInfo&);
	HPositionGenericInfo(const HPositionGenericInfo&);

	TInt FindEmptyRequestedFieldOffset(TInt& aEmptyFieldOffset) const;

	inline TPositionFieldId* RequestedFieldPtr();
	inline const TPositionFieldId* RequestedFieldPtr() const;
	inline TPositionFieldIndex* FieldIndexPtr();
	inline const TPositionFieldIndex* FieldIndexPtr() const;

private:
	friend class TPositionFieldSetter;
	friend class TPositionFieldGetter;

	/**	Max number of requesable/returnable fields. */
	const TInt iMaxFields;

	/** Offset into iBuffer of the field index. */
	const TUint iFieldIndexStartPoint;

	/** Offset into iBuffer of the actual location data. */
	const TUint iDataStartPoint;

	/** Total size of the buffer */
	const TInt iTotalBufferSize;

	/** Start of the buffer. The heap cell allocated for an instance of this class
	has space for information up to iBuffer[iTotalBufferSize-1]*/
	TUint8 iBuffer[1];	//Must be at end of class
	};

#endif //__LBSPOSITIONINFO_H__
