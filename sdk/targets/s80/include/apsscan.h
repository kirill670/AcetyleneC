// APSSCAN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// AppArc recognizer and application scanning
//

#if !defined(__APSSCAN_H__)
#define __APSSCAN_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif


class CApaFsMonitor : public CActive
/** A low priority (EPriorityIdle) active object which monitors changes 
in the file system. 

If a change is detected, the callback function supplied by the user of the class 
is called after a 0.25 second delay. If there are further changes, the callback 
is not called again until 3 seconds have elapsed. It uses RFs::NotifyChange() 
to request notifications.

@see RFs::NotifyChange()

@publishedPartner 
@released */
	{
public:
	IMPORT_C ~CApaFsMonitor();
	IMPORT_C static CApaFsMonitor* NewL(RFs& aFs, const TDesC& aLocation, TCallBack aCallBack);
	IMPORT_C void SetBlocked(TBool aIsBlocked);
	IMPORT_C void Start(TNotifyType aNotifyType);
	IMPORT_C TNotifyType NotifyType() const;
private:
	CApaFsMonitor(RFs& aFs, const TDesC& aLocation, TCallBack aCallBack);
	static TInt TimerCallBack(TAny* aObject);
	void DoStart();
	void DoCancel();
	void RunL();
private:
	RFs& iFs;
	TNotifyType iNotifyType;
	TCallBack iCallBack;
	CPeriodic* iFsTimer;
	TFileName iLocation;
	TBool iFsHasChanged;
	TBool iIsBlocked;
	TBool iIsSubsequentCall;
	};

#endif