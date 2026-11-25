/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis
*/

#ifndef __EPOCBRIDGEDEF_H
#define __EPOCBRIDGEDEF_H

#include <e32def.h>

#include "epocplatform.h"

// Some little hangovers from compiler.h - need a platform.h within core
#if defined(_UNICODE)
typedef TText16 uni_char;
#else
typedef char uni_char;
#endif
typedef TUint8 uint8;
typedef int BOOL;
typedef int OP_STATUS;
class OpStatus
    {
public:
    enum {OK,ERR};
    };
class OpStringC8;
class OpString8;
class OpStringC16;
class OpString16;
#ifdef _UNICODE
typedef OpStringC16 OpStringC;
typedef OpString16 OpString;
#else
typedef OpStringC8 OpStringC;
typedef OpString8 OpString;
#endif

#if defined(_DEBUG) && !defined(ER5)
// A unique integer is given to every socket used when logging to distinguish between sockets
# define SOCKETACCOUNTING 
#endif

#endif // __EPOCBRIDGEDEF_H
