// OBEXHEADERLIST.H
//
// Copyright (c) 2001-2004 Symbian Sofwtare Ltd.  All rights reserved.
//

#ifndef __OBEXHEADERLIST_H__
#define __OBEXHEADERLIST_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif     // __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif     // __SUPPORT_MESSAGING_API_V1__

#include <e32std.h> 
#include <e32base.h>    //CBase 

//forward declaration
class RMsvReadStream;
class RMsvWriteStream;
class CObexHeader;
class CObexBaseObject;
class CObexServerSendOperation;

#ifndef __HIDE_MESSAGING_API_V1__
class CObexMtmFileNameExternaliser;
#endif // __HIDE_MESSAGING_API_V1__

#ifdef __MESSAGING_API_V2__
class CMsvAttachment;

const TUid KUidObexHeaders = {0x10204282};
#endif // __MESSAGING_API_V2__

class CObexHeaderList : public CBase
/**
Encapsulates and owns a list of CObexHeader objects.
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
#ifndef __HIDE_MESSAGING_API_V1__
	friend class CObexMtmFileNameExternaliser;	// uses all functionality except 'AddHeadersToBaseObjectL'
#endif // __HIDE_MESSAGING_API_V1__

	/**
	 * Factory function to return a new CObexHeaderList.
	 @return New CObexHeaderList object 
	 */
	IMPORT_C static CObexHeaderList* NewL();
	
	
	/**
	 * Factory function to return a new CObexHeaderList and leave it on the 
	 * cleanup stack.
	 @return New CObexHeaderList object 
	 */
	IMPORT_C static CObexHeaderList* NewLC();


	/**
	 * Destructor which frees all allocated memory with the list.
	 */
    IMPORT_C ~CObexHeaderList();
    
    /**
	 * Add a CObexHeader object to the list. The CObexHeader object added 
	 * should have its attribute, header ID and header value set before
	 * it is added to the list. CObexHeaderlist will not change these
	 * values of its contained CObexHeader objects
	 * @param  aHeader Pointer to a constant CObexHeader object
	 *  
	 * @return KErrNone, if the operation is successful, otherwise
	 *         one of the system wide error codes  
	 */
	IMPORT_C TInt AddHeader(const CObexHeader*  aHeader);
	
#ifdef __MESSAGING_API_V2__
	IMPORT_C void ExportToAttachmentL(CMsvAttachment& aAttachment) const;
	
	IMPORT_C void ImportFromAttachmentL(CMsvAttachment& aAttachment);

	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
	
	IMPORT_C void InternalizeL(RReadStream& aReadStream);
#endif // __MESSAGING_API_V2__

protected:

#ifndef __MESSAGING_API_V2__
    /**
	 * Externalise the contents of the CObexHeaderList class to a 
	 * stream in CMsvStore
	 *
	 * @param  aWriteStream Reference to a RMsvWriteStream
	 *  
	 * @leave Error System wide error code 
	 */

	IMPORT_C void ExternalizeL(RMsvWriteStream& aWriteStream) const;
	
     /**
	 * Internalise the contents of the CObexHeaderList class from a 
	 * stream in CMsvStore
	 *
	 * @param  aReadStream Reference to a RMsvReadStream
	 *  
	 * @leave Error System wide error code 
	 */
	IMPORT_C void InternalizeL(RMsvReadStream& aReadStream);
#endif // __MESSAGING_API_V2__


    /**
	 * Add all the CObexHeader objects contained in a list to a 
	 * CObexBaseObject.
	 *
	 *
	 * @param aObexBaseObj CObexBaseObject to add the objects to
	 *  
	 * @leave Error System wide error code 
	 * 
	 */
    IMPORT_C void AddHeadersToBaseObjectL(CObexBaseObject& aObexBaseObj);

	
	//General list processing functions

    /**
	 * Return the number of CObexHeader object pointers contained in the list.
	 *
	 * 
	 * @return The number of CObexHeader object pointers in the list
	 */
	IMPORT_C TInt Count() const;

	/**
	 * Get a non constant reference to the CObexHeader object pointer at 
	 * position aPos into the list.
	 *
	 *
	 * @param aPos A list index specifying the CObexHeader object pointer to 
	 *        be returned
	 *  
	 * @leave KErrArgument aPos is out of range
	 * @leave KErrNotFound The list is empty
	 *        
	 * @return A non constant reference to the CObexHeader object 
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
	
#endif	// __OBEXHEADERLIST_H__
