// Copyright (c) 1999-2002 Symbian Software Ltd.  All rights reserved.

#ifndef BTMANCLIENT_H
#define BTMANCLIENT_H

#include <e32std.h>
#include <e32base.h>
#include <btdevice.h>

static const TInt KErrBluetoothRegistryCorrupt = -6501;

/** The type of device class search to perform.

The enumeration is of masks. Valid combinations are:

	EMajorDevice only
	EMajorDevice & EMinorDevice

Note: EMinorDevice may not be used on its own.
@publishedAll
@released
*/
enum TBTDeviceClassSearch
	{
	EMajorDevice = 0x01,/*!< Indicates the major device class search criteria. */
	EMinorDevice = 0x02,/*!< Indicates the minor device class search criteria. */
	};


class TBTRegistrySearch
	/** Set search criteria on the Bluetooth Registry.

	The search logic is "AND", so if device bonded is set, and code set to
	headsets the search results contain all the bonded headsets in the registry.

	Other things can be added to the search criteria e.g. recently used headsets
	can easil be found by adding in the LastUsed criterion.
	@publishedAll
	@released
	*/
	{
	friend class RBTDbQuery;
public:
	IMPORT_C TBTRegistrySearch();
	IMPORT_C TBTRegistrySearch(const TBTRegistrySearch& aSearch);
	IMPORT_C void Reset();
	IMPORT_C void FindAll();
	IMPORT_C void FindAddress(const TBTDevAddr& aAddress);
	IMPORT_C void FindBonded();
	IMPORT_C void FindTrusted();
	IMPORT_C void FindCoD(const TBTDeviceClass& aClass);
	IMPORT_C void FindCoD(const TBTDeviceClass& aClass, TBTDeviceClassSearch aPref);
	IMPORT_C void FindSinceSeen(const TTime& aLastSeen);
	IMPORT_C void FindSinceUsed(const TTime& aLastUsed);
	IMPORT_C void FindBluetoothName(const TDesC8& aName);
	IMPORT_C void FindFriendlyName(const TDesC& aName);
	IMPORT_C void FindCurrentProcessOwned();
	IMPORT_C TBTRegistrySearch& TBTRegistrySearch::operator=(const TBTRegistrySearch& aSearch);
private:
	enum TSearchMask
		{
		EAddress	  = 0x0001,
		EBonded		  = 0x0002,
		ETrusted	  = 0x0004,
		ECoD		  = 0x0008,
		ECoDMajorDev  = 0x0010,
		ECoDMinorDev  = 0x0020,
		ECoDService   = 0x0040, // not used at present
		ELastSeen	  = 0x0080,
		ELastUsed	  = 0x0100,
		EBTName		  = 0x0200,
		EFriendlyName = 0x0400,
		EProcess	  = 0x4000,
		EAll		  = 0x8000,
		};
private:
	TUint			iSearchMask;	// what we actually have set to search on
	TBTDevAddr		iDeviceAddress;
	TBTDeviceClass	iDeviceClass;
	TTime			iLastSeen;
	TTime			iLastUsed;
	TPtrC8			iBluetoothName;	
	TPtrC			iFriendlyName;	
	TUid			iCurrentProcessSID;
	};

class RBTMan : public RSessionBase
    /** Creates a sessions over which the Bluetooth security manager is accessible.

    A session must be used in order to access a subsession, RBTManSubSession,
	that allows access to the Security Manager. The following example creates and
	connects to the security manager session.

    @code
	RBTMan secMan;
	User::LeaveIfError(secMan.Connect());
	@endcode
	 
	Sessions available thus far are Registry-like
	@publishedAll
	@released
	*/
	{
public:
	IMPORT_C RBTMan();
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	};

struct TBTManClientServerMessage
/**
@internalComponent
*/
	{
public:
	TRequestStatus* iClientStatusToCancel;
	TBool			iClientBusy;
	};

