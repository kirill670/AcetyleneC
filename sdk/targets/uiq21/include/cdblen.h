// CDBLEN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Maximum length of a text field from the Comms database
//
// in a file alone so it can be used in a resource file

#ifndef __CDBLEN_H__
#define __CDBLEN_H__

#include <e32def.h>

/** Maximum text field length (in characters). */
const TInt KCommsDbSvrMaxFieldLength=50;
const TInt KCommsDbSvrDefaultTextFieldLength=50;
const TInt KCommsDbSvrMaxUserIdPassLength=255;
const TInt KCommsDbSvrRealMaxFieldLength=KCommsDbSvrMaxUserIdPassLength;

/** Maximum length of table and column names */
const TInt KCommsDbSvrMaxColumnNameLength=50;

#endif
