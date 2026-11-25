///////////////////////////////////////////////////////////////////////////////
//
// SMUTHDR.INL
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "smcmmain.h"
#include <gsmumsg.h>

inline CSmsSubmit& CSmsHeader::Submit()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsSubmit, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsSubmit&)(iMessage->SmsPDU());
	}

inline const CSmsSubmit& CSmsHeader::Submit() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsSubmit, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsSubmit&)(iMessage->SmsPDU());
	}

inline CSmsDeliver& CSmsHeader::Deliver()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsDeliver, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsDeliver&)(iMessage->SmsPDU());
	}

inline const CSmsDeliver& CSmsHeader::Deliver() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsDeliver, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsDeliver&)(iMessage->SmsPDU());
	}

inline CSmsCommand& CSmsHeader::Command()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsCommand, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsCommand&)(iMessage->SmsPDU());
	}

inline const CSmsCommand& CSmsHeader::Command() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsCommand, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsCommand&)(iMessage->SmsPDU());
	}

inline CSmsStatusReport& CSmsHeader::StatusReport()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsStatusReport, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsStatusReport&)(iMessage->SmsPDU());
	}

inline const CSmsStatusReport& CSmsHeader::StatusReport() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsStatusReport, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsStatusReport&)(iMessage->SmsPDU());
	}

inline CSmsPDU::TSmsPDUType CSmsHeader::Type() const
	{
	return iMessage->SmsPDU().Type();
	}

inline const CArrayPtrFlat<CSmsNumber>& CSmsHeader::Recipients() const
	{
	return iRecipients;
	}

inline CArrayPtrFlat<CSmsNumber>& CSmsHeader::Recipients()
	{
	return iRecipients;
	}

inline CSmsMessage& CSmsHeader::Message()
	{
	return *iMessage;
	}
	
inline const CSmsMessage& CSmsHeader::Message() const
	{
	return *iMessage;
	}

inline TBool CSmsHeader::ReplyPathProvided() const
	{
	return iFlags & ESmsHeaderReplyPathProvided;
	}

inline void CSmsHeader::SetReplyPathProvided(TBool aReplyPathProvided)
	{
	iFlags = (iFlags & ~ESmsHeaderReplyPathProvided) | (aReplyPathProvided ? ESmsHeaderReplyPathProvided : ESmsHeaderNoFlags);
	}

inline void CSmsHeader::SetFromAddressL(const TDesC& aAddress)
	{
	Message().SmsPDU().SetToFromAddressL(aAddress);
	}

inline TPtrC CSmsHeader::FromAddress() const
	{
	switch(Type())
		{
		case(CSmsPDU::ESmsSubmit):
										return Submit().ToFromAddress();
		case(CSmsPDU::ESmsDeliver):
										return Deliver().ToFromAddress();
		default: 
										return TPtrC(0,0);
		}
	}

inline TPtrC CSmsHeader::ServiceCenterAddress() const
	{
	return Submit().ServiceCenterAddress();
	}

inline void CSmsHeader::SetServiceCenterAddressL(const TDesC& aAddress)
	{
	Submit().SetServiceCenterAddressL(aAddress);
	}
/*
inline void CSmsHeader::ParsedServiceCenterAddress(TGsmSmsTelNumber& aParsedAddress) const
	{
	Submit().ParsedServiceCenterAddress(aParsedAddress);
	}

inline void CSmsHeader::SetParsedServiceCenterAddressL(const TGsmSmsTelNumber& aParsedAddress)
	{
	Submit().SetParsedServiceCenterAddressL(aParsedAddress);
	}
*/
inline TBioMsgIdType CSmsHeader::BioMsgIdType() const
	{
	return iBioMsgIdType;
	}

inline void CSmsHeader::SetBioMsgIdType(TBioMsgIdType aBioMsgIdType)
	{
	iBioMsgIdType = aBioMsgIdType;
	}

// TMsvSmsEntry

inline TMsvSmsEntry::TMsvSmsEntry()
	{
	}

inline TMsvSmsEntry::TMsvSmsEntry(const TMsvEntry& aEntry)  : TMsvEntry(aEntry)
	{
	}

inline void TMsvSmsEntry::SetUserPromptIndicator(TBool aUPI)
	{
	(aUPI) ? (iMtmData2 |= EMsvSmsEntryUserPromptIndicator) : (iMtmData2 &= ~EMsvSmsEntryUserPromptIndicator);
	}

inline TBool TMsvSmsEntry::UserPromptIndicator() const
	{
	return (iMtmData2 & EMsvSmsEntryUserPromptIndicator);
	}

inline TUint8 TMsvSmsEntry::ProtocolIdentifier() const
	{
	return STATIC_CAST(TUint8, iMtmData2 & EMsvSmsEntryProtocolIdentifier);
	}

inline void TMsvSmsEntry::SetProtocolIdentifier(TSmsProtocolIdentifier aPID)
	{
	SetProtocolIdentifier(STATIC_CAST(TUint8, aPID));
	}

inline void TMsvSmsEntry::SetProtocolIdentifier(TUint8 aPID)
	{
	iMtmData2 = (iMtmData2 & ~EMsvSmsEntryProtocolIdentifier) | (aPID & EMsvSmsEntryProtocolIdentifier);
	}

inline void TMsvSmsEntry::SetClass(TBool aClassDefined, TSmsDataCodingScheme::TSmsClass aClass)
	{
	aClassDefined ? (iMtmData2 |= EMsvSmsEntryClassDefined) : (iMtmData2 &= ~EMsvSmsEntryClassDefined);
	iMtmData2 = (iMtmData2 & ~EMsvSmsEntryClass) | ((aClass << EMsvSmsEntryClassShift) & EMsvSmsEntryClass);
	}

inline TBool TMsvSmsEntry::Class(TSmsDataCodingScheme::TSmsClass& aClass) const
	{
	aClass = STATIC_CAST(TSmsDataCodingScheme::TSmsClass, ((iMtmData2 & EMsvSmsEntryClass) >> EMsvSmsEntryClassShift));
	return iMtmData2 & EMsvSmsEntryClassDefined;
	}
