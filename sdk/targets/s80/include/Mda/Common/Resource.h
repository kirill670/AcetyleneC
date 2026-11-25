// Mda\Common\Resource.h
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_COMMON_RESOURCE_H__
#define __MDA_COMMON_RESOURCE_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Base.h>
#include <Mda\Common\Port.h>
#include <Mda\Common\Controller.h>
#include <Mda\Common\Resource.hrh>

// Uids
MDA_UID(KUidMdaResourceManager) // Resoruce Manager Uid
MDA_UID(KUidMdaSourceClip) // Resource Clip Handle Uids
MDA_UID(KUidMdaDestinationClip) 
MDA_UID(KUidMdaClipLocation) // Resource Clip Location/Format type Uids
MDA_UID(KUidMdaClipFormat) 
MDA_UID(KUidMdaSourceStream) // Resource Stream Handle Uids
MDA_UID(KUidMdaDestinationStream) 
MDA_UID(KUidMdaStreamDevice) // Resource Stream Device Uid
MDA_UID(KUidMdaFileResLoc) // Clip Location Uids
MDA_UID(KUidMdaDesResLoc) 
MDA_UID(KUidMdaUrlResLoc) 
MDA_UID(KUidMdaClipDuration) // Time related Uids
MDA_UID(KUidMdaClipPrimeWindow) 
MDA_UID(KUidMdaClipCrop) 


/**
 * @publishedAll
 * @deprecated
 *
 * Unknown size
 */
const TInt KMdaResourceSizeUnknown = KMdaUnknown;

/**
 * @publishedAll
 * @deprecated 
 */
const TInt KMdaRepeatForever = -2;

// Function numbers

/**
 * @publishedAll
 * @deprecated 
 *
 * Resource Port Handle
 */
enum 
	{
	EMLbResourceHandleConfig=EMLbPortNegotiate+1
	};

/**
 * @publishedAll
 * @deprecated 
 *
 *  Resource object functions
 */
enum
	{
	EMLbResourceObjectConfig=0,
	EMLbResourceObjectCreatePort=1
	};

/**
 * @publishedAll
 * @deprecated 
 *
 * Clip Location
 */
enum 
	{
	EMLbClipFunctionBase=EMLbResourceObjectCreatePort,
	EMLbClipLocRead,
	EMLbClipLocWrite
	};

/**
 * @publishedAll
 * @deprecated 
 *
 * Resource event IDs
 */
enum 
	{
	EMdaResourceEventIdConfigComplete,
	EMdaResourceEventIdConfigFailed,
	EMdaResourceEventIdSizeChanged,
	EMdaResourceEventIdDataChanged
	};

// Resource package classes

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaResourceQuery : public TMdaPackage
	{
public:
	TMdaResourceQuery(TUid aType);
	};

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaClipLocation : public TMdaPackage
	{
protected:
	inline TMdaClipLocation(TUid aUid, TInt aDerivedSize);
public:
	TInt iSize; // In bytes
	TInt iVisible; // In bytes
	};

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaClipFormat : public TMdaPackage
	{
public:
	inline TMdaClipFormat();
protected:
	inline TMdaClipFormat(TUid aUid, TInt aDerivedSize);
	};

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaClipFormatQuery : public TMdaClipFormat
	{
public:
	inline TMdaClipFormatQuery(TUid aUid, TInt aAdditionalSize);
	};

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaStreamDevice : public TMdaPackage
	{
protected:
	inline TMdaStreamDevice(TUid aUid, TInt aDerivedSize);
	};

// Clip Locations

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaFileClipLocation : public TMdaClipLocation
	{
public:
	inline TMdaFileClipLocation();
	inline TMdaFileClipLocation(const TDesC& aName);
public:
	TBuf<256> iName;
	};

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaDesClipLocation : public TMdaClipLocation
	{
public:
	inline TMdaDesClipLocation();
	inline TMdaDesClipLocation(TDes8& aWriteableDes);
	inline TMdaDesClipLocation(const TDesC8& aReadOnlyDes);
public:
	TThreadId iThreadId;
	TDesC8* iDes;
	};

/**
 * @publishedAll
 * @deprecated 
 */
class TMdaUrlClipLocation : public TMdaClipLocation
	{
public:
	inline TMdaUrlClipLocation();
	inline TMdaUrlClipLocation(const TDesC& aUrl, TInt aIapId, const TDesC8& aMimeType = KNullDesC8);
public:
	TBuf<256> iUrl;
	TBuf8<256> iMimeType;
	TInt iIapId;
	};


// Inline functions

inline TMdaResourceQuery::TMdaResourceQuery(TUid aType) :
TMdaPackage(aType,KNullUid,sizeof(TMdaResourceQuery)) {}
	
inline TMdaClipLocation::TMdaClipLocation(TUid aUid, TInt aDerivedSize) :
TMdaPackage(KUidMdaClipLocation,aUid,aDerivedSize) {}

inline TMdaClipFormat::TMdaClipFormat(TUid aUid, TInt aDerivedSize) :
TMdaPackage(KUidMdaClipFormat,aUid,aDerivedSize) {}

inline TMdaClipFormatQuery::TMdaClipFormatQuery(TUid aUid, TInt aAdditionalSize) :
TMdaClipFormat(aUid,sizeof(TMdaClipFormat)+aAdditionalSize) {}
	
inline TMdaClipFormat::TMdaClipFormat() : 
TMdaPackage(KUidMdaClipFormat,KNullUid,sizeof(TMdaClipFormat)) {}

inline TMdaStreamDevice::TMdaStreamDevice(TUid aUid, TInt aDerivedSize) :
TMdaPackage(KUidMdaStreamDevice,aUid,aDerivedSize) {}

inline TMdaFileClipLocation::TMdaFileClipLocation() : 
TMdaClipLocation(KUidMdaFileResLoc,sizeof(TMdaFileClipLocation)) {}

inline TMdaFileClipLocation::TMdaFileClipLocation(const TDesC& aName) :
TMdaClipLocation(KUidMdaFileResLoc,sizeof(TMdaFileClipLocation)), 
iName(aName) {}

inline TMdaUrlClipLocation::TMdaUrlClipLocation() : 
TMdaClipLocation(KUidMdaUrlResLoc,sizeof(TMdaUrlClipLocation)) {}

inline TMdaUrlClipLocation::TMdaUrlClipLocation(const TDesC& aUrl, TInt aIapId, const TDesC8& aMimeType) :
TMdaClipLocation(KUidMdaUrlResLoc,sizeof(TMdaUrlClipLocation)), 
iUrl(aUrl),iMimeType(aMimeType), iIapId(aIapId) {}


inline TMdaDesClipLocation::TMdaDesClipLocation() :
TMdaClipLocation(KUidMdaDesResLoc,sizeof(TMdaDesClipLocation)),
iThreadId(RThread().Id()) {}

inline TMdaDesClipLocation::TMdaDesClipLocation(const TDesC8& aReadOnlyDes) :
TMdaClipLocation(KUidMdaDesResLoc,sizeof(TMdaDesClipLocation)),
iThreadId(RThread().Id()),
iDes(&(TDesC8&)aReadOnlyDes) {}

inline TMdaDesClipLocation::TMdaDesClipLocation(TDes8& aWriteableDes) :
TMdaClipLocation(KUidMdaDesResLoc,sizeof(TMdaDesClipLocation)),
iThreadId(RThread().Id()),
iDes(&aWriteableDes) {}

#endif
