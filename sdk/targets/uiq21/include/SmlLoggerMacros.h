//
// SMLLOGGERMACROS.H
//
#if !defined(__SMLLOGGERMACROS_H__)
#define __SMLLOGGERMACROS_H__

#include <smlloggingenabled.h>
#if defined(SML_LOGGING_ENABLED)
#include <e32std.h>
#include "smllogger.h"
_LIT(KSharedFile, "SharedFile");	// The name of the shared log file
_LIT(KLogFileDir, "SyncML");		// The name of the directory where the shared log file goes


#define SLOG_CONNECTL		ConnectSharedLoggerL(KLogFileDir, KSharedFile, ETrue);\
							SetDateLogging(EFalse);\
							SetTimeLogging(EFalse);\
							SetSrcFilenameLogging(EFalse);
#define SLOG_DISCONNECT		DisconnectSharedLog();
#define SLOG_DISABLE		DisableLogging();
#define SLOG_ENABLE			EnableLogging();
#define SLOG_BEGIN(message)	EnteredNewFunction();\
							WriteSharedLogMessage(TPtrC8((TText8*)__FILE__), __LINE__,ESimpleLogging,ETrue, _L8(message));								
#define SLOG_END(message)	LeftFunction();\
							WriteSharedLogMessage(TPtrC8((TText8*)__FILE__), __LINE__, ESimpleLogging,ETrue, _L8(message));
#define SLOG_WRITE(message)	WriteSharedLogMessage(TPtrC8((TText8*)__FILE__), __LINE__,ESimpleLogging,ETrue,_L8(message));
#define SLOG_WRITED(buf)	WriteSharedLogMessage(TPtrC8((TText8*)__FILE__), __LINE__, ESimpleLogging,ETrue, buf);
#define SLOG_DATEOFF		SetDateLogging(EFalse);
#define SLOG_DATEON			SetDateLogging(ETrue);
#define SLOG_TIMEOFF		SetTimeLogging(EFalse);
#define SLOG_TIMEON			SetTimeLogging(ETrue);
#define SLOG_FILEOFF		SetSrcFilenameLogging(EFalse);
#define SLOG_FILEON			SetSrcFilenameLogging(ETrue);
#define SLOG_LINEOFF		SetSrcLineLogging(EFalse);
#define SLOG_LINEON			SetSrcLineLogging(ETrue);

#define	PLOG_DECLARE		CSmlLogger*	iPrivateLog;
#define PLOG_CONNECTL(file)	iPrivateLog= CSmlLogger::NewL();\
							iPrivateLog->ConnectL(KLogFileDir, file, ETrue);\
							iPrivateLog->SetDateLogging(EFalse);\
							iPrivateLog->SetTimeLogging(EFalse);\
							iPrivateLog->SetSrcFilenameLogging(EFalse);
#define PLOG_DISCONNECT		if (iPrivateLog) iPrivateLog->Disconnect();\
							delete iPrivateLog;\
							iPrivateLog = NULL;
#define PLOG_DISABLE		iPrivateLog->DisableLogging();
#define PLOG_ENABLE			iPrivateLog->EnableLogging();
#define PLOG_BEGIN(message)	iPrivateLog->WriteLogMessage(TPtrC8((TText8*)__FILE__), __LINE__,ESimpleLogging,EFalse,_L8(mesage));\
							iPrivateLog->EnteredNewFunction();
#define PLOG_END(message)	iPrivateLog->LeftFunction();\
							iPrivateLog->WriteLogMessage(TPtrC8((TText8*)__FILE__), __LINE__, ESimpleLogging,EFalse, _L8(message));
#define PLOG_WRITE(message)	iPrivateLog->WriteLogMessage(TPtrC8((TText8*)__FILE__), __LINE__, ESimpleLogging,EFalse,_L8(message));
#define PLOG_WRITED(buf)	iPrivateLog->WriteLogMessage(TPtrC8((TText8*)__FILE__), __LINE__, ESimpleLogging,EFalse, buf);
#define PLOG_DATEOFF		iPrivateLog->SetDateLogging(EFalse);
#define PLOG_DATEON			iPrivateLog->SetDateLogging(ETrue);
#define PLOG_TIMEOFF		iPrivateLog->SetTimeLogging(EFalse);
#define PLOG_TIMEON			iPrivateLog->SetTimeLogging(ETrue);
#define PLOG_FILEOFF		iPrivateLog->SetSrcFilenameLogging(EFalse);
#define PLOG_FILEON			iPrivateLog->SetSrcFilenameLogging(ETrue);
#define PLOG_LINEOFF		iPrivateLog->SetSrcLineLogging(EFalse);
#define PLOG_LINEON			iPrivateLog->SetSrcLineLogging(ETrue);
#else //#if defined(SML_LOGGING_ENABLED)
#define SLOG_CONNECTL		;
#define SLOG_DISCONNECT		;
#define SLOG_DISABLE		;
#define SLOG_ENABLE			;
#define SLOG_BEGIN(message)	;
#define SLOG_END(message)	;					
#define SLOG_WRITE(message)	;
#define SLOG_WRITED(buf)	;
#define SLOG_DATEOFF		;
#define SLOG_DATEON			;
#define SLOG_TIMEOFF		;
#define SLOG_TIMEON			;
#define SLOG_FILEOFF		;
#define SLOG_FILEON			;
#define SLOG_LINEOFF		;
#define SLOG_LINEON			;
#define SLOG_RESET			;

#define	PLOG_DECLARE		;
#define PLOG_CONNECTL(file)	;
#define PLOG_DISCONNECT		;
#define PLOG_DISABLE		;
#define PLOG_ENABLE			;
#define PLOG_BEGIN(message)	;
#define PLOG_END(message)	;
#define PLOG_WRITE(message)	;
#define PLOG_WRITED(buf)	;
#define PLOG_DATEOFF		;
#define PLOG_DATEON			;
#define PLOG_TIMEOFF		;
#define PLOG_TIMEON			;
#define PLOG_FILEOFF		;
#define PLOG_FILEON			;
#define PLOG_LINEOFF		;
#define PLOG_LINEON			;
#endif // #if defined(SML_LOGGING_ENABLED)

#endif //#if !defined(__SMLLOGGERMACROS_H__)