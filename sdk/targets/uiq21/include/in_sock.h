/** @file in_sock.h
 * IPv6/IPv4 socket library public header 
 *
 */

#ifndef __IN_SOCK_H__
#define __IN_SOCK_H__

#ifndef __ES_SOCK_H__
#include <es_sock.h>
#endif

#ifdef _MKLOG
#	include "log.h"
#endif

/**  Address family ID */
const TUint KAfInet				= 0x0800;

/**  Unknown Protocol ID */
const TUint KProtocolUnknown = 0xdead; // get some better value -tom

/**  IP Protocol IDs */
const TUint KProtocolInetIcmp	= 1;
const TUint KProtocolInetTcp	= 6;
const TUint KProtocolInetUdp	= 17;
const TUint KProtocolInetIp		= 0x100;	///< Pseudo protocol

/**  Socket option/ioctl levels */
const TUint KSolInetIcmp		= 0x101;
const TUint KSolInetTcp			= 0x106;
const TUint KSolInetUdp			= 0x111;
const TUint KSolInetIp			= 0x100;
const TUint KSolInetIfCtrl		= 0x201;
const TUint KSolInetRtCtrl		= 0x202;
const TUint KSolInetDnsCtrl		= 0x204;

/**  Security specific */
const TUint KSolInetSSL			= 0x205;  ///< SSL setopts/ioctls

/**  IPv6/IPv4 stack specific */
const TUint KSolInetIfQuery		= 0x206;  ///< Interface information

/**  Maximum IPv4 address */
const TInt KInetAddrMaxBits         = 32;

/**  Port constants */
const TUint KInetPortAny			= 0x0000;
const TUint KInetPortNone			= 0x0000;
const TUint KInetMinAutoPort		= 1024;
const TUint KInetMaxAutoPort		= 5000;

/**  Address constants and utilities */
#define INET_ADDR(a,b,c,d) (TUint32)(((a)<<24)|((b)<<16)|((c)<<8)|(d))

const TUint32 KInetAddrAny				= INET_ADDR(0,0,0,0);
const TUint32 KInetAddrNone				= INET_ADDR(0,0,0,0);
const TUint32 KInetAddrAll				= INET_ADDR(255,255,255,255);
const TUint32 KInetAddrBroadcast		= INET_ADDR(255,255,255,255);
const TUint32 KInetAddrLoop				= INET_ADDR(127,0,0,1);

const TUint32 KInetAddrGroupUnspec		= INET_ADDR(224,0,0,0);
const TUint32 KInetAddrGroupAllHosts	= INET_ADDR(224,0,0,1);

const TUint32 KInetAddrMaskAll			= INET_ADDR(0,0,0,0);
const TUint32 KInetAddrMaskHost			= INET_ADDR(255,255,255,255);

const TUint32 KInetAddrNetMaskA			= INET_ADDR(255,0,0,0);
const TUint32 KInetAddrHostMaskA		= ~KInetAddrNetMaskA;
const TInt KInetAddrShiftA				= 24;
const TUint32 KInetAddrNetMaskB 		= INET_ADDR(255,255,0,0);
const TUint32 KInetAddrHostMaskB		= ~KInetAddrNetMaskB;
const TInt KInetAddrShiftB				= 16;
const TUint32 KInetAddrNetMaskC 		= INET_ADDR(255,255,255,0);
const TUint32 KInetAddrHostMaskC		= ~KInetAddrNetMaskC;
const TInt KInetAddrShiftC				= 8;

const TUint32 KInetAddrIdMaskA			= 0x80000000;
const TUint32 KInetAddrIdValA			= 0x00000000;
const TUint32 KInetAddrIdMaskB			= 0xc0000000;
const TUint32 KInetAddrIdValB			= 0x80000000;
const TUint32 KInetAddrIdMaskC			= 0xe0000000;
const TUint32 KInetAddrIdValC			= 0xc0000000;
const TUint32 KInetAddrIdMaskD			= 0xf0000000;
const TUint32 KInetAddrIdValD			= 0xe0000000;
const TUint32 KInetAddrIdMaskE			= 0xf8000000;
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

struct SInetAddr
	{ TUint32 iAddr; };


////////////////////////////////////////////////////////////////
//
// DEBUG: Recognize semicolon as separator in IPv6 addresses
//
#define IPV6_ALLOW_SEMICOLON
////////////////////////////////////////////////////////////////

/**  Address family ID */
const TUint KAfInet6				= 0x0806;

/**
 *	Inet6 specific protocol Ids
 *	(IPv6 uses the same protocol id space as IPv4, one only needs to
 *	define symbols for protocol ids that are needed in addition to
 *	those of IPv4).
 */
const TUint KProtocolInet6Ipip		= 41;		///< IPv6 tunnels and other wrappings
const TUint KProtocolInet6Icmp		= 58;
const TUint KProtocolInet6Ip		= 0xF00;	///< Virtual

