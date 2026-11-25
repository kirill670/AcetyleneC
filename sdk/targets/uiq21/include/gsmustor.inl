// GSMUSTOR.INL
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

/**
 * @file gsmustor.inl Implements inline methods for classes TSAREntry and CSARStore
 *
 */

#include <s32file.h>

inline TInt TSAREntry::Reference() const
/**
 * @return the concatenation reference
 */
	{
	return iReference;
	}


inline void TSAREntry::SetReference(TInt aReference)
/**
 * set the concatenation reference
 * 
 * @param aReference The concatenation reference
 */
	{
	iReference=aReference;
	}

inline TInt TSAREntry::Total() const
/**
 * @return the total number of PDUs in SMS message
 */
	{
	return iTotal;
	}

inline void TSAREntry::SetTotal(TInt aTotal)
/**
 * set the total number of PDUs in SMS message
 * 
 * @param aTotal The total number of PDUs in the message
 */
	{
	iTotal=aTotal;
	}

inline TInt TSAREntry::Count() const
/**
 * @return number of PDUs sent/received
 */
	{
	return iCount;
	}

inline void TSAREntry::SetCount(TInt aCount)
/**
 * set number of PDUs sent/received
 *
 * @param aCount The number of PDUs sent/received
 */
	{
	iCount=aCount;
	}

inline TBool TSAREntry::IsComplete() const
/**
 * @return ETrue if the whole message is sent/received
 */
	{
	return iCount==iTotal;
	}

inline TPtrC TSAREntry::Description1() const
/**
 * @return a pointer to the first 32 characters from buffer
 */
	{
	return iDescription1;
	}

inline void TSAREntry::SetDescription1(const TDesC& aDescription)
/**
 * set the first 32 characters in buffer
 *
 * @param aDescription The SAR entry description string
 */
	{
	iDescription1=aDescription;
	}

inline TPtrC TSAREntry::Description2() const
/**
 * @return a pointer to the original address
 */
	{
	return iDescription2;
	}

inline void TSAREntry::SetDescription2(const TDesC& aDescription)
/**
 * set the original address
 *
 * @param aDescription To set the original address
 */
	{
	iDescription2=aDescription;
	}

inline TInt TSAREntry::Data3() const
/**
 *  @return iData3
 */
	{
	return iData3;
	}

inline void TSAREntry::SetData3(TInt aData)
/**
 * set iData3
 *
 * @param aData To set iData3
 */
	{
	iData3=aData;
	}

inline const TTime& TSAREntry::Time() const
/**
 * @return the time when this message was sent/received
 */
	{
	return iTime;
	}

inline void TSAREntry::SetTime(const TTime& aTime)
/**
 * set the time when this message was sent/received
 *
 * @param aTime To set the message sent/received
 */
	{
	iTime=aTime;
	}

inline TStreamId TSAREntry::DataStreamId() const
/**
 * @return the data stream ID
 */
	{
	return iDataStreamId;
	}

inline void TSAREntry::SetDataStreamId(TStreamId aStreamId)
/**
 * set the data stream ID
 *
 * @param aStreamId To set the datastream id
 */
	{
	iDataStreamId=aStreamId;
	}

inline TBool TSAREntry::IsDeleted() const
/**
 * @return ETrue if this message is deleted
 */
	{
	return iFlags&ESAREntryIsDeleted;
	}

inline void TSAREntry::SetIsDeleted(TBool aIsDeleted)
/**
 * set if this message should be marked as deleted
 *
 * @param aIsDeleted Set to True to mark a message as deleted
 */
	{
	iFlags=aIsDeleted?iFlags|ESAREntryIsDeleted: iFlags&(~ESAREntryIsDeleted);
	}

inline TBool TSAREntry::IsAdded() const
/**
 * @return ETrue if this message is added
 */
	{
	return iFlags&ESAREntryIsAdded;
	}

inline void TSAREntry::SetIsAdded(TBool aIsAdded)
/**
 * set if this message should be marked as added
 *
 * @param aIsDeleted Set to True to mark a message as added
 */
	{
	iFlags=aIsAdded?iFlags|ESAREntryIsAdded: iFlags&(~ESAREntryIsAdded);
	}

inline RFs& CSARStore::FileSession() const
/**
 * @return The file system reference
 */
	{
	return iFs;
	}

inline TBool CSARStore::InTransaction() const
/**
 * @return whether it's in transaction
*/
	{
	return iInTransaction;
	}
