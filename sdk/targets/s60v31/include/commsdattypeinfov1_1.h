// CommsDatTypeInfoV1_1.h
//
// Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
//

/**
 * @file
 * CommsDatTypeInfoV1_1.h
 * Comms Data Type Definitions version 1.1
 * @publishedPartner
 * @released 
 */

/*
Type info for Symbian OS Comms Data Types that can be stored in the Comms Repository

Information held here includes
- Field ID
- Field Name
- Field Value Type
- Field Max Length (for descriptors)

Type Definitions are version controlled.  New versions may be introduced from time to time.
Then older versions are marked as deprecated and given a planned removal date.

This version introduced with Release 9.1
*/

#if (!defined COMMSDATTYPEINFOV1_1_H)
#define       COMMSDATTYPEINFOV1_1_H



namespace CommsDat
{

	// TIds for each Comms Record Type


	// Internal
	const TMDBElementId KCDTIdGlobalSettingsRecord		 	  = 0x00800000; //
	const TMDBElementId KCDTIdConnectionPrefsRecord			  = 0x01000000; //

	const TMDBElementId KCDTIdNetworkRecord					  = 0x01800000; //
	const TMDBElementId KCDTIdLocationRecord				  = 0x02000000; //
	const TMDBElementId KCDTIdIAPRecord						  = 0x02800000; //

	// WAP
	const TMDBElementId KCDTIdWAPAccessPointRecord			  = 0x03000000; //

	// Service
	const TMDBElementId KCDTIdDialOutISPRecord				  = 0x03800000; //
	const TMDBElementId KCDTIdDialInISPRecord				  = 0x04000000; //
	const TMDBElementId KCDTIdLANServiceRecord				  = 0x04800000; //

	/**
	WLANServiceExtension is internal Table
	@internalComponent
	*/
	const TMDBElementId KCDTIdWLANServiceExtRecord			  = 0x05000000; //
	const TMDBElementId KCDTIdVPNServiceRecord				  = 0x05800000; //

    const TMDBElementId KCDTIdCDMA2000PacketServiceRecord	  = 0x06000000; //
	const TMDBElementId KCDTIdWCDMAPacketServiceRecord		  = 0x06800000; //
	const TMDBElementId KCDTIdOutgoingGprsRecord			  = 0x0C800000; //
	const TMDBElementId KCDTIdIncomingGprsRecord			  = 0x0D000000; //
	
	const TMDBElementId KCDTIdPANServiceExtRecord			  = 0x0D800000; //

	// Service Defaults
	const TMDBElementId KCDTIdDefaultCDMA2000SettingsRecord	  = 0x07000000; //
	const TMDBElementId KCDTIdDefaultWCDMARecord	    	  = 0x07800000; //

	// Bearer
	const TMDBElementId KCDTIdModemBearerRecord				  = 0x08000000; //
	const TMDBElementId KCDTIdLANBearerRecord				  = 0x08800000; //
	const TMDBElementId KCDTIdVirtualBearerRecord			  = 0x09000000; //

	const TMDBElementId KCDTIdWAPSMSBearerRecord			  = 0x09800000; //
	const TMDBElementId KCDTIdWAPIPBearerRecord				  = 0x0A000000; //

	const TMDBElementId KCDTIdChargecardRecord				  = 0x0A800000; //
	const TMDBElementId KCDTIdProxiesRecord					  = 0x0B000000; //
	
	/**
	SecureSocketProto is Internal Table
	@internalComponent
	*/
	const TMDBElementId KCDTIdSSProtoRecord					  = 0x0B800000; //
	/**
	Agent Lookup is Internal Table
	@internalComponent
	*/
	const TMDBElementId KCDTIdAgentLookupRecord				  = 0x0C000000; //
	
	const TMDBElementId KCDTIdAccessPointRecord	        	  = 0x0E000000; //
	const TMDBElementId KCDTIdIapPrioritySelectionPolicyRecord= 0x0E800000; //

	const TMDBElementId KCDTIdUmtsR99QoSAndOnTableRecord      = 0x0F000000; //

	/**
	EAPSecSettings is internal Table
	@internalComponent
	*/
	const TMDBElementId KCDTIdEAPSecRecord					= 0x0F800000; //
	
	/**
	TunEAPSettings is internal Table
	@internalComponent
	*/
	const TMDBElementId KCDTIdTunEAPRecord					= 0x10000000; //
	
	/**
	EAPTLSSetings is internal Table
	@internalComponent
	*/
	const TMDBElementId KCDTIdEAPTLSRecord					= 0x10800000; //
	
	/**
	LEAPSetting is internal Table
	@internalComponent
	*/
	const TMDBElementId KCDTIdLEAPRecord					= 0x11000000; //



 // Comms Record type names.- 26 in total

	#define	KCDTypeNameConnectionPrefs						_S("ConnectionPreferences")
	#define	KCDTypeNameGlobalSettings						_S("GlobalSettings")

	#define	KCDTypeNameNetwork								_S("Network")
	#define	KCDTypeNameIAP									_S("IAP")
	#define	KCDTypeNameLocation								_S("Location")

	#define	KCDTypeNameWAPAccessPoint						_S("WAPAccessPoint")

	// Service
	#define	KCDTypeNameDialOutISP							_S("DialOutISP")
	#define	KCDTypeNameDialInISP							_S("DialInISP")
	#define	KCDTypeNameLANService							_S("LANService")
	#define	KCDTypeNameWLANServiceExt						_S("WLANServiceExtensionTable")
	#define	KCDTypeNameVPNService							_S("VpnService")
	#define	KCDTypeNameOutgoingWCDMA						_S("OutgoingGPRS")
	#define	KCDTypeNameIncomingWCDMA						_S("IncomingGPRS")
	#define	KCDTypeNameCDMA2000PacketService		        _S("CDMA2000PacketServiceTable")

	#define	KCDTypeNameDefaultWCDMA							_S("DefaultGPRS")
	#define	KCDTypeNameDefaultCDMA2000Settings		        _S("DefaultCDMA2000SettingsTable")
	
	#define KCDTypeNamePANServiceExt						_S("PANServiceExtensions")

	// Bearer
	#define	KCDTypeNameModemBearer							_S("ModemBearer")
	#define	KCDTypeNameLANBearer							_S("LANBearer")
	#define	KCDTypeNameVirtualBearer						_S("VirtualBearer")

	#define	KCDTypeNameWAPSMSBearer							_S("WAPSMSBearer")
	#define	KCDTypeNameWAPIPBearer							_S("WAPIPBearer")

	// Other
	#define	KCDTypeNameChargecard							_S("Chargecard")
	#define	KCDTypeNameProxies								_S("Proxies")
	#define	KCDTypeNameSSProto								_S("SecureSocketTable")
	#define	KCDTypeNameAgentLookup							_S("AgentLookup")

	#define	KCDTypeNameService								_S("IAPService")
	#define	KCDTypeNameBearer								_S("IAPBearer")

	#define	KCDTTypeNameEAPSec								_S("EAPSecuritySettingsTable")
	#define	KCDTTypeNameTunEAP								_S("TunnelledEAPSettingsTable")
	#define	KCDTTypeNameEAPTLS								_S("EAPTLSSettingsTable")
	#define	KCDTTypeNameLEAP								_S("LEAPSettingsTable")
	
	#define	KCDNull											_S("")





///////////////////////////////////////////////////////////////////////////////////////////
// COMMSDAT RECORD BASE CLASS
// Contains fields common to all records
//

	// Element Type Ids

    /* 
    KCDTIdRecordTag - Field to contain a user-defined numeric tag for this record
    Useful for user searches and cheaper to search on a numeric tag than a string name.
    Can be null.
    This tag is not automatically connected with the record id itself,
    which is contained within the ElementId for the record and not in any field.

    @publishedAll
    */
	const TMDBElementId KCDTIdRecordTag			 = 0x00010000; 

    /*
    KCDTIdRecordName - Field to contain user-defined string tag for this record.
    Useful for user searches.
    Can be null, but for BC behaviour with Commdb should be present.
    
    It would be more efficient to use the RecordTag field instead for user searching
    as it is quicker and cheaper to search for a number than for a string.

    @publishedAll
    */
    const TMDBElementId KCDTIdRecordName		 = 0x00020000; 


	// Element Type Names
	#define	KCDTypeNameRecordTag				_S("Id")
	#define	KCDTypeNameRecordName		        _S("Name")



//////////////////////////////////////////////////////////////
// BASE CLASS FOR ALL SERVICE RECORDS
// Contains fields common to all service records
//
	const TMDBElementId KCDTIdServiceEnableLlmnr                = 0x007C0000;
	
	#define	KCDTypeNameServiceEnableLlmnr		                _S("EnableLLMNR")


//////////////////////////////////////////////////////////////
// BASE CLASS FOR ALL BEARER RECORDS
// Contains fields common to all bearer records
//
    const TMDBElementId KCDTIdBearerAgent		    = 0x007C0000;
	const TMDBElementId KCDTIdBearerTechnology  	= 0x007B0000;

    #define	KCDTypeNameBearerAgent		            _S("Agent")
    #define	KCDTypeNameBearerTechnology            _S("BearerTechnology")
///////////////////////////////////////////////////////////////////////////
// 008/  GLOBAL SETTINGS RECORD
//

	// Element Type IDs
	const TMDBElementId KCDTIdMaxConnectionAttempts         = 0x00830000;
	const TMDBElementId KCDTIdMaxRedialAttempts             = 0x00840000;
	const TMDBElementId KCDTIdSMSBearer						= 0x00850000;
	const TMDBElementId KCDTIdSMSReceiveMode				= 0x00860000;
	const TMDBElementId KCDTIdGPRSAttachMode                = 0x00870000;
	const TMDBElementId KCDTIdAcceptIncomingGPRS            = 0x00880000;
	const TMDBElementId KCDTIdGPRSClassCBearer				= 0x00890000;
	const TMDBElementId KCDTIdModemDataFax                  = 0x008A0000;
	const TMDBElementId KCDTIdModemPhoneServicesSMS			= 0x008B0000;
	const TMDBElementId KCDTIdLocationDataFax               = 0x008C0000;
	const TMDBElementId KCDTIdLocationPhoneServicesSMS		= 0x008D0000;
	const TMDBElementId KCDTIdMaxMBufHeap					= 0x008E0000;
	const TMDBElementId KCDTIdDefaultAgent					= 0x008F0000;
	const TMDBElementId KCDTIdDefaultNetwork				= 0x00900000;
	const TMDBElementId KCDTIdBearerAvailabilityCheckTSY	= 0x00910000;
	const TMDBElementId KCDTIdCDMAOPCapability					= 0x00920000;
	const TMDBElementId KCDTIdCDMASimIPMaxNumNai				= 0x00930000;
	const TMDBElementId KCDTIdCDMASimIPMaxNaiLength				= 0x00940000;
	const TMDBElementId KCDTIdCDMASimIPMaxSSLength				= 0x00950000;
	const TMDBElementId KCDTIdCDMASimIPAuthSupported			= 0x00960000;
	const TMDBElementId KCDTIdCDMAMIPMaxNumNai					= 0x00970000;
	const TMDBElementId KCDTIdCDMAMIPMaxNaiLength				= 0x00980000;
	const TMDBElementId KCDTIdCDMAMIPMaxMNAAASSLength			= 0x00990000;
	const TMDBElementId KCDTIdCDMAMIPMNAAAAuthAlgorithm			= 0x009A0000;
	const TMDBElementId KCDTIdCDMAMIPMaxMNHASSLength			= 0x009B0000;
	const TMDBElementId KCDTIdCDMAMIPMNHAAuthAlgorithm		= 0x009C0000;
	const TMDBElementId KCDTIdGlobalWapAcessPoint			= 0x009D0000;
	const TMDBElementId KCDTIdDefaultSnap					= 0x009E0000;
	const TMDBElementId KCDTIdPromptForSnap					= 0x009F0000;

