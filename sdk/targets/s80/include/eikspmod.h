/*
* ==============================================================================
*  Name        : eikspmod.h
*  Part of     : CKON
*  Interface   : Status Pane API
*  Description : Interface for the status pane
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


#if !defined(__EIKSPMOD_H__)
#define __EIKSPMOD_H__

// INCLUDES
#include <e32base.h>
#include <uikon.hrh>
#include <eiksrvc.h>

// FORWARD DECLARATIONS
class TResourceReader;
class CEikStatusPaneLayoutTree;
class CEikonEnv;

// CONSTANTS
// Extra bit flags not defined in hrh file.
const TInt KEikStatusPaneDirectionBit		= 0x04;
const TInt KEikStatusPaneHiddenBit			= 0x08;
const TInt KEikStatusPaneInitInitializedBit	= 0x80000000;

// DATA TYPES
typedef TUid TPaneId;

/**
*  Initialises the status pane
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
class TEikStatusPaneInit
	{
	public:

		/**
		* C++ default constructor.
		*/
		TEikStatusPaneInit();

		/**
		* C++ default constructor.
		*/
		TEikStatusPaneInit(const TEikStatusPaneInit& aCopy);
	TEikStatusPaneInit& operator=(const TEikStatusPaneInit& aCopy);
	

		/**
		* Returns the ID of the pane
		* @since ?Series90_version
		* @return The ID of the pane
		* <BR><B>Type of return value:</B> TPaneId
		*/
		inline TPaneId Id() const;

		/**
		* Loads the defaults from the specified resource
		* @since ?Series90_version
		* @param aResource The specified resource reader
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		void LoadDefaults(TResourceReader& aResource);


		/**
		* Returns if the application is owned or not
		* @since ?Series90_version
		* @return ETrue if the application is owned, EFalse otherwise
		* <BR><B>Type of return value:</B> TBool
		*/
		inline TBool AppOwned() const;

		/**
		* Returns the control type ID
		* @since ?Series90_version
		* @return The control type ID
		* <BR><B>Type of return value:</B> TInt
		*/
		inline TInt ControlTypeId() const;

		/**
		* Returns the control resource ID
		* @since ?Series90_version
		* @return The control resource ID
		* <BR><B>Type of return value:</B> TInt
		*/
		inline TInt ControlResourceId() const;


		/**
		* Sets the pane hidden
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		inline void SetHidden();

		/**
		* Clears the hidden flag
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		inline void ClearHidden();

		/**
		* Queries if pane is hidden
		* @since ?Series90_version
		* @return ETrue if pane is hidden, EFalse otherwise
		* <BR><B>Type of return value:</B> TBool
		*/
		inline TBool IsHidden() const;

	private:
		inline TBool Initialized();
		inline void SetInitialized();

	private:
		TPaneId iId;
		TInt iControlId;
		TInt iControlResource;
		TInt iFlags;
	};


/**
*  Set initial values for status pane
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
class CEikStatusPaneSetInit : public CArrayFixFlat<TEikStatusPaneInit>
	{
	public:

		/**
		* Two-phased constructor.
		*/
		static CEikStatusPaneSetInit* NewL();

		/**
		* Destructor.
		*/
		~CEikStatusPaneSetInit();


		/**
		* Loads the defaults from the resource reader
		* @since ?Series90_version
		* @param aResource The specified resource reader
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		void LoadDefaultsL(TResourceReader& aResource);
		TEikStatusPaneInit& FindL(const TPaneId& aPaneId);
		void SetDefaultsL(const TPaneId& aPaneId, const TEikStatusPaneInit& aPaneInit);

	private:
		CEikStatusPaneSetInit();
	};


/**
*  Status Pane layout tree visitor class
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
class MEikStatusPaneLayoutTreeVisitor
	{
	public:

		/**
		* Visit node on layout tree
		* @since ?Series90_version
		* @param aNode node to visit
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		virtual void VisitL(CEikStatusPaneLayoutTree* aNode) = 0;
	};


/**
*  Status pane layout tree class
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
class CEikStatusPaneLayoutTree : public CBase
	{
	public:
	enum TDirection
		{
		EHorizontal,
		EVertical
		};

	public:

		/**
		* Destructor.
		*/
		~CEikStatusPaneLayoutTree();

		/**
		* Two-phased constructor.
		*/
		static CEikStatusPaneLayoutTree* NewL(TResourceReader& aResource, TDirection aDefaultDirection = EHorizontal);

		CEikStatusPaneLayoutTree* Find(const TPaneId& aPaneId);

		void AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor);


		/**
		* Returns the pane ID
		* @since ?Series90_version
		* @return The pane ID
		* <BR><B>Type of return value:</B> TPaneId
		*/
		inline TPaneId Id() const;

		/**
		* Returns the size of the pane layout tree
		* @since ?Series90_version
		* @return The size of the pane layout tree
		* <BR><B>Type of return value:</B> TRect
		*/
		inline TRect Rect() const;

	private:
		CEikStatusPaneLayoutTree(TDirection aDefaultDirection);
		void ConstructL(TResourceReader& aResource);

		void SetRect(const TRect& aRect);
		inline TDirection Direction();
		void SetDirection(TDirection aDirection);
		inline TInt Size();
		inline TBool Stretchable();
		void SetStretchable(TBool aStretchable);
		void Layout();

	private:
		TPaneId iId;
		TInt iFlags;
		TRect iRect;
		TInt iSize;

		typedef CArrayPtrFlat<CEikStatusPaneLayoutTree> CSubPaneArray;
		CSubPaneArray* iSubPanes;

	private:
	friend class CEikStatusPaneLayout;
	};


