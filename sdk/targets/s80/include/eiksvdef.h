/*
* ==============================================================================
*  Name        : eiksvdef.h
*  Part of     : UIKON
*  Interface   : Application server API
*  Description : Misc. Definitions
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


#ifndef EIKSVDEF_H
#define EIKSVDEF_H

/**
@publishedPartner
@released
*/
// CONSTANTS
const TInt KExternalKeyModifier=0;
const TInt KExternalKey1=EKeyDictaphoneStop;
const TInt KExternalKey2=EKeyDictaphonePlay;
const TInt KExternalKey3=EKeyDictaphoneRecord;
const TInt KExternalKeyModifierMask=EAllStdModifiers|EModifierFunc;

/**
@publishedPartner
@released
*/
const TUid KUidExternalKeyHandlerAppStream={0x10000117};

/**
@publishedPartner
@deprecated
*/
const TUid KUidDictaphoneFileStream={0x100001CF};

/**
@internalComponent
*/
_LIT(__EIKON_SERVER_NAME,"EikonServer");

/**
@publishedPartner
@released
*/
enum TEikServEvent
	{
	EEikServExit,
	EEikServChangePasswordMode,
	EEikServShowTaskList
	};

/**
@publishedPartner
@released
*/
const TInt KNumOfSideButtons=5;
const TInt KNumOfAppButtons=9;

/**
@publishedPartner
@released
*/
_LIT(EIKON_SERVER_BACKDROP_WINDOW_GROUP_NAME,"EiksrvBackdrop");


#endif	// EIKSVDEF_H

// End of File
