/*
* ==============================================================================
*  Name        : GrdPrint.h
*  Part of     : Grid
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Handles printing and print preview functionality for grid
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


#ifndef CGRIDPRINTER_H
#define CGRIDPRINTER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <grdstd.h>


// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION




/* \class CGridPrinter
*    \brief Handles printing and print preview functionality for grid
*
*
*  @lib grid
*  @since ?Series90_version
*/
class CGridPrinter : public CBase, public MPageRegionPrinter
	{
	public:

        /**
        * Two-phased constructor.
        */
		IMPORT_C static CGridPrinter* NewL(CGridLay* aGridLay,CGridLabelImg* aPrintLabelImg,
			CGridCellImg* aPrintCellImg,TZoomFactor* aZoomFactor);

        /**
        * Destructor.
        */
		IMPORT_C virtual ~CGridPrinter();

    public: // New functions

		inline void SetRealPrintingDeviceMap(const MGraphicsDeviceMap* aGraphicsDeviceMap);
		IMPORT_C void SetTopLeftMargin(const TPoint& aTlMarginInTwips);
		IMPORT_C void SetPageSizeInTwipsL(const TSize& aSizeInTwips);
		IMPORT_C void PaginateL();
		inline CGridLay& GridLay();

    public: // Functions from base classes
		
		// from MPageRegionPrinter
		IMPORT_C virtual void PrintBandL(CGraphicsDevice* aDevice,TInt aPageNo,const TBandAttributes& aBandInPixels);

	private:

        /**
        * C++ default constructor.
        */
		CGridPrinter(CGridLabelImg* aPrintLabelImg,CGridCellImg* aPrintCellImg,TZoomFactor* aZoomFactor);


        /**
        * By default Symbian 2nd phase constructor is private.
        */
		void ConstructL(CGridLay* aGridLay);

    private:  // New functions

		void SetGdMapAndPushLabelImgLC();

    private:    // Data

		CGridLay* iGridLay;
		CGridImg* iGridImg;
		CGridLabelImg* iPrintLabelImg;
		CGridCellImg* iPrintCellImg;
		TZoomFactor* iZoomFactor;
		const MGraphicsDeviceMap* iGraphicsDeviceMap;
		TPoint iTlMarginInTwips;
		TRect iPrintablePage;
		TInt iScaleFactor;
	};

#include <grdprint.inl>


#endif      // CGRIDPRINTER_H   
            
// End of File


