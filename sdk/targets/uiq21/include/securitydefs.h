//
// SECURITYDEFS.H
//
// (c) Copyright 2001 Symbian Ltd

#ifndef __SECURITYDEFS_H__
#define __SECURITYDEFS_H__

#include <e32std.h>
#include <e32base.h>

///@file
/**@defgroup Securitydefs General Security Definitions */

///@{

/** Supported types of certificate format. Note these must be only 1
 * byte long as the file cert store only seralises them as 1 byte. */
enum TCertificateFormat
	{
    EX509Certificate    = 0x00,
    EWTLSCertificate    = 0x01,
	EX968Certificate    = 0x02,
	EUnknownCertificate = 0x0f,
	EX509CertificateUrl = 0x10,
	EWTLSCertificateUrl = 0x11,
	EX968CertificateUrl = 0x12
	};

/** What a key can be used for.
	The values this can take are defined in TKeyUsageVals
 */
typedef TInt TKeyUsage;

/** What a key is to be used for. These values can be ANDed together
 * if a key has several usages. EAllKeyUsages is used when searching
 * for all keys, rather than ones with a particular usage.
 * As these can be anded together, TKeyUsage is used to store them.*/
enum TKeyUsageVals
	{
    EDigitalSignature =  0x80000000,
    ENonRepudiation =  0x40000000,
    EKeyEncipherment =  0x20000000,
    EDataEncipherment =  0x10000000,
    EKeyAgreement =   0x08000000,
    EKeyCertSign =   0x04000000,
    ECRLSign =    0x02000000,
    EEncipherOnly =   0x01000000,
    EDecipherOnly =   0x00800000,
    EAllKeyUsages =   -1
	};

/** The owner of a certificate */
enum TCertificateOwnerType
	{
	ECACertificate,
	EUserCertificate,
	EPeerCertificate
	};

/** The length of a SHA1 hash */
const TInt KSHA1HashLengthBytes = 20;
/** A SHA1 hash */
typedef  TBuf8<KSHA1HashLengthBytes> TSHA1Hash;

//const TInt KMD5HashLengthBytes = 16;
//typedef TMD5Hash TBufC8<KMD5HashLengthBytes>;

/** A SHA 1 hash is also used as a key identifier */
typedef TSHA1Hash TKeyIdentifier;

/** Errors that can occur when validating a certificate chain */
enum TValidationError
	{
	//fatal errors
	EValidatedOK,		//well, except for this one
	EChainHasNoRoot,
	ESignatureInvalid,
	EDateOutOfRange,
	ENameIsExcluded,
	ENameNotPermitted,	//subtle difference here!
	ENotCACert,
	ECertificateRevoked,
	EUnrecognizedCriticalExtension,
	ENoBasicConstraintInCACert,
	ENoAcceptablePolicy,
	EPathTooLong,
	ENegativePathLengthSpecified,
	ENamesDontChain,
	ERequiredPolicyNotFound,
	EBadKeyUsage,
	//warnings: we can't tell if these are fatal or not, 'cos we lack the context
	ERootCertNotSelfSigned,
	ECriticalExtendedKeyUsage,
	ECriticalCertPoliciesWithQualifiers,
	ECriticalPolicyMapping
	};
///@}
#endif
