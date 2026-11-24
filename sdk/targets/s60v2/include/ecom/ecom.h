//
// ECom.h
// Copyright © 2001-2003 Symbian Ltd. All rights reserved.
//

/** 
@file ECom.h
Comments : The definitions required for the use
of the ECOM framework by a client are contained / defined here.

@warning This code contains Rose2000 generated ModelId comments
		 used in round trip engineering. Please do not remove.
 */ 

#ifndef __ECOM_H__
#define __ECOM_H__

#include <e32base.h>
#include <s32std.h>
#include <f32file.h>


#include <Ecom/EComErrorCodes.h>
#include <Ecom/EComResolverParams.h>
#include <Ecom/ImplementationInformation.h>

// ____________________________________________________________________________________
//
/**
@internalComponent
*/
const TInt KMaxServiceArgs = 4;

/** 
The UID identifiying the CResolver Interface Implementation that only returns plug-ins from ROM. 

@publishedAll
@released
*/
const TUid KRomOnlyResolverUid = {0x10009D92};

/**
REComSession

@publishedAll
@released

This singleton class controls the process of identifying, 
(resolution), instantiation, and destruction of the 
interface class implementations requested by the client.
It manages itself to produce a single connection to the ECom framework 
per thread.

@since 7.0
 */
//##ModelId=3A1D08B702D1
class REComSession  : public RSessionBase
	{
public:
	//##ModelId=3A62E4700202
	IMPORT_C REComSession();
	//##ModelId=3A2D03B2003F
	IMPORT_C static REComSession& OpenL();
	//##ModelId=3A62E471009B
	IMPORT_C void Close();
	//##ModelId=3AE45A6900C6
	IMPORT_C void NotifyOnChange(TRequestStatus& aStatus);
	//##ModelId=3AE45A690025
	IMPORT_C void CancelNotifyOnChange(TRequestStatus& aStatus);
	//##ModelId=3A2D04B2001F
	IMPORT_C static void ListImplementationsL(TUid aInterfaceUid, 
											  const TEComResolverParams& aResolutionParameters,
											  RImplInfoPtrArray& aImplInfoArray);
	//##ModelId=3AE05EB603BD
	IMPORT_C static void ListImplementationsL(TUid aInterfaceUid,
											  RImplInfoPtrArray& aImplInfoArray);
	//##ModelId=3A65868D0354
	IMPORT_C static void ListImplementationsL(TUid aInterfaceUid, 
											  const TEComResolverParams& aResolutionParameters, 
											  TUid aResolverUid,
											  RImplInfoPtrArray& aImplInfoArray);

	// Loading method overloads
	// 1. Implementation UID is known : No parameters to creation.(Key, and offset versions)
	// 2. Implementation UID is known : Parameters required for creation.(Key, and offset versions)
	// 3. Interface UID and default resolver : No parameters to creation.(Key, and offset versions)
	// 4. Interface UID and default resolver : Parameters required for creation.(Key, and offset versions)
	// 5. Interface UID and non-default resolver : No parameters to creation.(Key, and offset versions)
	// 6. Interface UID and non-default resolver : Parameters required for creation.(Key, and offset versions)

	//##ModelId=3AD31E6700C8
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TUid& aDtorIDKey);
	//##ModelId=3AD31E680047
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TInt32 aKeyOffset);
	//##ModelId=3A9D2C5B0170
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters);
	//##ModelId=3AD31E680386
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TInt32 aKeyOffset,
												TAny* aConstructionParameters);
	//##ModelId=3AD31E6A000E
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey,
												const TEComResolverParams& aResolutionParameters);
	//##ModelId=3AD31E6B006A
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												const TEComResolverParams& aResolutionParameters);
	//##ModelId=3AD31E6C00E3
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters, 
												const TEComResolverParams& aResolutionParameters);
	//##ModelId=3AD31E6D026B
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												TAny* aConstructionParameters, 
												const TEComResolverParams& aResolutionParameters);
	//##ModelId=3AD31E6F0033
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												const TEComResolverParams& aResolutionParameters,
												TUid aResolverUid);
	//##ModelId=3AD31E7001E3
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset,
												const TEComResolverParams& aResolutionParameters, 
												TUid aResolverUid);
	//##ModelId=3AD31E7103D0
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters,
												const TEComResolverParams& aResolutionParameters, 
												TUid aResolverUid);
	//##ModelId=3AD31E73035A
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												TAny* aConstructionParameters,
												const TEComResolverParams& aResolutionParameters,
												TUid aResolverUid);
	//##ModelId=3A716CC401D8
	IMPORT_C static void DestroyedImplementation(TUid aDtorIDKey);
	IMPORT_C static void FinalClose();

private:
	//##ModelId=3A62E47001BC
	void ConstructL();
	//##ModelId=3AC83A290054
	void ReallyClose();
	//##ModelId=3AE99A5F00CC
	static void ListImplementationsL(TInt aServiceId, 
									 TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid,
									 RImplInfoPtrArray& aImplInfoArray);
	//##ModelId=3A7FEAF002A3
	TAny* GetResolvedCreationMethodL(TUid aImplementationUid, 
									 TUid& aDtorIDKey);
	//##ModelId=3A2E4670007B
	TAny* GetResolvedCreationMethodL(TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid& aDtorIDKey);
	//##ModelId=3A65868D003D
	TAny* GetResolvedCreationMethodL(TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid, 
									 TUid& aDtorIDKey);
	//##ModelId=3AE99A5D021E
	TAny* GetResolvedCreationMethodL(TInt aServiceId,
									 TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid, 
									 TUid& aDtorIDKey);
	//##ModelId=3AD4795801AE
	TAny* CreateL(TAny* aCreationMethodPtr);
	//##ModelId=3AD47958038E
	TAny* CreateL(TAny* aCreationMethodPtr, TAny* aCreationParameters);

private:
	//##ModelId=3B050BC302C7
	TInt iReserved2;


/** Flag indicating that this session should not be closed because the interface
	implementation is in the middle of construction and this will be on the CleanupStack*/
	//##ModelId=3B2A288403AE
	TBool iDoNotCloseThis;

	/** Buffer for the arguments to the framework services */
	TAny* iReserved;

	};

#endif	// __ECOM_H__

