/**
@file CDBCOLS.H

General definitions for client use
		Table and column names,
		Enums and constants use in tables,
		UIDs for notifications

Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
*/

/** 
 * @file CDBCOLS.H
 *
 * - General definitions for client use
 * - Table and column names,
 * - Enums and constants use in tables,
 * - UIDs for notifications
 * 
 * @publishedAll 
 */


#ifndef __CDBCOLS_H__
#define __CDBCOLS_H__

#include <e32std.h>

// Database table names. The name (a string) of each table is defined by a macro.
#define NETWORK											_S("Network")
/** Internet access point table identifier.*/
#define IAP												_S("IAP")
/** Identifier of default dial-out ISP table.

Field type: TUint32 */
#define DIAL_OUT_ISP									_S("DialOutISP")
/** Dial-in Internet Service Provider.
*/
#define DIAL_IN_ISP										_S("DialInISP")
/** Outgoing WCDMA table.
*/
#define OUTGOING_WCDMA									_S("OutgoingGPRS")
/**
Not used in v7.0 */
#define INCOMING_WCDMA									_S("IncomingGPRS")	
#define LAN_SERVICE										_S("LANService")	// test use only

/**
Identifier of modem settings table.
In v7.0s, this table changed its name from MODEM to MODEM_BEARER.
In v6.1, it is possible to define only a single record for this table. */
#define MODEM_BEARER									_S("ModemBearer")
#define LAN_BEARER										_S("LANBearer")
/** Identifier of the default location table.
In 6.1, it is possible to define only a single record for this table.
Field type: TUint32 */
#define LOCATION										_S("Location")
/** Identifier of the default chargecard table.

Field type: TUint32 */
#define CHARGECARD										_S("Chargecard")
/** Identifier of proxy server settings table.*/
#define PROXIES											_S("Proxies")
/** Identifier of default WAP Access Point table.

Field type: TUint32 */
#define WAP_ACCESS_POINT								_S("WAPAccessPoint")
/** WAP IP bearer. */
#define WAP_IP_BEARER									_S("WAPIPBearer")
/** WAP SMS bearer. */
#define WAP_SMS_BEARER									_S("WAPSMSBearer")
/** GPRS default settings.

It is possible to define only one record for  this table.
*/
#define DEFAULT_GPRS									_S("DefaultGPRS")
/** Bluetooth device table. */
#define BT_DEVICE_TABLE									_S("BTDeviceTable")
/** Bluetooth default table. */
#define BT_DEFAULT_TABLE								_S("BTDefaultTable")
/** Bluetooth security table. */
#define BT_SECURITY_TABLE								_S("BTSecurityTable")
/** Bluetooth persist table. */
#define BT_PERSIST_TABLE								_S("BTPersistTable") 
/** Identifier of the sockets table.*/
#define SS_PROTO_TABLE									_S("SecureSocketTable")
/** Agent lookup table identifier*/
#define AGENT_LOOKUP									_S("AgentLookup")
/** CMDA2000 packet service table.*/
#define CDMA2000_PACKET_SERVICE_TABLE					_S("CDMA2000PacketServiceTable")
/** CDMA2000 default settings.*/
#define DEFAULT_CDMA2000_SETTINGS_TABLE					_S("DefaultCDMA2000SettingsTable")
#define VIRTUAL_BEARER									_S("VirtualBearer")
#define VPN_SERVICE										_S("VpnService")

//DEPRECATED : MODEM has been reassigned so as to maintain backwards compatibility
/** Identifier of default modem.

Field type: TUint32
@deprecated Unsupported since v7.0 */
#define MODEM											MODEM_BEARER
// Just in case any applications use the literal pre-7.0s string for the ModemBearer table.
/** @deprecated Unsupported since v7.0 */
#define OLD_MODEM_TABLE									_S("Modem")


//
// Global settings.
// The following macros define values for the Global table fields.
// Note that Global table fields are accessed through CCommsDatabase.
//
/** Number of times to attempt redial when the ISP number is busy.

Field type: TUint32 */
#define REDIAL_ATTEMPTS									_S("RedialAttempts")				
/** The bearer for sending SMS.

Values for this are defined by the enum RMobileSmsMessaging::TMobileSmsBearer

Field type: TUint32 */
#define SMS_BEARER										_S("SmsBearer")				// Takes the values of RGprs::TSmsBearer from ETEL
/** The SMS receive mode, taken from RMobileSmsMessaging::TMobileSmsReceiveMode.

Field type:TUint32 */
#define SMS_RECEIVE_MODE								_S("SmsReceiveMode")		// Takes the values of RMobileSmsMessaging::TMobileSmsReceiveMode from ETel MM
/** The GPRS attach mode, i.e. whether to attach at the boot-up of the device or 
at a later time.

Values for this are defined by the enum RPacketService::TAttachMode
Field type: TUint32 */
#define GPRS_ATTACH_MODE								_S("GPRSAttachMode")				// Takes the values of RGprs::TGprsAttachMode from ETEL
/** Whether or not to allow incoming requests for PDP context activation to be automatically 
accepted (when there is a waiting application).

Use a TBool to specify the value.

Field type: TUint32 */
#define ACCEPT_INCOMING_GPRS							_S("AcceptIncomingGprs")			// Takes a TBool value - ETrue = accept incoming requests, EFalse = reject incoming requests
/** The preferred bearer when device is forced into GPRS Class C operation.

The values for this field are defined by TCommDbGprsClassCBearer.

Field type: TUint32

@see TCommDbGprsClassCBearer */
#define GPRS_CLASS_C_BEARER								_S("GPRSClassCBearer")				// Takes the values of TCommDbGprsClassCBearer
/** The number of connection attempts (preferences) to make. 

This is limited to a maximum of 2.

Field type: TUint32 */
#define CONNECTION_ATTEMPTS								_S("ConnectionAttempts")			// Number of connection preferences, with incremental rank, to try
/** Specifies the ID of the modem record to be used for data transactions.

Field type: TUint32 */
#define MODEM_DATA_FAX									_S("ModemForDataAndFax")
/** Specifies the ID of the modem record to be used for phone services such as SMS.

Field type: TUint32 */
#define MODEM_PHONE_SERVICES_SMS						_S("ModemForPhoneServicesAndSMS")
/** Specifies the location to be used with the default modem for data transactions.

Field type: TUint32 */
#define LOCATION_DATA_FAX								_S("LocationForDataAndFax")
/** Specifies the location to be used with default modem for phone services such 
as SMS.

Field type: TUint32 */
#define LOCATION_PHONE_SERVICES_SMS						_S("LocationForPhoneServicesAndSMS")
/** Maximum RMBuf heap size.

Field type: TUint32 */
#define MAXMBUF_HEAP									_S("MaxMBufHeap")
#define DEFAULT_AGENT									_S("DefaultAgent")
#define DEFAULT_NETWORK									_S("DefaultNetwork")
#define BEARER_AVAILABILITY_CHECK_TSY					_S("BearerAvailabilityCheckTSY")

/**
Maintained for backwards compatibility.
Specifies whether to show the connection dialog.
Field type: TUint32 (Boolean) 
@deprecated v7.0 */
#define ASK_USER_BEFORE_DIAL							_S("AskUserBeforeDial")		
/** Identifier of default dial-out IAP.

Field type: TUint32
@deprecated v7.0 */
#define DIAL_OUT_IAP									_S("DialOutIAP")
#define DIAL_IN_IAP										_S("DialInIAP")
/** Identifier of (dial out) ISP in this IAP.
Field type:	TUint32. This field may not be left as NULL.
@deprecated v7.0 */
#define IAP_ISP											_S("IAPISP")
/** Time to stay online when all clients have closed.

Field type: TUint32
@deprecated v7.0 */
#define CLIENT_TIMEOUT									_S("ClientTimout")
/** Time to stay online when idle.

Field type: TUint32
@deprecated v7.0 */
#define ROUTE_TIMEOUT									_S("RouteTimeout")
/** Outgoing GPRS table.
*/
#define OUTGOING_GPRS									OUTGOING_WCDMA
/** Incoming GPRS table.
*/
#define INCOMING_GPRS									INCOMING_WCDMA
#define ECommDbBearerUnknown							KCommDbBearerUnknown
#define ECommDbBearerCSD								KCommDbBearerCSD
#define ECommDbBearerWcdma								KCommDbBearerWcdma
#define ECommDbBearerLAN								KCommDbBearerLAN
#define ECommDbBearerCdma2000							KCommDbBearerCdma2000
#define ECommDbBearerPSD								KCommDbBearerPSD
#define ECommDbBearerVirtual							KCommDbBearerVirtual
/** Avoids the need for lots of search & replace in migrations from v6.1 */
#define ECommDbBearerGPRS                               ECommDbBearerWcdma

// Columns common to all tables 
/**Unique ID assigned by the server for identification of records by the server.

Field type: TUint32 */
#define COMMDB_ID										_S("Id")			// Id of the row
/**Name of the record for easy identification by the user.

This is not present in the some tables.
Field type: text. */
#define COMMDB_NAME										_S("Name")			// Name of the row

// COMMDB_UNUSED_NAME with COMMDB_ID appended, is inserted in the name column of entries that 
// have been deleted, but are required to be inserted by ceddum, inserted and subsequently 
// deleted by ced so that the COMMDB_ID indices are preserved. Such entries may be modified
// but ideally should not be deleted as this will require all the indices to be recalculated.
_LIT(COMMDB_UNUSED_NAME, "__UNUSED_ENTRY_DO_NOT_DELETE__");

