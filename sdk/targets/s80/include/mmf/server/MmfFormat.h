// include\server\mmfformat.h
// Copyright (c) 2001 Symbian Ltd
//

#ifndef __MMF_SERVER_FORMAT_H__
#define __MMF_SERVER_FORMAT_H__

#include <mmfdatasink.h>
#include <mmfdatasource.h>
#include <ecom\ecom.h>
#include <mmfPluginInterfaceUIDs.hrh>

const TUint KMMFFormatDefaultFrameSize = 0x1000;  //4K
/**
 * @publishedAll
 * @released
 *
 * CMMFFormatDecode
 * Base class from which source formats can be derived from.   The intended usage is for controllers that can support more
 * Than one type of format.
 * The class is an MDataSource as far as the data path is concerned but is an MDataSink to the clip
 * that is the source of the actual data.
 * All CMMFFormatDecode plugin DLLs must include interface_uid = KMmfUidPluginInterfaceFormatDecode in their .rss files.
 */
class CMMFFormatDecode : public CBase, public MDataSource, public MDataSink
	{
public:
	// ECOM creation.
	IMPORT_C static CMMFFormatDecode* NewL( TUid aUid, MDataSource* aSource );
	IMPORT_C static CMMFFormatDecode* NewL( const TDesC& aFileName, MDataSource* aSource, const TDesC& aPreferredSupplier ) ;
	IMPORT_C static CMMFFormatDecode* NewL( const TDesC8& aSourceHeader,  MDataSource* aSource, const TDesC& aPreferredSupplier ) ;
	IMPORT_C static CMMFFormatDecode* NewL( MDataSource* aSource, const TDesC& aPreferredSupplier ) ;

	/**
	 * Destructor
	 */
	virtual ~CMMFFormatDecode()  {REComSession::DestroyedImplementation(iDtor_ID_Key);};

	// returns ECOM plugin uid of this format
	TUid ImplementationUid() const {return iImplementationUid;}

	/**
	 * Gets the number of streams of the specified media type.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaId"
	 *			The media type id.
	 * @return	The number of streams.
	 */
	virtual TUint Streams(TUid aMediaType) const = 0;

	/**
	 * Gets the time interval for one frame for the specified media type.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The frame time interval
	 */
	virtual TTimeIntervalMicroSeconds FrameTimeInterval(TMediaId aMediaType) const = 0;


	/**
	 * Returns the duration of the clip for the specified media type.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The duration
	 */
	virtual TTimeIntervalMicroSeconds Duration(TMediaId aMediaType) const = 0;

	/**
	 * Request from CMMFDataPath to fill the specified buffer.
	 * The CMMFFormat needs to break this down into one or more reads from the clip.
	 * (from MDataSource - CMMFFormatDecode is a MDataSource to a CMMFDataPath consumer)
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aBuffer"
	 *			The buffer to fill.
	 * @param	"aConsumer"
	 *			The consumer.
	 * @param	"aMediaId"
	 *			The media type id.
	 */
	virtual void FillBufferL(CMMFBuffer* aBuffer, MDataSink* aConsumer, TMediaId aMediaId)=0;
	
	/**
	 * @internalAll
	 */
	virtual void BufferEmptiedL(CMMFBuffer* /*aBuffer*/) {}

	/**
	 * Tests whether a source buffer can be created.
	 * The format knows what type of source buffer it requires so default returns ETrue.
	 * It doesn't usually need to set the size of this buffer.
	 *
	 * @return	ETrue if buffer can be created, EFalse otherwise.
	 */
	virtual TBool CanCreateSourceBuffer() {return ETrue;}

	/**
	 * Creates a source buffer.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaId"
	 *			The media type id.
	 * @param	"aReference"
	 *			If ETrue the MDataSource owns the buffer. 
	 *			If EFalse, then the caller owns the buffer.
	 * @return	Source buffer.
	 */
	virtual CMMFBuffer* CreateSourceBufferL(TMediaId /*aMediaId*/, TBool &aReference)=0;
	
	/**
	 * Gets the source data type code for the specified media type ID. 
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The source data type code.
	 */
	virtual TFourCC SourceDataTypeCode(TMediaId /*aMediaId*/)=0;

	/**
	 * @internalAll
	 */
	virtual void EmptyBufferL(CMMFBuffer* /*aBuffer*/, MDataSource* /*aSupplier*/, TMediaId /*aMediaId*/) {}


	/**
	 * Called by the CMMFFormat's MDataSource when it has filled the buffer.
	 * The default implementation below would need overriding in cases where multiple
	 * clip reads were required to fill the buffer from the data path.
	 *
	 * @param	"aBuffer"
	 *			The buffer to which the clip is added.
	 */
	virtual void BufferFilledL(CMMFBuffer* aBuffer) {iDataPath->BufferFilledL(aBuffer);}	

	/**
	 * Tests whether a sink buffer can be created.
	 * Format would normally pass its own buffer onto the CMMFClip, so
	 * this may not be required.
	 * The default returns EFalse.
	 *
	 * @return	ETrue if buffer can be created, EFalse otherwise.
	 */
	virtual TBool CanCreateSinkBuffer() {return EFalse;}

	/**
	 * Creates a sink buffer for the specified media ID.
	 * The default version returns NULL.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @param	"aReference"
	 *			If ETrue the MDataSink owns the buffer. 
	 *			If EFalse, then the caller owns the buffer.
	 * @return	The CMMFBuffer
	 */
	virtual CMMFBuffer* CreateSinkBufferL(TMediaId /*aMediaId*/, TBool &/*aReference */) {return NULL;};

	/**
	 * Gets the sink data type code for the specified media type ID. 
	 * This would be the same as the source data type four CC although 
	 * the clip is not going to need this info
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The sink data type code.
	 */
	virtual TFourCC SinkDataTypeCode(TMediaId /*aMediaId*/) {TFourCC fourCC; return fourCC;}
	
	/**
	 * Meta Data support.The decode format is only capable of reading meta data entries from the clip.
	 * Gets the number of meta data entries. 
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aNumberOfEntries"
	 *			On return, the number of meta data entries.
	 */
	virtual void GetNumberOfMetaDataEntriesL(TInt& /*aNumberOfEntries*/) {User::Leave(KErrNotSupported);};

	/**
	 * Gets the specified meta data entry.  
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aIndex"
	 *			The zero based meta data entry index to retrieve.
	 * @return	The meta data entry.
	 */
	virtual CMMFMetaDataEntry* MetaDataEntryL(TInt /*aIndex*/) {User::Leave(KErrNotSupported); return NULL;};

	//audio format methods

	/**
	 * Sets the number of channels.  
	 * The default returns KErrNotSupported.
	 *
	 * @param	"aChannels"
	 *			The number of channels.
	 * @return	KErrNone or one of the other system-wide error codes.
	 */
	virtual TInt SetNumChannels(TUint /*aChannels*/) {return KErrNotSupported;}

	/**
	 * Sets the sample rate.  
	 * The default returns KErrNotSupported.
	 *
	 * @param	"aSampleRate"
	 *			The sample rate.
	 * @return	KErrNone or one of the other system-wide error codes.
	 */
	virtual TInt SetSampleRate(TUint /*aSampleRate*/) {return KErrNotSupported;}

	/**
	 * Sets the bit rate.  
	 * The default returns KErrNotSupported.
	 *
	 * @param	"aBitRate"
	 *			The bit rate.
	 * @return	KErrNone or one of the other system-wide error codes.
	 */
	virtual TInt SetBitRate(TUint /*aBitRate*/) {return KErrNotSupported;}

	/**
	 * Gets the number of channels.  
	 * The default returns 0.
	 *
	 * @return	The number of channels.
	 */
	virtual TUint NumChannels() {return 0;}

	/**
	 * Gets the sample rate.  
	 * The default returns 0.
	 *
	 * @return	The sample rate.
	 */
	virtual TUint SampleRate() {return 0;}

	/**
	 * Gets the bit rate.  
	 * The default returns 0.
	 *
	 * @return	The bit rate.
	 */
	virtual TUint BitRate() {return 0;}

	/**
	 * Gets the supported sample rates.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aSampleRates"
	 *			Reference to an array of supported sample rates.
	 */
	virtual void GetSupportedSampleRatesL(RArray<TUint>& /*aSampleRates*/) {User::Leave(KErrNotSupported);}

	/**
	 * Gets the supported bit rates.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aBitRates"
	 *			Reference to an array of supported bit rates.
	 */
	virtual void GetSupportedBitRatesL(RArray<TUint>& /*aBitRates*/) {User::Leave(KErrNotSupported);}

	/**
	 * Gets the supported number of channels.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aNumChannels"
	 *			Reference to an array of supported number of channels.
	 */
	virtual void GetSupportedNumChannelsL(RArray<TUint>& /*aNumChannels*/) {User::Leave(KErrNotSupported);}

	/**
	 * Gets the supported data types for the given media type id.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aMediaId"
	 *			The media type id.
	 * @param	"aDataTypes"
	 *			Reference to an array of supported data types.
	 */
	virtual void GetSupportedDataTypesL(TMediaId /*aMediaId*/, RArray<TFourCC>& /*aDataTypes*/) {User::Leave(KErrNotSupported);}

	/**
	 * Used by the sink to suggest a source buffer size.
	 * This is an optional function provided so that a controller can suggest a buffer 
	 * size for the format. The controller should not assume that the format will accept 
	 * the suggested buffer size and there is no obligation on behalf of the format to 
	 * use the suggested buffer size.

	 * @param	"aSuggestedBufferSize"
	 *			A recommended buffer size that the format should create.
	 */
	virtual void SuggestSourceBufferSize(TUint /*aSuggestedBufferSize*/) {}	


	/** 
	 * Used to set the formats position.
	 * Subsequent data reads should ignore the FrameNumber in the CMMFBuffer and use this
	 * setting to determine what data to provide.
	 *
	 * The actual position the format sets itself to may vary to this setting to ensure
	 * that it is aligned to sample boundaries to ensure consistent data output.
	 *
	 * If not supported, positional information should be extracted from the FrameNumber in CMMFBuffer
	 *
	 * @param "aPosition"
	 *         The position the format should position to
	 */
    virtual void SetPositionL(const TTimeIntervalMicroSeconds& /*aPosition*/) {User::Leave(KErrNotSupported);}

    
	/**
	 * Supplies the current position. Subsequent data reads will commence from this position.
	 */
	virtual TTimeIntervalMicroSeconds PositionL() {User::Leave(KErrNotSupported);return TTimeIntervalMicroSeconds(0);}



protected:
	//ConstructSourceL should never be called. The CMMFFormatDecode NewL functions should 
	//always be used to instantiate a CMMFFormatDecode object (not MDataSource::NewL)
	/**
	 * @internalAll
	 */
	virtual void ConstructSourceL( const TDesC8& /*aInitData*/ ) {User::Leave(KErrNotSupported);}
	//ConstructSinkL should never be called. The CMMFFormatDecode NewL functions should 
	//always be used to instantiate a CMMFFormatDecode object (not MDataSink::NewL)
	/**
	 * @internalAll
	 */
	virtual void ConstructSinkL( const TDesC8& /*aInitData*/ ) {User::Leave(KErrNotSupported);}	 

	/**
	 * Default constructor
	 */
	CMMFFormatDecode() : MDataSource(KUidMmfFormatDecode), MDataSink(KUidMmfFormatDecode) {};

	// Creates and initialises format plugin.
	static CMMFFormatDecode* CreateFormatL(TUid aImplementationUid, MDataSource* aSource);
protected:
	/** The clip is the source for the decode format */
	MDataSource* iClip;
	/** The Data path is the sink for the decode format */
	MDataSink* iDataPath;
private:
	TUid iDtor_ID_Key ; // ECOM
	TUid iImplementationUid;
	};


