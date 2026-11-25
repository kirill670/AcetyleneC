/*
* ==============================================================================
*  Name        : cknsort.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : TCknSortParameters - Parameters for a potential sort operation.
*  				 CCknSortDialog - A dialog allowing the user to select the parameters for a potential sort operation.
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


#ifndef CKNSORT_H
#define CKNSORT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <eikdialg.h>
#include <eikchlst.h>
#include <eiktxlbm.h>
#include <ckndlg.rsg>
#include <badesca.h>

// CONSTANTS

/**
 * This enum corresponds to the field index returned from a sort dialog
 * that was invoked without providing custom field names.
 */
enum TCknDefaultSortFields { ECknSortByDate, ECknSortByName, ECknSortBySize };

enum TCknSortOrder { ECknSortAscending, ECknSortDescending };

/**
*  Parameters for a potential sort operation.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class TCknSortParameters
	{
	public:
		/**
		* C++ constructor.
		* @param aFieldIndex The index of the field to sort on.
		* @param aOrder Whether the sort should be in ascending or descending order
		*/
	TCknSortParameters(TInt aFieldIndex = 0, TCknSortOrder aOrder = ECknSortDescending) 
		: iFieldIndex(aFieldIndex), iOrder(aOrder){}

	/**
	 * The index of the field to sort on. 
	 */
		TInt iFieldIndex;
	/**
	 * Whether the sort should be in ascending or descending order
	 */
		TCknSortOrder iOrder;
	};

/**
*  A dialog allowing the user to select the parameters for a potential sort operation
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class CCknSortDialog : public CEikDialog
	{
    public:
		/**
		 * Run the sort dialog using the default list of fields
		 * which are enumerated in TCknDefaultSortFields
		 *
		 * @param aParameters the default values of the parameters on the dialog
		 * The field index must be a valid default field
		 * @return whether the dialog succeeded or was dismissed
		 * If the dialog succeeded, aParameters will contain the parameters set by the user
		 * The field index in aParameters is an index of one of the default fields
 		 * <BR><B>Type of return value:</B> TBool
		 */
		IMPORT_C static TBool RunLD(TCknSortParameters& aParameters);
		/**
		 * Run the sort dialog using a caller-specified list of fields
		 *
		 * @param aParameters the default values of the parameters on the dialog
		 * The field index must be a valid index into aFieldNames
		 * @param aFieldNames the names of the fields the user can choose to sort by
		 * @return whether the dialog succeeded or was dismissed
		 * If the dialog succeeded, aParameters will contain the parameters set by the user
		 * The field index in aParameters is an index of one of the aFieldName fields
 		 * <BR><B>Type of return value:</B> TBool
		 */
		IMPORT_C static TBool RunLD(TCknSortParameters& aParameters, const MDesCArray& aFieldNames);
        
    private:
    	CCknSortDialog(TCknSortParameters& aParameters, const MDesCArray* aFieldNames = 0);
		~CCknSortDialog();

		// from CEikDialog
		void PreLayoutDynInitL();
		TBool OkToExitL(TInt aButtonId);

        // not implemented
    	CCknSortDialog(const CCknSortDialog&);
    	void operator=(const CCknSortDialog&);

	private:
		TCknSortParameters& iParameters;
		const MDesC16Array* iFieldNames;
	};

#endif	// CKNSORT_H

// End of File
