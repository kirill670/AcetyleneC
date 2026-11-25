// $Workfile: MmsReplyOp.inl $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Simonk $
// $Revision: 2 $
// $Date: 15/11/01 10:07 $
//


/** @file
    This file contains inline implementations of TMmsReplyOpProgress methods
 */

#ifndef __MMSREPLYOP_INL__
#define __MMSREPLYOP_INL__

#include <MsvIds.h>             // KMsvNullIndexEntryId

inline TMmsReplyOpProgress::TMmsReplyOpProgress() : 
 iProgressId(KUidReplyOpProgress),
 iState(EInit),
 iMessageId(KMsvNullIndexEntryId),
 iErrorCode(KErrNone)
/**
 *  Default constructor
 */
    {

    }

#endif //__MMSREPLYOP_INL__