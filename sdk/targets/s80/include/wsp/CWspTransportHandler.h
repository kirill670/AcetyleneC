// CWspTransportHandler.h
//
// Copyright (C) 2001 Symbian Ltd

/** 
	@file CWspTransportHandler.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __CWSPTRANSPORTHANDLER_H__
#define __CWSPTRANSPORTHANDLER_H__

// System includes
#include <e32base.h>
#include <stringpool.h>
#include <http/framework/csecuritypolicy.h>

// Forward class declarations
class MWspCOSessionCallback;
class MWspProxyInfoProvider;
class MWspCapabilityProvider;
class MWspSessionHeadersProvider;
class MWspCOSessionInvoker;
class MWspCOMethodInvoker;
class MWspCOPushInvoker;
class MWspCLMethodInvoker;
class MWspCLPushInvoker;


//##ModelId=3BBD849A0269
class CWspTransportHandler : public CBase, public MSecurityPolicy
/** 
@class CWspTransportHandler
@since			7.0
The WSP Transport Handler API. The WSP TH provides its client with WSP services.
It defines a set of interfaces that abstract the behaviour of the top-level of a
WAP protocol stack - ie. the WSP layer.

Five distinct services are offered:

* MWspCOSessionInvoker a Connection-Oriented Session service.

* MWspCOMethodInvoker a Connection-Oriented Transaction service.

* MWspCOPushInvoker a Connection-Oriented Push service.

* MWspCLMethodInvoker a Connection-Less Session service.

* MWspCLPushInvoker a Connection-Less Push service.

The API is specified as an ECOM interface.  Specific implementations may offer
some or all of the five services.

All implementations must provide default security policy settings via the
MSecurityPolicy interface.  The defaults shall be used when no security policy
plug-in is supplied by the caller of CWspTransportHandler::NewL().  This might
occur if the plug-in could not be located on the device,
@publishedAll
@released
*/
	{
public: // type definitions and enumerations

/** A bit-field type that is set to contain a union of the services supported by the
	WSP transport handler.
*/
	typedef TUint8 TWspSupportedServices;

/** The five different service types that may be supported
*/
	enum TWspService
		{
		ECOSessionService = 0x01,
		ECOMethodInvocationService = 0x02,
		ECOPushService = 0x04,
		ECLSessionService = 0x08,
		ECLPushService = 0x10
		};

public: // methods

/** @fn	static CWspTransportHandler* NewL(RStringPool aStringPool,
									      MSecurityPolicy* aSecurityPolicy,
										  MWspCOSessionCallback& aSessionCB,
										  MWspProxyInfoProvider& aProxyInfoProv,
										  MWspCapabilityProvider& aCapProv,
										  MWspSessionHeadersProvider& aSessHdrProv)
	Intended Usage:	Factory construction - instantiates the transport handler plug-in.
	@since			7.0
	@param			aStringPool		(in) An open string pool reference.
	@param			aSecurityPolicy	(in) (optional) A security policy provider
	@param			aSessionCB		(in) A client callback API for CO session events.
	@param			aProxyInfoProv	(in) A client API that provides WAP proxy details
	@param			aCapProv		(in) A client API for capability negotatiation.
	@param			aSessHdrProv	(in) A client API for exchange of session headers
	@return			The constructed plug-in.
	@exception		KErrNotFound - if an ECOM implementation of the interface is not present on the device.
	@exception		It could also leave with other ECOM error codes.
*/
	//##ModelId=3C4C453103DD
	inline static CWspTransportHandler* NewL(RStringPool aStringPool,
											   MSecurityPolicy* aSecurityPolicy,
											   MWspCOSessionCallback& aSessionCB,
											   MWspProxyInfoProvider& aProxyInfoProv,
											   MWspCapabilityProvider& aCapProv,
											   MWspSessionHeadersProvider& aSessHdrProv);

/** @fn	virtual ~CWspTransportHandler()
	Intended Usage:	Class destructor.
	@since			7.0
*/
	//##ModelId=3C4C453103AB
	inline virtual ~CWspTransportHandler();

public: // General API methods

/** @fn	virtual TWspSupportedServices SupportedServices() const
	Intended Usage:	Query the services supported by this instantiation of the WSP
					transport handler plug-in.
	@since			7.0
	@return			A union of flags describing the services supported by the WSP transport
					handler
*/
	//##ModelId=3C4C45310256
	virtual TWspSupportedServices SupportedServices() const = 0;

	/** Get the Server Certificate for the current session.
	@param	aServerCert A TCertInfo which will be filled with the certificate information
	@return	An error code.  KErrNone if aServerCert has been completed, otherwise one of 
			the system wide error codes
	*/
	virtual TInt ServerCert(TCertInfo& aCertInfo) const = 0;

public: // Connection-Oriented WSP API methods

/** @fn	virtual MWspCOSessionInvoker& COSessionInvoker()
	Intended Usage:	Obtain the connection-oriented session invocation API.
	@since			7.0
	@return			The API object that should be used by the client for CO session
					invocations.
	@exception		This method will panic if the service isn't supported by a particular
					implementation of the API.
*/
	//##ModelId=3BC577C202B2
	virtual MWspCOSessionInvoker& COSessionInvoker() = 0;

/** @fn	virtual MWspCOMethodInvoker& COTransactionInvoker()
	Intended Usage:	Obtain the connection-oriented transaction invocation API.
	@since			7.0
	@return			The API object that should be used by the client for transaction
					invocations.
	@exception		This method will panic if the service isn't supported by a particular
					implementation of the API.
*/
	//##ModelId=3BC577C70165
	virtual MWspCOMethodInvoker& COTransactionInvoker() = 0;

/** @fn	virtual MWspCOPushInvoker& COPushInvoker()
	Intended Usage:	Obtain the connection-oriented push invocation API.
	@since			7.0
	@return			The API object that should be used by the client to signal
					readiness to receive CO push invocations.
	@exception		This method will panic if the service isn't supported by a particular
					implementation of the API.
*/
	//##ModelId=3C4C45310206
	virtual MWspCOPushInvoker& COPushInvoker() = 0;

public: // Connection-Less WSP API methods

/** @fn	virtual MWspCLMethodInvoker& CLMethodInvoker()
	Intended Usage:	Obtain the connection-less method invocation API.
	@since			7.0
	@return			The API object that should be used by the client for CL method
					invocations.
	@exception		This method will panic if the service isn't supported by a particular
					implementation of the API.
*/
	//##ModelId=3C4C453101DE
	virtual MWspCLMethodInvoker& CLMethodInvoker() = 0;

/** @fn	virtual MWspCLPushInvoker& CLPushInvoker()
	Intended Usage:	Obtain the connection-less push invocation API.
	@since			7.0
	@return			The API object that should be used by the client to signal
					readiness to receive CL push invocations.
	@exception		This method will panic if the service isn't supported by a particular
					implementation of the API.
*/
	//##ModelId=3C4C453101CA
	virtual MWspCLPushInvoker& CLPushInvoker() = 0;

protected: // type definitions
	/** @protected */
	/** 
		@struct SInstantiationParams
		A structure containing the instantiation parameters to NewL, passed across
		via ECOM to the sub-class NewL
	*/
	struct SInstantiationParams
		{
		/** An open string pool reference. */
		RStringPool* iStringPool;
		/** The security policy plugin. */
		MSecurityPolicy* iSecurityPolicy;
		/** A client callback API for CO session events.*/
		MWspCOSessionCallback* iSessionCB;
		/** A client API that provides WAP proxy details. */
		MWspProxyInfoProvider* iProxyInfoProv;
		/** A client API for capability negotatiation. */
		MWspCapabilityProvider* iCapProv;
		/** A client API for exchange of session headers. */
		MWspSessionHeadersProvider* iSessHdrProv;
		};

protected: // methods

/** @fn			CWspTransportHandler(RStringPool aStringPool,
								     MWspCOSessionCallback& aSessionCB,
								     MWspProxyInfoProvider& aProxyInfoProv,
							         MWspCapabilityProvider& aCapProv,
							         MWspSessionHeadersProvider& aSessHdrProv)
	Intended Usage:	Normal constructor. Creates an instance of the plug-in base.
	@since			7.0
	@param			aStringPool		(in) An open string pool reference.
	@param			aSecurityPolicy	(in) (optional) A security policy plug-in instance
	@param			aSessionCB		(in) A client callback API for CO session events.
	@param			aProxyInfoProv	(in) A client API that provides WAP proxy details
	@param			aCapProv		(in) A client API for capability negotatiation.
	@param			aSessHdrProv	(in) A client API for exchange of session headers
	@return			The constructed plug-in.
*/
	inline CWspTransportHandler(RStringPool aStringPool,
								  MSecurityPolicy* aSecurityPolicy,
								  MWspCOSessionCallback& aSessionCB,
								  MWspProxyInfoProvider& aProxyInfoProv,
							      MWspCapabilityProvider& aCapProv,
							      MWspSessionHeadersProvider& aSessHdrProv);

protected: // attributes

	/** Handle for a string pool used by the WSP transport handler.  This is owned
		and managed elsewhere.
	*/
	//##ModelId=3C4C453101A2
	RStringPool iStringPool;

	/** An optional security policy plug-in.  If a plug-in was not supplied, the
		value is NULL.
	*/
	//##ModelId=3C4C4531018E
	MSecurityPolicy* iSecurityPolicy;

	/** The client's callback for session events
	*/
	//##ModelId=3C4C4531017C
	MWspCOSessionCallback& iSessionCB;

	/** The client's provider of proxy information
	*/
	//##ModelId=3C4C45310170
	MWspProxyInfoProvider& iProxyInfoProv;

	/** The client's provider of capabilities information
	*/
	//##ModelId=3C4C4531015C
	MWspCapabilityProvider& iCapProv;

	/** THe client's provider of session headers
	*/
	//##ModelId=3C4C45310148
	MWspSessionHeadersProvider& iSessHdrProv;

private: // attributes

	/** @private */
	/** D'tor Key identification required for ECOM
		@internal
	*/
	//##ModelId=3C4C45310134
	TUid iDtor_ID_Key;
	};

#include <wsp/cwsptransporthandler.inl>

#endif // __CWSPTRANSPORTHANDLER_H__
