// GSMUELEM.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

/**@file Gsmuelem.inl 
Inline methods for operations on PDU elements
*/

#include <s32strm.h>
#include <badesca.h>

inline void TGsmuLex8::LeaveL() const
/** Leaves with KErrGsmuDecoding */
	{
	User::Leave(KErrGsmuDecoding);
	}

inline TSmsOctet::TSmsOctet(TUint8 aValue)
: iValue(aValue)
/** Constructor, initialising the octet value with a TInt8.

@param aValue Octet value */
	{
	}

inline TSmsOctet::TSmsOctet(TInt aValue)
	:iValue(STATIC_CAST(TUint8, aValue))
/** Constructor, initialising the octet value with a TInt.

@param aValue Octet value */
	{
	}

inline void TSmsOctet::DecodeL(TGsmuLex8& aPdu)
/** Sets the octet value to the next byte in TGsmuLex8 PDU.

@param aPdu PDU to read value from */
	{
	iValue=aPdu.GetL();
	}

inline TSmsOctet::operator TInt() const
/**
@return The octet value
*/
	{
	return iValue;
	}

inline void TSmsOctet::FillSemiOctets(TInt aNum)
/** Converts an integer to semi-octet format and set the object's data to this 
value.

@param aNum Value to convert to semi-octet */
	{
	*this=(aNum/10)|((aNum%10)<<4);
	}

inline TInt TSmsOctet::SemiOctetsToNum() const
/** Converts a semi-octet value to an integer.

@return Object's data as an integer */
	{
	return ((iValue&0x0F)*10) + ((iValue&0xF0)>>4);
	}

inline void TSmsOctet::InternalizeL(RReadStream& aStream)
/** Internalises the object.

@param aStream Stream to read from */
	{
	aStream >> iValue;
	}

inline void TSmsOctet::ExternalizeL(RWriteStream& aStream) const
/** Externalises the object.

@param aStream Stream to write to */
	{
	aStream << iValue;
	}

inline TInt TSmsFailureCause::Error() const
/** Gets the error code.

@return Error code */
	{
	return iValue;
	}

inline void TSmsFailureCause::SetError(TSmsFailureCauseError aError)
/** Sets the error code.

@param aError Error code */
	{
	iValue=(TUint8) aError;
	}

TSmsStatus::TSmsStatusValue TSmsStatus::Status() const
/** Gets status value.

@return Status value */
	{
	return (TSmsStatusValue) iValue;
	}

inline void TSmsStatus::SetStatus(TSmsStatusValue aValue)
/** Sets status value.

@param aValue Status value */
	{
	iValue=(TUint8) aValue;
	}

inline TInt TSmsCommandType::CommandType() const
/** Gets command type.

@return Command type */
	{
	return iValue;
	}

inline void TSmsCommandType::SetCommandType(TSmsCommandTypeValue aType)
/** Sets command type.

@param aType Command type */
	{
	iValue=(TUint8) aType;
	}

inline TBool TSmsParameterIndicator::Extension() const
/**
Tests if the extension flag is set.

@return True if data contains a PID extension */
	{
	return iValue&ESmsPIDExtension;
	}

inline void TSmsParameterIndicator::SetExtension(TBool aExtension)
/** Sets extension flag.

@param aExtension Extension flag */
	{
	iValue=(TUint8) (aExtension? iValue|ESmsPIDExtension: (iValue&(~ESmsPIDExtension)));
	}

inline TBool TSmsParameterIndicator::UserDataPresent() const
/**
Tests user data present flag.

@return True if User Data is indicated */
	{
	return iValue&ESmsPIDUserDataPresent;
	}

inline void TSmsParameterIndicator::SetUserDataPresent(TBool aPresent)
/**
Sets user data present flag.

@param aPresent Set to True/False to indicate/clear User Data */
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDUserDataPresent: iValue&(~ESmsPIDUserDataPresent));
	}

