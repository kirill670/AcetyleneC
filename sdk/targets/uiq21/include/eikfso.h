// EIKFSO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKFSO_H__)
#define __EIKFSO_H__


class MEikFileSelectionObserver
	{
public:
	enum TUpdateEvent
		{
		EPathChanged,
		EFullNameChanged,
		};
public:
	virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged) = 0;
	};

#endif
