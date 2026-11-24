// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll
@released
*/

#ifndef REMCONTRACKINFOCONTROLLEROBSERVER_H
#define REMCONTRACKINFOCONTROLLEROBSERVER_H

#include <e32base.h>

/**
Client-implemented mixin- notifies the client of incoming TrackInfo responses.
*/
class MRemConTrackInfoControllerObserver
	{
public:
	/**
	A response to a 'set track name' command has been received.
	@param aError The response error.
	*/
	virtual void MrcticoSetTrackNameResponse(TInt aError);
	};

#endif // REMCONTRACKINFOCONTROLLEROBSERVER_H
