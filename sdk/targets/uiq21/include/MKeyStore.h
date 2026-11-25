// Copyright (c) Symbian Ltd 2001

#ifndef __MKEYSTORE_H__
#define __MKEYSTORE_H__

#include <ct.h>

class CCTKeyInfo;
struct TCTKeyAttributeFilter;

/** @ingroup interfaces */
/** @{ */

/** A representation of a key store on a token. This lets the client
	query the keys */
class MKeyStore
	{
public:
	///@name Listing keys */
	///@{
	/** List all the keys in the store that match the filter.
		@param aKeys An array to which the returned keys are appended.
		@param aFilter a filter controlling which keys are returned.
		@param aStatus This will be completed with the final status code
		*/
	virtual void List(RMPointerArray<CCTKeyInfo>& aKeys, 
					  const TCTKeyAttributeFilter& aFilter, 
					  TRequestStatus& aStatus) = 0;
	/** Cancel an ongoing List operation */
	virtual void CancelList() = 0;
	///@}

	///@name Getting a key given a TCTTokenObjectHandle */
	///@{
	/** Retrieves a key given its handle.
		@param aHandle The handle of the required key
		@param aInfo The returned key info
		@param aStatus Async request notification */
	virtual void GetKeyInfo(TCTTokenObjectHandle aHandle, CCTKeyInfo*& aInfo,
							TRequestStatus& aStatus) = 0;
	/** Cancel an ongoing GetKeyInfo operation */
	virtual void CancelGetKeyInfo() = 0;
	///@}
	};
///@}
#endif // __MKEYSTORE_H__
