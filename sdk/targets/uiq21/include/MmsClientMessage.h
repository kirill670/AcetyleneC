// $Workfile: MmsClientMessage.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 16 $
// $Date: 7/01/02 16:25 $
//


/** @file
 *  This file contains the interface for the CMmsClientMessage class.
 */


#ifndef __MMSCLIENTMESSAGE_H__
#define __MMSCLIENTMESSAGE_H__


#include <msvapi.h>         // CMsvSession
#include "MmsMessage.h"     // CMmsMessage


/**
 * Client-side MMS message class.
 * This is a concrete implementation of CMmsMessage that has its own CMsvEntry,
 * so that a user can store and restore the message without using an MTM.
 */
class CMmsClientMessage : public CMmsMessage
    {
    public:
        /**
         * 2 phase constructor
         * This function creates a CMmsClientMessage object.
         * Note that a corresponding messaging entry must have been previously created.
         * @param aSession A reference to a messaging session. This must have been successfully opened previously.
         * @param aEntryId The ID of the entry this message is associated with.
         * @exception KErrXxx Leaves if no memory is available
         * @return A newly created CMmsClientMessage object
         */
        IMPORT_C static CMmsClientMessage* NewL(CMsvSession& aSession, TMsvId aEntryId);
        
        /**
         * 2 phase constructor
         * This function creates a CMmsClientMessage object and puts it on the cleanup stack.
         * Note that a corresponding messaging entry must have been previously created.
         * @param aSession A reference to a messaging session. This must have been successfully opened previously.
         * @param aEntryId The ID of the entry this message is associated with.
         * @exception KErrXxx Leaves if no memory is available
         * @return A newly created CMmsClientMessage object
         */
        IMPORT_C static CMmsClientMessage* NewLC(CMsvSession& aSession, TMsvId aEntryId);
        
        /**
         * C++ destructor
         */
        IMPORT_C ~CMmsClientMessage();

        /**
         * Asynchronously stores the current message, including headers and media objects, to the associated entry's store.
         * Also updates the associated Messaging Index entry (the TMsvEntry) with the current values from this object.
         * @param aStatus Request status of the requesting active object.
         * @return Operation class returned by CMsvEntry::ChangeL
         * @exception KErrXxx           Standard EPOC stream leave codes.
         */
        IMPORT_C CMsvOperation* StoreL(TRequestStatus& aStatus);

        /**
         * Synchronously stores the current message, including headers and media objects, to the associated entry's store.
         * Also updates the associated Messaging Index entry (the TMsvEntry) with the current values from this object.
         * @exception KErrXxx           Standard EPOC stream leave codes.
         */
        IMPORT_C void StoreL();
        
        /**
         * Restores the current message, including headers and media objects.
         * @exception KErrXxx Standard EPOC stream leave codes.
         */
        IMPORT_C void RestoreL();

        /**
         * Get the messaging index entry associated with this message.
         * @return A const reference to a TMsvEntry associated with this message.
         */
        IMPORT_C virtual const TMsvMmsEntry& Entry() const;

    private: // from CMmsMessage
        /**
         * Get the name of the directory asscoaited with this message's entry.
         * @param aEntryDir A file name buffer which will contain the entry directory name once this function successfully returns.
         * @exception KErrXxx Leaves if the directory name cannot be obtained from iEntry.
         */
        void EntryDirectoryL(TFileName& aEntryDir) const;

    private:
        /**
         * C++ constructor
         */
        CMmsClientMessage();
        /**
         * 2nd level constructor
         *
         * Constructs class's member data.
         * @param aEntryId The ID of the entry this message is associated with.
         * @exception KErrXxx Leaves if no memory is available
         */
        void ConstructL(CMsvSession& aSession, TMsvId aEntryId);
        /**
         * Copies the index entry from this class's CMsvEntry context (iEntry) to this class's index entry (iIndexEntry).
         */
        void InitialiseIndexEntry();
        /**
         * Stores the Mms Client Message to the messaging store
         * @exception KErrXxx Standard EPOC stream leave codes.
         */
        void StoreMmsMessageL();

        /**
         * Forces iEntry to re-cache its children (and hence pick up any recent
         * index entry changes) by changing context away and then back again.
         * This is nasty, but otherwise iEntry may not yet have been notified
         * of very recent changes made elsewhere.
         * @exception KErrXxx Standard EPOC leave codes
         */
        void ForceEntryContextRefreshL();

    private:
        CMsvEntry* iEntry;  ///< The messaging entry where this message is stored
    };


#endif __MMSCLIENTMESSAGE_H__
