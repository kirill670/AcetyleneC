// E32STD.INL
//
// Copyright (c) Symbian Software Ltd 1994-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/

// Global operator new
inline TAny* operator new(TUint /*aSize*/, TAny* aBase)
	{return(aBase);}
inline TAny* operator new(TUint aSize, TLeave)
	{return User::AllocL(aSize);}

#ifndef __VC32__
inline TAny* operator new[](TUint aSize, TLeave)
	{return User::AllocL(aSize);}
#endif

// Class TInt64
inline TInt64::TInt64()
	{}
inline TInt64::TInt64(TUint aVal)
	: iLow(aVal),iHigh(0)
	{}
inline TInt64::TInt64(TUint aHigh,TUint aLow)
	: iLow(aLow),iHigh(aHigh)
	{}
inline void TInt64::Set(TUint aHigh,TUint aLow)
	{iLow=aLow;iHigh=aHigh;}
inline TUint TInt64::Low() const
	{return(iLow);}
inline TUint TInt64::High() const
	{return(iHigh);}
inline TInt64 &TInt64::operator=(TUint aVal)
	{iLow=aVal;iHigh=0;return(*this);}

// Class TRefByValue
template <class T>
inline TRefByValue<T>::TRefByValue(T &aRef)
	: iRef(aRef)
	{}
template <class T>
inline TRefByValue<T>::operator T &()
	{return(iRef);}

// Class TCallBack
inline TCallBack::TCallBack()
	{iFunction=NULL;}
inline TCallBack::TCallBack(TInt (*aFunction)(TAny *aPtr))
	: iFunction(aFunction),iPtr(NULL)
	{}
inline TCallBack::TCallBack(TInt (*aFunction)(TAny *aPtr),TAny *aPtr)
	: iFunction(aFunction),iPtr(aPtr)
	{}
inline TInt TCallBack::CallBack() const
	{ return (iFunction ? (*iFunction)(iPtr) : 0); }

// Class TSglQue
template <class T>
inline TSglQue<T>::TSglQue()
	{}
template <class T>
inline TSglQue<T>::TSglQue(TInt anOffset)
	: TSglQueBase(anOffset)
	{}
template <class T>
inline void TSglQue<T>::AddFirst(T &aRef)
	{DoAddFirst(&aRef);}
template <class T>
inline void TSglQue<T>::AddLast(T &aRef)
	{DoAddLast(&aRef);}
template <class T>
inline TBool TSglQue<T>::IsFirst(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead);}
template <class T>
inline TBool TSglQue<T>::IsLast(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iLast);}
template <class T>
inline T *TSglQue<T>::First() const
	{return(PtrSub((T *)iHead,iOffset));}
template <class T>
inline T *TSglQue<T>::Last() const
	{return(PtrSub((T *)iLast,iOffset));}
template <class T>
inline void TSglQue<T>::Remove(T &aRef)
	{DoRemove(&aRef);}

// Class TDblQue
template <class T>
inline TDblQue<T>::TDblQue()
	{}
template <class T>
inline TDblQue<T>::TDblQue(TInt anOffset)
	: TDblQueBase(anOffset)
	{}
template <class T>
inline void TDblQue<T>::AddFirst(T &aRef)
	{DoAddFirst(&aRef);}
template <class T>
inline void TDblQue<T>::AddLast(T &aRef)
	{DoAddLast(&aRef);}
template <class T>
inline TBool TDblQue<T>::IsHead(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)&iHead);}
template <class T>
inline TBool TDblQue<T>::IsFirst(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iNext);}
template <class T>
inline TBool TDblQue<T>::IsLast(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iPrev);}
template <class T>
inline T *TDblQue<T>::First() const
	{
#if defined (_DEBUG)
	__DbgTestEmpty();
#endif
    return(PtrSub((T *)iHead.iNext,iOffset));
    }
template <class T>
inline T *TDblQue<T>::Last() const
	{
#if defined (_DEBUG)
	__DbgTestEmpty();
#endif
	return(PtrSub((T *)iHead.iPrev,iOffset));
	}

// Class TPriQue
template <class T>
inline TPriQue<T>::TPriQue()
	{}
template <class T>
inline TPriQue<T>::TPriQue(TInt anOffset)
	: TDblQueBase(anOffset)
	{}
template <class T>
inline void TPriQue<T>::Add(T &aRef)
	{DoAddPriority(&aRef);}
template <class T>
inline TBool TPriQue<T>::IsHead(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)&iHead);}
template <class T>
inline TBool TPriQue<T>::IsFirst(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iNext);}
template <class T>
inline TBool TPriQue<T>::IsLast(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iPrev);}
template <class T>
inline T *TPriQue<T>::First() const
	{return(PtrSub((T *)iHead.iNext,iOffset));}
template <class T>
inline T *TPriQue<T>::Last() const
	{return(PtrSub((T *)iHead.iPrev,iOffset));}

// Class TDeltaQue
template <class T>
inline TDeltaQue<T>::TDeltaQue()
	{}
template <class T>
inline TDeltaQue<T>::TDeltaQue(TInt anOffset)
	: TDeltaQueBase(anOffset)
	{}
template <class T>
inline void TDeltaQue<T>::Add(T &aRef,TInt aDelta)
	{DoAddDelta(&aRef,aDelta);}
template <class T>
inline void TDeltaQue<T>::Remove(T &aRef)
	{DoRemove(&aRef);}
template <class T>
inline T *TDeltaQue<T>::RemoveFirst()
	{return((T *) DoRemoveFirst());}

// Class TSglQueIter
template <class T>
inline TSglQueIter<T>::TSglQueIter(TSglQueBase &aQue)
	: TSglQueIterBase(aQue)
	{}
template <class T>
inline void TSglQueIter<T>::Set(T &aLink)
	{DoSet(&aLink);}
template <class T>
inline TSglQueIter<T>::operator T *()
	{return((T *)DoCurrent());}
template <class T>
inline T *TSglQueIter<T>::operator++(TInt)
	{return((T *)DoPostInc());}

// Class TDblQueIter
template <class T>
inline TDblQueIter<T>::TDblQueIter(TDblQueBase &aQue)
	: TDblQueIterBase(aQue)
	{}
template <class T>
inline void TDblQueIter<T>::Set(T &aLink)
	{DoSet(&aLink);}
template <class T>
inline TDblQueIter<T>::operator T *()
	{return((T *) DoCurrent());}
template <class T>
inline T *TDblQueIter<T>::operator++(TInt)
	{return((T *) DoPostInc());}
template <class T>
inline T *TDblQueIter<T>::operator--(TInt)
	{return((T *) DoPostDec());}

// Class TKey
inline void TKey::SetPtr(const TAny *aPtr)
	{iPtr=aPtr;}

// Class THeapWalk
inline TInt THeapWalk::Value() const
	{return(iValue);}
inline void THeapWalk::SetValue(TInt aValue)
	{iValue=aValue;}

// Class TChar
inline TChar::TChar()
	{}
inline TChar::TChar(TUint aChar)
	: iChar(aChar)
	{}
inline void TChar::SetChar(TUint aChar)
	{iChar=aChar;}
inline TChar& TChar::operator-=(TUint aChar)
	{iChar-=aChar;return(*this);}
inline TChar& TChar::operator+=(TUint aChar)
	{iChar+=aChar;return(*this);}
inline TChar TChar::operator-(TUint aChar)
	{return(iChar-aChar);}
inline TChar TChar::operator+(TUint aChar)
	{return(iChar+aChar);}
inline TChar::operator TUint() const
	{return(iChar);}
inline void TChar::Fold()
	{iChar=User::Fold(iChar);}
inline void TChar::LowerCase()
	{iChar=User::LowerCase(iChar);}
inline void TChar::UpperCase()
	{iChar=User::UpperCase(iChar);}
#ifdef _UNICODE
inline void TChar::Fold(TInt aFlags)
	{iChar=User::Fold(iChar,aFlags);}
inline void TChar::TitleCase()
	{iChar=User::TitleCase(iChar);}
#endif
inline TBool TChar::Eos() const
	{return(iChar==0);}

// Class TCharF
inline TCharF::TCharF(TUint aChar)
	: TChar(User::Fold(aChar))
	{}
inline TCharF::TCharF(const TChar& aChar)
	: TChar(User::Fold(aChar))
	{}
inline TCharF& TCharF::operator=(TUint aChar)
	{SetChar(User::Fold(aChar));return(*this);}
inline TCharF& TCharF::operator=(const TChar& aChar)
	{SetChar(User::Fold(aChar));return(*this);}

// Class TCharLC
inline TCharLC::TCharLC(TUint aChar)
	: TChar(User::LowerCase(aChar))
	{}
inline TCharLC::TCharLC(const TChar& aChar)
	: TChar(User::LowerCase(aChar))
	{}
inline TCharLC& TCharLC::operator=(TUint aChar)
	{SetChar(User::LowerCase(aChar));return(*this);}
inline TCharLC& TCharLC::operator=(const TChar& aChar)
	{SetChar(User::LowerCase(aChar));return(*this);}

// Class TCharUC
inline TCharUC::TCharUC(TUint aChar)
	: TChar(User::UpperCase(aChar))
	{}
inline TCharUC::TCharUC(const TChar& aChar)
	: TChar(User::UpperCase(aChar))
	{}
inline TCharUC& TCharUC::operator=(TUint aChar)
	{SetChar(User::UpperCase(aChar));return(*this);}
inline TCharUC& TCharUC::operator=(const TChar& aChar)
	{SetChar(User::UpperCase(aChar));return(*this);}

// Class TDesC8
inline TInt TDesC8::operator<(const TDesC8 &aDes) const
	{return(Compare(aDes)<0);}
inline TInt TDesC8::operator<=(const TDesC8 &aDes) const
	{return(Compare(aDes)<=0);}
inline TInt TDesC8::operator>(const TDesC8 &aDes) const
	{return(Compare(aDes)>0);}
inline TInt TDesC8::operator>=(const TDesC8 &aDes) const
	{return(Compare(aDes)>=0);}
inline TInt TDesC8::operator==(const TDesC8 &aDes) const
	{return(Compare(aDes)==0);}
inline TInt TDesC8::operator!=(const TDesC8 &aDes) const
	{return(Compare(aDes)!=0);}
inline const TUint8 &TDesC8::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TInt TDesC8::Length() const
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	return(iLength&KMaskDesLength8);
#else
	return(iLength);
#endif
	}
inline TInt TDesC8::Size() const
	{return(Length());}
inline void TDesC8::DoSetLength(TInt aLength)
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	iLength=(iLength&(~KMaskDesLength8))|aLength;
#else
	iLength=aLength;
#endif
	}

// Class TPtrC8
inline void TPtrC8::Set(const TUint8 *aBuf,TInt aLength)
	{new(this) TPtrC8(aBuf,aLength);}
inline void TPtrC8::Set(const TDesC8 &aDes)
	{new(this) TPtrC8(aDes);}
inline void TPtrC8::Set(const TPtrC8& aPtr)
	{new(this) TPtrC8(aPtr);}

// class TBufCBase8
inline TPtr8 TBufCBase8::DoDes(TInt aMaxLength)
	{return TPtr8(*this,aMaxLength);}

// Template class TBufC8
template <TInt S>
inline TBufC8<S>::TBufC8()
	: TBufCBase8()
	{}
template <TInt S>
inline TBufC8<S>::TBufC8(const TUint8 *aString)
	: TBufCBase8(aString,S)
	{}
template <TInt S>
inline TBufC8<S>::TBufC8(const TDesC8 &aDes)
	: TBufCBase8(aDes,S)
	{}
template <TInt S>
inline TBufC8<S> &TBufC8<S>::operator=(const TUint8 *aString)
	{Copy(aString,S);return(*this);}
template <TInt S>
inline TBufC8<S> &TBufC8<S>::operator=(const TDesC8 &aDes)
	{Copy(aDes,S);return(*this);}
template <TInt S>
inline TPtr8 TBufC8<S>::Des()
	{return DoDes(S);}

// Class HBufC8
inline HBufC8 &HBufC8::operator=(const HBufC8 &aLcb)
	{return *this=static_cast<const TDesC8&>(aLcb);}

// Class TDes8
inline TDes8 &TDes8::operator=(const TUint8 *aString)
    {Copy(aString);return(*this);}
inline TDes8 &TDes8::operator=(const TDesC8 &aDes)
    {Copy(aDes);return(*this);}
inline TDes8 &TDes8::operator=(const TDes8 &aDes)
    {Copy(aDes);return(*this);}
inline TDes8 &TDes8::operator+=(const TDesC8 &aDes)
	{Append(aDes);return(*this);}
inline const TUint8 &TDes8::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TUint8 &TDes8::operator[](TInt anIndex)
	{return((TUint8 &)AtC(anIndex));}
inline TInt TDes8::MaxLength() const
	{return(iMaxLength);}
inline TInt TDes8::MaxSize() const
	{return(iMaxLength);}
inline TUint8 * TDes8::WPtr() const
	{return((TUint8 *)Ptr());}

// Class TPtr8
inline TPtr8 &TPtr8::operator=(const TUint8 *aString)
	{Copy(aString);return(*this);}
inline TPtr8 &TPtr8::operator=(const TDesC8 &aDes)
	{Copy(aDes);return(*this);}
inline TPtr8 &TPtr8::operator=(const TPtr8 &aDes)
	{Copy(aDes);return(*this);}
inline void TPtr8::Set(TUint8 *aBuf,TInt aLength,TInt aMaxLength)
	{new(this) TPtr8(aBuf,aLength,aMaxLength);}
inline void TPtr8::Set(const TPtr8 &aPtr)
	{new(this) TPtr8(aPtr);}

// Template class TBuf8
template <TInt S>
inline TBuf8<S>::TBuf8()
	: TBufBase8(S)
	{}
template <TInt S>
inline TBuf8<S>::TBuf8(TInt aLength)
	: TBufBase8(aLength,S)
	{}
template <TInt S>
inline TBuf8<S>::TBuf8(const TUint8 *aString)
	: TBufBase8(aString,S)
	{}
template <TInt S>
inline TBuf8<S>::TBuf8(const TDesC8 &aDes)
	: TBufBase8(aDes,S)
	{}
template <TInt S>
inline TBuf8<S> &TBuf8<S>::operator=(const TUint8 *aString)
	{Copy(aString);return(*this);}
template <TInt S>
inline TBuf8<S> &TBuf8<S>::operator=(const TDesC8 &aDes)
	{Copy(aDes);return(*this);}
template <TInt S>
inline TBuf8<S>& TBuf8<S>::operator=(const TBuf8<S>& aBuf)
	{Copy(aBuf);return *this;}

// Template class TLitC8
template <TInt S>
inline const TDesC8* TLitC8<S>::operator&() const
	{return REINTERPRET_CAST(const TDesC8*,this);}
template <TInt S>
inline const TDesC8& TLitC8<S>::operator()() const
	{return *operator&();}
template <TInt S>
inline TLitC8<S>::operator const TDesC8&() const
	{return *operator&();}
template <TInt S>
inline TLitC8<S>::operator const __TRefDesC8() const
	{return *operator&();}

// Class TDesC16
inline TInt TDesC16::operator<(const TDesC16 &aDes) const
	{return(Compare(aDes)<0);}
inline TInt TDesC16::operator<=(const TDesC16 &aDes) const
	{return(Compare(aDes)<=0);}
inline TInt TDesC16::operator>(const TDesC16 &aDes) const
	{return(Compare(aDes)>0);}
inline TInt TDesC16::operator>=(const TDesC16 &aDes) const
	{return(Compare(aDes)>=0);}
inline TInt TDesC16::operator==(const TDesC16 &aDes) const
	{return(Compare(aDes)==0);}
inline TInt TDesC16::operator!=(const TDesC16 &aDes) const
	{return(Compare(aDes)!=0);}
inline const TUint16 &TDesC16::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TInt TDesC16::Length() const
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	return(iLength&KMaskDesLength16);
#else
	return(iLength);
#endif
	}
inline TInt TDesC16::Size() const
	{return(Length()<<1);}
inline void TDesC16::DoSetLength(TInt aLength)
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	iLength=(iLength&(~KMaskDesLength16))|aLength;
#else
	iLength=aLength;
#endif
	}

// Class TPtrC16
inline void TPtrC16::Set(const TUint16 *aBuf,TInt aLength)
	{new(this) TPtrC16(aBuf,aLength);}
inline void TPtrC16::Set(const TDesC16 &aDes)
	{new(this) TPtrC16(aDes);}
inline void TPtrC16::Set(const TPtrC16& aPtr)
	{new(this) TPtrC16(aPtr);}

// class TBufCBase16
inline TPtr16 TBufCBase16::DoDes(TInt aMaxLength)
	{return TPtr16(*this,aMaxLength);}

// Template class TBufC16
template <TInt S>
inline TBufC16<S>::TBufC16()
	: TBufCBase16()
	{}
template <TInt S>
inline TBufC16<S>::TBufC16(const TUint16 *aString)
	: TBufCBase16(aString,S)
	{}
template <TInt S>
inline TBufC16<S>::TBufC16(const TDesC16 &aDes)
	: TBufCBase16(aDes,S)
	{}
template <TInt S>
inline TBufC16<S> &TBufC16<S>::operator=(const TUint16 *aString)
	{Copy(aString,S);return(*this);}
template <TInt S>
inline TBufC16<S> &TBufC16<S>::operator=(const TDesC16 &aDes)
	{Copy(aDes,S);return(*this);}
template <TInt S>
inline TPtr16 TBufC16<S>::Des()
	{return(DoDes(S));}

// Class HBufC16
inline HBufC16 &HBufC16::operator=(const HBufC16 &aLcb)
	{return *this=static_cast<const TDesC16&>(aLcb);}

// Class TDes16
inline TDes16 &TDes16::operator=(const TUint16 *aString)
    {Copy(aString);return(*this);}
inline TDes16 &TDes16::operator=(const TDesC16 &aDes)
    {Copy(aDes);return(*this);}
inline TDes16 &TDes16::operator=(const TDes16 &aDes)
    {Copy(aDes);return(*this);}
inline TDes16 &TDes16::operator+=(const TDesC16 &aDes)
	{Append(aDes);return(*this);}
inline const TUint16 &TDes16::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TUint16 &TDes16::operator[](TInt anIndex)
	{return((TUint16 &)AtC(anIndex));}
inline TInt TDes16::MaxLength() const
	{return(iMaxLength);}
inline TInt TDes16::MaxSize() const
	{return(iMaxLength<<1);}
inline TUint16 * TDes16::WPtr() const
	{return((TUint16 *)Ptr());}

// Class TPtr16
inline TPtr16 &TPtr16::operator=(const TUint16 *aString)
	{Copy(aString);return(*this);}
inline TPtr16 &TPtr16::operator=(const TDesC16 &aDes)
	{Copy(aDes);return(*this);}
inline TPtr16 &TPtr16::operator=(const TPtr16 &aDes)
	{Copy(aDes);return(*this);}
inline void TPtr16::Set(TUint16 *aBuf,TInt aLength,TInt aMaxLength)
	{new(this) TPtr16(aBuf,aLength,aMaxLength);}
inline void TPtr16::Set(const TPtr16 &aPtr)
	{new(this) TPtr16(aPtr);}

// Template class TBuf16
template <TInt S>
inline TBuf16<S>::TBuf16()
	: TBufBase16(S)
	{}
template <TInt S>
inline TBuf16<S>::TBuf16(TInt aLength)
	: TBufBase16(aLength,S)
	{}
template <TInt S>
inline TBuf16<S>::TBuf16(const TUint16 *aString)
	: TBufBase16(aString,S)
	{}
template <TInt S>
inline TBuf16<S>::TBuf16(const TDesC16 &aDes)
	: TBufBase16(aDes,S)
	{}
template <TInt S>
inline TBuf16<S> &TBuf16<S>::operator=(const TUint16 *aString)
	{Copy(aString);return(*this);}
template <TInt S>
inline TBuf16<S> &TBuf16<S>::operator=(const TDesC16 &aDes)
	{Copy(aDes);return(*this);}
