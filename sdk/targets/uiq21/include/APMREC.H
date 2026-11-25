// APMREC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APMREC_H__)
#define __APMREC_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif

// classes defined
class CApaDataRecognizerType;
// classes referenced
class RFs;

/**
 *
 * The result of an attempt to recognize data.
 *
 * The class contains a data (MIME) type and a confidence rating.An
 * object of this type is passed to the Application Architecture server
 * when making a request to recognize data.
 *
 * @since 5.0
 * @lib "apmime.lib"
 */
class TDataRecognitionResult
	{
public:
	IMPORT_C void Reset();
public:
	TDataType iDataType;
	TInt iConfidence;
	};

const TInt KDataArrayGranularity=5;
typedef CArrayFixFlat<TDataType> CDataTypeArray;

class CApaDataRecognizer : public CBase
	{
public:
	IMPORT_C TDataRecognitionResult RecognizeL(const TDesC& aName, const TDesC8& aBuffer);
	IMPORT_C TBool RecognizeL(const TDesC& aName, const TDesC8& aBuffer, const TDataType& aDataType);
	IMPORT_C ~CApaDataRecognizer();
	IMPORT_C TInt PreferredBufSize();
	IMPORT_C void DataTypeL(CDataTypeArray& aArray);
	IMPORT_C void UpdateDataTypesL();
	IMPORT_C TInt AcceptedConfidence();
	IMPORT_C void SetAcceptedConfidence(TInt aConfidence);
protected:
	IMPORT_C CApaDataRecognizer(RFs& aFs);
	IMPORT_C void AddDataRecognizerType(CApaDataRecognizerType* aDataRecognizerType);
	IMPORT_C TInt RemoveDataRecognizerType(const CApaDataRecognizerType* aDataRecognizerType);
	IMPORT_C void DestroyRecognizerList();
private:
	void AddDataTypeL(const TDataType& aDataType);
	TBool DoRecognizeL(CApaDataRecognizerType* aDataRecognizerType, const TDesC& aName,
	const TDesC8& aBuffer, const TDataType& aDataType);
protected:
	RFs& iFs;
private:
	IMPORT_C virtual void CApaDataRecognizer_Reserved_1();
private:
	CArrayPtrFlat<CApaDataRecognizerType> iDataRecognizerList;
	CDataTypeArray iDataArray;
	TInt iAcceptedConfidence;
	TDataRecognitionResult iResult;
	TInt iSpare;
	};

/**
 *
 * Abstract base class for a recognizer.
 *
 * Concrete recognizers need to define and implement a derived class;
 * specifically, they need to provide an implementation of the
 * <code>DoRecognizeL()</code>, <code>SupportedDataTypeL()</code> and
 * <code>PreferredBufSize()</code> functions.The class is implemented as
 * part of a DLL. The ordinal 1 function of the DLL must construct an
 * instance of, and return a pointer to, a
 * <code>CApaDataRecognizerType</code> derived class.
 *
 * @since 5.0
 * @lib "apmime.lib"
 */
class CApaDataRecognizerType : public CBase
	{
public:	
	/**
	 *
	 * A set of values used to indicate the probability that the recognizer
	 * will successfully identify data.
	 
	 *
	 * The Application Architecture framework uses this set to determine the
	 * order in which recognizers are invoked.
	 * * @since 
	 */
	enum TRecognizerPriority
		{
		/** The highest recognizer priority. Recognizers with this priority are
		invoked before those with any other priority.
		 */
		EHigh=100,
		/** The normal recognizer priority. Recognizers with this priority are
		invoked after those with a <code>EHigh</code> priority but before
		those with a <code>ELow</code> priority.
		 */
		ENormal=0,
		/** The lowest recognizer priority.
		 */
		ELow=-100
		};		
	/**
	 *
	 * A set of values describing the probability that the recognizer assigns
	 * to its belief that the most recently sampled data is of the type
	 * ascribed to it.
	 * @since 
	 */
 	enum TRecognitionConfidence
		{
		/** The data is definitely of the data type.
 		*/	
		ECertain=KMaxTInt,
		/** A level of confidence between <code>ECertain</code> and <code>EPossible</code>.
		 */
		EProbable=100,
		/** The data is possibly of the data type.
		 */
		EPossible=0,
		/** A level of confidence between <code>EPossible</code> and <code>ENotRecognized</code>.
		 */
		EUnlikely=-100,
		/** The data is not recognized.
		 */
		ENotRecognized=KMinTInt
		};
public:
	inline TInt MimeTypesCount() const;
	inline TUid TypeUid() const;
	inline TInt Priority() const;
	inline TInt Confidence() const;
	inline TInt Locked() const;
	IMPORT_C TDataRecognitionResult RecognizeL(const TDesC& aName, const TDesC8& aBuffer);
	IMPORT_C TDataType MimeType();
	IMPORT_C void Lock();
	IMPORT_C void Unlock();
	IMPORT_C void UpdateDataTypesL();
	IMPORT_C ~CApaDataRecognizerType();
	IMPORT_C virtual TUint PreferredBufSize();
	/**
	 *
	 * Gets one of the data (MIME) types that the recognizer can recognize.
	 *
	 * @param     "TInt aIndex"
	 *            An index that identifies the data type. Typically, the
	 *            minimum value is zero and the maximum value is the
	 *            value of <code>MimeTypesCount()</code> - 1.
	 * @returns   "TDataType"
	 *            The data (MIME) type.
	 */
	IMPORT_C virtual TDataType SupportedDataTypeL(TInt aIndex) const = 0;
protected:
	IMPORT_C CApaDataRecognizerType(TUid aUid, TInt aPriority);
private:
	IMPORT_C virtual void DoRecognizeL(const TDesC& aName, const TDesC8& aBuffer);
	// Reserved virtual functions...
	IMPORT_C virtual void Reserved_1();
protected:
	const TUid iTypeUid;
	const TInt iPriority;
	TInt iCountDataTypes;
	TInt iConfidence;
	TDataType iDataType;
private:
	TInt iLock;
	TInt iSpare;
	};

#include <apmrec.inl>

#endif
