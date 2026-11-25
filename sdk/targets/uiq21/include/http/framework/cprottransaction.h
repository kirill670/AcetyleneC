// CProtTransaction.h 
//
// Copyright (C) 2001 Symbian Ltd

/** 
	@file CProtTransaction.h 
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __CPROTTRANSACTION_H__
#define __CPROTTRANSACTION_H__

// System includes
#include <e32base.h>
#include <http/rhttptransaction.h>

// Forward declarations
class CTxData;
class CRxData;
class MRxDataObserver;

/** 
	@public
	@class			CProtTransaction
	@since			7.0
	A representation of a transaction used by protocol handlers.
	This class is lower-level than the RHTTPTransaction class,
	since it owns objects that represent the request and response data as
	transmitted and received over a transport medium.
 */

//##ModelId=3B1E52B30382
class CProtTransaction : public CBase
	{
public:	// Enums

/** The TTransactionState type defines the states of a transaction.
*/
	enum TTransactionState
		{
		/** Specifies that the transaction is pending servicing.
		*/
		EPending		= 0,
		/** Specifies that the transaction is being serviced - active.
		*/
		EActive,
		/** Specifies that the transaction has been cancelled.
		*/
		ECancelled,
		/** Specifies that the transaction has completed.
		*/
		ECompleted
		};

public:

/** @fn				~CProtTransaction()
	Intended Usage:	Destructor - cleans up and releases resources to the system	
	@since			7.0
*/
	//##ModelId=3B1E52B40031
	IMPORT_C virtual ~CProtTransaction();

public: // accessors

/**	@fn				TransactionState() const
	Intended Usage:	Provides the state of the transaction, e.g. pending, 
						active, etc.
	@since			7.0
	@return			A enum specifying the state of the transaction.
*/
	//##ModelId=3C4C37E50306
	TTransactionState TransactionState() const;

/**	@fn				SetTransactionState(TTransactionState aState)
	Intended Usage:	Sets the state of the transaction.
	@since			7.0
	@param			aState	The state that the transaction is in.
	@post			The state of the transaction has been updated.
*/
	//##ModelId=3C4C37E502D4
	void SetTransactionState(TTransactionState aState);

/**	@fn				ResetRxData()
	Intended Usage:	Resets the Rx data object. The Rx data object must be 
						created again to be used.
	@since			7.0
	@post			The Rx data objects has been reset.
*/
	//##ModelId=3C4C37E502CA
	IMPORT_C void ResetRxData();

/**	@fn				ResetTxData()
	Intended Usage:	Resets the Tx data object. The Tx data object must be 
						created again to be used.
	@since			7.0
	@post			The Tx data objects has been reset.
*/
	//##ModelId=3C4C37E502C0
	IMPORT_C void ResetTxData();

/**	@fn				Transaction() const
	Intended Usage:	Obtain the API-level transaction to which this object
						corresponds to.
	@since			7.0
	@return			The API-level transaction that this object corresponds to.
*/
	//##ModelId=3B1E52B40013
	IMPORT_C RHTTPTransaction Transaction() const;

/**	@fn				TxData() const
	Intended Usage:	Obtain the Transmit Data portion of the transaction.
	@since			7.0
	@return			A reference to the Tx data object of the transaction.
*/
	//##ModelId=3B1E52B40012
	IMPORT_C CTxData& TxData() const;

/**	@fn				RxData() const
	Intended Usage:	Obtain the Receive Data portion of the transaction.
	@since			7.0
	@return			A reference to the Rx data object of the transaction.
*/
	//##ModelId=3B1E52B40009
	IMPORT_C CRxData& RxData() const;

public:	// Methods to be implemented by derived classes

/**	@fn				CreateTxDataL() =0
	Intended Usage:	Creates the appropriate CTxData object.
	@since			7.0
	@leave			KErrNoMemory if there is not enough memory available to 
					create the object.
*/
	//##ModelId=3C4C37E502AC
	virtual void CreateTxDataL() =0;

/**	@fn				CreateRxDataL(MRxDataObserver& aObserver) =0
	Intended Usage:	Creates the appropriate CRxData object.
	@since			7.0
	@leave			KErrNoMemory if there is not enough memory available to 
					create the object.
	@param			aObserver	A reference to the observer for the Rx data object.
*/
	//##ModelId=3C4C37E50284
	virtual void CreateRxDataL(MRxDataObserver& aObserver) =0;

protected: // Methods

/** @fn				CProtTransaction()
	Intended Usage:	Default constructor	
	@since			7.0
*/
	//##ModelId=3B1E52B303E6
	CProtTransaction();

/** @fn				CProtTransaction(RHTTPTransaction aTrans)
	Intended Usage:	Normal constructor, of a CProtTransaction that corresponds to the
					supplied client transaction handle.
	@since			7.0
	@param			aTrans	(in) The client transaction handle.
*/
	//##ModelId=3B1E52B303E7
	IMPORT_C CProtTransaction(RHTTPTransaction aTrans);

protected:	// Attributes

	/** The client transaction
	*/
	//##ModelId=3B1E52B303D4
	RHTTPTransaction iTrans;

	/** The transmission data
	*/
	//##ModelId=3B1E52B303CA
	CTxData* iTxData;

	/** The received data
	*/
	//##ModelId=3B1E52B303C0
	CRxData* iRxData;

	/** Transaction state indicator.
	*/
	//##ModelId=3C4C37E50247
	TTransactionState	iTransactionState;

private: // methods

/**	@fn				Reserved1()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C37E5026F
	inline virtual void Reserved1();

/**	@fn				Reserved2()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C37E50251
	inline virtual void Reserved2();
	};


inline void CProtTransaction::Reserved1()
	{}
inline void CProtTransaction::Reserved2()
	{}


#endif // __CPROTTRANSACTION_H__

