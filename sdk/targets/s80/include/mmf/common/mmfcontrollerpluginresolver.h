// mmf\common\mmfcontrollerpluginresolver.h
//
// Copyright  2002 Symbian Ltd. All rights reserved.
//
#ifndef __MMF_COMMON_MMFCONTROLLERPLUGINRESOLVER_H__
#define __MMF_COMMON_MMFCONTROLLERPLUGINRESOLVER_H__

#include <ecom\ECom.h>
#include <E32Base.h>
#include <apmstd.h>


/**
@publishedAll
*/
const TUint KMMFDefaultControllerThreadHeapSize = 0x100000; //1MB


class CMMFFormatImplementationInformation;
/**
@publishedAll
*/
typedef RPointerArray<CMMFFormatImplementationInformation> RMMFFormatImplInfoArray;
class CMMFControllerImplementationInformation;
/**
@publishedAll
*/
typedef RPointerArray<CMMFControllerImplementationInformation> RMMFControllerImplInfoArray;

/**
@internalComponent

Interface to be implemented by customers of the class TaggedDataParser.
*/
class MTaggedDataParserClient
	{
public:
	virtual void ProcessTaggedDataL(const TDesC8& aTag, const TDesC8& aData) = 0;
	};

/**
@internalComponent

Utility class used to parse data separated by xml-style tags.
*/
class TaggedDataParser
	{
public:
/**
Splits aData into xml-style tags and values, and gets aClient to process each tag/value pair.
*/
	static void ParseTaggedDataL(const TDesC8& aData, MTaggedDataParserClient& aClient);
/**
Converts a string to a uid. If the string begin with "0x" it will be parsed as Hex, else Decimal.
*/
	static void ConvertTextToUidL(const TDesC8& aData, TUid& aUid);

/**
Converts a string to a TUint. The string must begin with "0x" and be 10 characters long,
otherwise it is considered corrupt.
*/
	static void ConvertTextToTUintL(const TDesC8& aData, TUint& aUid);
	
	};

class CDesC8Array;

/**
@publishedAll

Abstract class that contains basic information about ECom Multimedia plugins.

@released
@since 7.0s
*/
class CMMFPluginImplementationInformation : public CBase
	{
public:
/**
Returns the uid of this particular plugin implementation.
This is the UID used to instantiate this multimedia plugin.
@return "The implementation uid. "
@since 7.0s
*/
	IMPORT_C TUid Uid() const;
	
/**
Returns the display name of this plugin implementation.
@return "The display name."
@since 7.0s
*/
	IMPORT_C const TDesC& DisplayName() const;
	
/**
Returns the name of the supplier of this plugin implementation, e.g. "Symbian".
@return "The plugin supplier."
@since 7.0s
*/
	IMPORT_C const TDesC& Supplier() const;
	
/**
Returns the version number of this plugin.
@return "The version number."
@since 7.0s
*/
	IMPORT_C TInt Version() const;

/**
Returns the array of media ids supported by this plugin.

The media id can be used by clients to determine whether the plugin supports audio or
video data (or both). A uid is used for the media id to provide future extensibility.
@return "The array of media ids."
@since 7.0s
*/
	IMPORT_C const RArray<TUid>& SupportedMediaIds() const;

/**
Tests whether this plugin was supplied by aSupplier.
@param	"aSupplier"	"The required supplier."
@return "ETrue if this plugin was supplied by aSupplier, EFalse if not."
@since 7.0s
*/
	IMPORT_C TBool SupportsSupplier(const TDesC& aSupplier) const;

/**
Tests whether this plugin supports aMediaId.
@param	"aMediaId"	"The required media id."
@return "ETrue if this plugin supports aMediaId, EFalse if not."
@since 7.0s
*/
	IMPORT_C TBool SupportsMediaId(TUid aMediaId) const;

/**	Destructor. */
	virtual ~CMMFPluginImplementationInformation();

protected:
/** Constructor. */
	CMMFPluginImplementationInformation();
/** Sets the supplier.  Takes a copy of aData. */
	void SetSupplierL(const TDesC8& aData);
/** Adds a media id.  aData is parsed to find the uid of the media id to be added.*/
	void AddMediaIdL(const TDesC8& aData);
protected:
/** The UID of this plugin. */
	TUid iUid;
/** The display name of this plugin. */
	HBufC* iDisplayName;
/** The supplier of this plugin. */
	HBufC* iSupplier;
/** The version number of this plugin. */
	TInt iVersion;
/** The media ids supported by this plugin. */
	RArray<TUid> iMediaIds;
	};

