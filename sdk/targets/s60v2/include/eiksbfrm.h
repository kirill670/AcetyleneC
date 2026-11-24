// EIKSBFRM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
	
#if !defined(__EIKSBFRM_H__)
#define __EIKSBFRM_H__

#include <lafpublc.h>
#if !defined(__AKNSCRLB_H__)
#include <aknscrlb.h>
#endif

class CEikCba;

// 
// TEikScrollBarFrameLayout
//

class TEikScrollBarFrameLayout
	{
public:
	// enums
	enum TTilingMode
		{
		EClientRectConstant,
		EInclusiveRectConstant
		};
public:
	// c'tor
	IMPORT_C TEikScrollBarFrameLayout();

	// set all margins to the same value
	IMPORT_C void SetInclusiveMargin(TInt aMargin);
	IMPORT_C void SetClientMargin(TInt aMargin);
public:
	TMargins iInclusiveMargin;
	TMargins iClientMargin;
	TSize iClientAreaGranularity;
	TTilingMode iTilingMode;
	};

// 
// CEikScrollBarFrame
// 

class CEikCornerWindow;
class CEikScrollBarFrameExtension;

class CEikScrollBarFrame : public CBase
	{
public:	// enums
	DECLARE_TYPE_ID(0x101F8672)   

	enum TScrollBarVisibility
		{
		EOff,
		EOn,
		EAuto
		};
	enum TScrollBarType
		{
		ENormalScrollBar	=0x0,
		EArrowHead			=0x200,
		EDoubleSpan			=0x400
		};
	enum TScrollBarSide
		{
		EBottomOrRight		=0x0,
		ETopOrLeft			=0x800
		};

	enum TScrollBarManagement 
		{
		EComponent					,//=SLafScrollBarFrame::EComponent,
		EFloating					,//=SLafScrollBarFrame::EFloating,
		EApplicationScrollBar		//=SLafScrollBarFrame::EApplicationScrollBar
		};

	enum TScrollBarFrameFlags
		{
		EHVisible			=0x01,
		EVVisible			=0x02,
		};
private:
	enum TMarginsAdjustmentMode
		{
		EGrow,
		EShrink
		};

public:	// specific
	CEikScrollBarFrame(){}
	IMPORT_C CEikScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool aPreAlloc=EFalse);
	IMPORT_C ~CEikScrollBarFrame();

	// drawing

   /**
    * Forces any scroll bars, and the corner window if it is visible, to be redrawn.
    */     
	IMPORT_C void DrawScrollBarsNow() const;

	// scrollbar visibility functions
	
   /**
    * Sets the visibility state for both the horizontal and the vertical scroll bars. This is used when tiling.
    */     
    IMPORT_C void SetScrollBarVisibilityL(TScrollBarVisibility aHVisibility, TScrollBarVisibility aVVisibility);

   /**
    * Usage of this method has been deprecated. 
    * Method CEikScrollBarFrame::ScrollBarVisibility(CEikScrollBar::TOrientation aOrientation)
    * can be used instead.
    *
    * @deprecated 
    */     
    inline TScrollBarVisibility HScrollBarVisibility() const;
	
   /**
    * Determines the vertical scroll bar’s visibility. 
    * CEikScrollBarFrame::ScrollBarVisibility(CEikScrollBar::TOrientation aOrientation) can be used instead
    * of this method.
    * 
    * @return Visibility for vertical scroll bar.
    *
    */     
    inline TScrollBarVisibility VScrollBarVisibility() const;

	// scrollbar dimming

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
	IMPORT_C void SetScrollBarsDimmed(TBool aHorizDimmed, TBool aVertDimmed) const;

	// Set scrollbar observers

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
	IMPORT_C void SetScrollBarFrameObserver(MEikScrollBarObserver* aObserver);

	// Model setting. 
	
   /**
    * Set the vertical scrollbar mode. Does not actually draw anything until 
    * the thumb or focus setting functions are called.
    *
    * @param    aVModel Model for the vertical scrollbar.
    * @return   ETrue if the non-constant rectangle is adjusted, otherwise EFalse.
    *  
    */     
    IMPORT_C TBool Tile(TEikScrollBarModel* aVModel);
	
   /**
    * Tiles the client area and the scroll bars managed by the frame. 
    * The scroll bars are set up according to the scroll bar models; aHModel and aVModel. 
    * Ownership is not transferred as a result of passing these parameters as pointers. 
    * The result of tiling geometry management is observable through the two rectangles 
    * aClientRect and aInclusiveRect. Depending on the tiling layout aLayout and the scroll bar 
    * visibility settings, either of these rectangles can be made constant and the other 
    * rectangle adjusted accordingly.
    *
    *    
    * @param aHModel Horizontal scroll bar model.
    * @param aVModel Vertical scroll bar model.
    * @param aClientRect Client rectangle.
    * @param aInclusiveRect A rectangle that includes the area to be scrolled and the scroll bars themselves.
    * @param aLayout Tiling layout.
    * @return ETrue if the non-constant rectangle is adjusted, otherwise EFalse.
    *
    * For EArrowhead type scrollbar the layout is always fixed, it cannot be altered by using this method.
    *
    * For EDoublespan type scrollbar the layout can be set also with two helper methods from
    * the AknLayoutUtils class:
    *
    *   - AknLayoutUtils::LayoutVerticalScrollBar(CEikScrollBarFrame* aScrollBarFrame, const TRect& aControlParent, const TAknWindowLineLayout& aLayout);
    *   - AknLayoutUtils::LayoutHorizontalScrollBar(CEikScrollBarFrame* aScrollBarFrame, const TRect& aControlParent, const TAknWindowLineLayout& aLayout);
    *
    */     
    IMPORT_C TBool TileL(TEikScrollBarModel* aHModel, TEikScrollBarModel* aVModel,
			  TRect& aClientRect, TRect& aInclusiveRect, const TEikScrollBarFrameLayout& aLayout);
	
	// move scrollbar thumbs functions
	
   /**
    * Moves the scroll bar thumbs by the specified amounts. This updates the scroll bars after 
    * an external scroll. The values of the parameters should be supplied in terms of the horizontal 
    * and vertical scrolling models respectively. The scrolling models are presumed not to have 
    * changed spans.
    *
    * @param aDeltaX The amount to move the horizontal scroll bar.
    * @param aDeltaY The amount to move the vertical scroll bar.
    *
    */     
    IMPORT_C void MoveThumbsBy(TInt aDeltaX, TInt aDeltaY);

   /**
    * Moves the horizontal scroll bar thumb to the position aThumbPos. 
    * This function is used to update the scroll bar after an external scroll. 
    * The value of aThumbPos should be supplied in terms of the scrolling model, which is presumed not 
    * to have changed spans.
    * 
    * @param aHorizThumbPos The required thumb position.
    *
    */     
	IMPORT_C void MoveHorizThumbTo(TInt aHorizThumbPos);

   /**
    * Moves the vertical scroll bar thumb to the position aThumbPos. 
    * This function is used to update the scroll bar after an external scroll. 
    * The value of aThumbPos should be supplied in terms of the scrolling model, which is presumed not 
    * to have changed spans.
    * 
    * @param aVertThumbPos The required thumb position.
    *
    */     
    IMPORT_C void MoveVertThumbTo(TInt aVertThumbPos);

   /**
    * Moves the vertical scroll bar thumb to the position aFocusPosition. 
    * This function is used to update the scroll bar after an external scroll. 
    * The value of aFocusPosition should be supplied in terms of the scrolling model, 
    * which is presumed not to have changed spans.
    * 
    * @param aFocusPosition The required thumb position.
    */     
    IMPORT_C void SetVFocusPosToThumbPos(TInt aFocusPosition);

   /**
    * Returns the breadth of the scroll bar idenitified by aOrientation, or zero if none exists.
    *
    * @param  aOrientation The orientation of the scroll bar for which you wish to obtain the breadth.
    * @retrun The specified scroll bar's breadth. This is zero if none exists.
    *
    */     
 	IMPORT_C TInt ScrollBarBreadth(CEikScrollBar::TOrientation aOrientation) const;

	// scroll bar frame behavior functions

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C void SetAdjustsHorizontalModel(TBool aAdjusts); 

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C void SetAdjustsVerticalModel(TBool aAdjusts);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TBool AdjustsHorizontalModel() const;

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TBool AdjustsVerticalModel() const;

    // scrollbar flags functions

   /**
    * Sets scrollbar frame flags. 
    *
    * @param aMask bitmask of bits that are to be set.
    *
    */     
    inline void SetScrollBarFrameFlags(TInt aMask);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    inline void SetFlagsForHScrollBar(TInt aMask);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    inline void SetFlagsForVScrollBar(TInt aMask);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    inline void ClearFlagsForHScrollBar(TInt aMask);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    inline void ClearFlagsForVScrollBar(TInt aMask);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    inline TInt FlagsForHScrollBar() const;

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    inline TInt FlagsForVScrollBar() const;
	
   /**
    * Determines whether the scroll bar specified by aOrientation exists
    * 
    * @param aOrientation The scroll bar’s orientation.
    * @return ETrue if the specified scroll bar exists.EFalse if the specified scroll bar does not exist.
    *
    */     
    IMPORT_C TBool ScrollBarExists(CEikScrollBar::TOrientation aOrientation) const;

	// component control functions

   /**
    * Gets the number of controls contained in a compound control.
    * 
    * @return The number of component controls contained in this control.
    *
    */     
    IMPORT_C TInt CountComponentControls() const;
	
   /**
    * Gets the component specified by index. Within a compound control, each component 
    * control is identified by an index, where the index depends on the order the controls were added: 
    * the first is given an index of 0, the next an index of 1, and so on.
    * 
    * @return The component control with an index of aIndex
    */         
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	
   /**
    * Returns a pointer to the scroll bar identified by orientation aOrientation.
    * 
    * @param aOrientation The orientation of the scroll bar for which you wish to obtain a pointer.
    * @return A pointer to the scroll bar with orientation aOrientation if the scrollbar is visible.
    */         
    IMPORT_C CEikScrollBar* GetScrollBarHandle(CEikScrollBar::TOrientation aOrientation) const;
	
   /**
    * Returns a pointer to the vertical scroll bar.
    * 
    * @return A pointer to the vertical scroll bar.
    */         
    IMPORT_C CEikScrollBar* VerticalScrollBar() const;
	
   /**
    * Sets the type of horizontal scroll bar. Possible values are
    * EArrowHead and EDoubleSpan.
    *
    * @param aType Type of the scrollbar.
    * 
    */         
    IMPORT_C void SetTypeOfHScrollBar(TScrollBarType aType);
    
   /**
    * Sets the type of vertical scroll bar. Possible values are
    * EArrowHead and EDoubleSpan.
    *
    * @param aType Type of the scrollbar.
    * 
    */         
   	IMPORT_C void SetTypeOfVScrollBar(TScrollBarType aType);
	
   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C void SetSideOfHScrollBar(TScrollBarSide aSide);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
	IMPORT_C void SetSideOfVScrollBar(TScrollBarSide aSide);
	
   /**
    * Returns the control type of the horizontal scroll bar 
    * 
    * @return Type of the scrollbar.
    */         
    IMPORT_C TScrollBarType TypeOfHScrollBar() const;

   /**
    * Returns the control type of the vertical scroll bar 
    * 
    * @return Type of the scrollbar.
    */         
	IMPORT_C TScrollBarType TypeOfVScrollBar() const;

    
   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TBool RightSideForHScrollBar() const;

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TBool RightSideForVScrollBar() const;

   /**
    * Checks if the vertical scrollbar type is EArrowHead.
    *
    * @param aFlag  A dummy parameter.
    * @return ETrue if the type of the scrollbar is EArrowHead.
    */         
    IMPORT_C TBool IsArrowHeadScrollBar(TInt aFlag) const;

	// application scroll bar utilities

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C static void SetApplicationScrollBarL(CEikScrollBar::TOrientation aOrientation, CEikScrollBar* aScrollBar);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
	IMPORT_C static CEikScrollBar* ApplicationScrollBar(CEikScrollBar::TOrientation aOrientation);

	// scroll bar attributes functions
	
   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C void SetScrollBarManagement(CEikScrollBar::TOrientation aOrientation, TScrollBarManagement aManagement);
	
   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TScrollBarManagement ScrollBarManagement(CEikScrollBar::TOrientation aOrientation) const;

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C void SetScrollBarControlType(CEikScrollBar::TOrientation aOrientation, TInt aControlType);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TInt ScrollBarControlType(CEikScrollBar::TOrientation aOrientation) const;

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C void SetScrollBarSide(CEikScrollBar::TOrientation aOrientation, TScrollBarSide aSide);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TScrollBarSide ScrollBarSide(CEikScrollBar::TOrientation aOrientation) const;

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C void SetScrollBarBreadth(CEikScrollBar::TOrientation aOrientation, TInt aBreadth);

   /**
    * Usage of this method has been deprecated.
    *
    * @deprecated 
    */     
    IMPORT_C TBool AdjustsModel(CEikScrollBar::TOrientation aOrientation) const;

   /**
    * This method is used only internally by the CEikScrollBar. Disconnects externally
    * connected scrollbar.
    * 
    * @param aScrollBar scrollbar to be disconnected.
    */     
	void DisconnectExternalScrollBar(CEikScrollBar* aScrollBar);

   /**
    * This method creates double span type scrollbars into this frame. Old scrollbars are
    * deleted or disconnected.
    *
    *
    * @since    2.6
    * @param    aWindowOwning     Tells wheter created scrollbar should be a window owning 
    *                             control or not. Selection for this is relevant especially
    *                             because skinned scrollbar draws its background using its
    *                             parent windows background context.
    *                             
    * @param    aRemote           True if this method should instead of creating own scrollbar 
    *                             try to connect to a remote scrollbar frame and start using its 
    *                             scrollbars. Connecting is done using through object 
    *                             provider mechanism, so the object supply chain 
    *                             must be valid. Also if true, then parameter aWindowOwning
    *                             will be ignored.
    *
    *   Example of use:
    *
    *    iSBFrame=new(ELeave) CEikScrollBarFrame(this, NULL, ETrue);
    *    iSBFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);
    *    iSBFrame->CreateDoubleSpanScrollBarsL(ETrue, EFalse);
    *
    *    // Note that double span scrollbar types requires different model classes to be used in places of 
    *    // TEikScrollBarModel of this scrollbar frame API:s other method calls.
    *    // 
    *    // Scrollbar type                            Required model (in places of TEikScrollBarModel)
    *    // -------------------------                 ------------------------------------------------
    *    // EDoubleSpan                               TAknDoubleSpanScrollBarModel 
    *    // EArrowHead                                TEikScrollBarModel
    *
    *
    *   TAknDoubleSpanScrollBarModel vModel; // model for double span type scrollbar
    *   TAknDoubleSpanScrollBarModel hModel; // model for double span type scrollbar
    *   
    *   iSBFrame->Tile(vModel, iVRect);
    *
    */ 
    IMPORT_C void CreateDoubleSpanScrollBarsL(TBool aWindowOwning, TBool aRemote);
    
   /**
    * This method creates double span type scrollbars into this frame. Old scrollbars are
    * deleted or disconnected.
    *
    *
    * @since    2.8
    * @param    aWindowOwning     Tells wheter created scrollbar should be a window owning 
    *                             control or not. Selection for this is relevant especially
    *                             because skinned scrollbar draws its background using its
    *                             parent windows background context.
    *                             
    * @param    aRemote           True if this method should instead of creating own scrollbar 
    *                             try to connect to a remote scrollbar frame and start using its 
    *                             scrollbars. Connecting is done using through object 
    *                             provider mechanism, so the object supply chain 
    *                             must be valid. Also if true, then parameter aWindowOwning
    *                             will be ignored.
    *
    * @param    aVertical         If ETrue vertical scrollbar will be created to scrollbar frame.
    * @param    aHorizontal       If ETrue horizontal scrollbar will be created to scrollbar frame.
    *
    */ 
    IMPORT_C void CreateDoubleSpanScrollBarsL(TBool aWindowOwning, TBool aRemote, TBool aVertical, TBool aHorizontal);

    /**
    * Tiles the vertical EDouble span type scroll bar managed by the frame. The scroll 
    * bar is set up according to the scroll bar model and given rectangle which is
    * relative to the parent window of the frame.
    *
    * @since    2.6
    * @param    aVModel           Vertical scrollbar model.         
    * @param    aVScrollBar       Vertical scrollbar rectangle.            
    *
    * For EDoublespan type scrollbar the layout can be set also with a helper method from
    * the AknLayoutUtils class:
    *
    *   - AknLayoutUtils::LayoutVerticalScrollBar(CEikScrollBarFrame* aScrollBarFrame, const TRect& aControlParent, const TAknWindowLineLayout& aLayout);
    *
    */     
    IMPORT_C void Tile(TEikScrollBarModel* aVModel, TRect& aVScrollBar);

    /**
    * Sets the models of the scrollbars. 
    * 
    * @since    2.6
    * @param    aHModel  The model of the horizontal scrollbar.
    * @param    aVModel  The model of the vertical scrollbar.
    *
    */     
	IMPORT_C void Tile(TEikScrollBarModel* aHModel, TEikScrollBarModel* aVModel);

    /**
    * Returns the visibility of given scrollbar orientation. 
    * 
    * This method should be used instead of a deprecated method 
    * CEikScrollBarFrame::HScrollBarVisibility() and
    * also can be used instead of CEikScrollBarFrame::VScrollBarVisibility().
    *
    * @since    2.6
    * @param    aOrientation  the orientation of a scrollbar in the frame.
    * @return   The visibility of requested scrollbar.
    *
    */     
	IMPORT_C TScrollBarVisibility ScrollBarVisibility(CEikScrollBar::TOrientation aOrientation) const;

