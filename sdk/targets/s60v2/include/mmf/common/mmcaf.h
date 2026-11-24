// include\mm\common\mmcaf.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//
// CAF wrapper classes for Multimedia.

#ifndef __MM_COMMON_MMCAF_H__
#define __MM_COMMON_MMCAF_H__

#include <F32File.h>
#include <caf\caf.h>

#ifdef SYMBIAN_CAF_V2

/**
@publishedAll
@released

A class that provides a consistent interface between filename based and file handle based API's.
In particular this API:

- provides support for container files with embedded content
- allows enabling/disabling of Agent provided user interface features (AgentUI)
- allows a client to take explicit responsibility for the execution of intent
*/

const TUid KUidMMFileSource = {0x101F7D3E};
const TUid KUidMMFileHandleSource = {0x101F7D3F};

class TMMSource
	{
public:
	/**
	TODO: add SYSDOC comments
	*/
	IMPORT_C TUid SourceType() const;
	
	IMPORT_C const TDesC& UniqueId() const;
	IMPORT_C ContentAccess::TIntent Intent() const;

protected:
	IMPORT_C TMMSource(TUid aSourceType, const TDesC& aUniqueId, ContentAccess::TIntent aIntent);

private:
	/**
	TODO: add SYSDOC comments
	*/
	TUid iSourceType;
	const TDesC& iUniqueId;
	ContentAccess::TIntent iIntent;
	TInt iReserved1;
	TInt iReserved2;
	TInt iReserved3;
	};
	
class TMMFileHandleSource : public TMMSource
	{
public:
	IMPORT_C TMMFileHandleSource(RFile& aFile);
	IMPORT_C TMMFileHandleSource(RFile& aFile, const TDesC& aUniqueId);
	IMPORT_C TMMFileHandleSource(RFile& aFile, const TDesC& aUniqueId, ContentAccess::TIntent aIntent);

	IMPORT_C RFile& Handle() const;

private:
	RFile& iFile;
	};

class TMMFileSource : public TMMSource
	{
public:
	/**
	TODO: add SYSDOC comments
	*/
	IMPORT_C TMMFileSource(const TDesC& aName);
	IMPORT_C TMMFileSource(const TDesC& aName, const TDesC& aUniqueId);
	IMPORT_C TMMFileSource(const TDesC& aName, const TDesC& aUniqueId, ContentAccess::TIntent aIntent);
	
	IMPORT_C const TDesC& Name() const;
	
private:
	/**
	TODO: add SYSDOC comments
	*/
	const TDesC& iName;	// filename or descriptor or url
	};

#endif // SYMBIAN_CAF_V2
	
#endif // __MM_COMMON_MMCAF_H__
