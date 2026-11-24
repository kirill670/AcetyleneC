// CMsvDeleteStoreOperation.h
//
// Copyright (c) 2004 Symbian Software Ltd.  All rights reserved.
//


#include "CCopyFiles.h"
#include "CCopyOneFile.h"


/**
@internalComponent
@released
*/
class CMsvDeleteStoreOperation : public CMsvServerOperation
	{
public:
	CMsvDeleteStoreOperation(const RMessage2& aMessage, CMsvServer& aServer);
	~CMsvDeleteStoreOperation();
	//
	virtual const TDesC8& Progress(); // Inherited from CMsvServerOperation
	void Start();
	//
private:
	virtual void DoCancel();   // Inherited from CActive
	virtual void RunL();	   // Inherited from CActive
	TInt RunError(TInt aError);
	void DeleteMailStoreL();
	void Completed(TInt);
	//
private:
	TPckgBuf<TMsvDeleteProgress> iProgress;
	TDriveUnit iDrive;
	CMsvServer& iServer;
	TFileName iToDelete;
	CFileMan* iFileMan;	
	};

