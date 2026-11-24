/*
* ==============================================================================
*  Name        : LbsPtrHolder.h
*  Part of     : Mobile Location Framework/Core
*  Interface   : --
*  Description :
*   ?description_line
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/
// LbsPtrHolder.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSPTRHOLDER_H__
#define __LBSPTRHOLDER_H__

#include <e32base.h>
#include <LbsCommon.h>


class CPositioningPtrHolder : public CBase
/*
 * Holds the TPtr8 and TPtrC8 arrays for all RPositionServer requests.
 *
 * @internalComponent
 */
	{
public:
	IMPORT_C static CPositioningPtrHolder* NewL(TInt aNumberOfPtrs,
	                                            TInt aNumberOfPtrCs);
	IMPORT_C ~CPositioningPtrHolder();
	IMPORT_C TPtr8& Ptr(TInt aIndex);
	IMPORT_C TPtrC8& PtrC(TInt aIndex);
protected:
	IMPORT_C void ConstructL(TInt aNumberOfPtrs, TInt aNumberOfPtrCs);
private:
	RArray<TPtr8> iPtrArray;
	RArray<TPtrC8> iPtrCArray;
	};


class CServerPositioningPtrHolder : public CPositioningPtrHolder
/*
 * Holds the TPtr8 and TPtrC8 arrays for all RPositioner requests.
 *
 * @internalComponent
 */
	{
public:
	IMPORT_C static CServerPositioningPtrHolder* NewL(TInt aNumberOfPtrs,
	                                                  TInt aNumberOfPtrCs);
	TPositionModuleId iPositionModuleId;
	};

#endif // __LBSPTRHOLDER_H__