/**
 * TIp6Addr
 * The raw 128 bits of IP6 address stored in network byte order.
 */
class TIp6Addr
	{
public:
	IMPORT_C TBool IsUnicast() const;
	IMPORT_C TBool IsMulticast() const;
	IMPORT_C TBool IsLoopback() const;
	IMPORT_C TBool IsUnspecified() const;
	IMPORT_C TBool IsLinkLocal() const;
	IMPORT_C TBool IsSiteLocal() const;
	IMPORT_C TBool IsV4Compat() const;
	IMPORT_C TBool IsV4Mapped() const;
	IMPORT_C TBool IsEqual(const TIp6Addr &aAddr) const;
	IMPORT_C TInt Match(const TIp6Addr &aAddr) const;
	IMPORT_C TInt Scope() const;
	union
		{
		TUint8  iAddr8[16];
		TUint16 iAddr16[8];
		TUint32 iAddr32[4];
		} u;
	};

/**
 * IPv6 Address Scope Constants
 * (the standard values, RFC-2373 2.7)
 */
const TInt KIp6AddrScopeNodeLocal = 0x01;
const TInt KIp6AddrScopeLinkLocal = 0x02;
const TInt KIp6AddrScopeSiteLocal = 0x05;
const TInt KIp6AddrScopeOrganization = 0x08;
const TInt KIp6AddrScopeGlobal = 0x0E;
/**
 * (non-standard value, used internally)
 *
 * The Scope() method will return this value, when the
 * address is some form of IPv4 mapped, compatible or
 * other mangling of IPv4 address into IPv6 format. It
 * is assumed that all these have the IPv4 address as
 * the last 4 bytes of the address.
 *
 * *NOTE* 6to4 addresses DO NOT BELONG TO THIS GROUP!
 */
const TInt KIp6AddrScopeMangledV4 = 0x10;


const TIp6Addr KInet6AddrNone = {{{0}}};
const TIp6Addr KInet6AddrLoop = {{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}};
const TIp6Addr KInet6AddrLinkLocal = {{{0xfe, 0x80, }}};

struct SInet6Addr
	{
	TIp6Addr iAddr;		///< 16 bytes of IP6 address (128 bits)
	TUint32 iFlow;		///<  4 bytes of IP6 Flow Id
	TUint32 iScope;		///<  4 bytes of IP6 Scope (this is interface index)
	};


/**
 *	TIp6Mreq
 *		Used by IPv6 multicast join/leave group socket options
 */
class TIp6Mreq
	{
public:
	TIp6Addr iAddr;		// Contains IPv6 multicast address
	TUint iInterface;	// Interface Index
	};

/**
 * This class specialises the generic socket server address class
 * TSockAddr for the TCP/IP protocol family. It represents an IP
 * address and stores either an IPv4 or an IPv6 address in its buffer
 * after the generic data defined by TSockAddr. The protocol family
 * field provided by the TSockAddr base class can be set to KAfInet or
 * KAfInet6.  
 */
