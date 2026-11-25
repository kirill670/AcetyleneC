/*
* =============================================================================
*  Name        : eikcba.h
*  Part of     : CKON
*  Interface   : Eikon CBA buttons
*  Description : Interface for CBA buttons
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
* =============================================================================
*/


#if !defined(__EIKCBA_H__)
#define __EIKCBA_H__

// INCLUDES
#include <eikctgrp.h>
#include <badesca.h>
#include <eikbtgrp.h>
#include <eikbtgpc.h>
#include <gulutil.h>
#include <eikcmbut.h>
#include <skin.h>

// FORWARD DECLARATIONS
class CEikCbaButton;
class CCoeBrushAndPenContext;
class MEikCommandObserver;
class TCoeColorUse;
class CEikCba;
class CDefaultCmdStack;
class MCknButtonDimmedObserver;
class CEikCbaExtension;



/**
*  The <code>CEikCbaContainer</code> class provides a container object for the 
*  CBA.
*
*  @lib eikctl.lib
*  @since ?Series90_version
*/
class CEikCbaContainer : public CCoeControl, public MEikButtonGroup
    {
    public:
        /**
        * @internal
        */
    static CEikCbaContainer* NewL(CEikButtonGroupContainer::TOrientation aOrientation,TInt aResourceId,
                                MEikCommandObserver* aCommandObserver,CEikButtonGroupContainer::TUse aUse,
                                TUint aFlags);

        /**
        * Returns a pointer to the Command Bar for this container.
        *
        * @return a pointer to the Command Bar group of buttons
        * @remarks The return value should be cast to <code>CEikControlGroup*</code>
        *          in order to access the individual button controls owned by 
        *          <code>Cba()</code>, for example, to access the first of the 
        *          buttons in the Command Bar:  
        *          <code>CEikControlGroup* MyCba = 
        *          STATIC_CAST(CEikControlGroup*,Cba())</code> 
        *          and 
        *          <code>CEikCommandButton* Button1 = 
        *          STATIC_CAST(CEikCommandButton*, MyCba->Control(0))</code>
        * @see
        */
        IMPORT_C CEikCba* Cba();
    private:
        ~CEikCbaContainer();
    void ConstructL(CEikButtonGroupContainer::TOrientation aOrientation,TInt aResourceId,
                    MEikCommandObserver* aCommandObserver,CEikButtonGroupContainer::TUse aUse,TUint aFlags);
    private: // from CCoeControl
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        void MakeVisible(TBool aVisible);
        TSize MinimumSize();
        void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
        void SizeChanged();
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void Draw(const TRect& aRect) const;
        void ActivateL();
    private: // from MEikButtonGroup
        void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
        void SetCommandL(TInt aPosition,TInt aResourceId);
        void SetCommandSetL(TInt aResourceId);
        void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
        void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
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
        void SetBoundingRect(const TRect& aBoundingRect);
        void ReduceRect(TRect& aBoundingRect) const;
        CCoeControl* GroupControlById(TInt aCommandId) const;
        CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
        TInt CommandId(TInt aCommandPos) const;
        TInt ButtonCount() const;
        TUint ButtonGroupFlags() const;
    private:
        CEikCba* iCba;
    };

