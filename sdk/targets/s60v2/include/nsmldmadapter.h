 /*
* ==============================================================================
*  Name        : NSmlDmAdapter.h
*  Part of     : SyncML DM / Plugin adapters
*  Interface   : SDK, Device Management Adapter API
*  Description : Interface for Device Management plugin adapters
*  Version     : $Revision: 22 $ $Modtime: 19.12.03 7:52 $
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef __NSMLDMADAPTER_H
#define __NSMLDMADAPTER_H

#include <e32std.h>
#include <e32base.h>


// ===========================================================================
// MSmlDmAdapter (and related stuff)
// ===========================================================================

// ECOM interface uid for DM plugin adapters
#define KNSmlDMInterfaceUid 0x101F4D3B

#define KNSmlMaxURISegLen 32


class MNSmlDmDDFObject;
class MNSmlDmCallback;

/**
 * TNSmlDmMappingInfo
 *
 * The struct combines an URI segment to a LUID in a device.
 * Data members:
 *	TBufC<KNSmlMaxURISegLen> iURISeg		- URI segment. When using this structure, a path of
											  the URI segment must be known.
 *	TPtrC iURISegLUID						- Local  UID in the device.
*/
struct TNSmlDmMappingInfo
	{
	TBufC<KNSmlMaxURISegLen> iURISeg;
	TPtrC iURISegLUID;	
	};

/**
 * TNSmlDmAccessTypes
 *
 * Functions in the class set access types which are allowed to a DM object.
*/
class TNSmlDmAccessTypes
	{
	public:
	inline TNSmlDmAccessTypes();

	/**
	 * The function sets Add access type property. 
	*/
	inline void SetAdd();

	/**
	 * The function sets Copy access type property.
	 * (for future, the copy operation is not supported in current version)
	*/
	inline void SetCopy();

	/**
	 * The function sets Delete access type property. 
	*/
	inline void SetDelete();

	/**
	 * The function sets Execute access type property.
	 * (for future, the execute operation is not supported in current version)
	*/
	inline void SetExec();

	/**
	 * The function sets Get access type property. 
	*/
	inline void SetGet();

	/**
	 * The function sets Replace access type property. 
	*/
	inline void SetReplace();

	inline TUint8 GetACL();

	private:
	TUint8 iACL;
	};



/**
 * CSmlDmAdapter
 *
 * Device management plugin adapter interface.
 * The plugin interface which must be implemented by every
 * DM plugin adapter
 */

