// $Workfile: MmsAddressParser.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 6 $
// $Date: 15/11/01 17:27 $
//


/** @file
 *  This file contains the interface for the MmsAddressParser class.
 */


#ifndef __MMSADDRESSPARSER_H__
#define __MMSADDRESSPARSER_H__


#include <e32std.h>
#include <badesca.h>    // CDesCArray


/**
 * A class for validating potential MMS addresses.
 * MMS messages can be addressed using a range of addressing schemes.
 * This class reports whether or not a string represents a valid address, and
 * if so for what scheme.
 */
class MmsAddressParser
    {
    public:
        /**
         * Enumerated type listing the various acceptable MMS addressing schemes.
         */
        enum TMmsAddressType
            {
            EInvalid,           ///< Invalid MMS address
            EIPv4Address,       ///< IPv4 address
            EIPv6Address,       ///< IPv6 address
            EGlobalPhoneNumber, ///< Global phone number
            ERfc822Address      ///< RFC822 email address
            };
    public:
        /**
         * Check if a string constitutes a valid MMS address.
         *
         * @note
         * Validation is <i>extremely</i> basic in the current version.
         * @li <b>IPv4</b> validation checks for four numbers separated by dots, where each number is a decimal integer in the range 0..255.
         * @li <b>IPv6</b> validation checks for eight numbers separated by colons, where each number is a hexadecimal integer in the range 0x0000..0XFFFF.
         * @li <b>Global phone number</b> validation checks for a + symbol followed by a single, unbroken string of numeric digits.
         * @li <b>RFC822</b> validation checks for two parts separated by an @ symbol.
         *
         * @param aString The string to check
         * @return The type of MMS address contained in aString, if valid. Otherwise <code>EInvalid</code>.
         */
        IMPORT_C static TMmsAddressType ValidateAddress(const TDesC& aString);

    private:
        /**
         * Check if a string constitutes a valid MMS address.
         * This is a private, leaving function which is called and trapped in ValidateAddress().
         *
         * @param aString The string to check
         * @return The type of MMS address contained in aString, if valid. Otherwise <code>EInvalid</code>.
         * @exception KErrXxx Standard EPOC error codes
         */
        static TMmsAddressType ValidateAddressL(const TDesC& aString);
        /**
         * Verify whether aString constitutes a valid IPv4 address (e.g. <i>195.224.64.203</i> or <i>127.0.0.1</i>).
         * 
         * @note
         * In the current version this does not do a full IPv4 address validation: it simply verifies that aString consists of four
         * numbers separated by dots, where each number is a decimal integer in the range 0..255.
         *
         * @param aString The string to validate.
         * @retval ETrue aString constitutes a valid IPv4 address.
         * @retval EFalse aString does not constitute a valid IPv4 address.
         * @exception KErrXxx Standard EPOC error codes if the array used internally for parsing cannot be allocated.
         */
        static TBool IsValidIPv4AddressL(const TDesC& aString);
        /**
         * Verify whether aString constitutes a valid IPv6 address (e.g. <i>FEDC:BA98:7654:3210:FEDC:BA98:7654:3210</i> or <i>1080:0:0:0:8:800:200C:417A</i>).
         *
         * @note
         * In the current version this does not do a full IPv6 address validation: it simply verifies that aString consists of eight
         * numbers separated by colons, where each number is a hexidecimal integer in the range 0x0000..0xffff.
         *
         * @param aString The string to validate.
         * @retval ETrue aString constitutes a valid IPv6 address.
         * @retval EFalse aString does not constitute a valid IPv6 address.
         * @exception KErrXxx Standard EPOC error codes if the array used internally for parsing cannot be allocated.
         */
        static TBool IsValidIPv6AddressL(const TDesC& aString);
        /**
         * Verify whether aString constitutes a valid global phone number (e.g. "+441223719800").
         *
         * @note
         * In the current version this does not do a full global phone number validation: it simply verifies that aString
         * consists of a + symbol followed by a single, unbroken string of numeric digits.
         *
         * @param aString The string to validate.
         * @retval ETrue aString constitutes a valid global phone number.
         * @retval EFalse aString does not constitute a valid global phone number.
         */
        static TBool IsValidGlobalPhoneNumber(const TDesC& aString);
        /**
         * Verify whether aString constitutes a valid RFC822 address (e.g. "somebody@something.com").
         *
         * @note
         * In the current version this does <i>extremely</i> basic validation: it simply verifies that aString
         * consists of two parts separated by an @ symbol.
         *
         * @param aString The string to validate.
         * @retval ETrue aString constitutes a valid RFC822 address.
         * @retval EFalse aString does not constitute a valid RFC822 address.
         * @exception KErrXxx Standard EPOC error codes if the array used internally for parsing cannot be allocated.
         */
        static TBool IsValidRfc822AddressL(const TDesC& aString);
        /**
         * Splits a string at every occurrence of a separator character, appending the tokens (the parts between the separators) to an array.
         * Note that the separator character is not present in the tokens added to the array.
         * Also note that if the separator occurs twice concurrently in the string, this will result in
         * a zero-length substring in the array.
         *
         * @param aString The string to be split
         * @param aSeparator The character to split on
         * @param aPartsArray The array which will be populated by this function
         * @retval KErrNotFound aSeparator is not found in aString
         * @retval KErrNone The function completed successfully
         * @exception KErrXxx Standard EPOC error codes if the descriptor array cannot be appended to.
         */
        static TInt SplitStringL(const TDesC& aString, TChar aSeparator, CDesCArray& aPartsArray);
    };


#endif // __MMSADDRESSPARSER_H__
