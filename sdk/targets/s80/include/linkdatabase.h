/*
* ==============================================================================
*  Name        : linkdatabase.h
*  Part of     : Linkmodel
*  Interface   : Add to Desk API
*  Description : Shortcut link objects and shortcut database
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef __LINKDATABASE_H__
#define __LINKDATABASE_H__

// INCLUDES
#include <databaseengine.h>
#include <databaseentry.h>
#include <d32dbms.h>
#include <cntdb.h>
#include <msvapi.h>

// FORWARD DECLARATIONS
class CBrokenShortcutUpdater;
class CGulIcon;
class CViewRoute;
class RApaLsSession;
class CViewRouteEntry;
class CLinkCustomIcon;
class CApaCommandLine;
class TApaAppInfo;

// FUNCTION PROTOTYPES
GLREF_C void WriteHBufL(RWriteStream& aWriteStream,const HBufC* aBuf);
GLREF_C void WriteHBufL(RWriteStream& aWriteStream,const HBufC8* aBuf);
GLREF_C void ReadHBufL(RReadStream& aReadStream,HBufC*& aBuf);
GLREF_C void ReadHBufL(RReadStream& aReadStream,HBufC8*& aBuf);

// CONSTANTS
const TInt KMaxGroupName=KMaxCategoryName;
const TInt KMaxLinkName=255;

enum
	{ // deprecated. Use 'EDatabaseEngineGroupPreferencesChanged' instead
	EShortcutDatabaseGroupPrefsChanged=EDatabaseEngineGroupPreferencesChanged
	};

enum
	{
	EIconSizeSmall=0, // list view
	EIconSizeMedium, // currently not supported
	EIconSizeLarge, // grid view
	EMaxIconSizes=3, // max number of icons supported
	};

enum
	{ // used as low bits of category flags
	ELinkModelGroupTypeNormal=0,
	ELinkModelGroupCannotBeDeletedOrRenamed=1,
	ELinkModelGroupHidden=2,
	ELinkModelGroupTypeMask=7
	// flag bits 32 and above can be used by user
	};

enum TShortcutType
	{
	EShortcutTypeApplication=0,
	EShortcutTypeContact,
	EShortcutTypeDocument,
	EShortcutTypeMessage,
	EShortcutTypeUrl,
	};

/**
*  Base class for all shortcuts that can be added to Desk.
*
*  @lib linkmodel.lib
*  @since Series90 1.0
*/
class CShortcutEntry : public CDatabaseEntryBase
	{
	public:
	enum
		{ // shortcut position
		EShortcutPositionUnassigned=-1, // fills first available space
		EShortcutPositionLast=-2 // appears at end
		};
	enum
		{ // flags
		EUsingDefaultName=1,
		EIsPermanentlyBroken=2,
		EModifiedByUser=4,
		EPersistedFlags=0x0fff,
		};
	public:

		/**
		* Two-phased constructor. Creates an empty shortcut of given type.
		* @return Pointer to the empty shortcut.
		* <BR><B>Type of return value:</B> CShortcutEntry*
		*/
		IMPORT_C static CShortcutEntry* NewLC(TShortcutType aType);

		/**
		* Destructor.
		*/
		IMPORT_C ~CShortcutEntry();

		/**
		* Gets the shortcut link name.
		* @return The name of the shortcut link.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC Name() const;

		/**
		* Checks if the shortcut link is permanently broken.
		* @return ETrue if link is permanently broken
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool IsPermanentlyBroken() const;

		/**
		* Checks if the shortcut has been customized by the user.
		* @return ETrue if the shortcut has been customized by the user
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool HasBeenModifiedByUser() const;

		/**
		* Updates the shortcut to indicate if it has been modified by
		* the user.
		* @param aModified If ETrue the EModifiedByUser will be set else it will be
		* cleared.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetModifiedByUser(TBool aModified);

		/**
		* Sets the custom icon to be displayed with the shortcut link.
		* @param aIconInfo The information about the custom icon.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetCustomIconL(const CLinkCustomIcon& aIconInfo);

		/**
		* Sets the icon for the shortcut link to be that of an existing 
		* application icon
		* @param aIconUid The UID of the application whose icon is to be used.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void OverrideIcon(TUid aIconUid);

		/**
		* Get the UID of the application icon to be used for this shortcut link.
		* @param aApaLsSession An open application session.
		* @param aIsOverridden This is set to ETrue if the icon has been 
		* overridden using the OverrideIcon() function, i.e. if its icon is 
		* taken from another application.
		* @return The UID of the application icon
		* <BR><B>Type of return value:</B> TUid
		*/
		IMPORT_C TUid IconUid(RApaLsSession& aApaLsSession,TBool& aIsOverridden) const;

		/**
		* Set the name of the shortcut link. This creates a copy of the 
		* specified descriptor, hence it may leave.
		* @param aShortcutName The name to set.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetNameL(const TDesC& aShortcutName);

		/**
		* Set the name of the shortcut link. This takes ownership of the 
		* specified descriptor, and it cannot leave.
		* @param aShortcutName The name to set.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetName(HBufC* aShortcutName);

		/**
		* Sets the index of the shortcut's position on the Desk 'All' page.
		* @param aPosition The shortcut's position.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetPosition(TInt aPosition);

		/**
		* Get the index of the shortcut's position on the Desk 'All' page.
		* @return The shortcut's position.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt Position() const;

		/**
		* Returns custom icon information about the shortcut link.
		* @param aIndex On return, contains the index value of the icon 
		* bitmap in the .mbm file.
		* @return The .mbm filename of the icon
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC CustomIconInfo(TInt& aIndex) const;

		/**
		* Opens the shortcut link. 
		* @param aApaLsSession An open application session.
		* @param aReturnView The view to return to after the shortcut 
		* application is closed.
		* @return ETrue if app was already open
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C virtual TBool StartLinkL(RApaLsSession& aApaLsSession,CViewRouteEntry* aReturnView=NULL);

		virtual TBool OnceBrokenAlwaysBroken() const;

		/**
		* Get the type of shortcut link.
		* @return The shortcut type
		* <BR><B>Type of return value:</B> TShortcutType
		*/
		virtual TShortcutType ShortcutType() const=0;

		/**
		* Does this shortcut's parameters match another shortcuts?
		* @param aShortcutEntry The shortcut to compare with this one.
		* @return ETrue if the shortcuts match.
		* <BR><B>Type of return value:</B> TBool
		*/
		virtual TBool ParametersMatch(const CShortcutEntry& aShortcutEntry) const=0;

		/**
		* Is this shortcut broken?
		* @param aFs An open file session.
		* @param aApaLsSession An open application session.
		* @return ETrue if the shortcut link is broken.
		* <BR><B>Type of return value:</B> TBool
		*/
		virtual TBool IsBrokenL(RFs& aFs,RApaLsSession& aApaLsSession) const=0;

		/**
		* Gets the UID of the application needed to open the shortcut, 
		* e.g. a shortcut to a Word document would have the Word app's UID.
		* @param aApaLsSession An open application session.
		* @return The application UID.
		* <BR><B>Type of return value:</B> TUid
		*/
		virtual TUid AppUsedToStartShortcutL(RApaLsSession& aApaLsSession) const=0;

		/**
		* Gets the UID of the application whose icon is displayed in this 
		* shortcut link.
		* @param aApaLsSession An open application session.
		* @return The application UID.
		* <BR><B>Type of return value:</B> TUid
		*/
		virtual TUid GetIconUid(RApaLsSession& aApaLsSession) const=0;

		/**
		* Add this shortcut to the specified view route.
		* @param aRoute The view route to add the shortcut to.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void SetupHilViewRouteL(CViewRoute& aRoute) const=0;

		/**
		* Write the shortcut's parameters to a data stream.
		* @param aWriteStream The data stream to write to.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void DoExternalizeL(RWriteStream& aWriteStream) const=0;

		/**
		* Read the shortcut's parameters from a data stream.
		* @param aWriteStream The data stream to read from.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void DoInternalizeL(RReadStream& aReadStream)=0;

		/**
		* Two-phased constructor.
		* @param aType The type of shortcut.
		* @param aFlags The flags for the shortcut. These are:
		*	EUsingDefaultName		=1
		*	EIsPermanentlyBroken	=2
		*	EPersistedFlags			=0x0fff
		* @return Pointer to the new shortcut.
		* <BR><B>Type of return value:</B> TUid
		*/
		static CShortcutEntry* NewLC(TShortcutType aType,TInt aFlags);

		TBool UsingDefaultName() const;
		TUid CustomIconUid() const;
		void ExternalizeL(RWriteStream& aWriteStream) const;
		void InternalizeL(RReadStream& aReadStream);
		void SetPermanentlyBroken() const;
		void SetFlags(TInt aFlags);
		IMPORT_C TInt Flags() const;
	protected:

		/**
		* C++ default constructor.
		*/
		CShortcutEntry();
		void SetDefaultNameL(TInt aRid);
		void RemoveNonPrintableChars();
		virtual void ConstructL();
		static TBool CanUseHilViewToStartAppL(TUid aAppUid);
	protected:
		HBufC* iCustomIconFileName;
		HBufC* iLinkName;
		TInt iPosition;
		TInt iCustomIconIndex;
	private:
		mutable TUid iIconUid;
		mutable TInt iFlags;

	friend class CShortcutDatabase;
	};

