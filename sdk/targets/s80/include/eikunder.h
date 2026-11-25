/*
* ==============================================================================
*  Name        : eikunder.h
*  Part of     : UIKON
*  Interface   : Eikon Servers
*  Description : EIK Undertaker observer and active object
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


#if !defined(__EIKUNDER_H__)
#define __EIKUNDER_H__

// INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class RThread;

/**
*  @internal
*  Internal to Symbian.  Undertaker observer.
*  Should not be available to 3rd parties but is being used by series 60 apps - should we deprecate to 3rd partie
*
*  @lib eiksrv.lib
*  @since ?Series90_version
*/
class MEikUndertakerObserver
	{
	public:

		/**
		* Handles an exiting thread
		* @since ?Series90_version
		* @param aThread The thread ID
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		virtual void HandleThreadExitL(RThread& aThread)=0;
	};


/**
*  @internal
*  Internal to Symbian.  Undertaker active object
*  Should not be available to 3rd parties but is being used by series 60 apps - should we deprecate to 3rd parties?
*
*  @lib eiksrv.lib
*  @since ?Series90_version
*/
class CEikUndertaker : public CActive
	{
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CEikUndertaker* NewL(MEikUndertakerObserver& aObserver);

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikUndertaker();
	private:
		CEikUndertaker(MEikUndertakerObserver& aObserver);
		void ConstructL();
		void Request();
	private: // from CActive
		virtual void DoCancel();
		virtual void RunL();
	private:
		MEikUndertakerObserver& iObserver;
		RUndertaker iUndertaker;
		TInt iThreadHandle;
	};


#endif	// EIKUNDER_H

// End of File
