// ocsp.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// Header specifying client interface to the OCSP module.
// This module has been produced as part of the Software Install 6.2 project.

#ifndef __OCSP_H__
#define __OCSP_H__

#include <e32base.h>
#include <signed.h>
#include <f32file.h>
#include <unifiedcertstore.h>

#define KOCSPNonceBytes 16

class COCSPRequestCertInfo;
class COCSPResponseCertInfo;
class COCSPCertID;
class MOCSPTransport;
class COCSPResponse;
class COCSPTransportHandler;
class MOCSPAuthorisationScheme;
class COCSPTransaction;
class COCSPValidator;
class COCSPRequestCertInfo;
class COCSPResponseDecoder;

class CASN1EncBase;
class CASN1EncContainer;
class TASN1DecGeneric;

class CX509Certificate;
class CX509CertChain;
class CPKIXCertChain;

// Enums placed in OCSP namespace
namespace OCSP
	{
	// Globally-reserved error codes - range is -7601 to -7649
	enum 
		{
		KErrTransportFailure	= -7601,
		KErrInvalidURI			= -7602,
		KErrNoCertificates		= -7603
		};

	// What we think of the response, or why we haven't got one
	enum TStatus 
		{
		// Error in communication with server
		ETransportError = 1,

		// Internal problem processing response
		EClientInternalError = 2,

		// No OCSP server specified
		ENoServerSpecified = 3,

		// Invalid sever URI
		EInvalidURI = 4,

		// Problems understanding the response
		EMalformedResponse = 10,
		EUnknownResponseType = 11,
		EUnknownCriticalExtension = 12,

		// Unsuccessful responses from server
		EMalformedRequest = 20,
		EServerInternalError = 21,
		ETryLater = 22,
		ESignatureRequired = 23,
		EClientUnauthorised = 24,
			
		// Response validation failures
		EMissingCertificates = 30,
		EResponseSignatureValidationFailure = 31,
		
		// Time problems
		EThisUpdateTooLate = 40,
		EThisUpdateTooEarly = 41,
		ENextUpdateTooEarly = 42,
		ECertificateNotValidAtValidationTime = 43,

		// Nonce error
		ENonceMismatch = 50,

		// Response sufficiently valid to use - clients to decide if
		// missing nonce is sufficiently serious to require rejection
		EMissingNonce = 51,

		EValid = 100,
		};

	// What does the response say about the certificates?
	// IMPORTANT: Do not change the order these are in
	enum TResult
		{
		EGood = 10, EUnknown = 20, ERevoked = 30
		};
	}
		

class TOCSPOutcome
	{
public:
	TOCSPOutcome(OCSP::TStatus aStatus, OCSP::TResult aResult)
		: iStatus(aStatus), iResult(aResult) {};

	TOCSPOutcome()
		: iStatus(OCSP::EClientInternalError), iResult(OCSP::EUnknown) {};

	TBool operator==(const TOCSPOutcome& aRhs) const
		{ return iStatus == aRhs.iStatus && iResult == aRhs.iResult; }

	OCSP::TStatus iStatus;
	OCSP::TResult iResult;
	};


/**
 * Represents an OCSP protocol request.
 */

class COCSPRequest : public CBase
	{
public:

	/**
	 * Get the nonce used in the request.  Returns NULL if a nonce was not used.
	 */

	IMPORT_C const TDesC8* Nonce() const;

	/**
	 * Get the number of certificates used in a response
	 */
	
	IMPORT_C TInt CertCount() const;

	/**
	 * Get a COCSPRequestCertInfo object containing details about one of the
	 * certificates present in the request.
	 */

	IMPORT_C const COCSPRequestCertInfo& CertInfo(TUint aIndex) const;
	
public:

	// Not exported
	static COCSPRequest* NewLC(TBool aUseNonce);
	~COCSPRequest();
	void AddCertificateL(const CX509Certificate& aSubject,
						 const CX509Certificate& aIssuer);

private:

	COCSPRequest();
	void ConstructL(TBool aUseNonce);

	HBufC8* iNonce;
	RPointerArray<const COCSPRequestCertInfo> iCertInfos;
	};

