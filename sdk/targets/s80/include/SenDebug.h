// SenDebug.h
//
// Central place for debug-type macros
//

#ifndef SEN_DEBUG_H
#define SEN_DEBUG_H

// Note that _DEBUG is automatically defined for debug builds

// To enable file logging: please comment following #ifdef line and uncomment #ifdef TRUE
#ifdef _DEBUG

#include <e32svr.h>

#define _SENDEBUG	1
#define SENDEBUG(parameters)		RDebug::Print parameters
#define SENDEBUG_L(string)			RDebug::Print(_L(string))	// single param

#define LOG_CONNECT					Log()->Connect()
#define LOG_CREATELOG(parameters)	Log()->CreateLog parameters
#define LOG_WRITE(parameters)		Log()->Write parameters
#define LOG_WRITE_L(string)			Log()->Write(_L(string))	// single param
#define LOG_WRITEFORMAT(parameters)	Log()->WriteFormat parameters
#define LOG_CLOSELOG				Log()->CloseLog()
#define LOG_CLOSE					Log()->Close()
#define LOG_WRITEALL(parameters) \
	TInt i = 0; \
	TInt amount = 100; \
	while(i<parameters.Length()) \
		{ \
		if(( parameters.Length()-i) < 100) \
			amount = parameters.Length()-i; \
		Log()->Write(parameters.Mid(i,amount)); \
		i+=100; \
		}

#else

#define SENDEBUG(parameters)
#define SENDEBUG_L(string)

#define LOG_CONNECT
#define LOG_CREATELOG(parameters)
#define LOG_WRITE(parameters)
#define LOG_WRITE_L(string)
#define LOG_WRITEFORMAT(parameters)
#define LOG_CLOSELOG
#define LOG_CLOSE
#define LOG_WRITEALL(parameters)

#endif // _DEBUG

#endif // SEN_DEBUG_H
