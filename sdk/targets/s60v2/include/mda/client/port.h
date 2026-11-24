// Mda\Client\Port.h 
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_PORT_H__
#define __MDA_CLIENT_PORT_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Client\Base.h>
#include <Mda\Common\Port.h> // for uids

/**
 * @publishedAll 
 * @deprecated
 *
 * Not used by MMF
 */
class RMdaPort : public RDummyMdaObject
	{
	};

/**
 * @publishedAll 
 * @deprecated
 *
 * Not used by MMF
 */
class RMdaSrcPort : public RMdaPort
	{ // For type safety
	};

/**
 * @publishedAll 
 * @deprecated
 *
 * Not used by MMF
 */
class RMdaDstPort : public RMdaPort
	{ // For type safety
	};

#endif
