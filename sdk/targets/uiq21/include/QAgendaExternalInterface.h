// QAGENDAEXTERNALINTERFACE.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QAGENDAEXTERNALINTERFACE_H__
#define __QAGENDAEXTERNALINTERFACE_H__

#include <AGMIDS.H>
#include <VWSDEF.H>

const TUid KUidAgendaApp =				{0x10003A5C};
const TUid KUidAgendaDlg =              {0x1000679B};
const TUid KUidAgnViewDetail =			{0x10005200};
const TUid KUidAgnViewDay =				{0x100051fd};
const TUid KUidAgnViewWeek =			{0x100051fe};
const TUid KUidAgnViewMonth =			{0x100051e6};

const TUid KClipboardUidAgnEntryType =	{0x10003A6F};


/**
 * Agenda DNL:s
 */

/**
 * DNL to detail view in Agenda, creating a new entry with defaults
 */
const TUid KUidAgnDnlDetailNew     = {0x10005fbf};	// New entry thru tap on empyt slot.
const TUid KUidAgnDnlDetailNewMenu = {0x1000903A};	// New entry thru selecting 'New' in menu.
class TAgnDnlDetailNew
{
public:
	TTime iTimeDate;	// time and date of day to view in agenda day view
};
typedef TPckgBuf<TAgnDnlDetailNew> TAgnDnlDetailNewBuf;

/**
 * DNL to detail view in Agenda, editing agenda or todo entry
 */
const TUid KUidAgnDnlDetail =			{0x10005202};
const TUid KUidAgnDnlDetailTodo =		{0x10005fc0};
class TAgnDnlDetail
{
public:
	TAgnInstanceId iId; // id of agenda entry to view
						// nullid will create a new entry
						// invalid id will display an error message
};
typedef TPckgBuf<TAgnDnlDetail> TAgnDnlDetailBuf;


class TAgnDnlDetailTodo
{
public:
	TAgnUniqueId iId; // id of To do entry
};
typedef TPckgBuf<TAgnDnlDetailTodo> TAgnDnlDetailTodoBuf;

/**
 * DNL to day view in Agenda
 */
const TUid KUidAgnDnlDay =				{0x10005203};
class TAgnDnlDay
{
public:
	TTime iTimeDate;	// time and date of day to view in agenda day view
};
typedef TPckgBuf<TAgnDnlDay> TAgnDnlDayBuf;

/**
 * DNL to week view in Agenda
 */
const TUid KUidAgnDnlWeek =				{0x10005204};
class TAgnDnlWeek
{
public:
	TTime iDate;	// date to view in agenda week view
};
typedef TPckgBuf<TAgnDnlWeek> TAgnDnlWeekBuf;

/**
 * DNL to month view in Agenda
 */
const TUid KUidAgnDnlMonth =			{0x10005205};
class TAgnDnlMonth
{
public:
	TTime iDate;	// date to view in agenda month view
};
typedef TPckgBuf<TAgnDnlMonth> TAgnDnlMonthBuf;

#endif
