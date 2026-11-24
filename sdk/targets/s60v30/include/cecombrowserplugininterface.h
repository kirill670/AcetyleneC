/*
* ==============================================================================
*  Name        : CEcomBrowserPluginInterface.h
*  Part of     : embed
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright (c)  2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or stranslating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef CECOMBROWSERPLUGININTERFACE_H
#define CECOMBROWSERPLUGININTERFACE_H

// System includes
#include <e32base.h>
#include <ecom/ecom.h>

// User includes
#include "npupp.h"
#include "BrowserPluginInterface.h"

typedef struct
    {
    NPNetscapeFuncs* iNetscapeFuncs;
    NPPluginFuncs* iPluginFuncs;
    }TFuncs;

//
// The ECOM interface definition for a Netscape plugin interface class.
//
class CEcomBrowserPluginInterface: public CBase
	{
	public: 

        inline static CEcomBrowserPluginInterface* CreatePluginL(
                                        TUid aImplementationUid,
                                        NPNetscapeFuncs* aNetscapeFuncs,
                                        NPPluginFuncs* aPluginFuncs);
		
		inline virtual ~CEcomBrowserPluginInterface();
		
  public:

	private:
  //	The ECom destructor key identifier
	TUid iEcomDtorID;

	// A refedrence count
	TInt iCount;

	};

//
//
inline CEcomBrowserPluginInterface* CEcomBrowserPluginInterface::CreatePluginL(
        TUid aImplementationUid,
        NPNetscapeFuncs* aNetscapeFuncs,
        NPPluginFuncs* aPluginFuncs)
	{

	TFuncs initParams;
	initParams.iNetscapeFuncs = aNetscapeFuncs;
	initParams.iPluginFuncs = aPluginFuncs;

	TAny* ptr = REComSession::CreateImplementationL(aImplementationUid, 
									_FOFF(CEcomBrowserPluginInterface, iEcomDtorID),
                                    &initParams);

	return REINTERPRET_CAST(CEcomBrowserPluginInterface*, ptr);
	}

inline CEcomBrowserPluginInterface::~CEcomBrowserPluginInterface()
	{
	REComSession::DestroyedImplementation(iEcomDtorID);
	} 	


#endif // CECOMBROWSERPLUGININTERFACE_H




