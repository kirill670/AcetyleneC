/*
* ==============================================================================
*  Name        : Grdcells.h
*  Part of     : Grid
*  Interface   : ?Interface_category, ?Interface_name
*  Description : class to handle cell region
*  Version     : ?Version
*
*  Copyright (c) 2002 Nokia Corporation.
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


#ifndef CGRIDCELLREGION_H
#define CGRIDCELLREGION_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <bacell.h>



// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION


/* \class CGridCellRegion
*    \brief Defines a selected region.
*    
*    
*    A selected region consists of one or more cell ranges, represented by 
*    TRangeRef objects, that exist within a defined boundary. The boundary 
*    is itself defined as a cell range.
*    
*    Cell ranges map cell selections, and the class provides the behaviour 
*    to manage these selections.
*
*  @lib Grid
*  @since ?Series90_version
*/
class CGridCellRegion : public CBase
	{
    public: // New functions
		IMPORT_C static CGridCellRegion* NewL(const TRangeRef& aBounds);
		IMPORT_C virtual ~CGridCellRegion();
		IMPORT_C void AddColL(TInt aCol);
		IMPORT_C void AddRowL(TInt aRow);
		IMPORT_C void AddCellRangeL(const TRangeRef& aCellRange);
		IMPORT_C void SetLastCellRange(const TRangeRef& aCellRange);
		IMPORT_C void ResizeBounds(const TCellRef& aNewToBounds);
		IMPORT_C void Reset();
		IMPORT_C TInt Count() const;
		IMPORT_C TBool IsCellSelected(const TCellRef &aCell) const;
		IMPORT_C TBool IsCellSelected(const TCellRef &aCell,TInt aIndex) const;
		IMPORT_C TBool IsCellSelectedLastIndex(const TCellRef &aCell) const;
		IMPORT_C TBool IsRowSelected(TInt aRow) const;
		IMPORT_C TBool IsRowSelected(TInt aRow,TInt aIndex) const;
		IMPORT_C TBool IsRowSelectedLastIndex(TInt aRow) const;
		IMPORT_C TBool IsAnyRowSelected() const;
		IMPORT_C TBool IsColSelected(TInt aCol) const;
		IMPORT_C TBool IsColSelected(TInt aCol,TInt aIndex) const;
		IMPORT_C TBool IsColSelectedLastIndex(TInt aCol) const;
		IMPORT_C TBool IsAnyColSelected() const;
		IMPORT_C TBool IsRangeSelected(const TRangeRef &aRange) const;
		IMPORT_C TBool IsRangeSelected(const TRangeRef &aRange,TInt aIndex) const;
		IMPORT_C TBool IsRangeSelectedLastIndex(const TRangeRef &aRange) const;
		IMPORT_C TRangeRef operator[](TInt aIndex) const;
		IMPORT_C const CArrayFix<TRangeRef>* RangeList() const;

	private:

        /**
        * C++ default constructor.
        */
		CGridCellRegion(const TRangeRef& aBounds);

        /**
        * By default Symbian 2nd phase constructor is private.
        */
		void ConstructL();

    private:    // Data
		TRangeRef iBounds;
		CArrayFix<TRangeRef>* iRangeList;
	};


#endif      // CGRIDCELLREGION_H   
            
// End of File
