/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis
*/

#ifndef __EPOCLOG_H
#define __EPOCLOG_H

#ifdef __cplusplus

#include <e32base.h>

IMPORT_C void Log(const TDesC8&);
IMPORT_C void Log(const TDesC16&);
IMPORT_C void Log(const char*);
IMPORT_C void Log(const unsigned short*);
IMPORT_C void Log(const int);
IMPORT_C void Log(TUid aUid);
IMPORT_C void LogHex(const TUint);
IMPORT_C void LogSp(const TDesC8&);
IMPORT_C void LogSp(const TDesC16&);
IMPORT_C void LogSp(const char*);
IMPORT_C void LogSp(const int);
IMPORT_C void LogHexSp(const TUint);
IMPORT_C void LogNl(const char* =NULL);
IMPORT_C void LogNl(const int);
IMPORT_C void LogNl(TUid aUid);
IMPORT_C void LogInd(const char*);
IMPORT_C void LogIndNl(const char*);
IMPORT_C void LogLine();
IMPORT_C void LogBool(TBool aBool);
IMPORT_C void CloseLogFile();

class LogIndent 
	{
private:
    const char* func;
public:
    IMPORT_C LogIndent(const char*);
    IMPORT_C ~LogIndent();
	};

#define LogFunc(v) LogIndent _li(v)

#else	// !__cplusplus

extern void LogFunc(const char*);

#endif	// !__cplusplus

#define LogThis() LogSp("("); Log((int)this); Log(")");

#endif // __EPOCLOG_H