// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll
@released
*/

#ifndef REMCONTRACKINFOTARGETOBSERVER_H
#define REMCONTRACKINFOTARGETOBSERVER_H

#include <e32base.h>

/**
Client-implemented mixin- notifies the client of incoming TrackInfo commands.
*/
class MRemConTrackInfoTargetObserver
	{
public:
	/**
	A 'get track name' command has been received.
	*/
	virtual void MrctitoGetTrackName();

	/**
	A 'get artist' command has been received.
	*/
	virtual void MrctitoGetArtist();

	/**
	A 'get track duration' command has been received. 
	*/
	virtual void MrctitoGetTrackDuration();
	};

// REMCONTRACKINFOTARGETOBSERVER_H
#endif
