/*
* ==============================================================================
*  Name        : rconnmon.h
*  Part of     : Connection Monitor / ConnMon.dll
*  Description : 
*        RConnectionMonitor provides an interface for an application
*        to get information about active data connection. It also provides
*        a way to close any connection or all the connections.
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/

#ifndef __CONNECTIONMONITOR_H
#define __CONNECTIONMONITOR_H

// INCLUDES
#include <e32base.h>

// CONSTANTS

// TInt Attributes 
// Used by GetIntAttribute
const TUint KBearer                            =1;  // TConnMonBearerType
const TUint KNetworkStatus                     =2;  // TConnMonNetworkStatus
const TUint KConnectionStatus                  =3;  // progress constants from nifvar.h
const TUint KProtocolType                      =4;  // TConnMonProtocolType
const TUint KNetworkRegistration               =5;  // TConnMonNetworkRegistration
const TUint KSignalStrength                    =6;  // dBm
const TUint KNetworkMode                       =7;  // TConnMonNetworkMode
const TUint KSecurityMode                      =8;  // TConnMonSecurityMode
const TUint KBearerInfo                        =9;  // TConnMonBearerInfo

const TUint KTrafficClass                      =30; // Qos - Not supported
const TUint KDeliveryOrder                     =31; // Qos - Not supported
const TUint KErroneousSDUDelivery              =32; // Qos - Not supported
const TUint KResidualBitErrorRatio             =33; // Qos - Not supported
const TUint KSDUErrorRatio                     =34; // Qos - Not supported

// TUInt Attributes
// Used by GetUintAttribute, SetUintAttribute
const TUint KDownlinkData                      =100; // in bytes
const TUint KUplinkData                        =101; // in bytes
const TUint KIAPId                             =102;
const TUint KNetworkIdentifier                 =103;
const TUint KTransmitPower                     =104; // mW
const TUint KMobilePhoneNetworkMode			   =105; // TConnMonMobilePhoneNetworkMode 	
const TUint KMaximumBitrateDownlink            =130; // Qos - Not supported
const TUint KMaximumBitrateUplink              =131; // Qos - Not supported
const TUint KMaximumSDUSize                    =132; // Qos - Not supported
const TUint KTransferDelay                     =133; // Qos - Not supported
const TUint KGuaranteedBitrateDownlink         =134; // Qos - Not supported
const TUint KGuaranteedBitrateUplink           =135; // Qos - Not supported
const TUint KTrafficHandlingPriority           =136; // Qos - Not supported
const TUint KActivityTimeThreshold             =150; // in seconds, minimum allowed is 5
const TUint KDownlinkDataThreshold             =151; // in bytes,   minimum allowed is 4096
const TUint KUplinkDataThreshold               =152; // in bytes,   minimum allowed is 4096
const TUint KBearerAvailabilityThreshold       =153; // 1 means that events are 'ON', 0 means 'OFF'
const TUint KSignalStrengthThreshold           =154; // 1 means that events are 'ON', 0 means 'OFF'
const TUint KBearerGroupThreshold              =155; // 1 means that events are 'ON', 0 means 'OFF'
                                                     // if 'ON' -->
                                                     // EConnMonBearerInfoChange and EConnMonBearerGroupChange
                                                     // events are used instead of EConnMonBearerChange event


// TBool Attributes 
// Used by GetBoolAttribute, SetBoolAttribute 
const TUint KConnectionActive                  =200;
const TUint KBearerAvailability                =201;
const TUint KPacketDataAvailability            =202; // returns EFalse if packet data is blocked
                                                     // because of no dual transfer mode support
                                                     // and phone call being active otherwise ETrue
const TUint KConnectionStop                    =250;
const TUint KConnectionStopAll                 =251;

// TDes Attributes 
// Used by GetStringAttribute 
const TUint KIAPName                           =300;
const TUint KAccessPointName                   =301;
const TUint KTelNumber                         =302;
const TUint KNetworkName                       =303;

// TPckgBuf Attributes
// Used by GetPckgAttribute
const TUint KStartTime                         =400; // TTime
const TUint KClientInfo                        =401; // TConnMonClientEnum (connections only)
const TUint KNetworkNames                      =402; // TConnMonNetworkNames
const TUint KIapAvailability                   =403; // TConnMonIapInfo 
const TUint KWLANNetworks                      =404; // ConnMonWLANNetworksArrayPckg
const TUint KSNAPsAvailability                 =405; // returns SNAPs ids in old iap-like way (see KIapAvailability)
const TUint KAvailableSNAPsIds                 =406; // returns SNAPs ids in TConnMonIdsArrayPckg       
const TUint KWlanNetworks                      =407; // CConnMonWLANNetworksArrayPckg
const TUint KBearerGroupInfo                   =408; // TConnMonBearerGroupInfo


// Base value for plug-in specific attribute ids
const TUint KConnMonPluginAttributeBase        =3000000;

// DATA TYPES

// Bearer type
enum TConnMonBearerType
{
    EBearerUnknown            = 0,
    EBearerCSD                = 1,  // CSD (GSM)
    EBearerWCDMA              = 2,  // PSD (WCDMA)
    EBearerLAN                = 3,
    EBearerCDMA2000           = 4,
    EBearerGPRS               = 5,    
    EBearerHSCSD              = 6,  // HSCSD (GSM)
    EBearerEdgeGPRS           = 7,
    EBearerWLAN               = 8,
    EBearerBluetooth          = 9,
    EBearerVirtual            = 10,
    EBearerVirtualVPN         = 11,
    EBearerWcdmaCSD           = 12, // CSD (WCDMA)
    
    EBearerExternalCSD        = 30, // ext CSD (GSM)
    EBearerExternalWCDMA      = 31, // ext PSD (WCDMA)
    EBearerExternalLAN        = 32,
    EBearerExternalCDMA2000   = 33,
    EBearerExternalGPRS       = 34,    
    EBearerExternalHSCSD      = 35, // ext HSCSD (GSM)
    EBearerExternalEdgeGPRS   = 36,
    EBearerExternalWLAN       = 37,
    EBearerExternalBluetooth  = 38,
    EBearerExternalWcdmaCSD   = 39,  // ext CSD (WCDMA)
};

// Bearer specific general connection id
enum TConnMonBearerId
{
    EBearerIdAll              = 0,
    EBearerIdGPRS             = 2000000,  // covers internal and external GPRS and EdgeGPRS
    EBearerIdWCDMA            = 2000001,  // covers internal and external PSD (WCDMA)
    EBearerIdCSD              = 2000002,  // covers internal and external CSD and HSCSD (GSM)
    EBearerIdGSM              = 2000003,  // union of EBearerIdGPRS and EBearerIdCSD
    EBearerIdWLAN             = 2000004,
    EBearerIdLAN              = 2000005,
    EBearerIdWcdmaCSD         = 2000006,  // covers internal and external CSD (WCDMA)
    EBearerIdCDMA2000         = 2000007,
    EBearerIdVirtualVPN       = 2000008
};

// Network status
enum TConnMonNetworkStatus
    {
    EConnMonStatusNotAvailable = 0,
    EConnMonStatusUnattached,
    EConnMonStatusAttached,
    EConnMonStatusActive,
    EConnMonStatusSuspended
    };

// Protocol Type (type of PDP)
// It may not be available for some bearers (returns EProtocolTypeUnknown).
enum TConnMonProtocolType
{
    EProtocolTypeUnknown = 0,
    EProtocolTypeIPv4,
    EProtocolTypeIPv6,
    EProtocolTypeX25,
    EProtocolTypePPP,
    EProtocolTypeCDPD,
    EProtocolTypeIP  // connection uses both IPv4 and IPv6
};

// Asyncronous request codes
enum TConnMonAsyncRequest
    {
    EConnMonGetConnectionCount = 1,
    EConnMonGetIntAttribute,
    EConnMonGetUintAttribute,
    EConnMonGetBoolAttribute,
    EConnMonGetStringAttribute,
    EConnMonGetPckgAttribute
    };

// Events sent by Connection Monitor
enum TConnMonEvent
    {
    EConnMonCreateConnection          = 1,
    EConnMonDeleteConnection          = 2,
    EConnMonCreateSubConnection       = 3,
    EConnMonDeleteSubConnection       = 4,
    EConnMonDownlinkDataThreshold     = 5,
    EConnMonUplinkDataThreshold       = 6,
    EConnMonNetworkStatusChange       = 7,
    EConnMonConnectionStatusChange    = 8,
    EConnMonConnectionActivityChange  = 9,
    EConnMonNetworkRegistrationChange = 10,
    EConnMonBearerChange              = 11,
    EConnMonSignalStrengthChange      = 12,
    EConnMonBearerAvailabilityChange  = 13,
    EConnMonIapAvailabilityChange     = 14,
    EConnMonTransmitPowerChange       = 15,  
	EConnMonSNAPsAvailabilityChange	  = 16,	
	EConnMonNewWLANNetworkDetected	  = 17,
	EConnMonOldWLANNetworkLost		  = 18,		
	EConnMonPacketDataAvailable       = 19,	// Event is being generated when packet data
	                                        // is not anymore temporarily blocked because of
	                                        // no dual transfer mode support and 
	                                        // phone call being active	

	EConnMonPacketDataUnavailable     = 20,	// Event is being generated when packet data
	                                        // is temporarily blocked because of
	                                        // no dual transfer mode support and 
	                                        // phone call being active
    EConnMonBearerInfoChange          = 21,
    EConnMonBearerGroupChange         = 22,

    EConnMonPluginEventBase           = 4000000
    };

// Network registration status. Valid for CSD, GPRS and WCDMA.
enum TConnMonNetworkRegistration
    {
    ENetworkRegistrationNotAvailable = 0,
    ENetworkRegistrationUnknown,
    ENetworkRegistrationNoService,
    ENetworkRegistrationEmergencyOnly,
    ENetworkRegistrationSearching,
    ENetworkRegistrationBusy,
    ENetworkRegistrationHomeNetwork,
    ENetworkRegistrationDenied,
    ENetworkRegistrationRoaming
    };

// Traffic class
enum TQosTrafficClass
    {
    EQosTrafficClassConversational = 1,
    EQosTrafficClassStreaming,
    EQosTrafficClassInteractive,
    EQosTrafficClassBackground
    };

// Delivery order
enum TQosDeliveryOrder
    {
    EQosDeliveryOrderYes = 1,
    EQosDeliveryOrderNo
    };

// Delivery of erroneous SDUs
enum TQosErroneousSDUDelivery
    {
    EQosErroneousSDUDeliveryYes = 1,
    EQosErroneousSDUDeliveryNo,
    EQosErroneousSDUDeliveryUnspecified
    };

// Residual bit error ratio
enum TQosBitErrorRatio
    {
    EQosBERFivePerHundred = 1,
    EQosBEROnePerHundred,
    EQosBERFivePerThousand,
    EQosBEROnePerThousand,
    EQosBEROnePerTenThousand,
    EQosBEROnePerMillion
    };

// SDU error ratio
enum TQosSDUErrorRatio
    {
    EQosSDUErrorRatioOnePerHundred = 1,
    EQosSDUErrorRatioSevenPerThousand,
    EQosSDUErrorRatioOnePerThousand,
    EQosSDUErrorRatioOnePerTenThousand,
    EQosSDUErrorRatioOnePerHundredThousand
    };

// Client-server requests
enum TConnMonRequests
    {
    EReqGetConnectionCount             = 0,
    EReqGetConnectionInfo              = 1,
    EReqGetSubConnectionInfo           = 2,
    EReqGetIntAttribute                = 3,
    EReqGetUintAttribute               = 4,
    EReqGetBoolAttribute               = 5,
    EReqGetStringAttribute             = 6,
    EReqGetPckgAttribute               = 7,
    EReqSetIntAttribute                = 8,
    EReqSetUintAttribute               = 9,
    EReqSetBoolAttribute               = 10,
    EReqSetStringAttribute             = 11,
    EReqSetPckgAttribute               = 12,
    EReqCancelAsyncRequest             = 13,
    EReqReceiveEvent                   = 14,
    EReqCancelReceiveEvent             = 15,

    EReqPluginCreateSubSession         = 500,
    EReqPluginCloseSubSession          = 501,             
    EReqPluginRegisterAttribute        = 502,
    EReqPluginCancelRegisterAttribute  = 503,
    EReqPluginEvent                    = 504, 
    EReqPluginGetQuery                 = 505,
    EReqPluginCancelGetQuery           = 506,
    EReqPluginAttribute                = 507,

    EReqInternalSetThreshold           = 600,
    EReqInternalResetThreshold         = 601
    };

// WLAN connection modes
enum TConnMonNetworkMode 
    {
    EConnMonInfraStructure = 0,
    EConnMonAdHoc          = 1,
    EConnMonSecureInfra    = 2
    };

// WLAN connection security modes
enum TConnMonSecurityMode
    {
    EConnMonSecurityOpen   = 0,
    EConnMonSecurityWep    = 1,
    EConnMonSecurity802d1x = 2,
    EConnMonSecurityWpa    = 3,
    EConnMonSecurityWpaPsk = 4
    };
    
/** Defines Current Network Modes.

Modes: Common */
	enum TConnMonMobilePhoneNetworkMode
		{
	/** Network mode is unknown.
	
	Modes: Common */
		EConnMonNetworkModeUnknown = 0,
	/** ME is not registered.
	
	Modes: Common */
		EConnMonNetworkModeUnregistered,
	/** GSM/GPRS or DCS1800 network. */
		EConnMonNetworkModeGsm,
	/** AMPS network.
	
	Modes: CDMA */
		EConnMonNetworkModeAmps,
	/** CDMA (IS-95) network.
	
	Modes: CDMA */
		EConnMonNetworkModeCdma95,
	/** CDMA (cdma2000) network.
	
	Modes: CDMA */
		EConnMonNetworkModeCdma2000,
	/** WCDMA  (UTRA Frequency Division Duplex (FDD)) network.
	
	Modes: WCDMA */
		EConnMonNetworkModeWcdma,
	/** TD-CDMA (UTRA Time Division Duplex (TDD)) network.
	
	Modes: WCDMA */	
		EConnMonNetworkModeTdcdma
		};


