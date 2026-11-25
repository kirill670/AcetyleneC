// BTDevice.h
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

#ifndef BTDEVICE_H
#define BTDEVICE_H

#include <e32std.h>
#include <e32base.h>
#include <s32mem.h>
#include <bttypes.h>

/** Bluetooth device name buffer. */
typedef TBuf<256> TBTDeviceName;

//forward decs
class TBTDeviceClass;
class CBTDevice;
class TBTDeviceSecurityPerService;

typedef CArrayPtrFlat<CBTDevice> CBTDeviceArray;
typedef CArrayFixFlat<TBTDeviceSecurityPerService> CBTSecurityArray;

const TInt KSecurityGranularity=1;

class BTDeviceArrayCleanupStack
/** Cleanup utility for CBTDeviceArrays.

Creates a TCleanupItem that calls ResetAndDestroy and then deletes the array.
**/
	{
public:
	inline static void PushL(CBTDeviceArray* aBTDeviceArray);
private:
	inline static void ResetAndDestroy(TAny* aBTDeviceArray);
	};

inline void BTDeviceArrayCleanupStack::PushL(CBTDeviceArray* aBTDeviceArray)
	{
	CleanupStack::PushL(TCleanupItem(&BTDeviceArrayCleanupStack::ResetAndDestroy, (TAny*)aBTDeviceArray));
	}
inline void BTDeviceArrayCleanupStack::ResetAndDestroy(TAny* aBTDeviceArray)
	{
	CBTDeviceArray* array = STATIC_CAST(CBTDeviceArray*,aBTDeviceArray);
	array->ResetAndDestroy();
	delete array;
	}


enum TBTMajorServiceClass
	{												//23        13	<- bit number
	EMajorServiceLimitedDiscoverableMode = 0x01,	//00000000001
	EMajorServiceNetworking = 0x10,					//00000010000
	EMajorServiceRendering = 0x20,					//00000100000
	EMajorServiceCapturing = 0x40,					//00001000000
	EMajorServiceObjectTransfer = 0x80,				//00010000000
	EMajorServiceAudioService = 0x100,				//00100000000
	EMajorServiceTelephony = 0x200,					//01000000000
	EMajorServiceInformation = 0x400				//10000000000
	};

enum TBTMajorDeviceClass
	{												//12  8	<- bit number
	EMajorDeviceMisc = 0x0,							//00000
	EMajorDeviceComputer = 0x1,						//00001
	EMajorDevicePhone = 0x2,						//00010
	EMajorDeviceLanAccessPoint = 0x3,				//00011
	EMajorDeviceAudioDevice = 0x4,					//00100
	EMajorDevicePeripheral = 0x5,					//00101
	EMajorDeviceImaging = 0x6,                      //00110
	EMajorDeviceDeviceUnclassified = 0x1F			//11111
	};

enum TBTMinorDeviceClassComputer
	{										//7    2	<- bit number
	EMinorDeviceComputerUnclassified = 0x0,	//000000
	EMinorDeviceComputerDesktop = 0x1,		//000001
	EMinorDeviceComputerServer = 0x2,		//000010
	EMinorDeviceComputerLaptop = 0x3,		//000011
	EMinorDeviceComputerHandheld = 0x4,		//000100
	EMinorDeviceComputerPalmSize = 0x5		//000101
	};

enum TBTMinorDeviceClassPhone
	{										//7    2	<- bit number
	EMinorDevicePhoneUnclassified = 0x0,	//000000
	EMinorDevicePhoneCellular = 0x1,		//000001
	EMinorDevicePhoneCordless = 0x2,		//000010
	EMinorDevicePhoneSmartPhone = 0x3,		//000011
	EMinorDevicePhoneWiredModem = 0x4		//000100
	};

enum TBTMinorDeviceClassLAN
	{																//7    2	<- bit number
	EMinorDeviceLANFullyAvailable = 0x0,	///< 0% usage			//000000
	EMinorDeviceLANServiceOne = 0x8,		///< 1-17% utilized		//001000
	EMinorDeviceLANServiceTwo = 0x10,		///< 17-33% utilized	//010000
	EMinorDeviceLANServiceThree = 0x18,		///< 33-50% utilized	//011000
	EMinorDeviceLANServiceFour = 0x20,		///< 50-67% utilized	//100000
	EMinorDeviceLANServiceFive = 0x28,		///< 67-83% utilized	//101000
	EMinorDeviceLANServiceSix = 0x30,		///< 83-99% utilized	//110000
	EMinorDeviceLANNoService = 0x38,		///< 100% utilized		//111000
	};

