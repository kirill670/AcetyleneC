// Ftpsess.h
//
// Copyright (c) Psion Software PLC 1998. All rights reserved.
//
// EPOC32 FTP Engine header file
//
// Author:	Philippe Gabriel
//
//
// Exports set of APIs simplyfying access to the FTP protocol
//
#if !defined(__FTPSESS_H__)
#define __FTPSESS_H__
#include <e32base.h>
#include <es_sock.h>
#include <f32file.h>


#define FTPSESS_VERSION_MAJOR 0x01 // The very first release
#define FTPSESS_VERSION_MINOR 0x03
#define FTPSESS_VERSION_NUMBER (FTPSESS_VERSION_MAJOR<<8)|FTPSESS_VERSION_MINOR

// Following Def as per RFC 959
const TUint KDefaultServerPiPort = 21;
//
// MInterface definition to provide callback functions to the client
//

class MFtpSessionNotifier
	{
public:
//
// Operation completion return codes.
// 
	enum TOpComp 
		{
		EOpComplete=0,	// No error
		EOpCanceled,	// User canceled last operation
		//Connection errors
		EHostNotExist,	// Connect address invalid
		ESocketError,	// Problem with socket operation
		EConnectionFailed,	// Can't connect to FTP port
		EPasswordNeeded,
		EAccountNeeded,	// i.e. anonymous login disallowed
		ELoginFailed,	// UserName,Password combination invalid
		ENotConnected,	// Not connected to a server
		EAlreadyConnected,	// Already connected to a server
		ETimedOut,	// Inactive for too long
		//Local filesystem errors
		EFileSystemError, 
		EFileOpenFailure, EFileReadError, EFileWriteError,
		EFileAlreadyExist,EFileNotExist,
		EDirAlreadyExist,EDirNotExist,
		// Permission error
		EPermissionDenied,
		//Remote filesystem errors
		ERemoteFileSystemError, 
		ERemoteFileOpenFailure, ERemoteFileReadError, ERemoteFileWriteError,
		ERemoteFileAlreadyExist,ERemoteFileNotExist,
		ERemoteDirAlreadyExist,ERemoteDirNotExist,
		ERestartNotSupported
		};
	// Normal operation completion
	virtual void Complete(void)=0;
	// Operation completed, more data to follow
	virtual void MoreData(void)=0;
	// Report the amount already transfered
	virtual void TransferProgress(TUint aProgress)=0;
	// User canceled ongoing operation
	virtual void Cancel(void)=0;
	// Peer reset the connection
	virtual void ConnReset(void)=0;
	// Connection error
	virtual void ConnectionError(TOpComp aTConnectionError)=0;
	// FTP server does not implement the operation requested
	virtual void OperationNotSupported(void)=0;
	// Local File system error
	virtual void LocalFileSystemError(TOpComp aTLocalFileSystemError)=0;
	// Remote File system error
	virtual void RemoteFileSystemError(TOpComp aTRemoteFileSystemError)=0;
	// Not specified yet
	virtual void EUnknownError()=0;
	// Message reported by server
	virtual void ServerMessage(const TDesC8&)=0;
	};		
//
// The CFTPSession class
//
class CFTPSession : public CBase

	{
public:
	enum TConnectionMode 
		{
		EActive=0, //server initiates DTP connection to client (see RFC959)
		Epassive   //client initiates DTP connection to server (see RFC959)
		};
	enum RepresentationType
		{
		EUninitialised=0,						   
		EBinary,	// File transfered in Binary mode, no translation
		EASCII		// File transfered in ASCII mode, translation
		};
	enum TransferMode
		{
		EStream=0,	// File transfered as stream of bytes
		Eblock		// File transfered as blocks, with header
					// needed to restart aborted transfer
		};
	enum TOpenMode
		{
		EOverwrite,
		ENoOverwrite,
		EExpand
		};

// Construction
//
public:

//
// Connection APIs
//
// Establish a connection with a server:
	virtual void Connect(	const TSockAddr& aNetAddr, //IP address
							const TDesC8& aUserName, 
							const TDesC8& aPassword,
							const TConnectionMode aConnectionMode=EActive)=0;

	virtual void Connect(	const THostName& aServerName, //DNS name
							const TDesC8& aUserName, 
							const TDesC8& aPassword,
							const TConnectionMode aConnectionMode=EActive, 
							const TUint aPort=KDefaultServerPiPort)=0;

// Close connection with a server
	virtual void Close()=0;

// Cancel last FTP operation
	virtual void Cancel()=0;

// Restart an aborted transfer operation
	virtual void Restart(const TUint aTFTPRestartOffset)=0;

//
// Transfer APIs
//
// Store a file on the server	
	virtual void Store(	const TDesC& aLocalFileName,
						const TDesC8& aNewRemoteFileName,
						const TBool	aOverwrite = EFalse,
						const RepresentationType aRepresentationType = EBinary,
						const TransferMode aTransferMode = EStream)=0;
	
// Get a file from the server
	virtual void Retrieve(	const TDesC8& aRemoteFileName,
							const TDesC& aNewLocalFileName,
							const TOpenMode	aOpenMode = EOverwrite,
							const RepresentationType aRepresentationType = EBinary,
							const TransferMode aTransferMode = EStream)=0;
	
//
// File system management functions
//
	virtual void ChangeDirectory(const TDesC8& aDirectoryName)=0;
	virtual void CreateDirectory(const TDesC8& aDirectoryName)=0;
	virtual void DeleteDirectory(const TDesC8& aDirectoryName)=0;
	virtual void GetCurrentDirectory(void)=0;
	virtual void ListDirectory(const	TDesC8& aDirectoryName,
										TDes8& aFileList)=0;
	
	virtual void DeleteFile(const TDesC8& aFileName)=0;
	virtual void RenameFile(const TDesC8& aRemoteFileName,
							const TDesC8& aNewRemoteFileName)=0;
// Returns 32-bit, with 
// ftpsess dll MAJOR_VERSION in msb of the msw
// ftpsess dll MINOR_VERSION in lsb of the msw
// ftpprot dll MAJOR_VERSION in msb of the lsw
// ftpprot dll MINOR_VERSION in lsb of the lsw
	IMPORT_C static TUint32 GetVersion(void);

	IMPORT_C static CFTPSession* NewL(MFtpSessionNotifier* aNotifier);

	virtual ~CFTPSession();
};
#endif