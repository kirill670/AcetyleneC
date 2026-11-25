// OBEX.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef OBEX_H
#define OBEX_H


#if !defined(__OBEX_USER_DEFINED_HEADERS__)

	#include <e32std.h>
	#include <f32file.h>
	#include <es_sock.h>
	#include <ir_sock.h> // Required even if not building for IrDA
	#include <bt_sock.h> // Required even if not building for Bluetooth
	#include <utf.h>
	#include <e32des8.h>
	#include <e32des16.h>

	//common to request & resp digests

	/**	@internalComponent */
	const TInt KChallResponseSize = 58;

	/**	@internalComponent */
	const TInt KMinChallResponseSize = 18; //Nonce(16) + tag(1) + size(1)

	/**	@internalComponent */
	const TInt KObexNonceSize = 16;

	/**	@internalComponent */
	const TUint8 KObexRequireUID = 0x01;

	//request or chall

	/**	@internalComponent */
	const TUint KObexChallNonceTag = 0;

	/**	@internalComponent */
	const TUint8 KObexChallOptionsTag = 0x01;

	/**	@internalComponent */
	const TUint8 KObexChallRealmTag = 0x02;

	/**	@internalComponent */
	const TInt KObexChallOptionSize = 1; //this can't be changed from one without making

	/**	@internalComponent */
	const TUint KObexChallHeaderSize = 23; //assuming no Realm data

	//response

	/**	@internalComponent */
	const TUint KObexRespTag = 0;

	/**	@internalComponent */
	const TInt KObexRespSize = 16;

	/**	@internalComponent */
	const TUint8 KObexRespUserIDTag = 0x01;

	/**	@internalComponent */
	const TUint8 KObexRespNonceTag = 0x02;

	#ifdef _UNICODE
	/**	@internalComponent */
	const TInt KUidOBEXTransportModule = 0x10003d56;
	#else
	/**	@internalComponent */
	const TInt KUidOBEXTransportModule = 0x1000169c;
	#endif

	/**	@internalComponent */
	const TUint8 KObexConnectionIDLength = 4;


	/** A "header mask" through which a caller can specify which OBEX object attributes 
	will be sent or read, to allow restrictions on the headers exchanged.

	Possible mask flags are listed from KObexHdrName to KObexHdrConnectionID.

	@see CObexBaseObject::HeaderMask()
	@see CObexBaseObject::SetHeaderMask() 

	@publishedAll
	@released
	*/
	typedef TUint16 TObexHeaderMask;

	/** Name header flag. 
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrName			= 0x0001;

	/** Type header flag. 
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrType			= 0x0002;

	/** Length header flag. 
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrLength		= 0x0004;

	/** Time header flag. 
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrTime			= 0x0008;

	/** Description header flag. 
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrDescription	= 0x0010;

	/** Target header flag.  
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrTarget		= 0x0020;

	/** Obex header ConnectionID flag.  
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrConnectionID	= 0x0040;
	/** Obex header begin body flag  
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrBody			= 0x0080;
	/** Obex header end body flag  
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrEndOfBody		= 0x0100;

	/** Obex header HTTP flag 
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrHttp			= 0x0200;

	/** Obex header Application Parameter 
	@publishedAll
	@released
	*/
	const TUint16 KObexHdrAppParam		= 0x0400;

	/** OBEX version number. 
	@internalComponent 
	*/
	const TUint8 KObexVersion           = 0x10;		///< Version 1.0 (still correct for Obex spec v 1.2)

	/** Buffer size for storing OBEX attribute values. 
	@internalComponent
	*/
	const TUint8 KObexObjectFieldSize   = 127;

	/** Buffer size for storing OBEX Description values. 
	@internalComponent
	*/
	const TUint8 KObexObjectDescriptionSize = 255;

	//Extended Errors for IrObex

	/** Extended error for OBEX: no other device found. 
	@publishedAll
	@released
	*/
	const TInt KErrIrObexClientNoDevicesFound = -5501;

	/** Extended error for OBEX: Other device cannot handle OBEX. 
	@publishedAll
	@released
	*/
	const TInt KErrIrObexClientPeerDoesNotHaveObex = -5502;

	/** Extended error for OBEX: Other device aborted the transfer. 
	@publishedAll
	@released
	*/
	const TInt KErrIrObexClientPutPeerAborted = -5503;

	/** Extended error for OBEX: peer device aborted data transmission/OBEX sending. 
	@publishedAll
	@released
	*/
	const TInt KErrIrObexServerPutPeerAborted = -5507;

	/** Extended error for OBEX: authentication challenge rejected. 
	@publishedAll
	@released
	*/
	const TInt KErrIrObexConnectChallRejected = -5512; 

	 
	// Flags used by Connect
	// ...None in OBEX 1.0

	// Flags used by SetPath

	/** Set path information parent flag, as used in CObex::TSetPathInfo::Parent(). 
	@publishedAll
	@released
	*/
	const TUint8 KObexSetPathParent	= 0x01;

	/** @internalComponent */
	typedef TUint8 TObexOpcode;

	/** @internalComponent */
	typedef TBuf8<KObexConnectionIDLength> TConnId;

	/** @internalComponent */
	typedef TBuf8<16> TNonce;

	/** @internalComponent */
	typedef TBuf8<16> TRequestDigest;

	class TObexPacket;

	class CObexBaseObject : public CBase
	/** Base class for OBEX objects.

	The class has a number of attributes describing the object. The attributes
	correspond closely to the underlying OBEX headers. OBEX headers specified as
	Unicode strings (e.g. Name) are held as Symbian OS modifiable descriptors;
	OBEX "byte sequences" (e.g. Type) are narrow descriptors or literals; and 
	OBEX byte and 32 bit integers (e.g. Length) are TUint32s. 

	The class records which attributes have been set to valid values, so that 
	only these attributes are sent to the remote machine. A "header mask" concept 
	is also available, through which the caller can specify which attributes will 
	be sent or read, to allow restrictions on the headers exchanged. Objects default 
	to transferring all valid attributes.

	The class does not define how the object data (body) is stored. This is done 
	in the derived classes CObexBufObject, CObexFileObject, and CObexNullObject. 
	The class is not designed for user derivation. 

	@publishedAll
	@released
	*/
		{
	friend class CObexClient;
	friend class CObexServer; 
	public:
		virtual ~CObexBaseObject();
		
		/** Sets the header mask. 
		
		aHeaderMask is a bitmask of KObexHdr... (KObexHdrName etc.) constants. For 
		example, if it is set to KObexHdrName | KObexHdrLength, only these two headers 
		will be specified in transfer operations with the remote machine, even if 
		there are other valid attributes which could be used. In effect, this mask 
		is bit-wise 'and'ed with the "valid headers" mask when determining which 
		headers are valid for the purposes of transfers.
		
		@param aHeaderMask Header mask 
		
		@publishedAll
		@released
		*/
		inline void SetHeaderMask(const TObexHeaderMask aHeaderMask);
		IMPORT_C void SetNameL(const TDesC& aDesc);
		IMPORT_C void SetTypeL(const TDesC8& aDesc);
		IMPORT_C void SetLengthL(const TUint32 aLength);
		IMPORT_C void SetTimeL(const TTime aTime);
		IMPORT_C void SetDescriptionL(const TDesC& aDesc);
		IMPORT_C void SetTargetL(const TDesC8& aDesc);
		IMPORT_C void AddHttpL(const TDesC8& aDesc);
		IMPORT_C void SetAppParamL(const TDesC8& aDesc);


		/** Gets the number of bytes of the body of the object transferred so far while 
		sending this object.
		@return Number of bytes sent 
		
		@publishedAll
		@released
		*/
		inline TInt BytesSent();
		
		/** Gets the number of bytes of the body of the object transferred so far while 
		receiving this object.
		
		@return Number of bytes received 
		
		@publishedAll
		@released
		*/
		inline TInt BytesReceived();
		
		/** Gets the header mask.
		
		It defaults to 0xFF (i.e. allow everything). 
		
		@return Header mask 
		
		@publishedAll
		@released
		*/
		inline TObexHeaderMask HeaderMask();

		/** Gets the valid header mask.
		
		@return Header mask 
		
		@publishedAll
		@released
		*/
		inline TObexHeaderMask ValidHeaders();

		IMPORT_C const TDesC& Name();
		IMPORT_C const TDesC8& Type();
		IMPORT_C const TUint32 Length();
		IMPORT_C const TTime Time();
		IMPORT_C const TDesC& Description();
		IMPORT_C const TDesC8& Target();
		IMPORT_C const RPointerArray<HBufC8>* Http() const;
		IMPORT_C const TDesC8& AppParam() const;
		IMPORT_C void Reset();
	protected:
		CObexBaseObject();
		void GuessTypeFromExtL(const TDesC& aExt);
		void ResetHeaders();
		// Pure virtuals that all derived objects must implement
		virtual void GetData(TInt aPos, TDes8& aDes) =0;
		virtual void NewData(TInt aPos, TDes8& aDes) =0;
		virtual TInt DataSize() =0;
		virtual void ResetData() =0;
	private:
		enum TProgress { EContinue,EComplete,EError };
		TInt InitSend(TObexOpcode aOpcode);
		TProgress PrepareNextSendPacket(TObexPacket& aPacket);
		TInt InitReceive();
		TProgress ParseNextReceivePacket(TObexPacket& aPacket);
		void PrepareConnectionHeader( TObexPacket& aPacket );
		void SetConnectionIdL(const TUint32 aConnectionID);
		TUint32 ConnectionID();
	// Data
	protected:
		// Accessed by an inline
		TObexHeaderMask iHeaderMask;
		
		// Accessed by an inline
		TObexHeaderMask iValidHeaders;
		
		HBufC* iName;	
		HBufC8* iType;
		TInt iLength;
		TTime iTime;
		HBufC* iDescription;
		HBufC8* iTarget;
		TUint32 iConnectionID;
	private:
		// Members used while transfering the object
		TProgress iSendProgress;
		TObexOpcode iSendOpcode;
		TObexHeaderMask iSendHeaders;
		
		// Accessed by an inline
		TInt iSendBytes;
		
		TProgress iRecvProgress;
		
		// Accessed by an inline
		TInt iRecvBytes;
		
		TInt iNextHttpHeader;
	protected:
		HBufC8* iAppParam;
		RPointerArray<HBufC8>* iHttp;
		};

	class CObexFileObject : public CObexBaseObject
	/** Concrete OBEX object with the body part stored as a file.

	Access to the body is achieved through an additional attribute to the object: 
	the data file. This is the file-system name of the file used to store the 
	body of the object. Note that there is no explicit relation between this and 
	the Name attribute of the object, although it is expected that most applications 
	would attempt to relate the two. 

	There is no restriction in what the class is used to transfer, although it 
	is particularly suited to OBEX file beaming applications. CObexFileObject 
	is also suited to situations where an object is expected to be received, but 
	no information about the purpose of this object is known. This is because 
	CObexFileObject's can create temporary files in which to store received data, 
	when a file is not specified by the application.

	When a valid data file is set, this file is effectively open, hence stopping 
	any other application from opening it with exclusive rights. Therefore, it 
	is recommended that the base class function Reset() be called on the object 
	as soon as it is no longer required, and definitely before (conceptually) 
	passing ownership of the data file to any other object or user.

	This class is not designed for user derivation. 

	@publishedAll
	@released
	*/
		{
	public:
		static IMPORT_C CObexFileObject* NewL(const TDesC &aDataFile = TPtrC(NULL, 0));
		virtual IMPORT_C ~CObexFileObject();
		IMPORT_C void InitFromFileL(const TDesC& aFile);

		IMPORT_C void HurricaneSetStub(const TDesC& aDesc);
		IMPORT_C const TDesC& HurricaneGetStub();

	private:
		void ConstructL(const TDesC &aDataFile);
		void SetDataFileL(const TDesC& aDesc);
		const TDesC& DataFile();
		TBool RenameFile(const TDesC& aDesC);
		void SetTempFilePath(const TDesC& aPath);
		void QueryTempFilePath(TDes& aPath);
		// From CObexBaseObject
		virtual void GetData(TInt aPos, TDes8& aDes);
		virtual void NewData(TInt aPos, TDes8& aDes);
		virtual TInt DataSize();
		virtual void ResetData();
	// Data
	private:
		RFs iFs;
		TParse iDataFile;
		RFile iFile;
		TBuf<KObexObjectDescriptionSize> iTempFilePath;
		};

	class MObexFileWriter;

	class CObexBufObject : public CObexBaseObject
	/** Concrete OBEX object with the body part stored as a dynamic buffer (CBufBase-derived 
	class).


	CObexBufObject must always have a valid data buffer set, but does not create 
	or own the buffer. It is always the responsibility of the caller to free the 
	buffer when its use is complete.

	This class is not designed for user derivation. 

	@publishedAll
	@released
	*/
		{
	public:
		enum TFileBuffering
		/**
		 * Obex file buffering method.
		 *
		 * @publishedAll
		 */
			{
			/** Only the supplied buffer will be used to buffer file writes. */
			ESingleBuffering,
	        /** The object will create a secound buffer and perform double buffering. */
	        EDoubleBuffering
			};
	
	public:
		static IMPORT_C CObexBufObject* NewL(CBufBase* aDataBuf);
		virtual IMPORT_C ~CObexBufObject();
		IMPORT_C TInt WriteToFile(const TPtrC& aFileName);
		IMPORT_C void SetDataBufL(CBufBase* aDataBuf);
		IMPORT_C void SetDataBufL(const TPtrC& aFilename);
		IMPORT_C void SetDataBufL(const TPtrC& aFilename, CBufBase* aDataBuf);
		IMPORT_C void SetDataBufL(const TPtrC& aFilename, CBufBase& aDataBuf, const TFileBuffering aBufferingStrategy);
		IMPORT_C CBufBase* DataBuf();
		HBufC* FileName();

		IMPORT_C void HurricaneSetStub(CBufBase* aBuf);

	private:
		CObexBufObject();
		void ConstructL(CBufBase* aDataBuf);

		void CopyFileL(const TDesC& aFilename);
		TInt NewFileData(TInt aPos, TDes8& aDes);
		void GetFileData(TInt aPos, TDes8& aDes);

		// From CObexBaseObject
		virtual void GetData(TInt aPos, TDes8& aDes);
		virtual void NewData(TInt aPos, TDes8& aDes);
		virtual TInt DataSize();
		virtual void ResetData();

		inline void CloseDataFile();
		inline TInt OpenDataFile(const TDesC& aFilename);
		inline void CloseFileServer();
		inline TInt OpenFileServer();
		inline TInt WriteBufferToFile(TBool aFinal);

	// Data
	private:
		CBufBase* iBuf;
		HBufC* iFilename;
		RFs* iFileServ;
		RFile* iFile;
		TInt iBufOffset;
		TInt iBuffered;
		TInt iBufSegSize;

	// Added for double-buffering
	private:
		// Owned
		MObexFileWriter*	iWriter;
		CBufBase*			iDoubleBuf;
		};

	class CObexNullObject : public CObexBaseObject
	/** Concrete OBEX object with NULL data representation.

	Use this when only the headers of an object are required, and the data (if 
	any) can safely be discarded. 

	@publishedAll
	@released
	*/
		{
	public:
		IMPORT_C static CObexNullObject* NewL ();
	private:
		// From CObexBaseObject
		virtual void GetData (TInt aPos, TDes8& aDes);
		virtual void NewData (TInt aPos, TDes8& aDes);
		virtual TInt DataSize ();
		virtual void ResetData ();
		};


	// Constants used to define which transport Obex will run over.  Used in
	// TObexProtocolInfo's iTransport member.

	//! Protocol string when running over IrDA
	_LIT(KObexIrTTPProtocol, "IrTinyTP");

	//! Protocol string when running over Bluetooth
	_LIT(KObexRfcommProtocol, "RFCOMM");

	//! Protocol string when running over USB
	_LIT(KObexUsbProtocol, "USB");


	class TObexProtocolInfo
	/** Base class for information relating to the transport protocol over which OBEX 
	is running.

	It is derived for each underlying transport protocol OBEX runs over. At this 
	time, IrTinyTP (TObexIrProtocolInfo) and Bluetooth RFCOMM (TObexBluetoothProtocolInfo) 
	are supported. 

	@publishedAll
	@released
	*/
		{
	public:
		/** The unique name for the transport.
		
		For IrTinyTP this is "IrTinyTP", and for Bluetooth RFCOMM, it is "RFCOMM". 
		
		@publishedAll
		@released
		*/
		TBuf<60> iTransport;
		};

	// NB: This will require ir_sock.h even if it is never used

	class TObexIrProtocolInfo : public TObexProtocolInfo
	/** Extends OBEX transport protocol information for when IrDA is used as the transport. 
	@publishedAll
	@released
	*/
		{
	public:
		/** IrDA address information about this connection.
		
		Its main use is for setting the port that the local machine will listen on. 
		
		@publishedAll
		@released
		*/
		TIrdaSockAddr iAddr;
		
		/** IAS class value with which the OBEX session registers its listener port, or 
		requests a remote port.
		
		To access the default OBEX server, this should be "OBEX". 
		
		@publishedAll
		@released
		*/
		TBuf8<KIASClassNameMax> iClassName;
		
		/** IAS attribute value with which the OBEX session will register its listener 
		port, or requests a remote port.
		
		To access the default OBEX server, this should be "IrDA:TinyTP:LsapSel". 
		
		@publishedAll
		@released
		*/
		TBuf8<KIASAttributeNameMax> iAttributeName;
		};

	// NB: This will require bt_sock.h even if it is never used
	class TObexBluetoothProtocolInfo : public TObexProtocolInfo
	/** Extends OBEX transport protocol information for when Bluetooth is used as the 
	transport. 

	@publishedAll
	@released
	*/
		{
	public:
		/** Bluetooth sockets address. 
		
		@publishedAll
		@released
		*/
		TRfcommSockAddr iAddr;
		};

	/**	Defines maximum length allowable for a USB interface string descriptor

	@publishedAll
	@released
	*/
	const TInt KUsbIntStringDescLength = 30;

	class TObexUsbProtocolInfo : public TObexProtocolInfo
	/** Extends OBEX transport protocol information for when USB is used as the 
	transport. 

	@publishedAll
	@released
	*/
		{
	public:
		TBuf16<KUsbIntStringDescLength> iInterfaceStringDescriptor;
		};

	struct TObexConnectionInfo;

	class TObexConnectInfo
	/** OBEX connection information.

	This includes the OBEX version of the machine, connection flags, and the Who 
	attribute from the connect packet.

	It is recommended that this class is only ever allocated on the heap as it 
	is quite large. 

	@publishedAll
	@released
	*/
		{
	public:
		/** Default constructor. 
		
		@publishedAll
		@released
		*/
		inline TObexConnectInfo();
		
		/** Gets the major OBEX version number of the machine.
		
		@return Major OBEX version number 
		
		@publishedAll
		@released
		*/
		inline TUint8 VersionMajor() const;
		
		/** Gets the minor OBEX version number of the machine.
		
		@return Minor OBEX version number 
		
		@publishedAll
		@released
		*/
		inline TUint8 VersionMinor() const;
	public:
		
		/** Encoded OBEX version number of the machine. 
		
		@publishedAll
		@released
		*/
		TUint8 iVersion; ///< Encoded OBEX version of the machine
		
		/** OBEX connection flags. 
		@publishedAll
		@released
		*/
		TUint8 iFlags; ///< iFlags holds OBEX connection flags
		
		/** The Who attribute from the connect packet.
		
		If none was specified, this has a length of 0. 
		
		@publishedAll
		@released
		*/
		TBuf8<KObexObjectDescriptionSize> iWho; ///< the Who attribute from the connect packet, if any was specified
		
		/** The Target header from the connect packet, if any was specified. 
		
		@publishedAll
		@released
		*/
		TBuf8<KObexObjectDescriptionSize> iTargetHeader; ///< the Target header from the connect packet, if any was specified

		};


	//---------------
	// Provides the call back interface for anything using CObexTransport (ie CObex)
	class MObexNotify
	/** This is internal and not intended for use. 

	@internalComponent
	*/
		{
	public:

		/** @internalComponent */
		virtual void Process(TObexPacket &aPacket) =0;
		/** @internalComponent */
		virtual void Error(TInt aError) =0;
		/** @internalComponent */
		virtual void TransportUp(TObexConnectionInfo& aInfo) =0;			// Call back to start the obex session
		/** @internalComponent */
		virtual void TransportDown(TBool aForceTransportDeletion = EFalse) =0;			//   "   "      stop       "	 "
		};

	class MObexAuthChallengeHandler
	/** OBEX authentication challenge interface.

	An object that uses a OBEX Server or Client must implement this interface 
	to be notified that the Server/Client that requires a password to access a 
	remote machine. 

	@publishedAll
	@released
	*/
		{
	public:
		/** Indicates that the server/client has received an authentication challenge. 
		
		The challenge can only be responded to once a password has been retrieved 
		by some means and passed back to the calling class. The password is passed 
		back through CObex::UserPasswordL().
		
		@param aRealm The realm (a userid to determine which password to use) specified 
		by the unit forcing the authentication. If no userid was supplied, then this 
		parameter will be of zero length. 
		
		@publishedAll
		@released
		*/
		virtual void GetUserPasswordL(const TDesC& aRealm) = 0;
		};

	class CObexTransport;
	class CObexSocketConnector;
	class TObexInternalHeader;
	class CObexAuthenticator;

	//-----------------------------------------------
	//
	class CObex : public CBase, protected MObexNotify
	/** Abstract base class for OBEX client (CObexClient) and OBEX server (CObexServer) 
	objects.

	The class provides the basic OBEX transport functionality for sending and 
	receiving files. Client and server provide the more specialied APIs for initiating 
	or responding to OBEX operations.

	This class is not designed for user derivation. 

	@publishedAll
	@released
	*/
		{
	public:
		class TSetPathInfo
		/** Describes the information received in an OBEX SETPATH command. 
		
		@publishedAll
		@released
		*/
			{
		public:
			/** Default constructor. 
			
			@publishedAll
			@released
			*/
			inline TSetPathInfo();
		
			/** Tests if the KObexSetPathParent flag is set.
			
			@return True if the flag is set 
			
			@publishedAll
			@released
			*/
			inline TBool Parent() const;
		
			/** SETPATH request flags. 
			
			@publishedAll
			@released
			*/
			TUint8 iFlags;
		
			/** SETPATH request constants. 
			
			@publishedAll
			@released
			*/
			TUint8 iConstants;
		
			/** Name header value specifying the path. 
			
			@publishedAll
			@released
			*/
			TBuf<KObexObjectDescriptionSize> iName;
		
			/** Indicates if the iName is set in this SETPATH information. 
			
			@publishedAll
			@released
			*/
			TBool iNamePresent;	///< Whether @c iName is present in this SETPATH info
			};
		enum TConnectState 
		/** Current obex connection state. 
		
		@internalComponent
		*/
			{
			/** The connection is idle so nothing is happening. */
			EConnIdle,
	        /** The connection transport (only) link is up. */
			EConnTransport,
	        /** Full connection over an Obex link has been established. */
			EConnObex,
	        /** A connection that has not been authorized. */
			ESimpleConnRequest,
	        /** A connection request has been challenged by the server. */
			EConnChallRxed,
	        /** A request for a simple connection has been challenged by the
			server. */
			ESimpleConnChallIssued,
	        /** A request for connection, with authorization, has been sent by a
			client or received by the server. */
			EChallConnRequested,
	        /** Server has sent a Challenge & Resp to a Client EChallConnRequest */
			EChallConnChallIssued,
	        /** Client, waiting for final success/fail not chall-response expected
			Server, Waiting for final Resp fromm Client to Challenge */
			EWaitForFinalResponse,
	        /** The final response has been received by the server. */
			EFinalResponseReceived,
	        /** Server, Client connect with challenge, Server responds with
			challenge, Client re-issued original/new challenge */
			EFinalChallRxed,
	        /** Waiting for input from the user. */
			EWaitForUserInput,
	        /** The link has been dropped. */
			EDropLink
			};


		enum TOperation 
		/** OBEX operations. 
		
		@publishedAll
		@released
		*/
			{ 
			/** CONNECT operation. */
			EOpConnect		= 0x00,
			/** DISCONNECT operation. */
			EOpDisconnect	= 0x01,
			/** PUT operation. */
			EOpPut			= 0x02,
			/** GET operation. */
			EOpGet			= 0x03,
			/** SETPATH operation. */
			EOpSetPath		= 0x05,
			/** ABORT operation. */
			EOpAbort		= 0xFF,	// - abort must fit in one pkt so final bit is always set
			/** ABORT operation in progress. */
			EOpAbortNoFBit	= 0x7F,
			/** Waiting for response. */
			EOpGetResponse  = 0xFD,	// Not actually an obex operation. 
			/** No operation. */
			EOpIdle			= 0xFE,	// Not actually an obex operation. 
			};
		virtual ~CObex();
		IMPORT_C void SetCallBack(MObexAuthChallengeHandler& aCallBack);
		
		/** Tests if this object has an OBEX connection.
		
		To return true, the two devices must have completed the OBEX connection request/response. 
		All other states return false. 
		
		This will be unreliable if either the server blindly returns the client’s 
		Who header (always reports true), or if neither supply Who headers (always 
		reports false).
		
		@return True if this object has an OBEX connection 
		
		@publishedAll
		@released
		*/
		inline TBool IsConnected() const;
		
		/** Tests if the Who header specified in the server's connect response matched 
		that of the client's connect request, and that both specified a Who field.
		
		It is undefined if IsConnected() is false.
		
		@return True if client and server are strict peers 
		
		@publishedAll
		@released
		*/
		inline TBool IsStrictPeer() const;
		
		/** Gets the connection information that will be sent to the OBEX peer as part 
		of the connection process.
		
		You can alter the retrieved information. Altering this structure after a connection 
		has been made will have no effect on the current session, but will be used 
		for future connection attempts.
		
		@return Connection information 
		
		@publishedAll
		@released
		*/
		inline const TObexConnectInfo& LocalInfo() const;
		IMPORT_C TInt SetLocalWho(const TDesC8& aInfo); 
		
		/** Gets the connection information specified by the remote machine during the 
		OBEX connection.
		
		The content of this structure is undefined when IsConnected() is false.
		
		@return Remote machine's connection information 
		
		@publishedAll
		@released
		*/
	    inline const TObexConnectInfo& RemoteInfo() const;
		// Implementation of MObexNotify Interface
		virtual void Process(TObexPacket& aPacket);
		virtual void Error(TInt aError) ;
		virtual void TransportUp(TObexConnectionInfo& aInfo);				// Call back to start the obex session
		virtual void TransportDown(TBool aForceTransportDeletion = EFalse);	//   "   "      stop       "	 "
		
		/** A call back from the the service with the password required for use with generating 
		the challenge response. 
		
		@param aPassword Password 
		
		@publishedAll
		@released
		*/
		virtual void UserPasswordL( const TDesC& aPassword) = 0; 
		
		IMPORT_C void RemoteAddr(TSockAddr& anAddr); 
	protected:
		CObex();
		virtual void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
		virtual TInt ParseConnectPacket(TObexPacket& aPacket) = 0;	
		void NewConnectorL(TObexProtocolInfo& aObexProtocolInfoPtr);
		void DeleteConnector();
		void NewTransportL(TObexConnectionInfo& aInfo);
		void DeleteTransport();
		void SetConnectState(TConnectState aNewState);
		inline TConnectState ConnectState() const;
		virtual void OnPacketReceive(TObexPacket& aPacket) =0;
		virtual void OnError(TInt aError) =0;
		virtual void OnTransportUp() =0;
		virtual void OnTransportDown() =0;
		void ProcessChallengeL(const TObexInternalHeader& hdr);			//process the received challenge
		void ProcessChallResponseL(const TObexInternalHeader& hdr);		//process the response to challenge
		TInt GenerateChallenge(TObexPacket& aPacket);			//generate a challenge 
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
		};

	class CObexClient : public CObex
	/** OBEX client.

	The class supports standard OBEX operations in an OBEX session running over 
	an IrDA or Bluetooth socket.

	This class is not designed for user derivation. 

	@publishedAll
	@released
	*/
		{
	public:
		IMPORT_C ~CObexClient();
		IMPORT_C static CObexClient* NewL(TObexProtocolInfo& aObexProtocolInfoPtr);
		IMPORT_C void Connect(TRequestStatus& aStatus);
		IMPORT_C void Connect(CObexBaseObject& aObject, TRequestStatus& aStatus);	
		IMPORT_C void ConnectL(CObexBaseObject& aObject, const TDesC& aPassword, 
														TRequestStatus& aStatus);
		IMPORT_C void ConnectL(const TDesC& aPassword, TRequestStatus& aStatus);
		IMPORT_C void Disconnect(TRequestStatus& aStatus);						
		IMPORT_C void Put(CObexBaseObject& aObject, TRequestStatus& aStatus);
		IMPORT_C void Get(CObexBaseObject& aObject, TRequestStatus& aStatus);		
		IMPORT_C void SetPath(TSetPathInfo& aPathInfo, TRequestStatus& aStatus);
		IMPORT_C void Abort();					
		IMPORT_C void UserPasswordL( const TDesC& aPassword); 
		
	private:
		CObexClient();
		void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
		TBool AlreadyActive(TRequestStatus& aStatus);
		void ClientCommandL(TOperation aOp, TAny* aParam, TRequestStatus& aStatus);
		// Implementation of CObex Events
		virtual void OnPacketReceive(TObexPacket& aPacket);
		virtual void OnError(TInt aError);
		virtual void OnTransportUp();
		virtual void OnTransportDown();
		void SetRequest(TRequestStatus& aStatus, TOperation aOperation);
		void CompleteRequest(const TInt aCompletion);
		TInt PrepareConnectPacket(TObexPacket& aPacket);	// Should be members of TConnectInfo
		TInt ParseConnectPacket(TObexPacket& aPacket);	
		void ResetConnectionID();
		void SetConnectionID(TUint32 aConnectionID);
	private: 
		TRequestStatus* iPendingRequest;
		CObexBaseObject* iCurrentObject;
		TUint32 iConnectionID; 
		TBool iConnectionIdSet;
		};

	class MObexServerNotify;

	class CObexServer : public CObex
	/** OBEX server.

	CObexServer provides a framework for servicing OBEX requests from remote clients. 
	It is designed to be able to act as either a "default" application (in IrDA 
	terms, registering on the IrDA:OBEX IAS class), or as a application specific 
	server (registering itself on a private IAS class). 

	You implement service-specific behaviour by providing a MObexServerNotify 
	interface implementation to the server object. The server calls the interface's 
	functions to provide notification of server events, which specific implementations 
	can process (or ignore) as appropriate.

	This class is not designed for user derivation. 

	@publishedAll
	@released
	*/
		{
	public:
		enum TTargetChecking
			/**
			 * @publishedAll
			 *
			 * The target header checking to apply to incoming connection requests.  Defaults to
			 * EIfPresent.
			 * @see CObexServer::SetTargetChecking
			 */
			{
			ENoChecking,	/** Allow all target headers to connect. */
			EIfPresent,		/** Only check target header in response to receiving one. Allows all clients
								specifying an Inbox service to connect. */
			EAlways,		/** Strict checking. Only allow connections if target header matches or no header
								received and none expected. */
			};

		IMPORT_C static CObexServer* NewL(TObexProtocolInfo& aObexProtocolInfoPtr);
		IMPORT_C ~CObexServer();
		IMPORT_C TInt Start(MObexServerNotify* aOwner);
		IMPORT_C void Stop();
		
		/** Tests if the server is started, and is available to accept connections.
		
		@return True if the server is started 
		
		@publishedAll
		@released
		*/
		inline TBool IsStarted();
		
		/** Gets the operation currently being performed by the remote client, or CObex::EOpIdle 
		if between operations.
		
		Note that there is no implication of whether the server is currently connected: 
		CObex::EOpIdle can be returned regardless of the connection state if no operation 
		is currently being performed. Use CObex::IsConnected() to find the connection 
		staus.
		
		@return Operation currently being performed by the remote client
		
		@publishedAll
		@released
		*/
		inline TOperation CurrentOperation() const;
		IMPORT_C void SetChallengeL(const TDesC& aPassword);
		IMPORT_C void ResetChallenge();
		IMPORT_C void UserPasswordL( const TDesC& aPassword); 
		IMPORT_C void SetTargetChecking(TTargetChecking aChecking);

	private:
		CObexServer();
		void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
		TInt AcceptConnection();
		// Implementation of CObex Events
		virtual void OnPacketReceive(TObexPacket& aPacket);
		virtual void OnError(TInt aError);
		virtual void OnTransportUp();
		virtual void OnTransportDown();
		TInt PrepareConnectPacket(TObexPacket& aPacket);	
		TInt ParseConnectPacket(TObexPacket& aPacket);	
		TInt AddConnectionIDHeader(TObexPacket& aPacket);
		TInt PrepareFinalChallResponse(TObexPacket& aPacket, TConnectState& aNextState);
		TBool CheckForConnectionID(CObexBaseObject& aObject);
		void CheckTarget(TConnectState& aNextState, TInt& aRetVal);
		void ResetConnectionID();
		void SetConnectionID(TUint32 aConnectionID);
		TUint32 ConnectionID();

	private:
		MObexServerNotify* iOwner;
		TBool iEnabled;
		CObexBaseObject* iTransObject;
		CObexBaseObject* iSpecObject;
		TBool iSpecDone;
		TBool iTargetReceived;
		TTargetChecking iTargetChecking;
		TUint32 iConnectionID; 
		TBool iConnectionIdSet;
		};

	class MObexServerNotify
	/** OBEX server notification interface.

	Any service that provides OBEX server functionality must implement this interface 
	to receive notifications of asynchronous events from the server.

	The CObexServer object handles the protocol side of an OBEX server session, 
	while this class provides the server policy for a particular session.

	CObexServer is a friend of this class, hence member functions are private. 

	@publishedAll
	@released
	*/
		{
	friend class CObexServer;

	private:
		/** Called if an OBEX protocol error occurs.
		
		It is only called for fatal errors that cause the OBEX connection to terminate. 
		An error that does not terminate the connection, for example the server issuing 
		a semantically valid, but unrecognised command, will not be indicated.
		
		@param aError Error code that describes the OBEX error. OBEX specific error 
		codes are listed from KErrIrObexClientNoDevicesFound. 
		
		@publishedAll
		@released
		*/
		virtual void ErrorIndication(TInt aError) =0;
		
		/** Called when the underlying socket transport connection is made from a remote 
		client to the server.
		
		Note that this does not, however, indicate an OBEX connection has been successfully 
		established.
		
		You can define any low-level connection policy here. It is also a good place 
		to set up the local connection information (CObex::LocalInfo()), if any non-defaults 
		are required. 

		@publishedAll
		@released
		*/
		virtual void TransportUpIndication() =0;
		
		/** Called when the transport connection is dropped (by either party).
		
		It is called whether the OBEX connection was gracefully disconnected or not. 
		The function is the definitive place for disconnection processing.
		
		@publishedAll
		@released
		*/
		virtual void TransportDownIndication() =0;
		
		/** Called when an OBEX connection is made from a remote client.
		
		Override this function to provide any extra OBEX connection processing.
		
		@param aRemoteInfo Connection information supplied by that remote machine
		@param aInfo Further information about the requested connection (reserved)
		@return System wide error code that indicates the success of the connection
		
		@publishedAll
		@released
		*/
		virtual TInt ObexConnectIndication(const TObexConnectInfo& aRemoteInfo, const TDesC8& aInfo) =0;
		
		/** Called on a (graceful) OBEX disconnection by the client.
		
		Override this to provide any extra processing OBEX disconnection processing.
		
		Note that this indication will not be raised if the remote machine simply 
		drops the transport connection. However, ErrorIndication() will be called 
		if the disconnection is unexpected/ invalid (i.e. another operation was in 
		progress at the time). In all cases, TransportDownIndication() will be called.
		
		@param aInfo Contains information about the disconnection (reserved) 
		
		@publishedAll
		@released
		*/
		virtual void ObexDisconnectIndication(const TDesC8& aInfo) =0;
		
		/** Called on receipt of the first packet of a (valid) put request. 
		
		It is called before any parsing of the packet is performed, simply to establish 
		whether this server is interested in receiving objects at all.
		
		Note if the returned object cannot be initialised for receiving (e.g. a temporary 
		file could not be created for a CObexFileObject), ERespInternalError is returned 
		to the client.
		
		@return CObexBaseObject-derived object, which the object being put will be 
		parsed into. If this is NULL,ERespForbidden is returned to the client. 
		
		@publishedAll
		@released
		*/
		virtual CObexBufObject* PutRequestIndication() =0;
		
		/** Called on receipt of every packet of an OBEX PUT operation.
		
		It will always be preceded by a PutRequestIndication(). The object returned 
		by the request indication will be updated to reflect all the information received 
		concerning the object which the client is sending, from packets up to and 
		including the current one. 
		
		You can use this function to provide periodic user notification on the progress 
		of the transfer (noting that the Length attribute may take an arbitrary number 
		of packets to become non-zero, and the constraints on its accuracy). Due to 
		the nature of OBEX operations, where any header attribute can be sent at any 
		point in the transfer, this is also a good place to marshal the details of 
		a received object, and possibly prompt for action on the received object (e.g. 
		renaming on filename clashes).
		
		Note that this function could be hit quite heavily, in proportion to the size 
		of the object transferred. Therefore more consideration should be given to 
		the speed of execution of this function than that of the other indications.
		
		@return KErrNoneinstructs the server to allow the client to continue the put 
		operation. Any other value cancels the operation with an appropriate OBEX 
		server response code. 
		
		@publishedAll
		@released
		*/
		virtual TInt PutPacketIndication() =0;
		
		/** Called after the final put packet has been successfully received and parsed. 
		
		Note that there will not necessarily be a call to this function corresponding 
		to each PutRequestIndication() as, if an error occurs while the put is being 
		carried out, ErrorIndication() will be called instead.
		
		Before version 6.1, the return type was void.
		
		@return KErrNoneinstructs the remote client that the put completed successfully. 
		Any other value cancels the operation with an appropriate OBEX server response 
		code.
		
		@publishedAll
		@released
		*/
		virtual TInt PutCompleteIndication() =0;
		
		/** Called when a full get request has been received from the client. 
		
		aRequestedObject holds all the details about the object the remote client 
		has requested. Use this function to analyse the client's request, and return 
		a pointer to the object to be returned to the client, or NULL to return no 
		object. 
		
		If NULL is returned, the server will send ERespForbidden to the client; if 
		an error occurs in returning the object, ERespInternalError is returned, otherwise 
		the returned object is sent back to the client.
		
		@param aRequiredObject Details about the object the remote client has requested
		@return Object to return to the client 
		
		@publishedAll
		@released
		*/
		virtual CObexBufObject* GetRequestIndication(CObexBaseObject *aRequiredObject) =0;
		
		/** Called for every packet of get reply sent by the server back to the client. 
		
		The function is only called while an object is being sent to the client, not 
		while the client is providing its initial specification for the object it 
		requires. 
		
		You can use this function to provide user notification on the object being 
		sent, and its progress. As with PutPacketIndication(), you should consider 
		that this function might get called often, especially for large objects and 
		small OBEX packet sizes, so the speed of execution here is important.
		
		@return KErrNone to continue sending the object, or any other error code to 
		cancel the operation 
		
		@publishedAll
		@released
		*/
		virtual TInt GetPacketIndication() =0;
		
		/** Called when the final packet of the object has been returned to the client.
		
		Note like PutCompleteIndication(), this function might not be called for each 
		GetRequestIndication(), if the operation is interrupted by an error.
		
		Before version 6.1, the return type was void.
		
		@return KErrNoneinstructs the remote client that the get completed successfully. 
		Any other value cancels the operation with an appropriate OBEX server response 
		code. 
		
		@publishedAll
		@released
		*/
		virtual TInt GetCompleteIndication() =0;
		
		/** Called when an OBEX SETPATH command is received by the server. 
		
		@param aPathInfo SETPATH command parameters
		@param aInfo Not currently used
		@return System wide error code indicating the success of the setpath command 
		
		@publishedAll
		@released
		*/
		virtual TInt SetPathIndication(const CObex::TSetPathInfo& aPathInfo, const TDesC8& aInfo) =0;
		
		/** Called when an abort packet is received from the client. 
		
		An OBEX abort command simply cancels the current operation, and does not necessarily 
		have to cause the connection to be dropped. On return, a ERespSuccess packet 
		is sent to the client. 
		
		@publishedAll
		@released
		*/
		virtual void AbortIndication() =0;
		};



	//if these codes are extended due to a IRObex spec update ensure 
	//that the TInt immediately below are updated 
	//and the default in the method IrOBEXUtil::ObexResponse is also updated

	enum TObexResponse  
	/** OBEX response code values.

	Descriptions of response codes are as given in the OBEX standard. 

	@publishedAll
	@released
	*/
		{ 
		/** Continue */
		ERespContinue			= 0x10,
		/** OK, Success */
		ERespSuccess			= 0x20,
		/** Created */
		ERespCreated			= 0x21,
		/** Accepted */
		ERespAccepted			= 0x22,
	    /** Non-Authoritative Information. */
		ERespNonAuthInfo		= 0x23,
	    /** No Content */
		ERespNoContent			= 0x24,
	    /** Reset Content */
		ERespResetContent		= 0x25,
	    /** Partial Content */
		ERespPartialContent		= 0x26,
	    /** Multiple choices. */
		ERespMultipleChoices	= 0x30,
	    /** Permanently moved */
		ERespMovedPerm			= 0x31,
	    /** Temporarily moved */
		ERespMovedTemp			= 0x32,
	    /** See other */
		ERespSeeOther			= 0x33,
	    /** Not modified */
		ERespNotModified		= 0x34,
	    /** Use proxy */
		ERespUseProxy			= 0x35,
		/** Bad Request- server couldn't understand request */
		ERespBadRequest			= 0x40,
		/** Unauthorized */
		ERespUnauthorized		= 0x41,
		/** Payment required */
		ERespPaymentRequired	= 0x42,
		/** Forbidden - operation is understood but refused */
		ERespForbidden			= 0x43,
		/** Not Found */
		ERespNotFound			= 0x44,
		/** Method not allowed */
		ERespMethodNotAllowed	= 0x45,
		/** Not Acceptable */
		ERespNotAcceptable		= 0x46,
	    /** Proxy authentication required. */
		ERespProxyAuthenReqd	= 0x47,
		/** Request Time Out */
		ERespTimedOut			= 0x48,
		/** Conflict */
		ERespConflict			= 0x49,
	    /** Gone */
		ERespGone				= 0x4A,
	    /** Length required */
		ERespLengthReqd			= 0x4B,
	    /** Pre-condition failed */
		ERespPreCondFailed		= 0x4C,
	    /** Entity is too large */
		ERespReqEntityTooLarge	= 0x4D,
	    /** URL is too large. */
		ERespReqURLTooLarge		= 0x4E,
	    /** The media type is not supported. */
		ERespUnsupMediaType		= 0x4F,
		/** Internal Server Error */
		ERespInternalError		= 0x50,
		/** Not Implemented */
		ERespNotImplemented		= 0x51,
	    /** Bad gateway */
		ERespBadGateway			= 0x52,
	    /** Service unavailable */
		ERespServiceUnavail		= 0x53,
	    /** Gateway has timed out */
		ERespGatewayTimeout		= 0x54,
	    /** HTTP version is not supported. */
		ERespHTTPVerNotSupp		= 0x55,
	    /** The database is full */
		ERespDatabaseFull		= 0x60,
	    /** The database is currently locked. */
		ERespDatabaseLocked		= 0x61,
		/** Service Unavailable */
		ERespServiceUnavailable = 0xD3,
		};


	//some error codes to be used specifically by the client
	//these shall be mapped directly to OBEX defined error codes.

	/** @publishedAll @released */
	const TInt KErrIrObexRespBase = - 5500; //must not use as not in our allocated range
	/** @publishedAll @released */
	const TInt KErrIrObexRespSuccess		= KErrIrObexRespBase - ERespSuccess;			//-5532 returns 0x20 (0xA0)
	/** @publishedAll @released */
	const TInt KErrIrObexRespCreated		= KErrIrObexRespBase - ERespCreated;			//-5533 returns 0x21 (0xA1)
	/** @publishedAll @released */
	const TInt KErrIrObexRespAccepted		= KErrIrObexRespBase - ERespAccepted;			//-5534 returns 0x22 (0xA2)
	/** @publishedAll @released */
	const TInt KErrIrObexRespNonAuthInfo	= KErrIrObexRespBase - ERespNonAuthInfo;		//-5535 returns 0x23 (0xA3)
	/** @publishedAll @released */
	const TInt KErrIrObexRespNoContent		= KErrIrObexRespBase - ERespNoContent;			//-5536 returns 0x24 (0xA4)
	/** @publishedAll @released */
	const TInt KErrIrObexRespResetContent	= KErrIrObexRespBase - ERespResetContent;		//-5537 returns 0x25 (0xA5)
	/** @publishedAll @released */
	const TInt KErrIrObexRespPartialContent = KErrIrObexRespBase - ERespPartialContent;		//-5538 returns 0x26 (0xA6)
	/** @publishedAll @released */
	const TInt KErrIrObexRespMultipleChoices = KErrIrObexRespBase - ERespMultipleChoices;	//-5548 returns 0x30 (0xB0)
	/** @publishedAll @released */
	const TInt KErrIrObexRespMovedPerm		= KErrIrObexRespBase - ERespMovedPerm;			//-5549 returns 0x31 (0xB1)
	/** @publishedAll @released */
	const TInt KErrIrObexRespMovedTemp		= KErrIrObexRespBase - ERespMovedTemp;			//-5550 returns 0x32 (0xB2)
	/** @publishedAll @released */
	const TInt KErrIrObexRespSeeOther		= KErrIrObexRespBase - ERespSeeOther;			//-5551 returns 0x33 (0xB3)
	/** @publishedAll @released */
	const TInt KErrIrObexRespNotModified	= KErrIrObexRespBase - ERespNotModified;		//-5552 returns 0x34 (0xB4)
	/** @publishedAll @released */
	const TInt KErrIrObexRespUseProxy		= KErrIrObexRespBase - ERespUseProxy;			//-5553 returns 0x35 (0xB5)
	/** @publishedAll @released */
	const TInt KErrIrObexRespBadRequest		= KErrIrObexRespBase - ERespBadRequest;			//-5564 returns 0x40 (0xC0)
	/** @publishedAll @released */
	const TInt KErrIrObexRespUnauthorized	= KErrIrObexRespBase - ERespUnauthorized;		//-5565 returns 0x41 (0xC1)
	/** @publishedAll @released */
	const TInt KErrIrObexRespPaymentRequired = KErrIrObexRespBase - ERespPaymentRequired;	//-5566 returns 0x42 (0xC2)
	/** @publishedAll @released */
	const TInt KErrIrObexRespForbidden		= KErrIrObexRespBase - ERespForbidden;			//-5567 returns 0x43 (0xC3)
	/** @publishedAll @released */
	const TInt KErrIrObexRespNotFound		= KErrIrObexRespBase - ERespNotFound;			//-5568 returns 0x44 (0xC4)
	/** @publishedAll @released */
	const TInt KErrIrObexRespMethodNotAllowed = KErrIrObexRespBase - ERespMethodNotAllowed;	//-5569 returns 0x45 (0xC5)
	/** @publishedAll @released */
	const TInt KErrIrObexRespNotAcceptable	= KErrIrObexRespBase - ERespNotAcceptable;		//-5570 returns 0x46 (0xC6)
	/** @publishedAll @released */
	const TInt KErrIrObexRespProxyAuthenReqd = KErrIrObexRespBase - ERespProxyAuthenReqd;	//-5571 returns 0x47 (0xC7)
	/** @publishedAll @released */
	const TInt KErrIrObexRespTimedOut		= KErrIrObexRespBase - ERespTimedOut;			//-5572 returns 0x48 (0xC8)
	/** @publishedAll @released */
	const TInt KErrIrObexRespConflict		= KErrIrObexRespBase - ERespConflict;			//-5573 returns 0x49 (0xC9)
	/** @publishedAll @released */
	const TInt KErrIrObexRespGone			= KErrIrObexRespBase - ERespGone;				//-5574 returns 0x4A (0xCA)
	/** @publishedAll @released */
	const TInt KErrIrObexRespLengthReqd		= KErrIrObexRespBase - ERespLengthReqd;			//-5575 returns 0x4B (0xCB)
	/** @publishedAll @released */
	const TInt KErrIrObexRespPreCondFailed	= KErrIrObexRespBase - ERespPreCondFailed;		//-5576 returns 0x4C (0xCC)
	/** @publishedAll @released */
	const TInt KErrIrObexRespReqEntityTooLarge = KErrIrObexRespBase - ERespReqEntityTooLarge;//-5577 returns 0x4D (0xCD)
	/** @publishedAll @released */
	const TInt KErrIrObexRespReqURLTooLarge	= KErrIrObexRespBase - ERespReqURLTooLarge;		//-5578 returns 0x4E (0xCE)
	/** @publishedAll @released */
	const TInt KErrIrObexRespUnsupMediaType = KErrIrObexRespBase - ERespUnsupMediaType;		//-5579 returns 0x4F (0xCF)
	/** @publishedAll @released */
	const TInt KErrIrObexRespInternalError	= KErrIrObexRespBase - ERespInternalError;		//-5580 returns 0x50 (0xD0)
	/** @publishedAll @released */
	const TInt KErrIrObexRespNotImplemented = KErrIrObexRespBase - ERespNotImplemented;		//-5581 returns 0x51 (0xD1)
	/** @publishedAll @released */
	const TInt KErrIrObexRespBadGateway		= KErrIrObexRespBase - ERespBadGateway;			//-5582 returns 0x52 (0xD2)
	/** @publishedAll @released */
	const TInt KErrIrObexRespServiceUnavail = KErrIrObexRespBase - ERespServiceUnavail;		//-5583 returns 0x53 (0xD3)
	/** @publishedAll @released */
	const TInt KErrIrObexRespGatewayTimeout = KErrIrObexRespBase - ERespGatewayTimeout;		//-5584 returns 0x54 (0xD4)
	/** @publishedAll @released */
	const TInt KErrIrObexRespHTTPVerNotSupp = KErrIrObexRespBase - ERespHTTPVerNotSupp;		//-5585 returns 0x55 (0xD5)
	/** @publishedAll @released */
	const TInt KErrIrObexRespDatabaseFull	= KErrIrObexRespBase - ERespDatabaseFull;		//-5596 returns 0x60 (0xE0)
	/** @publishedAll @released */
	const TInt KErrIrObexRespDatabaseLocked = KErrIrObexRespBase - ERespDatabaseLocked;		//-5597 returns 0x61 (0xE1)

	#include <obex.inl>

#else //__OBEX_USER_DEFINED_HEADERS__

	#include "obextypes.h"
	#include "obexconstants.h"
	#include "obexbaseobject.h"
	#include "obexobjects.h"
	#include "obexheaders.h"
	#include "obexbase.h"
	#include "obexclient.h"
	#include "obexserver.h"

#endif // __OBEX_USER_DEFINED_HEADERS__

#endif // OBEX_H
