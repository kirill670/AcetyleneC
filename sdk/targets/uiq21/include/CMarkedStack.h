// CMarkedStack.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

// Template class to implement a marked stack. Conatins a stack itself of marks 
// providing basic marking functionality.

#ifndef __CMARKEDSTACK_H__
#define __CMARKEDSTACK_H__

// includes
#include <e32base.h>
#include <CStack.h>

//##ModelId=3B666BCD0001
template <class T, TBool Owner>
class CMarkedStack : public CStack<T, Owner>
{
protected:
class TMarkPoint
{
public:
	TMarkPoint(TInt aMarkType
		   , TInt aIndex)
	  : iMarkType(aMarkType)
	  , iStackIndex(aIndex)
	{}
	TInt iMarkType;
	TInt iStackIndex;
};
typedef CStack<TMarkPoint, ETrue> CMarks;
public:
	//##ModelId=3B666BCD0048
	inline virtual ~CMarkedStack();

	//##ModelId=3B666BCD0041
	inline void MarkL(TInt aMarkType);
	//##ModelId=3B666BCD003F
	inline TInt RemoveMark(TInt aMarkType);
	//##ModelId=3B666BCD003D
	inline void DeleteToMark(TInt aMarkType);
	//##ModelId=3B666BCD0033
	inline void ResetToMark(TInt aMarkType);
protected:
	//##ModelId=3B666BCD002D
	CMarks iMarks;
};

#include "CMarkedStack.inl"

#endif // __CMARKEDSTACK_H__
