/*
* ==============================================================================
*  Name        : eikspane.h
*  Part of     : CKON
*  Interface   : Indicator API
*  Description : MEikStatusPaneObserver enables the owner of the screen contents
*				 to pick up changes in the size of the status pane.
*				 CEikStatusPaneBase is the base class for the concrete status pane class CEikStatusPane.
*				 CEikStatusPane synchronises the server-side status pane with 
*				 the applications status pane layout.
*  Version     : 1.0
*
*  Copyright (c) 2002 Nokia Corporation.
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


#ifndef EIKSPANE_H
#define EIKSPANE_H


// INCLUDES
#include <eikspmod.h>
#include <coecntrl.h>
#include <coecobs.h>

// FORWARD DECLARATIONS
class CCoeBrushAndPenContext;
class CEikStatusPaneContainer;

// DATA TYPES

const TInt KStatusPaneCapsPresentBit = 1;
const TInt KStatusPaneCapsAppOwnedBit = 2;
const TInt KStatusPaneCapsInCurrentLayoutBit = 4;

// CLASS DECLARATIONS

/**
 *
 * Enables the owner of the screen contents (the application user
 * interface) to pick up changes in the size of the status pane.
 *
 * As a result, applications may have to resize other components placed
 * on the screen.
 *
 * Link against eikcoctl.lib
 * @since ?Series90_version
 */
