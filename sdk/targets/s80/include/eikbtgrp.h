/*
* ==============================================================================
*  Name        : eikbtgrp.h
*  Part of     : CKON
*  Interface   : Button Group API
*  Description : Mixin base class needed by button groups.
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


#ifndef EIKBTGRP_H
#define EIKBTGRP_H

// INCLUDES
#include <e32std.h>

// FORWARD DECLARATIONS
class CCoeControl;
class CEikCommandButton;
class CFbsBitmap;

/**
 *
 * Abstract base class used in the derivation of <code>CEikToolBar</code>, 
 * <code>CEikButtonPanel</code> and others
 *
 * It has no user accessible functions
 *
 * @internal
 * @since 1.2
 * @lib "eikcoctl.lib"
 */
class MEikButtonGroup
    {
    public:

        void Release();

        /**
        * Set a command in this button group.
        * @param aPosition The position of the control in the button group.
        * @param aCommandId The ID of the command.
        * @param aText The button text.
        * @param aBitmap The bitmap for the button.
        * @param aMask The bitmap mask for the button.
        * @remarks
        * @see
        */
        virtual void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;

        /**
        * Set a command in this button group from resources.
        * @param aPosition The position of the control in the button group.
        * @param aResourceId The resource ID for this button.
        * @remarks
        * @see
        */
        virtual void SetCommandL(TInt aPosition,TInt aResourceId)=0;

        /**
        * Sets a button group from resources.
        * @param aResourceId The resource ID of the button group.
        * @remarks
        * @see
        */
        virtual void SetCommandSetL(TInt aResourceId)=0;

        /**
        * Adds a command to the button group.
        * @param aPosition The position of the control in the button group.
        * @param aCommandId The ID of the command.
        * @param aText The button text.
        * @param aBitmap The bitmap for the button.
        * @param aMask The bitmap mask for the button.
        * @remarks
        * @see
        */
        virtual void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;

        /**
        * Adds a command to the button group command stack.
        * @param aPosition The position of the control in the button group.
        * @param aCommandId The ID of the command.
        * @param aText The button text.
        * @param aBitmap The bitmap for the button.
        * @param aMask The bitmap mask for the button.
        * @remarks
        * @see
        */
        virtual void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;

        /**
        * Adds a command to the button group command stack from resources.
        * @param aPosition The position of the control in the button group.
        * @param aResourceId The resource ID for this button.
        * @remarks
        * @see
        */
        virtual void AddCommandToStackL(TInt aPosition,TInt aResourceId)=0;

        /**
        * Adds a command to the button group command stack from resources.
        * @param aResourceId The resource ID of the button group.
        * @remarks
        * @see
        */
        virtual void AddCommandSetToStackL(TInt aResourceId)=0;

        /**
        * Sets the default command of the button group.
        * @param aCommandId The ID of the default command
        * @remarks
        * @see
        */
        virtual void SetDefaultCommand(TInt aCommandId)=0;

        /**
        * Calculates the minimum size of this button group from resources.
        * @param aResourceId The resource ID of the button group.
        * @return The minimum size required to display the button group.
        * @remarks
        * @see
        */
        virtual TSize CalcMinimumSizeL(TInt aResourceId)=0;

        /**
        * Removes a command from the button group and the command stack.
        * @param aPosition The position of the command in the button group.
        * @param aCommandId The ID for this command.
        * @remarks
        * @see
        */
        virtual void RemoveCommandFromStack(TInt aPosition,TInt aCommandId)=0;

        /**
        * Get the position of a command from its ID.
        * @param aCommandId The ID for this command.
        * @return The command position.
        * @remarks
        * @see
        */
        virtual TInt CommandPos(TInt aCommandId) const=0;

        /**
        * Sets the dimmed state of a command button.
        * @param aCommandId The ID of the command.
        * @param aDimmed ETrue if this command button should be dimmed. 
        *        EFalse to undim it.
        * @remarks
        * @see
        */
        virtual void DimCommand(TInt aCommandId,TBool aDimmed)=0;

        /**
        * @param aCommandId The ID of the command.
        * @return ETrue if this command button is dimmed. EFalse if not.
        * @remarks
        * @see
        */
        virtual TBool IsCommandDimmed(TInt aCommandId) const=0;

        /**
        * Sets the visibility of a command button.
        * @param aCommandId The ID of the command.
        * @param aVisible ETrue if the command button should be visible.
        * @remarks
        * @see
        */
        virtual void MakeCommandVisible(TInt aCommandId,TBool aVisible)=0;

        /**
        * @param aCommandId The ID of the command.
        * @return ETrue if the command button is visible.
        * @remarks
        * @see
        */
        virtual TBool IsCommandVisible(TInt aCommandId) const=0;

        /**
        * @return The command button group as a pointer to a CCoeControl.
        * @remarks
        * @see
        */
        virtual CCoeControl* AsControl()=0;

        /**
        * Gets a const pointer to the control group as a CCoeControl
        * @return The command button group as a const pointer to a CCoeControl.
        * @remarks
        * @see
        */
        virtual const CCoeControl* AsControl() const=0;
    // The following methods are only needed for external button groups.

        /**
        * Sets the rectangle that contains the button group.
        * @param aBoundingRect The bounding rectangle.
        * @remarks This is only used for button groups which are positioned 
        *          outside the parent control - for example an AppView which
        *          defines its own CBA
        * @see
        */
        virtual void SetBoundingRect(const TRect& aBoundingRect)=0;
        /**
        *
        * Shrinks a rectangle to exclude the toolbar area.
        * @param aBoundingRect Specifies a rectangle which, on return, is shrunk to
        *            exclude the toolbars extent.
        * @remarks   This function reduces the size of the rectangle passed 
        *            into the function so that on return, the area occupied 
        *            by the toolbar or toolband is removed from the rectangle. 
        *            It is provided to prevent drawing over an existing toolbar
        *            or toolband.
        */
        virtual void ReduceRect(TRect& aBoundingRect) const=0;
    //

        /**
        * Gets a pointer to one of the command buttons.
        * @param aCommandId The ID of the command.
        * @return Pointer to the command button control.
        * @remarks
        * @see
        */
        virtual CCoeControl* GroupControlById(TInt aCommandId) const=0;

        /**
        * Gets a pointer to one of the command buttons.
        * @param aCommandId The ID of the command.
        * @return Pointer to the command button.
        * @remarks
        * @see
        */
        virtual CEikCommandButton* GroupControlAsButton(TInt aCommandId) const=0;

        /**
        * Get the command ID for the button at a particular position in the button group.
        * @param aCommandPos The position index of the button.
        * @return The ID of the command button.
        * @remarks
        * @see
        */
        virtual TInt CommandId(TInt aCommandPos) const=0;

        /**
        * The number of buttons in the group
        * @return The number of buttons in the group.
        * @remarks
        * @see
        */
        virtual TInt ButtonCount() const=0;

        /**
        * @return The flags of the button group.
        * @remarks This is provided as a utility method; the flags and their
        *          meanings are specified by the class which implements
        *          <code>MEikButtonGroup</code>
        * @see
        */
        virtual TUint ButtonGroupFlags() const=0;
    private:
        IMPORT_C void Reserved_1();
    };


#endif  // EIKBTGRP_H

// End of File
