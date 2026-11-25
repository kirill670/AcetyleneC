// X509GN.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

//x500 general name class...
#ifndef __X509GN_H__
#define __X509GN_H__

#include <e32std.h>
#include <badesca.h>

typedef TUint TGNType;
enum 
	{
	EX509RFC822Name = 1,
	EX509DNSName = 2,
	EX509DirectoryName = 4,
	EX509URI = 6,
	EX509IPAddress = 7
	};
//specific name forms we support...
//we should probably put these in a file of their own,
//but they can stay here for now

//superclass
class CX509DomainName : public CBase
	{
public:
	IMPORT_C ~CX509DomainName();
	IMPORT_C TBool IsWithinSubtree(const CX509DomainName& aName) const;
	IMPORT_C TPtrC Name() const;
protected:
	TBool AddDomainL(TInt& aPos);
	TBool AddSubdomainL(TInt& aPos);
	TBool AddSubdomainSeparatorL(TInt& aPos);
	virtual TBool IsValidString(const TDesC& aStr) const;
	virtual TBool IsValidChar(const TChar& aChar) const;
	TBool IsAlphaOrNum(const TChar& aChar) const;
	TBool IsAlpha(const TChar& aChar) const;
	CX509DomainName();
protected:
	CPtrCArray* iRep;
	HBufC* iName;
	};

//rfc822 email address has the form localpart@domain
class CX509RFC822NameSubtree : public CX509DomainName
	{
public:
	IMPORT_C static CX509RFC822NameSubtree* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509RFC822NameSubtree* NewLC(const TDesC8& aBinaryData);
	IMPORT_C const CPtrCArray& Rep() const;
protected:
	virtual void ConstructL(const TDesC8& aBinaryData);
	TBool AddLocalHostL(TInt& aPos);
	TBool IsValidChar(const TChar& aChar) const;
	};

class CX509RFC822Name : public CX509RFC822NameSubtree
	{
public:
	IMPORT_C static CX509RFC822Name* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509RFC822Name* NewLC(const TDesC8& aBinaryData);
private:
	virtual void ConstructL(const TDesC8& aBinaryData);
	};

class CX509DNSNameSubtree : public CX509DomainName
	{
public:
	IMPORT_C static CX509DNSNameSubtree* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509DNSNameSubtree* NewLC(const TDesC8& aBinaryData);
//	IMPORT_C static CX509DNSNameSubtree* NewL(const CX509DNSNameSubtree& aName);
//	IMPORT_C static CX509DNSNameSubtree* NewLC(const CX509DNSNameSubtree& aName);
	IMPORT_C const CPtrCArray& Rep() const;
private:
	void ConstructL(const CX509DNSNameSubtree& aName);
	void ConstructL(const TDesC8& aBinaryData);
	TBool IsValidString(const TDesC& aStr) const;
	};

class CX509DNSName : public CX509DNSNameSubtree
	{
public:
	IMPORT_C static CX509DNSName* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509DNSName* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509DNSName* NewL(const CX509DNSName& aName);
	IMPORT_C static CX509DNSName* NewLC(const CX509DNSName& aName);
	IMPORT_C static CX509DNSName* NewL(const TDesC& aNameString);
	IMPORT_C static CX509DNSName* NewLC(const TDesC& aNameString);
private:
	void ConstructL(const TDesC8& aBinaryData);
	void ConstructL(const TDesC& aNameString);
	void ConstructL(const CX509DNSName& aName);
	void ParseNameL();
	};

class CX509IPBasedURI : public CBase
	{
public:
	IMPORT_C static CX509IPBasedURI* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509IPBasedURI* NewLC(const TDesC8& aBinaryData);
	IMPORT_C ~CX509IPBasedURI();
	IMPORT_C const CX509DNSName& Host() const;
	IMPORT_C TPtrC Name() const;
	CX509IPBasedURI();
private:
	void ConstructL(const TDesC8& aBinaryData);
	TPtrC ExtractHostNameL() const;
	CX509DNSName* iHost;
	HBufC* iName;
	};

class CX509IPSubnetMask : public CBase
	{
	friend class CX509IPAddress;
public:
	IMPORT_C static CX509IPSubnetMask* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509IPSubnetMask* NewLC(const TDesC8& aBinaryData);
	IMPORT_C ~CX509IPSubnetMask();
	IMPORT_C TPtrC8 BaseAddress() const;
	IMPORT_C TPtrC8 Mask() const;
	CX509IPSubnetMask();
private:
	void ConstructL(const TDesC8& aBinaryData);
	HBufC8* iName;
	};

class CX509IPAddress : public CBase
	{
public:
	IMPORT_C static CX509IPAddress* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509IPAddress* NewLC(const TDesC8& aBinaryData);
	IMPORT_C TBool IsWithinSubtree(const CX509IPSubnetMask& aName) const;
	IMPORT_C ~CX509IPAddress();
	IMPORT_C TPtrC8 Address() const;
	CX509IPAddress();
private:
	void ConstructL(const TDesC8& aBinaryData);
	HBufC8* iName;//4 octets for v4, 16 for v6
	};

//general name...
class CX509GeneralName : public CBase
	{
public:
	IMPORT_C static CX509GeneralName* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509GeneralName* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509GeneralName* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509GeneralName* NewLC(const TDesC8& aBinaryData, TInt& aPos);

	IMPORT_C static CX509GeneralName* NewL(const CX509GeneralName& aName);
	IMPORT_C static CX509GeneralName* NewLC(const CX509GeneralName& aName);

	IMPORT_C TGNType Tag() const;
	IMPORT_C TPtrC8 Data() const;
	IMPORT_C ~CX509GeneralName(); 
	IMPORT_C TBool ExactMatch(const CX509GeneralName& aName) const;
private:
	CX509GeneralName();
	CX509GeneralName(TGNType aType);
	void ConstructL();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const TDesC8& aData);
	TGNType iTag;
	HBufC8* iData;
	};

#endif