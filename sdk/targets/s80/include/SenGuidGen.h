/*
 * =========================================================================
 *  Name     : SenGuidGen.h
 *  Part of  : SenUtils
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Utils/inc/SenGuidGen.h,v $
 *   $Date: 2004/10/19 08:55:40 $
 *   $Revision: 1.2 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */
 


#ifndef CCGUIDGEN_H
#define CCGUIDGEN_H

#include <e32base.h>
#include <e32std.h>


// FORWARD DECLARATION
class CMD5; 

class CSenGuidGen : public CBase
    {
public:
    enum { KMaxLength = 36 };

public:
    IMPORT_C static CSenGuidGen *NewL();
    IMPORT_C static CSenGuidGen *NewLC();
    ~CSenGuidGen();

public:
    // Generate totally random (but not cryptographically strong)
    // GUIDs. The GUID is based on the MD5 hash of a random number
    // and the current time. Some kind of host ID should be also
    // used but the author did not find an easy way of getting it.
    IMPORT_C HBufC* GetRandomGuidLC();
    IMPORT_C HBufC8* GetRandomGuid8LC();
    IMPORT_C HBufC16* GetRandomGuid16LC();

private:
    CSenGuidGen();
    void ConstructL();

private:
    TPtrC8 GetRandomHash();

private:
    TInt64 iSeed;
    HBufC8 *ipHostId;
    CMD5 *ipMd5HashGen;
    };

#endif