	// Element Type names .
	#define	KCDTypeNameMaxRedialAttempts			_S("RedialAttempts")
	#define	KCDTypeNameSMSBearer					_S("SmsBearer")
	#define	KCDTypeNameSMSReceiveMode				_S("SmsReceiveMode")
	#define	KCDTypeNameGPRSAttachMode				_S("GPRSAttachMode")
	#define	KCDTypeNameAcceptIncomingGPRS			_S("AcceptIncomingGprs")
	#define	KCDTypeNameGPRSClassCBearer				_S("GPRSClassCBearer")
	#define	KCDTypeNameMaxConnectionAttempts		_S("ConnectionAttempts")
	#define	KCDTypeNameModemDataFax					_S("ModemForDataAndFax")
	#define	KCDTypeNameModemPhoneServicesSMS		_S("ModemForPhoneServicesAndSMS")
	#define	KCDTypeNameLocationDataFax				_S("LocationForDataAndFax")
	#define	KCDTypeNameLocationPhoneServicesSMS		_S("LocationForPhoneServicesAndSMS")
	#define	KCDTypeNameMaxMBufHeap					_S("MaxMBufHeap")
	#define	KCDTypeNameDefaultAgent					_S("DefaultAgent")
	#define	KCDTypeNameDefaultNetwork				_S("DefaultNetwork")
	#define	KCDTypeNameBearerAvailabilityCheckTSY	_S("BearerAvailabilityCheckTSY")
	#define KCDTypeNameCDMAOPCapability				_S("CDMAOperationCapability")
	#define KCDTypeNameCDMASimIPMaxNumNai			_S("CDMASimpleIpMaxNumNai")
	#define KCDTypeNameCDMASimIPMaxNaiLength		_S("CDMASimpleIpMaxNaiLength")
	#define KCDTypeNameCDMASimIPMaxSSLength			_S("CDMASimpleIpMaxSsLength")
	#define KCDTypeNameCDMASimIPAuthSupported		_S("CDMASimpleIpAuthSupported")
	#define KCDTypeNameCDMAMIPMaxNumNai				_S("CDMAMobileIpMaxNumNai")
	#define KCDTypeNameCDMAMIPMaxNaiLength			_S("CDMAMobileIpMaxNAILength")
	#define KCDTypeNameCDMAMIPMaxMNAAASSLength		_S("CDMAMobileIpMaxMnAaaSsLength")
	#define KCDTypeNameCDMAMIPMNAAAAuthAlgorithm	_S("CDMAMobileIpMnAaaAuthAlgorithm")
	#define KCDTypeNameCDMAMIPMaxMNHASSLength		_S("CDMAMobileIpMaxMnHaSsLength")
	#define KCDTypeNameCDMAMIPMNHAAuthAlgorithm		_S("CDMAMobileIpMnHaAuthAlgorithm")
	#define KCDTypeNameDefaultSnap				_S("DefaultSnap")
	#define KCDTypeNamePromptForSnap			_S("PromptForSnap")




//////////////////////////////////////////////////////////////////////////////
// 010/ CONNECTION PREFERENCES RECORD
//

	// Element Type Ids
	const TMDBElementId KCDTIdRanking         = 0x01030000;
	const TMDBElementId KCDTIdDirection       = 0x01040000;
	const TMDBElementId KCDTIdBearerSet       = 0x01050000;
	const TMDBElementId KCDTIdDialogPref      = 0x01060000;
	const TMDBElementId KCDTIdIAPLink         = 0x01070000;


	// Element Type Names
	#define	KCDTypeNameRanking				_S("Ranking")
	#define	KCDTypeNameDirection			_S("Direction")
	#define	KCDTypeNameBearerSet			_S("BearerSet")
	#define	KCDTypeNameDialogPref			_S("DialogPref")






///////////////////////////////////////////////////////////////////////////
// 018  NETWORK RECORD
//
        // Field Type IDs
	const TMDBElementId KCDTIdHostName				  = 0x01830000;

        // NETWORK Table Field Names
	#define	KCDTypeNameHostName						_S("HostName")

////////////////////////////////////////////////////////////////////////
// 020  LOCATION RECORD
//

	// Field Type IDs
	const TMDBElementId KCDTIdIntlPrefixCode				  = 0x02030000;
	const TMDBElementId KCDTIdNatPrefixCode					  = 0x02040000;
	const TMDBElementId KCDTIdNatCode				  		  = 0x02050000;
	const TMDBElementId KCDTIdAreaCode						  = 0x02060000;
	const TMDBElementId KCDTIdDialOutCode					  = 0x02070000;
	const TMDBElementId KCDTIdDisableCallWaitingCode	      = 0x02080000;
	const TMDBElementId KCDTIdMobile						  = 0x02090000;
	const TMDBElementId KCDTIdUsePulseDial					  = 0x020A0000;
	const TMDBElementId KCDTIdWaitForDialTone				  = 0x020B0000;
	const TMDBElementId KCDTIdPauseAfterDialOut			      = 0x020C0000;


	// Location Table Field Names
	#define	KCDTypeNameIntlPrefixCode						_S("IntlPrefixCode")
	#define	KCDTypeNameNatPrefixCode						_S("NatPrefixCode")
	#define	KCDTypeNameNatCode								_S("NatCode")
	#define	KCDTypeNameAreaCode								_S("AreaCode")
	#define	KCDTypeNameDialOutCode							_S("DialOutCode")
	#define	KCDTypeNameDisableCallWaitingCode		        _S("DisableCallWaitingCode")
	#define	KCDTypeNameMobile								_S("Mobile")
	#define	KCDTypeNameUsePulseDial							_S("UsePulseDial")
	#define	KCDTypeNameWaitForDialTone						_S("WaitForDialTone")
	#define	KCDTypeNamePauseAfterDialOut		            _S("PauseAfterDialout")
	#define KCDTypeNameOPCapability	   						_S("OPCapability")
	#define	KCDTypeNameSimipMaxNumNai						_S("SimipMaxNumNai")
	#define	KCDTypeNameSimipMaxNaiLength					_S("SimipMaxNaiLength")   
	#define	KCDTypeNameSimipMaxSsLength						_S("SimipMaxSsLength")
	#define	KCDTypeNameSimipAuthSupported					_S("SimipAuthSupported")
	#define	KCDTypeNameMipMaxNumNai							_S("MipMaxNumNai ")
	#define	KCDTypeNameMipMaxNaiLength						_S("MipMaxNaiLength")
	#define	KCDTypeNameMipMaxMnAaaSsLength					_S("MipMaxMnAaaSsLength")
	#define	KCDTypeNameMipMnAaaAuthAlgorithm				_S("MipMnAaaAuthAlgorithm")
	#define	KCDTypeNameMipMaxMnHaSsLength					_S("MipMaxMnHaSsLength")
	#define	KCDTypeNameMipMnAaaAuthAlgorithm				_S("MipMnAaaAuthAlgorithm")

//////////////////////////////////////////////////////////////////////////////////////
// 028/  IAP RECORD
//

	// FieldTIds
	const TMDBElementId KCDTIdIAPServiceType 				= 0x02830000; // Type of Service record
	const TMDBElementId KCDTIdIAPService 					= 0x02840000; // Link to a Service record
	const TMDBElementId KCDTIdIAPBearerType 				= 0x02850000; // Type of Bearer record
	const TMDBElementId KCDTIdIAPBearer 					= 0x02860000; // Link to a Bearer record
	const TMDBElementId KCDTIdIAPNetwork 					= 0x02870000; // Link to a Network record
	const TMDBElementId KCDTIdIAPNetworkWeighting 			= 0x02880000; // Network weighting
	const TMDBElementId KCDTIdIAPLocation 					= 0x02890000; // Link to a Location record


  // Field Names
	#define	KCDTypeNameIAPNetwork				       _S("IAPNetwork")
	#define	KCDTypeNameNetworkWeighting		           _S("IAPNetworkWeighting")
	#define	KCDTypeNameServiceType		               _S("IAPServiceType")
	#define	KCDTypeNameBearerType		               _S("IAPBearerType")





//////////////////////////////////////////////////////////////////////////////////////
// 030/ WAP ACCESS POINT RECORD
//


	// Element Type Ids
	const TMDBElementId KCDTIdWAPCurrentBearer  = 0x03030000;
	const TMDBElementId KCDTIdWAPStartPage      = 0x03040000;


	// Element Type Names
	#define	KCDTypeNameWAPCurrentBearer		      _S("CurrentBearer")
	#define	KCDTypeNameWAPStartPage		          _S("StartPage")






/////////////////////////////////////////////////////////////////////////////////////
// 06/  DIAL OUT ISP SERVICE RECORD
//

	// FieldTIds

	const TMDBElementId KCDTIdDescription               = 0x03830000;
	const TMDBElementId KCDTIdType						= 0x03840000;
	const TMDBElementId KCDTIdDefaultTelNum             = 0x03850000;
	const TMDBElementId KCDTIdDialResolution            = 0x03860000;
	const TMDBElementId KCDTIdChargecard                = 0x03870000;
	const TMDBElementId KCDTIdUseLoginScript            = 0x03880000;
	const TMDBElementId KCDTIdLoginScript               = 0x03890000;
	const TMDBElementId KCDTIdPromptForLogin            = 0x038A0000;
	const TMDBElementId KCDTIdLoginName                 = 0x038B0000;
	const TMDBElementId KCDTIdLoginPass                 = 0x038C0000;
	const TMDBElementId KCDTIdDisplayPct                = 0x038D0000;
	const TMDBElementId KCDTIdIfParams                  = 0x038F0000;
	const TMDBElementId KCDTIdIfNetworks                = 0x03900000;
	const TMDBElementId KCDTIdIfPromptForAuth           = 0x03910000;
	const TMDBElementId KCDTIdIfAuthName                = 0x03920000;
	const TMDBElementId KCDTIdIfAuthPass                = 0x03930000;
	const TMDBElementId KCDTIdIfAuthRetries             = 0x03940000;
	const TMDBElementId KCDTIdIfCallbackEnabled         = 0x03950000;
	const TMDBElementId KCDTIdIfCallbackType            = 0x03960000;
	const TMDBElementId KCDTIdIfCallbackInfo            = 0x03970000;
	const TMDBElementId KCDTIdCallbackTimeout           = 0x03980000;
	const TMDBElementId KCDTIdIfServerMode              = 0x03990000;
	const TMDBElementId KCDTIdIpAddrFromServer          = 0x039A0000;
	const TMDBElementId KCDTIdIpAddr					= 0x039B0000;
	const TMDBElementId KCDTIdIpNetMask                 = 0x039C0000;
	const TMDBElementId KCDTIdIpGateway                 = 0x039D0000;
	const TMDBElementId KCDTIdIpDNSAddrFromServer       = 0x039E0000;
	const TMDBElementId KCDTIdIpNameServer1             = 0x039F0000;
	const TMDBElementId KCDTIdIpNameServer2             = 0x03A00000;
	const TMDBElementId KCDTIdIp6DNSAddrFromServer      = 0x03A10000;
	const TMDBElementId KCDTIdIp6NameServer1            = 0x03A20000;
	const TMDBElementId KCDTIdIp6NameServer2            = 0x03A30000;
	const TMDBElementId KCDTIdIpAddrLeaseValidFrom      = 0x03A40000;
	const TMDBElementId KCDTIdIpAddrLeaseValidTo        = 0x03A50000;
	const TMDBElementId KCDTIdConfigDaemonManagerName   = 0x03A60000;
	const TMDBElementId KCDTIdConfigDaemonName          = 0x03A70000;
	const TMDBElementId KCDTIdEnableIpHeaderComp        = 0x03A80000;
	const TMDBElementId KCDTIdEnableLCPExtension        = 0x03A90000;
	const TMDBElementId KCDTIdDisablePlainTextAuth      = 0x03AA0000;
	const TMDBElementId KCDTIdEnableSwComp              = 0x03AB0000;
	const TMDBElementId KCDTIdBearerName                = 0x03AC0000;
	const TMDBElementId KCDTIdBearerSpeed               = 0x03AD0000;
	const TMDBElementId KCDTIdBearerCe                  = 0x03AE0000;
	const TMDBElementId KCDTIdInitString                = 0x03AF0000;
	const TMDBElementId KCDTIdBearerType                = 0x03B00000;
	const TMDBElementId KCDTIdChannelCoding             = 0x03B10000;
	const TMDBElementId KCDTIdAiur						= 0x03B20000;
	const TMDBElementId KCDTIdRequestedTimeSlots        = 0x03B30000;
	const TMDBElementId KCDTIdMaximumTimeSlots          = 0x03B40000;
	const TMDBElementId KCDTIdBearerService             = 0x03B50000;
	const TMDBElementId KCDTIdBearerProtocol            = 0x03B60000;
	const TMDBElementId KCDTIdRlpVersion                = 0x03B70000;
	const TMDBElementId KCDTIdIwfToMs                   = 0x03B80000;
	const TMDBElementId KCDTIdMsToIwf                   = 0x03B90000;
	const TMDBElementId KCDTIdAckTimer                  = 0x03BA0000;
	const TMDBElementId KCDTIdRetransmissionAttempts    = 0x03BB0000;
	const TMDBElementId KCDTIdResequencePeriod          = 0x03BC0000;
	const TMDBElementId KCDTIdV42Compression            = 0x03BD0000;
	const TMDBElementId KCDTIdV42Codewords              = 0x03BE0000;
	const TMDBElementId KCDTIdV42MaxLength              = 0x03BF0000;
	const TMDBElementId KCDTIdAsymmetry                 = 0x03C00000;
	const TMDBElementId KCDTIdUserInitUpgrade           = 0x03C10000;
	const TMDBElementId KCDTIdUseEdge                   = 0x03C20000;