class MEikStatusPaneObserver
	{
	public:
	// New methods
		/**
	 	* Handles a change in the position or size of the screen area occupied
		* by the status pane.
		*
	 	* This may be as a result of changes in layout or visibility and usually
		* requires other screen furniture and the top level control to be
		* redrawn.
		* @since ?Series90_version
		* <BR><B>Type of return value:</B> void
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
 * Link against eikcoctl.lib
 * @since ?Series90_version
 */
class CEikStatusPaneBase : public CBase
	{
	public:  // Declarations
	/**
	 *
	 * Describes the capabilities of a subpane.
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
	// Constructors and destructor
		/**
		* Destructor.
		*/
		IMPORT_C ~CEikStatusPaneBase();

	// New methods
        
		/**
		* Returns a pointer to the thread's currently active status pane
		* without transferring ownership.  Returns NULL is no such pane exists.
		* @since ?Series90_version
		* @return Pointer CEikStatusPaneBase*
		* <BR><B>Type of return value:</B> CEikStatusPaneBase*
		*/
		IMPORT_C static CEikStatusPaneBase* Current();
	
		/**
		* Sets the status pane observer.
		* @since ?Series90_version
		* @param aObserver The status pane observer
		* <BR><B>Type of return value:</B> void
		*/
		inline   void SetObserver(MEikStatusPaneObserver* aObserver);
		/**
		* Modifies the bounding rectangle passed in so that the application's
		* main window area lies next to the status pane rectangle.
		* @since ?Series90_version
		* @param aBoundingRect Rectangle to be modified
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ReduceRect(TRect& aBoundingRect) const;

		/**
		* Changes the entire status pane layout to the one specified in the resource.
		* @since ?Series90_version
		* @param aLayoutResourceId Resource ID for the layout
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void SwitchLayoutL(TInt aLayoutResourceId);
		/**
		* Sets the visibility of the status pane and its contents.
		* @since ?Series90_version
		* @param aVisible If <code>ETrue</code>, the status pane is drawn.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void MakeVisible(TBool aVisible);
		/**
		* Sets the dimmed state of the status pane and its contents.
		* @since ?Series90_version
		* @param aDimmed If <code>ETrue</code>, the status pane is dimmed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void SetDimmed(TBool aDimmed);
		/**
		* Sets the faded state of the status pane and its contents.
		* @since ?Series90_version
		* @param aFaded If <code>ETrue</code>, the status pane is drawn faded.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void SetFaded(TBool aFaded);
		/**
		* Handles changes in resources which are shared across the environment.
		* @since ?Series90_version
		* @param aType Message type
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);

		/**
		* Sets all the <code>CCoeControl</code> visual flags at once (faded,dimmed and visible).
		* @since ?Series90_version
		* @param aFlags A bitwise OR of visual flags.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetFlags(TInt aFlags);
		/**
		* Tests whether the status pane is visible.
		* @since ?Series90_version
		* @return <code>ETrue</code> if the status pane is visible.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool IsVisible() const;
		/**
		* Test whether the status pane is dimmed.
		* @since ?Series90_version
		* @return <code>ETrue</code> if the status pane is dimmed
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool IsDimmed() const;
		/**
		* Tests whether the status pane is faded.
		* @since ?Series90_version
		* @return <code>ETrue</code> if the status pane is faded.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool IsFaded() const;

		/**
		* Gets the capabilities of a subpane.
		* @since ?Series90_version
		* @param aPaneId ID of the subpane
		* @return Set of flags indicating whether the subpane is:
		* present, part of the current status pane layout, owned by an application.
		* <BR><B>Type of return value:</B> TPaneCapabilities
		*/
		IMPORT_C TPaneCapabilities PaneCapabilities(TPaneId aPaneId) const;
		/**
		* Gets the size and location of a subpane.
		* @since ?Series90_version
		* @param aPaneId ID of the subpane.
		* @return The subpane's size and position inside the status pane.
		* <BR><B>Type of return value:</B> TRect
		*/
		IMPORT_C TRect PaneRectL(TPaneId aPaneId) const;
		/**
		* Gets a subpane control by ID.
		* @since ?Series90_version
		* @param aPaneId ID of the subpane.
		* @return The container control for the subpane identified by <code>aPaneID</code>.
		* <BR><B>Type of return value:</B> CCoeControl*
		*/
		IMPORT_C CCoeControl* ControlL(TPaneId aPaneId) const;
		/**
		* Swaps a subpane control.
		* @since ?Series90_version
		* @param aPaneId ID of the subpane.
		* @param aNewControl A fully constructed control to place at <code>aPaneId</code>.
		* @return The control which was at <code>aPaneId</code>.
		* <BR><B>Type of return value:</B> CCoeControl*
		*/
		IMPORT_C CCoeControl* SwapControlL(TPaneId aPaneId, CCoeControl* aNewControl);
		/**
		* Gets the subpane container control.
		* @since ?Series90_version
		* @param aPaneId ID of the subpane.
		* @return A pointer to the container control for the subpane
		* identified by <code>aPaneID</code> in this status pane base.
		* <BR><B>Type of return value:</B> CCoeControl*
		*/
		IMPORT_C CCoeControl* ContainerControlL(TPaneId aPaneId) const;
		/**
		* Returns a pointer to a parent window group.
		* @since ?Series90_version
		* @return Pointer RWindowGroup*
		* <BR><B>Type of return value:</B> RWindowGroup*
		*/
		inline RWindowGroup* WindowGroup() const;
		/**
		* Utility function which adds and removes rectangles from <code>aRegion</code>.
		* @since ?Series90_version
		* @param aRegion Reference to the region of the status panes.  (An empty region should be passed in).
		* @param aIncludeAppPanes Whether or not the computed region will contain application owned status panes.
		* @param aIncludeServerPanes Whether or not the computed region will contain server (ie.system) owned status panes.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void GetShapeL(TRegion& aRegion, TBool aIncludeAppPanes, TBool aIncludeServerPanes) const;

    protected:  // Methods
		/**
		* Constructor.
		* @param aEikEnv The Uikon environment in which the control is created.
		* @param aParent Its parent window group.
		*/
		IMPORT_C CEikStatusPaneBase(CEikonEnv& aEikEnv, RWindowGroup* aParent);

	// New Methods

		/**
		* Base constructor.
		* @param aCoreResId Resource id
		*/
		IMPORT_C void BaseConstructL(TInt aCoreResId);

		/**
		* Creates a status pane model for this status pane.
		* @param aCoreResId Resource id
		*/
		virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const = 0;
		/**
		* Creates panes.
		*/
		void CreatePanesL();
		/**
		* Creates one pane.
		* @param aPaneInit Pane to be initialised with.
		*/
		void CreatePaneL(const TEikStatusPaneInit& aPaneInit);
		/**
		* Returns a pointer to a status pane container with <code>aPaneId</code>.
		* @param aPaneId Status pane id
		* @return Pointer CEikStatusPaneContainer
		*/
		CEikStatusPaneContainer* Find(TPaneId aPaneId) const;

		/**
		* Return whether it is an application.
		* @return <code>ETrue</code> if it is an app
		*/
		virtual TBool IsApp() const = 0;
		/**
		* Gets the status pane rectangle.
		* @return Status pane rectangle
		*/
		inline TRect Rect() const;

    private: //Methods
		void ApplyLayoutL(CEikStatusPaneLayout* aLayout);
		void SetAllInvisible();
		void ReportSizeChange();

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

	protected:     // Data
		/** Uikon environment. */
		CEikonEnv& iEikEnv;
		/** Model. */
		CEikStatusPaneModelBase* iModel;
		/** Flags if the status pane is visible, dimmed, faded. */
		TInt iFlags;

	private:     // Data
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
 * Link against eikcoctl.lib
 * @since ?Series90_version
 */
class CEikStatusPane : public CEikStatusPaneBase, public MCoeForegroundObserver
	{
	public:
	// Constructors and destructor

		/**
		* Static constructor.
		* @param aEikEnv The Uikon environment the application will use.
		* @param aParent Parent window group.
		* @param aCoreStatusPaneModelResId Resource ID of the core status pane model.
		* @param aAppStatusPaneModelResId Resource ID of the application status pane model.
		*/
		IMPORT_C static CEikStatusPane* NewL(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aCoreStatusPaneModelResId, TInt aAppStatusPaneModelResId=EEikStatusPaneUseDefaults);
		/**
		* Destructor.
		*/
		IMPORT_C ~CEikStatusPane();

	// New methods
        
		/**
		* Synchronises the server-side status pane layout with the applications
		* status pane layout.
		* @since ?Series90_version
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ApplyCurrentSettingsL();

	// Methods from base classes

		/**
        * From CEikStatusPaneBase.
		* Hides or reveals all the controls in the applications status pane.
		* @since ?Series90_version
		* @param aVisible If <code>ETrue</code>, the applications status pane is made visible.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void MakeVisible(TBool aVisible);
		/**
		* Dims all the controls in the applications status pane.
		* @since ?Series90_version
		* @param aDimmed If <code>ETrue</code>, the applications status pane is dimmed.
		* <BR><B>Type of return value:</B> void
		*/
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
		/**
		* Fades all the controls in the applications status pane.
		* @since ?Series90_version
		* @param aFaded If <code>ETrue</code>, the applications status pane is faded.
		* <BR><B>Type of return value:</B> void
		*/
	IMPORT_C virtual void SetFaded(TBool aFaded);
		/**
		* Handles changes to the visibility of the entire status pane according
		* to the message type identified by the argument <code>aType</code>.
		* @since ?Series90_version
		* @param aType Message type.
		* <BR><B>Type of return value:</B> void
		*/
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	//internal
	IMPORT_C void HandleStatusPaneUpdateMessageL();

    private: //Methods
		CEikStatusPane(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aAppStatusPaneModelId);
		void ConstructL(TInt aCoreStatusPaneModelResId);

		virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const;
		TBool IsApp() const;

		void ApplyCurrentFlags();
		void DoHandleGainingForegroundL();
		static TInt TimerCallBackL(TAny* aPtr);

		// from MCoeForegroundObserver
		void HandleGainingForeground();
		void HandleLosingForeground();
		TBool IsForeground();

	private:     // Data
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

#endif      // EIKSPANE_H   
            
// End of File
