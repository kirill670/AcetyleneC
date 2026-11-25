 /*
* ==============================================================================
*  Name        : NSmlDmAdapter.inl
*  Part of     : SyncML DM / Plugin adapters
*  Interface   : SDK, Device Management Adapter API
*  Description : Inline interface methods for Device Management plugin adapters
*  Version     : $Revision: 8 $ $Modtime: 18.08.03 16:34 $
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

const TUint8 KNSmlDmAclAdd = 1;
const TUint8 KNSmlDmAclCopy = 2;
const TUint8 KNSmlDmAclDelete = 4;
const TUint8 KNSmlDmAclExec = 8;
const TUint8 KNSmlDmAclGet = 16;
const TUint8 KNSmlDmAclReplace = 32;

// ------------------------------------------------------------------------------------------------
//  NewL
// ------------------------------------------------------------------------------------------------
inline CNSmlDmAdapter* CNSmlDmAdapter::NewL( const TUid& aImplementationUid, MNSmlDmCallback* aDMCallback )
	{
	TAny* any = REComSession::CreateImplementationL(aImplementationUid, _FOFF(CNSmlDmAdapter, iDtor_ID_Key), aDMCallback);
	CNSmlDmAdapter* object = REINTERPRET_CAST(CNSmlDmAdapter*, any);
	return object;
	}

// ------------------------------------------------------------------------------------------------
// C++ default destructor
// ------------------------------------------------------------------------------------------------
inline CNSmlDmAdapter::~CNSmlDmAdapter()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}

// ------------------------------------------------------------------------------------------------
// C++ default constructor
// ------------------------------------------------------------------------------------------------
inline TNSmlDmAccessTypes::TNSmlDmAccessTypes()
	{
	iACL = 0;
	}

// ------------------------------------------------------------------------------------------------
// TNSmlDmAccessTypes::SetAdd()
// ------------------------------------------------------------------------------------------------
inline void TNSmlDmAccessTypes::SetAdd()
	{
	iACL |= KNSmlDmAclAdd;
	}

// ------------------------------------------------------------------------------------------------
// TNSmlDmAccessTypes::SetCopy()
// ------------------------------------------------------------------------------------------------
inline void TNSmlDmAccessTypes::SetCopy()
	{
	iACL |= KNSmlDmAclCopy;
	}

// ------------------------------------------------------------------------------------------------
// TNSmlDmAccessTypes::SetDelete()
// ------------------------------------------------------------------------------------------------
inline void TNSmlDmAccessTypes::SetDelete()
	{
	iACL |= KNSmlDmAclDelete;
	}

// ------------------------------------------------------------------------------------------------
// TNSmlDmAccessTypes::SetExec()
// ------------------------------------------------------------------------------------------------
inline void TNSmlDmAccessTypes::SetExec()
	{
	iACL |= KNSmlDmAclExec;
	}

// ------------------------------------------------------------------------------------------------
// TNSmlDmAccessTypes::SetGet()
// ------------------------------------------------------------------------------------------------
inline void TNSmlDmAccessTypes::SetGet()
	{
	iACL |= KNSmlDmAclGet;
	}

// ------------------------------------------------------------------------------------------------
// TNSmlDmAccessTypes::SetReplace()
// ------------------------------------------------------------------------------------------------
inline void TNSmlDmAccessTypes::SetReplace()
	{
	iACL |= KNSmlDmAclReplace;
	}


// ------------------------------------------------------------------------------------------------
// TNSmlDmAccessTypes::GetACL()
// ------------------------------------------------------------------------------------------------
TUint8 TNSmlDmAccessTypes::GetACL()
	{
	return iACL;
	}
