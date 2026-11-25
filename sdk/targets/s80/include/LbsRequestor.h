/*
* ==============================================================================
*  Name        : LbsRequestor.h
*  Part of     : Mobile Location Framework/Core
*  Interface   : --
*  Description :
*   ?description_line
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/
// LbsRequestor.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSREQUESTOR_H__
#define __LBSREQUESTOR_H__

#include <e32base.h>

// Forward declarations
class RReadStream;
class RWriteStream;


class CRequestorBase : public CBase
/**
 * Each instance of a CRequestor class is used to hold the identity of one
 * of the parties involved requesting the location. The class contains three
 * data fields that indicate:
 * (1) If the requesting party is a "service" or an actual person ("contact").
 * (2) A descriptor that identifiers the requestor and
 * (3) a field that indicates which format the information is in
 *     - for example, a telephone number, URL or email address.
 *
 * @publishedAll
 */
	{
public:
	typedef TInt TRequestorType;

	enum _TRequestorType
		{
		ERequestorUnknown,
		ERequestorService,
		ERequestorContact
		};

	typedef TInt TRequestorFormat;

	enum _TRequestorFormat
		{
		EFormatUnknown,
		EFormatApplication,
		EFormatTelephone,
		EFormatUrl,
		EFormatMail
		};

	IMPORT_C ~CRequestorBase();

	IMPORT_C void SetRequestorL(TRequestorType aType,
	                            TRequestorFormat aFormat,
	                            const TDesC& aData);
	IMPORT_C void GetRequestor(TRequestorType& aType,
	                           TRequestorFormat& aFormat,
	                           TPtrC& aData) const;

	IMPORT_C TRequestorType RequestorType() const;
	IMPORT_C TRequestorFormat RequestorFormat() const;
	IMPORT_C TDesC& RequestorData() const;

	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;

protected:
	IMPORT_C CRequestorBase();

	IMPORT_C void ConstructL(TRequestorType aType,
							 TRequestorFormat aFormat,
							 const TDesC& aData);
	// Reserved for future expansion - derived classes should see documentation
	// on how this is to be used.
	IMPORT_C virtual TAny* ExtendedInterface(TInt aFunctionNumber, TAny* aPtr1, TAny* aPtr2);

protected:
	TRequestorType   iRequestorType;
	TRequestorFormat iFormat;
private:
	/** This is owned by the CRequestor */
	HBufC* iData;
	/** Reserved data for future extension */
	TAny* iBaseReservedPtr;
	};


class CRequestor : public CRequestorBase
	{
public:
	IMPORT_C static CRequestor* New(TRequestorType aType,
	                                TRequestorFormat aFormat,
	                                const TDesC& aData);
	IMPORT_C static CRequestor* NewL(TRequestorType aType,
	                                 TRequestorFormat aFormat,
	                                 const TDesC& aData);
	IMPORT_C static CRequestor* NewLC(TRequestorType aType,
	                                  TRequestorFormat aFormat,
	                                  const TDesC& aData);
	IMPORT_C static CRequestor* NewL(RReadStream& aStream);

	~CRequestor();

private:
	CRequestor();
	};

class RRequestorStack : public RPointerArray<CRequestor>
/**
 * Most standard applications will not use the RRequestorStack. Instead,
 * they will call the simpler RPositioner::SetRequestor() method to
 * identify themselves.
 *
 * RRequestorStack will typically only be used if the application needs to
 * identify a chain of requestors. For example, a remote party is requesting
 * the location and this is routed through a local application. In this
 * situation, the application should identify both itself and the remote party.
 *
 * @see RPointerArray
 * @publishedAll
 */
	{
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	static void CleanupResetAndDestroy(TAny* aArray);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[8];
	};

#endif //__LBSREQUESTOR_H__
