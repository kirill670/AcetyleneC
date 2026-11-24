// GSMUNMSPACEMOBMSG.H
//
// Copyright (c) 2004-2005 Symbian Software Ltd.  All rights reserved.
//

/** 
@file 
Multimode SMS common API header file.

Describes common MM ETel RMobileSmsMessaging API types.
The types are duplicated from ETELMM.h in an effort to separate SMS from ETEL.
Correspondent ETEL types could be found in ETELMM.h, class RMobileSmsMessaging.

@publishedPartner
@released
*/

#ifndef __GSMUNMSPACEMOBMSG_H__
#define __GSMUNMSPACEMOBMSG_H__


namespace NMobileSmsMessaging
	{
	
/** PDU types.
Modes: Common 

@ref class class RMobileSmsMessaging : public RTelSubSessionBase
*/
	// Definitions for sizes of TPDU and User Data fields
	enum 
		{ 
		KGsmTpduSize = 165,		// 140 bytes user data + 25 bytes TPDU header
		KCdmaTpduSize  = 256	// Max size of Bearer Data in Transport Layer message
		};

/** A typedef'd buffer for GSM or WCDMA message data. */
	typedef TBuf8<KGsmTpduSize>			TMobileSmsGsmTpdu;
/** A typedef'd buffer for CDMA message data. */
	typedef TBuf8<KCdmaTpduSize>		TMobileSmsCdmaTpdu;
	}

#endif // __GSMUNMSPACEMOBMSG_H__
