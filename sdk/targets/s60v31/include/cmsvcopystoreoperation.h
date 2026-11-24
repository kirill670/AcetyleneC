// CMsvCopyStoreOperation.h
//
// Copyright (c) 2004-2005 Symbian Software Ltd.  All rights reserved.
//

/**
@internalComponent
@released
*/
class CMsvCopyStoreOperation : public CMsvServerOperation
	{
public:
	static CMsvCopyStoreOperation* NewL(const RMessage2& aMessage, CMsvServer& aServer);
	~CMsvCopyStoreOperation();
	//
	const virtual TDesC8& Progress(); // Inherited from CMsvServerOperation
	void StartL();
	//
private:
	CMsvCopyStoreOperation(const RMessage2& aMessage, CMsvServer& aServer);
	void DoCancel(); // Inherited from CActive
	void RunL();	 // Inherited from CActive
	TInt RunError(TInt aError);
	
	void InitCopyStoreL();
	void CopySourceL();
	void FinishCopyStoreL();
	void LockMailStoreL();
	void UnlockMailStore();
	void CompleteSelf();
	void Completed(TInt aError);
	void CheckDiskSpaceL();
private:
	TPckgBuf<TMsvCopyProgress> iProgress;
	TDriveUnit iDrive;
	TInt iPos;
	CMsvServer& iServer;
	TFileName iDest;
	TFileName iIndex;
	TFileName iSrc;
	CDir* 	  iDir;
	CFileMan*	  iFileMan;
	
	};
