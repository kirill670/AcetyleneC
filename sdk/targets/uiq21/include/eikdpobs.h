// EIKDPOBS.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKDPOBS_H__
#define __EIKDPOBS_H__

#ifndef __EIKFCTRY_H__
#include <eikfctry.h>
#endif


/**
 * The MEikDialogPageObserver class specifies an interface through which the behaviour of the pages of
 * a dialog may be observed.
 *
 * @since ER5U
 */
class MEikDialogPageObserver
	{
public:

	/**
	 * Prepares for focus transition from the current line e.g. to validate the
	 * contents of the current control.
	 */
	virtual void PrepareForFocusTransitionL()=0;

	/**
	 * Takes any action required when the active dialog page is changed to aPageId.
	 */
	virtual void PageChangedL(TInt aPageId)=0;

	/**
	 * Takes any action required when the current line is changed to aControlId.
	 */
	virtual void LineChangedL(TInt aControlId)=0;

	/**
	 * Creates a custom control of type aControlType and returns the control information for the custom control
	 * which is created. Called when creating a line on the dialog page if the Eikon control factory does not
	 * recognise the type aControlType.
	 */
	virtual SEikControlInfo CreateCustomControlL(TInt aControlType)=0;

	/**
	 * Processes a button command from a button within the page button bar.
	 */
	virtual void ProcessPageButtonCommandL(TInt aCommandId)=0;

	/**
	 * Gets the custom auto value for the custom control aControl of type aControlType with return value
	 * aReturnValue. This method is included in the interface to support deprecated legacy code only.
	 * @deprecated
	 */
//	virtual void GetCustomAutoValue(TAny* aReturnValue,TInt aControlType,const CCoeControl* aControl)=0;
	};

#endif
