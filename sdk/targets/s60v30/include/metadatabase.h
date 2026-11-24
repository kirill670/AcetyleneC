// MetaDatabase.h
//
// Copyright (c) Symbian Software Ltd. 2004.
//

/**
 * @file
 *
 * Meta-database declarations for use in storing comms data
 *
 * @publishedPartner
 * @prototype
 * This component is under development and is subject to change
 *
**/


#if (!defined METADATABASE_H)
#define       METADATABASE_H



// NetMeta headers
#include <MetaData.h>
#include <MetaType.h>
//#include <string.h>

// CommsDat headers
#include "CommsDat.h"



/**@plaintext

This file contains :

1/  Class for expressing a session with the storage server

			CMDBSession

		This class contains functions to create and close a session, to set the dataset version
		and to request database actions such as locking for a transaction.

2/  Generic database functionality interface

			MMetaDatabase

		This class uses a CMDBSession object


3/  General base class that inherits from MMetaDatabase to express any database element

			CMDBElement

		This class contains the ElementId for each MetaDatabase object
		An element id locates stored data in the comms database.


4/  Data classes that each inherit from CMDBElement

	a) Fields

			CMDBField<T>

		where T is a basic type value of the field (TInt, TDes, TBool etc)
		
		This class derives from

			CMDBElement

		to implement the thin template idiom


			CMDBRecordLink<T>

		where T is a record of a particular type.  This class expresses a soft-link
		from a field in one record to a record of a different type (i.e. in another table).
		The TMDBElementId value stored in this field in the repository is the id of an instance 
		of the record of type T

		This class derives from

			CMDBRecordLinkBase

		to implement the thin template idiom


	b) Field Containers


			CCDRecord

		base class for record containing specific list of fields - see CommsDatTypesv1_1.h


			CMDBRecordSet<T>

		an array of records where T is the record type.  This can represent a Table in a database.




5/  Other support classes and type definitions

			TMDBElementId

		The TMDBElementId locates a data object or set of data objects in the database.

		A TMDBElementId expresses

		<TableId><ColumnId><RecordId><Attributes>

		A TMDBElementId has a different format depending on the data type it expresses

			Table       <TableId><0><0>
			Column      <TableId><ColumnId><0>

			Record      <TableId><0><RecordId>
			Field       <TAbleId><ColumnId><RecordId>


			TMDBAttributeFlags

		Attribute settings for any storable element.
		Attributes express access control for data in the database

*/



