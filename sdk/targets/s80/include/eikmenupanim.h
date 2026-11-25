/*
* ==============================================================================
*  Name        : eikmenupanim.h
*  Part of     : CKON
*  Interface   : Menubar API
*  Description : Menu pane animator classes
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef EIKMENUPANIM_H
#define EIKMENUPANIM_H

// INCLUDES
#include <coemain.h>

// FORWARD DECLARATIONS
class CEikMenuPane;

/**
 * The MEikMenuPaneDisplayAnimator class defines an interface for classes to start and cancel the
 * animation of the menu pane.
*
* @internal
*  @since 6.0
*/
class MEikMenuPaneDisplayAnimator
    {
    public:

        /**
        * Tell the display animator to animate the opening of the menu pane.
        * @param aMenuPane The menu pane
        * <BR><B>Type of return value:</B> void
        */
        virtual void AnimateOpenL(CEikMenuPane& aMenuPane)=0;

        /**
        * Tell the display animator to animate the closing of the menu pane.
        * @param aMenuPane the menu pane
        * <BR><B>Type of return value:</B> void
        */
        virtual void AnimateClosedL(CEikMenuPane& aMenuPane)=0;
    };




/**
* The CEikMenuPaneDisplayAnimator class implements global static storage and access to the object
* which provides the custom drawing of the menu pane. It provides a function which creates the the
* static object and stores the pointer of the custon animator display.
* This class is used by CEikMenuPane class to re-direct the open and close the menu pane messages
* to the custom animator display.
*
* @internal
*  @lib eikcoctl.lib
*  @since Series90 1.0
*/
class CEikMenuPaneDisplayAnimator : public CCoeStatic
    {
    public:

        /**
        * Installs the custom display animator to aDisplayAnimator in the static storage.
        * If the singleton has not been created yet it gets created before setting the custom
        * display animator. It does not get the ownership of aDisplayAnimator.
        * @param aDisplayAnimator The display animator
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C static void InstallDisplayAnimatorL(MEikMenuPaneDisplayAnimator* aDisplayAnimator);

        static CEikMenuPaneDisplayAnimator* Static();
        void AnimateOpenL(CEikMenuPane& aMenuPane);
        void AnimateClosedL(CEikMenuPane& aMenuPane);
    private:
        CEikMenuPaneDisplayAnimator(MEikMenuPaneDisplayAnimator* aDisplayAnimator);
    private:
        MEikMenuPaneDisplayAnimator* iDisplayAnimator;
    };


#endif  // EIKMENUPANIM_H
// End of File
