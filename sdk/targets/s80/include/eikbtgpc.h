/*
* ==============================================================================
*  Name        : eikbtgpc.h
*  Part of     : CKON
*  Interface   : Button Group API
*  Description : Button group container class
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

#ifndef EIKBTGPC_H
#define EIKBTGPC_H

// INCLUDES
#include <coecntrl.h>
#include <eikbtgrp.h>
#include <eikcmobs.h>
#include <lafpublc.h>
#include <uikon.hrh>

// FORWARD DECLARATIONS
class MEikCommandObserver;
class CEikButtonGroupStack;
class CEikCommandButton;

/**
 * The <code>CEikButtonGroupContainer</code> provides a wrapper around the 
 * different button arrays used in both pen and no-pen devices. Requesting 
 * <code>aUse</code> as either <code>EView</code> or <code>EDialog</code> 
 * will create the default button set for the host device. The other options 
 * are included primarily for testing.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikButtonGroupContainer : public CCoeControl, public MEikCommandObserver
    {
    public:
    /**
     * The enumeration <code>TUse</code> describes how the container is being 
     * used. It is used by the system to create the appropriate (DFRD-specific)
     * Button Group for the specified type. From version 6.1, only two use
     * types can be specified: <code>EView</code> or <code>EDialog</code>.
     */
    enum TUse
        {
        /** in a view */
        EView               =SLafButtonGroupContainer::EView,           
        /** in a dialog */
        EDialog             =SLafButtonGroupContainer::EDialog,         
        /** @deprecated */
        EToolbar            =SLafButtonGroupContainer::EToolbar,        
        /** @deprecated */
        ECba                =SLafButtonGroupContainer::ECba,            
        /** @deprecated */
        EDialogButtons      =SLafButtonGroupContainer::EDialogButtons,  
        /** @deprecated */
        EDeviceCustomStart  =0x100000, 
        /** @deprecated */
        EDeviceCustomEnd    =0x800000
        };

    /**
     * The enumeration <code>TOrientation</code> describes the orientation of 
     * the container.
     */
    enum TOrientation
        {
        /** buttons are laid out vertically */
        EVertical   =SLafButtonGroupContainer::EVertical,   
        /** buttons are laid out horizontally */
        EHorizontal =SLafButtonGroupContainer::EHorizontal  
        };

    /**
     * The enumeration <code>TLocation</code> describes the relative positions
     * of the container and the control that uses it.
     */
    enum TLocation
        {
        /** for example, dialog buttons */
        EInternal   =SLafButtonGroupContainer::EInternal,   
        /** for example, the toolbar or CBA */
        EExternal   =SLafButtonGroupContainer::EExternal    
        };

    /**
     * The enumeration <code>THotKeyFlags</code> provides the flags for the 
     * display of hotkeys.
     */
    enum THotKeyFlags
        {
        /** the hotkeys for commands should be shown */
        EShowHotKey         =0x01,  
        /** the hotkeys for commands should not be shown */
        EPlainHotKey        =0x02   
        };

    /** The Button Group's flags */
    enum TFlags
        {
        /** add Button Group to Button Group stack */
        EAddToStack         =0x01,
        /** 
        * do not call <code>ActivateL()</code> on the Button Group on 
        * creation 
        */
        EDelayActivation    =0x02,
        /** 
        * use the width specified by 
        * <code>ESkinConstCommandBarMaxWidth</code> (for CBA) 
        */
        EUseMaxSize         =0x04
        };
    public:
        
       /**
        * Creates a Button Group container in its own window. 
        *
        * @param aUse The Button Group's type. Specifying this as either
        *             <code>EView</code> or <code>EDialog</code> creates the
        *             default button set for the host device. The other
        *             options are included primarily for testing
        * @param aOrientation The Button Group's orientation
        * @param aCommandObserver A command observer to be notified of commands on 
        *                         the container. Ownership is not passed to 
        *                         this class
        * @param aResourceId A resource containing descriptions of buttons in the
        *                    group. This can be <code>NULL</code> if buttons are to 
        *                    be added dynamically
        * @param aFlags The Button Group's flags. Valid values are:
        *               <code>EAddToStack =0x01</code>;
        *               <code>EDelayActivation =0x02</code>
        *               <code>EUseMaxSize =0x04</code>
        *               The values may be OR'ed together
        * @return the Button Group container object
        * @remarks
        * @see
        */
        IMPORT_C static CEikButtonGroupContainer* NewL(TUse aUse,TOrientation aOrientation,
                                                    MEikCommandObserver* aCommandObserver,TInt aResourceId,
                                                    TUint aFlags=EAddToStack);
    
       /**
        * Creates a Button Group container in its own window, or if specified, 
        * in its parent control's window.
        *
        * @param aUse The Button Group's type. Specifying this as either 
        *             <code>EView</code> or <code>EDialog</code> creates the 
        *             default button set for the host device; the other options are 
        *             included primarily for testing
        * @param aOrientation The Button Group's orientation. This only needs to be
        *                     specified for devices that can lay out their buttons 
        *                     either horizontally or vertically
        * @param aCommandObserver A command observer to be notified of commands on 
        *                         the container. Ownership is not passed to 
        *                         this class
        * @param aResourceId A resource containing descriptions of buttons in the
        *                    group. This can be <code>NULL</code> if buttons are to 
        *                    be added dynamically
        * @param aParent The control's parent
        * @param aFlags The Button Group's flags. Valid values are:
        *               <code>EAddToStack =0x01</code>;
        *               <code>EDelayActivation =0x02</code>
        *               <code>EUseMaxSize =0x04</code>
        *               The values may be OR'ed together
        * @return the Button Group container object
        * @remarks
        * @see
        */
        IMPORT_C static CEikButtonGroupContainer* NewL(TUse aUse,TOrientation aOrientation,
                                                    MEikCommandObserver* aCommandObserver,TInt aResourceId,
                                                    const CCoeControl& aParent,TUint aFlags=EAddToStack);

       /**
        * The object destructor.
        */
        IMPORT_C ~CEikButtonGroupContainer();

       /**
        * Gets a pointer to an application's currently active
        * <code>CEikButtonGroupContainer</code> (if any). This method returns 
        * <code>NULL</code> if there are no containers active or none suitable 
        * for sharing. Ownership of the returned pointer is not transferred.
        *
        * @return the Button Group container
        * @remarks Returns <code>NULL</code> if there are no containers active 
        *          or none suitable for sharing. Ownership of the returned 
        *          Button Group container is not transferred
        */
        IMPORT_C static CEikButtonGroupContainer* Current();

        /**
        * Checks whether a Button Group is in the Button Group control stack.
        *
        * @param aBgc a Button Group
        * @return <code>ETrue</code> if <code>aBgc</code> is in the Button 
        *         Group control stack
        * @remarks
        * @see
        */
        IMPORT_C static TBool ButtonGroupInStack(const CEikButtonGroupContainer* aBgc);
    public:

       /**
        * Sets a command button's content, overwriting any previous contents at
        * that position. There are several overloads of this method, which 
        * allow the command button's image and text to be set (optional). 
        * If the supplied position is out 
        * of range a panic is raised. 
        *
        * @param aPosition The position within the Button Group
        * @param aCommandId The command ID that the new button will generate 
        *                   when tapped
        * @param aText The text for the button
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText);

       /**
        * Sets a command button's content, overwriting any previous contents.
        * The button is identified by its position.
        * A panic is raised if the supplied position is out 
        * of range.  
        * Ownership of 
        * bitmap arguments is transferred at the end of the method. 
        *
        * @param aPosition The position within the Button Group
        * @param aCommandId The command ID that the new button will send
        * @param aBitmap The bitmap for the button
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void SetCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);

       /**
        * Sets a command button's content, overwriting any previous contents.
        * The button is identified by its position.
        * A panic is raised if the supplied position is out 
        * of range.  
        * Ownership of 
        * bitmap arguments is transferred at the end of the method. 
        *
        * @param aPosition The position within the Button Group
        * @param aCommandId The command ID that the button will send
        * @param aText The text for the button
        * @param aBitmap The bitmap for the button
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);

       /**
        * Sets a command button's content, overwriting any previous contents.
        * The button is identified by its position.
        * A panic is raised if the supplied position is out 
        * of range.  
        *
        * @param aPosition The position within the Button Group
        * @param aCommandId The command ID that the button will send
        * @param aFile multi-bitmap file containing mask and bitmap images
        * @param aBitmapId The index within <code>aFile</code> of the image 
        *                  bitmap
        * @param aMaskId The index within <code>aFile</code> of a single-plane
        *                bitmap to use as the mask
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

       /**
        * Sets a command button's content, overwriting any previous contents.  
        * The button is identified by its position.
        * A panic is raised if the supplied position is out 
        * of range.  
        *
        * @param aPosition The position within the Button Group
        * @param aCommandId The command ID that the button will send
        * @param aText The text for the button
        * @param aFile multi-bitmap file containing mask and bitmap images
        * @param aBitmapId The index within <code>aFile</code> of the image 
        *                  bitmap
        * @param aMaskId The index within <code>aFile</code> of a single-plane
        *                bitmap to use as the mask
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

        /**
        * Sets a command button's content, overwriting any previous contents. 
        * The button is identified by its position.
        * A panic is raised if the supplied position is out 
        * of range.  
        *
        * @param aPosition The position within the Button Group
        * @param aResourceId The ID of a resource specifying the text, bitmaps 
        *                    and command ID
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void SetCommandL(TInt aPosition,TInt aResourceId);

        /**
        * Sets a command button's text, overwriting the previous text.
        * The button is identified by its command ID.
        * If two buttons have the same ID, which one will be altered is not 
        * defined. The behavior is also undefined if <code>aCommandId</code> 
        * cannot be matched to any button. 
        *
        * @param aCommandId The command ID that the new button will send
        * @param aText The text for the button
        * @remarks
        * @see
        */
        inline void SetCommandL(TInt aCommandId,const TDesC& aText);

        /**
        * Sets a command button's content, overwriting any previous contents.
        * The button is identified by its command ID.
        * Ownership of 
        * bitmap arguments is transferred at the end of the method.  
        * If two buttons have the same ID, which one will be altered is not 
        * defined. The behavior is also undefined if <code>aCommandId</code> 
        * cannot be matched to any button. 
        *
        * @param aCommandId The command ID that the new button will send
        * @param aBitmap The bitmap for the button
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks Ownership of the bitmap arguments is transferred, so they
        *          are needed on the cleanup stack
        * @see
        */
        inline void SetCommandL(TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);

        /**
        * Sets a command button's content, overwriting any previous contents at
        * that position. There are several overloads of this method, which 
        * allow the command button's image and text to be set. 
        * Ownership of 
        * bitmap arguments is transferred at the end of the method.  
        * If two buttons have the same ID, which one will be altered is not 
        * defined. The behavior is also undefined if <code>aCommandId</code> 
        * cannot be matched to any button. 
        *
        * @param aCommandId The command ID that the new button will send
        * @param aText The text for the button
        * @param aBitmap The bitmap for the button
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks Ownership of the bitmap arguments is transferred, so they
        *          are needed on the cleanup stack
        * @see
        */
        inline void SetCommandL(TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);

        /**
        * Sets a command button's content, overwriting any previous contents.
        * The button is identified by its command ID.
        * Both the image and mask must be specified to 
        * guarantee compliance with different color schemes. Ownership of 
        * bitmap arguments is transferred at the end of the method.  
        * If two buttons have the same ID, which one will be altered is not 
        * defined. The behavior is also undefined if <code>aCommandId</code> 
        * cannot be matched to any button. 
        *
        * @param aCommandId The command ID that the new button will send
        * @param aFile multi-bitmap file containing mask and bitmap images
        * @param aBitmapId The index within <code>aFile</code> of the image 
        *                  bitmap
        * @param aMaskId The index within <code>aFile</code> of a single-plane
        *                bitmap to use as the mask
        * @remarks
        * @see
        */
        inline void SetCommandL(TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

        /**
        * Sets a command button's content, overwriting any previous contents.
        * The button is identified by its command ID.
        * Both the image and mask must be specified to 
        * guarantee compliance with different color schemes. Ownership of 
        * bitmap arguments is transferred at the end of the method. 
        * If two buttons have the same ID, which one will be altered is not 
        * defined. The behavior is also undefined if <code>aCommandId</code> 
        * cannot be matched to any button. 
        *
        * @param aCommandId The command ID that the button will send
        * @param aText The text for the button
        * @param aFile multi-bitmap file containing mask and bitmap images
        * @param aBitmapId The index within <code>aFile</code> of the image 
        *                  bitmap
        * @param aMaskId The index within <code>aFile</code> of a single-plane
        *                bitmap to use as the mask
        * @remarks
        * @see
        */
        inline void SetCommandL(TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

       /**
        * Sets the buttons' text, bitmaps and command IDs from a resource. The 
        * type of resource depends on the type of button.
        *
        * @param aResourceId The ID of the resource structure specifying the 
        *                    command buttons
        * @remarks
        * @see
        */
        IMPORT_C void SetCommandSetL(TInt aResourceId);

       /**
        * Adds a command button at the specified position in the container. 
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aText The text for the button
        * @remarks
        * @see
        */
        inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText);

       /**
        * Adds a command button with a bitmap at the specified position 
        * in the container. 
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aBitmap The bitmap for the button 
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks
        * @see
        */
        inline void AddCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);

       /**
        * Adds a command button with a bitmap and text at the specified position 
        * in the container. 
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aText The text for the button
        * @param aBitmap The bitmap for the button 
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks Ownership of the bitmap arguments is transferred, so they
        *          are needed on the cleanup stack
        *          To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
       /**
        * Adds a button containing the bitmaps specified at <code>aPosition</code>.
        * This method panics if <code>aPosition</code> is out of range.
        * 
        * @since ER5U 
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button
        * @param aFile The file containing the bitmap and any mask for the 
        *              button
        * @param aBitmapId The ID of the bitmap, within <code>aFile</code>, 
        *                  for the button 
        * @param aMaskId The ID of the mask, within <code>aFile</code>, for 
        *                the button
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

       /**
        * Adds a command button at the specified position in the container. 
        * The button may have an optional text string or a bitmap image. 
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aText The text for the button
        * @param aFile The file containing the bitmap and any mask for the 
        *              button
        * @param aBitmapId The ID of the bitmap, within <code>aFile</code>, 
        *                  for the button 
        * @param aMaskId The ID of the mask, within <code>aFile</code>, for 
        *                the button
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

       /**
        * Adds a command to the top of a position's button stack. The 
        * command which was previously at the top can be restored to the top 
        * by calling <code>RemoveCommand()</code>.
        * This method panics if <code>aPosition</code> is out of range.
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aText The text for the button
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText);

       /**
        * Adds a command to the top of a position's button stack. The 
        * command which was previously at the top can be restored to the top 
        * by calling <code>RemoveCommand()</code>.
        * This method panics if <code>aPosition</code> is out of range.
        * Ownership of 
        * bitmap arguments is transferred at the end of the method.  
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aBitmap The bitmap for the button
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);

       /**
        * Adds a command to the top of a position's button stack. The 
        * command which was previously at the top can be restored to the top 
        * by calling <code>RemoveCommand()</code>.
        * This method panics if <code>aPosition</code> is out of range.
        * Ownership of 
        * bitmap arguments is transferred at the end of the method.  
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aText The text for the button
        * @param aBitmap The bitmap for the button
        * @param aMask The mask bitmap for <code>aBitmap</code>
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);

       /**
        * Adds a command to the top of a position's button stack. The 
        * command which was previously at the top can be restored to the top 
        * by calling <code>RemoveCommand()</code>.
        * This method panics if <code>aPosition</code> is out of range.
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aFile The file containing the bitmap and any mask for the 
        *              button
        * @param aBitmapId The ID of the bitmap, within <code>aFile</code>, 
        *                  for the button 
        * @param aMaskId The ID of the mask, within <code>aFile</code>, for 
        *                the button
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

       /**
        * Adds a command to the top of a position's button stack. The 
        * command which was previously at the top can be restored to the top 
        * by calling <code>RemoveCommand()</code>.
        * This method panics if <code>aPosition</code> is out of range.
        *
        * @param aPosition The position for the new button 
        * @param aCommandId The command ID for the new button 
        * @param aText The text for the button
        * @param aFile The file containing the bitmap and any mask for the 
        *              button
        * @param aBitmapId The ID of the bitmap, within <code>aFile</code>, 
        *                  for the button 
        * @param aMaskId The ID of the mask, within <code>aFile</code>, for 
        *                the button
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);

       /**
        * Adds a command to the top of a position's button stack. The 
        * command which was previously at the top can be restored to the top 
        * by calling <code>RemoveCommand()</code>.
        * This method panics if <code>aPosition</code> is out of range.
        *
        * @param aPosition The position for the new button 
        * @param aResourceId The ID of a resource specifying the text, bitmaps, 
        * and command ID
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        inline void AddCommandToStackL(TInt aPosition,TInt aResourceId);

       /**
        * This method is like <code>SetCommandL()</code> but is for a set of 
        * buttons.
        *
        * @param aResourceId The resource describing the set of command buttons
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        IMPORT_C void AddCommandSetToStackL(TInt aResourceId);

       /**
        * Removes the command identified by <code>aCommandId</code>, in 
        * position <code>aPosition</code> in the group, from the command stack.
        * The method automatically retrieves the previous command details. 
        * Commands are added to the stack by calling 
        * <code>AddCommandToStackL</code>.
        *
        * @param aPosition The position in the group 
        * @param aCommandId The command ID
        * @remarks To make sure that an invalid position does not make the 
        *          method panic, check that <code>aPosition</code> is less than 
        *          <code>ButtonCount()</code>
        * @see
        */
        IMPORT_C void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);

       /**
        * Sets the default command ID for buttons in this container.
        *
        * @param aCommandId The command to issue if no other is specified
        * @remarks
        * @see
        */
        IMPORT_C void SetDefaultCommand(TInt aCommandId); 

       /**
        * Calculates the minimum size required to display the buttons defined 
        * in the specified resource structure.
        *
        * @param aResourceId The ID of the resource structure describing the 
        *                    button group
        * @return the minimum size required to display the Button Group defined 
        *         in the specified resource structure
        * @remarks
        * @see
        */
        IMPORT_C TSize CalcMinimumSizeL(TInt aResourceId) const;

       /**
        * Places the command in position <code>aPosition</code> in the group 
        * on the cleanup stack. Typically, this method is used when a control 
        * or view changes the contents of two or more buttons on receipt of 
        * focus. After altering one command with a call to 
        * <code>AddCommandToStackL()</code>, the push is made to guarantee the 
        * display will be left in a consistent state if the second (and any 
        * subsequent) calls to <code>AddCommandToStackL()</code> fail. Only a 
        * single command can be pushed for each position. 
        * 
        * @param aPosition The position in the container of the button to push
        * @remarks
        * @see
        */
        IMPORT_C void CleanupCommandPushL(TInt aPosition);

       /**
        * Removes a command from the cleanup stack without destroying it.
        *
        * @remarks
        * @see
        */
        inline void CleanupCommandPop();

       /**
        * Removes one or more commands from the cleanup stack without destroying
        * them. 
        *
        * @param aCount The number of commands to pop
        * @remarks
        * @see
        */
        IMPORT_C void CleanupCommandPop(TInt aCount);

       /**
        * Removes a command that was pushed onto the cleanup stack. It does 
        * this by calling <code>CleanupCommandPushL()</code>, rolling back to 
        * the previous details. The command buttons popped are destroyed.
        *
        * @remarks
        * @see
        */
        inline void CleanupCommandPopAndDestroy();

       /**
        * Removes one or more command that were pushed onto the cleanup stack.
        * It does this by calling <code>CleanupCommandPushL()</code>, rolling
        * back to the previous details. The command buttons popped are 
        * destroyed.
        *
        * @param aCount The number of commands to pop and destroy
        * @remarks
        * @see
        */
        inline void CleanupCommandPopAndDestroy(TInt aCount);

       /**
        * Gets the maximum number of buttons that can be supported by the
        * device. 
        * 
        * @return the number of command buttons supported
        * @remarks
        * @see
        */
        IMPORT_C TInt MaxCommands() const;

       /**
        * Gets the total number of buttons currently present in the group.
        *
        * @return the number of buttons
        * @remarks
        * @see
        */
        IMPORT_C TInt ButtonCount() const;

       /**
        * Dims or undims a button without drawing it. If two buttons in the 
        * container have the same ID, the behavior is undefined. Dimming 
        * prevents acceptance of user input. 
        *
        * @param aCommandId The command ID of the button to change
        * @param aDimmed <code>ETrue</code> to dim the specified command. 
        *                <code>EFalse</code> to undim the specified command
        * @remarks
        * @see
        */
        IMPORT_C void DimCommand(TInt aCommandId,TBool aDimmed);

       /**
        * Determines whether the button with the specified command ID is 
        * dimmed. This method returns <code>ETrue</code> if the button with 
        * the specified command ID is dimmed. If two buttons have the same ID,
        * the results of this check are undefined.
        *
        * @param aCommandId The command ID
        * @returns <code>ETrue</code> if the specified command is dimmed; 
        *          <code>EFalse</code> if the specified command is not dimmed
        * @remarks
        * @see
        */
        IMPORT_C TBool IsCommandDimmed(TInt aCommandId) const;

       /**
        * Makes the button with the specified ID either visible or invisible.
        * If two buttons have the same ID, the button to be altered is 
        * undefined. 
        * 
        * @param aCommandId Specifies the button to alter
        * @param aVisible <code>ETrue</code> to make the specified button 
        *                 visible. <code>EFalse</code> to make the specified
        *                 button invisible
        * @remarks
        * @see
        */
        IMPORT_C void MakeCommandVisible(TInt aCommandId,TBool aVisible);

       /**
        * Tests whether the button with the specified command ID is visible. 
        * If two buttons have the same ID, the results are undefined. 
        * 
        * @param aCommandId Specifies the button
        * @return <code>ETrue</code> if the specified button is visible.
        *         <code>EFalse</code> if the specified button is not visible
        * @remarks
        * @see
        */
        IMPORT_C TBool IsCommandVisible(TInt aCommandId) const;

       /**
        * Animates the button with the specified ID, so that it appears to have
        * been pressed and then released.
        * If two buttons have the 
        * same ID, this method's behavior is undefined. 
        *
        * @param aCommandId The button to animate
        * @remarks
        * @see
        */
        IMPORT_C void AnimateCommand(TInt aCommandId);

       /**
        * Gets the Button Group's location. Typically, the Button Group is 
        * external to the view that is using it. In some cases, such as in 
        * dialogs with button panels, the Button Group is internal to the 
        * control that is using it. 
        *
        * @return the Button Group's location
        * @remarks
        * @see
        */
        IMPORT_C TLocation Location() const;

       /**
        * Gets a pointer to the command button with the specified command ID.
        *
        * @since 6.1
        * @param aCommandId The command ID of the button
        * @return a command button <code>CEikCommandButton</code> 
        *         or <code>NULL</code> if there was no button with ID
        *         <code>aCommandId</code>
        * @remarks
        * @see
        */
        IMPORT_C CEikCommandButton* CommandButtonOrNull(TInt aCommandId) const;
    // For use by EExternal Button Groups only.

       /**
        * Sets the boundary rectangle for externally-positioned Button Groups.
        * For use by <code>EExternal</code> Button Groups only.
        *
        * @param aRect The boundary rectangle to use. The Button Group attaches
        *              itself to the inside of this rectangle 
        * @remarks
        * @see
        */
        IMPORT_C void SetBoundingRect(const TRect& aRect);

       /**
        * Subtracts the area occupied by the Button Group from the specified
        * bounding rectangle. This method should be used at all times rather 
        * than querying the container's area.
        *
        * @param aBoundingRect The rectangle to be modified
        * @remarks
        * @see
        */
        IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
    //

       /**
        * Gets a pointer to the control (button) with the specified command ID.
        * This method is intended to allow access to standard 
        * <code>CCoeControl</code> functionality only. Casting the return value
        * is likely to fail on different devices since the derived 
        * controls may not be the same in every case.
        *
        * @param aCommandId The command ID of the button to get
        * @return a <code>CCoeControl</code> or <code>NULL</code>
        *         if there was no button at <code>aCommandId</code>
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* ControlOrNull(TInt aCommandId) const;

       /**
        * Gets a pointer to the button with the specified command ID. This 
        * method may return <code>NULL</code> on some devices as the number 
        * of buttons may vary e.g. in the Command Bar.
        *
        * @param aCommandId The command ID of the button to obtain
        * @return the button object with the specified command ID, or NULL
        *         if no button has the command ID
        * @remarks
        * @see
        */
        IMPORT_C CEikCommandButton* ButtonById(TInt aCommandId) const;

       /**
        * Gets the position in the group of the button with the specified 
        * command ID. The return value is undefined if two buttons share the 
        * same ID. 
        *
        * @param aCommandId Identifies the command
        * @return the command's container position, or KErrNotFound if no button
        *         has the command ID
        * @remarks
        * @see
        */
        IMPORT_C TInt PositionById(TInt aCommandId) const;

       /**
        * Updates a command's hotkey and whether the key is displayed.
        * This method is only supported by containers being used for dialog
        * buttons. 
        *
        * @param aCommandId Identifies the command to update
        * @param aFlags Whether to display the hotkey 
        * @param aKeyId The hotkey identifier
        * @remarks
        * @see
        */
        IMPORT_C void UpdateHotKey(TInt aCommandId,THotKeyFlags aFlags,TInt aKeyId);

       /**
        * Changes the command observer for the button at <code>aPos</code> to
        * <code>aCommandObserver</code>. This method panics if an updated 
        * observer is already present. This method should be followed by 
        * <code>RemoveCommandObserver()</code> when you need to restore the 
        * original observer. 
        *
        * @param aPos The button's position
        * @param aCommandObserver The command observer
        * @remarks Ownership of the supplied command observer is not transferred
        * @see
        */
        IMPORT_C void UpdateCommandObserverL(TInt aPos,MEikCommandObserver& aCommandObserver);

       /**
        * Removes the temporary observer for the button at <code>aPos</code>,
        * replacing it with the observer that was present when 
        * <code>UpdateCommandObserverL()</code> was called.
        *
        * @param aPos The button's position
        * @remarks
        * @see
        */
        IMPORT_C void RemoveCommandObserver(TInt aPos);

       /**
        * Determines whether the Button Group has been explicitly instructed 
        * to suppress redraws. Some Button Groups may not activate themselves 
        * during construction, in which case, they need to be activated by the 
        * client. This method allows the client to enquire whether this is 
        * necessary.
        *
        * @return <code>ETrue</code> if the Button Group will suppress
        *         redraws; otherwise <code>EFalse</code>
        * @remarks
        * @see
        */
        IMPORT_C TBool DelayActivation() const;

       /**
        * Gets the command ID in the group of the button at the specified
        * position.
        *
        * @param aPosition Identifies the position
        * @return the command ID corresponding to the position
        * @remarks
        * @see
        */
        IMPORT_C TInt IdByPosition(TInt aPosition) const;

       /**
        * Returns the Button Group 
        *
        * @return the Button Group as a <code>CCoeControl</code> class
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* ButtonGroupAsControl();
    public: // from CCoeControl

        /**
        * Gets the minimum size for the <code>CEikButtonGroupContainer</code> 
        * object.
        * 
        * @return the minimum size of the <code>CEikButtonGroupContainer</code> 
        *         object
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();

       /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        
        /** @internal */
        void MakeVisible(TBool aVisible);

       /**
        * Writes the internal state of the control and its components to 
        * <code>aStream</code>. This method does nothing in release mode. 
        * It is intended to be overridden and the base called by subclasses.
        *
        * @internal
 * @since App-Framework_6.1
 */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private:
    enum TCommandOp {ESet, EAdd, EPush};
    private:
