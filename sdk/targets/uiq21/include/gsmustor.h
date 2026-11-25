// GSMUSTOR.H
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

/**
 * @file gsmustor.h - Declares the classes TSAREntry and CSARStore
 *
 *
 * Abbreviations:
 *
 * PDU - Packet Data Unit
 * SAR - Segmentation and Reassembly Store
 * SR  - Status Report
 */

#ifndef GSMUSTOR_H__
#define GSMUSTOR_H__

#include <e32base.h>
#include <s32std.h>
#include <s32file.h>
#include "gsmumsg.h"
#include <babackup.h>

const TUid KSARStoreUid={0x1000089d};  ///<  Used for second uid of SAR stores

//
// forward declarations
//
class RReadStream;
class RWriteStream;

/**
 *  TSAREntry fields for the segmentation store
 *
 *  Reference - concatenation reference
 *  Total - total number of PDUs in SMS message
 *  Count - number of PDUs sent
 *  Data1 - total PDUs delivered<<16 and failed
 *  Data2 - log server id
 *  Data3 - validity period
 *  Data4 - type and min and max message reference
 *  Description1 - first 32 characters from buffer
 *  Description2 - original address
 *  Time - time on SMS message
 *
 * Abstracts an entry which is stored in the CSARStore
 *
 * The data stored in iDataN where N={1-4} has different meaning
 * depending on if it is used by the Reassembly store or the
 * Segmentation store. The table below should explain what they are
 * used for:
 *
 * <pre>
 *
 * Reassembly Store:
 *
 * -----------------------------------------------------------------
 * |  member |    3      |      2      |      1      |      0      |
 * -----------------------------------------------------------------
 * | iData1  |    bits7to4             | identifier1 | identifier2 |
 * | iData2  |                   Log server ID                     |
 * | iData3  |                                       | PDU type    |
 * | iData4  |                 SMS message storage                 |
 * -----------------------------------------------------------------
 *
 * Segmentation Store:
 *
 * -----------------------------------------------------------------
 * |  member |    3      |      2      |      1      |      0      |
 * -----------------------------------------------------------------
 * | iData1  |    N delivered          |         N failed          |
 * | iData2  |                   Log server ID                     |
 * | iData3  |              SMS submit validity period             |
 * | iData4  |   message PDU type      | reference1  | reference2  |
 * -----------------------------------------------------------------
 *
 * WAP Reassembly Store:
 *
 * -----------------------------------------------------------------
 * |  member |    3      |      2      |      1      |      0      |
 * -----------------------------------------------------------------
 * | iData1  |                    to port                          |
 * | iData2  |                   not used                          |
 * | iData3  |                   not used                          |
 * | iData4  |                   not used                          |
 * -----------------------------------------------------------------
 *
 * </pre>
 *
 */
class TSAREntry
/**
 * TSAREntry provides generic information useful for the segmentation and reassembly of SMS messages and
 * reassembly of WAP datagrams.  The constituent parts of both concatenated SMS messages and concatenated 7-bit
 * WAP datagrams contain a reference, the total number of parts and the index of the part in the complete
 * message or datagram.
 */
	{
public:
	enum
		{
		ESmsSAREntryDescriptionLength=32
		};
public:
	IMPORT_C TSAREntry();
	inline TInt Reference() const;
	inline void SetReference(TInt aReference);
	inline TInt Total() const;
	inline void SetTotal(TInt aTotal);
	inline TInt Count() const;
	inline void SetCount(TInt aCount);
	inline TBool IsComplete() const;

	inline TInt LogServerId() const {return iData2;}
	inline void SetLogServerId(TInt aId) {iData2 = aId;}
	
	inline TPtrC Description1() const;
	inline void SetDescription1(const TDesC& aDescription);
	inline TPtrC Description2() const;
	inline void SetDescription2(const TDesC& aDescription);

	inline TInt Data3() const;
	inline void SetData3(TInt aData);

	inline const TTime& Time() const;
	inline void SetTime(const TTime& aTime);

	inline TStreamId DataStreamId() const;
	inline void SetDataStreamId(TStreamId aStreamId);

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	inline TBool IsDeleted() const;
	inline void SetIsDeleted(TBool aIsDeleted);
	inline TBool IsAdded() const; 
	inline void SetIsAdded(TBool aIsAdded); 

private:
	enum TSAREntryFlags
		{
		ESAREntryIsDeleted=0x01, ///< indicates that this entry is deleted
		ESAREntryIsAdded=0x02    ///< indicated that this entry is added
		};
private:
	TInt iReference; ///< concatenation reference
	TInt iTotal;     ///< total number of PDUs in this SMS message
	TInt iCount;     ///< number of PDUs sent/received for this SMS message
protected:
	TInt iData1;     /// @todo should be TUint32
	TInt iData2;     ///< Log server ID
	TInt iData3;
	TInt iData4;
private:
	TBuf<ESmsSAREntryDescriptionLength> iDescription1; ///< first 32 characters from buffer
	TBuf<ESmsSAREntryDescriptionLength> iDescription2; ///< original address
	TTime iTime;                                       ///< time when message was sent/received
	TStreamId iDataStreamId;
	TInt iFlags;  //  Not externalized
	friend class CSARStore; 
	};


