/*
* ==============================================================================
*  Name        : NSmlDSProfileListAPI.h
*  Part of     : Nokia SyncML / DS Profile API
*  Interface   : CNSmlDSProfileListAPI
*  Description : An interface to DS settings database.
*  Version     : $Revision: 3 $ $Modtime: 28.05.04 11:42 $
*
*  Copyright © 2004 Nokia Corporation.
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

#ifndef __NSMLDSPROFILELISTAPI_H
#define __NSMLDSPROFILELISTAPI_H


// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>

// ------------------------------------------------------------------------------------------------
// Class forwards
// ------------------------------------------------------------------------------------------------

class CNSmlDSProfileAPI;

// ------------------------------------------------------------------------------------------------
// Class declarations
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// CNSmlDSProfListItem
// ------------------------------------------------------------------------------------------------
class CNSmlDSProfListItem : public CBase
    {
public:

    /**
    * Destructor.
    */
    ~CNSmlDSProfListItem();
    /**
    * Constructor.
    */
    CNSmlDSProfListItem();

    /**
    * Get profile id.
    * @return TInt Result, id of a profile.
    */
    virtual TInt GetProfileId() const;
    /**
    * Get profile name.
    * @return TPtrC Result, name of a profile.
    */
    virtual TPtrC GetProfileName() const;

    void SetProfileId( const TInt aProfileId );
    void SetProfileName( const TDesC& aFieldValue );

private:
	
    TInt iProfileId;
    HBufC* iFieldValue;
    };

// ------------------------------------------------------------------------------------------------
// CNSmlDSContentTypeItem
// ------------------------------------------------------------------------------------------------
class CNSmlDSContentTypeItem : public CBase
	{
public:
    /**
    * Constructor;
    */
	CNSmlDSContentTypeItem();
    /**
    * Destructor;
    */
	~CNSmlDSContentTypeItem();

    /**
    * Get human readable name for the content.
    * @return TPtrC, Content's display name.
    */
	virtual TPtrC GetDisplayName();
    /**
    * Get MIME type for the content.
    * @return TPtrC, Content's MIME type.
    */
	virtual TPtrC GetMimeType();
    /**
    * Get implementation UID for the content.
    * @return TInt, Content's implementation UID.
    */
	virtual TInt GetImplUid();

	void SetDisplayNameL( TDesC& aDispName ); 
	void SetMimeTypeL( TDesC& aType ); 
	void SetImplUid( TInt aImplementationUID ); 

private:
	HBufC* iDisplayName;
	HBufC* iMimeType;
	TInt   iImplementationUID;
	};


// ------------------------------------------------------------------------------------------------
// CNSmlDSProfileListAPI
// ------------------------------------------------------------------------------------------------
class CNSmlDSProfileListAPI : public CBase
    {
public:
    
    /**
    * Destructor.
    */
    ~CNSmlDSProfileListAPI();
    
    /**
    * Two-phase (leave safe) constructor.
    * @return CNSmlDSProfileListAPI* Pointer to newly created instance.
    */
    static CNSmlDSProfileListAPI* NewL();
    /**
    * Two-phase (leave safe) constructor.
    * @return CNSmlDSProfileListAPI* Pointer to newly created instance.
    */
    static CNSmlDSProfileListAPI* NewLC();

   /**
    * Fetch an array of profile list items.
    * @return CArrayPtrFlat<CNSmlDSProfListItem>*& An array of CNSmlDSProfListItem instances.
    */
    virtual CArrayPtrFlat<CNSmlDSProfListItem>*& GetProfileListL();

    /**
    * Fetch an array of content types selected to the profile.
    * @param aId Id of the profile.
    * @return CArrayPtrFlat<CNSmlDSContentTypeItem>*& An array of CNSmlDSContentTypeItem instances.
    */
    virtual CArrayPtrFlat<CNSmlDSContentTypeItem>*& GetSelectedContentTypesL( TInt aId );
    

private:
    CNSmlDSProfileListAPI();
    void ConstructL();
    
    CArrayPtrFlat<CNSmlDSProfListItem>* iProfItemList;
    CArrayPtrFlat<CNSmlDSContentTypeItem>* iContentTypes;
    CNSmlDSProfileAPI* iProfileapi; 
    RLibrary iSrLib;
    };

/**
* Create a Profile List API instance.
* @return CNSmlDSProfileListAPI* Pointer to newly created instance.
*/
IMPORT_C CNSmlDSProfileListAPI* CreateDSProfileListAPIL();
typedef CNSmlDSProfileListAPI* ( *TNSmlCreateDSProfileListAPIFunc ) ();

#endif // __NSMLDSPROFILELISTAPI_H
