// APASVST.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2004. All rights reserved.
//

//
// Starting of AppArc server
//

#ifndef __APASVST_H__
#define __APASCST_H__

#include <e32std.h>

// classes referenced
class MApaAppStarter;

#if defined(__WINS__) && !defined(EKA2)
# define APA_SERVER_IN_THREAD
#endif

IMPORT_C TPtrC NameApaServStartSemaphore();

IMPORT_C TPtrC NameApaServServerThread();

IMPORT_C TInt StartupApaServer(MApaAppStarter& aAppStarter);

IMPORT_C TInt StartupApaServerProcess();

IMPORT_C TInt ApaServThreadStart(TAny* aAppStarter);


#endif
