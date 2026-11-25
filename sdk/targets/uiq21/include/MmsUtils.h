// $Workfile: MmsUtils.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 47 $
// $Date: 31/01/02 12:14 $
//

/** @file
 * This file contains definitions of TMmsMediaObjectId, TMmsTransferProgress, TMmsMessageType and TMsvMmsEntry.
 */

#ifndef __MMSUTILS_H__
#define __MMSUTILS_H__


#include <msvstd.h>     //TMsvEntry


//forward declarations
class RReadStream;
class RWriteStream;
class CMsvSession;
class CMmsSettings;


// Global constants: UIDs
const TUid KUidMsgTypeMMS = {0x101F4A60};           ///< MTM UID for MMS
const TUid KUidMsvTechnologyGroupMms = {0x101F5420};

const TUid KUidMmsTransferProgress = {0x1000AABE};  ///< UID for TMmsTransferProgress

// Stream UIDs for message storage
const TUid KUidStreamMessage        = {0x101F4E56};    ///< Stream UID for the CMmsMessage object
const TUid KUidStreamHeaders        = {0x101F4E57};    ///< Stream UID for the CMmsHeaders object
const TUid KUidStreamMediaObjects   = {0x101F4E58};    ///< Stream UID for the CMmsMediaObjectList object
const TUid KUidStreamSettings       = {0x101F4E59};    ///< Stream UID for the CMmsSettings object


/**
 * Each media object within a message is identified by a TMmsMediaObjectId,
 * which is guaranteed to be unique within the scope of the message, and is
 * guaranteed not to change throughout the lifetime of the media object.
 */
typedef TInt32 TMmsMediaObjectId;
const TMmsMediaObjectId KMmsNullMediaObjectId = -1; ///< a null media object ID


/**
 * An enumeration identifying two broad MIME categories for MMS messages, either single-part or multi-part.
 * 
 * A single-part message can only have one media object added, and this media object cannot have its MIME headers set.
 * In addition, a single part message cannot have its content type set to a multipart type (e.g. multipart/related).
 * 
 * Conversely, a multipart message can have multiple media objects added, all of which may have MIME headers set individually.
 * However, it may not have its content type set to a non-multipart type.
 */
enum TMmsMessageMIMECategory
    {
    EMmsMIMECategoryUnset,  ///< Not yet set
    EMmsSinglePart,         ///< A single-part message
    EMmsMultiPart           ///< A multipart message
    };


/**
 * An enumeration used to identify valid values
 * for the X-MMS-Message-Type MMS header
 *
 * @note
 * The explicit values set here match those in the MMS spec and <b>must not be changed unless the spec changes</b>.
 */
enum TMmsMessageType
    {
    EMmsMessageTypeUnset   =   0,   ///< Value to indicate that this header is unset
    EMmsSendRequest        = 128,   ///< Corresponds to the m-send-req header value
    EMmsSendConfirm        = 129,   ///< Corresponds to the m-send-conf header value
    EMmsNotification       = 130,   ///< Corresponds to the m-notification-ind header value
    EMmsNotifyResponse     = 131,   ///< Corresponds to the m-notif-resp-ind header value
    EMmsRetrieveConfirm    = 132,   ///< Corresponds to the m-retrieve-conf header value
    EMmsAcknowledge        = 133,   ///< Corresponds to the m-acknowledge-ind header value
    EMmsDelivery           = 134    ///< Corresponds to the m-delivery-ind header value
    };


/**
 * An enumeration used to identify valid values
 * for the X-MMS-Response-Status MMS header 
 *
 * @note
 * The explicit values set here match those in the MMS spec and <b>must not be changed unless the spec changes</b>.
 */
enum TMmsResponseStatus
    {
    EMmsResponseStatusUnset            =   0,  ///< Value to indicate that this header is unset
    EMmsResponseStatusOk               = 128,  ///< Corresponds to the OK header value
    EMmsErrorUnspecified               = 129,  ///< Corresponds to the Error-unspecified header value
    EMmsErrorServiceDenied             = 130,  ///< Corresponds to the Error-service-denied header value
    EMmsErrorMessageFormatCorrupt      = 131,  ///< Corresponds to the Error-message-format-corrupt header value
    EMmsErrorSendingAddressUnresolved  = 132,  ///< Corresponds to the Error-sending-address-unresolved header value
    EMmsErrorMessageNotFound           = 133,  ///< Corresponds to the Error-message-not-found header value
    EMmsErrorNetworkProblem            = 134,  ///< Corresponds to the Error-network-problem header value
    EMmsErrorContentNotAccepted        = 135,  ///< Corresponds to the Error-content-not-accepted header value
    EMmsErrorUnsupportedMessage        = 136   ///< Corresponds to the Error-unsupported-message header value
    };


