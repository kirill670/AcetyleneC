// bttypes.h
//
// Copyright (c) Symbian Software Ltd 1999-2004. All rights reserved.
//

//
// BT protocol wide types
//

#ifndef BTTYPES_H
#define BTTYPES_H

#include <e32std.h>


/**
@publishedAll
@released

Minimum eSCO connection latency in milliseconds.  Attempts to specify less than this will be silently
increased to this level.
*/
static const TInt KMinESCOLatency = 4;

/**
@publishedAll
@released

Typedef to represent a HCI connection handle.
*/
typedef TUint16 THCIConnHandle;

/**
@publishedAll
@released

Bluetooth SIG specified values for specification of (piconet) role.
*/
enum TBTBasebandRole
	{
	EMaster			= 0x00, /*!< Master role */
	ESlave			= 0x01, /*!< Slave role */
	ERoleUnknown,			/*!< Unknown role */
	};

/**
@publishedAll
@released

Bluetooth SIG specified values for indicating link modes.
*/
enum TBTLinkMode
    {
    EActiveMode		= 0x00, /*!< Active mode */
    EHoldMode		= 0x01, /*!< Hold mode */
    ESniffMode		= 0x02, /*!< Sniff mode */
    EParkMode		= 0x04, /*!< Park mode */
	EScatterMode	= 0x08, /*!< Scatter mode */
    };

/**
@publishedAll
@released

Typedef to represent a union of TBTLinkMode values.
*/
typedef TUint32 TBTLinkModeSet;

/**
@publishedAll
@released

Bitmask values to help request combinations of link modes.
@see TBTLinkMode
*/
enum TBTLinkModeCombinations
	{
	EAnyLowPowerMode = (EHoldMode | ESniffMode | EParkMode | EScatterMode) /*!< Any low power mode */
	};

/**
@publishedAll
@released

Bluetooth SIG specified values for indicating packet types.

DM1, DH1, DM3, DH3, DM5, DH5 are ACL packet types
HV1, HV2, HV3 are SCO (synchronous link) packet types
*/
enum TBTPacketType
	{
	EPacketsDM1			= 0x0008, /*!< DM1 ACL packet type */
	EPacketsDH1			= 0x0010, /*!< DH1 ACL packet type */
	EPacketsDM3			= 0x0400, /*!< DM3 ACL packet type */
	EPacketsDH3			= 0x0800, /*!< DH3 ACL packet type */
	EPacketsDM5			= 0x4000, /*!< DM5 ACL packet type */
	EPacketsDH5			= 0x8000, /*!< DH5 ACL packet type */

	EPacketsHV1			= 0x0020, /*!< HV1 SCO packet type */
	EPacketsHV2			= 0x0040, /*!< HV2 SCO packet type */
	EPacketsHV3			= 0x0080, /*!< HV3 SCO packet type */
	};

/**
@publishedAll
@released

Typedef to represent a set of SCO packet types.
*/
typedef TUint16 TBTSCOPackets;

/**
@publishedAll
@released

Typedef to represent a set of ACL packet types.
*/
typedef TUint16 TBTACLPackets;

/**
@publishedAll
@released

Bitmask values to help request combinations of packets.
@see TBTPacketType
*/
enum TBTPacketTypeCombinations
	{
	EAnyACLPacket	= EPacketsDM1 | EPacketsDM3 | EPacketsDM5 | EPacketsDH1 | EPacketsDH3 | EPacketsDH5, /*!< Any ACL packet */
	EAnySCOPacket	= EPacketsHV1 | EPacketsHV2 | EPacketsHV3, /*!< Any SCO packet */
	EAnyPacket		= EAnyACLPacket | EAnySCOPacket  /*!< Any packet */
	};


/**
@publishedAll
@released

Typedef to represent a set of synchronous packet types (SCO and eSCO on v1.2).
@see TBTSyncPackets::TSyncPackets
*/
typedef TUint32 TBTSyncPacketTypes;

/**
@publishedAll
@deprecated

This constant is no longer needed to translate the SCO mapping of HV packet types to Synchronous
because CBluetoothSynchronousLink::SetupConnection(const TBTDevAddr& aBDAddr, const TUint16 aPacketTypes)
adjusts aPacketTypes internally on behalf of clients.
*/
static const TInt KSCOvsSyncHVOffset = 5;

