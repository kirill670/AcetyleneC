/*
* ==============================================================================
*  Name        : Lbs.h
*  Part of     : Mobile Location Framework/Location FW
*  Interface   : Location Acquisition API
*  Description : Client-Server communication
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

/**
 * This is generally the first interface class used by all client applications.
 * It is used to make the primary connection to the location server. After the
 * primary connection has been established, its handle is passed as a parameter
 * of the Open methods of RPositioner to create a "sub-session".
 *
 * The RPositionServer class can also be used to discover what position
 * technology "modules" are available. However, this is only required if a
 * client application actually needs to use a particular module.
 */
class RPositionServer : public RSessionBase
	{
public:
    /**
     * Constructor for RPositionServer
     */
	IMPORT_C RPositionServer();

    /**
     * Creates a session with the positioning server. If there are no other
     * sessions when this is called, the method will start the server.
     *
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt Connect();

    /**
     * Closes a session with the positioning server.
     */
	IMPORT_C void Close();

    /**
     * Obtains the current version number of the location server.
     *
     * @return the version of the client API.
     */
	IMPORT_C TVersion Version() const;

    /**
     * This method obtains the identifier of the systems' default positioning
     * module. This module will be used if no criteria is specified when an
     * RPositioner sub-session is created.
     *
     * @see RPositioner::Open()
     * @param aModuleId will be set, upon successful completion, to the ID of the
     * module that the positioning server uses by default.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt GetDefaultModuleId(TPositionModuleId& aModuleId) const;

    /**
     * This method obtains the current number of available positioning modules.
     *
     * @param aNumModules will be set, upon successful completion, to the number of
     * positioning modules (PSYs) that are currently available.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt GetNumModules(TUint& aNumModules) const;

    /**
     * Return details about a specified module.
     *
     * @param aModuleIndex a logical index (0..n) of a positioning module.
     * @param aModuleInfo contains, on successful completion, the information
     * relating to the specified positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt GetModuleInfoByIndex(TInt aModuleIndex,
	                                   TPositionModuleInfoBase& aModuleInfo) const;
    /**
     * Return details about a specified module.
     *
     * @param aModuleId the unique identifier (UID) of a positioning module
     * @param aModuleInfo contains, on successful completion, the information
     * relating to the specified positioning module.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt GetModuleInfoById(TPositionModuleId aModuleId,
	                                TPositionModuleInfoBase& aModuleInfo) const;

    /**
     * Obtains information about the specified positioning module.
     *
     * @param aPosModuleStatus contains, on successful completion, the status of
     * the specified positioning module
     * @param aModuleId the unique identifier (UID) of a positioning module
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt GetModuleStatus(TPositionModuleStatusBase& aPosModuleStatus,
	                              TPositionModuleId aModuleId) const;

    /**
     * This method reports status changes of either a single module or all
     * positioning modules. If the parameter aModuleId is zero, then a status
     * update is provided for all positioning modules. If aModuleId is supplied,
     * then the client will only receive a status update for that specified module.
     *
     * After a notification has been received, the client application must re-issue
     * the status change request if it wishes to obtain further updates.
     *
     * To cancel this request use RPositionServer::CancelRequest with 
     * EPositionServerNotifyModuleStatusEvent as parameter
     *
     * @param aStatusEvent contains, on successful completion, information regarding
     * the status event and the new status of of the specified positioning module.
     * @param aStatus returns the result code after the asynchronous call completes
     * @param aModuleId the unique identifier (UID) of a positioning module.
     */
	IMPORT_C void NotifyModuleStatusEvent(TPositionModuleStatusEventBase& aStatusEvent,
	                                      TRequestStatus& aStatus,
	                                      const TPositionModuleId aModuleId = KPositionNullModuleId) const;

    /**
     * Cancels a previously issued asynchronous request. The TRequestStatus of the
     * original request will be set to KErrCancel if the cancellation request was
     * successful, or any other Symbian OS error code if CancelRequest was called
     * too late.
     *
     * @param aRequestId is a number that uniquely identifies a client side method.
     */
	IMPORT_C TInt CancelRequest(TInt aRequestId);

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


/**
 * Abstract base class for all positioning sub-sessions, including RPositioner.
 *
 * @see RPositioner.
 */
class RPositionerSubSessionBase : public RSubSessionBase
	{
public:
    /**
     * Cancels a previously issued asynchronous request. The TRequestStatus of the
     * original request will be set to KErrCancel if the cancellation request was
     * successful, or any other Symbian OS error code if CancelRequest was called
     * too late.
     *
     * @param aRequestId is a number that uniquely identifies a client side method.
     */
	IMPORT_C TInt CancelRequest(TInt aRequestId);
protected:
	IMPORT_C RPositionerSubSessionBase();
	IMPORT_C virtual TAny* ExtendedInterface(TInt aFunctionNumber, TAny* aPtr1, TAny* aPtr2);
private:
	/** Unused variable for future expansion. */
	TAny* iReserved;
	};


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
 */
class RPositioner : public RPositionerSubSessionBase
	{
public:
    /**
     * Constructor for RPositioner
     */
	IMPORT_C RPositioner();

    /**
     * Creates a sub-session with the positioning server.
     *
     * @param aPosServer is a connected session with the positioning server.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt Open(RPositionServer& aPosServer);

    /**
     * Creates a sub-session with the positioning server.
     *
     * @param aPosServer is a connected session with the positioning server.
     * @param aModuleId is the module ID for this sub-session to use to
     * obtain location data.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt Open(RPositionServer& aPosServer,
	                   TPositionModuleId aModuleId);

    /**
     * Creates a sub-session with the positioning server.
     *
     * @param aPosServer is a connected session with the positioning server.
     * @param aCriteria is the criteria that the server must use to choose an
     * appropriate PSY for this sub-session.
     * @return a Symbian OS error code.
     * @note This function is not supported and it returns KErrNotFound.
     */
	IMPORT_C TInt Open(RPositionServer& aPosServer,
	                   const TPositionCriteriaBase& aCriteria);

    /**
     * Closes a sub-session with the positioning server.
     */
	IMPORT_C void Close();

    /**
     * Sets the requestor of the location information that will be obtained through
     * this sub-session.
     *
     * @param aType identifies the type of requestor, a service or a contact.
     * @param aFormat determines the type of data held in aData
     * @param aData is requestor data. Can be a telephone number, a URL etc.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetRequestor(CRequestor::TRequestorType aType,
	                           CRequestor::TRequestorFormat aFormat,
	                           const TDesC& aData);

    /**
     * Sets the many requestors of the location information that will be obtained
     * through this sub-session.
     *
     * @param aRequestorStack is a collection of CRequestor objects.
     * @return a Symbian OS error code.
     * @retval KErrArgument if aRequestorStack contains no requestors.
     */
	IMPORT_C TInt SetRequestor(const RRequestorStack& aRequestorStack);

    /**
     * This method can be used to modify the behaviour of NotifyPositionUpdate()
     * requests. It enables the client to request an interval time for receiving
     * position updates.
     *
     * @param aPosOption contains the clients requested options for receiving
     * location updates.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt SetUpdateOptions(const TPositionUpdateOptionsBase& aPosOption);

    /**
     * This method retrieves the current update options being used by this
     * RPositioner sub-session.
     *
     * @param aPosOption contains, upon successful completion, the set of update
     * options for NotifyPositionUpdate() that are currently in use.
     * @return a Symbian OS error code.
     */
	IMPORT_C TInt GetUpdateOptions(TPositionUpdateOptionsBase& aPosOption) const;

    /**
     * This method returns cached position information if it is available. This
     * method can be an efficient mechanism - in terms of speed, cost and power
     * consumption - of obtaining the devices' recent position.
     *
     * To cancel this request use RPositioner::CancelRequest with 
     * EPositionerGetLastKnownPosition as parameter.
     *
     * @param aPosInfo will be set, upon successful completion, to the most recently
     * determined location data.
     * @param aStatus returns the result code after the asynchronous call completes
     */
	IMPORT_C void GetLastKnownPosition(TPositionInfoBase& aPosInfo,
	                                   TRequestStatus& aStatus) const;

    /**
     * This is an asynchronous method for obtaining position updates. It is possible
     * to pass any class that is derived from TPositionInfoBase. However, the
     * standard data retrieval class is TPositionInfo. The standard means of
     * retrieving extended information is to use HPositionGenericInfo.
     *
     * To cancel this request use RPositioner::CancelRequest with 
     * EPositionerNotifyPositionUpdate as parameter.
     *
     * @param aPosInfo will hold, on successful completion, information on the
     * devices' current position.
     * @param aStatus returns the result code after the asynchronous call completes
     */
	IMPORT_C void NotifyPositionUpdate(TPositionInfoBase& aPosInfo,
	                                   TRequestStatus& aStatus) const;

protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void Destruct();

	/* Reserved for future expansion - derived classes should see documentation
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

// __LBS_H__
#endif
