// EIKBCTRL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBCTRL_H__)
#define __EIKBCTRL_H__

#include <gulbordr.h>
#include <coecntrl.h>

/**
 *
 * A control which is drawn surrounded by a rectangular border.
 *
 * This class is used as the basis for most Uikon controls.The screen
 * appearance of derived classes can be changed by overriding the
 * protected method <code>Draw()</code>. By default, this draws a border
 * of the appropriate type around the control.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikBorderedControl : public CCoeControl
	{
public:
	IMPORT_C CEikBorderedControl();
	IMPORT_C CEikBorderedControl(const TGulBorder& aBorder);
public: // from CCoeControl
	IMPORT_C TBool HasBorder() const;
	IMPORT_C void SetAdjacent(TInt aAdjacent);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public: // new function
	IMPORT_C void SetBorder(TGulBorder::TBorderType aBorderType);
	IMPORT_C void SetBorder(TInt aBorderType);
	IMPORT_C TGulBorder Border() const;
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
protected:
	TGulBorder iBorder;
	};



#endif
