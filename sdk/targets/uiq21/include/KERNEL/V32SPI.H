// V32SPI.H
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __V32SPI_H__
#define __V32SPI_H__

#if defined(_DEBUG)
//#define __DEBUG_INT__ 1
//#define __DEBUG_RAW__ 1
//#define __DEBUG_SMOOTH__ 1
//#define __DEBUG_CONFIDENCE__ 1
//#define __DEBUG_VOLTAGE__ 1
//#define __DEBUG_CONTINUOUS__ 1
//#define __DEBUG_ADJUST__ 1
//#define __DEBUG_STATUS__ 1
//#define __DEBUG_SWITCH_ON__ 1
//#define __DEBUG_CHANGE_BATTERY__ 1
#endif

const TInt KSpiChannelUnbound=-1;

enum TSpiChannelType
    {
    ESpiChannelOneShot,
    ESpiChannelAveraged
    };

class TSpiController;
class TSpiChannel
    {
public:
    IMPORT_C TSpiChannel();
	IMPORT_C TInt Bind(const TDesC8& aName);
    IMPORT_C TInt UnBind();
    IMPORT_C void Read();
    IMPORT_C void SetType(TSpiChannelType aType);
	inline TBool IsBound() {return(iChannelID!=KSpiChannelUnbound);}
public:
    IMPORT_C virtual void Prepare();
    IMPORT_C virtual void Unprepare();
	IMPORT_C virtual void Service();
private:
    void Complete(TInt aValue,TInt aSpread);
public:
    TSglQueLink iLink;
    TInt iChannelID;
    TInt iValue;
    TInt iSpread;
private:
    TBool iReadInProgress;
    TSpiChannelType iType;
    friend class TSpiController;
    };

class TSpiController
    {
public:
	IMPORT_C TSpiController();
    IMPORT_C static TBool ReadNextChannel(TCallBack aCallBack);
    IMPORT_C static void ReadThisChannel(TSpiChannel* aChannel);
	IMPORT_C static TInt ReferenceValue();
    IMPORT_C static void Suspend();
    IMPORT_C static void Resume();
    IMPORT_C static void SetMaxSpread(TInt aSpread);
    TInt static Init3();
protected:
    IMPORT_C static TSpiController *TheController();
	IMPORT_C void Complete(TInt aValue,TInt aSpread);
    inline void InitialisationComplete() {iInitialised=ETrue;}
    inline TSpiChannel* CurrentChannel() {return(iChannel);}
    inline TInt CurrentChannelID() {return(iChannel->iChannelID);}
private:
    void Read(TSpiChannel *aChan, TCallBack aCallBack);
    void Add(TSpiChannel* aChannel);
    static TInt NullCallBack(TAny* aPtr);
    static TInt TimerCallBack(TAny* aPtr);
	TInt BindAChannel(TInt aChannelID);
	void UnbindAChannel(TInt aChannelID);
// Pure virtual
    virtual void InitialiseSpiDevice()=0;
    virtual void StartAveragedReading()=0;
    virtual void StartOneShotReading()=0;
private:
    TSglQue<TSpiChannel> iQueue;
    TMilliSecondCallBack iTimer;
    TSpiChannel* iChannel;
    TBool iInitialised;
    TCallBack iCallBack;
    TUint iChanBoundMask;
	TBool iPerformingARead;
    TBool iSuspended;
    friend class TSpiChannel;
    };

#endif

