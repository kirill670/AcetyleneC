// COECNTRL.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#if !defined(__COECNTRL_H__)
#define __COECNTRL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__GULALIGN_H__)
#include <gulalign.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

#if !defined(__COEHELP_H__)
#include <coehelp.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

#if !defined(__COEMOP_H__)
#include <coemop.h>
#endif

#if !defined(__COEMAIN_H__)
#include <coemain.h>
#endif

#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
	#if !defined(__COETEXTDRAWER_H__)
	#include <coetextdrawer.h>
	#endif
#endif

class TResourceReader;
class CCoeEnv;
class MCoeControlContext;
class CCoeControlExtension;

#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
class MCoeLayoutManager;
class TCoeZoomWithType; 
class CCoeFontProvider;
class TCoeFont; 
#endif

/** Logical colour used when drawing in controls.

This class pairs a logical colour value with an explanation of how it is used 
when drawing a control. The explanation is in terms of categories of use, e.g. 
in the TGround category, the colour can used for either the foreground or 
background. 

@publishedAll 
@released */
class TCoeColorUse
    {
public:
	/** Foreground and background category flags */
	enum TGround
		{
		/** The logical colour is used to draw the control when it is in the foreground. */
		EFore=0x01,
		/** The logical colour is used to draw the control when it is in the background. */
		EBack=0x02
		};

	/** Flags that control the area in which colour is used. */
	enum TAreas
		{
		/** The logical colour is used to draw a control's contents. */
		EContents=0x10,
		/** The logical colour is used to draw a control's highlighted contents. */
		EHighlights=0x20,
		/** The logical colour is used to draw a control's surrounds. */
		ESurrounds=0x40,
		/** The logical colour is used to draw a control's borders. */
		EBorders=0x80
		};

	/** Focus category flags */
	enum TFocus
		{
		/** The logical colour is used to draw the control when active and either focused 
		or unfocused. */
		EActive=0x100,
		/** The logical colour is used to draw the control when dimmed and either focused 
		or unfocused. */
		EDimmed=0x200,
		/** The logical colour is used to draw the control when it is shadowed. */
		EShadowed=0x400,	
		/** The logical colour is used to draw the control when focused and pressed. */
		EPressed=0x800
		};

	/** State category flags */
	enum TState
		{
		/** The logical colour is used to draw the control in the normal state. */
		ENormal=0x1000,
		/** The logical colour is used to draw the control in the set state. */
		ESet=0x2000,
		/** The logical colour is used to draw the control in the checked state. */
		EChecked=0x4000
		};

	/** Tone flags */
	enum TTones
		{
		/** The logical colour is used to draw the control in neutral tones. */
		ENeutral=0x10000,
		/** The logical colour is used to draw the control in light tones. */
		ELight=0x20000,
		/** The logical colour is used to draw the control in midlight tones. */
		EMidLight=0x40000,
		/** The logical colour is used to draw the control in mid tones. */
		EMid=0x80000,
		/** The logical colour is used to draw the control in dark tones. */
		EDark=0x100000
		};
public:
	IMPORT_C TCoeColorUse();
	//
	IMPORT_C void SetUse(TInt aUse);
	IMPORT_C void SetLogicalColor(TInt aLogicalColor);
	IMPORT_C TInt LogicalColor() const;
	IMPORT_C TInt Use() const;
	//
	IMPORT_C TBool IsForeground() const;
	IMPORT_C TBool IsBackground() const;
	//
	IMPORT_C TBool IsContents() const;
	IMPORT_C TBool IsHighlights() const;
	IMPORT_C TBool IsSurrounds() const;
	IMPORT_C TBool IsBorders() const;
	IMPORT_C TBool IsActive() const;
	IMPORT_C TBool IsDimmed() const;
	IMPORT_C TBool IsPressed() const;
	IMPORT_C TBool IsNormal() const;
	IMPORT_C TBool IsSet() const;
private:
    TInt iLogicalColor;
	TInt iUse;
    };

#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)

// forward declarations.	
class CCoeControl;
class CCoeTextDrawerBase;

