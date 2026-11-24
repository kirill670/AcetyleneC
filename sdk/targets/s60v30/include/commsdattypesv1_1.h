// CommsDatTypesV1_1.h
//
// Copyright (c) 2004 Symbian Ltd.  All rights reserved.
//

/**
 * @file
 * CommsDatTypesV1_1.h
 * Comms Data Type Definitions version 1.1
 * @publishedPartner
 * @prototype
 */

/*
Container classes expressing Symbian OS Comms Data Types that can be stored in the Comms Repository

Type Definitions are version controlled.  New versions may be introduced from time to time.
Then older versions are marked as deprecated and given a planned removal date.

This version introduced with Release 9.1
*/

#if (!defined COMMSDATTYPESV1_1_H)
#define       COMMSDATTYPESV1_1_H


#include "Metadatabase.h"
#include "CommsDatTypeInfoV1_1.h"
#include "CommsDatUtils.h"

namespace CommsDat
/*

*/
{


///////////////////////////////////////////////////////////////////////////////////////////
// COMMSDAT RECORD BASE CLASS
// Contains fields common to all records
//

class CCDRecordBase : public CMDBRecordBase
/**
Base class for wrapper containers for supported CommsDat recordtypes
Alternatively the class CMDBGenericRecord can be used to express any record.
@publishedAll
@prototype
*/
	{
	public:

		IMPORT_C CCDRecordBase(TMDBElementId aElementId);

		IMPORT_C static CMDBRecordBase* RecordFactoryL(TMDBElementId);
		
		IMPORT_C static CMDBRecordBase* CreateCopyRecordL(CMDBRecordBase& aCopyFromRecord);
	
	protected:

		EXP_DATA_VTABLE
			
	public:

		// Element members
        /*
        User-defined numeric tag for this record.  Should be unique in this table
        */
		CMDBField<TInt>	 iRecordTag;    
		/*
        User-defined name for this record.  Should be unique in this table
        */
        CMDBField<TDesC> iRecordName;   

	private:

        CCDRecordBase(){}
	};




//////////////////////////////////////////////////////////////
// BASE CLASS FOR ALL SERVICE RECORDS
// Contains fields common to all service records
//
/**
@publishedAll
@prototype
*/
class CCDServiceRecordBase : public CCDRecordBase
	{
	public:
		// Constructor

		CCDServiceRecordBase();
		CCDServiceRecordBase(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	protected:

		DATA_VTABLE
    
   	public:

		// Field Declarations shared by all Service Records
		CMDBField<TBool>	iServiceEnableLlmnr;
	
	private:
	
	    static const SRecordTypeInfo iRecordInfo[];
	};



//////////////////////////////////////////////////////////////
// BASE CLASS FOR ALL BEARER RECORDS
// Contains fields common to all bearer records
//
/**
@publishedAll
@prototype
*/
class CCDBearerRecordBase : public CCDRecordBase
	{
	public:

		// Constructor
		CCDBearerRecordBase();
		CCDBearerRecordBase(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	protected:

		DATA_VTABLE

    public:

		// Field Declarations shared by all Bearer Records
        CMDBField<TDesC>					iBearerAgent;

	private:

        static const SRecordTypeInfo iRecordInfo[];
	};



class CCDIAPRecord;

//////////////////////////////////////////////////////////////////////////////
// 02/  CONNECTION PREFERENCES RECORD
//
// Forward declaration
/**
@publishedAll
@prototype
*/
class CCDConnectionPrefsRecord : public CCDRecordBase
	{
	public :
		CCDConnectionPrefsRecord();
		CCDConnectionPrefsRecord(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}
        
        DATA_VTABLE
        
	public :
		// Member Elements
		CMDBField<TUint32>		        iRanking;
		CMDBField<TCommDbConnectionDirection>		        iDirection;
		CMDBField<TUint32>		        iBearerSet;
		CMDBField<TUint32>		        iDialogPref;
		CMDBRecordLink<CCDIAPRecord>	iDefaultIAP;

    private:
        static const SRecordTypeInfo iRecordInfo[];
	};



//Forward defines
class CCDLocationRecord;
class CCDNetworkRecord;
class CCDAgentLookupRecord;
class CCDCDMA2000PacketServiceRecord;
class CCDWAPAccessPointRecord;
class CCDAccessPointRecord;

///////////////////////////////////////////////////////////////////////////
// 03/  GLOBAL SETTINGS RECORD
//
/**
@publishedAll
@prototype
*/
class CCDGlobalSettingsRecord : public CCDRecordBase
	{
	public :

		// Constructor
		CCDGlobalSettingsRecord();
		CCDGlobalSettingsRecord(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

		DATA_VTABLE
		
	 public:
		CMDBRecordLink<CCDWAPAccessPointRecord>		                        iWAPAccessPoint;
		CMDBField<TUint32>                                                  iMaxConnectionAttempts;
		CMDBField<TUint32>                                                  iMaxRedialAttempts;

		CMDBField<TUint32>                                                  iSMSBearer;
		CMDBField<TUint32>                                                  iSMSReceiveMode;

		CMDBField<TUint32>                                                  iGPRSAttachMode;
		CMDBField<TUint32>                                                  iAcceptIncomingGPRS;
		CMDBField<TUint32>                                                  iGPRSClassCBearer;
		
		CMDBRecordLink<CCDBearerRecordBase>                                 iModemForDataAndFax;
		CMDBRecordLink<CCDBearerRecordBase>                                 iModemForPhoneServicesAndSMS;

		CMDBRecordLink<CCDLocationRecord>                                   iLocationForDataAndFax;
		CMDBRecordLink<CCDLocationRecord>                                   iLocationForPhoneServicesAndSMS;
		
		CMDBField<TUint32>							                        iMaxMBufHeap;
		CMDBRecordLink<CCDAgentLookupRecord>                                iDefaultAgent;

		CMDBRecordLink<CCDNetworkRecord>                                    iDefaultNetwork;

		CMDBField<TDesC>                                                    iBearerAvailabilityCheckTSY;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMAOPCapability;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMASimIPMaxNumNai;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMASimIPMaxNaiLength;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMASimIPMaxSSLength;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMASimIPAuthSupported;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMAMIPMaxNumNai;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMAMIPMaxNaiLength;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMAMIPMaxMNAAASSLength;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMAMIPMNAAAAuthAlgorithm;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMAMIPMaxMNHASSLength;
		CMDBRecordLink<CCDCDMA2000PacketServiceRecord>						iCDMAMIPMNHAAuthAlgorithm;
		
		CMDBRecordLink<CCDAccessPointRecord>								iDefaultSnap;
		CMDBField<TBool>													iPromptForSnap;

	private:
	
		static const SRecordTypeInfo iRecordInfo[];
	};



///////////////////////////////////////////////////////////////////////////
// 04/  NETWORK RECORD
//
/**
@publishedAll
@prototype
*/
class CCDNetworkRecord : public CCDRecordBase
	{
	public :

		CCDNetworkRecord();
		CCDNetworkRecord(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

    	DATA_VTABLE

	public:
       		CMDBField<TDesC>		    iHostName;

	private:

		static const SRecordTypeInfo iRecordInfo[];

	};



////////////////////////////////////////////////////////////////////////
//  05/  LOCATION RECORD
//
/**
@publishedAll
@prototype
*/
class CCDLocationRecord : public CCDRecordBase
	{
	public :

		// Constructors
		CCDLocationRecord();
		CCDLocationRecord(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

		DATA_VTABLE


	public:
		// MemberData
		CMDBField<TDesC>	        iIntlPrefixCode;
		CMDBField<TDesC>	        iNatPrefixCode;
		CMDBField<TDesC>		    iNatCode;
		CMDBField<TDesC>		    iAreaCode;
		CMDBField<TDesC>		    iDialOutCode;
		CMDBField<TDesC>	        iDisableCallWaitingCode;
		CMDBField<TBool>		iMobile;
		CMDBField<TBool>		iUsePulseDial;
		CMDBField<TBool>	    iWaitForDialTone;
		CMDBField<TUint32>	    iPauseAfterDialOut;

    private:

		static const SRecordTypeInfo iRecordInfo[];
	};




//////////////////////////////////////////////////////////////////////////////////////
// 06/  IAP RECORD
//
/**
@publishedAll
@prototype
*/
class CCDIAPRecord : public CCDRecordBase
	{
	public:

		CCDIAPRecord();
		CCDIAPRecord(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}
    
    	DATA_VTABLE

	public:

		// Member Data
		CMDBField<TDesC>                        iServiceType;
		CMDBRecordLink<CCDServiceRecordBase>	iService;
		CMDBField<TDesC>                        iBearerType;
		CMDBRecordLink<CCDBearerRecordBase>	    iBearer;
		CMDBRecordLink<CCDNetworkRecord>	    iNetwork;
		CMDBField<TUint32>	                    iNetworkWeighting;
		CMDBRecordLink<CCDLocationRecord>	    iLocation;

    private:
    
	    static const SRecordTypeInfo iRecordInfo[];
	};



//////////////////////////////////////////////////////////////////////////////////////
// 07/  WAP ACCESS POINT RECORD
//
/**
@publishedAll
@prototype
*/
class CCDWAPAccessPointRecord : public CCDRecordBase
	{
	public:
	
		CCDWAPAccessPointRecord();
		CCDWAPAccessPointRecord(TMDBElementId aElementId);

		const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

		DATA_VTABLE        

	public :

		// Member Elements
		CMDBField<TDesC>    iWAPCurrentBearer;
		CMDBField<TDesC>    iWAPStartPage;

    private:
    
		static const SRecordTypeInfo iRecordInfo[];
	};


//Forward declaration
class CCDChargecardRecord;

/////////////////////////////////////////////////////////////////////////////////////
// 08/  DIAL OUT ISP SERVICE RECORD
//
/**
@publishedAll
@prototype
*/
class CCDDialOutISPRecord : public CCDServiceRecordBase
	{

	public:

		CCDDialOutISPRecord();

		CCDDialOutISPRecord(TMDBElementId aId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}


	public:

		// Member Data

		CMDBField<TDesC>	                        iDescription;
		CMDBField<TUint32>	                    iType;
		CMDBField<TDesC>	                        iDefaultTelNum;
		CMDBField<TBool>	                    iDialResolution;
		CMDBRecordLink<CCDChargecardRecord>	    iChargecard;
		CMDBField<TBool>	                    iUseLoginScript;
		CMDBField<TDesC>	                        iLoginScript;
		CMDBField<TBool>	                    iPromptForLogin;
		CMDBField<TDesC>	                        iLoginName;
		CMDBField<TDesC>	                        iLoginPass;
		CMDBField<TBool>	                    iDisplayPct;
		CMDBField<TDesC> 	                    iIfParams;
		CMDBField<TDesC>	                        iIfNetworks;
		CMDBField<TBool>	                    iIfPromptForAuth;
		CMDBField<TDesC>	                        iIfAuthName;
		CMDBField<TDesC>	                        iIfAuthPass;
		CMDBField<TUint32>	                    iIfAuthRetries;
		CMDBField<TBool>	                    iIfCallbackEnabled;
		CMDBField<TUint32>	                    iIfCallbackType;
		CMDBField<TDesC8>	                        iIfCallbackInfo;
		CMDBField<TUint32>	                    iCallbackTimeout;
		CMDBField<TBool>	                    iIfServerMode;
		CMDBField<TBool>	                    iIpAddrFromServer;
		CMDBField<TDesC>	                        iIpAddr;
		CMDBField<TDesC>	                        iIpNetMask;
		CMDBField<TDesC>	                        iIpGateway;
		CMDBField<TBool>	                    iIpDnsAddrFromServer;
		CMDBField<TDesC>	            iIpNameServer1;
		CMDBField<TDesC>	            iIpNameServer2;
		CMDBField<TBool>	        iIp6DnsAddrFromServer;
		CMDBField<TDesC>	            iIp6NameServer1;
		CMDBField<TDesC>	            iIp6NameServer2;
		CMDBField<TDesC>	        iIpAddrLeaseValidFrom;
		CMDBField<TDesC>	        iIpAddrLeaseValidTo;
		CMDBField<TDesC>	    iConfigDaemonManagerName;
		CMDBField<TDesC>	            iConfigDaemonName;
		CMDBField<TBool>	        iEnableIpHeaderComp;
		CMDBField<TBool>	        iEnableLcpExtension;
		CMDBField<TBool>	        iDisablePlainTextAuth;
		CMDBField<TBool>	                iEnableSwComp;
		CMDBField<TUint32>	                iBearerName;
		CMDBField<TUint32>	                iBearerSpeed;
		CMDBField<TUint32>	                    iBearerCe;
		CMDBField<TDesC8>	                iInitString;
		CMDBField<TUint32>	                iBearerType;
		CMDBField<TUint32>	            iChannelCoding;
		CMDBField<TUint32>	                        iAiur;
		CMDBField<TUint32>	        iRequestedTimeSlots;
		CMDBField<TUint32>	            iMaximumTimeSlots;
		CMDBField<TUint32>	            iBearerService;
		CMDBField<TUint32>	            iBearerProtocol;
		CMDBField<TUint32>	                iRlpVersion;
		CMDBField<TUint32>	                    iIwfToMs;
		CMDBField<TUint32>	                    iMsToIwf;
		CMDBField<TUint32>	                    iAckTimer;
		CMDBField<TUint32>	    iRetransmissionAttempts;
		CMDBField<TUint32>	            iResequencePeriod;
		CMDBField<TUint32>	            iV42Compression;
		CMDBField<TUint32>	                iV42Codewords;
		CMDBField<TUint32>	                iV42MaxLength;
		CMDBField<TUint32>	                iAsymmetry;
		CMDBField<TBool>	            iUserInitUpgrade;
		CMDBField<TBool>	                    iUseEdge;


    private:
    
    	static const SRecordTypeInfo iRecordInfo[];
    };




//////////////////////////////////////////////////////////////////////////////////////
// 09/  DIAL IN ISP RECORD
//
/**
@publishedAll
@prototype
*/
class CCDDialInISPRecord : public CCDServiceRecordBase
	{
	public:
		CCDDialInISPRecord();

		CCDDialInISPRecord(TMDBElementId aId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}


	public:

		// Member Data
		CMDBField<TDesC>	            iDescription;
		CMDBField<TUint32>	                    iType;
		CMDBField<TBool>	        iUseLoginScript;
		CMDBField<TDesC>	            iLoginScript;
		CMDBField<TUint32>	        iAuthentication;
		CMDBField<TUint32>	        iIfAuthRetries;
		CMDBField<TDesC>	                iIfParams;
		CMDBField<TDesC>	            iIfNetworks;
		CMDBField<TBool>	        iIpAddrFromServer;
		CMDBField<TDesC>	                iIpAddr;
		CMDBField<TDesC>	            iIpNetMask;
		CMDBField<TDesC>	            iIpGateway;
		CMDBField<TBool>	    iIpDnsAddrFromServer;
		CMDBField<TDesC>	        iIpNameServer1;
		CMDBField<TDesC>	        iIpNameServer2;
		CMDBField<TBool>	    iIp6DnsAddrFromServer;
		CMDBField<TDesC>	        iIp6NameServer1;
		CMDBField<TDesC>	        iIp6NameServer2;
		CMDBField<TBool>	    iEnableIpHeaderComp;
		CMDBField<TBool>	    iEnableLcpExtension;
		CMDBField<TBool>	    iDisablePlainTextAuth;
		CMDBField<TBool>	            iEnableSwComp;
		CMDBField<TUint32>	            iBearerName;
		CMDBField<TUint32>	            iBearerSpeed;
		CMDBField<TUint32>	                iBearerCe;
		CMDBField<TDesC8>	            iInitString;
		CMDBField<TBool>	                iUseEdge;


    private:
	
		static const SRecordTypeInfo iRecordInfo[];
	};



/////////////////////////////////////////////////////////////////////////////////////
//  0A/  LAN Service Record
//
/**
@publishedAll
@prototype
*/
class CCDLANServiceRecord : public CCDServiceRecordBase
	{
	public:

		CCDLANServiceRecord();

		CCDLANServiceRecord(TMDBElementId aElementId);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

		DATA_VTABLE


	public:

		// Member Data
		CMDBField<TDesC>	                iIfNetworks;
		CMDBField<TDesC>	                iIpNetmask;
		CMDBField<TDesC>	                iIpGateway;
		CMDBField<TBool>	                iIpAddrFromServer;
		CMDBField<TDesC>	                iIpAddr;
		CMDBField<TBool>	                iIpDnsAddrFromServer;
		CMDBField<TDesC>	                iIpNameServer1;
		CMDBField<TDesC>	                iIpNameServer2;
		CMDBField<TBool>	                iIp6DnsAddrFromServer;
		CMDBField<TDesC>	                iIp6NameServer1;
		CMDBField<TDesC>	                iIp6NameServer2;
		CMDBField<TDesC>	                iIpAddrLeaseValidFrom;
		CMDBField<TDesC>	                iIpAddrLeaseValidTo;
		CMDBField<TDesC>	                iConfigDaemonManagerName;
		CMDBField<TDesC>	                iConfigDaemonName;
		CMDBField<TDesC>	                iServiceExtensionTableName;
		CMDBRecordLink<TUint32>	            iServiceExtensionTableRecordId;
	
    private:
	
		static const SRecordTypeInfo iRecordInfo[];
	};



//////////////////////////////////////////////////////////////////////////////////////
// 0B/  WLAN SERVICE EXTENSION RECORD
//
/**
@internalComponent
@prototype
*/
class CCDWLANServiceExtRecord : public CCDRecordBase
	{
	public:

		CCDWLANServiceExtRecord();

		CCDWLANServiceExtRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:

		// Member Data

		CMDBField<TUint32>	        iServiceConnectionMode;
		CMDBField<TDesC>	        iServiceSSID;
		CMDBField<TUint32>	        iServiceChannelId;
		CMDBField<TUint32>	        iServiceSecurityMode;
		CMDBField<TDesC>	        iServiceWepKey1;
		CMDBField<TDesC>	        iServiceWepKey2;
		CMDBField<TDesC>	        iServiceWepKey3;
		CMDBField<TDesC>	        iServiceWepKey4;
		CMDBField<TUint32>	        iServiceDefaultWepKey;
		CMDBField<TUint32>          iServiceAuthenticationMode;
		CMDBField<TDesC>	        iServiceWpaPreshareKey;
		CMDBField<TUint32>	        iServiceWpaKeyLength;
		CMDBField<TDesC>	        iServiceEapList;
		CMDBField<TUint32>          iServiceWpaPreshareKeyUsed;


    private:
    
    	static const SRecordTypeInfo iRecordInfo[];
	};



//////////////////////////////////////////////////////////////////////////////////////
// 0C/  VPN SERVICE RECORD
//
/**
@publishedAll
@prototype
*/
class CCDVPNServiceRecord : public CCDServiceRecordBase
	{
	public:
		CCDVPNServiceRecord();

		CCDVPNServiceRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:

		// Member Data
		CMDBField<TDesC>	                iServicePolicy;
		CMDBRecordLink<CCDIAPRecord>	    iServiceIAP;
		CMDBRecordLink<CCDNetworkRecord>	iServiceNetwork;

    private:
    
    	static const SRecordTypeInfo iRecordInfo[];
	};



//////////////////////////////////////////////////////////////////////////////////////
// 0F/  CDMA2000 PACKETSERVICE TABLE RECORD
//
/**
@publishedAll
@prototype
*/
class CCDCDMA2000PacketServiceRecord : public CCDServiceRecordBase
	{
	public:

		CCDCDMA2000PacketServiceRecord();

		CCDCDMA2000PacketServiceRecord(TMDBElementId aElementId);
		  
		const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}
        
        DATA_VTABLE
        
	public:

		CMDBField<TUint32>	            iCDMAFchMux;
		CMDBField<TUint32>	            iCDMASchMux;
		CMDBField<TDesC>	                iIwfName;
		CMDBField<TUint32>	        iServiceOption;
		CMDBField<TUint32>	                iPdpType;
		CMDBField<TDesC>	            iPdpAddress;
		CMDBField<TUint32>	        iReqFwdPriority;
		CMDBField<TUint32>	        iReqRevPriority;
		CMDBField<TUint32>   	    iReqFwdBitrate;
		CMDBField<TUint32>   	    iReqRevBitrate;
		CMDBField<TUint32>	            iReqFwdLoss;
		CMDBField<TUint32>	            iReqRevLoss;
		CMDBField<TUint32>	        iReqFwdMaxdelay;
		CMDBField<TUint32>	        iReqRevMaxdelay;
		CMDBField<TUint32>	        iMinFwdBitrate;
		CMDBField<TUint32>	        iMinRevBitrate;
		CMDBField<TUint32>	        iAccptFwdLoss;
		CMDBField<TUint32>	        iAccptRevLoss;
		CMDBField<TUint32>	        iAccptFwdMaxdelay;
		CMDBField<TUint32>	        iAccptRevMaxdelay;
		CMDBField<TBool>	        iDataCompression;
		CMDBField<TBool>	        iHeaderCompression;
		CMDBField<TBool>	        iAnonymousAccess;
		CMDBField<TDesC>        	    iIfParams;
		CMDBField<TDesC>	            iIfNetworks;
		CMDBField<TBool>	        iIfPromptForAuth;
		CMDBField<TDesC>	            iIfAuthName;
		CMDBField<TDesC>	            iIfAuthPass;
		CMDBField<TUint32>	            iAuthRetries;
		CMDBField<TDesC>	            iIpNetMask;
		CMDBField<TDesC>	            iIpGateway;
		CMDBField<TBool>	    iIpAddrFromServer;
		CMDBField<TDesC>	                iIpAddr;
		CMDBField<TBool>	    iIpDNSAddrFromServer;
		CMDBField<TDesC>	        iIpNameServer1;
		CMDBField<TDesC>	        iIpNameServer2;
		CMDBField<TBool>	iIp6DNSAddrFromServer;
		CMDBField<TDesC>	        iIp6NameServer1;
		CMDBField<TDesC>	        iIp6NameServer2;
		CMDBField<TDesC>	iIpAddrLeaseValidFrom;
		CMDBField<TDesC>	    iIpAddrLeaseValidTo;
		CMDBField<TDesC>	iConfigDaemonManagerName;
		CMDBField<TDesC>	    iConfigDaemonName;
		CMDBField<TBool>	    iEnableLCPExtension;
		CMDBField<TBool>	iDisablePlainTextAuth;
		CMDBField<TUint32>	                iApType;
		CMDBField<TUint32>	    iQosWarningTimeout;
		CMDBField<TUint32>	                iRlpMode;
		CMDBField<TUint32>	                iNAIType;
		CMDBField<TUint32>	    iSimIPAuthAlgorithm;
		CMDBField<TUint32>	    iSimIPPapSSHandle;
		CMDBField<TUint32>	    iSimIPChapSSHandle;
		CMDBField<TUint32>	                iMIPTBit;
		CMDBField<TDesC>	        iMIPHomeAddress;
		CMDBField<TDesC>	    iMIPPrimaryHomeAgent;
		CMDBField<TDesC>	iMIPSecondaryHomeAgent;
		CMDBField<TUint32>	iMIPMnAaaAuthAlgorithm;
		CMDBField<TBool>	iMIPMnAaaSpiIndicator;
		CMDBField<TUint32>	            iMIPMnAaaSpi;
		CMDBField<TUint32>	iMIPMnHaAuthAlgorithm;
		CMDBField<TBool>	    iMIPMnHaSpiIndicator;
		CMDBField<TUint32>	            iMIPMnHaSpi;
		CMDBField<TDesC>	        iMIPMnAaaSsData;
		CMDBField<TDesC>	        iMIPMnHaSsData;
		CMDBField<TUint32>	    iServiceEnableSwComp;
		CMDBField<TBool>	iServiceIfExternIpConfigAlwaysRejectAuth;
		CMDBField<TBool>	    iEnableIpHeaderComp;
		CMDBField<TBool>	    iCDMAMobileIP;
		CMDBField<TUint32>	    iCDMAMobileIPTimeout;
		CMDBField<TDesC>	    iCDMAHomeAgentAddress;
		
    private:
        
        static const SRecordTypeInfo iRecordInfo[];
	};



/////////////////////////////////////////////////////////////////////////////////////////
// 10/  WCDMA Packet Service Record
//
/**
@publishedAll
@prototype
*/
class CCDWCDMAPacketServiceRecord : public CCDServiceRecordBase
	{
	public:

	    CCDWCDMAPacketServiceRecord();

		CCDWCDMAPacketServiceRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}


	public:

		// Member Data
		CMDBField<TDesC>	                        iGPRSAPN;
		CMDBField<TUint32>	                iGPRSPDPType;
		CMDBField<TDesC>	                iGPRSPDPAddress;
		CMDBField<TUint32>	            iGPRSReqPrecedence;
		CMDBField<TUint32>	                iGPRSReqDelay;
		CMDBField<TUint32>	            iGPRSReqReliability;
		CMDBField<TUint32>	        iGPRSReqPeakThroughput;
		CMDBField<TUint32>	        iGPRSReqMeanThroughput;
		CMDBField<TUint32>	            iGPRSMinPrecedence;
		CMDBField<TUint32>	                iGPRSMinDelay;
		CMDBField<TUint32>	            iGPRSMinReliability;
		CMDBField<TUint32>	        iGPRSMinPeakThroughput;
		CMDBField<TUint32>	        iGPRSMinMeanThroughput;
		CMDBField<TBool>	        iGPRSDataCompression;
		CMDBField<TBool>	        iGPRSHeaderCompression;
		CMDBField<TBool>	                iGPRSUseEdge;
		CMDBField<TBool>	        iGPRSAnonymousAccess;
		CMDBField<TDesC>	                iGPRSIfParams;
		CMDBField<TDesC>	                iGPRSIfNetworks;
		CMDBField<TBool>	        iGPRSIfPromptForAuth;
		CMDBField<TDesC>	                iGPRSIfAuthName;
		CMDBField<TDesC>	                iGPRSIfAuthPass;
		CMDBField<TUint32>	            iGPRSIfAuthRetries;
		CMDBField<TDesC>	                iGPRSIPNetMask;
		CMDBField<TDesC>	                iGPRSIPGateway;
		CMDBField<TBool>  	        iGPRSIPAddrFromServer;
		CMDBField<TDesC>	                    iGPRSIPAddr;
		CMDBField<TBool>	    iGPRSIPDNSAddrFromServer;
		CMDBField<TDesC>	            iGPRSIPNameServer1;
		CMDBField<TDesC>	            iGPRSIPNameServer2;
		CMDBField<TBool>	    iGPRSIP6DNSAddrFromServer;
		CMDBField<TDesC>	            iGPRSIP6NameServer1;
		CMDBField<TDesC>	            iGPRSIP6NameServer2;
		CMDBField<TDesC>	    iGPRSIPAddrLeaseValidFrom;
		CMDBField<TDesC>	        iGPRSIPAddrLeaseValidTo;
		CMDBField<TDesC>	iGPRSConfigDaemonManagerName;
		CMDBField<TDesC>	        iGPRSConfigDaemonName;
		CMDBField<TBool>	        iGPRSEnableLCPExtension;
		CMDBField<TBool>	    iGPRSDisablePlainTextAuth;
		CMDBField<TUint32>            	        iGPRSAPType;
		CMDBField<TUint32>	        iGPRSQOSWarningTimeOut;
		

    public:

        static const SRecordTypeInfo iRecordInfo[];
    };

/**
@publishedAll
@prototype
*/
class CCDOutgoingGprsRecord : public CCDWCDMAPacketServiceRecord
	{
	public:
		CCDOutgoingGprsRecord(TMDBElementId aElementId);

		DATA_VTABLE
	};

/**
@publishedAll
@prototype
*/
class CCDIncomingGprsRecord : public CCDWCDMAPacketServiceRecord
	{
	public:
		CCDIncomingGprsRecord(TMDBElementId aElementId);

		DATA_VTABLE
	};

/////////////////////////////////////////////////////////////////////////////////////////
// 11/  Default CDMA2000 Settings Table
//
/**
@publishedPartner
@prototype
*/
class CCDDefaultCDMA2000SettingsRecord : public CCDRecordBase
	{
	public:
		CCDDefaultCDMA2000SettingsRecord();

		CCDDefaultCDMA2000SettingsRecord(TMDBElementId aId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public :

		// Member Elements

		CMDBField<TUint32>		    iUsage;
		CMDBField<TDesC>		        iIwfName;
		CMDBField<TUint32>	    iServiceOption;
		CMDBField<TUint32>		        iPdpType;
		CMDBField<TDesC>		    iPdpAddress;
		CMDBField<TUint32>	    iReqFwdPriority;
		CMDBField<TUint32>	    iReqRevPriority;
		CMDBField<TUint32>		    iReqFwdBitrate;
		CMDBField<TUint32>		    iReqRevBitrate;
		CMDBField<TUint32>		    iReqFwdLoss;
		CMDBField<TUint32>		    iReqRevLoss;
		CMDBField<TUint32>		iReqFwdMaxdelay;
		CMDBField<TUint32>		iReqRevMaxdelay;
		CMDBField<TUint32>		    iMinFwdBitrate;
		CMDBField<TUint32>		    iMinRevBitrate;
		CMDBField<TUint32>	    	iAccptFwdLoss;
		CMDBField<TUint32>		    iAccptRevLoss;
		CMDBField<TUint32>		iAccptFwdMaxdelay;
		CMDBField<TUint32>		iAccptRevMaxdelay;
		CMDBField<TBool>		iDataCompression;
		CMDBField<TBool>		iHeaderCompression;
		CMDBField<TBool>		iAnonymousAccess;
		CMDBField<TUint32>	        	iCDMAOperationMode;
		CMDBField<TUint32>		iCDMAMobileIpMaxNumRetry;
		CMDBField<TUint32>		iCDMAMobileIpFirstRetryTimeout;
		CMDBField<TUint32>		iCDMAMobileIpReregThreshold;
		CMDBField<TBool>		iEnableLLMNR; 
		CMDBField<TBool>	    iEnableIpHeaderComp;
		CMDBField<TBool>	    iCDMAMobileIP;
		CMDBField<TDesC>	    iHomeAgentAddress;
		CMDBField<TUint32>	    iCDMAMobileIPTimeout; 
		CMDBField<TUint32>      iCDMAFchMux;
		CMDBField<TUint32>      iCDMASchMux;
		
    private:
    
    	static const SRecordTypeInfo iRecordInfo[];
	};

//////////////////////////////////////////////////////////////////////////////////////
// 12/  DEFAULT WCDMA RECORD
//
/**
@publishedPartner
@prototype
*/
class CCDDefaultWCDMARecord : public CCDRecordBase
	{
	public:
		CCDDefaultWCDMARecord();

		CCDDefaultWCDMARecord(TMDBElementId aId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public :

		// Member Elements

		CMDBField<TUint32>		    iUsage;
		CMDBField<TDesC>		        iAPN;
		CMDBField<TUint32>		    iPdpType;
		CMDBField<TDesC>		    	iPdpAddress;
		CMDBField<TUint32>		    iPrecedence;
		CMDBField<TUint32>	    	iDelay;
		CMDBField<TUint32>	    	iReliability;
		CMDBField<TUint32>	    	iPeakThroughput;
		CMDBField<TUint32>	    	iMeanThroughput;
		CMDBField<TUint32>		    iMinPrecedence;
		CMDBField<TUint32>	    	iMinDelay;
		CMDBField<TUint32>	    	iMinReliability;
		CMDBField<TUint32>	    	iMinPeakThroughput;
		CMDBField<TUint32>	    	iMinMeanThroughput;
		CMDBField<TBool>			iDataCompression;
		CMDBField<TBool>			iHeaderCompression;
		CMDBField<TBool>			iUseEdge;
		CMDBField<TBool>			iAnonymousAccess;

    private:
    
    	static const SRecordTypeInfo iRecordInfo[];
	};



////////////////////////////////////////////////////////////////////////////
// 13/  MODEM BEARER RECORD
//
/**
@publishedAll
@prototype
*/
class CCDModemBearerRecord : public CCDBearerRecordBase
	{
	public:
	
		CCDModemBearerRecord();		
		CCDModemBearerRecord(TMDBElementId id);

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

		DATA_VTABLE
		

	public:

		// MemberData
		CMDBField<TDesC>	                        iNifName;
		CMDBField<TDesC>	                        iPortName;
		CMDBField<TDesC>	                        iTsyName;
		CMDBField<TDesC>	                        iCsyName;
		CMDBField<TUint32>	    iLastSocketActivityTimeout;
		CMDBField<TUint32>	        iLastSessionClosedTimeout;
		CMDBField<TUint32>	        iLastSocketClosedTimeout;
		CMDBField<TUint32>	                        iDataBits;
		CMDBField<TUint32>	                        iStopBits;
		CMDBField<TUint32>	                        iParity;
		CMDBField<TUint32>	                            iRate;
		CMDBField<TUint32>	                    iHandshaking;
		CMDBField<TUint32>	                    iSpecialRate;
		CMDBField<TUint32>	                        iXonChar;
		CMDBField<TUint32>	                        iXoffChar;
		CMDBField<TUint32>	                    iFaxClassPref;
		CMDBField<TUint32>	                    iSpeakerPref;
		CMDBField<TUint32>	                iSpeakerVolPref;
		CMDBField<TDesC8>	                iModemInitString;
		CMDBField<TDesC8>	                iDataInitString;
		CMDBField<TDesC8>	                iFaxInitString;
		CMDBField<TDesC8>	                iIspInitString;
		CMDBField<TDesC>	                iDialPauseLength;
		CMDBField<TDesC>	                iCarrierTimeOut;
		CMDBField<TDesC>	            iAutoAnswerRingCount;
		CMDBField<TDesC>	            iSpeakerVolControlLow;
		CMDBField<TDesC>	        iSpeakerVolControlMedium;
		CMDBField<TDesC>	        iSpeakerVolControlHigh;
		CMDBField<TDesC>	                iSpeakerAlwaysOff;
		CMDBField<TDesC>	        iSpeakerOnUntilCarrier;
		CMDBField<TDesC>	                iSpeakerAlwaysOn;
		CMDBField<TDesC>	        iSpeakerOnAfterUntilCarrier;
		CMDBField<TDesC>	            iDialToneWaitModifier;
		CMDBField<TDesC>	                iCallProgress1;
		CMDBField<TDesC>	                iCallProgress2;
		CMDBField<TDesC>	                iCallProgress3;
		CMDBField<TDesC>	                iCallProgress4;
		CMDBField<TDesC>	                        iEchoOff;
		CMDBField<TDesC>	                    iVerboseText;
		CMDBField<TDesC>	                        iQuietOff;
		CMDBField<TDesC>	                        iQuietOn;
		CMDBField<TDesC>	        iDialCommandStateModifier;
		CMDBField<TDesC>	                        iOnLine;
		CMDBField<TDesC>	            iResetConfiguration;
		CMDBField<TDesC>	            iReturnToFactoryDefs;
		CMDBField<TDesC>	                iDcdOnDuringLink;
		CMDBField<TDesC>	                    iDtrHangUp;
		CMDBField<TDesC>	                    iDsrAlwaysOn;
		CMDBField<TDesC>	                iRtsCtsHandshake;
		CMDBField<TDesC>	                iXonXoffHandshake;
		CMDBField<TDesC>	                iEscapeCharacter;
		CMDBField<TDesC>	            iEscapeGuardPeriod;
		CMDBField<TDesC>	            iFaxClassInterrogate;
		CMDBField<TDesC>	                        iFaxClass;
		CMDBField<TDesC>	                    iNoDialTone;
		CMDBField<TDesC>	                            iBusy;
		CMDBField<TDesC>	                        iNoAnswer;
		CMDBField<TDesC>	                        iCarrier;
		CMDBField<TDesC>	                        iConnect;
		CMDBField<TDesC>	            iCompressionClass5;
		CMDBField<TDesC>	            iCompressionV42bis;
		CMDBField<TDesC>	                iCompressionNone;
		CMDBField<TDesC>	                    iProtocolLapd;
		CMDBField<TDesC>	                    iProtocolAlt;
		CMDBField<TDesC>	            iProtocolAltcellular;
		CMDBField<TDesC>	                    iProtocolNone;
		CMDBField<TDesC>	            iMessageCentreNumber;
		CMDBField<TUint32>	        iMessageValidityPeriod;
		CMDBField<TBool>	        iMessageDeliveryReport;
		CMDBField<TUint32>	                iMinSignalLevel;
		CMDBField<TUint32>	                        iCommRole;
		CMDBField<TDesC>	        iControlChannelPortName;
		CMDBField<TUint32>	                    iSirSettings;
		CMDBField<TDesC>	                    iBcaStack;
    
    private:
    
		static const SRecordTypeInfo iRecordInfo[];
	};






//////////////////////////////////////////////////////////////////////////////////////
// 14/  LAN BEARER RECORD
//
/**
@publishedAll
@prototype
*/
class CCDLANBearerRecord : public CCDBearerRecordBase
	{
	public:

		CCDLANBearerRecord();
		CCDLANBearerRecord(TMDBElementId aId);

		const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

		DATA_VTABLE        

	public:

    	CMDBField<TDesC>	        iLanBearerNifName;
		CMDBField<TDesC>    	    iLanBearerLddFilename;
		CMDBField<TDesC>	        iLanBearerLddName;
		CMDBField<TDesC>	        iLanBearerPddFilename;
   	    CMDBField<TDesC>          iLanBearerPddName;
		CMDBField<TDesC>	        iLanBearerPacketDriverName;
		CMDBField<TUint32>        iLastSocketActivityTimeout;
		CMDBField<TUint32>        iLastSessionClosedTimeout;
		CMDBField<TUint32>	            iLastSocketClosedTimeout;

    private:

		static const SRecordTypeInfo iRecordInfo[];
	};


//////////////////////////////////////////////////////////////////////////////////////
// 15/  VIRTUAL BEARER RECORD
//
/**
@publishedAll
@prototype
*/
class CCDVirtualBearerRecord : public CCDBearerRecordBase
	{
	public:

		CCDVirtualBearerRecord();
		CCDVirtualBearerRecord(TMDBElementId aId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:

		// Member Data
		CMDBField<TDesC>	    iVirtualBearerNifName;
		CMDBField<TUint32>	    iLastSocketActivityTimeout;
		CMDBField<TUint32>	    iLastSessionClosedTimeout;
		CMDBField<TUint32>	    iLastSocketClosedTimeout;

    private:
    
		static const SRecordTypeInfo iRecordInfo[];
	};



//////////////////////////////////////////////////////////////////////////////////////
// 16/ WAP SMS Bearer Record
//
/**
@publishedAll
@prototype
*/
class CCDWAPSMSBearerRecord : public CCDRecordBase
	{
	public:

		CCDWAPSMSBearerRecord();
		CCDWAPSMSBearerRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public :
		// Member Elements
		CMDBRecordLink<CCDWAPAccessPointRecord>   iWAPAccessPointId;
		CMDBField<TDesC>              		      iWAPGatewayAddress;
		CMDBField<TDesC>                          iWAPServiceCentreAddress;
		CMDBField<TUint8>                         iWAPWSPOption;
		CMDBField<TBool>                          iWAPSecurity;

    private:

		static const SRecordTypeInfo iRecordInfo[];
	};



////////////////////////////////////////////////////////////////////////////////////////
// 17/ WAP IP BEARER
//
/**
@publishedAll
@prototype
*/
class CCDWAPIPBearerRecord : public CCDRecordBase
	{

	public:

		CCDWAPIPBearerRecord();
		CCDWAPIPBearerRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public :

		// Member Elements
		CMDBRecordLink<CCDWAPAccessPointRecord> iWAPAccessPointId;
		CMDBField<TDesC>                        iWAPGatewayAddress;
	//	CMDBRecordLink<CCDChargecardRecord>     iWAPChargecard; 
		CMDBRecordLink<CCDIAPRecord>            iWAPIAP;
		CMDBField<TUint8>                       iWAPWSPOption;
		CMDBField<TBool>                        iWAPSecurity;
		CMDBField<TUint32>                      iWAPProxyPort;
		CMDBField<TDesC>                        iWAPProxyLoginName;
		CMDBField<TDesC>                        iWAPProxyLoginPass;


    private:
	
		static const SRecordTypeInfo iRecordInfo[];
	};




//////////////////////////////////////////////////////////////////////////////////////
// 18/  CHARGECARD RECORD
//
/**
Reading of ChargeCard Table data is protected with ECDPrivate Attribute.  
This will require additional capabilities to read.

@publishedAll
@prototype
*/
class CCDChargecardRecord : public CCDRecordBase
	{
	public:

		CCDChargecardRecord();
		CCDChargecardRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:

		// Member Elements
		CMDBField<TDesC>        iAccountNo;
		CMDBField<TDesC>              iPin;
		CMDBField<TDesC>        iLocalRule;
		CMDBField<TDesC>          iNatRule;
		CMDBField<TDesC>         iIntlRule;

    private:

		static const SRecordTypeInfo iRecordInfo[];

	};



//////////////////////////////////////////////////////////////////////////////////////
// 19/  PROXIES RECORD
//
/**
@publishedAll
@prototype
*/
class CCDProxiesRecord : public CCDRecordBase
	{
	public:

		CCDProxiesRecord();
		CCDProxiesRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public :

		// Member Elements
		CMDBRecordLink<CCDServiceRecordBase>    iService;
		CMDBField<TDesC>                        iServiceType;
		CMDBField<TBool>                        iUseProxyServer;
		CMDBField<TDesC>                        iServerName;
		CMDBField<TDesC>                        iProtocolName;
		CMDBField<TUint32>                      iPortNumber;
		CMDBField<TDesC>                        iExceptions;


    private:
    
        static const SRecordTypeInfo iRecordInfo[];
	};




//////////////////////////////////////////////////////////////////////////////////////
// 1A/  SECURE SOCKET PROTO RECORD
//
/**
@internalComponent
@prototype
*/
class CCDSecureSocketRecord : public CCDRecordBase
	{
	public:

		CCDSecureSocketRecord();
		CCDSecureSocketRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:

		// Member Data
		CMDBField<TDesC>	    iSSProtoName;
		CMDBField<TDesC>	iSSProtoLibrary;

    private:

		static const SRecordTypeInfo iRecordInfo[];
	};




//////////////////////////////////////////////////////////////////////////////////////
// 1B/ AGENTLOOKUPTABLE RECORD
//
/**
@internalComponent
@prototype
*/
class CCDAgentLookupRecord : public CCDRecordBase
	{
	public:

		CCDAgentLookupRecord();
		CCDAgentLookupRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:

		// Member Data
		CMDBField<TDesC>  	iAgentFriendlyName;
		CMDBField<TDesC>	 	iAgentFileName;


    private:
        
        static const SRecordTypeInfo iRecordInfo[];
	};
	

//////////////////////////////////////////////////////////////////////////////////////
// 1C/ PAN_SERVICE_EXTENSIONS
//
/**
@publishedAll
@prototype
*/
class CCDPANServiceExtRecord : public CCDServiceRecordBase
	{
	public:

		CCDPANServiceExtRecord();
		CCDPANServiceExtRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:

		// Member Data
		CMDBField<TUint32>  	iLocalRole;
		CMDBField<TUint32>	 	iPeerRole;
		CMDBField<TDesC>  		iPeerMACAddresses;
		CMDBField<TBool>	 	iPromptForRemoteDevices;
		CMDBField<TBool>  		iDisableSdpQuery;
		CMDBField<TBool>	 	iAllowIncoming;


    private:
        
        static const SRecordTypeInfo iRecordInfo[];
	};

class CCDSelectionPolicyRecordBase;

//////////////////////////////////////////////////////////////////////////////////////
// 1D/ ACCESS POINT RECORD
// -----------   --------------------------------------
//| ID | NAME | | ACCESS POINT (Group)ID | POLICY LINK |
//|-----------| |--------------------------------------|
//|  * |    * | |                      * |           * |
// -----------   --------------------------------------
// ID                     - Access point's unique ID.
// NAME                   - Access point's unique name.
// ACCESS POINT (Group)ID - identifies the access point's layer.
// POLICY LINK            - links to a policy record that describes bindings to the next leyer.
/**
@publishedAll
@prototype
*/
class CCDAccessPointRecord : public CCDRecordBase
	{
	public:
		CCDAccessPointRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:
		CMDBField<TUint32> iAccessPointGID;
		CMDBRecordLink<CCDSelectionPolicyRecordBase> iSelectionPolicy;

    private:
        static const SRecordTypeInfo iRecordInfo[];
	};

//////////////////////////////////////////////////////////////////////////////////////
// 1E/ SELECTION POLICY RECORD
/**
@publishedAll
@prototype
*/
class CCDSelectionPolicyRecordBase : public CCDRecordBase
	{
	public:
		DATA_VTABLE

    protected:
        CCDSelectionPolicyRecordBase(TMDBElementId aElementId);
	};

//////////////////////////////////////////////////////////////////////////////////////
// 1F/ IAP PRIORITY SELECTION POLICY RECORD
// -----------   ---------------------------------------------
//| ID | NAME | | IAP LINK 1 | IAP LINK 2 | ... | IAP LINK 15 |
//|-----------| |---------------------------------------------|
//|  * |    * | |          * |          * |   * |           * |
// -----------   ---------------------------------------------
// IAP LINK N - links to Nth IAP record.
/**
@publishedAll
@prototype
*/
class CCDIAPPrioritySelectionPolicyRecord : public CCDSelectionPolicyRecordBase
	{
    public:
		CCDIAPPrioritySelectionPolicyRecord(TMDBElementId aElementId);

		DATA_VTABLE

        const SRecordTypeInfo* GetRecordInfo(){return iRecordInfo;}

	public:
		CMDBRecordLink<CCDIAPRecord> iIap1;
		CMDBRecordLink<CCDIAPRecord> iIap2;
		CMDBRecordLink<CCDIAPRecord> iIap3;
		CMDBRecordLink<CCDIAPRecord> iIap4;
		CMDBRecordLink<CCDIAPRecord> iIap5;
		CMDBRecordLink<CCDIAPRecord> iIap6;
		CMDBRecordLink<CCDIAPRecord> iIap7;
		CMDBRecordLink<CCDIAPRecord> iIap8;
		CMDBRecordLink<CCDIAPRecord> iIap9;
		CMDBRecordLink<CCDIAPRecord> iIap10;
		CMDBRecordLink<CCDIAPRecord> iIap11;
		CMDBRecordLink<CCDIAPRecord> iIap12;
		CMDBRecordLink<CCDIAPRecord> iIap13;
		CMDBRecordLink<CCDIAPRecord> iIap14;
		CMDBRecordLink<CCDIAPRecord> iIap15;

    private:
        static const SRecordTypeInfo iRecordInfo[];
	};

} // end namespace CommsDat


#endif //COMMSDATTYPESV1_1_H
