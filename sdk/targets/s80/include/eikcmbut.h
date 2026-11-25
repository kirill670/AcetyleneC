/*
* ==============================================================================
*  Name        : eikcmbut.h
*  Part of     : CKon
*  Interface   : Button API
*  Description : Button Classes
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


#ifndef EIKCMBUT_H
#define EIKCMBUT_H

// INCLUDES
#include <eikbutb.h>
#include <coeccntx.h>
#include <gulutil.h>

// FORWARD DECLARATIONS
class CEikLabel;
class CEikImage;
class CEikAlignedControl;
class TResourceReader;
class CEikCommandStack;

/**
 *
 * The <code>CEikCommandButtonBase</code> class is the base class for 
 * Command Buttons.
 * A Command Button is used to invoke a command in an application.
 * It may display a text label, an image, or both. A Command Button consists of
 * two components. Each component can hold either a label or image. The
 * components can be displayed either on their own or at the same time.
 *
 * @lib eikcoctl.lib
 * @since 6.0
*/
class CEikCommandButtonBase : public CEikButtonBase, public MCoeControlContext
    {
    public:
    /**
     * The enumeration <code>TWhichComponent</code> identifies the components 
     * of the Command Button.
     */
    enum TWhichComponent
        {
        /** the first component */
        EFirst,
        /** the second component */
        ESecond
        };

    /**
     * The enumeration <code>TDisplayContent</code> specifies whether text, 
     * image or both are displayed on the Command Button.
     * This enumeration is redefined with more intuitive names in 
     * <code>CCknButtonBase</code>, <code>CEikCommandButton</code>, 
     * and <code>CEikTwoPictureCommendButton</code>.
     */
    enum TDisplayContent
        {
        /** only the Command Button's text is displayed */
        EFirstOnly  =0x0100,
        /** only the Command Button's image is displayed */
        ESecondOnly =0x0200,
        /** the Command Button's text and image are displayed */
        EBoth       =0x0300
        };

    /**
     * The enumeration <code>TLayout</code> specifies the positions of
     * text and image on the Command Button.
     * Except for <code>EDenseFont</code>, this enumeration is redefined 
     * with more intuitive names in <code>CCknButtonBase</code>, 
     * <code>CEikCommandButton</code>, and 
     * <code>CEikTwoPictureCommendButton</code>.
     */
    enum TLayout
        {
        /** components are positioned horizontally with the first component to the right of the second */
        EFirstRightSecondLeft=0x0000,
        /** components are positioned vertically with the first component below the second */
        EFirstBottomSecondTop=0x0001,
        /** components are positioned vertically with the first component above the second */
        EFirstTopSecondBottom=0x0002,
        /** components are positioned horizontally with the first component to the left of the second */
        EFirstLeftSecondRight=0x0003,
        /** defines that the text for the Command Button is dense (small) */
        EDenseFont           =0x0008
        };

    /**
     * The enumeration <code>TCenterAlignment</code> specifies the centering of
     * text or image in the Command Button.
     * This enumeration can be used in conjunction with the 
     * <code>ETextRightPictureLeft</code> and <code>ETextLeftPictureRight</code> 
     * flags defined in <code>CCknButtonBase::TLayout</code>, 
     * <code>CEikCommandButtonBase::TLayout</code>, 
     * and <code>CEikTwoPictureCommendButton::TLayout</code>.
     */
    enum TCenterAlignment
        {
        /** the first Command Button is always center-aligned regardless of its order in the layout */
        EFirstButtonCenter  =0x1000,
        /** the second Command Button is always center-aligned regardless of its order in the layout */
        ESecondButtonCenter =0x2000
        };

    /**
     * The enumeration <code>TExcess</code> specifies the possible ways
     * of allocating excess horizontal space 
     * between the two component controls of the Command Button.
     */
    enum TExcess
        {
        /** excess space is shared equally between the Command Button's components */
        EShare      =0x0000,
        /** excess space is allocated to the Command Button's first component */
        EToFirst    =0x0010,
        /** excess space is allocated to the Command Button's second component */
        EToSecond   =0x0020
        };
        
    public: // new functions

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikCommandButtonBase();

        /**
        * Sets the positions of the text and image in relation to each 
        * other on a Command Button.
        * 
        * @param aLayout The relative positions of text and image
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonLayout(TLayout aLayout);

        /**
        * Sets how excess horizontal space is shared between the two component
        * controls of the Command Button.
        * 
        * @param aExcess Determines whether excess horizontal space is shared 
        *                equally, allocated to the text only, or allocated to 
        *                the image only
        * @remarks This method can be used when the space shared between the 
        *          Command Button's label and image (its two components) need to be 
        *          modified. The default is that both components share the 
        *          space equally
        * @see
        */
        IMPORT_C void SetExcessSpace(TExcess aExcess);

        /**
        * Specifies whether the first, second, or both components are displayed 
        * on the Command Button.
        * 
        * @param aContent The required content
        * @remarks
        * @see
        */
        IMPORT_C void SetDisplayContent(TDisplayContent aContent);

        /**
        * Specifies if the first or second components are centered on the 
        * Command Button.
        * 
        * @param aAlignment The required alignment
        * @remarks
        * @see
        */
        IMPORT_C void SetCenterAlignment(TCenterAlignment aAlignment);

        /**
        * Responds to size and position changes to the contents of the Command 
        * Button.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void LayoutComponents();

        /**
        * Begins construction of the Command Button, setting default behavior
        * and layout. This method can be followed
        * by <code>ConstructImageFromResourceL()</code> and 
        * <code>ConstructLabelFromResourceL()</code> to set up a Command 
        * Button with an image and a label.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks
        * @see
        */
        IMPORT_C void StartConstructFromResourceL(TResourceReader& aReader);

        /**
        * Constructs a label from resource for the specified Command Button 
        * component.
        * 
        * @param aReader The resource reader to get the resource from
        * @param aWhich The component for which the label will be constructed
        * @remarks
        * @see
        */
        IMPORT_C void ConstructLabelFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);

        /**
        * Constructs an image from resource for the specified Command Button
        * component.
        * 
        * @param aReader The resource reader to get the resource from
        * @param aWhich The component for which the image is constructed
        * @remarks
        * @see
        */
        IMPORT_C void ConstructImageFromResourceL(TResourceReader& aReader,TWhichComponent aWhich);

        /**
        * Updates the alignment of Command Button text and image components
        * according to layout flags.
        * 
        * @remarks
        * @see
        */
        IMPORT_C virtual void UpdateComponentAlignment();

        /**
        * Sets the Command Button to be the default.
        * 
        * @param aIsDefault <code>ETrue</code> to be default; 
        *                   <code>EFalse</code> otherwise
        * @remarks In Series 80, the Command Button is underlined. Its shortcut
		* key is mapped to the Enter key. In Series 90, the default is 
		* highlighted, but there is no shortcut mapping
        * @see
        */
        IMPORT_C void SetDefault(TBool aIsDefault);

        /**
        * Returns whether the Command Button is the default one.
        * 
        * @return <code>ETrue</code> if the specified Command Button is the 
        *         default; <code>EFalse</code> otherwise
        * @remarks
        * @see 
        */
        IMPORT_C TBool IsDefault() const;

    public: // from CCoeControl

        /**
        * Dims or undims the Command Button. Typically, this method is used to
        * show that the action performed by the Command Button is temporarily 
        * unavailable.
        * 
        * @param aDimmed <code>ETrue</code> to dim the Command Button; 
        *                <code>EFalse</code> to set the Command Button as not 
        *                dimmed
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetDimmed(TBool aDimmed);

        /**
        * Gets the minimum amount of space required to display the Command 
        * Button.
        * 
        * @return the minimum size required by the Command Button
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Gets the number of controls contained in a compound control.
        *
        * @return the number of component controls contained by this control
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * Gets the specified component of a compound control. 
        *
        * @param aIndex The index of the control to get
        * @return the component control with an index of <code>aIndex</code>
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * Activates this Command Button.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ActivateL();

        /**
        * Sets the container window for a Command Button. 
        * 
        * @param aContainer The compound control that is to be the container
        *                   for the Command Button
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);

        /**
        * Responds to a change in focus. Whether the Command Button is redrawn depends 
        * on <code>aDrawNow</code>. This method is called whenever a Command 
        * Button gains or loses focus.
        * 
        * @param aDrawNow If <code>EDrawNow</code>, the Command Button is redrawn
        *                 immediately; if <code>ENoDrawNow</code>, the Command Button 
        *                 is not redrawn
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Handles key events.
        * 
        * @param aKeyEvent The key event
        * @param aType This parameter is not used
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code>
        *         otherwise 
        * @remarks The second parameter is not used
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode /*aType*/);

        // not available before Release 005u
        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A TInt message UID value for the resource that has changed.
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

    public: // but not exported

        /**
        * Returns the command stack.
        * @internal
        * @since Series90 1.0
        * @return the command stack
        * <BR><B>Type of return value:</B> CEikCommandStack*
        * <BR><B>Contents of return value:</B> The command stack
        */
        CEikCommandStack* CommandStack() const;

        /**
        * Returns the Button flags (Bit field contained in a TInt)
        * @since Series90 1.0
        * @return the Button flags
        * @internal
        * <BR><B>Type of return value:</B> TInt
        * <BR><B>Contents of return value:</B> The Button flags
        */
        TInt ButFlags() const;

    protected: // from CEikButtonBase

        /**
        * Notifies the Button that its draw state has changed.
        *
        */
        IMPORT_C void StateChanged();
    protected:

        /**
        * default constructor.
        */
        IMPORT_C CEikCommandButtonBase();

        /**
        * Sets the text that will appear on the Command Button
        * @param aText The text to appear on the Command Button.
        * @param aComponent The component for which the text is set.
        *
        */
        IMPORT_C void SetTextL(const TDesC& aText,CEikAlignedControl*& aComponent);

        /**
        * Sets the image to be displayed in the Command Button, and an optional bitmask
        * for the image.
        * @param aMain The bitmap to appear on the Command Button.
        * @param aMask Specifies the bitmap mask to use with the bitmap aMain.
        *        This must be 1 if you wish to use a null mask.
        * @param aComponent - The component for which the image is set.
        *
        */
        IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask,CEikAlignedControl*& aComponent);

        /**
        * Loads bitmap images from a specified file and associates the images
        * with the Command Button.
        * A bitmap mask may optionally be set using aMask. If the image cannot
        * be read from the file, the Command Button is not updated.
        * @param aFilename The filename from which to read the bitmap.
        * @param aMain The index of the bitmap in the file.
        * @param aMask The index of the bitmap mask in the file. If specified, this is used to create the bitmap mask for the image.
        * @param aComponent The component for which the image is set.
        */
        IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask,CEikAlignedControl*& aComponent);

        /**
        * Checks whether the command stack exists. If it does not exist one is created.
        *
        */
        inline void CheckCreateCommandStackL();

    protected: // from CCoeControl

        /**
        * See CCoeControl
        */
        IMPORT_C void Draw(const TRect& aRect) const;
    protected:

        void SetImageAttributes(CEikImage* aImage);

        inline TInt Behavior() const;

    protected:

        /**
        * Does nothing in Release version. Debug version writes the internal state to the specified stream.
        * @param aWriteStream Stream information is written to.
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private:
        IMPORT_C void SizeChanged();
        IMPORT_C void Reserved_2();
    private: // from CEikButtonBase
        IMPORT_C void Reserved_3();
    private: // from MCoeControlContext
        IMPORT_C void PrepareContext(CWindowGc& aGc) const;
    private:
        IMPORT_C virtual void Reserved_4();
    private:
        void SetComponentExtents(const TRect& aRect);
        void SetNewComponentExtentL();
        TBool LayoutIsVertical() const;
    protected:
        TMargins8 iMargins;
    CEikAlignedControl* iComponents[2];
        TInt iCmdFlags;
    private:
        TInt iDrawOffset;
        CEikCommandStack* iCommandStack;
        TInt iDummy;
        TBool iDefault;
    };

/**
 *
 * The <code>CEikCommandButton</code> class provides a Command Button. 
 * A Command Button may contain text, an image or both.
 * A Command Button can be used to invoke a command in an application.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikCommandButton : public CEikCommandButtonBase
    {
    public:
    /**
     * The enumeration <code>TLayout</code> specifies the positions of text 
     * and image on the Command Button. This enumeration shadows the values 
     * defined in <code>CEikCommandButtonBase::TLayout</code> to provide more 
     * intuitive names.
     */
    enum TLayout
        {
        /** text and image are positioned horizontally with the text to the right of the image */
        ETextRightPictureLeft=0x000,
        /** text and image are positioned vertically with the text below the image */
        ETextBottomPictureTop=0x001,
        /** text and image are positioned vertically with the text above the image */
        ETextTopPictureBottom=0x002,
        /** text and image are positioned horizontally with the text to the left of the image */
        ETextLeftPictureRight=0x003
        };

    /**
     * The enumeration <code>TCenterAlignment</code> specifies the centering 
     * of text or image in the Command Button. This enumeration can be used in 
     * conjunction with the <code>ETextRightPictureLeft</code> and 
     * <code>ETextLeftPictureRight</code> flags defined in 
     * <code>CCknButtonBase::TLayout</code>, 
     * <code>CEikCommandButton::TLayout</code>, 
     * and <code>CEikTwoPictureCommendButton::TLayout</code>.
     * See also <code>SetCenterAlignment(TExcess)</code>.
     */
    enum TCenterAlignment
        {
        /** the text is always center-aligned regardless of its order in the layout */
        ETextCentered   =0x1000,
        /** the image is always center-aligned regardless of its order in the layout */
        EPictureCentered=0x2000
        };

    /**
     * The enumeration <code>TExcess</code> specifies the possible ways of 
     * allocating excess horizontal space between the text and images of the 
     * Command Button. See also <code>SetExcessSpace(TExcess)</code>.
     */
    enum TExcess
        {
        /** excess space is shared equally between the Command Button's text and images */
        EShare      =0x0000,
        /** excess space is allocated to the text of the Command Button */
        EToText     =0x0010,
        /** excess space is allocated to the Command Button's images */
        EToPicture  =0x0020
        };

    /**
     * The enumeration <code>TDisplayContent</code> specifies whether text, 
     * image, or both are displayed on the Command Button.
     * This enumeration shadows the values defined in
     * <code>CEikCommandButtonBase::TDisplayContent</code> to provide more
     * intuitive names.
     */
    enum TDisplayContent
        {
        /** only the Command Button's text is displayed */
        ETextOnly       =0x0100,
        /** only the Command Button's image is displayed */
        EPictureOnly    =0x0200,
        /** the Command Button's text and image are displayed */
        ETextAndPicture =0x0300
        };

    public:

        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C CEikCommandButton();

        /**
        * The object destructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C ~CEikCommandButton();

        /**
        * Set the text for the Command Button.
        * 
        * @param aText The text to use
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

        /**
        * Sets the image to be displayed in the Command Button, 
        * and an optional bitmask for the image.
        *
        * @param aMain The bitmap to appear on the Command Button
        * @param aMask Specifies the bitmap mask to use with the bitmap 
        *              <code>aMain</code>. To use a <code>NULL</code> mask,
        *              This parameter can be omitted
        * @remarks If the mask is not used, only the specified bitmap is displayed
        * @see
        */
        IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL);

        /**
        * Loads a bitmap image from a specified file and associates it with 
        * the Command Button. A bitmap mask may be set using 
        * <code>aMask</code> (optional). If the image cannot be read from the file, the 
        * Command Button is not updated.
        * 
        * @param aFilename The filename from which to read the bitmap
        * @param aMain The index of the bitmap in the file
        * @param aMask The index of the bitmap mask in the file. 
        *              If specified, this is used to create the bitmap mask for 
        *              the image
        * @remarks
        * @see
        */
        IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);

        /**
        * Gets the text label for the Command Button.
        * 
        * @return the text label for the Command Button
        * @remarks
        * @see
        */
        IMPORT_C CEikLabel* Label() const;

        /**
        * Gets the image for the Command Button.
        * 
        * @return the image for the Command Button
        * @remarks
        * @see
        */
        IMPORT_C CEikImage* Picture() const;

        /**
        * Sets the relative positions of the text and image on a Command Button.
        * 
        * @param aLayout The relative positions of text and image
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonLayout(TLayout aLayout);

        /**
        * Sets how excess horizontal space is allocated between the text and
        * image of the Command Button.
        * 
        * @param aExcess Determines whether excess horizontal space is shared 
        *                equally, allocated to the text only or allocated to the 
        *                image only
        * @remarks
        * @see
        */
        IMPORT_C void SetExcessSpace(TExcess aExcess);

        /**
        * Specifies whether text, image or both are displayed on the Command 
        * Button.
        * 
        * @param aContent The required content
        * @remarks
        * @see
        */
        IMPORT_C void SetDisplayContent(TDisplayContent aContent);

        /**
        * Specifies whether the first and/or second components are centered on
        * the Command Button.
        *
        * @param aAlignment The required alignment
        * @remarks
        * @see
        */
        IMPORT_C void SetCenterAlignment(TCenterAlignment aAlignment);

        /**
        * Sets the text, bitmap, and bitmap mask for the Command Button.
        * 
        * @param aCommandId Not used
        * @param aText The text on the Command Button
        * @param aBitmap The bitmap for the Command Button
        * @param aMask The bitmap mask for the Command Button
        * @remarks This method is used only to assign a label and bitmaps to 
        *          the Command Button
        * @see
        */
        IMPORT_C void SetCommandL(TInt aCommandId,const TDesC* aText,
                                  const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

        /**
        * Adds the command ID, text, and/or bitmap to the top of the command stack.
        * These values can subsequently be restored from the command stack by a 
        * call to <code>PopCommandFromStack()</code>.
        * Each Command Button can store a stack of IDs, text items, and bitmaps
        * on a command stack. This allows an application to use different
        * Command Buttons according to the currently visible view.
        * 
        * @param aCommandId The command ID for the Command Button
        * @param aText The text on the Command Button
        * @param aBitmap The Command Button's bitmap
        * @param aMask The Command Button's bitmap mask
        * @remarks This method can be used when commands are allocated to the
        *          CBA. For example, when an application starts execution, 
        *          command 'New' is assigned to a CBA Button. When a new 
        *          document is created, command 'New' is added onto the 
        *          command stack and the same CBA is now assigned the command 
        *          'Save' 
        * @see
        */
        IMPORT_C void AddCommandToStackL(TInt aCommandId,const TDesC* aText,
                                         const CFbsBitmap* aBitmap,
                                         const CFbsBitmap* aMask);

        /**
        * Removes the Command Button with the command ID specified from 
        * the command stack.
        * 
        * @param aCommandId The command ID of the Command Button to remove
        * @return <code>ETrue</code> if a command with the command ID specified
        *         was found and removed; <code>EFalse</code> otherwise
        * @remarks The Command Button is discarded
        * @see
        */
        IMPORT_C TBool RemoveCommandFromStack(TInt aCommandId);

        /**
        * Pops the uppermost Command Button from the command stack.
        * This restores the current Command Button's command ID, text and 
        * bitmap to the values they had before the last call to 
        * <code>AddCommandToStackL()</code>.
        * 
        * @return the new command ID for the Command Button
        * @remarks This method is used to replace an existing CBA Button
        *          with a previous Command Button added to the stack.
        *          For example, when a newly created document 
        *          is saved and closed using the CBA Command Button 'Save'. 
        *          The command 'Save' is removed and replaced by 'New', 
        *          which is popped from the command stack
        * @see
        */
        IMPORT_C TInt PopCommandFromStack();

    public: // from CCoeControl

        /**
        * Used to construct a Command Button from a resource file.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks The resource type is <code>CMBUT</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    public: // from CEikCommandButtonBase

        /**
        * Updates the alignment of Command Button text and image components
        * according to layout flags.
        *
        * @remarks This method can be called when the position of the Command Button
        *          changes
        * @see
        */
        IMPORT_C void UpdateComponentAlignment();
    private:
        void UpdateLabelReserveLengthL(const TDesC* aText);
    private:
        TInt iDummy;
    };

