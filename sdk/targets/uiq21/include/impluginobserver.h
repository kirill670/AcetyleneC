/// IMPluginObserver.h
//
// Copyright (c) 1997-2003 UIQ Technology.  All rights reserved.
//
#ifndef __IMPLUGINOBSERVER_H
#define __IMPLUGINOBSERVER_H

#include <e32std.h>
#include <imdefs.h>

/** Mixin class to be used by plugins to notify the IM framework */
class MIMPluginObserver
{
public:
	/**
	 * PresenceStatusL is called when an IM user changes his/her online status.
	 * @param aIndicationData, data needed to interpret the status change.
	 */
	virtual void PresenceStatusL(const TIndicationData& aIndicationData) = 0;

	/**
	 * UsersPresenceStatusL is called when the user of the device changes his/her online status.
	 * @param aIndicationData, data needed to interpret the status change.
	 */
	virtual void UsersPresenceStatusL(const TIndicationData& aIndicationData) = 0;

	/**
	 * NewMessageContactL is called when a message arrives from a specific IM user.
	 * @param aIndicationData, data needed to interpret the message notification.
	 */
	virtual void NewMessageContactL(const TIndicationData& aIndicationData) = 0;

	/**
	 * NewMessageL is called when a message arrives from any IM user.
	 * @param aIndicationData, data needed to interpret the message notification.
	 */
	virtual void NewMessageL(const TIndicationData& aIndicationData) = 0;

	/**
	 * AllMessageReadL is called when all messages are read.
	 * @param aIndicationData, data needed to interpret the message notification.
	 */
	virtual void AllMessageReadL(const TIndicationData& aIndicationData) = 0;

	/**
	 * MessageReadContactL is called when the user has read all messages from a specific IM user.
	 * @param aServiceId, in which service (IM application) did the user read a message.
	 * @param aImUserId, the id of the IM user the user read all messages from.
	 * @param aCntId, which id this IM user has in the Contacts database.
	 */
	virtual void MessageReadContactL(const TUint32 aServiceId, const TDesC& aImUserId, TContactItemId aCntId) = 0;

	/**
	 * ImIdentityRemovedL is called when the user removes an IM user that might have a linked contact in Contacts.
	 * @param aServiceId, in which service (IM application) did the user remove this IM user.
	 * @param aImUserId, which id did the removed IM user have.
	 * @param aCntId, if the IM user was linked to a Contacts contact, which id did it have in the Contacts database.
	 */
	virtual void ImIdentityRemovedL(const TUint32 aServiceId, const TDesC& aImUserId, TContactItemId aCntId) = 0;

	/**
	 * UninstallL is called when an service (IM application) is found to be uninstalled.
	 * @param aServiceId, which service (IM application) was uninstalled.
	 */
	virtual void UninstallL(const TUint32 aServiceId) = 0; 

	/**
	 * InstallL is called when an service (IM application) is found to be installed.
	 * @param aServiceId, which service (IM application) was installed.
	 */
	virtual void InstallL(const TUint32 aServiceId) = 0; 

	/**
	 * OfflineL is called when an service (IM application) logs off its online service.
	 * @param aServiceId, which service (IM application) logged off.
	 */
	virtual void OfflineL(const TUint32 aServiceId) = 0; 
};


#endif	// __IMPLUGINOBSERVER_H