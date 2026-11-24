/*
* ============================================================================
*  Name        : DRMCommon.h
*  Part of     : DRM 3 API
*  Interface   : public interface, DRM 3 API
*  Description : Declaration of class DRMCommon for accessing common
*                DRM functions
*  Version     : 0.0
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef DRMCOMMON_H
#define DRMCOMMON_H

#include <e32base.h>

// TEST DEFINITION
#ifdef MODULE_TESTING
#define PROTECTED public
#define PRIVATE public
#else
#define PROTECTED protected
#define PRIVATE private
#endif

// CONSTANTS

// The number of bytes we need for inspecting a DCF file
// Includes the length, the content ID and the MIME type fields

const TUint KDrmMaxContentInfoSize = 1 + 1 + 1 + 256 + 256 + 5 + 5;

// FORWARD DECLARATIONS
class TDataType;
class DRMEngineSession;

// CLASS DECLARATION

/**
*  CDRMRightsConstraints: Encapsulates rights constaints for a specific right.
*
*  @lib    DRMCommon.dll
*  @since  2.5
*/
class CDRMRightsConstraints: public CBase
    {
public:     // Data Types
    enum TConstraintPriority
        {
        ENoConstraints = 8,
        ETime = 7,
        ETimeInterval = 6,
        ETimeIntervalCount = 5,
        ETimeCount = 4,
        EInterval = 3,
        EIntervalCount = 2,
        ECount = 1
        };
public:  // Constructors and destructor
    
    /**
    * Two-phased constructor.
    */
    IMPORT_C static CDRMRightsConstraints* NewL(void);
    
    /**
    * Destructor.
    */
    IMPORT_C virtual ~CDRMRightsConstraints(void);
    
public: // New functions
    
    /**
    * FullRights
    * 
    * The FullRights function checks if the object contains any restrictions 
    * or if usage is unconstrained.
    *
    * @since  2.5
    * @return ETrue if this object represents unconstrained rights, EFalse if
    *         there are some constraints set
    */
    IMPORT_C TBool FullRights(void);
    
    /**
    * IsPreview
    * 
    * The function checks if the object represents a preview constraint.
    *
    * @since  2.5
    * @return ETrue if this object represents a preview constraint, EFalse
    *         otherwise
    */
    IMPORT_C TBool IsPreview(void);

    /**
    * GetConstraintInfo
    * 
    * The fucntion retunrs expiration and constraint details of the object  
    *
    * @since  2.5
    * @param  aExpiration: return parameter for the expiration detail of the
    *         object. EValid, EExpired, EFuture
    * @param  aConstType: return parameter for the constraint details of the
    *         object. A bitmask combination of ETimeBased, EInActiveInterval,
    *         ECountBased. Or only ENoConstraints 
    * @return Priority value of the object, if the details were returned
    *         succesfully. Priority value defines, which constraint is used
    *         during decryption. The highest one is consumed first.
    *         EInvalidRights if details cannot be retrieved. 
    */
    IMPORT_C TInt GetConstraintInfo(
        TUint32& aExpiration,
        TUint32& aConstType);

    /**
    * GetExpirationDetails
    * 
    * The function returns the end time and amount of counts left of the object.
    * 
    * @since  2.5
    * @param  aEndTime: return parameter for the end time value of the object.
    *         If end time restriction is not defined, parameter is set to 0.
    * @param  aCountsLeft: return parameter for amount of counts left. If count
    *         restriction is not defined, parameter is set to -1.          
    * @return EOk if details were retrieved successfully.
    * 
    */
    IMPORT_C TInt GetExpirationDetails(
        TTime& aEndTime,
        TInt& aCountsLeft);
	
    /**
    * GetCounters
    * 
    * This function returns the current value of the count restriction and
    * original value of the count restriction(value when the rights object
        * was added to the rights database)
    *
    * @since  2.5
    * @param  aCounter: out parameter for the current counter value
    * @param  aOriginalCounter: out parameter for the original counter value
    * @return EOk if the counters were returned successfully, ENoRights if 
    *         the object does not contain count based restrictions
    */
    IMPORT_C TInt GetCounters(
        TUint32& aCounter, 
        TUint32& aOriginalCounter);
    
    /**
    * GetStartTime
    * 
    * This function returns the start time constraint.
    *
    * @since  2.5
    * @param  aStartTime: out parameter for the start time restriction
    * @return EOk if the time restriction were returned successfully, 
    *         ENoRights if the object does not contain a start time
    *         restrictions
    */
    IMPORT_C TInt GetStartTime(
        TTime& aStartTime);
    
    /**
    * GetEndTime
    * 
    * This function returns the end time constraint.
    *
    * @since  2.5
    * @param  aEndTime: out parameter for the end time restriction
    * @return EOk if the time restriction were returned successfully, 
    *         ENoRights if the object does not contain an end time
    *         restrictions
    */
    IMPORT_C TInt GetEndTime(
        TTime& aEndTime);
    
    /**
    * GetInterval
    * 
    * This function returns interval time constraint
    *
    * @since  2.5
    * @param  anInterval: out parameter for the interval restriction
    * @return EOk if the interval time restriction was returned successfully, 
    *         ENoRights if the object does not contain interval based restrictions
    */
    IMPORT_C TInt GetInterval(
        TTimeIntervalSeconds& anInterval);
    
    /**
    * GetIntervalStart
    * 
    * This function returns the start time of an activated interval
    *
    * @since  2.5
    * @param  anInterval: out parameter for the start of an activated interval 
    * @return EOk if the interval start time was returned successfully, 
    *         ENoRights if the interval has not been started yet
    */
    IMPORT_C TInt GetIntervalStart(
        TTime& aStartTime);
    
    /**
    * SetCounters
    * 
    * Sets the counter instance variables of the rights constraint
    *
    * @since  2.5
    * @param  aCounter: the current counter value
    * @param  aOriginalCounter: the original counter value
    * @return EOk if the counters were set successfully
    */
    IMPORT_C TInt SetCounters(
        TUint32 aCounter, 
        TUint32 aOriginalCounter);
    
    /**
    * SetStartTime
    * 
    * Sets the start time constraint.
    *
    * @since  2.5
    * @param  aStartTime: the start time restriction
    * @return EOk if the time restriction was set successfully, 
    *         ENoRights if the object does not contain a start time
    *         restrictions
    */
    IMPORT_C TInt SetStartTime(
        TTime aStartTime);
    
    /**
    * SetEndTime
    * 
    * Sets the end time constraint.
    *
    * @since  2.5
    * @param  aEndTime: the end time restriction
    * @return EOk if the time restriction was set successfully, 
    */
    IMPORT_C TInt SetEndTime(
        TTime aEndTime);
    
    /**
    * SetInterval
    * 
    * Sets the interval time constraint
    *
    * @since  2.5
    * @param  anInterval: the interval restriction
    * @return EOk if the interval time restriction was set successfully.
    */
    IMPORT_C TInt SetInterval(
        TTimeIntervalSeconds anInterval);
    
    /**
    * SetIntervalStart
    * 
    * Sets the interval start time constraint
    *
    * @since  2.5
    * @param  anInterval: the interval start restriction
    * @return EOk if the interval start restriction was set successfully.
    */
    IMPORT_C TInt SetIntervalStart(
        TTime aStartTime);
    
    /**
    * operator=
    * 
    * Assignment operator.
    *
    * @since  2.5
    * @param  aConstraint: constraint to copy data from
    * @return a copy of the aConstraint parameter.
    */
    IMPORT_C CDRMRightsConstraints& operator=(
        CDRMRightsConstraints& aConstraint);
    
    PROTECTED:
    
    /**
    * Default constructor.
    */
    IMPORT_C CDRMRightsConstraints(void);
    
    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL(void);
    
    
PROTECTED: // Data
    
    // Set to ETrue if no restrictions apply.
    TBool iFullRights;
    
    // If not NULL, points to the current available consumption counts.
    TUint32* iCount;
    
    // If not NULL, points to the original available consumption counts.
    TUint32* iOriginalCount;
    
    // If not NULL, points to the start of the usable time.
    TTime* iStartTime;
    
    // If not NULL, points to the end of the usable time.
    TTime* iEndTime;
    
    // If not NULL, points to the usable time interval.
    TTimeIntervalSeconds* iInterval;
    
    // If not NULL, points to the start of an activated interval.
    TTime* iIntervalStart;
    
    };

