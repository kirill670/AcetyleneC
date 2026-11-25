// APMSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__APMSTD_H__)
#define __APMSTD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

const TInt KMaxDataTypeLength=256;

// classes referenced
class RReadStream;
class RWriteStream;

/**
 *
 * Defines the priority associated with a data type.
 *
 * The priority is used by a device to resolve the current preferred
 * handler of a data type, in the absence of any user preferences.
 *
 * @since 5.0
 * @lib ""
 */
typedef TInt16 TDataTypePriority;

const TInt16 KDataTypePriorityUserSpecified=KMaxTInt16;
const TInt16 KDataTypePriorityHigh=10000;
const TInt16 KDataTypePriorityNormal=0;
const TInt16 KDataTypePriorityLow=-10000;
const TInt16 KDataTypePriorityLastResort=-20000;
const TInt16 KDataTypePriorityNotSupported=KMinTInt16;

/**
 *
 * A data type.
 *
 * The class maintains a string that describes the data type and an
 * associated UID. A data type is also referred to as a MIME type.
 *
 * @since 5.0
 * @lib "apmime.lib"
 */
class TDataType
	{
public:
	IMPORT_C TDataType();
	IMPORT_C TDataType(const TDataType& aDataType);
	IMPORT_C TDataType(const TDesC8& aDataType);
	IMPORT_C TDataType(TUid aUid);
	// enquiry
	IMPORT_C TInt operator==(const TDataType& aDataType) const;
	IMPORT_C TInt operator!=(const TDataType& aDataType) const;
	IMPORT_C TBool IsNative() const;
	// 
	IMPORT_C TBuf<KMaxDataTypeLength> Des() const;
	IMPORT_C TPtrC8 Des8() const;
	IMPORT_C TUid Uid() const;
	//
	IMPORT_C void InternalizeL(RReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
private:
	void ParseDes();
private:
	TBuf8<KMaxDataTypeLength> iDataType;
	TUid iUid;
	};

#define KApaAppTypeDes _L8("x-epoc/x-app")
_LIT8(KEpocUrlDataTypeHeader, "X-Epoc-Url/");

/**
 *
 * A data (MIME) type and a priority value for that data type.
 *
 * The priority is used to resolve the current preferred handler of a
 * data type, in the absence of any user preferences. An AIF file can
 * associate an application with a data (MIME) type that is not native to
 * the Symbian platform. A priority value can be specified that allows
 * the device to choose the highest priority application that can handle
 * that data type.
 *
 * @since 5.0
 * @lib "apmime.lib"
 */
class TDataTypeWithPriority
	{
public:
	IMPORT_C TDataTypeWithPriority(const TDataType& aDataType, TDataTypePriority aPriority);
public:
	TDataType iDataType;
	TDataTypePriority iPriority;
	};

#endif