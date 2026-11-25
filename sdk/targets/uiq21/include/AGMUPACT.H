// AGMUPACT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMUPACT_H__
#define __AGMUPACT_H__


/**
 * Indicates which instances of a repeating entry are affected when the
 * entry is updated, deleted or cut (see for example
 * <code>CAgnModel::UpdateInstanceL()</code>).
 */
enum TAgnWhichInstances  
		{			
		ECurrentInstance,			/** Only the current instance.*/
		EAllInstances,				/** All instances.*/
		ECurrentAndFutureInstances,	/** The current and all future instances.*/
		ECurrentAndPastInstances	/** The current and all past instances.*/
		};

#endif