/**
 * This class stores information specific to a group other than "All". 
 * At the moment it only stores extra positional information.
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CShortcutCategoryInfo : public CEntryCategoryInfoBase
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CShortcutCategoryInfo();

		/**
		* Get the position of the shortcut category.
		* @return The position.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt ShortcutPosition() const;

		/**
		* Set the position of the shortcut category.
		* @param aPosition The position.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetShortcutPosition(TInt aPosition);
//
		void InternalizeL(RReadStream& aReadStream);
		void ExternalizeL(RWriteStream& aWriteStream) const;
	private:
		TInt iPosition;
	};

/**
 * This class stores group information for a shortcut - an array of
 * CShortcutCategoryInfo, one for each group the shortcut has been added to.
 * 
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CShortcutGrouping : public CDatabaseEntryGrouping
	{
	public:

		/**
		* Creates category information for the group.
		* @return A pointer to the category info data.
		* <BR><B>Type of return value:</B> CEntryCategoryInfoBase*
		*/
		IMPORT_C CEntryCategoryInfoBase* CreateCategoryInfoLC();

		/**
		* Adds an empty shortcut to this group.
		* @param aGroupId The type of shortcut to add.
		* @param aPosition The position of the shortcut link.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void AddShortcutToGroupL(TDatabaseCategoryId aGroupId,TInt aPosition=CShortcutEntry::EShortcutPositionUnassigned);
	};

class TSheetAndChartDocumentInfo
/** @internalComponent */
	{
public:
	TSheetAndChartDocumentInfo();
	TSheetAndChartDocumentInfo(TInt aSheetOrChartIndex,TBool aIsChart);
	void ExternalizeL(RWriteStream& aWriteStream) const;
	void InternalizeL(RReadStream& aReadStream);
	TBool IsChart() const;
	TInt SheetOrChartIndex() const;
private:
	TInt iSheetOrChartIndex;
	TBool iIsChart;
	};

