// e32property.h
//
// Copyright (c) Symbian Software Ltd 2003-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/

#ifndef __E32PROPERTY_H__
#define __E32PROPERTY_H__

#include <e32std.h>

/** Property category UID value reserved for System services */
static const TInt32 KUidSystemCategoryValue=0x101f75b6;
/** Property category UID reserved for System services */
static const TUid KUidSystemCategory={KUidSystemCategoryValue};

/** Interface to Publish & Subscribe */
class RProperty : public RHandleBase
	{
public:
	/** The largest supported property value in bytes */
	enum {
	KMaxPropertySize = 512
	};
	/** Property type attribute */
	enum TType
		{
		/** Integral property type */
		EInt,
		/** Byte-array (binary data) property type */
		EByteArray,
		/** Text property type. This is just a programmer friendly
		 * view of a byte-array property */
		EText = EByteArray,
		/** Maximal legal TType value plus 1 **/ 
		ETypeLimit,
		/** Bitmask for TType values coded within TInt attributes. **/ 
		ETypeMask = 0xff
		};
public:
	/** Define a property

	Defines the attributes and access control for a property. This can only be done 
	once for each property. Subsequent attempts to define the same property will return
	KErrAlreadyExists.
	
	This can fail with KErrArgument if wrong type or attribute was specified.
	This can fail with KErrArgument if aType is TInt and aPreallocate is not 0
	This can fail with KErrTooBig if aPreallocate is grater than KMaxPropertySize.
	
	Following definition the property has a default value, 0 for integer properties and
	zero-length	data for byte-array and text properties. Pending subscriptions for this
	property will not be completed until a new value is published.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aAttr This describes the property type, a TType value.
	@param aPreallocate The number of bytes to pre-allocate for variable sized properties.
	Pre-allocating enough space ensures that a variable sized property can be set in 'real-time'
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Define(TUid aCategory, TUint aKey, TInt aAttr, TInt aPreallocate=0);

	/**
	Defines a property.

	Defines the attributes and access control for a property. This can only be done 
	once for each property. Subsequent attempts to define the same property will return
	KErrAlreadyExists.

	Following definition, the property has a default value, 0 for integer
	properties and zero-length	data for byte-array and text properties.
	Pending subscriptions for this property will not be completed until a new
	value is published.

	@param aCategory    The UID that identifies the property category.
	@param aKey         The property sub-key, i.e. the key that identifies the
						specific property within the category.
	@param aAttr		This describes the property type, a TType value.
	@param aReadPolicy	A security policy defining the security attributes a
						process must have in order to read this value.
						This policy is ignored.
	@param aWritePolicy	A security policy defining the security attributes a
						process must have in order to write this value.
						This policy is ignored.
	@param aPreallocate The number of bytes to be pre-allocated for variable
						sized properties. Pre-allocating enough space ensures that
						a variable sized property can be set in 'real-time', 
						(i.e. the time to set the property is bounded). 

	@return KErrNone, if successful;
			KErrArgument, if the wrong type or attribute was specified;
			KErrArgument, if aType is TInt and aPreallocate is not 0;
			KErrTooBig, if aPreallocate is greater than KMaxPropertySize;
	*/
	inline static TInt Define(TUid aCategory, TUint aKey, TInt aAttr, const TSecurityPolicy& aReadPolicy, const TSecurityPolicy& aWritePolicy, TInt aPreallocated=0);

	/** Delete a property
		
	If the property has not been defined this fails with KErrNotFound.
	
	Any pending subscriptions for this property will be completed with KErrNotFound.
	Any new request will not complete until the property is defined and published again.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Delete(TUid aCategory, TUint aKey);

	/** Get an integer property

	Retrieve an integral property value.

	If the property has not been defined this fails with KErrNotFound.
	If the property is not of integral type the	caller is panicked.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aValue Reference to an integer that will receive the current value of the property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Get(TUid aCategory, TUint aKey, TInt& aValue);
	
	/** Get a binary property

	Retrieve a binary property value.

	If the property has not been defined this fails with KErrNotFound.
	If the supplied buffer is too small this returns KErrOverflow and
	truncates the value to the maximum length of the buffer.
	If the property is not of byte-array type the caller is panicked.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aValue  Client descriptor where current value of the property will be written to
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Get(TUid aCategory, TUint aKey, TDes8& aValue);
	
	/** Get a text property

	Retrieve a text property value.

	If the property has not been defined this fails with KErrNotFound.
	If the supplied buffer is too small this returns KErrOverflow and
	truncates the value to the maximum length of the buffer.
	If the property is not of text/byte-array type the caller is
	panicked.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aValue  Client descriptor where current value of the property will be written to
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Get(TUid aCategory, TUint aKey, TDes16& aValue);

	/** Set an integer property

	Publish a new integral property value.
	
	If the property has not been defined this fails with KErrNotFound.
	If the property is not of integral type	this fails with KErrArgument.
	
	Any pending subscriptions for this property will be completed.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aValue Integer representing the new value for this property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Set(TUid aCategory, TUint aKey, TInt aValue);
	
	/** Set a binary property
		
	Publish a new binary property value.
	If the property has not been defined this fails with KErrNotFound.
	If allocation is required this may fail with KErrNoMemory.
	If the property is larger than KMaxPropertySize this fails with KErrTooBig.
	If the property is not of byte-array type this fails with KErrArgument.
	
	Any pending subscriptions for this property will be completed.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aValue Descriptor with the new value for this property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Set(TUid aCategory, TUint aKey, const TDesC8& aValue);
	
	/** Set a text property

	Publish a new text property value.
	If the property has not been defined this fails with KErrNotFound.
	If allocation is required this may fail with KErrNoMemory.
	If the property is larger than KMaxPropertySize this fails with KErrTooBig
	If the property is not of byte-array type this fails with KErrArgument.
	
	Any pending subscriptions for this property will be completed.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aValue Descriptor with the new value for this property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C static TInt Set(TUid aCategory, TUint aKey, const TDesC16& aValue);

	/** Attach to a property

	Create a handle to the property. This allows the caller to
	subscribe for notification of changes to this property, and to
	faster property access methods.
	
	If the property has not been defined this will still succeed. This
	may fail with KErrNoMemory.
	
	@param aCategory The property category
	@param aKey The property sub-key
	@param aType The ownership of this property handle. 
			If not explicitly specified, EOwnerProcess is taken as default
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C TInt Attach(TUid aCategory, TUint aKey, TOwnerType aType = EOwnerProcess);

	/** Subscribe to a property

	Request notification when the property is changed. The calling thread will have the
	specified request status signalled when the property is next updated. Note that the
	property may change several times before the subscribing thread processes this
	notification. To improve the chance that the subscriber does not miss updates it should re-issue
	a subscription request before retrieving the current value and acting on it.

	If the property has not been defined, the request will not complete until the property
	is defined and published.

	Only one subscriptoin per RProperty object is allowed, the caller will be panicked with 
	ERequestAlreadyPending panic code if there is already a subscription on this object.

	@param aRequest The request status to signal on update
	*/
	IMPORT_C void Subscribe(TRequestStatus& aRequest);
	
	/** Cancel a subscription

	Cancel an outstanding subscription request for this property handle. If it has not
	already completed, the request is completed with KErrCancel.
	*/
	IMPORT_C void Cancel();
	
	/** Get the integer property

	Retrieve the attached integral property value.
	If the property has not been defined this fails with KErrNotFound.
	If the property is not of integral type this fails with KErrArgument.

	@param aValue Reference to an integer that will receive the current value of the property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C TInt Get(TInt& aValue);
	
	/** Get the binary property

	Retrieve the attached binary property value.
	If the property has not been defined this fails with KErrNotFound.
	If the property is not of byte-array type this fails with KErrArgument.
	If the supplied buffer is too small this fails with KErrOverflow and the truncated value is reported.

	@param aValue Client descriptor where current value of the property will be written to
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C TInt Get(TDes8& aValue);
	
	/** Get the text property

	Retrieve the attached text property value.
	If the property has not been defined this fails with KErrNotFound.

	If the property is not of text/byte-array
	type the caller is panicked.  If the supplied buffer is too small
	this fails with KErrOverflow and the truncated value is reported.
	
	@param aValue Client descriptor where current value of the property will be written to
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C TInt Get(TDes16& aValue);

	/** Set the integer property

	Publish the attached new integral property value.

	If the property has not been defined this fails with KErrNotFound.
	
	If the property is not of integer type this fails with
	KErrArgument.
	
	Any pending subscriptions for this property will be completed.
	
	@param aValue Integer representing the new value for this property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C TInt Set(TInt aValue);
	
	/** Set the binary property

	Publish the attached new binary property value.
	If the property has not been defined this fails with KErrNotFound.
	If allocation is required this may fail with KErrNoMemory.
	If the property is larger than KMaxPropertySize this fails with KErrTooBig
	If the property is not of byte-array type this fails with KErrArgument.

	Any pending subscriptions for this property will be completed.

	@param aValue Descriptor with the new value for this property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C TInt Set(const TDesC8& aValue);
	
	/** Set the text property
		
	Publish the attached new text property value.
	
	If the property has not been defined this fails with KErrNotFound.
	If allocation is required this may fail with KErrNoMemory.
	
	If the property is not of text/byte-array type this fails with
	KErrArgument.
	
	If the property is larger than KMaxPropertySize this fails with KErrTooBig.
	
	Any pending subscriptions for this property will be completed.
	
	@param aValue Descriptor with the new value for this property
	@return KErrNone if successful otherwise another of the system-wide error codes
	*/
	IMPORT_C TInt Set(const TDesC16& aValue);
	};

inline TInt RProperty::Define(TUid aCategory, TUint aKey, TInt aAttr, const TSecurityPolicy& /*aReadPolicy*/, const TSecurityPolicy& /*aWritePolicy*/, TInt aPreallocated)
	{
	return Define(aCategory,aKey,aAttr,aPreallocated);
	}

#endif
