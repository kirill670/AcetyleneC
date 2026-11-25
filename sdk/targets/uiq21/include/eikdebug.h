// EIKDEBUG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDEBUG_H__)
#define __EIKDEBUG_H__

//#define UIKON_OOM_TESTING		// enabling the testing requires also adding the FBSRV.LIB to eiksrvs and console mmp file.

#if defined(UIKON_OOM_TESTING)
#define __SHOW_FAIL_RATE(aFormatString, aFailRate) RDebug::Print(aFormatString,aFailRate)
#else
#define __SHOW_FAIL_RATE(aFormatString, aFailRate)
#endif

//
//	class CEikDebugPreferences
//

/**
 * @private
 */
class CEikDebugPreferences : public CBase
	{
public:
	enum TFlag
		{
		EFlagDebugKeysOn				=0x00000001,
		EFlagOOMTestingOnAppStartUp		=0x00000002,
		EFlagOOMTestingOnEiksrvStartUp	=0x00000004,
		EFlagOOMTestingOnConsoleStartUp	=0x00000008
		};
public:
	IMPORT_C static CEikDebugPreferences* New();
	IMPORT_C static CEikDebugPreferences* NewL();
	IMPORT_C static CEikDebugPreferences* NewLC();
	IMPORT_C ~CEikDebugPreferences();
	IMPORT_C void StoreL(RFs& aFileServerSession);
	IMPORT_C TInt Restore(RFs& aFileServerSession); // can be used with or without a CTrapHandler being currently installed
	IMPORT_C void RestoreL(RFs& aFileServerSession);
	inline void SetFlags(TUint aFlags);
	inline TUint Flags() const;
private:
	CEikDebugPreferences();
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
private:
	TUint iFlags;
	TUint iSpare;
	};

inline void CEikDebugPreferences::SetFlags(TUint aFlags)
	{
	iFlags=aFlags;
	}

inline TUint CEikDebugPreferences::Flags() const
	{
	return iFlags;
	}

#endif

