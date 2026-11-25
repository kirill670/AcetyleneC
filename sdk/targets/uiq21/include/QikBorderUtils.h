// QikBorderUtils.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKBORDERUTILS_H__
#define __QIKBORDERUTILS_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <coecntrl.h>
#include <gulutil.h>

class QikBorderUtils
	{
public:
	IMPORT_C static void GetRgbDerivedBorderColors(TGulBorder::TColors& aBorderColors,
		TLogicalColor aLogicalBackgroundColor, CEikonEnv* aEnv, const CCoeControl& aBorderedControl);
	};

#endif
