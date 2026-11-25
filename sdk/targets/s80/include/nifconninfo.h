/**
@file nifconninfo.h

Network adaptor connection information standard data structures

Copyright (c) 2003 Symbian Ltd.  All rights reserved.
*/


#ifndef __NIFCONNINFO_H__
#define __NIFCONNINFO_H__

#include <es_enum.h>	// for TSubConnectionInfo
#include <etelqos.h>    // for all the QoS parameter types

enum TGPRSContextType
/**
 * The type of the GPRS context
 * Values above 2000 are reserved for future use
 * @publishedPartner
 * @released since v7.0s
 */
	{
	EGPRSPrimary,          ///< Values from 0 - 999 are for primary contexts
	EGPRSSecondary = 1000  ///< Values from 1000 - 1999 are for secondary contexts

	};

class TSubConnectionInfoGprsUmts : public TSubConnectionInfo
/**
 * Basic parameters for a generic GPRS/UMTS connection
 * @publishedPartner
 * @released since v7.0s
 * @note Classes with more specific GPRS/UMTS parameters should derive from this class, as clients can assume that any less specific TSubConnectionInfo-derived classes are acceptable for use in GetSubConnectionInfo() calls.
 * @see TConnectionType
 */
	{
public:
	TGPRSContextType iContextType;
	};

class TSubConnectionInfoR99_R4 : public TSubConnectionInfoGprsUmts
/**
 * QoS parameters appropriate for the GPRS/UMTS Rel99 and UMTS Rel4 QoS profile.
 * @publishedPartner
 * @released since v7.0s
 */
{
public:
	RPacketQoS::TTrafficClass				iTrafficClass;
	RPacketQoS::TDeliveryOrder				iDeliveryOrderReqd;
	RPacketQoS::TErroneousSDUDelivery		iDeliverErroneousSDU;
	TInt									iMaxSDUSize;
	RPacketQoS::TBitRate					iMaxRate;
	RPacketQoS::TBitErrorRatio				iBER;
	RPacketQoS::TSDUErrorRatio				iSDUErrorRatio;
	RPacketQoS::TTrafficHandlingPriority	iTrafficHandlingPriority;
	TInt									iTransferDelay;
	RPacketQoS::TBitRate					iGuaranteedRate;
}

#endif // __NIFCONNINFO_H__