namespace CommsDat
{

using namespace Meta;


// Private to implementation
//@internalTechnology
class CMDBSessionImpl;

// Forward declarations
class MMetaDatabase;


/*
Attribute flags for an element in the Meta Database

Attributes describe access rights to the data
*/
typedef TUint32         TMDBAttributeFlags;


/**
The identifier of an entry in the MetaDatabase

	<TableId><ColumnId><RecordId>

This identifies the data location
and the data meaning in the database schema
It also identifies the type of the data stored in this element

@publishedAll
@prototype
*/
typedef TUint32         TMDBElementId;




class CMDBSession : public CBase
/*
A session with the underlying storage server
*/
{
public:

	/**
	Calls ConstructL on new object

	@publishedAll
	*/
	IMPORT_C static CMDBSession* NewL(TVersion aRequiredVersion);

	/**
	Calls ConstructL on new object

	@publishedAll
	*/
	IMPORT_C static CMDBSession* NewLC(TVersion aRequiredVersion);

	/**
	Virtual Destructor

	@publishedAll
	*/
	IMPORT_C ~CMDBSession();


	/**
	Close session with storage server.

	@publishedAll
	@deprecated v9.1
	*/
	IMPORT_C void Close();


	/**
	Lookup latest data format version

	@publishedAll
	*/
	IMPORT_C static TVersion LatestVersion();


	/**
	Lookup data format version currently in use by client

	@publishedAll
	*/
	IMPORT_C TVersion VersionInUse();


	/**
	Open Transaction with storage server and obtain write lock - if not already set

	Will fail with KErrNotAvailable if Database write locked by another process

	Will fail if client does not have capabilities to obtain write lock on storage server.

	Will report KErrAlreadyInTransaction if transaction already open.

	@publishedAll
	*/
	IMPORT_C void OpenTransactionL();


	/**
	Commit Transaction in database.

	Will fail with KErrNotFound if not in transaction

	Will leave if error occurs during commit.

	@publishedAll
	*/
	IMPORT_C void CommitTransactionL();


	/**
	Cancel Transaction with database and rollback all associated changes

	Will fail with KErrNotFound if not in transaction

	@publishedAll
	*/
	IMPORT_C void RollbackTransactionL();

   /**
	Query if in transaction with database
	Return code will indicate
		Not in transaction,
		Already in transaction for this session,
		Write-lock not available.  Another session has it.

	@publishedAll
	*/
	IMPORT_C TInt IsInTransaction();

	
    /**
	Set attribute mask indicating required access level to stored data
	Access settings set by this call will be obeyed in all database interaction
	providing client has enough platform security capabilities to back up the request
	
	@publishedAll
	*/
	IMPORT_C void SetAttributeMask(TMDBAttributeFlags aAttributeFlags);

	
	/**
	Check flags in attribute mask
	
	@publishedAll
	*/
	IMPORT_C TBool IsSetAttributeMask(TMDBAttributeFlags aAttributeFlags);

    
    /**
	Clear attribute mask settings, indicating required access level to stored data
	setting a flag here clears it from the session attribute mask.
	
	@publishedAll
	*/
	IMPORT_C void ClearAttributeMask(TMDBAttributeFlags aAttributeFlags);

    
    /**
	Attempt to create publish/subscribe properties if not allready defined. The client
	calling this function needs WriteDeviceData capability since these properties are created
	in KUidSystemCategory category.
	@publishedAll
	*/	
	IMPORT_C TInt PublishProperties();


	/**
	Cancel all notifications that have been requested via the MMetaDatabase interface
	Individual requests can be cancelled via MMetaDatabase::CancelNotify.

	@publishedAll
	*/
	IMPORT_C TInt CancelAllNotifications();


private:

	/*
	Open a session with the storage server and establish data format version in use

	The MetaDatabase always attempts to support the required version of the client-facing data set.
	If the requested version is the latest version, KErrNone will be returned.
	If the requested version is an older but still supported version, a warning code will be returned.
	Otherwise an error will be returned and the session will not be created.

	*/
	TInt ConstructL( TVersion aRequiredVersion );

	/*
	Always construct class with version information
	*/
	CMDBSession();

private:

	CMDBSessionImpl* iMDBSessionImpl;
	
	friend class MMetaDatabase;
};





class MMetaDatabase : public Meta::MMetaData
/*
Interface for interaction with a database server
Inherited by each data set type that can be stored
*/
{
public:

	IMPORT_C virtual ~MMetaDatabase();


	/**
	Load all requested fields from the database
		Client can request to ignore access control flags by setting the attribute mask,
		but only data that the client has capabilities to view will be loaded.
		
		If inappropriate attributes explicitly set, will leave with
	        KErrPermissionDenied
	    otherwise, will silently ignore fields requiring more capabilities than client process owns

        If data not found, will leave with 
            KErrNotFound

        May also leave with KErrNoMemory or other general error codes
	@publishedAll
	*/
	IMPORT_C void LoadL(CMDBSession& aSession);


	/**
	Find and load all requested data sets that match instantiated fields
		Client can request to ignore access control flags by setting the attribute mask,
		but only data that the client has capabilities to view will be loaded.

		Will return
			ETrue on success
			KFalse if no data found that client is authorised to view
            
        Will not find data client not authorised to see even if client sets an attribute mask
        that requires higher platform security capabilities than it owns.

        May also leave with KErrNotFound or other general error codes.

	@publishedAll
	 */
	IMPORT_C TBool FindL(CMDBSession& aSession);


	/**
	Refresh all fields in the container that have not been changed by the client
		Client can request to ignore access control flags by setting the attribute mask,
		but only data that the client has capabilities to view will be loaded
		Unauthorised data will be silently ignored

		If fields not found, may leave with 
			KErrNotFound
		If fields not accessible, may leave with 
            KErrPermissionDenied
	    
        May also leave with KErrNotFound or other general error codes.

	@publishedAll
	*/
	IMPORT_C void RefreshL(CMDBSession& aSession);


	/**
	Store all initialised fields in the database - this will create new entries in the database
		Client can request to ignore access control flags by setting the attribute mask,
		but only fields that the client has capabilities to set will be created

		A request to store data in an unauthorised area will cause the function to leave.
		A request to create data in an already populated field will cause the function to leave

		Store will be atomic - all fields stored after success.  No fields stored if the function leaves

	Will leave with 
		KErrPermissionDenied 
    if client not authorised to read or write the data at given locations

	If a field already exists, will leave with
	   KErrAlreadyExists

	@publishedAll
	*/
	IMPORT_C void StoreL(CMDBSession& aSession);


	/**
	Modify all changed fields in the database - will only modify existing data, won't create new fields
		Client can request to ignore access control flags by setting the attribute mask,
		but only fields that the client has capabilities to set will be modified.

		A request to Modify data in an unauthorised area will cause the function to leave.with 
            KErrPermissionDenied
        If field does not exist, function will leave with 
            KErrNotFound

		Modify is atomic and uses an internal transaction even if no overall transaction set by client.
        All fields modified in database after success.  No fields altered if the function leaves

	@publishedAll
	*/
	IMPORT_C void ModifyL(CMDBSession& aSession);


	/**
	Delete fields from the database.
		Client can request to ignore access control flags by setting the attribute mask,
		but only fields that the client has capabilities to delete will be removed.

		A request to delete data in unauthorised area will cause the function to leave

		If client not authorised to read or write the data, will leave with 
	    	KErrPermissionDenied 

	@publishedAll
	*/
	IMPORT_C void DeleteL(CMDBSession& aSession);


	/**
	Register for notification of changes in the database

	@publishedAll
	*/
	IMPORT_C TInt RequestNotification(CMDBSession&          aSession,
									  TRequestStatus&        aRequestStatus);

	/**
	Cancel registration for notification of changes in the database

	@publishedAll
	*/
	IMPORT_C TInt CancelNotification(CMDBSession&       aSession,
									 TRequestStatus&     aRequestStatus);


protected:

	explicit MMetaDatabase();
};





class CMDBElement : public CBase, public MMetaDatabase
/*
Every item stored in the database is represented as a CMDBElement
This class contains the id and attributes of every item in the database
and for individual fields it also contains the value.

@publishedAll
@prototype
*/
{
public:


	/**
	Default Constructor

	@publishedAll
	*/
	IMPORT_C CMDBElement();


	/**
	Constructor

	@publishedAll
	*/
	IMPORT_C CMDBElement(TMDBElementId aElementId);
	
	
	/**
	Destructor

	@publishedAll
	*/
	IMPORT_C ~CMDBElement();


	// Accessors

	/**
	Returns the ElementId of an object of this type.

	The TypeId is

	<TableId><ColumnId><RecordId>

	This identifies the meaning of the field in the database schema
	It also identifies the type of the data stored in this element
	and the instance of the type

	@publishedAll
	*/
	IMPORT_C TMDBElementId ElementId() const;


	/**
	Returns the TypeId of an object of this type.

	The TypeId is

	<TableId><ColumnId><x>

	This identifies the meaning of the field in the database schema
	It also identifies the type of the data stored in this element

	@publishedAll
	*/
	IMPORT_C TMDBElementId  TypeId() const;


	/**
	Returns the RecordId of an object of this type.

	The RecordId is part of the ElementId <x><x><RecordId>

	It identifies a particular instance of this type of Element in the database

	@publishedAll
	*/
	IMPORT_C TInt RecordId() const;


	/**
	Returns the Attributes of an object of this type.

	Attributes express database access rights for the data of this element

	@publishedAll
	*/
	IMPORT_C TMDBAttributeFlags Attributes() const;


	/**
	Sets the ElementId

	@publishedAll
	*/
	IMPORT_C void SetElementId(TMDBElementId aElementId);


	/**
	Sets the TypeId

	@publishedAll
	*/
	IMPORT_C void SetTypeId(TMDBElementId aElementId);


	/**
	Sets the RecordId

	@publishedAll
	*/
	IMPORT_C void SetRecordId(TInt aRecordId);


	/**
	Sets one or more attributes

	@publishedAll
	*/
	IMPORT_C void SetAttributes(TMDBAttributeFlags aAttributes);


	/**
	Clears one or more attributes

	@publishedAll
	*/
	IMPORT_C void ClearAttributes(TMDBAttributeFlags aAttributes);


	/**
	Queries the attributes

	Returns ETrue if all queried attributes are set
	Returns EFalse if any queried attribute is not set.

	@publishedAll
	*/
	IMPORT_C TBool IsSetAttribute(TMDBAttributeFlags aAttributes) const;


	/**
	Queries the attributes

	Returns ETrue if the value of the field is not obtained from the database
	Returns EFalse if the value is obtained from the database

	@publishedAll
	*/
	IMPORT_C TBool IsNull() const;	
	
	
	/**
	@internal Component
	*/
    TMDBElementId* Data(){return &iElementId;}
    
	/**
	@internal Component
	*/
    const TMDBElementId* CData(){return &iElementId;}
    
    EXP_DATA_VTABLE

	virtual TCDFieldValueTypes Type()=0;

	/**
	Returns the TableId of an object of this type.

	The TableId is

	<TableId><x><x>

	This identifies the type of the table stored in this element

	@publishedAll
	*/
	IMPORT_C TMDBElementId  TableId() const;

protected:

	TMDBElementId     iElementId;
	
    TAny*             iValue;
    
    };




///////////////////////////////////////////////////////////////////////////////////////
//  COMMSDAT CONTAINERS
//

/**
Commsdat Container classes qualifying numeric values
@internalComponent 
*/
class CMDBNumFieldBase : public CMDBElement
{
public:
	/**
	Default Constructor
	*/
    IMPORT_C CMDBNumFieldBase();


