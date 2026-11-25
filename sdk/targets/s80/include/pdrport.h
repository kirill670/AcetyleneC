// PDRPORT.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef PDRPORT_H
#define PDRPORT_H

// Begin 31.3.04 MR: Added for Erin printing functionality
#define CBTPRINTERPORT_DEFINED
// End

#include <e32std.h>
#include <c32comm.h>
#include <gdi.h>
#include <s32file.h>
#include <bttypes.h>
#include <es_sock.h>
#include <bt_sock.h>
#include <in_sock.h>

/**
 * @internal
 * Internal to Symbian
 */
class CFilePrinterPort : public CPrinterPort
	{
public:
	IMPORT_C static CFilePrinterPort* NewL(const TDesC& aFileName);
	IMPORT_C ~CFilePrinterPort();
	void WriteRequest(const TDesC8& aBuf,TRequestStatus& aRequestStatus);
	void Cancel();
	inline const TDesC& FileName() { return iFileName; }
private:
	void ConstructL();
	CFilePrinterPort(const TDesC& aFileName);
private:
	RFs iFs;
	TFileName iFileName;
	RFile iFile;
	TBool iCancelled;
	};

/**
 * @internal
 * Internal to Symbian
 */
class TOutputHandshake
	{
public:
	IMPORT_C TOutputHandshake();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TBool iXonXoff;
	TBool iCts;
	TBool iDsr;
	TBool iDcd;
	};

/**
 * @internal
 * Internal to Symbian
 */