// Columns for `IAP` table
// The following macros define values for the IAP table fields.
// An IAP table allows a group of related records for service information (including service
// type), and chargecard (optional) to be identified.
/** Identifier of the dialog preference in this IAP.

Field type: TUint32. This field may be left as NULL. */
#define IAP_DIALOG_PREF									_S("DialogPref")
/** Identifier of the service in this IAP.

Field type: TUint32. This field may not be left as NULL. */
#define IAP_SERVICE										_S("IAPService")
/** Name of the service table (e.g. DIAL_OUT_ISP, OUTGOING_GPRS) 
in this IAP.

Field type: Text. This field may not be left as NULL. */
#define IAP_SERVICE_TYPE								_S("IAPServiceType")
/** Identifier of the bearer in this IAP.

Field type: TUint32. This field may be left as NULL. */
#define IAP_BEARER										_S("IAPBearer")
/** Identifier of the type of the bearer in this IAP.

Field type: TUint32. This field may be left as NULL. */
#define IAP_BEARER_TYPE									_S("IAPBearerType")
/** Identifier of the network in this IAP.

Field type: TUint32. This field may be left as NULL. */
#define IAP_NETWORK										_S("IAPNetwork")
/** Identifier of the weighting for networks in this IAP.

Field type: TUint32. This field may be left as NULL. */
#define IAP_NETWORK_WEIGHTING							_S("IAPNetworkWeighting")
/** Identifier of the location in this IAP.

Field type: TUint32. This field may be left as NULL. */
#define IAP_LOCATION									_S("Location")
//#define IAP_CHARGECARD									_S("Chargecard")

// Columns common to all bearer tables using IP and PPP
#define IF_NAME											_S("IfName")						// Interface name, e.g. "PPP" or "SLIP"

// Columns common to all service tables using IP and PPP
#define SERVICE_IF_PARAMS								_S("IfParams")						// Interface parameter string
#define SERVICE_IF_NETWORKS								_S("IfNetworks")					// Comma separated list of network protocols, e.g. "PPP"
#define SERVICE_IF_PROMPT_FOR_AUTH						_S("IfPromptForAuth")				// Prompt user for authentication name and password?
#define SERVICE_IF_AUTH_NAME							_S("IfAuthName")					// Authentication username used by PPP
#define SERVICE_IF_AUTH_PASS							_S("IfAuthPass")					// Authentication password used by PPP
#define SERVICE_IF_AUTH_RETRIES							_S("AuthRetries")					// No of times to retry authentication if it fails
#define SERVICE_IF_CALLBACK_ENABLED						_S("IfCallbackEnabled")				// Callback enabled?
#define SERVICE_IF_CALLBACK_TYPE						_S("IfCallbackType")				// Type of callback if enabled
#define SERVICE_IF_CALLBACK_INFO						_S("IfCallbackInfo")				// Info for callback request if enabled
#define SERVICE_CALLBACK_TIMEOUT						_S("CallbackTimeout")				// time to wait for callback

#define SERVICE_IP_ADDR_FROM_SERVER						_S("IpAddrFromServer")				// Get IP address from server?
#define SERVICE_IP_ADDR									_S("IpAddr")						// IP Address of Interface
#define SERVICE_IP_NETMASK								_S("IpNetMask")						// IP Netmask of Interface
#define SERVICE_IP_GATEWAY								_S("IpGateway")						// IP Address of Gateway
#define SERVICE_IP_DNS_ADDR_FROM_SERVER					_S("IpDNSAddrFromServer")			// Get DNS addresses from server?
#define SERVICE_IP_NAME_SERVER1							_S("IpNameServer1")					// IP Address of primary name server reachable through this interface
#define SERVICE_IP_NAME_SERVER2							_S("IpNameServer2")					// IP Address of secondary name server reachable through this interface

#define SERVICE_IP6_DNS_ADDR_FROM_SERVER					_S("Ip6DNSAddrFromServer")			// Get DNS addresses from server?
#define SERVICE_IP6_NAME_SERVER1							_S("Ip6NameServer1")					// IP Address of primary name server reachable through this interface
#define SERVICE_IP6_NAME_SERVER2							_S("Ip6NameServer2")					// IP Address of secondary name server reachable through this interface

#define SERVICE_ENABLE_IP_HEADER_COMP	 				_S("EnableIPHeaderComp")			// Enable IP header compression
#define SERVICE_ENABLE_LCP_EXTENSIONS					_S("EnableLCPExtension")			// Enable LCP extension
#define SERVICE_DISABLE_PLAIN_TEXT_AUTH					_S("DisablePlainTextAuth")			// Disable plain text authentication
#define SERVICE_ENABLE_SW_COMP							_S("EnableSWComp")					// Enable S/W compression

// Columns of the `DIAL_OUT_ISP` and `DIAL_IN_ISP` service tables.
// The following macros define values for the dial out/in ISP table fields.
/** Description of ISP (for use by applications etc.)

Field type: Text. This field may be left as NULL.*/
#define ISP_DESCRIPTION									_S("Description")					// text field for app to use to describe ISP
/** TCommsDbIspType value indicating ISP type, e.g. Internet, LAN, etc.

Field type: TUint32. This field may be left as NULL. */
#define ISP_TYPE										_S("Type")							// int field for ISP "type" e.g. Internet, LAN, etc

/** Default phone number.

Field type: Text. This field may be left as NULL. */
#define ISP_DEFAULT_TEL_NUM								_S("DefaultTelNum")					// The default telephone number to be used if the location does not match those below
/** Perform dialling resolution for default phone number?

Field type: TBool. This field may not be left as NULL. */
#define ISP_DIAL_RESOLUTION								_S("DialResolution")				// Perform Dialing Resolution for default phone number?
/** Use login script?

Field type: TBool. This field may not be left as NULL. */
#define ISP_USE_LOGIN_SCRIPT							_S("UseLoginScript")				// Use login script?
/** Login script (used if ISP_USE_LOGIN_SCRIPT is ETrue).

Type Text. This field may be left as NULL */
#define ISP_LOGIN_SCRIPT								_S("LoginScript")					// Login Script
/** Prompt user for username and password?

Field type: TBool. This field may not be left as NULL. */
#define ISP_PROMPT_FOR_LOGIN							_S("PromptForLogin")				// Prompt user for username and password?
/** Login name

Field type: Text. This field may be left as NULL. */
#define ISP_LOGIN_NAME									_S("LoginName")						// Login name
/** Login Password

Field type: Text. This field may be left as NULL. */
#define ISP_LOGIN_PASS									_S("LoginPass")						// Login password
/** Identifier of the chargecard used for this ISP (optional).

Field type: TUint32. This field may be left as NULL. */
#define ISP_CHARGECARD									_S("Chargecard")
/** Display post connection terminal (PCT) (without scanning script for READ command)?

Field type: TBool. This field may be left as NULL. */
#define ISP_DISPLAY_PCT									_S("DisplayPCT")					// Display PCT (do not scan script for READ)?
//#define ISP_IF_NAME									SERVICE_IF_NAME
/** Interface parameter string

Field type: Text. This field may be left as NULL. */
#define ISP_IF_PARAMS									SERVICE_IF_PARAMS
/** Comma separated list of network protocols, e.g. "IP"

Field type: Text. This field may be left as NULL. */
#define ISP_IF_NETWORKS									SERVICE_IF_NETWORKS
/** Prompt user for authentication username and password?

Field type: TBool. This field may not be left as NULL. */
#define ISP_IF_PROMPT_FOR_AUTH							SERVICE_IF_PROMPT_FOR_AUTH
/** Authentication username used by PPP

Field type: Text. This field may be left as NULL. */
#define ISP_IF_AUTH_NAME								SERVICE_IF_AUTH_NAME
/** Authentication password used by PPP

Field type: Text. This field may be left as NULL. */
#define ISP_IF_AUTH_PASS								SERVICE_IF_AUTH_PASS
/** Number of retries if authentication fails.

Field type: TUint32. This field may be left as NULL */
#define ISP_IF_AUTH_RETRIES								SERVICE_IF_AUTH_RETRIES
/** Callback enabled?

Field type: TBool. This field may be left as NULL. */
#define ISP_IF_CALLBACK_ENABLED							SERVICE_IF_CALLBACK_ENABLED
/** TCallbackAction value indicating type of callback (if enabled)

Field type: TUint32. This field may be left as NULL. */
#define ISP_IF_CALLBACK_TYPE							SERVICE_IF_CALLBACK_TYPE
/** Callback information, e.g. phone number to call back to.

Field type: 8-Bit Text. This field may be left as NULL. */
#define ISP_IF_CALLBACK_INFO							SERVICE_IF_CALLBACK_INFO
/** Time to wait for callback in microseconds (if enabled)

Field type: TUint32. This field may be left as NULL. */
#define ISP_CALLBACK_TIMEOUT							SERVICE_CALLBACK_TIMEOUT

/** Get IP address from server?

Field type: TBool. This field may not be left as NULL. */
#define ISP_IP_ADDR_FROM_SERVER							SERVICE_IP_ADDR_FROM_SERVER
/** IP address of interface

Field type: Text. This field may be left as NULL. */
#define ISP_IP_ADDR										SERVICE_IP_ADDR
/** IP net mask of interface

Field type: Text. This field may be left as NULL. */
#define ISP_IP_NETMASK									SERVICE_IP_NETMASK
/** IP address of gateway

Field type: Text. This field may be left as NULL. */
#define ISP_IP_GATEWAY									SERVICE_IP_GATEWAY
/** Get DNS addresses from server?

Field type: TBool. This field may not be left as NULL. */
#define ISP_IP_DNS_ADDR_FROM_SERVER						SERVICE_IP_DNS_ADDR_FROM_SERVER
/** IP address of primary name server

Field type: Text. This field may be left as NULL. */
#define ISP_IP_NAME_SERVER1								SERVICE_IP_NAME_SERVER1
/** IP address of secondary name server

Field type: Text. This field may be left as NULL. */
#define ISP_IP_NAME_SERVER2								SERVICE_IP_NAME_SERVER2

