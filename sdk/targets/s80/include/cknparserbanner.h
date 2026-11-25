/*
* =============================================================================
*  Name        : cknparserbanner.h
*  Part of     : CKON
*  Interface   : Parser Banner API
*  Description : CCknParserBanner class creates the parser banner control.
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


#ifndef CKNPARSERBANNER_H
#define CKNPARSERBANNER_H

// INCLUDES
#include <cknbctrl.h>

// FORWARD DECLARATIONS
class CRichText;
class MParser;

/**
*  The <code>CCknParserBanner</code> class creates the parser banner control,
*  which can have the screen or owner's rect boundary.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknParserBanner : public CCknBorderedControl
    {
    public:

    /** 
    * The enumeration <code>TParserBannerBounds</code> specifies whether the 
    * parser banner may extend beyond the owning control or not. This is used 
    * as an argument to <code>CEikRichTextEditor::EnableParserBanner()</code>.
    */
    enum TParserBannerBounds
        {
        /** the parser banner can extend beyond the owning control */
        EParserBannerBoundByScreen,
        /** the parser banner must be drawn within the bounds of the owning control */
        EParserBannerBoundByOwnerRect
        };


        /**
        * Two-phased constructor.
        * @internal
        */
        IMPORT_C static CCknParserBanner* NewL();

        /**
        * Destructor.
        * @internal
        */
        ~CCknParserBanner();

        /**
        * Sets the parser banner. The method also calculates the size of the 
        * banner.
        * 
        * @param aParser A pointer to the parser for the current tag
        * @param aRichText A pointer to the rich text object that contains the 
        *                  tag
        * @param aTagStart The start position of the tag that the cursor is on
        * @param aTagLen The length of the tag that the cursor is on
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C void SetL(MParser* aParser, CRichText* aRichText, TInt aTagStart, TInt aTagLen);

        /**
        * Sets the parser banner position.
        * 
        * @param aPos Banner position
        * @param aCursorHeight Cursor height
        * @param aBoundary Banner's boundary
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C void SetPositionL(TPoint aPos, TInt aCursorHeight, TRect aBoundary);

        /**
        * Clears the parser banner.
        * 
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C void Clear();

        /**
        * Brings parser banner to the front.
        * 
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C void BringToFront();

        /**
        * Whether parser banner is active.
        * 
        * @return <code>ETrue</code> if parser banner is active. 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C TBool IsActive();

        /**
        * Enables/disables the parser banner.
        * 
        * @param aEnable True if the parser banner is enabled
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C void Enable(TBool aEnable);

        /**
        * Whether parser banner is enabled.
        * 
        * @return <code>ETrue</code> if parser banner is enabled
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C TBool IsEnabled();

        /**
        * Sets the banner boundary type.
        * 
        * @param aType Stores whether the banner boundary is the screen or the 
        *              owner's rect
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C void SetBoundaryType(TParserBannerBounds aType);

        /**
        * Gets the banner boundary type.
        * 
        * @remarks
        * @see
        * @internal
        */
        IMPORT_C CCknParserBanner::TParserBannerBounds BoundaryType();

    public: 

        /**
        * Handles pointer events.
        *
        * @param aPointerEvent The pointer event
        * @remarks
        * @see CCoeControl
        * @internal
        */
        void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Sets the size and position of contents of control after a resize.
        *
        * @remarks
        * @see CCoeControl
        * @internal
        */
        void SizeChanged();

    private:  // from CCoeControl
        void Draw(const TRect& /*aRect*/) const;

    private:
        CCknParserBanner();
        void ConstructL();
        void OptimisePosition(TRect& aBannerRect, TInt aTextHeight, TRect aBoundary);

        /**
         * Pointer to rich text object that contains tag
         * (not owned)
         */  
        CRichText* iRichText;
        /** 
         * Pointer to the parser for the current tag 
         * (not owned)
         */
        MParser* iParser;
        /**
         * The icon for the current parser type
         */
        const CFbsBitmap* iIcon;
        /**
         * The icon's mask
         */
        const CFbsBitmap* iIconMask;
        /**
         * The start position of the tag that the cursor is on
         */
        TInt iTagStartPos;
        /**
         * The length of the tag that the cursor is on
         */
        TInt iTagLength;
        /**
         * True if the parser banner is active 
         */
        TBool iActive;
        /**
         * True if the parser banner is enabled
         */
        TBool iEnabled;
        /**
         * Stores whether the banner boundary is the screen or the owner's rect
         */
        TParserBannerBounds iBoundaryType;

        TInt iBitmapIndex;
    };

    

#endif  // CKNPARSERBANNER_H

// End of File