class TSmsReassemblyEntry : public TSAREntry
/**
 * Abstraction of an SMS reassembly store entry for incoming SMS messages.
 * This class should reflect parts of a complete SMS message to be stored
 * in the reassembly store.
 */
	{
private:
	enum
		{
		KMarkedAsPassedToClientFlag = 0x80000000,
		KPduTypeMask = 0xFF,
		KReassemblyEntryClear = 0x00
		};

public:
	// iData1
	inline TInt Bits7to4() const {return (iData1 >> 16) & 0xffff;}
	inline TInt Identifier1() const {return (iData1 >> 8) & 0xff;}
	inline TInt Identifier2() const {return (iData1 >> 0) & 0xff;}
	inline void SetBits7to4andIdentifiers(TInt aBits7to4, TInt aId1, TInt aId2)
	{iData1 = (TInt)((aBits7to4 << 16) | ((aId1 & 0xff)<< 8) | (aId2 & 0xff)); }

	// iData3
	inline CSmsPDU::TSmsPDUType PduType() const {return (CSmsPDU::TSmsPDUType)(iData3 & 0xff);} // 8 bits
	inline void SetPduType(CSmsPDU::TSmsPDUType aPduType) {iData3 = (iData3 & ~KPduTypeMask) | (TInt)(aPduType & KPduTypeMask);}

	inline TBool PassedToClient() const {return (iData3 & KMarkedAsPassedToClientFlag) ? ETrue:EFalse;}
	inline void SetPassedToClient(TBool aPassed) {iData3 = (iData3 & ~KMarkedAsPassedToClientFlag) | (aPassed ? KMarkedAsPassedToClientFlag : KReassemblyEntryClear);}

	// iData4
	inline CSmsMessage::TMobileSmsStorage Storage() const {return (CSmsMessage::TMobileSmsStorage)(iData4 & 0xff);}
	inline void SetStorage(CSmsMessage::TMobileSmsStorage aStorage) {iData4 = (CSmsMessage::TMobileSmsStorage)aStorage;}
	};


class TSmsSegmentationEntry : public TSAREntry
/**
 * Abstraction of an SMS segmentation store entry for outgoing SMS messages.
 * This class should reflect parts of a complete SMS message to be stored
 * in the segmentation store.
 */
	{
public:
	// iData1
	inline TInt Delivered() const {return (iData1 >> 16);} ///< return number of delivered PDUs
	inline TInt Failed() const {return (iData1 & 0xffff);} ///< return number of permanently failed PDUs
	inline void SetDeliveredAndFailed(TInt aDelivered, TInt aFailed)
		{iData1 = ((aDelivered << 16) | (aFailed & 0xffff));} ///< set the number of delivered and failed PDUs

	// iData3
	inline TInt ValidityPeriod() const {return (iData3); }           ///< return the validity period
	inline void SetValidityPeriod(TInt aValPer) {iData3 = aValPer; } ///< set the validity period

	// iData4
	inline TBool ExpectStatusReport() const {return (((iData4 >> 24) & 0x01) == 0x01); }  ///< return if we expect SR
	inline CSmsPDU::TSmsPDUType PduType() const {return (CSmsPDU::TSmsPDUType)((iData4 >> 16) & 0xff); }  ///< return the type of the PDU
	inline TInt Reference1() const {return ((iData4 >> 8) & 0xff); }  ///< return the message reference (low)
	inline TInt Reference2() const {return ((iData4 >> 0) & 0xff); }  ///< return the message reference (high)
	inline void SetPduTypeAndRefs(TBool aSR, TInt aPduType, TInt aRef1, TInt aRef2)
		{iData4 = (((aSR & 0x01) << 24) | (aPduType << 16) | ((aRef1 & 0xff ) << 8) | (aRef2 & 0xff));} ///< set PDU type and references
	};


