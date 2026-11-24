// SAIRAS.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __SAIRAS_H__
#define __SAIRAS_H__

#include <e32base.h>
#include "sacls.h"
#include "saclient.h"

/**
@internalComponent
*/
enum TSAIrStatus
	{
	IrLoaded,
	IrDiscoveredPeer,
	IrLostPeer,
	IrConnected,
	IrBlocked,
	IrDisConnected,
	IrUnloaded
	};


/** 
Note: The class is a part of SystemAgent services and it is deprecated now. Use 
P&S services.
@see RProperty
@deprecated
@publishedPartner
*/
class RISANotify : public RSystemAgentBase
 	{
public:
	IMPORT_C RISANotify();    
	IMPORT_C TInt NotifyIREvent(TSAIrStatus aIRStatus);
	IMPORT_C TInt NotifyIREventSynchronously(TSAIrStatus aIRStatus);
	};


#endif
