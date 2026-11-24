// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedPartner
@released
*/

#ifndef CLIENTTYPE_H
#define CLIENTTYPE_H

/**
Client type enumeration.
*/
enum TRemConClientType
	{
	/** Undefined client type. */
	ERemConClientTypeUndefined = 0,

	/** Controller. */
	ERemConClientTypeController,

	/** Target. */
	ERemConClientTypeTarget,
	};

#endif // CLIENTTYPE_H
