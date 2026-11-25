// cfutil.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __CFUTIL_H__
#define __CFUTIL_H__

#include <cfshared.h>
#include <cfmsgs.h>
#include <cflog.h>

namespace CommsFW 
/** Namespace for the Comms Framework
@publishedPartner 
@released
*/
{

class CCFModuleChannelHandler:public CActive
/** Utility class to help holding a channelpair, listening for incoming messages
and sending responses for CPMs needing a quick way to implement support
for the basic messages Discover, Bind, Unbind and Shutdown.
All the virtuals have default bodies so only those that require special treatment
needs implementation.
@publishedPartner 
@released
*/
	{
	protected:
		IMPORT_C TInt Send(const CommsFW::TCFMessage &aMessage);
		IMPORT_C ~CCFModuleChannelHandler();
		IMPORT_C CCFModuleChannelHandler(TInt aPriority);
		IMPORT_C virtual void CFMessageDiscover(const CommsFW::TCFDiscoverMsg& aMessage);
		IMPORT_C virtual void CFMessageBind(const CommsFW::TCFBindMsg& aMessage);
		IMPORT_C virtual void CFMessageUnbind(const CommsFW::TCFUnbindMsg& aMessage);
		IMPORT_C virtual void CFMessageShutdown(const CommsFW::TCFShutdownMsg& aMessage);
		IMPORT_C virtual void CFMessageUnknown(const CommsFW::TCFMessage& aMessage);
		IMPORT_C virtual void CFChannelError(TInt aError);
		IMPORT_C void ConstructL(CommsFW::RCFChannel::TMsgQueues &aRxQueues,
			                     CommsFW::RCFChannel::TMsgQueues &aTxQueues);
	private:
		IMPORT_C virtual void DoCancel();
		IMPORT_C virtual void RunL();
	private:
		CommsFW::RCFChannelPair iChannelPair;
	}; // CCFModuleChannelHandler

} // CommsFW
 
#endif // __CFUTIL_H__