inline TBool TSmsParameterIndicator::DataCodingSchemePresent() const
/** Tests data coding scheme present flag.

@return True to indicate Data Coding Scheme present */
	{
	return iValue&ESmsPIDDataCodingSchemePresent;
	}

inline void TSmsParameterIndicator::SetDataCodingSchemePresent(TBool aPresent)
/** Sets data coding scheme present flag.

@param aPresent Set to True/False to indicate/clear Data Coding Scheme present */
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDDataCodingSchemePresent: iValue&(~ESmsPIDDataCodingSchemePresent));
	}

inline TBool TSmsParameterIndicator::ProtocolIdentifierPresent() const
/** Tests protocol identifier present flag.

@return True to indicate Protocol ID present */
	{
	return iValue&ESmsPIDProtocolIdentifierPresent;
	}

inline void TSmsParameterIndicator::SetProtocolIdentifierPresent(TBool aPresent)
/** Sets protocol identifier present flag.

@param aPresent PSet to True/False to indicate/clear Protocol ID present */
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDProtocolIdentifierPresent: iValue&(~ESmsPIDProtocolIdentifierPresent));
	}

inline TSmsProtocolIdentifier::TSmsPIDType TSmsProtocolIdentifier::PIDType() const
/** Gets the Protocol ID type.

@return Protocol ID type */
	{
	return (TSmsPIDType) (iValue&ESmsPIDTypeMask);
	}

inline void TSmsProtocolIdentifier::SetPIDType(TSmsPIDType aSmsPIDType)
/** Sets the Protocol ID type.

@param aSmsPIDType Protocol ID type */
	{
	iValue=(TUint8) aSmsPIDType;
	}

inline TSmsDataCodingScheme::TSmsDCSBits7To4 TSmsDataCodingScheme::Bits7To4() const
/** Gets bits 7 - 4 of the Data Coding Scheme.

@return Bits 7 - 4 of the Data Coding Scheme */
	{
	return (TSmsDCSBits7To4) (iValue&ESmsDCSBits7To4Mask);
	}

inline void TSmsDataCodingScheme::SetBits7To4(TSmsDCSBits7To4 aBits7To4)
/** Sets bits 7 - 4 of the Data Coding Scheme.

@param aBits7To4 Bits 7 - 4 of the Data Coding Scheme */
	{
	iValue=(TUint8) (aBits7To4);
	}

inline TGsmSmsTypeOfAddress::TGsmSmsTypeOfAddress(TInt aValue)
: TSmsOctet(aValue)
/** Constructor, specifying an octet value.

@param aValue Octet value */
	{
	}

inline TGsmSmsTypeOfAddress::TGsmSmsTypeOfAddress(TGsmSmsTypeOfNumber aTon, TGsmSmsNumberingPlanIdentification aNPI)
: TSmsOctet(EGsmSmsFirstBitMask)
/** Constructor, specifying type of numbering and numbering plan identification.

@param aTon Type of numbering
@param aNPI Numbering plan identification */
	{
	SetTON(aTon);
	SetNPI(aNPI);
	}

inline TGsmSmsTypeOfNumber TGsmSmsTypeOfAddress::TON() const
/** Gets the type of numbering.

@return Type of numbering */
	{
	return (TGsmSmsTypeOfNumber) (iValue & EGsmSmsTONMask);
	}

inline void TGsmSmsTypeOfAddress::SetTON(TGsmSmsTypeOfNumber aTON)
/** Sets the type of numbering.

@param aTON Type of numbering */
	{
	iValue = (TUint8) ((iValue & (~EGsmSmsTONMask)) | aTON);	
	}

inline TGsmSmsNumberingPlanIdentification TGsmSmsTypeOfAddress::NPI() const
/** Gets the numbering plan identification.

@return Numbering plan identification */
	{
	return (TGsmSmsNumberingPlanIdentification) (iValue & EGsmSmsNPIMask);
	}

inline void TGsmSmsTypeOfAddress::SetNPI(TGsmSmsNumberingPlanIdentification aNumberingPlanIdentification)
/**
Set the Numbering Plan Identification */
	{
	iValue = (TUint8) ((iValue &(~EGsmSmsNPIMask)) | aNumberingPlanIdentification);
	}


