// $Workfile: MmsErrors.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 1 $
// $Date: 20/12/01 11:40 $
//


/** @file
 *  This file contains error codes for the MMS Server MTM.
 */


#ifndef __MMSERRORS_H__
#define __MMSERRORS_H__


// Error codes for the MMS Server MTM
const TInt KMmsErrorBase                    = -5000;
const TInt KMmsErrUnspecified               = KMmsErrorBase;
const TInt KMmsErrServiceDenied             = KMmsErrorBase - 1;
const TInt KMmsErrMessageFormatCorrupt      = KMmsErrorBase - 2;
const TInt KMmsErrSendingAddressUnresolved  = KMmsErrorBase - 3;
const TInt KMmsErrMessageNotFound           = KMmsErrorBase - 4;
const TInt KMmsErrNetworkProblem            = KMmsErrorBase - 5;
const TInt KMmsErrContentNotAccepted        = KMmsErrorBase - 6;
const TInt KMmsErrUnsupportedMessage        = KMmsErrorBase - 7;
const TInt KMmsErrInvalidPDU                = KMmsErrorBase - 8;
const TInt KMmsErrNoData                    = KMmsErrorBase - 9;
const TInt KMmsNoResponseStatus             = KMmsErrorBase - 10;


#endif // __MMSERRORS_H__