   	/**
	Constructor setting Field's ElementId
	*/
	IMPORT_C CMDBNumFieldBase(TMDBElementId aFieldId);
		

    /**
	Assignment operator for field value
	*/
	IMPORT_C CMDBNumFieldBase& operator=(const TInt aValue);
	
    IMPORT_C void SetMaxLengthL(TInt aLength);
	     
    EXP_DATA_VTABLE

	virtual TCDFieldValueTypes Type()
		{
		return EInt;
		}    
    
};



template<class TYPE>
class CMDBField : public CMDBNumFieldBase
/**
A thin template that guards typed data access in a single CMDBElement
This class describes a single numeric field in the database

@publishedAll
*/
{
public:

	/**
	Default Constructor

	@publishedAll
	*/
	inline CMDBField()
		{
		}

	/**
	Constructor setting Field's ElementId

	@publishedAll
	*/
	inline CMDBField(TMDBElementId aFieldId)
		: CMDBNumFieldBase(aFieldId)
		{
		}


	/**
	Assignment operator for field value

	@publishedAll
	*/
	inline CMDBField<TYPE>& operator=(const TYPE& aValue)
	{
    	return (CMDBField<TYPE>&)CMDBNumFieldBase::operator=((TInt&)aValue);
	}


    inline CMDBField<TYPE>& operator=(const CMDBField<TYPE>& aValue)
	{
	    return (CMDBField<TYPE>&)CMDBNumFieldBase::operator=(aValue);
	}
	
	/**
	Conversion operator for field value

	@publishedAll
	*/
	inline operator TYPE&()
	{
		return (TYPE&)iValue;
	}
	
	/**
	Conversion operator for field value

	@publishedAll
	*/
	inline CMDBField<TYPE>& GetL()
	{
		if(IsNull() && !(ElementId() & KCDChangedFlag))
			{
			User::Leave(KErrNotFound); //todo commsdat specific error code
			}

		return (TYPE&)iValue;
	}
	
	/**
	Function for setting a value

	@publishedAll
	*/
	inline void SetL(const TYPE& aValue)
	{
	CMDBNumFieldBase::operator=(aValue);
	}
	
};



//////////////////
/**
Base Container class qualifying a text field
@internalComponent
*/
class CMDBTextFieldBase : public CMDBElement
{
public:
	/**
	Default Constructor
	*/
	IMPORT_C CMDBTextFieldBase();

