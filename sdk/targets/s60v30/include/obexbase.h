//
// obexbase.h
//
// Copyright (c) 2003-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __OBEXBASE_H
#define __OBEXBASE_H

#include "obextypes.h"


class MObexNotify
	/**
	 * @internalComponent
	 *
	 * Provides the call back interface for anything using CObexTransport (ie CObex).
	 * Note:  This is an internal class which is not intended for use outside of
	 * the Transport<->Obex interface.  Even where access rules allow it, external
	 * users should not call these functions as their implementation may change.
	 */
	{
	public:
		virtual void Process(CObexPacket &aPacket) =0;
		virtual void Error(TInt aError) =0;
		virtual void TransportUp(TObexConnectionInfo& aInfo) =0;			// Call back to start the obex session
		virtual void TransportDown(TBool aForceTransportDeletion = EFalse) =0;			//   "   "      stop       "	 "
	};

class MObexAuthChallengeHandler
	/**
	 * @publishedAll
	 * @released
	 *
	 * This class is the common base class for any object which wishes
	 * to use the Obex Server or Client. 
	 * The class which owns a CObexClient or CObexServer must be provide an object
	 * derived from this class to handle the call from the Server/Client for a request
	 * for a Password.
	 * @see CObex::SetCallBack
	 */
	{
	public:
	
		/**
		Indicates that the server/client has received an Authentication challenge. The challenge
		can only be responded to once a password has been retrieved by some means and passed
		back to the calling class. The password is passed back via
		CObex::UserPasswordL( const TDesC& aPassword)
		
		@param aRealm this will contain the Realm specified by the unit forcing the
		Authentication, if no UserID was supplied then this parameter will be of zero
		length.

		@publishedAll
		@released
		*/
		virtual void GetUserPasswordL(const TDesC& aRealm) = 0;
		
	    /**
	 	 Returns a null aObject if the extension is not implemented, or a pointer to another interface if it is.
		 @param aInterface UID of the interface to return
		 @param aObject the container for another interface as specified by aInterface
		 */
		IMPORT_C virtual void MOACH_ExtensionInterfaceL(TUid aInterface, void*& aObject);
		
	};