/**
 * This is a type of shortcut link which can link to a document or a folder.
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CDocumentShortcut : public CShortcutEntry
	{
	public:

		/**
		* C++ default constructor.
		*/
		CDocumentShortcut();

		/**
		* Destructor.
		*/
		~CDocumentShortcut();
//

		/**
		* Returns the filename of the document that this shortcut links to.
		* @return The document filename.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC Document() const;

		/**
		* Sets the document that this shortcut links to.
		* @param aFs An open file session.
		* @param aDocument The document filename.
		* @param aSetLinkNameFromDocName If this is ETrue then the shortcut 
		* will have the same name as the document.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetDocumentL(RFs& aFs,const TDesC& aDocument,TBool aSetLinkNameFromDocName=ETrue);

		/**
		* Sets the folder that this shortcut links to.
		* @param aFs An open file session.
		* @param aFolder The path of the folder.
		* @param aSetLinkNameFromDocName If this is ETrue then the shortcut 
		* will have the same name as the folder.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetFolderL(RFs& aFs,const TDesC& aFolder,TBool aSetLinkNameFromFolderName=ETrue);

		/**
		* Does this shortcut link to a document or a folder?
		* @return ETrue if the shortcut links to a folder.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool IsFolder() const;
//

		void SetExtraInfoL(const TDesC8& aInfo);
// from CShortcutEntry
		TShortcutType ShortcutType() const;
		TBool ParametersMatch(const CShortcutEntry& aShortcutEntry) const;
		TBool IsBrokenL(RFs& aFs,RApaLsSession& aApaLsSession) const;
		TBool StartLinkL(RApaLsSession& aApaLsSession,CViewRouteEntry* aReturnView);
		TUid AppUsedToStartShortcutL(RApaLsSession& aApaLsSession) const;
		TUid GetIconUid(RApaLsSession& aApaLsSession) const;
		void SetupHilViewRouteL(CViewRoute& aRoute) const;
		void DoExternalizeL(RWriteStream& aWriteStream) const;
		void DoInternalizeL(RReadStream& aReadStream);
//
		static void SetupHilViewRouteL(CViewRoute& aRoute,const TDesC& aFolder);
	private:
		HBufC* iDocument;
		HBufC8* iExtraInfo;
		TUint iVolumeUniqueID;
	};

class TApplicationShortcutParams
/** @internalComponent */
	{
public:
	inline TUid AppUid() const { return iAppUid; };
	inline void SetAppUid(TUid aAppUid) { iAppUid=aAppUid; };
//
	void ExternalizeL(RWriteStream& aWriteStream) const;
	void InternalizeL(RReadStream& aReadStream);
private:
	TUid iAppUid;
	};

