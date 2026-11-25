// WNGMODEL.INL
//
// Copyright (c) Nokia Corporation 2001-2004. All rights reserved.
//
CRichText* CWordModel::Text()
	{return iText;}

CStyleList* CWordModel::StyleList()
	{return iStyleList;}

CArrayFix<TInt>* CWordModel::PageTable()
	{return iPageTable;}

CStyleShortCutList* CWordModel::StyleShortCutList()
	{return iStyleShortCutList;}

TChar& CWordModel::NormalStyleShortCut()
	{return iNormalStyleShortCut;}

#if !defined(__HILDON__)
CPrintSetup* CWordModel::PrintSetup()
	{return iPrintSetup;}
#endif
