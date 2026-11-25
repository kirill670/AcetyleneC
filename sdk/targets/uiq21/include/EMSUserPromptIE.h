// Copyright (c) 2002 Symbian Ltd.  All rights reserved.

/**
 * @file EMSUserPromptIE.h
 *
 * Defines  CEmsUserprompt class
 */

#ifndef __EMSUserPromptIE_H__
#define __EMSUserPromptIE_H__

/**
 * CEmsUserPrompt wraps the creation & modification of the user prompt
 * information elements into a single class.
 *
 * Format of EMS Object
 * ------------------------------------------
 *
 * Position (Octet)		Bit		Description					
 *	1							Object count
 * 
 * @see 3gpp Spec V5 section 9.2.3.24.10.1.10
 */
#include "emsinformationelement.h"

class CEmsUserPrompt : public CEmsInformationElement
	{
public:
	enum {EIESize=1};

public:
	IMPORT_C static CEmsUserPrompt* NewL(TUint aObjectCount=1);
	IMPORT_C CEmsInformationElement* DuplicateL() const;
	IMPORT_C void CopyL(const CEmsUserPrompt& aSrc);	
	IMPORT_C TUint ObjectCount() const;
	IMPORT_C void SetObjectCount(TUint aObjectCount);

private:
	virtual void EncodeBodyL(TPtr8 aPtr, TBool aIsForSerialisation) const;
	virtual void DecodeBodyL(const TPtrC8 aPtr, TBool aIsFromSerialisation);
	CEmsUserPrompt(TUint aObjectCount = 0);
	TUint iObjectCount;
	};

#endif __EMSUserPromptIE_H__


//eof.