class RBTManSubSession : public RSubSessionBase
    /** A subsession for the RBTMan session.

    RBTManSubSession provides the actual access to the security manager.

    Contains basic subssession functionality.
	@publishedAll
	@released
	*/
	{
public:
	/** Used to close the subsession. */
	virtual void Close() = 0; // All subsessions must provide Close overrides
	IMPORT_C void CancelRequest(TRequestStatus& aStatus);
	void LocalComplete(TRequestStatus& aStatus, TInt aErr);
protected:
	TPckgBuf<TBTManClientServerMessage>	iClientServerMsg;
protected:
	IMPORT_C RBTManSubSession();
	TBool IsBusy() const;
	void SetBusy(TRequestStatus& aStatus);
	};

class RBTRegServ : protected RBTMan
    /** Registry access session.

    It has a RBTMan session as implementation.
	@released
	@publishedAll
	*/
	{
public:
	IMPORT_C RBTRegServ();
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C RBTMan& Session();
	IMPORT_C TInt SetHeapFailure(TInt aType,TInt aRate);
	IMPORT_C TInt ResourceCount();
	};

// other functional sessions can derive from RBTMan

typedef RPointerArray<CBTDevice> RBTDeviceArray; /*!<RPointerArray of CBTDevices*/
typedef TPckgBuf<TBTNamelessDevice> TBTNamelessDevicePckgBuf; /*!<packagebuf of TBTNamelessDevice*/
typedef TPckgC<TBTDevAddr> TBTDevAddrPckg;	/*!<const package (not buf) of TBTDevAddr*/
typedef TPckgBuf<TBTDevAddr> TBTDevAddrPckgBuf; /*!<packagebuf of TBTDevAddr*/
typedef TPckgBuf<TBTRegistrySearch> TBTRegistrySearchPckgBuf; /*!<packagebuf of TBTRegistrySearch*/

class RBTRegistry;


class CBTRegistryResponse : public CActive
    /** Retrieves a set of results from the Registry.
	 
	This is a helper class that retrieves a set of results as a view from the registry.
	@publishedAll
	@released
	*/
	{
public:
	IMPORT_C static CBTRegistryResponse* NewL(RBTRegistry& aView);
	IMPORT_C void Start(TRequestStatus& aClientStatus);
	IMPORT_C RBTDeviceArray& Results();
	IMPORT_C ~CBTRegistryResponse();
private:
	CBTRegistryResponse(RBTRegistry& aView);
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();
	void DoGet();
	void ConstructL();
	enum TState {EGettingSize, EGettingResults};
private:
	RBTRegistry&		iView;
	RBTDeviceArray		iArray;
	HBufC8*				iResponseBuf;
	TPtr8				iResponsePtr;
	TState				iState;
	TRequestStatus*		iClientStatus;
	};

class RBTRegistry : public RBTManSubSession
    /** Creates and opens a subsession on the BT Registry Server for remote devices.
	
	This subsession allows details of remote devices to be updated, modified, examined etc.
	@publishedAll
	@released
	*/
	{
public:
	IMPORT_C RBTRegistry();
	IMPORT_C TInt Open(RBTRegServ& aSession);
	IMPORT_C void AddDeviceL(const CBTDevice& aDeviceDetails, TRequestStatus& aStatus);
	IMPORT_C void GetDevice(TBTNamelessDevice& aDevice, TRequestStatus& aStatus); // nameless device
	IMPORT_C void ModifyDevice(const TBTNamelessDevice& aDevice, TRequestStatus& aStatus); //namesless device
	IMPORT_C void UnpairDevice(const TBTDevAddr& aAddress, TRequestStatus& aStatus);
	IMPORT_C void ModifyFriendlyDeviceNameL(const TBTDevAddr& aAddress, const TDesC& aNewName, TRequestStatus& aStatus);
	IMPORT_C void ModifyBluetoothDeviceNameL(const TBTDevAddr& aAddress, const TDesC8& aNewName, TRequestStatus& aStatus);
	IMPORT_C void CreateView(const TBTRegistrySearch& aSearch, TRequestStatus& aStatus);
	IMPORT_C void UnpairAllInView(TRequestStatus& aStatus);
	IMPORT_C void DeleteAllInView(TRequestStatus& aStatus);	// depends on client process capabilities
	IMPORT_C void Close();
	IMPORT_C TInt CloseView();
	

	void PreLoad(TRequestStatus& aStatus);
	void GetResults(TPtr8& aResultBuf, TRequestStatus& aStatus);
private:
	CBufFlat*	iSendBuffer;	// lazily constructed
	TPtrC8		iSendBufferPtr;
	TBTRegistrySearchPckgBuf	iSearchPckg;
	TPckg<TBTNamelessDevice>	iDevicePckg;
	TPckgBuf<TBTDevAddr>		iAddrBuf;
	};

