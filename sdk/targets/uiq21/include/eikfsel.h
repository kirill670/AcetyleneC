// EIKFSEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFSEL_H__)
#define __EIKFSEL_H__

#if !defined(__EIKCHLST_H__)
#include <eikchlst.h>
#endif

#if !defined(__EIKEDWIN_H__)
#include <eikedwin.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__EIKLBI_H__)
#include <eiklbi.h>
#endif

#if !defined(__EIKTXLBX_H__)
#include <eiktxlbx.h>
#endif

#if !defined(__EIKFSO_H__)
#include <eikfso.h>
#endif


class CEikFileNameSelector : public CEikChoiceList, public MEikFileSelectionObserver
	{
public:
	enum TFlags
		{
		EMultiSelectionAllowed	= 0x0002,
		ESpecifiedFolderIsEmpty	= 0x0004
		};

public:
	IMPORT_C CEikFileNameSelector();
	IMPORT_C ~CEikFileNameSelector();
	IMPORT_C TFileName FullName() const;
	IMPORT_C void SetFullNameL(const TDesC& aFullName);
	IMPORT_C void GetFullNamesOfSelectedFilesL(CDesCArray* aFullNames) const;
	IMPORT_C void SetSelectedFileNamesL(CDesCArray* aFileNames);
	IMPORT_C TBool MultipleSelectionAllowed() const;
	IMPORT_C void SetMultipleSelectionAllowed(TBool aMultipleSelectionAllowed);
	IMPORT_C void SetFileSelectionObserver(MEikFileSelectionObserver* aObserver);
	IMPORT_C void ValidateStateL();
	IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void SetExtensionL(const TDesC& aExtension);
	inline const TDesC* Extension() const {return(iExtension);}
	IMPORT_C TBool MultipleFilesSelected() const;
	IMPORT_C void SetUidType(const TUidType& aUidType);
protected:
	void SetFlags(TInt aMask) {iFileSelectorFlags|=aMask;}
	void ClearFlags(TInt aMask) {iFileSelectorFlags&=(~aMask);}
	IMPORT_C MEikFileSelectionObserver* FileSelectionObserver() const;
	IMPORT_C TUidType UidType() const;
	IMPORT_C TInt BuildFileNameArrayL(const TParse& aParse, MDesCArray* aFileNames);
	IMPORT_C virtual void DoCreatePopoutL();
	IMPORT_C virtual void DestroyPopout();
	IMPORT_C virtual void HandleInteractionConfirmedL();
	IMPORT_C virtual void DrawContent() const;
	IMPORT_C virtual void CurrentItemChangedL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void TryFindCurrentItemL(const TDesC& aFullName);
	TInt TryBuildFileNameArrayL(const TDesC& aFullName);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
protected:
	CDesCArray* iSelectionArray;
	CDesCArray* iTempFileNameArray;
	TFileName iRef;
	HBufC* iExtension;
	TInt iFileSelectorFlags;
private:
	MEikFileSelectionObserver* iFileSelectionObserver;
	TUidType iUidType;
	TInt iSpare;
	};


class CEikFileSelectorListBox : public CEikTextListBox
	{
public:
	IMPORT_C CEikFileSelectorListBox();
protected:
	IMPORT_C virtual void CreateItemDrawerL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
	};


class CFileSelectorItemDrawer : public CTextListItemDrawer
	{
public:
	IMPORT_C CFileSelectorItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);
protected:
	IMPORT_C virtual void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aSelected) const;  
	};

class CEikFileNameEditor : public CEikEdwin, public MEikFileSelectionObserver
	{
public:
	IMPORT_C CEikFileNameEditor();
	IMPORT_C ~CEikFileNameEditor();
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void GetFullNameL(TFileName& aFileName);
	IMPORT_C void SetFullNameL(const TDesC& aFullName);
	IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);
	IMPORT_C void SetAppendExtension(TBool aAppendExtension);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	// from CCoeControl
	IMPORT_C virtual void Reserved_2();
	// from CEikEdwin
	IMPORT_C virtual void Reserved_3();