/**
 * Information about a certificate sent as part of an OCSP request.
 */

class COCSPRequestCertInfo : public CBase
	{
public:

	/**
	 * Get the certificate present in the request.
	 */
	
	IMPORT_C const CX509Certificate& Subject() const;

	/**
	 * Get the issuer of the certificate present in the request.
	 */
	
	IMPORT_C const CX509Certificate& Issuer() const;

public:

	// Not exported
	static COCSPRequestCertInfo* NewLC(
		const CX509Certificate& aSubject,
		const CX509Certificate& aIssuer);

	~COCSPRequestCertInfo();

	const COCSPCertID& CertID() const;

 private:
	
	COCSPRequestCertInfo(const CX509Certificate& aIssuer,
						 const CX509Certificate& aSubject);
	void ConstructL();

private:

	const CX509Certificate& iSubject;
	const CX509Certificate& iIssuer;
	COCSPCertID* iCertID;
	};


/**
 * Represents an OCSP protocol response.
 */

class COCSPResponse : public CSignedObject
	{
public:

	/**
	 * Get the number of certificates statuses present in the response.
	 */

	IMPORT_C TInt CertCount() const;

	/**
	 * Get a COCSPResponseCertInfo object containing details about one of the
	 * certificate statuses present in the response.
	 */

	IMPORT_C const COCSPResponseCertInfo& CertInfo(TUint aIndex) const;

	/**
	 * Get the producedAt time for the response.
	 */

	IMPORT_C TTime ProducedAt() const;

	/**
	 * Get the archiveCutoff time for the response, or NULL if it was not present.
	 */

	IMPORT_C const TTime* ArchiveCutoff() const;

public:

	// This class is created and initialised by the response decoder
	friend class COCSPResponseDecoder;
	
	~COCSPResponse();

	/**
	 * Get the index for the given cert, or KErrNotFound.
	 */
	
	TInt Find(const COCSPCertID& aCertID) const;

	// Enums to use in DataElementEncoding
	enum
		{
		ECertificateChain,
		ENonce,
		EResponderIDName,    // Only one of the ResponderIDs won't be NULL
		EResponderIDKeyHash
		};

  	// From CSignedObject
  	const TPtrC8* DataElementEncoding(const TUint aIndex) const;

private:

	COCSPResponse();

  	// From CSignedObject
	const TPtrC8 SignedDataL() const;
	void InternalizeL(RReadStream& aStream);

private:

	// Time of response, and of archiveCutoff extension (if present)
	TTime iProducedAt;
	TTime* iArchiveCutoff;

	// Value of nonce in response extension (if present)
	TPtrC8 iNonce;

	// Point to the signing certificates in the response
	TPtrC8 iSigningCerts;

	// Point to the signed portion of the data
	TPtrC8 iSignedData;

	// There are two ways the responder ID can be specified - only
	// one of these will be used
	TPtrC8 iResponderIDName;
	TPtrC8 iResponderIDKeyHash;

	RPointerArray<COCSPResponseCertInfo> iCertInfos;
	};


/**
 * Information about a certificate status, as given in OCSP response
 * singleResponse data item.
 */

class COCSPResponseCertInfo : public CBase
	{
public:
	
	IMPORT_C OCSP::TResult Status() const;
	IMPORT_C TTime ThisUpdate() const;
	IMPORT_C const TTime* NextUpdate() const;     // NULL if nextUpdate not set
	IMPORT_C const TTime* RevocationTime() const; // NULL if not revoked

public:
	
	static COCSPResponseCertInfo* NewLC(CArrayPtr<TASN1DecGeneric>& items);
	~COCSPResponseCertInfo();
	COCSPCertID& CertID() const;
	
private:
	void ConstructL(CArrayPtr<TASN1DecGeneric>& items);

private:
	OCSP::TResult iStatus;

	TTime iThisUpdate;
	TTime* iNextUpdate;
	TTime* iRevocationTime;

	COCSPCertID* iCertID;
	};