/**
*  
*  A data structure used in the command stack, containing a command and its position in the stack.
*
*/
    class TCmdPos
        {
    public:

        /**
        * C++ default constructor.
        */
        inline TCmdPos();

        /**
        * C++ default constructor.
        */
        inline TCmdPos(TInt aPos,TInt aCmd);
    public:
        TInt iPos;
        TInt iCmd;
        };
/**
*  A data structure used in the command observer stack, containing a command 
*  observer and its position in the stack.
*
*/
    class TCmdObserver
        {
    public:

        /**
        * C++ default constructor.
        */
        inline TCmdObserver(TInt aPos,MEikCommandObserver& aObserver);
    public:
        TInt iPos;
        MEikCommandObserver& iObserver;
        };
/**
*  Array of command observers.
*/
    class CCmdObserverArray : public CArrayFixFlat<TCmdObserver>
        {
    public:

        /**
        * C++ default constructor.
        */
        inline CCmdObserverArray();
        TInt FindIndex(TInt aPos);
        };
    private:
        CEikButtonGroupContainer(TUse aUse);
        void ConstructL(TOrientation aOrientation,MEikCommandObserver* aCommandObserver,TInt aResourceId,TUint aFlags);
        IMPORT_C void DoSetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask,TCommandOp aOp);
        IMPORT_C void DoSetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId,TCommandOp aOp);
        IMPORT_C void DoSetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask,TCommandOp aOp);
        IMPORT_C void DoSetCommandL(TInt aCommandId,const TDesC* aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId,TCommandOp aOp);
        IMPORT_C void DoSetCommandL(TInt aPosition,TInt aResourceId,TCommandOp aOp);
        inline CCoeControl* ButtonGroupAsControl() const;
        void UpdateRect();
        static void CleanupCommandDestroy(TAny* aPtr);
        TCmdPos DoCleanupCommandPop();
        void DoCleanupCommandPopAndDestroy();
    private: // from CCoeControl
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void SizeChanged();
    private: // from MEikCommandObserver
        void ProcessCommandL(TInt aCommandId);
        CCoeControl* CreateCustomCommandControlL(TInt aControlType);
    private:
        MEikButtonGroup* iButtonGroup;
        TUse iUse;
        CArrayFix<TCmdPos>* iCommandsCleanup;
        MEikCommandObserver* iCommandObserver;
        CCmdObserverArray* iObserverArray;
        TDblQueLink iBtLink;
    private:
    friend class CCmdObserverArray;
    friend class CEikButtonGroupStack;
    };

inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText)
    {DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aResourceId)
    {DoSetCommandL(aPosition,aResourceId,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText)
    {DoSetCommandL(aCommandId,&aText,NULL,NULL,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aCommandId,NULL,&aBitmap,&aMask,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aCommandId,&aText,&aBitmap,&aMask,ESet);}


inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aCommandId,NULL,aFile,aBitmapId,aMaskId,ESet);}

inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aCommandId,&aText,aFile,aBitmapId,aMaskId,ESet);}

inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText)
    {DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,EAdd);}

inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,EAdd);}

inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,EAdd);}

inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,EAdd);}

inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,EAdd);}

inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText)
    {DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,EPush);}

inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,EPush);}

inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
    {DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,EPush);}

inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,EPush);}

inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
    {DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,EPush);}

inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aResourceId)
    {DoSetCommandL(aPosition,aResourceId,EPush);}

inline void CEikButtonGroupContainer::CleanupCommandPop()
    {CleanupCommandPop(1);}

inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy()
    {CleanupStack::PopAndDestroy();}

inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy(TInt aCount)
    {CleanupStack::PopAndDestroy(aCount);}


#endif  // EIKBTGPC_H

// End of File
