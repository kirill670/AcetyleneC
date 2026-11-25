/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2001-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis
*/

#ifndef __EPOCDEF_H
#define __EPOCDEF_H

#include <e32std.h>
#include <e32def.h>

#include "epocplatform.h"

_LIT(KSystemDataPath, "\\System\\Data\\");
_LIT(KOperaDataPath, "\\System\\Data\\Opera\\");
_LIT(KOperaSystemPath, "\\System\\Apps\\Opera\\");

#if defined(__SCARLET__)

/*** Font enum - this must match the order in the resource file ***/

enum 
	{
	EOperaFontLatinPlain12=0,
	EOperaFontLatinBold12,
	EOperaFontLatinBold13,
	EOperaFontLatinBold17,
	EOperaFontLatinBold19,
	EOperaFontPlainItalic12,
	EOperaFontBoldItalic12,
	EOperaFontPlain13,
	EOperaFontPlainItalic13,
	EOperaFontBoldItalic13,
	EOperaFontPlainItalic17,
	EOperaFontPlain17,
	EOperaFontBold17,
	EOperaFontBoldItalic17
	};

const TInt KOperaNumFonts=14;	// number of fonts in resources - must be correct

#define KOperaBaseFontResource R_OPERA_FONT_LATIN_PLAIN_12	// the first font

const TInt KOperaNumCoreGenericFonts=5;

_LIT(KOperaFontNameLatin,"Latin");
_LIT(KOperaFontNameAlp,"Alp");

const TInt KOperaSmallFontPoints=12;	// the limit for small font
const TInt KOperaMediumFontPoints=16;
const TInt KOperaBigFontPoints=24;

#endif	//__SCARLET__

#endif // __EPOCDEF_H
