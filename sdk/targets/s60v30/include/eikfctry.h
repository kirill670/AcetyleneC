// EIKFCTRY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFCTRY_H__)
#define __EIKFCTRY_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

class CCoeControl;

/**
@publishedPartner
@released
*/
enum
	{
	EEikControlHasEars=0x01,
	EEikControlIsNonFocusing=0x02,
	EEikControlHasExtraAscent=0x04,
	/** Flag to determine if a control should be placed directly
	 in the view/dialog or if it should be placed in a pop-out control. */
	EEikControlIsNonEditInPlace=0x08
	};

/**
@publishedAll
@released
*/
struct SEikControlInfo
    {
    CCoeControl* iControl;
	TInt iTrailerTextId;
    TInt iFlags;
    };


class EikControlFactory
/** Abstract factory that creates controls by type. 

This class provides a unified way to create controls according to the 
specified control integer ID. 

@publishedAll 
@released */
	{
public:
    IMPORT_C static SEikControlInfo CreateByTypeL(TInt aControlType);
	};

#endif
