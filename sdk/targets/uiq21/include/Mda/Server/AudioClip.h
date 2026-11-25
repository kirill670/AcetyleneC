// Mda\Server\AudioClip.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_SERVER_AUDIOCLIP_H__
#define __MDA_SERVER_AUDIOCLIP_H__

#include <Mda\Server\Clip.h>
#include <Mda\Server\AudioIo.h>
#include <Mda\Server\Port.h>
#include <Mda\Server\Controller.h>
#include <Mda\Server\Buffer.h>
#include <Mda\Server\Dispatcher.h>
#include <Mda\Server\AudioCodecs.h>
#include <Mda\Server\AudioDatatype.h>

enum TMdaAudioPortFunction
	{
	EMLbAudioPortFunctionBase = EMLbPortNegotiate,
	EMLbAudioPortFillBuffer
	};

class CMdaAudioClipSrcPort;
class CMdaAudioClipDstPort;
class CMdaAudioCodecFactory;
class CMdaAudioClipFormat : public CMdaLinearClipFormat, public MMdaMessage, public MMdaProcessor, public MMdaEventListener
	{
public:
	IMPORT_C CMdaAudioClipFormat(TUid aType,TInt aFormatDataSizeRequired);
	IMPORT_C virtual ~CMdaAudioClipFormat();
	IMPORT_C virtual TTimeIntervalMicroSeconds Duration();
	IMPORT_C virtual TInt BytesPerSecond();
	//
	inline CMdaAudioCodecFactory* CodecFactory();
protected:
	// From CMdaResourceObject
	IMPORT_C virtual void ConfigL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelConfig(CMdaMessage* aMessage);
	IMPORT_C virtual void CreatePortL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelCreatePort(CMdaMessage* aMessage);
	// From MMdaMessage
	IMPORT_C virtual void MessageDoComplete(TInt aVal);	
	IMPORT_C virtual void MessageDoReturnObjectL(TInt aArg, CMdaObject* aObject);
	// From MMdaProcessor
	IMPORT_C virtual void ProcessL();
	IMPORT_C virtual void ProcessFailed(TInt aError);
	// From MMdaEventListener
	IMPORT_C virtual void Event(const TMdaEvent& aEvent);
	// New functions
	IMPORT_C virtual void OpenExistingL();
	IMPORT_C virtual void ReadFormatL();
	IMPORT_C virtual void ProcessFormatL();
	IMPORT_C virtual void OpenNewL();
	IMPORT_C virtual void WriteHeaderL();
	IMPORT_C virtual void MatchCodecL();
	IMPORT_C virtual void CreateCodecL();
	IMPORT_C virtual void ConfigCodecL();
	IMPORT_C virtual void CodecConfiguredL();
	IMPORT_C virtual void UpdateHeaderL();
	IMPORT_C virtual void DoConfigL();
	IMPORT_C void DoReadL(TInt aReadPosition = 0);
	IMPORT_C virtual void DoCropL(TMdaClipCrop* aCropParams);
	// Derived classes must supply these functions
	virtual TUid CodecUid() const = 0;
	IMPORT_C virtual CMdaAudioClipSrcPort* CreateSourcePortL();
	IMPORT_C virtual CMdaAudioClipDstPort* CreateDestinationPortL();
	virtual void SetStartPosition()=0;
	virtual const TPtrC8 CodecMatchData()=0;
protected:
	enum TState
		{
		EClosed=0,
		EOpenExisting,
		EReadFormat,
		EProcessFormat,
		EOpenNew,
		EWriteHeader,
		ENoCodec,
		EMatchCodec,
		ECreateCodec,
		EConfigCodec,
		ECodecConfigured,
		EConfig,
		EOpen
		};
public:
	TInt iNumberOfSamples;
	TInt iNumberOfRepeats;
	TInt iMicroSecTrailingSilence;
	TBool iIsCompressed;
protected:
	TState iState;
	CMdaMessageProcessor iProcessor;
	CMdaTargetedMessage iMsg;
	TMdaAudioDataSettings iAudio;
	CMdaAudioCodecFactory* iCodecFactory;
	HBufC8* iFormatHeader;
	HBufC8* iBuffer;
	TMdaPtr8 iBufDes;
	TInt iFormatDataSizeRequired;
	//
	friend class CMdaAudioClipSrcPort;
	friend class CMdaAudioClipDstPort;
	friend class CMdaVfsAudioClipSrcPort;
	friend class CMdaVfsAudioClipDstPort;
	};

inline CMdaAudioCodecFactory* CMdaAudioClipFormat::CodecFactory()
	{ return iCodecFactory; };