/**
@publishedAll
@released

Class to represent a set of synchronous packet types (SCO and eSCO on v1.2).
This differs from TBTSyncPacketTypes as it is the interface used by CBluetoothSynchronousLink
in order to detect the difference between a pre and post eSCO caller.  This is necessary
as HV1 packets in the SCO numbering clash with EV5 packets in the sync numbering.
*/
NONSHARABLE_CLASS(TBTSyncPackets)
	{
	public:
		/**
		@publishedAll
		@released
		
		Individual synchronous packet types.
		@see TBTSyncPacketTypes
		*/
		enum TSyncPackets
			{
			ESyncPacketsHV1		= 0x10001,
			ESyncPacketsHV2		= 0x10002,
			ESyncPacketsHV3		= 0x10004,

			ESyncPacketsEV3		= 0x20008,
			ESyncPacketsEV4		= 0x20010,
			ESyncPacketsEV5		= 0x20020,
			
			ESyncAnySCOPacket	= ESyncPacketsHV1 | ESyncPacketsHV2 | ESyncPacketsHV3,
			ESyncAnyESCOPacket	= ESyncPacketsEV3 | ESyncPacketsEV4 | ESyncPacketsEV5
			};
	
	public:
		IMPORT_C explicit TBTSyncPackets(TBTSyncPacketTypes aPackets);
		IMPORT_C TBTSyncPacketTypes operator()() const;
		
	private:
		TUint32 iPacketTypes;

		// This data padding has been added to help prevent future binary compatibility breaks	
		// Neither iPadding1 nor iPadding2 have been zero'd because they are currently not used
		TUint32     iPadding1; 
		TUint32     iPadding2; 		
	};


/**
@publishedAll
@released

eSCO links can have different retransmission options, optimised for link usage,
power or reliability.

@see CBluetoothSynchronousLink::SetRetransmissionEffort
*/
enum TBTeSCORetransmissionTypes
	{
	EeSCORetransmitNone			= 0,
	EeSCORetransmitPower		= 1,
	EeSCORetransmitReliability	= 2,
	EeSCORetransmitDontCare		= 0xff
	};

/**
@publishedAll
@released

eSCO unspecified bandwidth.  This value can only be used by the accepting side
of an eSCO link, to allow any bandwidth to be specified by the initiator.
Otherwise both sides of the link must agree on the same bandwidth.

@see CBluetoothSynchronousLink::SetBandwidth
@see CBluetoothSynchronousLink::AcceptConnection
*/
static const TUint32 KESCOBandwidthDontCare = KMaxTUint32;

/**
@internalTechnology
Size of featureset
*/
const TInt KBTHCIFeaturesBytes = 8;


