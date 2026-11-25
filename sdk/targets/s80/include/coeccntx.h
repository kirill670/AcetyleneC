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
 * The <code>MCoeControlContext</code> class is an interface class that allows
 * the sharing of graphics settings between controls. The interface provides 
 * methods to set the graphics context of a control before drawing. If a 
 * control has its <code>iContext</code> member set, when a control is about 
 * to be drawn, the UI Control Framework calls methods defined by this 
 * interface. Developers must implement <code>PrepareContext()</code>, which 
 * is called by the framework, to initialize the control's window with the 
 * required graphics settings. To use control contexts, a control should 
 * inherit from an <code>MCoeControlContext</code>-derived class. To share the 
 * context between controls, this control should then be set as the context 
 * for all controls that wish to share it. This is done by setting the 
 * <code>iContext</code> member of each of the controls, using 
 * <code>CCoeControl::SetControlContext()</code> and 
 * <code>CCoeControl::CopyControlContextFrom()</code>. 
 * 
 * @lib [what]
 * @publishedAll
 * @released 
 */
class MCoeControlContext

    {
public:
    /**
    * Activates a graphics context for the specified window. This method
    * is called whenever a control is about to be drawn. Its default 
    * implementation activates the graphics context given by <code>aGc</code>
    * for the window given by <code>aWindow</code>, and calls 
    * <code>PrepareContext()</code>. This method may be overridden by derived 
    * classes.
    *
    * @param aGc The graphics context to activate. When called from 
    *            <code>CCoeControl::ActivateGc()</code>, this is the system 
    *            graphics context
    * @param aWindow The window for which the graphics context is to be 
    *                activated
    * @remarks
    * @see
    */ 
    IMPORT_C virtual void ActivateContext(CWindowGc& aGc,RDrawableWindow& aWindow) const;

    /**
    * Resets the control context. The default implementation first resets the 
    * graphics context given by <code>aGc</code>, and then calls 
    * <code>PrepareContext()</code>. The method may be overridden by derived 
    * classes.
    *
    * @param aGc The graphics context to be reset
    * @remarks
    * @see
    */ 
    IMPORT_C virtual void ResetContext(CWindowGc& aGc) const;

    /**
    * Initializes graphics context settings. This method should be implemented 
    * by derived classes to initialize the graphics context, given by 
    * <code>aGc</code>, with the required settings. The default implementation 
    * is empty.
    * 
    * @param aGc The graphics context to be initialized
    * @remarks
    * @see
    */
    IMPORT_C virtual void PrepareContext(CWindowGc& aGc) const;
    };

/** 
 * The <code>CCoeBrushAndPenContext</code> class for a brush and pen 
 * graphics context. This class allows an <code>MCoeControlContext</code> to 
 * be instantiated and used to set brush and pen properties before drawing a 
 * control.
 *
 * @lib [what]
 * @publishedAll 
 * @released 
 */
class CCoeBrushAndPenContext : public CBase, public MCoeControlContext

    {
public:
   /**
    * Starts the two-phase object construction. Allocates and constructs a new 
    * brush and pen graphics context object.
    * 
    * @return a pointer to the newly created object
    * @remarks
    * @see
    */
    IMPORT_C static CCoeBrushAndPenContext* NewL();

    /**
    * Sets the brush style.
    * 
    * @param aBrushStyle The brush style to be used for drawing
    * @remarks
    * @see
    */
    IMPORT_C void SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle);
    /**
    * Sets the brush color.
    * 
    * @param aColor The brush color
    * @remarks
    * @see
    */
    IMPORT_C void SetBrushColor(TRgb aColor);

    /**
    * Sets the drawing brush pattern bitmap. When a bitmap has been set, a 
    * patterned style brush is selected automatically. 
    *
    * @param aBitmap The pattern bitmap
    * @remarks
    * @see
    */
    IMPORT_C void SetBrushBitmap(const CFbsBitmap& aBitmap);

    /**
    * Sets the pen color.
    * 
    * @param aColor The pen color
    * @remarks
    * @see
    */
    IMPORT_C void SetPenColor(TRgb aColor);
    
    /**
    * Gets the brush style.
    * 
    * @return the current brush style
    * @remarks
    * @see
    */
    IMPORT_C CWindowGc::TBrushStyle BrushStyle() const;

    /**
    * Gets the brush color.
    * 
    * @return the current brush color
    * @remarks
    * @see
    */
    IMPORT_C TRgb BrushColor() const;

    /**
    * Gets a reference to the bitmap used to pattern the drawing brush.
    * 
    * @return The pattern bitmap
    * @remarks
    * @see
    */
    IMPORT_C const CFbsBitmap& BrushBitmap() const;

    /**
    * Gets the pen color.
    * 
    * @return the current pen color
    * @remarks
    * @see
    */
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

/** Protocol for sharing brush settings used in graphics operations. 

It can be used to set brush and pen properties before drawing a control.

The mixin provides a default implementation of a control context. It implements 
PrepareContext() to initialise brush settings used in graphics operations. 
Its data members are public so that the brush style, brush colour and brush 
pattern can be set by application code.

@publishedAll
@deprecated */
class MCoeControlBrushContext : public MCoeControlContext

    {
protected: // from MCoeControlContext
    IMPORT_C void PrepareContext(CWindowGc& aGc) const;
public:
    /** Brush style. (Not required if iBitmap is set.) */
    CWindowGc::TBrushStyle iBrushStyle;
    /** Brush colour. (Not required if iBitmap is set.) */
    TRgb iBrushColor;
    /** Brush pattern. */
    const CFbsBitmap* iBitmap;
    };

#endif