enum TBTMinorDeviceClassAV
	{												//7    2
	EMinorDeviceAVUnclassified = 0x0,				//000000
	EMinorDeviceAVHeadset = 0x1,					//000001
	EMinorDeviceAVHandsfree = 0x2,					//000010
	EMinorDeviceAVMicrophone = 0x4,					//000100
	EMinorDeviceAVLoudspeaker = 0x5,				//000101
	EMinorDeviceAVHeadphones = 0x6,					//000110
	EMinorDeviceAVPortableAudio = 0x7,				//000111
	EMinorDeviceAVCarAudio = 0x8,					//001000
	EMinorDeviceAVSetTopBox = 0x9,					//001001
	EMinorDeviceAVHiFiAudio = 0xA,					//001010
	EMinorDeviceAVVCR = 0xB,						//001011
	EMinorDeviceAVVideoCamera = 0xC,				//001100
	EMinorDeviceAVCamcorder = 0xD,					//001101
	EMinorDeviceAVVideoMonitor = 0xE,				//001110
	EMinorDeviceAVVideoDisplayAndLoudspeaker = 0xF,	//001111
	EMinorDeviceAVVideoConferencing = 0x10,			//010000
	EMinorDeviceAVGamingToy = 0x12					//010010
	};

enum TBTMinorDeviceClassHeadset
	{										//7    2
	EHeadsetUnclassified = 0x0,				//000000
	EHeadsetProfile = 0x1,					//000001
	};

class TBTDeviceClass
/** Bluetooth service and device class information.

The class specifies the major and minor device class, and a service class. */
	{
public:
	IMPORT_C TBTDeviceClass();
	IMPORT_C TBTDeviceClass(TUint32 aDeviceClass);
	IMPORT_C TBTDeviceClass(TUint16 aMajorServiceClass, TUint8 aMajorDeviceClass,
							TUint8 aMinorDeviceClass);
	IMPORT_C TUint16 MajorServiceClass();	///<Returns service class - caller must parse bitwise field
	IMPORT_C TUint8 MajorDeviceClass();			///<Returns major device type
	IMPORT_C TUint8 MinorDeviceClass();			///<Returns minor device type
	IMPORT_C TUint32 DeviceClass() const;							///<Returns 32bit integer defining device class
	IMPORT_C TBool operator==(const TBTDeviceClass& aDeviceClass) const;

	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	///<Internalize data from a stream
	IMPORT_C void InternalizeL(RReadStream& aStream);			///<Externalize data to a stream
private:
	TUint32 iDeviceClass;
	};

class TBTDeviceSecurity
/** Class to store the security parameters for a device. */
	{
public:
	IMPORT_C TBTDeviceSecurity();
	IMPORT_C TBTDeviceSecurity(TUint8 aSecurity);
	IMPORT_C TBTDeviceSecurity(TBool aNoAuthenticate, TBool aNoAuthorise, TBool aEncrypt, TBool aBanned);
	IMPORT_C void SetNoAuthenticate(TBool aDecision);
	IMPORT_C void SetNoAuthorise(TBool aDecision);
	IMPORT_C void SetEncrypt(TBool aDecision);
	IMPORT_C void SetBanned(TBool aDecision);
	IMPORT_C TBool NoAuthenticate() const;
	IMPORT_C TBool NoAuthorise() const;
	IMPORT_C TBool Encrypt() const;
	IMPORT_C TBool Banned() const;
	IMPORT_C TUint8 SecurityValue() const;
	IMPORT_C void SetSecurityValue(TUint8);
	IMPORT_C TBool operator==(const TBTDeviceSecurity&) const;
	IMPORT_C TBool operator!=(const TBTDeviceSecurity&) const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	///<Internalize data from a stream
	IMPORT_C void InternalizeL(RReadStream& aStream);			///<Externalize data to a stream

public:
	enum TBTDeviceSecuritySettings
		{
		ENoAuthenticate	= 0x01,
		ENoAuthorise = 0x02,
		EEncrypt = 0x04,
		EBanned = 0x08
		};

private:
	TUint8 iSecurity;
	};

