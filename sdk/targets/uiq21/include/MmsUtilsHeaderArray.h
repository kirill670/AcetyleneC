// $Workfile: MmsUtilsHeaderArray.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 13 $
// $Date: 6/02/02 11:46 $
//

/** @file 
 * This file contains the interfaces for the CMmsUtilsHeaderArray and CMmsUtilsHeader classes.
 */


#ifndef __MMSUTILSHEADERARRAY_H__
#define __MMSUTILSHEADERARRAY_H__

#include <e32std.h>
#include <e32base.h>    //CArrayPtrSeg
#include <badesca.h>    //CDesCArray


// Forward declarations
class RWriteStream;
class RReadStream;


/**
 * CMmsUtilsHeaderArray represents a collection of headers, where each header is a name and 1 or more values.
 * It is suitable for storing, for example, RFC822 or MIME headers.
 *
 * @note
 * Header <b>values</b> are <i>always</i> treated as case-sensitive.
 * Whether header <b>names</b> are treated as case-sensitive is controlled by the aHeaderNamesCaseSensitive flag passed to the constructor.
 */
class CMmsUtilsHeaderArray : public CBase
    {
    public:
        /**
         * 2-phase constructor
         *
         * @param aHeaderNamesCaseSensitive Specifies whether header names should be considered case-sensitive.
         *      If ETrue, "Content-Type" and "content-type" will be considered different headers.
         *      If EFalse, they will be considered the same.
         * @exception KErrXxx Leaves if an out-of-memory condition occurs.
         * @return returns a newly created CMmsUtilsHeaderArray
         */
        IMPORT_C static CMmsUtilsHeaderArray* NewL(TBool aHeaderNamesCaseSensitive);

        /**
         * 2-phase constructor
         *
         * @exception KErrXxx Leaves if an out-of-memory condition occurs.
         * @param aHeaderNamesCaseSensitive Specifies whether header names should be considered case-sensitive.
         *      If ETrue, "Content-Type" and "content-type" will be considered different headers.
         *      If EFalse, they will be considered the same.
         * @return returns a newly created CMmsUtilsHeaderArray, left on the cleanup stack
         */
        IMPORT_C static CMmsUtilsHeaderArray* NewLC(TBool aHeaderNamesCaseSensitive);
        
        /**
         * C++ destructor
         */
        IMPORT_C ~CMmsUtilsHeaderArray();

        /**
         * Get a list of header values for this header name.
         *
         * @param aHeaderName The header name to look up
         * @exception KErrNotFound No values are stored for aHeaderName
         * @return A list of header values stored for aHeaderName
         */
        IMPORT_C const CDesCArray* HeaderValuesL(const TDesC& aHeaderName);

        /**
         * Get a list of header values for this header name.
         *
         * Note that this function will panic with <code>EMmsPanicNoValuesForHeaderName</code> if no values are stored for aHeaderName.
         * It should therefore only be called after first calling HeaderValuesExist.
         * Otherwise you should call the leaving function HeaderValuesL.
         *
         * @param aHeaderName The header name to look up
         * @return A list of header values stored for aHeaderName
         */
        IMPORT_C const CDesCArray* HeaderValues(const TDesC& aHeaderName);

        /**
         * Add a single header value by name.
         * If values are already stored for the header name aHeaderName, this will add aHeaderValue to that list.
         * Otherwise it will create a new header.
         * Duplicate header values are ignored, not added.
         *
         * @param aHeaderName The header name for which the value is being added (e.g. "Content-Type")
         * @param aHeaderValue The value being added for this header (e.g. "text\plain")
         * @exception KErrXxx Leaves if sufficient memory cannot be allocated to store the new header
         */
        IMPORT_C void AddHeaderValueL(const TDesC& aHeaderName, const TDesC& aHeaderValue);

        /**
         * Add an array of header values by name.
         * If values are already stored for the header name aHeaderName, this will add aHeaderValues to that list.
         * Otherwise it will create a new header.
         *
         * @param aHeaderName The header name for which the value is being added
         * @param aHeaderValues An array of values to add for this header
         * @exception KErrXxx Leaves if sufficient memory cannot be allocated to store the new header
         */
        IMPORT_C void AddHeaderValuesL(const TDesC& aHeaderName, const CDesCArray& aHeaderValues);

        /**
         * Add several header values by name.
         * Each header in the array will be added as described by AddHeaderValueL.
         * Note that header values which already exist will be ignore, not duplicated.
         *
         * @note
         * This function will panic with <code>EMmsPanicHeaderArraysIncompatible</code> if the array being added
         * treats header names as case sensitive and this one does not, or vice versa.
         *
         * @param aHeaderArray An array of headers to add to this one.
         * @exception KErrXxx Leaves if sufficient memory cannot be allocated to store the new header
         */
        IMPORT_C void AddHeaderArrayL(const CMmsUtilsHeaderArray& aHeaderArray);

        /**
         * Remove a header by name.
         * This will remove the header, including all of its values.
         *
         * @param aHeaderName The name of the header to be removed (e.g. "Content-Type")
         * @retval KErrNotFound No header exists with the name specified in aHeaderName
         * @retval KErrNone A header with the name specified in aHeaderName was found.
         */
        IMPORT_C TInt RemoveHeader(const TDesC& aHeaderName);

        /**
         * Get the list of the header names that have been set and pushes them to the cleanup stack
         * @exception KErrXXX Leaves with standard EPOC leave codes if memory can't be allocated for the array of header names, if pushing to the cleanup stack fails and if appending to the array fails
         * @return An array of header names
         */
		IMPORT_C CDesCArray* HeaderNamesLC();

        /**
         * Have header values been set for a header name?
         * If this function returns true, HeaderValuesL() can safely be called for aHeaderName.
         * @param aHeaderName A header name (e.g. "content-type")
         * @retval ETrue Values have been added for this header name
         * @retval EFalse No values have been added for this header name
         * @exception KErrXxx Standard EPOC error codes
         */
        IMPORT_C TBool HeaderValuesExist(const TDesC& aHeaderName) const;

        /**
         * Query whether this array treats headers names as case sensitive
         * @retval ETrue Header names are case sensitive (e.g. "fred" is distinct from "FRED")
         * @retval EFalse Header names are case insensitive (e.g. "fred", "Fred" and "FRED" are equivalent)
         */
        inline TBool AreHeaderNamesCaseSensitive() const;

        /**
         * Externalizes the CMmsUtilsHeaderArray to a stream.
         *
         * @param aStream The stream to be written to
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         */
        IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
        /**
         * Internalizes the CMmsUtilsHeaderArray from a stream.
         *
         * @param aStream The stream to be read from
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         */
        IMPORT_C void InternalizeL(RReadStream& aReadStream);

    private:
        /**
         * 2nd phase constructor
         *
         * @exception KErrXxx Leaves if an out-of-memory condition occurs.
         */
        void ConstructL();

        /**
         * C++ constructor
         *
         * @param aHeaderNamesCaseSensitive Specifies whether header names should be considered case-sensitive.
         *      If ETrue, "Content-Type" and "content-type" will be considered different headers.
         *      If EFalse, they will be considered the same.
         */
        CMmsUtilsHeaderArray(TBool aHeaderNamesCaseSensitive);

        /**
         * Get the index of a header by supplying its name.
         * @return Index of the matching header
         * @retval KErrNotFound The header does not exist
         */
        TInt HeaderByName(const TDesC& aHeaderName);

        /**
         * Compares two header names according to the current value of iHeaderNamesCaseSensitive.
         *
         * This is a convenience function that calls either TDesC::Compare() or TDesC::CompareF()
         * depending on the value of iHeaderNamesCaseSensitive.
         *
         * @param aName1 One of the names to compare
         * @param aName2 The other name to compare
         * @return The same values as returned by the TDesC::Compare() API.
         */
        inline TInt CompareHeaderNames(const TDesC& aName1, const TDesC& aName2) const;

        /**
         * Finds a header by name and returns its index, or KErrNotFound.
         *
         * @param aHeaderName The header name to find
         * @return The index of the header if found, otherwise KErrNotFound.
         */
        TInt FindHeaderByName(const TDesC& aHeaderName) const;

    private:
        // Private member class
        class CMmsUtilsHeader : public CBase
            {
            public:
                /**
                 * 2-phase constructor
                 *
                 * @param aHeaderName The name for this header (e.g. "content-type")
                 * @param aHeaderValue A value for this header (e.g. "text\plain")
                 * @exception KErrXXX Leaves if an out-of-memory condition occurs.
                 */
                static CMmsUtilsHeader* NewL(const TDesC& aHeaderName, const TDesC& aHeaderValue);
                /**
                 * 2-phase constructor
                 *
                 * @param aHeaderName The name for this header (e.g. "content-type")
                 * @param aHeaderValue A value for this header (e.g. "text\plain")
                 * @exception KErrXXX Leaves if an out-of-memory condition occurs.
                 */
                static CMmsUtilsHeader* NewLC(const TDesC& aHeaderName, const TDesC& aHeaderValue);
                /**
                 * C++ destructor
                 */
                ~CMmsUtilsHeader();
                
                /**
                 * Get the header name for this header.
                 *
                 * @return The header name.
                 */
                TPtrC HeaderName();
                /**
                 * Get a list of header values stored for this header.
                 *
                 * @return The list of header values.
                 */
                const CDesCArray* HeaderValues();
                /**
                 * Add a value for this header.
                 * Note that if aHeaderValue is already in the values array it will not be added again.
                 *
                 * @param aHeaderValue The value to add
                 * @exception KErrXXX Leaves if a buffer cannot be allocated for the new value
                 */
                void AddHeaderValueL(const TDesC& aHeaderValue);

                /**
                 * Externalizes the CMmsUtilsHeader to a stream.
                 *
                 * @param aStream The stream to be written to
                 * @exception KErrXXX Leaves with standard EPOC stream leave codes
                 */
                void ExternalizeL(RWriteStream& aStream) const;
                /**
                 * Internalizes the CMmsUtilsHeader from a stream.
                 *
                 * @param aStream The stream to be read from
                 * @exception KErrXXX Leaves with standard EPOC stream leave codes
                 */
                void InternalizeL(RReadStream& aStream);

            private:
                /**
                 * C++ constructor
                 * Does nothing
                 */
                CMmsUtilsHeader();
                /**
                 * 2nd phase constructor
                 *
                 * @param aHeaderName The name for this header (e.g. "content-type")
                 * @param aHeaderValue A value for this header (e.g. "text\plain")
                 * @exception KErrXXX Leaves if an out-of-memory condition occurs.
                 */
                void ConstructL(const TDesC& aHeaderName, const TDesC& aHeaderValue);
                
            private:
                HBufC* iHeaderName;         ///< The name of this header (e.g. "Content-type")
                CDesCArray* iHeaderValues;  ///< The value(s) for this header
            };

    private:
        CArrayPtrSeg<CMmsUtilsHeader>* iHeaders;    ///< The array containing the CMmsUtilsHeader objects
        TBool iHeaderNamesCaseSensitive;    ///< Flag that determines whether header names should be treated as case sensitive
    };


#include "MmsUtilsHeaderArray.inl"


#endif // __MMSUTILSHEADERARRAY_H__