class TInetAddr : public TSockAddr
	{
public:
	/** 
	 * Constructs a basic TInetAddr. The port is initialised to 0, 
	 * and the IP address is unspecified. The resulting address family
	 * is KAfUnspec.
	 */
	IMPORT_C TInetAddr();
	
	/** 
	 * Constructs a TInetAddr from another TInetAddr that has been upcast 
	 * to a TSockAddr. The port and IP address values are copied from anAddr.
	 * The resulting address family is same as that of anAddr. This method is a 
	 * raw copying operation of the TSockAddr. No checks are made at this 
	 * point.
	 *
	 * The resulting address family is either KAfInet6 or KAfInet depending on 
	 * anAddr.
	 * 
	 * @param anAddr  TSockAddr from which to copy port and IP address values. 
	 */
	IMPORT_C TInetAddr(const TSockAddr& anAddr);

	/**
	 * Constructs a TInetAddr and initialises the port to the specified value, 
	 * and the IP address is unspecified.	
	 *
	 * @param aPort Value to which to set the port. 
	 */
	IMPORT_C TInetAddr(TUint aPort);

	/**
	 * Constructs a TInetAddr and initialises the port to the
	 * specified value, and the IPv6 address to anAddr. 
	 *
	 * @param anAddr Value to which to set the IPv6 address.  
	 * @param aPort Value to which to set the port.  
	 */
	IMPORT_C TInetAddr(const TIp6Addr &anAddr, TUint aPort);

	/**
	 * Constructs a TInetAddr and initialise the specified port value to aPort
	 * and the IP address to anAddr. The resulting address family is KAfInet.
	 *
	 * @param anAddr Value to which to set the IP address. 
	 * @param aPort Value to which to set the port. 
	 */
	IMPORT_C TInetAddr(TUint32 anAddr, TUint aPort);

	/**
	 * Sets the IPv4 address value. 
	 * An IP address in dotted-decimal form can be converted into a TUint32 
	 * by the INET_ADDR macro. 
	 *
	 * @param anAddr Value to which to set the IPv4 address. 
	 */
	IMPORT_C void SetAddress(TUint32 anAddr);

	/**
	 * Sets the IPv6 address value. 
	 *
	 * @param anAddr Value to which to set the IPv6 address. 
	 */	
	IMPORT_C void SetAddress(const TIp6Addr &anAddr);

	/**
	 * Creates an IPv4 compatible IPv6 address.
	 *
	 * @param anAddr IPv4 address from which the IPv6 address is generated.
	 */
	IMPORT_C void SetV4CompatAddress(TUint32 anAddr);

	/**
	 * Creates an IPv4 mapped IPv6 address.
	 *
	 * @param anAddr IPv4 address from which the IPv6 address is generated.
	 */
	IMPORT_C void SetV4MappedAddress(TUint32 anAddr);

	/**
	 * Only for IPv6, undefined for IPv4.
	 *
	 * @param aLabel the flow label
	 */
	IMPORT_C void SetFlowLabel(TInt aLabel);

	/**
	 * Only for IPv6, undefined for IPv4.
	 *
	 * @return the flow label
	 */
	IMPORT_C TInt FlowLabel() const;

	/**
	 * Only for IPv6, undefined for IPv4.
	 *
	 * @return the IPv6 address
	 */
	IMPORT_C const TIp6Addr &Ip6Address() const;

	/**
	 * Only for IPv4. The method assumes that the previous content is IPv4 
	 * (not checked, uses Address()). The resulting family is KAfInet6
	 */
	IMPORT_C void ConvertToV4Compat();

	/**
	 * Only for IPv4. The method assumes that the previous content is IPv4 
	 * (not checked, uses Address()). The resulting family is KAfInet6
	 */
	IMPORT_C void ConvertToV4Mapped();

	/**
	 * Converts mapped or compatible addresses to IPv4 from IPv6. 
	 */
	IMPORT_C void ConvertToV4();

	/**
	 * Tests the protocol family, IP address, and port values with 
	 * those in another TInetAddr.
	 * 
	 * @param anAddr TInetAddr with which to compare
	 * @return ETrue if protocol family, IP address, and port values are the same, otherwise EFalse. 
	 */
	IMPORT_C TBool CmpAddr(const TInetAddr& anAddr) const;

	/**
	 * Tests the IP address value with that in another TInetAddr.
	 * 
	 * @param aHost TInetAddr with which to compare
	 * @return ETrue if IP address value is the same as this, otherwise EFalse
	 */
	IMPORT_C TBool Match(const TInetAddr& aHost) const;

	/**
	 * Tests if another TInetAddr is in the same subnet. The function applies 
	 * the subnet mask passed through aMask to the IP address and to the IP 
	 * address in aNet. If the resulting values are the same, this indicates 
	 * that the addresses are part of the same subnet, andETrue is returned.
	 * 
	 * @param aNet TInetAddr with which to compare. 
	 * @param aMask TInetAddr object with the IP address set to the relevant subnet mask. 
	 * @return ETrue if both IP address values are the members of the same subnet, otherwise EFalse.
	 */
	IMPORT_C TBool Match(const TInetAddr& aNet, const TInetAddr& aMask) const;

	/**
	 * Return ETrue if leftmost aPrefixLen bits on addresses are same (both 
	 * families must be the same).
	 *
	 * @param aNet TInetAddr with which to compare.
	 * @param aPrefixLen the prefix length.
	 */
	IMPORT_C TBool Match(const TInetAddr& aNet, TInt aPrefixLen) const;

	/**
	 * Generate IPv6 address with leftmost aPrefixLen bits set as 1, and rest 0.
	 * The previous content of the TSockAddr does not matter
	 *
	 * @param aPrefixLen the prefix length
	 */
	IMPORT_C void PrefixMask(TInt aPrefixLen);

	/**
	 * Generate IPv6 address with leftmost aPrefixLen bits copied from aAddr, 
	 * and remaining bits set to 0. The method does not check the family of 
	 * the aAddr, and for IPv4 the resulting prefix value is undefined.
	 *
	 * @param aAddr the address to generate the prefix from.
	 * @param aPrefixLen the number of bits of the resulting prefix
	 */
	IMPORT_C void Prefix(const TInetAddr& aAddr, TInt aPrefixLen);

	/**
	 * Writes the IP address into a string. The format is either
	 * "d.d.d.d" or "h:h:h:h:h:h:h:h" depending on the address
	 * family where "d" is an 8-bit decimal number and "h" is a
	 * 16-bit hexadecimal number.
	 *
	 * @param aBuf On return, contains a string representation of the IP address 
	 */
	IMPORT_C void Output(TDes &aBuf) const;

	/**
	 * Sets the IP address from a string containing a representation of an 
	 * IP address, such as might be entered in a dialog. The string must 
	 * contain an ASCII representation of the address. 
	 * The format may be one of the following examples:
	 * @verbatim
	 * Four 8-bit decimal numbers separated by '.' (eg. 192.168.40.4)
	 * Two 8-bit decimal numbers and a 16 bit decimal (eg. 192.168.10244)
	 * One 8-bit decimal number and a 24-bit decimal (eg. 192.11020292)
	 * One 32 decimal number (eg. 3232245764)
	 * Eight 16-bit hex numbers separated by ':' (eg.2001:618:400:6a:0:0:0:abc)
	 * '::' to denote consecutive zeroes (eg. 2001:618:400:6a::abc)
	 * IPv4 compatible address (eg. ::192.168.40.4)
	 * IPv4 mapped address (eg. ::ffff:192.168.40.4) @endverbatim
	 *
	 * The hexadecimal numbers may be either upper or lower case.
	 *
	 * @param aBuf  Descriptor containing a string representation of an IP address 
	 * @return KErrNone, otherwise another of the system-wide error codes.
	 */
	IMPORT_C TInt Input(const TDesC &aBuf);
	

	/**
	 * Casts a TSockAddr to a TInetAddr reference. The cast is only safe if 
	 * the object being referenced is actually aTInetAddr. 
	 *
	 * @param anAddr  TSockAddr to cast
	 * @return Casted reference to a TInetAddr. 
	 */
	inline static TInetAddr& Cast(const TSockAddr& anAddr);

	/**
	 * Casts a TSockAddr to a TInetAddr reference. The cast is only safe if 
	 * the object being referenced is actually aTInetAddr. 
	 *
	 * @param anAddr  TSockAddr to cast
	 * @return Casted pointer to a TInetAddr. 
	 */
	inline static TInetAddr& Cast(const TSockAddr* anAddr);
	
	/**  Address tests */

	/**
	 * Both IPv4 and IPv6.
	 *
	 * @return ETrue if the address is unicast.
	 */
	IMPORT_C TBool IsUnicast() const;

	/**
	 * Tests if the IP address is Class D (multicast).
	 *
	 * @return ETrue if the IP address value is Class D, otherwise EFalse
	 */
	IMPORT_C TBool IsMulticast() const;

	/**
	 * Both IPv4 and IPv6.
	 *
	 * @return ETrue if the address is loopback.
	 */
	IMPORT_C TBool IsLoopback() const;

	/**
	 * Tests if the IP address is zero (0.0.0.0 or ::). Same as IsWildAddr()
	 *
	 * @return ETrue if the IP address value is zero, otherwise EFalse. 
	 */
	IMPORT_C TBool IsUnspecified() const;

	/**
	 * Both IPv4 and IPv6. Always false for IPv4.
	 *
	 * @return ETrue if this TInetAddr is a link local address.
	 */
	IMPORT_C TBool IsLinkLocal() const;

	/**
	 * Both IPv4 and IPv6. Always false for IPv4.
	 * 
	 * @return ETrue if this TInetAddr is a site local address.
	 */
	IMPORT_C TBool IsSiteLocal() const;

	/**
	 * Both IPv4 and IPv6. Always false for IPv4.
	 * 
	 * @return ETrue if this TInetAddr is a IPv4 compatible address.
	 */
	IMPORT_C TBool IsV4Compat() const;

	/**
	 * Both IPv4 and IPv6. Always false for IPv4.
	 * 
	 * @return ETrue if this TInetAddr is a IPv4 mapped address.
	 */
	IMPORT_C TBool IsV4Mapped() const;
        
	/**
	 * Gets the IPv4 address value. Returns IPv4 address also from IPv6 
	 * addresses that are IPv4 mapped or compatible, otherwise zero for IPv6.
	 * 
	 * @return TUint32 The IP address value 
	 */
	IMPORT_C TUint32 Address() const;  

	/**
	 * This function is deprecated and works only for IPv4.
	 * It assumes the rigid IPv4 address classes (A, B, C). Applications using 
	 * this method may not work properly in the current internet environment. 
	 *
	 * Sets the IP address to a mask suitable for extracting the network 
	 * number part of the IP address. The function tests whether the IP 
	 * address in aAddr is a Class A, B, C, or other address. It then sets 
	 * the IP address to suitable mask values as follows:
	 * @verbatim
	 * Class A addresses: mask 255.0.0.0
	 * Class B addresses: mask 255.255.0.0
	 * Class C addresses: mask 255.255.255.0
	 * other addresses: mask 255.255.255.255 @endverbatim
	 *
	 * @param aAddr  TInetAddr from which to obtain IP address
	 */
	IMPORT_C void NetMask(const TInetAddr& aAddr);

	/**
	 * This function is deprecated and works only for IPv4.
	 * It assumes the rigid IPv4 address classes (A, B, C). Applications using 
	 * this method may not work properly in the current internet environment.
	 *
	 * Obtains a network mask corresponding to the class of the IP address, 
	 * using the NetMask() function. It then applies this mask to the current 
	 * IP address.
	 * 
	 * @param aAddr TInetAddr from which to obtain IP address for creating the network mask. 
	 */
	IMPORT_C void Net(const TInetAddr& aAddr);

	/**
	 * This function is deprecated and works only for IPv4.
	 * It assumes the rigid IPv4 address classes (A, B, C). Applications using 
	 * this method may not work properly in the current internet environment.
	 *
	 * Sets the IP address to be suitable for a network-directed broadcast 
	 * address. The function obtains a network mask corresponding to the class 
	 * of the IP address in aAddr, using the NetMask() function. It then 
	 * applies this mask to the current IP address to separate the network 
	 * number part of the address. The mask is then used again to set all host 
	 * number bits to 1 (which signifies, broadcast to all hosts on the network).
	 * 
	 * @param aAddr TInetAddr from which to obtain IP address for creating the network mask. 
	 */
	IMPORT_C void NetBroadcast(const TInetAddr& aAddr);

	/**
	 * Sets the IP address to the network number and subnet parts of the IP 
	 * address (that is, the original IP address with the host number part 
	 * cleared). This is obtained by applying the mask value in aMask to the 
	 * IP address in aAddr. 
	 *
	 * The result is undefined if address and mask have different address family.
	 *
	 * @param aAddr TInetAddr from which to obtain IP address
	 * @param aMask TInetAddr object with the IP address set to the relevant subnet mask. 
	 */
	IMPORT_C void SubNet(const TInetAddr& aAddr, const TInetAddr& aMask);

	/**
	 * Sets the IP address to be suitable for a subnet-directed broadcast 
	 * address. To achieve this, the subnet mask value in aMask is applied 
	 * to the IP address in aAddr. The mask is then used again to set all 
	 * host number bits to 1 (which signifies, broadcast to all hosts on the 
	 * subnet).
	 *
	 * Only for IPv4. The method does not have a sensible interpretation in 
	 * IPv6. An application that uses this needs to code separate branches for 
	 * IPv4 and IPv6 cases.
	 * 
	 * @param aAddr  TInetAddr from which to obtain IP address
	 * @param aMask  TInetAddr object with the IP address set to the relevant subnet mask. 
	 */
	IMPORT_C void SubNetBroadcast(const TInetAddr& aAddr, const TInetAddr& aMask);
        

	/**
	 * This function is deprecated and works only for IPv4.
	 * It assumes the rigid IPv4 address classes (A, B, C). Applications using 
	 * this method may not work properly in the current internet environment.
	 *
	 * Tests if the IP address is Class A.
	 *
	 * @return ETrue if the IPv4 address value is Class A, otherwise EFalse
	 */
	inline TBool IsClassA() const;

	/**
	 * This function is deprecated and works only for IPv4.
	 * It assumes the rigid IPv4 address classes (A, B, C). Applications using 
	 * this method may not work properly in the current internet environment.
	 *
	 * Tests if the IP address is Class B.
	 *
	 * @return ETrue if the IPv4 address value is Class B, otherwise EFalse
	 */
	inline TBool IsClassB() const;

	/**
	 * This function is deprecated and works only for IPv4.
	 * It assumes the rigid IPv4 address classes (A, B, C). Applications using 
	 * this method may not work properly in the current internet environment.
	 *
	 * Tests if the IP address is Class C.
	 *
	 * @return ETrue if the IPv4 address value is Class C, otherwise EFalse
	 */
	inline TBool IsClassC() const;

	/**
	 * This function is deprecated and works only for IPv4.
	 * It assumes the rigid IPv4 address classes (A, B, C). Applications using 
	 * this method may not work properly in the current internet environment.
	 *
	 * Tests if the IP address is a limited broadcast address (255.255.255.255).
	 *
	 * @return ETrue if the IPv4 address value is a limited broadcast address, otherwise EFalse
	 */
	inline TBool IsBroadcast() const;

	/**
	 * Tests if the IP address is zero (0.0.0.0 or ::). Same as IsUnspecified()
	 *
	 * @return ETrue if the IP address value is zero, otherwise EFalse. 
	 */
	inline TBool IsWildAddr() const;

	/**
	 * Tests if the port is zero.
	 *
	 * @return ETrue if the port is zero, otherwise EFalse.
	 */
	inline TBool IsWildPort() const;

#ifdef _MKLOG
	IMPORT_C void Log(const char *aFormat) const;
#endif


	/**
	 * Set the IPv6 scope
	 *
	 * @param aScope the scope of the IPv6 address.
	 */
	IMPORT_C void SetScope(TUint32 aScope);

	/**
	 * Get the IPv6 scope
	 *
	 * @return the scope of the IPv6 address.
	 */
	IMPORT_C TUint32 Scope() const;

	/**
	 * Initialises the object properly according to the address family passed in.
	 *
	 * @param aFamily The address family.
	 */
	IMPORT_C void Init(TUint aFamily);
protected:
	inline SInetAddr *Addr4Ptr() const;
	inline SInet6Addr *AddrPtr() const;
	inline static TInt AddrLen();
private:
	TInt Ipv4Input(const TDesC& aDes);
	TInt Ipv6Input(const TDesC& aDes);
	};


