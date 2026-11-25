// MCTCertStore.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MCTCERTSTORE_H__
#define __MCTCERTSTORE_H__

#include <cctcertinfo.h>
#include <ccertattributefilter.h>
#include <mcertstore.h>

/** The UID of read-only cert store interfaces */
const TInt KInterfaceCertStore = 0x101F501B;

/** @ingroup interfaces */
/** @{ */

/** A single certificate store. All the details are defined in MCertStore
	as they are shared by the unified cert store.
	@see MCertStore
 */
class MCTCertStore : public MCertStore, public MCTTokenInterface
	{
	};
///@}
#endif