public:

   /**
    * Returns a pointer to the horizontal scroll bar.
    * 
    * @return A pointer to the horizontal scroll bar.
    */         
    CEikScrollBar* HorizontalScrollBar() const;

protected:
	// Accessor methods
	void SetParentWindow(CCoeControl* aParentWindow);
	CCoeControl* ParentWindow() const;

protected:
	struct SBarData
		{
		CAknScrollBar* iBar;
		TEikScrollBarModel iModel;
		TScrollBarVisibility iVisibility;
		TBool iExternalScrollBarAttached;
		};

private:
	void CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aVModel);
	void ApplyModel(SBarData& aSBar);
	void MakeSBarVisible(SBarData& aSBar, TBool aVisible);
	void GetScrollBars();
	CEikCba* GetCurrentCba();
    void DeleteScrollBars();
    void CreateArrowHeadScrollBarsL();

    void CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aVModel, const TEikScrollBarModel* aHModel);

protected:
	SBarData iV;

private:
    CEikScrollBarFrameExtension* iExtension; 
    TInt iScrollBarFrameFlags;

    friend class CEikScrollBarFrameExtension;
	};

inline CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::HScrollBarVisibility() const
    { return EOff; } // Deprecated
inline CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::VScrollBarVisibility() const
	{ return iV.iVisibility; }
inline void CEikScrollBarFrame::SetScrollBarFrameFlags(TInt aMask)
	{ iScrollBarFrameFlags|=aMask; }
inline void CEikScrollBarFrame::SetFlagsForHScrollBar(TInt /*aMask*/)
	{ }
inline void CEikScrollBarFrame::SetFlagsForVScrollBar(TInt /*aMask*/)
	{ }
inline void CEikScrollBarFrame::ClearFlagsForHScrollBar(TInt /*aMask*/)
	{ }
inline void CEikScrollBarFrame::ClearFlagsForVScrollBar(TInt /*aMask*/)
	{ }
inline TInt CEikScrollBarFrame::FlagsForHScrollBar() const
	{ return 0; }
inline TInt CEikScrollBarFrame::FlagsForVScrollBar() const
	{ return 0; }



// Cba scroll bar frame (with it's own scrollbar creation methods)
class CEikCbaScrollBarFrame : public CEikScrollBarFrame
	{
public:
	CEikCbaScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool aPreAlloc=EFalse);
	void ConstructL();
	};

#endif
