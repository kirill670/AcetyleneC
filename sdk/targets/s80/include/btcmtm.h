// $Workfile: btcmtm.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//



#if !defined (__BTCMTM_H__)
#define __BTCMTM_H__

#include <obexClientMtm.h>
#include <obexMtmUtil.h>

/* This defines the maximum length that the connection password can be for BlueTooth.  The PDU used for this
   has a payload of 16 bytes.
*/
#define KBlueToothObexPasswordLength 16

extern const TUint8 KObexConnectionIDHeader;

class CBtClientMtm : public CObexClientMtm
/**
class CBtClientMtm

Bluetooth Client MTM
Provides client-side functionality for bluetooth messaging. This is a thin implementation over the top of
CObexClientMtm.

@publishedPartner
@released
*/
	{
public:
	
	/**
	 * Canonical NewL factory function. 
	 *
	 * @param aRegisteredMtmDll Reference to registration data for MTM DLL.
	 * @param aMsvSession Reference to CMsvSession of the client requesting the object.	
	 * @returns Pointer to a new, constructed CBtClientMtm
	 * @exception Leaves if no memory is available.
	 */
	IMPORT_C static CBtClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);

	/// Contains the timeout values for connect and put operations
	struct STimeouts
		{
		TInt iConnectTimeout;
		TInt iPutTimeout;
		};
	
	///Structure for parameter needed for sending via Bluetooth
	struct SBtcCmdSendParams
		{
		STimeouts iTimeouts; ///< Structure containing connect and put operation timeouts
		TInt iRemoteObexPort; ///< The value of the remote obex port
		TDesC* iConnectPassword; ///<password sent to the remote server for a client initiated obex authentication challenge
		};

	struct SBtcCmdSendServerParams
		{
		STimeouts iTimeouts; ///< Structure containing connect and put operation timeouts
		TInt iRemoteObexPort; ///< The value of the remote obex port
		TBufC<KBlueToothObexPasswordLength> iConnectPassword; ///<password sent to the remote server for a client initiated obex authentication challenge 
		};

	// --- RTTI functions ---
	
	/**
	 * Starts an asynchronous function as an active object. Only works for EBtcCmdSend.
	 *
	 * @param aFunctionId Identifier of the function to be invoked. Only supports EBtcCmdSend.
	 * @param aSelection Selction of message entries for the requested function to operate on.
	 * @param aParameter Buffer containing input and output parameters.
	 * @param aCompletionStatus Canonical TRequestStatus used for control of the active object.
	 * @return Pointer to a new asynchronously completing CMsvOperation. If failed, this is a completed operation with 
	 * status set to the relevant error code.
	 * @exception Leaves if no memory is available, or if the specified aFunctionId is unsupported.
	 */

	virtual CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus); //aParameter should package up SBtcCmdSendParams

private:
	
	/**
	 * Constructor--not for use by client applications
	 *
	 * @param aRegisteredMtmDll Registration data for MTM DLL.
	 * @param aMsvSession CMsvSession of the client requesting the object. 
	 */

	CBtClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	
	/**
	 * Deletes the old header, then creates a new CBtHeader.
	 *
	 * @exception KErrXXX System-wide error codes if allocation fails
	 */
	
	virtual void InitialiseHeaderL();
#ifdef _DEBUG
	virtual void TestInvariant() const;
#endif //_DEBUG
	};



#endif // __BTCMTM_H__
