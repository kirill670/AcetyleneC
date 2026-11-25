// CRxData.h
//
// Copyright (C) 2001 Symbian Ltd

/** 
	@file CRxData.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __CRXDATA_H__
#define __CRXDATA_H__

// System includes
#include <e32base.h>
#include <http/framework/cprottransaction.h>
#include <http/mhttpdatasupplier.h>
#include <http/rhttpsession.h> // this include is needed to ensure that the <rhttp.inl> is compiled by gcc...

// Forward declarations
class MRxDataObserver;

/**
	@public
	@class			CRxData
	@since			7.0
	An abstract base class for the decoding of response data received by a
	protocol handler.
 */

//##ModelId=3B1E52AB0087
class CRxData : public CBase, public MHTTPDataSupplier
	{
public:

/** @fn				~CRxData()
	Intended Usage:	Destructor - cleans up and releases resources to the system	
	@since			7.0
*/
	IMPORT_C
	//##ModelId=3B1E52AB00ED
	virtual ~CRxData();

/** @fn				CProtTransaction& ProtTrans()
	Intended Usage:	Obtain the protocol transaction whose request part is represented
					as encoded data by this object.
	@since			7.0
	@return The protocol transaction object
*/
	IMPORT_C
	//##ModelId=3B1E52AB00EC
	CProtTransaction& ProtTrans();

public:

/** @fn				void ResetRxData()
	Intended Usage:	Resets the received data object to its initial state following
					construction.  This method must be implemented for specific sub-
					classes of received data.
	@post			The object is reset.
	@since			7.0
*/
	//##ModelId=3BA60048014B
	virtual void ResetRxData() = 0;

protected:

/** @fn				CRxData()
	Intended Usage:	Default constructor	- creates an Rx data object not associated
					with any protocol transaction.
	@since			7.0
*/
	IMPORT_C
	//##ModelId=3A914E5F008F
	CRxData();

/** @fn				CRxData(CProtTransaction& aProtTrans, MRxDataObserver& aObserver)
	Intended Usage:	Normal constructor, of a CRxData that corresponds to the supplied
					protocol transaction, and which sends status updates to the supplied
					observer interface,
	@since			7.0
	@param			aProtTransaction	(in) The transaction for which this object
											 represents the transmitted data.
	@param			aObserver			(in) The object's observer.
*/
	IMPORT_C CRxData(CProtTransaction& aProtTrans, MRxDataObserver& aObserver);

/** @fn				ConstructL()
	Intended Usage:	Second phase construction, default
	@since			7.0
*/
	IMPORT_C
	//##ModelId=3B1E52AB00BA
	void ConstructL();

protected:

	/** The protocol transaction for which this object represents the encoded received data
	*/
	//##ModelId=3B1E52AB00B2
	CProtTransaction* iProtTrans;

	/** This object's observer, to whom we forward status information
	*/
	//##ModelId=3B1E7738028B
	MRxDataObserver* iObserver;

private: // methods

/**	@fn				Reserved1()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C37DA0007
	inline virtual void Reserved1();

/**	@fn				Reserved2()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C37D903DB
	inline virtual void Reserved2();
	};


inline void CRxData::Reserved1()
	{}
inline void CRxData::Reserved2()
	{}


#endif // __CRXDATA_H__ 

