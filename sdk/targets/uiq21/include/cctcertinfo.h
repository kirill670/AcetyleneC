// CCTCertInfo.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __CCTCERTINFO_H__
#define __CCTCERTINFO_H__

#include <e32base.h>
#include <s32strm.h>

#include <securitydefs.h>
#include <ct/mcttokentype.h>
#include <ct/mcttoken.h>
#include <ct/mcttokenobject.h>

/** The UID of a CertInfo MCTTokenObject */
const TInt KCTObjectCertInfo = 0x101F50E6;

const TUint32 KMaxCertLabelLength = 64;
typedef TBuf<KMaxCertLabelLength> TCertLabel;

/** @ingroup interfaces */
/** @{ */

/** This class encapsulates information about a stored
	certificate. These are usualy returned by a cert store, to allow a
    client to query the contents of the store. */
class CCTCertInfo : protected CBase, public MCTTokenObject
	{
public:
	/** @name Construction. Note that these objects are normaly
		constructed by certificate stores, not by clients. */
	///@{
	/** Makes a new CCTCertInfo by copying an existing one.
		@param aCertInfo The cert info to copy
		@exception KErrNoMemory There is no memory to construct it.
	 */
	IMPORT_C static CCTCertInfo* NewL(const CCTCertInfo& aCertInfo);
	/** Makes a new CCTCertInfo by copying an existing one.
		This function leaves it on the cleanup stack.
		@param aCertInfo The cert info to copy
		@exception KErrNoMemory There is no memory to construct it.
	 */
	IMPORT_C static CCTCertInfo* NewLC(const CCTCertInfo& aCertInfo);
	/** Makes a new CCTCertInfo from its constituent parts.
		@param aLabel The certificate's label
		@param aFormat The certificate's format
		@param aCertificateOwnerType The owner type
		@param aSize The size of the certificate
		@param aSubjectKeyId The subject key ID
		@param aIssuerKeyId The issuer key ID
		@param aToken The token that the certificate is within.
		@param aCertificateId The ID within the object handle
		@exception KErrNoMemory There is no memory to construct it.
	 */
	IMPORT_C static CCTCertInfo* NewL(const TDesC& aLabel, TCertificateFormat aFormat,
		TCertificateOwnerType aCertificateOwnerType, TInt aSize,
		const TKeyIdentifier* aSubjectKeyId, const TKeyIdentifier* aIssuerKeyId,
		MCTToken& aToken, TInt aCertificateId);
	/** Makes a new CCTCertInfo from its constituent parts.
		This function leaves it on the cleanup stack.
		@param aLabel The certificate's label
		@param aFormat The certificate's format
		@param aCertificateOwnerType The owner type
		@param aSize The size of the certificate
		@param aSubjectKeyId The subject key ID
		@param aIssuerKeyId The issuer key ID
		@param aToken The token that the certificate is within.
		@param aCertificateId The ID within the object handle
		@exception KErrNoMemory There is no memory to construct it.
	 */
	IMPORT_C static CCTCertInfo* NewLC(const TDesC& aLabel, TCertificateFormat aFormat,
		TCertificateOwnerType aCertificateOwnerType, TInt aSize,
		const TKeyIdentifier* aSubjectKeyId, const TKeyIdentifier* aIssuerKeyId,
		MCTToken& aToken, TInt aCertificateId);
	/** Makes a new CCTCertInfo by internalising a previously externalised one.
		@param aStream The stream to read it in from
		@param aToken The token that it is within
		@exception KErrNoMemory There is no memory to construct it.
		@see ExternalizeL
		@see InternalizeL
	 */
	IMPORT_C static CCTCertInfo* NewL(RReadStream& aStream, MCTToken& aToken);
	/** Makes a new CCTCertInfo by internalising a previously externalised one.
		This function leaves it on the cleanup stack.
		@param aStream The stream to read it in from
		@param aToken The token that it is within
		@exception KErrNoMemory There is no memory to construct it.
		@see ExternalizeL
		@see InternalizeL
	 */
	IMPORT_C static CCTCertInfo* NewLC(RReadStream& aStream, MCTToken& aToken);
	///@}

	/** Returns the subject key ID */
	IMPORT_C const TKeyIdentifier& SubjectKeyId() const;
	/** Returns the issuer key ID */
	IMPORT_C const TKeyIdentifier& IssuerKeyId() const;
	/** Returns the certificate format */
	IMPORT_C TCertificateFormat CertificateFormat() const;
	/** Returns the owner type */
	IMPORT_C TCertificateOwnerType CertificateOwnerType() const;
	/** Returns the size. Note that when retrieving a certificate with
		MCertStore::Retrieve, you need a descriptor of the right
		size. This function is needed for allocating the right
		descriptor before retrieving the certificate.*/
	IMPORT_C TInt Size() const;
	/** Returns the object handle. @see TCTTokenObjectHandle */
	IMPORT_C TCTTokenObjectHandle Handle() const;

 public:	///@name from MCTTokenObject
	///@{
	/** @see MCTTokenObject::Label */
	virtual const TDesC& Label() const;
	/** @see MCTTokenObject::Token */
	virtual MCTToken& Token() const;
	/** @see MCTTokenObject::Type */
	virtual TUid Type() const;
	///@}

	/** Compares 2 cert infos */
	IMPORT_C TBool operator ==(const CCTCertInfo& aCertInfo) const;

	///@name Internalization/Externalization
	///@{
	/** Externalize. Writes the data out to a stream
		@param aStream The stream to write to 
	*/
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	/** Internalize. Reads the data from a stream 
		@param The stream to read from 
	*/
	IMPORT_C void InternalizeL(RReadStream& aStream);
	///@}
 protected:
	IMPORT_C virtual ~CCTCertInfo();
private:
	CCTCertInfo(MCTToken& aToken);
	CCTCertInfo(const TDesC& aLabel, TCertificateFormat aFormat,
		TCertificateOwnerType aCertificateOwnerType, 
		const TKeyIdentifier* aSubjectKeyId,
		const TKeyIdentifier* aIssuerKeyId,
		TInt aSize,
		MCTToken& aToken, TInt aCertificateId);
	CCTCertInfo(const CCTCertInfo& aCertInfo);
	void ConstructL(RReadStream& aStream);

private:
	TCertLabel iLabel;
	MCTToken& iToken;
	TInt iCertificateId;
	TCertificateFormat iFormat;
	TCertificateOwnerType iCertificateOwnerType;
	TInt iSize;
	TKeyIdentifier iSubjectKeyId;
	TKeyIdentifier iIssuerKeyId;
	};
///@}
#endif
