//K32Fir.inl
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//

#include <K32Fir.h>


inline TInt DFirPhysChannel::SetIrRange(TUint aRange)
	{return KErrNotSupported;}

inline void DFirPhysChannel::SetComm(DLddFirChannel *aLDD)
	{iLDD=(DLddFirChannel *)aLDD;}

inline void DFirPhysChannel::SetCurrent(TInt aCurrent)
	{ iLDD->SetCurrentConsumptionInMilliAmps(aCurrent); }

inline void DLddFirChannel::SetCurrentConsumptionInMilliAmps(TInt aValue)
	{ iPowerHandler->SetCurrentConsumptionInMilliAmps(aValue); }
