// GSMUMSG.H
//
// Copyright (c) 1999-2003 Symbian Ltd.  All rights reserved.
// 

/**@file gsmumsg.h  
This file defines the class CSmsMessage
*/

#ifndef __GSMUMSG_H__
#define __GSMUMSG_H__


#include <f32file.h>
#include <etelmm.h>
#include "gsmuetel.h"
#include <charconv.h>
#include "gsmupdu.h"

#include "EMSInformationElement.h"

/**
@internalComponent
*/
const TUint IoctlWriteSMSBufferSize = 256;

class CSmsBufferBase;
class CSmsCompressedBuffer;
class TSmsUserDataSettings;
class CSmsEMSBufferSegmenter;
class CGsmCompressionBase;
class CEmsUserPrompt;
class CEmsObjectDistribution;

class TGsmSmsSlot : public RMobileSmsStore::TMobileGsmSmsEntryV1
/**
@internalComponent
*/
	{
public:
	IMPORT_C  TGsmSmsSlot();
	IMPORT_C  TGsmSmsSlot(const RMobileSmsStore::TMobileGsmSmsEntryV1& aSmsEntry);
public:
	RMobilePhone::TMobileName iStore; ///< Name of the store where slot is
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	};

class CSmsMessage : public CBase
/** Represents a complete SMS message.

This class can:

Internalise and externalise its data

Encode/decode itself to/from one or more SMS PDU's

SMS Message Data is stored in the CSmsBufferBase iBuffer. SMS Message Settings 
are stored in the CSmsPDU iSmsPDU.
@publishedAll
@released */
	{
public:
/** User data optimisation flags. */
	enum TSmsOptimizationFlags
		{
	/** The alphabet flag causes an alphabet to be chosen which preserves information 
	in the message and makes the number of PDUs as small as possible. */
		ESmsFlagOptimizeAlphabet=0x01,
	/** 8-bit referenced concatenation.
	
	This causes compression to be switched off and if the message length is greater 
	than the maximum message length, concatenation is switched on. */
		ESmsFlagOptimizeConcatenation=0x08,
	/** 16-bit referenced concatenation.
	
	This causes compression to be switched off and if the message length is greater 
	than the maximum message length, concatenation is switched on. */
		ESmsFlagOptimizeConcatenation16BitReference=0x10,
		};

/** Flags that indicate whether a message is stored. */
	enum TMobileSmsStorage
		{
	/** No storage. */
		ESmsNoStorage=0x00,
	/** SIM storage. */
		ESmsSIMStorage=0x04,
	/** Phone storage. */
		ESmsPhoneStorage=0x08,
	/** Combined storage. */
		ESmsCombinedStorage=0x0C
		};
public:
	IMPORT_C static CSmsMessage* NewL(RFs& aFs, const TGsmSms& aGsmSms,CSmsBufferBase* aBuffer, TBool aIsRPError=EFalse,TBool aIsMobileTerminated=ETrue);
	IMPORT_C static CSmsMessage* NewL(RFs& aFs, CSmsPDU::TSmsPDUType aType,CSmsBufferBase* aBuffer,TBool aIsRPError=EFalse);
	IMPORT_C ~CSmsMessage();

	inline CSmsPDU::TSmsPDUType Type() const;
	inline TBool IsComplete() const;
	inline TBool IsDecoded() const;
	inline TMobileSmsStorage Storage() const;
	inline void SetStorage(TMobileSmsStorage aStorage);
	inline RMobileSmsStore::TMobileSmsStoreStatus Status() const;
	inline void SetStatus(RMobileSmsStore::TMobileSmsStoreStatus aStatus);
	inline TInt LogServerId() const;
	inline void SetLogServerId(TInt aId);
	inline const TTime& Time() const;
	inline void SetTime(const TTime& aTime);

	inline CSmsPDU& SmsPDU(); 
	inline const CSmsPDU& SmsPDU() const; 

	inline TPtrC ServiceCenterAddress() const;
	inline void SetServiceCenterAddressL(const TDesC& aAddress);
	inline void ParsedServiceCenterAddress(TGsmSmsTelNumber& aParsedAddress) const;
	inline void SetParsedServiceCenterAddressL(const TGsmSmsTelNumber& aParsedAddress);

	inline TPtrC ToFromAddress() const;
	inline void SetToFromAddressL(const TDesC& aAddress);
	inline void ParsedToFromAddress(TGsmSmsTelNumber& aParsedAddress) const;
	inline void SetParsedToFromAddressL(const TGsmSmsTelNumber& aParsedAddress);

	IMPORT_C void InternalizeWithoutBufferL(RReadStream& aStream);
	IMPORT_C void ExternalizeWithoutBufferL(RWriteStream& aStream) const;

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

	inline CSmsBufferBase& Buffer();
	inline const CSmsBufferBase& Buffer() const;

//  Functions related to encoding/decoding the text buffer
	IMPORT_C TBool TextPresent() const;
	IMPORT_C TInt NumMessagePDUsL();
	IMPORT_C TInt MaxMessageLength() const;
	IMPORT_C TInt MessageLengthL();

	IMPORT_C void UserDataSettings(TSmsUserDataSettings& aSettings) const;
	IMPORT_C void SetUserDataSettingsL(const TSmsUserDataSettings& aSettings);
	IMPORT_C void OptimizeSettingsL(TInt aOptions);

	IMPORT_C TBool IsSupportedL(const TDesC& aDes,TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstUnconvertibleCharacter);

	IMPORT_C void EncodeMessagePDUsL(CArrayFix<TGsmSms>& aSmsArray, TInt aReference=0);
	IMPORT_C void DecodeMessagePDUsL(const CArrayFix<TGsmSms>& aSmsArray);
	IMPORT_C const RPointerArray<const CEmsInformationElement>& GetEMSInformationElementsL()const;
	IMPORT_C void AddEMSInformationElementL(const CEmsInformationElement& aEmsIE);			
	IMPORT_C RPointerArray<CEmsInformationElement>* RemoveEMSInformationElementsL(const TUint aStartPosition,const TSmsId aEmsId);
	IMPORT_C CEmsInformationElement* RemoveEMSInformationElementL(const TUint aStartPosition,const TSmsId aEmsId);	
	IMPORT_C void ResetEMSL();
	IMPORT_C TBool EncodeIntoSinglePDUL(CArrayFix<TGsmSms>& aSmsArray);
	IMPORT_C void CopyEmsElementsL(CSmsMessage& aToMessage) const;
	IMPORT_C void AddSlotL(const TGsmSmsSlot& aSlot);
	IMPORT_C TBool MatchSlots(const CArrayFixFlat<TGsmSmsSlot>& aSlotArray);
// E-mail header 
 	IMPORT_C void AddEmailHeaderL(const TDesC& aEmailHeader,const TDesC& aEmailBody);
 	IMPORT_C TBool IsEmailHeader() const;
 	IMPORT_C TBool GetEmailHeaderL(HBufC** aEmailHeader,HBufC** aEmailBody);
 	void InstallEmailHeaderInformationElementL(CSmsUserData& aUserData,TInt& aHeaderLength);
 	void InstallEmailHeaderInformationElementL(CSmsCommand& aCommand,TInt& aHeaderLength);
	inline void Set16BitConcatenation(TBool aIs16BitConcatenation);
	inline TBool Is16BitConcatenation()const;
	IMPORT_C void UpdateSlotsL(TDesC8& aBuf);

private:
	
	CSmsMessage(RFs& aFs, CSmsBufferBase* aBuffer);
	void ConstructL(const TGsmSms& aGsmSms, TBool aIsRPError,TBool aIsMobileTerminated);
	void ConstructL(CSmsPDU::TSmsPDUType aType,TBool aIsRPError);

	inline void SetIsComplete(TBool aIsComplete);
	inline void SetIsDecoded(TBool aIsDecoded);
	

	inline TBool BinaryData() const;
	TInt ConvertedBufferLengthL(const CSmsBufferBase& aBuffer);			
	void EncodeBufferL(CArrayFix<TGsmSms>& aSmsArray,TInt aReference,const CSmsBufferBase& aBuffer,TBool aDoEncode=ETrue);
	void DecodeBufferL(CArrayPtr<CSmsPDU>& aSmsPDUArray,CSmsBufferBase& aBuffer);
	void InstallEmsInformationElementsL(CSmsUserData& aUserData, TInt aStartPosition);
	void InstallEmsInformationElementsL(CSmsCommand& aCommand, TInt aStartPosition);
	TBool AddEMSInformationElementsToMultiSegmentMessageL(CArrayFix<TGsmSms>& aSmsArray,CSmsEMSBufferSegmenter& aSegmenter,TUint& aCharsAdded,TBool aDoEncode,RPointerArray<CEmsInformationElement>& aCorrectedFormatingIEArray,TUint& aCurEMSIEno,TUint& aBaseAddr);
	TBool AddEMSInformationElementsToSingleSegmentMessageL(CSmsEMSBufferSegmenter& aSegmenter);	
	void AddCurrentPDUToSmsArrayL(CArrayFix<TGsmSms>& aSmsArray,TBool aDoEncode);
	TBool AddIEToUserDataL(CEmsInformationElement* aIe, TInt aCharsAlreadyAdded,TUint& aCharsAddedToCurrentPDU,CSmsEMSBufferSegmenter& aSeg);
	TInt FillPduL(CSmsEMSBufferSegmenter& aSeg, TInt aNumChars);
	TInt NumMessageEmsPDUsL();
	void CorrectFormattingL(TUint aCharsAddedToCurrentPDU,RPointerArray<CEmsInformationElement>& aCorrectedFormatingIEArray,TUint aBaseAddr);
	void CorrectFormattingInSinglePDUL();
	void ResetWorkingPDUL();
	TBool CanBeRemoved(const CEmsInformationElement& aIE, TUint aIEIndex);
	void AddEmsUserPromptL(const CEmsUserPrompt& aEmsIE);
	void AddEmsObjectDistributionL(const CEmsObjectDistribution& aObjectDistributionIE);
	void UpdateUserPromptAndODIElementsStartPosition();
	TInt AddReceivedEmsInformationElement(CEmsInformationElement* aIE);
 	
private:
	enum TSmsMessageFlags
		{
		ESmsFlagIsComplete=0x01,
		ESmsFlagIsDecoded=0x02,

		ESmsStorageMask=0x0C,
		};

private:

	TInt iFlags;
	RMobileSmsStore::TMobileSmsStoreStatus iStatus;
	TInt iLogServerId;
	TTime iTime;
	CSmsPDU* iSmsPDU;
	CSmsBufferBase* iBuffer;
	RFs& iFs;

	TBool iIs16BitConcatenation;
	RPointerArray<CEmsInformationElement>* iInformationElementArray;
	CCnvCharacterSetConverter* iCharacterSetConverter;
public:
	CArrayFixFlat<TGsmSmsSlot> iSlotArray; ///< Array for slots	
	};

#include "gsmumsg.inl"

#endif // !defined __GSMUMSG_H__

