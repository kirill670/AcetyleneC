// BADESCA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by DavidW, October 1996
// Descriptor arrays
// 

#if !defined(__BADESCA_H__)
#define __BADESCA_H__

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif


/**
 *
 * An implementation base class for 8 bit descriptor arrays.
 *
 * It provides some of the behaviour for 8 bit descriptor arrays.The
 * class is abstract and cannot be instantiated.
 *
 * @since 5.0
 * @lib " bafl.lib "
 */
class CDesC8Array : public CArrayFixBase, public MDesC8Array
	{
protected:
	IMPORT_C CDesC8Array(TBufRep aRep,TInt aGranularity);
public:
    IMPORT_C ~CDesC8Array();
	IMPORT_C void AppendL(const TDesC8& aPtr);
	IMPORT_C void InsertL(TInt aPos,const TDesC8& aPtr);
	IMPORT_C TInt InsertIsqL(const TDesC8& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt InsertIsqAllowDuplicatesL(const TDesC8& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C void Sort(TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt Find(const TDesC8& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C TInt FindIsq(const TDesC8& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C void Delete(TInt aPos);
	IMPORT_C void Delete(TInt aIndex,TInt aCount);
	IMPORT_C void Reset();
	inline TPtrC8 operator[](TInt aIndex) const;
// from MDesC8Array
    IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC8 MdcaPoint(TInt aIndex) const;
	};

inline TPtrC8 CDesC8Array::operator[](TInt aIndex) const
	{ return(MdcaPoint(aIndex)); }


/**
 *
 * An array of 8 bit descriptors implemented using a flat buffer.
 * @since 5.0
 * @lib "bafl.lib"
 */
class CDesC8ArrayFlat : public CDesC8Array
	{
public:
	IMPORT_C CDesC8ArrayFlat(TInt aGranularity);
    IMPORT_C ~CDesC8ArrayFlat();
	};


/**
 *
 * An array of 8 bit descriptors implemented using a segmented buffer.
 * @since 5.0
 * @lib "bafl.lib"
 */
class CDesC8ArraySeg : public CDesC8Array
	{
public:
	IMPORT_C CDesC8ArraySeg(TInt aGranularity);
    IMPORT_C ~CDesC8ArraySeg();
	};


/**
 *
 * An implementation base class for 16 bit descriptor arrays.
 *
 * It provides some of the behaviour for 16it descriptor arrays.The class
 * is abstract and cannot be instantiated.
 *
 * @since 5.0
 * @lib " bafl.lib "
 */
class CDesC16Array : public CArrayFixBase, public MDesC16Array
	{
protected:
	IMPORT_C CDesC16Array(TBufRep aRep,TInt aGranularity);
public:
    IMPORT_C ~CDesC16Array();
	IMPORT_C void AppendL(const TDesC16& aPtr);
	IMPORT_C void InsertL(TInt aPos,const TDesC16& aPtr);
	IMPORT_C TInt InsertIsqL(const TDesC16& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt InsertIsqAllowDuplicatesL(const TDesC16& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C void Sort(TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt Find(const TDesC16& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C TInt FindIsq(const TDesC16& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C void Delete(TInt aPos);
	IMPORT_C void Delete(TInt aIndex,TInt aCount);
	IMPORT_C void Reset();
	inline TPtrC16 operator[](TInt aIndex) const;
// from MDesC16Array
    IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC16 MdcaPoint(TInt aIndex) const;
	};


/**
 *
 * Returns a non-modifiable descriptor to represent the descriptor
 * element located at the specified index within the array.
 *
 * @param     " TInt aIndex "
 *            The position of the descriptor element within the
 *            array. The position is relative to zero; i.e. zero
 *            implies the first descriptor element in the array.
 *            This value must be non-negative and less than the
 *            number of descriptors currently within the array
 *            otherwise the operator panics
 *            with<code>EArrayIndexOutOfRange</code>.
 * @returns   " TPtrC16 "
 *            A 16 bit non-modifiable pointer descriptor.
 */
inline TPtrC16 CDesC16Array::operator[](TInt aIndex) const
	{ return(MdcaPoint(aIndex)); }


/**
 *
 * Array of 16 bit descriptors implemented using a flat buffer.
 * @since 5.0
 * @lib "bafl.lib"
 */
class CDesC16ArrayFlat : public CDesC16Array
	{
public:
	IMPORT_C CDesC16ArrayFlat(TInt aGranularity);
    IMPORT_C ~CDesC16ArrayFlat();
	};


/**
 *
 * An array of 16 bit descriptors implemented using a segmented buffer.
 * @since 5.0
 * @lib "bafl.lib"
 */
class CDesC16ArraySeg : public CDesC16Array
	{
public:
	IMPORT_C CDesC16ArraySeg(TInt aGranularity);
    IMPORT_C ~CDesC16ArraySeg();
	};


/**
 *
 * Array of 8 bit non-modifiable pointer descriptors,
 * <code>TPtrC8</code>, implemented using a flat buffer.
 * @since 5.0
 * @lib "bafl.lib"
 */
class CPtrC8Array : public CArrayFixFlat<TPtrC8>, public MDesC8Array
	{
public:
	IMPORT_C CPtrC8Array(TInt aGranularity);
	IMPORT_C ~CPtrC8Array();
//
	IMPORT_C void CopyL(const MDesC8Array& aArray);
    inline void operator=(const MDesC8Array& aArray);
// Mixin members
    IMPORT_C TInt MdcaCount() const;
    IMPORT_C TPtrC8 MdcaPoint(TInt aIndex) const;
	};


/**
 *
 * An array of 16 bit non-modifiable pointer descriptors,
 * <code>TPtrC16</code>, implemented using a flat buffer.
 * @since 5.0
 * @lib "bafl.lib"
 */
class CPtrC16Array : public CArrayFixFlat<TPtrC16>, public MDesC16Array
	{
public:
	IMPORT_C CPtrC16Array(TInt aGranularity);
	IMPORT_C ~CPtrC16Array();
//
	IMPORT_C void CopyL(const MDesC16Array& aArray);
    inline void operator=(const MDesC16Array& aArray);
// Mixin members
    IMPORT_C TInt MdcaCount() const;
    IMPORT_C TPtrC16 MdcaPoint(TInt aIndex) const;
	};


/**
 *
 * Copies a descriptor array into this array, deleting any pre-existing
 * elements.
 *
 * The function constructs <code>TPtrC8</code> elements for each
 * descriptor element in the specified descriptor array.This operator
 * behaves in the same ways as <code>CPtrC8Array::CopyL()</code>.
 *
 * @param     "const MDesC8Array& aArray"
 *            A reference to any descriptor array which satisfies
 *            the protocol defined by this mixin class.
 */
inline void CPtrC8Array::operator=(const MDesC8Array& aArray)
	{CopyL(aArray);}


/**
 *
 * Copies a descriptor array into this array, deleting any pre-existing
 * elements.
 *
 * The function constructs <code>TPtrC16</code> elements for each
 * descriptor element in the specified descriptor array.This operator
 * behaves in the same ways as <code>CPtrC16Array::CopyL()</code>.
 *
 * @param     "const MDesC16Array& aArray"
 *            A reference to any descriptor array which satisfies
 *            the protocol defined by this mixin class.
 */
inline void CPtrC16Array::operator=(const MDesC16Array& aArray)
	{CopyL(aArray);}

// generic text array definitions

#if defined (_UNICODE)
/**
 * Build independent implementation base class for descriptor arrays.
 * @since 5.0
 */
typedef CDesC16Array     CDesCArray;

/**
 * Build independent array of descriptors implemented using a flat buffer.
 * @since 5.0
 */
typedef CDesC16ArrayFlat CDesCArrayFlat;

/**
 * Build independent array of descriptors implemented using a segmented buffer.
 * @since 5.0
 */
typedef CDesC16ArraySeg  CDesCArraySeg;

/**
 *
 * Build independent array of non-modifiable pointer descriptors.
 *
 * A 16 bit build variant is generated for a Unicode build and an 8 bit
 * build variant generated for a non-Unicode build.This build independent
 * type should always be used unless an explicit 8 bit or 16 bit build
 * variant is required.
 *
 * @since 5.0
 */
typedef CPtrC16Array CPtrCArray;
#else
typedef CDesC8Array      CDesCArray;
typedef CDesC8ArrayFlat  CDesCArrayFlat;
typedef CDesC8ArraySeg   CDesCArraySeg;
typedef CPtrC8Array CPtrCArray;
#endif


#endif // __BADESCA_H__




