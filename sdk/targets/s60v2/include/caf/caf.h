// caf.h
// Copyright (C) 2003 Symbian Software Ltd.  All rights reserved.
//

/** 
This contains constant definitions required by clients accessing the 
Content Access Framework.

@publishedPartner
@prototype
*/

#ifndef __CAF_H__
#define __CAF_H__

#include <e32std.h>

/** Agent does not support the requested capability. */
const TInt KErrCANotSupported  =(-17450);

/** 
 * Rights evaluation failed for the supplied intent. This implies that
 * rights were available, but their evaluation, in the context of
 * supplied <i>intent</i>, failed.
 */
const TInt KErrCANoPermission  =(-17451); 

/** 
 * No rights were available for evaluation. A number of causes may
 * generate this error: Perhaps the rights were removed or lost
 * during a separate delivery
 */
const TInt KErrCANoRights      =(-17452); 

/**
 * The Agent required is not present. This may occur if content
 * 'belongs' to an agent that is no longer available on the 
 * device. 
 */
const TInt KErrCANoAgent       =(-17453);

/** Values specified are out of range. */
const TInt KErrCAOutOfRange    =(-17454);

/** 
 * The rights were not available but are 'expected'. Will only be
 * returned if the agent supports this capability. 
 */
const TInt KErrCAPendingRights =(-17455);

/**
 * A request to get the content size failed because the agent was unable
 * to determine it. This error may occur on circumstances where, say, the
 * content is streamed over HTTP.
 */
const TInt KErrCASizeNotDetermined = (-17456);

/** More than one F32 agent found */
const TInt KErrCAF32AgentAlreadyFound  =(-17457);


namespace ContentAccess
	{
	/** Defines the valid attributes used for some agent operations. */
	enum TQosAttribute
		{
		/** */
		EQosBufferSize   = 0,
		/** */
		EQosAttrTop // Must always be last sequential entry
		};

	/** 
	 * Defines the share modes available when opening content for consumption.
	 * These modes have no effect unless the content is a file stored on the device.
	 */
	enum TContentShareMode
		{
		EContentShareReadOnly      = 0,  ///< Client will only read and expects others will only read.
		EContentShareReadWrite     = 1,  ///< Client expects to read and write and others will read and write
		EContentShareExclusive     = 2   ///< Client will have exclusive access to the file.
		};
		
		/**
	 * This defines the set of valid reader intents when opening
	 * content.
	 */
	enum TIntent
		{
		EPeek		= 0,	///< Reader intends to peek at content.
		EPlay		= 1,	///< Reader intends to play content.
		EView		= 2,	///< Reader intends to view content.
		EExecute	= 3,	///< Reader intends to execute content.
		EPrint		= 4		///< Reader intends to print content.
		};

	/** 
	 * Defines the generic conditions attributable to content (DRM related
	 * or otherwise. This attribute-space is Symbian-owned.
	 */
	enum TAttribute
		{
		EIsProtected   = 0, // Set = protected
		EIsForwardable = 1,
		EIsModifyable  = 2,
		EIsCopyable    = 3,
		ECanPlay       = 4, // OMA
		ECanPrint      = 5, // OMA
		ECanExecute    = 6, // OMA
		ECanView       = 7, // OMA
		ERightsNone    = 8, // Rights, Set = no rights
		ERightsPending = 9, // Rights, Set = expected soon
		
		EAttrTop			// Must always be last sequential entry
		}; 

	/**
	 * Defines the types of output file produced when importing files
	 * into the Content Access Famework
	 */
	enum TOutputType
		{
		EContent					= 0,	///< Content file produced
		EReceipt					= 1     ///< Receipt for rights produced
		}; 

	/**
	 * Defines an internal set of 'standard' MIME header fields. These allow an agent
	 * to quickly read the value of a field when importing files
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
	}

#endif // __CAF_H__
