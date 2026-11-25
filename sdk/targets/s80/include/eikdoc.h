/*
* ==============================================================================
*  Name        : eikdoc.h
*  Part of     : UIKON
*  Interface   : Document API
*  Description : Base class for all application documents.
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


#ifndef EIKDOC_H
#define EIKDOC_H

// INCLUDES
#include <apparc.h>
#include <savenotf.h>

// FORWARD DECLARATIONS
class CEikAppUi;
class CEikApplication;
class CApaWindowGroupName;

/**
 * The <code>CEikDocument</code> class is the base for all Uikon 
 * applications' documents. A class derived from <code>CEikDocument</code> 
 * is used in each Uikon application. In file-based applications, the document 
 * provides an intermediate layer between the user interface, the model, and the
 * file the model will be stored in. Non-file-based applications only use
 * a document to create the application UI. Each Uikon application should
 * use a class derived from <code>CEikDocument</code> to represent its
 * document. The derived class must implement at least
 * <code>CreateAppUiL()</code>.
 *
 * @lib eikcore.lib
 * @since 6.0
 */
class CEikDocument : public CApaDocument
    {
    public: // new functions
        /**
         * Allocates the application UI.
         * This method is called by the application framework to create an 
         * instance of an application UI for this document and its associated 
         * application. The object returned is owned by the Uikon framework.
         *
         * @return a freshly allocated application UI. The framework calls
         *         <code>ConstructL()</code> on this object to complete the 
         *         second phase of construction
         * @see
         * @remarks
         */
        virtual CEikAppUi* CreateAppUiL()=0;

        /**
         * Called by the Uikon framework to open a file.
         * If <code>aDoOpen</code> is <code>ETrue</code>, this method attempts
         * to open a file for exclusive writes
         * (<code>EFileShareExclusive|EFileWrite</code>). Failing that, the
         * method attempts to open the file for exclusive reads
         * (<code>EFileRead|EFileShareReadersOnly</code>). If the file cannot 
         * be opened at all when <code>aDoOpen</code> is <code>ETrue</code>, 
         * this method leaves with <code>KErrNotFound</code> if the file cannot be
         * found or <code>KErrCorrupt</code> if the file is not a valid
         * stream-based document file. If <code>aDoOpen</code> is
         * <code>EFalse</code>, this method attempts to create and open a new
         * file for exclusive writes.
         *
         * @param aDoOpen If <code>ETrue</code>, opens an existing file; 
         *                otherwise creates a new file
         * @param aFilename The name of the file to open or create
         * @param aFs The file server session to use
         * @return the file store object referring to the newly-opened file
         * @remarks
         * @see
         */
        IMPORT_C virtual CFileStore* OpenFileL(TBool aDoOpen,const TDesC& aFilename,RFs& aFs);

        /**
         * Prepares a document for editing. This method calls 
         * <code>CreateAppUiL()</code> to construct the application's user 
         * interface. It is called by <code>PrepareToEditL()</code> when an 
         * application is constructed, and by <code>EditL()</code> when a 
         * document is embedded within another and is opened for editing.
         *
         * @param aObserver The observer to be called when editing is completed.
         *                  Set to <code>NULL</code> if the document is not 
         *                  embedded
         * @param aReadOnly If <code>ETrue</code>, the document is opened as
         *                  read-only and changes made to its content do not 
         *                  persist; otherwise, the document is opened as 
         *                  editable
         * @remarks
         * @see PrepareToEditL()
         * @see EditL(MApaEmbeddedDocObserver* aObserver, TBool aReadOnly)
         */
        IMPORT_C void PrepareToEditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly);

        /**
        * Prepares a document for editing. This implementation just calls 
        * <code>PrepareToEditL(NULL, NULL)</code>. The framework calls this 
        * method when an application is constructed.
        *
        * @return
        * @remarks
        * @see PrepareToEditL(MApaEmbeddedDocObserver* aObserver, TBool aReadOnly)
        */
        IMPORT_C void PrepareToEditL();

        /**
         * Sets the application file's access and share mode.
         *
         * @param aMode The new value for the file mode field of this document: 
         *              a bitwise OR of values defined in <code>TFileMode</code>
         *              (in f32file.h)
         * @remarks Sets a new value by ORing flags together, for example,
         *          <code>EFileRead|EFileShareReadersOnly</code>
         * @see
         */
        IMPORT_C void SetAppFileMode(TUint aMode);

        /**
         * Gets the access and share mode of the application file.
         *
         * @return the file mode field of this document:
         *         a bitwise OR of values defined in <code>TFileMode</code>
         *         (in f32file.h)
         * @remarks Check for a flag by ANDing with the flag, for example, 
         *          <code>TBool writeable = Document()->AppFileMode() & EFileWrite;</code>
         * @see
         */
        IMPORT_C TUint AppFileMode() const;

        /**
         * Updates the task name (also known as the window group name) that is
         * held in the task list. The task list can be accessed through
         * <code>TApaTaskList</code>'s API. The window group name
         * encodes four pieces of information for that task: the name of the
         * document that the task is handling, the task's caption, the 
         * application specific UID as eight hexadecimal characters, and 
         * status information for the task as two hexadecimal characters.
         * Derived classes can override this method to control what is held
         * in the task list.
         *
         * @param aWgName A pointer to the task name to be updated
         * @remarks
         * @see CApaWindowGroupName
         * @see TApaTaskList
         */
        IMPORT_C virtual void UpdateTaskNameL(CApaWindowGroupName* aWgName);

        /**
         * Gets the associated application's caption. The caption is the name
         * shown on the desktop and in the application's title bar. It can be
         * set in the .aif file. If no caption is set in the .aif 
         * file, the target name of the application, as specified in the .mmp
         * file, is used.
         *
         * @return the caption of the application with which this document is
         *         associated
         * @remarks
         * @see CEikApplication::AppCaption()
         */
        IMPORT_C const TApaAppCaption& AppCaption() const;

        /**
         * Sets this document's document-changed flag. This flag can be
         * accessed using <code>HasChanged()</code>.
         *
         * @param aHasChanged The new state for the document-changed flag. 
         *                    <code>ETrue</code> if the document has changes; 
         *                    otherwise <code>EFalse</code>
         * @remarks
         * @see HasChanged()
         */
        IMPORT_C void SetChanged(TBool aHasChanged);

        /**
         * Sets the stream store associated with this document to <code>aStore</code>.
         * The framework calls this method when the application is constructed
         * and initialized to the same value as the process's main store.
         *
         * @param aStore The stream store to use
         * @remarks
         * @see EditStoreL()
         */
        IMPORT_C void SetEditStoreL(CStreamStore* aStore);

        /**
         * Gets the stream store associated with this document.
         * An application might use this if it needs access to the stream store
         * outside of the usual <code>StoreL()</code> and <code>RestoreL()</code>
         * methods.
         *
         * @return a pointer to the stream store associated with this document
         * @remarks 
         * @see SetEditStoreL()
         */
        inline CStreamStore* EditStore() const;

        /**
         * The object destructor.
         *
         * @remarks
         * @see
         */
        IMPORT_C ~CEikDocument();

        /**
         * Saves this document to its current direct file store.
         * Marks the document as not having changed. The framework calls this 
         * method when an application exits and the current state of the
         * application's document is saved to the currently opened file. The
         * application can then exit cleanly.
         *
         * @param aSaveType The save type
         * @remarks <code>SaveL()</code> saves the document regardless of the 
         *          state of the document-changed flag. <code>aSaveType</code> 
         *          is ignored in the default implementation
         * @see HasChangedL()
         * @see SaveL()
         */
        IMPORT_C virtual void SaveL(MSaveObserver::TSaveType aSaveType);

    public: // from CApaDocument

        /**
         * The framework calls this method to initialize a new default document file.
         * The method is called when the application is started 
         * without a file and there is no existing default document file in the 
         * file system. The default document filename is specified by the first
         * TBUF string in the application's resource file. This method should 
         * initialize the document to some default settings, for example, a
         * default template file.
         *
         * @remarks The default implementation does nothing
         * @see
         */
        IMPORT_C void NewDocumentL();

        /**
         * Creates a new file store for a file. It creates a new file or 
         * overwrites an existing one, as necessary. <code>StoreL()</code> is 
         * called immediately on the new store.
         *
         * @param aFs The file server session to use
         * @param aFileName The full path to the file
         * @return the newly created file store
         * @remarks The method pushes the <code>CFileStore*</code> pointer onto 
         *          the cleanup stack. An invalid file server session  
         *          causes a KERN-EXEC panic
         * @see
         */
        IMPORT_C CFileStore* CreateFileStoreLC(RFs& aFs,const TDesC& aFileName);

        /**
         * Starts an editing session on an embedded document.
         * This creates the associated application's UI and switches to the new
         * view, with the document open for editing or viewing, depending on 
         * <code>aReadOnly</code>. This method is called when an embedded 
         * document must be opened, for example when the user taps an 
         * embedded image in a rich text editor. The method calls 
         * <code>PrepareToEditL()</code> to construct the application's UI.
         *
         * @param aObserver The pointer to an observer that should be informed 
         *                  when editing is completed
         * @param aReadOnly If <code>ETrue</code>, the document is opened as 
         *                  read-only, and changes made to its content do not 
         *                  persist; if <code>EFalse</code>, the document is opened as 
         *                  editable
         * @remarks
         * @see MApaEmbeddedDocObserver
         * @see PrepareToEditL(MApaEmbeddedDocObserver* aObserver, TBool aReadOnly)
         */
        IMPORT_C void EditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly=EFalse);

        /**
         * <B>Note:</B> this method is not supported in Series 90.         
         * Prints a document without opening it for editing first.
         * Typically, this method would be called from a shell or file manager 
         * application that wanted to print the document without opening it fully.
         * This method is empty. Applications that support printing should
         * override this with a method that uses default print parameters.
         *
         * @param aSourceStore The source stream store
         * @remarks
         * @see
         */
        IMPORT_C void PrintL(const CStreamStore& aSourceStore);

        /**
         * Saves this document to its current direct file store.
         * This method marks the document as not having changed. It is called 
         * by the framework when an application exits. The current state of the
         * application's document is saved to the currently open file and the
         * application can then exit cleanly. The actual saving is handled by
         * <code>StoreL()</code>.
         *
         * @remarks <code>SaveL()</code> saves the document regardless of the 
         *          state of the document-changed flag
         * @see HasChangedL()
         * @see SaveL(MSaveObserver::TSaveType aSaveType)
         * @see StoreL()
         */
        IMPORT_C void SaveL();

        /**
         * Stores the documents content and state to a supplied stream store.
         * The Uikon implementation of this method is empty. Applications that
         * wish to persist any data must provide their own version. The 
         * framework calls this method when <code>SaveL()</code> is called.
         *
         * @param aStore The stream store to which data is saved
         * @param aStreamDic The stream dictionary in which streams created by 
         *                   the stream store must be assigned a unique identifier
         * @remarks
         * @see SaveL()
         */
        IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const;

        /**
         * Restores this document from a supplied stream store.
         * It sets the document's state and content. Any existing data in the
         * document is lost. The Uikon implementation of this method is
         * empty. Applications that wish to load any persisted data must provide
         * their own version. The framework calls this method when the
         * application is loaded.
         *
         * @param aStore The stream store from which to read the new state and
         *               content
         * @param aStreamDic The stream dictionary in which streams to be opened
         *                   by the stream store can be accessed by their unique
         *                   identifier
         * @remarks
         * @see
         */
        IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic);

        /**
         * Externalizes this document to a write stream.
         * The Uikon implementation of this method is empty and it is never
         * called by the framework.
         *
         * @param aStream  The write stream to which information is written
         * @remarks
         * @see
         */
        IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

        /**
         * Determines whether this document contains any content.
         * Because the Uikon implementation of this method just returns
         * <code>ETrue</code>, any applications that use documents to represent
         * and store data should override it. This method is declared as
         * <code>virtual</code> in <code>CApaDocument</code>.
         *
         * @return <code>ETrue</code> (in <code>CEikDocument</code>)
         * @remarks
         * @see
         */
        IMPORT_C TBool IsEmpty() const;

        /**
         * Gets this document's document-changed flag. This flag can be set by
         * <code>SetChanged()</code> and is cleared by <code>SaveL()</code>.
         *
         * @return <code>ETrue</code> if the document has changed; otherwise 
                   <code>EFalse</code>
         * @remarks Applications can check this flag to decide whether or not
         *          to call <code>SaveL()</code>
         * @see SetChanged()
         * @see SaveL()
         */
        IMPORT_C TBool HasChanged() const;
    protected:

        /**
         * The default object constructor. Allocates a new 
         * <code>CEikDocument</code> and initializes its references to its 
         * associated application and managing process.
         *
         * @param aApp The application instance with which the new document
         *            is associated
         * @remarks
         * @see
         */
        IMPORT_C CEikDocument(CEikApplication& aApp);
    private:
        void NullAppUi();
    // reserved functions from CApaDocument
        IMPORT_C virtual void Reserved_1();
        IMPORT_C virtual void Reserved_2();
    protected:
        CEikAppUi* iAppUi;
        CStreamStore* iEditStore;
    private:
        TBool iChanged;
        TUint iAppFileMode;
    //
    friend class CEikAppUi;
    };

/**
 * returns a pointer to the application process associated with this document
 * @publishedAll
 * @released
 */
#define iEikProcess ((CEikProcess*)Process())

/**
 * returns a pointer to the application that created the document
 * @publishedAll
 * @released
 */
#define iEikApplication ((CEikApplication*)Application())

/**
 * the default dimensions of any icon used to represent an embedded document
 * @publishedPartner
 * @released
 */
#define KDefaultIconicDoorSize TSize(500,500)

/** 
 * gets the edit store
 * @return Pointer to the stream store set as the edit store.
 */
inline CStreamStore* CEikDocument::EditStore() const
    { return(iEditStore); }


#endif  // EIKDOC_H

// End of File