/** Inline methods */
inline SInet6Addr* TInetAddr::AddrPtr() const
	{ return (SInet6Addr*)UserPtr(); }

// XXX - Test family or return max size?
inline TInt TInetAddr::AddrLen()
	{ return sizeof(SInet6Addr); }

inline TInetAddr& TInetAddr::Cast(const TSockAddr& anAddr)
        { return *((TInetAddr*)&anAddr); }

inline TInetAddr& TInetAddr::Cast(const TSockAddr* anAddr)
        { return *((TInetAddr*)anAddr); }

/**  Compatibility */
inline SInetAddr* TInetAddr::Addr4Ptr() const
	{ return (SInetAddr*)UserPtr(); }

inline TBool TInetAddr::IsBroadcast() const
	{ return Address() == KInetAddrBroadcast; }

inline TBool TInetAddr::IsWildPort() const
	{ return Port() == KInetPortNone; }

inline TBool TInetAddr::IsWildAddr() const
	{ return IsUnspecified(); }

inline TBool TInetAddr::IsClassA() const
	{ return (Address() & KInetAddrIdMaskA) == KInetAddrIdValA; }

inline TBool TInetAddr::IsClassB() const
	{ return (Address() & KInetAddrIdMaskB) == KInetAddrIdValB; }

inline TBool TInetAddr::IsClassC() const
	{ return (Address() & KInetAddrIdMaskC) == KInetAddrIdValC; }

