// caftypes.h
// Copyright (c) 2003 - 2004 Symbian Software Ltd. All rights reserved.

/** 
@file

This file contains enumerations and constants used throughout the 
content access framework

@publishedPartner
@released
*/

#ifndef __CAF_TYPES_H__
#define __CAF_TYPES_H__

#include <e32std.h>

namespace ContentAccess
	{
#ifndef REMOVE_CAF1
	/** @deprecated */
	enum TQosAttribute
		{
		EQosBufferSize   = 0,  ///< Size of read buffer suggested by client
		EQosAttrTop // Must always be last sequential entry
		};

	/**
	 Defines an internal set of 'standard' MIME header fields. These allow an agent
	 to quickly read the value of a field when importing files

	 @deprecated 
	 */
	enum TMimeFields
		{
		EContentType				= 0,	///< Content-Type :
		EContentLength				= 1,	///< Content-Length :
		EContentId					= 2,    ///< Content-Id:
		EContentTransferEncoding	= 3,    ///< Content-Transfer-Encoding:
		EBoundary					= 4,    ///< Boundary:
		EMimeMax				    		///< indicates the end of this enumeration
		}; 
#endif // REMOVE_CAF1
	
	/** Defines the share modes available when opening content for consumption. These
	modes have no effect unless the content is a file stored on the device.
	*/
	enum TContentShareMode
		{
		EContentShareReadOnly      = 0,  ///< Client will only read and expects others will only read.
		EContentShareReadWrite     = 1,  ///< Client expects to read and write and others will read and write
		EContentShareExclusive     = 2   ///< Client will have exclusive access to the file. This can only be used for unprotected content
		};
		
	/**
	 * Set of valid reader intents when opening content.
	 */
	enum TIntent
		{
		EPeek		= 0,	///< Reader intends to peek at content.
		EPlay		= 1,	///< Reader intends to play content.
		EView		= 2,	///< Reader intends to view content.
		EExecute	= 3,	///< Reader intends to execute content.
		EPrint		= 4,	///< Reader intends to print content.
		EPause		= 5,	///< Reader pauses play operation
		EContinue	= 6,	///< Reader continues play operation after a pause operation
		EStop		= 7,	///< Reader stops play operation.
		EUnknown    = 8,    ///< Reader is uncertain of how the content will be used. Permits free access to unprotected data but prevents access to protected content
		EInstall	= 9		///< Reader intends to install content.
		};


	/**
	 * Defines the types of output file produced when importing files
	 * into the Content Access Famework using CImportFile
	 */
	enum TOutputType
		{
		EContent					= 0,	///< Content file produced
		EReceipt					= 1     ///< Receipt for rights produced
		}; 

	/**
	 The agent status codes reported when importing a file with the supplier API
	 */
	enum TImportStatus 
		{
		EInProgress,				///< The import operation is proceeding with no error
		EWaitingForNewOutputFile,	///< The agent is waiting for the client application to provide a new output file by calling ContinueWithNewOutputFile()
		EComplete,					///< The import operation is complete
		EFailed,					///< The import was aborted by the agent 
		EUnsupportedMedia			///< The mime-type of the content is not supported on this device
		};

	/** 
	The list of generic content object attributes. Each of these attributes has a 
	value that is either ETrue or EFalse unless otherwise specified

	@li ETrue If an attribute is true
	@li EFalse If the attribute is false
	*/
	enum TAttribute
			{
			EIsProtected				= 0, ///< Content object is protected
			EIsForwardable				= 1, ///< Content object can be forwarded to another device or copied to removable media
			EIsModifyable				= 2, ///< The content can be modified
			EIsCopyable					= 3, ///< The content object can be duplicated in internal storage
			ECanPlay					= 4, ///< Rights exist allowing the content to be played
			ECanPrint					= 5, ///< Rights exist allowing the content to be printed
			ECanExecute					= 6, ///< Rights exist allowing the content to be executed
			ECanView					= 7, ///< Rights exist allowing the content to be viewed on screen
			ERightsNone					= 8, ///< No rights exist for the content object
			ERightsPending				= 9, ///< Rights are expected to arrive soon
			ERightsHaveExpired			= 10, ///< Rights were were present but have since expired or been consumed
			EPreviewAvailable			= 11, ///< A preview URI is available
			EContentCDataInUse			= 12, ///< Set if the content is currently being used by another CData session
			ECanRewind					= 13, ///< Media can be rewound without decrementing rights
			ECopyPaste					= 14, ///< can make copies via the clipboard
			ERightsConsumable			= 15, ///< Rights are consumable. The are decremented whenever content is accessed (ie. play counts).
			ERightsStateless			= 16, ///< Rights are stateless and the content can be used repeatedly until a condition expires (ie. expiry date)
			ECanMove					= 17, ///< Content can be moved
			ECanRename					= 18, ///< Content can be renamed
			ECanAutomaticConsume		= 19, ///< Rights can be consumed automatically when the content object is used for say wallpaper
			EAgentSpecificAttributeBase	= 32768	///< Base index the agents should use when implementing new agent specific attributes
			};


		
		/**  The list of generic string attributes. Each of these attributes 
		has a value that is returned to the client as a string.
		*/
		enum TStringAttribute
			{
			EDescription				= 0,	///< Description of the embedded object
			EMimeType					= 1,    ///< Mime type of the content object
			ETitle						= 2,    ///< Title of the object
			EAuthor						= 3,	///< Author of the object
			EIconURI					= 4,	///< Location of the icon for this content
			EPreviewURI					= 5,	///< Location of a preview of the content
			EContentURI					= 6,	///< URI where this content can be found
			EContentID					= 7,	///< Unique CID for this content
			EInfoURL					= 8,	///< Location of further information about this content
			EPendingRightsETA			= 9,	///< Expected number of seconds before the rights arrive
			EAgentSpecificStringAttributeBase	= 32768 ///< Base index the agents should use when implementing new string attributes
			};

		/** 
		Events relating to DRM objects, powers of 2 so they can be OR'd
		*/
		enum TEventMask
			{
			ERightsAvailable = 1,			///< Rights have arrived for the content object
			ERightsExpired   = 2			///< Rights have expired or have been exhausted
			};
		/** 
		The type of object inside a DRM file
		*/
		enum TEmbeddedType 
			{
			EContainerObject		= 0,	///< A container object
			EContentObject			= 1,	///< A content object
			EAgentSpecificObject	= 2	    ///< An agent specific object
			};

		/** Type of information to display
		 */
		enum TDisplayInfo
			{	
			EFileProperties			= 0,	///< Display file name, last modified date etc
			EFileAndRights			= 1,	///< Display file information and DRM rights information
			ERights					= 2		///< Display DRM rights information only
			};

		/** The type of rights object

		A rights object can be consumable and 
		stateless so these can be OR'd together to form a bit mask
		*/
		enum TRightsTypeMask
			{	
			ERightsTypeConsumable		= 1,    ///< Rights are consumable. The are decremented whenever content is accessed (ie. play counts).
			ERightsTypeStateless		= 2		///< Rights are stateless and the content can be used repeatedly until a condition expires (ie. expiry date)
			};
		
		/** State of a rights object */
		enum TRightsStatus
			{	
			ERightsStatusNone				= 0,    ///< Rights do not exist
			ERightsStatusValid				= 1,	///< Rights are valid, ready to use
			ERightsStatusExpired			= 2,	///< Rights have all expired
			ERightsStatusPending			= 3		///< Rights are expected soon
			};

	/** The Unique Id that identifies the default content object within any file
	*/
	_LIT(KDefaultContentObject,"DEFAULT");

	/** Defines the properties that an application can set in an agent. */
	enum TAgentProperty
		{
		EAgentPropertyBufferSize				= 0,	///< Set the buffer size used by the agent when reading content. This can be used to optimise performance.
		EAgentPropertyAgentUI					= 1,	///< Enable or disable the Agent's user interface for errors and confirmation requests. 0 = Disable Agent UI, 1 = Enable Agent UI
		EAgentPropertyMultipleSequence			= 2		///< Communicates to the agent that a series of operations are to be performed as part of one larger operation. eg. deleting multiple files, the value should be set back to zero when the sequence is finished.  0 = Not performing a multiple sequence, 1 = performing a multiple sequence.
		};

	/** Maximum length of a Uniqueid 
	*/
	const TInt KMaxCafUniqueId = 1024;
	
	/** Maximum length of a content object Name
	*/
	const TInt KMaxCafContentName = 1024;

	}

#endif // __CAF_H__

