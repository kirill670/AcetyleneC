// regpsdll.h
//
// Copyright (c) 1999-2004 Symbian Software Ltd.  All rights reserved.
//
// A revised version of the CRegisteredParserDll class.  This no longer uses a 
// reference to a CParserRegistrationData object.  Instead a UidType is passed in 
// the  constructor, or through a set method.  The class is used to find the file 
// which contains a parser, to load and maintain a reference count of the number of 
// objects using the dll, so that it can be unloaded when no longer required. 
// It will also unload the dll when a new parser is required.



#ifndef __REGPSDLL_H__
#define __REGPSDLL_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__

#include <e32base.h>

// forward declarations
class RWriteStream;
class RReadStream;
class RFs;

//
//  Real non-derivable class
//
class CRegisteredParserDll : public CTimer
/** Finds, loads and maintains a reference count of client processes for a BIO 
parser DLL.

When the reference count falls to 0, the class is also responsible for unloading 
the DLL. The public interface for this class is used only by CBIOServerMtm. 
@internalTechnology
@released
*/
	{
public:
#ifndef __HIDE_MESSAGING_API_V1__	
    IMPORT_C static CRegisteredParserDll* NewL(TUidType& aParserUidType);
#endif // __HIDE_MESSAGING_API_V1__
#ifdef __MESSAGING_API_V2__	
    IMPORT_C static CRegisteredParserDll* NewL(TDesC& aParserName);
#endif // __MESSAGING_API_V2__

    IMPORT_C ~CRegisteredParserDll();

	inline TInt DllRefCount() const;
	inline TUidType UidType() const;
	inline void SetUidType(const TUidType& aUidType);

	IMPORT_C TInt GetLibrary(RFs& aFs,RLibrary& aDllLibrary);   // Increments reference count if successful or returns error 
	IMPORT_C void ReleaseLibrary();                                   // Decrements access count
	                                                                  // Should be called from destructor of any objects created from the library 
private:
#ifndef __HIDE_MESSAGING_API_V1__	
	CRegisteredParserDll(TUidType& aParserUidType);
#endif
#ifdef __MESSAGING_API_V2__	
	CRegisteredParserDll(const TDesC& aParserName);
#endif
    void ConstructL();

	void LoadLibraryL(RFs& aFs);   
	TInt FindFullName(RFs& aFs,TDes& aFullName); 

private:
	TUidType iUidType;
#ifdef __MESSAGING_API_V2__	
    TPtrC iParserName;
#endif
	RLibrary iParserDllLibrary;
	TInt iDllRefCount;

    void RunL();
    enum { KReleaseLibraryTimeout = 30000000 };
	};

#include "regpsdll.inl"
#endif
