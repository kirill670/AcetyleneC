// TXTFMLYR.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


/**
 *
 * Constructs and returns a new <code>CParaFormatLayer</code> with
 * identical formatting to the current layer.
 *
 * Note that the function does not copy the original layer's based-on
 * link the new layer's based-on link is set to NULL, so that the two
 * layers may not have the same effective formatting.
 *
 * @returns   " CParaFormatLayer* "
 *            A new paragraph format layer cloned from the current
 *            layer.
 */

inline CParaFormatLayer* CParaFormatLayer::CloneL()const
	{return STATIC_CAST(CParaFormatLayer*,DoCloneL());}


/**
 *
 * Constructs and returns a new <code>CCharFormatLayer</code> with
 * identical formatting to the current layer.
 *
 * Note that the function does not copy the original layer's based-on
 * link the new layer's based-on link is set to NULL, so that the two
 * layers may not have the same effective formatting.
 *
 * @returns   " CCharFormatLayer* "
 *            A new character format layer cloned from the current
 *            layer.
 */

inline CCharFormatLayer* CCharFormatLayer::CloneL()const
	{return STATIC_CAST(CCharFormatLayer*,DoCloneL());}
