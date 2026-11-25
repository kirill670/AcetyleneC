// Copyright (c) 2002 Symbian Ltd.  All rights reserved.

/**
 * @file EMSSoundIE.h
 *
 * Defines  CEmsPreDEfSound and CEmsSoundIE  classes
 */

#ifndef __EMSSoundIE_H__
#define __EMSSoundIE_H__

#include "EMSInformationElement.h"

/**
 * CEmsSoundIE wraps the creation & modification of the user & predefined sound
 * information elements into a single class.
 *
 * Format of Extended Object PreDefined Sound.
 * ------------------------------------------
 *
 * Position (Octet)		Bit		Description					
 *	1							Start Position
 *	2							Number of predef sound
 *
 * Format of Extended Object User Defined Sound.
 * --------------------------------------------
 *
 * Position (Octet)		Bit		Description					
 *	1							Start Position
 *	2..n						Sound Data (iMelody)
 *
 * @see 3gpp Spec V5 section 9.2.3.24.10.1.2/3
 */

class CEmsPreDefSoundIE : public CEmsInformationElement
{
public:
		enum TPredefinedSound {EChimesHigh=0, EChimesLow, EDing, ETaDa, ENotify, EDrum, EClaps, EFanFar, EChordHigh, EChordLow};
		IMPORT_C static CEmsPreDefSoundIE* NewL(TPredefinedSound aSound=EChimesHigh);
		IMPORT_C CEmsInformationElement* DuplicateL() const;
		        
		IMPORT_C void CopyL(const CEmsPreDefSoundIE& aSrc);
		IMPORT_C TPredefinedSound PredefinedSound() const;
private:
		CEmsPreDefSoundIE();
		virtual void EncodeBodyL(TPtr8 aPtr, TBool aIsForSerialisation) const;
		virtual void DecodeBodyL(const TPtrC8 aPtr, TBool aIsFromSerialisation);
		void ConstructL(TPredefinedSound aSound);
		TPredefinedSound iSound;

};

class CEmsSoundIE : public CEmsInformationElement
	{
public:
	enum {EMaxSoundLength=128};

	static CEmsSoundIE* NewL();	
	IMPORT_C static CEmsSoundIE* NewL(const TDesC8& aMelody);
	
	IMPORT_C CEmsInformationElement* DuplicateL() const;
	IMPORT_C ~CEmsSoundIE();    
	IMPORT_C void CopyL(const CEmsSoundIE& aSrc);
		
	IMPORT_C const HBufC8* Melody() const;

private:
	CEmsSoundIE();	
	void ConstructL(const TDesC8& aMelody);
	virtual void EncodeBodyL(TPtr8 aPtr, TBool aIsForSerialisation) const;
	virtual void DecodeBodyL(const TPtrC8 aPtr, TBool aIsFromSerialisation);
	void Reset();			
	HBufC8* iMelody;		
	};


#endif __EMSSoundIE_H__

//eof.
