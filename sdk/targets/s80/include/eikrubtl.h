/*
* ==============================================================================
*  Name        : eikrubtl.h
*  Part of     : CKON
*  Interface   : Rubberband API
*  Description : CEikRubberBand class handles (creates, drags, draws) a rubberband.
*                CEikRubberLine class handles (creates, drags, draws) a rubber line.
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


#ifndef EIKRUBTL_H
#define EIKRUBTL_H

// INCLUDES
#include <coecntrl.h>

// CLASS DECLARATIONS
/**
 *  The <code>CEikRubberBand</code> class handles (creates, drags, and draws) 
 *  a rubberband (rectangle or ellipse).
 *
 *  @lib eikctl.lib
 *  @since Series90.1.0
 */
class CEikRubberBand : public CCoeControl
    {
    public:
    /** The different flags used to create rubberband. 
    *   The values share space with <code>TEdges</code>.
    */
    enum TFlags
        { 
        /** rubberband can flip */
        EAllowToFlip    =0x10,
        /** whole rubberband can be moved */
        EMoveWholeBand  =0x20,
        /** rubberband will be drawn as ellipse */
        EDrawAsCircle   =0x40,
        /** maintains the width/height ratio */
        EMaintainAspect =0x80
        };

    public:

       /**
        * The default object constructor.
        */
        IMPORT_C CEikRubberBand();

       /**
        * The object destructor.
        */
        IMPORT_C ~CEikRubberBand();

       /**
        * Activates the rubberband.
        *
        * @since Series90.1.0
        * @param aStartPos The starting position
        * @param aRect The rubberband rectangle to be activated
        * @param aFlags The rubberband flags
        * @remarks
        * @see <code>TPoint</code> (e32std.h)
        * @see <code>TRect</code> (e32std.h)
        */
        IMPORT_C void Activate(const TPoint& aStartPos, const TRect& aRect, const TInt aFlags);

       /**
        * Draws a 'dragged' rubberband. This method is similar 
        * to the one below except <code>aMinWidth=aMinHeight=0</code>.
        *
        * @since Series90.1.0
        * @param aPos The dragged position of the rubberband
        * @remarks
        * @see <code>TPoint</code> (e32std.h)
        */
        IMPORT_C void NotifyDragPos(const TPoint& aPos);

       /**
        * Draws a 'dragged' rubberband.
        *
        * @since Series90.1.0
        * @param aPos The rubberband's dragged position
        * @param aMinWidth The minimum band width
        * @param aMinHeight The minimum band height
        * @remarks
        * @see <code>TPoint</code> (e32std.h)
        */
        IMPORT_C void NotifyDragPos(const TPoint& aPos,  TInt aMinWidth, TInt aMinHeight);

       /**
        * Clears the rubberband.
        *
        * @since Series90.1.0
        * @remarks
        * @see
        */
        IMPORT_C void Deactivate();

       /**
        * Draws a rubberband (ellipse or rectangle).
        *
        * @since Series90.1.0
        * @remarks
        * @see
        */
        IMPORT_C void XorDraw() const;

       /**
        * Calls <code>XorDraw()</code>, but activates and deactivates graphics 
        * context before and after the call.
        *
        * @since Series90.1.0
        * @remarks
        * @see
        */
        IMPORT_C void XorDrawNow() const;

        /**
        * Gets the rubberband rectangle.
        *
        * @since Series90.1.0
        * @return the rubberband rectangle
        * @remarks
        * @see
        */
        inline TRect BandRect() const;
    private:
        void CheckDragPosIsValid(TPoint& aPointerPos);
        TRect EnclosedRect(const TPoint &aPointA,const TPoint &aPointB);
    private:
    enum
        {
        EMaintainAspectDragHoriz    =0x100,
        EMaintainAspectDragVert     =0x200
        };

    private:
        TInt iRubberBandFlags;
        TPoint iAnchorPos;
        TRect iBandRect;
    };


inline TRect CEikRubberBand::BandRect() const
    { return(iBandRect); }


/**
*  The <code>CEikRubberLine</code> class handles (creates, drags, and draws) a 
*  rubber line.
*
*  @lib eikctl.lib
*  @since Series90.1.0
*/
class CEikRubberLine : public CCoeControl
    {
    public:
       /**
        * The default object constructor.
        */
        IMPORT_C CEikRubberLine();

       /**
        * The object destructor.
        */

        IMPORT_C ~CEikRubberLine();
       /**
        * Activates a rubber line.
        *
        * @since Series90.1.0
        * @param aStartPos The rubber line starting position
        * @remarks
        * @see <code>TPoint</code> (e32std.h)
        */
        IMPORT_C void Activate(const TPoint& aStartPos);

       /**
        * Draws a 'dragged' rubber line.
        *
        * @since Series90.1.0
        * @param aPos The rubber line's dragged position
        * @remarks
        * @see <code>TPoint</code> (e32std.h)
        */
        IMPORT_C void NotifyDragPos(const TPoint& aPos);
       /**
        * Clears the rubber line.
        *
        * @since Series90.1.0
        * @remarks
        * @see
        */
        IMPORT_C void Deactivate();
        /**
        * Draws a rubber line.
        *
        * @since Series90.1.0
        * @remarks
        * @see
        */
        IMPORT_C void XorDraw() const;

       /**
        * Calls <code>XorDraw()</code>, but activates and deactivates graphics 
        * context before and after the call.
        *
        * @since Series90.1.0
        * @remarks
        * @see
        */
        IMPORT_C void XorDrawNow() const;
       /**
        * Gets the rubber line's anchored position.
        *
        * @since Series90.1.0
        * @return the anchored position
        * @remarksype of return value:</B> TPoint
        * @see
        */
        inline TPoint AnchorPos() const;
       /**
        * Gets the rubber line's moving position.
        *
        * @since Series90.1.0
        * @return the moving position
        * @remarks
        * @see
        */
        inline TPoint MovingPos() const;
    private:
        TPoint iAnchorPos;
        TPoint iMovingPos;
    };


inline TPoint CEikRubberLine::AnchorPos() const
    { return(iAnchorPos); }
inline TPoint CEikRubberLine::MovingPos() const
    { return(iMovingPos); }

#endif  // EIKRUBTL_H

// End of File
