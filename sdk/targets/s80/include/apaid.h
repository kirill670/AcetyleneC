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


class TApaAppIdentifier
/** The identity of an application.

An object of this type contains two pieces of information:

The application specific UID

The file name and extension of the application DLL

All persisted documents associated with this application have a stream containing 
this information.

@publishedAll 
@released
@see CApaProcess::ReadRootStreamLC()
@see CApaProcess::WriteRootStreamL()
@see CApaProcess::ReadAppIdentifierL()
@see CApaProcess::WriteAppIdentifierL() */
	{
public:
	IMPORT_C TApaAppIdentifier();
	IMPORT_C TApaAppIdentifier(TUid aAppUidType,const TFileName& aDllName);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	/** The application-specific UID. */
	TUid iAppUid;
	/** The full path name of the application DLL. */
	TFileName iFullName;
	};


class TApaAppEntry
/** An application entry.

An object of this type contains two pieces of information:

the full path name of the application DLL

the UID type (or compound identifier) of the application DLL. 

@publishedAll 
@released */
	{
public:
	IMPORT_C TApaAppEntry();
	IMPORT_C TApaAppEntry(const TUidType& aAppUidType,const TFileName& aDllName);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	/** The UID type (or compound identifier) of the application DLL. */
	TUidType iUidType;
	/** The full path name of the application DLL. */
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
class TApaAppInfoBC
	{
public:
	IMPORT_C TApaAppInfoBC();
	IMPORT_C TApaAppInfoBC(TUid aAppUid,const TFileName& aDllName,const TApaAppCaption& aCaption);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUid iUid;
	TFileName iFullName;
	TApaAppCaption iCaption;
	};

/**
 *
 * Application information.
 *
 * Added to handle addition of iShortCaption without breaking BC
 *
 */
class TApaAppInfo : public TApaAppInfoBC
	{
public:
	IMPORT_C TApaAppInfo();
	IMPORT_C TApaAppInfo(TUid aAppUid,const TFileName& aDllName,const TApaAppCaption& aCaption);
	IMPORT_C TApaAppInfo(TUid aAppUid,const TFileName& aDllName,const TApaAppCaption& aCaption,const TApaAppCaption& aShortCaption);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TApaAppCaption iShortCaption;
	};


class TApaAppViewInfo
/** Contains the basic information about an application view.

An object of this type contains two pieces of information:

The UID that identifies the view

The application's caption.

Objects of this type are returned in an array populated by a call to RApaLsSession::GetAppViews().

@publishedAll 
@released
@see CApaAppViewArray
@see TUid */
	{
public:
	IMPORT_C TApaAppViewInfo();
	IMPORT_C TApaAppViewInfo(TUid aViewUid,const TApaAppCaption& aViewCaption,TInt aScreenMode);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	/** The UID identifying the view. */
	TUid iUid;
	/** The application caption. */
	TApaAppCaption iViewCaption;
	TInt iScreenMode;
	};


/** Defines an array of TApaAppViewInfo objects contained within a flat dynamic 
buffer.

An array of this type is populated with TApaAppViewInfo objects in a call 
to RApaLsSession::GetAppViews().

@publishedAll 
@released */
typedef CArrayFixFlat<TApaAppViewInfo> CApaAppViewArray;


class TApaAppCapability
// expandable class - add new members to the end, add them to the end of int/ext also, and increment the version no.
// default value for all data members must be 0
/** Application capabilities. 

@publishedAll
@released */
	{
public:
	IMPORT_C static void CopyCapability(TDes8& aDest,const TDesC8& aSource);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	//
	/** Defines an application's support for embeddability. */
	enum TEmbeddability {
		/** An application cannot be embedded. */
		ENotEmbeddable=0,
		/** An application can be run embedded or standalone and can read/write embedded document-content. */
		EEmbeddable=1,
		/** An application can only be run embedded and can read/write embedded document-content. */
		EEmbeddableOnly=2,
		/** An application can be run embedded or standalone and cannot read/write embedded document-content. */
		EEmbeddableUiOrStandAlone=5,
		/** An application can only be run embedded and cannot read/write embedded document-content. */
		EEmbeddableUiNotStandAlone=6 };
public:
	/** Indicates the extent to which the application can be embedded. */
	TEmbeddability iEmbeddability;
	/** Indicates whether the application is document-based and supports being asked 
	to create a new file. */
	TBool iSupportsNewFile;
	/** Indicates whether the existence of the application should be advertised to the 
	user. If this is set to ETrue, the application does not appear on the Extras 
	Bar (or equivalent). */
	TBool iAppIsHidden; // not shown in the Shell etc.
	/** Allows the application to be launched in the foreground (when set to EFalse) 
	or in the background (when set to ETrue). */
	TBool iLaunchInBackground;	// Series 60 extension to allow apps to be launched in the background	
	/** Stores the application's logical group name. */
	TApaAppGroupName iGroupName; // Series 60 extension to allow apps to be categorized according a logical group name, e.g. 'games'
private:
	enum { EVersion=3 };
	};

/** Packages the TApaAppCapability class. 

@publishedAll
@released */
typedef TPckgBuf<TApaAppCapability> TApaAppCapabilityBuf;


/** Filter used to define the subset of applications returned by RApaLsSession::GetNextApp()

@publishedAll
@released
*/
class TApaEmbeddabilityFilter
	{
public:
	IMPORT_C TApaEmbeddabilityFilter();
	IMPORT_C void AddEmbeddability(TApaAppCapability::TEmbeddability aEmbeddability);
	IMPORT_C TBool MatchesEmbeddability(TApaAppCapability::TEmbeddability aEmbeddability) const;
private:
	TUint iEmbeddabilityFlags;
	};


class CApaAppFinder : public CBase
/**
@publishedPartner
@released 
*/
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
