/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Yngve Pettersen
**
*/


#ifndef _URL_ENUM_H_
#define _URL_ENUM_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
/* The defines in vfunc.h should be moved into configure.in */
#ifdef _QT_
# include "core/qt/vfunc.h"
#endif // _QT_
#endif                                                                          
#ifdef _NO_PCH_
#include "core/compiler.h"
#endif

// NOTE!! CHECK THAT YOU DO NOT EXCEED VALUE 63 WHEN EXPANDING THIS SET
// IF YOU DO INCREASE THE NUMBER OF BITS USED IN URL_Rep::rep_info_st::content_type

enum URLContentType
{
	URL_HTML_CONTENT = 0,
	URL_XML_CONTENT,
	URL_WML_CONTENT,
	URL_WBMP_CONTENT,
	URL_OPF_CONTENT,
	URL_CSR_CONTENT,
	URL_TEXT_CONTENT,
	URL_GIF_CONTENT,
	URL_JPG_CONTENT,
	URL_TV_CONTENT,
	URL_XBM_CONTENT,
	URL_BMP_CONTENT,
	URL_CPR_CONTENT,
	URL_WAV_CONTENT,
	URL_MIDI_CONTENT,
	URL_AVI_CONTENT,
	URL_NEWS_LST_CONTENT,
	URL_NEWS_GRP_CONTENT,
	URL_NEWS_ART_CONTENT,
	URL_DIR_CONTENT,
	URL_MPG_CONTENT,
	URL_CNX_CONTENT,
	URL_X_MIXED_REPLACE_CONTENT,
	URL_X_X509_USER_CERT,
	URL_X_X509_CA_CERT,
	URL_X_PEM_FILE,
	URL_NEWS_ATTACHMENT,
	URL_MIME_CONTENT,
	URL_X_JAVASCRIPT,
	URL_PNG_CONTENT,
	URL_POSTSEC_CONTENT,
	URL_CSS_CONTENT,
	URL_PAC_CONTENT,
	URL_PFX_CONTENT,
	URL_UNKNOWN_CONTENT,
	URL_UNDETERMINED_CONTENT
#ifdef _ISHORTCUT_SUPPORT
	,URL_ISHORTCUT_CONTENT
#endif//_ISHORTCUT_SUPPORT
#if defined(MIDLET_SUPPORT)
	,URL_JAD_CONTENT
#endif
#ifdef ICO_SUPPORT
	,URL_ICO_CONTENT
#endif // ICO_SUPPORT
#ifdef EPOC
	,URL_EPOC_CONTENT
#endif
};

enum URLStatus
{
	URL_EMPTY = 0,
	URL_UNLOADED,
	URL_LOADED,
	URL_LOADING,
	URL_LOADING_ABORTED,
	URL_LOADING_FAILURE,
	URL_LOADING_WAITING,
	URL_LOADING_FROM_CACHE
};

enum HTTP_Authinfo_Status {
	AuthInfo_Failed, 
	AuthInfo_Succeded, 
	Authinfo_Not_Finished
};

enum CommState {
    COMM_REQUEST_FAILED = 0,
    COMM_LOADING,
    COMM_WAITING,
    COMM_REQUEST_FINISHED,
    COMM_REQUEST_WAITING,
    COMM_WAITING_FOR_SYNC_DNS,
    COMM_LISTENING,
    COMM_CHANGED_HOSTNAME
};

enum URLCacheType
{
	URL_CACHE_NO = 0,
	URL_CACHE_MEMORY,
	URL_CACHE_DISK,
	URL_CACHE_TEMP,
	URL_CACHE_USERFILE
};

#define SECURITY_STATE_NONE 0		// Notice, if you are looking for the values possible for
#define SECURITY_STATE_LOW 1		// security state, ehm, it looks like you have to add 1,
#define SECURITY_STATE_HALF 2		// then divide by 2, to get these values. <JB>
#define SECURITY_STATE_FULL 3
#define SECURITY_STATE_UNKNOWN 10

#define AuthScheme			BYTE

#define AUTH_USER_CANCELLED		0
#define AUTH_NO_METH			1
#define AUTH_NO_PROXY_METH		2
#define AUTH_NO_DOMAIN_MATCH	3
#define AUTH_MEMORY_FAILURE		4
#define AUTH_GENERAL_FAILURE	5

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!
// !!                                                                            !!
// !! DO NOT USE IFDEFS IN THIS ENUMERATOR                                       !!
// !!                                                                            !!
// !! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!!! NOTE !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
enum URLType
{
	URL_HTTP = 0,				// 0
	URL_FTP,					// 1
	URL_Gopher,					// 2
	URL_WAIS,					// 3
	URL_FILE,					// 4
	URL_NEWS,					// 5
	URL_TELNET,					// 6
	URL_MAILTO,					// 7
	URL_NEWSPOST,				// 8
	URL_INTERNAL,				// 9
	URL_HTTPS,					// 10
	URL_OPERA,					// 11
	URL_JAVASCRIPT,				// 12
	URL_SNEWS,					// 13
	URL_SNEWSPOST,				// 14
	URL_NEWSATTACHMENT,			// 15
	URL_SNEWSATTACHMENT,		// 16
	URL_ATTACHMENT,				// 17
	URL_EMAIL,					// 18
	URL_CONTENT_ID,				// 19
	URL_TN3270,					// 20
	URL_NOKIA,					// 21
	URL_SOURCE,					// 22
	URL_CLIENT,					// 23
	URL_NNTP,					// 24 // alternative protocol // translated to URL_NEWS
	URL_NNTPS,					// 25 // alternative protocol // translated to URL_SNEWS
	URL_SHARE,					// 26
	URL_GHTTP,                  // 27 // alternative protocol // translated to URL_HTTP
	URL_TV,                     // 28
    URL_EDITED,                 // 29
	URL_ERROR,					// 30
	URL_DVB,					// 31 // perhaps URL_REMOTE_FILE is more apropriate, but someone wanted it this way...
	URL_TEL,					//32 
	URL_MAIL,					//33 
	// APPEND NEW TYPES HERE AND IN CORRESPONDING PLACE IN URL_pref_typenames table
	// ALSO ADD TEXTSTRINGS TO protocol_selentry table
	// !!!! NOTE !!!!	DO NOT USE IFDEFS IN THIS ENUMERATOR

