/*
* ==============================================================================
*  Name        : nsmldsadapter.inl
*  Part of     : SyncML DS / Plugin adapters
*  Interface   : SDK, Data Synchronisation Adapter API
*  Description : Inline interface methods for Data Synchronisation plugin adapters
*  Version     : $Revision: 5 $ $Modtime: 18.08.03 16:31 $
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

#include <ECom.h>

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------
inline CNSmlDSAdapter* CNSmlDSAdapter::NewL( const TUid& aImplementationUid, MNSmlDataStore* aDataStore )
	{
	TAny* any = REComSession::CreateImplementationL(aImplementationUid, _FOFF(CNSmlDSAdapter, iDtor_ID_Key), aDataStore);
	CNSmlDSAdapter* object = REINTERPRET_CAST(CNSmlDSAdapter*, any);
	return object;
	}

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------
inline CNSmlDSAdapter::~CNSmlDSAdapter()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}