#define ISP_IP6_DNS_ADDR_FROM_SERVER					SERVICE_IP6_DNS_ADDR_FROM_SERVER
#define ISP_IP6_NAME_SERVER1							SERVICE_IP6_NAME_SERVER1
#define ISP_IP6_NAME_SERVER2							SERVICE_IP6_NAME_SERVER2
/** Field type: TBool. This field may be left as NULL. */
#define ISP_ENABLE_IP_HEADER_COMP		 				SERVICE_ENABLE_IP_HEADER_COMP
/** Field type: TBool. This field may be left as NULL. */
#define ISP_ENABLE_LCP_EXTENSIONS						SERVICE_ENABLE_LCP_EXTENSIONS
/** Disable plain text authentication?

Field type: TBool. This field may be left as NULL. */
#define ISP_DISABLE_PLAIN_TEXT_AUTH						SERVICE_DISABLE_PLAIN_TEXT_AUTH
/** Enable software compression (e.g. Microsoft, STAC or Predictor compression)?

Field type: TBool. This field may be left as NULL. */
#define ISP_ENABLE_SW_COMP								SERVICE_ENABLE_SW_COMP

/** The name of the bearer (RMobileCall::TMobileCallDataProtocol value)

Field type: TUint32. This field may be left as NULL. */
#define ISP_BEARER_NAME									_S("BearerName")					// Bearer Name (for GSM)
/** Connection speed if this is an ISDN, HSCSD or other connection (RMobileCall::TMobileCallDataSpeed 
value).

Field type: TUint32. This field may be left as NULL. */
#define ISP_BEARER_SPEED								_S("BearerSpeed")					// Bearer Speed (for GSM)
/** The bearer CE (RMobileCall::TMobileCallTchCoding value)

Field type: TUint32. This field may be left as NULL. */
#define ISP_BEARER_CE									_S("BearerCE")						// Bearer CE (for GSM)
/** Modem initialization string to be used when this ISP is in use. This string 
will be copied into the MODEM_ISP_INIT_STRING field by RGenericAgent.

Field type: TUint32. This field may be left as NULL. */
#define ISP_INIT_STRING									_S("InitString")					// Init string specific to ISP, to be written into the MODEM_ISP_INIT_STRING by NetDial

/** TCommsDbBearerType value indicating connection type, e.g. Standard GSM, HSCSD.

Field type: TUint32. This field may be left as NULL. */
#define ISP_BEARER_TYPE									_S("BearerType")					// HSCSD or CSD?
/** RMobileCall::TMobileCallTchCoding value specifying HSCSD channel coding.

Field type: TUint32. This field may be left as NULL. */
#define ISP_CHANNEL_CODING								_S("ChannelCoding")					// Channel coding if HSCSD connection
/** RMobileCall::TMobileCallAiur value specifying AIUR for HSCSD.

Field type: TUint32. This field may be left as NULL. */
#define ISP_AIUR										_S("AIUR")							// AIUR is HSCSD connection
/** Requested number of time slots for HSCSD.

Field type: TUint32. This field may be left as NULL. */
#define ISP_REQUESTED_TIME_SLOTS						_S("RequestedTimeSlots")			// Requested time slots if HSCSD connection
/** Maximum number of time slots for HSCSD which could be requested during this 
connection.

Field type: TUint32. This field may be left as NULL. */
#define ISP_MAXIMUM_TIME_SLOTS							_S("MaximumTimeSlots")				// Maximum time slots if HSCSD connection

/** Reserved for future use.

Field type: Text. This field may be left as NULL */
#define ISP_AUTHENTICATION								_S("Authentication")				// Authentication table/group (dial in only)

/** Enum of type RMobileCall::TMobileCallDataService.

Field type: TUint32. This field may be left as NULL. */
#define ISP_BEARER_SERVICE								_S("BearerService")
/** Enum of type RMobileCall::TMobileCallDataProtocol.

Field type: TUint32. This field may be left as NULL. */
#define ISP_BEARER_PROTOCOL								_S("BearerProtocol")
/** Enum of type RMobileCall::TMobileCallDataRLPVersion.

Field type: TUint32. This field may be left as NULL. */
#define ISP_RLP_VERSION									_S("RlpVersion")
/** Integer specifying network to MS window size.

Field type: TUint32. This field may be left as NULL. */
#define ISP_IWF_TO_MS									_S("IwfToMs")
/** Integer specifying MS to network window size.

Field type: TUint32. This field may be left as NULL. */
#define ISP_MS_TO_IWF									_S("MsToIwf")
/** Integer specifying rlp ack timeout in microseconds.

Field type: TUint32. This field may be left as NULL. */
#define ISP_ACK_TIMER									_S("AckTimer")
/** Integer specifying rlp retransmission attempts.

Field type: TUint32. This field may be left as NULL. */
#define ISP_RETRANSMISSION_ATTEMPTS						_S("RetransmissionAttempts")
/** Integer specifying resequencing period.

Field type: TUint32. This field may be left as NULL. */
#define ISP_RESEQUENCE_PERIOD							_S("ResequencePeriod")
/** Enum of type RMobileCall::TMobileCallDataV42bis.

Field type: TUint32. This field may be left as NULL. */
#define ISP_V42_COMPRESSION								_S("V42Compression")
/** Integer specifying V42bis codewords.

Field type: TUint32. This field may be left as NULL. */
#define ISP_V42_CODEWORDS								_S("V42Codewords")
/** Integer specifying V42bis maximum string length.

Field type: TUint32. This field may be left as NULL. */
#define ISP_V42_MAX_LENGTH								_S("V42MaxLength")
/** Enum of type RMobileCall::TMobileCallAsymmetry for HSCSD.

Field type: TUint32. This field may be left as NULL. */
#define ISP_ASYMMETRY									_S("Asymmetry")
/** HSCSD parameter - user init upgrade?

Field type: TBool. This field may be left as NULL. */
#define ISP_USER_INIT_UPGRADE							_S("UserInitUpgrade")
/** Use edge?

Field type: TBool. This field may be left as NULL. */
#define ISP_USE_EDGE									_S("UseEdge")

// Columns for `OUTGOING_WCDMA` and `INCOMING_WCDMA` tables.
// The following macros define values for the outgoing and incoming WCDMA table fields.
// Both tables have the same set of fields.
/** Access point name.

Field type: Text. This field may be left as NULL. */
#define GPRS_APN										_S("APN")

/** PDP (Packet Data Protocol, e.g. IP) type.

Field type: TUint32. This field may not be left as NULL. */
#define GPRS_PDP_TYPE									_S("PDPType")
/** PDP address of the phone.

Field type: Text. This field may be left as NULL. */
#define GPRS_PDP_ADDRESS								_S("PDPAddress")		// Phone IP address

/** Requested quality of service precedence class.

Field type: TUint32 from RPacketQoS::TQoSPrecedence. This field may be left as NULL. */
#define GPRS_REQ_PRECEDENCE								_S("ReqPrecedence")
/** Requested quality of service delay class.

Field type: TUint32 from RPacketQoS::TQoSDelay. This field may be left as NULL. */
#define GPRS_REQ_DELAY									_S("ReqDelay")
/** Requested quality of service reliability class.

Field type: TUint32 from RPacketQoS::TQoSReliability. This field may be left as NULL.*/
#define GPRS_REQ_RELIABILITY							_S("ReqReliability")
/** Requested quality of service peak throughput.

Field type: TUint32 from RPacketQoS::TQoSPeakThroughput. This field may be left as NULL. */
#define GPRS_REQ_PEAK_THROUGHPUT						_S("ReqPeakThroughput")
/** Requested quality of service mean throughput class.

Field type: TUint32 from RPacketQoS::TQoSMeanThroughput. This field may be left as NULL. */
#define GPRS_REQ_MEAN_THROUGHPUT						_S("ReqMeanThroughput")

/** Minimum quality of service precedence class.

Field type: TUint32 from RPacketQoS::TQoSPrecedence. This field may be left as NULL. */
#define GPRS_MIN_PRECEDENCE								_S("MinPrecedence")
/** Minimum quality of service delay class.

Field type: TUint32 from RPacketQoS::TQoSDelay. This field may be left as NULL. */
#define GPRS_MIN_DELAY									_S("MinDelay")
/** Minimum quality of service reliability class.
		
Field type: TUint32 from RPacketQoS::TQoSReliability. This field may be left as NULL.*/
#define GPRS_MIN_RELIABILITY							_S("MinReliability")
/** Minimum quality of service peak throughput class.

Field type: TUint32 from RPacketQoS::TQoSMeanThroughput. This field may be left as NULL. */
#define GPRS_MIN_PEAK_THROUGHPUT						_S("MinPeakThroughput")
/** Minimum quality of service mean throughput class.

Field type: TUint32 from RPacketQoS::TQoSMeanThroughput. This field may be left as NULL. */
#define GPRS_MIN_MEAN_THROUGHPUT						_S("MinMeanThroughput")

/** Whether data compression is on.

Field type: TBool. This field may be left as NULL. */
#define GPRS_DATA_COMPRESSION							_S("DataCompression")
/** Whether IP header compression is on.

Field type: TBool. This field may be left as NULL. */
#define GPRS_HEADER_COMPRESSION							_S("HeaderCompression")

/** Whether use of anonymous access is on.

Field type: TBool. This field may be left as NULL. */
#define GPRS_ANONYMOUS_ACCESS							_S("AnonymousAccess")
#define GPRS_USE_EDGE									_S("GprsUseEdge")

