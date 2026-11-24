/*
* ============================================================================
*  Name     : CommonPhoneParser from CommonPhoneParser.h
*  Part of  : ?module_name (e.g. Continuus subproject name)
*
*  Description:
*   Class to parse phone numbers. All methods are static.
*
*  Copyright (C) 2002 Nokia Corporation.
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

#ifndef COMMONPHONEPARSER_H
#define COMMONPHONEPARSER_H

//  INCLUDES
#include    <coemain.h>


// CLASS DECLARATION

/**
* CommonPhoneParser
*
* The Common Phone Parser offers methods for parsing and 
* validating phone numbers. All methods are static.
*
* Note! There's two levels on validity. An example will probably
* square the matter best:
*
* Number for SMS (EPlainPhoneNumber) is valid if it contains (only) the
* following characters: "+1234567890()- ./" where space represents all 
* whitespaces. But it can be used for SMS sending only after parsing it 
* to containing characters: "+1234567890".
*
* Example:
*   
* @code
* TBuf<50> number1 = _L("+358 (40) 123 132");
* 
* TBool validNumber1 = 
* CommonPhoneParser::ParsePhoneNumber( number1,
*                                      CommonPhoneParser::EPlainPhoneNumber );
* // validNumber1 is ETrue;
* // number1 is "+35840123132"
* // SendSMS( number1 ) // etc..
* 
* TBuf<50> number2 = _L("+358 (40) 123p132"); // note 'p'
* 
* TBool validNumber2 = 
* CommonPhoneParser::ParsePhoneNumber( number2,
*                                      CommonPhoneParser::EPlainPhoneNumber );
* // validNumber2 is EFalse;
* // number2 is "+358-40w123p132" // unchanged
* @endcode
*
* @lib commonengine.lib
* @since Series S60 2.0
*/

class CommonPhoneParser
    {
    public:

        /**
        * Enumeration for phone number types
        */
        enum TPhoneNumberType
            {
            EPlainPhoneNumber,
            EContactCardNumber,
            EPhoneClientNumber,
			ESMSNumber
            };

        /**
        * Parse phone number
        *
        * If given Phone number is valid, method parses it and returns ETrue.
        *   If the number was not valid no parsing will be done, and method
        *   returns EFalse.
        *
        * @param aNumber Number which will be checked and parsed. Contains
        *                   parsed number after returning.
        * @param aType  Phone number type
        *
        * @return Returns ETrue if the number was valid and parsed.
        */
        IMPORT_C static TBool ParsePhoneNumber( TDes& aNumber, 
                                                TPhoneNumberType aType );

        /**
        * Check if string is a valid phone number
        *
        * @param aNumber Number which will be checked
        * @param aType  Phone number type
        *
        * @return ETrue if the number was valid
        */
        IMPORT_C static TBool IsValidPhoneNumber( const TDesC& aNumber,
                                                  TPhoneNumberType aType );
        
        /**
        * Check if string is a valid phone number
        *
        * @param aNumber Number which will be checked
        * @param aValidChars Chars that are valid for the number.
        *           Note! Some chars have special rules. See Find Item
        *           UI spec for more info.
        *
        * @return ETrue if the number was valid
        */
        static TBool IsValidPhoneNumber( const TDesC& aNumber,
                                         const TDesC& aValidChars);
        /**
        * Parses invalid characters from a string
        *
        * @param aNumber Number which will be parsed
        * @param aInvalidChars Characters that are invalid
        */
        static void ParseInvalidChars( TDes& aNumber,
                                       const TDesC& aInvalidChars);
    };

// COMMONPHONEPARSER_H
#endif
            
// End of File
