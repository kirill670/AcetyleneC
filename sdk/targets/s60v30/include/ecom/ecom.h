// ECom.h
// 
// Copyright © 2001-2005 Symbian Software Ltd. All rights reserved.
//

/** 
Comments : The definitions required for the use
of the ECOM framework by a client are contained / defined here.
*/ 

#ifndef __ECOM_H__
#define __ECOM_H__

#include <e32base.h>
#include <s32std.h>
#include <f32file.h>


#include <Ecom/EComErrorCodes.h>
#include <Ecom/EComResolverParams.h>
#include <Ecom/ImplementationInformation.h>

// Forward class declarations
class CLoadManager;
class CGlobalData;

/**
@internalComponent
*/
const TInt KMaxServiceArgs = 4;

/** 
The UID identifying the ROM-Only CResolver Interface Implementation. 
This resolver only returns implementations present on R/O internal media
(built-in) or upgrades of such implementations on R/W media. It does not 
return implementations that solely reside on R/W media. 

@publishedAll
@released
*/
const TUid KRomOnlyResolverUid = {0x10009D92};

////////////////////////////////////////////////////////////////////////////////////////////
// REComSession class

/**
The REcomSession singleton class controls the process of identifying 
(resolution), instantiation, and destruction of the 
interface class implementations requested by ECOM clients.
It manages itself to produce a single connection to the ECom framework 
per thread.

Direct users of ECOM plugins (and this API) must call the static 
REComSession::FinalClose() method when all implementations they have created
have been destroyed and they are finished using ECOM e.g. library shutdown.
It must never be called from within a plugin class destructor.
This is required to avoid false memory leak panics within debug processes.

Note: Althrough a public default constructor is provided in this class
it is strongly recommended this object is never created by users of this
API on the stack or heap by value. To access the non-static methods of this
API use the static REComSession::OpenL() method to obtain a pointer to the
session. This may be stored, used and later Close() when finished with.

@publishedAll
@released
*/
class REComSession  : public RSessionBase
	{
	friend class CGlobalData;
public:

	IMPORT_C REComSession();
	IMPORT_C static REComSession& OpenL();
	IMPORT_C void Close();
	IMPORT_C void NotifyOnChange(TRequestStatus& aStatus);
	IMPORT_C void CancelNotifyOnChange(TRequestStatus& aStatus);
	//ListImplementationsL() declarations. If you want to find the related implementation - 
	//look for related "LI<n>" comment in the CPP file.
	//ListImplementationsL - LI1
	IMPORT_C static void ListImplementationsL(TUid aInterfaceUid, 
											  const TEComResolverParams& aResolutionParameters,
											  RImplInfoPtrArray& aImplInfoArray);
	//ListImplementationsL - LI2
	IMPORT_C static void ListImplementationsL(TUid aInterfaceUid,
											  RImplInfoPtrArray& aImplInfoArray);
	//ListImplementationsL - LI3
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

	//CreateImplementationL() declarations. If you want to find the related implementation - 
	//look for related "CI<n>" comment in the CPP file.
	//CreateImplementationL - CI1
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TUid& aDtorIDKey);
	//CreateImplementationL - CI2
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TInt32 aKeyOffset);
	//CreateImplementationL - CI3
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters);
	//CreateImplementationL - CI4
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TInt32 aKeyOffset,
												TAny* aConstructionParameters);
	//CreateImplementationL - CI5
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey,
												const TEComResolverParams& aResolutionParameters);
	//CreateImplementationL - CI6
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												const TEComResolverParams& aResolutionParameters);
	//CreateImplementationL - CI7
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters, 
												const TEComResolverParams& aResolutionParameters);
	//CreateImplementationL - CI8
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												TAny* aConstructionParameters, 
												const TEComResolverParams& aResolutionParameters);
	//CreateImplementationL - CI9
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												const TEComResolverParams& aResolutionParameters,
												TUid aResolverUid);
	//CreateImplementationL - CI10
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset,
												const TEComResolverParams& aResolutionParameters, 
												TUid aResolverUid);
	//CreateImplementationL - CI11
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters,
												const TEComResolverParams& aResolutionParameters, 
												TUid aResolverUid);
	//CreateImplementationL - CI12
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												TAny* aConstructionParameters,
												const TEComResolverParams& aResolutionParameters,
												TUid aResolverUid);
	IMPORT_C static void DestroyedImplementation(TUid aDtorIDKey);

	//See developer documentation for use of FinalClose.
	IMPORT_C static void FinalClose();

private:
	void ConstructL();
	void ReallyClose();
	static void ListImplementationsL(TInt aServiceId, 
									 TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid,
									 RImplInfoPtrArray& aImplInfoArray);
	TAny* ResolveAndCreateImplL(TUid aImplementationUid, 
									 TUid& aDtorIDKey, 
									 TAny* aCreationParameters, TBool aCreationParamsFlag);
	TAny* ResolveAndCreateImplL(TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid& aDtorIDKey, 
									 TAny* aCreationParameters, TBool aCreationParamsFlag);
	TAny* ResolveAndCreateImplL(TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid, 
									 TUid& aDtorIDKey, 
									 TAny* aCreationParameters, TBool aCreationParamsFlag);
	TAny* ResolveAndCreateImplL(TInt aServiceId,
									 TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid, 
									 TUid& aDtorIDKey, 
									 TAny* aCreationParameters, TBool aCreationParamsFlag);
public:
    //This API is for internal use only and for testing purposes.
	IMPORT_C static void SetGetParametersL(const TIpcArgs &aArgs);
												
private:
	TInt iReserved1;

	/** Internal session flag indicating that this session should not be closed 
	because an implementation is in the middle of construction and this will be 
	on the CleanupStack. Used in Leave conditions to avoid double cleanup. */
	TBool iDoNotCloseThis;

	TInt iReserved2;
	};

#endif	// __ECOM_H__
