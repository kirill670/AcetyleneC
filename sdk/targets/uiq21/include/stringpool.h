// 
// Copyright (C) 2001 Symbian Ltd

#ifndef __STRINGPOOL_H__
#define __STRINGPOOL_H__ 

#include <e32base.h>
#include <StringTableSupport.h>
#include "StringPoolErr.h"

class RStringF;
class RString;
class RStringToken;
class RStringTokenF;
class MStringPoolCloseCallBack;

/** Interface for the callback function. Derive from this class to be notified of the string pool closure */
class MStringPoolCloseCallBack
	{
	///Implement this function to perform some operation when the string pool is being closed
	public:
		virtual void StringPoolClosing()=0;
	};

/** The string pool handle object.  A string pool can have several
	distinct handles associated with it, each associated with a
	different pre-loaded table. The difference between them is that
	creating a string from an enum will interpret the enum as an
	offset into the relevant pre-loaded table */
class RStringPool
	{
 public:
	inline RStringPool();

	IMPORT_C void OpenL();

	IMPORT_C void OpenL(const TStringTable& aTable);

	IMPORT_C void OpenL(const TStringTable& aTable,MStringPoolCloseCallBack& aCallBack);

	IMPORT_C void Close();

	IMPORT_C RStringF OpenFStringL(const TDesC8& aString) const;

	IMPORT_C RString OpenStringL(const TDesC8& aString) const;

	IMPORT_C RString String(RStringToken aString) const;

	IMPORT_C RString String(TInt aIndex,const TStringTable& aTable) const;	

	IMPORT_C RStringF StringF(RStringTokenF aString) const;

	IMPORT_C RStringF StringF(TInt aIndex,const TStringTable& aTable) const;	

 private:
	friend class RStringBase;
	friend class RString;
	friend class RStringF;
	friend class CStringPoolImplementation;

	CStringPoolImplementation* iImplementation;
	};

/** A compact (4 byte) representation of a string in the string pool. This
	class must be turned into a RStringBase (or one of its derived classes) before you can do anything
	useful with it. It is only intended to be used when storing strings 
	in situations where space matters; normaly use RStringBase.
	@see RStringBase
*/
class RStringTokenBase
	{
 public:
	inline RStringTokenBase();

	inline RStringTokenBase operator=(RStringBase aVal);

	inline TBool IsNull() const;

 protected:
	friend class RStringPool;
	friend class RStringBase;
	friend class RStringTokenEither;
	friend class CStringPoolImplementation;

	TUint32 iVal;
	};

/** A compact (4 byte) representation of a case-sensitive string in the string pool. This
	class must be turned into a RString before you can do anything
	useful with it. It is only intended to be used when storing strings 
	in situations where space matters; normaly use RString.
	@see RString
*/
class RStringToken : public RStringTokenBase
	{
 public:
	inline TBool operator==(RStringToken aVal) const;

	inline TBool operator!=(RStringToken aVal) const;

	inline RStringToken operator=(RString aVal);

	friend class RStringPool;
	friend class RString;
	friend class CStringPoolImplementation;
	};

/** A compact (4 byte) representation of a case-insensitive string in the string pool. This
	class must be turned into a RStringF before you can do anything
	useful with it. It is only intended to be used when storing strings 
	in situations where space matters; normaly use RStringF.
	@see RStringF
*/
class RStringTokenF  : public RStringTokenBase
	{
 public:
	inline TBool operator==(RStringTokenF aVal) const;

	inline TBool operator!=(RStringTokenF aVal) const;

	inline RStringTokenF operator=(RStringF aVal);

	friend class RStringPool;
	friend class RStringF;
	friend class CStringPoolImplementation;
	};

/** A String that is actualy stored in a string pool.
	This is the base class; there are subclasses for folded and non-folded
	versions. Use this class when you want to receive a string but have
	no intention of comparing it with anything.
	@see RStringPool
*/
class RStringBase
	{
 public:
	inline RStringBase();

	IMPORT_C void Close();

	IMPORT_C RStringBase Copy();

	IMPORT_C const TDesC8& DesC() const;

	inline operator RStringTokenBase() const;

	IMPORT_C TInt Index(const TStringTable& aTable) const;

	IMPORT_C const TStringTable*  OriginalTableRef() const;

	inline RStringPool Pool() const;

 protected:
	friend class RStringPool;
	friend class RStringTokenBase;

	RStringPool iPool;
	TUint32 iVal;
	};

/** A case-sensitiveString that is actualy stored in a string pool.
	To initialise values of this class, you need to use the operator() 
	functions on the RStringPool.
	This class performs comparisons in a non-folded (case-sensitive) manner.
	@see RStringPool
*/
class RString : public RStringBase
	{
 public:
	inline RString Copy();

	inline operator RStringToken() const;

	inline TBool operator==(const RString& aVal) const;

	inline TBool operator!=(const RString& aVal) const;

	friend class RStringPool;
	friend class RStringToken;
	};

/** A case-insensitive String that is actualy stored in a string pool.
	To initialise values of this class, you need to use the operator() 
	functions on the RStringPool.
	Comparisons with this class use folded (case-insensitive) comparisons.
	@see RStringPool
*/
class RStringF : public RStringBase
	{
 public:
	inline RStringF Copy();

	inline operator RStringTokenF() const;

	inline TBool operator==(const RStringF& aVal) const;

	inline TBool operator!=(const RStringF& aVal) const;

	friend class RStringPool;
	friend class RStringTokenF;
	};


/** A pointer to a string table
 */
struct TStringTable
	{
	/// The number of elements in the table
	TUint iCount;
	/// A pointer to an array of pointers to the strings
	const void* const * iTable;	

	/// ETrue if the table should be considered case-sensitive.
	TBool iCaseSensitive;
	};

// Include the inline functions
#include <stringpool.inl>

#endif // __STRINGPOOL_H__