// CSmlDmAdapter 
class CNSmlDmAdapter : public CBase 
	{
	// Public enums
	public:

	/**
	* TError enumeration describes error codes which are used by DM adapters.
	*/
	enum TError 
		{
		EOk = 0,
		ENotFound,
		EInvalidObject,
		EAlreadyExists,
		ETooLargeObject,
		EDiskFull,
		EError
		};

	// Public functions
	public:
	/**
	* The construction for CNSmlDmAdapter class.
    * @param aDmCallback An address of the callback interface class.
	*/
	inline static CNSmlDmAdapter* NewL( const TUid& aImplementationUid, MNSmlDmCallback* aDmCallback=0); 

	/**
	* C++ default destructor.
	*/
	inline virtual ~CNSmlDmAdapter();
	
	/**
	* Pure virtual methods.
	*/

	/**
	* The function returns current version of the DDF.
	* By asking current DDF versions from adapters DM Module can control
	* possible changes in the data structure and send the changed DDF
	* description to a management server.
    * @param aVersion DDF version of the adapter. (filled by the adapter)
	*/
	virtual void DDFVersionL( CBufBase& aVersion ) = 0;
	
	/**
	* The function for filling the DDF structure of the adapter
	* @param aDDFObject	Reference to root object. A DM adapter starts filling
	* the data structure by calling AddChildObjectL to the root object and
	* so describes the DDF of the adapter. 
	*/
	virtual void DDFStructureL( MNSmlDmDDFObject& aDDF ) = 0;
	
	/**
	* The function adds a leaf object. The information about the success of the
	* command should be returned by calling SetStatusL function of MNSmlDmCallback
	* callback interface. This makes it possible to buffer the commands.
	* However, all the status codes for buffered commands must be returned at the
	* latest when the EndMessageL() of adapter is called.
	* @param aURI			URI of the object
	* @param aParentLUID	LUID of the parent object (if the adapter
	*						have earlier returned LUID to the DM Module).   
	* @param aObject		Data of the object.
	* @param aType			MIME type of the object
	* @param aStatusRef		Reference to correct command, i.e. this reference must
	*						be used when calling the SetStatusL of this command.
	*/
	virtual void AddLeafObjectL( const TDesC& aURI,const TDesC& aParentLUID, const TDesC8& aObject, const TDesC& aType,const TInt aStatusRef ) = 0;  
	
	/**
	* The function replaces data of a leaf object. The SetStatusL should be used as
	* described in AddLeafObjectL()
	* @param aURI		URI of the object
	* @param aLUID		LUID of the object (if the adapter have earlier returned
	*					LUID to the DM Module).   
	* @param aObject	Data of the object.
	* @param aType		MIME type of the object
	* @param aStatusRef	Reference to correct command, i.e. this reference
	*								must be used when calling the SetStatusL of this command.
	*/
	virtual void UpdateLeafObjectL( const TDesC& aURI, const TDesC& aLUID, const TDesC8& aObject, const TDesC& aType, const TInt aStatusRef ) = 0;
	
	/**
	* The function deletes an object and its child objects. The SetStatusL should be used
	* as described in AddLeafObjectL()
	* @param aURI		URI of the object
	* @param aLUID		LUID of the object (if the adapter have earlier returned
						LUID to the DM Module).
	* @param aStatusRef	Reference to correct command, i.e. this reference must
	*					be used when calling the SetStatusL of this command.
	*/
	virtual void DeleteObjectL( const TDesC& aURI, const TDesC& aLUID, const TInt aStatusRef ) = 0;
	
	/**
	* The function fetches data of a leaf object. The SetStatusL should be used as described
	* in AddLeafObjectL(). The data is returned by using the SetResultsL function of
	* MNSmlCallback callback interface.
	* @param aURI			URI of the object
	* @param aLUID			LUID of the object (if the adapter have earlier returned LUID
	*						to the DM Module).   
	* @param aType 			MIME type of the object
	* @param aResultsRef	Reference to correct results, i.e. this reference must be used
	*						when returning the result by calling the SetResultsL.
	* @param aStatusRef		Reference to correct command, i.e. this reference must be used
	*						when calling the SetStatusL of this command.
	*/
	virtual void FetchLeafObjectL( const TDesC& aURI, const TDesC& aLUID, const TDesC& aType, const TInt aResultsRef, const TInt aStatusRef ) = 0;
	
	/**
	* The function fetches URI list. An adapter returns the list of URI segments under the given URI
	* be separated by slash ("/"). The URI segment names for new objects must be given by the adapter.
	* The list is returned by calling the SetResultsL function of MNSmlCallback callback interface.
	* @param aParentURI					URI of the parent object
	* @param aParentLUID				LUID of the parent object (if the adapter have earlier
	*									returned LUID to the DM Module).   
	* @param aPreviousURISegmentLIist	URI list with mapping LUID information, which is known by
	*									DM engine. An adapter can use this information when verifying
	*									if old objects still exists. An adapter also knows what
	*									objects are new to DM engine and can provide LUID mapping
	*									for them. aPreviousURISegmentList parameter (see above) helps
	*									to recognise new objects.
	* @param aResultsRef				Reference to correct results, i.e. this reference must be used
	*									when returning the result by calling the SetResultsL.
	* @param aStatusRef					Reference to correct command, i.e. this reference must be used
	*									when calling the SetStatusL of this command.
	*/
	virtual void ChildURIListL( const TDesC& aURI, const TDesC& aLUID, const CArrayFix<TNSmlDmMappingInfo>& aPreviousURISegmentList, const TInt aResultsRef, const TInt aStatusRef ) = 0;
	
	/**
	* The function adds node object. In some cases an implementation of the function may be empty
	* function, if the node object does not need concrete database update. Still this function may
	* be helpful to an adapter, i.e. in passing mapping LUID of the node to DM Module. The SetStatusL
	* should be used as described in AddLeafObjectL()
	* @param aURI			URI of the object
	* @param aParentLUID	LUID of the parent object (if the adapter have earlier
	*						returned LUID to the DM Module).   
	* @param aStatusRef		Reference to correct command, i.e. this reference must
	*						be used when calling the SetStatusL of this command.
	*/
	virtual void AddNodeObjectL( const TDesC& aURI, const TDesC& aParentLUID, const TInt aStatusRef )=0;

	/**
	* Virtual methods.
	*/

	/**
	* The function is called only if an adapter has returned ETrue in AdapterCanChangeACL() function.
	* An adapter MUST always return ACL to the DM engine which stores it. ACL must be returned
	* although an adapter has not changed it. ACL is returned by using SetACLL() function of
	* MNSmlCallback interface. The SetStatusL should be used as described in AddLeafObjectL().
	* The function has default (empty) implementation, and the new implementation is not needed
	* if the adapter does not want to update ACLs. This function is called only if the
	* AdapterCanChangeACL function returns ETrue.
	* @param aURI		URI of the object.  Note: "?prop=ACL" has already been
	*					dropped by DM engine.
	* @param aLUID		LUID of the object (if the adapter have earlier returned LUID
	*					to the DM engine).   
	* @param aACL		ACL of the object.
	* @param aStatusRef	Reference to correct command, i.e. this reference must be
	*					used when calling the SetStatusL of this command.
	*/
	virtual void UpdateACLPropertyL( const TDesC& /*aURI*/, const TDesC& /*aLUID*/, const TDesC8& /*aACL*/, const TInt /*aStatusRef*/ ){};

	/**
	* The function tells if a DM adapter is able to change ACL properties which are sent
	* from DM servers. This function has default implemention  in the base class,
	* which returns EFalse. If the function returns ETrue, the UpdateACLPropertyL is called
	* when the server sends the replace to any of ACLs whic belongs to this adapter.
	* @return TBool ETrue if the adapter wants to edit ACL properties.
	*/
	virtual TBool AdapterCanChangeACL(){return EFalse;}

	/**
	* The function tells if a DM adapter cares mapping LUIDs to URIs itself. This function
	* has default implemention  in the base class, which returns EFalse.
	* @return TBool ETrue if an adapter wants to store and stores and care of mapping itself
	* without DM engines services. In default implementation the function return EFalse, when
	* DM engine stores the mappings.
	*/
	virtual TBool LuidMappingInAdapter(){return EFalse;}

	/**
	* The function tells to adapter that all the commands of the message have been handled
	* and the status codes and results to buffered commands must be returned at latests when
	* this function is called.
	*/
	virtual void EndMessageL(){}


	private:
	// ECOM framework requires this ID in object destructor
	TUid iDtor_ID_Key;

	};