/**
 * @publishedAll
 * @released
 *
 * CMMFFormatEncode
 * Base class from which sink formats can be derived from.   The intended usage is for controllers that can support more
 * Than one type of format.
 * The class is an MDataSink as far as the data path is concerned but is an MDataSource to the clip
 * that is the sink of the actual data.
 * All CMMFFormatEncode plugin DLLs must include interface_uid = KMmfUidPluginInterfaceFormatEncode in their .rss files.
 */
class CMMFFormatEncode : public CBase, public MDataSource, public MDataSink
	{
public:
	// ECOM creation.
	IMPORT_C static CMMFFormatEncode* NewL( TUid aUid, MDataSink* aSink );
	IMPORT_C static CMMFFormatEncode* NewL( const TDesC& aFileName, MDataSink* aSink, const TDesC& aPreferredSupplier ) ;
	IMPORT_C static CMMFFormatEncode* NewL( const TDesC8& aSourceHeader,  MDataSink* aSink, const TDesC& aPreferredSupplier ) ;
	IMPORT_C static CMMFFormatEncode* NewL( MDataSink* aSink, const TDesC& aPreferredSupplier ) ;

	/**
	 * Destructor
	 */
	virtual ~CMMFFormatEncode()  {REComSession::DestroyedImplementation(iDtor_ID_Key);}

	// returns ECOM plugin uid of this format
	TUid ImplementationUid() const {return iImplementationUid;}

	/**
	 * Gets the time interval for one frame for the specified media type.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The frame time interval
	 */
	virtual TTimeIntervalMicroSeconds FrameTimeInterval(TMediaId aMediaType) const = 0;

	
	/**
	 * Returns the duration of the sink clip for the specified media type.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The duration
	 */
	virtual TTimeIntervalMicroSeconds Duration(TMediaId aMediaType) const = 0;

	/**
	 * @internalAll
	 */
	virtual void FillBufferL(CMMFBuffer* /*aBuffer*/, MDataSink* /*aConsumer*/, TMediaId /*aMediaId*/) {}
	
	/**
	 * Called by the clip when it has added the data to the file.
	 *
	 * @param	"aBuffer"
	 *			The emptied buffer.
	 */
	virtual void BufferEmptiedL(CMMFBuffer* aBuffer) {iDataPath->BufferEmptiedL(aBuffer);}

	/**
	 * Tests whether a source buffer can be created.
	 * The default returns EFalse.
	 *
	 * @return	ETrue if buffer can be created, EFalse otherwise.
	 */
	virtual TBool CanCreateSourceBuffer() {return EFalse;}

	/**
	 * Creates a source buffer. The default returns NULL.
	 *
	 * @param	"aMediaId"
	 *			The media type id.
	 * @param	"aReference"
	 *			If ETrue the MDataSource owns the buffer. 
	 *			If EFalse, then the caller owns the buffer.
	 * @return	Source buffer.
	 */
	virtual CMMFBuffer* CreateSourceBufferL(TMediaId /*aMediaId*/, TBool &/*aReference*/) {return NULL;};
	
	/**
	 * Gets the source data type code for the specified media type ID. 
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The source data type code.
	 */
	virtual TFourCC SourceDataTypeCode(TMediaId /*aMediaId*/) {TFourCC fourCC; return fourCC;}

	/**
	 * Called by the CMMFDataPath to add a buffer to a clip.
	 * (from MDataSink - CMMFFormatEncode is a MDataSink to a CMMFDataPath)
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aBuffer"
	 *			The buffer to which the clip is added.
	 * @param	"aSupplier"
	 *			Data source.
	 * @param	"aMediaType"
	 *			The media type id.
	 */
	virtual void EmptyBufferL(CMMFBuffer* aBuffer, MDataSource* aSupplier, TMediaId aMediaId)=0;

	/**
	 * @internalAll
	 */
	virtual void BufferFilledL(CMMFBuffer* /*aBuffer*/) {}

	/**
	 * Tests whether a sink buffer can be created.
	 * Format would normally pass its own buffer onto the CMMFClip, so
	 * this may not be required.
	 * The default returns ETrue.
	 *
	 * @return	ETrue if buffer can be created, EFalse otherwise.
	 */
	virtual TBool CanCreateSinkBuffer() {return ETrue;}


	/**
	 * Creates a sink buffer for the specified media ID.
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @param	"aReference"
	 *			If ETrue the MDataSink owns the buffer. 
	 *			If EFalse, then the caller owns the buffer.
	 * @return	The CMMFBuffer
	 */
	virtual CMMFBuffer* CreateSinkBufferL(TMediaId /*aMediaId*/, TBool &aReference)=0;

	/**
	 * Gets the sink data type code for the specified media type ID.
	 * This would be the same as the source data type four CC although the clip 
	 * is not going to need this info
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aMediaType"
	 *			The media type id.
	 * @return	The sink data type code.
	 */
	//
	virtual TFourCC SinkDataTypeCode(TMediaId /*aMediaId*/) = 0;

	/**
	 * This function is used to truncate the sink ie a CMMFClip either from the aPosition to the
	 * end of the clip if aToEnd = ETrue or from the start of the clip to aPosition if
	 * aToEnd = EFalse. This function would be called by the CMMFController. The default leaves
	 * with KErrNotSupported.
	 *
	 * @param	"aPosition"
	 *			The position within the clip.
	 * @param	"aToEnd"
	 *			Flag to determine which part of the clip to delete. Clip is truncated from 
	 *			aPosition to the end of the clip, if aToEnd is ETrue. Clip is truncated from 
	 *			the start of the clip to aPosition if aToEnd is EFalse. 
	 */
	virtual void CropL(TTimeIntervalMicroSeconds /*aPosition*/,TBool /*aToEnd*/ = ETrue) {User::Leave(KErrNotSupported);}


	/**
	 * Meta Data support.The encode format is capable of reading and writing meta data to the clip.
	 * Gets the number of meta data entries. 
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aNumberOfEntries"
	 *			On return, the number of meta data entries.
	 */
	virtual void GetNumberOfMetaDataEntriesL(TInt& /*aNumberOfEntries*/) {User::Leave(KErrNotSupported);};

	/**
	 * Gets the specified meta data entry.  
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aIndex"
	 *			The zero based meta data entry index to retrieve.
	 * @return	The meta data entry.
	 */
	virtual CMMFMetaDataEntry* MetaDataEntryL(TInt /*aIndex*/) {User::Leave(KErrNotSupported); return NULL;};

	/**
	 * Adds the specified meta data entry to the clip.  
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aNewEntry"
	 *			The meta data entry to add.
	 */
	virtual void AddMetaDataEntryL(const CMMFMetaDataEntry& /*aNewEntry*/) {User::Leave(KErrNotSupported);};

	/**
	 * Removes the specified meta data entry.  
	 * The default returns KErrNotSupported.
	 *
	 * @param	"aIndex"
	 *			The zero based meta data entry index to retrieve.
	 * @return	KErrNone or one of the other system-wide error codes.
	 */
	virtual TInt RemoveMetaDataEntry(TInt /*aIndex*/) {return KErrNotSupported;};

	/**
	 * Replaces the specified meta data entry.  
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aIndex"
	 *			The zero based meta data entry index to replace.
	 * @param	"aNewEntry"
	 *			The meta data entry to replace.
	 */
	virtual void ReplaceMetaDataEntryL(TInt /*aIndex*/, const CMMFMetaDataEntry& /*aNewEntry*/) {User::Leave(KErrNotSupported);};

	
	//audio format methods

	/**
	 * Sets the number of channels.  
	 * The default returns KErrNotSupported.
	 *
	 * @param	"aChannels"
	 *			The number of channels.
	 * @return	KErrNone or one of the other system-wide error codes.
	 */
	virtual TInt SetNumChannels(TUint /*aChannels*/) {return KErrNotSupported;}

	/**
	 * Sets the sample rate.  
	 * The default returns KErrNotSupported.
	 *
	 * @param	"aSampleRate"
	 *			The sample rate.
	 * @return	KErrNone or one of the other system-wide error codes.
	 */
	virtual TInt SetSampleRate(TUint /*aSampleRate*/) {return KErrNotSupported;}

	/**
	 * Sets the bit rate.  
	 * The default returns KErrNotSupported.
	 *
	 * @param	"aBitRate"
	 *			The bit rate.
	 * @return	KErrNone or one of the other system-wide error codes.
	 */
	virtual TInt SetBitRate(TUint /*aBitRate*/) {return KErrNotSupported;}

	/**
	 * Gets the number of channels.  
	 * The default returns 0.
	 *
	 * @return	The number of channels.
	 */
	virtual TUint NumChannels() {return 0;}

	/**
	 * Gets the sample rate.  
	 * The default returns 0.
	 *
	 * @return	The sample rate.
	 */
	virtual TUint SampleRate() {return 0;}

	/**
	 * Gets the default sample rate.  
	 * The default returns 0.
	 *
	 * @return	The default sample rate.
	 */
	virtual TUint GetDefaultSampleRate() {return 0;}

	/**
	 * Gets the bit rate.  
	 * The default returns 0.
	 *
	 * @return	The bit rate.
	 */
	virtual TUint BitRate() {return 0;}

	/**
	 * Gets the bytes per second.  
	 * The default returns 0.
	 *
	 * @return	The bytes per second.
	 */
	virtual TInt64 BytesPerSecond() {return 0;}

	/**
	 * Gets the supported sample rates.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aSampleRates"
	 *			Reference to an array of supported sample rates.
	 */
	virtual void GetSupportedSampleRatesL(RArray<TUint>& /*aSampleRates*/) {User::Leave(KErrNotSupported);}

	/**
	 * Gets the supported bit rates.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aBitRates"
	 *			Reference to an array of supported bit rates.
	 */
	virtual void GetSupportedBitRatesL(RArray<TUint>& /*aBitRates*/) {User::Leave(KErrNotSupported);}

	/**
	 * Gets the supported number of channels.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aNumChannels"
	 *			Reference to an array of supported number of channels.
	 */
	virtual void GetSupportedNumChannelsL(RArray<TUint>& /*aNumChannels*/) {User::Leave(KErrNotSupported);}

	/**
	 * Gets the supported data types for the given media type id.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aMediaId"
	 *			The media type id.
	 * @param	"aDataTypes"
	 *			Reference to an array of supported data types.
	 */
	virtual void GetSupportedDataTypesL(TMediaId /*aMediaId*/, RArray<TFourCC>& /*aDataTypes*/) {User::Leave(KErrNotSupported);}

	/**
	 * Sets the maximum clip size.
	 * The default leaves with KErrNotSupported.
	 *
	 * @param	"aBytes"
	 *			Maximum clip size.
	 */
	virtual void SetMaximumClipSizeL(TInt /*aBytes*/) {User::Leave(KErrNotSupported);}

	/**
	 * Gets the maximum clip size.
	 * The default returns 0.
	 *
	 * @return	Maximum clip size.
	 */
	virtual TInt MaximumClipSize() { return 0;}



	/** 
	 * Used to set the formats position.
	 * Subsequent data reads should ignore the FrameNumber in the CMMFBuffer and use this
	 * setting to determine what data to provide.
	 *
	 * The actual position the format sets itself to may vary to this setting to ensure
	 * that it is aligned to sample boundaries to ensure consistent data output.
	 *
	 * If not supported, positional information should be extracted from the FrameNumber in CMMFBuffer
	 *
	 * @param "aPosition"
	 *         The position the format should position to
	 */
    virtual void SetPositionL(const TTimeIntervalMicroSeconds& /*aPosition*/) {User::Leave(KErrNotSupported);}

    
	/**
	 * Supplies the current position. Subsequent data reads will commence from this position.
	 */
	virtual TTimeIntervalMicroSeconds PositionL() {User::Leave(KErrNotSupported);return TTimeIntervalMicroSeconds(0);}


protected:
	//ConstructSourceL should never be called. The CMMFFormatEncode NewL functions should 
	//always be used to instantiate a CMMFFormatEncode object (not MDataSource::NewL)
	/**
	 * @internalAll
	 */
	virtual void ConstructSourceL( const TDesC8& /*aInitData*/ ) {User::Leave(KErrNotSupported);}
	//ConstructSinkL should never be called. The CMMFFormatEncode NewL functions should 
	//always be used to instantiate a CMMFFormatEncode object (not MDataSink::NewL)
	/**
	 * @internalAll
	 */
	virtual void ConstructSinkL(  const TDesC8& /*aInitData*/ ) {User::Leave(KErrNotSupported);}	

	/**
	 * Default constructor
	 */
	CMMFFormatEncode() : MDataSource(KUidMmfFormatEncode), MDataSink(KUidMmfFormatEncode) {};

	// Creates and initialises format plugin.
	static CMMFFormatEncode* CreateFormatL(TUid aImplementationUid, MDataSink* aSink);
protected:
	/** The Data path is the source for the encode format */
	MDataSource* iDataPath;
	/** The clip is the sink for the encode format */
	MDataSink* iClip;
private:
	TUid iDtor_ID_Key ; // ECOM
	TUid iImplementationUid;
	};


class CMMFFormatPluginSelectionParameters;
/**
 * @publishedAll
 * @released
 */
class MMFFormatEcomUtilities
	{
public:
	//Internal utility function to choose a format plugin from ECOM
	static TUid SelectFormatPluginL(const CMMFFormatPluginSelectionParameters& aSelectParams);

	// Internal utility function to instantiate each format decode plugin in turn 
	// until we find one that works
	static CMMFFormatDecode* SelectFormatDecodePluginL(const CMMFFormatPluginSelectionParameters& aSelectParams, MDataSource* aSource);
	};

#endif

