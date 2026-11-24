 /*
* ==============================================================================
*  Name        : nsmldssynchronizer.h
*  Part of     : Nokia SyncML / DS Synchronizer
*  Interface   : RNSmlDSSynchronizer
*  Description : DS synchronizer client code.
*  Version     : $Revision: 12 $ $Modtime: 29.06.04 14:12 $
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

#ifndef __NSMLDSSYNCHRONIZER_H__
#define __NSMLDSSYNCHRONIZER_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>
#include <nsmlsynchronizer.h>
#include <nsmldbcaps.h>

struct TNSmlContentSpecificSyncType
	{
	TInt iImplUid;
	CNSmlDbCaps::ENSmlSyncTypes iType;
	};

// ------------------------------------------------------------------------------------------------
// class RNSmlDSSynchronizer
// ------------------------------------------------------------------------------------------------
class RNSmlDSSynchronizer : public RNSmlSynchronizer
	{
public:
	/**
	* Connects to synchronizer server. If server cannot be found launches remote synchronizatio application.
	* return RNSmlSynchronizer::TResult Results of connect.
	*/
	IMPORT_C virtual RNSmlSynchronizer::TResult ConnectL();

    /**
    * Starts synchronization with content override.
    * @param aProfileId Id of a profile to be synchronized.
    * @param aSyncTypeArray Array of TNSmlContentSpecificSyncType items which includes implementation UID 
    *   of the content and type of the synchronization.
	* @return RNSmlSynchronizer::TResult - result of the operation
    */
    IMPORT_C virtual RNSmlSynchronizer::TResult SynchronizeCtL( TInt aProfileId, CArrayFix<TNSmlContentSpecificSyncType>* aSyncTypeArray );
    };

#endif // __NSMLDSSYNCHRONIZER_H__