	#define                    KCDTypeNameDescription                 _S("Description")
	#define                    KCDTypeNameType                        _S("Type")
	#define                    KCDTypeNameDefaultTelNum               _S("DefaultTelNum")
	#define                    KCDTypeNameDialResolution              _S("DialResolution")
	#define                    KCDTypeNameUseLoginScript              _S("UseLoginScript")
	#define                    KCDTypeNameLoginScript                 _S("LoginScript")
	#define                    KCDTypeNamePromptForLogin              _S("PromptForLogin")
	#define                    KCDTypeNameLoginName                   _S("LoginName")
	#define                    KCDTypeNameLoginPass                   _S("LoginPass")
	#define                    KCDTypeNameDisplayPct                  _S("DisplayPCT")
	#define                    KCDTypeNameIfParams                    _S("IfParams")
	#define                    KCDTypeNameIfNetworks                  _S("IfNetworks")
	#define                    KCDTypeNameIfPromptForAuth             _S("IfPromptForAuth")
	#define                    KCDTypeNameIfAuthName                  _S("IfAuthName")
	#define                    KCDTypeNameIfAuthPass                  _S("IfAuthPass")
	#define                    KCDTypeNameIfAuthRetries               _S("AuthRetries")
	#define                    KCDTypeNameIfCallbackEnabled           _S("IfCallbackEnabled")
	#define                    KCDTypeNameIfCallbackType              _S("IfCallbackType")
	#define                    KCDTypeNameIfCallbackInfo              _S("IfCallbackInfo")
	#define                    KCDTypeNameCallbackTimeout             _S("CallbackTimeout")
	#define                    KCDTypeNameIfServerMode                _S("IfServerMode")
	#define                    KCDTypeNameIpAddrFromServer            _S("IpAddrFromServer")
	#define                    KCDTypeNameIpAddr                      _S("IpAddr")
	#define                    KCDTypeNameIpNetMask                   _S("IpNetMask")
	#define                    KCDTypeNameIpGateway                   _S("IpGateway")
	#define                    KCDTypeNameIpDNSAddrFromServer         _S("IpDNSAddrFromServer")
	#define                    KCDTypeNameIpNameServer1               _S("IpNameServer1")
	#define                    KCDTypeNameIpNameServer2               _S("IpNameServer2")
	#define                    KCDTypeNameIp6DNSAddrFromServer        _S("Ip6DnsAddrFromServer")
	#define                    KCDTypeNameIp6NameServer1              _S("Ip6NameServer1")
	#define                    KCDTypeNameIp6NameServer2              _S("Ip6NameServer2")
	#define                    KCDTypeNameIpAddrLeaseValidFrom        _S("IpAddrLeaseValidFrom")
	#define                    KCDTypeNameIpAddrLeaseValidTo          _S("IpAddrLeaseValidTo")
	#define                    KCDTypeNameConfigDaemonManagerName     _S("ConfigDaemonManagerName")
	#define                    KCDTypeNameConfigDaemonName            _S("ConfigDaemonName")
	#define                    KCDTypeNameEnableIpHeaderComp          _S("EnableIPHeaderComp")
	#define                    KCDTypeNameEnableLcpExtensions         _S("EnableLCPExtension")
	#define                    KCDTypeNameDisablePlainTextAuth        _S("DisablePlainTextAuth")
	#define                    KCDTypeNameEnableSwComp                _S("EnableSWComp")
	#define                    KCDTypeNameBearerName                  _S("BearerName")
	#define                    KCDTypeNameBearerSpeed                 _S("BearerSpeed")
	#define                    KCDTypeNameBearerCe                    _S("BearerCE")
	#define                    KCDTypeNameInitString                  _S("InitString")
	#define	                   KCDTypeNameISPBearerType		          _S("BearerType")
	#define                    KCDTypeNameChannelCoding               _S("ChannelCoding")
	#define                    KCDTypeNameAiur                        _S("Aiur")
	#define                    KCDTypeNameRequestedTimeSlots          _S("RequestedTimeSlots")
	#define                    KCDTypeNameMaximumTimeSlots            _S("MaximumTimeSlots")
	#define                    KCDTypeNameBearerService               _S("BearerService")
	#define                    KCDTypeNameBearerProtocol              _S("BearerProtocol")
	#define                    KCDTypeNameRlpVersion                  _S("RlpVersion")
	#define                    KCDTypeNameIwfToMs                     _S("IwfToMs")
	#define                    KCDTypeNameMsToIwf                     _S("MsToIwf")
	#define                    KCDTypeNameAckTimer                    _S("AckTimer")
	#define                    KCDTypeNameRetransmissionAttempts      _S("RetransmissionAttempts")
	#define                    KCDTypeNameResequencePeriod            _S("ResequencePeriod")
	#define                    KCDTypeNameV42Compression              _S("V42Compression")
	#define                    KCDTypeNameV42Codewords                _S("V42Codewords")
	#define                    KCDTypeNameV42MaxLength                _S("V42MaxLength")
	#define                    KCDTypeNameAsymmetry                   _S("Asymmetry")
	#define                    KCDTypeNameUserInitUpgrade             _S("UserInitUpgrade")
	#define                    KCDTypeNameUseEdge                     _S("UseEdge")







//////////////////////////////////////////////////////////////////////////////////////
// 040/ DIAL IN ISP RECORD
//


	// FieldTIds
	//
	const TMDBElementId KCDTIdDINDescription              = 0x04030000;
	const TMDBElementId KCDTIdDINType                     = 0x04040000;
	const TMDBElementId KCDTIdDINUseLoginScript           = 0x04050000;
	const TMDBElementId KCDTIdDINLoginScript              = 0x04060000;
	//
	const TMDBElementId KCDTIdDINAuthentication           = 0x04070000;
	//
	const TMDBElementId KCDTIdDINIfAuthRetries            = 0x04080000;
	const TMDBElementId KCDTIdDINIfParams                 = 0x04090000;
	const TMDBElementId KCDTIdDINIfNetworks               = 0x040A0000;
	const TMDBElementId KCDTIdDINIpAddrFromServer         = 0x040B0000;
	const TMDBElementId KCDTIdDINIpAddr                   = 0x040C0000;
	const TMDBElementId KCDTIdDINIpNetMask                = 0x040D0000;
	const TMDBElementId KCDTIdDINIpGateway                = 0x040E0000;
	const TMDBElementId KCDTIdDINIpDNSAddrFromServer      = 0x040F0000;
	const TMDBElementId KCDTIdDINIpNameServer1            = 0x04100000;
	const TMDBElementId KCDTIdDINIpNameServer2            = 0x04110000;
	const TMDBElementId KCDTIdDINIp6DNSAddrFromServer     = 0x04120000;
	const TMDBElementId KCDTIdDINIp6NameServer1           = 0x04130000;
	const TMDBElementId KCDTIdDINIp6NameServer2           = 0x04140000;
	const TMDBElementId KCDTIdDINEnableIpHeaderComp       = 0x04150000;
	const TMDBElementId KCDTIdDINEnableLCPExtensions      = 0x04160000;
	const TMDBElementId KCDTIdDINDisablePlainTextAuth     = 0x04170000;
	const TMDBElementId KCDTIdDINEnableSwComp             = 0x04180000;
	const TMDBElementId KCDTIdDINBearerName               = 0x04190000;
	const TMDBElementId KCDTIdDINBearerSpeed              = 0x041A0000;
	const TMDBElementId KCDTIdDINBearerCe                 = 0x041B0000;
	const TMDBElementId KCDTIdDINInitString               = 0x041C0000;
	const TMDBElementId KCDTIdDINUseEdge                  = 0x041D0000;
//


	#define	KCDTypeNameAuthentication		               _S("Authentication")




/////////////////////////////////////////////////////////////////////////////////////
//  048/  LAN Service Record
//
//
	// FieldTIds
	const TMDBElementId KCDTIdLANIfNetworks 					= 0x04830000;
	const TMDBElementId KCDTIdLANIpNetMask 					    = 0x04840000;
	const TMDBElementId KCDTIdLANIpGateway 					    = 0x04850000;
	const TMDBElementId KCDTIdLANIpAddrFromServer 				= 0x04860000;
	const TMDBElementId KCDTIdLANIpAddr 						= 0x04870000;
	const TMDBElementId KCDTIdLANIpDNSAddrFromServer 			= 0x04880000;
	const TMDBElementId KCDTIdLANIpNameServer1 				    = 0x04890000;
	const TMDBElementId KCDTIdLANIpNameServer2 				    = 0x048A0000;
	const TMDBElementId KCDTIdLANIp6DNSAddrFromServer			= 0x048B0000;
	const TMDBElementId KCDTIdLANIp6NameServer1				    = 0x048C0000;
	const TMDBElementId KCDTIdLANIp6NameServer2 				= 0x048D0000;
	const TMDBElementId KCDTIdLANIpAddrLeaseValidFrom			= 0x048E0000;
	const TMDBElementId KCDTIdLANIpAddrLeaseValidTo 			= 0x048F0000;
	const TMDBElementId KCDTIdLANConfigDaemonManagerName 		= 0x04900000;
	const TMDBElementId KCDTIdLANConfigDaemonName 				= 0x04910000;
	//
	const TMDBElementId KCDTIdLANServiceExtensionTableName 		= 0x04920000;
	const TMDBElementId KCDTIdLANServiceExtensionTableRecordId 	= 0x04930000;


	#define	KCDTypeNameServiceExtensionTableName				_S("LanServiceExtensionTableName")
	#define	KCDTypeNameServiceExtensionTableRecordId		    _S("LanServiceExtensionTableRecordId")
	#define	KCDTypeNameServiceIfExternIpConfigAlwaysRejectAuth	_S("ServiceIfExternIpConfigAlwaysRejectAuth")



//////////////////////////////////////////////////////////////////////////////////////
// 050/ WLAN SERVICE EXTENSION RECORD
//

	// FieldTIds
#ifdef SYMBIAN_NETWORKING_WIFI
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANProfile	 					= 0x05030000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANSSID	 					= 0x05040000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANEncryptionStatus	 			= 0x05050000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANEncryptionType	 			= 0x05060000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANDefaultWepKey  	 			= 0x05070000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANEncryptKey1Valid	 			= 0x05080000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANWepKey1	 				= 0x05090000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANEncryptKey2Valid	 			= 0x050A0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANWepKey2	 				= 0x050B0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANEncryptKey3Valid	 			= 0x050C0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANWepKey3	 				= 0x050D0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANEncryptKey4Valid	 			= 0x050E0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANWepKey4	 				= 0x050F0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANRanking 	 					= 0x05100000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANDialogPref	 				= 0x05110000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANNetworkType	 				= 0x05120000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANFragThres	 					= 0x05130000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANRTSThres	 					= 0x05140000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANDesTransRate	 				= 0x05150000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANBeaconInt	 					= 0x05160000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANChannelId	 				= 0x05170000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANAuthenticationMode	 		= 0x05180000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANPowerSaveMode	 				= 0x05190000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANAllowUnencryptMode	 		= 0x051A0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANAllowShortPre	 				= 0x051B0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANPreambleType	 				= 0x051C0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANTxPowerLevel	 				= 0x051D0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANEapPresharedKey	 			= 0x051E0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANRegDomain	 					= 0x051F0000;
	/**
	@internalComponent
	*/
	const TMDBElementId	KCDTIdWLANSecData	 					= 0x05200000;


	// Field Names
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANProfile							_S("Wlan_Profile")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANSSID							_S("Wlan_SSID")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANEncryptionStatus					_S("Wlan_Encryption_Status")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANEncryptionType					_S("Wlan_Encryption_Type")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANDefaultWepKey  				_S("Wlan_Wep_Default_Key")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANEncryptKey1Valid					_S("Wlan_Key1_Valid")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANWepKey1						_S("Wlan_Wep_Key1")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANEncryptKey2Valid					_S("Wlan_Key2_Valid")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANWepKey2						_S("Wlan_Wep_Key2")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANEncryptKey3Valid					_S("Wlan_Key3_Valid")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANWepKey3						_S("Wlan_Wep_Key3")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANEncryptKey4Valid					_S("Wlan_Key4_Valid")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANWepKey4						_S("Wlan_Wep_Key4")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANRanking 							_S("Wlan_Ranking")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANDialogPref						_S("Wlan_Dialog_Pref")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANNetworkType						_S("Wlan_Network_Type")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANFragThres						_S("Wlan_Frag_Threshold")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANRTSThres							_S("Wlan_RTS_Threshold")
	/**	
	@internalComponent
	*/
	#define	KCDTypeNameWLANDesTransRate						_S("Wlan_Desired_Transmit_Rate")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANBeaconInt						_S("Wlan_Beacon_Int")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANChannelId						_S("Wlan_Channel_ID")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANAuthenticationMode			_S("Wlan_Authentication_Mode")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANPowerSaveMode					_S("Wlan_Power_Save_Mode")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANAllowUnencryptMode				_S("Wlan_Allow_UnEncrypt_Mode")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANAllowShortPre					_S("Wlan_Allow_Short_Preamble")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANPreambleType						_S("Wlan_Preamble_Type")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANTxPowerLevel						_S("Wlan_TX_Power_Level")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANEapPresharedKey					_S("Wlan_EAP_Preshared_Key")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANRegDomain						_S("Wlan_Reglutory_Domain")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameWLANSecData							_S("Wlan_Security_Data")

// SYMBIAN_NETWORKING_WIFI
#endif

//////////////////////////////////////////////////////////////////////////////////////
// 058/  VPN SERVICE RECORD
//