// CLASS DECLARATION

/**
*  CDRMRights: Encapsulates a single rights object.
*
*  @lib    DRMCommon.dll
*  @since  2.5
*/
class CDRMRights: public CBase
    {
public:     // Data Types
    enum TExpiration
        {
        EValidRights = 100,
        EFutureRights = 10,
        EExpiredRights = 1 
        };
    
    enum TConstraintType
        {
        ENoConstraints = 0x0001,
        ETimeBased = 0x0002,
        EInActiveInterval = 0x0004,
        ECountBased = 0x0008
        };
    
    enum TRestriction
        {
        EFullRights = 1, 
        ERestrictedRights,
        EPreviewRights
        };
    
    enum TAdditionalRestriction
        {
        ENoRestriction = 0x00000000,
        ENoRingingTone = 0x00000001,
        EReserved1     = 0x00000002,
        EReserved2     = 0x00000004,
        EReserved3     = 0x00000008,
        EReserved4     = 0x00000010,
        EReserved5     = 0x00000020,
        EReserved6     = 0x00000040,
        EReserved7     = 0x00000080                                                
        };    

public:  // Constructors and destructor
    
    /**
    * Two-phased constructor.
    */
    IMPORT_C static CDRMRights* NewL(void);
    
    /**
    * Destructor.
    */
    IMPORT_C virtual ~CDRMRights(void);
    
public: // New functions
    
    /**
    * GetContentURI
    * 
    * This function returns the content URI of the object
    *
    * @since  2.5
    * @param  aContentURI: out parameter for the content URI.
    * @return EOk if the URI was returned successfully.
    */
    IMPORT_C TInt GetContentURI(
        HBufC8*& aContentURI);
    
    /**
    * GetLocalID
    * 
    * This function returns the local ID of the object
    *
    * @since  2.5
    * @return the local ID.
    */
    IMPORT_C TUint32 GetLocalID(void);
    
    /**
    * GetAddTime
    * 
    * This function returns the time when the rights object was added to the
    * rights database
    *
    * @since  2.5
    * @param  aTime: out parameter for the time.
    */
    IMPORT_C void GetAddTime(
        TTime& aTime);
    
    /**
    * GetRightsInfo
    * 
    * This function returns the restriction details associated with given
    * permission.
    *
    * @since  2.5
    * @param  aConstraintSpec: The permissions to be checked defined as a 
    *         bitmask combination of EPlay, EDisplay, EExecute and EPrint
    * @param  aRestriction: return paramer for the restriction detail of the
    *         object: EFullRights, ERestrictedRights or EPreviewRights
    * @param  aExpiration: return parameter for the expiration detail of the
    *         object: EValid, EExpired, EFuture
    * @param  aConstType: return parameter for the constraint details of the
    *         object. ETimeBased, EInActiveInterval, ECountBased or ENoConstraints 
    * @return Priority value of the object, if the details were returned
    *         succesfully. Priority value defines, which object is used
    *         during decryption. The value is calculated with formula:
    *         TConstraintPriority * TRightsExpiration.
    *         ENoRights if no rights for given permissions.	      
    */
    IMPORT_C TInt GetRightsInfo(
        TUint32 aConstraintSpec,
        TRestriction& aRestriction,
        TExpiration& aExpiration,
        TUint32& aConstType);

    /**
    * GetExpirationDetails
    * 
    * The function returns the end time and amount of counts left of the object
    * associated with given permission. The use of this method is only recommended
    * for objects, which contain a end time or a count restriction. The constraint
    * type information can be retrieved with e.g. GetRightsInfo -function.
    * In cases of full rights and inactive interval rights the aEndTime is set to
    * 0 and the aCountsLeft is set to < 0.
    * 
    * @since  2.5
    * @param  aConstraintSpec: The permissions to be checked defined as a 
    *         bitmask combination of EPlay, EDisplay, EExecute and EPrint.
    * @param  aEndTime: return parameter for the end time value of the object.
    *         If end time restriction is not defined, parameter is set to 0.
    * @param  aCountsLeft: return parameter for amount of counts left. If count
    *         restriction is not defined, parameter is set to -1.          
    * @return EOk if details were retrieved successfully. ENoRights if no rights
    *         for given permissions.	 
    */
    IMPORT_C TInt GetExpirationDetails(
        TUint32 aConstraintSpec,
        TTime& aEndTime,
        TInt& aCountsLeft);
    
    /**
    * GetPlayRight
    * 
    * This function returns the constraints associated with the play right.
    *
    * @since  2.5
    * @param  aConstraint: out parameter for the constraints associated with
    *         this right. It must be deleted by the caller.
    * @return EOk if the right exists and the associated restrictions were 
    *         returned successfully, ENoRights if the object does not contain
    *         the given right.
    */
    IMPORT_C TInt GetPlayRight(
        CDRMRightsConstraints*& aConstraint);
    
    /**
    * GetDisplayRight
    * 
    * This function returns the constraints associated with the display right.
    *
    * @since  2.5
    * @param  aConstraint: out parameter for the constraints associated with
    *         this right. It must be deleted by the caller.
    * @return EOk if the right exists and the associated restrictions were 
    *         returned successfully, ENoRights if the object does not contain
    *         the given right.
    */
    IMPORT_C TInt GetDisplayRight(
        CDRMRightsConstraints*& aConstraint);
    
    /**
    * GetPrintRight
    * 
    * This function returns the constraints associated with the print right.
    *
    * @since  2.5
    * @param  aConstraint: out parameter for the constraints associated with
    *         this right. It must be deleted by the caller.
    * @return EOk if the right exists and the associated restrictions were 
    *         returned successfully, ENoRights if the object does not contain
    *         the given right.
    */
    IMPORT_C TInt GetPrintRight(
        CDRMRightsConstraints*& aConstraint);
    
    /**
    * GetExecuteRight
    * 
    * This function returns the constraints associated with the execute right.
    *
    * @since  2.5
    * @param  aConstraint: out parameter for the constraints associated with
    *         this right. It must be deleted by the caller.
    * @return EOk if the right exists and the associated restrictions were 
    *         returned successfully, ENoRights if the object does not contain
    *         the given right.
    */
    IMPORT_C TInt GetExecuteRight(
        CDRMRightsConstraints*& aConstraint);
    
    /**
    * GetContentURIAndLocalID
    * 
    * This function sets the content URI and local ID of the object.
    *
    * @since  2.5
    * @param  aContentURI: the new content URI.
    * @param  aLocalID: the new local ID.
    * @return EOk if the values were set successfully.
    */
    IMPORT_C TInt SetContentURIAndLocalID(
        HBufC8* aContentURI, 
        TUint32 aLocalID);
    
    /**
    * SetAddTime
    * 
    * Sets the add time of the object.
    *
    * @since  2.5
    * @param  aTime: the new add time.
    * @return EOk if the value was set successfully.
    */
    IMPORT_C void SetAddTime(
        TTime aTime);
    
    /**
    * SetPlayRight
    * 
    * This function sets the play constraints.
    *
    * @since  2.5
    * @param  aConstraint: the constraints associated with the play right.
    *         It must not be deleted by the caller. It will be owned by the
    *         CDRMRights object.
    * @return EOk if the restrictions were set successfully
    */
    IMPORT_C TInt SetPlayRight(
        CDRMRightsConstraints* aConstraint);
    
    /**
    * SetDisplayRight
    * 
    * This function sets the constraints.
    *
    * @since  2.5
    * @param  aConstraint: the constraints associated with the display right.
    *         It must not be deleted by the caller. It will be owned by the
    *         CDRMRights object.
    * @return EOk if the restrictions were set successfully
    */
    IMPORT_C TInt SetDisplayRight(
        CDRMRightsConstraints* aConstraint);
    
    /**
    * SetPrintRight
    * 
    * This function sets the print constraints.
    *
    * @since  2.5
    * @param  aConstraint: the constraints associated with the print right.
    *         It must not be deleted by the caller. It will be owned by the
    *         CDRMRights object.
    * @return EOk if the restrictions were set successfully
    */
    IMPORT_C TInt SetPrintRight(
        CDRMRightsConstraints* aConstraint);
    
    /**
    * SetExecuteRight
    * 
    * This function sets the execute constraints.
    *
    * @since  2.5
    * @param  aConstraint: the constraints associated with the execute right.
    *         It must not be deleted by the caller. It will be owned by the
    *         CDRMRights object.
    * @return EOk if the restrictions were set successfully
    */
    IMPORT_C TInt SetExecuteRight(
        CDRMRightsConstraints* aConstraint);
    
    /**
    * operator=
    * 
    * Assignment operator.
    *
    * @since  2.5
    * @param  aRight: object to copy data from
    * @return a copy of the aRight parameter.
    */
    IMPORT_C CDRMRights& operator=(
        CDRMRights& aRight);
    
PROTECTED:
    
    /**
    * Default constructor.
    */
    IMPORT_C CDRMRights(void);
    
    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL(void);
    
    
public:
    // bitvector for information about the content
    TUint32 iAdditionalRestriction;
    
    
PROTECTED: // Data
    // Holds the content URI.
    HBufC8* iContentURI;
    
    // The local ID distinguishes different rights objects for the same URI.
    TUint32 iLocalID;
    
    // The time the rights object was added to the rights database.
    TTime iAddTime;
    
    // If not NULL, holds the play right and its restrictions.
    CDRMRightsConstraints* iPlayRight;
    
    // If not NULL, holds the display right and its restrictions.
    CDRMRightsConstraints* iDisplayRight;
    
    // If not NULL, holds the execute right and its restrictions.
    CDRMRightsConstraints* iExecuteRight;
    
    // If not NULL, holds the print right and its restrictions.
    CDRMRightsConstraints* iPrintRight;
    
    };

