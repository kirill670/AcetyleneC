// CUSTOMSERVER.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Server classes inlines
inline TInt CCustomServer::SessionCount() const
    { return iSessionCount; }

inline RLibrary& CCustomServer::Library() const
    { return (RLibrary&)iLib; }

inline MCustomServerManager& CCustomServer::Manager() const
    { return *iManager; }

inline void CCustomServer::SetLib(const RLibrary &aLib)
    { iLib = aLib; }

inline void CCustomServer::DeferredDelete()
    { iDeleter->Call(); }

inline TCustomServerServInfo& CCustomServer::Info() const
    { return *iInfo; }


//////////////////////////////////////////////////////////////////////////////

inline CCustomServer& CCustomServerSession::Server() const
    { return *iServer; }

inline void CCustomServerSession::DoCancel()
    { iMode=ECSIdle; }

inline void CCustomServerSession::Write(TDes8 *aPdu)
    {
	iCSWriter->OnSessionWrite(aPdu,iStatus);
	iMode = ECSWriting;
	SetActive();
	}

inline TBool CCustomServerSession::IsWriting() const
    { return iMode==ECSWriting; }


//////////////////////////////////////////////////////////////////////////////
//
// TRemSvPtr
//
//////////////////////////////////////////////////////////////////////////////

inline TRemSvPtr::TRemSvPtr()
    : TPtr8(0, 0)
    { }

inline TRemSvPtr::TRemSvPtr(TUint8* iBuf, TInt aLength)
    : TPtr8(iBuf, aLength, aLength)
    { }

inline void TRemSvPtr::WSet(TRemSvPtr& aPtr, TInt anOffset)
    { WSet(aPtr, anOffset, aPtr.MaxLength()-anOffset); }

inline TUint16 TRemSvPtr::GetWord(TInt anOffset) const
	{ return SiboUtil::Get16((TUint8 *)iPtr+anOffset); }

inline TUint32 TRemSvPtr::GetLong(TInt anOffset) const
	{ return SiboUtil::Get32((TUint8 *)iPtr+anOffset); }

inline void TRemSvPtr::PutLong(TInt anOffset, TUint32 aVal)
	{ SiboUtil::Put32((TUint8 *)iPtr+anOffset, aVal); }

inline void TRemSvPtr::PutWord(TInt anOffset, TUint16 aVal)
	{ SiboUtil::Put16((TUint8 *)iPtr+anOffset, aVal); }

inline TInt64 TRemSvPtr::GetInt64(TInt aOffset)
    { return TInt64(GetLong(aOffset+4), GetLong(aOffset)); }

inline void TRemSvPtr::PutInt64(TInt aOffset, TInt64 aVal)
    { PutLong(aOffset, aVal.Low()); PutLong(aOffset+4, aVal.High()); }

void TRemSvPtr::SetDesLength32(TInt aOffset, TInt aLength)
    { PutWord(aOffset, (TUint16)aLength); }

