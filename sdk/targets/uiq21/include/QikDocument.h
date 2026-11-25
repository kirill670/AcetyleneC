// QikDocument.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0


#ifndef __QIKDOCUMENT_H__
#define __QIKDOCUMENT_H__

#include <eikdoc.h>

/**
 * @short Extra Document layer closing down applications when EReleaseRam is received
 */
class CQikDocument : public CEikDocument
	{
public:
	IMPORT_C CQikDocument(CEikApplication& aApp);
	IMPORT_C ~CQikDocument();
public:	// from CEikDocument
	IMPORT_C void SaveL(MSaveObserver::TSaveType aSaveType);
	IMPORT_C void UpdateTaskNameL(CApaWindowGroupName* aWgName);
public: // from CApaDocument
	IMPORT_C void NewDocumentL();
	IMPORT_C CFileStore* CreateFileStoreLC(RFs& aFs,const TDesC& aFileName);
	IMPORT_C void EditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly=EFalse);
	IMPORT_C void PrintL(const CStreamStore& aSourceStore);
	IMPORT_C void SaveL();
	IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool HasChanged() const;
private: // reserved functions from CApaDocument
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private:	
	IMPORT_C virtual void CQikDocument_reserved1();
	IMPORT_C virtual void CQikDocument_reserved2();
private:
	TInt iQikDocumentSpare1;
	};

#endif // __QIKDOCUMENT_H__
