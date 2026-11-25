// QikSendAs.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.

#ifndef __QIKSENDAS_H__
#define __QIKSENDAS_H__

#include <eikdialg.h> //CEikDialog
#include <sendas.h> // MSendAsObserver

class CQikSendAsLogic;

const TUid KUidSmsMtm				= {0x1000102C};
const TUid KUidMmsMtm				= {0x101f4A60};
const TUid KUidFaxMtm				= {0x1000102B};
const TUid KUidEmailMtm				= {0x10001028};
const TUid KUidIrMtm				= {0x100053A4};
const TUid KUidPcMailMtm			= {0x1000412A};
const TUid KUidBtMtm				= {0x10009ED5};

const TUid KUidSmsBIOVCalMsg		= {0x10005533};   
const TUid KUidSmsBIOVCardMsg		= {0x10005534};

/**
 * This class displays a dialog where you can choose by which MTM you want
 * to send your entry.
 */
class CQikSendAsDialog : public CEikDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(CRichText* aBodyText,const TPath& aAttachPath,const TFileName& aAttachName,
		const TDesC& aSubject, TUid aCapabilityId=TUid::Null(), TUid aBioMessageType=TUid::Null(),
		TUid aDefaultMtm=TUid::Null(), TBool aAlwaysSendBody=EFalse);
	~CQikSendAsDialog();

private:
	CQikSendAsDialog(TUid aCapabilityId,TUid aDefaultMtm);
	void ConstructL(CRichText* aBodyText,const TPath& aAttachPath,const TFileName& aAttachName, 
		const TDesC& aSubject, TUid aBioMessageType, TBool aAlwaysSendBody);
	void SortArrayL();
	
private:	
	//from CEikDialog
	TBool OkToExitL(TInt aButtonId);
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
	void SaveMtmToFileL(TUid aMtmUid);
	TUid ReadMtmFromFileL();

private:
	CQikSendAsLogic* iSendAsLogic;
	CArrayFixFlat<TUid>* iMtmUidArray;
	CDesCArrayFlat* iMtmArray;
	TUid iAttachmentFlag;
	TUid iDefaultMtm;
	TInt iResourceFileOffset;
};

/**
 * This class sorts mtm uid and desc arrays according to a predefined order.
 * It also puts the default mtm (if any) first.
 */
class TMtmSorter : public TSwap, public TKey
	{
public:
	TMtmSorter(CArrayFixFlat<TUid>* aMtmUidArray, CDesCArrayFlat* aMtmArray, TUid aDefaultMtm) 
	: iMtmUidArray(aMtmUidArray), iMtmArray(aMtmArray), iDefaultMtm(aDefaultMtm) {};

	// Method called by User::QuickSort()
	void Swap(TInt aLeft, TInt aRight) const;
	TInt Compare(TInt aLeft, TInt aRight) const;

private:
	TUint RankMtm(const TUid aUid) const;

	CArrayFixFlat<TUid>* iMtmUidArray;
	CDesCArrayFlat* iMtmArray;
	TUid iDefaultMtm;
	};

/**
 * This class handles with SendAs functionality.
 * It sends text and/or attachment from chosen application by DNL, IR or Bluetooth.
 */
class CQikSendAsLogic : public CBase, public MSendAsObserver
	{
public:
	IMPORT_C static CQikSendAsLogic* NewL(CRichText* aBodyText, const TPath& aAttachPath, const TFileName& aAttachName, 
		const TDesC& aSubject, TUid aBioMessageType=TUid::Null(), TBool aAlwaysSendBody=EFalse);
	IMPORT_C ~CQikSendAsLogic();
	IMPORT_C CSendAs& SendAs() const;
	IMPORT_C void SendMtmL();
	
private:
	CQikSendAsLogic(CRichText* aBodyText, const TPath& aAttachPath, const TFileName& aAttachName, 
		TUid aBioMessageType, TBool aCompleteEmail);
	void ConstructL(const TDesC& aSubject);
	void CreateAttachmentL();
	void CreateBodyL();

private:
	//From MSendAsObserver
	TBool CapabilityOK(TUid aCapability, TInt aResponse);
	TInt RenderImage(TUid aPrinterUid, const TDesC& aFileName);
	TInt RenderImage(TUid aPrinterUid, const TDesC& aFileName, TRequestStatus& aRequestStatus);

private:
	CSendAs* iSendAs;
	CRichText* iBodyText;
	TPath iAttachPath;
	TFileName iAttachName;
	HBufC* iSubject;
	TUid iBioMessageType;
	TBool iAlwaysSendBody;
	RFs iFs; 
	};

#endif // __QIKSENDAS_H__