// TXTSTYLE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
 *
 * This default C++ constructor is used to construct the object,
 * initializing both style pointers to NULL.
 *
 */

RParagraphStyleInfo::RParagraphStyleInfo()
	: iStyle(NULL),iStyleForNextPara(NULL)
	{}

RParagraphStyleInfo::RParagraphStyleInfo(CParagraphStyle* aStyle,CParagraphStyle* aStyleForNextPara)
	: iStyle(aStyle),iStyleForNextPara(aStyleForNextPara)
	{}

/**
 *
 * Deletes the style pointer owned by the object.
 *
 * The pointer to the style for the following paragraph is not deleted.
 *
 */

void RParagraphStyleInfo::Discard()
	{delete iStyle;}


/**
 *
 * Gets a pointer to the character format layer owned by the object.
 *
 * NoteThe style's character formatting is set and retrieved using this
 * pointer.
 *
 * @returns   " CCharFormatLayer* "
 *            Pointer to the style's global character format layer.
 */

CCharFormatLayer* CParagraphStyle::CharFormatLayer()const
	{return iCharFormatLayer;}

/**
 *
 * Gets the styles outline level.
 *
 * @returns   " TInt "
 *            The styles outline level.
 */

TInt CParagraphStyle::OutlineLevel()const
	{return iOutlineLevel;}


/**
 *
 * Sets the styles outline level.
 *
 * @param     " TInt aOutlineLevel "
 *            The styles new outline level.
 */

void CParagraphStyle::SetOutlineLevel(TInt aOutlineLevel)
	{iOutlineLevel=aOutlineLevel;}


/**
 *
 * Sets the styles type UID.
 *
 * On construction, the styles type UID is initialized to
 * <code>KUserDefinedParagraphStyleUid</code> to distinguish it from
 * ordinary paragraph format layers, which have a type of
 * <code>KNormalParagraphStyleUid</code>. This function can be used to
 * change it to another value.
 *
 * @param     " TUid aType "
 *            The styles type UID.
 */

void CParagraphStyle::SetType(TUid aType)
	{iType=aType;}


/**
 *
 * Creates and returns a <code>CParagraphStyle</code> object which is a
 * clone of the current style.
 *
 * @returns   " CParagraphStyle* "
 *            Pointer to a clone of the current style.
 */

CParagraphStyle* CParagraphStyle::CloneL()const
	{return STATIC_CAST(CParagraphStyle*,DoCloneL());}


/**
 *
 * Gets a style from the style list, from its index into the array.
 *
 * Two versions are supplied. The compiler chooses the appropriate
 * version based on the use made of the returned reference. If it is used
 * in an expression where the reference can be modified, then the
 * non-const version is chosen.
 *
 * @param     " TInt aIndex "
 *            The index of the style into the list. The first style
 *            is at position zero. Must be within the bounds of the
 *            array or a panic occurs.
 * @returns   " const RParagraphStyleInfo& "
 *            A const reference to the style at position
 *            <code>aIndex</code> in the array.
 * @returns   " RParagraphStyleInfo& "
 *            A non-const reference to the style at position
 *            <code>aIndex</code> in the array.
 */

const RParagraphStyleInfo& CStyleList::operator[](TInt aIndex)const
	{return iList->At(aIndex);}


RParagraphStyleInfo& CStyleList::operator[](TInt aIndex)
	{return iList->At(aIndex);}

/**
 *
 * Gets the number of styles in the style list.
 *
 * @returns   " TInt "
 *            The number of styles in the style list
 */

TInt CStyleList::Count()const
	{return (iList) ? iList->Count() : 0;}
