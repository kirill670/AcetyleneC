/*
* ==============================================================================
*  Name        : eikcapca.h
*  Part of     : CKON
*  Interface   : Label API
*  Description : Array of captioned controls used in a dialog.
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


#ifndef EIKCAPCA_H
#define EIKCAPCA_H

// INCLUDES
#include <e32base.h>
#include <gulutil.h>

// FORWARD DECLARATIONS
class CEikCaptionedControl;
class CCoeControl;

/**
 * The CEikCapCArray is a class to contain an array of CEikCaptionedControls.
 * This is used by pages in dialogs.
 *
 * @internal
 * @lib eikdlg.lib
 * @since Series90 1.0
 */
class CEikCapCArray : public CArrayPtrFlat<CEikCaptionedControl>
    {
    public:

        /**
        * The default C++ constructor.
        */
        IMPORT_C CEikCapCArray(TInt aGranularity);

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikCapCArray();

        /**
        * @return the minimum size of the array of controls
        * <BR><B>Type of return value:</B> TSize
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Sets the display rectangle for the array of controls.
        * @param aRect The rectangle within which to position
        * the controls vertically
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetRect(const TRect& aRect);

        /**
        * Resets the minimum sizes of all the controls in the array.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void ResetMinimumSizes();

        /**
        * Returns the line number of the control that matches the specified ID.
        * @param aControlId The ID of the control to find.
        * @return The line number of the control.
        * <BR><B>Type of return value:</B> TInt
        */
        IMPORT_C TInt LineIndexFromId(TInt aControlId) const;

        /**
        * Returns the line number of the specified control.
        * @param aControl Pointer to the control to find.
        * @return The line number of the control.
        * <BR><B>Type of return value:</B> TInt
        */
        IMPORT_C TInt FindLineIndex(CCoeControl* aControl) const;

        /**
        * Deletes a control from the array.
        * @param aIndex The line index of the control to delete.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void DeleteLine(TInt aIndex);

        /**
        * Adds an offset number to the IDs of all of the controls in the array.
        * @param aControlIdDelta The offset to apply to the control IDs.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void AdjustAllIds(TInt aControlIdDelta);

        /**
        * Deprecated.
        */
        IMPORT_C void SetDensePacking(TBool aDensePacking);

        /**
        * Sets the margins of the caption control array and its controls.
        * @param aMargins The margins to apply to the control array.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetInternalMargins(TMargins8 aMargins);

        /**
        * Set the gap between lines in the array.
        * @param aValue The gap to leave between lines.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetGapBetweenLines(TInt aValue);
        
    public:
        TSize MinimumSize(TBool aForTallestControlOnly);        
        void SetTopMargin(TInt aTopMargin);
        void SetControlWidth(const TInt aWidth);
    private:
        TInt iCaptionWidth;
        TInt iGapBetweenLines;
        TInt iTopMargin;
    };


#endif  // EIKCAPCA_H

// End of File