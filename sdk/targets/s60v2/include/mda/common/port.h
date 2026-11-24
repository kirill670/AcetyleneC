// Mda\Common\Port.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_COMMON_PORT_H__
#define __MDA_COMMON_PORT_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Port.hrh> // shared defines
#include <Mda\Common\Base.h>

MDA_UID(KUidMdaSourcePort) 
MDA_UID(KUidMdaDestinationPort) 

// Functions

/**
 * @publishedAll
 * @deprecated 
 *
 * TMLbIoFactoryFunctions
 */
enum
	{
	EMLbIoFactoryNewIO=0
	};

/**
 * @publishedAll
 * @deprecated 
 *
 * TMLbPortFunctions
 */
enum
	{
	EMLbPortNewBuffer=EMLbIoFactoryNewIO+1,
	EMLbPortConfig,
	EMLbPortNegotiate
	};

#endif