/**
 * MNSmlDmCallback
 *
 * This class is callback interface which is implemented in DM Module. A pointer of an instance
 * is passed as argument in CNSmlDMAdapter::NewL() function. This interface is mostly used for
 * returning results and status codes of commands to dm client application. The interface also
 * has functionality for mapping the luids and handling access control list. The adapter does
 * not necessarily need to use any other functions but the SetStatusL and SetResultsL, if it
 * handles the luid mapping itself and let the dm application handle the acl.
*/
class MNSmlDmCallback
	{
	public:
	/**
	* The function is used to return the data in case of FetchLeafObjectL() and ChildURIListL()
	* functions. This function should not be called when command was failed, i.e. the error code
	* returned in SetStatusL is something else than EOk.
	* @param aResultsRef	Reference to correct command
	* @param aObject		The data which should be returned
	* @param aType			MIME type of the object
	*/
	virtual void SetResultsL( TInt aResultsRef, CBufBase& aObject, const TDesC& aType ) = 0;

	/**
	* The function returns information about the Add,Update,Delete and Fetch commands success
	* to DM engine. The reference to correct command must be used when calling the SetStatusL
	* function, the reference is got from the argument of the command functions. The SetStatusL
	* function must be called separately to every single command.
	* @param aStatusRef	Reference to correct command
	* @param aErrorCode	Information about the command success
	*/
	virtual void SetStatusL( TInt aStatusRef, CNSmlDmAdapter::TError aErrorCode ) = 0;

	/**
	* The function passes map information to DM Module. This function is called for a new
	* management object, both for node objects and for leaf objects. In addition if
	* ChildURIListL() function has returned new objects a mapping information of the new
	* objects must be passed. A mapping is treated as inheritable. If the mapping is not
	* set with this function, the mapping LUID of the parent object is passed in following
	* commands to the object.
	* @param aURI	URI of the object. 
	* @param aLUID	LUID of the object. LUID must contain the all information,
	*				which is needed for retrieve the invidual object from the
	*				database. Typically it is ID for the database table. In
	*				more complicated structures it can be combination of IDs,
	*				which represent path to the object.
	*/
	virtual void SetMappingL( const TDesC& aURI, const TDesC& aLUID ) = 0;

	/**
	* The function passes ACL to DM Module. This function must be called for each UpdateACLPropertyL()
	* function which has been called by DM Module. In addition an adapter can call the function for
	* other objects, i.e. if change to ACL influences to the other objects. DM module treats ACL that
	* it is derived from the parent object if it is not defined. A change to a parent object's ACL
	* overrides possible child object ACL:s, so child object's ACL:s must be set again if it is needed.
	* @param aURI	URI of the object. 
	* @param aLUID	LUID of the object. The argument is optional (null descriptor can be returned)
	*				if an adapter knows URI.
	* @param aACL	ACL of the object.
	* @return CNSmlDmAdapter::TError	EOk if command was successfully
	*									EError if command failed
	*/
	virtual CNSmlDmAdapter::TError SetACLL( const TDesC& aURI, const TDesC& aLUID, const TDesC8& aACL ) = 0;

	/**
	* The function is used to make a fetch to other adapters. The most common use is to make fetch to
	* AP adapter, because when managing the access points, the data comes as URI. For example, there
	* are ToNAPId field in some adapters, and data to it can be something like AP/IAPidx, and then
	* the link to AP adapter is needed.
	* @param aURI		URI of the object. 
	* @param aData		Reference to data, i.e. data is returned here
	* @param aStatus	The status of fetch command is returned here
	*/
	virtual void FetchLinkL(const TDesC& aURI, CBufBase& aData,CNSmlDmAdapter::TError& aStatus ) = 0;

	/**
	* The function returns the luid which is mapped to aURI. If luid is not found, the function
	* allocates a null length string, i.e. the function allocates memory in every case.
	* @param aURI	URI of the object. 
	*/
	virtual HBufC* GetLuidAllocL(const TDesC& aURI) = 0;
	};