/**  Send/Recv Flags (Datagram sockets only) */
const TUint KIpDontFragment		= 0x010000;
const TUint KIpHeaderIncluded	= 0x020000;
const TUint KIpDontRoute		= 0x040000;

/**  Structure returned by KSoInetLastError/KIoctlInetLastError */
class TSoInetLastErr
	{
public:
	TInt iStatus;			// ESock error code
	TInt iErrType;			// ICMP type
	TInt iErrCode;			// ICMP code
	TInetAddr iSrcAddr;		// Src of failed datagram
	TInetAddr iDstAddr;		// Dst of failed datagram
	TInetAddr iErrAddr;		// Addr of host that generated the error
	};

/**
 *	New IPv6 specific Socket Options
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
const TUint KSoIp6UnicastHops		= 0x465; ///<¨Same as KSoIpTTL (set/get hoplimit)
const TUint KSoIp6MulticastIf		= 0x46a; ///< Interface for outgoing multicast packets
const TUint KSoIp6MulticastHops		= 0x46b; ///< Hop limit for multicast packets (default = 1)
const TUint KSoIp6MulticastLoop		= 0x46c; ///< Loopback of the multicast packets (default = 1)
const TUint KSoIp6JoinGroup			= 0x46d; ///< Uses TIp6Mreq structure
const TUint KSoIp6LeaveGroup		= 0x46e; ///< Uses TIp6Mreq structure

/**
 * Level == KSolInetIfCtrl
 * Enumerating & Configuring Interfaces TPckgBuf<TSoInetInterfaceInfo>
 * With a level of KSolInetIfCtrl
 */ 
