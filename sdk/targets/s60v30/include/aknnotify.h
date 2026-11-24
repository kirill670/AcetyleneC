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

// INCLUDES

#include <e32base.h>

// CLASS DECLARATION

/**
*  Base class for handling @c RNotifier.
*
*  @since Series 60 0.9
*/
NONSHARABLE_CLASS(CAknNotifyBase) : public CBase
    {
public:
	
	/**
    * Destructor.
    */
	IMPORT_C ~CAknNotifyBase();

protected:
	
	/**
    * C++ constructor.
    * @param aUid The UID identifying the plug-in notifier.
    */
	CAknNotifyBase(TUid aUid);
	
	/**
	* 2nd phase constructor.
	* Connects to the notifier server.
	*/
	void ConstructL();
	
	/**
    * Starts or updates the notifier.
    * @param aBuffer Data that can be passed to notifier.
    * @param aResponse Data that can be returned by notifier.
    */
	void StartOrUpdateL(const TDesC8& aBuffer,TDes8& aResponse);
	
	/**
    * Starts the notifier.
    * @param aStatus The request status.
    * @param aBuffer Data that can be passed to the notifier.
    * @param aResponse Data that can be returned by the notifier.
    */
	void StartOrUpdateAndGetResponseL(TRequestStatus& aStatus,
	                                  const TDesC8& aBuffer,
	                                  TDes8& aResponse);
private:
	IMPORT_C void CAknNotifyBase_Reserved();

private:
	TUid iUid;
	TBool iStarted;
	RNotifier iNotify;
	TInt iSpare;
    };


#endif
