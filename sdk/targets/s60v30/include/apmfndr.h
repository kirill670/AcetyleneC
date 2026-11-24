// APMFNDR.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2004.  All rights reserved.
//

#if !defined (__APMFNDR_H__)
#define __APMFNDR_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__APMREC_H__)
#include <apmrec.h>
#endif

#include <babackup.h>

/**
@internalComponent
*/

// classes defined
class CApaRecognizerDll;


class CApaScanningDataRecognizer : public CApaDataRecognizer
/**
@publishedPartner 
@released 
*/
	{
public:
	class TRecognizer
		{
	friend class CApaRecognizerDll;
	friend class CT_MimeStep;
	public:
		TRecognizer(HBufC* aName);
		inline const TDesC& Name() const;
	public:
		TUid iUid;
		TInt iDrive;
		TTime iModified;
	private:
		inline TRecognizer();
		TRecognizer(const TRecognizer&);
		TRecognizer operator=(const TRecognizer&);
	private:
		HBufC* iName;
		};
	typedef CArrayFixFlat<TRecognizer> CRecognizerArray;

private:
	class CApaBackupOperationObserver : public CBase, public MBackupOperationObserver
		{
	public:
		CApaBackupOperationObserver(CApaScanningDataRecognizer& aRecognizer);
		~CApaBackupOperationObserver();
		void RegisterObserverL();

		virtual void HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes);
		TInt UpdateCounter() const;
		void SetUpdateCounter( TInt aValue );
	private:
		CBaBackupSessionWrapper* iSession;
		CApaScanningDataRecognizer& iRecognizer;
		TInt iUpdateCounter;
		};
	friend class CApaScanningDataRecognizer::CApaBackupOperationObserver;

	//
public:
	IMPORT_C static CApaScanningDataRecognizer* NewL(RFs& aFs);
	IMPORT_C ~CApaScanningDataRecognizer();
	IMPORT_C void ScanForRecognizersL();
	IMPORT_C TInt RecognizerCount();
	IMPORT_C CRecognizerArray* RecognizerListLC()const;
	IMPORT_C const TRecognizer& operator[](TInt aIndex)const;
	IMPORT_C TInt UpdateCounter()const;

#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
	IMPORT_C void SetRecognizersFromListL(const CRecognizerArray& aList);
	inline void SetRecognizersFromList(const CRecognizerArray& aList);
	IMPORT_C void SetRecognizerL(const TRecognizer& aRecognizer); 
#endif

protected:
	IMPORT_C CApaScanningDataRecognizer(RFs& aFs);
	IMPORT_C void ConstructL();
private:
	void ScanDriveL(TInt aDriveNum);
	void LoadRecognizerL(const TDesC& aFullName,TUid aUid, const TTime& aTime);
	TInt RemoveRecognizer(CApaRecognizerDll* aDll);
	void LoadEcomRecognizerL(TDriveUnit& aDrive,TUid aUid);
	void ScanForEcomRecognizersL();
public:
	IMPORT_C void SetEcomRecognizersFromListL(const CRecognizerArray& aList);
	IMPORT_C void SetEcomRecognizerL(const TRecognizer& aRecognizer); 
private:
	friend class CApaBackupObserver;
	CArrayPtrFlat<CApaRecognizerDll> iRecognizerLib;
	CApaBackupOperationObserver* iObserver;
	};


class CApaRecognizerDll : public CBase
/**
@internalTechnology
*/
	{
public:
	CApaRecognizerDll(HBufC* aName);
	~CApaRecognizerDll(); // closes lib and deletes next
public:
	enum TPresence { ENotPresent, EIsPresent, ESuperseded };
public:
	RLibrary iLibrary;
	CApaRecognizerDll* iNext;
	CApaScanningDataRecognizer::TRecognizer iId; // cached so that this data can be accessed from other threads (RLibrary cant be used in this case)
	CApaDataRecognizerType* iRec; // not ownership
	TPresence iPresent;
	};

//
// inlines
//

#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
inline void CApaScanningDataRecognizer::SetRecognizersFromList(const CRecognizerArray& aList)
/**
@deprecated
Deprecated in 7.0s - Use CApaScanningDataRecognizer::SetRecognizersFromListL instead as loading recognizers could leave.
*/
	{
	SetRecognizersFromListL(aList);
	}
#endif

inline const TDesC& CApaScanningDataRecognizer::TRecognizer::Name() const
	{
	return *iName;
	}

inline CApaScanningDataRecognizer::TRecognizer::TRecognizer()
	{
	}

#endif
