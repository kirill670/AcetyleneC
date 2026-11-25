/*
* ==============================================================================
*  Name        : eikdialg.h
*  Part of     : CKON
*  Interface   : Dialog Base API
*  Description : Main Dialog class.
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

#ifndef EIKDIALG_H
#define EIKDIALG_H

// INCLUDES
#include <coecobs.h>
#include <coeccntx.h>
#include <eikbctrl.h>
#include <eikdpobs.h>
#include <gulftflg.hrh>
//
// Header files needed by deprecated interfaces
//
#include <eikbutb.h>
#include <eikteled.h>


//
// FORWARD DECLARATIONS
//
class CEikMover;
class CEikCaptionedControl;
class CEikCapCArray;
class CEikDialogPageSelector;
class CEikButtonGroupContainer;
class CEikDialogButtonCommandObserver;
class MEikCommandObserver;
class CEikDialogExtension;

struct SEikControlInfo;

//
// Forward declarations needed by deprecated interfaces
//

class CEikLabel;
class CGlobalText;
struct SEikRange;
struct SEikDegreesMinutesDirection;


// CLASS DECLARATIONS

/**
 * The <code>CEikDialog</code> class provides an instantiable base class for 
 * Dialogs. Controls can be added directly to this class, but it is more usual
 * to create a derived class to handle the controls appearing on the Dialog 
 * dynamically. A Dialog is usually created on the heap and called using 
 * <code>ExecuteLD()</code>.
 *
 * @lib eikdlg.lib 
 * @since Series90 1.0
 */
