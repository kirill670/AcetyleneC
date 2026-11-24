// 
// WAPlog.h
// Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.
// 
// Created at: 07-Sep-99 9:46:31 AM

//
// Comments: WAP Logging public header, defines the name of the 
//			 file to use for WAP activity logging messages
// 

#if !defined(__WAPLOG_H__)
#define __WAPLOG_H__

#if !defined(__E32STD_H__)
#include <E32Std.h>
#endif

#ifdef _DEBUG
/**
@publishedAll
@deprecated
*/
_LIT(KWapLogFileName,"WAPLog.html");
#define __LOG_WAP_FILE_NAME KWapLogFileName
#else
#define __LOG_WAP_FILE_NAME
#endif

#endif
