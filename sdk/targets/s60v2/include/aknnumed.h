/*
* ============================================================================
*  Name     : AknNumed.h
*  Part of  : EikCtl
*
*  Description:
*		Intermediate class for defining data shared between numeric edwins    
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

#if !defined(__AKNNUMED_H_)
#define __AKNNUMED_H_

#include <eikedwin.h>


/**
 * Intermediate class for defining data shared between numeric edwins
 *
 */
class CAknNumericEdwin : public CEikEdwin
	{
public:
	IMPORT_C virtual ~CAknNumericEdwin();
	enum TValidationStatus
		{
		EValueValid = KErrNone,
		EValueTooSmall,
		EValueTooLarge,
		EValueNotParsed,
		EEmpty
		};

protected:
	IMPORT_C void MapKeyEvent(TKeyEvent& aKeyEvent,TEventCode& /*aType*/, TDigitType aDigitType) const;

private: // from CEikEdwin
		IMPORT_C virtual void Reserved_3();
	};


#endif
