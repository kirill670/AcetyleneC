// EIKALIGN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKALIGN_H__)
#define __EIKALIGN_H__

#include <coecntrl.h>
#include <gulalign.h>
#include <gulutil.h>

/**
 *
 * This class extends the <code>CCoeControl</code> class in order to
 * support extra functionality such as control alignment and margins.
 *
 * It is only intended as a simple building block for controls.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikAlignedControl : public CCoeControl
	{
public:
	IMPORT_C CEikAlignedControl();
	IMPORT_C ~CEikAlignedControl();
	IMPORT_C void SetAllMarginsTo(TInt aValue);
	IMPORT_C void SetAlignment(TGulAlignmentValue aAlign);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
public:
	TMargins8 iMargin;
	TGulAlignment iAlignment;
	};


#endif
