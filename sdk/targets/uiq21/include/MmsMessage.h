// $Workfile: MmsMessage.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 33 $
// $Date: 26/02/02 17:45 $
//


/** @file
 *  This file contains the interface for the CMmsMessage class.
 */


#ifndef __MMSMESSAGE_H__
#define __MMSMESSAGE_H__


// System includes
#include <e32base.h>
#include <badesca.h> //CDesCArray
// User includes
#include "MmsUtils.h"           //TMsvMmsEntry, TMmsSenderVisibility, TMmsMessageClass 
#include "MmsHeaders.h"         // CMmsHeaders
#include "MmsMediaObjectList.h" // CMmsMediaObjectList


//forward declarations
class CMmsMediaObject;



/**
 * Class to represent an MMS message.
 * 
 * This is an abstract base class. Client-side users should use the CMmsClientMessage class.
 * The Server MTM provides a derived class for server-side use.
 * 
 * This class provides the main APIs required to manipulate an MMS message.
 * The Headers() methods can be used to obtain the message's CMmsHeaders object, through
 * which header values can be set and obtained.
 * 
 * This class also provides APIs for manipulating the message's Media Object List, i.e.
 * its multimedia message parts, including the presentation part (if present). Note that media objects
 * are referenced by ID, and it is the responsibility of the user to maintain a list of IDs
 * of a message's media objects. A media object may be retrieved (and hence manipulated)
 * and deleted by specifying its ID.
 */
