/*
* =============================================================================
*  Name        : eikimage.h
*  Part of     : CKON
*  Interface   : Image API
*  Description : 
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
* =============================================================================
*/

#ifndef EIKIMAGE_H
#define EIKIMAGE_H


// INCLUDES
#include <eikalign.h>


// FORWARD DECLARATIONS
class CFbsBitmap;
class CBitmapContext;

// CLASS DECLARATIONS

/**
 *
 * This class provides methods that enable the packaging of bitmaps into
 * an Image.
 * Two bitmaps can be packaged, one for the Image itself and, optionally,
 * another for the Image's mask.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikImage : public CEikAlignedControl
    {
    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        */
        IMPORT_C CEikImage();
        /**
        * The object destructor.
        */
        IMPORT_C ~CEikImage();
    // New methods
        
        /**
        * Gets the minimum size required to draw the Image.
        *
        * @return  the minimum size required to draw the Image
        * @remarks Includes the dimensions of the Image plus any margins set
        *          by the base class
        * @see
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Constructs an Image from a resource file.
        *
        * @param aReader A resource reader
        * @remarks The resource type is <code>IMAGE</code>.
        *          The <code>TResourceReader</code> class is defined in 
        *          barsread.h
        * @see
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /**
        * Creates an Image from a multi-bitmap (.mbm) file.
        *
        * @param aFilename The file from which the Image is created
        * @param aMainId The ID of the bitmap to use in the Image
        * @param aMaskId The ID of the bitmap mask to use in the Image.  This 
        *                can be the same as <code>aMainId</code>, in order to 
        *                use the same bitmap as both the bitmap and mask. The
        *                default is to have no mask (<code>aMaskId = -1</code>)
        * @remarks This method can only be called once in the lifetime of an 
        *          Image, since it does not destroy existing bitmaps before 
        *          creating new ones and this would lead to a heap error on exit
        * @see
        */
        IMPORT_C void CreatePictureFromFileL(const TDesC& aFilename,TInt aMainId,TInt aMaskId=-1);
        
        /**
        * Sets the bitmap and mask for the Image.
        *
        * @param aBitmap The Image's bitmap
        * @param aMaskBitmap The Image's bitmap mask
        * @remarks The previous bitmaps are destroyed unless owned externally.
        *          <code>CFbsBitmap</code> is defined in fbs.h
        * @see
        */
        IMPORT_C void SetPicture(const CFbsBitmap* aBitmap,const CFbsBitmap* aMaskBitmap=NULL);
        
        /**
        * This method has no effect.
        *
        * @param aEmphasis <code>ETrue</code> to set the Image as emphasized; 
        *                  <code>EFalse</code> to set the Image as not 
        *                  emphasized
        * @remarks This method has no effect
        * @see
        */
        IMPORT_C void SetEmphasis(TBool aEmphasis);
        
        /**
        * Sets whether the Image's bitmaps are externally owned.
        *
        * @param aOwnership <code>ETrue</code> to set the Image as externally
        *        owned, <code>EFalse</code> to set the Image as not externally
        *        owned
        * @remarks If the Image is externally owned, it is the responsibility 
        *          of the caller to delete any bitmaps set using 
        *          <code>SetPicture</code>
        * @see
        */
        IMPORT_C void SetPictureOwnedExternally(TBool aOwnership);
        
        /**
        * Gets the Image's bitmap.
        *
        * @return a pointer to the Image's bitmap
        * @remarks  <code>CFbsBitmap</code> is defined in fbs.h
        * @see
        */
        IMPORT_C const CFbsBitmap* Bitmap() const;
        
        /**
        * Gets the Image's bitmap mask.
        *
        * @return a pointer to the Image's bitmap mask
        * @remarks <code>CFbsBitmap</code> is defined in fbs.h
        * @see
        */
        IMPORT_C const CFbsBitmap* Mask() const;
        
        /**
        * Sets the Image's bitmap and transfers ownership unless the bitmaps are
        * owned externally.
        *
        * @param aBitmap A pointer to the Image's bitmap
        * @remarks The previous bitmap is not destroyed, even if it is not
        *          externally owned. <code>CFbsBitmap</code> is defined in 
        *          fbs.h
        * @see
        */
        IMPORT_C void SetBitmap(const CFbsBitmap* aBitmap);
        
        /**
        * Sets the mask to <code>aMask</code> and transfers ownership, unless 
        * the bitmaps are owned externally.
        *
        * @param aMaskBitmap A pointer to the Image's bitmap mask
        * @remarks The previous bitmap is not destroyed even if it is not
        *          externally owned 
        * @see
        */
        IMPORT_C void SetMask(const CFbsBitmap* aMaskBitmap);
        /**
        * SetNewBitmaps
        * @deprecated
        */
        IMPORT_C void SetNewBitmaps(const CFbsBitmap* aNewBitmap,const CFbsBitmap* aNewMask);
        
        /**
        * Tests whether the Image is owned externally.
        *
        * @return <code>ETrue</code> if the Image is owned externally,
        *         <code>EFalse</code> otherwise
        * @remarks If the picture is specified as owned externally, it is the 
        *          responsibility of the application that creates the Image
        *          to delete the bitmaps. If it is not owned externally, the
        *          bitmaps are deleted within the destructor for this class
        * @see
        */
       IMPORT_C TBool IsPictureOwnedExternally();
    protected:  // Methods
    // Methods from base classes

        /**
        * From CCoeControl.
        * Writes the internal state of the control and its components to aStream.
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private: //Methods
        IMPORT_C void Draw(const TRect& aRect) const;
        IMPORT_C void Reserved_2();
    private:  // Declarations
    enum TFlags
        {
        /** has no effect */
        EFullEmphasis           = 0x01,
        /** indicates that the Image will not delete its bitmaps */
        EPictureOwnedExternally = 0x02,
        /** indicates that the same bitmap is used for Image and its mask */
        ESameBitmapAndMask      = 0x04
        };
    private:     // Data
        const CFbsBitmap* iBitmap;
        const CFbsBitmap* iMaskBitmap;
        TInt iImFlags;
        TInt iSpare;
    };


#endif      // EIKIMAGE_H   
            
// End of File
