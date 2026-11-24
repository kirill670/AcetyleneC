/*
* ============================================================================
*  Name     : akntitle.h
*  Part of  : AVKON
*
*  Description:
*      A default control in the status pane's title pane.
*
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef AKNTITLE_H
#define AKNTITLE_H

#include <AknControl.h>
#include <coeccntx.h>

class CEikLabel;
class CEikImage;
class CAknTitlePaneExtension;
class CAknTitlePaneLabel;
class MAknTitlePaneObserver;

/**
 * A default control in the status pane's title pane.
 */
class CAknTitlePane : public CAknControl, public MCoeControlContext
	{
public:
    /**
    * Constructor.
    */
    IMPORT_C CAknTitlePane();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknTitlePane();
    
    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL();
    
    /**
    * Read title pane data from resource file and show it in the status pane's title pane.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
    * Set a text and show it in the status pane's title pane. Descriptor
    * is copied to the title pane control and ownership of the original descriptor
    * leaves to the application.
    *
    * @param aText Text to be shown on the title pane.
    */
    IMPORT_C void SetTextL(const TDesC& aText);
    
    /**
    * Sets text to the title pane.
    * @param aText	new text. This object takes ownership of aText.
    */
    IMPORT_C void SetText(HBufC* aText);

    /**
    * Set a text and show it in the status pane's title pane. If whole text does
    * not fit into titlepane, it will be scrolled once and then shown in truncated 
    * form. 
    *
    * Descriptor is copied to the title pane control and ownership of the original 
    * descriptor leaves to the application.
    *
    * @since 3.0
    * @param aText Text to be shown on the title pane.
    * @param aScroll If ETrue text is scrolled when needed, otherwise not.  
    * 
    */
    IMPORT_C void SetTextL(const TDesC& aText, TBool aScroll);    

    /**
    * Sets text to the title pane. If whole text does not fit into titlepane, 
    * it will be scrolled once and then shown in truncated form. 
    *
    * @since 3.0
    * @param aText	new text. This object takes ownership of aText. If NULL is
    *        given then already existing text will be used.
    * @param aScroll If ETrue text is scrolled when needed, otherwise not.  
    */
    IMPORT_C void SetText(HBufC* aText, TBool aScroll);
    
    /**
    * Returns text currently in the status pane's title pane. Ownership is not 
    * transferred.
    * @return text currently shown in the title pane.
    */
    inline const TDesC* Text() const;
    
    /**
    * Set a picture to the title pane and show it in the status pane's title pane. 
    * Title pane object takes ownership of the picture.
    * If NULL bitmap is passed, previously set image is shown.
    * @param aBitmap bitmap to the title pane.
    * @param aMaskBitmap mask of the bitmap.
    */
    IMPORT_C void SetPicture(const CFbsBitmap* aBitmap, const CFbsBitmap* aMaskBitmap = NULL);
    
    /**
    * Set a picture from file and show it in the status pane's title pane.
    * @param aFileName name of the bitmap file.
    * @param aMainId id of the bitmap in the bitmap file.
    * @param aMaskId id of the bitmap's mask in the bitmap file.
    */
    IMPORT_C void SetPictureFromFileL(const TDesC& aFileName, TInt aMainId, TInt aMaskId = -1);

    /**
    * Set a small picture to the title pane and show it in the status pane's title pane together
    * with text. This method is currently supported only in landscape orientation statuspane layouts.
    * 
    * Title pane object takes ownership of the picture.
    *
    * If NULL bitmap is passed, previously set image is used.
    *
    * @since 3.0
    * @param aBitmap bitmap to the title pane.
    * @param aMaskBitmap mask of the bitmap.
    * @param aVisible if ETrue, picture is set visible. Otherwise only text is shown.
    */
    IMPORT_C void SetSmallPicture(const CFbsBitmap* aBitmap, const CFbsBitmap* aMaskBitmap, TBool aVisible);
    
    /**
    * Set data from resource file and show it in the status pane's title pane.
    */
    IMPORT_C void SetFromResourceL(TResourceReader& aReader);
    
    /**
    * Set default value to the status pane's title pane. Default value is the 
    * name of currently active application.
    */
    IMPORT_C void SetTextToDefaultL();
    
    /**
    * Gets the maximum amount of text rows that title pane is able to display simultaneously
    * in the currently active status pane layout. Typically the return value is 
    * either 2 (default portrait mode layout) or 1 (landscape mode layouts).
    *
    * @since 3.1 
    * @return Maximum number of visible text lines.
    *
    */    
    IMPORT_C TInt MaxNumberOfVisibleTextRows() const;

    /**
    * Sets the number of text rows that can be used to display the text. 
    * The largest allowed value is the the value returned from MaxNumberOfVisibleTextRows() and 
    * the minimum value is always 1.
    *
    * @since 3.1
    * @param aRows Number of rows that can be used to display the text.
    *
    */    
    IMPORT_C void SetNumberOfVisibleTextRows(TInt aRows);
    
public: // from MCoeControlContext
    /** 
    * From MCoeControlContext. Allows to modify graphics context before Draw.
    *
    * @param aGc Graphics context to be modified.
    */
    IMPORT_C virtual void PrepareContext(CWindowGc& aGc) const;
    
protected: // From CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl. Handles the position change events.
    */
    IMPORT_C virtual void PositionChanged();

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. color scheme change.
	 * @param aType Event type.
	 */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

    /**
    * From CCoeControl. Returns number of controls inside the context pane control.
    * @return Number of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * From CCoeControl. Returns a control determined by control id.
    * @param anIndex Index of a control to be returned.
    * @return Pointer to control
    */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
    
public:
    /**
    * From CCoeControl. 
    * Handles pointer events
    * @param aPointerEvent Pointer event to be handled
    */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    /**
    * Sets observer for title pane events
    * @param aObserver pointer to title pane observer 
    */
    IMPORT_C void SetTitlePaneObserver( MAknTitlePaneObserver* aObserver);
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

public:

    /**
    * Gets title text label.
    * @internal
    */
    CEikLabel* TextLabel();

private:
    void CommonConstructL();
    TUid AppUid();

    TInt FormatTitlePaneLabelL( 
        const TInt aOneLineLayoutWidth,  const TInt aTwoLineLayoutWidth,
        const CFont* aOneLineFont,  const CFont* aTwoLineFont);

    void ReadFromResourceFileL(TResourceReader& aReader);
    
private: // From CCoeControl
    IMPORT_C virtual void Draw(const TRect& aRect) const;
    
protected:    
    MAknTitlePaneObserver* iTitlePaneObserver;
    
private:
    void SizeChangedInNormalStatusPane();
    void SizeChangedInExtendedStatusPane();
    void SizeChangedInFlatStatusPane();
    void SizeChangedInStaconPane();
    RWindow* StatuspaneContainerWindow() const;
    void SetupTitleLabelEffectL();
    void SetContainerWindowNonFading(TBool aNonFading);
    
    void SetupStaconPaneScrollEffectL();
    void SetupFlatStatusPaneScrollEffectL();
    void SetupNormalStatusPaneScrollEffectL();
    void SetupFlatStatusPaneFadeEffectL();
    void SetupExtendedStatusPaneScrollEffectL();
    void SetupNoEffectL();
    
private:
    HBufC* iTitleText;
    HBufC* iDefaultTitleText;
    CAknTitlePaneLabel* iTitleLabel;
    TBool iImageShown;
    CAknTitlePaneExtension* iExtension;
    };


inline const TDesC* CAknTitlePane::Text() const
    { return(iTitleText); }


// AKNTITLE_H
#endif
