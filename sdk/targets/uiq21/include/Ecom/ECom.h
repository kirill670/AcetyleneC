//
// ECom.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
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
const TInt KMaxServiceArgs = 4;

/**
	@public
	@class REComSession

	This singleton class controls the process of identifying, 
	(resolution), instantiation, and destruction of the 
	interface class implementations requested by the client.
	It manages itself to produce a single connection to the ECom framework 
	per thread.

	@since 7.0
	@Depends RSessionBase, TEComResolverParams
 */
//##ModelId=3A1D08B702D1
class REComSession  : public RSessionBase
	{
public:
/**
	@fn				REComSession()
	Intended Usage	: Default c'tor	

	Error Condition	: None	
	@since			7.0
	@pre 			None
	@post			REComSession is fully constructed
 */
	//##ModelId=3A62E4700202
	IMPORT_C REComSession();

/**
	@fn				OpenL()
	Intended Usage	: Open a single connection to the the ECom server,
					reference counting all others.

	Error Condition	: Cannot connect.
	@exception		(@see RSessionBase)
	@since			7.0
	@return			Reference to the open session
	@pre 			None
	@post			REComSession is connected and ready to issue
					ECOM requests.
 */
	//##ModelId=3A2D03B2003F
	IMPORT_C static REComSession& OpenL();

/**
	@fn				Close()
	Intended Usage	: Close the connection to ECOM. 

	Error Condition	: None	
	@since			7.0
	@pre 			REComSession must have been fully constructed.
	@post			REComSession will be closed if this is the last 
					thread instance of REComSession that has been opened,
					otherwise its internal connection information is updated.
 */
	//##ModelId=3A62E471009B
	IMPORT_C void Close();

/**
	@fn				NotifyOnChange(TRequestStatus& aStatus)
	Intended Usage	: Register for notification messages when the underlying ECOM registration
					data changes. 

	Error Condition	: None	
	@since			7.0
	@param			aStatus A request status object to complete for notification signalling.
	@pre 			REComSession must have been fully constructed and opened.
	@post			The caller is registered for receipt of notifications
					if the server's registry data changes.
 */
	//##ModelId=3AE45A6900C6
	IMPORT_C void NotifyOnChange(TRequestStatus& aStatus);

/**
	@fn				CancelNotifyOnChange(TRequestStatus& aStatus)
	Intended Usage	: De-register for notification messages. 

	Error Condition	: None	
	@since			7.0
	@param			aStatus The request status object originally passed
					to NotifyOnChange() for notification signalling.
	@pre 			REComSession must have been fully constructed.
	@post			The caller's registeration for reciept of notifications
					of registry data changes has been cancelled.
 */
	//##ModelId=3AE45A690025
	IMPORT_C void CancelNotifyOnChange(TRequestStatus& aStatus);

/**
	@fn				ListImplementationsL(TUid aInterfaceUid, 
										 const TEComResolverParams& aResolutionParameters,
										 RImplInfoPtrArray& aImplInfoArray)
	Intended Usage	: Retrieve a list of all the implementations which 
						satisfy the specified interface with selection restriction to
						the specified parameters.

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aImplInfoArray A reference to a client owned array which will be filled 
					with interface implementation data. 
	@pre 			REComSession must have been fully constructed.
	@post			REComSession has not changed, and aImplInfoArray 
					contains the list of Implementation information for the interface.
	@warning		aImplInfoArray will first be cleared and all items on it destroyed before
					it is filled with the new information.
 */
	//##ModelId=3A2D04B2001F
	IMPORT_C static void ListImplementationsL(TUid aInterfaceUid, 
											  const TEComResolverParams& aResolutionParameters,
											  RImplInfoPtrArray& aImplInfoArray);
/**
	@fn				ListImplementationsL(TUid aInterfaceUid,
										 RImplInfoPtrArray& aImplInfoArray)
	Intended Usage	: Retrieve a list of all the implementations which 
						satisfy the specified interface.

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface.
	@param			aImplInfoArray A reference to a client owned array which will be filled 
					with interface implementation data. 
	@pre 			REComSession must have been fully constructed.
	@post			REComSession has not changed, and aImplInfoArray 
					contains the list of Implementation information for the interface.
	@warning		aImplInfoArray will first be cleared and all items on it destroyed before
					it is filled with the new information.
 */
	//##ModelId=3AE05EB603BD
	IMPORT_C static void ListImplementationsL(TUid aInterfaceUid,
											  RImplInfoPtrArray& aImplInfoArray);
/**
	@fn				ListImplementationsL(TUid aInterfaceUid, 
										 const TEComResolverParams& aResolutionParameters, 
										 TUid aResolverUid,
										 RImplInfoPtrArray& aImplInfoArray)
	Intended Usage	: Retrieve a list of all the implementations which satisfy the 
						specified interface with selection restriction to
						the specified parameters. 

					Overload with a client provided CResolver.

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The CResolver UID which identifies the resolver 
					implementation with the required client defined behaviour.
	@param			aImplInfoArray A reference to a client owned array which will be filled 
					with interface implementation data. 
	@pre 			REComSession must have been fully constructed.
	@post			REComSession has not changed, and aImplInfoArray 
					contains the list of Implementation information for the interface.
	@warning		aImplInfoArray will first be cleared and all items on it destroyed before
					it is filled with the new information.
 */
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
/**
	@fn				CreateImplementationL(TUid aImplementationUid,
										  TUid& aDtorIDKey)
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aImplementationUid A UID specifying the required interface implementation.
	@param			aDtorIDKey A 32 bit identifer returned by ECom to
					identify this instance to the framework.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E6700C8
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TUid& aDtorIDKey);

/**
	@fn				CreateImplementationL(TUid aImplementationUid,
										  TInt32 aKeyOffset)
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aImplementationUid A UID specifying the required interface implementation.
	@param			aKeyOffset An offset to the 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E680047
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TInt32 aKeyOffset);

/**
	@fn				CreateImplementationL(TUid aImplementationUid,
										  TUid& aDtorIDKey, 
										  TAny* aConstructionParameters)
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aImplementationUid A UID specifying the required interface implementation.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aConstructionParameters The parameter structure to pass to the object creation method.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3A9D2C5B0170
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters);

/**
	@fn				CreateImplementationL(TUid aImplementationUid,
										  TInt32 aKeyOffset, 
										  TAny* aConstructionParameters)
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface.
					
	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aImplementationUid A UID specifying the required interface implementation.
	@param			aKeyOffset An offset to the 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aConstructionParameters The parameter structure to pass to the object creation method.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E680386
	IMPORT_C static TAny* CreateImplementationL(TUid aImplementationUid, 
												TInt32 aKeyOffset,
												TAny* aConstructionParameters);

/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TUid& aDtorIDKey, 
										  const TEComResolverParams& aResolutionParameters)
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E6A000E
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey,
												const TEComResolverParams& aResolutionParameters);

/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TInt32 aKeyOffset, 
										  const TEComResolverParams& aResolutionParameters);
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 
	
	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aKeyOffset An offset to the 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E6B006A
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												const TEComResolverParams& aResolutionParameters);
/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TUid& aDtorIDKey, 
										  TAny* aConstructionParameters, 
										  const TEComResolverParams& aResolutionParameters)
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aConstructionParameters The parameter structure to pass to the object creation method.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E6C00E3
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters, 
												const TEComResolverParams& aResolutionParameters);

/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TInt32 aKeyOffset, 
										  TAny* aConstructionParameters, 
										  const TEComResolverParams& aResolutionParameters);
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aKeyOffset An offset to the 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aConstructionParameters The parameter structure to pass to the object creation method.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E6D026B
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												TAny* aConstructionParameters, 
												const TEComResolverParams& aResolutionParameters);

/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TUid& aDtorIDKey, 
										  const TEComResolverParams& aResolutionParameters,
										  TUid aResolverUid);
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The Uid of a CResolver with client defined behaviour.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E6F0033
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												const TEComResolverParams& aResolutionParameters,
												TUid aResolverUid);

/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TInt32 aKeyOffset,
										  const TEComResolverParams& aResolutionParameters, 
										  TUid aResolverUid);
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aKeyOffset An offset to the 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The Uid of a CResolver with client defined behaviour.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E7001E3
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset,
												const TEComResolverParams& aResolutionParameters, 
												TUid aResolverUid);

/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TUid& aDtorIDKey, 
										  TAny* aConstructionParameters,
										  const TEComResolverParams& aResolutionParameters, 
										  TUid aResolverUid);
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aConstructionParameters The parameter structure to pass to the object creation method.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The Uid of a CResolver with client defined behaviour.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E7103D0
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TUid& aDtorIDKey, 
												TAny* aConstructionParameters,
												const TEComResolverParams& aResolutionParameters, 
												TUid aResolverUid);

/**
	@fn				CreateImplementationL(TUid aInterfaceUid,
										  TInt32 aKeyOffset, 
										  TAny* aConstructionParameters,
										  const TEComResolverParams& aResolutionParameters,
										  TUid aResolverUid);
	Intended Usage	:Instantiate an interface implementation to satisfy the 
					specified interface. 

	Error Condition	: Lack of memory, not connected to the ECom server, or an argument is invalid.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@exception		KErrArgument
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface implementation.
	@param			aKeyOffset An offset to the 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@param			aConstructionParameters The parameter structure to pass to the object creation method.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The Uid of a CResolver with client defined behaviour.
	@return			TAny* A pointer to the instantiated interface implementation.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AD31E73035A
	IMPORT_C static TAny* CreateImplementationL(TUid aInterfaceUid, 
												TInt32 aKeyOffset, 
												TAny* aConstructionParameters,
												const TEComResolverParams& aResolutionParameters,
												TUid aResolverUid);

/**
	@fn				DestroyedImplementation(TUid aDtorIDKey)
	Intended Usage	: Signal the destruction of an interface implementation to ECOM.

	Error Condition	: None	
	@since			7.0
	@param			aDtorIDKey A key specifying the implementation instance.
	@pre 			REComSession must have been fully constructed, and aDtorIDKey 
					must refer to a previously created instance.
	@post			The destruction of the Interface Implementation referred 
					to by aDtorIDKey has been noted by the ECom framework.
 */
	//##ModelId=3A716CC401D8
	IMPORT_C static void DestroyedImplementation(TUid aDtorIDKey);

private:
/**
	@internal
	@fn				ConstructL()
	Intended Usage	: Initialisation phase of two phase construction.
	@exception		KErrNoMemory & @see CreateSession & StartServer
	@since			7.0
	@pre 			REComSession is fully constructed.
	@post			REComSession is fully initialised.
 */
	//##ModelId=3A62E47001BC
	void ConstructL();

/**
	@fn				ReallyClose()
	Intended Usage	: Controlled destruction of this singleton class.

	Error Condition	: None	
	@exception		KErrNoMemory
	@since			7.0
	@return			void 
	@pre 			REComSession is fully constructed.
	@post			The server session has been torn down and REComSession
					has been closed, releasing its resources.
 */
	//##ModelId=3AC83A290054
	void ReallyClose();

/**
	@fn				ListImplementationsL(TInt aServiceId,
										 TUid aInterfaceUid, 
										 const TEComResolverParams& aResolutionParameters, 
										 TUid aResolverUid,
										 RImplInfoPtrArray& aImplInfoArray)
	Intended Usage	: Retrieve a list of all the implementations which satisfy the 
						specified interface with selection restriction to
						the specified parameters. 
					Overload for internal use to ensure consistency between calls.
					This is the method which actually makes the IPC call.

	Error Condition	: Lack of memory, or not connected.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@since			7.0
	@param			aServiceId An integer specifying the ECom service variant to use.
	@param			aInterfaceUid A UID specifying the required interface.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The CResolver UID which identifies the resolver 
					implementation with the required client defined behaviour.
	@param			aImplInfoArray A reference to a client owned array which will be filled 
					with interface implementation data. 
	@pre 			REComSession must have been fully constructed.
	@post			REComSession has not changed, and aImplInfoArray 
					contains the list of Implementation information for the interface.
	@warning		aImplInfoArray will first be cleared and all items on it destroyed before
					it is filled with the new information.
 */
	//##ModelId=3AE99A5F00CC
	static void ListImplementationsL(TInt aServiceId, 
									 TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid,
									 RImplInfoPtrArray& aImplInfoArray);

/**
	@fn				GetResolvedCreationMethodL(TUid aImplementationUid,
											   TUid& aDtorIDKey)
	Intended Usage	:Provide the instantiation method for an interface implementation 
					that satisfies the specified interface. 

	Error Condition	: Lack of memory, or not connected.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@since			7.0
	@param			aImplementationUid A UID specifying the required interface implementation.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@return			TAny* A pointer to the interface implementation instantiation
					method.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3A7FEAF002A3
	TAny* GetResolvedCreationMethodL(TUid aImplementationUid, 
									 TUid& aDtorIDKey);
/**
	@fn				TAny* GetResolvedCreationMethodL(TUid aInterfaceUid, 
													 const TEComResolverParams& aResolutionParameters,
													 TUid& aDtorIDKey)
	Intended Usage	:Provide the instantiation method for an interface implementation 
					that satisfies the specified interface. 

	Error Condition	: Lack of memory, or not connected.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@return			TAny* A pointer to the interface implementation instantiation
					method.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3A2E4670007B
	TAny* GetResolvedCreationMethodL(TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid& aDtorIDKey);

/**
	@fn				GetResolvedCreationMethodL(TUid aInterfaceUid, 
											   const TEComResolverParams& aResolutionParameters, 
											   TUid aResolverUid,
											   TUid& aDtorIDKey)
	Intended Usage	:Provide the instantiation method for an interface implementation 
					that satisfies the specified interface.
					Overload with a client provided CResolver.

	Error Condition	: Lack of memory, or not connected.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@since			7.0
	@param			aInterfaceUid A UID specifying the required interface.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The Uid of a CResolver with client defined behaviour.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@return			TAny* A pointer to the interface implementation instantiation
					method.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3A65868D003D
	TAny* GetResolvedCreationMethodL(TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid, 
									 TUid& aDtorIDKey);

/**
	@fn				GetResolvedCreationMethodL( TInt aServiceId,
												TUid aInterfaceUid, 
												const TEComResolverParams& aResolutionParameters, 
												TUid aResolverUid,
												TUid& aDtorIDKey)
	Intended Usage	:Provide the instantiation method for an interface implementation 
					that satisfies the specified interface.
					Overload for internal use to ensure consistency between calls.
					This is the method which actually makes the IPC call.

	Error Condition	: Lack of memory, or not connected.	
	@exception		KErrNoMemory
	@exception		KErrNotConnected
	@since			7.0
	@param			aServiceId An integer specifying the ECom service variant to use.
	@param			aInterfaceUid A UID specifying the required interface.
	@param			aResolutionParameters A descriptor specifying any additional
					implementation characteristics to be fulfilled.
	@param			aResolverUid The Uid of a CResolver with client defined behaviour.
	@param			aDtorIDKey A 32 bit identifer returned by the ECom framework to
					identify this instance to the framework.
	@return			TAny* A pointer to the interface implementation instantiation
					method.
	@pre 			REComSession must have been fully constructed.
	@post			The requested interface implementation is identified,
					and the instantiation method pointer is returned.
 */
	//##ModelId=3AE99A5D021E
	TAny* GetResolvedCreationMethodL(TInt aServiceId,
									 TUid aInterfaceUid, 
									 const TEComResolverParams& aResolutionParameters, 
									 TUid aResolverUid, 
									 TUid& aDtorIDKey);

/**
	@fn				CreateL(TAny* aCreationMethodPtr)
	Intended Usage	: Construction of an Interface Implementation instance from
					the resolved creation method pointer.

	Error Condition	: Leaves with the error code.	
	@exception		KErrNoMemory
	@since			7.0
	@param			aCreationMethodPtr The pointer to a creation method of type 
					TAny* (*TNewL)().
	@return			TAny* a pointer to the fully constructed instantiation
					produced when aCreationMethodPtr is called.
	@pre 			REComSession is fully constructed.
	@post			TAny* contains a pointer to the fully constructed instantiation
					produced by aCreationMethod pointer.
 */
	//##ModelId=3AD4795801AE
	TAny* CreateL(TAny* aCreationMethodPtr);

/**
	@fn				CreateL(TAny* aCreationMethodPtr, TAny* aCreationParameters)
	Intended Usage	: Construction of an Interface Implementation instance from
					the resolved creation method pointer.

	Error Condition	: Leaves with the error code.	
	@exception		KErrNoMemory
	@since			7.0
	@param			aCreationMethodPtr The pointer to a creation method of type 
					TAny* (*TNewL)(TAny*).
	@param			aCreationParameters A pointer to the creation parameter
					structure passed to the creation method when called.
	@return			TAny* a pointer to the fully constructed instantiation
					produced when aCreationMethodPtr is called with aCreationParameters
					as its sole argument.
	@pre 			REComSession is fully constructed.
	@post			TAny* contains a pointer to the fully constructed instantiation
					produced by aCreationMethod pointer.
 */
	//##ModelId=3AD47958038E
	TAny* CreateL(TAny* aCreationMethodPtr, TAny* aCreationParameters);

private:
	//##ModelId=3B050BC302C7
	TInt iOutstandingNotificationRequests;

/** Flag indicating that this session should not be closed because the interface
	implementation is in the middle of construction and this will be on the CleanupStack*/
	//##ModelId=3B2A288403AE
	TBool iDoNotCloseThis;

	/** Buffer for the arguments to the framework services */
	TAny* iServiceArgs[KMaxServiceArgs];
	};

#endif	// __ECOM_H__
