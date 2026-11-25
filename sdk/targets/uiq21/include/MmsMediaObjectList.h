// $Workfile: mmsmediaobjectlist.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Simonk $
// $Revision: 3 $
// $Date: 3/04/03 17:48 $
//

/** @file
 *  This file contains the definition of the CMmsMediaObjectList class.
 */

#ifndef __MMSMEDIAOBJECTLIST_H__
#define __MMSMEDIAOBJECTLIST_H__

#include <e32std.h>
#include <e32base.h>	//CBase

#include "mmsutils.h"	//TMmsMediaObjectId
//forward declarations

class CMsvStore;
class CMmsMediaObject;
class RWriteStream;
class RReadStream;
class CMmsCodecMediaObjectCreator;

/**
 * This class provides the means for manipulating a collection of media objects.
 */

class CMmsMediaObjectList : public CBase
	{
	public:
        /**
         * 2 phase constructor
         * This function creates a CMmsMediaObjectList object.
         *
         * @param aFileDirectory The path associated with object list
         * @param aMIMECategory A MIME category (either single-part or multi-part) for this media object list.
         * @exception KErrXXX Standard EPOC leave codes if no memory is available
         * @return A newly created CMmsMediaObjectList
         */
		IMPORT_C static CMmsMediaObjectList* NewL(const TDesC& aFileDirectory, TMmsMessageMIMECategory aMIMECategory = EMmsMultiPart);
        /**
         * 2 phase constructor
         * This function creates a CMmsMediaObjectList object and puts it on the cleanup stack.
         *
         * @param aFileDirectory The path associated with object list
         * @param aMIMECategory A MIME category (either single-part or multi-part) for this media object list.
         * @exception KErrXXX Standard EPOC leave codes if no memory is available
         * @return A newly created CMmsMediaObjectList object
         */
		IMPORT_C static CMmsMediaObjectList* NewLC(const TDesC& aFileDirectory, TMmsMessageMIMECategory aMIMECategory = EMmsMultiPart);
        /**
         * C++ destructor.  Note that files associated with the component media objects are not removed.
         */
		IMPORT_C ~CMmsMediaObjectList();

        /**
         * Creates a stream in aStore and externalises all media objects in the list to it.
         *
         *
         * @param aStore The store to which this object is to be stored. Note this must be open with write access or
         *  this function will leave.
         * @param aCommit A boolean to indicate whether or not the CMsvStore should be committed
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         * @exception KErrAccessDenied aStore is not opened with write access.
         *
         */
		IMPORT_C void StoreL(CMsvStore& aStore, TBool aCommit) const;
        /**
         * Opens a stream in aStore and internalises a list of media objects from it.
         * @param aStore The store from which this object is to be restored. Note this must be open with read or
         *  read/write access or this function will leave.
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         * @exception KErrAccessDenied aStore is not opened with read access.
         *
         */
		IMPORT_C void RestoreL(const CMsvStore& aStore);

        /**
         * Creates a new media object in the media object list and an associated file.  A reference to the newly created
         * media object is returned.  The corresponding file can be manipulated by getting its filename, through
         * CMmsMediaObject::Filename().
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
         * a second media object to a list whose MIME category is set to <code>EMmsSinglePart</code>.
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
         * Creates a new media object in the media object list and an associated file.  A reference to the newly created
         * media object is returned.  The corresponding file can be manipulated by getting its filename, through
         * CMmsMediaObject::Filename().
         *
         * @note
         * This version of the function is for use primarily by clients which generate messages using
         * a SMIL template (i.e. where object URIs are already defined). Client code which generates messages dynamically
         * should generally use the overloaded version which takes a MIME type and file name/extension.
         *
         * @note
         * This function will panic with <code>EMmsPanicMIMECategoryViolation</code> if an attempt is made to add
         * a second media object to a list whose MIME category is set to <code>EMmsSinglePart</code>.
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
         * Removes the media object identified by aId, and its associated file.
         *
         * @param aId the TMmsMediaObjectId of the media object to be removed
         * @retval KErrNone The object was successfully deleted.
         * @retval KErrNotFound No object was found with the ID aId.
         */
		IMPORT_C TInt RemoveMediaObject(TMmsMediaObjectId aId);
        /**
         * Returns the number of media objects in the current message.
         * @return The number of media objects in the current message.
         */
		IMPORT_C TInt MediaObjectCount() const;
        /**
         * Returns the ID of the object with the URI aURI.
         *
         * @param aURI URI of the object whose ID is requested.
         * @retval TMmsMediaObjectId The ID of the object with URI aURI if found.
         * @retval KMmsNullMediaObjectId A match could not be made.
         */
		IMPORT_C TMmsMediaObjectId MediaObjectIdFromURI(const TDesC& aURI) const;
        /**
         * Returns a reference to a media object owned by the media object list.
         *
         * @param aId ID of the requested object
         * @exception KErrNotFound No object could be found matching this ID.
         * @return A reference to the requested object.
         */
		IMPORT_C CMmsMediaObject& MediaObjectL(TMmsMediaObjectId aId);
        /**
         * Get the ID of the root entry, if set (typically the presentation part of a message).
         *
         * @retval TMmsMediaObjectId The ID of the root entry
         * @retval KMmsNullMediaObjectId No root has been set.
         */
		IMPORT_C TMmsMediaObjectId RootId() const;
        /**
         * Along with IteratorHasNext() and IteratorGetNext(), this provides a simple iterator interface for sequentially
         * accessing all objects owned by a message. This method must be called prior to using the other iterator methods,
         * to ensure correct iteration through all media objects.
         */
		IMPORT_C void IteratorStart();
        /**
         * Call to check whether there are still media objects to iterate through.
         *
         * @return Boolean to indicate whether or not there are further media objects to iterate through.
         */
		IMPORT_C TBool IteratorHasNext() const;
        /**
         * Call to get the next object in the message.
         * N.B. Client should call IteratorHasNext() prior to calling this function, otherwise it will panic if at the end
         * of the list.
         * @return A reference to the next object in the message.
         */
		IMPORT_C CMmsMediaObject& IteratorGetNext();

	private:
        /**
         * C++ constructor
         * Sets the root id to KMmsNullMediaObjectId. All other construction is done in the ConstructL function.
         * @param aMIMECategory A MIME category (either single-part or multi-part) for this media object list.
         */
		CMmsMediaObjectList(TMmsMessageMIMECategory aMIMECategory);
        /**
         * 2nd phase constructor.  Responsible for non-trivial construction
         *
         * @param aFileDirectory The path associated with object list
         * @exception KErrXXX Standard EPOC leave codes if no memory is available
         */
		void ConstructL(const TDesC& aFileDirectory);
        /**
         * Externalizes the CMmsUtilsHeaderArray to a stream.
         *
         * @param aWriteStream The stream to be written to
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         */
		void ExternalizeL(RWriteStream& aWriteStream) const;
        /**
         * Internalizes the CMmsUtilsHeaderArray from a stream.
         *
         * @param aReadStream The stream to be read from
         * @exception KErrNotSupported The stream was written by a previous version and its format is no longer supported
         * @exception KErrXXX Leaves with standard EPOC stream leave codes
         */
		void InternalizeL(RReadStream& aReadStream);
        /**
         * Generates a filename unique within the context of this list and leaves it on the cleanup stack
         *
         * @param aFileNameOrExtn Either a preferred filename (e.g. "test.txt") or just a preferred file extension (e.g. ".txt").
         *      If a preferred filename is specified, this will be used unless it clashes with a filename of an existing media
         *      object. In this case, a new filename will be generated with digits appended to the original filename base
         *      (e.g. test01.txt, test02.txt, etc.).
         *      If just a file extension is specified, a unique filename will be generated of the format 00000001.<extn>.
         *      Note that a string without a full stop (e.g. "test") will be interpreted as a filename with no extension, and used
         *      accordingly.
         * @return A newly generated filename
         * @exception KErrXxx Standard EPOC leave codes
         */
		HBufC* GenerateFilenameLC(const TDesC& aFileNameOrExtn);
        /**
         * Generates a URI unique within the context of this list and leaves it on the cleanup stack
         *
         * @exception KErrXXX Standard EPOC leave codes if no memory is available
         * @return A newly generated URI
         */
		HBufC* GenerateURILC();
        /**
         * Currently a very simple implementation
         *
         * Extracts a file extension from the URI, assuming that the file extension consists of the last characters of
         * the URI - starting with a dot.
         *
         * @return The file extension of the URI including the dot.
         */
        TPtrC ExtractExtension(const TDesC& aURI) const;
        /**
         * Checks whether the URI passed in is the URI of a media object already in the list
         *
         * @param aURI      The URI to check the media object list for
         * @retval ETrue    The URI is already in the media object list and so can't be used
         * @retval EFalse   The URI is not already in the media object list
         */
        TBool URIAlreadyExists(const TDesC& aURI);

    private:
        /**
         * Utility class for deleting the media object file in the event of a leave in CreateMediaObjectL
         */
        class TMmsMediaObjectFileCleanup
            {
            public:
                TMmsMediaObjectFileCleanup(RFs& aFs, const TDesC& aFilename);
                void Release();
            private:
                RFs& iFs;
                TPtrC iFilename;
            };

        friend class CMmsCodecMediaObjectCreator;

	private:
		TMmsMediaObjectId iRootId;	///<The media object ID of the root object - typically the presentation part
		TInt iIteratorIndex;		///<The index of the current media object to be manipulated by the iterator interface ie. the index of the object returned by IteratorGetNext
		CArrayPtrSeg<CMmsMediaObject>* iMediaObjects;	///<An array of media objects
		TMmsMediaObjectId iLastIdGenerated;		///<The media object ID of the last media object created
		HBufC* iFileDirectory;		///<The file directory associated with the media objects
		TInt iLastFilenameNumber;	///<The number of the last filename created
		TInt iLastURINumber;	    ///<The number of the last URI created
        RFs iFs;		            ///<A handle to the file server session
        TMmsMessageMIMECategory iMIMECategory;    ///< MIME category (single-part or multi-part) for this media object list
	};



#endif //__MMSMEDIAOBJECTLIST_H__