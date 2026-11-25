// EIKLBVO.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

//
// MEikListBoxViewObserverClass
//

#if !defined(__EIKLBVO_H__)
#define __EIKLBVO_H__

class CListBoxView;


/**
 * Interface for objects wishing to observe a <code>CListBoxView</code>.
 *
 * @since		6.2
 * @internal
 */
class MEikListBoxViewObserver
	{
public:
	enum TListBoxViewEvent
		{
		EEventSelectionChanged
		};
public:
	virtual void HandleListBoxViewEventL(CListBoxView* aListBoxView, TListBoxViewEvent aEventType)=0;
	};

#endif
