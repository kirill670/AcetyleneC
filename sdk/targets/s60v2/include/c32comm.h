// C32COMM.H
//
// Copyright (c) Symbian Software Ltd. 1997-2004.  All rights reserved.
//
#if !defined(C32COMM_H__)
#define C32COMM_H__

/** @file

C32 header file to be included by the clients.
Defines the main interface to C32, RCommServ and RComm
*/

#include <e32base.h>
#include <d32comm.h>

/**
@publishedAll
@released	
*/
IMPORT_C TInt StartC32();
IMPORT_C TInt StartC32WithCMISuppressions(const TDesC& aCMISuppressionList);

/**
C32 major version number.
@internalAll
*/
const TUint KEC32MajorVersionNumber = 1;  
/**
C32 minor version number.
@internalAll
*/
const TUint KEC32MinorVersionNumber = 0;  
/**
C32 build version number.
@internalAll
*/
const TUint KEC32BuildVersionNumber = 605;

/**
@internalComponent
*/
const TDesC& KCommServerName(void);

/** Specifies the mode in which a port is opened.

We specify the mode when it is opened, and the mode cannot thereafter be
changed. If we open the port in Shared mode, other clients of the comms
server can use the same port while we have it open. If we open the port
in Exclusive mode, then it is locked for our own use and any attempt to
access it from another process will fail. Furthermore, our own attempt
to open a port in exclusive mode will fail if another process has already
opened the port in shared mode.
 
Infra-red ports using IRCOMM.CSY can be opened in either shared or exclusive 
mode. However they SHOULD only be opened in Exclusive mode, since opening 
them any other way warm-boots the computer.
 
@publishedAll
@released	
*/
enum TCommAccess
    {
	/** Once open, the port cannot be used by any other RComm clients. An attempt to 
	open a port in exclusive mode will fail if another process has already opened 
	the port in shared mode. */
	ECommExclusive,  
	/** The port can be shared by other RComm clients who open in the same mode. */
	ECommShared,    
	/** Allows another client to pre-empt the session with an open request in one of 
	the other two modes. The port will be lost if other clients are trying to open it.*/
	ECommPreemptable 
    };
/**
Use full buffering. Used by RComm::SetMode().

@publishedAll	
@released
*/
const TUint KCommBufferFull    = 0x0000; 
/**
Use partial buffering. Used by RComm::SetMode().

@publishedAll	
@released
*/
const TUint KCommBufferPartial = 0x0001;  


/**
trace flags for debugging purposes
@internalComponent
*/
enum TC32Trace 
	{
	ETraceC32Startup = 0x00000001,
	ETraceC32Panic   = 0x00000002,
	ETraceC32Request = 0x00000004,
	ETraceC32IPC     = 0x00000008,
	ETraceC32All     = 0xFFFFFFFF,
	};

/**
Used by the package TCommServerConfig to configure the comm port.

Holds the buffer configuration settings for the comms server. 

The comms server copies data between the descriptors provided by the client 
and the buffers used by the serial port drivers, for each read and write request. 
There are two methods by which this can be accomplished. Full buffering means 
that the comms server will always attempt to allocate enough memory to satisfy 
any reads or writes in a single copy, while partial buffering means that the 
comms server will allocate a static buffer and use partial copies to transfer 
data to the serial driver. When a port is opened, the default is full buffering. 

@publishedAll
@released
*/
struct TCommServerConfigV01
	{
	/** Buffering option: either KCommBufferFull or KCommBufferPartial */
	TUint iBufFlags; ///< contains buffer flags e.g for partial read/write
	/** Size of server buffer if partial buffering is being used */
	TUint iBufSize;  ///< size of the Tx/Rx buffer
	};

/** Package buffer for a server configuration object. TCommServerConfig is used 
as an argument to RComm::Mode() and RComm::SetMode(). 

@publishedAll	
@released
*/
typedef TPckgBuf<TCommServerConfigV01> TCommServerConfig; 

