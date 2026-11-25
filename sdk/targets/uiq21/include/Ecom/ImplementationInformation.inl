//
// ImplementationInformation.inl
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file ImplementationInformation.inl
	Comments : This file contains the implementation of
			the CImplementationInformation class.
 */ 

// ____________________________________________________________________________________
// Provide the inline implementation of CImplementationInformation
// CImplementationInformation provides access to information on a particular implementation
//
const TDesC& CImplementationInformation::DisplayName() const
	{
	if(iDisplayName == NULL)
		return KNullDesC();
	else
		return *iDisplayName;
	}

const TDesC8& CImplementationInformation::DataType() const
	{
	if(iData == NULL)
		return KNullDesC8();
	else
		return *iData;
	}

const TDesC8& CImplementationInformation::OpaqueData() const
	{
	if(iOpaqueData == NULL)
		return KNullDesC8();
	else
		return *iOpaqueData;
	}

TUid CImplementationInformation::ImplementationUid() const
	{
	return iImplementationUid;
	}

TInt CImplementationInformation::Version() const
	{
	return iVersion;
	}

TBool CImplementationInformation::Disabled() const
	{
	return iDisabled;
	}

void CImplementationInformation::SetDisabled(TBool aDisabled)
	{
	iDisabled = aDisabled;
	}
