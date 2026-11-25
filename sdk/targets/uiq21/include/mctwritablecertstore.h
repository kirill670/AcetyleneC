// Copyright (c) Symbian 2001

#ifndef __MCTWRITABLECERTSTORE_H__
#define __MCTWRITABLECERTSTORE_H__

#include <mctcertstore.h>

/** The UID of writeable cert store interfaces. A token that supports
	this interface should also support the read-only cert store
	interface. */
const TInt KInterfaceWritableCertStore = 0x101F501C;

/** @ingroup interfaces */
/** @{ */

/** A writeable cert store. This extends the read-only cert store API
	in MCTCertStore by adding functions to add and delete certificates,
	and to set their applicability and trust settings. 
*/
class MCTWritableCertStore : public MCTCertStore
	{
public:
	///@name Adding a certificate
	///@{
	/** Adds a certificate to the store
		@param alabel The label of the certificate to add
		@param aFormat the format of the certificate
		@param aCertificateOwnerType The owner type
		@param aSubjectKeyId The Subject key ID
		@param aIssuerKeyId The issuer key ID
		@param aCert The certificate to add
		@param aStatus This is completed with the return result when the
		add has completed 
	*/
	virtual void Add(const TDesC& aLabel, TCertificateFormat aFormat,
		TCertificateOwnerType aCertificateOwnerType, 
		const TKeyIdentifier* aSubjectKeyId,
		const TKeyIdentifier* aIssuerKeyId,
		const TDesC8& aCert, TRequestStatus& aStatus) = 0;
	/** Cancels an ongoing add operation. The operation will be
		completed with KErrCancel if it was cancelled */
	virtual void CancelAdd() = 0;
	///@}

	///@name Removing Certificates
	///@{
	/** Removes a certificate
		@param aCertInfo The certificate to remove
		@param aStatus This is completed with the return result when the
		remove has completed.
	 */
	virtual void Remove(const CCTCertInfo& aCertInfo, TRequestStatus& aStatus) = 0;
	/** Cancels an ongoing remove operation. The operation will be
		completed with KErrCancel if it was cancelled */
	virtual void CancelRemove() = 0;
	///@}

	///@name Setting applicability
	///@{
	/** Replaces the current applicability settings with the settings
		in the supplied array.
		@param aCertInfo The certificate whose applicability should be updated.
		@param aApplications The new applications
		@param aStatus This is completed with the return result when the
		operation has completed.
	*/
	virtual void SetApplicability(const CCTCertInfo& aCertInfo, 
		RArray<TUid>* aApplications, TRequestStatus &aStatus) = 0;
	/** Cancels an ongoing operation. The operation will be
		completed with KErrCancel if it was cancelled */
	virtual void CancelSetApplicability() = 0;
	///@}

	///@name Changing trust settings
	///@{
	/** Changes the trust settings. A CA certificate is trusted if the
		user is willing to use it for authenticating servers. It has no
		meaning with other types of certificates.
		@param aCertInfo The certificate to update.
		@param aTrusted Whether or not it is trusted
		@param aStatus This is completed with the return result when the
		operation has completed.
	*/
	virtual void SetTrust(const CCTCertInfo& aCertInfo, TBool aTrusted, 
		TRequestStatus& aStatus) = 0;
	/** Cancels an ongoing operation. The operation will be
		completed with KErrCancel if it was cancelled */
	virtual void CancelSetTrust() = 0;
	///@}
	};
///@}
#endif
