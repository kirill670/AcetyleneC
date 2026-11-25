// TXTSTYLE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTSTYLE_H__
#define __TXTSTYLE_H__

#include <e32std.h>
#include <e32base.h>
#include "txtfmlyr.h"


// Classes declared in this file:
class CParagraphStyle;
class CStyleTable;
//
// Classes referenced in this file:
class RReadStream;
class RWriteStream;

const TInt KMaxParagraphStyleName=0x20;

/**
 *
 * The name of a paragraph style with a maximum of 32 characters.
 *
 * Uniquely identifies the style.
 *
 * @since 5.0
 * @lib ""
 */

typedef TBuf<KMaxParagraphStyleName> TParagraphStyleName;

const TUid KUserDefinedParagraphStyleUid={268435535};


//
// Defines a paragraph style, and the paragraph style to use next.

/**
 *
 * A paragraph style.
 *
 * This is a named set of paragraph and character format attributes,
 * which must be applied to whole paragraphs. Paragraph styles may be
 * used in rich text. Global text does not support styles.This class owns
 * a pointer to an object of class <code>CParagraphStyle</code>, which
 * stores the style information for the current paragraph; it also
 * references another pointer which is optional, and stores the style
 * information for the next paragraph. After construction, the
 * <code>RParagraphStyleInfo</code> object should be appended to a style
 * list (class <code>CStyleList</code>) which takes ownership of it.
 *
 * @since 5.0
 * @lib ""
 */

class RParagraphStyleInfo
	{
public:
	inline RParagraphStyleInfo();
	inline RParagraphStyleInfo(CParagraphStyle* aStyle,CParagraphStyle* aStyleForNextPara=NULL);
	inline void Discard();
public:
	CParagraphStyle* iStyle;  // owned
	CParagraphStyle* iStyleForNextPara;  // referenced, may be NULL
	};



/**
 *
 * Defines a paragraph style.
 *
 * A paragraph style is a named paragraph format layer which owns a set
 * of character format attributes, has an outline level and a type UID.
 * The outline level controls which headings should be shown when in
 * document outline view. The type UID is used to differentiate between
 * the word processor's built-in styles, which cannot be deleted, and
 * user-defined styles, which can be deleted.The style's paragraph format
 * attributes can be set using the functions derived from the base class
 * <code>CParaFormatLayer</code>. Its character format attributes can be
 * set through the owned <code>CCharFormatLayer*</code>. The style's
 * character and paragraph format attributes are based on the global
 * format layers specified on construction.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class CParagraphStyle : public CParaFormatLayer
// Defines a paragraph style as a named para format with richer attributes.
	{
public:
	friend class CStyleList;
	friend class CRichTextIndex;
	
/**
 *
 * Controls what happens to the styles when styled rich text is pasted
 * into another rich text object.
 * @since 
 */

	enum TStylePasteMode
		{
/** The pasted rich text retains all formatting and any new style
definitions are added to the style list of the rich text object into
which it is pasted.
 */
		EAddNewStyles,
/** The pasted rich text retains all formatting, including that specified
in the styles, but the new style definitions are not added to the
style list of the rich text object into which it is pasted. The
formatting specified in the styles becomes specific formatting.
 */
		EConvertNewStyles,
/** The pasted rich text loses all formatting specified in the styles. */
		EIgnoreNewStyles
		};
	
/**
 *
 * Retention of specific formatting.
 * @since 
 */

	enum TApplyParaStyleMode
		{
/** Specific character and paragraph formatting which has been applied to
the paragraph is retained when a style is applied. If the styles
formatting conflicts with the specific formatting, the specific
formatting overrides the style.
 */
		ERetainAllSpecificFormats,
/** Specific character and paragraph formatting which has been applied to
the paragraph is removed when a style is applied, regardless of
whether or not it conflicts with the style.
 */
		ERetainNoSpecificFormats,
/** Specific paragraph formatting which has been applied to the paragraph
is retained when a style is applied. If the styles formatting
conflicts with the specific paragraph formatting, the specific
formatting overrides the style.Specific character formatting which has
been applied to the paragraph is removed, regardless of whether or not
it conflicts with the style.
 */
		ERetainSpecificParaFormat,
/** Specific character formatting which has been applied to the paragraph
is retained when a style is applied. If the styles formatting
conflicts with the specific character formatting, the specific
formatting overrides the style.Specific paragraph formatting which has
been applied to the paragraph is removed, regardless of whether or not
it conflicts with the style.
 */
		ERetainSpecificCharFormat
		};