class CEikDialog : public CEikBorderedControl,public MCoeControlObserver,public MEikDialogPageObserver,public MCoeControlContext
    { 

    private:  // Declarations

        friend class CEikDialogButtonCommandObserver;
        friend class CEikMover;
        friend class CEikDialogExtension;
    public:

    // Constructors and destructor

        /**
        * The default object constructor.
        */
        IMPORT_C CEikDialog(); 

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikDialog(); 

    // New methods
        
        /**
        * Prepares and runs the Dialog and returns the ID of the button used
        * to dismiss it. The Dialog is initialized from the resource with ID
        * <code>aResourceId</code> and is destroyed by this method on exit.
        *
        * @param aResourceId The resource ID of the Dialog to load
        * @return zero, unless it is a waiting Dialog. For a waiting Dialog, 
        *         the return value is the ID of the button that closed the
        *         Dialog, or zero if it was the Cancel button 
        *         (<code>EEikBidCancel</code>)
        * @remarks Internally, this method calls <code>PrepareLC()</code> and 
        *          then <code>RunLD()</code>
        * @see
        */
        IMPORT_C virtual TInt ExecuteLD(TInt aResourceId);

        /**
        * Prepares the Dialog for display, initializing it from the resource
        * with ID <code>aResourceId</code>.
        *
        * @param aResourceId The resource ID of the Dialog to load
        * @remarks
        * @see
        */
        IMPORT_C void PrepareLC(TInt aResourceId);

        /**
        * Runs the Dialog and returns the ID of the button used to dismiss it.
        * The Dialog is destroyed by this method on exit.
        *
        * @return the ID of the button used to dismiss the Dialog
        * @remarks
        * @see
        */
        IMPORT_C TInt RunLD();

        /**
        * Sets the title text for the Dialog to a string defined by the 
        * descriptor <code>aText</code>.
        *
        * @param aText The descriptor containing the new title text
        * @remarks
        * @see
        */
        IMPORT_C void SetTitleL(const TDesC& aText);

        /**
        * Sets the title text for the Dialog to a string defined by the
        * Resource ID <code>aResourceId</code>.
        *
        * @param aResourceId The ID of the resource containing the title text
        * @remarks
        * @see
        */
        IMPORT_C void SetTitleL(TInt aResourceId);

        /**
        * Sets the page identified by <code>aPageId</code> to be dimmed, if 
        * <code>aDimmed</code> is <code>ETrue</code>.
        *
        * @param aPageId The ID of the page to be dimmed
        * @param aDimmed <code>ETrue</code> to dim the page; <code>EFalse</code>
        *                to undim it
        * @remarks
        * @see
        */
        IMPORT_C void SetPageDimmedNow(TInt aPageId,TBool aDimmed);

        /**
        * Sets the Dialog line containing the control identified by 
        * <code>aControlId</code> to a non-focusing state
        * so that it will never be given keyboard focus.
        *
        * @param aControlId The ID of the control in the line that is to be 
        *                   set as non-focusing
        * @remarks
        * @see
        */
        IMPORT_C void SetLineNonFocusing(TInt aControlId);

        /**
        * Dims and inactivates the Dialog line containing the control 
        * identified by <code>aControlId</code>, if <code>aDimmed</code> is 
        * <code>ETrue</code>.
        *
        * @param aControlId The ID of the line to dim or undim
        * @param aDimmed <code>ETrue</code> to dim the line, <code>EFalse</code>
        *                to undim it
        * @remarks
        * @see
        */
        IMPORT_C void SetLineDimmedNow(TInt aControlId,TBool aDimmed);

        /**
        * Makes the specified control visible or invisible. This method only
        * affects the specified control; the visibility of the caption is not
        * affected.
        *
        * @param aControlId The ID of the control to make visible or invisible
        * @param aVisible  <code>ETrue</code> to make the control visible;
        *                  <code>EFalse</code> to make the control invisible
        * @remarks
        * @see
        */
        IMPORT_C void MakeLineVisible(TInt aControlId,TBool aVisible);

        /**
        * Makes the whole Dialog line containing the control identified by 
        * <code>aControlId</code> visible.
        *
        * @param aControlId The ID of the control on the line to make visible 
        *                   or invisible
        * @param aVisible <code>ETrue</code> to make the line visible; 
        *                 <code>EFalse</code> to make the line invisible
        * @remarks
        * @see
        */
        IMPORT_C void MakeWholeLineVisible(TInt aControlId,TBool aVisible);

        /**
        * Deletes the Dialog line with the control identified by 
        * <code>aControlId</code>.
        *
        * @param aControlId The Dialog line to delete
        * @remarks
        * @see
        */
        IMPORT_C void DeleteLine(TInt aControlId);

        /**
        * Inserts a line in the Dialog on the page identified by 
        * <code>aPageId</code> at the line index <code>aIndex</code>
        * and constructed from the resource specified by 
        * <code>aResourceId</code>.
        *
        * @param aIndex The index at which the line is to be inserted
        * @param aResourceId The ID of the resource that defines the line
        * @param aPageId The page on which the line is to be added
        * @remarks
        * @see
        */
        IMPORT_C void InsertLineL(TInt aIndex,TInt aResourceId,TInt aPageId=0);

        /**
        * Makes the Dialog button identified by <code>aButtonId</code> visible, 
        * if <code>aVisible</code> is <code>ETrue</code>.
        *
        * @param aButtonId The ID of the Dialog button to make visible or 
        *                  invisible
        * @param aVisible <code>ETrue</code> to make the button visible; 
        *                 <code>EFalse</code> to make it invisible
        * @remarks
        * @see
        */
        IMPORT_C void MakePanelButtonVisible(TInt aButtonId,TBool aVisible);

        /**
        * Attempts to move the focus to the line identified by 
        * <code>aLineId</code> (this method leaves with <code>KErrNotFound</code>
        * if the line ID is not valid). Calls <code>PrepareForFocusTransitionL()</code> 
        * on the current Dialog line, which in turn calls <code>PrepareForFocusLossL()</code> 
        * on its control to validate the current value. If the value fails 
        * validation, <code>PrepareForFocusLossL()</code> is usually 
        * implemented so that it leaves with a control-specific error code and 
        * an info message describing the error to the user.
        *
        * @param aControlId The ID of the line to change focus to
        * @remarks
        * @see CCoeControl::PrepareForFocusLossL()
        */
        IMPORT_C void TryChangeFocusToL(TInt aControlId);

        /**
        * Switches the latency of the line between <code>aNoLongerLatent</code>
        * and <code>aBecomesLatent</code>. If Dialog lines are latent they are
        * invisible, and are not taken into account when laying out the Dialog.
        * Latent lines can then be swapped around on the Dialog later.
        *
        * @param aBecomesLatent The line ID of the line to become latent
        * @param aNoLongerLatent The line ID of the line that is no longer
        *                        to be latent
        * @remarks
        * @see
        */
        IMPORT_C void SwitchLineLatency(TInt aBecomesLatent,TInt aNoLongerLatent);

        /**
        * If <code>aDensePacking</code> is <code>ETrue</code>, sets the page 
        * identified by <code>aPageId</code> to be densely 
        * packed (that is, with reduced spacing between the lines).
        *
        * @param aPageId The ID of the page to be densely packed
        * @param aDensePacking <code>ETrue</code> for dense packing; 
        *                      <code>EFalse</code> for normal packing
        * @remarks On Series 90 Dialog lines are always densely packed, and
        *          this method does nothing
        * @see
        */
        IMPORT_C void SetPageDensePacking(TInt aPageId,TBool aDensePacking);

        /**
        * Dynamically constructs a Dialog with flags <code>aFlags</code>, 
        * buttons constructed from the resource <code>aButtonId</code>, and 
        * with a single activated empty page with an ID of 0. The
        * Dialog is therefore ready to have lines added to it dynamically.
        *
        * @param aFlags The Dialog flags
        * @param aButtonsId The ID of the resource defining the Dialog's 
        *                   buttons
        * @remarks
        * @see
        */
        IMPORT_C void ConstructAutoDialogLC(TInt aFlags,TInt aButtonsId);

        /**
        * @deprecated
        */
        IMPORT_C void DeclareItemAuto(TInt aControlId,TInt aControlType,TAny* aReturnValue);

        /**
        * Lays out the Dialog, setting it to take its preferred size and 
        * position for the screen.
        *
        * @remarks
        * @see
        */
        IMPORT_C void Layout();

        /**
        * Calculates the preferred size of the Dialog, given that it must fit in 
        * a maximum size of <code>aMaxSize</code>.
        *
        * @param aMaxSize The maximum size of the area in which the Dialog 
        *                 must fit
        * @return the preferred size of the Dialog
        * @remarks
        * @see
        */
        IMPORT_C TSize PreferredSize(const TSize& aMaxSize) const;

        /**
        * Creates a control line in the Dialog on the active page with the 
        * caption text <code>aCaption</code>. The line can thereafter be 
        * accessed through the identifier <code>aControlId</code>.
        * A control of type <code>aControlType</code> is created by the Eikon 
        * control factory and the return value of the line set to 
        * <code>aReturnValue</code>. If the value of <code>aControlType</code> 
        * is not known to the Eikon control factory, the construction of 
        * the control is delegated to <code>CreateCustomControlL</code>,
        * which leaves with an application-defined error if the control
        * type is still not recognized.
        *
        * @param aCaption The caption to appear in the Dialog line
        * @param aControlId The ID of the control. After the line is created 
        *                   this can be used to access it. Must be unique within
        *                   the application
        * @param aControlType The type of control to create
        * @param aReturnValue Deprecated. A random pointer
        * @return a pointer to the newly created control
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aControlId,TInt aControlType,TAny* aReturnValue);

        /**
        * Creates a control line in the Dialog on the active page with caption
        * text <code>aCaption</code>. The line can thereafter be accessed 
        * through the identifier <code>aControlId</code>. A control of type 
        * <code>aControlType</code> is created by the Eikon control factory
        * and the return value of the line set to <code>aReturnValue</code>.
        * If the value of <code>aControlType</code> is not known to the Eikon 
        * control factory, the construction of the control is delegated to 
        * <code>CreateCustomControlL</code>, which leaves with an 
        * application-defined error if the control type is still not recognized.
        *
        * @param aCaption The caption to appear in the Dialog line
        * @param aPageId The ID of the active page on which the control line 
        *                is to be created
        * @param aControlId The ID of the control. After the line is created 
        *                   this can be used to access it
        * @param aControlType The type of control to create
        * @param aReturnValue Deprecated. A random pointer
        * @return a pointer to the newly created control
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aControlId,TInt aControlType,TAny* aReturnValue);

        /**
        * Sets the caption of the control identified by <code>aControlId</code>
        * to the descriptor <code>aText</code>.
        *
        * @param aControlId The ID of the control for which the caption text is
        *                   being set
        * @param aText The text for the caption
        * @remarks
        * @see
        */
        IMPORT_C void SetControlCaptionL(TInt aControlId,const TDesC& aText);

        /**
        * Sets the caption of the control identified by <code>aControlId</code>
        * by reading the caption text from the resource specified by 
        * <code>aResourceId</code>.
        *
        * @param aControlId The ID of the control for which the caption text is 
        *                   being set
        * @param aResourceId The ID of the resource containing the text for the 
        *                    caption
        * @remarks
        * @see
        */
        IMPORT_C void SetControlCaptionL(TInt aControlId,TInt aResourceId);

        /**
        * Returns a pointer to the caption of the control identified by 
        * <code>aControlId</code> (this does not imply transfer of ownership).
        *
        * @param aControlId The ID of the control for which the label is 
        *                   required
        * @return a pointer to the caption
        * @remarks
        * @see
        */
        IMPORT_C CEikLabel* ControlCaption(TInt aControlId) const;

        /**
        * Returns a pointer to the first control found to be identified by 
        * <code>aControlId</code>. This does not imply transfer of ownership.
        * This method panics if the control ID is invalid.
        *
        * @param aControlId The ID of the control for which a pointer is 
        *                   required
        * @return a pointer to the control with ID <code>aControlId</code>
        * @remarks If <code>aControlId</code> being 
        *          invalid is a serious error, use this method instead of 
        *          <code>ControlOrNull()</code>
        * @see
        */
        IMPORT_C CCoeControl* Control(TInt aControlId) const;

        /**
        * Returns a pointer to the control identified by
        * <code>aControlId</code> (or <code>NULL</code> if the control ID is
        * invalid). This does not imply transfer or ownership.
        *
        * @param aControlId The ID of the control for which a pointer is 
        *                   required
        * @return a pointer to the control with ID <code>aControlId</code>, or 
        *         <code>NULL</code> if the ID does not exist
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* ControlOrNull(TInt aControlId) const;

        /**
        * Returns a reference to the button group container that contains the 
        * command buttons for the Dialog.
        *
        * @return the Dialog's button group container
        * @remarks
        * @see CEikButtonGroupContainer
        */
        IMPORT_C CEikButtonGroupContainer& ButtonGroupContainer() const;

        /**
        * This method allows a client to change the command ID of the default 
        * Dialog button. If the button group container has been constructed 
        * already (that is, if <code>PrepareLC()</code> has been called), this 
        * method is equivalent to calling 
        * <code>ButtonGroupContainer().SetDefaultCommand(aDefaultCommandId)</code>.
        * If this method is called before <code>iButtonGroupContainer</code> is
        * constructed, this setting is saved until it is constructed. It
        * is useful on Series 80, where the default command is underlined in 
        * the CBA.
        *
        * @param aDefaultCommandId The ID of the Dialog button to be set as 
        *                          default
        * @remarks On Series 90 the default implementation does nothing
        * @see
        */
        IMPORT_C void SetDefaultCommand(TInt aDefaultCommandId);

        /**
        * Returns a reference to the Dialog title bar.
        *
        * @return a pointer to the Dialog title bar
        * @remarks
        * @see
        */
        IMPORT_C CEikMover& Title() const;

        /**
        * Returns the ID of the Dialog's active page.
        *
        * @return the ID of the active page
        * @remarks
        * @see
        */
        IMPORT_C TInt ActivePageId() const;

        /**
        * Activates the first page on the Dialog. At least one page must be
        * activated before the Dialog can be used.
        *
        * @remarks
        * @see
        */
        IMPORT_C void ActivateFirstPageL() const;

        /**
        * Gets the Dialog's margins. This is the space between the borders and
        * all of the controls on the Dialog, including the control buttons.
        *
        * @return the margins
        * @remarks
        * @see
        */
        IMPORT_C TMargins8 Margins() const;

        /**
        * Sets the Dialog's margins. This is the space between the borders and
        * all of the controls on the Dialog, including the control buttons.
        *
        * @param aMargins The margins
        * @remarks
        * @see SetInternalMargins()
        */
        IMPORT_C void SetMargins(TMargins8 aMargins);

        /**
        * Sets the initial page of the Dialog.
        *
        * @param aPageId The ID of the Dialog page
        * @remarks If <code>aPageId</code> does not represent a valid page, 
        *          panics with <code>USER</code> code <code>0</code> 
        * @see
        */
        IMPORT_C void SetActivePageByIdL(TInt aPageId);

        /**
        * Sets the focus to the first focusable line on the first page of the 
        * Dialog. This method is called by the default implementation of 
        * <code>SetInitialCurrentLine()</code>.
        *
        * @remarks
        * @see
        */
        IMPORT_C void SetInitialFocus();

        /**
        * Sets the Dialog's internal margins. This is the space between the
        * normal margins (see <code>SetMargins()</code>) and the lines of the
        * Dialog. The position of the control buttons is unaffected by this 
        * setting.
        *
        * @param aMargins The Dialog's internal margins
        * @remarks This method must be called after the Dialog is prepared, 
        *          because it requires access to the array of captioned 
        *          controls
        * @see SetMargins()
        */
        IMPORT_C void SetInternalMargins(TMargins8 aMargins);

        /**
        * Specifies the <code>iContext</code> control. The context control can
        * be any control derived from <code>CCoeControl</code> and is placed in the 
        * right-hand side of the Dialog. It is drawn and receives key and
        * pointer events in the normal way. For an example, see the Border
        * Preview control in Word's Border Dialog.
        *
        * @remarks
        * @see
        */
        IMPORT_C void SetContextControl(CCoeControl* aContextControl);

        /**
        * Sets the Dialog page observer.
        *
        * @param aObserver The page observer
        * @remarks
        * @see
        */
        IMPORT_C void SetValidatePageObserver(MEikDialogValidatePageObserver* aObserver);


        /**
        * Activates this control.
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void ActivateL();

        /**
        * Handles key events offered to the control by the control environment.
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code>, or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * Handles a change to the control's resources that are shared across 
        * the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        * @since Release 005u
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

        /**
        * Returns the input capabilities of the Dialog. 
        * By default, the Dialog is capable of handling navigation keys. These
        * include the arrow, page-up, page-down, home, end, and tab keys.
        *
        * @return the input capabilities
        * @remarks Input capabilities can be changed by overriding this method
        *          in a derived class
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

        /**
        * This method sets whether rocker-select (<code>EKeyDevice7</code>), 
        * that is, the user pushing the centre of the directional pad, 
        * is mapped to <code>EEikBidOk</code>.
        *
        * @param aBidOk <code>ETrue</code> if rocker-select is mapped to 
        *               <code>EEikBidOk</code>; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetRockerSelectBidOk(TBool aBidOk);

        /**
		* Overrides the state of the EEikDialogFlagWait flag
        * @remarks
        * @see
        */
        IMPORT_C void SetWaitFlag(TBool aFlag);

        /**
		* Overrides the state of the EEikDialogFlagNotifyEsc flag
        * @remarks
        * @see
        */
        IMPORT_C void SetNotifyEscFlag(TBool aFlag);
    protected:  // Methods
        /**
        * From MEikDialogPageObserver Prepares for a transition in focus in
        * the Dialog. By default, calls the currently focused control
        * to prepare for loss of focus.
        */
        IMPORT_C virtual void PrepareForFocusTransitionL();

        /**
        * From MEikDialogPageObserver Takes any action required when the active
        * Dialog page is changed to aPageId.
        * Should not leave for sleeping Dialogs.
        * @param aPageId The control ID of the new current page.
        */
        IMPORT_C virtual void PageChangedL(TInt aPageId);

        /**
        * From MEikDialogPageObserver Takes any action required when the
        * current line is changed to aControlId.
        * @param aControlId ID of the control being switched to.
        */
        IMPORT_C virtual void LineChangedL(TInt aControlId);

    public:  // Methods

        /**
        * Creates a custom control of a specified type. The method is called 
        * by the control factory if the type <code>aControlType</code> is not 
        * recognized when creating a line on the Dialog page.
        * This method panics by default. If it is to be called, it must be 
        * reimplemented in a derived class. The parent of a custom control 
        * should be the line that contains it (not the Dialog itself). However,
        * the line is not accessible at this stage. If necessary, the line 
        * should be set as the parent in <code>PreLayoutDynInitL</code>.
        *
        * @param aControlType The type ID of the custom control. This must not 
        *                     clash with any framework-defined control type IDs
        * @return the information structure for the custom control
        * @remarks
        * @see MEikDialogPageObserver
        * @see SEikControlInfo
        */
        IMPORT_C virtual SEikControlInfo CreateCustomControlL(TInt aControlType);

        /**
        * @deprecated
        */
        IMPORT_C virtual void GetCustomAutoValue(TAny* aReturnValue,TInt aControlType,const CCoeControl* aControl);

    protected:  // Methods
        /**
        * From <code>MCoeControlContext</code> Prepares the graphics context
        * aGc for drawing the control in its normal state.
        * @param aGc The graphics context.
        */
        IMPORT_C void PrepareContext(CWindowGc& aGc) const;

    private:  // Methods

    // Methods from base classes

        IMPORT_C void Draw(const TRect& aRect) const;
        IMPORT_C TInt CountComponentControls() const;
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
        IMPORT_C void SizeChanged();
        IMPORT_C TSize MinimumSize();
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();

    protected:  // Methods

    // Methods from base classes

        /**
        * From <code>MCoeControlObserver</code> Handle control event.
        * By default, handles <code>EEventStateChanged</code> by calling
        * <code>HandleControlStateChangeL</code> and
        * <code>EEventInteractionRefused</code> by calling
        * <code>HandleInteractionRefused</code>.
        * @param aControl The control reporting the event
        * @param aEventType The event type
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

    // New Methods
        
        /**
        * Tries to initiate user exit of the Dialog when the button identified
        * by <code>aButtonId</code> is pressed, if this button is one that
        * should exit the Dialog.
        * See <code>OkToExitL</code> for the buttons that can exit a Dialog
        * @param aButtonId The ID of button.
        */
        IMPORT_C void TryExitL(TInt aButtonId);

        /**
        * Adjusts the IDs of all controls on the page identified by
        * <code>aPageId</code>, by incrementing their ID values by
        * <code>aControlIdDelta</code>.
        * @param aPageId The page on which the control IDs are to be adjusted.
        * @param aControlIdDelta The amount by which to increment the IDs.
        */
        IMPORT_C void AdjustAllIdsOnPage(TInt aPageId,TInt aControlIdDelta);

        /**
        * Constructs a 'sleeping' Dialog from the resources identified by
        * aResourceId (a sleeping Dialog is one which can be displayed at
        * any time, since its memory resources are pre-allocated).
        * @param aResourceId Resource ID.
        */
        IMPORT_C void ConstructSleepingDialogL(TInt aResourceId);

        /**
        * Constructs a sleeping Dialog from the resources identified by
        * aResourceId at a high priority on the control stack.
        * @param aResourceId Resource ID.
        */
        IMPORT_C void ConstructSleepingAlertDialogL(TInt aResourceId);

        /**
        * Rouses a sleeping Dialog by dynamically constructing it and then
        * bringing it to the front.
        * @return ETrue if the Dialog is run successfully. EFalse if it fails.
        */
        IMPORT_C TInt RouseSleepingDialog();

        /**
        * Exits a sleeping Dialog without deleting it.
        */
        IMPORT_C void ExitSleepingDialog();

        /**
        * Returns the ID of the control in the line that has focus.
        * @return ID of the control.
        */
        IMPORT_C TInt IdOfFocusControl() const;

        /**
        * Returns the line index of the control <code>aControl</code> or
        * <code>KErrNotFound</code> if the control is not on the active page
        * @param aControl The control for which the line index is required
        * @return The line index, or KErrNotFound if the control is
        * not found on the active page.
        */
        IMPORT_C TInt FindLineIndex(const CCoeControl& aControl) const;

        /**
        * Returns a pointer to the line containing the control identified by
        * <code>aControlId</code>.
        * Does not imply transfer of ownership.
        * @param aControlId The ID of the control
        * @return A pointer to the line containing the control identified
        * by <code>aControlId</code>
        */
        IMPORT_C CEikCaptionedControl* Line(TInt aControlId) const;

        /**
        * Returns a pointer to the current line.
        * Does not imply transfer of ownership
        * @return A pointer to the current line.
        */
        IMPORT_C CEikCaptionedControl* CurrentLine() const;

        /**
        * Rotates the focus by aDelta steps.
        * Each line is a single step, as are Dialog tabs.
        * @param aDelta The number of steps.
        * @return ETrue if rotation of focus is successful, EFalse if there are
        * no lines in the Dialog or the rotation is otherwise unsuccessful.
        */
        IMPORT_C TBool RotateFocusByL(TInt aDelta);

        /**
        * Returns the index of the Dialog's active page.
        * Pages are indexed from 0 in the order that they are added.
        * @return Index of the current page.
        */
        IMPORT_C TInt ActivePageIndex() const;

        /**
        * Recalculates the minimum sizes of the lines on the active page.
        */
        IMPORT_C void ResetLineMinimumSizes();

        /**
        * Swaps the the button group container with a new container aContainer.
        * The Dialog takes ownership of the new container.
        * Returns a pointer to the old button group container and transfers ownership.
        * @param aContainer The new button group container
        * @return A pointer to the old button group container that is no longer
        * owned by the Dialog
        */
        IMPORT_C CEikButtonGroupContainer* SwapButtonGroupContainer(CEikButtonGroupContainer* aContainer);

        /**
        * A Dialog uses a proxy to observe button commands. This means that
        * Dialog subclasses can directly observe commands issued by controls
        * added to the Dialog pages or by menus launched by the Dialog.
        * @return A pointer to the Dialog's internal button command observer
        */
        IMPORT_C MEikCommandObserver* ButtonCommandObserver() const;

        /**
        * Handles a Dialog button press for the button with the ID
        * <code>aButtonId</code>.The Cancel button press is not passed to the
        * handler unless <code>EEikDialogFlagNotifyEsc</code> is set.
        * @param aButtonId Button ID.
        * @return ETrue if the Dialog is ready to exit. Returns ETrue by default.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
        * Initializes the Dialog's controls before the Dialog is sized, and
        * before it has been activated.
        */
        IMPORT_C virtual void PreLayoutDynInitL();

        /**
        * Initializes the Dialog's controls after the Dialog has been sized,
        * but before it has been activated.
        * Empty by default.
        */
        IMPORT_C virtual void PostLayoutDynInitL();

        /**
        * Set the line that will initially receive focus. By default, this is
        * the first focusable line on the first page in the Dialog.
        * Reimplementations of this method must activate a page before
        * doing anything else.
        */
        IMPORT_C virtual void SetInitialCurrentLine();

        /**
        * Handles a state change in the control with ID <code>aControlId</code>
        * (empty by default).
        * @param aControlId The ID of the control.
        */
        IMPORT_C virtual void HandleControlStateChangeL(TInt aControlId);

        /**
        * Handles an attempt by the user to activate a dimmed button with ID
        * <code>aControlId</code>. Prints an info message by default
        * @param aControlId The ID of the control.
        */
        IMPORT_C virtual void HandleInteractionRefused(TInt aControlId);

        /**
        * Sets the size and position of the Dialog given the size hint
        * <code>aSize</code>.
        * By default, positions the Dialog in the centre of the screen.
        * @param aSize Dialog's size.
        */
        IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);

    private:  // Methods

    // New Methods
        
        IMPORT_C virtual void Reserved_3();
        IMPORT_C virtual void Reserved_4();
        void BaseConstructL();
        void StaticConstructL(TInt aResourceId);
        void DynamicConstructL();
        void CreateTitleBarL();
        void CreateButtonGroupContainerL(TInt aResourceId);
        void CreatePageSelectorL();
        void CreatePageSelectorL(TInt aResourceId);
        TInt WaitAsRequired();
        TKeyResponse TryAnimateButtonAndExitL(TInt aKeycode);
        void GetAutoValues();
        void CommonConstructSleepingDialogL(TInt aResourceId);
        void ConstructMarginsFromResourceL(TInt aResourceId);
        void IncludeMargins(TSize& aPreferredSize);
        void ResizeRect(TRect& aRect);
        TSize PreferredSize(const TSize& aMaxSize,TBool aForTallestControlOnly) const;
        void DrawBorder(CGraphicsContext& aGc, const TRect& aRect, const TRect& aDrawRect) const;
        TRect InnerRect(TRect& aRect) const;
        TMargins BorderMargins() const;
        TSize BorderSizeDelta() const;
        void DrawHelpButton(CWindowGc& aGc) const;
        void DrawClipboardButton(CWindowGc& aGc) const;
        void FadeBehindDialog(TBool aFade) const;
        TInt ControlInButtonGroupContainer(CCoeControl* aControl);
        void CheckNeedsClipboardButton(TBool aAddingLine);
        TKeyResponse OfferKeyEventToControlL(const TKeyEvent& aKeyEvent,TEventCode aType);
        void SetPageSelectorMargins();
        TBool HasHelpButton() const;
        void HandleClipboardCommand(TInt aCommand);
        void UpdateClipboardButton();
        void SetClipBoardMenuActioned(TBool aActioned);
