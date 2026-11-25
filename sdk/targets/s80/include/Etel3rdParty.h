// Etel3rdParty.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.

// Etel3rdParty.dll interface, using CTelephony class defined here.

#ifndef ETEL3RDPARTY_H__
#define ETEL3RDPARTY_H__

/** @file Etel3rdParty.h
Etel 3rd Party API Header file

Describes the Etel 3rd Party API - classes, methods and types.
 */

#include <e32base.h>
#include <etel.h>

const TInt	KTelephonyMajorVersionNumber=7; ///< Major version-number
const TInt	KTelephonyMinorVersionNumber=0; ///< Minor version-number
const TInt	KTelephonyBuildVersionNumber=0; ///< Build version-number

// Panic numbers returned to applications. 0 upwards...
const TInt KTelephonyPanicIllegalReuse = 0;	///< Client code has attempted to re-post an asynchronous request before the original request has completed.

class CTelephonyFunctions;		// forward declaration

class CTelephony : public CBase
/**
Provides an easy-to-use translation and filtering layer between the telephony "protected" APIs 
allowing access to a subset of the Telephony Multimode functionality.

This class provides support for retrieving Phone Settings, Line Information, Call Functionality, 
Network Information and (basic) Supplementary Service Settings.

@publishedAll
@interim
 */
	{
public:

//////////////////////////////////////////////////////////
//General Functionality
//////////////////////////////////////////////////////////
	
	/** 
	Unique parameter class identifier.
	*/
	enum 
		{
		/** 
		Unique reference identifier for Etel 3rd Party v1.0 parameter classes.
		*/ 
		KEtelISVV1 = 1 
		}; 
	
	
	class TEtelISVType
	/**
	Specifies which version of an API parameter a client has used.  
 	For most ETel ISV v1.0/2.0 parameters this will equal KETelISV1.
	*/
		{
	public:
		IMPORT_C TInt VersionId() const;
	protected:
		TEtelISVType();
	protected:
		TInt iVersionId;
		};
		
	/**
	The maximum number of digits allowed in a multimode telephone number.
	*/
	enum { KMaxTelNumberSize = 100 }; 
	
	/**
	Address types.
	*/
	enum TTelNumberTON
		{
		/** 
		User or the network has no knowledge of the type of number.
	    */
		EUnknownNumber,
		/** 
		International number.
	    */
		EInternationalNumber,
		/** 
		National number.
	    */
		ENationalNumber,
		/** 
		Administration/service number specific to the serving network, e.g. used to 
		access an operator.
	    */
		ENetworkSpecificNumber,
		/** 
		Subscriber number.
	    */
		ESubscriberNumber,
		/** 
		Alphanumeric number.
	    */
		EAlphanumericNumber,
		/** 
		Abbreviated number.
	    */
		EAbbreviatedNumber
		};

	/** 
	Number Plan Indicator.
	*/
	enum TTelNumberNPI
		{
		/** 
		User or the network has no knowledge of the numbering plan.
	    */
		EUnknownNumberingPlan		= 0,
		/** 
		ISDN/telephony numbering plan.
	    */
		EIsdnNumberPlan				= 1,	
		/** 
		Data numbering plan.
	    */	
		EDataNumberPlan				= 3,
		/** 
		Telex numbering plan.
	    */		
		ETelexNumberPlan			= 4,
		/** 
		Service centre specific plan used to indicate a numbering plan specific to external 
		Short Message entities attached to the SMSC.
	    */	
		EServiceCentreSpecificPlan1	= 5,
		/** 
		Service centre specific plan used to indicate a numbering plan specific to external 
		Short Message entities attached to the SMSC.
	    */
		EServiceCentreSpecificPlan2	= 6,
		/** 
		National numbering plan.
	    */
		ENationalNumberPlan			= 8,
		/** 
		Private numbering plan.
	    */
		EPrivateNumberPlan			= 9,
		/** 
		ERMES numbering plan.
	    */
		EERMESNumberPlan			= 10
		};

	class TTelAddress
	/**
	Defines API abstraction of a mobile telephone number.
	*/
		{
	public:
		IMPORT_C TTelAddress();
	public:
		/**
		Type of number.
		*/
		TTelNumberTON 				iTypeOfNumber;
		/**
		Number plan.
		*/
		TTelNumberNPI 				iNumberPlan;
		/**
		Telephone number.
		*/
		TBuf<KMaxTelNumberSize> 	iTelNumber;
		};
	
	/**
	A typedef to hold the telephone number.
	*/
	typedef const TBuf<KMaxTelNumberSize> TTelNumber;	

//////////////////////////////////////////////////////////
// Phone Functionality
//////////////////////////////////////////////////////////
	
	/**
	Max size of Manufacturer Id.
	*/	
	enum { KPhoneManufacturerIdSize = 50 };
	/**
	Max size of Phone Model Id.
	*/	
	enum { KPhoneModelIdSize 		= 50 };
	/**
	Max size ofSerial Number.
	*/	
	enum { KPhoneSerialNumberSize 	= 50 };
	
	
	class TPhoneIdV1 : public TEtelISVType
	/**
	Defines the mobile phone identity.
	*/
		{
	public:
		IMPORT_C TPhoneIdV1();
	public:
		/**
		Phone manufacturer identification, in character string format.
		*/
		TBuf<KPhoneManufacturerIdSize> 	iManufacturer;
		/**
		Phone model identification, in character string format.
		*/
		TBuf<KPhoneModelIdSize> 		iModel;
		/**
		Phone serial number (IMEI or ESN), in character string format.
		*/
		TBuf<KPhoneSerialNumberSize> 	iSerialNumber;
		};
		
	/**
	A typedef'd packaged TPhoneIdV1 for passing through a generic API method
	*/
	typedef TPckg<TPhoneIdV1> TPhoneIdV1Pckg;

	/**
	Maximum size of IMSI identifier.
	*/	
	enum { KIMSISize = 15 };

	class TSubscriberIdV1 : public TEtelISVType
	/**
	Defines the Subscriber (IMSI) Id
	*/
		{
	public:
		IMPORT_C TSubscriberIdV1();
	public: 
		/**
		IMSI identifier.
		*/
		TBuf<KIMSISize> iSubscriberId;
		};
	
	/**
	A typedef'd packaged TSubscriberIdV1 for passing through a generic API method.
	*/
	typedef TPckg<TSubscriberIdV1> TSubscriberIdV1Pckg;

	/**
	The flight mode status.
	*/
	enum TFlightModeStatus
		{
		/**
		Flight mode is off.
		*/
		EFlightModeOff	= 0,
		/**
		Flight mode is on.
		*/
		EFlightModeOn	= 1,
		};

	class TFlightModeV1 : public TEtelISVType
	/**
	Defines the flight mode status.
	*/
		{
	public:
		IMPORT_C TFlightModeV1();
	public:
		/**
		The current status of the mobile radio interface and bluetooth.
		*/ 
		TFlightModeStatus iFlightModeStatus;
		};
	
	/**
	A typedef'd packaged TFlightModeV1 for passing through a generic API method.
	*/
	typedef TPckg<TFlightModeV1> TFlightModeV1Pckg;
	
	/**
	The mobile phone indicators.
	*/	
	enum TPhoneIndicators
		{
		/**
		If bit-flag is set to '1' indicates that the battery charger is connected to the phone. If bit-flag is set to '0' indicates that the battery charger is disconnected
 		For capability: If bit-flag is set to '0' indicates that the battery charger indication reporting is unavailable.
		*/
		KIndChargerConnected	= 0x00000001,
		/**
		If bit-flag is set to '1' indicates that network service is available. If bit-flag is set to '0' indicates that network service is unavailable
		For capability: If bit-flag is set to '0' indicates that the network availability indication reporting is unavailable.
		*/
		KIndNetworkAvailable	= 0x00000002,
		/**
		If bit-flag is set to '1' indicates that a call is in progress. If set to '0' indicates that a call is not in progress
		For capability: If bit-flag is set to '0' indicates that the call is in progress indication reporting is unavailable.
		*/
		KIndCallInProgress		= 0x00000004
		};
		
	class TIndicatorV1 : public TEtelISVType
	/**
	Contains indicator parameters.
	*/
		{
	public:
		IMPORT_C TIndicatorV1();
	public: 
		/**
		The value of the indicator. The result is returned is the sum of TPhoneIndicators constants detailed above.
		*/
		TUint32 iIndicator;
		/**
		The supported (available) indicator capability that the telephony service module offers. 
		The result is returned is the sum of TPhoneIndicators constants detailed above.
		*/
		TUint32 iCapabilities;
		};
	
	/**
	A typedef'd packaged TIndicatorV1 for passing through a generic API method.
	*/
	typedef TPckg<TIndicatorV1> TIndicatorV1Pckg;
		
	/**
	The mobile phone battery status.
	*/	
	enum TBatteryStatus
		{
		/**
		The phone software can not determine the phone's current power status.
		*/
		EPowerStatusUnknown,
		/**
		The phone is powered by the battery.
		*/
		EPoweredByBattery,
		/**
		A battery is connected, but the phone is externally powered.
		*/
		EBatteryConnectedButExternallyPowered,
		/**
		No battery is connected.
		*/
		ENoBatteryConnected,
		/**
		Power fault.
		*/
		EPowerFault
		};
		
	class TBatteryInfoV1 : public TEtelISVType
	/**
	Defines contents of the battery status of the phone.
	*/
		{
	public:
		IMPORT_C TBatteryInfoV1();
	public: 
		/**
		The power and battery status.
		*/
		TBatteryStatus iStatus;
		/**
		The percentage battery charge level.
		*/
		TUint iChargeLevel;
		};
	
	/**
	A typedef'd packaged TBatteryInfoV1 for passing through a generic API method.
	*/
	typedef TPckg<TBatteryInfoV1> TBatteryInfoV1Pckg;
			
	class TSignalStrengthV1 : public TEtelISVType
	/**
	Defines the phone's current signal strength.
	*/
		{
	public:
		IMPORT_C TSignalStrengthV1();
	public: 
		/**
		The value of signal strength.
		*/
		TInt32 iSignalStrength;
		/**
		The absolute number of signal "bars" that the phone should display.  
		*/
		TInt8 iBar;
		};
	
	/**
	A typedef'd packaged TSignalStrengthV1 for passing through a generic API method.
	*/
	typedef TPckg<TSignalStrengthV1> TSignalStrengthV1Pckg;
				
	/**
	Pin 1/Pin 2 security
	*/
	enum TIccLock
		{
		/**
		Lock PIN1 on the ICC. 
		*/
		ELockPin1,
		/**
		Lock PIN2 on the ICC. 
		*/
		ELockPin2
		};

	/**
	Status of an ICC lock.
	*/
	enum TIccLockStatus
		{
		/**
		The status of the lock is unknown.
		*/
		EStatusLockUnknown,
		/**
		Lock is closed.
		User can not access functionality governed by this lock until user correctly enters associated security code.
		*/
		EStatusLocked,
		/**
		Lock is open.
		User can access functionality governed by this lock
		*/
		EStatusUnlocked,
		/**
		Lock is blocked.
		User should enter the unblocking code to be able to switch back to the unlocked mode. 
		Blocking is enabled after a number of unsuccessful attempts to verify PIN1/2.
		*/
		EStatusBlocked
		};

	/**
	Setting of the ICC lock.
	*/
	enum TIccLockSetting
		{
		/**
		The setting of the lock is unknown.
		*/
		ELockSetUnknown,
		/**
		Lock is enabled. 
		Associated security code will be required to unlock the lock, the next time the lock's status is EStatusLocked.
		*/
		ELockSetEnabled,
		/**
		Lock is disabled 
		So its status is always EStatusUnlocked.
		*/
		ELockSetDisabled
		};
		
	class TIccLockInfoV1 : public TEtelISVType
	/**
	Defines the Icc Lock parameters.
	*/
		{
	public:
		IMPORT_C TIccLockInfoV1();
	public: 
		/**
		The current status of the lock. 
		*/
		TIccLockStatus iStatus;
		/**
		The current setting of the lock. 
		*/
		TIccLockSetting iSetting;
		};
	
	/**
	A typedef'd packaged TIccLockInfoV1 for passing through a generic API method.
	*/
	typedef TPckg<TIccLockInfoV1> TIccLockInfoV1Pckg;
					
//////////////////////////////////////////////////////////
// Line Functionality
//////////////////////////////////////////////////////////
					
	/**
	Line types
	*/	
	enum TPhoneLine
		{
		/**
		Voice line.
		*/
		EVoiceLine,
		/**
		Data line.
		*/
		EDataLine,
		/**
		Fax line.
		*/
		EFaxLine,
		};
	
	/**
	Describes the possible call or line states.
	*/	
	enum TCallStatus
		{
		/**
		Indicates that the call status is unknown.
		*/
		EStatusUnknown,
		/**
		Idle line status (no active calls).
		*/
		EStatusIdle,
		/**
		Call dialling status .
		*/
		EStatusDialling,
		/**
		Call ringing status.
		*/
		EStatusRinging,
		/**
		Call answering status.
		*/
		EStatusAnswering,
		/**
		Call connecting status.
		*/
		EStatusConnecting,
		/**
		Call connected status.
		*/
		EStatusConnected,
		/**
		Call is undergoing temporary channel loss and it may or may not be reconnected.
		*/
		EStatusReconnectPending,
		/**
		Call disconnecting status.
		*/
		EStatusDisconnecting,
		/**
		Call on hold.
		*/
		EStatusHold,
		/**
		Call is transferring.
		*/
		EStatusTransferring,
		/**
		Call in transfer is alerting the remote party.
		*/
		EStatusTransferAlerting
		};
		
	class TCallStatusV1 : public TEtelISVType
	/** 
	Defines the current call status.
	*/
		{
	public:
		IMPORT_C TCallStatusV1();
	public: 
		/**
		The current call or line status.
		*/
		TCallStatus iStatus;
		};
	
	/**
	A typedef'd packaged TCallStatusV1 for passing through a generic API method.
	*/
	typedef TPckg<TCallStatusV1> TCallStatusV1Pckg;
	
	/**
	Select a call defined by it current stats.
	*/	
	enum TCallSelect
		{
		/**
		Currently active call.
		*/
		EActiveCall,
		/**
		Currently held (applicable only for voice) call.
		*/
		EHeldCall,
		/**
		Call during the setup/disconnecting process - (dialling/connecting/answering/hanging up).
		*/
		EInProgressCall
		};
		
	class TCallSelectionV1 : public TEtelISVType
	/**
	Defines parameters to select a call, determined by its call state for a specific line 
	*/
		{
	public:
		IMPORT_C TCallSelectionV1();
	public: 
		/**
		The current phone line selection.
		*/		
		TPhoneLine iLine;
		/**
		The current call selection.
		*/
		TCallSelect iSelect;
		};
	
	/**
	A typedef'd packaged TCallSelectionV1 for passing through a generic API method.
	*/
	typedef TPckg<TCallSelectionV1> TCallSelectionV1Pckg;
		
	/**
	Etel 3rd Party owned call identifiers
	*/
	enum TCallId
		{
		/**
		Call owned by this ISV applcation.
		*/
		EISVCall1,
		/**
		Call owned by this ISV applcation.
		*/
		EISVCall2,
		/**
		Max number of calls supported by Etel 3rd Party.
		*/
		EISVMaxNumOfCalls
		};	
		
	/**
	Remote party identity status.
	*/
	enum TCallRemoteIdentityStatus
		{
		/**
		The remote party's identity can not be determined. 
		*/
		ERemoteIdentityUnknown,
		/**
		The remote party's identity is available.
		*/
		ERemoteIdentityAvailable,
		/**
		The remote party has suppressed the transmission of its identity.
		*/
		ERemoteIdentitySuppressed
		};

	/**
	The direction of the call.
	*/
	enum TCallDirection
		{
		/**
		The direction of the call is unknown.
		*/
		EDirectionUnknown,
		/**
		The call was originated by this phone, i.e. it is an outgoing call.
		*/
		EMobileOriginated,
		/**
		The call was terminated by this phone, i.e. it is an incoming call.
		*/
		EMobileTerminated
		};

	/**
	Enumerated network security types.
	*/
	enum TPhoneNetworkSecurity
		{
		/**
		The encryption level is NONE.
		*/
		ECipheringOff,
		/**
		The encryption level is GSM.(standard encryption algorithms for 2nd Generation Mobile networks).
		*/
		ECipheringGSM,
		/**
		The encryption level is WDCMA.(standard encryption algorithms for 3rd Generation Mobile networks).
		*/
		ECipheringWCDMA
		};
			
	class TCallInfoV1 : public TEtelISVType
	/**
	Defines general information about a call.
	*/
		{
	public:
		IMPORT_C TCallInfoV1();
	public: 
		/**
		The current status of the call.
		*/
		TCallStatus iStatus;
		/**
		The time & date the call started.
		*/
		TDateTime iStartTime;
		/**
		The current duration of the call.
		*/
		TTimeIntervalSeconds iDuration;
		/**
		The original number (including DTMF) dialled for an outgoing call.
		*/
		TTelAddress iDialledParty;
		/**
		The reason for termination of a finished call. 
		Will equal KErrNone if the call ended normally and KErrNotFound if the call has not ended.
		*/
		TInt iExitCode;
		/**
		This attribute indicates whether Ciphering Status of a Call is enabled or disabled. 
		*/
		TPhoneNetworkSecurity iSecurity;
		/**
		The call id of an ISV application owned call. For calls not owned by this ISV application (-1) is returned.
		*/
		TInt iCallId;
		};
	
	/**
	A typedef'd packaged TCallInfoV1 for passing through a generic API method.
	*/
	typedef TPckg<TCallInfoV1> TCallInfoV1Pckg;
		
	/**
	Maximum size of the calling party name.
	*/
	enum { KCallingNameSize = 80 };

	class TRemotePartyInfoV1 : public TEtelISVType
		{
		/**
		Defines information about the remote party of a call.
		*/
	public:
		IMPORT_C TRemotePartyInfoV1();
	public: 
		/**
		Indicates whether the remote party information in the rest of this structure is valid or not.
		*/
		TCallRemoteIdentityStatus iRemoteIdStatus;
		/**
		Calling party name available through the CNAP supplementary service (if provisioned).
		*/
		TBuf<KCallingNameSize> iCallingName;
		/**
		The phone number of the remote party if available.
		*/
		TTelAddress iRemoteNumber;
		/**
		The direction of the call and hence the role of the remote party. 
		i.e. if the call is mobile originated then the remote party is the called party.
		Whereas if the call is mobile terminated then the remote party is the calling party.
		*/
		TCallDirection iDirection;
		};
	
	/**
	A typedef'd packaged TCallRemotePartyInfoV1 for passing through a generic API method.
	*/
	typedef TPckg<TRemotePartyInfoV1> TRemotePartyInfoV1Pckg;
	
//////////////////////////////////////////////////////////
// Call Functionality
//////////////////////////////////////////////////////////
	
	/**
	Caller Id restriction settings.
	*/				
	enum TCallerIdentityRestrict
		{
		/**
		The default setting should be used if the user has not explicitly requested their identity to be restricted/allowed.
		*/
		EIdRestrictDefault,
		/**
		The user has explicitly requested their identity to be sent for this call.
		*/
		ESendMyId,
		/**
		The user has explicitly requested their identity not to be sent for this call.
		*/
		EDontSendMyId
		};	
		
	class TCallParamsV1 : public TEtelISVType
		{
		/**
		Defines the parameters used for set-up of a call.
		*/
	public:
		IMPORT_C TCallParamsV1();
	public: 
		/**
		Call Id restriction setting to be used for this call.
		*/
		TCallerIdentityRestrict iIdRestrict;
		};
	
	/**
	A typedef'd packaged TCallParamsV1 for passing through a generic API method.
	*/
	typedef TPckg<TCallParamsV1> TCallParamsV1Pckg;
						
	/**
	Mobile call control capabilites.
	*/	
	enum TMobileCallControlCaps 
		{
		/**
		Indicates that this call can be put on hold. 
		This implies that the call is currently active and that there is no other held call.
		*/
		KCapsHold 	= 0x00000200,
		/**
		Indicates that this call can be resumed. 
		This implies that the call is currently on hold and that there is no other active call.
		*/
		KCapsResume = 0x00000400,
		/**
		Indicates that this call's state can be swapped to the opposite state. 
		This implies that this call is either active or held. 
		There may be another call in the opposite state and if this is the case then both calls will be simultaneously swapped to their opposite state.
		*/
		KCapsSwap 	= 0x00000800
		};

	class TCallCapsV1 : public TEtelISVType
		{
		/**
		 Defines the dynamic capabilities of a call.
		*/
	public:
		IMPORT_C TCallCapsV1();
	public: 
		/**
		Call Id restriction setting to be used for this call. 
		*/
		TUint32 iControlCaps;
		};
	
	/**
	A typedef'd packaged TCallParamsV1 for passing through a generic API method.
	*/
	typedef TPckg<TCallCapsV1> TCallCapsV1Pckg;
	
			
//////////////////////////////////////////////////////////
// Network Functionality
//////////////////////////////////////////////////////////
							
	/**
	The registration status of the phone.
	*/	
	enum TRegistrationStatus
		{
		/**
		Registration status is unknown.
		*/
		ERegistrationUnknown,
		/**
		Not registered. The ME can not detect any other networks and is not currently searching a new operator to register to.
		*/
		ENotRegisteredNoService,
		/**
		Not registered. The ME can detect other networks on which it is possible to make emergency calls only.
		*/
		ENotRegisteredEmergencyOnly,
		/**
		Not registered, but the ME is currently searching a new operator to register to.
		*/
		ENotRegisteredSearching,
		/**
		Registered, network busy.
		*/
		ERegisteredBusy,
		/**
		Registered on home network.
		*/
		ERegisteredOnHomeNetwork,
		/**
		Registration denied.
		*/
		ERegistrationDenied,
		/**
		Registered, roaming.
		*/
		ERegisteredRoaming
		};
				
	class TNetworkRegistrationV1 : public TEtelISVType
		/**
		Defines the current network registration status
		*/
		{
	public:
		IMPORT_C TNetworkRegistrationV1();
	public: 
		/**
        The current network registration status.
		*/		
		TRegistrationStatus iRegStatus;
		};
	
	/**
	A typedef'd packaged TNetworkRegistrationV1 for passing through a generic API method.
	*/
	typedef TPckg<TNetworkRegistrationV1> TNetworkRegistrationV1Pckg;
									
	/***********************************************/
	// CTelephony::TNetworkInfoV1
	
	/**
	Maximum size of the network country code.
	*/
	enum { KNetworkCountryCodeSize 	= 4  };
	/**
	Maximum size of the network identity..
	*/
	enum { KNetworkIdentitySize 	= 8  };
	/**
	Maximum size of the network display tag..
	*/
	enum { KNetworkDisplayTagSize 	= 32 };
	/**
	Maximum size of the short network name.
	*/
	enum { KNetworkShortNameSize 	= 8  };
	/**
	Maximum size of the long network name.
	*/
	enum { KNetworkLongNameSize 	= 16 };
	
	/**
	Defines Current Network Modes.
	*/
	enum TNetworkMode
		{
		/**
		Network mode is unknown.
		*/
		ENetworkModeUnknown,
		/**
		Mobile device is not registered.
		*/
		ENetworkModeUnregistered,
		/**
		GSM/GPRS or DCS1800 network.
		*/
		ENetworkModeGsm,
		/**
		AMPS network.
		*/
		ENetworkModeAmps,
		/**
		CDMA (IS-95) network.
		*/
		ENetworkModeCdma95,
		/**
		CDMA (cdma2000) network.
		*/
		ENetworkModeCdma2000,
		/**
		WCDMA network.
		*/
		ENetworkModeWcdma
		};
	
	/**
	The access technology that the network is based on.
	*/	
	enum TNetworkAccess
		{
		/**
		This is used when there is no network activity and therefore no RAT active.
		*/
		ENetworkAccessUnknown,
		/**
		The access technology is GSM.
		*/
		ENetworkAccessGsm,
		/**
		The access technology is GSM COMPACT.
		However GSM COMPACT systems which use GSM frequency bands but with the CBPCCH broadcast channel are considered as a separate access technology from GSM.
		*/
		ENetworkAccessGsmCompact,
		/**
		The access technology is UTRAN (UMTS Network).
		*/
		ENetworkAccessUtran
		};

	/**
	Phone network status.
	*/
	enum TNetworkStatus
		{
		/**
		Status is unknown.
		*/
		ENetworkStatusUnknown,
		/**
		A network that the mobile device is allowed to register to.
		*/
		ENetworkStatusAvailable,
		/**
		Currently registered network.
		*/
		ENetworkStatusCurrent,
		/**
		A network that the ME is not allowed to register to.
		*/
		ENetworkStatusForbidden
		};

	/**
	Mobile phone network band information.
	*/
	enum TNetworkBandInfo
		{
		/**
		The current band and band class is unknown.
		*/
		EBandUnknown,
		/**
		The network operates at 800MHz on Band A.
		*/
		E800BandA,
		/**
		The network operates at 800MHz on Band B.
		*/
		E800BandB,
		/**
		The network operates at 800MHz on Band C.
		*/
		E800BandC,
		/**
		The network operates at 1900MHz on Band A.
		*/
		E1900BandA,
		/**
		The network operates at 1900MHz on Band B.
		*/
		E1900BandB,
		/**
		The network operates at 1900MHz on Band C.
		*/
		E1900BandC,
		/**
		The network operates at 1900MHz on Band D.
		*/
		E1900BandD,
		/**
		The network operates at 1900MHz on Band E.
		*/
		E1900BandE,
		/**
		The network operates at 1900MHz on Band F.
		*/
		E1900BandF
		};

	class TNetworkInfoV1 : public TEtelISVType
	/**
	Defines information related to a mobile phone network.
	*/
		{
	public:
		IMPORT_C TNetworkInfoV1();
	public:
		/**
		Mode of the network.
		*/
		TNetworkMode iMode;
		/**
		Status of the network
		*/
		TNetworkStatus iStatus;
		/**
		The MCC of the network.
		*/
		TBuf<KNetworkCountryCodeSize> 	iCountryCode;
		/**
		The network identity (NID in CDMA and MNC in GSM).
		*/
		TBuf<KNetworkIdentitySize> 		iNetworkId;
		/**
		The alpha-tag displayed when this is the serving network.
		*/
		TBuf<KNetworkDisplayTagSize> 	iDisplayTag;
		/**
		The short name (up to 8 characters) of the network operator.
		*/
		TBuf<KNetworkShortNameSize> 	iShortName;
		/**
		The band and band class of the CDMA network operator.
		*/
		TNetworkBandInfo iBandInfo;
		/**
		The system identity (SID) of the CDMA or AMPS network 
		*/
		TBuf<KNetworkIdentitySize> 		iCdmaSID;
		/**
		The long name (up to 16 characters) of the network operator.
		*/
		TBuf<KNetworkLongNameSize> 		iLongName;
		/**
		The type of network access.
		*/
		TNetworkAccess iAccess;
		/**
		Boolean indicating whether the location area is known.
		*/
		TBool iAreaKnown;
		/**
		Location area code.
		*/
		TUint iLocationAreaCode;
		/**
		Cell identity code.
		*/
		TUint iCellId;
		};
	
	/**
	A typedef'd packaged TNetworkInfoV1for passing through a generic API method.
	*/
	typedef TPckg<TNetworkInfoV1> TNetworkInfoV1Pckg;
									
	class TNetworkNameV1 : public TEtelISVType
	/**
	Defines the name network name.
	*/
		{
	public:
		IMPORT_C TNetworkNameV1();
	public:
		/**
		The displayed name (up to 16 characters) of the network provider.
		*/
		TBuf<KNetworkLongNameSize> 		iNetworkName;
		};
	
	/**
	A typedef'd packaged TNetworkNameV1 for passing through a generic API method.
	*/
	typedef TPckg<TNetworkNameV1> TNetworkNameV1Pckg;
								
	class TOperatorNameV1 : public TEtelISVType
	/**
	Defines the curreent operator.
	*/
		{
	public:
		IMPORT_C TOperatorNameV1();
	public:
		/**
		 The displayed name (up to 16 characters) of the network operator. 
		*/
		TBuf<KNetworkLongNameSize> 		iOperatorName;
		};
	
	/**
	A typedef'd packaged TOperatorNameV1 for passing through a generic API method.
	*/
	typedef TPckg<TOperatorNameV1> TOperatorNameV1Pckg;
				
//////////////////////////////////////////////////////////
// (Basic) Supplementary Services Functionality
//////////////////////////////////////////////////////////

	/**
	Supplementary Service status.
	*/
	enum TSupplServiceStatus
		{
		/**
		The supplementary service is currently active and operative.
		*/
		EStatusActive,
		/**
		The supplementary service is currently deactivated or quiescent.
		*/
		ENotActive,
		/**
		In GSM/WCDMA mode, the supplementary service is not provisioned.
		In CDMA mode, this value has no meaning.
		*/
		ENotProvisioned,
		/**
		In GSM/WCDMA mode, the supplementary service is not available in serving network.
		In CDMA mode, the supplementary service is not available in the phone.
		*/
		ENotAvailable,
		/**
		The phone can not determine supplementary service status.
		*/
		EUnknown
		};
											
	/**
	Call Forwarding conditions.
	*/
	enum TCallForwardingCondition
		{
		/**
		All calls to this subscriber are forwarded.
		*/
		ECallForwardingUnconditional,
		/**
		Calls are forwarded when this subscriber is busy.
		*/
		ECallForwardingBusy,
		/**
		Calls are forwarded when this subscriber does not reply within a timeout period.
		*/
		ECallForwardingNoReply,
		/**
		Calls are forwarded when this subscriber is unreachable.
		*/
		ECallForwardingNotReachable
		};
		
	class TCallForwardingSupplServicesV1 : public TEtelISVType
	/**
	Defines information about the call forwarding service.
	*/
		{
	public:
		IMPORT_C TCallForwardingSupplServicesV1();
	public:
		/**
		The status of the call forwarding supplementary service for this line.
		*/
		TSupplServiceStatus iCallForwarding;
		/**
		The provisioned call forwarding condition for this line.
		*/
		TCallForwardingCondition iCallForwardingCondition;
		};
	
	/**
	A typedef'd packaged TCallForwardingSupplServicesV1 for passing through a generic API method.
	*/
	typedef TPckg<TCallForwardingSupplServicesV1> TCallForwardingSupplServicesV1Pckg;
									

	/**
	Call Barring conditions.
	*/	
	enum TCallBarringCondition
		{
		/**
		All incoming calls to this subscriber are barred (BAIC).
		*/
		EBarAllIncoming,
		/**
		All incoming calls to this subscriber are barred when roaming outside the home PLMN country (BAIC-roam).
		*/
		EBarIncomingRoaming,
		/**
		All outgoing calls by this subscriber are barred (BAOC).
		*/
		EBarAllOutgoing,
		/**
		All outgoing international calls by this subscriber are barred (BOIC).
		*/
		EBarOutgoingInternational,
		/**
		All outgoing international calls except those directed to the home PLMN country by this subscriber are barred (BOIC-ExHC).
		*/
		EBarOutgoingInternationalExHC
		};
		
	class TCallBarringSupplServicesV1 : public TEtelISVType
	/**
	Defines information about the call barring service.
	*/
		{
	public:
		IMPORT_C TCallBarringSupplServicesV1();
	public:
		/**
		 The status of the call barring supplementary service for this line.
		*/
		TSupplServiceStatus iCallBarring;
		/**
	    The provisioned call barring condition for this line.
		*/
		TCallBarringCondition iCallBarringCondition;
		};
	
	/**
	A typedef'd packaged TCallBaringSupplServicesV1for passing through a generic API method.
	*/
	typedef TPckg<TCallBarringSupplServicesV1> TCallBarringSupplServicesV1Pckg;
						
	class TCallWaitingSupplServicesV1 : public TEtelISVType
	/**
	Defines information about the call waiting service.
	*/
		{
	public:
		IMPORT_C TCallWaitingSupplServicesV1();
	public:
		/**
		The status of the call waiting supplementary service for this line.
		*/
		TSupplServiceStatus iCallWaiting;
		};
	
	/**
	A typedef'd packaged TCallWaitingSupplServicesV1 for passing through a generic API method.
	*/
	typedef TPckg<TCallWaitingSupplServicesV1> TCallWaitingSupplServicesV1Pckg;

	/**
	Phone ID services.
	*/		
	enum TIdentityService
		{
		/**
		The identity service is unspecified.
		*/
		EIdServiceUnspecified,
		/**
		The caller's ID is presented to the called party.
		*/
		EIdServiceCallerPresentation,
		/**
		The caller's ID is restricted to the called party.
		*/
		EIdServiceCallerRestriction
		};
	
	/**
	Service status of the Phone ID services.
	*/
	enum TIdentityServiceStatus
		{
		/**
		The interrogated identity service is provisioned and permanently active.
		*/
		EIdServiceActivePermanent,
		/**
		The interrogated identity service is provisioned and active.
		*/
		EIdServiceActiveDefaultRestricted,
		/**
		The interrogated identity service is provisioned and active.
		*/
		EIdServiceActiveDefaultAllowed,
		/**
		The interrogated identity service is not provisioned.
		*/
		EIdServiceNotProvisioned,
		/**
		The status of the interrogated Identity service is unknown.
		*/
		EIdServiceUnknown
		};
			
	class TIdentityServiceV1 : public TEtelISVType
	/**
	Defines the call identity service status.
	*/
		{
	public:
		IMPORT_C TIdentityServiceV1();
	public:
		/**
		The status of the call identity service.
		*/
		TIdentityServiceStatus iIdentityStatus;
		};
	
	/**
	A typedef'd packaged TIdentityServicesV1for passing through a generic API method.
	*/
	typedef TPckg<TIdentityServiceV1> TIdentityServiceV1Pckg;
	
	/**
	Service group identifier.
	*/
	enum TServiceGroup
		{
		/**
		Voice service group
		*/
		EVoiceService,
		/**
		Fax service group
		*/
		EFaxService,
		/**
		Data service group
		*/
		EDataService
		};
						
	/**
	Cancel apending request 
	*/
	enum TCancellationRequest
		{	
		/**
		Cancel a pending GetPhoneId request.
		*/
		EGetPhoneIdCancel,
		/**
		Cancel a pending GetSubscriberId request.
		*/
		EGetSubscriberIdCancel,
		/**
		Cancel a pending GetFlightMode request.
		*/
		EGetFlightModeCancel,
		/**
		Cancel a pending FlightModeChange request.
		*/
		EFlightModeChangeCancel,
		/**
		Cancel a pending GetIndicator request.
		*/
		EGetIndicatorCancel,
		/**
		Cancel a pending IndicatorChange request.
		*/
		EIndicatorChangeCancel,
		/**
		Cancel a pending GetBatteryInfo request.
		*/
		EGetBatteryInfoCancel,
		/**
		Cancel a pending BatteryInfoChange request.
		*/
		EBatteryInfoChangeCancel,
		/**
		Cancel a pending GetSignalStrength request.
		*/
		EGetSignalStrengthCancel,
		/**
		Cancel a pending SignalStrengthChange request.
		*/
		ESignalStrengthChangeCancel,
		/**
		Cancel a pending GetLockInfo request.
		*/
		EGetLockInfoCancel,
		/**
		Cancel a pending Pin 1 LockInfoChange request.
		*/
		EPin1LockInfoChangeCancel,
		/**
		Cancel a pending Pin 2 LockInfoChange request.
		*/
		EPin2LockInfoChangeCancel,
		/**
		Cancel a pending VoiceLineStatusChange request.
		*/
		EVoiceLineStatusChangeCancel,
		/**
		Cancel a pending Call1StatusChange request.
		*/
		EOwnedCall1StatusChangeCancel,
		/**
		Cancel a pending Call2StatusChange request.
		*/
		EOwnedCall2StatusChangeCancel,
		/**
		Cancel a pending OwnedCall1RemotePartyInfoChange request.
		*/
		EOwnedCall1RemotePartyInfoChangeCancel,
		/**
		Cancel a pending OwnedCall2RemotePartyInfoChange request.
		*/
		EOwnedCall2RemotePartyInfoChangeCancel,
		/**
		Cancel a pending SendDTMFTones request.
		*/
		ESendDTMFTonesCancel,
		/**
		Cancel a pending DialNewCall request.
		*/
		EDialNewCallCancel,
		/**
		Cancel a pending Hold request.
		*/
		EHoldCancel,
		/**
		Cancel a pending Resume request.
		*/
		EResumeCancel,
		/**
		Cancel a pending Swap request.
		*/
		ESwapCancel,
		/**
		Cancel a pending Hangup request.
		*/
		EHangupCancel,
		/**
		Cancel a pending AnswerIncomingCall request.
		*/
		EAnswerIncomingCallCancel,
		/**
		Cancel a pending GetNetworkRegistrationStatus request.
		*/
		EGetNetworkRegistrationStatusCancel,
		/**
		Cancel a pending NetworkRegistrationStatusChange request.
		*/
		ENetworkRegistrationStatusChangeCancel,
		/**
		Cancel a pending GetCurrentNetworkInfo request.
		*/
		EGetCurrentNetworkInfoCancel,
		/**
		Cancel a pending CurrentNetworkInfoChange request.
		*/
		ECurrentNetworkInfoChangeCancel,
		/**
		Cancel a pending GetCurrentNetworkName request.
		*/
		EGetCurrentNetworkNameCancel,
		/**
		Cancel a pending GetOperatorName request.
		*/
		EGetOperatorNameCancel,
		/**
		Cancel a pending GetCallForwardingStatus request.
		*/
		EGetCallForwardingStatusCancel,
		/**
		Cancel a pending GetCallBarringStatus request.
		*/
		EGetCallBarringStatusCancel,
		/**
		Cancel a pending GetCallWaitingStatus request.
		*/
		EGetCallWaitingStatusCancel,
		/**
		Cancel a pending GetIdentityServiceStatus request.
		*/
	 	EGetIdentityServiceStatusCancel 		 			
		};
						
//////////////////////////////////////////////////////////
// Notification Functionality
//////////////////////////////////////////////////////////
	
	/**
	Notification events
	*/
	enum TNotificationEvent
		{
		/**
		Register interest for receiving a notification for flight mode changes.
		*/
		EFlightModeChange,
		/**
		Register interest for receiving a notification for phone indicator changes.
		*/
		EIndicatorChange,
		/**
		Register interest for receiving a notification for Battery information changes.
		*/
		EBatteryInfoChange,
		/**
		Register interest for receiving a notification for Signal Strength changes.
		*/
		ESignalStrengthChange,
		/**
		Register interest for receiving a notification for Icc Pin1 Lock Information changes.
		*/
		EPin1LockInfoChange,
		/**
		Register interest for receiving a notification for Icc Pin2 Lock Information changes.
		*/
		EPin2LockInfoChange,
		/**
		Register interest for receiving a notification for Voice Line Status changes.
		*/
		EVoiceLineStatusChange,
		/**
		Register interest for receiving a notification for owned Call 1 Status changes.
		*/
		EOwnedCall1StatusChange,
		/**
		Register interest for receiving a notification for owned Call 2 Status changes.
		*/
		EOwnedCall2StatusChange,
		/**
		Register interest for receiving a notification for call1 Remote Party Info changes.
		*/
		EOwnedCall1RemotePartyInfoChange,
		/**
		Register interest for receiving a notification for call2 Remote Party Info changes.
		*/
		EOwnedCall2RemotePartyInfoChange,
		/**
		Register interest for receiving a notification for Network registration status changes.
		*/
		ENetworkRegistrationStatusChange,
		/**
		Register interest for receiving a notification for Network information changes.
		*/
		ECurrentNetworkInfoChange
		};		
		
public:				
	// Constructors
	IMPORT_C static CTelephony* NewLC();
	IMPORT_C static CTelephony* NewL();
	
	// Destructor - virtual and class not intended
	// for derivation, so not exported
	
	~CTelephony();

	// General Functionality
	inline TVersion Version() const;

	// Phone Functionality
	IMPORT_C void GetPhoneId(TRequestStatus& aReqStatus, TDes8& aId) const;
	IMPORT_C void GetSubscriberId(TRequestStatus& aReqStatus, TDes8& aId) const;
	IMPORT_C void GetFlightMode(TRequestStatus& aReqStatus, TDes8& aMode) const;
	IMPORT_C void GetIndicator(TRequestStatus& aReqStatus, TDes8& aIndicator) const;
	IMPORT_C void GetBatteryInfo(TRequestStatus& aReqStatus, TDes8& aBatteryInfo) const;
	IMPORT_C void GetSignalStrength(TRequestStatus& aReqStatus, TDes8& aSignalStrength) const;
	IMPORT_C void GetLockInfo(TRequestStatus& aReqStatus, const TIccLock& aLock, TDes8& aLockInfo) const;
	IMPORT_C void SendDTMFTones(TRequestStatus& aReqStatus, const TDesC& aTones) const;
	// Line Functionality
	IMPORT_C TInt GetLineStatus(const TPhoneLine& aLine, TDes8& aStatus) const;
	IMPORT_C TInt GetCallInfo(TDes8& aCallSelect, TDes8& aCallInfo, TDes8& aRemoteInfo) const;
	// Call Functionality
	IMPORT_C void DialNewCall(TRequestStatus& aStatus, TDes8& aCallParams, 
		const TTelNumber& aTelNumber, TCallId& aCallId, const TPhoneLine aLine=EVoiceLine) const; 
	IMPORT_C TInt GetCallDynamicCaps(const TCallId& aCallId, TDes8& aCallCaps) const; 
	IMPORT_C TInt GetCallStatus(const TCallId& aCallId, TDes8& aCallStatus) const; 
	IMPORT_C void Hold(TRequestStatus& aReqStatus, const TCallId& aCallId) const;
	IMPORT_C void Resume(TRequestStatus& aReqStatus, const TCallId& aCallId) const;
	IMPORT_C void Swap(TRequestStatus& aReqStatus, const TCallId& aCallId1, 
		const TCallId& aCallId2) const;
	IMPORT_C void Hangup(TRequestStatus& aReqStatus, const TCallId& aCallId) const;
	IMPORT_C void AnswerIncomingCall(TRequestStatus& aReqStatus, TCallId& aCallId, 
		const TPhoneLine aLine=EVoiceLine) const;
	// Network Functionality
	IMPORT_C void GetNetworkRegistrationStatus(TRequestStatus& aReqStatus, TDes8& aStatus) const;
	IMPORT_C void GetCurrentNetworkInfo(TRequestStatus& aReqStatus, TDes8& aNetworkInfo) const;
	IMPORT_C void GetCurrentNetworkName(TRequestStatus& aReqStatus, TDes8& aNetworkName) const;
	IMPORT_C void GetOperatorName(TRequestStatus& aReqStatus, TDes8& aOperator) const;
 	// (Basic) Supplementary Services Functionality
	IMPORT_C void GetCallForwardingStatus(TRequestStatus& aRequestStatus, const	TCallForwardingCondition aCondition, TDes8& aSSInfo, const TServiceGroup aServiceGroup=EVoiceService) const;
	IMPORT_C void GetCallBarringStatus(TRequestStatus& aRequestStatus, const TCallBarringCondition aCondition, TDes8& aSSInfo, const TServiceGroup aServiceGroup=EVoiceService) const;
	IMPORT_C void GetCallWaitingStatus(TRequestStatus& aRequestStatus, TDes8& aSSInfo, const TServiceGroup aServiceGroup=EVoiceService) const;
	IMPORT_C void GetIdentityServiceStatus(TRequestStatus& aReqStatus, const TIdentityService& aService, TDes8& aStatus) const;
  	// Cancel Request Functionality
	IMPORT_C TInt CancelAsync(TCancellationRequest aCancel) const;
 	// Notification Functionality
	IMPORT_C void NotifyChange(TRequestStatus& aReqStatus, const TNotificationEvent& aEvent, TDes8& aDes) const;
 	
	IMPORT_C TInt FindDeviceStatus(RCall::TStatus& aCallStatus);
	IMPORT_C TInt EstablishDataCall(RComm& aDataChannel, const TDesC& aDialNumber);
	IMPORT_C void EstablishDataCall(TRequestStatus& aRequestStatus, RComm& aDataChannel, const TDesC& aDialNumber);
	IMPORT_C TInt TerminateDataCall();
	IMPORT_C TInt ReceiveDataCall(RComm& aDataChannel);
	IMPORT_C void ReceiveDataCall(TRequestStatus& aRequestStatus, RComm& aDataChannel);
	IMPORT_C void CancelEstablishDataCall();
	IMPORT_C void CancelReceiveDataCall();

private:	
	CTelephony();	// C++ constructor - not exported. Called from NewLC()
	void ConstructL();	// second-phase constructor
	void NewTeleFindDeviceStatusL(RCall::TStatus& aCallStatus);
	CTelephonyFunctions*	iTelephonyFunctions;	///< Object to do the real work
	};
	
#include "telephony.inl"	
#endif	// ETEL3RDPARTY_H__
