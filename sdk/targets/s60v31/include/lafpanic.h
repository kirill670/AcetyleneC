/*
* ==============================================================================
*  Name        : lafpanic.h
*  Part of     : 
*  Description : 
*  Version     :  
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef __LAFPANIC_H__
#define __LAFPANIC_H__

enum TLafPanic
	{
	ELafPanicPointerCursorIndexOutOfRange,
	ELafPanicFontIndexOutOfRange,
	ELafPanicConstantNotKnown,
	ELafPanicMsgWinBadHorizontalAlignment,
	ELafPanicMsgWinBadVerticalAlignment,
	ELafPanicBitmapIndexOutOfRange,
	ELafPanicNotificationWithoutRequest,
    ELafPanicFontUidUnknownOrMissing,
    ELafPanicUsingFontFromWrongVariant,
    ELafPanicFontCreationFailure
	};

//__LAFPANIC_H__
#endif

// End of file.
