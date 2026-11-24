/*
* ============================================================================
*  Name     : AknApp.h
*  Part of  : Avkon
*
*  Description:
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
* ============================================================================
*/
#ifndef __AKNAPP_H__
#define __AKNAPP_H__

#include <eikapp.h>

class CAknApplication : public CEikApplication
	{
public:
	// from CApaApplication
	IMPORT_C virtual void PreDocConstructL();
	IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
	IMPORT_C void NewAppServerL(CApaAppServer*& aAppServer);
	};

#endif