//
// Deprecated interfaces.
// Defined in EIKDLGUT.CPP.
//

    public:  // Methods
        /** @deprecated */
        IMPORT_C void DeclareAutoTextEditorL(TInt aId,TDes* aText);
        /** @deprecated */
        IMPORT_C void DeclareAutoChoiceList(TInt aId,TInt* aCurrentItem);
        /** @deprecated */
        IMPORT_C void DeclareAutoNumberEditor(TInt aId,TInt* aNumber);
        /** @deprecated */
        IMPORT_C void DeclareAutoRangeEditor(TInt aId,SEikRange* aRange);
        /** @deprecated */
        IMPORT_C void DeclareAutoTimeEditor(TInt aId,TTime* aTime);
        /** @deprecated */
        IMPORT_C void DeclareAutoDateEditor(TInt aId,TTime* aDate);
        /** @deprecated */
        IMPORT_C void DeclareAutoTimeAndDateEditor(TInt aId,TTime* aTimeAndDate);
        /** @deprecated */
        IMPORT_C void DeclareAutoDurationEditor(TInt aId,TTimeIntervalSeconds* aDuration);
        /** @deprecated */
        IMPORT_C void DeclareAutoTimeOffsetEditor(TInt aId,TTimeIntervalSeconds* aTimeOffset);
        /** @deprecated */
        IMPORT_C void DeclareAutoLatitudeEditor(TInt aId,SEikDegreesMinutesDirection* aLatitude);
        /** @deprecated */
        IMPORT_C void DeclareAutoLongitudeEditor(TInt aId,SEikDegreesMinutesDirection* aLongitude);
        /** @deprecated */
        IMPORT_C void DeclareAutoTwipsEditorL(TInt aId,TInt* aValue);
        /** @deprecated */
        IMPORT_C void DeclareAutoFixedPointEditor(TInt aId,TInt* aValue);
        /** @deprecated */
        IMPORT_C void DeclareAutoCheckBox(TInt aId,CEikButtonBase::TState* aState);
        /** @deprecated */
        IMPORT_C void DeclareAutoSecretEditor(TInt aId,TDes* aText);
        /** @deprecated */
        IMPORT_C void DeclareAutoHorOptionButList(TInt aId,TInt* aSet);
        /** @deprecated */
        IMPORT_C void AddAutoTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TDes* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoGlobalTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);
        /** @deprecated */
        IMPORT_C void AddAutoRichTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);
        /** @deprecated */
        IMPORT_C void AddAutoChoiceListL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aMaxChar,MDesCArray* aArray,TInt* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoNumberEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoRangeEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,HBufC* aSeparatorText,SEikRange* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoTimeEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TTime* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax, TBool aNoPopout,TTime* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoTimeAndDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TBool aNoPopout,HBufC* aInterveningText,TTime* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoDurationEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoTimeOffsetEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoLatitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForNorth,TChar aKeyToMatchForNorth,HBufC* aTextForSouth,TChar aKeyToMatchForSouth,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);
        /** @deprecated */
        IMPORT_C void AddAutoLongitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForEast,TChar aKeyToMatchForEast,HBufC* aTextForWest,TChar aKeyToMatchForWest,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);
        /** @deprecated */
        IMPORT_C void AddAutoFloatEditorL(const TDesC& aPrompt,TInt aId,const TReal& aMin,const TReal& aMax,TReal* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoTwipsEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoFixedPointEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aRetValue,TInt aDecimalPlaces);
        /** @deprecated */
        IMPORT_C void AddAutoCheckBoxL(const TDesC& aPrompt,TInt aId,CEikButtonBase::TState* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoSecretEditorL(const TDesC& aPrompt,TInt aId,TDes* aReturn);
        /** @deprecated */
        IMPORT_C void AddAutoTelephoneNumberEditorL(const TDesC& aPrompt,TInt aId,CEikTelephoneNumberEditor::TTelephoneEditorMode aMode, TInt aFlags, TPtrC* aPromptArray, TInt aWidth,TDes* aReturn);

    protected: // Methods
        /** @deprecated */
        IMPORT_C void SetLabelL(TInt aControlId, const TDesC& aDes);
        /** @deprecated */
        IMPORT_C void SetLabelL(TInt aControlId, TInt aResourceId);
        /** @deprecated */
        IMPORT_C void SetLabelReserveLengthL(TInt aControlId, TInt aLength);
        /** @deprecated */
        IMPORT_C void SetEdwinTextL(TInt aControlId, const TDesC* aDes);
        /** @deprecated */
        IMPORT_C void SetTextEditorTextL(TInt aControlId,const CGlobalText* aGlobalText);
        /** @deprecated */
        IMPORT_C void ResetSecretEditor(TInt aControlId);
        /** @deprecated */
        IMPORT_C void SetCheckBoxState(TInt aControlId, CEikButtonBase::TState aState);
        /** @deprecated */
        IMPORT_C void SetChoiceListCurrentItem(TInt aControlId, TInt aItem);
        /** @deprecated */
        IMPORT_C void SetFloatingPointEditorValueL(TInt aControlId, const TReal* aValue);
        /** @deprecated */
        IMPORT_C void SetFixedPointEditorValueL(TInt aControlId,TInt aValue);
        /** @deprecated */
        IMPORT_C void SetFixedPointEditorDecimal(TInt aControlId, TInt aDecimal);
        /** @deprecated */
        IMPORT_C void SetTwipsEditorValueL(TInt aControlId, TInt* aValue);
        /** @deprecated */
        IMPORT_C void SetNumberEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted
        /** @deprecated */
        IMPORT_C void SetNumberEditorValue(TInt aControlId, TInt aNumber);
        /** @deprecated */
        IMPORT_C void SetFloatEditorMinAndMax(TInt aControlId,TInt aMin,TInt aMax);
        /** @deprecated */
        IMPORT_C void SetFloatEditorValueL(TInt aControlId,TReal aFloat);
        /** @deprecated */
        IMPORT_C void SetRangeEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted
        /** @deprecated */
        IMPORT_C void SetRangeEditorValue(TInt aControlId, const SEikRange& aRange);
        /** @deprecated */
        IMPORT_C void SetTTimeEditorMinAndMax(TInt aControlId, const TTime& aMinimumTime, const TTime& aMaximumTime); // only values inside the initial min and max are permitted
        /** @deprecated */
        IMPORT_C void SetTTimeEditorValue(TInt aControlId, const TTime& aTime);
        /** @deprecated */
        IMPORT_C void SetDurationEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial min and max are permi
        /** @deprecated */
        IMPORT_C void SetDurationEditorValue(TInt aControlId, const TTimeIntervalSeconds& aDuration);
        /** @deprecated */
        IMPORT_C void SetTimeOffsetEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); // only values inside the initial min and max are
        /** @deprecated */
        IMPORT_C void SetTimeOffsetEditorValue(TInt aControlId, const TTimeIntervalSeconds& aTimeOffset);
        /** @deprecated */
        IMPORT_C void SetLatitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLatitude);
        /** @deprecated */
        IMPORT_C void SetLongitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLongitude);
        /** @deprecated */
        IMPORT_C void SetOptionButtonState(TInt aControlId, CEikButtonBase::TState aState);
        /** @deprecated */
        IMPORT_C void SetHorOptionButListCurrentSet(TInt aControlId,TInt aSetButId);
        /** @deprecated */
        IMPORT_C void SetTelephoneEditorMode(TInt aControlId,CEikTelephoneNumberEditor::TTelephoneEditorMode aMode);
        /** @deprecated */
        IMPORT_C void SetTelephoneEditorNumberL(TInt aControlId,const TDesC& aNumber);
        /** @deprecated */
        IMPORT_C void SetTelephoneEditorNumberL(TInt aControlId,const TDesC& aCountry,const TDesC& aArea,const TDesC& aNumber);
        /** @deprecated */
        IMPORT_C void SetSoundSelectorSound(TInt aControlId, const TDesC& aSound);
        /** @deprecated */
        IMPORT_C void SetListBoxCurrentItem(TInt aControlId, TInt aItem);
        /** @deprecated */
        IMPORT_C void SetCharEditor(TInt aControlId, TChar aChar);
        /** @deprecated */
        IMPORT_C void SetFileNameL(TInt aControlId, const TDesC* aFileName);
        /** @deprecated */
        IMPORT_C void SetGraySelectorColor(TInt aControlId, TRgb aColor);
        /** @deprecated */
        IMPORT_C void GetLabelText(TDes& aDes,TInt aControlId) const;
        /** @deprecated */
        IMPORT_C void GetEdwinText(TDes& aDes,TInt aControlId) const;
        /** @deprecated */
        IMPORT_C void GetTextEditorText(CGlobalText*& aGlobalText,TInt aControlId);
        /** @deprecated */
        IMPORT_C void GetSecretEditorText(TDes& aDes,TInt aControlId) const;
        /** @deprecated */
        IMPORT_C CEikButtonBase::TState CheckBoxState(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TInt ChoiceListCurrentItem(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TReal FloatingPointEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TInt FixedPointEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TInt FixedPointEditorDecimal(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TInt TwipsEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TReal FloatEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TInt NumberEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C SEikRange RangeEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TTime TTimeEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TTimeIntervalSeconds DurationEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TTimeIntervalSeconds TimeOffsetEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C SEikDegreesMinutesDirection LatitudeEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C SEikDegreesMinutesDirection LongitudeEditorValue(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C void GetAutoValuesFromPage(CEikCapCArray* aLines);
        /** @deprecated */
        IMPORT_C CEikButtonBase::TState OptionButtonState(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TInt HorOptionButListCurrentSet(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C void GetTelephoneEditorNumber(TInt aControlId,TDes& aNumber) const;
        /** @deprecated */
        IMPORT_C void GetSoundSelectorSound(TDes& aSound, TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TInt ListBoxCurrentItem(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TChar CharEditor(TInt aControlId) const;
        /** @deprecated */
        IMPORT_C void GetFileName(TFileName* aFileName,TInt aControlId) const;
        /** @deprecated */
        IMPORT_C TRgb GraySelectorColor(TInt aControlId) const;

    private:     // Data

        CEikMover* iTitleBar;
        CEikDialogPageSelector* iPageSelector;
        CEikButtonGroupContainer* iButtonGroupContainer;
        CEikDialogButtonCommandObserver* iButtonCommandObserver;
        TUint iDialogFlags;
        CEikDialogExtension* iExt;
        TMargins8 iMargins;

    };

 
#endif      // EIKDIALG_H   
            
// End of File
