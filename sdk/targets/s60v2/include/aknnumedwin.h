/*
* ============================================================================
*  Name     : AknNumEdwin.h
*  Part of  : Avkon
*
*  Description:  Numeric Editor derived from Uikon's CEikEdwin
* These specializations of CEikEdwin maintain a numeric content, 
* access methods and validation.
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


#if !defined(__AKNNUMEDWIN_H__)
#define __AKNNUMEDWIN_H__

// INCLUDES
#include <eikedwin.h>
#include <aknnumed.h> // CAknNumericEdwin


_LIT( KAknIntegerFormat, "%d" );

// CLASS DECLARATIONS


class CAknIntegerEdwin : public CAknNumericEdwin
	{
public:
	IMPORT_C static CAknIntegerEdwin* NewL(TInt aMin, TInt aMax, TInt aMaxChars);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ConstructL( TInt aMin, TInt aMax, TInt aMaxChars );

	// New methods
	IMPORT_C void SetValueL(TInt aValue);
	IMPORT_C void SetUnsetValue( TInt aUnsetValue);
	IMPORT_C TValidationStatus GetTextAsInteger( TInt& aValue );
	IMPORT_C void SetMinimumIntegerValue( TInt aMinimumValue );
	IMPORT_C void SetMaximumIntegerValue( TInt aMaximumValue );

	//CCoeControl
	IMPORT_C void PrepareForFocusLossL();
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

private:
	void CommonConstructL(TInt aMin, TInt aMax, TInt aMaxChars, TInt aFlags, TInt aUnset);
	void RefreshFromLocale();

private: // from CEikEdwin
    IMPORT_C void Reserved_3();

private:
	TInt iMinimumValue;
	TInt iMaximumValue;
	TInt iUnsetValue;
	TAny* iUnsetText;
	TDigitType iDigitType;
	TInt iSpare_Integer_2;
	};

#endif
