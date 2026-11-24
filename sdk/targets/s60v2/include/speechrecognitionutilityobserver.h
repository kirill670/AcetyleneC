// SpeechRecognitionUtilityObserver.h
//
// Copyright (c) 2002-2003 Nokia Corporation. All Rights Reserved.
//

#ifndef __SPEECHRECOGNITIONUTILITYOBSERVER_H__
#define __SPEECHRECOGNITIONUTILITYOBSERVER_H__

//  INCLUDES

#include <mmf\common\SpeechRecognitionDataClient.h>

// CLASS DECLARATION

/**
@publishedAll
@released

This is the main class of Speech Recognition Utility Observer

@since  8.0
*/
class MSpeechRecognitionUtilityObserver
{

public:
	/**
	Pure virtual function that receives speech recognition utility events.

	@param  aEvent
	        The event code indicating the event type.
	@param  aError
			The result code.

	@since  8.0
	*/
	virtual void MsruoEvent( TUid aEvent, TInt aError )=0;

};

#endif	// __SPEECHRECOGNITIONUTILITYOBSERVER_H__

// End of File
