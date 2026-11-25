// COECCNTX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COECCNTX_H__)
#define __COECCNTX_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

/**
 *
 * Interface to allow sharing of graphics settings between controls.
 *
 * The interface provides functions to set the graphics context of a
 * control before drawing. If a control has its <code>iContext</code>
 * member set, the UI Control Framework calls functions defined by this
 * interface when a control is about to be drawn. Developers must
 * implement <code>PrepareContext()</code>, which is called by the
 * framework, to initialise the controls window with the required
 * graphics settings.To use control contexts, a control should inherit
 * from an <code>MCoeControlContext</code>-derived class. To share the
 * context between controls, this control should then be set as the
 * context for all controls that wish to share it. This is done by
 * setting the <code>iContext</code> member of each of the controls using
 * <code>CCoeControl::SetControlContext()</code> and
 * <code>CCoeControl::CopyControlContextFrom()</code>.
 *
 * @since 5.0
 * @lib "cone.lib"
 */
class MCoeControlContext
	{
public:
	IMPORT_C virtual void ActivateContext(CWindowGc& aGc,RDrawableWindow& aWindow) const;
	IMPORT_C virtual void ResetContext(CWindowGc& aGc) const;
	IMPORT_C virtual void PrepareContext(CWindowGc& aGc) const;
	};

/**
 *
 * Brush and pen graphics context.
 *
 * This class allows an <code>MCoeControlContext</code> to be
 * instantiated and used to set brush and pen properties before drawing a
 * control.
 *
 * @since 5.1
 * @lib "cone.lib"
 */
class CCoeBrushAndPenContext : public CBase, public MCoeControlContext
	{
public:
	IMPORT_C static CCoeBrushAndPenContext* NewL();
	//
	IMPORT_C void SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle);
	IMPORT_C void SetBrushColor(TRgb aColor);
	IMPORT_C void SetBrushBitmap(const CFbsBitmap& aBitmap);
	IMPORT_C void SetPenColor(TRgb aColor);
	//
	IMPORT_C CWindowGc::TBrushStyle BrushStyle() const;
	IMPORT_C TRgb BrushColor() const;
	IMPORT_C const CFbsBitmap& BrushBitmap() const;
	IMPORT_C TRgb PenColor() const;
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	CCoeBrushAndPenContext();
private:
	CWindowGc::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	const CFbsBitmap* iBitmap;
	TRgb iPenColor;
	};

/**
 *
 * Protocol for sharing brush settings used in graphics operations.
 *
 * It can be used to set brush and pen properties before drawing a
 * control.The mixin provides a default implementation of a control
 * context. It implements <code>PrepareContext()</code> to initialise
 * brush settings used in graphics operations. Its data members are
 * public so that the brush style, brush colour and brush pattern can be
 * set by application code.Note:The class deprecated after ER5
 *
 * @since 5.0
 * @lib "cone.lib"
 * @deprecated
 */
class MCoeControlBrushContext : public MCoeControlContext
	{
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
public:
	CWindowGc::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	const CFbsBitmap* iBitmap;
	};

#endif
