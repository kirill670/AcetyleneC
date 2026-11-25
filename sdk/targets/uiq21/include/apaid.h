// APAID.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APAID_H__
#define __APAID_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

// classes defined:
class TApaAppIdentifier;
class TApaAppEntry;
class CApaAppFinder;
//
// classes referenced:
class RReadStream;
class RWriteStream;
class RFs;
//

/**
 *
 * The identity of an application.
 *
 * An object of this type contains two pieces of information:The
 * application specific UIDThe file name and extension of the application
 * DLLAll persisted documents associated with this application have a
 * stream containing this information.
 *
 * @since 5.0
 * @lib "apparc.lib"
 */
class TApaAppIdentifier
	{
public:
	IMPORT_C TApaAppIdentifier();
	IMPORT_C TApaAppIdentifier(TUid aAppUidType,const TFileName& aDllName);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUid iAppUid;
	TFileName iFullName;
	};


/**
 *
 * An application entry.
 *
 * An object of this type contains two pieces of information:the the full
 * path name of the application DLLthe UID type (or compound identifier)
 * of the application DLL.
 *
 * @since 5.0
 * @lib "apparc.lib"
 */
class TApaAppEntry
	{
public:
	IMPORT_C TApaAppEntry();
	IMPORT_C TApaAppEntry(const TUidType& aAppUidType,const TFileName& aDllName);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUidType iUidType;
	TFileName iFullName;
	};


/**
 *
 * Application information.
 *
 * An object of this type contains three pieces of information:the
 * application specific UIDthe full path name of the application DLLthe
 * caption for the application.
 *
 * @since 5.0
 * @lib "apparc.lib"
 */
class TApaAppInfo
	{
public:
	IMPORT_C TApaAppInfo();
	IMPORT_C TApaAppInfo(TUid aAppUid,const TFileName& aDllName,const TApaAppCaption& aCaption);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUid iUid;
	TFileName iFullName;
	TApaAppCaption iCaption;
	};



/**
 *
 * Contains the basic information about an application view.
 *
 * An object of this type contains two pieces of information:The UID that
 * identifies the viewThe application's caption.Objects of this type are
 * returned in an array populated by a call to
 * <code>RApaLsSession::GetAppViews()</code>.
 *
 * @since 6.1
 * @lib "apparc.lib"
 */
class TApaAppViewInfo
	{
public:
	IMPORT_C TApaAppViewInfo();
	IMPORT_C TApaAppViewInfo(TUid aViewUid,const TApaAppCaption& aViewCaption,TInt aScreenMode);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUid iUid;
	TApaAppCaption iViewCaption;
	TInt iScreenMode;
	};

/**
 *
 * Defines an array of <code>TApaAppViewInfo</code> objects contained
 * within a flat dynamic buffer.
 *
 * An array of this type is populated with <code>TApaAppViewInfo</code>
 * objects in a call to <code>RApaLsSession::GetAppViews()</code>.
 *
 * @since 6.1
 * @lib ""
 */	
typedef CArrayFixFlat<TApaAppViewInfo> CApaAppViewArray;


/**
 *
 * Application capabilities.
 * @since 5.0
 * @lib ""
 */
class TApaAppCapability
// expandable class - add new members to the end, add them to the end of int/ext also, and increment the version no.
// default value for all data members must be 0
	{
public:
	IMPORT_C static void CopyCapability(TDes8& aDest,const TDesC8& aSource);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	//
	/**
	 *
	 * Defines an application's support for embeddability.
	 * @since 
	 */
	enum TEmbeddability {
		/** An application cannot be embedded.
		 */
		ENotEmbeddable=0,
		/** An application can be embedded, and can also run as a main
		application.
		 */
		EEmbeddable,
		/** An application can only be embedded and will not run as a main
		application.
		 */
		EEmbeddableOnly };
public:
	TEmbeddability iEmbeddability;
	TBool iSupportsNewFile;
	TBool iAppIsHidden; // not shown in the Shell etc.
private:
	enum { EVersion=1 };
	};

/**
 *
 * Packages the <code>TApaAppCapability</code> class.
 * @since 5.0
 * @lib ""
 */	
typedef TPckgBuf<TApaAppCapability> TApaAppCapabilityBuf;


class CApaAppFinder : public CBase
	{
public:
	virtual void FindAllAppsL()=0; // sets up a scan for all apps
	virtual TBool NextL(TApaAppEntry& aEntry)=0; // increments a scan for all apps
	virtual TFileName FindAppL(const TDesC& aFileName,TUid aFileUid)=0; // searches for a particular app - should support wildcards in aFileName
	//
	virtual TFileName TempPath()const=0; // should return the drive and path of the temp directory
	virtual TFileName DefaultAppInfoFileName()const=0; // should return the full name, path and drive of the default icon file
	};


#endif
