/** @file in_sock.h
 * @publishedAll
 * @released
 *
 * IPv6/IPv4 socket library public header 
 * Copyright (c) 2003 Symbian Ltd.  All rights reserved. 
 */

#ifndef __IN_SOCK_H__
#define __IN_SOCK_H__

#ifndef __ES_SOCK_H__
#include <es_sock.h>
#endif

/** @name Address family IDs */
//@{
/** Identifies the TCP/IP (v4) protocol family. */
const TUint KAfInet				= 0x0800;   // ///< IPv4 address family
/** Identifies the TCP/IP (v6) protocol family. */
const TUint KAfInet6			= 0x0806;   // ///< IPv6 address family
//@}

/**
Unknown Protocol ID 
@internalTechnology
*/
const TUint KProtocolUnknown = 0xdead;

/** @name IPv4 protocol IDs */
//@{
const TUint KProtocolInetIcmp	= 1;		///< Identifies the ICMP protocol.
const TUint KProtocolInetTcp	= 6;		///< Identifies the TCP protocol.
const TUint KProtocolInetUdp	= 17;		///< Identifies the UDP protocol.
const TUint KProtocolInetIp		= 0x100;	///< Identifies the IP protocol. // Pseudo protocol
//@}

/**
 *	@name Inet6 specific protocol IDs
 *	IPv6 uses the same protocol ID space as IPv4, one only needs to
 *	define symbols for protocol IDs that are needed in addition to
 *	those of IPv4.
 */
 //@{
/** IP inside IP (IPIP). */
const TUint KProtocolInet6Ipip	= 41;		// ///< IPv6 encapsulation
/** Identifies the ICMPv6 protocol. */
const TUint KProtocolInet6Icmp	= 58;		// ///< ICMPv6 protocol
/** Identifies the IPv6 protocol. */
const TUint KProtocolInet6Ip	= 0xF00;	// ///< Pseudo protocol
//@}

/**  @name Socket option/ioctl levels */
//@{
/** ICMP level. */
const TUint KSolInetIcmp		= 0x101;	// ///< ICMP and ICMPv6 options/ioctls
/** TCP level. */
const TUint KSolInetTcp			= 0x106;	// ///< TCP options/ioctls
/** UDP level. */
const TUint KSolInetUdp			= 0x111;	// ///< UDP options/ioctls
/** IP level. */
const TUint KSolInetIp			= 0x100;	// ///< IP options/ioctls
/** Interface control level. */
const TUint KSolInetIfCtrl		= 0x201;	// ///< Interface options/ioctls
/** Route control level. */
const TUint KSolInetRtCtrl		= 0x202;	// ///< Route options/ioctls
//@}

/**
DNS control level.
@deprecated No longer supported
*/
const TUint KSolInetDnsCtrl		= 0x204;

/** Interface query options. */
const TUint KSolInetIfQuery		= 0x206;	// ///< Interface information

/** @name Address size constants */
//@{
/** Maximum IPv4 address length. */
const TInt KInetAddrMaxBits         = 32;
/** Maximum IPv6 address length. */
const TInt KInet6AddrMaxBits        = 128;
//@}

/** @name Port constants */
//@{
/** Any port flag (0). */
const TUint KInetPortAny			= 0x0000; 
/** No port flag (0). */
const TUint KInetPortNone			= 0x0000;
/** Minimum value of an automatically allocated port. */
const TUint KInetMinAutoPort		= 32768;	// ///< Start of ephemeral port range
/** Maximum value of an automatically allocated port. */
const TUint KInetMaxAutoPort		= 60999;	// ///< End of ephemeral port range
//@}

// IPv4 address constants and utilities
/** 
* Forms a 32-bit integer IPv4 address from the normal dotted-decimal representation. 
* 
* The four arguments are the four parts of the IPv4 address.
* 
* Example:
* @code
* TInetAddr addr;
* const TUint32 KInetAddr = INET_ADDR(194,129,2,54);
* addr.SetAddress(KInetAddr);
* @endcode 
*/
#define INET_ADDR(a,b,c,d) (TUint32)((((TUint32)(a))<<24)|((b)<<16)|((c)<<8)|(d))

/**  @name IPv4 address constants */
//@{
/** Any address flag (0.0.0.0). */
const TUint32 KInetAddrAny				= INET_ADDR(0,0,0,0);
/** No address mask (0.0.0.0). */
const TUint32 KInetAddrNone				= INET_ADDR(0,0,0,0);
/** All addresses mask (255.255.255.255). */
const TUint32 KInetAddrAll				= INET_ADDR(255,255,255,255);
/** Broadcast address (255.255.255.255). */
const TUint32 KInetAddrBroadcast		= INET_ADDR(255,255,255,255);
/** Loopback address (127.0.0.1). */
const TUint32 KInetAddrLoop				= INET_ADDR(127,0,0,1);

/** Group address range start. */
const TUint32 KInetAddrGroupUnspec		= INET_ADDR(224,0,0,0);
/** All hosts address (224.0.0.1). */
const TUint32 KInetAddrGroupAllHosts	= INET_ADDR(224,0,0,1);

/** . */
const TUint32 KInetAddrLinkLocalNet		= INET_ADDR(169,254,0,0);
/** . */
const TUint32 KInetAddrLinkLocalNetMask	= INET_ADDR(255,255,0,0);

/** All addresses mask (0.0.0.0). */
const TUint32 KInetAddrMaskAll			= INET_ADDR(0,0,0,0);
/** All bits mask (255.255.255.255). */
const TUint32 KInetAddrMaskHost			= INET_ADDR(255,255,255,255);
//@}


// The following are deprecated and should not be used
/** Class A net mask (255.0.0.0).
@deprecated */
const TUint32 KInetAddrNetMaskA			= INET_ADDR(255,0,0,0);
/** Class A host mask (255.255.255.0).
@deprecated */
const TUint32 KInetAddrHostMaskA		= ~KInetAddrNetMaskA;
/** Number of bits to right-shift a Class A address to obtain the network number.
@deprecated */
const TInt KInetAddrShiftA				= 24;
/** Class B net mask (255.255.0.0).
@deprecated */
const TUint32 KInetAddrNetMaskB 		= INET_ADDR(255,255,0,0);
/** Class B host mask (0.0.255.255).
@deprecated */
const TUint32 KInetAddrHostMaskB		= ~KInetAddrNetMaskB;
/** Number of bits to right-shift a Class B address to obtain the network number.
@deprecated */
const TInt KInetAddrShiftB				= 16;
/** Class C net mask (255.255.255.0).
@deprecated */
const TUint32 KInetAddrNetMaskC 		= INET_ADDR(255,255,255,0);
/** Class C host mask (0.255.255.255).
@deprecated */
const TUint32 KInetAddrHostMaskC		= ~KInetAddrNetMaskC;
/** Number of bits to right-shift a Class C address to obtain the network number.
@deprecated */
const TInt KInetAddrShiftC				= 8;

