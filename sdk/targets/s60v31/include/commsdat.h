// CommsDat.h
//
// Copyright (c) Symbian Software Ltd. 2004.
//

/**
 * @file
 *
 * Constants for use in storing comms data via CommsDat
 *
 * @publishedPartner
 *
 * @released
 */


#if (!defined COMMSDAT_H)
#define       COMMSDAT_H

#include <MetaType.h>
#include <e32property.h>


namespace Meta
    {

/**
Visitor factory functions
@internalComponent
*/
    MMetaType* TMDBNumBaseVisitorFactoryL(const TAny* mem, const TAny* data);
    MMetaType* TMDBTextBaseVisitorFactoryL(const TAny* mem, const TAny* data);
    MMetaType* TMDBBinBaseVisitorFactoryL(const TAny* mem, const TAny* data);

    IMPORT_C MMetaType* TMDBNumVisitorFactoryL(const TAny* mem, const TAny* data);
    IMPORT_C MMetaType* TMDBTextVisitorFactoryL(const TAny* mem, const TAny* data);
    IMPORT_C MMetaType* TMDBMedTextVisitorFactoryL(const TAny* mem, const TAny* data);
    IMPORT_C MMetaType* TMDBLongTextVisitorFactoryL(const TAny* mem, const TAny* data);
    IMPORT_C MMetaType* TMDBBinVisitorFactoryL(const TAny* mem, const TAny* data);
    IMPORT_C MMetaType* TMDBLinkVisitorFactoryL(const TAny* mem, const TAny* data);
    IMPORT_C MMetaType* TMDBRecordSetVisitorFactoryL(const TAny* mem, const TAny* data);
    IMPORT_C MMetaType* TMDBGenericRecordVisitorFactoryL(const TAny* mem, const TAny* data);

    }


