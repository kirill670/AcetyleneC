// TXTGLOBL.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


/**
 *
 * Gets the paragraph format layer referenced by the global text object.
 *
 * @returns   " CParaFormatLayer* "
 *            Pointer to the paragraph format layer referenced by
 *            the global text object.
 */

const CParaFormatLayer* CGlobalText::GlobalParaFormatLayer()const
	{return iGlobalParaFormatLayer;}
	

/**
 *
 * Gets the character format layer referenced by the global text object.
 *
 * @returns   " CCharFormatLayer* "
 *            Pointer to the character format layer referenced by
 *            the global text object.
 */
	
const CCharFormatLayer* CGlobalText::GlobalCharFormatLayer()const
	{return iGlobalCharFormatLayer;}