/** @deprecated */
const TUint32 KInetAddrIdMaskA			= 0x80000000;
/** @deprecated */
const TUint32 KInetAddrIdValA			= 0x00000000;
/** @deprecated */
const TUint32 KInetAddrIdMaskB			= 0xc0000000;
/** @deprecated */
const TUint32 KInetAddrIdValB			= 0x80000000;
/** @deprecated */
const TUint32 KInetAddrIdMaskC			= 0xe0000000;
/** @deprecated */
const TUint32 KInetAddrIdValC			= 0xc0000000;
/** @deprecated */
const TUint32 KInetAddrIdMaskD			= 0xf0000000;
/** @deprecated */
const TUint32 KInetAddrIdValD			= 0xe0000000;
/** @deprecated */
const TUint32 KInetAddrIdMaskE			= 0xf8000000;
/** @deprecated */
const TUint32 KInetAddrIdValE			= 0xf0000000;

enum TInetAddrClass
	{
	EInetClassUnknown = 0,
	EInetClassA,
	EInetClassB,
	EInetClassC,
	EInetClassD,
	EInetClassE,
	EInetMulticast = EInetClassD,
	EInetExperimental = EInetClassE
	};

/** IPv4 socket address */
struct SInetAddr
	{ TUint32 iAddr; };


class TIp6Addr
/** A raw 128-bit IPv6 address stored in network byte order. */
	{
public:
	IMPORT_C TBool IsUnicast() const;		// ///< TRUE, if address is not IPv6 unspecied or IPv6 multicast
	IMPORT_C TBool IsMulticast() const;		// ///< TRUE, if address is IPv6 multicast (ff::/8)
	IMPORT_C TBool IsLoopback() const;		// ///< TRUE, if address is IPv6 loopback (::1)
	IMPORT_C TBool IsUnspecified() const;	// ///< TRUE, if address is IPv6 unspecified (::)
	IMPORT_C TBool IsLinkLocal() const;		// ///< TRUE, if address is IPv6 Link Local (fe80::/10)
	IMPORT_C TBool IsSiteLocal() const;		// ///< TRUE, if address is IPv6 Site Local (fec0::/10)
	IMPORT_C TBool IsV4Compat() const;		// ///< TRUE, if address is IPv4-compatible (::x.x.x.x/96). Deprecated.
	IMPORT_C TBool IsV4Mapped() const;		// ///< TRUE, if address is IPv4-mapped (::ffff:x.x.x.x/96)
	IMPORT_C TBool IsEqual(const TIp6Addr &aAddr) const;// ///< TRUE, if addresses are equal
	IMPORT_C TInt Match(const TIp6Addr &aAddr) const;	// ///< Returns number of matching bits (common prefix)
	IMPORT_C TInt Scope() const;
	union
		{
		TUint8  iAddr8[16];
		TUint16 iAddr16[8];
		TUint32 iAddr32[4];
		} u;
	};


/** IPv6 socket address. */
struct SInet6Addr
	{
	TIp6Addr iAddr;		///< 16 bytes of IP6 address (128 bits)
	TUint32 iFlow;		///<  4 bytes of IP6 Flow ID
	TUint32 iScope;		///<  4 bytes of IP6 Scope ID
	};

/** @name IPv6 address scope constants
 * (the standard values, RFC-2373 2.7) */
 //@{
/** Node-local scope address. */
const TInt KIp6AddrScopeNodeLocal = 0x01;     // ///< Node local scope level
/** Link-local scope address. */
const TInt KIp6AddrScopeLinkLocal = 0x02;     // ///< Link local scope level
/** Site-local scope address. */
const TInt KIp6AddrScopeSiteLocal = 0x05;     // ///< Site local scope level
/** Organisation-local scope address. */
const TInt KIp6AddrScopeOrganization = 0x08;  // ///< Organisation local scope level
/** Global scope. */
const TInt KIp6AddrScopeGlobal = 0x0E;	      // ///< Global scope level
/**
 * (non-standard value, used internally)
 *
 * The Scope() function will return this value, when the
 * address is some form of IPv4 mapped, compatible or
 * other mangling of IPv4 address into IPv6 format. It
 * is assumed that all these have the IPv4 address as
 * the last 4 bytes of the address.
 *
 * Note that 6to4 addresses DO NOT BELONG TO THIS GROUP!
 */
//const TInt KIp6AddrScopeMangledV4 = 0x10;	// (deprecate this)
const TInt KIp6AddrScopeNetwork = 0x10;	      // ///< Network scope level (non-standard)
//@}

/** @name IPv6 address constants */
//@{
/** IPv6 address constant: No address (all 0s). */
const TIp6Addr KInet6AddrNone = {{{0}}};
/** IPv6 address constant: Loopback address. */
const TIp6Addr KInet6AddrLoop = {{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}};
/** IPv6 address constant: Link-local address. */
const TIp6Addr KInet6AddrLinkLocal = {{{0xfe, 0x80, }}};
//@}

/**
 * This class specialises the generic socket server address class
 * TSockAddr for the TCP/IP protocol family. It represents an IP
 * address and stores either an IPv4 or an IPv6 address in its buffer
 * after the generic data defined by TSockAddr. The protocol family
 * field provided by the TSockAddr base class can be set to KAfInet,
 * KAfInet6 or KAFUnspec.
 *
 * The address family defines the format of the stored address:
 *
 * @li KAfInet
 *	is for plain 32 bits IPv4 address presented as SInetAddr
 *	structure.
 * @li KAfInet6
 *	is for both IPv4 and IPv6 addresses (IPv4 addresses
 *	are in IPv4 mapped format). The content is presented as
 *	SInet6Addr structure, which includes the scope id
 *	and flow label, in addition to the 128 address bits.
 * @li KAFUnspec
 *	does not contain any addresses and works in most
 *	contexts as unspecified address, This is better than
 *	placing explicit IPv4 "0.0.0.0" or IPv6 "::", which
 *	in certain situations may limit the connections to either
 *	IPv4 or IPv6, but not both.
 *
 * The flow label and scope id fields exist only in KAfInet6
 * format. However, the access methods TInetAddr::FlowLabel
 * TInetAddr::Scope will also work for other address formats
 * by always returning 0.
 *
 * Any method which sets or changes the address bits, will
 * always reset the scope id and flow label to 0 (the
 * TInetAddr::Init is always called internally). These are
 * reasonable defaults, and normal application user does not
 * normally need to worry about flow label or scope id.
 *
 * When address is returned from the stack, it will often
 * be in KAfInet6 format, and may contain non-zero values
 * for flow label and scope id fields. When copying addresses,
 * the full TInetAddr (or at least SInet6Addr) should be
 * copied to preserve these fields.
 */
