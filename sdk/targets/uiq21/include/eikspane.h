// EIKSPANE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSPANE_H__)
#define __EIKSPANE_H__

#include <eikspmod.h>
#include <coecntrl.h>
#include <coecobs.h>

class CCoeBrushAndPenContext;
class CEikStatusPaneContainer;

const TInt KStatusPaneCapsPresentBit = 1;
const TInt KStatusPaneCapsAppOwnedBit = 2;
const TInt KStatusPaneCapsInCurrentLayoutBit = 4;

/**
 *
 * Enables the owner of the screen contents (the application user
 * interface) to pick up changes in the size of the status pane.
 *
 * As a result, applications may have to resize other components placed
 * on the screen.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class MEikStatusPaneObserver
	{
public:
	/**
	 * Handles a change in the position or size of the screen area occupied
	 * by the status pane.
	 *
	 * This may be as a result of changes in layout or visibility and usually
	 * requires other screen furniture and the top level control to be
	 * redrawn.
	 */
	virtual void HandleStatusPaneSizeChange() = 0;
	};

/**
 *
 * The base class for the concrete status pane class
 * <code>CEikStatusPane</code>.
 *
 * This class is not intended for user derivation.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikStatusPaneBase : public CBase
	{
public:
	/**
	 *
	 * Describes the capabilities of a subpane.
	 * @lib "eikcoctl.lib"
	 */
	class TPaneCapabilities
		{
	public:
		TPaneCapabilities();
		inline TBool IsPresent() const;
		inline TBool IsAppOwned() const;
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
	IMPORT_C ~CEikStatusPaneBase();

	IMPORT_C static CEikStatusPaneBase* Current();
	
	inline   void SetObserver(MEikStatusPaneObserver* aObserver);
	IMPORT_C void ReduceRect(TRect& aBoundingRect) const;

	IMPORT_C virtual void SwitchLayoutL(TInt aLayoutResourceId);
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void SetFaded(TBool aFaded);
	IMPORT_C virtual void HandleResourceChange(TInt aType);

	IMPORT_C void SetFlags(TInt aFlags);
	IMPORT_C TBool IsVisible() const;
	IMPORT_C TBool IsDimmed() const;
	IMPORT_C TBool IsFaded() const;

	IMPORT_C TPaneCapabilities PaneCapabilities(TPaneId aPaneId) const;
	IMPORT_C TRect PaneRectL(TPaneId aPaneId) const;
	IMPORT_C CCoeControl* ControlL(TPaneId aPaneId) const;
	IMPORT_C CCoeControl* SwapControlL(TPaneId aPaneId, CCoeControl* aNewControl);
	IMPORT_C CCoeControl* ContainerControlL(TPaneId aPaneId) const;
	inline RWindowGroup* WindowGroup() const;
	IMPORT_C void GetShapeL(TRegion& aRegion, TBool aIncludeAppPanes, TBool aIncludeServerPanes) const;

protected:
	IMPORT_C CEikStatusPaneBase(CEikonEnv& aEikEnv, RWindowGroup* aParent);
	IMPORT_C void BaseConstructL(TInt aCoreResId);

	virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const = 0;
	void CreatePanesL();
	void CreatePaneL(const TEikStatusPaneInit& aPaneInit);
	CEikStatusPaneContainer* Find(TPaneId aPaneId) const;

	virtual TBool IsApp() const = 0;
	inline TRect Rect() const;

private:
	void ApplyLayoutL(CEikStatusPaneLayout* aLayout);
	void SetAllInvisible();
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

protected:
	CEikonEnv& iEikEnv;
	CEikStatusPaneModelBase* iModel;

	TInt iFlags;

private:
	typedef CArrayPtrFlat<CEikStatusPaneContainer> CContainerControls;
	CContainerControls* iControls;
	MEikStatusPaneObserver* iObserver;
	RWindowGroup* iParentWindowGroup;
	TInt iSpbSpare;
	};

/**
 *
 * Client-side view of the status pane.
 *
 * Status panes are server-side objects; this class synchronises the
 * server-side status pane layout with the applications status pane
 * layout. Synchronisation is necessary as the server may need to change
 * its status pane to reflect changes made by an application to its
 * status pane.To ensure status pane synchronisation, an application must
 * call the <code>ApplyCurrentSettingsL()</code> method whenever it
 * switches to the foreground.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikStatusPane : public CEikStatusPaneBase, public MCoeForegroundObserver
	{
public:
	IMPORT_C static CEikStatusPane* NewL(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aCoreStatusPaneModelResId, TInt aAppStatusPaneModelResId=EEikStatusPaneUseDefaults);
	IMPORT_C ~CEikStatusPane();

	IMPORT_C void ApplyCurrentSettingsL();

	// from CEikStatusPaneBase
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void SetFaded(TBool aFaded);
	IMPORT_C virtual void HandleResourceChange(TInt aType);

private:
	CEikStatusPane(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aAppStatusPaneModelId);
	void ConstructL(TInt aCoreStatusPaneModelResId);

	virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const;
	TBool IsApp() const;

	void ApplyCurrentFlags();
	void DoHandleGainingForegroundL();
	static TInt TimerCallBackL(TAny* aPtr);

private: // from MCoeForegroundObserver
	void HandleGainingForeground();
	void HandleLosingForeground();
	TBool IsForeground();

private:
	TInt iAppDeclId;
	CPeriodic* iTimer;
	};


/**
 * Tests whether the subpane exists in the status pane.
 *
 * This returns true if the subpane can be used, even if it is not
 * visible.
 *
 * @returns   "TBool"
 *            If <code>ETrue</code>, the subpane exists in the
 *            status pane and can be used by the application.
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsPresent() const { return iFlags & KStatusPaneCapsPresentBit; }

/**
 * Tests whether the pane is owned by the application or the server.
 *
 * Applications can only interact directly with application owned
 * subpanes.
 *
 * @returns   "TBool"
 *            If <code>ETrue</code>, the subpane is owned by the
 *            application.
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsAppOwned() const { return iFlags & KStatusPaneCapsAppOwnedBit; }
/**
 * Is this pane part of the current status pane layout?
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsInCurrentLayout() const { return iFlags & KStatusPaneCapsInCurrentLayoutBit; }

/**
 * Sets the status pane observer.
 *
 * This function allows an observer of the status pane to register itself
 * to be notified about changes to the size of the status pane. The
 * observer must implement the
 * <code>MEikHandleStatusPaneSizeChange()</code> function.
 *
 * @param     "MEikStatusPaneObserver* aObserver"
 *            The status pane observer.
 */
inline void CEikStatusPaneBase::SetObserver(MEikStatusPaneObserver* aObserver) { iObserver = aObserver; }
inline TRect CEikStatusPaneBase::Rect() const { return iModel->CurrentLayout()->Rect(); }
inline RWindowGroup* CEikStatusPaneBase::WindowGroup() const { return iParentWindowGroup; }

#endif