class CMmsMessage : public CBase
    {
    public:
        /**
         * C++ destructor
         */
        IMPORT_C ~CMmsMessage();

        /**
         * Get the messaging index entry associated with this message.
         *
         * @return A const reference to a TMsvEntry associated with this message.
         */
        virtual const TMsvMmsEntry& Entry() const = 0;

        /**
         * Get the number of pages of the current message.
         * <b>N.B. This method is unsupported in the current version and will always return KErrNotSupported.</b>
         *
         * @retval KErrNotSupported This API is provided for future source compatibility, but is not implemented in the current release.
         */
        IMPORT_C TInt NumberOfPages() const;
        /**
         * Set the number of pages of the current message.
         * <b>N.B. This method is unsupported in the current version and does nothing.</b>
         *
         * @param aNumberOfPages This value is ignored in the current version.
         */
        IMPORT_C void SetNumberOfPages(TInt aNumberOfPages);

        /**
         * Get the headers object for this message.
         *
         * @return A modifiable reference to this message's headers object.
         */
        IMPORT_C CMmsHeaders& Headers();
        /**
         * Get the headers object for this message.
         *
         * @return A const reference to this message's headers object.
         */
        IMPORT_C const CMmsHeaders& Headers() const;

        //
        // Media object API
        //
        /**
         * Creates a new media object for this message and sets its MIME Content-type header if aMimeType is specified.
         *
         * Note that no object data is passed in to this function. The returned CMmsMediaObject object
         * specifies the name of a file which the object data should be written to. Other
         * characteristics of the media object (e.g. MIME headers) should be set using the APIs
         * on the returned CMmsMediaObject object.
         * 
         * @note
         * Client code should generally use this version of the function, and not the overload (which specifies a URI explicitly).<br>
         * <b>Client code should provide both a MIME type and a file extension suitable for the object being
         * created.</b> If either of these parameters is specified as a zero-length descriptor they will
         * be accepted, but there is a serious risk that a receiving device will not be able to use the media object.
         * This is because MMS clients may use either or both of these to determine the object's type.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if an attempt is made to add
         * a second media object to a message whose MIME category is set to <code>EMmsSinglePart</code>.
         *
         * @param aIsRoot Boolean to indicate whether or not this object is intended to be the root object
         * @param aMimeType A MIME content type for the object (e.g. "image/jpeg")
         * @param aFileNameOrExtn Either a preferred filename (e.g. "test.txt") or just a preferred file extension (e.g. ".txt").
         *      If a preferred filename is specified, this will be used unless it clashes with a filename of an existing media
         *      object. In this case, a new filename will be generated with digits appended to the original filename base
         *      (e.g. test01.txt, test02.txt, etc.).
         *      If just a file extension is specified, a unique filename will be generated of the format 00000001.<extn>.
         *      Note that a string without a full stop (e.g. "test") will be interpreted as a filename with no extension, and used
         *      accordingly.
         * @exception KErrArgument A file extension specified in aFileNameOrExtn contains wildcards ("*").
         * @exception KErrXXX Standard EPOC leave codes if no memory is available
         * @return A reference to the newly created media object
         */
        IMPORT_C CMmsMediaObject& CreateMediaObjectL(TBool aIsRoot, const TDesC& aMimeType, const TDesC& aFileNameOrExtn);
        /**
         * Creates a new media object for this message.
         *
         * Note that no object data is passed in to this function. The returned CMmsMediaObject object
         * specifies the name of a file which the object data should be written to. Other
         * characteristics of the media object (e.g. MIME headers) should be set using the APIs
         * on the returned CMmsMediaObject object.
         *
         * @note
         * This version of the function is for use primarily by clients which generate messages using
         * a SMIL template (i.e. where object URIs are already defined). Client code which generates messages dynamically
         * should generally use the overloaded version which takes a MIME type and file name/extension.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if an attempt is made to add
         * a second media object to a message whose MIME category is set to <code>EMmsSinglePart</code>.
         *
         * @param aIsRoot Boolean to indicate whether or not this object is intended to be the root object
         * @param aURI The URI of this media object, as given in the received message.
         * @exception KErrAlreadyExists The URI aURI is already in the list
         * @exception KErrXXX Standard EPOC leave codes if no memory is available
         * @return A reference to the newly created media object
         */
		IMPORT_C CMmsMediaObject& CreateMediaObjectL(TBool aIsRoot, const TDesC& aURI);
        /**
         * Creates and returns a CMmsCodecMediaObjectCreator, which encapsulates the deferred creation of the
         * components of a media object. The returned object has been pushed onto the cleanup stack.
         *
         * @note
         * This function is for use ONLY by the MMS decoder in the server MTM, where the URI
         * of an incoming media object is not already known.
         *
         *
         * @param aIsRoot Boolean to indicate whether or not this object is intended to be the root object
         * @exception KErrXXX Standard EPOC leave codes if no memory is available
         * @return A pointer to the newly created media object creator
         */
        IMPORT_C CMmsCodecMediaObjectCreator* CreateCodecMediaObjectLC(TBool aIsRoot);
        /**
         * Removes the media object identified by aId.
         * The file associated with the media objects will also be removed.
         * Note: The implications of calling this function whilst iterating through
         * all media objects using the iterator API is undefined.
         *
         * @param aId ID of the object to remove.
         * @retval KErrNone The object was successfully deleted.
         * @retval KErrNotFound No object was found with the ID aId.
         */
		IMPORT_C TInt RemoveMediaObject(TMmsMediaObjectId aId);
        /**
         * Returns the number of media objects in the current message.
         *
         * @return The number of media objects in the current message
         */
		IMPORT_C TInt MediaObjectCount() const;
        /**
         * Returns the ID of the object with the URI aURI.
         *
         * @param aURI URI of the object whose ID is requested.
         * @retval TMmsMediaObjectId The ID of the object with URI aURI if found
         * @retval KMmsNullMediaObjectId A match could not be made
         */
		IMPORT_C TMmsMediaObjectId MediaObjectIdFromURI(const TDesC& aURI) const;
        /**
         * Returns a reference to a media object owned by the media object list.
         *
         * @param aId ID of the requested object
         * @return A reference to the requested object
         * @exception KErrNotFound No object could be found matching this ID
         */
		IMPORT_C CMmsMediaObject& MediaObjectL(TMmsMediaObjectId aId);
        /**
         * Get the ID of the root entry, if set (typically the presentation part of a message).
         *
         * @retval TMmsMediaObjectId The ID of the root entry
         * @retval KMmsNullMediaObjectId The root ID has been set
         */
		IMPORT_C TMmsMediaObjectId MediaObjectRootId() const;
        /**
         * Along with MediaObjectIteratorHasNext() and MediaObjectIteratorGetNext(), this provides
         * a simple iterator interface for sequentially accessing all objects owned by a message.
         * This method must be called prior to using the other iterator methods, to ensure correct iteration through all media objects.
         * Example usage is as follows:
         * @code
         * // assuming CMmsMessage* msg
         * msg->MediaObjectIteratorStart();
         * while (msg->MediaObjectIteratorHasNext())
         *    {
         *    CMmsMediaObject& obj = msg->MediaObjectIteratorGetNext();
         *    //...
         *    }
         * @endcode
         */
		IMPORT_C void MediaObjectIteratorStart();
        /**
         * Call to check whether there are still media objects to iterate through.
         *
         * @retval ETrue There are further media objects to iterate through.
         * @retval EFalse There are no further media objects to iterate through (i.e. if the previous call to MediaObjectIteratorGetNext() returned the last object in the message).
         */
		IMPORT_C TBool MediaObjectIteratorHasNext() const;
        /**
         * Call to get the next object in the message.
         * N.B. Client should call MediaObjectIteratorHasNext() prior to calling this function, as it will panic if at the end of the list.
         *
         * @return A reference to the next object in the message.
         */
		IMPORT_C CMmsMediaObject& MediaObjectIteratorGetNext();

        /**
         * Set this message's MIME category.
         * @note
         * This function will panic with EMmsPanicMIMECategoryViolation if this message's MIME category has previously been set to a different value.
         * @param aMimeCategory The MIME category for this message
         */
        IMPORT_C void SetMimeCategory(TMmsMessageMIMECategory aMIMECategory);
        /**
         * Get this message's MIME category.
         * @return The MIME category for this message
         */
        IMPORT_C TMmsMessageMIMECategory MimeCategory() const;

    protected:
        /**
         * Pure virtual function.
         * Derived classes must implement this to provide the path of the associated
         * messaging entry's file directory, as returned by <code>CMsvEntry::GetFilePath()</code>
         * and <code>CMsvServerEntry::GetFilePath()</code>
         * 
         * @param aEntryDir Will contain the file directory name when this function returns
         * @exception KErrXxx General EPOC leave codes if the call to
         * <code>CMsvEntry::GetFilePath()</code>/<code>CMsvServerEntry::GetFilePath()</code> leaves.
         */
        virtual void EntryDirectoryL(TFileName& aEntryDir) const = 0;

    protected:
        /**
         * C++ constructor.
         */
        IMPORT_C CMmsMessage();

        /**
         * 2nd phase constructor.
         *
         * Constructs the iHeaders and iMediaObjectList objects.
         * Note that this function calls EntryDirectory() which must be implemented by the derived class.
         * Hence the derived class must do any necessary construction to allow this to be called BEFORE calling the base class ConstructL.
         *
         * @exception KErrXxx Standard EPOC leave codes if an error occurs during construction.
         */
        IMPORT_C void ConstructL();

        /**
         * Store this message to a message entry store.
         * Also updates the TMsvMmsEntry for this message, but does not save it.
         * Saving the TMsvMmsEntry is the responsibility of derived classes, as it will use client/server-specific code.
         *
         * @param aStore The message entry store.
         * @exception KErrAccessDenied aStore is not opened for editing
         * @exception KErrXxx Standard EPOC stream leave codes
         */
        IMPORT_C void StoreMessageL(CMsvStore& aStore);
        /**
         * Restore this message from a message entry store.
         *
         * @param aStore The message entry store.
         * @exception KErrXxx Standard EPOC stream leave codes if an error occurs opening or reading from the store.
         */
        IMPORT_C void RestoreMessageL(const CMsvStore& aStore);

        /**
         * Updates a local (copy of an) index entry to contain data set on this MMS message, such as subject, priority, etc.
         * @note
         * This function does <b>not</b> commit the index entry to the messaging index. This should be done by the calling code as required.
         * @param aIndexEntry An index entry to be updated.
         */
        IMPORT_C void UpdateLocalIndexEntryL(TMsvMmsEntry& aIndexEntry);

    private:
        /**
         * Externalize this message to a stream in a message entry store.
         *
         * @param aWriteStream The message entry store stream.
         * @exception KErrXxx Standard EPOC stream leave codes if an error occurs writing to the stream.
         */
        void ExternalizeL(RWriteStream& aWriteStream) const;
        /**
         * Internalize this message from a stream in a message entry store.
         *
         * @param aReadStream The message entry store stream.
         * @exception KErrNotSupported The stream was written by a previous version and its format is no longer supported
         * @exception KErrXxx Standard EPOC stream leave codes if an error occurs reading from the stream.
         */
        void InternalizeL(RReadStream& aReadStream);

        /**
         * Construct the media object list for this message.
         */
        void ConstructMediaObjectListL();

    private:
		CMmsHeaders* iHeaders;                  ///< MMS headers for this message
		CMmsMediaObjectList* iMediaObjectList;  ///< MMS media objects for this message
        TMmsMessageMIMECategory iMIMECategory;  ///< MIME category (single-part or multi-part) for this message
    };


#endif __MMSMESSAGE_H__