/**
 * An enumeration used to identify valid values
 * for the X-MMS-Status MMS header 
 *
 * @note
 * The explicit values set here match those in the MMS spec and <b>must not be changed unless the spec changes</b>.
 */
enum TMmsStatus
    {
    EMmsStatusUnset          =   0,  ///< Value to indicate that this header is unset
    EMmsStatusExpired        = 128,  ///< Corresponds to the Expired header value
    EMmsStatusRetrieved      = 129,  ///< Corresponds to the Retrieved header value
    EMmsStatusRejected       = 130,  ///< Corresponds to the Rejected header value
    EMmsStatusDeferred       = 131,  ///< Corresponds to the Deferred header value
    EMmsStatusUnrecognised   = 132   ///< Corresponds to the Unrecognised header value
    };


/**
 * An enumeration used to identify valid values
 * for the X-MMS-Sender-Visibility MMS header 
 *
 * @note
 * The explicit values set here match those in the MMS spec and <b>must not be changed unless the spec changes</b>.
 */
enum TMmsSenderVisibility
    {
    EMmsSenderVisibilityUnset  =   0,  ///< Value to indicate that this header is unset
    EMmsHide                   = 128,  ///< Corresponds to the Hide header value
    EMmsShow                   = 129   ///< Corresponds to the Show header value
    };


/**
 * An enumeration used to identify valid values
 * for MMS headers that take a yes/no value (e.g. X-MMS-Report-Allowed)
 *
 * @note
 * The explicit values set here match those in the MMS spec and <b>must not be changed unless the spec changes</b>.
 */
enum TMmsYesNo
    {
    EMmsYesNoUnset =   0,  ///< Value to indicate that this header is unset
    EMmsYes        = 128,  ///< Corresponds to the Yes header value
    EMmsNo         = 129   ///< Corresponds to the No header value
    };


/**
 * An enumeration used to identify valid values
 * for the MMS X-Mms-Priority header
 *
 * @note
 * The explicit values set here match those in the MMS spec and <b>must not be changed unless the spec changes</b>.
 */
enum TMmsPriority
    {
    EMmsPriorityUnset  =   0,  ///< Value to indicate that this header is unset
    EMmsPriorityLow    = 128,  ///< Corresponds to the Low header value
    EMmsPriorityNormal = 129,  ///< Corresponds to the Normal header value
    EMmsPriorityHigh   = 130,  ///< Corresponds to the High header value
    };




/**
 * An enumeration providing Message Class encoding values for the watcher and other server-side components.
 *
 * @note
 * This enum is for server-side components only and is not intended for use by a client application.
 */
enum TMmsMessageClass
    {
    EMmsPersonal        = 128, ///< Personal message class
    EMmsAdvertisement   = 129, ///< Advertisement message class
    EMmsInformational   = 130, ///< Informational message class
    EMmsAuto            = 131  ///< Auto message class
    };
_LIT(KMmsMessageClassPersonal, "Personal");             ///< String constant for "Personal" message class. Intended for use by server-side components.
_LIT(KMmsMessageClassAdvertisement, "Advertisement");   ///< String constant for "Advertisement" message class. Intended for use by server-side components.
_LIT(KMmsMessageClassInformational, "Informational");   ///< String constant for "Informational" message class. Intended for use by server-side components.
_LIT(KMmsMessageClassAuto, "Auto");                     ///< String constant for "Auto" message class. Intended for use by server-side components.


/**
 * This is a simple, struct-like class containing data required for reporting 
 * progress from a server-side send or fetch operation
 */