/**
@internalTechnology

Bit positions of the individual local and remote features.
@see TBTFeatures
*/
enum TBTSupportedFeaturesBits
	{
	ESupportedThreeSlotPacketsBit				= 0,  /*!< Three slot packets are supported */
	ESupportedFiveSlotPacketsBit				= 1,  /*!< Five slot packets are supported */
	ESupportedEncryptionBit						= 2,  /*!< Encryption is supported */
	ESupportedSlotOffsetBit						= 3,  /*!< Slot offset is supported */
	ESupportedTimingAccuracyBit					= 4,  /*!< Timing accuracy is supported */
	ESupportedSwitchBit							= 5,  /*!< Role switch is supported */
	ESupportedHoldModeBit						= 6,  /*!< Hold mode is supported */
	ESupportedSniffModeBit						= 7,  /*!< Sniff mode is supported */
	ESupportedParkModeBit						= 8,  /*!< Park mode is supported */
	ESupportedRSSIBit							= 9,  /*!< Receive signal strength indication is supported */
	ESupportedChannelQualityDrivenDataRateBit	= 10, /*!< Channel quality driven data rate is supported */
	ESupportedSCOLinkBit						= 11, /*!< SCO links are supported */
	ESupportedHV2PacketsBit						= 12, /*!< HV2 packets are supported */
	ESupportedHV3PacketsBit						= 13, /*!< HV3 packets are supported */
	ESupportedu_lawLogBit						= 14, /*!< SCO u-law encoding is supported */
	ESupportedA_lawLogBit						= 15, /*!< SCO A-law encoding is supported */
	ESupportedCVSDBit							= 16, /*!< SCO Continuously variable slope delta modulation is supported */
	ESupportedPagingSchemeBit					= 17, /*!< Paging scheme is supported */
	ESupportedPowerControlBit					= 18, /*!< Power control is supported */
	ESupportedTransparentSCODataBit				= 19, /*!< Transparent SCO data is supported */
	ESupportedFlowControlLagBit0Bit				= 20, /*!< Flow control lag bit 0 is supported */
	ESupportedFlowControlLagBit1Bit				= 21, /*!< Flow control lag bit 1 is supported */
	ESupportedFlowControlLagBit2Bit				= 22, /*!< Flow control lag bit 2 is supported */
	ESupportedBroadcastEncryptionBit			= 23, /*!< Broadcast encryption is supported */
	
	EEDR_ACL_2MbpsModeBit						= 25, /*!< 2Mbps EDR ACL supported */
	EEDR_ACL_3MbpsModeBit						= 26, /*!< 3Mbps EDR ACL supported */
	ESupportedEnhancedEnquiryScanBit			= 27, /*!< Enhanced enquiry scan is supported */
	ESupportedInterlacedEnquiryScanBit			= 28, /*!< Interlaced enquiry scan is supported */
	ESupportedInterlacedPageScanBit				= 29, /*!< Interlaced page scan is supported */
	ESupportedRSSIWithInquiryResultsBit			= 30, /*!< Read signal strength indication with inquiry is supported */
	ESupportedExtendedSCOLinkBit				= 31, /*!< Extended SCO links are supported */
	ESupportedEV4PacketsBit						= 32, /*!< EV4 packets are supported */
	ESupportedEV5PacketsBit						= 33, /*!< EV5 packets are supported */
	
	ESupportedAFHCapableSlaveBit				= 35, /*!< Adaptive frequency hopping in slave role is supported */
	ESupportedAFHClassificationSlaveBit			= 36, /*!< Adaptive frequency hopping classification in slave role is supported */

	ESupportedEDRThreeSlotPacketsBit			= 39, /*!< Three slot EDR packets are supported */
	ESupportedEDRFiveSlotPacketsBit				= 40, /*!< Five slot EDR packets are supported */

	ESupportedAFHCapableMasterBit				= 43, /*!< Adaptive frequency hopping in master role is supported */
	ESupportedAFHClassificationMasterBit		= 44, /*!< Adaptive frequency hopping classification in master role is supported */
	EEDR_eSCO_2MbpsModeBit						= 45, /*!< 2Mbps EDR eSCO supported */
	EEDR_eSCO_3MbpsModeBit						= 46, /*!< 3Mbps EDR eSCO supported */
	ESupportedEDReSCOThreeSlotPacketsBit		= 47, /*!< Three slot EDR eSCO packets are supported */
	
	ESupportedExtendedFeaturesBit				= 63  /*!< Additional features are supported */
	};

/**
@publishedAll
@released

Bluetooth SIG specified values indicating whether a device
is physically able to support a baseband (or link manager protocol) feature
*/
enum TBTSupportedFeatures
	{
	ESupportedThreeSlotPackets				= 1<<0,  /*!< Three slot packets are supported */
	ESupportedFiveSlotPackets				= 1<<1,  /*!< Five slot packets are supported */
	ESupportedEncryption					= 1<<2,  /*!< Encryption is supported */
	ESupportedSlotOffset					= 1<<3,  /*!< Slot offset is supported */
	ESupportedTimingAccuracy				= 1<<4,  /*!< Timing accuracy is supported */
	ESupportedSwitch						= 1<<5,  /*!< Role switch is supported */
	ESupportedHoldMode						= 1<<6,  /*!< Hold mode is supported */
	ESupportedSniffMode						= 1<<7,  /*!< Sniff mode is supported */
	ESupportedParkMode						= 1<<8,  /*!< Park mode is supported */
	ESupportedRSSI							= 1<<9,  /*!< Receive signal strength indication is supported */
	ESupportedChannelQualityDrivenDataRate	= 1<<10, /*!< Channel quality driven data rate is supported */
	ESupportedSCOLink						= 1<<11, /*!< SCO links are supported */
	ESupportedHV2Packets					= 1<<12, /*!< HV2 packets are supported */
	ESupportedHV3Packets					= 1<<13, /*!< HV3 packets are supported */
	ESupportedu_lawLog						= 1<<14, /*!< SCO u-law encoding is supported */
	ESupportedA_lawLog						= 1<<15, /*!< SCO A-law encoding is supported */
	ESupportedCVSD							= 1<<16, /*!< SCO Continuously variable slope delta modulation is supported */
	ESupportedPagingScheme					= 1<<17, /*!< Paging scheme is supported */
	ESupportedPowerControl					= 1<<18, /*!< Power control is supported */
	ESupportedTransparentSCOData			= 1<<19, /*!< Transparent SCO data is supported */
	ESupportedFlowControlLagBit0			= 1<<20, /*!< Flow control lag bit 0 is supported */
	ESupportedFlowControlLagBit1			= 1<<21, /*!< Flow control lag bit 1 is supported */
	ESupportedFlowControlLagBit2			= 1<<22, /*!< Flow control lag bit 2 is supported */
	};

