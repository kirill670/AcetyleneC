//
//    in6_if.h - control API between the stack and IPv6 interfaces
//
//    Copyright (C) 1999, 2000 Nokia Research Center
//
//    This software has been implemented in the 6PACK
//    project at the Mobile Networks Laboratory (MNW)
//
//    http://www.research.nokia.com/projects/6pack/
//
////////////////////////////////////////////////////////////////

/** @file in6_if.h
Specifies the IPv6 extensions for CNifIfBase::Control() API
defined in the standard EPOC header file in_iface.h.

@publishedAll
@released
*/

#ifndef __IN6_IF_H__
#define __IN6_IF_H__

#include <e32std.h>
#include "in_iface.h"	// TSoIfInfo

//	CNifIfBase::Control(aLevel, aName, aOption, ..)
//  aLevel is KSOLInterface defined in in_iface.h in standard EPOC

//	IPv6 specific aName constants and aOption structures

/**
* Option to get the current network interface driver operation parameters to 
* the passed TSoIfInfo6 structure. 
* @since v7.0
* @publishedAll
* @released
*/
const TUint KSoIfInfo6	= 0x202;

/**
* A TSoIfInfo::iFeatures flag to indicate that the interface requires Neighbour 
* Discovery.
*
* @note
*	For IPv4 this enables ARP for the interface. The NIF must
*	pass received ARP packets to the stack, and accept ARP
*	packets for sending from the stack.
* @since v7.0
* @publishedAll
* @released
*/
const TUint KIfNeedsND	= 0x00000100;

class TSoIfInfo6 : public TSoIfInfo		// aOption when aName == KSoIfInfo
	/**
	* Extends the TSoIfInfo, the current network interface operation parameters class, 
	* for a receiving MTU.
	* @since v7.0
	* @publishedAll
	* @released
	*/
	{
public:
	/** Maximum transmission unit for receiving. */
	TInt iRMtu;
	};

class TSoInet6IfConfig : public TSoIfConfigBase		// aOption when aName == KSoIfConfig
	/**
	* IPv6 interface configuration. 
	* @since v7.0
	* @publishedAll
	* @released
	*/
	{
public:	
	/** The local interface id */
	TSockAddr iLocalId;
	/** The remote interface id (or KAFUnspec, if not applicaple) */
	TSockAddr iRemoteId;
	/** Unused highest significant bits in interface id (usually 0) */
	TUint idPaddingBits;
	/** 1st DNS address (or Unspecified address, if none) */
	TInetAddr iNameSer1;
	/** 2nd DNS address (or Unspecified address, if none) */
	TInetAddr iNameSer2;
	};

#endif
