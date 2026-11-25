// COECNTRL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COECNTRL_H__)
#define __COECNTRL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__GULALIGN_H__)
#include <gulalign.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

#if !defined(__COEHELP_H__)
#include <coehelp.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

#if !defined(__COEMOP_H__)
#include <coemop.h>
#endif

class TResourceReader;
class CCoeEnv;
class MCoeControlContext;
class CCoeControlExtension;

/** 
 * The <code>TCoeColorUse</code> class for logical color used when drawing in controls.
 * This class pairs a logical color value with an explanation of how it is used 
 * when drawing a control. The explanation is in terms of categories of use, for
 * example, in the <code>TGround</code> category, the color can used for either 
 * the foreground or background.
 * 
 * @lib [what]
 * @publishedAll 
 * @released 
 */
class TCoeColorUse

    {
public:
    /** 
     * The enumeration <code>TGround</code> specifies the foreground and 
     * background category flags. 
     */
    enum TGround
        {
        /** 
         * the logical color is used to draw the control when it is in the 
         * foreground
         */
        EFore=0x01,
        /** 
         * the logical color is used to draw the control when it is in the 
         * background
         */
        EBack=0x02
        };

    /** 
     * The enumeration <code>TAreas</code> specifies the flags that control 
     * the area in which color is used
     */
    enum TAreas
        {
        /** the logical color is used to draw a control's contents */
        EContents=0x10,
        /** the logical color is used to draw a control's highlighted contents */
        EHighlights=0x20,
        /** the logical color is used to draw a control's surrounds */
        ESurrounds=0x40,
        /** the logical color is used to draw a control's borders */
        EBorders=0x80
        };

    /** The enumeration <code>TFocus</code> specifies the focus category flags */
    enum TFocus
        {
        /** 
         * the logical color is used to draw the control when active and either 
         * focused or unfocused
         */
        EActive=0x100,
        /** 
         * the logical color is used to draw the control when dimmed and either 
         * focused or unfocused
         */
        EDimmed=0x200,
        /** the logical color is used to draw the control when it is shadowed */
        EShadowed=0x400,    
        /** 
         * the logical color is used to draw the control when focused and 
         * pressed
         */
        EPressed=0x800
        };

    /** The enumeration <code>TState</code> specifies the state category flags. */
    enum TState
        {
        /** the logical color is used to draw the control in the normal state */
        ENormal=0x1000,
        /** the logical color is used to draw the control in the set state */
        ESet=0x2000,
        /** the logical color is used to draw the control in the checked state */
        EChecked=0x4000
        };

    /** The enumeration <code>TTones</code> specifies the tone flags. */
    enum TTones
        {
        /** the logical color is used to draw the control in neutral tones */
        ENeutral=0x10000,
        /** the logical color is used to draw the control in light tones */
        ELight=0x20000,
        /** the logical color is used to draw the control in midlight tones */
        EMidLight=0x40000,
        /** the logical color is used to draw the control in mid tones */
        EMid=0x80000,
        /** the logical color is used to draw the control in dark tones */
        EDark=0x100000
        };
public:
    /**
    * The default object constructor.
    * 
    * @remarks
    * @see
    */
    IMPORT_C TCoeColorUse();

    /**
    * Sets the use of the logical color.
    * 
    * @param aUse The use of the logical color. A valid value describing a 
    *             color use consists of choices of one value from each of the 
    *             enums <code>TGround</code>, <code>TAreas</code>, 
    *             <code>TFocus</code>, <code>TState</code>, and 
    *             <code>TTones</code> ORed together
    * @remarks
    * @see
    */
    IMPORT_C void SetUse(TInt aUse);

    /**
    * Sets the logical color, which has its use described by this 
    * <code>TCoeColorUse</code> object. 
    *
    * @param aLogicalColor The logical color
    * @remarks
    * @see
    */
    IMPORT_C void SetLogicalColor(TInt aLogicalColor);

    /**
    * Gets the logical color that has its use described by this 
    * <code>TCoeColorUse</code> object.
    * 
    * @return The logical color
    * @remarks
    * @see
    */
    IMPORT_C TInt LogicalColor() const;

    /**
    * Gets the value describing the use of the logical color.
    *
    * @return the use of the logical color. This is the logical OR of one value 
    *         from each of the enums <code>TGround</code>, <code>TAreas</code>, 
    *         <code>TFocus</code>, <code>TState</code>, and <code>TTones</code> 
    * @remarks
    * @see
    */
    IMPORT_C TInt Use() const;
    
    /**
    * Tests whether the logical color is used as a foreground color.
    *
    * @return <code>ETrue</code> if the logical color is used as a foreground 
    *         color; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsForeground() const;

    /**
    * Tests whether the logical color is used as a background color.
    *
    * @return <code>ETrue</code> if the logical color is used as a background 
    *         color; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsBackground() const;
    
    /**
    * Tests whether the logical color is used to draw a control's contents. 
    * The contents are the parts of the control that the user interacts with,
    * for example, an editor field, the contents of a listbox, or the page of 
    * a web browser. This is opposed to the fascia (or surrounds), which are 
    * the parts of controls that make up the illusion that the contents are 
    * set into some sort of solid frontage.
    *
    * @return <code>ETrue</code> if the logical color is used to draw a 
    *         control's contents; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsContents() const;

    /**
    * Tests whether the logical color is used to draw a control's highlighted 
    * contents. 
    *
    * @return <code>ETrue</code> if the logical color is used to draw a 
    *         control's highlighted contents; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsHighlights() const;

    /**
    * Tests whether the logical color is used to draw a control's surrounds.
    *
    * @return <code>ETrue</code> if the logical color is used to draw a 
    *         control's surrounds; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsSurrounds() const;

    /**
    * Tests whether the logical color is used to draw a control's borders.
    *
    * @return <code>ETrue</code> if the logical color is used to draw a 
    *         control's borders; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsBorders() const;

    /**
    * Tests whether the logical color is active. For example, whether or not 
    * it is used to draw the control when active and either focused or 
    * unfocused.
    *
    * @return <code>ETrue</code> if the logical color is active; 
    *         <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsActive() const;

    /**
    * Tests whether the logical color is used to draw the control when dimmed 
    * and either focused or unfocused. 
    *
    * @return <code>ETrue</code> if the logical color is used to draw the 
    *         control when dimmed and either focused or unfocused; 
    *         <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsDimmed() const;

    /**
    * Tests whether the logical color is used to draw the control when focused 
    * and tapped.
    *
    * @return <code>ETrue</code> if the logical color is used to draw the 
    *         control when focused and tapped; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsPressed() const;

    /**
    * Tests whether the logical color is used to draw the control in a normal 
    * state.
    *
    * @return <code>ETrue</code> if the logical color is used to draw the 
    *         control in a normal state; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsNormal() const;

    /**
    * Tests whether the logical color is used to draw the control in a set 
    * state. 
    *
    * @return <code>ETrue</code> if the logical color is used to draw the 
    *         control in a set state; <code>EFalse</code> otherwise 
    * @remarks
    * @see
    */
    IMPORT_C TBool IsSet() const;
private:
    TInt iLogicalColor;
    TInt iUse;
    };

