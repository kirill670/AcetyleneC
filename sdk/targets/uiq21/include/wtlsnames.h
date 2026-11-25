// WTLSNAMES.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//


#if !defined (__WTLSNAMES_H__)
#define __WTLSNAMES_H__

#include <e32base.h>
#include <e32std.h>
#include <X500dn.h>

/*
this file contains the definition for class CWTLSName

enum { null(0), text(1), binary(2), key_hash_sha(254), x509_name(255)}
	IdentifierType;

We only support text and x509_name as these are the only meaningful identifiers..
x509_name is X.500 Distinguished Name, and should use our existing X.500 DN implementation.  

struct {
		IdentifierType identifier_type;
		select (identifier_type) {
			case null: struct {};
			case text:
				CharacterSet character_set;
				opaque name<1.. 2^8-1>;
			case binary: opaque identifier<1..2^8-1>;
			case key_hash_sha: opaque key_hash[20];
			case x509_name: opaque distinguished_name<1..2^8-1>;
		} 
		Identifier;

uint16 CharacterSet;

This maps on to one of the IANA defined character sets. There are rather a lot of these.

For a first stab:
	we just support the text type
	and only latin-1 character set
*/

enum 
	{
	EWTLSNull =			0x00,
	EWTLSText =			0x01,
	EWTLSBinary =		0x02,
	EWTLSKeyHashSha =	0xfe,
	EWTLSX500DN =		0xff
	};

typedef TUint8 TWTLSNameType;

typedef TInt TWTLSCharSet;

// MIBenum constants from the IANA list of character sets. See
// http://www.iana.org/assignments/character-sets for more info.
const TInt KWTLSLatin1CharSet = 4;
const TInt KWTLSUTF8CharSet = 106;

class CWTLSName : public CBase
	{
public:
	IMPORT_C static CWTLSName* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSName* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSName* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSName* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSName* NewL(const CWTLSName& aName);
	IMPORT_C static CWTLSName* NewLC(const CWTLSName& aName);	
	IMPORT_C ~CWTLSName(); 	
	IMPORT_C TBool ExactMatchL(const CWTLSName& aName) const;	
	IMPORT_C TWTLSNameType NameType() const;
	IMPORT_C TPtrC8 NameData() const;
	IMPORT_C HBufC* DisplayNameL() const;
private:
	CWTLSName();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const CWTLSName& aName);
	void AllocNameDataL(const TDesC8& aBinaryData, TInt& aPos);
	void AllocTextDataL(const TDesC8& aBinaryData, TInt& aPos);
	TWTLSNameType iNameType;
	HBufC8* iNameData;
	};

class CWTLSText : public CBase
	{
public:
	IMPORT_C static CWTLSText* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSText* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSText* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSText* NewLC(const TDesC8& aBinaryData, TInt& aPos);	
	IMPORT_C ~CWTLSText(); 	
	IMPORT_C TBool ExactMatchL(const CWTLSText& aName) const;	
	IMPORT_C TPtrC Name() const;
	IMPORT_C TWTLSCharSet CharacterSet() const;
protected:
	CWTLSText();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	HBufC* iName;
private:
	TInt iCharacterSet;
	};

//this class implements the 'structured' variant of the text type defined in the WTLS spec, section 10.5.2:
//<servicename>; <organization>; <country>[; <commonname>[; <extension>[; <extension>[ …. ]]]]
_LIT(KWTLSCountryName,"C");
_LIT(KWTLSOrganizationName,"O");
_LIT(KWTLSServiceName,"OU");
_LIT(KWTLSTitle,"T");
_LIT(KWTLSCommonName,"CN");

class TWTLSStructuredTextField 
	{
public:
	TWTLSStructuredTextField(const TDesC& aType, const TDesC& aValue);
	IMPORT_C TPtrC Type() const;
	IMPORT_C TPtrC Value() const;
private:
	const TPtrC iType;
	const TPtrC iValue; 
	};

class CWTLSStructuredText : public CWTLSText
	{
public:
	IMPORT_C static CWTLSStructuredText* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSStructuredText* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSStructuredText* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSStructuredText* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C ~CWTLSStructuredText(); 
	IMPORT_C HBufC* DisplayNameL() const;
	//accessors for defined fields
	IMPORT_C TPtrC ServiceName() const;
	IMPORT_C TPtrC Organization() const;
	IMPORT_C TPtrC Country() const;
	IMPORT_C TInt Count() const;
	//returns NULL if field not found. returned object *remains the property of the structured text object*
	//(so don't delete it...)
	IMPORT_C const TWTLSStructuredTextField* FieldByName(const TDesC& aType) const;
	IMPORT_C const TWTLSStructuredTextField& FieldByIndex(TInt aIndex) const;
private:
	CWTLSStructuredText();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void AddFieldValueL(const TDesC& aFieldName, TInt& aPos);
	void AddFieldL(TInt& aPos);
	TPtrC GetFieldL(TDesC& aString, TInt& aPos);
	TBool GetSubFieldL(TDesC& aString, TInt& aPos);
	CArrayFixFlat<TWTLSStructuredTextField>* iFields; 
	};

#endif


