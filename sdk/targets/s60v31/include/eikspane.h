// EIKSPANE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSPANE_H__)
#define __EIKSPANE_H__

#if !defined(__EIKSPMOD_H__)
#include <eikspmod.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

class CCoeBrushAndPenContext;
class CEikStatusPaneContainer;
class TEikStatusPaneSyncDrawer;
class CEikStatusPaneBaseExtension;
class CAknStatuspaneClearer;
class CAknDelayedForegroundObserver;

const TInt KStatusPaneCapsPresentBit = 1;
const TInt KStatusPaneCapsAppOwnedBit = 2;
const TInt KStatusPaneCapsInCurrentLayoutBit = 4;


/**
 * The MEikStatusPaneObserver interface allows a status pane observer to pick 
 * up changes in the size or position of the status pane. Such events will be
 * as a result of layout changes which cause an actual change in the status 
 * pane rectangle.
 */
class MEikStatusPaneObserver
	{
public:
	virtual void HandleStatusPaneSizeChange() = 0;
	};

/**
 * The base class for status panes.
 */
class CEikStatusPaneBase : public CBase
	{

public:

    /**
     * Describes the capabilities of a subpane.
     */
    class TPaneCapabilities
        {

    public:
        
        /**
         * Constructor.
         */
        TPaneCapabilities();
        
        /**
         * Tests whether the subpane exists in the status pane.
         * 
         * @return @c ETrue if the subpane exists and can be used by the
         *            application, even if the subpane is not visible.
         */
        inline TBool IsPresent() const;
        
        /**
         * Tests whether the pane is owned by the application or the server. 
         * Applications can only interact directly with application owned
         * subpanes.
         *
         * @return @c ETrue if the subpane is owned by the application.
         */
        inline TBool IsAppOwned() const;
        
        /**
         * Tests if this pane is part of the current status pane layout.
         *
         * @return @c ETrue if pane is part of the current status pane layout.
         */
        inline TBool IsInCurrentLayout() const;

    private:

        inline void SetPresent();
        inline void SetAppOwned();
        inline void SetInCurrentLayout();

    private:

        TInt iFlags;

    private:

        friend class CEikStatusPaneBase;
        };

public:

    /**
     * Destructor.
     */
    IMPORT_C ~CEikStatusPaneBase();

    /**
     * Gets a pointer to the thread's currently active status pane
     * without transferring ownership. 
     *
     * @return Pointer to currently active status pane. Returns NULL if no such
     *         pane exists.
     */
    IMPORT_C static CEikStatusPaneBase* Current();
	
    /**
     * Sets the status pane observer.
     *
     * @param aObserver Pointer to status pane observer.
     */
    inline void SetObserver(MEikStatusPaneObserver* aObserver);
	
    /**
     * Modifies the bounding rectangle so that it lies next to the
     * status pane rectangle.
     *
     * The status pane always places itself along the edge of the screen, so 
     * that it is consistent across applications and the server. It is 
     * assumed that the given bounding rectangle does not extend beyond 
     * the screen area.
     *
     * @param[in,out] aBoundingRect The bounding rectangle.
     */
    IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
	
    /**
     * Adds and removes pane rectangles from @c aRegion.
     *
     * @param aRegion The two-dimensional area from where rectangles are
     *        removed from or where rectangles are added to.
     * @param aIncludeAppPanes If @c ETrue, app panes are added, otherwise 
     *        removed.
     * @param aIncludeServerPanes If @c ETrue, server panes are added, 
     *        otherwise removed.
     */
    IMPORT_C void GetShapeL(TRegion& aRegion, 
                            TBool aIncludeAppPanes, 
                            TBool aIncludeServerPanes) const;

    /**
     * Switchs to the specified status pane layout.
     * @param aLayoutResourceId Layout resource Id. This must be one of the 
     *        layouts identified in the status pane resource structures, 
     *        otherwise the function leaves @c KErrNotFound.
     * @leave KErrNotFound The specified layout does not exist in the status 
     *        pane resource structures.
     */
    IMPORT_C virtual void SwitchLayoutL(TInt aLayoutResourceId);
	
    /**
     * Sets the visiblility of the status pane and its contents.
     *
     * @param aVisible If @c ETrue the status pane and its contents are set to 
     *        visible.
     */
    IMPORT_C virtual void MakeVisible(TBool aVisible);
	
    /**
     * Sets the status pane and its contents to dimmed state.
     *
     * @param aDimmed If @c ETrue the status pane and its contents are set to 
     *        dimmed state.
     */
    IMPORT_C virtual void SetDimmed(TBool aDimmed);
	
    /**
     * Not implemented.
     *
     * @param aFaded Not used.
     */
    IMPORT_C virtual void SetFaded(TBool aFaded);
	
    /**
     * Handles changes in resources which are shared across the environment. 
     * This function responds to the changes in resources by propagating them
     * to sub-parts of the status pane.
     *
     * @param aType A message type.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);
	
    /**
     * Returns always @c ETrue. 
     *
     * @return Always @c ETrue.
     */
    IMPORT_C virtual TBool OkToChangeStatusPaneNow();

    /**
     * Sets all the visual flags at once (@c KEikStatusPaneBaseVisibleBitdimmed
     * and @c KEikStatusPaneBaseDimmedBit).
     * 
     * @param aFlags Flags to be set.
     */
    IMPORT_C void SetFlags(TInt aFlags);
	
    /**
     * Gets status pane settings.
     *
     * @return Flags used by status pane base class.
     */
    IMPORT_C TInt Flags() const;
	
    /**
     * Gets the visibility of the status pane.
     * 
     * @return @c ETrue if the status pane is visible.
     */
    IMPORT_C TBool IsVisible() const;
	
    /**
     * Gets the dimmed state of the status pane.
     * 
     * @return @c ETrue if the status pane is dimmed.
     */
    IMPORT_C TBool IsDimmed() const;
	
    /**
     * Gets the fade status of the status pane.
     * 
     * @return @c ETrue if status pane is faded.
     */
    IMPORT_C TBool IsFaded() const;

    /**
     * Gets the capabilities of the status pane.
     * 
     * @param aPaneId Status pane id.
     * @return Status pane capabilities.
     */
    IMPORT_C TPaneCapabilities PaneCapabilities(TPaneId aPaneId) const;
	
    /**
     * Provides the screen rectangle of a sub pane.
     * This can be used to set the size of a new control which you want 
     * to place in the status pane.
     * 
     * @param aPaneId Status pane id.
     * @return The sub pane rectangle.
     * @leave KErrNotFound The subpane ID is not valid.
     */
    IMPORT_C TRect PaneRectL(TPaneId aPaneId) const;
	
    /**
     * Provides the control currently inside a sub pane.
     * This gives the application direct access to the contents of a pane.
     *
     * @param aPaneId The status pane id.
     * @return Pointer to the control instance inside of the sub pane.
     * @leave KErrNotFound The subpane ID is not valid.
     */
    IMPORT_C CCoeControl* ControlL(TPaneId aPaneId) const;
	
    /**
     * Swaps the control currently inside a sub pane.
     * The new control must be a fully constructed control. It will be placed 
     * inside the status pane, and the current content will be returned to the 
     * caller. 
     * 
     * @param aPaneId ID of the subpane.
     * @param aNewControl A fully constructed control to place at @c aPaneId.
     * @return The control which was at @c aPaneId.
     * @leave KErrNotFound This can occur before ownership of the new control
     *        is taken, if the subpane ID is not valid.
     */
    IMPORT_C CCoeControl* SwapControlL(TPaneId aPaneId,
                                       CCoeControl* aNewControl);
	
    /**
     * Provides access to the container control for a sub pane.
     * You will need access to the container for a sub pane if you want 
     * to swap in a new control. The container control should be set as the 
     * parent window of the new control.
     * It also provides a fast way to get the rectangle of the sub pane 
     * (see @c PaneRect()).
     *
     * @param aPaneId Status pane ID.
     * @return Pointer to the new container control for the subpane.
     * @leave KErrNotFound The subpane ID is not valid.
     */
    IMPORT_C CCoeControl* ContainerControlL(TPaneId aPaneId) const;
	
    /**
     * Provides access to a server-side window group.
     *
     * @return Pointer to the window group.
     */
    inline RWindowGroup* WindowGroup() const;
	
    /**
     * Draws a control.
     */
    IMPORT_C void DrawNow();
	
    /**
     * Gets the resource id of the current layout.
     *
     * @return The Resource id of the current layout.
     */
    IMPORT_C TInt CurrentLayoutResId() const;

protected:

    /**
     * C++ default constructor.
     *
     * @param aEikEnv An environment for creating controls and utility 
     *        functions for manipulating them.
     * @param aParent Pointer to the parent window group.
     */
    IMPORT_C CEikStatusPaneBase(CEikonEnv& aEikEnv, RWindowGroup* aParent);
	
    /**
     * Initializes the status pane with standard values. 
     * 
     * @param aCoreResId Id for the status pane resource.
     */
    IMPORT_C void BaseConstructL(TInt aCoreResId);

    /**
     * Creates a new model for the status pane.
     *
     * @param aCoreResId Id for the status pane resource.
     * @return Pointer to the new status pane model instance.
     */
    virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const = 0;
	
    /**
     * Creates sub panes to the status pane.
     */
    void CreatePanesL();
	
    /**
     * Creates a sub pane.
     *
     * @param aPaneInit Initial values for the sub pane.
     */
    void CreatePaneL(const TEikStatusPaneInit& aPaneInit);
	
    /**
     * Gets a container of a wanted pane.
     *
     * @param aPaneId The pane id.
     * @return Pointer to the container of the pane with a given id. 
     */
    CEikStatusPaneContainer* Find(TPaneId aPaneId) const;

    /**
     *
     */
    virtual TBool IsApp() const = 0;
	
    /**
     * Gets the rectangle of the status pane.
     *
     * @return The rectangle used by the status pane.
     */
    inline TRect Rect() const;

    /**
     * Status pane drawing commands.
     */
    enum TDrawCmd 
        { 
        /** Do not draw. */
        ENoDraw, 

        /** Draw immediately. */
        EDrawNow, 
        
        /** Draw with low priority. */
        EDrawDeferred 
        };
	
    /**
     * Calls @c CCoeControl's @c DrawNow() or @c DrawDeferred() to draw the 
     * status pane. If @c aDraw is @c ENoDraw status pane is not drawed.
     * 
     * @param aDraw Status pane drawing commands.
     */
    void DoDrawNow(TDrawCmd aDraw);
	
    /**
     * Gets the status pane clearer.
     *
     * @return Pointer to the status pane clearer instance.
     */
    CAknStatuspaneClearer* Clearer();
	
    /**
     * Disables the status pane clearer. 
     *
     * @param aDisabled Disabled if @c ETrue.
     */
    IMPORT_C void DisableClearer(TBool aDisabled);
	
    /**
     * Prepares the status pane for the application exit. Clears the status
     * pane.
     */
    IMPORT_C void CommonPrepareForAppExit();

private:

    void DoSwitchLayoutL(TInt aLayoutResourceId, TDrawCmd aDraw);
    void ApplyLayoutL(CEikStatusPaneLayout* aLayout, TDrawCmd aDraw);
    void SetAllInvisible();
    void SetNotNeededInvisible();

public:
    
    /**
     * Notifies the command button area and status pane observer about the
     * status pane size change. If the status pane is an embedded application,
     * also this application is notified.
     */
    void ReportSizeChange();

private:

    class TSetRectAndVisibility : public MEikStatusPaneLayoutTreeVisitor
        {
    
    public:
    
        TSetRectAndVisibility(TBool aIsApp, CEikStatusPaneBase* aStatusPane);
        void VisitL(CEikStatusPaneLayoutTree* aNode);
    
    private:
    
        TBool iIsApp;
        CEikStatusPaneBase* iStatusPane;
        };
	
	friend class TSetRectAndVisibility;

private:

    void SetLastUsedResourceId(TInt aResourceId);
    TInt LastUsedResourceId();
    TInt ReadInitialUsedResourceIdL(TInt aCoreResId);    
    TInt InitialUsedResourceId();
    TRect LargestBoundingRect(TRegion& aWholeRegion,
                              TRegion& aRemovedRegion) const;

protected:

    /**
     * Sets the initial status pane resource id to an extension class 
     * @c CEikStatusPaneBaseExtension.
     *
     * @param aResourceId The initial status pane resource id.
     */
    void SetInitialUsedResourceId(TInt aResourceId);
	void OptimizeClearerWindowShape(TInt aOldResourceId, TInt aNewResourceId, TRegion& aRegion);

protected:

    /**
     * An environment for creating controls and utility functions for 
     * manipulating them.
     */
    CEikonEnv& iEikEnv;
	
    /**
     * Status pane model class. <br>
     * Own.
     */
    CEikStatusPaneModelBase* iModel;

    /**
     * Flags for the status pane.
     */
    TInt iFlags;

protected:

	typedef CArrayPtrFlat<CEikStatusPaneContainer> CContainerControls;
	CContainerControls* iControls;
private:
	MEikStatusPaneObserver* iObserver;
	RWindowGroup* iParentWindowGroup;
	CEikStatusPaneBaseExtension* iExtension;
	};