/**
 *
 * The <code>CEikTwoPictureCommandButton</code> class provides a Command Button 
 * that can hold two pictures in addition to label text. If a second picture is 
 * set for the Command Button it is shown when the Command Button is tapped.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikTwoPictureCommandButton : public CEikCommandButtonBase
    {
    public:
    /**
     * The enumeration <code>TLayout</code> specifies the positions of text 
     * and image on the Command Button.
     */
    enum TLayout
        {
        /** text and image are positioned horizontally with the text to the right of the image */
        ETextRightPictureLeft=0x000,
        /** text and image are positioned vertically with the text below the image */
        ETextBottomPictureTop=0x001,
        /** text and image are positioned vertically with the text above the image */
        ETextTopPictureBottom=0x002,
        /** text and image are positioned horizontally with the text to the left of the image */
        ETextLeftPictureRight=0x003
        };

    /**
     * The enumeration <code>TExcess</code> enumerates the possible ways of 
     * allocating excess horizontal space between the text and images of the 
     * Command Button.
     */
    enum TExcess
        {
        /** excess space is shared equally between the Command Button's text and images */
        EShare      =0x0000,
        /** excess space is allocated to the text of the Command Button */
        EToText     =0x0010,
        /** excess space is allocated to the Command Button's images */
        EToPicture  =0x0020
        };

    /**
     * The enumeration <code>TDisplayContent</code> specifies whether text, 
     * image or both are displayed on the Command Button.
     */
    enum TDisplayContent
        {
        /** only the Command Button's text is displayed */
        ETextOnly       =0x0100,
        /** only the Command Button's image is displayed */
        EPictureOnly    =0x0200,
        /** the Command Button's text and image are displayed */
        ETextAndPicture =0x0300
        };
    private:
    enum TPictureButtonType
        {
        EPictureButWithBorders      =0x0000,
        EPictureButWithoutBorders   =0x1000
        };
    enum TExternalPicture
        {
        EPictureNotOwnedExternally  =0x00,
        EPictureOwnedExternally     =0x01
        };
    public:

        /**
        * The default object constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C CEikTwoPictureCommandButton();

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikTwoPictureCommandButton();

        /**
        * Determines whether the bitmaps for the second Command Button's
        * image are owned externally.
        * 
        * @return <code>ETrue</code> if the bitmaps for the second 
        *         Command Button's image are owned externally;
        *         <code>EFalse</code> otherwise
        * @remarks Can be used when the bitmaps are required to change. If the 
        *          Command Button owns the bitmaps, they can be deleted and reallocated, 
        *          otherwise such actions cannot be done
        * @see
        */
        IMPORT_C TBool IsSecondPictureOwnedExternally();

        /**
        * Gets the image control component for the Command Button.
        * 
        * @return the image control component for the Command Button
        * @remarks
        * @see
        */
        IMPORT_C CEikImage* Picture() const;

        /**
        * Constructs the Command Button's images from resource.
        *
        * @since Series90 1.0
        * @param aReader The resource reader to use
        * @param aWhich Not used
        * @remarks
        * @see
        */
        IMPORT_C void ConstructImagesFromResourceL(TResourceReader& aReader,
                                                   TWhichComponent aWhich);

        /**
        * Sets the text for the Command Button.
        * 
        * @param aText The text to use for the Command Button's label
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

        /**
        * Sets both images for the Command Button. The first image is created 
        * from the image bitmap <code>aMain</code> and the mask bitmap 
        * <code>aMask</code>. The second image is created from the image bitmap 
        * <code>aSecondMain</code> and mask bitmap <code>aSecondMask</code>.
        * 
        * @param aMain The image bitmap for the first image
        * @param aMask The mask bitmap for the first image
        * @param aSecondMain The second image bitmap for the image
        * @param aSecondMask The second mask bitmap for the second image
        * @remarks This is an alternative method to loading in from resource
        * @see
        */
        IMPORT_C void SetTwoPicturesL(const CFbsBitmap* aMain,
                                      const CFbsBitmap* aMask=NULL,
                                      const CFbsBitmap* aSecondMain=NULL,
                                      const CFbsBitmap* aSecondMask=NULL);

        /**
        * Sets the second image.
        * 
        * @param aSecondMain The image bitmap for the second image
        * @param aSecondMask The mask bitmap for the second image
        * @remarks
        * @see
        */
        IMPORT_C void SetSecondPicture(const CFbsBitmap* aSecondMain,
                                       const CFbsBitmap* aSecondMask=NULL);

        /**
        * Loads bitmap images from a specified file and associates the
        * images with the Command Button. Loads the
        * image bitmap identified by <code>aMain</code> and the mask bitmap 
        * identified by <code>aMask</code> from the bitmap file named 
        * <code>aFilename</code>.
        * 
        * @param aFilename The bitmap file
        * @param aMain The image bitmap
        * @param aMask The mask bitmap
        * @remarks Loading bitmaps may result in a noticeable delay
        * @see
        */
        IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,
                                          TInt aMain,TInt aMask=-1);

        /**
        * Sets the Command Button’s second picture from file. Loads the image bitmap 
        * identified by <code>aMain</code> and the mask bitmap identified by 
        * <code>aMask</code> from the bitmap file named <code>aFilename</code>.
        *
        * @since Series90 1.0
        * @param aFilename The bitmap file
        * @param aMain The image bitmap
        * @param aMask The mask bitmap
        * @remarks
        * @see
        */
        IMPORT_C void SetSecondPictureFromFileL(const TDesC& aFilename,
                                                TInt aMain,TInt aMask=-1);

        /**
        * Sets ownership of the bitmaps used for the Command Button's second picture.
        *
        * @since Series90 1.0
        * @param aOwnership If <code>ETrue</code>, sets the bitmaps as owned 
        *                   externally; if <code>EFalse</code>, sets the bitmaps 
        *                   as not owned externally
        * @remarks
        * @see
        */
        IMPORT_C void SetSecondPictureOwnedExternally(TBool aOwnership);
    public: // from CCoeControl

        /**
        * Used to construct a Command Button from a resource file.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks The resource type is <code>PICMBUT</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Used to activate this Command Button.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ActivateL();
    protected: // from CCoeControl

        /**
        * Does nothing in Release version. Debug version writes the
        * internal state to the specified stream.
        * @param aWriteStream Stream information is written too.
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private: // from CCoeControl
    IMPORT_C void Draw(const TRect& /*aRect*/) const;
        IMPORT_C void StateChanged();
    private: // from MCoeControlContext
        IMPORT_C void PrepareContext(CWindowGc& aGc) const;
    private:
        void SwapPictures(CEikImage* aImage);
    private:
        const CFbsBitmap* iSecondBitmap;
        const CFbsBitmap* iSecondMaskBitmap;
        TInt iPictureFlags;
        TInt iDummy;
    };

