// MdaImageConverter.inl
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//

#include "MdaImageConverterPriv.h"

inline CMdaImageDataReadUtilityPriv* CMdaImageDataReadUtility::Properties() const
	{
	return static_cast<CMdaImageDataReadUtilityPriv*>(iProperties);
	}

inline CMdaImageDataWriteUtilityPriv* CMdaImageDataWriteUtility::Properties() const
	{
	return static_cast<CMdaImageDataWriteUtilityPriv*>(iProperties);
	}

inline CMdaImageFileToBitmapUtilityPriv* CMdaImageFileToBitmapUtility::Properties() const
	{
	return static_cast<CMdaImageFileToBitmapUtilityPriv*>(iProperties);
	}

inline CMdaImageDescToBitmapUtilityPriv* CMdaImageDescToBitmapUtility::Properties() const
	{
	return static_cast<CMdaImageDescToBitmapUtilityPriv*>(iProperties);
	}

inline CMdaImageBitmapToFileUtilityPriv* CMdaImageBitmapToFileUtility::Properties() const
	{
	return static_cast<CMdaImageBitmapToFileUtilityPriv*>(iProperties);
	}

inline CMdaImageBitmapToDescUtilityPriv* CMdaImageBitmapToDescUtility::Properties() const
	{
	return static_cast<CMdaImageBitmapToDescUtilityPriv*>(iProperties);
	}

inline CMdaImageBitmapToBitmapUtilityPriv* CMdaImageBitmapToBitmapUtility::Properties() const
	{
	return static_cast<CMdaImageBitmapToBitmapUtilityPriv*>(iProperties);
	}
