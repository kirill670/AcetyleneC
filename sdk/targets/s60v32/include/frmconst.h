// FRMCONST.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

// 
// FOR INFORMATION ONLY (CONTAINS PANIC NUMBERS, ETC.) - NOT PART OF INTERFACE
//

#ifndef __FRMCONST_H__
#define __FRMCONST_H__

#include <w32std.h>

/** 
Visible versions of control characters.
@internalComponent
*/
const TText KVisibleParagraphBreak = 0x00B6;		// paragraph sign (pilcrow)
const TText KVisibleLineBreak = 0x2193;				// down arrow
const TText KVisibleNonBreakSpace = 0x00B0;			// degree sign
const TText KVisiblePotentialHyphen = 0x00AC;		// not sign
const TText KVisibleNonBreakHyphen = 0x007E;		// spacing tilde
const TText KVisibleSpace = 0x00B7;					// middle dot
const TText KVisibleTab = 0x2192;					// right arrow
const TText KVisiblePicture = 0x25A3;				// white square containing small black square

/**
Control characters to allow or inhibit line breaks.
@internalComponent
*/
const TText KZeroWidthSpace = 0x200B;
const TText KZeroWidthNoBreakSpace = 0xFEFF;

/**
@publishedAll

*/
enum TFormPanic
	{
	EFDummy = 0,				// Not used

	// Used in ASSERT_ALWAYS

	// Parameter errors
	EFInvalidDocument = 200,	// Document handle NULL has been passed in
	EFInvalidLayout,			// A NULL layout handle has been passed in
	EFBadCharacterEditType,		// The character edit type was unknown or incompatible with the format changed value
	EFInvalidJumpValue,			// The horizontal scroll jump value has been set outside the allowable range (0,9999)

	// Document
	EFInvalidDocPos = 300,		// No or negative document position specified or greater than current document length

	// Drawing
	EFLineCursorBitmapNotSet = 400,	// The function CTextView::SetLineCursorBitmap has not been called even though a line cursor is being used

	// Pagination
	EFDocumentToPaginateNotSet = 500, // No document to paginate 
 	EFInvalidNumberCharsOnPage,	// Appending zero or negative characters per page to page list
	EFPageListEmpty,			// Page list should not be empty at this point

	// Printing
	EFInvalidPageList = 600,	// The array containing the number of characters per page has not been set or is defective
	EFInvalidPageNumber,		// A page requested that is outside the page list given.

	// Used only in ASSERT_DEBUG

	// Errors in internal format information
	EFNotEnoughFormat = 700,	// Format doesn't fill band but is not to end of document
	EFZeroHeightLine,			// A lines says it has height zero
	EFSelectedRangeZeroLen,		// The selected range flag is on but the selection has zero length
	EFCursorNotInCurrentFormat,	// The cursor is a document position that is outside the formatted range
	EFPixelNotInFormattedLine,	// GetLineRect pixel that was asked for
 	EFScrollCurtailed,			// The complete scroll should have been possible

	// Logic error during format process
	EFSelectionCannotCharEdit = 800,	// Should not be calling HandleCharEdit when there is a selection
	EFFormatOutOfDate,			// This function should not be called when the format is out of date
	EFBackgroundFormatting,		// Background formatting should not be going on

	// Scrolling errors
	EFScrollByZero1 = 900,		// The request for a scroll returned zero as the ammount to scroll by
	EFScrollByZero2,			// A routine that does the scrolling is called with a value of zero or one having wrong sign
	EFScrollError,				// Algorithmic or assumption error in the scroll routine
	EFScrollDownError,			// Error when scrolling text down
	EFScrollUpError,			// Error when scrolling text up
	EFInvalidScrollingType,		// A scrolling routine was expecting a certain type of scroll and got a different one

	// Out of memory
	EFNoMemory = 1000,			// Cannot do this when in no memory mode
	EFRecoverNoMemory,			// Trying to recover from no_memory when no no_memory condition has occured

	// Cursor
	EFCursorOffDisplay = 1100,	// The cursor has been moved to a position off the screen
	EFNoCursorPositionPolicy,	// Attempt to access the cursor navigation policy object when its pointer is 0
	EFPosHintInvalid,			// Invalid positioning hint value supplied to API
	EFPositionNotFormatted,		// Curosr APIs found formatting not available for position supplied.
	EFPositionInvalid,			// The document position was out of range for the current source document.

	// Drawing
	EFSelectionNotVisible = 1200, // Trying to toggle the highlight on part of the screen when the selection is not visible
 	EFPartialLineClearError,    // Clearing bottom partial line when not needed
	EFGcNotSet,					// The routine that does the display has been passed a null pointer to a graphics context

	//Internal Coding Errors	   
	EFViewNotPositionedCorrectly = 1300, // SetViewL has put the text at the wrong vertical height
	EFShouldNotLeave,			// The function call should not leave in this situation
	EFIncorrectCursorMovement,	// Trying to move cursor using wrong function call
	EFNoPictureFrame,			// Should be current picture frame
	EFSystemConstantsChanged,	// A value of a system constant has changed to a value that has broken this code
	};

/**
@internalComponent
*/
void FormPanic(TFormPanic aPanic);


enum TCursorMove
/**
This enum holds all the allowed movements of the document cursor by this
cursor positioning framework.
@publishedPartner

*/
	{
	/** No cursor movement */
	ECursNoMovement,
    /** Single character cursor movement to the left */
    ECursLeft,
    /** Single character cursor movement to the right */
    ECursRight,
    /** Line up cursor movement */
    ECursLineUp,
    /** Line down cursor movement */
    ECursLineDown,
    /** Not used, present for backwards compatibility for page movement */
    ECursReserved1,
    ECursReserved2,
    /** Cursor movement to line start */
    ECursLineBegin,
    /** Cursor movement to line end */
    ECursLineEnd
	};


// __FRMCONST_H__
#endif
