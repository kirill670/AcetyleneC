/*
* ============================================================================
*  Name       : PtiUserDicEntry.h
*  Part of    : PtiEngine
*  Description: User dictionary interface
*  Version:
*
*  Copyright © 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef _PTI_USERDICENTRY_H
#define _PTI_USERDICENTRY_H

// INCLUDES
#include <e32base.h>

// CONSTANTS
const TInt KMaxUserDictionaryEntrySize = 100;

class MPtiUserDictionaryEntry
    {
    public:
        virtual TPtrC Word() const = 0;
        virtual TPtrC Reading() const = 0;
        virtual void SetWord(TDesC& aWord, TDesC& aReading) = 0;
		virtual void SetWord(TDesC& aWord) = 0;
    };


// This is for latin languages (or any other language, which needs
// only one component (=word) for user dictionary entry).
// Implementation of Reading() method is same as implementation of
// Word() method.
class TPtiUserDictionaryEntry : public MPtiUserDictionaryEntry
	{
	public:		
		inline TPtiUserDictionaryEntry();
		inline TPtiUserDictionaryEntry(const TDesC& aWord);

	    inline TPtrC Word() const;
        inline TPtrC Reading() const;
        inline void SetWord(TDesC& aWord, TDesC& aReading);
		inline void SetWord(TDesC& aWord);

	private:
		TBuf<KMaxUserDictionaryEntrySize> iEntry;
	};

#include "PtiUserDicEntry.inl"

#endif

// End of file
 
