// D32RCHG.INL
//
// Copyright (c) Symbian Software Ltd 1996-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/

_LIT(KRDevRecharger,"Recharger");
inline TInt RDevRecharger::Open(TInt aUnit)
	{return(DoCreate(KRDevRecharger,TVersion(0,1,1),NULL,aUnit,NULL,NULL));}

inline TInt RDevRecharger::ChargeType(TInt& aChargeType)
	{return(DoControl(EGetChargeType,(TAny*)&aChargeType));}

inline TInt RDevRecharger::SetChargeType(TInt aChargeType)
	{return(DoControl(ESetChargeType,(TAny*)aChargeType));}

inline TInt RDevRecharger::ChargeInfo(TDes8& aChargeInfo)
	{return(DoControl(EGetChargeInfo,&aChargeInfo));}

//
