/*
* ==============================================================================
*  Name        : AknIconUtils.h
*  Part of     : AknIcon
*  Interface   : AknIcon
*  Description : Utility functions related to scalable icons.
*
*  Version     : 1
*
*  Copyright (c) 2002 Nokia Corporation.
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


#ifndef AKN_ICON_UTILS_H
#define AKN_ICON_UTILS_H

// INCLUDES
#include <e32std.h>
#include <gdi.h>

// FORWARD DECLARATIONS
class CFbsBitmap;
class MAknIconObserver;

// ENUMERATIONS
enum TScaleMode
    {
    /*
    * Scales the icon to the maximum size that fits in the given size,
    * whilst preserving the aspect ratio of the icon. The sizes of the resulting
    * bitmaps are exactly of the given size. If the aspect ratio of
    * the given size differs from the aspect ratio of the icon,
    * the resulting bitmaps will contain an unused area.
    */
    EAspectRatioPreserved = 0,

    /*
    * Scales the icon to the maximum size that fits in the given size,
    * whilst preserving the aspect ratio of the icon. The resulting bitmaps
    * are resized so that any unused portion of the given size is not
    * present in them.
    *
    * This mode should be used when only the height or the width of the icon
    * is known and the other should be based on the aspect ratio of the icon.
    * The unknown dimension should be defined high enough (e.g. KMaxTInt) so
    * that it does not limit the scaling based on the aspect ratio of the icon.
    */
    EAspectRatioPreservedAndUnusedSpaceRemoved = 1,

    /*
    * Scales the icon exactly to the given size. Does not preserve the aspect
    * ratio of the icon.
    */
    EAspectRatioNotPreserved = 2
    };

// CLASS DECLARATIONS

// Cleanup stack helper. Onws the bitmap and the mask.
NONSHARABLE_CLASS(CAknIcon) : public CBase
    {
    public:
        IMPORT_C static CAknIcon* NewL();
        ~CAknIcon();
    public:
        IMPORT_C CFbsBitmap* Bitmap() const;
        IMPORT_C CFbsBitmap* Mask() const;
        IMPORT_C void SetBitmap( CFbsBitmap* aBitmap );
        IMPORT_C void SetMask( CFbsBitmap* aMask );
    private:
        inline CAknIcon() {}

    private:
        CFbsBitmap* iBitmap; // owned
        CFbsBitmap* iMask; // owned
    };