class TInetAddr : public TSockAddr
	{
public:
	IMPORT_C TInetAddr();
	IMPORT_C TInetAddr(const TSockAddr& anAddr);
	IMPORT_C TInetAddr(TUint aPort);
	IMPORT_C TInetAddr(const TIp6Addr &anAddr, TUint aPort);
	IMPORT_C TInetAddr(TUint32 anAddr, TUint aPort);
	IMPORT_C void SetAddress(TUint32 anAddr);
	IMPORT_C void SetAddress(const TIp6Addr &anAddr);
	IMPORT_C void SetV4CompatAddress(TUint32 anAddr);
	IMPORT_C void SetV4MappedAddress(TUint32 anAddr);
	IMPORT_C void SetFlowLabel(TInt aLabel);
	IMPORT_C TInt FlowLabel() const;
	IMPORT_C const TIp6Addr &Ip6Address() const;
	IMPORT_C void ConvertToV4Compat();
	IMPORT_C void ConvertToV4Mapped();
	IMPORT_C void ConvertToV4();
	IMPORT_C TBool CmpAddr(const TInetAddr& anAddr) const;

	/**
	 * Tests the IP address value with that in another TInetAddr.
	 * 
	 * @param aHost	TInetAddr with which to compare.
	 * @return		ETrue, if IP address value is the same as this; otherwise, EFalse.
	 */
	IMPORT_C TBool Match(const TInetAddr& aHost) const;

	/** Tests if another TInetAddr is in the same subnet. 
	 * 
	 * The function applies the subnet mask passed through aMask to the IP address 
	 * and to the IP address in aNet. If the resulting values are the same, this 
	 * indicates that the addresses are part of the same subnet, and ETrue is returned.
	 * 
	 * @param aNet	TInetAddr with which to compare.
	 * @param aMask	TInetAddr object with the IP address set to the relevant subnet 
	 * 				mask.
	 * @return		ETrue, if both IP address values are the members of the same subnet; 
	 * 				otherwise, EFalse. 
	 */
	IMPORT_C TBool Match(const TInetAddr& aNet, const TInetAddr& aMask) const;
	IMPORT_C TBool Match(const TInetAddr& aNet, TInt aPrefixLen) const;
	IMPORT_C void PrefixMask(TInt aPrefixLen);
	IMPORT_C void Prefix(const TInetAddr& aAddr, TInt aPrefixLen);
	IMPORT_C void Output(TDes &aBuf) const;
	IMPORT_C TInt Input(const TDesC &aBuf);

	/**
	 * Casts a TSockAddr to a TInetAddr reference. 
	 * 
	 * The cast is only safe if the object being referenced is actually aTInetAddr. 
	 *
	 * @param anAddr	TSockAddr to cast
	 * @return			Casted reference to a TInetAddr. 
	 */
	inline static TInetAddr& Cast(const TSockAddr& anAddr);

	/**
	 * Casts a TSockAddr to a TInetAddr reference. 
	 * 
	 * The cast is only safe if the object to which anAddr points to is actually a TInetAddr.
	 *
	 * @param anAddr	TSockAddr to cast
	 * @return			Casted pointer to a TInetAddr. 
	 */
	inline static TInetAddr& Cast(const TSockAddr* anAddr);
	
	/** @name Address tests */
	//@{

	IMPORT_C TBool IsUnicast() const;
	IMPORT_C TBool IsMulticast() const;
	IMPORT_C TBool IsLoopback() const;
	IMPORT_C TBool IsUnspecified() const;
	IMPORT_C TBool IsLinkLocal() const;
	IMPORT_C TBool IsSiteLocal() const;
	IMPORT_C TBool IsV4Compat() const;
	IMPORT_C TBool IsV4Mapped() const;
	IMPORT_C TUint32 Address() const;  
	IMPORT_C void NetMask(const TInetAddr& aAddr);
	IMPORT_C void Net(const TInetAddr& aAddr);
	IMPORT_C void NetBroadcast(const TInetAddr& aAddr);
	IMPORT_C void SubNet(const TInetAddr& aAddr, const TInetAddr& aMask);
	IMPORT_C void SubNetBroadcast(const TInetAddr& aAddr, const TInetAddr& aMask);
        
	/**
	 * Tests if the IP address is Class A (deprecated).
	 *
	 * @return		ETrue, if the IPv4 address value is Class A; otherwise, EFalse.
	 * 
	 * @deprecated	This function works only for IPv4. It assumes the rigid 
	 * 				IPv4 address classes (A, B, C). Applications using this function 
	 * 				may not work properly in the current internet environment.
	 */
	inline TBool IsClassA() const;

	/**
	 * Tests if the IP address is Class B (deprecated).
	 *
	 * @return		ETrue, if the IPv4 address value is Class B; otherwise, EFalse.
	 *
	 * @deprecated	This function works only for IPv4. It assumes the rigid 
	 * 				IPv4 address classes (A, B, C). Applications using this function 
	 *				may not work properly in the current internet environment.
	 */
	inline TBool IsClassB() const;

	/**
	 * Tests if the IP address is Class C.
	 *
	 * @return		ETrue, if the IPv4 address value is Class C; otherwise, EFalse.
	 *
	 * @deprecated	This function works only for IPv4. It assumes the rigid 
	 *				IPv4 address classes (A, B, C). Applications using this function 
	 *				may not work properly in the current internet environment.
	 */
	inline TBool IsClassC() const;

	/**
	 * Tests if the IP address is a limited broadcast address (255.255.255.255) (deprecated).
	 *
	 * @return		ETrue, if the IPv4 address value is a limited broadcast address; otherwise, EFalse
	 *
	 * @deprecated	This function is deprecated and works only for IPv4. It assumes the rigid 
	 *				IPv4 address classes (A, B, C). Applications using this function may not work 
	 *				properly in the current internet environment.
	 */
	inline TBool IsBroadcast() const;

	/**
	 * Tests if the IP address is zero (0.0.0.0 or ::).
	 *
	 * This is the same as IsUnspecified().
	 *
	 * @return	ETrue, if the IP address value is zero; otherwise, EFalse. 
	 */
	inline TBool IsWildAddr() const;

	/**
	 * Tests if the port is zero.
	 *
	 * @return	ETrue if the port is zero; otherwise, EFalse.
	 */
	inline TBool IsWildPort() const;
	//@}

	IMPORT_C void SetScope(TUint32 aScope);
	IMPORT_C TUint32 Scope() const;
	IMPORT_C void Init(TUint aFamily);
	IMPORT_C void OutputWithScope(TDes &aBuf) const;
protected:
	inline SInetAddr *Addr4Ptr() const;	///< returns a pointer to KAfInet content format
	inline SInet6Addr *AddrPtr() const;	///< returns a pointer to KAfInet6 content format
	inline static TInt AddrLen();		///< returns the size of the KAfInet6 content format
private:
	TInt Ipv4Input(const TDesC& aDes);	///< parse string as IPv4 address
	TInt Ipv6Input(const TDesC& aDes);	///< parse string as IPv6 address
	};


/** @name Inline functions */
//@{
inline SInet6Addr* TInetAddr::AddrPtr() const
	{ return (SInet6Addr*)UserPtr(); }

inline TInt TInetAddr::AddrLen()
	{ return sizeof(SInet6Addr); }

inline TInetAddr& TInetAddr::Cast(const TSockAddr& anAddr)
	/** Casts a TSockAddr to a TInetAddr reference. 
	* 
	* The cast is only safe if the object to which anAddr points to is actually 
	* a TInetAddr.
	* 
	* @param anAddr	TSockAddr to cast
	* @return		Casted reference to a TInetAddr. */
        { return *((TInetAddr*)&anAddr); }

inline TInetAddr& TInetAddr::Cast(const TSockAddr* anAddr)
	/** Casts a pointer to a TSockAddr to a TInetAddr reference. 
	* 
	* The cast is only safe if the object to which anAddr points to is actually 
	* a TInetAddr.
	* 
	* @param anAddr	TSockAddr to cast
	* @return		Casted pointer to a TInetAddr. */
        { return *((TInetAddr*)anAddr); }