// Maximum size of a plug-in's attribute or event data
const TUint KConnMonMaxPluginDataSize        = 512;
const TUint KConnMonMaxStringAttributeLength = 64;


// Package class definition for getting the TTime
typedef TPckgBuf< TTime > TConnMonTimeBuf;

// Package class definition for getting the client information
const TUint KConnMonMaxClientUids = 10;

class TConnMonClientEnum
    {
    public:
	    inline TConnMonClientEnum():iCount(0){}
    public:
        TUint iCount;
        TUid  iUid[ KConnMonMaxClientUids ];
    };
typedef TPckgBuf< TConnMonClientEnum > TConnMonClientEnumBuf;

// Package class definition for getting network names
const TUint KConnMonMaxNetworkCount = 10;
 
class TConnMonNetwork
     {
     public:
     	inline TConnMonNetwork():iType(0), iSignalStrength(0){}
     public:
         TBuf8< 32 >  			iName;
         TInt8      			iType; 				// see TConnMonNetworkMode
         TUint8					iSignalStrength;
     };
  
class TConnMonNetworkNames
     {
     public:
     	inline TConnMonNetworkNames():iCount(0){}
		inline TUint Count() {return iCount;}
     public:
         TUint            iCount;
         TConnMonNetwork  iNetwork[ KConnMonMaxNetworkCount ];
      };
      