class CMdaAudioClipSrcPort :  public CMdaPort, public MMdaAudioDatatypeSupplier
	{
public:
	IMPORT_C CMdaAudioClipSrcPort(CMdaAudioClipFormat& aFormat);
	IMPORT_C virtual ~CMdaAudioClipSrcPort();
protected:
	// From CMdaPort
	IMPORT_C virtual void Close();
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void NewIOL(CMdaMessage* aMessage);
	//
	IMPORT_C virtual TBool MediaTypePresent(TUid aMediaType) const;
	IMPORT_C virtual void PortConfigL(CMdaMessage* aMessage);
	//
	IMPORT_C virtual void MachineStateChangeCompleted(CMdaMachine* aMachine);
	IMPORT_C virtual void MachinePrepareL();
	//
	// From MMdaAudioDatatypeSupplier
	IMPORT_C virtual void AdtsInitL(); // Fill settings values
	IMPORT_C virtual void AdtsPrepareL(); // Allocate resources
	IMPORT_C virtual void AdtsPrimeL(); // Allocate resources
	IMPORT_C virtual void AdtsPlayL(); // Allocate resources
	IMPORT_C virtual void AdtsBuffer(CMdaAudioBuffer* aBuffer);
	IMPORT_C virtual void AdtsPause();
	IMPORT_C virtual void AdtsStop();
	IMPORT_C virtual void AdtsUnprepare();
	// New
	IMPORT_C virtual void DoBufferFillL(CMdaMessage* aMessage);
	IMPORT_C virtual void DataMessageComplete(TInt aVal);
	IMPORT_C virtual void NewBufferL();
	IMPORT_C virtual void QueueReadFromL();
	IMPORT_C virtual void ReadComplete(TInt aVal);

	IMPORT_C virtual void NewFrameL();
	IMPORT_C virtual TBool PositionL(TMdaElapsedTime* aPackage);
	IMPORT_C virtual TBool WindowL(TMdaClipPrimeWindow* aPackage);
	IMPORT_C virtual TBool DurationL(TMdaClipDuration* aPackage);
	IMPORT_C virtual void DoSetPosition();
	IMPORT_C virtual void ValidateWindow();
protected:
	class TMessageHolder : public MMdaMessage
		{
	public:
		CMdaAudioClipSrcPort* iParent;
		CMdaDispatchMessage* iMsg;
		};
	class TDataMessageHolder : public TMessageHolder
		{
	public:
		inline virtual void MessageDoComplete(TInt aVal);
		};
	class TReadMessageHolder : public TMessageHolder
		{
	public:
		inline virtual void MessageDoComplete(TInt aVal);
		};
	friend class TDataMessageHolder;
	friend class TReadMessageHolder;
protected:
	enum TDataState
		{
		EIdle,
		EFillingBuffer,
		EReadingData
		};
	enum TFillState
		{
		ENoSourceData,
		EGetSourceData,
		EProcessNewSourceData,
		EProcessData,
		EReturnFilledBuffer,
		EProcessEndOfFile
		};
protected:
	CMdaAudioClipFormat& iFormat;
	TDataMessageHolder iDataMsg;
	TReadMessageHolder iReadMsg;
	//
	CMdaAudioSrcDatatype* iSrcDatatype;
	CMdaCodec* iCodec;
	CMdaAudioBuffer* iAudioBuffer;
	CMdaAudioBuffer* iOurBuffer;
	//
	TTimeIntervalMicroSeconds iLatency;
	// Play Window settings
	TTimeIntervalMicroSeconds iStartTime;
	TTimeIntervalMicroSeconds iEndTime;
	TTimeIntervalMicroSeconds iTrailingSilence;
	TInt iRepeats;
	TBool iRestrictedWindow;

	// Play position settings
	TTimeIntervalMicroSeconds iPositionTime;
	//
	TInt iPosition;
	TInt iRepeatsLeft;
	TInt iTrailingLeft;
	//
	TInt iFrameLen;
	TInt iSamplesPerFrame;
	TInt iNewFrameLen;
	//
	TInt iPrimeOffset;
	//
	TMdaPtr8 iSrc;
	TMdaPtr8 iDst;
	//
	TMdaPtr8 iSrcUse;
	TMdaPtr8 iDstUse;
	//
	TDataState iDataState;
	TFillState iFillState;
	//
	HBufC8* iBuffer;
	//
	friend class CMdaAudioClipFormat;
	};

inline void CMdaAudioClipSrcPort::TDataMessageHolder::MessageDoComplete(TInt aVal) 
	{ iParent->DataMessageComplete(aVal); }	
inline void CMdaAudioClipSrcPort::TReadMessageHolder::MessageDoComplete(TInt aVal) 
	{ iParent->ReadComplete(aVal); }	