//#define GPRS_IF_NAME									SERVICE_IF_NAME
/** Interface parameter string.

Field type: Text. This field may be left as NULL. */
#define GPRS_IF_PARAMS									SERVICE_IF_PARAMS
/** Comma separated list of network protocols, e.g. "PPP".

Field type: Text. This field may be left as NULL. */
#define GPRS_IF_NETWORKS								SERVICE_IF_NETWORKS
/** Whether to prompt user for authentication username and password.

Field type: TBool. This field may not be left as NULL. */
#define GPRS_IF_PROMPT_FOR_AUTH							SERVICE_IF_PROMPT_FOR_AUTH
/** Authentication username used by PPP.

Field type: Text. This field may be left as NULL. */
#define GPRS_IF_AUTH_NAME								SERVICE_IF_AUTH_NAME
/** Authentication password used by PPP.

Field type: Text. This field may be left as NULL. */
#define GPRS_IF_AUTH_PASS								SERVICE_IF_AUTH_PASS
/** Number of times to retry authentication if it fails.

Field type: TUint32. This field may be left as NULL. */
#define GPRS_IF_AUTH_RETRIES							SERVICE_IF_AUTH_RETRIES

/** IP net mask of interface.

Field type: Text. This field may be left as NULL */
#define GPRS_IP_NETMASK									SERVICE_IP_NETMASK
/** IP address of the gateway.

Field type: Text. This field may be left as NULL. */
#define GPRS_IP_GATEWAY									SERVICE_IP_GATEWAY
/** Whether to get IP addresses (for the Symbian phone) from the server.

Field type: TBool. This field may not be left as NULL. */
#define GPRS_IP_ADDR_FROM_SERVER						SERVICE_IP_ADDR_FROM_SERVER
/** IP address of the Symbian phone

Field type: Text. This field may be left as NULL. */
#define GPRS_IP_ADDR									SERVICE_IP_ADDR						// EPOC IP address
/** Whether to get DNS addresses from the server.

Field type: TBool. This field may not be left as NULL. */
#define GPRS_IP_DNS_ADDR_FROM_SERVER					SERVICE_IP_DNS_ADDR_FROM_SERVER
/** IP address of the primary name server.

Field type: Text. This field may be left as NULL. */
#define GPRS_IP_NAME_SERVER1							SERVICE_IP_NAME_SERVER1
/** IP address of the secondary name server.

Field type: Text. This field may be left as NULL. */
#define GPRS_IP_NAME_SERVER2							SERVICE_IP_NAME_SERVER2

#define GPRS_IP6_DNS_ADDR_FROM_SERVER					SERVICE_IP6_DNS_ADDR_FROM_SERVER
#define GPRS_IP6_NAME_SERVER1							SERVICE_IP6_NAME_SERVER1
#define GPRS_IP6_NAME_SERVER2							SERVICE_IP6_NAME_SERVER2

/** Whether to enable LCP extensions.

Field type: TBool. This field may be left as NULL. */
#define GPRS_ENABLE_LCP_EXTENSIONS						SERVICE_ENABLE_LCP_EXTENSIONS
/** Whether to disable plain text authentication.

Field type: TBool. This field may be left as NULL. */
#define GPRS_DISABLE_PLAIN_TEXT_AUTH					SERVICE_DISABLE_PLAIN_TEXT_AUTH

/** Service supports Internet only, WAP only or both.

Field type: TUint32. This field may be left as NULL. */
#define	GPRS_AP_TYPE									_S("GprsAccessPointType")

/** If the requested QOS can not be satisfied warn the user after this time in microseconds. 
Set to 0xffffffff to disable.

Field type: TUint32. This field may be left as NULL. */
#define GPRS_QOS_WARNING_TIMEOUT						_S("QosWarningTimeout")

// 
// Columns of the `LAN_SERVICE` Table.
// 
#define LAN_IF_NETWORKS									SERVICE_IF_NETWORKS
#define LAN_IP_NETMASK									SERVICE_IP_NETMASK
#define LAN_IP_GATEWAY									SERVICE_IP_GATEWAY
#define LAN_IP_ADDR_FROM_SERVER							SERVICE_IP_ADDR_FROM_SERVER
#define LAN_IP_ADDR										SERVICE_IP_ADDR
#define LAN_IP_DNS_ADDR_FROM_SERVER						SERVICE_IP_DNS_ADDR_FROM_SERVER
#define LAN_IP_NAME_SERVER1								SERVICE_IP_NAME_SERVER1
#define LAN_IP_NAME_SERVER2								SERVICE_IP_NAME_SERVER2

#define LAN_IP6_DNS_ADDR_FROM_SERVER					SERVICE_IP6_DNS_ADDR_FROM_SERVER
#define LAN_IP6_NAME_SERVER1							SERVICE_IP6_NAME_SERVER1
#define LAN_IP6_NAME_SERVER2							SERVICE_IP6_NAME_SERVER2

/** Columns of all bearer tables */
#define AGENT_NAME								_S("Agent")
#define LAST_SOCKET_ACTIVITY_TIMEOUT				_S("LastSocketActivityTimeout")
#define LAST_SESSION_CLOSED_TIMEOUT				_S("LastSessionClosedTimeout")
#define LAST_SOCKET_CLOSED_TIMEOUT				_S("LastSocketClosedTimeout")

// Columns of the `MODEM BEARER` table.
// The following macros define values for the Modem Bearer table fields.
// Note that in v7.0s, this table changed its name from MODEM to MODEM_BEARER.
// In v6.1 there can be only a single record in this table.
/** Agent identifier.

Field type: TUint32. This field may be left as NULL. */
#define MODEM_AGENT										AGENT_NAME
/** NIF name.

Field type: Text. This field may be left as NULL. */
#define MODEM_NIF_NAME									IF_NAME
/** Comm port name.

Field type: Text. This field may be left as NULL. */
#define MODEM_PORT_NAME									_S("PortName")
/** The modem control channel port name.

Field type: Text. This field may be left as NULL. */
#define MODEM_CONTROL_CHANNEL_PORT_NAME					_S("ControlChannelPortName")
/** TSY name.

Field type: Text. This field may be left as NULL. */
#define MODEM_TSY_NAME									_S("TSYName")
/** CSY name.

Field type: Text. This field may be left as NULL. */
#define MODEM_CSY_NAME									_S("CSYName")
/** Data bits (TDataBits value).

Field type: TUint8. This field may not be left as NULL. */
#define	MODEM_DATA_BITS									_S("DataBits")						// Data Bits to use for ISP or Modem
/** Stop bits.

This is a TStopBits value.

Field type: TUint8. This field may not be left as NULL. */
#define	MODEM_STOP_BITS									_S("StopBits")						// Stop Bits to use for ISP or Modem
/** Parity.

This is a TParity value.

Field type: TUint8. This field may not be left as NULL. */
#define	MODEM_PARITY									_S("Parity")						// Parity Type to use for ISP or Modem
/** Baud rate.

This is a TBps value.

Field type: TUint32. This field may not be left as NULL. */
#define MODEM_RATE										_S("Rate")
/** Handshaking.

Field type: TUint32. This field may be left as NULL. */
#define MODEM_HANDSHAKING								_S("Handshaking")
/** Special rate.

Field type: TUint32. This field may be left as NULL. */
#define MODEM_SPECIAL_RATE								_S("SpecialRate")
/** Xon character.

Field type: TUint8. This field may be left as NULL. */
#define MODEM_XON_CHAR									_S("XonChar")
/** Xoff Character.

Field type: TUint8. This field may be left as NULL. */
#define MODEM_XOFF_CHAR									_S("XoffChar")

/** Preferred fax class.

This is a TFaxClass value.

Field type: TUint8. This field may not be left as NULL. */
#define MODEM_FAX_CLASS_PREF							_S("FaxClassPref")
/** Preferred speaker mode.

This is a TCommsDbModemSpeakerSetting value.

Field type: TUint8. This field may not be left as NULL. */
#define MODEM_SPEAKER_PREF								_S("SpeakerPref")
/** Preferred speaker volume.

This is a TCommsDbModemSpeakerVolume value.

Field type: TUint8. This field may not be left as NULL. */
#define MODEM_SPEAKER_VOL_PREF							_S("SpeakerVolPref")