// Compatibility
inline SInetAddr* TInetAddr::Addr4Ptr() const
	{ return (SInetAddr*)UserPtr(); }

inline TBool TInetAddr::IsBroadcast() const
	/** Tests if the IP address is a limited broadcast address (255.255.255.255) (deprecated).
	* 
	* @return		ETrue, if the IPv4 address value is a limited broadcast address; 
	* 				otherwise, EFalse. 
	* 
	* @deprecated	This function works only for IPv4. It assumes the rigid 
	* 				IPv4 address classes (A, B, C). Applications using this function 
	*				may not work properly in the current internet environment.
	*/
	{ return Address() == KInetAddrBroadcast; }

inline TBool TInetAddr::IsWildPort() const
	/** Tests if the port is zero. 
	* 
	* @return	ETrue, if the port is zero; otherwise, EFalse. */
	{ return Port() == KInetPortNone; }

inline TBool TInetAddr::IsWildAddr() const
	/** Tests if the IP address is zero (0.0.0.0 or ::). 
	* 
	* This is the same as IsUnspecified().
	* 
	* @return	ETrue, if the IP address value is zero; otherwise, EFalse. */
	{ return IsUnspecified(); }

// The following are deprecated and should not be used

inline TBool TInetAddr::IsClassA() const
	/** Tests if the IP address is Class A (deprecated).
	* 
	* @return ETrue if the IPv4 address value is Class A; otherwise, EFalse 
	* 
	* @deprecated	This function works only for IPv4. It assumes the rigid 
	*				IPv4 address classes (A, B, C). Applications using this function 
	*				may not work properly in the current internet environment.
	*/
	// if ip6 address is not possible to convert to ip4 return failure
	{ return (Address() & KInetAddrIdMaskA) == KInetAddrIdValA; }

inline TBool TInetAddr::IsClassB() const
	/** Tests if the IP address is Class B (deprecated). 
	*
	* @return		ETrue, if the IPv4 address value is Class B; otherwise, EFalse.
	* 
	* @deprecated	This function is deprecated and works only for IPv4. It assumes the rigid 
	* 				IPv4 address classes (A, B, C). Applications using this function may not 
	*				work properly in the current internet environment. 
	*/
	// if ip6 address is not possible to convert to ip4 return failure
	{ return (Address() & KInetAddrIdMaskB) == KInetAddrIdValB; }

inline TBool TInetAddr::IsClassC() const
	/** Tests if the IP address is Class C (deprecated).  
	*
	* @return		ETrue if the IPv4 address value is Class C; otherwise, EFalse.
	* 
	* @deprecated	This function is deprecated and works only for IPv4. It assumes the rigid 
	*				IPv4 address classes (A, B, C). Applications using this function may not work 
	*				properly in the current internet environment.
	*/
	// if ip6 address is not possible to convert to ip4 return failure
	{ return (Address() & KInetAddrIdMaskC) == KInetAddrIdValC; }
//@}

/**  @name Send/Recv flags (datagram sockets only) */
//@{
const TUint KIpDontFragment		= 0x010000;	  ///< Don't fragment the packet.
const TUint KIpHeaderIncluded	= 0x020000;	  ///< The packet includes IP or IPv6 header.
/** Don't route the packet.
@deprecated  Not supported in Symbian OS v7.0 and v7.0s */
const TUint KIpDontRoute		= 0x040000;
//@}


class TSoInetLastErr
/** Error information for TCP/IP protocols. 
* 
* An object of this class is returned packaged as a TPckgBuf<TSoInetLastErr> 
* in the anOption argument of RSocket::GetOpt(), when this function is called 
* with anOptionLevel set to KSoInetLastError. The data members of this object 
* are updated whenever a packet carrying an ICMP message is received. */
// Structure returned by KSoInetLastError/KIoctlInetLastError
	{
public:
	/** The error code returned by the last ESOCK API function called. */
	TInt iStatus;			// ///< ESock error code
	/** The value of the Type field of the last ICMP message. */
	TInt iErrType;			// ///< ICMP type
	/** The value of the Code field of the last ICMP message. */
	TInt iErrCode;			// ///< ICMP code
	/** A TInetAddr with the IP address and port set to the source address and port 
	* of the failed datagram. */
	TInetAddr iSrcAddr;		// ///< Src of failed datagram
	/** A TInetAddr with the IP address and port set to the destination address and 
	* port of the failed datagram. */
	TInetAddr iDstAddr;		// ///< Dst of failed datagram
	/** A TInetAddr with the IP address set to the address of the host that generated 
	* the error. */
	TInetAddr iErrAddr;		// ///< Addr of host that generated the error
	};

class TIp6Mreq
/** Used by IPv6 multicast join/leave group socket options */
	{
public:
	
	TIp6Addr iAddr;		///< Contains IPv6 multicast address.
	TUint iInterface;	///< Interface index.
	};

// Level == KSolInetIfCtrl
// Enumerating & Configuring Interfaces TPckgBuf<TSoInetInterfaceInfo>
// With a level of KSolInetIfCtrl
 
/** Begin enumeration of network interfaces. 
* 
* This option should be set before enumerating interfaces with KSoInetNextInterface. 
* 
* This option is for use with SetOpt() only. */
const TInt KSoInetEnumInterfaces = 0x211;	// ///< Set - Enumerate network interfaces

/** Return details of the next interface in an enumeration started by setting the 
* option KSoInetEnumInterfaces.
* 
* This option is for use with GetOpt() only.
* 
* anOption should be a TPckgBuf<TSoInetInterfaceInfo>. */
const TInt KSoInetNextInterface = 0x212;	// ///< Get - Get next interface

/** Return details of the specified interface. 
* 
* This option is for use with GetOpt() only.
* 
* For IPv4/IPv6 dual stack, this anOption should be a TPckgBuf<TSoInet6InterfaceInfo>; 
* for IPv4, use a TPckgBuf<TSoInetInterfaceInfo>
* 
* The interface can be specified by setting the iAddress, iTag, iName, or iHwAddr 
* of the passed object. The complete details are passed back in the same object. */
const TInt KSoInetConfigInterface = 0x213;	// ///< Set - Configure network interface

/** Describes the state of an interface. 
* 
* It is used as a data member of TSoInetInterfaceInfo. */
enum TIfStatus
	{
	/** The interface has been initiated, but is not yet available. */
	EIfPending,				// ///< Nif is being set up
	/** The interface is up and available. */
	EIfUp,					// ///< Nif is ready
	/** The interface is up, but flowed off. */
	EIfBusy,				// ///< Nif has flowed off
	/** The interface is down. */
	EIfDown,				// ///< Nif is down
	};

