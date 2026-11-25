/*
* ==============================================================================
*  Name        : ckntoolbarbutton.h
*  Part of     : CKON
*  Interface   : Toolbar Button API
*  Description : Toolbar button controls
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


#ifndef CKNTOOLBARBUTTON_H
#define CKNTOOLBARBUTTON_H

// INCLUDES
#include <eikcmbut.h>

/**
*  The <code>CCknToolBarButton</code> class provides a button used in a 
*  Toolbar. This is a type of <code>CEikCommandButton</code> specifically for 
*  use in a Toolbar. 
*
*  @lib cknctl.lib
*  @since Series 90 1.0
*/
class CCknToolBarButton : public CEikCommandButton
    {
public:
        
    /**
    * The default object constructor.
    */
    IMPORT_C CCknToolBarButton();
        
    /**
    * The object destructor.
    */
    IMPORT_C ~CCknToolBarButton();
        
    /**
    * Constructs the Toolbar button image from resource. If the bitmap is not 
    * defined by a specific .mbm file, an icon defined by the skin .mbm is used.
    *
    * @param aReader The resource reader
    * @remarks
    * @see
    */
    IMPORT_C void ConstructImageFromResourceL(TResourceReader& aReader);
private: // from CCoeControl
    IMPORT_C void Draw(const TRect& aRect) const;
    IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C TSize MinimumSize();
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
protected:
    const CCoeControl* iParent;
    TInt iMbmUid;
    TInt iBitmapId;
    };

/**
*  The <code>CCknToolBarBitmapButton</code> creates a Toolbar button with a 
*  bitmap image.
*
*  @lib cknctl.lib
*  @since Series 90 1.0
*/
class CCknToolBarBitmapButton : public CEikBitmapButton
    {
public:

    /**
    * The default object constructor.
    */
    IMPORT_C CCknToolBarBitmapButton();

    /**
    * The object destructor.
    */
    IMPORT_C ~CCknToolBarBitmapButton();
private: // from CCoeControl
    IMPORT_C void Draw(const TRect& aRect) const;
    IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C TSize MinimumSize();

private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
protected:
    /**
    * The parent control
    */
    const CCoeControl* iParent;
    };

/**
* The <code>CCknToolBarTwoPictureButton</code> class provides a Toolbar button
* with two pictures; one for its untapped state and one for the button's state 
* when selected and latched down.
*
* @lib cknctl.lib
* @since Series 90 1.0
*/
class CCknToolBarTwoPictureButton : public CEikTwoPictureCommandButton
    {
public:

    /**
    * The default object constructor.
    */
    IMPORT_C CCknToolBarTwoPictureButton();

    /**
    * The object destructor.
    */
    IMPORT_C ~CCknToolBarTwoPictureButton();
private: // from CCoeControl
    IMPORT_C void Draw(const TRect& aRect) const;
    IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C TSize MinimumSize();
private: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
protected:
    /**
    * The parent control
    */
    const CCoeControl* iParent;
    };



#endif  // CKNTOOLBARBUTTON_H

// End of File