/**
 * CEikStatusPane is the interface through which applications use the status pane.
 * This class synchronises the status pane layout with the server side status pane
 * object. To do this, the ApplyCurrentSettingsL() method must be called whenever
 * the owner application switches to the foreground.
 */
NONSHARABLE_CLASS(CEikStatusPane) : public CEikStatusPaneBase, public MCoeForegroundObserver
	{
public:
	IMPORT_C static CEikStatusPane* NewL(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aCoreStatusPaneModelResId, TInt aAppStatusPaneModelResId=EEikStatusPaneUseDefaults);
	IMPORT_C ~CEikStatusPane();

	IMPORT_C void ApplyCurrentSettingsL();
	IMPORT_C void PrepareForAppExit();

	// from CEikStatusPaneBase
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void SetFaded(TBool aFaded);
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C virtual TBool OkToChangeStatusPaneNow();

private:
	CEikStatusPane(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aAppStatusPaneModelId);
	void ConstructL(TInt aCoreStatusPaneModelResId);

	virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const;
	TBool IsApp() const;

	void ApplyCurrentFlags();
	void HideAppPanes(TBool aHide);

private: // from MCoeForegroundObserver
	void HandleGainingForeground();
	void HandleLosingForeground();
private:	
    TInt ReadInitialUsedResourceIdL(TInt aCoreResId, TInt aAppStatusPaneModelResId);
    void DoHandleLosingForegroundL();

private:
	TInt iAppDeclId;
	TEikStatusPaneSyncDrawer* iSyncDrawer;	// formerly CPeriodic* iTimer;
	CAknDelayedForegroundObserver*iDelayedForegroundObserver;	// formerly iServerSpWgId;
	};






/**
 * Does the pane exist in this status pane?
 * Note: this will return true if the pane can be used, even if it is not visible.
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsPresent() const { return iFlags & KStatusPaneCapsPresentBit; }
/**
 * Is this pane owned by applications rather than the server?
 * Applications can only interact directly with application owned panes.
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsAppOwned() const { return iFlags & KStatusPaneCapsAppOwnedBit; }
/**
 * Is this pane part of the current status pane layout?
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsInCurrentLayout() const { return iFlags & KStatusPaneCapsInCurrentLayoutBit; }
/**
 * Set the status pane observer.
 */
inline void CEikStatusPaneBase::SetObserver(MEikStatusPaneObserver* aObserver) { iObserver = aObserver; }
inline TRect CEikStatusPaneBase::Rect() const { return iModel->CurrentLayout()->Rect(); }
inline RWindowGroup* CEikStatusPaneBase::WindowGroup() const { return iParentWindowGroup; }

#endif