const TInt KSoInetEnumInterfaces = 0x211;
const TInt KSoInetNextInterface = 0x212;
const TInt KSoInetConfigInterface = 0x213;

enum TIfStatus
	{
	EIfPending,
	EIfUp,
	EIfBusy,
	EIfDown,
	};

class TSoInetInterfaceInfo
	{
public:
	TName iTag;				///< Interface tag
	TName iName;			///< Interface name
	TIfStatus iState;		///< State
	TInt iMtu;				///< max transmition size
	TInt iSpeedMetric;		///< Metric - bigger is better
	TUint iFeatures;		///< Feature flags
	TSockAddr iHwAddr;		///< Hardware address (*)
	TInetAddr iAddress;		///< Interface IP Address (*)
	TInetAddr iNetMask;		///< IP netmask
	TInetAddr iBrdAddr;		///< IP broadcast address
	TInetAddr iDefGate;		///< IP default gateway or peer address (if known)
	TInetAddr iNameSer1;	///< IP Primary name server (if any)
	TInetAddr iNameSer2;	///< IP Secondary name server (if any)
	};

/**
 *		New IPv6 functionality, allow ConfigInterface in SetOption, and add
 *		two new options.
 *
 *		*NOTE*
 *			The difference between Config and Change is only that the Change will
 *			not create new interface entry, if it does not exist. Config never
 *			fails on "interface not found", it always finds some (or creates).
 */
 
