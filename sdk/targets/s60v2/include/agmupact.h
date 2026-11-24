// AGMUPACT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMUPACT_H__
#define __AGMUPACT_H__


/** Indicates which instances of a repeating entry are affected when an instance 
is updated, deleted or cut (see for example CAgnModel::UpdateInstanceL()). 
@publishedAll
@released
*/
enum TAgnWhichInstances  
		{			
		/** Only the current instance. */
		ECurrentInstance,
		/** All instances. */
		EAllInstances,
		/** The current and all future instances. */
		ECurrentAndFutureInstances,
		/** The current and all past instances. */
		ECurrentAndPastInstances
		};

#endif