class TBTDeviceSecurityPerService
/** Class to tie a service uid with a device security setting.

This allows us to have service-specific security settings for a device. */
	{
public:
	IMPORT_C TBTDeviceSecurityPerService();
	IMPORT_C TBTDeviceSecurityPerService(TUid aServiceUid, TBTDeviceSecurity aSecuritySettings);
	IMPORT_C TBTDeviceSecurityPerService(const TBTDeviceSecurityPerService&);
	IMPORT_C void SetDeviceSecurity(TBTDeviceSecurity aSecuritySettings);
	IMPORT_C void SetUid(TUid aServiceUid);
	IMPORT_C TBTDeviceSecurity DeviceSecurity() const;
	IMPORT_C TUid ServiceUid() const;
	IMPORT_C void operator=(const TBTDeviceSecurityPerService&);
	IMPORT_C TBool operator==(const TBTDeviceSecurityPerService&) const;
	IMPORT_C TBool operator!=(const TBTDeviceSecurityPerService&) const;
	IMPORT_C static TInt UidOffset();	///<Returns the offset of iUid, allowing an array-search-by-uid to be performed
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	///<Internalize data from a stream
	IMPORT_C void InternalizeL(RReadStream& aStream);			///<Externalize data to a stream
private:
	TUid iUid;
	TBTDeviceSecurity iDeviceSecurity;
	};