	URL_UNKNOWN,				// 34(32)
	URL_NULL_TYPE				// 35(33)

};

enum COOKIE_MODES
{
	COOKIE_NONE = 0,
	COOKIE_NO_THIRD_PARTY = 1, // also domain
	COOKIE_ONLY_SERVER,
	COOKIE_ALL,
	COOKIE_ONLY_SELECTED_SERVERS_N3P ,// No third party
	COOKIE_ONLY_SELECTED_SERVERS_OS , // Only cookies for the server
	COOKIE_ONLY_SELECTED_SERVERS_ALL, // From any server
	COOKIE_WARN_THIRD_PARTY,			// All non-third-party, user decides third party
	COOKIE_ONLY_SELECTED_SERVERS_W3P,   // All non-third-party selected servers,  user decides third party selected server
	// Used by filters
	COOKIE_DEFAULT,
	COOKIE_NONE_FROM_SERVER,
	COOKIE_NO_THIRD_PARTY_FROM_SERVER, 
	COOKIE_ACCEPT_THIRD_PARTY, // domain
	COOKIE_THIRD_PARTY_ONLY_SERVER // server_only
};

enum COOKIE_ILLPATH_MODE
{
	COOKIE_ILLPATH_DEFAULT,
	COOKIE_ILLPATH_REFUSE,
	COOKIE_ILLPATH_ACCEPT
};

/** Represents the different states that user name and password
  * criteria information is shown in URL strings as displayed to
  * the application or the user.
  * - This should be moved to the url_enums.h file
  */
enum Password_Status {
	PASSWORD_SHOW,		/** Include complete username:password */
	PASSWORD_HIDDEN,	/** Do not display password, but replace it by "*****" */
	PASSWORD_ONLYUSER,	/** Do not display any password, but show username */
	PASSWORD_NOTHING,	/** Remove all password information, also username */
	PASSWORD_HIDDEN_UNESCAPE_URL, /** Do not display password, but replace it by "*****", Also remove Escaped characters */
	PASSWORD_LINKID,	/** Same as PASSWORD_SHOW, but for unique URL's (POST forms) prepend a unique identifier **/
	PASSWORD_SHOW_VERBATIM /** Same as PASSWORD_SHOW, but do not un- or re-escape anything, used for relative URLs **/
};


#define MIME_NOT_CLEANSPACE 1
#define MIME_IN_COMMENT 2

enum Mime_EncodeTypes {
	GEN_BASE64,
	GEN_BASE64_ONELINE,
	MAIL_BASE64,
	MAIL_QP,
	MAIL_QP_E,
	MAIL_7BIT,
	MAIL_8BIT,
	MAIL_BINARY,
	HTTP_ENCODING,
	HTTP_ENCODING_BINARY,
	UUENCODE,
	BINHEX,
	NO_ENCODING
};

enum MIME_Encode_Error {	// Change to extend OpStatus... (no)
	MIME_NO_ERROR,
	MIME_LINE_TOO_LONG,
	MIME_7BIT_FAIL,
	MIME_8BIT_FAIL,
	MIME_FAILURE
};

/// User-Agent type
enum UA_BaseStringId
{
	UA_NotOverridden = 0,
	UA_Opera,
	UA_Mozilla,
	/*UA_Mozilla_Compatible,*/
	UA_MSIE,
	UA_MozillaOnly,
	UA_BEAR
};

enum EnteredByUser {
	NotEnteredByUser,
	WasEnteredByUser
};

enum TrustedNeverFlushLevel {
	NeverFlush_Undecided,
	NeverFlush_Untrusted,
	NeverFlush_Trusted
};


#define MAX_URL_LEN			4096

#define MAKE_INLINE_PARM_2(stat, extra) ((WORD)(((BYTE)(extra))|(((WORD)((BYTE)(stat)))<<8)))
#define URL_INLINE_NEED_PLUGIN	0x01

#define URL_STAT_PARM(parm) HIBYTE(parm)
#define URL_EXTRA_PARM(parm) LOBYTE(parm)

#define DEFAULT_FILE_LOAD_BUF_SIZE	(4096*4)

#endif