/**
* AknIconUtils
*/
class AknIconUtils
    {
    public:

        /**
        * Creates bitmap and mask for an icon.
        * Allocates bitmap and mask objects and sets aBitmap and
        * aMask to point at them. Ownership of those is transferred to the caller.
        * These bitmaps are not ready for drawing until they are initialized with
        * SetSize method. Usually, UI controls do this. Note also that a single
        * SetSize call initializes both the bitmap and the mask.
        *
        * Use this method only if aBitmap and aMask are member variables.
        * Otherwise, use method CreateIconLC.
        *
        * @since 2.8
        * @param aBitmap icon bitmap is stored here
        * @param aMask icon mask is stored here
        * @param aFileName File name. Can be either MBM or MIF file.
        * Extension is changed based on the given bitmap ID.
        * @param aBitmapId bitmap Id
        * @param aMaskId mask Id
        */
        IMPORT_C static void CreateIconL(
            CFbsBitmap*& aBitmap,
            CFbsBitmap*& aMask,
            const TDesC& aFileName,
            TInt aBitmapId,
            TInt aMaskId );

        /**
        * Creates bitmap and mask for an icon.
        * Allocates bitmap and mask objects and sets aBitmap and
        * aMask to point at them. Ownership of those is transferred to the caller.
        * These bitmaps are not ready for drawing until they are initialized with
        * SetSize method. Usually, UI controls do this. Note also that a single
        * SetSize call initializes both the bitmap and the mask.
        *
        * This method puts both aBitmap and aMask in the cleanup stack.
        *
        * @since 2.8
        * @param aBitmap icon bitmap is stored here
        * @param aMask icon mask is stored here
        * @param aFileName File name. Can be either MBM or MIF file.
        * Extension is changed based on the given bitmap ID.
        * @param aBitmapId bitmap ID
        * @param aMaskId mask ID
        */
        IMPORT_C static void CreateIconLC(
            CFbsBitmap*& aBitmap,
            CFbsBitmap*& aMask,
            const TDesC& aFileName,
            TInt aBitmapId,
            TInt aMaskId );

        /**
        * Creates the bitmap for an icon.
        * Use this variant when a mask is not needed.
        * Ownership of the returned object is transferred to the caller.
        * The bitmap is not ready for drawing until it is initialized with
        * SetSize method. Usually, UI controls do this.
        *
        * @since 2.8
        * @param aBitmap icon bitmap is stored here
        * @param aFileName File name. Can be either MBM or MIF file.
        * Extension is changed based on the given bitmap ID.
        * @param aBitmapId bitmap ID
        */
        IMPORT_C static CFbsBitmap* CreateIconL(
            const TDesC& aFileName,
            TInt aBitmapId );

        /**
        * Preserves the icon data (e.g. SVG-T data) related to the given icon
        * in memory. After this, the icon data is destroyed when either
        * DestroyIconData is explicitly called or the bitmap(s) of the icon are
        * deleted.
        *
        * This method should be called to improve performance if more than one
        * call to methods SetSize, SetSizeAndRotation or GetContentDimensions
        * is made successively on a particular icon. It should be called prior
        * to the above-mentioned calls. Without calling this method,
        * the icon data is destroyed after any of the method calls mentioned
        * above and then loaded from the storage medium and parsed from scratch
        * again in a new operation.
        *
        * Note! Icon data may consume considerable amounts of memory. In order
        * to save memory, any code that calls PreserveIconData should also
        * explicitly call DestroyIconData when the icon data is no longer
        * required.
        *
        * @since 2.8
        * @param aBitmap bitmap or mask of the icon.
        */
        IMPORT_C static void PreserveIconData( CFbsBitmap* aBitmap );

        /**
        * Destroys the icon data related to the given icon,
        * if it was preserved in memory. Note that this does not affect
        * the rendered frame buffers (CFbsBitmap objects).
        *
        * @since 2.8
        * @param aBitmap bitmap or mask of the icon.
        */
        IMPORT_C static void DestroyIconData( CFbsBitmap* aBitmap );

        /**
        * Initializes the icon to the given size, if the parameter aBitmap is
        * an instance of CAknBitmap, i.e. created with AknIconUtils methods.
        * If it is not CAknBitmap, this method does nothing. Note that this call
        * sets the sizes of both bitmap and mask (if it exists), regardless of
        * which is given as the parameter.
        *
        * @since 2.8
        * @param aBitmap bitmap or mask of the icon
        * @param aSize icon size
        * @param aMode scale mode
        * @return Standard Symbian OS error code. In error cases, the icon
        * is initialized to be of size (0,0).
        */
        IMPORT_C static TInt SetSize(
            CFbsBitmap* aBitmap,
            const TSize& aSize,
            TScaleMode aMode = EAspectRatioPreserved );

        /**
        * Initializes the icon to the given size, if the parameter aBitmap is
        * an instance of CAknBitmap, i.e. created with AknIconUtils methods.
        * If it is not CAknBitmap, this method does nothing. Note that this call
        * sets the sizes of both bitmap and mask (if it exists), regardless of
        * which is given as the parameter. Additionally, this method rotates
        * the icon according to the given angle.
        *
        * @since 2.8
        * @param aBitmap bitmap or mask of the icon
        * @param aSize icon size
        * @param aAngle Rotation angle in degrees.
        * @return Standard Symbian OS error code. In error cases, the icon
        * is initialized to be of size (0,0).
        */
        IMPORT_C static TInt SetSizeAndRotation(
            CFbsBitmap* aBitmap,
            const TSize& aSize,
            TScaleMode aMode,
            TInt aAngle );

        /**
        * Sets observer for change notification.
        * 
        * The method BitmapChanged() will be called when the contents of the CFbsBitmap
        * are changed. Controls can use this to redraw themselves when icon
        * animation progresses.
        * 
        * @since 2.8
        * @param aBitmap bitmap
        * @param aObserver observer
        */
        IMPORT_C static void SetObserver( CFbsBitmap* aBitmap, MAknIconObserver* aObserver );

        /**
        * Returns the file name of Avkon's icon file, containing full path.
        *
        * @since 2.8
        * @ret Avkon's icon file name, containing full path.
        */
        IMPORT_C static const TDesC& AvkonIconFileName();

        /**
        * Validates logical app icon ID so that it can be used as a parameter to
        * CreateIconL or CreateIconLC. If the given icon file name is .MBM file,
        * this method does nothing. If it is .MIF file, a predefined offset is
        * added to the given IDs.
        *
        * This method is only intended to be used when loading icons from the
        * icon file retrieved from AppArc.
        *
        * @param aIconFileName Icon file name retrieved from AppArc.
        * @param aId Logical bitmap ID used in the app icon file, usually 0.
        * @param aId Logical mask ID used in the app icon file, usually 1.
        */
        IMPORT_C static void ValidateLogicalAppIconId( 
            const TDesC& aIconFileName,
            TInt& aBitmapId,
            TInt& aMaskId );

        /**
        * Tells whether the given file name is recognized as a MIF file or not.
        * Only the file name extension is examined, not the contents of the file.
        *
        * @since 2.8
        * @param aFileName file name
        *
        * @return ETrue if MIF file, EFalse otherwise.
        */
        IMPORT_C static TBool IsMifFile( const TDesC& aFileName );

        /**
        * Tells whether the given bitmap is a part of a MIF icon or not.
        * Accepts any pointer (also NULL) as a parameter.
        *
        * @since 2.8
        * @param aBitmap bitmap
        *
        * @return ETrue if the given bitmap is part of a MIF icon,
        * EFalse otherwise.
        */
        IMPORT_C static TBool IsMifIcon( const CFbsBitmap* aBitmap );

        /**
        * Returns the content dimensions of the given icon.
        * In case of MBM icons, this is the original size of the bitmap.
        * In case of SVG icons, this is defined in the icon data.
        *
        * If SetSize or SetSizeAndRotation is going to be called on the same
        * icon after this call, the performance can be improved by calling
        * PreserveIconData before calling this method.
        * 
        * @since 2.8
        * @param aBitmap bitmap
        * @param aContentDimensions The content dimensions are returned here.
        *
        * @ret Standard Symbian OS error code.
        */
        IMPORT_C static TInt GetContentDimensions(
            CFbsBitmap* aBitmap,
            TSize& aContentDimensions );

        /**
        * Creates bitmap and mask for an icon.
        * Allocates bitmap and mask objects and sets aResultIcon to point at them.
        *
        * When this method returns, the resulting bitmaps are
        * duplicates of the source bitmaps.
        * Also the source bitmap instances are preserved in memory.
        *
        * Ownership of aSourceIcon is transferred from caller.
        * This method takes the responsibility of deleting the object
        * even if the method leaves.
        *
        * The returned icon bitmaps are instances of CAknBitmap,
        * so AknIconUtils::SetSize is functional for them.
        *
        * AknIconUtils::SetSize first creates duplicates of the source bitmaps
        * and after that, if required, creates new bitmaps and performs scaling.
        *
        * Note that due to the additional memory consumption caused by the source bitmaps,
        * this method should only be used if it is not possible to use the variant of
        * CreateIconL that takes icon file name and IDs as parameters.
        *
        * @since 2.8
        * @param aResultIcon Icon bitmap and mask are returned here. Ownership
        *   of the object is transferred to the caller.
        * @param aSourceIcon Contains source bitmap and mask.
        *   Ownership of aSourceIcon is transferred from caller.
        *   This method takes the responsibility of deleting the object
        *   even if the method leaves.
        */
        IMPORT_C static CAknIcon* CreateIconL( CAknIcon* aSourceIcon );

        /**
        * Non-masked variant of CreateIconL.
        *
        * Ownership of aSourceBitmap is transferred from caller.
        * This method takes the responsibility of deleting the object
        * even if the method leaves.
        * 
        * @since 2.8
        * @param aSourceBitmap Source bitmap.
        *   Ownership is transferred from caller.
        *   This method takes the responsibility of deleting the object
        *   even if the method leaves.
        *
        * @ret Resulting icon bitmap. Ownership transferred to the caller.
        */
        IMPORT_C static CFbsBitmap* CreateIconL( CFbsBitmap* aSourceBitmap );

        /**
        * Determines the icon color. Only effective if the given bitmap is
        * an instance of CAknBitmap. This method only needs to be called either
        * for the bitmap or the mask of an icon, but to be effective, it needs
        * to be called before calling SetSize or SetSizeAndRotation.
        *
        * TRgb value 0xFF000000 is reserved for internal use. Giving that as
        * a parameter will cause a client panic.
        *
        * @since 2.8
        * @param aBitmap bitmap
        * @param aColor icon color
        */
        IMPORT_C static void SetIconColor( CFbsBitmap* aBitmap, const TRgb aColor );

        /**
        * Utility for down-cast of CFbsBitmap objects. It informs whether
        * the given CFbsBitmap is CAknBitmap or not. A list of CAknBitmap
        * pointers is managed in TLS for this.
        * 
        * @param aBitmap bitmap
        * @ret ETrue iff the given CFbsBitmap is an CAknBitmap instance.
        */
        static TBool IsAknBitmap( const CFbsBitmap* aBitmap );

        /**
        * Bitmap scaling. Might be exported later.
        * This is ~15x faster than scaling with Symbian's DrawBitmap.
        */
        static void ScaleBitmapL( 
            const TRect& aTrgRect,
            CFbsBitmap* aTrgBitmap,
            CFbsBitmap* aSrcBitmap );

        /**
        * Bitmap rotation and scaling. Might be exported later. Scales and
        * rotates the given bitmap according to the parameters. Supported 
        * bitmap modes are EGray2, EGray256, EColor256, EColor4K, EColor64K and 
        * EColor16MU. All other bitmap depts will cause a leave with
        * KErrNotSupported. The only supported scalemode is 
        * EAspectRatioPreserved. The unused area in the target bitmap is
        * filled with black color unless the bitmap depth is EGray8 when the
        * area is filled with white. Areas that do not fit to the target area
        * after rotation are clipped out
        *
        * If the bitmap depth is EGray2, the routine will perform noticeably worse.
        * 
        * @since 2.8
        *
        * @param aTrgRect target rect inside the target bitmap
        * @param aTrgBitmap the target bitmap
        * @param aSrcBitmap the source bitmap
        * @param aAngle the rotation angle in degrees
        */
        static void RotateAndScaleBitmapL(
            const TRect& aTrgRect,
            CFbsBitmap* aTrgBitmap, 
            CFbsBitmap* aSrcBitmap,
            TInt aAngle );
        
    private:

        AknIconUtils();
    };

#endif // AKN_ICON_UTILS_H
            
// End of File
