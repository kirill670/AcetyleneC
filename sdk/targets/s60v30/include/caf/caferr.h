// caferr.h
// Copyright (c) 2003 - 2005 Symbian Software Ltd. All rights reserved.

/** 
@file

This contains constant definitions required by clients accessing the 
Content Access Framework.

@publishedPartner
@released
*/



#ifndef __CAFERR_H__
#define __CAFERR_H__

#include <e32std.h>

/** Agent does not support the requested capability.

 */
const TInt KErrCANotSupported  =-17450;

/** 
 * Rights evaluation failed for the supplied intent. This implies that
 * rights were available, but their evaluation, in the context of
 * supplied intent, failed.
 */
const TInt KErrCANoPermission  =-17451; 

/** 
 * No rights were available for evaluation. A number of causes may
 * generate this error: Perhaps the rights were removed or lost
 * during a separate delivery
 */
const TInt KErrCANoRights      =-17452; 

/**
 * The Agent required is not present. This may occur if content
 * 'belongs' to an agent that is no longer available on the 
 * device. 
 */
const TInt KErrCANoAgent       =-17453;

/** Values specified are out of range. */
const TInt KErrCAOutOfRange    =-17454;

/** 
 * The rights were not available but are 'expected'. Will only be
 * returned if the agent supports this capability. 
 */
const TInt KErrCAPendingRights =-17455;

/**
 * A request to get the content size failed because the agent was unable
 * to determine it. This error may occur on circumstances where, say, the
 * content is streamed over HTTP.
 */
const TInt KErrCASizeNotDetermined = -17456;

/**
 The function failed because the agent needs the client to provide another
 file handle before the import can continue
 */
const TInt KErrCANewFileHandleRequired = -17457;

#endif // __CAFERR_H__
