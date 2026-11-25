// APFREC.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#if !defined(__APFREC_H__)
#define __APFREC_H__

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif
#if !defined(__APAFLREC_H__)
#include <apaflrec.h>
#endif

#include <babackup.h>

// classes defined:
class CApaScanningFileRecognizer;
class CApaAppLocatorProxy;
//
// classes referenced:
class CApaAppFinder;
class TApaAppEntry;
class TEntry;
class RFs;
//

// dir in which app recognizers should live - this dir is scanned on all drives

/**
@internalTechnology
*/
_LIT(KAppRecognizerSearchPath,"\\System\\Recogs\\");

/**
@internalComponent
*/
_LIT(KAppRecognizerSearchString,"?:\\System\\Recogs\\");

/**
@internalComponent
*/
_LIT(KAppRecognizerSearchAnyFile,"*");

class CApaRecognizerDll; // private class

/** Constructs a recognizer type 

@publishedPartner
@released
*/
typedef CApaFileRecognizerType* (*CreateCApaFileRecognizerType)();

class CApaScanningFileRecognizer : public CApaFileRecognizer
/**
@publishedAll
@deprecated
*/
	{
public:
	class TRecognizer
		{
	friend class CApaRecognizerDll;
	friend class CT_FileStep;
	public:
		TRecognizer(HBufC* aName);
		inline const TDesC& Name() const;
	public:
		TUid iUid;
		TInt iDrive;
	private:
		inline TRecognizer();
		TRecognizer(const TRecognizer&);
		TRecognizer operator=(const TRecognizer&);
	private:
		HBufC* iName;
		};
	typedef CArrayFixFlat<TRecognizer> CRecognizerArray;
	//
private:
	class CApaBackupOperationObserver : public CBase, public MBackupOperationObserver
		{
	public:
		CApaBackupOperationObserver(CApaScanningFileRecognizer& aRecognizer);
		~CApaBackupOperationObserver();
		void RegisterObserverL();

		virtual void HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes);
		TInt UpdateCounter() const;
		void SetUpdateCounter( TInt aValue );
	private:
		CBaBackupSessionWrapper* iSession;
		CApaScanningFileRecognizer& iRecognizer;
		TInt iUpdateCounter;
		};
	friend class CApaScanningFileRecognizer::CApaBackupOperationObserver;
public:
	IMPORT_C static CApaScanningFileRecognizer* NewL(RFs& aFs,MApaAppStarter* aAppStarter);
	IMPORT_C ~CApaScanningFileRecognizer();
	IMPORT_C void ScanForRecognizersL();
	IMPORT_C TInt RecognizerCount();
	IMPORT_C void SetRecognizersFromListL(const CRecognizerArray& aList);
	IMPORT_C CRecognizerArray* RecognizerListLC()const;
	IMPORT_C void SetRecognizerL(const TRecognizer& aRecognizer); 
	IMPORT_C const TRecognizer& operator[](TInt aIndex)const; 
	IMPORT_C TInt UpdateCounter()const;
protected:
	IMPORT_C CApaScanningFileRecognizer(RFs& aFs,MApaAppStarter* aAppStarter);
	IMPORT_C void ConstructL();
	//
private:
	void ScanDriveL(TInt aDriveNum);
	void LoadRecognizerL(const TDesC& aFullName,TUid aUid);
	TInt RemoveRecognizer(CApaRecognizerDll* aDll);
private:
	CApaRecognizerDll* iRecognizerLib;
	MApaAppStarter* iAppStarter;
	CApaBackupOperationObserver* iObserver;
	};



class CApaAppLocatorProxy : public CApaAppLocator
/**
@internalComponent
*/
	{
public:
	IMPORT_C static CApaAppLocatorProxy* NewL(RFs& aFs);
	IMPORT_C TInt GetAppEntryByUid(TApaAppEntry& aAppEntry,TUid aAppUid);
	IMPORT_C TInt GetAppCapabilityByUid(TDes8& aCapabilityBuf,TUid aAppUid);
	IMPORT_C ~CApaAppLocatorProxy();
private:
	CApaAppLocatorProxy(RFs& aFs);
	void ConstructL();
	void DoGetAppEntryByUidL(TApaAppEntry& aAppEntry,TUid aAppUid);
private:
	RFs& iFs;
	CApaAppFinder* iAppFinder;
	};

inline const TDesC& CApaScanningFileRecognizer::TRecognizer::Name() const
	{
	return *iName;	
	}

inline CApaScanningFileRecognizer::TRecognizer::TRecognizer()
	{
	}

#endif
