// include\mmf\server\mmfdatasink.h
// Copyright (c) 2001 Symbian Ltd
//

#ifndef __MMF_SERVER_DATASINK_H__
#define __MMF_SERVER_DATASINK_H__

#include <E32Base.h>
#include <mmf\server\mmfdatasourcesink.hrh>
#include <mmf\common\mmfutilities.h>
#include <ecom\ecom.h>
#include <mmf\common\mmfbase.h>
#include <mmf\common\mmfcontrollerframework.h>

//
// MDataSink mixim
//

class TFourCC;
class TMediaId;
class CMMFBuffer;
class MDataSource;
class MAsyncEventHandler;

/**
 * @publishedAll
 * @released
 */
class MDataSink
	{
public: 

	static inline MDataSink* NewSinkL( TUid aImplementationUid,  const TDesC8& aInitData ) ;
	
	/**
	 * Destructor
	 */
	virtual ~MDataSink() {REComSession::DestroyedImplementation(iDtor_ID_Key);};
	
	/**
	 * Returns the uid identifying the type of data sink
	 *
	 * @return	The uid identifying the type of data sink
	 */
	virtual TUid DataSinkType() const {return iDataSinkType;};
	
	/**
	 * Returns the data type as a fourCC code of the data sink
	 *
	 * This is a pure virtual function that each derrived class must implement.
	 *
	 * @param	"aMediaId"
	 *			This identifies the type of media eg audio or video and the stream id.
	 *			This parameter is required in cases where the sink can accept data
	 * 			of more than one media type and/or multiple streams of data.
	 * @return	The fourCC code identifying the sink datatype for the specified aMediaId
	 */
	virtual TFourCC SinkDataTypeCode(TMediaId /*aMediaId*/) = 0;
	
	/**
	 * Sets the data type as a fourCC code for the data sink
	 *
	 * This is a virtual function that each derived class can implement if the data sink supports
	 * the ability to have its data type set.
	 * 
	 * @param	"aSinkFourCC"
	 *			This specifies the data type as a fourCC code to set the sink to
	 *
	 * @param	"aMediaId"
	 *			This identifies the type of media eg audio or video and the stream id.
	 *			This parameter is required in cases where the source can supply data
	 * 			of more than one media type and/or multiple strams of data.
	 *
	 * @return	KErrNone if successful, KErrNotSupported if the sink does not support having
	 *			it's data type set, otherwise a system wide error code.
	 */
	virtual TInt SetSinkDataTypeCode(TFourCC /*aSinkFourCC*/, TMediaId /*aMediaId*/) {return KErrNotSupported;};
	
	/**
	 * Method called by a MDataSource to request the data sink to empty aBuffer of data.
	 *
	 * This is a pure virtual function that each derived class must implement.
	 * This method is used when a data sink is passively waiting for requests from a supplier ie a data source
	 * to empty a buffer.  The data sink must call the BufferEmptiedL member on aSupplier when it has emptied
	 * the buffer of it's data - the data sink can either make this callback synchronously or asynchronously.
	 * 
	 * @param	"aBuffer"
	 *			The full buffer that needs emptying of it's data
	 *
	 * @param	"aSupplier" 
	 *			The data source that supplied the data. The data sink needs this to make the BufferEmptiedL
	 *			callback on aSupplier to indicate to the data source that the data sink has finished with the buffer.
	 *
	 * @param	"aMediaId"
	 *			This identifies the type of media eg audio or video and the stream id.
	 *			This parameter is required in cases where the source can supply data
	 * 			of more than one media type and/or multiple strams of data
	 */
	virtual void EmptyBufferL(CMMFBuffer* aBuffer, MDataSource* aSupplier, TMediaId /*aMediaId*/)=0;
	
	/**
	 * Method called by a data source to pass back an filled buffer to the sink
	 *
	 * This is a pure virtual function that each derived class must implement.
	 * This method is used as the callback when the data sink actively requests a supplier ie a data source
	 * to fill a buffer by calling the data sources FillBufferL.
	 * When the data sink gets this callback it knows that the buffer has been filled and is ready to be emptied
	 * 
	 * @param	"aBuffer"
	 *			The buffer that has been filled by a data source and is now available for processing
	 */
	virtual void BufferFilledL(CMMFBuffer* aBuffer)=0;
	
	/**
	 * Method to indicate whether the data sink can create a buffer.
	 *
	 * This is a pure virtual function that each derived class must implement.
	 * @deprecated
	 * @return	ETrue if the data sink can create a buffer else EFalse
	 */
	virtual TBool CanCreateSinkBuffer()=0;
	
	/**
	 * Returns a buffer created by the data sink
	 *
	 * This is a pure virtual function that each derived class must implement.
	 * @deprecated
	 * @param	"aMediaId"
	 *			This identifies the type of media eg audio or video and the stream id.
	 *			This parameter is required in cases where the source can supply data
	 * 			of more than one media type and/or multiple strams of data.
	 *
	 * @param	"aReference"
	 *			This must be written to by the method to indicate whether the created buffer is
	 *			a 'reference' buffer.  A 'reference' buffer is a buffer that is owned by the sink
	 *			and should be used in preference to the source buffer provided the source buffer
	 *			is also not a reference buffer.
	 * .  
	 * @return	The created buffer
	 */
	virtual CMMFBuffer* CreateSinkBufferL(TMediaId /*aMediaId*/, TBool &aReference)=0;
	
	/**
	 * Method to 'logon' the data sink to the same thread that sink will be consuming data in.
	 *
	 * This method may be required as the thread that the data sink was created in is not always
	 * the same thread that the data transfer will take place in.  Therefore any thread specific
	 * initialisation needs to be performed in the SinkThreadLogon rather than in the creation 
	 * of the data sink.
	 *
	 * This is a virtual function that a derrived data sink can implement if any thread specific
	 * initialisation is required and/or the data sink can create any asynchronous events.
	 * 
	 * 
	 * @param	"aEventHandler"
	 *			This is an MAsyncEventHandler to handle asynchronous events that occur during the
	 *			transfer of multimedia data.  The event handler must be in the same thread as the data transfer
	 * 			thread - hence the reason it is passed in the SinkThreadLogon as opposed to say the constructor.
	 *
	 *
	 * @return	KErrNone if successful, otherwise a system wide error code.
	 */
	virtual TInt SinkThreadLogon(MAsyncEventHandler& /*aEventHandler*/) {return KErrNone;};
	
	/**
	 * Method to 'logoff' the data sink from the same thread that sink consumes data in.
	 *
	 * This method may be required as the thread that the data sink is deleted in may not be
	 * the same thread that the data transfer took place in.  Therefore any thread specific
	 * releasing of resources needs to be performed in the SinkThreadLogoff rather than in the destructor
	 *
	 * This is a virtual function that a derrived data sink can implement if any thread specific
	 * releasing of resources is required.
	 */
	virtual void SinkThreadLogoff() {};
	
	/**
	 * Method to allow the data sink to negotiate with a data source
	 *
	 * This method is required in cases where the settings of data sink are dependant on those of a data source
	 * This is a virtual function that a derrived data sink can implement
	 * @deprecated
	 * @param	"aDataSource"
	 *			The data source whose settings can affect the data sink.		
	 */
	virtual void NegotiateL(MDataSource& /* aDataSource*/) {};
	
	/**
	 * Method to 'prime' the data sink
	 *
	 * This is a virtual function that a derrived data sink can implement if 
	 * any data sink specific 'priming' is required
	 */
	virtual void SinkPrimeL() {};
	
	/**
	 * Method to 'play' the data sink
	 *
	 * This is a virtual function that a derrived data sink can implement if 
	 * any data sink specific action is required prior to 'playing'ie the start of data transfer
	 */
	virtual void SinkPlayL() {};
	
	/**
	 * Method to 'pause' the data sink
	 *
	 * This is a virtual function that a derrived data sink can implement if 
	 * any data sink specific action is required to 'pause'
	 */
	virtual void SinkPauseL() {};
	
	/**
	 * Method to 'stop' the data sink
	 *
	 * This is a virtual function that a derrived data sink can implement if 
	 * any data sink specific action is required to 'stop'
	 */
	virtual void SinkStopL() {};
	
	/**
	 * Method to set the sink priority settings
	 *
	 * This is a virtual function that a derrived data sink can implement if 
	 * a priority mechanism is required to arbitrate between multiple clients
	 * trying to access the same resource
	 *
	 * @param	"aPrioritySettings
	 *			The sink priority settings
	 */
	virtual void SetSinkPrioritySettings(const TMMFPrioritySettings& /*aPrioritySettings*/) {};
	
	/**
	 * Method to call a sink specific custom command
	 *
	 * This is a virtual function that a derrived data sink can implement if 
	 * it implements any custom commands
	 *
	 * @param	"aMessage"
	 *			Message specifying the custom command
	 */
	virtual void SinkCustomCommand(TMMFMessage& aMessage) {aMessage.Complete(KErrNotSupported);};

protected:
	/**
	 * Method to perform any sink construction dependant on the sink construction
	 * initialisation data aInitData
	 *
	 * This is a pure virtual function that a derrived data sink must implement
	 *
	 * @param	"aInitData"
	 *			Sink specific initialisation data required for sink construction
	 */
	virtual void ConstructSinkL( const TDesC8& aInitData ) = 0;
	MDataSink(TUid aType): iDataSinkType(aType) {}
private:
	TUid iDataSinkType;
	TUid iDtor_ID_Key;
	};

	/**
	 * Method to instantiate a data sink
	 *
	 * @param	"aImplementationUid"
	 *			Uid identifying the data sink to be instantiated
	 *
	 * @param	"aInitData"
	 *			Sink specific initialisation data required for sink construction
	 *
	 * @return	The instantiated data sink
	 */