template <TInt S>
inline TBuf16<S>& TBuf16<S>::operator=(const TBuf16<S>& aBuf)
	{Copy(aBuf);return *this;}


// Class RBuf8
/**
Creates 8 bit resizable buffer descriptor from the stream.

@param aStream Input stream.
@param aMaxLength The maximum length of the buffer.
@leaves One of the system wide errors.
*/
inline void RBuf8::CreateL(RReadStream &aStream,TInt aMaxLength)
	{
	Assign(HBufC8::NewL(aStream,aMaxLength));
	}

// Class RBuf16
/**
Creates 16 bit resizable buffer descriptor from the stream.

@param aStream Input stream.
@param aMaxLength The maximum length of the buffer.
@leave One of the system wide errors.
*/
inline void RBuf16::CreateL(RReadStream &aStream,TInt aMaxLength)
	{
	Assign(HBufC16::NewL(aStream,aMaxLength));
	}


// Template class TLitC16
template <TInt S>
inline const TDesC16* TLitC16<S>::operator&() const
	{return REINTERPRET_CAST(const TDesC16*,this);}
template <TInt S>
inline const TDesC16& TLitC16<S>::operator()() const
	{return *operator&();}
template <TInt S>
inline TLitC16<S>::operator const TDesC16&() const
	{return *operator&();}
template <TInt S>
inline TLitC16<S>::operator const __TRefDesC16() const
	{return *operator&();}

// Template class TBufC
#ifdef _UNICODE
template <TInt S>
inline TBufC<S>::TBufC()
	: TBufCBase16()
	{}
template <TInt S>
inline TBufC<S>::TBufC(const TText *aString)
	: TBufCBase16(aString,S)
	{}
template <TInt S>
inline TBufC<S>::TBufC(const TDesC &aDes)
	: TBufCBase16(aDes,S)
	{}
#endif
template <TInt S>
inline TBufC<S> &TBufC<S>::operator=(const TText *aString)
	{Copy(aString,S);return(*this);}
template <TInt S>
inline TBufC<S> &TBufC<S>::operator=(const TDesC &aDes)
	{Copy(aDes,S);return(*this);}
template <TInt S>
inline TPtr TBufC<S>::Des()
	{return(DoDes(S));}

// Template class TBuf
#ifdef _UNICODE
template <TInt S>
inline TBuf<S>::TBuf()
	: TBufBase16(S)
	{}
template <TInt S>
inline TBuf<S>::TBuf(TInt aLength)
	: TBufBase16(aLength,S)
	{}
template <TInt S>
inline TBuf<S>::TBuf(const TText *aString)
	: TBufBase16(aString,S)
	{}
template <TInt S>
inline TBuf<S>::TBuf(const TDesC &aDes)
	: TBufBase16(aDes,S)
	{}
#endif
template <TInt S>
inline TBuf<S> &TBuf<S>::operator=(const TText *aString)
	{Copy(aString);return(*this);}
template <TInt S>
inline TBuf<S> &TBuf<S>::operator=(const TDesC &aDes)
	{Copy(aDes);return(*this);}
template <TInt S>
inline TBuf<S> &TBuf<S>::operator=(const TBuf<S> &aBuf)
	{Copy(aBuf);return(*this);}

// Template class TLitC
template <TInt S>
inline const TDesC* TLitC<S>::operator&() const
	{return REINTERPRET_CAST(const TDesC*,this);}
template <TInt S>
inline const TDesC& TLitC<S>::operator()() const
	{return *operator&();}
template <TInt S>
inline TLitC<S>::operator const TDesC&() const
	{return *operator&();}
template <TInt S>
inline TLitC<S>::operator const __TRefDesC() const
	{return *operator&();}

// Template class TPckgC
template <class T>
inline TPckgC<T>::TPckgC(const T &aRef)
	: TPtrC8((const TUint8 *)&aRef,sizeof(T))
	{}
template <class T>
inline const T &TPckgC<T>::operator()() const
	{return(*((const T *)iPtr));}

// Template class TPckg
template <class T>
inline TPckg<T>::TPckg(const T &aRef)
	: TPtr8((TUint8 *)&aRef,sizeof(T),sizeof(T))
	{}
template <class T>
inline T &TPckg<T>::operator()()
	{return(*((T *)iPtr));}

// Template class TPckgBuf
template <class T>
inline TPckgBuf<T>::TPckgBuf()
	: TBuf8<sizeof(T)>(sizeof(T))
	{new(&iBuf[0]) T;}
template <class T>
inline TPckgBuf<T>::TPckgBuf(const T &aRef)
	: TBuf8<sizeof(T)>(sizeof(T))
	{new(&iBuf[0]) T(aRef);}
template <class T>
inline TPckgBuf<T> &TPckgBuf<T>::operator=(const TPckgBuf<T> &aRef)
	{Copy(aRef);return(*this);}
template <class T>
inline T &TPckgBuf<T>::operator=(const T &aRef)
	{Copy((TUint8 *)&aRef,sizeof(T));return(*((T *)&iBuf[0]));}
template <class T>
inline T &TPckgBuf<T>::operator()()
	{return(*((T *)&iBuf[0]));}
template <class T>
inline const T &TPckgBuf<T>::operator()() const
	{return(*((T *)&iBuf[0]));}

// Class TDateTime
inline TDateTime::TDateTime()
	: iYear(1980),
	  iMonth(EJanuary), 
	  iDay(1),
	  iHour(0),
	  iMinute(0),
	  iSecond(0),
	  iMicroSecond(0)
	{}    

/**
 *
 * Gets the year component of the date/time.
 *
 * A negative value indicates a BC date.
 *
 * @returns   "TInt"
 *            The year
 */
       
inline TInt TDateTime::Year() const
	{return(iYear);}

/**
 *
 * Gets the month component of the date/time.
 *
 * @returns   "TMonth"
 *            The month. <code>EJanuary</code> to
 *            <code>EDecember</code>. Offset from zero, so add one
 *            before displaying the month number.
 */

inline TMonth TDateTime::Month() const
	{return(iMonth);}

/**
 *
 * Gets the day component of the date/time.
 *
 * @returns   "TInt"
 *            The day.Offset from zero, so add one before displaying
 *            the day number.
 */

inline TInt TDateTime::Day() const
	{return(iDay);}

/**
 *
 * Gets the hour component of the date/time.
 *
 * @returns   "TInt"
 *            The hour.
 */

inline TInt TDateTime::Hour() const
	{return(iHour);}

/**
 *
 * Gets the minute component of the date/time.
 *
 * @returns   "TInt"
 *            The minute.
 */

inline TInt TDateTime::Minute() const
	{return(iMinute);}

/**
 *
 * Gets the second component of the date/time.
 *
 * @returns   "TInt"
 *            The second.
 */

inline TInt TDateTime::Second() const
	{return(iSecond);}

/**
 *
 * Gets the microsecond component of the date/time.
 *
 * @returns   "TInt"
 *            The microsecond.
 */

inline TInt TDateTime::MicroSecond() const
	{return(iMicroSecond);}

// Class TTimeIntervalMicroSeconds

/**
 *
 * Constructs a <code>TTimeIntervalMicroSeconds</code>, initialised to an
 * arbitrary value.
 *
 * It is necessary because there is also a non-default constructor in
 * this class.
 *
 */

inline TTimeIntervalMicroSeconds::TTimeIntervalMicroSeconds()
	{}
inline TTimeIntervalMicroSeconds::TTimeIntervalMicroSeconds(const TInt64& aInterval)
	: iInterval(aInterval)
	{}

/**
 *
 * Assigns a 64-bit integer value to this
 * <code>TTimeIntervalMicroSeconds</code>.
 *
 * @param     "const TInt64& aInterval"
 *            The 64-bit value to assign to this
 *            <code>TTimeIntervalMicroSeconds</code>.
 * @returns   "TTimeIntervalMicroSeconds&"
 *            This <code>TTimeIntervalMicroSeconds</code>.
 */

inline TTimeIntervalMicroSeconds& TTimeIntervalMicroSeconds::operator=(const TInt64& aInterval)
	{iInterval=aInterval;return(*this);}

/**
 *
 * Tests whether two <code>TTimeIntervalMicroSeconds</code> objects are
 * equal.
 *
 * @param     "const TTimeIntervalMicroSeconds& aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the two time intervals are equal. False if not
 *            equal.
 */

inline TBool TTimeIntervalMicroSeconds::operator==(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval==aInterval.iInterval);}

/**
 *
 * Tests whether two <code>TTimeIntervalMicroSeconds</code> are not
 * equal.
 *
 * @param     "const TTimeIntervalMicroSeconds& aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the two time intervals differ. False if equal.
 */

inline TBool TTimeIntervalMicroSeconds::operator!=(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval!=aInterval.iInterval);}

/**
 *
 * Tests whether a <code>TTimeIntervalMicroSeconds</code> is greater than
 * or equal to another.
 *
 * @param     "const TTimeIntervalMicroSeconds& aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is greater than or
 *            equal to the second. False if not.
 */

inline TBool TTimeIntervalMicroSeconds::operator>=(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval>=aInterval.iInterval);}

/**
 *
 * Tests whether a <code>TTimeIntervalMicroSeconds</code> is less than or
 * equal to another.
 *
 * @param     "const TTimeIntervalMicroSeconds& aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is less than or equal
 *            to the second. False if not.
 */

inline TBool TTimeIntervalMicroSeconds::operator<=(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval<=aInterval.iInterval);}

/**
 *
 * Tests whether a <code>TTimeIntervalMicroSeconds</code> is greater than
 * another.
 *
 * @param     "const TTimeIntervalMicroSeconds& aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is greater than the
 *            second. False if not.
 */

inline TBool TTimeIntervalMicroSeconds::operator>(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval>aInterval.iInterval);}

/**
 *
 * Tests whether a <code>TTimeIntervalMicroSeconds</code> is less than
 * another.
 *
 * @param     "const TTimeIntervalMicroSeconds& aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is less than the
 *            second. False if not.
 */

inline TBool TTimeIntervalMicroSeconds::operator<(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval<aInterval.iInterval);}

/**
 *
 * Gets the 64-bit microsecond time interval.
 *
 * @returns   "TInt64&"
 *            This time interval in microseconds.
 */

inline const TInt64& TTimeIntervalMicroSeconds::Int64() const
	{return(iInterval);}

// Class TTimeIntervalBase
inline TTimeIntervalBase::TTimeIntervalBase()
	{}
inline TTimeIntervalBase::TTimeIntervalBase(TInt aInterval)
	: iInterval(aInterval)
	{}

/**
 *
 * Tests whether two time intervals are equal.
 *
 * @param     "TTimeIntervalBase aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the two time intervals are equal. False if not
 *            equal.
 */

inline TBool TTimeIntervalBase::operator==(TTimeIntervalBase aInterval) const
	{return(iInterval==aInterval.iInterval);}

/**
 *
 * Tests whether two time intervals are not equal.
 *
 * @param     "TTimeIntervalBase aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the two time intervals differ. False if equal.
 */

inline TBool TTimeIntervalBase::operator!=(TTimeIntervalBase aInterval) const
	{return(iInterval!=aInterval.iInterval);}

/**
 *
 * Tests whether one time interval is greater than or equal to another.
 *
 * @param     "TTimeIntervalBase aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is greater than or
 *            equal to the second. False if not.
 */

inline TBool TTimeIntervalBase::operator>=(TTimeIntervalBase aInterval) const
	{return(iInterval>=aInterval.iInterval);}

/**
 *
 * Tests whether one time interval is less than or equal to another.
 *
 * @param     "TTimeIntervalBase aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is less than or equal
 *            to the second. False if not.
 */

inline TBool TTimeIntervalBase::operator<=(TTimeIntervalBase aInterval) const
	{return(iInterval<=aInterval.iInterval);}

/**
 *
 * Tests whether one time interval is greater than another.
 *
 * @param     "TTimeIntervalBase aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is greater than the
 *            second. False if not.
 */

inline TBool TTimeIntervalBase::operator>(TTimeIntervalBase aInterval) const
	{return(iInterval>aInterval.iInterval);}

/**
 *
 * Tests whether one time interval is less than another.
 *
 * @param     "TTimeIntervalBase aInterval"
 *            The time interval to compare with this time interval.
 * @returns   "TBool"
 *            True if the first time interval is less than the
 *            second. False if not.
 */

inline TBool TTimeIntervalBase::operator<(TTimeIntervalBase aInterval) const
	{return(iInterval<aInterval.iInterval);}

/**
 *
 * Gets the time interval as a 32 bit integer.
 *
 * @returns   "TInt"
 *            The time interval as a 32 bit integer.
 */

inline TInt TTimeIntervalBase::Int() const
	{return(iInterval);}

// Class TTimeIntervalMicroSeconds32

inline TTimeIntervalMicroSeconds32::TTimeIntervalMicroSeconds32()
	{}

/**
 *
 * Constructs the object with a <code>TInt</code>.
 *
 * @param     "TInt aInterval"
 *            The interval with which to initialise the
 *            newly-constructed
 *            <code>TTimeIntervalMicroSeconds32</code>.
 */

inline TTimeIntervalMicroSeconds32::TTimeIntervalMicroSeconds32(TInt aInterval)
    : TTimeIntervalBase(aInterval)
	{}

/**
 *
 * Assigns an interval value to this
 * <code>TTimeIntervalMicroSeconds32</code>.
 *
 * @param     "TInt aInterval"
 *            The interval to assign to this
 *            <code>TTimeIntervalMicroSeconds32</code>.
 * @returns   "TTimeIntervalMicroSeconds32&"
 *            This <code>TTimeIntervalMicroSeconds32</code>.
 */

inline TTimeIntervalMicroSeconds32& TTimeIntervalMicroSeconds32::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalSeconds

/**
 *
 * Constructs an uninitialised <code>TTimeIntervalSeconds</code> object.
 *
 * It is necessary because there is also a non-default constructor in
 * this class.
 *
 */

inline TTimeIntervalSeconds::TTimeIntervalSeconds()
	{}
inline TTimeIntervalSeconds::TTimeIntervalSeconds(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}

/**
 *
 * Assigns an interval value to this <code>TTimeIntervalSeconds</code>.
 *
 * @param     "TInt aInterval"
 *            The interval to assign to this
 *            <code>TTimeIntervalSeconds</code>.
 * @returns   "TTimeIntervalSeconds&"
 *            This <code>TTimeIntervalSeconds</code>.
 */

inline TTimeIntervalSeconds& TTimeIntervalSeconds::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalMinutes

inline TTimeIntervalMinutes::TTimeIntervalMinutes()
	{}

/**
 *
 * Constructs the object with a <code>TInt</code>.
 *
 * @param     "TInt aInterval"
 *            The interval with which to initialise the
 *            newly-constructed <code>TTimeIntervalMinutes</code>.
 */

inline TTimeIntervalMinutes::TTimeIntervalMinutes(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}

/**
 *
 * Assigns a value to this <code>TTimeIntervalMinutes</code>.
 *
 * @param     "TInt aInterval"
 *            The interval to assign to this
 *            <code>TTimeIntervalMinutes</code>.
 * @returns   "TTimeIntervalMinutes&"
 *            This <code>TTimeIntervalMinutes</code>.
 */

inline TTimeIntervalMinutes& TTimeIntervalMinutes::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalHours

/**
 *
 * Constructs an uninitialised <code>TTimeIntervalHours</code> object.
 *
 * It is necessary because there is also a non-default constructor in
 * this class.
 *
 */

inline TTimeIntervalHours::TTimeIntervalHours()
	{}
inline TTimeIntervalHours::TTimeIntervalHours(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}

/**
 *
 * Assigns a value to this <code>TTimeIntervalHours</code>.
 *
 * @param     "TInt aInterval"
 *            The interval to assign to this
 *            <code>TTimeIntervalHours</code>.
 * @returns   "TTimeIntervalHours&"
 *            This <code>TTimeIntervalHours</code>.
 */

inline TTimeIntervalHours& TTimeIntervalHours::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalDays

inline TTimeIntervalDays::TTimeIntervalDays()
	{}

/**
 *
 * Constructs the object with a <code>TInt</code>.
 *
 * @param     "TInt aInterval"
 *            The interval with which the new object is to be
 *            initialised.
 */

inline TTimeIntervalDays::TTimeIntervalDays(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}

/**
 *
 * Assigns a value to this <code>TTimeIntervalDays</code>.
 *
 * @param     "TInt aInterval"
 *            The interval to assign to this
 *            <code>TTimeIntervalDays</code>.
 * @returns   "TTimeIntervalDays&"
 *            This <code>TTimeIntervalDays</code>.
 */

inline TTimeIntervalDays& TTimeIntervalDays::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalMonths
inline TTimeIntervalMonths::TTimeIntervalMonths()
	{}

/**
 *
 * Constructs the object with a <code>TInt</code>.
 *
 * @param     "TInt aInterval"
 *            The interval with which to initialise the
 *            newly-constructed <code>TTimeIntervalMonths</code>.
 */

inline TTimeIntervalMonths::TTimeIntervalMonths(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}

/**
 *
 * Assigns a value to this <code>TTimeIntervalMonths</code>.
 *
 * @param     "TInt aInterval"
 *            The interval to assign to this
 *            <code>TTimeIntervalMonths</code>.
 * @returns   "TTimeIntervalMonths&"
 *            This <code>TTimeIntervalMonths</code>.
 */

inline TTimeIntervalMonths& TTimeIntervalMonths::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalYears
inline TTimeIntervalYears::TTimeIntervalYears()
	{}

/**
 *
 * Constructs the interval, initialising it to the value specified in the
 * argument.
 *
 * @param     "TInt aInterval"
 *            The interval with which to initialise the
 *            newly-constructed <code>TTimeIntervalYears</code>.
 */

inline TTimeIntervalYears::TTimeIntervalYears(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}

/**
 *
 * Assigns a value to this <code>TTimeIntervalYears</code>.
 *
 * @param     "TInt aInterval"
 *            The value to assign to this
 *            <code>TTimeIntervalYears</code>.
 * @returns   "TTimeIntervalYears&"
 *            This <code>TTimeIntervalYears</code>.
 */

inline TTimeIntervalYears& TTimeIntervalYears::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTime
inline TTime::TTime()
	{}
inline TTime::TTime(const TInt64& aTime)
	: iTime(aTime)
	{}
inline TTime &TTime::operator=(const TInt64& aTime)
	{iTime=aTime;return(*this);}

/**
 *
 * Tests whether two date/times are equal.
 *
 * @param     "TTime aTime"
 *            The time to compare with this <code>TTime</code>.
 * @returns   "TBool"
 *            True if the two <code>TTime</code>s are equal. False
 *            if not
 */

inline TBool TTime::operator==(TTime aTime) const
	{return(iTime==aTime.iTime);}

/**
 *
 * Tests whether two date/times are not equal.
 *
 * @param     "TTime aTime"
 *            The date/time to compare with this <code>TTime</code>.
 * @returns   "TBool"
 *            True if the two <code>TTime</code>s are different.
 *            False if the same.
 */

inline TBool TTime::operator!=(TTime aTime) const
	{return(iTime!=aTime.iTime);}

/**
 *
 * Tests whether a date/time is after or is the same as another.
 *
 * @param     "TTime aTime"
 *            The time to compare with this <code>TTime</code>.
 * @returns   "TBool"
 *            True if the first <code>TTime</code> is after than or
 *            the same as the second. Otherwise false.
 */

inline TBool TTime::operator>=(TTime aTime) const
	{return(iTime>=aTime.iTime);}

/**
 *
 * Tests whether a date/time precedes or is the same as another.
 *
 * @param     "TTime aTime"
 *            The time to compare with this <code>TTime</code>.
 * @returns   "TBool"
 *            True if the first <code>TTime</code> precedes or is
 *            the same as the second. Otherwise false.
 */

inline TBool TTime::operator<=(TTime aTime) const
	{return(iTime<=aTime.iTime);}

/**
 *
 * Tests whether a date/time is after another.
 *
 * @param     "TTime aTime"
 *            The time to compare with this <code>TTime</code>.
 * @returns   "TBool"
 *            True if the first <code>TTime</code> is after the
 *            second. Otherwise false.
 */

