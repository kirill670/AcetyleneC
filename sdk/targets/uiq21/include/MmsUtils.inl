// $Workfile: MmsUtils.inl $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Simonk $
// $Revision: 9 $
// $Date: 9/01/02 14:01 $
//

/** @file
 * This file contains inline implementations of TMmsTransferProgress and TMsvMmsEntry methods.
 */

#ifndef __MMSUTILS_INL__
#define __MMSUTILS_INL__


//
//TMmsTransferProgress
//

inline TInt TMmsTransferProgress::ErrorCode() const
/**
 * Get the error code for the current operation
 *
 * @return An error code
 */
	{
	return iErrorCode;
	}

inline void TMmsTransferProgress::SetErrorCode(TInt aErrorCode)
/**
 * Set the error code for the current operation.
 *
 * @param aErrorCode An error code
 */
	{
	iErrorCode = aErrorCode;
	}

inline TMmsTransferProgress::TMmsTransactionType TMmsTransferProgress::TransactionType() const
/**
 * Get the transaction type for the current operation.
 *
 * @return A transaction type
 */
	{
	return iTransactionType;
	}

inline void TMmsTransferProgress::SetTransactionType(TMmsTransferProgress::TMmsTransactionType aTransactionType)
/**
 * Set the transaction type for the current operation.
 *
 * @param aTransactionType A transaction type
 */
	{
	iTransactionType = aTransactionType;
	}

inline TInt TMmsTransferProgress::BytesSent() const
/**
 * Get the number of bytes sent in the current operation.
 *
 * @return A byte count
 */
	{
	return iBytesSent;
	}

inline void TMmsTransferProgress::SetBytesSent(TInt aBytesSent)
/**
 * Set the number of bytes sent in the current operation.
 *
 * @param aBytesSent A byte count
 */
	{
	iBytesSent = aBytesSent;
	}

inline TInt TMmsTransferProgress::BytesToSend() const
/**
 * Get the number of bytes still to be sent for the current operation.
 *
 * @return A byte count
 */
	{
	return iBytesToSend;
	}

inline void TMmsTransferProgress::SetBytesToSend(TInt aBytesToSend)
/**
 * Set the number of bytes still to be sent for the current operation.
 *
 * @param aBytesToSend A byte count
 */
	{
	iBytesToSend = aBytesToSend;
	}

inline TInt TMmsTransferProgress::MessageNumber() const
/**
 * During an operation which transfers <i>n</i> messages, this returns a number between 0..<i>n</i> indicating the number of the message currently being transferred.
 *
 * @return Number of the current message in an operation
 */
	{
	return iMessageNumber;
	}

inline void TMmsTransferProgress::SetMessageNumber(TInt aMessageNumber)
/**
 * During an operation which transfers <i>n</i> messages, this is used to set a number between 0..<i>n</i> indicating the number of the message currently being transferred.
 *
 * @param aMessageNumber Number of the current message in an operation
 */
	{
	iMessageNumber = aMessageNumber;
	}

inline TInt TMmsTransferProgress::MessageTotal() const
/**
 * Get the total number of messages being transferred in the current operation.
 *
 * @return Total number of messages for the current operation
 */
	{
	return iMessageTotal;
	}

inline void TMmsTransferProgress::SetMessageTotal(TInt aMessageTotal)
/**
 * Set the total number of messages being transferred in the current operation.
 *
 * @param aMessageTotal Total number of messages for the current operation
 */
	{
	iMessageTotal = aMessageTotal;
	}

inline TMmsTransferProgress::TMmsConnectionState TMmsTransferProgress::ConnectionState() const
    {
    return iConnectionState;
    }

inline void TMmsTransferProgress::SetConnectionState(TMmsTransferProgress::TMmsConnectionState aConnectionState)
    {
    iConnectionState = aConnectionState;
    }


//
//TMsvMmsEntry
//

const TInt32 KMmsProcessedFlag = 1;

inline TMmsMessageType TMsvMmsEntry::MessageType() const
/**
 * Get the MMS message type of this entry.
 *
 * @return An MMS message type
 */
    {
    return static_cast <TMmsMessageType> (iMtmData1);
    }
inline void TMsvMmsEntry::SetMessageType(TMmsMessageType aType)
/**
 * Set the MMS message type of this entry.
 *
 * @param aType An MMS message type
 */
    {
    iMtmData1 = static_cast <TInt32> (aType);
    }
inline TBool TMsvMmsEntry::Processed() const
/**
 * Get the processed flag for the current message
 */
	{
	if ((iMtmData2 & KMmsProcessedFlag) != 0)
		return ETrue;
	else
		return EFalse;
	}

inline void TMsvMmsEntry::SetProcessed(TBool aProcessed)
/**
 * Set the processed flag for the current message
 */
	{
	// Clear the processed flag
	iMtmData2 &= (~KMmsProcessedFlag);

	// Set the processed flag
	if (aProcessed)
		iMtmData2 |= KMmsProcessedFlag;
	}

//
// TMmsVersion
//

inline TUint8 TMmsVersion::Uint8() const
    {
    return iVersion;
    }


#endif // __MMSUTILS_INL__
