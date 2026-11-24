// APMSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__APMSTD_H__)
#define __APMSTD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

/**
@publishedAll
@released
*/
const TInt KMaxDataTypeLength=256;

// classes referenced
class RReadStream;
class RWriteStream;

/** Defines the priority associated with a data type.

The priority is used by a device to resolve the current preferred handler 
of a data type, in the absence of any user preferences.

@publishedAll
@released
@see TDataTypeWithPriority */
typedef TInt16 TDataTypePriority;

/** Reserved for future use. 

@publishedAll
@released */
const TInt16 KDataTypePriorityUserSpecified=KMaxTInt16;

/** A priority value associated with a data (MIME) type. Associating an application 
with a data type at this priority means that this application, and no other, 
should ever handle the data type. Use sparingly.

@publishedAll
@released
@see TDataTypeWithPriority */
const TInt16 KDataTypePriorityHigh=10000;

/** A priority value associated with a data (MIME) type. Associating an application 
with a data type at this priority means that the data type is the primary 
type for that application. For example, "text/plain" files for a text editor.

@publishedAll
@released
@see TDataTypeWithPriority */
const TInt16 KDataTypePriorityNormal=0;

/** A priority value associated with a data (MIME) type. Associating an application 
with a data type at this priority means that the data type is a secondary 
type for that application. For example, "text/plain" files for a web browser.

@publishedAll
@released
@see TDataTypeWithPriority */
const TInt16 KDataTypePriorityLow=-10000;

/** A priority value associated with a data (MIME) type. Associating an application 
with a data type at this priority means that the data type is a last resort 
for that application. Use sparingly.

@publishedAll
@released
@see TDataTypeWithPriority */
const TInt16 KDataTypePriorityLastResort=-20000;

/** Reserved for future use. 

@publishedAll
@released */
const TInt16 KDataTypePriorityNotSupported=KMinTInt16;


class TDataType
/** A data type.

The class maintains a string that describes the data type and an associated 
UID.

A data type is also referred to as a MIME type. 

@publishedAll
@released */
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

/**
@internalComponent
*/
#define KApaAppTypeDes _L8("x-epoc/x-app")

/**
@internalComponent
*/
_LIT8(KEpocUrlDataTypeHeader, "X-Epoc-Url/");



class TDataTypeWithPriority
/** A data (MIME) type and a priority value for that data type.

The priority is used to resolve the current preferred handler of a data type, 
in the absence of any user preferences. An AIF file can associate an application 
with a data (MIME) type that is not native to Symbian OS. A priority value 
can be specified that allows the device to choose the highest priority application 
that can handle that data type.

@publishedAll 
@released 
@see TDataType
@see TDataTypePriority */
	{
public:
	IMPORT_C TDataTypeWithPriority(const TDataType& aDataType, TDataTypePriority aPriority);
public:
	/** The data type. */
	TDataType iDataType;
	/** The priority value. */
	TDataTypePriority iPriority;
	};

#endif