typedef TPckgBuf< TConnMonNetworkNames > TConnMonNetworkNamesBuf;
      
// Package class definiton for getting available IAPs
const TUint KConnMonMaxIAPCount = 25;

class TConnMonIap
    {
    public:
    	inline TConnMonIap():iIapId(0){}
    public:
        TUint iIapId;
    };

class TConnMonIapInfo
    {
    public:
    	inline TConnMonIapInfo():iCount(0){}
		inline TUint Count() {return iCount;}
    public:
        TUint        iCount;
        TConnMonIap  iIap[ KConnMonMaxIAPCount ];
    };

typedef TPckgBuf< TConnMonIapInfo > TConnMonIapInfoBuf;

// Package class definiton for receiving event of SNAPs' availability change
const TUint KConnMonMaxSNAPsCount = 25;

class TConnMonSNAPId
    {
    public:
    	inline TConnMonSNAPId():iSNAPId(0){}
    public:
        TUint iSNAPId;
    };

class TConnMonSNAPInfo
    {
    public:
    	inline TConnMonSNAPInfo():iCount(0){}
		inline TUint Count() {return iCount;}
    public:
        TUint        iCount; // amount of items in iSNAP
        TConnMonSNAPId iSNAP[ KConnMonMaxSNAPsCount ]; // array of ids of available SNAPs
    };

typedef TPckgBuf< TConnMonSNAPInfo > TConnMonSNAPInfoBuf;

// Bearer group definition, new values will be added to the end of the
// enumeration.
enum TConnMonBearerGroup
    {
    EBearerGroupUnknown = 0,
    EBearerGroupCellular = 0x00000001,
    EBearerGroupNonCellular = 0x00000002,
    EBearerGroupCellularPacket = 0x00000004,
    EBearerGroupCircuitSwitched = 0x00000008,
    EBearerGroup2G = 0x00000010,
    EBearerGroup2GPacket = 0x00000020,
    EBearerGroup3G = 0x00000040,
    EBearerGroup3GPacket = 0x00000080,
    EBearerGroupHSPA = 0x00000100,
    EBearerGroupLANBased = 0x00000200,
    EBearerGroupWLAN = 0x00000400,
    EBearerGroupIPOverConnectivityProtocol = 0x00000800,
    EBearerGroupWired = 0x00001000,
    EBearerGroupVirtual = 0x00002000
    };

// Bearer definition, new values will be added to the end of the
// enumeration. These are used if KBearerInfo attribute is used
// or in events if KBearerGroupThreshold is set 'ON'.
enum TConnMonBearerInfo
    {
    EBearerInfoUnknown = 0,
    EBearerInfoCSD,
    EBearerInfoWCDMA,
    EBearerInfoLAN,
    EBearerInfoCDMA2000,
    EBearerInfoGPRS,
    EBearerInfoHSCSD,
    EBearerInfoEdgeGPRS,
    EBearerInfoWLAN,
    EBearerInfoBluetooth,
    EBearerInfoVirtual,
    EBearerInfoVirtualVPN,
    EBearerInfoWcdmaCSD,
    EBearerInfoHSDPA,
    EBearerInfoHSUPA,
    EBearerInfoHSxPA
    };

// Bearer Group info
class TConnMonBearerGroupInfo
    {
    public:
        inline TConnMonBearerGroupInfo():iInternal( ETrue ),
                                         iBearerGroups( 0 ),
                                         iBearerGroups2( 0 ){}
    public:
        TBool   iInternal;      // ETrue == internal or EFalse == external connection
        TUint   iBearerGroups;  // Masked bearer groups
        TUint   iBearerGroups2; // Reserved for the future
    };

typedef TPckgBuf<TConnMonBearerGroupInfo> TConnMonBearerGroupInfoBuf;


/**
 *  CConnMonWlanNetwork is a class, incapsulated Wlan network abstraction 
 *  Is able to be transferred through processes (client/server)
 *  in object's size-independent manner, to meet backward/forward compatibility 
 *
 *  
 */