/**
@publishedAll
@released

Contains format support information retrieved from the ECom registry.

An object of this type may describe either a concrete format plugin (ie a CMMFFormatEncode or a 
CMMFFormatDecode implementation) or a format supported by a controller plugin.

The object is created using a CImplementationInformation object retrieved from the ECom registry.
All relevant data is copied out of the CImplementationInformation object, and its opaque data is
parsed to provide the supplier, supported media ids, supported mime types, supported file extensions,
and supported header data matches.

Notes for Format Plugin developers:
The opaque data section of the ECom plugin resource file must be in the format:
`
opaque_data = "<?>Data 1<?>Data 2<?>Data 3<?>Data 4[...]<?>Data N";
`
The <?> preceding the data determines the meaning of the data.  The following are the possible tags:
`
	<s> - Supplier
	<i> - Media Id
	<m> - Mime Type
	<e> - File Extension
	<h> - Header Data
`
UIDs must always be in hex in the format '0x12345678', must include the '0x' and be 10 characters long/

@since 7.0s
*/
class CMMFFormatImplementationInformation : public CMMFPluginImplementationInformation, MTaggedDataParserClient
	{
public:
/**
Construct a new format implementation information object.

@param  "aImplInfo"	"The ECOM implementation information"
@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	static CMMFFormatImplementationInformation* NewL(const CImplementationInformation& aImplInfo);

/**
Construct a new format implementation information object.

@param  "aImplInfo"	"The ECOM implementation information"
@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created. Note that this will be on the cleanupStack."
@since 7.0s
*/
	static CMMFFormatImplementationInformation* NewLC(const CImplementationInformation& aImplInfo);

/** Destructor */
	virtual ~CMMFFormatImplementationInformation();


/**
Returns the array of supported file extensions.

@return "The array of file extensions."
@since 7.0s
*/
	IMPORT_C const CDesC8Array& SupportedFileExtensions() const;

/**
Returns the array of supported mime types.

@return "The array of mime types."
@since 7.0s
*/
	IMPORT_C const CDesC8Array& SupportedMimeTypes() const;

/**
Returns the array of supported header data matches.

@return "The array of header data."
@since 7.0s
*/
	IMPORT_C const CDesC8Array& SupportedHeaderData() const;


/**
Tests whether this format provides support for aFileExtension.
@param	"aFileExtension"	"The requested file extension.  Must be the extension only, and contain the dot '.'"
@return "ETrue if this format provides the required support, EFalse if not."
@since 7.0s
*/
	IMPORT_C TBool SupportsFileExtension(const TDesC8& aFileExtension) const;

/**
Tests whether this format provides support for aMimeType.
@param	"aMimeType"	"The requested mime type."
@return "ETrue if this format provides the required support, EFalse if not."
@since 7.0s
*/
	IMPORT_C TBool SupportsMimeType(const TDesC8& aMimeType) const;

/**
Tests whether this format provides support for aHeaderData.
aHeaderData is searched for each chunk supported by this format.
@param	"aMimeType"	"The requested header data."
@return "ETrue if this format provides the required support, EFalse if not."
@since 7.0s
*/
	IMPORT_C TBool SupportsHeaderDataL(const TDesC8& aHeaderData) const;
protected:
/** Constructor */
	CMMFFormatImplementationInformation();
/** 2nd phase constructor */
	void ConstructL(const CImplementationInformation& aImplInfo);
/** Adds a file extension to the array of extensions supported by this format. */
	void AddFileExtensionL(const TDesC8& aData);
/** Adds a mime type to the array of types supported by this format. */
	void AddMimeTypeL(const TDesC8& aData);
/** Adds a chunk of header data to the array of chunks supported by this format. */
	void AddHeaderDataL(const TDesC8& aData);

/** from MTaggedDataParserClient */
	void ProcessTaggedDataL(const TDesC8& aTag, const TDesC8& aData);

private:
/** The file extensions supported by this format. */
	CDesC8Array* iFileExtensions;
/** The mime types supported by this format. */
	CDesC8Array* iMimeTypes;
/** The header data chunks supported by this format. */
	CDesC8Array* iHeaderData;
	};


