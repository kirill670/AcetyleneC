/*
* ==============================================================================
*  Name        : MPEngOPresenceAttributes.h
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


#ifndef _MPENGOPRESENCEATTRIBUTES_H
#define _MPENGOPRESENCEATTRIBUTES_H


/**
* TAttributeType contains the supported attributes.
*
* @since Series 60 2.1
*/
enum TAttributeType
    {
    EAttributeUserAvailability = 0,
    EAttributeStatusText = 1,
    EAttributeStatusContent = 2
    };

/**
* TAttributeUserAvailability contains the supported UserAvailability values
*
* @since Series 60 2.1
*/
enum TAttributeUserAvailability
    {
    EUsrAvailabilityOffline = 0, //default value
    EUsrAvailabilityDiscreet = 1,
    EUsrAvailabilityOnline = 2
    };


/**
* This is a M-interface class for presence attributes. The plugin is responsible 
* for creating the attributes but the client can access and modify them. 
* Also in some cases the client is responsible for destroying the objects.
*
* @since Series 60 2.1
*/

class MPresenceAttribute
    {
    public:

        /**
        * Destructor
        * @since Series 60 2.1
        */
        virtual ~MPresenceAttribute( ) { };

        /**
        * Method fot getting the qualifer value of the attribute.
        * The qualifier means weather the attribute is active or not.
        * @since Series 60 2.1
        */
        virtual TBool Qualifier( ) const = 0;

        /**
        * Method for getting the value of the attribute in UNICODE format
        * @since Series 60 2.1
        * @return value as unicode
        */
        virtual TPtrC ValueAsUnicode( ) const = 0;

        /**
        * Method for getting the type of the attribute
        * @since Series 60 2.1
        * @return Enum representing the type of the attribute
        */
        virtual TAttributeType AttributeType( ) const = 0;

        /**
        * Method for getting the value of the attribute integer.
        * Enum values are stored as integer values.
        * @since Series 60 2.1
        * @return value as integer
        */
        virtual TInt DataAsEnum( ) const = 0;

        /**
        * Method for setting the attributes validess.
        * @since Series 60 2.1
        * @param aValue If true this attribute is valid, if false it is not
        */
        virtual void SetQualifier( TBool aValue ) = 0;

        /**
        * Method for setting attributes value in UNICODE
        * @since Series 60 2.1
        * @param Value to be set
        */
        virtual void SetValueAsUnicodeL( const TDesC& aValue ) = 0;

        /**
        * Method for setting attributes value as integer
        * @since Series 60 2.1
        * @param Attribute value
        */
        virtual void SetDataAsEnum( TInt aValue ) = 0;
    };


#endif // _MPENGOPRESENCEATTRIBUTES_H
            
// End of File
