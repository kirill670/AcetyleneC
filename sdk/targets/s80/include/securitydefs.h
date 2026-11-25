//
// SECURITYDEFS.H
//
// (c) Copyright 2001 Symbian Ltd

#ifndef __SECURITYDEFS_H__
#define __SECURITYDEFS_H__

#include <e32std.h>
#include <e32base.h>

// //@file

//@defgroup Securitydefs General Security Definitions
//@{

// Old keystore interface, deprecated //////////////////////////////////////////

/**
 * What a key can be used for.
 * The values this can take are defined in TKeyUsageVals.
 *
 * @publishedAll
 * @deprecated
 */
typedef TInt TKeyUsage;

/**
 * What a key can be used for.
 *
 * These values can be ORed together if a key has several usages. EAllKeyUsages
 * is used when searching for all keys, rather than ones with a particular
 * usage.  As these can be combined, TKeyUsage is used to store them.
 *
 * @publishedAll
 * @deprecated
 */
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

// End of deprecated keystore API //////////////////////////////////////////////

/**
 * What a key can be used for - PKCS15 scheme.
 *
 * @publishedAll
 * @released
 */
enum TKeyUsagePKCS15
	{
	EPKCS15UsageEncrypt				= 0x001,
	EPKCS15UsageDecrypt				= 0x002,
	EPKCS15UsageSign				= 0x004,
	EPKCS15UsageSignRecover			= 0x008,
	EPKCS15UsageWrap				= 0x010,
	EPKCS15UsageUnwrap				= 0x020,	
	EPKCS15UsageVerify				= 0x040,
	EPKCS15UsageVerifyRecover		= 0x080,
	EPKCS15UsageDerive				= 0x100,
	EPKCS15UsageNonRepudiation		= 0x200,
	// Common combinations
	EPKCS15UsageEncryptWrap         = 0x011,
	EPKCS15UsageVerifyVerifyRecover = 0x0C0,
	EPKCS15UsageDecryptUnwrap       = 0x022,
	EPKCS15UsageSignSignRecover     = 0x00C,
	EPKCS15UsageVerifyEncrypt       = 0x0D1,
	EPKCS15UsageSignDecrypt         = 0x02E,
	// For use in filters to return all keys
	EPKCS15UsageAll					= 0xffffffff,
	EPKCS15UsageNone				= 0x00000000
	};

inline TKeyUsagePKCS15 operator|(TKeyUsagePKCS15 aLeft, TKeyUsagePKCS15 aRight);
inline TKeyUsagePKCS15 operator&(TKeyUsagePKCS15 aLeft, TKeyUsagePKCS15 aRight);
inline const TKeyUsagePKCS15& operator|=(TKeyUsagePKCS15& aLeft, TKeyUsagePKCS15 aRight);
inline const TKeyUsagePKCS15& operator&=(TKeyUsagePKCS15& aLeft, TKeyUsagePKCS15 aRight);

/**
 * What a key can be used for - X509 scheme.
 *
 * @publishedAll
 * @released
 */
enum TKeyUsageX509
	{
	EX509UsageDigitalSignature		= 0x80000000,
	EX509UsageNonRepudiation		= 0x40000000,
	EX509UsageKeyEncipherment		= 0x20000000,
	EX509UsageDataEncipherment		= 0x10000000,
	EX509UsageKeyAgreement			= 0x08000000,
	EX509UsageKeyCertSign			= 0x04000000,
	EX509UsageCRLSign				= 0x02000000,
	EX509UsageEncipherOnly			= 0x01000000,
	EX509UsageDecipherOnly			= 0x00800000,
	// Values for commonly permitted combinations
	EX509UsageAnySign               = 0x86000000,
	EX509UsageAllEncipher           = 0x30000000,
	EX509UsageAllSignEncipher       = 0xB6000000,
	/// For use in filters to return all keys
	EX509UsageAll					= 0xffffffff,
	EX509UsageNone					= 0x00000000
	};

inline TKeyUsageX509 operator|(TKeyUsageX509 aLeft, TKeyUsageX509 aRight);
inline TKeyUsageX509 operator&(TKeyUsageX509 aLeft, TKeyUsageX509 aRight);
inline const TKeyUsageX509& operator|=(TKeyUsageX509& aLeft, TKeyUsageX509 aRight);
inline const TKeyUsageX509& operator&=(TKeyUsageX509& aLeft, TKeyUsageX509 aRight);

IMPORT_C TKeyUsageX509 KeyUsagePKCS15ToX509(TKeyUsagePKCS15 aUsage);
IMPORT_C TKeyUsagePKCS15 KeyUsageX509ToPKCS15Private(TKeyUsageX509 aUsage);
IMPORT_C TKeyUsagePKCS15 KeyUsageX509ToPKCS15Public(TKeyUsageX509 aUsage);

/**
 * Supported types of certificate format. Note these must be only 1 byte long as
 * the file cert store only seralises them as 1 byte.
 * 
 * @publishedAll
 * @released
 */
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

/**
 * The owner of a certificate.
 * 
 * @publishedAll
 * @released
 */
enum TCertificateOwnerType
	{
	ECACertificate,
	EUserCertificate,
	EPeerCertificate
	};

/** The length of a SHA1 hash */
const TInt KSHA1HashLengthBytes = 20;

/**
 * A SHA1 hash.
 * 
 * @publishedAll
 * @released
 */
typedef  TBuf8<KSHA1HashLengthBytes> TSHA1Hash;

//const TInt KMD5HashLengthBytes = 16;
//typedef TMD5Hash TBufC8<KMD5HashLengthBytes>;

/**
 * A SHA 1 hash is also used as a key identifier.
 * 
 * @publishedAll
 * @released
 */
typedef TSHA1Hash TKeyIdentifier;

/**
 * Errors that can occur when validating a certificate chain.
 * 
 * @publishedAll
 * @released
 */
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
//@}

#include "securitydefs.inl"

#endif