class CMdaAudioClipDstPort :  public CMdaPort, public MMdaAudioDatatypeConsumer
	{
public:
	IMPORT_C CMdaAudioClipDstPort(CMdaAudioClipFormat& aFormat);
	IMPORT_C virtual ~CMdaAudioClipDstPort();
protected:
	// From CMdaPort
	IMPORT_C virtual void Close();
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void NewIOL(CMdaMessage* aMessage);
	IMPORT_C virtual TBool MediaTypePresent(TUid aMediaType) const;
	IMPORT_C virtual void PortConfigL(CMdaMessage* aMessage);
	IMPORT_C virtual void MachineStateChangeCompleted(CMdaMachine* aMachine);
	IMPORT_C virtual void MachinePrepareL();
	// From MMdaAudioDatatypeConsumer
	IMPORT_C virtual void AdtcInitL(); // Fill settings values
	IMPORT_C virtual void AdtcPrepareL(); // Allocate resources
	IMPORT_C virtual void AdtcPrimeL(); // Allocate resources
	IMPORT_C virtual void AdtcPlayL(); // Allocate resources
	IMPORT_C virtual void AdtcBuffer(CMdaAudioBuffer* aBuffer);
	IMPORT_C virtual void AdtcPause();
	IMPORT_C virtual void AdtcStop();
	IMPORT_C virtual void AdtcUnprepare();
	// New
	IMPORT_C virtual void DoBufferFillL(CMdaMessage* aMessage);
	IMPORT_C virtual void DataMessageComplete(TInt aVal);
	IMPORT_C virtual void NewBufferL();
	IMPORT_C virtual void QueueWriteToL();
	IMPORT_C virtual void WriteComplete(TInt aVal);

	IMPORT_C virtual void NewFrameL();
	IMPORT_C virtual TBool DurationL(TMdaClipDuration* aPackage);
protected:
	class TMessageHolder : public MMdaMessage
		{
	public:
		CMdaAudioClipDstPort* iParent;
		CMdaDispatchMessage* iMsg;
		};
	class TDataMessageHolder : public TMessageHolder
		{
	public:
		inline virtual void MessageDoComplete(TInt aVal);
		};
	class TWriteMessageHolder : public TMessageHolder
		{
	public:
		inline virtual void MessageDoComplete(TInt aVal);
		};
	friend class TDataMessageHolder;
	friend class TWriteMessageHolder;
protected:
	enum TDataState
		{
		EIdle,
		EFillingBuffer,
		EWritingData
		};
protected:
	CMdaAudioClipFormat& iFormat;
	TDataMessageHolder iDataMsg;
	TWriteMessageHolder iWriteMsg;
	//
	CMdaAudioDstDatatype* iDstDatatype;
	CMdaCodec* iCodec;
	CMdaAudioBuffer* iAudioBuffer;
	TBool iReturnBuffer;
	//
	TInt iPosition;
	//
	TInt iFrameLen;
	TInt iSamplesPerFrame;
	TInt iNewFrameLen;
	TInt iSamplesOfThisFrame;
	//
	TMdaPtr8 iSrc;
	TMdaPtr8 iDst;
	//
	TMdaPtr8 iSrcUse;
	TMdaPtr8 iDstUse;
	//
	HBufC8* iBuffer;
	//
	TDataState iDataState;
	//
	friend class CMdaAudioClipFormat;
	};

inline void CMdaAudioClipDstPort::TDataMessageHolder::MessageDoComplete(TInt aVal) 
	{ iParent->DataMessageComplete(aVal); }	
inline void CMdaAudioClipDstPort::TWriteMessageHolder::MessageDoComplete(TInt aVal) 
	{ iParent->WriteComplete(aVal); }	

class CMdaAudioCodecFactory : public CMdaResourceObject
	{
public:
	inline TMdaAudioDataSettings::TAudioCaps Capabilities();
	inline TBool IsCompressed();
	inline TInt RatioUnencoded();
	inline TInt RatioEncoded();
	// These will be called before any codecs created
	virtual void SetFormatHeaderL(const TDesC8& aHeader)=0;
	virtual HBufC8* NewFormatHeaderL(const TMdaAudioDataSettings& aAudio)=0;
	// Config cannot be called after codecs created
	virtual CMdaCodec* CreateReadCodecL()=0;
	virtual CMdaCodec* CreateWriteCodecL()=0;
	// For compressed/framed data
	virtual TInt FrameLength() { return 0; };
	virtual TInt SamplesPerFrame() { return 0; };
protected:
	inline CMdaAudioCodecFactory(TUid aType, TUid aUid,TMdaAudioDataSettings::TAudioCaps aCaps,	TInt aUnenc=1, TInt aEnc=1, TBool aCompressed=EFalse);
protected:
	TMdaAudioDataSettings::TAudioCaps iCaps;
	TBool iCompressed;
	TInt iRatioUnencoded;
	TInt iRatioEncoded;
	};