public:
	// Creates style & bases it on the speicfied global layers - the 'Normal' style.
	IMPORT_C static CParagraphStyle* NewL(const CParaFormatLayer& aGlobalParaFormatLayer,const CCharFormatLayer& aGlobalCharFormatLayer);
	IMPORT_C ~CParagraphStyle();
	//
	// Getters/Setters
	inline CCharFormatLayer* CharFormatLayer()const;
	inline TInt OutlineLevel()const;
	inline void SetOutlineLevel(TInt aOutlineLevel);
	//
	// Utilities
	IMPORT_C virtual TUid Type()const;
	inline void SetType(TUid aType);
	inline CParagraphStyle* CloneL()const;
private:
	CParagraphStyle();	
	void ConstructL(const CParaFormatLayer& aGlobalParaFormatLayer,
							 const CCharFormatLayer& aGlobalCharFormatLayer);
	IMPORT_C virtual CFormatLayer* DoCloneL()const;
	//
	// Save/Load
	static CParagraphStyle* NewL(RReadStream& aStream,const CParaFormatLayer& aGlobalParaFormatLayer,const CCharFormatLayer& aGlobalCharFormatLayer);
	virtual void InternalizeL(RReadStream& aStream,const CFormatLayer* aParaLayerBase,const CFormatLayer* aCharLayerBase);
	virtual void ExternalizeL(RWriteStream& aStream)const;
private:
	TUid iType;
	TInt iOutlineLevel;
	CCharFormatLayer* iCharFormatLayer;  // should never be NULL
public:
	TParagraphStyleName iName;
	};


const TInt KMaxStyleListGranularity=0x04;

/**
 *
 * A container of paragraph styles.
 *
 * It is implemented as a fixed length array of pointers to
 * <code>RParagraphStyleInfo</code>s. The array's granularity is
 * specified on construction. The list takes ownership of all paragraph
 * styles appended to it. When the list is deleted, all styles it owns
 * are also deleted.After the style list has been set up, it should
 * normally be passed to a <code>CRichText</code> object, either in the
 * rich text object's constructor, or by calling
 * <code>CRichText::SetStyleListExternallyOwned()</code>. The rich text
 * object takes ownership of the style list (unless
 * <code>SetStyleListExternallyOwned()</code> is used). Styles can be
 * modified, added to and removed from the style list after ownership of
 * the list has been passed to the rich text object.If
 * <code>CRichText::SetStyleListExternallyOwned()</code> is used, the
 * style list is not owned by the rich text object, and it must be stored
 * and restored separately from the rich text object.
 *
 * @since 5.0
 * @lib ""
 */

class CStyleList : public CBase
	{
public:
	IMPORT_C static CStyleList* NewL(TInt aCapacity=KMaxStyleListGranularity);
	IMPORT_C static CStyleList* NewL(RReadStream& aStream,
									const CParaFormatLayer* aGlobalParaFormatLayer,
									const CCharFormatLayer* aGlobalCharFormatLayer);
	IMPORT_C ~CStyleList();
	//
	inline const RParagraphStyleInfo& operator[](TInt aIndex)const;
	inline RParagraphStyleInfo& operator[](TInt aIndex);
	IMPORT_C const RParagraphStyleInfo& At(TInt aIndex)const;
	IMPORT_C RParagraphStyleInfo& At(TInt aIndex);
	//
	// Persistence
	IMPORT_C TStreamId StoreL(CStreamStore& aStore)const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream,
								const CParaFormatLayer* aGlobalParaFormatLayer,
								const CCharFormatLayer* aGlobalCharFormatLayer);
	//
	// Table maintenance
	IMPORT_C void Reset();  // Delete all styles from the style list.
	IMPORT_C TInt AppendL(RParagraphStyleInfo* aStyleSet);
	IMPORT_C void Remove(CParagraphStyle* aStyle);
	IMPORT_C TInt SetStyleToFollow(const RParagraphStyleInfo& aStyleSet);  // returns KErrNone or KErrNotFound
	IMPORT_C CStyleList* DeepCloneL()const;
	//
	// Getters
	IMPORT_C RParagraphStyleInfo* PtrByName(const TParagraphStyleName& aName)const;
	IMPORT_C RParagraphStyleInfo* PtrByType(const TUid aType)const;
	IMPORT_C TInt IndexByPtr(const CParaFormatLayer* aPtr)const;
	// Returns KErrNotFound if the specified style is not located in the style list.
	//
	IMPORT_C TInt IndexByName(const TDesC& aName)const;
	// Returns KErrNotFound if the specified style name is not located in the style list.
	//
	// General
	inline TInt Count()const;
protected:
	IMPORT_C CStyleList();
	IMPORT_C void ConstructL(TInt aGranularity);
private:
	void KillStyleList();
private:
	CArrayFixFlat<RParagraphStyleInfo>* iList;
	__DECLARE_TEST;
	};


#include <txtstyle.inl>

#endif