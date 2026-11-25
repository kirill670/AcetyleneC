//
// smlTask.h
//

#ifndef __SMLTASK_H__
#define __SMLTASK_H__

/**

The CSmlTask class represents a synchronisation task. It comprises a Content Provider,
a Source database or path, and a Target database or path. It can also be enabled or
disabled: a disabled task will not run when Synchronise is called on its profile

*/
class CSmlTask : public CBase
	{
	friend class CSmlController;
public:
	static CSmlTask* NewL(const CSmlTask& aTask); // just for profiles
	static CSmlTask* NewL();
	static CSmlTask* NewLC();

	IMPORT_C const CSmlIdentifier& Identifier() const;
	IMPORT_C void SetNameL(const TDesC& aName);
	
	IMPORT_C void SetProviderL(const CSmlIdentifier& aProvider);
	IMPORT_C const CSmlIdentifier& Provider() const;
	
	IMPORT_C void SetSourceL(const CSmlIdentifier& aSource);
	IMPORT_C const CSmlIdentifier& Source() const;
	
	IMPORT_C void SetTargetL(const CSmlIdentifier& aTarget);
	IMPORT_C const CSmlIdentifier& Target() const;
	
	virtual ~CSmlTask();

	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	
	void SetTaskState(TUint aState);
	TUint TaskState() const;

	TBool IsModified() const;

	TBool DataComplete() const;
	void EnableTask(TBool aEnable = ETrue);
	TBool TaskEnabled() const;

	void SetIdentifierL(const CSmlIdentifier& aIdentifier);
	void SetIdL(TUint aId);

private:
	CSmlTask();
	void ConstructL();
	void ConstructL(const CSmlTask& aTask);

// data
	CSmlIdentifier* iIdentifier;// id & name of this task
	CSmlIdentifier* iProvider;	// id & name of provider
	CSmlIdentifier* iSource;	// Source: database or filepath
	CSmlIdentifier* iTarget;	// Target: database or filepath
	TUint iState;				// enum of task states
	TBool iEnabled;				// enabled state of task
	};

#endif // __SMLTASK_H__