/** Interface to be used if a control elects to be a background drawer.

Parent controls can elect to take responsibility for drawing the background for their child
controls. To achieve this, they should aggregate an object that implements this interface.
CCoeControl::SetBackground() accepts the object and sets it as the background drawer

@publishedAll
@released
*/
class MCoeControlBackground
	{
public:
/** Draw the background for a given control.
The text drawer that shall be used to draw text on the specific background can be 
fetched through the GetTextDrawer() method. 

@param aGc Graphics context used for drawing
@param aControl The control being drawn (may be a child of the drawer)
@param aRect The area to be redrawn

@publishedAll
@released
*/
	virtual void Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const = 0;
	IMPORT_C virtual void GetTextDrawer(CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl) const;

private:  
  	IMPORT_C virtual void MCoeControlBackground_Reserved1();
  	IMPORT_C virtual void MCoeControlBackground_Reserved2();
  	IMPORT_C virtual void MCoeControlBackground_Reserved3();
  	IMPORT_C virtual void MCoeControlBackground_Reserved4();
  	IMPORT_C virtual void MCoeControlBackground_Reserved5();
	};

/** Abstract interface for defining a control's hit region.

This could be implemented by a CCoeControl-derived class to 
define hit region checking. The object is installed by calling CCoeControl::SetHitTest().

The hit region is the area inside the control's rectangle in which pointer events are handled.
It can be any shape, not necessarily rectangular.

@publishedAll
@released
*/
class MCoeControlHitTest
	{
public:	
/** Tests whether a pointer event occurred inside the control's hit region.
This function is called by CCoeControl::HandlePointerEventL().

@param aPoint The position of the pointer event.
@return ETrue if the specified point lies inside the hit region, EFalse if not.

@publishedAll
@released
*/
	virtual TBool HitRegionContains(const TPoint& aPoint) const = 0;
	};
#endif

class RCoeExtensionStorage
/** @internalComponent */
	{
public:
	RCoeExtensionStorage();
	void Close();
	TInt& Flags();
	TInt Flags() const;
#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
	const MCoeControlBackground* Background() const;
	void SetBackground(const MCoeControlBackground* aBackground);
	CCoeControl* Parent();
	void SetParent(CCoeControl* aParent);
	MCoeControlHitTest* HitTestControl() const;
	void SetHitTestControl(MCoeControlHitTest* aHitTest);
	TCoeZoomWithType* ZoomWithType() const;
	TInt SetZoomWithType(TCoeZoomWithType* aZoomWithType);
	const CCoeFontProvider* FontProvider() const;
	TInt SetFontProvider(const CCoeFontProvider* aFontProvider);
#endif
	void SetExtension(CCoeControlExtension* aExtension);
	CCoeControlExtension* Extension() const;
private:
	inline TBool IsFlags() const;
private:
	union
		{
		TInt iFlags;
		CCoeControlExtension* iExtension;
		};
	
	};

class CCoeControl : public CBase
#if !defined(BC_WITH_7_0)
								, public MObjectProvider