/**
@publishedAll
@released

Contains controller plugin information retrieved from the ECom registry.

The object is created using a CImplementationInformation object retrieved from the ECom registry.
All relevant data is copied out of the CImplementationInformation object, and its opaque data is
parsed to provide the supplier, supported media ids.

Notes for Format Plugin developers:
The exact formats supported by the controller plugin are calculated by:

1. The formats supported by the controller plugin itself must be declared in separate entries in the
controller plugin resource file.  Two interface uids should be defined by the plugin writer - one
for the play formats supported, the other for the record formats supported.  The play formats are
then listed as implementations of the play format interface uid, and likewise the record formats.

2. Format plugins (CMMFFormatEncode and CMMFFormatDecode) declare which controller plugin they 
extend.  ECom is search for the format plugins that extend the controller plugin, and they
are added to the list.

The opaque data section of the ECom plugin resource file must be in the format:
`
opaque_data = "<?>Data 1<?>Data 2<?>Data 3<?>Data 4[...]<?>Data N";
`
The <?> preceding the data determines the meaning of the data.  The following are the possible tags:
`
	<s> - Supplier - must be only one
	<i> - Media Id
	<p> - UID of play format 'interface' - must be only one
	<r> - UID of record format 'interface' - must be only one
`
UIDs must always be in hex in the format '0x12345678', must include the '0x' and be 10 characters long/

@since 7.0s
*/
class CMMFControllerImplementationInformation : public CMMFPluginImplementationInformation, MTaggedDataParserClient
	{
public:
/**
Construct a new controller implementation information object.

@param  "aImplInfo"	"The ECOM implementation information"
@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	static CMMFControllerImplementationInformation* NewL(const CImplementationInformation& aImplInfo);

/**
Construct a new controller implementation information object.

@param  "aImplInfo"	"The ECOM implementation information"
@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created. Note that this will be on the cleanupStack."
@since 7.0s
*/
	static CMMFControllerImplementationInformation* NewLC(const CImplementationInformation& aImplInfo);
	
	
/**
Construct a new controller implementation information object.
@param  "aUid"	"The Uid of the controller to obtain controller implementation information"
@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	IMPORT_C static CMMFControllerImplementationInformation* NewL(TUid aUid);


/** Destructor */
	~CMMFControllerImplementationInformation();

/**
Returns the array of play formats supported by this controller.
@return "The play formats supported."
@since	7.0s
*/
	IMPORT_C const RMMFFormatImplInfoArray& PlayFormats() const;

/**
Returns the array of record formats supported by this controller.
@return "The record formats supported."
@since	7.0s
*/
	IMPORT_C const RMMFFormatImplInfoArray& RecordFormats() const;

	IMPORT_C TUint HeapSpaceRequired() const;

/** Queries the ECom registry for the play formats supported. */
	void GetPlayFormatsL();
/** Queries the ECom registry for the record formats supported. */
	void GetRecordFormatsL();
protected:
/** Constructor */
	CMMFControllerImplementationInformation();
/** 2nd phase constructor */
	void ConstructL(const CImplementationInformation& aImplInfo);
/** Parses aData to get the collection uid of the play formats supported by this controller. */
	void SetPlayFormatCollectionUidL(const TDesC8& aData);
/** Parses aData to get the collection uid of the record formats supported by this controller. */
	void SetRecordFormatCollectionUidL(const TDesC8& aData);
/** Parses aData to get the size of the stack the controller requires */
	void SetHeapSizeL(const TDesC8& aData);

/** From MTaggedDataParserClient. */
	void ProcessTaggedDataL(const TDesC8& aTag, const TDesC8& aData);

/**
Queries the ECom registry for:
	- all registry entries with an interface uid of aFormatCollectionUid
	- all format plugins with an interface uid of aFormatPluginCollectionUid (ie CMMFFormatEncode
	  or CMMFFormatDecode) that have the uid of this controller plugin in the default_data field
	  of their ECom resource file.
CMMFFormatImplementationInformation objects are created for each entry returned, and appended to
aFormatArray.
@param "aFormatCollectionUid" "See above."
@param "aFormatPluginCollectionUid" "See above."
@param "aFormatArray" "See above."
@since 7.0s
*/
	void GetFormatsL(TUid aFormatCollectionUid, TUid aFormatPluginCollectionUid, RMMFFormatImplInfoArray& aFormatArray);

/**
Creates CMMFFormatImplementationInformation objects for all CImplementationInformation objects
in aEcomArray.  Any corrupt objects are ignored.  The objects created are added to aFormatArray.
@param "aEcomArray" "See above."
@param "aFormatArray" "See above."
@since 7.0s
*/
	void AddFormatsSwallowCorruptL(RImplInfoPtrArray& aEcomArray, RMMFFormatImplInfoArray& aFormatArray);

private:
/** The play formats supported by this controller. */
	RMMFFormatImplInfoArray iPlayFormats;
/** The record formats supported by this controller. */
	RMMFFormatImplInfoArray iRecordFormats;
/** The interface uid of the resource file definitions of the play formats supported directly by this controller. */
	TUid iPlayFormatCollectionUid;
/** The interface uid of the resource file definitions of the record formats supported directly by this controller. */
	TUid iRecordFormatCollectionUid;

	TUint iHeapSpaceRequired;
	};


