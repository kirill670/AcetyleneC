// PUSHLOG.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

/** @file PUSHLOG.H
 * This file contains the declaration of the MWapPushLog which is a logging interface.
 */

#ifndef __PUSHLOG_H__
#define __PUSHLOG_H__


/**
 * Macros
 *
 */

#define __LOG_ALWAYS(a) {_LIT(name,a); iLog.WPLPrintf(name);} 
#define __LOG_PTR_ALWAYS(a) {_LIT(name,a); iLog->WPLPrintf(name);} 
#define __LOG_PAR_ALWAYS(a) {_LIT(name,a); aLog.WPLPrintf(name);}
#define __LOG_ERROR_ALWAYS(a,b) {_LIT(name,a); iLog.WPLLogError(name,b);}

#if defined(_DEBUG)
#define __LOG_DEBUG(a) __LOG_ALWAYS(a) 
#define __LOG_PTR_DEBUG(a) __LOG_PTR_ALWAYS(a) 
#define __LOG_PAR_DEBUG(a) __LOG_PAR_ALWAYS(a)
#define __LOG_MSG_DEBUG(a) iLog.WPLPrintf(a)
#define __LOG_ERROR_DEBUG(a,b) __LOG_ERROR_ALWAYS(a,b)
#else
#define __LOG_DEBUG(a) 
#define __LOG_PTR_DEBUG(a) 
#define __LOG_PAR_DEBUG(a) 
#define __LOG_MSG_DEBUG(a)
#define __LOG_ERROR_DEBUG(a,b) 


#endif


/**
 * Forward Declares
 *
 */
class CPushMessage;

/**
 * MWapPushLog
 * A logging interface, primarily for debugging.  
 * If  c:\logs\push\ is on the device, a log file will be created.
 *		
 */
//##ModelId=3B659EEA0062
class MWapPushLog
	{
public:
	//##ModelId=3B659EEA007A
	virtual void WPLPrintf(const TDesC& aDescription)=0;
	//##ModelId=3B659EEA007C
	virtual void WPLPrintf(CPushMessage& aMessage)=0;
	//##ModelId=3B659EEA0078
	virtual void WPLLogBinaryAsHex(const TDesC& aDescription)=0;
	//##ModelId=3B659EEA006C
	virtual void WPLLogError(const TDesC& aDescription,TInt aError)=0;
	};


#endif
