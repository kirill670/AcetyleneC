/// IMFramework.h
//
// Copyright (c) 1997-2003 UIQ Technology.  All rights reserved.
//
#ifndef __IMFRAMEWORK_H
#define __IMFRAMEWORK_H

#include <imdefs.h>
#include <impluginapi.h>

class CEcomHandler;
class CRequestedContacts;

/** Mixin class to be used by the IM framework to notify the application */
class MIMObserver
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



/** Framework */
class CImFramework : public CBase, public MIMPluginObserver
{
public:

	/**
	 * NewL is a static construction method
	 * @return	CImFramework	A pointer to the created object
	 */
	IMPORT_C static CImFramework* NewL();

	/**
	 * d'tor
	 */
	~CImFramework();

	/**
	 * RequestContactNotificationL is called to request notifications about status changes and new messages from a specific IM user.
	 * @param aServiceId, the id of the service
	 * @param aImUserId, the id of the IM user that this is requested for.
	 * @param aCntId, the contact id that this user shall be associated with.
	 * @return TBool, returns whether the requested IM user id exists
	 */
	IMPORT_C TBool RequestContactNotificationL(const TUint32& aServiceId, const TDesC& aImUserId, TContactItemId	aCntId);

	/**
	 * CancelContactNotificationL is called to stop all notifications, both status changes and new messages, from a specific IM user.
	 * @param aServiceId, the id of the service
	 * @param aImUserId, which id the IM user has.
	 * @param aCntId, the contacts id associated with this IM user.
	 */
	IMPORT_C void CancelContactNotificationL(const TUint32& aServiceId, const TDesC& aImUserId, TContactItemId aCntId);

	/**
	 * CancelAllNotificationsL is called to stop all notifications, both status changes and new messages, from all users.
	 * @param	aServiceId, the id of the service
	 */
	IMPORT_C void CancelAllNotificationsL(const TUint32& aServiceId);

	/**
	 * RequestAnyMessageNotificationL is called to request a notification when a message arrives in any services
	 */
	IMPORT_C void RequestAnyMessageNotificationL();

	/**
	 * CancelAnyMessageNotificationL is called to cancel the notification for any messages.
	 */
	IMPORT_C void CancelAnyMessageNotificationL();

	/**
	 * RequestUsersPresenceStatusL is called when the presence status of the user is requested.
	 * @param aServiceId, the id of the service
	 */
	IMPORT_C void RequestUsersPresenceStatusL(const TUint32& aServiceId);

	/**
	 * GetAvailableStatusesInServiceL is called to get a list of all the choices the user has when he/she wishes to change his/her status.
	 * @param aServiceId, the id of the service
	 * @return CImStatusArray, the array of statuses. The ownership is transfered to the caller.
	 */
	IMPORT_C CImStatusArray* GetAvailableStatusesInServiceL(const TUint32& aServiceId);

	/**
	 * SetUsersPresenceStatusL is called when the user changes his/her status in the active IM application.
	 * @param aServiceId, the id of the service
	 * @param aStatusId, the is the new status has.
	 * @param aDescription, a text describing the new status.
	 */
	IMPORT_C void SetUsersPresenceStatusL(const TUint32& aServiceId, TUint32 aStatusId, const TDesC& aDescription);

	/**
	 * FindIMIdentityL is called when a new link should be created. The method should provide a search-mechanism for the user to select an IM user.
	 * @param aServiceId, the id of the service
	 * @param aFirstName, the first name the contact has.
	 * @param aLastName, the last name the contact has.
	 * @param aMailAddress, the mail address the contact has.
	 * @return TDesC&, the IM users id.
	 */
	IMPORT_C const TDesC& FindIMIdentityL(const TUint32& aServiceId, const TDesC& aFirstName, const TDesC& aLastName, const TDesC& aMailAddress);

	/**
	 * GetViewUidForAction is called to get view uid's used to perform the various actions (TImApplicationAction)
	 * @param aServiceId, the id of the service
	 * @param aAction, the action that a view uid is requested for.
	 * @return TUid, the view uid.
	 */
	IMPORT_C TUid GetViewUidForAction(const TUint32& aServiceId, TImApplicationAction aAction);

