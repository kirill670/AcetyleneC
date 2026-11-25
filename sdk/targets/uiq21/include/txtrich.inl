// TXTRICH.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


const TUint32 KStyleListExternallyOwned=0x01;
const TUint32 KParaTypeIsSingle=0x02;

/**
 *
 * Tests whether the rich text object uses a style list.
 *
 * The style list may be owned by the object itself, or may be externally
 * owned.
 *
 * @returns   " TBool "
 *            True if the object uses a style list. False if not
 */

TBool CRichText::StyleListPresent()const
	{return iStyleList.IsPtr() && iStyleList.AsPtr();}


/**
 *
 * Gets a pointer to the style list used by the rich text object.
 *
 * @returns   " CStyleList* "
 *            The object's style list. NULL if no style list
 *            present.
 */

CStyleList* CRichText::StyleList()const
	{return (StyleListPresent()) ? iStyleList.AsPtr() : NULL;}


/**
 *
 * Gets the number of styles contained in the rich text object's style
 * list.
 *
 * Returns zero if there is no style list present.
 *
 * @returns   " TInt "
 *            The number of styles in the style list
 */

TInt CRichText::StyleCount()const
	{return (StyleListPresent()) ? iStyleList->Count():0;}


void CRichText::SetStyleListExternallyOwned(TBool aBool)
	{
	if (aBool) iFlags|=KStyleListExternallyOwned;
	else iFlags&=~KStyleListExternallyOwned;
	}


/**
 *
 * Tests whether the style list used by this rich text object is owned by
 * the object itself, or is externally owned.
 *
 * This value is set using <code>SetStyleListExternallyOwned()</code>.
 *
 * @returns   " TBool "
 *            True if the rich text object's style list is
 *            externally owned. False if it owns its style list, or
 *            if it does not use a style list.
 */

TBool CRichText::StyleListExternallyOwned()const
	{return iFlags&KStyleListExternallyOwned;}


/**
 *
 * Removes a style from all paragraphs to which it applies.
 *
 * The formatting is reset to the global character and paragraph format
 * layers, except that any specific formatting which has been applied to
 * the paragraphs is retained.Notes:This function should be called on the
 * text content object after deleting a style in the style list.A panic
 * occurs if the rich text object does not use a style list (this can be
 * tested for using <code>StyleListPresent()</code>).
 *
 * @param     " const CParagraphStyle* aStyle "
 *            Pointer to the style to remove from the rich text
 *            object.
 */

void CRichText::NotifyStyleDeletedL(const CParagraphStyle* aStyle)
	{NotifyStyleChangedL(NULL,aStyle);}


/**
 *
 * Gets the store resolver.
 *
 * A store resolver may be set during construction, or by calling
 * <code>CRichText::SetPictureFactory()</code>.
 *
 * @returns   " MRichTextStoreResolver* "
 *            The store resolver. This determines which file store
 *            the picture is stored in.
 */

MRichTextStoreResolver* CRichText::StoreResolver()const
	{return iStoreResolver;}


/**
 *
 * Gets the picture factory.
 *
 * A picture factory may be set during construction, or by calling
 * <code>CRichText::SetPictureFactory()</code>.
 *
 * @returns   " MPictureFactory* "
 *            The picture factory
 */

MPictureFactory* CRichText::PictureFactory()const
	{return iPictureFactory;}