inline TGsmSmsTelNumber::TGsmSmsTelNumber()
/**
Constructor
*/
	{
	}

inline TInt TSmsServiceCenterTimeStamp::TimeOffset() const
/** Gets the time zone offset from GMT in +/- quarter hours.

@return Time zone offset */
	{
	return iTimeZoneNumQuarterHours;
	}

inline const TTime& TSmsServiceCenterTimeStamp::Time() const
/** Gets the Service Center Time.

@return The Service Center Time */
	{
	return iTime;
	}

inline void TSmsServiceCenterTimeStamp::SetTime(const TTime& aTime)
/** Sets the Service Center Time.

@param aTime The Service Center Time */
	{
	iTime=aTime;
	}

inline TSmsFirstOctet::TSmsValidityPeriodFormat TSmsValidityPeriod::ValidityPeriodFormat() const
/** Gets the message Validity Period Format.

@return The message Validity Period Format */
	{
	return (TSmsFirstOctet::TSmsValidityPeriodFormat) (iFirstOctet&TSmsFirstOctet::ESmsVPFMask);
	}

inline void TSmsValidityPeriod::SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat)
/** Sets the message Validity Period Format.

@param aValidityPeriodFormat The message Validity Period Format */
	{
	iFirstOctet=(iFirstOctet&(~TSmsFirstOctet::ESmsVPFMask)|aValidityPeriodFormat);
	}

inline const TTimeIntervalMinutes& TSmsValidityPeriod::TimeIntervalMinutes() const
/** Gets the message Validity Period in minutes.

@return The message Validity Period in minutes */
	{
	return iTimeIntervalMinutes;
	}

inline void TSmsValidityPeriod::SetTimeIntervalMinutes(const TTimeIntervalMinutes& aTimeIntervalMinutes)
/** Sets the message Validity Period in minutes.

@param aTimeIntervalMinutes The message Validity Period in minutes */
	{
	iTimeIntervalMinutes=aTimeIntervalMinutes;
	}

inline void CSmsAlphabetConverter::ResetUnconvertedNativeCharacters()
/** Resets the unconverted native character buffer. */
	{
	iUnconvertedNativeCharactersPtr.Zero();
	}

inline void CSmsAlphabetConverter::ResetUnconvertedUDElements()
/** Resets the unconverted user data elements buffer. */
	{
	iUnconvertedUDElementsPtr.Zero();
	}

inline TPtrC CSmsAlphabetConverter::UnconvertedNativeCharacters()
/** Gets the unconverted native characters.

@return Unconverted native characters */
	{
	return iUnconvertedNativeCharactersPtr;
	}

inline TPtrC8 CSmsAlphabetConverter::UnconvertedUDElements()
/** Gets the unconverted user data elements.

@return Unconverted user data elements */
	{
	return iUnconvertedUDElementsPtr;
	}

inline TSmsDataCodingScheme::TSmsAlphabet CSmsAlphabetConverter::Alphabet() const
/** Gets the coding scheme alphabet.

@return Coding scheme alphabet */
	{
	return iSmsAlphabet;
	}


inline CSmsInformationElement::CSmsInformationElement(TSmsInformationElementIdentifier aInformationElementIdentifier):iIdentifier(aInformationElementIdentifier)
/**
@publishedAll
@released
*/
	{
	}
	
	
inline TInt CSmsUserData::NumInformationElements() const
/** Gets the number of information elements.

@return Number of information elements */
	{
	return iInformationElementArray.Count();
	}

inline TInt CSmsCommandData::NumInformationElements() const
/**
@return The number of Command Information Elements
@publishedAll
@released
*/
	{
	return iInformationElementArray.Count();
	}

inline TInt CSmsCommandData::MaxDataLength() const
/**
@return The amount of space in the Command buffer
@publishedAll
@released
*/
	{
	return KSmsMaxDataSize-iBuffer->Des().Length();
	}
