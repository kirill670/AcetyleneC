/*
* ============================================================================
*  Name     : AknInfrm.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

// INCLUDES
#ifndef __AKNINFRM_H__
#define __AKNINFRM_H__


#include <eikdef.h>
#include <eikbctrl.h>
#include <gulicon.h>
#include <eiklabel.h>
#include <aknutils.h>
#include <avkon.rsg>

class CAknInputFrameExtension;
class CAknsFrameBackgroundControlContext;
// CLASS DECLARATION
	/**
	* Implements an input frame which can contain any @c CCoeControl.
	* The input frame can have additional icon and/or info text.
 	* @since Series60 0.9
 	*/
NONSHARABLE_CLASS(CAknInputFrame) : public CEikBorderedControl, public MCoeControlObserver
	{
public:

	/**
 	* Default C++ constructor.
 	*/
	CAknInputFrame();
	
	/**
 	* Destructor. Frees all resources owned by the object prior to its
 	* destruction.
 	*/
	IMPORT_C ~CAknInputFrame();
	
	/**
    * Two-phased constructor.
 	* @param aField Control which will be located inside the input frame
 	* @param aComponentOwner Defines whether the ownership of the control will
 	* be transferred or not.
 	* @param aBitmapfile Bitmap file name and path.
 	* @param aBitmapId Bitmap Id.
 	* @param aMaskId Bitmap Mask Id.
 	* @param aFlags Flags.
    * @return a Pointer to the new @c CAknInputFrame object.
    */
	IMPORT_C static CAknInputFrame* NewL(CCoeControl* aField,TBool aComponentOwner,
				   const TDesC& aBitmapfile, TInt aBitmapId, TInt aMaskId,
				   TUint32 aFlags = 0 );
	/**
    * Two-phased constructor.
 	* @param aField Control which will be located inside the input frame
 	* @param aComponentOwner Defines whether the ownership of the control is
 	* transferred or not.
 	* @param aIcon Bitmap file name and path.
 	* @param aFlags Flags.
    * @return a Pointer to the new @c CAknInputFrame object.
    */
	IMPORT_C static CAknInputFrame* NewL(CCoeControl* aField,TBool aComponentOwner,
				   CGulIcon* aIcon, TUint32 aFlags = 0 );
	/**
    * Returns apointer to field.
    * @return a Pointer to the control, which is located inside the input frame. 
    */
	IMPORT_C CCoeControl* Field() const;
	
	/**
    * Sets additional info text to input frame.
 	* @param aText Info text to be added in the input frame.
    */
	IMPORT_C void SetInfoTextL(const TDesC& aText);
	
	/**
    * Sets the lines visible or invisible.
    * @param aText @c ETrue to make the line visible, @c EFalse to make it
    * invisible.
    */
	IMPORT_C void SetLineState(TBool aLineVisible);
	
	/**
    * Sets new icon to input frame.
    * @param aIcon a Pointer to the new icon. Ownership is transffered which 
    * means that object is deleted in @c CAknInputFrame::~CAknInputFrame().
    */
	void SetIcon(CGulIcon* aIcon);
public: //from MCoeControlObserver

	/**
    * Handles focus changes. This is called by the UI Control Framework to 
    * notify that an event occured in observed input frame.
    * @param aControl The control where event has happened.
    * @param aEventType a Type of the event.
    */
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public: //from CCoeControl

	/**
    * Handles key events.
    * @param aKeyEvent The key event.
    * @param aType The type of the event: @c EEventKey, @c EEventKeyUp or 
    * @c EEventKeyDown.
    * @return Indicates whether or not the key event was used by this control. 
    */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	
	/**
    * Tells the minimum size of the control.
    * @return The minimum size of the control.
    */
	IMPORT_C TSize MinimumSize();
	
	/**
    * The second phase constructor: constructs input frame from resources.
    * @param The resource reader.
    */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader); 
	
	/**
    * Sets the implementation of this control context in this input frame.
    * It is a layout background of the frame item. 
    * @since Series 60 2.1
    * @param Pointer to the context.
    */
	IMPORT_C void SetInputContext(CAknsFrameBackgroundControlContext* aContext);


private: // From CCoeControl
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
	TSize InfoAreaSize() const;
public:
	/** Enumeration flags for different layouts.	*/
	enum TInputFrameFlags
	
		{
		/** a Standard layout. */
		EOwnsField=0x40,
		/** a Popup layoyt. */
		EPopupLayout=0x80,
		/** a Pinboard layout. */
		EPinbLayout=0x100,
		/** a ClockAppLayout. */
		EClockAppLayout=0x200,
		/** a Layout without lines. */
		EFixedFindWithoutLine   = 0x400,
		/** a Layout that shows indicator.*/
        EShowIndicators         = 0x800,
        /** A layout used by list query. */
		EPopupWindowLayout=0x1000
		};
private:
	CAknInputFrameExtension *iExtension;
	CGulIcon* iIcon;
	CEikLabel* iInfoText;
	TUint32 iFlags;
	TAknLayoutRect iVertShadow, iHoriShadow, iOutlineRect, iMagnIconPos;
	// next ones are only used with popup style
	TAknLayoutRect iCoverRect, iSecondShadow, iFirstShadow, iOutlineFrame, iInsideArea;
	};


#endif



