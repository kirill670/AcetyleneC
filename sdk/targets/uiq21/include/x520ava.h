// X520AVA.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__X520AVA_H__)
#define __X520AVA_H__

#include <e32base.h>
#include <e32std.h>
#include <s32std.h>

enum TAttributeType
	{
	ECommonName,
	ELocalityName,
	EStateOrProvinceName,
	EOrganizationName,
	EOrganizationalUnitName,
	ETitle,
	EDNQualifier,
	ECountryName,
	EGivenName,
	ESurname,
	EInitials,
	EGenerationQualifier,
	EPKCS9EmailAddress
	};

//these are the only attribute types we handle at present
_LIT(KX520CountryName,"2.5.4.6");
_LIT(KX520OrganizationName,"2.5.4.10");
_LIT(KX520OrganizationalUnitName,"2.5.4.11");
_LIT(KX520LocalityName,"2.5.4.7");
_LIT(KX520StateOrProvinceName,"2.5.4.8");
_LIT(KX520Title,"2.5.4.12");
_LIT(KX520CommonName,"2.5.4.3");
_LIT(KX520GivenName,"2.5.4.42");
_LIT(KX520Surname,"2.5.4.4");
_LIT(KX520Initials,"2.5.4.43");
_LIT(KX520GenerationQualifier,"2.5.4.44");
_LIT(KX520DNQualifier,"2.5.4.46");
_LIT(KX520SerialNumber,"2.5.4.5");
_LIT(KX520PostalCode,"2.5.4.17");
//email address is deprecated but we support it anyway...
_LIT(KPKCS9EmailAddress, "1.2.840.113549.1.9.1");

const TInt KX520MaxCLength = 2;
const TInt KX520MaxOLength = 64;
const TInt KX520MaxOULength = 64;
const TInt KX520MaxLLength = 128;
const TInt KX520MaxSOPLength = 128;
const TInt KX520MaxTLength = 64;
const TInt KX520MaxCNLength = 64;
const TInt KX520MaxGNLength = 16;
const TInt KX520MaxSLength = 40;
const TInt KX520MaxILength = 5;
const TInt KX520MaxGQLength = 3;
const TInt KX520MaxSNLength = 64;
const TInt KX520MaxPostalCodeLength = 40;
const TInt KPKCS9MaxEmailAddressLength = 128;

//ava base class
/**
 * TODO
 */
class CX520AttributeTypeAndValue : public CBase
	{
public:
	IMPORT_C static CX520AttributeTypeAndValue* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX520AttributeTypeAndValue* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX520AttributeTypeAndValue* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX520AttributeTypeAndValue* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX520AttributeTypeAndValue* NewL(const CX520AttributeTypeAndValue& aPair);
	IMPORT_C static CX520AttributeTypeAndValue* NewLC(const CX520AttributeTypeAndValue& aPair);
	IMPORT_C static CX520AttributeTypeAndValue* NewL(RReadStream& aStream);
	IMPORT_C static CX520AttributeTypeAndValue* NewLC(RReadStream& aStream);
	IMPORT_C ~CX520AttributeTypeAndValue();
	IMPORT_C const TPtrC Type() const;
	IMPORT_C const TPtrC8 EncodedValue() const;
	IMPORT_C virtual HBufC* ValueL() const;
	/**
	 * This function compares the current element with aElement.
	 * @param aElement The element to compare this element with
	 * @return 
	 * <UL>
	 * <LI>ETrue if the elements are the same i.e. the value and the type are identical.</LI>
	 * <LI>EFalse otherwise</LI>
	 * </UL>
	 */
	IMPORT_C virtual TBool ExactMatchL(const CX520AttributeTypeAndValue& aElement) const;
	virtual void ExternalizeL(RWriteStream& aStream) const;
private:
	virtual void InternalizeL(RReadStream& aStream);
	CX520AttributeTypeAndValue(const TAttributeType aType);
	CX520AttributeTypeAndValue();
	void ConstructL(const CX520AttributeTypeAndValue& aPair);
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	HBufC* iType;
	/**
	 * The encoded value
	 */
	HBufC8* iValue;
	};

#endif