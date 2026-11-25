// asn1enc.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// Declare all classes used to decode ASN.1 data, including the base interface

#ifndef __ASN1ENC_H__
#define __ASN1ENC_H__

#include <e32base.h>
#include <asn1cons.h>

class CASN1EncBase;
class CInteger;
class TASN1EncBase128DER;


typedef void (CASN1EncBase::* WriteFunc)(TDes8& aBuf) const;

// Base class for all asn1 types that we can encode
class CASN1EncBase : public CBase
	{
public:
	// Gives total number of octets in the DER encoding of this object
	IMPORT_C TUint LengthDER() const;
	
	// Writes entire DER encoding of this object into the given buffer
	IMPORT_C void WriteDERL(TDes8& aBuf, TUint& aPos) const;

	// Set tag type/class
	IMPORT_C void SetTag(const TTagType aType,
		const TASN1Class aClass = EContextSpecific);

	IMPORT_C ~CASN1EncBase();

	void SetParent(CASN1EncBase* aParent);

protected:
	IMPORT_C CASN1EncBase(const TTagType aType, const TASN1Class aClass);

	// Must call this version from derived classes in their ConstructL, but only once
	// they're ready to have CalculateContentsLengthDER called on them
	IMPORT_C virtual void ConstructL();

	// Derived classes must call this if the length of their contents changes
	// after construction
	void ContentsLengthChanged();

private:
	// Number of octets in DER encoding of each section
	// These methods must set the values in their appropriate data members (declared below)
	void CalculateTagLengthDER();
	void CalculateLengthLengthDER();
	virtual void CalculateContentsLengthDER() = 0;

	virtual TBool IsConstructed() const = 0;
	
	// Write the octet data in each section
	// Note that buffer *will* be big enough: these are called only after checking.
	void WriteTagDERL(TDes8& aBuf) const;
	virtual void WriteLengthDER(TDes8& aBuf) const;
	virtual void WriteContentsDERL(TDes8& aBuf) const = 0;

	// Helper function, used for efficiency
	void WriteHelperL(TDes8& aBuf, TUint& aPos, const TUint aLength,
		WriteFunc aWriteFunc) const;

protected:
	// Cached length data - data set from the CalculateXxxx methods above
	TUint iTagLengthDER;
	TUint iLengthLengthDER;
	TUint iContentsLengthDER;

private:
	// The object owning this one (if we're held in a sequence, for example)
	CASN1EncBase* iParent;

	// Tag data
	TTagType iType;
	TASN1Class iClass;
	};


// Base class for all ASN1 constructed-type objects.  Most of these are container classes,
// but another type is the explicit-tagging wrapper object
class CASN1EncConstructed : public CASN1EncBase
	{
protected:
	CASN1EncConstructed(const TTagType aType, const TASN1Class aClass);

private:
	virtual const CASN1EncBase& Child(const TUint aIndex) const = 0;
	virtual TUint NumChildren() const = 0;

private:
	// From CASN1EncBase
	void CalculateContentsLengthDER();
	TBool IsConstructed() const;
	void WriteContentsDERL(TDes8& aBuf) const;
	};


// Class used to wrap other encoding objects, in order to give them an explicit tag
class CASN1EncExplicitTag : public CASN1EncConstructed
	{
public:
	// Takes ownership of the encoder, *including* if this method Leaves()
	IMPORT_C static CASN1EncExplicitTag* NewLC(CASN1EncBase* aEncoder,
		const TTagType aType, const TASN1Class aClass = EContextSpecific);

	IMPORT_C ~CASN1EncExplicitTag(); // virtual from base

private:
	CASN1EncExplicitTag(CASN1EncBase* aEncoder, const TTagType aType, const TASN1Class aClass);

	// From CASN1EncConstructed
	TUint NumChildren() const;
	const CASN1EncBase& Child(const TUint aIndex) const;

private:
	CASN1EncBase* iEncoder;  // Inner encoding object
	};


// Base class for all ASN1 container types - sequences, sets, etc.
class CASN1EncContainer : public CASN1EncConstructed
	{
public:
	// Call this to add a child object to the container
	// Takes ownership if and only if it doesn't Leave
	// Checks for null input, calls AddChildInt, calls ContentsLengthChanged()
	IMPORT_C void AddChildL(CASN1EncBase* aChild);

protected:
	CASN1EncContainer(const TTagType aType);

private:
	// Internal method, derived classes implement to add a child
	// No need to check for null input or call ContentsLengthChanged()
	// Take ownership, but only if you don't leave
	virtual void AddChildIntL(const CASN1EncBase* aChild) = 0;
	};


