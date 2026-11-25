/*
* ==============================================================================
*  Name        : eiktbar.h
*  Part of     : CKON
*  Interface   : Toolbar API
*  Description : CEikToolBar displays a horizontal group of controls along the 
*                bottom of an application.
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


#ifndef EIKTBAR_H
#define EIKTBAR_H


// INCLUDES
#include <eikctgrp.h>
#include <coecobs.h>
#include <eikbtgrp.h>
#include <eikbtgpc.h>


// FORWARD DECLARATIONS
class MCknButtonDimmedObserver;
class CCknToolBarExtension;
class MEikCommandObserver;
class TEikButtonCoordinator;
class CEikCommandButton;
class CCoeBrushAndPenContext;


// CLASS DECLARATIONS

/**
* The <code>CEikToolBar</code> class displays a horizontal group of controls 
* along the bottom of an application. A Toolbar contains buttons that are used 
* to issue application commands and other controls. A Toolbar may be created 
* using this class by setting the <code>EEikToolBarHorizontal</code> flag and 
* initializing from a <code>TOOLBAND</code> resource.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikToolBar : public CEikControlGroup, 
                    public MCoeControlObserver, 
                    public MEikButtonGroup
    {
public:
    // Constructors and destructor
    /**
    * The object destructor.
    */
    IMPORT_C ~CEikToolBar();
    /**
    * The default object constructor.
    */
    IMPORT_C CEikToolBar();
    // New methods
        
    /**
    * Completes construction of a default-constructed Toolbar.
    *
    * @param aCommandObserver The command observer for this Toolbar
    * @param aResourceId The ID of <code>TOOLBAND</code> resource structure
    * @param aBoundingRect The rectangle to which the Toolbar is limited. The 
    *                      <code>CEikAppUi::ClientRect()</code> method returns 
    *                      the extent of the whole application window, less 
    *                      the extent of any Toolbars that already exist and 
    *                      are owned by the AppUI
    * @remarks Command observers respond to user commands, and have the 
    *          secondary ability to create custom controls on request for 
    *          classes such as <code>CEikToolbar</code>, or developer-defined 
    *          classes. The command observer interface defines a method for 
    *          creating custom controls on the Toolbar from developer-defined 
    *          IDs specified in the resource <code>aResourceId</code>. IDs for 
    *          controls that cannot be constructed using 
    *          <code>EikControlFactory::CreateByTypeL()</code> are passed to 
    *          this object's command observer for construction. If that fails, 
    *          this method panics with a code of 
    *          <code>EEikPanicToolBarNullControl</code> and a category of 
    *          Uikon. Applications requiring custom controls in their Toolbars 
    *          should override their AppUI's 
    *          <code>CreateCustomCommandControlL()</code> method, inherited 
    *          from <code>MEikCommandObserver</code>
    * @see
    */
    IMPORT_C void ConstructL(MEikCommandObserver* aCommandObserver,
                             TInt aResourceId,const TRect& aBoundingRect);
    /**
    * Creates a Toolbar from a resource definition, but does not set its extent
    * or activate it.
    *
    * @param aCommandObserver The command observer
    * @param aResourceId The resource that defines the Toolbar
    * @remarks 
    * @see
    */
    IMPORT_C void StaticConstructL(MEikCommandObserver* aCommandObserver,
                                   TInt aResourceId);
    /**
    * Sets the Toolbar's command observer.
    * 
    * @param aCommandObserver The command observer for this Toolbar
    * @remarks See eikcmobs.h for the virtual methods in 
    *          <code>MEikCommandObserver</code>
    * @see
    */
    IMPORT_C void SetCommandObserver(MEikCommandObserver* aCommandObserver);
    /**
    * Sets the button coordinator for a group of buttons in a Toolbar. The 
    * <code>TEikButtonCoordinator</code> class is used to coordinate groups 
    * of buttons when only one button can be set at one time. All buttons 
    * that should be coordinated in an application must share the same 
    * button coordinator.
    *
    * @param aId Command identifying a Toolbar button
    * @param aCount The number of buttons in the group
    * @param aCoordinator The button coordinator
    * @remarks See eikbutb.h for the definition of 
    *          <code>TEikButtonCoordinator</code>
    * @see SetButtonStateOn()
    */
    IMPORT_C void CoordinateButtons(TInt aId,TInt aCount,
                                    TEikButtonCoordinator* aCoordinator);
    /**
    * Sets the state of the specified button and draws the button to show the 
    * new state. 
    *
    * @param aId The command that identifies the button
    * @param aState <code>ETrue</code> to set the button as down; 
    *               <code>EFalse</code> to set the button as up
    * @remarks
    * @see CoordinateButtons()
    */
    IMPORT_C void SetButtonStateOn(TInt aId,TBool aState);
    /**
    * Delays activation of the Toolbar when constructed.
    *
    * @return <code>ETrue</code> to delay activation of the Toolbar; 
    *         <code>EFalse</code>
    *         otherwise
    * @remarks This method sets the Toolbar flag 
    *          <code>EEikToolBarDelayActivation</code>. If this flag is set 
    *          when <code>ConstructL()</code> is called on the Toolbar, the 
    *          Toolbar is constructed but not activated. The application can 
    *          subsequently activate the Toolbar by calling 
    *          <code>CCoeControl::ActivateL()</code>. Typically, this is not 
    *          necessary, as the view's <code>ActivateL()</code> is called, 
    *          which, in turn, results in all the controls in the view,
    *          including the Toolbar, being drawn
    * @see
    */
    IMPORT_C TBool DelayActivation() const;
    /**
    * Sets the button dimmed observer.
    *
    * @param aObserver The button dimmed observer
    * @remarks The <code>MCknButtonDimmedObserver</code> class is a mixin 
    *          interface class with one virtual method,
    *          <code>HandleDimmedButtonSelectedL()</code> requiring 
    *          implementation by the caller object. See 
    *          cknbuttondimmedobserver.h for the class definition
    * @see
    */
    IMPORT_C void SetButtonDimmedObserver(MCknButtonDimmedObserver* aObserver);
        
    // Methods from base classes
        
    /**
    * Draws the Toolbar control on request.
    *
    * @param aRect Optional. If supplied, the rectangle in which to draw the 
    *        control
    * @remarks
    * @see CCoeControl
    */
    IMPORT_C void Draw(const TRect& aRect) const;
    /**
    * Constructs a Toolbar from a resource.    
    *
    * @param aReader A resource reader
    * @remarks The resource type is <code>TOOLBAND</code>. Do not use this 
    *          method directly. Instead call <code>ConstructL()</code> or 
    *          <code>StaticConstructL()</code> to create the Toolbar. Either 
    *          of these two methods calls this method indirectly
    * @see CCoeControl
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    /**
    * Sets the Toolbar dim state.
    *
    * @param aDimmed <code>ETrue</code> to set as dimmed;
    *        <code>EFalse</code> to set as not dimmed
    * @remarks
    * @see CCoeControl
    */
    IMPORT_C void SetDimmed(TBool aDimmed);
    /**
    * Gets the list of logical colors used for drawing the control. This 
    * method is no longer used. Skin functionality manages the colors for 
    * this control.
    * 
    * @param aColorUseList Not used
    * @remarks
    * @see CCoeControl
    */
    // not available before Release 005u
    IMPORT_C 
        void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; 
    /**
    * Handles a change to the control's resources that are shared across the 
    * environment.
    * 
    * @param aType A <code>TInt</code> message UID value for the resource 
    *              that has changed
    * @remarks
    * @see CCoeControl
    */
    // not available before Release 005u
    IMPORT_C void HandleResourceChange(TInt aType);
    /**
    * Adds a control to the control group.
    *
    * @param aControl The control to add to the control group
    * @param aId The control's ID
    * @remarks
    * @see CEikControlGroup
    */
    IMPORT_C void AddControlL(CCoeControl* aControl,TInt aId);
    /**
    * Adds a control, wrapped with its ID and length, to the control group.
    *
    * @param aGroupControl The wrapped control to add
    * @remarks
    * @see CEikControlGroup
    */
    IMPORT_C void AddControlL(TEikGroupControl& aGroupControl);
    /**
    * Adds the control type. The control type is the ID of a control.
    *
    * @param aType The type to be added
    * @remarks 
    * @see
    */
    void AddControlTypeL(TInt aType);
    /**
    * Removes the control type. The control type is the ID of a control.
    *
    * @param aIndex The index of a control type to be removed
    * @remarks
    * @see
    */
    void RemoveControlType(TInt aIndex);
    /**
    * Returns whether a control is a button.
    *
    * @param aIndex The index of the control to test
    * @return <code>ETrue</code> if a control is a button; <code>EFalse</code>
    *         otherwise
    * @remarks
    * @see
    */
    TBool ControlIsButton(TInt aIndex) const;
    /**
    * Sets the Toolbar's bounding rectangle.
    *
    * @param aBoundingRect The Toolbar's bounding rectangle
    * @remarks
    * @see MEikButtonGroup
    */
    IMPORT_C void SetBoundingRect(const TRect& aBoundingRect);
    /**
    * Shrinks a rectangle to exclude the Toolbar area.
    *
    * @param aBoundingRect Specifies a rectangle which, on return, is shrunk 
    *        to exclude the extent of the Toolbar
    * @remarks The parameter passed to the method is the view's area minus 
    *          the area occupied by the Toolbar. It is provided to prevent
    *          drawing over an existing Toolbar
    * @see MEikButtonGroup
    */
    IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
