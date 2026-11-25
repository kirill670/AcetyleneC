/*
* ==============================================================================
*  Name        : eikapp.h
*  Part of     : UIKON
*  Interface   : Application API
*  Description : The root of all Uikon application
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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


#ifndef EIKAPP_H
#define EIKAPP_H

// INCLUDES
#include <apparc.h>
#include <apaflrec.h>

// FORWARD DECLARATIONS
class CCoeEnv;
class CEikApplicationExtra;




/**
 *
 * The <code>CEikApplication</code> class is the root of all Uikon applications.
 * It builds on <code>CApaApplication</code> providing a basis for applications 
 * working within the framework provided by Uikon. It also contains an 
 * interface to the resource file and the document. Each Uikon application 
 * class is derived from <code>CEikApplication</code>. Application developers 
 * must provide at least an implementation of  
 * <code>CreateDocumentL()</code> that has no parameters. The application's 
 * resource file can be changed from the default by overriding 
 * <code>ResourceFileName()</code>.
 *
 * @lib eikcore.lib
 * @since 6.0
 */
class CEikApplication : public CApaApplication
    {
    public:

        /**
        * The default object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikApplication();

        /**
        * Gets the offset value defined for this application's default resource
        * file. Since the resource file offset can also be accessed through 
        * <code>iResouceFileOffset</code>, this method should not be needed by any
        * applications.
        * 
        * @return offset of a resource file
        * @remarks
        * @see 
        */
        inline TInt ResourceFileOffset() const;

        /**
        * Gets the managing process.
        * 
        * @return a pointer to the process object managing this application's 
        *         documents
        * @remarks Once a pointer to the process has been obtained, it is 
        *          possible to carry out document-related operations
        * @see
        */
        inline CApaProcess* Process() const;

        /**
        * Gets the caption for this application.
        * Application captions are displayed in the task list.
        * 
        * @return the application's caption
        * @remarks
        * @see
        */
        inline const TApaAppCaption& AppCaption() const;

        /**
        * Gets the default document name for this application.
        * Each application has a default naming convention for the
        * documents created with it. If the user fails to supply an 
        * alternative filename, a document created by the application
        * is named using this default naming convention.  
        * 
        * @param aDocumentName On return, contains the default document file 
        *        name
        * @remarks The alternative document filename is specified by the first
        *          TBUF string in the application's resource file and is, 
        *          by convention, given the same name as the application.
        *          <code>RESOURCE TBUF { buf="MyDocumentName"; }</code>
        * @see
        */
        IMPORT_C virtual 
            void GetDefaultDocumentFileName(TFileName& aDocumentName) const;

        /**
        * Gets the filename of the .mbm file with the same basename as the
        * application file in the same directory. Language variants are
        * supported using <code>BaflUtils::NearestLanguageFile()</code>.
        * 
        * @return the filename of the bitmap store for this application
        * @remarks
        * @see BaflUtils::NearestLanguageFile()
        */
        IMPORT_C virtual TFileName BitmapStoreName() const;

        /**
        * Creates a <code>CApaAppInfoFileReader</code> object for reading 
        * the default application information file associated with
        * this Uikon application and returns a pointer to it.
        * 
        * @return the reader for the application's information (.aif) file
        * @remarks The application information file has an .aif 
        *          extension. The file is used to customize 
        *          the application with items like icons
        * @see 
        */
        IMPORT_C CApaAppInfoFileReader* OpenAppInfoFileLC() const;

        /**
        * Opens the application's .ini file if it exists.
        * If an .ini file does not exist for this application, or if it is 
        * corrupt, this method creates a new .ini file and opens that. INI 
        * files are located on <code>KIniFileDrive</code>. By default, this
        * is in the c: drive in the same directory as the application DLL.
        * 
        * @param aFs The file server session to use
        * @return the pointer to the dictionary store for the opened file
        * @remarks Once a pointer to <code>CDictionaryStore</code> is obtained,
        *          providing the location of the document data and application 
        *          identifier stream. This allows access to information such 
        *          as the application's DLL name. The .ini file contains 
        *          initialization data for the application
        * @see 
        */
        IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;

        /**
        * Gets the application's capabilities.
        * This is an implementation of the pure virtual method 
        * <code>CApaApplication::Capability()</code>. Uikon
        * application developers should not need to override this method.
        * 
        * @param aInfo Contains the data about the application's capability
        * @remarks
        * @see
        */
        IMPORT_C void Capability(TDes8& aInfo) const;

        /**
        * Creates a parser for this application's .ini file.
        * Sets the fields of a supplied filename parser object, allowing it 
        * to find this application's .ini file.
        * 
        * @param aParser On return, contains a parser that can be used to find 
        *                this application's .ini file
        * @remarks
        * @see
        */
        IMPORT_C void SetToIniFileNameL(TParse& aParser) const;
		/**
		* Adds an entry for the specified document file name to the beginning of
		* the list.
		*
		* If an entry with the same name already exists in the list, then that
		* entry is moved from its current position to the beginning of the
		* list.This entry represents the most recently used document.
		*
		* @param aFs		Handle to a file server session.
		* @param aFileName	The document file name to be added to the list.
		* @param aAppUid	The associated UID
		*/
		IMPORT_C static void AddLastUsedEntryL(RFs& aFs, const TDesC& aFileName, TUid aAppUid);

		/**
		* Returns all entries for those last used documents which match the
		* specified criteria.
		*
		* The first entry in the returned array represents the most recently
		* used document, the second entry represents the second most recently
		* used etc.
		*
		* @param     "RFs& aFs"
		*            Handle to a file server session.
		* @param     "TUid aAppUid"
		*            An application specific UID. If <code>KNullUid</code>,
		*            then all documents in the list are eligible, otherwise
		*            only those documents associated with this UID are
		*            eligible.
		* @returns   "CArrayFixFlat<TApaLastUsedEntry>*"
		*            A pointer to an array of entries for the last used
		*            documents.
		*/
		IMPORT_C static CArrayFixFlat<TApaLastUsedEntry>* GetRecentTaskListL(RFs& aFs, TUid aAppUid);
    protected: // from CApaApplication

        /**
        * Prepares for document creation.
        * Called by the application DLL framework to complete construction and 
        * initialize the new application object. After this method has been 
        * called, the <code>CEikApplication</code> can create document objects.
        * If there is a default resource file for this application, then it is 
        * added to the control environment. This method's leaving should be 
        * treated as if construction had failed and the object should be 
        * destroyed by the caller.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void PreDocConstructL();

        /**
        * Called by the application DLL framework to create a new instance of 
        * the document associated with this application. The Uikon 
        * implementation of this CApaApplication member function makes a 
        * record of the CApaProcess argument, and returns a
        * document created by the un-parameterised, private, form of 
        * CEikApplication::CreateDocumentL().
        *
        * @param aProcess deals with the loading of application DLLs and 
        *                 manages the creation and destruction of application 
        *                 objects and document objects. Maintains a list of 
        *                 documents and all of the potentially shared 
        *                 resources used by documents.
        */
        IMPORT_C CApaDocument* CreateDocumentL(CApaProcess* aProcess);
    private:
        // reserved virtual function from CApaApplication
        IMPORT_C virtual void Reserved_1();
    protected: // new function

        /**
        * C++ default constructor.
        */
        IMPORT_C CEikApplication();
    public: // new function

        /**
        * Gets the name of the resource file used by this application.
        * By default, this is an .rsc file with the same 
        * basename as the application file located in the same directory. 
        * Language variants are supported through
        * <code>BafUtils::NearestLanguageFile()</code>.
        * 
        * @return the name of the resource file. Used by 
        *         <code>PreDocConstructL()</code>
        * @remarks
        * @see
        */
        IMPORT_C virtual TFileName ResourceFileName() const;
    private: // new function
        virtual CApaDocument* CreateDocumentL()=0;
    private: // internal use
        void ParseWithAppName(TParse& aParse,const TDesC& aFileName) const;
        void ReadCaptionNameL();
        RFs* FileSession() const;
    protected:
        CCoeEnv* iCoeEnv;
        TInt iResourceFileOffset;
    private:
        CApaProcess* iProcess;
        TApaAppCaption iCaption;
        TApaAppCapabilityBuf* iCapabilityBuf;
        TUint iAppFlags;
        mutable CEikApplicationExtra* iExtra;
    };

inline TInt CEikApplication::ResourceFileOffset() const
/** Gets the offset value defined for this application's default resource file. 

As the resource file offset can also be accessed through iResourceFileOffset, 
this function should not be needed by any apps.

@return Offset of a resource file. */
    { return(iResourceFileOffset); }

inline CApaProcess* CEikApplication::Process() const
/** Gets the managing process.

@return A pointer to the process object managing this application's documents. */
    { return(iProcess); }

inline const TApaAppCaption& CEikApplication::AppCaption() const
/** Gets the caption for this application.

Captions are displayed in the task list.

@return Application caption. */
    { return(iCaption); }


#endif  // EIKAPP_H

// End of File
