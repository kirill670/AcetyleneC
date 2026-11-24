/*
* ============================================================================
*  Name     : AknGridM.h
*  Part of  : Avkon
*
*  Description:
*     This class is an extension of the text list
*     model class. It is designed specifically to be used with
*     the grid class and the grid view class.
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
// AKNGRIDM.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//


#if !defined(__AKNGRIDM_H__)
#define __AKNGRIDM_H__  

#include <eiktxlbm.h>
#include <aknutils.h>

class CAknGridM : public CTextListBoxModel
	{
public:
	IMPORT_C CAknGridM();
	IMPORT_C virtual ~CAknGridM();

	IMPORT_C virtual TInt NumberOfItems() const;
	IMPORT_C virtual TBool IndexContainsData(TInt aDataIndex) const;
	IMPORT_C virtual TInt NumberOfData() const;

	IMPORT_C void SetStartCells(TInt aNumEmpty);

	IMPORT_C TInt IndexOfFirstDataItem() const;
	IMPORT_C TInt IndexOfLastDataItem() const;

	IMPORT_C virtual TPtrC ItemText(TInt aItemIndex) const;
private:
	TInt iEmptyCellsAtStart;
	TInt iEmptyCellsAtEnd;
	}; 


#endif
