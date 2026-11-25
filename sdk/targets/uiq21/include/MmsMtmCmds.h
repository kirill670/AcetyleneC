// $Workfile: MmsMtmCmds.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 6 $
// $Date: 27/02/02 11:46 $
//


/** @file
    This file contains the command IDs used by the client MTM's InvokeAsyncFunctionL() method.
 */



#ifndef __MMSMTMCMDS_H__
#define __MMSMTMCMDS_H__


#include <msvstd.hrh> // KMtmFirstFreeMtmFunctionId


/**
 * MTM-specific commands for the MMS MTM.
 */
enum TMmsMtmCmds
    {
    KMmsMtmFetchMessage = KMtmFirstFreeMtmFunctionId,   ///< Initiates a fetch which returns an operation providing full progress information. N.B. Use for a manual fetch only. For an auto fetch (from the watcher) use KMmsMtmAutoFetchMessage.
    KMmsMtmBackgroundFetchMessage,                      ///< Initiates a "fire and forget" fetch which returns an operation which completes immediately. N.B. Use for a manual fetch only. For an auto fetch (from the watcher) use KMmsMtmBackgroundAutoFetchMessage.
    KMmsMtmSendMessage,                                 ///< Initiates a send which returns an operation providing full progress information
    KMmsMtmBackgroundSendMessage,                       ///< Initiates a "fire and forget" send which returns an operation which completes immediately
    KMmsMtmAutoFetchMessage,                            ///< Initiates an automatic fetch which returns an operation providing full progress information. N.B. Use for an automatic fetch only. For a manual fetch use KMmsMtmFetchMessage.
    KMmsMtmBackgroundAutoFetchMessage,                  ///< Initiates a "fire and forget" automatic fetch which returns an operation which completes immediately. N.B. Use for a automatic fetch only. For a manual fetch use KMmsMtmBackgroundFetchMessage.
    KMmsMtmAcknowledgeNotification,                     ///< Send an acknowledgement message on receipt of notification when an automatic fetch is not required.
    KMmsMtmRejectNotification                           ///< Send a M-NotifyResp.ind with 'rejected' status (after receiving an invalid M-Notification.ind)
    };


#endif // __MMSMTMCMDS_H__
