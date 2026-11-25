// APASVST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Starting of AppArc server
//

#if !defined(__APASVST_H__)
#define __APASCST_H__
#include <e32def.h>

// classes referenced

class MApaAppStarter;

/**
NameApaServStartSemaphore

@internalTechnology
*/
IMPORT_C TPtrC NameApaServStartSemaphore();

/**
NameApaServServerThread

@internalTechnology 
*/
IMPORT_C TPtrC NameApaServServerThread();

/**
StartupApaServer

@internalTechnology 
*/
IMPORT_C TInt StartupApaServer(MApaAppStarter& aAppStarter);

#endif
