/*
* ==============================================================================
*  Name        : AknColourSelectionGrid.h
*  Part of     : Avkon
*  Interface   : 
*  Description : 
*      This file defines the CAknColourSelectionGrid class
*  Version     : 
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


#ifndef __AKNCOLOURSELECTIONGRID_H
#define __AKNCOLOURSELECTIONGRID_H

//  INCLUDES
#include <e32base.h>
#include <AknDialog.h>

// FORWARD DECLARATIONS
class CColorGrid;
class CNoneField;
class CAknGrid;

// CLASS DECLARATION

/**
* Colour selection grid
*
* This class can be used when application offers to user 
* possibility to choose colour. There is also possibility to select
* nothing.
*
* use example: 
*
* TBool noneExist = ETrue;
* TBool noneChosen = EFalse;
* TRgb  colour = KRgbDarkGray;
* CArrayFixFlat<TRgb>* colours = new(ELeave) CArrayFixFlat<TRgb>(6);
*
* colours->AppendL(KRgbBlack);
* colours->AppendL(KRgbDarkGray);
* 
*   CAknColourSelectionGrid *d = CAknColourSelectionGrid::NewL(
*                                                 colours, 
*                                                 noneExist, 
*                                                 noneChosen, 
*                                                 colour);
*
*   d->ExecuteLD();
*
*
*  @lib avkon
*  @since 2.0
*/

class CAknColourSelectionGrid : public CAknDialog
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        *
        * NewL() Creates dialog
        *
        * @since 2.0
        *
        * @param aColours array of colors for grid
        *
        * @param aNoneExist boolean flag does none exist in dialog
        *
        * @param aNoneChosen Dialog sets boolean value is none chosen
        * If value is EFalse in start, some colour will be active in start
        *
        * @param aColourChosen Dialog sets the value of color chosen
        * If starting value aNoneChosen is EFalse, starting value of
        * aColours tells witch colour is active when grid starts
        *
        */
        IMPORT_C static CAknColourSelectionGrid* NewL(
                            CArrayFixFlat<TRgb> *aColours,
                            TBool aNoneExist,
                            TBool& aNoneChosen,
                            TRgb& aColourChosen);

        /**
        * ExecuteLD() runs dialog, waits user to make his choise 
        * and destroys dialog
        *
        * @since 2.0
        */
        IMPORT_C TBool ExecuteLD();


    private: // Constructor
        /**
        * C++ default constructor.
        */
        CAknColourSelectionGrid();


    public: // Destructor
        /**
        * Destructor
        */
        IMPORT_C ~CAknColourSelectionGrid();



    private: // New functions
        
        /**
        * Grid() returns control to grid
        *
        * @since 2.0
        * @return Control to grid
        */
        CAknGrid *Grid() const;


    private: // Functions from base classes
        /**
        * From CAknDialog.
        *
        * Handles key events
        *
        * @since 2.0
        * @param aKeyEvent
        * @param aType
        * @return was the key event handled
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) ;
        
        /**
        * From CAknDialog.
        *
        * If ok is pressed, writes values for iColorChosen and iNoneChosen
        *
        * @since 2.0
        * @param aKeycode
        * @return allways ETrue
        */
	    TBool OkToExitL(TInt aKeycode);	
        
        /**
        * From CEikDialog
        * @since 2.0
        */
        void  PreLayoutDynInitL();
        /**
        * From CEikDialog
        * @since 2.0
        */
        void  PostLayoutDynInitL();
        /**
        * From CEikDialog
        * @since 2.0
        * @param aControlType 
        * @return created control
        */
        SEikControlInfo CreateCustomControlL(TInt aControlType);

        /**
        * From CEikDialog
        * @since 2.0
        * @param aSize not in use
        */
        virtual void SetSizeAndPosition(const TSize& aSize);

        /**
        * From CCoeControl
        * @since 2.0
        */
        virtual void ActivateL();


    private: // Data
        CColorGrid* iListBox;
        CNoneField* iNoneBox;
        TInt iIndex;
        CFbsBitmap* iBitmap;
        TBool iNoneExist;
        TBool* iNoneChosen;
        TRgb* iColourChosen;
        CArrayFixFlat<TRgb>* iColours;
        TInt iWsBufferRequestID;

    };

#endif  // __AKNCOLOURSELECTIONGRID_H
