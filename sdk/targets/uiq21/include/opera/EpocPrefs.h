/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis
*/

#ifndef __EPOCPREFS_H
#define __EPOCPREFS_H

#include "css_mode.h"
#include "cursor.h"
#include "htm_enum.h"
#include "pm_type.h"
#include "url_enum.h"

enum TObjectType
    {
    EObjectNone      =0x00,
    EObjectImage     =0x01,
    EObjectLink      =0x02,
    EObjectMailtoLink=0x04,
    EObjectInput     =0x08
    };

enum TSecurityLevel // Must match SECURITY_STATE_ values
    {
    ESecurityNone   =SECURITY_STATE_NONE,
    ESecurityLow    =SECURITY_STATE_LOW,
    ESecurityHalf   =SECURITY_STATE_HALF,
    ESecurityFull   =SECURITY_STATE_FULL,
    ESecurityUnknown=SECURITY_STATE_UNKNOWN
    };

enum TImageDisplayMode // Must match SHOWIMAGESTATE
	{
	ENoImages        =FIGS_OFF,
	ELoadedImagesOnly=FIGS_SHOW,
	EAllImages       =FIGS_ON
	};

enum TCSSDisplayMode // Must match CSSMODE
    {
	EUserMode    =CSS_NONE,
	EDocumentMode=CSS_FULL
    };

enum TJpegDCTMethod // Must match JPEGDCTMethod
	{
	EJpegInteger      =JINTEGER,
	EJpegFastInteger  =JFAST_INTEGER,
	EJpegFloatingPoint=JFLOAT
	};

enum TJpegDithering // Must match JPEGDithering
	{
	EJpegFloydSteinberg=FLOYD_STEINBERG,
	EJpegOrdered       =ORDERED,
	EJpegNone          =NONE
	};

enum TJpegPasses // Must match JPEGPasses
	{
	EJpegOne=ONE,
	EJpegTwo=TWO
	};

enum TOnStartupShow // Must match STARTUPTYPE
	{
	ESavedWindowsAndHistory =STARTUP_HISTORY,
	ESavedWindowsAndHomePage=STARTUP_WINHOMES,
	EHomePageOnly           =STARTUP_HOME
	};

enum TOperaAlternateBrowserType // Mapped onto UA_BaseStringId + version
	{
	EOpera,
	EMozilla50,
	EMozilla478,
	EMozilla30,
	EMSIE50
	};

enum TCookieAction
    {
	ECookieActionDefault,
	ECookieActionIgnore,
	ECookieActionSet,
	ECookieActionAskUser
    };

enum TCookieMode // Must match COOKIE_MODES
    {
	ECookieModeNone=COOKIE_NONE,
	ECookieModeNoThirdParty=COOKIE_NO_THIRD_PARTY,                      // also domain
	ECookieModeOnlyServer=COOKIE_ONLY_SERVER,
	ECookieModeAll=COOKIE_ALL,
	ECookieModeOnlySelectedServersN3P=COOKIE_ONLY_SELECTED_SERVERS_N3P, // No third party
	ECookieModeOnlySelectedServersOs=COOKIE_ONLY_SELECTED_SERVERS_OS,   // Only cookies for the server
	ECookieModeOnlySelectedServersAll=COOKIE_ONLY_SELECTED_SERVERS_ALL, // From any server
	ECookieModeWarnThirdParty=COOKIE_WARN_THIRD_PARTY,			        // All non-third-party, user decides third party
	ECookieModeOnlySelectedServersW3P=COOKIE_ONLY_SELECTED_SERVERS_W3P, // All non-third-party selected servers,  user decides third party selected server
    };

enum TAskCookieAction
    {
    EAskCookieAcceptAndUpdates,
    EAskCookieAcceptShowUpdates,
    EAskCookieAcceptButDiscard,
    EAskCookieAcceptButSave,
    EAskCookieAcceptAllFromServer,
    EAskCookieRefuseAllFromServer,
    EAskCookieAcceptAllFromDomain,
    EAskCookieRefuseAllFromDomain,
    EAskCookieAcceptAll3PFromServer,
    EAskCookieRefuseAll3PFromServer,
    EAskCookieAcceptAll3PFromDomain,
    EAskCookieRefuseAll3PFromDomain
    };

enum TScrollingMode // Must match SCROLLING_ values
    {
    EScrollingNone=SCROLLING_NO,
    EScrollingFull=SCROLLING_YES,
    EScrollingAutomatic=SCROLLING_AUTO
    };

enum TCursorType // Must match CursorType values
    {
    ECursorTypeDefault=DEFAULT_ARROW,
    ECursorTypeLink=CUR_POINTER,
    ECursorTypeWait=WAIT,
    ECursorTypeHorizontalResize=VERT_SPLITTER,
    ECursorTypeVerticalResize=HOR_SPLITTER
    };

typedef TInt TUnknownDataAction;
enum
	{
	EActionNone,
	EActionSave,
	EActionSaveAndNotify,
    EActionValueMask=0xFF,
    EActionReadOnly=0x100
	};

#endif /* __EPOCPREFS_H */