// Base class interface for authorisation schemes, for plugging into the validator object
class MOCSPAuthorisationScheme
	{
public:
	virtual ~MOCSPAuthorisationScheme() {};

	// Validate the certificate chain and signature on the response signed object
	virtual void Validate(OCSP::TStatus& aOCSPStatus, COCSPResponse& aResponse, 
		const TTime aValidationTime, TRequestStatus& aStatus) = 0;

	virtual void CancelValidate() = 0;
	};


class CPKIXValidationResult;
class CUnifiedCertStore;
class CCertAttributeFilter;

// Authorisation scheme taking a cert store UID, and allowing those cert chains
// with a root cert in the cert store valid for that UID
class COCSPDirectAuthorisationScheme : public CActive, public MOCSPAuthorisationScheme
	{
public:
	IMPORT_C static COCSPDirectAuthorisationScheme* NewLC(const TUid& aCertStoreUid);

	~COCSPDirectAuthorisationScheme();

	// From MOCSPAuthorisationScheme
	void Validate(OCSP::TStatus& aOCSPStatus, COCSPResponse& aResponse, 
		const TTime aValidationTime, TRequestStatus& aStatus);
	void CancelValidate();

protected:
	virtual void DoCancel();
	virtual void RunL();
	virtual TInt RunError(TInt aError);
private:
	void ConstructL();
	COCSPDirectAuthorisationScheme(const TUid& aCertStoreUid);

	TBool StartAsyncValidateL();
	// Return indicates whether that stage was passed OK
	TBool MakeCertChainL(const TDesC8& aCertChainData);
	TBool ValidateSignatureL();
	
	// async now
	void ValidateFromRootsL();
	void ValidateCertChainL(); 
	
	TBool CertSignedResponseL(const CX509Certificate& aCert);
	TBool CertMatchesResponderIDL(const CX509Certificate& aCert);

	// handlers for async event completion
	void OnInitialValidateL();
	void OnValidateCertChainL();
	void OnInitCertStoreL();
	void OnListCertEntriesL();
	void OnRetrieveNextL();
	void OnRetrievingEntryL();


	TBool UnexpectedErr(TInt aError); // some errors are interesting for us

private:
	TUid iCertStoreUid;

	COCSPResponse* iResponse;

	CPKIXCertChain* iCertChain;

	TRequestStatus* iValidateStatus;
	CPKIXValidationResult* iPKIXResult;
	OCSP::TStatus* iOCSPStatus;

	enum TStatus
		{
		EInitialValidate,   // fake state for initial non-async validation
		EValidateCertChain, // waiting for cert chain validation to complete
		EInitCertStore,     // waiting for cert store init to complete    
		EListCertEntries,   // waiting listing to complete
		ERetrieveNext,      // get next cert entry
		ERetrievingEntry,   // waiting for entry retrieval to complete
		};
	TStatus iState;

	CUnifiedCertStore* iCertStore;
	CCertAttributeFilter* iCertFilter;
	RMPointerArray<CCTCertInfo> iCertStoreEntries;
	HBufC8* iEncodedCertBuf;
	TPtr8* iEncodedCertPtr;

	RFs iFs;

	TInt iCurEntry; // while async processing 509 certs, points to the current one

	TTime iValidationTime;
	};


/**
 * Interface through which the OCSP module sends requests to the outside world.
 * Normally, the appropriate concrete objects are made automatically, depending
 * on the URI, and so clients don't have to deal with this.  However, clients
 * can override the automatically created object by specifying their own
 * transport object instead.
 */