/**
*  Status Pane layout
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
class CEikStatusPaneLayout : public CBase
	{
	public:

		/**
		* Two-phased constructor.
		*/
		static CEikStatusPaneLayout* NewL(TResourceReader& aResource, const TRect& aScreenRect);

		/**
		* Destructor.
		*/
		~CEikStatusPaneLayout();

		/**
		* Find tree based on pane ID
		* @since ?Series90_version
		* @param aPaneId The specified pane ID
		* @return The tree matching the pane ID
		* <BR><B>Type of return value:</B> CEikStatusPaneLayoutTree*
		*/
		inline CEikStatusPaneLayoutTree* Find(const TPaneId& aPaneId) const;

		/**
		* Accept visitor to status pane
		* @since ?Series90_version
		* @param aVisitor The visitor
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		inline void AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor);

		/**
		* Returns the size of the rectangle
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> TRect
		*/
		inline TRect Rect() const;

	private:
		CEikStatusPaneLayout();
		void ConstructL(TResourceReader& aResource, const TRect& aScreenRect);

	private:
		CEikStatusPaneLayoutTree* iRoot;
	};


/**
*  Status pane model base
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
class CEikStatusPaneModelBase : public CBase
	{
	public:

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikStatusPaneModelBase();


		/**
		* Returns the initial values of the pane
		* @since ?Series90_version
		* @return The initial values of the pane
		* <BR><B>Type of return value:</B> CEikStatusPaneSetInit*
		*/
		inline CEikStatusPaneSetInit* PaneInits() const;

		/**
		* Sets the layout of the pane
		* @since ?Series90_version
		* @param aLayoutResId Resource ID of the layout
		* @param aChangeStatusPaneNow ETrue if layout is to be changed straight away
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow = ETrue);

		/**
		* Returns the current layout
		* @since ?Series90_version
		* @return A pointer to the current layout of the status pane
		* <BR><B>Type of return value:</B> CEikStatusPaneLayout*
		*/
		inline CEikStatusPaneLayout* CurrentLayout() const;

	protected:
/**
*  Class with resource ID and layout
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
	class CIdLayoutPair : public CBase
		{
	public:

		/**
		* C++ default constructor.
		*/
		CIdLayoutPair(TInt aResId, CEikStatusPaneLayout* aLayout);

		/**
		* Destructor.
		*/
		~CIdLayoutPair();
	public:
		TInt iResId;
		CEikStatusPaneLayout* iLayout;
		};


		typedef CArrayPtrFlat<CIdLayoutPair> CLayoutIdSet;
		typedef CArrayFixFlat<TInt> CIdSet;

	protected:

		/**
		* Constructor
		* @param aEikEnv Eikon environment
		*/
		IMPORT_C CEikStatusPaneModelBase(CEikonEnv& aEikEnv);

		/**
		* Constructs the base
		* @param aCoreResId Core resource ID
		* @return void
		*/
		IMPORT_C void BaseConstructL(TInt aCoreResId);


		/**
		* Loads the layout
		* @param aLayoutResId The resource ID of the layout
		* @return pointer to the new layout
		*/
		IMPORT_C CEikStatusPaneLayout* LoadLayoutL(TInt aLayoutResId);


		/**
		* Returns the legal IDs
		* @return The legal IDs
		*/
		inline CIdSet* LegalIds() const;

		/**
		* Queries if layout resource ID is a legal ID
		* @param aLayoutResId The specified resource ID
		* @return ETrue if it is a legal ID, EFalse otherwise
		*/
		TBool IsLegalId(TInt aLayoutResId) const;

	private:
		CEikStatusPaneLayout* Layout(TInt aLayoutResId);
		void CheckLayoutL(CEikStatusPaneLayout* aLayout);

	private:
		IMPORT_C virtual void Reserved_1();

	private:
