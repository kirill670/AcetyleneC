// $Workfile: mmsheaders.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 29 $
// $Date: 7/01/02 16:34 $
//

/** @file
 * This file contains the definition of the CMmsHeaders class.
 */


#ifndef __MMSHEADERS_H__
#define __MMSHEADERS_H__


// System includes
#include <badesca.h>    //CDesCArray
#include <e32std.h> 
#include <e32base.h>    //CBase 
#include <msvstd.h>     //TMsvPriority
// User includes
#include "MmsUtils.h"   //TMmsMessageType, TMmsStatus, TMmsResponseStatus, TMmsTime
#include "MmsUtilsHeaderParameter.h"    // CMmsUtilsHeaderParameterArray


//forward declarations
class CMmsUtilsHeaderArray;
class CMmsMediaObjectList;
class CMmsMessage;
class CMmsRecipient;
class CMsvStore;    
class RReadStream;
class RWriteStream;


typedef CArrayPtrSeg<CMmsRecipient> CMmsRecipientArray;


/**
 * This class encapsulates the names and values of the MMS headers specified in the WAP MMS encapsulation 
 * protocol (WAP-209-MMSEncapsulation-20010601-a, available from www.wapforum.org).  This class 
 * also supports additional headers from RFC822. It is not intended that this class be responsible for 
 * validation of its header values.  This class will support multiple values for some of its headers, e.g. 
 * To, Cc And Bcc headers.
 */

