// $Workfile: MmsUtilsHeaderArray.inl $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 3 $
// $Date: 31/01/02 11:45 $
//

/** @file 
 * This file contains inline function definitions the CMmsUtilsHeaderArray and CMmsUtilsHeader classes.
 */


#ifndef __MMSUTILSHEADERARRAY_INL__
#define __MMSUTILSHEADERARRAY_INL__


inline TBool CMmsUtilsHeaderArray::AreHeaderNamesCaseSensitive() const
    {
    return iHeaderNamesCaseSensitive;
    }


inline TInt CMmsUtilsHeaderArray::CompareHeaderNames(const TDesC& aName1, const TDesC& aName2) const
    {
    return iHeaderNamesCaseSensitive
           ? aName1.Compare(aName2)
           : aName1.CompareF(aName2);
    }


#endif // __MMSUTILSHEADERARRAY_INL__