NONSHARABLE_CLASS( CConnMonWlanNetwork ): public CBase
    {
    public:

        // Length of the WLAN network name
        static const TUint KMaxNameLength   = 32;

        // Length of the WLAN bssid
        static const TUint KWlanBssId = 6;

        // Reserved for future usage
        static const TUint KExtraCount = 10;

        /**
         * Constructor
         * @param aName name of the network
         * @param aConnectionMode ConnectionMode of the network
         * @param aSignalStrength Signal strength of the network
         * @param aSecurityMode Security mode of the network
         * @param aBssId Bssid of the network
         * @param aVendorData Vendordata of the network
         * 
         * @return Returns pointer to the created CConnMonWlanNetwork object.
         */
        IMPORT_C static CConnMonWlanNetwork* NewL( const TBuf<KMaxNameLength>& aName,
                                                   TUint aConnectionMode,
                                                   TUint aSignalStrength,
                                                   TUint aSecurityMode,
                                                   const TBuf8<KWlanBssId>& aBssId,
                                                   const TDesC& aVendorData );

        /**
         * Constructor
         * 
         * @return Returns pointer to the created CConnMonWlanNetwork
         * object. Data members are empty.

         */
        IMPORT_C static CConnMonWlanNetwork* NewL();

        /**
         * Copy constructor
         * @param aConnMonWlanNetwork An object which is copied.
         * 
         * @return Returns pointer to the created CConnMonWlanNetwork object.
         */
        IMPORT_C static CConnMonWlanNetwork* NewL( CConnMonWlanNetwork& aConnMonWlanNetwork );

        /**
         * Destructor
         */
        IMPORT_C ~CConnMonWlanNetwork();

        /**
         * Assignment operator
         * @param An object which is assigned.
         * 
         */
        IMPORT_C CConnMonWlanNetwork& operator=( CConnMonWlanNetwork& aConnMonWlanNetwork );

        /**
         * Compares two networks by iSignalStrength; 
         *
         * @param aFirst to be compared with aSecond
         * 
         * @return Returns 1 if aFirst is less than aSecond, 0 if they
         * are equal and -1 otherwise
         */
        IMPORT_C static TInt CompareBySignal( const CConnMonWlanNetwork& aFirst,
                                              const CConnMonWlanNetwork& aSecond );

        /**
         * Returns the name(SSID) of the network.
         *
         * @return Returns the name of the wlan network if exists.
         * Otherwise returns empty buffer.
         */
        inline TBuf<KMaxNameLength> Name() 
            {
            return iName;
            };
        
        /**
         * Returns the connection mode of the network.
         *
         * @return Returns the connection mode (defined in
         * TConnMonNetworkMode)
         */
        inline TUint ConnectionMode() 
            {
            return iConnectionMode;
            };

        /**
         * Returns the signal strength of the network.
         *
         * @return Returns the signal strength
         */
        inline TUint SignalStrength() 
            {
            return iSignalStrength;
            };

        /**
         * Returns the security mode of the network.
         *
         * @return Returns the security mode.
         */
        inline TUint SecurityMode() 
            {
            return iSecurityMode;
            };

        /**
         * Returns the WLAN bssid.
         *
         * 
         * @return Returns the WLAN bssid.
         */
        inline TBuf8<KWlanBssId> WlanBssid()
            {
            return iWlanBssId;
            };

        /**
         * Returns the pointer to the Vendor specific data buffer.
         * Ownership of the data is NOT transferred.
         *
         * 
         * @return Returns the vendor specific data if available.
         * Otherwise returns NULL.
         */
        inline HBufC* VendorData()
            {
            return iVendorData;
            };

        /**
         * Packs the object of class to HBufC
         * Ownership of newly created pointer is transferred to caller  
         * 
         * @return pointer to heap descriptor
         */ 
        const HBufC* ToBuf() const;

        /**
         * Unpacks object of class CConnMonWlanNetwork from aPtrC
         * 
         * @return Returns KErrNone is succeed. Otherwise returns
         * system-wide error code.
         */ 
        static TInt FromPtrC( const TPtrC&          aPtrC,
                              CConnMonWlanNetwork*  aConnMonWlanNetwork );

    private:

        /**
         * Default constructor
         * 
         */ 
        CConnMonWlanNetwork();

        /**
         * Default constructor
         * @param aName name of the network
         * @param aConnectionMode ConnectionMode of the network
         * @param aSignalStrength Signal strength of the network
         * @param aSecurityMode Security mode of the network
         * @param aBssId Mac address of the base station.
         * @param aVendorData Vendordata of the network
         * 
         */ 
        CConnMonWlanNetwork( const TBuf<KMaxNameLength>& aName,
                             TUint aConnectionMode,
                             TUint aSignalStrength,
                             TUint aSecurityMode,
                             const TBuf8<KWlanBssId>& aBssId,
                             const TDesC& aVendorData );

        /**
         * Second-phase constructor
         * 
         */ 
        void ConstructL();


    // data
    private:  

        TBuf<KMaxNameLength>    iName;              // Network name
        TUint                   iConnectionMode;    // See TConnMonNetworkMode
        TUint                   iSignalStrength;    // Signal strength
        TUint                   iSecurityMode;      // See TConnMonSecurityMode
        TBuf8<KWlanBssId>       iWlanBssId;         // Wlan BssId
        HBufC*                  iVendorData;        // For vendor specific data
        TUint                   iExtraBuf[KExtraCount]; // Reserved for future
    };

// Array of the WLAN networks
typedef RPointerArray<CConnMonWlanNetwork>    RConnMonWlanNetworksPtrArray;


/**
 *  Package of array of items of class CConnMonWlanNetwork
 *  
 *  
 */

class CConnMonWlanNetworksPtrArrayPckg : public CBase
    {
    public:
    
    /**
     * Constructs the package of array of pointers to
     * CConnMonWlanNetwork objects on the heap
     *
     * @param aRef Array of pointers to CConnMonWlanNetwork objects
     * @param aBufSize Size of the buffer, intended to contain the package
     */
    CConnMonWlanNetworksPtrArrayPckg(const RPointerArray<CConnMonWlanNetwork>& aRef,
                                     TUint aBufSize); 
            
    /**
     * Constructs empty package on the heap
     *
     * @param aBufSize Size of the buffer, intended to contain the package
     */
    IMPORT_C CConnMonWlanNetworksPtrArrayPckg(TUint aBufSize);
        
    /**
     * Destruction
     */     
    IMPORT_C virtual ~CConnMonWlanNetworksPtrArrayPckg(); 
        
    /**
     * Unpacks package to an array of pointers to 
     * CConnMonWLANNetwork objects
     *
     * @param aRef Array, containing pointers to unpacked objects
     */ 
    IMPORT_C void UnpackToL(RPointerArray<CConnMonWlanNetwork>& aRef) const;

    /**
     * Gets iBuf
     *
     * @return iBuf
     */ 
    IMPORT_C HBufC* Buf() const;
        
    // data
    private:
        
        /**
         * Buffer on the heap, containing the package
         */ 
        HBufC*      iBuf;
    
    };

/**
 *  Interface template for the class T serialization to/from HBuf/TPtr
 *  Class T could be any type of class (T, C, etc)
 *
 *  
 */
template <class T>
   class MDesSerializer
    {
    public:

    /**
     * Have to pack the object of class T to HBufC
     * Ownership of newly cleated pointer is transferred to caller  
     * 
     * @return pointer to heap descriptor
     */ 
     virtual const HBufC* ToBuf() const = 0;

    /**
     * Have to unpack object of class T from aPtrC
     * 
     * @return const pointer to heap descriptor
     */ 
     static T FromPtrC(const TPtrC& aPtrC);

    };

/**
 *  Id
 *	MDesSerializer - abstract interface for class serialization
 *  ConnMonTId class declaration 
 *
 *  
 */
class TConnMonId : public MDesSerializer<TConnMonId>
    {

public:
	
	// defines max size of the object in TChar's
	static const TUint KMaxSize = (
								  sizeof(TUid)			// iId 
								  )/  sizeof(TChar) + 1;   	// +1 is for rounding to bigger integer
 		 
	// defines shifts of fields	inside the object
	enum FieldsShifts
		{
		EId = 	0
		};

	/**
     * Constructor.
	 * @param aId ID
     */
	 IMPORT_C TConnMonId(TUint aId);

	/**
     * 
     * iId getter
     *
     * @return iId 
     */
     IMPORT_C TUint Id() const;

	// From MDesSerializer
		
	/**
	 * See MDesSerializer
	 */					
	 IMPORT_C const HBufC* ToBuf() const;
			
	/**
	 * See MDesSerializer
	 */	
  	 IMPORT_C static TConnMonId FromPtrC(const TPtrC& aPtrC);
     
protected:

private:
	
protected: // data

	/**
     * ID
     */
    const TUint iId;
	
private: // data
    
    };

