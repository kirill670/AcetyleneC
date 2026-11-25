// secdlg.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __SECDLG_H__
#define __SECDLG_H__

#include <ct.h>


///@file
/**@defgroup secdlg Security Dialog API */

///@{


/** The maximum length of a PIN label */
const TInt KPINLabelMaxLength = 64;
/**
 * TPINLabel is a human-readable name for the PIN to be entered.
 */
//64 = 255 bytes / poss 4bytes per unicode character
typedef TBuf<KPINLabelMaxLength> TPINLabel;


/**
 * TPINParams provides information associated with the PIN, 
 * to enable the dialog to display the name and do some basic correctness checking.
 */
class TPINParams
	{
public:
	/** The label that identifies the PIN */
	TPINLabel iPINLabel;
	/** The minimum length of the PIN */
	TInt iMinLength;
	/** The maximum length of the PIN */
	TInt iMaxLength;
	};

/** The max PIN length should not exceed 32, because this is the maximum
	size possible in the CEikSecretEditor class. */
const TInt KMaxPINLength = 32;
/** A PIN value */
typedef TBuf<KMaxPINLength> TPINValue;


/**
 * Definition of the security dialog interface
 *
 * @since 7.0
 */
class MSecurityDialog 
	{
public:
	/**
	 * TConnectionType defines the possible protocols used in EstablishSecureConnection
	 * which allows the type of the certificate to be derived.
	 */
	enum TConnectionType
		{
		EWTLS,
		ETLS
		};


public:
	/**
	 * Prompt the user to enter a PIN. 
	 *
	 * @param aPINParams Information about the PIN to enter.
	 * @param aRetry Indicates whether the user is retrying.
	 * 
	 * @param aPINValue returns the PIN the user entered: 
	 * 
	 */
	virtual void EnterPIN( const TPINParams& aPINParams, TBool aRetry, TPINValue& aPINValue,
						   TRequestStatus& aStatus ) = 0;

	/**
	 * Prompt the user to change a PIN. 
	 * 
	 * @param aPINParams Information about the PIN to change
	 * @param aRetry Indicates whether the user is retrying
	 * 
	 * @param aOldPINValue - returns the old PIN the user entered 
	 * @param aNewPINValue - returns the new PIN the user entered
	 */
	virtual void ChangePIN( const TPINParams& aPINParams, TBool aRetry,
							TPINValue& aOldPINValue, TPINValue& aNewPINValue,
							TRequestStatus& aStatus ) = 0;



	/**
	 * Prompt the user to enable a PIN. 
	 * 
	 * @param aPINParams Information about the PIN to enable.
	 * @param aRetry Indicates whether the user is retrying.
	 * 
	 * @param aPINValue - returns the PIN the user entered: 
	 * 
	 */
	virtual void EnablePIN( const TPINParams& aPINParams, TBool aRetry, TPINValue& aPINValue,
							TRequestStatus& aStatus ) = 0;

	/**
	 * Prompt the user to disable a PIN. 
	 * 
	 * @param aPINParams Information about the PIN to disable.
	 * @param aRetry Indicates whether the user is retrying.
	 * 
	 * @param aPINValue - returns the PIN the user entered: 
	 * 
	 */
	virtual void DisablePIN( const TPINParams& aPINParams, TBool aRetry,
								TPINValue& aPINValue, TRequestStatus& aStatus ) = 0;
	/**
	 * Prompt the user to unblock a PIN. 
	 * 
	 * @param aBlockedPINParams Information about the PIN to unblock
	 * @param aUnblockingPINParams Information about the unblocking PIN
	 * 	TBool aRetry Indicates whether the user is retrying
	 * 
	 * @param aUnblockingPINValue - returns the PIN the user entered
	 * 
	 */	
	virtual void UnblockPIN( const TPINParams& aBlockedPINParams,
							 const TPINParams& aUnblockingPINParams, TBool aRetry,
							 TPINValue& aUnblockingPINValue, TPINValue& aNewPINValue,
							 TRequestStatus& aStatus ) = 0;

	/**
	 * Inform the user that the PIN has become blocked.
	 * 
	 * @param aPINParams Information about the blocked PIN.
	 */
	virtual void PINBlocked( const TPINParams& aPINParams, TRequestStatus& aStatus ) = 0;
	
	/**
	 * Inform the user that a secure connection is being established with the given
	 * server, allowing them to proceed or cancel the operation.
	 * 
	 * @param aCertData The certificate sent by the server.
	 * @param aCertHandleList A selection of certificates to display to the user. All
	 * certificates are displayed if this is empty.
	 * @param aConnectionType This allows the type of certificate to be identified.
	 * @param aDoClientAuthentication Determines whether the user is prompted to
	 * agree to authenticate themselves to the server.
	 * 
	 * @param aDoClientAuthentication - if this was true before the method was called, it
	 * will contain the result of the user's decision on return.
	 * aCertHandle - an identifier for the certificate the user selected.
	 * aStatus - this will be set to KErrNotFound if no certificates could be presented to
	 * the user.
	 */	
	virtual void EstablishSecureConnection( const TDesC8& aCertData,
						const RArray<TCTTokenObjectHandle>& aCertHandleList,
						MSecurityDialog::TConnectionType aConnectionType,
						TBool& aDoClientAuthentication, TCTTokenObjectHandle& aCertHandle,
						TRequestStatus& aStatus ) = 0;

	/**
	 * Sign some text.
	 * 
	 * @param aTextToSign The text to be signed.
	 * @param aCertHandleList A selection of certificates to display to the user. All
	 * certificates are displayed if this is empty.
	 * 
	 * @param aCertHandle - returns an identifier for the certificate the user selected.
	 * aStatus - this will be set to KErrNotFound if no certificates could be presented to
	 * the user.
	 */
	virtual void SignText( const TDesC& aTextToSign,
							const RArray<TCTTokenObjectHandle>& aCertHandleList, 
							TCTTokenObjectHandle& aCertHandle,
							TRequestStatus& aStatus ) = 0;

	/**
	*	Release is called to free resources of the MSecurityDialog class
	*/
	virtual void Release()=0;


protected:
	/**
	 * 
	 * Destructor for the MSecurityDialog class
	 */
	inline virtual ~MSecurityDialog()=0;
	};
	inline MSecurityDialog::~MSecurityDialog(){}


/**
 * Factory for creating the relevant concrete subclass of the security dialog
 */
class SecurityDialogFactory
	{
public:
	/**
	 * Creates an instance of a subclass of MSecurityDialog. Implement to create
	 * the appropriate security dialog
	 * 
	 * @param returns an object that implements MSecurityDialog methods
	 */
	IMPORT_C static MSecurityDialog* CreateL();	};

///@}

#endif
