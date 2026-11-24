/*
* ============================================================================
*  Name     : CAknVolumeControl from Aknvolumecontrol.h
*  Part of  : Avkon
*
*  Description:
*     Volume editor class
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

#ifndef AKNVOLUMECONTROL_H
#define AKNVOLUMECONTROL_H

// Forward declarations
class CGulIcon;
class MAknsSkinInstance;
class CVolumeExtension;

// CLASS DECLARATION
class CAknVolumeControl : public CCoeControl
    {
    public:
        IMPORT_C CAknVolumeControl();
        IMPORT_C ~CAknVolumeControl();
        IMPORT_C void SetValue(TInt aValue);
        IMPORT_C TInt Value() const;
        
    public: // from CCoeControl

        TSize MinimumSize();
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /**
        *  Returns volume bitmap to "list pane for setting item" 
        *  (setting option item volume graphic). Ownership of the returned bitmap
        *  is transfered to the caller.
        *
        * @param  aValue Current value (1-10)
        * @return Volume bitmap. Ownership of the bitmap is transfered to the caller
        */
        IMPORT_C static CFbsBitmap* CreateBitmapL(TInt aValue);
    
        /**
        *  Returns volume icon to "list pane for setting item" 
        *  (setting option item volume graphic). Ownership of the returned icon
        *  is transfered to the caller.
        *
        * @param  aValue Current value (1-10)
        * @return Volume icon. Ownership of the icon is transfered to the caller
        */
        IMPORT_C static CGulIcon* CreateSetStyleListBoxIconL( TInt aValue );
        
    protected: // from CCoeControl
        void SizeChanged();
        void Draw(const TRect& aRect) const;
        
    private:
        void SetVolumeLayout(TInt aStyle);
        static TBool DrawSkinnedBackgroundL(CFbsBitGc* aFbsBitGc, MAknsSkinInstance* aSkin, 
                                            TRect& aOrigin, TRect& aOuterRect, TRect& aInnerRect);

    private:        
        CFbsBitmap*         iBitmap;
        CFbsBitmap*         iMaskBitmap;
        TPoint              iStartPos;
        CVolumeExtension*   iExtension;
        TInt                iSpare1;     // not in use
        TPoint              iBmpPos;
        TInt                iValue;
        TInt                iStyle;
    };

#endif        // AKNVOLUMECONTROL_H
            
// End of File