// Array of the ids
typedef RArray<TConnMonId>			  RConnMonIdsArray;

/**
 *  Package of array of items of class TConnMonId 
 *  
 *  
 */

class ConnMonIdsArrayPckg 
	{
public:
	
	/**
     * Constructs the package of array 
     *
     * @param aRef Array to be packed
     * @param aBufSize Length of the buffer, intended to contain the package
     */
    ConnMonIdsArrayPckg(const RArray<TConnMonId>& aRef, TUint aBufSize); 
			
	/**
     * Constructs an empty package
     *
     * @param aBufSize Length of the buffer, intended to contain the package
     */
	IMPORT_C ConnMonIdsArrayPckg(TUint aBufSize);
		
	/**
     * Destruction
     */		
	IMPORT_C virtual ~ConnMonIdsArrayPckg(); 
		
	/**
     * Unpacks package to the array
     *
     * @param aRef Array, intended to containing the unpacked objects
     */	
	IMPORT_C void UnpackToL(RArray<TConnMonId>& aRef) const;

	/**
     * Gets iBuf
     * gettet returns not const
     * @return iBuf
     */	
	IMPORT_C HBufC* Buf() const;
		
	// data
	protected:
		
		/**
	     * Buffer, containing the package
		 */	
		HBufC* 		iBuf;
    
    };

// FORWARD DECLARATIONS
class CConnMonEventBase;
class CConnMonEventHandler;

// CLASS DECLARATION
/**
*  MConnectionMonitorObserver
*  Client application must implement the MConnectionMonitorObserver interface 
*  in order to receive notifications. MConnectionMonitorObserver::EventL() method  
*  will be called every time an event arrives.
*
*  
*  
*/
class MConnectionMonitorObserver
    {
    public:
         /**
        * Event method is called every time an event occures.
        * 
        * @param aConnMonEvent The event information.
        * @return void
        */
        virtual void EventL( const CConnMonEventBase &aConnMonEvent ) =0;
    };

/**
*  RConnectionMonitor
*  
*  
*/
class RConnectionMonitor : public RSessionBase
    {
    public: // Constructor
        inline RConnectionMonitor() : RSessionBase(), iHandler( 0 ), iPtrArray(), iIndex( 0 ) {};

    public: // New methods
        /**
        * Connects the client to the Connection Monitor Server. It must be called 
        * before any of other methods during the Connection Monitor session.
        * 
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt ConnectL();

        /**
        * Closes the Connection Monitor session. An opened RConnectionMonitor must 
        * be closed explicitily to prevent a resource (memory) leak.
        * 
        * @return void
        */
        IMPORT_C void Close();

        /**
        * Gathers information on currently active connections.
        * 
        * @param aConnectionCount On completion, contains the number of active connections.
        * @param aStatus KErrNone if successful, a system-wide error code if not.
        * @return void
        */
        IMPORT_C void GetConnectionCount( TUint& aConnectionCount, TRequestStatus& aStatus );

        /**
        * Gets the connection id and the count of the subconnections for the given index.
        * GetConnectionCount() must be called to gather the information on active
        * connections before calling this method.
        * @param aIndex Must be between 1 and the count returned by GetConnectionCount().
        * @param aConnectionId On return, contains the connection id.
        * @param aSubConnectionCount On return, contains the number of subconnections.
        * @return void
        */
        IMPORT_C TInt GetConnectionInfo( const TUint aIndex, 
                                         TUint& aConnectionId, 
                                         TUint& aSubConnectionCount ) const;

        /**
        * Gets the subconnection id for the given index.
        * @param aConnectionId Connection id.
        * @param aIndex Must be between 1 and the count returned by GetConnectionInfo().
        * @param aSubConnectionId On return, contains the subconnection id.
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt GetSubConnectionInfo( const TUint aConnectionId, 
                                            const TUint aIndex, 
                                            TUint& aSubConnectionId ) const;

        /**
        * Gets the value for a TInt attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be retrived.
        * @param aValue On completion, contains the requested TInt attribute.
        * @param aStatus KErrNone if successful, a system-wide error code if not.
        * @return void.
        */
        IMPORT_C void GetIntAttribute( const TUint aConnectionId, 
                                       const TUint aSubConnectionId, 
                                       const TUint aAttribute, 
                                       TInt& aValue, 
                                       TRequestStatus& aStatus );

        /**
        * Gets the value for a TUint attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be retrived.
        * @param aValue On completion, contains the requested TUint attribute.
        * @param aStatus KErrNone if successful, a system-wide error code if not.
        * @return void.
        */
        IMPORT_C void GetUintAttribute( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TUint aAttribute, 
                                        TUint& aValue, 
                                        TRequestStatus& aStatus );

        /**
        * Gets the value for a TBool attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be retrived.
        * @param aValue On completion, contains the requested TBool attribute.
        * @param aStatus KErrNone if successful, a system-wide error code if not.
        * @return void.
        */
        IMPORT_C void GetBoolAttribute( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TUint aAttribute, 
                                        TBool& aValue, 
                                        TRequestStatus& aStatus );

        /**
        * Gets the value for a string attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be retrived.
        * @param aValue On completion, contains the requested string. Use a 16-bit descriptor!
        * @param aStatus KErrNone if successful, a system-wide error code if not.
        * @return void.
        */
        IMPORT_C void GetStringAttribute( const TUint aConnectionId, 
                                          const TUint aSubConnectionId, 
                                          const TUint aAttribute, 
                                          TDes& aValue, 
                                          TRequestStatus& aStatus ) const;

        /**
        * Gets the value for a packaged attribute (TConnMonTimeBuf, TConnMonClientEnumBuf).
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be retrived.
        * @param aValue On completion, contains the requested packaged attribute.
        * @param aStatus KErrNone if successful, a system-wide error code if not.
        * @return void.
        */
        IMPORT_C void GetPckgAttribute( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TUint aAttribute, 
                                        TDes8& aValue, 
                                        TRequestStatus& aStatus ) const;
                                        
        /**
        * Gets the value for a packaged attribute (TConnMonTimeBuf, TConnMonClientEnumBuf).
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be retrived.
        * @param aValue On completion, contains the requested packaged attribute.
        * @param aStatus KErrNone if successful, a system-wide error code if not.
        * @return void.
        */
        IMPORT_C void GetPckgAttribute( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TUint aAttribute, 
                                        TDes16& aValue, 
                                        TRequestStatus& aStatus ) const;
        
        /**
        * Sets the value for a TInt attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be set.
        * @param aValue The value to be set.
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt SetIntAttribute( const TUint aConnectionId, 
                                       const TUint aSubConnectionId, 
                                       const TUint aAttribute, 
                                       const TInt aValue ) const;
        
        /**
        * Sets the value for a TUint attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be set.
        * @param aValue The value to be set.
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt SetUintAttribute( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TUint aAttribute, 
                                        const TUint aValue ) const;
        
        /**
        * Sets the value for a TBool attribute.
        * This method can be used to stop a connection (KConnectionStop).
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be set.
        * @param aValue The value to be set.
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt SetBoolAttribute( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TUint aAttribute, 
                                        const TBool aValue ) const;
        
        /**
        * Sets the value for a string attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be set.
        * @param aValue The string value to be set. Must be a 16-bit descriptor!.
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt SetStringAttribute( const TUint aConnectionId, 
                                          const TUint aSubConnectionId, 
                                          const TUint aAttribute, 
                                          const TDes& aValue ) const;
        
        /**
        * Sets the value for a packaged attribute.
        * @param aConnectionId Connection id.
        * @param aSubConnectionId Subconnection id. If set to 0, method applies to connection.
        * @param aAttribute Identifies the attribute to be set.
        * @param aValue The value to be set.
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt SetPckgAttribute( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TUint aAttribute, 
                                        const TDes8& aValue ) const;
        
        /**
        * Cancels an asyncronous request.
        * @param aReqToCancel Identifies the request to be cancelled.
        *                     Values are defined in TConnMonAsyncRequest.
        * @return void.
        */
        IMPORT_C void CancelAsyncRequest( TInt aReqToCancel );
        
        /**
        * Registers an event observer to catch connection monitor events.
        * @param aObserver The event observer.
        * @return KErrNone if successful, a system-wide error code if not.
        */
        IMPORT_C TInt NotifyEventL( MConnectionMonitorObserver& aObserver );
        
        /**
        * Cancels the notifications.
        * @return void.
        */
        IMPORT_C void CancelNotifications();

    private: // New methods
        void ReceiveEvent( TDes8& aBuffer, TDes8& aExtraBuf, TRequestStatus& aStatus );
        void CancelReceiveEvent();
        TBool IsConnected() const;
        TPtr8& NextPtr();

    private: // Data
        CConnMonEventHandler* iHandler;
        RArray< TPtr8 > iPtrArray;
        TInt iIndex;

    private: // Friend classes
        friend class CConnMonEventHandler;
    };

