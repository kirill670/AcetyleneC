// X509CERTEXT.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

//some common specific extensions...
//1)	basic constraints
//2)	alt name
//3)	key usage
//4)	name constraints
//5)	policy constraints
//6)	policies
//7)	policy mapping
//8)	authority key ID
//9)	subject key ID
//10)	extended key usage
//11)	CRL distribution point			not done yet
//12)	authority information access
//13)   subject directory attributes	not done yet
//14)	private key usage period		not done yet

#if !defined (__X509CERTEXT_H__)
#define __X509CERTEXT_H__

#include <e32base.h>
#include <e32std.h>
#include <x509gn.h>

//OIDS for the extensions we define here...
_LIT(KBasicConstraints,"2.5.29.19");
_LIT(KSubjectAltName,"2.5.29.17");
_LIT(KIssuerAltName,"2.5.29.18");
_LIT(KKeyUsage,"2.5.29.15");
_LIT(KNameConstraints,"2.5.29.30");
_LIT(KPolicyConstraints,"2.5.29.36");
_LIT(KCertPolicies,"2.5.29.32");
_LIT(KPolicyMapping,"2.5.29.33");
_LIT(KAuthorityKeyId,"2.5.29.35");
_LIT(KSubjectKeyId,"2.5.29.14");
_LIT(KExtendedKeyUsage,"2.5.29.37");
_LIT(KAuthorityInfoAccess, "1.3.6.1.5.5.7.1.1");

// OIDs for access methods
_LIT(KAccessMethodOCSP, "1.3.6.1.5.5.7.48.1");

//deprecated OIDs we might still encounter
_LIT(KOldBasicConstraints,"2.5.29.10");
_LIT(KOldBasicConstraints2,"2.5.29.13");
_LIT(KOldSubjectAltName,"2.5.29.7");
_LIT(KOldIssuerAltName,"2.5.29.8");
_LIT(KOldNameConstraints,"2.5.29.11");
_LIT(KOldPolicyConstraints,"2.5.29.2");
_LIT(KOldPolicyConstraints2,"2.5.29.34");
_LIT(KOldCertPolicies,"2.5.29.3");
_LIT(KOldPolicyMapping,"2.5.29.5");
_LIT(KOldAuthorityKeyId,"2.5.29.1");

//1) basic constraints...
class CX509ExtensionBase : public CBase
	{
protected:
	virtual void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	virtual void DoConstructL(const TDesC8& aBinaryData, TInt& aPos) = 0;
	};

class CX509BasicConstraintsExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509BasicConstraintsExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509BasicConstraintsExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509BasicConstraintsExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509BasicConstraintsExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	~CX509BasicConstraintsExt();
	IMPORT_C TBool IsCA() const;
	IMPORT_C TInt MaxChainLength() const;//0 if not set
private:
	CX509BasicConstraintsExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	TBool iIsCA;
	TInt iMaxChainLen;
	};

//2) alt name
class CX509AltNameExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509AltNameExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509AltNameExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509AltNameExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509AltNameExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	 ~CX509AltNameExt();
	IMPORT_C const CArrayPtrFlat<CX509GeneralName>& AltName() const;
	IMPORT_C TBool Match(const CX509AltNameExt& aExt) const;
private:
	CX509AltNameExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CArrayPtrFlat<CX509GeneralName>* iAuthorityName;
	};

//3) key usage
class CX509BitString : public CBase
	{
public:
	~CX509BitString();
	TBool IsSet(TInt aBit) const;
	CX509BitString(HBufC8* aData, TInt aEffectiveLength);
private:
	HBufC8* iData;
	TInt iLength;
	};

enum TX509KeyUsage
	{
	EX509DigitalSignature,
	EX509NonRepudiation,
	EX509KeyEncipherment,
	EX509DataEncipherment,
	EX509KeyAgreement,
	EX509KeyCertSign,
	EX509CRLSign,
	EX509EncipherOnly,
	EX509DecipherOnly
	};

class CX509KeyUsageExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509KeyUsageExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509KeyUsageExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509KeyUsageExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509KeyUsageExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	~CX509KeyUsageExt();
	IMPORT_C TBool IsSet(TX509KeyUsage aUsage) const;
private:
	CX509KeyUsageExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CX509BitString* iData;
	};

