// CMDEFS.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
#ifndef __CMDEFS_H__
#define __CMDEFS_H__

#include <E32Std.h>
#include <EikScrlb.h>


/**
 * A few defines and enums used in several places
 *
 */

//const TInt KUidCntUiDllValue = 0x10003A78;	
const TInt KUidCntUiDllValue = 0x10009142;	

const TUid KUidCntUiDll = {KUidCntUiDllValue};

const TInt KEllipsisCharacter=0x2026;

enum TSortBy
	{
	ESortByFirstNameLastName,
	ESortByLastNameFirstName,
	ESortByCompanyLastName,
	ESortByCompanyFirstName,
	};

enum TColumnState
	{
	EOneColumn, // see SortBy above for content. One column in dialogs.
	ETwoColumns, // as above but with preferred tel# in the second column. 
	EIMTwoColumns, // IM icon and SortBy (see above)
	EIMThreeColumns,	// as above but with preferred tel# in the third column.
	ECntsOneColumn, // see SortBy above for content. One column in Contacts list view
	ECntsTwoColumns // as above but with preferred tel# in the second column
	};

const TInt KMinMemoryBeforeCreateNew = 60;  // Minimum 60K of memory allowed to create a new contact.

const TUint KMaxFindString=255; // Should be using KContactUiMaxFindText from contacui.hrh
typedef TBuf<KMaxFindString> TFindString;

#endif // __CMDEFS_H__
