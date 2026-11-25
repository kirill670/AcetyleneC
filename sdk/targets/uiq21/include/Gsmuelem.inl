// GSMUELEM.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

/**
 * @file gsmuelem.inl Inline methods for operations on PDU elements
 *
 */

#include <s32strm.h>
#include <badesca.h>

inline void TGsmuLex8::LeaveL() const
/**
 * Leaves with KErrGsmuDecoding
 */
	{
	User::Leave(KErrGsmuDecoding);
	}

inline TSmsOctet::TSmsOctet(TUint8 aValue)
: iValue(aValue)
/**
 * Constructor Initialise class variables
 */
	{
	}

inline TSmsOctet::TSmsOctet(TInt aValue)
	:iValue(STATIC_CAST(TUint8, aValue))
/**
 * Constructor Initialise class variables
 */
	{
	}

inline void TSmsOctet::DecodeL(TGsmuLex8& aPdu)
/**
 * Sets this to the next byte in aPdu
 */
	{
	iValue=aPdu.GetL();
	}

inline TSmsOctet::operator TInt() const
/**
 * @return The octet value
 */
	{
	return iValue;
	}

inline void TSmsOctet::FillSemiOctets(TInt aNum)
/**
 * Convert an integer to semi-octet format and set TSmsOctet's data to this value
 *
 * @param aNum To convert to semi-octet
 */
	{
	*this=(aNum/10)|((aNum%10)<<4);
	}

inline TInt TSmsOctet::SemiOctetsToNum() const
/**
 * Convert semi-octet to integer
 *
 * @return TSmsOctet's data as an integer
 */
	{
	return ((iValue&0x0F)*10) + ((iValue&0xF0)>>4);
	}

inline void TSmsOctet::InternalizeL(RReadStream& aStream)
/**
 *
 * @param aStream The stream to internalize TSmsOctet's data to
 */
	{
	aStream >> iValue;
	}

inline void TSmsOctet::ExternalizeL(RWriteStream& aStream) const
/**
 *
 * @param aStream The stream to externalize TSmsOctet's from
 */
	{
	aStream << iValue;
	}

inline TInt TSmsFailureCause::Error() const
/**
 *
 * @return error code
 */
	{
	return iValue;
	}

inline void TSmsFailureCause::SetError(TSmsFailureCauseError aError)
/**
 *
 * @param aError To set error code
 */
	{
	iValue=(TUint8) aError;
	}

TSmsStatus::TSmsStatusValue TSmsStatus::Status() const
/**
 *
 * @return status value
 */
	{
	return (TSmsStatusValue) iValue;
	}

inline void TSmsStatus::SetStatus(TSmsStatusValue aValue)
/**
 *
 * @param aValue To set status value
 */
	{
	iValue=(TUint8) aValue;
	}

inline TInt TSmsCommandType::CommandType() const
/**
 *
 * @return command type
 */
	{
	return iValue;
	}

inline void TSmsCommandType::SetCommandType(TSmsCommandTypeValue aType)
/**
 *
 * @param aType To set command type
 */
	{
	iValue=(TUint8) aType;
	}

inline TBool TSmsParameterIndicator::Extension() const
/**
 *
 * @return True if data contains a PID extension
 */
	{
	return iValue&ESmsPIDExtension;
	}

inline void TSmsParameterIndicator::SetExtension(TBool aExtension)
/**
 *
 * @param aExtension To set a PID extension
 */
	{
	iValue=(TUint8) (aExtension? iValue|ESmsPIDExtension: (iValue&(~ESmsPIDExtension)));
	}

inline TBool TSmsParameterIndicator::UserDataPresent() const
/**
 *
 * @return True if User Data is indicated
 */
	{
	return iValue&ESmsPIDUserDataPresent;
	}

inline void TSmsParameterIndicator::SetUserDataPresent(TBool aPresent)
/**
 *
 * @param aPresent Set to True/False to indicate/clear User Data
 */
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDUserDataPresent: iValue&(~ESmsPIDUserDataPresent));
	}