/**
@publishedAll
@released

Bitmask values for notifying/requesting notification of the state of a physical link.

These values have a two fold purpose:
1) They can be used along with TBTPhysicalLinkStateNotifierCombinations to specify
a set of baseband change events for which notification is desired.
2) They can be used to notify the state of a physical link or a subset of that state.
For example if only mode change events are being monitored, then at each mode change event
only the bit reperesenting the new mode will be returned, however if the whole link state
is required, then a combination of bit values indicating that state will be returned.

THESE BIT VALUES MUST ONLY BE USED WHEN REQUESTING NOTIFICATION, OR WHEN PARSING THE
RESULTS OF A NOTIFICATION. All other baseband state activities should use one of the 
appropriate Bluetooth SIG specified enums
@see TBTBasebandRole
@see TBTLinkMode
@see TBTLinkModeCombinations
@see TBTPacketType
@see TBTPacketTypeCombinations
*/
enum TBTPhysicalLinkStateNotifier
	{
	ENotifyMaster					= 0x00000001, /*!< Master */
	ENotifySlave					= 0x00000002, /*!< Slave */

	ENotifyActiveMode				= 0x00000004, /*!< Active mode */
	ENotifySniffMode				= 0x00000008, /*!< Sniff mode */
	ENotifyParkMode					= 0x00000010, /*!< Park mode */
	ENotifyHoldMode					= 0x00000020, /*!< Hold mode */

	ENotifyMaxSlots1				= 0x00000040, /*!< Max slots 1 */
	ENotifyMaxSlots3				= 0x00000080, /*!< Max slots 3 */
	ENotifyMaxSlots5				= 0x00000100, /*!< Max slots 5 */

	ENotifyPacketsDM1				= 0x00000200, /*!< Packets DM1 */
	ENotifyPacketsDH1				= 0x00000400, /*!< Packets DH1 */
	ENotifyPacketsDM3				= 0x00000800, /*!< Packets DM3 */
	ENotifyPacketsDH3				= 0x00001000, /*!< Packets DH3 */
	ENotifyPacketsDM5				= 0x00002000, /*!< Packets DM5 */
	ENotifyPacketsDH5				= 0x00004000, /*!< Packets DH5 */

	ENotifyPacketsHV1				= 0x00008000, /*!< HV1 */
	ENotifyPacketsHV2				= 0x00010000, /*!< HV2 */
	ENotifyPacketsHV3				= 0x00020000, /*!< HV3 */

	ENotifyAuthenticationComplete	= 0x00040000, /*!< Authentication Complete */
	ENotifyEncryptionChangeOn		= 0x00080000, /*!< Encryption Change On */
	ENotifyEncryptionChangeOff		= 0x00100000, /*!< Encryption Change Off */

	ENotifyPhysicalLinkUp			= 0x00200000, /*!< Physical Link Up */
	ENotifyPhysicalLinkDown			= 0x00400000, /*!< Physical Link Down */
	ENotifyPhysicalLinkError		= 0x00800000, /*!< Physical Link Error */

	ENotifySCOLinkUp				= 0x01000000, /*!< SCO Link Up */
	ENotifySCOLinkDown				= 0x02000000, /*!< SCO Link Down */
	ENotifySCOLinkError				= 0x04000000, /*!< SCO Link Error */

	};

