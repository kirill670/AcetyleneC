/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright (C) 1995-2000 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
*/

// Creator: JB 11/09-1999
// Purpose: Abstract the SetCursor(...) and GetCursor(...) functions, so that they
// get out of the core (doc.cpp, win_man.cpp)

#ifndef _CURSOR_H_	// {
#define _CURSOR_H_
#define HAS_MOUSECURSOR_CLASS

enum CursorType
{
	URI,
	CROSSHAIR,
	DEFAULT_ARROW,
	CUR_POINTER,
	MOVE,
	E_RESIZE,
	NE_RESIZE,
	NW_RESIZE,
	N_RESIZE,
	SE_RESIZE,
	SW_RESIZE,
	S_RESIZE,
	W_RESIZE,
	TEXT,
	WAIT,
	HELP,
	HOR_SPLITTER,
	VERT_SPLITTER,
	ARROW_WAIT,

	NUM_CURSORS			// added 26/7-00 <JB>
};

class MouseCursor			// the 'Cursor' structure has been taken already on the Macintosh!
{
private:
	CursorType			curCursor;						// current cursor

public:
						MouseCursor();					// load/initialize cursor array
						~MouseCursor();
	void				SetCursor(CursorType newCursor);
#ifdef _MACINTOSH_
	void				ReapplyCursor();
#endif
	inline CursorType	GetCursor(){ return(curCursor); }
//	BOOL				Available(CursorType cursor);	// return true if cursor exist
//	void				Show();							// show cursor on screen
//	void				Hide();							// make cursor invisible
};

extern	MouseCursor	*gMouseCursor;

#endif		// } _CURSOR_H_
