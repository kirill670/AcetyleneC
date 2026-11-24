/*
* ============================================================================
*  Name     : FavouritesItem.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class CFavouritesItem.
*      
*  Version:
*
*  Copyright (C) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef FAVOURITES_ITEM_H
#define FAVOURITES_ITEM_H

//  INCLUDES

#include <e32base.h>
#include <FavouritesLimits.h>
#include <FavouritesWapAp.h>

// FORWARD DECLARATION

class CFavouritesItemImpl;
class RWriteStream;
class RReadStream;

// CLASS DECLARATION

/**
* Base class for representing one favourites entry (item or folder).
* Instances of this class are used to exchange data between the Favourites
* Engine and clients using it.
*/
class CFavouritesItem: public CBase
    {

    public:     // Data types

        enum TType  /// Type of an item (item or folder).
            {
            ENone,  ///< Invalid value, cannot be set for a CFavouritesItem.
            EItem,  ///< Favourites item.
            EFolder ///< Favourites folder.
            };

    public:     // Constructors and destructor
        
        /**
        * Two-phased constructor. Leaves on failure. Places the instance on the
        * cleanup stack.
        * @return The constructed item.
        */
        IMPORT_C static CFavouritesItem* NewLC();

        /**
        * Two-phased constructor. Leaves on failure.
        * @return The constructed item.
        */
        IMPORT_C static CFavouritesItem* NewL();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CFavouritesItem();

        /**
        * Assignment operator.
        * @param aCopyFrom Assign from this.
        */
        IMPORT_C CFavouritesItem& operator=
            ( const CFavouritesItem& aCopyFrom );

    public:     // Query

        /**
        * Get unique id of the item.
        * @return The unique id.
        */
        IMPORT_C TInt Uid() const;

        /**
        * Get the uid of the parent folder of this item.
        * @return The unique id of the parent folder.
        */
        IMPORT_C TInt ParentFolder() const;

        /**
        * Get type of the item (item or folder).
        * @return The type of the item. It is either EFolder or EItem
        * (never ENone).
        */

        IMPORT_C TType Type() const;

        /**
        * Get the name of this item.
        * @return The name of this item.
        */
        IMPORT_C const TPtrC Name() const;

        /**
        * Get the URL of this item.
        * @return The URL of this item.
        */
        IMPORT_C const TPtrC Url() const;

        /**
        * Get WAP Access Point id associated with this item.
        * @return The WAP Access Point id.
        */
        IMPORT_C TFavouritesWapAp WapAp() const;

        /**
        * Get the username associated with this item.
        * @return The username.
        */
        IMPORT_C const TPtrC UserName() const;

        /**
        * Get password associated with this item.
        * @return The password.
        */
        IMPORT_C const TPtrC Password() const;

        /**
        * Get context id associated with this item.
        * @return The context id.
        */
        IMPORT_C TInt32 ContextId() const;

        /**
        * Check if this is an item (not folder).
        * @return ETrue if this is an item.
        */
        IMPORT_C TBool IsItem() const;

        /**
        * Check if this is a folder.
        * @return ETrue if this is a folder.
        */
        IMPORT_C TBool IsFolder() const;

        /**
        * Check if this is a factory item.
        * @return ETrue if this is a factory item.
        */
        IMPORT_C TBool IsFactoryItem() const;

        /**
        * Check if this is a read-only in database. Note that ETrue value does
        * not prevent modifying this CFavouritesItem object.
        * @return ETrue if this is read-only in database.
        */
        IMPORT_C TBool IsReadOnly() const;

        /**
        * Get last modification time (of database entry), universal time.
        * This can be zero if:
        * - Last modification time is not available in database (old
        *   databases); or
        * - Engine does not support this feature.
        * Note that zero means Modified().Int64() == 0, and not
        * Time::NullTTime().
        */
        IMPORT_C TTime Modified() const;

    public:     // update

        /**
        * Reset the item to default values.
        */
        IMPORT_C void ClearL();

        /**
        * Set parent folder.
        * @param aId The unique id of the parent folder.
        */
        IMPORT_C void SetParentFolder( TInt aId );

        /**
        * Set item type (item or folder).
        * @param aType The type to be set. ENone cannot be set (if that is
        * specified, it is ignored).
        */
        IMPORT_C void SetType( TType aType );

        /**
        * Set name of the item. Leading or trailing whitespace is trimmed.
        * Length limit is KFavouritesMaxName (leaves with KErrOverflow).
        * @param aName The name to be set.
        */
        IMPORT_C void SetNameL( const TDesC& aName );

        /**
        * Set URL of the item.
        * Length limit is KFavouritesMaxURL (leaves with KErrOverflow).
        * @param aUrl The URL to be set.
        */
        IMPORT_C void SetUrlL( const TDesC& aUrl );

        /**
        * Set WAP Access Point of the item.
        * @param aAccessPoint The WAP Access point to be set.
        */
        IMPORT_C void SetWapAp( const TFavouritesWapAp& aAccessPoint );

        /**
        * Set username of the item.
        * Length limit is KFavouritesMaxUserName (leaves with KErrOverflow).
        * @param aUserName The username to be set.
        */
        IMPORT_C void SetUserNameL( const TDesC& aUserName );

        /**
        * Set password.
        * Length limit is KFavouritesMaxPassword (leaves with KErrOverflow).
        * @param aPassword The password to be set.
        */
        IMPORT_C void SetPasswordL( const TDesC& aPassword );

        /**
        * Set context id of the item.
        * @param aContextId The context id to be set.
        */
        IMPORT_C void SetContextId( TInt32 aContextId );

    public:     // (But not exported:) Streaming

        /**
        * Externalize into a stream.
        * @param aStream The stream to externalize to.
        */
        void ExternalizeL( RWriteStream& aStream ) const;

        /**
        * Internalize from a stream.
        * @param aStream The stream to externalize from.
        */
        void InternalizeL( RReadStream& aStream );

    private:    // Constructors
        
        /**
        * C++ constructor.
        */
        CFavouritesItem();

        /**
        * Second-phase constructor.
        */
        void ConstructL();

    private:    // Data

        CFavouritesItemImpl* iImpl; ///< Implementation. Owned.

    private:    // friends

        // Setting UID and accessing implementation is granted to this.
        friend class RFavouritesDb;

    };

#endif
            
// End of File