inline MDataSink* MDataSink::NewSinkL( TUid aImplementationUid,  const TDesC8& aInitData ) 
	{
	MDataSink* retPtr = REINTERPRET_CAST( MDataSink*, REComSession::CreateImplementationL( aImplementationUid,
																			_FOFF(MDataSink, iDtor_ID_Key) ) ) ;
	CleanupDeletePushL(retPtr);
	retPtr->ConstructSinkL( aInitData ) ;

	CleanupStack::Pop(retPtr);
	return retPtr ;
	}

	/**
	 * This method is used by TCleanupItem objects to perform
     * a SinkStopL() when leaving functions exist, ususally between SinkPrimeL-SinkStopL pairs.
	 *
	 * @param	"aSink"
	 *			The data sink to be stopped
	 */
inline static void DoDataSinkStop(TAny* aSink)
	{
	MDataSink* sink = STATIC_CAST(MDataSink*, aSink);
	// we don't want this function to leave because no leaving functions are supposed
	// to be used as argument to the TCleanupItem objects. Hence we catch the error but
	// we do nothing with it.
	TRAPD(error, sink->SinkStopL());
	}

	/**
	 * This method is used by TCleanupItem objects to perform
     * a SinkThreadLogoff()
	 *
	 * @param	"aSink"
	 *			The data sink to be logged off
	 */
inline static void DoDataSinkThreadLogoff(TAny* aSink)
	{
	MDataSink* sink = STATIC_CAST(MDataSink*, aSink);
	sink->SinkThreadLogoff();
	}


#endif