	// FieldTIds
	const TMDBElementId KCDTIdVPNPolicyName 		= 0x05830000; // Policy name
	const TMDBElementId KCDTIdVPNIAPRecord 			= 0x05840000; // Link to a IAP record
	const TMDBElementId KCDTIdVPNNetwork 			= 0x05850000; // Link to a Network record


	#define	KCDTypeNameVPNPolicyName		       _S("Policy")
	#define	KCDTypeNameVPNIAPRecord		           _S("HomeIAP")
	#define	KCDTypeNameVPNNetwork		           _S("HomeNetwork")




//////////////////////////////////////////////////////////////////////////////////////
// 060/  CDMA2000 PACKETSERVICE TABLE RECORD
//


	// FieldTIds
	const TMDBElementId KCDTIdCDMAFchMux 		        				= 0x06030000;
	const TMDBElementId KCDTIdCDMASchMux         						= 0x06040000;
	const TMDBElementId KCDTIdIwfName 		        					= 0x06050000;
	const TMDBElementId KCDTIdServiceOption 	       					= 0x06060000;
	const TMDBElementId KCDTIdPdpType 		        					= 0x06070000;
	const TMDBElementId KCDTIdPdpAddress 	        					= 0x06080000;
	const TMDBElementId KCDTIdReqFwdPriority         					= 0x06090000;
	const TMDBElementId KCDTIdReqRevPriority 	        				= 0x060A0000;
	const TMDBElementId KCDTIdReqFwdBitrate 	        				= 0x060B0000;
	const TMDBElementId KCDTIdReqRevBitrate 	        				= 0x060C0000;
	const TMDBElementId KCDTIdReqFwdLoss 	        					= 0x060D0000;
	const TMDBElementId KCDTIdReqRevLoss 	        					= 0x060E0000;
	const TMDBElementId KCDTIdReqFwdMaxdelay         					= 0x060F0000;
	const TMDBElementId KCDTIdReqRevMaxdelay         					= 0x06100000;
	const TMDBElementId KCDTIdMinFwdBitrate 	       					= 0x06110000;
	const TMDBElementId KCDTIdMinRevBitrate 	       					= 0x06120000;
	const TMDBElementId KCDTIdAccptFwdLoss       						= 0x06130000;
	const TMDBElementId KCDTIdAccptRevLoss 	          					= 0x06140000;
	const TMDBElementId KCDTIdAccptFwdMaxdelay 		        			= 0x06150000;
	const TMDBElementId KCDTIdAccptRevMaxdelay 		           			= 0x06160000;
	const TMDBElementId KCDTIdDataCompression 							= 0x06170000;
	const TMDBElementId KCDTIdHeaderCompression         				= 0x06180000;
	const TMDBElementId KCDTIdAnonymousAccess        					= 0x06190000;
	/*	*/																
	/*const TMDBElementId KCDTIdCDMA2000IfName 		        			= 0x061A0000;*/
	const TMDBElementId KCDTIdCDMA2000IfParams		        			= 0x061B0000;
	//																	
	const TMDBElementId KCDTIdApType 									= 0x061C0000;
	const TMDBElementId KCDTIdQosWarningTimeout          				= 0x061D0000;
	const TMDBElementId KCDTIdRlpMode 									= 0x061E0000;
	const TMDBElementId KCDTIdNAIType 			        				= 0x061F0000;
	const TMDBElementId KCDTIdSimIPAuthAlgorithm         				= 0x06200000;
	const TMDBElementId KCDTIdSimIPChapSSHandle		         			= 0x06210000;
	const TMDBElementId KCDTIdSimIPPapSSHandle		         			= 0x06220000;
	const TMDBElementId KCDTIdMIPTBit 									= 0x06230000;
	const TMDBElementId KCDTIdMIPHomeAddress 	        				= 0x06240000;
	const TMDBElementId KCDTIdMIPPrimaryHomeAgent        				= 0x06250000;
	const TMDBElementId KCDTIdMIPSecondaryHomeAgent      				= 0x06260000;
	const TMDBElementId KCDTIdMIPMnAaaAuthAlgorithm      				= 0x06270000;
	const TMDBElementId KCDTIdMIPMnAaaSpiIndicator       				= 0x06280000;
	const TMDBElementId KCDTIdMIPMnAaaSpi 		        				= 0x06290000;
	const TMDBElementId KCDTIdMIPMnAaaSsData 	        				= 0x062A0000;
	const TMDBElementId KCDTIdMIPMnHaAuthAlgorithm       				= 0x062B0000;
	const TMDBElementId KCDTIdMIPMnHaSpiIndicator          				= 0x062C0000;
	const TMDBElementId KCDTIdMIPMnHaSpi 		        				= 0x062D0000;
	const TMDBElementId KCDTIdMIPMnHaSsData 	   	    				= 0x062E0000;
	//																
	const TMDBElementId KCDTIdCDMA2000IfNetworks 		        		= 0x062F0000;
	const TMDBElementId KCDTIdCDMA2000IfPromptForAuth        			= 0x06300000;
	const TMDBElementId KCDTIdCDMA2000IfAuthName 	        			= 0x06310000;
	const TMDBElementId KCDTIdCDMA2000IfAuthPass 	        			= 0x06320000;
	const TMDBElementId KCDTIdCDMA2000IfAuthRetries         			= 0x06330000;
	const TMDBElementId KCDTIdCDMA2000IpNetMask 	       				= 0x06340000;
	const TMDBElementId KCDTIdCDMA2000IpGateway 			        	= 0x06350000;
	const TMDBElementId KCDTIdCDMA2000IpAddrFromServer 	    	    	= 0x06360000;
	const TMDBElementId KCDTIdCDMA2000IpAddr 			        		= 0x06370000;
	const TMDBElementId KCDTIdCDMA2000IpDNSAddrFromServer        		= 0x06380000;
	const TMDBElementId KCDTIdCDMA2000IpNameServer1 	        		= 0x06390000;
	const TMDBElementId KCDTIdCDMA2000IpNameServer2 	        		= 0x063A0000;
	const TMDBElementId KCDTIdCDMA2000Ip6DNSAddrFromServer 	        	= 0x063B0000;
	const TMDBElementId KCDTIdCDMA2000Ip6NameServer1 		        	= 0x063C0000;
	const TMDBElementId KCDTIdCDMA2000Ip6NameServer2 	        		= 0x063D0000;
	const TMDBElementId KCDTIdCDMA2000IpAddrLeaseValidFrom 	        	= 0x063E0000;
	const TMDBElementId KCDTIdCDMA2000IpAddrLeaseValidTo         		= 0x063F0000;
	const TMDBElementId KCDTIdCDMA2000ConfigDaemonManagerName       	= 0x06400000;
	const TMDBElementId KCDTIdCDMA2000ConfigDaemonName 		        	= 0x06410000;
	const TMDBElementId KCDTIdCDMA2000EnableLCPExtension         		= 0x06420000;
	const TMDBElementId KCDTIdCDMA2000DisablePlainTextAuth 	        	= 0x06430000;
	//
	const TMDBElementId KCDTIdCDMA2000EnableSwComp						= 0x06440000;
	const TMDBElementId KCDTIdCDMA2000IfExternIpConfigAlwaysRejectAuth	= 0x06450000;
	const TMDBElementId KCDTIdCDMA2000EnableIpHeaderComp				= 0x06460000;
	const TMDBElementId KCDTIdCDMA2000CDMAMobileIP						= 0x06470000;
	const TMDBElementId KCDTIdCDMA2000CDMAMobileIPTimeout 				= 0x06480000;
	const TMDBElementId KCDTIdCDMA2000HomeAgentAddress    				= 0x06490000;
	


	// Field Names
	#define	KCDTypeNameCDMAFchMux					        		_S("CDMAFchMux")
	#define	KCDTypeNameCDMASchMux									_S("CDMASchMux")
	#define	KCDTypeNameCDMAIwfName			        				_S("IwfName")
	#define	KCDTypeNameCDMAServiceOption		        			_S("ServiceOption")
	#define	KCDTypeNameCDMAPdpType		        					_S("PDPType")
	#define	KCDTypeNameCDMAPdpAddress		        				_S("PDPAddress")
	#define	KCDTypeNameCDMAReqFwdPriority		        			_S("ReqFwdPriority")
	#define	KCDTypeNameCDMAReqRevPriority		        			_S("ReqRevPriority")
	#define	KCDTypeNameCDMAReqFwdBitrate		        			_S("ReqFwdBitrate")
	#define	KCDTypeNameCDMAReqRevBitrate		        			_S("ReqRevBitrate")
	#define	KCDTypeNameCDMAReqFwdLoss				        		_S("ReqFwdLoss")
	#define	KCDTypeNameCDMAReqRevLoss				        		_S("ReqRevLoss")
	#define	KCDTypeNameCDMAReqFwdMaxdelay							_S("ReqFwdMaxdelay")
	#define	KCDTypeNameCDMAReqRevMaxdelay	        				_S("ReqRevMaxdelay")
	#define	KCDTypeNameCDMAMinFwdBitrate		        			_S("MinFwdBitrate")
	#define	KCDTypeNameCDMAMinRevBitrate			        		_S("MinRevBitrate")
	#define	KCDTypeNameCDMAAccptFwdLoss        						_S("AccptFwdLoss")
	#define	KCDTypeNameCDMAAccptRevLoss	        					_S("AccptRevLoss")
	#define	KCDTypeNameCDMAAccptFwdMaxdelay	        				_S("AccptFwdMaxdelay")
	#define	KCDTypeNameCDMAAccptRevMaxdelay		        			_S("AccptRevMaxdelay")
	#define	KCDTypeNameCDMADataCompression	        				_S("DataCompression")
	#define	KCDTypeNameCDMAHeaderCompression	        			_S("HeaderCompression")
	#define	KCDTypeNameCDMAAnonymousAccess			        		_S("AnonymousAccess")
	#define	KCDTypeNameCDMAIfParams		        					_S("IfParams")
	#define	KCDTypeNameCDMAApType				        			_S("ApType")
	#define	KCDTypeNameCDMAQosWarningTimeout       					_S("QosWarningTimeout")
	#define	KCDTypeNameCDMARlpMode				        			_S("RlpMode")
	#define	KCDTypeNameCDMANAIType					        		_S("CDMANaiType")
	#define	KCDTypeNameCDMASimpleIPAuthAlgorithm	        		_S("CDMASimpleIpAuthAlgorithm")
	#define	KCDTypeNameCDMA_SIMIP_Pap_SS_Handle	        			_S("CDMASimpleIpPapSsHandle")
	#define	KCDTypeNameCDMASimpleIpPapSsHandle		        		_S("CDMASimpleIpChapSsHandle")
	#define	KCDTypeNameCDMAMobileIpTBit			        			_S("CDMAMobileIpTBit")
	#define	KCDTypeNameCDMAMIPHomeAddress		        			_S("CDMAMobileIpHomeAddress")
	#define	KCDTypeNameCDMAMIPPrimaryHomeAgent		        		_S("CDMAMobileIpPrimaryHomeAgent")
	#define	KCDTypeNameCDMAMIPSecondaryHomeAgent       				_S("CDMAMobileIpSecondaryHomeAgent")
	#define	KCDTypeNameCDMAMIPMnAaaAuthAlgorithm					_S("CDMAMobileIpMnAaaAuthAlgorithm")
	#define	KCDTypeNameCDMAMIPMnAaaSpiIndicator        				_S("CDMAMobileIpMnAaaSpiIndicator")
	#define	KCDTypeNameCDMAMIPMnAaaSpi			        			_S("CDMAMobileIpMnAaaSpi")
	#define	KCDTypeNameCDMAMIPMnAaaSsData			        		_S("CDMAMobileIpMnAaaSsData")
	#define	KCDTypeNameCDMAMIPMnHaAuthAlgorithm						_S("CDMAMobileIpMnHaAuthAlgorithm")
	#define	KCDTypeNameCDMAMIPMnHaSpiIndicator						_S("CDMAMobileIpMnHaSpiIndicator")
	#define	KCDTypeNameCDMAMIPMnHaSpi								_S("CDMAMobileIpMnHaSpi")
	#define	KCDTypeNameCDMAMIPMnHaSsData							_S("CDMAMobileIpMnHaSsData")
	#define	KCDTypeNameCDMAIfExternIpConfigAlwaysRejectAuth			_S("IfExternIpConfigAlwaysRejectAuth")
	#define	KCDTypeNameCDMAIfPromptForAuth				    		_S("IfPromptForAuth")
	#define	KCDTypeNameCDMAIfAuthName								_S("IfAuthName")
	#define	KCDTypeNameCDMAIfAuthPass								_S("IfAuthPass")
	#define	KCDTypeNameCDMAAuthRetries								_S("AuthRetries")
	#define	KCDTypeNameCDMAIpNetMask								_S("IpNetMask")
	#define	KCDTypeNameCDMAIpGateway								_S("IpGateway")
	#define	KCDTypeNameCDMAIpAddrFromServer						    _S("IpAddrFromServer")
	#define	KCDTypeNameCDMAIpAddr									_S("IpAddr")
	#define	KCDTypeNameCDMAIpDNSAddrFromServer						_S("IpDNSAddrFromServer")
	#define	KCDTypeNameCDMAIpNameServer1							_S("IpNameServer1")
	#define	KCDTypeNameCDMAIpNameServer2							_S("IpNameServer2")
	#define	KCDTypeNameCDMAIp6DNSAddrFromServer					    _S("Ip6DNSAddrFromServer")
	#define	KCDTypeNameCDMAIp6NameServer1							_S("Ip6NameServer1")
	#define	KCDTypeNameCDMAIp6NameServer2							_S("Ip6NameServer2")
	#define	KCDTypeNameCDMAIpAddrLeaseValidFrom						_S("IpAddrLeaseValidFrom")
	#define	KCDTypeNameCDMAIpAddrLeaseValidTo						_S("IpAddrLeaseValidTo")
	#define	KCDTypeNameCDMAConfigDaemonManagerName					_S("ConfigDaemonManagerName")
	#define	KCDTypeNameCDMAConfigDaemonName							_S("ConfigDaemonName")
	#define	KCDTypeNameCDMAEnableLCPExtension						_S("EnableLCPExtension")
	#define	KCDTypeNameCDMADisablePlainTextAuth						_S("DisablePlainTextAuth")
	#define	KCDTypeNameServiceEnableSwComp							_S("EnableSWComp")
	#define	KCDTypeNameCDMAMobileIP									_S("CDMAMobileIP")
	#define	KCDTypeNameCDMAMobileIPTimeout							_S("CDMAMobileIPTimeout")
	


/////////////////////////////////////////////////////////////////////////////////////////
// 0F0/ GPRS QoS R99 Parameters
//

//VR99/R4 QoS parameters
    const TMDBElementId KCDTIdWCDMAReqTrafficClass                     = 0x0F030000;             
    const TMDBElementId KCDTIdWCDMAMinTrafficClass                     = 0x0F040000;
    const TMDBElementId KCDTIdWCDMAReqDeliveryOrder                    = 0x0F050000;
    const TMDBElementId KCDTIdWCDMAMinDeliveryOrder                    = 0x0F060000;
    const TMDBElementId KCDTIdWCDMAReqDeliverErroneousSDU              = 0x0F070000;
    const TMDBElementId KCDTIdWCDMAMinDeliverErroneousSDU              = 0x0F080000;
    const TMDBElementId KCDTIdWCDMAReqMaxSDUSize                       = 0x0F090000;
    const TMDBElementId KCDTIdWCDMAMinAcceptableMaxSDUSize             = 0x0F0A0000;
    const TMDBElementId KCDTIdWCDMAReqMaxUplinkRate                    = 0x0F0B0000;
    const TMDBElementId KCDTIdWCDMAReqMinUplinkRate                    = 0x0F0C0000;
    const TMDBElementId KCDTIdWCDMAReqMaxDownlinkRate                  = 0x0F0D0000;
    const TMDBElementId KCDTIdWCDMAReqMinDownlinkRate                  = 0x0F0E0000;
    const TMDBElementId KCDTIdWCDMAReqBER                              = 0x0F0F0000;
    const TMDBElementId KCDTIdWCDMAMaxBER                              = 0x0F100000;
    const TMDBElementId KCDTIdWCDMAReqSDUErrorRatio                    = 0x0F110000;
    const TMDBElementId KCDTIdWCDMAMaxSDUErrorRatio                    = 0x0F120000;
    const TMDBElementId KCDTIdWCDMAReqTrafficHandlingPriority          = 0x0F130000;
    const TMDBElementId KCDTIdWCDMAMinTrafficHandlingPriority          = 0x0F140000;
    const TMDBElementId KCDTIdWCDMAReqTransferDelay                    = 0x0F150000;
    const TMDBElementId KCDTIdWCDMAMaxTransferDelay                    = 0x0F160000;
    const TMDBElementId KCDTIdWCDMAReqGuaranteedUplinkRate             = 0x0F170000;
    const TMDBElementId KCDTIdWCDMAMinGuaranteedUplinkRate             = 0x0F180000;
    const TMDBElementId KCDTIdWCDMAReqGuaranteedDownlinkRate           = 0x0F190000;
    const TMDBElementId KCDTIdWCDMAMinGuaranteedDownlinkRate           = 0x0F1A0000;
    const TMDBElementId KCDTIdWCDMASignallingIndication                = 0x0F1B0000;
    const TMDBElementId KCDTIdWCDMAImCmSignallingIndication            = 0x0F1C0000;
    const TMDBElementId KCDTIdWCDMASourceStatisticsDescriptor          = 0x0F1D0000;

