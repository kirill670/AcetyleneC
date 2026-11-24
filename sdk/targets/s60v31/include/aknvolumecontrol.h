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

#include <aknnavidecoratorobserver.h>

#include <AknControl.h>

class CGulIcon;
class MAknsSkinInstance;
class CVolumeExtension;

/**
 * Used for controlling the volume setting on the phone.
 */
class CAknVolumeControl : public CAknControl, public MAknNaviDecoratorObserver
    {

    public:

        /** 
         * C++ default constructor. 
         */
        IMPORT_C CAknVolumeControl();

        /** 
         * Destructor. 
         */
        IMPORT_C ~CAknVolumeControl();

        /** 
         * Sets volume.
         *
         * @param aValue The new volume.
         */
        IMPORT_C void SetValue(TInt aValue);

        /** 
         * Gets volume.
         *
         * @return The volume setting.
         */ 
        IMPORT_C TInt Value() const;

        
    public: // from CCoeControl

        /** 
         * From @c CCoeControl.
         * 
         * Gets minimun size of layout rectangle.
         *
         * @return Minimum layout rectangle size. 
         */ 
        TSize MinimumSize();
   
        /** 
         * From @c CCoeControl 
         *
         * Handles key events.
         * 
         * @param aKeyEvent Key event to be handled.
         * @param aType Type of the event.
         * @return Returns @c EKeyConsumed if key event was handled. 
         */ 
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
        
        /**
         * From @c CCoeControl.
         *
         * Construct item from given resource.
         *
         * @param aReader Resource reader reading the wanted resource set. 
         */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /** 
         * From @c CCoeControl.
         *
         * Handles the change of @c CAknVolumeControl's resources. 
         * 
         * @param aType Type of resource to change
         */ 
        IMPORT_C void HandleResourceChange(TInt aType);
        
        /**
         * Creates volume bitmap to "list pane for setting item" 
         * (setting option item volume graphic). Ownership of the returned bitmap
         * is transfered to the caller.
         *
         * @param  aValue Current value (1-10)
         * @return Volume bitmap. Ownership of the bitmap is transfered to 
         *         the caller.
         */
        IMPORT_C static CFbsBitmap* CreateBitmapL(TInt aValue);
    
        /**
        * Creates volume icon to "list pane for setting item" 
        * (setting option item volume graphic). Ownership of the returned icon
        * is transfered to the caller.
        *
        * @param  aValue Current value (1-10)
        * @return Volume icon. Ownership of the icon is transfered to 
        *         the caller.
        */
        IMPORT_C static CGulIcon* CreateSetStyleListBoxIconL( TInt aValue );
        
    protected: // from CCoeControl

        /** 
         * From @c CCoeControl. 
         *
         * Handles layout change. 
         */
        void SizeChanged();
        
        /**
         * From @c CCoeControl.
         *
         * Draws every visible item into the specified rectangle.
         *
         * @param aRect the specified rectangle.
         */ 
        void Draw(const TRect& aRect) const;
        
    public:
        /**
         * From @c CCoeControl. 
         *
         * Handles pointer events.
         * 
         * @param aPointerEvent Pointer event to be handled
         */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
         * From @c MAknNaviDecoratorObserver
         *
         * Handles Navidecorator events (Arrow left and arrow right)
         * 
         * @param aEventID ID of event to be handled
         */
        IMPORT_C void HandleNaviDecoratorEventL( TInt aEventID ); 

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );        

        
    private:
        void SetVolumeLayout(TInt aStyle);
        static TBool DrawSkinnedBackgroundL(CFbsBitGc* aFbsBitGc, MAknsSkinInstance* aSkin, 
                                            const TRect& aOrigin, TRect& aOuterRect, TRect& aInnerRect);
        
        
        /* Starts a timer for feedback effect visualization */
        void StartTimerL();
        
    	/**
    	 * A callback function for feedback effect.
    	 *
    	 * @param aThis Pointer to this volume control.
    	 */
        static TInt IndicationDrawCallbackL( TAny* aThis );
		
		/**
         * Implementation of the feedback effect (Blinking when the volume value
         * is set to the max/min value).
         */
		void SmallDirectionIndicationL();

        /**
        * (Re)create the navi icon
        */
        void CreateNaviIconL();

    private:        
        CFbsBitmap*         iBitmap;
        CFbsBitmap*         iMaskBitmap;
        TPoint              iStartPos;
        CVolumeExtension*   iExtension;
        TInt                iSpare1;
        TPoint              iBmpPos;
        TInt                iValue;
        TInt                iStyle;
    };

// AKNVOLUMECONTROL_H
#endif
