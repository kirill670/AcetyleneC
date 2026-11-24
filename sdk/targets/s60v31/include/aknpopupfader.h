/*
* ============================================================================
*  Name     : AknPopupFader.h
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
// AknPopupFader.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNPOPUPFADER_H__)
#define __AKNPOPUPFADER_H__

#include <e32base.h>

class CCoeControl;


class MAknFadedComponent
	{
public:
	IMPORT_C virtual TInt CountFadedComponents();
	IMPORT_C virtual CCoeControl* FadedComponent(TInt aIndex);
	};

class TAknPopupFader
	{
public:
	IMPORT_C void FadeBehindPopup(MAknFadedComponent* aComponent, CCoeControl* aParent, TBool aFade);

public:	// internal
	static void CreateStaticL();

private:
	void FadeBehindPopupL(MAknFadedComponent* aComponent, CCoeControl* aParent, TBool aFade);

private:
	TBool iBackgroundFaded; // unused
	};


#endif
