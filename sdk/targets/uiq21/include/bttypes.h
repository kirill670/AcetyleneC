// BTTypes.h
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
//

//
// BT protocol wide types
//

#ifndef BTTYPES_H
#define BTTYPES_H

#include <e32std.h>

typedef TUint16 THCIConnHandle;

enum TBTHostMode
    {
    EActiveMode,        // 0x00 - this is the default
    EHoldMode,          // 0x01
    ESniffMode,         // 0x02
    EParkMode,          // 0x03
    };

enum TBTBasebandRole
	{
	EMaster,			// 0x00
	ESlave,				// 0x01
	};

static const TInt KSdpUUIDMaxLength			= 16;
const TInt KBTDevAddrSize=0x06;
const TInt KBTMaxDevAddrSize = KBTDevAddrSize;

/**
   48-bit bluetooth device address.
   Each bluetooth device has a unique address built into the hardware, which
   is represented by this class. Used for identifying remote addresses.
   The interface operates in a big-endian manner -- e.g. addr[0] refers
   to the most significant byte of the address. This is the same ordering
   as the addresses would naturally be written down on paper.
**/
class TBTDevAddr
    {
public:
    IMPORT_C TBTDevAddr();
    IMPORT_C TBTDevAddr(const TInt64 &aInt); ///< Construct from a TInt64
    IMPORT_C TBTDevAddr(const TDesC8 &aDes);  ///< Construct from a buffer
    inline TBool operator==(const TBTDevAddr& aAddr) const;
    inline TBool operator!=(const TBTDevAddr& aAddr) const;
	inline const TUint8 &operator[](TInt aIndex) const;
	inline TUint8 &operator[](TInt aIndex);
	inline void Reset(); ///< Zero fill
	inline TPtr8 Des();  ///< Access value as a bigendian descriptor
	inline const TPtrC8 Des() const;
	IMPORT_C TInt SetReadable(const TDesC& aSource);
	inline void GetReadable(TDes& aDest) const;
	IMPORT_C void GetReadable(TDes& aDest, const TDesC& aPrepend, const TDesC& aByteSeperator, const TDesC& aAppend) const;
private:
	TFixedArray<TUint8, KBTDevAddrSize> iAddr;
    };

/**
	A Bluetooth Universally Unique Identifier.

	This is a 128-bit quantity that can be created without a central registry 
	while still being globally unique.
	UUIDs are always held in full 128 bit format, however they can be set from 
	BT SIG short form (16 or 32 bit) addresses, and returned as down to their 
	shortest form using ShortestForm().
**/
class TUUID
	{
public:
	IMPORT_C TUUID();
	IMPORT_C TUUID(TUint32 aLong);
	IMPORT_C TUUID(TUint32 aHH, TUint32 aHL, TUint32 aLH, TUint32 aLL);
	IMPORT_C TUUID(const TUid& aUid);
	IMPORT_C void SetL(const TDesC8& aDes);
	IMPORT_C const TPtrC8 LongForm() const;
	IMPORT_C const TPtrC8 ShortestForm() const;
	IMPORT_C const TPtrC8 Des() const;
    inline TBool operator==(const TUUID& aUUID) const;
    inline TBool operator!=(const TUUID& aUUID) const;
	inline const TUint8 &operator[](TInt aIndex) const;
	inline TUint8 &operator[](TInt aIndex);
private:
	TFixedArray<TUint8, KSdpUUIDMaxLength> iUUID;
	};

const TUint8 KHCILinkKeySize=16;
const TUint8 KHCIPINCodeSize=16;

class TLinkKeyV10
    {
public:
    TUint8 iLinkKey[KHCILinkKeySize];
    };

/**
@internal
Struct used to transfer new Juice information from host resolver client to server.
Juice information contains data pertaining to 
**/

class RWriteStream;
class RReadStream;

class TBTBasebandParameters
	{
public:

	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);			
	IMPORT_C TInt SizeOffJuice( void );		

	TBTDevAddr iBdaddr;
	TUint8 iPageScanRepetitionMode;				///< Page Scan repetition mode of remote device ( valid if > 0 )
	TUint8 iPageScanMode;					///< Page scan mode of remote device ( valid if > 0 )
	TUint16 iClockOffset;					///< clock off set of remote device ( valid if > 0 )
	};

typedef TPckgBuf<TBTBasebandParameters> TBTBasebandParametersPckg;

class TBTDevicesV1
	{
	public:
//	TInt					iNumberOfDevicesFound;	//Number of devices retrieved in search criteria
	TBTBasebandParameters	iBaseBandParameter;		//Single baseband parameter for single BTDevice
//	TInt					iCurrentDeviceIndex;	//Index of the current device.
	};

typedef TPckgBuf<TLinkKeyV10> TBTLinkKey;
typedef TPckgBuf<TBTDevicesV1> TBTDevices;



class TPINCodeV10
    {
public:
    TUint8 iLength; 
    TUint8 iPIN[KHCIPINCodeSize];
    };
typedef TPckgBuf<TPINCodeV10> TBTPinCode;

const TUint   KGIAC=0x9e8b33; // General Unlimited Inquiry Access Code
const TUint   KLIAC=0x9e8b00; // Limited Inquiry Access Code

#include <bttypes.inl>

#endif