/**
@publishedAll
@released

Bitmask values to help request notification of the state of a physical link.
@see TBTPhysicalLinkStateNotifier
*/
enum TBTPhysicalLinkStateNotifierCombinations
	{
	ENotifyAnyRole					= ENotifyMaster | ENotifySlave,
	ENotifyAnyLowPowerMode			= ENotifySniffMode | ENotifyParkMode | ENotifyHoldMode,
	ENotifyAnyPowerMode				= ENotifyActiveMode | ENotifyAnyLowPowerMode,
	ENotifyAnyMaxSlots				= ENotifyMaxSlots1 | ENotifyMaxSlots3 | ENotifyMaxSlots5,
	ENotifyAnyACLPacketType			= ENotifyPacketsDM1 | ENotifyPacketsDH1 | ENotifyPacketsDM3 | EPacketsDH3 | EPacketsDM5 | EPacketsDH5,
	ENotifyAnySCOPacketType			= ENotifyPacketsHV1 | ENotifyPacketsHV2 | ENotifyPacketsHV3,
	ENotifyAnyPacketType			= ENotifyAnyACLPacketType | ENotifyAnySCOPacketType,
	ENotifyAnyPhysicalLinkState		= 0xffffffff,
	};

/**
@publishedAll
@released

The maximum length of an SDP UUID.
*/
static const TInt KSdpUUIDMaxLength			= 16;

/**
@publishedAll
@released

The size of a bluetooth device address in bytes.
*/
const TInt KBTDevAddrSize=0x06;

/**
@publishedAll
@released

The size of a bluetooth device address in bytes.
*/
const TInt KBTMaxDevAddrSize = KBTDevAddrSize;

/**
@publishedAll
@released

48-bit bluetooth device address.
Each bluetooth device has a unique address built into the hardware, which
is represented by this class. Used for identifying remote addresses.
The interface operates in a big-endian manner -- e.g. addr[0] refers
to the most significant byte of the address. This is the same ordering
as the addresses would naturally be written down on paper.
**/
NONSHARABLE_CLASS(TBTDevAddr)
    {
public:
    IMPORT_C TBTDevAddr();
    IMPORT_C TBTDevAddr(const TInt64 &aInt);
    IMPORT_C TBTDevAddr(const TDesC8 &aDes);
    IMPORT_C TBool operator==(const TBTDevAddr& aAddr) const;
    IMPORT_C TBool operator!=(const TBTDevAddr& aAddr) const;
	IMPORT_C const TUint8 &operator[](TInt aIndex) const;
	IMPORT_C TUint8 &operator[](TInt aIndex);
	IMPORT_C void Reset();
	IMPORT_C TPtr8 Des();
	IMPORT_C const TPtrC8 Des() const;
	IMPORT_C TInt SetReadable(const TDesC& aSource);
	IMPORT_C void GetReadable(TDes& aDest) const;
	IMPORT_C void GetReadable(TDes& aDest, const TDesC& aPrepend, const TDesC& aByteSeperator, const TDesC& aAppend) const;
    IMPORT_C TBool operator<=(const TBTDevAddr& aAddr) const;
private:
	TFixedArray<TUint8, KBTDevAddrSize> iAddr;

	// This data padding has been added to help prevent future binary compatibility breaks	
	// iPadding hasn't been zero'd because it is currently not used
	TUint16     iPadding; 			
    };

/**
@publishedAll
@released

A Bluetooth Universally Unique Identifier.

This is a 128-bit quantity that can be created without a central registry 
while still being globally unique.
UUIDs are always held in full 128 bit format, however they can be set from 
BT SIG short form (16 or 32 bit) addresses, and returned as down to their 
shortest form using ShortestForm().
**/
NONSHARABLE_CLASS(TUUID)
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
	IMPORT_C const TPtrC8 FixedLengthL(TInt aLength) const;
	IMPORT_C TInt MinimumSize() const;
    IMPORT_C TBool operator==(const TUUID& aUUID) const;
    IMPORT_C TBool operator!=(const TUUID& aUUID) const;
	IMPORT_C const TUint8 &operator[](TInt aIndex) const;
	IMPORT_C TUint8 &operator[](TInt aIndex);
