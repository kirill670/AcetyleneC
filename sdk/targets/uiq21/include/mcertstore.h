// MCertInfo.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MCERTINFO_H__
#define __MCERTINFO_H__

#include <ct.h>
#include <cctcertinfo.h>
#include <ccertattributefilter.h>

/** @ingroup interfaces */
/** @{ */


/** The base class for certificate storage */
class MCertStore
	{
public:
	///@name Listing Certificates
	///@{
	/** List all certificates that satisfy the supplied filter.
		This is an async function; all errors are reported by
		completing aStatus with the error value, and it can be
		cancelled with CancelList

		@param aCerts An array into which the returned certificates are placed.
		@param aFilter A filter to select which certificates should be included
		@param aStatus a Request status that will be completed when
		the operation completes.
*/
	virtual void List(RMPointerArray<CCTCertInfo>& aCerts, const CCertAttributeFilter& aFilter,
		TRequestStatus& aStatus) = 0;
	/** Cancel any ongoing list operation. If it is cancelled, it will
		be completed with KErrCancel.
	 */
	virtual void CancelList() = 0;
	///@}

	///@name Getting a certificate from a handle.
	///@{
	/** Gets a certificate given its handle.
		@param aCertInfo The returned certificate.
		@param aHandle Thehandle of the certificate to return
		@param aStatus A request status that is completed when the
		operation has finished.
	 */
	virtual void GetCert(CCTCertInfo*& aCertInfo, const TCTTokenObjectHandle& aHandle, 
		TRequestStatus& aStatus) = 0;
	/** Cancel an ongoing GetCert operation. If the operation hasn't
	 * already completed, it will complete with KErrCancel. */
	virtual void CancelGetCert() = 0;
	///@}

	///@name Querying the applications of a certificate.
	///@{
	/** List the applications of a certificate. Applications are
		represented by UIDs. Examples would be Software Install, TLS,
		WTLS, WMLScript SignText etc.
		@param aCertInfo The certificate to return applications for.
		@param aApplications An array to save the applications in.
		@param aStatus  A request status that is completed when the
		operation has finished.
	*/
	virtual void Applications(const CCTCertInfo& aCertInfo, RArray<TUid>& aAplications,
		TRequestStatus& aStatus) = 0;
	/** Cancels an ongoing Applications operation */
	virtual void CancelApplications() = 0;
	/** Indicates if a particular certificate is applicable to a
		particular application
		@param aCertInfo The certificate in question
		@param aApplication The application
		@param aIsApplicable Set to ETrue or EFalse by the function to
		return the result.
		@param aStatus A request status that is completed when the
		operation has finished.
	*/
	virtual void IsApplicable(const CCTCertInfo& aCertInfo, TUid aApplication, 
		TBool& aIsApplicable, TRequestStatus& aStatus) = 0;
	/** Cancels an IsApplicable operation */
	virtual void CancelIsApplicable() = 0;
	///@}

	///@name Trust querying
	///@{
	/** Returns if a certificate is trusted. Trust is only meaningful
		for CA certificates where it means that the certificate can be
		used as a trust root for the purposes of certificate
		validation.
		@param aCertInfo The certificate we're interested in.
		@param aTrusted Used to return the trust status.
		@param aStatus A request status that is completed when the
		operation has finished.
	*/
	virtual void Trusted(const CCTCertInfo& aCertInfo, TBool& aTrusted, 
		TRequestStatus& aStatus) = 0;
	/** Cancels an ongoing Trusted operation */
	virtual void CancelTrusted() = 0;
	///@}

	///@name Retrieving the actual certificate
	///@{
	/** Retrieves the actual data of the certificate.
		@param aCertInfo the certificate to retrieve
		@param aEncodedCert. A buffer to put the certificate in. It
		must be big enough. (The sizze is stored in aCertInfo)
		@param  aStatus A request status that is completed when the
		operation has finished.
	 */
	virtual void Retrieve(const CCTCertInfo& aCertInfo, TDes8& aEncodedCert, 
		TRequestStatus& aStatus) = 0;
	/** Cancels an ongoing Retrieve operation */
	virtual void CancelRetrieve() = 0;
	///@}
	};
///@}
#endif

