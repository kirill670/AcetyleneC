// source\server\mmfdatapath.h
// Copyright (c) 2001 Symbian Ltd
//

#ifndef __MMF_SERVER_DATAPATH_H__
#define __MMF_SERVER_DATAPATH_H__

#include <mmf\common\mmfcontroller.h>
#include <mmf\server\mmfdatasource.h>
#include <mmf\server\mmfdatasink.h>
#include <mmf\server\mmfcodec.h>
#include <mmf\server\mmfnullcodec.h>
#include <mmf\server\mmfbuffer.h>
#include <mmf\common\mmfutilities.h>
#include <mmf\server\mmfformat.h>
#include "mmfsubthreadbase.h"

/**
 * @publishedAll
 * @deprecated
 *
 * Datapath general error code used when sending events to clients
 */
const TUid KMMFErrorCategoryDataPathGeneralError = {0x101F76DC};



/**
 * @publishedAll
 * @deprecated
 */
class CMMFDataPath : public CActive, 
					 public MDataSink, 
					 public MDataSource, 
					 public MAsyncEventHandler
	{ 
public:
	
	//CMMFDataPath constructor if codec Uid is not already known by CMMFController
	//and there is no data path ambiguity - ie only one data path is possible
	IMPORT_C static CMMFDataPath* NewL(MAsyncEventHandler& aEventHandler); 

	//CMMFDataPath constructor if codec Uid is not already known by CMMFController
	//and there is ambiguity ie more than one possible data path TMediaId used to select path 
	IMPORT_C static CMMFDataPath* NewL(TMediaId aMediaId, MAsyncEventHandler& aEventHandler); 

	//CMMFDataPath constructor if codec Uid is already known by CMMFController
	//and there is no data path ambiguity - ie only one data path is possible
	IMPORT_C static CMMFDataPath* NewL(TUid aCodecUid, MAsyncEventHandler& aEventHandler); 

	//CMMFDataPath constructor if codec Uid is already known by CMMFController
	//and there is ambiguity ie more than one possible data path TMediaId used to select path 
	IMPORT_C static CMMFDataPath* NewL(TUid aCodecUid, TMediaId aMediaId, MAsyncEventHandler& aEventHandler);

	IMPORT_C virtual ~CMMFDataPath();

	// Called when source and sink needs to be de-referenced
	IMPORT_C virtual void ResetL();

	//from MDataSink - CMMFData path is a sink to its MDataSource
	IMPORT_C virtual void EmptyBufferL(CMMFBuffer* aBuffer, MDataSource* aSupplier, TMediaId /*aMediaId*/); //only required for an active push MDataSource requesting a buffer empty - not implemented
	IMPORT_C virtual void BufferFilledL(CMMFBuffer* aBuffer); //called by the CMMFDataPath's MDataSource when it has filled the buffer
	IMPORT_C virtual TBool CanCreateSinkBuffer(); //from both MDataSource & MDataSink?
	IMPORT_C virtual CMMFBuffer* CreateSinkBufferL(TMediaId /*aMediaId*/); //CMMFDataPath can't create buffers
	IMPORT_C virtual CMMFBuffer* CreateSinkBufferL(TMediaId /*aMediaId*/, TBool &aReference); //CMMFDataPath can't create buffers

	IMPORT_C virtual TFourCC SinkDataTypeCode(TMediaId /*aMediaId*/);

	//from MDataSource
	IMPORT_C virtual void FillBufferL(CMMFBuffer* aBuffer, MDataSink* aConsumer, TMediaId /*aMediaId*/); //only required for an active pull MDataSink requesting buffer fill - not implementated
	IMPORT_C virtual void BufferEmptiedL(CMMFBuffer* aBuffer);//called by the CMMFDataPath's MDataSink when it has emptied the buffer
	IMPORT_C virtual TBool CanCreateSourceBuffer(); //from both MDataSource & MDataSink?
	IMPORT_C virtual CMMFBuffer* CreateSourceBufferL(TMediaId /*aMediaId*/); //CMMFDataPath can't create buffers
	IMPORT_C virtual CMMFBuffer* CreateSourceBufferL(TMediaId /*aMediaId*/, TBool &aReference); //CMMFDataPath can't create buffers
	IMPORT_C virtual TFourCC SourceDataTypeCode(TMediaId /*aMediaId*/);

	IMPORT_C virtual void AddDataSourceL(MDataSource* aSource);
	IMPORT_C virtual void AddDataSinkL(MDataSink* aSink);

	//could derive these from a mixin eg MMMFControle later for active MDataSource/Sinks
	IMPORT_C virtual void PrimeL();
	IMPORT_C virtual void PlayL();
	IMPORT_C virtual void Pause();
	IMPORT_C virtual void Stop();

	IMPORT_C virtual TTimeIntervalMicroSeconds Position() const;
	IMPORT_C virtual void SetPositionL(const TTimeIntervalMicroSeconds& aPosition);

	// Play Window.
	IMPORT_C virtual void SetPlayWindowL( const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd ) ;
	IMPORT_C virtual void ClearPlayWindowL() ;

	//State
	IMPORT_C virtual TInt State();

	//CActive implementations
	IMPORT_C void RunL();
	IMPORT_C void DoCancel();
	IMPORT_C TInt RunError(TInt aError);

	//error handling
	IMPORT_C TInt DoSendEventToClient(TUid aEventType, TInt aErrorCode);

/**
*
* TDataPathState
* Enumeration of the datapath state machine
*
*		Mimics typical MultiMedia behaviour of stopped, primed and playing
*
*/
	enum TDataPathState
		{
		EStopped,
		EPrimed,
		EPlaying,
		ERecording,
		EConverting
		};

	/** 
	 * @internalComponent 
	 */
	class CCompleteCallback : public CActive
		{
	public:
		CCompleteCallback(CMMFDataPath& aDataPath, TBool aWaitForSink);
		~CCompleteCallback();

		void SignalDataPathComplete(TInt aDataPathError);
		void SignalSinkComplete(TInt aSinkError);
		TRequestStatus& ActiveStatus();

		void DoCancel();
	private:
		void RunL();
		CMMFDataPath& iDataPath;
		TBool iDataPathComplete;
		TBool iSinkComplete;
		TBool iWaitForSink;

		TInt iSinkError;
		TInt iDataPathError;
		};
	friend class CCompleteCallback;
protected:

/**
*
* TTransferState
* Enumeration of the transfer state of a data buffer within datapaths flow control
*
* Buffers maybe be filled, emptied, or have "one" shot initialisatings performed upon them.
*
* TTransferState is used within the datapath RunL which drives databuffer exchange
*
*/
	enum TTransferState
		{
		EWaitSink,
		EWaitSource,
		EInitializeSink,
		EInitializeSource,
		ENeedSourceData,
		ENeedSinkData,
		ENeedToMatchSourceToSink,
		ESendDataToSink,
		EEndOfData //indicates that the datapath has transferred all the data to the sink
		};




protected:
	CMMFDataPath(TMediaId aMediaId, MAsyncEventHandler& aEventHandler) : 
		CActive(EPriorityStandard), MDataSink(KUidMmfDataPath), MDataSource(KUidMmfDataPath),
		iEventHandler(aEventHandler), iMediaId(aMediaId), iState(EStopped) 
			{CActiveScheduler::Add(this);};

	IMPORT_C void ConstructL(TUid aCodecUid = KNullUid);
	IMPORT_C virtual void ConstructSourceL( const TDesC8& aInitData ) ;
	IMPORT_C virtual void ConstructSinkL( const TDesC8& aInitData ) ;
	IMPORT_C virtual void EndOfData();

	//These methods use API on DevSound to determine how many samples have been played/recorded
	//and thereby determine the real position.
	TTimeIntervalMicroSeconds CalculateAudioOutputPosition() const;
	TTimeIntervalMicroSeconds CalculateAudioInputPosition() const;

	//These methods determine the position of either the input or the output.
	//The position may come from a format or from an audio input/output depending on 
	//the operation the datapath is doing (Playing (output), Recording & Converting (input))
	TTimeIntervalMicroSeconds OutputPosition() const;
	TTimeIntervalMicroSeconds InputPosition() const;


	//Determines what buffers are required (see TNeedBuffer)
	//May leave KErrNotSupported if source/sinks can't supply the necessary buffers
	TInt DetermineBuffersToUseL(void) const; 

	//Determines how many samples have been played by DevSound
	TInt AudioSamplesPlayed() const;

	//Determines how many samples have been recorded by DevSound
	TInt AudioSamplesRecorded() const;


private:
	void ChangeDataPathTransferState(TTransferState aNewDataPathTransferState);
	void CreateDataPathL(MDataSource* aSource, MDataSink* aSink);
	
	void InitializeSinkL();
	void InitializeSourceL();
	void FillSourceBufferL();
	void FillSinkBufferL();
	void EmptySinkBufferL();
	void DoCleanupBuffers();
	void ObtainSyncBuffersL(); //tries to obtain synchronous data buffers from src/snk

	TTimeIntervalMicroSeconds Duration() const;

	void DoStopL();
	void DoPauseL();
	void DoEndOfDataL();

	IMPORT_C TInt SendEventToClient(const TMMFEvent& aEvent);

	void SetBuffersAvailable();
	void ResetRefBuffers();

	

protected:
	MAsyncEventHandler& iEventHandler;
	MDataSource* iDataSource; //the source of data to which the CMMFDataPath is a MDataSink for
	MDataSink* iDataSink; //the sink of data for which the CMMFDataPath is a MDataSource for
	TBool iSinkCanReceive; //set to true when the sink is able to accept data
	TFourCC iSinkFourCC; //FourCC type of a CMMFDataPath  - same as codec input data type
	TFourCC iSourceFourCC; //FourCC type of a CMMFDataPath - same as codec output data type
	TMediaId iMediaId; //identifies which media type & stream within MDataSource (& MDataSink?)
	CMMFCodec* iCodec;  //Codec in use. Null Codec is signified by == NULL
	TCodecProcessResult iCodecProcessResult;
	TBool iDataPathCreated; //set to ETrue when the data path has a source,sink and can send data from source->sink
	TDataPathState iState;
	TTransferState iTransferState;
	TBool iUseSuppliedCodecUid; //set to true if dataPath has to used a supplied codec in its construction

	CMMFBuffer* iSinkBuffer; //this is set to point to whichever sink buffer is in use
	CMMFBuffer* iSourceBuffer; //this is the pointer to whichever source buffer is in use

	TUint iCurrentSourceFrameNumber; //position in terms of frames or some other time fixed parameter
	TUint iCurrentSinkFrameNumber;

	TBool iNoMoreSourceData; //indicates that all data has been obtained from the source
	TBool iAllDataSentToSink; //indicates that all data has been sent to the sink

	TUint iDataPathCompletedErrorCode; //datapath completed because of an error; usually KErrNone

	// Play Window.  Defaults to the full duration of the clip/source.  
	TTimeIntervalMicroSeconds iPlayWindowStartPosition ;
	TTimeIntervalMicroSeconds iPlayWindowEndPosition ;

	//The position audio will start playing from. 
	//When stopping, this is set to iPlayWindowStartPosition.
	//When pausing, this is set to the current position.
	TTimeIntervalMicroSeconds iStartPosition; 


	//This value can be used to obtain the duration of the source when playing or converting.
	//This is a optimisation as this value will not change if we are playing or converting.
	TTimeIntervalMicroSeconds iCachedSourceDuration;


	TBool iSrcBufRef; // true if source buffer is reference to object owned by someone else
	TBool iSnkBufRef; // true if sink buffer is reference to object owned by someone else

	TBool iObtainingAsyncSourceBuffer; // indicates asynchrous buffers from AudioInput
	TBool iObtainingAsyncSinkBuffer; // indicates asynchrous buffers from AudioOutput

	TBool iPauseCalled;	// indicates DoPauseL has been called

	//Flags to indicate that a buffer is with the source/sink.
	//These are necessary as it is imperrative that when a buffer is with the source/sink, it must
	//not be referenced in any way. The reason for this is that it is not mandated that sources/sinks
	//maintain buffer references. For example, it is valid for DevSound to return recorded data in a
	//different buffer to the one supplied to it.
	TBool iSourceBufferWithSource; 
	TBool iSinkBufferWithSink;


	//holds the number of samples played on audio output at a point where we
	//want to reference play duration from
	TInt iReferenceAudioSamplesPlayed;  


	//holds the number of samples recorded from audio input at a point where we
	//want to reference record duration from
	TInt iReferenceAudioSamplesRecorded;  


	CCompleteCallback * iCompleteCallback;

	//This indicates what buffers are required in order to operate.
	//If a real Codec is in use, buffers are required from both source and sink,
	//else only one is required and source is preferred.
	enum TNeedBuffer
		{
		ENoBuffers = 0x0,
		ENeedSinkBuffer = 0x01,
		ENeedSourceBuffer = 0x10
		};
	TInt iBuffersToUse; //holds the outcome of the call to DetermineBuffersToUseL
	};

#endif