/**
@publishedAll

Contains the parameters used to select mmf plugins from the ECOM registry.

@released
@since 7.0s
*/
class CMMFPluginSelectionParameters : public CBase
	{
public:
/**
Describes the type of preferred supplier match to be performed on the plugins return from
the ECOM registry.
*/
enum TPreferredSupplierMatchType
	{
	/**No preferred supplier match will be performed.*/
	ENoPreferredSupplierMatch,
	/**Plugins from all suppliers will be returned, but those from the preferred supplier will be first in the list.*/
	EPreferredSupplierPluginsFirstInList,
	/**Only plugins from the preferred supplier will be returned.*/
	EOnlyPreferredSupplierPluginsReturned
	};
/**
Describes the type of media id match to be performed on the plugins return from
the ECOM registry.
*/
enum TMediaIdMatchType
	{
	/**No media id match will be performed.*/
	ENoMediaIdMatch,
	/**All plugins that support the media id supplied will be returned, even those that support
	   other media ids.  For example, if an audio plugin is requested, plugins that support
	   audio and video will also be returned.*/
	EAllowOtherMediaIds,
	/**Only plugins that support the exact media ids supplied will be returned.  For example, if an
	   audio plugin is requested, plugins that only support audio will be returned 
	   (ie no audio/video plugins).*/
	EAllowOnlySuppliedMediaIds
	};

public:
/**
		Destructor.  Resets and destroys all member data.

		@since 7.0s
*/
	virtual ~CMMFPluginSelectionParameters();


/**
Sets the preferred supplier of the plugin.

@param	"aPreferredSupplier"	"The preferred supplier of the plugin."
@param	"aMatchType"			"The type of match to be made."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetPreferredSupplierL(const TDesC& aPreferredSupplier, TPreferredSupplierMatchType aMatchType);

/**
Sets the media ids that must be supported by the plugin, for example audio, video etc.

@param	"aMediaIds"	 "An array of the media ids that the selected plugins must support."
@param  "aMatchType" "The type of match to be made."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetMediaIdsL(const RArray<TUid>& aMediaIds, TMediaIdMatchType aMatchType);

/**
Returns the preferred supplier.  If no preferred supplier has been set, a blank 
string will be returned.

@return "The preferred supplier."
@since 7.0s
*/
	IMPORT_C const TDesC& PreferredSupplier() const;

/**
Returns the type of preferred supplier match to perform.

@return "The preferred supplier match type."
@since 7.0s
*/
	IMPORT_C TPreferredSupplierMatchType PreferredSupplierMatchType() const;

/**
Returns the list of media ids that must be supported by the plugin.
@return "The list of media ids."
@since	7.0s
*/
	IMPORT_C const RArray<TUid>& MediaIds() const;

/**
Returns the type of preferred supplier match to perform.

@return "The preferred supplier match type."
@since 7.0s
*/
	IMPORT_C TMediaIdMatchType MediaIdMatchType() const;

/**
Returns the uid of the interface to be searched for plugin matches.

@return "The interface uid."
@since 7.0s
*/
	IMPORT_C TUid InterfaceUid() const;

protected:
	CMMFPluginSelectionParameters(TUid aPluginInterfaceUid);

	TBool CheckMediaIdSupportL(const CMMFPluginImplementationInformation& aPlugin) const;
private:
	TUid iPluginInterfaceUid;
	HBufC* iPreferredSupplier;
	TPreferredSupplierMatchType iPreferredSupplierMatchType;
	RArray<TUid> iMediaIds;
	TMediaIdMatchType iMediaIdMatchType;
	};







