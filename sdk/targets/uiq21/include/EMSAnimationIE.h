// Copyright (c) 2002 Symbian Ltd.  All rights reserved.

/**
 * @file EMSAnimationIE.h
 *
 * Defines  CEmsPreDefAnimation and CEmsAnimationIE classes
 */

#ifndef __EMSAnimationIE_H__
#define __EMSAnimationIE_H__

#include "EMSPictureIE.h"

#define KSmallAnimSize TSize(8,8)
#define KLargeAnimSize TSize(16,16)

/**
 * CEmsPreDefAnimationIE wraps the creation & modification of an EMS predefined animation
 * information element into a single class.
 *
 * Format of PreDef animation Information Element.
 * -----------------------------------------------
 *
 * Position (Octet)		Bit		Description					
 *	1							Start Position
 *	2							PreDefined Animation Number
 *
 * The start position of the information element is relative to the PDU that contains the object.
 * However when within this class it will be an converted to an absolute position within the message.
 *
 * @see 3gpp Spec V5 section 9.2.3.24.10.1.4
 */
class CEmsPreDefAnimationIE : public CEmsInformationElement
	{
public:
	// EIESize is 1 because start position is not included
	enum {EIESize=1};
	enum TAnimType{
		EFlirty		=0x0, 
		EGlad		=0x1, 
		ESceptic	=0x2, 
		ESad		=0x3, 
		EWow		=0x4, 
		ECrying		=0x5, 
		EWinking	=0x6, 
		ELaughing	=0x7, 
		EIndifferent=0x8, 
		EKissing	=0x9, 
		EConfused	=0xA, 
		ETongueOut	=0xB, 
		EAngry		=0xC, 
		EGlasses	=0xD, 
		EDevil		=0xE};

	IMPORT_C static CEmsPreDefAnimationIE* NewL(TAnimType aAnimValue=EFlirty);
	IMPORT_C CEmsInformationElement* DuplicateL() const;
	IMPORT_C void CopyL(const CEmsPreDefAnimationIE& aSrc);
	
	IMPORT_C TAnimType Animation() const ;	
	IMPORT_C void SetAnimationL(TAnimType aValue);

private:
	CEmsPreDefAnimationIE(TAnimType aAnimValue);
	CEmsPreDefAnimationIE();
	virtual void EncodeBodyL(TPtr8 aPtr, TBool aIsForSerialisation) const;
	virtual void DecodeBodyL(const TPtrC8 aPtr, TBool aIsFromSerialisation);
	TAnimType iAnimNumber;
	};


/**
 * CEmsAnimationIE wraps the creation & modification of both an EMS large animation & small animation
 * information element into a single class.
 *
 * Format of Large/User Animation Information Element.
 * -----------------------------------------------
 *
 * Position (Octet)		Bit		Description					
 *	1							Start Position
 *	2..n						Animation Data
 *
 * The start position of the information element is relative to the PDU that contains the object.
 * However when within this class it will be an converted to an absolute position within the message.
 *
 * @see 3gpp Spec V5 section 9.2.3.24.10.1.5/6
 */

class CEmsAnimationIE : public CEmsInformationElement
	{
public:
	enum {EFramesPerMsg=4};
	enum {EIESmallSize=32, EIELargeSize=128};

	static CEmsAnimationIE* NewL();
	IMPORT_C static CEmsAnimationIE* NewL(const CFbsBitmap& aBitmap);
	IMPORT_C ~CEmsAnimationIE();
	IMPORT_C CEmsInformationElement* DuplicateL() const;
	IMPORT_C void CopyL(const CEmsAnimationIE& aSrc);	
	
	IMPORT_C CFbsBitmap* GetBitmapL() const;	

private:	
	CEmsAnimationIE();
	void ConstructL(const CFbsBitmap& aBitmap);
	virtual void EncodeBodyL(TPtr8 aPtr, TBool aIsForSerialisation) const;
	virtual void DecodeBodyL(const TPtrC8 aPtr, TBool aIsFromSerialisation);
	CFbsBitmap* GetBitmapL(const TSize& aSize, const TDesC8& aDataBuf)const;
	HBufC8* iData;
	};

#endif __EMSAnimationIE_H__


//eof
