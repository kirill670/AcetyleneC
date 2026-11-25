//
// smlProfile.h
//

#ifndef __SMLPROFILE_H__
#define __SMLPROFILE_H__

typedef const RPointerArray<const CSmlTask>& RSmlTaskArray;

/**

The CSmlProfile class represents a synchronisation profile which comprises
information to be able to connect and synchronise to a particular server,
as well as information about what data to synchronise to the server

*/
class CSmlProfile : public CBase
	{
	friend class CSmlController;
public:
	IMPORT_C static CSmlProfile* NewL(CSmlController* aController);
	IMPORT_C static CSmlProfile* NewLC(CSmlController* aController);

	IMPORT_C const CSmlIdentifier& Identifier() const;
	IMPORT_C void SetProfileNameL(const TDesC& aProfileName);

	IMPORT_C void SetUserNameL(const TDesC& aUserName);
	IMPORT_C const TDesC& UserName() const;
	IMPORT_C void SetPasswordL(const TDesC& aPassword);
	IMPORT_C const TDesC& Password() const;
	
	IMPORT_C void SetTransportUserNameL(const TDesC& aUserName);
	IMPORT_C const TDesC& TransportUserName() const;
	IMPORT_C void SetTransportPasswordL(const TDesC& aPassword);
	IMPORT_C const TDesC& TransportPassword() const;
	
	IMPORT_C void SetTargetServerAddressL(const TDesC& aServerAddr);
	IMPORT_C const TDesC& TargetServerAddress() const;
	
	IMPORT_C void SetProtocolL(const CSmlIdentifier& aProtocol);
	IMPORT_C const CSmlIdentifier& Protocol() const;

	IMPORT_C RSmlTaskArray ListTasks() const;
	IMPORT_C void ListTaskIdsL(RPointerArray<const CSmlIdentifier>& aList) const;
	IMPORT_C const CSmlTask& TaskL(const CSmlIdentifier& aId) const;
	
	IMPORT_C CSmlTask* NewTaskLC(const CSmlIdentifier* aProvider = NULL);
	IMPORT_C const CSmlIdentifier& AddTaskL(CSmlTask& aTask);
	IMPORT_C void RemoveTaskL(const CSmlIdentifier& aId);

	IMPORT_C void EnableTaskL(const CSmlIdentifier& aId, TBool aEnable = ETrue);
	IMPORT_C TBool TaskEnabledL(const CSmlIdentifier& aId) const;

	IMPORT_C TBool DataComplete() const;

	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	
	virtual ~CSmlProfile();

private:
	CSmlProfile(CSmlController* aController);
	void ConstructL();

	TBool TaskExistsL(const CSmlTask& aTask);
	void ConvertText(HBufC* aData);

// data
	CSmlIdentifier* iIdentifier;		  // name & Id of this profile
	HBufC* iUsername;					  // Username to server
	HBufC* iPassword;					  // Password to server
	HBufC* iTransportUsername;			  // Transport username
	HBufC* iTransportPassword;			  // Transport Password
	HBufC* iTargetAddress;				  // Address of the server eg "192.168.23.1//servlet//fde.sync.SyncML"
	CSmlIdentifier* iProtocol;			  // transport protocol to use
	RPointerArray<const CSmlTask> iTasks; // array of tasks in this profile
	RPointerArray<CSmlTask> iDeletedTasks;// array of deleted tasks in this profile
	CSmlController* iController;		  // the controller
	};

#endif // __SMLPROFILE_H__