protected:
	TFileName iRef;
	TBool iAppendExtension;
private:
	TInt iSpare;
	};


class CEikDirectoryTreeListBox;

class CEikFolderNameSelector : public CEikChoiceList, public MEikFileSelectionObserver
	{
public:
	enum TFlags
		{
		EFullNameUpdate	= 0x0001,
		EShowSystem		= 0x0002
		};

public:
	IMPORT_C CEikFolderNameSelector();
	IMPORT_C ~CEikFolderNameSelector();
	IMPORT_C TFileName FullName() const;
	IMPORT_C void SetFullNameL(const TDesC& aFullName);
	IMPORT_C void SetRootL(const TDesC& aRoot);
	IMPORT_C void CreateFlattenedHierarchyL();
	IMPORT_C void SetFileSelectionObserver(MEikFileSelectionObserver* aObserver);
	IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);
	IMPORT_C CEikDirectoryTreeListBox* PopoutDirTreeListBox() const;
	IMPORT_C void SetShowSystem(TBool aShowSystem);
public: // framework
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
protected: // framework
	IMPORT_C virtual void MatchTypedChar(TUint aCode);
	IMPORT_C virtual void HandleInteractionConfirmedL();
	IMPORT_C virtual void CurrentItemChangedL();
	IMPORT_C virtual void DrawContent() const;
	IMPORT_C virtual void CreateListBoxL();
	IMPORT_C virtual void InitializeListBoxL();
	IMPORT_C virtual void ActivateListBoxL();
	IMPORT_C virtual void SetListBoxExtentL();
	IMPORT_C virtual void DestroyPopout();
protected:  // new functions
	IMPORT_C void ExpandFolderL(TDes* aPath, TInt aPositionToInsertSubFolders);
	IMPORT_C void FullyExpandFolderL(TInt aIndexOfFolderToFullyExpand, TBool aAutoExpandAllFolders);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void SetRootFromReferenceL();
private: // from CCoeControl
	IMPORT_C void Reserved_2();
protected:
	MEikFileSelectionObserver* iFileSelectionObserver;
	TFileName iRoot;
	TFileName iRef;
	TFileName iCurrentPath;
	TInt iFolderSelectorFlags;
private:
	TInt iSpare;
	};


class CEikFolderNameEditor : public CEikEdwin, public MEikFileSelectionObserver	
	{
public:
	IMPORT_C CEikFolderNameEditor();
	IMPORT_C ~CEikFolderNameEditor();
	IMPORT_C TFileName FullName() const;
	IMPORT_C void SetFullNameL(const TDesC& aFullName);
	IMPORT_C void ValidateStateL();
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
protected:
	TFileName iRef;
private:
	TInt iSpare;
	};


typedef TBuf<1> TEikDriveName;

class CEikDriveNameSelector : public CEikChoiceList
	{
public:
	enum TFlags {EHideROM = 0x0001, EAllowCorruptDisk = 0x0002};
public:
	IMPORT_C CEikDriveNameSelector();
	IMPORT_C CEikDriveNameSelector(TInt aFlags);
	IMPORT_C ~CEikDriveNameSelector();
	IMPORT_C TFileName FullName() const;
	IMPORT_C void SetFullNameL(const TDesC& aFullName);
	IMPORT_C void SetFileSelectionObserver(MEikFileSelectionObserver* aObserver);
	IMPORT_C void AllowCorruptDisk(TBool aAllowCorruptDisk);
	IMPORT_C void ShowRom(TBool aShowRom);
public: // framework
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
protected:
	IMPORT_C void BuildDriveNameArrayL();
protected: // framework
	IMPORT_C virtual void CurrentItemChangedL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	TEikDriveName DriveNameFromFullName(const TDesC& aFullName) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
protected:
	MEikFileSelectionObserver* iFileSelectionObserver;
	TFileName iRef;
	TInt iDriveSelectorFlags;
private:
	TInt iSpare;
	};


#endif
