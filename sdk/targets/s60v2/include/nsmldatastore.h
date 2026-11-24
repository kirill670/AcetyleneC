/*
* ==============================================================================
*  Name        : nsmldatastore.h
*  Part of     : SyncML DS / Datastore
*  Interface   : SDK, Data Synchronisation Adapter API
*  Description : Datastore interface for Data Synchronisation plugin adapters
*  Version     : $Revision: 3 $ $Modtime: 18.08.03 18:24 $
*
*  Copyright © 2002 Nokia Corporation.
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

#ifndef __NSMLDATASTORE_H__
#define __NSMLDATASTORE_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32std.h>
#include <e32base.h>
#include <d32dbms.h>
#include <f32file.h>
#include <s32file.h>
#include <utf.h>

//=============================================
//		MNSmlDataStore
//=============================================
class MNSmlDataStore
	{
public:

	/**
    * Opens a specified stream for reading.
    * @param aUid Stream to be opened.
    * @return MStreamBuf* Stream buffer for the read stream.
    */
	virtual MStreamBuf* OpenReadStreamL( TUid aUid ) = 0;

	/**
    * Opens a specified stream for writing.
    * @param aUid Stream to be opened.
    * @return MStreamBuf* Stream buffer for the write stream.
    */
	virtual MStreamBuf* OpenWriteStreamL( TUid aUid ) = 0;

	/**
    * Tests if specified stream is present in the store.
    * @param aUid Stream to be tested.
    * @return TBool ETrue if stream exists, otherwise EFalse.
    */
	virtual TBool IsPresentL( TUid aUid ) = 0;

	/**
    * Deletes the specified stream from the store.
    * @param aUid Stream to be deleted.
    */
	virtual void DeleteStreamL( TUid aUid ) = 0;

	/**
    * Deletes the store.
    */
	virtual void DeleteStoreL() = 0;

	/**
    * Closes the write stream.
    * @param aCommit If ETrue, commits all changes to store, else discards changes. 
    */
	virtual void CloseWriteStreamL( TBool aCommit = ETrue ) = 0;

	/**
    * Closes the read stream.
    */
	virtual void CloseReadStreamL() = 0;
	};

#endif // __NSMLDATASTORE_H__
