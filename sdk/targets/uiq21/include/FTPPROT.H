// ftprot.h
//
// Copyright (c) Psion Software PLC 1998. All rights reserved.
//
// FTP Protocol header file
//
// Author:	Philippe Gabriel
//

#if !defined(__FTPPROT_H__)
#define __FTPPROT_H__

#include <e32base.h>
#include <es_sock.h>

#define FTPPROTDLL_VERSION_MAJOR 0x01 // The very first release
#define FTPPROTDLL_VERSION_MINOR 0x03
#define FTPPROTDLL_VERSION_NUMBER (FTPPROTDLL_VERSION_MAJOR<<8)|FTPPROTDLL_VERSION_MINOR

class MFtpProtocolNotifier
	{
// Operation completion return codes.
	
public:
	enum TOpComp 
	{
	EOpComplete=0,
	EOpCanceled,	// User canceled last operation
	EOpFailed, 
	ESocketError, 
	// Connection errors
	EOpConnectionReset,EOpConnectionFailed,EHostNotFound,
	// Transfer error 
	EXferReset,EXferNotInitialised,
	//Transfer notification
	EPacketReceived,EPacketSent
	};
public:
	virtual ~MFtpProtocolNotifier(){};
	virtual void ServerPositiveAnswerNotification(const TOpComp aStatus)=0;
	virtual void ServerMessage(const TDesC8& aMessage)=0;
	virtual void ServerXFerNotification(const TOpComp aStatus)=0;
	virtual void ServerNegativeAnswerNotification(const TOpComp aStatus)=0;
	virtual void ErrorNotification(const TOpComp aStatus)=0;
	};


// FtpEngine

class CFtpProtocol : public CBase
	{
public:

// Establish a connection:
	virtual void Connect(TSockAddr& aNetAddr)=0;	// IP address
	virtual void Connect(const THostName& aServerName)=0;  // URL name
	virtual void Connect(const THostName& aServerName, const TUint aPort)=0; // URL name + port

// FTP commands, presented in the same order as RFC959:
	virtual void User(const TDesC8& aParam)=0;
	virtual void Pass(const TDesC8& aParam)=0;
	virtual void Acct(const TDesC8& aParam)=0;
	virtual void Cwd(const TDesC8& aParam)=0;
	virtual void Cdup(void)=0;
	virtual void Smnt(const TDesC8& aParam)=0;
	virtual void Quit(void)=0;
	virtual void Rein(void)=0;
	virtual void Port(void)=0;			// Sets the DTP port to one allocated by ESOCK
	virtual void Port(TUint aPort)=0;	// Sets the DTP port to a specific one
	virtual void Pasv(void)=0;
	virtual void Type(const TDesC8& aParam)=0;
	virtual void Type(const TDesC8& aParam1, const TDesC8& aParam2)=0;
	virtual void Stru(const TDesC8& aParam)=0;
	virtual void Mode(const TDesC8& aParam)=0;
	virtual void Retr(const TDesC8& aFileName)=0;
	virtual void Stor(const TDesC8& aFileName)=0;
	virtual void Stou(void)=0;
	virtual void Appe(const TDesC8& aFileName)=0;
	virtual void Allo(const TDesC8& aParam)=0;
	virtual void Allo(const TDesC8& aParam1, const TDesC8& aParam2)=0;
	virtual void Rest(const TDesC8& aParam)=0;
	virtual void Rnfr(const TDesC8& aFileName)=0;
	virtual void Rnto(const TDesC8& aFileName)=0;
	virtual void Abor(void)=0;
	virtual void Dele(const TDesC8& aFileName)=0;
	virtual void Rmd(const TDesC8& aParam)=0;
	virtual void Mkd(const TDesC8& aParam)=0;
	virtual void Pwd(void)=0;
	virtual void List(void)=0;
	virtual void List(const TDesC8& aParam)=0;
	virtual void Nlst(void)=0;
	virtual void Nlst(const TDesC8& aParam)=0;
	virtual void Site(const TDesC8& aParam)=0;
	virtual void Syst(void)=0;
	virtual void Stat(const TDesC8& aParam)=0;
	virtual void Stat(void)=0;
	virtual void Help(const TDesC8& aParam)=0;
	virtual void Help(void)=0;
	virtual void Noop(void)=0;
// Buffer management for transfer
	// Following functions pass a pointer to a buffer
	// to transfer data to/from the Dtp channel
	// Before an operation which cause data to transit on the 
	// DTP channel to occur (Nlst, List, Retr, Stor)
	// a Buffer must be provided with the following api
	// Also when the client is notified of a MoreData event
	// It must reissue the following operation to get the rest of
	// the data
	virtual void SendBuffer(TDes8* aBuffer)=0;
	virtual void RecvBuffer(TDes8* aBuffer)=0;
	virtual void SendEOF(void)=0; //Finishes the transfer initiated by a stor command
	virtual void UserCancel(void)=0;

// Copies the 3 digits answer received from the FTP server
	virtual void FTPServerAnswer(TDes& aServerAnswer)=0;
// Returns 32-bit, with MAJOR_VERSION in the highest byte
// MINOR_VERSION in the next byte
// i.e. MAJOR 2, MINOR 0x34, BUILD 0x278 would be "ver 2.52
	IMPORT_C static TUint32 GetVersion(void);

	IMPORT_C static CFtpProtocol *NewL(MFtpProtocolNotifier*);
	virtual ~CFtpProtocol();
	};
#endif //__FTPPROT_H__
