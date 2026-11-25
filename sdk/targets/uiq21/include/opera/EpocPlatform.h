/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis
*/

#ifndef __EPOCPLATFORM_H
#define __EPOCPLATFORM_H

#if defined(__SYMBIAN32__) && !defined(EPOC)
#define EPOC
#endif

#if defined(__PSISOFT32__) && !defined(ER5)
#define ER5
#endif

#ifdef ER5
//#define SetRect SetRectL
//#define SetSize SetSizeL
#define SetExtent SetExtentL
#define SizeChanged SizeChangedL
#define TGulAlignmentValue TCoeAlignmentValue
#define EGulAdjLeft ECoeAdjLeft
#define EGulAdjRight ECoeAdjRight
#define EGulAdjTop ECoeAdjTop
#define EGulAdjBottom ECoeAdjBottom
#define TGulBorder TEikBorder
#define CEikIcon CFbsBitmap
#define ItemIcon ItemBitmap
#define iIconArray iBitmaps
#define CreateIconL(a,b,c) CreateBitmapL(a,b)
#define SetIconArray SetBitmapArray
#define EColorWindowBackground EEikColorWindowBackground
#define EColorWindowText EEikColorWindowText
#define EColorControlBackground EEikColorControlBackground
#define EColorControlText EEikColorControlText
#else
#define CEikIcon CGulIcon
#endif

#ifdef _UNICODE
#define AllocReadResourceAsDesLC AllocReadResourceAsDes16LC
#define AllocReadResourceAsDesL AllocReadResourceAsDes16L
#else
#define AllocReadResourceAsDesLC AllocReadResourceAsDes8LC
#define AllocReadResourceAsDesL AllocReadResourceAsDes8L
#endif

#ifndef __SCARLET__
#define _SSL_SUPPORT_
#endif
#ifndef ER5
#define _EXTERNAL_SSL_SUPPORT_
#endif

#endif // __EPOCPLATFORM_H
