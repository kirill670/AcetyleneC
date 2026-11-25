// P32STD.INL
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//


// Class TPBusCallBack
inline TPBusCallBack::TPBusCallBack(CBase *anOwner,const TCallBack &aCallBack)
	: iOwner(anOwner),iEventMask(0),iCallBack(aCallBack),iCallBackReason(0),iCallBackInfo(0),iSglEvent(0)
	{iBus=KInvalidPBusNum; iController=NULL;}

inline TPBusCallBack::TPBusCallBack(CBase *anOwner,const TCallBack &aCallBack,TUint anEventMask)
	: iOwner(anOwner),iEventMask(anEventMask),iCallBack(aCallBack),iCallBackReason(0),iCallBackInfo(0),iSglEvent(0)
	{iBus=KInvalidPBusNum; iController=NULL;}

inline void TPBusCallBack::SetEventMask(TUint anEventMask)
    {iEventMask=anEventMask;}

inline TInt TPBusCallBack::CallBackReason()
	{return(iCallBackReason);}

inline TInt TPBusCallBack::CallBackInfo()
	{return(iCallBackInfo);}

// Class DPeriphBusController
inline DPeriphBusPowerHandler& DPeriphBusController::PowerHandler()
    {return(*iPowerHandler);}

// Class TMediaChangeBase
inline TBool TMediaChangeBase::IsPostponed()
	{return(iPostponed);}

inline TBool TMediaChangeBase::IsPostponed(CBase *aClientID)
	{return(iPostponed&&iPostponeClientID==aClientID);}

inline TInt TMediaChangeBase::Number()
	{return(iMediaChangeNum);}

// Class TPBusPsuBase
inline TBool TPBusPsuBase::IsOff() 
	{return(iState==EPsuOff);}

inline void TPBusPsuBase::SetCurrLimited()
	{iCurrLimited=ETrue;}

inline void TPBusPsuBase::ResetInactivityTimer()
	{iInactivityCount=0;}

inline TUint TPBusPsuBase::VoltageSupported()
	{return(iVoltageSupported);}

inline TInt TPBusPsuBase::MaxCurrentInMicroAmps()
	{return(iMaxCurrentInMicroAmps);}

/* ???
// TMediaChangeBaseNotifier
inline void TMediaChangeBaseNotifier::SignalMediaChange()
	{iThread->RequestComplete(iReqStat,KErrNone);}

inline TBool TMediaChangeBaseNotifier::IsCallBackActive()
	{return(iReqStat!=NULL&&iThread!=NULL);}
*/
