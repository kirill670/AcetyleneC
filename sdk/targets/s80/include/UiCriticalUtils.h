// UiCriticalUtils.h
//

#ifndef __UICRITICALUTILS_H__
#define __UICRITICALUTILS_H__

#include <e32std.H>
#include <f32file.H>

/*!
	\brief A static utility class to help File access
*/
class CCoeEnv;
class CEikonEnv;

class CUiCriticalUtil
	{
public:
	enum TOperationFailedType
		{
		EInternalMemory,
		EMMCCard,
		EBoth
		};

	IMPORT_C static TInt CheckFileToCopyAndReportL(CCoeEnv& aCoeEnv, const TDesC& aSourceName, const TDesC& aTargetName);
	IMPORT_C static TInt CheckFileToAddAndReportL(CCoeEnv& aCoeEnv, const TDesC& aFileName, TInt aFileSize);
	IMPORT_C static TInt CheckFileToAddAndReportL(CCoeEnv& aCoeEnv, TInt aDrive, TInt aFileSize);
	
	IMPORT_C static TInt CheckFileToAdd(RFs& aFs, const TDesC& aFileName, TInt aFileSize);
	IMPORT_C static TInt CheckFileToAdd(RFs& aFs, TInt aDrive, TInt aFileSize);
	IMPORT_C static void ReportDiskFullErrorL(CCoeEnv& aCoeEnv, const TDesC& aDrive);

private:
	enum TResourceStringType
		{
		EFullInternalAndMMC,
		EFullInternal,
		EFullInternalNoMMC,
		EOpFailInternal,
		EOpFailInternalNoMMC,
		EFullMMC,
		EOpFailMMC
		};

	static void OperationFailedDialogL(CCoeEnv& aCoeEnv, TOperationFailedType aDialogType);
	static TBool DeviceHasMemoryCard(RFs& aFs, TInt64& aFreeSpace);
	static TInt InternalDiskSpace(RFs& aFs, TInt64& aFreeSpace);
	static void GetCriticalNotificationResources(TInt& aTextId, TInt& aButtonId, TResourceStringType aType);
	};

#endif // __UICRITICALUTILS_H__