private:
	TFixedArray<TUint8, KSdpUUIDMaxLength> iUUID;	

	// This data padding has been added to help prevent future binary compatibility breaks	
	// Neither iPadding1 nor iPadding2 have been zero'd because they are currently not used
	TUint32     iPadding1; 
	TUint32     iPadding2; 			
	};

/**
@publishedAll
@released

The size of a link key, in bytes.
*/
const TUint8 KHCILinkKeySize=16;

/**
@publishedAll
@released

The size of a pin code, in bytes.
*/
const TUint8 KHCIPINCodeSize=16;

/**
@publishedAll
@released

Link key structure.
*/
NONSHARABLE_CLASS(TLinkKeyV10)
    {
public:
    TUint8 iLinkKey[KHCILinkKeySize]; /*!< The link key */
    };

/**
@publishedAll
@released

Typedef'ed TPckgBuf of the class TLinkKeyV10.
*/
typedef TPckgBuf<TLinkKeyV10> TBTLinkKey;

/**
@publishedAll
@released

Link key structure.
*/
NONSHARABLE_CLASS(TPINCodeV10)
    {
public:
    TUint8 iLength; /*!< The length of the pin key */
    TUint8 iPIN[KHCIPINCodeSize]; /*!< The pin code */
    };

/**
@publishedAll
@released

Typedef'ed TPckgBuf of the class TPINCodeV10.
*/
typedef TPckgBuf<TPINCodeV10> TBTPinCode;


/**
@publishedAll
@released

Contains information resulting from a baseband notification.
*/
NONSHARABLE_CLASS(TBTBasebandEventNotification)
	{
public:
	/** 
	Constructor.
	@param aEventType The type of event.
	@param aErrorCode The error code.
	*/
	TBTBasebandEventNotification(TUint32 aEventType, TInt aErrorCode = KErrNone) : iEventType(aEventType), iErrorCode(aErrorCode) {};

	/**
	Default constructor.
	*/
	TBTBasebandEventNotification() : iEventType(0), iErrorCode(KErrNone) {};

	/**
	Copy constructor.
	@param aEvent The event to copy.
	*/
	TBTBasebandEventNotification(const TBTBasebandEventNotification& aEvent) : iEventType(aEvent.iEventType), iErrorCode(aEvent.iErrorCode) {};

	/**
	The event type.
	@return The event type.
	*/
	TUint32 EventType() const	{ return iEventType; };

	/**
	The Bluetooth SIG error code associated with the event.
	@return The SIG error code.
	*/
	TInt ErrorCode() const		{ return iErrorCode; };

	/**
	The Symbian HCI error code associated with the event.
	@return The Symbian error code.
	*/
	IMPORT_C TInt SymbianErrorCode() const;

	/**
	Set the event type.
	@param aEventType The event type.
	*/
	void SetEventType(TUint32 aEventType)	{ iEventType = aEventType; };

	/**
	Set the error code.
	@param aErrorCode The Bluetooth SIG error code.
	*/
	void SetErrorCode(TInt aErrorCode)		{ iErrorCode = aErrorCode; };

private:
	TUint32 iEventType;
	TInt iErrorCode;
	};

/**
@publishedAll
@released

Typedef'ed pckgbuf of the class TBTBasebandEventNotification.
*/
typedef TPckgBuf<TBTBasebandEventNotification> TBTBasebandEvent;

/**
@publishedAll
@released

General Unlimited Inquiry Access Code
*/
const TUint KGIAC=0x9e8b33;

/**
@publishedAll
@released

Limited Inquiry Access Code
*/
const TUint KLIAC=0x9e8b00;


