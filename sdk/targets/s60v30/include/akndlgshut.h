/*
* ============================================================================
*  Name     : AknDlgShut.h
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
// AKNDLGSHUT.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNDLGSHUT_H__)
#define __AKNDLGSHUT_H__

#include <e32std.h>

class CEikonEnv;

class AknDialogShutter
	{
public:
	IMPORT_C static void ShutDialogsL(CEikonEnv& aEikEnv);

private:
	static TInt StartLevel();
	};

#endif
