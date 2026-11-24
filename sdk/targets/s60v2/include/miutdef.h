// MIUTDEF.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

//
// This header file defines the bit flags that may be used to instruct
// the CImMessageOperation class how to construct a new Email message
//

#if !defined (__MIUTDEF_H__)
#define __MIUTDEF_H__

/** Type for email creation flags used in the aMsvEmailTypeList parameter of CImEmailOperation 
functions.

@see KMsvEmailTypeListMHTMLMessage
@see KMsvEmailTypeListInvisibleMessage
@see KMsvEmailTypeListMessageInPreparation 
@publishedAll
@released
*/
typedef TUint TMsvEmailTypeList;

/** An MHTML type message. */
const TMsvEmailTypeList KMsvEmailTypeListMHTMLMessage				= 0x00000001;	// if not set Email is a "normal" (i.e. non-MHTML) Email message
/** An invisible message. */
const TMsvEmailTypeList KMsvEmailTypeListInvisibleMessage			= 0x00000002;	// if set, message stays invisible on completion
/** Message is in preparation. */
const TMsvEmailTypeList KMsvEmailTypeListMessageInPreparation		= 0x00000004;	// if set, message stays marked "In preparation" on completion

#endif //MIUTDEF.H

