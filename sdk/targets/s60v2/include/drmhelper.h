/*
* ==============================================================================
*  Name        : drmhelper.h
*  Part of     : DRMHelper
*  Interface   : 
*  Description : Class to show miscellaneous DRM related error notes and 
*                details about rights 
*  Version     : 
*
*  Copyright (c) 2003, 2004 Nokia Corporation.
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


#ifndef __DRMHELPER_H__
#define __DRMHELPER_H__

//  INCLUDES
#include <e32base.h>
#include <ConeResLoader.h>
#include <apparc.h>
#include <rdrmhelper.h>

// CONSTANTS
const TInt KDRMHelperDefaultCountThreshold = 3;
const TInt KDRMHelperDefaultTimeThreshold = 7;
const TInt KDRMHelperDefaultPercentageThreshold = 10;

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class DRMCommon;
class CDRMRightsConstraints;
class CEikDocument;
class CDRMRights;
class CStringResourceReader;

// CLASS DECLARATION

/**
*  Helper class for wrapping CDRMRightsConstraints.
*
*  @lib drmhelper.lib
*  @since Series 60 2.1
*/
class CDRMHelperRightsConstraints : public CBase
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        static CDRMHelperRightsConstraints* NewL( 
            CDRMRightsConstraints* aConstraints );
        static CDRMHelperRightsConstraints* NewLC( 
            CDRMRightsConstraints* aConstraints );
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CDRMHelperRightsConstraints();

    public: // New functions

        /**
        * checks if the object contains any restrictions 
        * or if usage is unconstrained.        
        * @return ETrue if usage is unconstrained
        */
        IMPORT_C TBool FullRights();

        /**
        * checks if the object contains only preview rights 
        * @return ETrue if object contains only preview rights
        */
        IMPORT_C TBool IsPreview();

        /**
        * Gets number of counts left and number of original counts.
        * Leaves with KErrNotFound if object doesn't have count based rights.
        * @param aCounter: (out) counts left
        * @param aOriginalCounter: (out) number of counts when stored to 
        *                          rights db
        * @return -
        */
        IMPORT_C void GetCountersL( TUint32& aCounter, 
            TUint32& aOriginalCounter );

        /**
        * Gets start time of time based rights.
        * Leaves with KErrNotFound if object doesn't have time based rights.
        * @param aStartTime: (out) start time
        * @return -
        */
        IMPORT_C void GetStartTimeL( TTime& aStartTime );

        /**
        * Gets end time of time based rights.
        * Leaves with KErrNotFound if object doesn't have time based rights.
        * @param aEndTime: (out) start time
        * @return -
        */
        IMPORT_C void GetEndTimeL( TTime& aEndTime );

        /**
        * Gets interval time constraint.
        * Leaves with KErrNotFound if object doesn't have interval constraint.
        * @param aInterval: (out) interval
        * @return -
        */
        IMPORT_C void GetIntervalL( TTimeIntervalSeconds& aInterval );

        /**
        * Gets start time of activated interval constraint.
        * Leaves with KErrNotFound if interval has not been started yet.
        * @param aStartTime: (out) start time of activated interval
        * @return -
        */
        IMPORT_C void GetIntervalStartL( TTime& aStartTime );

    private:

        /**
        * C++ default constructor.
        */
        CDRMHelperRightsConstraints( CDRMRightsConstraints* aConstrains );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:    // Data
        // pointer to CDRMRightsConstraints object
        CDRMRightsConstraints* iConstraints;
    };