class TMmsTransferProgress
    {
    public:
        /**
         * An enumeration used to identify whether this class is reporting the progress of
         * a send or fetch transaction
         */
        enum TMmsTransactionType
            {
            EUnset,         ///< unset transaction type
            ESend,          ///< send transaction type
            EFetch,         ///< fetch transaction type
            EAcknowledge    ///< acknowledge transaction type
            };
        /**
         * An enumeration used to identify the connection state
         *
         */
        enum TMmsConnectionState
            {
            EConnecting,            ///< "connecting" connection state
            EConnected,             ///< "connected" connection state 
            EDisconnecting,         ///< "disconnecting" connection state 
            EDisconnected           ///< "disconnected" connection state 
            }; 

    public:
        /**
         *  Default constructor for TMmsTransferProgress
         */
        IMPORT_C TMmsTransferProgress();
        /**
         *  Constructor with parameters for TMmsTransferProgress
         *  Note that there is no parameter for connection state - it is always set to disconnected to start with.
         */
        IMPORT_C TMmsTransferProgress(TInt aErrorCode, TMmsTransactionType aType, TInt aBytesSent, TInt aBytesToSend, TInt aMessageNumber, TInt aMessageTotal);
        /**
         * Get the error code for the current operation
         *
         * @return An error code
         */
        inline TInt ErrorCode() const;
        /**
         * Set the error code for the current operation.
         *
         * @param aErrorCode An error code
         */
        inline void SetErrorCode(TInt aErrorCode);
        /**
         * Get the transaction type for the current operation.
         *
         * @return A transaction type
         */
        inline TMmsTransactionType TransactionType() const;
        /**
         * Set the transaction type for the current operation.
         *
         * @param aTransactionType A transaction type
         */
        inline void SetTransactionType(TMmsTransactionType aTransactionType);
        /**
         * Get the number of bytes sent in the current operation.
         *
         * @return A byte count
         */
        inline TInt BytesSent() const;
        /**
         * Set the number of bytes sent in the current operation.
         *
         * @param aBytesSent A byte count
         */
        inline void SetBytesSent(TInt aBytesSent);
        /**
         * Get the number of bytes still to be sent for the current operation.
         *
         * @return A byte count
         */
        inline TInt BytesToSend() const;
        /**
         * Set the number of bytes still to be sent for the current operation.
         *
         * @param aBytesToSend A byte count
         */
        inline void SetBytesToSend(TInt aBytesToSend);
        /**
         * During an operation which transfers <i>n</i> messages, this returns a number between 0..<i>n</i> indicating the number of the message currently being transferred.
         *
         * @return Number of the current message in an operation
         */
        inline TInt MessageNumber() const;
        /**
         * During an operation which transfers <i>n</i> messages, this is used to set a number between 0..<i>n</i> indicating the number of the message currently being transferred.
         *
         * @param aMessageNumber Number of the current message in an operation
         */
        inline void SetMessageNumber(TInt aMessageNumber);
        /**
         * Get the total number of messages being transferred in the current operation.
         *
         * @return Total number of messages for the current operation
         */
        inline TInt MessageTotal() const;
        /**
         * Set the total number of messages being transferred in the current operation.
         *
         * @param aMessageTotal Total number of messages for the current operation
         */
        inline void SetMessageTotal(TInt aMessageTotal);
        /**
         * Get the current connection state.
         *
         * @return the current connection state
         */
        inline TMmsConnectionState ConnectionState() const;
        /**
         * Set the current connection state
         *
         * @param aConnectionState the current connection state
         */
        inline void SetConnectionState(TMmsConnectionState aConnectionState);
    
    private:
        TUid iProgressId;                       ///< The UID of this progress structure
        TInt iErrorCode;                        ///< error code
        TMmsTransactionType iTransactionType;   ///< the type of transaction (send or fetch)
        TInt iBytesSent;                        ///< bytes sent so far
        TInt iBytesToSend;                      ///< total bytes to send
        TInt iMessageNumber;                    ///< message number
        TInt iMessageTotal;                     ///< total number of messages
        TMmsConnectionState iConnectionState;   ///< current connection state
    };


/**
 * A TMsvEntry-derived class adding MMS-specific functions.
 */
class TMsvMmsEntry : public TMsvEntry
    {
    public:
        /**
         * Get the type of the current message
         */
        inline TMmsMessageType MessageType() const;
        /**
         * Set the type of the current message
         */
        inline void SetMessageType(TMmsMessageType aType);
        /**
         * Get the processed flag for the current message
         */
        inline TBool Processed() const;
        /**
         * Set the processed flag for the current message
         */
        inline void SetProcessed(TBool aProcessed);
    };



// Constants for MMS Version numbers
const TUint8 KMmsMajorVersionMin  =  1;     ///< Minimum value for the major part of an MMS version number
const TUint8 KMmsMajorVersionMax  =  7;     ///< Maximum value for the major part of an MMS version number
const TUint8 KMmsMinorVersionMin  =  0;     ///< Minimum value for the minor part of an MMS version number
const TUint8 KMmsMinorVersionMax  = 14;     ///< Maximum value for the minor part of an MMS version number
const TUint8 KMmsMinorVersionNone = 15;     ///< Value representing an absent minor part for an MMS version number

