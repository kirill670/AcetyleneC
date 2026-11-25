//	T_tabdef.h
//
//	Copyright (c) 1997-1999, 2001 Symbian Ltd. All rights reserved.
//

//	Table definitions

#ifndef __TABDEF_H__
#define __TABDEF_H__

#include <e32math.h>
#include <f32file.h>
#include "cdbstd.h"

namespace commdb_dll
{
const TUint KSingleQuoteChar='\'';

//	Database file name, Default file name and UID
_LIT(KCommsDbFileName,"c:\\System\\Data\\Cdbv3.dat");
_LIT(KCommsDbDefaultFileName,"z:\\System\\Data\\DefaultCdbv3.dat");
// `KCommsDbFileUid` is a magic string used in the aFormat argument of Open()
//	and Create() to ensure that an existing driver is reopened
_LIT(KCommsDbFileUid,"[10004e1d]");

/** Literals to speed up commdb by not having to create TPtr's at runtime */
CDB_LIT(KGlobalSettings,_GLOBAL_SETTINGS);
CDB_LIT(KConnectionPreferences,_CONNECTION_PREFERENCES);
CDB_LIT(KAgent,_AGENT);
CDB_LIT(KConnectPrefRanking,_CONNECT_PREF_RANKING);
CDB_LIT(KConnectPrefDirection,_CONNECT_PREF_DIRECTION);
CDB_LIT(KAgentServiceType,_AGENT_SERVICE_TYPE);
CDB_LIT(KAgentName,_AGENT_NAME);
CDB_LIT(KAgentExtName,_AGENT_EXT_NAME);
CDB_LIT(KAgentClientTimeout,_AGENT_CLIENT_TIMEOUT);
CDB_LIT(KAgentRouteTimeout,_AGENT_ROUTE_TIMEOUT);
CDB_LIT(KCommDbIntValue, _COMMDB_INT_VALUE);
CDB_LIT(KCommDbTextValue, _COMMDB_TEXT_VALUE);
CDB_LIT(KStartSQLQuery,_SQL_START_SQL_QUERY);
CDB_LIT(KWhereKeyword,_SQL_WHERE_KEYWORD);
CDB_LIT(KAndKeyword,_SQL_AND_KEYWORD);
CDB_LIT(KOrderKeyword,_SQL_ORDER_KEYWORD);
CDB_LIT(KOrderByKeyword, _SQL_ORDER_BY_KEYWORD);
CDB_LIT(KWhereHidden,_SQL_WHERE_HIDDEN);
CDB_LIT(KAndHidden,_SQL_AND_HIDDEN);
CDB_LIT(KWhereIntMatch,_SQL_WHERE_INT_MATCH);
CDB_LIT(KWhereTextMatch,_SQL_WHERE_TEXT_MATCH);
CDB_LIT(KAndIntMatch,_SQL_AND_INT_MATCH) ;
CDB_LIT(KAndTextMatch,_SQL_AND_TEXT_MATCH);
CDB_LIT(KOrTextMatch,_SQL_OR_TEXT_MATCH);
CDB_LIT(KWhereIntGreaterThan,_SQL_WHERE_INT_GREATERTHAN);

// Default widths for DB columns
const TInt KDefaultColumnWidth = KDbUndefinedLength  ;
const TInt KDefaultTextColumnWidth = 50 ;

// Non-default DB column widths
const TInt KAUTH_NAME_FIELD_WIDTH = 255 ;
const TInt KAUTH_PASS_FIELD_WIDTH = 255 ;

//	Specifies the name, type and special attributes of a column in a table.
//	Used during the creation of a new database.
struct TColumn
	{
	const TText* iName;
	TDbColType iType;
	TUint iAttributes;
	TInt iColumnWidth ;
	};

//	Specifies the name and columns of a table.
//	An array of `TTable` objects is used during the creation of a new database.
struct TTable
	{
	const TText* iName;
	const TColumn* iTable;
	};

//	Maps a bearer type and direction to a service table (Dialout,GPRS,CDMA2000)
//	Used by `OpenIAPTableViewMatchingBearerSetLC()`.
struct TMapBearerToServiceType
	{
	TCommDbBearer				bearerMask;
	TCommDbConnectionDirection	direction;
	const TText*				serviceType;
	};

//	Table defintions
TColumn const KIAPTable[]=
	{
	{COMMDB_ID, EDbColUint32, TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME, EDbColText, TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit, TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY, EDbColBit, TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{IAP_SERVICE,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{IAP_SERVICE_TYPE, EDbColText, TDbCol::ENotNull, KDefaultTextColumnWidth},
	{IAP_CHARGECARD, EDbColUint32, 0, KDefaultColumnWidth},
	//
	{0}
	};

TColumn const KDialOutISPTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{ISP_DESCRIPTION,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_TYPE,EDbColUint32,0, KDefaultColumnWidth},
	//
	{ISP_DEFAULT_TEL_NUM,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_DIAL_RESOLUTION,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_USE_LOGIN_SCRIPT,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_LOGIN_SCRIPT,EDbColLongText,0, KDefaultColumnWidth},
	{ISP_PROMPT_FOR_LOGIN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_LOGIN_NAME,EDbColText,0, KAUTH_NAME_FIELD_WIDTH},
	{ISP_LOGIN_PASS,EDbColText,0, KAUTH_PASS_FIELD_WIDTH},
	{ISP_DISPLAY_PCT,EDbColBit,0, KDefaultColumnWidth},
	{ISP_IF_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	//
	{ISP_IF_PARAMS,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IF_NETWORKS,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IF_PROMPT_FOR_AUTH,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_IF_AUTH_NAME,EDbColText,0, KAUTH_NAME_FIELD_WIDTH},
	{ISP_IF_AUTH_PASS,EDbColText,0, KAUTH_PASS_FIELD_WIDTH},
	{ISP_IF_AUTH_RETRIES,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_IF_CALLBACK_ENABLED,EDbColBit,0, KDefaultColumnWidth},
	{ISP_IF_CALLBACK_TYPE,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_IF_CALLBACK_INFO,EDbColText8,0, KDefaultTextColumnWidth},
	{ISP_CALLBACK_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	//
	{ISP_IP_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_IP_ADDR,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_NETMASK,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_GATEWAY,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_DNS_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_IP_NAME_SERVER1,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_NAME_SERVER2,EDbColText,0, KDefaultTextColumnWidth},
	//
	{ISP_ENABLE_IP_HEADER_COMP,EDbColBit,0, KDefaultColumnWidth},
	{ISP_ENABLE_LCP_EXTENSIONS,EDbColBit,0, KDefaultColumnWidth},
	{ISP_DISABLE_PLAIN_TEXT_AUTH,EDbColBit,0, KDefaultColumnWidth},
	{ISP_ENABLE_SW_COMP,EDbColBit,0, KDefaultColumnWidth},
	//
	{ISP_BEARER_NAME,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_BEARER_SPEED,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_BEARER_CE,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_INIT_STRING,EDbColText8,0, KDefaultTextColumnWidth},
	//
	{ISP_BEARER_TYPE,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_CHANNEL_CODING,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_AIUR,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_REQUESTED_TIME_SLOTS,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_MAXIMUM_TIME_SLOTS,EDbColUint32,0, KDefaultColumnWidth},
	//
	//	new multimode columns
	{ISP_BEARER_SERVICE,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_BEARER_PROTOCOL,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_RLP_VERSION,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_IWF_TO_MS,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_MS_TO_IWF,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_ACK_TIMER,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_RETRANSMISSION_ATTEMPTS,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_RESEQUENCE_PERIOD,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_V42_COMPRESSION,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_V42_CODEWORDS,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_V42_MAX_LENGTH,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_ASYMMETRY,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_USER_INIT_UPGRADE,EDbColBit,0, KDefaultColumnWidth},
	{ISP_USE_EDGE,EDbColBit,0, KDefaultColumnWidth},

	{0}
	};

TColumn const KDialInISPTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{ISP_DESCRIPTION,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_TYPE,EDbColUint32,0, KDefaultColumnWidth},
	//
	{ISP_USE_LOGIN_SCRIPT,EDbColBit,0, KDefaultColumnWidth},
	{ISP_LOGIN_SCRIPT,EDbColLongText,0, KDefaultColumnWidth},
	//
	{ISP_AUTHENTICATION,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_IF_AUTH_RETRIES,EDbColUint32,0, KDefaultColumnWidth},
	//
	{ISP_IF_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	//
	{ISP_IF_PARAMS,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IF_NETWORKS,EDbColText,0, KDefaultTextColumnWidth},
	//
	{ISP_IP_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_IP_ADDR,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_NETMASK,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_GATEWAY,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_DNS_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{ISP_IP_NAME_SERVER1,EDbColText,0, KDefaultTextColumnWidth},
	{ISP_IP_NAME_SERVER2,EDbColText,0, KDefaultTextColumnWidth},
	//
	{ISP_ENABLE_IP_HEADER_COMP,EDbColBit,0, KDefaultColumnWidth},
	{ISP_ENABLE_LCP_EXTENSIONS,EDbColBit,0, KDefaultColumnWidth},
	{ISP_DISABLE_PLAIN_TEXT_AUTH,EDbColBit,0, KDefaultColumnWidth},
	{ISP_ENABLE_SW_COMP,EDbColBit,0, KDefaultColumnWidth},
	//
	{ISP_BEARER_NAME,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_BEARER_SPEED,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_BEARER_CE,EDbColUint32,0, KDefaultColumnWidth},
	{ISP_INIT_STRING,EDbColText8,0, KDefaultTextColumnWidth},
	{ISP_USE_EDGE,EDbColBit,0, KDefaultColumnWidth},
	//
	{0}
	};

TColumn const KGPRSTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},

	{GPRS_APN,EDbColLongText,0, KDefaultColumnWidth},
	//
	{GPRS_PDP_TYPE,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{GPRS_PDP_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	//
	{GPRS_REQ_PRECEDENCE,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_REQ_DELAY,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_REQ_RELIABILITY,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_REQ_PEAK_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_REQ_MEAN_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	//
	{GPRS_MIN_PRECEDENCE,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_MIN_DELAY,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_MIN_RELIABILITY,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_MIN_PEAK_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	{GPRS_MIN_MEAN_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	//
	{GPRS_DATA_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	{GPRS_HEADER_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	{GPRS_USE_EDGE, EDbColBit, 0, KDefaultColumnWidth},
	//
	{GPRS_ANONYMOUS_ACCESS,EDbColBit,0, KDefaultColumnWidth},
	//
	{GPRS_IF_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	//
	{GPRS_IF_PARAMS,EDbColText,0, KDefaultTextColumnWidth},
	{GPRS_IF_NETWORKS,EDbColText,0, KDefaultTextColumnWidth},
	{GPRS_IF_PROMPT_FOR_AUTH,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{GPRS_IF_AUTH_NAME,EDbColText,0, KAUTH_NAME_FIELD_WIDTH},
	{GPRS_IF_AUTH_PASS,EDbColText,0, KAUTH_PASS_FIELD_WIDTH},
	//
	{GPRS_IF_AUTH_RETRIES,EDbColUint32,0, KDefaultColumnWidth},
	//
	{GPRS_IP_NETMASK,EDbColText,0, KDefaultTextColumnWidth},
	{GPRS_IP_GATEWAY,EDbColText,0, KDefaultTextColumnWidth},
	{GPRS_IP_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{GPRS_IP_ADDR,EDbColText,0, KDefaultTextColumnWidth},
	{GPRS_IP_DNS_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull,KDefaultColumnWidth},
	{GPRS_IP_NAME_SERVER1,EDbColText,0, KDefaultTextColumnWidth},
	{GPRS_IP_NAME_SERVER2,EDbColText,0, KDefaultTextColumnWidth},
	//
	{GPRS_ENABLE_LCP_EXTENSIONS,EDbColBit,0, KDefaultColumnWidth},
	{GPRS_DISABLE_PLAIN_TEXT_AUTH,EDbColBit,0, KDefaultColumnWidth},
	//
	{GPRS_AP_TYPE,EDbColUint32,0, KDefaultColumnWidth},
	//
	{GPRS_QOS_WARNING_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KLANServiceTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{LAN_IF_NETWORKS,EDbColText,0, KDefaultTextColumnWidth},

	{LAN_IF_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	//
	{LAN_IP_NETMASK,EDbColText,0, KDefaultTextColumnWidth},
	{LAN_IP_GATEWAY,EDbColText,0, KDefaultTextColumnWidth},
	{LAN_IP_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{LAN_IP_ADDR,EDbColText,0, KDefaultTextColumnWidth},
	{LAN_IP_DNS_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{LAN_IP_NAME_SERVER1,EDbColText,0, KDefaultTextColumnWidth},
	{LAN_IP_NAME_SERVER2,EDbColText,0, KDefaultTextColumnWidth},
	//
	{0}
	};

TColumn const KModemTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{MODEM_PORT_NAME,EDbColText,0, KDefaultTextColumnWidth},
	{MODEM_CONTROL_CHANNEL_PORT_NAME,EDbColText,0, KDefaultTextColumnWidth},
	{MODEM_TSY_NAME,EDbColText,0, KDefaultTextColumnWidth},
	{MODEM_CSY_NAME,EDbColText,0, KDefaultTextColumnWidth},
	{MODEM_DATA_BITS,EDbColUint8,0, KDefaultColumnWidth},
	{MODEM_STOP_BITS,EDbColUint8,0, KDefaultColumnWidth},
	{MODEM_PARITY,EDbColUint8,0, KDefaultColumnWidth},
	{MODEM_RATE,EDbColUint32,0, KDefaultColumnWidth},
	{MODEM_HANDSHAKING,EDbColUint32,0, KDefaultColumnWidth},
	{MODEM_SPECIAL_RATE,EDbColUint32,0, KDefaultColumnWidth},
	{MODEM_XON_CHAR,EDbColUint8,0, KDefaultColumnWidth},
	{MODEM_XOFF_CHAR,EDbColUint8,0, KDefaultColumnWidth},
	//
	{MODEM_FAX_CLASS_PREF,EDbColUint8,0, KDefaultColumnWidth},
	{MODEM_SPEAKER_PREF,EDbColUint8,0, KDefaultColumnWidth},
	{MODEM_SPEAKER_VOL_PREF,EDbColUint8,0, KDefaultColumnWidth},
	//
	{MODEM_MODEM_INIT_STRING,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_DATA_INIT_STRING,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_FAX_INIT_STRING,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_ISP_INIT_STRING,EDbColText8,0, KDefaultTextColumnWidth},
	//
	{MODEM_DIAL_PAUSE_LENGTH,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_CARRIER_TIMEOUT,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_AUTO_ANSWER_RING_COUNT,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_SPEAKER_VOL_CONTROL_LOW,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_SPEAKER_VOL_CONTROL_MEDIUM,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_SPEAKER_VOL_CONTROL_HIGH,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_SPEAKER_ALWAYS_OFF,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_SPEAKER_ON_UNTIL_CARRIER,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_SPEAKER_ALWAYS_ON,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_SPEAKER_ON_AFTER_DIAL_UNTIL_CARRIER,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_DIAL_TONE_WAIT_MODIFIER,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_CALL_PROGRESS_1,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_CALL_PROGRESS_2,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_CALL_PROGRESS_3,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_CALL_PROGRESS_4,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_ECHO_OFF,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_VERBOSE_TEXT,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_QUIET_OFF,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_QUIET_ON,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_DIAL_COMMAND_STATE_MODIFIER,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_ON_LINE,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_RESET_CONFIGURATION,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_RETURN_TO_FACTORY_DEFS,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_DCD_ON_DURING_LINK,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_DTR_HANG_UP,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_DSR_ALWAYS_ON,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_RTS_CTS_HANDSHAKE,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_XON_XOFF_HANDSHAKE,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_ESCAPE_CHARACTER,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_ESCAPE_GUARD_PERIOD,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_FAX_CLASS_INTERROGATE,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_FAX_CLASS,EDbColText8,0, KDefaultTextColumnWidth},
	//
	{MODEM_NO_DIAL_TONE,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_BUSY,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_NO_ANSWER,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_CARRIER,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_CONNECT,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_COMPRESSION_CLASS_5,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_COMPRESSION_V42BIS,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_COMPRESSION_NONE,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_PROTOCOL_LAPD,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_PROTOCOL_ALT,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_PROTOCOL_ALTCELLULAR,EDbColText8,0, KDefaultTextColumnWidth},
	{MODEM_PROTOCOL_NONE,EDbColText8,0, KDefaultTextColumnWidth},
	//
	{MODEM_MESSAGE_CENTRE_NUMBER,EDbColText,0, KDefaultTextColumnWidth},
	{MODEM_MESSAGE_VALIDITY_PERIOD,EDbColUint32,0, KDefaultColumnWidth},
	{MODEM_MESSAGE_DELIVERY_REPORT,EDbColBit,0, KDefaultColumnWidth},
	//
	{MODEM_MIN_SIGNAL_LEVEL,EDbColUint32,0, KDefaultColumnWidth},
	//
	{0}
	};

TColumn const KLocationTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{LOCATION_INTL_PREFIX_CODE,EDbColText,0, KDefaultTextColumnWidth},
	{LOCATION_NAT_PREFIX_CODE,EDbColText,0, KDefaultTextColumnWidth},
	{LOCATION_NAT_CODE,EDbColText,0, KDefaultTextColumnWidth},
	{LOCATION_AREA_CODE,EDbColText,0, KDefaultTextColumnWidth},
	{LOCATION_DIAL_OUT_CODE,EDbColText,0, KDefaultTextColumnWidth},
	{LOCATION_DISABLE_CALL_WAITING_CODE,EDbColText,0, KDefaultTextColumnWidth},
	{LOCATION_MOBILE,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{LOCATION_USE_PULSE_DIAL,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{LOCATION_WAIT_FOR_DIAL_TONE,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{LOCATION_PAUSE_AFTER_DIAL_OUT,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{0}
	};

TColumn const KChargecardTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{CHARGECARD_ACCOUNT_NUMBER,EDbColText,0, KDefaultTextColumnWidth},
	{CHARGECARD_PIN,EDbColText,0, KDefaultTextColumnWidth},
	{CHARGECARD_LOCAL_RULE,EDbColText,0, KDefaultTextColumnWidth},
	{CHARGECARD_NAT_RULE,EDbColText,0, KDefaultTextColumnWidth},
	{CHARGECARD_INTL_RULE,EDbColText,0, KDefaultTextColumnWidth},
	{0}
	};

TColumn const KProxiesTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
//	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},		// Not having a row name is historical - it could be removed from other tables to reduce localisation effort
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{PROXY_ISP,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{PROXY_SERVICE_TYPE,EDbColText,0, KDefaultTextColumnWidth},
	{PROXY_USE_PROXY_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{PROXY_SERVER_NAME,EDbColLongText,0, KDefaultColumnWidth},
	{PROXY_PROTOCOL_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{PROXY_PORT_NUMBER,EDbColUint32,0, KDefaultColumnWidth},
	{PROXY_EXCEPTIONS,EDbColLongText,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KWAPAccessPointTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{WAP_CURRENT_BEARER,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{WAP_START_PAGE,EDbColLongText,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KWAPIPBearerTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{WAP_ACCESS_POINT_ID,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{WAP_GATEWAY_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	{WAP_IAP,EDbColUint32,0, KDefaultColumnWidth},
	//	The following two fields are obsoleted for WAP2.0 but maintained for
	//	WAP1.0. They should be removed in Symbian OS 8.0
	{WAP_WSP_OPTION,EDbColUint8,0, KDefaultColumnWidth},
	{WAP_SECURITY,EDbColBit,0, KDefaultColumnWidth},
	//
	{WAP_PROXY_PORT,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{WAP_PROXY_LOGIN_NAME,EDbColText,0, KAUTH_NAME_FIELD_WIDTH},
	{WAP_PROXY_LOGIN_PASS,EDbColText,0, KAUTH_PASS_FIELD_WIDTH},
	//
	{0}
	};

TColumn const KWAPSMSBearerTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{WAP_ACCESS_POINT_ID,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{WAP_GATEWAY_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	{WAP_SERVICE_CENTRE_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	{WAP_WSP_OPTION,EDbColUint8,0, KDefaultColumnWidth},
	{WAP_SECURITY,EDbColBit,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KConnectionPreferencesTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
//	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},		// Not having a row name is historical - it could be removed from other tables to reduce localisation effort
//	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},		// Hidden field is not required as Connection Preferences can not be accessed via the normal views
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{CONNECT_PREF_RANKING,EDbColUint32,0, KDefaultColumnWidth},
	{CONNECT_PREF_DIRECTION,EDbColUint32,0, KDefaultColumnWidth},
	{CONNECT_PREF_BEARER_SET,EDbColUint32,0, KDefaultColumnWidth},
	{CONNECT_PREF_DIALOG_PREF,EDbColUint32,0, KDefaultColumnWidth},
	{CONNECT_PREF_IAP,EDbColUint32,0, KDefaultColumnWidth},
	//
	{0}
	};

TColumn const KAgentLookup[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{AGENT_FRIENDLY_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{AGENT_FILENAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{0}
	};

TColumn const KAgentTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
//	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},		// Not having a row name is historical - it could be removed from other tables to reduce localisation effort
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{AGENT_SERVICE_TYPE,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{AGENT_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{AGENT_EXT_NAME,EDbColText,0, KDefaultTextColumnWidth},
	{AGENT_CLIENT_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	{AGENT_ROUTE_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	//
	{0}
	};

TColumn const KGlobalSettingsTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	//
	{COMMDB_INT_VALUE,EDbColUint32,0, KDefaultColumnWidth},
	{COMMDB_TEXT_VALUE,EDbColText,0, KDefaultTextColumnWidth},
	{0}
	};

TColumn const KDefaultGPRSTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{DEFAULT_GPRS_USAGE,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_APN,EDbColText, 0, KDefaultTextColumnWidth},
	//
	{DEFAULT_GPRS_PDP_TYPE,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{DEFAULT_GPRS_PDP_ADDRESS,EDbColText, 0, KDefaultTextColumnWidth},
	//
	{DEFAULT_GPRS_PRECEDENCE,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_DELAY,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_RELIABILITY,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_PEAK_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_MEAN_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	//
	{DEFAULT_GPRS_MIN_PRECEDENCE,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_MIN_DELAY,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_MIN_RELIABILITY,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_MIN_PEAK_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_MIN_MEAN_THROUGHPUT,EDbColUint32,0, KDefaultColumnWidth},
	//
	{DEFAULT_GPRS_DATA_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_HEADER_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	{DEFAULT_GPRS_USE_EDGE, EDbColBit, 0, KDefaultColumnWidth},
	//
	{DEFAULT_GPRS_ANONYMOUS_ACCESS,EDbColBit,0, KDefaultColumnWidth},
	//
	{0}
	};

TColumn const KCBTDeviceTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{BT_DEV_ADD,EDbColText8,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{BT_DEV_DFLT_NAME,EDbColLongText16,0, KDefaultColumnWidth},
	{BT_DEV_FRIENDLY_NAME,EDbColLongText16,0, KDefaultColumnWidth},
	{BT_DEVICE_CLASS,EDbColUint32,0, KDefaultColumnWidth},
	{BT_LINKKEY,EDbColText8,0, KDefaultTextColumnWidth},
	{BT_DEVICE_GLOBAL_SECURITY, EDbColUint32,0, KDefaultColumnWidth},
	{BT_DEV_STATE, EDbColUint32, TDbCol::ENotNull, KDefaultColumnWidth},
	//specific details concerning the juice of each device
	{BT_PAGE_SCAN_REP_MODE, EDbColUint32, 0, KDefaultColumnWidth}, 
	{BT_PAGE_SCAN_PERIOD_MODE, EDbColUint32, 0, KDefaultColumnWidth}, 
	{BT_PAGE_SCAN_MODE, EDbColUint32, 0, KDefaultColumnWidth}, 
	{BT_SPARE, EDbColUint32, 0, KDefaultColumnWidth}, 
	{BT_CLK_OFFSET, EDbColUint32, 0, KDefaultColumnWidth}, 
	{BT_COD, EDbColUint32, 0, KDefaultColumnWidth}, 
	{0}
	};

TColumn const KCBTDefaultServiceTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{BT_DFLT_SER_NAME,EDbColText16,0, KDefaultTextColumnWidth},
	{BT_DFLT_SER_UUID,EDbColText8,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{BT_DFLT_VIRTUAL_PORT,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{BT_DFLT_DEV_ADD,EDbColText8,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{BT_DFLT_SECURITY_LEVEL,EDbColUint8,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KCBTSecurityTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{BT_DEV_ADD,EDbColText8,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{BT_SEC_DEVICE_SECURITY,EDbColUint32,0, KDefaultColumnWidth},
	{BT_SEC_UID,EDbColUint32,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KCBTPersistTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{BT_PERSIST_COD,EDbColUint32,0 , KDefaultColumnWidth},
	{BT_PERSIST_PAGE_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_PAGE_SCAN_INTERVAL,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_PAGE_SCAN_WINDOW,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_INQUIRY_SCAN_INTERVAL,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_INQUIRY_SCAN_WINDOW,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_HOLD_MODE_ACTIVITY,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_SCO_FLOW_CONTROL,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_PAGE_SCAN_PERIOD,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_PAGE_SCAN_MODE,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_POWER_SETTINGS,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_SCAN,EDbColUint32,0, KDefaultColumnWidth},
	{BT_PERSIST_LOCAL_NAME,EDbColLongText16,0 , KDefaultColumnWidth},
	{BT_PERSIST_IAC_LAP, EDbColLongText16, 0, KDefaultColumnWidth},
	{BT_PERSIST_STATE, EDbColUint32, TDbCol::ENotNull, KDefaultColumnWidth},
	{0}
	};



TColumn const KCdma2000PacketServiceTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{CDMA_IWF_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{CDMA_SERVICE_OPTION,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{CDMA_PDP_TYPE,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{CDMA_PDP_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	//
	{CDMA_REQ_FWD_PRIORITY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_PRIORITY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_FWD_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_FWD_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_FWD_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_MIN_FWD_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_MIN_REV_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_FWD_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_REV_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_FWD_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_REV_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	//
	{CDMA_DATA_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	{CDMA_HEADER_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	//
	{CDMA_ANONYMOUS_ACCESS,EDbColBit,0, KDefaultColumnWidth},

	{CDMA_IF_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	//
	{CDMA_IF_PARAMS,EDbColText,0, KDefaultTextColumnWidth},
	{CDMA_IF_NETWORKS,EDbColText,0, KDefaultTextColumnWidth},
	{CDMA_IF_PROMPT_FOR_AUTH,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{CDMA_IF_AUTH_NAME,EDbColText,0, KAUTH_NAME_FIELD_WIDTH},
	{CDMA_IF_AUTH_PASS,EDbColText,0, KAUTH_PASS_FIELD_WIDTH},
	//
	{CDMA_IF_AUTH_RETRIES,EDbColUint32,0, KDefaultColumnWidth},
	//
	{CDMA_IP_NETMASK,EDbColText,0, KDefaultTextColumnWidth},
	{CDMA_IP_GATEWAY,EDbColText,0, KDefaultTextColumnWidth},
	{CDMA_IP_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{CDMA_IP_ADDR,EDbColText,0, KDefaultTextColumnWidth},
	{CDMA_IP_DNS_ADDR_FROM_SERVER,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{CDMA_IP_NAME_SERVER1,EDbColText,0, KDefaultTextColumnWidth},
	{CDMA_IP_NAME_SERVER2,EDbColText,0, KDefaultTextColumnWidth},
	//
	{CDMA_ENABLE_LCP_EXTENSIONS,EDbColBit,0, KDefaultColumnWidth},
	{CDMA_DISABLE_PLAIN_TEXT_AUTH,EDbColBit,0, KDefaultColumnWidth},
	//
	{CDMA_AP_TYPE,EDbColUint32,0, KDefaultColumnWidth},
	//
	{CDMA_QOS_WARNING_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_RLP_MODE,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	//MobileIP
	{CDMA_MIP,EDbColBit,0, KDefaultColumnWidth},
	{CDMA_MIP_HA_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	{CDMA_MIP_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KDefaultCdma2000SettingsTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{DEFAULT_CDMA_USAGE,EDbColUint32,0, KDefaultColumnWidth},
	{DEFAULT_CDMA_IWF_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	//
	{DEFAULT_CDMA_SERVICE_OPTION,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{DEFAULT_CDMA_PDP_TYPE,EDbColUint32,TDbCol::ENotNull, KDefaultColumnWidth},
	{DEFAULT_CDMA_PDP_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	//
	{CDMA_REQ_FWD_PRIORITY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_PRIORITY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_FWD_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_FWD_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_FWD_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_REQ_REV_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_MIN_FWD_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_MIN_REV_BITRATE,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_FWD_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_REV_LOSS,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_FWD_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	{CDMA_ACCPT_REV_MAXDELAY,EDbColUint32,0, KDefaultColumnWidth},
	//
	{DEFAULT_CDMA_DATA_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	{DEFAULT_CDMA_HEADER_COMPRESSION,EDbColBit,0, KDefaultColumnWidth},
	//
	{DEFAULT_CDMA_ANONYMOUS_ACCESS,EDbColBit,0, KDefaultColumnWidth},
	//MobileIP
	{DEFAULT_CDMA_MIP,EDbColBit,0, KDefaultColumnWidth},
	{DEFAULT_CDMA_MIP_HA_ADDRESS,EDbColText,0, KDefaultTextColumnWidth},
	{DEFAULT_CDMA_MIP_TIMEOUT,EDbColUint32,0, KDefaultColumnWidth},
	{0}
	};

TColumn const KAccessTypeTable[]=
  	{	
  	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
  	//
	{TABLE_ACC_NAME,EDbColText16,TDbCol::ENotNull, KDefaultTextColumnWidth},
  	{TABLE_ACC_TYPE,EDbColUint8,0, KDefaultColumnWidth},
  	{0}
  	};

TColumn const KSecureSocketTable[]=
	{
	{COMMDB_ID,EDbColUint32,TDbCol::EAutoIncrement|TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_HIDDEN,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	{COMMDB_READ_ONLY,EDbColBit,TDbCol::ENotNull, KDefaultColumnWidth},
	//
	{SS_PROTO_NAME,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{SS_PROTO_LIBRARY,EDbColText,TDbCol::ENotNull, KDefaultTextColumnWidth},
	{0}
	};
// Indices into array of tables KTableList. Make sure this list is kept in step
// with the array.
enum
	{
	EIAPTableIndex,
	EDialOutISPTableIndex,
	EDialInISPTableIndex,
	EWAPAccessPointTableIndex,
	EWAPIPBearerTableIndex,
	EWAPSMSBearerTableIndex,
	EOutgoingGPRSTableIndex,
	EIncomingGPRSTableIndex,
	ELANServiceTableIndex,
	EModemTableIndex,
	ELocationTableIndex,
	EChargecardTableIndex,
	EProxiesTableIndex,
	EConnectionPreferencesTableIndex,
	EAgentTableIndex,
	EGlobalSettingsTableIndex,
	ECBTDeviceTableIndex,
	ECBTDefaultServiceTableIndex,
	EDefaultGPRSTableIndex,
	ECBTSecurityTableIndex,
	ECBTPersistTableIndex,
	EAgentLookupIndex,
	ESecureSocketTableIndex,
	ECdma2000PacketServiceTableIndex,
	EDefaultCdma2000SettingsTableIndex,
	EAccessTypeTableIndex
	};
//	Array of Tables. Make sure the order corresponds with that of the enum above.
TTable const KTableList[]=
	{
	{IAP, KIAPTable},
	{DIAL_OUT_ISP, KDialOutISPTable},
	{DIAL_IN_ISP, KDialInISPTable},
	{WAP_ACCESS_POINT, KWAPAccessPointTable},
	{WAP_IP_BEARER, KWAPIPBearerTable},
	{WAP_SMS_BEARER, KWAPSMSBearerTable},
	{OUTGOING_GPRS, KGPRSTable},
	{INCOMING_GPRS, KGPRSTable},
	{LAN_SERVICE,KLANServiceTable},
	{MODEM, KModemTable},
	{LOCATION, KLocationTable},
	{CHARGECARD, KChargecardTable},
	{PROXIES, KProxiesTable},
	{CONNECTION_PREFERENCES, KConnectionPreferencesTable},
	{AGENT, KAgentTable},
	{GLOBAL_SETTINGS, KGlobalSettingsTable},
	{BT_DEVICE_TABLE, KCBTDeviceTable},
	{BT_DEFAULT_TABLE, KCBTDefaultServiceTable},
	{DEFAULT_GPRS, KDefaultGPRSTable},
	{BT_SECURITY_TABLE, KCBTSecurityTable},
	{BT_PERSIST_TABLE, KCBTPersistTable}, 
	{AGENT_LOOKUP,KAgentLookup},
	{SS_PROTO_TABLE,KSecureSocketTable},
	{CDMA2000_PACKET_SERVICE_TABLE,KCdma2000PacketServiceTable},
	{DEFAULT_CDMA2000_SETTINGS_TABLE,KDefaultCdma2000SettingsTable},
	{ACCESS_TYPE_TABLE, KAccessTypeTable},
	{0}
	};

const TInt KNumServiceType = 8;
const TMapBearerToServiceType KMap[KNumServiceType] =
	{
	{KCommDbBearerCSD,		ECommDbConnectionDirectionOutgoing, DIAL_OUT_ISP},
	{KCommDbBearerCSD,		ECommDbConnectionDirectionIncoming, DIAL_IN_ISP},
	{KCommDbBearerWcdma,	ECommDbConnectionDirectionOutgoing, OUTGOING_GPRS},
	{KCommDbBearerCdma2000,	ECommDbConnectionDirectionOutgoing, CDMA2000_PACKET_SERVICE_TABLE},
	 //	The following two mappings are only required for tornado
	{KCommDbBearerWcdma,	ECommDbConnectionDirectionIncoming, INCOMING_GPRS},
	{KCommDbBearerCdma2000,	ECommDbConnectionDirectionIncoming, CDMA2000_PACKET_SERVICE_TABLE},
	{KCommDbBearerLAN,		ECommDbConnectionDirectionIncoming,	LAN_SERVICE},
	{KCommDbBearerLAN,		ECommDbConnectionDirectionOutgoing,	LAN_SERVICE}
	};

//	Given `aBearerSet` and `aDirection` `CreateIapQuery()` returns a database
//	query that selects the relevant entries from the IAP table.
/*void CreateIapQuery(TUint32 aBearerSet,
					TCommDbConnectionDirection aDirection, TDes *aQuery)
	{
	aQuery->Append(TPtrC(IAP));

	static const TLitC<15> KServiceType={14,L"IAPServiceType"};
	__ASSERT_DEBUG(TPtrC(IAP_SERVICE_TYPE)==KServiceType, User::Invariant());

	//	Note if requesting all types this does not produce the best result
	//	i.e. no where expression. This could be optimised by pre testing for
	//	aBearerSet == KCommDbBearerAny
	TBool firstOne = ETrue;
	for (int i = 0; i < KNumServiceType; i++)
		{
		if ((aBearerSet & KMap[i].bearerMask) != 0 &&
			(aDirection == KMap[i].direction ||
			aDirection == ECommDbConnectionDirectionUnknown ))
			{
			const TPtrC serviceType(KMap[i].serviceType);
			if (firstOne)
				{
				aQuery->AppendFormat(KWhereTextMatch,&KServiceType,&serviceType);
				firstOne = EFalse;
				}
			else
				{
				aQuery->AppendFormat(KOrTextMatch,&KServiceType,&serviceType);
				}
			}
		}
	}

//	Replace single quotes `'` with two single quotes `''` as text queries are
//	delimited by single quotes
// This is excesivly complex for what it does - could just scan string and
// insert ' where required. Fix in next revision.
void FindAndReplaceSingleQuote(const TDesC& aSrc, TDes& aTrg)
	{
	__ASSERT_DEBUG(aTrg.MaxLength()>=KTwiceMaxFieldLength, User::Invariant());

	TChar ch(KSingleQuoteChar);
	TInt pos=aSrc.Locate(ch);
	if (pos<0)
		{
		aTrg.Copy(aSrc);
		return;				// Exit point if no quotes (usual case)
		}

	TBuf16<KCommsDbSvrMaxColumnNameLength> rem;	// This is a wast of stack
	rem.Copy(aSrc);
	while (pos>=0)
		{
		aTrg.Append(rem.Left(pos+1));
		aTrg.Append(ch);
		rem.Delete(0,pos+1);
		if (rem.Length()>0)
			{
			pos=rem.Locate(ch);
			if (pos==KErrNotFound)
				aTrg.Append(rem);
			}
		else
			pos=KErrNotFound;
		}
	}*/

}
using namespace commdb_dll;


#endif