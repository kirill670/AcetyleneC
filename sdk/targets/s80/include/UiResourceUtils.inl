// UiResourceUtils.inl
//

#ifndef __HILRESOURCEUTILS_INL__
#define __HILRESOURCEUTILS_INL__

_LIT(KSystemDataPath, "\\System\\Data\\");

/*! 
	Load the most relevant language resource file.
	Note that the drive is determined by the caller's Dll filename.
	
	\param aCoeEnv Cone environment
	\param aOriginalResourceLeafName Leaf name of the original resource file (may have drive and folders in it, but these are ignored and it must be a parseable path)
	\param aOriginalResourcePath Path of the resource file (may have drive and leaf name in it, but these are ignored and it must be a parseable path)
*/
inline TInt UiResourceUtils::LoadResourceFileL(CCoeEnv& aCoeEnv, const TDesC& aOriginalResourceLeafName, const TDesC& aOriginalResourcePath)
	{
	TFileName fileName;
	Dll::FileName(fileName);
	return LoadResourceFileL(aCoeEnv, fileName, aOriginalResourceLeafName, aOriginalResourcePath);
	}

/*! 
	Load the most relevant language resource file.
	Note that the drive is determined by the caller's Dll filename and the path is the system data directory.
	
	\param aCoeEnv Cone environment
	\param aResourceLeafName Leaf name of the original resource file (may have drive and folders in it, but these are ignored and it must be a parseable path)
*/
inline TInt UiResourceUtils::LoadSystemResourceFileL(CCoeEnv& aCoeEnv, const TDesC& aResourceLeafName)
	{
	return LoadResourceFileL(aCoeEnv, aResourceLeafName, KSystemDataPath);
	}

#endif // __UIRESOURCEUTILS_INL__
