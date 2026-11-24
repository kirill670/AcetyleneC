/*
* ============================================================================
*  Name     : AknNotify.h
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
#ifndef __AKNNOTIFY_H__
#define __AKNNOTIFY_H__

#include <e32base.h>


class CAknNotifyBase : public CBase
    {
public:
	IMPORT_C ~CAknNotifyBase();

protected:
	CAknNotifyBase(TUid aUid);
	void ConstructL();
	void StartOrUpdateL(const TDesC8& aBuffer,TDes8& aResponse);
	void StartOrUpdateAndGetResponseL(TRequestStatus& aStatus,const TDesC8& aBuffer,TDes8& aResponse);
private:
	IMPORT_C void CAknNotifyBase_Reserved();

private:
	TUid iUid;
	TBool iStarted;
	RNotifier iNotify;
	TInt iSpare;
    };


#endif