	/**
	 * SetImFwObserver is called to set iFw
	 * @param aFw, a pointer to the framework
	 */
	void SetImFwObserver(MIMObserver* aFw) {iApp = aFw;};

	/**
	 * GetListOfServicesL is called to get a list of the available services
	 * @return CImServiceArray, a pointer to the list. This ownership of the list is then transfered to the framework.
	 */
	IMPORT_C CImServiceArray* GetListOfServicesL();

	/**
	 * GetMessageIconL is called to get the message icon that belongs to the specified service id
	 * @param aServiceId, the id of the service
	 * @return CImIcon, a pointer to the icon. This icon is then owned by the caller.
	 */
	IMPORT_C CImIcon* GetMessageIconL(const TUint32& aServiceId);

	/**
	 * GetApplicationIconL is called to get the icon that belongs to the specified service id's application
	 * @param aServiceId, the id of the service
	 * @return CImIcon, a pointer to the icon. This icon is then owned by the caller.
	 */
	IMPORT_C CImIcon* GetApplicationIconL(const TUint32& aServiceId);

	/**
	 * GetDefaultIconL is called to get the default icon
	 * @return CImIcon, a pointer to the icon. This icon is then owned by the caller.
	 */
	IMPORT_C CImIcon* GetDefaultIconL();

protected:

	/**	A pointer to the framework observing this plugin. */
	MIMObserver*	iApp;

private:
	/**
	 * c'tor
	 */
	CImFramework();

	/**
	 * ConstructL
	 */
	void ConstructL();

	/**
	 * See MIMPluginObserver::PresenceStatusL
	 */
	void PresenceStatusL(const TIndicationData& aIndicationData);

	/**
	 * See MIMPluginObserver::UsersPresenceStatusL
	 */
	void UsersPresenceStatusL(const TIndicationData& aIndicationData);

	/**
	 * See MIMPluginObserver::NewMessageContactL
	 */
	void NewMessageContactL(const TIndicationData& aIndicationData);

	/**
	 * See MIMPluginObserver::AllMessageReadL
	 */
	void AllMessageReadL(const TIndicationData& aIndicationData);

	/**
	 * See MIMPluginObserver::MessageReadContactL
	 */
	void MessageReadContactL(const TUint32 aServiceId, const TDesC& aImUserId, TContactItemId aCntId);

	/**
	 * See MIMPluginObserver::ImIdentityRemovedL
	 */
	void ImIdentityRemovedL(const TUint32 aServiceId, const TDesC& aImUserId, TContactItemId aCntId);

	/**
	 * See MIMPluginObserver::UninstallL
	 */
	void UninstallL(const TUint32 aServiceId); 

	/**
	 * See MIMPluginObserver::InstallL
	 */
	void InstallL(const TUint32 aServiceId); 

	/**
	 * See MIMPluginObserver::NewMessageL
	 */
	void NewMessageL(const TIndicationData& aIndicationData);

	/**
	 * See MIMPluginObserver::OfflineL
	 */
	void OfflineL(const TUint32 aServiceId); 

	/**
	 * CreateIconL creates an icon of the specified bitmaps id's
	 * @param aSmallBitmap		The id of the small bitmap
	 * @param aSmallBitmapMask	The id of the small bitmap's mask
	 * @param aLargeBitmap		The id of the large bitmap
	 * @param aLargeBitmapMask	The id of the large bitmap's mask
	 * @return CImIcon			A pointer to the created icon. Ownership is transfered to the caller.
	 */
	CImIcon* CreateIconL(TInt aSmallBitmap, TInt aSmallBitmapMask, TInt aLargeBitmap, TInt aLargeBitmapMask);
private:
	/** Pointer to the ecom handler */
	CEcomHandler*		iEcomHandler;

	/** A pointer to the array of available services */
	CImServiceArray*	iServiceArray;

	/** Pointer to a list of contacts that notification are request for */
	CRequestedContacts* iRequestedContacts;
};


#endif // __IMFRAMEWORK_H