/**
 *  This is a type of shortcut which can be used to link to an application.
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CApplicationShortcut : public CShortcutEntry
	{
	public:

		/**
		* C++ default constructor.
		*/
		CApplicationShortcut();

		/**
		* Opens an application.
		* @param aApaLsSession An open application session.
		* @param aUid The UID of the application to start up.
		* @return ETrue if the application was already running.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool StartAppL(RApaLsSession& aApaLsSession,TUid aUid);

		/**
		* Opens an application.
		* @param aApaLsSession An open application session.
		* @param aDocument The document whose owner application is to be 
		* started up.
		* @return ETrue if the application was already running.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool StartAppL(RApaLsSession& aApaLsSession,const TDesC& aDocument);
//

		/**
		* Get the UID of the application that this shortcut links to.
		* @return The application UID.
		* <BR><B>Type of return value:</B> TUid
		*/
		IMPORT_C TUid AppUid() const;

		/**
		* Sets the UID of the application that this shortcut links to.
		* @param aApaLsSession An open application session.
		* @param aAppUid The application UID.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetAppUidL(RApaLsSession& aApaLsSession,TUid aAppUid);

		/**
		* Sets the UID of the application that this shortcut links to.
		* @param aAppInfo the application information
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetAppL(const TApaAppInfo& aAppInfo);
// from CShortcutEntry

		TShortcutType ShortcutType() const;
		TBool StartLinkL(RApaLsSession& aApaLsSession,CViewRouteEntry* aReturnView);
		TBool ParametersMatch(const CShortcutEntry& aShortcutEntry) const;
		TBool IsBrokenL(RFs& aFs,RApaLsSession& aApaLsSession) const;
		TUid AppUsedToStartShortcutL(RApaLsSession& aApaLsSession) const;
		TUid GetIconUid(RApaLsSession& aApaLsSession) const;
		void SetupHilViewRouteL(CViewRoute& aRoute) const;
		void DoExternalizeL(RWriteStream& aWriteStream) const;
		void DoInternalizeL(RReadStream& aReadStream);
//
		static TBool StartAppL(RApaLsSession& aApaLsSession,TUid aAppUid,const TDesC& aDocument,CViewRouteEntry* aReturnView);
		static TBool StartAppL(RApaLsSession& aApaLsSession,TUid aAppUid,const TDesC& aDocument);
	private:
		static void SetupHilViewRouteL(CViewRoute& aRoute,TUid aAppUid,const TDesC& aDocument);
		static void SetDefaultDocL(CApaCommandLine& aCmdLine,const TApaAppInfo& aAppInfo);
	private:
	TApplicationShortcutParams iParams;
	};

/**
 *  This is a type of shortcut which can be used to link to a web URL or a 
 *  bookmark.
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CUrlShortcut : public CShortcutEntry
	{
	public:

		/**
		* C++ default constructor.
		*/
		CUrlShortcut();

		/**
		* Destructor.
		*/
		~CUrlShortcut();
//

		/**
		* Gets the URL that the shortcut links to.
		* @return The shortcut's URL.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC Url() const;

		/**
		* Sets the URL that the shortcut links to.
		* @param aUrl The shortcut's URL.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetUrlL(const TDesC& aUrl);

		static void SetupHilViewRouteL(CViewRoute& aRoute,const TDesC& aUrl);
// from CShortcutEntry
		TBool StartLinkL(RApaLsSession& aApaLsSession,CViewRouteEntry* aReturnView=NULL);
		TShortcutType ShortcutType() const;
		TBool ParametersMatch(const CShortcutEntry& aShortcutEntry) const;
		TBool IsBrokenL(RFs& aFs,RApaLsSession& aApaLsSession) const;
		TUid AppUsedToStartShortcutL(RApaLsSession& aApaLsSession) const;
		TUid GetIconUid(RApaLsSession& aApaLsSession) const;
		void SetupHilViewRouteL(CViewRoute& aRoute) const;
		void DoExternalizeL(RWriteStream& aWriteStream) const;
		void DoInternalizeL(RReadStream& aReadStream);
	private:
		HBufC* iUrl;
	};

/**
 *  This is a type of shortcut which can be used to link to a contact card.
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CContactShortcut : public CShortcutEntry
	{
	public:

		/**
		* C++ default constructor.
		*/
		CContactShortcut();
