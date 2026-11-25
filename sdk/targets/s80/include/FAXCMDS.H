/**@file
   @publishedPartner
   @removed
 */

// FAXCMDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined (__FAXCMDS_H__)
#define __FAXCMDS_H__

#if !defined (__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif

// will be in <msvstd.hrh> in next release
#define KMtmFirstFreeMtmFunctionId 			0x100000 // MTM can use any value above this

/** Fax-specific commands that can be issued through CFaxMtmClient::InvokeAsyncFunctionL(). */
enum TFaxCmds {
	/** Dials the number specified and then attempt to receive a "polled" fax from 
	the fax machine at the other end of the telephone line. 
	
	The aParameter argument should contain a packaged telephone number specifying 
	the telephone number to be dialed by the MTM. */
	KFaxMTMDialAndReceive = KMtmFirstFreeMtmFunctionId,
	/** Transmits the fax to the receiving machine via an existing connection. 
	
	This operation assumes that a telephone connection has already been established 
	with another fax machine. On success, the message is placed in the "Sent" 
	folder, if it exists. Note that all recipients of the message are ignored 
	as no dialing occurs. */
	KFaxMTMImmediateTransmitCopy,
	/** Waits for handshaking signals from the transmitting fax machine, and then automatically 
	receives that message. 
	
	This operation assumes that a telephone connection has already been established 
	with another fax machine. */
	KFaxMTMImmediateReceive,
	/** Renders the message entries specified in aSelection (if they are not rendered 
	already) and then sends each rendered file to each recipient specified in 
	the message header. 
	
	When a message has been successfully sent to all receipients identified in 
	the message, the message is moved to the Outbox, if it exists. If transmission 
	fails to one or more recipients specified in the message, then the message 
	will be left in the Outbox, the TMsvEntry::Failed() flag will be set, and 
	the first error code that occurred during the transmission will be stored 
	in the TMsvEntry::iError member variable. */
	KFaxMTMRingAndTransmitCopy,
	/** Transmits the fax to the receiving machine via an existing connection. 
	
	This operation assumes that a telephone connection has already been established 
	with another fax machine. On success, the message is deleted. Note that all 
	recipients of the message are ignored as no dialing occurs. */
	KFaxMTMImmediateTransmitMove,
	/** Renders the message entries specified in aSelection (if they are not rendered 
	already) and then sends each rendered file to each recipient specified in 
	the message header. 
	
	When a message has been successfully sent to all receipients identified in 
	the message, the message is deleted. If transmission fails to one or more 
	recipients specified in the message, then the message will be left in the 
	Outbox, the TMsvEntry::Failed() flag will be set, and the first error code 
	that occurred during the transmission will be stored in the TMsvEntry::iError 
	member variable. */
	KFaxMTMRingAndTransmitMove,
	/** See the KFaxMTMDialAndReceive operation. */
	KFaxMtmPolledReceive,
	/** Renders the contents of the CRichText stream (and hence any CPicture objects 
	embedded in that rich text stream) into a single file called "IMAGE", which 
	will be placed in the folder path identified by aParameter. */
	KFaxMTMRenderToFile,
	/** Add the messages specified in aSelection to the task scheduler list, and request 
	that the "copy" operation is used to send those messages. 
	
	Each TMsvEntry identified in aSelection must have the same iDate and OffPeak() 
	value (though OffPeak() is not supported in the v7.0 Messaging engine). 
	
	If the messages identified by aSelection are scheduled successfully, the SendStatus() 
	and Scheduled() entries on each message TMsvEntry will be set by the scheduler 
	
	
	After a successful send, messages are placed in the "Sent" folder (if that 
	folder exists). 
	
	The aParameter argument is not used by this command. */
	KFaxMTMScheduleCopy,
	/** Performs as KFaxMTMScheduleCopy, except that after a successful send, the messages 
	are deleted. */
	KFaxMTMScheduleMove,
	/** Removes all messages specified in aSelection from the task scheduler list. 
	
	If successful, the messages will have their SendStatus() set to KMsvSendStateSuspended 
	on completion of this operation. 
	
	The aParameter argument is not used by this function. */
	KFaxMTMDeleteSchedule,
	/** Check the current scheduled status of the messages specified by aSelection. 
	
	If successful, the Scheduled() and iDate members of each TMsvEntry identified 
	in the selection will be changed to represent that message's current status. 
	
	The aParameter argument is not used by this function. */
	KFaxMTMCheckSchedule,
	KFaxMTMSendScheduledCopy,
	KFaxMTMSendScheduledMove,
	KFaxMTMWatcherReceive
};

#endif
