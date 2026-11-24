/*
* ==============================================================================
*  Name        : MPEngOPresenceIDData.h
*  Part of     : Presence API
*  Interface   : 
*  Description : 
*  Version     : 1.0
*
*  Copyright © 2003 Nokia Corporation.
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


#ifndef _MPENGOPRESENCEIDDTATA_H
#define _MPENGOPRESENCEIDDTATA_H

// FORWARD DECLARATIONS
class MPresenceAttribute;


/**
* This is M-interface for the CPresenceIDData class. The plugin is responsible 
* for creating the attributes but the client can access and modify them. 
* Also in some cases the client is responsible for destroying the objects.
*
* @since Series 60 2.1
*/

class MPresenceIDData
    {
    public:

        /**
        * Destructor
        * @since Series 60 2.1
        */
        virtual ~MPresenceIDData( ) { };

        /**
        * Method for getting the number of items in the container.
        *
        * @since Series 60 2.1
        * @return Number of items in the container
        */
        virtual TInt Count( ) const = 0;

        /**
        * Method for getting the nth item from the container.
        *
        * @since Series 60 2.1
        * @param aIndex Get nth item from the container
        * @return TContactItemId
        */
        virtual TContactItemId Id( const TInt aIndex ) const = 0;

        /**
        * Method for getting the status of the nth item in the container.
        *
        * @since Series 60 2.1
        * @param aIndex Get nth item
        * @return Status of the item
        */
        virtual TInt Status( const TInt aIndex ) const = 0;
    };


/**
* This is M-interface class for the MWVIdData. The plugin is responsible 
* for creating the attributes but the client can access them. 
*
* @since Series 60 2.1
*/

class MWVIdData
    {
    public:
        /**
        * Destructor
        *
        * @since Series 60 2.1
        */
        virtual ~MWVIdData( ) { };

        /**
        * Method for getting the textual user ID
        *
        * @since Series 60 2.1
        * @return TPtrC to the name
        */
        virtual TPtrC Name( ) const = 0;

        /**
        * Method for getting the number of attributes.
        *
        * @since Series 60 2.1
        * @return Number of attributes
        */
        virtual TInt NbrOfAttributes( ) const = 0;

        /**
        * Method for getting the nth attribute
        *
        * @since Series 60 2.1
        * @param aIndex Which attribute
        * @return pointer to MPresenceAttribute object
        */
        virtual const MPresenceAttribute* Attribute( TInt aIndex ) const = 0;

        /**
        * Method for getting the status of nth entry
        * @since Series 60 2.1
        * @param aIndex which entry
        * @return status of the entry
        */
        virtual TInt Status( ) const = 0;

    };

/**
* This is M-interface class for the CContactData. The plugin is responsible 
* for creating the attributes but the client can access them. 
*
* @since Series 60 2.1
*/

class MContactData
    {
    public:
        /**
        * Destructor
        *
        * @since Series 60 2.1
        */
        virtual ~MContactData( ) { };

        /**
        * Method for getting the TContactItemId of the entry
        *
        * @since Series 60 2.1
        * @return TContactItemId of the entry
        */
        virtual TContactItemId ContactId( ) const = 0;

        /**
        * Method for getting the status of nth entry
        * @since Series 60 2.1
        * @return status of the entry
        */
        virtual TInt Status( ) const = 0;

        /**
        * Method for getting the number of attributes.
        *
        * @since Series 60 2.1
        * @return Number of attributes
        */
        virtual TInt NbrOfAttributes( ) const = 0;

        /**
        * Method for getting the nth attribute
        *
        * @since Series 60 2.1
        * @param aIndex Which attribute
        * @return pointer to MPresenceAttribute object
        */
        virtual const MPresenceAttribute* Attribute( TInt aIndex ) const = 0;
    };


/**
* This is M-interface class for the CPresenceData. The plugin is responsible 
* for creating the attributes but the client can access and modify them. 
* Also in some cases the client is responsible for destroying the objects.  
*
* @since Series 60 2.1
*/

class MPresenceData
    {
    public:

        /**
        * Destructor
        * @since Series 60 2.1
        */
        virtual ~MPresenceData( ) { };

        /**
        * Method for counting the number of Contact based presencies.
        *
        * @since Series 60 2.1
        * @return number of presencies.
        */
        virtual TInt CountPresenceIds( ) const = 0;

        /**
        * Method for counting the number of Textual User Id based presencies.
        *
        * @since Series 60 2.1
        * @return number of presencies.
        */
        virtual TInt CountTextualIds( ) const = 0;

        /**
        * Method for getting the nth MContactData from the container.
        *
        * @since Series 60 2.1
        * @param aIndex which object.
        * @return MContactData object
        */
        virtual const MContactData* Contact( TInt aIndex ) const = 0;

        /**
        * Method for getting the nth MWVIdData from the container.
        *
        * @since Series 60 2.1
        * @param aIndex which object.
        * @return MWVIdData object
        */
        virtual const MWVIdData* TextualUser( TInt aIndex ) const = 0;
    };


#endif // _MPENGOPRESENCEIDDTATA_H
            
// End of File