/** General modem initialisation string

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_MODEM_INIT_STRING							_S("ModemInitString")
/** Data initialisation string

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_DATA_INIT_STRING							_S("DataInitString")
/** Fax initialisation string.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_FAX_INIT_STRING							_S("FaxInitString")
/** ISP Initialisation string. This field is written from the ISP_INIT_STRING.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_ISP_INIT_STRING							_S("IspInitString")				// To be written by NetDial from ISP_INIT_STRING.  Should not be accessed by user.

/** Command to modify the pause created during dialling using the comma character 
(',')

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_DIAL_PAUSE_LENGTH							_S("DialPauseLength")
/** Command to set the time out the modem uses when establishing a link before 
giving up and returning to command mode.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_CARRIER_TIMEOUT							_S("CarrierTimeout")
/** Command to set the number of rings before the modem auto answers.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_AUTO_ANSWER_RING_COUNT					_S("AutoAnswerRingCount")
/** Command to set the modem speaker volume to low.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_SPEAKER_VOL_CONTROL_LOW					_S("SpeakerVolContorlLow")
/** Command to set the modem speaker volume to medium.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_SPEAKER_VOL_CONTROL_MEDIUM				_S("SpeakerVolControlMedium")
/** Command to set the modem speaker volume to high.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_SPEAKER_VOL_CONTROL_HIGH					_S("SpeakerVolControlHigh")
/** Command to set the modem speaker off.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_SPEAKER_ALWAYS_OFF						_S("SpeakerAlwaysOff")
/** Command to set the modem speaker on until the carrier.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_SPEAKER_ON_UNTIL_CARRIER					_S("SpeakerOnUntilCarrier")
/** Command to set the modem speaker on

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_SPEAKER_ALWAYS_ON							_S("SpeakerAlwaysOn")
/** Command to set the modem speaker on except during dialling.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_SPEAKER_ON_AFTER_DIAL_UNTIL_CARRIER		_S("SpeakerOnAfterUntilCarrier")
/** The dial command modifier to wait for dial tone.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_DIAL_TONE_WAIT_MODIFIER					_S("DialToneWaitModifier")
/** Disable busy and dial tone detection.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_CALL_PROGRESS_1							_S("CallProgress1")					// Dialtone & busy detection disabled, result codes 0-5,10
/** Dial tone detection enabled, busy detection disabled.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_CALL_PROGRESS_2							_S("CallProgress2")					// Dialtone detection enabled & busy detection disabled, result codes 0-6,10
/** Dial tone detection disabled, busy detection enabled.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_CALL_PROGRESS_3							_S("CallProgress3")					// Dialtone detection disabled , but busy detection enabled, result codes 0-5,7,10
/** Dial tone and busy detection enabled.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_CALL_PROGRESS_4							_S("CallProgress4")					// Dialtone detection & busy detection enabled, result codes 0-7,10
/** Switch echo mode off.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_ECHO_OFF									_S("EchoOff")
/** Switch verbose mode on.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_VERBOSE_TEXT								_S("VerboseText")
/** Switch quiet mode on.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_QUIET_ON									_S("QuietOn")
/** Switch quiet mode off.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_QUIET_OFF									_S("QuietOff")
/** Dial command modifier to return to command mode after dialling.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_DIAL_COMMAND_STATE_MODIFIER				_S("DialCommandStateModifier")
/** Enter on-line mode from on-line command mode.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_ON_LINE									_S("OnLine")
/** Reset the modem configuration.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_RESET_CONFIGURATION						_S("ResetConfiguration")
/** Return the modem configuration to its factory defaults.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_RETURN_TO_FACTORY_DEFS					_S("ReturnToFactoryDefs")
/** Command the modem to only assert DCD when a carrier is actually detected, i.e. 
while the link is up.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_DCD_ON_DURING_LINK						_S("DCDOnDuringLink")
/** Command the modem to hang up the current call when the DTE drops the DTR line.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_DTR_HANG_UP								_S("DTRHangUp")
/** Command the modem to always assert DSR.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_DSR_ALWAYS_ON								_S("DSRAlwaysOn")
/** Command the modem to use RTS/CTS flow control.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_RTS_CTS_HANDSHAKE							_S("RTSCTSHandshake")
/** Command the modem to use software flow control.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_XON_XOFF_HANDSHAKE						_S("XonXoffHandshake")
/** The character used by the DTE to return to command mode from on-line mode.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_ESCAPE_CHARACTER							_S("EscapeCharacter")
/** Command the modem to use a particular escape sequence guard period.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_ESCAPE_GUARD_PERIOD						_S("EscapeGuardPeriod")
/** Ask the modem which fax modes are supported.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_FAX_CLASS_INTERROGATE						_S("FaxClassInterrogate")
/** Set the fax mode.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_FAX_CLASS									_S("FaxClass")

/** Modem response when no dial tone is detected.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_NO_DIAL_TONE								_S("NoDialTone")
/** Modem response when a busy tone is detected.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_BUSY										_S("Busy")
/** Modem response when no answer is detected.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_NO_ANSWER									_S("NoAnswer")
/** Carrier report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_CARRIER									_S("Carrier")
/** Connection report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_CONNECT									_S("Connect")
/** Compression Class 5 report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_COMPRESSION_CLASS_5						_S("CompressionClass5")
/** Compression V.42 bis report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_COMPRESSION_V42BIS						_S("CompressionV42bis")
/** No compression report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_COMPRESSION_NONE							_S("CompressionNone")
/** LAPD protocol report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_PROTOCOL_LAPD								_S("ProtocolLAPD")
/** ALT protocol report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_PROTOCOL_ALT								_S("ProtocolALT")
/** ALT-CELLULAR report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_PROTOCOL_ALTCELLULAR						_S("ProtocolALTCELLULAR")
/** No protocol report message.

Field type: 8-Bit Text. This field may be left as NULL. */
#define MODEM_PROTOCOL_NONE								_S("ProtocolNone")

/** Phone number of messsage centre.

Field type: TUint16. This field may be left as NULL. */
#define MODEM_MESSAGE_CENTRE_NUMBER						_S("MessageCentreNumber")
/** Validity period for SMS in minutes.

Field type: TUint32. This field may be left as NULL. */
#define MODEM_MESSAGE_VALIDITY_PERIOD					_S("MessageValidityPeriod")
/** Whether to produce an SMS deilvery report.

Field type: TBool. This field may be left as NULL. */
#define MODEM_MESSAGE_DELIVERY_REPORT					_S("MessageDeliveryReport")
/** Minimum signal level.

Field type: TUint32. This field may not be left as NULL. */
#define MODEM_MIN_SIGNAL_LEVEL							_S("MinimumSignalLevel")
/** SIR settings.
Field type: TUint32. This field may be left as NULL. */
#define MODEM_SIR_SETTINGS								_S("SIRSettings")
#define MODEM_COMM_ROLE									_S("CommRole")

// Columns of the 'LAN Bearer' table 
#define LAN_BEARER_AGENT								AGENT_NAME
#define LAN_BEARER_NIF_NAME								IF_NAME
#define LAN_BEARER_LDD_NAME								_S("LDDName")
#define LAN_BEARER_PDD_NAME								_S("PDDName")

// Columns of the `LOCATION` table.
// The following macros define values for the Location table fields.
// Note that in v6.1 there can be only a single record in this table.
/** International prefix code.

Field type: Text. This field may be left as NULL. */
#define LOCATION_INTL_PREFIX_CODE						_S("IntlPrefixCode")
/** National prefix code.

Field type: Text. This field may be left as NULL. */
#define LOCATION_NAT_PREFIX_CODE						_S("NatPrefixCode")
/** National code.

Field type: Text. This field may be left as NULL. */
#define LOCATION_NAT_CODE								_S("NatCode")
/** Area code.

Field type: Text. This field may be left as NULL. */
#define LOCATION_AREA_CODE								_S("AreaCode")
/** Number to dial for an outside line.

Field type: Text. This field may be left as NULL. */
#define LOCATION_DIAL_OUT_CODE							_S("DialOutCode")
/** Code to dial to disable call waiting facility.

Field type: Text. This field may be left as NULL. */
#define LOCATION_DISABLE_CALL_WAITING_CODE				_S("DisableCallWaitingCode")
/** Mobile phone?

Field type: TBool. This field may not be left as NULL. */
#define LOCATION_MOBILE									_S("Mobile")
/** Use pulse dialling?

Field type: TBool. This field may not be left as NULL. */
#define LOCATION_USE_PULSE_DIAL							_S("UsePulseDial")
/** Wait for the dial tone?

Field type: TBool. This field may not be left as NULL. */
#define LOCATION_WAIT_FOR_DIAL_TONE						_S("WaitForDialTone")
/** Pause time after dial out.

Field type: TUint32. This field may not be left as NULL. */
#define LOCATION_PAUSE_AFTER_DIAL_OUT					_S("PauseAfterDialout")

// Columns of the `CHARGECARD` table 
// The following macros define values for the Chargecard table fields.
/** Account number.

Field type: Text. This field may be left as NULL. */
#define CHARGECARD_ACCOUNT_NUMBER						_S("AccountNumber")
/** PIN number.

Field type: Text. This field may be left as NULL. */
#define CHARGECARD_PIN									_S("Pin")
/** Order of dialling account number, PIN and phone number for local calls.

Field type: Text. This field may be left as NULL. */
#define CHARGECARD_LOCAL_RULE							_S("LocalRule")
/** Order of dialling account number, PIN and phone number for national calls.

Field type: Text. This field may be left as NULL. */
#define CHARGECARD_NAT_RULE								_S("NatRule")
/** Order of dialling account number, PIN and phone number for international calls.

Field type: Text. This field may be left as NULL. */
#define CHARGECARD_INTL_RULE							_S("IntlRule")

// Columns of the `PROXIES` table.
// The following macros define values for the Proxies table fields.
/** Identifier of the associated ISP record.

Field type: TUint32. This field may not be left as NULL.*/
#define PROXY_ISP										_S("ISP")							// ISP with which these proxies are associated
/** The table from which the PROXY_ISP has been taken. 

This is necessary as GPRS records as well as ISP records can have proxy settings 
associated with them. 

If this field is read and its length is zero, the value DIAL_OUT_ISP is returned, 
as it is assumed that any client that has not written this field is assuming 
that proxies are only available to the dial out ISP and not other service 
types.

Field type: Text. This field may be left as NULL. */
#define PROXY_SERVICE_TYPE								_S("ProxyServiceType")
/** Use proxy server?

Field type: TBool. This field may not be left as NULL. */
#define PROXY_USE_PROXY_SERVER							_S("UseProxyServer")
/** Name of the host.

Field type: Long Text. This field may be left as NULL. */
#define PROXY_SERVER_NAME								_S("ProxyServerName")				// Name of the proxy server
/** Name of the protocol for which this proxy can be used.

Field type: Text. This field may not be left as NULL. */
#define PROXY_PROTOCOL_NAME								_S("ProtocolName")
/** Port number.

Field type: TUint32. This field may be left as NULL. */
#define PROXY_PORT_NUMBER								_S("PortNumber")
/** Semi-colon separated list of the addresses for which the proxy server should 
not be used.

Field type: Long Text. This field may be left as NULL. */
#define PROXY_EXCEPTIONS								_S("Exceptions")

// Columns of the `WAP_ACCESS_POINT` table. The following macros define values 
// for the WAP access point table fields.
/** Text string indicating the name of the table from which to read the bearer 
information.

This can be WAP_IP_BEARER or WAP_SMS_BEARER.

Field type: Text. This field may not be left as NULL. */
#define WAP_CURRENT_BEARER								_S("CurrentBearer")
/** WAP start page URL.

Field type: Text. This field may be left as NULL. */
#define WAP_START_PAGE									_S("StartPage")

