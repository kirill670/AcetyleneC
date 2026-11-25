/*
* ==============================================================================
*  Name        : mtmstore.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Message Store utilities
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


#ifndef MTMSTORE_H
#define MTMSTORE_H

// INCLUDES
#include <msvapi.h>

// CONSTANTS
// FORWARD DECLARATIONS
class CClientMtmRegistry;
class CMtmUiRegistry;
class CBaseMtmUi;
class CBaseMtm;
class CBaseMtmUiData;
class CMtmUiInfoItem;
class CMtmUiDataRegistry;

/**
*  M class related to CMtmUsageTimer. Any code which accesses a 
*  CMtmUsageTimer should be derived from MmtmUsageTimerObserver
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class MMtmUsageTimerObserver
{
	public:

		/**
		* Called when an MTM times out
		* @since ?Series90_version
		* @param aMtm The timed out MTM
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		virtual void MtmUsageTimedOut(TUid aMtm)=0;
};

/**
*  A message store class
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class CMtmStore: public CBase, public MMtmUsageTimerObserver
{
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CMtmStore* NewL(CMsvSession& aSession);

		/**
		* Destructor.
		*/
		IMPORT_C ~CMtmStore();


		/**
		* Retrieves the message editor data for the specified Uid.
		* @since ?Series90_version
		* @param aMtm The specified uid
		* @return The message editor data
		* <BR><B>Type of return value:</B> CBaseMtmUiData&
		*/
		IMPORT_C CBaseMtmUiData& MtmUiDataL(TUid aMtm);


		/**
		* Retrieves the message editor for the specified Uid.
		* @since ?Series90_version
		* @param aMtm The specified uid
		* @return The message editor
		* <BR><B>Type of return value:</B> CBaseMtmUi&
		*/
		IMPORT_C CBaseMtmUi& ClaimMtmUiL(TUid aMtm);

		/**
		* Retrieves the message editor for the specified entry then 
		* sets the current message to be the one specified.
		* @since ?Series90_version
		* @param aContext The entry
		* @return The message editor
		* <BR><B>Type of return value:</B> CBaseMtmUi&
		*/
		IMPORT_C CBaseMtmUi& ClaimMtmUiAndSetContextL(const TMsvEntry& aContext);

		/**
		* Releases the specified message editor from the usage array.
		* @since ?Series90_version
		* @param aMtm The specified mtm
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ReleaseMtmUi(TUid aMtm);


		/**
		* Retrieves the message editor for the specified Uid. The difference 
		* between this and ClaimMtmUiL() is that GetMtmUiLC() puts a releasing 
		* clean up item (a CMtmStoreMtmReleaser) on the clean up stack.
		* @since ?Series90_version
		* @param aMtm The specified mtm
		* @return The message editor
		* <BR><B>Type of return value:</B> CBaseMtmUi&
		*/
		IMPORT_C CBaseMtmUi& GetMtmUiLC(TUid aMtm); // puts a releasing cleanup item on the stack

		/**
		* Same as GetMtmUiLC(), but also sets the current
		* message to be the one specified.
		* @since ?Series90_version
		* @param aContext The message entry
		* @return The message editor
		* <BR><B>Type of return value:</B> CBaseMtmUi&
		*/
		IMPORT_C CBaseMtmUi& GetMtmUiAndSetContextLC(const TMsvEntry& aContext); // puts a releasing cleanup item on the stack 

	private: // from MMtmUsageTimerObserver
		virtual void MtmUsageTimedOut(TUid aMtm);

	private:
		CMtmStore(CMsvSession& aSession);
		void ConstructL();
		CMtmUiInfoItem& DoClaimMtmUiL(TUid aMtm);
		TInt FindMtmUiIndex(TUid aMtm) const;
		TInt FindMtmUiDataIndex(TUid aMtm) const;
		void AddNewMtmUiHolderL(TUid aMtm, TInt& aNewIndex);

	private:
		CMsvSession& iSession;
		CArrayPtrFlat<CMtmUiInfoItem> iMtmUiInfoArray;
		CArrayPtrFlat<CBaseMtmUiData> iMtmUiDataArray;
		CClientMtmRegistry* iBaseMtmRegistry;
		CMtmUiRegistry* iMtmUiRegistry;
		CMtmUiDataRegistry* iMtmUiDataRegistry;
};


/**
*  An MTM store releaser
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class CMtmStoreMtmReleaser: public CBase
{
	public:

		/**
		* Cleanup and release specified mtm
		* @since ?Series90_version
		* @param aMtmStore The mtm store to cleanup
		* @param aMtm The specified mtm
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void CleanupReleaseMtmUiLC(CMtmStore& aMtmStore, TUid aMtm);

	private:
		inline CMtmStoreMtmReleaser(CMtmStore& aMtmStore, TUid aMtm);
		inline ~CMtmStoreMtmReleaser();
	private:
		CMtmStore& iMtmStore;
		TUid iMtm;
};

inline CMtmStoreMtmReleaser::CMtmStoreMtmReleaser(CMtmStore& aMtmStore, TUid aMtm)
:CBase(), iMtmStore(aMtmStore), iMtm(aMtm)
{}

inline CMtmStoreMtmReleaser::~CMtmStoreMtmReleaser()
{
iMtmStore.ReleaseMtmUi(iMtm);
}


#endif	// MTMSTORE_H

// End of File
