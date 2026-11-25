// EIKUFSEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKUFSEL_H__)
#define __EIKUFSEL_H__

#if !defined(__EIKFSEL_H__)
#include <eikfsel.h>
#endif

// class CEikUnifiedFileNameSelector only availiable to platform-004 and higher

class CEikUnifiedFileNameSelector : public CEikFileNameSelector
	{
public:
	IMPORT_C CEikUnifiedFileNameSelector();
	IMPORT_C void SetROMIncluded(TBool aIncludeROM);
	IMPORT_C TBool ROMIncluded();
public:
	IMPORT_C TFileName FullName() const;
	IMPORT_C void SetFullNameL(const TDesC& aFullName);
	IMPORT_C void GetFullNamesOfSelectedFilesL(CDesCArray* aFullNames) const;
	IMPORT_C void SetSelectedFileNamesL(CDesCArray* aFileNames);
protected:
	IMPORT_C virtual void BuildFileNameArrayL(const TParse& aParse, MDesCArray* aFileNames);
protected: // from CEikFileNameSelector
	IMPORT_C virtual void DoCreatePopoutL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	TInt TryFindCurrentItemL(const TDesC& aFullName);
	TInt TryBuildFileNameArrayL(const TDesC& aFullName, MDesCArray* aFileNames);
private:
	void SpecialMessageL(TDesC& aMessage);
	void ParseToRearL(TFileName& aFileName) const;
	void ParseToFront(TFileName& aFileName) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TBool iIncludeROM;
	};


#endif