// Columns common to the `WAP_IP_BEARER` and `WAP_SMS_BEARER` tables.
// The following macros define values for the WAP IP bearer and WAP SMS bearer table fields.
// These tables have no COMMDB_NAME field. 
/** ID of the the WAP Access Point record to which this bearer information refers.

Field type: TUint32. This field may not be left as NULL.*/
#define WAP_ACCESS_POINT_ID								_S("AccessPointId")
/** WAP gateway address: an IP address or phone number.

Field type: Text. This field may be left as NULL. */
#define WAP_GATEWAY_ADDRESS								_S("GatewayAddress")
/** Whether connection-oriented or connectionless API should be used.

This is a TCommsDbWapWspOption value.

Field type: TUint8. This field may be left as NULL. */
#define WAP_WSP_OPTION									_S("WSPOption")							// Connectionless or Connection-oriented
/** Attempt secure WTLS connection to the gateway.

Field type: TBool. This field may be left as NULL. */
#define WAP_SECURITY									_S("Security")

// Additional Columns of the `WAP_IP_BEARER` table.
/** Identifier of a record in the IAP table to be used.

Field type: TUint32. This field may be left as NULL. */
#define WAP_IAP											_S("IAP")								
/** Proxy port number. Required for WAP2.0 only.

Field type: TUint32. This field may not be left as NULL. */
#define WAP_PROXY_PORT									_S("ProxyPortNumber")
/** Proxy login name. Required for WAP2.0 only.

Field type: Text. This field may be left as NULL. */
#define WAP_PROXY_LOGIN_NAME							_S("ProxyLogin")
/** Proxy login password. Required for WAP2.0 only.

Field type: Text. This field may be left as NULL. */
#define WAP_PROXY_LOGIN_PASS							_S("ProxyPassword")

// Additional Column of the `WAP_SMS_BEARER` table.
/** Service Centre Address.

Field type: Text. This field may be left as NULL. */
#define WAP_SERVICE_CENTRE_ADDRESS						_S("ServiceCentreAddress")

// The following macros define values for the Bluetooth device table fields.
// These tables have no COMMDB_NAME field.

// Column common to the `BT_DEVICE_TABLE` and `BT_SECURITY_TABLE` tables.
/** Bluetooth device address.

Field type: 8-bit Text. This field may not be left as NULL. */
#define BT_DEV_ADD										_S("DeviceAddress")

// Additional Columns of the `BT_DEVICE_TABLE` table.
/** Bluetooth device default name.

Field type: Long text. This field may be left as NULL */
#define BT_DEV_DFLT_NAME								_S("DeviceDefaultName")
/** Bluetooth device friendly name.

Field type: Long text. This field may be left as NULL */
#define BT_DEV_FRIENDLY_NAME							_S("DeviceFriendlyName")
/** Bluetooth device class.

Field type: TUint32. This field may be left as NULL */
#define BT_DEVICE_CLASS									_S("DeviceClass")
/** Bluetooth Link key.

Field type: 8-bit Text. This field may be left as NULL */
#define BT_LINKKEY										_S("DeviceLinkKey")
/** Bluetooth device state.

Field type: TUint32. This field may not be left as NULL. */
#define BT_DEV_STATE									_S("DeviceStatus")
/** Bluetooth device global security setting.

Field type: TUint32. This field may be left as NULL */
#define BT_DEVICE_GLOBAL_SECURITY						_S("DeviceGlobalSecurity")
/** Bluetooth page scan repetition mode.

Field type: TUint32. This field may be left as NULL */
#define BT_PAGE_SCAN_REP_MODE							_S("DevicePageScanRepMode") 
/** Field type: TUint32. This field may be left as NULL */
#define BT_PAGE_SCAN_PERIOD_MODE						_S("DevicePageScanPeriodMode") 
/** Field type: TUint32. This field may be left as NULL */
#define BT_PAGE_SCAN_MODE								_S("DevicePageScanMode") 
/** Internal*/
#define BT_SPARE										_S("DeviceSpareInfo") 
/** Bluetooth clock offset.

Field type: TUint32. This field may be left as NULL */
#define BT_CLK_OFFSET									_S("DeviceClkOffset") 
/** Bluetooth class of device.

Field type: TUint32. This field may be left as NULL */
#define BT_COD											_S("DeviceClassOfDevice") 

// Additional Columns of the `WAP_SMS_BEARER` table.
/** Bluetooth security UID.

Field type: TUint32. This field may be left as NULL */
#define BT_SEC_UID										_S("BTSecurityUID")
/** Bluetooth security device.

Field type: TUint32. This field may be left as NULL */
#define BT_SEC_DEVICE_SECURITY							_S("BTSecurityDevice")

// Columns of the `BT_DEFAULT_TABLE` table.
// The following macros define values for the Bluetooth Default table fields.
// This table has no COMMDB_NAME field.
/** Bluetooth default service name.

Field type: Text. This field may be left as NULL. */
#define BT_DFLT_SER_NAME								_S("DefaultServicename")
/** Bluetooth default service ID.

Field type: TUint32. This field may not be left as NULL. */
#define BT_DFLT_SER_UUID								_S("DefaultServiceUID")
/** Bluetooth default device address.

Field type: 8-bit Text. This field may not be left as NULL. */
#define BT_DFLT_DEV_ADD									_S("DefaultDeviceAddress")
/** Bluetooth default virtual port number.

Field type: TUint32. This field may not be left as NULL. */
#define BT_DFLT_VIRTUAL_PORT    						_S("DefaultVirtualPort")
/** Bluetooth default security level.

Field type: TUint8. This field may be left as NULL */
#define BT_DFLT_SECURITY_LEVEL  						_S("DefaultSecurityLevel")


// Columns of the BT Persistance Table 
// The following macros define values for the Bluetooth Persist table fields.
// This table has no COMMDB_NAME field.
// These items are all internal and not intended for use.
#define BT_PERSIST_COD									_S("ClassOfDevice")
#define BT_PERSIST_PAGE_TIMEOUT							_S("PageTimeout")
#define BT_PERSIST_PAGE_SCAN_INTERVAL					_S("PageScanInterval")
#define BT_PERSIST_PAGE_SCAN_WINDOW						_S("PageScanWindow")
#define BT_PERSIST_INQUIRY_SCAN_INTERVAL				_S("InquiryScanInterval")
#define BT_PERSIST_INQUIRY_SCAN_WINDOW					_S("InquiryScanWindow")
#define BT_PERSIST_HOLD_MODE_ACTIVITY					_S("HoldModeActivity")
#define BT_PERSIST_SCO_FLOW_CONTROL						_S("SCOFlowControl")
#define BT_PERSIST_PAGE_SCAN_PERIOD						_S("PageScanPeriod")
#define BT_PERSIST_PAGE_SCAN_MODE						_S("PageScanMode")
#define BT_PERSIST_POWER_SETTINGS						_S("PowerSettings")
#define BT_PERSIST_SCAN									_S("Scan")
#define BT_PERSIST_LOCAL_NAME							_S("LocalName")
#define BT_PERSIST_IAC_LAP								_S("IacLap")
#define BT_PERSIST_STATE								_S("PersistState")


// Columns for `SS_PROTO_TABLE` table 
// The following macros define values for the SS Proto table fields.
// This table has no COMMDB_NAME field.
/** Secure Sockets protocol name.

Field type: Text. This field may not be left as NULL. */
#define SS_PROTO_NAME									_S("ProtocolName")
/** Secure Sockets protocol library.

Field type: Text. This field may not be left as NULL. */
#define SS_PROTO_LIBRARY								_S("ProtoLibrary")

// Columns of the `DEFAULT_GPRS` table.
// The following macros define values for the Default GPRS fields.
// GPRS Phase 1 requires that a default PDP (Packet Data Protocol, e.g. IP4)
// context configuration for GPRS is stored for use when no other configuration
// information is specified for a context by the terminal. This table is
// provided for this purpose. Defaults can be used when the device
// is used as a GPRS modem with an external device that does not specify GPRS
// parameters for the  connection.In release v6.1 the enums that are now in
// RPacketContext and RPacketQoS were in RGprsContext.The following macros
// define the fields for  the  table. The description is followed by the field
// type, and whether the specified field may be left null or not.
/** Specifies usage of this default.

Field type: TUint32. This field may be left as NULL */
#define DEFAULT_GPRS_USAGE								_S("Usage")
/** Default access point name.

Field type: Text. This field may not be left as NULL. */
#define DEFAULT_GPRS_APN								_S("APN")

/** Default PDP type (e.g. IP4).

The enum RPacketContext::TProtocolType defines valid values for this field.

Field type: TUint32. This field may not be left as NULL. */
#define DEFAULT_GPRS_PDP_TYPE							_S("PDPType")
/** Default PDP address.

Field type: Text. This field may not be left as NULL. */
#define DEFAULT_GPRS_PDP_ADDRESS						_S("PDPAddress")

/** Default quality of service precedence class.

Values for this are defined by the enum RPacketQoS::TQoSPrecedence.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_PRECEDENCE							_S("Precedence")

/** Default quality of service delay class.

Values for this are defined by the enum RPacketQoS::TQoSDelay.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_DELAY								_S("Delay")

/** Default quality of service reliability class.

Values for this are defined by the enum RPacketQoS::TQoSReliability.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_RELIABILITY						_S("Reliability")

/** Default quality of service peak throughput class.

Values for this are defined by the enum RPacketQoS::TQoSPeakThroughput.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_PEAK_THROUGHPUT					_S("PeakThroughput")

/** Default quality of service mean throughput class.

Values for this are defined by the enum RPacketQoS::TQoSMeanThroughput.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_MEAN_THROUGHPUT					_S("MeanThroughput")

#define DEFAULT_GPRS_MIN_PRECEDENCE						_S("MinPrecedence")

/** Minimum quality of service delay class.

Values for this are defined by the enum RPacketQoS::TQoSDelay.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_MIN_DELAY							_S("MinDelay")

/** Default minimum quality of service reliability class.

Values for this are defined by the enum RPacketQoS::TQoSReliability.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_MIN_RELIABILITY					_S("MinReliability")

/** Default minimum quality of service peak throughput class.

Values for this are defined by the enum RPacketQoS::TQoSMeanThroughput.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_MIN_PEAK_THROUGHPUT				_S("MinPeakThroughput")

/** Default minimum quality of service mean throughput class.

Values for this are defined by the enum RPacketQoS::TQoSMeanThroughput.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_GPRS_MIN_MEAN_THROUGHPUT				_S("MinMeanThroughput")

/** Default value for whether data compression is on.

Field type: TBool. This field may be left as NULL. */
#define DEFAULT_GPRS_DATA_COMPRESSION					_S("DataCompression")