inline TBool TTime::operator>(TTime aTime) const
	{return(iTime>aTime.iTime);}

/**
 *
 * Tests whether a date/time precedes another.
 *
 * @param     "TTime aTime"
 *            The time to compare with this <code>TTime</code>.
 * @returns   "TBool"
 *            True if the first <code>TTime</code> precedes the
 *            second. Otherwise false.
 */

inline TBool TTime::operator<(TTime aTime) const
	{return(iTime<aTime.iTime);}

/**
 *
 * Gets the 64 bit integer representation of a <code>TTime</code>.
 *
 * @returns   "TInt64&"
 *            The 64 bit integer representation of a
 *            <code>TTime</code>.
 */
inline const TInt64& TTime::Int64() const
	{return(iTime);}

// Class TLexMark8
inline TLexMark8::TLexMark8()
	: iPtr(NULL)
	{}
inline TLexMark8::TLexMark8(const TUint8 *aString) 
	: iPtr(aString)
	{}

// Class TLex8
inline TLex8::TLex8(const TUint8 *aString)
	{Assign(TPtrC8(aString));}
inline TLex8::TLex8(const TDesC8 &aDes)
	{Assign(aDes);}
inline TLex8& TLex8::operator=(const TUint8* aString)
	{Assign(TPtrC8(aString));return(*this);}
inline TLex8& TLex8::operator=(const TDesC8& aBuf)
	{Assign(aBuf);return(*this);}
inline TBool TLex8::Eos() const
	{return(iNext==iEnd);}
inline void TLex8::Mark()
	{Mark(iMark);}
inline void TLex8::Mark(TLexMark8& aMark) const
	{aMark.iPtr=iNext;}
inline void TLex8::UnGetToMark()
    {UnGetToMark(iMark);}
inline void TLex8::SkipAndMark(TInt aNumber)
    {SkipAndMark(aNumber,iMark);}
inline void TLex8::SkipSpaceAndMark()
    {SkipSpaceAndMark(iMark);}
inline TInt TLex8::TokenLength() const
	{return(iNext-iMark.iPtr);}
inline TInt TLex8::MarkedOffset() const
    {return(iMark.iPtr-iBuf);}
inline TInt TLex8::Val(TInt &aVal)
	{return(Val((TInt32&)aVal));}
inline TInt TLex8::Val(TUint &aVal,TRadix aRadix)
	{return(Val((TUint32&)aVal,aRadix));}
inline void TLex8::Assign(const TLex8& aLex)
	{new(this) TLex8(aLex);}

// Class TLexMark16
inline TLexMark16::TLexMark16()
	: iPtr(NULL)
	{}
inline TLexMark16::TLexMark16(const TUint16 *aString) 
	: iPtr(aString)
	{}

// Class TLex16
inline TLex16::TLex16(const TUint16 *aString)
	{Assign(TPtrC16(aString));}
inline TLex16::TLex16(const TDesC16 &aDes)
	{Assign(aDes);}
inline TLex16& TLex16::operator=(const TUint16* aString)
	{Assign(TPtrC16(aString));return(*this);}
inline TLex16& TLex16::operator=(const TDesC16& aBuf)
	{Assign(aBuf);return(*this);}
inline TBool TLex16::Eos() const
	{return(iNext==iEnd);}
inline void TLex16::Mark(TLexMark16& aMark) const
	{aMark.iPtr=iNext;}
inline void TLex16::Mark()
	{iMark.iPtr=iNext;}
inline void TLex16::UnGetToMark()
    {UnGetToMark(iMark);}
inline void TLex16::SkipAndMark(TInt aNumber)
    {SkipAndMark(aNumber,iMark);}
inline void TLex16::SkipSpaceAndMark()
    {SkipSpaceAndMark(iMark);}
inline TInt TLex16::TokenLength() const
	{return(iNext-iMark.iPtr);}
inline TInt TLex16::MarkedOffset() const
    {return(iMark.iPtr-iBuf);}
inline TInt TLex16::Val(TInt &aVal)
	{return(Val((TInt32&)aVal));}
inline TInt TLex16::Val(TUint &aVal,TRadix aRadix)
	{return(Val((TUint32&)aVal,aRadix));}
inline void TLex16::Assign(const TLex16& aLex)
	{new(this) TLex16(aLex);}

// Class TLocale

/**
 *
 * Returns the code which is used to select country-specific locale data.
 *
 * The country code is the code used as the international dialling
 * prefix. This code is also used to identify a country by the dialling
 * software.
 *
 * @returns   "TInt "
 *            The country code
 */

inline TInt TLocale::CountryCode() const
	{return(iCountryCode);}

/**
 *
 * Sets the value which is used to select country-specific locale data.
 *
 * This value can be retrieved by using
 * <code>TLocale::CountryCode()</code>. The country code is the code used
 * as the international dialling prefix. This code is also used to
 * identify a country by the dialling software.
 *
 * @param     "TInt aCode"
 *            The country code
 */

inline void TLocale::SetCountryCode(TInt aCode)
	{iCountryCode=aCode;}

/**
 *
 * Returns the locales universal time offset.
 *
 * @returns   "TTimeIntervalSeconds"
 *            Offset in seconds from universal time. A negative
 *            value indicates that the locale is to the east of zero
 *            degrees longitude.
 */

inline TTimeIntervalSeconds TLocale::UniversalTimeOffset() const
	{return(iUniversalTimeOffset);}

/**
 *
 * Sets the locales universal time offset.
 *
 * @param     "const TTimeIntervalSeconds& anOffset"
 *            Offset in seconds from universal time. A negative
 *            value indicates that the locale is to the east of zero
 *            degrees longitude.
 */

inline void TLocale::SetUniversalTimeOffset(const TTimeIntervalSeconds& anOffset)
	{iUniversalTimeOffset=anOffset;}

/**
 *
 * Returns the date format.
 *
 * @returns   "TDateFormat"
 *            The date format
 */

inline TDateFormat TLocale::DateFormat() const
	{return(iDateFormat);}

/**
 *
 * Sets the date format.
 *
 * @param     "TDateFormat aFormat"
 *            The date format to be used
 */

inline void TLocale::SetDateFormat(TDateFormat aFormat)
	{iDateFormat=aFormat;}

/**
 *
 * Returns the time format.
 *
 * This indicates whether the 12 or 24 hour clock format is used.
 *
 * @returns   "TTimeFormat"
 *            The time format
 */

inline TTimeFormat TLocale::TimeFormat() const
	{return(iTimeFormat);}

/**
 *
 * Sets the time format.
 *
 * This indicates whether the 12 or 24 hour clock format is to be used.
 *
 * @param     "TTimeFormat aFormat"
 *            The time format to be used
 */

inline void TLocale::SetTimeFormat(TTimeFormat aFormat)
	{iTimeFormat=aFormat;}

/**
 *
 * Returns the currency symbol position.
 *
 * The currency symbol can be located before or after the currency
 * value.Note:For negative currency values, this position may be reversed
 * using <code>SetNegativeCurrencySymbolOpposite()</code>.
 *
 * @returns   "TLocalePos"
 *            The currency symbol position.
 */

inline TLocalePos TLocale::CurrencySymbolPosition() const
	{return(iCurrencySymbolPosition);}

/**
 *
 * Sets the currency symbol position.
 *
 * The currency symbol can be located either before or after the currency
 * value.
 *
 * @param     "TLocalePos aPos"
 *            The currency symbol position.
 */

inline void TLocale::SetCurrencySymbolPosition(TLocalePos aPos)
	{iCurrencySymbolPosition=aPos;}

/**
 *
 * Returns whether or not a space is inserted between the currency symbol
 * and the currency value.
 *
 * Note:For negative currency values, the space can be removed using
 * <code>SetNegativeLoseSpace()</code>.
 *
 * @returns   "TBool"
 *            True, if a space is inserted; false, otherwise
 */

inline TBool TLocale::CurrencySpaceBetween() const
	{return(iCurrencySpaceBetween);}

/**
 *
 * Sets whether a space must be inserted between the currency symbol and
 * the currency amount.
 *
 * @param     "TBool aSpace"
 *            <code>ETrue</code> if a space must be inserted;
 *            <code>EFalse</code> otherwise
 */

inline void TLocale::SetCurrencySpaceBetween(TBool aSpace)
	{iCurrencySpaceBetween=aSpace;}

/**
 *
 * Returns the number of decimal places to which currency values are set.
 *
 * @returns   "TInt"
 *            The number of decimal places.
 */

inline TInt TLocale::CurrencyDecimalPlaces() const
	{return(iCurrencyDecimalPlaces);}

/**
 *
 * Sets the number of decimal places to which currency values should be
 * set.
 *
 * @param     "TInt aPlaces"
 *            The number of decimal places.
 */

inline void TLocale::SetCurrencyDecimalPlaces(TInt aPlaces)
	{iCurrencyDecimalPlaces=aPlaces;}

/**
 *
 * Returns whether negative currency values are enclosed in brackets
 * rather than being preceded by a minus sign.
 *
 * Note:From v6.1 onwards, use <code>NegativeCurrencyFormat()</code>
 * instead.
 *
 * @returns   "TBool"
 *            True if negative currency is enclosed in brackets and
 *            has no minus sign; false, if negative currency has a
 *            minus sign and is not enclosed in brackets.
 *
 * @deprecated in 6.1  
 */

inline TBool TLocale::CurrencyNegativeInBrackets() const				             
	{return((TBool)iNegativeCurrencyFormat);}							

/**
 *
 * Sets whether negative currency values are enclosed in brackets rather
 * than being preceded by a minus sign.
 *
 * Note:From v6.1 onwards, use <code>SetNegativeCurrencyFormat()</code>
 * instead.
 *
 * @param     "TBool aBool"
 *            <code>ETrue</code>, if a negative currency value must
 *            be enclosed in brackets without a minus sign;
 *            <code>EFalse</code>, if a negative currency value is
 *            preceded by a minus sign without any enclosing
 *            brackets.
 *
 * @deprecated in 6.1
 */

inline void TLocale::SetCurrencyNegativeInBrackets(TBool aBool)			
	{iNegativeCurrencyFormat=(aBool)?EInBrackets:ELeadingMinusSign;}	

/**
 *
 * Returns whether triads are allowed in currency values.
 *
 * Triads are groups of three digits separated by the thousands
 * separator.
 *
 * @returns   "TBool"
 *            True, if triads are allowed; false, otherwise
 */

inline TBool TLocale::CurrencyTriadsAllowed() const
	{return(iCurrencyTriadsAllowed);}

/**
 *
 * Sets whether triads are allowed in currency values.
 *
 * @param     "TBool aBool"
 *            <code>ETrue</code>, if triads are allowed;
 *            <code>EFalse</code>, if triads not allowed.
 */

inline void TLocale::SetCurrencyTriadsAllowed(TBool aBool)
	{iCurrencyTriadsAllowed=aBool;}

/**
 *
 * Returns the character used to separate groups of three digits to the
 * left of the decimal separator.
 *
 * Notes:A thousands separator character is only displayed in currency
 * values if currency triads are allowed.
 *
 * @returns   "TChar"
 *            The character used as the thousands separator
 */

inline TChar TLocale::ThousandsSeparator() const
	{return(iThousandsSeparator);}

/**
 *
 * Sets the character to be used to separate groups of three digits to
 * the left of the decimal separator.
 *
 * NotesA thousands separator character is only displayed in currency
 * values if currency triads are allowed.
 *
 * @param     "const TChar& aChar"
 *            The character to be used as the thousands separator.
 */

inline void TLocale::SetThousandsSeparator(const TChar& aChar)
	{iThousandsSeparator=aChar;}

/**
 *
 * Returns the character used to separate a whole number from its
 * fractional part.
 *
 * @returns   "TChar"
 *            The character used as the decimal separator.
 */

inline TChar TLocale::DecimalSeparator() const
	{return(iDecimalSeparator);}

/**
 *
 * Sets the character to be used to separate a whole number from its
 * fractional part.
 *
 * @param     "const TChar& aChar"
 *            The character to be used as the decimal separator.
 */

inline void TLocale::SetDecimalSeparator(const TChar& aChar)
	{iDecimalSeparator=aChar;}

/**
 *
 * Returns one of the four characters used to separate the day, month and
 * year components of the date.
 *
 * If the four separators are represented by S0, S1, S2 and S3 and the
 * three date components are represented by XX, YY and ZZ, then the
 * separators are located: S0 XX S1 YY S2 ZZ S3.
 *
 * @param     "TInt aIndex"
 *            An index indicating which of the four separators is
 *            being accessed. This must be a value between zero and
 *            three inclusive.
 * @returns   "TChar"
 *            A date separator character as determined by the value
 *            of <code>aIndex</code>.
 */

inline TChar TLocale::DateSeparator(TInt aIndex) const
	{return(iDateSeparator[aIndex]);}

/**
 *
 * Sets one of the four characters used to separate the day, month and
 * year components of the date.
 *
 * If the four separators are represented by S0, S1, S2 and S3 and the
 * three date components are represented by XX, YY and ZZ, then the
 * separators are located: S0 XX S1 YY S2 ZZ S3.
 *
 * @param     "const TChar& aChar"
 *            A date separator character to be used.
 * @param     "TInt aIndex"
 *            An index indicating which of the four separators is
 *            being accessed. This must be a value between zero and
 *            three inclusive.
 */

inline void TLocale::SetDateSeparator(const TChar& aChar,TInt aIndex)
	{__ASSERT_DEBUG(aIndex>=0 && aIndex<KMaxDateSeparators,User::Invariant());
	iDateSeparator[aIndex]=aChar;}

/**
 *
 * Returns one of the four characters used to separate the hour, second
 * and minute components of the time.
 *
 * If the four separators are represented by S0, S1, S2 and S3 and the
 * three time components are represented by XX, YY and ZZ, then the
 * separators are located: S0 XX S1 YY S2 ZZ S3.
 *
 * @param     "TInt aIndex"
 *            An index indicating which of the four separators is
 *            being accessed. This must be a value between zero and
 *            three inclusive.
 * @returns   "TChar"
 *            A time separator character as determined by the value
 *            of <code>aIndex</code>.
 */

inline TChar TLocale::TimeSeparator(TInt aIndex) const
	{return(iTimeSeparator[aIndex]);}

/**
 *
 * Sets one of the four characters used to separate the hour, minute and
 * second components of the date.
 *
 * If the four separators are represented by S0, S1, S2 and S3 and the
 * three time components are represented by XX, YY and ZZ, then the
 * separators are located: S0 XX S1 YY S2 ZZ S3.
 *
 * @param     "const TChar& aChar"
 *            A time separator character to be used.
 * @param     "TInt aIndex"
 *            An index indicating which of the four separators is
 *            being accessed. This must be a value between zero and
 *            three inclusive.
 */

inline void TLocale::SetTimeSeparator(const TChar& aChar,TInt aIndex)
	{__ASSERT_DEBUG(aIndex>=0 && aIndex<KMaxTimeSeparators,User::Invariant());
	iTimeSeparator[aIndex]=aChar;}

/**
 *
 * Returns the am/pm text position.
 *
 * The am/pm text is located before or after the time value.
 *
 * @returns   "TLocalePos"
 *            The am/pm text position
 */

inline TLocalePos TLocale::AmPmSymbolPosition() const
	{return(iAmPmSymbolPosition);}

/**
 *
 * Sets the am/pm text position.
 *
 * The am/pm text can be located either before or after the time value.
 *
 * @param     "TLocalePos aPos"
 *            The am/pm text position
 */

inline void TLocale::SetAmPmSymbolPosition(TLocalePos aPos)
	{iAmPmSymbolPosition=aPos;}

/**
 *
 * Determines whether or not a space is inserted between the time and
 * preceding or trailing am/pm text.
 *
 * @returns   "TBool"
 *            True, if a space is inserted between the time and
 *            am/pm text; false, otherwise
 */

inline TBool TLocale::AmPmSpaceBetween() const
	{return(iAmPmSpaceBetween);}

/**
 *
 * Sets whether a space must be inserted between the time and preceding
 * or trailing am/pm text.
 *
 * @param     "TBool aSpace"
 *            <code>ETrue</code> if a space must be inserted between
 *            the time and am/pm text;<code>EFalse</code> otherwise
 */

inline void TLocale::SetAmPmSpaceBetween(TBool aSpace)
	{iAmPmSpaceBetween=aSpace;}

/**
 *
 * Returns the daylight saving zones in which daylight saving is in
 * effect.
 *
 * The function returns a bit mask in which the three least significant
 * bits are defined. These bits represent Northern (non-European
 * countries in the northern hemisphere), Southern (southern hemisphere),
 * and European.NotesIf daylight saving is in effect, one hour is added
 * to the time. Use <code>TLocale::QueryHomeHasDaylightSavingOn()</code>
 * rather than this function to get whether daylight saving is in effect
 * for the home city. This is because the daylight saving setting for the
 * home city may differ from that of the zone in which home is located.
 *
 * @returns   "TUint"
 *            A bit mask indicating which of the three daylight
 *            saving zones should be adjusted for daylight saving.
 *            For more information, see the
 *            <code>TDaylightSavingZone</code> enumeration.
 */

inline TUint TLocale::DaylightSaving() const
	{return(iDaylightSaving);} 

/**
 *
 * Sets the daylight saving zones in which daylight saving is in effect.
 *
 * The function uses a bit mask in which the three least significant bits
 * are defined plus a fourth bit for home. These bits represent European,
 * Northern (non-European countries in the northern hemisphere) and
 * Southern (southern hemisphere).NotesThe daylight saving setting for
 * the home city normally corresponds to the setting for the zone in
 * which home is located. However they may differ. Assuming home is
 * located in Europe,to set home and unset Europe, use
 * <code>TLocale::SetDaylightSaving(EDstHome)</code>. In this case, the
 * home bit overrides the Europe bit.to unset home and set Europe, home
 * must be removed from the Europe daylight saving zone. First set both
 * home and Europe by using
 * <code>TLocale::SetDaylightSaving(EDstEurope)</code>. Then, remove home
 * from Europe by using
 * <code>TLocale::SetHomeDaylightSavingZone(EDstNone)</code>. Home
 * daylight saving is now unset while Europe remains set.
 *
 * @param     "TUint aMask"
 *            A bit mask indicating which of four daylight saving
 *            zones should be adjusted for daylight saving. To unset
 *            all daylight saving zones, specify
 *            <code>EDstNone</code>. For more information, see the
 *            <code>TDaylightSavingZone</code> enumeration.
 */

inline void TLocale::SetDaylightSaving(TUint aDaylightSaving)
	{iDaylightSaving=aDaylightSaving;} 

/**
 *
 * Determines whether or not daylight saving is set for the home city.
 *
 * @returns   "TBool"
 *            True, if home daylight saving is set; false,
 *            otherwise.
 */

inline TBool TLocale::QueryHomeHasDaylightSavingOn() const
	{return((iHomeDaylightSavingZone|EDstHome) & iDaylightSaving);}

/**
 *
 * Returns the daylight saving zone in which the home city is located.
 *
 * @returns   "TDaylightSavingZone"
 *            European, non European in the northern hemisphere,
 *            southern hemisphere, or none.
 */

inline TDaylightSavingZone TLocale::HomeDaylightSavingZone() const
	{return(iHomeDaylightSavingZone);}

/**
 *
 * Sets the daylight saving zone in which the home city is located.
 *
 * @param     "TDaylightSavingZone aZone"
 *            European, non European in the Northern hemisphere,
 *            Southern hemisphere, or none.
 */

inline void TLocale::SetHomeDaylightSavingZone(TDaylightSavingZone aZone)
	{iHomeDaylightSavingZone=aZone;}

/**
 *
 * Returns a bit mask representing the days of the week which are
 * considered as working days.
 *
 * @returns   "TUint"
 *            A bit mask of seven bits indicating (by being set)
 *            which days are to be considered workdays. The least
 *            significant bit corresponds to Monday, the next bit to
 *            Tuesday and so on.
 */

inline TUint TLocale::WorkDays() const
	{return(iWorkDays);}

