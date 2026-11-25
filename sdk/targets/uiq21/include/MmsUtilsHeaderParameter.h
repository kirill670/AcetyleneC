// $Workfile: MmsUtilsHeaderParameter.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 4 $
// $Date: 20/12/01 11:45 $
//

/** @file 
 * This file contains the interfaces for the CMmsUtilsHeaderParameter class.
 */


#ifndef __MMSUTILSHEADERPARAMETER_H__
#define __MMSUTILSHEADERPARAMETER_H__


#include <e32std.h>
#include "MmsUtils.h"   // TMmsVersion


// Forward declaration
class CMmsUtilsHeaderParameter;


// Typedef
typedef CArrayPtrSeg<CMmsUtilsHeaderParameter> CMmsUtilsHeaderParameterArray;


/**
 * MMS Parameter class.
 *
 * Provides the means to store and interrogate a header value parameter as described in the WAP WSP spec
 * (WAP-230-WSP-20010705-a, Approved Version 5-July-2001), section 8.4 (especially 8.4.2.3, 8.4.2.4, 8.4.2.6).
 *
 * Each object of this class will represent a single parameter, comprising a name and a value. The name is always
 * represented as text. The value is represented as one of a range of types defined by the TMmsParameterValueType enum.
 * Once a value has been set, it cannot be reset. Calling either a setter or a wrongly-typed getter on a previously set value
 * will result in a panic. The correct value type can be obtained by calling ValueType().
 */
class CMmsUtilsHeaderParameter : public CBase
    {
    public:
        /**
         * Enumerated values representing the different MMS parameter values.
         */
        enum TMmsParameterValueType
            {
            ENull = 0,      ///< Null value. This is the default value. A valid parameter may have a null value.
            EText,          ///< Text
            EInteger,       ///< Integer
            EDate,          ///< Date (expressed as epoch seconds)
            EDeltaSeconds,  ///< Delta seconds
            EQValue,        ///< Q-value
            EVersion,       ///< Version
            EUri            ///< URI
            };
    public:
        /**
         * Create and return a new parameter object.
         * @param aName The parameter name.
         * @return A new parameter object
         * @exception KErrXxx Standard EPOC error codes
         */
        IMPORT_C static CMmsUtilsHeaderParameter* NewL(const TDesC& aName);

        /**
         * Create and return a new parameter object. The object is placed on the cleanup stack before being returned.
         * @param aName The parameter name.
         * @return A new parameter object
         * @exception KErrXxx Standard EPOC error codes
         */
        IMPORT_C static CMmsUtilsHeaderParameter* NewLC(const TDesC& aName);

        /**
         * Create and return a new parameter object from a stream.
         * @param aReadStream An open read stream
         * @return A new parameter object
         * @exception KErrXxx Standard EPOC error codes
         */
        IMPORT_C static CMmsUtilsHeaderParameter* NewL(RReadStream& aReadStream);

        /**
         * Create and return a new parameter object from a stream. The object is placed on the cleanup stack before being returned.
         * @param aReadStream An open read stream
         * @return A new parameter object
         * @exception KErrXxx Standard EPOC error codes
         */
        IMPORT_C static CMmsUtilsHeaderParameter* NewLC(RReadStream& aReadStream);

        /**
         * C++ destructor
         */
        IMPORT_C ~CMmsUtilsHeaderParameter();

    public:
        /**
         * Set a text value on this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the parameter's value has already been set.
         * @param aValue A parameter value
         * @exception KErrXxx Standard EPOC error codes if a buffer cannot be allocated to store aValue.
         */
        IMPORT_C void SetTextValueL(const TDesC& aValue);

        /**
         * Set an integer value on this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the parameter's value has already been set.
         * @param aValue A parameter value
         */
        IMPORT_C void SetIntegerValue(TInt aValue);
        
        /**
         * Set a date value on this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the parameter's value has already been set.
         * @param aValue A parameter value
         */
        IMPORT_C void SetDateValue(TTime aValue);
        
        /**
         * Set a delta seconds value on this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the parameter's value has already been set.
         * @param aValue A parameter value
         */
        IMPORT_C void SetDeltaSecondsValue(TInt aValue);
        
        /**
         * Set a Q-value on this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the parameter's value has already been set.
         * @param aValue A parameter value
         */
        IMPORT_C void SetQValue(TInt16 aValue);
        
        /**
         * Set a version value on this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the parameter's value has already been set.
         * @param aValue A parameter value
         */
        IMPORT_C void SetVersionValue(TMmsVersion aValue);
        
        /**
         * Set a URI value on this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the parameter's value has already been set.
         * @param aValue A parameter value
         * @exception KErrXxx Standard EPOC error codes if a buffer cannot be allocated to store aValue.
         */
        IMPORT_C void SetUriValueL(const TDesC& aValue);


        /**
         * Get the name set for this parameter.
         * @return The parameter name
         */
        inline TPtrC Name() const;
        
        /**
         * Get the type of this parameter's value.
         * @return The parameter's value type
         */
        inline TMmsParameterValueType ValueType() const;

        
        /**
         * Get the text value set for this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the value has not yet been set, or has been set to a different type.
         * @return The parameter value
         */
        IMPORT_C TPtrC TextValue() const;
        
        /**
         * Get the integer value set for this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the value has not yet been set, or has been set to a different type.
         * @return The parameter value
         */
        IMPORT_C TInt IntegerValue() const;
        
        /**
         * Get the date value set for this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the value has not yet been set, or has been set to a different type.
         * @return The parameter value
         */
        IMPORT_C TTime DateValue() const;
        
        /**
         * Get the delta seconds value set for this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the value has not yet been set, or has been set to a different type.
         * @return The parameter value
         */
        IMPORT_C TInt DeltaSecondsValue() const;
        
        /**
         * Get the Q-value set for this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the value has not yet been set, or has been set to a different type.
         * @return The parameter value
         */
        IMPORT_C TInt16 QValue() const;
        
        /**
         * Get the version value set for this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the value has not yet been set, or has been set to a different type.
         * @return The parameter value
         */
        IMPORT_C TMmsVersion VersionValue() const;
        
        /**
         * Get the URI value set for this parameter.
         * @note This function will panic with <code>EMmsPanicHeaderParameterError</code> if the value has not yet been set, or has been set to a different type.
         * @return The parameter value
         */
        IMPORT_C TPtrC UriValue() const;

        /**
         * Externalizes the CMmsUtilsHeader to a stream.
         * @param aStream The stream to be written to
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         */
        IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;

        /**
         * Internalizes the CMmsUtilsHeader from a stream.
         * @param aStream The stream to be read from
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         */
        IMPORT_C void InternalizeL(RReadStream& aReadStream);

    private:
        /**
         * C++ constructor.
         */
        CMmsUtilsHeaderParameter();
        
        /**
         * 2nd phase constructor.
         * @param aName The parameter name.
         * @exception KErrXxx Standard EPOC error codes
         */
        void ConstructL(const TDesC& aName);

    private:
        TMmsParameterValueType iValueType;
        HBufC* iName;
        HBufC* iTextValue;
        TInt64 iInt64Value;
    };


#include "MmsUtilsHeaderParameter.inl"


#endif // __MMSUTILSHEADERPARAMETER_H__
