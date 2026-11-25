// TXTFRMAT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


/**
 *
 * Compares two tab stops for inequality.
 *
 * They are different if the twips position or alignment is different.
 *
 * @param     " const TTabStop& aTabStop "
 *            The tab stop to compare with the current tab stop
 * @returns   " TBool "
 *            <code>ETrue</code> if the objects' twips position or
 *            alignment differs. <code>EFalse</code> if equal.
 */

TBool TTabStop::operator!=(const TTabStop& aTabStop)const
	{return !(*this==aTabStop);}

/**
 *
 * Compares two paragraph border sides for inequality.
 *
 * Two paragraph border sides are different if any of their data members
 * are different.
 *
 * @param     " const TParaBorder& aBorder "
 *            The paragraph border to compare with the current
 *            border.
 * @returns   " TBool "
 *            <code>ETrue</code> if the two paragraph border sides
 *            are different, <code>EFalse</code> if not.
 */

TBool TParaBorder::operator!=(const TParaBorder& aParaBorder)const
	{return !(*this==aParaBorder);}

/**
 *
 * Compares two bullet points for inequality.
 *
 * Two bullet points are unequal if any of their data members are
 * different.
 *
 * @param     " const TBullet& aBullet "
 *            The bullet point to compare.
 * @returns   " TBool "
 *            <code>ETrue</code> if the two bullet points are
 *            different, <code>EFalse</code> if not.
 */

TBool TBullet::operator!=(const TBullet& aBullet)const
	{return !(*this==aBullet);}


/**
 *
 * Removes all tab stops from the object.
 *
 */

void CParaFormat::RemoveAllTabs()
	{
	if (iTabList)
		{
		delete iTabList;
		iTabList = NULL;
		}
	}

/**
 *
 * Gets a count of the total number of tab stops in the object's tab
 * list.
 *
 * If the object has no tab list, returns zero.
 *
 * @returns   " TInt "
 *            The number of tab stops.
 */

TInt CParaFormat::TabCount()const
	{return (iTabList)?iTabList->Count():0;}


/**
 *
 * The default C++ constructor constructs a paragraph format mask,
 * initialising all bits to zero.
 *
 */

TParaFormatMask::TParaFormatMask()
// Constructor.  Clears all guard bits.
//
	:iGuard(0)
	{}

/**
 *
 * Sets a single attribute flag in the paragraph format mask.
 *
 * @param     " TTextFormatAttribute aAttribute "
 *            The attribute flag to set.
 */

void TParaFormatMask::SetAttrib(TTextFormatAttribute aAttribute)
	{iGuard|=(1<<aAttribute);}

/**
 *
 * Clears a single attribute flag in the paragraph format mask.
 *
 * @param     " TTextFormatAttribute aAttribute "
 *            The attribute flag to clear.
 */

void TParaFormatMask::ClearAttrib(TTextFormatAttribute aAttribute)
	{iGuard&=~(1<<aAttribute);}

/**
 *
 * Tests whether an attribute flag is set.
 *
 * @param     " TTextFormatAttribute aAttribute "
 *            The paragraph format attribute to test for.
 * @returns   " TBool "
 *            <code>ETrue</code> if the flag is set,
 *            <code>EFalse</code> if not.
 */

TBool TParaFormatMask::AttribIsSet(TTextFormatAttribute aAttribute)const
	{return (iGuard&(1<<aAttribute));}

/**
 *
 * Tests whether the mask is NULL, indicating that no flags have been
 * set.
 *
 * @returns   " TBool "
 *            <code>ETrue</code> if mask is NULL,
 *            <code>EFalse</code> if not NULL.
 */

TBool TParaFormatMask::IsNull()const
// Returns ETrue if the mask has not been set.
//
	{return !iGuard;}

/**
 *
 * Compares two paragraph format masks for inequality.
 *
 * @param     " const TParaFormatMask& aMask "
 *            The mask to compare.
 * @returns   " TBool "
 *            <code>ETrue</code> if any flags are different.
 *            <code>EFalse</code> if all flags are the same.
 */

TBool TParaFormatMask::operator!=(const TParaFormatMask& aMask)const
	{return !(*this==aMask);}


/**
 *
 * The default C++ constructor constructs a character format mask,
 * initialising all bits to zero.
 *
 */

TCharFormatMask::TCharFormatMask()
// Constructor.  Clears all guard bits.
//
	:iGuard(0)
	{}

/**
 *
 * Sets a single attribute flag in the character format mask.
 *
 * @param     " TTextFormatAttribute aAttribute "
 *            The attribute flag to set.
 */

void TCharFormatMask::SetAttrib(TTextFormatAttribute aAttribute)
	{iGuard|=(1<<((aAttribute-KMaxParaAttributes)-1));}

/**
 *
 * Clears a single attribute flag in the character format mask.
 *
 * @param     " TTextFormatAttribute aAttribute "
 *            The attribute flag to clear.
 */

void TCharFormatMask::ClearAttrib(TTextFormatAttribute aAttribute)
	{iGuard&=~(1<<((aAttribute-KMaxParaAttributes)-1));}

/**
 *
 * Tests whether an attribute flag is set.
 *
 * @param     " TTextFormatAttribute aAttribute "
 *            The character format attribute to test for.
 * @returns   " TBool "
 *            <code>ETrue</code> if the flag is set,
 *            <code>EFalse</code> if not.
 */

TBool TCharFormatMask::AttribIsSet(TTextFormatAttribute aAttribute)const
	{return iGuard&(1<<((aAttribute-KMaxParaAttributes)-1));}

/**
 *
 * Tests whether the mask is NULL, indicating that no flags have been
 * set.
 *
 * @returns   " TBool "
 *            <code>ETrue</code> if mask is NULL,
 *            <code>EFalse</code> if not NULL.
 */

TBool TCharFormatMask::IsNull()const
	{return !iGuard;}

/**
 *
 * Compares two paragraph format masks for inequality.
 *
 * @param     " const TCharFormatMask& aMask "
 *            The mask to compare.
 * @returns   " TBool "
 *            <code>ETrue</code> if any flags are different.
 *            <code>EFalse</code> if all flags are the same.
 */

TBool TCharFormatMask::operator!=(const TCharFormatMask& aMask)const
	{return !(*this==aMask);}


