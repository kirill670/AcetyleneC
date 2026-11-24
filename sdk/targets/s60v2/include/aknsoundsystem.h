/*
* ============================================================================
*  Name     : AknSoundSystem.h
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
// AKNSOUNDSYSTEM.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// CAknKeySoundSystem - interface for controlling keysounds


#if !defined(__AKNSOUNDSYSTEM_H__)
#define __AKNSOUNDSYSTEM_H__

#include <e32base.h>
#include <w32std.h>
#include <aknSoundInfo.h>

class CAknSoundPlayer;
class CAknKeySoundStack;

class CAknKeySoundSystem : public CBase
	{
public:
	IMPORT_C static CAknKeySoundSystem* NewL(TInt aUid);
	IMPORT_C ~CAknKeySoundSystem();
	IMPORT_C void PushContextL(TInt aResourceId);
	IMPORT_C void PopContext();
	IMPORT_C void PlaySound(const TKeyEvent& aKeyEvent);
	IMPORT_C void PlaySound(TInt aSid);
	IMPORT_C void AddAppSoundInfoListL(TInt aResourceId);
	IMPORT_C void BringToForeground();
    IMPORT_C void StopSound(TInt aSid);
    IMPORT_C void LockContext();
    IMPORT_C void ReleaseContext();
	IMPORT_C TInt RequestSoundInfoL(TInt aSid, CAknSoundInfo& aInfo);

private:
	CAknKeySoundSystem();
	void ConstructL(TInt aUid);
private:
	CAknSoundPlayer* iSoundPlayer;
	TInt iSpare;
	};

#endif