/**
*  CConnMonEventBase
*  Base class for all event types.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonEventBase ) : public CBase
    {
    public: // constructors and destructor
        CConnMonEventBase( const TInt aEventType, const TUint iConnectionId );
        ~CConnMonEventBase();

    public: // new methods
        /**
        * Gets the type of the event.
        * @return Type of the event. Values are defined in TConnMonEventType.
        */
        IMPORT_C TInt EventType() const;

        /**
        * Gets the connection id of the connection.
        * @return Connection id.
        */
        IMPORT_C TUint ConnectionId() const;

    private: // Data
        TInt  iEventType;
        TUint iConnectionId;
    };

/**
*  CConnMonCreateConnection
*  Event is triggered when a new connection has been been created.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonCreateConnection ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonCreateConnection( const TUint aConnectionId );
        ~CConnMonCreateConnection();
    };

/**
*  CConnMonDeleteConnection
*  Event is triggered when a connection has been been deleted.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonDeleteConnection ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonDeleteConnection( const TUint aConnectionId, 
                                  const TUint aDownlinkData, 
                                  const TUint aUplinkData,
                                  const TBool aAuthDelete );
        ~CConnMonDeleteConnection();

    public: // new methods
        /**
        * Gets the downlink data volume.
        * @return Downlink data volume in bytes.
        */
        IMPORT_C TUint DownlinkData() const;
        
        /**
        * Gets the uplink data volume.
        * @return Uplink data volume in bytes.
        */
        IMPORT_C TUint UplinkData() const;

        /**
        * Returns ETrue if the user has deactivated the connection
        * by using Connection Monitor or if some application has issued 
        * RConnection::Stop( RConnection::EStopAuthoritative ).
        * @return ETrue if connection has been deactivated in an 
        *         authoritative way otherwise returns EFalse.
        */
        IMPORT_C TBool AuthoritativeDelete() const;

    private: // Data
        TUint iDownlinkData;
        TUint iUplinkData;
        TBool iAuthDelete;
    };

/**
*  CConnMonCreateSubConnection
*  Event is triggered when a new subconnection has been been created.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonCreateSubConnection ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonCreateSubConnection( const TUint aConnectionId, 
                                     const TUint aSubConnectionId );
        ~CConnMonCreateSubConnection();

    public: // new methods
        /**
        * Gets the new subconnection id.
        * @return Subconnection id.
        */
        IMPORT_C TUint SubConnectionId() const;

    private: // Data
        TUint iSubConnectionId;
    };

/**
*  CConnMonDeleteSubConnection
*  Event is triggered when a subconnection has been been deleted.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonDeleteSubConnection ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonDeleteSubConnection( const TUint aConnectionId, 
                                     const TUint aSubConnectionId, 
                                     const TUint aDownlinkData, 
                                     const TUint aUplinkData,
                                     const TBool aAuthDelete );
        ~CConnMonDeleteSubConnection();

    public: // new methods
        /**
        * Gets the subconnection id of the deleted subconnection.
        * @return Subconnection id.
        */
        IMPORT_C TUint SubConnectionId() const;
        
        /**
        * Gets the downlink data volume.
        * @return Downlink data volume in bytes.
        */
        IMPORT_C TUint DownlinkData() const;
        
        /**
        * Gets the uplink data volume.
        * @return Uplink data volume in bytes.
        */
        IMPORT_C TUint UplinkData() const;

        /**
        * Returns ETrue if the user has deactivated the connection
        * by using Connection Monitor or if some application has issued 
        * RConnection::Stop( RConnection::EStopAuthoritative ).
        * @return ETrue if connection has been deactivated in an 
        *         authoritative way otherwise returns EFalse.
        */
        IMPORT_C TBool AuthoritativeDelete() const;

    private: // Data
        TUint iSubConnectionId;
        TUint iDownlinkData;
        TUint iUplinkData;
        TBool iAuthDelete;
    };

/**
*  CConnMonDownlinkDataThreshold
*  Event is triggered when there is a change in the volume of downlink data 
*  for some connection. The notification will only complete when the change in 
*  volume increases by a client specified amount (KDownlinkDataThreshold). 
*  If KDownlinkDataThreshold=0 (=default) events will not be sent for that connection.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonDownlinkDataThreshold ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonDownlinkDataThreshold( const TUint aConnectionId, 
                                       const TUint aSubConnectionId, 
                                       const TUint aDownlinkData );
        ~CConnMonDownlinkDataThreshold();

    public: // new methods
        /**
        * Gets the subconnection id.
        * @return Subconnection id.
        */
        IMPORT_C TUint SubConnectionId() const;
        
        /**
        * Gets the downlink data volume.
        * @return Downlink data volume in bytes.
        */
        IMPORT_C TUint DownlinkData() const;

    private: // Data
        TUint iSubConnectionId;
        TUint iDownlinkData;
    };

