// COEUTILS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEUTILS_H__)
#define __COEUTILS_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

/** 
 * The <code>ConeUtils</code> class provides file and path utility methods.
 * 
 * @lib
 * @publishedAll
 * @released 
 */
class ConeUtils

    {
public:
   /**
    * [what]
    * 
    * @param aFileName [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C static TBool FileExists(const TDesC& aFileName);

   /**
    * [what]
    * 
    * @param aFileName [what]
    * @remarks
    * @see
    */
    IMPORT_C static void EnsurePathExistsL(const TPtrC& aFileName);
    };

#endif
