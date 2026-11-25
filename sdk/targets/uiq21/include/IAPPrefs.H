#ifndef IAPPrefs__
#define IAPPrefs__

#include <e32base.h>
#include <msvapi.h>
#include <msvuids.h>
#include <cdbcols.h>

// Note: Version 1 = EPOC6.1
//		 Version 2 = EPOC6.2 / Hurricane
const TInt KImIAPPreferencesVersion = 2;	// identify which version of this class has been stored

// for builds which don't define it.
/*
enum TCommDbDialogPref
	{
	ECommDbDialogPrefUnknown =0,
	ECommDbDialogPrefPrompt,
	ECommDbDialogPrefWarn,
	ECommDbDialogPrefDoNotPrompt
	};
*/

class TImIAPChoice
	{
	public:
	TUint32	iIAP;
	TCommDbDialogPref iDialogPref;
	};

class CImIAPPreferences : public CBase
	{
	public:
		IMPORT_C static CImIAPPreferences* NewLC();
		IMPORT_C TInt Version() const;
		IMPORT_C void RestoreL(CMsvStore& aMessageStore);
		IMPORT_C void StoreL(CMsvStore& aMessageStore) const;
		IMPORT_C TInt NumberOfIAPs() const;
		IMPORT_C TImIAPChoice IAPPreference(TInt aPreference) const;
		IMPORT_C void AddIAPL(TImIAPChoice aIap, TInt aPreferenceNumber=0);
		IMPORT_C void RemoveIAPL(TInt aPreferenceNumber);
		IMPORT_C TInt FindIAPL(TUint32 aIAP, TInt &aLocation) const;
		IMPORT_C void ReplaceIAPL(TInt aPreferenceNumber,TImIAPChoice aIap);
		IMPORT_C ~CImIAPPreferences();
		// class constants
		enum 
			{
			KSanityCheckOldWins = 0xEFBEADDE,
			KSanityCheck = 0xDEADBEEF
			};
		const static TUid KUidMsgFileInternetAccessPreferences;
	private:
		CArrayFixFlat<TImIAPChoice>* iChoices;
		TInt iVersion;
	private:
		CImIAPPreferences();
		CImIAPPreferences(CImIAPPreferences& aOther); // not implemented
		int operator=(CImIAPPreferences& aOther); // not implemented
		void ConstructL();
		void Panic(int err) const;
	};

#endif
