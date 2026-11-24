/*
* ============================================================================
*  Name     : CAknNumericSecretEditor from Aknnumseced.h
*  Part of  : Avkon
*
*  Description:
*     Numeric secret editor class; derives from secret editor class in \eikstd, 
*     CEikSecretEditor
*
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#if !defined(__AKNNUMSECED_H__)
#define __AKNNUMSECED_H__

//  INCLUDES
#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#include <eikseced.h>

// CLASS DECLARATION
class CAknNumericSecretEditor : public CEikSecretEditor
	{
public:
	IMPORT_C CAknNumericSecretEditor();
    ~CAknNumericSecretEditor();
public:	// from CCoeControl
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
protected:
    // methods to enable CAknNumericSecretEditor to inherit from CEikSecretEditor
    IMPORT_C virtual void AppendCharacterL( TInt aKeyCode );
	IMPORT_C virtual MCoeFepAwareTextEditor_Extension1::CState* CreateFepStateL();
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private: // from MCoeFepAwareTextEditor
	IMPORT_C void MCoeFepAwareTextEditor_Reserved_2();
private:  // from MCoeFepAwareTextEditor_Extension1
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_2();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_3();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_4();
	TInt iSpare;
	};

#endif	// AKNNUMSECED_H
            
// End of File
