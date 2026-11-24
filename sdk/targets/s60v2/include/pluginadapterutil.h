/*
* ==============================================================================
*  Name        : PluginAdapterUtil.h
*  Part of     :  / Browser Plugin API
*  Interface   : Browser Plugin API, CPluginAdapterUtil
*  Description : Series 60, Series 80 Platforms and the Nokia 7710 smartphone compatible layer
*  Version     : 1.01
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef CPLUGINADAPTERUTIL_H
#define CPLUGINADAPTERUTIL_H

//  INCLUDES
#include "PluginAdapterInterface.h"

// DATA TYPES
typedef MPluginAdapter *MPluginAdapterPTR;
typedef CCoeControl *CCoeControlPTR;

// CLASS DECLARATION

/**
*  All plugins need to extract the platform dependent window from the NPWindow structure
*  while processing the Netscape API’s NPP_SetWindow call.
*  Like this:
*
*     //NPError NPP_SetWindow(NPP instance, NPWindow* window) {
*     //	CPluginAdapterUtil::ExtractParentControlAndApiL(window,iAdaptor,iParentControl);
*     //	etc...
*     //
*
*
*  @lib PluginAdapterUtil
*  @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
*/
class CPluginAdapterUtil
    {
    public: // New functions
        
        /**
        * Extract the platform dependent window from the NPWindow structure
        * while processing the Netscape API’s NPP_SetWindow call.
        * @since Series 60 2nd Edition, Feature Pack 2 and Series 80 Platforms and the Nokia 7710 smartphone
        * @param aWindow Window pointer (NPWindow *)
        * @param aPluginAdapter The object to communicate with the browser for additional functionality
        * @param aCoeControl The Parent control
        * @return in parameters aPluginAdapter & aCoeControl
        */
IMPORT_C static void ExtractParentControlAndApiL(
//IN
                                           const NPWindow* aWindow,
//out
                                           MPluginAdapterPTR &aPluginAdapter,
                                           CCoeControlPTR &aCoeControl
								  );        

    };


#endif      // CPLUGINADAPTERUTIL_H
            
// End of File