// Class for encoding SEQUENCE and SEQUENCE-OF data types
class CASN1EncSequence : public CASN1EncContainer
	{
public:
	IMPORT_C static CASN1EncSequence* NewLC();

	IMPORT_C ~CASN1EncSequence(); // virtual from base

private:
	CASN1EncSequence();

	// From CASN1EncContainer
	const CASN1EncBase& Child(const TUint aIndex) const;
	void AddChildIntL(const CASN1EncBase* aChild);
	TUint NumChildren() const;

private:
	RPointerArray<CASN1EncBase> iChildren;
	};


// All ASN1 primitive type encoding classes derive from here
class CASN1EncPrimitive : public CASN1EncBase
	{
protected:
	IMPORT_C CASN1EncPrimitive(const TTagType aType);

private:
	// From CASN1EncBase
	TBool IsConstructed() const;
	};


// For encoding NULLs
class CASN1EncNull : public CASN1EncPrimitive
	{
public:
	IMPORT_C static CASN1EncNull* NewLC();

private:
	CASN1EncNull();

	// Methods from CASN1EncBase
	void CalculateContentsLengthDER() ;
	void WriteContentsDERL(TDes8& aBuf) const;
	};


// For encoding Booleans
class CASN1EncBoolean : public CASN1EncPrimitive
	{
public:
	IMPORT_C static CASN1EncBoolean* NewLC(const TBool aBool);

private:
	CASN1EncBoolean(const TBool aBool);

	// Methods from CASN1EncBase
	void CalculateContentsLengthDER() ;
	void WriteContentsDERL(TDes8& aBuf) const;

	const TBool iBool;
	};


// For encoding TInts only.  Use CASN1EncBigInt for encoding CInteger objects
class CASN1EncInt : public CASN1EncPrimitive
	{
public:
	IMPORT_C static CASN1EncInt* NewLC(const TInt aInt);

private:
	CASN1EncInt(const TInt aInt);

	// Methods from CASN1EncBase
	void CalculateContentsLengthDER() ;
	void WriteContentsDERL(TDes8& aBuf) const;

private:
	const TInt iInt;
	};


// For encoding CInteger objects only - use CASN1EncInt for TInts
class CASN1EncBigInt : public CASN1EncPrimitive
	{
public:
	// Takes a deep copy
	IMPORT_C static CASN1EncBigInt* NewLC(const CInteger& aInteger);

	IMPORT_C ~CASN1EncBigInt(); // virtual from base

private:
	CASN1EncBigInt();
	void ConstructL(const CInteger& aInteger);

	// Methods from CASN1EncBase
	void CalculateContentsLengthDER();
	void WriteContentsDERL(TDes8& aBuf) const;

private:
	HBufC8* iContents;
	TPtrC8 iWriteContents;
	};


// For encoding octet strings
class CASN1EncOctetString : public CASN1EncPrimitive
	{
public:
	// Takes a deep copy
	IMPORT_C static CASN1EncOctetString* NewLC(const TDesC8& aStr);

	IMPORT_C ~CASN1EncOctetString(); // virtual from base

private:
	CASN1EncOctetString();
	void ConstructL(const TDesC8& aStr);

	// Methods from CASN1EncBase
	void CalculateContentsLengthDER();
	void WriteContentsDERL(TDes8& aBuf) const;

private:
	HBufC8* iContents;
	};


// For encoding object identifiers
class CASN1EncObjectIdentifier : public CASN1EncPrimitive
	{
public:
	// Takes ints in a string, delimited by '.' characters in between (not at ends)
	// Takes a deep copy of the info
	IMPORT_C static CASN1EncObjectIdentifier* NewLC(const TDesC& aStr);

	IMPORT_C ~CASN1EncObjectIdentifier(); // virtual from base

private:
	CASN1EncObjectIdentifier();
	void ConstructL(const TDesC& aStr);

	// Methods from CASN1EncBase
	void CalculateContentsLengthDER();
	void WriteContentsDERL(TDes8& aBuf) const;

private:
	// Data to encode
	RArray<TASN1EncBase128DER> iData;
	TUint8 iFirstOctet;
	};


// For encoding GeneralisedTime objects
// Doesn't support fractions of seconds or regional time zone offsets
class CASN1EncGeneralizedTime : public CASN1EncPrimitive
	{
public:
	IMPORT_C static CASN1EncGeneralizedTime* NewLC(const TTime& aTime);

private:
	CASN1EncGeneralizedTime(const TTime& aTime);

	// Methods from CASN1EncBase
	void CalculateContentsLengthDER();
	void WriteContentsDERL(TDes8& aBuf) const;

private:
	TDateTime iDateTime;
	};

#endif