#endif
/** Control base class from which all other controls are derived. 

@publishedAll
@released */
	{
public:

#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
    enum TZoomType 
        { 
        EAbsoluteZoom,        // absolute 
        ERelativeZoom         // relative to parent's zoom 
        }; 
#endif
        
	IMPORT_C CCoeControl();
	IMPORT_C ~CCoeControl();
	// client interface
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C void SetContainerWindowL(RWindow& aWindow); 
	IMPORT_C void SetContainerWindowL(RBackedUpWindow& aWindow);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void ActivateL();
	IMPORT_C virtual void PrepareForFocusLossL();
	IMPORT_C virtual void PrepareForFocusGainL();
	IMPORT_C virtual void SetAdjacent(TInt aAdjacent);
	IMPORT_C virtual void SetNeighbor(CCoeControl* aNeighbor);
	IMPORT_C virtual TBool HasBorder() const;
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void GetHelpContext(TCoeHelpContext& aContext) const;
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C TCoeInputCapabilities RecursivelyMergedInputCapabilities() const; // not available before Release 006
	IMPORT_C void DrawNow() const;
	IMPORT_C void DrawDeferred() const;
	IMPORT_C void SetFocus(TBool aFocus,TDrawNow aDrawNow=ENoDrawNow);
	IMPORT_C void SetExtent(const TPoint& aPosition,const TSize& aSize);
	IMPORT_C void SetSize(const TSize& aSize);
	IMPORT_C TInt SetMaximumWidth(TInt aMaxWidth);	
	IMPORT_C void SetPosition(const TPoint& aPosition);
	IMPORT_C void SetRect(const TRect& aRect);
	IMPORT_C void SetExtentToWholeScreen();
	IMPORT_C TBool IsFocused() const;
	IMPORT_C TBool IsVisible() const;
	IMPORT_C TBool IsDimmed() const;
	IMPORT_C RDrawableWindow* DrawableWindow() const;
	IMPORT_C TSize Size() const;
	IMPORT_C TInt MaximumWidth() const;
	IMPORT_C TPoint Position() const;
	IMPORT_C TRect Rect() const;
	IMPORT_C TPoint PositionRelativeToScreen() const;
	IMPORT_C void SetObserver(MCoeControlObserver* aObserver);
	IMPORT_C MCoeControlObserver* Observer() const;
	inline CCoeEnv* ControlEnv() const;
	IMPORT_C TInt Index(const CCoeControl* aControl) const;
	IMPORT_C void SetNonFocusing();
	IMPORT_C void SetFocusing(TBool aFocusing); // not available before Release 005
	IMPORT_C TBool IsNonFocusing() const;
	IMPORT_C void SetControlContext(MCoeControlContext* aContext);
	IMPORT_C void CopyControlContextFrom(const CCoeControl* aControl);
	IMPORT_C MCoeControlContext* ControlContext() const;
	IMPORT_C TBool OwnsWindow() const;
	IMPORT_C TBool IsBackedUp() const;
	IMPORT_C void SetPointerCapture(TBool aCapture=ETrue);
	IMPORT_C void ClaimPointerGrab(TBool aSendUpEvent=ETrue);
	IMPORT_C void IgnoreEventsUntilNextPointerUp();
	IMPORT_C void SetComponentsToInheritVisibility(TBool aInherit=ETrue);
	IMPORT_C void SetGloballyCapturing(TBool aGlobal);
	IMPORT_C void OverrideColorL(TInt aLogicalColor,TRgb aColor); // not available before Release 005
	IMPORT_C TBool GetColor(TInt aLogicalColor,TRgb& aColor) const; // not available before Release 005

	// Context access mechanism - not available before Release 7.0s
	IMPORT_C void SetMopParent(MObjectProvider* aParent);
	
#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
	IMPORT_C const MCoeControlBackground* Background() const;
	IMPORT_C const MCoeControlBackground* FindBackground() const;
	IMPORT_C virtual TInt SetParent(CCoeControl* aParent);
	// Layout methods	
	IMPORT_C virtual void SetLayoutManagerL(MCoeLayoutManager* aLayout);
	IMPORT_C MCoeLayoutManager* LayoutManager() const;
	IMPORT_C virtual TBool RequestRelayout(const CCoeControl* aChildControl);

	IMPORT_C void SetZoomFactorL(TInt aZoomFactor, TZoomType aZoomType = ERelativeZoom);
   	IMPORT_C void SetFontProviderL(const CCoeFontProvider& aFontProvider);
   	IMPORT_C TZoomFactor AccumulatedZoom() const;
    IMPORT_C const CCoeFontProvider& FindFontProvider() const;

	// Baseline methods
	IMPORT_C virtual TInt TextBaselineOffset(const TSize& aSize) const;
	IMPORT_C virtual void SetTextBaselineSpacing(TInt aSpacing);
#endif
	
public: // but not exported
	void ProcessPointerEventL(const TPointerEvent& aPointerEvent);
	void ProcessPointerBufferReadyL();
	void RecursivelyMergeInputCapabilities(TCoeInputCapabilities& aInputCapabilities) const;
	void WriteInternalStateNowL(RWriteStream& aWriteStream) const;

#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
    void NotifyFontChange(const CCoeFontProvider* aFontProvider);
#endif

protected:
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void HandlePointerBufferReadyL();
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void PositionChanged();
public:
	IMPORT_C virtual TInt CountComponentControls() const;
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
protected:
	IMPORT_C void EnableDragEvents();
	IMPORT_C void HandleRedrawEvent(const TRect& aRect) const;
	IMPORT_C RWindow& Window() const;
	IMPORT_C RBackedUpWindow& BackedUpWindow() const;
	IMPORT_C void CloseWindow();
	IMPORT_C void CreateWindowL();
	IMPORT_C void CreateWindowL(const CCoeControl* aParent);
	IMPORT_C void CreateWindowL(RWindowTreeNode& aParent);
	IMPORT_C void CreateWindowL(RWindowGroup* aParent);
	IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent); // not available before Release 005
	IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent,TDisplayMode aDisplayMode);
	IMPORT_C void SetAllowStrayPointers();
	IMPORT_C void SetCanDrawOutsideRect();
	IMPORT_C void SetBlank();
	IMPORT_C void ReportEventL(MCoeControlObserver::TCoeEvent aEvent);
	IMPORT_C void SetCornerAndSize(TGulAlignment aCorner,const TSize& aSize);
	IMPORT_C void SetSizeWithoutNotification(const TSize& aSize);
	IMPORT_C CWindowGc& SystemGc() const;
	IMPORT_C void ActivateGc() const;
	IMPORT_C void ResetGc() const;
	IMPORT_C void DeactivateGc() const;
	IMPORT_C TBool IsReadyToDraw() const;
	IMPORT_C TBool IsActivated() const;
	IMPORT_C TBool IsBlank() const;
	IMPORT_C TBool IsBeingDestroyed() const;
	IMPORT_C CCoeControl* GrabbingComponent() const;
	IMPORT_C TBool CapturesPointer() const;
	IMPORT_C void HandleComponentControlsResourceChange(TInt aType); // not available before Release 005u
	
