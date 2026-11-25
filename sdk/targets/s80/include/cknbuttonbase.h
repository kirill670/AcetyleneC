/*
* ==============================================================================
*  Name        : cknbuttonbase.h
*  Part of     : CKon
*  Interface   : Button API
*  Description : CCKnButtonBase Class
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


#ifndef CKNBUTTONBASE_H
#define CKNBUTTONBASE_H

// INCLUDES
#include <eikbutb.h>
#include <coeccntx.h>
#include <gulutil.h>
#include <CknLogicalFont.h>
#include <eiklabel.h>

// FORWARD DECLARATIONS
class CCknCommandStack;
class CEikImage;
class CEikAlignedControl;
class TResourceReader;


/**
*  The <code>CCknButtonBase</code> class provides the 
*  <code>CCknButtonBase</code> class.
*
*  @lib cknctl.lib
*  @since Series 90 1.0
*/
class CCknButtonBase : public CEikButtonBase, public MCoeControlContext
    {
    public:
        /**
         * The enumeration <code>TCknButtonBaseWhichComponent</code> 
         * identifies the components of the Button.
         */
        enum TCknButtonBaseWhichComponent
            {
            /** the first component (the text) */
            EText,
            /** the second component (the image) */
            EPicture
            };

        /**
         * The enumeration <code>TLayout</code> specifies the order and the 
         * layout of the text and the image on the Button.
         */
        enum TLayout
            {
            /** text and image are positioned horizontally with the text to the right of the image */
            ETextRightPictureLeft=0x0000,
            /** text and image are positioned vertically with the text below the image */
            ETextBottomPictureTop=0x0001,
            /** text and image are positioned vertically with the text above the image */
            ETextTopPictureBottom=0x0002,
            /** text and image are positioned horizontally with the text to the left of the image */
            ETextLeftPictureRight=0x0003
            };

        /**
         * The enumeration <code>TExcess</code> specifies the possible ways 
         * of sharing excess horizontal space
         * between the Button's text and image.
         * See also <code>SetExcessSpace(TExcess)</code>.
         */
        enum TExcess
            {
            /** excess space is shared equally */
            EShare      =0x0000,
            /** excess space is allocated to the text only */
            EToText     =0x0010,
            /** excess space is allocated to the image only */
            EToPicture  =0x0020
            };

        /**
         * The enumeration <code>TDisplayContent</code> specifies whether text,
         * image or both are displayed on the Button.
         */
        enum TDisplayContent
            {
            /** display text only */
            ETextOnly       =0x0100,
            /** display image only */
            EPictureOnly    =0x0200,
            /** display text and image */
            ETextAndPicture =0x0300
            };

    public:

        /**
        * The object destructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C ~CCknButtonBase();

        /**
        * Responds to size and position changes to the contents of the Button.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void LayoutComponents();

        /**
        * Begins construction of the Button, setting default behavior and layout.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks
        * @see
        */
        IMPORT_C void StartConstructFromResourceL(TResourceReader& aReader);

        /**
        * Constructs a label from resource for the first Button component.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks
        * @see
        */
        IMPORT_C void ConstructLabelFromResourceL(TResourceReader& aReader);

        /**
        * Constructs an image from resource for the specified Button component.
        * 
        * @param aReader The resource reader to get the resource from
        * @remarks
        * @see
        */
        IMPORT_C void ConstructImageFromResourceL(TResourceReader& aReader);

        /**
        * Sets the Button to be the default.
        * 
        * @param aIsDefault <code>ETrue</code> to be default; <code>EFalse</code> 
        *                   otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetDefault(TBool aIsDefault);

        /**
        * Determines if the Button is set to be the default.
        * 
        * @return <code>ETrue</code> if the Button is default; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsDefault() const;

        /**
        * Updates the alignment of the text and image components of the Button.
        * 
        * @remarks The method is called by other methods such as 
        *          <code>ActivateL()</code>,
        *          <code>ResetDefaultAlignment</code>, and 
        *          <code>SetAlignment()</code>. The method can 
        *          be called when a control has changed position
        * @see
        */
        IMPORT_C void UpdateComponentAlignment();

        /**
        * Sets the text that appears on the Button.
        * 
        * @param aText The text to appear on the Button
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

        /**
        * Sets the bitmap image to be displayed in the Button and, optionally, a
        * bitmap mask for the image.
        * 
        * @param aMain Specifies the bitmap to appear on the Button
        * @param aMask Specifies the bitmap mask to use with the bitmap
        * @remarks If no bitmap mask is specified, only the image is displayed.
        *          Unless it is created externally, the method takes ownership 
        *          of the bitmap 
        * @see
        */
        IMPORT_C void SetPictureL(const CFbsBitmap* aMain,const CFbsBitmap* aMask=NULL);

        /**
        * Loads a bitmap image from a specified file. The bitmap is then 
        * associated with the Button. A bitmap mask may be set using 
        * <code>aMask</code> (optional). If the
        * image cannot be read from the file, the Button is not updated.
        * 
        * @param aFilename The filename from which to read the bitmap
        * @param aMain The index of the bitmap in the file
        * @param aMask The index of the bitmap mask in the file. If specified, this is used to
        * create the bitmap mask for the image
        * @remarks
        * @see
        */
        IMPORT_C void SetPictureFromFileL(const TDesC& aFilename,TInt aMain,TInt aMask=-1);

        /**
        * Sets the space between the text and the image.
        * 
        * @param aPixelGap The required gap, in pixels
        * @remarks
        * @see
        */
        IMPORT_C void SetInterComponentGap(TInt aPixelGap);

        /**
        * Gets the text label for the Button.
        * 
        * @return the Button's text label
        * @remarks
        * @see
        */
        IMPORT_C CEikLabel* Label() const;

        /**
        * Gets the image for the Button.
        * 
        * @return the Button's image
        * @remarks
        * @see
        */
        IMPORT_C CEikImage* Picture() const;

        /**
        * Sets the positions of the text and image in relation to each other 
        * on a Button.
        * 
        * @param aLayout The relative positions of text and image
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonLayout(TLayout aLayout);

        /**
        * Sets how excess horizontal space is shared between the text and the image of the Button.
        * 
        * @param aExcess Determines whether excess horizontal space is shared equally, allocated to the text only, or allocated to the image only
        * @remarks
        * @see
        */
        IMPORT_C void SetExcessSpace(TExcess aExcess);

        /**
        * Specifies whether text, image or both are displayed on the Button.
        *
        * @param aContent The required content
        * @remarks
        * @see
        */
        IMPORT_C void SetDisplayContent(TDisplayContent aContent);

        /**
        * Sets the text, bitmap, and bitmap mask for the Button.
        * 
        * @param aCommandId Not used
        * @param aText The text in the Button
        * @param aBitmap The Button's bitmap
        * @param aMask The Button's bitmap mask
        * @remarks
        * @see
        */
        IMPORT_C void SetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

        /**
        * Adds the Button's command ID and text and/or bitmap to the top of the 
        * command stack. These values can subsequently be restored from the 
        * command stack by a call to <code>PopCommandFromStack()</code>. Each 
        * Button can store a stack of IDs and text and/or bitmaps on a command 
        * stack. This allows an application to use different Buttons according to 
        * the currently visible view.
        * 
        * @param aCommandId The command ID for the Button
        * @param aText The text in the Button
        * @param aBitmap The Button's bitmap
        * @param aMask The Button's bitmap mask
        * @remarks
        * @see
        */
        IMPORT_C void AddCommandToStackL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);

        /**
        * Removes the Button with the specified command ID from the command stack.
        * 
        * @param aCommandId The command ID of the Button to remove
        * @return <code>ETrue</code> if a command with the specified command 
        *         ID was found and removed; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool RemoveCommandFromStack(TInt aCommandId);

        /**
        * Pops the uppermost Button from the command stack. This method restores 
        * the current Button's command ID, text and/or bitmap to the values they 
        * had before the last call to <code>AddCommandToStackL()</code>.
        * 
        * @return the new command ID for the Button
        * @remarks
        * @see
        */
        IMPORT_C TInt PopCommandFromStack();

        /**
        * Sets the specified component to use the default alignment. The default 
        * alignment for the text is left aligned. The default alignment for the 
        * image is left aligned if the image is shown before the text, and 
        * right aligned if the image follows the text.
        * 
        * @param aComponent The component to apply the default alignment to
        * @remarks
        * @see
        */
        IMPORT_C void ResetDefaultAlignment(TCknButtonBaseWhichComponent aComponent);

        /**
        * Sets the specified component to use the alignment passed in 
        * <code>aAlignment</code>.
        * 
        * @param aAlignment Contains the alignment information
        * @param aComponent The component to apply the alignment defined at 
        *                   <code>aAlignment</code> to
        * @remarks
        * @see
        */
        IMPORT_C void SetAlignment(TGulAlignmentValue aAlignment, TCknButtonBaseWhichComponent aComponent);
    
    public: // but not exported

        /** @internal */
        CCknCommandStack* CommandStack() const;
        /** @internal */
        TInt ButFlags() const;

    public: // from CCoeControl

        /**
        * Constructs a Button from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is defined in the enumeration 
        *          <code>TEikStockControls</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Dims or undims the Button. Typically, this method is used to show that 
        * the action performed by the Button is temporarily unavailable.
        * 
        * @param aDimmed <code>ETrue</code> to dim the Button; <code>EFalse</code>
        *                to set the Button as not dimmed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void SetDimmed(TBool aDimmed);

        /**
        * Gets the minimum amount of space required to display the Button.
        * 
        * @return the minimum size required by the Button
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Gets the number of controls contained in a compound control.
        *
        * @return the number of component controls contained by this control
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * Gets the specified component of a compound control. 
        *
        * @param aIndex The index of the control to get
        * @return the component control with an index of <code>aIndex</code>
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * Sets the Button as ready to be drawn.
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void ActivateL();

        /**
        * Sets a component control's container window if the container is a 
        * window-owning control. This method sets the control's associated 
        * window to be the same as the container's associated window. The 
        * method can only be called on non-window-owning controls
        *
        * @param aContainer The window owned by the container control
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);

        /**
        * Responds to changes of focus. This method is called when a control gains 
        * or loses focus as a result of a call to <code>SetFocus()</code>. A 
        * typical use of this method is to change the appearance 
        * of the control to indicate whether or not it has focus.
        *
        * @param aDrawNow Contains the value that was passed to it by 
        *                 <code>SetFocus()</code>
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Handles key events.
        * 
        * @param aKeyEvent The key event
        * @param aType The type of key event, either: <code>EEventKey</code>, 
        *              <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
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
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource that 
        *              has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u

    public: //deprecated - support for existing code that uses previous base class enums

        /**
        * This method is deprecated. Sets the relative positions of the text and image on a command Button.
        * 
        * @param aLayout Relative positions of text and image
        * @deprecated
        */
        IMPORT_C void SetButtonLayout(TInt aLayout);

        /**
        * This method is deprecated. Sets how excess horizontal space is shared between the two component controls of the command Button.
        * @param aExcess Determines whether excess horizontal space is shared equally, allocated to the text only or allocated to the image only.
        * @deprecated
        */
        IMPORT_C void SetExcessSpace(TInt aExcess);

        /**
        * This method is deprecated. Specify whether component 1, component 2 or both are displayed.
        * @param aContent The required content
        * @deprecated
        */
        IMPORT_C void SetDisplayContent(TInt aContent);

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CCknButtonBase();
    protected: // from CCoeControl

        /**
        * Responds to size changes to set the size and position of the contents of this control.
        */
        IMPORT_C void SizeChanged();
    protected: // from CEikButtonBase

        /**
        * Notifies the Button that its draw state has changed.
        */
        IMPORT_C void StateChanged();
    protected:

        /**
        * Checks whether the command stack exists. If it does not exist one is created.
        */
        inline void CheckCreateCommandStackL();

        void SetImageAttributes(CEikImage* aImage);

        /**
        * Gets the behaviour of a Button.
        * @return Button behaviour can be: stay set, stay clear or latching Button.
        */
        inline TInt Behavior() const;

        /**
        * Writes the internal state of the control and its components to aStream.
        * Does nothing in release mode.
        * Designed to be overidden and base called by subclasses.
        * @param aWriteStream  Stream to write too.
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

    private:
    enum TCknButtonBaseAlignment
        {
        ETextAlignmentConstant      =0x0001,
        EPictureAlignmentConstant   =0x0002
        };
    private:
        IMPORT_C void Reserved_2();
    private: // from CEikButtonBase
        IMPORT_C void Reserved_3();
    private:
        IMPORT_C virtual void Reserved_4();
        void SetComponentExtents(const TRect& aRect);
        void SetNewComponentExtentL();
        TBool LayoutIsVertical() const;
        void UpdateLabelReserveLengthL(const TDesC* aText);
    private: // from MCoeControlContext
        IMPORT_C void PrepareContext(CWindowGc& aGc) const;
    protected:
        TMargins8 iMargins;
    CEikAlignedControl* iComponents[2];
        TUint iCmdFlags;
        TUint iInternalFlags;
        TCknLogicalFont iLogicalFont;
        CCoeControl* iContainer;
        TInt iInterComponentGap;
		CEikLabel::TEikLabelColors* iLabelColors;
    private:
        TInt iDrawOffset;
        CCknCommandStack* iCommandStack;
        TBool iDefault;
        TInt iDummy;
        TGulAlignmentValue iTextAlignment;
        TGulAlignmentValue iPictureAlignment;
    };


#endif  // CKNBUTTONBASE_H

// End of File
