/**
@file CDBLEN.H
@publishedAll
@released

Maximum length of a text field from the Comms database
in a file alone so it can be used in a resource file.

Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
*/

#ifndef __CDBLEN_H__
#define __CDBLEN_H__

#include <e32def.h>

/**
Maximum text field length (in characters).
@publishedAll
@released
*/
const TInt KCommsDbSvrMaxFieldLength=50;

/**
@publishedAll
@released
*/
const TInt KCommsDbSvrDefaultTextFieldLength=50;
const TInt KCommsDbSvrMaxUserIdPassLength=255;
const TInt KCommsDbSvrRealMaxFieldLength=KCommsDbSvrMaxUserIdPassLength;

/** Maximum length of table and column names. 
@publishedAll
@released */
const TInt KCommsDbSvrMaxColumnNameLength=50;

#endif
