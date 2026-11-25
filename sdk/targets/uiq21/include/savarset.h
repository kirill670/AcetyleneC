// SAVARSET.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __SAVARSET_H__
#define __SAVARSET_H__

#include <e32base.h>
#include "saclient.h"

/**
 * The interface to the System Agent for notifying changes to a state
 * variable.
 *
 * Note that after construction, <code>RSystemAgentBase::Connect()</code>
 * must be called before using any of the services provided by this
 * class.
 *
 * @since 5.2
 * @lib "sysagt.lib"
 */
class RSAVarChangeNotify : public RSystemAgentBase
 	{
public:
	IMPORT_C RSAVarChangeNotify();    
	IMPORT_C void NotifySaVarChangeL(const TUid aVariable, const TInt aState);	
	IMPORT_C TInt ReleaseVariable(TUid aVariable);
	};

#endif