/**
*  Handles some error situations DRM-aware applications may encounter.
*
*  @lib drmhelper.lib
*  @since Series 60 2.1
*/
class CDRMHelper : public CBase, public MApaEmbeddedDocObserver
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CDRMHelper* NewL( CCoeEnv& aCoeEnv );
        IMPORT_C static CDRMHelper* NewLC( CCoeEnv& aCoeEnv );

        /**
        * Two-phased constructor.
        * @since Series 60 2.6
        */
        IMPORT_C static CDRMHelper* NewL();
        IMPORT_C static CDRMHelper* NewLC();
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CDRMHelper();

    public: // New functions
        
        /**
        * Handles error situations 'rights expired', 'no rights' and
        * 'rights database corrupted'.
        * @param aError: error code returned by DRM engine
        * @param aFileName: full path to file
        * @return 
        * - Button code, if user selected "buy rights" or "launch rights 
        *   manager" in query.
        * - 0 if user selected "No", "Back" or "Cancel" (or whatever which 
        *   just dismiss the query)
        * - 0 if just a simple error note is displayed
        */
        IMPORT_C virtual TInt HandleErrorL( TInt aError, 
           const TDesC& aFileName );

        /**
        * Check rights for the file. If there is less than given amount 
        * of usage time/count left, one of the following note is displayed
        * depending on situation:
        * 'Usage rights about to expire. View details?'
        * 'Usage rights about to expire. %N days left. View details?'
        * 'Usage rights about to expire. 1 day left. View details?'
        * 'Usage rights about to expire. %N counts left. View details?'
        * 'Usage rights about to expire. 1 count left. View details?'
        * It also checks that rights are valid and displays appropriate note,
        * if they are not.
        * @param aFileName: Full path to file
        * @param aCount: Threshold value for count limit
        * @param aDays: Threshold value for time limit in days
        * @return Button code
        */
        IMPORT_C TInt CheckRightsAmountL( const TDesC& aFileName, 
            TInt aCount = KDRMHelperDefaultCountThreshold, 
            TInt aDays = KDRMHelperDefaultTimeThreshold );

        /**
        * Check rights for the file. If there is less than given amount 
        * of usage time/count left, one of the following note is displayed
        * depending on situation:
        * 'Usage rights about to expire. View details?'
        * 'Usage rights about to expire. %N days left. View details?'
        * 'Usage rights about to expire. 1 day left. View details?'
        * 'Usage rights about to expire. %N counts left. View details?'
        * 'Usage rights about to expire. 1 count left. View details?'
        * It also checks that rights are valid and displays appropriate note,
        * if they are not.
        * @param aUri: Content URI
        * @param aCount: Threshold value for count limit
        * @param aDays: Threshold value for time limit in days
        * @return Button code
        */
        IMPORT_C TInt CheckRightsAmountL( const TDesC8& aUri, 
            TInt aCount = KDRMHelperDefaultCountThreshold, 
            TInt aDays = KDRMHelperDefaultTimeThreshold );

        /**
        * Check rights for the file. If there is less than aThreshold percent 
        * of usage time/count left, one of the following note is displayed
        * depending on situation:
        * 'Usage rights about to expire. View details?'
        * 'Usage rights about to expire. %N days left. View details?'
        * 'Usage rights about to expire. 1 day left. View details?'
        * 'Usage rights about to expire. %N counts left. View details?'
        * 'Usage rights about to expire. 1 count left. View details?'
        * It also checks that rights are valid and displays appropriate note,
        * if they are not.
        * @param aFileName: Full path to file
        * @param aThreshold: Threshold value in percents for displaying the note
        * @return Button code
        */
        IMPORT_C TInt CheckRightsPercentL( const TDesC& aFileName, 
            TInt aThreshold = KDRMHelperDefaultPercentageThreshold );

        /**
        * Launches DRM Rights Manager UI embedded with details view related 
        * to given file.
        * @param aFileName: Full path to file
        * @return -
        */
        IMPORT_C virtual void LaunchDetailsViewEmbeddedL( 
            const TDesC& aFileName );

        /**
        * Launches DRM Rights Manager UI embedded with details view related 
        * to given content.
        * @param aContentURI: URI of the content
        * @return -
        */
        IMPORT_C virtual void LaunchDetailsViewEmbeddedL( 
            const HBufC8* aContentURI );

        /**
        * Gets details of rights object associated of given file.
        * @param aFileName: Full path to file
        * @param aIntent: bitmask of DRMCommon::EPlay, DRMCommon::EDisplay, 
        *                 DRMCommon::EExecute and DRMCommon::EPrint
        * @param aExpired: (out) ETrue if rights are expired
        * @param aSendingAllowed: (out) ETrue if content can be sent
        * @param aPlay: (out) play constraints, must be deleted by caller
        * @param aDisplay: (out) display constraints, must be deleted by caller
        * @param aExecute: (out) execute constraints, must be deleted by caller
        * @param aPrint: (out) print constraints, must be deleted by caller
        * @return -
        */
        IMPORT_C virtual void GetRightsDetailsL( const TDesC& aFileName, 
            TUint32 aIntent, TBool& aExpired, TBool& aSendingAllowed, 
            CDRMHelperRightsConstraints*& aPlay, 
            CDRMHelperRightsConstraints*& aDisplay, 
            CDRMHelperRightsConstraints*& aExecute, 
            CDRMHelperRightsConstraints*& aPrint );

        /**
        * Registers given content to be used as an automated content. This
        * function is used when registering application listens expiry 
        * notifications itself
        * @param aURI: content URI
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt SetAutomated( const TDesC8& aURI );

        /**
        * Registers given content to be used as an automated content. This
        * function is used when registering application listens expiry 
        * notifications itself.
        * @param aFileName: Full path to file
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt SetAutomated( const TDesC& aFilename );

        /**
        * Displays the confirmation query about setting given content as an
        * automated content. Note that this function does not actually
        * register content, just displays the note
        * @param aURI: content URI
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt ShowAutomatedNote( const TDesC8& aURI );

        /**
        * Displays the confirmation query about setting given content as an
        * automated content. Note that this function does not actually
        * register content, just displays the note
        * @param aFileName: Full path to file
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt ShowAutomatedNote( const TDesC& aFilename );

        /**
        * Registers given content to be used as an automated content. This
        * function is used when phone application listens expiry notifications.
        * @param aURI: content URI
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt SetAutomatedPassive( const TDesC8& aURI );

        /**
        * Registers given content to be used as an automated content. This
        * function is used when phone application listens expiry notifications.
        * @param aFileName: Full path to file
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt SetAutomatedPassive( const TDesC& aFilename );

        /**
        * Registers given content to be used as an automated content without
        * confirmation query.
        * @param aURI: content URI
        * @param aActive: ETrue if registering application itself listens
        * expiry notifications
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt SetAutomatedSilent( const TDesC8& aURI, TBool aActive );

        /**
        * Registers given content to be used as an automated content without
        * confirmation query.
        * @param aURI: content URI
        * @param aActive: ETrue if registering application itself listens
        * expiry notifications
        * @return System wide error code (KErrCancel if user pressed no to 
        * query).
        * @since Series 60 2.6
        */
        IMPORT_C TInt SetAutomatedSilent( const TDesC& aFilename, 
            TBool aActive );

        /**
        * Unregisters given content to be used as an automated content.
        * @param aURI: content URI
        * @return System wide error code.
        * @since Series 60 2.6
        */
        IMPORT_C TInt RemoveAutomated( const TDesC8& aURI );

        /**
        * Unregisters given content to be used as an automated content.
        * @param aFileName: Full path to file
        * @return System wide error code.
        * @since Series 60 2.6
        */
        IMPORT_C TInt RemoveAutomated( const TDesC& aFilename );

        /**
        * Unregisters given content to be used as an automated content.
        * This function must be used when content was registered using 
        * SetAutomatedPassive.
        * @param aURI: content URI
        * @return System wide error code.
        * @since Series 60 2.6
        */
        IMPORT_C TInt RemoveAutomatedPassive( const TDesC8& aURI );

        /**
        * Unregisters given content to be used as an automated content.
        * This function must be used when content was registered using 
        * SetAutomatedPassive.
        * @param aFileName: Full path to file
        * @return System wide error code.
        * @since Series 60 2.6
        */
        IMPORT_C TInt RemoveAutomatedPassive( const TDesC& aFilename );

        /**
        * Checks if given content can be set as an automated content.
        * @param aURI: content URI
        * @param aValue: ETrue if content can be set as automated.
        * @return System wide or DRM specific error code.
        * @since Series 60 2.6
        */
        IMPORT_C TInt CanSetAutomated( const TDesC8& aURI, TBool& aValue );

        /**
        * Checks if given content can be set as an automated content.
        * @param aFileName: Full path to file
        * @param aValue: ETrue if content can be set as automated.
        * @return System wide or DRM specific error code.
        * @since Series 60 2.6
        */
        IMPORT_C TInt CanSetAutomated( const TDesC& aFilename, TBool& aValue );

        /**
        * Informs DRMHelper that idle-screen has been activated.
        * @return -
        * @since Series 60 2.6
        */
        IMPORT_C void IndicateIdle();

    public: // Functions from base classes

        /**
        * From MApaEmbeddedDocObserver NotifyExit Implements the required 
        * behaviour when the editing of an embedded document completes.
        * @param aMode state of the document
        * @return -
        */
        void NotifyExit( TExitMode aMode );

    protected:  // New functions
        
        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    protected:  // Functions from base classes
        
        /**
        * From ?base_class ?member_description
        */
        //?type ?member_function();

    private:

        /**
        * C++ default constructor.
        */
        CDRMHelper( CCoeEnv& aCoeEnv );
        CDRMHelper();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        // Prohibit copy constructor if not deriving from CBase.
        // ?classname( const ?classname& );
        // Prohibit assigment operator if not deriving from CBase.
        // ?classname& operator=( const ?classname& );

        /**
        * Display query dialog
        */
        TInt DisplayQueryL( TInt aTextResourceId );
        TInt DisplayQueryL( TInt aTextResourceId, TInt aValue );
        TInt DisplayQueryL( TInt aTextResourceId, const TDesC& aString );
        TInt DisplayQueryL( 
        	TInt aTextResourceId, 
        	const TDesC& aString, 
            TInt aValue,
        	TInt aStringPos = -1,
        	TInt aValuePos = -1 );
        TInt DisplayQueryL( TDesC& aPromptText );

        /**
        * Display information note
        */
        void DisplayInfoNoteL( TInt aTextResourceId );
        void DisplayInfoNoteL( TInt aTextResourceId, const TDesC& aString );
        void DisplayInfoNoteL( TDesC& aPromptText );

        /**
        * Launch browser embedded
        */
        void LaunchBrowserL( const HBufC8* aUrl );

        /**
        * Get rights-issuer URI from DCF file
        */
        void GetRightsIssuerL( const TDesC& aFileName, HBufC8*& aIssuer );

        /**
        * Get time and count based constraints
        */
        TInt GetCounts( CDRMRightsConstraints* aConstraint, 
            TUint32& aOriginalCount, TTimeIntervalDays& aDuration );

        TInt GetCounts( CDRMRightsConstraints* aConstraint,
            TUint32& aCountLeft, TTime& aEndTime );

        /**
        * Launch rights manager UI
        */
        void LaunchRightsManagerUiL( const TDesC& aParam16 );

        /**
        * Form string needed to launch rights manager UI embedded.
        */
        void CreateLaunchParamL( TUint32 aLocalId, const HBufC8* aUrl, 
            HBufC*& aLaunchParam );

        /**
        * Strip path and extension from given filename.
        * Caller is responsible for freeing returned buffer
        */
        TPtrC StripPathAndExtension( const TDesC& aFileName );

        /**
        * Get expiration details of file.
        * Returns DRMCommon::ENoRights if no rights object found or
        * CDRMRights::TExpiration value
        */
        TInt GetExpirationDetails( const TDesC& aFileName );

        /**
        * Get expiration time of given rights object
        */
        TInt CalculateEndTime( CDRMRights* aRights, TInt aIntent, 
            TTime& aEndTime, TBool& aInactive );

        /**
        * Get end time of given constraint
        */
        TInt GetEndTime( CDRMRightsConstraints* aConstraint, 
            TTime& aEndTime, TBool& aInactive );
        
        /**
        * Register content as automated
        */
        TInt DoSetAutomatedL( const TDesC8& aURI, TBool aActive, 
            const HBufC8* aMimeType );

        /**
        * Display confirmation query about setting as automated. Does not 
        * actually register.
        */
        TInt DoShowAutomatedNoteL( const TDesC8& aURI, 
            const HBufC8* aMimeType );

        /**
        * Register content as automated without showing any queries
        */
        TInt DoSetAutomatedSilent( const TDesC8& aURI, TBool aActive );

        /**
        * Returns default intent for the mimetype
        */
        TInt Intent( const HBufC8* aMimeType );
        
        /**
        * Checks if content can be used as automated content
        */
        TInt CanSetAutomated( const TDesC8& aURI, const HBufC8* aMimeType, 
            TBool& aValue );
            
        /**
        * Gets mimetype based on content URI
        */
        HBufC8* MimeTypeFromURIL( const TDesC8& aURI );
        
        /**
        * Gets corresponding filename (including full path) based on content 
        * URI
        */
        TInt GetFileNameFromURIL( const TDesC8& aURI, TFileName& aFileName );

        /**
        * Get start time of given rights object
        */
        TInt GetStartTime( CDRMRights* aRights, TInt aIntent, 
            TTime& aStartTime );

        /**
        * Displays info note of rights that are not yet valid 
        */
        TInt ShowFutureNoteL( const TDesC8& aURI, 
            const HBufC8* aMimeType );

    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;
    
    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        CCoeEnv*                iCoeEnv;

        // DRM engine
        DRMCommon*              iDRMCommon;

        // document used when rights manager ui is launched embedded
        CEikDocument*           iDoc;

        // used to make launching rights manager ui synchronous
        CActiveSchedulerWait    iWait;
   
        RDRMHelper              iHelperServer;
        
        // is CoeEnv used
        TBool                   iUseCoeEnv;

        // Used to read resources when CoeEnv is not available
        CStringResourceReader*  iStringResourceReader;
        
    public:     // Friend classes
    protected:  // Friend classes
    private:    // Friend classes

    };

#endif      // __DRMHELPER_H__   
            
// End of File