NONSHARABLE_CLASS(CObex) : public CBase, protected MObexNotify
	/**
	 * @publishedAll
	 * @released
	 *
	 * This class is the common base class for CObexClient and CObexServer. It is 
	 * an abstract class and cannot be instantiated in itself. However, it does 
	 * contain user functionality common to both client and server connections.
	 *
	 * Provides the basic OBEX transport functionallity (sending and receiving 
	 * files)
	 * Client and server provide the more specialied APIs for
	 *	@li initiation or response to puts & gets
	 *	@li (possible) handling of more generalised 'objects' (prob. with data
	 *		buffered through a file).
	 *
	 * @par Deriving classes from CObex
	 * This class is not designed for user derivation
	 */
	{
	public:
		NONSHARABLE_CLASS(TSetPathInfo)
		/**
		Describes the information set of received in a SETPATH command.
			 
		The first bit of iFlags, 0, can be set to indicate to the receiver of SETPATH to backup a level before applying the path name.
		The second bit of iFlags, 1, can be set to indicate to the receiver of SETPATH to NOT create the directory if it doesn't exist.
		The iConstants variable is always set to zero as it is reserved. 
		The iName variable indicates the directory to create or go to, and does not include the root directory of the receiver (i.e. 
		if the directory to be set is C:\notes then iName is set to "notes").
	 	If  a name is not set then set CObex::TSetPathInfo::iNamePresent to false. 
		*/
			{
		public:
			IMPORT_C TSetPathInfo();
			IMPORT_C TBool Parent() const;
			TUint8 iFlags;
			TUint8 iConstants;
			TBuf<KObexObjectDescriptionSize> iName;
			TBool iNamePresent;	///< Whether @c iName is present in this SETPATH info

		private:
			// This data padding has been added to help prevent future binary compatibility breaks	
			// Neither iPadding1 nor iPadding2 have been zero'd because they are currently not used
			TUint32     iPadding1; 
			TUint32     iPadding2; 				
			};
		
		// Current obex connection state
		enum TConnectState 
			{ 
			EConnIdle,					//nothing is happening
			EConnTransport,				//Transport Link connected not yet established true Link
			EConnObex,					//full connection established
			ESimpleConnRequest,			//Connect without Auth has been sent by ClientReceived by Server
			EConnChallRxed,				// Server has issued a challenge, to a Client cionnect
			ESimpleConnChallIssued,		//Server, received Simple Connect but Server Challenge issued
			EChallConnRequested,		//Connect with Auth has been sent by Client\Received by Server
			EChallConnChallIssued,		//Server has sent a Challenge & Resp to a Client EChallConnRequest
			EWaitForFinalResponse,		//Client, waiting for final success/fail not chall-response expected
										//Server, Waiting for final Resp fromm Client to Challenge
			EFinalResponseReceived,		//Server, the final response has been received
			EFinalChallRxed,			//Server, Client connect with challenge, Server responds with challenge, Client re-issued original/new challenge
			EWaitForUserInput,			//waiting for the user
			EDropLink					//drop the link 
			};

		enum TOperation 
			{ 
			EOpConnect		= 0x00,
			EOpDisconnect	= 0x01,
			EOpPut			= 0x02,
			EOpGet			= 0x03,
			EOpSetPath		= 0x05,
			EOpAbort		= 0xFF,	// - abort must fit in one pkt so final bit is always set
			EOpAbortNoFBit	= 0x7F,
			EOpGetResponse  = 0xFD,	// Not actually an obex operation. 
			EOpIdle			= 0xFE,	// Not actually an obex operation. 
			};
		
		virtual ~CObex();
		IMPORT_C void SetCallBack(MObexAuthChallengeHandler& aCallBack);
		IMPORT_C TBool IsConnected() const;
		IMPORT_C TBool IsStrictPeer() const;
		IMPORT_C const TObexConnectInfo& LocalInfo() const;
		IMPORT_C TInt SetLocalWho(const TDesC8& aInfo); 
	    IMPORT_C const TObexConnectInfo& RemoteInfo() const;

		// Implementation of MObexNotify Interface
		/**
		@internalTechnology
		*/
		virtual void Process(CObexPacket& aPacket);
		/**
		@internalTechnology
		*/
		virtual void Error(TInt aError) ;
		/**
		@internalTechnology
		*/
		virtual void TransportUp(TObexConnectionInfo& aInfo);				// Call back to start the obex session
		/**
		@internalTechnology
		*/
		virtual void TransportDown(TBool aForceTransportDeletion = EFalse);	//   "   "      stop       "	 "

		virtual void UserPasswordL( const TDesC& aPassword) = 0; 
		IMPORT_C void RemoteAddr(TSockAddr& anAddr); 
	protected:
		CObex(TObexProtocolPolicy& aObexProtocolPolicy);
		virtual void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);

		virtual TInt ParseConnectPacket(CObexPacket& aPacket) = 0;	
		void NewConnectorL(TObexProtocolInfo& aObexProtocolInfoPtr);
		void DeleteConnector();
		void NewTransportL(TObexConnectionInfo& aInfo);
		void DeleteTransport();
		void SetConnectState(TConnectState aNewState);
		IMPORT_C TConnectState ConnectState() const;
		virtual void OnPacketReceive(CObexPacket& aPacket) =0;
		virtual void OnError(TInt aError) =0;
		virtual void OnTransportUp() =0;
		virtual void OnTransportDown() =0;
		void ProcessChallengeL(const TObexInternalHeader& hdr);			//process the received challenge
		void ProcessChallResponseL(const TObexInternalHeader& hdr);		//process the response to challenge
		TInt GenerateChallenge(CObexPacket& aPacket);			//generate a challenge 
		void PrepareChallResponseL(const TDesC& aPassword);			//generate a response a respose to challenge
																//after user Password input
		void BringTransportDown();

	protected:
		TConnectState iConnectState;
		RSocketServ iSocketServ;
		RSocket iSocket;
		CObexSocketConnector* iConnector;
		CObexTransport* iTransport;
		TObexConnectInfo iLocalInfo;
		TObexConnectInfo iRemoteInfo;
		MObexAuthChallengeHandler* iCallBack;
		TNonce iOutgoingNonce; //nonce used when challenging
		TNonce iIncomingNonce; //nonce used when receiving a challenge
		HBufC8* iChallPassword;	//password used when challenging
		HBufC8* iRespPassword;	//password used when responding to a challenge
		HBufC8* iRxChallenge;
		TBuf8<KChallResponseSize> iOutgoingChallResp;//response to the previously issued challenge
									//16 nonce, 16 digest resp, 20 UserID, 3*(tag+size)
		TBuf8<KChallResponseSize> iIncomingChallResp;//response received from previous challenge
		TBuf8<KObexRespSize> iIncomingRequestDigest;
		HBufC* iRemoteUID;	//UID of remote device
		HBufC* iRemoteRealm;//Realm of remote device
		CObexAuthenticator* iAuthEngine;
		TBool iChallenge;	//to challenge or not to challenge?
		TBool iUserIDRequested; //does the challenge insist that a UserID is returned
		TBool iResponseVerified; //keep track if the EAuthResponse header has been received 
									//and has been verified as correct
		TOperation iCurrentOperation;
		TObexProtocolPolicy iProtocolPolicy;	// information on packet sizes
	};

#endif	// __OBEXBASE_H
