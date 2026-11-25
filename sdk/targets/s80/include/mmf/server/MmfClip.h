// MMFClip.h
//
// Copyright (c) 2001-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MMFCLIP_H_
#define __MMFCLIP_H_

#include <mmf\server\mmfdatasource.h>
#include <mmf\server\mmfdatasink.h>
#include <mmf\server\mmfbuffer.h>
#include <mmf\common\mmfutilities.h>

/**
 * @publishedAll
 * @released
 */
class CMMFClip : public CBase, public MDataSource, public MDataSink
	{
public :
	//asynchronous Read/WriteBufferLs

	/**
	 * Reads aLength number of bytes of data from offset aPosition into buffer aBuffer.
	 * Intended for asynchronous usage.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aLength"
	 *			The number of bytes to read.
	 * @param	"aBuffer"
	 *			The buffer to read the data into.
	 * @param	"aPosition"
	 *			The offset from which to start reading.
	 * @param	"aConsumer"
	 *			The sink of tha data read from the clip. 
	 *			Will be informed of read if not NULL
	 */
	virtual void ReadBufferL( TInt aLength, CMMFBuffer* aBuffer, TInt aPosition, MDataSink* aConsumer) = 0 ;

	/**
	 * Writes aLength number of bytes of data from offset aPosition from buffer aBuffer
	 * Intended for asynchronous usage.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aLength"
	 *			The number of bytes to write.
	 * @param	"aBuffer"
	 *			The buffer to write the data into.
	 * @param	"aPosition"
	 *			The offset from which to start writing.
	 * @param	"aSupplier"
	 *			The source of the data writen to the clip. 
	 *			Will be informed of write if not NULL
	 */
	virtual void WriteBufferL( TInt aLength, CMMFBuffer* aBuffer, TInt aPosition, MDataSource* aSupplier) = 0 ;

	/**
	 * Reads maximum number of bytes of data from offset aPosition into buffer aBuffer.
	 * Intended for asynchronous usage.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aBuffer"
	 *			The buffer to read the data into.
	 * @param	"aPosition"
	 *			The offset from which to start reading.
	 * @param	"aConsumer"
	 *			The sink of tha data read from the clip. 
	 *			Will be informed of read if not NULL
	 */
	virtual void ReadBufferL( CMMFBuffer* aBuffer, TInt aPosition, MDataSink* aConsumer) = 0 ;

	/**
	 * Writes maximum number of bytes of data from offset aPosition from buffer aBuffer
	 * Intended for asynchronous usage.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aBuffer"
	 *			The buffer to write the data into.
	 * @param	"aPosition"
	 *			The offset from which to start writing.
	 * @param	"aSupplier"
	 *			The source of the data writen to the clip. 
	 *			Will be informed of write if not NULL
	 */
	virtual void WriteBufferL( CMMFBuffer* aBuffer, TInt aPosition, MDataSource* aSupplier) = 0 ;

	//synchronous Read/WriteBufferLs

	/**
	 * Reads maximum number of bytes of data from offset aPosition into buffer aBuffer.
	 * Intended for synchronous usage.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aBuffer"
	 *			The buffer to read the data into.
	 * @param	"aPosition"
	 *			The offset from which to start reading.
	 */
	virtual void ReadBufferL( CMMFBuffer* aBuffer, TInt aPosition) = 0 ;

	/**
	 * Writes maximum number of bytes of data from offset aPosition from buffer aBuffer
	 * Intended for synchronous usage.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aBuffer"
	 *			The buffer to write the data into.
	 * @param	"aPosition"
	 *			The offset from which to start writing.
	 */
	virtual void WriteBufferL( CMMFBuffer* aBuffer, TInt aPosition) = 0 ;

	/**
	 * Retrieve the amount of space available for the clip.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @return	The amount of space available.
	 */
	virtual TInt64 BytesFree() = 0 ;

	/**
	 * Retrieve the size of the clip in bytes.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @return	The size of the clip.
	 */
	virtual TInt Size() = 0 ;
	
	/**
	 * Delete the clip. This should be overriden in the derived
	 * classes, the default version returns KErrNotSupported.
	 *
	 * @return	KErrNone if successful, otherwise a system wide error code.
	 */
	virtual TInt Delete()	{return KErrNotSupported;}


	/**
	 * Set the size of the clip. This should be overriden in the derived
	 * classes, the default version returns KErrNotSupported.
	 *
	 * @param	"aSize"
	 *			The size of the clip.
	 * @return	KErrNone if successful, otherwise a system wide error code.
	 */
	virtual TInt SetSize(TInt /*aSize*/)	{return KErrNotSupported;}

protected :
	/**
	 * Constructor
	 */
	CMMFClip( TUid aSourceType, TUid aSinkType ) : MDataSource( aSourceType ), MDataSink( aSinkType ) {}
	} ;


#endif
