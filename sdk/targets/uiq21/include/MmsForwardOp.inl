// $Workfile: MmsForwardOp.inl $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Simonk $
// $Revision: 2 $
// $Date: 15/11/01 10:07 $
//


/** @file
    This file contains inline implementations of TMmsForwardOpProgress methods
 */

#ifndef __MMSFORWARDOP_INL__
#define __MMSFORWARDOP_INL__

#include <MsvIds.h>             // KMsvNullIndexEntryId

inline TMmsForwardOpProgress::TMmsForwardOpProgress() : 
 iProgressId(KUidForwardOpProgress),
 iState(EInit),
 iMessageId(KMsvNullIndexEntryId),
 iErrorCode(KErrNone)
/**
 *  Default constructor
 */
    {

    }

#endif //__MMSFORWARDOP_INL__