const TUint KSoInetDeleteInterface = 0x214;	// Delete interface
const TUint KSoInetChangeInterface = 0x215;

class TSoInet6InterfaceInfo : public TSoInetInterfaceInfo
	{
public:
	TUint iDelete:1;	///< 0 = Add, 1 = delete
	TUint iAlias:1;		///< 0 = Primary, 1 = Alias
	TUint iDoPrefix:1;	///< 0 = Ignore prefix part, 1=process prefix
	TUint iDoId:1;		///< 0 = Ignore id part, 1=process id
	TUint iDoState:1;	///< 0 = Ignore iState, 1=set interface state from iState
	TUint iDoAnycast:1;	///< 1 = Configure anycast (DoPrefix/DoId ignored!)
	};

/**
 * IPv6/IPv4 stack specific
 * KSolInetIfQuery
 */
class TSoInetIfQuery
	{
public:
	TInetAddr iDstAddr;		///< Destination address
	TInetAddr iSrcAddr;		///< Source address
	TUint32 iIndex;			///< Interface Index
	TName iName;			///< Interface Name
	TUint iIsUp:1;			///< 1 = if interface has CNifIfBase * attached
	};
/**
 * Only GetOption for KSolInetIfQuery is supported. It returns
 * information about the selected interface. The option name
 * determines the input field in the TSoInetIfQuery, which is
 * used as a key for locating the interface.
 */
const TUint KSoInetIfQueryByDstAddr	= 0x1;
const TUint KSoInetIfQueryBySrcAddr	= 0x2;
const TUint KSoInetIfQueryByIndex	= 0x3;
const TUint KSoInetIfQueryByName	= 0x4;
//const TUint KSoInetIfQueryByNextIndex = 0x5;
/**
 * Returns, KErrNotFound, if interface is not found
 *
 * Returns, KErrNone, if interface is located, and fills
 * fields from the interface with following logic
 *
 * 1. iDstAddr: not touched, left as is
 * 2. iSrcAddr is result of the Select Source Address algorithm
 *    for the interface using the iDstAddr as input. If there
 *    is no valid source address, the value will be KAFUnspec.
 * 3. iIndex is loaded with the interface index of the interface
 * 4. iName is loaded from the name of the interface
 * 5. iIsUp is set 1, if interface has CNifIfBase pointer attached,
 *    and 0 otherwise.
 *
 * For example, if QueryByDstAddr for specified destination address
 * results iIsUp == 1, then there is an interface and route for that
 * destination. iIsUp == 0, means that trying to connect to the address
 * will most likely activate a netdial/interface link startup phase.
 *  
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	New UDP option for IPv4/6 Dual Stack
 *
 * Level == KSolInetUdp
 *
 *			Setting the KSoUdpSynchronousSend option causes the UDP send operation
 *			to block when dynamic interface setup is in progress or when local
 *			flow control within the stack would otherwise cause the packet to
 *			be dropped.
 */
const TUint KSoUdpSynchronousSend	= 0x560;

/**
 * Enumerating & Configuring Routes TPckgBuf<TSoInetRouteInfo>
 * With a level of KSolInetRtCtrl
 */
const TInt KSoInetEnumRoutes = 0x221;
const TInt KSoInetNextRoute = 0x222;
const TInt KSoInetAddRoute = 0x223;
const TInt KSoInetDeleteRoute = 0x224;
const TInt KSoInetChangeRoute = 0x225;

enum TRouteState
	{
	ERtNone,
	ERtPending,		///< Interface has been started as a dialup, but no info available
	ERtBusy,		///< Interface is up but flowed off
	ERtReady,		///< Interface is up and ready
	ERtDown		    ///< Route is down and most likely to stay that way
	};

enum TRouteType
	{
	ERtNormal,		///< Created when interface was started
	ERtUser,		///< Created by user - ie via SetOpt()
	ERtIcmpAdd,		///< Added by ICMP redirect
	ERtIcmpDel		///< Replaced by an ICMP redirect
	};

class TSoInetRouteInfo
	{
public:
	TRouteType iType;		///< Type of route (normal/icmp generated etc)
	TRouteState iState;		///< State of route
	TInt iMetric;			///< Smaller is better (less hops and/or faster link)
	TInetAddr iIfAddr;		///< IP address of interface used for this route
	TInetAddr iGateway;		///< IP address of gateway (might be the interface)
	TInetAddr iDstAddr;		///< Destination network or host
	TInetAddr iNetMask;		///< Destination mask of network (or host if KInetMaskHost)
	};

/**
 * Access to route cache TPckgBuf<TSoInetCachedRouteInfo>, set iDstAddr for required address
 * With a level of KSolInetRtCtrl
 */
