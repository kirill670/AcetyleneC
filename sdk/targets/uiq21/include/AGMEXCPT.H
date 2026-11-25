// AGMEXCPT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMEXCPT_H__
#define __AGMEXCPT_H__

#include <e32base.h>
#include "agmids.h"
#include "agmdate.h"


// -------------------------- Local classes -----------------------------------
class TAgnException;
class CAgnExceptionList;


// ---------------------------- Referenced classes ------------------------------
class TStreamCArrayFix;



/**
 * Stores the date of an exception to a repeating entry.
 *
 * Agenda entries own a repeat definition (<code>CAgnRptDef*</code>)
 * which contains the repeat details for the entry, including exceptions.
 * This pointer is NULL if the entry is not repeating. To set it, use
 * <code>CAgnEntry::SetRptDefL()</code>. The repeat definition can be
 * retrieved using <code>CAgnBasicEntry::RptDef()</code>. Exceptions can
 * be added, removed, pruned and searched for using functions defined in
 * class <code>CAgnBasicEntry</code>, or the <code>CAgnRptDef</code>
 * class can be used directly.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class TAgnException
	{
public:
	IMPORT_C TAgnException();
	IMPORT_C TAgnException(TAgnDate aDate);
	inline void SetDate(TAgnDate aDate);
	inline TAgnDate Date() const;

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	friend class CAgnExceptionList;			// CAgnException requires access to the offset
											// of iDate when constructing key
private:									 
	TAgnDate 	iDate;
	};


class CAgnExceptionList : public CArrayFixFlat<TAgnException>
//
// A list of exception entrys
//
	{
public:
	enum {EGranularity=4};
	IMPORT_C CAgnExceptionList();
	TBool Compare(const CAgnExceptionList* aExceptions) const;		
	inline TInt InsertL(const TAgnException& aException);
	inline TInt Find(const TAgnException& aException,TInt& aPos);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	TKeyArrayFix iDateKey; // When searching etc. for exceptions in an exception list its done via the date field
	};


#include "agmexcpt.inl"

#endif
