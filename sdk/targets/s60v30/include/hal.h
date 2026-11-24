// hal\inc\hal.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

#ifndef __HAL_H__
#define __HAL_H__

#include <e32def.h>
#include <hal_data.h>
#include <e32property.h>




/**
@publishedPartner
@released

A set of static functions to get and set hardware attributes.

@see HALData
*/
class HAL : public HALData
	{
public:

    /**
    Synonyms for the attribute properties
    HALData::TAttributeProperty, and used in SEntry.
    */
	enum TEntryProperty
		{
		/**		
		When set, means that an attribute is meaningful on this device.
		*/
		EEntryValid=0x1,
		
		
		/**
		When set, means that an attribute is modifiable.
		*/
		EEntryDynamic=0x2,
		};

    
    /**
    Defines an entry in the array that is returned in a call to HAL::GetAll().
    */
	struct SEntry
		{
		/**
		The properties of the attribute.
		
		@see HAL::TEntryProperty
		*/
		TInt iProperties;
		
		/**
		The attribute value.
		
		@see HALData::TAttribute
		*/
		TInt iValue;
		};
public:
	IMPORT_C static TInt Get(TAttribute aAttribute, TInt& aValue);
	IMPORT_C static TInt Set(TAttribute aAttribute, TInt aValue);
	IMPORT_C static TInt GetAll(TInt& aNumEntries, SEntry*& aData);
	IMPORT_C static TInt Get(TInt aDeviceNumber, TAttribute aAttribute, TInt& aValue);
	IMPORT_C static TInt Set(TInt aDeviceNumber, TAttribute aAttribute, TInt aValue);
	};


/**
@internalComponent
*/
static const TInt32 KUidHalPropertyKeyBase = 0x1020E306;

__ASSERT_COMPILE(HAL::ENumHalAttributes<256); // only 256 UIDs allocated for HAL property keys



#endif
