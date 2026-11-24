// GSMUMSG.INL
//
// Copyright (c) Symbian Software Ltd. 1999-2005.  All rights reserved.
//


/** @file
 */


inline CSmsPDU::TSmsPDUType CSmsMessage::Type() const
/** Gets the SMS-XXX message type.

@return SMS-XXX message type */
	{
	return iSmsPDU->Type();
	}

inline TBool CSmsMessage::IsComplete() const
/** Tests if the SMS message is complete.

@return True if complete */
	{
	return iFlags&ESmsFlagIsComplete;
	}

inline TBool CSmsMessage::IsDecoded() const
/** Tests if the SMS message is Decoded.

@return True if Decoded */
	{
	return iFlags&ESmsFlagIsDecoded;
	}

inline CSmsMessage::TMobileSmsStorage CSmsMessage::Storage() const
/** Gets the physical location where the message represented by the object is stored.

@return Physical location */
	{
	return (TMobileSmsStorage) (iFlags&ESmsStorageMask);
	}

inline void CSmsMessage::SetStorage(TMobileSmsStorage aStorage)
/** Sets the physical location where the message represented by the object is stored.

@param aStorage Physical location */
	{
	iFlags=aStorage|(iFlags&(~ESmsStorageMask));
	}

inline NMobileSmsStore::TMobileSmsStoreStatus CSmsMessage::Status() const
/** Gets the SMS store status of the message.

@return SMS store status */
	{
	return iStatus;
	}

inline void CSmsMessage::SetStatus(NMobileSmsStore::TMobileSmsStoreStatus aStatus)
/** Sets the SMS store status of the message.

@param aStatus SMS store status */
	{
	iStatus=aStatus;
	}

inline TInt CSmsMessage::LogServerId() const
/** Gets the Log Server Id.

@return Log Server Id */
	{
	return iLogServerId;
	}

inline void CSmsMessage::SetLogServerId(TInt aId)
/** Sets the Log Server Id.

@param aId Log Server Id */
	{
	iLogServerId=aId;
	}

inline const TTime& CSmsMessage::Time() const
/** Gets the time of message creation.

@return Time of message creation */
	{
	return iTime;
	}

inline void CSmsMessage::SetTime(const TTime& aTime)
/** Sets the time of message creation.

@param aTime Time of message creation */
	{
	iTime=aTime;
	}

inline CSmsPDU& CSmsMessage::SmsPDU()
/** Gets the message PDU.

@return PDU. */
	{
	return *iSmsPDU;
	}

inline const CSmsPDU& CSmsMessage::SmsPDU() const
/** Gets the message PDU (const).

@return PDU. */
	{
	return *iSmsPDU;
	}

inline TPtrC CSmsMessage::ServiceCenterAddress() const
/** Gets the message Service Center Address.

@return Service Center Address */
	{
	return iSmsPDU->ServiceCenterAddress();
	}

inline void CSmsMessage::SetServiceCenterAddressL(const TDesC& aAddress)
/** Sets the message Service Center Address.

@param aAddress Service Center Address */
	{
	iSmsPDU->SetServiceCenterAddressL(aAddress);
	}

inline void CSmsMessage::ParsedServiceCenterAddress(TGsmSmsTelNumber& aParsedAddress) const
/** Gets the Service Center Address as an ETSI-formatted telephone number.

@param aParsedAddress Service Center Address */
	{
	iSmsPDU->ParsedServiceCenterAddress(aParsedAddress);
	}

inline void CSmsMessage::SetParsedServiceCenterAddressL(const TGsmSmsTelNumber& aParsedAddress)
/** Sets the Service Center Address as an ETSI-formatted telephone number.

@param aParsedAddress Service Center Address */
	{
	iSmsPDU->SetParsedServiceCenterAddressL(aParsedAddress);
	}

inline TPtrC CSmsMessage::ToFromAddress() const
/** Gets unparsed To and From addresses.

@return To and From addresses */
	{
	return iSmsPDU->ToFromAddress();
	}

inline void CSmsMessage::SetToFromAddressL(const TDesC& aAddress)
/** Sets unparsed To and From addresses.

@param aAddress To and From addresses */
	{
	iSmsPDU->SetToFromAddressL(aAddress);
	}

inline void CSmsMessage::ParsedToFromAddress(TGsmSmsTelNumber& aParsedAddress) const
/** Gets To and From addresses in ETSI format.

@param aParsedAddress To and From addresses */
	{
	iSmsPDU->ParsedToFromAddress(aParsedAddress);
	}

inline void CSmsMessage::SetParsedToFromAddressL(const TGsmSmsTelNumber& aParsedAddress)
/** Sets To and From addresses in ETSI format.

@param aParsedAddress To and From addresses */
	{
	iSmsPDU->SetParsedToFromAddressL(aParsedAddress);
	}

inline CSmsBufferBase& CSmsMessage::Buffer()
/** Gets the text portion of the message (non-const).

@return Text portion of the message */
	{
	return *iBuffer;
	}

inline const CSmsBufferBase& CSmsMessage::Buffer() const
/**
@return The text portion of the CSmsMessage (const)
*/
	{
	return *iBuffer;
	}

inline void CSmsMessage::SetIsComplete(TBool aIsComplete)
/**
@param aIsComplete Set to True for CSmsMessage complete
*/
	{
	iFlags=aIsComplete? iFlags|ESmsFlagIsComplete: iFlags&(~ESmsFlagIsComplete);
	}

inline void CSmsMessage::SetIsDecoded(TBool aIsDecoded)
/**
@param aIsDecoded Set to True for CSmsMessage decoded
*/
	{
	iFlags=aIsDecoded? iFlags|ESmsFlagIsDecoded: iFlags&(~ESmsFlagIsDecoded);
	}

inline TBool CSmsMessage::BinaryData() const
/**
@return True if the User Data is Binary
*/
	{
	return iSmsPDU->UserData().IsBinaryData();
	}

inline void CSmsMessage::Set16BitConcatenation(TBool aIs16BitConcatenation)
	{
	iIs16BitConcatenation=aIs16BitConcatenation;
	}

inline TBool CSmsMessage::Is16BitConcatenation()const 
	{
	return iIs16BitConcatenation;
	}
