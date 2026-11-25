//
// ImplementationInformation.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file ImplementationInformation.h
	Comments : This file contains the definition of
			the CImplementationInformation class.
 */ 

#ifndef __IMPLEMENTATIONINFORMATION_H__
#define __IMPLEMENTATIONINFORMATION_H__

#include <s32std.h>

// ____________________________________________________________________________________
// 
/**
	@class CImplementationInformation

	This class acts as the container for the registration data 
	relating to a particular Interface Implementation.
	
	It is available to the client to allow access to the
	registered characteristics of the implementation.
	These characteristics are:

	ImplementationUid() The Uid of this implementation.

	Version()			The version number of this implementation.

	DisplayName()		The human readable name for this implementation returned 
						as a 16 bit descriptor.

	DataType()			The data type which this implementation supports, returned
						as an 8 bit descriptor.

	OpaqueData()		The opaque data which is registered for this implementation,
						returned as an 8 bit descriptor.

	@since 7.0
	@dependencies RArray, RPointerArray, RReadStream, RWriteStream, TUid, HBufC, HBufC8, CBase
*/
//##ModelId=3AD31E780181
class CImplementationInformation : public CBase
	{
public:
	/**
		@fn				CImplementationInformation* NewLC(RReadStream& aStream)
		Intended Usage	:	Standardised two phase constructor which leaves the
							CImplementationInformation pointer upon the cleanup stack.
		@exception		KErrNoMemory
		@since			7.0
		@param			aStream The stream to internalize this object from
		@return			A pointer to a fully constructed CImplementationInformation
		@post			Object is fully constructed and initialised
	 */
	//##ModelId=3AD4795C002E
	static CImplementationInformation* NewLC(RReadStream& aStream);

	/**
		@fn				CImplementationInformation* NewL(TUid	 aUid, 
														 TInt	 aVersion, 
														 HBufC*  aName,
														 HBufC8* aDataType,
														 HBufC8* aOpaqueData)
		Intended Usage	:	Standardised two phase construction which leaves nothing
							on the cleanup stack.  
		@warning		This object takes ownership of aName, aDataType & aOpaqueData.
		@exception		KErrNoMemory
		@since			7.0
		@param			aUid The unique Id of this implementation
		@param			aVersion The version number of this implementation
		@param			aName The display name of this implementation
		@param			aDataType The data type supported by this implementation
		@param			aOpaqueData Data for this implementation which is not used by the ECom framework
		@return			A pointer to a fully constructed CImplementationInformation
		@post			Object is fully constructed and initialised
	 */
	//##ModelId=3AD4795C002F
	static CImplementationInformation* NewL(TUid	aUid, 
											TInt	aVersion, 
											HBufC*  aName,
											HBufC8* aDataType,
											HBufC8* aOpaqueData);

/**
	@fn				CImplementationInformation* NewL(const CImplementationInformation& aImplInfo)
	Intended Usage	:	Copy construction which leaves nothing on the cleanup stack.  
	@exception		KErrNoMemory
	@since			7.0
	@param			aImplInfo Item to make a copy of
	@return			A pointer to a fully constructed CImplementationInformation
	@post			Object is fully constructed and initialized
 */
	//##ModelId=3B050BD401A9
	static CImplementationInformation* NewL(const CImplementationInformation& aImplInfo);

	/**
		@fn				~CImplementationInformation()
		Intended Usage	: D'tor	
		@since			7.0
		@pre 			CImplementationInformation is fully constructed.
		@post			CImplementationInformation is completely destroyed.
	 */
	//##ModelId=3AD31E7801C7
	~CImplementationInformation();

	/**
		@fn				DisplayName() const
		Intended Usage	:	Accessor for this implementation's human readable name
		@since			7.0
		@return			The human readable name for this implementation
		@pre 			CImplementationInformation is fully constructed and initialized
	 */
	//##ModelId=3AE05EBF0244
	inline const TDesC& DisplayName() const;

	/**
		@fn				DataType() const
		Intended Usage	:	Accessor for this implementation's default binary data
		@since			7.0
		@return			The data type which this implementation supports
		@pre 			CImplementationInformation is fully constructed and initialized
	 */
	//##ModelId=3AD4795C002D
	inline const TDesC8& DataType() const;

	/**
		@fn				OpaqueData() const
		Intended Usage	:	Accessor for this implementation's opaque binary data
		@since			7.0
		@return			The opaque data which is available for this implementation
		@pre 			CImplementationInformation is fully constructed and initialized
	 */
	//##ModelId=3AE05EBF0103
	inline const TDesC8& OpaqueData() const;

	/**
		@fn				ImplementationUid() const
		Intended Usage	:	Accessor for this implementation's Uid
		@since			7.0
		@return			The Uid of this implementation
		@pre 			CImplementationInformation is fully constructed and initialized
	 */
	//##ModelId=3B050BD4004A
	inline TUid ImplementationUid() const;

	/**
		@fn				Version() const
		Intended Usage	:	Accessor for the version number of this implementation
		@since			7.0
		@return			The version number of this implementation
		@pre 			CImplementationInformation is fully constructed and initialized
	 */
	//##ModelId=3B050BD3032E
	inline TInt Version() const;

	/**
		@fn				Disabled() const
		Intended Usage	:	Accessor for whether this implementation is currently 
							disabled
		@since			7.0
		@return			Flag indicating whether this implementation is disabled
		@pre 			CImplementationInformation is fully constructed and initialized
	 */
	//##ModelId=3AD31E7801BF
	inline TBool Disabled() const;

	/**
		@fn				SetDisabled(TBool aDisabled)
		Intended Usage	:	Marks this implementation as disabled, or enabled.
		@since			7.0
		@param			aDisabled ETrue to indicate this implementation should be disabled, EFalse for enabled.
		@pre 			CImplementationInformation is fully constructed and initialized
		@post			Implementation is marked as.
	 */
	//##ModelId=3AD4795C0023
	inline void SetDisabled(TBool aDisabled);

	/**
		@fn				void ExternalizeL(RWriteStream& aStream) const
		Intended Usage	: Stream out the internal state to aStream.	

		Error Condition	: Leave with the error code.
		@exception		KErrNoMemory.
		@exception		@see RWriteStream.
		@since			7.0
		@param			aStream The stream to store the data in.
		@pre 			CImplementationInformation is fully constructed and initialized
	 */
	//##ModelId=3AD4795C001A
	void ExternalizeL(RWriteStream& aStream) const;

	/**
		@fn				void InternalizeL(RReadStream& aStream)
		Intended Usage	: Restore the internal state from aStream.	

		Error Condition	: Leave with the error code.
		@exception		KErrNoMemory.
		@exception		@see RReadStream.
		@since			7.0
		@param			aStream The stream to read the data from.
		@pre 			CImplementationInformation is fully constructed.
		@post			CImplementationInformation is restored to the state specified by
						the contents of aStream.
	 */
	//##ModelId=3AD4795C0010
	void InternalizeL(RReadStream& aStream);

private:
	/**
		@fn				CImplementationInformation()
		Intended Usage	: Default c'tor
		@since			7.0
		@pre 			None
		@post			CImplementationInformation is fully constructed.
	 */
	//##ModelId=3AD4795B03E4
	CImplementationInformation();

	/**
		@fn				CImplementationInformation(TUid aUid, 
												   TInt aVersion, 
												   HBufC* aName, 
												   HBufC8* aDataType,
												   HBufC8* aOpaqueData)
		Intended Usage	:	Constructor with parameters.  This object takes ownership of
							aName, aDataType and aOpaqueData.
		@param			aUid The unique Id of this implementation
		@param			aVersion The version number of this implementation
		@param			aName The display name of this implementation
		@param			aDataType The data type supported by this implementation
		@param			aOpaqueData Data for this implementation which is not used by the ECom framework
		@since			7.0
		@pre 			None
		@post			CImplementationInformation is fully constructed.
	 */
	//##ModelId=3AD4795B03E5
	CImplementationInformation(TUid aUid, 
							   TInt aVersion, 
							   HBufC*  aName, 
							   HBufC8* aDataType,
							   HBufC8* aOpaqueData);

private:
	/** The implementation UID */
	//##ModelId=3AE05EBE033D
	TUid		iImplementationUid;
	/** The implementation version */
	//##ModelId=3AD4795B03CF
	TInt		iVersion;
	/** This implementations human readable name intended for display in UI implementations */
	//##ModelId=3AD4795B03CA
	HBufC*		iDisplayName;
	/** 
		The type of data this implementation is registered to handle : 
		Used for matching against the run-time cue provided by the client
		during default interface implementation resolution.
	*/
	//##ModelId=3AD4795B03C5
	HBufC8*		iData;
	/** 
		Data registered for this implementation which can be used by the client
		during non-default resolution operations but is ignored by the framework. 
	*/
	//##ModelId=3AE05EBE031F
	HBufC8*		iOpaqueData;
	/** The flag recording if this implementation is disabled or enabled */ 
	//##ModelId=3AD4795B03BB
	TBool		iDisabled;
	};	// End CImplementationInformation

/** Simplifies the definition of functions which return registry information */
typedef RArray<CImplementationInformation*> RImplInfoArray;

/** Simplifies the definition of functions which return registry information */
typedef RPointerArray<CImplementationInformation> RImplInfoPtrArray;


#include <Ecom/ImplementationInformation.inl>

#endif		// __IMPLEMENTATIONINFORMATION_H__
