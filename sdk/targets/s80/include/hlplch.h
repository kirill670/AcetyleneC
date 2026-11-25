/*
* ==============================================================================
*  Name        : HlpLch.h
*  Part of     : Help model
*  Interface   :
*  Description : Help Launch support definitions
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
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

#ifndef __HLPLCH_H__
#define __HLPLCH_H__

#include <apgtask.h>
#include <eikdll.h>
#include <w32std.h>
#include <coehelp.h>

const TUid KHlpAppUid={ 0x10005234 };
const TUid KHlpAppWsMsg={ 0x100055c7 };
const TInt KMaxCmdLineLength = 512;

_LIT(KHlpAppPath, "z:\\System\\Apps\\CsHelp\\CsHelp.app");

class CHlpCmdLine : public CBase
	{
public:
	static CHlpCmdLine* NewL(CArrayFix<TCoeHelpContext>* aContextList);
	static CHlpCmdLine* NewLC(CArrayFix<TCoeHelpContext>* aContextList);
	~CHlpCmdLine();
public:
	TPtr8 CmdLineL();
private:
	void BuildCmdLineL();
	void AddContextL(TCoeHelpContext& aContext);
private:
	void ConstructL();
	CHlpCmdLine(CArrayFix<TCoeHelpContext>* aContextList);
private:
	CArrayFix<TCoeHelpContext>* iContextList;
	CBufFlat* iCmdLine;
	};

class HlpLauncher
	{
public:
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession, CArrayFix<TCoeHelpContext>* aContextList);
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession, TUid aUid);
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession);
private:
	static void DoLaunchHelpApplicationL(RWsSession& aWsSession, const TDesC8& aCmdLine);
	};

#endif