/** Maximum length of port full name, TPortDescription (48 characters).

@publishedAll	
@released
 */
const TInt KMaxPortDescription = 0x30; 
/** Maximum length of port short name, TPortName (16 characters). 

@publishedAll	
@released
*/
const TInt KMaxPortName = 0x10;        

/** Reset the receive buffer 

@publishedAll	
@released
*/
const TUint KCommResetRx = 0x00000001;  ///< to by used as flag by RComm::ResetBuffers
/** Reset the transmit buffer 

@publishedAll	
@released
*/
const TUint KCommResetTx = 0x00000002;  ///< to by used as flag by RComm::ResetBuffers
/** Port name. Used by TSerialInfo::iName. 

@publishedAll	
@released
*/
typedef TBuf<KMaxPortName> TPortName;            
/** Full port name/description. Used by TSerialInfo::iDescription. 

@publishedAll	
@released
*/
typedef TBuf<KMaxPortDescription> TPortDescription; 


class TSerialInfo
/** Describes a serial protocol's general capabilities.

Used by RCommServ::GetPortInfo to retrieve information
about the comm ports and the CSY.

Notes:

The lowest port need not necessarily be numbered zero.

At least one port is always guaranteed. 

The full name of the serial port (used when opening it) consists of the name 
returned by TSerialInfo, followed by a double colon separator, followed by 
the unit number as an ASCII number (for instance COMM::0). 

@publishedAll	
@released
*/
	{
public:
	/** The full name of the port. This is used only for user interaction (see note 4) */
	TPortDescription iDescription; ///< description of the port (CSY)
	/** The short name of the port. This is used in calls to RComm::Open() (see note 5) */
	TPortName iName;               ///< name of the port
	/** The lowest unit number supported by the serial module */
	TUint iLowUnit;                ///< the lowest number of the port available
	/** The highest unit number supported by the serial module */
	TUint iHighUnit;               ///< the highest number of the port available
	};

/**
Specifies the DTE/DCE role in which a port is opened.

@see RComm::Open() 
@publishedAll	
@released
*/
enum TCommRole
	{
	/** Port takes on role of DTE. (DTE=computer).
	This is the default.
	*/
		ECommRoleDTE, 
	/** Port takes on role of DCE. (DCE=modem).
	*/
		ECommRoleDCE  
	};

class RComm;


class RCommServ : public RSessionBase
/** Represents a session with the comms server. Functions are provided for connection 
to the server and for loading and unloading different comms modules, and services 
for finding out the name and numbers of the available ports.

This class is not intended for user derivation.

@publishedAll	
@released */
	{
public:
	IMPORT_C RCommServ();
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;

	IMPORT_C TInt LoadCommModule(const TDesC& aFileName);
	IMPORT_C TInt UnloadCommModule(const TDesC& aName);
	IMPORT_C TInt NumPorts(TInt& aNum);
	IMPORT_C TInt GetPortInfo(const TDesC& aName, TSerialInfo& aInfo);
	IMPORT_C TInt GetPortInfo(TInt aIndex, TDes& aModuleName, TSerialInfo& aInfo);

	IMPORT_C TInt __DbgMarkHeap();
	IMPORT_C TInt __DbgCheckHeap(TInt aCount);
	IMPORT_C TInt __DbgMarkEnd(TInt aCount);
	IMPORT_C TInt __DbgFailNext(TInt aCount);
	IMPORT_C TInt __DbgSetTraceMask(TC32Trace aMask);

	IMPORT_C static TInt CreateThreadInCommProc(const TDesC& aLibraryName, const TDesC& aThreadName, TThreadFunction aFunction, TInt aStackSize, TInt aHeapMinSize, TInt aHeapMaxSize);
private:
	static TBool IsServerThreadL();
	};
//

struct TCommDebugInfo; // defined in d32comm.h