    //Field names
    #define                    KCDTypeNameGPRSReqTrafficClass            _S("ReqTrafficClass")
    #define                    KCDTypeNameGPRSMinTrafficClass            _S("MinTrafficClass")
    #define                    KCDTypeNameGPRSReqDeliveryOrder           _S("ReqDeliveryOrder")
    #define                    KCDTypeNameGPRSMinDeliveryOrder           _S("MinDeliveryOrder")
    #define                    KCDTypeNameGPRSReqDeliverErroneousSDU     _S("ReqDeliverErroneousSDU")
    #define                    KCDTypeNameGPRSMinDeliverErroneousSDU     _S("MinDeliverErroneousSDU")
    #define                    KCDTypeNameGPRSReqMaxSDUSize              _S("ReqMaxSDUSize")
    #define                    KCDTypeNameGPRSMinAcceptableMaxSDUSize    _S("MinAcceptableMaxSDUSize")
    #define                    KCDTypeNameGPRSReqMaxUplinkRate           _S("ReqMaxUplinkRate")
    #define                    KCDTypeNameGPRSReqMinUplinkRate           _S("ReqMinUplinkRate")
    #define                    KCDTypeNameGPRSReqMaxDownlinkRate         _S("ReqMaxDownlinkRate")
    #define                    KCDTypeNameGPRSReqMinDownlinkRate         _S("ReqMinDownlinkRate")
    #define                    KCDTypeNameGPRSReqBER                     _S("ReqBER")
    #define                    KCDTypeNameGPRSMaxBER                     _S("MaxBER")
    #define                    KCDTypeNameGPRSReqSDUErrorRatio           _S("ReqSDUErrorRatio")
    #define                    KCDTypeNameGPRSMaxSDUErrorRatio           _S("MaxSDUErrorRatio")
    #define                    KCDTypeNameGPRSReqTrafficHandlingPriority _S("ReqTrafficHandlingPriority")
    #define                    KCDTypeNameGPRSMinTrafficHandlingPriority _S("MinTrafficHandlingPriority")
    #define                    KCDTypeNameGPRSReqTransferDelay           _S("ReqTransferDelay")
    #define                    KCDTypeNameGPRSMaxTransferDelay           _S("MaxTransferDelay")
    #define                    KCDTypeNameGPRSReqGuaranteedUplinkRate    _S("ReqGuaranteedUplinkRate")
    #define                    KCDTypeNameGPRSMinGuaranteedUplinkRate    _S("MinGuaranteedUplinkRat")
    #define                    KCDTypeNameGPRSReqGuaranteedDownlinkRate  _S("ReqGuaranteedDownlinkRate")
    #define                    KCDTypeNameGPRSMinGuaranteedDownlinkRate  _S("MinGuaranteedDownlinkRate")
    #define                    KCDTypeNameGPRSSignallingIndication       _S("SignallingIndication")
    #define                    KCDTypeNameGPRSImCnSignallingIndication   _S("ImCnSignallingIndication")
    #define                    KCDTypeNameGPRSSourceStatisticsDescriptor _S("SourceStatisticsDescriptor")


/////////////////////////////////////////////////////////////////////////////////////////
// 068/ WCDMA Packet Service Record
//

	// FieldTIds
	const TMDBElementId KCDTIdAPN						    	 = 0x00030000;
	const TMDBElementId KCDTIdWCDMPDPType 						 = 0x00040000;
	const TMDBElementId KCDTIdWCDMAPDPAddress					 = 0x00050000;
	const TMDBElementId KCDTIdReqPrecedence						 = 0x00060000;
	const TMDBElementId KCDTIdReqDelay							 = 0x00070000;
	const TMDBElementId KCDTIdReqReliability					 = 0x00080000;
	const TMDBElementId KCDTIdReqPeakThroughput                  = 0x00090000;
	const TMDBElementId KCDTIdReqMeanThroughput			         = 0x000A0000;
	const TMDBElementId KCDTIdMinPrecedence						 = 0x000B0000;
	const TMDBElementId KCDTIdMinDelay							 = 0x000C0000;
	const TMDBElementId KCDTIdMinReliability					 = 0x000D0000;
	const TMDBElementId KCDTIdMinPeakThroughput				     = 0x000E0000;
	const TMDBElementId KCDTIdMinMeanThroughput				     = 0x000F0000;
	//
	const TMDBElementId KCDTIdWCDMADataCompression				 = 0x00100000;
	const TMDBElementId KCDTIdWCDMAHeaderCompression  			 = 0x00110000;
	const TMDBElementId KCDTIdWCDMAUseEdge				         = 0x00120000;
	const TMDBElementId KCDTIdWCDMAAnonymousAccess	    		 = 0x00130000;
	const TMDBElementId KCDTIdWCDMAIfParams						 = 0x00140000;
	const TMDBElementId KCDTIdWCDMAIfNetworks					 = 0x00150000;
	const TMDBElementId KCDTIdWCDMAIfPromptForAuth				 = 0x00160000;
	const TMDBElementId KCDTIdWCDMAIfAuthName					 = 0x00170000;
	const TMDBElementId KCDTIdWCDMAIfAuthPass					 = 0x00180000;
	const TMDBElementId KCDTIdWCDMAIfAuthRetries				 = 0x00190000;
	const TMDBElementId KCDTIdWCDMAIPNetMask					 = 0x001A0000;
	const TMDBElementId KCDTIdWCDMAIPGateway					 = 0x001B0000;
	const TMDBElementId KCDTIdWCDMAIPAddrFromServer				 = 0x001C0000;
	const TMDBElementId KCDTIdWCDMAIPAddr						 = 0x001D0000;
	const TMDBElementId KCDTIdWCDMAIPDNSAddrFromServer			 = 0x001E0000;
	const TMDBElementId KCDTIdWCDMAIPNameServer1				 = 0x001F0000;
	const TMDBElementId KCDTIdWCDMAIPNameServer2				 = 0x00200000;
	const TMDBElementId KCDTIdWCDMAIP6DNSAddrFromServer		     = 0x00210000;
	const TMDBElementId KCDTIdWCDMAIP6NameServer1				 = 0x00220000;
	const TMDBElementId KCDTIdWCDMAIP6NameServer2				 = 0x00230000;
	const TMDBElementId KCDTIdWCDMAIPAddrLeaseValidFrom			 = 0x00240000;
	const TMDBElementId KCDTIdWCDMAIPAddrLeaseValidTo			 = 0x00250000;
	const TMDBElementId KCDTIdWCDMAConfigDaemonManagerName	     = 0x00260000;
	const TMDBElementId KCDTIdWCDMAConfigDaemonName				 = 0x00270000;
	const TMDBElementId KCDTIdWCDMAEnableLCPExtensions			 = 0x00280000;
	const TMDBElementId KCDTIdWCDMADisablePlainTextAuth			 = 0x00290000;
	//
	const TMDBElementId KCDTIdAPType					  		 		= 0x002A0000;
	const TMDBElementId KCDTIdQOSWarningTimeOut				    		= 0x002B0000;
	//
	const TMDBElementId KCDTIdUmtsR99QoSAndOn					= 0x002C0000;

	
	// Field Names
	#define                    KCDTypeNameGPRSAPN                        _S("APN")
	#define                    KCDTypeNameGPRSPDPType                    _S("PDPType")
	#define                    KCDTypeNameGPRSPDPAddress                 _S("PDPAddress")
	#define                    KCDTypeNameGPRSReqPrecedence              _S("ReqPrecedence")
	#define                    KCDTypeNameGPRSReqDelay                   _S("ReqDelay")
	#define                    KCDTypeNameGPRSReqReliability             _S("ReqReliability")
	#define                    KCDTypeNameGPRSReqPeakThroughput          _S("ReqPeakThroughput")
	#define                    KCDTypeNameGPRSReqMeanThroughput          _S("ReqMeanThroughput")
	#define                    KCDTypeNameGPRSMinPrecedence              _S("MinPrecedence")
	#define                    KCDTypeNameGPRSMinDelay                   _S("MinDelay")
	#define                    KCDTypeNameGPRSMinReliability             _S("MinReliability")
	#define                    KCDTypeNameGPRSMinPeakThroughput          _S("MinPeakThroughput")
	#define                    KCDTypeNameGPRSMinMeanThroughput          _S("MinMeanThroughput")
	#define                    KCDTypeNameGPRSDataCompression            _S("DataCompression")
	#define                    KCDTypeNameGPRSHeaderCompression          _S("HeaderCompression")
	#define                    KCDTypeNameGPRSUseEdge                    _S("GprsUseEdge")
	#define                    KCDTypeNameGPRSAnonymousAccess            _S("AnonymousAccess")
	#define                    KCDTypeNameGPRSIfParams                   _S("IfParams")
	#define                    KCDTypeNameGPRSIfPromptForAuth            _S("IfPromptForAuth")
	#define                    KCDTypeNameGPRSIfAuthName                 _S("IfAuthName")
	#define                    KCDTypeNameGPRSIfAuthPass                 _S("IfAuthPass")
	#define                    KCDTypeNameGPRSIfAuthRetries              _S("AuthRetries")
	#define                    KCDTypeNameGPRSIPNetMask                  _S("IpNetMask")
	#define                    KCDTypeNameGPRSIPGateway                  _S("IpGateway")
	#define                    KCDTypeNameGPRSIPAddrFromServer           _S("IpAddrFromServer")
	#define                    KCDTypeNameGPRSIPAddr                     _S("IpAddr")
	#define                    KCDTypeNameGPRSIPDNSAddrFromServer        _S("IpDNSAddrFromServer")
	#define                    KCDTypeNameGPRSIPNameServer1              _S("IpNameServer1")
	#define                    KCDTypeNameGPRSIPNameServer2              _S("IpNameServer2")
	#define                    KCDTypeNameGPRSIP6DNSAddrFromServer       _S("Ip6DNSAddrFromServer")
	#define                    KCDTypeNameGPRSIP6NameServer1             _S("Ip6NameServer1")
	#define                    KCDTypeNameGPRSIP6NameServer2             _S("Ip6NameServer2")
	#define                    KCDTypeNameGPRSIPAddrLeaseValidFrom       _S("IpAddrLeaseValidFrom")
	#define                    KCDTypeNameGPRSIPAddrLeaseValidTo         _S("IpAddrLeaseValidTo")
	#define                    KCDTypeNameGPRSConfigDaemonManagerName    _S("ConfigDaemonManagerName")
	#define                    KCDTypeNameGPRSConfigDaemonName           _S("ConfigDaemonName")
	#define                    KCDTypeNameGPRSEnableLCPExtensions        _S("EnableLCPExtension")
	#define                    KCDTypeNameGPRSDisablePlainTextAuth       _S("DisablePlainTextAuth")
	#define                    KCDTypeNameGPRSAPType                     _S("GprsAccessPointType")
	#define                    KCDTypeNameGPRSQOSWarningTimeOut          _S("QosWarningTimeout")
	#define                    KCDTypeNameUmtsR99QoSAndOn                _S("UmtsR99QoSAndOn")
	

/////////////////////////////////////////////////////////////////////////////////////////
// 0D8/  PAN Service Extensions Table
//

