/*
* ==============================================================================
*  Name        : nsmldssynchronizer.h
*  Part of     : Nokia SyncML / DS Synchronizer
*  Interface   : RNSmlDSSynchronizer
*  Description : DS synchronizer client code.
*  Version     : $Revision: 4 $ $Modtime: 9.06.03 12:48 $
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
	IMPORT_C RNSmlSynchronizer::TResult ConnectL();
	};

#endif // __NSMLDSSYNCHRONIZER_H__
