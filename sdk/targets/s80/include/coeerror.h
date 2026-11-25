// COEERROR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEERROR_H__)
#define __COEERROR_H__

/**
@internal Technology
*/
#define KUidConeDllValue16 0x10003a41

/**
@internal Technology
*/
const TUid KUidConeDll16={KUidConeDllValue16};


#if defined(_UNICODE)
/** @internal Technology */
#define KUidConeDllValue KUidConeDllValue16
/** @internal Technology */
const TUid KUidConeDll={KUidConeDllValue};
#else
/** [what] */
#define KUidConeDllValue KUidConeDllValue8
/** [what] */
const TUid KUidConeDll={KUidConeDllValue};
#endif


/** 
 * UI Control Framework errors.
 * @publishedAll
 * @deprecated 
 */
enum
    {
    /** Not used. */
    KErrCoeResourceFileDuplicateOffset,
    /** Read fail. CCoeEnv::ReadResource() sets this as the
    active scheduler's extended error number if the read fails. */
    KErrCoeFailedToReadFromProgDisk
    };

#endif