/**
@publishedAll

Defines the format support required.

On construction, the selection parameters are blank, causing all plugins to be returned.

@released
@since 7.0s
*/
class CMMFFormatSelectionParameters : public CBase
	{
public:
/**
Describes the type of match to be performed.
The match types are mutually exclusive.
*/
enum TMatchDataType 
	{
	/**All plugins will be selected. This is the default option.*/
	EMatchAny,
	/**The match will be based on a file extension.*/
	EMatchFileExtension,
	/**The match will be based on a mime type.*/
	EMatchMimeType,
	/**The match will be based on a header data.*/
	EMatchHeaderData
	};

public:
	IMPORT_C static CMMFFormatSelectionParameters* NewL();
	IMPORT_C static CMMFFormatSelectionParameters* NewLC();

	static CMMFFormatSelectionParameters* NewL(const CMMFFormatSelectionParameters& aParams);
/**
Sets this object to match to a file extension.

aFileName can be a full filename or just an extension.  If there is no dot in the filename
and it is 5 characters or less in length then it is assumed to be an extension.  If the first
character of the filename is a dot, it assumed to be an extension.  Otherwise, the filename
is parsed using TParse to reveal the extension.

Once the extension has been extracted, it is converted from unicode to utf8 and copied into
iMatchData.

@param	"aFileName"	"The file name to be matched.  Must include the extension."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetMatchToFileNameL(const TDesC& aFileName);
	
/**
Sets this object to match to a file extension specified by a URI


Once the extension has been extracted, it is converted from unicode to utf8 and copied into
iMatchData.

@param	"aUri"	"The URI containing the file name to be matched.  Must include the extension."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetMatchToUriL(const TDesC& aUri);


/**
Sets this object to match to a mime type.

@param	"aMimeType"	"The mime type to match."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetMatchToMimeTypeL(const TDesC8& aMimeType);

/**
Sets this object to match to a pattern in header data.

@param	"aHeaderData"	"The header of the file in question.  This header data will be matched
						against the match patterns provided by the plugins."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetMatchToHeaderDataL(const TDesC8& aHeaderData);

/**
Returns the data used to perform the plugin match.

@return "The match data."
@since 7.0s
*/
	IMPORT_C const TDesC8& MatchData() const;

/**
Returns the type of the data used to perform the plugin match.

@return "The match data type."
@since 7.0s
*/
	IMPORT_C TMatchDataType MatchDataType() const;

/** Destructor */
	virtual ~CMMFFormatSelectionParameters();
protected:
	CMMFFormatSelectionParameters();
	void ConstructL(const CMMFFormatSelectionParameters& aParams);
private:
	HBufC8* iMatchData;
	TMatchDataType iMatchDataType;
	};



