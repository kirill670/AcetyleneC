// APMREC.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
 *
 * Gets the number of data (MIME) types supported by this recognizer.
 *
 * @returns   "TInt"
 *            The number of data types.
 */
inline TInt CApaDataRecognizerType::MimeTypesCount() const
	{
	return iCountDataTypes;
	}

/**
 *
 * Gets the UID that identifies the recognizer.
 *
 * @returns   "TUid"
 *            The UID.
 */
inline TUid CApaDataRecognizerType::TypeUid() const
	{
	return iTypeUid;
	}

/**
 *
 * Gets the recognizer's priority.
 *
 * The priority defines the likelihood that the recognizer will
 * successfully identify data. This is one of the
 * <code>CApaDataRecognizerType::TRecognizerPriority</code> enumerators.
 *
 * @returns   "TInt"
 *            The priority value.
 */
inline TInt CApaDataRecognizerType::Priority() const
	{
	return iPriority;
	}
	
/**
 *
 * Gets the recognizer's confidence rating for the most recently
 * recognized data.
 *
 * @returns   "TInt"
 *            The confidence rating. This is one of the
 *            <code>TRecognitionConfidence</code> enumeration
 *            values.
 */
inline TInt CApaDataRecognizerType::Confidence() const
	{
	return iConfidence;
	}

/**
 *
 * Tests whether the recognizer is locked.
 *
 * @returns   "TInt"
 *            If zero, the recognizer is not locked; if greater than
 *            0, the recognizer is locked.
 */
inline TInt CApaDataRecognizerType::Locked() const
	{
	return iLock;
	}


	
