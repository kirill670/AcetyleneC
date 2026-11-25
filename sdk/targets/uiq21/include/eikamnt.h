// EIKAMNT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKAMNT_H__)
#define __EIKAMNT_H__

#include <e32base.h>

class CGulIcon;
class MEikAutoMenuObserver;

/**
 *
 * A menu title that will be added to a standard resource-constructed
 * menu bar.
 *
 * If added to the <code>CEikAutoMenuTitleArray</code> stored by
 * <code>CEikonEnv</code> during standard application start up, the menu
 * pane specified will appear in all applications. The menu observer
 * passed in is notified of any events on such menu panes in preference
 * to the usual observer (<code>C<MyApp>AppUi</code>).
 *
 * @since 6.0
 * @lib "eikcore.lib"
 */
class CEikAutoMenuTitle : public CBase
	{
public:
	/**
	 *
	 * Specifies the position of a menu title in a menu.
	 *
	 * If an array of menu titles holds more than one menu title that is
	 * specified for the start or end of a menu, the menu titles are placed
	 * in the same order as that in which they appear in the array. This
	 * means the first menu title specified with <code>EStart</code> in an
	 * array will be the first on a menu bar and the last <code>EEnd</code>
	 * will be the last on a menu bar.
	 */
	enum TTitlePos
		{
		EStart,	/** Place the menu title first in a menu. */
		EEnd	/** Place the menu title last in a menu. */
		};
	enum { ENominalTextLength=40 };
public:
	IMPORT_C static CEikAutoMenuTitle* NewLC(TTitlePos aPos,const TDesC& aText,MEikAutoMenuObserver& aMenuObserver,
										TInt aMenuPaneResourceId=0,CGulIcon* aIcon=NULL);
	IMPORT_C ~CEikAutoMenuTitle();
private:
	CEikAutoMenuTitle(TTitlePos aPos,const TDesC& aText,MEikAutoMenuObserver& aMenuObserver,
										TInt aMenuPaneResourceId,CGulIcon* aIcon);
public:
	TTitlePos iPos;
	TBuf<ENominalTextLength> iText;
	MEikAutoMenuObserver& iMenuObserver;
	TInt iMenuPaneResourceId;
	CGulIcon* iIcon;
	};

/**
 *
 * Standard Epoc array of CEikAutoMenuTitles
 * If more than one title is specified for the start or end, they will be placed in the same order they appear
 * in the array (so the first EStart in the array will be the first on a menu bar also but the last EEnd will
 * be the last).
 *
 * @since 6.0
 * @lib "eikcore.lib"
 */
class CEikAutoMenuTitleArray : public CArrayPtrFlat<CEikAutoMenuTitle>
	{
public:
	CEikAutoMenuTitleArray();
	~CEikAutoMenuTitleArray();
	};

#endif
