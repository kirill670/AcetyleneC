// EIKEDWIN.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef EIKEDWIN_PAN
#define EIKEDWIN_PAN

/** 
 * The enumeration <code>TEikEdwinPanic</code> contains panics relating to 
 * Edwin controls. 
 */
enum TEikEdwinPanic
    {
    /** not used */
    EEikPanicEdwinNoWidth,
    /** not used */
    EEikPanicEdwinNoHeight,
    /** not used */
    EEikPanicEdwinNotRichText,
    /** not used */
    EEikPanicEdwinNotOwnCharFormat,
    /** not used */
    EEikPanicEdwinNotOwnParaFormat,
    /** no associated text view object */
    EEikPanicEdwinNoView,
    /** not used */
    EEikPanicEdwinBadAttribute,
    /** unknown clipboard function - not defined by <code>TClipboardFunc</code> */
    EEikPanicEdwinBadClipboardFunc,
    /** no associated plain text object */
    EEikPanicEdwinNoText,
    /** no associated <code>CTextLayout</code> object */
    EEikPanicEdwinNoLayout,
    /** not a window-owning control */
    EEikPanicEdwinNoWindow,
    /** document limit exceeds the limit */
    EEikPanicEdwinInvalidTextLimit,
    /** text insertion at an invalid position */
    EEikPanicEdwinInvalidInsertPos,
    /** an attempt to format an invalid number of lines */
    EEikPanicEdwinInvalidNumberOfLines,
    /** not used */
    EEikPanicEdwinAutoScrollOnWithMultiLineEdwin
    };

GLREF_C void Panic(TEikEdwinPanic aPanic);

#endif   //EIKEDWIN_PAN
