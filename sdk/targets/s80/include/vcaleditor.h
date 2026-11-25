//vcaleditor.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
#if !defined (__VCALEDITOR_H__)
#define __VCALEDITOR_H__

#include <eikrted.h> 
#include <badesca.h>	//Only used in Series 80.
 
class CParserVCal;
class CParserProperty;	//Only used in Series 80.

class CVCalEditor:public CEikRichTextEditor
	{
public:
	IMPORT_C	void FormatVCalToRichTextL(CParserVCal* aVCal);
	//This overwritten interface function should only be used from VCalViewer application
	//Structure of the aAttendees array should be :
	//n Attendee Role Mark (OPT, REQ, UNK) as a string
	//n+1. Attendee Email address
	//aIsRecurring tells that if the entry is has a recurrence property.
	IMPORT_C    void FormatVCalToRichTextL(CParserVCal* aVCal, CDesCArrayFlat* aAttendees, TBool aIsRecurring = EFalse);	//Only used in Series 80.
	IMPORT_C	~CVCalEditor();
	IMPORT_C	void	ConstructL(const CCoeControl* aParent,TInt aNumberOfLines,TInt aTextLimit,TInt aEdwinFlags,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);

private:
	void FormatVCalEventL(CParserVCal* aVCal);
	void FormatVCalToDoL(CParserVCal* aVCal);
	TInt iResourceFileOffset;
	};

#endif