/**
 * The <code>CEikInverterCommandButton</code> class is a Command Button that 
 * swaps the foreground and background colors used to draw the contents of 
 * the Command Button when it is tapped.
 *
 * @lib eikcoctl.lib
 * @since ER5U
 */
class CEikInverterCommandButton : public CEikCommandButton
    {
    public:

        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C CEikInverterCommandButton();

        /**
        * The object destructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C ~CEikInverterCommandButton();
    protected:

        /**
        * Writes the internal state to the specified stream.
        * @param aWriteStream Stream information is written to.
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private: // from MCoeControlContext
        IMPORT_C void PrepareContext(CWindowGc& aGc) const;
    private:
        TInt iFlag;
        TInt iDummy;
    };

//
// CEikTextButton
//

/**
 * This class provides member methods to create a Command Button with a text 
 * label. This text Command Button has no image associated with it. It displays 
 * a text label only.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikTextButton : public CEikCommandButtonBase
    {
    public:

        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C CEikTextButton();

        /**
        * The object destructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C ~CEikTextButton();

        /**
        * Sets the label for the specified Command Button component.
        * 
        * @param aText The label for the specified component
        * @param aWhich The component for which the text label is set
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText,TWhichComponent aWhich=EFirst);

        /**
        * Gets the label associated with the specified Command Button component.
        * 
        * @param aWhich The component for which the text label is retrieved
        * @return the text label associated with the specified component
        * @remarks
        * @see
        */
        IMPORT_C CEikLabel* Label(TWhichComponent aWhich=EFirst) const;
    public: // from CCoeControl

        /**
        * Used to construct a Command Button from a resource file.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks The resource type is <code>TXTBUT</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    private:
        TInt iDummy;
    };

/**
 *
 * The <code>CEikBitmapButton</code> class provides member methods to create a
 * Command Button with a bitmap image. This bitmap Command Button has no text 
 * associated with it; it displays an image only.
 *
 * @since 6.0
 * @lib eikcoctl.lib
 */
class CEikBitmapButton : public CEikCommandButtonBase
    {
    public:

        /**
        * The default object constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C CEikBitmapButton();

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikBitmapButton();

        /**
        * Sets the image to be displayed in the Command Button and an 
        * optional bitmap mask for the image.
        *
        * @param aMain The bitmap to appear on the Command Button
        * @param aMask Specifies the bitmap mask to use with the bitmap <code>aMain</code>.
        *        The default is none
        * @param aWhich The component for which the image is set
        * @remarks
        * @see
        */
        IMPORT_C void SetPictureL(const CFbsBitmap* aMain,
                                  const CFbsBitmap* aMask=NULL,
                                  TWhichComponent aWhich=EFirst);

        /**
        * Sets the Command Button's image to a bitmap stored in a file.
        * A bitmap mask can be set using <code>aMask</code>. 
        * If the image cannot be read from the file, 
        * the Command Button is not updated.
        *
        * @param aFilename The filename from which to read the bitmap
        * @param aMain The index of the bitmap in the file
        * @param aMask The index of the bitmap mask in the file. If specified, 
        *              this is used to create the bitmap mask for the image
        * @param aWhich The component for which the image is set
        * @remarks
        * @see
        */
        IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,
                                          TInt aMask=-1,TWhichComponent aWhich=EFirst);

        /**
        * Gets the image associated with the specified component.
        * 
        * @param aWhich The component for which the image is retrieved
        * @return the image associated with the specified component
        * @remarks
        * @see
        */
        IMPORT_C CEikImage* Picture(TWhichComponent aWhich=EFirst) const;

    public: // from CCoeControl

        /**
        * Used to construct a Command Button from a resource file.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks The resource type is <code>BMPBUT</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    private:
        TInt iDummy;
    };


#endif  // EIKCMBUT_H

// End of File