class TWapReassemblyEntry : public TSAREntry
/**
 * Abstraction of a WAP reassembly store entry.
 * This class should reflect a complete WAP message.
 */
	{
public:
	inline TInt ToPort() const {return iData1;}            ///< return the destination port number
	inline void SetToPort(TInt aToPort){iData1 = aToPort;} ///< set the destination port number
	};

class CSARStore : public CBase
/**
 * this class controls the SAR store for Sms Segmentation and
 * Reassembly, and Wap Reassembly.
 */
	{
public:
	IMPORT_C void OpenL(const TDesC& aFullName,const TUid& aThirdUid);
	IMPORT_C void Close();
	IMPORT_C void CompactL();

	IMPORT_C const CArrayFix<TSAREntry>& Entries() const;
	IMPORT_C void PurgeL(const TTimeIntervalMinutes& aTimeIntervalMinutes,TBool aPurgeIncompleteOnly);
	IMPORT_C void PurgeL(TInt aKSegmentationLifetimeMultiplier,TBool aPurgeIncompleteOnly);
	IMPORT_C void DeleteEntryL(TInt aIndex);

	IMPORT_C void BeginTransactionLC();
	IMPORT_C void CommitTransactionL(); //Pops this off this cleanup stack and commits iFileStore
	void Revert();

	inline RFs& FileSession() const;
	inline TBool InTransaction()const;
	IMPORT_C void DoOpenL();

protected:
	IMPORT_C CSARStore(RFs& aFs);
	IMPORT_C ~CSARStore();

	IMPORT_C CFileStore& FileStore();
	IMPORT_C const CFileStore& FileStore() const;

	IMPORT_C void AddEntryL(const TSAREntry& aEntry);
	IMPORT_C void ChangeEntryL(TInt aIndex,const TSAREntry& aNewEntry);  

	IMPORT_C TStreamId ExtraStreamId() const;
	IMPORT_C void SetExtraStreamIdL(const TStreamId& aExtraStreamId);

private:
	void DoDeleteEntryL(TInt aIndex);  //  Deletes stream but doesn't call iFileStore->CommitL()
	void InternalizeEntryArrayL(); 
	void ExternalizeEntryArrayL(); 
	void DoCommitAndCompactL();
	void RemoveDeletedEntries();
	void ReinstateDeletedEntries();

private:
	enum
		{
		KNumStoreCommitsBeforeCompaction=16
		};

protected:
	RFs& iFs;                             ///< file server
private:

	CFileStore* iFileStore;               ///< pointer to the file store
	CArrayFixFlat<TSAREntry> iEntryArray; ///< array of SAR entries
	TStreamId iExtraStreamId;             ///< used for any other data that needs persisting
	TInt iCommitCount;                    ///< counts number of Commit's - used for CompactL
	TPtrC iFullName;                      ///< holds the name of the File Store
	TUid iThirdUid;
	TBool iInTransaction;					///< For debugging purposes to ensure only one transaction at a time
	};

class CGsmuBackupObserver : public CBase, MBackupOperationObserver
/**
 * This class handle closes all SAR stores if a backup event starts
 */
	{
	public:
		IMPORT_C static CGsmuBackupObserver* NewL();
		IMPORT_C ~CGsmuBackupObserver();
		IMPORT_C void AddSARStoreL(CSARStore& aSARStore);
		IMPORT_C void RemoveSARStore(const CSARStore& aSARStore);

	private:
		CGsmuBackupObserver();
		void ConstructL();
		void HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes);

		CBaBackupSessionWrapper* iBackup;
		RPointerArray<CSARStore> iSARStores;
	};

#include "gsmustor.inl"

#endif // !defined GSMUSTOR_H__

