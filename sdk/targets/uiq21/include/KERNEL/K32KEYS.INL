// K32KEYS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TBool MatchesMaskedValue(TInt aModifiers,const TMaskedModifiers &aMaskedModifiers)
    {
    return (TBool)((aModifiers&aMaskedModifiers.iMask)==aMaskedModifiers.iValue);
    }

inline void MergeModifiers(TInt &aModifiers,const TMaskedModifiers &aMaskedModifiers)
// Set the masked bits only of the parameter
	{
	aModifiers&=~aMaskedModifiers.iMask;
	aModifiers|=(aMaskedModifiers.iMask&aMaskedModifiers.iValue);
	}

inline void TCtrlDigits::SetRadix(TRadix aRadix)
	{iRadix=aRadix;}

inline void TCtrlDigits::SetMaxCount(TInt aMaxCount)
	{iMaxCount=Min(aMaxCount, iMaximumCtrlDigitsMaxCount);}

inline TRadix TCtrlDigits::GetRadix() const
	{return iRadix;}

inline TBool TCtrlDigits::WithinLimits() const
	{return (TBool)(iDigits<=0xffffL);}

inline TUint TCtrlDigits::GetDigits() const
	{return iDigits;}

inline TBool TCtrlDigits::Error() const
	{return iErrorFlag;}

inline TUint TConvTable::FirstScanCode() const
	{return iFirstScanCode;}

inline TUint TConvTable::LastScanCode() const
	{return iLastScanCode;}

inline TCharExtended::TCharExtended():
	TChar(0)
	{}

inline TCharExtended::TCharExtended(TUint aChar):
	TChar(aChar)
	{}

