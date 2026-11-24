// attribute.h
//Copyright (c) Symbian Software Ltd 2003 - 2004 . All rights reserved.

#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <e32base.h>
#include <caf\caf.h>
#include <f32file.h>

namespace ContentAccess
{
	class CAgentInfo;
	class CAgentConsumer;
	class CBitset;
	
	/**
	 * Encapsulates the attributes of a piece of content. 
	 *
	 * These attributes will be required by DRM-aware
	 * applications in order that they can uphold DRM policies in a
	 * well-behaved manner. In general, clients set one or more attributes
	 * in the <i>Query</i> set, make a <i>GetL</i> call, and then
	 * read the agent's reponse from the <i>Response</i> set.
	 *
	 * CAttribute is a container for a number of separate
	 * ContentAccess::CBitset objects. These individual bitsets contain:
	 * -# Queries - what the client is interested in knowing.
	 * -# Responses - the answers to the queries.
	 * -# Capabilities - which attributes the system is able to support.
	 *
	 * Access to the bitset operations themselves can be achieved via the
	 * ContentAccess::CAttribute::AttributeSetL operation.
	 *
	 * @publishedPartner
	 * @prototype
	 */
	class CAttribute : public CBase
		{
	public:
		virtual ~CAttribute();

		/**
		 * Returns a reference to the query set
		 *
		 * The bits of the query-set should be set or cleared prior to the "GetL()" 
		 * call to specify which attributes the client is interested in.
		 *
		 * @note	Set is probably best used inline to access some of the 
		 * 			CBitset operations directly.
		 * 			@code 
		 * 			// Set EIsProtected in the Query set.
		 * 			MyAttr->QuerySet(EQuerySet).Set(EIsProtected);
		 * 			@endcode
		 *
		 * @return	A CBitset refererence.
		 */
		IMPORT_C CBitset& QuerySet();

		/**
		 * Returns a reference to the response set. 
		 * 
		 * The response set will only be valid after a call to the "GetL()" operation.
		 *
		 * @return	A CBitset refererence.
		 */
		IMPORT_C const CBitset& ResponseSet() const;
		
		/**
		 * Resets the attribute object completely. 
		 */ 
		IMPORT_C void Reset();
		
		/**
		 * Delivers the attribute object to the relevant agent for
		 * querying. 
		 * 
		 * The agent will set or reset the ResponseSet() bits for any QuerySet() bits 
		 * that are set
		 */
		IMPORT_C void GetL();
		
		/**
		 * Constructs a new attribute given an agent and content.
		 *
		 * @param aAgent	The object that encapsulates the agent ECOM plug-in.
		 * @param aURI		The pathname of the target content.
		 * @param aShareMode Optional share mode for opening attributes of this content, defaults to EContentShareReadOnly. This parameter has no effect unless the content is a local file on the device.
		 * @return			The new object.
		 */
		static CAttribute* NewL(CAgentInfo& aAgent, const TDesC& aURI, TContentShareMode aShareMode=EContentShareReadOnly);
		
		/** @see NewL() */
		static CAttribute* NewLC(CAgentInfo& aAgent, const TDesC& aURI, TContentShareMode aShareMode=EContentShareReadOnly);

	private:
		void ConstructL(CAgentInfo& aAgent, const TDesC& aURI, TContentShareMode aShareMode=EContentShareReadOnly);
		CAttribute();

#ifdef SYMBIAN_SECURITY_CAF_RFILE_HANDLE		
	public:
		/**
		 * Constructs a new attribute given an agent and content.
		 *
		 * @param aAgent	The object that encapsulates the agent ECOM plug-in.
		 * @param aFile		The handle of the target content.
		  * @return			The new object.
		 */
		static CAttribute* NewL(CAgentInfo& aAgent, RFile& aFile);

		/** @see NewL() */
		static CAttribute* NewLC(CAgentInfo& aAgent, RFile& aFile);

	private:
		void ConstructL(CAgentInfo& aAgent, RFile& aFile);
#endif
		

	private:
		/** The agent ECOM encapsulation. */
		CAgentConsumer *iAgentConsumer;
		
		// Need to increment the reference count of a CAgentInfo 
		// otherwise ECOM will unload the agent when we least expect it
		CAgentInfo *iAgent;

		CBitset* iQuerySet;
		CBitset* iResponseSet;
		};
}
#endif // __ATTRIBUTE_H__