class TSoInetInterfaceInfo
// Used when listing interfaces with KSoInetNextInterface socket option.
/** Information describing an instance of a network interface provided by Nifman 
* (for example, a PPP interface).
* 
* An object of this class is returned packaged as a TPckgBuf<TSoInetInterfaceInfo> 
* in the anOption argument of RSocket::GetOpt(), when that function is called 
* with anOptionLevel set to KSolInetIfCtrl and anOptionName set to KSoInetNextInterface 
* or KSoInetConfigInterface. */
	{
public:
	/** Tag that identifies the interface in tcpip.ini. */
	TName iTag;				// ///< Interface tag
	/** Interface protocol name, e.g., ppp. */
	TName iName;			// ///< Interface name
	/** Interface state. */
	TIfStatus iState;		// ///< State
	/** Maximum transmission unit. */
	TInt iMtu;				// ///< max transmition size
	/** An approximation of the interface speed in Kbps. */
	TInt iSpeedMetric;		// ///< Metric - bigger is better
	/** Feature flags. 
	* 
	* Possible values are defined in in_iface.h. */
	TUint iFeatures;		// ///< Feature flags
	TSockAddr iHwAddr;		///< Hardware address.
	TInetAddr iAddress;		///< Interface IP Address.
	TInetAddr iNetMask;		///< IP netmask (IPv4 only).
	TInetAddr iBrdAddr;		///< IP broadcast address (IPv4 only).
	TInetAddr iDefGate;		///< IP default gateway or peer address (IPv4 only).
	TInetAddr iNameSer1;	///< IP Primary name server.
	TInetAddr iNameSer2;	///< IP Secondary name server.
	};


// New IPv6 functionality, allow ConfigInterface in SetOption, and add
// two new options.
//     *NOTE*
// The difference between Config and Change is only that the Change will
// not create new interface entry, if it does not exist. Config never
// fails on "interface not found", it always finds some (or creates).
 
/** Deletes an interface.
* 
* anOption should be a TPckgBuf<TSoInet6InterfaceInfo>. */
const TUint KSoInetDeleteInterface = 0x214;	  // ///< Set - Delete interface

/** Sets interface details.
* 
* anOption should be a TPckgBuf<TSoInet6InterfaceInfo>.
* 
* Note that this, unlike KSoInetConfigInterface, never creates a new interface 
* entry, if one does not already exist. KSoInetConfigInterface never fails with 
* interface not found, as it always finds or creates one. */
const TUint KSoInetChangeInterface = 0x215;	  // ///< Set - Modify interface

/** Reset interface to initial state */
const TUint KSoInetResetInterface = 0x216;	// ///< Set - Reset interface to initial state

/** Restart interface, and reconfigure */
const TUint KSoInetStartInterface = 0x217;	// ///< Set - Restart interface, reconfigure

class TSoInet6InterfaceInfo : public TSoInetInterfaceInfo
// Extension for TSoInetInterfaceInfo. Available in Symbian OS v7.0 and later.
/** Extended interface information class for IPv6. */
	{
public:
	/** Delete flag.
	* 
	* 0 = add, 1 = delete */
	TUint iDelete:1;

	/** Primary or alias interface flag.
	* 
	* 0 = primary, 1 = alias. */
	TUint iAlias:1;
	
	/** Prefix handling flag.
	* 
	* 0 = ignore prefix part, 1 = process prefix. */
	TUint iDoPrefix:1;
	
	/** ID part handling flag.
	* 
	* 0 = ignore ID, 1 = process ID. */
	TUint iDoId:1;
	
	/** Interface state handling flag.
	* 
	* 0 = ignore TSoInetInterfaceInfo::iState, 1 = set interface state from TSoInetInterfaceInfo::iState. */
	TUint iDoState:1;
	/** Unused. 
	* 
	* 1 = configure anycast (DoPrefix/DoId ignored!) */
	TUint iDoAnycast:1;
	
	/** Reserved for future use */
	TUint iDoProxy:1;
	};

/**
 * IPv6/IPv4 stack specific
 * KSolInetIfQuery
 */
typedef TUint32 TInetScopeIds[16];

class TSoInetIfQuery
/** Structure holding information for querying a specified interface.
* 
* This structure is used as a RSocket::GetOpt() parameter for the option level 
* KSolInetIfQuery. 
* 
* The option name, one of KSoInetIfQueryByDstAddr, KSoInetIfQueryBySrcAddr, 
* KSoInetIfQueryByIndex, and KSoInetIfQueryByName, determines the input field 
* in the TSoInetIfQuery that is used as a key for locating the interface.
* 
* Returns KErrNotFound, if interface is not found.
* 
* Returns KErrNone, if interface is located, and fills
* fields from the interface with following logic:
* 
* @li iDstAddr:	unchanged
* @li iSrcAddr:	result of the Select Source Address algorithm for the interface 
* 				using the iDstAddr as input. If there is no valid source address, 
* 				the value will be KAFUnspec.
* @li iIndex    the interface index of the interface
* @li iName:	the name of the interface
* @li iIsUp 	is set 1, if the interface is up; otherwise, 0.
* 
* For example, if querying for a specified destination address results in iIsUp 
* == 1, then there is an interface and route for that destination. If iIsUp 
* == 0, this means that trying to connect to the address is likely to activate 
* a network dial=up/interface link startup phase. 
*/
	{
public:
	TInetAddr iDstAddr;		///< Destination address
	TInetAddr iSrcAddr;		///< Source address
	TUint32 iIndex;			///< Interface Index (same as iZone[0] on output)
	TName iName;			///< Interface Name
	/** Flag that is set to 1 if the interface is up. */
	TUint iIsUp:1;			// ///< 1 = if interface has CNifIfBase * attached
	TInetScopeIds iZone;	///< Scope Id Vector (iScope[0] = Interface Index, iScope[15] = Network ID)
	};

/** Get information for the interface specified by the destination address (iDstAddr) 
* field of the passed packaged TSoInetIfQuery.
* 
* This allows the caller to find out what interface would be used (without invoking 
* a dial-up process) for the specified destination. A path for this destination 
* is open, if GetOpt() returns KErrNone, iSrcAddr is not KAFUnspec, and iIsUp 
* == 1. */
const TUint KSoInetIfQueryByDstAddr	= 0x1;	// ///< Get - Query interface by destination address

/** Get information for the interface specified by the source address (iSrcAddr) 
* field of the passed packaged TSoInetIfQuery.
* 
* If there are multiple interfaces with the same source address, then the first 
* matching interface is returned. 
* 
* Note that the information return phase will overwrite the iSrcAddr based on whatever 
* happens to be in iDstAddr. It is not necessary to initialize iDstAddr, if 
* application is not interested in resulting iSrcAddr. */
const TUint KSoInetIfQueryBySrcAddr	= 0x2;	// ///< Get - Query interface by source address

/** Get information for the interface specified by the Interface Index (iIndex) 
* field of the passed packaged TSoInetIfQuery. */
const TUint KSoInetIfQueryByIndex	= 0x3;	// ///< Get - Query interface by index

/** Get information for the interface specified by the Interface Name (iName) field 
* of the passed packaged TSoInetIfQuery. */
const TUint KSoInetIfQueryByName	= 0x4;	// ///< Get - Query interface by name 

/** Setting this option causes the UDP send operation to block when dynamic interface 
* setup is in progress, or when local flow control within the stack would otherwise 
* cause the packet to be dropped. */
const TUint KSoInetIfQuerySetScope	= 0x10;	// ///< Set - Load scope vector from iScope