	// FieldTIds
	const TMDBElementId KCDTIdLocalRole						    	 = 0x0D830000;
	const TMDBElementId KCDTIdPeerRole						    	 = 0x0D840000;
	const TMDBElementId KCDTIdPeerMACAddresses				    	 = 0x0D850000;
	const TMDBElementId KCDTIdPromptForRemoteDevices			   	 = 0x0D860000;
	const TMDBElementId KCDTIdDisableSdpQuery				    	 = 0x0D870000;
	const TMDBElementId KCDTIdAllowIncoming					    	 = 0x0D880000;
	const TMDBElementId KCDTIdPromptIfMACListFails				   	 = 0x0D890000;

	// Field Names
	#define                    KCDTypeNameLocalRole          		_S("LocalRole")
	#define                    KCDTypeNamePeerRole					_S("PeerRole")
	#define                    KCDTypeNamePeerMACAddresses			_S("PeerMACAddresses")
	#define                    KCDTypeNamePromptForRemoteDevices	_S("PromptForRemoteDevices")
	#define                    KCDTypeNameDisableSdpQuery			_S("DisableSdpQuery")
	#define                    KCDTypeNameAllowIncoming				_S("AllowIncomingConnections")
	#define                    KCDTypeNamePromptIfMACListFails		_S("PromptIfMACListFails")


/////////////////////////////////////////////////////////////////////////////////////////
// 070/  Default CDMA2000 Settings Table
//


	// Element Type Ids
	const TMDBElementId KCDTIdDefaultCdmaUsage			 = 0x07030000;
	const TMDBElementId KCDTIdCdmaIwfName				 = 0x07040000;
	const TMDBElementId KCDTIdCdmaServiceOptions		 = 0x07050000;
	const TMDBElementId KCDTIdCdmaPdpType				 = 0x07060000;
	const TMDBElementId KCDTIdCdmaPdpAddress			 = 0x07070000;
	const TMDBElementId KCDTIdCdmaReqFwdPriority		 = 0x07080000;
	const TMDBElementId KCDTIdCdmaReqRevPriority		 = 0x07090000;
	const TMDBElementId KCDTIdCdmaReqFwdBitrate			 = 0x070A0000;
	const TMDBElementId KCDTIdCdmaReqRevBitrate			 = 0x070B0000;
	const TMDBElementId KCDTIdCdmaReqFwdLoss			 = 0x070C0000;
	const TMDBElementId KCDTIdCdmaReqRevLoss			 = 0x070D0000;
	const TMDBElementId KCDTIdCdmaReqFwdMaxdelay		 = 0x070E0000;
	const TMDBElementId KCDTIdCdmaReqRevMaxdelay		 = 0x070F0000;
	const TMDBElementId KCDTIdCdmaMinFwdBitrate			 = 0x07100000;
	const TMDBElementId KCDTIdCdmaMinRevBitrate			 = 0x07110000;
	const TMDBElementId KCDTIdCdmaAccptFwdLoss			 = 0x07120000;
	const TMDBElementId KCDTIdCdmaAccptRevLoss			 = 0x07130000;
	const TMDBElementId KCDTIdCdmaAccptFwdMaxdelay		 = 0x07140000;
	const TMDBElementId KCDTIdCdmaAccptRevMaxdelay		 = 0x07150000;
	const TMDBElementId KCDTIdCdmaDataCompression		 = 0x07160000;
	const TMDBElementId KCDTIdCdmaHeaderCompression		 = 0x07170000;
	const TMDBElementId KCDTIdCdmaAnonymousAccess		 = 0x07180000;
	const TMDBElementId KCDTIdCdmaOpMode				 = 0x07190000;
	const TMDBElementId KCDTIdCdmaMipMaxNumRetry		 = 0x071A0000;
	const TMDBElementId KCDTIdCdmaMipFirstRetryTimeout	 = 0x071B0000;
	const TMDBElementId KCDTIdCdmaMipReregThreshold		 = 0x071C0000;
    const TMDBElementId KCDTIdCdmaServiceEnableLlmnr	 = 0x071D0000;
    const TMDBElementId KCDTIdCdmaEnableIpHeaderComp	 = 0x071E0000;
    const TMDBElementId KCDTIdCdmaMobileIP	             = 0x071F0000;
    const TMDBElementId KCDTIdCdmaHomeAgentAddress       = 0x07200000;
    const TMDBElementId KCDTIdCdmaMobileIPTimeout        = 0x07210000;
    const TMDBElementId KCDTIdCdmaFchMux                 = 0x07220000;
    const TMDBElementId KCDTIdCdmaSchMux                 = 0x07230000;
    
   

	// Element Type Names
	#define	KCDTypeNameDefaultCdmaUsage		           _S("Usage")
	#define	KCDTypeNameCdmaIwfName		               _S("IwfName")
	#define	KCDTypeNameCdmaServiceOptions		       _S("ServiceOption")
	#define	KCDTypeNameCdmaPdpType		               _S("PDPType")
	#define	KCDTypeNameCdmaPdpAddress		           _S("PDPAddress")
	#define	KCDTypeNameCdmaReqFwdPriority		       _S("ReqFwdPriority")
	#define	KCDTypeNameCdmaReqRevPriority		       _S("ReqRevPriority")
	#define	KCDTypeNameCdmaReqFwdBitrate		       _S("ReqFwdBitrate")
	#define	KCDTypeNameCdmaReqRevBitrate		       _S("ReqRevBitrate")
	#define	KCDTypeNameCdmaReqFwdLoss		           _S("ReqFwdLoss")
	#define	KCDTypeNameCdmaReqRevLoss		           _S("ReqRevLoss")
	#define	KCDTypeNameCdmaReqFwdMaxdelay		       _S("ReqFwdMaxdelay")
	#define	KCDTypeNameCdmaReqRevMaxdelay		       _S("ReqRevMaxdelay")
	#define	KCDTypeNameCdmaMinFwdBitrate		       _S("MinFwdBitrate")
	#define	KCDTypeNameCdmaMinRevBitrate		       _S("MinRevBitrate")
	#define	KCDTypeNameCdmaAccptFwdLoss		           _S("AccptFwdLoss")
	#define	KCDTypeNameCdmaAccptRevLoss		           _S("AccptRevLoss")
	#define	KCDTypeNameCdmaAccptFwdMaxdelay		       _S("AccptFwdMaxdelay")
	#define	KCDTypeNameCdmaAccptRevMaxdelay		       _S("AccptRevMaxdelay")
	#define	KCDTypeNameCdmaDataCompression		       _S("DataCompression")
	#define	KCDTypeNameCdmaHeaderCompression		   _S("HeaderCompression")
	#define	KCDTypeNameCdmaAnonymousAccess		       _S("AnonymousAccess")
	#define	KCDTypeNameCdmaOpMode		               _S("CDMAOperationMode")
	#define	KCDTypeNameCdmaMipMaxNumRetry		       _S("CDMAMobileIpMaxNumRetry")
	#define	KCDTypeNameCdmaMipFirstRetryTimeout		   _S("CDMAMobileIpFirstRetryTimeout")
	#define	KCDTypeNameCdmaMipReregThreshold		   _S("CDMAMobileIpReregThreshold")
	#define	KCDTypeNameDefaultCdmaHomeAgentAddress	   _S("HomeAgentAddress")
	#define	KCDTypeNameDefaultCdmaMobileIPTimeout	   _S("CDMAMobileIPTimeout")

////////////////////////////////////////////////////////////////////////////
// 078/ Default WCDMA Settings Table
//

	const TMDBElementId KCDTIdDefaultGPRSUsage						     = 0x07830000;
	const TMDBElementId KCDTIdDefaultGPRSAPN						     = 0x07840000;
	const TMDBElementId KCDTIdDefaultGPRSPDPType					     = 0x07850000;
	const TMDBElementId KCDTIdDefaultGPRSPDPAddress				    	 = 0x07860000;
	const TMDBElementId KCDTIdDefaultGPRSPrecedence				    	 = 0x07870000;
	const TMDBElementId KCDTIdDefaultGPRSDelay						     = 0x07880000;
	const TMDBElementId KCDTIdDefaultGPRSReliability				     = 0x07890000;
	const TMDBElementId KCDTIdDefaultGPRSPeakThroughput			    	 = 0x078A0000;
	const TMDBElementId KCDTIdDefaultGPRSMeanThroughput			    	 = 0x078B0000;
	const TMDBElementId KCDTIdDefaultGPRSMinPrecedence				     = 0x078C0000;
	const TMDBElementId KCDTIdDefaultGPRSMinDelay					     = 0x078D0000;
	const TMDBElementId KCDTIdDefaultGPRSMinReliability			    	 = 0x078E0000;
	const TMDBElementId KCDTIdDefaultGPRSMinPeakThroughput			     = 0x078F0000;
	const TMDBElementId KCDTIdDefaultGPRSMinMeanThroughput			     = 0x07900000;
	const TMDBElementId KCDTIdDefaultGPRSDataCompression			     = 0x07910000;
	const TMDBElementId KCDTIdDefaultGPRSHeaderCompression			     = 0x07920000;
	const TMDBElementId KCDTIdDefaultGPRSUseEdge					     = 0x07930000;
	const TMDBElementId KCDTIdDefaultGPRSAnonymousAccess			     = 0x07940000;