/**
@publishedAll
@released

API class for setting up an L2Cap configuration

This class may be used to set all or a subset of the following configuration items:
Channel Reliability (and associated timer)
Maximum Transmission Unit
Maximum Receive Unit
Channel Priority

If a configuration item is to be set, then its 'Set' or 'Setup'
method should be called.

Once a TL2CapConfig object has been set up it should be sent using
RSocket::SetOption or RSocket::Ioctl (or the CBluetoothSocket) equivalents.

@see RSocket
@see CBluetoothSocket
*/
NONSHARABLE_CLASS(TL2CapConfig)
	{
public:
	/**	
	Priority required for data on L2Cap channel
	*/
	enum TChannelPriority
		{
		EHigh		= 2,
		EMedium		= 1,
		ELow		= 0,
		};

	/**	
	Reliability of data tranfer required for L2Cap channel
	*/
	enum TChannelReliability
		{
		EReliableChannel,
		EUnreliableChannel,
		};	

	/**	
	Timer values in milliseconds for reliable and unreliable channels
	*/
	enum TL2CapConfigSpecifiedTimers
		{
		/**
		This is a time in milliseconds. However 0xffff has been given a special meaning 
		in this interface. It means	"Allow up 256 transmissions of a single packet before 
		giving up and disconnecting the L2Cap channel.". This is the maximum number of
		transmissions effectively allowed by the spec.
		*/
		EDefaultRetransmission = 0xffff,
		/**
		Minimum data obsolescence timeout required because data packets 
		will not ever be sent if we flush them too quickly.
		Speed of sending data depends on how many channels are open and channel priority.
		*/
		EMinDataObsolescenceTimeout = 0x0a,
		/**
		This is translated to mean never flush (as per spec).
		*/
		EDefaultDataObsolescenceTimeout = 0xffff, 
		};	

	/**	
	Used to indicate which config options have been specified by the user
	*/
	enum TL2CapConfigSpecifiedMask
		{
		ENoConfigElementsSpecified			= 0x0000,
		EMTUSizeSpecifiedMask				= 0x0001,
		EMRUSizeSpecifiedMask				= 0x0002,
		EReliabilitySpecifiedMask			= 0x0004,
		EPrioritySpecifiedMask				= 0x0008,
		};
		
	IMPORT_C TL2CapConfig();

	IMPORT_C TInt SetMaxTransmitUnitSize(TUint16 aSize = 0xffff);
	IMPORT_C TUint16 MaxTransmitUnitSize(TBool& aIsSpecified) const;
	IMPORT_C TInt SetMaxReceiveUnitSize(TUint16 aSize = 0xffff);
	IMPORT_C TUint16 MaxReceiveUnitSize(TBool& aIsSpecified) const;

	IMPORT_C TInt ConfigureReliableChannel(TUint16 aRetransmissionTimer);
	IMPORT_C TInt ConfigureUnreliableChannel(TUint16 aObsolescenceTimer);
	IMPORT_C TChannelReliability ChannelReliability(TBool& aIsSpecified, TUint16& aAssociatedTimer) const;
	
	IMPORT_C TInt ConfigureChannelPriority(TChannelPriority aPriority);
	IMPORT_C TChannelPriority ChannelPriority(TBool& aIsSpecified) const;
	
	/**
	@deprecated
	Use ConfigureReliableChannel(TUint16 aRetransmissionTimer) instead
	*/
	IMPORT_C TInt SetupReliableChannel(TUint16 aRetransmissionTimer = EDefaultRetransmission);
	/**
	@deprecated
	Use ConfigureUnreliableChannel(TUint16 aObsolescenceTimer) instead
	*/
	IMPORT_C TInt SetupUnreliableChannel(TUint16 aObsolescenceTimer = EDefaultDataObsolescenceTimeout);
	/**
	@deprecated
	Use ConfigureChannelPriority(TChannelPriority aPriority) instead
	*/
	IMPORT_C TInt SetChannelPriority(TChannelPriority aPriority = ELow);
		
private:
	TUint16 iMTUSize;
	TUint16 iMRUSize;
	TChannelReliability iChannelReliability;
	TUint16	iChannelReliabilityTimer;
	TChannelPriority iChannelPriority;
	TUint16 iSpecifiedMask;

	// This data padding has been added to help prevent future binary compatibility breaks
	// Neither iPadding1 nor iPadding2 have been zero'd because they are currently not used	
	TUint32     iPadding1; 
	TUint32     iPadding2; 
	};

/**
@publishedAll
@released

Typedef to represent a L2CAP Config object.
*/
typedef TPckgBuf<TL2CapConfig> TL2CapConfigPkg;

#endif
