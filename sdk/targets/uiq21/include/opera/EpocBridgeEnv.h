/** -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
  *
  * Copyright (C) 2002 Opera Software AS.  All rights reserved.
  *
  * This file is part of the Opera web browser.  It may not be distributed
  * under any circumstances.
  *
  * @file EpocBridgeEnv.h  
  *
  * Contains the definition of the CEpocBridgeEnv class.
  *
  * @author Keith Hollis
  */

#ifndef __EPOCBRIDGEENV_H
#define __EPOCBRIDGEENV_H

#include <e32base.h>

#ifdef SOCKETACCOUNTING
class TInstanceNumber
    {
public:
    inline TInstanceNumber(const TDesC& aType) : iType(aType) {}; /* aType is not working */
    TInt NewInstance();
    void RemoveInstance();
private:    
    TInt iInstanceNumber;
    TInt iNumberOfSockets;
    TPtrC iType;
    };
#endif

class RFile;
class CErrResolver;
class CEpocBridgeFactory;
class CSecureKeepAlive;
class CEpocNetworkMonitor;
class MpNetworkMonitor;

class MEpocBridgeAdapter
    {
public:
    virtual void ReportErrorL(TInt aError)=0;
    };

class CEpocBridgeEnv : public CBase
    {
public:
    IMPORT_C static CEpocBridgeEnv* NewL(MEpocBridgeAdapter* aAdapter);
    IMPORT_C ~CEpocBridgeEnv();
public: // new
    IMPORT_C static CEpocBridgeEnv* CEpocBridgeEnv::Static();
    IMPORT_C CEpocBridgeFactory* SocketFactoryL();
    /**
      * Report error code.
      */
    IMPORT_C void ReportErrorL(TInt aError);
    /**
    * General logging of text
    */
    static void Log(const TDesC8& des);
    static void Log(const TDesC16& des);
    static TInt LogIndent();
    static void IncLogIndent();
    static void DecLogIndent();
    /*
    * NetworkMonitor
    */
    IMPORT_C MpNetworkMonitor* NetworkMonitor();
private: // new
    CEpocBridgeEnv(MEpocBridgeAdapter* aAdapter);
    void ConstructL();
    void DoLog(const TDesC8& des);
    void DoLog(const TDesC16& des);
    void OpenLogFileL();
    void CloseLogFile();
private:
    MEpocBridgeAdapter* iAdapter;
    CEpocBridgeFactory* iSocketFactory;
#ifdef ER6
    CErrResolver* iErrorResolver;
#endif
    RFile* iLogFile;
    TInt iLogIndent;
#if defined(_SSL_SUPPORT_) && defined(_EXTERNAL_SSL_SUPPORT_)
	CSecureKeepAlive* iSecureKeepAlive; // A persistent instance of a CSecureSocket keep the SSL session alive
#endif // _SSL_SUPPORT_ && _EXTERNAL_SSL_SUPPORT_
    CEpocNetworkMonitor* iEpocNetworkMonitor;
public:
#ifdef SOCKETACCOUNTING
    TInstanceNumber iSocketInstance;
    TBuf<256> iTempBuff;  // This is instead of static member data by CEpocSocket
#endif
    };

#endif // __EPOCBRIDGEENV_H
