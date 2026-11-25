/*
* ==============================================================================
*  Name        : eikproc.h
*  Part of     : UIKON
*  Interface   : File Utility API
*  Description : File store used by a process.
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


#ifndef EIKPROC_H
#define EIKPROC_H

// INCLUDES
#include <apparc.h>
#include <eikdef.h>

// FORWARD DECLARATIONS
class CFileStore;
class CEikDocument;
class CApaAppFinder;

/**
* The <code>CEikProcess</code> class maintains a list of documents and all of 
* the shared resources that can be used by documents. As well as
* the functionality of <code>CApaProcess</code> (see apparc.h), this class contains additional 
* methods for accessing the main file store, the last file opened, and the last 
* file created.
*
* @lib eikcore.lib
* @since Series90 1.0
*/
class CEikProcess : public CApaProcess
    {
    public:
    /** 
    * The enumeration <code>TLastUsedFile</code> specifies flags to indicate 
    * the state of the last used file. */
    enum TLastUsedFile
        {
        /** the last used file was opened */
        ELastOpenFile,
        /** the last used file was created */
        ELastCreatedFile
        };
    public:

        /**
        * Starts the two-phase object construction.
        *
        * @param aFs Handle to a file server session
        * @return Pointer to a new <code>CEikProcess</code> object.
        * @remarks
        * @see
        * @internal
        */
        static CEikProcess* NewL(const RFs& aFs);

        /**
        * This method is not supported in Series 90.
        *
        * @return Not supported
        * @remarks
        * @see
        */
        IMPORT_C TPtrC CommandTailEnd() const;

        /**
        * Returns the folder containing the main document.
        *
        * @return the name of the folder that contains the main document
        * @remarks
        * @see
        */
        IMPORT_C TFileName MainDocFolder() const;

        /**
        * Stores the name of the last file that was used.
        *
        * @param aType Either <code>ELastOpenFile</code> or 
        *              <code>ELastCreatedFile</code> depending on whether the 
        *              file was opened or created
        * @param aFileName The name of the last used file
        * @remarks
        * @see
        */
        IMPORT_C void SetLastUsedFileL(TLastUsedFile aType,const TDesC& aFileName) const;

        /**
        * Returns the filename of the last used file.
        *
        * @param aType The type of file to retrieve. <code>ELastOpenFile</code>
        *              to get the last opened file; or <code>ELastCreatedFile</code>
        *              to get the last file created
        * @return the name of the last file that was used
        * @remarks
        * @see
        */
        IMPORT_C TFileName LastUsedFileL(TLastUsedFile aType) const;

        /**
        * Sets the main file store.
        *
        * @param aMainStore The store
        * @remarks
        * @see
        */
        IMPORT_C void SetMainStore(CFileStore* aMainStore);

        /**
        * Returns the main file store.
        *
        * @return the main file store
        * @remarks
        * @see
        */
        IMPORT_C CFileStore* MainStore() const;

        /**
        * Gets the application associated with a document.
        *
        * @param aLibraryName On return, contains the filename of the 
        *                     application or library
        * @param aDocumentName The filename of the document
        * @remarks
        * @see
        */
        IMPORT_C void AppFromDocL(TDes& aLibraryName,const TDesC& aDocumentName) const;
        
        /**
        * Saves a document to a new file and then opens that file for reading.
        *
        * @param aDoc The document to save
        * @param aNewFileName The filename to save to. If <code>NULL</code>, 
        *                     saves to the main document file store
        * @remarks
        * @see
        */
        IMPORT_C void SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName=NULL);

        /**
        * Saves a document and optionally reopens the saved document.
        *
        * @param aDoc The document to save
        * @param aNewFileName The filename to save to. If <code>NULL</code>, 
        *                     the document is saved to a temporary file and 
        *                     <code>aTempFile</code> is set to the temporary 
        *                     filename. If <code>aTempFile</code> is also 
        *                     <code>NULL</code>, the document is saved to the 
        *                     main document file store
        * @param aReopen If <code>ETrue</code>, the newly saved document is 
        *                reopened as the main store; if <code>EFalse</code> [what]
        * @param aTempFile If not set to <code>NULL</code>, on return this 
        *                  contains the temporary filename 
        * @remarks
        * @see
        */
        IMPORT_C void SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName,TBool aReopen,TFileName* aTempFile=NULL);

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikProcess();
    private:
        CEikProcess(const RFs& aFs,CApaAppFinder& aAppFinder);
        void GetLibraryNameL(TDes& aLibraryName,const CFileStore& aDocStore,const CStreamDictionary& aStreamDic) const;
        void OpenNewFileL(const TFileName* aNewFileName,const TParse& aNewFilePath);
        CDictionaryStore* OpenMainAppIniFileLC() const;
    private:
        TPtrC iCommandTailEnd;
        CFileStore* iMainStore;
    };


#endif  // EIKPROC_H

// End of File
