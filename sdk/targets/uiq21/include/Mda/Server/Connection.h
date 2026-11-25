// Mda\Server\Connection.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_SERVER_CONNECTION_H__
#define __MDA_SERVER_CONNECTION_H__

#ifndef __MDA_SERVER_ENVIRONMENT_H__
#include <Mda\Server\Environment.h>
#endif

#include <Mda\Server\Io.h>
#include <Mda\Server\Machine.h>
#include <Mda\Server\Dispatcher.h>
#include <Mda\Server\Controller.h>

class CMdaController; // Forward reference

// Constants
const TInt16 KMdaConnectionTransfer = 0x1000;

// Panics
enum TMdaConnectionPanic
	{
	ESrcIONull=0,
	EDstIONull=1,
	ESrcReadyTwice=2,
	EDstReadyTwice=3,
	ESrcCancelWhenNotReady=4,
	EDstCancelWhenNotReady=5
	};

// CMdaConnection
class CMdaConnection : public CMdaObject, public MMdaMessage
	{
public:
	IMPORT_C static CMdaConnection* NewLC(CMdaController& aController, 
								CMdaIO* aSrc, CMdaIO* aDst);
	IMPORT_C void Close();
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	// From MMdaMessage
	IMPORT_C void MessageDoComplete(TInt aVal);

	// ------------------------------------------
	// Functions for IO objects
	// Asynchronous buffer exchange
	IMPORT_C void SrcReadyToSupply();
	IMPORT_C void CancelSrcReadyToSupply();
	IMPORT_C void DstReadyToAccept();
	IMPORT_C void CancelDstReadyToAccept();
	IMPORT_C void SrcReadyToAccept();
	IMPORT_C void CancelSrcReadyToAccept();
	IMPORT_C void DstReadyToSupply();
	IMPORT_C void CancelDstReadyToSupply();
	// State change
	IMPORT_C void SrcFinished(TBool aFinished);	
	IMPORT_C void DstFinished(TBool aFinished);	
	IMPORT_C void SrcError(TInt aErr);	
	IMPORT_C void DstError(TInt aErr);	
	// ------------------------------------------
	// Utility functions
	inline CMdaController& Controller() const;
	inline CMdaIO* Dst() const;
	inline CMdaIO* Src() const;
	inline TBool IsSrcReadyToSupply();
	inline TBool IsDstReadyToAccept();
	inline TBool IsSrcReadyToAccept();
	inline TBool IsDstReadyToSupply();

	inline TBool IsSrcFinished();
	inline TBool IsDstFinished();
	inline TBool IsFinished();
	inline TBool IsSrcError();
	inline TBool IsDstError();
	inline TInt GetSrcError();
	inline TInt GetDstError();
private:
	CMdaConnection(CMdaController& aController);
	virtual ~CMdaConnection();
	void ConstructL(CMdaIO* aSrc, CMdaIO* aDst);	
	void QueueTransfer();
	void DoTransferL(CMdaMessage* aMessage);
	void MakeTransferMessage();
public:
    TSglQueLink iControllerLink;
private:
	enum TConnState
		{
		EIdle =				0x00000000,
		// Buffer exchange states
		EDstReadyToSupply =	0x00000001,
		ESrcReadyToAccept = 0x00000002,
		EDstToSrcReady =	EDstReadyToSupply|ESrcReadyToAccept,
		EDstReadyToAccept =	0x00000004,
		ESrcReadyToSupply =	0x00000008,
		ESrcToDstReady =	EDstReadyToAccept|ESrcReadyToSupply,
		// Terminate states
		ESrcFinished =		0x00000010,
		EDstFinished =		0x00000020,
		EDstSrcFinished =	ESrcFinished|EDstFinished,
		ESrcError =			0x00000040,
		EDstError =			0x00000080
		};
private:
	TBool iRunQueued;
	TInt iState;
	TInt iSrcError;
	TInt iDstError;
	CMdaController& iController;
	CMdaIO* iDst;
	CMdaIO* iSrc;
	CMdaIOFactory* iSrcIOFactory;
	CMdaIOFactory* iDstIOFactory;
	CMdaDispatchMessage* iMessage;
	friend class TMdaConnecter;
	};

// Inlines

inline CMdaController& CMdaConnection::Controller() const
	{ return iController; }
inline CMdaIO* CMdaConnection::Dst() const
	{ return iDst; }
inline CMdaIO* CMdaConnection::Src() const
	{ return iSrc; }

inline TBool CMdaConnection::IsSrcReadyToSupply()
	{ return iState&ESrcReadyToSupply; }
inline TBool CMdaConnection::IsDstReadyToAccept()
	{ return iState&EDstReadyToAccept; }
inline TBool CMdaConnection::IsSrcReadyToAccept()
	{ return iState&ESrcReadyToAccept; }
inline TBool CMdaConnection::IsDstReadyToSupply()
	{ return iState&EDstReadyToSupply; }

inline TBool CMdaConnection::IsSrcFinished()
	{ return iState&ESrcFinished; }
inline TBool CMdaConnection::IsDstFinished()
	{ return iState&EDstFinished; }
inline TBool CMdaConnection::IsFinished()
	{ return iState&EDstSrcFinished; }
inline TBool CMdaConnection::IsSrcError()
	{ return iState&ESrcError; }
inline TBool CMdaConnection::IsDstError()
	{ return iState&EDstError; }
inline TInt CMdaConnection::GetSrcError()
	{ return iSrcError; }
inline TInt CMdaConnection::GetDstError()
	{ return iDstError; }

#endif