/**
@publishedAll

Contains the parameters used to select controller plugins from the ECOM registry.

@released
@since 7.0s
*/
class CMMFControllerPluginSelectionParameters : public CMMFPluginSelectionParameters
	{
public:
/**
Construct a new controller selection parameters object.

@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	IMPORT_C static CMMFControllerPluginSelectionParameters* NewL();

/**
Construct a new controller selection parameters object.

@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created.  Note that the new object will be left on the cleanupStack."
@since 7.0s
*/
	IMPORT_C static CMMFControllerPluginSelectionParameters* NewLC();

/**
Set the play format support required.

Note that the play formats supported by the controller plugins will only be retrieved if
this method is called.  To get all the play formats supported by the system, call this
with a 'blank' CMMFFormatSelectionParameters object.

@param	"aRequiredSupport"	"The play format support required."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetRequiredPlayFormatSupportL(const CMMFFormatSelectionParameters& aRequiredSupport);

/**
Set the record format support required.

Note that the record formats supported by the controller plugins will only be retrieved if
this method is called.  To get all the record formats supported by the system, call this
with a 'blank' CMMFFormatSelectionParameters object.

@param	"aRequiredSupport"	"The record format support required."
@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	IMPORT_C void SetRequiredRecordFormatSupportL(const CMMFFormatSelectionParameters& aRequiredSupport);


/**
Retrieves all controller plugins that support the requirements of the caller.

@param	"aImplementations"	"After this method returns, this array will contain all the 
							controller plugins that support the caller's requirements.
							Note: The array will be emptied by this method."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C virtual void ListImplementationsL(RMMFControllerImplInfoArray& aImplementations) const;

/** Destructor */
	virtual ~CMMFControllerPluginSelectionParameters();
protected:
	CMMFControllerPluginSelectionParameters();
	void MatchImplementationToSelectParamsL(RMMFControllerImplInfoArray& aImplementations, const CMMFControllerImplementationInformation& aPlugin, TInt& aArrayPos) const;
	TInt CheckPreferredSupplierL(RMMFControllerImplInfoArray& aImplementations, const CMMFControllerImplementationInformation& aPlugin) const;
	TBool CheckFormatSupportL(CMMFFormatSelectionParameters* aSelectParams, const RMMFFormatImplInfoArray& aFormats) const;
protected:
	CMMFFormatSelectionParameters* iRequiredPlayFormatSupport;
	CMMFFormatSelectionParameters* iRequiredRecordFormatSupport;
	};

/**
 * @internalAll
 *
 * MMF utility class used by MMF recognizer
 * Maintains an array of CMMFControllerImplementationInformation objects
 * so that data headers can be speedily matched against.
 * Updates the array when notified by ECOM of a change to the global
 * interface implementation registration data.
 */
class CMmfRecognizerUtil : public CBase
	{
public:
	enum TMatchLevel
		{
		EMatchNone, //no match
		EMatchData, //data match only
		EMatchName  //suffix and data match
		};
public:
	IMPORT_C static void GetMimeTypesL(CDesC8Array* aMimeTypes);

	IMPORT_C static CMmfRecognizerUtil* CMmfRecognizerUtil::NewL();
	~CMmfRecognizerUtil();
	IMPORT_C TMatchLevel GetMimeTypeL(const TDesC& aFileName, const TDesC8& aImageData, TDes8& aMimeType);

private:
	CMmfRecognizerUtil();
	void ConstructL();

private:
	class CBody;
	CBody* iBody;
	};





