/*
* ==============================================================================
*  Name        : Lbs.h
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
// Lbs.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBS_H__
#define __LBS_H__

#include <LbsPositionInfo.h>
#include <LbsIpc.h>
#include <LbsCommon.h>
#include <LbsRequestor.h>
#include <LbsCriteria.h>

// Forward declarations
class CPositioningPtrHolder;
class CServerPositioningPtrHolder;


class RPositionServer : public RSessionBase
/**
 * This is generally the first interface class used by all client applications.
 * It is used to make the primary connection to the location server. After the
 * primary connection has been established, its handle is passed as a parameter
 * of the Open methods of RPositioner to create a "sub-session".
 *
 * The RPositionServer class can also be used to discover what position
 * technology "modules" are available. However, this is only required if a
 * client application actually needs to use a particular module.
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C RPositionServer();

	IMPORT_C TInt Connect();
	IMPORT_C void Close();

	IMPORT_C TInt CancelRequest(TInt aRequestId);
	IMPORT_C TVersion Version() const;

	IMPORT_C TInt GetDefaultModuleId(TPositionModuleId& aModuleId) const;
	IMPORT_C TInt GetNumModules(TUint& aNumModules) const;
	IMPORT_C TInt GetModuleInfoByIndex(TInt aModuleIndex,
	                                   TPositionModuleInfoBase& aModuleInfo) const;
	IMPORT_C TInt GetModuleInfoById(TPositionModuleId aModuleId,
	                                TPositionModuleInfoBase& aModuleInfo) const;

	IMPORT_C TInt GetModuleStatus(TPositionModuleStatusBase& aPosModuleStatus,
	                              TPositionModuleId aModuleId) const;

	IMPORT_C void NotifyModuleStatusEvent(TPositionModuleStatusEventBase& aStatusEvent,
	                                      TRequestStatus& aStatus,
	                                      const TPositionModuleId aModuleId = KPositionNullModuleId) const;

private:
	void ConstructL();
	void Destruct();
	static TInt StartServer();

private:
	/** A pointer to a container that holds pointer descriptors, needed to point
	to the clients request data during asynchronous requests */
	CServerPositioningPtrHolder* iPtrHolder;
	/** Unused variable for future expansion. */
	TAny* iReserved;
	};


class RPositionerSubSessionBase : public RSubSessionBase
/**
 * Abstract base class for all positioning sub-sessions, including RPositioner.
 *
 * @see RPositioner.
 * @publishedAll
 */
	{
public:
	IMPORT_C TInt CancelRequest(TInt aRequestId);
protected:
	IMPORT_C RPositionerSubSessionBase();
	/** Reserved for future expansion - derived classes should see documentation
	on how this is to be used. */
	IMPORT_C virtual TAny* ExtendedInterface(TInt aFunctionNumber, TAny* aPtr1, TAny* aPtr2);
private:
	/** Unused variable for future expansion. */
	TAny* iReserved;
	};


class RPositioner : public RPositionerSubSessionBase
/**
 * This class is used to create a sub-session with the server for the
 * purpose of obtaining the current position. In addition to actually
 * obtaining position information, this class also provides mechanisms
 * for obtaining the last known position, the general status of the
 * positioning module, changing how often it wishes to receive position
 * updates, as well as identifying itself to the location framework. 
 *
 * Before using the class, a primary connection must have already been
 * established with the server.
 *
 * @see RPositionServer
 * @publishedAll
 */
	{
public:
	IMPORT_C RPositioner();

	IMPORT_C TInt Open(RPositionServer& aPosServer);
	IMPORT_C TInt Open(RPositionServer& aPosServer,
	                   TPositionModuleId aModuleId);
	IMPORT_C TInt Open(RPositionServer& aPosServer,
	                   const TPositionCriteriaBase& aCriteria);
	IMPORT_C void Close();

	IMPORT_C TInt SetRequestor(CRequestor::TRequestorType aType,
	                           CRequestor::TRequestorFormat aFormat,
	                           const TDesC& aData);
	IMPORT_C TInt SetRequestor(const RRequestorStack& aRequestorStack);

	IMPORT_C TInt SetUpdateOptions(const TPositionUpdateOptionsBase& aPosOption);
	IMPORT_C TInt GetUpdateOptions(TPositionUpdateOptionsBase& aPosOption) const;

	IMPORT_C void GetLastKnownPosition(TPositionInfoBase& aPosInfo,
	                                   TRequestStatus& aStatus) const;
	IMPORT_C void NotifyPositionUpdate(TPositionInfoBase& aPosInfo,
	                                   TRequestStatus& aStatus) const;

protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void Destruct();

	/** Reserved for future expansion - derived classes should see documentation
	on how this is to be used. */
	IMPORT_C virtual TAny* ExtendedInterface(TInt aFunctionNumber, TAny* aPtr1, TAny* aPtr2);

private:
	void SetRequestorImplL(const RRequestorStack& aRequestorStack) const;

private:
	/** A pointer to a container that holds pointer descriptors, needed to point
	to the clients request data during asynchronous requests */
	CPositioningPtrHolder* iPtrHolder;
	/** Unused variable for future expansion. */
	TAny* iReserved;
	};

#endif // __LBS_H__
