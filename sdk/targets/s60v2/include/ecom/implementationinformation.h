//
// ImplementationInformation.h
// Copyright © 1997-2003 Symbian Ltd. All rights reserved.
//

/** 
@file ImplementationInformation.h
Comments : This file contains the definition of
		the CImplementationInformation class.
*/ 

#ifndef __IMPLEMENTATIONINFORMATION_H__
#define __IMPLEMENTATIONINFORMATION_H__

#include <s32std.h>
#include <f32file.h>

// ____________________________________________________________________________________
// 
/**
CImplementationInformation

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

RomOnly()			The flag indicating whether this implementation is to be loaded
					from ROM only.

RomBased()			The flag recording whether this implementation is on ROM or is
					a later version of one on ROM.

Dependencies RArray, RPointerArray, RReadStream, RWriteStream, TUid, HBufC, HBufC8, CBase

@since 7.0
@internalComponent
*/
//##ModelId=3AD31E780181
class CImplementationInformation : public CBase
	{
public:
	//##ModelId=3AD4795C002E
	static CImplementationInformation* NewLC(RReadStream& aStream);
	//##ModelId=3AD4795C002F
	static CImplementationInformation* NewL(TUid	aUid, 
											TInt	aVersion, 
											HBufC*  aName,
											HBufC8* aDataType,
											HBufC8* aOpaqueData,
											TDriveUnit aDrive,
											TBool aRomOnly,
											TBool aRomBased);
	//##ModelId=3B050BD401A9
	static CImplementationInformation* NewL(const CImplementationInformation& aImplInfo);
	//##ModelId=3AD31E7801C7
	~CImplementationInformation();
	//##ModelId=3AE05EBF0244
	inline const TDesC& DisplayName() const;
	//##ModelId=3AD4795C002D
	inline const TDesC8& DataType() const;
	//##ModelId=3AE05EBF0103
	inline const TDesC8& OpaqueData() const;
	//##ModelId=3B050BD4004A
	inline TUid ImplementationUid() const;
	//##ModelId=3B050BD3032E
	inline TInt Version() const;
	//##ModelId=3AD31E7801BF
	inline TBool Disabled() const;
	//##ModelId=3AD4795C0023
	inline void SetDisabled(TBool aDisabled);
	//##ModelId=3AD4795C001A
	void ExternalizeL(RWriteStream& aStream) const;
	//##ModelId=3AD4795C0010
	void InternalizeL(RReadStream& aStream);
	inline TDriveUnit Drive() const;
	inline TBool RomOnly() const;
	inline TBool RomBased() const;
	void SetRomBased(TBool aRomBased);

private:
	//##ModelId=3AD4795B03E4
	CImplementationInformation();
	//##ModelId=3AD4795B03E5
	CImplementationInformation(TUid aUid, 
							   TInt aVersion, 
							   HBufC*  aName, 
							   HBufC8* aDataType,
							   HBufC8* aOpaqueData,
							   TDriveUnit aDrive,
							   TBool aRomOnly,
							   TBool aRomBased);

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
	/** The drive that this plug-in resides on */ 
	TDriveUnit		iDrive;
	/** The flag recording whether this implementation may be loaded from ROM only */
	TBool iRomOnly;
	/** The flag recording whether this implementation is on ROM or is a later version of one on ROM */
	TBool iRomBased;
	};	// End CImplementationInformation

/** 
Simplifies the definition of functions which return registry information 
@internalComponent
*/
typedef RArray<CImplementationInformation*> RImplInfoArray;

/** 
Simplifies the definition of functions which return registry information 
@internalComponent
*/
typedef RPointerArray<CImplementationInformation> RImplInfoPtrArray;


#include <Ecom/ImplementationInformation.inl>

#endif		// __IMPLEMENTATIONINFORMATION_H__