	/**
	Constructor setting Field's ElementId
	*/
	IMPORT_C CMDBTextFieldBase(TMDBElementId aFieldId);    
	
	
	/**
	Destructor that deletes the field value
	*/
	IMPORT_C ~CMDBTextFieldBase();    
	
	
	/**
	Assignment Operator setting Field's value
	*/
	IMPORT_C CMDBTextFieldBase& operator=(const TDesC& aValue);
	
	    	
    IMPORT_C void SetMaxLengthL(TInt aLength);

    EXP_DATA_VTABLE
    
	virtual TCDFieldValueTypes Type()
		{
		return EText;
		}    

};







template<>
class CMDBField<TDesC> : public CMDBTextFieldBase
/**
A thin template that guards typed data access in a single CMDBElement
This class describes a single field in the database

@publishedAll
*/
{
public:

	/**
	Default Constructor

	@publishedAll
	*/
	inline CMDBField()
		{
		}

	/**
	Constructor setting Field's ElementId

	@publishedAll
	*/
	inline CMDBField(TMDBElementId aFieldId)
		: CMDBTextFieldBase(aFieldId)
		{
		}


    inline void SetMaxLengthL(TInt aLength)
	// create a new buffer if necessary.
	{
	    CMDBTextFieldBase::SetMaxLengthL(aLength);
	}
	
    inline CMDBField<TDesC>& operator=(const TDesC& aValue)
	{
        CMDBTextFieldBase::operator=(aValue);	   
        return *this; 
	}

    inline CMDBField<TDesC>& operator=(CMDBField<TDesC>& aValue)
	{
        CMDBTextFieldBase::operator=((const TDesC&)aValue);	
        return *this;   
	}

	/**
	Conversion operator for field value

	@publishedAll
	*/
	inline operator const TDesC&()
	{
        if (! iValue)
            return KNullDesC;

		return *(HBufC*)iValue;
	}
	
	/**
	Conversion operator for field value

	@publishedAll
	*/
	inline TDesC& GetL()
	{
		if(IsNull() && !(ElementId() & KCDChangedFlag))
			{
			User::Leave(KErrNotFound); //todo commsdat specific error code
			}

		return *(HBufC*)iValue;
	}
	
	/**
	Function for setting a value

	@publishedAll
	*/
	inline void SetL(const TDesC& aValue)
	{
	SetMaxLengthL(aValue.Length());
	CMDBTextFieldBase::operator=(aValue);
	}
	
	
};


//////////////////
/**
Container class for qualifying binary values
@internalComponent 
*/
class CMDBBinFieldBase : public CMDBElement
{
public:
	/**
	Default Constructor
	*/
	IMPORT_C CMDBBinFieldBase();

	
	/**
	Constructor setting Field's ElementId
	*/
	IMPORT_C CMDBBinFieldBase(TMDBElementId aFieldId);    
	
	
	/**
	Destructor that deletes the field value
	*/
	IMPORT_C ~CMDBBinFieldBase();    
	
	
	/**
	Assignment Operator setting Field's value
	*/
	IMPORT_C CMDBBinFieldBase& operator=(const TDesC8& aValue);
	    	