// Enumerating & Configuring Routes TPckgBuf<TSoInetRouteInfo>
// With a level of KSolInetRtCtrl
/** Begin enumeration of routes. 
*
* This option can only be used with RSocket::SetOpt().
* 
* This option should be set before enumerating routes with KSoInetNextRoute. */
const TInt KSoInetEnumRoutes  = 0x221;		// ///< Set - Enumerate routes

/** Return the next route in an enumeration started by setting the option KSoInetEnumRoutes.
* 
* anOption should be a TPckgBuf< TSoInetRouteInfo >.
* 
* This option can only be used with RSocket::GetOpt(). */
const TInt KSoInetNextRoute	  = 0x222;		// ///< Get - Get next route

/** Adds the specified route to the routing table.
* 
* anOption should be a TPckgBuf<TSoInetRouteInfo>. The interface concerned must 
* exist as a virtual or real interface.
* 
* This option can only be used with RSocket::SetOpt(). */
const TInt KSoInetAddRoute	  = 0x223;		// ///< Set - Add route

/** Deletes the specified route from the routing table.
* 
* anOption should be a TPckgBuf<TSoInetRouteInfo>. The interface concerned must 
* exist as a virtual or real interface.
* 
* This option can only be used with RSocket::SetOpt(). */
const TInt KSoInetDeleteRoute = 0x224;		// ///< Set - Delete route

/** Modifies the specified route in the routing table. 
* 
* The destination and netmask settings must be the same in the new route as 
* in the old.
* 
* anOption should be a TPckgBuf< TSoInetRouteInfo >.
* 
* This option can only be used with RSocket::SetOpt(). */
const TInt KSoInetChangeRoute = 0x225;		// ///< Set - Modify route

/** Identifies the state of a route held in an entry in the IP routing table. 
* 
* It is used as a data member of TSoInetRouteInfo. The state of the route depends 
* on the state of the network interface used to access the routeâ€™s destination 
* (compare TIfStatus). */
enum TRouteState
	{
	/** Unused. */
	ERtNone,
	/** The interface for the route has been initiated, but no information is available. 
	 * 
	 * i.e. ARP or Neighbor Cache Entry is pending. */
	ERtPending,	
	/** The interface for the route is up, but flowed off. 
	 * 
	 * Currently not supported. */
	ERtBusy,
	/** The interface for the route is up and ready. */
	ERtReady,
	/** The interface for the route is down. 
	 * 
	 * Currently not supported. */
	ERtDown	
	};

/** Identifies the type of creator of an entry in the IP routing table. 
* 
* It is used as a data member of TSoInetRouteInfo. */
enum TRouteType
	{
	/** Created when the interface was started. 
	 *
	 * Normal route entry. */
	ERtNormal,
	/** Created by user by a call to RSocket::SetOpt().
	 * 
	 * Currently not supported. */
	ERtUser,
	/** Added by ICMP redirect (currently unsupported).
	 *
	 * ARP or neighbor cache entry. */
	ERtIcmpAdd,
	/** Replaced by an ICMP redirect.
	 * 
	 * Currently not supported. */
	ERtIcmpDel	
	};

class TSoInetRouteInfo
/** Encapsulates information describing an entry in the IP routing table. 
* 
* TSoInetRouteInfo objects are used to specify routing table entries in calls 
* to RSocket::GetOpt() and RSocket::SetOpt(), when these functions are called 
* with anOptionLevel set to KSolInetRtCtrl.
*
* This API is supported for backward compatibility with Symbian OS v6.x. 
* IPv6 addresses are returned as IPv4-mapped IPv6 addresses qualified with 
* appropriate scope ID. */
	{
public:
	TRouteType iType;		///< Type of route (normal/icmp generated etc)
	TRouteState iState;		///< State of route
	TInt iMetric;			///< Smaller is better (less hops and/or faster link)
	TInetAddr iIfAddr;		///< IP address on interface used for this route
	TInetAddr iGateway;		///< IP address of gateway or link-layer address for ARP and ND entries
	TInetAddr iDstAddr;		///< Destination network or host
	TInetAddr iNetMask;		///< Destination mask of network (or host if KInetMaskHost)
	};

class TSoInetCachedRouteInfo : public TSoInetRouteInfo
/** Information describing a cached routing entry.
* 
* A TSoInetCachedRouteInfo object is returned by a call to RSocket::GetOpt(), 
* when that function is called with anOptionLevel set to KSolInetRtCtrl and 
* anOptionName set to KSoInetCachedRouteByDest.
*
* @deprecated This API is no longer supported.
*/
// Access to route cache TPckgBuf<TSoInetCachedRouteInfo>, set iDstAddr for required address
// With a level of KSolInetRtCtrl. This API is no longer suported.
	{
public:
	TInt iPathMtu;			///< Set if used by DF datagram (incl TCP SYN), else 0
	TUint iPathRtt;			///< Set if used by TCP, else 0
	};

/** Find a cached route to a specified destination.
* 
* This is only supported in the IPv4 stack, not the IPv4/v6 dual stack.
* 
* The caller should pass a packaged TSoInetCachedRouteInfo with its iDstAddr 
* member set to the required address.
* 
* anOption should be a TPckgBuf< TSoInetCachedRouteInfo >.
* 
* This option can only be used with RSocket::GetOpt(). 
*
* @deprecated This constant is no longer supported. */
const TInt KSoInetCachedRouteByDest = 0x225;


// Flags returned from DNS records
/** Provides flag bitmasks that are used to describe properties of results of DNS 
* queries via RHostResolver. */
enum TNameRecordFlags
	{
	EDnsAlias=0x00000001,		///< Name is an Alias
	EDnsAuthoritive=0x00000002, ///< Answer is authoritive 
	EDnsHostsFile=0x00000004,   ///< Answer is from hosts file
	EDnsServer=0x00000008,      ///< Answer is from a DNS server
	EDnsHostName=0x00000010,    ///< Answer is host name for this host
	EDnsCache=0x00000020		///< Answer is from the resolver cache
	};

/** Enable DNS cache flag.
* 
* This is only supported in the IPv4 stack, not the IPv4/v6 dual stack.
* 
* anOption should be a TInt.
* 
* Values are: 0 = Disable, 1 = Enable.
* 
* The default is enabled. 
*
* @deprecated This constant is no longer supported. */
const TUint KSoDnsCacheEnable = 0x600;

/** Flush DNS cache.
* 
* This is only supported in the IPv4 stack, not the IPv4/v6 dual stack.
* 
* This option is for use with SetOpt() only. 
*
* @deprecated This constant is no longer supported. */
const TUint KSoDnsCacheFlush = 0x601;

// TCP specific options and ioctls with a level of KSolInetTcp Ioclt

/** Complete the ioctl request when the data has been sent. */
const TUint KIoctlTcpNotifyDataSent = 0x300;  // ///< Get/Set

// Options
/** The maximum number of bytes that can be queued for sending. 
* 
* If this option is set when the connection state is not closed, then KErrLocked 
* is returned.
* 
* anOption should be a TInt.
* 
* The default value is 8192. */
const TUint KSoTcpSendWinSize = 0x301; // ///< Get/Set before connect

