// QIKAPPLICATION.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__QIKAPPLICATION_H__)
#define __QIKAPPLICATION_H__

#if !defined(__EIKAPP_H__)
#include <eikapp.h>
#endif


class CQikApplication : public CEikApplication
	{
public:
	IMPORT_C ~CQikApplication();

	// from CEikApplication
	IMPORT_C void GetDefaultDocumentFileName(TFileName& aDocumentName) const;
	IMPORT_C TFileName BitmapStoreName() const;
	IMPORT_C TFileName ResourceFileName() const;

	// from CApaApplication
	IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
	IMPORT_C CApaAppInfoFileReader* OpenAppInfoFileLC() const;
	IMPORT_C void Capability(TDes8& aInfo) const;
	IMPORT_C TFileName AppFullName()const;
protected:
	IMPORT_C void PreDocConstructL();
	IMPORT_C CApaDocument* CreateDocumentL(CApaProcess* aProcess);
private:
	IMPORT_C void Reserved_1();



protected: 
	IMPORT_C CQikApplication();

private: 

	IMPORT_C virtual void CQikApplication_reserved1();
	IMPORT_C virtual void CQikApplication_reserved2();

	TInt iCQikApplicationSpare1;
	};

#endif
