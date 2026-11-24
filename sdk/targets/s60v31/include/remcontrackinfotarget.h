// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll
@released
*/

#ifndef REMCONTRACKINFOTARGET_H
#define REMCONTRACKINFOTARGET_H

#include <e32base.h>
#include <remcon\remconinterfacebase.h>
#include <remcon\remconinterfaceif.h>

class MRemConTrackInfoTargetObserver;
class CRemConInterfaceSelector;

/**
Client-instantiable type supporting sending TrackInfo API responses.
*/
NONSHARABLE_CLASS(CRemConTrackInfoTarget) : public CRemConInterfaceBase, 
								            public MRemConInterfaceIf
	{
public:
	/**
	Factory function.
	@param aInterfaceSelector The interface selector. The client must have 
	created one of these first.
	@param aObserver The observer of this interface.
	@return A new CRemConTrackInfoTarget, owned by the interface selector.
	*/
	IMPORT_C static CRemConTrackInfoTarget* NewL(CRemConInterfaceSelector& aInterfaceSelector, 
		MRemConTrackInfoTargetObserver& aObserver);
	
	/** Destructor. */
	IMPORT_C ~CRemConTrackInfoTarget();

public:
	/**
	Sends a response to a 'get track name' command.
	@param aStatus Used by RemCon to indicate completion of the send request.
	@param aTrackName The track name.
	@param aError The response error.
	@panic USER 23, if the length of aTrackName is greater than 58 Characters. 
	*/
	IMPORT_C void GetTrackNameResponse(TRequestStatus& aStatus, 
		const TDesC& aTrackName, 
		TInt aError);

	/**
	Sends a response to a 'get artist' command.
	@param aStatus Used by RemCon to indicate completion of the send request.
	@param aArtist The artist.
	@param aError The response error.
	@panic USER 23, if the length of aArtist is greater than 58 Characters. 
	*/
	IMPORT_C void GetArtistResponse(TRequestStatus& aStatus, 
		const TDesC& aArtist, 
		TInt aError);

	/**
	Sends a response to a 'get track duration' command.
	@param aStatus Used by RemCon to indicate completion of the send request.
	@param aDuration The duration.
	@param aError The response error.
	*/
	IMPORT_C void GetTrackDurationResponse(TRequestStatus& aStatus, 
		const TTime& aDuration, 
		TInt aError);

private:
	/** 
	Constructor.
	@param aInterfaceSelector The interface selector.
	@param aObserver The observer of this interface.
	*/
	CRemConTrackInfoTarget(CRemConInterfaceSelector& aInterfaceSelector, 
		MRemConTrackInfoTargetObserver& aObserver);

private: // from CRemConInterfaceBase
	TAny* GetInterfaceIf(TUid aUid);

private: // from MRemConInterfaceIf
	void MrcibNewMessage(TUint aOperationId, const TDesC8& aData);

private: // unowned
	MRemConTrackInfoTargetObserver& iObserver;

private: // owned
	// For operation-specific data.
	TBuf8<KMaxName> iOutData;
	
	// not used by this class, but required for calling RRemCon::Send ...
	TUint iNumRemotes;

	};

// REMCONTRACKINFOTARGET_H
#endif