class MOCSPTransport
	{
public:

	virtual ~MOCSPTransport() {};

	/**
	 * Send request data to a URI.  This is an asynchronous method.
	 */
	
	virtual void SendRequest(const TDesC8& aURI,
							 const TDesC8& aRequest,
							 TRequestStatus& aStatus) = 0;

	/**
	 * Cancel the request.
	 */
	
	virtual void CancelRequest() = 0;

	// The following methods will only be called after the aStatus above is completed

	/**
	 * Get the response data.  Panic if completion gave an error.
	 */
	
	virtual TPtrC8 GetResponse() const = 0;	
	};


/**
 * Specifies paremeters needed to perform revocation checking.  The important
 * things to set are the certificates to be checked all - all the other
 * parameters have defaults.
 */

class COCSPParameters : public CBase
	{
public:
	
	/**
	 * Create a new parameters object.
	 */

	IMPORT_C static COCSPParameters* NewL();
	IMPORT_C static COCSPParameters* NewLC();

 	/**
	 * A static method, clients can use this to determine whether a URI is going
	 * to be accepted by us (ie we have a transport scheme to support it).
	 */
	
	IMPORT_C static TBool SupportedURIL(const TDesC8& aURI);
	
	/**
	 * Add a certificate chain to be checked.  Does not take ownership -
	 * certificates must not be destroyed until the OCSP check complete.
	 */

	IMPORT_C void AddCertificatesL(const CX509CertChain& aChain);

	/**
	 * Add a certificate to be checked.  Does not take ownership - certificates
	 * must not be destroyed until the OCSP check complete.
	 */

	IMPORT_C void AddCertificateL(const CX509Certificate& aSubject, const CX509Certificate& aIssuer);

	/**
	 * Set whether or not to use a nonce.  By default this is turned on.
	 */

	IMPORT_C void SetUseNonce(TBool aUseNonce);

	/**
	 * Set the URI of the OCSP responder to use.  The descriptor is copied.
	 *
	 * @param aURI The URI of the responder to use.
	 * @param aUseAIA Indicates whether to use the responder specified in
	 * certifcate AuthorityInfoAccess extensions in preference to the one given
	 * here.
	 */

	IMPORT_C void SetURIL(const TDesC8& aURI, TBool aUseAIA);

	/**
	 * Set the transport to use, rather than creating one based on the protocol
	 * in the URI.  This object takes ownership.
	 */

	IMPORT_C void SetTransport(MOCSPTransport* aTransport);

	/**
	 * Add an authorisation scheme - takes ownership if it doesn't leave.
	 * Clients must specify at least one such scheme, used to validate the signature
	 * on the response.
	 */

	IMPORT_C void AddAuthorisationSchemeL(MOCSPAuthorisationScheme* aScheme);

	/**
	 * Specify the authorisation time (optional - uses producedAt time from response otherwise).
	 */

	IMPORT_C void SetValidationTimeL(const TTime& aValidationTime);

	/**
	 * Specify the maximum age of the thisUpdate field in seconds (zero => don't check).
	 */

	IMPORT_C void SetMaxStatusAgeL(TUint aMaxAge);

	/**
	 * Specify how much leeway we allow when comparing times.
	 */

	IMPORT_C void SetTimeLeewayL(TUint aLeewaySeconds);

public:
	
	// Not exported

	~COCSPParameters();
	TUint CertCount() const;
	const CX509Certificate& SubjectCert(TUint aIndex) const;
	const CX509Certificate& IssuerCert(TUint aIndex) const;
	TBool UseNonce() const;
	const TDesC8* DefaultURI() const;
	TBool UseAIA() const;
	MOCSPTransport* Transport() const;
	TUint AuthSchemeCount() const;
	MOCSPAuthorisationScheme& AuthScheme(TUint aIndex) const;
	const TTime* ValidationTime() const;
	const TUint* MaxStatusAge() const;
	const TUint* TimeLeeway() const;

private:

	COCSPParameters();
	
private:

	RPointerArray<CX509Certificate>			iSubjectCerts;
	RPointerArray<CX509Certificate>			iIssuerCerts;	
	TBool									iUseNonce;
	TDesC8*									iDefaultURI;
	MOCSPTransport*							iTransport;
	TBool									iUseAIA;
	RPointerArray<MOCSPAuthorisationScheme> iAuthSchemes;
	TTime*									iValidationTime;
	TUint*									iMaxStatusAge;
	TUint*									iTimeLeeway;
	};