/** The maximum number of bytes that can be buffered for receiving. 
* 
* If this option is set when the connection state is not closed, then KErrLocked 
* is returned.
* 
* anOption should be a TInt. 
* 
* The default value is 8192. */
const TUint KSoTcpRecvWinSize = 0x302; // ///< Get/Set before connect

/** The maximum TCP segment size (bytes). 
* 
* If this option is set when the connection state is not closed, then KErrLocked 
* is returned.
* 
* The default value is 1460.
* 
* anOption should be a TInt. */
const TUint KSoTcpMaxSegSize = 0x303; // ///< Get/Set before connect

/** Send data at once if there is an established connection, without waiting for 
* the maximum segment size to be reached. 
* 
* The default is disabled.
* 
* anOption should be a TInt. 
* 
* Values are: 0 = Disable, 1 = Enable. */
const TUint KSoTcpNoDelay = 0x304; // ///< Get/Set

/** On the time-out expiring without an acknowledgement being received, send a 
* packet designed to force a response if the peer is up and reachable.
* 
* This is only supported in the IPv4 stack, not the IPv4/v6 dual stack.
* 
* The default is disabled.
* 
* anOption should be a TInt. 
* 
* Values are: 0 = Disable, 1 = Enable. */
const TUint KSoTcpKeepAlive = 0x305; // ///< Get/Set

/** If address reuse is allowed, and a connection already exists between the requested 
* local and remote addresses, wait for the address to become available.
* 
* This is only supported in the IPv4 stack, not the IPv4/v6 dual stack.
* 
* The default is disabled.
* 
* anOption should be a TInt. 
* 
* Values are: 0 = Disable, 1 = Enable. 
*
* @deprecated This constant is no longer supported. */
const TUint KSoTcpAsync2MslWait = 0x306;

/** The number of bytes currently queued for sending.
* 
* anOption should be a TInt.
* 
* This option can only be used with RSocket::GetOpt(), not RSocket::SetOpt(). */
const TUint KSoTcpSendBytesPending = 0x307; // ///<Get

/** The number of bytes currently available for reading (the same value as is obtained 
* using KSOReadBytesPending).
* 
* anOption should be a TInt.
* 
* This option can only be used with RSocket::GetOpt(), not RSocket::SetOpt(). */
const TUint KSoTcpReadBytesPending = 0x308; // ///<Get

/** The socket has been set to listen (through RSocket::Listen()).
* 
* anOption should be a TInt.
* 
* Values are: 0. Not listening, 1. Listening
* 
* This option can only be used with RSocket::GetOpt(), not RSocket::SetOpt(). */
const TUint KSoTcpListening = 0x309; // ///<Get

/** The number of current TCP sockets.
* 
* anOption should be a TInt.
* 
* This option can only be used with RSocket::GetOpt(), not RSocket::SetOpt(). */
const TUint KSoTcpNumSockets = 0x310; // ///<Get

/** Read out-of-band urgent data.
* 
* KErrNotFound is returned if there is no data waiting and no urgent data pointer 
* has been received.
* 
* KErrWouldBlock is returned if and urgent is available but data needs to be 
* read from the current stream to match the urgent data mark.
* 
* anOption should be a TInt.
* 
* This option can only be used with RSocket::GetOpt(), not RSocket::SetOpt(). */
const TUint KSoTcpReadUrgentData = 0x311; // ///<Get

/** Peeks for urgent data. The behaviour is the same as KSoTcpReadUrgentData, but 
* the urgent data is not removed.
* 
* anOption should be a TInt.
* 
* This option can only be used with RSocket::GetOpt(), not RSocket::SetOpt(). */
const TUint KSoTcpPeekUrgentData = 0x312; // ///<Get

/** True if the data stream has been read up to the point where urgent data is 
* available, otherwise false.
* 
* anOption should be a TInt.
* 
* This option can only be used with RSocket::GetOpt(), not RSocket::SetOpt(). */
const TUint KSoTcpRcvAtMark = 0x313; // ///<Get

/** The next send operation will mark the last byte sent as urgent data.
* 
* The default is disabled.
* 
* anOption should be a TInt.
* 
* Values are: 0 = Disable, 1 = Enable. */
const TUint KSoTcpNextSendUrgentData = 0x314; // ///<Get/Set

/** Receive out-of-band data in the normal data stream.
* 
* The default is disabled.
* 
* anOption should be a TInt.
* 
* Values are: 0 = Disable, 1 = Enable. */
const TUint KSoTcpOobInline = 0x315; // ///<Set

/** @deprecated This constant is no longer supported. */
const TUint KSOTcpDebugMode = 0x11110000;


// Generic with a level of KSolInetIp 
/** Data to place in IP Options field of sent datagrams. 
* 
* Not supported in the IPv4/IPv6 dual stack. The option is not applicable to 
* IPv6.
* 
* anOption should be a TBuf8< TInt >.
* 
* The maximum length is 40 bytes. */
const TUint KSoIpOptions = 0x401; // ///< Set/Get

/** Include IP header in data returned to client.
* 
* IPv4 packets are returned as is with all headers in network byte order (until 
* v7.0, this returned IPv4 headers in host order).
* 
* The default is disabled.
* 
* anOption should be a TInt.
* 
* Values are: 0 = Disable, 1 = Enable. */
const TUint KSoRawMode = 0x402; // ///< Set/Get

/** Assume that the IP header is included in all data written by the client. KSoRawMode 
* must be set before this is allowed.
* 
* anOption should be a TInt. Values are: 0. Disable; 1. Enable
* 
* The default is disabled. */
const TUint KSoHeaderIncluded = 0x403; // ///< Set/Get

/** Type of Service field of outgoing datagrams.
* 
* For IPv6, there is no Type of Service field, so this option sets the Traffic Class.
* 
* anOption should be a TInt.
* 
* Values are 0-63.
* 
* The default value is 0. */
const TUint KSoIpTOS = 0x404; // ///< Set/Get

/** Time to Live field of outgoing datagrams.
* 
* There is no TTL in IPv6, so the value sets the HopLimit: see also KSoIp6UnicastHops.
* 
* anOption should be a TInt.
* 
* Values are 1-255.
* 
* The default value is 66 (configurable through tcpip.ini). */
const TUint KSoIpTTL = 0x405; // ///< Set/Get

/** Allow a socket to be bound to an local address that is already in use.
* 
* anOption should be a TInt.
* 
* Values are: 0 = Disable, 1 = Enable.
* 
* The default is disabled. */
const TUint KSoReuseAddr = 0x406; // ///<Set/Get

/** Do not return an error if there are no available routes when a connect call 
* is made.
* 
* anOption should be a TInt.
* 
* Values are: 0 = Disable, 1 = Enable.
* 
* The default is disabled. */
const TUint KSoNoInterfaceError = 0x407; // ///<Set/Get

/** Modify number of users of the socket.
* 
* Background internet services that have sockets open count as active interface 
* user and prevents the interface manager (NifMan) idle timer from expiring. 
* By this socket option, such a process can make selected sockets invisible 
* to NifMan, hence allowing interface shutdown.
* 
* By setting the value to 0, the socket is not counted as active user. The value 
* 1 makes it visible again.
* 
* The option has no effect if the visibility state already matches the parameter.
* 
* By default, all sockets are initially visible. */
const TUint KSoUserSocket = 0x408; // ///<Set/Get

