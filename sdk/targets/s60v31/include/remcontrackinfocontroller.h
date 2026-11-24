// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll
@released
*/

#ifndef REMCONTRACKINFOCONTROLLER_H
#define REMCONTRACKINFOCONTROLLER_H

#include <e32base.h>
#include <remcon\remconinterfacebase.h>
#include <remcon\remconinterfaceif.h>

class MRemConTrackInfoControllerObserver;
class CRemConInterfaceSelector;

/**
Client-instantiable type supporting sending TrackInfo API commands.
*/
NONSHARABLE_CLASS(CRemConTrackInfoController) : public CRemConInterfaceBase, 
								       	        public MRemConInterfaceIf
	{
public:
	/**
	Factory function.
	@param aInterfaceSelector The interface selector. The client must have 
	created one of these first.
	@param aObserver The observer of this interface.
	@return A new CRemConTrackInfoController, owned by the interface selector.
	*/
	IMPORT_C static CRemConTrackInfoController* NewL(CRemConInterfaceSelector& aInterfaceSelector, 
		MRemConTrackInfoControllerObserver& aObserver);
	
	/** Destructor. */
	IMPORT_C ~CRemConTrackInfoController();

public:
	/** 
	Sends a 'set track name' command.
	@param aStatus Used by RemCon to indicate completion of the send request.
	@param aTrackName The track name.
	@panic USER 23, if the length of aTrackName is greater than 58 Characters.
	*/
	IMPORT_C void SetTrackName(TRequestStatus& aStatus, const TDesC& aTrackName, TUint& aNumRemotes);

private:
	/** 
	Constructor.
	@param aInterfaceSelector The interface selector.
	@param aObserver The observer of this interface.
	*/
	CRemConTrackInfoController(CRemConInterfaceSelector& aInterfaceSelector, 
		MRemConTrackInfoControllerObserver& aObserver);

private: // from CRemConInterfaceBase
	TAny* GetInterfaceIf(TUid aUid);

private: // from MRemConInterfaceIf
	void MrcibNewMessage(TUint aOperationId, const TDesC8& aData);

private: // unowned
	MRemConTrackInfoControllerObserver& iObserver;

private: // owned
	TBuf8<KMaxName> iOutData;
	};

// REMCONTRACKINFOCONTROLLER_H
#endif