/**
 *
 * Sets the days of the week which are considered as working days.
 *
 * @param     "TUint aMask"
 *            A mask of seven bits indicating (by being set) which
 *            days are to be considered workdays. The least
 *            significant bit corresponds to Monday, the next bit is
 *            Tuesday and so on.
 */

inline void TLocale::SetWorkDays(TUint aMask)
	{iWorkDays=aMask;}

/**
 *
 * Returns the day which is considered the first day of the week.
 *
 * @returns   "TDay"
 *            The first day of the week.
 */

inline TDay TLocale::StartOfWeek() const
	{return(iStartOfWeek);}

/**
 *
 * Sets the day which is considered to be the first day of the week.
 *
 * @param     "TDay aDay"
 *            The first day of the week.
 */

inline void TLocale::SetStartOfWeek(TDay aDay)
	{iStartOfWeek=aDay;}

/**
 *
 * Returns the clock display format.
 *
 * @returns   "TClockFormat"
 *            The clock display format.
 */

inline TClockFormat TLocale::ClockFormat() const
	{return(iClockFormat);}

/**
 *
 * Sets the clock display format.
 *
 * @param     "TClockFormat aFormat"
 *            The clock display format.
 */

inline void TLocale::SetClockFormat(TClockFormat aFormat)
	{iClockFormat=aFormat;}

/**
 *
 * Returns the general units of measurement.
 *
 * This function should be used when both short and long distances use
 * the same units of measurement.
 *
 * @returns   "TUnitsFormat"
 *            General units of measurement.
 */

inline TUnitsFormat TLocale::UnitsGeneral() const
	{return(iUnitsGeneral);}

/**
 *
 * Sets the general units of measurement.
 *
 * This function should be used when both short and long distances use
 * the same units of measurement.
 *
 * @param     "TUnitsFormat aFormat"
 *            General units of measurement.
 */

inline void TLocale::SetUnitsGeneral(TUnitsFormat aFormat)
	{iUnitsGeneral=aFormat;}

/**
 *
 * Returns the units of measurement for short distances.
 *
 * Short distances are those which would normally be represented by
 * either meters and centimetres or feet and inches.
 *
 * @returns   "TUnitsFormat"
 *            Units of measurement for short distances.
 */

inline TUnitsFormat TLocale::UnitsDistanceShort() const
	{return(iUnitsDistanceShort);}

/**
 *
 * Sets the units of measurement for short distances.
 *
 * Short distances are those which would normally be represented by
 * either meters and centimetres or feet and inches.
 *
 * @param     "TUnitsFormat aFormat"
 *            Units of measurement for short distances.
 */

inline void TLocale::SetUnitsDistanceShort(TUnitsFormat aFormat)
	{iUnitsDistanceShort=aFormat;}

/**
 *
 * Returns the units of measurement for long distances.
 *
 * Long distances are those which would normally be represented by either
 * miles or kilometres.
 *
 * @returns   "TUnitsFormat"
 *            Units of measurement for long distances.
 */

inline TUnitsFormat TLocale::UnitsDistanceLong() const
	{return(iUnitsDistanceLong);}

/**
 *
 * Sets the units of measurement for long distances.
 *
 * Long distances are those which would normally be represented by either
 * miles or kilometres.
 *
 * @param     "TUnitsFormat aFormat"
 *            Units of measurement for long distances.
 */

inline void TLocale::SetUnitsDistanceLong(TUnitsFormat aFormat)
	{iUnitsDistanceLong=aFormat;}

/**
 *
 * Gets the negative currency format.
 *
 * @since     6.1
 * @returns   "TNegativeCurrencyFormat"
 *            How negative currency values are formatted.
 */

inline TLocale::TNegativeCurrencyFormat TLocale::NegativeCurrencyFormat() const
	{return(iNegativeCurrencyFormat);}

/**
 *
 * Sets the negative currency format.
 *
 * @since     6.1
 * @param     "TNegativeCurrencyFormat aNegativeCurrencyFormat"
 *            How negative currency values are formatted.
 */

inline void TLocale::SetNegativeCurrencyFormat(TLocale::TNegativeCurrencyFormat aNegativeCurrencyFormat)
	{iNegativeCurrencyFormat = aNegativeCurrencyFormat;}

/**
 *
 * Returns whether negative currency values lose the space between the
 * currency symbol and the value.
 *
 * @since     6.1
 * @returns   "TBool"
 *            <code>ETrue</code> if negative currency values lose
 *            the space between the value and the symbol.
 *            <code>EFalse</code> if not.
 */

inline TBool TLocale::NegativeLoseSpace() const
	{ 
	if((iExtraNegativeCurrencyFormatFlags|EFlagNegativeLoseSpace)==iExtraNegativeCurrencyFormatFlags)
		return ETrue;
	else
		return EFalse;
	}

/**
 *
 * Sets whether negative currency values lose the space between the
 * currency symbol and the value.
 *
 * @since     6.1
 * @param     "TBool aBool"
 *            <code>ETrue</code> to set a flag which indicates that
 *            negative currency values should lose the space between
 *            the value and the symbol. <code>EFalse</code> to unset
 *            it.
 */

inline void TLocale::SetNegativeLoseSpace(TBool aBool)
	{
	if(aBool)
		iExtraNegativeCurrencyFormatFlags |= EFlagNegativeLoseSpace;
	else
		iExtraNegativeCurrencyFormatFlags &= ~EFlagNegativeLoseSpace;
	}

/**
 *
 * Returns whether in negative currency values, the position of the
 * currency symbol is set to be the opposite of the position used for
 * non-negative values (before or after the value — as set by
 * <code>SetCurrencySymbolPosition()</code>).
 *
 * @since     6.1
 * @returns   "TBool"
 *            <code>ETrue</code> if the currency symbol position for
 *            negative currency values is the opposite of the
 *            position set by
 *            <code>SetCurrencySymbolPosition()</code>.
 *            <code>EFalse</code> if not.
 */

inline TBool TLocale::NegativeCurrencySymbolOpposite() const
	{
	if((iExtraNegativeCurrencyFormatFlags|EFlagNegativeCurrencySymbolOpposite)==iExtraNegativeCurrencyFormatFlags)
		return ETrue;
	else
		return EFalse;
	}

/**
 *
 * Sets whether the position of the currency symbol for negative currency
 * values should be the opposite of the position used for non-negative
 * values (before or after the value — as set by
 * <code>SetCurrencySymbolPosition()</code>).
 *
 * @since     6.1
 * @param     "TBool aBool"
 *            <code>ETrue</code> to set the position of the currency
 *            symbol in negative currency values to be the opposite
 *            of the position as set using
 *            <code>SetCurrencySymbolPosition()</code>.
 *            <code>EFalse</code> to leave the position unchanged.
 */

inline void TLocale::SetNegativeCurrencySymbolOpposite(TBool aBool)
	{
	if (aBool)
		iExtraNegativeCurrencyFormatFlags |= EFlagNegativeCurrencySymbolOpposite;
	else
		iExtraNegativeCurrencyFormatFlags &= ~EFlagNegativeCurrencySymbolOpposite;
	}

inline TLanguage TLocale::LanguageDowngrade(TInt aIndex) const
	{
	__ASSERT_DEBUG(0 <= aIndex && aIndex < 3, User::Invariant());
	return static_cast<TLanguage>(iLanguageDowngrade[aIndex]);
	}

inline void TLocale::SetLanguageDowngrade(TInt aIndex, TLanguage aLanguage)
	{
	__ASSERT_DEBUG(0 <= aIndex && aIndex < 3, User::Invariant());
	iLanguageDowngrade[aIndex] = static_cast<TUint16>(aLanguage);
	}
/**
 *
 * Returns the number mode stored in the locale.
 *
 * @since     7.0s
 * @returns   "TDigitType"
 *          
 */
inline TDigitType TLocale::DigitType() const
	{ return iDigitType; }
/**
 *
 * Set the Number mode in the locale to aDigitType. 
 *
 * @since    7.0s
 * @param   "TDigitType aDigitType"
 *           
 */
inline void TLocale::SetDigitType(TDigitType aDigitType)
	{ iDigitType=aDigitType; }

/**
Sets the device time state to aState

@since 7.0s
@param "TDeviceTimeState aState"
*/
inline void TLocale::SetDeviceTime(TDeviceTimeState aState)
	{
	iDeviceTimeState=aState;
	}

/**
Returns the device time state

@since 7.0s
@returns "TDeviceTimeState"
*/
inline TLocale::TDeviceTimeState TLocale::DeviceTime() const
	{
	return iDeviceTimeState;
	}

// Class TPoint
inline TPoint::TPoint()
	: iX(0),iY(0)
	{}
inline TPoint::TPoint(TInt aX,TInt aY)
	: iX(aX),iY(aY)
	{}

// Class TSize
inline TSize::TSize()
	: iWidth(0),iHeight(0)
	{}
inline TSize::TSize(TInt aWidth,TInt aHeight)
	: iWidth(aWidth),iHeight(aHeight)
	{}

// Class TRequestStatus
inline TRequestStatus::TRequestStatus()
	{}
inline TRequestStatus::TRequestStatus(TInt aVal)
	: iStatus(aVal)
	{}
inline TInt TRequestStatus::operator=(TInt aVal)
	{return(iStatus=aVal);}
inline TInt TRequestStatus::operator==(TInt aVal) const
	{return(iStatus==aVal);}
inline TInt TRequestStatus::operator!=(TInt aVal) const
	{return(iStatus!=aVal);}
inline TInt TRequestStatus::operator>=(TInt aVal) const
	{return(iStatus>=aVal);}
inline TInt TRequestStatus::operator<=(TInt aVal) const
	{return(iStatus<=aVal);}
inline TInt TRequestStatus::operator>(TInt aVal) const
	{return(iStatus>aVal);}
inline TInt TRequestStatus::operator<(TInt aVal) const
	{return(iStatus<aVal);}
inline TInt TRequestStatus::Int() const
	{return(iStatus);}

// Class TFindHandleBase
inline TInt TFindHandleBase::Handle() const
	{return(iFindHandle);}

// Class RHandleBase
inline RHandleBase::RHandleBase()
	: iHandle(0)
	{}
inline RHandleBase::RHandleBase(TInt aHandle)
	: iHandle(aHandle)
	{}
inline void RHandleBase::SetHandle(TInt aHandle)
	{iHandle=aHandle;}
inline TInt RHandleBase::Handle() const
	{return(iHandle);}

// Class TFindSemaphore
inline TFindSemaphore::TFindSemaphore()
    : TFindHandleBase()
    {}
