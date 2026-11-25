// SysLog.h: interface for the CInstSysLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__INST_SYSLOG_H__)
#define __INST_SYSLOG_H__

#include <e32base.h>
#include <f32file.h>

class RReadStream;
class RWriteStream;

const TInt KInstSysLogMaxNameLen=50;

class TInstSysLogEntry
	{
	public:
		enum TInstEvent
			{
			EInstInstallEvent,
			EInstRemoveEvent,
			EInstPartialInstallEvent,
			EInstAbortInstallEvent
			};
	public:
		TInstSysLogEntry();
		TInstSysLogEntry(TInstEvent aAction, TDesC& aName);
		static TInstSysLogEntry* NewL(RReadStream& aStream);

		inline const TDesC& Name() {return iName;};
		inline TTime Time() {return iTime;};
		inline TInstEvent Action() {return iAction;};

		void ExternalizeL(RWriteStream& aStream);
		void InternalizeL(RReadStream& aStream);
	private:
		TBuf<KInstSysLogMaxNameLen> iName;
		TTime iTime;
		TInstEvent iAction;
	};

class CInstSysLog : public CBase
	{
	public:
		IMPORT_C static CInstSysLog* NewL();
		inline const CArrayFixFlat<TInstSysLogEntry>* Entries() {return iLogEntry;};
	public:
		virtual ~CInstSysLog();
		void AppendEntryL(TInstSysLogEntry& aLogEntry);
		void WriteLogFile() { TRAPD(err,WriteLogFileL());}
	private:
		void ConstructL();
		void ExternalizeL(RWriteStream& aStream);
		void InternalizeL(RReadStream& aStream);
		void ReadLogFileL();
		void WriteLogFileL();
	private:
		RFs iFsSession;
		RFile* iLogFile;
		CArrayFixFlat<TInstSysLogEntry>* iLogEntry;
	};

#endif
