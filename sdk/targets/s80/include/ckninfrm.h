/*
* ==============================================================================
*  Name        : ckninfrm.h
*  Part of     : CKON / CKCTL
*  Interface   : Input Frame API
*  Description : An Input Frame which can contain any CCoeControl
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


#ifndef CKNINFRM_H
#define CKNINFRM_H

// INCLUDES
#include <eikdef.h>
#include <eikbctrl.h>
#include <gulicon.h>
#include <eiklabel.h>

/**
 * The <code>CCknInputFrame</code> class implements an Input Frame that can 
 * contain any <code>CCoeControl</code>. The Input Frame can have additional 
 * icon and/or information text.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */

class CCknInputFrame : public CEikBorderedControl, public MCoeControlObserver
    {
    public:

        /**
        * The default object constructor.
        * @internal
        */
        CCknInputFrame();

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknInputFrame();
        
        /**
        * Static factory method to create an instance of the 
		* <code>CCknInputFrame</code> class. 
        * After construction, the application should usually perform the 
        * following operations before the Input Frame object is ready to use: 
        *   set a text label, if required, by calling 
        *       <code>SetInfoTextL()</code>; 
        *   set a container window by calling 
        *       <code>SetContainerWindowL(CCoeControl*)</code>; 
        *   set the size and position of the control as required; 
        *   set an observer to the Input Frame, if required, by calling 
        *       <code>SetObserver(MCoeObserver* )</code>; 
        *   set an observer to the control in the Input Frame, if required, by 
        *       calling <code>SetObserver(MCoeObserver* )</code>. 
        * 
        * @param aField Pointer to a control which will be located inside the 
        *               Input Frame. This must point to a valid control. To 
        *               receive state change events from the control inside 
        *               the Input Frame, <code>SetObserver()</code> must be 
        *               called on that control
        *
        * @param aComponentOwner Defines the ownership of the control located 
		*                        in the Input Frame. <code>ETrue</code> sets 
		*                        ownership of the control to the Input Frame. 
		*                        Input Frame deletes the control in its 
		*                        destructor
        *
        * @param aBitmapfile     Descriptor containing a path to the MBM file 
		*                        that contains the icon to be shown in the 
		*                        Input Frame. An empty descriptor implies that 
		*                        no icon is required
        *
        * @param aBitmapId       Defines the index of the required icon bitmap in the specified MBM file.
        *
        * @param aMaskId         Defines the index of the mask of the required icon bitmap in the specified 
        *                        MBM file
        *
        * @param aFlags          Flags used to influence the layout and style 
		*                        of the Input Frame. These are specified in 
		*                        ckon.hrh under the comment '// CKNINFRM 
		*                        constants'. Only one of these, 
		*                        <code>ECknInputFrmRemoveBorder</code>, 
		*                        is currently implemented, and causes the 
		*                        control in the Input Frame to be displayed 
		*                        with no border
        *
        *
        * @return      Returns a <code>CCknInputFrame</code> object
        * @remarks     Leaves if allocation of the <code>CCknInputFrame</code> 
		*              object fails.
        *              Panics if invalid <code>aField</code> pointer passed
        * @see         ckon.hrh for definition of flag values
        */
        IMPORT_C static CCknInputFrame* NewL(CCoeControl* aField,
                                             TBool aComponentOwner,
                                             const TDesC& aBitmapfile, 
                                             TInt aBitmapId, 
                                             TInt aMaskId,
                                             TUint32 aFlags = 0 );

        /**
        * Static factory method to create an instance of the 
		* <code>CCknInputFrame</code> class. 
        * After construction, the application should usually perform the 
		* following operations before the Input Frame object is ready to use: 
        *   set a text label, if required, by calling 
		*       <code>SetInfoTextL()</code>; 
        *   set a container window by calling 
		*       <code>SetContainerWindowL(CCoeControl*)</code>; 
        *   set size and position of the control as required; 
        *   set an observer to the Input Frame, if required, by calling 
        *       <code>SetObserver(MCoeObserver* )</code>;  
        *   set an observer to the control in the Input Frame, if required, by 
		*       calling <code>SetObserver(MCoeObserver* )</code>. 
        * 
        * @param aField Pointer to a control which will be located inside the 
		*               Input Frame. This must point to a valid control. To 
		*               receive state-change events from the control inside 
		*               the Input Frame, <code>SetObserver()</code> must be 
        *               called on that control
        *
        * @param aComponentOwner Defines the ownership of the control located 
		*                        in the Input Frame. <code>ETrue</code> sets 
		*                        ownership of the control to the Input Frame. 
		*                        Input Frame deletes the control in its 
		*                        destructor
        *
        * @param aIcon           Pointer to a <code>GulIcon</code> bitmap 
		*                        package object. This contains the required 
        *                        icon bitmap and its mask. A NULL value 
		*                        indicates that no icon is required.
        *                        The Input Frame takes ownership of the icon 
		*                        object passed
        *
        * @param aFlags          Flags used to influence the layout and style 
		*                        of the Input Frame. These are specified in 
		*                        ckon.hrh under the comment '// CKNINFRM 
		*                        constants'. Only one of these, 
		*                        <code>ECknInputFrmRemoveBorder</code>, 
		*                        is currently implemented, and causes the 
		*                        control in the Input Frame to be displayed 
		*                        with no border
        *
        * @return      returns a <code>CCknInputFrame</code> object.          
        * @remarks     Leaves if allocation of the <code>CCknInputFrame</code> 
		*              object fails.
        *              Panics if invalid aField pointer passed
        * @see         ckon.hrh for definition of flag values
        * @see         gulicon.h for definition of <code>CGulIcon</code>
        */
        IMPORT_C static CCknInputFrame* NewL(CCoeControl* aField,
                                             TBool aComponentOwner,
                                             CGulIcon* aIcon, 
                                             TUint32 aFlags = 0 );

        /**
        * Returns a pointer to the control located in the Input Frame. 
		* Cast the  pointer returned to the type of the control before calling 
		* any type-specific methods on the control.
        *
        * @return   returns a <code>CCoeCOntrol</code> pointer to the control 
		*           located in the Input Frame
        * @remarks
        * @see      <code>CGulIcon</code> definition in gulicon.h
        */
        IMPORT_C CCoeControl* Field() const;

        /**
        * Sets additional information text to Input Frame. This method may be 
		* called at any time during the operation of the Input Frame.
        *
        * @param aText  The text to be set
        *
        * @remarks      Leaves if allocation fails during the creation or 
		*               updating of the text label
        * @see
        */
        IMPORT_C void SetInfoTextL(const TDesC& aText);

        /**
        * Sets an icon to the Input Frame. This method may be called at any 
		* time during the operation of the Input Frame.
        *
        * @param aIcon      The <code>GulIcon</code> bitmap package object to 
		*                   be set. This contains the required icon bitmap and 
		*                   its mask. A NULL value indicates that no icon is 
		*                   required. The Input Frame takes ownership of the 
		*                   icon object passed. If an icon object has been 
		*                   previously set by this method or by constructor, 
		*                   that icon object is deleted
        *                   
        * @remarks
        * @see
        */
        void SetIcon(CGulIcon* aIcon);

    public: //from MCoeControlObserver

        /**
        * Handles the <code>EEventRequestFocus</code> event by setting the 
		* contained control as focused.
        *
        * @param aControl       The control that sent the event
        *
        * @param aEventType     The event type. This method handles 
		*                       <code>EEventRequestFocus</code> only
        *
        * @remarks  It IS exported 
        * @see      <code>MCoeControlObserver</code>
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType); // not exported

    public: //from CCoeControl

        /**
        * Handles key events offered to the Input Frame control by the control 
		* environment. The Input Frame forwards the key events to the control 
		* located in the Input Frame.
        * 
        * @param aKeyEvent      The key event offered
        *
        * @param aType          The type of key event, either: 
		*                       <code>EEventKey</code>, 
		*                       <code>EEventKeyUp</code> or 
		*                       <code>EEventKeyDown</code>
        *
        * @return   indicates whether or not the key event was used by this 
		*           control. <code>EKeyWasConsumed</code> if the control takes 
		*           action on the key event; <code>EKeyWasNotConsumed</code> 
		*           otherwise
        *
        * @remarks
        * @see      <code>CCoeControl</code>
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Returns the smallest possible size for the Input Frame.
        *
        * @return   the minimum size for the Input Frame
        *
        * @remarks
        * @see      <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Construct an Input Frame from a resource file. The resource reader 
		* must be set to read a resource structure of the 
		* type <code>INPUTFRAME</code>
        *
        * @param aReader A resource reader
        *
        * @remarks  The resource structure is of type <code>INPUTFRAME</code>
        * @see      cknctl.rh for definition of <code>INPUTFRAME</code> 
		*           resource structure 
        * @see      barsread.h for definition of <code>TResourceReader</code>
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader); 

        /**
        * Sets a component control's container window.
        *
        * @param aContainer The window owned by the container control
        * @internal
        */
        void SetContainerWindowL(const CCoeControl& aContainer);

    private: // From CCoeControl
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void SizeChanged();
        void FocusChanged(TDrawNow aDrawNow); 
        void Draw(const TRect& aRect) const;
        void PrepareForFocusLossL();
    private:
        TMargins Borders() const;
        void BaseConstructL(CCoeControl* aField, TBool aOwner, TUint32 aFlags);
        void ConstructL(CCoeControl* aField, TBool aOwner, const TDesC& aFileName, TInt aBitmapId, TInt aMaskId, TUint32 aFlags);
        void ConstructL(CCoeControl* aField, TBool aOwner, CGulIcon* aIcon, TUint32 aFlags);
        TRect InnerRect() const;
        void DrawBorder(CWindowGc& aGc, TRect& aRect) const;
        void DrawCentralRect(CWindowGc& aGc, TRect& aRect) const;
        TInt MinHeight();
    private:
    enum TInputFrameFlags
        {
        EOwnsField=0x40
        };
        CCoeControl* iField;
        CGulIcon* iIcon;
        CEikLabel* iInfoText;
        TUint32 iFlags; 
        TBool iResourceConstructed;
    protected:
        CCoeBrushAndPenContext* iBrushAndPenContext;
        TBool iIsBcVersion;
    };

/**
*  This version of the CCknInputFrame class is retained for backward compatibility.
*
*  This class should not be used by user clients. Use CCknInputFrame.
*  @deprecated 
*  @lib CKNCTL.LIB
*/
class CCknInputFrameBC : public CCknInputFrame
    {
    public:

        /**
        * C++ default constructor.
        */
        CCknInputFrameBC();
    private:
    };


#endif  // CKNINFRM_H

// End of File
