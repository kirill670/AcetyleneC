/*
* ============================================================================
*  Name        : CMessageData.h
*  Part of     : SendUi
*  Description : Encapsulates the message data for sending services.
*  Version     : 1.0
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  Information which may not be disclosed to others without the 
*  prior written consent of Nokia.
*
* ============================================================================
*/

#ifndef CMESSAGEDATA_H
#define CMESSAGEDATA_H

// INCLUDES
#include <e32Base.h>
#include <badesca.h>
#include <f32file.h>
#include <msvstd.h>
#include "CMessageAddress.h"

//  FORWARD DECLARATIONS
class MDesC16Array;
class CRichText;

// CLASS DECLARATION

/**
 * Encapsulates the message data for sending services.
 *
 * @lib SendUi
 * @since Series 60 3.0
 */ 
class CMessageData : public CBase
    {
    public:  // Constructors and destructor
    
        /**
        * Two-phased constructor.
        * @return Pointer to object of CMessageData.
        */
        IMPORT_C static CMessageData* NewL();
        
        /**
        * Two-phased constructor.
        * @return Pointer to object of CMessageData.
        */
        IMPORT_C static CMessageData* NewLC();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CMessageData();

    public: // New functions

        /**
        * Set message subject.
        * @since Series 60 3.0
        * @param aSubject Message subject.
        * @return None.
        */
        IMPORT_C void SetSubjectL( const TDesC* aSubject );

        /**
        * Returns message subject.
        * @since Series 60 3.0
        * @return Message subject.
        */
        IMPORT_C const TPtrC Subject() const;

        /**
        * Appends attachment file path to the array of attachment file paths. 
        * @since Series 60 3.0
        * @param aFilePath File path of the attachment.
        * @return None.
        */
        IMPORT_C void AppendAttachmentL( const TDesC& aFilePath );

        /**
        * Returns the array of attachment file paths.
        * @since Series 60 3.0
        * @return Array of attachment file paths.
        */
        IMPORT_C const CDesCArray& AttachmentArray() const;
        
        /**
        * Clears the array of attachment file paths.
        * @since Series 60 3.0
        * @return Array of attachment file paths.
        */        
        IMPORT_C void ClearAttachmentArray();

        /**
        * Encapsulates address and alias to CMessageAddress and adds to array.
        * @since Series 60 3.0
        * @param aAddress Real address.
        * @param aAlias Alias for the real address.
        * @return None.
        */
        IMPORT_C void AppendToAddressL(
            const TDesC& aAddress,
            const TDesC& aAlias = KNullDesC);

        /**
        * Returns array of addresses and aliases.
        * @since Series 60 3.0
        * @return Array of addresses and aliases.
        */
        IMPORT_C const CMessageAddressArray& ToAddressArray() const;

        /**
        * Encapsulates CC address and alias to CMessageAddress and adds to 
        * array.
        * @since Series 60 3.0
        * @param aCcAddress Real CC-address.
        * @param aCcAlias Alias for the real CC-address.
        * @return None.
        */
        IMPORT_C void AppendCcAddressL(
            const TDesC& aCcAddress,
            const TDesC& aCcAlias = KNullDesC);

        /**
        * Returns array of CC addresses and aliases.
        * @since Series 60 3.0
        * @return Array of cc addresses and aliases.
        */
        IMPORT_C const CMessageAddressArray& CcAddressArray() const;

        /**
        * Encapsulates Bcc address and alias to CMessageAddress and adds to
        * array.
        * @since Series 60 3.0
        * @param aBccAddress Real Bcc-address.
        * @param aBccAlias Alias for the real Bcc-address.
        * @return None.
        */
        IMPORT_C void AppendBccAddressL(
            const TDesC& aBccAddress,
            const TDesC& aBccAlias = KNullDesC);

        /**
        * Returns array of Bcc addresses and aliases.
        * @since Series 60 3.0
        * @return Array of Bcc addresses and aliases.
        */
        IMPORT_C const CMessageAddressArray& BccAddressArray() const;

        /**
        * Set message body text.
        * @since Series 60 3.0
        * @param aBodyText Message body text.
        * @return None.
        */
        IMPORT_C void SetBodyTextL( const CRichText* aBodyText );

        /**
        * Returns message body text.
        * @since Series 60 3.0
        * @return Message body text.
        */
        IMPORT_C const CRichText* BodyText() const;
        
        /**
        * Appends attachment handle to the array of attachment handles. 
        *
        * NOTE: Attachment handles should be opened using ShareProtected()
        * file session, otherwise handles can't be transfered through
        * client-server interface.
        *
        * @since Series 60 3.0
        * @param aFileHandle File handle of the attachment.
        * @return None.
        */
        IMPORT_C void AppendAttachmentHandleL( const RFile& aFileHandle );

        /**
        * Returns the array of attachment handles.
        * @since Series 60 3.0
        * @return Array of attachment handles.
        */
        IMPORT_C const RArray<RFile>& AttachmentHandleArray() const;

        /**
        * Returns data type id.
        * This is used for static casting.
        * @since Series 60 3.0
        * @return Data type id.
        */
        IMPORT_C TUid DataType() const;

        /**
        * Clears all addressee arrays.
        * @since Series 60 3.0
        * @return None.
        */ 
        IMPORT_C void ClearAddresses();

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CMessageData();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        IMPORT_C void ConstructL();

    protected:  // Data

        // Data type id
        TUid                            iDataType;

    private:  // Data

        // Message subject. Owned.
        HBufC*                          iSubject;

        // Message body text. Owned. 
        CRichText*                      iBodyText;

        // Attachment filepaths. Owned.
        CDesCArray*                     iAttachments;

        // Array of real addresses and aliases. Owned.
        CMessageAddressArray*           iToAddresses;

        // Array of real CC addresses and aliases. Owned.
        CMessageAddressArray*           iCcAddresses;

        // Array of real BC addresses and aliases. Owned.
        CMessageAddressArray*           iBccAddresses;
    
        // Attachment handles. Owned.
        RArray<RFile>                   iAttachmentHandles;
    };

#endif      // CMESSAGEDATA_H

// End of File

