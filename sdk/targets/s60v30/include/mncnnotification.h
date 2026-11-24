/*
* ============================================================================
*  Name     : MNcnNotification.h
*  Part of  : Ncn Notification API
*
*  Description:
*       Public ECom notification API towards NcnList.
*  Version:
*
*  Copyright (C) 2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing,  adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __MNCNNOTIFICATION_H__
#define __MNCNNOTIFICATION_H__

//  INCLUDES
#include <e32base.h>
#include <msvstd.h>
#include <bamdesca.h>
#include <ECom.h>
#include <EComResolverParams.h>

// FORWARD DECLARATIONS

// UID of this interface
const TUid KNcnNotificationInterfaceUid = {0x101f8855};

// CLASS DECLARATION

/**
 * Public ECom notification API towards NcnList.
 * This API allows notifying NcnList about new message(s).
 *
 */
class MNcnNotification
    {
    private: // Enumerations
        /**
         * Indication type bit enumeration.
         */
        enum TIndicationTypeBits
            {
            /* Icon bit */
            EIndicationIconBit = 0x1,

            /* Tone bit */
            EIndicationToneBit = 0x2,

            /* Soft note bit */
            EIndicationSoftNoteBit = 0x4
            };

    public: // Enumerations
        /**
         * Indication type enumeration.
         */
        enum TIndicationType
            {
            /* Icon indication */
            EIndicationIcon = EIndicationIconBit,

            /* Normail indication */
            EIndicationNormal = EIndicationIconBit | EIndicationToneBit | EIndicationSoftNoteBit
            };

    public: // Constructor and destructor

       /**
        * ECom implementation class factory method.
        * Caller takes the ownership of the created object.
        * If interface needs to be pushed into CleanupStack,
        * remember to use CleanupStackDeletePushL() function!
        * DO NOT USE CleanupStack::PushL()!!
        * @return ECom implementation instance
        */
        static MNcnNotification* CreateMNcnNotificationL();

       /**
        * Destructor.
        */
        virtual ~MNcnNotification();

    public: // Interface

		/**
         * Called by Messaging Server -compatible 3rd party Email plugins
         * to inform NcnList that there's new message(s). Parameter aInfo
         * is reserved for future use and is not handled in any way currently.
         *
         * @param aMailBox        The id for mail message type identifying mailbox or
         *                        individual mail folder that contains new message(s)         
         * @param aIndicationType Indication type for new messages. May be any combination
         *                        of enumeration TIndicationType values.
         * @param aInfo           Optional info about message (subject, sender etc.)
         *
         * @return                KErrNone for success, or some error code
         */
        virtual TInt NewMessages( const TMsvId& aMailBox,                                  
                                  TIndicationType aIndicationType,
                                  const MDesCArray& aInfo ) = 0;

        /**
         * Called by Messaging Server -compatible 3rd party Email plugins
         * wanting to make a request about marking certain new messages as unread.
         *
         * @param aMailBox The id for mail msg type identifying mailbox or mail
         *                 folder containing message(s) to be marked as unread.
         *
         * @return         KErrNone for success, or some error code
         */
        virtual TInt MarkUnread( const TMsvId& aMailBox ) = 0;

    private: // data
    
        // for ECom to identify plug-in instance
        TUid iDtor_ID_Key;                         
    };

#include <MNcnNotification.inl>

#endif // __MNCNNOTIFICATION_H__

// End of File
