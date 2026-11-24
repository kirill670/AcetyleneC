//CommsDatUtils.h
//
// Copyright (c) Symbian Software Ltd. 2004.
//

/**
 * @file
 *
 * Utility functions to retrieve comms data for specific use-cases and present it in a particular way.
 *
 * @publishedPartner
 * @prototype
 * This component is under development and is subject to change
 *
 */
#ifndef __COMMSDATUTILS_H__
#define	__COMMSDATUTILS_H__

#include <cdbcols.h>
#include  <DIAL.H>

class CCommsDatUtilImpl;
namespace CommsDatUtils

{

class CCommsDatUtils : public CBase
	{
	public :
		
		IMPORT_C static CCommsDatUtils* NewL();
		
		IMPORT_C ~CCommsDatUtils();

		//  Set `aDialString` to be the appropriate string based on the directory
		//	number, where the dial is being performed and the chargecard to use.
		//	`ResolvePhoneNumberL()` opens a comms database to perform the
		//	resolution
		IMPORT_C static void ResolvePhoneNumberL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);

		// Set `aDialString` to be the appropriate string based on the directory
		//	number, where the dial is being performed and the chargecard to use.
		IMPORT_C static void ResolvePhoneNumberFromDatabaseL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);

    	// Check access to database fields
	    IMPORT_C TInt CheckReadCapability( const TDesC& aField, const RMessagePtr2* aMessage );
	    
	    IMPORT_C TInt CheckWriteCapability( const TDesC& aField, const RMessagePtr2* aMessage );
	
	private:
		CCommsDatUtils() {};
		void ConstructL();

	private :

		CCommsDatUtilImpl* iUtilsImpl;
	};

} //end namespace CommsDat::utils

#endif //__COMMSDATUTILS_H__
