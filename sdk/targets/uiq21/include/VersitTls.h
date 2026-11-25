// VERSITTLS.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __VERSITTLS_H__
#define __VERSITTLS_H__

// System includes
#include <e32base.h>
#include <charconv.h>

#include "vutil.h"

class CVersitTimer;

/**
 * An object stored in TLS which allows a single instance of
 * a unicode converter to be shared throughout import and export.
 *
 * This is a major performance improvement. 
 */
class CVersitTlsData : public CBase
	{
	friend class CVersitTimer;

public:
	IMPORT_C static CVersitTlsData& VersitTlsDataL();
	IMPORT_C static void CloseVersitTlsData();
	IMPORT_C void VersitTlsDataClose();

public:
	inline CVersitUnicodeUtils& UnicodeUtils() { return *iUnicodeUtils; }

private:
	static CVersitTlsData* NewL();
	void ConstructL();
	~CVersitTlsData();

private:
	TInt iRefCount;
	CVersitUnicodeUtils* iUnicodeUtils;
	};

#endif