inline TBool TSmsParameterIndicator::DataCodingSchemePresent() const
/**
 *
 * @return True to indicate Data Coding Scheme present
 */
	{
	return iValue&ESmsPIDDataCodingSchemePresent;
	}

inline void TSmsParameterIndicator::SetDataCodingSchemePresent(TBool aPresent)
/**
 *
 * @param aPresent Set to True/False to indicate/clear Data Coding Scheme present
 */
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDDataCodingSchemePresent: iValue&(~ESmsPIDDataCodingSchemePresent));
	}

inline TBool TSmsParameterIndicator::ProtocolIdentifierPresent() const
/**
 *
 * @return True to indicate Protocol ID present
 */
	{
	return iValue&ESmsPIDProtocolIdentifierPresent;
	}

inline void TSmsParameterIndicator::SetProtocolIdentifierPresent(TBool aPresent)
/**
 *
 * @param aPresent Set to True/False to indicate/clear Protocol ID present
 */
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDProtocolIdentifierPresent: iValue&(~ESmsPIDProtocolIdentifierPresent));
	}

inline TSmsProtocolIdentifier::TSmsPIDType TSmsProtocolIdentifier::PIDType() const
/**
 *
 * @return Protocol ID type
 */
	{
	return (TSmsPIDType) (iValue&ESmsPIDTypeMask);
	}

inline void TSmsProtocolIdentifier::SetPIDType(TSmsPIDType aSmsPIDType)
/**
 *
 * @param aSmsPidType To set to a Protocol ID type
 */
	{
	iValue=(TUint8) aSmsPIDType;
	}

inline TSmsDataCodingScheme::TSmsDCSBits7To4 TSmsDataCodingScheme::Bits7To4() const
/**
 *
 * @return Bits 7 - 4 of the Data Coding Scheme
 */
	{
	return (TSmsDCSBits7To4) (iValue&ESmsDCSBits7To4Mask);
	}

inline void TSmsDataCodingScheme::SetBits7To4(TSmsDCSBits7To4 aBits7To4)
/**
 *
 * @param aBits7To4 To set bits 7 - 4 of the Data Coding Scheme
 */
	{
	iValue=(TUint8) (aBits7To4);
	}

inline TGsmSmsTypeOfAddress::TGsmSmsTypeOfAddress(TInt aValue)
: TSmsOctet(aValue)
/**
 * Constructor
 */
	{
	}

inline TGsmSmsTypeOfAddress::TGsmSmsTypeOfAddress(TGsmSmsTypeOfNumber aTon, TGsmSmsNumberingPlanIdentification aNPI)
: TSmsOctet(EGsmSmsFirstBitMask)
/**
 *
 * @param aTon To set the Type of Numbering
 * @param aNPI To set the Numbering Plan Identification
 */
	{
	SetTON(aTon);
	SetNPI(aNPI);
	}

inline TGsmSmsTypeOfNumber TGsmSmsTypeOfAddress::TON() const
/**
 *
 * @return The Type Of Numbering
 */
	{
	return (TGsmSmsTypeOfNumber) (iValue & EGsmSmsTONMask);
	}

inline void TGsmSmsTypeOfAddress::SetTON(TGsmSmsTypeOfNumber aTON)
/**
 *
 * @param aTON To set the Type Of Numbering
 */
	{
	iValue = (TUint8) ((iValue & (~EGsmSmsTONMask)) | aTON);	
	}

inline TGsmSmsNumberingPlanIdentification TGsmSmsTypeOfAddress::NPI() const
/**
 * return the numbering plan identification
 */
	{
	return (TGsmSmsNumberingPlanIdentification) (iValue & EGsmSmsNPIMask);
	}