//

		/**
		* Gets the ID of the contact card that this shortcut links to.
		* @return The contact card ID.
		* <BR><B>Type of return value:</B> TContactItemId
		*/
		IMPORT_C TContactItemId ContactItem() const;

		/**
		* Sets the ID of the contact card that this shortcut links to.
		* @param aContact The contact card ID.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetContactItemL(const CContactItem& aContact);
//
		static void SetupHilViewRouteL(CViewRoute& aRoute,TContactItemId aContactId,TInt aFieldId);
// from CShortcutEntry

		TBool OnceBrokenAlwaysBroken() const;
		TShortcutType ShortcutType() const;
		TBool ParametersMatch(const CShortcutEntry& aShortcutEntry) const;
		TBool IsBrokenL(RFs& aFs,RApaLsSession& aApaLsSession) const;
		TUid AppUsedToStartShortcutL(RApaLsSession& aApaLsSession) const;
		TUid GetIconUid(RApaLsSession& aApaLsSession) const;
		void SetupHilViewRouteL(CViewRoute& aRoute) const;
		void DoExternalizeL(RWriteStream& aWriteStream) const;
		void DoInternalizeL(RReadStream& aReadStream);
	private:
		mutable TContactItemId iContactId;
	};

/**
 *  This is a type of shortcut which can be used to link to a message of any 
 *  type.
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CMessageShortcut : public CShortcutEntry
	{
	public:

		/**
		* C++ default constructor.
		*/
		CMessageShortcut();