/**
*  The <code>CEikCba</code> class provides an interface for the CBA buttons.
*
*  @lib eikctl.lib
*  @since ?Series90_version
*/
class CEikCba : public CEikControlGroup, 
                public MCoeControlObserver, 
                public MCknSkinServObserver
    {
    public:// from MCknSkinServObserver

        /**
        * Updates the fonts array stored in the Eikon Environment. This method 
        * delays deletion of the old array in case applications redraw before
        * they have taken the new fonts.
        *
        * @param aReloadStatus This method does nothing unless 
        *                      <code>aReloadStatus=ESkinReloadStatusSuccess</code>
        * @remarks <code>aReloadStatus=ESkinReloadStatusSuccess</code>
        *          indicates that the skin has been successfully changed and
        *          therefore the Command Bar may need to be updated.
        *          <code>TSkinReloadStatus</code> is defined in skin.h.
        * @see
        */
        virtual void HandleSkinReloadEventL(TSkinReloadStatus aReloadStatus);

        /**
        *<B>Note:</B> This method is not supported in Series 90.
        *
        * @remarks
        * @see
        */
        virtual void HandleAppViewChange();
    public:
        /** @internal */
    static CEikCba* NewL(   CCoeControl& aContainer,
                            CEikButtonGroupContainer::TOrientation aOrientation,
                            TInt aResourceId,
                            MEikCommandObserver* aCommandObserver,
                            CEikButtonGroupContainer::TUse aUse,
                            TUint aFlags);

        /**
        * The object destructor.
        */
        ~CEikCba();

        /**
        * Sets the <code>MCknButtonDimmedObserver</code>. This is notified 
        * when the user taps a dimmed toolbar or CBA button.
        *
        * @param aObserver The <code>MCknButtonDimmedObserver</code> observer
        * @remarks <code>MCknButtonDimmedObserver</code> is defined in 
        *          cknbuttondimmedobserver.h
        * @see
        */
        IMPORT_C void SetButtonDimmedObserver(MCknButtonDimmedObserver* aObserver);
    private:
        CEikCba(MEikCommandObserver* aCommandObserver,TUint aFlags);
        void BaseConstructL(CEikButtonGroupContainer::TOrientation aOrientation);

    void ConstructL(CCoeControl& aContainer,
                    CEikButtonGroupContainer::TOrientation aOrientation,
                    TInt aResourceId,
                    CEikButtonGroupContainer::TUse aUse);

        CEikCbaButton* ButtonById(TInt aCommandId) const;
        CEikCbaButton* ButtonByPos(TInt aPosition) const;
        TInt MaxCommands() const;
        void UpdateStackedDefaultsL(TInt aNewDefaultId);
        void UpdateDefaultCommandStatus();
        TInt BreadthRequiredForCommandSetL(TInt aResourceId);
        TInt BreadthRequiredForCommandL(TInt aResourceId);
        TInt BreadthRequiredForCommandL(TResourceReader& aReader);
        static TInt FullScreenModeTimerCallBackL(TAny* aThis);
        void LayoutButtons();
        void AddButtonL(TInt aPosition);
        void PreReadButtonSetResourceL(TResourceReader& aReader);
        void PreReadButtonResourceL(TResourceReader& aReader, TInt& aCommandId) const;
        void PostReadButtonResource(TResourceReader& aReader) const;
        void ConstructFromCbaResourceL(TResourceReader& aReader);
        void ConstructFromDialogButtonResourceL(TResourceReader& aReader);
        TInt MinimumBreadth() const;
        TBool CommandIndexForKey(const TKeyEvent& aKeyEvent,TEventCode aType,TInt& aIndex) const;
    public: 

        /**
        * @internal
        * Sets a command in this button group.
        *
        * @param aPosition The position of the control in the button group
        * @param aCommandId The ID of the command
        * @param aText The button text
        * @param aBitmap The bitmap for the button
        * @param aMask The bitmap mask for the button
        */
        void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

        /**
        * @internal
        * Sets a command in this button group from resources.
        *
        * @param aPosition The position of the control in the button group
        * @param aResourceId The resource ID for this button
        */
        void SetCommandL(TInt aPosition,TInt aResourceId);

        /**
        * @internal
        * Sets a button group from resources.
        *
        * @param aResourceId The resource ID of the button group
        * @remarks
        * @see
        */
        void SetCommandSetL(TInt aResourceId);

        /**
        * @internal
        * Adds a command to the button group.
        *
        * @param aPosition The position of the control in the button group
        * @param aCommandId The ID of the command
        * @param aText The button text
        * @param aBitmap The bitmap for the button
        * @param aMask The bitmap mask for the button
        * @remarks
        * @see
        */
        void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

        /**
        * Adds a command to the button group command stack.
        *
        * @param aPosition The position of the control in the button group
        * @param aCommandId The ID of the command
        * @param aText The button text
        * @param aBitmap The bitmap for the button
        * @param aMask The bitmap mask for the button
        * @remarks The specified command ID and text are added to the top
        *          of the command stack. This means that <code>aCommandId</code>
        *          is generated whenever the button is tapped. The change 
        *          is reversed by a call to <code>PopCommandFromStack</code>
        *          or <code>RemoveCommandFromStack</code>
        * @see
        */
        void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

        /**
        * @internal
        * Adds a command to the button group command stack from resources.
        *
        * @param aPosition The position of the control in the button group
        * @param aResourceId The resource ID for this button
        * @remarks
        * @see
        */
        void AddCommandToStackL(TInt aPosition,TInt aResourceId);
        
        /**
        * @internal
        * Adds a command to the button group command stack from resources.
        *
        * @param aResourceId The resource ID of the button group
        */
        void AddCommandSetToStackL(TInt aResourceId);

        /**
        * @internal
        * Sets the default command of the button group.
        *
        * @param aCommandId The ID of the default command
        */
        void SetDefaultCommand(TInt aCommandId);

        /**
        * @internal
        * Calculates the minimum size of this button group from resources.
        *
        * @param aResourceId The resource ID of the button group
        * @return the minimum size
        * @remarks
        * @see
        */
        TSize CalcMinimumSizeL(TInt aResourceId);

        /**
        * @internal
        * Removes a command from the button group and the command stack.
        *
        * @param aPosition The position of the command in the button group
        * @param aCommandId The ID for this command
        * @remarks
        * @see
        */
        void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);

        /**
        * @internal
        * Pops a command from the button group and the command stack.
        *
        * @param aPosition The position of the command in the button group
        * @remarks This restores the current command button's command ID and
        *          text to the values they had before the last call to
        *          AddCommandL.
        * @see
        */
        void PopCommandFromStack(TInt aPosition);

        /**
        * @internal
        * Gets the position of a command from its ID.
        *
        * @param aCommandId The ID for this command
        * @return the command position
        * @remarks
        * @see
        */
        TInt CommandPos(TInt aCommandId) const;

        /**
        * @internal
        * Sets the dim state of a command button.
        *
        * @param aCommandId The ID of the command
        * @param aDimmed <code>ETrue</code> if this command button should be 
        *                dimmed; <code>EFalse</code> to undim it
        * @remarks
        * @see
        */
        void DimCommand(TInt aCommandId,TBool aDimmed);

        /**
        * @internal
        * Determines the dim state of the command button.
        *
        * @param aCommandId The ID of the command
        * @return <code>ETrue</code> if this command button is dimmed; 
        *         <code>EFalse</code> if not
        * @remarks
        * @see
        */
        TBool IsCommandDimmed(TInt aCommandId) const;

        /**
        * @internal
        * Sets the visibility of a command button.
        *
        * @param aCommandId The ID of the command
        * @param aVisible <code>ETrue</code> if the command button should be 
        *                 visible; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        void MakeCommandVisible(TInt aCommandId,TBool aVisible);

        /**
        * @internal
        * Determines whether the command button is visible.
        *
        * @param aCommandId The ID of the command
        * @return <code>ETrue</code> if the command button is visible; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        TBool IsCommandVisible(TInt aCommandId) const;

        /**
        * @internal
        * Sets the rectangle that contains the button group.
        *
        * @param aBoundingRect The bounding rectangle
        * @remarks
        * @see
        */
        void SetBoundingRect(const TRect& aBoundingRect);

        /**
        * @internal
        * Shrinks a rectangle to exclude the toolbar area. This method reduces 
        * the size of the rectangle passed into the method so that, on return, 
        * the area occupied by the toolbar or toolband is removed from the 
        * rectangle. It is provided to prevent drawing over an existing 
        * toolbar or toolband.
        *
        * @param aBoundingRect Specifies a rectangle which, on return, 
        *                             is shrunk to exclude the toolbars extent
        * @remarks
        * @see
        */
        void ReduceRect(TRect& aBoundingRect) const;

        /**
        * @internal
        * Gets a pointer to one of the command buttons.
        *
        * @param aCommandId The ID of the command
        * @return a pointer to the command button control
        * @remarks
        * @see
        */
        CCoeControl* GroupControlById(TInt aCommandId) const;

        /**
        * @internal
        * Gets a pointer to one of the command buttons.
        *
        * @param aCommandId The ID of the command
        * @return a pointer to the command button
        * @remarks
        * @see
        */
        CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;

        /**
        * @internal
        * Gets the command ID for the button at a particular position in the 
        * button group.
        *
        * @param aCommandPos The position index of the button
        * @return the ID of the command button 
        * @remarks
        * @see
        */
        TInt CommandId(TInt aCommandPos) const;

        /**
        * @internal
        * Gets the number of buttons in the group.
        *
        * @return the number of buttons in the group
        * @remarks
        * @see
        */
        TInt ButtonCount() const;

        /**
        * @internal
        * Gets the flags of the button group.
        *
        * @return the flags of the button group 
        * @remarks
        * @see
        */
        TUint ButtonGroupFlags() const;

        /**
        * @internal
        * intentionally doing nothing
        *
        * @remarks
        * @see
        */
        void CopyContextToButtons();

		/**
		* @internal
		* for use by the CEikCbaContainer
		*
		* @return ETrue if the dialog buttons are on the CBA, EFalse otherwise
        * @remarks
        * @see
		*/
		TBool AreDialogButtonsOnCBA() const;

    public: // from CCoeControl

        /**
        * Handles key events offered to the control by the control environment.
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this control. 
        *         <code>EKeyWasConsumed</code> if the control takes action on the 
        *         key event; <code>EKeyWasNotConsumed</code> otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Sets this control as visible or invisible.
        *
        * @param aVisible <code>ETrue</code> to make the control visible, 
        *           <code>EFalse</code> to make it invisible
        * @remarks
        * @see CCoeControl
        */
        void MakeVisible(TBool aVisible);

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
         * Gets the smallest area in which this control can be 
         * displayed in its entirety.
         *
         * @return the smallest area in which this control can be
         *         displayed in its entirety
         * @remarks The minimum size is dictated by the size of the buttons,
         *          and the margins and borders that have been set
         * @see
         */
        TSize MinimumSize();
    private: // from CCoeControl
        void HandleResourceChange(TInt aType);
        void Draw(const TRect& aRect) const;
    private: // from MCoeControlObserver
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
    private:
    enum TCbaFlags
        {
        EDefaultCommandOnTop = 0x0010,
        ESizeCalculated      = 0x0020
        };
    private:
        CCoeBrushAndPenContext* iBrushAndPenContext;
        MEikCommandObserver* iCommandObserver;
        CFbsBitmap* iBrushBitmap;
        TInt iDefaultCommandId;
        CPeriodic* iFullScreenModeTimer;
        CEikButtonGroupContainer::TUse iUse;
        TUint iCbaFlags;
        CEikCbaExtension* iCbaExt;
        TBool iClockOnCba;
		TBool iDialogButtonsOnCba;
    };

