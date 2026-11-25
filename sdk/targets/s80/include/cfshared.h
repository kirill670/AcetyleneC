// cfshared.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __CFSHARED_H__
#define __CFSHARED_H__

#include <es_mbman.h>

namespace CommsFW 
/** Namespace for the Comms Framework
@publishedPartner 
@released
*/
{

/** Maximum length of a module name.
@publishedPartner 
@released
*/
const TInt KCFMaxModuleName = 0x20;

/** Maximum length of a submodule name.
@publishedPartner 
@released
*/
const TInt KCFMaxSubModuleName = 0x20;

/** Maximum number of queues i the channels used for the Comms Framework.
This is not a restriction imposed on private/custom channels created by
the modules.
@publishedPartner 
@released
*/
const TInt KCFMaxChannelQueues = 1; 

/** Name of a Comms Provider Module.
@publishedPartner 
@released
*/
typedef TBuf8<KCFMaxModuleName> TCFModuleName;

/** Name of a Sub-module in a Comms Provider Module
@publishedPartner 
@released
*/
typedef TBuf8<KCFMaxSubModuleName> TCFSubModuleName;

/** Name of a Comms Provider Module and an associated sub-module 
in the form "module name:submodule name"
@publishedPartner 
@released
*/
typedef TBuf8<KCFMaxModuleName + KCFMaxSubModuleName + 1> TCFFullModuleName;

/** Type of shutdown message
@publishedPartner 
@released
*/
enum TCFShutdownType
	{
	/** Shutdown is requested but is not mandatory.
	*/
	EOptional,
	/** Shutdown is requested. It should be done in as graceful a way as possible.
	E.g. if a server it could be deferred to such time when no client are
	connected or connected clients could be cancelled in a controlled manner.
	*/
	EGraceful,
	/** Immediate shutdown is requested. Graceful shutdown is preferred where possible
	but not if it would not be immediate.
	*/
	EUnGraceful
	};

/** Comms Framework PANIC
*/
_LIT(KCFSharedPanic, "CommsFW");

#if defined _DEBUG
#define __DEBUG_STMT(a) a
#else
#define __DEBUG_STMT(a)
#endif

class TCFSubModuleAddress
/** Used to uniquely identify a specific submodule (e.g. protocol) within a 
module (e.g. a CPM).
@publishedPartner 
@released
*/
	{
public:
	IMPORT_C TCFSubModuleAddress();
	IMPORT_C TCFSubModuleAddress(const TCFSubModuleAddress& aAddress);
	IMPORT_C TCFSubModuleAddress(const TCFModuleName& aModule, const TCFSubModuleName& aSubModule);
	
	inline const TCFModuleName& Module() const;
	inline const TCFSubModuleName& SubModule() const;
	IMPORT_C void SetModule(const TCFModuleName& aModule);
	IMPORT_C void SetSubModule(const TCFSubModuleName& aSubModule);
	
	IMPORT_C TBool operator==(const TCFSubModuleAddress& aAddress) const;
	IMPORT_C TBool operator!=(const TCFSubModuleAddress& aAddress) const;
	IMPORT_C TCFSubModuleAddress& operator=(const TCFSubModuleAddress& aAddress);

	IMPORT_C TCFFullModuleName& Printable(TCFFullModuleName& aFullName) const;
private:
	TCFModuleName iModule;
	TCFSubModuleName iSubModule;
	};

#include "cfshared.inl"

} // namespace CommsFW

#endif // __CFSHARED_H__