/**
 * Checks the revocation state of one or more certificates.
 *
 * The current implementation makes one OCSP request for every certificate
 * checked - future impelementations may check multiple certificates with a
 * single request.
 */

class COCSPClient : public CActive
	{
public:

	/**
	 * Create a new OCSP client.
	 * 
	 * @param params An object describing the parameters for the check.  This
	 * method takes ownership if it does not leave.
	 */

	IMPORT_C static COCSPClient* NewL(const COCSPParameters* aParams);
	
	~COCSPClient();

	/**
	 * Start the checker - this is an asynchronous method.
	 */

	IMPORT_C void Check(TRequestStatus& aStatus);

	/**
	 * Cancel checking.
	 */

	IMPORT_C void CancelCheck(void);

	/**
	 * Get the summary result of the check.  If any certificates were revoked,
	 * this returns ERevoked.  If no certificates were revoked, but if there
	 * were any errors communicating with ocsp servers or any certs had unknown
	 * status, this returns EUnknown.  Otherwise it returns EGood. 
	 * Panics if the check has not been run, or is not complete.
	 */

	IMPORT_C OCSP::TResult SummaryResult(void) const;

	/**
	 * Get the number of transactions made.
	 * Panics if the check has not been run, or is not complete.
	 */

	IMPORT_C TInt TransactionCount(void) const;

	/** 
	 * Get the request object for a specified transaction.
	 * Panics if the check has not been run, is not complete, or the index is invalid.
	 */

	IMPORT_C const COCSPRequest& Request(TInt aIndex) const;

	/**
	 * Get the outcome for an individual transaction.
	 */

	IMPORT_C const TOCSPOutcome& Outcome(TInt aIndex) const;

	/** 
	 * Get the response object for a specified transaction.  If there was an
	 * error sending the request, this may return NULL for the corresponding
	 * response.
	 * Panics if the check has not been run, is not complete, or the index is invalid.
	 */

	IMPORT_C const COCSPResponse* Response(TInt aIndex) const;

public:

	virtual void RunL();
	virtual TInt RunError(TInt aErr);
	virtual void DoCancel();

private:
	
	COCSPClient();
	void ConstructL(const COCSPParameters* aParams);
	void Destroy();
	void DoCheckL();
	void SendRequestL();
	void DoSendRequestL();
	void ValidateResponseL();
	void HandleResponseReceivedL();
	void HandleResponseValidatedL();
	const TDesC8* ServerURIL(const CX509Certificate& aCert);
	MOCSPTransport& GetTransportL(const TDesC8& aURI);
	void HandleTransactionErrorL(OCSP::TStatus aStatus);

	enum TState
		{
		EInitial,
		ESendingRequest,		// Request is being sent to server
		EValidatingResponse,	// Request is being validated
		EHaveResult,			// Validation complete
		EError					// We got an error
		};

	TState							iState;	
	TRequestStatus*					iClientStatus;
	const COCSPParameters*			iParams;
	TDesC8*							iURI;
	MOCSPTransport*					iTransport;
	COCSPTransaction*				iTransaction;
	RPointerArray<COCSPRequest>		iRequests;
	RPointerArray<COCSPResponse>	iResponses;
	COCSPValidator*					iValidator;
	RArray<TOCSPOutcome>			iOutcomes;
	OCSP::TResult					iSummaryResult;
	};


#endif // __OCSP_H__
