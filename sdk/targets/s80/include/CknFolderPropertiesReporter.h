/*
* ==============================================================================
*  Name        : cknfolderpropertiesreporter.h
*  Part of     : CKON / CKNDLG
*  Interface   : 
*  Description : Folder properties dialog
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


#ifndef CKNFOLDERPROPERTIESREPORTER_H
#define CKNFOLDERPROPERTIESREPORTER_H

// INCLUDES
#include <f32file.h>


/**
*  The <code>MCknFolderPropertiesObserver</code> class defines the 
*  folder properties observer. When a class that implements this interface
*  is passed as an observer in a call to 
*  <code>CCknFolderPropertiesReporter::NewL()</code> the overridden public 
*  virtual methods  are called from the folder properties reporter to report 
*  folder and file statistics.
*
*  @lib ckndlg.lib
*  @since Series90 1.0
*/
class MCknFolderPropertiesObserver
    {
    public:
       /**
        * Overriding this method provides the observer with an incremental 
        * count of folders, files, and file size.
        * 
        * @param aFolderCount The total number of folders
        * @param aFileCount The total number of files
        * @param aSizeInBytes The size in bytes
        * @remarks
        * @see
        */
        virtual void UpdateValuesL(TInt aFolderCount, TInt aFileCount, TInt aSizeInBytes)=0;

       /**
        * This method is called when all calculations for the specified folder 
        * have been completed.
        * 
        * @remarks
        * @see
        */
        virtual void HandleUpdateComplete()=0;
    private:
        virtual void MCknFolderPropertiesObserver_Reserved_1();
        virtual void MCknFolderPropertiesObserver_Reserved_2();
    };

/**
 * The <code>CCknFolderPropertiesReporter</code> class implements an active 
 * object used by the Properties Dialog to count the number of sub-folders and 
 * files contained in a particular folder and to calculate the total file size.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 * @internal
 */

class CCknFolderPropertiesReporter : public CActive
    {
    public:

        /**
         * The object destructor.
         * @internal
         */
        ~CCknFolderPropertiesReporter();

        /**
         * Creates a new <code>CCknFolderPropertiesReporter</code> to calculate 
         * folder/file counts and total file size for the specified folder.
         * Incremental values will be reported by calls to the observer's 
         * <code>UpdateValues(TInt aFolderCount, TInt aFileCount, TInt 
         * aSizeInBytes)</code> method. Completion of calculation will be 
         * reported by a call to the observer's <code>HandleUpdateComplete()</code>
         * method.
         *
         * @param aFolderPropertiesObserver The observer that handles the 
         *                                  results of the calulations
         * @param aFullPath The object for which the calculations are performed. 
         *                  To scan all folder contents, the path should end 
         *                  with '\*'
         * @param aFsSession
         * @return [what]
         * @remarks
         * @see
         * @internal
         */
        static CCknFolderPropertiesReporter* NewL(RFs& aFsSession,MCknFolderPropertiesObserver* aFolderPropertiesObserver,const TDesC& aFullPath);

        /**
         * Begins calculations and reports incremental values periodically.
         *
         * @internal
         */
        void Start();
    private:

    /**
    * The enumeration <code>TStage</code> specifies the stages that the scanning 
    * process passes through.
    */
    enum TStage
        {
        /** set up the scan data */
        EInitialise,
        /** 
         * get a list of files/folders in the next folder in the hierarchy 
         * (performs a 'downwards scan') 
         */
        EScanNext,
        /** 
         * increment folder/file count and cumulative size using the object's 
         * from the last scanned directory  
         */
        EProcessCurrent,
        /** all folders have been processed */
        EScanComplete
        };
    private:
        CCknFolderPropertiesReporter(RFs& aFsSession,MCknFolderPropertiesObserver* aFolderPropertiesObserver,const TDesC& aFullPath);

        /**
         * Schedule to run again
         */
        void Queue();
    private: // from CActive

        /**
         * Performs the current stage of processing and sets the object state to the next stage before queueing to run again.
         * The EProcessCurrent stage will timeout after a specified period and will continue when next scheduled
         */
        void RunL();

        void DoCancel();
    private:
        RFs& iFsSession;                                            /// Used during the direcory scan
        MCknFolderPropertiesObserver* iFolderPropertiesObserver;    /// Observer that receives the incremental updates
        const TDesC& iFolderPath;                                   /// Folder at the top of the hierarchy to scan
        TInt iFolderCount;                                          /// Cumulative count of folders within the hierarchy (excluding the parent folder)
        TInt iFileCount;                                            /// Cumulative count of files within the hierarchy
        TInt iSizeInBytes;                                          /// Cumulative calculation of file size
        CDirScan* iDirScan;                                         /// Performs the scan of the hierarchy
        TStage iStage;                                              /// Maintains the current stage of the process
        CDir* iEntries;                                             /// The objects contained in the folder currently being processed
        TInt iCurrentIndex;                                         /// The object currently being examined
        TInt iTotalCount;                                           /// Total number of objects in the folder currently being procesed
        TBool iTimeout;                                             /// Indicates if the process is stopping due to timeout
        TTime iTimeOfNextReport;                                    /// The time the next report is due
    };


#endif  // CKNFOLDERPROPERTIESREPORTER_H

// End of File