/** Default value for whether IP header compression is on.

Field type: TBool. This field may be left as NULL. */
#define DEFAULT_GPRS_HEADER_COMPRESSION					_S("HeaderCompression")

/** Default value for whether use of anonymous access is on.

Field type: TBool. This field may be left as NULL. */
#define DEFAULT_GPRS_ANONYMOUS_ACCESS					_S("AnonymousAccess")
/** Field type: TBool. This field may be left as NULL */
#define DEFAULT_GPRS_USE_EDGE							_S("GprsUseEdge")

// Columns of the `AGENT_LOOKUP` table 
// The following macros define values for the Agent Lookup fields. 
// This table has no COMMDB_NAME field.</para>
/** The Agent's name.

Field type: Text. This field may not be left as NULL. */
#define	AGENT_FRIENDLY_NAME								_S("AgentFriendlyName")
/** The internal file location of the agent.

Field type: Text. This field may not be left as NULL. */
#define AGENT_FILENAME									_S("AgentFilename")

// Columns of the `CDMA2000_PACKET_SERVICE_TABLE` 
// The following macros define values for the CDMA 2000 Packet Service fields.
/** IWF name.

Field type:Text. This field may be left as NULL */
#define CDMA_IWF_NAME									_S("IwfName")
/** Mask indicating valid service options.

Field type:	TUint32 from RPacketContext::TServiceOption. This field may not be left as NULL */
#define CDMA_SERVICE_OPTION								_S("ServiceOption")

/** PDP type. (IPv4 or IPv6).

Field type:TUint32 from RPacketContext::TProtocolType. This field may not be left as NULL. */
#define CDMA_PDP_TYPE									_S("PdpType")
/** PDP address of phone.

Field type:Text. This field may be left as NULL */
#define CDMA_PDP_ADDRESS								_S("PdpAddress")

/** Requested forward priority.

Field type:TUint32 from RPacketQoS::TQoSLinkPriority. This field may be left as NULL */
#define CDMA_REQ_FWD_PRIORITY							_S("ReqFwdPriority")
/** Requested reverse priority.

Field type:TUint32 from RPacketQoS::TQoSLinkPriority. This field may be left as NULL */
#define CDMA_REQ_REV_PRIORITY							_S("ReqRevPriority")
/** Requested forward bitrate.

Field type:TUint32 from RPacketQoS::TQoSDataRate. This field may be left as NULL */
#define CDMA_REQ_FWD_BITRATE							_S("ReqFwdBitrate")
/** Requested reverse bitrate.

Field type: TUint32 from RPacketQoS::TQoSDataRate. This field may be left as NULL */
#define CDMA_REQ_REV_BITRATE							_S("ReqRevBitrate")
/** Requested forward frame loss rate.

Field type:TUint32 from RPacketQoS::TQoSDataLoss. This field may be left as NULL */
#define CDMA_REQ_FWD_LOSS								_S("ReqFwdLoss")
/** Requested reverse frame loss rate.

Field type: TUint32 from RPacketQoS::TQoSDataLoss. This field may be left as NULL */
#define CDMA_REQ_REV_LOSS								_S("ReqRevLoss")
/** Requested forward delay.

Field type: TUint32 from RPacketQoS::TQoSDelay. This field may be left as NULL */
#define CDMA_REQ_FWD_MAXDELAY							_S("ReqFwdMaxdelay")
/** Requested reverse delay.

Field type:TUint32 from RPacketQoS::TQoSDelay. This field may be left as NULL */
#define CDMA_REQ_REV_MAXDELAY							_S("ReqRevMaxdelay")
/** Minimum acceptable forward bitrate.

Field type: TUint32 from RPacketQoS::TQoSDataRate. This field may be left as NULL */
#define CDMA_MIN_FWD_BITRATE							_S("MinFwdBitrate")
/** Minimum acceptable reverse bitrate.

Field type: TUint32 from RPacketQoS::TQoSDataRate. This field may be left as NULL */
#define CDMA_MIN_REV_BITRATE							_S("MinRevBitrate")
/** Maximum acceptable forward frame loss rate.

Field type:TUint32from RPacketQoS::TQoSDataLoss. This field may be left as NULL */
#define CDMA_ACCPT_FWD_LOSS								_S("AccptFwdLoss")
/** Maximum acceptable forward frame loss rate.

Field type:TUint32 from RPacketQoS::TQoSDataLoss. This field may be left as NULL */
#define CDMA_ACCPT_REV_LOSS								_S("AccptRevLoss")

/** Maximum acceptable forward delay.

Field type:TUint32 from RPacketQoS::TQoSDelay. This field may be left as NULL. */
#define CDMA_ACCPT_FWD_MAXDELAY							_S("AccptFwdMaxdelay")
/** Maximum acceptable reverse delay.

Field type: TUint32 from RPacketQoS::TQoSDelay. This field may be left as NULL */
#define CDMA_ACCPT_REV_MAXDELAY							_S("AccptRevMaxdelay")

/** Data compression on?

Field type: TBool. This field may be left as NULL */
#define CDMA_DATA_COMPRESSION							_S("DataCompression")
/** IP header compression on?

Field type: TBool. This field may be left as NULL */
#define CDMA_HEADER_COMPRESSION							_S("HeaderCompression")

/** Use anonymous access on?

Field type:TBool. This field may be left as NULL */
#define CDMA_ANONYMOUS_ACCESS							_S("AnonymousAccess")

//#define CDMA_IF_NAME									SERVICE_IF_NAME
/** Interface parameter string.

Field type:Text. This field may be left as NULL */
#define CDMA_IF_PARAMS									SERVICE_IF_PARAMS
/** Comma separated list of network protocols, e.g. "PPP".

Field type: Text. This field may be left as NULL */
#define CDMA_IF_NETWORKS								SERVICE_IF_NETWORKS
/** Prompt user for authentication username and password?

Field type: TBool. This field may not be left as NULL. */
#define CDMA_IF_PROMPT_FOR_AUTH							SERVICE_IF_PROMPT_FOR_AUTH
/** Authentication username used by PPP.

Field type:Text. This field may be left as NULL */
#define CDMA_IF_AUTH_NAME								SERVICE_IF_AUTH_NAME
/** Authentication password used by PPP.

Field type: Text. This field may be left as NULL. */
#define CDMA_IF_AUTH_PASS								SERVICE_IF_AUTH_PASS

/** Number of times to retry authentication if it fails.

Field type:TUint32. This field may be left as NULL. */
#define CDMA_IF_AUTH_RETRIES							SERVICE_IF_AUTH_RETRIES

#define CDMA_IP_NETMASK									SERVICE_IP_NETMASK
/** IP address of gateway.

Field type: Text. This field may be left as NULL. */
#define CDMA_IP_GATEWAY									SERVICE_IP_GATEWAY
/** Get IP addresses (for Symbian OS mobile) from server?

Field type: TBool. This field may not be left as NULL. */
#define CDMA_IP_ADDR_FROM_SERVER						SERVICE_IP_ADDR_FROM_SERVER
#define CDMA_IP_ADDR									SERVICE_IP_ADDR
/** Get DNS addresses from server?

Field type:TBool. This field may not be left as NULL. */
#define CDMA_IP_DNS_ADDR_FROM_SERVER					SERVICE_IP_DNS_ADDR_FROM_SERVER
/** IP Address of primary name server.

Field type:Text. This field may be left as NULL */
#define CDMA_IP_NAME_SERVER1							SERVICE_IP_NAME_SERVER1
/** IP Address of secondary name server.

Field type: Text. This field may be left as NULL */
#define CDMA_IP_NAME_SERVER2							SERVICE_IP_NAME_SERVER2

#define CDMA_IP6_DNS_ADDR_FROM_SERVER					SERVICE_IP6_DNS_ADDR_FROM_SERVER
#define CDMA_IP6_NAME_SERVER1							SERVICE_IP6_NAME_SERVER1
#define CDMA_IP6_NAME_SERVER2							SERVICE_IP6_NAME_SERVER2

/** Enable LCP extensions?

Field type: TBool. This field may be left as NULL */
#define CDMA_ENABLE_LCP_EXTENSIONS						SERVICE_ENABLE_LCP_EXTENSIONS
/** Disable plain text authentication?

Field type: TBool. This field may be left as NULL */
#define CDMA_DISABLE_PLAIN_TEXT_AUTH					SERVICE_DISABLE_PLAIN_TEXT_AUTH

/** Service supports Internet only, WAP only or both.

Field type: TUint32 from TCommsDbIspType. This field may be left as NULL */
#define CDMA_AP_TYPE									_S("ApType")
/** Notify user if the requested QOS can not be satisfied for this time in microseconds. 
Set to 0xffffffff to disable.

Field type: TUint32. This field may be left as NULL */
#define CDMA_QOS_WARNING_TIMEOUT						_S("QosWarningTimeout")
/** Transparent or non-transparent radio link protocol.

Field type:TUint32 from RPacketQoS::TRLPMode. This field may not be left as NULL. */
#define CDMA_RLP_MODE									_S("RlpMode")

