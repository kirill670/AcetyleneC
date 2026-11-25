/*
* ============================================================================
*  Name     : CIrListenAppUi from irlistenappui.h
*  Part of  : IRMTMUI
*
*  Description:
*     API for Irlistenserver.
*
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef __IRLISTENAPPUI_H__
#define __IRLISTENAPPUI_H__

#include <irlistenui.h> //CIrListenAppUiBase

/**
*  CIrListenAppUi.
*  Class for inteface provided by IrMtmUi.
*/
class CIrListenAppUi : public CIrListenAppUiBase
	{
	public: // Constructors and destructor

        /**
        * Two-phased constructor.
        */
	    IMPORT_C static CIrListenAppUi* NewL();
	   
        /**
        * Two-phased constructor.
        */
		IMPORT_C static CIrListenAppUi* NewLC();

        /**
        * Destructor.
        */		
		IMPORT_C virtual ~CIrListenAppUi();
		
	public: // Functions from base classes

        /**
        * From CIrListenAppUiBase Set IR listening state.
        * @param aOn EFalse means deactivate IR.
        * @return None.
        */
		IMPORT_C virtual void SetListeningL(TBool aOn);

        /**
        * From CIrListenAppUiBase Toggle IR activity state. 
        * If called when IR is active it will turn off.
        * @param None.
        * @return None.
        */
		IMPORT_C virtual void ToggleListeningL();

        /**
        * From CIrListenAppUiBase Toggle BlueTooth activity state.
        * If called when Bt is active it will turn off.
        * @param None.
        * @return None.
        */
		IMPORT_C virtual void ToggleBtListeningL();

        /**
        * From CIrListenAppUiBase Returns IR activity state.
        * @param None.
        * @return TBool ETrue when listening state, if inactive EFalse.
        */
		IMPORT_C virtual TBool ListeningL();

        /**
        * From CIrListenAppUiBase Returns Bt activity state.
        * @param None.
        * @return TBool ETrue when listening state, if inactive EFalse.
        */
		IMPORT_C virtual TBool BtListeningL();
		
		
	private:  // data
		
		// RLibrary API used for loading needed Dll's; irlisten.dll
		RLibrary iUiDll;
		
		// pointer to base class ( CIrListenAppUiBase ).
		CIrListenAppUiBase* iRealAppUi;
	};

#endif      // __IRLISTENAPPUI_H__
            
// End of File