// CLASS DECLARATION

/**
*  DRMCommon: provides common DRM functions.
*
*  @lib    DRMCommon.dll
*  @since  2.0
*/
class DRMCommon: public CBase
    {
public:     // Data Types
    enum
        {
        EPlay = 0x0001, 
        EDisplay = 0x0002, 
        EExecute = 0x0004, 
        EPrint = 0x0008, 
        EInstall = 0x0010, 
        };

    enum TConsumeAction
        {
        EStart,
        EFinish,
        };
    
    enum
        {
        EOk = KErrNone, 
        EGeneralError = -30100, 
        EUnknownMIME = -30101, 
        EVersionNotSupported = -30102, 
        ESessionError = -30103, 
        ENoRights = -30104, 
        ERightsDBCorrupted = -30105, 
        EUnsupported = -30106, 
        ERightsExpired = -30107, 
        EInvalidRights = -30108,
        EPaddingFailed = -30109,
        EFileError = -30110
        };
    
    enum TContentProtection
        {
        ENoDCFFile, 
        EForwardLocked, 
        ESuperDistributable
        };
    
    enum TOMALevel
        {
        EOMA_None, 
        EOMA_1_0
        };
    
    enum
        {
        EForwardLock = 0x0001, 
        ECombinedDelivery = 0x0002, 
        ESeparateDelivery = 0x0004, 
        ESuperDistribution = 0x0008
        };
    
public:  // Constructors and destructor
    
    /**
    * Two-phased constructor.
    */
    IMPORT_C static DRMCommon* NewL(void);
    
    /**
    * Destructor.
    */
    IMPORT_C virtual ~DRMCommon(void);
    
    public: // New functions
    
    /**
    * Version
    *
    * Returns the version of this API.
    *
    * @since  2.0
    * @return Version of the API
    */
    IMPORT_C static TVersion Version(void);
    
    /**
    * ServerVersion
    * 
    * Returns the version of the DRM Engine.
    *
    * @since  2.0
    * @return Version of the DRM Engine
    */
    IMPORT_C static TVersion ServerVersion(void);
    
    /**
    * Connect
    *
    * Connect to the DRM Engine.
    *
    * @since  2.0
    * @return EOk if the connection has been made
    */
    IMPORT_C TInt Connect(void);
    
    /**
    * Disconnect
    *
    * Disconnect the current connection.
    *
    * @since  2.0
    * @return EOk if the connection has been disconnected
    */
    IMPORT_C TInt Disconnect(void);
    
    /**
    * CheckContentRights
    * 
    * Takes a Content URI and a rights specification.
    * Checks if the specified rights can be exercised with this content 
    * by looking up the content URI in the rights database and checking
    * the stored rights.
    *
    * @since  2.0
    * @param  aContentURI: the content URI of the content to be tested
    * @param  aRightsSpec: The rights to be checked defined as a bitmask
    *         combination of EPlay, EDisplay, EExecute and EPrint
    * @return EOk if all of the given rights can be exercised, otherwise
    *         or if the content URI cannot be found, ENoRights
    */
    IMPORT_C TInt CheckContentRights(
        const TDesC8& aContentURI, 
        TUint32 aRightsSpec);
    
    /**
    * CheckFileRights
    *
    * Takes a file name and a rights specification. Opens the given file
    * and checks if the specified rights can be exercised with this file 
    * by extracting the content URI from the file, looking up the content
    * URI in the rights database and checking the stored rights.
    *
    * @since  2.0
    * @param  aFileName: the name of the file to be tested.
    * @param  aRightsSpec: The rights to be checked defined as a bitmask
    *         combination of EPlay, EDisplay, EExecute and EPrint
    * @return EOk if all of the given rights can be exercised, otherwise
    *         or if the file is not a DCF file or if the content URI cannot
    *         be found, ENoRights. KErrArgument if the file is not a valid
    *         DCF file.
    */
    IMPORT_C TInt CheckFileRights(
        const TDesC& aFileName, 
        TUint32 aRightsSpec);
    
    /**
    * IsProtectedContent
    *
    * Takes a memory buffer containing a file and checks if it is a DCF file
    * or a regular file.
    *
    * @since  2.0
    * @param  aContent: memory buffer containing a file
    * @param  aProtection: return parameter, true if the file is a DCF file
    * @return EOk if the content could be checked.
    */
    IMPORT_C TInt IsProtectedContent(
        const TDesC8& aContent, 
        TBool& aProtection);
    
    /**
    * IsProtectedFile
    *
    * Takes a file name and checks if it is a DCF file or a regular file.
    *
    * @since  2.0
    * @param  aFileName: the name of the file to be tested.
    * @param  aProtection: return parameter, true if the file is a DCF file
    * @return EOk if the content could be checked.
    */
    IMPORT_C TInt IsProtectedFile(
        const TDesC& aFileName, 
        TBool& aProtection);
    
    /**
    * GetContentInfo
    *
    * Takes a memory buffer containing a DCF(or at least the header part
        * of it) and returns the protection for this content, the MIME type, 
    * Content URI and encrypted data length in out parameters.
    *
    * @since  2.0
    * @param  aContent: memory buffer containing a DCF
    * @param  aProtection: return parameter for the type of protection for
    *         this DCF
    * @param  aMIMEType: return parameter for the MIME type header field
    * @param  aContentURI: return parameter for the content URI header field
    * @param  aDataLength: return parameter for the length of the encrypted
    *         data
    * @return EOk if the information could be extracted from the DCF
    */
    IMPORT_C TInt GetContentInfo(
        const TDesC8& aContent, 
        TContentProtection& aProtection, 
        HBufC8*& aMIMEType, 
        HBufC8*& aContentURI, 
        TUint& aDataLength);
    
    /**
    * GetFileInfo
    * 
    * Takes the name of a DCF file, opens it and returns the protection for
    * this content, the MIME type, Content URI and encrypted data length in
    * out parameters.
    *
    * @since  2.0
    * @param  aFileName: the name of the file to be inspected
    * @param  aProtection: return parameter for the type of protection for
    *         this DCF
    * @param  aMIMEType: return parameter for the MIME type header field
    * @param  aContentURI: return parameter for the content URI header field
    * @param  aDataLength: return parameter for the length of the encrypted
    *         data
    * @return EOk if the information could be extracted from the DCF
    */
    IMPORT_C TInt GetFileInfo(
        const TDesC& aFileName, 
        TContentProtection& aProtection, 
        HBufC8*& aMIMEType, 
        HBufC8*& aContentURI, 
        TUint& aDataLength);
    
    /**
    * GetContentHeader
    *
    * Takes a memory buffer containing a DCF(or at least the header part of
    * it) and a header name and returns the value of the header field in an
    * out parameter. Return value specifies if the header has been found.
    * Search is case insensitive.
    *
    * @since  2.0
    * @param  aContent: memory buffer containing a DCF
    * @param  aHeaderName: Name of the header to look for
    * @param  aHeaderValue: return parameter for value of the header
    * @return EOk if the header was found
    */
    IMPORT_C TInt GetContentHeader(
        const TDesC8& aContent, 
        const TDesC8& aHeaderName, 
        HBufC8*& aHeaderValue);
    
    /**
    * GetFileHeader
    *
    * Takes the name of a DCF file and a header name, opens the DCF file and
    * returns the value of the header field in an out parameter. Return value
    * specifies if the header has been found. Search is case insensitive.
    *
    * @since  2.0
    * @param  aFileName: the name of the DCF file to be opened
    * @param  aHeaderName: Name of the header to look for
    * @param  aHeaderValue: return parameter for value of the header
    * @return EOk if the header was found
    */
    IMPORT_C TInt GetFileHeader(
        const TFileName& aFileName, 
        const TDesC8& aHeaderName, 
        HBufC8*& aHeaderValue);
    
    /**
    * GetSingleRightsObject
    *
    * Takes a content URI, a local ID and a rights object out parameter.
    * Looks up the rights object using the content URI and the local ID
    * and returns it in the out parameter.
    *
    * @since  2.5
    * @param  aContentURI: the content URI of the content to be tested.
    * @param  aLocalID: local ID of the rights object
    * @param  aRightsObject: Out parameter for the rights object. It has
    *         to be released by the caller.
    * @return EOk if the rights object could be retreived, ENoRights if
    *         no rights object exists.
    */
    IMPORT_C TInt GetSingleRightsObject(
        const TDesC8& aContentURI, 
        TUint32 aLocalID, 
        CDRMRights*& aRightsObject);
    
    /**
    * GetDetailedContentRights
    *
    * Takes a Content URI and an array out parameter. Fills the rights
    * specification array with the available rights by looking up the content
    * URI in the rights database and retrieving the stored rights. The array
    * parameter will contain a list of pointers to all rights object for the 
    * given content URI. The rights objects themselves can be distinguished by
    * their local ID.
    *
    * @since  2.5
    * @param  aContentURI: the content URI of the content to be tested.
    * @param  aRightsList: Out parameter for the available rights. It has to
    *         be released by the caller.
    * @return EOk if the rights could be retreived, ENoRights if no rights 
    *         object exists.
    */
    IMPORT_C TInt GetDetailedContentRights(
        const TDesC8& aContentURI, 
        RPointerArray<CDRMRights>*& aRightsList);
    
    /**
    * GetDetailedFileRights
    *
    * Takes a file name and a rights specification. Opens the given file and 
    * fills the rights specification array with the available rights by
    * looking up the content URI in the rights database and retrieving the
    * stored rights. The array parameter will contain a list of pointers to
    * all rights object for the given content URI. The rights objects
    * themselves can be distinguished by their local ID.
    *
    * @since  2.5
    * @param  aFileName: the name of the file to be tested.
    * @param  aRightsList: Out parameter for the available rights.
    * @return EOk if the rights could be retreived, if the file is not a DCF
    *         file or if the content URI cannot be found, ENoRights.
    */
    IMPORT_C TInt GetDetailedFileRights(
        const TDesC& aFileName, 
        RPointerArray<CDRMRights>*& aRightsList);
    
    /**
    * GetActiveRights
    *
    * Takes a Content URI and a rights specification. Finds all rights objects
    * associated with given URI and returns a possible active one. The out 
    * parameters will contain a pointer to the found rights object. The found
    * rights object can be expired. The details about expiration and constraints
    * of the rights can be retrieved with the CDRMRights::GetRightsInfo function. 
    *
    * @since  2.5
    * @param  aContentURI: the content URI of the content to be tested.
    * @param  aRightsSpec: The rights to be checked defined as a bitmask
    *		  combination of EPlay, EDisplay, EExecute and EPrint
    * @param  aRightsObject: Out parameter for the rights object. It has
    *         to be released by the caller.
    * @return EFullRights, ERestrictedRights, EPreviewRights if a possble active
    *         rights object was found. ENoRights if no rights object for given 
    *         content URI or permissions.
    */
    IMPORT_C TInt GetActiveRights(
        const TDesC8& aContentURI,
        TUint32 aRightsSpec,
        CDRMRights*& aRightsObject);
    
    /**
    * GetContentURIList
    *
    * Returns a list of all content URIs that have rights in the rights 
    * database.
    *
    * @since  2.5
    * @param  aURIList: Out parameter for the URI list.
    * @return Ok if the URI list could be retreived.
    */
    IMPORT_C TInt GetContentURIList(
        RPointerArray<HBufC8>*& aURIList);
    
    /**
    * DataTypesCount
    *
    * Returns the number of previously registered datatypes which are
    * supported by the DRM system and associated applications.
    *
    * @since  2.0
    * @param  aCount: Out parameter for the datatype count
    * @return EOk if the number of datatypes has been returned correctly
    */
    IMPORT_C TInt DataTypesCount(
        TInt& aCount);
    
    /**
    * SupportedDataType
    *
    * Returns a specific datatype which has been registered before by giving an index
    *
    * @since  2.0
    * @param  aIndex: Number of the datatype to return
    * @param  aDataType: Out parameter for the datatype
    * @return EOk if the datatype was returned correctly
    */
    
    IMPORT_C TInt SupportedDataType(
        const TInt aIndex, TDataType& aDataType);
    
    /**
    * StaticDataTypesCount
    *
    * Returns the number of default registered datatypes which are
    * supported by the DRM system and associated applications.
    *
    * @since  2.0
    * @param  aCount: Out parameter for the static datatype count
    * @return EOk if the number of datatypes has been returned correctly
    */
    IMPORT_C TInt StaticDataTypesCount(
        TInt& aCount);
    
    /**
    * SupportedDRMMethods
    *
    * Returns the supported DRM protection methods and the OMA compliance
    * level of the DRM engine
    *
    * @since  2.0
    * @param  aDRMMethod: Out parameter, bit mask containing any 
    *         combination of EForwardLock, ECombinedDelivery, 
    *         ESeparateDelivery etc.
    * @param  aOMALevel: OMA compliance of the DRM engine
    * @return DRMCommon error code
    */
    
    IMPORT_C TInt SupportedDRMMethods(
        TInt& aDRMMethod, TOMALevel& aOMALevel);

    /**
    * SetEstimatedArrival
    *
    * Sets the ETA of a rights object connected to the given content id
    * to the provided value
    *
    * @since    2.6
    * @param    aContentID : Content identifier
    * @param    aLogicalName : name of the content, maximum size 256 
    *                          characters
    * @param    aDeltaSeconds : The maximum time to wait for the arrival 
    *                           of rights  
    * @return   DRMCommon error core or Symbian OS error code
    */
    IMPORT_C TInt SetEstimatedArrival( 
        const TDesC8& aContentId,
        const TFileName& aLogicalName,
        const TTimeIntervalSeconds& aDeltaSeconds );

    /**
    * GetEstimatedArrival
    *
    * Gets the ETA of a rights object connected to the given content id
    * and the logical name
    *
    * @since    2.6
    * @param    aContentID : Content identifier
    * @param    aLogicalName : name of the content, maximum size 256 
    *                          characters
    * @param    aDeltaSeconds : The maximum time to wait for the arrival 
    *                           of rights  
    * @return   DRMCommon error core or Symbian OS error code
    */
    IMPORT_C TInt GetEstimatedArrival( 
        const TDesC8& aContentId,
        TFileName& aLogicalName,
        TTimeIntervalSeconds& aDeltaSeconds );        
                                   
PROTECTED:
    
    /**
    * C++ default constructor.
    */
    IMPORT_C DRMCommon(void);
    
    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL(void);
    
    /**
    * MapErrorCode
    *
    * Maps the error codes returned by the core engine to DRMCommon
    * error codes.
    *
    * @since  2.5
    * @param  aCode: core error code
    * @return DRMCommon error code.
    */
    IMPORT_C TInt MapErrorCode(
        const TInt aCode);
    
    };

#endif      // DRMCOMMON_H   

// End of File
