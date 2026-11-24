/*
* ============================================================================
*  Name     : AknPopupNotify.h
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
#ifndef __AKNPOPUPNOTIFY_H__
#define __AKNPOPUPNOTIFY_H__

#include <AknNotify.h>


NONSHARABLE_CLASS(CAknPopupNotify) : public CAknNotifyBase
    {
public:
	IMPORT_C static CAknPopupNotify* NewL();
	IMPORT_C static CAknPopupNotify* NewLC();
	IMPORT_C ~CAknPopupNotify();

	IMPORT_C void PopupMessageL(const TDesC& aMessage);

private:
	CAknPopupNotify();
	void ConstructL();
private:
	IMPORT_C void CAknNotifyBase_Reserved();
    };


#endif