#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
	IMPORT_C virtual void AddComponentByIdLC( CCoeControl* aControl, TInt aComponentId = KErrNotFound ) ; 
	IMPORT_C virtual CCoeControl* RemoveComponentById( TInt aComponentId );
	IMPORT_C virtual TInt RemoveComponent( CCoeControl& aControl ); 
	IMPORT_C virtual CCoeControl* ComponentById( TInt aComponentId );
	IMPORT_C virtual CCoeControl* ComponentById( TInt aComponentId ) const;
	IMPORT_C const CFont& ScreenFont(const TCoeFont& aFont) const;
	IMPORT_C CCoeTextDrawerBase& TextDrawer(TInt aKey = KErrNotFound) const; 

private:
	IMPORT_C virtual void GetTextDrawer(CCoeTextDrawerBase*& aTextDrawer, const CCoeControl* aDrawingControl, TInt aKey) const;
	IMPORT_C virtual void Reserved_CCoeControl_8();
	IMPORT_C virtual void Reserved_CCoeControl_9();
#endif

protected: // from MObjectProvider - not available before Release 7.0s
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

private: // from MObjectProvider - not available before Release 7.0s
	IMPORT_C virtual MObjectProvider* MopNext();

private:
	friend class CCoeRedrawer;
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	void DrawComponents(const TRect& aRect) const;
	void DrawWindowOwningComponentsNow() const;
	void SetGrabbed(TBool aGrabbed);
	TBool IsGrabbed() const;
	void DoMakeVisible(TBool aVisible);
	void CheckPointerEventPurge() const;
	inline TInt Flags() const;
	inline TInt& Flags();
#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
	void RecursivelyMergeTextDrawers(CCoeTextDrawerBase*& aTextDrawer, TInt aKey) const;
	const CCoeControl* WindowOwningParent() const;
	const CCoeControl* SearchParent(const CCoeControl* aParentToFind) const;
	void DoSetLayoutL(MCoeLayoutManager* aLayoutManager);
	TInt SetZoomWithType(TCoeZoomWithType* aZoomWithType);
	TCoeZoomWithType* GetZoomWithType() const;
	TInt SetFontProvider(const CCoeFontProvider* aFontProvider);
	const CCoeFontProvider* GetFontProvider() const;
#endif

protected: // was Reserved_1(). Must be left here to maintain BC
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)
public:
	IMPORT_C void SetBackground(const MCoeControlBackground* aBackground);
	IMPORT_C CCoeControl* Parent();
	IMPORT_C const CCoeControl* Parent() const;
	void RemoveFromParent() ;
	IMPORT_C TInt SetGc(CWindowGc* aGraphicsContext);
	IMPORT_C void DrawBackground(const TRect& aRect) const;
	IMPORT_C void DrawForeground(const TRect& aRect) const;
	IMPORT_C TInt SetHitTest(MCoeControlHitTest* aHitTestControl);
	IMPORT_C MCoeControlHitTest* HitTest() const;
#endif

private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_2();
	
#if defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)

public:
	IMPORT_C TInt UniqueHandle() const ;
	IMPORT_C TInt SetUniqueHandle( TInt aUniqueHandle ) ; 
#endif //	defined(SYMBIAN_UI_FRAMEWORKS_CONTROL_API_V2)

protected:
	CCoeEnv* iCoeEnv;
	MCoeControlContext* iContext;
	TPoint iPosition;
	TSize iSize;
private:
	RDrawableWindow* iWin;
	MCoeControlObserver* iObserver;
	RCoeExtensionStorage iExt;
#if !defined(BC_WITH_7_0)
	MObjectProvider* iMopParent;
#endif
	};


inline CCoeEnv* CCoeControl::ControlEnv() const
/** Gets the control environment object for this control.

@return The control's control environment object. */
	{return(iCoeEnv);}

#endif
