// BioUtil.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Public header for BIO-message Utilities DLL 
// 
// Class CBioIconUtils will return the bitmaps for a given Bio Msg type. 
//

#if !defined(__BIOUTIL_H__)
#define __BIOUTIL_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>		// IMPORT_C
#endif

#if !defined(__MTUDBAS_H__)
#include <mtudcbas.h>		// CBitmapArray
#endif

#if !defined(__BIODB_H__)
#include <biodb.h>			// MBifChangeObserver, CBifObserver...
#endif 

// Forward declerations
class TMsvEntry;
class CBase;
class CBioIcons;
class CCoeEnv;
class CMsvOperation;

class CBioIconUtils : public CBase, public MBifChangeObserver
	{
public:	
	//
	// Construction/destruction
	IMPORT_C static CBioIconUtils* NewL(CCoeEnv& aCoeEnv);
	IMPORT_C ~CBioIconUtils();

	IMPORT_C const CBaseMtmUiData::CBitmapArray& ContextIcon(const TMsvEntry& aContext,TInt aStateFlags) const;

private:		
	//
	// Construction/destruction
	CBioIconUtils(CCoeEnv& aCoeEnv);
	void ConstructL();

	//
	// Utility
	void ResetAndLoadIconsL();
	void ResetAndDestroyIconArray();
	CBioIcons* CreateBioIconsL(TUid aMsgUid,const TDesC& aMbmFilename,TInt aBitmapCount);

	// from MBifChangeObserver
	virtual void HandleBifChangeL(TBifChangeEvent aEvent, TUid aBioID);

private:
	CCoeEnv&					iCoeEnv;
	CArrayPtrFlat<CBioIcons>*	iIconArrays;
	CBifChangeObserver*			iBifObserver;
	CArrayPtr<CFbsBitmap>*		iLastResortIcon;
	};


#endif

