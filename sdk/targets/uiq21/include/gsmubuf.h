// GSMUBUF.H
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//
/**
 *
 * @file gsmubuf.h    This file contains the header file of the CSmsBuffers.
 *
 */

#ifndef __GSMUBUF_H__
#define __GSMUBUF_H__

#include <e32std.h>
#include <s32strm.h>

class CEditableText;
class RReadStream;
class RWriteStream;

class CSmsBufferBase : public CBase
/**
 * The base class for all SMS buffers  
 */
	{
public:
	enum
		{
		EMaxBufLength=0x100
		};
public:
	virtual TInt Length() const=0;
	virtual void Extract(TDes& aBuf,TInt aPos,TInt aLength) const=0;
	virtual void InsertL(TInt aPos,const TDesC& aBuf)=0;
	virtual void DeleteL(TInt aPos,TInt aLength)=0;
	virtual void Reset()=0;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	};

class CSmsBuffer : public CSmsBufferBase
/**
 * This is the simplest implementation of CSmsBufferBase.  It stores the buffer in an array of TTexts
 */
	{
public:
	IMPORT_C static CSmsBuffer* NewL();
	IMPORT_C ~CSmsBuffer();
	IMPORT_C TInt Length() const;
	IMPORT_C void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;
	IMPORT_C void InsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C void DeleteL(TInt aPos,TInt aLength);
	IMPORT_C void Reset();
private:
	CSmsBuffer();
private:

	CArrayFix<TText>* iBuffer;
	};

class CSmsEditorBuffer : public CSmsBufferBase
/**
 * This buffer is a thin wrapper over CEditableText
 * This class is designed to be used by the Message Server, which stores SMS text as CRichText,
 * which is derived from CEditableText.	
 */
	{
public:
	IMPORT_C static CSmsEditorBuffer* NewL(CEditableText& aText);
	IMPORT_C ~CSmsEditorBuffer();
	IMPORT_C TInt Length() const;
	IMPORT_C void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;
	IMPORT_C void InsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C void DeleteL(TInt aPos,TInt aLength);
	IMPORT_C void Reset();
private:
	CSmsEditorBuffer(CEditableText& aText);
private:
	CEditableText& iText;
	};


#endif // !defined __GSMUBUF_H__