const TInt KSoInetCachedRouteByDest = 0x225;

class TSoInetCachedRouteInfo : public TSoInetRouteInfo
	{
public:
	TInt iPathMtu;			///< Set if used by DF datagram (incl TCP SYN), else 0
	TUint iPathRtt;			///< Set if used by TCP, else 0
	};

/** Flags returned from DNS records */
enum TNameRecordFlags
	{
	EDnsAlias=0x00000001,		///< Name is an Alias
	EDnsAuthoritive=0x00000002, ///< Answer is authoritive 
	EDnsHostsFile=0x00000004,   ///< Answer is from hosts file
	EDnsServer=0x00000008,      ///< Answer is from a DNS server
	EDnsHostName=0x00000010,    ///< Answer is host name for this host
	EDnsCache=0x00000020		///< Answer is from the resolver cache
	};
const TUint KSoDnsCacheEnable = 0x600; ///< Get/Set
const TUint KSoDnsCacheFlush = 0x601; ///<Set

/**
 * TCP specific options and ioctls with a level of KSolInetTcp
 * Ioclt
 */
const TUint KIoctlTcpNotifyDataSent = 0x300;
/** Options */
const TUint KSoTcpSendWinSize = 0x301; ///< Get/Set before connect
const TUint KSoTcpRecvWinSize = 0x302; ///< Get/Set before connect
const TUint KSoTcpMaxSegSize = 0x303; ///< Get/Set before connect
const TUint KSoTcpNoDelay = 0x304; ///< Get/Set
const TUint KSoTcpKeepAlive = 0x305; ///< Get/Set
const TUint KSoTcpAsync2MslWait = 0x306; ///< Get/Set
const TUint KSoTcpSendBytesPending = 0x307; ///<Get
const TUint KSoTcpReadBytesPending = 0x308; ///<Get
const TUint KSoTcpListening = 0x309; ///<Get
const TUint KSoTcpNumSockets = 0x310; ///<Get
const TUint KSoTcpReadUrgentData = 0x311; ///<Get
const TUint KSoTcpPeekUrgentData = 0x312; ///<Get
const TUint KSoTcpRcvAtMark = 0x313; ///<Get
const TUint KSoTcpNextSendUrgentData = 0x314; ///<Get/Set
const TUint KSoTcpOobInline = 0x315; ///<Set
const TUint KSOTcpDebugMode = 0x11110000;

/** SECURITY SPECIFIC STUFF */

/** At level KSolInetSSL */
const TUint KSoSecureSocket = 0x400;          ///< set/clear secure socket
const TUint KSoSSLUnloadTimeout = 0x401;      ///< set/get SSL dll unload timeout
const TUint KSoCurrentCipherSuite = 0x402;    ///< set/get current cipher suite
const TUint KSoSSLServerCert = 0x403;	      ///< get current server cert
const TUint KSoDialogMode = 0x404;            ///< set/get current dialog mode
const TUint KSoAvailableCipherSuites = 0x405; ///< set/get supported cipher suites

/** For KSoTcpSecureSocket */
const TUint KSSLClearSecureStatus = 0x00; ///< disconnect SSL session
const TUint KSSLSetSecureStatus = 0x01;   ///< complete connect on SSL connect

/** For KSoDialogMode */
const TUint KSSLDialogUnattendedMode = 0x00; ///< dialogs
const TUint KSSLDialogAttendedMode = 0x01;   ///< no dialogs

/** Generic with a level of KSolInetIp */
const TUint KSoIpOptions = 0x401; ///< Set/Get
const TUint KSoRawMode = 0x402; ///< Set/Get
const TUint KSoHeaderIncluded = 0x403; ///< Set/Get
const TUint KSoIpTOS = 0x404; ///< Set/Get
const TUint KSoIpTTL = 0x405; ///< Set/Get
const TUint KSoReuseAddr = 0x406; ///<Set/Get
const TUint KSoNoInterfaceError = 0x407; ///<Set/Get
const TUint KSoUserSocket = 0x408; ///<Set/Get
const TUint KSoInterfaceIndex = 0x409; //Set/Get (flow option)
const TUint KSoKeepInterfaceUp = 0x40a; //Set/Get (flow option)
const TUint KSoInetLastError = 0x200; ///< Get Last ICMP error TPckgBuf<TSoInetLastErr>
const TUint KIoctlInetLastError = 0x200; ///< Exactly the same a the GetOpt

/**  UDP specific with a level of KSolInetUdp */
const TUint KSoUdpReceiveICMPError = 0x500; ///<Set/Get

/**  Extended error codes */
const TInt KErrNetUnreach = -190;
const TInt KErrHostUnreach = -191;
const TInt KErrNoProtocolOpt = -192;
const TInt KErrUrgentData = -193;

#endif