    /**
	To allocate space for field data.
	*/
	IMPORT_C void SetMaxLengthL(TInt aLength);

    EXP_DATA_VTABLE
    
	virtual TCDFieldValueTypes Type()
		{
		return EDesC8;
		}    
};


template<>
class CMDBField<TDesC8> : public CMDBBinFieldBase
/**
A thin template that guards typed data access in a single CMDBElement
This class describes a single field in the database

@publishedAll
*/
{
public:

	/**
	Default Constructor

	@publishedAll
	*/
	inline CMDBField()
		{
		}

	/**
	Constructor setting Field's ElementId

	@publishedAll
	*/
	inline CMDBField(TMDBElementId aFieldId)
		: CMDBBinFieldBase(aFieldId)
		{
		}

    inline void SetMaxLengthL(TInt aLength)
	// create a new buffer if necessary.
    	{
    	    CMDBBinFieldBase::SetMaxLengthL(aLength);
    	}
	
	
    inline CMDBField<TDesC8>& operator=(const TDesC8& aValue)
    	{
            return (CMDBField<TDesC8>&)CMDBBinFieldBase::operator=(aValue);	    
    	}
	
	
    inline CMDBField<TDesC8>& operator=(CMDBField<TDesC8>& aValue)
	// Copy assignment
        {
            return (CMDBField<TDesC8>&)CMDBBinFieldBase::operator=((const TDesC8&)aValue);	    
    	}


	/**
	Conversion operator for field value

	@publishedAll
	*/
	inline operator const TDesC8&()
    	{
		    if (! iValue)
                return KNullDesC8;

    		return *(HBufC8*)iValue;
    	}
    	
    /**
	Conversion operator for field value

	@publishedAll
	*/
	inline TDesC8& GetL()
	{
		if(IsNull() && !(ElementId() & KCDChangedFlag))
			{
			User::Leave(KErrNotFound); //todo commsdat specific error code
			}

    	return *(HBufC8*)iValue;
	}
	
	/**
	Function for setting a value

	@publishedAll
	*/
	inline void SetL(const TDesC8& aValue)
	{
	SetMaxLengthL(aValue.Length());
	CMDBBinFieldBase::operator=(aValue);
	}
	
};



///////////////////////////////////////////////////////////////////////////////////////////////

/**
Base class for CMDBRecordLink
@internalComponent 
*/
class CMDBRecordLinkBase : public CMDBNumFieldBase
{
public :	