/**
 * Simple version number class for MMS.
 *
 * Implements the following requirement from the WAP MMS Encapsulation Protocol Spec:
 *
 *   "The three most significant bits of the Short-integer are interpreted to encode a major version number in the range 1-7,
 *   and the four least significant bits contain a minor version number in the range 0-14. If there is only a major version
 *   number, this is encoded by placing the value 15 in the four least significant bits [WAPWSP]."
 */
class TMmsVersion
    {
    public:
        /**
         * Default constructor.
         * Initialises the object to the current MMS version number.
         */
        IMPORT_C TMmsVersion();

        /**
         * Constructor. Will panic if the parameters are outside the following valid ranges:
         * aMajorVersionNumber: 1-7 incl
         * Use this overload if you require a major version number only, and no minor version number
         */
        IMPORT_C explicit TMmsVersion(TUint8 aMajorVersionNo);
        
        /**
         * Constructor. Will panic if the parameters are outside the following valid ranges:
         * aMajorVersionNumber: 1-7 incl
         * aMinorVersionNumber: 0-14 incl
         * Use this overload if you require both a major version and a minor version number
         */
        IMPORT_C TMmsVersion(TUint8 aMajorVersionNo, TUint8 aMinorVersionNo);

        /**
         * Getter to return the major version number component
         */
        IMPORT_C TUint8 MajorVersionNumber() const;

        /**
         * Getter to return the minor version number component.
         * Returns KMmsMinorVersionNone if none is set.
         */
        IMPORT_C TUint8 MinorVersionNumber() const;

        /**
         * Getter to return the internal representation of an object.
         */
        inline TUint8 Uint8() const;

        /**
         * Externalizes this object to a stream
         * @param aStream The stream to externalize to
         * @exception KErrXxx Standard stream leave codes
         */
        IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

        /**
         * Internalizes this object from a stream
         * @param aStream The stream to internalize from
         * @exception KErrXxx Standard stream leave codes
         */
        IMPORT_C void InternalizeL(RReadStream& aStream);

    private:
        TUint8 iVersion;
    };


/**
 * A simple class for use with expiry and delivery time MMS headers, which can have values
 * of absolute time or a time interval (in seconds)
 */
class TMmsTime
    {
    public:
        /**
         * An enumeration to describe whether the value currently held in an interval, an
         * absolute time, or hasn't been set yet.
         */
        enum TTimeType
            {
            EUnset      =   0,  ///< Unset time type
            EAbsolute   = 128,  ///< Absolute time type
            EInterval   = 129   ///< Interval time type
            };
    public:
        /**
         * C++ constructor
         */
        IMPORT_C TMmsTime();

        /**
         * Use this function to find the type of time currently held in this class
         * @return The type of time curently held in this class, unset, absolute or interval
         */
        IMPORT_C TTimeType TimeType() const;

        /**
         * Gets the absolute time value stored in this class
         * @return The absolute time value
         */
        IMPORT_C TTime AbsoluteTime() const;
        /**
         * Gets the time interval value stored in this class, expressed in seconds
         * @return The time interval value
         */
        IMPORT_C TInt TimeInterval() const;

        /**
         * Sets the absolute time, updates the time type and resets the interval time
         * @param aTime The new value for the absolute time
         */
        IMPORT_C void SetAbsoluteTime(TTime aTime);
        /**
         * Sets the interval time (expressed in seconds), updates the time type and resets the absolute time
         * @param aTimeInterval The new value for the interval time
         */
        IMPORT_C void SetTimeInterval(TInt aTimeIntervalSecs);

        /**
         * Externalizes this object to a stream
         * @param aStream The stream to externalize to
         * @exception KErrXxx Standard stream leave codes
         */
        IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
        /**
         * Internalizes this object from a stream
         * @param aStream The stream to internalize from
         * @exception KErrXxx Standard stream leave codes
         */
        IMPORT_C void InternalizeL(RReadStream& aStream);

    private:
        TTime iAbsoluteTime;    ///< An absolute time value
        TInt iTimeInterval;     ///< An time interval value
        TTimeType iTimeType;    ///< The time type currently held

    };


/**
 * General MMS utility class containing static functions.
 */
class MmsUtils
    {
    public:
        /** Gets a settings object internalized from the MMS service entry and returns it on the cleanup stack.
         *
         * @exception KErrNotFound No MMS service entry could be found
         * @exception KErrXxx Standard EPOC error codes
         * @return Settings object
         */
        IMPORT_C static CMmsSettings* MmsSettingsLC(CMsvSession& aSession);
    };


#include "MmsUtils.inl"


#endif // __MMSUTILS_H__
