/*
* ==============================================================================
*  Name        : BrCtlBrCtlSpecialLoadObserver.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle special load events such as network connection, deal with non-http or non-html requests
*  Version     : %Version%
*
*  Copyright (c) 2004 Nokia Corporation.
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


#ifndef BRCTLSPECIALLOADOBSERVER_H
#define BRCTLSPECIALLOADOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <apmstd.h> 
#include <ApEngineConsts.h>
#include <badesca.h>

// CONSTANTS

// MACROS

// DATA TYPES
enum TBrCtlDownloadParam
    {
    EParamRequestUrl,
    EParamRealm,
    EParamUsername,
    EParamPassword,
    EParamProxyRealm,
    EParamProxyUsername,
    EParamProxyPassword,
    EParamRawRequestHeader,
    EParamReceivedContentType,
    EParamExpectedContentType,
    EParamTotalContentLength,
    EParamReceivedContentLength,
    EParamReceivedContent,
    EParamRawResponseHeader,
    EParamLocalFileName,
    EParamCharset,
    EParamRefererHeader
    };

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
*  This observer handles special load events such as network connection, deal with non-http(s) or non-html requests. 
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlSpecialLoadObserver
    {
    public: // New functions
        /**
        * Request to create a network connection.
        * @since 2.8
        * @param aConnectionPtr A pointer to the new connection. If NULL, the proxy filter will automatically create a network connection
        * @param aSockSvrHandle A handle to the socket server.
        * @param aNewConn A flag if a new connection was created. If the connection is not new, proxy filter optimization will not read the proxy again from CommsBd
        * @param aBearerType The bearer type of the new connection
        * @return void
        */
        virtual void NetworkConnectionNeededL(TInt* aConnectionPtr,
                                              TInt* aSockSvrHandle,
                                              TBool* aNewConn,
                                              TApBearerType* aBearerType) = 0;

        /**
        * Request the host applicaion to handle non-http request.
        * @since 2.8
        * @param aTypeArray -- an array of download parameter types
        * @param aDesArray -- an array of values associated with the types in the type array
        * @return ETrue is handled by the host application. EFlase if not
        */
        virtual TBool HandleRequestL(RArray<TUint>* aTypeArray, CDesCArrayFlat* aDesArray) = 0;

        /**
        * Request the host applicaion to handle downloads
        * @since 2.8
        * @param aTypeArray array of download parameter types
        * @param aDesArray array of values associated with the types in the type array
        * @return ETrue is handled by the host application. EFlase if not
        */
        virtual TBool HandleDownloadL(RArray<TUint>* aTypeArray, CDesCArrayFlat* aDesArray) = 0;

    };

#endif      // BRCTLSPECIALLOADOBSERVER_H
            
// End of File