class CBTDevice : public CBase
/** Encapsulates all information that must be known about a device. */
	{
public:
	IMPORT_C static CBTDevice* NewL(const TBTDevAddr& aBDAddr);
	IMPORT_C static CBTDevice* NewLC(const TBTDevAddr& aBDAddr);
	IMPORT_C static CBTDevice* NewL();
	IMPORT_C static CBTDevice* NewLC();
	~CBTDevice();
	IMPORT_C void ConstructL();
	IMPORT_C CBTDevice* CopyL() const;				///< Copies the contents of this into a new CBTDevice object
	IMPORT_C void UpdateL(const CBTDevice& aDevice);	///< Copies the contents of aDevice into *this
//Getters
	IMPORT_C const TBTDevAddr& BDAddr() const;				///< Returns the address of the device
	IMPORT_C const TDesC& DeviceName() const;		///< Returns the name of the device
	IMPORT_C const TDesC& FriendlyName() const;		///< Returns the friendly name of the device
	IMPORT_C TBTDeviceClass DeviceClass() const;	///< Returns the class of the device
	IMPORT_C const TBTLinkKey& LinkKey() const;		///< Returns the link key of the device

	IMPORT_C const TUint32 PageScanRepMode() const;	///< Returns the Page Scan Repitition Mode of the device
	IMPORT_C const TUint32 PageScanMode() const;	///< Returns the Page Scan Mode of the device
	IMPORT_C const TUint32 ClockOffSet() const;		///< Returns the Clock-Off-Set of the device

	IMPORT_C const TBTDeviceSecurity GlobalSecurity() const; ///< Returns the Global security settings for all services used by this device
	IMPORT_C const CBTSecurityArray& IndividualSecurityArray() const; ///< Returns the individual security settings for Services useb by this device
	IMPORT_C const TBTDeviceSecurityPerService& FindServiceL(TUid aServiceUid) const;	///<Locates the service with uid aServiceUid. Returns KErrNotFound if service isn't found.

//Setters
	IMPORT_C void SetDeviceAddress(const TBTDevAddr& aBDAddr);	///< Set the address of the device
	IMPORT_C void SetDeviceName(const TDesC& aName);	///< Set the name of the device
	IMPORT_C void SetFriendlyName(const TDesC& aName);	///< Set the friendly name of the device
	IMPORT_C void SetDeviceClass(TBTDeviceClass aDeviceClass);	///< Set the class of the device
	IMPORT_C void SetLinkKey(const TBTLinkKey& aLinkKey);	///< Set the link key of the device
	
	IMPORT_C void SetPageScanRepMode(const TUint32& aPageScanRepMode);	///<Set the Page Scan Repition mode for device
	IMPORT_C void SetPageScanMode(const TUint32& aPageScanMode);			///<Set the Page Scan Mode for device
	IMPORT_C void SetClockOffSet(const TUint32& aClockOffSet);			///<Set the clock off set for device

	IMPORT_C void SetGlobalSecurity(const TBTDeviceSecurity& aSetting); ///< Set the Global security settings for all services used by this device
	IMPORT_C void SetIndividualSecurityArrayL(const CBTSecurityArray& aSetting); ///< set the individual security settings for Services useb by this device
	IMPORT_C void SetServiceSecurityL(const TBTDeviceSecurityPerService& aService); ///<Adds service to array if doesn't exist, else modifies the existing one.
	IMPORT_C void DeleteServiceSecurityL(TUid aServiceUid); ///<Deletes the service with uid aServiceUid from the array.

	IMPORT_C void DeleteLinkKey();	///<ensure that the previously known linkkey is discarded

//
	IMPORT_C static CBTDeviceArray* CopyBTDeviceArrayL(const CBTDeviceArray& aArray);	///< Copy an array of devices
//Comparers
	IMPORT_C TBool operator==(const CBTDevice& aDevice) const;
	IMPORT_C TBool operator!=(const CBTDevice& aDevice) const;
	IMPORT_C TInt CompareTo(const CBTDevice& aDevice) const;	///< Compares two devices. Returns a bit field (values of TBTDeviceComparisonResult) describing the similarities.
	IMPORT_C TInt SizeOffJuice( void );		//Returns size of info for Externalise Juice
//Internalize/externalize
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	///< Externalize a device to a stream
	IMPORT_C void InternalizeL(RReadStream& aStream);			///< Internalize a device from a stream

//	BUGBUG
//	IMPORT_C void ExternalizeJuiceL(RWriteStream& aStream) const;	///<Externalize a device to a stream ( minimum info)
//	IMPORT_C void InternalizeJuiceL(RReadStream& aStream);			///<Internalize a device to a stream ( minimum info)

//Check to see if device data is valid (ie has been constructed)
	IMPORT_C TBool IsValidBDAddr() const;			///< Has the address of the device been set?
	IMPORT_C TBool IsValidDeviceName() const;		///< Has the name of the device been set?
	IMPORT_C TBool IsValidFriendlyName() const;		///< Has the friendly name of the device been set?
	IMPORT_C TBool IsValidDeviceClass() const;		///< Has the class of the device been set?
	IMPORT_C TBool IsValidLinkKey() const;			///< Has the link key of the device been set?
	IMPORT_C TBool IsValidGlobalSecurity() const;	///< Has the global service security setting been set?
	IMPORT_C TBool IsValidIndividualSecurity() const; ///< Have the individual service settings been set?
	
	IMPORT_C TBool IsValidPageScanRepMode() const;	///< Has the Page Scan Repitition mode been set?
	IMPORT_C TBool IsValidPageScanMode() const;		///< Has the Page Scan Mode been Set?	
	IMPORT_C TBool IsValidClockOffSet() const;		///< Has the clock off set been set?

private:
	CBTDevice();
	TInt LocateServiceInSecurityArrayL(TUid aUid) const;
public:
	/**Describes the similarities between two devices**/
	enum TBTDeviceComparisonResult
		{
		EBDAddr = 0x001,				  //000000000001
		EDeviceName = 0x002,			  //000000000010
		EFriendlyName = 0x004,			  //000000000100
		EDeviceClass = 0x008,			  //000000001000
		ELinkKey = 0x010,				  //000000010000
		EGlobalSecurity = 0x020,		  //000000100000
		EIndividualSecurityArray = 0x040, //000001000000
		EPageScanRepMode		 = 0x080, //000010000000
		EPageScanMode            = 0x100, //000100000000
		EClockOffSet			 = 0x200, //001000000000
		EAllTheSame				 = 0x3FF  //001111111111
		};
private:
	TBTDevAddr iBDAddr; 				///< The BT address of the remote device
	TBTDeviceName iDeviceName; 			///< The name given by the remote device
	TBTDeviceName iFriendlyName;		///< The friendly name provided by the user
	TBTDeviceClass iDeviceClass; 		///< The class(es) of the remote device
	TBTLinkKey iLinkKey;				///< The link key
	TInt iValidDataMask;				///< Bit mask indicating the data members that have been set
	TBTDeviceSecurity iGlobalSecurity;	///< The overall security criteria for all services which this device may wish to use
	CBTSecurityArray* iIndividualSecurity;	///< Individual security settings per Service for this device
	TUint32 iPageScanRepMode;				///< Page Scan repetition mode of remote device
	TUint32 iPageScanMode;					///< Page scan mode of remote device
	TUint32 iClockOffSet;					///< clock off set of remote device
	
	};




#endif