protected:  // Methods
    // Methods from base classes
    /**
    * From CCoeControl 
    * Writes the internal state of the control and its components to aStream.
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: //Methods
    CEikCommandButton* ButtonByIndex(TInt aIndex) const;
    void SetCurrentId(TInt aPosition,TInt aId);
    TInt CurrentId(TInt aPosition) const;
    TEikGroupControl& GroupControlByIndex(TInt aIndex) const;
    TInt IndexFromPosition(TInt aPos) const;
    // from MEikButtonGroup
    void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,
                     const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
    void SetCommandL(TInt aPosition,TInt aResourceId);
    void SetCommandSetL(TInt aResourceId);
    void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,
                     const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
    void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,
                            const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
    void AddCommandToStackL(TInt aPosition,TInt aResourceId);
    void AddCommandSetToStackL(TInt aResourceId);
    void SetDefaultCommand(TInt aCommandId);
    TSize CalcMinimumSizeL(TInt aResourceId);
    void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
    TInt CommandPos(TInt aCommandId) const;
    void DimCommand(TInt aCommandId,TBool aDimmed);
    TBool IsCommandDimmed(TInt aCommandId) const;
    void MakeCommandVisible(TInt aCommandId,TBool aVisible);
    TBool IsCommandVisible(TInt aCommandId) const;
    CCoeControl* AsControl();
    const CCoeControl* AsControl() const;
    CCoeControl* GroupControlById(TInt aCommandId) const;
    CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
    TInt CommandId(TInt aCommandPos) const;
    TInt ButtonCount() const;
    TUint ButtonGroupFlags() const;
    // from MCoeControlObserver
    IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
    IMPORT_C void Reserved_2(); //from CCoeControl
    void BaseConstructL();
    TInt ControlCount() const;
    TBool ControlIsCommandButton(TInt aIndex) const;
    TBool ControlIsLabel(TInt aIndex) const;
    void SetLabelFont(TInt aIndex);
private:     // Data
    TInt iToolBarFlags;
    MEikCommandObserver* iCommandObserver;
    CCknToolBarExtension* iExt;
    CArrayFix<TInt>* iControlTypes; 
    };


#endif      // EIKTBAR_H   
            
// End of File
