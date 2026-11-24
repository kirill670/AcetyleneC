/*
* ==============================================================================
*  Name        : LbsFields.h
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
// LbsFields.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSFIELDS_H__
#define __LBSFIELDS_H__

#include <e32std.h>
#include <LbsFieldIds.h>

typedef TUint16 TPositionFieldId;

typedef TPositionFieldId TPositionFieldIdList[];
class HPositionGenericInfo;


/*
 * Class to provide the interface for the HPositionGenericInfo GetValue and SetValue methods.
 * Methods in class not intended to be called directly, clients should use the GetValue
 * and SetValue methods provided by HPositionGenericInfo.
 *
 * @internalComponent
 */
class PositionFieldManager
	{
public:
	/**
	 * Supported data types
	 */
	enum TFieldType
		{
		EUndefined,
		ETInt8,
		ETInt16,
		ETInt32,
		ETInt64,
		ETUint8,
		ETUint16,
		ETUint32,
		ETReal32,
		ETReal64,
		ETTime,
		ETTimeIntervalMicroSeconds,
		ETDesC8,
		ETDesC16
		};

friend class HPositionGenericInfo;
private:	
	// TInt8
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              TInt8 aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TInt8& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TInt16
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              TInt16 aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TInt16& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TInt32
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              TInt32 aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TInt32& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TInt64
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              const TInt64& aValue,
	                              HPositionGenericInfo& aInfo);
	
	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TInt64& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TUint8
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              TUint8 aValue,
	                              HPositionGenericInfo& aInfo);
	
	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TUint8& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TUint16
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              TUint16 aValue,
	                              HPositionGenericInfo& aInfo);
	
	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TUint16& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TUint32
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              TUint32 aValue,
	                              HPositionGenericInfo& aInfo);
	
	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TUint32& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TReal32
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              TReal32 aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TReal32& aValue,
	                              const HPositionGenericInfo& aInfo);
	
	// TReal64
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              const TReal64& aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TReal64& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TDesC8 & TDes8
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              const TDesC8& aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TDes8& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TDesC16 & TDes16
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              const TDesC16& aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TDes16& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TPtrC8 and TPtrC16 - Only Getters are needed as Setters are covered by the above
	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TPtrC8& aValue,
	                              const HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TPtrC16& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TTime
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              const TTime& aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TTime& aValue,
	                              const HPositionGenericInfo& aInfo);

	// TTimeIntervalMicroSeconds
	IMPORT_C static TInt SetValue(TPositionFieldId aFieldId,
	                              const TTimeIntervalMicroSeconds& aValue,
	                              HPositionGenericInfo& aInfo);

	IMPORT_C static TInt GetValue(TPositionFieldId aFieldId,
	                              TTimeIntervalMicroSeconds& aValue,
	                              const HPositionGenericInfo& aInfo);
	};

/*
 * Class used for indexing entries in HPositionGenericInfo.
 *
 * @internalComponent
 */
class TPositionFieldIndex
	{
public:
	inline TPositionFieldIndex();

	inline TPositionFieldId FieldId() const;
	inline TUint16 FieldStartPos() const;
	inline PositionFieldManager::TFieldType FieldType() const;

	inline void SetFieldId(TPositionFieldId aFieldId);
	inline void SetFieldStartPos(TUint16 aFieldStartPos);
	inline void SetFieldType(PositionFieldManager::TFieldType aFieldType);

private:
	/** Id of the field that this index refers to. */
	TPositionFieldId iFieldId;
	/** Offset from HPositionGenericInfo::iBuffer that the object referred to by
	this index starts at. */
	TUint16 iFieldStartPos;
	/** Type of the data that this index refers to. */
	PositionFieldManager::TFieldType iFieldType;
	};

#endif //__LBSFIELDS_H__
