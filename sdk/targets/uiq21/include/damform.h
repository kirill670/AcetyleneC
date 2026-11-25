// DAMFORM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// This file define the interface between Form and the Data App
//
#if !defined(__DAFORM_H__)
#define __DAFORM_H__

#if !defined (__TXTRICH_H__)
#include <txtrich.h>
#endif
#if !defined (__TXTFMLYR_H__)
#include <txtfmlyr.h>
#endif
#if !defined(__TXTMRTSR_H__)
#include <txtmrtsr.h>
#endif
#include <gdi.h>
#if !defined (__DADBMS_H__)
#include "damdbms.h"
#endif

class TDaStoreResolver : public MRichTextStoreResolver
	{
public:
	virtual const CStreamStore& StreamStoreL(TInt aPos) const;
	CStreamStore* iStore;
	};

class CDaRow : public CBase
	{
public:
	enum {EInvalidControl};
	IMPORT_C ~CDaRow();
	IMPORT_C static CDaRow* NewL(CDaModel& aModel);
	IMPORT_C void GetColAsTextL(TDbColNo aUserColNo, CBufBase* aBufBase);
	IMPORT_C void SetColFromTextL(TDbColNo aUserColNo, const TDesC& aFieldBuffer);
	IMPORT_C void GetColAsRichTextL(TDbColNo aUserColNo,CRichText& aRichText);
	IMPORT_C void SetColFromRichTextL(TDbColNo aUserColNo,CRichText& aRichText);
	inline CRichText* RichText()const{return iRichText;}
	inline void SetPictureFactory(MPictureFactory* aPictureFactory) {iPictureFactory = aPictureFactory;}
protected:
	IMPORT_C CDaRow(CDaModel& aModel);
	IMPORT_C void ConstructL();
	IMPORT_C TDbColNo MapColNo(TDbColNo aUserColNo);
private:
	void SetMarkupL(CRichText& aRichText, TInt aDbColNo);
	void GetMarkupL(CRichText& aRichText, TInt aDbColNo);
private:
	CDaModel& iModel;
	CRichText* iRichText;
	CCharFormatLayer* iCharFormatLayer;
	CParaFormatLayer* iParaFormatLayer;
	TDaStoreResolver iStoreResolver;
	MPictureFactory* iPictureFactory;
	//undefined
	CDaRow& operator=(const CDaRow&);
	};

#endif
