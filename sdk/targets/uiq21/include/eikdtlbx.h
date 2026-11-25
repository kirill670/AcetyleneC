// EIKDTLBX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDTLBX_H__)
#define __EIKDTLBX_H__

#if !defined(__EIKHLBX_H__)
#include <eikhlbx.h>
#endif

#if !defined(__EIKLBED_H__)
#include <eiklbed.h>
#endif

#if !defined(__EIKDTLBM_H__)
#include <eikdtlbm.h>
#endif

class TResourceReader;

class CEikDirectoryTreeListBox : public CEikHierarchicalListBox, public MHierarchicalListExpansionObserver
	{
public:
    IMPORT_C CEikDirectoryTreeListBox();
    IMPORT_C ~CEikDirectoryTreeListBox();
	IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags,TInt aModelFlags,TInt aNumVisibleLines=0,TInt aWidthInPixels=0);
	IMPORT_C void CreateListL(TDriveNumber* aDrive);
	IMPORT_C void UpdateL();
	IMPORT_C void SetCurrentItemPathL(const TDesC& aPath);
	IMPORT_C CDirectoryTreeListBoxModel* DtlModel() const;
public: // framework
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKayEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
public: // from MHierExpansionObserver
	IMPORT_C void UpdateHierarchyL(TInt aItemIndex);
public: // from CEikListBox
	IMPORT_C void EditItemL(TInt aMaxLength);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void BaseConstructL(TInt aModelFlags);
	void CheckForErrorFromFileServerL(TInt aErrorCode);
	TInt NewItemIndex(const TDesC& aItemPath) const;
	void SetCurrentItemName(const TDesC& aName,TInt aItemLevel,TInt& aSearchFromIndex);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TBool* iDtlbxDestroyed;
	};

class CEikDirTreeListBoxEditor : public CEikListBoxTextEditor
	{
public:
	IMPORT_C CEikDirTreeListBoxEditor( MListBoxModel* aModel );
	IMPORT_C ~CEikDirTreeListBoxEditor();
public: // from MEikListBoxEditor
	IMPORT_C TPtrC ItemText();
	IMPORT_C TBool UpdateModelL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TInt iSpare;
	};

#endif
