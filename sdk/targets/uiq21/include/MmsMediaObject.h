// $Workfile: mmsmediaobject.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 25 $
// $Date: 20/02/02 16:11 $
//

/** @file
 *  This file contains the definition of the CMmsMediaObject class.
 */


#ifndef __MMSMEDIAOBJECT_H__
#define __MMSMEDIAOBJECT_H__


// System includes
#include <e32std.h>
#include <badesca.h>	//CDesCArray
// User includes
#include "mmsutils.h"	//TMmsMediaObjectId
#include "MmsUtilsHeaderParameter.h"    // CMmsUtilsHeaderParameterArray


// Forward declarations
class CMmsUtilsHeaderArray;
class RWriteStream;
class RReadStream;


/**
 * This class represents a single media object. It does not contain the actual media object 
 * payload data; this is stored separately in a file. However, CMmsMediaObject contains the 
 * filename of this file, and hence the means of accessing it.
 */

class CMmsMediaObject : public CBase
	{
	public:
        /**
         * Get the ID of this media object.
         * @return The ID of this media object 
         */
		IMPORT_C TMmsMediaObjectId Id() const;

        /**
         * Get the URI of this media object from either the content-id or content-location headers.
         * Note that this function panics if there is no URI set
         *
         * @return The URI of this media object
         */
		IMPORT_C TPtrC URI() const;
        
        /**
         * Get the Filename of this media object.
         * @return The Filename of this media object
         */
		IMPORT_C TPtrC Filename() const;

        /**
         * Set the Filename of this media object.
         * @note This function is intentionally not exported.  Filenames are normally allocated by the media object list
         * @param aFilename The Filename of this media object
         * @exception KErrXXX Standard EPOC leave codes if no memory is available for the new filename value
         */
		void SetFilenameL(const TDesC& aFilename);
        
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
         * Remove the header with a given name.  
         * Note that if more than one value is stored for this header, all values will be removed.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if this media object
         * is set not to allow MIME headers.
         *
         * @param aHeaderName The name of the header to be removed
         * @retval KErrNone The MIME header was successfully deleted.
         * @retval KErrNotFound No MIME header was found with the name aHeaderName.
         */
		IMPORT_C TInt RemoveMimeHeader(const TDesC& aHeaderName);

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
         * Get Content-type header parameters.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if this media object
         * is set not to allow MIME headers.
         *
         * @return An array of parameters added for the Content-type header. This will be empty if none have been added.
         */
        IMPORT_C const CMmsUtilsHeaderParameterArray& ContentTypeParameters() const;
        
        /**
         * Remove all Content-type header parameters.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if this media object
         * is set not to allow MIME headers.
         */
        IMPORT_C void RemoveContentTypeParameters();

    public:
        /**
         * 2 phase constructor.  
         * This function creates a CMmsMediaObject object.
         * @param aURI The URI of the media object, added as a content-id header value
         * @param aFilename The filename of the media object
         * @param aId The ID of this media object
         * @param aAllowMIMEHeaders Specifies whether the user is allowed to set MIME headers for this object. This will typically not be the case for single-part MMS messages.
         * @exception KErrXXX Standard leave codes if no memory is available
         * @return The newly created CMmsMediaObject
         */
		static CMmsMediaObject* NewL(const TDesC& aURI, const TDesC& aFilename, TMmsMediaObjectId aId, TBool aAllowMIMEHeaders);

        /**
         * 2 phase constructor.  
         * This function creates a CMmsMediaObject object and puts it on the cleanup stack.
         * @param aURI The URI of the media object, added as a content-id header value
         * @param aFilename The filename of the media object
         * @param aId The ID of this media object
         * @param aAllowMIMEHeaders Specifies whether the user is allowed to set MIME headers for this object. This will typically not be the case for single-part MMS messages.
         * @exception KErrXXX Standard leave codes if no memory is available
         * @return The newly created CMmsMediaObject
         */
		static CMmsMediaObject* NewLC(const TDesC& aURI, const TDesC& aFilename, TMmsMediaObjectId aId, TBool aAllowMIMEHeaders);
     
        /**
         * 2 phase constructor.  
         * This function constructs a CMmsMediaObjectList and internalizes it from a stream
         * @param aReadStream The stream to internalize the object from
         * @exception KErrXXX Standard leave codes if no memory is available
         * @exception KErrXXX Standard stream leave codes if aStream is not opened or cannot be read from
         * @return The newly created CMmsMediaObject
         */
		static CMmsMediaObject* NewL(RReadStream& aReadStream);
        
        /**
         * 2 phase constructor.  
         * This function constructs a CMmsMediaObjectList, internalizes it from a stream, and puts it on the cleanup stack.
         * @param aReadStream The stream to internalize the object from
         * @exception KErrXXX Standard leave codes if no memory is available
         * @exception KErrXXX Standard stream leave codes if aStream is not opened or cannot be read from
         * @return The newly created CMmsMediaObject
         */
		static CMmsMediaObject* NewLC(RReadStream& aReadStream);

        /**
         * 2 phase constructor.  
         * This function creates a CMmsMediaObject object and puts it on the cleanup stack.
         * @note This method is only intended for use by the CMmsCodecMediaObjectCreator
         * @param aId The ID of this media object
         * @param aAllowMIMEHeaders Specifies whether the user is allowed to set MIME headers for this object. This will typically not be the case for single-part MMS messages.
         * @exception KErrXXX Standard leave codes if no memory is available
         * @return The newly created CMmsMediaObject
         */
		static CMmsMediaObject* NewL(TMmsMediaObjectId aId, TBool aAllowMIMEHeaders);
        
        /**
         * C++ destructor.
         */
		~CMmsMediaObject();

        /**
         * Externalizes CMmsMediaObject object to a stream.
         * @param aWriteStream The stream to be written to
         * @exception KErrXXX Standard EPOC stream leave codes
         */
        void ExternalizeL(RWriteStream& aWriteStream) const;

        /**
         * Internalizes the CMmsMediaObject object from a stream.
         * @param aReadStream The stream to be read from
         * @exception KErrNotSupported The stream was written by a previous version and its format is no longer supported
         * @exception KErrXXX Standard EPOC stream leave codes
         */
		void InternalizeL(RReadStream& aReadStream);
	
	private:
        /**
         * C++ constructor.
         * @param aId The media object ID of this object.
         */
		CMmsMediaObject(TMmsMediaObjectId aId);
        
        /**
         * 2nd phase constructor.
         * @param aURI The URI of the media object, added as a content-id header value
         * @param aFilename The filename of the media object
         * @param aAllowMIMEHeaders Specifies whether the user is allowed to set MIME headers for this object. This will typically not be the case for single-part MMS messages.
         * @exception KErrXXX Standard leave codes if no memory is available
         */
		void ConstructL(const TDesC& aURI, const TDesC& aFilename, TBool aAllowMIMEHeaders);

        /**
         * 2nd phase constructor.
         * @param aAllowMIMEHeaders Specifies whether the user is allowed to set MIME headers for this object. This will typically not be the case for single-part MMS messages.
         * @exception KErrXXX Standard leave codes if no memory is available
         */
        void ConstructL(TBool aAllowMIMEHeaders);
        
	private:
		TMmsMediaObjectId iId;			    ///<The media object's ID
		HBufC* iFilename;				    ///<The filename of the media object
        TBool iMimeHeadersAllowed;          ///< Are MIME headers allowed for this object
		CMmsUtilsHeaderArray* iMimeHeaders; ///<MIME headers that describe the media object are stored in this attribute
        CMmsUtilsHeaderParameterArray* iContentTypeParams; ///<Parameters associated with the content-type header

        mutable HBufC* iURI;                ///< Temporary member to hold a URI to be returned by URI()
	};

#endif //__MMSMEDIAOBJECT_H__