/**
*  The <code>CEikCbaButton</code> class provides the CBA button interface.
*
*  @lib eikctl.lib
*  @since ?Series90_version
*/
class CEikCbaButton : public CEikCommandButton
    {
    public:

        /**
        * The default object constructor.
        */
        CEikCbaButton(CEikCba& aContainer);

        /**
        * @internal
        * The object constructor.
        *
        * @param aPosition The position of the button
        * @remarks
        * @see
        */
        void ConstructL(TInt aPosition);

        /**
        * @internal
        * The object constructor.
        *
        * @param aReader A reference to the resource reader
        * @param aUse The type of button group container
        * @param aPosition The position of the button
        * @return the command ID of the button 
        * @remarks
        * @see
        */
        TInt ConstructL(TResourceReader& aReader,CEikButtonGroupContainer::TUse aUse,TInt aPosition);
    public:

        /**
        * @internal
        * Sets up the command for the CBA button.
        * 
        * @param aCommandId The command ID to be associated with the button
        * @param aText The text to go on the button
        * @param aBitmap A pointer to the bitmap to go on the button
        * @param aMask A pointer to the mask for the bitmap that goes on the 
        *              button
        * @remarks
        * @see
        */
        void SetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

        /**
        * @internal
        * Adds a new command to the top of the button.
        *
        * @param aCommandId The command ID to add
        * @param aText The text of the command
        * @remarks
        * @see
        */
        void PushCommandL(TInt aCommandId,const TDesC& aText);

        /**
        * @internal
        * Removes the top command from the button.
        * 
        * @return the new ID of the command on top
        * @remarks
        * @see
        */
        TInt PopCommand();

        /**
        * @internal
        * Removes a command from the stack.
        *
        * @param aCommandId The command ID of the command to remove
        * @return <code>ETrue</code> if the command was removed; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        TBool RemoveCommand(TInt aCommandId);

        /**
        * @internal
        * Calculates the minimum size of the button based on the supplied text.
        * 
        * @param aText The button text
        * @return the minimum size of the button
        * @remarks
        * @see
        */
        TSize CalcMinimumSize(TPtrC& aText) const;

        /**
        * @internal
        * Reads in information from resource.
        *
        * @param aReader A reference to the resource reader
        * @param aCommandId A reference to the command ID to be loaded
        * @param aText A reference to the text to be loaded
        * @param aUse The type of button group container
        * @remarks
        * @see
        */
        static void ReadFromResourceLC(TResourceReader& aReader,TInt& aCommandId,HBufC*& aText,CEikButtonGroupContainer::TUse aUse);

        /**
        * @internal
        * Sets the margins on the button.
        *
        * @param aMargins A <code>TMargins8</code> variable containing margin 
        *                 information
        * @remarks
        * @see
        */
        void SetMargins(TMargins8 aMargins);

        /**
        * @internal
        * Updates the margins.
        *
        * @param aButtonCount The number of buttons to update the margin for
        * @param aIndex The index to start from
        * @remarks
        * @see
        */
        void UpdateMargins(TInt aButtonCount,TInt aIndex);

        /**
        * @internal
        * Sets the alignment of the text on the button
        * 
        * @param aAlign TGulAlignmentValue representing a type of alignment
        * @return void
        * @remarks
        * @see
        */
        void SetAlignment(TGulAlignmentValue aAlign);

        /**
        * @internal
        * Sets the default value of this button
        * 
        * @param aDefault a TBool value representing the default value.  
        *                 If eTrue, button is the default, eFalse otherwise
        * @return void
        * @remarks
        * @see
        */
        void SetDefault(TBool aDefault);

        /**
        * @internal
        * Checks if the button has stacked commands
        * 
        * @return eTrue if the button has stacked commands, eFalse otherwise
        * @remarks
        * @see
        */
        TBool IsCommandStacked() const;
    public: // from CCoeControl

        /**
         * Gets the smallest area in which this control can be 
         * displayed in its entirety.
         *
         * @return the smallest area in which this control can be
         *         displayed in its entirety
         * @remarks The minimum size is dictated by the size of the buttons and
         *          margins and borders that have been set
         * @see
         */
        TSize MinimumSize();

         /**
        * Activates this control.
        * 
        * @remarks Informs the framework that the control is ready to be drawn
        * @see CCoeControl
        */
        void ActivateL();
    protected: // from CCoeControl

        /**
        * From CCoeControl.
        * Writes the internal state of the control and its components to aWriteStream.
        * @param aWriteStream Write stream.
        */
        void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private: // from CCoeControl
        void Draw(const TRect& aRect) const;
        void SizeChanged();
    private: // from CEikButtonBase
        void Animate();
    private: // from MCoeControlContext
        void PrepareContext(CWindowGc& aGc) const;
    private:
        void SetInitialWrappingWidthL();
        void SizeChangedL();
    private:
        TMargins8 iMargins;
        TInt iStackCount;
        TInt iPosition;
        CEikCba& iContainer;
    };

class CCBASizeManager : public CBase
    {
    class TWindowGroupSize
        {
    public:
        TWindowGroupSize(TInt aWindowGroupId, TInt aCBAInstance, TInt aCBAWidth);

    public:
        TInt iWindowGroupId;
        TInt iCBAInstance;
        TInt iCBAWidth;
        };

public:
    static TInt GetNotifierServerWindowGroupId(TInt& aWindowGroupId);
    static TInt UpdateSize(TInt aWindowGroupId, TInt aCBAInstance, TInt aCBAWidth);
    static TInt RemoveSize(TInt aWindowGroupId, TInt aCBAInstance);
	IMPORT_C static TInt GetMaxWidth(TInt& aMaxWidth);
    
private:
    static TInt Read(RArray<TWindowGroupSize>& aCBASizes);
    static TInt Write(RArray<TWindowGroupSize>& aCBASizes);
    static TInt FindByWindowGroupAndCBAInstance(const RArray<TWindowGroupSize>& aCBASizes,
        TInt aWindowGroupId, TInt aCBAInstance);
    static TInt CreateChunkAndSem();
    };

#endif// #if !defined(__EIKCBA_H__)

// End of File