/** @internal Component */
class RCoeExtensionStorage

    {
public:
    RCoeExtensionStorage();
    void Close();
    TInt& Flags();
    TInt Flags() const;
    void SetExtension(CCoeControlExtension* aExtension);
    CCoeControlExtension* Extension() const;
private:
    inline TBool IsFlags() const;
private:
    union
        {
        TInt iFlags;
        CCoeControlExtension* iExtension;
        };
    };

/** 
 * The <code>CCoeControl</code> class is the control base class from which all 
 * other controls are derived.
 *
 * @lib [what]
 * @publishedAll
 * @released 
 */
class CCoeControl : public CBase

    {
public:
   /**
    * The default object constructor.
    */
    IMPORT_C CCoeControl();

    /**
    * The object destructor.
    */
    IMPORT_C ~CCoeControl();
    // client interface
    
   /**
    * Handles key events offered to the control by the control environment. 
    * 
    * @param aKeyEvent The key event offered
    * @param aType	The type of key event, either: <code>EEventKey</code>, 
    *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
    * @return indicates whether or not the key event was used by this 
    *         control. <code>EKeyWasConsumed</code> if the control takes 
    *         action on the key event; <code>EKeyWasNotConsumed</code> 
    *         otherwise
    * @remarks
    * @see 
    */
    IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    /**
    * Sets this control as visible or invisible. This method causes the control 
    * to disappear or reappear. When a control is created, it is made visible 
    * by default. <code>MakeVisible()</code> can be called before or after the 
    * control is activated. This function can be overridden. The visibility of 
    * the control can be queried using <code>IsVisible()</code>. If 
    * <code>MakeVisible()</code> is used to make a component visible, and the 
    * control captures the pointer (see CapturesPointer()), 
    * <code>MakeVisible()</code> throws away any pending pointer events for 
    * that control. Typically, this method is used for scrollbars, or for 
    * dialogs where some user responses are not required in some circumstances.
    *
    * @param aVisible <code>ETrue</code> to make the control visible;
    *                 <code>EFalse</code> to make it invisible
    * @remarks
    * @see
    */
    IMPORT_C virtual void MakeVisible(TBool aVisible);

    /**
    * Sets the control to be dimmed. This method sets a flag within the control 
    * that indicates whether or not the control is dimmed. Typically, this is 
    * used to show that the control is temporarily unavailable. 
    * <code>SetDimmed()</code> does not initiate a redraw of the control. If a
    * redraw is required after calling <code>SetDimmed()</code>, the 
    * application should call <code>DrawNow()</code> or 
    * <code>DrawDeferred()</code>. The control's <code>Draw()</code> method 
    * should draw the control appropriately according to whether it is dimmed 
    * or not. (This can be enquired using <code>IsDimmed()</code>.)
    *
    * @param aDimmed <code>ETrue</code> to dim the control; <code>EFalse</code>
    *                to set the control as not dimmed
    * @remarks
    * @see
    */
    IMPORT_C virtual void SetDimmed(TBool aDimmed);

    /**
    * Sets the control's containing window by copying it from 
    * <code>aContainer</code>. If a control context has not been set previously,
    * this method also copies one from <code>aContainer</code>. This method
    * can only be called on non-window-owning controls. Alternatively, if the 
    * container is a window-owning control, use <code>SetContainerWindow()</code>.
    * 
    * @param aContainer The compound control that is the container for this 
    *                   control
    * @remarks
    * @see
    */
    IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);

    /**
    * Sets the control's containing window, if the container is a window-owning 
    * control. This method can only be called on non-window-owning controls. 
    * <b>Note</b>: The container's window can be accessed using 
    * <code>Window()</code>, <code>DrawableWindow()</code>, or 
    * <code>BackedUpWindow()<code>.
    *
    * @param aWindow The window owned by the container control
    * @remarks
    * @see
    */
    IMPORT_C void SetContainerWindowL(RWindow& aWindow); 

    /**
    * Sets the control's containing window to be a backed-up window. The 
    * method can only be called on non-window-owning controls. <b>Note</b>:
    * The container's window can be accessed using <code>Window()</code>, 
    * <code>DrawableWindow()</code>, or <code>BackedUpWindow()<code>.
    *
    * @param aWindow The backed-up window owned by the container control
    * @remarks
    * @see
    */
    IMPORT_C void SetContainerWindowL(RBackedUpWindow& aWindow);

    /**
    * Constructs a control from a resource file. This method has an empty 
    * default implementation. It should be implemented if the control is to be 
    * displayed within a dialog. It should initialize the control, reading in 
    * resource values from the resource file. <b>Note</b>: If a control is not
    * displayed in a dialog, it is necessary to set the control's associated 
    * window using <code>SetContainerWindowL()</code>. Since this may leave, 
    * the control should be constructed using <code>ConstructL()</code>.
    *
    * @param aReader The resource reader with which to access the control's 
    *                resource values
    * @remarks The resource type is [what]
    * @see
    */
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

    /**
    * Activates the control. The application should call this method on all 
    * controls that are not components in a compound control. The purpose of 
    * this method is that controls are not always ready to be drawn as soon as 
    * they have been constructed. For example, it may not be possible to set 
    * the control's extent during construction, but its extent should always 
    * be set before it is drawn. Similarly, if a control is to be made 
    * invisible, this should be done before it is activated. The default 
    * implementation sets a flag in the control to indicate that it is ready 
    * to be drawn. If the control is a compound control, the default 
    * implementation also calls <code>ActivateL()</code> for all the control's
    * components. To get the control's components it uses 
    * <code>CountComponentControls()</code> and <code>ComponentControl()</code>,
    * which should be implemented by the compound control. Typically, 
    * <code>ActivateL()</code> is  called from the control's 
    * <code>ConstructL()</code> method. <b>Note</b>: This method can be 
    * overridden. This is useful for doing late initialization of the control, 
    * using information that was not available at the time the control was 
    * created. For example, a text editor might override <code>ActivateL()</code> 
    * and use it to enquire whether it is focused. If it is, it makes the 
    * cursor and any highlighting visible. At the time that the editor is 
    * created, it does not know whether or not it has keyboard focus.
    * 
    * @remarks
    * @see
    */
    IMPORT_C virtual void ActivateL();

   /**
    * Prepares the control for loss of focus. A control that is displayed 
    * within a dialog should implement this method if it is required
    * to validate data entered into the control. This method is called by the 
    * dialog framework immediately before it removes keyboard focus from a 
    * control within a dialog. It is intended to be used for validating the 
    * state of the control. For example, if the control allows the user to 
    * enter a date, <code>PrepareForFocusLossL()</code> would normally check 
    * to make sure the user did not enter an invalid date such as February 31st.
    * If an invalid state is detected, <code>PrepareForFocusLossL()<code> 
    * should leave and issue a message to the user, if appropriate. If it does 
    * leave, the framework does not perform the action that would have resulted 
    * in the control losing focus, and focus remains with the control to allow 
    * valid data to be entered. In standard GUI dialogs, various actions can 
    * result in a control losing focus, for instance if the user taps the OK 
    * button or presses the Enter key to close the dialog and enter the 
    * information, or if the user navigates away from the focussed control. 
    * These actions result in <code>PrepareForFocusLossL()</code> being called 
    * on the control that currently has keyboard focus. The default 
    * implementation of this method is empty, and it is not called from within 
    * the UI control framework. The method exists only to provide an interface 
    * to the control for the GUI and any other UI library.
    * 
    * @remarks
    * @see 
    */
    IMPORT_C virtual void PrepareForFocusLossL();

   /**
    * Prepares the control for gaining focus. Implementations can take 
    * any action required, such as updating control information. By 
    * default, the implementation is empty.  
    * 
    * @remarks
    * @see 
    */
    IMPORT_C virtual void PrepareForFocusGainL();

    /**
    * Sets the control's appearance when it is next to other controls. Its 
    * intended use is to remove the double border that may occur if two 
    * controls, both with borders, are adjacent within a container control. 
    * This method has an empty default implementation, and is not used within 
    * the UI control framework. However, it may be implemented and used by 
    * derived control classes. 
    *
    * @param aAdjacent Typically, a value defined in <code>TGulAdjacent</code>
    * @remarks
    * @see
    */
    IMPORT_C virtual void SetAdjacent(TInt aAdjacent);

    /**
    * Sets an associated control. This method can be used to establish 
    * co-ordinated groups of controls, for instance in dialogs without 
    * specific application co-operation. This method has an empty default 
    * implementation, and is not used within the UI control framework. 
    * However, it may be implemented and used by derived control classes.
    *
    * @param aNeighbor A control to be used by this method
    * @remarks
    * @see
    */
    IMPORT_C virtual void SetNeighbor(CCoeControl* aNeighbor);

    /**
    * Tests if the control has a border. When component controls are arranged 
    * in a container, the container control may need to know whether or not 
    * the components have borders, as this may affect the way the components 
    * are laid out within the container. The default implementation of this 
    * method returns <code>EFalse</code>, but can be overridden to provide the 
    * required functionality.
    *
    * @return <code>ETrue</code> if the control has a border; <code>EFalse</code> 
    *         if the control does not have a border. The default implementation 
    *         of this method returns <code>EFalse<code>
    * @remarks
    * @see
    */
    IMPORT_C virtual TBool HasBorder() const;

    /**
    * Sets the control's minimum required size. If the control is to be 
    * displayed inside a dialog, this method should be overridden by the 
    * concrete control class. Standard GUI dialogs set the size and 
    * position of their components automatically and use this method to 
    * enquire the minimum size that a control requires. Other container 
    * controls that automatically calculate the layout of their components 
    * may also use this method.
    *
    * @return the minimum size required by the control
    * @remarks
    * @see
    */
    IMPORT_C virtual TSize MinimumSize();

    /**
    * Handles a change to the control's resources that are shared across the 
    * environment. For color scheme changes, <code>DrawDeferred()</code> is 
    * called in order to redraw the control.
    * 
    * @param aType A <code>TInt</code> message UID value for the resource 
    *              that has changed
    * @remarks
    * @see <code>HandleComponentControlsResourceChange()</code>
    */
    IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u

    /**
    * Gets the list of logical colors used for drawing the control. This 
    * method is no longer used. Skin functionality manages the colors for 
    * this control.
    * 
    * @param aColorUseList Not used
    * @remarks
    * @see
    */
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

    /**
    * Gets the control's help context. The default implementation is empty. 
    * The method must be implemented in derived classes to associate the 
    * control with a particular Help file and topic in a context-sensitive 
    * application. The implementation should set the public data members of 
    * <code>TCoeHelpContext</code> to the required Help file UID and context 
    * descriptor, as created using the context-sensitive Help compiler.
    *
    * @param aContext The control's Help context
    * @remarks
    * @see
    */
    IMPORT_C virtual void GetHelpContext(TCoeHelpContext& aContext) const;

    /**
    * Returns the input capabilities of the control. Classes that override 
    * <code>CCoeControl::OfferKeyEventL()</code> should also override this 
    * method, returning a <code>TCoeInputCapabilities</code> object whose 
    * attributes correspond to the behavior of the <code>OfferKeyEventL()</code>
    * method. The default implementation returns 
    * <code>TCoeInputCapabilities::ENone</code>. It is not necessary to call 
    * <code>InputCapabilities()</code> on any component controls from inside a
    * class's <code>InputCapabilities()</code> method. This is done 
    * automatically by the UI Control Framework.
    *
    * @return The control's input capabilities
    * @remarks This method is used, for example, when the control is queried 
    *          by the FEP about the types of inputs that are consumed by the 
    *          control
    * @see
    */
    IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;

    /**
    * Gets the input capabilities of the control and all its components.
    *
    * @return the input capabilities of the control
    * @remarks
    * @see
    */
    IMPORT_C TCoeInputCapabilities RecursivelyMergedInputCapabilities() const; // not available before Release 006

    /**
    * Draws the control. This method is called by an application or other code.
    * The application should call this method when the control is first created 
    * and is ready for drawing, or if a change in application data or the 
    * control's internal state means that entire control's appearance is no 
    * longer up-to-date. Partial redrawing of a control is sometimes more 
    * appropriate than drawing the entire control, and in this case 
    * <code>DrawNow()</code> should not be used. <code>DrawNow()</code> is 
    * implemented by <code>CCoeControl</code> and must not be overridden. It 
    * calls <code>Draw()</code> on the control itself, and also on all its 
    * component controls, if it is a compound control. (To do this, it uses 
    * <code>CountComponentControls()</code> and <code>ComponentControl()</code>, 
    * which should be implemented by the derived control class.) If the control 
    * is a window-owning control, it also calls <code>Draw()</code> for its 
    * child windows (if any).
    * 
    * @remarks
    * @see
    */
    IMPORT_C void DrawNow() const;

    /**
    * Draws the control, with low priority. This method is called by an 
    * application or other code. It causes the control area to be marked as 
    * invalid, which will eventually cause a redraw initiated by the window 
    * server. The control framework handles redraw events at a lower priority 
    * than user input events, which means that any pending user input events 
    * will be processed before the redraw event. Therefore,
    * <code>DrawDeferred()</code> allows a control to do drawing at a lower 
    * priority than drawing performed by <code>DrawNow()</code>. An advantage 
    * of using <code>DrawDeferred()</code> is that if you make multiple calls 
    * to <code>DrawDeferred()</code> on the same area of a control, the window 
    * server will not generate a redraw event to do drawing that has already 
    * been superceded. If you make multiple calls to <code>DrawNow()</code>, 
    * however, all of them get processed, even if they have already been 
    * superceded by the time they are processed.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void DrawDeferred() const;

    /**
    * Sets this control to have the keyboard focus. It sets the value of a 
    * focus flag within the control to the value given by <code>aFocus</code>. 
    * This flag indicates whether or not the control has keyboard focus, and 
    * its value can be enquired using <code>IsFocused()</code>. It then calls 
    * <code>FocusChanged()</code>, passing it the value given by 
    * <code>aDrawNow</code>, unless the control is invisible or not activated, 
    * in which case it passes <code>ENoDrawNow</code>. Setting focus does not 
    * initiate a redraw. The control's implementation of 
    * <code>FocusChanged()</code> should do this, if required. The control's 
    * <code>Draw()</code> method, or that of its container, should normally 
    * change the appearance of the control to indicate whether or not it 
    * currently has focus.
    *
    * @param aFocus <code>ETrue</code> sets the control as having keyboard 
    *               focus; <code>EFalse</code> sets it as not having keyboard 
    *               focus
    * @param aDrawNow The flag to pass to <code>FocusChanged()</code>
    * @remarks
    * @see
    */
    IMPORT_C void SetFocus(TBool aFocus,TDrawNow aDrawNow=ENoDrawNow);

    /**
    * Sets the control's extent, specifying a size and a position. <b>Note,/b>:
    * Calling this method results in a call to <code>SizeChanged()</code>.
    *
    * @param aPosition The position of the control, relative to its associated 
    *                  window
    * @param aSize The size of the control, in pixels
    * @remarks
    * @see
    */
    IMPORT_C void SetExtent(const TPoint& aPosition,const TSize& aSize);

    /**
    * Sets the control's size. If the size, but not the position, of a control 
    * is set, then its position will default to <code>TPoint(0,0)</code>. 
    * <b>Note</b>: Calling this method results in a call to 
    * <code>SizeChanged()</code>.
    *
    * @param aSize The control's size, in pixels
    * @see
    */
    IMPORT_C void SetSize(const TSize& aSize);

    /**
    * Sets the control's position. If the control owns its containing window,
    * it achieves this by setting the position of the window. Otherwise, the 
    * position of the control is set relative to its containing window. The 
    * positions of the control's components are adjusted accordingly and 
    * <code>PositionChanged()</code> is called.
    *
    * @param aPosition The position of the top-left of the control, relative 
    *                  to its associated window
    * @remarks
    * @see
    */
    IMPORT_C void SetPosition(const TPoint& aPosition);

    /**
    * Sets the control's extent, specifying a rectangle. <b>Note</b>: Calling 
    * this method results in a call to <code>SizeChanged()</code>. 
    *
    * @param aRect The rectangle that defines the control's extent. The 
    *              rectangle's origin is relative to the origin of its 
    *              associated window
    * @remarks
    * @see
    */
    IMPORT_C void SetRect(const TRect& aRect);

    /**
    * Sets the control's extent to the whole screen. <b>Note</b>: Calling this 
    * method results in a call to <code>SizeChanged()</code>.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void SetExtentToWholeScreen();

    /**
    * Tests if the control has focus. Focus is set and unset using 
    * <code>SetFocus()</code>.
    *
    * @return <code>ETrue</code> if the control has focus; <code>EFalse</code> 
    *         otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool IsFocused() const;

    /**
    * Tests if the control is visible. Unless <code>MakeVisible()</code> has 
    * been called with argument <code>EFalse</code>, the control is visible.
    *
    * @return <code>ETrue</code> if the control is visible; <code>EFalse</code> 
    *         otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool IsVisible() const;

    /**
    * Tests if the control is dimmed. This method returns the value of a flag 
    * within the control, which is set and unset using <code>SetDimmed()</code>.
    * 
    * @return <code>ETrue</code> if the control is dimmed; <code>EFalse</code> 
    *         otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool IsDimmed() const;

    /**
    * Gets the control's associated drawable window. The control must be a 
    * window-owning control. This method should be called if it is not known 
    * whether the window is of type <code>RWindow</code> or 
    * <code>RBackedUpWindow</code>. <code>RDrawableWindow</code> is an abstract 
    * base class from which <code>RWindow</code> and <code>RBackedUpWindow</code> 
    * are derived.
    *
    * @return The control's associated window
    * @remarks
    * @see <code>Window()</code>
    */
    IMPORT_C RDrawableWindow* DrawableWindow() const;

    /**
    * Gets the control's size.
    *
    * @return The control's size, in pixels
    * @remarks
    * @see
    */
    IMPORT_C TSize Size() const;

    /**
    * Gets the control's position.
    *
    * @return The position of the control, relative to its associated window
    * @remarks
    * @see
    */
    IMPORT_C TPoint Position() const;

    /**
    * Gets the control's extent. The position of the top-left of the rectangle 
    * is <code>(0,0)</code> if the control owns its window. Otherwise, its 
    * position is relative to its window.
    *
    * @return The control's extent
    * @remarks
    * @see
    */
    IMPORT_C TRect Rect() const;

    /**
    * Gets the control's position relative to screen origin. The screen 
    * origin is its top-left corner. 
    *
    * @return The position of the control relative to the screen origin, in 
    *         pixels
    * @remarks
    * @see
    */
    IMPORT_C TPoint PositionRelativeToScreen() const;

    /**
    * Sets the control's observer.
    *
    * @param aObserver The observer
    * @remarks
    * @see
    */
    IMPORT_C void SetObserver(MCoeControlObserver* aObserver);

    /**
    * Gets the control's observer.
    *
    * @return The control's observer
    * @remarks
    * @see
    */
    IMPORT_C MCoeControlObserver* Observer() const;

    /**
    * Gets the control environment object for this control. 
    *
    * @return The control's control environment object
    * @remarks
    * @see
    */
    inline CCoeEnv* ControlEnv() const;

    /**
    * Gets the index of a control that is a component of this control.
    *
    * @param aControl The component control
    * @return the index of the component control within the compound control, 
    *         or <code>KErrNotFound</code> if <code>aControl</code> is not a 
    *         component of this control
    * @remarks
    * @see
    */
    IMPORT_C TInt Index(const CCoeControl* aControl) const;

    /**
    * @deprecated 
    * @see <code>SetFocusing()</code>
    */
    IMPORT_C void SetNonFocusing();

    /**
    * Sets the control as able to receive keyboard focus. 
    *
    * @param aFocusing <code>ETrue</code> if the control can have focus;
    *                  <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C void SetFocusing(TBool aFocusing); // not available before Release 005

   /**
    * Tests if the control can receive focus. 
    *
    * @return <code>ETrue</code> if the control cannot receive focus;
    *         <code>EFalse</code> otherwise
    * @remarks
    * @see <code>SetNonFocusing()</code> 
    */
    IMPORT_C TBool IsNonFocusing() const;

   /**
    * Set the control context for this control.
    *
    * @param aContext The context for this control
    * @remarks
    * @see
    */
    IMPORT_C void SetControlContext(MCoeControlContext* aContext);

   /**
    * Sets the control's context from another control.
    *
    * @param aControl The control whose context is copied
    * @remarks
    * @see
    */
    IMPORT_C void CopyControlContextFrom(const CCoeControl* aControl);

   /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C MCoeControlContext* ControlContext() const;

   /**
    * Gets the control context being used by this control. The method does not 
    * transfer ownership to the caller.
    *
    * @return The control context
    * @remarks
    * @see
    */
    IMPORT_C TBool OwnsWindow() const;

   /**
    * Tests if the window owned by the control is a backed-up window.
    *
    * @return <code>ETrue</code> if the window owned by this control is a 
    *         backed-up window; <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool IsBackedUp() const;

    /**
    * Sets pointer capture. Once set, pointer capture lasts until 
    * <code>SetPointerCapture()</code> is called on the control with 
    * <code>aCapture=EFalse</code>. Typically, this method is used by dialogs 
    * to discard any pointer events that occur outside of the dialog.
    * 
    * @param aCapture If <code>ETrue</code>, passes the following value as the 
    *                 argument to <code>RWindowBase::SetPointerCapture()</code>: 
    *                 <code>RWindowBase::TCaptureFlagAllGroups|RWindowBase::TCaptureFlagEnabled</code>, 
    *                 if the control's global capture flag is set to 
    *                 <code>ETrue</code> (see <code>SetGloballyCapturing()</code>) 
    *                 or <code>RWindowBase::TCaptureFlagEnabled</code>, 
    *                 if the control's global capture flag is set to 
    *                 <code>EFalse</code>. If <code>EFalse</code>, passes 
    *                 <code>EFalse</code> as the argument to 
    *                 <code>RWindowBase::SetPointerCapture()</code>
    * @remarks
    * @see <code>RWindowBase::SetPointerCapture()</code> 
    */
    IMPORT_C void SetPointerCapture(TBool aCapture=ETrue);

    /**
    * Claims pointer grab from another control. This ensures that all 
    * subsequent pointer events are delivered to it and not to the control that 
    * originally owned the grab. The method allows a control to claim the 
    * pointer grab only if the pointer is already grabbed by another control.
    *
    * @param aSendUpEvent Passed as the argument to 
    *                     <code>RWindowBase::ClaimPointerGrab()</code>
    * @remarks
    * @see <code>RWindowBase::ClaimPointerGrab()</code>
    * @remarks
    */
    IMPORT_C void ClaimPointerGrab(TBool aSendUpEvent=ETrue);

    /**
    * Sets the control to ignore pointer events until the next pointer up.
    * This means that all events until and including the next pointer up event 
    * are discarded and are not processed.
    * 
    * @remarks
    * @see
    */
    IMPORT_C void IgnoreEventsUntilNextPointerUp();

    /**
    * Sets the control's components to inherit the visibility setting of their
    * container control. If set, when <code>MakeVisible()</code> is called on 
    * the compound control, the visibility setting is propagated to all its 
    * components.
    *
    * @param aInherit If <code>ETrue</code>, the control's components inherit 
    *                 its visibility setting; if <code>EFalse</code> they do 
    *                 not
    * @remarks
    * @see
    */
    IMPORT_C void SetComponentsToInheritVisibility(TBool aInherit=ETrue);

    /**
    * Sets the global pointer capture flag. This flag indicates whether or not 
    * pointer capture should be global. The flag is used by 
    * <code>SetPointerCapture()</code> to determine what value to pass to 
    * <code>RWindowBase::SetPointerCapture()</code>. The default for the 
    * global capture flag, when a control is created, is <code>EFalse</code>.
    *
    * @param aGlobal The value for global capture flag
    * @remarks
    * @see
    */
    IMPORT_C void SetGloballyCapturing(TBool aGlobal);

    /**
    * Overrides the control's color setting, as specified in the application's
    * color scheme. This method does not change the application's color scheme.
    * It changes the color mapping used in this control only. 
    * 
    * @param aLogicalColor The logical color. Indicates which part of a control 
    *                      the physical color maps to. The set of logical 
    *                      colors for a standard application are defined in 
    *                      <code>TLogicalColor</code>
    * @param aColor The new physical color to which the logical color should 
    *               be mapped
    * @remarks
    * @see <code>GetColor()</code>
    */
    IMPORT_C void OverrideColorL(TInt aLogicalColor,TRgb aColor); // not available before Release 005

    /**
    * Gets the overridden physical color. This is the color that has been 
    * mapped to the logical color specified by a call to 
    * <code>OverrideColorL()</code>. If the logical color specified has not 
    * been overridden, the <code>aColor</code> value is not changed. 
    *
    * @param aLogicalColor The logical color for which the corresponding 
    *                      physical color will be retrieved. The set of 
    *                      logical colors for a standard GUI application are 
    *                      defined in <code>TLogicalColor</code>
    * @param aColor On return, contains the physical color that has been 
    *               mapped to <code>aLogicalColour</code> by a call to 
    *               <code>OverrideColorL()</code>
    * @return <code>ETrue</code> if <code>aLogicalColour</code> has been 
    *         overridden; <code>EFalse</code> otherwise
    * @remarks
    * @see
    */
    IMPORT_C TBool GetColor(TInt aLogicalColor,TRgb& aColor) const; // not available before Release 005

