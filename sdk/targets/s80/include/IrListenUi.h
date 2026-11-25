/*
* ============================================================================
*  Name     : CIrListenAppUiBase, CIrListenAppUi from IrListenUi.h
*  Part of  : IrMtmUi
*
*  Description:
*      part of MTM UI module. Part of client server communication interface.     
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

#ifndef __IRLISTENUI_H__
#define __IRLISTENUI_H__

//  INCLUDES
#include <e32base.h>

// CONSTANTS
_LIT(KIrListenDLLName, "\\system\\libs\\IrListen.dll");
const TUid KIrListenDllUid1	= {0x10000079};
const TUid KIrListenDllUid2	= {0x1000008D};
const TUid KIrListenDllUid3 = {0x101F87E1};

/**
*  CIrListenAppUiBase.
*  Base class for interface provided by IrMtmUi.
*/
class CIrListenAppUiBase : public CBase
	{
	public:  // Constructors and destructor
        
		/**
        * Destructor.
        */
	    IMPORT_C virtual ~CIrListenAppUiBase();

	public: // New functions

        /**
        * Set IR listening state.
        * @param aOn EFalse means deactivate IR.
        * @return None.
        */
		IMPORT_C virtual void SetListeningL(TBool aOn);
        

        /**
        * Toggle IR activity state. If called when IR is active 
        * it will turn off.
        * @param None.
        * @return None.
        */
	    IMPORT_C virtual void ToggleListeningL();

	    /**
        * Toggle BlueTooth activity state.If called when 
        * Bt is active it will turn off.
        * @param None.
        * @return None.
        */
	    IMPORT_C virtual void ToggleBtListeningL();

        /**
        * Returns IR activity state.
        * @param None.
        * @return TBool ETrue when listening state, if inactive EFalse.
        */
	    IMPORT_C virtual TBool ListeningL();

        /**
        * Returns Bt activity state.
        * @param None.
        * @return TBool ETrue when listening state, if inactive EFalse.
        */
	    IMPORT_C virtual TBool BtListeningL();
	    
	};



#endif  // __IRLISTENUI_H__
// End of File
