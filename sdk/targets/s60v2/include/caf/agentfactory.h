// agentfactory.h
//Copyright (c) Symbian Software Ltd 2003 - 2004 . All rights reserved

/** 
@publishedPartner
@prototype
*/



#ifndef __AGENTFACTORY_H__
#define __AGENTFACTORY_H__

#include <e32base.h>
#include <caf\caf.h>
#include <f32file.h>

namespace ContentAccess
{
	class CAgentConsumer;
	class CAgentSupplier;
	class CAgentManager;

	/** The ECOM agent interface UID. */
	const TUid KCAAgentInterfaceUid = {0x101FC2CE};

	/**
	 * Abstract interface handed out by an ECOM agent
	 * implementation (by REComSession::CreateImplementationL()).
	 * 
	 * Defines an abstract factory that is responsible for
	 * creating the abstract products: 
	 * @li ContentAccess::CAgentSupplier
	 * @li ContentAccess::CAgentConsumer
	 * @li ContentAccess::CAgentManager.
	 *
	 * Each agent implementation will hand out concrete product 
	 * implementations which are specific for that particular DRM-scheme.
	 *
	 * @see ContentAccess::CF32AgentFactory. This implements 
	 * ContentAccess::CAgentFactory to handle unrestricted content.
	 *
 	 * @publishedPartner
	 * @prototype
	 */
	class CAgentFactory : public CBase
		{
	public:
		/**
		 * Factory function that creates a consumer object.
		 *
		 * @param aURI	The path or URI of the target content.
		 * @param aShareMode The share mode for opening this content
		 * @return		A pointer to a consumer object.
		 */
		virtual CAgentConsumer* CreateConsumerL(const TDesC& aURI, TContentShareMode aShareMode)  = 0;

		/** 
		 * Factory function that creates a manager object. 
		 * 
		 * @return	A pointer to a ContentAccess::CAgentManager object.
		 */
		virtual CAgentManager*  CreateManagerL()   = 0;
		
		/** 
		 * Factory function that creates a supplier object. 
		 * 
		 * @return	A pointer to a ContentAccess::CAgentSupplier object.
		 */
		virtual CAgentSupplier* CreateSupplierL() = 0;

#ifdef SYMBIAN_SECURITY_CAF_RFILE_HANDLE
		/**
		 * Factory function that creates a consumer object.
		 *
		 * @param aFile	The path or URI of the target content.		 
		 * @return		A pointer to a consumer object.
		 */
		virtual CAgentConsumer* CreateConsumerL(RFile& aFile)  = 0;
#endif
		};
	
} // namespace ContentAccess
#endif // __AGENTFACTORY_H__