//4) name constraints
class CX509GeneralSubtree : public CBase
	{
public:
	static CX509GeneralSubtree* NewL(const TDesC8& aBinaryData);
	static CX509GeneralSubtree* NewLC(const TDesC8& aBinaryData);
	static CX509GeneralSubtree* NewL(const TDesC8& aBinaryData, TInt& aPos);
	static CX509GeneralSubtree* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	~CX509GeneralSubtree();
	IMPORT_C const CX509GeneralName& Name() const;
	IMPORT_C TInt MinDistance() const;
	IMPORT_C TInt MaxDistance() const;
private:
	CX509GeneralSubtree();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CX509GeneralName* iName;
	TInt iMaxDist;
	TInt iMinDist;
	};

class CX509NameConstraintsExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509NameConstraintsExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509NameConstraintsExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509NameConstraintsExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509NameConstraintsExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C ~CX509NameConstraintsExt();
	IMPORT_C const CArrayPtrFlat<CX509GeneralSubtree>& ExcludedSubtrees() const;
	IMPORT_C const CArrayPtrFlat<CX509GeneralSubtree>& PermittedSubtrees() const;
private:
	CX509NameConstraintsExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void AddSubtreesL(CArrayPtrFlat<CX509GeneralSubtree>& aSubtrees, const TDesC8& aBinaryData);
	CArrayPtrFlat<CX509GeneralSubtree>* iExcludedSubtrees;
	CArrayPtrFlat<CX509GeneralSubtree>* iPermittedSubtrees;
	};

//5) policy constraints
class TX509PolicyConstraint
	{
public:
	TX509PolicyConstraint(TBool aRequired, TInt aCountdown);
	TX509PolicyConstraint();
	TBool iRequired;
	TInt iCountdown;
	};

class CX509PolicyConstraintsExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509PolicyConstraintsExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509PolicyConstraintsExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509PolicyConstraintsExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509PolicyConstraintsExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C ~CX509PolicyConstraintsExt();
	IMPORT_C TX509PolicyConstraint ExplicitPolicyRequired() const;
	IMPORT_C TX509PolicyConstraint InhibitPolicyMapping() const;
private:
	CX509PolicyConstraintsExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	TX509PolicyConstraint iRequirePolicy;
	TX509PolicyConstraint iInhibitPolicyMapping;
	};

//6) policies
class CX509PolicyQualifierInfo : public CBase
	{
public:
	static CX509PolicyQualifierInfo* NewL(const TDesC8& aBinaryData);
	static CX509PolicyQualifierInfo* NewLC(const TDesC8& aBinaryData);
	static CX509PolicyQualifierInfo* NewL(const TDesC8& aBinaryData, TInt& aPos);
	static CX509PolicyQualifierInfo* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	static CX509PolicyQualifierInfo* NewL(const CX509PolicyQualifierInfo& aQualifierInfo);
	static CX509PolicyQualifierInfo* NewLC(const CX509PolicyQualifierInfo& aQualifierInfo);
	~CX509PolicyQualifierInfo();
	IMPORT_C TPtrC Id() const;
	IMPORT_C TPtrC8 Data() const;
private:
	CX509PolicyQualifierInfo();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const CX509PolicyQualifierInfo& aQualifier);
	HBufC* iPolicyQualifierId;
	HBufC8* iData; //opaque (this is another any-defined-by, so could be anything)
	};

class CX509CertPolicyInfo : public CBase
	{
public:
	static CX509CertPolicyInfo* NewL(const TDesC8& aBinaryData);
	static CX509CertPolicyInfo* NewLC(const TDesC8& aBinaryData);
	static CX509CertPolicyInfo* NewL(const TDesC8& aBinaryData, TInt& aPos);
	static CX509CertPolicyInfo* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509CertPolicyInfo* NewL(const CX509CertPolicyInfo& aPolicy);
	IMPORT_C static CX509CertPolicyInfo* NewLC(const CX509CertPolicyInfo& aPolicy);
	~CX509CertPolicyInfo();
	IMPORT_C const CArrayPtrFlat<CX509PolicyQualifierInfo>& Qualifiers() const;
	IMPORT_C TPtrC Id() const;
private:
	CX509CertPolicyInfo();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const CX509CertPolicyInfo& aInfo);
	HBufC* iCertPolicyId;//OID for this policy
	CArrayPtrFlat<CX509PolicyQualifierInfo>* iQualifiers;
	};

//the policy under which this certificate has been issued...
class CX509CertPoliciesExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509CertPoliciesExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509CertPoliciesExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509CertPoliciesExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509CertPoliciesExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	~CX509CertPoliciesExt();
	IMPORT_C const CArrayPtrFlat<CX509CertPolicyInfo>& Policies() const;