class CMmsHeaders : public CBase
    {
    public:
        /**
         Enumerated type to distinguish different types of MMS recipient.
         */
        enum TMmsRecipientType
            {
            ETo,    ///< a To recipient
            ECc,    ///< a Cc recipient
            EBcc    ///< a Bcc recipient
            };

        //
        // Recipients API
        //

        /**
         * Adds a recipient unless the address is a duplicate of an existing recipient.
         * @param aType Type of recipient
         * @param aAddress Recipient's address
         * @retval KErrAlreadyExists A recipient of this type already exists with address aAddress. No new recipient has been added.
         * @retval KErrNone The recipient has been successfully added
         */
        IMPORT_C TInt AddRecipientL(TMmsRecipientType aType, const TDesC& aAddress);

        /**
         * Get a read-only array of recipients of a particular type
         * @param aType Type of recipients requested
         * @return A read-only array of recipients. This will have zero count if no recipients have been added for this type
         */
        IMPORT_C const CMmsRecipientArray& Recipients(TMmsRecipientType aType) const;
        
        /**
         * Remove a recipient by address and type
         * @param aType Type of recipient to remove
         * @param aAddress Address of recipient to remove
         * @retval KErrNone The recipient has been removed
         * @retval KErrNotFound A recipient did not exist matching aType and aAddress. No recipients have been removed.
         */
        IMPORT_C TInt RemoveRecipient(TMmsRecipientType aType, const TDesC& aAddress);
        
        /**
         * Remove all recipient of a particular type
         * @param aType Type of recipients to remove
         */
        IMPORT_C void RemoveAllRecipients(TMmsRecipientType aType);
        
        /**
         * Query whether a delivery report has been received for a recipient
         * @param aType Type of recipient
         * @param aAddress Address of recipient
         * @param aError Error flag. This will be set to <code>KErrNotFound</code> if the recipient does not exist, otherwise <code>KErrNone</code>.
         * @retval ETrue A delivery report has been received for this recipient
         * @retval EFalse A delivery report has not been received for this recipient, or the recipient does not exist. Check the value if aError to determine which is the case.
         */
        IMPORT_C TBool DeliveryReportReceived(TMmsRecipientType aType, const TDesC& aAddress, TInt& aError) const;
        
        /**
         * Set the Delivery Report Received flag for a recipient
         * @param aType Type of recipient
         * @param aAddress Address of recipient
         * @retval KErrNone Flag has been set successfully
         * @retval KErrNotFound The recipient does not exist for this message
         */
        IMPORT_C TInt SetDeliveryReportReceived(TMmsRecipientType aType, const TDesC& aAddress);

        //
        // End of recipients API
        //


        /**
         * Returns the from MMS header.
         * @return The from header value. This will be a zero-length descriptor if the From address has not been set.
         */
        IMPORT_C TPtrC From() const;
        /**
         * Sets the from MMS header.
         *
         * @param aFrom The new from header value
         * @exception KErrXXX Standard EPOC error codes if allocation of a buffer to hold the from header fails.
         */
        IMPORT_C void SetFromL(const TDesC& aFrom);

        /**
         * Returns the date MMS header.
         * @return The date header value
         */
        IMPORT_C const TTime& Date() const;
        /**
         * Sets the date MMS header.
         *
         * @param aDate The new date header value
         */
        IMPORT_C void SetDate(const TTime& aDate);

        /**
         * Returns the priority MMS header.
         * @return The priority header value, or EPriorityUnset if this header has not been set.
         */
        IMPORT_C TMmsPriority Priority() const;
        /**
         * Sets the priority MMS header.
         *
         * @param aPriority The new priority header value
         */
        IMPORT_C void SetPriority(TMmsPriority aPriority);

        /**
         * Returns the message-type MMS header.
         * @return The message-type header value, or EMessageTypeUnset if this header has not been set.
         */
        IMPORT_C TMmsMessageType MessageType() const;
        /**
         * Sets the message-type MMS header.
         *
         * @param aMessageType The new message-type header value
         */
        IMPORT_C void SetMessageType(TMmsMessageType aMessageType);

        /**
         * Returns the read-reply MMS header.
         * @return The read-reply header value, or EYesNoUnset if this header has not been set.
         */
        IMPORT_C TMmsYesNo ReadReply() const;
        /**
         * Sets the read-reply MMS header.
         *
         * @param aReadReply The new read-reply header value
         */
        IMPORT_C void SetReadReply(TMmsYesNo aReadReply);

        /**
         * Returns the subject MMS header.
         * @return The subject header value. This will be a zero-length descriptor if this header has not been set.
         */
        IMPORT_C TPtrC Subject() const;
        /**
         * Sets the subject MMS header.
         *
         * @param aSubject The new subject header value
         * @exception KErrXXX Standard EPOC error codes if allocation of a buffer to hold the subject header fails.
         */
        IMPORT_C void SetSubjectL(const TDesC& aSubject);

        /**
         * Returns the content-location MMS header.
         * @return The content-location header value. This will be a zero-length descriptor if this header has not been set.
         */
        IMPORT_C TPtrC ContentLocation() const;
        /**
         * Sets the content-location MMS header.
         *
         * @param aLocation The new content-location header value
         * @exception KErrXXX Standard EPOC error codes if allocation of a buffer to hold the content-location header fails.
         */
        IMPORT_C void SetContentLocationL(const TDesC& aLocation);

        /**
         * Returns the content-type MMS header.
         * @return The content-type header value. This will be a zero-length descriptor if this header has not been set.
         */
        IMPORT_C TPtrC ContentType() const;
        /**
         * Sets the content-type MMS header.
         *
         * @param aContentType The new content-type header value
         * @exception KErrXXX Standard EPOC error codes if allocation of a buffer to hold the content-type header fails.
         */
        IMPORT_C void SetContentTypeL(const TDesC& aContentType);

        /**
         * Add a Content-type header parameter.
         * @param aParameter The parameter to add. <b>Note that this object takes ownership of aParameter and will delete it.</b>
         * @exception KErrXxx Standard EPOC error codes if memory cannot be allocated for aParameter
         */
        IMPORT_C void AddContentTypeParameterL(CMmsUtilsHeaderParameter* aParameter);
        /**
         * Get Content-type header parameters.
         * @return An array of parameters added for the Content-type header. This will be empty if none have been added.
         */
        IMPORT_C const CMmsUtilsHeaderParameterArray& ContentTypeParameters() const;
        /**
         * Remove all Content-type header parameters.
         */
        IMPORT_C void RemoveContentTypeParameters();

        /**
         * Returns the delivery-report MMS header. This specifies whether the user wants a delivery report from each recipient.
         * @return The delivery-report header value, or EYesNoUnset if this header has not been set.
         */
        IMPORT_C TMmsYesNo DeliveryReport() const;
        /**
         * Sets the delivery-report MMS header, which specifies whether the user wants a delivery report from each recipient.
         * When delivery reports are received, the corresponding recipients may be flagged using the SetDeliveryReportReceived() method.
         * @param aReport The new delivery-report header value
         */
        IMPORT_C void SetDeliveryReport(TMmsYesNo aReport);
    
        /**
         * Returns the delivery-time MMS header.
         * @return The delivery-time header value
         */
        IMPORT_C const TMmsTime& DeliveryTime() const;
        /**
         * Sets the delivery-time MMS header.
         * @param aTime The new delivery-time header value
         */
        IMPORT_C void SetDeliveryTime(const TMmsTime& aTime);

        /**
         * Returns the expiry MMS header.
         * @return The expiry header value
         */
        IMPORT_C const TMmsTime& Expiry() const;
        /**
         * Sets the expiry MMS header.
         * @param aExpiry The new expiry header value
         */
        IMPORT_C void SetExpiry(const TMmsTime& aExpiry);
    
        /**
         * Returns the message-class MMS header.
         * @return The message-class header value. This will be a zero-length descriptor if this header has not been set.
         */
        IMPORT_C TPtrC MessageClass() const;
        /**
         * Sets the message-class MMS header.
         *
         * @param aClass The new message-class header value
         * @exception KErrXXX Standard EPOC error codes if allocation of a buffer to hold the message-class header fails.
         */
        IMPORT_C void SetMessageClassL(const TDesC& aClass);

        /**
         * Returns the version MMS header.
         * @return The version header value, or EVersionUnset if this header has not been set.
         */
        IMPORT_C TMmsVersion Version() const;
        /**
         * Sets the version MMS header.
         * @param aVersion The new version header value
         */
        IMPORT_C void SetVersion(TMmsVersion aVersion);

        /**
         * Returns the message-size MMS header.
         * @return The message-size header value
         */
        IMPORT_C TInt MessageSize() const;
        /**
         * Sets the message-size MMS header.
         * @param aSize The new message-size header value, or 0 if this header has not been set.
         */
        IMPORT_C void SetMessageSize(TInt aSize);

        /**
         * Returns the report-allowed MMS header.
         * @return The report-allowed header value
         */
        IMPORT_C TMmsYesNo ReportAllowed() const;
        /**
         * Sets the report-allowed MMS header.
         * @param aReport The new report-allowed header value
         */
        IMPORT_C void SetReportAllowed(TMmsYesNo aReport);

        /**
         * Returns the response-status MMS header.
         * @return The response-status header value, or EResponseStatusUnset if this header has not been set.
         */
        IMPORT_C TMmsResponseStatus ResponseStatus() const;
        /**
         * Sets the response-status MMS header.
         * @param aStatus The new response-status header value
         */
        IMPORT_C void SetResponseStatus(TMmsResponseStatus aStatus);

        /**
         * Sets the response-text MMS header.
         * @return aReadReply The new response-text header value. This will be a zero-length descriptor if this header has not been set.
         */
        IMPORT_C TPtrC ResponseText() const;
        /**
         * Sets the response-text MMS header.
         *
         * @param aText The new response-text header value
         * @exception KErrXXX Standard EPOC error codes if allocation of a buffer to hold the response-text header fails.
         */
        IMPORT_C void SetResponseTextL(const TDesC& aText);

        /**
         * Returns the sender-visibility MMS header.
         * @return The sender-visibility header value, or ESenderVisibilityUnset if this header has not been set.
         */
        IMPORT_C TMmsSenderVisibility SenderVisibility() const;
        /**
         * Sets the sender-visibility MMS header.
         * @param aVisibility The new sender-visibility header value
         */
        IMPORT_C void SetSenderVisibility(TMmsSenderVisibility aVisibility);

        /**
         * Returns the status MMS header.
         * @return The status header value, or EStatusUnset if this header has not been set.
         */
        IMPORT_C TMmsStatus Status() const;
        /**
         * Sets the status MMS header.
         * @param aStatus The new status header value
         */
        IMPORT_C void SetStatus(TMmsStatus aStatus);

        /**
         * Returns the transaction-id MMS header.
         * @return The transaction-id header value. This will be a zero-length descriptor if this header has not been set.
         */
        IMPORT_C TPtrC TransactionId() const;
        /**
         * Sets the transaction-id MMS header.
         * @param aId The new transaction-id header value
         */
        IMPORT_C void SetTransactionIdL(const TDesC& aId);

        /**
         * Returns the message-id MMS header.
         * @return The message-id header value. This will be a zero-length descriptor if this header has not been set.
         */
        IMPORT_C TPtrC MessageId() const;
        /**
         * Sets the message-id MMS header.
         * @param aId The new message-id header value
         */
        IMPORT_C void SetMessageIdL(const TDesC& aId);

        /**
         * Add a special header value for a given header name.  Note that this may be called more than once with 
         * the same header name, in which case a list of values will be stored for this name. 
         *
         * @param aHeaderName The header name 
         * @param aHeaderValue The header value 
         * @exception KErrXXX Standard EPOC error codes if memory cannot be allocated for the new header value.
         */
        IMPORT_C void AddSpecialHeaderL(const TDesC& aHeaderName, const TDesC& aHeaderValue);
        /**
         * Remove the header with a given name.  Note that if more than one value is stored for this header, 
         * all values will be removed.
         *
         * @param aHeaderName The header name
         * @retval KErrNone The special header was successfully deleted.
         * @retval KErrNotFound No special header was found with the name aHeaderName.
         */
        IMPORT_C TInt RemoveSpecialHeader(const TDesC& aHeaderName);
        /**
         * Get the list of header values for a given header name.
         *
         * @param aHeaderName The name of the header for which values are required
         * @exception KErrNotFound No values stored for the header name aHeaderName
         * @return An array of header values.
         */
        IMPORT_C const CDesCArray& SpecialHeaderValuesL(const TDesC& aHeaderName);
        /**
         * Get the list of the header names that have been set.
         * @exception KErrNotFound No header names stored 
         * @exception KErrXXX Leaves with standard EPOC leave codes if memory allocation or pushing to the cleanup stack fails
         * @return An array of header names.
         */
        IMPORT_C CDesCArray* SpecialHeaderNamesLC();


    public: // Not exported because they should only be accessible to CMmsMessage.
        /**
         * 2 phase constructor.  This function creates a new CMmsHeaders object.
         * @exception KErrXXX Standard leave codes if no memory is available
         * @return A newly created CMmsHeaders object
         */
        static CMmsHeaders* NewL();
        /**
         * 2 phase constructor
         * This function creates a new CMmsHeaders object and puts it on the cleanup stack.
         * @exception KErrXXX Standard leave codes if no memory is available
         * @return A newly created CMmsHeaders object
         */
        static CMmsHeaders* NewLC();
        /**
         * C++ destructor
         */
        ~CMmsHeaders();
        /**
         * Creates a stream in aStore and externalises this object to it.
         *
         *
         * @param aStore The store to which this object is to be stored. Note this must be open with write access or 
         *  this function will leave.
         * @exception KErrXXX Standard EPOC stream leave codes.
         * @exception KErrAccessDenied aStore is not opened with write access.
         */
        void StoreL(CMsvStore& aStore) const;
        /**
         * Opens a stream in aStore and internalises this object from it.
         * @param aStore The store from which this object is to be restored. Note this must be open with read or 
         *  read/write access or this function will leave.
         * @exception KErrXXX Standard EPOC stream leave codes. 
         * @exception KErrAccessDenied aStore is not opened with read access.
         */
        void RestoreL(const CMsvStore& aStore);
        /**
         * Set a MIME category (either single-part or multi-part) for this message.
         * @note
         * This function will panic with EMmsPanicMIMECategoryViolation if this message's MIME category has previously been set to a different value.
         * @param aMIMECategory A MIME category for this message.
         */
        void SetMimeCategory(TMmsMessageMIMECategory aMIMECategory);

    private:
        /**
         * C++ constructor
         * Sets all enum values to unset. All non-trivial construction is done in the ConstructL function.
         */
        CMmsHeaders();
        /**
         * 2nd phase constructor
         *
         * @exception KErrXXX Standard leave codes if no memory is available
         */
        void ConstructL();

        /**
         * Externalizes CMmsHeaders object to a stream.
         *
         * @param aWriteStream The stream to be written to
         * @exception KErrXXX Standard EPOC stream leave codes
         */
        void ExternalizeL(RWriteStream& aWriteStream) const;
        /**
         * Internalizes the CMmsHeaders object from a stream.
         *
         * @param aReadStream The stream to be read from
         * @exception KErrNotSupported The stream was written by a previous version and its format is no longer supported
         * @exception KErrXXX Standard EPOC stream leave codes
         */
        void InternalizeL(RReadStream& aReadStream);

        void ExternalizeRecipientArrayL(const CMmsRecipientArray& aArray, RWriteStream& aWriteStream) const;
        void InternalizeRecipientArrayL(CMmsRecipientArray& aArray, RReadStream& aReadStream);

        /**
         * Utility function to return a reference to a recipient array by type.
         */
        CMmsRecipientArray& RecipientArray(TMmsRecipientType aType) const;

        /**
         * Binary search function to find an item in a sorted array.
         * @param aArray The array to search in
         * @param aRecipientAddress The recipient address to search for
         * @param aPos If a matching recipient is found, the position the item was found at. Otherwise the position it should be inserted at.
         * @retval ETrue A recipient with address aRecipientAddress was found in the aArray
         * @retval EFalse A recipient with address aRecipientAddress was not found in the aArray
         */
        TBool IsInArray(const CMmsRecipientArray& aArray, const TDesC& aRecipientAddress, TInt& aPos) const;

    private:

    //attributes to represent headers that can have multiple values
        
        CMmsRecipientArray* iToRecipients;
        CMmsRecipientArray* iCcRecipients;
        CMmsRecipientArray* iBccRecipients;


    //attributes to represent headers that can have only one value each

        HBufC* iSubject;                ///<the Subject MMS header value
        HBufC* iFrom;                   ///<the From MMS header value 
        TTime iDate;                    ///<the Date MMS header value 
        TMmsPriority iPriority;         ///<the X-Mms-Message-Priority MMS header value 
        TMmsMessageType iMessageType;   ///<the X-Mms-Message-Type MMS header value 
        TMmsYesNo iReadReply;           ///<the X-Mms-Message-Read-Reply MMS header value 

        HBufC* iContentLocation;        ///<the X-Mms-Content-Location MMS header value 
        HBufC* iContentType;            ///<the content-type MMS header value
        TMmsYesNo iDeliveryReport;      ///<the X-Mms-Delivery-Report MMS header value  
        TMmsTime iDeliveryTime;         ///<the X-Mms-Delivery-Time MMS header value  
        TMmsTime iExpiry;               ///<the X-Mms-Expiry MMS header value   
        HBufC* iMessageClass;           ///<the X-Mms-Message-Class MMS header value   
        TMmsVersion iVersion;           ///<the X-Mms-MMS-Version MMS header value  
        TInt iMessageSize;              ///<the X-Mms-Message-Size MMS header value 
        TMmsYesNo iReportAllowed;       ///<the X-Mms-Report-Allowed MMS header value 
        TMmsResponseStatus iResponseStatus; ///<the X-Mms-Response-Status MMS header value 
        HBufC* iResponseText;               ///<the X-Mms-Response-Text MMS header value 
        TMmsSenderVisibility iSenderVisibility; ///<the X-Mms-Sender-Visibility MMS header value 

        TMmsStatus iStatus;             ///<the X-Mms-Status MMS header value  
        HBufC* iTransactionId;          ///<the X-Mms-Transaction-ID MMS header value  
        HBufC* iMessageId;              ///<the message-id MMS header value  

        CMmsUtilsHeaderArray* iSpecialHeaders;  ///< any additional headers added have their names and values stored in this attribute
        TMmsMessageMIMECategory iMIMECategory;  ///< MIME category (single-part or multi-part) for this message
        CMmsUtilsHeaderParameterArray* iContentTypeParams; ///< Parameters associated with the content-type header
    };


#endif __MMSHEADERS_H__