inline void TGsmSmsTypeOfAddress::SetNPI(TGsmSmsNumberingPlanIdentification aNumberingPlanIdentification)
/**
 * Set the Numbering Plan Identification
 */
	{
	iValue = (TUint8) ((iValue &(~EGsmSmsNPIMask)) | aNumberingPlanIdentification);
	}


inline TGsmSmsTelNumber::TGsmSmsTelNumber()
/**
 * Constructor
 */
	{
	}

inline TInt TSmsServiceCenterTimeStamp::TimeOffset() const
/**
 *
 * @return The time zone offset from GMT in +/- Quarter Hours
 */
	{
	return iTimeZoneNumQuarterHours;
	}

inline const TTime& TSmsServiceCenterTimeStamp::Time() const
/**
 *
 * @return The Service Center Time
 */
	{
	return iTime;
	}

inline void TSmsServiceCenterTimeStamp::SetTime(const TTime& aTime)
/**
 *
 * @param aTime To set the Service Center Time
 */
	{
	iTime=aTime;
	}

inline TSmsFirstOctet::TSmsValidityPeriodFormat TSmsValidityPeriod::ValidityPeriodFormat() const
/**
 *
 * @return The message Validity Period Format
 */
	{
	return (TSmsFirstOctet::TSmsValidityPeriodFormat) (iFirstOctet&TSmsFirstOctet::ESmsVPFMask);
	}

inline void TSmsValidityPeriod::SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat)
/**
 *
 * @param aValidityPeriod To set the message Validity Period Format
 */
	{
	iFirstOctet=(iFirstOctet&(~TSmsFirstOctet::ESmsVPFMask)|aValidityPeriodFormat);
	}

inline const TTimeIntervalMinutes& TSmsValidityPeriod::TimeIntervalMinutes() const
/**
 *
 * @return The message Validity Period in minutes
 */
	{
	return iTimeIntervalMinutes;
	}

inline void TSmsValidityPeriod::SetTimeIntervalMinutes(const TTimeIntervalMinutes& aTimeIntervalMinutes)
/**
 *
 * @param aTimeIntervalInMinutes To set the message Validity Period in minutes
 */
	{
	iTimeIntervalMinutes=aTimeIntervalMinutes;
	}

inline void CSmsAlphabetConverter::ResetUnconvertedNativeCharacters()
/**
 * Reset the Unconverted Native Character buffer
 */
	{
	iUnconvertedNativeCharactersPtr.Zero();
	}

inline void CSmsAlphabetConverter::ResetUnconvertedUDElements()
/**
 * Reset the Unconverted User Data Elements buffer
 */
	{
	iUnconvertedUDElementsPtr.Zero();
	}

inline TPtrC CSmsAlphabetConverter::UnconvertedNativeCharacters()
/**
 *
 * @return The Unconverted Native Characters
 */
	{
	return iUnconvertedNativeCharactersPtr;
	}

inline TPtrC8 CSmsAlphabetConverter::UnconvertedUDElements()
/**
 *
 * @return The Unconverted User Data Elements
 */
	{
	return iUnconvertedUDElementsPtr;
	}

inline TSmsDataCodingScheme::TSmsAlphabet CSmsAlphabetConverter::Alphabet() const
/**
 *
 * @return The Coding Scheme Alphabet
 */
	{
	return iSmsAlphabet;
	}


inline CSmsInformationElement::CSmsInformationElement(TSmsInformationElementIdentifier aInformationElementIdentifier):iIdentifier(aInformationElementIdentifier)
	{
	}
	
	
inline TInt CSmsUserData::NumInformationElements() const
/**
 *
 * @return The number of User Data Information Elements
 */
	{
	return iInformationElementArray.Count();
	}

inline TInt CSmsCommandData::NumInformationElements() const
/**
 *
 * @return The number of Command Information Elements
 */
	{
	return iInformationElementArray.Count();
	}

inline TInt CSmsCommandData::MaxDataLength() const
/**
 *
 * @return The amount of space in the Command buffer
 */
	{
	return KSmsMaxDataSize-iBuffer->Des().Length();
	}
