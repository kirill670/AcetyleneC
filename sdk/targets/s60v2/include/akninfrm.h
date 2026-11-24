/*
* ============================================================================
*  Name     : AknInfrm.h
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
// Akninfrm.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __AKNINFRM_H__
#define __AKNINFRM_H__


#include <eikdef.h>
#include <eikbctrl.h>
#include <gulicon.h>
#include <eiklabel.h>
#include <aknutils.h>
#include <avkon.rsg>

class CAknInputFrameExtension;
class CAknsFrameBackgroundControlContext;

/**
 * The CAknInputFrame class 
 *
 * implements an input frame which can contain any CCoeControl. The input frame can have 
 * additional icon and/or info text.
 *
 */
class CAknInputFrame : public CEikBorderedControl, public MCoeControlObserver
	{
public:
	CAknInputFrame();
	IMPORT_C ~CAknInputFrame();
	
	IMPORT_C static CAknInputFrame* NewL(CCoeControl* aField,TBool aComponentOwner,
				   const TDesC& aBitmapfile, TInt aBitmapId, TInt aMaskId,
				   TUint32 aFlags = 0 );
	IMPORT_C static CAknInputFrame* NewL(CCoeControl* aField,TBool aComponentOwner,
				   CGulIcon* aIcon, TUint32 aFlags = 0 );
	IMPORT_C CCoeControl* Field() const;
	IMPORT_C void SetInfoTextL(const TDesC& aText);
	IMPORT_C void SetLineState(TBool aLineVisible);
	void SetIcon(CGulIcon* aIcon);
public: //from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public: //from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader); 
	IMPORT_C void SetInputContext(CAknsFrameBackgroundControlContext* aContext);


private: // From CCoeControl
	void SizeChanged();
	void FocusChanged(TDrawNow aDrawNow); 
	void Draw(const TRect& aRect) const;
	void PrepareForFocusLossL();
private:
	TMargins Borders() const;
	void BaseConstructL(CCoeControl* aField, TBool aOwner, TUint32 aFlags);
	void ConstructL(CCoeControl* aField, TBool aOwner, const TDesC& aFileName, TInt aBitmapId, TInt aMaskId, TUint32 aFlags);
	void ConstructL(CCoeControl* aField, TBool aOwner, CGulIcon* aIcon, TUint32 aFlags);
	TRect InnerRect() const;
	TSize InfoAreaSize() const;
public:
	enum TInputFrameFlags
		{
		EOwnsField=0x40,
		EPopupLayout=0x80,
		EPinbLayout=0x100,
		EClockAppLayout=0x200,
		EFixedFindWithoutLine   = 0x400,
        EShowIndicators         = 0x800,
		EPopupWindowLayout=0x1000
		};
private:
	CAknInputFrameExtension *iExtension;
	CGulIcon* iIcon;
	CEikLabel* iInfoText;
	TUint32 iFlags;
	TAknLayoutRect iVertShadow, iHoriShadow, iOutlineRect, iMagnIconPos;
	// next ones are only used with popup style
	TAknLayoutRect iCoverRect, iSecondShadow, iFirstShadow, iOutlineFrame, iInsideArea;
	};


#endif



