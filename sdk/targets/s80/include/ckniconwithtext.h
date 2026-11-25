/*
* ==============================================================================
*  Name        : ckniconwithtext.h
*  Part of     : CKON
*  Interface   : Icon API
*  Description : CCknIconWithText implements a control that has a single Icon
*                followed by a single text string.
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


#ifndef CKNICONWITHTEXT_H
#define CKNICONWITHTEXT_H

// INCLUDES
#include <cknbctrl.h>

/**
* The <code>CCknIconWithText</code> class implements a control that has a 
* single Icon followed by a single text string. A bitmap, a text descriptor, 
* and a maximum width, in pixels, must be specified. The 
* image to use can be specified from a UID and index pair (which 
* describes a bitmap), or by using an externally owned bitmap and mask pair. 
* Late initialization of the contents can be achieved using the
* <code>AddContentsL()</code> methods, although the client should ensure that
* the contents are set before drawing the control. It is possible 
* to specify the maximum width of the control in a resource file (using 
* the <code>ConstructFromResourceL()</code> method). The bitmap and text
* cannot be set in the resource file. The 
* size of the control should be set using the size returned from 
* the <code>MinimumSize()</code> method.
*
* @lib cknctl.lib
* @since Series90 1.0
*/
class CCknIconWithText : public CCknBorderedControl
    {
    public: 
        /**
        * Constructs and returns a pointer to a new <code>CCknIconWithText</code>
        * object. This variant initializes the object to settings defined by 
        * the caller.
        *
        * @param aBitmapIndex Determines which bitmap to 
        *                     display in the control. The index is in 
        *                     the MBM group specified by <code>aMbmUid</code>
        * @param aMbmUid Locates the Icon 
        *                bitmap
        * @param aText The reference to a text string displayed in the 
        *              control
        * @param aMaximumWidth The maximum width for the control, in pixels
        * @return the newly instantiated object
        * @remarks The single <code>aBitmapIndex</code> argument 
        *          defines both the bitmap index and the mask for the Icon
        * @see <code>NewL()</code>
        * @see For more information on acquiring bitmaps using the UID of the 
        *      .mbm and an index within it, see Skin API documentation 
        */
        IMPORT_C static CCknIconWithText* NewL(TInt aBitmapIndex,
                                             TUid aMbmUid,
                                             const TDesC& aText, 
                                             TInt aMaximumWidth);
        /**
        * Constructs and returns a pointer to a new <code>CCknIconWithText</code>
        * object. This variant creates the object without setting internal 
        * members.  
        * 
        * @return the newly instantiated object
        * @remarks Initialization of the bitmaps, text, and maximum width 
        *          should be completed before the control is drawn
        * @see <code>NewL(TInt aBitmapIndex,TUid aMbmUid,const TDesC& aText,
        *      TInt aMaximumWidth)</code>
        */
        IMPORT_C static CCknIconWithText* NewL();
        
        /**
        * Constructs an Icon control from a resource file. The resource ID is 
        * <code>ECknCtIconWithText</code>.
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>ICONWITHTEXT</code>. This method
        *          only initializes the maximum control width, in pixels. It 
        *          does not initialize the bitmap or text
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /**
        * Sets the Icon and text displayed by the control.
        *
        * @param aBitmapIndex Determines which bitmap to 
        *                     display in the control. The index is within 
        *                     the MBM group specified by <code>aMbmUid</code>
        * @param aMbmUid Locates the Icon bitmap
        * @param aText A text string displayed in the control
        * @remarks This method is safe to call, even if the contents have 
        *          previously been initialized. The single 
        *          <code>aBitmapIndex</code> argument defines both 
        *          the bitmap index and the mask for the Icon
        * @remarks This method does not trigger a redraw of the control
        * @see For more information on acquiring bitmaps using the UID of the 
        *      .mbm and an index within it, see Skin API documentation 
        */
        IMPORT_C void AddContentsL(TInt aBitmapIndex, 
                                  TUid aMbmUid,
                                  const TDesC& aText);

        /**
        * Sets the Icon and text displayed by the control.
        *
        * @param aBitmap An externally owned bitmap to display in the control
        * @param aMask The bitmap mask - externally owned
        * @param aText The text string displayed in the control
        * @remarks This method is safe to call, even if the contents have 
        *          previously been initialized. This method does not trigger 
        *          a redraw of the control
        * @see
        */
        IMPORT_C void AddContentsL(const CFbsBitmap* aBitmap, 
                                   const CFbsBitmap* aMask,
                                   const TDesC& aText);

        /**
        * Sets the text displayed by the control.
        *
        * @param aText The text string displayed in the control
        * @remarks This method does not trigger a redraw of the control
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

        /**
        * Sets the maximum width used by the control.
        *
        * @param aWidth The maximum width used by the control, in pixels 
        * @remarks This method does not trigger a redraw of the control
        * @see
        */
        IMPORT_C void SetMaximumWidth(TInt aWidth);

        /**
        * Gets the minimum size for the Icon control.
        * 
        * @return the minimum size of the Icon control
        * @remarks This method should only be called after the contents of the
        *          control, that is, the bitmaps and text, have been 
        *          initialized
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();
    protected:
        /**
        * C++ default constructor.
        *
        * @return
        * @remarks  Sets iMaximumWidth to the default value (240 pixels),
        *           but does no further object initialisation
        * @see
        */
        IMPORT_C CCknIconWithText();
        /**
        * Destructor.
        *
        * @return
        * @remarks
        * @see
        */
        IMPORT_C ~CCknIconWithText();
        /**
        * Base constructor.
        * @param    aBitmapIndex Index used to determine which Icon to
        *           display in the control. The index is within the mbm
        *           group specified by <code>aMbmUid</code>
        * @param    aMbmUid The MbmUid used to locate the Icon bitmap
        * @param    aText Reference to a text string displayed in the control
        * @param    aMaximumWidth The maximum width in pixels for the control   
        * @return
        * @remarks
        * @see  
        */
        IMPORT_C void BaseConstructL(TInt aBitmapIndex,
                        TUid aMbmUid,
                        const TDesC& aText, 
                        TInt aMaximumWidth);
        /**
        * Draws the Icon and text.
        *
        * @param    aRect The invalidated rect which is unused. The control
        *           is redrawn completely
        * @return
        * @remarks  Uses logical font <code>TCknLogicalFont::EDialogLabelFont
        *           </code> for the text
        *           Truncates text to maintain iMaximumWidth
        * @see
        */
        IMPORT_C void Draw(const TRect& aRect) const;
        /**
        * Method to calculate the available width in pixels for the
        * control's text.
        *
        * @return   Maximum width in pixels available for text in the control
        * @remarks
        * @see
        */
        IMPORT_C TInt WidthForText() const;
    private: 
// from CCoeControl
        /**
         * Method to refetch the bitmap if the skin resource changes.
         *
         * @param   aType The type of the resource which has changed
         */
        IMPORT_C void HandleResourceChange(TInt aType);
    protected:
        /**
        * The text displayed by the control.
        */
        HBufC* iText;
        /**
        * The maximum width of the control.
        */
        TInt iMaximumWidth;
        /**
        * The index of the bitmap displayed by the control
        * used to refetch the bitmap on resource change.
        */
        TInt iBitmapIndex; 
        /**
        * The MbmUid used to locate the bitmap.
        */
        TUid iMbmUid;
        /**
        * An externallly owned bitmap to be displayed by the control.
        */
        const CFbsBitmap* iBitmap;
        /**
        * An externallly owned bitmap mask to be displayed by the control.
        */
        const CFbsBitmap* iMask;
        /**
        * Internal flags.
        */
        TUint iFlags;
    private:
        TAny* iReserved;
    };

#endif  // CKNICONWITHTEXT_H

// End of File
