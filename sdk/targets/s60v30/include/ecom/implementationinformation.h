//
// ImplementationInformation.h
// Copyright © 1997-2005 Symbian Software Ltd. All rights reserved.
//

/** 
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

@publishedAll
@released
*/

NONSHARABLE_CLASS(CImplementationInformation) : public CBase
	{
public:
	
	static CImplementationInformation* NewLC(RReadStream& aStream);
	
	static CImplementationInformation* NewL(TUid	aUid, 
											TInt	aVersion, 
											HBufC*  aName,
											HBufC8* aDataType,
											HBufC8* aOpaqueData,
											TDriveUnit aDrive,
											TBool aRomOnly,
											TBool aRomBased);
	
	static CImplementationInformation* NewL(const CImplementationInformation& aImplInfo);
	
	~CImplementationInformation();
	
	inline const TDesC& DisplayName() const;
	
	inline const TDesC8& DataType() const;
	
	inline const TDesC8& OpaqueData() const;
	
	inline TUid ImplementationUid() const;
	
	inline TInt Version() const;
	
	inline TBool Disabled() const;
	
	inline void SetDisabled(TBool aDisabled);
	
	void ExternalizeL(RWriteStream& aStream) const;
	
	void InternalizeL(RReadStream& aStream);
	inline TDriveUnit Drive() const;
	inline TBool RomOnly() const;
	inline TBool RomBased() const;
	void SetRomBased(TBool aRomBased);

private:
	
	CImplementationInformation();
	
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
	
	TUid		iImplementationUid;
	/** The implementation version */
	
	TInt		iVersion;
	/** This implementations human readable name intended for display in UI implementations */
	
	HBufC*		iDisplayName;
	/** 
		The type of data this implementation is registered to handle : 
		Used for matching against the run-time cue provided by the client
		during default interface implementation resolution.
	*/
	
	HBufC8*		iData;
	/** 
		Data registered for this implementation which can be used by the client
		during non-default resolution operations but is ignored by the framework. 
	*/
	
	HBufC8*		iOpaqueData;
	/** The flag recording if this implementation is disabled or enabled */ 
	
	TBool		iDisabled;
	/** The drive that this plug-in resides on */ 
	TDriveUnit		iDrive;
	/** The flag recording whether this implementation may only be loaded 
	from read-only internal media */
	TBool iRomOnly;
	/** This flag records whether this implementation was discovered on 
	read-only internal media or that it is a later version of one that was */
	TBool iRomBased;
	};	// End CImplementationInformation

/** 
Simplifies the definition of functions which return registry information 

@publishedAll
@released
*/
typedef RArray<CImplementationInformation*> RImplInfoArray;

/** 
Simplifies the definition of functions which return registry information 

@publishedAll
@released
*/
typedef RPointerArray<CImplementationInformation> RImplInfoPtrArray;


#include <Ecom/ImplementationInformation.inl>

#endif		// __IMPLEMENTATIONINFORMATION_H__