/**
*  CConnMonUplinkDataThreshold
*  Event is triggered when there is a change in the volume of uplink data
*  for some connection. The notification will only complete when the change
*  in volume increases by a client specified amount (KUplinkDataThreshold). 
*  If KUplinkDataThreshold=0 (=default) events will not be sent for that connection.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonUplinkDataThreshold ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonUplinkDataThreshold( const TUint aConnectionId, 
                                     const TUint aSubConnectionId, 
                                     const TUint aUplinkData );
        ~CConnMonUplinkDataThreshold();

    public: // new methods
        /**
        * Gets the subconnection id.
        * @return Subconnection id.
        */
        IMPORT_C TUint SubConnectionId() const;
        
        /**
        * Gets the uplink data volume.
        * @return Uplink data volume in bytes.
        */
        IMPORT_C TUint UplinkData() const;

    private: // Data
        TUint iSubConnectionId;
        TUint iUplinkData;
    };

/**
*  CConnMonNetworkStatusChange
*  Event is triggered when network status changes for some connection.
*  Connection id passed in the event is a bearer specific connection id (TConnMonBearerId).
*  
*  
*/
NONSHARABLE_CLASS( CConnMonNetworkStatusChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonNetworkStatusChange( const TUint aConnectionId, 
                                     const TInt aNetworkStatus );
        ~CConnMonNetworkStatusChange();

    public: // new methods
        /**
        * Gets the network status.
        * @return Network status. Values are defined in TConnMonNetworkStatus.
        */
        IMPORT_C TInt NetworkStatus() const;

    private: // Data
        TInt  iNetworkStatus;
    };

/**
*  CConnMonConnectionStatusChange
*  Event is triggered when the status of some connection changes.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonConnectionStatusChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonConnectionStatusChange( const TUint aConnectionId, 
                                        const TUint aSubConnectionId, 
                                        const TInt aConnectionStatus );
        ~CConnMonConnectionStatusChange();

    public: // new methods
        /**
        * Gets the subconnection id.
        * @return Subconnection id.
        */
        IMPORT_C TUint SubConnectionId() const;
        
        /**
        * Gets the connection status.
        * @return Connection status. Values are defined in nifvar.h.
        */
        IMPORT_C TInt ConnectionStatus() const;

    private: // Data
        TUint iSubConnectionId;
        TInt  iConnectionStatus;
    };

/**
*  CConnMonConnectionActivityChange
*  Event is triggered when some connection changes from active to idle or vice versa.
*  If KActivityTimeThreshold=0 (=default) events will not be sent for that connection.
*  KActivityTimeThreshold defines the period (in seconds) for checking whether the 
*  connection is active or not.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonConnectionActivityChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonConnectionActivityChange( const TUint aConnectionId, 
                                          const TUint aSubConnectionId, 
                                          const TBool aActivity );
        ~CConnMonConnectionActivityChange();

    public: // new methods
        /**
        * Gets the subconnection id.
        * @return Subconnection id.
        */
        IMPORT_C TUint SubConnectionId() const;
        
        /**
        * Gets the connection activity.
        * @return ETrue if the connection is active, EFalse if not.
        */
        IMPORT_C TBool ConnectionActivity() const;

    private: // Data
        TUint iSubConnectionId;
        TBool iActivity;
    };

/**
*  CConnMonNetworkRegistrationChange
*  Event is triggered when network registration status (GSM/GPRS/WCDMA) changes.
*  Connection id passed in the event is generic (TConnMonBearerId) and the event
*  applies to all (GSM/GPRS/WCDMA) connections.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonNetworkRegistrationChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonNetworkRegistrationChange( const TUint aConnectionId, 
                                           const TInt  aRegistrationStatus );
        ~CConnMonNetworkRegistrationChange();

    public: // new methods
        /**
        * Gets the network registration status.
        * @return Registration status. Values are defined in TConnMonNetworkRegistration.
        */
        IMPORT_C TInt RegistrationStatus() const;

    private: // Data
        TInt  iRegistrationStatus;
    };

/**
*  CConnMonBearerChange
*  Event is triggered when bearer type (GPRS / Edge GPRS / WCDMA) changes. 
*  Connection id passed in the event is generic (see. TConnMonBearerId) and the event 
*  applies to all GPRS connections (including also external GPRS connections).
*  
*  
*/
NONSHARABLE_CLASS( CConnMonBearerChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonBearerChange( const TUint aConnectionId, const TInt aBearer );
        ~CConnMonBearerChange();

    public: // new methods
        /**
        * Gets the new bearer. Values are defined in TConnMonBearerType.
        * @return 
        */
        IMPORT_C TInt Bearer() const;

    private: // Data
        TInt  iBearer;
    };

/**
*  CConnMonSignalStrengthChange
*  Event is triggered when signal strength (dB) changes. 
*  Connection id passed in the event is generic (see. TConnMonBearerId) and the event 
*  applies to all GSM or WLAN connections.
*  Client must set KSignalStrengthThreshold to 1 to receive these
*  events. This event is valid only for cellular (GPRS, WCDMA etc.)
*  bearers and not available for other bearers, e.g. WLAN.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonSignalStrengthChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonSignalStrengthChange( const TUint aConnectionId, const TInt aSignalStrength );
        ~CConnMonSignalStrengthChange();

    public: // new methods
        /**
        * Gets the signal strength. 
        * @return 
        */
        IMPORT_C TInt SignalStrength() const;

    private: // Data
        TInt  iSignalStrength;
    };

/**
*  CConnMonBearerAvailabilityChange
*  Event is triggered when the availability of some bearer changes.
*  Connection id passed in the event is generic (see. TConnMonBearerId).
*  Client must set KBearerAvailabilityThreshold to 1 to receive these
*  events. Using this event for detecting changes in WLAN availability
*  requires WLAN background scan to be enabled.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonBearerAvailabilityChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonBearerAvailabilityChange( const TUint aConnectionId, 
                                          const TBool aAvailability );
        ~CConnMonBearerAvailabilityChange();

    public: // new methods        
        /**
        * Gets the availability of a bearer.
        * @return ETrue if the bearer is available, EFalse if not.
        */
        IMPORT_C TBool Availability() const;

    private: // Data
        TBool iAvailability;
    };

/**
*  CConnMonGenericEvent
*  Event is triggered when a plug-in engine sends a bearer specific event
*  that is unknown to the Connection Monitor server.
*  Connection id passed in the event is generic (see. TConnMonBearerId).
*  
*  
*/
NONSHARABLE_CLASS( CConnMonGenericEvent ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonGenericEvent( const TUint aType,
                              const TUint aConnectionId, 
                              TAny* aData );
        ~CConnMonGenericEvent();

    public: // new methods        
        /**
        * Gets a pointer to the event data.
        * Note that the pointer is valid only inside EventL().
        * @return A pointer to the event data.
        */
        IMPORT_C TAny* Data() const;

    private: // Data
        TAny* iData;
    };

