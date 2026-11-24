/*
* ============================================================================
*  Name     : AknStaticNoteDialog.h
*  Part of  : Avkon
*
*  Description:
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

#ifndef __AKNSTATICNOTEDIALOG__
#define __AKNSTATICNOTEDIALOG__

#include <aknnotedialog.h>
#include <AknControl.h>

class CEikImage;
class CAknStackIndicatorAttributes;

class CAknStaticNoteStackIndicator : public CAknControl
	{
public:
	void ConstructL(CCoeControl* aParentNote, TInt aStackDepth);
	void UpdateDepth(TInt aDepth);
	~CAknStaticNoteStackIndicator();
	// From Coe
	IMPORT_C void HandleResourceChange(TInt aType);
    //From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	void Draw(const TRect& aRect) const;
	void DoSetExtent();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
	CAknStackIndicatorAttributes* iAttributes;
	CCoeControl* iParentNote;
	};


/**
 * Static note dialog
 */
class CAknStaticNoteDialog : public CAknNoteDialog
	{
public:
	IMPORT_C CAknStaticNoteDialog();
	IMPORT_C CAknStaticNoteDialog(CEikDialog** aSelfPtr);
	IMPORT_C virtual ~CAknStaticNoteDialog();

    IMPORT_C void SetNumberOfBorders(TInt aNumber);

    // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

protected:
	IMPORT_C void PostLayoutDynInitL();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

protected:
	CAknStaticNoteStackIndicator* iStackIndicator;
	TInt iStackDepth;
private:
	TInt iSpare;
	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknNoteDialog_Reserved();
private: // new virtual function.
	IMPORT_C virtual void CAknStaticNoteDialog_Reserved();
	};

#endif
