/*
 * NOKIA MOBILE PHONES
 * DIGITAL CONVERGENCE
 * LINDA SW
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *           Bio Control Observer
 *           -------------------------
 * 
 *           SW Include Document - C++
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Module name:    MsgEditorUtils
 * 
 * $Archive: /Erin messaging/Implementation/MSGEDITORUTILS/Inc/MsgBioControlObserver.h $
 * 
 * $Revision: 1 $
 * 
 * 
 * Copyright (c) 1998. Nokia Mobile Phones
 * 
 * 
 * Change History:
 * 
 * History: MMsgBioControlObserver.h $
 * 
 *
 *---------------------------------------------------------------------------
 */


/*
-----------------------------------------------------------------------------

    DESCRIPTION

    Defines an API for Bio Control Observer. The MMsgBioControlObserver is used
    for observing the bio control from the editor application.

-----------------------------------------------------------------------------
*/


#if !defined(__MSGBIOCONTROLOBSERVER_H__)
#define __MSGBIOCONTROLOBSERVER_H__


// CLASS DEFINITIONS

class MMsgBioControlObserver
    {
    public:
        enum TMsgCommands
            {
            EMsgNone = 0,
            EMsgSave,
            EMsgReply,          // Not supported by sms editor
            EMsgForwad,         // Misspelling but not fixed because many controls may already use this, although this is not supported by sms viewer
            EMsgSend,
            EMsgAddressBook,          
            EMsgClose,
            EMsgUnLockEntry,    // Use this for saving the message data to CMsvStore in editor. Only used in Series 80
            EMsgLockEntry       // Call this immediately after saving data to lock the message entry back. Only used in Series 80

            };
	
    public:
        virtual TInt FirstFreeCommand() const = 0;
        virtual TInt RequestHandleCommandL(TMsgCommands aCommand) = 0;
        virtual TBool IsCommandSupported(TMsgCommands aCommand) const = 0;
    };


#endif // MSGBIOCONTROLOBSERVER

