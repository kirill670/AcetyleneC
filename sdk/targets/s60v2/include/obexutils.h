// ObexUtils
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
// Obex Utility Class

#ifndef __OBEXUTILS_H__
#define __OBEXUTILS_H__

#include <e32base.h>
#include <obex.h>



// Messaging Suite
#include <msvAPI.h>

#include "ListenerContainer.h"

class CObexUtils : public CBase
/**
Class CObexUtils
The purpose of this class is multifold:

Handles storage / deletion of the received object in the messaging inbox.

@internalTechnology
@removed
*/
	{
public:
	IMPORT_C static void DummySaveObjToInboxL(CMsvSession& , CBaseContainer& , TUid , TMsvId& , TDesC&);

	IMPORT_C static void DummyRemoveFromInboxL(CMsvSession& , TMsvId);

	IMPORT_C static void DummyFinaliseObexMessageL(CMsvSession& , TMsvId);



	

	};


#endif // __OBEXUTILS__
