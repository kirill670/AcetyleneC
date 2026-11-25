/// IMPluginapi.h
//
// Copyright (c) 1997-2003 UIQ Technology.  All rights reserved.
//
#ifndef __IMPLUGINAPI_H
#define __IMPLUGINAPI_H

#include <e32std.h>
#include <imdefs.h>
#include <impluginobserver.h>


/** Base-class for all IM framework plugins */
class CImPlugin : public CBase
{
public:
	/**
	 * RequestContactNotificationL is called to request notifications about status changes and new messages from a specific IM user.
	 * @param aImUserId, the id of the IM user that this is requested for.
	 * @param aCntId, the contact id that this user shall be associated with.
	 * @return TBool, returns weather the requested IM user id exists
	 */
	virtual TBool RequestContactNotificationL(const TDesC& aImUserId, TContactItemId aCntId) = 0;

	/**
	 * CancelContactNotificationL is called to stop all notifications, both status changes and new messages, from a specific IM user.
	 * @param aImUserId, which id the IM user has.
	 * @param aCntId, the contacts id associated with this IM user.
	 */
	virtual void CancelContactNotificationL(const TDesC& aImUserId, TContactItemId aCntId) = 0;

	/**
	 * CancelAllNotificationsL is called to stop all notifications, both status changes and new messages, from all users.
	 */
	virtual void CancelAllNotificationsL() = 0;

	/**
	 * RequestUsersPresenceStatusL is called when the presence status of the user is requested.
	 */
	virtual void RequestUsersPresenceStatusL() = 0;

	/**
	 * RequestAnyMessageNotificationL is called to request a notification when a message arrives in any services
	 */
	virtual void RequestAnyMessageNotificationL() = 0;

	/**
	 * CancelAnyMessageNotificationL is called to cancel the notification for any messages.
	 */
	virtual void CancelAnyMessageNotificationL() = 0;

	/**
	 * GetAvailableStatusesInServiceL is called to get a list of all the choices the user has when he/she wishes to change his/her status.
	 * @return CImStatusArray, the array of statuses. The ownership is transfered to the framework.
	 */
	virtual CImStatusArray* GetAvailableStatusesInServiceL() = 0;

	/**
	 * SetUsersPresenceStatusL is called when the user changes his/her status in the active IM application.
	 * @param aStatusId, the is the new status has.
	 * @param aDescription, a text describing the new status.
	 */
	virtual void SetUsersPresenceStatusL(TUint32 aStatusId, const TDesC& aDescription) = 0;

	/**
	 * FindIMIdentityL is called when a new link should be created. The method should provide a search-mechanism for the user to select an IM user.
	 * @param aFirstName, the first name the contact has.
	 * @param aLastName, the last name the contact has.
	 * @param aMailAddress, the mail address the contact has.
	 * @return TDesC&, the IM users id.
	 */
	virtual const TDesC& FindIMIdentityL(const TDesC& aFirstName, const TDesC& aLastName, const TDesC& aMailAddress) = 0;

	/**
	 * GetViewUidForAction is called to get view uid's used to perform the various actions (TImApplicationAction)
	 * @param aAction, the action that a view uid is requested for.
	 * @return TUid, the view uid.
	 */
	virtual TUid GetViewUidForAction(TImApplicationAction aAction) = 0;

	/**
	 * GetMessageIcon is called to get the message icon to which the plugin belongs.
	 * @return CImIcon, the message icon. Ownership is transfered to the framework.
	 */
	virtual CImIcon* GetMessageIcon() = 0;

	/**
	 * GetApplicationIcon is called to get the application icon to which the plugin belongs.
	 * @return CImIcon, the application icon. Ownership is transfered to the framework.
	 */
	virtual CImIcon* GetApplicationIcon() = 0;

	/**
	 * SetImFwObserver is called to set iFw
	 * @param aFw, a pointer to the framework
	 */
	void SetImFwObserver(MIMPluginObserver* aFw) {iFw = aFw;};

protected:

	/**	A pointer to the framework observing this plugin. */
	MIMPluginObserver*	iFw;
};

#endif	// __IMPLUGINAPI_H