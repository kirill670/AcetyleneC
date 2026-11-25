/*
* ==============================================================================
*  Name        : eikthumb.h
*  Part of     : CKON
*  Interface   : Scroll bar API
*  Description : Scroll bar thumb.
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

#ifndef EIKTHUMB_H
#define EIKTHUMB_H


// INCLUDES

#include <eikbctrl.h>
#include <lafpublc.h>

// FORWARD DECLARATIONS
class MEikScrollBarCustomDrawBase;

// CLASS DECLARATIONS

/**
* A scroll thumb.
*
* @lib eikcoctl.lib
* @internal
* @since 6.0
*/
class CEikScrollThumb : public CEikBorderedControl
    {

public:  // Declarations
        
    /**
    * Specifes the orientation of a scroll thumb.
    */
    enum TOrientation 
        {
        /** sets the orientation to vertical */
        EVertical = SLafScrollThumb::EVertical,
        /** sets the orientation to horizontal */
        EHorizontal = SLafScrollThumb::EHorizontal
        };

public:

    // Constructors and destructor

    CEikScrollThumb(TOrientation aOrientation);
    void SetDragState(TBool aState);
    TBool DragState();
    void DrawDragStateNow() const;
    
    void SetCustomDrawer(MEikScrollBarCustomDrawBase* aCustomDrawer);

    // Methods from base classes
    
    // from CCoeControl
    void Draw(const TRect& aRect) const;
    void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
    void HandleResourceChange(TInt aType);

protected:  // Methods

    // Methods from base classes
    
    //from CCoeControl
    void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: //Methods

    void DrawDragState(CWindowGc& aGc) const;

private:     // Data

    TBool iDragState;
    TOrientation iOrientation;
    MEikScrollBarCustomDrawBase* iCustomDrawer;

    };

#endif      // EIKTHUMB_H   
            
// End of File