//

		/**
		* Gets the ID of the message that this shortcut links to.
		* @return The message ID.
		* <BR><B>Type of return value:</B> TMsvId
		*/
		IMPORT_C TMsvId MessageId() const;

		/**
		* Sets the message that this shortcut links to.
		* This gets the application UID and shortcut link name from the message 
		* server entry.
		* @param aEntry The message server entry.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMessageL(const TMsvEntry& aEntry);

		/**
		* Sets the message that this shortcut links to.
		* @param aEntryId The message ID.
		* @param aMtmUid The UID of the application used to edit this message.
		* @param aLinkName The name of the shortcut link.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMessageL(const TMsvId& aEntryId,TUid aMtmUid,const TDesC& aLinkName);
//
		static void SetupHilViewRouteL(CViewRoute& aRoute,TMsvId aEntryId);
// from CShortcutEntry
		TBool OnceBrokenAlwaysBroken() const;
		TShortcutType ShortcutType() const;
		TBool ParametersMatch(const CShortcutEntry& aShortcutEntry) const;
		TBool IsBrokenL(RFs& aFs,RApaLsSession& aApaLsSession) const;
		TUid AppUsedToStartShortcutL(RApaLsSession& aApaLsSession) const;
		TUid GetIconUid(RApaLsSession& aApaLsSession) const;
		void SetupHilViewRouteL(CViewRoute& aRoute) const;
		void DoExternalizeL(RWriteStream& aWriteStream) const;
		void DoInternalizeL(RReadStream& aReadStream);
	private:
		mutable TMsvId iMessageId;
		mutable TUid iMtmUid;
	};

/**
*  This class stores preferences for a group of desk icons
*  Other prefs classes can be derived from MGroupPrefsBase
*  to store additional preference settings
*
*  @lib linkmodel.lib
*  @since Series90 1.0
*/
class TGroupPrefs : public MGroupPrefsBase
	{
	public:
// from MGroupPrefsBase

		/**
		* Store the preferences to a data stream.
		* @param aWriteStream The data stream to write to.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void ExternalizeL(RWriteStream& aWriteStream) const;

		/**
		* Get the preferences from a data stream.
		* @param aReadStream The data stream to read from.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void InternalizeL(RReadStream& aReadStream);
	public:
		TFileName iImageName;
		TInt iZoomState;
	private:
	enum
		{
		EGroupPrefsStreamVersion=500,
		};
	};

/**
 *  Mixin observer class for broken links.
 *
 *  A class derived from this will be called when a link is broken, if it is set
 *  as the link observer with CShortcutDatabase::StartIdleBrokenLinkUpdateL().
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class MBrokenLinkUpdaterObserver
	{
	public:

		/**
		* Callback function when a link is found to be broken.
		* @param aEntry The shortcut in question.
		* @param aBroken ETrue if the entry is broken. EFalse if it is not.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void HandleLinkBroken(CShortcutEntry& aEntry,TBool aBroken)=0;
	};

/**
 *  Class for looking up shortcut entryId from app Uid
 *
 *  Used when calling the GetAppShortcutIds() function in CShortcutDatabase
 *
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class TAppShortcutLookup
	{
public:
	TUid iAppUid;
	TDatabaseEntryId iEntryId;
	};

/**
 * Class for accessing Desk shortcuts
 *
 * Use functions in CDatabaseEngine for reading/writing shortcuts.
 * 
 *  @lib linkmodel.lib
 *  @since Series90 1.0
 */
class CShortcutDatabase : public CDatabaseEngineImp
	{
	public:

		/**
		* Opens the shortcut database.
		* @param aFs An open file session.
		* @return A pointer to the shortcut database.
		* <BR><B>Type of return value:</B> CShortcutDatabase*
		*/
		IMPORT_C static CShortcutDatabase* OpenL(RFs& aFs);

		/**
		* Creates and opens the shortcut database.
		* @param aFs An open file session.
		* @return A pointer to the shortcut database.
		* <BR><B>Type of return value:</B> CShortcutDatabase*
		*/
		IMPORT_C static CShortcutDatabase* CreateL(RFs& aFs);

		/**
		* Creates and opens the shortcut database, replacing any existing one.
		* @param aFs An open file session.
		* @return A pointer to the shortcut database.
		* <BR><B>Type of return value:</B> CShortcutDatabase*
		*/
		IMPORT_C static CShortcutDatabase* ReplaceL(RFs& aFs);

		/**
		* Recreates an empty shortcut database - not static. 
		* Used after major corruption.
		* @param aFs An open file session.
		* @return A pointer to the shortcut database.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void RecreateDatabaseL(RFs& aFs);

		/**
		* Destructor.
		*/
		IMPORT_C ~CShortcutDatabase();

		/**
		* Returns type of a shortcut in the database.
		* Note that this is quicker than reading the entire shortcut.
		* @param aEntryId The ID of the database entry.
		* @return The shortcut type.
		* <BR><B>Type of return value:</B> TShortcutType
		*/
		IMPORT_C TShortcutType ShortcutTypeL(TDatabaseEntryId aEntryId);

		/**
		* Returns name of a shortcut in the database.
		* Note that this is quicker than reading the entire shortcut.
		* @param aEntryId The ID of the database entry.
		* @return The shortcut name.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC ShortcutNameL(TDatabaseEntryId aEntryId);

		/**
		* Deletes the given application from all groups.
		* @param aAppUid The UID of the application to delete.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void RemoveAllAppShortcutsL(TUid aAppUid);

		/**
		* Gets the database ID of the shortcut of the specified application.
		* @param aAppUid The UID of the application to find.
		* @return The database ID of the application's shortcut.
		* <BR><B>Type of return value:</B> TDatabaseEntryId
		*/
		IMPORT_C TDatabaseEntryId AppShortcutIdL(TUid aAppUid);
	
		/**
		* Adds an application to the given group.
		* @param aApp The UID of the application to add.
		* @param aLsSession An open application session.
		* @param aGroup The group to add the app to. Default value is 
		* KNullDatabaseCategoryId which sets the "All" group.
		* @param aIndex The position of the shortcut in the group. Default 
		* value is -1.
		* @return The database entry ID of the new or modified entry.
		* <BR><B>Type of return value:</B> TDatabaseEntryId
		*/
		IMPORT_C TDatabaseEntryId AddAppToGroupL(TUid aApp,RApaLsSession& aLsSession,TDatabaseCategoryId aGroup=KNullDatabaseCategoryId,TInt aIndex=-1,TBool aUpdatePositionIfAlreadyInGroup=ETrue);

		/**
		* Removes an application from the given group.
		* @param aApp The UID of the application to remove.
		* @param aGroup The group to add the app to. Default value is 
		* KNullDatabaseCategoryId which sets the "All" group.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void RemoveAppFromGroupL(TUid aApp,TDatabaseCategoryId aGroup=KNullDatabaseCategoryId);

		/**
		* Updates a shortcuts position.
		* Note that this is quicker than writing the entire shortcut.
		* @param aEntryId The database entry to update.
		* @param aNewPosition The new position of the shortcut.
		* @param aCategoryId The group in which to modify the shortcut's 
		* position. Default value is KNullDatabaseCategoryId which sets 
		* the "All" group.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void UpdateShortcutPositionL(TDatabaseEntryId aEntryId,TInt aNewPosition,TDatabaseCategoryId aCategoryId=KNullDatabaseCategoryId);

		/**
		* Updates a shortcuts position.
		* Note that this is quicker than writing the entire shortcut.
		* @param aEntryId The database entry to update.
		* @param aNewPosition The new position of the shortcut in the All category
		* @param aNewGrouping The new grouping information for other categories
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void UpdateShortcutL(TDatabaseEntryId aEntryId,TInt aNewPosition,CDatabaseEntryGrouping& aNewGrouping);

		/**
		* Returns an array of all application shortcuts stored in the database and their entryIds.
		* The array will be sorted by application Uid. Array ownership transferred to the caller.
		* If the return value is NULL then an error ocurred creating the array
		* <BR><B>Type of return value:</B> CArrayFixSeg<TAppShortcutLookup>
		*/
		IMPORT_C CArrayFixSeg<TAppShortcutLookup>* GetAppShortcutIds();

		/**
		* Compares shortcuts for type, name and parameters.
		* @param aEntryId The first shortcut entry to compare.
		* @param aSecondEntryId The first shortcut entry to compare.
		* @return ETrue if the shortcuts match.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool ShortcutsMatchL(TDatabaseEntryId aEntryId,TDatabaseEntryId aSecondEntryId);

		/**
		* Updates all document shortcuts that point to a particular filename 
		* to point to a new file.
		* @param aFs An open file session.
		* @param aOldDocName The old document filename.
		* @param aNewDocName The new document filename.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void UpdateDocShortcutL(RFs& aFs,const TDesC& aOldDocName,const TDesC& aNewDocName);

		/**
		* Checks if shortcut already exists in a group, i.e. a shortcut that 
		* has the same type, parameters and optionally same name.
		* @param aShortcut The shortcut to be checked.
		* @param aGroup The group to look in.
		* @param aCheckName ETrue if the name should be checked. EFalse if not.
		* @return The ID of the identical shortcut in the database.
		* <BR><B>Type of return value:</B> TDatabaseEntryId
		*/
		IMPORT_C TDatabaseEntryId DoesShortcutExistL(const CShortcutEntry& aShortcut,TDatabaseCategoryId aGroup,TBool aCheckName=ETrue);

		/**
		* Checks if a shortcut exists in any group with the same name
		* @param aApaLsSession An open application session.
		* @param aShortcut The shortcut to be checked.
		* @return The ID of the identical shortcut in the database.
		* <BR><B>Type of return value:</B> TDatabaseEntryId
		*/
		IMPORT_C TDatabaseEntryId DoesShortcutExistL(RApaLsSession& aApaLsSession,const CShortcutEntry& aShortcut);

		/**
		* Checks if a shortcut exists in any group with the same name and 
		* application used to open the shortcut.
		* @param aApaLsSession An open application session.
		* @param aShortcutName The name of the shortcut to be checked.
		* @param aAppUsedToStartShortcut The UID of the application to check.
		* @return The ID of the identical shortcut in the database.
		* <BR><B>Type of return value:</B> TDatabaseEntryId
		*/
		IMPORT_C TDatabaseEntryId DoesShortcutExistL(RApaLsSession& aApaLsSession,const TDesC& aShortcutName,TUid aAppUsedToStartShortcut);

		/**
		* Starts an idle object to update state of broken links.
		* @param aObserver The observer for the broken links. When a link is 
		* found to be broken or not, this callback class will be called.
		* @param aFs An open file session.
		* @param aApaLsSession An open application session.
		* @param aDelayBeforeStarting The interval before starting the broken
		* link check.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void StartIdleBrokenLinkUpdateL(MBrokenLinkUpdaterObserver* aObserver,RFs* aFs,RApaLsSession* aApaLsSession,TTimeIntervalMicroSeconds32 aDelayBeforeStarting);

		/**
		* Cancels the broken link updater. This must be called if a rollback 
		* or tables closed event occurs.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void CancelIdleBrokenLinkUpdate();

		/**
		* Pauses broken link updater for a given time. This is used to allow 
		* applications a look-in when tasking away.
		* @param aDelayBeforeStarting The length of the delay before restarting
		* the broken link updater.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void PauseIdleBrokenLinkUpdate(TTimeIntervalMicroSeconds32 aDelayBeforeStarting);

		/**
		* Finds the first entry in the database of a specified type.
		* @param aType The type of shortcut to look for.
		* @param aSqlBuf On return, gives an SQL string for the shortcut search.
		* This should be passed into further calls to FindNextL().
		* Leave this blank if it is just necessary to find the first database
		* entry of the given shortcut type.
		* @return The database ID of the shortcut entry, or KNullDatabaseEntryId
		* if no entry is found.
		* <BR><B>Type of return value:</B> TDatabaseEntryId
		*/
		IMPORT_C TDatabaseEntryId FindFirstL(TShortcutType aType,TDes& aSqlBuf);

		/**
		* Finds the next entry in the database of a given shortcut type.
		* @param aSqlBuf An SQL search string containing the shortcut type. This
		* is set automatically in a call to FindFirstL().
		* @return The database ID of the shortcut entry, or KNullDatabaseEntryId
		* if no entry is found.
		* <BR><B>Type of return value:</B> TDatabaseEntryId
		*/
		IMPORT_C TDatabaseEntryId FindNextL(TDes& aSqlBuf);

		void UpdateShortcutNameL(TDatabaseEntryId aEntryId,const TDesC& aNewName);
		void WriteShortcutFlagsL(CShortcutEntry& aEntry);
		TBool IsUsingDefaultNameL(TDatabaseEntryId aEntryId);
	private:
		CShortcutDatabase();
		TUid GetAppShortcutUidL(TDatabaseEntryId aEntryId);
		void WriteIntToTableL(RDbTable& aTable,TInt aEntryIdCol,TInt aDataCol,TDatabaseEntryId aEntryId,TInt aInteger,TInt aDataCol2=-1,TInt aInteger2=0);
		void WriteDesToTableL(RDbTable& aTable,TInt aEntryIdCol,TInt aDataCol,TDatabaseEntryId aEntryId,const TDesC& aDes,TInt aMaxLength);
		void WriteShortcutParamsL(CShortcutEntry& aEntry);
		void AddAppsToArrayL(CArrayFixSeg<TAppShortcutLookup>& aArray);
		TInt SeekL(RDbTable& aTable,TDatabaseEntryId aEntryId);
		TInt ShortcutPositionL(TDatabaseEntryId aEntryId,TDatabaseCategoryId aCategory);
//
		TInt DoOpenEntryTableL(RDbNamedDatabase& aDatabase,RDbTable& aTable,const TDesC& aTableName,const TDesC& a2ndColName,TInt& a2ndColNo);
		TInt DoOpenEntryTableL(RDbNamedDatabase& aDatabase,RDbTable& aTable,const TDesC& aTableName,const TDesC& a2ndColName,TInt& a2ndColNo,const TDesC& a3rdColName,TInt& a3rdColNo);
// from CDataBaseEngineImp
		CDatabaseEntryBase* CreateDatabaseEntryL(TDatabaseEntryId aEntryId);
		CDatabaseEntryGrouping* CreateCategoryGroupingLC();
		void DoDeleteCategoryL(TDatabaseCategoryId aCategoryId);
		void DoCommitEntryL(CDatabaseEntryBase& aEntry);
		void DoAddNewEntryL(CDatabaseEntryBase& aEntry);
		void DoDeleteEntryL(TDatabaseEntryId aEntryId);
		void DoCreateTablesL();
		void DoCloseTables();
		void DoOpenTablesL();
	private:
// shortcut type lookup table
		RDbTable iShortcutTypeLookupTable;
		TInt iTypeLookupEntryIdColNo;
		TInt iTypeLookupColNo;
		TInt iFlagLookupColNo;
// shortcut position lookup table
		RDbTable iShortcutPosLookupTable;
		TInt iPosLookupEntryIdColNo;
		TInt iPosLookupColNo;
// shortcut name lookup table
		RDbTable iShortcutNameLookupTable;
		TInt iNameLookupEntryIdColNo;
		TInt iNameLookupColNo;
// shortcut name lookup table
		RDbTable iShortcutParamsLookupTable;
		TInt iParamsLookupEntryIdColNo;
		TInt iParamsLookupColNo;
//
		CBrokenShortcutUpdater* iBrokenLinkUpdater;
	};


#endif // __LINKDATABASE_H__

// End of File