/**
@publishedAll

Abstract class used to contain the parameters used to select format plugins from the ECOM registry.
Note: the classes CMMFFormatEncodePluginSelectionParamters and CMMFFormatDecodePluginSelectionParameters
should be used to list and select format plugin implementations.

@released
@since 7.0s
*/
class CMMFFormatPluginSelectionParameters : public CMMFPluginSelectionParameters
	{
public:

/**
Retrieves all format plugins that support the requirements of the caller.

@param	"aImplementations"	"After this method returns, this array will contain all the 
							format plugins that support the caller's requirements.
							Note: The array will be emptied by this method."
@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	IMPORT_C void ListImplementationsL(RMMFFormatImplInfoArray& aImplementations) const;

/**
Set the format support required.

@param	"aRequiredSupport"	"The format support required."
@leave	"This method may leave with one of the system-wide error codes."
@since 7.0s
*/
	IMPORT_C void SetRequiredFormatSupportL(const CMMFFormatSelectionParameters& aRequiredSupport);

/** Destructor. */
	virtual ~CMMFFormatPluginSelectionParameters();
protected:
	CMMFFormatPluginSelectionParameters(TUid aInterfaceUid);

	void MatchImplementationToSelectParamsL(RMMFFormatImplInfoArray& aImplementations, const CMMFFormatImplementationInformation& aPlugin, TInt& aArrayPos) const;
	TInt CheckPreferredSupplierL(RMMFFormatImplInfoArray& aImplementations, const CMMFFormatImplementationInformation& aPlugin) const;
	TBool CheckFormatSupportL(const CMMFFormatImplementationInformation& aPlugin) const;
protected:
	CMMFFormatSelectionParameters* iRequiredFormatSupport;
	};

/**
@publishedAll

Class used to list and select plugins implementing the CMMFFormatEncode interface.

@released
@since 7.0s
*/
class CMMFFormatEncodePluginSelectionParameters : public CMMFFormatPluginSelectionParameters
	{
public:
/**
Construct a new format encode selection parameters object.

@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	IMPORT_C static CMMFFormatEncodePluginSelectionParameters* NewL();

/**
Construct a new format encode selection parameters object.

@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created.  Note that the new object will be left on the cleanupStack."
@since 7.0s
*/
	IMPORT_C static CMMFFormatEncodePluginSelectionParameters* NewLC();
protected:
	CMMFFormatEncodePluginSelectionParameters();
	};


/**
@publishedAll

Class used to list and select plugins implementing the CMMFFormatDecode interface.

@released
@since 7.0s
*/
class CMMFFormatDecodePluginSelectionParameters : public CMMFFormatPluginSelectionParameters
	{
public:
/**
Construct a new format decode selection parameters object.

@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created."
@since 7.0s
*/
	IMPORT_C static CMMFFormatDecodePluginSelectionParameters* NewL();

/**
Construct a new format decode selection parameters object.

@leave	"This method may leave with one of the system-wide error codes."
@return "The new object created.  Note that the new object will be left on the cleanupStack."
@since 7.0s
*/
	IMPORT_C static CMMFFormatDecodePluginSelectionParameters* NewLC();
protected:
	CMMFFormatDecodePluginSelectionParameters();
	};



/** 
 * @publishedAll
 * @released
 *
 * Template class CleanupResetAndDestroy to clean up the array
 * of implementation information from the cleanup stack.
 */

template <class T>
class CleanupResetAndDestroy
	{
public:
	inline static void PushL(T& aRef);
private:
	static void ResetAndDestroy(TAny *aPtr);
	};
template <class T>
inline void CleanupResetAndDestroyPushL(T& aRef);
template <class T>
inline void CleanupResetAndDestroy<T>::PushL(T& aRef)
	{CleanupStack::PushL(TCleanupItem(&ResetAndDestroy,&aRef));}
template <class T>
void CleanupResetAndDestroy<T>::ResetAndDestroy(TAny *aPtr)
	{(STATIC_CAST(T*,aPtr))->ResetAndDestroy();}
template <class T>
inline void CleanupResetAndDestroyPushL(T& aRef)
	{CleanupResetAndDestroy<T>::PushL(aRef);}


#endif
