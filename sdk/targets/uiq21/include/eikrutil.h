// EIKRUTIL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKRUTIL_H__)
#define __EIKRUTIL_H__

#include <e32std.h>
#include <gulutil.h>

class CFbsFont;
class CEikonEnv;
class CWsScreenDevice;
class TResourceReader;

/**
 *
 * This class provides utilities for reading standard resources.
 * @since 6.0
 * @lib " eikcore.lib "
 */
class EikResourceUtils
	{
public:
	inline static CFbsFont* CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CFbsFont* CreateScreenFontL(TInt aResourceId,CEikonEnv* aEnv=NULL);
	inline static TInt8 ReadTInt8L(TInt aResourceId,CEikonEnv* aEnv=NULL);
	inline static TInt16 ReadTInt16L(TInt aResourceId,CEikonEnv* aEnv=NULL);
	inline static TInt32 ReadTInt32L(TInt aResourceId,CEikonEnv* aEnv=NULL);
	IMPORT_C static CColorArray* CreateColorArrayL(TInt aResourceId,CEikonEnv* aEnv=NULL);
	IMPORT_C static CColorArray* CreateColorArrayLC(TInt aResourceId,CEikonEnv* aEnv=NULL);
	//
private:
	enum TResourceTypeInt { EResourceInt8,EResourceInt16,EResourceInt32 };
private:
	IMPORT_C static TInt32 ReadResourceIntL(TInt aResourceId,CEikonEnv* aEnv,TResourceTypeInt aSize);
	};

inline CFbsFont* EikResourceUtils::CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice)
	{
	return(ResourceUtils::CreateScreenFontL(aResourceReader,aScreenDevice));
	}

/**
 *
 * Gets the 8 bit signed integer held in a specified resource location.
 *
 * @param     " TInt aResourceId "
 *            The location in the resource to be read.
 * @param     " CEikonEnv* aEnv "
 *            The Eikon environment.
 * @returns   " TInt8 "
 *            The eight bits that follow the specified location in
 *            the resource.
 */
inline TInt8 EikResourceUtils::ReadTInt8L(TInt aResourceId,CEikonEnv* aEnv)
	{
	return((TInt8)ReadResourceIntL(aResourceId,aEnv,EResourceInt8));
	}

/**
 *
 * Gets the 16 bit signed integer held in a specified resource location.
 *
 * @param     " TInt aResourceId "
 *            The location in the resource to be read.
 * @param     " CEikonEnv* aEnv "
 *            The Eikon environment.
 * @returns   " TInt16 "
 *            The 16 bits that follow the specified location in the
 *            resource.
 */
inline TInt16 EikResourceUtils::ReadTInt16L(TInt aResourceId,CEikonEnv* aEnv)
	{
	return((TInt16)ReadResourceIntL(aResourceId,aEnv,EResourceInt16));
	}

/**
 *
 * Gets the 32 bit signed integer held in a specified resource location.
 *
 * @param     " TInt aResourceId "
 *            The location in the resource to be read.
 * @param     " CEikonEnv* aEnv "
 *            The Eikon environment.
 * @returns   " TInt32 "
 *            The 32 bits that follow the specified location in the
 *            resource.
 */
inline TInt32 EikResourceUtils::ReadTInt32L(TInt aResourceId,CEikonEnv* aEnv)
	{
	return((TInt32)ReadResourceIntL(aResourceId,aEnv,EResourceInt32));
	}

#endif
