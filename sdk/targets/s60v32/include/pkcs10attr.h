//
//	Copyright (C) 2002 Symbian Software Ltd. All rights reserved.
//

/** 
 * @file
 * PKCS#10 Certificate Request Attributes class.
 *
 * @internalTechnology 
 */

#if !defined (__PKCS10ATTR_H__)
#define __PKCS10ATTR_H__

class CASN1EncBase;
class CASN1EncSequence;

/** Class representing a single certificate attribute.  Attributes have and
	object identifier and one or more values.

	This class is part of the pkcs10 API, and will be changed or removed in a
	future release.  You should not use it.
 
	@internalTechnology  
*/
class CPKCS10Attribute : public CBase
	{
public:
	
	/** Create an attribute with a specified OID and no values, leaving it on
		the cleanup stack.
	*/
	IMPORT_C static CPKCS10Attribute* NewLC(const TDesC& aAttrOID);

	/** Create an attribute with a specified OID and a single value, leaving it on
		the cleanup stack.
		@param aAttrOID	The specified OID
		@param aASN1	ASN1 encoding object for attribute value
		 				-- this method takes ownership.
	*/
	IMPORT_C static CPKCS10Attribute* NewLC(const TDesC& aAttrOID, CASN1EncBase* aASN1);

	virtual ~CPKCS10Attribute();
	
	/** Add a value to the attribute. */
	IMPORT_C void AddValueL(CASN1EncBase* aASN1);
   
	/** Get the ASN1 encoding of the attribute and relinquish ownership of it,
		leaving it on the cleanup stack.  This is called by CPKCS10Attribtues
		when AddAttribute() is called. This method may leave with E32USER-CBase:66 
		if a stack frame for the next PushL() cannot be allocated.
		@deprecated
	*/
	CASN1EncBase* TakeEncodingC();

	/** Get the ASN1 encoding of the attribute and relinquish ownership of it,
		leaving it on the cleanup stack.  This is called by CPKCS10Attribtues
		when AddAttribute() is called. This method may leave with E32USER-CBase:66 
		if a stack frame for the next PushL() cannot be allocated.
	*/
	CASN1EncBase* TakeEncodingLC();

private:

	CPKCS10Attribute();
	void ConstructL(const TDesC& aAttrOID);

private:	

	CASN1EncSequence* iRoot;
	CASN1EncSequence* iValues;	
	};

/** Class for encoding a collection of certificate attributes and passing them
	to the CPKCS10Request class. Some possible attributes are described in
	PKCS#9.
  
	@publishedAll
	
*/
class CPKCS10Attributes : public CBase
	{
public:
	/** Creates an instance of the class.
		@return New attributes object on the cleanup stack.
	*/
	IMPORT_C static CPKCS10Attributes* NewLC();

	/** Creates an instance of the class.
		@return New attributes object.
	*/
	IMPORT_C static CPKCS10Attributes* NewL();

	/** Adds a new attribute for the certificate request.
		@param aAttr The attribute to add - this method takes ownership.
	*/
	IMPORT_C void AddAttributeL(CPKCS10Attribute* aAttr);

	IMPORT_C ~CPKCS10Attributes(); // virtual from base
	
	/** Get the ASN1 encoding of the attributes and relinquish ownership of it,
		leaving it on the cleanup stack. This is called by CPKCS10Request when
		SetAttributes() is called. This method may leave with E32USER-CBase:66 
		if a stack frame for the next PushL() cannot be allocated.
		@deprecated
	*/
	CASN1EncBase* TakeEncodingC();

	/** Get the ASN1 encoding of the attribute and relinquish ownership of it,
		leaving it on the cleanup stack. This is called by CPKCS10Request when
		SetAttributes() is called. This method may leave with E32USER-CBase:66 
		if a stack frame for the next PushL() cannot be allocated.
	*/
	CASN1EncBase* TakeEncodingLC();

private:
	/** Default constructor.
	*/
	CPKCS10Attributes();

	/** Second phase construction function. 
		@note The structure of the attribute node is as follows:
		@code
		  SET
		    SEQUENCE
			  OID of attribute
			  SET values
			...
		@endcode
	*/
	void ConstructL();
	
private:
	/** Pointer to sequence of user-supplied certificate attributes. 
		#AddAttributeL method is used to create and fill this member. 
		If it is initialized by the time #CalculateEncodingL method 
		is called, the latter uses attributes from this member variable 
		for the request, otherwise no attributes are inserted into 
		the request. 
		
		See #AddAttributeL for the explanation of ASN.1 encoding of
		attributes.
	*/
	CASN1EncSequence* iRoot;
	};

// __PKCS10ATTR_H__
#endif
