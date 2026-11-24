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


class EikResourceUtils
/** Provides utilities for reading standard resources. 

@publishedAll 
*/
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
/** Create a screen font from resource.

Creates a font for the specified screen device by reading a font UID and font 
flags from the given position in a resource. Returns a pointer to the font 
and transfers ownership.

@param aResourceReader The resource reader to use to read the font. 
@param aScreenDevice The screen device for which the font will be created. 
@return Screen font object. */
	{
	return(ResourceUtils::CreateScreenFontL(aResourceReader,aScreenDevice));
	}

inline TInt8 EikResourceUtils::ReadTInt8L(TInt aResourceId,CEikonEnv* aEnv)
/** Gets the 8 bit signed integer held in a specified resource location.

@param aResourceId The location in the resource to be read. 
@param aEnv The UI environment. 
@return The eight bits that follow the specified location in the resource. */
	{
	return((TInt8)ReadResourceIntL(aResourceId,aEnv,EResourceInt8));
	}

inline TInt16 EikResourceUtils::ReadTInt16L(TInt aResourceId,CEikonEnv* aEnv)
/** Gets the 16 bit signed integer held in a specified resource location.

@param aResourceId The location in the resource to be read. 
@param aEnv The UI environment. 
@return The 16 bits that follow the specified location in the resource. */
	{
	return((TInt16)ReadResourceIntL(aResourceId,aEnv,EResourceInt16));
	}

inline TInt32 EikResourceUtils::ReadTInt32L(TInt aResourceId,CEikonEnv* aEnv)
/** Gets the 32 bit signed integer held in a specified resource location.

@param aResourceId The location in the resource to be read. 
@param aEnv The UI environment. 
@return The 32 bits that follow the specified location in the resource. */
	{
	return((TInt32)ReadResourceIntL(aResourceId,aEnv,EResourceInt32));
	}

#endif
