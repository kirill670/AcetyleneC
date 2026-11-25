/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis
*/

#ifndef __EPOCABSTRACTPLUGIN_H
#define __EPOCABSTRACTPLUGIN_H

class CCoeControl;
class MCoeControlObserver;

/*************************************************************************

    class MOperaPluginNotifier
*/

class MOperaPluginNotifier
    {
public:
	enum TNotificationType
		{
		EEditCut,
		EEditCopy,
		EEditPaste,
		EEditDelete,
		EApplicationFocusChanged,
		ESystemNotification
		};
public:
	virtual TInt NotifyL(TNotificationType aCallType, TAny* aParam) = 0;
    };

/*************************************************************************

    class MOperaPluginAdapter
*/

class MOperaPluginAdapter
    {
public:
    virtual void PluginDeletedL()=0;
    virtual void OpenUrlL(const TDesC& aUrl,TBool aNewWindow=EFalse)=0;
    virtual void PluginCreatedL(CCoeControl* aControl)=0;
    virtual TBool HistoryHasPrevious() const=0;
    virtual void HistoryLoadPreviousL()=0;
    virtual TBool HistoryHasNext() const=0;
    virtual void HistoryLoadNextL()=0;
    };

/*************************************************************************

    class MOperaPlugin
*/

class MOperaPlugin
    {
public:
    virtual CCoeControl* Control()=0;
    virtual MCoeControlObserver* CoeControlObserver()=0;
    virtual MOperaPluginAdapter* PluginAdapter()=0;
    virtual void SetPluginNotifier(MOperaPluginNotifier*aPluginNotifier)=0;
    };

#endif