inline CMdaAudioCodecFactory::CMdaAudioCodecFactory(TUid aType, TUid aUid,TMdaAudioDataSettings::TAudioCaps aCaps,TInt aUnenc,TInt aEnc,TBool aCompressed) :
CMdaResourceObject(aType,aUid),
iCaps(aCaps),
iCompressed(aCompressed),
iRatioUnencoded(aUnenc),
iRatioEncoded(aEnc)
	{}

inline TMdaAudioDataSettings::TAudioCaps CMdaAudioCodecFactory::Capabilities()
	{
	return iCaps;
	}

inline TBool CMdaAudioCodecFactory::IsCompressed()
	{
	return iCompressed;
	}

inline TBool CMdaAudioCodecFactory::RatioUnencoded()
	{
	return iRatioUnencoded;
	}

inline TBool CMdaAudioCodecFactory::RatioEncoded()
	{
	return iRatioEncoded;
	}



class CMdaVfsAudioClipFormat;

class TMdaVfsFrameLength
	{
public:
	inline TMdaVfsFrameLength();
	inline TMdaVfsFrameLength(TInt aSize,TInt aSamples);
public:
	TInt iSize;
	TInt iSamples;
	};

inline TMdaVfsFrameLength::TMdaVfsFrameLength()
		: iSize(0), iSamples(0) {};
inline TMdaVfsFrameLength::TMdaVfsFrameLength(TInt aSize,TInt aSamples)
		: iSize(aSize), iSamples(aSamples) {};



class CMdaVfsAudioCodec : public CMdaAudioCodec
	{
public:
	// New
	IMPORT_C virtual TInt EncodeFrameL(TMdaPtr8* aSrc, TMdaPtr8* aDst,TMdaVfsFrameLength& aFrameLength);
	};



class CMdaVfsAudioCodecFactory : public CMdaAudioCodecFactory
	{
public:
	// New
	inline TBool IsVariableFrameSize();
protected:
	// New
	inline CMdaVfsAudioCodecFactory(TUid aType, TUid aUid,TMdaAudioDataSettings::TAudioCaps aCaps,	TInt aUnenc=1, TInt aEnc=1, TBool aCompressed=ETrue, TBool aVariableFrameSize=ETrue);
protected:
	TBool iVariableFrameSize;
	};

inline TBool CMdaVfsAudioCodecFactory::IsVariableFrameSize()
	{ return iVariableFrameSize; }

inline CMdaVfsAudioCodecFactory::CMdaVfsAudioCodecFactory(TUid aType, TUid aUid,TMdaAudioDataSettings::TAudioCaps aCaps,	TInt aUnenc, TInt aEnc, TBool aCompressed, TBool aVariableFrameSize)
	: CMdaAudioCodecFactory(aType,aUid,aCaps,aUnenc,aEnc,aCompressed), iVariableFrameSize(aVariableFrameSize)
	{}



class CMdaVfsAudioClipSrcPort : public CMdaAudioClipSrcPort
	{
public:
	IMPORT_C CMdaVfsAudioClipSrcPort(CMdaVfsAudioClipFormat& aFormat);
protected:
	// From CMdaAudioClipDstPort
	IMPORT_C virtual void DoSetPosition();
	IMPORT_C virtual void NewFrameL();
	};



class CMdaVfsAudioClipDstPort : public CMdaAudioClipDstPort
	{
public:
	IMPORT_C CMdaVfsAudioClipDstPort(CMdaVfsAudioClipFormat& aFormat);
protected:
	// From CMdaAudioClipDstPort
	IMPORT_C virtual void NewFrameL();
	IMPORT_C virtual void DoBufferFillL(CMdaMessage* aMessage);
	IMPORT_C virtual void AdtcPrepareL();
	IMPORT_C virtual void AdtcStop();
private:
	// New
	void CropPartialFrameL();
	};



class CMdaVfsAudioClipFormat : public CMdaAudioClipFormat
	{
	friend class CMdaVfsAudioClipSrcPort;
	friend class CMdaVfsAudioClipDstPort;
public:
	IMPORT_C CMdaVfsAudioClipFormat(TUid aType,TInt aFormatDataSizeRequired);
	// From CMdaAudioClipFormat
	virtual TTimeIntervalMicroSeconds Duration() =0; // now pure virtual
protected:
	// From CMdaAudioClipFormat
	IMPORT_C virtual CMdaAudioClipSrcPort* CreateSourcePortL();	// really returns a CMdaVfsAudioClipSrcPort*
	IMPORT_C virtual CMdaAudioClipDstPort* CreateDestinationPortL();	// really returns a CMdaVfsAudioClipDstPort*
	virtual void DoCropL(TMdaClipCrop* aCropParams) =0; // now pure virtual
	// New
	virtual TInt Position(TTimeIntervalMicroSeconds& aTime,TBool aRoundUp=EFalse) = 0;
	virtual void FrameAppendedL(const TMdaVfsFrameLength& aFrameLength) = 0;
	};


#endif