public: // but not exported
    /** @internal */
    void ProcessPointerEventL(const TPointerEvent& aPointerEvent);
    /** @internal */
    void ProcessPointerBufferReadyL();
    /** @internal */
    void RecursivelyMergeInputCapabilities(TCoeInputCapabilities& aInputCapabilities) const;
    /** @internal */
    void WriteInternalStateNowL(RWriteStream& aWriteStream) const;
protected:
    IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    IMPORT_C virtual void HandlePointerBufferReadyL();
    IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
    IMPORT_C virtual void SizeChanged();
    IMPORT_C virtual void PositionChanged();
public:
    /**
    * Gets the number of controls contained in a compound control. This 
    * method should be implemented by all compound controls. The default 
    * implementation returns zero. 
    *
    * @return The number of component controls contained by this control
    * @remarks
    * @see
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * Gets an indexed component of a compound control. This method should be 
    * implemented by all compound controls. <b>Note</b>: Within a compound 
    * control, each component control is identified by an index, where the 
    * index depends on the order the controls were added. The first is given 
    * an index of <code>0</code>, the next an index of <code>1</code>, and so 
    * on.
    *
    * @param aIndex The index of the control
    * @return The component control with an index of <code>aIndex</code>
    * @remarks Panics with CONE 12 if the default implementation of this 
    *          method was called
    * @see
    */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