namespace CommsDat
{

_LIT(KCommsDatName,"CommsDat");

/**
Use this constant for Panic calls

@publishedAll
*/
enum
	{
	ECommitBeforeOpenTransaction = 1,
	ERollBackBeforeOpenTransaction = 2
	};
	
using namespace Meta;

//////////////////////////////////////////////////
// VERSION INFO
//

/**
Use this constant when starting a session to ask to use the latest version of the data set
Do not use this constant if want option to keep using particular version after update
Using this constant will require the client to keep up to date with any changes in the current dataset
Use specific version constants to avoid changing until a deprecated version is no longer supported.

@publishedAll
*/
#define KCDLatestVersion            TVersion(0,0,0)


/**
Versions of the dataset in use
NB These versions will change as data set is updated
All versions apart from the one defined as KCDCurrentVersion are deprecated

@publishedAll
*/

#define KCDVersion1_1               TVersion(1,1,1)

/**
The version of the dataset supported by default
NB This version will change as data set is updated

@publishedAll
*/
#define KCDCurrentVersion           KCDVersion1_1




////////////////////////////////////////////////////
//  Attribute Flags
//

/**
Access control attribute flags.
When these are SET in the mask the attribute is obeyed
When they are CLEARED from the mask, the attribute is ignored
By default attributes are obeyed.

@publishedAll
*/
typedef enum
{
  ECDNoWriteButDelete = 0x0000010,     // R/W Read Only but deleteable      Caller should explicitly choose to modify
                                       //                                   Enforced by convention only, not with Platform Security
  ECDHidden           = 0x0000020,     // R/W Read-Write Hidden data        Not policed - hides public utility info such as default values
                                       //                                   Enforced by convention only, not with Platform Security  
  ECDPrivate          = 0x0000040,     // R/W Read-Write Private data       For sensitive user data such as passwords
                                       //                                   Policed at storage server API with platsec capability
  ECDProtectedWrite   = 0x0000080,     // W   Write-Protected data          To allow data to be read only to most clients but modifiable by a few privileged clients
                                       //                                   Policed at storage server API with platsec capability
} TCDAttributeFlags;


/////////////////////////////////////////////////////
// Field types
//
typedef enum
{
	EText,          // 50 length
	EDesC8,         // binary
	EUint32,
	EInt,
	EBool,
	EMedText,       // 256 length
	ELongText, 
    ELink
} TCDFieldValueTypes;

const TInt KMaxTextLength		= 50;
const TInt KMaxMedTextLength	= 255; //256;
const TInt KMaxLongTextLength	= 1024;
const TInt KMaxNumLength		= 1;

////////////////////////////////////////////////////
// Masks for Element Type info
//


/**
Mask to use to hide attribute reserved bits

@publishedAll
*/
#define KCDMaskHideAttrAndRes       0xffffff00


/**
Mask to use to show reserved bits

@publishedAll
*/
#define KCDMaskShowRes              0x8000000f


/**
Mask to use to hide reserved bits

@publishedAll
*/
#define KCDMaskHideRes              0x7ffffff0


/**
T x x   Mask to show Table Type info

@publishedAll
*/
#define KCDMaskShowRecordType       0x7f800000


/**
x C x   Mask to show Column Type 

@publishedAll
*/
#define KCDMaskShowFieldType        0x007f0000


/**
T C x   Mask to show Table and Column Type 

@publishedAll
*/
#define KCDMaskShowType             0x7fff0000


/**
T x R   Mask to show Record id

@publishedAll - don't use this.  Replace with KCDMaskShowRecordId
*/
#define KCDMaskShowInstance         0x0000ff00


/**
T x R   Mask to show Record id
Use in place of KCDMaskShowInstance
@publishedAll
*/
#define KCDMaskShowRecordId         0x0000ff00


/**
T C R   Mask to show Field instance without attributes or reserved bits

@publishedAll
*/
#define KCDMaskShowField            0x7fffff00


/**
T C R   Mask for Central Repository to find a single field

@internalComponent
*/
#define KCDMaskFindSingleField		0x7FFFFFFE

/**
T x R   Mask to show Record Type and Record Id without column type, attributes or reserved bits

@publishedAll
*/
#define KCDMaskShowRecordTypeAndId  0x7f80ff00

/**
x C R   Mask to show Column Type and Record Id without Record type, attributes or reserved bits

@
*/
#define KCDMaskShowColumnTypeAndRecordId  0x007fff00


/**
Mask to show Attributes

@publishedAll
*/
#define KCDMaskShowAttributes       0x000000f0


/**
Mask for all attribute settings that apply to read and write operations
see TCDAttributeFlags

  ECDNoWriteButDelete = 0x0000010                             
  ECDHidden           = 0x0000020
  ECDPrivate          = 0x0000040
  ECDProtectedWrite   = 0x0000080
*/
#define KCDMaskShowReadWriteAttributes  0x000000f0

/*
Mask for all attribute settings that apply to read operations
see TCDAttributeFlags
                          
  ECDHidden           = 0x0000020
  ECDPrivate          = 0x0000040
*/
#define KCDMaskShowReadAttributes       0x00000060    

/**
Mask to use to show attributes and reserved bits

@publishedAll
*/
#define KCDMaskShowAttrAndRes       0x000000ff


/**
Id for the Initial record in a record set

@publishedAll
*/
#define KCDInitialRecordId			0x00000100


/**
Id for the Initial table in the database

@publishedAll
*/
#define KCDInitialTableId			0x00800000


/**
Id for the Initial User defined table in the database
clients have 64 table ids available to them

@publishedAll
*/
#define KCDInitialUDefRecordType   0x5F800000


/**
Id for the Last User defined table in the database.

@publishedAll
*/
#define KCDLastUDefRecordType      0x7F800000


/**
Id for the Initial column in a record set

@publishedAll
*/
#define KCDInitialColumnId			0x00010000


/**
T C 0   location for default field values

@publishedAll
*/
#define KCDDefaultRecord            0x00000000


/**
Combine with table id and Column id to give the location of column type info

@publishedAll
*/
#define KCDColumnTypeInfo           0x0000ff00

/*
Combine with table id to give the location of table type info
*/
#define KCDTableTypeInfo            0x007fff00

/*
Combine with table id to give location of record type info
*/
//#define KCDRecordTypeInfo			0x007f0000


/**
Use to request allocation of a new table id.
Should only be called when creating a new user-defined table

@publishedPartner
*/
#define KCDNewTableRequest          0x007fff00


/**
Combine with table id to give request for a new column in a table.
The table must already exist.  New columns should only normally be 
requested when creating a new user-defined table

@publishedPartner
*/
#define KCDNewColumnRequest			0x0000ff01



/**
Combine with table id to give request for a new record in a table.
The table must already exist.

@publishedAll
*/
#define KCDNewRecordRequest			0x807f0001


/**
Combined with CMDBField, it finds the TableId given the table name

@publishedAll
*/
#define KCDMaskGenericTableName			KCDNewTableRequest



/**
Maximum number of tables that can be created in one repository

@publishedAll
*/
#define KCDMaxTables                254


/**
Maximum number of User defined tables that can be created in one repository

@publishedAll
*/
#define KCDMaxUserDefTables         64


/**
Maximum number of columns that can be created in one table

@publishedAll
*/
#define KCDMaxColumns               126  


/**
Maximum number of records that can be stored in one table

@publishedAll
*/
#define KCDMaxRecords               254


/**
Maximum number of characters in a field name

@publishedAll
*/
#define KCDMaxFieldNameLength        64



/**
Flag to indicate change in field
Not for use in database.  Just with fields

@internalComponent
*/
#define KCDChangedFlag      0x00000001


#define KCDMaxRecordId     0x0000ff00

#define KCDMaxColumnId     0x007f0000

#define KCDMaxTableId      0x7f800000



/**
Typedefs for convenience in meta data definitions
@internalComponent
*/
using namespace Meta;

template <class TYPE> class TMDBVisitor;
class TMDBRecordLinkVisitor;
class TMDBRecordSetVisitor;
class TMDBGenericRecordVisitor;
class CMDBElement;

/*
Visitors for field values
*/
typedef TMDBVisitor<TInt>                           TMDBNum;
typedef TMDBVisitor<TInt>                           TMDBBool;
typedef TMDBVisitor<TDesC>                          TMDBDes;
typedef TMDBVisitor<TDesC8>                         TMDBDes8;

/*
Visitors for containers
*/
typedef TMDBRecordLinkVisitor						TMDBLink;
typedef TMDBRecordSetVisitor                        TMDBRecordSet;
typedef TMDBGenericRecordVisitor                    TMDBGenRecord;

/** UIDs for CommDB event notification */
const TUid KUidCommDbNotificationEvent = {0x1020762E};
const TUid KUidCommsDatStatusEvent = {KUidSystemCategoryValue};
const TInt KCommsDatStatusEventCommitSeq = 0x1020762F;

/**
Metadatabase container type ids

@internalComponent
*/

#define KCDTIdMDBElement            123
#define KCDTIdMDBNumFieldBase       223
#define KCDTIdMDBTextFieldBase      224
#define KCDTIdMDBBinFieldBase       225
#define KCDTIdMDBRecordLinkBase     323
#define KCDTIdMDBRecordSetBase      523
#define KCDTIdMDBGenericRecord      585


/**
Macro for interaction with netmeta
@publishedAll
*/
#define X_REGISTER_ATTRIBUTE( thisMetaClass, var, metaType ) \
 { _FOFF( thisMetaClass, var ), Meta::metaType##VisitorFactoryL },


#define EXP_DATA_VTABLE \
 IMPORT_C virtual Meta::SVDataTableEntry const* GetVDataTable() const;	\
 IMPORT_C virtual TUint8* GetAttribPtr(const TInt aOffset) const;	\
 IMPORT_C static Meta::SVDataTableEntry const* GetVDataTableStatic(); \
 static const Meta::SVDataTableEntry iVDataTable[];


/**
Macros used to implement virtual functions from MMetaData interface and construct the v data table
@publishedAll
*/
#define EXP_START_ATTRIBUTE_TABLE( thisMetaClass, uid, typeId ) \
 EXPORT_C Meta::SVDataTableEntry const* thisMetaClass::GetVDataTable() const { return &iVDataTable[0]; };	\
 EXPORT_C TUint8* thisMetaClass::GetAttribPtr(const TInt aOffset) const { return (TUint8*)this + aOffset; };	\
 EXPORT_C Meta::SVDataTableEntry const* thisMetaClass::GetVDataTableStatic() { return &iVDataTable[0]; }; \
 const Meta::SVDataTableEntry thisMetaClass::iVDataTable[] = { \
 { uid, reinterpret_cast<Meta::TMetaTypeNewL>(typeId) },


#define END_ATTRIBUTE_TABLE_BASE_N( baseMetaClass, baseId, entry ) \
 { (TInt)((TAny*)(baseMetaClass::GetVDataTableStatic() + entry)), NULL }};


} //end namespace CommsDat
#endif