class RBTLocalDevice : public RBTManSubSession
    /** Creates and opens a subsession on BT Registry Server for local devices.

    This subsession allows the local device to be updated, modified, examined etc.
	@publishedAll
    @released
    */
	{
public:
	IMPORT_C RBTLocalDevice();
	IMPORT_C TInt Open(RBTRegServ& aSession);
	IMPORT_C TInt Get(TBTLocalDevice& aLocalDevice);
	IMPORT_C TInt Modify(const TBTLocalDevice& aLocalDevice);
	IMPORT_C void Modify(const TBTLocalDevice& aLocalDevice, TRequestStatus& aStatus);
	IMPORT_C void Close();
private:
	TPckg<TBTLocalDevice> iLocalDevicePckg;
	};


/**
UID of the PIN entry RNotifier plugin
@publishedPartner
@released
*/
const TUid KBTManPinNotifierUid={0x100069c9};

/**
UID of the authorisation RNotifier plugin
@publishedPartner
@released
*/
const TUid KBTManAuthNotifierUid={0x100069cf};



class TBTAuthorisationParams
    /** Bluetooth authorisation parameters.
	 
	Struct to allow us to send params from the security manager to the Authorisation RNotifier plugin.
	@publishedPartner
	@released
	*/
	{
public:
    /** Device address of remote device requiring authorisation. */
	TBTDevAddr iBDAddr;
    /** UID of the service requesting authorisation. */
	TUid iUid;
	};



class TBTNotifierUpdateParams
	/** Sends parameter updates to the notifier.
	
	Struct to allow us to send a device name to the Passkey Entry and Authorisation RNotifier plugins.
	@publishedPartner
	@released
	*/
	{
public:
	/** The device name that has been retrieved since security procedures started. */
	TBTDeviceName iName;
	/** The result. */
	TInt iResult;
	};

class TBTNotifierParams : public TBTAuthorisationParams
	/** The device name parameter for the security notifier.
	
	@publishedPartner
	@released
	*/
	{
public:
	/** The device name that has been retrieved since security procedures started. */
	TBTDeviceName iName;
	};


typedef TPckgBuf<TBTAuthorisationParams> TBTAuthorisationParamsPckg; /*!< packagebuf of TBTAuthorisationParams*/
typedef TPckgBuf<TBTNotifierUpdateParams> TBTNotifierUpdateParamsPckg; /*!< packagebuf of TBTNotifierUpdateParams*/
typedef TPckgBuf<TBTNotifierParams> TBTNotifierParamsPckg; /*!< packagebuf of TBTNotifierParams*/

#ifdef __BC70s__