	#define KCDTypeNameUsage						     _S("Usage")
	#define KCDTypeNameAPN						    	 _S("APN")
	#define KCDTypeNamePDPType					    	 _S("PDPType")
	#define KCDTypeNamePDPAddress				    	 _S("PDPAddress")
	#define KCDTypeNamePrecedence				    	 _S("Precedence")
	#define KCDTypeNameDelay						     _S("Delay")
	#define KCDTypeNameReliability				    	 _S("Reliability")
	#define KCDTypeNamePeakThroughput			    	 _S("PeakThroughput")
	#define KCDTypeNameMeanThroughput			    	 _S("MeanThroughput")
	#define KCDTypeNameMinPrecedence				     _S("MinPrecedence")
	#define KCDTypeNameMinDelay					    	 _S("MinDelay")
	#define KCDTypeNameMinReliability			    	 _S("MinReliability")
	#define KCDTypeNameMinPeakThroughput			     _S("MinPeakThroughput")
	#define KCDTypeNameMinMeanThroughput			     _S("MinMeanThroughput")
	#define KCDTypeNameDataCompression			    	 _S("DataCompression")
	#define KCDTypeNameHeaderCompression			     _S("HeaderCompression")
	#define KCDTypeNameAnonymousAccess			    	 _S("AnonymousAccess")




////////////////////////////////////////////////////////////////////////////
// 080/  MODEM BEARER RECORD
//

	const TMDBElementId KCDTIdNifName							  = 0x08030000;
	const TMDBElementId KCDTIdPortName							  = 0x08040000;
	const TMDBElementId KCDTIdTsyName							  = 0x08050000;
	const TMDBElementId KCDTIdCsyName							  = 0x08060000;
	const TMDBElementId KCDTIdDataBits							  = 0x08070000;
	const TMDBElementId KCDTIdStopBits							  = 0x08080000;
	const TMDBElementId KCDTIdParity							  = 0x08090000;
	const TMDBElementId KCDTIdRate								  = 0x080A0000;
	const TMDBElementId KCDTIdHandshaking						  = 0x080B0000;
	const TMDBElementId KCDTIdSpecialRate						  = 0x080C0000;
	const TMDBElementId KCDTIdXonChar							  = 0x080D0000;
	const TMDBElementId KCDTIdXoffChar							  = 0x080E0000;
	const TMDBElementId KCDTIdFaxClassPref						  = 0x080F0000;
	const TMDBElementId KCDTIdSpeakerPref						  = 0x08100000;
	const TMDBElementId KCDTIdSpeakerVolPref					  = 0x08110000;
	const TMDBElementId KCDTIdModemInitString					  = 0x08120000;
	const TMDBElementId KCDTIdDataInitString					  = 0x08130000;
	const TMDBElementId KCDTIdFaxInitString						  = 0x08140000;
	const TMDBElementId KCDTIdIspInitString						  = 0x08150000;
	const TMDBElementId KCDTIdDialPauseLength					  = 0x08160000;
	const TMDBElementId KCDTIdCarrierTimeOut					  = 0x08170000;
	const TMDBElementId KCDTIdAutoAnswerRingCount				  = 0x08180000;
	const TMDBElementId KCDTIdSpeakerVolControlLow				  = 0x08190000;
	const TMDBElementId KCDTIdSpeakerVolControlMedium			  = 0x081A0000;
	const TMDBElementId KCDTIdSpeakerVolControlHigh				  = 0x081B0000;
	const TMDBElementId KCDTIdSpeakerAlwaysOff					  = 0x081C0000;
	const TMDBElementId KCDTIdSpeakerOnUntilCarrier				  = 0x081D0000;
	const TMDBElementId KCDTIdSpeakerAlwaysOn					  = 0x081E0000;
	const TMDBElementId KCDTIdSpeakerOnAfterUntilCarrier		  = 0x081F0000;
	const TMDBElementId KCDTIdDialToneWaitModifier				  = 0x08200000;
	const TMDBElementId KCDTIdCallProgress1						  = 0x08210000;
	const TMDBElementId KCDTIdCallProgress2						  = 0x08220000;
	const TMDBElementId KCDTIdCallProgress3					 	  = 0x08230000;
	const TMDBElementId KCDTIdCallProgress4					 	  = 0x08240000;
	const TMDBElementId KCDTIdEchoOff							  = 0x08250000;
	const TMDBElementId KCDTIdVerboseText						  = 0x08260000;
	const TMDBElementId KCDTIdQuietOff							  = 0x08270000;
	const TMDBElementId KCDTIdQuietOn							  = 0x08280000;
	const TMDBElementId KCDTIdDialCommandStateModifier			  = 0x08290000;
	const TMDBElementId KCDTIdOnLine							  = 0x082A0000;
	const TMDBElementId KCDTIdResetConfiguration				  = 0x082B0000;
	const TMDBElementId KCDTIdReturnToFactoryDefs				  = 0x082C0000;
	const TMDBElementId KCDTIdDcdOnDuringLink					  = 0x082D0000;
	const TMDBElementId KCDTIdDtrHangUp							  = 0x082E0000;
	const TMDBElementId KCDTIdDsrAlwaysOn						  = 0x082F0000;
	const TMDBElementId KCDTIdRtsCtsHandshake					  = 0x08300000;
	const TMDBElementId KCDTIdXonXoffHandshake					  = 0x08310000;
	const TMDBElementId KCDTIdEscapeCharacter					  = 0x08320000;
	const TMDBElementId KCDTIdEscapeGuardPeriod					  = 0x08330000;
	const TMDBElementId KCDTIdFaxClassInterrogate				  = 0x08340000;
	const TMDBElementId KCDTIdFaxClass							  = 0x08350000;
	const TMDBElementId KCDTIdNoDialTone						  = 0x08360000;
	const TMDBElementId KCDTIdBusy								  = 0x08370000;
	const TMDBElementId KCDTIdNoAnswer							  = 0x08380000;
	const TMDBElementId KCDTIdCarrier							  = 0x08390000;
	const TMDBElementId KCDTIdConnect							  = 0x083A0000;
	const TMDBElementId KCDTIdCompressionClass5					  = 0x083B0000;
	const TMDBElementId KCDTIdCompressionV42bis					  = 0x083C0000;
	const TMDBElementId KCDTIdCompressionNone					  = 0x083D0000;
	const TMDBElementId KCDTIdProtocolLapd						  = 0x083E0000;
	const TMDBElementId KCDTIdProtocolAlt						  = 0x083F0000;
	const TMDBElementId KCDTIdProtocolAltcellular				  = 0x08400000;
	const TMDBElementId KCDTIdProtocolNone						  = 0x08410000;
	const TMDBElementId KCDTIdMessageCentreNumber				  = 0x08420000;
	const TMDBElementId KCDTIdMessageValidityPeriod				  = 0x08430000;
	const TMDBElementId KCDTIdMessageDeliveryReport				  = 0x08440000;
	const TMDBElementId KCDTIdMinSignalLevel					  = 0x08450000;
	const TMDBElementId KCDTIdCommRole							  = 0x08460000;
	const TMDBElementId KCDTIdControlChannelPortName			  = 0x08470000;
	const TMDBElementId KCDTIdSirSettings					      = 0x08480000;
    const TMDBElementId KCDTIdLastSocketActivityTimeout			  = 0x08490000;
	const TMDBElementId KCDTIdLastSessionClosedTimeout			  = 0x084A0000;
	const TMDBElementId KCDTIdLastSocketClosedTimeout			  = 0x084B0000;
	const TMDBElementId KCDTIdBCAStack							  = 0x084C0000;
	


	// Field Names
	#define	KCDTypeNameNifName								_S("IfName")
	#define	KCDTypeNamePortName								_S("PortName")
	#define	KCDTypeNameTsyName								_S("TSYName")
	#define	KCDTypeNameCsyName								_S("CSYName")
	#define	KCDTypeNameSocketActivityTimeout		        _S("SocketActivityTimeout")
	#define	KCDTypeNameSessionClosedTimeout		            _S("SessionClosedTimeout")
	#define	KCDTypeNameSocketClosedTimeout		            _S("SocketClosedTimeout")
	#define	KCDTypeNameDataBits								_S("DataBits")
	#define	KCDTypeNameStopBits								_S("StopBits")
	#define	KCDTypeNameParity								_S("Parity")
	#define	KCDTypeNameRate									_S("Rate")
	#define	KCDTypeNameHandShaking							_S("Handshaking")
	#define	KCDTypeNameSpecialRate							_S("SpecialRate")
	#define	KCDTypeNameXonChar								_S("XonChar")
	#define	KCDTypeNameXoffChar								_S("XoffChar")
	#define	KCDTypeNameFaxClassPref							_S("FaxClassPref")
	#define	KCDTypeNameSpeakerPref							_S("SpeakerPref")
	#define	KCDTypeNameSpeakerVolPref						_S("SpeakerVolPref")
	#define	KCDTypeNameModemInitString						_S("ModemInitString")
	#define	KCDTypeNameDataInitString						_S("DataInitString")
	#define	KCDTypeNameFaxInitString						_S("FaxInitString")
	#define	KCDTypeNameIspInitString						_S("IspInitString")
	#define	KCDTypeNameDialPauseLength						_S("DialPauseLength")
	#define	KCDTypeNameCarrierTimeout						_S("CarrierTimeout")
	#define	KCDTypeNameAutoAnswerRingCount		            _S("AutoAnswerRingCount")
	#define	KCDTypeNameSpeakerVolControlLow		            _S("SpeakerVolContorlLow")
	#define	KCDTypeNameSpeakerVolControlMedium		        _S("SpeakerVolControlMedium")
	#define	KCDTypeNameSpeakerVolControlHigh		        _S("SpeakerVolControlHigh")
	#define	KCDTypeNameSpeakerAlwaysOff		                _S("SpeakerAlwaysOff")
	#define	KCDTypeNameSpeakerOnUntilCarrier		        _S("SpeakerOnUntilCarrier")
	#define	KCDTypeNameSpeakerAlwaysOn		                _S("SpeakerAlwaysOn")
	#define	KCDTypeNameSpeakerOnAfterUntilCarrier		    _S("SpeakerOnAfterUntilCarrier")
	#define	KCDTypeNameDialToneWaitModifier		            _S("DialToneWaitModifier")
	#define	KCDTypeNameCallProgress1						_S("CallProgress1")
	#define	KCDTypeNameCallProgress2						_S("CallProgress2")
	#define	KCDTypeNameCallProgress3						_S("CallProgress3")
	#define	KCDTypeNameCallProgress4						_S("CallProgress4")
	#define	KCDTypeNameEchoOff								_S("EchoOff")
	#define	KCDTypeNameVerboseText							_S("VerboseText")
	#define	KCDTypeNameQuietOff								_S("QuietOff")
	#define	KCDTypeNameQuietOn								_S("QuietOn")
	#define	KCDTypeNameDialCommandStateModifier		        _S("DialCommandStateModifier")
	#define	KCDTypeNameOnLine								_S("OnLine")
	#define	KCDTypeNameResetConfiguration		            _S("ResetConfiguration")
	#define	KCDTypeNameReturnToFactoryDefs		            _S("ReturnToFactoryDefs")
	#define	KCDTypeNameDcdOnDuringLink						_S("DCDOnDuringLink")
	#define	KCDTypeNameDtrHangUp							_S("DTRHangUp")
	#define	KCDTypeNameDsrAlwaysOn							_S("DSRAlwaysOn")
	#define	KCDTypeNameRtsCtsHandshake						_S("RTSCTSHandshake")
	#define	KCDTypeNameXonXoffHandshake						_S("XonXoffHandshake")
	#define	KCDTypeNameEscapeCharacter						_S("EscapeCharacter")
	#define	KCDTypeNameEscapeGuardPeriod		            _S("EscapeGuardPeriod")
	#define	KCDTypeNameFaxClassInterrogate		            _S("FaxClassInterrogate")
	#define	KCDTypeNameFaxClass								_S("FaxClass")
	#define	KCDTypeNameNoDialTone							_S("NoDialTone")
	#define	KCDTypeNameBusy									_S("Busy")
	#define	KCDTypeNameNoAnswer								_S("NoAnswer")
	#define	KCDTypeNameCarrier								_S("Carrier")
	#define	KCDTypeNameConnect								_S("Connect")
	#define	KCDTypeNameCompressionClass5		            _S("CompressionClass5")
	#define	KCDTypeNameCompressionClassV42bis		        _S("CompressionV42bis")
	#define	KCDTypeNameCompressionNone						_S("CompressionNone")
	#define	KCDTypeNameProtocolLapd							_S("ProtocolLAPD")
	#define	KCDTypeNameProtocolAlt							_S("ProtocolALT")
	#define	KCDTypeNameProtocolAltcellular		            _S("ProtocolALTCELLULAR")
	#define	KCDTypeNameProtocolNone							_S("ProtocolNone")
	#define	KCDTypeNameMessageCentreNumber		            _S("MessageCentreNumber")
	#define	KCDTypeNameMessageValidityPeriod		        _S("MessageValidityPeriod")
	#define	KCDTypeNameMessageDeliveryReport		        _S("MessageDeliveryReport")
	#define	KCDTypeNameMinSignalLevel						_S("MinimumSignalLevel")
	#define	KCDTypeNameCommRole								_S("CommRole")
	#define	KCDTypeNameControlChannelPortName		        _S("ControlChannelPortName")
	#define	KCDTypeNameSirSettings							_S("SIRSettings")
	#define	KCDTypeNameBCAStack								_S("BCAStack")



/////////////////////////////////////////////////////////////////////////////////////
// 088/  LAN Bearer
//