inline TFindSemaphore::TFindSemaphore(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindMutex
inline TFindMutex::TFindMutex()
    : TFindHandleBase()
    {}
inline TFindMutex::TFindMutex(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindChunk
inline TFindChunk::TFindChunk()
    : TFindHandleBase()
    {}
inline TFindChunk::TFindChunk(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindThread
inline TFindThread::TFindThread()
    : TFindHandleBase()
    {}
inline TFindThread::TFindThread(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindProcess
inline TFindProcess::TFindProcess()
    : TFindHandleBase()
    {}
inline TFindProcess::TFindProcess(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindLogicalDevice
inline TFindLogicalDevice::TFindLogicalDevice()
    : TFindHandleBase()
    {}
inline TFindLogicalDevice::TFindLogicalDevice(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindPhysicalDevice
inline TFindPhysicalDevice::TFindPhysicalDevice()
    : TFindHandleBase()
    {}
inline TFindPhysicalDevice::TFindPhysicalDevice(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindLogicalChannel
inline TFindLogicalChannel::TFindLogicalChannel()
    : TFindHandleBase()
    {}
inline TFindLogicalChannel::TFindLogicalChannel(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindServer
inline TFindServer::TFindServer()
    : TFindHandleBase()
    {}
inline TFindServer::TFindServer(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindLibrary
inline TFindLibrary::TFindLibrary()
    : TFindHandleBase()
    {}
inline TFindLibrary::TFindLibrary(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class RDevice
inline TInt RDevice::Open(const TFindLogicalDevice& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class RSemaphore
inline TInt RSemaphore::Open(const TFindSemaphore& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class RCriticalSection
inline TBool RCriticalSection::IsBlocked() const
	{return(iBlocked!=1);}

// Class RMutex
inline TInt RMutex::Open(const TFindMutex& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class RChunk
inline TInt RChunk::Open(const TFindChunk& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}
inline TBool RChunk::IsReadable() const
	{return (Attributes()&RHandleBase::EDirectReadAccess); }
inline TBool RChunk::IsWritable() const
	{return (Attributes()&RHandleBase::EDirectWriteAccess); }

// Class TThreadId
inline TThreadId::TThreadId()
	{}
inline TThreadId::TThreadId(TUint aId)
	: iId(aId)
	{}
inline TThreadId::operator TUint() const
	{ return iId; }
inline TInt TThreadId::operator==(TThreadId aId) const
	{return iId==aId.iId;}
inline TInt TThreadId::operator!=(TThreadId aId) const
	{return iId!=aId.iId;}

// Class RThread
inline RThread::RThread()
	: RHandleBase(KCurrentThreadHandle)
	{}
inline TInt RThread::Open(const TFindThread& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class TProcessId
inline TProcessId::TProcessId()
	{}
inline TProcessId::TProcessId(TUint aId)
	: iId(aId)
	{}
inline TProcessId::operator TUint() const
	{ return iId; }
inline TInt TProcessId::operator==(TProcessId aId) const
	{return iId==aId.iId;}
inline TInt TProcessId::operator!=(TProcessId aId) const
	{return iId!=aId.iId;}

// Class RProcess
inline RProcess::RProcess()
	: RHandleBase(KCurrentProcessHandle)
	{}
inline RProcess::RProcess(TInt aHandle)
	: RHandleBase(aHandle)
	{}
inline TInt RProcess::Open(const TFindProcess& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

#ifndef __HIDE_IPC_V1__

// Class RMessagePtr
inline RMessagePtr::RMessagePtr()
	: iHandle(0)
	{}
inline RMessagePtr::RMessagePtr(const RMessage& aMessage)
	: iHandle(aMessage.iHandle)
	{}
inline TBool RMessagePtr::IsNull() const
	{return iHandle==0;}
inline TBool operator==(RMessagePtr aLeft,RMessagePtr aRight)
	{return aLeft.iHandle==aRight.iHandle;}
inline TBool operator!=(RMessagePtr aLeft,RMessagePtr aRight)
	{return !(aLeft==aRight);}

// Class RMessage
inline TInt RMessage::Function() const
	{return(iFunction);}
inline const RThread &RMessage::Client() const
	{return(iClient);}
inline TInt RMessage::Int0() const
	{return(iArgs[0]);}
inline TInt RMessage::Int1() const
	{return(iArgs[1]);}
inline TInt RMessage::Int2() const
	{return(iArgs[2]);}
inline TInt RMessage::Int3() const
	{return(iArgs[3]);}
inline const TAny *RMessage::Ptr0() const
	{return((const TAny *)iArgs[0]);}
inline const TAny *RMessage::Ptr1() const
	{return((const TAny *)iArgs[1]);}
inline const TAny *RMessage::Ptr2() const
	{return((const TAny *)iArgs[2]);}
inline const TAny *RMessage::Ptr3() const
	{return((const TAny *)iArgs[3]);}
inline const RMessagePtr RMessage::MessagePtr() const
	{return(RMessagePtr(*this));}

// Class RServer
inline const RMessage &RServer::Message() const
	{return iMessage;}

#endif // __HIDE_IPC_V1__

// Class RSessionBase
#ifndef __HIDE_IPC_V1__
inline TInt RSessionBase::Share(TAttachMode aAttachMode)
/**
@deprecated Superceded by RSessionBase::ShareAuto() in the IPC V2 framework
*/
	{return DoShare(aAttachMode);}
inline TInt RSessionBase::Send(TInt aFunction,TAny* aPtr) const
/**
@deprecated Superceded by RSessionBase::Send(TInt aFunction,const TIpcArgs& aArgs) in the IPC V2 framework
*/
	{return DoSend(aFunction,aPtr);}
inline void RSessionBase::SendReceive(TInt aFunction,TAny* aPtr,TRequestStatus& aStatus) const
/**
@deprecated Superceded by RSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs,TRequestStatus& aStatus) in the IPC V2 framework
*/
	{DoSendReceive(aFunction,aPtr,aStatus);}
inline TInt RSessionBase::SendReceive(TInt aFunction,TAny* aPtr) const
/**
@deprecated Superceded by RSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs) in the IPC V2 framework
*/
	{return DoSendReceive(aFunction,aPtr);}
#endif // __HIDE_IPC_V1__
inline TInt RSessionBase::ShareAuto()
/**
After calling this function the session object may be used by threads other than than
the one that created it.

@return	KErrNone if the session is successfully shared
		KErrNoMmemory if out of memory

@panic	KERN-SVR 23 Unsharable session
*/
	{return DoShare(EAutoAttach);}
inline TInt RSessionBase::CreateSession(const TDesC& aServer,const TVersion& aVersion)
/**
Create a session to the specified server.

@param aServer  the name of the server with which this session will connect
@param aVersion the version of the server against which this client was compiled

@return		KErrNone if session created successfully
			KErrNotFound if no server with the specified name
*/
	{return CreateSession(aServer,aVersion,-1);}
inline TInt RSessionBase::Send(TInt aFunction,const TIpcArgs& aArgs) const
/**
Issue a blind request to the server with the specified function number and arguments.
The server will not issue a response to the client.

@param aFunction the function number for the request
@param aArgs up to 4 arguments and their types

@return KErrNone if successful send
		KErrServerTerminated if server no longer present
		KErrServerBusy if no message slots available
		KErrNoMemory if out of memory

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSend(aFunction,(TAny*)&aArgs);}
inline void RSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs,TRequestStatus& aStatus) const
/**
Issue an asynchronous request to the server with the specified function number
and arguments. Request completion will be signaled in aStatus.

@param aFunction the function number for the request
@param aArgs up to 4 arguments and their types
@param aStatus the request status for signalling request completion

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{DoSendReceive(aFunction,(TAny*)&aArgs,aStatus);}
inline TInt RSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs) const
/**
Issue a synchronous request to the server with the specified function number
and arguments

@param aFunction the function number for the request
@param aArgs up to 4 arguments and their types

@return KErrNone if successful send
		KErrServerTerminated if server no longer present
		KErrServerBusy if no message slots available
		KErrNoMemory if out of memory

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSendReceive(aFunction,(TAny*)&aArgs);}
inline TInt RSessionBase::Send(TInt aFunction) const
/**
Issue a blind request to the server with the specified function number,
but no arguments. The server will not issue a response to the client.

@param aFunction the function number for the request

@return KErrNone if successful send
		KErrServerTerminated if server no longer present
		KErrServerBusy if no message slots available
		KErrNoMemory if out of memory

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSend(aFunction,NULL);}
inline void RSessionBase::SendReceive(TInt aFunction,TRequestStatus& aStatus) const
/**
Issue an asynchronous request to the server with the specified function number
but no arguments. Request completion will be signaled in aStatus

@param aFunction the function number for the request
@param aArgs up to 4 arguments and their types
@param aStatus the request status for signalling request completion

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{DoSendReceive(aFunction,NULL,aStatus);}
inline TInt RSessionBase::SendReceive(TInt aFunction) const
/**
Issue a synchronous request to the server with the specified function number
but no arguments.

@param aFunction the function number for the request

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSendReceive(aFunction,NULL);}

// Class RSubSessionBase
inline RSubSessionBase::RSubSessionBase()
	: iSubSessionHandle(0)
/**
Construct a subsession object.
*/
	{}
inline TInt RSubSessionBase::SubSessionHandle() const
/**
Return the handle for this subsession.

@return the handle for this subsession
*/
	{return iSubSessionHandle;}
inline RSessionBase& RSubSessionBase::Session()
/**
Return the session object of which this is a subsession.

@return the session object of which this is a subsession.
*/
	{return iSession;}
#ifndef __HIDE_IPC_V1__
inline TInt RSubSessionBase::CreateSubSession(RSessionBase& aSession,TInt aFunction,const TAny* aPtr)
/**
@deprecated Superceded by CreateSubSession(RSessionBase& aSession,TInt aFunction,const TIpcArgs& aArgs) in the IPC V2 framework
*/
	{ return DoCreateSubSession(aSession,aFunction,aPtr); }
#endif
inline TInt RSubSessionBase::CreateSubSession(RSessionBase& aSession,TInt aFunction,const TIpcArgs& aArgs)
/**
Create a sub session on a pre-existing session

@param aSession the session upon which the subsession should be based
@param aFunction the function number of the server function that issues subsessions
@param aArgs up to 3 arguments and their types, the 4th is used to return the subsession handle

@return		KErrNone if subsession created successfully
			Server-specific error code if subsession could not be created

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{ return DoCreateSubSession(aSession,aFunction,(TAny*)&aArgs); }
inline TInt RSubSessionBase::CreateSubSession(RSessionBase& aSession,TInt aFunction)
/**
Create a sub session on a pre-existing session using no arguments

@param aSession the session upon which the subsession should be based
@param aFunction the function number of the server function that issues subsessions

@return		KErrNone if subsession created successfully
			Server-specific error code if subsession could not be created

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{ return DoCreateSubSession(aSession,aFunction,NULL); }
#ifndef __HIDE_IPC_V1__
inline TInt RSubSessionBase::Send(TInt aFunction,const TAny* aPtr) const
/**
@deprecated Superceded by RSubSessionBase::Send(TInt aFunction,const TIpcArgs& aArgs) in the IPC V2 framework
*/
	{return DoSend(aFunction,aPtr);}
inline void RSubSessionBase::SendReceive(TInt aFunction,const TAny* aPtr,TRequestStatus& aStatus) const
/**
@deprecated Superceded by RSubSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs,TRequestStatus& aStatus) in the IPC V2 framework
*/
	{DoSendReceive(aFunction,aPtr,aStatus);}
inline TInt RSubSessionBase::SendReceive(TInt aFunction,const TAny* aPtr) const
/**
@deprecated Superceded by RSubSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs) in the IPC V2 framework
*/
	{return DoSendReceive(aFunction,aPtr);}
#endif
inline TInt RSubSessionBase::Send(TInt aFunction,const TIpcArgs& aArgs) const
/**
Issue a blind request to the server on this subsession with the specified
function number and arguments. The server will not issue a response to the client.

@param aFunction the function number for the request
@param aArgs up to 3 arguments and their types

@return KErrNone if successful send
		KErrServerTerminated if server no longer present
		KErrServerBusy if no message slots available
		KErrNoMemory if out of memory

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSend(aFunction,(TAny*)&aArgs);}
inline void RSubSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs,TRequestStatus& aStatus) const
/**
Issue an asynchronous request to the server on this subsession
with the specified function number and arguments. Request
completion will be signaled in aStatus.

@param aFunction the function number for the request
@param aArgs up to 3 arguments and their types
@param aStatus the request status for signalling request completion

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{DoSendReceive(aFunction,(TAny*)&aArgs,aStatus);}
inline TInt RSubSessionBase::SendReceive(TInt aFunction,const TIpcArgs& aArgs) const
/**
Issue a synchronous request to the server on this subsession
with the specified function number and arguments

@param aFunction the function number for the request
@param aArgs up to 3 arguments and their types

@return KErrNone if successful send
		KErrServerTerminated if server no longer present
		KErrServerBusy if no message slots available
		KErrNoMemory if out of memory

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSendReceive(aFunction,(TAny*)&aArgs);}
inline TInt RSubSessionBase::Send(TInt aFunction) const
/**
Issue a blind request to the server on this subsession
with the specified function number, but no arguments.
The server will not issue a response to the client.

@param aFunction the function number for the request

@return KErrNone if successful send
		KErrServerTerminated if server no longer present
		KErrServerBusy if no message slots available
		KErrNoMemory if out of memory

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSend(aFunction,NULL);}
inline void RSubSessionBase::SendReceive(TInt aFunction,TRequestStatus& aStatus) const
/**
Issue an asynchronous request to the server on this subsession
with the specified function number but no arguments.
Request completion will be signaled in aStatus

@param aFunction the function number for the request
@param aArgs up to 4 arguments and their types
@param aStatus the request status for signalling request completion

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{ DoSendReceive(aFunction,NULL,aStatus);}
inline TInt RSubSessionBase::SendReceive(TInt aFunction) const
/**
Issue a synchronous request to the server on this subsession
with the specified function number but no arguments.

@param aFunction the function number for the request

@panic  USER 72 if function number is negative
@panic	USER 135 if unable to attach to shared session
*/
	{return DoSendReceive(aFunction,NULL);}

// Class RMessagePtr2
inline RMessagePtr2::RMessagePtr2()
	: iHandle(0)
/**
Construct an RMessagePtr2 object
*/
	{}
inline TBool RMessagePtr2::IsNull() const
/**
Report if the handle is null

@return	ETrue if handle is null
		EFalse if handle is no null
*/
	{return iHandle==0;}
inline TInt RMessagePtr2::Handle() const
/*
Return the handle

@return the handle
*/
	{return iHandle;}
inline TBool RMessagePtr2::ClientDataCaging() const
/*
Report if the client process uses data caging

@return ETrue if the client process uses data caging
		EFalse if the clinet process does not use data caging
*/
//	{return ClientProcessFlags() & KProcessFlagUseDataCaging;}
	{return ClientProcessFlags();}
inline TBool operator==(RMessagePtr2 aLeft,RMessagePtr2 aRight)
/*
Check if two RMessagePtr objects refer to the same message

@return ETrue if the RMessagePtr2 objects refer to the same message
		EFalse if the RMessagePtr2 objects do not refer to the same message
*/
	{return aLeft.Handle()==aRight.Handle();}
inline TBool operator!=(RMessagePtr2 aLeft,RMessagePtr2 aRight)
/*
Check if two RMessagePtr objects refer to the same message

@return ETrue if the RMessagePtr2 objects do not refer to the same message
		EFalse if the RMessagePtr2 objects refer to the same message
*/
	{return aLeft.Handle()!=aRight.Handle();}

// Class RMessage2
inline RMessage2::RMessage2()
/*
Construct an RMessage2 object
*/
	{}
inline TInt RMessage2::Function() const
/*
Return the message's function number

@return the message's function number
*/
	{return(iFunction);}
inline TInt RMessage2::Int0() const
/*
Return message argument 0 as a TInt

@return message argument 0 as a TInt
*/
	{return(iArgs[0]);}
inline TInt RMessage2::Int1() const
/*
Return message argument 1 as a TInt

@return message argument 1 as a TInt
*/
	{return(iArgs[1]);}
inline TInt RMessage2::Int2() const
/*
Return message argument 2 as a TInt

@return message argument 2 as a TInt
*/
	{return(iArgs[2]);}
inline TInt RMessage2::Int3() const
/*
Return message argument 3 as a TInt

@return message argument 3 as a TInt
*/
	{return(iArgs[3]);}
inline const TAny *RMessage2::Ptr0() const
/*
Return message argument 0 as a untyped pointer

@return message argument 0 as a untyped pointer
*/
	{return((const TAny *)iArgs[0]);}
inline const TAny *RMessage2::Ptr1() const
/*
Return message argument 1 as a untyped pointer

@return message argument 1 as a untyped pointer
*/
	{return((const TAny *)iArgs[1]);}
inline const TAny *RMessage2::Ptr2() const
/*
Return message argument 2 as a untyped pointer

@return message argument 2 as a untyped pointer
*/
	{return((const TAny *)iArgs[2]);}
inline const TAny *RMessage2::Ptr3() const
/*
Return message argument 3 as a untyped pointer

@return message argument 3 as a untyped pointer
*/
	{return((const TAny *)iArgs[3]);}
inline CSession2* RMessage2::Session() const
/*
Return the session by which this message arrived

@return the session by which this message arrived
*/
	{return (CSession2*)iSessionPtr; }

// Class RRefBase
inline RRefBase::RRefBase()
	: iPtr(NULL)
	{}
inline RRefBase::RRefBase(const RRefBase &aRef)
	{Copy(aRef);}

// Class RRef
template <class T>
inline RRef<T>::RRef()
	{}
template <class T>
inline RRef<T>::RRef(const RRef<T> &anObject)
	{Copy(anObject);}
template <class T>
inline void RRef<T>::operator=(const RRef<T> &anObject)
	{Copy(anObject);}
template <class T>
inline T *RRef<T>::operator->()
	{return((T *)iPtr);}
template <class T>
inline RRef<T>::operator T*()
	{return((T *)iPtr);}
template <class T>
void RRef<T>::Alloc(const T &anObject)
	{DoAlloc(&anObject,sizeof(T));}
template <class T>
void RRef<T>::Alloc(const T &anObject,TInt aSize)
	{DoAlloc(&anObject,aSize);}
template <class T>
void RRef<T>::AllocL(const T &anObject)
	{DoAllocL(&anObject,sizeof(T));}
template <class T>
void RRef<T>::AllocL(const T &anObject,TInt aSize)
	{DoAllocL(&anObject,aSize);}

// Class TRegion
inline TBool TRegion::CheckError() const
	{return(iError);}
inline TInt TRegion::Count() const
	{return(iCount);}
inline const TRect *TRegion::RectangleList() const
	{return(((TRegion *)this)->RectangleListW());}
inline TRegion::TRegion()
	{}

// Class RRegion
inline TInt RRegion::CheckSpare() const
	{return(iAllocedRects-iCount);}

// Class TRegionFix
template <TInt S>
inline TRegionFix<S>::TRegionFix() : TRegion(-S)
	{}
template <TInt S>
inline TRegionFix<S>::TRegionFix(const TRect &aRect) : TRegion(-S)
	{AddRect(aRect);}
template <TInt S>
inline TRegionFix<S>::TRegionFix(const TRegionFix<S> &aRegion)
	{*this=aRegion;}

template <TInt S>
inline RRegionBuf<S>::RRegionBuf() : RRegion(-S&(~ERRegionBuf),S)
	{}
template <TInt S>
inline RRegionBuf<S>::RRegionBuf(const RRegion &aRegion) 
	{*this=aRegion;}
template <TInt S>
inline RRegionBuf<S>::RRegionBuf(const TRect &aRect) : RRegion(-S&(~ERRegionBuf),S)
	{AddRect(aRect);}
template <TInt S>
inline RRegionBuf<S>::RRegionBuf(const RRegionBuf<S> &aRegion)
    {*this=aRegion;}

// Class TTrap
inline TTrap::TTrap()
	{}

// enum TTimerLockSpec
inline TTimerLockSpec &operator++(TTimerLockSpec &aLock)
	{
	return aLock=((aLock==ETwelveOClock) ? EOneOClock : (TTimerLockSpec)((TInt)aLock+1));
	}
inline TTimerLockSpec operator++(TTimerLockSpec &aLock, TInt)
	{
	TTimerLockSpec l=aLock;
	aLock=((aLock==ETwelveOClock) ? EOneOClock : (TTimerLockSpec)((TInt)aLock+1));
	return l;
	}

// Class TUid
inline TUid TUid::Uid(TInt aUid)
	{TUid uid={aUid};return uid;}
inline TUid TUid::Null()
	{TUid uid={KNullUidValue};return uid;}

// Class TCheckedUid
inline const TUidType& TCheckedUid::UidType() const
    {return(iType);}

// Template class TArray
template <class T>
inline TArray<T>::TArray(TInt (*aCount)(const CBase *aPtr),const TAny *(*anAt)(const CBase *aPtr,TInt anIndex),const CBase *aPtr)
	: iPtr(aPtr),iCount(aCount),iAt(anAt)
	{}
template <class T>
inline TInt TArray<T>::Count() const
	{return((*iCount)(iPtr));}
template <class T>
inline const T &TArray<T>::operator[](TInt anIndex) const
	{return(*((const T *)(*iAt)(iPtr,anIndex)));}

// Array deletion support, uses CBase deletion (virtual d'tor) for all C-classes
template <class T>
void _DeleteArray(T** aBegin,T** aEnd)
	{for (;;) if (aBegin<aEnd) delete *aBegin++; else return;}
template <class T>
struct _ArrayUtil
	{
	static inline void Delete(T* aBegin,T* aEnd,CBase*)
		{::_DeleteArray((CBase**)aBegin,(CBase**)aEnd);}
	static inline void Delete(T* aBegin,T* aEnd,TAny*)
		{::_DeleteArray(aBegin,aEnd);}
	static inline void Delete(T* aArray,TInt aCount)
		{Delete(aArray,aArray+aCount,*aArray);}
	};
#ifndef __TOOLS__

// Template class TFixedArray
IMPORT_C void PanicTFixedArray();

template <class T,TInt S>
inline TFixedArray<T,S>::TFixedArray()
	{}
template <class T,TInt S>
inline void TFixedArray<T,S>::Copy(const T* aList,TInt aLength)
	{__ASSERT_DEBUG(TUint(aLength)<=TUint(S),PanicTFixedArray());Mem::Copy(iRep,aList,aLength*sizeof(T));}
template <class T,TInt S>
inline TFixedArray<T,S>::TFixedArray(const T* aList,TInt aLength)
	{Copy(aList,aLength);}
template <class T,TInt S>
inline void TFixedArray<T,S>::Reset()
	{Mem::FillZ(iRep,sizeof(iRep));}
template <class T,TInt S>
inline TInt TFixedArray<T,S>::Count() const
	{return S;}
template <class T,TInt S>
inline TInt TFixedArray<T,S>::Length() const
	{return sizeof(T);}
template <class T,TInt S>
inline TBool TFixedArray<T,S>::InRange(TInt aIndex)
	{return TUint(aIndex)<S;}
template <class T,TInt S>
inline T& TFixedArray<T,S>::operator[](TInt aIndex)
	{__ASSERT_DEBUG(InRange(aIndex),PanicTFixedArray());return iRep[aIndex];}
template <class T,TInt S>
inline const T& TFixedArray<T,S>::operator[](TInt aIndex) const
	{return CONST_CAST(ThisClass&,*this)[aIndex];}
template <class T,TInt S>
inline T& TFixedArray<T,S>::At(TInt aIndex)
	{__ASSERT_ALWAYS(InRange(aIndex),PanicTFixedArray());return iRep[aIndex];}
template <class T,TInt S>
inline const T& TFixedArray<T,S>::At(TInt aIndex) const
	{return CONST_CAST(ThisClass&,*this).At(aIndex);}
template <class T,TInt S>
inline T* TFixedArray<T,S>::Begin()
	{return &iRep[0];}
template <class T,TInt S>
inline T* TFixedArray<T,S>::End()
	{return &iRep[S];}
template <class T,TInt S>
inline const T* TFixedArray<T,S>::Begin() const
	{return &iRep[0];}
template <class T,TInt S>
inline const T* TFixedArray<T,S>::End() const
	{return &iRep[S];}
template <class T,TInt S>
inline TInt TFixedArray<T,S>::CountFunctionR(const CBase*)
	{return S;}
template <class T,TInt S>
inline const TAny* TFixedArray<T,S>::AtFunctionR(const CBase* aThis,TInt aIndex)
	{return &REINTERPRET_CAST(const ThisClass&,*aThis)[aIndex];}
template <class T,TInt S>
inline TArray<T> TFixedArray<T,S>::Array() const
	{return TArray<T>(CountFunctionR,AtFunctionR,REINTERPRET_CAST(const CBase*,this));}
template <class T,TInt S>
inline void TFixedArray<T,S>::DeleteAll()
	{_ArrayUtil<T>::Delete(iRep,S);}

// Class TIdentityRelation<T>
template <class T>
inline TIdentityRelation<T>::TIdentityRelation( TBool(*anIdentity)(const T&, const T&) )
	{ iIdentity=(TGeneralIdentityRelation)anIdentity; }
template <class T>
inline TIdentityRelation<T>::operator TGeneralIdentityRelation() const
	{ return iIdentity; }

// Class TLinearOrder<T>
template <class T>
inline TLinearOrder<T>::TLinearOrder( TInt(*anOrder)(const T&, const T&) )
	{ iOrder=(TGeneralLinearOrder)anOrder; }
template <class T>
inline TLinearOrder<T>::operator TGeneralLinearOrder() const
	{ return iOrder; }

// Class RPointerArray<T>
template <class T>
inline RPointerArray<T>::RPointerArray()
	: RPointerArrayBase()
	{}
template <class T>
inline RPointerArray<T>::RPointerArray(TInt aGranularity)
	: RPointerArrayBase(aGranularity)
	{}
template <class T>
inline RPointerArray<T>::RPointerArray(T** aEntries, TInt aCount)
	: RPointerArrayBase((TAny **)aEntries, aCount)
	{}
template <class T>
inline void RPointerArray<T>::Close()
	{RPointerArrayBase::Close();}
template <class T>
inline TInt RPointerArray<T>::Count() const
	{ return RPointerArrayBase::Count(); }
template <class T>
inline T* const& RPointerArray<T>::operator[](TInt anIndex) const
	{return (T* const&)At(anIndex);}
template <class T>
inline T*& RPointerArray<T>::operator[](TInt anIndex)
	{return (T*&)At(anIndex);}
template <class T>
inline TInt RPointerArray<T>::Append(const T* anEntry)
	{ return RPointerArrayBase::Append(anEntry); }
template <class T>
inline TInt RPointerArray<T>::Insert(const T* anEntry, TInt aPos)
	{ return RPointerArrayBase::Insert(anEntry,aPos); }
template <class T>
inline void RPointerArray<T>::Remove(TInt anIndex)
	{RPointerArrayBase::Remove(anIndex);}
template <class T>
inline void RPointerArray<T>::Compress()
	{RPointerArrayBase::Compress();}
template <class T>
inline void RPointerArray<T>::GranularCompress()
	{RPointerArrayBase::GranularCompress();}
template <class T>
inline void RPointerArray<T>::Reset()
	{RPointerArrayBase::Reset();}
template <class T>
inline TInt RPointerArray<T>::Find(const T* anEntry) const
	{ return RPointerArrayBase::Find(anEntry); }
template <class T>
inline TInt RPointerArray<T>::Find(const T* anEntry, TIdentityRelation<T> anIdentity) const
	{ return RPointerArrayBase::Find(anEntry,anIdentity); }
template <class T>
inline TInt RPointerArray<T>::FindInAddressOrder(const T* anEntry) const
	{ return RPointerArrayBase::FindIsqUnsigned((TUint)anEntry); }
template <class T>
inline TInt RPointerArray<T>::FindInOrder(const T* anEntry, TLinearOrder<T> anOrder) const
	{ return RPointerArrayBase::FindIsq(anEntry,anOrder); }
template <class T>
inline TInt RPointerArray<T>::FindInAddressOrder(const T* anEntry, TInt& anIndex) const
	{ return RPointerArrayBase::BinarySearchUnsigned((TUint)anEntry,anIndex); }
template <class T>
inline TInt RPointerArray<T>::FindInOrder(const T* anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const
	{ return RPointerArrayBase::BinarySearch(anEntry,anIndex,anOrder); }
template <class T>
inline TInt RPointerArray<T>::SpecificFindInAddressOrder(const T* anEntry, TInt aMode) const
	{ return RPointerArrayBase::FindIsqUnsigned((TUint)anEntry, aMode); }
template <class T>
inline TInt RPointerArray<T>::SpecificFindInOrder(const T* anEntry, TLinearOrder<T> anOrder, TInt aMode) const
	{ return RPointerArrayBase::FindIsq(anEntry,anOrder,aMode); }
template <class T>
inline TInt RPointerArray<T>::SpecificFindInAddressOrder(const T* anEntry, TInt& anIndex, TInt aMode) const
	{ return RPointerArrayBase::BinarySearchUnsigned((TUint)anEntry,anIndex,aMode); }
template <class T>
inline TInt RPointerArray<T>::SpecificFindInOrder(const T* anEntry, TInt& anIndex, TLinearOrder<T> anOrder, TInt aMode) const
	{ return RPointerArrayBase::BinarySearch(anEntry,anIndex,anOrder,aMode); }
template <class T>
inline TInt RPointerArray<T>::InsertInAddressOrder(const T* anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned((TUint)anEntry,EFalse); }
template <class T>
inline TInt RPointerArray<T>::InsertInOrder(const T* anEntry, TLinearOrder<T> anOrder)
	{ return RPointerArrayBase::InsertIsq(anEntry,anOrder,EFalse); }
template <class T>
inline TInt RPointerArray<T>::InsertInAddressOrderAllowRepeats(const T* anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned((TUint)anEntry,ETrue); }
template <class T>
inline TInt RPointerArray<T>::InsertInOrderAllowRepeats(const T* anEntry, TLinearOrder<T> anOrder)
	{ return RPointerArrayBase::InsertIsq(anEntry,anOrder,ETrue); }
template <class T>
inline void RPointerArray<T>::SortIntoAddressOrder()
	{ HeapSortUnsigned(); }
template <class T>
inline void RPointerArray<T>::Sort(TLinearOrder<T> anOrder)
	{ HeapSort(anOrder); }
template <class T>
inline TArray<T*> RPointerArray<T>::Array() const
	{ return TArray<T*>(GetCount,GetElementPtr,(const CBase*)this); }

template <class T>
void RPointerArray<T>::ResetAndDestroy()
	{
	TInt c=Count();
	T** pE=(T**)Entries();
	ZeroCount();
	TInt i;
	for (i=0; i<c; i++)
		{
		delete *pE;
		pE++;
		}
	Reset();
	}

template <class T>
inline RArray<T>::RArray()
	: RArrayBase(sizeof(T))
	{}
template <class T>
inline RArray<T>::RArray(TInt aGranularity)
	: RArrayBase(sizeof(T),aGranularity)
	{}
template <class T>
inline RArray<T>::RArray(TInt aGranularity, TInt aKeyOffset)
	: RArrayBase(sizeof(T),aGranularity,aKeyOffset)
	{}
template <class T>
inline RArray<T>::RArray(TInt aEntrySize,T* aEntries, TInt aCount)
	: RArrayBase(aEntrySize,aEntries,aCount)
	{}
template <class T>
inline void RArray<T>::Close()
	{RArrayBase::Close();}
template <class T>
inline TInt RArray<T>::Count() const
	{return RArrayBase::Count();}
template <class T>
inline const T& RArray<T>::operator[](TInt anIndex) const
	{return *(const T*)At(anIndex); }
template <class T>
inline T& RArray<T>::operator[](TInt anIndex)
	{return *(T*)At(anIndex); }
template <class T>
inline TInt RArray<T>::Append(const T& anEntry)
	{return RArrayBase::Append(&anEntry);}
template <class T>
inline TInt RArray<T>::Insert(const T& anEntry, TInt aPos)
	{return RArrayBase::Insert(&anEntry,aPos);}
template <class T>
inline void RArray<T>::Remove(TInt anIndex)
	{RArrayBase::Remove(anIndex);}
template <class T>
inline void RArray<T>::Compress()
	{RArrayBase::Compress();}
template <class T>
inline void RArray<T>::GranularCompress()
	{RArrayBase::GranularCompress();}
template <class T>
inline void RArray<T>::Reset()
	{RArrayBase::Reset();}
template <class T>
inline TInt RArray<T>::Find(const T& anEntry) const
	{return RArrayBase::Find(&anEntry);}
template <class T>
inline TInt RArray<T>::Find(const T& anEntry, TIdentityRelation<T> anIdentity) const
	{return RArrayBase::Find(&anEntry,anIdentity);}
template <class T>
inline TInt RArray<T>::FindInSignedKeyOrder(const T& anEntry) const
	{return RArrayBase::FindIsqSigned(&anEntry);}
template <class T>
inline TInt RArray<T>::FindInUnsignedKeyOrder(const T& anEntry) const
	{return RArrayBase::FindIsqUnsigned(&anEntry);}
template <class T>
inline TInt RArray<T>::FindInOrder(const T& anEntry, TLinearOrder<T> anOrder) const
	{return RArrayBase::FindIsq(&anEntry,anOrder);}
template <class T>
inline TInt RArray<T>::FindInSignedKeyOrder(const T& anEntry, TInt& anIndex) const
	{return RArrayBase::BinarySearchSigned(&anEntry,anIndex);}
template <class T>
inline TInt RArray<T>::FindInUnsignedKeyOrder(const T& anEntry, TInt& anIndex) const
	{return RArrayBase::BinarySearchUnsigned(&anEntry,anIndex);}
template <class T>
inline TInt RArray<T>::FindInOrder(const T& anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const
	{return RArrayBase::BinarySearch(&anEntry,anIndex,anOrder);}
template <class T>
inline TInt RArray<T>::SpecificFindInSignedKeyOrder(const T& anEntry, TInt aMode) const
 	{return RArrayBase::FindIsqSigned(&anEntry,aMode);}
template <class T>
inline TInt RArray<T>::SpecificFindInUnsignedKeyOrder(const T& anEntry, TInt aMode) const
 	{return RArrayBase::FindIsqUnsigned(&anEntry,aMode);}
template <class T>
inline TInt RArray<T>::SpecificFindInOrder(const T& anEntry, TLinearOrder<T> anOrder, TInt aMode) const
 	{return RArrayBase::FindIsq(&anEntry,anOrder,aMode);}
template <class T>
inline TInt RArray<T>::SpecificFindInSignedKeyOrder(const T& anEntry, TInt& anIndex, TInt aMode) const
 	{return RArrayBase::BinarySearchSigned(&anEntry,anIndex,aMode);}
template <class T>
inline TInt RArray<T>::SpecificFindInUnsignedKeyOrder(const T& anEntry, TInt& anIndex, TInt aMode) const
 	{return RArrayBase::BinarySearchUnsigned(&anEntry,anIndex,aMode);}
template <class T>
inline TInt RArray<T>::SpecificFindInOrder(const T& anEntry, TInt& anIndex, TLinearOrder<T> anOrder, TInt aMode) const
 	{return RArrayBase::BinarySearch(&anEntry,anIndex,anOrder,aMode);}
template <class T>
inline TInt RArray<T>::InsertInSignedKeyOrder(const T& anEntry)
	{return RArrayBase::InsertIsqSigned(&anEntry,EFalse);}
template <class T>
inline TInt RArray<T>::InsertInUnsignedKeyOrder(const T& anEntry)
	{return RArrayBase::InsertIsqUnsigned(&anEntry,EFalse);}
template <class T>
inline TInt RArray<T>::InsertInOrder(const T& anEntry, TLinearOrder<T> anOrder)
	{return RArrayBase::InsertIsq(&anEntry,anOrder,EFalse);}
template <class T>
inline TInt RArray<T>::InsertInSignedKeyOrderAllowRepeats(const T& anEntry)
	{return RArrayBase::InsertIsqSigned(&anEntry,ETrue);}
template <class T>
inline TInt RArray<T>::InsertInUnsignedKeyOrderAllowRepeats(const T& anEntry)
	{return RArrayBase::InsertIsqUnsigned(&anEntry,ETrue);}
template <class T>
inline TInt RArray<T>::InsertInOrderAllowRepeats(const T& anEntry, TLinearOrder<T> anOrder)
	{return RArrayBase::InsertIsq(&anEntry,anOrder,ETrue);}
template <class T>
inline void RArray<T>::SortSigned()
	{HeapSortSigned();}
template <class T>
inline void RArray<T>::SortUnsigned()
	{HeapSortUnsigned();}
template <class T>
inline void RArray<T>::Sort(TLinearOrder<T> anOrder)
	{HeapSort(anOrder);}
template <class T>
inline TArray<T> RArray<T>::Array() const
	{ return TArray<T>(GetCount,GetElementPtr,(const CBase*)this); }

inline RArray<TInt>::RArray()
	: RPointerArrayBase()
	{}
inline RArray<TInt>::RArray(TInt aGranularity)
	: RPointerArrayBase(aGranularity)
	{}
inline void RArray<TInt>::Close()
	{RPointerArrayBase::Close();}
inline TInt RArray<TInt>::Count() const
	{ return RPointerArrayBase::Count(); }
inline const TInt& RArray<TInt>::operator[](TInt anIndex) const
	{return (const TInt&)At(anIndex);}
inline TInt& RArray<TInt>::operator[](TInt anIndex)
	{return (TInt&)At(anIndex);}
inline TInt RArray<TInt>::Append(TInt anEntry)
	{ return RPointerArrayBase::Append((const TAny*)anEntry); }
inline TInt RArray<TInt>::Insert(TInt anEntry, TInt aPos)
	{ return RPointerArrayBase::Insert((const TAny*)anEntry,aPos); }
inline void RArray<TInt>::Remove(TInt anIndex)
	{RPointerArrayBase::Remove(anIndex);}
inline void RArray<TInt>::Compress()
	{RPointerArrayBase::Compress();}
inline void RArray<TInt>::GranularCompress()
	{RPointerArrayBase::GranularCompress();}
inline void RArray<TInt>::Reset()
	{RPointerArrayBase::Reset();}
inline TInt RArray<TInt>::Find(TInt anEntry) const
	{ return RPointerArrayBase::Find((const TAny*)anEntry); }
inline TInt RArray<TInt>::FindInOrder(TInt anEntry) const
	{ return RPointerArrayBase::FindIsqSigned(anEntry); }
inline TInt RArray<TInt>::FindInOrder(TInt anEntry, TInt& anIndex) const
	{ return RPointerArrayBase::BinarySearchSigned(anEntry,anIndex); }
inline TInt RArray<TInt>::SpecificFindInOrder(TInt anEntry, TInt aMode) const
 	{ return RPointerArrayBase::FindIsqSigned(anEntry,aMode); }
inline TInt RArray<TInt>::SpecificFindInOrder(TInt anEntry, TInt& anIndex, TInt aMode) const
 	{ return RPointerArrayBase::BinarySearchSigned(anEntry,anIndex,aMode); }
inline TInt RArray<TInt>::InsertInOrder(TInt anEntry)
	{ return RPointerArrayBase::InsertIsqSigned(anEntry,EFalse); }
inline TInt RArray<TInt>::InsertInOrderAllowRepeats(TInt anEntry)
	{ return RPointerArrayBase::InsertIsqSigned(anEntry,ETrue); }
inline void RArray<TInt>::Sort()
	{ HeapSortSigned(); }
inline TArray<TInt> RArray<TInt>::Array() const
	{ return TArray<TInt>(GetCount,GetElementPtr,(const CBase*)this); }

inline RArray<TUint>::RArray()
	: RPointerArrayBase()
	{}
inline RArray<TUint>::RArray(TInt aGranularity)
	: RPointerArrayBase(aGranularity)
	{}
inline void RArray<TUint>::Close()
	{RPointerArrayBase::Close();}
inline TInt RArray<TUint>::Count() const
	{return RPointerArrayBase::Count(); }
inline const TUint& RArray<TUint>::operator[](TInt anIndex) const
	{return (const TUint&)At(anIndex);}
inline TUint& RArray<TUint>::operator[](TInt anIndex)
	{return (TUint&)At(anIndex);}
inline TInt RArray<TUint>::Append(TUint anEntry)
	{ return RPointerArrayBase::Append((const TAny*)anEntry); }
inline TInt RArray<TUint>::Insert(TUint anEntry, TInt aPos)
	{ return RPointerArrayBase::Insert((const TAny*)anEntry,aPos); }
inline void RArray<TUint>::Remove(TInt anIndex)
	{RPointerArrayBase::Remove(anIndex);}
inline void RArray<TUint>::Compress()
	{RPointerArrayBase::Compress();}
inline void RArray<TUint>::Reset()
	{RPointerArrayBase::Reset();}
inline TInt RArray<TUint>::Find(TUint anEntry) const
	{ return RPointerArrayBase::Find((const TAny*)anEntry); }
inline TInt RArray<TUint>::FindInOrder(TUint anEntry) const
	{ return RPointerArrayBase::FindIsqUnsigned(anEntry); }
inline TInt RArray<TUint>::FindInOrder(TUint anEntry, TInt& anIndex) const
	{ return RPointerArrayBase::BinarySearchUnsigned(anEntry,anIndex); }
inline TInt RArray<TUint>::SpecificFindInOrder(TUint anEntry, TInt aMode) const
 	{ return RPointerArrayBase::FindIsqUnsigned(anEntry,aMode); }
inline TInt RArray<TUint>::SpecificFindInOrder(TUint anEntry, TInt& anIndex, TInt aMode) const
 	{ return RPointerArrayBase::BinarySearchUnsigned(anEntry,anIndex,aMode); }
inline TInt RArray<TUint>::InsertInOrder(TUint anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned(anEntry,EFalse); }
inline TInt RArray<TUint>::InsertInOrderAllowRepeats(TUint anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned(anEntry,ETrue); }
inline void RArray<TUint>::Sort()
	{ HeapSortUnsigned(); }
inline TArray<TUint> RArray<TUint>::Array() const
	{ return TArray<TUint>(GetCount,GetElementPtr,(const CBase*)this); }
#endif


inline void TIpcArgs::Set(TInt,TNothing)
/**
TIpcArgs is an array of 4 arguments (iArgs) bound together with run-time
information (iFlags) describing the type of those arguments.

Sets the specified argument to default value and type

@param aIndex the IPC argument to be set - must be 0, 1, 2, or 3
@param aValue the value to which the nominated argument is set
*/
	{}
inline void TIpcArgs::Set(TInt aIndex,TInt aValue)
/**
TIpcArgs is an array of 4 arguments (iArgs) bound together with run-time
information (iFlags) describing the type of those arguments.

Sets the specified argument to a TInt of the specified value

@param aIndex the IPC argument to be set - must be 0, 1, 2, or 3
@param aValue the value to which the nominated argument is set
*/
	{
	iArgs[aIndex] = aValue;
	iFlags |= EUnspecified<<(aIndex*KBitsPerType);
	}
inline void TIpcArgs::Set(TInt aIndex,const TAny* aValue)
/**
TIpcArgs is an array of 4 arguments (iArgs) bound together with run-time
information (iFlags) describing the type of those arguments.

Sets the specified argument to a TAny* of the specified value

@param aIndex the IPC argument to be set - must be 0, 1, 2, or 3
@param aValue the value to which the nominated argument is set
*/
	{
	iArgs[aIndex] = (TInt)aValue;
	iFlags |= EUnspecified<<(aIndex*KBitsPerType);
	}
inline void TIpcArgs::Set(TInt aIndex,const TDesC8* aValue)
/**
TIpcArgs is an array of 4 arguments (iArgs) bound together with run-time
information (iFlags) describing the type of those arguments.

Sets the specified argument to a TDesC8* of the specified value

@param aIndex the IPC argument to be set - must be 0, 1, 2, or 3
@param aValue the value to which the nominated argument is set
*/
	{
	iArgs[aIndex] = (TInt)aValue;
	iFlags |= EDesC8<<(aIndex*KBitsPerType);
	}
inline void TIpcArgs::Set(TInt aIndex,const TDesC16* aValue)
/**
TIpcArgs is an array of 4 arguments (iArgs) bound together with run-time
information (iFlags) describing the type of those arguments.

Sets the specified argument to a TDesC16* of the specified value

@param aIndex the IPC argument to be set - must be 0, 1, 2, or 3
@param aValue the value to which the nominated argument is set
*/
	{
	iArgs[aIndex] = (TInt)aValue;
	iFlags |= EDesC16<<(aIndex*KBitsPerType);
	}
inline void TIpcArgs::Set(TInt aIndex,TDes8* aValue)
/**
TIpcArgs is an array of 4 arguments (iArgs) bound together with run-time
information (iFlags) describing the type of those arguments.

Sets the specified argument to a TDes8* of the specified value

@param aIndex the IPC argument to be set - must be 0, 1, 2, or 3
@param aValue the value to which the nominated argument is set
*/
	{
	iArgs[aIndex] = (TInt)aValue;
	iFlags |= EDes8<<(aIndex*KBitsPerType);
	}
inline void TIpcArgs::Set(TInt aIndex,TDes16* aValue)
/**
TIpcArgs is an array of 4 arguments (iArgs) bound together with run-time
information (iFlags) describing the type of those arguments.

Sets the specified argument to a TDes16* of the specified value

@param aIndex the IPC argument to be set - must be 0, 1, 2, or 3
@param aValue the value to which the nominated argument is set
*/
	{
	iArgs[aIndex] = (TInt)aValue;
	iFlags |= EDes16<<(aIndex*KBitsPerType);
	}
inline TIpcArgs::TArgType TIpcArgs::Type(TNothing)
	{ return EUnspecified; }
inline TIpcArgs::TArgType TIpcArgs::Type(TInt)
	{ return EUnspecified; }
inline TIpcArgs::TArgType TIpcArgs::Type(const TAny*)
	{ return EUnspecified; }
inline TIpcArgs::TArgType TIpcArgs::Type(const TDesC8*)
	{ return EDesC8; }
inline TIpcArgs::TArgType TIpcArgs::Type(const TDesC16*)
	{ return EDesC16; }
inline TIpcArgs::TArgType TIpcArgs::Type(TDes8*)
	{ return EDes8; }
inline TIpcArgs::TArgType TIpcArgs::Type(TDes16*)
	{ return EDes16; }
inline void TIpcArgs::Assign(TInt&,TIpcArgs::TNothing)
	{}
inline void TIpcArgs::Assign(TInt& aArg,TInt aValue)
	{ aArg = aValue; }
inline void TIpcArgs::Assign(TInt& aArg,const TAny* aValue)
	{ aArg = (TInt)aValue; }
inline void TIpcArgs::Assign(TInt& aArg,const TDesC8* aValue)
	{ aArg = (TInt)aValue; }
inline void TIpcArgs::Assign(TInt& aArg,const TDesC16* aValue)
	{ aArg = (TInt)aValue; }
inline void TIpcArgs::Assign(TInt& aArg,TDes8* aValue)
	{ aArg = (TInt)aValue; }
inline void TIpcArgs::Assign(TInt& aArg,TDes16* aValue)
	{ aArg = (TInt)aValue; }

//
// TSecureId
//
inline TSecureId::TSecureId()
	{}
inline TSecureId::TSecureId(TUint32 aId)
	: iId(aId) {}
inline TSecureId::operator TUint32() const
	{ return iId; }
inline TSecureId::TSecureId(TUid aId)
	: iId(aId.iUid) {}
inline TSecureId::operator TUid() const
	{ return (TUid&)iId; }

//
// SSecureId
//
inline const TSecureId* SSecureId::operator&() const
	{ return (const TSecureId*)this; }
inline SSecureId::operator const TSecureId&() const
	{ return (const TSecureId&)iId; }
inline SSecureId::operator TUint32() const
	{ return iId; }
inline SSecureId::operator TUid() const
	{ return (TUid&)iId; }

//
// TVendorId
//
inline TVendorId::TVendorId()
	{}
inline TVendorId::TVendorId(TUint32 aId)
	: iId(aId) {}
inline TVendorId::operator TUint32() const
	{ return iId; }
inline TVendorId::TVendorId(TUid aId)
	: iId(aId.iUid) {}
inline TVendorId::operator TUid() const
	{ return (TUid&)iId; }

//
// SSecureId
//
inline const TVendorId* SVendorId::operator&() const
	{ return (const TVendorId*)this; }
inline SVendorId::operator const TVendorId&() const
	{ return (const TVendorId&)iId; }
inline SVendorId::operator TUint32() const
	{ return iId; }
inline SVendorId::operator TUid() const
	{ return (TUid&)iId; }

/** Constructs a TSecurityPolicy that will always fail, irrespective of the
checked object's attributes.
*/
inline TSecurityPolicy::TSecurityPolicy()
	{ new (this) TSecurityPolicy(EAlwaysFail); }

//
// Helper classes for defining static Security Policy objects
//
inline const TSecurityPolicy* SSecurityPolicyV1C7::operator&() const
	{ return (const TSecurityPolicy*)this; }
inline SSecurityPolicyV1C7::operator const TSecurityPolicy&() const
	{ return *(const TSecurityPolicy*)this; }
inline const TSecurityPolicy& SSecurityPolicyV1C7::operator()() const
	{ return *(const TSecurityPolicy*)this; }
inline const TSecurityPolicy* SSecurityPolicyV1SVC3::operator&() const
	{ return (const TSecurityPolicy*)this; }
inline SSecurityPolicyV1SVC3::operator const TSecurityPolicy&() const
	{ return *(const TSecurityPolicy*)this; }
inline const TSecurityPolicy& SSecurityPolicyV1SVC3::operator()() const
	{ return *(const TSecurityPolicy*)this; }

#ifndef __REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool SSecurityPolicyV1C7::CheckPolicy(RProcess aProcess, const char* aDiagnosticMessage) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aProcess, aDiagnosticMessage); }
inline TBool SSecurityPolicyV1C7::CheckPolicy(RThread aThread, const char* aDiagnosticMessage) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aThread, aDiagnosticMessage); }
inline TBool SSecurityPolicyV1C7::CheckPolicy(RMessagePtr2 aMsgPtr, const char* aDiagnosticMessage) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aMsgPtr, aDiagnosticMessage); }
inline TBool SSecurityPolicyV1SVC3::CheckPolicy(RProcess aProcess, const char* aDiagnosticMessage) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aProcess, aDiagnosticMessage); }
inline TBool SSecurityPolicyV1SVC3::CheckPolicy(RThread aThread, const char* aDiagnosticMessage) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aThread, aDiagnosticMessage); }
inline TBool SSecurityPolicyV1SVC3::CheckPolicy(RMessagePtr2 aMsgPtr, const char* aDiagnosticMessage) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aMsgPtr, aDiagnosticMessage); }
#else //__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool SSecurityPolicyV1C7::CheckPolicy(RProcess aProcess, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aProcess, NULL); }
inline TBool SSecurityPolicyV1C7::CheckPolicy(RThread aThread, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aThread, NULL); }
inline TBool SSecurityPolicyV1C7::CheckPolicy(RMessagePtr2 aMsgPtr, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aMsgPtr, NULL); }
inline TBool SSecurityPolicyV1SVC3::CheckPolicy(RProcess aProcess, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aProcess, NULL); }
inline TBool SSecurityPolicyV1SVC3::CheckPolicy(RThread aThread, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aThread, NULL); }
inline TBool SSecurityPolicyV1SVC3::CheckPolicy(RMessagePtr2 aMsgPtr, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ((TSecurityPolicy*)this)->CheckPolicy(aMsgPtr, NULL); }
#endif //!__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__


/** Checks this policy against the platform security attributes of aProcess.

On EKA1, tests using this function always pass.

@param aProcess The RProcess object to check against this TSecurityPolicy.
@param aDiagnosticMessage This parameter is ignored.
@return ETrue
*/
#ifndef __REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool TSecurityPolicy::CheckPolicy(RProcess /*aProcess*/, const char* /*aDiagnosticMessage*/) const
	{ return ETrue; }
#else //__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool TSecurityPolicy::CheckPolicy(RProcess /*aProcess*/, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ETrue; }
#endif //!__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__

/** Checks this policy against the platform security attributes of the process
owning aThread.

On EKA1, tests using this function always pass.

@param aThread The thread whose owning process' platform security attributes
are to be checked against this TSecurityPolicy.
@param aDiagnosticMessage This parameter is ignored.
@return ETrue
*/
#ifndef __REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool TSecurityPolicy::CheckPolicy(RThread /*aThread*/, const char* /*aDiagnosticMessage*/) const
	{ return ETrue; }
#else //__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool TSecurityPolicy::CheckPolicy(RThread /*aThread*/, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ETrue; }
#endif //!__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__

/** Checks this policy against the platform security attributes of the process which sent
the given message.

On EKA1, tests using this function always pass.

@param aMsgPtr The RMessagePtr2 object to check against this TSecurityPolicy.
@param aDiagnosticMessage This parameter is ignored.
@return ETrue
*/
#ifndef __REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool TSecurityPolicy::CheckPolicy(RMessagePtr2 /*aMsgPtr*/, const char* /*aDiagnosticMessage*/) const
	{ return ETrue; }
#else //__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__
inline TBool TSecurityPolicy::CheckPolicy(RMessagePtr2 /*aMsgPtr*/, OnlyCreateWithNull /*aDiagnosticMessage*/) const
	{ return ETrue; }
#endif //!__REMOVE_PLATSEC_DIAGNOSTIC_STRINGS__

//
// PlatSec
//

inline TBool PlatSec::IsCapabilityEnforced(TCapability /*aCapability*/)
	{ return 0; }
inline TInt PlatSec::ConfigSetting(TConfigSetting /*aSetting*/)
	{ return 0; }



/**
Appends an object pointer onto the array.

@param anEntry The object pointer to be appended.
@leave  System wide error codes.
*/
template <class T>
inline void RPointerArray<T>::AppendL(const T* anEntry)
	{ User::LeaveIfError(Append(anEntry));}


/**
Inserts an object pointer into the array at the specified position.

@param anEntry The object pointer to be inserted.
@param aPos    The position within the array where the object pointer is to be 
               inserted. The position is relative to zero, i.e. zero implies
			   that a pointer is inserted at the beginning of the array.

@leave  System wide error codes.
@panic USER 131, if aPos is negative, or is greater than the number of object
       pointers currently in the array.
*/
template <class T>
inline void RPointerArray<T>::InsertL(const T* anEntry, TInt aPos)
	{ User::LeaveIfError(Insert(anEntry,aPos)); }


/**
Finds the first object pointer in the array which matches the specified object 
pointer, using a sequential search.

Matching is based on the comparison of pointers.

The find operation always starts at the low index end of the array. There 
is no assumption about the order of objects in the array.

@param anEntry The object pointer to be found.
@return The index of the first matching object pointer within the array.
@leave KErrNotFound, if no matching object pointer can be found.
*/
template <class T>
inline TInt RPointerArray<T>::FindL(const T* anEntry) const
	{ return User::LeaveIfError(Find(anEntry));}


/**
Finds the first object pointer in the array whose object matches the specified 
object, using a sequential search and a matching algorithm.

The algorithm for determining whether two class T objects match is provided 
by a function supplied by the caller.

The find operation always starts at the low index end of the array. There 
is no assumption about the order of objects in the array.

@param anEntry    The object pointer to be found.
@param anIdentity A package encapsulating the function which determines whether 
                  two class T objects match.

@return The index of the first matching object pointer within the array.
@leave  KErrNotFound, if no suitable object pointer can be found.
*/
template <class T>
inline TInt RPointerArray<T>::FindL(const T* anEntry, TIdentityRelation<T> anIdentity) const
	{ return User::LeaveIfError(Find(anEntry, anIdentity));}


/**
Finds the object pointer in the array that matches the specified object
pointer, using a binary search technique.

The function assumes that object pointers in the array are in address order.

@param anEntry The object pointer to be found.

@return The index of the matching object pointer within the array
@leave KErrNotFound, if no suitable object pointer can be found.
*/
template <class T>
inline TInt RPointerArray<T>::FindInAddressOrderL(const T* anEntry) const
	{ return User::LeaveIfError(FindInAddressOrder(anEntry));}


/**
Finds the object pointer in the array whose object matches the specified
object, using a binary search technique and an ordering algorithm.

The function assumes that existing object pointers in the array are ordered 
so that the objects themselves are in object order as determined by an algorithm 
supplied by the caller and packaged as a TLinearOrder<T>.

@param anEntry The object pointer to be found.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.

@return The index of the matching object pointer within the array.
@leave KErrNotFound, if no suitable object pointer can be found.
*/
template <class T>
inline TInt RPointerArray<T>::FindInOrderL(const T* anEntry, TLinearOrder<T> anOrder) const
	{ return User::LeaveIfError(FindInOrder(anEntry, anOrder));}


/**
Finds the object pointer in the array that matches the specified object
pointer, using a binary search technique.

The function assumes that object pointers in the array are in address order.

@param anEntry The object pointer to be found.
@param anIndex A TInt supplied by the caller. On return, contains an index
               value:
               If the function does not leave, this is the index of the
			   matching object pointer within the array. 
               If the function leaves with KErrNotFound, this is the index of the
			   last object pointer within the array which logically
			   precedes anEntry.

@leave KErrNotFound, if no suitable object pointer can be found.
*/
template <class T>
inline void RPointerArray<T>::FindInAddressOrderL(const T* anEntry, TInt& anIndex) const
	{ User::LeaveIfError(FindInAddressOrder(anEntry, anIndex)); }


/**
Finds the object pointer in the array whose object matches the specified
object, using a binary search technique and an ordering algorithm.

The function assumes that existing object pointers in the array are ordered 
so that the objects themselves are in object order as determined by an
algorithm supplied by the caller and packaged as a TLinearOrder<T>.

@param anEntry The object pointer to be found.
@param anIndex A TInt supplied by the caller. On return, contains an
               index value:
			   If the function does not leave, this is the index of the
			   matching object pointer within the array. 
               If the function leaves with KErrNotFound, this is the index of
			   the last object pointer within the array which logically
			   precedes anEntry.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.

@leaves        KErrNotFound, if no suitable object pointer can be found.
*/
template <class T>
inline void RPointerArray<T>::FindInOrderL(const T* anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const
	{ User::LeaveIfError(FindInOrder(anEntry, anIndex, anOrder)); }


/**
Finds the object pointer in the array that matches the specified object
pointer, using a binary search technique. In the case that there is more than
one matching element, finds the first, last or any match as specified.

The function assumes that object pointers in the array are in address order.

@param	anEntry The object pointer to be found.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@return If a matching entry exists an array index depending on aMode as follows:
		EArrayFindMode_First - the index of the first matching entry
		EArrayFindMode_Last - the index of the first entry exceeding the match value
							  or the array count if no such entry exists.
		EArrayFindMode_Any - the index of a matching entry (could be any one)
@leave  KErrNotFound if no matching entry exists.
*/
template <class T>
inline TInt RPointerArray<T>::SpecificFindInAddressOrderL(const T* anEntry, TInt aMode) const
	{ return User::LeaveIfError(SpecificFindInAddressOrder(anEntry, aMode));}


/**
Finds the object pointer in the array whose object matches the specified
object, using a binary search technique and an ordering algorithm.
In the case that there is more than one matching element finds the first, last
or any match as specified.

The function assumes that existing object pointers in the array are ordered 
so that the objects themselves are in object order as determined by an algorithm 
supplied by the caller and packaged as a TLinearOrder<T>.

@param anEntry The object pointer to be found.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@return If a matching entry exists an array index depending on aMode as follows:
		EArrayFindMode_First -	the index of the first matching entry
		EArrayFindMode_Last -	the index of the first entry exceeding the match
								value, or the array count if no such entry exists.
		EArrayFindMode_Any -	the index of a matching entry (could be any one)
@leave  KErrNotFound if no matching entry exists.
*/
template <class T>
inline TInt RPointerArray<T>::SpecificFindInOrderL(const T* anEntry, TLinearOrder<T> anOrder, TInt aMode) const
	{ return User::LeaveIfError(SpecificFindInOrder(anEntry, anOrder, aMode));}


/**
Finds the object pointer in the array that matches the specified object
pointer, using a binary search technique.

The function assumes that object pointers in the array are in address order.

@param anEntry The object pointer to be found.
@param anIndex A TInt supplied by the caller. On return, contains an index
               value depending on whether a match is found and on aMode.
			   If a match is found anIndex is as follows:
				EArrayFindMode_First - the index of the first matching entry
				EArrayFindMode_Last - the index of the first entry exceeding the match
									  value, or the array count if no such entry exists.
				EArrayFindMode_Any - the index of a matching entry (could be any one)
			   If no match is found anIndex is the index of the first entry
			   exceeding the match value, or the array count if no such entry exists.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@leave  KErrNotFound, if no suitable object pointer can be found.
*/
template <class T>
inline void RPointerArray<T>::SpecificFindInAddressOrderL(const T* anEntry, TInt& anIndex, TInt aMode) const
	{ User::LeaveIfError(SpecificFindInAddressOrder(anEntry, anIndex, aMode)); }


/**
Finds the object pointer in the array whose object matches the specified
object, using a binary search technique and an ordering algorithm.

The function assumes that existing object pointers in the array are ordered 
so that the objects themselves are in object order as determined by an
algorithm supplied by the caller and packaged as a TLinearOrder<T>.

@param anEntry The object pointer to be found.
@param anIndex A TInt supplied by the caller. On return, contains an index
               value depending on whether a match is found and on aMode.
			   If a match is found anIndex is as follows:
				EArrayFindMode_First - the index of the first matching entry
				EArrayFindMode_Last - the index of the first entry exceeding the match
									  value, or the array count if no such entry exists.
				EArrayFindMode_Any - the index of a matching entry (could be any one)
			   If no match is found anIndex is the index of the first entry
			   exceeding the match value, or the array count if no such entry exists.

@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@leave  KErrNotFound, if no suitable object pointer can be found.
*/
template <class T>
inline void RPointerArray<T>::SpecificFindInOrderL(const T* anEntry, TInt& anIndex, TLinearOrder<T> anOrder, TInt aMode) const
	{ User::LeaveIfError(SpecificFindInOrder(anEntry, anIndex, anOrder, aMode)); }


/**
Inserts an object pointer into the array in address order.
No duplicate entries are permitted.
The function assumes that existing object pointers within the array are in 
address order.

@param anEntry The object pointer to be inserted.
@leave System wide error codes.
*/
template <class T>
inline void RPointerArray<T>::InsertInAddressOrderL(const T* anEntry)
	{ User::LeaveIfError(InsertInAddressOrder(anEntry)); }


/**
Inserts an object pointer into the array so that the object itself is in object 
order.

The algorithm for determining the order of two class T objects is provided 
by a function supplied by the caller.

No duplicate entries are permitted.

The function assumes that the array is ordered so that the referenced objects 
are in object order.

@param anEntry The object pointer to be inserted.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@leave System wide error codes.
*/
template <class T>
inline void RPointerArray<T>::InsertInOrderL(const T* anEntry, TLinearOrder<T> anOrder)
	{ User::LeaveIfError(InsertInOrder(anEntry, anOrder)); }


/**
Inserts an object pointer into the array in address order, allowing duplicates.

If the new object pointer is a duplicate of an existing object pointer in 
the array, then the new pointer is inserted after the existing one. If more 
than one duplicate object pointer already exists in the array, then any new 
duplicate pointer is inserted after the last one.

The function assumes that existing object pointers within the array are in 
address order.

@param anEntry The object pointer to be inserted.
@leave System wide error codes.
*/
template <class T>
inline void RPointerArray<T>::InsertInAddressOrderAllowRepeatsL(const T* anEntry)
	{ User::LeaveIfError(InsertInAddressOrderAllowRepeats(anEntry)); }


/**
Inserts an object pointer into the array so that the object itself is in object 
order, allowing duplicates

The algorithm for determining the order of two class T objects is provided 
by a function supplied by the caller.

If the specified object is a duplicate of an existing object, then the new 
pointer is inserted after the pointer to the existing object. If more than 
one duplicate object already exists, then the new pointer is inserted after 
the pointer to the last one.

@param anEntry The object pointer to be inserted. 
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@leave System wide error codes.
*/
template <class T>
inline void RPointerArray<T>::InsertInOrderAllowRepeatsL(const T* anEntry, TLinearOrder<T> anOrder)
	{ User::LeaveIfError(InsertInOrderAllowRepeats(anEntry, anOrder)); }


/**
Apends an object onto the array.

@param anEntry    A reference to the object of type class T to be appended.
@leave  System wide error codes.
*/
template <class T>
inline void RArray<T>::AppendL(const T& anEntry)
	{ User::LeaveIfError(Append(anEntry));}


/**
Inserts an object into the array at a specified position.

@param anEntry The class T object to be inserted.
@param aPos    The position within the array where the object is to
               be inserted. The position is relative to zero, i.e. zero
			   implies that an object is inserted at the beginning of
			   the array.
			   
@leave  System wide error codes.
@panic USER 131, if aPos is negative or is greater than the number of objects
       currently in the array.
*/
template <class T>
inline void RArray<T>::InsertL(const T& anEntry, TInt aPos)
	{ User::LeaveIfError(Insert(anEntry, aPos));}


/**
Finds the first object in the array which matches the specified object using 
a sequential search.

Matching is based on the comparison of a TInt value at the key offset position 
within the objects.

The find operation always starts at the low index end of the array. There 
is no assumption about the order of objects in the array.

@param anEntry A reference to an object of type class T to be used for matching.

@return The index of the first matching object within the array. 
@leave  KErrNotFound, if no matching object can be found.
*/
template <class T>
inline TInt RArray<T>::FindL(const T& anEntry) const
	{ return User::LeaveIfError(Find(anEntry));}


/**
Finds the first object in the array which matches the specified object using 
a sequential search and a matching algorithm.

The algorithm for determining whether two class T type objects match is provided 
by a function supplied by the caller.

The find operation always starts at the low index end of the array. There 
is no assumption about the order of objects in the array.

@param anEntry    A reference to an object of type class T to be used
                  for matching.
@param anIdentity A package encapsulating the function which determines whether 
                  two class T type objects match.

@return The index of the first matching object within the array.
@leave  KErrNotFound, if no matching object can be found.
*/
template <class T>
inline TInt RArray<T>::FindL(const T& anEntry, TIdentityRelation<T> anIdentity) const
	{ return User::LeaveIfError(Find(anEntry, anIdentity));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique.

The function assumes that existing objects within the array are in signed 
key order.

@param anEntry A reference to an object of type class T to be used for matching.

@return The index of the matching object within the array.
@leave  KErrNotFound, if no matching object can be found.
*/
template <class T>
inline TInt RArray<T>::FindInSignedKeyOrderL(const T& anEntry) const
	{ return User::LeaveIfError(FindInSignedKeyOrder(anEntry));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique.

The function assumes that existing objects within the array are in unsigned 
key order.

@param anEntry A reference to an object of type class T to be used for matching.

@return The index of the matching object within the array.
@leave  KErrNotFound, if no matching object can be found.
*/
template <class T>
inline TInt RArray<T>::FindInUnsignedKeyOrderL(const T& anEntry) const
	{ return User::LeaveIfError(FindInUnsignedKeyOrder(anEntry));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique and an ordering algorithm.

The function assumes that existing objects within the array are in object 
order as determined by an algorithm supplied by the caller and packaged as 
a TLinearOrder<T>.

@param anEntry A reference to an object of type class T to be used for matching.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.

@return The index of the matching object within the array.
@leave  KErrNotFound if no matching object can be found.
*/
template <class T>
inline TInt RArray<T>::FindInOrderL(const T& anEntry, TLinearOrder<T> anOrder) const
{ return User::LeaveIfError(FindInOrder(anEntry, anOrder));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique.

The function assumes that existing objects within the array are in signed 
key order.

@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains an index value of the matching object within the array.
			   If the function leaves with KErrNotFound, this is the index of the last
			   object within the array which logically precedes anEntry.

@leaves KErrNotFound, if no matching object can be found.
*/
template <class T>
inline void RArray<T>::FindInSignedKeyOrderL(const T& anEntry, TInt& anIndex) const
	{ User::LeaveIfError(FindInSignedKeyOrder(anEntry, anIndex));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique.

The function assumes that existing objects within the array are in unsigned 
key order.

@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains an index value of the matching object within the array. 
			   If the function leaves with KErrNotFound, this is the index of the
			   last object within the array which logically precedes anEntry.

@leave  KErrNotFound, if no matching object can be found.
*/
template <class T>
inline void RArray<T>::FindInUnsignedKeyOrderL(const T& anEntry, TInt& anIndex) const
	{ User::LeaveIfError(FindInUnsignedKeyOrder(anEntry, anIndex));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique and an ordering algorithm.

The function assumes that existing objects within the array are in object 
order as determined by an algorithm supplied by the caller and packaged as 
a TLinearOrder<T>.

@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains the index value of the matching object within the array
			   If the function leaves with KErrNotFound, this is the index of the
			   last object within the array which logically precedes anEntry.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.

@leave  KErrNotFound if no matching object can be found.
*/
template <class T>
inline void RArray<T>::FindInOrderL(const T& anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const
	{ User::LeaveIfError(FindInOrder(anEntry, anIndex, anOrder));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique. The element ordering is determined by a signed 32-bit word
(the key) embedded in each array element. In the case that there is more than
one matching element, finds the first, last or any match as specified.

The function assumes that existing objects within the array are in signed 
key order.

@param anEntry A reference to an object of type class T to be used for matching.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@return If a matching entry exists an array index depending on aMode as follows:
		EArrayFindMode_First - the index of the first matching entry
		EArrayFindMode_Last - the index of the first entry exceeding the match value
							  or the array count if no such entry exists.
		EArrayFindMode_Any - the index of a matching entry (could be any one)
@leave  KErrNotFound if no matching entry exists.
*/
template <class T>
inline TInt RArray<T>::SpecificFindInSignedKeyOrderL(const T& anEntry, TInt aMode) const
{ return User::LeaveIfError(SpecificFindInSignedKeyOrder(anEntry, aMode));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique. The element ordering is determined by an unsigned 32-bit word
(the key) embedded in each array element. In the case that there is more than
one matching element, finds the first, last or any match as specified.

The function assumes that existing objects within the array are in unsigned 
key order.

@param anEntry A reference to an object of type class T to be used for matching.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@return If a matching entry exists an array index depending on aMode as follows:
		EArrayFindMode_First - the index of the first matching entry
		EArrayFindMode_Last - the index of the first entry exceeding the match value
							  or the array count if no such entry exists.
		EArrayFindMode_Any - the index of a matching entry (could be any one)
@leave  KErrNotFound if no matching entry exists.
*/
template <class T>
inline TInt RArray<T>::SpecificFindInUnsignedKeyOrderL(const T& anEntry, TInt aMode) const
	{ return User::LeaveIfError(SpecificFindInUnsignedKeyOrder(anEntry, aMode));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique and an ordering algorithm.

The function assumes that existing objects within the array are in object 
order as determined by an algorithm supplied by the caller and packaged as 
a TLinearOrder<T>.

@param anEntry A reference to an object of type class T to be used for matching.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@return If a matching entry exists an array index depending on aMode as follows:
		EArrayFindMode_First - the index of the first matching entry
		EArrayFindMode_Last - the index of the first entry exceeding the match value
							  or the array count if no such entry exists.
		EArrayFindMode_Any - the index of a matching entry (could be any one)
@leave KErrNotFound if no matching entry exists.
*/
template <class T>
inline TInt RArray<T>::SpecificFindInOrderL(const T& anEntry, TLinearOrder<T> anOrder, TInt aMode) const
{ return User::LeaveIfError(SpecificFindInOrder(anEntry, anOrder, aMode));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique. The element ordering is determined by a signed 32-bit word
(the key) embedded in each array element. In the case that there is more than
one matching element, finds the first, last or any match as specified.

The function assumes that existing objects within the array are in signed 
key order.

@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains an array index as follows:
				If a matching entry exists an array index depending on aMode as follows:
				EArrayFindMode_First - the index of the first matching entry
				EArrayFindMode_Last - the index of the first entry exceeding the match value
									  or the array count if no such entry exists.
				EArrayFindMode_Any - the index of a matching entry (could be any one)
			   If the function leaves, anIndex is the index of the first entry
			   exceeding the match value, or the array count if no such entry exists.
@param aMode	Specifies whether to find first, last or any match (TArrayFindMode)
@leave KErrNotFound if no matching entry exists.
*/
template <class T>
inline void RArray<T>::SpecificFindInSignedKeyOrderL(const T& anEntry, TInt& anIndex, TInt aMode) const
	{ User::LeaveIfError(SpecificFindInSignedKeyOrder(anEntry, anIndex, aMode));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique. The element ordering is determined by an unsigned 32-bit word
(the key) embedded in each array element. In the case that there is more than
one matching element, finds the first, last or any match as specified.

The function assumes that existing objects within the array are in unsigned 
key order.

@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains an array index as follows:
				If a matching entry exists an array index depending on aMode as follows:
				EArrayFindMode_First - the index of the first matching entry
				EArrayFindMode_Last - the index of the first entry exceeding the match value
									  or the array count if no such entry exists.
				EArrayFindMode_Any - the index of a matching entry (could be any one)
			   If the function leaves, anIndex is the index of the first entry
			   exceeding the match value, or the array count if no such entry exists.
@param aMode	Specifies whether to find first, last or any match (TArrayFindMode)
@leave KErrNotFound if no matching entry exists.
*/
template <class T>
inline void RArray<T>::SpecificFindInUnsignedKeyOrderL(const T& anEntry, TInt& anIndex, TInt aMode) const
	{ User::LeaveIfError(SpecificFindInUnsignedKeyOrder(anEntry, anIndex, aMode));}


/**
Finds the object in the array which matches the specified object using a binary 
search technique and a specified ordering algorithm. In the case that there is
more than one matching element, finds the first, last or any match as specified.

The function assumes that existing objects within the array are in object 
order as determined by an algorithm supplied by the caller and packaged as 
a TLinearOrder<T>.

@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains an array index as follows:
				If a matching entry exists an array index depending on aMode as follows:
				EArrayFindMode_First - the index of the first matching entry
				EArrayFindMode_Last - the index of the first entry exceeding the match value
									  or the array count if no such entry exists.
				EArrayFindMode_Any - the index of a matching entry (could be any one)
			   If the function leaves, anIndex is the index of the first entry
			   exceeding the match value, or the array count if no such entry exists.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@param aMode	Specifies whether to find first, last or any match (TArrayFindMode)
@leave KErrNotFound if no matching entry exists.
*/
template <class T>
inline void RArray<T>::SpecificFindInOrderL(const T& anEntry, TInt& anIndex, TLinearOrder<T> anOrder, TInt aMode) const
	{ User::LeaveIfError(SpecificFindInOrder(anEntry, anIndex, anOrder, aMode));}


/**
Inserts an object into the array in ascending signed key order.

The order of two class T type objects is based on comparing a TInt value
located at the key offset position within the class T object.

No duplicate entries are permitted.

@param anEntry A reference to the object of type class T to be inserted.
@leave System wide error codes.
*/
template <class T>
inline void RArray<T>::InsertInSignedKeyOrderL(const T& anEntry)
	{ User::LeaveIfError(InsertInSignedKeyOrder(anEntry));}


/**
Inserts an object into the array in ascending unsigned key order, not allowing 
duplicate entries.

The order of two class T type objects is based on comparing a TUint value 
located at the key offset position within the class T object. 

@param anEntry A reference to the object of type class T to be inserted.
@leave System wide error codes.
*/
template <class T>
inline void RArray<T>::InsertInUnsignedKeyOrderL(const T& anEntry)
	{ User::LeaveIfError(InsertInUnsignedKeyOrder(anEntry));}


/**
Inserts an object of into the array in object order.

The algorithm for determining the order of two class T type objects is provided 
by a function supplied by the caller.

No duplicate entries are permitted.

The function assumes that existing objects within the array are in object 
order.

@param anEntry A reference to the object of type class T to be inserted.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@leave System wide error codes.
*/
template <class T>
inline void RArray<T>::InsertInOrderL(const T& anEntry, TLinearOrder<T> anOrder)
	{ User::LeaveIfError(InsertInOrder(anEntry, anOrder));}


/**
Inserts an object into the array in ascending signed key order,
allowing duplicates.

The order of two class T type objects is based on comparing a TInt value
located at the key offset position within the class T object. 

If anEntry is a duplicate of an existing object in the array, then the new 
object is inserted after the existing object. If more than one duplicate object 
already exists in the array, then any new duplicate object is inserted after 
the last one.

@param anEntry A reference to the object of type class T to be inserted.
@leave System wide error codes.
*/
template <class T>
inline void RArray<T>::InsertInSignedKeyOrderAllowRepeatsL(const T& anEntry)
	{ User::LeaveIfError(InsertInSignedKeyOrderAllowRepeats(anEntry));}


/**
Inserts an object into the array in ascending unsigned key order, allowing 
duplicates.

The order of two class T type objects is based on comparing a TUint value 
located at the key offset position within the class T object. 

If anEntry is a duplicate of an existing object in the array, then the new 
object is inserted after the existing object. If more than one duplicate object 
already exists in the array, then any new duplicate object is inserted after 
the last one.

@param anEntry A reference to the object of type class T to be inserted.
@leave System wide error codes.
*/
template <class T>
inline void RArray<T>::InsertInUnsignedKeyOrderAllowRepeatsL(const T& anEntry)
	{ User::LeaveIfError(InsertInUnsignedKeyOrderAllowRepeats(anEntry));}


/**
Inserts an object into the array in object order, allowing duplicates.

The algorithm for determining the order of two class T type objects is provided 
by a function supplied by the caller.

If anEntry is a duplicate of an existing object in the array, then the new 
object is inserted after the existing object. If more than one duplicate object 
already exists in the array, then anEntry is inserted after the last one.

The function assumes that existing objects within the array are in object 
order.

@param anEntry A reference to the object of type class T to be inserted.
@param anOrder A package encapsulating the function which determines the order 
               of two class T objects.
@leave System wide error codes.
*/
template <class T>
inline void RArray<T>::InsertInOrderAllowRepeatsL(const T& anEntry, TLinearOrder<T> anOrder)
	{ User::LeaveIfError(InsertInOrderAllowRepeats(anEntry, anOrder));}


/**
Appends a signed integer onto the array.
	
@param anEntry The signed integer to be appended.
@leave  System wide error codes.
*/
inline void RArray<TInt>::AppendL(TInt anEntry)
	{ User::LeaveIfError(Append(anEntry));}


/**
Inserts a signed integer into the array at the specified position.
	
@param anEntry The signed integer to be inserted.
@param aPos    The position within the array where the signed integer is to be 
	           inserted. The position is relative to zero, i.e. zero implies
			   that an entry is inserted at the beginning of the array.
		   
@leave  System wide error codes.
@panic USER 131, if aPos is negative, or is greater than the number of entries
       currently in the array.
*/
inline void RArray<TInt>::InsertL(TInt anEntry, TInt aPos)
	{ User::LeaveIfError(Insert(anEntry, aPos));}


/**
Finds the first signed integer in the array which matches the specified signed 
integer using a sequential search.
The find operation always starts at the low index end of the array. There 
is no assumption about the order of entries in the array.
	
@param anEntry The signed integer to be found.

@return The index of the first matching signed integer within the array.
@leave  KErrNotFound, if no matching entry can be found.
*/
inline TInt RArray<TInt>::FindL(TInt anEntry) const
	{ return User::LeaveIfError(Find(anEntry));}


/**
Finds the signed integer in the array that matches the specified signed integer 
using a binary search technique.
The function assumes that the array is in signed integer order.
	
@param anEntry The signed integer to find.

@return The index of the matching signed integer within the array.
@leave  KErrNotFound, if no match can be found.
*/
inline TInt RArray<TInt>::FindInOrderL(TInt anEntry) const
	{ return User::LeaveIfError(FindInOrder(anEntry));}


/**
Finds the signed integer in the array that matches the specified signed integer
using a binary search technique.
	
The function assumes that the array is in signed integer order.
	
@param anEntry The signed integer to find.
@param anIndex A TInt suplied by the caller. On return contains an index value
               of the matching signed integer within the array.
			   If the function leaves with KErrNotFound, this is the index of the
			   last signed integer within the array which logically precedes anEntry. 

@leave  KErrNotFound if no  match can be found.
*/
inline void RArray<TInt>::FindInOrderL(TInt anEntry, TInt& anIndex) const
	{ User::LeaveIfError(FindInOrder(anEntry, anIndex));}


/**
Finds the signed integer in the array that matches the specified signed integer 
using a binary search technique. In the case that there is more than one matching
element, finds the first, last or any match as specified.
	
The function assumes that the array is in signed integer order.
	
@param anEntry The signed integer to find.
@param aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@return If a matching entry exists an array index depending on aMode as follows:
		EArrayFindMode_First - the index of the first matching entry
		EArrayFindMode_Last - the index of the first entry exceeding the match value
							  or the array count if no such entry exists.
		EArrayFindMode_Any - the index of a matching entry (could be any one)
@leave  KErrNotFound if no matching entry exists.
*/
inline TInt RArray<TInt>::SpecificFindInOrderL(TInt anEntry, TInt aMode) const
	{ return User::LeaveIfError(SpecificFindInOrder(anEntry, aMode));}


/**
Finds the signed integer in the array that matches the specified signed integer
using a binary search technique. In the case that there is more than
one matching element, finds the first, last or any match as specified.

The function assumes that the array is in signed integer order.
	
@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains an array index as follows:
				If a matching entry exists an array index depending on aMode as follows:
				EArrayFindMode_First - the index of the first matching entry
				EArrayFindMode_Last - the index of the first entry exceeding the match value
									  or the array count if no such entry exists.
				EArrayFindMode_Any - the index of a matching entry (could be any one)
			   If no match is found anIndex is the index of the first entry
			   exceeding the match value, or the array count if no such entry exists.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)
@leave KErrNotFound if no matching entry exists.
*/
inline void RArray<TInt>::SpecificFindInOrderL(TInt anEntry, TInt& anIndex, TInt aMode) const
	{ User::LeaveIfError(SpecificFindInOrder(anEntry, anIndex, aMode));}


/**
Inserts a signed integer into the array in signed integer order.
No duplicate entries are permitted.
The function assumes that existing entries within the array are in signed 
integer order.

@param anEntry The signed integer to be inserted
@leave  System wide error codes.
*/
inline void RArray<TInt>::InsertInOrderL(TInt anEntry)
	{ User::LeaveIfError(InsertInOrder(anEntry));}


/**
Inserts a signed integer into the array in signed integer order,
allowing duplicates.
If anEntry is a duplicate of an existing entry in the array, then the new 
signed integer is inserted after the existing one. If more than one duplicate 
entry already exists in the array, then any new duplicate signed integer is 
inserted after the last one.
The function assumes that existing entries within the array are in signed 
integer order.
	
@param anEntry The signed integer to be inserted.
@leave  System wide error codes.
*/
inline void RArray<TInt>::InsertInOrderAllowRepeatsL(TInt anEntry)
	{ User::LeaveIfError(InsertInOrderAllowRepeats(anEntry));}


/**
Appends an unsigned integer onto the array.
	
@param anEntry The unsigned integer to be appended.
@leave  System wide error codes.
*/
inline void RArray<TUint>::AppendL(TUint anEntry)
	{ User::LeaveIfError(Append(anEntry));}


/**
Inserts an unsigned integer into the array at the specified position.
	
@param anEntry  The unsigned integer to be inserted.
@param aPos     The position within the array where the unsigned integer is to 
	            be inserted. The position is relative to zero, i.e. zero
				implies that an entry is inserted at the beginning of
				the array.
			
@leave  System wide error codes.
@panic USER 131, if aPos is negative, or is greater than the number of entries
       currently in the array.
*/
inline void RArray<TUint>::InsertL(TUint anEntry, TInt aPos)
	{ User::LeaveIfError(Insert(anEntry, aPos));}


/**
Finds the first unsigned integer in the array which matches the specified
value, using a sequential search.
The find operation always starts at the low index end of the array. There 
is no assumption about the order of entries in the array.
	
@param anEntry The unsigned integer to be found.
@return The index of the first matching unsigned integer within the array.
@leave  KErrNotFound, if no matching entry can be found.
*/
inline TInt RArray<TUint>::FindL(TUint anEntry) const
	{ return User::LeaveIfError(Find(anEntry));}


/**
Finds the unsigned integer in the array which matches the specified value, 
using a binary search technique.
	
The functions assume that existing entries within the array are in unsigned 
integer order.
	
@param anEntry The unsigned integer to be found.

@return The index of the matching unsigned integer within the array;
@leave  KErrNotFound, if no matching entry can be found.
*/
inline TInt RArray<TUint>::FindInOrderL(TUint anEntry) const
	{ return User::LeaveIfError(FindInOrder(anEntry));}


/**
Finds the unsigned integer in the array which matches the specified value, 
using a binary search technique.
If the index cannot be found, the function returns the index of the last
unsigned integer within the array which logically precedes anEntry.
The functions assume that existing entries within the array are in unsigned 
integer order.
	
@param anEntry The unsigned integer to be found.
@param anIndex A TInt supplied by the caller. On return, contains an index
               value of the matching unsigned integer within the array. 
	           If the function leaves with KErrNotFound, this is the index of
			   the last unsigned integer within the array which logically
			   precedes anEntry.

@leave  KErrNotFound, if no matching entry can be found.
*/
inline void RArray<TUint>::FindInOrderL(TUint anEntry, TInt& anIndex) const
	{ User::LeaveIfError(FindInOrder(anEntry, anIndex));}


/**
Finds the unsigned integer in the array that matches the specified unsigned integer 
using a binary search technique. In the case that there is more than one matching
element, finds the first, last or any match as specified.
	
The function assumes that the array is in unsigned integer order.
	
@param anEntry The signed integer to find.
@param aMode	Specifies whether to find first, last or any match (TArrayFindMode)

@return If a matching entry exists an array index depending on aMode as follows:
		EArrayFindMode_First - the index of the first matching entry
		EArrayFindMode_Last - the index of the first entry exceeding the match value
							  or the array count if no such entry exists.
		EArrayFindMode_Any - the index of a matching entry (could be any one)
@leave KErrNotFound if no matching entry exists.
*/
inline TInt RArray<TUint>::SpecificFindInOrderL(TUint anEntry, TInt aMode) const
	{ return User::LeaveIfError(SpecificFindInOrder(anEntry, aMode));}


/**
Finds the unsigned integer in the array that matches the specified unsigned integer
using a binary search technique. In the case that there is more than
one matching element, finds the first, last or any match as specified.

The function assumes that the array is in unsigned integer order.
	
@param anEntry A reference to an object of type class T to be used for matching.
@param anIndex On return contains an array index as follows:
				If a matching entry exists an array index depending on aMode as follows:
				EArrayFindMode_First - the index of the first matching entry
				EArrayFindMode_Last - the index of the first entry exceeding the match value
									  or the array count if no such entry exists.
				EArrayFindMode_Any - the index of a matching entry (could be any one)
			   If no match is found anIndex is the index of the first entry
			   exceeding the match value, or the array count if no such entry exists.
@param	aMode	Specifies whether to find first, last or any match (TArrayFindMode)
@leave KErrNotFound if no matching entry exists.
*/
inline void RArray<TUint>::SpecificFindInOrderL(TUint anEntry, TInt& anIndex, TInt aMode) const
	{ User::LeaveIfError(SpecificFindInOrder(anEntry, anIndex, aMode));}


/**
Inserts an unsigned integer into the array in unsigned integer order.
No duplicate entries are permitted.
The function assumes that existing entries within the array are in unsigned 
integer order.
	
@param anEntry The unsigned integer to be inserted.
@leave  System wide error codes.
*/
inline void RArray<TUint>::InsertInOrderL(TUint anEntry)
	{ User::LeaveIfError(InsertInOrder(anEntry));}


/**
Inserts an unsigned integer into the array in unsigned integer order, allowing 
duplicates.
If the new integer is a duplicate of an existing entry in the array, then 
the new unsigned integer is inserted after the existing one. If more than 
one duplicate entry already exists in the array, then any new duplicate
unsigned integer is inserted after the last one.
	
The function assumes that existing entries within the array are in unsigned 
integer order.
	
@param anEntry The unsigned integer to be inserted.
@leave  System wide error codes.
*/
inline void RArray<TUint>::InsertInOrderAllowRepeatsL(TUint anEntry)
	{ User::LeaveIfError(InsertInOrderAllowRepeats(anEntry));}


/**
Sets the priority of the client's process.

@param aPriority The priority value.
*/
inline void RMessagePtr2::SetProcessPriorityL(TProcessPriority aPriority) const
	{ User::LeaveIfError(SetProcessPriority(aPriority));}


/**
Opens a handle on the client thread.

@param aClient    On successful return, the handle to the client thread.
@param aOwnerType An enumeration whose enumerators define the ownership of
                  the handle. If not explicitly specified,
                  EOwnerProcess is taken as default.
*/
inline void RMessagePtr2::ClientL(RThread& aClient, TOwnerType aOwnerType) const
	{ User::LeaveIfError(Client(aClient, aOwnerType));}
