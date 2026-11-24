// APGCTL.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2004. All rights reserved.
//

#ifndef __APGCTL_H__
#define __APGCTL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

// classes defined:
class CApaSystemControl;
class CApaSystemControlList;
//
// classes referenced:
class RFs;
class CApaMaskedBitmap;
//

/**
Calls the control DLL's first ordinal function to create and run the control.

The function leaves with KErrBadLibraryEntryPoint if the ordinal 1 function 
cannot be found.

@publishedAll 
@released
*/
typedef TInt (*ApaRunSystemControl)(const TDesC&);

/**
@publishedAll 
@released
*/
#ifdef _UNICODE
#define KUidSystemControlDll KUidSystemControlDll16
#else
#define KUidSystemControlDll KUidSystemControlDll8
#endif

/**
@publishedAll 
@deprecated
*/
const TInt KSystemControlDllUidValue8=0x10000297;

/**
@publishedAll
@deprecated
*/
const TUid KUidSystemControlDll8={KSystemControlDllUidValue8};

/**
@publishedAll
@released
*/
const TUid KUidSystemControlDll16={0x10003A34};


class CApaSystemControl : public CBase
/** Wrapper for a plug-in extension to the control panel.

An instance of the class represents an extension control's DLL. It is also 
a cache for the control's icon and caption.

An instance of the wrapper can only be constructed by the control list, which 
is a CApaSystemControlList object that is part of the internal implementation 
of Symbian OS. 

@publishedAll
@released */
	{
public:
	IMPORT_C void CreateL();
	IMPORT_C TUid Type()const;
	IMPORT_C TFileName FileName()const;
	IMPORT_C CApaMaskedBitmap* Icon()const; // one size of icon, 48x48?
	IMPORT_C TPtrC Caption()const;
	IMPORT_C TPtrC ShortCaption()const;
private:
	static CApaSystemControl* NewL(RFs& aFs,const TDesC& aFullPath,const TUidType aUidType);
	~CApaSystemControl();
	//
	CApaSystemControl(RFs& aFs);
	void ConstructL(const TDesC& aFullPath,const TUidType aUidType);
private:
	CApaSystemControl* iNext;
	HBufC* iCaption;
	HBufC* iShortCaption;
	CApaMaskedBitmap* iIcon;
	TBool iExists; // used during updating
	TFileName iFullPath;
	TUidType iUidType;
	RFs& iFs;
	//
	friend class CApaSystemControlList;
	};



class CApaSystemControlList : public CBase
/** Provides a list of all available control panel plugin DLLs present on the phone. 
Control panel plugins are located in \\system\\controls\\ on any local drive. They 
have a .ctl extension and a UID2 of KUidSystemControlDll. They are uniquely 
identified by their UID3. Each control panel plugin may have an accompanying caption 
resource file to contain its caption and short caption in multiple languages. If it 
doesn't, its caption defaults to the dll name. 

This class is implemented as a linked list of CApaSystemControls. It also manages 
rescanning of the file system to locate new control panel plugins. 

@see CApaSystemControl
@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CApaSystemControlList* NewL(RFs& aFs);
	IMPORT_C ~CApaSystemControlList();
	//
	IMPORT_C TInt Count()const;
	IMPORT_C TInt Index(TUid aType)const;
	IMPORT_C CApaSystemControl* Control(TInt aIndex)const;
	IMPORT_C CApaSystemControl* Control(TUid aType)const;
	//
	IMPORT_C void UpdateL();
	inline TInt UpdateCount()const;
private:
	CApaSystemControlList(RFs& aFs);
	void ConstructL();
	CApaSystemControl* PreviousControl(CApaSystemControl* aControl)const;
private:
	TInt iUpdateCount;
	RFs& iFs;
	CApaSystemControl* iControl;
	};


//
// inlines
//


inline TInt CApaSystemControlList::UpdateCount()const
/** Gets the number of times the control panel plugin list has been 
updated (by calling UpdateL()). It returns 1 for a newly created list.

@return The number of times the list has been changed. */
	{ return iUpdateCount; }



#endif