class TSerialPrinterPortConfig
	{
public:
	IMPORT_C TSerialPrinterPortConfig();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TBps iRate;
	TDataBits iDataBits;
	TStopBits iStopBits;
	TParity iParity;
	TBool iIgnoreParity;
	TOutputHandshake iHandshake;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CCommPrinterPort : public CPrinterPort
	{
public:
	IMPORT_C static CCommPrinterPort* NewL(const TDesC& aCsyName, const TDesC& aPortName, const TSerialPrinterPortConfig& aConfig, const TFifo aFifo = EFifoEnable);
	IMPORT_C ~CCommPrinterPort();
	IMPORT_C void WriteRequest(const TDesC8& aBuf, TRequestStatus& aRequestStatus);
	IMPORT_C void Cancel();
protected:
	IMPORT_C void ConstructL(const TDesC& aCsyName, const TDesC& aPortName, const TSerialPrinterPortConfig& aConfig, const TFifo aFifo = EFifoEnable);
	IMPORT_C CCommPrinterPort();
protected:
	RCommServ iCommServ;
	RComm iComm;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CSerialPrinterPort : public CCommPrinterPort
	{
public:
	IMPORT_C static CSerialPrinterPort* NewL(const TDesC& aPortName, const TSerialPrinterPortConfig& aConfig);
	IMPORT_C ~CSerialPrinterPort();
	IMPORT_C TSerialPrinterPortConfig Config();  // returns the current port config
private:
	void ConstructL(const TDesC& aPortName);
	CSerialPrinterPort(const TSerialPrinterPortConfig& aConfig);
private:
	TSerialPrinterPortConfig iConfig;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CParallelPrinterPort : public CCommPrinterPort
	{
public:
	IMPORT_C static CParallelPrinterPort* NewL(const TDesC& aPortName);
	IMPORT_C ~CParallelPrinterPort();
private:
	void ConstructL(const TDesC& aPortName);
	CParallelPrinterPort();
	};

/**
 * @internal
 * Internal to Symbian
 */
class CIrdaPrinterPort : public CCommPrinterPort
	{
public:
	IMPORT_C static CIrdaPrinterPort* NewL();
	IMPORT_C ~CIrdaPrinterPort();
private:
	void ConstructL();
	CIrdaPrinterPort();
	};

/**
 * @internal
 * Internal to Symbian
 */
class CEpocConnectPort : public CCommPrinterPort
	{
public:
	IMPORT_C static CEpocConnectPort* NewL();
	IMPORT_C ~CEpocConnectPort();
private:
	void ConstructL();
	CEpocConnectPort();
	};

/**
 * @internal
 * Internal to Nokia
 */
class CBTPrinterPort : public CPrinterPort
	{
public:
	IMPORT_C static CBTPrinterPort* NewL(TSockAddr& aAddr);
	IMPORT_C ~CBTPrinterPort();
	IMPORT_C void WriteRequest(const TDesC8& aBuf, TRequestStatus& aRequestStatus);
	IMPORT_C void Cancel();
private:
	void ConstructL(TSockAddr& aAddr);
	CBTPrinterPort();

	RSocketServ	iSession;
	RSocket		iSocket;
	};

const TUint KNoPortSpecified	= 0;	// No source port range used

/**
 * @internal
 * Internal to Nokia
 */
class CSocketPrinterPort : public CPrinterPort
	{
public:
	IMPORT_C static CSocketPrinterPort* NewL(const TInetAddr& aAddr);
	IMPORT_C static CSocketPrinterPort* NewL(const THostName& aHostName, const TUint aPort);
	IMPORT_C ~CSocketPrinterPort();
	IMPORT_C void WriteRequest(const TDesC8& aBuf, TRequestStatus& aRequestStatus);
	IMPORT_C void Cancel();
	inline TUint LocalPort() const { return iLocalPort; }
protected:
	virtual void BaseConstructL();
	void ConstructL(const TInetAddr& aAddr, const TUint aLocalPortLow = KNoPortSpecified, const TUint aLocalPortHigh = KNoPortSpecified);
	void ConstructL(const THostName& aHostname, const TUint aPort, const TUint aLocalPortLow = KNoPortSpecified, const TUint aLocalPortHigh = KNoPortSpecified);
	CSocketPrinterPort();

	void InitL(const THostName& aHostName, const TUint aPort, const TUint aLocalPort = KNoPortSpecified, const TUint aLocalPortHigh = KNoPortSpecified);
	void InitL(const TInetAddr& aAddr, const TUint aLocalPortLow = KNoPortSpecified, const TUint aLocalPortHigh = KNoPortSpecified);
	void ResolveHostNameL(const THostName& aHostName, TInetAddr& aInetAddr);

	RSocketServ		iSession;
	RHostResolver	iResolver;
	RSocket			iSocket;

private:
	TUint			iLocalPort;
	};

const TInt KLprMaxHostnameLen = 32;
const TUint KLprMaxUserNameLen = 32;
const TUint KLprMaxQueueLen = 256;

typedef TBuf<KLprMaxUserNameLen> TLprUserName;	/** Defines a descriptor to hold the LPR username. */
typedef TBuf<KLprMaxQueueLen> TLprQueueName;	/** Defines a descriptor to hold the LPR queue name. */

/**
 * @internal
 * Internal to Nokia
 */
class CLprPrinterPort : public CSocketPrinterPort
	{
public:
	IMPORT_C static CLprPrinterPort* NewL(const TInetAddr& aAddr, const TLprQueueName& aQueueName, const TLprUserName& aUsername);
	IMPORT_C static CLprPrinterPort* NewL(const THostName& aHostName, const TLprQueueName& aQueueName, const TLprUserName& aUsername);
	IMPORT_C ~CLprPrinterPort();
	IMPORT_C void WriteRequest(const TDesC8& aBuf, TRequestStatus& aRequestStatus);
	IMPORT_C void Cancel();
private:
	void BaseConstructL();
	void ConstructL(const TInetAddr& aAddr);
	void ConstructL(const THostName& aHostName);
	CLprPrinterPort(const TLprQueueName& aQueueName, const TLprUserName& aUsername);

	void SendBufferL(const TDesC8& aBuffer, const TBool aWait = ETrue);
	void PrepareL();
	void PrepareLprControlAndDataFilesL();
	void SendLprReceiveJobL();
	void SendLprDataL();

	TInt						iStatus;
	TUint						iJobNumber;
	TBuf8<KLprMaxQueueLen>		iQueueName;
	TBuf8<KLprMaxUserNameLen>	iUsername;
	TBuf8<KLprMaxHostnameLen>	iHostname;
	HBufC8*						iBuffer;
	HBufC8*						iCtrlFile;
	HBufC8*						iDataFile;
	TPtrC8						iCtrlFilePtr;
	TInt						iCtrlFilePos;
	TBool						iCtrlFileSent;
	TInt						iTicksToWait;
	TInt						iTickCount;
	};

#endif