class TBTAccessRequirementsB
	/** The access requirements set up by a bluetooth service.

	Note: This class is provided ONLY for BC with versions prior to v8.0
	@removed
	@internalTechnology
	*/
	{
public:
	IMPORT_C TBTAccessRequirementsB();
	IMPORT_C void SetAuthentication(TBool aPreference);
	IMPORT_C void SetAuthorisation(TBool aPreference);
	IMPORT_C void SetEncryption(TBool aPreference);
	IMPORT_C void SetDenied(TBool aPreference);
	IMPORT_C TBool AuthenticationRequired() const;
	IMPORT_C TBool AuthorisationRequired() const;
	IMPORT_C TBool EncryptionRequired() const;
	IMPORT_C TBool Denied() const;
	IMPORT_C TBool operator==(const TBTAccessRequirementsB& aRequirements) const;
private:
	TInt iRequirements;
private:
	enum TBTServiceSecuritySettings
		{
		EAuthenticate = 0x01,
		EAuthorise = 0x02,
		EEncrypt = 0x04,
		EDenied = 0x08
		};
	};

class TBTServiceSecurityB
	/** The security settings of a bluetooth service.

	Note: This class is provided ONLY for BC with versions prior to v8.0.
	@removed
	@internalTechnology
	*/
	{
public:
	IMPORT_C TBTServiceSecurityB(TUid aUid, TInt aProtocolID, TInt aChannelID);
	IMPORT_C TBTServiceSecurityB(const TBTServiceSecurityB& aService);
	IMPORT_C TBTServiceSecurityB();
	IMPORT_C void SetUid(TUid aUid);
	IMPORT_C void SetProtocolID(TInt aProtocolID);
	IMPORT_C void SetChannelID(TInt aChannelID);
	IMPORT_C void SetAuthentication(TBool aPreference);
	IMPORT_C void SetAuthorisation(TBool aPreference);
	IMPORT_C void SetEncryption(TBool aPreference);
	IMPORT_C void SetDenied(TBool aPreference);
	IMPORT_C TBool AuthorisationRequired() const;
	IMPORT_C TBool EncryptionRequired() const;
	IMPORT_C TBool AuthenticationRequired() const;
	IMPORT_C TBool Denied() const;
	IMPORT_C TUid Uid() const;
	IMPORT_C TInt ProtocolID() const;
	IMPORT_C TInt ChannelID() const;
private:
	TUid iUid;	///<The UID of the service.  Will be used by the UI to work out the name of the service when prompting the user.
	TInt iProtocolID;	///<The protocol layer below this service.
	TInt iChannelID;	///<The port number on which the service is sitting
	TBTAccessRequirementsB iSecurityRequirements;	///<Whether the service requires authentication, authorisation, or encryption.
	};

typedef TPckgBuf<TBTServiceSecurityB> TBTServiceSecurityPckgBufB; /*! removed*/


class RBTManSubSessionB : public RSubSessionBase
	/** Subsession base class.
	
	Note: This class is provided ONLY for BC with versions prior to v8.0
	@removed
	@internalTechnology
	*/
	{
public:
	virtual TInt Open(RBTMan& aSession) = 0;
	virtual void Close() = 0;
	IMPORT_C void CancelRequest(TRequestStatus& aStatus);	//THIS IS NOT ASYNCHRONOUS!!!!
	void LocalComplete(TRequestStatus& aStatus, TInt aErr);
	};

class RBTSecuritySettingsB : public RBTManSubSessionB
	/** Security Settings Subsession.

	Note: This class is provided ONLY for BC with versions prior to v8.0
	@removed
	@internalTechnology
	*/
	{
public:
	IMPORT_C TInt Open(RBTMan& aSession);
	IMPORT_C void Close();
	IMPORT_C void RegisterService(const TBTServiceSecurityB& aService, TRequestStatus& aStatus);
	IMPORT_C void UnregisterService(const TBTServiceSecurityB& aService, TRequestStatus& aStatus);
private:
	TBTServiceSecurityPckgBufB iRegPckg;	///<Stores the parameters passed in during a service registration.
	TBTServiceSecurityPckgBufB iUnregPckg;	///<Stores the parameters passed in during a service unregistration.
	};



_LIT(K70sBCStubPanicName,"BTManClntBC");

#endif

#endif