/**
*  CConnMonIapAvailabilityChange
*  Event is triggered when when IAP Availability changes.
*  Connection id passed in the event is generic (see. TConnMonBearerId).
*  
*  
*/
NONSHARABLE_CLASS( CConnMonIapAvailabilityChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonIapAvailabilityChange( const TUint            aConnectionId, 
                                       const TConnMonIapInfo* aIapInfoPtr );
        ~CConnMonIapAvailabilityChange();

    public: // new methods        
        /**
        * Gets the IAP availability information. 
        * @return TConnMonIapInfo.
        */
        IMPORT_C TConnMonIapInfo IapAvailability() const;

    private: // Data
        TConnMonIapInfo iIapInfo;
    };

/**
*  CConnMonTransmitPowerChange
*  Event is triggered when the used transmit power (mW) changes (WLAN). 
*  Connection id passed in the event is EBearerIdWLAN.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonTransmitPowerChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonTransmitPowerChange( const TUint aConnectionId, const TUint aTransmitPower );
        ~CConnMonTransmitPowerChange();

    public: // new methods
        /**
        * Gets the transmit power. 
        * @return 
        */
        IMPORT_C TUint TransmitPower() const;

    private: // Data
        TUint  iTransmitPower;
    };

/**
*  CConnMonSNAPsAvailabilityChange
*  Event is triggered when when SNAPs Availability changes.
*  Connection id passed in the event is generic (see. TConnMonBearerId).
*  
*  
*/
NONSHARABLE_CLASS( CConnMonSNAPsAvailabilityChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonSNAPsAvailabilityChange( const TUint            aConnectionId, 
										const TUint				aSNAPsAvailable,
                                       const TConnMonSNAPInfo*  aSNAPInfoPtr );
        ~CConnMonSNAPsAvailabilityChange();

    public: // new methods        
        /**
        * Gets the SNAP availability information. 
        * @return TConnMonSNAPInfo.
        */
        IMPORT_C TConnMonSNAPInfo SNAPAvailability() const;
		
		/**
        * Gets amount of available SNAPs. 
        * @return iSNAPsAvailable
        */
        IMPORT_C TUint SNAPsAvailabile() const;

    private: // Data
        TConnMonSNAPInfo iSNAPInfo;
		TUint			iSNAPsAvailable;
    };

/**
*  CConnNewWLANNetworkDetected
*  Event is triggered when new WLAN network is detected.
*  Connection id passed in the event is generic (TConnMonBearerWLAN).
*  iDetected is TRUE, if new network is detected
*  
*  
*/
NONSHARABLE_CLASS( CConnMonNewWLANNetworkDetected ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonNewWLANNetworkDetected( const TUint aConnectionId/*, 
                                          const TBool aDetected*/ );
        ~CConnMonNewWLANNetworkDetected();

    public: // new methods        
        /**
        * New WLAN network is in visibility range
        * @return ETrue if the new WLAN network detected, EFalse if not.
        */
       // IMPORT_C TBool Detected() const;

   // private: // Data
    //    TBool iDetected;
    };

/**
*  CConnOldWLANNetworkLost
*  Event is triggered when old WLAN network is lost.
*  Connection id passed in the event is generic (TConnMonBearerWLAN).
*  iLost is TRUE, if old network is lost
*  
*  
*/
NONSHARABLE_CLASS( CConnMonOldWLANNetworkLost ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonOldWLANNetworkLost( const TUint aConnectionId/*, 
                                          const TBool aLost */);
        ~CConnMonOldWLANNetworkLost();

    public: // new methods        
        /**
        * New WLAN network is lost from visibility range
        * @return ETrue if the old WLAN network lost, EFalse if not.
        */
      //  IMPORT_C TBool Lost() const;

    private: // Data
       // TBool iLost;
    };
/**
*  CConnMonPacketDataUnavailable
*  Event is triggered when dual transfer mode is not supported
*  and call status changes resulting in blocking of packet data connections
*  Connection id passed in the event is generic 
*  TConnMonBearerGPRS or TConnMonBearerWCDMA
*  
*  
*/
NONSHARABLE_CLASS( CConnMonPacketDataUnavailable ) : 
public CConnMonEventBase
    {
    public: // constructors and destructor
        /**
        * Constructor
        * @param aConnectionId The id of the connection,
        *                      TConnMonBearerGPRS or TConnMonBearerWCDMA
        */
        CConnMonPacketDataUnavailable( const TUint aConnectionId );

        /**
        * Destructor
        */
        virtual ~CConnMonPacketDataUnavailable();
    };    

/**
*  CConnMonPacketDataAvailable
*  Event is triggered when packet data connections are no longer
*  being unavailable because of no dual transfer mode support and 
*  simultaneous phone call being active
*  Connection id passed in the event is generic
*  TConnMonBearerGPRS or TConnMonBearerWCDMA
*  
*  
*/
NONSHARABLE_CLASS( CConnMonPacketDataAvailable ) : 
public CConnMonEventBase
    {
    public: // constructors and destructor
        /**
        * Constructor
        * @param aConnectionId The id of the connection,
        *                      TConnMonBearerGPRS || TConnMonBearerWCDMA
        */
        CConnMonPacketDataAvailable( const TUint aConnectionId );

        /**
        * Destructor
        */
        virtual ~CConnMonPacketDataAvailable();
    };    

/**
*  CConnMonBearerInfoChange
*  Event is triggered when bearer info for the connection changes or
*  if the network mode changes e.g. from 2G to 3G.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonBearerInfoChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonBearerInfoChange( const TUint aConnectionId,
                                  const TInt aBearerInfo );
        ~CConnMonBearerInfoChange();

    public: // new methods
        /**
        * Gets the new bearer. Values are defined in TConnMonBearerInfo.
        * @return Returns the bearer value.
        */
        IMPORT_C TInt BearerInfo() const;

    private: // Data
        TInt  iBearerInfo;
    };

/**
*  CConnMonBearerGroupChange
*  Event is triggered when bearer group(s) for the connection changes.
*  
*  
*/
NONSHARABLE_CLASS( CConnMonBearerGroupChange ) : public CConnMonEventBase
    {
    public: // constructors and destructor
        CConnMonBearerGroupChange( const TUint aConnectionId,
                                   const TUint aBearerGroups1,
                                   const TUint aBearerGroups2,
                                   const TBool aInternal );
        ~CConnMonBearerGroupChange();

    public: // new methods
        /**
        * Gets the bearer groups. Values are defined in TConnMonBearerGroup.
        * @return 
        */
        IMPORT_C void BearerGroups( TUint& aBearerGroups1,
                                    TUint& aBearerGroups2 ) const;

        /**
        * Gets the information whether the current connection bearer is
        * internal or external.
        * @return Returns ETrue if the bearer is internal and EFalse if
        * it's external.
        */
        IMPORT_C TBool Internal() const;

    private: // Data
        TBool iInternal;      // ETrue == internal or EFalse == external connection
        TUint iBearerGroups1; // Contains the groups in masked form.
        TUint iBearerGroups2; // Reserved for the future
    };

//__CONNECTIONMONITOR_H
#endif
// end of file
