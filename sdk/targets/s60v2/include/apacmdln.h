// APACMDLN.H
//
// Copyright (c) Symbian Software Ltd 1997-2004.  All rights reserved.
//

#if !defined(__APACMDLN_H__)
#define __APACMDLN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif


class CApaCommandLine : public CBase
/** Information for launching an application.

This is often referred to as a command line and contains:

the name of an application DLL to be launched,

a document name,

a command code that defines the way the application is launched

trailing data; the structure of this depends on the application to be launched.

The information is held in a buffer implemented by a heap descriptor. 

@publishedAll
@released */
	{
public:
	// construction/destruction
	IMPORT_C static CApaCommandLine* NewL();
	IMPORT_C static CApaCommandLine* NewLC();
	IMPORT_C ~CApaCommandLine();
#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
	IMPORT_C static CApaCommandLine* New(HBufC* aCmdLine);
	IMPORT_C static CApaCommandLine* NewL(const TDesC& aCmdLine);
	IMPORT_C static CApaCommandLine* NewLC(const TDesC& aCmdLine);
	IMPORT_C void SetReserveLengthL(TInt aMaxLength);

	// operations on the full command line
	IMPORT_C TInt SetFullCommandLine(HBufC* aCmdLine);
	IMPORT_C void SetFullCommandLineL(const TDesC& aCmdLine);
	IMPORT_C TPtrC FullCommandLine() const;

	// operations on the library name
	IMPORT_C void SetLibraryNameL(const TDesC& aLibName);
	IMPORT_C TPtrC LibraryName() const;
#endif

	// Getting/setting the CApaCommandLine to/from process environment-slots
	IMPORT_C void SetProcessEnvironmentL(RProcess& aProcess) const;
	IMPORT_C static TInt GetCommandLineFromProcessEnvironment(CApaCommandLine*& aCommandLine);

	// Getting/setting the CApaCommandLine to/from a server IPC-message
	IMPORT_C void GetIpcArgsLC(TIpcArgs& aIpcArgs) const;
	IMPORT_C void ConstructCmdLineFromMessageL(const RMessage2& aMessage);

	// operations on the document name
	IMPORT_C void SetDocumentNameL(const TDesC& aDocName);
	IMPORT_C TPtrC DocumentName() const;

	// operations on the executable name
	IMPORT_C void SetExecutableNameL(const TDesC& aAppName);
	IMPORT_C TPtrC ExecutableName() const;

	// operations on the tail end
	IMPORT_C void SetTailEndL(const TDesC8& aTailEnd);
	IMPORT_C TPtrC8 TailEnd() const;

	// operations on the command
	IMPORT_C void SetCommandL(TApaCommand aCommand);
	IMPORT_C TApaCommand Command() const;

#if defined(EKA2) || defined(APACMDLN_EXPOSE_PASSING_FILE_BY_HANDLE)
	// operations on the file passed by handle
	IMPORT_C void SetFileByHandleL(const RFs& aFsSession, const RFile& aFile);
	IMPORT_C void GetFileByHandleL(RFs& aFsSession, RFile& aFile) const;
#endif
public:

	// operations on the server requirement/differentiator number - 0 means no server, non-zero sets the differentiator for the server name
	IMPORT_C void SetServerNotRequiredL();
	IMPORT_C void SetServerRequiredL(TUint aServerDifferentiator);
	IMPORT_C TUint ServerRequired() const;

	// Operations to support starting an application with a specific screen number
	IMPORT_C void SetDefaultScreenL(TInt aDefaultScreenNumber);
	IMPORT_C TInt DefaultScreen() const;

	IMPORT_C static TInt EnvironmentSlotForPublicUse(TInt aIndex);

private:
	CApaCommandLine();
	void SetServerDifferentiatorL(TUint aServerDifferentiator);
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);

#ifndef SYMBIAN_REMOVE_UI_FRAMEWORKS_V1
private:
	void SetCmdLineL();
	TInt Parse(const TDesC& aCmdLine);
	TInt Parse(HBufC* aCmdLine); // takes ownership of aCmdLine if it succeeds
	TPtrC StripQuotes(const TDesC& aDes) const;
	static TBool FileNameNeedsQuotes(const TDesC& aFileName);
private:
	struct SOption
		{
		const TDesC* iToken;
		TUint* iResult;
		};
private:
	HBufC* iCmdLine;
#endif //#ifndef SYMBIAN_REMOVE_UI_FRAMEWORKS_V1
private:
	enum
		{
		EEnvironmentSlotUnused=0,
		EEnvironmentSlotDocumentName=1,
		EEnvironmentSlotExecutableName=2,
		EEnvironmentSlotTailEnd=3,
		EEnvironmentSlotCommand=4,
		EEnvironmentSlotServerDifferentiator=5,
		EEnvironmentSlotDefaultScreenNumber=6,
		EEnvironmentSlotFsSession=7,
		EEnvironmentSlotFile=8,

		EFirstEnvironmentSlotForPublicUse=10,
		ENumberOfEnvironmentSlotsForPublicUse=2
		};
	enum
		{
		EIpcSlot=0
		};
public:
	enum
		{
		EIpcFirstFreeSlot=2
		};
private:
	HBufC* iDocumentName;
	HBufC* iExecutableName;
	HBufC8* iTailEnd;
	TApaCommand iCommand;
	TUint iServerDifferentiator;
	TInt iDefaultScreenNumber;
	RFs iFsSession; // only used on the "setting" side, not the "getting" side
	RFile iFile; // only used on the "setting" side, not the "getting" side
	};

#endif