/** Attempt to use the mobile IP protocol.

Field type: TBool. This field may be left as NULL */
#define CDMA_MIP										_S("CDMAMobileIP")
/** Home agent address.

Field type: Text. This field may be left as NULL */
#define CDMA_MIP_HA_ADDRESS								_S("HomeAgentAddress")
/** A normal reconnect (informing the user) takes place if not both the PPP link 
drops and a change in SID or NID is received with in this time (in milliseconds). 
If they do, an automatic reconnect takes place.

Field type: TUint32 This field may be left as NULL */
#define CDMA_MIP_TIMEOUT								_S("CDMAMobileIPTimeout")

// Columns of the `DEFAULT_CDMA2000_SETTINGS_TABLE` 
// The following macros define values for the Default CDMA 2000 Settings fields.
/** The usage of this default. 

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_CDMA_USAGE								_S("Usage")
/** IWF name.

Field type: Text. This field may not be left as NULL. */
#define DEFAULT_CDMA_IWF_NAME							CDMA_IWF_NAME
/** Mask indicating valid service options.

Field type: TUint32 from RPacketContext::TServiceOption. This field may not be left as NULL. */
#define DEFAULT_CDMA_SERVICE_OPTION						CDMA_SERVICE_OPTION
/** PDP type. (IPv4 or IPv6).

Field type:TUint32 from RPacketContext::TProtocolType. This field may not be left as NULL. */
#define DEFAULT_CDMA_PDP_TYPE							CDMA_PDP_TYPE
/** PDP address of phone.

Field type:Text. This field may be left as NULL. */
#define DEFAULT_CDMA_PDP_ADDRESS						CDMA_PDP_ADDRESS
/** Data compression?

Field type:TBool. This field may be left as NULL. */
#define DEFAULT_CDMA_DATA_COMPRESSION					CDMA_DATA_COMPRESSION
/** IP header compression?

Field type: TBool. This field may be left as NULL. */
#define DEFAULT_CDMA_HEADER_COMPRESSION					CDMA_HEADER_COMPRESSION
/** Use anonymous access?

Field type:TBool. This field may be left as NULL. */
#define DEFAULT_CDMA_ANONYMOUS_ACCESS					CDMA_ANONYMOUS_ACCESS

/** Default CDMA mobile IP?

Field type: TBool. This field may be left as NULL. */
#define DEFAULT_CDMA_MIP								CDMA_MIP
/** CMDA mobile IP home address.

Field type: Text. This field may be left as NULL. */
#define DEFAULT_CDMA_MIP_HA_ADDRESS						CDMA_MIP_HA_ADDRESS
/** CMDA Mobile IP timeout.

Field type: TUint32. This field may be left as NULL. */
#define DEFAULT_CDMA_MIP_TIMEOUT						CDMA_MIP_TIMEOUT

/** Columns of the `VIRTUAL_BEARER table` */
#define VIRTUAL_BEARER_AGENT							AGENT_NAME		
#define VIRTUAL_BEARER_NIF								IF_NAME

/** Columns of the `VIRTUAL_SERVICE table` */
#define VPN_SERVICE_POLICY							_S("Policy")
#define VPN_SERVICE_IAP								_S("HomeIAP")
#define VPN_SERVICE_NETWORKID						_S("HomeNetwork")

/** Enumerated sets and bitmasks for the modem speaker `MODEM_BEARER:MODEM_SPEAKER_PREF`. */
enum TCommsDbModemSpeakerSetting
	{
	/** Speaker always off. */
	EModemSpeakerSettingNever,
	/** Speaker on until the call has been answered. */
	EModemSpeakerSettingUntilCallAnswered,
	/** Speaker always on. */
	EModemSpeakerSettingAlways,
	/** Speaker on after dialing until answer. */
	EModemSpeakerSettingAfterDialUntilAnswer
	};

/** Enumeration used by `MODEM_BEARER:MODEM_SPEAKER_VOL_PREF` */
enum TCommsDbModemSpeakerVolume
	{
	/** Speaker off. */
	EModemSpeakerVolumeQuiet,
	/** Speaker volume set to medium. */
	EModemSpeakerVolumeMedium,
	/** Speaker volume set to loud. */
	EModemSpeakerVolumeLoud
	};

/** Enumeration used by DIAL_*_ISP:ISP_TYPE, OUTGOING_WCDMA:GPRS_AP_TYPE and CDMA2000_PACKET_SERVICE_TABLE:CDMA_AP_TYPE. */
enum TCommsDbIspType
	{
	/** ISP internet only. */
	EIspTypeInternetOnly,
	/** ISP WAP only. */
	EIspTypeWAPOnly,
	/** ISP internet and WAP. */
	EIspTypeInternetAndWAP
	};

/** Enum used by DIAL_*_ISP:ISP_BEARER_TYPE. */
enum TCommsDbBearerType
	{
	/** CSD bearer. */
	EBearerTypeCSD,
	/** HSCSD bearer. */
	EBearerTypeHSCSD
	};

/** Enum used by WAP_*_BEARER:WAP_WSP_OPTION. */
enum TCommsDbWapWspOption
	{
	/** WAP WSP option set to connectionless. */
	EWapWspOptionConnectionless,
	/** WAP WSP option set to connection oriented. */
	EWapWspOptionConnectionOriented
	};

/** 
Enum for use in calls to `CCommsDatabase::OpenConnectionPrefTable*LC()`,
CCommsDatabase::OpenIAPTableViewMatchingBearerSetLC() and
CCommsDbConnectionPrefTableView::SwapConnectionPreferencesL()
*/
enum TCommDbConnectionDirection
	{
	/** Connection direction is unkown. */
	ECommDbConnectionDirectionUnknown,
	/** Connection direction is outgoing. */
	ECommDbConnectionDirectionOutgoing,
	/** Connection direction is incoming. */
	ECommDbConnectionDirectionIncoming
	};

/** Bitmask for use in calls to: CCommsDatabase::OpenIAPTableViewMatchingBearerSetLC() */
enum TCommDbBearer
	{
	/** Bearer support unknown. */
	KCommDbBearerUnknown = 0x0,
	/** CSD Bearer support. */
	KCommDbBearerCSD = 0x1,
	/** WCDMA Bearer support. */
	KCommDbBearerWcdma = 0x2,
	/** LAN Bearer support. */
	KCommDbBearerLAN = 0x4,
	/** CDMA2000 Bearer support. */	
	KCommDbBearerCdma2000 = 0x8,
	KCommDbBearerVirtual = 0x10
	};
#define KCommDbBearerPSD (KCommDbBearerWcdma|KCommDbBearerCdma2000)

/** The dialog preference determines whether or not a user should be prompted with 
a dialog at connect time. Used in CCommsDbConnectionPrefTableView::UpdateDialogPrefL() */
enum TCommDbDialogPref
	{
	/** CommDB dialiog preference is unknown. */
	ECommDbDialogPrefUnknown,
	/** Prefernce set to prompt user. */
	ECommDbDialogPrefPrompt,
	/** Preference set to warn user. */
	ECommDbDialogPrefWarn,
	/** Preference set not to prompt user. */
	ECommDbDialogPrefDoNotPrompt,
	/** Preference set to prompt user when in wrong mode. */
	ECommDbDialogPrefPromptIfWrongMode
	};

/** Enum for the global setting: GPRS_CLASS_C_BEARER. */
enum TCommDbGprsClassCBearer
	{
	/** GPRS Class C bearer. */
	ECommDbGprsClassCBearerGprs,
	/** GSM Class C bearer. */
	ECommDbGprsClassCBearerGsm
	};

/** Enum for use in calls to CCommsDatabase::NewL() */
enum TCommDbOpeningMethod
	{
	/** CommDB has been created. */
	ECommDbCreated = 0,
	/** CommDB Copied default. */
	ECommDbCopiedDefault,
	/** CommDB has been opened. */
	ECommDbOpened
	};

/** UIDs for system agent event notification */

/** The global setting `SMS_BEARER` has changed */
const TUid KUidCommDbSMSBearerChange = {0x10008F04};
/** The global setting `SMS_RECEIVE_MODE' has changed */
const TUid KUidCommDbSMSReceiveModeChange = {0x101F4AB0};
/** The global setting `GPRS_ATTACH_MODE' has changed */
const TUid KUidCommDbGPRSAttachModeChange = {0x100092BC};

/** The `MODEM_BEARER:MODEM_TSY_NAME` field has been written or a `MODEM` record has
	been deleted */
const TUid KUidCommDbModemTsyNameChange = {0x1000947f};
/** As `KUidCommDbModemTsyNameChange` above except only for a change in the
	record specified by the `MODEM_DATA_FAX` global setting */
const TUid KUidCommDbModemDataAndFaxChange =  {0x1000A43F} ;
/** As `KUidCommDbModemTsyNameChange` above except only for a change in the
	record specified by the `MODEM_PHONE_SERVICES_SMS` global setting */
const TUid KUidCommDbModemPhoneServicesAndSMSChange = {0x1000A440};

/** A record in the `DEFAULT_GPRS` table has been modified or deleted. */
const TUid KUidCommDbGPRSDefaultParamsChange = {0x10008F05};
/** A record in the `MODEM_BEARER` table has been modified or deleted. */
const TUid KUidCommDbModemRecordChange =  {0x1000A43D} ;
/** A record in the `PROXIES` table has been modified or deleted */
const TUid KUidCommDbProxiesRecordChange = {0x1000A43E};

/** Enum for DATABASE_TYPE field. 
Was deprecated in v7.0 but replaced for BC with v6.1 in v7.0s and v8.0. */
enum TCommDbDatabaseType
	{
	/** Unspecified database type. Any type of database can be opened with this parameter.*/
	EDatabaseTypeUnspecified =0,	
	/** The database has an IAP table, which defines sets of ISPs and chargecards that 
	may be used together. */
	EDatabaseTypeIAP,
	/** The database is arranged using separate ISP, location, modem and chargecard 
	tables whose records are not associated by using IAPs.
	
	ISP type databases are deprecated from version 6.1. */
	EDatabaseTypeISP
	};

#endif
