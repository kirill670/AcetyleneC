// X500DN.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#if !defined (__X500DN_H__)
#define __X500DN_H__

#include <e32base.h>
#include <e32std.h>
#include <s32file.h>
#include <x520ava.h>

/**
 * TODO : a brief description of this class, Will ?
 */
class CX500DistinguishedName : public CBase
	{
public:
	IMPORT_C static CX500DistinguishedName* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX500DistinguishedName* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX500DistinguishedName* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX500DistinguishedName* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX500DistinguishedName* NewL(RReadStream& aStream);
	IMPORT_C static CX500DistinguishedName* NewLC(RReadStream& aStream);	
	IMPORT_C static CX500DistinguishedName* NewL(const CArrayPtr<CX520AttributeTypeAndValue>& aElements);
	IMPORT_C static CX500DistinguishedName* NewLC(const CArrayPtr<CX520AttributeTypeAndValue>& aElements);	
	IMPORT_C static CX500DistinguishedName* NewL(const CX500DistinguishedName& aName);
	IMPORT_C static CX500DistinguishedName* NewLC(const CX500DistinguishedName& aName);
	//
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TInt Count() const;
	IMPORT_C const CX520AttributeTypeAndValue& Element(TInt aIndex) const;
	IMPORT_C ~CX500DistinguishedName(); 
	/**
	 * This function checks if all the fields of aName and iElements are the same but
	 * not necessarily in the same order.
	 * @param aName A X500 distinguished name
	 * @return
	 * <UL>
	 * <LI>ETrue if all the fields in aName and iElements are the same.</LI>
	 * <LI>EFalse otherwise.</LI>
	 * </UL>
	 */
	IMPORT_C TBool ExactMatchL(const CX500DistinguishedName& aName) const;
	/**
	 * This function checks if the elements of iElements are a superset of
	 * the fields in aName.
	 * @param aName We want to check that the fields in aName are present in
	 * iElements.
	 * @return 
	 * <UL>
	 * <LI>ETrue if all the fields in aName have a corresponding field in iElements.</LI>
	 * <LI>EFalse otherwise</LI>
	 * </UL>
	 */
	IMPORT_C TBool IsWithinSubtreeL(const CX500DistinguishedName& aName) const;
	/**
	 * This function compares each of the elements in iElements with aElement. The comparison
	 * is made by the CX520AttributeTypeAndValue::ExactMatchL function.
	 * @param aElement The element which we want to compare the elements of
	 * iElements with.
	 * @return 
	 * <UL>
	 * <LI>ETrue if one of the elements in iElements is equal to aElement.</LI>
	 * <LI>EFalse otherwise</LI>
	 * </UL>
	 */
	IMPORT_C TBool MatchElementL(const CX520AttributeTypeAndValue& aElement) const;
	IMPORT_C HBufC* ExtractFieldL(const TDesC& aFieldName) const;
	IMPORT_C HBufC* DisplayNameL() const;

private:
	CX500DistinguishedName();
	void ConstructL(const CArrayPtr<CX520AttributeTypeAndValue>& aElements);
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(RReadStream& aStream);
	void InternalizeL(RReadStream& aStream);
	CArrayPtrFlat<CX520AttributeTypeAndValue>* iElements;
	};

#endif