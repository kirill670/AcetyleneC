// MMFFile.h
//
// Copyright (c) 2001-2002 Symbian Ltd.  All rights reserved.
//


#ifndef __MMFFILE_H_
#define __MMFFILE_H_

#include <f32file.h>

#include <mmf\server\mmfclip.h>
#include <mmf\server\mmfdatabuffer.h>

class CReadWriteRequest;
class CTransferBufferCopy;

/**
 * @publishedAll
 * @released
 */
class TMMFFileParams
	{
public:
	TFileName iPath ; // Filename and path of file.
	} ;

/**
 * @publishedAll
 */
typedef TPckgBuf<TMMFFileParams>  TMMFFileConfig ;


/**
 * @publishedAll
 *
 * This details how big the iTransferBufferCopies array of CMMFFile may 
 * become before we start looking to free entries
 *
 */
const TInt KAcceptableTransferBufferCopiesSize = 5;

/**
 * @publishedAll
 *
 * This details how big the iTransferBufferCopies array of CMMFFile may 
 * become before we start looking to free entries
 *
 */
const TInt KMaximumTransferBufferCopiesSize = 100;


/**
 *  @publishedAll
 *  @released
 *
 *  MultiMedia framework class.  Represents physical file.
 *  May be source file from which data is read or destination to which data is written
 */
class CMMFFile : public CMMFClip
	{
public:
	// From MDataSource
	virtual TFourCC SourceDataTypeCode(TMediaId /*aMediaId*/) ;
	virtual void FillBufferL( CMMFBuffer* aBuffer, MDataSink* aConsumer, TMediaId /*aMediaId*/ ) ;
	virtual void BufferEmptiedL( CMMFBuffer* aBuffer ) ;
	virtual TBool CanCreateSourceBuffer() ;
	virtual CMMFBuffer* CreateSourceBufferL( TMediaId /*aMediaId*/, TBool &aReference ) ;
	virtual TInt SourceThreadLogon(MAsyncEventHandler& /*aEventHandler*/) ;
	virtual void SourceThreadLogoff();
	virtual void SourcePrimeL();
	virtual void SourceStopL();

	// From MDataSink
	virtual TFourCC SinkDataTypeCode(TMediaId /*aMediaId*/) ; //used by data path MDataSource/Sink for codec matching
	virtual void EmptyBufferL( CMMFBuffer* aBuffer, MDataSource* aSupplier, TMediaId /*aMediaId*/ ) ; 
	virtual void BufferFilledL( CMMFBuffer* aBuffer ) ;
	virtual TBool CanCreateSinkBuffer() ;
	virtual CMMFBuffer* CreateSinkBufferL( TMediaId /*aMediaId*/ , TBool &aReference) ;
	virtual TInt SinkThreadLogon(MAsyncEventHandler& /*aEventHandler*/) ;
	virtual void SinkThreadLogoff();
	virtual void SinkPrimeL();
	virtual void SinkStopL();

	// From CMMFClip
	virtual void ReadBufferL( TInt aLength, CMMFBuffer* aBuffer, TInt aPosition, MDataSink* aConsumer);
	virtual void WriteBufferL( TInt aLength, CMMFBuffer* aBuffer, TInt aPosition, MDataSource* aSupplier);
	virtual void ReadBufferL( CMMFBuffer* aBuffer, TInt aPosition, MDataSink* aConsumer) ;
	virtual void WriteBufferL( CMMFBuffer* aBuffer, TInt aPosition, MDataSource* aSupplier) ;
	virtual void ReadBufferL( CMMFBuffer* aBuffer, TInt aPosition ) ;
	virtual void WriteBufferL( CMMFBuffer* aBuffer, TInt aPosition ) ;
	virtual TInt64 BytesFree() ;  // amount of space available for the clip
	virtual TInt Size() ;
	virtual TInt Delete();
	virtual TInt SetSize(TInt aSize);

	// New Functions
	virtual const TDesC& FileName() const ;
	virtual const TDesC& Extension() const ;
	virtual const TDesC& FilePath() const ;
	virtual const TDesC& FileDrive() const ;
	virtual const TFileName FullName() const;
	virtual RFile& FileL() ;

public :
	virtual ~CMMFFile() ;
	static MDataSource* NewSourceL() ;
	static MDataSink* NewSinkL() ;

	void SetTransferBuffer (TBool aTBuffer) ;
	TBool CanUseTransferBuffer () ;
	virtual TBool SinkStopped();

protected :
	virtual void ConstructSourceL( const TDesC8& aInitData ) ;
	virtual void ConstructSinkL( const TDesC8& aInitData ) ;
	void ConstructL(const TDesC8& aInitData) ;
	CMMFFile() ;

	void StoreRequestL( CReadWriteRequest* aRequest ) ;
	void CancelRequests();


	CTransferBufferCopy* ObtainCopyOfTransferBufferL(TInt aMaxLength);

private: 
	void OpenFileL(const TUint aFileMode);

private:
	class CMMFFileAsyncEventHandler : public MAsyncEventHandler
		{
		public:
			CMMFFileAsyncEventHandler(CMMFFile* aParent);
			virtual ~CMMFFileAsyncEventHandler();
		public:
			virtual TInt SendEventToClient(const TMMFEvent& aEvent);
		private:
			CMMFFile* iParent;
		};
private:
	RFile iFile ;
	TBool iFileOpen ;
	TBool iSessionOpen ;
	TBool iSinkNotStopped ;
	RFs iFsSession ;
	TFileName iFullFileName ;
	HBufC* iFileName ;
	HBufC* iFileExt ;
	HBufC* iFilePath ;
	HBufC* iFileDrive ;
	TInt iFileSize; //holds the cached file size

	//Keeps track of the read position within the file. Needed in order to enable passing of the
	//read position to the CReadRequest to manage the LastBuffer flag.
	//NB: Continuous reads once EOF has been reached will result in iPosition going > iFileSize,
	//but this causes no ill effects
	TUint iPosition;

	TFourCC  iSinkFourCC ;
	TFourCC  iSourceFourCC ;


	RPointerArray<CReadWriteRequest> iRequests;

	MAsyncEventHandler *iEventHandler;
	CMMFFileAsyncEventHandler* iMmfFileEventHandler;

	RPointerArray<CTransferBufferCopy> iTransferBufferCopies;
	friend class CMMFFileAsyncEventHandler;
	};




#endif