protected:
    IMPORT_C void EnableDragEvents();
    IMPORT_C void HandleRedrawEvent(const TRect& aRect) const;
    IMPORT_C RWindow& Window() const;
    IMPORT_C RBackedUpWindow& BackedUpWindow() const;
    IMPORT_C void CloseWindow();
    IMPORT_C void CreateWindowL();
    IMPORT_C void CreateWindowL(const CCoeControl* aParent);
    IMPORT_C void CreateWindowL(RWindowTreeNode& aParent);
    IMPORT_C void CreateWindowL(RWindowGroup* aParent);
    IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent); // not available before Release 005
    IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent,TDisplayMode aDisplayMode);
    IMPORT_C void SetAllowStrayPointers();
    IMPORT_C void SetCanDrawOutsideRect();
    IMPORT_C void SetBlank();
    IMPORT_C void ReportEventL(MCoeControlObserver::TCoeEvent aEvent);
    IMPORT_C void SetCornerAndSize(TGulAlignment aCorner,const TSize& aSize);
    IMPORT_C void SetSizeWithoutNotification(const TSize& aSize);
    IMPORT_C CWindowGc& SystemGc() const;
    IMPORT_C void ActivateGc() const;
    IMPORT_C void ResetGc() const;
    IMPORT_C void DeactivateGc() const;
    IMPORT_C TBool IsReadyToDraw() const;
    IMPORT_C TBool IsActivated() const;
    IMPORT_C TBool IsBlank() const;
    IMPORT_C TBool IsBeingDestroyed() const;
    IMPORT_C CCoeControl* GrabbingComponent() const;
    IMPORT_C TBool CapturesPointer() const;
    IMPORT_C void HandleComponentControlsResourceChange(TInt aType); // not available before Release 005u



private:
    friend class CCoeRedrawer;
    IMPORT_C virtual void Draw(const TRect& aRect) const;
    void DrawComponents(const TRect& aRect) const;
    void DrawWindowOwningComponentsNow() const;
    void SetGrabbed(TBool aGrabbed);
    TBool IsGrabbed() const;
    void DoMakeVisible(TBool aVisible);
    void CheckPointerEventPurge() const;
    inline TInt Flags() const;
    inline TInt& Flags();
protected: // was Reserved_1(). Must be left here to maintain BC
    IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
// reserved virtual function space
    IMPORT_C virtual void Reserved_2();
protected:
    CCoeEnv* iCoeEnv;
    MCoeControlContext* iContext;
    TPoint iPosition;
    TSize iSize;
private:
    RDrawableWindow* iWin;
    MCoeControlObserver* iObserver;
    RCoeExtensionStorage iExt;
    };


inline CCoeEnv* CCoeControl::ControlEnv() const
/** Gets the control environment object for this control.

@return The control's control environment object. */
    {return(iCoeEnv);}

#endif
