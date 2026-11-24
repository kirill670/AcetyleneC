//
// Copyright (c) 2001 Symbian Software Ltd.  All rights reserved.
//

/** 
 * @file 
 * Global header file for the crypto token framework.
 * 
 * Include this header file and you should have everything you'll need
 * to use the CryptoToken framework. Look inside the included header
 * files to find out details of the classes.
 */

#ifndef __CT_H__
#define __CT_H__

#include <e32std.h>
#include <e32base.h>

#include <ct/TCTTokenTypeAttribute.h>
#include <ct/CCTTokenTypeInfo.h>
#include <ct/MCTTokenTypeFilter.h>
#include <ct/TCTAllTokenTypes.h>
#include <ct/TCTFindTokenTypesByInterface.h>
#include <ct/TCTFindTokenTypesByInterfaceAndAttribute.h>
#include <ct/CCTTokenType.h>
#include <ct/MCTToken.h>
#include <ct/MCTTokenInterface.h>
#include <ct/RMPointerArray.h>
#include <ct/RCPointerArray.h>
#include <securitydefs.h>

/** 
 *	@defgroup ct Crypto Token Framework 
 */

/** 
 *	@defgroup array Owning pointer arrays
 *
 *	These are pointer array classes that own their contents.
 *	Close() releases the array, and also releases the contents.
 */

/** 
 *	@defgroup interfaces Token Interfaces
 *
 *	These are classes defining particular interfaces which tokens
 *	might implement. Other interfaces may be defined by 3rd parties.
 */

//__CT_H__
#endif
