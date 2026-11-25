// $Workfile: obexHeaderList.h $
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#if !defined (__OBEXHEADERLIST_H__)
#define __OBEXHEADERLIST_H__

#include <e32std.h> 
#include <e32base.h>    //CBase 




//forward declaration
class RMsvReadStream;
class RMsvWriteStream;
class CObexHeader;
class CObexBaseObject;
class CObexServerSendOperation;
class CObexMtmFileNameExternaliser;

class CObexHeaderList : public CBase
/**
Class CObexHeaderList
This class encapsulates and owns a list of CObexHeader objects.
Public users of this class can add CObexHeader objects 
                        
@publishedAll
@prototype
*/
	{
public:

	/*
    It provides functionalities for its friend classes to internalize and 
    externalize itself from a CMsvStore stream, and add all its contained 
    CObexHeader objects to a CObexBaseObject, as well as two general list
    functions to return the number of objects it contained and a contained
    object at a specified index into the list.
    */  
	friend class CObexServerSendOperation;		// requires the use of 'AddHeadersToBaseObjectL'
	friend class CObexMtmFileNameExternaliser;	// uses all functionality except 'AddHeadersToBaseObjectL'

	/**
	 * Factory function to return a CObexHeaderList*
	 */
	IMPORT_C static CObexHeaderList* NewL();
	
	
	/**
	 * Factory function to return a CObexHeaderList* and leave it on the 
	 * CleanupStack
	 */
	IMPORT_C static CObexHeaderList* NewLC();


	/**
	 * Destructor which frees all allocated memory with the list
	 */
    IMPORT_C ~CObexHeaderList();
    
    /**
	 * Add a CObexHeader object to the list. The CObexHeader object added 
	 * should have its attribute, header ID and header value set before
	 * it is added to the list. CObexHeaderlist will not change these
	 * values of its contained CObexHeader objects
	 * @param  aHeader is a pointer to a constant CObexHeader object
	 *  
	 * @return KErrNone, if the operation is successful, otherwise
	 *         one of the system wide error codes  
	 */
	IMPORT_C TInt AddHeader(const CObexHeader*  aHeader);
    
protected:
    /**
	 * Externalise the contents of the CObexHeaderList class to a 
	 * stream in CMsvStore
	 *
	 * @param  aWriteStream is a reference to a RMsvWriteStream
	 *  
	 * @leave it may leave with one of the system wide error code 
	 */
	IMPORT_C void ExternalizeL(RMsvWriteStream& aWriteStream) const;

	
     /**
	 * Internalise the contents of the CObexHeaderList class from a 
	 * stream in CMsvStore
	 *
	 * @param  aReadStream is a reference to a RMsvReadStream
	 *  
	 * @leave it may leave with one of the system wide error code 
	 */
	IMPORT_C void InternalizeL(RMsvReadStream& aReadStream);


    /**
	 * Add all the CObexHeader objects contained in a list to a 
	 * CObexBaseObject
	 *
	 *
	 * @param aObexBaseObj is a reference to a CObexBaseObject
	 *  
	 * @leave it may leave with one of the system wide error code 
	 * 
	 */
    IMPORT_C void AddHeadersToBaseObjectL(CObexBaseObject& aObexBaseObj);

	
	//General list processing functions

    /**
	 * Return the number of  CObexHeader object pointers contained in the list
	 *
	 * 
	 * @return return the number of CObexHeader object pointers in the list
	 */
	IMPORT_C TInt Count() const;

	/**
	 * Get a non constant reference to the CObexHeader object pointer at 
	 * position aPos into the list.
	 *
	 *
	 * @param aPos is a list index specifying the CObexHeader object pointer to 
	 *        be returned
	 *  
	 * @leave leave if aPos is out of range(KErrArgument) or the list is empty
	 *        (KErrNotFound)
	 * @return return a non constant reference to the CObexHeader object 
	 *         pointer
	 */
	IMPORT_C CObexHeader*& ObexHeaderL(TInt aPos); 

private:
	/**
	 * Leaving constructor function used in 2 phase construction in NewLC()
	 */
	void ConstructL();

    /**
	 *  Constructor function used in 2 phase construction in NewLC()
	 */
	CObexHeaderList();

private:
    ///<pointer to the CObexHeader object pointer array
	RPointerArray<CObexHeader>*	iObexHeaders;


	};
#endif	//!defined (__OBEXHEADERLIST_H__)
