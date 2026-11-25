/*
* ==============================================================================
*  Name        : laffonts.h
*  Part of     : CUIKLAF
*  Interface   : LAF API
*  Description : Constants for LAF fonts
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


#ifndef LAFFONTS_H
#define LAFFONTS_H

// INCLUDES
#include <e32std.h>
#include <gulfont.h>

// CONSTANTS


// deprecated - kept for source compatibility
/** @deprecated */
const TInt  KLafUidSystemfontTerm8normal=           0x10004B22;
/** @deprecated */
const TInt  KLafUidSystemfontTerm15zoomed=          0x10004B23;
/** @deprecated */
const TInt  KLafUidSystemfont16bold=                0x10004B24;
/** @deprecated */
const TInt  KLafUidSystemfont18normal=              0x10004B25;
/** @deprecated */
const TInt  KLafUidSystemfont18bold=                0x10004B26;
/** @deprecated */
const TInt  KLafUidSystemfont20light=               0x10004B27;
/** @deprecated */
const TInt  KLafUidSystemfont20normal=              0x10004B28;
/** @deprecated */
const TInt  KLafUidSystemfont20italic=              0x10004B29;
/** @deprecated */
const TInt  KLafUidSystemfont20bold=                0x10004B2A;
/** @deprecated */
const TInt  KLafUidSystemfont20bolditalic=          0x10004B2B;
/** @deprecated */
const TInt  KLafUidSystemfont22bold=                0x10004B2C;
/** @deprecated */
const TInt  KLafUidSystemfont24light=               0x10004B2D;
/** @deprecated */
const TInt  KLafUidSystemfont24normal=              0x10004B2E;
/** @deprecated */
const TInt  KLafUidSystemfont24bold=                0x10004B2F;
/** @deprecated */
const TInt  KLafUidSystemfont29light=               0x10004B30;
/** @deprecated */
const TInt  KLafUidSystemfont29normal=              0x10004B31;
/** @deprecated */
const TInt  KLafUidSystemfont29bold=                0x10004B32;
/** @deprecated */
const TInt  KLafUidSymbolfont20normal=              0x10004B33;
/** @deprecated */
const TInt  KLafUidSystemfont10normal=              0x10004B34;
// Expansion possible to allocated UID 0x10004B50

// apps must not get fonts via a System Font UID; instead they
// must use the CCknLogicalFont category
/** [what] */
#define KLafSystemFont1 0x101F806D
#define KLafSystemFont2 0x101F806E
#define KLafSystemFont3 0x101F806F
#define KLafSystemFont4 0x101F8070
#define KLafSystemFont5 0x101F8071
#define KLafSystemFont6 0x101F8072
#define KLafSystemFont7 0x101F8073
#define KLafSystemFont8 0x101F8074
#define KLafSystemFont9 0x101F8075
#define KLafSystemFont10 0x101F8076
#define KLafSystemFont11 0x101F8077
#define KLafSystemFont12 0x101F8078
#define KLafSystemFont13 0x101F8079
#define KLafSystemFont14 0x101F807A
#define KLafSystemFont15 0x101F807B
#define KLafSystemFont16 0x101FAC25
#define KLafSystemFont17 0x101FAC26
#define KLafSystemFont18 0x101FAC27
#define KLafSystemFont19 0x101FAC28
#define KLafSystemFont20 0x101FAC29
#define KLafSystemFont21 0x101FAC53
#define KLafSystemFont22 0x101FAC54
#define KLafSystemFont23 0x101FAC55
#define KLafSystemFont24 0x101FAC56
#define KLafSystemFont25 0x101FAC57
#define KLafSystemFont26 0x101FAC58
#define KLafSystemFont27 0x101FAC59


#endif  // LAFFONTS_H

// End of File