class RComm : public RSubSessionBase
/** A sub-session serial port.

All the necessary functions are provided by this class for communicating via 
a port, including functions for opening, closing, reading, writing, together 
with port configuration and capability checking.

@publishedAll	
@released
*/
		{
public:
	IMPORT_C RComm();
	IMPORT_C TInt Open(RCommServ& aServer, const TDesC& aName, TCommAccess aMode);
	IMPORT_C TInt Open(RCommServ& aServer, const TDesC& aName, TCommAccess aMode, TCommRole aRole);
	IMPORT_C void OpenWhenAvailable(TRequestStatus& aStatus, RCommServ& aServer, const TDesC& aName);
	IMPORT_C void OpenWhenAvailable(TRequestStatus& aStatus, RCommServ& aServer, const TDesC& aName, TCommRole aRole);
	IMPORT_C void OpenWhenAvailableCancel();
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes, TInt aLength);
	IMPORT_C void Read(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, TDes8& aDes, TInt aLength);
	IMPORT_C void ReadOneOrMore(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C TInt ReadCancel();
	IMPORT_C TInt QueryReceiveBuffer() const;
	IMPORT_C TInt ResetBuffers(TUint aFlags=(KCommResetRx|KCommResetTx));
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes, TInt aLength);
	IMPORT_C void Write(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, const TDesC8& aDes, TInt aLength);
	IMPORT_C TInt WriteCancel();
	IMPORT_C void Break(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTime);
	IMPORT_C TInt BreakCancel();
	IMPORT_C TInt Cancel();
	IMPORT_C TInt Config(TDes8& aConfig) const;
	IMPORT_C TInt SetConfig(const TDesC8& aConfig);
	IMPORT_C TInt Caps(TDes8& aCaps) const;
	IMPORT_C TInt SetMode(const TCommServerConfig& aConfig);
	IMPORT_C TInt Mode(TCommServerConfig& aConfig) const;
	IMPORT_C TUint Signals(TUint aSignalMask = 0x3F) const;
	IMPORT_C TInt SetSignalsToMark(TUint aSignalMask);
	IMPORT_C TInt SetSignalsToSpace(TUint aSignalMask);
	IMPORT_C TInt ReceiveBufferLength() const;
	IMPORT_C TInt SetReceiveBufferLength(TInt aLength);
	IMPORT_C void Close();
	inline void SetSignals(TUint aSetMask, TUint aClearMask);
	IMPORT_C void NotifySignalChange(TRequestStatus& aStatus, TUint& aSignals, TUint aSignalMask=0x3F);
	IMPORT_C TInt NotifySignalChangeCancel() const;
	IMPORT_C void NotifyConfigChange(TRequestStatus& aStatus, TDes8& aNewConfig) const;
	IMPORT_C TInt NotifyConfigChangeCancel() const;
	IMPORT_C void NotifyFlowControlChange(TRequestStatus& aStatus, TFlowControl& aFlowControl);
	IMPORT_C TInt NotifyFlowControlChangeCancel() const;	  
	IMPORT_C void NotifyBreak(TRequestStatus& aStatus) const;
	IMPORT_C TInt NotifyBreakCancel() const;
	IMPORT_C void NotifyDataAvailable(TRequestStatus& aStatus) const;
	IMPORT_C TInt NotifyDataAvailableCancel() const;
	IMPORT_C void NotifyOutputEmpty(TRequestStatus& aStatus) const;
	IMPORT_C TInt NotifyOutputEmptyCancel() const;
	IMPORT_C TInt GetFlowControlStatus(TFlowControl& aFlowControl) const;
	IMPORT_C TInt GetRole(TCommRole& aRole) const;

	IMPORT_C TInt SetAccessMode(TCommAccess aNewMode);
	IMPORT_C TInt DebugState(TCommDebugInfo&);

#ifdef _DEBUG_DEVCOMM
	IMPORT_C TInt RComm::DebugInfo(TDes8& aDes);
#endif
private:
	TPtr8 iSignalsNotification; ///< pointer to the signals to be changed during notification
	TPtr8 iFlowNotification;    ///< pointer to the flow control to be changed during notification
	};

#include <C32COMM.INL>

#endif // C32COMM_H__
