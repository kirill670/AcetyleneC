// EIKCMOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCMOBS_H__)
#define __EIKCMOBS_H__

#include <e32def.h>

class CCoeControl;

/**
 *
 * Command observers respond to user commands, and have the secondary
 * function of creating custom controls on request for classes such as
 * <code>CEikToolbar</code>, or user-defined classes.
 *
 * An implementation of the pure virtual function
 * <code>ProcessCommandL()</code> must be provided for each concrete
 * class derived from <code>MEikCommandObserver</code>.
 * <code>CreateCustomCommandControlL()</code> may also be re-implemented.
 *
 * @since 6.0
 * @lib " eikcoctl.lib "
 */
class MEikCommandObserver
	{
public:
	/**
	 * Processes user commands.
	 *
	 * Derived classes must provide an implementation of this function which
	 * responds to user commands appropriately based on a user-defined ID for
	 * the command.
	 *
	 * @param     " TInt aCommandId "
	 *            ID of the command to respond to.
	 */
	virtual void ProcessCommandL(TInt aCommandId)=0;
	IMPORT_C virtual CCoeControl* CreateCustomCommandControlL(TInt aControlType);
	};

#endif
