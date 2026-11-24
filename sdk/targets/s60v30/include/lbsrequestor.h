/*
* ==============================================================================
*  Name        : LbsRequestor.h
*  Part of     : Mobile Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Requestor classes
*  Version     :
*
*  Copyright (c) 2002-2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef __LBSREQUESTOR_H__
#define __LBSREQUESTOR_H__

#include <e32base.h>

// Forward declarations
class RReadStream;
class RWriteStream;


/**
 * Requestor base class.
 */
class CRequestorBase : public CBase
	{
public:
	typedef TInt TRequestorType;

    /** Requestor types */
	enum _TRequestorType
		{
		ERequestorUnknown,
		ERequestorService,
		ERequestorContact
		};

	typedef TInt TRequestorFormat;

    /** Requestor formats */
	enum _TRequestorFormat
		{
		EFormatUnknown,
		EFormatApplication,
		EFormatTelephone,
		EFormatUrl,
		EFormatMail
		};

    /**
     * Destructor for CRequestorBase.
     */
	IMPORT_C ~CRequestorBase();

    /**
     * Replaces the requestor data for this object with the specified data.
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat determines the type of data held in aData
     * @param aData is requestor data. Can be a telephone number, a URL etc.
     */
	IMPORT_C void SetRequestorL(TRequestorType aType,
	                            TRequestorFormat aFormat,
	                            const TDesC& aData);
    /**
     * Simple accessor for this requestors member data.
     * @param aType will be set to the type of requestor.
     * @param aFormat will be set to the type of data held in aData.
     * @param aData will be set to point to this requestors data.
     */
	IMPORT_C void GetRequestor(TRequestorType& aType,
	                           TRequestorFormat& aFormat,
	                           TPtrC& aData) const;

    /**
     * Simple accessor for this requestors member data.
     * @return the type of requestor, a service or a contact.
     */
	IMPORT_C TRequestorType RequestorType() const;

    /**
     * Simple accessor for this requestors member data.
     * @return the type of data held in this requestor.
     */
	IMPORT_C TRequestorFormat RequestorFormat() const;

    /**
     * Simple accessor for this requestors member data.
     * @returns the requestor data.
     */
	IMPORT_C TDesC& RequestorData() const;

    /**
     * Restores this requestors member data from a stream.
     * @param aStream the stream from which the requestors data is read.
     */
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);

    /**
     * Stores this requestors member data to a stream.
     * @param aStream the stream to which the requestors data is written.
     */
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


/**
 * Each instance of a CRequestor class is used to hold the identity of one
 * of the parties involved requesting the location. The class contains three
 * data fields that indicate:
 * (1) If the requesting party is a "service" or an actual person ("contact").
 * (2) A descriptor that identifiers the requestor and
 * (3) a field that indicates which format the information is in
 *     - for example, a telephone number, URL or email address.
 */
class CRequestor : public CRequestorBase
	{
public:
    /**
     * Allocates and constructs a CRequestor object.
     *
     * The function returns NULL if there is insufficient memory.
     *
     * Slightly unusual construction is to ensure that iData can never be NULL
     * even if someone inherits from this class.
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat determines the type of data held in aData
     * @param aData is requestor data. Can be a telephone number, a URL etc.
     * @return a newly created CRequestor object, or NULL.
     */
	IMPORT_C static CRequestor* New(TRequestorType aType,
	                                TRequestorFormat aFormat,
	                                const TDesC& aData);

    /**
     * Allocates and constructs a CRequestor object.
     * The function leaves if there is insufficient memory.
     *
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat determines the type of data held in aData
     * @param aData is requestor data. Can be a telephone number, a URL etc.
     * @return a newly created CRequestor object.
     */
	IMPORT_C static CRequestor* NewL(TRequestorType aType,
	                                 TRequestorFormat aFormat,
	                                 const TDesC& aData);

    /**
     * Allocates and constructs a CRequestor> object, and leaves
     * the object on the cleanup stack.
     * The function leaves if there is insufficient memory.
     *
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat determines the type of data held in aData
     * @param aData is requestor data. Can be a telephone number, a URL etc.
     * @return a newly created CRequestor object.
     */
	IMPORT_C static CRequestor* NewLC(TRequestorType aType,
	                                  TRequestorFormat aFormat,
	                                  const TDesC& aData);

    /**
     * Allocates and constructs a CRequestor object, and initialises
     * its member variables by reading the internalizing the object from the
     * specified stream.
     * The function leaves if there is insufficient memory.
     *
     * @param aStream is a stream that a CRequestor object was previously
     * externalised to.
     * @return a newly created CRequestor object.
     */
	IMPORT_C static CRequestor* NewL(RReadStream& aStream);

    /**
     * Destructor for CRequestor.
     */
	~CRequestor();

private:
	CRequestor();
	};

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
 */
class RRequestorStack : public RPointerArray<CRequestor>
	{
public:
    /**
     * Restores a collection of requestors member data from a stream.
     * @param aStream the stream from which each of the requestors data is read.
     */
	IMPORT_C void InternalizeL(RReadStream& aStream);

    /**
     * Stores a collection of requestors member data to a stream.
     * @param aStream the stream to which each of the requestors data is written.
     */
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	static void CleanupResetAndDestroy(TAny* aArray);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[8];
	};

#endif //__LBSREQUESTOR_H__