    const TMDBElementId 	KCDTIdLANBearerNifName	             = 0x08830000;
	const TMDBElementId 	KCDTIdLANBearerLddFilename    	     = 0x08840000;
	const TMDBElementId 	KCDTIdLANBearerLddName	             = 0x08850000;
	const TMDBElementId 	KCDTIdLANBearerPddFilename	         = 0x08860000;
   	const TMDBElementId     KCDTIdLANBearerPddName               = 0x08870000;
	const TMDBElementId 	KCDTIdLANBearerPacketDriverName	     = 0x08880000;
	const TMDBElementId 	KCDTIdLANLastSocketActivityTimeout   = 0x08890000;
	const TMDBElementId 	KCDTIdLANLastSessionClosedTimeout    = 0x088A0000;
    const TMDBElementId 	KCDTIdLANLastSocketClosedTimeout     = 0x088B0000;

	// Field Names
	#define	KCDTypeNameLanBearerLddFilename				_S("LDDFilename")
	#define	KCDTypeNameLanBearerLddName					_S("LDDName")
	#define	KCDTypeNameLanBearerPddFilename				_S("PDDFilename")
	#define	KCDTypeNameLanBearerPddName					_S("PDDName")
	#define	KCDTypeNameLanBearerPacketDriverName        _S("PacketDriverName")



//////////////////////////////////////////////////////////////////////////////////////
// 090/ VIRTUAL BEARER RECORD
//

    // FieldTIds
	const TMDBElementId KCDTIdVirtualBearerNifName		    = 0x09030000;
	//
	const TMDBElementId KCDTIdVBLastSocketActivityTimeout	= 0x09040000;
	const TMDBElementId KCDTIdVBLastSessionClosedTimeout	= 0x09050000;
	const TMDBElementId KCDTIdVBLastSocketClosedTimeout	    = 0x09060000;
	//
    

	// Field Names
	#define	KCDTypeNameVirtualBearerAgent		            _S("Agent")
	#define	KCDTypeNameVirtualBeareNIFName					_S("IfName")
	#define	KCDTypeNameLastSocketActivityTimeout		    _S("LastSocketActivityTimeout")
	#define	KCDTypeNameLastSessionClosedTimeout		        _S("LastSessionClosedTimeout")
	#define	KCDTypeNameLastSocketClosedTimeout              _S("LastSocketClosedTimeout")





//////////////////////////////////////////////////////////////////////////////////////
// 098/ WAP SMS Bearer Record
//

	// Element Type Ids
	const TMDBElementId KCDTIdWAPSMSAccessPointId			= 0x09830000;
	const TMDBElementId KCDTIdWAPSMSGatewayAddress			= 0x09840000;
	const TMDBElementId KCDTIdWAPSMSServiceCentreAddress    = 0x09850000;
	const TMDBElementId KCDTIdWAPSMSWSPOption               = 0x09860000;
	const TMDBElementId KCDTIdWAPSMSSecurity                = 0x09870000;


	// Element Type Names
	#define	KCDTypeNameWAPAccessPointId		               _S("AccessPointId")
	#define	KCDTypeNameWAPGatewayAddress		           _S("GatewayAddress")
	#define	KCDTypeNameWAPServiceCentreAddress		       _S("ServiceCentreAddress")
	#define	KCDTypeNameWAPWSPOption						   _S("WSPOption")
	#define	KCDTypeNameWAPSecurity						   _S("Security")




////////////////////////////////////////////////////////////////////////////////////////
// 0A0/  WAP IP BEARER
//

	const TMDBElementId  KCDTIdWAPAccessPointId       = 0x0A030000;
	const TMDBElementId  KCDTIdWAPGatewayAddress      = 0x0A040000;
	const TMDBElementId  KCDTIdWAPChargecard          = 0x0A050000;
	const TMDBElementId  KCDTIdWAPIAP                 = 0x0A060000;
	const TMDBElementId  KCDTIdWAPWSPOption           = 0x0A070000;
	const TMDBElementId  KCDTIdWAPSecurity            = 0x0A080000;
	const TMDBElementId  KCDTIdWAPProxyPort           = 0x0A090000;
	const TMDBElementId  KCDTIdWAPProxyLoginName      = 0x0A0A0000;
	const TMDBElementId  KCDTIdWAPProxyLoginPass      = 0x0A0B0000;


	// Element Type Names

	#define	KCDTypeNameWAPIAP		               _S("IAP" )
	#define	KCDTypeNameWAPProxyPort		           _S("ProxyPortNumber" )
	#define	KCDTypeNameWAPProxyLoginName		   _S("ProxyLogin" )
	#define	KCDTypeNameWAPProxyLoginPass		   _S("ProxyPassword" )

//////////////////////////////////////////////////////////////////////////////////////
// 0A8/  CHARGECARD RECORD
//


	// Element Type Ids
	const TMDBElementId KCDTIdAccountNo     = 0x0A830000;
	const TMDBElementId KCDTIdPin           = 0x0A840000;
	const TMDBElementId KCDTIdLocalRule     = 0x0A850000;
	const TMDBElementId KCDTIdNatRule       = 0x0A860000;
	const TMDBElementId KCDTIdIntlRule      = 0x0A870000;


	// Element Type Names
	#define	KCDTypeNameAccountNo		       _S("AccountNumber")
	#define	KCDTypeNamePin		               _S("Pin")
	#define	KCDTypeNameLocalRule		       _S("LocalRule")
	#define	KCDTypeNameNatRule		           _S("NatRule")
	#define	KCDTypeNameIntlRule		           _S("IntlRule")




//////////////////////////////////////////////////////////////////////////////////////
// 0B0/ PROXIES RECORD
//

   // Element Type Ids
	const TMDBElementId KCDTIdISP                = 0x0B030000;
	const TMDBElementId KCDTIdProxyServiceType   = 0x0B040000;
	const TMDBElementId KCDTIdUseProxyServer     = 0x0B050000;
	const TMDBElementId KCDTIdServerName         = 0x0B060000;
	const TMDBElementId KCDTIdProtocolName       = 0x0B070000;
	const TMDBElementId KCDTIdPortNumber         = 0x0B080000;
	const TMDBElementId KCDTIdExceptions         = 0x0B090000;


	// Element Type Names
	#define	KCDTypeNameProxyISP				          _S("ISP")
	#define	KCDTypeNameUseProxyServer		          _S("UseProxyServer")
	#define	KCDTypeNameProxyServiceType		          _S("ProxyServiceType")
	#define	KCDTypeNameServerName		              _S("ProxyServerName")
	#define	KCDTypeNameProtocolName		              _S("ProtocolName")
	#define	KCDTypeNamePortNumber		              _S("PortNumber")
	#define	KCDTypeNameExceptions		              _S("Exceptions")



//////////////////////////////////////////////////////////////////////////////////////
// 0B8/ SECURE SOCKET PROTO RECORD
//

	// Field Type Ids
	/**
	@internalComponent
	*/
	const TMDBElementId KCDTIdSSProtoName		 = 0x0B830000;
	/**
	@internalComponent
	*/
	const TMDBElementId KCDTIdSSProtoLibrary 	 = 0x0B840000;


	/**
	@internalComponent
	*/
	#define	KCDTypeNameSSProtoName		           _S("ProtocolName")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameSSProtoLibrary		       _S("ProtoLibrary")





//////////////////////////////////////////////////////////////////////////////////////
// 17/ AGENTLOOKUPTABLE RECORD
//


	// FieldTIds
	/**
	@internalComponent
	*/
	const TMDBElementId KCDTIdAgentFriendlyName 	 = 0x0C030000;
	/**
	@internalComponent
	*/
	const TMDBElementId KCDTIdAgentFileName 		 = 0x0C040000;


	// Field Names - names used more than once stored globally
	/**
	@internalComponent
	*/
	#define	KCDTypeNameAgentFileName		               _S("AgentFilename")
	/**
	@internalComponent
	*/
	#define	KCDTypeNameAgentFriendlyName		           _S("AgentFriendlyName")


//////////////////////////////////////////////////////////////////////////////////////
// 1D/ ACCESS POINT RECORD
//
	// FieldTIds
	const TMDBElementId KCDTIdAccessPointGID        = 0x0E030000;
	const TMDBElementId KCDTIdSelectionPolicy       = 0x0E040000;

	// Field Names - names used more than once stored globally
	#define	KCDTypeNameAccessPointGID               _S("AccessPointGID")
	#define	KCDTypeNameSelectionPolicy              _S("AccessPointSelectionPolicy")


//////////////////////////////////////////////////////////////////////////////////////
// 1E/ IAP PRIORITY RECORD
//
	// FieldTIds
	const TMDBElementId KCDTIdIap1                  = 0x0E830000;
	const TMDBElementId KCDTIdIap2                  = 0x0E840000;
	const TMDBElementId KCDTIdIap3                  = 0x0E850000;
	const TMDBElementId KCDTIdIap4                  = 0x0E860000;
	const TMDBElementId KCDTIdIap5                  = 0x0E870000;
	const TMDBElementId KCDTIdIap6                  = 0x0E880000;
	const TMDBElementId KCDTIdIap7                  = 0x0E890000;
	const TMDBElementId KCDTIdIap8                  = 0x0E8A0000;
	const TMDBElementId KCDTIdIap9                  = 0x0E8B0000;
	const TMDBElementId KCDTIdIap10                 = 0x0E8C0000;
	const TMDBElementId KCDTIdIap11                 = 0x0E8D0000;
	const TMDBElementId KCDTIdIap12                 = 0x0E8E0000;
	const TMDBElementId KCDTIdIap13                 = 0x0E8F0000;
	const TMDBElementId KCDTIdIap14                 = 0x0E900000;
	const TMDBElementId KCDTIdIap15                 = 0x0E910000;
	const TMDBElementId KCDTIdIapCount              = 0x0E920000;

	// Field Names - names used more than once stored globally
	#define	KCDTypeNameIap1Name                     _S("IAP1")
	#define	KCDTypeNameIap2Name                     _S("IAP2")
	#define	KCDTypeNameIap3Name                     _S("IAP3")
	#define	KCDTypeNameIap4Name                     _S("IAP4")
	#define	KCDTypeNameIap5Name                     _S("IAP5")
	#define	KCDTypeNameIap6Name                     _S("IAP6")
	#define	KCDTypeNameIap7Name                     _S("IAP7")
	#define	KCDTypeNameIap8Name                     _S("IAP8")
	#define	KCDTypeNameIap9Name                     _S("IAP9")
	#define	KCDTypeNameIap10Name                    _S("IAP10")
	#define	KCDTypeNameIap11Name                    _S("IAP11")
	#define	KCDTypeNameIap12Name                    _S("IAP12")
	#define	KCDTypeNameIap13Name                    _S("IAP13")
	#define	KCDTypeNameIap14Name                    _S("IAP14")
	#define	KCDTypeNameIap15Name                    _S("IAP15")
	#define	KCDTypeNameIapCountName                    _S("IAPCOUNT")




//////////////////////////////////////////////////////////////////////////////////////
// 20/  EAP SECURITY SETTINGS RECORD
//
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdEAPSecOuterEAPType    = 0x0F830000;
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdEAPSecId       		= 0x0F840000;
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdEAPSecPassword       	= 0x0F850000;
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdEAPSecData       		= 0x0F860000;


/**
@internalComponent
@prototype
*/
	#define	KCDTypeNameEAPSecOuterEAPType	 	_S("OuterEapMethodType")
/**
@internalComponent
@prototype
*/
	#define	KCDTypeNameEapId  					_S("EapId")
/**
@internalComponent
@prototype
*/
	#define	KCDTypeNameEAPSecPassword  			_S("EapPassword")
/**
@internalComponent
@prototype
*/
	#define	KCDTypeNameEAPSecData 				_S("EAP_Method_Data")




//////////////////////////////////////////////////////////////////////////////////////
// 21/  TUNNELLED EAP SETTINGS RECORD
//
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdTUNEAPInnerType       = 0x10030000;
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdTUNEAPData       		= 0x10040000;



/**
@internalComponent
@prototype
*/
	#define	KCDTypeNameTUNEAPInnerType	 	_S("InnerEapMethodType")
/**
@internalComponent
@prototype
*/
	#define KCDTypeNameTUNEAPData 			_S("Tun_EAP_Method_Data")



//////////////////////////////////////////////////////////////////////////////////////
// 22/  EAP-TLS SETTINGS RECORD
//
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdEAPTLSClientCertName    	= 0x10830000;
/**
@internalComponent
@prototype
*/
	#define	KCDTypeNameEAPTLSClientCertName	 			_S("ClientCertificateName")



//////////////////////////////////////////////////////////////////////////////////////
// 23/  LEAP SETTINGS RECORD
//
/**
@internalComponent
@prototype
*/
	const TMDBElementId KCDTIdLEAPTimeout    	= 0x11030000;
/**
@internalComponent
@prototype
*/
	#define	KCDTypeNameLEAPTimeout	 			_S("LeapTimeout")


} // end namespace CommsDat


//COMMSDATTYPEINFOV1_1_H
#endif

