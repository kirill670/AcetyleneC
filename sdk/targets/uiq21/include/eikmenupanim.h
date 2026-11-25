// EIKMENUPANIM.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKMENUPANIM_H__
#define __EIKMENUPANIM_H__

#include <coemain.h>


/**
 * The MEikMenuPaneDisplayAnimator class defines an interface for classes to start and cancel the
 * animation of the menu pane.
 *
 * @internal
 * @since App-Framework_6.2
 */
class MEikMenuPaneDisplayAnimator
	{
public:
	virtual void AnimateOpenL(CEikMenuPane& aMenuPane)=0;
	virtual void AnimateClosedL(CEikMenuPane& aMenuPane)=0;
	};



class CEikMenuPane;

/**
 * The CEikMenuPaneDisplayAnimator class implements global static storage and access to the object
 * which provides the custom drawing of the menu pane. It provides a function which creates the the
 * static object and stores the pointer of the custon animator display.
 * This class is used by CEikMenuPane class to re-direct the open and close the menu pane messages
 * to the custom animator display.
 *
 * @internal
 * @since App-Framework_6.2
 */
class CEikMenuPaneDisplayAnimator : public CCoeStatic
	{
public:
	IMPORT_C static void InstallDisplayAnimatorL(MEikMenuPaneDisplayAnimator* aDisplayAnimator);
public:
	static CEikMenuPaneDisplayAnimator* Static();
public:
	void AnimateOpenL(CEikMenuPane& aMenuPane);
	void AnimateClosedL(CEikMenuPane& aMenuPane);
private:
	CEikMenuPaneDisplayAnimator(MEikMenuPaneDisplayAnimator* aDisplayAnimator);
private:
	MEikMenuPaneDisplayAnimator* iDisplayAnimator;
	};

#endif