/**
 * MNSmlDmDDFObject
 *
 * This class structure includes DDF description. When used as an argument in DM
 * Adapters Interface each adapter fills its own branch of DDF Tree to the data
 * structure. 
*/
class MNSmlDmDDFObject 
	{
	public:

	/**
	* The possible formats of a node.
	*/
	enum TDFFormat
		{
		Eb64,
		Ebool,
		Echr,
		Eint,
		Enode,
		Enull,
		Exml,
		Ebin
		};

	/**
	* The possible occurrences of a node.
	*/
	enum TOccurence
		{
		EOne,
		EZeroOrOne,
		EZeroOrMore,
		EOneOrMore,
		EZeroOrN,
		EOneOrN
		};

	/**
	* The possible scopes of a node.
	*/
	enum TScope
		{
		EPermanent,
		EDynamic
		};

	/**
	* The function sets permitted access types property to the object. Access types property is
	* mandatory element. If this function is not called all accesses are denied.
	* @param aAccessTypes	Access types property.
	*/
	virtual void SetAccessTypesL( TNSmlDmAccessTypes aAccessTypes )=0;

	/**
	* The function sets a default value property to the object. A default value is not mandatory element.
	* If this function is not called, it means that the default value property is not set at all.
	* @param aDefaultValue	Default value property.
	*/
	virtual void SetDefaultValueL( const TDesC& aDefaultValue )=0; 

	/**
	* The function sets a description property to the object. A description  is not mandatory element.
	* If this function is not called, it means that the description property value is not set at all. 
	* @param aDescription	Description property.
	*/
	virtual void SetDescriptionL( const TDesC& aDescription )=0;

	/**
	* The function sets a format property to the object. A format  is mandatory element. If this
	* function is not called for node element,  format is set as 'node'. For leaf elements this
	* function must be called.
	* @param aFormat	Format property.
	*/
	virtual void SetDFFormatL( TDFFormat aFormat )= 0;

	/**
	* The function sets an occurence property to the object.  If this function is
	* not called,  an occurence is set as TOccurence::EOne. 
	* @param aOccurence	Occurence property.
	*/
	virtual void SetOccurenceL( TOccurence aOccurence ) =0;

	/**
	* The function sets a scope property to the object.  If this function is not called,
	* the scope is set as TScope::EDynamic. 
	* @param aScope	Scope property.
	*/
	virtual void SetScopeL( TScope aScope ) = 0;

	/**
	* The function sets a title property to the object. A title is not mandatory element.
	* If this function is not called, it means that a title property value is not set at all. 
	* @param aTitle	DFTitle property.
	*/
	virtual void SetDFTitleL( const TDesC& aTitle ) = 0;

	/**
	* The function sets a MIME type property to the object. A MIME Type is mandatory element
	* for leaf objects. If this function is not called (for node elements), it means that the
	* MIME type property value is not set at all.
	* @param aMimeType	MIME type property.
	*/
	virtual void AddDFTypeMimeTypeL( const TDesC& aMimeType ) = 0;

	/**
	* The function sets an object as an object group. If this function is not called, it means
	* that the object is not an object group. Object group is a term used with for the node in
	* the management tree that is used to be a container for other object groups, container for
	* management objects or a container for both object groups and management objects. Name object
	* group is not used when talked about the nodes which are part of the management object itself.
	*/
	virtual void SetAsObjectGroup() = 0;

	/**
	* The function adds a child object and sets name of the URI segment, which is used by the DM
	* server. The highest object must be directly under root. An adapter is not able to set
	* properties of the root object. The aNodeName argument should be an empty string, when
	* the name is not fixed in DDF, i.e. in case of dynamic nodes.
	* @param aNodeName	The name of the node
	*/
	virtual MNSmlDmDDFObject& AddChildObjectL(const TDesC& aNodeName) = 0;
	};

#include "nsmldmadapter.inl"

#endif // __NSMLDMADAPTER_H