private:
	CX509CertPoliciesExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CArrayPtrFlat<CX509CertPolicyInfo>* iPolicies;
	};

//7) policy mapping
class CX509PolicyMapping : public CBase
	{
public:
	static CX509PolicyMapping* NewL(const TDesC8& aBinaryData);
	static CX509PolicyMapping* NewLC(const TDesC8& aBinaryData);
	static CX509PolicyMapping* NewL(const TDesC8& aBinaryData, TInt& aPos);
	static CX509PolicyMapping* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509PolicyMapping* NewL(const CX509PolicyMapping& aMapping);
	IMPORT_C static CX509PolicyMapping* NewLC(const CX509PolicyMapping& aMapping);
	~CX509PolicyMapping();
	IMPORT_C TPtrC IssuerPolicy() const;
	IMPORT_C TPtrC SubjectPolicy() const;
private:
	CX509PolicyMapping();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const CX509PolicyMapping& aMapping);
	HBufC* iIssuerPolicy;
	HBufC* iSubjectPolicy;
	};

class CX509PolicyMappingExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509PolicyMappingExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509PolicyMappingExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509PolicyMappingExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509PolicyMappingExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	~CX509PolicyMappingExt();
	IMPORT_C const CArrayPtrFlat<CX509PolicyMapping>& Mappings() const;
private:
	CX509PolicyMappingExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CArrayPtrFlat<CX509PolicyMapping>* iPolicies;
	};

//8) authority key ID
class CX509AuthorityKeyIdExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509AuthorityKeyIdExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509AuthorityKeyIdExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509AuthorityKeyIdExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509AuthorityKeyIdExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	~CX509AuthorityKeyIdExt();
	IMPORT_C const CArrayPtrFlat<CX509GeneralName>& AuthorityName() const;
	IMPORT_C TPtrC8 AuthorityCertSerialNumber() const;
	IMPORT_C TPtrC8 KeyId() const;
private:
	CX509AuthorityKeyIdExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void DecodeNameL(const TDesC8& aBinaryData);
	void DecodeSerialNoL(const TDesC8& aBinaryData);
	void DecodeKeyIdL(const TDesC8& aBinaryData);
	CArrayPtrFlat<CX509GeneralName>* iAuthorityName;
	HBufC8* iAuthorityCertSerialNumber;
	HBufC8* iKeyIdentifier;
	};

//9) subject key ID
class CX509SubjectKeyIdExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509SubjectKeyIdExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509SubjectKeyIdExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509SubjectKeyIdExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509SubjectKeyIdExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C ~CX509SubjectKeyIdExt();
	IMPORT_C TPtrC8 KeyId() const;
private:
	CX509SubjectKeyIdExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	HBufC8* iKeyIdentifier;
	};

//10) extended key usage
class CX509ExtendedKeyUsageExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509ExtendedKeyUsageExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509ExtendedKeyUsageExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509ExtendedKeyUsageExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509ExtendedKeyUsageExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C ~CX509ExtendedKeyUsageExt();
	IMPORT_C const CArrayPtrFlat<HBufC>& KeyUsages() const;
private:
	CX509ExtendedKeyUsageExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CArrayPtrFlat<HBufC>* iKeyUsages;
	};

//12) authority information access
class CX509AccessDescription : public CBase
	{
public:
	static CX509AccessDescription* NewL(const TDesC8& aBinaryData);
	static CX509AccessDescription* NewLC(const TDesC8& aBinaryData);
	static CX509AccessDescription* NewL(const TDesC8& aBinaryData, TInt& aPos);
	static CX509AccessDescription* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	~CX509AccessDescription();
	IMPORT_C TPtrC Method() const; // Get accessMethod OID
	IMPORT_C const CX509GeneralName& Location() const;
private:
	CX509AccessDescription();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	HBufC* iMethodId;
	CX509GeneralName* iLocation;
	};

class CX509AuthInfoAccessExt : public CX509ExtensionBase
	{
public:
	IMPORT_C static CX509AuthInfoAccessExt* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509AuthInfoAccessExt* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509AuthInfoAccessExt* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509AuthInfoAccessExt* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C ~CX509AuthInfoAccessExt();
	IMPORT_C const CArrayPtrFlat<CX509AccessDescription>& AccessDescriptions() const;
private:
	CX509AuthInfoAccessExt();
	void DoConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CArrayPtrFlat<CX509AccessDescription>* iAccessDescs;
	};

#endif
