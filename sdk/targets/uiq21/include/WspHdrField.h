// WspHdrField.h
//
// Copyright (C) 2001 Symbian Ltd.

#ifndef	__WSPHDRFIELD_H__
#define	__WSPHDRFIELD_H__

#include <e32std.h>
#include <WSPDecoder.h>
#include <StringPool.h>

/** 
* @file WspHdrField.h
* This file contains the following classes:
* CWspHeaderField - Holds a header field holding the pair: <CWspFieldName,CWspFieldValue>
* CWspHeaders - Holds the a buffer which contains WSP Headers, provides parsing utils
*	
*/

/** 
*	Created with a buffer containing a chunk of WSP Headers
*	Fields will be segmented interanally, and can be searched and
*   collected by the user.
*/ 
class CWspHeaders : public CBase
{
public:

	/**
	* @param aFinalHeader the final encoded header value, usually the content type
	* @param aHdrBuf the buffer containing the chunk of header
	* @return CWspHeader
	*/
	IMPORT_C static CWspHeaders* NewL(TInt aFinalHeader, TPtrC8 aHdrBuf);

	/**
	* @param aHdrBuf the buffer containing the chunk of header
	* @return CWspHeader
	*/
	IMPORT_C static CWspHeaders* NewL(TPtrC8 aHdrBuf);

	/**
	* @param aStringTable use a different string table than default (MMSFieldName::Table)
	* @param aHdrBuf the buffer containing the chunk of header
	* @return CWspHeader
	*/
	IMPORT_C static CWspHeaders* NewL(const TStringTable& aStringTable, TPtrC8 aHdrBuf);

	/**
	* Destructor
	*/
	IMPORT_C virtual ~CWspHeaders();

	/**
	* @return Number of headers
	*/
	IMPORT_C  TInt Count() const;

	/**
	* @param aIndex: In - which header
	* @param aFld: Out - returns the header field indexed
	*/
	IMPORT_C  const TWspField& GetFieldL(TInt aIndex);

	/**
	* @param aFieldName: In - search by name
	* @param aFld: Out - returns the header field indexed
	*/
	IMPORT_C  TInt GetFieldByNameL(RStringF aFieldName, TWspField& aFld);
	
	/**
	* 
	* @return current offset of position beyond the last MMS field, Content-Type.
	*/
	IMPORT_C  TInt EndOfMmsHeader() const;
	
private:
	/**
	* Private constructor
	*/
	CWspHeaders(const TStringTable& aStringTable);
	
	/**
	* Factory constructor
	*/
	void ConstructL(TPtrC8 aHdrBuf);

	void EnumerateL();

	RStringPool	iPool;
	const TStringTable& iTable;
	HBufC8*	iHdrBuffer;
	RArray<TWspField> iHdrFields;
	TInt iEndOfHeaderOffset; ///< The offset position marking the end of the MMS headers.
							 ///< This should be just beyond the content-Type field.
	TInt iFinalHeader;		///< The expected final header. Header parsing will stop after this header is found.
};



#endif //WSPHDRFIELD
