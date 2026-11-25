// PKIXVALIDATIONRESULT.H
//
// Copyright (c) 1998-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __PKIXVALIDATIONRESULT_H__
#define __PKIXVALIDATIONRESULT_H__

#include <x509certchain.h>
#include <x509CertExt.h>

/**
 * This class stores the information regarding the results of a validation.
 */
class CPKIXValidationResult : public CBase
	{
public:
	IMPORT_C static CPKIXValidationResult* NewL();
	IMPORT_C static CPKIXValidationResult* NewLC();
	IMPORT_C ~CPKIXValidationResult();
	IMPORT_C const TValidationStatus Error() const;
	IMPORT_C const CArrayFixFlat<TValidationStatus>& Warnings() const;
	IMPORT_C const CArrayPtrFlat<CX509CertPolicyInfo>& Policies() const;
	void Reset();
	void SetErrorAndLeaveL(const TValidationError aError, const TInt aCert);
	void SetError(const TValidationError aError, const TInt aCert);
	void AppendWarningL(TValidationStatus aWarning);
	void AppendPolicyL(CX509CertPolicyInfo& aPolicy);
	/**
	 * This function removes all the policies from the result. It is used by
	 * the validation to remove all policies it might have added when it can't complete 
	 * the computation due to 'external conditions' (like OOM, file access, not like
	 * signature validation...).
	 */
	void RemovePolicies();

private:
	CPKIXValidationResult();
	void ConstructL();
	TValidationStatus iError;
	CArrayFixFlat<TValidationStatus>* iWarnings;
	CArrayPtrFlat<CX509CertPolicyInfo>* iPolicies;
	};

#endif