	IMPORT_C CMDBRecordLinkBase();

	IMPORT_C CMDBRecordLinkBase(TMDBElementId aLinkingFieldId);

	IMPORT_C CMDBRecordLinkBase(TMDBElementId aLinkingFieldId, CMDBElement* aLinkedRecord);


	IMPORT_C ~CMDBRecordLinkBase();

	/**
	Assignment operator for field value
	which sets the id of the element list
	*/
	IMPORT_C CMDBRecordLinkBase& operator=(const TMDBElementId aValue);


	/**
	Conversion operator for field value
	which gets the id of the element list
	*/
	IMPORT_C operator TMDBElementId();


protected:

	EXP_DATA_VTABLE

public:
    
	// the record referenced by the link id stored in the value of this field.
	CMDBElement*     iLinkedRecord;

};



template<class RECORD_TYPE>
class CMDBRecordLink : public CMDBRecordLinkBase
/**
- This container expresses a 'soft-link' to a nested record.
- The value of this field as stored in the database is the ElementId of the linked record.
- The linked record is referenced by iLinkedElement
- Calling MMetaDatabase functions on this element directly will pass the call on to the
  linked data
- However, if this element is a field in a MetaDatabase record the value is taken to be the elementId
- When instantiating the pointer directly take care to match the object's
  type to the Type ID that will be found at the linking element.

@publishedAll
@prototype
*/
{
public :
	/**
	Constructor/Destructor

	@publishedAll
	*/

	inline CMDBRecordLink()
		: CMDBRecordLinkBase() {}

	inline CMDBRecordLink(TMDBElementId aLinkingFieldId)
		: CMDBRecordLinkBase(aLinkingFieldId) {}

	inline CMDBRecordLink(TMDBElementId aLinkingFieldId, RECORD_TYPE* aLinkedRecord)
		: CMDBRecordLinkBase(aLinkingFieldId, (CMDBElement*)aLinkedRecord) {}

	inline CMDBRecordLink& operator=(const TMDBElementId aValue)
	{
		return (CMDBRecordLink&)CMDBRecordLinkBase::operator=(aValue);
	}
	
	inline void SetL(const TMDBElementId aValue)
		{
		CMDBRecordLinkBase::operator=(aValue);
		}
		
	inline operator RECORD_TYPE*()
	{
		return (RECORD_TYPE*)iLinkedRecord;
	}	

};

enum TFieldTypeAttributes
/**
To express type information for all MetaDatabase fields
@publishedAll
@prototype
*/
	{
	ENoAttrs,
	ENotNull,
	};

typedef struct
/**
To express type information for all MetaDatabase fields
@publishedAll
@prototype
*/
	{
		const TMDBElementId	        iTypeId;
		const TInt                  iValType;
	    const TFieldTypeAttributes	iTypeAttr;
        const TText * const         iTypeName;
	    
	} SRecordTypeInfo;


#define MDB_GENERIC_TYPE_INFO(a, b, c, d) SGenericRecordTypeInfo(a, b, c, d)

typedef TBuf<64> TGenericTypeName;

typedef struct SGenericRecordTypeInfoTag
/**
To express type information for all MetaDatabase fields
@publishedAll
@prototype
*/
	{
	     SGenericRecordTypeInfoTag()
    	     : iTypeId(0), iValType(0), iTypeAttr(ENoAttrs) {}

	     SGenericRecordTypeInfoTag(TMDBElementId        aId,
	                               TInt                 aVal,
	                               TFieldTypeAttributes aAttrType)
   	     : iTypeId(aId), iValType(aVal), iTypeAttr(aAttrType)
    	        {
    	        }

	     SGenericRecordTypeInfoTag(TMDBElementId        aId,
	                               TInt                 aVal,
	                               TFieldTypeAttributes aAttrType,
	                               TText * const        aTypeName)
    	     : iTypeId(aId), iValType(aVal), iTypeAttr(aAttrType), iTypeName(aTypeName)
    	        {
    	        // 666 - This constructor in inherently dangerous (passing NULL pointer through aTypeName 
    	        }


	     SGenericRecordTypeInfoTag(      TMDBElementId        aId,
	                                     TInt                 aVal,
	                                     TFieldTypeAttributes aAttrType,
	                               const TGenericTypeName&    aTypeName)
    	     : iTypeId(aId), iValType(aVal), iTypeAttr(aAttrType), iTypeName(aTypeName) {}


		 TMDBElementId	       iTypeId;
		 TInt                  iValType;
	     TFieldTypeAttributes  iTypeAttr;
         TGenericTypeName	   iTypeName;
//         const TText *         iTypeName;
	} SGenericRecordTypeInfo;
	
	

class CMDBRecordBase : public CMDBNumFieldBase
/**
Base class for all MetaDatabase records
@publishedAll
@prototype
*/
	{
	public:

		inline CMDBRecordBase(){}
		inline CMDBRecordBase(TMDBElementId aElementId)
			: CMDBNumFieldBase(aElementId | KCDMaskShowFieldType){}
			
        IMPORT_C static CMDBRecordBase* RecordFactoryLC(TMDBElementId);

		IMPORT_C virtual CMDBElement* GetFieldByNameL(const TPtrC& aFieldName, TInt& aValType );

		IMPORT_C virtual CMDBElement* GetFieldByIdL(TMDBElementId aId);
		
		IMPORT_C virtual const SRecordTypeInfo* GetRecordInfo();
		
	};



class CMDBGenericRecord : public CMDBRecordBase
/**
Container for data and type information in a MetaDatabase record
For use to contain user-defined records as an alternative to declaring a 
specific record class of type CCDRecordBase

@publishedAll
@prototype
*/
    {
friend class TMDBGenericRecordVisitor;  
friend class CMDBSessionImpl;  
	public:


		EXP_DATA_VTABLE
		    
		explicit inline CMDBGenericRecord(TMDBElementId aElementId)
			: CMDBRecordBase(aElementId) {}

        EXPORT_C ~CMDBGenericRecord();

		IMPORT_C virtual CMDBElement* GetFieldByNameL(const TPtrC& aFieldName, TInt& aValType );

		IMPORT_C CMDBElement* GetFieldByIdL(TMDBElementId aId);
		
		
		IMPORT_C void InitializeL(const TDesC& aTableName, const SGenericRecordTypeInfo*  aNewTableInfo);
		

	private:

        /*
        The name of this record type
        */
	    TBuf<KCDMaxFieldNameLength>   	iRecordType; 
        
        /*
        array of type information about fields in this record
        order of field info should match order of fields
        */
        RArray<SGenericRecordTypeInfo>  iRecordInfo;
        /*
        array of fields in this record
        order of fields should match order of field info
        */
		RPointerArray<CMDBElement>      iFields;
	};



class CMDBRecordSetBase : public CMDBTextFieldBase
/**
Use this class to express a list of records MetaDatabase Element type
Records can be ordered using the standard RPointerArray functions

@publishedAll
@prototype
*/
    {
    public:
		/**
		@internalComponent
		*/
    	IMPORT_C CMDBRecordSetBase();

		/**
		@internalComponent
		*/
    	IMPORT_C CMDBRecordSetBase(TMDBElementId aElementId);

		/**
		@internalComponent
		*/
    	IMPORT_C ~CMDBRecordSetBase();

        inline CMDBRecordSetBase& operator=(const TPtrC& aValue)
        {
        return (CMDBRecordSetBase&)CMDBTextFieldBase::operator=(aValue);
        }
	
	protected:

    	EXP_DATA_VTABLE

    public:
       
    	RPointerArray<CMDBRecordBase> iRecords;

    };



template <class TYPE>
class CMDBRecordSet : public CMDBRecordSetBase
/**
Use this class to express a list of records of a particular MetaDatabase Element type
Records can be ordered using the standard RPointerArray functions

@publishedAll
*/
{
public:

	inline CMDBRecordSet(){}

	inline CMDBRecordSet(TMDBElementId aElementId)
		: CMDBRecordSetBase(aElementId) {}
		
	inline CMDBRecordSet<TYPE>& operator=(const TPtrC& aValue)
	{
		return (CMDBRecordSet<TYPE>&)CMDBRecordSetBase::operator=(aValue);
	}
    		
	inline TYPE* operator [](const TInt i)
	{
		return (TYPE*)iRecords[i];
	}

private:

};




} //end namespace CommsDat

#endif  // METADATABASE_H
