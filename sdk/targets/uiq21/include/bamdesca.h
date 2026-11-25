// BAMDESCA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by DavidW, March 1996
// Mixin descriptor array
//

#if !defined(__BAMDESCA_H__)
#define __BAMDESCA_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif


/**
 *
 * Interface class for 8 bit descriptor arrays.
 *
 * It should be inherited by classes which implement this protocol.This
 * protocol is implemented by class <code>CDesC8Array</code> and the
 * concrete class <code>CPtrC8Array</code>.
 *
 * @since 5.0
 * @lib " N/A "
 */
class MDesC8Array
    {
public:
	/**
	 * Destructor.
	 */
    virtual ~MDesC8Array() {}

	/**
	 *
	 * Returns the number of descriptor elements in a descriptor
	 * array.
	 *
	 * @returns   " TInt "
	 *            The number of descriptor elements in a descriptor
	 *            array.
	 */
    virtual TInt MdcaCount() const =0;

	/**
	 *
	 * Indexes into a descriptor array.
	 *
	 * @param     " TInt aIndex "
	 *            The position of the descriptor element within a
	 *            descriptor array. The position is relative to zero;
	 *            i.e. zero implies the first descriptor element in a
	 *            descriptor array.
	 * @returns   " TPtrC8 "
	 *            An 8 bit non-modifiable pointer descriptor
	 *            representing the descriptor element located at
	 *            position <code>aIndex</code> within a descriptor
	 *            array.
	 */
    virtual TPtrC8 MdcaPoint(TInt aIndex) const =0;
    };


/**
 *
 * Interface class for 16 bit descriptor arrays.
 *
 * It should be inherited by classes which implement this protocol.This
 * protocol is implemented by class <code>CDesC16Array</code> and the
 * concrete class <code>CPtrC16Array</code>.
 *
 * @since 5.0
 * @lib " N/A"
 */
class MDesC16Array
    {
public:
	/**
	 * Destructor.
	 */
    virtual ~MDesC16Array() {}

	/**
	 *
	 * Returns the number of descriptor elements in a descriptor
	 * array.
	 *
	 * @returns   " TInt "
	 *            The number of descriptor elements in a descriptor
	 *            array.
	 */
    virtual TInt MdcaCount() const =0;

	/**
	 *
	 * Indexes into a descriptor array.
	 *
	 * @param     " TInt aIndex "
	 *            The position of the descriptor element within a
	 *            descriptor array. The position is relative to zero;
	 *            i.e. zero implies the first descriptor element in a
	 *            descriptor array.
	 * @returns   " TPtrC16 "
	 *            A 16 bit non-modifiable pointer descriptor
	 *            representing the descriptor element located at
	 *            position <code>aIndex</code> within a descriptor
	 *            array.
	 */
    virtual TPtrC16 MdcaPoint(TInt aIndex) const =0;
    };


// The definitions below are macros rather than typedefs to avoid generating
// warning C4097 every time the generic mixin class is used in a class
// definition.

#if defined(_UNICODE)
#define MDesCArray MDesC16Array
//typedef MDesC16Array MDesCArray;
#else
#define MDesCArray MDesC8Array
//typedef MDesC8Array  MDesCArray;
#endif


#endif // __BAMDESCA_H__

