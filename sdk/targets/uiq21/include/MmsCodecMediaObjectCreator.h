// $Workfile: MmsCodecMediaObjectCreator.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Simonk $
// $Revision: 3 $
// $Date: 1/04/03 16:42 $
//

/** @file
 *  This file contains the definition of the CMmsCodecMediaObjectCreator class.
 */

#ifndef __MMSCODECMEDIAOBJECTCREATOR_H__
#define __MMSCODECMEDIAOBJECTCREATOR_H__


#include <e32std.h>
#include <e32base.h>	//CBase
#include <badesca.h>    //CDesCArray


//forward declarations
class CMmsMediaObject;
class CMmsMediaObjectList;
class CMmsUtilsHeaderArray;
class CMmsUtilsHeaderParameter;


/**
 * This class is used by the MMS server MTM's codec to add incoming media objects to the message.
 */
class CMmsCodecMediaObjectCreator : public CBase
    {
    // Exported public functions
    public:

        //
        // CMmsMediaObject API
        //

        /**
         * Add a MIME header value for a given header name.
         * Note that this may be called more than once with the same header name,
         * in which case a list of values will be stored for this name.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if this media object
         * is set not to allow MIME headers.
         *
         * @param aHeaderName The header name
         * @param aHeaderValue The header value
         * @exception KErrXXX Standard EPOC leave codes if no memory is available for the new header values
         */
		IMPORT_C void AddMimeHeaderL(const TDesC& aHeaderName, const TDesC& aHeaderValue);

        /**
         * Add an array of MIME header values.
         * Duplicate header values will be ignored, not added.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if this media object
         * is set not to allow MIME headers.
         *
         * @note
         * This function will panic with <code>EMmsPanicHeaderArraysIncompatible</code> if aHeaderArray is not set
         * to treat header names as case-sensitive.
         *
         * @param aHeaderArray An array of headers
         * @exception KErrXXX Standard EPOC leave codes if no memory is available for the new header values
         */
		IMPORT_C void AddMimeHeadersL(const CMmsUtilsHeaderArray& aHeaderArray);

        /**
         * Add a Content-type header parameter.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if this media object
         * is set not to allow MIME headers.
         *
         * @param aParameter The parameter to add. <b>Note that this object takes ownership of aParameter and will delete it.</b>
         * @exception KErrXxx Standard EPOC error codes if memory cannot be allocated for aParameter
         */
        IMPORT_C void AddContentTypeParameterL(CMmsUtilsHeaderParameter* aParameter);

        /**
         * Get the list of header values for a given header name.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if this media object
         * is set not to allow MIME headers.
         *
         * @param aHeaderName The header name
         * @exception KErrNotFound No values stored for the header name aHeaderName
         * @return An array of header values.
         */
		IMPORT_C const CDesCArray* MimeHeaderValuesL(const TDesC& aHeaderName);

        /**
         * Get the list of the header names that have been set. If no headers have been set the returned array will be empty.
         *
         * @note
         * This function will return an empty array if this media object has been set not to allow MIME headers.
         *
         * @exception KErrXxx Standard EPOC error codes
         * @return An array of header values.
         */
		IMPORT_C CDesCArray* MimeHeaderNamesLC();


        //
        // Other API
        //

        /**
         * Create a file for this media object.
         * @param aFileNameOrExtn Either a preferred filename (e.g. "test.txt") or just a preferred file extension (e.g. ".txt").
         *      If a preferred filename is specified, this will be used unless it clashes with a filename of an existing media
         *      object. In this case, a new filename will be generated with digits appended to the original filename base
         *      (e.g. test01.txt, test02.txt, etc.).
         *      If just a file extension is specified, a unique filename will be generated of the format 00000001.<extn>.
         *      Note that a string without a full stop (e.g. "test") will be interpreted as a filename with no extension, and used
         *      accordingly.
         * @return The filename generated for this object.
         * @exception KErrXxx Standard EPOC file error codes if the file cannot be created
         * @exception KErrAlreadyExists A file has already been created for the media object
         */
        IMPORT_C TPtrC CreateFileL(const TDesC& aFileNameOrExtn);

        /**
         * Commit this media object -- i.e. add it to the media object list.
         *
         * This function checks that the media object is in a consistent state:
         * i.e. that it has a file associated with it, and a URI (either a Content-Id
         * or a Content-Location header). It leaves if the media object is not
         * consistent, or cannot be added to the list.
         * @note If this function returns successfully, it will have deleted <code>this</code> (i.e. the CMmsCodecMediaObjectCreator object).
         * This is because a CMmsCodecMediaObjectCreator object can only be used once and is redundant once committed.
         * @note To prevent the deletion of a wild pointer, either call CleanupStack::Pop or set a pointer to this object to NULL after
         * calling this function
         * @exception KErrNotReady The media object is not in a consistent state and was not added to the media object list.
         * @exception KErrXxx Standard EPOC error codes.
         */
        IMPORT_C void CommitLD();

    // Non-exported public functions
    public:
        /**
         * 2-phase constructor. Creates a new CMmsCodecMediaObjectCreator object, places it on the cleanup stack, then returns it.
         * Non-exported as it is only called from CMmsMediaObjectList
         * @param aMediaObjectList A reference to the media object list which this media object will be added to
         * @param aIsRoot Is this object the root object?
         * @param aMultiPartMessage Is the owning message multipart?
         */
        static CMmsCodecMediaObjectCreator* NewLC(CMmsMediaObjectList& aMediaObjectList, TBool aIsRoot, TBool aMultiPartMessage);

        ~CMmsCodecMediaObjectCreator();

    private:
        CMmsCodecMediaObjectCreator(CMmsMediaObjectList& aMediaObjectList, TBool aIsRoot, TBool aMultiPartMessage);
        void ConstructL();

    private:
        CMmsMediaObject* iMediaObject;
        CMmsMediaObjectList& iMediaObjectList;
        HBufC* iFilename;
        const TBool iIsRoot;
        const TBool iMultiPartMessage;
    };


#endif // __MMSCODECMEDIAOBJECTCREATOR_H__
