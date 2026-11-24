/*
* ============================================================================
*  Name        : DownloadMgrClientApiExt.h
*  Part of     : DownloadMgrClntSrv / DownloadMgr
*  Description : API extensions for RHttpDownloadMgr
*  Version     : %version: 1 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/


#ifndef __RHTTPDOWNLOADMGRAPIEXT_H__
#define __RHTTPDOWNLOADMGRAPIEXT_H__


#include "DownloadMgrClient.h"


/**
 *  API Extensions for RHttpDownloadMgr
 *
 *  This class was added to provide support for ProgressiveDownload
 *
 *  
 *  
 */
class RHttpDownloadMgrApiExt : public RHttpDownloadMgr
    {

    public:
        /**
        * C++ default constructor.
        */
        IMPORT_C RHttpDownloadMgrApiExt();

    public:    // New functions

        /**
        * Attach to an existing download.
        * @param aDlId Download ID.
        * @return RHttpDownload&
        */
        IMPORT_C RHttpDownload& AttachToDownloadL( const TInt32 aDlId );

    };



// __RHTTPDOWNLOADMGRAPIEXT_H__
#endif
