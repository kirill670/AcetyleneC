/*
* ============================================================================
*  Name     : aknmessagequerycontrol.h
*  Part of  : AVKON
*
*  Description:
*  Interface to control to implement message queries, 
*  to be contained within CAknMessageQueryDialog
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
*/

#ifndef AKNMESSAGEQUERYCONTROL_H
#define AKNMESSAGEQUERYCONTROL_H

#include <coecntrl.h>
#include <aknutils.h>

class CEikEdwin;
class CEikScrollBarFrame;
class CEikRichTextEditor;
class CRichText;

class CAknMessageQueryControl : public CCoeControl
    {
public: 
    CAknMessageQueryControl();
    ~CAknMessageQueryControl();
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    IMPORT_C void SetMessageTextL(TDesC* aMessage);

    inline TInt Lines() const;
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);

    //@since 2.8
    void SetMessageTextWithLinkL(TDesC* aMessage, TDesC* aLinkText);
    TBool LinkHighLighted();

public:  // from CCoeControl
    TSize MinimumSize();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt anIndex) const;
    void SizeChanged();
    virtual void ActivateL();

private:
    void CalculateNumberOfScreens();
    void UpdateScrollIndicatorL();

    //@since 2.8
    void SetHightlightOnL(TBool aOn);
    TBool IsLinkVisible() const;
    void SetLinkTextL(const TDesC* alinkText);

private:
    //@since 2.8
    //changed editor from CEikEdwin to CEikRichTextEditor
    //CEikEdwin* iEdwin;
    CEikRichTextEditor* iEdwin;
    TInt iNumberOfLines;
    TInt iCurrentScreen;
    TInt iNumberOfScreens;

    CEikScrollBarFrame* iSBFrame;
    TInt iSpare;   // Not in use.

    //@since 2.8
    TBool iHighlightOn;
    TBool iHLBeforePrevScrollDown;
    TBool iHLBeforePrevScrollUp;
    TCharFormatMask iCharFormatMask;
    TCharFormat iCharFormat;
    HBufC* iLinkText;
    TInt iLinkTextLocation;

protected:
    /**
    * From CCoeControl  Draw a control.  
    *
    * @param aRect      The region of the control to be redrawn.   
    */
IMPORT_C    void Draw(const TRect& aRect) const;


protected:
    /**
    * Layout rectangle (shift up and left by margins)
    */
    TRect LayoutRect();

    };

inline TInt CAknMessageQueryControl::Lines() const
    {
    return iNumberOfLines;
    }

#endif // AKNMESSAGEQUERYCONTROL_H

// End of file