/** This is only supported in the IPv4 stack, not the IPv4/v6 dual stack. */
const TUint KSoInterfaceIndex = 0x409; // ///< Set/Get (flow option)

/** Controls whether the interface flow counter is affected by this flow. 
* 
* This counter is used in determining when the interface can be brought down.
* 
* anOption should be a TInt. Values are: 0=Don't count, 1= count flow against 
* interface flow count. */
const TUint KSoKeepInterfaceUp = 0x40a; // ///< Set/Get (flow option)
const TUint KSoNoSourceAddressSelect = 0x40b; ///<Set

/** Retrieve last error information.
* 
* This option is for use with GetOpt() only.
* 
* anOption should be a TPckgBuf<TSoInetLastErr>. */
const TUint KSoInetLastError = 0x200; // ///< Get Last ICMP error TPckgBuf<TSoInetLastErr>

/** An Ioctl corresponding to the socket option KSoInetLastError. */
const TUint KIoctlInetLastError = 0x200; // ///< Exactly the same as the GetOpt

// Generic with a level of KSolInetIp.
// Base stack supports link-local multicast only.
// IPv4 multicast groups can be joined by specifying their address
/**
 *	@name New IPv6 specific socket options
 *
 *	(How to avoid overlap when assigning these?)
 *
 * Level == KSolInetIp
 *
 *		*NOTE*
 *			KSoIp6UnicastHops can be used to detect dual IPv4/IPv6 stack from
 *			from the old TCPIP only-IPv4 stack. This option is only implemented
 *			in the dual stack.
 */
 //@{

/** IPv6 hop limit for outgoing datagrams: same as KSoIpTTL.
* 
* For IPv4, this sets the TTL: see KSoIpTTL.
* 
* anOption should be a TInt. */
const TUint KSoIp6UnicastHops = 0x465; // ///<¨Set/Get hop limit for unicast (equivalent to KSoIpTTL)

/** Interface for outgoing multicast packets
* 
* Unused. */
const TUint KSoIp6MulticastIf = 0x46a; // ///< Set/Get Interface for outgoing multicast packets

/** IPv6 hop limit for multicast packets.
* 
* For IPv4, this sets the TTL: see KSoIpTTL.
* 
* anOption should be a TInt.
* 
* The default is 1. */
const TUint KSoIp6MulticastHops	= 0x46b; // ///< Set/Get hop limit for multicast (default = 1)

/** Enable/disable loopback of the multicast packets.
* 
* anOption should be a TInt.
* 
* Values are 1=enable; 0=disable. The default is 1. */
const TUint KSoIp6MulticastLoop	= 0x46c; // ///< Set/Get loopback of the multicast packets (default = 1)

/** For future use. 
*
* Uses TIp6Mreq structure. */
const TUint KSoIp6JoinGroup	= 0x46d; // ///< Set - Join multicast group (paramerer is TIp6Mreq)

/** For future use.
*
* Uses TIp6Mreq structure. */
const TUint KSoIp6LeaveGroup = 0x46e; // ///< Set - Leave multicast group (parameter TIp6Mreq)
//@}

//  UDP specific with a level of KSolInetUdp
/** Inform client of error if ICMP error packets received.
* 
* The default is enabled.
* 
* anOption should be a TInt.
* 
* Values are: 0 = Disable, 1 = Enable. */
const TUint KSoUdpReceiveICMPError = 0x500; // ///<Set/Get

/**
 Set the UDP receive buffer size for a socket in bytes. Overrides global ini parameter
 <tt>udp_recv_buf</tt>. At least one datagram always fits to the buffer, no matter how
 small it is.
 
 Default receive buffer size is 8192 bytes, or the value given in <tt>udp_recv_buf</tt>.
 
 @internalAll
 @prototype
 */
const TUint KSoUdpRecvBuf = 0x501;

/** Setting this option causes the UDP send operation to block when dynamic interface 
* setup is in progress, or when local flow control within the stack would otherwise 
* cause the packet to be dropped. */
const TUint KSoUdpSynchronousSend = 0x560; // ///<Set/Get block send on flow control

/** Internal flow option called when the flow is about to be closed */
const TUint KSoFlowClosing = 0x600 | KSocketInternalOptionBit;

/**  @name Extended error codes */
//@{
const TInt KErrNetUnreach = -190;		///< Network could not be reached.
const TInt KErrHostUnreach = -191;		///< Host could not be reached.
const TInt KErrNoProtocolOpt = -192;	///< Protocol could not be reached.
const TInt KErrUrgentData = -193;		///< Urgent data error.
//@}

// Socket options for secure sockets

/** Option level for secure sockets. 
*
* @deprecated */
const TUint KSolInetSSL			= 0x205;	  // ///< SSL setopts/ioctls

/** @name Security specific constants */
//@{

// Socket options at level KSolInetSSL 
/** Sets a secure socket connection using the current secure socket options.
*
* @deprecated */
const TUint KSoSecureSocket = 0x400;          // ///< set/clear secure socket

/** Sets or gets a timeout value after which the SSL DLL is unloaded.
*
* @deprecated */
const TUint KSoSSLUnloadTimeout = 0x401;      // ///< set/get SSL dll unload timeout

/** Sets or gets the current cipher suite.
* 
* A cipher suite is supplied in a descriptor in a two byte format as defined 
* by the TLS/SSL protocols.
*
* @deprecated Refer to ssl.h  */
const TUint KSoCurrentCipherSuite = 0x402;    // ///< set/get current cipher suite

/** Get the current server certificate.
* 
* The certificate is encapsulated in a packaged TCertInfo.
*
* @deprecated Refer to ssl.h */
const TUint KSoSSLServerCert = 0x403;	      // ///< get current server cert

/** Sets or gets the current dialog mode: whether a dialog is presented to the 
* user to accept the service certificate.
* 
* Options are KSSLDialogUnattendedMode and KSSLDialogAttendedMode.
*
* @deprecated Refer to ssl.h */
const TUint KSoDialogMode = 0x404;            // ///< set/get current dialog mode

/** Sets or gets the supported cipher suites.
* 
* Cipher suites are supplied in a descriptor, with each cipher specified in 
* a two-byte format as defined by the TLS/SSL protocols.
*
* @deprecated Refer to ssl.h */
const TUint KSoAvailableCipherSuites = 0x405; // ///< set/get supported cipher suites

// For KSoTcpSecureSocket
/** Disconnect SSL session
* 
* @deprecated Unused. */
const TUint KSSLClearSecureStatus = 0x00;

/** Complete connect on SSL connect
* 
* @deprecated Unused. */
const TUint KSSLSetSecureStatus = 0x01;	
//@}

// For KSoDialogMode
/** A KSoDialogMode option: do not present a dialog.
* 
* @deprecated  Refer to ssl.h */
const TUint KSSLDialogUnattendedMode = 0x00; // ///< dialogs

/** A KSoDialogMode option: present a dialog. 
*
* @deprecated  Refer to ssl.h */
const TUint KSSLDialogAttendedMode = 0x01;   // ///< no dialogs

#endif