/**
*  Checks the layout
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
	class TLayoutChecker : public MEikStatusPaneLayoutTreeVisitor
		{
	public:

		/**
		* C++ default constructor.
		*/
		TLayoutChecker(CEikStatusPaneSetInit* aPanes);

		void VisitL(CEikStatusPaneLayoutTree* aNode);
	private:
		CEikStatusPaneSetInit* iPanes;	
		};

	protected:
		CLayoutIdSet* iLayouts;
		TInt iCurrentResId;
		CEikonEnv& iEikEnv;

	private:
		CEikStatusPaneSetInit* iPanes;
		CEikStatusPaneLayout* iCurrentLayout;
		CIdSet* iLegalIds;
	};


/**
*  Status pane model
*
*  @lib eikcoctl.lib
*  @since ?Series90_version
*/
class CEikAppStatusPaneModel : public CEikStatusPaneModelBase
	{
	public:
	static CEikAppStatusPaneModel* NewL(CEikonEnv& aEikEnv, /*REikSrvSession,*/ TInt aCoreResId, TInt aAppResId = EEikStatusPaneUseDefaults, TBool aChangeStatusPaneNow = ETrue);

		/**
		* Destructor.
		*/
		~CEikAppStatusPaneModel();

		/**
		* Apply the current layout to the pane
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		void ApplyCurrentLayoutL();

		/**
		* Returns a pointer to the current app ui session
		* @since ?Series90_version
		* @return Pointer to the current app ui session
		* <BR><B>Type of return value:</B> const REikAppUiSession&
		*/
		inline const REikAppUiSession& EikServ() const;
	public:	// from CEikStatusPaneModelBase

		void SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow = ETrue);
		//internal
		void UpdateLayoutL();
	private:
		CEikAppStatusPaneModel(CEikonEnv& aEikEnv);
		void ConstructL(TInt aCoreResId, TInt aAppResId, TBool aChangeStatusPaneNow = ETrue);

	private:
		REikAppUiSession iEikServ;
	};


inline TPaneId TEikStatusPaneInit::Id() const { return iId; }
inline TBool TEikStatusPaneInit::AppOwned() const { return iFlags & EEikStatusPaneAppOwned; }
inline TInt TEikStatusPaneInit::ControlTypeId() const { return iControlId; }
inline TInt TEikStatusPaneInit::ControlResourceId() const { return iControlResource; }
inline void TEikStatusPaneInit::SetHidden() {iFlags|=KEikStatusPaneHiddenBit;}
inline void TEikStatusPaneInit::ClearHidden() {iFlags&=~KEikStatusPaneHiddenBit;}
inline TBool TEikStatusPaneInit::IsHidden() const {return iFlags&KEikStatusPaneHiddenBit;}

inline CEikStatusPaneLayoutTree* CEikStatusPaneLayout::Find(const TPaneId& aPaneId) const { return iRoot->Find(aPaneId); }
inline void CEikStatusPaneLayout::AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor) { iRoot->AcceptL(aVisitor); }
inline TRect CEikStatusPaneLayout::Rect() const { return iRoot->Rect(); }

inline TPaneId CEikStatusPaneLayoutTree::Id() const { return iId; }
inline TRect CEikStatusPaneLayoutTree::Rect() const { return iRect; }


inline CEikStatusPaneSetInit* CEikStatusPaneModelBase::PaneInits() const { return iPanes; }
inline CEikStatusPaneLayout* CEikStatusPaneModelBase::CurrentLayout() const { return iCurrentLayout; }
inline CEikStatusPaneModelBase::CIdSet* CEikStatusPaneModelBase::LegalIds() const { return iLegalIds; }

inline const REikAppUiSession& CEikAppStatusPaneModel::EikServ() const { return iEikServ; }


#endif	// EIKSPMOD_H

// End of File
