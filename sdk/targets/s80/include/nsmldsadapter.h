/*
* ==============================================================================
*  Name        : nsmldsadapter.h
*  Part of     : SyncML DS / Plugin adapters
*  Interface   : SDK, Data Synchronisation Adapter API
*  Description : Interface for Data Synchronisation plugin adapters
*  Version     : $Revision: 24 $ $Modtime: 18.08.03 16:29 $
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

#ifndef __NSMLDSADAPTER_H__
#define __NSMLDSADAPTER_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>
#include <nsmlids.h> // TSmlDbItemUid
#include <nsmldsparams.h>
#include <nsmldbcaps.h>


// ECOM interface uid for DS plugin adapters
#define KNSmlDSInterfaceUid 0x101F4D3A

// ------------------------------------------------------------------------------------------------
// Class forwards
// ------------------------------------------------------------------------------------------------
class MNSmlDataStore;
struct TNSmlDbItemUid;

// ------------------------------------------------------------------------------------------------
// CNSmlDSAdapter
// ------------------------------------------------------------------------------------------------
class CNSmlDSAdapter : public CBase
	{
public:
	/**
    * Creates new instance of CNSmlDSAdapter based class.
    * @param aImplementationUid UID of the implementation to be created.
    * @param aDataStore Pointer to MNSmlDataStore interface.
    * @return CNSmlDSAdapter* Newly created instance.
    */
	inline static CNSmlDSAdapter* NewL( const TUid& aImplementationUid, MNSmlDataStore* aDataStore = 0 );

	/**
    * Destructor.
    */
	inline virtual ~CNSmlDSAdapter();

	/**
    * Returns adapter's parameter list to the caller.
    * @return CNSmlParamList* Pointer to list of parameters this adapters accepts.
    */
	virtual CNSmlParamList* GetParamListL() = 0;
	
	/**
    * Opens database that will be handled by this insntace.
    * @param aParams Constant reference to parameter list.
    * @param aStatus Reference to asynchronous call status.
    * @return TInt Result as TInt. If no errors happened KErrNone is returned.
    */
	virtual TInt OpenL( const CNSmlParamList& aParams, TRequestStatus& aStatus ) = 0;

	/**
    * Cancels aysnchronous OpenL() call.
    */
	virtual void CancelOpenL() = 0;

	/**
    * Closes database.
    */
	virtual void CloseL() = 0;

	/**
    * Resets the synchronization. After this adapter will fetch all items in database (i.e. slowsync).
    */
	virtual void ResetL() = 0;

	/**
    * Resets the database. Deletes all items in database.
    */
	virtual void ResetDbL() = 0;

	/**
    * Sets content format used in items received from the sync partner.
    * @param aFormat Format's MIME type.
    * @param aVersion Addidional version information for MIME type (this may be omitted).
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt SetRxItemDataFormatL( const TDesC8& aFormat, const TVersion aVersion = TVersion() ) = 0;

	/**
    * Sets content format used in items sent to the sync partner.
    * @param aFormat Format's MIME type.
    * @param aVersion Addidional version information for MIME type (this may be omitted).
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt SetTxItemDataFormatL( const TDesC8& aFormat, const TVersion aVersion = TVersion() ) = 0;

	/**
    * Returns DB capabilities for this adapter.
    * @return CNSmlDbCaps* Pointer to CNSmlDbCaps instance. Caller is responsible for releasing this instance.
    */
	virtual CNSmlDbCaps* DbCapabilitiesL() const = 0;

	/**
    * Sync partner's DB capabilities.
    * @param aCtCaps Partner DB capabilities in array.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt SetPartnerDbCapabilitiesL( const CArrayFix<TNSmlCtCapData>& aCtCaps ) = 0;

	/**
    * Gets CGI scripting parameters for this adapter.
    * @return TPtrC8 CGI scripting parameters as 8-bit descriptor.
    */
	virtual TPtrC8 CGISciptingParamsL() = 0;

	/**
    * Sets partner's CGI sciprting parameters.
    * @param aCGIParams CGI scripting parameters received from the sync partner in 8-bit descriptor.
    */
	virtual void SetCGISciptingParamsL( const TDesC8& aCGIParams ) = 0;
	
	/**
    * Fetches all modifications since last synchronization.
    * @param aUids On return this array will contain UIDs of the items that have been changed since last synchronization.
    * @param aStatus Asynchronous call status.
    * @param aFromTime End time of last synchronization.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt FetchModificationsL( CArrayFix<TNSmlModificationItem>& aUids, TRequestStatus& aStatus, const TTime& aFromTime = Time::NullTTime() ) = 0;

	/**
    * Cancels asynchronous FetchModificationsL() call.
    */
	virtual void CancelFetchModificationsL() = 0;

	/**
    * Adds new item into database.
    * @param aUid On return contains added item's UID.
    * @param aItem Data for the item to be added into database.
    * @param aLocName Value of the item's locname field as descriptor.
	* @param aMeta Meta information for the item.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt AddItemL( TNSmlDbItemUid& aUid, const TDesC8& aItem, const TDesC& aLocName = TPtrC(), const CNSmlDbMetaHandler& aMeta = CNSmlDbMetaHandler() ) = 0;

	/**
    * Updates item in the database.
    * @param aUid UID of the item to be updated.
    * @param aItem Data for the item to be updated into database.
    * @param aLocName Value of the item's locname field as descriptor.
	* @param aMeta Meta information for the item.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt UpdateItemL( const TNSmlDbItemUid& aUid, const TDesC8& aItem, const TDesC& aLocName = TPtrC(), const CNSmlDbMetaHandler& aMeta = CNSmlDbMetaHandler() ) = 0;

	/**
    * Deletes item from the database.
    * @param aUid UID of the item to be deleted.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt DeleteItemL( const TNSmlDbItemUid& aUid ) = 0;

	/**
    * Fetches one item from the database.
    * @param aUid UID of the item to be fetched.
    * @param aItem Fetched item's data.
    * @param aLocName Locname value of the fetched item.
    * @param aMeta Meta for the fetched item.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt FetchItemL( const TNSmlDbItemUid& aUid, CBufBase& aItem, HBufC*& aLocName, CNSmlDbMeta& aMeta ) = 0;

	/**
    * Called when sync partner has successfully deleted item from its database.
    * @param aUid UID of the item that has been deleted.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt PartnerDeletedL( const TNSmlDbItemUid& aUid ) = 0;

	/**
    * Called when sync partner has successfully added new item into its database.
    * @param aUid UID of the item that has been added.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt PartnerAddedL( const TNSmlDbItemUid& aUid ) = 0;

	/**
    * Called when sync partner has successfully replaced item in its database.
    * @param aUid UID of the item that has been replaced.
    * @return TInt Result, KErrNone or one of the system wide error codes.
    */
	virtual TInt PartnerReplacedL( const TNSmlDbItemUid& aUid ) = 0;

	/**
    * Returns database's UID. OpenL() must have been successfully called before this method can be called.
    * @return TNSmlDbItemUid Database's UID.
    */
	virtual TNSmlDbItemUid DbUid() const = 0;

	/**
    * Returns version of SyncML this adapter was made for.
    * @return TVersion Adapter's SyncML version.
    */
	virtual TVersion Version() const = 0;

protected:

private:
	// ECOM framework requires this ID in object destructor
	TUid iDtor_ID_Key;
	};

#include "nsmldsadapter.inl"

#endif // __NSMLDSADAPTER_H__
