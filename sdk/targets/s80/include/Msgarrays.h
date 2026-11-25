/*
* ==============================================================================
*  Name        : msgarrays.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Utilities for handling message arrays
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef MSGARRAYS_H
#define MSGARRAYS_H

// INCLUDES
#include <e32def.h>
#include <MSVREG.H>
#include <MTUDCBAS.H>

class TMsgFunctionInfo;

// Function info array
//
typedef CArrayFixFlat<TMsgFunctionInfo> CMsgFuncArray;

/**
*  Message function info
*
*  This class is a store for message functions.
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class TMsgFunctionInfo
{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C TMsgFunctionInfo(const TDesC& aCaption, TInt aKeyCode, TInt aKeyModifiers, TInt aFuncId, TInt aFlags, TUid aMtmUid);

	public:
		TBuf<CBaseMtmUiData::TMtmUiFunction::ECaptionMaxLen> iCaption;
		TInt iKeyCode;
		TInt iKeyModifiers;
		TInt iFuncId;
		TInt iFlags;
		TUid iMtmUid;
};


/**
*  Message type info
*  Wrapper class for UIDs and their names.
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class TUidNameInfo
{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C TUidNameInfo(TUid aUid, const TDesC& aName);
	public:
		TUid iUid;
		TBuf<KHumanReadableNameLength> iName;
};

/**
*  Message type key
*  Wrapper class which allows UID names to be compared 
*  alphabetically, which is necessary in ordered arrays.
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class TUidNameKey : public TKeyArrayFix
{ 
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C TUidNameKey(TKeyCmpText aType);
	private: // from TKey
		TInt Compare(TInt aLeft,TInt aRight) const;
}; 


/**
*  Message type array	
*  Array class, for storing a number of UIds and their names.
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class CUidNameArray : public CArrayFixFlat<TUidNameInfo>, public MDesCArray
{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CUidNameArray(TInt aGranularity); 

		/**
		* Destructor.
		*/
		IMPORT_C ~CUidNameArray();

		/**
		* Sort the name array
		* @since ?Series90_version
		* @param aTextComparisonType Type of text comparison to use
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void Sort(TKeyCmpText aTextComparisonType);
	private:
		IMPORT_C virtual TInt MdcaCount() const;
		IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
};

/**
*  CGroupedEntryArray
*  'Sort' a selection of entry IDs into a set of selections determined by TGroupBy.
*  If grouping by EByMtm, one element will be created for each MTM type in the selection.
*  If grouping by EByService, one element will be created for each service in the selection.
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class CGroupedEntryArray : public CBase
	{
	public:
	enum TGroupBy
		{
		EByMtm,
		EByService
		};
/**
*  Element class
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
	class CElement : public CBase
		{
	public:
		inline CElement() {}
	public:
		TUid iMtm;
		TMsvId iService;             // Only valid for EByService sorting.
		CMsvEntrySelection iEntries;
		};
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CGroupedEntryArray* NewL(CMsvSession&, TGroupBy, const CMsvEntrySelection&);

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CGroupedEntryArray();

		/**
		* Reset all elements
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ResetL(TGroupBy, const CMsvEntrySelection&);

		/**
		* Group elements by
		* @since ?Series90_version
		* @return The groupby type
		* <BR><B>Type of return value:</B> TGroupBy
		*/
		inline TGroupBy GroupBy() const;

		/**
		* Count the number of elements
		* @since ?Series90_version
		* @return The number of elements
		* <BR><B>Type of return value:</B> TInt
		*/
		inline TInt Count() const;

		/**
		* [] Operator
		* @since ?Series90_version
		* @return The element at the specified index
		* <BR><B>Type of return value:</B> CElement&
		*/
		inline CElement& operator[](TInt);

		/**
		* Const version of [] operator
		* @since ?Series90_version
		* @return The element at the specified index
		* <BR><B>Type of return value:</B> const CElement&
		*/
		inline const CElement& operator[](TInt) const;
	private:
		CGroupedEntryArray(CMsvSession&);
	private:
		CMsvSession& iSession;
		TGroupBy iGroupBy;
		RPointerArray<CElement> iArray;
	};


inline CGroupedEntryArray::TGroupBy CGroupedEntryArray::GroupBy() const { return iGroupBy; }
inline TInt CGroupedEntryArray::Count() const { return iArray.Count(); }
inline CGroupedEntryArray::CElement& CGroupedEntryArray::operator[](TInt aIndex) { return *iArray[aIndex]; }
inline const CGroupedEntryArray::CElement& CGroupedEntryArray::operator[](TInt aIndex) const { return *iArray[aIndex]; }



#endif	// MSGARRAYS_H

// End of File
